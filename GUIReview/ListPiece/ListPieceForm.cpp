#include "ListPieceForm.h"
#include "ui_ListPieceForm.h"
#include "ReviewStructureItems.h"
#include "ReviewStructurePacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../ShowHistoryListForReview/ShowHistoryListForReviewPacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "XGeneralFunc.h"

int	AreaList::Compare(AreaList &src)
{
	bool	COk1;
	int	NumColumn1=Column.toInt(&COk1);
	bool	ROk1;
	int	NumRow1	 =Row.toInt(&ROk1);
	bool	COk2;
	int	NumColumn2=src.Column.toInt(&COk2);
	bool	ROk2;
	int	NumRow2	 =src.Row.toInt(&ROk2);
	if(ROk1==true && ROk2==true){
		if(NumRow1<NumRow2)
			return -1;
		if(NumRow1>NumRow2)
			return 1;
	}
	else{
		int	d=Row.compare(src.Row);
		if(d<0)
			return -1;
		if(d>0)
			return 1;
	}
	if(COk1==true && COk2==true){
		if(NumColumn1<NumColumn2)
			return -1;
		if(NumColumn1>NumColumn2)
			return 1;
	}
	else{
		int	d=Column.compare(src.Column);
		if(d<0)
			return -1;
		if(d>0)
			return 1;
	}
	int	d=AreaName.compare(src.AreaName);
	if(d<0)
		return -1;
	if(d>0)
		return 1;
	return 0;
}

void	AreaListContainer::MergeArea(QString &aname)
{
	QString	AreaS=aname;
	QStringList	LListS=AreaS.split(',');
	AreaS=LListS[0];
	for(AreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AreaName==AreaS)
			return;
	}
	AreaList	*a=new AreaList();
	a->AreaName=AreaS;
	AppendList(a);
}
QStringList	AreaListContainer::MakeAreaList(void)
{
	QStringList	L;
	for(AreaList *a=GetFirst();a!=NULL;a=a->GetNext()){
		L.append(a->AreaName);
	}
	return L;
}

ListPieceForm::ListPieceForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::ListPieceForm)
{
    ui->setupUi(this);

	ui->tableWidgetPiece->setColumnWidth(0,24);
	ui->tableWidgetPiece->setColumnWidth(1,40);
	ui->tableWidgetPiece->setColumnWidth(2,40);
	ui->tableWidgetPiece->setColumnWidth(3,100);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ListPieceForm::~ListPieceForm()
{
    delete ui;
}


void	ListPieceForm::ResizeAction(void)
{
	ui->tableWidgetPiece->resize(width(),height());
	ui->tableWidgetPiece->setColumnWidth(3,width()-130);
}

void ListPieceForm::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		UpdateList();
		return;
	}
	GUICmdSetCurrentFocusOnNail	*GUICmdSetCurrentFocusOnNailVar=dynamic_cast<GUICmdSetCurrentFocusOnNail *>(packet);
	if(GUICmdSetCurrentFocusOnNailVar!=NULL){
		int	Row=0;
		for(AreaList *a=FrontList.GetFirst();a!=NULL;a=a->GetNext()){
			if(GUICmdSetCurrentFocusOnNailVar->Side==Review::Front
			&& a->AreaName==GUICmdSetCurrentFocusOnNailVar->PieceName){
				ui->tableWidgetPiece->setCurrentCell(Row,0);
				break;
			}
			Row++;
		}
	
		for(AreaList *a=BackList.GetFirst();a!=NULL;a=a->GetNext()){
			if(GUICmdSetCurrentFocusOnNailVar->Side==Review::Back
			&& a->AreaName==GUICmdSetCurrentFocusOnNailVar->PieceName){
				ui->tableWidgetPiece->setCurrentCell(Row,0);
				break;
			}
			Row++;
		}
		return;
	}
	GUICmdReqAreaList	*GUICmdReqAreaListVar=dynamic_cast<GUICmdReqAreaList *>(packet);
	if(GUICmdReqAreaListVar!=NULL){
		if(GUICmdReqAreaListVar->Side==Review::Front){
			GUICmdReqAreaListVar->PieceList=FrontList.MakeAreaList();
		}
		if(GUICmdReqAreaListVar->Side==Review::Back){
			GUICmdReqAreaListVar->PieceList=BackList.MakeAreaList();
		}
		GUICmdReqAreaListVar->Ret=true;
		return;
	}
}

