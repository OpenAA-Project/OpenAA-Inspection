#include "EditLibraryDialogResource.h"
#include "PropertyAlignmentFlexAreaForm.h"
#include "ui_PropertyAlignmentFlexAreaForm.h"
#include "AlignmentFlexAreaImagePropertyPacket.h"
#include "EditLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "BrightHistogramForm.h"
#include "SelectAlignmentFlexAreaDialog.h"
#include "SelectLibFolderDialog.h"
#include "InputAlignmentAreaForm.h"
#include "XDisplayImagePacket.h"
#include "ShowMarkListForm.h"
#include "XPropertyAlignmentFlexAreaCommon.h"
#include "XGUIPacketGeneral.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAlignmentFlexAreaForm::PropertyAlignmentFlexAreaForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyAlignmentFlexAreaForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID			=-1;
	ShowMarkListFormInst=NULL;

	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetArea			->setColumnWidth (0, 48);
	ui->tableWidgetArea			->setColumnWidth (1, 48);
	ui->tableWidgetArea			->setColumnWidth (2, 120);
	ui->tableWidgetArea			->setColumnWidth (3, 100);

	ui->tableWidgetWholeMatch	->setColumnWidth (0, 60);
	ui->tableWidgetWholeMatch	->setColumnWidth (1, 60);
	ui->tableWidgetWholeMatch	->setColumnWidth (2, 60);

	ui->tableWidgetBaseMatch	->setColumnWidth (0, 48);
	ui->tableWidgetBaseMatch	->setColumnWidth (1, 72);
	ui->tableWidgetBaseMatch	->setColumnWidth (2, 72);

	ui->tableWidgetLibList		->setColumnWidth (0, 30);
	ui->tableWidgetLibList		->setColumnWidth (1, 70);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 70);

	int	Wm=ui->tableWidgetMarkList->width()-32;
	ui->tableWidgetMarkList		->setColumnWidth (0, Wm*0.15);
	ui->tableWidgetMarkList		->setColumnWidth (1, Wm*0.5);
	ui->tableWidgetMarkList		->setColumnWidth (2, Wm*0.2);

	ui->tabWidgetPoint->setCurrentIndex(0);

	QStringList	AreaInfoLabel;
	ui->tableWidgetAlignmentFlexAreaInfo->setColumnCount(1+GetPageNumb());
	ui->tableWidgetAlignmentFlexAreaInfo->setColumnWidth (0, 48);
	AreaInfoLabel.append(/**/"LibID");
	for(int page=0;page<GetPageNumb();page++){
		ui->tableWidgetAlignmentFlexAreaInfo->setColumnWidth (1+page, 48);
		AreaInfoLabel.append(LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_2)/*"Page"*/
							+QString::number(page));
	}
	ui->tableWidgetAlignmentFlexAreaInfo->setHorizontalHeaderLabels(AreaInfoLabel);

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	if(LLib!=NULL){
		LLib->SetLibID(-1);
	}
	ShowAreaGrid();
	ui->toolButtonAlignmrntFlexAreaArea->setChecked(true);
	ui->stackedWidgetArea	->setCurrentIndex(0);

	InstallIgnoreKeyForChild();
}

