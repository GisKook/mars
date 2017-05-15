#include "precomp.h"
static void CloseEvents(int num, HANDLE *hEvents)
{
	for (int i = 0 ; i < num ; i++) {
		if (hEvents[i]) {
			if (!::CloseHandle(hEvents[i])) {
				TraceLastError("CloseEvents(): CloseHandle()");
			}
			hEvents[i] = NULL;
		}
	}
}

BOOL PrepareEvents(int num, HANDLE *hEvents, OVERLAPPED *overlaps)
{
	memset(hEvents, 0, num * sizeof(HANDLE));
	memset(overlaps, 0, num * sizeof(OVERLAPPED));

	for (int i = 0 ; i < num ; i++) {
		overlaps[i].hEvent = hEvents[i] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		if (!hEvents[i]) {
			TraceLastError("PrepareEvents(): CreateEvent()");
			CloseEvents(i, hEvents);
			return FALSE;
		}
	}
	return TRUE;
}

void InOut(
				  HANDLE hC0C,
				  SOCKET hSock,
				  Protocol &protocol,
				  BOOL ignoreDSR,
				  SOCKET hSockListen = INVALID_SOCKET)
{
	printf("InOut() START\n");

	protocol.Clean();

	BOOL stop = FALSE;

	enum {
		EVENT_READ,
		EVENT_SENT,
		EVENT_RECEIVED,
		EVENT_WRITTEN,
		EVENT_STAT,
		EVENT_CLOSE,
		EVENT_ACCEPT,
		EVENT_NUM
	};

	HANDLE hEvents[EVENT_NUM];
	OVERLAPPED overlaps[EVENT_NUM];

	if (!PrepareEvents(EVENT_NUM, hEvents, overlaps))
		stop = TRUE;

	if (!SetCommMask(hC0C, EV_DSR)) {
		TraceLastError("InOut(): SetCommMask()");
		stop = TRUE;
	}

	WSAEventSelect(hSock, hEvents[EVENT_CLOSE], FD_CLOSE);

	DWORD not_used;

	BYTE cbufRead[64];
	BOOL waitingRead = FALSE;

	BYTE cbufSend[64];
	int cbufSendSize = 0;
	int cbufSendDone = 0;
	BOOL waitingSend = FALSE;

	BYTE cbufRecv[64];
	BOOL waitingRecv = FALSE;

	BYTE cbufWrite[64];
	int cbufWriteSize = 0;
	int cbufWriteDone = 0;
	BOOL waitingWrite = FALSE;

	BOOL waitingStat = FALSE;
	int DSR = -1;

	while (!stop) {
		if (!waitingSend) {
			if (!cbufSendSize) {
				cbufSendSize = protocol.Read(cbufSend, sizeof(cbufSend));
				if (cbufSendSize < 0)
					break;
			}

			DWORD num = cbufSendSize - cbufSendDone;

			if (num) {
				if (!WriteFile((HANDLE)hSock, cbufSend + cbufSendDone, num, &not_used, &overlaps[EVENT_SENT])) {
					if (::GetLastError() != ERROR_IO_PENDING) {
						TraceLastError("InOut(): WriteFile(hSock)");
						break;
					}
				}
				waitingSend = TRUE;
			}
		}

		if (!waitingRead && !protocol.isSendFull()) {
			if (!ReadFile(hC0C, cbufRead, sizeof(cbufRead), &not_used, &overlaps[EVENT_READ])) {
				if (::GetLastError() != ERROR_IO_PENDING) {
					TraceLastError("InOut(): ReadFile(hC0C)");
					break;
				}
			}
			waitingRead = TRUE;
		}

		if (!waitingWrite) {
			if (!cbufWriteSize) {
				cbufWriteSize = protocol.Recv(cbufWrite, sizeof(cbufWrite));
				if (cbufWriteSize < 0)
					break;
			}

			DWORD num = cbufWriteSize - cbufWriteDone;

			if (num) {
				if (!WriteFile(hC0C, cbufWrite + cbufWriteDone, num, &not_used, &overlaps[EVENT_WRITTEN])) {
					if (::GetLastError() != ERROR_IO_PENDING) {
						TraceLastError("InOut(): WriteFile(hC0C)");
						break;
					}
				}
				waitingWrite = TRUE;
			}
		}

		if (!waitingRecv && !protocol.isWriteFull()) {
			if (!ReadFile((HANDLE)hSock, cbufRecv, sizeof(cbufRecv), &not_used, &overlaps[EVENT_RECEIVED])) {
				if (::GetLastError() != ERROR_IO_PENDING) {
					TraceLastError("InOut(): ReadFile(hSock)");
					break;
				}
			}
			waitingRecv = TRUE;
		}

		if (!waitingStat) {
			if (!WaitCommEvent(hC0C, &not_used, &overlaps[EVENT_STAT])) {
				if (::GetLastError() != ERROR_IO_PENDING) {
					TraceLastError("InOut(): WaitCommEvent()");
					break;
				}
			}
			waitingStat = TRUE;

			DWORD stat;

			if (!GetCommModemStatus(hC0C, &stat)) {
				TraceLastError("InOut(): GetCommModemStatus()");
				break;
			}

			if (!(stat & MS_DSR_ON)) {
				if (DSR != 0) {
					printf("DSR is OFF\n");
					DSR = 0;
				}
				if (!ignoreDSR) {
					if (waitingSend)
						Sleep(1000);
					break;
				}
			} else {
				if (DSR != 1) {
					printf("DSR is ON\n");
					DSR = 1;
				}
			}
		}

		if ((waitingRead || waitingSend) && (waitingRecv || waitingWrite) && waitingStat) {
			DWORD done;

			switch (WaitForMultipleObjects(EVENT_NUM, hEvents, FALSE, 5000)) {
	  case WAIT_OBJECT_0 + EVENT_READ:
		  if (!GetOverlappedResult(hC0C, &overlaps[EVENT_READ], &done, FALSE)) {
			  if (::GetLastError() != ERROR_OPERATION_ABORTED) {
				  TraceLastError("InOut(): GetOverlappedResult(EVENT_READ)");
				  stop = TRUE;
				  break;
			  }
		  }
		  ResetEvent(hEvents[EVENT_READ]);
		  waitingRead = FALSE;
		  protocol.Send(cbufRead, done);
		  break;
	  case WAIT_OBJECT_0 + EVENT_SENT:
		  if (!GetOverlappedResult((HANDLE)hSock, &overlaps[EVENT_SENT], &done, FALSE)) {
			  if (::GetLastError() != ERROR_OPERATION_ABORTED) {
				  TraceLastError("InOut(): GetOverlappedResult(EVENT_SENT)");
				  stop = TRUE;
				  break;
			  }
			  done = 0;
		  }
		  ResetEvent(hEvents[EVENT_SENT]);
		  cbufSendDone += done;
		  if (cbufSendDone >= cbufSendSize)
			  cbufSendDone = cbufSendSize = 0;
		  waitingSend = FALSE;
		  break;
	  case WAIT_OBJECT_0 + EVENT_RECEIVED:
		  if (!GetOverlappedResult((HANDLE)hSock, &overlaps[EVENT_RECEIVED], &done, FALSE)) {
			  if (::GetLastError() != ERROR_OPERATION_ABORTED) {
				  TraceLastError("InOut(): GetOverlappedResult(EVENT_RECEIVED)");
				  stop = TRUE;
				  break;
			  }
			  done = 0;
		  } else if (!done) {
			  ResetEvent(hEvents[EVENT_RECEIVED]);
			  printf("Received EOF\n");
			  break;
		  }
		  ResetEvent(hEvents[EVENT_RECEIVED]);
		  waitingRecv = FALSE;
		  protocol.Write(cbufRecv, done);
		  break;
	  case WAIT_OBJECT_0 + EVENT_WRITTEN:
		  if (!GetOverlappedResult(hC0C, &overlaps[EVENT_WRITTEN], &done, FALSE)) {
			  if (::GetLastError() != ERROR_OPERATION_ABORTED) {
				  TraceLastError("InOut(): GetOverlappedResult(EVENT_WRITTEN)");
				  stop = TRUE;
				  break;
			  }
			  done = 0;
		  }
		  ResetEvent(hEvents[EVENT_WRITTEN]);
		  cbufWriteDone += done;
		  if (cbufWriteDone >= cbufWriteSize)
			  cbufWriteDone = cbufWriteSize = 0;
		  waitingWrite = FALSE;
		  break;
	  case WAIT_OBJECT_0 + EVENT_STAT:
		  if (!GetOverlappedResult(hC0C, &overlaps[EVENT_STAT], &done, FALSE)) {
			  if (::GetLastError() != ERROR_OPERATION_ABORTED) {
				  TraceLastError("InOut(): GetOverlappedResult(EVENT_STAT)");
				  stop = TRUE;
				  break;
			  }
		  }
		  waitingStat = FALSE;
		  break;
	  case WAIT_OBJECT_0 + EVENT_CLOSE:
		  ResetEvent(hEvents[EVENT_CLOSE]);
		  printf("EVENT_CLOSE\n");
		  if (waitingWrite)
			  Sleep(1000);
		  stop = TRUE;
		  break;
	  case WAIT_TIMEOUT:
		  break;
	  default:
		  TraceLastError("InOut(): WaitForMultipleObjects()");
		  stop = TRUE;
			}
		}
	}

	CancelIo(hC0C);
	CancelIo((HANDLE)hSock);


	CloseEvents(EVENT_NUM, hEvents);

	printf("InOut() - STOP\n");
}