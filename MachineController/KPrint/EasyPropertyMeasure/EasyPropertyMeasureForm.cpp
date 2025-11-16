#include "EasyPropertyMeasureResource.h"
#include "EasyPropertyMeasureForm.h"
#include "ui_EasyPropertyMeasureForm.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "XMeasureLineMove.h"
#include "EasyMeasureImagePanel.h"
#include "InputPanelDialog.h"
#include "SetSearchDotDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

MeasurePointButton::MeasurePointButton(void)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setCheckable(true);
	setStyleSheet(/**/"QPushButton {\n	border-style: outset;\n	border-width: 1px;\n	"
				/**/"border-radius: 20px;\n	border-color: gray;\n	"
				/**/"background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1,stop:0 rgba(160, 160, 160, 255), stop:1 rgba(120, 120, 120, 255));\n"
				/**/"}\n"
				/**/"QPushButton:checked { 	\n	"
				/**/"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(180, 0, 0, 255));\n}");

}
void	MeasurePointButton::SlotClicked()
{
	emit	SignalClicked(EndNo , MeasureNo);
}

//===============================================================

MeasureResultInMachine::MeasureResultInMachine(void)
{	
	CountingPoint	=0;
	AllocatedResultCount	=MaxCountTotalResultDim;
	ResultDim	=new MeasureResult[AllocatedResultCount];
	ResultCount		=0;
	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].InspectionID=0;
	}
	NGCount	=0;
}
MeasureResultInMachine::MeasureResultInMachine(const MeasureResultInMachine &src)
{
	CountingPoint		=src.CountingPoint;
	AllocatedResultCount=src.AllocatedResultCount;
	ResultDim			=new MeasureResult[AllocatedResultCount];
	ResultCount			=src.ResultCount			;
	NGCount				=src.NGCount				;
	memcpy(ResultDim,src.ResultDim,sizeof(ResultDim[0])*ResultCount);
	memcpy(UniqueIndexData,src.UniqueIndexData,sizeof(UniqueIndexData));
}

MeasureResultInMachine::~MeasureResultInMachine(void)
{
	if(ResultDim!=NULL){
		delete	[]ResultDim;
		ResultDim		=NULL;
	}
	ResultCount			=0;
	AllocatedResultCount=0;
	NGCount		=0;
}

MeasureResultInMachine	&MeasureResultInMachine::operator=(const MeasureResultInMachine &src)
{
	CountingPoint		=src.CountingPoint;
	AllocatedResultCount=src.AllocatedResultCount;
	if(ResultDim!=NULL){
		delete	[]ResultDim;
		ResultDim		=NULL;
	}
	ResultDim			=new MeasureResult[AllocatedResultCount];
	ResultCount			=src.ResultCount			;
	NGCount				=src.NGCount				;
	memcpy(ResultDim,src.ResultDim,sizeof(ResultDim[0])*ResultCount);
	memcpy(UniqueIndexData,src.UniqueIndexData,sizeof(UniqueIndexData));
	return *this;
}

void	MeasureResultInMachine::SetResultPage(InspectionList *n)
{
	if(ResultCount<AllocatedResultCount){
		bool	NGFlag=false;
		for(NGPointInAllPage *Ph=n->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
			for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
				for(NGPoint *p=Pg->NPListPack<NGPoint>::GetFirst();p!=NULL;p=p->GetNext()){
					if(p->LibType==DefLibTypeMeasureLineMove){
						int	Index=-1;
						for(int i=0;i<MaxCountOfMeasureResult;i++){
							if(UniqueIndexData[i].Phase==Ph->Phase
							&& UniqueIndexData[i].Page ==Pg->Page
							&& UniqueIndexData[i].ItemID==p->UniqueID){
								Index=i;
								break;
							}
						}
						if(Index<0){
							for(int i=0;i<MaxCountOfMeasureResult;i++){
								if(UniqueIndexData[i].Phase<0
								&& UniqueIndexData[i].Page <0
								&& UniqueIndexData[i].ItemID<0){
									UniqueIndexData[i].Phase	=Ph->Phase;
									UniqueIndexData[i].Page		=Pg->Page;
									UniqueIndexData[i].ItemID	=p->UniqueID;
									Index=i;
									break;
								}
							}
						}
						if(Index>=0){
							ResultDim[ResultCount].InspectionID	=n->ID;
							ResultDim[ResultCount].ResultDouble[Index]=p->DoubleCause;
							if(p->Error>1){
								NGFlag=true;
							}
						}
					}
				}
			}
		}
		if(NGFlag==true){
			NGCount++;
		}
		ResultCount++;
	}
}
void	MeasureResultInMachine::RemoveAll(void)
{
	CountingPoint=0;

	for(int i=0;i<AllocatedResultCount;i++){
		ResultDim[i].InspectionID=0;
	}
	ResultCount	=0;

	for(int i=0;i<MaxCountOfMeasureResult;i++){
		UniqueIndexData[i].Phase	=-1;
		UniqueIndexData[i].Page		=-1;
		UniqueIndexData[i].ItemID	=-1;
	}
}

