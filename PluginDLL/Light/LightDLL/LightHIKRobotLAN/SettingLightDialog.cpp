#include "SettingLightDialog.h"
#include "ui_SettingLightDialog.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QDir.h>
#include <QFile.h>
#include "XCriticalFunc.h"
#include "LightHIKRobotLAN.h"


SettingLightDialog::SettingLightDialog(LightHIKRobotLAN *p,QWidget *parent)
    : QDialog(parent)
    , Parent(p)
    , ui(new Ui::SettingLightDialog)
{
    ui->setupUi(this);

	ChannelCount = Parent->ChannelCount;
	ChannelNames = Parent->ChannelNames;
	LightDim = new LightSourceValue[ChannelCount];

	for(int s = 0;s<ChannelCount;s++){
		LightDim[s] = Parent->LightDim[s];
	}

	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 50);
	::SetColumnWidthInTable(ui->tableWidget ,2, 25);

	ui->tableWidget->setRowCount(ChannelCount);
	for(int row=0;row<ChannelCount;row++){
		::SetDataToTableCheckable(ui->tableWidget, 0, row, "", LightDim[row].ONMode);
		if(ChannelNames.count()>row){
			::SetDataToTable(ui->tableWidget, 1, row, ChannelNames[row], Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
		}
		else{
			::SetDataToTable(ui->tableWidget, 1, row, "", Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
		}
		QSpinBox	*s=::SetDataToTableSpinBox(ui->tableWidget,2,row, LightDim[row].Brightness,0,255);
		int MaxBrightness,MinBrightness;
		Parent->GetBrightnessRange(row+1,MaxBrightness,MinBrightness);
		s->setMinimum(MinBrightness);
		s->setMaximum(MaxBrightness);
	}
}

SettingLightDialog::~SettingLightDialog()
{
    delete ui;
}

void SettingLightDialog::on_pushButtonOK_clicked()
{
	for(int row=0;row<ChannelCount;row++){
		LightDim[row].ONMode=::GetCheckedFromTable(ui->tableWidget, 0, row);
		if(ChannelNames.count()>row){
			ChannelNames[row]=::GetDataToTable(ui->tableWidget, 1, row);
		}
		else{
			ChannelNames.append(::GetDataToTable(ui->tableWidget, 1, row));
		}
		LightDim[row].Brightness=::GetDataToTableSpinBox(ui->tableWidget, 2, row);
	}
	done(true);
}


void SettingLightDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

