// 2dcolorDoc.h : interface of the CMy2dcolorDoc class
//


#pragma once


class CMy2dcolorDoc : public CDocument
{
protected: // create from serialization only
	CMy2dcolorDoc();
	DECLARE_DYNCREATE(CMy2dcolorDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMy2dcolorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


