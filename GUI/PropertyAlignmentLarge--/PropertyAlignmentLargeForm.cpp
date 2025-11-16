#include "AlignmentLargeFormResource.h"
#include "PropertyAlignmentLargeForm.h"
#include "ui_PropertyAlignmentLargeForm.h"
#include "XGeneralFunc.h"
#include "AlignmentLargeImagePropertyPacket.h"
#include "InputAlignmentAreaForm.h"
#include "ImageControlTools.h"
#include "InputAlignmentPointForm.h"
#include "XDisplayImagePacket.h"
#include "EditAlignmentLargeLibraryDialog.h"
#include "XPropertyAlignmentLargeCommon.h"
#include "SelectAlignmentLargeDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAlignmentLargeForm::PropertyAlignmentLargeForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyAlignmentLargeForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->tableWidgetArea->setColumnWidth (0,45);
	ui->tableWidgetArea->setColumnWidth (1,45);
	ui->tableWidgetArea->setColumnWidth (2,120);
	ui->tableWidgetArea->setColumnWidth (3,100);

	ui->tableWidgetPoint->setColumnWidth (0,86);
	ui->tableWidgetPoint->setColumnWidth (1,86);
	ui->tableWidgetPoint->setColumnWidth (2,50);
	ui->tableWidgetPoint->setColumnWidth (3,50);
	ui->tableWidgetPoint->setColumnWidth (4,50);

	ImageControlToolsPointer=NULL;
	ui->pushButtonSelectAll->setEnabled(false);

	InstallIgnoreKeyForChild();
}

PropertyAlignmentLargeForm::~PropertyAlignmentLargeForm()
{
    delete ui;
}

AlignmentLargeBase	*PropertyAlignmentLargeForm::GetAlignmentLargeBase(void)
{
	AlignmentLargeBase *BBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	return BBase;
}
void	PropertyAlignmentLargeForm::ReadyParam(void)
{
	ImageControlToolsPointer	=(ImageControlTools *)GetImageControlToolsPointer();
	if(ImageControlToolsPointer!=NULL){
		connect(ImageControlToolsPointer,SIGNAL(SignalChangeCurrentLayer(int)),this,SLOT(SlotLayerButtonClicked(int)));
	}
	ShowAreaGrid();
	ui->toolButtonArea->setChecked(true);
}
void	PropertyAlignmentLargeForm::BuildForShow(void)
{
	ShowAreaGrid();
}

bool	PropertyAlignmentLargeForm::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	ShowAreaGrid();
	return true;
}

void	PropertyAlignmentLargeForm::SlotLayerButtonClicked(int newLayer)
{
	ShowAreaGrid();
	ShowPointList();
}
void	PropertyAlignmentLargeForm::ShowInEdit	(void)
{
	ShowAreaGrid();
	ShowPointList();
}

void	PropertyAlignmentLargeForm::StartPage(void)
{
	ShowAreaGrid();
	ShowPointList();
}

void	PropertyAlignmentLargeForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAlignmentLargeAreaList	**BmpReceiver	=new GUICmdSendAlignmentLargeAreaList*[GetLayersBase()->GetPageNumb()];
	GUICmdReqAlignmentLargeAreaList		**BmpRequester	=new GUICmdReqAlignmentLargeAreaList*[GetLayersBase()->GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[N]=new GUICmdSendAlignmentLargeAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[N]=new GUICmdReqAlignmentLargeAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
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

	AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
	ui->tableWidgetArea->setRowCount(AreaList.GetNumber());
	N=0;
	for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		::SetDataToTable(ui->tableWidgetArea ,0 ,N ,QString::number(a->GlobalPage));
		::SetDataToTable(ui->tableWidgetArea ,1 ,N ,QString::number(a->AreaID));
		::SetDataToTable(ui->tableWidgetArea ,2 ,N ,a->AreaName);
		::SetDataToTable(ui->tableWidgetArea ,3 ,N ,  QString::number(a->XSize)
													+ QString(/**/",")
													+ QString::number(a->YSize));
		QColor	BackCol=Qt::white;
		switch(a->Priority){
			case XAlignmentLargeArea::_PriorityHigh:
				BackCol=BBase->ColorPriorityHigh;
				break;
			case XAlignmentLargeArea::_PriorityMiddle:
				BackCol=BBase->ColorPriorityMiddle;
				break;
			case XAlignmentLargeArea::_PriorityLow:
				BackCol=BBase->ColorPriorityLow;
				break;
			case XAlignmentLargeArea::_PriorityGlobal:
				BackCol=BBase->ColorPriorityGlobal;
				break;
		}
		::SetTableColor(ui->tableWidgetArea ,0 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,1 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,2 ,N ,BackCol);
		::SetTableColor(ui->tableWidgetArea ,3 ,N ,BackCol);
	}
	ReEntrant=false;
}

