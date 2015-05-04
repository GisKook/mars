// 2dcolorDoc.cpp : implementation of the CMy2dcolorDoc class
//

#include "stdafx.h"
#include "2dcolor.h"

#include "2dcolorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2dcolorDoc

IMPLEMENT_DYNCREATE(CMy2dcolorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy2dcolorDoc, CDocument)
END_MESSAGE_MAP()


// CMy2dcolorDoc construction/destruction

CMy2dcolorDoc::CMy2dcolorDoc()
{
	// TODO: add one-time construction code here

}

CMy2dcolorDoc::~CMy2dcolorDoc()
{
}

BOOL CMy2dcolorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMy2dcolorDoc serialization

void CMy2dcolorDoc::Serialize(CArchive& ar)
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


// CMy2dcolorDoc diagnostics

#ifdef _DEBUG
void CMy2dcolorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2dcolorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2dcolorDoc commands
