#ifndef __SOCKET_H_H__
#define __SOCKET_H_H__

#include "precomp.h"

SOCKET Connect( const char *pIF, const char *pAddr, const char *pPort);

void Disconnect(SOCKET hSock);

#endif