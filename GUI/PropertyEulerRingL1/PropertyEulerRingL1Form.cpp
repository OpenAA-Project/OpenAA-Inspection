#include "PropertyEulerRingL1Resource.h"
#include "PropertyEulerRingL1Form.h"
#include "ui_PropertyEulerRingL1Form.h"
#include "XEulerRingL1.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "EditEulerRingL1LibraryDialog.h"
#include "XGeneralFunc.h"
#include "XPropertyEulerRingL1Packet.h"
#include "CreateManualEulerRingL1Dialog.h"
#include "EulerRingL1PickupDialog.h"
#include "XPropertyEulerRingL1Common.h"
#include "SelectEulerRingL1LibraryForm.h"
#include "XDataInLayerToDisplayImage.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyEulerRingL1Form::PropertyEulerRingL1Form(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyEulerRingL1Form)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempEulerRingL1LibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui->toolButtonLibrary->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);

	TabBarBlockOnMouse.setParent(ui->frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui->frame->geometry().left(),ui->frame->geometry().top()-30,ui->frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].EulerRingL1InfoOnMouse=NULL;
	}

	ui->tableWidgetBlockInfo->setColumnCount(3+GetLayerNumb(0));
	ui->tableWidgetBlockInfo->setColumnWidth (0, 30);
	ui->tableWidgetBlockInfo->setColumnWidth (1, 100);
	ui->tableWidgetBlockInfo->setColumnWidth (2, 60);
	QStringList	HeaderLabel;
	HeaderLabel.append(QString(/**/"ID"));
	HeaderLabel.append(LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_10)/*"Lib name"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_11)/*"Amount"*/);
	for(int layer=0;layer<GetLayerNumb(0);layer++){
		ui->tableWidgetBlockInfo->setColumnWidth (3+layer, 50);
		HeaderLabel.append(GetParamGlobal()->GetLayerName(layer));
	}
	ui->tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TabBarBlockOnMouse.setParent(ui->frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui->frame->geometry().left(),ui->frame->geometry().top()-30,ui->frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyEulerRingL1Form::~PropertyEulerRingL1Form()
{
    delete ui;
}

EulerRingL1Base	*PropertyEulerRingL1Form::GetEulerRingL1Base(void)
{
	return (EulerRingL1Base *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRingL1");
}

void PropertyEulerRingL1Form::on_toolButtonLibrary_clicked()
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

void PropertyEulerRingL1Form::on_toolButtonCreateBlock_clicked()
{
	if(ui->toolButtonCreateBlock->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqSetButtonMode	RCmd(GetLayersBase() ,sRoot,sName ,GlobalPage);
				RCmd.Mode=GUICmdReqSetButtonMode::_CreateBlock;
				RCmd.InstForm=GetName();
				RCmd.Send(NULL,GlobalPage,0);
			}
		}
		ShowBlockInfoList();
	}
	GetLayersBase()->SetStatusModes(this,/**/"BlockMode");
	BroadcastShowInEdit();
}

