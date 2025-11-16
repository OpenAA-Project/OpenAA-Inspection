/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayNGListCategorized\DisplayNGListCategorized.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayNGListCategorized.h"
#include <QIcon>
#include <QPixmap>
#include <QKeyEvent>
#include <QMouseEvent>

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "XCmdPacket.h"
#include "XGUI.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XFileThread.h"
#include "XReviewCommonPacket.h"
#include "XTransform.h"
#include "XDataInLayerCommander.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"DisplayNGListCategorized";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NG Categorized List for Inspection ");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayNGListCategorized(Base,parent));
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
	if(maxDataDim<5)
		return(-1);

	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[0].Pointer				 =&((DisplayNGListCategorized *)Instance)->TargetImagePanelName;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"TargetImagePanelNames";
	Data[1].Pointer				 =&((DisplayNGListCategorized *)Instance)->TargetImagePanelNames;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ResetPosition";
	Data[2].Pointer				 =&((DisplayNGListCategorized *)Instance)->ResetPosition;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"MinTimToNext";
	Data[3].Pointer				 =&((DisplayNGListCategorized *)Instance)->MinTimToNext;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"FirstPointAfterInspection";
	Data[4].Pointer				 =&((DisplayNGListCategorized *)Instance)->FirstPointAfterInspection;
	
	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayNGListCategorized.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
//==================================================================================================

ErrorGroupPackWithShadowTree::ErrorGroupPackWithShadowTree(void){}

ErrorGroupPackWithShadowTree  &ErrorGroupPackWithShadowTree::operator=(const ErrorGroupPackWithShadowTree &src)
{
	ShadowLevel =src.ShadowLevel ;
	ShadowNumber=src.ShadowNumber;
	ErrorGroupPack::operator=(src);
	return *this;
}
ErrorGroupPackWithShadowTree  &ErrorGroupPackWithShadowTree::operator=(const ErrorGroupPack &src)
{
	ErrorGroupPack::operator=(src);
	return *this;
}
ErrorGroupPackWithShadowTree  &ErrorGroupPackWithShadowTree::operator+=(const ErrorGroupPackWithShadowTree &src)
{
	ShadowLevel =src.ShadowLevel ;
	ShadowNumber=src.ShadowNumber;
	ErrorGroupPack::operator+=(src);
	return *this;
}
bool    ErrorGroupPackWithShadowTree::Load(QIODevice *f,LayersBase *Base)
{
	if(::Load(f,ShadowLevel)==false)	return false;
	if(::Load(f,ShadowNumber)==false)	return false;
	return ErrorGroupPack::Load(f,Base);
}

bool    ErrorGroupPackWithShadowTree::Save(QIODevice *f)
{
	if(::Save(f,ShadowLevel)==false)	return false;
	if(::Save(f,ShadowNumber)==false)	return false;
	return ErrorGroupPack::Save(f);
}
bool    ErrorGroupPackWithShadowTree::Save(FileThread *f)
{
	if(f->Save(ShadowLevel)==false)		return false;
	if(f->Save(ShadowNumber)==false)	return false;
	return ErrorGroupPack::Save(f);
}
    
ErrorGroupPackWithShadowTreePack  &ErrorGroupPackWithShadowTreePack::operator=(const ErrorGroupPackWithShadowTreePack &src)
{
	RemoveAll();
	for(ErrorGroupPackWithShadowTree *s=GetFirst();s!=NULL;s=s->GetNext()){
		ErrorGroupPackWithShadowTree *d=new ErrorGroupPackWithShadowTree();
		*d=*s;
		AppendList(d);
	}
	return *this;
}
bool    ErrorGroupPackWithShadowTreePack::Load(QIODevice *f,LayersBase *Base)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ErrorGroupPackWithShadowTree *s=new ErrorGroupPackWithShadowTree();
		if(s->Load(f,Base)==false){
			return false;
		}
		AppendList(s);
	}
	return true;
}
bool    ErrorGroupPackWithShadowTreePack::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ErrorGroupPackWithShadowTree *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    ErrorGroupPackWithShadowTreePack::Save(FileThread *f)
{
	int32	N=GetCount();
	if(f->Save(N)==false){
		return false;
	}
	for(ErrorGroupPackWithShadowTree *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Save(f)==false){
			return false;
		}
	}
	return true;
}

