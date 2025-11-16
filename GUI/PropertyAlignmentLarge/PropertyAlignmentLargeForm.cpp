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
#include "ButtonLoadAlgorithm.h"
#include "SelectPriorityInAreaDialog.h"

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
	EnableAreaSelection=true;
	AreaList=NULL;
	LayerNumb=0;
	ui->pushButtonSelectAll->setEnabled(false);

	::SetColumnWidthInTable(ui->tableWidgetHeadAlignment ,0, 47);
	::SetColumnWidthInTable(ui->tableWidgetHeadAlignment ,1, 47);

	InstallIgnoreKeyForChild();
}

PropertyAlignmentLargeForm::~PropertyAlignmentLargeForm()
{
    delete ui;
		
	if(AreaList!=NULL){
		delete	[]AreaList;
		AreaList=NULL;
		LayerNumb=0;
	}
}

AlignmentLargeBase	*PropertyAlignmentLargeForm::GetAlignmentLargeBase(void)
{
	AlignmentLargeBase *BBase=(AlignmentLargeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentLarge");
	return BBase;
}
void	PropertyAlignmentLargeForm::ReadyParam(void)
{
	LayerNumb	=GetLayersBase()->GetMaxLayerNumb();
	AreaList		=new AlignmentLargeAreaListPack[LayerNumb];
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

	GUICmdReqHeadAlignment	RCmd(GetLayersBase(),sRoot,sName,0);
	GUICmdAckHeadAlignment	ACmd(GetLayersBase(),sRoot,sName,0);
	if(RCmd.Send(0,0,ACmd)==true){
		ui->checkBoxUseHeadAlignment->setChecked(ACmd.HeadData.UseHeadAlignment);
		::SetDataToTable(ui->tableWidgetHeadAlignment, 0, 0, QString::number(ACmd.HeadData.SkipHeadAlignmentX),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetHeadAlignment, 0, 1, QString::number(ACmd.HeadData.SkipHeadAlignmentY),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetHeadAlignment, 1, 0, QString::number(ACmd.HeadData.MaxHeadAlignmentX ),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetHeadAlignment, 1, 1, QString::number(ACmd.HeadData.MaxHeadAlignmentY ),Qt::ItemIsEditable);
		ui->spinBoxHeadAlignmentDifColor->setValue(ACmd.HeadData.HeadAlignmentDifColor);
		ui->spinBoxHeadAlignmentMinSize	->setValue(ACmd.HeadData.HeadAlignmentMinSize );
	}
}

bool	PropertyAlignmentLargeForm::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(LayerNumb!=newLayerNumb){
		if(AreaList!=NULL){
			delete	[]AreaList;
			AreaList=NULL;
			LayerNumb=0;
		}
		LayerNumb	=newLayerNumb;
		AreaList		=new AlignmentLargeAreaListPack[LayerNumb];
		ShowAreaGrid();
	}
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

int		PropertyAlignmentLargeForm::GetCurrentLayerNo(void)
{
	if(ImageControlToolsPointer!=NULL){
		LayerNumb	=GetLayersBase()->GetMaxLayerNumb();
		CmdReqImageLayer	RCmd(GetLayersBase(),LayerNumb);
		ImageControlToolsPointer->TransmitDirectly(&RCmd);
		if(RCmd.LayerList.GetFirst()!=NULL){
			return RCmd.LayerList.GetFirst()->GetValue();
		}
	}
	return -1;
}

void	PropertyAlignmentLargeForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
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
		AreaList[CurrentLayerNo].RemoveAll();
		for(int n=0;n<N;n++){
			BmpRequester[n]->CurrentLayer=CurrentLayerNo;
			if(BmpRequester[n]->Send(BmpRequester[n]->GetGlobalPage(),0,*BmpReceiver[n])==true){
				AreaList[CurrentLayerNo]+=BmpReceiver[n]->Area;
			}
		}

		for(int i=0;i<N;i++){
			delete	BmpRequester[i];
			delete	BmpReceiver[i];
		}
		delete	[]BmpRequester;
		delete	[]BmpReceiver;

		AlignmentLargeBase	*BBase=GetAlignmentLargeBase();
		ui->tableWidgetArea->setRowCount(AreaList[CurrentLayerNo].GetNumber());
		N=0;
		for(AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetFirst();a!=NULL;a=a->GetNext(),N++){
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
	GUICmdReqAlignmentLargePointList	 BmpRequester(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	BmpRequester.Layer =A->Layer;
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
		::SetDataToTable(ui->tableWidgetPoint ,2 ,N ,QString::number(a->GroupNumber)
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
	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		AlignmentLargeAreaList	*AL=(AreaList[CurrentLayerNo])[0];
		if(AL==NULL)
			return;

		//IntList	Rows;
		//Rows.Add(0);
		//::SetSelectedRows(ui->tableWidgetArea	,Rows);

		IntList	LayerList;
		LayerList.Add(AL->Layer);
		SetLayersFromLib(LayerList);

		GUICmdClickPointButton	RCmd(GetLayersBase(),sRoot,sName,-1);
		RCmd.InstName=GetName();
		RCmd.SendAllPages(NULL,0);
	}
}

void PropertyAlignmentLargeForm::CreateAndShowPointGrid(void)
{
	QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
	PointList.RemoveAll();
	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(qi->row());
			if(a==NULL)
				continue;
			CreatePointList(a);
		}
		ShowPointGridRaw();
	}
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
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		CmdReqImageLayer	RLayer(GetLayersBase(),LayerNumb);
		GUIFormBase	*GProp=GetImageControlToolsPointer();
		if(GProp!=NULL)
			GProp->TransmitDirectly(&RLayer);

		if(ui->toolButtonArea->isChecked()==true){
			InputAlignmentAreaForm	D(false,GetLayersBase(),/**/"",this);
			if(D.exec()==QDialog::Accepted){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge area");

				for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
					int	LocalPage=PList->GetValue();
					int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

					FlexArea	A=Da->Area;
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
					for(IntClass *dLayer=RLayer.LayerList.GetFirst();dLayer!=NULL;dLayer=dLayer->GetNext()){
						int	layer=dLayer->GetValue();
						if(IsValid(LocalPage ,layer)==true){
							GUICmdReqAlignmentLargePutArea	DNewMsg	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
							GUICmdAckAlignmentLargePutArea	ACmd	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
							DNewMsg.Area		=A;
							DNewMsg.AreaName	=D.AreaName;
							DNewMsg.LimitedLib	=D.Libs.SelectedList;
							DNewMsg.GlobalPage	=globalPage;
							DNewMsg.Layer		=layer;
							DNewMsg.MasterNo	=D.MasterNo;
							DNewMsg.Priority	=D.Priority;
 							DNewMsg.Send(globalPage ,0,ACmd);
						}
					}
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
			int row=ui->tableWidgetArea->rowCount()-1;
			if(row>=0){
				::SetCurrentRow(ui->tableWidgetArea,row);
			}
			on_tableWidgetArea_itemSelectionChanged();
			AreaListFromMaster.RemoveAll();
		}
		else if(ui->toolButtonPoint->isChecked()==true){
			int	CurrentLayerNo=GetCurrentLayerNo();
			if(CurrentLayerNo>=0){
				QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
				if(Q.count()==0)
					return;
				IntList Rows;
				::GetSelectedRows(ui->tableWidgetArea,Rows);
				if(Da->MultiSelect==false && Rows.GetCount()==0)
					return;

				int	CurrentLayerNo=GetCurrentLayerNo();
				if(CurrentLayerNo>=0){
					AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(Rows.GetFirst()->GetValue());
					InputAlignmentPointForm	D(false,a->Priority,GetLayersBase(),NULL);
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
									int	row=Rows.GetFirst()->GetValue();
									AlignmentLargeAreaList	*a=(AreaList[CurrentLayerNo])[row];
									DNewMsg.AreaID.Add(a->AreaID);
									DNewMsg.Layer	=a->Layer;
								}
								else{
									for(IntClass *c=Rows.GetFirst();c!=NULL;c=c->GetNext()){
										int	row=c->GetValue();
										AlignmentLargeAreaList	*a=(AreaList[CurrentLayerNo])[row];
										if(a->GlobalPage==globalPage && a->Layer==CurrentLayerNo){
											DNewMsg.AreaID.Add(a->AreaID);
										}
									}
									DNewMsg.Layer	=CurrentLayerNo;
								}
								if(DNewMsg.AreaID.GetFirst()!=NULL){
									DNewMsg.PointArea			=A;
									DNewMsg.MoveDotX			=D.MoveDotX;
									DNewMsg.MoveDotY			=D.MoveDotY;
									DNewMsg.MoveDotX2			=D.MoveDotX2;
									DNewMsg.MoveDotY2			=D.MoveDotY2;
									DNewMsg.SearchAround		=D.SearchAround;
									DNewMsg.GroupNumber			=D.GroupNumber;		
									DNewMsg.UsageGlobal			=D.UsageGlobal;
									DNewMsg.MultiSelect			=Da->MultiSelect;
									DNewMsg.GlobalPage			=globalPage;
									DNewMsg.UseBitBuff			=UseBitBuff;
									DNewMsg.JudgeWithBrDif		=D.JudgeWithBrDif;
									DNewMsg.CharacterMode 		=D.CharacterMode ;
									DNewMsg.UseLayer			=D.UseLayer		;
									DNewMsg.ThresholdColor		=D.ThresholdColor;	
									DNewMsg.Send(NULL,globalPage ,0);
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
					AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(qi->row());
					if(a==NULL)
						continue;
					CreatePointList(a);
				}
			}
			else{
				PointList.RemoveAll();
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
		int	CurrentLayerNo=GetCurrentLayerNo();
		if(CurrentLayerNo>=0){
			QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
			for(int i=0;i<Q.count();i++){
				QTableWidgetItem *qi=Q.value(i);
				if(qi->column()!=0)
					continue;
				AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(qi->row());
				if(a==NULL)
					continue;
				ReqAlignmentLargeAreaList	*qa=new ReqAlignmentLargeAreaList();
				qa->AreaID		=a->AreaID;
				qa->GlobalPage	=a->GlobalPage;
				qa->Layer		=a->Layer;

				DMode->AList.AppendList(qa);
			}
			DMode->AList+=AreaListFromMaster;
		}
		return;
	}
	GUICmdAlignmentLargeReflectChangeItems	*ReDrawMode=dynamic_cast<GUICmdAlignmentLargeReflectChangeItems *>(packet);
	if(ReDrawMode!=NULL){
		ShowAreaGrid();
		CreateAndShowPointGrid();
		on_tableWidgetArea_itemSelectionChanged();
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
				int	CurrentLayerNo=GetCurrentLayerNo();
				if(CurrentLayerNo>=0){
					IntList	LayerList;
					for(IntClass *p=Rows.GetFirst();p!=NULL;p=p->GetNext()){
						LayerList.Add((AreaList[CurrentLayerNo])[p->GetValue()]->Layer);
					}
					int32		AreaID=(AreaList[CurrentLayerNo])[Rows.GetFirst()->GetValue()]->AreaID;
					XAlignmentLargeArea::_EnumPriority	Priority=(AreaList[CurrentLayerNo])[Rows.GetFirst()->GetValue()]->Priority;
		
					InputAlignmentPointForm	D(false,Priority,GetLayersBase(),NULL);
					if(D.exec()==QDialog::Accepted){
						QBuffer	Buff;
						Buff.open(QIODevice::ReadWrite);
						::Save(&Buff,(int32)2);
						::Save(&Buff,AreaID);
						LayerList.Save(&Buff);
						::Save(&Buff,D.MoveDotX);
						::Save(&Buff,D.MoveDotY);
						::Save(&Buff,D.MoveDotX2);
						::Save(&Buff,D.MoveDotY2);
						::Save(&Buff,D.SearchAround);
						::Save(&Buff,D.GroupNumber);
						::Save(&Buff,D.UsageGlobal);
						::Save(&Buff,D.JudgeWithBrDif);
						::Save(&Buff,D.CharacterMode);
						SAArea->BuffData=Buff.buffer();
					}
				}
			}
		}
		return;
	}
	CmdAlignmentLargeIsModeItemEditingPacket	*CmdIsModeItemEditingPacketVar=dynamic_cast<CmdAlignmentLargeIsModeItemEditingPacket *>(packet);
	if(CmdIsModeItemEditingPacketVar!=NULL){
		if(ui->toolButtonArea->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdAlignmentLargeIsModeItemEditingPacket::_AreaMode;
		else if(ui->toolButtonPoint->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdAlignmentLargeIsModeItemEditingPacket::_ItemMode;
		return;
	}
	CmdSetActiveAreas	*CmdSetActiveAreasVar=dynamic_cast<CmdSetActiveAreas *>(packet);
	if(CmdSetActiveAreasVar!=NULL){
		static	bool	ReEntrant=false;

		if(ReEntrant==false){
			ReEntrant=true;
			ShowAreaGrid();
			int	CurrentLayerNo=GetCurrentLayerNo();
			if(CurrentLayerNo>=0){
				ui->tableWidgetArea->setUpdatesEnabled(false);
				EnableAreaSelection=false;
				for(int r=0;r<ui->tableWidgetArea->rowCount();r++){
					for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
						QTableWidgetItem	*p=ui->tableWidgetArea->item(r,c);
						p->setSelected(false);
					}
				}
				for(ReqAlignmentLargeAreaList *L=CmdSetActiveAreasVar->ActiveAreas.GetFirst();L!=NULL;L=L->GetNext()){
					int	Row=0;
					for(AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetFirst();a!=NULL;a=a->GetNext(),Row++){
						if(L->GlobalPage==a->GlobalPage
						&& L->Layer		==a->Layer
						&& L->AreaID	==a->AreaID){
							for(int c=0;c<ui->tableWidgetArea->columnCount();c++){
								QTableWidgetItem	*p=ui->tableWidgetArea->item(Row,c);
								p->setSelected(true);
							}
						}
					}
				}
				ui->tableWidgetArea->setUpdatesEnabled(true);
				EnableAreaSelection=true;
			}
			AreaListFromMaster=CmdSetActiveAreasVar->ActiveAreas;
			ReEntrant=false;
		}
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
		int	CurrentLayerNo=GetCurrentLayerNo();
		if(CurrentLayerNo>=0){
			IntList	Rows;
			::GetSelectedRows(ui->tableWidgetArea,Rows);
			for(AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetFirst();a!=NULL;a=a->GetNext()){
				if(a->GlobalPage==CmdReqAlignmentLargeSelectedAreaIDVar->Page && Rows.IsInclude(a->Number)==true){
					CmdReqAlignmentLargeSelectedAreaIDVar->AreaIDList.Add(a->AreaID);
				}
			}
		}
		return;
	}
	CmdReqAlignmentLargeAreaListPack	*CmdReqAlignmentLargeAreaListPackVar=dynamic_cast<CmdReqAlignmentLargeAreaListPack *>(packet);
	if(CmdReqAlignmentLargeAreaListPackVar!=NULL){
		CmdReqAlignmentLargeAreaListPackVar->Area=&AreaList[CmdReqAlignmentLargeAreaListPackVar->Layer];
		return;
	}
	CmdSetAlignmentLargeAreaListPackToSlave	*CmdSetAlignmentLargeAreaListPackToSlaveVar=dynamic_cast<CmdSetAlignmentLargeAreaListPackToSlave *>(packet);
	if(CmdSetAlignmentLargeAreaListPackToSlaveVar!=NULL){
		for(AlignmentLargeAreaList *L=AreaList[CmdSetAlignmentLargeAreaListPackToSlaveVar->Layer].GetFirst();L!=NULL;L=L->GetNext()){
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqModifyAlignmentLargeAreaInfo	DModMsg(GetLayersBase(),sRoot,sName,globalPage);
				DModMsg.AreaName	=L->AreaName;
				DModMsg.AreaID		=L->AreaID;
				DModMsg.MasterNo	=L->MasterNo;
				DModMsg.LimitedLib	=L->LimitedLib;
				DModMsg.DeleteMode	=false;
				DModMsg.Layer		=CmdSetAlignmentLargeAreaListPackToSlaveVar->Layer;
				DModMsg.Priority	=L->Priority;
				DModMsg.Send(NULL,globalPage ,0);
			}
		}
		return;
	}
	CmdSetAlignmentData	*CmdSetAlignmentDataVar=dynamic_cast<CmdSetAlignmentData *>(packet);
	if(CmdSetAlignmentDataVar!=NULL){
		ExecuteLoadAlgorithmByData	RCmd(GetLayersBase());
		RCmd.Data=CmdSetAlignmentDataVar->AlignData;
		RCmd.AlgorithmRoot=/**/"Basic";
		RCmd.AlgorithmName=/**/"AlignmentLarge";
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"LoadAlgorithm",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&RCmd);
		}

		return;
	}
	CmdReqAddAlignmentArea	*CmdReqAddAlignmentAreaVar=dynamic_cast<CmdReqAddAlignmentArea *>(packet);
	if(CmdReqAddAlignmentAreaVar!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(CmdReqAddAlignmentAreaVar->Area ,PageList);
		if(PageN<=0)
			return;
		for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
			int	LocalPage=PList->GetValue();
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
			FlexArea	A=CmdReqAddAlignmentAreaVar->Area;
			GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
			
			GUICmdReqAlignmentLargePutArea	DNewMsg	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			GUICmdAckAlignmentLargePutArea	ACmd	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			DNewMsg.Area		=A;
			DNewMsg.AreaName	=CmdReqAddAlignmentAreaVar->AreaName;
			DNewMsg.LimitedLib	=CmdReqAddAlignmentAreaVar->LimitedLib;
			DNewMsg.GlobalPage	=globalPage;
			DNewMsg.Layer		=0;
			DNewMsg.MasterNo	=0;
			DNewMsg.Priority	=CmdReqAddAlignmentAreaVar->Priority;
			if(DNewMsg.Send(globalPage ,0,ACmd)==true){
				CmdReqAddAlignmentAreaVar->GeneratedAreaID=ACmd.GeneratedAreaID;
			}
		}
		return;
	}
	CmdReqAddAlignmentPoint	*CmdReqAddAlignmentPointVar=dynamic_cast<CmdReqAddAlignmentPoint *>(packet);
	if(CmdReqAddAlignmentPointVar!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(CmdReqAddAlignmentPointVar->Area ,PageList);
		if(PageN<=0)
			return;
		for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
			int	LocalPage=PList->GetValue();
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);
			GUICmdReqAlignmentLargePutPoint	DNewMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);

			DNewMsg.AreaID.Add(CmdReqAddAlignmentPointVar->AreaID);

			FlexArea	A=CmdReqAddAlignmentPointVar->Area;
			GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);		
			DNewMsg.PointArea			=A;
			DNewMsg.Layer				=0;
			DNewMsg.MoveDotX			=CmdReqAddAlignmentPointVar->MoveDotX;
			DNewMsg.MoveDotY			=CmdReqAddAlignmentPointVar->MoveDotY;
			DNewMsg.MoveDotX2			=CmdReqAddAlignmentPointVar->MoveDotX;
			DNewMsg.MoveDotY2			=CmdReqAddAlignmentPointVar->MoveDotY;
			DNewMsg.SearchAround		=false;
			DNewMsg.GroupNumber			=0;		
			DNewMsg.UsageGlobal			=false;
			DNewMsg.MultiSelect			=false;
			DNewMsg.GlobalPage			=globalPage;
			DNewMsg.UseBitBuff			=false;
			DNewMsg.UsageGlobal			=false;
			DNewMsg.JudgeWithBrDif		=true;
			DNewMsg.CharacterMode		=false;
			DNewMsg.UseLayer			=-1;
			DNewMsg.ThresholdColor		=-1;	
			DNewMsg.Send(NULL,globalPage ,0);
		}
		return;
	}
	CmdReqDelAlignmentAreaByName	*CmdReqDelAlignmentAreaByNameVar=dynamic_cast<CmdReqDelAlignmentAreaByName *>(packet);
	if(CmdReqDelAlignmentAreaByNameVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqDelAlignmentArea	DDelMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			DDelMsg.AreaName	=CmdReqDelAlignmentAreaByNameVar->AreaName;
			DDelMsg.Send(NULL,globalPage ,0);
		}
		return;
	}
	CmdAutoGenerateMark	*CmdAutoGenerateMarkVar=dynamic_cast<CmdAutoGenerateMark *>(packet);
	if(CmdAutoGenerateMarkVar!=NULL){
		for(ListPhasePageLayerItem *a=CmdAutoGenerateMarkVar->AreaIDList.GetFirst();a!=NULL;a=a->GetNext()){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(a->Data.Page);
			GUICmdGenerateAuto	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.AreaID	=a->Data.ItemID;
			RCmd.Layer	=a->Data.Layer;
			RCmd.SendOnly(globalPage,1);
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
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqImageLayer	RLayer(GetLayersBase(),LayerNumb);
	GUIFormBase	*GProp=GetImageControlToolsPointer();
	if(GProp!=NULL)
		GProp->TransmitDirectly(&RLayer);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge area");

	for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
		int	LocalPage=PList->GetValue();
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

		FlexArea	A=area;
		GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				
		for(IntClass *dLayer=RLayer.LayerList.GetFirst();dLayer!=NULL;dLayer=dLayer->GetNext()){
			int	layer=dLayer->GetValue();
			if(IsValid(LocalPage ,layer)==true){
				GUICmdReqAlignmentLargePutArea	DNewMsg	(GetLayersBase(),sRoot,sName,globalPage);
				GUICmdAckAlignmentLargePutArea	ACmd	(GetLayersBase(),sRoot,sName,globalPage);
				DNewMsg.Area		=A;
				DNewMsg.AreaName	=/**/"";
				DNewMsg.GlobalPage	=globalPage;
				DNewMsg.MasterNo	=0;
				DNewMsg.Layer		=layer;
				DNewMsg.Priority	=XAlignmentLargeArea::_PriorityMiddle;
				DNewMsg.Send(globalPage ,0,ACmd);
			}
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

void	PropertyAlignmentLargeForm::CreateAlignmentPoint(FlexArea &area ,int MoveDotX,int MoveDotY,int MoveDotX2,int MoveDotY2,int SearchAround)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentLarge point");

	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		bool	UseBitBuff=GetUseBitBuffMode();
		IntList	Rows;
		::GetSelectedRows(ui->tableWidgetArea,Rows);
		for(AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetFirst();a!=NULL;a=a->GetNext()){
			if(Rows.IsInclude(a->Number)==true){
				int	globalPage	=a->GlobalPage;
				int	LocalPage	=GetLayersBase()->GetLocalPageFromGlobal(globalPage);

				GUICmdReqAlignmentLargePutPoint	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
				DNewMsg.PointArea			=area;
				DNewMsg.MoveDotX			=MoveDotX;
				DNewMsg.MoveDotY			=MoveDotY;
				DNewMsg.MoveDotX2			=MoveDotX2;
				DNewMsg.MoveDotY2			=MoveDotY2;
				DNewMsg.SearchAround		=SearchAround;
				DNewMsg.UsageGlobal			=true;
				DNewMsg.CharacterMode		=false;
				DNewMsg.UseBitBuff			=UseBitBuff;
				DNewMsg.UseLayer			=-1;
				DNewMsg.ThresholdColor		=-1;	
				GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(DNewMsg.PointArea);
				if(DNewMsg.PointArea.GetPatternByte()>9){
					DNewMsg.GlobalPage=globalPage;
					DNewMsg.Layer	  =a->Layer;
					DNewMsg.AreaID.Add(a->AreaID);
					DNewMsg.Send(NULL,globalPage ,0);					
				}
			}
		}
		PointList.RemoveAll();

		for(AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetFirst();a!=NULL;a=a->GetNext()){
			CreatePointList(a);
		}
		ShowPointGridRaw();
	}
	else{
		PointList.RemoveAll();
		ShowPointGridRaw();
	}
}
void PropertyAlignmentLargeForm::on_tableWidgetPoint_doubleClicked(const QModelIndex &Index)
{
	int	R=Index.row();
	AlignmentLargePointList *a=PointList.GetItem(R);
	if(a==NULL)
		return;

	XAlignmentLargeArea::_EnumPriority	Priority=XAlignmentLargeArea::_PriorityMiddle;
	for(AlignmentLargeAreaList *L=AreaList[a->Layer].GetFirst();L!=NULL;L=L->GetNext()){
		if(L->AreaID==a->AreaID){
			Priority=L->Priority;
			break;
		}
	}

	InputAlignmentPointForm	D(true,Priority,GetLayersBase(),NULL);
	D.MoveDotX		=a->MoveDotX;
	D.MoveDotY		=a->MoveDotY;
	D.MoveDotX2		=a->MoveDotX2;
	D.MoveDotY2		=a->MoveDotY2;
	D.SearchAround	=a->SearchAround;
	D.UsageGlobal	=a->UsageGlobal;
	D.GroupNumber	=a->GroupNumber;
	D.JudgeWithBrDif=a->JudgeWithBrDif;
	D.CharacterMode	=a->CharacterMode;
	D.UseLayer		=a->UseLayer;
	D.ThresholdColor=a->ThresholdColor;
	D.UpdateData();
	if(D.exec()==QDialog::Accepted){
		if(D.DeleteMode==false){
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
				DModMsg.SearchAround=D.SearchAround;	
				DModMsg.GroupNumber	=D.GroupNumber;	
				DModMsg.UsageGlobal	=D.UsageGlobal;
				DModMsg.GlobalPage	=globalPage;
				DModMsg.Layer		=a->Layer;
				DModMsg.AreaID		=a->AreaID;
				DModMsg.ItemID		=a->ItemID;
				DModMsg.JudgeWithBrDif	=D.JudgeWithBrDif	;
				DModMsg.CharacterMode	=D.CharacterMode	;
				DModMsg.UseLayer		=D.UseLayer		;
				DModMsg.ThresholdColor	=D.ThresholdColor	;
				DModMsg.Send(NULL,globalPage ,0);					
			}
		}
		else{
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
				GUICmdReqAlignmentLargeRemovePoint	DDelMsg(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
				DDelMsg.GlobalPage	=globalPage;
				DDelMsg.Layer		=a->Layer;
				DDelMsg.AreaID		=a->AreaID;
				DDelMsg.ItemID		=a->ItemID;
				DDelMsg.Send(NULL,globalPage ,0);					
			}
		}
		CreateAndShowPointGrid();
	}
}

