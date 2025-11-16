#include "DisplayNGListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayNGList\DisplayNGList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayNGList.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCmdPacket.h"
#include "XGUI.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XDataInLayerCommander.h"
#include "XReviewCommonPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"DisplayNGList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NG List for Inspection");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayNGList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqNGList	(Base,sRoot,sName);
	(*Base)=new GUICmdSendNGList(Base,sRoot,sName);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"WidthLineNumber";
	Data[0].Pointer				 =&((DisplayNGList *)Instance)->WidthLineNumber;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"WidthPhaseNumber";
	Data[1].Pointer				 =&((DisplayNGList *)Instance)->WidthPhaseNumber;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"WidthPageNumber";
	Data[2].Pointer				 =&((DisplayNGList *)Instance)->WidthPageNumber;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"WidthPosition";
	Data[3].Pointer				 =&((DisplayNGList *)Instance)->WidthPosition;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"WidthLocationName";
	Data[4].Pointer				 =&((DisplayNGList *)Instance)->WidthLocationName;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"WidthCause";
	Data[5].Pointer				 =&((DisplayNGList *)Instance)->WidthCause;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"WidthMessage";
	Data[6].Pointer				 =&((DisplayNGList *)Instance)->WidthMessage;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[7].Pointer				 =&((DisplayNGList *)Instance)->TargetImagePanelName;
	Data[8].Type				 =/**/"QStringList";
	Data[8].VariableNameWithRoute=/**/"TargetImagePanelNames";
	Data[8].Pointer				 =&((DisplayNGList *)Instance)->TargetImagePanelNames;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ResetPosition";
	Data[9].Pointer				 =&((DisplayNGList *)Instance)->ResetPosition;
	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"MinTimToNext";
	Data[10].Pointer				 =&((DisplayNGList *)Instance)->MinTimToNext;

	return(11);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	//List.AppendList(new RootNameList(/**/"Review", /**/"ReviewStructure"));
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayNGList.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================

void NGListWidget::mousePressEvent ( QMouseEvent * event )
{
	QTableWidget::mousePressEvent ( event );
	emit	SignalClicked();
}
void NGListWidget::keyPressEvent(QKeyEvent *event)
{
	int	d=event->key();
	if(d==Qt::Key_Down){
		int	Row=currentRow();
		if(Row==rowCount()-1){
			event->setAccepted(true);
			setFocus();
		}
		else{
			QTableWidget::keyPressEvent(event);
		}
	}
	else if(d==Qt::Key_Up){
		int	Row=currentRow();
		if(Row==0){
			event->setAccepted(true);
			setFocus();
		}
		else{
			QTableWidget::keyPressEvent(event);
		}
	}
	else{
		QTableWidget::keyPressEvent(event);
	}
}

DisplayNGList::DisplayNGList(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LastSelectedRow		=-1;
	ResetPosition		=true;
	AllocatedPageCount	=0;
	CmdReq				=NULL;
	CmdAck				=NULL;
	PhaseNumb			=0;
	ErrorGroupData		=NULL;

	WidthLineNumber		=24;
	WidthPhaseNumber	=0;
	WidthPageNumber		=24;
	WidthPosition		=64;
	WidthLocationName	=0;
	WidthCause			=64;
	WidthMessage		=0;
	NGList.move(0,0);
	resize(250,250);
	NGList.setParent(this);
	connect(&NGList,SIGNAL(itemEntered (QTableWidgetItem *)),this,SLOT(ListItemClicked (QTableWidgetItem *)));
	connect(&NGList,SIGNAL(itemSelectionChanged ()),this,SLOT(ListItemSelectionChanged()),Qt::QueuedConnection);
	NGList.setSelectionMode(QAbstractItemView::SingleSelection);
	NGList.setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(&NGList,SIGNAL(SignalClicked ()),this,SLOT(SlotClicked()));

	ioEffective		=NULL;
	ioNG_X			=NULL;
	ioNG_Y			=NULL;
	ioNGCount		=NULL;
	ioCurrentNG		=NULL;
	ErrorGroupData	=NULL;
	MinTimToNext	=200;
	LastTime		=0;
	LastRow			=0;
}