DisplayNGListCategorized::DisplayNGListCategorized(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LastSelectedRow		=-1;
	ResetPosition		=true;
	AllocatedPageCount	=0;
	CmdReq				=NULL;
	CmdAck				=NULL;
	ErrorGroupData		=NULL;
	ColCount			=0;
	PhaseNumb			=1;
	FirstPointAfterInspection	=false;

	NGList.move(0,0);
	resize(250,250);
	NGList.setParent(this);
	connect(&NGList,SIGNAL(itemEntered (QTableWidgetItem *)),this,SLOT(ListItemClicked (QTableWidgetItem *)));
	connect(&NGList,SIGNAL(itemSelectionChanged ()),this,SLOT(ListItemSelectionChanged()),Qt::QueuedConnection);
	NGList.setSelectionMode(QAbstractItemView::SingleSelection);
	NGList.setSelectionBehavior(QAbstractItemView::SelectItems);
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

	TM.setInterval(300);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
}

DisplayNGListCategorized::~DisplayNGListCategorized(void)
{
	ReleaseMemory();
}


void	DisplayNGListCategorized::Prepare(void)
{
	AllocateMemory();

	NGList.setColumnCount(ColCount);
	NGList.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ShowInPlayer(-1);

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioEffective	=new SignalOperandInt(this,431,/**/"DisplayNGListCategorized:ioEffective");
			ioNG_X		=new SignalOperandInt(this,429,/**/"DisplayNGListCategorized:ioNG_X");
			ioNG_Y		=new SignalOperandInt(this,430,/**/"DisplayNGListCategorized:ioNG_Y");
			ioNGCount	=new SignalOperandInt(this,433,/**/"DisplayNGListCategorized:ioNGCount");
			ioCurrentNG	=new SignalOperandInt(this,432,/**/"DisplayNGListCategorized:ioCurrentNG");

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
			}
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
void	DisplayNGListCategorized::BuildForShow(void)
{
	//ColCount=0;
	//NGList.setColumnCount(ColCount);	
	//NGList.setRowCount(0);
}

void	DisplayNGListCategorized::AllocateMemory(void)
{
	if(ErrorGroupData!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<AllocatedPageCount;page++){
				delete	ErrorGroupData[phase][page];
			}
			delete	[]ErrorGroupData[phase];
		}
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
	ErrorGroupData	=new ErrorGroupPackWithShadowTreePack**[PhaseNumb];
	for(int phase=0;phase<PhaseNumb;phase++){
		ErrorGroupData[phase]=new ErrorGroupPackWithShadowTreePack*[AllocatedPageCount];
		for(int page=0;page<AllocatedPageCount;page++){
			ErrorGroupData[phase][page]=new ErrorGroupPackWithShadowTreePack();
		}
	}
}

void	DisplayNGListCategorized::ReleaseMemory(void)
{
	if(ErrorGroupData!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<AllocatedPageCount;page++){
				delete	ErrorGroupData[phase][page];
			}
			delete	[]ErrorGroupData[phase];
		}
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
}

void	DisplayNGListCategorized::SlotChangedPhasePageLayer()
{
	ReleaseMemory();
	AllocateMemory();
}

void	DisplayNGListCategorized::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	InitializedSpecifiedBroadcaster	*InitializedSpecifiedBroadcasterVar=dynamic_cast<InitializedSpecifiedBroadcaster *>(v);
	if(InitializedSpecifiedBroadcasterVar!=NULL){
		ShowInPlayer(0);
	}
}
void	DisplayNGListCategorized::ResizeAction()
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

void	DisplayNGListCategorized::ShowInPlayer(int64 shownInspectionID)
{
	//if(GetLayersBase()->GetCurrentScanPhaseNumber()!=0)
	GetLayersBase()->SetShouldWriteResult(true);
	ShownInspectionID	=shownInspectionID;
	TM.start();
}


