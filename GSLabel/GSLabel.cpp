// GSLabel.cpp: Implementierungsdatei
//

#include "stdafx.h"
// #include "resource.h"
#include "GSLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// C_GSLabel
IMPLEMENT_DYNAMIC( C_GSLabel, CStatic )

C_GSLabel::C_GSLabel()
{ m_bPreserveFrontSpace = true;
}

C_GSLabel::~C_GSLabel()
{
}


BEGIN_MESSAGE_MAP(C_GSLabel, CStatic)
	//{{AFX_MSG_MAP(C_GSLabel)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten C_GSLabel

void C_GSLabel::PreSubclassWindow()
{ m_CTextAttributes.m_ftDefault.CreateFontIndirect(&m_CTextAttributes.m_lfDefault);
  CStatic::PreSubclassWindow();
}

BOOL C_GSLabel::OnEraseBkgnd(CDC* pDC)
{// Where is the window
  CWnd *pOutputWnd = pDC->GetWindow();
  if( NULL == pOutputWnd ) // Where there's no output, there's no erasing
    { return true;         // so there's no further erasing required
    }
  CRect rect;
  pOutputWnd->GetWindowRect(rect);
  rect.OffsetRect(-rect.left,-rect.top);
  pDC->DPtoLP(&rect);
  pDC->FillSolidRect(&rect,BackgroundColor());
  return true; // We did our job
}

void C_GSLabel::OnPaint()
{ if( !GetUpdateRect(NULL) )
    { return; // nothing to paint
    }
  CPaintDC dc(this); // device context for painting
// Check if we have characters to write available!!
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() == NULL )
    { m_CTextAttributes.m_ftDefault.CreateFontIndirect( &m_CTextAttributes.m_lfDefault );
    }
// Save the actual DC state
  CSize  OldWndExt  = dc.GetWindowExt();
  CPoint OldWndOrg  = dc.GetWindowOrg();
  CSize  OldViewExt = dc.GetViewportExt();
  CPoint OldViewOrg = dc.GetViewportOrg();
  int    OldMapMode = dc.GetMapMode();
  int    OldBkMode  = dc.GetBkMode();
  int    OldGphMode = ::SetGraphicsMode(dc.GetSafeHdc(),GM_ADVANCED);
// Get drawing rectangle and convert it
  CWnd *pWnd = dc.GetWindow();
  if( NULL == pWnd ) // No window no pain(t)
    { return;
	}
  CRect rectWindow(0,0,0,0);
  pWnd->GetClientRect(&rectWindow);
// Set mapping mode to 1440 Twips with
//     y-axis running down, x-axis running to the right
  dc.SetMapMode(MM_ANISOTROPIC);
  dc.SetBkMode(TRANSPARENT);
  dc.SetWindowOrg(0, 0);   // Origin of the coordinates
  dc.SetViewportOrg(0, 0); // Origin of looking
  dc.SetWindowExt(1440,1440);// Measuring units count of x- and y-axis
// Device viewport is dpi of actual output device.
  dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX),
                   dc.GetDeviceCaps(LOGPIXELSY));
  //CSize sizeMonitor(dc.GetDeviceCaps(HORZSIZE),dc.GetDeviceCaps(VERTSIZE));
  //CSize sizeResMonitor(dc.GetDeviceCaps(HORZRES),dc.GetDeviceCaps(VERTRES));
// Turn size and position of window in logical coordinates
  dc.DPtoLP(&rectWindow);

// Now avoid flickering using memory dc and bitmap
  CDC     *pDrawDC = &dc;       // !! ATTENTION !! either CPaintDC or memory dc. Never delete!
  CDC     *pMemDC  = new CDC;   // Memory dc to be
  CBitmap *pBitmap = new CBitmap;
  CBitmap *pOldBitmap = NULL;
// Check if we may use bitmap and memory dc
// if something goes wrong, use CPaintDC directly
  if( RC_BITBLT == (dc.GetDeviceCaps(RASTERCAPS) & RC_BITBLT) ) // may we use a bitmap?
    { if( pMemDC->CreateCompatibleDC(&dc) )// We may use the memory dc
        {// Set memory dc to the same settings as CPaintDC
          pMemDC->SetMapMode(MM_ANISOTROPIC);
          pMemDC->SetBkMode(TRANSPARENT);
          pMemDC->SetWindowOrg(0, 0);
          pMemDC->SetWindowExt(1440,1440);
          pMemDC->SetViewportOrg(0, 0);
          pMemDC->SetViewportExt(pMemDC->GetDeviceCaps(LOGPIXELSX),
                                 pMemDC->GetDeviceCaps(LOGPIXELSY));
          if( pBitmap->CreateCompatibleBitmap(&dc,rectWindow.Width(),rectWindow.Height()) )
            { // Although we created the bitmap for use with to the CPaintDC, it is safe to select
			        // the bitmap into the memory dc, because this dc is comaptible to the CPaintDC
			        pOldBitmap = pMemDC->SelectObject(pBitmap);
			        // Because the new dc is black, we have to transport the picture information (background)
			        // from the CPaintDC to the memory dc
              pMemDC->BitBlt(rectWindow.left,rectWindow.top,rectWindow.Width(),rectWindow.Height(),
                             &dc,0,0,SRCCOPY);
			        pDrawDC = pMemDC;// Now it's safe to use the memory dc for drawing
			      }
          else
			      { delete pBitmap;
			        pBitmap = NULL;
			        delete pMemDC;
			        pMemDC = NULL;
			      }
		    }// if( pMemDC->CreateCompatibleDC(&dc) )
      else
        { delete pBitmap;
		      pBitmap = NULL;
          delete pMemDC;
		      pMemDC = NULL;
		    }
	  }// if( RC_BITBLT == (dc.GetDeviceCaps(RASTERCAPS) & RC_BITBLT) )
  else
    { delete pBitmap;
	    pBitmap = NULL;
      delete pMemDC;
	    pMemDC = NULL;
	  }

// Now that we found the device context, start drawing
  Draw(*pDrawDC,rectWindow);
// Copy memory bitmap if available to CPaintDC (screen)
  if( pBitmap != NULL )
    { dc.BitBlt(rectWindow.left,rectWindow.top,rectWindow.Width(),rectWindow.Height(),
                pDrawDC,0,0,SRCCOPY);
    }

// Restore old dc state
  dc.SetBkMode(OldBkMode);
  dc.SetMapMode(OldMapMode);
  dc.SetViewportOrg(OldViewOrg);
  dc.SetViewportExt(OldViewExt);
  dc.SetWindowOrg(OldWndOrg);
  dc.SetWindowExt(OldWndExt);
  if( 0 != OldGphMode )
    { ::SetGraphicsMode(dc.GetSafeHdc(),OldGphMode);
	  }
// Get rid of created classes
// do not delete pDrawDC!!
  if( pBitmap != NULL )
    { pMemDC->SelectObject(pOldBitmap);// Select bitmap out of memory dc
      delete pBitmap;
      pBitmap = NULL;
	  }
  if( pMemDC != NULL )
    { delete pMemDC;
      pMemDC = NULL;
	  }
}


// Initialization
void C_GSLabel::Initialize(const SAttributesTextGS& attr)
{ if( NULL == &attr )
    { return;
	}
  LOGFONT logFont;
  m_CTextAttributes.m_lFrameStyle = attr.m_dwFrameStyle;
  m_CTextAttributes.m_enum3DStyle = attr.m_enum3DStyle;
  m_CTextAttributes.m_enumCorners = attr.m_enumCorners;
  // Colours, colours
  BackgroundColor(attr.m_clrBackground);
  BorderColor(attr.m_clrBorder);
  OuterFrameColor(attr.m_clrOuterFrame);
  FrameColor(attr.m_clrFrame);
  InnerFrameColor(attr.m_clrInnerFrame);
  TextColor(attr.m_clrText);
  // Frame widths
  OuterFrame(attr.m_rectOuterWidth);
  Frame(attr.m_rectMiddleWidth);
  InnerFrame(attr.m_rectInnerWidth);
  Padding(attr.m_rectPadding);
  // Font
  memset(&logFont,0,sizeof(LOGFONT));
  logFont.lfHeight		     = attr.m_iFontSize*20;
  logFont.lfWidth		       = 0;
  logFont.lfEscapement	   = 0;
  logFont.lfOrientation	   = 0;
  logFont.lfWeight		     = (attr.m_bBold)?(FW_BOLD):(FW_NORMAL);
  logFont.lfItalic		     = attr.m_bItalic;
  logFont.lfUnderline	     = attr.m_bUnderline;
  logFont.lfStrikeOut	     = false;
  logFont.lfCharSet		     = ANSI_CHARSET;
  logFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;
  logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
  logFont.lfQuality		     = DEFAULT_QUALITY;
  logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
  _tcsncpy_s(logFont.lfFaceName,32,attr.m_strFontName,31);
  TextFont(logFont);
  // Text formatting and orientation
  TextAngle(attr.m_enumLineAngle);
  TextReadingFormat(attr.m_enumReading);
  TextVerticalAlign(attr.m_enumTVAlignment);
  ParaAlignFormat(attr.m_enumParagraph);
}
void C_GSLabel::Initialize(const SAttributesTextGS_Simple& attr)
{ if( NULL == &attr )
    { return;
	}
  LOGFONT logFont;
  m_CTextAttributes.m_lFrameStyle = attr.m_dwFrameStyle;
  m_CTextAttributes.m_enum3DStyle = attr.m_enum3DStyle;
  // Colours, colours
  BackgroundColor(attr.m_clrBackground);
  BorderColor(attr.m_clrBorder);
  OuterFrameColor(attr.m_clrFrame);
  FrameColor(attr.m_clrFrame);
  InnerFrameColor(attr.m_clrFrame);
  TextColor(attr.m_clrText);
  // Frame widths
  OuterFrame(attr.m_iOuterWidth);
  Frame(attr.m_iMiddleWidth);
  InnerFrame(attr.m_iInnerWidth);
  Padding(attr.m_iPadding);
  // Font
  memset(&logFont,0,sizeof(LOGFONT));
  logFont.lfHeight		  	 = attr.m_iFontSize*20;
  logFont.lfWidth		  		 = 0;
  logFont.lfEscapement	   = 0;
  logFont.lfOrientation	   = 0;
  logFont.lfWeight		  	 = (attr.m_bBold)?(FW_BOLD):(FW_NORMAL);
  logFont.lfItalic		  	 = attr.m_bItalic;
  logFont.lfUnderline	  	 = attr.m_bUnderline;
  logFont.lfStrikeOut	  	 = false;
  logFont.lfCharSet		  	 = ANSI_CHARSET;
  logFont.lfOutPrecision   = OUT_DEFAULT_PRECIS;
  logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
  logFont.lfQuality		   	 = DEFAULT_QUALITY;
  logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
  _tcsncpy_s(logFont.lfFaceName,32,attr.m_strFontName,31);
  TextFont(logFont);
  // Text formatting and orientation
  TextVerticalAlign(attr.m_enumTVAlignment);
  ParaAlignFormat(attr.m_enumParagraph);
}

void C_GSLabel::Initialize(const SAttributesImageGS_ID& attr)
{ if( NULL == &attr )
    { return;
	}
  if( attr.m_uiBitmap == 0 )
    { return;
	}
  if( m_CImageAttributes.m_uiBitmap != attr.m_uiBitmap )
	{ LoadImage(attr.m_uiBitmap, attr.m_enumBackImage);
	}
  m_CImageAttributes.m_enumBackImage = attr.m_enumBackImage;
  m_CImageAttributes.m_enumInvertAxis = attr.m_enumInvertAxis;
}

void C_GSLabel::Initialize(const SAttributesImageGS_File& attr)
{ if( NULL == &attr )
    { return;
	}
  if( 0>= _tcslen(attr.m_strBitmap) )
    { return;
	}
  CString strFile(attr.m_strBitmap);
  if( strFile != m_CImageAttributes.m_strBitmap )
    { LoadImage(attr.m_strBitmap, attr.m_enumBackImage);
	}
  m_CImageAttributes.m_enumBackImage = attr.m_enumBackImage;
  m_CImageAttributes.m_enumInvertAxis = attr.m_enumInvertAxis;
}

