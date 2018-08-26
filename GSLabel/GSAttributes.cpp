// GSAttributes.cpp: Implementierungsdatei
//

#include "stdafx.h"
// #include "resource.h"
#include "GSAttributes.h"
// #include "UTF16File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if _MSC_VER < 1400
#if !defined _UNICODE
#define _tcsncpy_s( source,size,dest,count) strncpy(source,dest,count)
#define _tstoi(strValue) atoi(strValue)
#define _itot_s(iValue,buffer,size,base)  _itoa(iValue,buffer,base)
#endif
#if defined _UNICODE
#define _tcsncpy_s( source,size,dest,count) wcsncpy(source,dest,count)
#define _tstoi(strValue) _wtoi(strValue)   
#define _itot_s(iValue,buffer,size,base)  _itow(iValue,buffer,base)
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// SAttributesTextGS
// structures for easier initialization
SAttributesTextGS& SAttributesTextGS::operator=(const SAttributesTextGS& attr)
{ if( this==&attr )
    { return (*this);
    }
  m_dwFrameStyle  = attr.m_dwFrameStyle;
  m_enum3DStyle   = attr.m_enum3DStyle;
  m_clrBackground = attr.m_clrBackground;
  m_clrBorder     = attr.m_clrBorder;
  m_clrOuterFrame = attr.m_clrOuterFrame;
  m_clrFrame      = attr.m_clrFrame;
  m_clrInnerFrame = attr.m_clrInnerFrame;

  m_rectOuterWidth   = attr.m_rectOuterWidth;
  m_rectMiddleWidth  = attr.m_rectMiddleWidth;
  m_rectInnerWidth   = attr.m_rectInnerWidth;
  m_rectPadding      = attr.m_rectPadding;
  _tcsncpy_s(m_strFontName,32,attr.m_strFontName,31);
  m_iFontSize   = attr.m_iFontSize;
  m_bBold       = attr.m_bBold;
  m_bItalic     = attr.m_bItalic;
  m_bUnderline  = attr.m_bUnderline;
  m_clrText     = attr.m_clrText;

  m_enumCharacterAngle = attr.m_enumCharacterAngle;
  m_enumLineAngle      = attr.m_enumLineAngle;
  m_enumReading        = attr.m_enumReading;
  m_enumTVAlignment    = attr.m_enumTVAlignment;
  m_enumParagraph      = attr.m_enumParagraph;
  m_enumCorners        = attr.m_enumCorners;
  return (*this);
}

SAttributesTextGS_Simple& SAttributesTextGS_Simple::operator=(const SAttributesTextGS_Simple& attr)
{ if( this==&attr )
    { return (*this);
    }
  m_dwFrameStyle  = attr.m_dwFrameStyle;
  m_enum3DStyle   = attr.m_enum3DStyle;
  m_clrBackground = attr.m_clrBackground;
  m_clrBorder     = attr.m_clrBorder;
  m_clrFrame      = attr.m_clrFrame;

  m_iOuterWidth   = attr.m_iOuterWidth;
  m_iMiddleWidth  = attr.m_iMiddleWidth;
  m_iInnerWidth   = attr.m_iInnerWidth;
  m_iPadding      = attr.m_iPadding;

  _tcsncpy_s(m_strFontName,32,attr.m_strFontName,31);
  m_iFontSize   = attr.m_iFontSize;
  m_bBold       = attr.m_bBold;
  m_bItalic     = attr.m_bItalic;
  m_bUnderline  = attr.m_bUnderline;
  m_clrText     = attr.m_clrText;

  m_enumTVAlignment    = attr.m_enumTVAlignment;
  m_enumParagraph      = attr.m_enumParagraph;
  return (*this);
}


/////////////////////////////////////////////////////////////////////////////
// CGSAttributes

CAttributesTextGS::CAttributesTextGS()
{ Initialize();
};

CAttributesTextGS::~CAttributesTextGS()
{ if( m_ftDefault.GetSafeHandle() != NULL )
    { m_ftDefault.DeleteObject();
    }
};

