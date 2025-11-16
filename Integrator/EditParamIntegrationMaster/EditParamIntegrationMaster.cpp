#include "EditParamIntegrationMaster.h"
#include "XParamIntegrationMaster.h"
#include "XDataInLayer.h"
#include <QFile>
#include <QFileDialog>
#include "XDatabase.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "swap.h"

EditParamIntegrationMaster::EditParamIntegrationMaster(LayersBase *base,ParamIntegrationMaster *param,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base),Param(param)
{
	ui.setupUi(this);

	WTab = new WEditParameterTab(Param ,-1,ui.frameGlobalParam);

	GlobalParamLoadedFileName=Param->GetDefaultFileName();
	ui.lineEditFileName->setText(GlobalParamLoadedFileName);
	QFile	F(GlobalParamLoadedFileName);
	if(F.open(QIODevice::ReadOnly)==true){
		if(WTab->Load(&F)==true){
			WTab->ShowToWindow();
		}
	}
	ui.tableWidgetImageFolders->setColumnWidth(0,ui.tableWidgetImageFolders->width()-50);

	ShowSlaveList();
	LastRowInSlave=-1;
}

EditParamIntegrationMaster::~EditParamIntegrationMaster()
{
	delete	WTab;
}

void EditParamIntegrationMaster::on_SaveButton_clicked()
{
	QString	 fileName=GetLayersBase()->LGetSaveFileName (NULL
														, WTab->GetDataText()
														, QString()
														, QString(/**/"dat(*.dat);;AllFile(*.*)"));
	if(fileName.isEmpty()==false){
		QFile	F(fileName);
		if(F.open(QIODevice::WriteOnly)==true){
			GetIntegrationSlave(LastRowInSlave);
			WTab->LoadFromWindow();
			WTab->Save(&F);
		}
	}

}

void EditParamIntegrationMaster::on_UpdateDefaultButton_clicked()
{
	//QString	FileName=WTab->GetParamBase()->GetSavedFileName();
	//QFile	F(FileName);
	GetIntegrationSlave(LastRowInSlave);

	QFile	F(GlobalParamLoadedFileName);
	if(F.open(QIODevice::WriteOnly)==true){
		WTab->LoadFromWindow();
		WTab->Save(&F);
	}
}