//===============================================================
EasyPropertyMeasureForm::EasyPropertyMeasureForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::EasyPropertyMeasureForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SlaveNo	=0;
	DrawMode=0;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

EasyPropertyMeasureForm::~EasyPropertyMeasureForm()
{
    delete ui;
}

void	EasyPropertyMeasureForm::ResizeAction()
{
}
	
void	EasyPropertyMeasureForm::Prepare(void)
{
	MeasureResultData.RemoveAll();
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalDoneLoadResult(InspectionList *)),this,SLOT(SlotDoneLoadResult(InspectionList *)));

	SetColumnWidthInTable(ui->tableWidgetList ,0, 20);
	SetColumnWidthInTable(ui->tableWidgetList ,1, 20);
	SetColumnWidthInTable(ui->tableWidgetList ,2, 20);
	SetColumnWidthInTable(ui->tableWidgetList ,3, 20);
	SetColumnWidthInTable(ui->tableWidgetList ,4, 20);
	ShowList();
}

void	EasyPropertyMeasureForm::BuildForShow(void)
{
	ShowList();
}

void	EasyPropertyMeasureForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddDistance	*CmdAddDistanceVar=dynamic_cast<CmdAddDistance *>(packet);
	if(CmdAddDistanceVar!=NULL){
		IntegrationCmdAddDistance	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LocalX1		=CmdAddDistanceVar->X1		;
		RCmd.LocalY1		=CmdAddDistanceVar->Y1		;
		RCmd.LocalX2		=CmdAddDistanceVar->X2		;
		RCmd.LocalY2		=CmdAddDistanceVar->Y2		;
		RCmd.LineLength		=CmdAddDistanceVar->LineLength		;
		RCmd.LineLibID1		=CmdAddDistanceVar->LineLibID1		;
		RCmd.LineLibID2		=CmdAddDistanceVar->LineLibID2		;
		RCmd.DistanceLibID	=CmdAddDistanceVar->DistanceLibID	;

		RCmd.Send(NULL,SlaveNo,0);
		ShowList();
		return;
	}
	CmdSetEndPointDistance	*CmdSetEndPointDistanceVar=dynamic_cast<CmdSetEndPointDistance *>(packet);
	if(CmdSetEndPointDistanceVar!=NULL){
		IntegrationCmdSetMeasureDistanceEndPoint	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(DrawMode==1){
			RCmd.EndNo		=0;
			RCmd.MeasureNo	=CurrentMeasureNo;
			RCmd.GlobalX	=CmdSetEndPointDistanceVar->GlobalX;
			RCmd.GlobalY	=CmdSetEndPointDistanceVar->GlobalY;
			RCmd.Send(NULL,SlaveNo,0);
		}
		else if(DrawMode==2){
			RCmd.EndNo		=1;
			RCmd.MeasureNo	=CurrentMeasureNo;
			RCmd.GlobalX	=CmdSetEndPointDistanceVar->GlobalX;
			RCmd.GlobalY	=CmdSetEndPointDistanceVar->GlobalY;
			RCmd.Send(NULL,SlaveNo,0);
		}
		return;
	}
}

void	EasyPropertyMeasureForm::SlotDoneLoadResult(InspectionList *n)
{
	if(n!=NULL){
		EachMaster	*m=n->GetMaster();
		if(m->GetIntegrationSlaveNo()==SlaveNo){
			MeasureResultData.SetResultPage(n);
		}
	}
	else{
		MeasureResultData.RemoveAll();
	}
}


