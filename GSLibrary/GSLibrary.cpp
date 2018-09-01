
// GSLibrary.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GSLibrary.h"
#include "FrameMain_GSLibrary.h"

#include "FrameChild_GSLibrary.h"
#include "DocA_GSLibrary.h"
#include "ViewFormA_GSLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//++ CApp_GSLibrary

BEGIN_MESSAGE_MAP(CApp_GSLibrary, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CApp_GSLibrary::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

//+ The one and only CApp_GSLibrary object
CApp_GSLibrary theApp;

//+ CApp_GSLibrary construction
CApp_GSLibrary::CApp_GSLibrary()
{
	m_bHiColorIcons = TRUE;

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GSLibrary.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

//+ CApp_GSLibrary initialization
BOOL CApp_GSLibrary::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
	//- AfxInitRichEdit2();

	// Enable APPLICATION!!! D2D1-support from CWinApp::EnableD2DSupport
	//- Remember you have to enable D2D1-support for each window you want to use D2D1 too
	VERIFY(EnableD2DSupport(D2D1_FACTORY_TYPE_MULTI_THREADED, DWRITE_FACTORY_TYPE_SHARED));

	// Standard initialization
	//- If you are not using these features and wish to reduce the size
	//- of your final executable, you should remove from the following
	//- the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	//- TODO: You should modify this string to be something appropriate
	//- such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(12);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	// serve as the connection between documents, frame windows and views
	//- Add as many document templates as you need and don't forget the views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_GSLibraryTYPE,
		RUNTIME_CLASS(CDocA_GSLibrary),
		RUNTIME_CLASS(CFrameChild_GSLibrary), // custom MDI child frame
		RUNTIME_CLASS(CViewFormA_GSLibrary));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CFrameMain_GSLibrary* pMainFrame = new CFrameMain_GSLibrary;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// call DragAcceptFiles only if there's a suffix
	//- In an MDI app, this should occur immediately after setting m_pMainWnd
	//- Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

//+ CApp_GSLibrary deinitialization
int CApp_GSLibrary::ExitInstance()
{	//+ TODO: handle additional resources you may have added

	return CWinAppEx::ExitInstance();
}

//+ CApp_GSLibrary message handlers


//+ CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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

// App command to run the dialog
void CApp_GSLibrary::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CApp_GSLibrary customization load/save methods

void CApp_GSLibrary::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CApp_GSLibrary::LoadCustomState()
{
}

void CApp_GSLibrary::SaveCustomState()
{
}

// CApp_GSLibrary message handlers



