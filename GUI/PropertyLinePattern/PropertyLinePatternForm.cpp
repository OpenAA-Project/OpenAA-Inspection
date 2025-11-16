#include "PropertyLinePatternFormResource.h"
#include "PropertyLinePatternForm.h"
#include "ui_PropertyLinePatternForm.h"
#include "EditLibraryDialog.h"
#include "SelectLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XLinePatternPacket.h"
#include "XPropertyLinePatternCommon.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyLinePatternForm::PropertyLinePatternForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyLinePatternForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LinePatternBase	*BBase=GetLinePatternBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	
	int	tPage=0;
	ui->tableWidgetBlockInfo->setColumnCount(3+GetLayerNumb(tPage));
	ui->tableWidgetBlockInfo->setColumnWidth (0, 30);
	ui->tableWidgetBlockInfo->setColumnWidth (1, 100);
	ui->tableWidgetBlockInfo->setColumnWidth (2, 60);
	QStringList	HeaderLabel;
	HeaderLabel.append(LangSolver.GetString(PropertyLinePatternForm_LS,LID_0)/*"ID"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyLinePatternForm_LS,LID_1)/*"Library"*/);
	HeaderLabel.append(LangSolver.GetString(PropertyLinePatternForm_LS,LID_2)/*"Count"*/);
	for(int layer=0;layer<GetLayerNumb(tPage);layer++){
		ui->tableWidgetBlockInfo->setColumnWidth (3+layer, 50);
		HeaderLabel.append(GetParamGlobal()->GetLayerName(layer));
	}
	ui->tableWidgetBlockInfo->setHorizontalHeaderLabels(HeaderLabel);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLinePatternLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}

	TabBarBlockOnMouse.setParent(ui->frameBlockInfoOnMouse);
	TabBarBlockOnMouse.setGeometry(ui->frame->geometry().left(),ui->frame->geometry().top()-30,ui->frame->geometry().width(),30);
	connect(&TabBarBlockOnMouse,SIGNAL(currentChanged(int)),this,SLOT(TabBarBlockOnMouseChanged(int)));

	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		BInfo[i].BlockInfoOnMouse=NULL;
	}

	if(TempLib!=NULL){
		TempLib->SetLibID(-1);
	}
	if(ui->toolButtonLibrary->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(0);
	}
	if(ui->toolButtonCreateBlock->isChecked()==true){
		ui->stackedWidget->setCurrentIndex(1);
		ShowBlockInfoList();
	}

	LibSortType	=KOS_ID_Up;
	connect(ui->tableWidgetLibList->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyLinePatternForm::~PropertyLinePatternForm()
{
    delete ui;
	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}
LinePatternBase	*PropertyLinePatternForm::GetLinePatternBase(void)
{
	return (LinePatternBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LinePattern");
}
void	PropertyLinePatternForm::MListSectionClicked ( int logicalIndex )
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


void	PropertyLinePatternForm::ShowTab(void)
{
	int	r=TabBarBlockOnMouse.currentIndex();
	while(TabBarBlockOnMouse.count()!=0){
		TabBarBlockOnMouse.removeTab(0);
	}
	for(int i=0;i<sizeof(BInfo)/sizeof(BInfo[0]);i++){
		if(BInfo[i].BlockInfoOnMouse!=NULL){
			TabBarBlockOnMouse.addTab (QString::number(BInfo[i].Page)
										+LangSolver.GetString(PropertyLinePatternForm_LS,LID_3)/*"-"*/
										+GetParamGlobal()->GetLayerName(BInfo[i].Layer));
		}
	}
	if(0<=r && TabBarBlockOnMouse.count()>r){
		TabBarBlockOnMouse.setCurrentIndex(r);
	}
}

void	PropertyLinePatternForm::TabBarBlockOnMouseChanged(int index)
{
	if(index>=0 && BInfo[index].BlockInfoOnMouse!=NULL){
		ui->EditLibIDnBlock		->setText(QString::number(BInfo[index].BlockInfoOnMouse->GetLibID()));
		LinePatternBase	*BBase=GetLinePatternBase();
		CmdGetLibName	Cmd(GetLayersBase());
		Cmd.LibID	=BInfo[index].BlockInfoOnMouse->GetLibID();
		BBase->TransmitDirectly(&Cmd);
		ui->EditLibNameInBlock	->setText(Cmd.LibName);

		ui->EditBrightWidthIL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.BrightWidthIL);
		ui->EditBrightWidthIH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.BrightWidthIH);
		ui->EditBrightWidthOL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.BrightWidthOL);
		ui->EditBrightWidthOH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.BrightWidthOH);
		ui->EditNGSizeIL		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.NGSizeIL);
		ui->EditNGSizeIH		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.NGSizeIH);
		ui->EditNGSizeOL		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.NGSizeOL);
		ui->EditNGSizeOH		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.NGSizeOH);
		ui->checkBModeEnabled				->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.PointMove.ModeEnabled);
		ui->checkBModeAbsoluteBright		->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.PointMove.ModeAbsoluteBright);
		ui->checkBModeCenterBrightFromParts	->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.PointMove.ModeCenterBrightFromParts);
		ui->checkBModeDynamicMask			->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.PointMove.ModeDynamicMask);
		ui->checkBModeUseRegularBrightness	->setChecked(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.PointMove.ModeUseRegularBrightness);
		ui->EditTransitDot		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.TransitDot);
		ui->EditAdjustBrightIL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.AdjustBrightIL);
		ui->EditAdjustBrightIH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.AdjustBrightIH);
		ui->EditAdjustBrightOL	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.AdjustBrightOL);
		ui->EditAdjustBrightOH	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.AdjustBrightOH);
		ui->EditSearchDot		->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.SearchDot);
		ui->EditGlobalSearchDot	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.GlobalSearchDot);
		ui->EditRegulatedColI	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.RegulatedColI);
		ui->EditRegulatedColO	->setValue(BInfo[index].BlockInfoOnMouse->GetThresholdR()->ThreshBag.RegulatedColO);

	}
	else{
		ui->EditBrightWidthIL	->clear();
		ui->EditBrightWidthIH	->clear();
		ui->EditBrightWidthOL	->clear();
		ui->EditBrightWidthOH	->clear();
		ui->EditNGSizeIL		->clear();
		ui->EditNGSizeIH		->clear();
		ui->EditNGSizeOL		->clear();
		ui->EditNGSizeOH		->clear();
		ui->checkBModeEnabled				->setChecked(false);
		ui->checkBModeAbsoluteBright		->setChecked(false);
		ui->checkBModeCenterBrightFromParts	->setChecked(false);
		ui->checkBModeDynamicMask			->setChecked(false);
		ui->checkBModeUseRegularBrightness	->setChecked(false);
		ui->EditTransitDot		->clear();
		ui->EditAdjustBrightIL	->clear();
		ui->EditAdjustBrightIH	->clear();
		ui->EditAdjustBrightOL	->clear();
		ui->EditAdjustBrightOH	->clear();
		ui->EditSearchDot		->clear();
		ui->EditGlobalSearchDot	->clear();
		ui->EditRegulatedColI	->clear();
		ui->EditRegulatedColO	->clear();
	}
}
void	PropertyLinePatternForm::TransmitDirectly(GUIDirectMessage *packet)
{
	LinePatternBase	*BBase=GetLinePatternBase();
	CmdLinePatternDrawPacket	*BDrawModePacket=dynamic_cast<CmdLinePatternDrawPacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonArea->isChecked()==true)
			BDrawModePacket->ModeDrawArea=true;
		else
			BDrawModePacket->ModeDrawArea=false;

		if(ui->toolButtonInside->isChecked()==true)
			BDrawModePacket->ModeDrawInside=true;
		else
			BDrawModePacket->ModeDrawInside=false;

		if(ui->toolButtonOutside->isChecked()==true)
			BDrawModePacket->ModeDrawOutside=true;
		else
			BDrawModePacket->ModeDrawOutside=false;
		BDrawModePacket->ResultAngleNumber	=ui->comboBoxResultAngleNumber->currentIndex();
		return;
	}
	CmdLinePatternDrawEnd	*BlockDEnd=dynamic_cast<CmdLinePatternDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui->toolButtonCreateBlock->isChecked()==true){
			SelectLibraryDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.SelectedID>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Block");
				/*
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						Cmd.LibID=D.SelectedID;
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				*/
			}
		}
		return;
	}
	AddLinePacket	*AddLinePacketVar=dynamic_cast<AddLinePacket *>(packet);
	if(AddLinePacketVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromVector(AddLinePacketVar->Vector,PageList);

		if(ui->toolButtonCreateBlock->isChecked()==true){	
			SelectLibraryDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.SelectedID>=0){
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					VectorLineBase	*v=AddLinePacketVar->Vector->CreateEmpty();
					*v=*AddLinePacketVar->Vector;
					pdata->ClipMoveVectorFromGlobal(v);
					GUICmdSendAddManualLinePattern	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.LayerList	=AddLinePacketVar->LayerList;
					Cmd.Vector=v->CreateDup();
							
					Cmd.SelectedLibID=D.SelectedID;
					Cmd.Send(NULL,page,0);
				}
			}
			ShowBlockInfoList();
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
		return;
	}
	CmdSelectLinePatternLibraryDialog	*CmdSelectLinePatternLibraryDialogVar=dynamic_cast<CmdSelectLinePatternLibraryDialog *>(packet);
	if(CmdSelectLinePatternLibraryDialogVar!=NULL){
		SelectLibraryDialog	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectLinePatternLibraryDialogVar->LibID=D.SelectedID;
		}
		return;
	}
	ChangeLinePatternsThresholdCommon	*ChangeLinePatternsThresholdCommonVar=dynamic_cast<ChangeLinePatternsThresholdCommon *>(packet);
	if(ChangeLinePatternsThresholdCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeLinePatternThreshold	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.LinePatternLibID=ChangeLinePatternsThresholdCommonVar->LinePatternLibID;
			Cmd.InfosData		=ChangeLinePatternsThresholdCommonVar->InfosData;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdRemoveAllOriginalLinePatternItems	*CmdRemoveAllOriginalLinePatternItemsVar=dynamic_cast<CmdRemoveAllOriginalLinePatternItems *>(packet);
	if(CmdRemoveAllOriginalLinePatternItemsVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRemoveAllOriginal	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.GeneratedOrigin	=CmdRemoveAllOriginalLinePatternItemsVar->GeneratedOrigin;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
}

void	PropertyLinePatternForm::BuildForShow(void)
{
}
void	PropertyLinePatternForm::ShowInEdit(void)
{
	ShowBlockInfoList();
}
void	PropertyLinePatternForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
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
void	PropertyLinePatternForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	LinePatternBase	*BBase=GetLinePatternBase();
	if(BBase!=NULL){
		CmdGetLinePatternLibraryListPacket	Packet(GetLayersBase());
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

struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
};

void	PropertyLinePatternForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	LinePatternBase	*BBase=GetLinePatternBase();
	if(BBase!=NULL){
		CmdCreateTempLinePatternLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadLinePatternLibraryPacket	Packet(GetLayersBase());
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
void PropertyLinePatternForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL	, /**/"Warning"
																	, /**/"No Library Name"
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateLinePatternLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LinePatternBase	*BBase=GetLinePatternBase();
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

void PropertyLinePatternForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLinePatternLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyLinePatternForm::ShowBlockInfoList(void)
{
	BlockInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqBlockInfoList	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendBlockInfoList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.Send(GlobalPage,0,CmdSend);

		for(BlockInfoList *a=CmdSend.BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
			BlockInfoList *b;
			for(b=BlockInfos.GetFirst();b!=NULL;b=b->GetNext()){
				if(a->LibID==b->LibID){
					for(int layer=0;layer<GetLayerNumb(page);layer++){
						IntClass	*d=b->BlockCount.GetItem(layer);
						IntClass	*s=a->BlockCount.GetItem(layer);
						d->SetValue(d->GetValue()+s->GetValue());
					}
					break;
				}
			}
			if(b==NULL){
				b=new BlockInfoList();
				b->LibID=a->LibID;
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					IntClass	*s=a->BlockCount.GetItem(layer);
					b->BlockCount.Add(s->GetValue());
				}
				BlockInfos.AppendList(b);
			}
		}
	}
	int	N=BlockInfos.GetNumber();
	ui->tableWidgetBlockInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(BlockInfoList *a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	LinePatternBase	*BBase=GetLinePatternBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(BlockInfoList *a=BlockInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
		for(IntClass *h=a->BlockCount.GetFirst();h!=NULL;h=h->GetNext()){
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
			IntClass *h=a->BlockCount.GetItem(layer);
			W->setText(QString::number(h->GetValue()));
		}
	}
}

void	PropertyLinePatternForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(data.GetLibrary());
	ui->EditLineWidthInPattern	->setValue(ALib->LineWidthInPattern);
	ui->EditLineWidthOutside	->setValue(ALib->LineWidthOutside);
	ui->EditLimitLength			->setValue(ALib->LimitLength);
}

