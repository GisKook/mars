#include "serial.h"

void TraceLastError(const char *pFmt, ...) {
	DWORD err = GetLastError();
	va_list va;
	va_start(va, pFmt);
	vfprintf(stderr, pFmt, va);
	va_end(va);

	fprintf(stderr, " ERROR %s (%lu)\n", strerror(err), (unsigned long)err);
}

BOOL myGetCommState(HANDLE hC0C, DCB *dcb) {
  dcb->DCBlength = sizeof(*dcb);

  if (!GetCommState(hC0C, dcb)) {
    TraceLastError("GetCommState()");
    return FALSE;
  }
  return TRUE;
}

BOOL mySetCommState(HANDLE hC0C, DCB *dcb)
{
  if (!SetCommState(hC0C, dcb)) {
    TraceLastError("SetCommState()");
    return FALSE;
  }
  return TRUE;
}

HANDLE OpenC0C(const char *pPath, const ComParams &comParams) {
	HANDLE hC0C = CreateFile(pPath,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL);

	if (hC0C == INVALID_HANDLE_VALUE) {
		TraceLastError("OpenC0C(): CreateFile(\"%s\")", pPath);
		return INVALID_HANDLE_VALUE;
	}

	DCB dcb;

	if (!myGetCommState(hC0C, &dcb)) {
		CloseHandle(hC0C);
		return INVALID_HANDLE_VALUE;
	}

	if (comParams.BaudRate() > 0)
		dcb.BaudRate = (DWORD)comParams.BaudRate();

	if (comParams.ByteSize() > 0)
		dcb.ByteSize = (BYTE)comParams.ByteSize();

	if (comParams.Parity() >= 0)
		dcb.Parity = (BYTE)comParams.Parity();

	if (comParams.StopBits() >= 0)
		dcb.StopBits = (BYTE)comParams.StopBits();

	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDsrSensitivity = !comParams.IgnoreDSR();
	dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	dcb.fDtrControl = comParams.ConnectDTR() ? DTR_CONTROL_DISABLE : DTR_CONTROL_ENABLE;
	dcb.fOutX = FALSE;
	dcb.fInX = TRUE;
	dcb.XonChar = 0x11;
	dcb.XoffChar = 0x13;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fParity = FALSE;
	dcb.fNull = FALSE;
	dcb.fAbortOnError = FALSE;
	dcb.fErrorChar = FALSE;

	if (!mySetCommState(hC0C, &dcb)) {
		CloseHandle(hC0C);
		return INVALID_HANDLE_VALUE;
	}

	COMMTIMEOUTS timeouts;

	if (!GetCommTimeouts(hC0C, &timeouts)) {
		TraceLastError("OpenC0C(): GetCommTimeouts()");
		CloseHandle(hC0C);
		return INVALID_HANDLE_VALUE;
	}

	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = MAXDWORD - 1;
	timeouts.ReadIntervalTimeout = MAXDWORD;

	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;

	if (!SetCommTimeouts(hC0C, &timeouts)) {
		TraceLastError("OpenC0C(): SetCommTimeouts()");
		CloseHandle(hC0C);
		return INVALID_HANDLE_VALUE;
	}

	printf("OpenC0C(\"%s\", baud=%ld, data=%ld, parity=%s, stop=%s) - OK\n",
		pPath,
		(long)dcb.BaudRate,
		(long)dcb.ByteSize,
		ComParams::ParityStr(dcb.Parity),
		ComParams::StopBitsStr(dcb.StopBits));

	return hC0C;
}
