// VC_Example.h : main header file for the VC_EXAMPLE application
//

#if !defined(AFX_VC_EXAMPLE_H__52AB1D1C_3F83_4536_B6F9_BE657D9029E2__INCLUDED_)
#define AFX_VC_EXAMPLE_H__52AB1D1C_3F83_4536_B6F9_BE657D9029E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVC_ExampleApp:
// See VC_Example.cpp for the implementation of this class
//

class CVC_ExampleApp : public CWinApp
{
public:
	CVC_ExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVC_ExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVC_ExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC_EXAMPLE_H__52AB1D1C_3F83_4536_B6F9_BE657D9029E2__INCLUDED_)
