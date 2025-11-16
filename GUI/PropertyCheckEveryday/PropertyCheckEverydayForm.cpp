#include "PropertyCheckEverydayFormResource.h"
#include "PropertyCheckEverydayForm.h"
#include "ui_PropertyCheckEverydayForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
//#include "XPropertyVIAPacket.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XDataInLayer.h"
#include "XCheckEverydayGUIPacket.h"
#include "CreateManualLightDialog.h"
#include "CreateManualFocusDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyCheckEverydayForm::PropertyCheckEverydayForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyCheckEverydayForm)
{
    ui->setupUi(this);

	ui->tableWidgetLight->setColumnWidth(0,48);	//Page
	ui->tableWidgetLight->setColumnWidth(1,48);	//Layer
	ui->tableWidgetLight->setColumnWidth(2,48);	//ID
	ui->tableWidgetLight->setColumnWidth(3,60);	//BrightLow
	ui->tableWidgetLight->setColumnWidth(4,60);	//BrightHigh
	ui->tableWidgetLight->setColumnWidth(5,60);	//Value

	ui->tableWidgetFocus->setColumnWidth(0,48);	//Page
	ui->tableWidgetFocus->setColumnWidth(1,48);	//Layer
	ui->tableWidgetFocus->setColumnWidth(2,48);	//ID
	ui->tableWidgetFocus->setColumnWidth(3,60);	//FocusLow
	ui->tableWidgetFocus->setColumnWidth(4,60);	//Value
}

PropertyCheckEverydayForm::~PropertyCheckEverydayForm()
{
    delete ui;
}

CheckEverydayBase	*PropertyCheckEverydayForm::GetCheckEverydayBase(void)
{
	return (CheckEverydayBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
}


void	PropertyCheckEverydayForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCheckEverydayDrawEnd	*CmdCheckEverydayDrawEndVar=dynamic_cast<CmdCheckEverydayDrawEnd *>(packet);
	if(CmdCheckEverydayDrawEndVar!=NULL){
		if(ui->toolButtonLight->isChecked()==true){
			CreateManualLightDialog	D(GetLayersBase());
			if(D.exec()==(int)true){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Light");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(CmdCheckEverydayDrawEndVar->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=CmdCheckEverydayDrawEndVar->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdReqAddManualLight	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						Cmd.ItemName	=D.ItemName;
						Cmd.BrightnessLow =D.BrightnessLow;
						Cmd.BrightnessHigh=D.BrightnessHigh;
						Cmd.LayerList=CmdCheckEverydayDrawEndVar->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
			}
			ShowGrid();
		}
		else if(ui->toolButtonFocus->isChecked()==true){
			CreateManualFocusDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Focus");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(CmdCheckEverydayDrawEndVar->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=CmdCheckEverydayDrawEndVar->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdReqAddManualFocus	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						Cmd.ItemName	=D.ItemName;
						Cmd.FocusLow =D.FocusLow;
						Cmd.LayerList=CmdCheckEverydayDrawEndVar->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
			}
			ShowGrid();
		}
	}
}

static	int	SortLightInfoFunc(const void *a , const void *b)
{
	CheckEverydayLightInfo	**aa=(CheckEverydayLightInfo **)a;
	CheckEverydayLightInfo	**bb=(CheckEverydayLightInfo **)b;
	if(aa[0]->Page<bb[0]->Page)
		return 1;
	if(aa[0]->Page>bb[0]->Page)
		return -1;
	if(aa[0]->Layer<bb[0]->Layer)
		return 1;
	if(aa[0]->Layer>bb[0]->Layer)
		return -1;
	if(aa[0]->ID<bb[0]->ID)
		return 1;
	if(aa[0]->ID>bb[0]->ID)
		return -1;
	return 0;
}


static	int	SortFocusInfoFunc(const void *a , const void *b)
{
	CheckEverydayFocusInfo	**aa=(CheckEverydayFocusInfo **)a;
	CheckEverydayFocusInfo	**bb=(CheckEverydayFocusInfo **)b;
	if(aa[0]->Page<bb[0]->Page)
		return 1;
	if(aa[0]->Page>bb[0]->Page)
		return -1;
	if(aa[0]->Layer<bb[0]->Layer)
		return 1;
	if(aa[0]->Layer>bb[0]->Layer)
		return -1;
	if(aa[0]->ID<bb[0]->ID)
		return 1;
	if(aa[0]->ID>bb[0]->ID)
		return -1;
	return 0;
}

