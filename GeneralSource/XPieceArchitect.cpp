/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceArchitect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XPieceArchitect.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlgorithmBase.h"
#include "XResultDLLManager.h"
#include "XArrangementFromFile.h"
#include "XGeneralStocker.h"

PieceClass::PCLayersBase::PCLayersBase(LayersBase *parent)
	:LayersBase(/**/"Piece",parent),ParentBase(parent)
{
}
bool	PieceClass::PCLayersBase::Set(LayersBase *Base,int masterCode,PieceClass *parent
										,QString &ErrorMessageOfFalse)
{
	ParentBase			=Base;
	CurrentPath			=Base->GetSystemPath();
	UserPath			=Base->GetUserPath();
	RootDBase			=Base->GetDataBase();
	OriginalRootDBase	=false;
	DBLoader			=Base->GetDatabaseLoader();
	MasterCode			=masterCode;
	OnProcessing		=NULL;	//Base->OnProcessing;
	OperationLoggerData	=NULL;
	GeneralStockerData		=new GeneralStockerContainer(this);
	ShrinkingPackContainerInstance	=Base->GetShrinkingPackContainer();

	InitialParamFromDatabase(masterCode);
	GetParamGlobal()->NGCacheNumb=1;
	GetParamGlobal()->ResultDLLFileName="";
	GetParamGlobal()->ImageFilePath	=Base->GetParamGlobal()->ImageFilePath;

	InitialCreatePages(parent);
	InitialAllocExecuterDim();
	InitialResult();
	*LogicDLLBase	=*Base->GetLogicDLLBase();
	CreateAlgorithmPointer();
	ResultDLLBase	=NULL;
	//InitialArrangementDLL();
	GetArrangementDLLStock()->CopyPointerFrom(*Base->GetArrangementDLLStock());
	InitialAlgorithmLibrary();
	InitialAfterParamLoaded();
	bool CriticalErrorOccured=false;
	if(SQLLoadMasterData(masterCode,-1,true,CriticalErrorOccured
						 ,ErrorMessageOfFalse)==false){
		return false;
	}
	CloseInformed();
	return true;
}

PieceClass::PCLayersBase::~PCLayersBase(void)
{
	if(ParentBase!=NULL){
		ShrinkingPackContainerInstance=NULL;
	}
}


bool	PieceClass::PCLayersBase::ReLoadMasterDataForPiece(LayersBase *Base,int masterCode,PieceClass *parent
															,QString &ErrorMessageOfFalse)
{
	*LogicDLLBase	=*Base->GetLogicDLLBase();
	CreateAlgorithmPointer();
	GetArrangementDLLStock()->CopyPointerFrom(*Base->GetArrangementDLLStock());
	InitialAlgorithmLibrary();
	InitialAfterParamLoaded();
	bool CriticalErrorOccured=false;
	if(SQLLoadMasterData(masterCode,-1,true,CriticalErrorOccured,ErrorMessageOfFalse)==false)
		return false;
	CloseInformed();
	return true;
}

bool	PieceClass::PCLayersBase::GetOnTerminating(void)	const
{
	if(ParentBase!=NULL)
		return ParentBase->GetOnTerminating();
	return LayersBase::GetOnTerminating();
}

PieceClass::PieceClass(void)
{
	PieceLayersBase=new PCLayersBase(GetLayersBase());
	ZoomRateOnImage=-1;
}
PieceClass::PieceClass(const PieceClass &src)
{
	PieceLayersBase=new PCLayersBase(((PieceClass *)&src)->GetLayersBase());
	ZoomRateOnImage	=src.ZoomRateOnImage;
	LayerListOnImage=src.LayerListOnImage;
	for(AlgorithmImageList *a=src.ImageList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmImageList	*b=new AlgorithmImageList(*a);
		ImageList.AppendList(b);
	}
}
PieceClass::~PieceClass(void)
{
	delete	PieceLayersBase;
	PieceLayersBase=NULL;
}

PieceClass	&PieceClass::operator=(const PieceClass &src)
{
	PieceLayersBase=new PCLayersBase(((PieceClass *)&src)->GetLayersBase());
	ZoomRateOnImage	=src.ZoomRateOnImage;
	LayerListOnImage=src.LayerListOnImage;
	for(AlgorithmImageList *a=src.ImageList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmImageList	*b=new AlgorithmImageList(*a);
		ImageList.AppendList(b);
	}
	return *this;
}
bool	PieceClass::Initial(LayersBase *Base ,int masterCode,QString &ErrorMessageOfFalse)
{
	if(PieceLayersBase->Set(Base,masterCode,this,ErrorMessageOfFalse)==false){
		return false;
	}
	ExecuteInitialAfterEditInfo EInfo;
	PieceLayersBase->MakeExecuteInitialAfterEditInfo(EInfo);
	PieceLayersBase->ExecuteInitialAfterEdit(EInfo,false);
	return true;
}

