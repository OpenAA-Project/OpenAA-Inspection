#include "AddAreaDialogResource.h"
#include "PropertyTreeMasterForm.h"
#include "ui_PropertyTreeMasterForm.h"
#include "EditCatItemDialog.h"
#include "AddAreaDialog.h"
#include "SelectShapeTypeDialog.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include <QMenu>

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyTreeMasterForm::PropertyTreeMasterForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::PropertyTreeMasterForm)
{
    ui->setupUi(this);

	ui->tableWidgetCatList->setColumnWidth (0,45);
	ui->tableWidgetCatList->setColumnWidth (1,100);
	ui->tableWidgetCatList->setColumnWidth (2,64);
	ui->tableWidgetCatList->setColumnWidth (3,100);
	ui->tableWidgetCatList->setColumnWidth (4,40);

}

PropertyTreeMasterForm::~PropertyTreeMasterForm()
{
    delete ui;
}

TreeMasterBase	*PropertyTreeMasterForm::GetTreeMasterBase(void)
{
	return (TreeMasterBase *)GetLayersBase()->GetAlgorithmBase(/**/"Classify",/**/"TreeMaster");
}

void	PropertyTreeMasterForm::BuildForShow(void)
{
	ShowGridList();
}

void	PropertyTreeMasterForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdTreeMasterDrawEnd	*de=dynamic_cast<CmdTreeMasterDrawEnd *>(packet);
	if(de!=NULL){
		int	Row=ui->tableWidgetCatList->currentRow();
		if(Row<0)
			return;
		TreeMasterList *a=TreeMasterInfo[Row];
		if(a==NULL){
//			return;
//		
//		TreeMasterList *a=TreeMasterInfo.FindByMasterCode(GetLayersBase()->GetMasterCode());
//		if(a==NULL){
			QMessageBox::information(0,/**/"Dialog",LangSolver.GetString(PropertyTreeMasterForm_LS,LID_22)/*"You must make the category before drawing. (「Edit」→「New」） "*/,QMessageBox::Close);
			return;
		}
		ImagePointerContainer Images;
		int Page = GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(de->GlobalArea);
		DataInPage *page = GetLayersBase()->GetPageData(Page);
		page->GetMasterImages(Images);
		ColorLogic CLogic;
		FlexArea area(de->GlobalArea);
		page->ClipMoveAreaFromGlobal(area); // page対応
		area.CreateColorLogic(Images,CLogic);
		QColor Color(CLogic.GetFirstBase()->GetCenter());

		/*AddAreaDialog	D(Color,GetLayersBase());
		if(D.exec()==false)
			return;*/
		SelectShapeTypeDialog	SelectD(GetLayersBase());
		int	Selection=SelectD.exec();
		if(Selection<0)
			return;
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(de->GlobalArea,PageList);
		if(PageList.GetFirst()==NULL)
			return;
		for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
			int	globalPage=PageClass->GetValue();
			FlexArea	A;
			A=de->GlobalArea;
			GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);

			GUICmdAddTreeMasterArea	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.TMItemID		=a->ItemID;
			RCmd.Area			=A;
			RCmd.MasterCode		=a->MasterCode;
			QString	CatName		=a->CatName;
			QString MasterName	=a->MasterName;
			RCmd.TreeMasterColor = Color;
			RCmd.Selection		=Selection;
			RCmd.ThreShape	=SelectD.ThreShape;
			RCmd.ThreColor	=SelectD.ThreColor;
			RCmd.SearchDot	=SelectD.SearchDot;
			//RCmd.TreeMasterColor=D.Color;
			RCmd.Send(NULL,globalPage,0);
		}
		return;
	}
	CmdTreeReqSelectedMasterCode	*CmdTreeReqSelectedMasterCodeVar=dynamic_cast<CmdTreeReqSelectedMasterCode *>(packet);
	if(CmdTreeReqSelectedMasterCodeVar!=NULL){
		int	Row=ui->tableWidgetCatList->currentRow();
		TreeMasterList *a=TreeMasterInfo[Row];
		if(a!=NULL){
			CmdTreeReqSelectedMasterCodeVar->SelectedMasterCode=a->MasterCode;
		}
		else{
			CmdTreeReqSelectedMasterCodeVar->SelectedMasterCode=-1;
		}
		return;
	}
}

void	PropertyTreeMasterForm::ShowInEdit(void)
{
	ShowGridList();
}

