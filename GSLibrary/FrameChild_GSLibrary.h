
// FrameChild_GSLibrary.h : interface of the CFrameChild_GSLibrary class
//

#pragma once

class CFrameChild_GSLibrary : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CFrameChild_GSLibrary)
public:
	CFrameChild_GSLibrary();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CFrameChild_GSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
