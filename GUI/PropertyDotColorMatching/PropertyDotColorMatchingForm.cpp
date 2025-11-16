#include "PropertyDotColorMatchingResource.h"
#include "PropertyDotColorMatchingForm.h"
#include "ui_PropertyDotColorMatchingForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyDotColorMatchingPacket.h"
//#include "BrightHistogramForm.h"
#include "CreateManualDotColorMatchingDialog.h"
#include "EditDotColorMatchingLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "ItemListForm.h"
#include "EditItemsDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyDotColorMatchingForm::PropertyDotColorMatchingForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyDotColorMatchingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	LibFolderID		=-1;
	ItemListWindow	=NULL;

	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ItemListForPageData=NULL;

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);

	ui->tableWidget->setColumnWidth (0, 40);
	ui->tableWidget->setColumnWidth (1, 48);
	ui->tableWidget->setColumnWidth (2, 160);
	ui->tableWidget->setColumnWidth (3, 56);

	if(BBase!=NULL){
		CmdCreateTempDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	LLib->SetLibID(-1);

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyDotColorMatchingForm::~PropertyDotColorMatchingForm()
{
	if(ItemListWindow!=NULL){
		ItemListWindow->deleteLater();
	}
    delete ui;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}
DotColorMatchingBase	*PropertyDotColorMatchingForm::GetDotColorMatchingBase(void)
{
	return (DotColorMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
}
void PropertyDotColorMatchingForm::on_pushButtonEditLibFolder_clicked()
{
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyDotColorMatchingForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void PropertyDotColorMatchingForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void	PropertyDotColorMatchingForm::ShowInEdit(void)
{
}
void	PropertyDotColorMatchingForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
}
void	PropertyDotColorMatchingForm::BuildForShow(void)
{
	ShowItemList();
}
void	PropertyDotColorMatchingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	CmdDotColorMatchingDrawModePacket	*BDrawModePacket=dynamic_cast<CmdDotColorMatchingDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		BDrawModePacket->ModeShowArea		=ui->toolButtonShowArea		->isChecked();
		BDrawModePacket->ModeShowRotation	=ui->toolButtonShowRotation	->isChecked();
		BDrawModePacket->ModeShowDiv		=ui->toolButtonShowDiv		->isChecked();
		BDrawModePacket->ModeShowFlat		=ui->toolButtonShowFlat		->isChecked();
		BDrawModePacket->ModeShowBackGround	=ui->toolButtonShowBackGround->isChecked();
		return;
	}
	CmdDotColorMatchingDrawEnd	*DotColorMatchingDEnd=dynamic_cast<CmdDotColorMatchingDrawEnd *>(packet);
	if(DotColorMatchingDEnd!=NULL){
		CreateManualDotColorMatchingDialog	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual DotColorMatching");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(DotColorMatchingDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=DotColorMatchingDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualDotColorMatching	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					CmdCreateByteArrayFromDotColorMatchingItemPacket	BCmd(GetLayersBase());
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.LayerList=DotColorMatchingDEnd->LayerList;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
			//ShowDotColorMatchingInfoList();
		}
	}
	CmdDotColorMatchingShowAttrPacket	*ShowAttr=dynamic_cast<CmdDotColorMatchingShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	/*
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			BInfo[i].DotColorMatchingInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();
			for(int layer=0;layer<GetLayerNumb();layer++){
				ListLayerAndIDPack	Items;
				if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
					break;
				for(ListPageLayerID *a=CmdExecuteMouseLDownVar->CurrentItem.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->Page==page && a->Layer==layer){
						Items.AppendList(new ListLayerAndID(a->Layer,a->ID));
					}
				}
				if(Items.GetNumber()!=NULL){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdReqDotColorMatchingFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckDotColorMatchingFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.DotColorMatchingInfoOnMouse)/sizeof(AckCmd.DotColorMatchingInfoOnMouse[0]);i++){
						if(AckCmd.DotColorMatchingInfoOnMouse[i]!=NULL){
							BInfo[N].DotColorMatchingInfoOnMouse=AckCmd.DotColorMatchingInfoOnMouse[i];
							AckCmd.DotColorMatchingInfoOnMouse[i]=NULL;
							BInfo[N].Page=page;
							BInfo[N].Layer=layer;
							N++;
							if(N>=sizeof(BInfo)/sizeof(BInfo[0]))
								break;
						}
					}
				}
			}
		}
		ShowTab();
		return;
	}
	*/
	/*
	CmdExecuteMouseRDownWithShift	*ShiftRight=dynamic_cast<CmdExecuteMouseRDownWithShift *>(packet);
	if(ShiftRight!=NULL){
		QByteArray	DotColorMatchingItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedDotColorMatchingItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedDotColorMatchingItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					DotColorMatchingItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(DotColorMatchingItemData.size()!=0){
			CreateManualDotColorMatchingForm	D(GetLayersBase(),NULL);
			CmdLoadDotColorMatchingItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=DotColorMatchingItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedDotColorMatching	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromDotColorMatchingItemPacket	BCmd;
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.LayerList=ShiftRight->LayerList;
					Cmd.Send(NULL,page,0);					
				}
			}
		}
	}
	*/
	CmdSetSpecialData	*CmdSetSpecialDataVar=dynamic_cast<CmdSetSpecialData *>(packet);
	if(CmdSetSpecialDataVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetSpecialData	DCmd(GetLayersBase(),sRoot,sName,globalPage);
			DCmd.SpecialData	=CmdSetSpecialDataVar->SpecialData;
			DCmd.SendOnly(NULL,globalPage ,0);
		}
		return;
	}
	CmdAddDotColorMatching	*CmdAddDotColorMatchingVar=dynamic_cast<CmdAddDotColorMatching *>(packet);
	if(CmdAddDotColorMatchingVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(CmdAddDotColorMatchingVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=CmdAddDotColorMatchingVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdAddDotColorMatching	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				Cmd.LibID=CmdAddDotColorMatchingVar->LibID;
				Cmd.ItemName=CmdAddDotColorMatchingVar->ItemName;
				Cmd.SendOnly(GlobalPage,0);
			}
		}
		return;
	}
	CmdDeleteDotColorMatchingByName	*CmdDeleteDotColorMatchingByNameVar=dynamic_cast<CmdDeleteDotColorMatchingByName *>(packet);
	if(CmdDeleteDotColorMatchingByNameVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdDeleteDotColorMatchingByName	DCmd(GetLayersBase(),sRoot,sName,globalPage);
			DCmd.ItemName	=CmdDeleteDotColorMatchingByNameVar->ItemName;
			DCmd.SendOnly(NULL,globalPage ,0);
		}
		return;
	}
}
void	PropertyDotColorMatchingForm::ShowEditLibrary(void)
{
	on_pushButtonEditLibrary_clicked();
}
void PropertyDotColorMatchingForm::on_pushButtonEditLibrary_clicked()
{
	EditDotColorMatchingLibraryDialog	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(LLib!=NULL){
		CmdLoadDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
			}
		}
	}
}