void PropertyAlignmentLargeForm::on_tableWidgetArea_doubleClicked(const QModelIndex &Index)
{
	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		int	R=Index.row();
		AlignmentLargeAreaList *a=(AreaList[CurrentLayerNo])[R];
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
				DModMsg.MasterNo	=D.MasterNo;
				DModMsg.Layer		=a->Layer;
				DModMsg.Priority	=D.Priority;
				DModMsg.Send(NULL,a->GlobalPage ,0);
			}
			on_tableWidgetArea_itemSelectionChanged();
			ShowAreaGrid();
		}
	}
}

void	PropertyAlignmentLargeForm::ClearAllAreas(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearAllAreas		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Send(NULL,globalPage,0);
	}
	ShowAreaGrid();
}
void	PropertyAlignmentLargeForm::ClearAllPoints(int Priority)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdClearAllPoints		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.Priority	=Priority;
		RCmd.Send(NULL,globalPage,0);
	}
	ShowPointList();
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
	ShowAreaGrid();
}
void	PropertyAlignmentLargeForm::AutoCreatePoint(int Layer ,int PointSize 
													,int SearchAreaDotX	,int SearchAreaDotY	
													,int SearchAreaDot2X,int SearchAreaDot2Y
													,int AreaPriority
													,bool GeneratePartialAlignment
													,bool AlignmntJudgeWithBrDif
													,int LimitedLibType ,int LimitedLibID)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdAutoCreatePoint		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.GeneratePartialAlignment	=GeneratePartialAlignment	;
		RCmd.AlignmntPointSize			=PointSize	;
		RCmd.AlignmntSearchAreaDotX		=SearchAreaDotX;
		RCmd.AlignmntSearchAreaDotY		=SearchAreaDotY;
		RCmd.AlignmntSearchAreaDot2X	=SearchAreaDot2X;
		RCmd.AlignmntSearchAreaDot2Y	=SearchAreaDot2Y;
		RCmd.Layer						=Layer;
		RCmd.AreaPriority				=AreaPriority;
		RCmd.LimitedLibType				=LimitedLibType;
		RCmd.LimitedLibID				=LimitedLibID;
		RCmd.AlignmntJudgeWithBrDif		=AlignmntJudgeWithBrDif;
		RCmd.Send(NULL,globalPage,0);
	}
	ShowPointList();
}


