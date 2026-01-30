/*
 * Copyright (C) 2021
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

#include "LogIntegratorSettingDialog.h"
#include <QDir>
#include <QMessageBox>

LogIntegratorSettingDialog::LogIntegratorSettingDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect( ui.lineEdit_UpperLogHD, SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );
	connect( ui.lineEdit_LowerLogHD, SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );
	connect( ui.lineEdit_OutputDir,  SIGNAL(returnPressed()), this, SLOT(on_pushButton_OK_clicked()) );

}

LogIntegratorSettingDialog::~LogIntegratorSettingDialog()
{

}

QString LogIntegratorSettingDialog::SelectDirectory( QFileDialog::AcceptMode acceptmode, QString DefaultDir="" )
{
	QFileDialog Dialog(this, Qt::Dialog);
	if( !DefaultDir.isEmpty() )
		Dialog.setDirectory(DefaultDir);
	Dialog.setFileMode(QFileDialog::DirectoryOnly);
	Dialog.setAcceptMode(acceptmode);
	if( Dialog.exec()==QDialog::Accepted )
		return Dialog.selectedFiles().takeFirst();
	else
		return "";
}

void LogIntegratorSettingDialog::on_pushButton_SelectUpperLogHD_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("上面ログのあるHDを指定してください"),
                                                 ui.lineEdit_UpperLogHD->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_UpperLogHD->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_SelectLowerLogHD_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("下面ログのあるHDを指定してください"),
                                                 ui.lineEdit_LowerLogHD->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_LowerLogHD->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_SelectOutputDir_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, QString("統合したログの出力先フォルダを指定してください"),
                                                 ui.lineEdit_OutputDir->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 );
	if( dir.isNull() )
		return;
	ui.lineEdit_OutputDir->setText( QDir::toNativeSeparators(dir) );
}

void LogIntegratorSettingDialog::on_pushButton_OK_clicked()
{
	accept();
}

void LogIntegratorSettingDialog::on_pushButton_Cancel_clicked()
{
	reject();
}