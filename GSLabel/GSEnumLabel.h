#pragma once

// Moved here from objbase.w.
/*
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) | ((int)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) & ((int)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
inline ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((int)a)); } \
inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) ^ ((int)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); } \
}
*/

//+ Enumerated constants for drawing label frames.
// Styles may be combined (or-operator).
enum class eBorderLines : unsigned //int32_t
{	BL_without = 0x0000,// no border lines
	BL_Frame   = 0xF000,// shortcut for drawing all border lines
	BL_Left    = 0x1000,// draw only left border line
	BL_Top     = 0x2000,// draw only top border line
	BL_Right   = 0x4000,// draw only right border line
	BL_Bottom  = 0x8000 // draw only bottom border line
};
DEFINE_ENUM_FLAG_OPERATORS(eBorderLines)

enum class eOuterFrameLines : unsigned //int32_t
{	OF_without = 0x0000,// no outer frame lines
	OF_Frame   = 0x0F00,// shortcut for drawing outer frame all lines
	OF_Left    = 0x0100,// draw only left outer frame line
	OF_Top     = 0x0200,// draw only top outer frame line
	OF_Right   = 0x0400,// draw only right outer frame line
	OF_Bottom  = 0x0800 // draw only bottom outer frame line
};
DEFINE_ENUM_FLAG_OPERATORS(eOuterFrameLines)

enum class eFrameLines : unsigned //int32_t
{	FL_without = 0x0000,// no frame lines
	FL_Frame   = 0x00F0,// shortcut for drawing all frame lines
	FL_Left    = 0x0010,// draw only left frame line
	FL_Top     = 0x0020,// draw only top frame line
	FL_Right   = 0x0040,// draw only right frame line
	FL_Bottom  = 0x0080 // draw only bottom frame line
};
DEFINE_ENUM_FLAG_OPERATORS(eFrameLines)

enum class eInnerFrameLines : unsigned //int32_t
{	IF_without = 0x0000,// no inner frame lines
	IF_Frame   = 0x000F,// shortcut for drwaing inner frameall lines
	IF_Left    = 0x0001,// draw only left inner frame line
	IF_Top     = 0x0002,// draw only top inner frame line
	IF_Right   = 0x0004,// draw only right inner frame line
	IF_Bottom  = 0x0008 // draw only bottom inner frame line
};
DEFINE_ENUM_FLAG_OPERATORS(eInnerFrameLines)

enum class eFrameConnections : unsigned //int32_t
{	FC_without                  = 0x0000, // no connections to draw (default)
	FC_LeftTop                  = 0x0001, // force drawing connecting corner top-left
	FC_RightTop                 = 0x0002, // force drawing connecting corner top-right
	FC_RightBottom              = 0x0004, // force drawing connecting corner bottom-right
	FC_LeftBottom               = 0x0008, // force drawing connecting corner bottom-left
	FC_ConnectionsLeft          = 0x0010, // connect left side => todo pointlist
	FC_ConnectionsTop           = 0x0020, // connect top side
	FC_ConnectionsRight         = 0x0040, // connect right side
	FC_ConnectionsBottom        = 0x0080, // connect bottom side
	FC_ConnectTopLeftLeft       = 0x0100, // connect the top left corner to the left
	FC_ConnectTopRightRight     = 0x0200, // connect the top right corner to the right
	FC_ConnectBottomRightRight  = 0x0400, // connect the bottom right corner to the right
	FC_ConnectBottomLeftLeft    = 0x0800, // connect the bottom left corner to the left
	FC_ConnectTopLeftTop        = 0x1000, // connect the top left corner to the top
	FC_ConnectTopRightTop       = 0x2000, // connect the top right corner to the top
	FC_ConnectBottomRightBottom = 0x4000, // connect the bottom right corner to the bottom
	FC_ConnectBottomLeftBottom  = 0x8000, // connect the bottom left corner to the bottom
};
DEFINE_ENUM_FLAG_OPERATORS(eFrameConnections)

