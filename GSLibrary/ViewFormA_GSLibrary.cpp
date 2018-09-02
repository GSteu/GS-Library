//+ ViewFormA_GSLibrary.cpp 
// implementation of the CViewFormA_GSLibrary class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GSLibrary.h"
#endif

#include "DocA_GSLibrary.h"
#include "ViewFormA_GSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//+ CViewFormA_GSLibrary
IMPLEMENT_DYNCREATE(CViewFormA_GSLibrary, CFormView)

BEGIN_MESSAGE_MAP(CViewFormA_GSLibrary, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CViewFormA_GSLibrary construction/destruction

CViewFormA_GSLibrary::CViewFormA_GSLibrary()
	: CFormView(IDD_GSLIBRARY_FORM)
{
	// TODO: add construction code here

}

CViewFormA_GSLibrary::~CViewFormA_GSLibrary()
{
}

void CViewFormA_GSLibrary::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CViewFormA_GSLibrary::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CViewFormA_GSLibrary::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CViewFormA_GSLibrary::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CViewFormA_GSLibrary::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CViewFormA_GSLibrary diagnostics

#ifdef _DEBUG
void CViewFormA_GSLibrary::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewFormA_GSLibrary::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDocA_GSLibrary* CViewFormA_GSLibrary::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocA_GSLibrary)));
	return (CDocA_GSLibrary*)m_pDocument;
}
#endif //_DEBUG


// CViewFormA_GSLibrary message handlers