void	DisplayNGListCategorized::SlotTimeout()
{
	if(GetParamGlobal()->OutputOnlyPhase==-1
	|| GetParamGlobal()->OutputOnlyPhase==GetLayersBase()->GetCurrentScanPhaseNumber()){
		NGList.setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);

		if(ShownInspectionID>=0){
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
						for(int page=0;page<AllocatedPageCount;page++){
							delete	ErrorGroupData[phase][page];
						}
						delete	[]ErrorGroupData[phase];
					}
					delete	[]ErrorGroupData;
					ErrorGroupData=NULL;
				}

				AllocatedPageCount=GetPageNumb();
				CmdReq	=new GUICmdReqNGList*[AllocatedPageCount];
				CmdAck	=new GUICmdSendNGList*[AllocatedPageCount];
				for(int page=0;page<AllocatedPageCount;page++){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					CmdReq[page]=new GUICmdReqNGList (GetLayersBase(),sRoot,sName,GlobalPage);
					CmdAck[page]=new GUICmdSendNGList(GetLayersBase(),sRoot,sName,GlobalPage);
				}
			}
			if(PhaseNumb!=GetPhaseNumb() && ErrorGroupData!=NULL){
				for(int phase=0;phase<PhaseNumb;phase++){
					for(int page=0;page<AllocatedPageCount;page++){
						delete	ErrorGroupData[phase][page];
					}
					delete	[]ErrorGroupData[phase];
				}
				delete	[]ErrorGroupData;
				ErrorGroupData=NULL;
				PhaseNumb=GetPhaseNumb();
			}
			if(ErrorGroupData==NULL){
				PhaseNumb=GetPhaseNumb();
				ErrorGroupData	=new ErrorGroupPackWithShadowTreePack**[PhaseNumb];
				for(int phase=0;phase<PhaseNumb;phase++){
					ErrorGroupData[phase]=new ErrorGroupPackWithShadowTreePack*[AllocatedPageCount];
					for(int page=0;page<AllocatedPageCount;page++){
						ErrorGroupData[phase][page]=new ErrorGroupPackWithShadowTreePack();
					}
				}
			}
			
			//for(int phase=0;phase<PhaseNumb;phase++){
			//	for(int page=0;page<AllocatedPageCount;page++){
			//		ErrorGroupData[phase][page]->RemoveAll();
			//	}
			//}
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				CmdReq[page]->ShownInspectionID=ShownInspectionID;
				if(CmdReq[page]->Send(GlobalPage ,0,*CmdAck[page])==true){
					for(int phase=0;phase<PhaseNumb;phase++){
						for(ErrorGroupPackWithShadowTree *t=CmdAck[page]->ErrorGroupData[phase].GetFirst();t!=NULL;t=t->GetNext()){
							ErrorGroupPackWithShadowTree	*dE=new ErrorGroupPackWithShadowTree();
							*dE=*t;
							ErrorGroupData[phase][page]->AppendList(dE);
						}
					}
					
				}
			}
		}
		for(int i=0;i<ColCount;i++){
			NGListContainerDim[i].RemoveAll();
		}

		for(int page=0;page<GetPageNumb();page++){
			for(int phase=0;phase<PhaseNumb;phase++){
				for(ErrorGroupPackWithShadowTree *t=CmdAck[page]->ErrorGroupData[phase].GetFirst();t!=NULL;t=t->GetNext()){
					for(ErrorGroup *e=t->ErrorGroupPack::GetFirst();e!=NULL;e=e->GetNext()){
						int Index=0;
						for(;Index<ColCount;Index++){
							if(NGListContainerDim[Index].CategoryName==e->GetMessageStr()){
								break;
							}
						}
						if(Index>=ColCount){
							if(ColCount<100){
								ColCount++;
								Index=ColCount-1;
								NGListContainerDim[Index].RemoveAll();
								NGListContainerDim[Index].CategoryName=e->GetMessageStr();
							}
							else{
								goto	LNext;
							}
						}
						NGListData	*w	=new NGListData();
						w->ShadowLevel =t->ShadowLevel ;
						w->ShadowNumber=t->ShadowNumber;
						w->Phase		=phase;
						w->Page			=page;
						e->GetCenter(w->CenterXInMaster,w->CenterYInMaster);
						w->Cause		=e->GetCause();
						w->Message		=e->GetMessageStr();
						w->E			=e;

						NGListContainerDim[Index].AppendList(w);
					}
				}
			}
		}
