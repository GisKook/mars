#include "CNP_Protocol1.h"
#include "endianness.h"
#include <stdlib.h>

using namespace cnp;

char * encode_createaccount(struct CNP_CREATE_ACCOUNT_REQUEST * ccar){
	struct CNP_CREATE_ACCOUNT_REQUEST * iptrccar = (struct CNP_CREATE_ACCOUNT_REQUEST * )malloc(sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));
	memset(iptrccar, 0, sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));
	if(!ISBIGENDIAN){
		iptrccar->m_Hdr.m_dwContext = swap32(ccar->m_Hdr.m_dwContext);
		iptrccar->m_Hdr.m_dwMsgType = swap32(ccar->m_Hdr.m_dwMsgType);
		iptrccar->m_Hdr.m_wClientID = swap16(ccar->m_Hdr.m_wClientID);
		iptrccar->m_Hdr.m_wDataLen = swap16(ccar->m_Hdr.m_wDataLen);
		iptrccar->m_Request.m_dwDLNumber = swap32(ccar->m_Request.m_dwDLNumber);
		iptrccar->m_Request.m_dwSSNumber = swap32(ccar->m_Request.m_dwSSNumber);
		iptrccar->m_Request.m_wPIN = swap16(ccar->m_Request.m_wPIN);
		iptrccar->m_Request.set_FirstName(ccar->m_Request.m_szFirstName);
		iptrccar->m_Request.set_LastName(ccar->m_Request.m_szLastName);
	}
	memcpy(iptrccar, ccar, sizeof(struct CNP_CREATE_ACCOUNT_REQUEST));

	return (char *)iptrccar;
}