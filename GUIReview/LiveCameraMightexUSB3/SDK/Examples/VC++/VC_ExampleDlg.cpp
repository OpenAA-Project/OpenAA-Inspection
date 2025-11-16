// VC_ExampleDlg.cpp : implementation file

#include "stdafx.h"
#include "VC_Example.h"
#include "VC_ExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ALL_DEVICES	0x88

int FrameCount;
int FrameTimeStamp[200];
extern CVC_ExampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVC_ExampleDlg dialog

CVC_ExampleDlg::CVC_ExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVC_ExampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVC_ExampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVC_ExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVC_ExampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVC_ExampleDlg, CDialog)
	//{{AFX_MSG_MAP(CVC_ExampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DEVICEINIT_BUTTON, OnDeviceinitButton)
	ON_BN_CLICKED(IDC_GetModule_BUTTON, OnGetModuleBUTTON)
	ON_BN_CLICKED(IDC_StartEngine_BUTTON, OnStartEngineBUTTON)
	ON_BN_CLICKED(IDC_ShowPanel_BUTTON, OnShowPanelBUTTON)
	ON_BN_CLICKED(IDC_HidePanel_BUTTON, OnHidePanelBUTTON)
	ON_BN_CLICKED(IDC_StartGrab_BUTTON, OnStartGrabBUTTON)
	ON_BN_CLICKED(IDC_StopGrab_BUTTON, OnStopGrabBUTTON)
	ON_BN_CLICKED(IDC_StopEngine_BUTTON, OnStopEngineBUTTON)
	ON_BN_CLICKED(IDC_UninitailDevice_BUTTON, OnUninitailDeviceBUTTON)
	ON_BN_CLICKED(IDC_SetExposure_BUTTON, OnSetExposureBUTTON)
	ON_BN_CLICKED(IDC_IOCONFIG_BUTTON, OnIoconfigButton)
	ON_BN_CLICKED(IDC_IOOUTPUT_BUTTON, OnIooutputButton)
	ON_BN_CLICKED(IDC_FRAMECALLBACK_BUTTON, OnFramecallbackButton)
	ON_BN_CLICKED(IDC_SETNORMALBUTTON, OnSetnormalbutton)
	ON_BN_CLICKED(IDC_SETTRIGGERMODEBUTTON, OnSettriggermodebutton)
	ON_BN_CLICKED(IDC_SETRESOLUTION_BUTTON, OnSetresolutionButton)
	ON_BN_CLICKED(IDC_SETGAINS_BUTTON, OnSetgainsButton)
	ON_BN_CLICKED(IDC_XYSTART_BUTTON, OnXystartButton)
	ON_BN_CLICKED(IDC_GetFrameData_BUTTON, OnGetFrameDataBUTTON)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVC_ExampleDlg message handlers
void CameraFaultCallBack( int Device, int ImageType )
{
	// Note: It's recommended to stop the engine and close the application
	SSClassicUSB_StopCameraEngine();
	SSClassicUSB_UnInitDevice();
}

void FrameCallBack( TProcessedDataProperty* Attributes, unsigned char *Frameptr )
{
	int i;
	
	if ( Attributes->CameraID == 1 ) // The working camera.
	{
		// All frame related attributes is in Attributes.
		// All frame data is pointed by Frameptr
		((CVC_ExampleDlg *)theApp.m_pMainWnd)->SetCallBackStatus( Attributes->TimeStamp );
		//SetDlgItemText( IDC_CALLBACK_STATIC, CString(  ) );
		/*
		*  Note that user can check the Attributes's items for the information
		*  of this frame.
		*/
	}
}

void CVC_ExampleDlg::SetCallBackStatus( int ShowNo )
{
	CString numberStr(" ");

	numberStr.Format( "%d", ShowNo );
	SetDlgItemText( IDC_CALLBACK_STATIC, numberStr );
}

BOOL CVC_ExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(false);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, false);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVC_ExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVC_ExampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVC_ExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVC_ExampleDlg::OnOK() 
{
	// TODO: Add extra validation here
	// Clean Up
	CDialog::OnOK();
}

// Button Events:
void CVC_ExampleDlg::OnDeviceinitButton() 
{
	CString MyStr;
	byte *buffer;

	// TODO: Add your control notification handler code here
	TotalDevices = SSClassicUSB_InitDevice();
	/*
	while (TotalDevices == 0 )
	{
		SSClassicUSB_UnInitDevice();
		TotalDevices = SSClassicUSB_InitDevice();
	}
	*/
	MyStr.Format( "There are %d devices.", TotalDevices );
	MessageBox( MyStr );
}

void CVC_ExampleDlg::OnUninitailDeviceBUTTON() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_UnInitDevice();
}