PropertyAlignmentFlexAreaForm::~PropertyAlignmentFlexAreaForm()
{
    delete ui;

	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

AlignmentFlexAreaBase	*PropertyAlignmentFlexAreaForm::GetAlignmentFlexAreaBase(void)
{
	return (AlignmentFlexAreaBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
}


GUIFormBase	*PropertyAlignmentFlexAreaForm::GetImagePanel(void)
{
	GUIFormBase	*GForm=GetLayersBase()->FindByName(/**/"Inspection",/**/"AlignmentFlexAreaImagePanel",/**/"");
	return GForm;
}
void	PropertyAlignmentFlexAreaForm::RepaintImage(void)
{
	GUIFormBase	*GForm=GetImagePanel();
	if(GForm!=NULL){
		GForm->repaint();
	}
}
void	PropertyAlignmentFlexAreaForm::Prepare(void)
{
	//_heapchk();
}
void	PropertyAlignmentFlexAreaForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	int	CurrentRow=ui->tableWidgetArea->currentRow();
	int	CurrentAreaID=-1;
	if(CurrentRow>=0){
		AlignmentFlexAreaAreaList *a=AreaList[CurrentRow];
		if(a!=NULL){
			CurrentAreaID=a->AreaID;
		}
	}

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAlignmentFlexAreaAreaList	**BmpReceiver=new GUICmdSendAlignmentFlexAreaAreaList*[GetLayersBase()->GetPageNumb()];
	GUICmdReqAlignmentFlexAreaAreaList	**BmpRequester=new GUICmdReqAlignmentFlexAreaAreaList*[GetLayersBase()->GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[N]=new GUICmdSendAlignmentFlexAreaAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[N]=new GUICmdReqAlignmentFlexAreaAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		N++;
	}
	AreaList.RemoveAll();
	for(int n=0;n<N;n++){
		if(BmpRequester[n]->Send(BmpRequester[n]->GetGlobalPage(),0,*BmpReceiver[n])==true){
			AreaList+=BmpReceiver[n]->Area;
		}
	}

	for(int i=0;i<N;i++){
		delete	BmpRequester[i];
		delete	BmpReceiver[i];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	ui->tableWidgetArea->setRowCount(AreaList.GetNumber());
	N=0;
	for(AlignmentFlexAreaAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		::SetDataToTable(ui->tableWidgetArea ,0 ,N ,QString::number(a->GlobalPage)	,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetArea ,1 ,N ,QString::number(a->AreaID)		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QString	s=a->AreaName;
		if(s.isEmpty()==true)
			s=QString::number(a->XSize)+ QString(/**/",")+ QString::number(a->YSize);
		::SetDataToTable(ui->tableWidgetArea ,2 ,N ,s		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		QString	SType;
		QColor	BackCol=Qt::white;
		switch(a->Priority){
			case XAlignmentFlexAreaArea::_PriorityHigh:
				BackCol=BBase->ColorPriorityHigh;
				SType=/**/"High";
				break;
			case XAlignmentFlexAreaArea::_PriorityMiddle:
				BackCol=BBase->ColorPriorityMiddle;
				SType=/**/"Middle";
				break;
			case XAlignmentFlexAreaArea::_PriorityLow:
				BackCol=BBase->ColorPriorityLow;
				SType=/**/"Low";
				break;
			case XAlignmentFlexAreaArea::_PriorityGlobal:
				BackCol=BBase->ColorPriorityGlobal;
				SType=/**/"Global";
				break;
		}
		::SetDataToTable(ui->tableWidgetArea ,3 ,N ,SType	,Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		::SetTableColor(ui->tableWidgetArea ,0 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,1 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,2 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,3 ,N ,BackCol);
	}
	if(CurrentAreaID<0 && AreaList.GetCount()>0){
		ui->tableWidgetArea->setCurrentCell(0,0);
	}
	else{
		int	Row=0;
		for(AlignmentFlexAreaAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			if(a->AreaID==CurrentAreaID){
				ui->tableWidgetArea->setCurrentCell(Row,0);
				break;
			}
		}
	}


	ReEntrant=false;
}

void	PropertyAlignmentFlexAreaForm::ShowWholeMatchGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	int	CurrentRow=ui->tableWidgetWholeMatch->currentRow();
	int	CurrentWholeMatchID=-1;
	if(CurrentRow>=0){
		AlignmentWholeMatchList *a=WholeMatchInfo[CurrentRow];
		if(a!=NULL){
			CurrentWholeMatchID=a->ID;
		}
	}

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendWholeMatchList	**BmpReceiver=new GUICmdSendWholeMatchList*[GetLayersBase()->GetPageNumb()];
	GUICmdReqWholeMatchList		**BmpRequester=new GUICmdReqWholeMatchList*[GetLayersBase()->GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[N]=new GUICmdSendWholeMatchList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[N]=new GUICmdReqWholeMatchList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		N++;
	}
	WholeMatchInfo.RemoveAll();
	for(int n=0;n<N;n++){
		if(BmpRequester[n]->Send(BmpRequester[n]->GetGlobalPage(),0,*BmpReceiver[n])==true){
			WholeMatchInfo+=BmpReceiver[n]->WholeMatchInfo;
		}
	}

	for(int i=0;i<N;i++){
		delete	BmpRequester[i];
		delete	BmpReceiver[i];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	ui->tableWidgetWholeMatch->setRowCount(WholeMatchInfo.GetNumber());
	N=0;
	for(AlignmentWholeMatchList *a=WholeMatchInfo.GetFirst();a!=NULL;a=a->GetNext(),N++){
		::SetDataToTable(ui->tableWidgetWholeMatch ,0 ,N ,QString::number(a->GlobalPage)	,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetWholeMatch ,1 ,N ,QString::number(a->ID)		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetWholeMatch ,2 ,N ,QString::number(a->Division)		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	if(CurrentWholeMatchID<0 && WholeMatchInfo.GetCount()>0){
		ui->tableWidgetWholeMatch->setCurrentCell(0,0);
	}
	else{
		int	Row=0;
		for(AlignmentWholeMatchList *a=WholeMatchInfo.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			if(a->ID==CurrentWholeMatchID){
				ui->tableWidgetWholeMatch->setCurrentCell(Row,0);
				break;
			}
		}
	}


	ReEntrant=false;
}
void	PropertyAlignmentFlexAreaForm::ShowLibList(void)
{
	int	AreaPriority=-1;
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row>=0){
		AlignmentFlexAreaAreaList	*A=AreaList[Row];;
		if(A!=NULL)
			AreaPriority=A->Priority;
	}

	ui->tableWidgetLibList->setRowCount(0);
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		CmdGetAlignmentFlexAreaLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID	=LibFolderID;
		Packet.AreaPriority	=AreaPriority;
		BBase->TransmitDirectly(&Packet);
		//LibList	=Packet.AList;
		LibList.RemoveAll();

		AlgorithmLibraryList	**Dim=new AlgorithmLibraryList*[Packet.AList.GetCount()];
		int	row=0;
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			Dim[row]=a;
		}

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
void	PropertyAlignmentFlexAreaForm::ShowInEdit(void)
{
	ShowAlignmentFlexAreaInfoList();
	AlignmentFlexAreaBase	*ABase=GetAlignmentFlexAreaBase();
	if(ABase!=NULL){
		if(ABase->EnableBaseMatch==false){
			ui->stackedWidgetMatchingType	->setCurrentIndex(0);
		}
		else{
			ui->stackedWidgetMatchingType	->setCurrentIndex(1);
		}
	}
}
void	PropertyAlignmentFlexAreaForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
}
void	PropertyAlignmentFlexAreaForm::BuildForShow(void)
{
	StartPage();
	ShowAreaGrid();
	ShowWholeMatchGrid();
}
void	PropertyAlignmentFlexAreaForm::SetupLibFolder(int _LibFolderID,int originalLibFolder)
{
	LibFolderID=_LibFolderID;
}
void	PropertyAlignmentFlexAreaForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	CmdAlignmentFlexAreaDrawModePacket	*BDrawModePacket=dynamic_cast<CmdAlignmentFlexAreaDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==true)
			BDrawModePacket->DrawGeneratedArea=true;
		else
			BDrawModePacket->DrawGeneratedArea=false;

		if(ui->toolButtonOutline->isChecked()==true)
			BDrawModePacket->DrawOutlineArea=true;
		else 
			BDrawModePacket->DrawOutlineArea=false;

		if(ui->toolButtonWholeMatch->isChecked()==true)
			BDrawModePacket->DrawWholeMatch=true;
		else 
			BDrawModePacket->DrawWholeMatch=false;

		if(ui->toolButtonBaseMatch->isChecked()==true)
			BDrawModePacket->DrawBaseMatch=true;
		else 
			BDrawModePacket->DrawBaseMatch=false;

		BDrawModePacket->CurrentBaseMatchRow	=ui->tableWidgetBaseMatch	->currentRow();

		IntList	Rows;
		::GetSelectedRows(ui->tableWidgetArea,Rows);
		BDrawModePacket->SelectedArea.RemoveAll();
		for(IntClass *v=Rows.GetFirst();v!=NULL;v=v->GetNext()){
			AlignmentFlexAreaAreaList	*A=AreaList.GetItem(v->GetValue());
			if(A!=NULL){
				BDrawModePacket->SelectedArea.Add(A->AreaID);
			}
		}
		
		::GetSelectedRows(ui->tableWidgetWholeMatch,Rows);
		BDrawModePacket->SelectWholeMatch.RemoveAll();
		for(IntClass *v=Rows.GetFirst();v!=NULL;v=v->GetNext()){
			AlignmentWholeMatchList	*A=WholeMatchInfo.GetItem(v->GetValue());
			if(A!=NULL){
				BDrawModePacket->SelectWholeMatch.Add(A->ID);
			}
		}
		return;
	}
	CmdAlignmentFlexAreaDrawEnd	*AlignmentFlexAreaDEnd=dynamic_cast<CmdAlignmentFlexAreaDrawEnd *>(packet);
	if(AlignmentFlexAreaDEnd!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(AlignmentFlexAreaDEnd->Area ,PageList);
		if(PageN<=0)
			return;
		if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==true && ui->toolButtonOutline->isChecked()==false){
			InputAlignmentAreaForm	D(false,GetLayersBase(),/**/"",this);
			if(D.exec()==QDialog::Accepted){
				if(D.DeleteMode==false){
					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge area");

					for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
						int	LocalPage=PList->GetValue();
						int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

						FlexArea	A=AlignmentFlexAreaDEnd->Area;
						GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				

						GUICmdReqAlignmentFlexAreaPutArea	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
						DNewMsg.Area			=A;
						DNewMsg.AreaName		=D.AreaName;
						DNewMsg.LimitedLib		=D.Libs.SelectedList;
						DNewMsg.LibToCreateItems=D.LibToCreateItems;
						DNewMsg.GlobalPage		=globalPage;
						DNewMsg.Priority		=D.Priority;
						DNewMsg.Send(NULL,globalPage ,0);
					}
					ShowAreaGrid();
					for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
						for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
							QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
							p->setSelected(false);
						}
					}
				}
				else if(D.DeleteMode==true && ui->tableWidgetArea->currentRow()>=0){
					int	Row=ui->tableWidgetArea->currentRow();
					AlignmentFlexAreaAreaList	*A=AreaList.GetItem(Row);
					int	AreaID=A->AreaID;
					for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdDeleteArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
						Cmd.AreaID	=A->AreaID;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
			}
		}
		else if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==false){
			if(LLib->GetLibID()>=0){
				AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(LLib->GetLibrary());
				//GlobalPickupArea+=AlignmentFlexAreaDEnd->Area;
				BrightHistogramForm	D(AlignmentFlexAreaDEnd->Area
										,AlignmentFlexAreaDEnd->ImagePanelPoint
										,ALib->PickupL,ALib->PickupH
										,GetLayersBase(),this);
				D.Reflect(ALib->PickupL,ALib->PickupH);
				if(D.exec()==(int)true){
					ALib->PickupL	=D.PickupL;
					ALib->PickupH	=D.PickupH;
					on_ButtonLibSave_clicked();
				}
			}
		}
		else if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==true && ui->toolButtonOutline->isChecked()==true
		&& ui->tableWidgetArea->currentRow()>=0){
			int	Row=ui->tableWidgetArea->currentRow();
			AlignmentFlexAreaAreaList	*A=AreaList.GetItem(Row);
			int	AreaID=A->AreaID;

			SelectAlignmentFlexAreaDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.AlignmentFlexAreaLibID>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual AlignmentFlexArea");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(AlignmentFlexAreaDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=AlignmentFlexAreaDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualAlignmentFlexArea	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area	=A;
						Cmd.AreaID	=AreaID;
						Cmd.LibID	=D.AlignmentFlexAreaLibID;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowAlignmentFlexAreaInfoList();
			}
		}
		return;
	}
	CmdIsModeItemEditingPacket	*CmdIsModeItemEditingPacketVar=dynamic_cast<CmdIsModeItemEditingPacket *>(packet);
	if(CmdIsModeItemEditingPacketVar!=NULL){
		if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==true && ui->toolButtonOutline->isChecked()==false)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_AreaMode;
		else if(ui->toolButtonOutline->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_ItemMode;
		else if(ui->toolButtonWholeMatch->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_WholeMatchMode;
		return;
	}
	GUICmdAlignmentFlexAreaReflectChangeItems	*ReDrawMode=dynamic_cast<GUICmdAlignmentFlexAreaReflectChangeItems *>(packet);
	if(ReDrawMode!=NULL){
		ShowAreaGrid();
		//CreateAndShowPointGrid();
		return;
	}
	GUICmdReqAlignmentFlexAreaSetMode	*GUICmdReqAlignmentFlexAreaSetModeVar=dynamic_cast<GUICmdReqAlignmentFlexAreaSetMode *>(packet);
	if(GUICmdReqAlignmentFlexAreaSetModeVar!=NULL){
		ui->toolButtonAlignmrntFlexAreaArea	->setChecked(GUICmdReqAlignmentFlexAreaSetModeVar->ModeFlexAreaArea);
		ui->toolButtonOutline				->setChecked(GUICmdReqAlignmentFlexAreaSetModeVar->ModeOutline);
		ui->toolButtonWholeMatch			->setChecked(GUICmdReqAlignmentFlexAreaSetModeVar->ModeWholeMatch);
		return;
	}
	GUICmdReqAlignmentFlexAreaSetCurrentArea	*GUICmdReqAlignmentFlexAreaSetCurrentAreaVar=dynamic_cast<GUICmdReqAlignmentFlexAreaSetCurrentArea *>(packet);
	if(GUICmdReqAlignmentFlexAreaSetCurrentAreaVar!=NULL){
		for(int row=0;row<AreaList.GetCount();row++){
			if(AreaList[row]->AreaID==GUICmdReqAlignmentFlexAreaSetCurrentAreaVar->AreaID
			&& AreaList[row]->GlobalPage==GUICmdReqAlignmentFlexAreaSetCurrentAreaVar->GlobalPage){
				ui->tableWidgetArea->setCurrentCell(row,0);
				ui->tableWidgetArea->setCurrentCell(row,1);
			}
		}
		return;
	}
	CmdGetCurrentAreaIDPacket	*CmdGetCurrentAreaIDPacketVar=dynamic_cast<CmdGetCurrentAreaIDPacket *>(packet);
	if(CmdGetCurrentAreaIDPacketVar!=NULL){
		int	Row=ui->tableWidgetArea->currentRow();
		if(Row>=0){
			AlignmentFlexAreaAreaList	*a=AreaList[Row];
			if(a!=NULL){
				CmdGetCurrentAreaIDPacketVar->AreaID	=a->AreaID;
			}
		}
		return;
	}
	CmdSelectAlignmentFlexAreaLibraryDialog	*CmdSelectAlignmentFlexAreaLibraryDialogVar=dynamic_cast<CmdSelectAlignmentFlexAreaLibraryDialog *>(packet);
	if(CmdSelectAlignmentFlexAreaLibraryDialogVar!=NULL){
		SelectAlignmentFlexAreaDialog	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectAlignmentFlexAreaLibraryDialogVar->LibID=D.AlignmentFlexAreaLibID;
		}
		return;
	}
	ChangeAlignmentFlexAreaThresholdCommon	*ChangeAlignmentFlexAreaThresholdCommonVar=dynamic_cast<ChangeAlignmentFlexAreaThresholdCommon *>(packet);
	if(ChangeAlignmentFlexAreaThresholdCommonVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeAlignmentFlexAreaThreshold	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.LibID		=ChangeAlignmentFlexAreaThresholdCommonVar->LibID;
			Cmd.InfosData	=ChangeAlignmentFlexAreaThresholdCommonVar->InfosData;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdRemoveAllOriginalAlignmentFlexAreaItems	*CmdRemoveAllOriginalAlignmentFlexAreaItemsVar=dynamic_cast<CmdRemoveAllOriginalAlignmentFlexAreaItems *>(packet);
	if(CmdRemoveAllOriginalAlignmentFlexAreaItemsVar!=NULL){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqRemoveAllOriginal	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.GeneratedOrigin	=CmdRemoveAllOriginalAlignmentFlexAreaItemsVar->GeneratedOrigin;
			Cmd.SendOnly(GlobalPage,0);
		}
		return;
	}
	CmdGenerateBaseMatchGUI	*CmdGenerateBaseMatchVar=dynamic_cast<CmdGenerateBaseMatchGUI *>(packet);
	if(CmdGenerateBaseMatchVar!=NULL){
		on_pushButtonGenerateBaseMatch_clicked();
		return;
	}
}