DisplayNGList::~DisplayNGList(void)
{
	ReleaseMemory();
}


void	DisplayNGList::Prepare(void)
{
	AllocateMemory();

	int	ColCount=((WidthPageNumber>0)?1:0)
				+((WidthPhaseNumber>0)?1:0)
				+((WidthPosition>0)?1:0)
				+((WidthLocationName>0)?1:0)
				+((WidthCause>0)?1:0)
				+((WidthMessage>0)?1:0);
	NGList.setColumnCount(ColCount);
	NGList.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ShowInPlayer(-1);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioEffective	=new SignalOperandInt(this,331,/**/"DisplayNGList:ioEffective");
			ioNG_X		=new SignalOperandInt(this,329,/**/"DisplayNGList:ioNG_X");
			ioNG_Y		=new SignalOperandInt(this,330,/**/"DisplayNGList:ioNG_Y");
			ioNGCount	=new SignalOperandInt(this,333,/**/"DisplayNGList:ioNGCount");
			ioCurrentNG	=new SignalOperandInt(this,332,/**/"DisplayNGList:ioCurrentNG");

			connect(ioEffective	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			connect(ioNG_X		,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			connect(ioNG_Y		,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			connect(ioNGCount	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			connect(ioCurrentNG	,SIGNAL(changed())	,this	,SLOT(OperandChanged()));

			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioEffective	,&Error)==false){
				ioEffective->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioNG_X			,&Error)==false){
				ioNG_X->ShowErrorMessage(Error);
			};
			if(Param->SetSpecialOperand(ioNG_Y			,&Error)==false){
				ioNG_Y->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioNGCount		,&Error)==false){
				ioNGCount->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioCurrentNG	,&Error)==false){
				ioCurrentNG->ShowErrorMessage(Error);
			}
		}
	}
	connect(GetLayersBase(),SIGNAL(SignalChangedPhasePageLayer())	,this,SLOT(SlotChangedPhasePageLayer()));
}
void	DisplayNGList::ReadyParam(void)
{
	int	N=0;
	if(WidthPhaseNumber>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem(LangSolver.GetString(DisplayNGList_LS,LID_0)/*"Ph"*/));
		NGList.setColumnWidth (N, WidthPhaseNumber);
		N++;
	}
	if(WidthPageNumber>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem(LangSolver.GetString(DisplayNGList_LS,LID_1)/*"Pg"*/));
		NGList.setColumnWidth (N, WidthPageNumber);
		N++;
	}
	if(WidthPosition>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem(LangSolver.GetString(DisplayNGList_LS,LID_2)/*"Position"*/));
		NGList.setColumnWidth (N, WidthPosition);
		N++;
	}
	if(WidthLocationName>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem(LangSolver.GetString(DisplayNGList_LS,LID_3)/*"Location"*/));
		NGList.setColumnWidth (N, WidthLocationName);
		N++;
	}
	if(WidthCause>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem(LangSolver.GetString(DisplayNGList_LS,LID_4)/*"Cause"*/));
		NGList.setColumnWidth (N, WidthCause);
		N++;
	}
	if(WidthMessage>0){
		NGList.setHorizontalHeaderItem ( N, new QTableWidgetItem("Message"));
		NGList.setColumnWidth (N, WidthMessage);
		N++;
	}
}

void	DisplayNGList::AllocateMemory(void)
{
	if(ErrorGroupData!=NULL){
		delete	[]ErrorGroupData;
	}
	AllocatedPageCount=GetPageNumb();
	CmdReq	=new GUICmdReqNGList*[AllocatedPageCount];
	CmdAck	=new GUICmdSendNGList*[AllocatedPageCount];
	for(int page=0;page<AllocatedPageCount;page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		CmdReq[page]=new GUICmdReqNGList (GetLayersBase(),sRoot,sName,GlobalPage);
		CmdAck[page]=new GUICmdSendNGList(GetLayersBase(),sRoot,sName,GlobalPage);
	}

	PhaseNumb=GetPhaseNumb();
	ErrorGroupData	=new ErrorGroupPack**[PhaseNumb];
	for(int phase=0;phase<PhaseNumb;phase++){
		ErrorGroupData[phase]=new ErrorGroupPack*[AllocatedPageCount];
		for(int page=0;page<AllocatedPageCount;page++){
			ErrorGroupData[phase][page]=NULL;
		}
	}
}

