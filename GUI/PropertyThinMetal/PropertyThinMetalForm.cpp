#include "PropertyThinMetalFormResource.h"
#include "PropertyThinMetalForm.h"
#include "ui_PropertyThinMetalForm.h"
#include "XDLLOnly.h"
//#include "SelectThinMetalLibraryForm.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyThinMetalPacket.h"
#include "CreateManualThinMetalForm.h"
#include "EditLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "BrightHistogramForm.h"
#include "DistinguishPix.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyThinMetalForm::PropertyThinMetalForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyThinMetalForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	LibFolderID=-1;
	ShowSampleFormInst=NULL;

	ThinMetalBase	*BBase=GetThinMetalBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);	

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].ThinMetalInfoOnMouse=NULL;
	}

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempThinMetalLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	if(LLib!=NULL){
		LLib->SetLibID(-1);
	}
	if(ui->toolButtonLibrary->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
	}
	if(ui->toolButtonCreateArea->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		ShowThinMetalInfoList();
	}

	LibSortType	=KOS_ID_Up;
	connect(ui->tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	ui->tableWidgetItems->setColumnWidth (0, 48);
	ui->tableWidgetItems->setColumnWidth (1, 48);
	ui->tableWidgetItems->setColumnWidth (2, 60);
	ui->tableWidgetItems->setColumnWidth (3, 150);
}

PropertyThinMetalForm::~PropertyThinMetalForm()
{
	if(ShowSampleFormInst!=NULL)
		delete	ShowSampleFormInst;
	ShowSampleFormInst=NULL;

    delete ui;

	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}
void	PropertyThinMetalForm::MListSectionClicked ( int logicalIndex )
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


ThinMetalBase	*PropertyThinMetalForm::GetThinMetalBase(void)
{
	return (ThinMetalBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ThinMetal");
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

void	PropertyThinMetalForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		CmdGetThinMetalLibraryListPacket	Packet(GetLayersBase());
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
void	PropertyThinMetalForm::ShowInEdit(void)
{
	ShowThinMetalInfoList();
}
void	PropertyThinMetalForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
	on_toolButtonLibrary_clicked();
	//on_toolButtonCreateThinMetal_clicked();
}
void	PropertyThinMetalForm::TransmitDirectly(GUIDirectMessage *packet)
{
	ThinMetalBase	*BBase=GetThinMetalBase();
	CmdThinMetalDrawModePacket	*BDrawModePacket=dynamic_cast<CmdThinMetalDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true)
			BDrawModePacket->Mode=ThinMetalDrawAttr::_LibTest;
		else if(ui->toolButtonCreateArea->isChecked()==true)
			BDrawModePacket->Mode=ThinMetalDrawAttr::_CreatedArea;
		return;
	}
	CmdThinMetalDrawEnd	*ThinMetalDEnd=dynamic_cast<CmdThinMetalDrawEnd *>(packet);
	if(ThinMetalDEnd!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true){
			if(LLib->GetLibID()>=0){
				ThinMetalLibrary	*ALib=dynamic_cast<ThinMetalLibrary *>(LLib->GetLibrary());
				if(ALib!=NULL){
					//GlobalPickupArea+=ThinMetalDEnd->Area;
					BrightHistogramForm	D(ThinMetalDEnd->Area
											,ThinMetalDEnd->ImagePanelPoint
											,ALib->PickupL,ALib->PickupH
											,this);
					D.Reflect(ALib->PickupL,ALib->PickupH);
					if(D.exec()==(int)true){
						ALib->PickupL	=D.PickupL;
						ALib->PickupH	=D.PickupH;
					}
				}
			}
		}
		else if(ui->toolButtonCreateArea->isChecked()==true){
			CreateManualThinMetalForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual ThinMetal");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(ThinMetalDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=ThinMetalDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualThinMetal	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						CmdCreateByteArrayFromThinMetalItemPacket	BCmd(GetLayersBase());
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=ThinMetalDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowThinMetalInfoList();
			}
		}
	}
	CmdThinMetalShowAttrPacket	*ShowAttr=dynamic_cast<CmdThinMetalShowAttrPacket *>(packet);
	if(ShowAttr!=NULL){

	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].ThinMetalInfoOnMouse!=NULL)
			//	delete	BInfo[i].ThinMetalInfoOnMouse;
			BInfo[i].ThinMetalInfoOnMouse=NULL;
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
					GUICmdReqThinMetalFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckThinMetalFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.ThinMetalInfoOnMouse)/sizeof(AckCmd.ThinMetalInfoOnMouse[0]);i++){
						if(AckCmd.ThinMetalInfoOnMouse[i]!=NULL){
							BInfo[N].ThinMetalInfoOnMouse=AckCmd.ThinMetalInfoOnMouse[i];
							AckCmd.ThinMetalInfoOnMouse[i]=NULL;
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
		QByteArray	ThinMetalItemData;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
			GUICmdReqSelectedThinMetalItemAttr	ReqCmd(GetLayersBase(),sRoot,sName,page);
			ReqCmd.LayerList=ShiftRight->LayerList;
			GUICmdSendSelectedThinMetalItemAttr	SendCmd(GetLayersBase(),sRoot,sName,page);
			if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,SendCmd)==true
			&& SendCmd.IsReceived()==true){
				if(SendCmd.ExistSelected==true){
					ThinMetalItemData=SendCmd.BItem;
					break;
				}
			}
		}
		if(ThinMetalItemData.size()!=0){
			CreateManualThinMetalForm	D(GetLayersBase(),NULL);
			CmdLoadThinMetalItemPacketFromByteArray	CmdPacket;
			CmdPacket.Buff=ThinMetalItemData;
			CmdPacket.BItemPoint=D.BItem;
			BBase->TransmitDirectly(&CmdPacket);
			D.Reflect();
			if(D.exec()==(int)true){
				IntList PageList;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					GUICmdSendModifySelectedThinMetal	Cmd(GetLayersBase(),sRoot,sName,page);
					CmdCreateByteArrayFromThinMetalItemPacket	BCmd;
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
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_CreateThinMetal){
			ui->toolButtonCreateArea->setChecked(true);
		}
	}
}


