
// DocGSLibrary.h: Schnittstelle der Klasse CDocGSLibrary
//


#pragma once


class CDocGSLibrary : public CDocument
{
protected: // Nur aus Serialisierung erstellen
	CDocGSLibrary();
	DECLARE_DYNCREATE(CDocGSLibrary)

// Attribute
public:

// Vorg�nge
public:

// �berschreibungen
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementierung
public:
	virtual ~CDocGSLibrary();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen f�r die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Hilfsfunktion, die Suchinhalt f�r Suchhandler festlegt
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
