#include "AutoStartParamList.h"
#include "AutoStartEachParam.h"
#include "XAutoStart.h"
#include "XGeneralFunc.h"
#include <QFileInfo>

AutoStartParamList::AutoStartParamList(AutoStartExeList &List ,QWidget *parent)
	: QDialog(parent),TmpData(List)
{
	ui.setupUi(this);

	ui.tableWidget	->setColumnWidth(0,250);
	ui.tableWidget	->setColumnWidth(1,200);
	ui.tableWidget	->setColumnWidth(2,300);
	ui.tableWidget	->setColumnWidth(3,80);

	ShowList();

	ui.checkBoxAllDesktopArea	->setChecked(TmpData.AllDesktopArea);
	ui.spinBoxAreaLeft			->setValue(TmpData.AreaLeft);
	ui.spinBoxAreaTop			->setValue(TmpData.AreaTop);
	ui.spinBoxAreaRight			->setValue(TmpData.AreaRight);
	ui.spinBoxAreaBottom		->setValue(TmpData.AreaBottom);
	ui.checkBoxTasktray			->setChecked(TmpData.Tasktray);
}

AutoStartParamList::~AutoStartParamList()
{

}

void	AutoStartParamList::ShowList(void)
{
	ui.spinBoxLoopCount->setValue(TmpData.LoopCount);

	ui.tableWidget->setRowCount(TmpData.GetCount());
	int Row=0;
	for(AutoStartExecution *a=TmpData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		QFileInfo	Info(a->ExeFilePath);
		::SetDataToTable(ui.tableWidget ,0,Row ,Info.absolutePath());
		::SetDataToTable(ui.tableWidget ,1,Row ,Info.fileName());
		::SetDataToTable(ui.tableWidget ,2,Row ,a->Parameter);
		QString	LocStr;
		switch(a->Location){
			case 0:	LocStr=/**/"Single";		break;
			case 1:	LocStr=/**/"Left";			break;
			case 2:	LocStr=/**/"Right";			break;
			case 3:	LocStr=/**/"Top";			break;
			case 4:	LocStr=/**/"Bottom";		break;
			case 5:	LocStr=/**/"Client";		break;
			case 6:	LocStr=/**/"LeftClient";	break;
			case 7:	LocStr=/**/"RightClient";	break;
			case 8:	LocStr=/**/"TopClient";		break;
			case 9:	LocStr=/**/"BottomClient";	break;
		}
		::SetDataToTable(ui.tableWidget ,3,Row ,LocStr);
	}
}

void AutoStartParamList::on_pushButtonOK_clicked()
{
	TmpData.LoopCount		=ui.spinBoxLoopCount->value();
	TmpData.AllDesktopArea	=ui.checkBoxAllDesktopArea	->isChecked();
	TmpData.AreaLeft		=ui.spinBoxAreaLeft			->value();
	TmpData.AreaTop			=ui.spinBoxAreaTop			->value();
	TmpData.AreaRight		=ui.spinBoxAreaRight		->value();
	TmpData.AreaBottom		=ui.spinBoxAreaBottom		->value();
	TmpData.Tasktray		=ui.checkBoxTasktray		->isChecked();

	done(true);
}



void AutoStartParamList::on_pushButtonAdd_clicked()
{
	AutoStartEachParam	D(/**/"",/**/"",/**/"",0,1000);
	if(D.exec()==(int)true){
		AutoStartExecution	*e=new AutoStartExecution();
		e->ExeFilePath		=D.ExeFilePath;
		e->Parameter		=D.Parameters;
		e->WorkingPath		=D.WorkingPath;
		e->Location			=D.Location;
		e->BootingWaitTime	=D.BootingWaitTime;
		TmpData.AppendList(e);
		ShowList();
	}
}

void AutoStartParamList::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	R=ui.tableWidget->currentRow();
	AutoStartExecution	*e=TmpData.GetItem(R);
	if(e!=NULL){
		AutoStartEachParam	D(e->ExeFilePath,e->Parameter,e->WorkingPath,e->Location,e->BootingWaitTime);
		if(D.exec()==(int)true){
			e->ExeFilePath		=D.ExeFilePath;
			e->Parameter		=D.Parameters;
			e->WorkingPath		=D.WorkingPath;
			e->Location			=D.Location;
			e->BootingWaitTime	=D.BootingWaitTime;
			ShowList();
		}
	}
}