void CAttributesTextGS::Initialize(void)
{ // Colouring the Troops
  m_clrBackground = COLOR_BTNFACE | 0xFF000000;
  m_clrBorder     = COLOR_ACTIVEBORDER | 0xFF000000;
  m_clrFrame      = COLOR_3DFACE | 0xFF000000;
  m_clrOuterFrame = COLOR_3DFACE | 0xFF000000;
  m_clrInnerFrame = COLOR_3DFACE | 0xFF000000;
  m_clrText       = COLOR_BTNTEXT | 0xFF000000;
// Set the default font
  memset(&m_lfDefault,0,sizeof(LOGFONT));
  m_lfDefault.lfHeight		     = 240;// We're working with twips
  m_lfDefault.lfWidth		       = 0;
  m_lfDefault.lfEscapement	   = 0;
  m_lfDefault.lfOrientation	   = 0;
  m_lfDefault.lfWeight		     = FW_NORMAL;
  m_lfDefault.lfItalic		     = false;
  m_lfDefault.lfUnderline	     = false;
  m_lfDefault.lfStrikeOut	     = false;
  m_lfDefault.lfCharSet		     = ANSI_CHARSET;
  m_lfDefault.lfOutPrecision   = OUT_DEFAULT_PRECIS;
  m_lfDefault.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
  m_lfDefault.lfQuality		     = DEFAULT_QUALITY;
  m_lfDefault.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
  _tcsncpy_s(m_lfDefault.lfFaceName,32,_T("Arial"),31);

  m_widthsOuterFrame.SetRectEmpty(); // no frame(s)
  m_widthsFrame.SetRectEmpty();
  m_widthsInnerFrame.SetRectEmpty();
// Setting text formatting attributes
  m_enumReading     = TR_LeftToRight;
  m_enumTVAlignment = TV_Center;
  m_enumParagraph   = PA_Front;
  m_lCharacterAngle = m_lfDefault.lfOrientation;
  m_lLineAngle      = m_lfDefault.lfOrientation;
  m_enumInvertAxis  = IA_Axis_None;
  m_enumCorners     = FC_without;
// Setting frame style and text sizes
  m_lFrameStyle = 0;  // No Border, no frame
  m_enum3DStyle = D3_without;
  m_iLineHeight = 0;
  m_sizeTextRect = CSize(0,0);
  m_widthsPadding = CRect(1,1,1,1);
};

struct SAttributesTextGS CAttributesTextGS::AttributesTextGS(void)
{ SAttributesTextGS attr;

  attr.m_dwFrameStyle  = m_lFrameStyle;
  attr.m_enum3DStyle   = m_enum3DStyle;
  attr.m_clrBackground = m_clrBackground;
  attr.m_clrBorder     = m_clrBorder;
  attr.m_clrOuterFrame = m_clrOuterFrame;
  attr.m_clrFrame      = m_clrFrame;
  attr.m_clrInnerFrame = m_clrInnerFrame;

  attr.m_rectOuterWidth   = m_widthsOuterFrame;
  attr.m_rectMiddleWidth  = m_widthsFrame;
  attr.m_rectInnerWidth   = m_widthsInnerFrame;
  attr.m_rectPadding      = m_widthsPadding;

  _tcsncpy_s(attr.m_strFontName,32,m_lfDefault.lfFaceName,31);
  attr.m_iFontSize   = m_lfDefault.lfHeight/20;
  attr.m_bBold       = (m_lfDefault.lfWeight > FW_NORMAL);
  attr.m_bItalic     = (m_lfDefault.lfItalic != 0)? true : false;
  attr.m_bUnderline  = (m_lfDefault.lfUnderline != 0) ? true : false;
  attr.m_clrText     = m_clrText;

  switch(m_lCharacterAngle)
  { default   :
    case 0    : attr.m_enumCharacterAngle = CA_0Degree;break;
    case 900  : attr.m_enumCharacterAngle = CA_90Degree;break;
    case 1800 : attr.m_enumCharacterAngle = CA_180Degree;break;
    case 2700 : attr.m_enumCharacterAngle = CA_270Degree;break;
  }
  switch(m_lCharacterAngle)
  { default   :
    case 0    : attr.m_enumLineAngle = LA_0Degree;break;
    case 900  : attr.m_enumLineAngle = LA_90Degree;break;
    case 1800 : attr.m_enumLineAngle = LA_180Degree;break;
    case 2700 : attr.m_enumLineAngle = LA_270Degree;break;
  }
  attr.m_enumReading     = m_enumReading;
  attr.m_enumTVAlignment = m_enumTVAlignment;
  attr.m_enumParagraph   = m_enumParagraph;
  attr.m_enumCorners     = m_enumCorners;
  return (attr);
}
void CAttributesTextGS::AttributesTextGS(SAttributesTextGS& attr)
{ m_lFrameStyle   = attr.m_dwFrameStyle;
  m_enum3DStyle   = attr.m_enum3DStyle;
  m_clrBackground = attr.m_clrBackground;
  m_clrBorder     = attr.m_clrBorder;
  m_clrOuterFrame = attr.m_clrOuterFrame;
  m_clrFrame      = attr.m_clrFrame;
  m_clrInnerFrame = attr.m_clrInnerFrame;

  m_widthsOuterFrame = attr.m_rectOuterWidth;
  m_widthsFrame      = attr.m_rectMiddleWidth;
  m_widthsInnerFrame = attr.m_rectInnerWidth;
  m_widthsPadding    = attr.m_rectPadding;

  _tcsncpy_s(m_lfDefault.lfFaceName,32,attr.m_strFontName,31);
  m_lfDefault.lfHeight   = attr.m_iFontSize *20;
  attr.m_bBold ? (m_lfDefault.lfWeight = FW_BOLD) : (m_lfDefault.lfWeight = FW_NORMAL);
  m_lfDefault.lfItalic     = attr.m_bItalic;
  m_lfDefault.lfUnderline  = attr.m_bUnderline;
  m_clrText                = attr.m_clrText;

  m_lCharacterAngle  = attr.m_enumCharacterAngle;
  m_lLineAngle       = attr.m_enumLineAngle;
  m_enumReading      = attr.m_enumReading;
  m_enumTVAlignment  = attr.m_enumTVAlignment;
  m_enumParagraph    = attr.m_enumParagraph;
  m_enumCorners      = attr.m_enumCorners;
}

