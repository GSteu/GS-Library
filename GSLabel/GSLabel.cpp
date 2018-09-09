//+ GSLabel.cpp
// implementation file
#include "stdafx.h"
#include "GSLabel.h"

//+ CGSLabel
IMPLEMENT_DYNAMIC(CGSLabel, CStatic)

CGSLabel::CGSLabel() //default constructor
{ // sine qua non
	m_pRenderTarget           = NULL;
	//- Brushes
	m_pSolidBrushBackground   = NULL;
	m_pSolidBrushOuterFrame   = NULL;
	m_pSolidBrushMiddleFrame  = NULL;
	m_pSolidBrushInnerFrame   = NULL;
	m_pSolidBrushDrawingArea  = NULL;
	//- Geometries
	m_pBorderGeometry         = NULL;
	m_pOuterFrameGeometry     = NULL;
	m_pMiddleFrameGeometry    = NULL;
	m_pInnerGeometry          = NULL;
	m_pDrawingAreaGeometry    = NULL;

}

CGSLabel::~CGSLabel() // default destructor
{	// EnableD2DSupport(TRUE, FALSE);
}

void CGSLabel::PreSubclassWindow()
{	//- TODO: Add your specialized code here and/or call the base class
	//+ Enable WINDOW!!! D2D1-Support;
	// - must be done for each and every window
	  EnableD2DSupport(TRUE, FALSE);
		HRESULT hr = S_OK;
		if (m_pRenderTarget == NULL) { m_pRenderTarget = GetRenderTarget(); }
		ATLASSERT(m_pRenderTarget && m_pRenderTarget->IsValid());
		if (SUCCEEDED(hr)) { m_pSolidBrushBackground = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(0, 0, 0)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushOuterFrame = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushMiddleFrame = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(192, 160, 64)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushInnerFrame = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushDrawingArea = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(240, 240, 240)); }
		CStatic::PreSubclassWindow();
}


BEGIN_MESSAGE_MAP(CGSLabel, CStatic)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(AFX_WM_DRAW2D, &CGSLabel::OnDraw2D)
	ON_REGISTERED_MESSAGE(AFX_WM_RECREATED2DRESOURCES, &CGSLabel::OnAfxWmRecreateD2DResources)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
// CGSLabel message handlers

// WM_CREATE
int CGSLabel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	if(CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

  // Create Direct2D resources
  HRESULT hr = S_OK;
	if ( m_pRenderTarget == NULL ) { m_pRenderTarget = GetRenderTarget(); }
	ATLASSERT(m_pRenderTarget && m_pRenderTarget->IsValid());
	if(SUCCEEDED(hr)) {m_pSolidBrushBackground   = new CD2DSolidColorBrush(m_pRenderTarget, GetSysColor(COLOR_WINDOW));}
	if(SUCCEEDED(hr)) {m_pSolidBrushOuterFrame   = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96));}
	if(SUCCEEDED(hr)) {m_pSolidBrushMiddleFrame  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(192, 160, 64));}
	if(SUCCEEDED(hr)) {m_pSolidBrushInnerFrame   = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96));}
	if(SUCCEEDED(hr)) {m_pSolidBrushDrawingArea  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(192, 240, 192));}
  // CreateBrushes
	return hr;
}
// WM_ERASEBKGRND (EraseBackground)
BOOL CGSLabel::OnEraseBkgnd(CDC* pDC)
{	// TODO: Add your message handler code here and/or call default
  // m_pRenderTarget->Clear(_Color);
	return CStatic::OnEraseBkgnd(pDC);
	//return(0);
}

// AFX_WM_DRAW2D
afx_msg LRESULT CGSLabel::OnDraw2D(WPARAM /*wParam*/, LPARAM /*lParam*/)
{//	m_pRenderTarget = GetRenderTarget();
	m_pRenderTarget->Clear({ float(0.8),float(0.0),float(0.8),1 });

	CRect rectWindow;
	this->GetClientRect(&rectWindow);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushOuterFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushMiddleFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushInnerFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushDrawingArea);
	return (LRESULT)TRUE;

}
// AFX_WM_RECREATED2DRESOURCES
afx_msg LRESULT CGSLabel::OnAfxWmRecreateD2DResources(WPARAM /*wParam*/, LPARAM lParam)
{	CHwndRenderTarget* pRenderTarget = (CHwndRenderTarget*)lParam;
	ASSERT_KINDOF(CHwndRenderTarget, pRenderTarget);
	return (LRESULT)TRUE;
}




