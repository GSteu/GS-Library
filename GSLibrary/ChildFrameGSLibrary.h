
// ChildFrameGSLibrary.h: Schnittstelle der Klasse CChildFrameGSLibrary
//

#pragma once

class CChildFrameGSLibrary : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrameGSLibrary)
public:
	CChildFrameGSLibrary();

// Attribute
public:

// Vorgänge
public:

// Überschreibungen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CChildFrameGSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generierte Funktionen für die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
};