void	PropertyAlignmentLargeForm::ShowPointGrid(AlignmentLargeAreaList *A)
{
	PointList.RemoveAll();
	CreatePointList(A);
	ShowPointGridRaw();
}

void	PropertyAlignmentLargeForm::CreatePointList(AlignmentLargeAreaList *A)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	int	globalPage=A->GlobalPage;
	GUICmdSendAlignmentLargePointList	BmpReceiver (GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	GUICmdReqAlignmentLargePointList	BmpRequester(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	BmpRequester.Number=A->Number;

	if(BmpRequester.Send(BmpRequester.GetGlobalPage(),0,BmpReceiver)==true){
		PointList+=BmpReceiver.Points;
	}
	ReEntrant=false;
}
void	PropertyAlignmentLargeForm::ShowPointGridRaw(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;
	ui->tableWidgetPoint->setRowCount(PointList.GetNumber());
	int	N=0;
	for(AlignmentLargePointList *a=PointList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		::SetDataToTable(ui->tableWidgetPoint ,0 ,N ,QString::number(a->Cx)
													+QString(/**/",")
													+QString::number(a->Cy)
													,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetPoint ,1 ,N ,QString::number(a->XSize)
													+QString(/**/",")
													+QString::number(a->YSize)
													,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetPoint ,2 ,N ,QString::number(a->GroupID)
													,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetPoint ,3 ,N ,QString(/**/"Pattern")
													,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetPoint ,4 ,N ,QString::number(a->MoveDotX)
													+QString(/**/",")
													+QString::number(a->MoveDotY)
													,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	ReEntrant=false;
}

//==============================================================================
void PropertyAlignmentLargeForm::on_toolButtonArea_clicked()
{
	GUICmdClickAreaButton	RCmd(GetLayersBase(),sRoot,sName,-1);
	RCmd.InstName=GetName();
	RCmd.SendAllPages(NULL,0);
}

void PropertyAlignmentLargeForm::on_toolButtonPoint_clicked()
{
	AlignmentLargeAreaList	*AL=AreaList[0];
	if(AL==NULL)
		return;

	IntList	Rows;
	Rows.Add(0);
	::SetSelectedRows(ui->tableWidgetArea	,Rows);

	GUICmdClickPointButton	RCmd(GetLayersBase(),sRoot,sName,-1);
	RCmd.InstName=GetName();
	RCmd.SendAllPages(NULL,0);
}

void PropertyAlignmentLargeForm::CreateAndShowPointGrid(void)
{
	QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
	PointList.RemoveAll();

	for(int i=0;i<Q.count();i++){
		QTableWidgetItem *qi=Q.value(i);
		if(qi->column()!=0)
			continue;
		AlignmentLargeAreaList *a=AreaList.GetItem(qi->row());
		if(a==NULL)
			continue;
		CreatePointList(a);
	}
	ShowPointGridRaw();
}

void	PropertyAlignmentLargeForm::TransmitDirectly(GUIDirectMessage *packet)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdAlignmentLargeDrawEnd	*Da=dynamic_cast<GUICmdAlignmentLargeDrawEnd *>(packet);
	if(Da!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(Da->Area ,PageList);
		if(PageN<=0)
			return;

		if(ui->toolButtonArea->isChecked()==true){
			InputAlignmentAreaForm	D(false,GetLayersBase(),/**/"",this);
			if(D.exec()==QDialog::Accepted){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge area");

				for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
					int	LocalPage=PList->GetValue();
					int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

					FlexArea	A=Da->Area;
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
					GUICmdReqAlignmentLargePutArea	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
					DNewMsg.Area		=A;
					DNewMsg.AreaName	=D.AreaName;
					DNewMsg.LimitedLib	=D.Libs.SelectedList;
					DNewMsg.GlobalPage	=globalPage;
					DNewMsg.Priority	=D.Priority;
					DNewMsg.Send(NULL,globalPage ,0);
				}
			}
			ShowAreaGrid();
			ui->tableWidgetArea->setUpdatesEnabled(false);
			for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
				for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
					QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
					p->setSelected(false);
				}
			}
			ui->tableWidgetArea->setUpdatesEnabled(true);
			AreaListFromMaster.RemoveAll();
		}
		else if(ui->toolButtonPoint->isChecked()==true){
			QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
			if(Q.count()==0)
				return;
			IntList Rows;
			::GetSelectedRows(ui->tableWidgetArea,Rows);
			if(Da->MultiSelect==false && Rows.GetCount()==0)
				return;

			InputAlignmentPointForm	D(GetLayersBase(),NULL);
			if(D.exec()==QDialog::Accepted){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge point");

				bool	UseBitBuff=GetUseBitBuffMode();
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(Da->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	LocalPage=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(LocalPage);
					FlexArea	A=Da->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>9){
						int	globalPage	=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

						GUICmdReqAlignmentLargePutPoint	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
						if(Da->MultiSelect==false){
							int	Row=Rows[0];
							AlignmentLargeAreaList	*a=AreaList[Row];
							DNewMsg.AreaID		=a->AreaID;
							DNewMsg.PointArea	=A;
							DNewMsg.MoveDotX	=D.MoveDotX;
							DNewMsg.MoveDotY	=D.MoveDotY;
							DNewMsg.MoveDotX2	=D.MoveDotX2;
							DNewMsg.MoveDotY2	=D.MoveDotY2;
							DNewMsg.GroupID		=D.GroupID;		
							DNewMsg.UsageGlobal	=D.UsageGlobal;
							DNewMsg.GlobalPage	=globalPage;
							DNewMsg.UseBitBuff	=UseBitBuff;
							DNewMsg.Send(NULL,globalPage ,0);
						}
						else{
							for(IntClass *c=Rows.GetFirst();c!=NULL;c=c->GetNext()){
								int	row=c->GetValue();
								AlignmentLargeAreaList	*a=AreaList[row];
								if(a->GlobalPage==globalPage){
									DNewMsg.AreaID=a->AreaID;
									DNewMsg.PointArea	=A;
									DNewMsg.MoveDotX	=D.MoveDotX;
									DNewMsg.MoveDotY	=D.MoveDotY;
									DNewMsg.MoveDotX2	=D.MoveDotX2;
									DNewMsg.MoveDotY2	=D.MoveDotY2;
									DNewMsg.GroupID		=D.GroupID;		
									DNewMsg.UsageGlobal	=D.UsageGlobal;
									DNewMsg.GlobalPage	=globalPage;
									DNewMsg.UseBitBuff	=UseBitBuff;
									DNewMsg.Send(NULL,globalPage ,0);
								}
							}
						}
					}
				}
			}
			PointList.RemoveAll();
			for(int i=0;i<Q.count();i++){
				QTableWidgetItem *qi=Q.value(i);
				if(qi->column()!=0)
					continue;
				AlignmentLargeAreaList *a=AreaList.GetItem(qi->row());
				if(a==NULL)
					continue;
				CreatePointList(a);
			}
			ShowPointGridRaw();
		}
		return;
	}
	GUICmdReqAlignmentLargeDrawMode	*DMode=dynamic_cast<GUICmdReqAlignmentLargeDrawMode *>(packet);
	if(DMode!=NULL){
		if(ui->toolButtonArea->isChecked()==true)
			DMode->Mode=AlignmentLargeDrawAttr::_Area;
		if(ui->toolButtonPoint->isChecked()==true)
			DMode->Mode=AlignmentLargeDrawAttr::_Point;

		QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentLargeAreaList *a=AreaList.GetItem(qi->row());
			if(a==NULL)
				continue;
			ReqAlignmentLargeAreaList	*qa=new ReqAlignmentLargeAreaList();
			qa->AreaID		=a->AreaID;
			qa->GlobalPage	=a->GlobalPage;

			DMode->AList.AppendList(qa);
		}
		DMode->AList+=AreaListFromMaster;
		if(ui->comboBoxAngle->currentIndex()>=0
		&& AngleList.GetCount()>ui->comboBoxAngle->currentIndex()){
			DMode->AngleRadian=AngleList[ui->comboBoxAngle->currentIndex()];
		}
		return;
	}
	GUICmdAlignmentLargeReflectChangeItems	*ReDrawMode=dynamic_cast<GUICmdAlignmentLargeReflectChangeItems *>(packet);
	if(ReDrawMode!=NULL){
		ShowAreaGrid();
		CreateAndShowPointGrid();
		return;
	}
	GetSelectedAlignmentLargeAreaPacket	*SAArea=dynamic_cast<GetSelectedAlignmentLargeAreaPacket *>(packet);
	if(SAArea!=NULL){
		if(ui->toolButtonArea->isChecked()==true){
			InputAlignmentAreaForm	D(false,GetLayersBase(),/**/"",this);
			if(D.exec()==QDialog::Accepted){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				::Save(&Buff,(int32)1);
				::Save(&Buff,D.AreaName);
				D.Libs.SelectedList.Save(&Buff);
				int32	Priority=(int32)D.Priority;
				::Save(&Buff,Priority);
				SAArea->BuffData=Buff.buffer();
			}
		}
		else if(ui->toolButtonPoint->isChecked()==true){
			IntList	Rows;
			GetSelectedRows(ui->tableWidgetArea ,Rows);
			if(Rows.GetCount()>0){
				int32		AreaID=AreaList[Rows.GetFirst()->GetValue()]->AreaID;
				InputAlignmentPointForm	D(GetLayersBase(),NULL);
				if(D.exec()==QDialog::Accepted){
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					::Save(&Buff,(int32)2);
					::Save(&Buff,AreaID);
					::Save(&Buff,D.MoveDotX);
					::Save(&Buff,D.MoveDotY);
					::Save(&Buff,D.MoveDotX2);
					::Save(&Buff,D.MoveDotY2);
					::Save(&Buff,D.GroupID);
					::Save(&Buff,D.UsageGlobal);
					SAArea->BuffData=Buff.buffer();
				}
			}
		}
		return;
	}
	CmdIsModeItemEditingPacket	*CmdIsModeItemEditingPacketVar=dynamic_cast<CmdIsModeItemEditingPacket *>(packet);
	if(CmdIsModeItemEditingPacketVar!=NULL){
		if(ui->toolButtonArea->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_AreaMode;
		else if(ui->toolButtonPoint->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_ItemMode;
		return;
	}
	CmdSetActiveAreas	*CmdSetActiveAreasVar=dynamic_cast<CmdSetActiveAreas *>(packet);
	if(CmdSetActiveAreasVar!=NULL){
		ShowAreaGrid();

		ui->tableWidgetArea->setUpdatesEnabled(false);
		for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
			for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
				QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
				p->setSelected(false);
			}
		}
		for(ReqAlignmentLargeAreaList *L=CmdSetActiveAreasVar->ActiveAreas.GetFirst();L!=NULL;L=L->GetNext()){
			int	Row=0;
			for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
				if(L->GlobalPage==a->GlobalPage
				&& L->AreaID	==a->AreaID){
					for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
						QTableWidgetItem	*p=ui->tableWidgetArea->item(Row,c);
						p->setSelected(true);
					}
				}
			}
		}
		ui->tableWidgetArea->setUpdatesEnabled(true);

		AreaListFromMaster=CmdSetActiveAreasVar->ActiveAreas;
		return;
	}
	CmdAddArea	*CmdAddAreaVar=dynamic_cast<CmdAddArea *>(packet);
	if(CmdAddAreaVar!=NULL){
		ui->tableWidgetArea->setUpdatesEnabled(false);
		for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
			for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
				QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
				p->setSelected(false);
			}
		}
		ui->tableWidgetArea->setUpdatesEnabled(true);
		return;
	}
	GUICmdClickAreaButton *GUICmdClickAreaButtonVar=dynamic_cast<GUICmdClickAreaButton *>(packet);
	if(GUICmdClickAreaButtonVar!=NULL){
		ui->toolButtonArea->setChecked(true);
	}
	GUICmdClickPointButton *GUICmdClickPointButtonVar=dynamic_cast<GUICmdClickPointButton *>(packet);
	if(GUICmdClickPointButtonVar!=NULL){
		ui->toolButtonPoint->setChecked(true);
	}

	CmdClickAreaButton *CmdClickAreaButtonVar=dynamic_cast<CmdClickAreaButton *>(packet);
	if(CmdClickAreaButtonVar!=NULL){
		ui->toolButtonArea->setChecked(true);
	}
	CmdClickPointButton *CmdClickPointButtonVar=dynamic_cast<CmdClickPointButton *>(packet);
	if(CmdClickPointButtonVar!=NULL){
		ui->toolButtonPoint->setChecked(true);
	}
	CmdSelectAlignmentLargeLibraryDialog	*CmdSelectAlignmentLargeLibraryDialogVar=dynamic_cast<CmdSelectAlignmentLargeLibraryDialog *>(packet);
	if(CmdSelectAlignmentLargeLibraryDialogVar!=NULL){
		SelectAlignmentLargeDialog	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectAlignmentLargeLibraryDialogVar->LibID=D.AlignmentLargeLibID;
		}
		return;
	}
	CmdSetMultiSelectAlignmentLarge	*CmdSetMultiSelectAlignmentLargeVar=dynamic_cast<CmdSetMultiSelectAlignmentLarge *>(packet);
	if(CmdSetMultiSelectAlignmentLargeVar!=NULL){
		if(CmdSetMultiSelectAlignmentLargeVar->MultiSelect==true){
			ui->tableWidgetArea->setSelectionMode(QAbstractItemView::MultiSelection);
			ui->pushButtonSelectAll->setEnabled(true);
		}
		else{
			ui->tableWidgetArea->setSelectionMode(QAbstractItemView::SingleSelection);
			ui->pushButtonSelectAll->setEnabled(false);
		}
		return;
	}
	CmdReqAlignmentLargeSelectedAreaID	*CmdReqAlignmentLargeSelectedAreaIDVar=dynamic_cast<CmdReqAlignmentLargeSelectedAreaID *>(packet);
	if(CmdReqAlignmentLargeSelectedAreaIDVar!=NULL){
		IntList	Rows;
		::GetSelectedRows(ui->tableWidgetArea,Rows);
		for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GlobalPage==CmdReqAlignmentLargeSelectedAreaIDVar->Page && Rows.IsInclude(a->Number)==true){
				CmdReqAlignmentLargeSelectedAreaIDVar->AreaIDList.Add(a->AreaID);
			}
		}
		return;
	}
}