void	EasyPropertyMeasureForm::ShowList(void)
{
	IntegrationCmdReqListData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationCmdAckListData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		ListData=ACmd.ListData;
		ui->tableWidgetList->setRowCount(ListData.GetCount());
		int	Row=0;
		EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(ThisM!=NULL){
			for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				::SetDataToTable(ui->tableWidgetList ,0 ,Row ,QString::number(L->Data.OKLengthLUnit,'f',2),Qt::ItemIsEditable);
				::SetDataToTable(ui->tableWidgetList ,1 ,Row ,QString::number(L->Data.OKLengthHUnit,'f',2),Qt::ItemIsEditable);

				QWidget *b1=ui->tableWidgetList->cellWidget(Row,2);
				if(b1==NULL){
					MeasurePointButton	*b=new MeasurePointButton();
					ButtonRightClickEnabler	*Bn=new ButtonRightClickEnabler(b);
					b->Phase			=L->Data.Phase;
					b->Page				=L->Data.Page;
					b->DistanceItemID	=L->Data.ItemID;
					b->EndNo=0;
					b->MeasureNo=L->Data.MeasureNo;

					ShowSearchDotOnButton(b);

					ui->tableWidgetList->setCellWidget(Row,2,b);
					connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
					connect(Bn,SIGNAL(RightClicked(QAbstractButton *)),this,SLOT(SlotRightClicked(QAbstractButton *)));
				}
				QWidget *b2=ui->tableWidgetList->cellWidget(Row,3);
				if(b2==NULL){
					MeasurePointButton	*b=new MeasurePointButton();
					ButtonRightClickEnabler	*Bn=new ButtonRightClickEnabler(b);
					b->Phase			=L->Data.Phase;
					b->Page				=L->Data.Page;
					b->DistanceItemID=L->Data.ItemID;
					b->EndNo=1;
					b->MeasureNo=L->Data.MeasureNo;

					ShowSearchDotOnButton(b);

					ui->tableWidgetList->setCellWidget(Row,3,b);
					connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
					connect(Bn,SIGNAL(RightClicked(QAbstractButton *)),this,SLOT(SlotRightClicked(QAbstractButton *)));
				}

				::SetDataToTable(ui->tableWidgetList ,4 ,Row ,QString::number(L->Data.CurrentValueUnit,'f',2),Qt::ItemIsEditable);
			}
		}
	}
}
void	EasyPropertyMeasureForm::ShowSearchDotOnButton(MeasurePointButton *b)
{
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);

	IntegrationCmdReqMeasureLineInfo	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	IntegrationCmdAckMeasureLineInfo	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
	RCmd.Phase			=b->Phase;
	RCmd.Page			=b->Page;
	RCmd.DistanceItemID	=b->DistanceItemID;
	RCmd.EndNo			=b->EndNo;
	RCmd.MeasureNo		=b->MeasureNo;
	if(RCmd.Send(SlaveNo,0,ACmd)==true){
		b->setText(QString::number(ACmd.SearchDot) 
				 + QString(/**/"(")
				 + ThisM->TransformPixelToUnitStr(ACmd.SearchDot)
				 + QString(/**/")"));
	}
}
void	EasyPropertyMeasureForm::ShowSearchDotOnButton(void)
{
	int	Row=0;
	for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){

		QWidget *b1=ui->tableWidgetList->cellWidget(Row,2);
		if(b1!=NULL){
			MeasurePointButton	*b=dynamic_cast<MeasurePointButton *>(b1);
			ShowSearchDotOnButton(b);
		}
		QWidget *b2=ui->tableWidgetList->cellWidget(Row,3);
		if(b2!=NULL){
			MeasurePointButton	*b=dynamic_cast<MeasurePointButton *>(b2);
			ShowSearchDotOnButton(b);
		}
	}
}

void	EasyPropertyMeasureForm::SlotEndPointClicked(int EndNo,int MeasureNo)
{
	CurrentMeasureNo=MeasureNo;
	bool	ModeDown=false;
	if(EndNo==0){
		DrawMode=1;
		int	Row=0;
		for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
			if(L->Data.MeasureNo==MeasureNo){
				MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,2));
				if(b!=NULL && b->isChecked()==true){
					ModeDown=true;
					break;
				}
			}
		}
		if(ModeDown==true){
			Row=0;
			for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,3));
				if(b!=NULL && b->isChecked()==true){
					b->setChecked(false);
				}
			}
			Row=0;
			for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				if(L->Data.MeasureNo!=MeasureNo){
					MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,2));
					if(b!=NULL && b->isChecked()==true){
						b->setChecked(false);
					}
				}
			}
		}
	}
	else if(EndNo==1){
		DrawMode=2;
		int	Row=0;
		for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
			if(L->Data.MeasureNo==MeasureNo){
				MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,3));
				if(b!=NULL && b->isChecked()==true){
					ModeDown=true;
					break;
				}
			}
		}
		if(ModeDown==true){
			Row=0;
			for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,2));
				if(b!=NULL && b->isChecked()==true){
					b->setChecked(false);
				}
			}
			Row=0;
			for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				if(L->Data.MeasureNo!=MeasureNo){
					MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,3));
					if(b!=NULL && b->isChecked()==true){
						b->setChecked(false);
					}
				}
			}
		}
	}
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return;
	EasyMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyMeasureImagePanel *)GUIFormRet[i]);
			break;
		}
	}
	if(AccessPanel!=NULL){
	}
}
void EasyPropertyMeasureForm::on_pushButtonStartPoint1_clicked()
{
	DrawMode=0;
	int	Row=0;
	for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		{
			MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,2));
			if(b!=NULL){
				b->setChecked(false);
			}
		}
		{
			MeasurePointButton *b=dynamic_cast<MeasurePointButton *>(ui->tableWidgetList->cellWidget(Row,3));
			if(b!=NULL){
				b->setChecked(false);
			}
		}
	}
}