void	DisplayNGList::ReleaseMemory(void)
{
	if(ErrorGroupData!=NULL){
		delete	[]ErrorGroupData;
		ErrorGroupData=NULL;
	}
	if(CmdReq!=NULL){
		for(int i=0;i<AllocatedPageCount;i++){
			delete	CmdReq[i];
		}
		delete	CmdReq;
		CmdReq=NULL;
	}
	if(CmdAck!=NULL){
		for(int i=0;i<AllocatedPageCount;i++){
			delete	CmdAck[i];
		}
		delete	CmdAck;
		CmdAck=NULL;
	}
	if(ErrorGroupData!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			delete	[]ErrorGroupData[phase];
		}
		delete	[]ErrorGroupData;
		ErrorGroupData=NULL;
	}
}

void	DisplayNGList::SlotChangedPhasePageLayer()
{
	ReleaseMemory();
	AllocateMemory();
}

void	DisplayNGList::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	InitializedSpecifiedBroadcaster	*InitializedSpecifiedBroadcasterVar=dynamic_cast<InitializedSpecifiedBroadcaster *>(v);
	if(InitializedSpecifiedBroadcasterVar!=NULL){
		ShowInPlayer(0);
	}
}
void	DisplayNGList::ResizeAction()
{
	NGList.resize(width(),height());
}

static	int	ErrorGroupTableFunc(const void *a ,const void *b)
{
	ErrorGroup	*am=((ErrorGroup **)a)[0];
	ErrorGroup	*bm=((ErrorGroup **)b)[0];
	if(am->GetPieceAreaNumber()<bm->GetPieceAreaNumber())
		return -1;
	if(am->GetPieceAreaNumber()>bm->GetPieceAreaNumber())
		return 1;

	int aCx, aCy;
	am->GetCenter(aCx, aCy);
	int bCx, bCy;
	bm->GetCenter(bCx, bCy);

	if(aCy>bCy)
		return -1;
	if(aCy<bCy)
		return 1;

	if(aCx>bCx)
		return -1;
	if(aCx<bCx)
		return 1;
	return 0;
}