void PropertyCheckEverydayForm::ShowGrid(void)
{
	CheckEverydayLightInfoContainer	TmpInfoLight;
	CheckEverydayFocusInfoContainer	TmpInfoFocus;

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqInfo	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckInfo	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			TmpInfoLight+=ACmd.InfoLight;
			TmpInfoFocus+=ACmd.InfoFocus;
		}
	}
	CheckEverydayLightInfo	**LTmp=new CheckEverydayLightInfo*[TmpInfoLight.GetNumber()];
	CheckEverydayFocusInfo	**FTmp=new CheckEverydayFocusInfo*[TmpInfoFocus.GetNumber()];

	int	LRow=0;
	for(CheckEverydayLightInfo *L=TmpInfoLight.GetFirst();L!=NULL;){
		CheckEverydayLightInfo *LNext=L->GetNext();
		LTmp[LRow]=L;
		LRow++;
		TmpInfoLight.RemoveList(L);
		L=LNext;
	}
	int	FRow=0;
	for(CheckEverydayFocusInfo *F=TmpInfoFocus.GetFirst();F!=NULL;){
		CheckEverydayFocusInfo *FNext=F->GetNext();
		FTmp[FRow]=F;
		FRow++;
		TmpInfoFocus.RemoveList(F);
		F=FNext;
	}
	QSort(LTmp,LRow,sizeof(CheckEverydayLightInfo *),SortLightInfoFunc);
	QSort(FTmp,FRow,sizeof(CheckEverydayFocusInfo *),SortFocusInfoFunc);

	ui->tableWidgetLight->setRowCount(LRow);
	ui->tableWidgetFocus->setRowCount(FRow);

	for(int row=0;row<LRow;row++){
		::SetDataToTable(ui->tableWidgetLight ,0,row ,QString::number(LTmp[row]->Page));
		::SetDataToTable(ui->tableWidgetLight ,1,row ,QString::number(LTmp[row]->Layer));
		if(LTmp[row]->ItemName.isEmpty()==true)
			::SetDataToTable(ui->tableWidgetLight ,2,row ,QString::number(LTmp[row]->ID));
		else
			::SetDataToTable(ui->tableWidgetLight ,2,row ,QString::number(LTmp[row]->ID) + LangSolver.GetString(PropertyCheckEverydayForm_LS,LID_0)/*" / "*/+LTmp[row]->ItemName);
		::SetDataToTable(ui->tableWidgetLight ,3,row ,QString::number(LTmp[row]->BrightnessLow));
		::SetDataToTable(ui->tableWidgetLight ,4,row ,QString::number(LTmp[row]->BrightnessHigh));
		::SetDataToTable(ui->tableWidgetLight ,5,row ,QString::number(LTmp[row]->CurrentValue));
		TmpInfoLight.AppendList(LTmp[row]);
	}
	for(int row=0;row<FRow;row++){
		::SetDataToTable(ui->tableWidgetFocus ,0,row ,QString::number(FTmp[row]->Page));
		::SetDataToTable(ui->tableWidgetFocus ,1,row ,QString::number(FTmp[row]->Layer));
		if(FTmp[row]->ItemName.isEmpty()==true)
			::SetDataToTable(ui->tableWidgetLight ,2,row ,QString::number(FTmp[row]->ID));
		else
			::SetDataToTable(ui->tableWidgetLight ,2,row ,QString::number(FTmp[row]->ID) + LangSolver.GetString(PropertyCheckEverydayForm_LS,LID_1)/*" / "*/+FTmp[row]->ItemName);
		::SetDataToTable(ui->tableWidgetFocus ,3,row ,QString::number(FTmp[row]->FocusLow,'f',3));
		::SetDataToTable(ui->tableWidgetFocus ,4,row ,QString::number(FTmp[row]->CurrentValue));
		TmpInfoFocus.AppendList(FTmp[row]);
	}
	delete	[]LTmp;
	delete	[]FTmp;

	InfoLight=TmpInfoLight;
	InfoFocus=TmpInfoFocus;
}

void PropertyCheckEverydayForm::showEvent ( QShowEvent * event )
{
	ShowGrid();
}
void	PropertyCheckEverydayForm::BuildForShow(void)
{
	ShowGrid();
}

void PropertyCheckEverydayForm::on_toolButtonLight_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void PropertyCheckEverydayForm::on_toolButtonFocus_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void PropertyCheckEverydayForm::on_pushButtonSave_clicked()
{

}

void PropertyCheckEverydayForm::on_tableWidgetLight_clicked(const QModelIndex &index)
{
	CheckEverydayLightInfo *L=InfoLight.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckEverydayImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,L->Layer,L->ID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyCheckEverydayForm::on_tableWidgetLight_doubleClicked(const QModelIndex &index)
{
	CheckEverydayLightInfo *L=InfoLight.GetItem(index.row());
	if(L==NULL)
		return;
	CreateManualLightDialog	D(GetLayersBase());
	D.ItemName		=L->ItemName;
	D.BrightnessLow	=L->BrightnessLow;
	D.BrightnessHigh=L->BrightnessHigh;
	D.Reflect();
	if(D.exec()==(int)true){
		int	GlobalPage=L->Page;
		GUICmdReqModifyManualLight	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.ItemName		=D.ItemName;
		Cmd.BrightnessLow	=D.BrightnessLow;
		Cmd.BrightnessHigh	=D.BrightnessHigh;
		Cmd.Layer			=L->Layer;
		Cmd.ItemID			=L->ID;
		Cmd.SendOnly(GlobalPage,0);
		ShowGrid();
	}
}

void PropertyCheckEverydayForm::on_tableWidgetFocus_clicked(const QModelIndex &index)
{
	CheckEverydayFocusInfo *L=InfoFocus.GetItem(index.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"CheckEverydayImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,L->Layer,L->ID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyCheckEverydayForm::on_tableWidgetFocus_doubleClicked(const QModelIndex &index)
{
	CheckEverydayFocusInfo *L=InfoFocus.GetItem(index.row());
	if(L==NULL)
		return;
	CreateManualFocusDialog	D(GetLayersBase());
	D.ItemName	=L->ItemName;
	D.FocusLow	=L->FocusLow;
	D.Reflect();
	if(D.exec()==(int)true){
		int	GlobalPage=L->Page;
		GUICmdReqModifyManualFocus	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.ItemName	=D.ItemName;
		Cmd.FocusLow	=D.FocusLow;
		Cmd.Layer		=L->Layer;
		Cmd.ItemID		=L->ID;
		Cmd.SendOnly(GlobalPage,0);
		ShowGrid();
	}
}
