
#include "protocol_tt.h"
#include "utils.h"
#include "protocol_common.h"
#include "bytebuffer.h"

TTProtocol::TTProtocol( int _thresholdSend /*= 0*/, int _thresholdWrite /*= 0*/ ):
Protocol(_thresholdSend, _thresholdWrite) { 
	Clean();
	m_serial_id =0;
	m_send_buf = 0;
	m_send_buf_count = 0;
}

int TTProtocol::Write( const void *pBuf, int count )
{ 
	WriteRaw(pBuf, count);
	return count;
}

int TTProtocol::Send( const void *pBuf, int count )
{ 
//	unsigned int encode_count = count + PROTOCOL_COMMON_LEN;
//	if(encode_count > m_send_buf_count){
//		m_send_buf = (unsigned char *)realloc(m_send_buf,encode_count);
//		m_send_buf_count = encode_count;
//	}
//
//	unsigned char * p = m_send_buf;
//	protocol_common_write_header(&p, PROTOCOL_TRANSPARENT_TRANSMISSION, 0, m_id, m_serial_id);
//	bytebuffer_writebytes(&p, (unsigned char *)pBuf, count);
//	bytebuffer_writelength(m_send_buf, p - m_send_buf + 3);
//	bytebuffer_writeword(&p, CRC(m_send_buf, p - m_send_buf));
//	bytebuffer_writebyte(&p, PROTOCOL_END_FLAG);
//
//	SendRaw(m_send_buf, p-m_send_buf);
//	m_serial_id++;
//
//	return m_send_buf_count;
	SendRaw(pBuf, count);

	return count;
}