// Protected members 
CAttributesTextGS&   C_GSLabel::AttributesText(void)
{return (m_CTextAttributes);}
CAttributesImageGS&  C_GSLabel::AttributesImage(void)
{return (m_CImageAttributes);}
// Dynamic Data eXchange routines
void AFXAPI C_GSLabel::DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesTextGS& struDDX)
{// code from Microsoft
  if( this->m_hWnd == NULL )    // not subclassed yet
    { ASSERT(!pDX->m_bSaveAndValidate);
      HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
      if( !this->SubclassWindow(hWndCtrl) )
        { ASSERT(FALSE);      // possibly trying to subclass twice ?
          AfxThrowNotSupportedException();
        }
    }
  if( NULL != &struDDX )
    { Initialize(struDDX);
	}
}
void AFXAPI C_GSLabel::DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesTextGS_Simple& struDDX)
{// code from Microsoft
  if( this->m_hWnd == NULL )    // not subclassed yet
    { ASSERT(!pDX->m_bSaveAndValidate);
      HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
      if( !this->SubclassWindow(hWndCtrl) )
        { ASSERT(FALSE);      // possibly trying to subclass twice ?
          AfxThrowNotSupportedException();
        }
    }
  if( NULL != &struDDX )
    { Initialize(struDDX);
	}
}
void AFXAPI C_GSLabel::DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesImageGS_ID& struDDX)
{// code from Microsoft
  if( this->m_hWnd == NULL )    // not subclassed yet
    { ASSERT(!pDX->m_bSaveAndValidate);
      HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
      if( !this->SubclassWindow(hWndCtrl) )
        { ASSERT(FALSE);      // possibly trying to subclass twice ?
          AfxThrowNotSupportedException();
        }
    }
  if( NULL != &struDDX )
    { Initialize(struDDX);
	}
}
void AFXAPI C_GSLabel::DDX_Control( CDataExchange* pDX, int nIDC, const SAttributesImageGS_File& struDDX)
{// code from Microsoft
  if( this->m_hWnd == NULL )    // not subclassed yet
    { ASSERT(!pDX->m_bSaveAndValidate);
      HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
      if( !this->SubclassWindow(hWndCtrl) )
        { ASSERT(FALSE);      // possibly trying to subclass twice ?
          AfxThrowNotSupportedException();
        }
    }
  if( NULL != &struDDX )
    { Initialize(struDDX);
	}
}

// Colour functions
void C_GSLabel::BackgroundColor(const COLORREF color)
{ m_CTextAttributes.m_clrBackground = color;
}
COLORREF C_GSLabel::BackgroundColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrBackground;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrBackground & 0x00FFFFFF));
	}
  return( clrColour );
}

void C_GSLabel::BorderColor(const COLORREF color)
{ m_CTextAttributes.m_clrBorder = color;
}
COLORREF C_GSLabel::BorderColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrBorder;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrBorder & 0x00FFFFFF));
	}
  return( clrColour );
}

void C_GSLabel::OuterFrameColor(const COLORREF color)
{ m_CTextAttributes.m_clrOuterFrame = color;
}
COLORREF C_GSLabel::OuterFrameColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrOuterFrame;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrOuterFrame & 0x00FFFFFF));
	}
  return( clrColour );
}

void C_GSLabel::FrameColor(const COLORREF color)
{ m_CTextAttributes.m_clrFrame = color;
}
COLORREF C_GSLabel::FrameColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrFrame;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrFrame & 0x00FFFFFF));
	}
  return( clrColour );
}

void C_GSLabel::InnerFrameColor(const COLORREF color)
{ m_CTextAttributes.m_clrInnerFrame = color;
}
COLORREF C_GSLabel::InnerFrameColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrInnerFrame;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrInnerFrame & 0x00FFFFFF));
	}
  return( clrColour );
}

void C_GSLabel::TextColor(const COLORREF color)
{ m_CTextAttributes.m_clrText = color;
}
COLORREF C_GSLabel::TextColor(void) const
{ COLORREF clrColour = m_CTextAttributes.m_clrText;
  if( (clrColour & 0xFF000000) == 0xFF000000 )
    { clrColour = ::GetSysColor((m_CTextAttributes.m_clrText & 0x00FFFFFF));
	}
  return( clrColour );
}

// Width functions for the frame
void C_GSLabel::OuterFrame(const int width)
{ if( width >= 0)
    { m_CTextAttributes.m_widthsOuterFrame.SetRect(width,width,width,width);
	}
}
void C_GSLabel::OuterFrame(const CRect rect)
{ if( rect.left >= 0 )
    { m_CTextAttributes.m_widthsOuterFrame.left = rect.left;
		}
  if( rect.top >= 0 )
    { m_CTextAttributes.m_widthsOuterFrame.top = rect.top;
	}
  if( rect.right >= 0 )
    { m_CTextAttributes.m_widthsOuterFrame.right = rect.right;
	}
  if( rect.bottom >= 0 )
    { m_CTextAttributes.m_widthsOuterFrame.bottom = rect.bottom;
	}
}

void C_GSLabel::Frame(const int width, const int outerWidth/* = -1*/, const int innerWidth/* = -1*/)
{ if( width >= 0)
    { m_CTextAttributes.m_widthsFrame.SetRect(width,width,width,width);
	}
  if( outerWidth >= 0)
    { m_CTextAttributes.m_widthsOuterFrame.SetRect(outerWidth,outerWidth,outerWidth,outerWidth);
	}
  if( innerWidth >= 0)
    { m_CTextAttributes.m_widthsInnerFrame.SetRect(innerWidth,innerWidth,innerWidth,innerWidth);
	}
}
void C_GSLabel::Frame(const CRect rect)
{ if( rect.left >= 0 )
    { m_CTextAttributes.m_widthsFrame.left = rect.left;
	}
  if( rect.top >= 0 )
    { m_CTextAttributes.m_widthsFrame.top = rect.top;
	}
  if( rect.right >= 0 )
    { m_CTextAttributes.m_widthsFrame.right = rect.right;
	}
  if( rect.bottom >= 0 )
    { m_CTextAttributes.m_widthsFrame.bottom = rect.bottom;
	}
}

void C_GSLabel::InnerFrame(const int width)
{ if( width >= 0)
    { m_CTextAttributes.m_widthsInnerFrame.SetRect(width,width,width,width);
	}
}
void C_GSLabel::InnerFrame(const CRect rect)
{ if( rect.left >= 0 )
    { m_CTextAttributes.m_widthsInnerFrame.left = rect.left;
	}
  if( rect.top >= 0 )
    { m_CTextAttributes.m_widthsInnerFrame.top = rect.top;
	}
  if( rect.right >= 0 )
    { m_CTextAttributes.m_widthsInnerFrame.right = rect.right;
	}
  if( rect.bottom >= 0 )
    { m_CTextAttributes.m_widthsInnerFrame.bottom = rect.bottom;
	}
}

void C_GSLabel::Padding(const int width)
{ if( width >= 0)
    { m_CTextAttributes.m_widthsPadding.SetRect(width,width,width,width);
	}
}
void C_GSLabel::Padding(const CRect rect)
{ if( rect.left >= 0 )
    { m_CTextAttributes.m_widthsPadding.left = rect.left;
	}
  if( rect.top >= 0 )
    { m_CTextAttributes.m_widthsPadding.top = rect.top;
	}
  if( rect.right >= 0 )
    { m_CTextAttributes.m_widthsPadding.right = rect.right;
	}
  if( rect.bottom >= 0 )
    { m_CTextAttributes.m_widthsPadding.bottom = rect.bottom;
	}
}

// Style functions
void C_GSLabel::BorderStyle(const enum CAttributesTextGS::BorderLines BorderLines)
{ m_CTextAttributes.m_lFrameStyle &= 0x0FFF;
  m_CTextAttributes.m_lFrameStyle |= BorderLines;
}
enum CAttributesTextGS::BorderLines C_GSLabel::BorderStyle(void) const
{ return (m_CTextAttributes.BorderLines());
}
void C_GSLabel::OuterFrameStyle(const enum CAttributesTextGS::OuterFrameLines OuterFrameLines)
{ m_CTextAttributes.m_lFrameStyle &= 0xF0FF;
  m_CTextAttributes.m_lFrameStyle |= OuterFrameLines;
}
enum CAttributesTextGS::OuterFrameLines C_GSLabel::OuterFrameSytle(void) const
{ return (m_CTextAttributes.OuterFrameLines());
}
void C_GSLabel::FrameStyle(const enum CAttributesTextGS::FrameLines FrameLines)
{ m_CTextAttributes.m_lFrameStyle &= 0xFF0F;
  m_CTextAttributes.m_lFrameStyle |= FrameLines;
}
enum CAttributesTextGS::FrameLines C_GSLabel::FrameStyle(void) const
{ return (m_CTextAttributes.FrameLines());
}
void C_GSLabel::InnerFrameStyle(const enum CAttributesTextGS::InnerFrameLines InnerFrameLines)
{ m_CTextAttributes.m_lFrameStyle &= 0xFFF0;
  m_CTextAttributes.m_lFrameStyle |= InnerFrameLines;
}
enum CAttributesTextGS::InnerFrameLines C_GSLabel::InnerFrameStyle(void) const
{ return (m_CTextAttributes.InnerFrameLines());
}
void C_GSLabel::FrameStyle3D(const enum CAttributesTextGS::Frame3DStyle Frame3DStyle)
{ m_CTextAttributes.m_enum3DStyle = Frame3DStyle;
}
enum CAttributesTextGS::Frame3DStyle C_GSLabel::FrameStyle3D(void) const
{ return (m_CTextAttributes.m_enum3DStyle);
}

// Text output formats
void C_GSLabel::TextReadingFormat(const enum CAttributesTextGS::TextReading TextReading)
{ m_CTextAttributes.m_enumReading = TextReading;
}
enum CAttributesTextGS::TextReading C_GSLabel::TextReadingFormat(void) const
{ return (m_CTextAttributes.m_enumReading);
}
void C_GSLabel::TextVerticalAlign(const enum CAttributesTextGS::TextVAlignment VerticalAlign)
{ m_CTextAttributes.m_enumTVAlignment = VerticalAlign;
}
enum CAttributesTextGS::TextVAlignment C_GSLabel::TextVerticalAlign(void)
{ return (m_CTextAttributes.m_enumTVAlignment);
}
void C_GSLabel::ParaAlignFormat(const enum CAttributesTextGS::ParaAlign ParaAlign)
{ m_CTextAttributes.m_enumParagraph = ParaAlign;
}
enum CAttributesTextGS::ParaAlign C_GSLabel::ParaAlignFormat(void) const
{ return (m_CTextAttributes.m_enumParagraph);
}
void C_GSLabel::TextFont(const LOGFONT& logfont)
{// Prepare the font, be carefull because the window may not be fully initialized yet
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() != NULL )
    { m_CTextAttributes.m_ftDefault.DeleteObject();
    }
  memset(&m_CTextAttributes.m_lfDefault,0,sizeof(LOGFONT));
  m_CTextAttributes.m_lfDefault.lfHeight				 = logfont.lfHeight;
  m_CTextAttributes.m_lfDefault.lfWidth					 = logfont.lfWidth;
  m_CTextAttributes.m_lfDefault.lfEscapement		 = logfont.lfEscapement;
  m_CTextAttributes.m_lfDefault.lfOrientation		 = logfont.lfOrientation;
  m_CTextAttributes.m_lfDefault.lfWeight		 		 = logfont.lfWeight;
  m_CTextAttributes.m_lfDefault.lfItalic		 		 = logfont.lfItalic;
  m_CTextAttributes.m_lfDefault.lfUnderline			 = logfont.lfUnderline;
  m_CTextAttributes.m_lfDefault.lfStrikeOut			 = logfont.lfStrikeOut;
  m_CTextAttributes.m_lfDefault.lfCharSet				 = logfont.lfCharSet;
  m_CTextAttributes.m_lfDefault.lfOutPrecision	 = logfont.lfOutPrecision;
  m_CTextAttributes.m_lfDefault.lfClipPrecision	 = logfont.lfClipPrecision;
  m_CTextAttributes.m_lfDefault.lfQuality				 = logfont.lfQuality;
  m_CTextAttributes.m_lfDefault.lfPitchAndFamily = logfont.lfPitchAndFamily;
  _tcsncpy_s(m_CTextAttributes.m_lfDefault.lfFaceName,32,logfont.lfFaceName,31);
  m_CTextAttributes.m_lfDefault.lfOrientation		 = m_CTextAttributes.m_lLineAngle;
  m_CTextAttributes.m_lfDefault.lfEscapement 		 = m_CTextAttributes.m_lLineAngle;
}
void C_GSLabel::TextFont(CFont& cFont)
{// Prepare the font, be carefull because the window may not be fully initialized yet
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() != NULL )
    { m_CTextAttributes.m_ftDefault.DeleteObject();
    }
  cFont.GetLogFont(&m_CTextAttributes.m_lfDefault);
  m_CTextAttributes.m_lfDefault.lfOrientation = m_CTextAttributes.m_lLineAngle;
  m_CTextAttributes.m_lfDefault.lfEscapement  = m_CTextAttributes.m_lLineAngle;
}
LOGFONT& C_GSLabel::TextFont(void)
{ return (m_CTextAttributes.m_lfDefault);
}
void C_GSLabel::TextAngle(const enum CAttributesTextGS::LineAngle Angle)
{ long lAngle = (long)Angle;
  if( m_CTextAttributes.m_lLineAngle == lAngle )
    { return; // No angle changes, no angel flies
	}
  m_CTextAttributes.m_lLineAngle = lAngle;
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() != NULL )
    { m_CTextAttributes.m_ftDefault.GetLogFont(&m_CTextAttributes.m_lfDefault);
      m_CTextAttributes.m_ftDefault.DeleteObject();
	}
  m_CTextAttributes.m_lfDefault.lfOrientation = 0;
  m_CTextAttributes.m_lfDefault.lfOrientation = m_CTextAttributes.m_lLineAngle;
  m_CTextAttributes.m_lfDefault.lfEscapement  = m_CTextAttributes.m_lLineAngle;
}
long C_GSLabel::TextAngle(void)
{ return (m_CTextAttributes.m_lLineAngle);
}