void	PropertyAlignmentLargeForm::CreateAlignmentArea(FlexArea &area)
{
	IntList	PageList;
	int	PageN=GetLayersBase()->GetLocalPageFromArea(area ,PageList);
	if(PageN<=0)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge area");

	for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
		int	LocalPage=PList->GetValue();
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

		FlexArea	A=area;
		GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
		GUICmdReqAlignmentLargePutArea	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
		DNewMsg.Area		=A;
		DNewMsg.AreaName	=/**/"";
		DNewMsg.GlobalPage	=globalPage;
		DNewMsg.Priority	=XAlignmentLargeArea::_PriorityMiddle;
		DNewMsg.Send(NULL,globalPage ,0);
	}
	ShowAreaGrid();

	ui->tableWidgetArea->setUpdatesEnabled(false);
	for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
		for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
			QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
			p->setSelected(false);
		}
	}
	ui->tableWidgetArea->setUpdatesEnabled(true);

	AreaListFromMaster.RemoveAll();
}

void	PropertyAlignmentLargeForm::CreateAlignmentPoint(FlexArea &area ,int MoveDotX,int MoveDotY,int MoveDotX2,int MoveDotY2)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge point");

	bool	UseBitBuff=GetUseBitBuffMode();
	IntList	Rows;
	::GetSelectedRows(ui->tableWidgetArea,Rows);
	for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		if(Rows.IsInclude(a->Number)==true){
			int	globalPage	=a->GlobalPage;
			int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);

			GUICmdReqAlignmentLargePutPoint	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
			DNewMsg.PointArea	=area;
			DNewMsg.MoveDotX	=MoveDotX;
			DNewMsg.MoveDotY	=MoveDotY;
			DNewMsg.MoveDotX2	=MoveDotX2;
			DNewMsg.MoveDotY2	=MoveDotY2;
			DNewMsg.UsageGlobal	=true;
			DNewMsg.UseBitBuff	=UseBitBuff;
			GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(DNewMsg.PointArea);
			if(DNewMsg.PointArea.GetPatternByte()>9){
				DNewMsg.GlobalPage	=globalPage;
				DNewMsg.AreaID		=a->AreaID;
				DNewMsg.Send(NULL,globalPage ,0);					
			}
		}
	}
	PointList.RemoveAll();

	for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext()){
		CreatePointList(a);
	}
	ShowPointGridRaw();

}
void PropertyAlignmentLargeForm::on_tableWidgetPoint_doubleClicked(const QModelIndex &Index)
{
	int	R=Index.row();
	AlignmentLargePointList *a=PointList.GetItem(R);
	if(a==NULL)
		return;
	InputAlignmentPointForm	D(GetLayersBase(),NULL);
	D.MoveDotX		=a->MoveDotX;
	D.MoveDotY		=a->MoveDotY;
	D.MoveDotX2		=a->MoveDotX2;
	D.MoveDotY2		=a->MoveDotY2;
	D.UsageGlobal	=a->UsageGlobal;
	D.GroupID		=a->GroupID;
	D.UpdateData();
	if(D.exec()==QDialog::Accepted){
		QList<QTableWidgetItem *> Q=ui->tableWidgetPoint->selectedItems ();
		if(Q.count()==0)
			return;
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentLargePointList *a=PointList.GetItem(qi->row());
			if(a==NULL)
				continue;
			int	globalPage	=a->Page;

			QString	EmitterRoot=sRoot;
			QString	EmitterName=sName;
			GUICmdReqAlignmentLargeModifyPoint	DModMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			DModMsg.MoveDotX	=D.MoveDotX;
			DModMsg.MoveDotY	=D.MoveDotY;
			DModMsg.MoveDotX2	=D.MoveDotX2;
			DModMsg.MoveDotY2	=D.MoveDotY2;
			DModMsg.GroupID		=D.GroupID;	
			DModMsg.UsageGlobal	=D.UsageGlobal;
			DModMsg.GlobalPage	=globalPage;
			DModMsg.AreaID		=a->AreaID;
			DModMsg.ItemID		=a->ItemID;
			DModMsg.Send(NULL,globalPage ,0);					
		}
	CreateAndShowPointGrid();
	}
}

