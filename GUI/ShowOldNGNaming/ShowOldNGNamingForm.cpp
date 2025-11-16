#include "ShowOldNGNamingResource.h"
#include "ShowOldNGNamingForm.h"
#include "ui_ShowOldNGNamingForm.h"
#include "XNaming.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XShowOldNGNamingPacket.h"
#include "XWriteResultThread.h"
#include "swap.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowOldNGNamingForm::ShowOldNGNamingForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowOldNGNamingForm)
{
    ui->setupUi(this);
	NamingCompiled = false;
	NGNaming	=NULL;
	NamingArea	=NULL;
	GenerationLevel	=1;
	CompNGAreaList.clear();
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ioNGCount			=NULL;
	ioCurrentCounter	=NULL;
	ioNGXPos			=NULL;
	ioNGYPos			=NULL;
	ioAck				=NULL;
	ioReqResult			=NULL;

}

ShowOldNGNamingForm::~ShowOldNGNamingForm()
{
	if(NamingArea!=NULL){
		delete	[]NamingArea;
	}
	NamingArea	=NULL;

	if(NGNaming!=NULL){
		delete	[]NGNaming;
	}
	NGNaming	=NULL;

	delete ui;
}
NamingBase	*ShowOldNGNamingForm::GetNamingBase(void)
{
	return (NamingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
}
void	ShowOldNGNamingForm::Prepare(void)
{
	if(NamingArea!=NULL){
		delete	[]NamingArea;
	}
	NamingArea	=new NamingPointerStock[GetPhaseNumb()];

	if(NGNaming!=NULL){
		delete	[]NGNaming;
	}
	NGNaming	=new NamingNGContainer[GetPhaseNumb()];

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioNGCount		=new SignalOperandInt(this,521);
			ioCurrentCounter=new SignalOperandInt(this,522);
			ioNGXPos		=new SignalOperandInt(this,523);
			ioNGYPos		=new SignalOperandInt(this,524);
			ioAck			=new SignalOperandInt(this,525);
			ioReqResult		=new SignalOperandBit(this,30);

			connect(ioNGCount			,SIGNAL(changed())	,this	,SLOT(OperandChanged()), Qt::QueuedConnection);
			connect(ioCurrentCounter	,SIGNAL(changed())	,this	,SLOT(OperandChanged()), Qt::QueuedConnection);
			connect(ioReqResult			,SIGNAL(changed())	,this	,SLOT(SlotReqResult()), Qt::QueuedConnection);

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioNGCount			,&Error)==false){
				ioNGCount->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioCurrentCounter	,&Error)==false){
				ioCurrentCounter->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioNGXPos			,&Error)==false){
				ioNGXPos->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioNGYPos			,&Error)==false){
				ioNGYPos->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioAck				,&Error)==false){
				ioAck->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioReqResult		,&Error)==false){
				ioReqResult->ShowErrorMessage(Error);
			}
		}
	}
}

void	ShowOldNGNamingForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height()-23);
	int	W=width();
	ui->tableWidget->setColumnWidth (0, (W-24)/2);
	ui->tableWidget->setColumnWidth (1, (W-24)/3);
	ui->tableWidget->setColumnWidth (2, (W-24)/6);

}
int	SortFuncNamingPointer(const void *a ,const void *b)
{
	NamingPointer	*pa=((NamingPointer **)a)[0];
	NamingPointer	*pb=((NamingPointer **)b)[0];
	bool	aok,bok;
	int	an=pa->AreaName.toInt(&aok);
	int	bn=pb->AreaName.toInt(&bok);
	if(aok==true && bok==true){
		if(an>bn)
			return 1;
		if(an<bn)
			return -1;
		return 0;
	}
	if(pa->AreaName>pb->AreaName)
		return 1;
	if(pa->AreaName<pb->AreaName)
		return -1;
	return 0;
}
void	ShowOldNGNamingForm::BuildForShow(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NamingArea[phase].RemoveAll();
	}
	for(int page=0;page<GetPageNumb();page++){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqNamingAreaList		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendNamingAreaList	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
			CmdReq.Phase	=phase;

			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				NamingArea[phase]+=CmdAck.NamingArea;
			}
		}
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		int	n=NamingArea[phase].GetCount();
		NamingPointer	**Index=new NamingPointer*[n];
		
		for(int	k=0;k<n;k++){
			NamingPointer *a=NamingArea[phase].GetFirst();
			NamingArea[phase].RemoveList(a);
			Index[k]=a;
		}
		QSort(Index,n,sizeof(Index[0]),SortFuncNamingPointer);

		for(int	k=0;k<n;k++){
			NamingArea[phase].AppendList(Index[k]);
		}

		NamingCompiled = false;
	}

	on_pushButtonGetNow_clicked();
}

