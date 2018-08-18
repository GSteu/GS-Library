
// ChildFrameGSLibrary.cpp: Implementierung der Klasse CChildFrameGSLibrary
//

#include "stdafx.h"
#include "GSLibrary.h"

#include "ChildFrameGSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrameGSLibrary

IMPLEMENT_DYNCREATE(CChildFrameGSLibrary, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrameGSLibrary, CMDIChildWnd)
END_MESSAGE_MAP()

// CChildFrameGSLibrary-Erstellung/Zerstörung

CChildFrameGSLibrary::CChildFrameGSLibrary()
{
	// TODO: Hier Code für die Memberinitialisierung einfügen
}

CChildFrameGSLibrary::~CChildFrameGSLibrary()
{
}


BOOL CChildFrameGSLibrary::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Ändern Sie die Fensterklasse oder die Stile hier, indem Sie CREATESTRUCT ändern
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrameGSLibrary-Diagnose

#ifdef _DEBUG
void CChildFrameGSLibrary::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrameGSLibrary::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrameGSLibrary-Meldungshandler