bool	PieceClass::ReLoadMasterDataForPiece(LayersBase *Base,QString &ErrorMessageOfFalse)
{
	if(PieceLayersBase==NULL){
		ErrorMessageOfFalse="No PieceLayersBase";
		return false;
	}
	if(PieceLayersBase->ReLoadMasterDataForPiece(Base,PieceLayersBase->GetMasterCode(),this,ErrorMessageOfFalse)==false){
		return false;
	}
	ExecuteInitialAfterEditInfo EInfo;
	PieceLayersBase->MakeExecuteInitialAfterEditInfo(EInfo);
	PieceLayersBase->ExecuteInitialAfterEdit(EInfo,false);
	return true;
}

ThreadSequence		*PieceClass::GetThreadSequence(void)	const	{	return NULL;	}
ExecuteInspectBase	*PieceClass::GetExecuteInspect(void)	const	{	return NULL;	}

bool		PieceClass::SendData (int32 commID ,int globalPage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f 
								,ErrorCodeList &ErrorData)
{
	return PieceLayersBase->GetGuiInitializer()->TxData(globalPage ,IndoPacket,commID ,f,ErrorData);
}
bool		PieceClass::SendArray(int32 commID ,int globalPage
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QByteArray *f
								,ErrorCodeList &ErrorData)
{
	return PieceLayersBase->GetGuiInitializer()->TxData(globalPage ,IndoPacket,commID ,f,ErrorData);
}
bool		PieceClass::SendDataDirectComm(int32 commID ,int privatePage
						,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						,QBuffer *f 
						,ErrorCodeList &ErrorData)
{
	return true;
}
bool	PieceClass::SendIntegrationData (int slaveNo
								,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
								,QBuffer *f,ErrorCodeList &ErrorData)
{
	return true;
}

void		PieceClass::ReadyReadDirectComm(void)
{
}
bool	PieceClass::GUIIsEditMode(void)
{
	return PieceLayersBase->GetEntryPoint()->GUIIsEditMode();
}

void	PieceClass::WaitReadyReadAll(int milisec)
{
}
void	PieceClass::SetLanguageCode(int LanguageCode)
{
	if(PieceLayersBase!=NULL)
		PieceLayersBase->SetLanguageCode(LanguageCode);
}

QTcpSocket	*PieceClass::GetSocket(int ComNo)
{
	return PieceLayersBase->GetGuiInitializer()->GetSocket(ComNo);
}

QTcpSocket	*PieceClass::GetIntegrationSocket(int slaveNo)
{
	return PieceLayersBase->GetGuiInitializer()->GetIntegrationSocket(slaveNo);
}

AlgorithmItemRoot	*PieceClass::GetAlgorithmItem(const QString &DLLRoot,const QString &DLLName,int Layer ,int ItemID)
{
	if(PieceLayersBase!=NULL){
		AlgorithmBase	*A=PieceLayersBase->GetAlgorithmBase(DLLRoot,DLLName);
		if(A!=NULL){
			AlgorithmInPageRoot		*Pg=A->GetPageData(0);
			return Pg->GetItemData(Layer,ItemID);
		}
	}
	return NULL;
}

bool	PieceClass::SetAlgorithmItemData(int Command,const QString &DLLRoot,const QString &DLLName ,AlgorithmItemIndependentPack &IData)
{
	if(PieceLayersBase!=NULL){
		AlgorithmBase	*A=PieceLayersBase->GetAlgorithmBase(DLLRoot,DLLName);
		if(A!=NULL){
			for(AlgorithmItemIndependent *a=IData.Items.GetFirst();a!=NULL;a=a->GetNext()){
				QByteArray	AckData;
				A->SetIndependentItemData(Command,-1,0,a->Layer,a->ItemID,a->Data,IData.EdittedMemberID,a->Something,AckData);
			}
			return true;
		}
	}
	return false;
}


bool	PieceClass::SaveAlgorithmForMaster(const QString &DLLRoot,const QString &DLLName)
{
	if(PieceLayersBase!=NULL){
		AlgorithmBase	*A=PieceLayersBase->GetAlgorithmBase(DLLRoot,DLLName);
		if(A!=NULL)
			return PieceLayersBase->SQLUpdateAlgorithmOnly(A);
	}
	return false;
}
ExeResult	PieceClass::ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	ret=GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	return ret;
}