void PropertyDotColorMatchingForm::on_ButtonPickupTest_clicked()
{
	if(LLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDotColorMatchingForm_LS,LID_0)/*"Pickup Test"*/);

	GetLibraryFromWindow(*LLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibPoint	=LLib;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyDotColorMatchingForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyDotColorMatchingForm::on_ButtonGenerateLibs_clicked()
{
	if(LLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate DotColorMatchings automatically");
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDotColorMatchingForm_LS,LID_1)/*"Generating items"*/,GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateDotColorMatchings	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,GlobalPage,0);
	}
	ShowItemList();
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void	PropertyDotColorMatchingForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		CmdGetDotColorMatchingLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}


struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
	int						Priority;
};

int	DDimFunc(const void *a ,const void *b)
{
	if(((struct AlgorithmLibraryListClass *)a)->Priority>((struct AlgorithmLibraryListClass *)b)->Priority)
		return 1;
	if(((struct AlgorithmLibraryListClass *)a)->Priority<((struct AlgorithmLibraryListClass *)b)->Priority)
		return -1;
	return 0;
}

QColor	GetTableColor(int n)
{
	switch(n&7){
		case 0 :	return QColor(255,255,0);
		case 1 :	return QColor(235,255,0);
		case 2 :	return QColor(235,235,0);
		case 3 :	return QColor(215,235,0);
		case 4 :	return QColor(215,215,0);
		case 5 :	return QColor(195,215,0);
		case 6 :	return QColor(195,195,0);
		case 7 :	return QColor(175,195,0);
	}
	return Qt::white;
}

void	PropertyDotColorMatchingForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		CmdCreateTempDotColorMatchingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		if(LLib!=NULL){
			delete	LLib;
		}
		LLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			LLib->SetLibID(a->GetLibID());
			CmdLoadDotColorMatchingLibraryPacket	Packet(GetLayersBase());
			Packet.Point=LLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority=((DotColorMatchingLibrary *)(LLib->GetLibrary()))->Priority;
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		QSort(DDim,row,sizeof(DDim[0]),DDimFunc);
		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}
	
	bool	HasChanged;
	int		LCounter=0;
	do{
		HasChanged=false;
		LCounter++;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryList *b=a->GetNext();
			if(b!=NULL){
				CmdCreateTempDotColorMatchingLibraryPacket	ACreateCmd(GetLayersBase());
				CmdCreateTempDotColorMatchingLibraryPacket	BCreateCmd(GetLayersBase());
				BBase->TransmitDirectly(&ACreateCmd);
				BBase->TransmitDirectly(&BCreateCmd);

				CmdLoadDotColorMatchingLibraryPacket	ALoadLibCmd(GetLayersBase());
				CmdLoadDotColorMatchingLibraryPacket	BLoadLibCmd(GetLayersBase());
				ALoadLibCmd.Point=ACreateCmd.Point;
				ALoadLibCmd.Point->SetLibID(a->GetLibID());
				BLoadLibCmd.Point=BCreateCmd.Point;
				BLoadLibCmd.Point->SetLibID(b->GetLibID());
				BBase->TransmitDirectly(&ALoadLibCmd);
				BBase->TransmitDirectly(&BLoadLibCmd);
				DotColorMatchingLibrary	*ALib=(DotColorMatchingLibrary	*)ALoadLibCmd.Point;
				DotColorMatchingLibrary	*BLib=(DotColorMatchingLibrary	*)BLoadLibCmd.Point;
				if(ALib->Priority>BLib->Priority){
					delete	ALib;
					delete	BLib;
					SelectedLibList.Swap(a,b);
					HasChanged=true;
					goto	TryNext;
				}
				delete	ALib;
				delete	BLib;
			}
		}
TryNext:;
	}while(HasChanged==true && LCounter<30);

	int	row=0;
	int	CuPriority=-1;
	int	ColNum=-1;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(CuPriority!=DDim[row].Priority){
			CuPriority=DDim[row].Priority;
			ColNum++;
		}
		QColor	Col=GetTableColor(ColNum);

		QTableWidgetItem *W;
		W=ui->tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W->setBackground(Col);
		W=ui->tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
		W->setBackground(Col);
	}
}

void	PropertyDotColorMatchingForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{

}

void	PropertyDotColorMatchingForm::ShowItemList(void)
{
	ui->tableWidget->setRowCount(0);
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(ItemListForPageData!=NULL){
		delete	[]ItemListForPageData;
		ItemListForPageData=NULL;
	}
	ItemListForPageData=new ItemListForPageContainer[GetPageNumb()];

	if(BBase!=NULL){
		int	ListCount=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqItemListForPageContainer	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdAckItemListForPageContainer	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);

			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,AckCmd)==true){
				ItemListForPageData[page]=AckCmd.ItemListForPageData;
				ListCount+=ItemListForPageData[page].GetCount();
			}
		}
		ui->tableWidget->setRowCount(ListCount);
		int	Row=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			for(ItemListForPage *L=ItemListForPageData[page].GetFirst();L!=NULL;L=L->GetNext()){
				::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(page));
				::SetDataToTable(ui->tableWidget ,1,Row ,QString::number(L->LibID));
				QString	LibName=BBase->GetLibraryContainer()->GetLibraryName(L->LibID);
				::SetDataToTable(ui->tableWidget ,2,Row ,LibName);
				::SetDataToTable(ui->tableWidget ,3,Row ,QString::number(L->ItemCount));
				Row++;
			}
		}
	}
}

bool	PropertyDotColorMatchingForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		GetDotColorMatchingBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,data);
		return true;
	}
	return false;
}
void PropertyDotColorMatchingForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui->tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyDotColorMatchingForm::on_pushButtonGetBack_clicked()
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void	PropertyDotColorMatchingForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}
void PropertyDotColorMatchingForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyDotColorMatchingForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyDotColorMatchingForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index)
{
	int	r=ui->tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}

void	PropertyDotColorMatchingForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		CmdGetDotColorMatchingLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

