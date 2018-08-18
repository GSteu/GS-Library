
// MainFrameGSLibrary.cpp: Implementierung der Klasse CMainFrameGSLibrary
//

#include "stdafx.h"
#include "GSLibrary.h"

#include "MainFrameGSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrameGSLibrary

IMPLEMENT_DYNAMIC(CMainFrameGSLibrary, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrameGSLibrary, CMDIFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrameGSLibrary-Erstellung/Zerstörung

CMainFrameGSLibrary::CMainFrameGSLibrary()
{
	// TODO: Hier Code für die Memberinitialisierung einfügen
}

CMainFrameGSLibrary::~CMainFrameGSLibrary()
{
}

int CMainFrameGSLibrary::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Fehler beim Erstellen der Symbolleiste.\n");
		return -1;      // Fehler beim Erstellen
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Fehler beim Erstellen der Statusleiste.\n");
		return -1;      // Fehler beim Erstellen
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Löschen Sie diese drei Zeilen, wenn Sie nicht möchten, dass die Systemleiste andockbar ist
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrameGSLibrary::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

// CMainFrameGSLibrary-Diagnose

#ifdef _DEBUG
void CMainFrameGSLibrary::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrameGSLibrary::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrameGSLibrary-Meldungshandler

