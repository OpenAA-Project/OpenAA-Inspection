#include "SettingLoadReleaseDialog.h"
#include "ui_SettingLoadReleaseDialog.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

SettingLoadReleaseDialog::SettingLoadReleaseDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SettingLoadReleaseDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,32);
	ui->tableWidget->setColumnWidth(1,200);

	int	N=GetLayersBase()->GetLogicDLLBase()->GetCount();
	ui->tableWidget->setRowCount(N);
	SettingData.RemoveAll();
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		::SetDataToTableCheckable(ui->tableWidget,0,row ,/**/"",false);
		QString	s=d->GetDLLRoot()
				+ ::GetSeparator()
				+ d->GetDLLName();
		::SetDataToTable		 (ui->tableWidget,1,row ,s);

		LoadReleaseAlgoList	*k=new LoadReleaseAlgoList();
		k->DLLRoot	=d->GetDLLRoot();
		k->DLLName	=d->GetDLLName();
		SettingData.AppendList(k);
		row++;
	}

	InstallOperationLog(this);
}

SettingLoadReleaseDialog::~SettingLoadReleaseDialog()
{
    delete ui;
}

void SettingLoadReleaseDialog::Merge(LoadReleaseAlgoContainer &SrcSettingData)
{
	SettingData.ReleaseableMasterBuff	=SrcSettingData.ReleaseableMasterBuff;
	SettingData.ReleaseableTargetBuff	=SrcSettingData.ReleaseableTargetBuff;

	for(LoadReleaseAlgoList *a=SrcSettingData.GetFirst();a!=NULL;a=a->GetNext()){
		for(LoadReleaseAlgoList *b=SettingData.GetFirst();b!=NULL;b=b->GetNext()){
			if(a->DLLRoot==b->DLLRoot && a->DLLName==b->DLLName){
				b->Releaseable=a->Releaseable;
				break;
			}
		}
	}
}
void SettingLoadReleaseDialog::ReflectToWindow(void)
{
	ui->checkBoxMasterBuff	->setChecked(SettingData.ReleaseableMasterBuff);
	ui->checkBoxTargetBuff	->setChecked(SettingData.ReleaseableTargetBuff);
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		LoadReleaseAlgoList *b=SettingData[row];
		::SetDataToTableCheckable(ui->tableWidget,0,row ,/**/"",b->Releaseable);
		row++;
	}
}

void SettingLoadReleaseDialog::on_pushButtonOK_clicked()
{
	SettingData.ReleaseableMasterBuff	=ui->checkBoxMasterBuff	->isChecked();
	SettingData.ReleaseableTargetBuff	=ui->checkBoxTargetBuff	->isChecked();
	int	row=0;
	for(LogicDLL *d=GetLayersBase()->GetLogicDLLBase()->GetFirst();d!=NULL;d=d->GetNext()){
		LoadReleaseAlgoList *b=SettingData[row];
		b->Releaseable	=	GetCheckedFromTable(ui->tableWidget,0,row);
		row++;
	}
	done(true);
}