void	PropertyDotColorMatchingForm::GenerateDotColorMatchings(void)
{
	on_ButtonGenerateLibs_clicked();
}


bool	PropertyDotColorMatchingForm::SaveContent(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LibType)==false)
		return false;
	if(LibList.Save(f)==false)
		return false;
	if(SelectedLibList.Save(f)==false)
		return false;
	if(::Save(f,LibFolderID)==false)
		return false;
	if(GlobalPickupArea.Save(f)==false)
		return false;
	return true;
}
bool	PropertyDotColorMatchingForm::LoadContent(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,LibType)==false)
		return false;
	if(LibList.Load(f)==false)
		return false;
	if(SelectedLibList.Load(f)==false)
		return false;
	if(::Load(f,LibFolderID)==false)
		return false;
	if(GlobalPickupArea.Load(f)==false)
		return false;
	ShowLibList();
	ShowSelectedLibList();

	QString FolderName;
	int ParentID;
	int NumberInFolder;
	if(GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindData(GetLayersBase()->GetDatabase(),LibFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
		SetLibFolder(LibFolderID ,FolderName);
	}
	return true;
}

void PropertyDotColorMatchingForm::on_tableWidget_itemSelectionChanged()
{
	int	CurrentRow=ui->tableWidget->currentRow();
	if(CurrentRow<0)
		return;

	ItemListForPage *a=NULL;
	int	Row=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
		for(ItemListForPage *L=ItemListForPageData[page].GetFirst();L!=NULL;L=L->GetNext(),Row++){
			if(CurrentRow==Row){
				a=L;
				goto	EndRow;
			}
		}
	}
EndRow:;

	if(a==NULL)
		return;
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"DotColorMatchingImagePanel",/**/"");
	if(f!=NULL){
		QStringList	Arg;
		Arg.append(QString::number(a->LibID));
		bool	Ok;
		f->ExecuteMacro(/**/"SelectItemsByLibID",Arg,Ok);
	}
}

void PropertyDotColorMatchingForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyDotColorMatchingForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
	DotColorMatchingBase	*BBase=GetDotColorMatchingBase();
	if(BBase!=NULL){
		int	row=ui->tableWidgetLibList->currentRow();
		AlgorithmLibraryList *a=LibList.GetItem(row);
		if(a!=NULL){
			QString	LibComment=BBase->GetLibComment(a->GetLibID());
			ui->tableWidgetLibList->setToolTip(LibComment);
		}
	}
}

void PropertyDotColorMatchingForm::on_pushButtonBlockList_clicked()
{
	if(ItemListWindow==NULL){
		ItemListWindow=new ItemListForm(GetLayersBase());
	}
	ItemListWindow->Initial();
	ItemListWindow->show();
}


void PropertyDotColorMatchingForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Index=ui->tableWidget->currentRow();
	if(Index<0)
		return;
	EditItemsDialog	D(GetLayersBase());
	{
		int	Row=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			for(ItemListForPage *L=ItemListForPageData[page].GetFirst();L!=NULL;L=L->GetNext()){
				if(Index==Row){
					GUICmdReqItemsByLibID	RCmd(GetLayersBase(),sRoot,sName,0);
					RCmd.ItemID	=-1;
					RCmd.LibID	=L->LibID;
					GUICmdAckItemsByLibID	ACmd(GetLayersBase(),sRoot,sName,0);
					if(RCmd.Send(0,0,ACmd)==true){
						D.SetItemInfo(ACmd.MasterNoOriginCode
									 ,ACmd.SubLibIDs
									 ,ACmd.ExpandToSubBlock);
					}
				}
				Row++;
			}
		}
	}
					
	if(D.exec()==true){
		int	Row=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			for(ItemListForPage *L=ItemListForPageData[page].GetFirst();L!=NULL;L=L->GetNext()){
				if(Index==Row){
					for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSetItemsByLibID	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
						RCmd.LibID=L->LibID;
						RCmd.AvailableMasterNo	=D.AvailableMasterNo;
						RCmd.MasterNoOriginCode	=D.MasterNoOriginCode;
						RCmd.AvailableSubBlock	=D.AvailableSubBlock;
						RCmd.SubBlockList		=D.SubBlockList;
						RCmd.ExpandToSubBlock	=D.ExpandToSubBlock;
						RCmd.Send(NULL,GlobalPage,0);
						return;
					}
				}
				Row++;
			}
		}
	}
}

