#ifndef NETWORKDRIVEAUTOCONNECT_H
#define NETWORKDRIVEAUTOCONNECT_H

//
//		NetworkDriveAutoConnect header
//
//		Version 0.1c
//			ネットワークドライブへのダミーアクセスによる接続維持機能を実装
//
//		Version 0.1b
//			* LanguageSolverによる英語化に対応
//			初期読み込みIniファイル名を AutoConnectInfomation.ini に変更
//			作成したIniファイルにバージョンを記述するようにした
//
//		Version 0.1a
//			初期完成バージョン
//


#include <QMainWindow>
#include "ui_networkdriveautoconnect.h"

#include <QTimeLine>
#include <windows.h>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>

class NetworkDriveAutoConnect : public QMainWindow
{
	Q_OBJECT

public:
	NetworkDriveAutoConnect(QWidget *parent = 0, const QString &iniFilename =QString(), bool loop=false, DWORD loopTime=60000, Qt::WindowFlags flags = Qt::Widget);
	~NetworkDriveAutoConnect();

private:
	Ui::NetworkDriveAutoConnectClass ui;

private:
	NETRESOURCE m_nr;
	wchar_t m_LocalDriverName[MAX_PATH];
	wchar_t m_ConctFolderPass[MAX_PATH];
	wchar_t m_LogonUserName[MAX_PATH];
	wchar_t m_LogonPassword[MAX_PATH];
	DWORD m_retrydelay;

	bool m_IsAutoConnectStarted;// 自動接続を開始しているか

	QTimeLine QTimeAutoConnect;

	bool m_LoopEnable;
	bool m_isConnected;
	DWORD m_LoopTime;

	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	QTimer				TM;
	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*quitAction;
public:
	void setLoopEnable(bool enable);

private:// iniファイル関係
	wchar_t m_IniVersionReaded[MAX_PATH];
	wchar_t m_IniVersionLatest[MAX_PATH];
	wchar_t m_IniFilename[MAX_PATH];

private:
	// true:コントロール→変数, false:変数→コントロール
	int UpdateData(bool flag=true);

	// コントロールの内容をwhcar_t型の変数へ格納
	int GetLocalDriveName(wchar_t* buffer, size_t len);
	int GetConctFolderPass(wchar_t* buffer, size_t len);
	int GetLogonUserName(wchar_t* buffer, size_t len);
	int GetLogonPassword(wchar_t* buffer, size_t len);

	// QLineEditへの書き込み許可変更
	void ChangeQLineEditEnable(bool is_able);

	// 初期化ファイルの保存と読み込み
	int WriteIniFile(wchar_t* filename, bool fullpass=false);
	int ReadIniFile(wchar_t* filename, bool fullpass=false);

	// WNetAddConnection2 エラー関係
	int GetWNetAddConnection2ErrorString(DWORD errid, QString* buffer);
	int IsWNetAdded(DWORD errid);

private:
	void accessDrive(const QString &path);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void on_QBtnConnectStart_clicked();
	void on_QBtnConnectNow_clicked();
	void on_QBtnSaveDefault_clicked();
	void on_QBtnExitButton_clicked();
	void TryAutoConnection();
	void	SlotTimeOut();
};


#endif // NETWORKDRIVEAUTOCONNECT_H