void	PropertyLinePatternForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	LinePatternLibrary	*ALib=dynamic_cast<LinePatternLibrary *>(data.GetLibrary());
	ALib->LineWidthInPattern=ui->EditLineWidthInPattern	->value();
	ALib->LineWidthOutside	=ui->EditLineWidthOutside	->value();
	ALib->LimitLength		=ui->EditLimitLength		->value();
}

void PropertyLinePatternForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLinePatternLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LinePatternBase	*BBase=GetLinePatternBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyLinePatternForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyLinePatternForm::on_ButtonGenerateLibs_clicked()
{

}

void PropertyLinePatternForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyLinePatternForm::on_toolButtonLibrary_clicked()
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

void PropertyLinePatternForm::on_toolButtonCreateBlock_clicked()
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
	GetLayersBase()->SetStatusModes(this,/**/"CreateMode");
	BroadcastShowInEdit();
}

void PropertyLinePatternForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &index)
{
	LinePatternBase	*BBase=GetLinePatternBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReleaseSelectImagePanel	Cmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		Cmd.AlgoRoot=/**/"Basic";
		Cmd.AlgoName=/**/"LinePattern";
		Cmd.SendOnly(GlobalPage,0);
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,GlobalPage);
		for(int row=0;row<ui->tableWidgetBlockInfo->rowCount();row++){
			BlockInfoList *a=BlockInfos.GetItem(row);
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

void PropertyLinePatternForm::on_pushButtonSetFrom_clicked()
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

void PropertyLinePatternForm::on_pushButtonGetBack_clicked()
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

void PropertyLinePatternForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyLinePatternForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyLinePatternForm::on_pushButtonEditLibFolder_clicked()
{
	LinePatternBase	*BBase=GetLinePatternBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void PropertyLinePatternForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyLinePatternForm::on_toolButtonArea_clicked()
{
	BroadcastShowInEdit();
}

void PropertyLinePatternForm::on_toolButtonInside_clicked()
{
	BroadcastShowInEdit();
}

void PropertyLinePatternForm::on_toolButtonOutside_clicked()
{
	BroadcastShowInEdit();
}

void PropertyLinePatternForm::on_comboBoxResultAngleNumber_currentIndexChanged(int index)
{
	BroadcastShowInEdit();
}
