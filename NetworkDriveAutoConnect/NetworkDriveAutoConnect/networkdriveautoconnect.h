/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef NETWORKDRIVEAUTOCONNECT_H
#define NETWORKDRIVEAUTOCONNECT_H

//
//		NetworkDriveAutoConnect header
//
//		Version 0.1c
//			�l�b�g���[�N�h���C�u�ւ̃_�~�[�A�N�Z�X�ɂ����ڑ��ێ��@�\������
//
//		Version 0.1b
//			* LanguageSolver�ɂ����p�ꉻ�ɑΉ�
//			�����ǂݍ���Ini�t�@�C������ AutoConnectInfomation.ini �ɕύX
//			�쐬����Ini�t�@�C���Ƀo�[�W�������L�q�����悤�ɂ���
//
//		Version 0.1a
//			���������o�[�W����
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

	bool m_IsAutoConnectStarted;// �����ڑ����J�n���Ă��邩

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

private:// ini�t�@�C���֌W
	wchar_t m_IniVersionReaded[MAX_PATH];
	wchar_t m_IniVersionLatest[MAX_PATH];
	wchar_t m_IniFilename[MAX_PATH];

private:
	// true:�R���g���[�����ϐ�, false:�ϐ����R���g���[��
	int UpdateData(bool flag=true);

	// �R���g���[���̓��e��whcar_t�^�̕ϐ��֊i�[
	int GetLocalDriveName(wchar_t* buffer, size_t len);
	int GetConctFolderPass(wchar_t* buffer, size_t len);
	int GetLogonUserName(wchar_t* buffer, size_t len);
	int GetLogonPassword(wchar_t* buffer, size_t len);

	// QLineEdit�ւ̏������݋��ύX
	void ChangeQLineEditEnable(bool is_able);

	// �������t�@�C���̕ۑ��Ɠǂݍ���
	int WriteIniFile(wchar_t* filename, bool fullpass=false);
	int ReadIniFile(wchar_t* filename, bool fullpass=false);

	// WNetAddConnection2 �G���[�֌W
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