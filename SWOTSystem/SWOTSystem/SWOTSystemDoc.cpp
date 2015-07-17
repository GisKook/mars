// SWOTSystemDoc.cpp : implementation of the CSWOTSystemDoc class
//

#include "stdafx.h"
#include "SWOTSystem.h"

#include "SWOTSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSWOTSystemDoc

IMPLEMENT_DYNCREATE(CSWOTSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CSWOTSystemDoc, CDocument)
END_MESSAGE_MAP()


// CSWOTSystemDoc construction/destruction

CSWOTSystemDoc::CSWOTSystemDoc()
{
	// TODO: add one-time construction code here

}

CSWOTSystemDoc::~CSWOTSystemDoc()
{
}

BOOL CSWOTSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSWOTSystemDoc serialization

void CSWOTSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CSWOTSystemDoc diagnostics

#ifdef _DEBUG
void CSWOTSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSWOTSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSWOTSystemDoc commands
