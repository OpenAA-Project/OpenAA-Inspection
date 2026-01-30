/*
 * Copyright (C) 2024
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

#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "ShowLoadingDLLForm.h"
#include "ui_ShowLoadingDLLForm.h"
#include "XDataInLayer.h"

//#define	Mode_OutLoadingFile

ShowLoadingDLLForm::ShowLoadingDLLForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ShowLoadingDLLForm)
{
    ui->setupUi(this);
	LangLibSolver.SetUI(this);
	DLLLogFile	=/**/"LoadingDLL.log";

	setWindowFlags(Qt::WindowTitleHint);
	move(0,0);
	Tested=false;

#if defined(Mode_OutLoadingFile)

	QString	LogFileName=GetLayersBase()->GetUserPath()
						+GetSeparator()
						+DLLLogFile;
	QFile	File(LogFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream	TextFile(&File);
		TextFile<</**/"\r\n";
	}
#endif // defined(Mode_OutLoadingFile)
}

ShowLoadingDLLForm::~ShowLoadingDLLForm()
{
    delete ui;
}

void	ShowLoadingDLLForm::Add(const QString &FileName)
{
#if defined(Mode_OutLoadingFile)
	QString	LogFileName=GetLayersBase()->GetUserPath()
						+GetSeparator()
						+DLLLogFile;
	QFile	File(LogFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	TextFile(&File);
		TextFile<<QDateTime::currentDateTime().toString(/**/"yy/MM/dd-hh:mm:ss")
				+QString(/**/" ")
				+FileName
				+QString(/**/"\r\n");
	}
#endif // defined(Mode_OutLoadingFile)

	if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
		if(Tested==true){
			QListWidgetItem *r=ui->listWidget->item (0);
			r->setText(FileName);
		}
		else{
			ui->listWidget->insertItem(0,FileName);
		}
		ui->listWidget->update();
	}
	Tested=false;
}

void	ShowLoadingDLLForm::TestAdd(const QString &FileName)
{
#if defined(Mode_OutLoadingFile)
	QString	LogFileName=GetLayersBase()->GetUserPath()
						+GetSeparator()
						+DLLLogFile;
	QFile	File(LogFileName);
	if(File.open(QIODevice::Append)==true){
		QTextStream	TextFile(&File);
		TextFile<<QDateTime::currentDateTime().toString(/**/"yy/MM/dd-hh:mm:ss")
				+QString(/**/" ")
				+FileName
				+QString(/**/"\r\n");
	}
#endif // defined(Mode_OutLoadingFile)

	if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
		if(Tested==true){
			QListWidgetItem *r=ui->listWidget->item (0);
			r->setText(QString(/**/" ... ")+FileName);
		}
		else{
			ui->listWidget->insertItem(0,QString(" ... ")+FileName);
		}
		ui->listWidget->update();
	}
	Tested=true;
}