LNext:;

		int	TotalErrorNumb=0;
		int	LNumb=0;
		for(int i=0;i<ColCount;i++){
			int	n=NGListContainerDim[i].GetNumber();
			if(n>=LNumb){
				LNumb=n;
			}
			TotalErrorNumb+=n;
		}
		if(ioNGCount!=NULL){
			ioNGCount->Set(TotalErrorNumb);
		}

		NGList.setColumnCount(ColCount);	
		NGList.setRowCount(LNumb);
		if(ColCount>0){
			for(int col=0;col<ColCount;col++){
				::SetColumnWidthInTable(&NGList ,col, 100/ColCount);
			}

			//NGList.setCurrentCell(0,0);
			NGList.setUpdatesEnabled(false);
			NGList.clearSelection();

			for(int col=0;col<ColCount;col++){
				int	row=0;
				for(NGListData *w=NGListContainerDim[col].GetFirst();w!=NULL;w=w->GetNext(),row++){
					if(w->Cause.isEmpty()==false)
						::SetDataToTable(&NGList,col,row, w->Cause);
					else
						::SetDataToTable(&NGList,col,row, w->Message);
				}
			}
			NGList.setUpdatesEnabled(true);
		

			if(ResetPosition==true){
				if(LNumb!=0){
					if(FirstPointAfterInspection==true){
						NGList.setFocus();
						NGList.setCurrentCell(0,0);
					}
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
	//GetLayersBase()->SetShouldWriteResult(false);
}


void	DisplayNGListCategorized::ListItemSelectionChanged ()
{
	int row	=NGList.currentRow();
	if(row<0)
		return;
	int	col	=NGList.currentColumn();
	if(col<0)
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

	//int	CRow=0;
	//ErrorGroup *E=NULL;
	//int	CPhase=0;
	//for(int phase=0;phase<PhaseNumb;phase++){
	//	for(int page=0;page<AllocatedPageCount;page++){
	//		if(ErrorGroupData[phase][page]!=NULL){
	//			for(ErrorGroupPackWithShadowTree *t=ErrorGroupData[phase][page]->GetFirst();t!=NULL;t=t->GetNext()){
	//				for(ErrorGroup *e=t->ErrorGroupPack::GetFirst();e!=NULL;e=e->GetNext(),CRow++){
	//					if(CRow==row){
	//						E=e;
	//						CPhase=phase;
	//						goto	FoundE;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	int	CRow=0;
	ErrorGroup *E=NULL;
	NGListData	*W=NULL;
	int	CPhase=0;
	for(NGListData *w=NGListContainerDim[col].GetFirst();w!=NULL;w=w->GetNext(),CRow++){
		if(CRow==row){
			W=w;
			E=w->E;
			CPhase=w->Phase;
			goto	FoundE;
		}

	}

	FoundE:;
	if(E!=NULL && W!=NULL){
		int	ex1,ey1,ex2,ey2;
		E->GetXY(ex1,ey1,ex2,ey2);
		DataInPage *pdata=GetLayersBase()->GetPageData(E->GetPage());
		int	X=(ex1+ex2)/2 +pdata->GetOutlineOffset()->x;
		int	Y=(ey1+ey2)/2 +pdata->GetOutlineOffset()->y;
		LayersBase	*LBase=GetLayersBase()->GetShadowTree(W->ShadowLevel ,W->ShadowNumber);
		//LBase->ConvertToTop(X,Y);

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
					d->ShowCenter(X,Y);
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
						d->ShowCenter(X,Y);
					}
				}
			}
		}

		if(ioNG_X!=NULL && ioNG_Y!=NULL && ioEffective!=NULL){
			ioNG_X->Set(X);
			ioNG_Y->Set(Y);
			ioEffective->Set(1);
		}
		AlgorithmBase *RBase = GetLayersBase()->GetAlgorithmBase(/**/"Review", /**/"ReviewStructure");
		if(RBase!=NULL){
			ReviewCommonPacket::CmdMoveVRSWithAlignment moveVRS(GetLayersBase());
			DataInPage *pdata=LBase->GetPageData(E->GetPage());

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
void DisplayNGListCategorized::keyReleaseEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Up || event->key()==Qt::Key_Down || event->key()==Qt::Key_Return){
		ListItemSelectionChanged ();
		event->accept();
	}
}

