#include "networkdriveautoconnectResource.h"
//
//		NetworkDriveAutoConnect source
//
//		Version 0.1c
//

#include "networkdriveautoconnect.h"
#include <windows.h>
#include <fstream>
#include <sstream>
#include <QApplication>
#include <QTextCodec>
#include <QFileDialog>
#include <QCloseEvent>

#pragma comment(lib, /**/"Mpr.lib")

using namespace std;

NetworkDriveAutoConnect::NetworkDriveAutoConnect(QWidget *parent, const QString &iniFilename, bool loop, DWORD loopTime, Qt::WindowFlags flags)
: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	LangSolver.SetUI(this);

	// ネットリソースの初期化と変数への関連付け
	memset(&m_nr, 0, sizeof(m_nr));
	m_nr.dwType = RESOURCETYPE_DISK;
	m_nr.lpLocalName = m_LocalDriverName;
	m_nr.lpRemoteName = m_ConctFolderPass;

	// 各メンバ変数の初期化
	memset(m_LocalDriverName, 0, sizeof(m_LocalDriverName));
	memset(m_ConctFolderPass, 0, sizeof(m_ConctFolderPass));
	memset(m_LogonUserName, 0, sizeof(m_LogonUserName));
	memset(m_LogonPassword, 0, sizeof(m_LogonPassword));
	memset(m_IniFilename, 0, sizeof(m_IniFilename));
	m_retrydelay = 0;
	m_IsAutoConnectStarted = false;

	m_LoopEnable = loop;
	m_isConnected = false;
	m_LoopTime = loopTime;

	// バージョン
	wcscpy(m_IniVersionReaded, L"0.1a"); // 初期バージョン
	wcscpy(m_IniVersionLatest, L"0.1b"); // 最終バージョン

	QFileInfo	FInfo(iniFilename);

	FInfo.absoluteFilePath().toWCharArray(m_IniFilename);
	//wcscpy(m_IniFilename, L"NetworkDriveAutoConnectInfo.ini");

	// 日本語使用宣言
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	connect( &QTimeAutoConnect, SIGNAL( frameChanged(int) ), ui.progressBar, SLOT( setValue(int) ));
	connect( &QTimeAutoConnect, SIGNAL( finished() ), this, SLOT( TryAutoConnection() ));

	if(QFile::exists(QString::fromWCharArray(m_IniFilename)))
	{
		ReadIniFile(m_IniFilename,true);
		UpdateData(true);
		on_QBtnConnectStart_clicked();
	}

	if(m_IsAutoConnectStarted==true){
		minimizeAction	=new QAction("Minimize",this);
		connect(minimizeAction	,SIGNAL(triggered()),this,SLOT(hide()));
		showAction		=new QAction(QString::fromWCharArray(m_LocalDriverName),this);
		connect(showAction		,SIGNAL(triggered()),this,SLOT(showNormal()));
		quitAction		=new QAction("quit",this);
		connect(quitAction		,SIGNAL(triggered()),qApp,SLOT(quit()));

		TrayIconMenu=new QMenu(this);
		TrayIconMenu->addAction(minimizeAction);
		TrayIconMenu->addAction(showAction);
		TrayIconMenu->addAction(quitAction);

		TrayIcon	=new QSystemTrayIcon(this);
		TrayIcon->setContextMenu(TrayIconMenu);
		TrayIcon->setIcon(QIcon(QPixmap(":Resources/NDAC.png")));
		//TrayIcon->setIcon(QIcon("NDAC.png"));
		TrayIcon->show();
	}

}

NetworkDriveAutoConnect::~NetworkDriveAutoConnect()
{
	
}

void NetworkDriveAutoConnect::setLoopEnable(bool enable)
{
	m_LoopEnable = enable;
}

