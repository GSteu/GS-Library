================================================================================
    MICROSOFT FOUNDATION CLASS-BIBLIOTHEK: GSLibrary-Projektübersicht
===============================================================================

Diese GSLibrary-Anwendung wurde vom Anwendungs-Assistenten für Sie erstellt. Diese Anwendung zeigt nicht nur die Grundlagen der Verwendung von Microsoft Foundation Classes, sondern dient auch als Ausgangspunkt für das Schreiben Ihrer Anwendung.

Diese Datei bietet eine Übersicht über den Inhalt der einzelnen Dateien, aus
denen Ihre GSLibrary-Anwendung besteht.

GSLibrary.vcxproj
    Dies ist die Hauptprojektdatei für VC++-Projekte, die mit dem Anwendungs-Assistenten generiert werden. Sie enthält Informationen über die Version von Visual C++, mit der die Datei generiert wurde, sowie über die Plattformen, Konfigurationen und Projektfunktionen, die im Anwendungs-Assistenten ausgewählt wurden.

GSLibrary.vcxproj.filters
    Dies ist die Filterdatei für VC++-Projekte, die mithilfe eines Anwendungs-Assistenten erstellt werden. Sie enthält Informationen über die Zuordnung zwischen den Dateien im Projekt und den Filtern. Diese Zuordnung wird in der IDE zur Darstellung der Gruppierung von Dateien mit ähnlichen Erweiterungen unter einem bestimmten Knoten verwendet (z. B. sind CPP-Dateien dem Filter "Quelldateien" zugeordnet).

GSLibrary.h
    Dies ist die Hauptheaderdatei für die Anwendung.
    Sie enthält andere projektspezifische Header (einschließlich Resource.h) und deklariert die CGSLibraryApp-Anwendungsklasse.

GSLibrary.cpp
    Dies ist die wichtigste Anwendungsquelldatei, die die Anwendungsklasse CGSLibraryApp enthält.

GSLibrary.rc
    Dies ist eine Auflistung aller vom Programm verwendeten Microsoft Windows-Ressourcen. Sie enthält die Symbole, Bitmaps und Cursor, die im Unterverzeichnis "RES" gespeichert werden. Diese Datei kann direkt in Microsoft Visual C++ bearbeitet werden. Ihre Projektressourcen befinden sich in 1031.

res\GSLibrary.ico
    Dies ist eine Symboldatei, die als Anwendungssymbol verwendet wird. Dieses Symbol ist in der Hauptressourcendatei GSLibrary.rc enthalten.

res\GSLibrary.rc2
    Diese Datei enthält Ressourcen, die nicht von Microsoft Visual C++ bearbeitet werden. Sie sollten alle Ressourcen, die nicht mit dem Ressourcen-Editor bearbeitet werden können, in dieser Datei platzieren.

GSLibrary.reg
    Dies ist eine Beispiel-REG-Datei, in der die Registrierungseinstellungen dargestellt sind, die vom Framework festgelegt werden. Sie können diese als REG-Datei
    für Ihre Anwendung verwenden oder die Datei einfach löschen und die Standard-RegisterShellFileTypes-Registrierung nutzen.


/////////////////////////////////////////////////////////////////////////////

Für das Hauptrahmenfenster:
    Das Projekt enthält eine Standard-MFC-Schnittstelle.

MainFrameGSLibrary.h, MainFrameGSLibrary.cpp
    Diese Dateien enthalten die CMainFrameGSLibrary-Rahmenklasse, die abgeleitet ist von
    CMDIFrameWnd und alle MDI-Rahmenfunktionen steuert.

res\Toolbar.bmp
    Diese Bitmapdatei wird zum Erstellen von Kachelbildern für die Symbolleiste verwendet.
    Die ursprüngliche Symbol- und Statusleiste werden in der CMainFrameGSLibrary-Klasse erstellt. Bearbeiten Sie diese Bitmapdatei für die Symbolleiste mit dem Ressourcen-Editor, und aktualisieren Sie das IDR_MAINFRAME TOOLBAR-Array in GSLibrary.rc, um Symbolleistenschaltflächen hinzuzufügen.
