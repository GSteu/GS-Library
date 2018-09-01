// GSLabel.cpp : implementation file
//

#include "stdafx.h"
#include "GSLabel.h"


// CGSLabel

IMPLEMENT_DYNAMIC(CGSLabel, CStatic)

CGSLabel::CGSLabel()
{

}

CGSLabel::~CGSLabel()
{
}


BEGIN_MESSAGE_MAP(CGSLabel, CStatic)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CGSLabel message handlers




int CGSLabel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Enable WINDOW!!! D2D1-Support must be done for each and every window
	EnableD2DSupport(TRUE,FALSE;


	return 0;
}
