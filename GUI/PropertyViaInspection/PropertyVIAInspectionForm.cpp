/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVIA\PropertyVIAInspectionForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyVIAInspectionFormResource.h"
#include "PropertyVIAInspectionForm.h"
#include "ui_PropertyVIAInspectionForm.h"
#include "XDLLOnly.h"
//#include "SelectVIALibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyVIAPacket.h"
#include "CreateManualVIAForm.h"
#include "EditVIALibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "BrightHistogramForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyVIAInspectionForm::PropertyVIAInspectionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyVIAInspectionForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	LibFolderID=-1;

	VIABase	*BBase=GetVIABase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	int	tPage=0;
	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);	
	ui->tableWidgetVIAInfo->setColumnCount(3+GetLayerNumb(tPage));
	ui->tableWidgetVIAInfo->setColumnWidth (0, 30);
	ui->tableWidgetVIAInfo->setColumnWidth (1, 100);
	ui->tableWidgetVIAInfo->setColumnWidth (2, 60);
	QStringList	HeaderLabel;
	HeaderLabel.append(QString(/**/"ID"));
	HeaderLabel.append(QString(/**/""));
	HeaderLabel.append(QString(/**/""));
	for(int layer=0;layer<GetLayerNumb(tPage);layer++){
		ui->tableWidgetVIAInfo->setColumnWidth (3+layer, 50);
		HeaderLabel.append(GetParamGlobal()->GetLayerName(layer));
	}
	ui->tableWidgetVIAInfo->setHorizontalHeaderLabels(HeaderLabel);

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].VIAInfoOnMouse=NULL;
	}

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempVIALibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	if(TempLib!=NULL){
		TempLib->SetLibID(-1);
	}
	if(ui->toolButtonLibrary->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
	}
	if(ui->toolButtonCreateVIA->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		ShowVIAInfoList();
	}

	LibSortType	=KOS_ID_Up;
	connect(ui->tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyVIAInspectionForm::~PropertyVIAInspectionForm()
{
    delete ui;

	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}
void	PropertyVIAInspectionForm::MListSectionClicked ( int logicalIndex )
{
	switch(logicalIndex){
		case 0:
			if(LibSortType==KOS_ID_Up)
				LibSortType=KOS_ID_Dn;
			else
				LibSortType=KOS_ID_Up;
			break;
		case 1:
			if(LibSortType==KOS_Name_Up)
				LibSortType=KOS_Name_Dn;
			else
				LibSortType=KOS_Name_Up;
			break;
	}
	ShowLibList();
}


VIABase	*PropertyVIAInspectionForm::GetVIABase(void)
{
	return (VIABase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
}

static	int	FuncIDUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pa->GetLibID() - pb->GetLibID();
}

static	int	FuncIDDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	return pb->GetLibID() - pa->GetLibID();
}

static	int	FuncNameUp(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return 1;
	if(pa->GetLibName() > pb->GetLibName())
		return -1;
	return 0;
}

static	int	FuncNameDn(const void *a ,const void *b)
{
	AlgorithmLibraryList	*pa=((AlgorithmLibraryList **)a)[0];
	AlgorithmLibraryList	*pb=((AlgorithmLibraryList **)b)[0];
	if(pa->GetLibName() < pb->GetLibName())
		return -1;
	if(pa->GetLibName() > pb->GetLibName())
		return 1;
	return 0;
}

