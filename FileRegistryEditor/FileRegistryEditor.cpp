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
#include "XOpenAA.h"

FileRegistryEditor::FileRegistryEditor(LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base)
{
	ui.setupUi(this);

	PathName=QDir::currentPath();
	FRegistry=GetLayersBase()->GetFRegistry();
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
		FRegistry=new FileRegistry(pathName+QDir::separator()+DefaultMachineInfoFileName);
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