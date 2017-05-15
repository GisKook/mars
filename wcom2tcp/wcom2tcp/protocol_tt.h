#ifndef __PROTOCOL_TT_H_H__
#define __PROTOCOL_TT_H_H__
#include "utils.h"
#include "kfifo.h"
class TTProtocol:public Protocol{
public:
	TTProtocol(int _thresholdSend = 0, int _thresholdWrite = 0);

	virtual int Write(const void *pBuf, int count);
	virtual int Send(const void *pBuf, int count);
	
	inline void SetID(unsigned long long id){m_id = id;}
	inline void SetSerialID(unsigned long long serial_id){m_serial_id = serial_id;}
private:
	unsigned long long m_id;
	unsigned short m_serial_id;

private:
	struct kfifo * m_fifo; 
	unsigned char m_fifo_buf[4096];

private:
	unsigned char * m_send_buf;
	unsigned int m_send_buf_count;
};
#endif