bool	PropertyAlignmentFlexAreaForm::SaveContent(QIODevice *f)
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
bool	PropertyAlignmentFlexAreaForm::LoadContent(QIODevice *f)
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
	//_heapchk();

	return true;
}

void	PropertyAlignmentFlexAreaForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditMinAreaSize		->setValue(ALib->MinAreaSize	);
	ui->EditMaxAreaSize		->setValue(ALib->MaxAreaSize	);
	ui->EditMinAreaDots		->setValue(ALib->MinAreaDots	);
	ui->EditMaxAreaDots		->setValue(ALib->MaxAreaDots	);
	ui->EditLimitSize		->setValue(ALib->LimitSize		);
	ui->EditExpansionDot	->setValue(ALib->ExpansionDot	);
	ui->EditLimitSize		->setValue(ALib->LimitSize		);
}

void	PropertyAlignmentFlexAreaForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	ALib->MinAreaSize	=ui->EditMinAreaSize	->value();
	ALib->MaxAreaSize	=ui->EditMaxAreaSize	->value();
	ALib->MinAreaDots	=ui->EditMinAreaDots	->value();
	ALib->MaxAreaDots	=ui->EditMaxAreaDots	->value();
	ALib->LimitSize		=ui->EditLimitSize		->value();
	ALib->ExpansionDot	=ui->EditExpansionDot	->value();
	ALib->LimitSize		=ui->EditLimitSize		->value();
}

