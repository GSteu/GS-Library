
// MainFrameGSLibrary.h: Schnittstelle der Klasse CMainFrameGSLibrary
//

#pragma once

class CMainFrameGSLibrary : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrameGSLibrary)
public:
	CMainFrameGSLibrary();

// Attribute
public:

// Vorg�nge
public:

// �berschreibungen
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CMainFrameGSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebettete Member der Steuerleiste
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generierte Funktionen f�r die Meldungstabellen
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


