#pragma once
#include "GSAttributes.h"

class GSAttributes
{ public:
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
	// FrameCorners and FrameStyle
	enum Frame3DStyle m_e3DStyle;
	enum eFrameConnections m_eConnections;
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


  public:
	GSAttributes();
	virtual ~GSAttributes();
};