struct SAttributesTextGS_Simple CAttributesTextGS::AttributesTextGS_Simple(void)
{ SAttributesTextGS_Simple attr;

  attr.m_dwFrameStyle  = m_lFrameStyle;
  attr.m_enum3DStyle   = m_enum3DStyle;
  attr.m_clrBackground = m_clrBackground;
  attr.m_clrBorder     = m_clrBorder;
  attr.m_clrFrame      = m_clrFrame;

  attr.m_iOuterWidth   = m_widthsOuterFrame.left;
  attr.m_iMiddleWidth  = m_widthsFrame.left;
  attr.m_iInnerWidth   = m_widthsInnerFrame.left;
  attr.m_iPadding      = m_widthsPadding.left;

  _tcsncpy_s(attr.m_strFontName,32,m_lfDefault.lfFaceName,31);
  attr.m_iFontSize   = m_lfDefault.lfHeight/20;
  attr.m_bBold       = (m_lfDefault.lfWeight > FW_NORMAL);
  attr.m_bItalic     = (m_lfDefault.lfItalic != 0) ? true : false;
  attr.m_bUnderline  = (m_lfDefault.lfUnderline != 0) ? true : false;
  attr.m_clrText     = m_clrText;

  attr.m_enumTVAlignment = m_enumTVAlignment;
  attr.m_enumParagraph   = m_enumParagraph;
  return (attr);
}

void CAttributesTextGS::AttributesTextGS_Simple(SAttributesTextGS_Simple& attr)
{ m_lFrameStyle   = attr.m_dwFrameStyle;
  m_enum3DStyle   = attr.m_enum3DStyle;
  m_clrBackground = attr.m_clrBackground;
  m_clrBorder     = attr.m_clrBorder;
  m_clrOuterFrame = attr.m_clrFrame;
  m_clrFrame      = attr.m_clrFrame;
  m_clrInnerFrame = attr.m_clrFrame;

  m_widthsOuterFrame = CRect(attr.m_iOuterWidth,attr.m_iOuterWidth,attr.m_iOuterWidth,attr.m_iOuterWidth);
  m_widthsFrame      = CRect(attr.m_iMiddleWidth,attr.m_iMiddleWidth,attr.m_iMiddleWidth,attr.m_iMiddleWidth);
  m_widthsInnerFrame = CRect(attr.m_iInnerWidth,attr.m_iInnerWidth,attr.m_iInnerWidth,attr.m_iInnerWidth);
  m_widthsPadding    = CRect(attr.m_iPadding,attr.m_iPadding,attr.m_iPadding,attr.m_iPadding);

  _tcsncpy_s(m_lfDefault.lfFaceName,32,attr.m_strFontName,31);
  m_lfDefault.lfHeight   = attr.m_iFontSize *20;
  attr.m_bBold ? (m_lfDefault.lfWeight = FW_BOLD) : (m_lfDefault.lfWeight = FW_NORMAL);
  m_lfDefault.lfItalic     = attr.m_bItalic;
  m_lfDefault.lfUnderline  = attr.m_bUnderline;
  m_clrText                = attr.m_clrText;

  m_enumTVAlignment  = attr.m_enumTVAlignment;
  m_enumParagraph    = attr.m_enumParagraph;
}

enum CAttributesTextGS::BorderLines CAttributesTextGS::BorderLines(void)const
{ return ((enum CAttributesTextGS::BorderLines)(m_lFrameStyle & 0xF000));
}
enum CAttributesTextGS::OuterFrameLines CAttributesTextGS::OuterFrameLines(void)const
{ return ((enum CAttributesTextGS::OuterFrameLines)(m_lFrameStyle & 0x0F00));
}
enum CAttributesTextGS::FrameLines CAttributesTextGS::FrameLines(void)const
{ return ((enum CAttributesTextGS::FrameLines)(m_lFrameStyle & 0x00F0));
}
enum CAttributesTextGS::InnerFrameLines CAttributesTextGS::InnerFrameLines(void)const
{ return ((enum CAttributesTextGS::InnerFrameLines)(m_lFrameStyle & 0x000F));
}