void	DisplayNGListCategorized::ListItemClicked ( QTableWidgetItem *)
{
	int row	=NGList.currentRow();
	if(row<0)
		return;
	int	col	=NGList.currentColumn();
	if(col<0)
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
	NGListData	*W=NULL;
	int	CPhase=0;
	for(NGListData *w=NGListContainerDim[col].GetFirst();w!=NULL;w=w->GetNext(),CRow++){
		if(CRow==row){
			E=w->E;
			W=w;
			CPhase=w->Phase;
			goto	FoundE;
		}
	}
	FoundE:;
	if(E!=NULL && W!=NULL){

		int	ex1,ey1,ex2,ey2;
		E->GetXY(ex1,ey1,ex2,ey2);
		DataInPage *pdata=GetLayersBase()->GetPageData(E->GetPage());
		int	X=(ex1+ex2)/2 +pdata->GetOutlineOffset()->x;
		int	Y=(ey1+ey2)/2 +pdata->GetOutlineOffset()->y;
		//LayersBase	*LBase=GetLayersBase()->GetShadowTree(W->ShadowLevel ,W->ShadowNumber);
		//LBase->ConvertToTop(X,Y);

		GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelName);
		if(F!=NULL){
			DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
			if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
				if(pdata!=NULL){
					d->ShowCenter(X,Y);
				}
			}
		}
		for(int i=0;i<TargetImagePanelNames.count();i++){
			GUIFormBase	*F=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelNames[i]);
			if(F!=NULL){
				DisplayImage	*d=dynamic_cast<DisplayImage *>(F);
				if(d!=NULL && (d->ShowFixedPhase==-1 || d->ShowFixedPhase==CPhase)){
					if(pdata!=NULL){
						d->ShowCenter(X,Y);
					}
				}
			}
		}
		if(ioNG_X!=NULL && ioNG_Y!=NULL && ioEffective!=NULL){
			ioNG_X->Set(X);
			ioNG_Y->Set(Y);
			ioEffective->Set(1);
		}
	}
	if(ioCurrentNG!=NULL){
		ioCurrentNG->Set(row);
	}
}
void	DisplayNGListCategorized::OperandChanged()
{
}

void	DisplayNGListCategorized::SlotClicked ()
{
	int row	=NGList.currentRow();
	if(LastSelectedRow==row){
		ListItemSelectionChanged ();
	}
}