void PropertyAlignmentFlexAreaForm::on_ButtonLibSave_clicked()
{
	if(LLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
										, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_3)/*"Warning"*/
										, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_4)/*"No Library Name"*/
										, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
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

void PropertyAlignmentFlexAreaForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());
		CmdLoadAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL
									, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_5)/*"Library error"*/
									, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_6)/*"Not loaded this library record"*/);
			}
		}
	}
}
void PropertyAlignmentFlexAreaForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentFlexAreaImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(LLib->GetAdaptedPickLayers());
				ShowLibrary(*LLib);
			}
			else{
				QMessageBox::critical(NULL
								, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_7)/*"Library error"*/
								, LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_8)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}
void	PropertyAlignmentFlexAreaForm::SelectModeType(int ModeType)
{
	if(ModeType==0)
		ui->toolButtonAlignmrntFlexAreaArea->setChecked(true);
	else if(ModeType==1)
		ui->toolButtonOutline->setChecked(true);
	else if(ModeType==2)
		ui->toolButtonWholeMatch->setChecked(true);

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

void	PropertyAlignmentFlexAreaForm::ShowSelectedLibList(void)
{
	int	row=0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){

		//QColor	Col=GetTableColor(ColNum);

		::SetDataToTable(ui->tableWidgetGeneratedLibList ,0 ,row ,QString::number(a->GetLibID()));
		::SetDataToTable(ui->tableWidgetGeneratedLibList ,1 ,row ,a->GetLibName());
		//::SetTableColor(ui->tableWidgetGeneratedLibList ,0 ,row ,Col);
		//::SetTableColor(ui->tableWidgetGeneratedLibList ,1 ,row ,Col);
	}
}

