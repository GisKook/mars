/******************************************/
/**
  @file   CNP_Protocal.h
*/
/******************************************/


#ifndef _CNP_PROTOCOL_H__
#define _CNP_PROTOCOL_H__

#include <string.h>

// set structure alignment to 1 byte
#pragma pack(push, 1)

namespace cnp
{
    typedef unsigned short      WORD;
    typedef unsigned int        DWORD;
    typedef unsigned long long  QWORD;

#ifndef COUNTOF
    #define COUNTOF(_array)  (sizeof(_array) / sizeof(_array[0]))
#endif

#ifndef MAKE_CNP_MSG_TYPE
    #define   MAKE_CNP_MSG_TYPE(type, sub) ((sub << 16) + type)
#endif


// ============== const definitions =====================

/// CNP Protocol version
 const WORD g_wMajorVersion = 1;
 const WORD g_wMinorVersion = 0;

/// [first,last] name field lengths
/**
    @sa _CREATE_ACCOUNT_REQUEST, _LOGON_REQUEST
*/
 const size_t MAX_NAME_LEN     = 32;

 /// Used for error checking & default initialization
 const WORD   INVALID_CLIENT_ID = (~0);

/// Supported CNP Message Types
enum CNP_MESSAGE_TYPE
{
    CMT_INVALID           = 0x00,  ///< used for initialization and error checking
    CMT_CONNECT           = 0x50,
    CMT_CREATE_ACCOUNT    = 0x51,
    CMT_LOGON             = 0x52,
    CMT_LOGOFF            = 0x53,
    CMT_DEPOSIT           = 0x54,
    CMT_WITHDRAWAL        = 0x55,
    CMT_BALANCE_QUERY     = 0x56,
    CMT_TRANSACTION_QUERY = 0x57,
    CMT_PURCHASE_STAMPS   = 0x58
};

/// Supported CNP Message Subtypes
enum CNP_MESSAGE_SUBTYPE
{
    CMS_INVALID           = 0x00,
    CMS_REQUEST           = 0x01,
    CMS_RESPONSE          = 0x02
};

// Constructed Message Type IDs
const DWORD CNP_INVALID_ID                       = MAKE_CNP_MSG_TYPE(CMT_INVALID, CMS_INVALID);

const DWORD CNP_CONNECT_REQUEST_ID               = MAKE_CNP_MSG_TYPE(CMT_CONNECT, CMS_REQUEST);
const DWORD CNP_CONNECT_RESPONSE_ID              = MAKE_CNP_MSG_TYPE(CMT_CONNECT, CMS_RESPONSE);

const DWORD CNP_CREATE_ACCOUNT_REQUEST_ID        = MAKE_CNP_MSG_TYPE(CMT_CREATE_ACCOUNT, CMS_REQUEST);
const DWORD CNP_CREATE_ACCOUNT_RESPONSE_ID       = MAKE_CNP_MSG_TYPE(CMT_CREATE_ACCOUNT, CMS_RESPONSE);

const DWORD CNP_LOGON_REQUEST_ID                 = MAKE_CNP_MSG_TYPE(CMT_LOGON, CMS_REQUEST);
const DWORD CNP_LOGON_RESPONSE_ID                = MAKE_CNP_MSG_TYPE(CMT_LOGON, CMS_RESPONSE);

const DWORD CNP_LOGOFF_REQUEST_ID                = MAKE_CNP_MSG_TYPE(CMT_LOGOFF, CMS_REQUEST);
const DWORD CNP_LOGOFF_RESPONSE_ID               = MAKE_CNP_MSG_TYPE(CMT_LOGOFF, CMS_RESPONSE);

const DWORD CNP_DEPOSIT_REQUEST_ID               = MAKE_CNP_MSG_TYPE(CMT_DEPOSIT, CMS_REQUEST);
const DWORD CNP_DEPOSIT_RESPONSE_ID              = MAKE_CNP_MSG_TYPE(CMT_DEPOSIT, CMS_RESPONSE);

const DWORD CNP_WITHDRAWAL_REQUEST_ID            = MAKE_CNP_MSG_TYPE(CMT_WITHDRAWAL, CMS_REQUEST);
const DWORD CNP_WITHDRAWAL_RESPONSE_ID           = MAKE_CNP_MSG_TYPE(CMT_WITHDRAWAL, CMS_RESPONSE);

const DWORD CNP_BALANCE_QUERY_REQUEST_ID         = MAKE_CNP_MSG_TYPE(CMT_BALANCE_QUERY, CMS_REQUEST);
const DWORD CNP_BALANCE_QUERY_RESPONSE_ID        = MAKE_CNP_MSG_TYPE(CMT_BALANCE_QUERY, CMS_RESPONSE);

const DWORD CNP_TRANSACTION_QUERY_REQUEST_ID     = MAKE_CNP_MSG_TYPE(CMT_TRANSACTION_QUERY, CMS_REQUEST);
const DWORD CNP_TRANSACTION_QUERY_RESPONSE_ID    = MAKE_CNP_MSG_TYPE(CMT_TRANSACTION_QUERY, CMS_RESPONSE);

const DWORD CNP_PURCHASE_STAMPS_REQUEST_ID       = MAKE_CNP_MSG_TYPE(CMT_PURCHASE_STAMPS, CMS_REQUEST);
const DWORD CNP_PURCHASE_STAMES_RESPONSE_ID      = MAKE_CNP_MSG_TYPE(CMT_PURCHASE_STAMPS, CMS_RESPONSE);


/// =============================== CNP Message Primitives =======================================
enum DEPOSIT_TYPE
{
    DT_INVALID = 0,       ///< for initialization and error checking
    DT_CASH    = 0x01,
    DT_CHECK   = 0x02
};

enum TRANSACTION_TYPE
{
    TT_INVALID    = 0,     ///< for initialization and error checking
    TT_DEPOSIT    = 0x01,
    TT_WITHDRAWAL = 0x02
};

struct TRANSACTION
{
    DWORD                   m_dwID;        ///< unique sequential ID associated with each transaction
    QWORD                   m_qwDateTime;  ///< a 64bit UTC value that represents number of seconds since Epoch
    DWORD                   m_dwAmount;    ///< Amount excluding decimal point (i.e. $100.00 would be 10000)
    WORD                    m_wType;       ///< the type of transaction, represented as TT_DEPOSIT or TT_WITHDRAWAL
};


/// Connection Request Primitive
struct CONNECTION_REQUEST
{
    DWORD                   m_dwValidationKey;  ///< to be determined