/////////////////////////////////////////////////////////////////////////////

Für das untergeordnete Rahmenfenster:

ChildFrm.h, ChildFrm.cpp
    Diese Dateien definieren und implementieren die CChildFrameGSLibrary-Klasse, die die untergeordneten Fenster in einer MDI-Anwendung unterstützt.

/////////////////////////////////////////////////////////////////////////////

Der Anwendungs-Assistent erstellt einen Dokumententyp und eine Ansicht:

DocGSLibrary.h, DocGSLibrary.cpp - das Dokument
    Diese Dateien enthalten Ihre CDocGSLibrary-Klasse. Bearbeiten Sie diese Dateien, um Ihre speziellen Dokumentdaten hinzuzufügen sowie um das Speichern und Laden von Dateien zu implementieren (über CDocGSLibrary::Serialize).
    Das Dokument verfügt über die folgenden Zeichenfolgen:
        Dateierweiterung:      GSLib
        Dateityp-ID:        GSLibrary.Document
        Hauptrahmenüberschrift:  GSLibrary
        Dokumententypname:       GSLibrary
        Filtername:         GSLibrary Files (*.GSLib)
        Neuer Dateikurzname: GSLibrary
        Langer Dateitypname: GSLibrary.Document

ViewGSLibrary.h, ViewGSLibrary.cpp - die Ansicht des Dokuments
    Diese Dateien enthalten Ihre CViewGSLibrary-Klasse.
    CViewGSLibrary-Objekte werden verwendet, um CDocGSLibrary-Objekte anzuzeigen.

res\GSLibraryDoc.ico
    Dies ist eine Symboldatei, die als Symbol für untergeordnete MDI-Fenster für die CDocGSLibrary-Klasse verwendet wird. Dieses Symbol ist in der Hauptressourcendatei GSLibrary.rc enthalten.



/////////////////////////////////////////////////////////////////////////////

Andere Funktionen:

Unterstützung für Drucken und Druckvorschau
    Der Anwendungs-Assistent hat Code zum Verarbeiten der Befehle zum Drucken, zur Druckereinrichtung und zur Druckvorschau generiert, indem Memberfunktionen in der CView-Klasse aus der MFC-Bibliothek aufgerufen wurden.

/////////////////////////////////////////////////////////////////////////////

Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    Mit diesen Dateien werden eine vorkompilierte Headerdatei (PCH) mit dem Namen GSLibrary.pch und eine vorkompilierte Typendatei mit dem Namen StdAfx.obj erstellt.

Resource.h
    Dies ist die Standardheaderdatei, die neue Ressourcen-IDs definiert. Die Datei wird mit Microsoft Visual C++ gelesen und aktualisiert.

GSLibrary.manifest
	Anwendungsmanifestdateien werden von Windows XP verwendet, um die Abhängigkeit einer Anwendung von bestimmten Versionen paralleler Assemblys zu beschreiben. Das Ladeprogramm verwendet diese Informationen, um die entsprechende Assembly aus dem Assemblycache oder privat von der Anwendung zu laden. Das Anwendungsmanifest kann zur Neuverteilung als externe .manifest-Datei einbezogen werden, die im selben Ordner wie die ausführbare Datei der Anwendung installiert ist, oder sie wird der ausführbaren Datei in Form einer Ressource hinzugefügt.
/////////////////////////////////////////////////////////////////////////////

Weitere Hinweise:

Der Anwendungs-Assistent weist Sie mit "TODO:"-Kommentaren auf Teile des Quellcodes hin, die Sie ergänzen oder anpassen sollten.

Wenn Ihre Anwendung MFC in einer gemeinsam genutzten DLL verwendet, müssen die MFC-DLLs mitverteilt werden. Wenn Ihre Anwendung eine andere Sprache als Systemsprache verwendet, müssen auch die entsprechende mfc110XXX.DLL für die lokalisierten Ressourcen mitverteilt werden.
Weitere Informationen zu diesen beiden Themen finden Sie im Abschnitt zur Neuverteilung von Visual C++-Anwendungen in der MSDN-Dokumentation.

/////////////////////////////////////////////////////////////////////////////
