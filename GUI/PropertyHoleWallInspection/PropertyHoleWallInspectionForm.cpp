#include "PropertyHoleWallInspectionForm.h"
#include "ui_PropertyHoleWallInspectionForm.h"
#include "XHoleWallInspection.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "EditHoleWallInspectionDialog.h"
#include "XGeneralFunc.h"
#include "XPropertyHoleWallPacket.h"
#include "XPropertyHoleWallCommon.h"
#include "SelectHoleWallLibraryForm.h"
#include "XGUIPacketGeneral.h"
#include "XAlgorithmLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyHoleWallInspectionForm::PropertyHoleWallInspectionForm(LayersBase *Base,QWidget *parent) :
     GUIFormBase(Base,parent),
    ui(new Ui::PropertyHoleWallInspectionForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	HoleWallBase	*BBase=GetHoleWallBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempHoleWallLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	ui->toolButtonLibrary->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);

	TabBarBlockOnMouse.setParent(ui->frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui->frame->geometry().left(),ui->frame->geometry().top()-30,ui->frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].HoleWallInfoOnMouse=NULL;
	}

	ui->tableWidgetBlockInfo->setColumnCount(3+GetLayerNumb(0));
	ui->tableWidgetBlockInfo->setColumnWidth (0, 30);
	ui->tableWidgetBlockInfo->setColumnWidth (1, 100);
	ui->tableWidgetBlockInfo->setColumnWidth (2, 60);
	QStringList	HeaderLabel;
	HeaderLabel.append(QString(/**/"ID"));
	HeaderLabel.append("Lib name");
	HeaderLabel.append("Amount");
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

PropertyHoleWallInspectionForm::~PropertyHoleWallInspectionForm()
{
    delete ui;
}