void PropertyAlignmentFlexAreaForm::on_pushButtonPickupTest_clicked()
{
	if(LLib==NULL)
		return;
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row<0)
		return;
	AlignmentFlexAreaAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_9)/*"Pickup Test"*/,7);

	GetLibraryFromWindow(*LLib);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList.Add(LLib->GetLibID());
		Cmd.AreaID	=A->AreaID;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonGenerate_clicked()
{
	if(LLib==NULL)
		return;
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row<0)
		return;
	AlignmentFlexAreaAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	//_heapchk();

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate AlignmentFlexAreas automatically");
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_10)/*"Generating items"*/
										,false,SelectedLibList.GetCount()*(7+7));
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateAlignmentFlexAreas	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList	=SelectedLibList.GetIDList();
		Cmd.AreaID	=A->AreaID;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonClearPickup_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}
void	PropertyAlignmentFlexAreaForm::GenerateAreaFromMask(int Priority,int ItemLibID)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate Area with Item automatically");
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAlignmentFlexAreaForm_LS,LID_11)/*"Generating items from mask"*/
										,false,SelectedLibList.GetCount()*(7+7));
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateAlignmentFlexAreaFromMask	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Priority	=Priority;
		Cmd.ItemLibID	=ItemLibID;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyAlignmentFlexAreaForm::ShowAlignmentFlexAreaInfoList(void)
{
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row<0)
		return;
	AlignmentFlexAreaAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;

	AlignmentFlexAreaInfos.RemoveAll();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaPointList		CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.AreaID	=A->AreaID;
		GUICmdSendAlignmentFlexAreaPointList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
			for(AlignmentFlexAreaInfoList *a=CmdSend.Points.GetFirst();a!=NULL;a=a->GetNext()){
				AlignmentFlexAreaInfoList *b;
				for(b=AlignmentFlexAreaInfos.GetFirst();b!=NULL;b=b->GetNext()){
					if(a->LibID==b->LibID){
						while(b->AlignmentFlexAreaCount.GetCount()<GlobalPage){
							b->AlignmentFlexAreaCount.Add(0);
						}
						b->AlignmentFlexAreaCount.Add(a->AlignmentFlexAreaCount.GetFirst()->GetValue());
						break;
					}
				}
				if(b==NULL){
					b=new AlignmentFlexAreaInfoList();
					b->LibID=a->LibID;
					while(b->AlignmentFlexAreaCount.GetCount()<GlobalPage){
						b->AlignmentFlexAreaCount.Add(0);
					}
					b->AlignmentFlexAreaCount.Add(a->AlignmentFlexAreaCount.GetFirst()->GetValue());
					AlignmentFlexAreaInfos.AppendList(b);
				}
			}
		}
	}
	int	N=AlignmentFlexAreaInfos.GetNumber();
	ui->tableWidgetAlignmentFlexAreaInfo->setRowCount(N);
	AlgorithmLibraryListContainer LibIDList;
	for(AlignmentFlexAreaInfoList *a=AlignmentFlexAreaInfos.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmLibraryList	*k=new AlgorithmLibraryList();
		k->SetLibID(a->GetLibID());
		LibIDList.AppendList(k);
	}
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	GetLayersBase()->GetDatabaseLoader()->G_GetLibraryNames(*GetLayersBase()->GetDataBase(),BBase->GetLibraryContainer(),LibIDList);
	int	row=0;
	for(AlignmentFlexAreaInfoList *a=AlignmentFlexAreaInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QString	LibName;
		for(AlgorithmLibraryList *m=LibIDList.GetFirst();m!=NULL;m=m->GetNext()){
			if(m->GetLibID()==a->GetLibID()){
				LibName=m->GetLibName();
				break;
			}
		}
		::SetDataToTable(ui->tableWidgetAlignmentFlexAreaInfo ,0 ,row ,QString::number(a->LibID));
		for(int page=0;page<GetPageNumb();page++){
			int	n=a->AlignmentFlexAreaCount[page];
			::SetDataToTable(ui->tableWidgetAlignmentFlexAreaInfo ,1+page ,row ,QString::number(n));
		}
	}
}
void PropertyAlignmentFlexAreaForm::on_tableWidgetAlignmentFlexAreaInfo_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row<0)
		return;
	AlignmentFlexAreaAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	int	ItemRow=ui->tableWidgetAlignmentFlexAreaInfo->currentRow();
	if(ItemRow<0)
		return;
	AlignmentFlexAreaInfoList	*ItemIndex=AlignmentFlexAreaInfos[ItemRow];
	if(ItemIndex==NULL)
		return;

	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSelectByLibs	Cmd(BBase,sRoot,sName,GlobalPage);
		SelectLibList	*v=new SelectLibList();
		v->LibType	=BBase->GetLibType();
		v->LibID	=ItemIndex->LibID;
		v->Layer=0;
		Cmd.SelectedList.AppendList(v);
		Cmd.SendOnly(GlobalPage,1);
	}
	ShowLibList();
	BroadcastShowInEdit();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(LLib!=NULL){
		CmdLoadAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
			}
		}
	}
}