void PropertyEulerRingL1Form::on_pushButtonEditLibFolder_clicked()
{
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyEulerRingL1Form::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyEulerRingL1Form::BuildForShow(void)
{
}

void	PropertyEulerRingL1Form::ShowInEdit	(void)
{
	ShowLibList();
}
void	PropertyEulerRingL1Form::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	if(BBase!=NULL){
		CmdGetEulerRingL1LibraryListPacket	Packet(GetLayersBase());
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
};

void	PropertyEulerRingL1Form::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	if(BBase!=NULL){
		CmdCreateTempEulerRingL1LibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadEulerRingL1LibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
			BBase->TransmitDirectly(&Packet);
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

	int	row=0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui->tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui->tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void PropertyEulerRingL1Form::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadEulerRingL1LibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}
void PropertyEulerRingL1Form::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"EulerRingL1ImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyEulerRingL1Form::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyEulerRingL1Form::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadEulerRingL1LibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyEulerRingL1Form::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyEulerRingL1Form::on_pushButtonSetFrom_clicked()
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

void PropertyEulerRingL1Form::on_pushButtonGetBack_clicked()
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

void PropertyEulerRingL1Form::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyEulerRingL1Form::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}
void	PropertyEulerRingL1Form::TransmitDirectly(GUIDirectMessage *packet)
{
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	/*
	GUICmdReqEulerRingL1DrawMode	*GUICmdReqEulerRingL1DrawModeVar=dynamic_cast<GUICmdReqEulerRingL1DrawMode *>(packet);
	if(GUICmdReqEulerRingL1DrawModeVar!=NULL){
		if(ui->radioButtonPickupArea->isChecked()==true)
			GUICmdReqEulerRingL1DrawModeVar->DrawingArea=EulerRingL1DrawAttr::_Pickup;
		if(ui->radioButtonBlock->isChecked()==true)
			GUICmdReqEulerRingL1DrawModeVar->DrawingArea=EulerRingL1DrawAttr::_Block;
		if(ui->radioButtonCalc->isChecked()==true)
			GUICmdReqEulerRingL1DrawModeVar->DrawingArea=EulerRingL1DrawAttr::_Calc;
		if(ui->radioButtonMatching->isChecked()==true)
			GUICmdReqEulerRingL1DrawModeVar->DrawingArea=EulerRingL1DrawAttr::_Matching;
		return;
	}
	*/
	CmdEulerRingL1DrawModePacket	*CmdEulerRingL1DrawModePacketVar=dynamic_cast<CmdEulerRingL1DrawModePacket *>(packet);
	if(CmdEulerRingL1DrawModePacketVar!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true)
			CmdEulerRingL1DrawModePacketVar->Mode=EulerRingL1DrawAttr::_LibTest;
		else if(ui->toolButtonCreateBlock->isChecked()==true)
			CmdEulerRingL1DrawModePacketVar->Mode=EulerRingL1DrawAttr::_CreatedBlock;
		return;
	}

	CmdEulerRingL1DrawEnd	*BlockDEnd=dynamic_cast<CmdEulerRingL1DrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(TempLib->GetLibrary());
				EulerRingL1PickupDialog	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint
										  ,ALib->PickupL,ALib->PickupH,this);
				D.Reflect(ALib->PickupL,ALib->PickupH);
				if(D.exec()==(int)true){
					ALib->PickupL	=D.PickupL;
					ALib->PickupH	=D.PickupH;
				}
			}
		}
		else if(ui->toolButtonCreateBlock->isChecked()==true){
			CreateManualEulerRingL1Dialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual EulerRingL1");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualEulerRingL1	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						CmdCreateByteArrayFromEulerRingL1ItemPacket	BCmd(GetLayersBase());
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowBlockInfoList();
			}
		}
		return;
	}
	CmdReqSetButtonMode	*CmdReqSetButtonModeVar=dynamic_cast<CmdReqSetButtonMode *>(packet);
	if(CmdReqSetButtonModeVar!=NULL){
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_LibraryTest){
			ui->toolButtonLibrary->setChecked(true);
		}
		if(CmdReqSetButtonModeVar->Mode==GUICmdReqSetButtonMode::_CreateBlock){
			ui->toolButtonCreateBlock->setChecked(true);
		}
	}
	CmdExecuteMouseLDown	*CmdExecuteMouseLDownVar=dynamic_cast<CmdExecuteMouseLDown *>(packet);
	if(CmdExecuteMouseLDownVar!=NULL){
		for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
			//if(BInfo[i].BlockInfoOnMouse!=NULL)
			//	delete	BInfo[i].BlockInfoOnMouse;
			BInfo[i].EulerRingL1InfoOnMouse=NULL;
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
					GUICmdReqEulerRingL1FromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckEulerRingL1FromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.EulerRingL1InfoOnMouse)/sizeof(AckCmd.EulerRingL1InfoOnMouse[0]);i++){
						if(AckCmd.EulerRingL1InfoOnMouse[i]!=NULL){
							BInfo[N].EulerRingL1InfoOnMouse=AckCmd.EulerRingL1InfoOnMouse[i];
							AckCmd.EulerRingL1InfoOnMouse[i]=NULL;
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
	CmdSelectEulerRingL1LibraryDialog	*CmdSelectEulerRingL1LibraryDialogVar=dynamic_cast<CmdSelectEulerRingL1LibraryDialog *>(packet);
	if(CmdSelectEulerRingL1LibraryDialogVar!=NULL){
		SelectEulerRingL1LibraryForm	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectEulerRingL1LibraryDialogVar->LibID=D.SelectedLibID;
		}
		return;
	}
	CmdRemoveAllOriginalEulerRingL1Items	*CmdRemoveAllOriginalEulerRingL1ItemsVar=dynamic_cast<CmdRemoveAllOriginalEulerRingL1Items *>(packet);
	if(CmdRemoveAllOriginalEulerRingL1ItemsVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRemoveAllOriginal	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.GeneratedOrigin	=CmdRemoveAllOriginalEulerRingL1ItemsVar->GeneratedOrigin;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	ChangeEulerRingL1sThresholdCommon	*ChangeEulerRingL1sThresholdCommonVar=dynamic_cast<ChangeEulerRingL1sThresholdCommon *>(packet);
	if(ChangeEulerRingL1sThresholdCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeEulerRingL1sThreshold	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.BlockLibID	=ChangeEulerRingL1sThresholdCommonVar->BlockLibID;
			Cmd.InfosData	=ChangeEulerRingL1sThresholdCommonVar->InfosData;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
}

void	PropertyEulerRingL1Form::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].EulerRingL1InfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString::number(BInfo[i].Page)
										+QString(/**/"-")
										+GetParamGlobal()->GetLayerName(BInfo[i].Layer));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void PropertyEulerRingL1Form::on_pushButtonEditLibrary_clicked()
{
	EditEulerRingL1LibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyEulerRingL1Form::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_12)/*"Pickup Test"*/);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"EulerRingL1ImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LayerList=LayerList;
		Cmd.LibPoint	=TempLib;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyEulerRingL1Form::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyEulerRingL1Form::on_ButtonGenerateLibs_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"EulerRingL1ImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_13)/*"Generating items"*/,GetLayersBase()->GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateEulerRingL1s	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibList	=SelectedLibList;
		RCmd.LayerList	=LayerList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyEulerRingL1Form::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
										, LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_8)/*"Warning"*/
										, LangSolver.GetString(PropertyEulerRingL1Form_LS,LID_9)/*"No Library Name"*/
										, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateEulerRingL1LibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
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