HoleWallBase	*PropertyHoleWallInspectionForm::GetHoleWallBase(void)
{
	return (HoleWallBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HoleWall");
}

void PropertyHoleWallInspectionForm::on_toolButtonLibrary_clicked()
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

void PropertyHoleWallInspectionForm::on_toolButtonCreateBlock_clicked()
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

void PropertyHoleWallInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	HoleWallBase	*BBase=GetHoleWallBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyHoleWallInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyHoleWallInspectionForm::BuildForShow(void)
{
}

void	PropertyHoleWallInspectionForm::ShowInEdit	(void)
{
	ShowLibList();
}
void	PropertyHoleWallInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	HoleWallBase	*BBase=GetHoleWallBase();
	if(BBase!=NULL){
		CmdGetHoleWallLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyHoleWallInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	HoleWallBase	*BBase=GetHoleWallBase();
	if(BBase!=NULL){
		CmdCreateTempHoleWallLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadHoleWallLibraryPacket	Packet(GetLayersBase());
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

void PropertyHoleWallInspectionForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());
		CmdLoadHoleWallLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}
void PropertyHoleWallInspectionForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"HoleWallImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyHoleWallInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyHoleWallInspectionForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadHoleWallLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		HoleWallBase	*BBase=GetHoleWallBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyHoleWallInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyHoleWallInspectionForm::on_pushButtonSetFrom_clicked()
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

void PropertyHoleWallInspectionForm::on_pushButtonGetBack_clicked()
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

void PropertyHoleWallInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyHoleWallInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void	PropertyHoleWallInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	HoleWallBase	*BBase=GetHoleWallBase();
	/*
	GUICmdReqHoleWallDrawMode	*GUICmdReqHoleWallDrawModeVar=dynamic_cast<GUICmdReqHoleWallDrawMode *>(packet);
	if(GUICmdReqHoleWallDrawModeVar!=NULL){
		if(ui->radioButtonPickupArea->isChecked()==true)
			GUICmdReqHoleWallDrawModeVar->DrawingArea=HoleWallDrawAttr::_Pickup;
		if(ui->radioButtonBlock->isChecked()==true)
			GUICmdReqHoleWallDrawModeVar->DrawingArea=HoleWallDrawAttr::_Block;
		if(ui->radioButtonCalc->isChecked()==true)
			GUICmdReqHoleWallDrawModeVar->DrawingArea=HoleWallDrawAttr::_Calc;
		if(ui->radioButtonMatching->isChecked()==true)
			GUICmdReqHoleWallDrawModeVar->DrawingArea=HoleWallDrawAttr::_Matching;
		return;
	}
	*/
	CmdHoleWallDrawModePacket	*CmdHoleWallDrawModePacketVar=dynamic_cast<CmdHoleWallDrawModePacket *>(packet);
	if(CmdHoleWallDrawModePacketVar!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true)
			CmdHoleWallDrawModePacketVar->Mode=HoleWallDrawAttr::_LibTest;
		else if(ui->toolButtonCreateBlock->isChecked()==true)
			CmdHoleWallDrawModePacketVar->Mode=HoleWallDrawAttr::_CreatedBlock;
		return;
	}

	CmdHoleWallDrawEnd	*BlockDEnd=dynamic_cast<CmdHoleWallDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui->toolButtonLibrary->isChecked()==true){
			if(LLib->GetLibID()>=0){
			}
		}
		else if(ui->toolButtonCreateBlock->isChecked()==true){
			//CreateManualHoleWallDialog	D(GetLayersBase(),NULL);
			//if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual HoleWall");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualHoleWall	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						CmdCreateByteArrayFromHoleWallItemPacket	BCmd(GetLayersBase());
						//BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowBlockInfoList();
			//}
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
			BInfo[i].HoleWallInfoOnMouse=NULL;
		}
		int	N=0;
		for(IntClass *p=CmdExecuteMouseLDownVar->PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int page=p->GetValue();
			for(int layer=0;layer<GetLayerNumb(0);layer++){
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
					GUICmdReqHoleWallFromList	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckHoleWallFromList	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					ReqCmd.CurrentItem=Items;
					ReqCmd.Send(GlobalPage,0,AckCmd);
					for(int i=0;i<sizeof(AckCmd.HoleWallInfoOnMouse)/sizeof(AckCmd.HoleWallInfoOnMouse[0]);i++){
						if(AckCmd.HoleWallInfoOnMouse[i]!=NULL){
							BInfo[N].HoleWallInfoOnMouse=AckCmd.HoleWallInfoOnMouse[i];
							AckCmd.HoleWallInfoOnMouse[i]=NULL;
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
	CmdSelectHoleWallLibraryDialog	*CmdSelectHoleWallLibraryDialogVar=dynamic_cast<CmdSelectHoleWallLibraryDialog *>(packet);
	if(CmdSelectHoleWallLibraryDialogVar!=NULL){
		SelectHoleWallLibraryForm	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectHoleWallLibraryDialogVar->LibID=D.SelectedLibID;
		}
		return;
	}
	CmdRemoveAllOriginalHoleWallItems	*CmdRemoveAllOriginalHoleWallItemsVar=dynamic_cast<CmdRemoveAllOriginalHoleWallItems *>(packet);
	if(CmdRemoveAllOriginalHoleWallItemsVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRemoveAllOriginal	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.GeneratedOrigin	=CmdRemoveAllOriginalHoleWallItemsVar->GeneratedOrigin;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	ChangeHoleWallsThresholdCommon	*ChangeHoleWallsThresholdCommonVar=dynamic_cast<ChangeHoleWallsThresholdCommon *>(packet);
	if(ChangeHoleWallsThresholdCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeHoleWallsThreshold	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.BlockLibID	=ChangeHoleWallsThresholdCommonVar->BlockLibID;
			Cmd.InfosData	=ChangeHoleWallsThresholdCommonVar->InfosData;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
}

void	PropertyHoleWallInspectionForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].HoleWallInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString::number(BInfo[i].Page)
										+QString(/**/"-")
										+GetParamGlobal()->GetLayerName(BInfo[i].Layer));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void PropertyHoleWallInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditHoleWallInspectionDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyHoleWallInspectionForm::on_ButtonPickupTest_clicked()
{
	if(LLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm("Pickup Test");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"HoleWallImagePanel" ,/**/"");
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
		Cmd.LibPoint	=LLib;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyHoleWallInspectionForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyHoleWallInspectionForm::on_ButtonGenerateLibs_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"HoleWallImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items",GetLayersBase()->GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateHoleWalls	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.LibList	=SelectedLibList;
		RCmd.LayerList	=LayerList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyHoleWallInspectionForm::on_ButtonLibSave_clicked()
{
	if(LLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
										, "Warning"
										, "No Library Name"
										, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateHoleWallLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	HoleWallBase	*BBase=GetHoleWallBase();
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

void PropertyHoleWallInspectionForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &index)
{
	HoleWallBase	*BBase=GetHoleWallBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"HoleWall";
		Cmd.SendOnly(GlobalPage,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,GlobalPage);
		for(int row=0;row<ui->tableWidgetBlockInfo->rowCount();row++){
			HoleWallInfoList *a=HoleWallInfos.GetItem(row);
			for(int layer=0;layer<GetLayerNumb(0);layer++){
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

void	PropertyHoleWallInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	HoleWallLibrary	*d=dynamic_cast<HoleWallLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditMinBlockDots	->setValue(d->MinBlockDots);
	ui->EditMaxBlockDots	->setValue(d->MaxBlockDots);
	ui->EditMinBlockSize	->setValue(d->MinBlockSize);
	ui->EditMaxBlockSize	->setValue(d->MaxBlockSize);

	ui->EditNoiseSize		->setValue(d->NoiseSize);
	ui->EditNoiseSizePinHole->setValue(d->NoiseSizePinHole);
}

void	PropertyHoleWallInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	HoleWallLibrary	*d=dynamic_cast<HoleWallLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->MinBlockDots		=ui->EditMinBlockDots		->value();
	d->MaxBlockDots		=ui->EditMaxBlockDots		->value();
	d->MinBlockSize		=ui->EditMinBlockSize		->value();
	d->MaxBlockSize		=ui->EditMaxBlockSize		->value();

	d->NoiseSize		=ui->EditNoiseSize			->value();
	d->NoiseSizePinHole	=ui->EditNoiseSizePinHole	->value();
}

void PropertyHoleWallInspectionForm::ShowBlockInfoList(void)
{
	HoleWallInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqHoleWallInfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendHoleWallInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(HoleWallInfoList *a=CmdSend.HoleWallInfos.GetFirst();a!=NULL;a=a->GetNext()){
			HoleWallInfoList *b;
			for(b=HoleWallInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					for(int layer=0;layer<GetLayerNumb(0);layer++){
						IntClass	*d=b->HoleWallCount.GetItem(layer);
						IntClass	*s=a->HoleWallCount.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new HoleWallInfoList();
				b->LibID=a->LibID;
				for(int layer=0;layer<GetLayerNumb(0);layer++){
					IntClass	*s=a->HoleWallCount.GetItem(layer);
					if(s!=NULL){
						b->HoleWallCount.Add(s->GetValue());
					}
					else{
						b->HoleWallCount.Add(0);
					}
				}
				HoleWallInfos.AppendList(b);
			}
		}
	}
	int	N=HoleWallInfos.GetNumber();
	ui->tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(HoleWallInfoList *a=HoleWallInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	HoleWallBase	*BBase=GetHoleWallBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(HoleWallInfoList *a=HoleWallInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		for(IntClass *h=a->HoleWallCount.GetFirst();h!=NULL;h=h->GetNext()){
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
			IntClass *h=a->HoleWallCount.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}


void	PropertyHoleWallInspectionForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].HoleWallInfoOnMouse!=NULL){
		ui->EditLibIDInBlock			->setText(QString::number(BInfo[index].HoleWallInfoOnMouse->GetLibID()));
		HoleWallBase	*BBase=GetHoleWallBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].HoleWallInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui->EditLibNameInBlock			->setText(Cmd.LibName);

		ui->EditSearchDot			->setValue(BInfo[index].HoleWallInfoOnMouse->GetThresholdR()->SearchDot	);
		ui->EditNGSize				->setValue(BInfo[index].HoleWallInfoOnMouse->GetThresholdR()->NGSize	);
	}
	else{
		ui->EditSearchDot			->clear();
		ui->EditNGSize				->clear();

	}
}
void PropertyHoleWallInspectionForm::on_pushButtonMakeBitBuff_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeBitBuff	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(NULL,GlobalPage,0);
	}
}