bool	PropertyThinMetalForm::SaveContent(QIODevice *f)
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
bool	PropertyThinMetalForm::LoadContent(QIODevice *f)
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

void	PropertyThinMetalForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	ThinMetalLibrary	*d=dynamic_cast<ThinMetalLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditMinSize		->setValue(d->MinSize);
	ui->EditMaxSize		->setValue(d->MaxSize);
	ui->EditMinDots		->setValue(d->MinDots);
	ui->EditMaxDots		->setValue(d->MaxDots);
	ui->EditLimitSize	->setValue(d->LimitSize);
	/*
	ui->EditSpaceToOutline	->setValue(data.SpaceToOutline);
	ui->EditNoiseSize		->setValue(data.NoiseSize);
	ui->EditNoiseSizePinHole	->setValue(data.NoiseSizePinHole);
	ui->EditPriority			->setValue(data.Priority);
	*/
}

void	PropertyThinMetalForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	ThinMetalLibrary	*d=dynamic_cast<ThinMetalLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->MinSize	=ui->EditMinSize	->value();
	d->MaxSize	=ui->EditMaxSize	->value();
	d->MinDots	=ui->EditMinDots	->value();
	d->MaxDots	=ui->EditMaxDots	->value();
	d->LimitSize=ui->EditLimitSize	->value();
	/*
	data.SpaceToOutline		=ui->EditSpaceToOutline	->value();
	data.NoiseSize			=ui->EditNoiseSize		->value();
	data.NoiseSizePinHole	=ui->EditNoiseSizePinHole->value();
	data.Priority			=ui->EditPriority		->value();
	*/
}

void PropertyThinMetalForm::on_toolButtonLibrary_clicked()
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

void PropertyThinMetalForm::on_toolButtonCreateArea_clicked()
{
	if(ui->toolButtonCreateArea->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_CreateThinMetal;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		ShowThinMetalInfoList();
	}
	GetLayersBase()->SetStatusModes(this,/**/"ThinMetalMode");
	BroadcastShowInEdit();
}