void	DisplayNGListCategorized::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetCurrentInfo	*CmdGetCurrentInfoVar=dynamic_cast<CmdGetCurrentInfo *>(packet);
	if(CmdGetCurrentInfoVar!=NULL){
		int row	=NGList.currentRow();
		if(row<0)
			return;
		int	col	=NGList.currentColumn();
		if(col<0)
			return;
		int	CRow=0;
		for(NGListData *w=NGListContainerDim[col].GetFirst();w!=NULL;w=w->GetNext(),CRow++){
			if(CRow==row){
				CmdGetCurrentInfoVar->Phase	=w->Phase;
				CmdGetCurrentInfoVar->Page	=w->Page;
				if(w->E!=NULL){
					if(w->E->RepresentativeItemPoint!=NULL){
						CmdGetCurrentInfoVar->Layer	=w->E->RepresentativeItemPoint->GetLayer();
						CmdGetCurrentInfoVar->ItemID=w->E->RepresentativeItemPoint->GetItemID();
						if(w->E->RepresentativeItemPoint->GetAlgorithmItemRoot()!=NULL){
							CmdGetCurrentInfoVar->RepresentativeItem	=w->E->RepresentativeItemPoint->GetAlgorithmItemRoot();
							CmdGetCurrentInfoVar->ShadowLevel =w->ShadowLevel ;
							CmdGetCurrentInfoVar->ShadowNumber=w->ShadowNumber;
							CmdGetCurrentInfoVar->LibID		=w->E->RepresentativeItemPoint->GetAlgorithmItemRoot()->GetLibID();
							CmdGetCurrentInfoVar->LibType	=w->E->RepresentativeItemPoint->GetAlgorithmItemRoot()->GetLibType();
						}
					}
					else
					if(w->E->TmpRepresentativeItem[0]!=NULL){
						CmdGetCurrentInfoVar->Layer	=w->E->TmpRepresentativeItem[0]->GetLayer();
						CmdGetCurrentInfoVar->ItemID=w->E->TmpRepresentativeItem[0]->GetItemID();
						if(w->E->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()!=NULL){
							CmdGetCurrentInfoVar->ShadowLevel =w->ShadowLevel ;
							CmdGetCurrentInfoVar->ShadowNumber=w->ShadowNumber;
							CmdGetCurrentInfoVar->RepresentativeItem	=w->E->TmpRepresentativeItem[0]->GetAlgorithmItemRoot();
							CmdGetCurrentInfoVar->LibID		=w->E->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()->GetLibID();
							CmdGetCurrentInfoVar->LibType	=w->E->TmpRepresentativeItem[0]->GetAlgorithmItemRoot()->GetLibType();
						}
					}
				}
				return;
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
	return(true);
}
bool	GUICmdReqNGList::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	return(true);
}

void	GUICmdReqNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGList	*SendBack=GetSendBack(GUICmdSendNGList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Initial();
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ErrorGroupPackWithShadowTreePack	*DestPack=&SendBack->ErrorGroupData[phase];
			ErrorGroupPackWithShadowTree	*dG=new ErrorGroupPackWithShadowTree();
			dG->ShadowLevel	=GetLayersBase()->GetShadowLevel();
			dG->ShadowNumber=GetLayersBase()->GetShadowNumber();
			DestPack->AppendList(dG);

			NGImageContainerInPhase	*Ph=R->GetNGImageInPhase(phase);
			if(Ph!=NULL){
				NGImageContainerInPage	*p=Ph->GetNGImageInPage(localPage);
				if(p!=NULL){
					for(ErrorGroup *e=p->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
						ErrorGroup	*G=new ErrorGroup(GetLayersBase());
						*G=*e;
						if(e->TmpRepresentativeItemCount>0){
							G->SetMessageStr(e->TmpRepresentativeItem[0]->ResultItemToString());
						}
						dG->AppendList(G);
					}
				}
			}
		}
	}
	int	ShadowChildCount=GetLayersBase()->GetShadowChildrenCount();
	for(int i=0;i<ShadowChildCount;i++){
		ShadowTree	*c=GetLayersBase()->GetShadowChildren(i);
		TransformBase	&TransformToMain	=c->MakeTransformFromMain();
		LayersBase	*LBase=c->GetTreeLayersBase();
		ResultInspection	*R=LBase->GetBufferedResult(ShownInspectionID);
		if(R!=NULL){
			for(int phase=0;phase<LBase->GetPhaseNumb();phase++){
				ErrorGroupPackWithShadowTreePack	*DestPack=&SendBack->ErrorGroupData[phase];
				ErrorGroupPackWithShadowTree	*dG=new ErrorGroupPackWithShadowTree();
				dG->ShadowLevel	=LBase->GetShadowLevel();
				dG->ShadowNumber=LBase->GetShadowNumber();
				DestPack->AppendList(dG);

				NGImageContainerInPhase	*Ph=R->GetNGImageInPhase(phase);
				if(Ph!=NULL){
					NGImageContainerInPage	*p=Ph->GetNGImageInPage(localPage);
					if(p!=NULL){
						for(ErrorGroup *e=p->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
							ErrorGroup	*G=new ErrorGroup(LBase);
							*G=*e;
							int qx1,qy1,qx2,qy2;
							e->GetXY(qx1,qy1,qx2,qy2);
							double	DestX1,DestY1;
							double	DestX2,DestY2;
							TransformToMain.ReverseTransform(qx1,qy1
															,DestX1,DestY1);
							TransformToMain.ReverseTransform(qx2,qy2
															,DestX2,DestY2);

							G->SetRectangle(DestX1,DestY1 ,DestX2,DestY2);
							if(e->TmpRepresentativeItemCount>0){
								G->SetMessageStr(e->TmpRepresentativeItem[0]->ResultItemToString());
							}
							dG->AppendList(G);
						}
					}
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
	ErrorGroupData=new ErrorGroupPackWithShadowTreePack[GetPhaseNumb()];
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
	ErrorGroupData=new ErrorGroupPackWithShadowTreePack[GetPhaseNumb()];
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
