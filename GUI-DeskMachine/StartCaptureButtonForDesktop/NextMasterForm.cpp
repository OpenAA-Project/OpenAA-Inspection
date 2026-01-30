/*
 * Copyright (C) 2023
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

#include "StartCaptureButtonForDesktopResource.h"

#include "NextMasterForm.h"
#include "XGeneralFunc.h"

NextMasterForm::NextMasterForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
//	setWindowFlags(Qt::WindowStaysOnTopHint);	//���ɑO�ʂɕ\��
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);

	ui.lbMasterCount		->setVisible(false);
	ui.lbMasterCountLabel	->setVisible(false);

	//���ʕ\�����̌����Ή�
	LangSolver.SetUI(this);
}

NextMasterForm::~NextMasterForm()
{
}

void NextMasterForm::SetLanguageCode(int LCode)
{
	LanguageCode=LCode;

	//�t�H���g�̐ݒ�
    QFont font1[5];
	//���{��
    font1[0].setPointSize(13);
    font1[0].setBold(true);
    font1[0].setWeight(75);
	//English
    font1[1].setPointSize(13);
    font1[1].setBold(true);
    font1[1].setWeight(75);
	//�ȑ̒���
    font1[2].setPointSize(13);
    font1[2].setBold(true);
    font1[2].setWeight(75);
	//�ɑ̒���
	font1[3].setPointSize(13);
    font1[3].setBold(true);
    font1[3].setWeight(75);
	//Korean
    font1[4].setPointSize(13);
    font1[4].setBold(true);
    font1[4].setWeight(75);

	QString strFont=/**/"";
	if(font1[LanguageCode].bold()==true){
		strFont	+=/**/"font-weight: bold;";
	}
	if(font1[LanguageCode].style()==QFont::StyleItalic){
		strFont	+=/**/"font-style: italic;";
	}
	else if(font1[LanguageCode].style()==QFont::StyleOblique){
		strFont	+=/**/"font-style: oblique;";
	}
	QString strFontStyleSheet;
	strFontStyleSheet=/**/"font-family: "
						+ font1[LanguageCode].family() + /**/";"
						+ /**/"font-size: "
						+ QString::number(font1[LanguageCode].pointSize()) + /**/"pt;"
						+ strFont;

	if(LanguageCode>0){
		ui.lbNext				->setStyleSheet(strFontStyleSheet);
		ui.lbNone				->setStyleSheet(strFontStyleSheet);
		ui.pushButtonFinish		->setStyleSheet(strFontStyleSheet);
		ui.pushButtonStartNext	->setStyleSheet(strFontStyleSheet);
	}
}

void NextMasterForm::SetNextMasterFlag(bool Flag)
{
	ui.lbNext->setVisible(Flag);
	ui.lbNone->setVisible(!Flag);
}

void NextMasterForm::SetMasterCounter(int Count,bool Enable)
{
	ui.lbMasterCount		->setText(QString::number(Count));
	ui.lbMasterCount		->setVisible(Enable);
	ui.lbMasterCountLabel	->setVisible(Enable);
}

void NextMasterForm::on_pushButtonFinish_clicked()
{
	accept();
}

void NextMasterForm::on_pushButtonStartNext_clicked()
{
	reject();
}