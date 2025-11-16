/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\FileRegistryEditor\FileRegistryEditor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FileRegistryEditor.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlDriver>
//#include <QIBaseDriver>
#include <QSqlQuery>
#include "XDatabase.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

FileRegistryEditor::FileRegistryEditor(LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base)
{
	ui.setupUi(this);

	PathName=QDir::currentPath();
	FRegistry=new FileRegistry(/**/"MachineInfo.dat");
	SetWidgetCenter(this);
	ShowInfo();
}

FileRegistryEditor::~FileRegistryEditor()
{

}


void FileRegistryEditor::on_pushButtonOK_clicked()
{
	int	MachineID=ui.spinBoxMachineID->value();
	FRegistry->Save(/**/"MachineID",MachineID);

	int	Language=ui.comboBoxLanguage->currentIndex();
	FRegistry->Save(/**/"Language",Language);

	bool	EditMaltipleMachine=ui.checkBoxEditMaltipleMachine->isChecked();
	FRegistry->Save(/**/"EditMaltipleMachine",EditMaltipleMachine);

	close();
}

void FileRegistryEditor::on_pushButtonCancel_clicked()
{
	close();
}

void	FileRegistryEditor::ShowInfo()
{
	ui.lineEditPathName->setText(PathName);

	int	MachineID=FRegistry->LoadRegInt(/**/"MachineID",0);
	ui.spinBoxMachineID->setValue(MachineID);

	int	Language=FRegistry->LoadRegInt(/**/"Language",0);
	ui.comboBoxLanguage->setCurrentIndex(Language);

	bool	EditMaltipleMachine=FRegistry->LoadRegBool(/**/"EditMaltipleMachine",0);
	ui.checkBoxEditMaltipleMachine->setChecked(EditMaltipleMachine);
}
void FileRegistryEditor::on_pushButtonSelectFolder_clicked()
{
	QString pathName=QFileDialog::getExistingDirectory ( 0, /**/"MachineInfo Directory");
	if(pathName.isEmpty()==false){
		delete	FRegistry;
		PathName=pathName;
		FRegistry=new FileRegistry(pathName+QString(/**/"/MachineInfo.dat"));
		ShowInfo();
	}
}

bool	FileRegistryEditor::SQLLoadMachine(void)
{
	QString	HostName=ui.lineEditHostName->text();
	QString	DBName	=ui.lineEditDatabaseName->text();
	int		PortNo	=ui.spinBoxDatabasePortNo->value();

	QString	Msg;
	GetLayersBase()->InitialDatabaseLoader(Msg);
	GetLayersBase()->CloseInformed();

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(GetLayersBase()->GetDatabaseLoader()
																	,DBName
																	,HostName
																	,PortNo
																	,/**/"",0);
	
	if(KDatabase->IsExistDatabase()==false){
		QMessageBox Q( /**/"Error"
					, "No database file", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return false;
	}
	if(GetLayersBase()->OpenDatabase(*KDatabase)==false){
		QMessageBox Q( /**/"Error"
					, "Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return false;
	}

	int	MachineID=ui.spinBoxMachineID->value();
	QString	S=QString(/**/"SELECT * FROM MACHINE where MACHINEID=")+QString::number(MachineID);
	QSqlQuery query(S,*GetLayersBase()->GetDataBase());
	if(query.next ()==false){
		ui.lineEditName->setText(/**/"");
		return false;
	}
	QString	Name=query.value(query.record().indexOf(/**/"NAME")).toString();
	ui.lineEditName->setText(Name);

	return true;
}

void FileRegistryEditor::on_pushButtonLoadDatabase_clicked()
{
	SQLLoadMachine();	
}