void	DisplayNGList::ShowInPlayer(int64 shownInspectionID)
{
	ParamGlobal	*ParamG	=GetParamGlobal();
	LayersBase	*LBase	=GetLayersBase();
	//if(GetLayersBase()->GetCurrentScanPhaseNumber()!=0)
	if(ParamG->OutputOnlyPhase==-1 || ParamG->OutputOnlyPhase==LBase->GetCurrentScanPhaseNumber()){
		NGList.setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);

		if(shownInspectionID>=0){
			if(AllocatedPageCount!=GetPageNumb()){
				if(CmdReq!=NULL){
					for(int i=0;i<AllocatedPageCount;i++){
						delete	CmdReq[i];
					}
					delete	CmdReq;
					CmdReq=NULL;
				}
				if(CmdAck!=NULL){
					for(int i=0;i<AllocatedPageCount;i++){
						delete	CmdAck[i];
					}
					delete	CmdAck;
					CmdAck=NULL;
				}
				if(ErrorGroupData!=NULL){
					for(int phase=0;phase<PhaseNumb;phase++){
						delete	[]ErrorGroupData[phase];
					}
					delete	[]ErrorGroupData;
					ErrorGroupData=NULL;
				}

				AllocatedPageCount=GetPageNumb();
				CmdReq	=new GUICmdReqNGList*[AllocatedPageCount];
				CmdAck	=new GUICmdSendNGList*[AllocatedPageCount];
				for(int page=0;page<AllocatedPageCount;page++){
					int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
					CmdReq[page]=new GUICmdReqNGList (GetLayersBase(),sRoot,sName,GlobalPage);
					CmdAck[page]=new GUICmdSendNGList(GetLayersBase(),sRoot,sName,GlobalPage);
				}
			}
			if(PhaseNumb!=GetPhaseNumb() && ErrorGroupData!=NULL){
				for(int phase=0;phase<PhaseNumb;phase++){
					delete	[]ErrorGroupData[phase];
				}
				delete	[]ErrorGroupData;
				ErrorGroupData=NULL;
				PhaseNumb=GetPhaseNumb();
			}
			if(ErrorGroupData==NULL){
				ErrorGroupData	=new ErrorGroupPack**[PhaseNumb];
				for(int phase=0;phase<PhaseNumb;phase++){
					ErrorGroupData[phase]=new ErrorGroupPack*[AllocatedPageCount];
					for(int page=0;page<AllocatedPageCount;page++){
						ErrorGroupData[phase][page]=NULL;
					}
				}
			}
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=LBase->GetGlobalPageFromLocal(page);
				CmdReq[page]->ShownInspectionID=shownInspectionID;
				CmdReq[page]->ShowCause=(WidthCause>0)?true:false;
				if(CmdReq[page]->Send(GlobalPage ,0,*CmdAck[page])==true){
					for(int phase=0;phase<PhaseNumb;phase++){
						for(ErrorGroup *e=CmdAck[page]->ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext()){
							e->SetPage(page);
						}
					}
				}
			}
		}
		int	LNumb=0;
		for(int page=0;page<GetPageNumb();page++){
			for(int phase=0;phase<PhaseNumb;phase++){
				ErrorGroupData[phase][page]=&CmdAck[page]->ErrorGroupData[phase];
				LNumb+=ErrorGroupData[phase][page]->GetCount();
			}
		}
		
		NGList.setRowCount(LNumb);
		if(ioNGCount!=NULL){
			ioNGCount->Set(LNumb);
		}
		//NGList.setCurrentCell(0,0);
		NGList.setUpdatesEnabled(false);
		NGList.clearSelection();


		int	row=0;
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<GetPageNumb();page++){
				ErrorGroupPack	*E=ErrorGroupData[phase][page];
		
				int	ErrorGroupNumber=E->GetCount();
				ErrorGroup *ErrorGroupTableDim[100000];
				ErrorGroup **ErrorGroupTable;
				if(ErrorGroupNumber>=sizeof(ErrorGroupTableDim)/sizeof(ErrorGroupTableDim[0])){
					ErrorGroupTable=new ErrorGroup*[ErrorGroupNumber];
				}
				else{
					ErrorGroupTable=ErrorGroupTableDim;
				}
				int	n=0;
				for(ErrorGroup *e=E->GetFirst();e!=NULL;e=e->GetNext()){
					ErrorGroupTable[n]=e;
					n++;
				}
				QSort(ErrorGroupTable,ErrorGroupNumber,sizeof(ErrorGroupTable[0]),ErrorGroupTableFunc);
				ErrorGroup *err;
				while((err=E->GetFirst())!=NULL){
					E->RemoveList(err);
				}
				for(n=0;n<ErrorGroupNumber;n++){
					E->AppendList(ErrorGroupTable[n]);
				}

				for(n=0;n<ErrorGroupNumber;n++,row++){
					ErrorGroup *e=ErrorGroupTable[n];

					int	ex1,ey1,ex2,ey2;
					e->GetXY(ex1,ey1,ex2,ey2);
					QTableWidgetItem *W;
					int	N=0;
					if(WidthPhaseNumber>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(ParamG->GetPhaseString(phase));
						N++;
					}
					if(WidthPageNumber>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(QString::number(e->GetPage()));
						N++;
					}
					if(WidthPosition>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(QString::number((ex1+ex2)/2) + QString(/**/",") +QString::number((ey1+ey2)/2));
						N++;
					}
					if(WidthLocationName>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(e->GetName());
						N++;
					}
					if(WidthCause>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(e->GetCause());
						N++;
					}
					if(WidthMessage>0){
						W=NGList.item ( row, N);
						if(W==NULL){
							W=new QTableWidgetItem();
							NGList.setItem ( row, N,W);
							W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
						}
						W->setText(e->GetMessageStr());
						N++;
					}
				}
				if(ErrorGroupTable!=ErrorGroupTableDim){
					delete	[]ErrorGroupTable;
				}
			}
		}	
		NGList.setUpdatesEnabled(true);

		if(ResetPosition==true){
			if(LNumb!=0){
				NGList.setFocus();
				NGList.setCurrentCell(0,0);
			}
			if(ioCurrentNG!=NULL){
				ioCurrentNG->Set(0);
			}
		}
		else{
			LastSelectedRow=-1;
		}
	}
}


