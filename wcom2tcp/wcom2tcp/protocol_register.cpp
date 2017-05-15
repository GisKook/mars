#include "protocol_common.h"
#include "bytebuffer.h"

unsigned short encode_protocol_register(unsigned char * dst, struct protocol_register * reg){ 
    unsigned char * p = dst;
	protocol_common_write_header (&p, PROTOCOL_REQ_TRANSPARENT_TRANSMISSION, 0, reg->id, reg->serial_id); 
    bytebuffer_writequadword(&p, reg->router_id);
	bytebuffer_writedword(&p, reg->key);
    bytebuffer_writelength(dst, p - dst + 3);

    unsigned short crc = CRC(dst, p-dst);
	bytebuffer_writeword(&p, crc);
	bytebuffer_writebyte(&p, PROTOCOL_END_FLAG);

	return p-dst;
}

unsigned char parse_tt_feedback(unsigned char * register_feedback){ 
	const unsigned char * p = register_feedback;
	unsigned long long id;
	unsigned short serial_id;
	protocol_common_read_id_and_serial(&p , &id, &serial_id);
	unsigned char result;
	unsigned int reserved;
	bytebuffer_readbyte(&p, &result);
	bytebuffer_readdword(&p, &reserved);

	return result;
}
