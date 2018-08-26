#if !defined(AFX_STATICGS_H__72FB959A_8071_43DB_90E3_2E5CA9393FD4__INCLUDED_)
#define AFX_STATICGS_H__72FB959A_8071_43DB_90E3_2E5CA9393FD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticGS.h : Header-Datei
//
#include "GSAttributes.h"
/////////////////////////////////////////////////////////////////////////////
// Fenster C_GSLabel 

class C_GSLabel : public CStatic
{
	DECLARE_DYNAMIC(C_GSLabel)

// Konstruktion
public:
  C_GSLabel();
  
// Attribute
protected:
  CAttributesTextGS   m_CTextAttributes;     // Display and text attributes
  CAttributesImageGS  m_CImageAttributes;    // Background image attributes
  CString  m_strText;                        // The text to display
  bool m_bPreserveFrontSpace;                // Preserve spaces ar the beginning of text, to start a new line with (intending?)
  
public:
// Initialization
   void Initialize(const SAttributesTextGS& attr);
   void Initialize(const SAttributesTextGS_Simple& attr);
   void Initialize(const SAttributesImageGS_ID& attr);
   void Initialize(const SAttributesImageGS_File& attr);
// Protected members 
   CAttributesTextGS&   AttributesText(void);
   CAttributesImageGS&  AttributesImage(void);
// Dynamic Data eXchange routines
   void AFXAPI DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesTextGS& struDDX);
   void AFXAPI DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesTextGS_Simple& struDDX);
   void AFXAPI DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesImageGS_ID& struDDX);
   void AFXAPI DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesImageGS_File& struDDX);


// Colour functions
   void BackgroundColor(const COLORREF color);
   COLORREF BackgroundColor(void) const;
   void BorderColor(const COLORREF color);
   COLORREF BorderColor(void) const;
   void OuterFrameColor(const COLORREF color);
   COLORREF OuterFrameColor(void) const;
   void FrameColor(const COLORREF color);
   COLORREF FrameColor(void) const;
   void InnerFrameColor(const COLORREF color);
   COLORREF InnerFrameColor(void) const;
   void TextColor(const COLORREF color);
   COLORREF TextColor(void) const;

// Width functions for the frame
   void OuterFrame(const int width);
   void OuterFrame(const CRect rect);
   void Frame(const int width, const int outerWidth = -1, const int innerWidth = -1);
   void Frame(const CRect rect);
   void InnerFrame(const int width);
   void InnerFrame(const CRect rect);
   void Padding(const int width);
   void Padding(const CRect rect);

// Style functions
   void BorderStyle(const enum CAttributesTextGS::BorderLines BorderLines);
   enum CAttributesTextGS::BorderLines BorderStyle(void) const;
   void OuterFrameStyle(const enum CAttributesTextGS::OuterFrameLines OuterFrameLines);
   enum CAttributesTextGS::OuterFrameLines OuterFrameSytle(void) const;
   void FrameStyle(const enum CAttributesTextGS::FrameLines FrameLines);
   enum CAttributesTextGS::FrameLines FrameStyle(void) const;
   void InnerFrameStyle(const enum CAttributesTextGS::InnerFrameLines InnerFrameLines);
   enum CAttributesTextGS::InnerFrameLines InnerFrameStyle(void) const;
   void FrameStyle3D(const enum CAttributesTextGS::Frame3DStyle Frame3DStyle);
   enum CAttributesTextGS::Frame3DStyle FrameStyle3D(void) const;

// Text output formats
   void TextReadingFormat(const enum CAttributesTextGS::TextReading TextReading);
   enum CAttributesTextGS::TextReading TextReadingFormat(void) const;
   void TextVerticalAlign(const enum CAttributesTextGS::TextVAlignment VerticalAlign);
   enum CAttributesTextGS::TextVAlignment TextVerticalAlign(void);
   void ParaAlignFormat(const enum CAttributesTextGS::ParaAlign ParaAlign);
   enum CAttributesTextGS::ParaAlign ParaAlignFormat(void) const;
   void TextFont(const LOGFONT& logfont);
   void TextFont(CFont& cFont);
   LOGFONT& TextFont(void);
   void TextAngle(const enum CAttributesTextGS::LineAngle Angle);
   long TextAngle(void);

// Text operations
   void Text(const CString& strText);
   void Text(LPCTSTR strText);
   void Text(UINT uiResource);
   CString& Text(void);

// Image loading and style
   void LoadImage(LPCTSTR pFilename, const enum CAttributesImageGS::BackgroundImage eBackgroundImage = CAttributesImageGS::BI_StretchBlt);
   void LoadImage(UINT nIDResource, const enum CAttributesImageGS::BackgroundImage eBackgroundImage = CAttributesImageGS::BI_StretchBlt);
   void StyleImage(const enum CAttributesImageGS::BackgroundImage eBackgroundImage);

// Axis functions
   void TextXAxis(const enum CAttributesTextGS::InvertAxis XAxis);
   enum CAttributesTextGS::InvertAxis TextXAxis(void) const;
   void TextYAxis(const enum CAttributesTextGS::InvertAxis YAxis);
   enum CAttributesTextGS::InvertAxis TextYAxis(void) const;

   void ImageXAxis(const enum CAttributesImageGS::InvertAxis XAxis);
   enum CAttributesImageGS::InvertAxis ImageXAxis(void) const;
   void ImageYAxis(const enum CAttributesImageGS::InvertAxis YAxis);
   enum CAttributesImageGS::InvertAxis ImageYAxis(void) const;
// Operationen
   
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(C_GSLabel)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementierung
public:
  virtual ~C_GSLabel();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(C_GSLabel)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
   // drawing and related functions
   void Draw(CDC& dc,const CRect& rect);
   CRect CalculateTextRect(CDC& dc, const CRect& rect);
   void DrawBorder(CDC& dc, const CRect& rect);
   void DrawFrame(CDC& dc, const CRect& rect);
   void DrawImage(CDC& dc, const CRect& rect);
   void DrawText(CDC& dc, const CRect& rect);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_STATICGS_H__72FB959A_8071_43DB_90E3_2E5CA9393FD4__INCLUDED_