void	DisplayNGList::ListItemSelectionChanged ()
//void	DisplayNGList::SlotCurrentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn )
{
	int row	=NGList.currentRow();
	if(row<0)
		return;
	//if(LastSelectedRow==row)
	//	return;
	DWORD	NowMilisec=::GetComputerMiliSec();
	if(NowMilisec-LastTime<MinTimToNext){
		NGList.setCurrentCell(LastRow,0);
		return;
	}
	LastRow=row;
	LastTime=NowMilisec;

	LastSelectedRow=row;

	int	CRow=0;
	ErrorGroup *E=NULL;
	int	CPhase=0;
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<AllocatedPageCount;page++){
			for(ErrorGroup *e=ErrorGroupData[phase][page]->GetFirst();e!=NULL;e=e->GetNext(),CRow++){
				if(CRow==row){
					E=e;
					CPhase=phase;
					goto	FoundE;
				}
			}
		}
	}
	FoundE:;
	if(E!=NULL){
		int	ex1,ey1,ex2,ey2;
		E->GetXY(ex1,ey1,ex2,ey2);
		DataInPage *pdata=GetLayersBase()->GetPageData(E->GetPage());

		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
				if(pdata!=NULL){
					if(d->ShowFixedPhase==-1){
						GetLayersBase()->SetCurrentPhase(CPhase);
							int RetScanPhaseNumber;
							GetLayersBase()->GetScanPhaseFromPhase(CPhase ,RetScanPhaseNumber);
							GetLayersBase()->TF_SetCurrentScanPhaseNumber(RetScanPhaseNumber);
					}
					d->ShowCenter((ex1+ex2)/2 +pdata->GetOutlineOffset()->x,(ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
				}
			}
		}
		for(int i=0;i<TargetImagePanelNames.count();i++){
			GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelNames[i]);
			if(F!=NULL){
				DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
				if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
					if(pdata!=NULL){
						if(d->ShowFixedPhase==-1){
							GetLayersBase()->SetCurrentPhase(CPhase);
							int RetScanPhaseNumber;
							GetLayersBase()->GetScanPhaseFromPhase(CPhase ,RetScanPhaseNumber);
							GetLayersBase()->TF_SetCurrentScanPhaseNumber(RetScanPhaseNumber);
						}
						d->ShowCenter((ex1+ex2)/2 +pdata->GetOutlineOffset()->x,(ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
					}
				}
			}
		}
		/*
		GUIFormBase	*F=GetLayersBase()->FindByName("Inspection","DisplayTargetImage" ,TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
				if(pdata!=NULL){
					ShowingQueue	*k=new ShowingQueue();
					k->d=d;
					if(d->ShowFixedPhase==-1){
						k->CPhase=CPhase;
					}
					else{
						k->CPhase=-1;
					}
					k->Cx=(ex1+ex2)/2 +pdata->GetOutlineOffset()->x;
					k->Cy=(ey1+ey2)/2 +pdata->GetOutlineOffset()->y;
					ShowingQueueData.AppendList(k);
					emit	SignalShowRow();
				}
			}
		}
		for(int i=0;i<TargetImagePanelNames.count();i++){
			GUIFormBase	*F=GetLayersBase()->FindByName("Inspection","DisplayTargetImage" ,TargetImagePanelNames[i]);
			if(F!=NULL){
				DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
				if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
					if(pdata!=NULL){
						ShowingQueue	*k=new ShowingQueue();
						k->d=d;
						if(d->ShowFixedPhase==-1){
							k->CPhase=CPhase;
						}
						else{
							k->CPhase=-1;
						}
						k->Cx=(ex1+ex2)/2 +pdata->GetOutlineOffset()->x;
						k->Cy=(ey1+ey2)/2 +pdata->GetOutlineOffset()->y;
						ShowingQueueData.AppendList(k);
						emit	SignalShowRow();
					}
				}
			}
		}
		*/

		if(ioNG_X!=NULL && ioNG_Y!=NULL && ioEffective!=NULL){
			ioNG_X->Set((ex1+ex2)/2 +pdata->GetOutlineOffset()->x);
			ioNG_Y->Set((ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
			ioEffective->Set(1);
		}
		AlgorithmBase *RBase = GetLayersBase()->GetAlgorithmBase(/**/"Review", /**/"ReviewStructure");
		if(RBase!=NULL){
			ReviewCommonPacket::CmdMoveVRSWithAlignment moveVRS(GetLayersBase());
			DataInPage *pdata=GetLayersBase()->GetPageData(E->GetPage());

			moveVRS.setMachineID(GetLayersBase()->GetMachineID());
			moveVRS.setPage(pdata->GetPage());
			moveVRS.setPhase(CPhase);
			moveVRS.setX((ex1+ex2)/2);
			moveVRS.setY((ey1+ey2)/2);
			RBase->TransmitDirectly( &moveVRS );
		}
	}
	if(ioCurrentNG!=NULL){
		ioCurrentNG->Set(row);
	}
	BroadcastShowInEdit();
}
void DisplayNGList::keyReleaseEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Up || event->key()==Qt::Key_Down || event->key()==Qt::Key_Return){
		ListItemSelectionChanged ();
		event->accept();
	}
}


