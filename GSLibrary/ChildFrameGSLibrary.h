
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

// Vorg�nge
public:

// �berschreibungen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CChildFrameGSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generierte Funktionen f�r die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
};