    CONNECTION_REQUEST(DWORD dwKey = 0)
        : m_dwValidationKey(dwKey)
    { };
};

/// Connection Response Result Primitive
struct CONNECTION_RESPONSE
{
     DWORD                   m_dwResult;
     WORD                    m_wMajorVersion;    ///< Server Major Version number
     WORD                    m_wMinorVersion;    ///< Server Minor Version number
     WORD                    m_wClientID;        ///< this field is generated by the server and is required in all subsequent request messages by the client
};

/// Create Account Request Primitive
struct CREATE_ACCOUNT_REQUEST
{
    char                    m_szFirstName[MAX_NAME_LEN];
    char                    m_szLastName[MAX_NAME_LEN];
    DWORD                   m_dwDLNumber;
    DWORD                   m_dwSSNumber;
    WORD                    m_wPIN;

    CREATE_ACCOUNT_REQUEST()
        : m_dwDLNumber(0),
          m_dwSSNumber(0),
          m_wPIN(0)
    { memset(m_szFirstName, 0, sizeof(m_szFirstName) + sizeof(m_szLastName) ); };

    void set_FirstName(const char* szSet)
    { if (szSet)
         strncpy(m_szFirstName, szSet, COUNTOF(m_szFirstName) - 1); };

    void set_LastName(const char* szSet)
    { if (szSet)
         strncpy(m_szLastName, szSet, COUNTOF(m_szLastName) - 1); };


};

/// Create Account Response Result Primitive
struct CREATE_ACCOUNT_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Logon Request Primitive
struct LOGON_REQUEST
{
    char                    m_szFirstName[MAX_NAME_LEN]; ///< User's first name
    WORD                    m_wPIN;                      ///< Personal Identification Number