void	ShowOldNGNamingForm::ShowInPlayer(int64 shownInspectionID)
{
	//ReqNamingData(shownInspectionID);
	//ShowGrid();
}

void	ShowOldNGNamingForm::ReqNamingData(int64 shownInspectionID)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGNaming[phase].RemoveAll();
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			GUICmdReqOlderNGList	CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendOlderNGList	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);

			CmdReq.CurrentInspectionID	=shownInspectionID;
			CmdReq.GenerationLevel=GenerationLevel;
			CmdReq.Phase=phase;

			if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
				for(NamingNG *n=CmdAck.NGNaming.GetFirst(); n!=NULL; n=n->GetNext()){
					NamingNG *item = new NamingNG();

					item->GlobalPage = n->GlobalPage;
					item->ItemID = n->ItemID;
					item->NGCount = n->NGCount;
					
					NGNaming[phase].AppendList( item );

					qDebug() << /**/"NGData";
					qDebug() << /**/"\t" << item->GlobalPage;
					qDebug() << /**/"\t" << item->ItemID;
					qDebug() << /**/"\t" << item->NGCount;
				}
				//for(int i=0; i<CmdAck.NGNaming.GetNumber(); i++){
				//	NamingNG *item = new NamingNG();
				//	*item = *(CmdAck.NGNaming[i]);
				//	NGNaming[phase].AppendList( item );

				//	qDebug() << "NGData";
				//	qDebug() << "\t" << item->GlobalPage;
				//	qDebug() << "\t" << item->ItemID;
				//	qDebug() << "\t" << item->NGCount;
				//}
				//NGNaming[phase]+=CmdAck.NGNaming;
			}
		}
	}

	if(NamingCompiled==false){
		CompNGAreaList.clear();
		//“¯‚¶–¼‘O‚Ì‚à‚Ì‚Í‚Ü‚Æ‚ß‚é
		for(int phase=0;phase<GetPhaseNumb();phase++){
			CompNGAreaList.append(ComplessNGAreaList());
			Retry:;
			for(NamingPointer *a=NamingArea[phase].GetFirst();a!=NULL;a=a->GetNext()){
				CompNGAreaList[phase].push(a->AreaName, a->GlobalPage, a->ItemID);
				debugOut();
				for(NamingPointer *b=a->GetNext();b!=NULL;b=b->GetNext()){
					if(a->AreaName==b->AreaName){
						CompNGAreaList[phase].push(b->AreaName, b->GlobalPage, b->ItemID);
						a->GlobalX1=min(a->GlobalX1,b->GlobalX1);
						a->GlobalY1=min(a->GlobalY1,b->GlobalY1);
						a->GlobalX2=max(a->GlobalX2,b->GlobalX2);
						a->GlobalY2=max(a->GlobalY2,b->GlobalY2);
						NamingArea[phase].RemoveList(b);
						delete	b;
						goto	Retry;
					}
				}
			}
		}
		NamingCompiled = true;
	}
	debugOut();
}

void ShowOldNGNamingForm::debugOut(){
	//for(int phase=0; phase<CompNGAreaList.count(); phase++){
	//	for(int i=0; i<CompNGAreaList[phase].count(); i++){
	//		qDebug() << CompNGAreaList[phase][i].Name;
	//		qDebug() << "\t" << CompNGAreaList[phase][i].GlobalPageList;
	//		qDebug() << "\t" << CompNGAreaList[phase][i].ItemIDList;

	//	}
	//}
}

void	ShowOldNGNamingForm::ShowGrid(void)
{
	int	LNumb=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(NamingPointer *a=NamingArea[phase].GetFirst();a!=NULL;a=a->GetNext()){
			NamingNG	*L=FindNG(a, phase);
			if(L!=NULL){
				LNumb++;
			}
		}
	}
	ioNGCount->Set(LNumb);

	ui->tableWidget->setRowCount(LNumb);
	ui->tableWidget->clearSelection();

	int	row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(NamingPointer *a=NamingArea[phase].GetFirst();a!=NULL;a=a->GetNext()){
			NamingNG	*L=FindNG(a, phase);
			if(L!=NULL){
				int NGCount = CountNG(a, phase);
				QString	s=QString::number((a->GlobalX1+a->GlobalX2)/2) + QString(/**/",") +QString::number((a->GlobalY1+a->GlobalY2)/2);

				SetDataToTable(ui->tableWidget,0,row ,a->AreaName);
				SetDataToTable(ui->tableWidget,1,row ,s);
				SetDataToTable(ui->tableWidget,2,row ,QString::number(NGCount/*L->NGCount*/));
				row++;
			}
		}
	}
}