CRect CAttributesTextGS::CalculateTextRect(CDC& dc, const CRect& rectWindow, const bool bConvertToLP = false)
{ CRect rectText(rectWindow);
  if( dc.GetSafeHdc() == NULL )
    { rectText.SetRectEmpty();
	    return(rectText); // Thou shallst calculate only when there is something to do
	  }
  if( rectWindow.IsRectEmpty() )
    { rectText.SetRectEmpty();
	    return(rectText); // Thou shallst calculate only with existing values
	  }
  if( rectWindow.bottom <= rectWindow.top || rectWindow.right <= rectWindow.left )
    { rectText.SetRectEmpty();
	    return (rectText); // Thou shallst calculate only with positive values
	  }
	CRect rectMargin = CalculateMargins();
  if( bConvertToLP )
    { dc.DPtoLP(&rectMargin);
    }
  rectText.DeflateRect(rectMargin);   
  if( rectText.bottom <= rectText.top || rectText.right <= rectText.left )
    { rectText.SetRectEmpty();
	}
  return (rectText);
}
CRect CAttributesTextGS::CalculateMargins(void)
{ CRect rectMargin(0,0,0,0);
  enum CAttributesTextGS::BorderLines      eBorderLines     = CAttributesTextGS::BL_without;
  enum CAttributesTextGS::OuterFrameLines  eOuterFrameLines = CAttributesTextGS::OF_without;
  enum CAttributesTextGS::FrameLines       eFrameLines      = CAttributesTextGS::FL_without;
  enum CAttributesTextGS::InnerFrameLines  eInnerFrameLines = CAttributesTextGS::IF_without;
  enum CAttributesTextGS::FrameCorners     eCorners         = CAttributesTextGS::FC_without;
  eBorderLines     = BorderLines();
  eOuterFrameLines = OuterFrameLines();
  eFrameLines      = FrameLines();
  eInnerFrameLines = InnerFrameLines();
  eCorners         = (enum CAttributesTextGS::FrameCorners)(m_enumCorners & 0x000F);
  if( CAttributesTextGS::BL_without != eBorderLines ) // Yes we do
    { if( (eBorderLines & CAttributesTextGS::BL_Left) == CAttributesTextGS::BL_Left )
		{ rectMargin.left += 1; // Adjust text rect for the left borderline
		}
      if( (eBorderLines & CAttributesTextGS::BL_Top) == CAttributesTextGS::BL_Top )
		{ rectMargin.top += 1; // Adjust text rect for the top borderline
		}
      if( (eBorderLines & CAttributesTextGS::BL_Right) == CAttributesTextGS::BL_Right )
		{ rectMargin.right += 1; // Adjust text rect for the right borderline
		}
      if( (eBorderLines & CAttributesTextGS::BL_Bottom) == CAttributesTextGS::BL_Bottom )
		{ rectMargin.bottom += 1; // Adjust text rect for the bottom borderline
		}
	}
  // Do we have to adjust for the outer frame lines?
  if( CAttributesTextGS::OF_without != eOuterFrameLines || CAttributesTextGS::FC_without !=  eCorners ) // Yes we do
    { if( (eOuterFrameLines & CAttributesTextGS::OF_Left) == CAttributesTextGS::OF_Left
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.left += m_widthsOuterFrame.left; // Adjust text rect for the left outer frame line
		    }
      if(    (eOuterFrameLines & CAttributesTextGS::OF_Top) == CAttributesTextGS::OF_Top
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.top += m_widthsOuterFrame.top; // Adjust text rect for the top outer frame line
		    }
      if(    (eOuterFrameLines & CAttributesTextGS::OF_Right) == CAttributesTextGS::OF_Right
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop )
		    { rectMargin.right += m_widthsOuterFrame.right; // Adjust text rect for the right outer frame line
		    }
      if(    (eOuterFrameLines & CAttributesTextGS::OF_Bottom) == CAttributesTextGS::OF_Bottom
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom )
		    { rectMargin.bottom += m_widthsOuterFrame.bottom; // Adjust text rect for the bottom outer frame line
		    }
	}
  // Do we have to adjust for the frame lines?
  if( CAttributesTextGS::FL_without != eFrameLines || CAttributesTextGS::FC_without !=  eCorners ) // Yes we do
    { if( (eFrameLines & CAttributesTextGS::FL_Left) == CAttributesTextGS::FL_Left 
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.left += m_widthsFrame.left; // Adjust text rect for the left outer frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Top) == CAttributesTextGS::FL_Top 
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.top += m_widthsFrame.top; // Adjust text rect for the top outer frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Right) == CAttributesTextGS::FL_Right 
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop )
		    { rectMargin.right += m_widthsFrame.right; // Adjust text rect for the right outer frame line
		    }
      if( (eFrameLines & CAttributesTextGS::FL_Bottom) == CAttributesTextGS::FL_Bottom 
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom )
		    { rectMargin.bottom += m_widthsFrame.bottom; // Adjust text rect for the bottom outer frame line
		    }
	}
  // Do we have to adjust for the outer frame lines?
  if( CAttributesTextGS::IF_without != eInnerFrameLines || CAttributesTextGS::FC_without !=  eCorners ) // Yes we do
    { if( (eInnerFrameLines & CAttributesTextGS::IF_Left) == CAttributesTextGS::IF_Left 
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.left += m_widthsInnerFrame.left; // Adjust text rect for the left outer frame line
		    }
      if( (eInnerFrameLines & CAttributesTextGS::IF_Top) == CAttributesTextGS::IF_Top 
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop
	        || (eCorners & CAttributesTextGS::FC_LeftTop) == CAttributesTextGS::FC_LeftTop )
		    { rectMargin.top += m_widthsInnerFrame.top; // Adjust text rect for the top outer frame line
		    }
      if( (eInnerFrameLines & CAttributesTextGS::IF_Right) == CAttributesTextGS::IF_Right 
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom
	        || (eCorners & CAttributesTextGS::FC_RightTop) == CAttributesTextGS::FC_RightTop )
		    { rectMargin.right += m_widthsInnerFrame.right; // Adjust text rect for the right outer frame line
		    }
      if( (eInnerFrameLines & CAttributesTextGS::IF_Bottom) == CAttributesTextGS::IF_Bottom 
	        || (eCorners & CAttributesTextGS::FC_LeftBottom) == CAttributesTextGS::FC_LeftBottom 
	        || (eCorners & CAttributesTextGS::FC_RightBottom) == CAttributesTextGS::FC_RightBottom )
		    { rectMargin.bottom += m_widthsInnerFrame.bottom; // Adjust text rect for the bottom outer frame line
		    }
	}
	rectMargin.left   += m_widthsPadding.left;
	rectMargin.top    += m_widthsPadding.top;
	rectMargin.right  += m_widthsPadding.right;
	rectMargin.bottom += m_widthsPadding.bottom;
  return (rectMargin);
}