void EasyPropertyMeasureForm::on_pushButtonDelete_clicked()
{
	int	R=ui->tableWidgetList->currentRow();
	if(R<0)
		return;
	int	Row=0;
	for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		if(Row==R){
			IntegrationCmdDeleteDistance	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=L->Data.Phase;
			RCmd.Page		=L->Data.Page;
			RCmd.MeasureNo	=L->Data.MeasureNo;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	ShowList();
}

void EasyPropertyMeasureForm::on_toolButtonGetCorrentValuesTarget_clicked()
{
	ShowList();
}

void EasyPropertyMeasureForm::on_toolButtonReflect_clicked()
{
	int	Row=0;
	for(MeasureDistanceItemInfo *L=ListData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		QString	LenLStr=::GetDataToTable(ui->tableWidgetList, 0, Row);
		QString	LenHStr=::GetDataToTable(ui->tableWidgetList, 1, Row);
		bool	okL;
		double	LenL=LenLStr.toDouble(&okL);
		bool	okH;
		double	LenH=LenHStr.toDouble(&okH);
		if(okL==true && okH==true){
			IntegrationCmdSetCorrectValue	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=L->Data.Phase;
			RCmd.Page		=L->Data.Page;
			RCmd.ItemID		=L->Data.ItemID;
			RCmd.OKLengthLUnit	=LenL;
			RCmd.OKLengthHUnit	=LenH;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	ShowList();
}
EasyMeasureImagePanel	*EasyPropertyMeasureForm::GetEasyMeasureImagePanel(void)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyMeasureImagePanel" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(ThisM==NULL)
		return NULL;
	EasyMeasureImagePanel	*AccessPanel=NULL;
	for(int i=0;i<n;i++){
		if(((EasyMeasureImagePanel *)GUIFormRet[i])->MachineCode==ThisM->GetMachineCode()){
			AccessPanel=((EasyMeasureImagePanel *)GUIFormRet[i]);
			return AccessPanel;
		}
	}
	return NULL;
}
void EasyPropertyMeasureForm::on_tableWidgetList_itemSelectionChanged()
{
	EasyMeasureImagePanel	*AccessPanel=GetEasyMeasureImagePanel();
	if(AccessPanel!=NULL){
		int	Row=ui->tableWidgetList->currentRow();
		if(0<=Row){
			MeasureDistanceItemInfo *L=ListData.GetItem(Row);
			if(L!=NULL){
				AccessPanel->ShowingItemID=L->Data.ItemID;
				AccessPanel->Repaint();
			}
		}
	}
}

void	EasyPropertyMeasureForm::SlotRightClicked(QAbstractButton *obj)
{
	MeasurePointButton	*b=dynamic_cast<MeasurePointButton *>(obj);
	if(b!=NULL){
		IntegrationCmdReqMeasureLineInfo	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationCmdAckMeasureLineInfo	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.Phase			=b->Phase;
		RCmd.Page			=b->Page;
		RCmd.DistanceItemID	=b->DistanceItemID;
		RCmd.EndNo			=b->EndNo;
		RCmd.MeasureNo		=b->MeasureNo;
		if(RCmd.Send(SlaveNo,0,ACmd)==true){

			SetSearchDotDialog	D(GetLayersBase(),this,ACmd.SearchDot,b->Page);
			int	Ret=D.exec();
			if(Ret==1){
				IntegrationCmdSetMeasureLineInfo	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				SCmd.Phase			=b->Phase;
				SCmd.Page			=b->Page;
				SCmd.DistanceItemID	=b->DistanceItemID;
				SCmd.EndNo			=b->EndNo;
				SCmd.MeasureNo		=b->MeasureNo;
				SCmd.SearchDot		=D.RetSearchDot;
				SCmd.Send(NULL,SlaveNo,0);

				EasyMeasureImagePanel	*AccessPanel=GetEasyMeasureImagePanel();
				if(AccessPanel!=NULL){
					AccessPanel->Repaint();
				}
				ShowSearchDotOnButton();
			}
			else
			if(Ret==2){
				IntegrationCmdSetMeasureLineInfoAll	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				SCmd.Phase			=b->Phase;
				SCmd.Page			=b->Page;
				SCmd.DistanceItemID	=b->DistanceItemID;
				SCmd.EndNo			=b->EndNo;
				SCmd.MeasureNo		=b->MeasureNo;
				SCmd.SearchDot		=D.RetSearchDot;
				SCmd.Send(NULL,SlaveNo,0);

				EasyMeasureImagePanel	*AccessPanel=GetEasyMeasureImagePanel();
				if(AccessPanel!=NULL){
					AccessPanel->Repaint();
				}
				ShowSearchDotOnButton();
			}
		}
	}
}
void	EasyPropertyMeasureForm::StartInitial(void)
{
	ShowList();
}
