// colourchangingDoc.h : interface of the CcolourchangingDoc class
//


#pragma once


class CcolourchangingDoc : public CDocument
{
protected: // create from serialization only
	CcolourchangingDoc();
	DECLARE_DYNCREATE(CcolourchangingDoc)

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
	virtual ~CcolourchangingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