// Text operations
void C_GSLabel::Text(const CString& strText)
{ m_strText = strText;
}
void C_GSLabel::Text(LPCTSTR strText)
{ m_strText = strText;
}
void C_GSLabel::Text(UINT uiResource)
{ CString strRes;
  if( strRes.LoadString(uiResource) )
    { m_strText = strRes;
	}
}
CString& C_GSLabel::Text(void)
{ return m_strText;
}

// Image loading and style
void C_GSLabel::LoadImage(LPCTSTR pFilename, const enum CAttributesImageGS::BackgroundImage eBackgroundImage/* = CAttributesImageGS::BI_StretchBlt*/)
{ m_CImageAttributes.LoadBitmap(pFilename);
  m_CImageAttributes.m_enumBackImage = eBackgroundImage;
}
void C_GSLabel::LoadImage(UINT nIDResource, const enum CAttributesImageGS::BackgroundImage eBackgroundImage/* = CAttributesImageGS::BI_StretchBlt*/)
{ m_CImageAttributes.LoadBitmap(nIDResource);
  m_CImageAttributes.m_enumBackImage = eBackgroundImage;
}
void C_GSLabel::StyleImage(const enum CAttributesImageGS::BackgroundImage eBackgroundImage)
{ m_CImageAttributes.m_enumBackImage = eBackgroundImage;
}

// Axis functions
void C_GSLabel::TextXAxis(const enum CAttributesTextGS::InvertAxis XAxis)
{ DWORD enumAxis = m_CTextAttributes.m_enumInvertAxis;
  enumAxis &= 0x0002;
  enumAxis |= XAxis;
  m_CTextAttributes.m_enumInvertAxis = (enum CAttributesTextGS::InvertAxis)enumAxis;
}
enum CAttributesTextGS::InvertAxis C_GSLabel::TextXAxis(void) const
{return (enum CAttributesTextGS::InvertAxis)(m_CTextAttributes.m_enumInvertAxis & CAttributesTextGS::IA_Axis_X);
}
void C_GSLabel::TextYAxis(const enum CAttributesTextGS::InvertAxis YAxis)
{ DWORD enumAxis = m_CTextAttributes.m_enumInvertAxis;
  enumAxis &= 0x0001;
  enumAxis |= YAxis;
  m_CTextAttributes.m_enumInvertAxis = (enum CAttributesTextGS::InvertAxis)enumAxis;
}
enum CAttributesTextGS::InvertAxis C_GSLabel::TextYAxis(void) const
{return (enum CAttributesTextGS::InvertAxis)(m_CTextAttributes.m_enumInvertAxis & CAttributesTextGS::IA_Axis_Y);
}
void C_GSLabel::ImageXAxis(const enum CAttributesImageGS::InvertAxis XAxis)
{ DWORD enumAxis = m_CImageAttributes.m_enumInvertAxis;
  enumAxis &= 0x0002;
  enumAxis |= XAxis;
  m_CImageAttributes.m_enumInvertAxis = (enum CAttributesImageGS::InvertAxis)enumAxis;
}
enum CAttributesImageGS::InvertAxis C_GSLabel::ImageXAxis(void) const
{return (enum CAttributesImageGS::InvertAxis)(m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_X);
}
void C_GSLabel::ImageYAxis(const enum CAttributesImageGS::InvertAxis YAxis)
{ DWORD enumAxis = m_CImageAttributes.m_enumInvertAxis;
  enumAxis &= 0x0001;
  enumAxis |= YAxis;
  m_CImageAttributes.m_enumInvertAxis = (enum CAttributesImageGS::InvertAxis)enumAxis;
}
enum CAttributesImageGS::InvertAxis C_GSLabel::ImageYAxis(void) const
{return (enum CAttributesImageGS::InvertAxis)(m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_Y);
}

// Drawing functions (protected members )
void C_GSLabel::Draw(CDC& dc,const CRect& rect)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst draw only on valid devices
	}
  if( rect.IsRectEmpty() )
    { return; // Thou shallst draw only if there is room
	}
  if( rect.bottom <= rect.top || rect.right <= rect.left )
    { return; // Thou shallst not draw in negative spaces
	}
  CRect rectText = CalculateTextRect(dc,rect);
  DrawBorder(dc, rect);
  DrawFrame (dc, rect);
  DrawImage (dc, rectText);
  DrawText  (dc, rectText);
}

CRect C_GSLabel::CalculateTextRect(CDC& dc, const CRect& rect)
{ CRect rectText(rect);
  rectText = m_CTextAttributes.CalculateTextRect(dc,rect,true);
  return (rectText);
}

void C_GSLabel::DrawBorder(CDC& dc, const CRect& rect)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst not draw on plain air
	}
  if( rect.IsRectEmpty() )
    { return; // Thou shallst not draw only on empty spaces
	}
  if( rect.bottom <= rect.top || rect.right <= rect.left )
    { return; // Thou shallst not draw outside of your paper
	}
  enum CAttributesTextGS::BorderLines eBorderLines = CAttributesTextGS::BL_without;
  eBorderLines = m_CTextAttributes.BorderLines();
  if( CAttributesTextGS::BL_without == eBorderLines )
    { return;
	}
// GDI objects
  CPen    *pOldPen;
  CPen    *pBorderPen = new CPen;

  pBorderPen->CreatePen(PS_SOLID,0,BorderColor());
  pOldPen = dc.SelectObject(pBorderPen);
  CSize DevSize(1,1);// The border is always one pixel wide
  dc.DPtoLP(&DevSize);

// Draw the border ( without corner points )
  CPoint Point;
  if( (eBorderLines & CAttributesTextGS::BL_Left) == CAttributesTextGS::BL_Left ) // Draw borderline to the left
    { Point.x = rect.left;
	  Point.y = rect.top;
	  if( (eBorderLines & CAttributesTextGS::BL_Top) == CAttributesTextGS::BL_Top )
		{ Point.y += DevSize.cy;
		}
	      dc.MoveTo(Point);
		  Point.y = rect.bottom;
      if( (eBorderLines & CAttributesTextGS::BL_Bottom) == CAttributesTextGS::BL_Bottom )
		{ Point.y -= DevSize.cy;
		}
	  dc.LineTo(Point);
	}
  if( (eBorderLines & CAttributesTextGS::BL_Right) == CAttributesTextGS::BL_Right ) // Draw borderline to the right
    { Point.x = rect.right - DevSize.cx;
	  Point.y = rect.top;
	  if( (eBorderLines & CAttributesTextGS::BL_Top) == CAttributesTextGS::BL_Top )
		{ Point.y += DevSize.cy;
		}
	  dc.MoveTo(Point);
	  Point.y = rect.bottom;
      if( (eBorderLines & CAttributesTextGS::BL_Bottom) == CAttributesTextGS::BL_Bottom )
		{ Point.y -= DevSize.cy;
		}
	  dc.LineTo(Point);
	}
  if( (eBorderLines & CAttributesTextGS::BL_Top) == CAttributesTextGS::BL_Top ) // Draw borderline at the top
    { Point.x = rect.left;
	  Point.y = rect.top;
	  if( (eBorderLines & CAttributesTextGS::BL_Left) == CAttributesTextGS::BL_Left )
		{ Point.x += DevSize.cx;
		}
	  dc.MoveTo(Point);
	  Point.x = rect.right;
      if( (eBorderLines & CAttributesTextGS::BL_Right) == CAttributesTextGS::BL_Right )
		{ Point.x -= DevSize.cx;
		}
	  dc.LineTo(Point);
	}
  if( (eBorderLines & CAttributesTextGS::BL_Bottom) == CAttributesTextGS::BL_Bottom ) // Draw borderline at the bottom
    { Point.x = rect.left;
	  Point.y = rect.bottom - DevSize.cy;
	  if( (eBorderLines & CAttributesTextGS::BL_Left) == CAttributesTextGS::BL_Left )
		{ Point.x += DevSize.cx;
		}
	  dc.MoveTo(Point);
	  Point.x = rect.right;
      if( (eBorderLines & CAttributesTextGS::BL_Right) == CAttributesTextGS::BL_Right )
		{ Point.x -= DevSize.cx;
		}
	  dc.LineTo(Point);
	}

// dissolve GDI objects
  dc.SelectObject(pOldPen);
  pBorderPen->DeleteObject();
  delete pBorderPen;
  pBorderPen = NULL;
}

void C_GSLabel::DrawFrame(CDC& dc, const CRect& rect)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst not draw on plain air
	  }
  if( rect.IsRectEmpty() )
    { return; // Thou shallst not draw on empty spaces
	  }
  if( rect.bottom <= rect.top || rect.right <= rect.left )
    { return; // Thou shallst not draw outside of your paper
	  }
  CRect rectOuterFrame = rect;
  CRect rectFrame      = rect;
  CRect rectInnerFrame = rect;
  enum CAttributesTextGS::BorderLines      eBorderLines     = CAttributesTextGS::BL_without;
  enum CAttributesTextGS::OuterFrameLines  eOuterFrameLines = CAttributesTextGS::OF_without;
  enum CAttributesTextGS::FrameLines       eFrameLines      = CAttributesTextGS::FL_without;
  enum CAttributesTextGS::InnerFrameLines  eInnerFrameLines = CAttributesTextGS::IF_without;
  enum CAttributesTextGS::Frame3DStyle     eOuter3DStyle    = CAttributesTextGS::D3_without;
  enum CAttributesTextGS::Frame3DStyle     eMiddle3DStyle   = CAttributesTextGS::D3_without;
  enum CAttributesTextGS::Frame3DStyle     eInner3DStyle    = CAttributesTextGS::D3_without;
  enum CAttributesTextGS::FrameCorners     eCorners         = CAttributesTextGS::FC_without;
  enum CAttributesTextGS::FrameCorners     eCornersConnect  = CAttributesTextGS::FC_without;

  eBorderLines     = m_CTextAttributes.BorderLines();
  eOuterFrameLines = m_CTextAttributes.OuterFrameLines();
  eFrameLines      = m_CTextAttributes.FrameLines();
  eInnerFrameLines = m_CTextAttributes.InnerFrameLines();
  eOuter3DStyle    = (enum CAttributesTextGS::Frame3DStyle)(m_CTextAttributes.m_enum3DStyle & 0x000F);
  eMiddle3DStyle   = (enum CAttributesTextGS::Frame3DStyle)(m_CTextAttributes.m_enum3DStyle & 0x0F00);
  eInner3DStyle    = (enum CAttributesTextGS::Frame3DStyle)(m_CTextAttributes.m_enum3DStyle & 0x00F0);
  eCorners         = (enum CAttributesTextGS::FrameCorners)(m_CTextAttributes.m_enumCorners & 0x000F);
  eCornersConnect  = (enum CAttributesTextGS::FrameCorners)(m_CTextAttributes.m_enumCorners & 0x0FF0);
