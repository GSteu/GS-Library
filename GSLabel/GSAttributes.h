#if !defined(AFX_ATTRIBUTESGS_H__1C417ABF_5251_43E2_9CDA_9287E69B3A17__INCLUDED_)
#define AFX_ATTRIBUTESGS_H__1C417ABF_5251_43E2_9CDA_9287E69B3A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#endif
//#include <afxext.h>     // MFC-Erweiterungen
//#include <afxdtctl.h>	  // MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
//#include <afxcmn.h>	    // MFC-Unterstützung für gängige Windows-Steuerelemente
#include <vector>
//#include "Markup.h"

// AttributeGS.h : Header-Datei
//
struct SAttributesTextGS;           // forward declarations
struct SAttributesTextGS_Simple;    // for interface structures
struct SAttributesTextGS_ImageID;   // Display image by resource id
struct SAttributesTextGS_ImageFile; // Display image (*.bmp) by filename
//struct SAttributesBindings;         // Create and display an own picture by algorithmn

// These classes contain all enumeratione and basic methods for the GUILib classes
// class for text attributes (formatting and size calculations)
class CAttributesTextGS
{
 public:
// Enumerations
// Enumerated constants for border/frame line(s).
// These styles MUST be combined (or'd).
  enum BorderLines
  { BL_without = 0x0000,// no border lines
    BL_Frame   = 0xF000,// shortcut for drawing all lines
	  BL_Left    = 0x1000,// draw only left border line
	  BL_Top     = 0x2000,// draw only top border line
	  BL_Right   = 0x4000,// draw only right border line
	  BL_Bottom  = 0x8000 // draw only bottom border line
  };
  enum OuterFrameLines
  { OF_without = 0x0000,// no outer frame lines
    OF_Frame   = 0x0F00,// shortcut for drawing all lines
	  OF_Left    = 0x0100,// draw only left outer frame line
	  OF_Top     = 0x0200,// draw only top outer frame line
	  OF_Right   = 0x0400,// draw only right outer frame line
	  OF_Bottom  = 0x0800 // draw only bottom outer frame line
  };
  enum FrameLines
  { FL_without = 0x0000,// no frame lines
    FL_Frame   = 0x00F0,// shortcut for drawing all lines
	  FL_Left    = 0x0010,// draw only left frame line
	  FL_Top     = 0x0020,// draw only top frame line
	  FL_Right   = 0x0040,// draw only right frame line
	  FL_Bottom  = 0x0080 // draw only bottom frame line
  };
  enum InnerFrameLines
  { IF_without = 0x0000,// no inner frame lines
    IF_Frame   = 0x000F,// shortcut for drwaing all lines
	  IF_Left    = 0x0001,// draw only left inner frame line
	  IF_Top     = 0x0002,// draw only top inner frame line
	  IF_Right   = 0x0004,// draw only right inner frame line
	  IF_Bottom  = 0x0008 // draw only bottom inner frame line
  };
  enum FrameCorners
  { FC_without     = 0x0000, // no connecting corners to draw (default)
    FC_LeftTop     = 0x0001, // force drawing connecting corner top-left
    FC_RightTop    = 0x0002, // force drawing connecting corner top-right
    FC_RightBottom = 0x0004, // force drawing connecting corner bottom-right
    FC_LeftBottom  = 0x0008, // force drawing connecting corner bottom-left
    FC_ConnectTopLeftLeft        = 0x0010, // connect to the top left corner to the left
    FC_ConnectTopRightRight      = 0x0020, // connect to the top right corner to the right
    FC_ConnectBottomRightRight   = 0x0040, // connect to the bottom right corner to the right
    FC_ConnectBottomLeftLeft     = 0x0080, // connect to the bottom left corner to the left
    FC_ConnectTopLeftTop         = 0x0100, // connect to the top left corner to the top
    FC_ConnectTopRightTop        = 0x0200, // connect to the top right corner to the top
    FC_ConnectBottomRightBottom  = 0x0400, // connect to the bottom right corner to the bottom
    FC_ConnectBottomLeftBottom   = 0x0800, // connect to the bottom left corner to the bottom
  };
// Enumerated constants for 3D-effects of frame line(s).
// These styles may NOT be combined.
  enum Frame3DStyle
  { D3_without   = 0x0000,// no 3D style
    D3_OutRaised = 0x0001,
	  D3_OutSunken = 0x0002,
	  D3_InRaised  = 0x0010,
	  D3_InSunken  = 0x0020,
	  D3_MidRaised = 0x0100,
	  D3_MidSunken = 0x0200,
    D3_Raised    = 0x0021,
	  D3_Sunken    = 0x0012,
	  D3_UpWards   = 0x0011,
	  D3_DownWards = 0x0022,
	  D3_SlopeUp   = 0x0100,
	  D3_SlopeDown = 0x0200,
  };
// Enumerated constants for text writing.
// These styles may NOT be combined.
  enum TextReading
  { TR_LeftToRight = 0x0001,
    TR_RightToLeft = 0x0002,
	  TR_DownLeft    = 0x0004,
	  TR_DownRight   = 0x0008
  };

// Enumerated constants for vertical text alignment.
// These styles may NOT be combined.
  enum TextVAlignment
  { TV_Top    = 0x0001,
    TV_Center = 0x0002,
	  TV_Bottom = 0x0004
  };

// Enumerated constants for paragraph alignment.
// These styles may NOT be combined.
  enum ParaAlign
  { PA_Front   = 0x0001, // left on L2R, right on R2L, top on down
    PA_Center  = 0x0002,
    PA_End     = 0x0004, // right on L2R, left on R2L, bottom on down
	  PA_Justify = 0x0008, //  last line of paragraph at start of line
	  PA_JustifyCenter = 0x0018, // last line of paragraph centered
	  PA_JustifyEnd    = 0x0028  // last line of paragraph at the end of line
  };

// Enumerated constants for character angles.
// These values may NEVER be combined.
  enum CharacterAngle
  { CA_0Degree   = 0,
    CA_90Degree  = 900,
	  CA_180Degree = 1800,
 	  CA_270Degree = 2700,
 };
  enum LineAngle
  { LA_0Degree   = 0,
    LA_90Degree  = 900,
	  LA_180Degree = 1800,
	  LA_270Degree = 2700,
  };
// for fooling around
  enum InvertAxis
  { IA_Axis_None  = 0x0000,
    IA_Axis_X     = 0x0001,
    IA_Axis_Y     = 0x0002,
	  IA_Axis_Both  = 0x0003
  };

// Variables
// Framestyles, colors and width
  long m_lFrameStyle;
  enum Frame3DStyle m_enum3DStyle;
  // Colours
  COLORREF m_clrBackground;
  COLORREF m_clrBorder;
  COLORREF m_clrFrame;
  COLORREF m_clrOuterFrame;
  COLORREF m_clrInnerFrame;
  // Frame widths
  CRect    m_widthsOuterFrame; // Width in 20*points for
  CRect    m_widthsFrame;      // left, top, right and bottom
  CRect    m_widthsInnerFrame; // parts of the frame
  CRect    m_widthsPadding;    // Padding values
// Text attributes
  CFont    m_ftDefault; // Default font
  LOGFONT  m_lfDefault;
  COLORREF m_clrText;   // Text colour
  long m_lCharacterAngle;
  long m_lLineAngle;
  enum InvertAxis     m_enumInvertAxis;
  enum TextReading    m_enumReading;
  enum TextVAlignment m_enumTVAlignment;
  enum ParaAlign      m_enumParagraph;
  enum FrameCorners   m_enumCorners;
protected:
  CSize m_sizeTextRect;
  int   m_iLineHeight;
  int   m_iLineNumbers;
public:
// Constructor/Destructor
  CAttributesTextGS();
  ~CAttributesTextGS();
protected:
  void Initialize(void);
public:
  struct SAttributesTextGS AttributesTextGS(void);
  struct SAttributesTextGS_Simple AttributesTextGS_Simple(void);
  void AttributesTextGS(SAttributesTextGS& attr);
  void AttributesTextGS_Simple(SAttributesTextGS_Simple& attr);
  enum BorderLines BorderLines(void)const;
  enum OuterFrameLines OuterFrameLines(void)const;
  enum FrameLines FrameLines(void)const;
  enum InnerFrameLines InnerFrameLines(void)const;
  // Helper routines 
  CRect CalculateTextRect(CDC& dc, const CRect& rectWindow, const bool bConvertToLP /*= false*/);
  CRect CalculateMargins(void);
  void CalculateTextHeight( CDC& dc, const int iWidth, LPCTSTR pstrText, const bool bConvertToLP /*= false*/);
  int  CalculateLineCharCount( CDC& dc, const int iWidth, LPCTSTR pstrText, const bool bConvertToLP /*= false*/);
  int  TextHeight(void);
  static COLORREF DarkColor(const COLORREF color);
  static COLORREF DarkerColor(const COLORREF color);
  static COLORREF LightColor(const COLORREF color);
  static COLORREF LighterColor(const COLORREF color);
};

