
// SampleDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSampleDlg ダイアログ




CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, &CSampleDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_TEST2, &CSampleDlg::OnBnClickedBtnTest2)
END_MESSAGE_MAP()


// CSampleDlg メッセージ ハンドラー

BOOL CSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(false);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, false);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSampleDlg::OnOK()
{
}


void CSampleDlg::OnCancel()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CDialogEx::OnCancel();
}

void CSampleDlg::AddLog( CString csMessage )
{
	m_List1.AddString( csMessage );
	m_List1.SetCurSel( m_List1.GetCount() - 1 );
}

void CSampleDlg::OnBnClickedBtnTest()
{
	AddLog("***** Test(定義ファイル無し) *****");

	CString csMessage;

	// タグの作成
	// タグを10個作成し、D1000～D1002を割り付けます
	SwPlcTag tags[3];
	for( int i = 0; i < 3; i++ ){
		tags[i].tagId = i;							// タグID
		strcpy_s( tags[i].device, "D" );			// レジスタ名
		tags[i].address = 1000 + i;					// アドレス
		tags[i].dataType = SWPLC_DATATYPE_SHORT;	// データ型
		tags[i].count = 1;							// 要素数(連続したアドレスを配列として登録する場合は配列要素数で設定します)
		tags[i].monitor = 0;						// 0:モニタOff 1:モニタOn
		tags[i].notify = 0;							// 0:通知Off 1:通知On
	}

	// ポートオープン
	CStringA csLibName;
	CStringA csParam;
	CStringA csOption;

	// 接続パラメータ文字列を作成
	csParam =  "Address=127.0.0.1;";				// 接続先アドレス
	csParam += "Port=50001;";						// 接続先ポート
	csParam += "Timeout=1000;";						// 通信タイムアウト時間(ms)
	csParam += "Retry=0;";							// 通信リトライ回数
	csParam += "LogFilePath=.\\;";					// 通信ログ出力先パス
	csParam += "LogFileName=TestLog;";				// 通信ログファイル名
	csParam += "LogSize=100000;";					// 通信ログファイルサイズ(byte)
	csParam += "LogNum=3";							// 通信ログファイル数

	// 通信オプション設定文字列を作成
	// ※PLC固有の通信パラメータを設定します。（PLC機種により内容が変わります)

	// ダミーPLCへ接続します
	csLibName = "SwCom";
	csOption =  "ReadMaxSize=1024;";
	csOption += "WriteMaxSize=1024;";

	//// 三菱PLCへ接続します
	//csLibName = "McCom";
	//csOption =	"Frame=3E;";
	//csOption += "Code=ASCII;";
	//csOption += "MonitoringTimer=0C;";
	//csOption += "NetworkNo=00;";
	//csOption += "PcNo=FF;";
	//csOption += "ReqDestModIONo=03FF;";
	//csOption += "ReqDestModStationNo=00;";
	//csOption += "ReadBitMaxSize=7904;";
	//csOption += "WriteBitMaxSize=7904;";
	//csOption += "ReadWordMaxSize=960;";
	//csOption += "WriteWordMaxSize=960";

	SWPLC_HANDLE handle;
	int ret;

	ret = SwPlcInitPort( 
		&handle,					// 通信ハンドル
		"TEST_PORT",				// 通信ポート名
		csLibName,					// 通信ライブラリ名(McCom/OmronCom/KvCom/SwComなど)
		SWPLC_TYPE_TCP,				// 通信タイプ(TCP/UDP/Serial/Custom)
		tags,						// 登録タグ
		3,							// タグ数
		csParam,					// パラメータ
		csOption					// オプション
		);

	if( ret != SWPLC_OK ){
		AddLog(_T("通信ポートオープンエラー"));
		return;
	}

	AddLog(_T("通信ポートオープン"));

	// Tag0～Tag2に書き込み
	short data;
	data = 100;
	ret = SwPlcWriteShort( handle, 0, data );
	data = 200;
	ret = SwPlcWriteShort( handle, 1, data );
	data = 300;
	ret = SwPlcWriteShort( handle, 2, data );

	// 実行
	ret = SwPlcExecute( handle );
	AddLog(_T("書き込み実行"));

	// 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
	ret = SwPlcResponse( handle, 3000 );

	if( ret == SWPLC_RESPONSE_DONE ){
		AddLog(_T("書込み完了"));
	}else{
		AddLog(_T("書込みエラー"));
	}

	// Tag0～Tag2を読込み
	ret = SwPlcRead( handle, 0 );
	ret = SwPlcRead( handle, 1 );
	ret = SwPlcRead( handle, 2 );
	ret = SwPlcExecute( handle );

	// 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
	ret = SwPlcResponse( handle, 3000 );

	if( ret == SWPLC_RESPONSE_DONE ){
		AddLog(_T("読込み完了"));
	}else{
		AddLog(_T("読込みエラー"));
	}
	
	// PLCから読み込まれた値を取得
	SwPlcGetShort( handle, 0, &data );
	csMessage.Format( _T("Read Tag0 = %d"), data );
	AddLog( csMessage );

	SwPlcGetShort( handle, 1, &data );
	csMessage.Format( _T("Read Tag1 = %d"), data );
	AddLog( csMessage );

	SwPlcGetShort( handle, 2, &data );
	csMessage.Format( _T("Read Tag2 = %d"), data );
	AddLog( csMessage );

	SwPlcClosePort( handle );
}


void CSampleDlg::OnBnClickedBtnTest2()
{
	AddLog("***** Test(定義ファイル有り) *****");

	CString csMessage;
	SWPLC_HANDLE handle;
	int ret;
	ret = SwPlcLoadFile( &handle, ".\\sample.xml" );

	if( ret != SWPLC_OK ){
		AddLog(_T("通信ポートオープンエラー"));
		return;
	}

	AddLog(_T("通信ポートオープン"));

	// Tag0～Tag2に書き込み
	short data;
	data = 100;
	ret = SwPlcWriteShort( handle, 0, data );
	data = 200;
	ret = SwPlcWriteShort( handle, 1, data );
	data = 300;
	ret = SwPlcWriteShort( handle, 2, data );

	// 実行
	ret = SwPlcExecute( handle );
	AddLog(_T("書き込み実行"));

	// 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
	ret = SwPlcResponse( handle, 3000 );

	if( ret == SWPLC_RESPONSE_DONE ){
		AddLog(_T("書込み完了"));
	}else{
		AddLog(_T("書込みエラー"));
	}

	// Tag0～Tag2を読込み
	ret = SwPlcRead( handle, 0 );
	ret = SwPlcRead( handle, 1 );
	ret = SwPlcRead( handle, 2 );
	ret = SwPlcExecute( handle );

	// 完了待ち(3000ms待つ wait = 0:待ちなし wait = -1:完了まで待つ)
	ret = SwPlcResponse( handle, 3000 );

	if( ret == SWPLC_RESPONSE_DONE ){
		AddLog(_T("読込み完了"));
	}else{
		AddLog(_T("読込みエラー"));
	}
	
	// PLCから読み込まれた値を取得
	SwPlcGetShort( handle, 0, &data );
	csMessage.Format( _T("Read Tag0 = %d"), data );
	AddLog( csMessage );

	SwPlcGetShort( handle, 1, &data );
	csMessage.Format( _T("Read Tag1 = %d"), data );
	AddLog( csMessage );

	SwPlcGetShort( handle, 2, &data );
	csMessage.Format( _T("Read Tag2 = %d"), data );
	AddLog( csMessage );

	SwPlcClosePort( handle );
}
