
// DocGSLibrary.cpp: Implementierung der Klasse CDocGSLibrary
//

#include "stdafx.h"
// SHARED_HANDLERS können in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode für das Projekt wird ermöglicht.
#ifndef SHARED_HANDLERS
#include "GSLibrary.h"
#endif

#include "DocGSLibrary.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDocGSLibrary

IMPLEMENT_DYNCREATE(CDocGSLibrary, CDocument)

BEGIN_MESSAGE_MAP(CDocGSLibrary, CDocument)
END_MESSAGE_MAP()


// CDocGSLibrary-Erstellung/Zerstörung

CDocGSLibrary::CDocGSLibrary()
{
	// TODO: Hier Code für One-Time-Konstruktion einfügen

}

CDocGSLibrary::~CDocGSLibrary()
{
}

BOOL CDocGSLibrary::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}




// CDocGSLibrary-Serialisierung

void CDocGSLibrary::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: Hier Code zum Speichern einfügen
	}
	else
	{
		// TODO: Hier Code zum Laden einfügen
	}
}

#ifdef SHARED_HANDLERS

// Unterstützung für Miniaturansichten
void CDocGSLibrary::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Ändern Sie diesen Code, um die Dokumentdaten zu zeichnen.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Unterstützung für Suchhandler
void CDocGSLibrary::InitializeSearchContent()
{
	CString strSearchContent;
	// Suchinhalte aus Dokumentdaten festlegen. 
	// Die Inhaltsteile sollten durch ";" getrennt werden.

	// Beispiel:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDocGSLibrary::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDocGSLibrary-Diagnose

#ifdef _DEBUG
void CDocGSLibrary::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocGSLibrary::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDocGSLibrary-Befehle