// Do we have to adjust for the border line?
  if( CAttributesTextGS::BL_without != eBorderLines ) // Yes we do
    { CSize BorderSize(1,1); // The border is always one pixel wide
	    dc.DPtoLP(&BorderSize);
      if( (eBorderLines & CAttributesTextGS::BL_Left) == CAttributesTextGS::BL_Left )
		    { rectOuterFrame.left += BorderSize.cx; // Adjust frame rect for the left borderline
		    }
      if( (eBorderLines & CAttributesTextGS::BL_Top) == CAttributesTextGS::BL_Top )
		    { rectOuterFrame.top += BorderSize.cy; // Adjust frame rect for the top borderline
		    }
      if( (eBorderLines & CAttributesTextGS::BL_Right) == CAttributesTextGS::BL_Right )
		    { rectOuterFrame.right -= BorderSize.cx; // Adjust frame rect for the right borderline
		    }
      if( (eBorderLines & CAttributesTextGS::BL_Bottom) == CAttributesTextGS::BL_Bottom )
		    { rectOuterFrame.bottom -= BorderSize.cy; // Adjust frame rect for the bottom borderline
		    }
	  }
// Now adjust the other frame rectangles as well
  rectFrame = rectOuterFrame;
  // Do we have to adjust for the outer frame lines?
  if( CAttributesTextGS::OF_without != eOuterFrameLines ) // Yes we do
    { CRect rectAdjust(m_CTextAttributes.m_widthsOuterFrame);
	    dc.DPtoLP(&rectAdjust);
	    if( (eOuterFrameLines & CAttributesTextGS::OF_Left) == CAttributesTextGS::OF_Left)
		    { rectFrame.left += rectAdjust.left; // Adjust text rect for the left outer frame line
		    }
      if( (eOuterFrameLines & CAttributesTextGS::OF_Top) == CAttributesTextGS::OF_Top )
		    { rectFrame.top += rectAdjust.top; // Adjust text rect for the top outer frame line
		    }
      if( (eOuterFrameLines & CAttributesTextGS::OF_Right) == CAttributesTextGS::OF_Right )
		    { rectFrame.right -= rectAdjust.right; // Adjust text rect for the right outer frame line
		    }
      if( (eOuterFrameLines & CAttributesTextGS::OF_Bottom) == CAttributesTextGS::OF_Bottom )
		    { rectFrame.bottom -= rectAdjust.bottom; // Adjust text rect for the bottom outer frame line
		    }
	  }
  rectInnerFrame = rectFrame;
  // Do we have to adjust for the inner frame lines?
  if( CAttributesTextGS::FL_without != eFrameLines ) // Yes we do
    { CRect rectAdjust(m_CTextAttributes.m_widthsFrame);
	    dc.DPtoLP(&rectAdjust);
      if( (eFrameLines & CAttributesTextGS::FL_Left) == CAttributesTextGS::FL_Left )
		    { rectInnerFrame.left += rectAdjust.left; // Adjust text rect for the left frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Top) == CAttributesTextGS::FL_Top )
		    { rectInnerFrame.top += rectAdjust.top; // Adjust text rect for the top frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Right) == CAttributesTextGS::FL_Right )
		    { rectInnerFrame.right -=rectAdjust .right; // Adjust text rect for the right frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Bottom) == CAttributesTextGS::FL_Bottom )
		    { rectInnerFrame.bottom -= rectAdjust.bottom; // Adjust text rect for the bottom frame line
		    }
	  }

  CPoint Point;
  if( CAttributesTextGS::BL_without != eBorderLines )
    { DrawBorder(dc,rect);
    }
  if(    (CAttributesTextGS::OF_without == eOuterFrameLines)
      && (CAttributesTextGS::FL_without == eFrameLines)
      && (CAttributesTextGS::IF_without == eInnerFrameLines)
      && (CAttributesTextGS::FC_without == eCorners)
      && (CAttributesTextGS::FC_without == eCornersConnect)
    )// no frame work, no do
    { return;
    }
  if(CAttributesTextGS::FC_without != eCorners)
    { dc.FillSolidRect(&rectOuterFrame,BackgroundColor());
      // Normally the background will be erased when drawing text
      // but because of corners it is done here
    }
     
   CBrush OuterFrameBrushLeft,OuterFrameBrushTop,OuterFrameBrushRight,OuterFrameBrushBottom;
   CBrush MiddleFrameBrushLeft,MiddleFrameBrushTop,MiddleFrameBrushRight,MiddleFrameBrushBottom;
   CBrush InnerFrameBrushLeft,InnerFrameBrushTop,InnerFrameBrushRight,InnerFrameBrushBottom;
   COLORREF clrDark,clrLight,clrDarker,clrLighter;
   // Creating the brushes for the outer frame part
   clrDark    = CAttributesTextGS::DarkColor(OuterFrameColor());
   clrDarker  = CAttributesTextGS::DarkerColor(OuterFrameColor());
   clrLight   = CAttributesTextGS::LightColor(OuterFrameColor());
   clrLighter = CAttributesTextGS::LighterColor(OuterFrameColor());
	 if( CAttributesTextGS::D3_OutRaised == eOuter3DStyle )
     { OuterFrameBrushLeft.CreateSolidBrush(clrLight);
       OuterFrameBrushTop.CreateSolidBrush(clrLighter);
       OuterFrameBrushRight.CreateSolidBrush(clrDark);
       OuterFrameBrushBottom.CreateSolidBrush(clrDarker);
     }
   else
     { if( CAttributesTextGS::D3_OutSunken == eOuter3DStyle )
         { OuterFrameBrushLeft.CreateSolidBrush(clrDark);
           OuterFrameBrushTop.CreateSolidBrush(clrDarker);
           OuterFrameBrushRight.CreateSolidBrush(clrLight);
           OuterFrameBrushBottom.CreateSolidBrush(clrLighter);
         }
      else
         { OuterFrameBrushLeft.CreateSolidBrush(OuterFrameColor());
           OuterFrameBrushTop.CreateSolidBrush(OuterFrameColor());
           OuterFrameBrushRight.CreateSolidBrush(OuterFrameColor());
           OuterFrameBrushBottom.CreateSolidBrush(OuterFrameColor());
         }   
     }
   // Creating the brushes for the middle frame part
   clrDark    = CAttributesTextGS::DarkColor(FrameColor());
   clrDarker  = CAttributesTextGS::DarkerColor(FrameColor());
   clrLight   = CAttributesTextGS::LightColor(FrameColor());
   clrLighter = CAttributesTextGS::LighterColor(FrameColor());
	 if( CAttributesTextGS::D3_MidRaised == eMiddle3DStyle )
     { MiddleFrameBrushLeft.CreateSolidBrush(clrLight);
       MiddleFrameBrushTop.CreateSolidBrush(clrLighter);
       MiddleFrameBrushRight.CreateSolidBrush(clrDark);
       MiddleFrameBrushBottom.CreateSolidBrush(clrDarker);
     }
   else
     { if( CAttributesTextGS::D3_MidSunken == eMiddle3DStyle )
         { MiddleFrameBrushLeft.CreateSolidBrush(clrDark);
           MiddleFrameBrushTop.CreateSolidBrush(clrDarker);
           MiddleFrameBrushRight.CreateSolidBrush(clrLight);
           MiddleFrameBrushBottom.CreateSolidBrush(clrLighter);
         }
      else
         { MiddleFrameBrushLeft.CreateSolidBrush(FrameColor());
           MiddleFrameBrushTop.CreateSolidBrush(FrameColor());
           MiddleFrameBrushRight.CreateSolidBrush(FrameColor());
           MiddleFrameBrushBottom.CreateSolidBrush(FrameColor());
         }   
     }
   // Creating the brushes for the inner frame part
   clrDark    = CAttributesTextGS::DarkColor(InnerFrameColor());
   clrDarker  = CAttributesTextGS::DarkerColor(InnerFrameColor());
   clrLight   = CAttributesTextGS::LightColor(InnerFrameColor());
   clrLighter = CAttributesTextGS::LighterColor(InnerFrameColor());
	 if( CAttributesTextGS::D3_InRaised == eInner3DStyle )
     { InnerFrameBrushLeft.CreateSolidBrush(clrLight);
       InnerFrameBrushTop.CreateSolidBrush(clrLighter);
       InnerFrameBrushRight.CreateSolidBrush(clrDark);
       InnerFrameBrushBottom.CreateSolidBrush(clrDarker);
     }
   else
     { if( CAttributesTextGS::D3_InSunken == eInner3DStyle )
         { InnerFrameBrushLeft.CreateSolidBrush(clrDark);
           InnerFrameBrushTop.CreateSolidBrush(clrDarker);
           InnerFrameBrushRight.CreateSolidBrush(clrLight);
           InnerFrameBrushBottom.CreateSolidBrush(clrLighter);
         }
      else
         { InnerFrameBrushLeft.CreateSolidBrush(InnerFrameColor());
           InnerFrameBrushTop.CreateSolidBrush(InnerFrameColor());
           InnerFrameBrushRight.CreateSolidBrush(InnerFrameColor());
           InnerFrameBrushBottom.CreateSolidBrush(InnerFrameColor());
         }   
     }

// Painting the outer frame
  if( CAttributesTextGS::OF_without != eOuterFrameLines )
    { CBrush *pBrush = dc.SelectObject(&OuterFrameBrushLeft);
      CRect rectAdjust(m_CTextAttributes.m_widthsOuterFrame);
	    dc.DPtoLP(&rectAdjust);
      if( ((eOuterFrameLines & CAttributesTextGS::OF_Left) == CAttributesTextGS::OF_Left)
			    && (m_CTextAttributes.m_widthsOuterFrame.left > 0) )
		    { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectOuterFrame.left;
		      Point.y = rectOuterFrame.top;
		      dc.MoveTo(Point);
          // Second point of the path ( left bottom corner )
		      Point.y = rectOuterFrame.bottom;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
		      Point.x = rectOuterFrame.left + rectAdjust.left;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Bottom) == CAttributesTextGS::OF_Bottom )
			      { Point.y -= rectAdjust.bottom;
			      }
		      dc.LineTo(Point);
		      // Fourth point of the path (right top corner )
		      Point.y = rectOuterFrame.top;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Top) == CAttributesTextGS::OF_Top )
			      { Point.y += rectAdjust.top;
			      }
		      dc.LineTo(Point);
		      dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&OuterFrameBrushTop);
	    if( ((eOuterFrameLines & CAttributesTextGS::OF_Top) == CAttributesTextGS::OF_Top)
			    && (m_CTextAttributes.m_widthsOuterFrame.top > 0) )
		    { dc.BeginPath();
          // Startpoint of the path (top left corner)
		      Point.x = rectOuterFrame.left;
		      Point.y = rectOuterFrame.top;
		      dc.MoveTo(Point);
          // Second point of the path ( top right corner )
		      Point.x = rectOuterFrame.right;
		      dc.LineTo(Point);
		      // Third point of the path (bottom right corner )
		      Point.y = rectOuterFrame.top + rectAdjust.top;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Right) == CAttributesTextGS::OF_Right )
			      { Point.x -= rectAdjust.right;
			      }
		      dc.LineTo(Point);
		      // Fourth point of the path (bottom right corner )
		      Point.x = rectOuterFrame.left;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Left) == CAttributesTextGS::OF_Left )
		        { Point.x += rectAdjust.left;
		        }
		      dc.LineTo(Point);
		      dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&OuterFrameBrushRight);
	    if( ((eOuterFrameLines & CAttributesTextGS::OF_Right) == CAttributesTextGS::OF_Right)
	        && (m_CTextAttributes.m_widthsOuterFrame.right > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectOuterFrame.right - rectAdjust.right;
	        Point.y = rectOuterFrame.top;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Top) == CAttributesTextGS::OF_Top )
		        { Point.y += rectAdjust.top;
		        }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectOuterFrame.right;
	        Point.y = rectOuterFrame.top;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
          Point.y = rectOuterFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
          Point.x = rectOuterFrame.right - rectAdjust.right;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Bottom) == CAttributesTextGS::OF_Bottom )
		        { Point.y -= rectAdjust.bottom;
		        }
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&OuterFrameBrushBottom);
	    if( ((eOuterFrameLines & CAttributesTextGS::OF_Bottom) == CAttributesTextGS::OF_Bottom)
	        && (m_CTextAttributes.m_widthsOuterFrame.bottom > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectOuterFrame.left;
	        Point.y = rectOuterFrame.bottom -rectAdjust .bottom;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Left) == CAttributesTextGS::OF_Left )
		        { Point.x += rectAdjust.left;
			      }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectOuterFrame.right;
		      if( (eOuterFrameLines & CAttributesTextGS::OF_Right) == CAttributesTextGS::OF_Right )
		        { Point.x -= rectAdjust.right;
			      }
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
		      Point.x = rectOuterFrame.right;
          Point.y = rectOuterFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
		      Point.x = rectOuterFrame.left;
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	  }// if( OF_without != OuterFrameLines )
// Painting the frame
  if( CAttributesTextGS::FL_without != eFrameLines )
    { CBrush *pBrush = dc.SelectObject(&MiddleFrameBrushLeft);
      CRect rectAdjust(m_CTextAttributes.m_widthsFrame);
	    dc.DPtoLP(&rectAdjust);
	    if( ((eFrameLines & CAttributesTextGS::FL_Left) == CAttributesTextGS::FL_Left)
	        && (m_CTextAttributes.m_widthsFrame.left > 0) )
		    { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectFrame.left;
		      Point.y = rectFrame.top;
		      dc.MoveTo(Point);
          // Second point of the path ( left bottom corner )
		      Point.y = rectFrame.bottom;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
		      Point.x = rectFrame.left + rectAdjust.left;
		      if( (eFrameLines & CAttributesTextGS::FL_Bottom) == CAttributesTextGS::FL_Bottom )
			      { Point.y -= rectAdjust.bottom;
			      }
		      dc.LineTo(Point);
		      // Fourth point of the path (right top corner )
		      Point.y = rectFrame.top;
		      if( (eFrameLines & CAttributesTextGS::FL_Top) == CAttributesTextGS::FL_Top )
			      { Point.y += rectAdjust.top;
			      }
		      dc.LineTo(Point);
		      dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&MiddleFrameBrushTop);
	    if( ((eFrameLines & CAttributesTextGS::FL_Top) == CAttributesTextGS::FL_Top)
			    && (m_CTextAttributes.m_widthsFrame.top > 0) )
		    { dc.BeginPath();
          // Startpoint of the path (top left corner)
		      Point.x = rectFrame.left;
		      Point.y = rectFrame.top;
		      dc.MoveTo(Point);
          // Second point of the path ( top right corner )
		      Point.x = rectFrame.right;
		      dc.LineTo(Point);
		      // Third point of the path (bottom right corner )
		      Point.y = rectFrame.top + rectAdjust.top;
		      if( (eFrameLines & CAttributesTextGS::FL_Right) == CAttributesTextGS::FL_Right )
			      { Point.x -= rectAdjust.right;
			      }
		      dc.LineTo(Point);
		      // Fourth point of the path (bottom right corner )
		      Point.x = rectFrame.left;
		      if( (eFrameLines & CAttributesTextGS::FL_Left) == CAttributesTextGS::FL_Left )
		        { Point.x += rectAdjust.left;
		        }
		      dc.LineTo(Point);
		      dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&MiddleFrameBrushRight);
	    if( ((eFrameLines & CAttributesTextGS::FL_Right) == CAttributesTextGS::FL_Right)
	      && (m_CTextAttributes.m_widthsFrame.right > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectFrame.right - rectAdjust.right;
	        Point.y = rectFrame.top;
		      if( (eFrameLines & CAttributesTextGS::FL_Top) == CAttributesTextGS::FL_Top )
		        { Point.y += rectAdjust.top;
		        }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectFrame.right;
	        Point.y = rectFrame.top;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
          Point.y = rectFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
          Point.x = rectFrame.right - rectAdjust.right;
		      if( (eFrameLines & CAttributesTextGS::FL_Bottom) == CAttributesTextGS::FL_Bottom )
		        { Point.y -= rectAdjust.bottom;
		        }
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&MiddleFrameBrushBottom);
	    if( ((eFrameLines & CAttributesTextGS::FL_Bottom) == CAttributesTextGS::FL_Bottom)
	      && (m_CTextAttributes.m_widthsFrame.bottom > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectFrame.left;
	        Point.y = rectFrame.bottom -rectAdjust .bottom;
		      if( (eFrameLines & CAttributesTextGS::FL_Left) == CAttributesTextGS::FL_Left )
		        { Point.x += rectAdjust.left;
			      }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectFrame.right;
		      if( (eFrameLines & CAttributesTextGS::FL_Right) == CAttributesTextGS::FL_Right )
		        { Point.x -= rectAdjust.right;
			      }
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
		      Point.x = rectFrame.right;
          Point.y = rectFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
		      Point.x = rectFrame.left;
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	   dc.SelectObject(pBrush);
	  }// if( FL_without != FrameLines )
// Painting the inner frame
  if( CAttributesTextGS::IF_without != eInnerFrameLines )
    { CBrush *pBrush = dc.SelectObject(&InnerFrameBrushLeft);
      CRect rectAdjust(m_CTextAttributes.m_widthsInnerFrame);
	    dc.DPtoLP(&rectAdjust);
	    if( ((eInnerFrameLines & CAttributesTextGS::IF_Left) == CAttributesTextGS::IF_Left)
	        && (m_CTextAttributes.m_widthsInnerFrame.left > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectInnerFrame.left;
	        Point.y = rectInnerFrame.top;
	        dc.MoveTo(Point);
          // Second point of the path ( left bottom corner )
		      Point.y = rectInnerFrame.bottom;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
          Point.x = rectInnerFrame.left + rectAdjust.left;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Bottom) == CAttributesTextGS::IF_Bottom )
            { Point.y -= rectAdjust.bottom;
			      }
  		    dc.LineTo(Point);
		       // Fourth point of the path (right top corner )
		      Point.y = rectInnerFrame.top;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Top) == CAttributesTextGS::IF_Top )
		        { Point.y += rectAdjust.top;
			      }
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&InnerFrameBrushTop);
	    if( ((eInnerFrameLines & CAttributesTextGS::IF_Top) == CAttributesTextGS::IF_Top)
	        && (m_CTextAttributes.m_widthsInnerFrame.top > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (top left corner)
          Point.x = rectInnerFrame.left;
	        Point.y = rectInnerFrame.top;
	        dc.MoveTo(Point);
          // Second point of the path ( top right corner )
		      Point.x = rectInnerFrame.right;
		      dc.LineTo(Point);
		      // Third point of the path (bottom right corner )
          Point.y = rectInnerFrame.top + rectAdjust.top;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Right) == CAttributesTextGS::IF_Right )
            { Point.x -= rectAdjust.right;
			      }
  		    dc.LineTo(Point);
		      // Fourth point of the path (bottom left corner )
		      Point.x = rectInnerFrame.left;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Left) == CAttributesTextGS::IF_Left )
		        { Point.x += rectAdjust.left;
			      }
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&InnerFrameBrushRight);
	    if( ((eInnerFrameLines & CAttributesTextGS::IF_Right) == CAttributesTextGS::IF_Right)
	        && (m_CTextAttributes.m_widthsInnerFrame.right > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectInnerFrame.right - rectAdjust.right;
	        Point.y = rectInnerFrame.top;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Top) == CAttributesTextGS::IF_Top )
		        { Point.y += rectAdjust.top;
			      }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectInnerFrame.right;
	        Point.y = rectInnerFrame.top;
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
          Point.y = rectInnerFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
          Point.x = rectInnerFrame.right - rectAdjust.right;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Bottom) == CAttributesTextGS::IF_Bottom )
		        { Point.y -= rectAdjust.bottom;
			      }
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		    }
	    dc.SelectObject(pBrush);
	    pBrush = dc.SelectObject(&InnerFrameBrushBottom);
	    if( ((eInnerFrameLines & CAttributesTextGS::IF_Bottom) == CAttributesTextGS::IF_Bottom)
	        && (m_CTextAttributes.m_widthsInnerFrame.bottom > 0) )
	      { dc.BeginPath();
          // Startpoint of the path (left top corner)
          Point.x = rectInnerFrame.left;
	        Point.y = rectInnerFrame.bottom - rectAdjust.bottom;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Left) == CAttributesTextGS::IF_Left )
		        { Point.x += rectAdjust.left;
			      }
	        dc.MoveTo(Point);
          // Second point of the path (right top corner )
		      Point.x = rectInnerFrame.right;
		      if( (eInnerFrameLines & CAttributesTextGS::IF_Right) == CAttributesTextGS::IF_Right )
		        { Point.x -= rectAdjust.right;
			      }
		      dc.LineTo(Point);
		      // Third point of the path (right bottom corner )
		      Point.x = rectInnerFrame.right;
          Point.y = rectInnerFrame.bottom;
  		    dc.LineTo(Point);
		      // Fourth point of the path (left bottom corner )
		      Point.x = rectInnerFrame.left;
		      dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		     }
	     dc.SelectObject(pBrush);
	  }// if( IF_without != InnerFrameLines )