void	DisplayNGList::ListItemClicked ( QTableWidgetItem *)
{
	int row	=NGList.currentRow();
	if(row<0)
		return;
	//if(LastSelectedRow==row)
	//	return;
	DWORD	NowMilisec=::GetComputerMiliSec();
	if(NowMilisec-LastTime<MinTimToNext){
		NGList.setCurrentCell(LastRow,0);
		return;
	}
	LastTime=NowMilisec;
	LastSelectedRow=row;

	int	CRow=0;
	ErrorGroup *E=NULL;
	int	CPhase=0;
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<AllocatedPageCount;page++){
			for(ErrorGroup *e=ErrorGroupData[phase][page]->GetFirst();e!=NULL;e=e->GetNext(),CRow++){
				if(CRow==row){
					CPhase=phase;
					E=e;
					goto	FoundE;
				}
			}
		}
	}
	FoundE:;
	if(E!=NULL){
		int	ex1,ey1,ex2,ey2;
		E->GetXY(ex1,ey1,ex2,ey2);
		DataInPage *pdata=GetLayersBase()->GetPageData(E->GetPage());

		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
				if(pdata!=NULL){
					d->ShowCenter((ex1+ex2)/2 +pdata->GetOutlineOffset()->x,(ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
				}
			}
		}
		for(int i=0;i<TargetImagePanelNames.count();i++){
			GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelNames[i]);
			if(F!=NULL){
				DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
				if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
					if(pdata!=NULL){
						d->ShowCenter((ex1+ex2)/2 +pdata->GetOutlineOffset()->x,(ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
					}
				}
			}
		}
		if(ioNG_X!=NULL && ioNG_Y!=NULL && ioEffective!=NULL){
			ioNG_X->Set((ex1+ex2)/2 +pdata->GetOutlineOffset()->x);
			ioNG_Y->Set((ey1+ey2)/2 +pdata->GetOutlineOffset()->y);
			ioEffective->Set(1);
		}
	}
	if(ioCurrentNG!=NULL){
		ioCurrentNG->Set(row);
	}
}
void	DisplayNGList::OperandChanged()
{
}

