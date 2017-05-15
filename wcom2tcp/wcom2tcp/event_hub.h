#ifndef __EVENT_HUB_H_H_
#define __EVENT_HUB_H_H_
void InOut(
				  HANDLE hC0C,
				  SOCKET hSock,
				  Protocol &protocol,
				  BOOL ignoreDSR,
				  SOCKET hSockListen = INVALID_SOCKET);
#endif