void CAttributesTextGS::CalculateTextHeight( CDC& dc, const int iWidth, LPCTSTR pstrText, const bool bConvertToLP = false)
{ if( dc.GetSafeHdc() == NULL )
    { return; // Thou shallst write only on paper
    }
  if( iWidth <= 0 )
    { return; // Thou shallst write only if there is room
    }
  if( pstrText == NULL )
    { return; // Thou shallst only write if there is text available
    }
  CString strParagraph(pstrText);
  if( strParagraph.IsEmpty() )
    { return; // Thou shallst not write if there is no text
    }
  if( m_ftDefault.GetSafeHandle() == NULL )
    { m_ftDefault.CreateFontIndirect( &m_lfDefault );
    }
  if( m_ftDefault.GetSafeHandle() == NULL )
    { return; // Thou shallst write only if thou havest characters
    }
  CSize sizeCalcText(iWidth,0);
  int iLineNumbers = 0;
// Save the actual DC state
  CSize  OldWndExt  = dc.GetWindowExt();
  CPoint OldWndOrg  = dc.GetWindowOrg();
  CSize  OldViewExt = dc.GetViewportExt();
  CPoint OldViewOrg = dc.GetViewportOrg();
  int    OldMapMode = dc.GetMapMode();
  int    OldBkMode  = dc.GetBkMode();
  ::SetGraphicsMode(dc.GetSafeHdc(),GM_ADVANCED);

// Set mapping mode to 1440 Twips with
//     y-axis running down, x-axis running to the right
  dc.SetMapMode(MM_ANISOTROPIC);
  dc.SetBkMode(TRANSPARENT);
  dc.SetWindowOrg(0, 0);
  dc.SetViewportOrg(0, 0);
  dc.SetWindowExt(1440,1440);
// Device viewport is dpi of actual output device.
  dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX),dc.GetDeviceCaps(LOGPIXELSY));
  if( bConvertToLP)
    { dc.DPtoLP(&sizeCalcText);
    }
  TEXTMETRIC tmFont;
  int iLineHeight = 0;
  CString strOutputLine = _T("");
  CFont *pOldFont = NULL;
  // Default settings
  //dc.SetTextColor(m_clrText);
  dc.SetTextAlign(TA_LEFT|TA_BASELINE|TA_NOUPDATECP);
  dc.SetTextJustification(0,0);
  pOldFont = dc.SelectObject(&m_ftDefault);
  dc.GetTextMetrics(&tmFont);
  // Get the height of a textline
  iLineHeight = tmFont.tmHeight + tmFont.tmExternalLeading;

  // Retrieve the maximum count of characters, that will fit in one line
  // and then get the output text
  int iLastChar   = 0;
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
    { CSize sizeT;
      CString strEmpty(TCHAR(' '),iCountSpacesFront);
      sizeSpacesFront = dc.GetOutputTextExtent(strEmpty);
    }
  bool bParagraphEnd = false;
  while( strParagraph.GetLength()>0 )
       { bParagraphEnd = false;
         iLastChar = CalculateLineCharCount(dc,sizeCalcText.cx,strParagraph,false);
         if( iLastChar < iCountSpacesFront + 1 )
           { break;
           }
         strOutputLine = strParagraph.Left(iLastChar);
         if( strParagraph[iLastChar-1] == TCHAR('\n') )
           { bParagraphEnd = true;
           }
         strParagraph = strParagraph.Mid(iLastChar);
         if( !bParagraphEnd )
           { strParagraph.TrimLeft(TCHAR(' '));
           }
         strParagraph.TrimLeft(TCHAR('­')); // soft hyphen
         sizeCalcText.cy += iLineHeight;
         iLineNumbers++;
       }
  m_iLineNumbers = iLineNumbers;
  m_iLineHeight  = iLineHeight;
  m_sizeTextRect = sizeCalcText;

  dc.SelectObject(pOldFont);
  // In case we changed the old values, we should restore them
  dc.SetBkMode(OldBkMode);
  dc.SetMapMode(OldMapMode);
  dc.SetViewportOrg(OldViewOrg);
  dc.SetViewportExt(OldViewExt);
  dc.SetWindowOrg(OldWndOrg);
  dc.SetWindowExt(OldWndExt);
}

