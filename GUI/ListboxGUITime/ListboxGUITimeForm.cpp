#include "ListboxGUITimeResource.h"
#include "ListboxGUITimeForm.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

ListboxGUITimeForm::ListboxGUITimeForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ListboxGUITimeForm::~ListboxGUITimeForm()
{

}

void	ListboxGUITimeForm::resizeEvent ( QResizeEvent * )
{
	ui.tableWidget->resize(width()-2,height()-ui.frame->height());
	ui.frame->move(0,height()-ui.frame->height());
}


void ListboxGUITimeForm::on_pushButtonUpdate_clicked()
{
	GUIInstancePack		*P=GetLayersBase()->GetEntryPoint()->GetGUIInstancePack();
	int	RowCount=P->NPListPack<GUIItemInstance>::GetCount();
	ui.tableWidget->setRowCount(RowCount);
	int	row=0;
	DWORD	TotalTime=0;
	for(GUIItemInstance *g=P->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
		if(g->DLLAccess!=NULL){
			SetDataToTable(ui.tableWidget ,0,row ,g->GetForm()->GetDLLRoot());
			SetDataToTable(ui.tableWidget ,1,row ,g->GetForm()->GetDLLName());
		}
		else{
			SetDataToTable(ui.tableWidget ,0,row ,/**/"");
			SetDataToTable(ui.tableWidget ,1,row ,/**/"");
		}
		SetDataToTable(ui.tableWidget ,2,row ,g->Handle->GetName());
		SetDataToTable(ui.tableWidget ,3,row ,QString::number(g->Handle->GetShowingMilisec()));
		SetDataToTable(ui.tableWidget ,4,row ,QString::number(g->Handle->GetRunningMilisec()));
		SetDataToTable(ui.tableWidget ,5,row ,QString::number(g->Handle->GetScanningMilisec()));
		TotalTime+=g->Handle->GetShowingMilisec();
		row++;
	}
	ui.lineEdit->setText(QString::number(TotalTime));
}