// Structure for easier initialization
struct SAttributesTextGS
      { // Frame Styles
		    DWORD    m_dwFrameStyle;
		    enum CAttributesTextGS::Frame3DStyle m_enum3DStyle;
		    // Frame colours and dimensions
        COLORREF m_clrBackground;
		    COLORREF m_clrBorder;
		    COLORREF m_clrOuterFrame;
		    COLORREF m_clrFrame;
		    COLORREF m_clrInnerFrame;
		    RECT     m_rectOuterWidth;
		    RECT     m_rectMiddleWidth;
		    RECT     m_rectInnerWidth;
		    RECT     m_rectPadding;
        // Font attributes
        TCHAR    m_strFontName[32];
        int      m_iFontSize; // in points!!
		    bool     m_bBold;
		    bool     m_bItalic;
		    bool     m_bUnderline;
		    COLORREF m_clrText;
		    // Text behaviour
        enum CAttributesTextGS::CharacterAngle m_enumCharacterAngle;
        enum CAttributesTextGS::LineAngle      m_enumLineAngle;
        enum CAttributesTextGS::TextReading    m_enumReading;
        enum CAttributesTextGS::TextVAlignment m_enumTVAlignment;
        enum CAttributesTextGS::ParaAlign      m_enumParagraph;
        enum CAttributesTextGS::FrameCorners   m_enumCorners;
        // Assignment operator
        SAttributesTextGS& operator=(const SAttributesTextGS& attr);
      };