void CVC_ExampleDlg::OnGetModuleBUTTON() 
{
	char ModuleNo[32], SerialNo[32];

	// TODO: Add your control notification handler code here
	// We take the first Device (if there're more than one) as example.
	if ( SSClassicUSB_GetModuleNoSerialNo( 1, ModuleNo, SerialNo ) == 1 )
	{
		SetDlgItemText(IDC_ModuleNo_STATIC, CString( ModuleNo ) );
		SetDlgItemText(IDC_SerialNo_STATIC, CString( SerialNo ) );
	}
}

void CVC_ExampleDlg::OnStartEngineBUTTON() 
{
	int i;

	// We only put the first camera to working set...user might also
	// add more than one camera to working set...and the CameraID passed
	// in SSClassicUSB_AddDeviceToWorkingSet( CameraID ) should also be used as
	// the device handle to invoke other APIs which is with deviceID
	// as the first argument.
	for ( i=1; i<(TotalDevices+1); i++)
		SSClassicUSB_AddDeviceToWorkingSet( i );
	//SSClassicUSB_StartCameraEngine( m_hWnd, 8, 2, 0);  // Callback in message loop
	SSClassicUSB_StartCameraEngine( m_hWnd, 8, 2, 1); // callback in working thread.
}

void CVC_ExampleDlg::OnStopEngineBUTTON() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_StopCameraEngine();
}

void CVC_ExampleDlg::OnShowPanelBUTTON() 
{
	// TODO: Add your control notification handler code here
	// Note: The panel is for the first camera ( we have camera from 
	// 1.. to .. TotalDevices )
	SSClassicUSB_ShowFactoryControlPanel( 1, "123456" );
}

void CVC_ExampleDlg::OnHidePanelBUTTON() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_HideFactoryControlPanel();
}

void CVC_ExampleDlg::OnStartGrabBUTTON() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_StartFrameGrab( ALL_DEVICES,  GRAB_FRAME_FOREVER );
}

void CVC_ExampleDlg::OnStopGrabBUTTON() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_StopFrameGrab( ALL_DEVICES );
}

void CVC_ExampleDlg::OnSetExposureBUTTON() 
{
	// TODO: Add your control notification handler code here
	// 30x50 -- the exposure time is 1500us.
	// false -- camera will NOT store the exposure time to its NV memory.
	SSClassicUSB_SetExposureTime( 1, 30 );
}

void CVC_ExampleDlg::OnIoconfigButton() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_SetGPIOConfig( 1, 0x03 ); // Pin1, 2 as Input, Pin3, 4 as output
}

void CVC_ExampleDlg::OnIooutputButton() 
{
	unsigned char RcvByte;

	// TODO: Add your control notification handler code here
	SSClassicUSB_SetGPIOInOut( 1, 0x04, &RcvByte );  // OUTPUT: High for Pin3, Low for Pin4
	                                           // All four pin states are in RcvByte.
	//SetDlgItemText( IDC_CALLBACK_STATIC, CString( RcvByte ) );
}

void CVC_ExampleDlg::OnFramecallbackButton() 
{
	// FrameType = 0, which means Raw Data, for this BUF Camera
	// FrameType = 1 (processed data) is the same as RAW data.
	SSClassicUSB_InstallFrameHooker( 0, FrameCallBack );
	SSClassicUSB_InstallUSBDeviceHooker( CameraFaultCallBack );
}

void CVC_ExampleDlg::OnSetnormalbutton() 
{
	// TODO: Add your control notification handler code here
	// Set To Normal Mode
	SSClassicUSB_SetCameraWorkMode( 1, 0 );
}

void CVC_ExampleDlg::OnSettriggermodebutton() 
{
	// TODO: Add your control notification handler code here
	// Set to Trigger mode.
	SSClassicUSB_SetCameraWorkMode( 1, 1 );
}

void CVC_ExampleDlg::OnSetresolutionButton() 
{
	// TODO: Add your control notification handler code here
	//NewClassicUSB_SetResolution( 1, 8, 1, 4 );
	SSClassicUSB_SetCustomizedResolution( 1, 752, 480, 0, 0 );
}

void CVC_ExampleDlg::OnSetgainsButton() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_SetGains( 1, 8, 8, 8);
}

void CVC_ExampleDlg::OnXystartButton() 
{
	// TODO: Add your control notification handler code here
	SSClassicUSB_SetXYStart( 1, 0, 0 );
}

void CVC_ExampleDlg::OnGetFrameDataBUTTON() 
{
	unsigned char tmpArray[10000];
	unsigned char *sPtr;
	unsigned char *rPtr;
	int result, i;

	// TODO: Add your control notification handler code here
	SSClassicUSB_InstallFrameHooker( 0, NULL );
	rPtr = SSClassicUSB_GetCurrentFrame(0, 1, sPtr);
	if ( rPtr != NULL )
	{
		// For demo purpose, we check the first 10000 bytes only
		// The first 14x4 bytes (14 ints) are properties, the following
		// are image data. Note that the first 1 or 2 rows might be
		// Optical Black rows (sensor dependant).
		for (i=0;i<10000;i++)
			tmpArray[i] = *sPtr++;
	}
}