void	ListPieceForm::UpdateList(void)
{
	OrganizedHistoryIndex orgHistoryPtr=NULL;
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqCurrentHistory Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			orgHistoryPtr=Send.historyPrt();
		}
	}
	CmdReqPCEList reqPCECmd(GetLayersBase());
	RBase->TransmitDirectly(&reqPCECmd);
	PCEList FrontPceList = reqPCECmd.FrontList;
	PCEList BackPceList  = reqPCECmd.BackList;

	FrontList.RemoveAll();
	BackList.RemoveAll();
	if(orgHistoryPtr!=NULL){
		if(orgHistoryPtr->hasFront()==true && orgHistoryPtr->getFront()->getNGNails().count()>0){
			// サムネイルアイテム作成
			HistoryIndex FHistory = orgHistoryPtr->getFront();
			for(int i=0; i<FHistory->getNGNails().count(); i++){
				QString	Area=FHistory->getNGNails()[i].getArea();
				if(FHistory->getNGNails()[i].phase==0)
					FrontList.MergeArea(Area);
				else
					BackList.MergeArea(Area);
			}
		}
		if(orgHistoryPtr->hasBack()==true && orgHistoryPtr->getBack()->getNGNails().count()>0){
			// サムネイルアイテム作成
			HistoryIndex BHistory = orgHistoryPtr->getBack();
			for(int i=0; i<BHistory->getNGNails().count(); i++){
				QString	Area=BHistory->getNGNails()[i].getArea();
				BackList.MergeArea(Area);
			}
		}
	}
	for(AreaList *a=FrontList.GetFirst();a!=NULL;a=a->GetNext()){
		a->Front =0;
		if(a->AreaName.isEmpty()==false){
			QStringList	CName=a->AreaName.split(',');
			QStringList	CList=CName[0].split('-');
			a->Column=CList[1];
			a->Row	 =CList[2];
			a->AreaName=CName[0];
		}
	}
	for(AreaList *a=BackList.GetFirst();a!=NULL;a=a->GetNext()){
		a->Front =1;
		if(a->AreaName.isEmpty()==false){
			QStringList	CName=a->AreaName.split(',');
			QStringList	CList=CName[0].split('-');
			a->Column=CList[1];
			a->Row	 =CList[2];
			a->AreaName=CName[0];
		}
	}

	FrontList.Sort();
	BackList.Sort();

	int	N=FrontList.GetCount() + BackList.GetCount();
	ui->tableWidgetPiece->setRowCount(N);

	int	Row=0;
	for(AreaList *a=FrontList.GetFirst();a!=NULL;a=a->GetNext()){
		SetDataToTable(ui->tableWidgetPiece ,0 ,Row ,/**/"F");
		SetDataToTable(ui->tableWidgetPiece ,1 ,Row ,a->Row);
		SetDataToTable(ui->tableWidgetPiece ,2 ,Row ,a->Column);
		SetDataToTable(ui->tableWidgetPiece ,3 ,Row ,a->AreaName);
		Row++;
	}
	for(AreaList *a=BackList.GetFirst();a!=NULL;a=a->GetNext()){
		SetDataToTable(ui->tableWidgetPiece ,0 ,Row ,/**/"B");
		SetDataToTable(ui->tableWidgetPiece ,1 ,Row ,a->Row);
		SetDataToTable(ui->tableWidgetPiece ,2 ,Row ,a->Column);
		SetDataToTable(ui->tableWidgetPiece ,3 ,Row ,a->AreaName);
		Row++;
	}
}

void ListPieceForm::on_tableWidgetPiece_clicked(const QModelIndex &index)
{
	GUIFormBase *GUIForm = GetLayersBase()->FindByName(/**/"Review", /**/"ShowThumbnail", "");
	if(GUIForm!=NULL){
		GUICmdSetCurrentNGNailPageTop	UpdateCmd(GetLayersBase());
		int	n=ui->tableWidgetPiece->currentRow();
		if(n>=FrontList.count()){
			n-=FrontList.count();
			UpdateCmd.Side=Review::Back;
			UpdateCmd.PieceName=BackList[n]->AreaName;
		}
		else{
			UpdateCmd.Side=Review::Front;
			UpdateCmd.PieceName=FrontList[n]->AreaName;
		}
		GUIForm->TransmitDirectly(&UpdateCmd);
	}
}