void	DisplayNGList::SlotClicked ()
{
	int row	=NGList.currentRow();
	if(LastSelectedRow==row){
		ListItemSelectionChanged ();
	}
}
void	DisplayNGList::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetCurrentInfo	*CmdGetCurrentInfoVar=dynamic_cast<CmdGetCurrentInfo *>(packet);
	if(CmdGetCurrentInfoVar!=NULL){
		int row	=NGList.currentRow();
		if(row<0)
			return;
		int	CRow=0;
		ErrorGroup *E=NULL;
		int	CPhase=0;
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<AllocatedPageCount;page++){
				for(ErrorGroup *e=ErrorGroupData[phase][page]->GetFirst();e!=NULL;e=e->GetNext(),CRow++){
					if(CRow==row){
						CmdGetCurrentInfoVar->Phase	=phase;
						CmdGetCurrentInfoVar->Page	=page;
						if(e->RepresentativeItemPoint!=NULL){
							CmdGetCurrentInfoVar->Layer	=e->RepresentativeItemPoint->GetLayer();
							CmdGetCurrentInfoVar->ItemID=e->RepresentativeItemPoint->GetItemID();
							if(e->RepresentativeItemPoint->GetAlgorithmItemRoot()!=NULL){
								CmdGetCurrentInfoVar->RepresentativeItem	=e->RepresentativeItemPoint->GetAlgorithmItemRoot();
								CmdGetCurrentInfoVar->LibID		=e->RepresentativeItemPoint->GetAlgorithmItemRoot()->GetLibID();
								CmdGetCurrentInfoVar->LibType	=e->RepresentativeItemPoint->GetAlgorithmItemRoot()->GetLibType();
							}
						}
						else
						if(e->TmpRepresentativeItem[0]!=NULL){
							CmdGetCurrentInfoVar->Layer	=e->TmpRepresentativeItem[0]->GetLayer();
							CmdGetCurrentInfoVar->ItemID=e->TmpRepresentativeItem[0]->GetItemID();
							if(e->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()!=NULL){
								CmdGetCurrentInfoVar->RepresentativeItem	=e->TmpRepresentativeItem[0]->GetAlgorithmItemRoot();
								CmdGetCurrentInfoVar->LibID		=e->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()->GetLibID();
								CmdGetCurrentInfoVar->LibType	=e->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()->GetLibType();
							}
						}
					}
					return;
				}
			}
		}
		return;
	}
}

//=======================================================================

GUICmdReqNGList::GUICmdReqNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqNGList::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	::Save(f,ShowCause);
	return(true);
}
bool	GUICmdReqNGList::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	::Load(f,ShowCause);
	return(true);
}

void	GUICmdReqNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGList	*SendBack=GetSendBack(GUICmdSendNGList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Initial();
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			NGImageContainerInPhase	*Ph=R->GetNGImageInPhase(phase);
			if(Ph!=NULL){
				NGImageContainerInPage	*p=Ph->GetNGImageInPage(localPage);
				if(p!=NULL){
					SendBack->ErrorGroupData[phase]=p->GetErrorGroupData();
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendNGList::GUICmdSendNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ErrorGroupData=new ErrorGroupPack[GetPhaseNumb()];
}

GUICmdSendNGList::~GUICmdSendNGList(void)
{
	delete	[]ErrorGroupData;
	ErrorGroupData=NULL;
}

void	GUICmdSendNGList::Initial(void)
{
	if(ErrorGroupData!=NULL)
		delete	[]ErrorGroupData;
	ErrorGroupData=new ErrorGroupPack[GetPhaseNumb()];
}

bool	GUICmdSendNGList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Initial();
	for(int phase=0;phase<N && phase<GetPhaseNumb();phase++){
		if(ErrorGroupData[phase].Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdSendNGList::Save(QIODevice *f)
{
	int32	N=GetPhaseNumb();

	if(::Save(f,N)==false){
		return false;
	}
	for(int phase=0;phase<N;phase++){
		if(ErrorGroupData[phase].Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