void PropertyAlignmentLargeForm::on_tableWidgetArea_doubleClicked(const QModelIndex &Index)
{
	int	R=Index.row();
	AlignmentLargeAreaList *a=AreaList[R];
	if(a!=NULL){
		InputAlignmentAreaForm	D(true,GetLayersBase(),a->AreaName,this);
		D.Reflect(a);
		if(D.exec()==QDialog::Accepted){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Modify AlignmentLarge area");

			QString	EmitterRoot=sRoot;
			QString	EmitterName=sName;
			GUICmdReqModifyAlignmentLargeAreaInfo	DModMsg(GetLayersBase(),EmitterRoot,EmitterName,a->GlobalPage);
			DModMsg.AreaName	=D.AreaName;
			DModMsg.AreaID		=a->AreaID;
			DModMsg.LimitedLib	=D.Libs.SelectedList;
			DModMsg.DeleteMode	=D.DeleteMode;
			DModMsg.Priority	=D.Priority;
			DModMsg.Send(NULL,a->GlobalPage ,0);
		}
		ShowAreaGrid();
	}
}

void	PropertyAlignmentLargeForm::ClearAllAreas(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearAllAreas		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}
void	PropertyAlignmentLargeForm::ClearAllPoints(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearAllPoints		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}
void	PropertyAlignmentLargeForm::CreateAreaInMask(int Priority,int Erosion)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCreateAreaInMask		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Priority	=Priority;
		RCmd.Erosion	=Erosion;
		RCmd.Send(NULL,globalPage,0);
	}
}
void	PropertyAlignmentLargeForm::AutoCreatePoint(int PointSize ,int SearchAreaDot,int SearchAreaDot2)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAutoCreatePoint		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.AlignmntPointSize		=PointSize	;
		RCmd.AlignmntSearchAreaDot	=SearchAreaDot;
		RCmd.AlignmntSearchAreaDot2	=SearchAreaDot2;
		RCmd.Send(NULL,globalPage,0);
	}
}