void PropertyAlignmentFlexAreaForm::on_pushButtonEditLibFolder_clicked()
{
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	SelectLibFolderDialog	D(BBase->GetLibType(),GetLayersBase(),this);
	if(D.exec()==(int)true){
		SetLibFolder(D.SelectedLibFolderID,D.SelectedFolderName);
	}
}

void	PropertyAlignmentFlexAreaForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonSetFrom_clicked()
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

void PropertyAlignmentFlexAreaForm::on_pushButtonGetBack_clicked()
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

void PropertyAlignmentFlexAreaForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void	PropertyAlignmentFlexAreaForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void	PropertyAlignmentFlexAreaForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}


void PropertyAlignmentFlexAreaForm::on_toolButtonGenerate_clicked()
{
	RepaintImage();
}

void PropertyAlignmentFlexAreaForm::on_toolButtonOutline_clicked()
{
	RepaintImage();

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaSetMode	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ModeFlexAreaArea	=ui->toolButtonAlignmrntFlexAreaArea	->isChecked();
		Cmd.ModeWholeMatch		=ui->toolButtonWholeMatch				->isChecked();
		Cmd.ModeOutline			=ui->toolButtonOutline					->isChecked();
		Cmd.Send(NULL,GlobalPage,0);
	}	
}

