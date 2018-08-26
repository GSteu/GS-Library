
// ViewGSLibrary.h: Schnittstelle der Klasse CViewGSLibrary
//

#pragma once


class CViewGSLibrary : public CScrollView
{
protected: // Nur aus Serialisierung erstellen
	CViewGSLibrary();
	DECLARE_DYNCREATE(CViewGSLibrary)

// Attribute
public:
	CDocGSLibrary* GetDocument() const;

	CD2DTextFormat*          m_pTextFormat;
	CD2DSolidColorBrush*     m_pBlackBrush;
	CD2DLinearGradientBrush* m_pLinearGradientBrush;

// Vorgänge
public:

// Überschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // Überschrieben, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // Erster Aufruf nach Erstellung
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementierung
public:
	virtual ~CViewGSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen für die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // Debugversion in ViewGSLibrary.cpp
inline CDocGSLibrary* CViewGSLibrary::GetDocument() const
   { return reinterpret_cast<CDocGSLibrary*>(m_pDocument); }
#endif