void	PropertyAlignmentLargeForm::SelectAreaByPriority(int AreaPriority)
{
	IntList	SelectedRows;
	int	Row=0;
	for(AlignmentLargeAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->Priority==(XAlignmentLargeArea::_EnumPriority)AreaPriority){
			SelectedRows.Add(Row);
		}
	}
	::SetSelectedRows(ui->tableWidgetArea,SelectedRows);
	ShowPointList();
	BroadcastShowInEdit();
}

void PropertyAlignmentLargeForm::on_tableWidgetArea_clicked(const QModelIndex &index)
{
	ShowPointList();
	BroadcastShowInEdit();
}
void PropertyAlignmentLargeForm::ShowPointList(void)
{
	if(ui->toolButtonPoint->isChecked()==true){
		int	Row=ui->tableWidgetArea->currentRow();
		if(Row<0){
			PointList.RemoveAll();
			ShowPointGridRaw();
			return;
		}
		AlignmentLargeAreaList	*AL=AreaList[Row];
		if(AL==NULL)
			return;
		int	CurrentPage=AL->GlobalPage;

		IntList	ShouldSelect;
		IntList	Rows;
		::GetSelectedRows(ui->tableWidgetArea ,Rows);
		for(IntClass *p=Rows.GetFirst();p!=NULL;p=p->GetNext()){
			AlignmentLargeAreaList	*BL=AreaList[p->GetValue()];
			if(BL!=NULL){
				if(BL->GlobalPage==CurrentPage){
					ShouldSelect.Add(p->GetValue());
				}
			}
		}
		SetSelectedRows(ui->tableWidgetArea ,ShouldSelect);
	}
	CmdSetImageLayer	LCmd(GetLayersBase());

	CreateAndShowPointGrid();

	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetActiveAreas	RCmd(GetLayersBase(),sRoot,sName,globalPage);

		QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentLargeAreaList *a=AreaList.GetItem(qi->row());
			if(a==NULL)
				continue;
			ReqAlignmentLargeAreaList	*qa=new ReqAlignmentLargeAreaList();
			qa->AreaID		=a->AreaID;
			qa->GlobalPage	=a->GlobalPage;
			LCmd.LayerList.Add(0);
			RCmd.ActiveAreas.AppendList(qa);
		}
		RCmd.SendOnly(globalPage,0);
	}
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL){
		//GProp->TransmitDirectly(&LCmd);
	}
}
GUIFormBase	*PropertyAlignmentLargeForm::GetImageControlToolsPointer(void)
{
	GUIFormBase *RetGUI[1000];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button" ,/**/"ImageControlTools" ,RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));

	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentLargeImagePanel" ,/**/"");
	if(ImagePanel==NULL)
		return NULL;
	QString	ImageName=ImagePanel->GetName();

	for(int i=0;i<N;i++){
		ImageControlTools	*p=dynamic_cast<ImageControlTools *>(RetGUI[i]);
		if(p!=NULL){
			if(p->RelatedPanels.contains(ImageName)==true){
				return p;
			}
		}
	}
	return NULL;
}
bool	PropertyAlignmentLargeForm::GetUseBitBuffMode(void)
{
	if(ImageControlToolsPointer==NULL)
		return false;
	CmdReqImageLayer	RCmd(GetLayersBase(),GetLayerNumb());
	ImageControlToolsPointer->TransmitDirectly(&RCmd);
	if(RCmd.DType==DisplayImage::__BitBuff)
		return true;
	else
		return false;
}