void NetworkDriveAutoConnect::TryAutoConnection()
{
	DWORD chk = WNetAddConnection2(
		&m_nr,
		m_LogonPassword[0]==0 ? NULL : m_LogonPassword,
		m_LogonUserName[0]==0 ? NULL : m_LogonUserName,
		NULL
		);
	if(IsWNetAdded(chk))
	{
		QString str;
		GetWNetAddConnection2ErrorString(chk, &str);
		ui.QLblStateInfo->setText(str);
		ui.progressBar->setValue(0);

		//QString qstr = QString(tr("%1")).arg(g_retrynum);
		//ui.QLblStateInfo->setText(qstr);
		//g_retrynum ++;

		QTimeAutoConnect.start();
	}
	else
	{
		ui.QLblStateInfo->setText(LangSolver.GetString(networkdriveautoconnect_LS,LID_0)/*"ネットワークドライバが確立しました"*/);
		m_isConnected = true;
		accessDrive(ui.QLiedLocalDriveName->text());
		if(m_LoopEnable==false){
			exit(EXIT_SUCCESS);
		}else{

			QTimeAutoConnect.setDuration(m_LoopTime);
			QTimeAutoConnect.setFrameRange(0, m_LoopTime / 100);
			QTimeAutoConnect.setUpdateInterval(m_LoopTime / 100 < 50 ? m_LoopTime / 100 : 50);
			QTimeAutoConnect.setCurveShape(QTimeLine::CurveShape::LinearCurve);

			ui.progressBar->setRange(0, m_LoopTime / 100);
			ui.progressBar->setValue(0);
				
			ui.QLblStateInfo->setText("Keep Connecting...");
			setWindowState(Qt::WindowState::WindowMinimized);
			QTimeAutoConnect.setCurrentTime(0);
			ui.progressBar->setValue(0);
			QTimeAutoConnect.start();

			QString str = LangSolver.GetString(networkdriveautoconnect_LS,LID_21)/*"接続中断"*/;
			ui.QBtnConnectStart->setText(str);
			m_IsAutoConnectStarted = true;
		}
		return;
	}
}

void NetworkDriveAutoConnect::on_QBtnExitButton_clicked()
{
	exit(EXIT_SUCCESS);
}

void NetworkDriveAutoConnect::on_QBtnSaveDefault_clicked()
{
	WriteIniFile(m_IniFilename);
}

void NetworkDriveAutoConnect::on_QBtnConnectNow_clicked()
{
	bool timeline_restart = false;

	if(QTimeAutoConnect.state())
	{
		QTimeAutoConnect.stop();
		QTimeAutoConnect.setCurrentTime(0);
		ui.progressBar->setValue(0);
		timeline_restart = true;
	}

	// ネットワークドライブ情報の設定
	NETRESOURCE nr;
	memset(&nr, 0, sizeof(nr));
	nr.dwType = RESOURCETYPE_DISK;

	// ネットワークドライブ名
	GetLocalDriveName(m_LocalDriverName, sizeof(m_LocalDriverName));
	nr.lpLocalName = m_LocalDriverName;

	// ネットワークドライブパス
	GetConctFolderPass(m_ConctFolderPass, sizeof(m_ConctFolderPass));
	nr.lpRemoteName = m_ConctFolderPass;

	// ユーザー名
	GetLogonUserName(m_LogonUserName, sizeof(m_LogonUserName));

	// パスワード
	GetLogonPassword(m_LogonPassword, sizeof(m_LogonPassword));

	// 接続
	DWORD chk = WNetAddConnection2(
		&nr,
		m_LogonPassword[0]==0 ? NULL : m_LogonPassword,
		m_LogonUserName[0]==0 ? NULL : m_LogonUserName,
		NULL
		);


	QString str;
	GetWNetAddConnection2ErrorString(chk, &str);
	ui.QLblStateInfo->setText(str);

	if(timeline_restart)
	{
		QTimeAutoConnect.start();
	}
}

