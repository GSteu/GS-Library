
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

// Vorg�nge
public:

// �berschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // �berschrieben, um diese Ansicht darzustellen
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

// Generierte Funktionen f�r die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debugversion in ViewGSLibrary.cpp
inline CDocGSLibrary* CViewGSLibrary::GetDocument() const
   { return reinterpret_cast<CDocGSLibrary*>(m_pDocument); }
#endif