void PropertyAlignmentLargeForm::on_pushButtonGrouping_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeMakeGroup	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}

void PropertyAlignmentLargeForm::on_pushButtonUngrouping_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeRemoveGroup	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
}

void PropertyAlignmentLargeForm::on_pushButtonCombination_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqAlignmentLargeMakeGroup	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,1);
	}
}

void PropertyAlignmentLargeForm::on_tableWidgetPoint_clicked(const QModelIndex &MIndex)
{
	AlignmentLargePointList *L=PointList.GetItem(MIndex.row());
	if(L==NULL)
		return;
		
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(L->Page);
	GUICmdReqAlignmentLargeAngleList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	GUICmdAckAlignmentLargeAngleList	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
	RCmd.ItemID=L->ItemID;
	if(RCmd.Send(GlobalPage,0,ACmd)==true){
		ui->comboBoxAngle->clear();
		AngleList=ACmd.AngleList;
		for(DoubleClass *d=AngleList.GetFirst();d!=NULL;d=d->GetNext()){
			ui->comboBoxAngle->addItem(QString::number(360.0/(2*M_PI)*d->GetValue(),'f',2));
		}
	}

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentLargeImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,L->Cx-L->XSize/2+P->GetOutlineOffset()->x,L->Cy-L->YSize/2+P->GetOutlineOffset()->y
										,L->Cx+L->XSize/2+P->GetOutlineOffset()->x,L->Cy+L->YSize/2+P->GetOutlineOffset()->y);
			GProp->TransmitDirectly(&Cmd);
		}
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyAlignmentLargeForm::on_pushButtonEditLibrary_clicked()
{
	EditAlignmentLargeLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyAlignmentLargeForm::on_pushButtonSelectAll_clicked()
{
	QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
	if(Q.count()==0){
		IntList Rows;
		int	RowCount=ui->tableWidgetArea->rowCount();
		
		for(int r=0;r<RowCount;r++){
			Rows.Add(r);
		}
		::SetSelectedRows(ui->tableWidgetArea,Rows);
	}
	else{
		IntList Rows;
		::SetSelectedRows(ui->tableWidgetArea,Rows);
	}
	//ShowPointList();
	CreateAndShowPointGrid();
	BroadcastShowInEdit();
}
	
void	PropertyAlignmentLargeForm::SetAreaMode(void)
{
	ui->toolButtonArea->setChecked(true);
	on_toolButtonArea_clicked();
}

void	PropertyAlignmentLargeForm::SetPointMode(void)
{
	ui->toolButtonPoint->setChecked(true);
	on_toolButtonPoint_clicked();
}

void PropertyAlignmentLargeForm::on_comboBoxAngle_currentIndexChanged(int index)
{
	BroadcastRepaintAll();
}
