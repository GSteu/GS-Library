
// GSLibrary.h: Hauptheaderdatei f�r die GSLibrary-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"       // Hauptsymbole


// CGSLibraryApp:
// Siehe GSLibrary.cpp f�r die Implementierung dieser Klasse
//

class CGSLibraryApp : public CWinApp
{
public:
	CGSLibraryApp();


// �berschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGSLibraryApp theApp;
