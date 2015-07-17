// SWOTSystemDoc.h : interface of the CSWOTSystemDoc class
//


#pragma once


class CSWOTSystemDoc : public CDocument
{
protected: // create from serialization only
	CSWOTSystemDoc();
	DECLARE_DYNCREATE(CSWOTSystemDoc)

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
	virtual ~CSWOTSystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


