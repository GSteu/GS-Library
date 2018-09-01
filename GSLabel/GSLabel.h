#pragma once


// CGSLabel

class CGSLabel : public CStatic
{
	DECLARE_DYNAMIC(CGSLabel)

public:
	CGSLabel();
	virtual ~CGSLabel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


