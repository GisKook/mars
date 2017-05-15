#include "bytebuffer.h"
#include "protocol_common.h"

#define POLYNOMIAL 0x8772
#define PRESET_VALUE 0xFFFF
#define CHECK_VALUE 0xF0B8
unsigned long CRC_ISO13239(unsigned char *buffer, unsigned int Len){ 
	unsigned int i,j;
	unsigned int current_crc_value;

	current_crc_value=PRESET_VALUE;
	for(i=0;i<Len;i++)
	{
		current_crc_value=current_crc_value^((unsigned int)buffer[i]);
		for(j=0;j<8;j++)
		{
			if(current_crc_value&0x0001)
			{
				current_crc_value=(current_crc_value>>1)^POLYNOMIAL;
			}
			else
			{
				current_crc_value=(current_crc_value>>1);
			}		
		}	 
	}

	return (~current_crc_value)&0xFFFF;

}

unsigned long CRC(unsigned char * buffer, unsigned int len){
	return CRC_ISO13239(buffer+1, len-1);
}

void protocol_common_read_id_and_serial(const unsigned char ** src, unsigned long long *tid, unsigned short *serial_id){
	bytebuffer_skipbytes(&(*src), PROTOCOL_ID_POS);
	unsigned long long id = 0;
	bytebuffer_readquadword(&(*src), tid);
	bytebuffer_readword(&(*src), serial_id);
}

void protocol_common_write_header (unsigned char ** src, unsigned short protocol_id, unsigned short protocol_len, unsigned long long tid, unsigned serial){
	bytebuffer_writebyte(src, PROTOCOL_BEGIN_FLAG);
	bytebuffer_writeword(src, protocol_len);
	bytebuffer_writeword(src, protocol_id);
	bytebuffer_writequadword(src, tid);
	bytebuffer_writeword(src, serial);
}