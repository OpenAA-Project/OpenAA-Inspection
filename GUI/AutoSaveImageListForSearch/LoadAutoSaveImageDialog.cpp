#include "AutoSaveImageListForSearchResource.h"
#include "LoadAutoSaveImageDialog.h"
#include "ui_LoadAutoSaveImageDialog.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

LoadAutoSaveImageDialog::LoadAutoSaveImageDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::LoadAutoSaveImageDialog)
{
    ui->setupUi(this);
	Selected	=NULL;

	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Algo!=NULL){
		AutoSaveImageBase	*ABase=dynamic_cast<AutoSaveImageBase *>(Algo);
		ui->comboBoxSelectDrive->clear();
		CmdGetRootPathList	Cmd(GetLayersBase());
		ABase->TransmitDirectly(&Cmd);
		for(int i=0;i<Cmd.RootPaths.count();i++){
			ui->comboBoxSelectDrive->addItem(Cmd.RootPaths[i]);
		}
	}
	ui->tableWidgetFound->setColumnWidth(0,150);
	ui->tableWidgetFound->setColumnWidth(1,140);

	ui->dateTimeEditFrom	->setDateTime(ControlRememberer::GetDateTime(ui->dateTimeEditFrom));
	ui->dateTimeEditTo		->setDateTime(ControlRememberer::GetDateTime(ui->dateTimeEditTo));
	ui->checkBoxAllDrives	->setChecked (ControlRememberer::GetBool(ui->checkBoxAllDrives));

	InstallOperationLog(this);
}

LoadAutoSaveImageDialog::~LoadAutoSaveImageDialog()
{
    delete ui;
}

void LoadAutoSaveImageDialog::on_checkBoxAllDrives_clicked()
{
	if(ui->checkBoxAllDrives->isChecked()==true){
		ui->comboBoxSelectDrive->setEnabled(false);
	}
	else{
		ui->comboBoxSelectDrive->setEnabled(true);
	}
}

void	PickupFolderDateTime(QString &BaseFileName,QString &Folder,QString &DateStr,QString &TimeStr);

void LoadAutoSaveImageDialog::on_pushButtonStartSearch_clicked()
{
	QStringList	RootPaths;
	QDateTime	TimeFrom;
	QDateTime	TimeTo;
	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Algo!=NULL){
		AutoSaveImageBase	*ABase=dynamic_cast<AutoSaveImageBase *>(Algo);
		if(ui->checkBoxAllDrives->isChecked()==true){
			CmdGetRootPathList	Cmd(GetLayersBase());
			ABase->TransmitDirectly(&Cmd);
			RootPaths=Cmd.RootPaths;
		}
		else{
			RootPaths.append(ui->comboBoxSelectDrive->currentText());
		}
		TimeFrom=ui->dateTimeEditFrom->dateTime();
		TimeTo	=ui->dateTimeEditTo->dateTime();

		CmdSearchFileList	RCmd(GetLayersBase());
		RCmd.RootPaths	=RootPaths;
		RCmd.TimeFrom	=TimeFrom;
		RCmd.TimeTo		=TimeTo;
		ABase->TransmitDirectly(&RCmd);
		FoundFile	=RCmd.RetFile;
		int	Row=0;
		ui->tableWidgetFound->setRowCount(RCmd.RetFile.GetCount());
		for(BandImageFileList *L=RCmd.RetFile.GetFirst();L!=NULL;L=L->GetNext()){
			QString	Folder;
			QString	DateStr;
			QString	TimeStr;
			PickupFolderDateTime(L->BaseFileName,Folder,DateStr,TimeStr);
			::SetDataToTable(ui->tableWidgetFound,0,Row,Folder);
			::SetDataToTable(ui->tableWidgetFound,1,Row,DateStr+QString(/**/" ")+TimeStr);
			Row++;
		}
	}
}


void	PickupFolderDateTime(QString &BaseFileName,QString &Folder,QString &DateStr,QString &TimeStr)
{	
	QStringList	List=BaseFileName.split(QDir::separator());
	if(List.count()>=2){
		bool	ok;
		QString	BaseName=List[List.count()-1];
		int	FileMin=BaseName.mid(0,2).toInt(&ok);	if(ok==false)	return;
		int	FileSec=BaseName.mid(2,2).toInt(&ok);	if(ok==false)	return;
		QString	DateName=List[List.count()-2];
		int	year	=DateName.mid(0,2).toInt(&ok);	if(ok==false)	return;
		int	month	=DateName.mid(4,2).toInt(&ok);	if(ok==false)	return;
		int	day		=DateName.mid(6,2).toInt(&ok);	if(ok==false)	return;
		int	hour	=DateName.mid(9,2).toInt(&ok);	if(ok==false)	return;
		char	Buff[200];
		sprintf(Buff,/**/"%02d/%02d/%02d",year,month,day);
		DateStr=Buff;
		sprintf(Buff,/**/"%02d:%02d:%02d",hour,FileMin,FileSec);
		TimeStr=Buff;
		for(int i=0;i<List.count()-1;i++){
			Folder+=List[i]+QDir::separator();
		}
	}
}

void LoadAutoSaveImageDialog::on_tableWidgetFound_doubleClicked(const QModelIndex &index)
{
	on_pushButtonOK_clicked();
}

void LoadAutoSaveImageDialog::on_pushButtonOK_clicked()
{
	ControlRememberer::SetValue(ui->checkBoxAllDrives	,ui->checkBoxAllDrives->isChecked());
	ControlRememberer::SetValue(ui->dateTimeEditFrom	,ui->dateTimeEditFrom->dateTime());
	ControlRememberer::SetValue(ui->dateTimeEditTo		,ui->dateTimeEditTo  ->dateTime());

	int	Row=ui->tableWidgetFound->currentRow();
	if(Row<0)
		return;
	Selected=FoundFile[Row];
	if(Selected!=NULL){
		done(true);
	}
}

void LoadAutoSaveImageDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