int NetworkDriveAutoConnect::GetWNetAddConnection2ErrorString(DWORD errid, QString* buffer)
{
	switch(errid){
	case NO_ERROR:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_1)/*"接続が確立されました。"*/;
		return EXIT_SUCCESS;

	case ERROR_ACCESS_DENIED:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_2)/*"ネットワーク資源へのアクセスが拒否されました。"*/;
		return EXIT_FAILURE;

	case ERROR_ALREADY_ASSIGNED:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_3)/*"指定したローカルデバイスは既にネットワーク資源に接続されています。"*/;
		return EXIT_SUCCESS;

	case ERROR_BAD_DEV_TYPE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_4)/*"ローカルデバイスの種類とネットワーク資源の種類が一致しません。"*/;
		return EXIT_FAILURE;

	case ERROR_BAD_DEVICE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_5)/*"ローカルネットワークドライブ名が無効です。"*/;
		return EXIT_FAILURE;

	case ERROR_BAD_NET_NAME:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_6)/*"共有ネットワークフォルダパスをどのネットワーク資源のプロバイダも受け付けません。\n資源の名前が無効か、指定したパスが見つかりません。"*/;
		return EXIT_FAILURE;

	case ERROR_BAD_PROFILE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_7)/*"ユーザープロファイルの形式が正しくありません。"*/;
		return EXIT_FAILURE;

	case ERROR_BAD_PROVIDER:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_8)/*"指定した値がどのプロバイダとも一致しません。"*/;
		return EXIT_FAILURE;

	case ERROR_BUSY:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_9)/*"ルーターまたはプロバイダがビジー（おそらく初期化中）です。"*/;
		return EXIT_FAILURE;

	case ERROR_CANCELLED:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_10)/*"ネットワーク資源のプロバイダのいずれかでユーザーがダイアログボックスを使って\n接続操作を取り消したか、接続先の資源が接続操作を取り消しました。"*/;
		return EXIT_FAILURE;

	case ERROR_CANNOT_OPEN_PROFILE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_11)/*"恒久的な接続を処理するためのユーザープロファイルを開くことができません。"*/;
		return EXIT_FAILURE;

	case ERROR_DEVICE_ALREADY_REMEMBERED:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_12)/*"指定したローカルデバイス名のエントリは既にユーザープロファイル内に存在します。"*/;
		return EXIT_FAILURE;

	case ERROR_EXTENDED_ERROR:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_13)/*"ネットワーク固有のエラーが発生しました。"*/;
		return EXIT_FAILURE;

	case ERROR_INVALID_PASSWORD:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_14)/*"指定したパスワードが無効です。"*/;
		return EXIT_FAILURE;

	case ERROR_NETWORK_UNREACHABLE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_15)/*"ネットワークに到達できません。ネットワークのトラブルシューティングについては\nWindows ヘルプを参照してください。"*/;
		return EXIT_FAILURE;

	case ERROR_NO_NETWORK:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_16)/*"ネットワークに接続されていません。"*/;
		return EXIT_FAILURE;

	case ERROR_LOGON_FAILURE:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_17)/*"ログオン失敗: ユーザー名を認識できないか、またはパスワードが間違っています。"*/;
		return EXIT_FAILURE;

	case ERROR_NO_NET_OR_BAD_PATH:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_18)/*"ネットワークコンポーネントが開始されていないか、指定した名前が利用できないために、\n操作を行えませんでした。"*/;
		return EXIT_FAILURE;

	default:
		*buffer =	LangSolver.GetString(networkdriveautoconnect_LS,LID_19)/*"不明なエラーが発生しました。"*/;
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}