void PropertyEulerRingL1Form::on_tableWidgetBlockInfo_cellClicked(int row, int column)
{
	EulerRingL1Base	*BBase=GetEulerRingL1Base();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"EulerRingL1";
		Cmd.SendOnly(GlobalPage,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,GlobalPage);
		for(int row=0;row<ui->tableWidgetBlockInfo->rowCount();row++){
			EulerRingL1InfoList *a=EulerRingL1Infos.GetItem(row);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				int	c=layer+3;
				QTableWidgetItem *item=ui->tableWidgetBlockInfo->item(row,c);
				if(item==NULL)
					continue;
				if(item->isSelected()==true){
					SelectLibList	*v=new SelectLibList();
					v->LibType	=BBase->GetLibType();
					v->LibID	=a->LibID;
					v->Layer=layer;
					Cmd.SelectedList.AppendList(v);
				}
			}
		}
		Cmd.SendOnly(GlobalPage,1);
	}
	BroadcastShowInEdit();
}

void	PropertyEulerRingL1Form::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(data.GetLibrary());
	ui->EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui->EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui->EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui->EditMaxBlockSize		->setValue(ALib->MaxBlockSize);

	ui->EditSpaceToOutline		->setValue(ALib->SpaceToOutline);
	ui->EditOutlineGeneration	->setValue(ALib->OutlineGeneration);
	ui->EditNoiseSize			->setValue(ALib->NoiseSize);
	ui->EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui->EditPriority			->setValue(ALib->Priority);
	ui->EditExpandedDotToPad	->setValue(ALib->ExpandedDotToPad);
}

void	PropertyEulerRingL1Form::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	EulerRingL1Library	*ALib=dynamic_cast<EulerRingL1Library *>(data.GetLibrary());
	ALib->MinBlockDots		=ui->EditMinBlockDots		->value();
	ALib->MaxBlockDots		=ui->EditMaxBlockDots		->value();
	ALib->MinBlockSize		=ui->EditMinBlockSize		->value();
	ALib->MaxBlockSize		=ui->EditMaxBlockSize		->value();

	ALib->SpaceToOutline	=ui->EditSpaceToOutline		->value();
	ALib->OutlineGeneration	=ui->EditOutlineGeneration	->value();
	ALib->NoiseSize			=ui->EditNoiseSize			->value();
	ALib->NoiseSizePinHole	=ui->EditNoiseSizePinHole	->value();
	ALib->Priority			=ui->EditPriority			->value();
	ALib->ExpandedDotToPad	=ui->EditExpandedDotToPad	->value();
}