void PropertyThinMetalForm::on_pushButtonEditLibFolder_clicked()
{
	ThinMetalBase	*BBase=GetThinMetalBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyThinMetalForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void PropertyThinMetalForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
	int	r=index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());
		CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(PropertyThinMetalForm_LS,LID_0)/*"Library error"*/
									, LangSolver.GetString(PropertyThinMetalForm_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyThinMetalForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ThinMetalImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}

void PropertyThinMetalForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyThinMetalForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index)
{
	int	r=index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL
										, LangSolver.GetString(PropertyThinMetalForm_LS,LID_2)/*"Library error"*/
										, LangSolver.GetString(PropertyThinMetalForm_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyThinMetalForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
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

void	PropertyThinMetalForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		CmdCreateTempThinMetalLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());
			CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
			ThinMetalLibrary	*ALib=dynamic_cast<ThinMetalLibrary *>(SLib->GetLibrary());
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
void PropertyThinMetalForm::on_pushButtonSetFrom_clicked()
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

void PropertyThinMetalForm::on_pushButtonGetBack_clicked()
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

void PropertyThinMetalForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyThinMetalForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyThinMetalForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(LLib!=NULL){
		CmdLoadThinMetalLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		ThinMetalBase	*BBase=GetThinMetalBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
			}
		}
	}
}

void PropertyThinMetalForm::on_ButtonLibSave_clicked()
{
	if(LLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
																, LangSolver.GetString(PropertyThinMetalForm_LS,LID_4)/*"Warning"*/
																, LangSolver.GetString(PropertyThinMetalForm_LS,LID_5)/*"No Library Name"*/
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateThinMetalLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==LLib->GetLibID()){
			a->SetLibName(LLib->GetLibName());
		}
	}
	ShowLibList();
	ShowSelectedLibList();
}


void PropertyThinMetalForm::ShowThinMetalInfoList(void)
{
	ThinMetalInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqThinMetalInfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendThinMetalInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(ThinMetalInfoList *a=CmdSend.ThinMetalInfos.GetFirst();a!=NULL;a=a->GetNext()){
			ThinMetalInfoList *b=new ThinMetalInfoList();
			*b=*a;
			ThinMetalInfos.AppendList(b);
		}
	}
	int	N=ThinMetalInfos.GetNumber();
	ui->tableWidgetItems->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(ThinMetalInfoList *a=ThinMetalInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->LibID);
		LibIDList.AppendList(k);
	}
	ThinMetalBase	*BBase=GetThinMetalBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(ThinMetalInfoList *a=ThinMetalInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QString	LibName;
		for(AlgorithmLibraryList *m=LibIDList.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetLibID()==a->LibID){
				LibName=m->GetLibName();
				break;
			}
		}
		::SetDataToTable(ui->tableWidgetItems ,0 ,row ,QString::number(a->GlobalPage));
		::SetDataToTable(ui->tableWidgetItems ,1 ,row ,QString::number(a->Layer));
		::SetDataToTable(ui->tableWidgetItems ,2 ,row ,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidgetItems ,3 ,row ,LibName);
	}
}

void	PropertyThinMetalForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void	PropertyThinMetalForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	ThinMetalBase	*BBase=GetThinMetalBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}
void PropertyThinMetalForm::on_tableWidgetItems_clicked(const QModelIndex &MIndex)
{
	ThinMetalInfoList *L=ThinMetalInfos.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->GlobalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ThinMetalImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->GlobalPage,L->Layer,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyThinMetalForm::on_tableWidgetItems_doubleClicked(const QModelIndex &MIndex)
{
	ThinMetalInfoList *L=ThinMetalInfos.GetItem(MIndex.row());
	if(L==NULL)
		return;

	if(ShowSampleFormInst!=NULL)
		delete	ShowSampleFormInst;
	ShowSampleFormInst=new ShowSampleForm(L,GetLayersBase());
	ShowSampleFormInst->show();
}
