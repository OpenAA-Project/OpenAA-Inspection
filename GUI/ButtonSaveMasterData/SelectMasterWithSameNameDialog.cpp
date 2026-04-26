#include "SelectMasterWithSameNameDialog.h"
#include "ui_SelectMasterWithSameNameDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XDataInLayer.h"


SelectMasterWithSameNameDialog::SelectMasterWithSameNameDialog(IntList &_MasterCodes ,LayersBase *Base 
                                                                ,QWidget *parent)
    : QDialog(parent)
    , ServiceForLayers(Base)
    , ui(new Ui::SelectMasterWithSameNameDialog)
{
    ui->setupUi(this);
    MasterCodes=_MasterCodes;
	SelectedMasterCode=-1;

    ::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 25);
    ::SetColumnWidthInTable(ui->tableWidget ,2, 25);
    ::SetColumnWidthInTable(ui->tableWidget ,3, 25);

    ui->tableWidget->setRowCount(MasterCodes.GetCount());
    int Row=0;
    for(IntClass *v=MasterCodes.GetFirst();v!=NULL;v=v->GetNext(),Row++){
        int MasterCode=v->GetValue();
        ::SetDataToTable(ui->tableWidget,0, Row, QString::number(MasterCode));

		int32		MachineID;
		XDateTime	RegTime;
		QString		MasterName ,Remark;
		int32		Version;
		XDateTime	LastEditTime;
		int32		CategoryID;
		int16		MasterType;
		int32		LibFolderID;
		int32		ThresholdLevelID;
		int32		ThresholdLevelParentID;

	    bool    Ret=GetLayersBase()->GetDatabaseLoader()->G_SQLGetMasterInfo(
                                        GetLayersBase()->GetDatabase()
                                        ,MasterCode
										,MachineID
										,RegTime
										,MasterName ,Remark
										,Version
										,LastEditTime
										,CategoryID
										,MasterType
										,LibFolderID
										,ThresholdLevelID
										,ThresholdLevelParentID);
		if(Ret==true){
			::SetDataToTable(ui->tableWidget,1, Row,Remark);
			::SetDataToTable(ui->tableWidget,2, Row,RegTime		.toString("yy/MM/dd hh:mm:ss"));
			::SetDataToTable(ui->tableWidget,3, Row,LastEditTime.toString("yy/MM/dd hh:mm:ss"));
		}
	}
}

SelectMasterWithSameNameDialog::~SelectMasterWithSameNameDialog()
{
    delete ui;
}

void SelectMasterWithSameNameDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}


void SelectMasterWithSameNameDialog::on_pushButtonSelect_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	SelectedMasterCode=MasterCodes[Row];
	done(true);
}


void SelectMasterWithSameNameDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