void PropertyAlignmentLargeForm::on_tableWidgetArea_clicked(const QModelIndex &index)
{
	on_tableWidgetArea_itemSelectionChanged();
}
void PropertyAlignmentLargeForm::ShowPointList(void)
{
	if(ui->toolButtonPoint->isChecked()==true){
		int	CurrentLayerNo=GetCurrentLayerNo();
		if(CurrentLayerNo>=0){
			int	Row=ui->tableWidgetArea->currentRow();
			if(Row<0){
				PointList.RemoveAll();
				ShowPointGridRaw();
				return;
			}
			AlignmentLargeAreaList	*AL=(AreaList[CurrentLayerNo])[Row];
			if(AL==NULL)
				return;
			int	CurrentPage=AL->GlobalPage;

			IntList	ShouldSelect;
			IntList	LayerList;
			IntList	Rows;
			::GetSelectedRows(ui->tableWidgetArea ,Rows);
			for(IntClass *p=Rows.GetFirst();p!=NULL;p=p->GetNext()){
				AlignmentLargeAreaList	*BL=(AreaList[CurrentLayerNo])[p->GetValue()];
				if(BL!=NULL){
					if(BL->GlobalPage==CurrentPage){
						ShouldSelect.Add(p->GetValue());
						if(LayerList.IsInclude(BL->Layer)==false){
							LayerList.Add(BL->Layer);
						}
					}
				}
			}
			SetSelectedRows(ui->tableWidgetArea ,ShouldSelect);
			SetLayersFromLib(LayerList);
		}
	}
	CmdSetImageLayer	LCmd(GetLayersBase());

	CreateAndShowPointGrid();
	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetActiveAreas	RCmd(GetLayersBase(),sRoot,sName,globalPage);

			QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
			for(int i=0;i<Q.count();i++){
				QTableWidgetItem *qi=Q.value(i);
				if(qi->column()!=0)
					continue;
				AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(qi->row());
				if(a==NULL)
					continue;
				ReqAlignmentLargeAreaList	*qa=new ReqAlignmentLargeAreaList();
				qa->AreaID		=a->AreaID;
				qa->GlobalPage	=a->GlobalPage;
				qa->Layer		=a->Layer;
				LCmd.LayerList.Add(a->Layer);
				RCmd.ActiveAreas.AppendList(qa);
			}
			RCmd.SendOnly(globalPage,0);
		}
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
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqImageLayer	RCmd(GetLayersBase(),LayerNumb);
	ImageControlToolsPointer->TransmitDirectly(&RCmd);
	if(RCmd.DType==DisplayImage::__BitBuff)
		return true;
	else
		return false;
}

void PropertyAlignmentLargeForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentLargeImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
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
	on_tableWidgetPoint_itemSelectionChanged();
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

void PropertyAlignmentLargeForm::on_tableWidgetArea_itemSelectionChanged()
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	if(EnableAreaSelection==false)
		return;
	ReEntrant=true;

	ShowPointList();
	BroadcastShowInEdit();

	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		int	Row=ui->tableWidgetArea->currentRow();
		if(Row>=0){
			AlignmentLargeAreaList	*AL=(AreaList[CurrentLayerNo])[Row];
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentLargeImagePanel" ,/**/"");
			if(GProp!=NULL){
				DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
				di->SetCurrentMasterNo(AL->MasterNo);
				di->Repaint();
			}
		}
	}
	ReEntrant=false;
}


void PropertyAlignmentLargeForm::on_tableWidgetPoint_itemSelectionChanged()
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	row=ui->tableWidgetPoint->currentRow();
	if(row<0){
		ReEntrant=false;
		return;
	}
	AlignmentLargePointList *L=PointList.GetItem(row);
	if(L==NULL){
		ReEntrant=false;
		return;
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
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,L->Layer,L->ID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
	ReEntrant=false;
}


void PropertyAlignmentLargeForm::on_pushButtonSetAlignmentHead_clicked()
{
	GUICmdSetHeadAlignment	SCmd(GetLayersBase(),sRoot,sName,0);
	SCmd.HeadData.UseHeadAlignment	=ui->checkBoxUseHeadAlignment->isChecked();
	SCmd.HeadData.SkipHeadAlignmentX=::GetDataToTable(ui->tableWidgetHeadAlignment, 0, 0).toInt();
	SCmd.HeadData.SkipHeadAlignmentY=::GetDataToTable(ui->tableWidgetHeadAlignment, 0, 1).toInt();
	SCmd.HeadData.MaxHeadAlignmentX	=::GetDataToTable(ui->tableWidgetHeadAlignment, 1, 0).toInt();
	SCmd.HeadData.MaxHeadAlignmentY	=::GetDataToTable(ui->tableWidgetHeadAlignment, 1, 1).toInt();
	SCmd.HeadData.HeadAlignmentDifColor	=ui->spinBoxHeadAlignmentDifColor	->value();
	SCmd.HeadData.HeadAlignmentMinSize	=ui->spinBoxHeadAlignmentMinSize	->value();
	SCmd.Send(NULL,0,0);
}

