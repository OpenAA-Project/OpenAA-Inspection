#include "CreateManualDotMatchingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDotMatching\PropertyDotMatchingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyDotMatchingForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyDotMatchingPacket.h"
//#include "BrightHistogramForm.h"
#include "CreateManualDotMatchingForm.h"
#include "EditDotMatchingLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "ui_PropertyDotMatchingForm.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyDotMatchingForm::PropertyDotMatchingForm(LayersBase *Base ,QWidget *parent)
    : GUIFormBase(Base,parent)
    ,ui(new Ui::PropertyDotMatchingForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID=-1;

	DotMatchingBase	*BBase=GetDotMatchingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempDotMatchingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	if(TempLib!=NULL){
		TempLib->SetLibID(-1);
	}
}

PropertyDotMatchingForm::~PropertyDotMatchingForm()
{
    delete ui;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}
DotMatchingBase	*PropertyDotMatchingForm::GetDotMatchingBase(void)
{
	return (DotMatchingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DotMatching");
}
void PropertyDotMatchingForm::on_pushButtonEditLibFolder_clicked()
{
	DotMatchingBase	*BBase=GetDotMatchingBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyDotMatchingForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void PropertyDotMatchingForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void	PropertyDotMatchingForm::ShowInEdit(void)
{
}
void	PropertyDotMatchingForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
}
void	PropertyDotMatchingForm::BuildForShow(void)
{
}
void	PropertyDotMatchingForm::TransmitDirectly(GUIDirectMessage *packet)
{
	DotMatchingBase	*BBase=GetDotMatchingBase();
	CmdDotMatchingDrawModePacket	*BDrawModePacket=dynamic_cast<CmdDotMatchingDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		return;
	}
	CmdDotMatchingDrawEnd	*DotMatchingDEnd=dynamic_cast<CmdDotMatchingDrawEnd *>(packet);
	if(DotMatchingDEnd!=NULL){
		CreateManualDotMatchingForm	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual DotMatching");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(DotMatchingDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=DotMatchingDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualDotMatching	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					CmdCreateByteArrayFromDotMatchingItemPacket	BCmd(GetLayersBase());
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.LayerList=DotMatchingDEnd->LayerList;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
			//ShowDotMatchingInfoList();
		}
	}
	CmdDotMatchingShowAttrPacket	*ShowAttr=dynamic_cast<CmdDotMatchingShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	/*
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			BInfo[i].DotMatchingInfoOnMouse=NULL;
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
					GUICmdReqDotMatchingFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckDotMatchingFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.DotMatchingInfoOnMouse)/sizeof(AckCmd.DotMatchingInfoOnMouse[0]);i++){
						if(AckCmd.DotMatchingInfoOnMouse[i]!=NULL){
							BInfo[N].DotMatchingInfoOnMouse=AckCmd.DotMatchingInfoOnMouse[i];
							AckCmd.DotMatchingInfoOnMouse[i]=NULL;
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
		QByteArray	DotMatchingItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedDotMatchingItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedDotMatchingItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					DotMatchingItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(DotMatchingItemData.size()!=0){
			CreateManualDotMatchingForm	D(GetLayersBase(),NULL);
			CmdLoadDotMatchingItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=DotMatchingItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedDotMatching	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromDotMatchingItemPacket	BCmd;
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
}
void PropertyDotMatchingForm::on_pushButtonEditLibrary_clicked()
{
	EditDotMatchingLibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadDotMatchingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		DotMatchingBase	*BBase=GetDotMatchingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}
}

void PropertyDotMatchingForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDotMatchingForm_LS,LID_10)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotMatchingImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibPoint	=TempLib;
		Cmd.LayerList	=LayerList;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyDotMatchingForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyDotMatchingForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate DotMatchings automatically");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DotMatchingImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyDotMatchingForm_LS,LID_11)/*"Generating items"*/
										,LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateDotMatchings	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void	PropertyDotMatchingForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		CmdGetDotMatchingLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
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

void	PropertyDotMatchingForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		CmdCreateTempDotMatchingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		DotMatchingLibrary	*ALib=dynamic_cast<DotMatchingLibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadDotMatchingLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority=ALib->Priority;
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

void	PropertyDotMatchingForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{

}

bool	PropertyDotMatchingForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		GetDotMatchingBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,data);
		return true;
	}
	return false;
}


void PropertyDotMatchingForm::on_pushButtonSetFrom_clicked()
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

void PropertyDotMatchingForm::on_pushButtonGetBack_clicked()
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
void	PropertyDotMatchingForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}
void PropertyDotMatchingForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyDotMatchingForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyDotMatchingForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index)
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

void	PropertyDotMatchingForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	DotMatchingBase	*BBase=GetDotMatchingBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

void	PropertyDotMatchingForm::GenerateDotMatchings(void)
{
	on_ButtonGenerateLibs_clicked();
}


bool	PropertyDotMatchingForm::SaveContent(QIODevice *f)
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
bool	PropertyDotMatchingForm::LoadContent(QIODevice *f)
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
