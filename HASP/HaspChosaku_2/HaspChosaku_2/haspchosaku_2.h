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

#ifndef HASPCHOSAKU_2_H
#define HASPCHOSAKU_2_H

#include <QMainWindow>
#include <QFileDialog>
#include  <QMessageBox>
#include "ui_haspchosaku_2.h"
//#include "hasp_hl.h"
#include "hasp_api.h"
#include  <QDateTimeEdit>
#include <QTranslator>
#include <QTextStream>
class HaspChosaku_2 : public QMainWindow
{
    Q_OBJECT

public:
    HaspChosaku_2(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspChosaku_2();
private:
    Ui::HaspChosaku_2Class ui;
	hasp_handle_t Handle;			//pbOK_clicked:HaspLogin()��Decrypt(),Encrypt()
	QString FileName;				//pbOK_clicked:FileOpen()��FileLoad()
	QByteArray CerealData;			//pbOK_clicked:FileLoad()��Decrypt()
	QByteArray DeCereal;			//pbOK_clicked:Decrypt()��Encrypt()
	QByteArray HaspData;			//pbOK_clicked:Encrypt()��SaveData()
	QString File;					//pbOK_clicked:SaveFile()��SaveData()
private slots:
	bool HaspLogin(hasp_handle_t &handle);						//HaspLogint
	bool FileOpen(QString &sfile);								//�J���t�@�C�����̎擾
	bool FileLoad(QString fileName, QByteArray &cerealData);	//�t�@�C�������f�[�^�̏o��
	bool Decrypt(hasp_handle_t handle, QByteArray cereal, QByteArray &deCereal); //�f�[�^�̕�����
	bool Encrypt(hasp_handle_t handle, QByteArray cerealcode, QString copyright, QString date, QByteArray &haspData);//�f�[�^�̈Í���
	bool SaveFile(QString &sfile);								//�ۑ������t�@�C�����̎擾
	bool SaveData(QString fileName, QByteArray HaspCode);		//�t�@�C���Ƀf�[�^�̕ۑ�
	void on_pbOK_clicked();
	void on_pbEND_clicked();
};

#endif // HASPCHOSAKU_2_H