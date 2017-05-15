#include "socket.h"

static const char *pProtoName = "tcp";

static BOOL SetAddr(struct sockaddr_in &sn, const char *pAddr, const char *pPort) {
  memset(&sn, 0, sizeof(sn));
  sn.sin_family = AF_INET;

  if (pPort) {
    struct servent *pServEnt;

    pServEnt = getservbyname(pPort, pProtoName);

    sn.sin_port = pServEnt ? pServEnt->s_port : htons((u_short)atoi(pPort));
  }

  sn.sin_addr.s_addr = pAddr ? inet_addr(pAddr) : INADDR_ANY;

  if (sn.sin_addr.s_addr == INADDR_NONE) {
    const struct hostent *pHostEnt = gethostbyname(pAddr);

    if (!pHostEnt) {
      TraceLastError("SetAddr(): gethostbyname(\"%s\")", pAddr);
      return FALSE;
    }

    memcpy(&sn.sin_addr, pHostEnt->h_addr, pHostEnt->h_length);
  }
  return TRUE;
}

static SOCKET Socket(
    const char *pIF,
    const char *pPort = NULL)
{
  const struct protoent *pProtoEnt;

  pProtoEnt = getprotobyname(pProtoName);

  if (!pProtoEnt) {
    TraceLastError("Socket(): getprotobyname(\"%s\")", pProtoName);
    return INVALID_SOCKET;
  }

  SOCKET hSock = socket(AF_INET, SOCK_STREAM, pProtoEnt->p_proto);

  if (hSock == INVALID_SOCKET) {
    TraceLastError("Socket(): socket()");
    return INVALID_SOCKET;
  }

  if (pIF || pPort) {
    struct sockaddr_in sn;

    if (!SetAddr(sn, pIF, pPort))
      return INVALID_SOCKET;

    if (bind(hSock, (struct sockaddr *)&sn, sizeof(sn)) == SOCKET_ERROR) {
      TraceLastError("Socket(): bind(\"%s\", \"%s\")", pIF, pPort);
      closesocket(hSock);
      return INVALID_SOCKET;
    }
  }

  return hSock;
}

void Disconnect(SOCKET hSock)
{
  if (shutdown(hSock, SD_BOTH) != 0)
    TraceLastError("Disconnect(): shutdown()");

  if (closesocket(hSock) != 0)
    TraceLastError("Disconnect(): closesocket()");

  printf("Disconnect() - OK\n");
}

SOCKET Connect(
    const char *pIF,
    const char *pAddr,
    const char *pPort)
{
  struct sockaddr_in sn;

  if (!SetAddr(sn, pAddr, pPort))
    return INVALID_SOCKET;

  SOCKET hSock = Socket(pIF);

  if (hSock == INVALID_SOCKET)
    return INVALID_SOCKET;

  if (connect(hSock, (struct sockaddr *)&sn, sizeof(sn)) == SOCKET_ERROR) {
    TraceLastError("Connect(): connect(\"%s\", \"%s\")", pAddr, pPort);
    closesocket(hSock);
    return INVALID_SOCKET;
  }

  printf("Connect(\"%s\", \"%s\") - OK\n", pAddr, pPort);

  return hSock;
}