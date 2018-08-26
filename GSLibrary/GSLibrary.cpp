
// GSLibrary.cpp: Definiert das Klassenverhalten f�r die Anwendung.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GSLibrary.h"
#include "MainFrameGSLibrary.h"

#include "ChildFrameGSLibrary.h"
#include "DocGSLibrary.h"
#include "ViewGSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGSLibraryApp

BEGIN_MESSAGE_MAP(CGSLibraryApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGSLibraryApp::OnAppAbout)
	// Dateibasierte Standarddokumentbefehle
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standarddruckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGSLibraryApp-Erstellung

CGSLibraryApp::CGSLibraryApp()
{
	// TODO: Ersetzen Sie die Anwendungs-ID-Zeichenfolge unten durch eine eindeutige ID-Zeichenfolge; empfohlen
	// Das Format f�r die Zeichenfolge ist: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GSLibrary.AppID.NoVersion"));

	// TODO: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}

// Das einzige CGSLibraryApp-Objekt

CGSLibraryApp theApp;


// CGSLibraryApp-Initialisierung

BOOL CGSLibraryApp::InitInstance()
{
	// InitCommonControlsEx() ist f�r Windows XP erforderlich, wenn ein Anwendungsmanifest
	// die Verwendung von ComCtl32.dll Version 6 oder h�her zum Aktivieren
	// von visuellen Stilen angibt.  Ansonsten treten beim Erstellen von Fenstern Fehler auf.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Legen Sie dies fest, um alle allgemeinen Steuerelementklassen einzubeziehen,
	// die Sie in Ihrer Anwendung verwenden m�chten.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	EnableD2DSupport(D2D1_FACTORY_TYPE_MULTI_THREADED, DWRITE_FACTORY_TYPE_SHARED);
	
	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() ist f�r die Verwendung des RichEdit-Steuerelements erforderlich.	
	// AfxInitRichEdit2();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht verwenden und die Gr��e
	// der ausf�hrbaren Datei verringern m�chten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// �ndern Sie den Registrierungsschl�ssel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: �ndern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));
	LoadStdProfileSettings(12);  // Standard INI-Dateioptionen laden (einschlie�lich MRU)


	// Dokumentvorlagen der Anwendung registrieren.  Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_GSLibraryTYPE,
		RUNTIME_CLASS(CDocGSLibrary),
		RUNTIME_CLASS(CChildFrameGSLibrary), // Benutzerspezifischer MDI-Child-Rahmen
		RUNTIME_CLASS(CViewGSLibrary));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Haupt-MDI-Rahmenfenster erstellen
	CMainFrameGSLibrary* pMainFrame = new CMainFrameGSLibrary;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Rufen Sie DragAcceptFiles nur auf, wenn eine Suffix vorhanden ist.
	//  In einer MDI-Anwendung ist dies unmittelbar nach dem Festlegen von m_pMainWnd erforderlich
	// �ffnen mit Drag Drop aktivieren
	m_pMainWnd->DragAcceptFiles();

	// Befehlszeile auf Standardumgebungsbefehle �berpr�fen, DDE, Datei �ffnen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DDE-Execute-Open aktivieren
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Verteilung der in der Befehlszeile angegebenen Befehle.  Gibt FALSE zur�ck, wenn
	// die Anwendung mit /RegServer, /Register, /Unregserver oder /Unregister gestartet wurde.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Das Hauptfenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CGSLibraryApp::ExitInstance()
{
	//TODO: Zus�tzliche Ressourcen behandeln, die Sie m�glicherweise hinzugef�gt haben
	return CWinApp::ExitInstance();
}

// CGSLibraryApp-Meldungshandler


// CAboutDlg-Dialogfeld f�r Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausf�hren des Dialogfelds
void CGSLibraryApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGSLibraryApp-Meldungshandler