    LOGON_REQUEST()
        : m_wPIN(0)
    { memset(m_szFirstName, 0, sizeof(m_szFirstName) ); };

    LOGON_REQUEST(const char* szFirstName, WORD wPIN)
        : m_wPIN(wPIN)
    { memset(m_szFirstName, 0, sizeof(m_szFirstName) );
      set_FirstName(szFirstName); };

    void set_FirstName(const char* szSet)
    { if (szSet)
         strncpy(m_szFirstName, szSet, COUNTOF(m_szFirstName) - 1); };
};

/// Logon Response Result Primitive
struct LOGON_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Logoff Request Primitive
struct LOGOFF_REQUEST
{
};

/// Logoff Response Result Primitive
struct LOGOFF_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Deposit Request Primitive
struct DEPOSIT_REQUEST
{
    DWORD                   m_dwAmount;  ///< Amount excluding decimal point (i.e. $100.00 would be 10000)
    WORD                    m_wType;     ///< DT_CASH or DT_CHECK

    DEPOSIT_REQUEST()
        : m_dwAmount(0),
          m_wType(DT_INVALID)
    { };

    DEPOSIT_REQUEST(DWORD dwAmount, DEPOSIT_TYPE Type)
        : m_dwAmount(dwAmount),
          m_wType(Type)
    { };
};

/// Deposit Response Result Primitive
struct DEPOSIT_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Withdrawal Request Primitive
struct WITHDRAWAL_REQUEST
{
    DWORD                   m_dwAmount;    ///< Amount excluding decimal point (i.e. $100.00 would be 10000)

    WITHDRAWAL_REQUEST()
        : m_dwAmount(0)
    { };

    WITHDRAWAL_REQUEST(DWORD dwAmount)
        : m_dwAmount(dwAmount)
    { };
};

/// Withdrawal Response Result Primitive
struct WITHDRAWAL_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Purchase Stamp Request Primitive
struct STAMP_PURCHASE_REQUEST
{
    DWORD                   m_dwAmount;    ///< Amount excluding decimal point (i.e. $100.00 would be 10000)

    STAMP_PURCHASE_REQUEST()
        : m_dwAmount(0)
    { };
};

/// Purchase Stamp Result Primitive
struct STAMP_PURCHASE_RESPONSE
{
    DWORD                   m_dwResult;
};

/// Transaction Query Request Primitive
struct TRANSACTION_QUERY_REQUEST
{
    DWORD                  m_dwStartID;           ///< the transaction number to begin the query from
    WORD                   m_wTransactionCount;  ///< the number of transactions requested

    TRANSACTION_QUERY_REQUEST()
        : m_dwStartID(0),
          m_wTransactionCount(0)
    { };
};


/// Transaction Query Result Primitive
struct TRANSACTION_QUERY_RESPONSE
{
    DWORD                   m_dwResult;
    WORD                    m_wTransactionCount; ///< number of transactions returned in array
    TRANSACTION             m_rgTransactions[];
};

/// Balance Query Request Primitive
struct BALANCE_QUERY_REQUEST
{
};

/// Balance Query Response Primitive
struct BALANCE_QUERY_RESPONSE
{
    DWORD                   m_dwResult;
    DWORD                   m_dwBalance;
};

/// CNP Standard Message Header
/**
   This is the header message that is provided as part of all CNP Request and Result 
   messages.  The m_wDataLen field is subsequently calculated as:

        sizeof(m_Request) or sizeof(m_Response)
 
   to get the size of message excluding the size of the header.

   The m_dwContext field is exclusively reserved for application use.  The contents 
   of this field is returned to the user in the corresponding result message structure 
   without modification.

*/
struct CNP_STD_HDR
{
    DWORD   m_dwMsgType;  ///< Message Type
    WORD    m_wDataLen;   ///< Message data length excluding this header
    WORD    m_wClientID;  ///< Client ID, set by the CNP Server
    DWORD   m_dwContext;  ///< Optional field, reserved for the Client

