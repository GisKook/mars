#ifndef __SERIAL_H_H__
#define __SERIAL_H_H__
#include "precomp.h"

BOOL myGetCommState(HANDLE hC0C, DCB *dcb);
HANDLE OpenC0C(const char *pPath, const ComParams &comParams);
BOOL mySetCommState(HANDLE hC0C, DCB *dcb);

#endif