void	PropertyVIAInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		CmdGetVIALibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		//LibList	=Packet.AList;
		LibList.RemoveAll();

		AlgorithmLibraryList	**Dim=new AlgorithmLibraryList*[Packet.AList.GetCount()];
		int	row=0;
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			Dim[row]=a;
		}
		if(LibSortType==KOS_ID_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDUp);
		else if(LibSortType==KOS_ID_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncIDDn);
		else if(LibSortType==KOS_Name_Up)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameUp);
		else if(LibSortType==KOS_Name_Dn)
			QSort(Dim,row,sizeof(Dim[0]),FuncNameDn);

		for(int i=0;i<row;i++){
			Packet.AList.RemoveList(Dim[i]);
			LibList.AppendList(Dim[i]);
		}
		delete	[]Dim;

		row=0;
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
void	PropertyVIAInspectionForm::ShowInEdit(void)
{
	ShowVIAInfoList();
}
void	PropertyVIAInspectionForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
	on_toolButtonLibrary_clicked();
	on_toolButtonCreateVIA_clicked();
}
void	PropertyVIAInspectionForm::BuildForShow(void)
{
	ShowVIAInfoList();
}
void	PropertyVIAInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	VIABase	*BBase=GetVIABase();
	CmdVIADrawModePacket	*BDrawModePacket=dynamic_cast<CmdVIADrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=VIADrawAttr::_LibTest;
		else if(ui->toolButtonCreateVIA->isChecked()==true)
			BDrawModePacket->Mode=VIADrawAttr::_CreatedVIA;
		return;
	}
	CmdVIADrawEnd	*VIADEnd=dynamic_cast<CmdVIADrawEnd *>(packet);
	if(VIADEnd!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=VIADEnd->Area;
				VIALibrary	*ALib=dynamic_cast<VIALibrary *>(TempLib->GetLibrary());
				BrightHistogramForm	D(VIADEnd->Area,VIADEnd->ImagePanelPoint
									  ,ALib->PickupL,ALib->PickupH,this);
				D.Reflect(ALib->PickupL,ALib->PickupH);
				if(D.exec()==(int)true){
					ALib->PickupL	=D.PickupL;
					ALib->PickupH	=D.PickupH;
				}
			}
		}
		else if(ui->toolButtonCreateVIA->isChecked()==true){
			CreateManualVIAForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual VIA");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(VIADEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=VIADEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualVIA	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						CmdCreateByteArrayFromVIAItemPacket	BCmd(GetLayersBase());
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=VIADEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowVIAInfoList();
			}
		}
	}
	CmdVIAShowAttrPacket	*ShowAttr=dynamic_cast<CmdVIAShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].VIAInfoOnMouse!=NULL)
			//	delete	BInfo[i].VIAInfoOnMouse;
			BInfo[i].VIAInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();
			for(int layer=0;layer<GetLayerNumb(page);layer++){
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
					GUICmdReqVIAFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckVIAFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.VIAInfoOnMouse)/sizeof(AckCmd.VIAInfoOnMouse[0]);i++){
						if(AckCmd.VIAInfoOnMouse[i]!=NULL){
							BInfo[N].VIAInfoOnMouse=AckCmd.VIAInfoOnMouse[i];
							AckCmd.VIAInfoOnMouse[i]=NULL;
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
		return;
	}
	/*
	CmdExecuteMouseRDownWithShift	*ShiftRight=dynamic_cast<CmdExecuteMouseRDownWithShift *>(packet);
	if(ShiftRight!=NULL){
		QByteArray	VIAItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedVIAItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedVIAItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					VIAItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(VIAItemData.size()!=0){
			CreateManualVIAForm	D(GetLayersBase(),NULL);
			CmdLoadVIAItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=VIAItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedVIA	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromVIAItemPacket	BCmd;
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
	CmdReqSetButtonMode	*CmdReqSetButtonModeVar=dynamic_cast<CmdReqSetButtonMode *>(packet);
	if(CmdReqSetButtonModeVar!=NULL){
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_LibraryTest){
			ui->toolButtonLibrary->setChecked(true);
		}
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_CreateVIA){
			ui->toolButtonCreateVIA->setChecked(true);
		}
	}
}

bool	PropertyVIAInspectionForm::SaveContent(QIODevice *f)
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
bool	PropertyVIAInspectionForm::LoadContent(QIODevice *f)
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

void	PropertyVIAInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	VIALibrary	*ALib=dynamic_cast<VIALibrary *>(data.GetLibrary());
	ui->EditMinVIASize		->setValue(ALib->MinVIASize);
	ui->EditMaxVIASize		->setValue(ALib->MaxVIASize);
	ui->EditMinVIADots		->setValue(ALib->MinVIADots);
	ui->EditMaxVIADots		->setValue(ALib->MaxVIADots);
	ui->EditLimitVIASize	->setValue(ALib->LimitVIASize);
	ui->EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui->EditNoiseSize		->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority		->setValue(ALib->Priority);
}

void	PropertyVIAInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	VIALibrary	*ALib=dynamic_cast<VIALibrary *>(data.GetLibrary());
	ALib->MinVIASize		=ui->EditMinVIASize	->value();
	ALib->MaxVIASize		=ui->EditMaxVIASize	->value();
	ALib->MinVIADots		=ui->EditMinVIADots	->value();
	ALib->MaxVIADots		=ui->EditMaxVIADots	->value();
	ALib->LimitVIASize		=ui->EditLimitVIASize	->value();
	ALib->SpaceToOutline	=ui->EditSpaceToOutline	->value();
	ALib->NoiseSize			=ui->EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui->EditNoiseSizePinHole->value();
	ALib->Priority			=ui->EditPriority		->value();
}

void PropertyVIAInspectionForm::on_toolButtonLibrary_clicked()
{
	if(ui->toolButtonLibrary->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_LibraryTest;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
	}
	GetLayersBase()->SetStatusModes(this,/**/"LibraryMode");

	BroadcastShowInEdit();
}