int CAttributesTextGS::CalculateLineCharCount( CDC& dc, const int iWidth, LPCTSTR pstrText, const bool bConvertToLP = false)
{ if( dc.GetSafeHdc() == NULL )
    { return (0); // Thou shallst write only on paper
    }
  if( iWidth <= 0 )
    { return (0); // Thou shallst write only if there is room
    }
  if( pstrText == NULL )
    { return (0); // Thou shallst only write if there is text available
    }
  CString strParagraph(pstrText);
  if( strParagraph.IsEmpty() )
    { return (0); // Thou shallst not write if there is no text
    }
  if( m_ftDefault.GetSafeHandle() == NULL )
    { m_ftDefault.CreateFontIndirect( &m_lfDefault );
    }
  if( m_ftDefault.GetSafeHandle() == NULL )
    { return (0); // Thou shallst write only if thou havest characters
    }
  CSize sizeCalcText(iWidth,0);
// Save the actual DC state
  CSize  OldWndExt  = dc.GetWindowExt();
  CPoint OldWndOrg  = dc.GetWindowOrg();
  CSize  OldViewExt = dc.GetViewportExt();
  CPoint OldViewOrg = dc.GetViewportOrg();
  int    OldMapMode = dc.GetMapMode();
  int    OldBkMode  = dc.GetBkMode();
  ::SetGraphicsMode(dc.GetSafeHdc(),GM_ADVANCED);

// Set mapping mode to 1440 Twips with
//     y-axis running down, x-axis running to the right
  dc.SetMapMode(MM_ANISOTROPIC);
  dc.SetBkMode(TRANSPARENT);
  dc.SetWindowOrg(0, 0);
  dc.SetViewportOrg(0, 0);
  dc.SetWindowExt(1440,1440);
// Device viewport is dpi of actual output device.
  dc.SetViewportExt(dc.GetDeviceCaps(LOGPIXELSX),
                    dc.GetDeviceCaps(LOGPIXELSY));
  if( bConvertToLP)
    { dc.DPtoLP(&sizeCalcText);
    }
  TEXTMETRIC tmFont;
  CString strOutputLine = _T("");
  CFont *pOldFont = NULL;
  // Default settings
  // dc.SetTextColor(m_clrText);
  dc.SetTextAlign(TA_LEFT|TA_BASELINE|TA_NOUPDATECP);
  dc.SetTextJustification(0,0);
  pOldFont = dc.SelectObject(&m_ftDefault);
  dc.GetTextMetrics(&tmFont);
  // Get the height of a textline

  // Retrieve the maximum count of characters, that will fit in one line
  // and then get the output text
  CSize sizeText(0,0);
  int iLastChar   = 0;
  int iPosSpace   = -1;
  int iPosHyphen  = -1;
  int iPosPara    = -1;
  bool bParagraphEnd = false;
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
    { CSize sizeT;
      CString strEmpty(TCHAR(' '),iCountSpacesFront);
      sizeSpacesFront = dc.GetOutputTextExtent(strEmpty);
    }
  while( (sizeText.cx <= sizeCalcText.cx ) && (iLastChar < strParagraph.GetLength()) )
       { iPosSpace = strParagraph.Find(TCHAR(' '),iLastChar);
         if( iPosSpace > iCountSpacesFront )
           { iLastChar = iPosSpace+1;
           }
         else
           { iLastChar = strParagraph.GetLength();
           }
         // First estimate output size, doing exact calculation as late as possible
         sizeText.cx = iLastChar*tmFont.tmAveCharWidth;
         if( sizeText.cx <= sizeCalcText.cx )
           { continue;
           }
         strOutputLine = strParagraph.Left(iLastChar);
         strOutputLine.TrimRight();            // Remove trailing white spaces
         strOutputLine.Replace(_T("­"),_T(""));// Remove soft hyphens
         // Use the output dc for exact calculation not the attribute dc
         if( CAttributesTextGS::TR_RightToLeft == m_enumReading)
           { strOutputLine.MakeReverse();
           }
         sizeText = dc.GetOutputTextExtent(strOutputLine);
       }
  if( iLastChar < 1 ) iLastChar = 1; // Always print at least one character
  strOutputLine = strParagraph.Left(iLastChar);
  iPosPara   = strOutputLine.Find(TCHAR('\n'));
  strOutputLine.TrimRight();
  strOutputLine.TrimRight(TCHAR(0xAD));//TCHAR('­')
  iPosSpace  = strOutputLine.ReverseFind(TCHAR(' '));
  iPosHyphen = strOutputLine.ReverseFind(TCHAR(0xAD));//TCHAR('­')
  strOutputLine.Replace(CString(TCHAR(0xAD)),_T(""));          // Remove soft hyphens
  sizeText = dc.GetOutputTextExtent(strOutputLine);
  while( (sizeText.cx > sizeCalcText.cx) || (iPosPara >= 0))
       { bool bBreakFound = false;
         bParagraphEnd = false;
         if( iPosHyphen > 0 && iPosHyphen > iPosSpace )// Hyphen break?
           { iLastChar = iPosHyphen +1;
             strOutputLine = strParagraph.Left(iLastChar);
             strOutputLine.TrimRight();
             strOutputLine.TrimRight(TCHAR(0xAD));//TCHAR('­')
             iPosSpace = strOutputLine.ReverseFind(TCHAR(' '));
             iPosHyphen = strOutputLine.ReverseFind(TCHAR(0xAD));//TCHAR('­')
             strOutputLine.Replace(CString(TCHAR(0xAD)),_T(""));
             strOutputLine += TCHAR(0xAD);//TCHAR('­')
             bBreakFound = true;
           }
         if( iPosSpace > iCountSpacesFront && !bBreakFound )// Word break?
           { iLastChar = iPosSpace+1;
             strOutputLine = strParagraph.Left(iLastChar);
             strOutputLine.TrimRight();
             strOutputLine.TrimRight(TCHAR(0xAD));//TCHAR('­')
             iPosSpace = strOutputLine.ReverseFind(TCHAR(' '));
             iPosHyphen = strOutputLine.ReverseFind(TCHAR(0xAD));//TCHAR('­')
             strOutputLine.Replace(CString(TCHAR(0xAD)),_T(""));
             bBreakFound = true;
           }
         if( iPosPara >= 0  )// End of a paragraph?
           { iLastChar = iPosPara+1;
             strOutputLine = strParagraph.Left(iLastChar);
             strOutputLine.TrimRight();
             strOutputLine.TrimRight(TCHAR(0xAD));//TCHAR('­')
             iPosPara   = strOutputLine.Find(TCHAR('\n'));
             iPosSpace  = strOutputLine.ReverseFind(TCHAR(' '));
             iPosHyphen = strOutputLine.ReverseFind(TCHAR(0xAD));//TCHAR('­')
             strOutputLine.Replace(CString(TCHAR(0xAD)),_T(""));
             bParagraphEnd = true;
             bBreakFound = true;
           }
         if( !bBreakFound )
           { if( iLastChar > 1) iLastChar --;
             strOutputLine = strParagraph.Left(iLastChar);
             if( iLastChar <=1 )
               { sizeText = dc.GetOutputTextExtent(strOutputLine);
                 break;
               }
           }
         if( CAttributesTextGS::TR_RightToLeft == m_enumReading)
           { strOutputLine.MakeReverse();
             sizeText = dc.GetOutputTextExtent(strOutputLine);
           }
         else
           { sizeText = dc.GetOutputTextExtent(strOutputLine);
           }
         bBreakFound = false;
       }// while( (sizeText.cx > sizeCalcText.cx) || (iPosPara >= 0))

  dc.SelectObject(pOldFont);
  // In case we changed the old values, we should restore them
  dc.SetBkMode(OldBkMode);
  dc.SetMapMode(OldMapMode);
  dc.SetViewportOrg(OldViewOrg);
  dc.SetViewportExt(OldViewExt);
  dc.SetWindowOrg(OldWndOrg);
  dc.SetWindowExt(OldWndExt);
  return (iLastChar);
}