void	PropertyAlignmentLargeForm::DeleteAreaExceptGlobal(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdDeleteAreaExceptGlobal	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.SendOnly(globalPage,1);
	}
}

void	PropertyAlignmentLargeForm::DeleteItemsExceptGlobal(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdDeleteItemsExceptGlobal	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.SendOnly(globalPage,1);
	}
}

void PropertyAlignmentLargeForm::on_pushButtonGenerate_clicked()
{
	int	AreaID=-1;
	int	globalPage=-1;
	int	Layer=-1;
	QList<QTableWidgetItem *> Q=ui->tableWidgetArea->selectedItems ();
	PointList.RemoveAll();
	int	CurrentLayerNo=GetCurrentLayerNo();
	if(CurrentLayerNo>=0){
		for(int i=0;i<Q.count();i++){
			QTableWidgetItem *qi=Q.value(i);
			if(qi->column()!=0)
				continue;
			AlignmentLargeAreaList *a=AreaList[CurrentLayerNo].GetItem(qi->row());
			if(a==NULL)
				continue;
			AreaID		=a->AreaID;
			globalPage	=a->GlobalPage;
			Layer		=a->Layer;
			break;
		}
	}
	if(AreaID>=0){
		GUICmdGenerateAuto	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.AreaID	=AreaID;
		RCmd.Layer	=Layer;
		RCmd.SendOnly(globalPage,1);
	}
	CreateAndShowPointGrid();
	//ShowPointGridRaw();
}


void PropertyAlignmentLargeForm::on_pushButtonGenerateAreaFromMask_clicked()
{
	SelectPriorityInAreaDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqMakeAreaFromMask	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.AreaPriority.Add((int)D.Priority);
			RCmd.SendOnly(globalPage,1);
		}
	}
}

