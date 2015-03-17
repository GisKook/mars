#include "CNP_Protocol1.h"
#include "endianness.h"
#include <stdlib.h>

using namespace cnp;

void encode_header(struct CNP_STD_HDR * csh, struct CNP_STD_HDR * refercsh){
	csh->m_dwContext = swap32(refercsh->m_dwContext);
	csh->m_dwMsgType = swap32(refercsh->m_dwMsgType);
	csh->m_wClientID = swap16(refercsh->m_wClientID);
	csh->m_wDataLen = swap16(refercsh->m_wDataLen);
}

char * encode_createaccount(struct CNP_CREATE_ACCOUNT_REQUEST * ccar){
	struct CNP_CREATE_ACCOUNT_REQUEST * iptrccar = (struct CNP_CREATE_ACCOUNT_REQUEST * )malloc(sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));
	memset(iptrccar, 0, sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));
	if(!ISBIGENDIAN){ 
		encode_header(&iptrccar->m_Hdr, &ccar->m_Hdr);
		iptrccar->m_Request.m_dwDLNumber = swap32(ccar->m_Request.m_dwDLNumber);
		iptrccar->m_Request.m_dwSSNumber = swap32(ccar->m_Request.m_dwSSNumber);
		iptrccar->m_Request.m_wPIN = swap16(ccar->m_Request.m_wPIN);
		iptrccar->m_Request.set_FirstName(ccar->m_Request.m_szFirstName);
		iptrccar->m_Request.set_LastName(ccar->m_Request.m_szLastName);
	}else{
		memcpy(iptrccar, ccar, sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));
	}
	
	return (char *)iptrccar;
}

char * encode_logon(struct CNP_LOGON_REQUEST * clr){
	struct CNP_LOGON_REQUEST * iptrclr = (struct CNP_LOGON_REQUEST*)malloc(sizeof(struct CNP_LOGON_REQUEST));
	memset(iptrclr, 0, sizeof(struct CNP_LOGON_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrclr->m_Hdr, &clr->m_Hdr);
		iptrclr->m_Request.set_FirstName(clr->m_Request.m_szFirstName);
		iptrclr->m_Request.m_wPIN = swap16(clr->m_Request.m_wPIN);
	}else{
		memcpy(iptrclr, clr, sizeof(struct CNP_LOGON_REQUEST));
	}

	return (char *)iptrclr;
}

char * encode_deposit(struct CNP_DEPOSIT_REQUEST * cdr){
	struct CNP_DEPOSIT_REQUEST * iptrcdr = (struct CNP_DEPOSIT_REQUEST *)malloc(sizeof(struct CNP_DEPOSIT_REQUEST));
	memset(iptrcdr, 0, sizeof(struct CNP_DEPOSIT_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrcdr->m_Hdr, &cdr->m_Hdr);
		iptrcdr->m_Request.m_dwAmount = swap32(cdr->m_Request.m_dwAmount);
		iptrcdr->m_Request.m_wType = swap16(cdr->m_Request.m_wType);
	}else{
		memcpy(iptrcdr, cdr, sizeof(struct CNP_DEPOSIT_REQUEST)); 
	}

	return (char *)iptrcdr;
}

char * encode_withdraw(struct CNP_WITHDRAWAL_REQUEST * cwr){
	struct CNP_WITHDRAWAL_REQUEST * iptrcwr = (struct CNP_WITHDRAWAL_REQUEST *)malloc(sizeof(struct CNP_WITHDRAWAL_REQUEST));
	memset(iptrcwr, 0, sizeof(struct CNP_WITHDRAWAL_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrcwr->m_Hdr, &cwr->m_Hdr);
		iptrcwr->m_Request.m_dwAmount = swap32(cwr->m_Request.m_dwAmount);
	}else{
		memcpy(iptrcwr, cwr, sizeof(struct CNP_WITHDRAWAL_REQUEST)); 
	}
	
	return (char *)iptrcwr;
}

char * encode_balance(struct CNP_BALANCE_QUERY_REQUEST * cbqr){
	struct CNP_BALANCE_QUERY_REQUEST * iptrcbqr = (struct CNP_BALANCE_QUERY_REQUEST *)malloc(sizeof(struct CNP_BALANCE_QUERY_REQUEST));
	memset(iptrcbqr, 0, sizeof(struct CNP_BALANCE_QUERY_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrcbqr->m_Hdr, &cbqr->m_Hdr);
	}else{
		memcpy(iptrcbqr, cbqr, sizeof(struct CNP_BALANCE_QUERY_REQUEST));
	}

	return (char *)iptrcbqr;
}

char * encode_transaction(struct CNP_TRANSACTION_QUERY_REQUEST * ctqr){
	struct CNP_TRANSACTION_QUERY_REQUEST * iptrctqr = (struct CNP_TRANSACTION_QUERY_REQUEST *)malloc(sizeof(struct CNP_TRANSACTION_QUERY_REQUEST));
	memset(iptrctqr, 0, sizeof(struct CNP_TRANSACTION_QUERY_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrctqr->m_Hdr, &ctqr->m_Hdr);
		iptrctqr->m_Request.m_dwStartID = swap32(ctqr->m_Request.m_dwStartID);
		iptrctqr->m_Request.m_wTransactionCount = swap16(ctqr->m_Request.m_wTransactionCount);
	}else{
		memcpy(iptrctqr, ctqr, sizeof(struct CNP_TRANSACTION_QUERY_REQUEST));
	}

	return (char *)iptrctqr;
}

char * encode_connect(struct CNP_CONNECT_REQUEST * ccr){
	struct CNP_CONNECT_REQUEST * iptrccr = (struct CNP_CONNECT_REQUEST *)malloc(sizeof(struct CNP_CONNECT_REQUEST));
	memset(iptrccr, 0, sizeof(struct CNP_CONNECT_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrccr->m_Hdr, &ccr->m_Hdr);
		iptrccr->m_Request.m_dwValidationKey = swap32(&ccr->m_Request.m_dwValidationKey);
	}else{
		memcpy(iptrccr, ccr, sizeof(struct CNP_CONNECT_REQUEST));
	}

	return (char *)iptrccr;
}

char * encode_logoff(struct CNP_LOGOFF_REQUEST * clr){
	struct CNP_LOGOFF_REQUEST * iptrclr = (struct CNP_LOGOFF_REQUEST *)malloc(sizeof(struct CNP_LOGOFF_REQUEST));
	memset(iptrclr, 0, sizeof(struct CNP_LOGOFF_REQUEST));
	if(!ISBIGENDIAN){
		encode_header(&iptrclr->m_Hdr, &clr->m_Hdr);
	}else{
		memcpy(iptrclr, clr, sizeof(struct CNP_LOGOFF_REQUEST));
	}

	return (char *)iptrclr;
}