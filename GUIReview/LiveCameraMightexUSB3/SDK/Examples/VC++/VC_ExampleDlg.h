// VC_ExampleDlg.h : header file
//

#if !defined(AFX_VC_EXAMPLEDLG_H__B59A68E6_D5C3_4D88_9DDB_3D887D6C0BAF__INCLUDED_)
#define AFX_VC_EXAMPLEDLG_H__B59A68E6_D5C3_4D88_9DDB_3D887D6C0BAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVC_ExampleDlg dialog

class CVC_ExampleDlg : public CDialog
{
// Construction
public:
	DEV_HANDLE DevHandle;
	int TotalDevices;
	
	CVC_ExampleDlg(CWnd* pParent = NULL);	// standard constructor
	void SetCallBackStatus( int number );
	void WriteBMPFile(char *FileName, int width, int height, unsigned char * bPtr);
// Dialog Data
	//{{AFX_DATA(CVC_ExampleDlg)
	enum { IDD = IDD_VC_EXAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVC_ExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVC_ExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDeviceinitButton();
	afx_msg void OnGetModuleBUTTON();
	afx_msg void OnStartEngineBUTTON();
	afx_msg void OnShowPanelBUTTON();
	afx_msg void OnHidePanelBUTTON();
	afx_msg void OnStartGrabBUTTON();
	afx_msg void OnStopGrabBUTTON();
	afx_msg void OnStopEngineBUTTON();
	afx_msg void OnUninitailDeviceBUTTON();
	afx_msg void OnSetExposureBUTTON();
	afx_msg void OnIoconfigButton();
	afx_msg void OnIooutputButton();
	afx_msg void OnFramecallbackButton();
	afx_msg void OnSetnormalbutton();
	afx_msg void OnSettriggermodebutton();
	afx_msg void OnSetresolutionButton();
	afx_msg void OnSetgainsButton();
	afx_msg void OnButton1();
	afx_msg void OnXystartButton();
	afx_msg void OnGetFrameDataBUTTON();
	afx_msg void OnGetFrameDataTestBUTTON();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VC_EXAMPLEDLG_H__B59A68E6_D5C3_4D88_9DDB_3D887D6C0BAF__INCLUDED_)
