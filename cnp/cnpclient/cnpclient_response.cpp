#include "CNP_Protocol1.h"
#include "endianness.h"
#include <assert.h>
#include <stdlib.h>
using namespace cnp;

DWORD parse_response(char * bytes, int len){
	struct CNP_STD_HDR * cth = (struct CNP_STD_HDR *)bytes;
	DWORD messagetype;
	if(!ISBIGENDIAN){
		messagetype = swap32(cth->m_dwMsgType);
	}else{ 
		messagetype = cth->m_dwMsgType;
	}

	return messagetype;
}

void parse_header(struct CNP_STD_HDR * csh){
	csh->m_dwContext = swap32(csh->m_dwContext);
	csh->m_dwMsgType = swap32(csh->m_dwMsgType);
	csh->m_wClientID = swap16(csh->m_wClientID);
	csh->m_wDataLen = swap16(csh->m_wDataLen);
}

struct CNP_CONNECT_RESPONSE * parse_connect(char * bytes, int len){
	assert(sizeof(struct CNP_CONNECT_RESPONSE)  == len);
	struct CNP_CONNECT_RESPONSE * iptrccr = (struct CNP_CONNECT_RESPONSE *)malloc(sizeof(struct CNP_CONNECT_RESPONSE));
	memcpy(iptrccr, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrccr->m_Hdr);
		iptrccr->m_Response.m_dwResult = swap32(iptrccr->m_Response.m_dwResult);
		iptrccr->m_Response.m_wClientID = swap16(iptrccr->m_Response.m_wClientID);
		iptrccr->m_Response.m_wMajorVersion = swap16(iptrccr->m_Response.m_wMajorVersion);
		iptrccr->m_Response.m_wMinorVersion = swap16(iptrccr->m_Response.m_wMinorVersion);
	}

	return iptrccr;
}

struct CNP_LOGON_RESPONSE * parse_logon(char * bytes, int len){
	assert(sizeof(struct CNP_LOGON_RESPONSE) == len);
	struct CNP_LOGON_RESPONSE * iptrclr = (struct CNP_LOGON_RESPONSE *)malloc(sizeof(struct CNP_LOGON_RESPONSE));
	memcpy(iptrclr, bytes, len);
	if (!ISBIGENDIAN) {
		parse_header(&iptrclr->m_Hdr);
		iptrclr->m_Response.m_dwResult= swap32(iptrclr->m_Response.m_dwResult);
	}

	return iptrclr;
}

struct CNP_CREATE_ACCOUNT_RESPONSE * parse_createaccount(char * bytes, int len){
	assert(sizeof(struct CNP_CREATE_ACCOUNT_RESPONSE) == len);
	struct CNP_CREATE_ACCOUNT_RESPONSE * iptrccar = (struct CNP_CREATE_ACCOUNT_RESPONSE *) malloc(sizeof(struct CNP_CREATE_ACCOUNT_RESPONSE));
	memcpy(iptrccar, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrccar->m_Hdr);
		iptrccar->m_Response.m_dwResult = swap32(iptrccar->m_Response.m_dwResult);
	}

	return iptrccar;
}

struct CNP_DEPOSIT_RESPONSE * parse_deposit(char * bytes, int len){
	assert(sizeof(struct CNP_DEPOSIT_RESPONSE) == len);
	struct CNP_DEPOSIT_RESPONSE * iptrcdr = (struct CNP_DEPOSIT_RESPONSE *)malloc(sizeof(struct CNP_DEPOSIT_RESPONSE));
	memcpy(iptrcdr, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrcdr->m_Hdr);
		iptrcdr->m_Response.m_dwResult = swap32(iptrcdr->m_Response.m_dwResult);
	}

	return iptrcdr;
}

struct CNP_WITHDRAWAL_RESPONSE * parse_withdrawal(char * bytes, int len){
	assert(sizeof(struct CNP_WITHDRAWAL_RESPONSE) == len);
	struct CNP_WITHDRAWAL_RESPONSE * iptrcwr = (struct CNP_WITHDRAWAL_RESPONSE *)malloc(sizeof(struct CNP_WITHDRAWAL_RESPONSE));
	memcpy(iptrcwr, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrcwr->m_Hdr);
		iptrcwr->m_Response.m_dwResult = swap32(iptrcwr->m_Response.m_dwResult);
	}

	return iptrcwr;
}

struct CNP_TRANSACTION_QUERY_RESPONSE * parse_transaction(char * bytes, int len){
	assert(sizeof(struct CNP_TRANSACTION_QUERY_RESPONSE) == len);
	struct CNP_TRANSACTION_QUERY_RESPONSE * iptrctqr = (struct CNP_TRANSACTION_QUERY_RESPONSE *)malloc(sizeof(struct CNP_TRANSACTION_QUERY_RESPONSE));
	memcpy(iptrctqr, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrctqr->m_Hdr);
		iptrctqr->m_Response.m_dwResult = swap32(iptrctqr->m_Response.m_dwResult);
		iptrctqr->m_Response.m_wTransactionCount = swap16(iptrctqr->m_Response.m_wTransactionCount);
		for(int i = 0; i < iptrctqr->m_Response.m_wTransactionCount; ++i){
			iptrctqr->m_Response.m_rgTransactions[i].m_dwAmount = swap32(iptrctqr->m_Response.m_rgTransactions[i].m_dwAmount);
			iptrctqr->m_Response.m_rgTransactions[i].m_dwID = swap32(iptrctqr->m_Response.m_rgTransactions[i].m_dwID);
			iptrctqr->m_Response.m_rgTransactions[i].m_qwDateTime = swap64(iptrctqr->m_Response.m_rgTransactions[i].m_qwDateTime);
			iptrctqr->m_Response.m_rgTransactions[i].m_wType = swap16(iptrctqr->m_Response.m_rgTransactions[i].m_wType);
		}
	}

	return iptrctqr;
}

struct CNP_LOGOFF_RESPONSE * parse_logoff(char * bytes, int len){
	assert(sizeof(struct CNP_LOGOFF_RESPONSE) == len);
	struct CNP_LOGOFF_RESPONSE * iptrclr = (struct CNP_LOGOFF_RESPONSE * )malloc(sizeof(struct CNP_LOGOFF_RESPONSE));
	memcpy(iptrclr, bytes, len);
	if(!ISBIGENDIAN){
		parse_header(&iptrclr->m_Hdr);
		iptrclr->m_Response.m_dwResult = swap32(iptrclr->m_Response.m_dwResult);
	}

	return iptrclr;
}