// Painting connecting corners
  if( CAttributesTextGS::FC_without != eCorners )
    { CRect rectAdjustOuter  (m_CTextAttributes.m_widthsOuterFrame);
      CRect rectAdjustMiddle (m_CTextAttributes.m_widthsFrame);
      CRect rectAdjustInner (m_CTextAttributes.m_widthsInnerFrame);
      dc.DPtoLP(&rectAdjustOuter);
      dc.DPtoLP(&rectAdjustMiddle);
      dc.DPtoLP(&rectAdjustInner);
      if( (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
        { CBrush *pBrush = dc.SelectObject(&OuterFrameBrushBottom);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.top;
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top + rectAdjustInner.top);
          dc.MoveTo(Point);
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left + rectAdjustInner.left);
          dc.LineTo(Point);
          Point.x -= rectAdjustInner.left;
          Point.y -= rectAdjustInner.top;
          dc.LineTo(Point);
          Point.x  -= (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(MiddleFrameBrushBottom);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.top;
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top );
          dc.MoveTo(Point);
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.LineTo(Point);
          Point.x -= rectAdjustMiddle.left;
          Point.y -= rectAdjustMiddle.top;
          dc.LineTo(Point);
          Point.x  -= rectAdjustOuter.left;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(InnerFrameBrushBottom);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.y += rectAdjustOuter.top;
          dc.MoveTo(Point);
          Point.x += rectAdjustOuter.left;
          dc.LineTo(Point);
          Point.x -= rectAdjustOuter.left;
          Point.y -= rectAdjustOuter.top;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      
		      dc.SelectObject(&OuterFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.top;
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left + rectAdjustInner.left);
          dc.MoveTo(Point);
          Point.y += (rectAdjustOuter.bottom + rectAdjustMiddle.bottom + rectAdjustInner.bottom);
          dc.LineTo(Point);
          Point.x -= rectAdjustInner.left;
          Point.y -= rectAdjustInner.top;
          dc.LineTo(Point);
          Point.y -= (rectAdjustOuter.top + rectAdjustMiddle.top);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&MiddleFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.top;
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.MoveTo(Point);
          Point.y += (rectAdjustOuter.bottom + rectAdjustMiddle.bottom);
          dc.LineTo(Point);
          Point.x -= rectAdjustMiddle.left;
          Point.y -= rectAdjustMiddle.top;
          dc.LineTo(Point);
          Point.y -= rectAdjustOuter.top;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&InnerFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.top;
          dc.MoveTo(Point);
          Point.x += rectAdjustOuter.left;
          Point.y += rectAdjustOuter.top;
          dc.LineTo(Point);
          Point.y -= rectAdjustOuter.top;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
 		      dc.SelectObject(pBrush);
       }
      if( (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop )
        { CBrush *pBrush = dc.SelectObject(&OuterFrameBrushBottom);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top + rectAdjustInner.top);
          dc.MoveTo(Point);
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right + rectAdjustInner.right);
          dc.LineTo(Point);
          Point.x += rectAdjustInner.right;
          Point.y -= rectAdjustInner.top;
          dc.LineTo(Point);
          Point.x  += (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(MiddleFrameBrushBottom);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top );
          dc.MoveTo(Point);
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.LineTo(Point);
          Point.x += rectAdjustMiddle.right;
          Point.y -= rectAdjustMiddle.top;
          dc.LineTo(Point);
          Point.x  += rectAdjustOuter.right;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(InnerFrameBrushBottom);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          Point.y += rectAdjustOuter.top;
          dc.MoveTo(Point);
          Point.x -= rectAdjustOuter.right;
          dc.LineTo(Point);
          Point.x += rectAdjustOuter.right;
          Point.y -= rectAdjustOuter.top;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      
		      dc.SelectObject(&OuterFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right + rectAdjustInner.right);
          dc.MoveTo(Point);
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top + rectAdjustInner.top);
          dc.LineTo(Point);
          Point.x += rectAdjustInner.right;
          Point.y -= rectAdjustInner.top;
          dc.LineTo(Point);
          Point.y -= (rectAdjustOuter.top + rectAdjustMiddle.top);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&MiddleFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.MoveTo(Point);
          Point.y += (rectAdjustOuter.top + rectAdjustMiddle.top);
          dc.LineTo(Point);
          Point.x += rectAdjustMiddle.right;
          Point.y -= rectAdjustMiddle.top;
          dc.LineTo(Point);
          Point.y -= rectAdjustOuter.top;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&InnerFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.top;
          dc.MoveTo(Point);
          Point.x -= rectAdjustOuter.right;
          Point.y += rectAdjustOuter.top;
          dc.LineTo(Point);
          Point.y -= rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
 		      dc.SelectObject(pBrush);
 		    }  
      if( (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom )
        { CBrush *pBrush = dc.SelectObject(&OuterFrameBrushTop);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom + rectAdjustInner.bottom);
          dc.MoveTo(Point);
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right + rectAdjustInner.right);
          dc.LineTo(Point);
          Point.x += rectAdjustInner.right;
          Point.y += rectAdjustInner.bottom;
          dc.LineTo(Point);
          Point.x  += (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(MiddleFrameBrushTop);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom );
          dc.MoveTo(Point);
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.LineTo(Point);
          Point.x += rectAdjustMiddle.right;
          Point.y += rectAdjustMiddle.bottom;
          dc.LineTo(Point);
          Point.x  += rectAdjustOuter.right;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(InnerFrameBrushTop);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= rectAdjustOuter.bottom;
          dc.MoveTo(Point);
          Point.x -= rectAdjustOuter.right;
          dc.LineTo(Point);
          Point.x += rectAdjustOuter.right;
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      
		      dc.SelectObject(&OuterFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right + rectAdjustInner.right);
          dc.MoveTo(Point);
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom + rectAdjustInner.bottom);
          dc.LineTo(Point);
          Point.x += rectAdjustInner.right;
          Point.y += rectAdjustInner.bottom;
          dc.LineTo(Point);
          Point.y += (rectAdjustOuter.bottom + rectAdjustMiddle.bottom);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&MiddleFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.x -= (rectAdjustOuter.right + rectAdjustMiddle.right);
          dc.MoveTo(Point);
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom);
          dc.LineTo(Point);
          Point.x += rectAdjustMiddle.right;
          Point.y += rectAdjustMiddle.bottom;
          dc.LineTo(Point);
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&InnerFrameBrushLeft);
          dc.BeginPath();
          Point.x  = rectOuterFrame.right;
          Point.y  = rectOuterFrame.bottom;
          Point.x -= rectAdjustOuter.right;
          dc.MoveTo(Point);
          Point.y -= rectAdjustOuter.bottom;
          dc.LineTo(Point);
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
 		      dc.SelectObject(pBrush);
 		    }  
      if( (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom )
        { CBrush *pBrush = dc.SelectObject(&OuterFrameBrushTop);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom + rectAdjustInner.bottom);
          dc.MoveTo(Point);
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left + rectAdjustInner.left);
          dc.LineTo(Point);
          Point.x -= rectAdjustInner.left;
          Point.y += rectAdjustInner.bottom;
          dc.LineTo(Point);
          Point.x  -= (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(MiddleFrameBrushTop);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom );
          dc.MoveTo(Point);
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.LineTo(Point);
          Point.x -= rectAdjustMiddle.left;
          Point.y += rectAdjustMiddle.bottom;
          dc.LineTo(Point);
          Point.x  -= rectAdjustOuter.left;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
          dc.SelectObject(InnerFrameBrushTop);//
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.y -= rectAdjustOuter.bottom;
          dc.MoveTo(Point);
          Point.x += rectAdjustOuter.left;
          dc.LineTo(Point);
          Point.x -= rectAdjustOuter.left;
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      
		      dc.SelectObject(&OuterFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left + rectAdjustInner.left);
          dc.MoveTo(Point);
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom + rectAdjustInner.bottom);
          dc.LineTo(Point);
          Point.x -= rectAdjustInner.left;
          Point.y += rectAdjustInner.bottom;
          dc.LineTo(Point);
          Point.y += (rectAdjustOuter.bottom + rectAdjustMiddle.bottom);
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&MiddleFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.x += (rectAdjustOuter.left + rectAdjustMiddle.left);
          dc.MoveTo(Point);
          Point.y -= (rectAdjustOuter.bottom + rectAdjustMiddle.bottom);
          dc.LineTo(Point);
          Point.x -= rectAdjustMiddle.left;
          Point.y += rectAdjustMiddle.bottom;
          dc.LineTo(Point);
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
		      dc.SelectObject(&InnerFrameBrushRight);
          dc.BeginPath();
          Point.x  = rectOuterFrame.left;
          Point.y  = rectOuterFrame.bottom;
          Point.x += rectAdjustOuter.left;
          dc.MoveTo(Point);
          Point.y -= rectAdjustOuter.bottom;
          dc.LineTo(Point);
          Point.y += rectAdjustOuter.bottom;
          dc.LineTo(Point);
          dc.CloseFigure(); // Make it a polygon
		      dc.EndPath();
		      dc.FillPath();
 		      dc.SelectObject(pBrush);
       }
  }	 