void PropertyAlignmentFlexAreaForm::on_toolButtonAlignmrntFlexAreaArea_clicked()
{
	RepaintImage();
	ui->stackedWidgetArea	->setCurrentIndex(0);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaSetMode	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ModeFlexAreaArea	=ui->toolButtonAlignmrntFlexAreaArea	->isChecked();
		Cmd.ModeWholeMatch		=ui->toolButtonWholeMatch				->isChecked();
		Cmd.ModeOutline			=ui->toolButtonOutline					->isChecked();
		Cmd.Send(NULL,GlobalPage,0);
	}	
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetArea_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetArea->currentRow();
	if(Row>=0){
		AlignmentFlexAreaAreaList	*a=AreaList[Row];
		//int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaSetCurrentArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),a->GlobalPage);
		Cmd.AreaID	=a->AreaID;
		Cmd.GlobalPage=a->GlobalPage;
		Cmd.Send(NULL,a->GlobalPage,0);

		ShowPointList(a->GlobalPage,a->AreaID);
	}	

	ShowAlignmentFlexAreaInfoList();
	ShowLibList();
	RepaintImage();
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetArea_doubleClicked(const QModelIndex &Index)
{
	int	R=Index.row();
	AlignmentFlexAreaAreaList *a=AreaList[R];
	if(a!=NULL){
		InputAlignmentAreaForm	D(true,GetLayersBase(),a->AreaName,this);
		D.Reflect(a);
		if(D.exec()==QDialog::Accepted){
			if(D.DeleteMode==false){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Modify AlignmentFlexArea area");

				QString	EmitterRoot=sRoot;
				QString	EmitterName=sName;
				GUICmdReqModifyAlignmentFlexAreaAreaInfo	DModMsg(GetLayersBase(),EmitterRoot,EmitterName,a->GlobalPage);
				DModMsg.AreaName		=D.AreaName;
				DModMsg.AreaID			=a->AreaID;
				DModMsg.LimitedLib		=D.Libs.SelectedList;
				DModMsg.LibToCreateItems=D.LibToCreateItems;
				DModMsg.DeleteMode		=D.DeleteMode;
				DModMsg.Priority		=D.Priority;
				DModMsg.Send(NULL,a->GlobalPage ,0);
			}
			else{
				int	AreaID=a->AreaID;
				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdDeleteArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
					Cmd.AreaID	=AreaID;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
		ShowAreaGrid();
	}
}

void PropertyAlignmentFlexAreaForm::on_toolButtonWholeMatch_clicked()
{
    BroadcastShowInEdit();
	RepaintImage();
	ui->stackedWidgetArea	->setCurrentIndex(1);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentFlexAreaSetMode	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ModeFlexAreaArea	=ui->toolButtonAlignmrntFlexAreaArea	->isChecked();
		Cmd.ModeWholeMatch		=ui->toolButtonWholeMatch				->isChecked();
		Cmd.ModeOutline			=ui->toolButtonOutline					->isChecked();
		Cmd.Send(NULL,GlobalPage,0);
	}	
}

void PropertyAlignmentFlexAreaForm::on_toolButtonMark_clicked()
{
    BroadcastShowInEdit();
	RepaintImage();
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetWholeMatch_clicked(const QModelIndex &index)
{
    BroadcastShowInEdit();
	RepaintImage();
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetAlignmentFlexAreaInfo_doubleClicked(const QModelIndex &index)
{
	int	ARow=ui->tableWidgetArea->currentRow();
	if(ARow>=0){
		AlignmentFlexAreaAreaList	*FArea=AreaList[ARow];
		int	Row=ui->tableWidgetAlignmentFlexAreaInfo->currentRow();
		if(Row<0)
			return;
		AlignmentFlexAreaInfoList *a=AlignmentFlexAreaInfos[Row];
		if(a==NULL)
			return;
		if(ShowMarkListFormInst==NULL){
			ShowMarkListFormInst=new ShowMarkListForm(GetLayersBase());
		}
		ShowMarkListFormInst->Initial(FArea->AreaID,a->LibID);
		ShowMarkListFormInst->show();
	}
}

void PropertyAlignmentFlexAreaForm::on_toolButtonBaseMatch_clicked()
{
	ui->stackedWidgetArea	->setCurrentIndex(2);
    BroadcastShowInEdit();
	RepaintImage();
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetBaseMatch_clicked(const QModelIndex &index)
{
    BroadcastShowInEdit();
	RepaintImage();
}

void	PropertyAlignmentFlexAreaForm::DrawBaseMatchList(void)
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
	GUICmdReqBaseMatchList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	GUICmdAckBaseMatchList	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	RCmd.Send(GlobalPage,0,ACmd);
	ui->tableWidgetBaseMatch->setRowCount(ACmd.ListData.GetCount());
	int	Row=0;
	for(MatchAngleList *f=ACmd.ListData.GetFirst();f!=NULL;f=f->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetBaseMatch ,0 ,Row ,QString::number(f->SImageNo));
		::SetDataToTable(ui->tableWidgetBaseMatch ,1 ,Row ,QString::number(f->Angle	,'f',3));
		::SetDataToTable(ui->tableWidgetBaseMatch ,2 ,Row ,QString::number(f->MatchingRate));
	}
}

void PropertyAlignmentFlexAreaForm::on_pushButtonGenerateBaseMatch_clicked()
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
	GUICmdGenerateBaseMatch	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	Cmd.Send(NULL,GlobalPage,0);

	DrawBaseMatchList();
}

void PropertyAlignmentFlexAreaForm::on_pushButtonExecuteBaseMatch_clicked()
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
	GUICmdExecBaseMatch	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	Cmd.Send(NULL,GlobalPage,0);

	DrawBaseMatchList();
}

