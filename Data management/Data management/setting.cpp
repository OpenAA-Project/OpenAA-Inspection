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

#include "setting.h"
#include "ui_setting.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "datamanagementResource.h"

QString MPath;
QStringList MPathList;
bool quit=false;
extern QFile *DBfile;

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	if(DBfile->open(QIODevice::ReadOnly)==true){
		QTextStream mystream(DBfile);
		QString myString;
		int ifire=1;
		while (mystream.atEnd()==0){
			myString=mystream.readLine();
			switch(ifire){
			case 1:
				ui->leHost->setText(myString);		//hostname
				break;
			case 2:
				ui->leFile->setText(myString);		//filename
				break;
			case 3:
				ui->leUser->setText(myString);		//username
				break;
			case 4:
				ui->lePassword->setText(myString);	//password
				break;
			case 5:
				ui->lePath->setText(myString);;		//path
				break;
			case 6:
				ui->lePort->setText(myString);		//portnumber
				break;
			}
			ifire++;
		}
		DBfile->close();
	}else{
		ui->lePath->setText(/**/"c:/Data");
		ui->leHost->setText(/**/"localhost");
		ui->lePort->setText(/**/"3051");
		ui->leFile->setText(/**/"c:/Data/OpenAA.fdb");
		ui->leUser->setText(/**/"sysdba");
		ui->lePassword->setText(/**/"masterkey");
	}	
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_okButton_clicked()
{
	GetData();
	close();
}

void Setting::on_cancelButton_clicked()
{
	quit=true;
	close();
}
void Setting::GetData()
{
	if(DBfile->open(QIODevice::WriteOnly )==true){
		MPath=ui->lePath->text();
		MPathList=MPath.split(/**/";");
		for(int i=0;i<MPathList.count();i++){
			if(MPathList[i].endsWith('/'))
				MPathList[i].remove(MPathList[i].count()-1,1);
		}
		ui->lePath->setText(MPathList.join(/**/";"));
		QTextStream mystream(DBfile);
		mystream<<ui->leHost->text()<<Qt::endl;
		mystream<<ui->leFile->text()<<Qt::endl;
		mystream<<ui->leUser->text()<<Qt::endl;
		mystream<<ui->lePassword->text()<<Qt::endl;
		mystream<<ui->lePath->text()<<Qt::endl;
		mystream<<ui->lePort->text()<<Qt::endl;
		DBfile->close();
	}else{
		QMessageBox::critical(0, LangSolver.GetString(setting_LS,LID_39)/*"Cannot open file"*/
			,LangSolver.GetString(setting_LS,LID_40)/*"Cannot open \\Regulus64v5\\save.dat\n"*/
			//,LangSolver.GetString(setting_LS,LID_41)/*"Click Cancel to exit."*/
			, QMessageBox::Cancel,
			QMessageBox::NoButton);
	}
}