// Painting connection for frames
  if( CAttributesTextGS::FC_without != eCornersConnect )
    {
    }	 
  OuterFrameBrushLeft.DeleteObject();
  OuterFrameBrushTop.DeleteObject();
  OuterFrameBrushRight.DeleteObject();
  OuterFrameBrushBottom.DeleteObject();
  MiddleFrameBrushLeft.DeleteObject();
  MiddleFrameBrushTop.DeleteObject();
  MiddleFrameBrushRight.DeleteObject();
  MiddleFrameBrushBottom.DeleteObject();
  InnerFrameBrushLeft.DeleteObject();
  InnerFrameBrushTop.DeleteObject();
  InnerFrameBrushRight.DeleteObject();
  InnerFrameBrushBottom.DeleteObject();
}

void C_GSLabel::DrawImage(CDC& dc, const CRect& rect)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst not paint on plain air
		}
  if( rect.IsRectEmpty() )
    { return; // Thou shallst not paint on empty spaces
		}
  if( rect.bottom <= rect.top || rect.right <= rect.left )
    { return; // Thou shallst not paint beside the paper
		}
  if( m_CImageAttributes.m_enumBackImage == CAttributesImageGS::BI_without || m_CImageAttributes.m_bmpBackground.GetSafeHandle() == NULL )
    { return; // Thou only shallst paint pictures
		}
  CRect rectPadding(m_CTextAttributes.m_widthsPadding);
  CRect rectBitmap(rect);
  CSize bmpDrawSize(m_CImageAttributes.m_bmpInfo.bmWidth,m_CImageAttributes.m_bmpInfo.bmHeight);
  CDC*	pDCTemp = new CDC;
  pDCTemp->CreateCompatibleDC( &dc );
  SetGraphicsMode(pDCTemp->GetSafeHdc(),GM_ADVANCED);
  pDCTemp->SetMapMode(MM_ANISOTROPIC);
  pDCTemp->SetBkMode(TRANSPARENT);
  pDCTemp->SetWindowOrg(0, 0);
  pDCTemp->SetWindowExt(1440,1440);
  pDCTemp->SetViewportOrg(0, 0);
  //CSize sizeMonitor(dc.GetDeviceCaps(HORZSIZE),dc.GetDeviceCaps(VERTSIZE));
  //CSize sizeResMonitor(dc.GetDeviceCaps(HORZRES),dc.GetDeviceCaps(VERTRES));

  pDCTemp->SetViewportExt(pDCTemp->GetDeviceCaps(LOGPIXELSX),
                          pDCTemp->GetDeviceCaps(LOGPIXELSY));
  // Select the bitmap into the temp device context
  // and adjust bitmap size to text area size if necessary
  pDCTemp->DPtoLP(&rectPadding);
  rectBitmap.InflateRect(rectPadding);// Padding is for text only!
  pDCTemp->DPtoLP(&bmpDrawSize);
  if( rectBitmap.Width() < bmpDrawSize.cx ) bmpDrawSize.cx = rectBitmap.Width();
  if( rectBitmap.Height() < bmpDrawSize.cy ) bmpDrawSize.cy = rectBitmap.Height();
  CBitmap* pOldBitmap = (CBitmap*) pDCTemp->SelectObject( &m_CImageAttributes.m_bmpBackground );
  // Smooth colours when stretching
  dc.SetStretchBltMode(STRETCH_HALFTONE);
  // Clear background
  dc.FillSolidRect(&rectBitmap,BackgroundColor());
  // Calculate window extension and window origin for different X/Y-axis directions
  int iOffsetX = 1440; // Window axis axtension / variables are multi purpose
  int iOffsetY = 1440;
  CSize bmpSize(m_CImageAttributes.m_bmpInfo.bmWidth,m_CImageAttributes.m_bmpInfo.bmHeight);
  if( CAttributesImageGS::IA_Axis_X == (m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_X) )
    { bmpSize.cx -=1;
	  iOffsetX = -1440;
	}
  if( CAttributesImageGS::IA_Axis_Y == (m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_Y) )
    { bmpSize.cy -=1;
	  iOffsetY = -1440;
	}
  pDCTemp->DPtoLP(&bmpSize);
  pDCTemp->SetWindowExt(iOffsetX,iOffsetY);
  iOffsetX = 0; // Window origin
  iOffsetY = 0;
  // Must be done here again because of DPtoLP
  if( CAttributesImageGS::IA_Axis_X == (m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_X) )
    { iOffsetX = bmpSize.cx;
	}
  if( CAttributesImageGS::IA_Axis_Y == (m_CImageAttributes.m_enumInvertAxis & CAttributesImageGS::IA_Axis_Y) )
    { iOffsetY = bmpSize.cy;
	}
  pDCTemp->SetWindowOrg(iOffsetX, iOffsetY);

  int iOriginX = rectBitmap.left;// Starting point for drawing
  int iOriginY = rectBitmap.top;
  iOffsetX = 0; // Offsets into bitmap
  iOffsetY = 0;
  int x1,y1;
  switch( m_CImageAttributes.m_enumBackImage )
  { default :
    case CAttributesImageGS::BI_StretchBlt :// Stretch the bitmap to fill the entire text area
         dc.StretchBlt( iOriginX, iOriginY, rectBitmap.Width(), rectBitmap.Height(), pDCTemp, iOffsetX, iOffsetY, bmpSize.cx, bmpSize.cy, SRCCOPY );
		 break;
	case CAttributesImageGS::BI_BestFit :// Fit the image into text area retain aspect ratio
	     { double dRatioText, dRatioImage, dRatio;
		   int iWidth,iHeight;
		   iWidth  = rectBitmap.Width();
		   iHeight = rectBitmap.Height();
		   dRatioImage = (double)m_CImageAttributes.m_bmpInfo.bmWidth/(double)m_CImageAttributes.m_bmpInfo.bmHeight;
		   dRatioText  = (double)iWidth/(double)iHeight;
		   if( dRatioImage > dRatioText )
			 { dRatio   = (double)iWidth/(double)m_CImageAttributes.m_bmpInfo.bmWidth;
		  	   iWidth   = rectBitmap.Width();
			   iHeight  = (int)(m_CImageAttributes.m_bmpInfo.bmHeight * dRatio);
			   iOriginY += (rectBitmap.Height() - iHeight)/2;
			 }
		   else
			 { dRatio  = (double)rectBitmap.Height()/(double)m_CImageAttributes.m_bmpInfo.bmHeight;
			   iHeight = rectBitmap.Height();
			   iWidth  = (int)(m_CImageAttributes.m_bmpInfo.bmWidth * dRatio);
			   iOriginX += (rectBitmap.Width() - iWidth)/2;
			 }
           dc.StretchBlt( iOriginX, iOriginY, iWidth, iHeight, pDCTemp, iOffsetX, iOffsetY, bmpSize.cx, bmpSize.cy, SRCCOPY );
		   break;
		 }
	case CAttributesImageGS::BI_Tile :// Tile the bitmap
		 if( bmpSize.cx > rectBitmap.Width() )
		   { iOffsetX += (bmpSize.cx-rectBitmap.Width())/2;
		   }
		 if( bmpSize.cy > rectBitmap.Height() )
		   { iOffsetY += (bmpSize.cy-rectBitmap.Height())/2;
		   }
		 for( y1 = iOriginY; y1 < rectBitmap.bottom; y1 += bmpSize.cy )
		    { int sizey = bmpDrawSize.cy;
			  if( y1 + sizey > rectBitmap.bottom )
			    { sizey = rectBitmap.bottom - y1;
				}
		      for( x1 = iOriginX; x1 < rectBitmap.right;  x1 += bmpSize.cx )
		         { int sizex = bmpDrawSize.cx;
			       if( x1 + sizex > rectBitmap.right )
				     { sizex = rectBitmap.right - x1;
					 }
			       dc.BitBlt( x1, y1, sizex, sizey, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
			     }
		    }
		 break;
	case CAttributesImageGS::BI_CenterLeft :// Center the bitmap to the left
		 if( bmpSize.cy < rectBitmap.Height() )
		   { iOriginY += (rectBitmap.Height()-bmpSize.cy)/2;
		   }
		 if( bmpSize.cy > rectBitmap.Height() )
		   { iOffsetY += (bmpSize.cy-rectBitmap.Height())/2;
		   }
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_Center :// Center the bitmap
	     if( bmpSize.cx < rectBitmap.Width() )
		   { iOriginX += (rectBitmap.Width()-bmpSize.cx)/2;
		   }
		 if( bmpSize.cy < rectBitmap.Height() )
		   { iOriginY += (rectBitmap.Height()-bmpSize.cy)/2;
		   }
		 if( bmpSize.cx > rectBitmap.Width() )
		   { iOffsetX += (bmpSize.cx-rectBitmap.Width())/2;
		   }
		 if( bmpSize.cy > rectBitmap.Height() )
		   { iOffsetY += (bmpSize.cy-rectBitmap.Height())/2;
		   }
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_CenterRight :// Center the bitmap to the right
		 if( bmpSize.cy < rectBitmap.Height() )
		   { iOriginY += (rectBitmap.Height()-bmpSize.cy)/2;
		   }
		 if( bmpSize.cy > rectBitmap.Height() )
		   { iOffsetY += (bmpSize.cy-rectBitmap.Height())/2;
		   }
	     if( bmpSize.cx > bmpDrawSize.cx )
		   { iOffsetX = bmpSize.cx - bmpDrawSize.cx;
		   }
		 iOriginX = rectBitmap.right - bmpDrawSize.cx;
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
		 break;
	case CAttributesImageGS::BI_TopLeft :// Place the bitmap into the top left corner, cut off excess part
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_TopCenter :// Place the bitmap centered at the top of the text area
	     if( bmpSize.cx < rectBitmap.Width() )
		   { iOriginX += (rectBitmap.Width()-bmpSize.cx)/2;
		   }
		 if( bmpSize.cx > rectBitmap.Width() )
		   { iOffsetX += (bmpSize.cx-rectBitmap.Width())/2;
		   }
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_TopRight :// Place the bitmap into the top right corner starting at top right corner of bitmap
	     if( bmpSize.cx > bmpDrawSize.cx )
		   { iOffsetX = bmpSize.cx - bmpDrawSize.cx;
		   }
		 iOriginX = rectBitmap.right - bmpDrawSize.cx;
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_BottomLeft :// Place the bitmap into the bottom left corner starting at bottom left corner of bitmap
	     if( bmpSize.cy > bmpDrawSize.cy )
		   { iOffsetY = bmpSize.cy - bmpDrawSize.cy;
		   }
		 iOriginY = rectBitmap.bottom - bmpDrawSize.cy;
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_BottomCenter :// Place the bitmap centered at the bottom of the text area
	     if( bmpSize.cx < rectBitmap.Width() )
		   { iOriginX += (rectBitmap.Width()-bmpSize.cx)/2;
		   }
		 if( bmpSize.cx > rectBitmap.Width() )
		   { iOffsetX += (bmpSize.cx-rectBitmap.Width())/2;
		   }
		 iOriginY = rectBitmap.bottom - bmpDrawSize.cy;
	     if( bmpSize.cy > bmpDrawSize.cy )
		   { iOffsetY = bmpSize.cy - bmpDrawSize.cy;
		   }
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
	case CAttributesImageGS::BI_BottomRight :// Place the bitmap into the bottom right corner starting at bottom right corner of bitmap
	     if( bmpSize.cx > bmpDrawSize.cx )
		   { iOffsetX = bmpSize.cx - bmpDrawSize.cx;
		   }
	     if( bmpSize.cy > bmpDrawSize.cy )
		   { iOffsetY = bmpSize.cy - bmpDrawSize.cy;
		   }
		 iOriginX = rectBitmap.right - bmpDrawSize.cx;
		 iOriginY = rectBitmap.bottom - bmpDrawSize.cy;
	     dc.BitBlt( iOriginX, iOriginY, bmpDrawSize.cx, bmpDrawSize.cy, pDCTemp, iOffsetX, iOffsetY, SRCCOPY );
         break;
    }
  pDCTemp->SelectObject( pOldBitmap );
  delete pDCTemp;
}
void C_GSLabel::DrawText(CDC& dc, const CRect& rect)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst not write on plain air
		}
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() == NULL )
    { m_CTextAttributes.m_ftDefault.CreateFontIndirect( &m_CTextAttributes.m_lfDefault );
    }
  if( m_CTextAttributes.m_ftDefault.GetSafeHandle() == NULL )
    { return; // Thou shallst not scribble
		}
  if( rect.IsRectEmpty() )
    { return; // Thou shallst not write on empty places
		}
  if( rect.bottom <= rect.top || rect.right <= rect.left )
    { return; // Thou shallst not write in negative spaces
		}
  TEXTMETRIC tmFont;
  int iLineHeight = 0;
  CString strParagraph = m_strText;
  CString strOutputLine = _T("");
  CFont *pOldFont = NULL;
  // Default settings
  dc.SetTextColor(TextColor());
  dc.SetTextAlign(TA_LEFT|TA_BASELINE|TA_NOUPDATECP);
  dc.SetTextJustification(0,0);
  pOldFont = dc.SelectObject(&m_CTextAttributes.m_ftDefault);
  dc.GetTextMetrics(&tmFont);
  // Get the height of a textline ( font height plus leading)
  iLineHeight = tmFont.tmHeight + tmFont.tmExternalLeading;
  // and clear the text area
  CRect rectInflate(m_CTextAttributes.m_widthsPadding);
  dc.DPtoLP(&rectInflate);
  CRect rectClear(rect);
  rectClear.InflateRect(rectInflate);
  // Check if it is save to clear the text background
  bool bDoFill = true;
  if( m_CImageAttributes.m_enumBackImage != CAttributesImageGS::BI_without
      && m_CImageAttributes.m_bmpBackground.GetSafeHandle() != NULL )
    { bDoFill = false; // We won't wipe out the background picture
	  }
  if( bDoFill)
    { CRect rectFill(rectClear);
      dc.FillSolidRect(&rectFill,BackgroundColor());
    }
  if( m_strText.IsEmpty() )
    { return; // Thou only shallst write if you got something to say
		}
  // protect the non-text area from being overwritten
  dc.LPtoDP(rectClear);
  CRgn rgnClip;
  rgnClip.CreateRectRgn(rectClear.left,rectClear.top,rectClear.right,rectClear.bottom);
  dc.SelectClipRgn(&rgnClip,RGN_COPY);

  CSize sizeRect  = rect.Size();
  CRect rectDraw(rect);
  CPoint ptTextStart(0,0);
  int iCountSpacesFront = 0;
  CSize sizeSpacesFront(0,0);
  for( int i = 0; i < strParagraph.GetLength(); i++ )
     { if( strParagraph.GetAt(i) == TCHAR(' ') )
         { iCountSpacesFront++;             
         }
       else
         { break;
         }  
     }
  if( iCountSpacesFront > 0 )
    { CString strEmpty(TCHAR(' '),iCountSpacesFront);
      sizeSpacesFront = dc.GetOutputTextExtent(strEmpty);
    }
  if( m_bPreserveFrontSpace && (iCountSpacesFront > 0) )
    { if( sizeRect.cx > sizeSpacesFront.cx )
        { rectDraw.left += sizeSpacesFront.cx;
          sizeRect  = rectDraw.Size();
#if _MSC_VER < 1500
          strParagraph = m_strText;
          strParagraph.TrimLeft();
          strParagraph.TrimRight();
#else
          strParagraph = m_strText.Trim();
#endif
        }
    }