    CNP_STD_HDR()
        : m_dwMsgType(CNP_INVALID_ID),
          m_wDataLen (0),
          m_wClientID(INVALID_CLIENT_ID),
          m_dwContext(0)
    { };

    CNP_STD_HDR(DWORD dwMsgType, WORD wDataLen, WORD wClientID = INVALID_CLIENT_ID, DWORD dwContext = 0)
        : m_dwMsgType(dwMsgType),
          m_wDataLen (wDataLen),
          m_wClientID(wClientID),
          m_dwContext(dwContext)
    { };
};


struct CNP_CONNECT_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    CONNECTION_REQUEST         m_Request;

    CNP_CONNECT_REQUEST()
        : m_Hdr(CNP_CONNECT_REQUEST_ID, sizeof(m_Request) ),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_CONNECT_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    CONNECTION_RESPONSE        m_Response;
};


struct CNP_CREATE_ACCOUNT_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    CREATE_ACCOUNT_REQUEST     m_Request;

    CNP_CREATE_ACCOUNT_REQUEST(WORD wClientID)
        : m_Hdr(CNP_CREATE_ACCOUNT_REQUEST_ID, sizeof(m_Request), wClientID ),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_CREATE_ACCOUNT_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    CREATE_ACCOUNT_RESPONSE    m_Response;
};


struct CNP_LOGON_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    LOGON_REQUEST              m_Request;

    CNP_LOGON_REQUEST(WORD wClientID)
        : m_Hdr(CNP_LOGON_REQUEST_ID, sizeof(m_Request), wClientID ),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_LOGON_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    LOGON_RESPONSE             m_Response;
};

struct CNP_LOGOFF_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    LOGOFF_REQUEST             m_Request;

    CNP_LOGOFF_REQUEST(WORD wClientID)
        : m_Hdr(CNP_LOGOFF_REQUEST_ID, sizeof(m_Request), wClientID ),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_LOGOFF_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    LOGOFF_RESPONSE            m_Response;
};

struct CNP_DEPOSIT_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    DEPOSIT_REQUEST            m_Request;

    CNP_DEPOSIT_REQUEST(WORD wClientID, DWORD dwAmount, DEPOSIT_TYPE Type)
        : m_Hdr(CNP_DEPOSIT_REQUEST_ID, sizeof(m_Request), wClientID ),
          m_Request(dwAmount, Type)
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_DEPOSIT_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    DEPOSIT_RESPONSE           m_Response;
};

struct CNP_WITHDRAWAL_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    WITHDRAWAL_REQUEST         m_Request;

    CNP_WITHDRAWAL_REQUEST(WORD wClientID, DWORD dwAmount)
        : m_Hdr(CNP_WITHDRAWAL_REQUEST_ID, sizeof(m_Request), wClientID),
          m_Request(dwAmount)
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_WITHDRAWAL_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    WITHDRAWAL_RESPONSE        m_Response;
};

struct CNP_BALANCE_QUERY_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    BALANCE_QUERY_REQUEST      m_Request;

    CNP_BALANCE_QUERY_REQUEST(WORD wClientID)
        : m_Hdr(CNP_BALANCE_QUERY_REQUEST_ID, sizeof(m_Request), wClientID),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_BALANCE_QUERY_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    BALANCE_QUERY_RESPONSE     m_Response;
};

struct CNP_TRANSACTION_QUERY_REQUEST
{
    CNP_STD_HDR                m_Hdr;
    TRANSACTION_QUERY_REQUEST  m_Request;

    CNP_TRANSACTION_QUERY_REQUEST(WORD wClientID)
        : m_Hdr(CNP_TRANSACTION_QUERY_REQUEST_ID, sizeof(m_Request), wClientID ),
          m_Request()
    { };

/**
    @retval size_t containing the size of the message in bytes
*/
    size_t get_Size(void) const
    { return sizeof(m_Hdr) + sizeof(m_Request); };
};

struct CNP_TRANSACTION_QUERY_RESPONSE
{
    CNP_STD_HDR                m_Hdr;
    TRANSACTION_QUERY_RESPONSE m_Response;
};

} // namespace cnp

// restore the default structure alignment
#pragma pack(pop)

#endif