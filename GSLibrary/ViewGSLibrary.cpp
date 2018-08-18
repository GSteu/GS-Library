
// ViewGSLibrary.cpp: Implementierung der Klasse CViewGSLibrary
//

#include "stdafx.h"
// SHARED_HANDLERS k�nnen in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode f�r das Projekt wird erm�glicht.
#ifndef SHARED_HANDLERS
#include "GSLibrary.h"
#endif

#include "DocGSLibrary.h"
#include "ViewGSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CViewGSLibrary

IMPLEMENT_DYNCREATE(CViewGSLibrary, CScrollView)

BEGIN_MESSAGE_MAP(CViewGSLibrary, CScrollView)
	// Standarddruckbefehle
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CViewGSLibrary-Erstellung/Zerst�rung

CViewGSLibrary::CViewGSLibrary()
{
	// TODO: Hier Code zur Konstruktion einf�gen

}

CViewGSLibrary::~CViewGSLibrary()
{
}

BOOL CViewGSLibrary::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ndern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CScrollView::PreCreateWindow(cs);
}

// CViewGSLibrary-Zeichnung

void CViewGSLibrary::OnDraw(CDC* /*pDC*/)
{
	CDocGSLibrary* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: Code zum Zeichnen der nativen Daten hinzuf�gen
}

void CViewGSLibrary::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: Gesamte Gr��e dieser Ansicht berechnen
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CViewGSLibrary drucken

BOOL CViewGSLibrary::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CViewGSLibrary::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: Zus�tzliche Initialisierung vor dem Drucken hier einf�gen
}

void CViewGSLibrary::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: Bereinigung nach dem Drucken einf�gen
}


// CViewGSLibrary-Diagnose

#ifdef _DEBUG
void CViewGSLibrary::AssertValid() const
{
	CScrollView::AssertValid();
}

void CViewGSLibrary::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDocGSLibrary* CViewGSLibrary::GetDocument() const // Nichtdebugversion ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocGSLibrary)));
	return (CDocGSLibrary*)m_pDocument;
}
#endif //_DEBUG


// CViewGSLibrary-Meldungshandler