int NetworkDriveAutoConnect::IsWNetAdded(DWORD errid)
{
	if(errid==NO_ERROR || errid==ERROR_ALREADY_ASSIGNED)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

void NetworkDriveAutoConnect::accessDrive(const QString &path)
{
	QDir dir;
	dir.cd(path);
	dir.refresh();
	const QString name = /**/"NDAC_KeepAccessTempFolder";
	dir.mkdir(name);
	QElapsedTimer timer;
	timer.start();
	while(timer.elapsed()<1000)
		;
	dir.rmdir(name);
}

int NetworkDriveAutoConnect::GetLocalDriveName(wchar_t* buffer, size_t len)
{
	if(ui.QLiedLocalDriveName->text().size() > len)return EXIT_FAILURE;

	ui.QLiedLocalDriveName->text().toWCharArray(buffer);
	for(int i=0; i<wcslen(buffer) && i<len; i++){
		if(buffer[i]=='/'){
			buffer[i] = '\\';
		}
	}

	return EXIT_SUCCESS;
}
int NetworkDriveAutoConnect::GetConctFolderPass(wchar_t* buffer, size_t len)
{
	if(ui.QLiedConctFolderPass->text().size() > len)return EXIT_FAILURE;

	ui.QLiedConctFolderPass->text().toWCharArray(buffer);
	for(int i=0; i<wcslen(buffer) && i<len; i++){
		if(buffer[i]=='/'){
			buffer[i] = '\\';
		}
	}

	return EXIT_SUCCESS;
}
int NetworkDriveAutoConnect::GetLogonUserName(wchar_t* buffer, size_t len)
{
	if(ui.QLiedLogon_UserName->text().size() > len)return EXIT_FAILURE;
	ui.QLiedLogon_UserName->text().toWCharArray(buffer);
	return EXIT_SUCCESS;
}
int NetworkDriveAutoConnect::GetLogonPassword(wchar_t* buffer, size_t len)
{
	if(ui.QLiedLogon_Password->text().size() > len)return EXIT_FAILURE;
	ui.QLiedLogon_Password->text().toWCharArray(buffer);
	return EXIT_SUCCESS;
}

void NetworkDriveAutoConnect::on_QBtnConnectStart_clicked()
{
	if(m_IsAutoConnectStarted==false)
	{
		ChangeQLineEditEnable(false);
		UpdateData();
		DWORD ret;
		ret = WNetAddConnection2(
			&m_nr,
			m_LogonPassword[0]==0 ? NULL : m_LogonPassword,
			m_LogonUserName[0]==0 ? NULL : m_LogonUserName,
			NULL);
		if(IsWNetAdded(ret)==EXIT_SUCCESS)
		{
			ui.QLblStateInfo->setText(LangSolver.GetString(networkdriveautoconnect_LS,LID_20)/*"ネットワークドライバが確立しました"*/);
			accessDrive(ui.QLiedLocalDriveName->text());
			if(m_LoopEnable==false){
				exit(EXIT_SUCCESS);
			}else{
				QTimeAutoConnect.setDuration(m_LoopTime);
				QTimeAutoConnect.setFrameRange(0, m_LoopTime / 100);
				QTimeAutoConnect.setUpdateInterval(m_LoopTime / 100 < 50 ? m_LoopTime / 100 : 50);
				QTimeAutoConnect.setCurveShape(QTimeLine::CurveShape::LinearCurve);

				ui.progressBar->setRange(0, m_LoopTime / 100);
				ui.progressBar->setValue(0);
				
				ui.QLblStateInfo->setText("Keep Connecting...");
				setWindowState(Qt::WindowState::WindowMinimized);
				QTimeAutoConnect.setCurrentTime(0);
				ui.progressBar->setValue(0);
				QTimeAutoConnect.start();

				QString str = LangSolver.GetString(networkdriveautoconnect_LS,LID_21)/*"接続中断"*/;
				ui.QBtnConnectStart->setText(str);
				m_IsAutoConnectStarted = true;

				TM.setInterval(5000);
				TM.setSingleShot(true);
				connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
				TM.start();
			}
			return;
		}

		QTimeAutoConnect.setDuration(m_retrydelay);
		QTimeAutoConnect.setFrameRange(0, m_retrydelay / 100);
		QTimeAutoConnect.setUpdateInterval(m_retrydelay / 100 < 50 ? m_retrydelay / 100 : 50);
		QTimeAutoConnect.setCurveShape(QTimeLine::CurveShape::LinearCurve);

		ui.progressBar->setRange(0, m_retrydelay / 100);
		ui.progressBar->setValue(0);

		QString str = LangSolver.GetString(networkdriveautoconnect_LS,LID_21)/*"接続中断"*/;
		ui.QBtnConnectStart->setText(str);
		m_IsAutoConnectStarted = true;

		QString err_log;
		GetWNetAddConnection2ErrorString(ret, &err_log);

		ui.QLblStateInfo->setText(err_log);
		QTimeAutoConnect.start();
	}
	else
	{
		QTimeAutoConnect.stop();
		QTimeAutoConnect.setCurrentTime(0);
		ui.progressBar->setValue(0);

		ChangeQLineEditEnable(true);

		QString str = LangSolver.GetString(networkdriveautoconnect_LS,LID_22)/*"接続開始"*/;
		ui.QBtnConnectStart->setText(str);
		m_IsAutoConnectStarted = false;
	}
}

void NetworkDriveAutoConnect::ChangeQLineEditEnable(bool is_able)
{
	ui.QLiedConctFolderPass->setEnabled(is_able);
	ui.QLiedConctFolderPass->setEnabled(is_able);
	ui.QLiedLocalDriveName->setEnabled(is_able);
	ui.QLiedLogon_Password->setEnabled(is_able);
	ui.QLiedLogon_UserName->setEnabled(is_able);
	ui.QLiedRetryTime->setEnabled(is_able);
}

int NetworkDriveAutoConnect::UpdateData(bool flag)
{
	if(flag)// QLineEdit内の文字列を変数へ格納
	{
		// ネットワークドライブ名
		GetLocalDriveName(m_LocalDriverName, sizeof(m_LocalDriverName));

		// ネットワークドライブパス
		GetConctFolderPass(m_ConctFolderPass, sizeof(m_ConctFolderPass));

		// ユーザー名
		GetLogonUserName(m_LogonUserName, sizeof(m_LogonUserName));

		// パスワード
		GetLogonPassword(m_LogonPassword, sizeof(m_LogonPassword));

		// リトライ間隔
		m_retrydelay = ui.QLiedRetryTime->text().toInt();

		return EXIT_SUCCESS;
	}
	else// 変数の内容をQLineEdit内の文字列へ転送 使用するかは未定
	{
		QString str;

		// ネットワークドライブ名
		str = QString::fromWCharArray(m_LocalDriverName);
		ui.QLiedLocalDriveName->setText(str);
		
		// ネットワークドライブパス
		str = QString::fromWCharArray(m_ConctFolderPass);
		ui.QLiedConctFolderPass->setText(str);
		
		// ユーザー名
		str = QString::fromWCharArray(m_LogonUserName);
		ui.QLiedLogon_UserName->setText(str);
		
		// パスワード
		str = QString::fromWCharArray(m_LogonPassword);
		ui.QLiedLogon_Password->setText(str);
		
		// リトライ間隔
		str = LangSolver.GetString(networkdriveautoconnect_LS,LID_23)/*"%1"*/.arg(m_retrydelay);
		ui.QLiedRetryTime->setText(str);
	}

	return EXIT_FAILURE;
}


int NetworkDriveAutoConnect::WriteIniFile(wchar_t* filename, bool fullpass)
{
	UpdateData(true);

	TCHAR inipath[MAX_PATH], curpath[MAX_PATH];
	if(!fullpass){
		GetCurrentDirectory(MAX_PATH, curpath);
		wsprintf(inipath, L"%s\\%s", curpath, filename);
	}
	else{
		for(int i=0; i<wcslen(filename) && filename[i]!=NULL; i++){
			if(filename[i]=='/'){
				filename[i] = '\\';
			}
		}
		wsprintf(inipath, L"%s", filename);
	}

	// Iniバージョン
	WritePrivateProfileString(L"string", L"Version", m_IniVersionLatest, inipath);
	// 
	WritePrivateProfileString(L"string", L"LocalDriverName", m_LocalDriverName, inipath);
	WritePrivateProfileString(L"string", L"ConctFolderPass", m_ConctFolderPass, inipath);
	WritePrivateProfileString(L"string", L"Username", m_LogonUserName, inipath);
	WritePrivateProfileString(L"string", L"Password", m_LogonPassword, inipath);

	std::wstringstream str;

	str << m_retrydelay;

	WritePrivateProfileString(L"int", L"RetryTime", str.str().data(), inipath);

	return EXIT_SUCCESS;
}

int NetworkDriveAutoConnect::ReadIniFile(wchar_t* filename, bool fullpass)
{
	TCHAR inipath[MAX_PATH], curpath[MAX_PATH];
	if(!fullpass)
	{
		GetCurrentDirectory(MAX_PATH, curpath);
		wsprintf(inipath, L"%s\\%s", curpath, filename);
	}
	else
	{
		for(int i=0; i<wcslen(filename) && filename[i]!=NULL; i++){
			if(filename[i]=='/'){
				filename[i] = '\\';
			}
		}
		wsprintf(inipath, L"%s", filename);
	}
	GetPrivateProfileString(L"string", L"Version", L"0.1a", m_IniVersionReaded, sizeof(m_IniVersionReaded), inipath);
	GetPrivateProfileString(L"string", L"LocalDriverName", L"", m_LocalDriverName, sizeof(m_LocalDriverName) / sizeof(TCHAR), inipath);
	GetPrivateProfileString(L"string", L"ConctFolderPass", L"", m_ConctFolderPass, sizeof(m_ConctFolderPass) / sizeof(TCHAR), inipath);
	GetPrivateProfileString(L"string", L"Username", L"", m_LogonUserName, sizeof(m_LogonUserName), inipath);
	GetPrivateProfileString(L"string", L"Password", L"", m_LogonPassword, sizeof(m_LogonPassword), inipath);
	m_retrydelay = GetPrivateProfileInt(L"int", L"RetryTime", 1000, inipath);

	return EXIT_SUCCESS;
}

void NetworkDriveAutoConnect::closeEvent(QCloseEvent *event)
{
	//QMainWindow::closeEvent(event);
	if(TrayIcon->isVisible()==true){
		hide();
		event->ignore();
	}
}
void	NetworkDriveAutoConnect::SlotTimeOut()
{
	hide();
}