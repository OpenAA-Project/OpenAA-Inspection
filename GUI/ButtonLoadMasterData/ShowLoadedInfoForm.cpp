#include "ButtonLoadMasterDataResource.h"
#include "ShowLoadedInfoForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDataComponent.h"
#include "XMasterData.h"

class LoadedInfoList;

ShowLoadedInfoForm::ShowLoadedInfoForm(LayersBase *Base ,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	GetLayersBase()->CenterizeDialog(this);
	//setAttribute();
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	
	ui.tableWidget->setColumnWidth(0,100);
	ui.tableWidget->setColumnWidth(1,140);
	ui.tableWidget->setColumnWidth(2,45);
	ui.tableWidget->setColumnWidth(3,45);
	ui.tableWidget->setColumnWidth(4,90);
	ShowList();
	setWindowTitle(GetLayersBase()->GetMainWidget()->windowTitle());
	InstallOperationLog(this);
}

ShowLoadedInfoForm::~ShowLoadedInfoForm()
{

}

struct	LoadedInfoListStruct
{
	LoadedInfoList	*Pointer;
	int				Page;
	int				Phase;
};

static	int	FuncSortByPage(const void *a ,const void *b)
{
	struct	LoadedInfoListStruct	*pa=(struct	LoadedInfoListStruct *)a;
	struct	LoadedInfoListStruct	*pb=(struct	LoadedInfoListStruct *)b;
	if(pa->Page<pb->Page)
		return -1;
	if(pa->Page>pb->Page)
		return 1;

	if(pa->Pointer->AlgoRoot<pb->Pointer->AlgoRoot)
		return -1;
	if(pa->Pointer->AlgoRoot>pb->Pointer->AlgoRoot)
		return 1;
	if(pa->Pointer->AlgoName<pb->Pointer->AlgoName)
		return -1;
	if(pa->Pointer->AlgoName>pb->Pointer->AlgoName)
		return 1;

	if(pa->Phase<pb->Phase)
		return -1;
	if(pa->Phase>pb->Phase)
		return 1;
	return 0;
}

static	int	FuncSortByName(const void *a ,const void *b)
{
	struct	LoadedInfoListStruct	*pa=(struct	LoadedInfoListStruct *)a;
	struct	LoadedInfoListStruct	*pb=(struct	LoadedInfoListStruct *)b;

	if(pa->Pointer->AlgoRoot<pb->Pointer->AlgoRoot)
		return -1;
	if(pa->Pointer->AlgoRoot>pb->Pointer->AlgoRoot)
		return 1;
	if(pa->Pointer->AlgoName<pb->Pointer->AlgoName)
		return -1;
	if(pa->Pointer->AlgoName>pb->Pointer->AlgoName)
		return 1;

	if(pa->Page<pb->Page)
		return -1;
	if(pa->Page>pb->Page)
		return 1;

	if(pa->Phase<pb->Phase)
		return -1;
	if(pa->Phase>pb->Phase)
		return 1;
	return 0;
}
void	ShowLoadedInfoForm::ShowList(void)
{
	int	RowCount=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *Pg=Ph->GetPageData(page);
			if(Pg!=NULL){
				LoadedInfoContainerInPhase	&LC=Pg->GetResultLoaded();
				RowCount+=LC.GetCount();
			}
		}
	}
	struct LoadedInfoListStruct *IndexPointer=new struct LoadedInfoListStruct[RowCount];
	int	Index=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *Pg=Ph->GetPageData(page);
			if(Pg!=NULL){
				LoadedInfoContainerInPhase	&LC=Pg->GetResultLoaded();
				for(LoadedInfoList *L=LC.NPListPack<LoadedInfoList>::GetFirst();L!=NULL;L=L->GetNext()){
					IndexPointer[Index].Pointer	=L;
					IndexPointer[Index].Page	=page;
					IndexPointer[Index].Phase	=phase;
					Index++;
				}
			}
		}
	}
	if(ui.toolButtonByPage->isChecked()==true){
		QSort(IndexPointer,RowCount,sizeof(struct LoadedInfoListStruct),FuncSortByPage);
	}
	else if(ui.toolButtonByName->isChecked()==true){
		QSort(IndexPointer,RowCount,sizeof(struct LoadedInfoListStruct),FuncSortByName);
	}
	else{
	}

	ui.tableWidget->setRowCount(RowCount);

	for(int Row=0;Row<RowCount;Row++){
		SetDataToTable(ui.tableWidget,0,Row,IndexPointer[Row].Pointer->AlgoRoot);
		SetDataToTable(ui.tableWidget,1,Row,IndexPointer[Row].Pointer->AlgoName);
		SetDataToTable(ui.tableWidget,2,Row,QString::number(IndexPointer[Row].Page));
		SetDataToTable(ui.tableWidget,3,Row,QString::number(IndexPointer[Row].Phase));
		if(IndexPointer[Row].Pointer->Error==LoadedInfoList::_NoFile)
			SetDataToTable(ui.tableWidget,4,Row,LangSolver.GetString(ShowLoadedInfoForm_LS,LID_33)/*"No file"*/);
		else if(IndexPointer[Row].Pointer->Error==LoadedInfoList::_Error)
			SetDataToTable(ui.tableWidget,4,Row,LangSolver.GetString(ShowLoadedInfoForm_LS,LID_34)/*"Error"*/);
		else if(IndexPointer[Row].Pointer->ItemCount==0)
			SetDataToTable(ui.tableWidget,4,Row,LangSolver.GetString(ShowLoadedInfoForm_LS,LID_35)/*"No Items"*/);
		else if(IndexPointer[Row].Pointer->Error==LoadedInfoList::_Success)
			SetDataToTable(ui.tableWidget,4,Row,LangSolver.GetString(ShowLoadedInfoForm_LS,LID_36)/*"OK"*/);
	}
	delete	[]IndexPointer;
}

void ShowLoadedInfoForm::on_pushButtonOK_clicked()
{
	close();
	emit	SignalClose();
}

void ShowLoadedInfoForm::on_toolButtonByPage_clicked()
{
	ShowList();
}

void ShowLoadedInfoForm::on_toolButtonByName_clicked()
{
	ShowList();
}