// Calculate the starting point for text
  switch(m_CTextAttributes.m_lLineAngle)
  { default  :  // starting point is upper left corner
		  ptTextStart = CPoint(rectDraw.left,rectDraw.top + tmFont.tmAscent);
		  break;
    case CAttributesTextGS::LA_90Degree:  // starting point is lower left corner
		  ptTextStart = CPoint(rectDraw.left + tmFont.tmAscent,rectDraw.bottom);
		  break;
    case CAttributesTextGS::LA_180Degree:  // starting point is lower right corner
		  ptTextStart = CPoint(rectDraw.right,rectDraw.bottom - tmFont.tmAscent);
      break;
	  case CAttributesTextGS::LA_270Degree: // starting point is upper right corner
		  ptTextStart = CPoint(rectDraw.right  - tmFont.tmAscent ,rectDraw.top);
		  break;
  }
// Adjust for X/Y axis extensions
  int iOffsetX = 0;
  int iOffsetY = 0;
  int iExtX = 1440;
  int iExtY = 1440;
  if( CAttributesTextGS::IA_Axis_X == (m_CTextAttributes.m_enumInvertAxis & CAttributesTextGS::IA_Axis_X) )
    { iExtX    = -1440;
      switch(m_CTextAttributes.m_lLineAngle)
	    { default                              : iOffsetX = rectDraw.right + ptTextStart.x; break;
	      case CAttributesTextGS::LA_90Degree  : iOffsetX = rectDraw.right + rectDraw.left; break;
		    case CAttributesTextGS::LA_180Degree : iOffsetX = rectDraw.left  + ptTextStart.x; break;
		    case CAttributesTextGS::LA_270Degree : iOffsetX = rectDraw.right + rectDraw.left; break;
	    }
	  }
  if( CAttributesTextGS::IA_Axis_Y == (m_CTextAttributes.m_enumInvertAxis & CAttributesTextGS::IA_Axis_Y) )
    { iExtY    = -1440;
      switch(m_CTextAttributes.m_lLineAngle)
			{ default                              : iOffsetY = rectDraw.bottom + rectDraw.top; break;
			  case CAttributesTextGS::LA_90Degree  : iOffsetY = rectDraw.top    + ptTextStart.y; break;
			  case CAttributesTextGS::LA_180Degree : iOffsetY = rectDraw.bottom + rectDraw.top; break;
			  case CAttributesTextGS::LA_270Degree : iOffsetY = rectDraw.bottom + ptTextStart.y; break;
			}
	  }
  dc.SetWindowOrg(iOffsetX, iOffsetY);
  dc.SetWindowExt(iExtX,iExtY);
  
