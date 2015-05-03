// colourchangingDoc.cpp : implementation of the CcolourchangingDoc class
//

#include "stdafx.h"
#include "colourchanging.h"

#include "colourchangingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcolourchangingDoc

IMPLEMENT_DYNCREATE(CcolourchangingDoc, CDocument)

BEGIN_MESSAGE_MAP(CcolourchangingDoc, CDocument)
END_MESSAGE_MAP()


// CcolourchangingDoc construction/destruction

CcolourchangingDoc::CcolourchangingDoc()
{
	// TODO: add one-time construction code here

}

CcolourchangingDoc::~CcolourchangingDoc()
{
}

BOOL CcolourchangingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CcolourchangingDoc serialization

void CcolourchangingDoc::Serialize(CArchive& ar)
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


// CcolourchangingDoc diagnostics

#ifdef _DEBUG
void CcolourchangingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcolourchangingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcolourchangingDoc commands