void PropertyTreeMasterForm::on_pushButtonAddNewCat_clicked()
{
	int	MaxTMItemID=0;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqMaxTMItemID	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdAckMaxTMItemID	ACmd(GetLayersBase(),sRoot,sName,globalPage);
		if(RCmd.Send(globalPage,0,ACmd)==true){
			if(MaxTMItemID<ACmd.TMItemID){
				MaxTMItemID=ACmd.TMItemID;
			}
		}
	}
	MaxTMItemID++;

	EditCatItemDialog	D(MaxTMItemID,GetLayersBase(),ui->tableWidgetCatList);
	if(D.exec()==true){
		QTableWidget *Src = D.getTable();
		QTableWidget *Dst = ui->tableWidgetCatList;

		for(int rowSrc=0;rowSrc<Src->rowCount();rowSrc++){
			bool	Found=false;
			for(int row=0;row<Dst->rowCount();row++){
				if(Dst->item(row,2)!=NULL && Src->item(rowSrc,2)!=NULL){
					if(Dst->item(row,2)->text()==Src->item(rowSrc,2)->text()){
						Found=true;
						break;
					}
				}
			}
			if(Found==false){
				//追加
				for(int page=0;page<GetParamGlobal()->PageNumb;page++){
					int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
					GUICmdAddTreeMaster	RCmd(GetLayersBase(),sRoot,sName,globalPage);
					RCmd.TMItemID	=Src->item(rowSrc,0)->text().toInt();
					RCmd.CatName	=Src->item(rowSrc,1)->text();
					RCmd.MasterCode	=Src->item(rowSrc,2)->text().toInt();
					RCmd.MasterName =Src->item(rowSrc,3)->text();
					RCmd.AlertMark	=(Src->item(rowSrc,4)->text()==/**/"")?false:true;
					RCmd.Send(NULL,globalPage,0);
				}
			}
		}
		for(int row=0;row<Dst->rowCount();row++){
			bool	Found=false;
			for(int rowSrc=0;rowSrc<Src->rowCount();rowSrc++){
				if(Dst->item(row,2)!=NULL && Src->item(rowSrc,2)!=NULL){
					if(Dst->item(row,2)->text()==Src->item(rowSrc,2)->text()){
						Found=true;
						break;
					}
				}
			}
			if(Found==false){
				//削除
				for(int page=0;page<GetParamGlobal()->PageNumb;page++){
					int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
					GUICmdRemoveItem Cmd(GetLayersBase(),sRoot,sName,globalPage);
					Cmd.MasterCode = Dst->item(row,2)->text().toInt();
					Cmd.Send(NULL,globalPage,0);
				}
				TreeMasterList *Info = TreeMasterInfo.FindByMasterCode(Dst->item(row,2)->text().toInt());
				if(Info!=NULL){
					TreeMasterInfo.decreaseID(Info->ItemID);
					TreeMasterInfo.RemoveList(Info);
				}
			}
		}

		//注意喚起
		for(int row=0;row<Dst->rowCount();row++){
			for(int rowSrc=0;rowSrc<Src->rowCount();rowSrc++){
				if(Dst->item(row,2)!=NULL && Src->item(rowSrc,2)!=NULL){
					if(Dst->item(row,2)->text()==Src->item(rowSrc,2)->text()){
						if(Dst->item(row,4)->text()!=Src->item(rowSrc,4)->text()){
							for(int page=0;page<GetParamGlobal()->PageNumb;page++){
								int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
								GUICmdSetAlertTreeMaster	RCmd(GetLayersBase(),sRoot,sName,globalPage);
								RCmd.TMItemID	=Src->item(rowSrc,0)->text().toInt();
								RCmd.MasterCode	=Src->item(rowSrc,2)->text().toInt();
								RCmd.AlertMark	=(Src->item(rowSrc,4)->text()==/**/"")?false:true;
								RCmd.Send(NULL,globalPage,0);
							}
						}
					}
				}
			}
		}

		for(int row=0;row<Src->rowCount();row++){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdSetCategoryName Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.CatName = Src->item(row,1)->text();
				Cmd.MasterCode = Src->item(row,2)->text().toInt();
				Cmd.Send(NULL,page,0);
			}
		}

		for(int row=0;row<Src->rowCount();row++){
			int MasterCode = Src->item(row,2)->text().toInt();
			if(MasterCode==GetLayersBase()->GetMasterCode())
				continue;
			for(int page=0;page<GetPageNumb();page++){
				GUICmdCopyTreeMasterItem Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.MasterSrc = Src->item(row,2)->text().toInt();
				Cmd.MasterDst = MasterCode;
				Cmd.Send(NULL,page,0);
			}
		}
	}
	ShowGridList();
}