GUIFormBase	*PieceClass::GUIMouseLeftDownInEdit(GUIFormBase *Current ,QMouseEvent * Event){	return NULL;	}
void	PieceClass::GUISetProperty(GUIFormBase *Current,GUIFormBase *PutTop)	{}
void	PieceClass::GUIRemoveItem(GUIFormBase *w)			{}
GUIInstancePack		*PieceClass::GetGUIInstancePack(void)
{	
	return(PieceLayersBase->GetGuiInitializer()->GetGUIInstanceRoot());
}
DirectComm			*PieceClass::CreateDirectComm(QObject * parent){	return NULL;	}
bool				PieceClass::InitialDirectCommInSlave(DirectComm	*p,QObject * parent ,SystemConnectionInfoContainer &){	return true;	}
int					PieceClass::GetDirectCommIDFromGlobalPage(int globalPageTo){	return 0;	}


QImage	*PieceClass::GetAlgorithmImage(int LocalPage
										,IntList &LayerList 
									   ,const QString &DLLRoot ,const QString &DLLName 
									   ,double ZoomRate
									   ,const QColor &ncol 
									   ,int ntranparentLevel)
{
	if(ZoomRateOnImage==ZoomRate && LayerListOnImage==LayerList){
		for(AlgorithmImageList *c=ImageList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetDLLRoot()==DLLRoot && c->GetDLLName()==DLLName){
				return c->GetImage();
			}
		}
	}
	AlgorithmBase	*P=GetLayersBase()->GetAlgorithmBase(DLLRoot ,DLLName);
	if(P==NULL){
		return NULL;
	}
	int	ImageWidth	=ceil(GetLayersBase()->GetDotPerLine(LocalPage)*ZoomRate);
	int	ImageHeight	=ceil(GetLayersBase()->GetMaxLines(LocalPage)*ZoomRate);
	QImage	*Image=new QImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	AlgorithmDrawAttr	DummyAttr(ncol ,ntranparentLevel
								, ncol ,ntranparentLevel
								, ncol ,ntranparentLevel);
	P->Draw(*Image, LayerList ,0,0,ZoomRate ,&DummyAttr);
	for(AlgorithmImageList *c=ImageList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetDLLRoot()==DLLRoot && c->GetDLLName()==DLLName){
			if(c->GetImage()!=NULL){
				c->DeleteImage();
			}
			c->SetImage(Image);
			return Image;
		}
	}
	AlgorithmImageList	*ci=new AlgorithmImageList(DLLRoot,DLLName,Image);
	ImageList.AppendList(ci);
	return Image;
}



PieceClass	*PieceStocker::SearchAndLoad(int masterCode,QString &ErrorMessageOfFalse)
{
	MutexLoader.lockForRead();
	for(PieceClass *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetMasterCode()==masterCode){
			MutexLoader.unlock();
			return p;
		}
	}
	MutexLoader.unlock();

	MutexPieceInitializer.lock();

	MutexLoader.lockForRead();
	for(PieceClass *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetMasterCode()==masterCode){
			MutexLoader.unlock();
			MutexPieceInitializer.unlock();
			return p;
		}
	}
	MutexLoader.unlock();

	PieceClass	*pi=new PieceClass();
	LayersBase		*PBase=pi->GetLayersBase();
	PBase->SetBootingLevel(1);
	if(pi->Initial(GetLayersBase() ,masterCode,ErrorMessageOfFalse)==false){
		MutexPieceInitializer.unlock();
		delete	pi;
		return NULL;
	}
	PBase->ReadLogicSettingFiles(true);

	MutexLoader.lockForWrite();
	AppendList(pi);
	MutexLoader.unlock();
	MutexPieceInitializer.unlock();
	return pi;
}
void	PieceStocker::RemoveFromList(PieceClass *p)
{
	MutexLoader.lockForWrite();
	RemoveList(p);
	MutexLoader.unlock();
}

QImage	*PieceStocker::GetAlgorithmImage(int LocalPage
										,int MasterCode ,IntList &LayerList 
										 ,const QString &DLLRoot ,const QString &DLLName 
										 ,double ZoomRate 
										 ,const QColor &ncol 
										 ,int ntranparentLevel
										 ,QString &ErrorMessageOfFalse)
{
	PieceClass	*P=SearchAndLoad(MasterCode,ErrorMessageOfFalse);
	if(P==NULL){
		return NULL;
	}
	return P->GetAlgorithmImage(LocalPage,LayerList ,DLLRoot ,DLLName ,ZoomRate,ncol ,ntranparentLevel);
}

bool	PieceStocker::ReLoadMasterDataForPiece(QString &ErrorMessageOfFalse)
{
	for(PieceClass *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ReLoadMasterDataForPiece(GetLayersBase(),ErrorMessageOfFalse)==false){
			return false;
		}
	}
	return true;
}

bool	PieceStocker::ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo,QString &ErrorMessageOfFalse)
{
	for(PieceClass *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ReLoadMasterDataForPiece(GetLayersBase(),ErrorMessageOfFalse)==false){
			return false;
		}
		a->ExecuteInitialAfterEdit	(ExeID,EInfo);
	}
	return true;
}