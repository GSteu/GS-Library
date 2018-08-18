
// GSLibrary.h: Hauptheaderdatei für die GSLibrary-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CGSLibraryApp:
// Siehe GSLibrary.cpp für die Implementierung dieser Klasse
//

class CGSLibraryApp : public CWinApp
{
public:
	CGSLibraryApp();


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGSLibraryApp theApp;
