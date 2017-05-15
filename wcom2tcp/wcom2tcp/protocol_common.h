#ifndef __PROTOCOL_COMMON_H_H_
#define __PROTOCOL_COMMON_H_H_

#define PROTOCOL_MAX_LEN 1018
#define PROTOCOL_BEGIN_FLAG 0x55
#define PROTOCOL_END_FLAG 0xaa

#define PROTOCOL_REQ_TRANSPARENT_TRANSMISSION 0x8082
#define PROTOCOL_REP_TRANSPARENT_TRANSMISSION 0x0082

#define PROTOCOL_REQ_RELEASE_TRANSPARENT_TRANSMISSION 0x8083
#define PROTOCOL_REP_RELEASE_TRANSPARENT_TRANSMISSION 0x0083

#define PROTOCOL_TRANSPARENT_TRANSMISSION  0x0084

#define PROTOCOL_TT_FEEDBACK_LEN PROTOCOL_COMMON_LEN + 5

#define PROTOCOL_COMMON_LEN 18

#define PROTOCOL_DATA_POS 15
#define PROTOCOL_ID_POS 5
#define PROTOCOL_SERIAL_ID_LEN 2
#define PROTOCOL_CPU_ID_LEN 20
#define PROTOCOL_REST_LEN 3

unsigned long CRC_ISO13239(unsigned char *buffer, unsigned int len); 
unsigned long CRC(unsigned char *buffer, unsigned int len); 

void protocol_common_read_id_and_serial(const unsigned char ** src, unsigned long long *tid, unsigned short *serial_id);

void protocol_common_write_header (unsigned char ** src, unsigned short protocol_id, unsigned short protocol_len, unsigned long long tid, unsigned serial);

///////////////////////////////////////////
struct protocol_register{
	unsigned long long id;
	unsigned short serial_id;
	unsigned long long router_id;
	unsigned short key;
};

struct protocol_cancel{ 
    unsigned long long id;
    unsigned short serial_id;
};

unsigned short encode_protocol_register(unsigned char * dst, struct protocol_register * reg);

unsigned short encode_protocol_cancel(unsigned char * dst, struct protocol_cancel * cancel);

unsigned char parse_tt_feedback(unsigned char * register_feedback); 

#endif