int CAttributesTextGS::TextHeight(void)
{ return (m_sizeTextRect.cy);
}

COLORREF CAttributesTextGS::DarkColor(const COLORREF color)
{ COLORREF newColor = color;
  BYTE red   = GetRValue(newColor);
  BYTE green = GetGValue(newColor);
  BYTE blue  = GetBValue(newColor);
  BYTE byThreshold = 56;
  BYTE r1 = (BYTE)(red/3);
  BYTE g1 = (BYTE)(green/3);
  BYTE b1 = (BYTE)(blue/3);
  if( r1 > byThreshold ) r1 = byThreshold;
  if( g1 > byThreshold ) g1 = byThreshold;
  if( b1 > byThreshold ) b1 = byThreshold;
  newColor = RGB(red-r1,green-g1,blue-b1);
  return (newColor);
}
COLORREF CAttributesTextGS::LightColor(const COLORREF color)
{ COLORREF newColor = color;
  BYTE red   = GetRValue(newColor);
  BYTE green = GetGValue(newColor);
  BYTE blue  = GetBValue(newColor);
  BYTE byThreshold = 56;
  BYTE r1 = (BYTE)((255 - red)/3);
  BYTE g1 = (BYTE)((255 - green)/3);
  BYTE b1 = (BYTE)((255 - blue)/3);
  if( r1 > byThreshold ) r1 = byThreshold;
  if( g1 > byThreshold ) g1 = byThreshold;
  if( b1 > byThreshold ) b1 = byThreshold;
  newColor = RGB(red+r1,green+g1,blue+b1);
  return (newColor);
}