void ShowOldNGNamingForm::on_tableWidget_clicked(const QModelIndex &index)
{
	int row	=ui->tableWidget->currentRow();
	if(row<0)
		return;
	int	LNumb=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(NamingPointer *a=NamingArea[phase].GetFirst();a!=NULL;a=a->GetNext()){
			NamingNG	*L=FindNG(a);
			if(L!=NULL){
				if(LNumb==row){
					DataInPage *pdata=GetLayersBase()->GetPageData(a->GlobalPage);
					for(int i=0;i<TargetImagePanelNames.count();i++){
						GUIFormBase	*F=GetLayersBase()->FindByName(TargetImagePanelNames[i]);
						if(F!=NULL){
							DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
							if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==phase)){
								if(pdata!=NULL){
									d->ShowCenter(a->GetCenterX() +pdata->GetOutlineOffset()->x
												, a->GetCenterY() +pdata->GetOutlineOffset()->y);
								}
							}
						}
					}
					return;
				}
				LNumb++;
			}
		}
	}
}

NamingNG	*ShowOldNGNamingForm::FindNG(NamingPointer *a)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(CompNGAreaList[phase].search(a->AreaName, a->GlobalPage, a->ItemID)==true){
			for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
				QString name = CompNGAreaList[phase].search(c->GlobalPage, c->ItemID);
				if(name.isNull()==false){
					return c;
				}
			}
		}
		
		//for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
		//	if(c->ItemID==a->ItemID){
		//		return c;
		//	}
		//}
	}
	return NULL;
}


NamingNG	*ShowOldNGNamingForm::FindNG(NamingPointer *a, int phase)
{
	if(CompNGAreaList[phase].search(a->AreaName, a->GlobalPage, a->ItemID)==true){
		for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
			if(CompNGAreaList[phase].search(a->AreaName, c->GlobalPage, c->ItemID)==true){
				return c;
			}
		}
	}
	//for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
	//	if(c->ItemID==a->ItemID){
	//		return c;
	//	}
	//}
	return NULL;
}

int ShowOldNGNamingForm::CountNG(NamingPointer *a, int phase)
{
	int count=0;
	if(CompNGAreaList[phase].search(a->AreaName, a->GlobalPage, a->ItemID)==true){
		for(NamingNG *c=NGNaming[phase].GetFirst();c!=NULL;c=c->GetNext()){
			if(CompNGAreaList[phase].search(a->AreaName, c->GlobalPage, c->ItemID)==true){
				count++;
			}
		}
	}

	return count;
}

void	ShowOldNGNamingForm::OperandChanged()
{
	int	Point=ioCurrentCounter->Get();
	if(0<=Point){
		int	row=0;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(NamingPointer *a=NamingArea[phase].GetFirst();a!=NULL;a=a->GetNext()){
				NamingNG	*L=FindNG(a, phase);
				if(L!=NULL){
					if(row==Point){
						int	XPos=(a->GlobalX1+a->GlobalX2)/2;
						int	YPos=(a->GlobalY1+a->GlobalY2)/2;
						ioNGXPos->Set(XPos);
						ioNGYPos->Set(YPos);
						ioAck	->Set(1);
						return;
					}
					row++;
				}
			}
		}
	}
	ioAck	->Set(-1);
}

void	ShowOldNGNamingForm::SlotReqResult()
{
	if(ioReqResult->Get()==true){
		ResultInspection	*p=GetLayersBase()->GetResultThread()->GetLatest();
		if(p!=NULL){
			int64	InspectionID=p->GetInspectionID();
			ReqNamingData(InspectionID);
			ShowGrid();
		}
		else{
			for(int phase=0;phase<GetPhaseNumb();phase++){
				NGNaming[phase].RemoveAll();
			}
			ui->tableWidget->setRowCount(0);
			ioNGCount->Set(0);
		}
		ioReqResult->Set(false);
	}
}
void ShowOldNGNamingForm::on_pushButtonGetNow_clicked()
{
	ResultInspection	*p=GetLayersBase()->GetResultThread()->GetLatest();
	if(p!=NULL){
		int64	InspectionID=p->GetInspectionID();
		ReqNamingData(InspectionID);
		ShowGrid();
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			NGNaming[phase].RemoveAll();
		}
		ui->tableWidget->setRowCount(0);
		ioNGCount->Set(0);
	}
}
