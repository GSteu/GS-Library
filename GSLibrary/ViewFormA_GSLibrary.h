
// ViewFormA_GSLibrary.h : interface of the CViewFormA_GSLibrary class
//

#pragma once


class CViewFormA_GSLibrary : public CFormView
{
protected: // create from serialization only
	CViewFormA_GSLibrary();
	DECLARE_DYNCREATE(CViewFormA_GSLibrary)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_GSLIBRARY_FORM };
#endif

// Attributes
public:
	CDocA_GSLibrary* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CViewFormA_GSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ViewFormA_GSLibrary.cpp
inline CDocA_GSLibrary* CViewFormA_GSLibrary::GetDocument() const
   { return reinterpret_cast<CDocA_GSLibrary*>(m_pDocument); }
#endif