int	PointerListFunc(const void *a ,const void *b)
{
	TreeMasterList	**ai=(TreeMasterList **)a;
	TreeMasterList	**bi=(TreeMasterList **)b;
	/*if(ai[0]->ItemID>bi[0]->ItemID){
		return -1;
	}
	if(ai[0]->ItemID<bi[0]->ItemID){
		return 1;
	}*/
	if(ai[0]->ItemID>bi[0]->ItemID){
		return 1;
	}
	if(ai[0]->ItemID<bi[0]->ItemID){
		return -1;
	}

	return 0;
}
void PropertyTreeMasterForm::ShowGridList(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	TreeMasterInfo.RemoveAll();

	GUICmdReqTreeMasterList	**BmpRequester=new GUICmdReqTreeMasterList*[GetParamGlobal()->PageNumb];
	GUICmdSendTreeMasterList	**BmpReceiver=new GUICmdSendTreeMasterList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpRequester[page]	=new GUICmdReqTreeMasterList	(GetLayersBase(),sRoot,sName,globalPage);
		BmpReceiver[page]	=new GUICmdSendTreeMasterList	(GetLayersBase(),sRoot,sName,globalPage);
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			for(TreeMasterList *L=BmpReceiver[page]->TreeMasterInfo.GetFirst();L!=NULL;L=L->GetNext()){
				TreeMasterList *a=TreeMasterInfo.FindByItemID(L->ItemID);
				if(a==NULL){
					TreeMasterList	*d=new TreeMasterList();
					*d=*L;
					TreeMasterInfo.AppendList(d);
				}
			}
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	Numb=TreeMasterInfo.GetNumber();

	TreeMasterList	**PointerList;
	PointerList=new TreeMasterList*[Numb];
	for(int	N=0;N<Numb;N++){
		TreeMasterList *a=TreeMasterInfo.GetFirst();
		TreeMasterInfo.RemoveList(a);
		PointerList[N]=a;
	}
	QSort(PointerList,Numb,sizeof(PointerList[0]),PointerListFunc);
	for(int	N=0;N<Numb;N++){
		TreeMasterInfo.AppendList(PointerList[N]);
	}
	delete	[]PointerList;

	ui->tableWidgetCatList->setRowCount(Numb);
	for(int	N=0;N<Numb;N++){
		TreeMasterList *a=TreeMasterInfo[N];
		::SetDataToTable(ui->tableWidgetCatList,0,N,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidgetCatList,1,N,a->CatName);
		::SetDataToTable(ui->tableWidgetCatList,2,N,QString::number(a->MasterCode));
		::SetDataToTable(ui->tableWidgetCatList,3,N,a->MasterName);
		::SetDataToTable(ui->tableWidgetCatList,4,N,(a->AlertMask==true)?/**/"●":/**/"");
	}

	ReEntrant=false;
}

void PropertyTreeMasterForm::on_tableWidgetCatList_clicked(const QModelIndex &index)
{
	/*
	int	Row=ui->tableWidgetCatList->currentRow();
	if(Row<0)
		return;
	TreeMasterList *a=TreeMasterInfo[Row];
	if(a==NULL)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqLoadMasterImage	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.MasterCode	=a->MasterCode;
		RCmd.Send(NULL,globalPage,0);
	}
	*/

	QMenu	Menu(this);
	
	Menu.addAction (LangSolver.GetString(PropertyTreeMasterForm_LS,LID_23)/*"選択"*/	, this, SLOT(SlotSelectLine()));
	Menu.addAction (LangSolver.GetString(PropertyTreeMasterForm_LS,LID_24)/*"削除"*/	, this, SLOT(SlotRemoveLine()));
	Menu.addAction (LangSolver.GetString(PropertyTreeMasterForm_LS,LID_25)/*"表示"*/	, this, SLOT(SlotViewLine()));
	QPoint	RCenter(width()/2,height()/2);
	QPoint	Q=mapToGlobal(RCenter);
	Menu.exec(Q);


	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"TreeMasterImagePanel" ,/**/"");
	if(GProp!=NULL){
		GProp->repaint();
	}
}

void PropertyTreeMasterForm::on_tableWidgetCatList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetCatList->currentRow();
	if(Row<0)
		return;
	TreeMasterList *a=TreeMasterInfo[Row];
	if(a==NULL)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSetAlertTreeMaster	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.MasterCode	=a->MasterCode;
		RCmd.AlertMark	=!a->AlertMask;
		RCmd.Send(NULL,globalPage,0);
	}
	ShowGridList();
}

/*
void PropertyTreeMasterForm::mousePressEvent ( QMouseEvent * Ev )
{
	bool	RightClicked	= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
	GUIFormBase::mousePressEvent ( Ev );
	if(RightClicked!=NULL){
		QMenu	Menu(this);
		Menu.addAction ("選択"	, this, SLOT(SlotSelectLine()));
		Menu.addAction ("削除"	, this, SLOT(SlotRemoveLine()));
		Menu.exec();
	}
}
*/
void PropertyTreeMasterForm::SlotSelectLine(void)
{
	int	Row=ui->tableWidgetCatList->currentRow();
	if(Row<0)
		return;
	TreeMasterList *a=TreeMasterInfo[Row];
	if(a==NULL)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSelectItem	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.MasterCode	=a->MasterCode;
		RCmd.Send(NULL,globalPage,0);
	}

	SlotViewLine();
}
void PropertyTreeMasterForm::SlotRemoveLine(void)
{
	int	Row=ui->tableWidgetCatList->currentRow();
	if(Row<0)
		return;
	TreeMasterList *a=TreeMasterInfo[Row];
	if(a==NULL)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdRemoveItem	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.MasterCode	=a->MasterCode;
		RCmd.Send(NULL,globalPage,0);
	
	}
	ShowGridList();
}

void	PropertyTreeMasterForm::SlotViewLine(void)
{
	int	Row=ui->tableWidgetCatList->currentRow();
	if(Row<0)
		return;
	TreeMasterList *a=TreeMasterInfo[Row];
	if(a==NULL)
		return;

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqLoadMasterImage	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.MasterCode	=a->MasterCode;
		RCmd.Send(NULL,globalPage,0);
	}
}