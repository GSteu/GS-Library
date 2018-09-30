#pragma once
//+ CGSLabel

class CGSLabel : public CStatic
{
	DECLARE_DYNAMIC(CGSLabel)

public:
	CGSLabel();
	virtual ~CGSLabel();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	afx_msg LRESULT OnDraw2D(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAfxWmRecreateD2DResources(WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();

	//+ Constants and Variables
	// sine qua non 
	CHwndRenderTarget   *m_pRenderTarget;
	// Solid Brushes 
	CD2DSolidColorBrush *m_pSolidBrushBackground;
	CD2DSolidColorBrush *m_pSolidBrushBorder;
	CD2DSolidColorBrush *m_pSolidBrushOuterFrame;
	CD2DSolidColorBrush *m_pSolidBrushMiddleFrame;
	CD2DSolidColorBrush *m_pSolidBrushInnerFrame;
	CD2DSolidColorBrush *m_pSolidBrushDrawingArea;
	// Gradient Brushes (linear)
	// Gradient Brushes (radial)
	// Gradient Brushes (conical)
	// Geometries
	CD2DPathGeometry* m_pBorderGeometry;
	CD2DPathGeometry* m_pOuterFrameGeometry;
	CD2DPathGeometry* m_pMiddleFrameGeometry;
	CD2DPathGeometry* m_pInnerGeometry;
	CD2DPathGeometry* m_pDrawingAreaGeometry;
	// Text and Formatting
	CString m_strText;
	CD2DSolidColorBrush *m_pSolidBrushTextColor;
	CD2DTextFormat *m_pTextFormat;
	CD2DTextLayout *m_pTextLayout;
	// TODO: to be defined
	// list of text range formats
	//CTypedPtrList<CObList, CTextRangeFormat*> m_listTextRangeFormat;
};


