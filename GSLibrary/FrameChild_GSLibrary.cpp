//+ FrameChild_GSLibrary.cpp
// implementation of the CFrameChild_GSLibrary class
//
#include "stdafx.h"
#include "GSLibrary.h"

#include "FrameChild_GSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//+ CFrameChild_GSLibrary

IMPLEMENT_DYNCREATE(CFrameChild_GSLibrary, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CFrameChild_GSLibrary, CMDIChildWndEx)
END_MESSAGE_MAP()

// CFrameChild_GSLibrary construction/destruction

CFrameChild_GSLibrary::CFrameChild_GSLibrary()
{
	// TODO: add member initialization code here
}

CFrameChild_GSLibrary::~CFrameChild_GSLibrary()
{
}


BOOL CFrameChild_GSLibrary::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CFrameChild_GSLibrary diagnostics

#ifdef _DEBUG
void CFrameChild_GSLibrary::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CFrameChild_GSLibrary::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CFrameChild_GSLibrary message handlers