void PropertyVIAInspectionForm::on_toolButtonCreateVIA_clicked()
{
	if(ui->toolButtonCreateVIA->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_CreateVIA;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		ShowVIAInfoList();
	}
	GetLayersBase()->SetStatusModes(this,/**/"VIAMode");
	BroadcastShowInEdit();
}

void PropertyVIAInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	VIABase	*BBase=GetVIABase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyVIAInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void PropertyVIAInspectionForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_0)/*"Library error"*/
									, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}
void PropertyVIAInspectionForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"VIAInspectionImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}

void PropertyVIAInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyVIAInspectionForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL
										, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_2)/*"Library error"*/
										, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyVIAInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
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

void	PropertyVIAInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		CmdCreateTempVIALibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;
		VIALibrary	*ALib=dynamic_cast<VIALibrary *>(SLib->GetLibrary());
		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadVIALibraryPacket	Packet(GetLayersBase());
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


void PropertyVIAInspectionForm::on_pushButtonSetFrom_clicked()
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

void PropertyVIAInspectionForm::on_pushButtonGetBack_clicked()
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

void PropertyVIAInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyVIAInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyVIAInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditVIALibrary	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(TempLib!=NULL){
		CmdLoadVIALibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VIABase	*BBase=GetVIABase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
		}
	}
}

void PropertyVIAInspectionForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_16)/*"Pickup Test"*/);

	GetLibraryFromWindow(*TempLib);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"VIAInspectionImagePanel" ,/**/"");
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

void PropertyVIAInspectionForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyVIAInspectionForm::on_ButtonGenerateLibs_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate VIAs automatically");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"VIAInspectionImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_17)/*"Generating items"*/
										,LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateVIAs	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyVIAInspectionForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
																, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_4)/*"Warning"*/
																, LangSolver.GetString(PropertyVIAInspectionForm_LS,LID_5)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateVIALibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==TempLib->GetLibID()){
			a->SetLibName(TempLib->GetLibName());
		}
	}
	ShowLibList();
	ShowSelectedLibList();
}

void PropertyVIAInspectionForm::ShowVIAInfoList(void)
{
	VIAInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqVIAInfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendVIAInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(VIAInfoList *a=CmdSend.VIAInfos.GetFirst();a!=NULL;a=a->GetNext()){
			VIAInfoList *b;
			for(b=VIAInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						IntClass	*d=b->VIACount.GetItem(layer);
						IntClass	*s=a->VIACount.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new VIAInfoList();
				b->LibID=a->LibID;
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					IntClass	*s=a->VIACount.GetItem(layer);
					b->VIACount.Add(s->GetValue());
				}
				VIAInfos.AppendList(b);
			}
		}
	}
	int	N=VIAInfos.GetNumber();
	ui->tableWidgetVIAInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(VIAInfoList *a=VIAInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	VIABase	*BBase=GetVIABase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(VIAInfoList *a=VIAInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QString	LibName;
		for(AlgorithmLibraryList *m=LibIDList.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetLibID()==a->GetLibID()){
				LibName=m->GetLibName();
				break;
			}
		}
		QTableWidgetItem *W;
		W=ui->tableWidgetVIAInfo->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetVIAInfo->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->LibID));

		W=ui->tableWidgetVIAInfo->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetVIAInfo->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(LibName);

		W=ui->tableWidgetVIAInfo->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetVIAInfo->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		int	TotalCount=0;
		for(IntClass *h=a->VIACount.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));

		for(int layer=0;layer<GetLayerNumb(0);layer++){
			W=ui->tableWidgetVIAInfo->item ( row, 3+layer);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetVIAInfo->setItem ( row, 3+layer,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			IntClass *h=a->VIACount.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}

void	PropertyVIAInspectionForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void	PropertyVIAInspectionForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	VIABase	*BBase=GetVIABase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

void	PropertyVIAInspectionForm::GenerateVIAs(void)
{
	on_ButtonGenerateLibs_clicked();
}