// Adjust the device mapping for the line angles
// default is a line angle of 0 degree
  int x = sizeRect.cx; // needed for swapping
  int iOffset = 0;
  switch(m_CTextAttributes.m_lLineAngle)
  { default  :  // starting point is upper left corner
		  m_CTextAttributes.CalculateTextHeight(dc,sizeRect.cx,strParagraph,false);
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Center)
		    { iOffset = (sizeRect.cy - m_CTextAttributes.TextHeight())/2;
		      ptTextStart.Offset(0, iOffset);
		    }
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Bottom)
		    { iOffset = sizeRect.cy - m_CTextAttributes.TextHeight();
			    ptTextStart.Offset(0, iOffset);
		    }
		  break;
    case CAttributesTextGS::LA_90Degree: // swap cx and cy
		  sizeRect.cx = sizeRect.cy;
		  sizeRect.cy = x;
		  m_CTextAttributes.CalculateTextHeight(dc,sizeRect.cx,strParagraph,false);
		  // starting point is lower left corner
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Center)
		    { iOffset = (sizeRect.cy - m_CTextAttributes.TextHeight())/2;
		 	    ptTextStart.Offset(iOffset, 0);
		    }
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Bottom)
		    { iOffset = sizeRect.cy - m_CTextAttributes.TextHeight();
		 	    ptTextStart.Offset(iOffset, 0);
		    }
      break;
    case CAttributesTextGS::LA_180Degree:  // starting point is lower right corner
		  m_CTextAttributes.CalculateTextHeight(dc,sizeRect.cx,strParagraph,false);
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Center)
		    { iOffset = (sizeRect.cy - m_CTextAttributes.TextHeight())/2;
		 	    ptTextStart.Offset(0, -iOffset);
		    }
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Bottom)
		    { iOffset = sizeRect.cy - m_CTextAttributes.TextHeight();
			    ptTextStart.Offset(0, -iOffset);
		    }
      break;
	  case CAttributesTextGS::LA_270Degree: // swap cx and cy
		  sizeRect.cx = sizeRect.cy;
		  sizeRect.cy = x;
		  m_CTextAttributes.CalculateTextHeight(dc,sizeRect.cx,strParagraph,false);
          // starting point is upper right corner
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Center)
			  { iOffset = (sizeRect.cy - m_CTextAttributes.TextHeight())/2;
			    ptTextStart.Offset(-iOffset, 0);
		    }
		  if( m_CTextAttributes.m_enumTVAlignment == CAttributesTextGS::TV_Bottom)
			  { iOffset = sizeRect.cy - m_CTextAttributes.TextHeight();
			    ptTextStart.Offset(-iOffset, 0);
			  }
		  break;
  }
// Write the text to the device
  CSize sizeText(0,0);
  int iLastChar   = 0;
  int iCountSpace = 0;
  bool bParagraphEnd = false;
  enum CAttributesTextGS::ParaAlign eAlignment;// Text alignment per line
  bool bCalculateSpaces = true; 
  while( strParagraph.GetLength()>0 )
       { CRect rectForDrawing(rectDraw);
         CSize sizeForDrawing(sizeRect);
         if( bCalculateSpaces && m_bPreserveFrontSpace )
           { iCountSpacesFront = 0;
             sizeSpacesFront   = CSize(0,0);
             for( int i = 0; i < strParagraph.GetLength(); i++ )
                { if( strParagraph.GetAt(i) == TCHAR(' ') )
                     { iCountSpacesFront++;             
                     }
                  else
                     { break;
                     }  
                }
             if( iCountSpacesFront > 0 )
               { CString strEmpty(TCHAR(' '),iCountSpacesFront);
                 sizeSpacesFront = dc.GetOutputTextExtent(strEmpty);
               }
             bCalculateSpaces = false;
           }
         if( m_bPreserveFrontSpace && (iCountSpacesFront > 0) )
           { if( sizeForDrawing.cx > sizeSpacesFront.cx )
               { rectForDrawing.left += sizeSpacesFront.cx;
                 sizeForDrawing  = rectForDrawing.Size();
#if _MSC_VER < 1500
                 strParagraph.TrimLeft();
#else
                 strParagraph = strParagraph.TrimLeft();
#endif
               }
            }
         bParagraphEnd = false;
		     sizeText  = CSize(0,0);
         // Retrieve the maximum count of characters, that will fit in one line
         // and then get the output text
		     iLastChar = m_CTextAttributes.CalculateLineCharCount(dc,sizeForDrawing.cx,strParagraph,false);
		     if( iLastChar < 1 )// Bail out, there's nothing to do and avoid looping endlessly
			     { break;
			     }
		     strOutputLine = strParagraph.Left(iLastChar);
		     if( strParagraph[iLastChar-1] == TCHAR('\n') )
		       { bParagraphEnd = true;
			       bCalculateSpaces = true;
		       }
		     // Get rid of soft hypens
		     strOutputLine.Replace(CString(TCHAR(0xAD)),_T(""));//TCHAR(0xAD)
		     strOutputLine.TrimRight();
		     if( strParagraph[iLastChar-1] == TCHAR(0xAD) )//TCHAR('­')
		       { //Place a hypen at the end if necessary
		         strOutputLine += TCHAR(0xAD);//TCHAR('­')
		       }
		     sizeText = dc.GetOutputTextExtent(strOutputLine);
		     // Now decide where to place the line
		     switch(m_CTextAttributes.m_enumParagraph )
		     { default:
		       case CAttributesTextGS::PA_Front:
		       case CAttributesTextGS::PA_Justify:
				   if( CAttributesTextGS::TR_RightToLeft == m_CTextAttributes.m_enumReading)
				     { eAlignment = CAttributesTextGS::PA_End;
				     }
				   else
				     { eAlignment = CAttributesTextGS::PA_Front;
				     }
				   break;
		       case CAttributesTextGS::PA_Center:
		       case CAttributesTextGS::PA_JustifyCenter:
				   eAlignment = CAttributesTextGS::PA_Center;
           break;
		       case CAttributesTextGS::PA_End:
		       case CAttributesTextGS::PA_JustifyEnd:
				   if( CAttributesTextGS::TR_RightToLeft == m_CTextAttributes.m_enumReading)
				     { eAlignment = CAttributesTextGS::PA_Front;
				     }
				   else
				     { eAlignment = CAttributesTextGS::PA_End;
				     }
				   break;
		     }
		     // Do the justification here. Count the spaces in the outputline and adjust space width
		     if( (iLastChar != strParagraph.GetLength() && !bParagraphEnd ) &&
			        CAttributesTextGS::PA_Justify == (m_CTextAttributes.m_enumParagraph & CAttributesTextGS::PA_Justify))
		       { //Do justification only if it is NOT the last line of a paragraph
			       iCountSpace = 0;
			       // iCountSpace = strOutputLine.Replace(TCHAR(' '),TCHAR(' ')); won't work
			       for( int i = 0; i < strOutputLine.GetLength() ; i++ )
				        { if( strOutputLine.GetAt(i) == TCHAR(' ') )
					{ iCountSpace++;
					}
				        }
			       dc.SetTextJustification(sizeForDrawing.cx - sizeText.cx,iCountSpace);
			       // Correct the line alignment
			       eAlignment = CAttributesTextGS::PA_Justify;
		       }
         if( CAttributesTextGS::PA_Center == eAlignment )
           { switch(m_CTextAttributes.m_lLineAngle)
             { default  : ptTextStart.x += (sizeForDrawing.cx-sizeText.cx)/2;
						              break;
			         case  CAttributesTextGS::LA_90Degree : 
			                    ptTextStart.y -= (sizeForDrawing.cx-sizeText.cx)/2;
						              break;
               case CAttributesTextGS::LA_180Degree : ptTextStart.x -= (sizeForDrawing.cx-sizeText.cx)/2;
						              break;
	             case CAttributesTextGS::LA_270Degree : 
	                        ptTextStart.y += (sizeForDrawing.cx-sizeText.cx)/2;
                          break;
             }
		       }
		     if(m_bPreserveFrontSpace)
		       { if( CAttributesTextGS::PA_Front == eAlignment )
               { switch(m_CTextAttributes.m_lLineAngle)
                 { default  : ptTextStart.x = rectForDrawing.left;
						                  break;
                   case  CAttributesTextGS::LA_90Degree :
                              ptTextStart.y = rectForDrawing.bottom;
						                  break;
                   case CAttributesTextGS::LA_180Degree : 
                              ptTextStart.x = rectForDrawing.right;
						                  break;
			             case CAttributesTextGS::LA_270Degree : 
			                        ptTextStart.y = rectForDrawing.top;
						                  break;
                 }
		           }
		       }
         if( CAttributesTextGS::PA_End == eAlignment )
           { switch(m_CTextAttributes.m_lLineAngle)
             { default  : ptTextStart.x += (sizeForDrawing.cx-sizeText.cx);
						              break;
               case  CAttributesTextGS::LA_90Degree :
                          ptTextStart.y -= (sizeForDrawing.cx-sizeText.cx);
						              break;
               case CAttributesTextGS::LA_180Degree : 
                          ptTextStart.x -= (sizeForDrawing.cx-sizeText.cx);
						              break;
			         case CAttributesTextGS::LA_270Degree : 
			                    ptTextStart.y += (sizeForDrawing.cx-sizeText.cx);
						              break;
             }
		       }
		     if( CAttributesTextGS::TR_RightToLeft == m_CTextAttributes.m_enumReading )
		       { strOutputLine.MakeReverse();
		       }
         dc.TextOut(ptTextStart.x,ptTextStart.y,strOutputLine);
         switch(m_CTextAttributes.m_lLineAngle) // Advance to a new line
         { default  : ptTextStart.y += iLineHeight;
					            ptTextStart.x  = rectForDrawing.left;
					            break;
           case  CAttributesTextGS::LA_90Degree :
                      ptTextStart.x += iLineHeight;
					            ptTextStart.y  = rectForDrawing.bottom;
                      break;
           case CAttributesTextGS::LA_180Degree :
                      ptTextStart.y -= iLineHeight;
                      ptTextStart.x  = rectForDrawing.right;
					             break;
		       case CAttributesTextGS::LA_270Degree :
		                  ptTextStart.x -= iLineHeight;
                      ptTextStart.y  = rectForDrawing.top;
                      break;
         }
         dc.SetTextJustification(0,0);
         strParagraph = strParagraph.Mid(iLastChar);
		     if( !bParagraphEnd )
           { strParagraph.TrimLeft(TCHAR(' '));
		       }
		     strParagraph.TrimLeft(TCHAR('­')); // soft hyphen
       }

  dc.SetTextJustification(0,0);
  dc.SelectObject(pOldFont);
  dc.SelectClipRgn(NULL);
  rgnClip.DeleteObject();
  dc.SetWindowOrg(0, 0);
  dc.SetWindowExt(1440,1440);
}