struct SAttributesTextGS_Simple
      { // Frame Styles
		    DWORD    m_dwFrameStyle;
		    enum CAttributesTextGS::Frame3DStyle m_enum3DStyle;
		    // Frame colours and dimensions
        COLORREF m_clrBackground;
		    COLORREF m_clrBorder;
		    COLORREF m_clrFrame;
		    int      m_iOuterWidth;
		    int      m_iMiddleWidth;
		    int      m_iInnerWidth;
		    int      m_iPadding;
        // Font
        TCHAR    m_strFontName[32];
        int      m_iFontSize; // in points!!
		    bool     m_bBold;
		    bool     m_bItalic;
		    bool     m_bUnderline;
		    COLORREF m_clrText;
		    // Text behaviour
        enum CAttributesTextGS::TextVAlignment m_enumTVAlignment;
        enum CAttributesTextGS::ParaAlign      m_enumParagraph;
        // Assignment operator
        SAttributesTextGS_Simple& operator=(const SAttributesTextGS_Simple& attr);
      };


// class for image attributes (formatting and size calculations)
class CAttributesImageGS
{public:
// Enumerated values for placing the background image
// These styles may NEVER be combined.
  enum BackgroundImage
  { BI_without     = 0x0000, // No background image
    BI_StretchBlt  = 0x0001, // Fit image to text area
    BI_BestFit     = 0x0002, // Fit image to window
	  BI_Tile        = 0x0003, // Tile image in text area
	  BI_CenterLeft  = 0x0004, // Center image in text area to the left
	  BI_Center      = 0x0005, // Center image in text area
	  BI_CenterRight = 0x0006, // Center image in text area to the right
	  BI_TopLeft     = 0x0007, // Put image at top left corner of text area
	  BI_TopCenter   = 0x0008, // Put image in top right corner of text area
	  BI_TopRight    = 0x0009, // Put image in top right corner of text area
	  BI_BottomLeft  = 0x000A, // Put image in bottom left corner of text area
	  BI_BottomCenter= 0x000B, // Put image centered at the bottom of text area
	  BI_BottomRight = 0x000C  // Put image in bottom right corner of text area
  };
  enum RotateImage
  { RI_0Degree   = 0,
    RI_90Degree  = 900,
	  RI_180Degree = 1800,
	  RI_270Degree = 2700
  };

  enum InvertAxis
  { IA_Axis_None  = 0x0000,
    IA_Axis_X     = 0x0001,
    IA_Axis_Y     = 0x0002,
	  IA_Axis_Both  = 0x0003
  };

// Background image
  UINT    m_uiBitmap;
  CString m_strBitmap;
  CBitmap m_bmpBackground;
  BITMAP  m_bmpInfo;
  enum BackgroundImage m_enumBackImage;
  enum RotateImage     m_enumRotateImage;
  enum InvertAxis      m_enumInvertAxis;

public:
  CAttributesImageGS();
  ~CAttributesImageGS();
protected:
  void Initialize(void);
public:
  bool LoadBitmap(LPCTSTR pstrBitmapFile);
  bool LoadBitmap(UINT uiResourceID);
};

// Structures for easier initialization
struct SAttributesImageGS_ID
      { // Image and Attributes
		    UINT m_uiBitmap;
        enum CAttributesImageGS::BackgroundImage m_enumBackImage;
		    enum CAttributesImageGS::InvertAxis      m_enumInvertAxis;
        // Assignment operator
        SAttributesImageGS_ID& operator=(const SAttributesImageGS_ID& attr);
      };

struct SAttributesImageGS_File
      { // Image and Attributes
		    TCHAR m_strBitmap[1025];
        enum CAttributesImageGS::BackgroundImage m_enumBackImage;
		    enum CAttributesImageGS::InvertAxis      m_enumInvertAxis;
        // Assignment operator
        SAttributesImageGS_File& operator=(const SAttributesImageGS_File& attr);
      };
#endif // AFX_ATTRIBUTESGS_H__1C417ABF_5251_43E2_9CDA_9287E69B3A17__INCLUDED_
