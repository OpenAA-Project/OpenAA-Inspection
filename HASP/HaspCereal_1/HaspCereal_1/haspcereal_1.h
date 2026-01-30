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

#ifndef HASPCEREAL_1_H
#define HASPCEREAL_1_H

#include <QWidget>
#include <QFileDialog>
#include <QDomNode>
#include  <QMessageBox>
#include  <QTranslator>
#include "ui_haspcereal_1.h"
//#include "hasp_hl.h"
#include "hasp_api.h"

class HaspCereal_1 : public QMainWindow
{
    Q_OBJECT

public:
    HaspCereal_1(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~HaspCereal_1();
	
private:
    Ui::HaspCereal_1Class ui;
	hasp_handle_t   handle;
	QByteArray HaspInfo;	//YES_clicked:Session()��GetHaspID()
	int HaspID;				//YES_clicked:GetHaspID()��Encrypt()
	QByteArray CerealID;	//YES_clicked:Encrypt()��SaveData()
	QString File;			//YES_clicked:SaveFile()��SaveData()
private slots:
	bool HaspLogin(hasp_handle_t &handle);										//HaspLogint
	bool Session(hasp_handle_t handle, QByteArray &info);						//HASP���ŗL�f�[�^�̎擾
	void GetHaspID(QByteArray haspInfo,int &haspID);							//HASP���ŗL�f�[�^�̒������V���A���R�[�h�̎擾
	bool Encrypt(hasp_handle_t handle, int cerealNo, QByteArray &cerealData);	//�V���A���̈Í���
	bool SaveFile(QString &sfile);												//�ۑ������t�@�C�����̎擾
	bool SaveData(QString fileName, QByteArray cerealCode);	 					//�t�@�C���Ƀf�[�^�̕ۑ�
	void on_pbYES_clicked();
	void on_pbNO_clicked();
};

#endif // HASPCEREAL_1_H
