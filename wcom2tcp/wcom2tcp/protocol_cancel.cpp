#include "protocol_common.h"

unsigned short encode_protocol_register(unsigned char * dst, struct protocol_cancel * cancel){ 
    unsigned char * p = dst;
	protocol_common_write_header (&p, PROTOCOL_REQ_RELEASE_TRANSPARENT_TRANSMISSION, 0, reg->id, regiser->serial_id); 
    bytebuffer_writelength(&p, p - dst + 3);

    unsigned short crc = CRC(dst, p-dst);
	bytebuffer_writeword(&p, crc);
	bytebuffer_writebyte(&p, PROTOCOL_END_FLAG);

	return p-dst;
}
