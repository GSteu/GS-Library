//+ GSLabel.cpp
// implementation file
#include "stdafx.h"
#include "GSLabel.h"
#include "GSEnumLabel.h"

//+ CGSLabel
IMPLEMENT_DYNAMIC(CGSLabel, CStatic)

CGSLabel::CGSLabel() //default constructor
{ // sine qua non
	m_pRenderTarget           = nullptr;
	//- Brushes
	m_pSolidBrushBackground   = nullptr;
	m_pSolidBrushOuterFrame   = nullptr;
	m_pSolidBrushMiddleFrame  = nullptr;
	m_pSolidBrushInnerFrame   = nullptr;
	m_pSolidBrushDrawingArea  = nullptr;
	//- Geometries
	m_pBorderGeometry         = nullptr;
	m_pOuterFrameGeometry     = nullptr;
	m_pMiddleFrameGeometry    = nullptr;
	m_pInnerGeometry          = nullptr;
	m_pDrawingAreaGeometry    = nullptr;
	//- Text
	m_strText                 ="CGSLabel Control";
	m_pSolidBrushTextColor    = nullptr;
	m_pTextFormat             = nullptr;
	m_pTextLayout             = nullptr;

}

CGSLabel::~CGSLabel() // default destructor
{	// EnableD2DSupport(TRUE, FALSE);
}

void CGSLabel::PreSubclassWindow()
{	//- TODO: Add your specialized code here and/or call the base class
	//+ Enable WINDOW!!! D2D1-Support;
	// - must be done for each and every window
	  EnableD2DSupport(TRUE, FALSE);
		CStatic::PreSubclassWindow();
		// This part should be be placed in OnCreate,
		// but that function is never called !! ?? !!
		HRESULT hr = S_OK;
		/* The following part won`t get called by OnCreate!! WHY??*/
		if (m_pRenderTarget == NULL) { m_pRenderTarget = GetRenderTarget(); }
		ATLASSERT(m_pRenderTarget && m_pRenderTarget->IsValid());
		//- Brushes
		if (SUCCEEDED(hr)) { m_pSolidBrushBackground  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(0, 0, 0)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushOuterFrame  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushMiddleFrame = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(192, 160, 64)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushInnerFrame  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(160, 144, 96)); }
		if (SUCCEEDED(hr)) { m_pSolidBrushDrawingArea = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(240, 240, 224)); }
		//- Text
		CD2DSizeF sizeTarget = m_pRenderTarget->GetSize();
		if (SUCCEEDED(hr)) { m_pTextFormat           = new CD2DTextFormat(m_pRenderTarget, CString("Segoe UI"), 12.0); }
		if (SUCCEEDED(hr)) { m_pTextLayout           = new CD2DTextLayout(m_pRenderTarget, m_strText, *m_pTextFormat, sizeTarget); }
		if (SUCCEEDED(hr)) { m_pSolidBrushTextColor  = new CD2DSolidColorBrush(m_pRenderTarget, COLORREF RGB(48, 48, 0)); }
		/* */
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
{	HRESULT hr = S_OK;
	if(CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
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
	CSize sizeWindow;
	this->GetClientRect(&rectWindow);
	sizeWindow = rectWindow.Size();

	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushOuterFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushMiddleFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushInnerFrame);
	rectWindow.DeflateRect(5, 5, 5, 5);
	m_pRenderTarget->FillRectangle(CD2DRectF(rectWindow), m_pSolidBrushDrawingArea);
	// finally, draw the text
	m_pRenderTarget->DrawTextLayout(CD2DPointF(25, 25),       // upper-left corner of the text 
		                              m_pTextLayout,            // text layout object
		                              m_pSolidBrushTextColor ); // brush used for text

	return (LRESULT)TRUE;

}
// AFX_WM_RECREATED2DRESOURCES
afx_msg LRESULT CGSLabel::OnAfxWmRecreateD2DResources(WPARAM /*wParam*/, LPARAM lParam)
{	CHwndRenderTarget* m_pRenderTarget = (CHwndRenderTarget*)lParam;
	ASSERT_KINDOF(CHwndRenderTarget, m_pRenderTarget);
	return (LRESULT)TRUE;
}