// Enumerated constants for 3D-effects of frame line(s).
// These styles may be combined. 
enum class eFrame3DStyle : unsigned //int32_t
{	D3_without   = 0x0000,// no 3D style
	D3_OutRaised = 0x0001,
	D3_OutSunken = 0x0002,
	D3_MidRaised = 0x0010,
	D3_MidSunken = 0x0020,
	D3_InRaised  = 0x0100,
	D3_InSunken  = 0x0200,
	// Combinations
	D3_Raised    = D3_OutRaised | D3_InSunken, // => _/  \_
	D3_Sunken    = D3_OutSunken | D3_InRaised, // =>  \_/
	D3_AllUp     = D3_OutRaised | D3_MidRaised | D3_InRaised,
	D3_AllDown   = D3_OutSunken | D3_MidSunken | D3_InSunken,
	D3_SlopeUp   = D3_OutRaised | D3_InRaised,
	D3_SlopeDown = D3_OutSunken | D3_InSunken
};
DEFINE_ENUM_FLAG_OPERATORS(eFrame3DStyle)

//+ Enumerated constants for text writing.
// These styles may NOT be combined.
enum class eTextReading : unsigned //int32_t
{	TR_LeftToRight   = 0x0001,
	TR_RightToLeft   = 0x0002,
	TR_DownLeft      = 0x0004,
	TR_DownRight     = 0x0008
};
// Enumerated constants for vertical text alignment.
// These styles may NOT be combined.
enum class eTextVAlignment : unsigned //int32_t
{	TV_Top           = 0x0001,
	TV_Center        = 0x0002,
	TV_Bottom        = 0x0004
};
// Enumerated constants for paragraph alignment.
// These styles may NOT be combined.
enum class  eParaAlign : unsigned //int32_t
{	PA_Front         = 0x0001, // left on L2R, right on R2L, top on down
	PA_Center        = 0x0002,
	PA_End           = 0x0004, // right on L2R, left on R2L, bottom on down
	PA_Justify       = 0x0008, // last line of paragraph at start of line
	PA_JustifyCenter = 0x0018, // last line of paragraph centered
	PA_JustifyEnd    = 0x0028  // last line of paragraph at the end of line
};
// Enumerated constants for Image fitting
// These styles may NOT be combined.
enum class eBackgroundImage : unsigned //int32_t
{	BI_without       = 0x0000, // No background image
	BI_StretchBlt    = 0x0001, // Fit image to text area
	BI_BestFit       = 0x0002, // Fit image into text area contain proportion
	BI_Tile          = 0x0003, // Tile image in text area
	BI_CenterLeft    = 0x0004, // Center image in text area to the left
	BI_Center        = 0x0005, // Center image in text area
	BI_CenterRight   = 0x0006, // Center image in text area to the right
	BI_TopLeft       = 0x0007, // Put image at top left corner of text area
	BI_TopCenter     = 0x0008, // Put image in top right corner of text area
	BI_TopRight      = 0x0009, // Put image in top right corner of text area
	BI_BottomLeft    = 0x000A, // Put image in bottom left corner of text area
	BI_BottomCenter  = 0x000B, // Put image centered at the bottom of text area
	BI_BottomRight   = 0x000C  // Put image in bottom right corner of text area
};

//+ Usefull typedefs and constants
typedef unsigned CharAngle;
const CharAngle CA_00Degree  = 0;
const CharAngle CA_15Degree  = 150;
const CharAngle CA_30Degree  = 300;
const CharAngle CA_45Degree  = 450;
const CharAngle CA_60Degree  = 600;
const CharAngle CA_75Degree  = 750;
const CharAngle CA_90Degree  = 900;
const CharAngle CA_180Degree = 1800;
const CharAngle CA_270Degree = 2700;

typedef unsigned LineAngle;
const LineAngle LA_00Degree  = 0;
const LineAngle LA_15Degree  = 150;
const LineAngle LA_30Degree  = 300;
const LineAngle LA_45Degree  = 450;
const LineAngle LA_60Degree  = 600;
const LineAngle LA_75Degree  = 750;
const LineAngle LA_90Degree  = 900;
const LineAngle LA_180Degree = 1800;
const LineAngle LA_270Degree = 2700;

typedef unsigned RotationAngle;
const RotationAngle RA_0Degree   = 0;
const RotationAngle RA_15Degree  = 150;
const RotationAngle RA_30Degree  = 300;
const RotationAngle RA_45Degree  = 450;
const RotationAngle RA_60Degree  = 600;
const RotationAngle RA_70Degree  = 750;
const RotationAngle RA_90Degree  = 900;
const RotationAngle RA_180Degree = 1800;
const RotationAngle RA_270Degree = 2700;


// for fooling around
enum class  eInvertAxis : unsigned //int32_t
{	IA_Axis_None = 0x0000,
	IA_Axis_X    = 0x0001,
	IA_Axis_Y    = 0x0002,
	IA_Axis_Both = 0x0003
};