void EditParamIntegrationMaster::on_LoadButton_clicked()
{
	QString	 fileName=GetLayersBase()->LGetOpenFileName(NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
	if(fileName.isEmpty()==false){
		GlobalParamLoadedFileName=fileName;
		ui.lineEditFileName->setText(GlobalParamLoadedFileName);
		QFile	F(fileName);
		if(F.open(QIODevice::ReadOnly)==true){
			WTab->Load(&F);
			WTab->ShowToWindow();
		}
	}
}

void EditParamIntegrationMaster::on_CancelButton_clicked()
{
	close();
}

void EditParamIntegrationMaster::on_listWidgetSlaveList_clicked(const QModelIndex &index)
{
	int	Row=ui.listWidgetSlaveList	->currentRow();
	if(LastRowInSlave>=0){
		GetIntegrationSlave(LastRowInSlave);
	}
	ShowIntegrationSlave(Row);
	LastRowInSlave=Row;
}

void	EditParamIntegrationMaster::ShowSlaveList(void)
{
	QStringList	SlaveNames;
	int	Row=0;
	for(IntegrationSlave *s=Param->Slaves.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		SlaveNames.append(QString("Slave-")+QString::number(Row));
	}
	ui.listWidgetSlaveList	->clear();
	ui.listWidgetSlaveList	->addItems(SlaveNames);
}

void	EditParamIntegrationMaster::ShowIntegrationSlave(int Row)
{
	IntegrationSlave *s=Param->Slaves[Row];
	if(s!=NULL){
		ui.spinBoxMachineCode		->setValue(s->MachineCode);
		ui.checkBoxDependent		->setChecked(s->Dependent);
		ui.checkBoxSlaveIsInMaster	->setChecked(s->SlaveIsInMaster);
		ui.lineEditSlaveAddress		->setText(s->SlaveAddress);
		ui.lineEditSharedFolder		->setText(s->SharedFolder);;

		ui.tableWidgetImageFolders	->setRowCount(s->ImageFolders.count());
		for(int row=0;row<s->ImageFolders.count();row++){
			::SetDataToTable(ui.tableWidgetImageFolders ,0,row ,s->ImageFolders[row] ,Qt::ItemIsEditable);
		}
		ui.spinBoxMinAdditionalSec	->setValue(s->MinAdditionalSec);
		ui.spinBoxMaxAdditionalSec	->setValue(s->MaxAdditionalSec);
		ui.spinBoxOffsetXForSync	->setValue(s->OffsetXForSync);
		ui.spinBoxOffsetYForSync	->setValue(s->OffsetYForSync);
	}
}
void	EditParamIntegrationMaster::GetIntegrationSlave(int Row)
{
	if(Row>=0){
		IntegrationSlave *s;
		while((s=Param->Slaves[Row])==NULL){
			s=new IntegrationSlave	();
			Param->Slaves.AppendList(s);
		}
		s->MachineCode		=ui.spinBoxMachineCode		->value();
		s->Dependent		=ui.checkBoxDependent		->isChecked();
		s->SlaveIsInMaster	=ui.checkBoxSlaveIsInMaster	->isChecked();
		s->SlaveAddress		=ui.lineEditSlaveAddress	->text();
		s->SharedFolder		=ui.lineEditSharedFolder	->text();

		s->ImageFolders.clear();
		int	N=ui.tableWidgetImageFolders->rowCount();
		for(int row=0;row<N;row++){
			QString	Str=GetDataToTable(ui.tableWidgetImageFolders ,0 ,row);
			s->ImageFolders.append(Str);
		}

		s->MinAdditionalSec	=ui.spinBoxMinAdditionalSec	->value();
		s->MaxAdditionalSec	=ui.spinBoxMaxAdditionalSec	->value();
		s->OffsetXForSync	=ui.spinBoxOffsetXForSync	->value();
		s->OffsetYForSync	=ui.spinBoxOffsetYForSync	->value();

	}
}
void	EditParamIntegrationMaster::ClearIntegrationSlave(void)
{
	ui.spinBoxMachineCode		->setValue(0);
	ui.checkBoxDependent		->setChecked(false);
	ui.checkBoxSlaveIsInMaster	->setChecked(false);
	ui.lineEditSlaveAddress		->setText(/**/"");
	ui.lineEditSharedFolder		->setText(/**/"");
	ui.tableWidgetImageFolders	->setRowCount(0);
	ui.spinBoxMinAdditionalSec	->setValue(0);
	ui.spinBoxMaxAdditionalSec	->setValue(0);
	ui.spinBoxOffsetXForSync	->setValue(0);
	ui.spinBoxOffsetYForSync	->setValue(0);
}

void EditParamIntegrationMaster::on_pushButtonSlaveListPlus_clicked()
{
	Param->Slaves.AppendList(new IntegrationSlave());
	QStringList	SlaveNames;
	int	Row=0;
	for(IntegrationSlave *s=Param->Slaves.GetFirst();s!=NULL;s=s->GetNext(),Row++){
		SlaveNames.append(QString("Slave-")+QString::number(Row));
	}
	ui.listWidgetSlaveList	->clear();
	ui.listWidgetSlaveList	->addItems(SlaveNames);
}

void EditParamIntegrationMaster::on_pushButtonSlaveListMinus_clicked()
{
	int	Row=ui.listWidgetSlaveList	->currentRow();
	IntegrationSlave *s=Param->Slaves[Row];
	if(s!=NULL){
		Param->Slaves.RemoveList(s);
		delete	s;
	}
	ShowSlaveList();

	if(Param->Slaves.GetCount()<Row){
		ui.listWidgetSlaveList	->setCurrentRow(Row);
		LastRowInSlave=Row;
	}
	else if(Param->Slaves.GetCount()>0){
		Row=Param->Slaves.GetCount()-1;
		if(Row>=0){
			ui.listWidgetSlaveList	->setCurrentRow(Row);
			ShowIntegrationSlave(Row);
			LastRowInSlave=Row;
		}
	}
	else{
		ClearIntegrationSlave();
	}
}

void EditParamIntegrationMaster::on_pushButtonShooseSharedFolder_clicked()
{
	QString	Folder=QFileDialog::getExistingDirectory(NULL,"Shared folder");
	if(Folder.isEmpty()==false){
		ui.lineEditSharedFolder		->setText(Folder);
	}
}

void EditParamIntegrationMaster::on_pushButtonImagePathPlus_clicked()
{
	int	N=ui.tableWidgetImageFolders->rowCount();
	ui.tableWidgetImageFolders	->setRowCount(N+1);

	::SetDataToTable(ui.tableWidgetImageFolders ,0,N ,/**/"",Qt::ItemIsEditable);
}

void EditParamIntegrationMaster::on_pushButtonImagePathMinus_clicked()
{
	int	Row=ui.tableWidgetImageFolders	->currentRow();
	ui.tableWidgetImageFolders	->removeRow(Row);
}