void	PropertyAlignmentFlexAreaForm::CreateAreaInMaskingArea(int priority)
{
}

void	PropertyAlignmentFlexAreaForm::GenerateAlignmentFlexArea(void)
{
	on_pushButtonGenerate_clicked();
}

void PropertyAlignmentFlexAreaForm::ShowPointList(int Page,int AreaID)
{
	ui->tableWidgetMarkList->setRowCount(0);

	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	GUICmdReqAlignmentPointList		CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
	CmdReq.AreaID	=AreaID;
	GUICmdAckAlignmentPointList	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
	if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
		CurrentPointList	=CmdSend.PointList;
		ui->tableWidgetMarkList->setRowCount(CmdSend.PointList.GetCount());
		int	Row=0;
		for(AlignmentPointList *a=CmdSend.PointList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			::SetDataToTable(ui->tableWidgetMarkList,0, Row, QString::number(a->LibID));
			::SetDataToTable(ui->tableWidgetMarkList,1, Row, QString::number((a->PosX1+a->PosX2)/2)
															+QString(",")
															+QString::number((a->PosY1+a->PosY2)/2));
			::SetDataToTable(ui->tableWidgetMarkList,2, Row, QString::number(a->SearchDot));
		}
	}
	
}

void PropertyAlignmentFlexAreaForm::on_tableWidgetMarkList_clicked(const QModelIndex &index)
{
	int	ALine=ui->tableWidgetArea->currentRow();
	if(ALine<0)
		return;
	AlignmentFlexAreaAreaList *A=AreaList[ALine];
	if(A==NULL)
		return;

	int	R=ui->tableWidgetMarkList->currentRow();
	if(R<0)
		return;
	AlignmentPointList *a=CurrentPointList[R];
	if(a==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(A->GlobalPage);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,a->PosX1+P->GetOutlineOffset()->x,a->PosY1+P->GetOutlineOffset()->y
									,a->PosX2+P->GetOutlineOffset()->x,a->PosY2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentFlexAreaImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),A->GlobalPage,0,a->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}