void PropertyEulerRingL1Form::ShowBlockInfoList(void)
{
	EulerRingL1Infos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqEulerRingL1InfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendEulerRingL1InfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(EulerRingL1InfoList *a=CmdSend.EulerRingL1Infos.GetFirst();a!=NULL;a=a->GetNext()){
			EulerRingL1InfoList *b;
			for(b=EulerRingL1Infos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						IntClass	*d=b->EulerRingL1Count.GetItem(layer);
						IntClass	*s=a->EulerRingL1Count.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new EulerRingL1InfoList();
				b->LibID=a->LibID;
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					IntClass	*s=a->EulerRingL1Count.GetItem(layer);
					if(s!=NULL){
						b->EulerRingL1Count.Add(s->GetValue());
					}
					else{
						b->EulerRingL1Count.Add(0);
					}
				}
				EulerRingL1Infos.AppendList(b);
			}
		}
	}
	int	N=EulerRingL1Infos.GetNumber();
	ui->tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(EulerRingL1InfoList *a=EulerRingL1Infos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	EulerRingL1Base	*BBase=GetEulerRingL1Base();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(EulerRingL1InfoList *a=EulerRingL1Infos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QString	LibName;
		for(AlgorithmLibraryList *m=LibIDList.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetLibID()==a->GetLibID()){
				LibName=m->GetLibName();
				break;
			}
		}
		QTableWidgetItem *W;
		W=ui->tableWidgetBlockInfo->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->LibID));

		W=ui->tableWidgetBlockInfo->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		W->setText(LibName);

		W=ui->tableWidgetBlockInfo->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetBlockInfo->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsEnabled);
		}
		int	TotalCount=0;
		for(IntClass *h=a->EulerRingL1Count.GetFirst();h!=NULL;h=h->GetNext()){
			TotalCount+=h->GetValue();
		}
		W->setText(QString::number(TotalCount));

		for(int layer=0;layer<GetLayerNumb(0);layer++){
			W=ui->tableWidgetBlockInfo->item ( row, 3+layer);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetBlockInfo->setItem ( row, 3+layer,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			IntClass *h=a->EulerRingL1Count.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}


void	PropertyEulerRingL1Form::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].EulerRingL1InfoOnMouse!=NULL){
		ui->EditLibIDInBlock			->setText(QString::number(BInfo[index].EulerRingL1InfoOnMouse->GetLibID()));
		EulerRingL1Base	*BBase=GetEulerRingL1Base();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].EulerRingL1InfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui->EditLibNameInBlock			->setText(Cmd.LibName);

		ui->EditDarkWidth				->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->DarkWidth);
		ui->EditLightWidth				->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->LightWidth);
		ui->EditConnectLen				->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->ConnectLen);
		ui->EditMinHoleDiameter			->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->MinHoleDiameter);
		ui->EditMaxHoleDiameter			->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->MaxHoleDiameter);
		ui->EditMaxShiftHole			->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->MaxShiftHole);

		ui->checkModeEnabled			->setChecked(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->PointMove.ModeEnabled);
		ui->checkModeDynamicMask		->setChecked(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->PointMove.ModeMakeDynamicMask);
		ui->checkModeEnableHoleCheck	->setChecked(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->PointMove.ModeEnableHoleCheck);

		ui->EditAdjustBlack				->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->AdjustBlack);
		ui->EditAdjustWhite				->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->AdjustWhite);
		ui->EditExpandForDynamicMask	->setValue(BInfo[index].EulerRingL1InfoOnMouse->GetThresholdR()->ExpandForDynamicMask);
	}
	else{
		ui->EditDarkWidth				->clear();
		ui->EditLightWidth				->clear();
		ui->EditConnectLen				->clear();
		ui->EditMinHoleDiameter			->clear();
		ui->EditMaxHoleDiameter			->clear();
		ui->EditMaxShiftHole			->clear();

		ui->checkModeEnabled			->setChecked(false);
		ui->checkModeDynamicMask		->setChecked(false);
		ui->checkModeEnableHoleCheck	->setChecked(false);
;
		ui->EditAdjustBlack				->clear();
		ui->EditAdjustWhite				->clear();
		ui->EditExpandForDynamicMask	->clear();
	}
}