COLORREF CAttributesTextGS::DarkerColor(const COLORREF color)
{ COLORREF newColor = color;
  BYTE red   = GetRValue(newColor);
  BYTE green = GetGValue(newColor);
  BYTE blue  = GetBValue(newColor);
  BYTE byThreshold = 80;
  BYTE r1 = (BYTE)(red/2);
  BYTE g1 = (BYTE)(green/2);
  BYTE b1 = (BYTE)(blue/2);
  if( r1 > byThreshold ) r1 = byThreshold;
  if( g1 > byThreshold ) g1 = byThreshold;
  if( b1 > byThreshold ) b1 = byThreshold;
  newColor = RGB(red-r1,green-g1,blue-b1);
  return (newColor);
}
COLORREF CAttributesTextGS::LighterColor(const COLORREF color)
{ COLORREF newColor = color;
  BYTE red   = GetRValue(newColor);
  BYTE green = GetGValue(newColor);
  BYTE blue  = GetBValue(newColor);
  BYTE byThreshold = 80;
  BYTE r1 = (BYTE)((255 - red)/2);
  BYTE g1 = (BYTE)((255 - green)/2);
  BYTE b1 = (BYTE)((255 - blue)/2);
  if( r1 > byThreshold ) r1 = byThreshold;
  if( g1 > byThreshold ) g1 = byThreshold;
  if( b1 > byThreshold ) b1 = byThreshold;
  newColor = RGB(red+r1,green+g1,blue+b1);
  return (newColor);
}


// Image Attributes
SAttributesImageGS_ID& SAttributesImageGS_ID::operator=(const SAttributesImageGS_ID& attr)
{ if( this==&attr )
    { return (*this);
    }
  m_uiBitmap  = attr.m_uiBitmap;
  m_enumBackImage   = attr.m_enumBackImage;
  m_enumInvertAxis = attr.m_enumInvertAxis;
  return (*this);
}

SAttributesImageGS_File& SAttributesImageGS_File::operator=(const SAttributesImageGS_File& attr)
{ if( this==&attr )
    { return (*this);
    }
  _tcsncpy_s(m_strBitmap,1025,attr.m_strBitmap,1024);
  m_enumBackImage   = attr.m_enumBackImage;
  m_enumInvertAxis = attr.m_enumInvertAxis;
  return (*this);
}

CAttributesImageGS::CAttributesImageGS()
{ Initialize();
}

CAttributesImageGS::~CAttributesImageGS()
{ if( m_bmpBackground.GetSafeHandle() != NULL )
    { m_bmpBackground.DeleteObject();
    }
}

void CAttributesImageGS::Initialize(void)
{// Setting background image style
  m_uiBitmap  = 0;
  m_strBitmap.Empty();
  m_enumBackImage   = BI_without;
  m_enumRotateImage = RI_0Degree;
  m_enumInvertAxis  = IA_Axis_None;
}

bool CAttributesImageGS::LoadBitmap(LPCTSTR pstrBitmapFile)
{ bool bSuccess = false;
  if( pstrBitmapFile == NULL )
    { return bSuccess;
    }
  if( m_bmpBackground.GetSafeHandle() != NULL )
    { m_bmpBackground.DeleteObject();
    }
  m_uiBitmap  = 0;
  m_strBitmap.Empty();
  if( !m_bmpBackground.LoadBitmap(pstrBitmapFile) )
    { return bSuccess;
    }
  bSuccess = true;
  m_strBitmap = pstrBitmapFile;
  m_bmpBackground.GetBitmap(&m_bmpInfo);
  return bSuccess;
}
bool CAttributesImageGS::LoadBitmap(UINT uiResourceID)
{ bool bSuccess = false;
  if( m_bmpBackground.GetSafeHandle() != NULL )
    { m_bmpBackground.DeleteObject();
    }
  m_uiBitmap  = 0;
  m_strBitmap.Empty();
  if( !m_bmpBackground.LoadBitmap(uiResourceID) )
    { return bSuccess;
    }
  bSuccess = true;
  m_uiBitmap = uiResourceID;
  m_bmpBackground.GetBitmap(&m_bmpInfo);
  return bSuccess;
}
