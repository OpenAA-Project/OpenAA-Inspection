/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <QMutex>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "SelectGeneralStocker.h"
#include "XLearningRule.h"
#include "XPassword.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "ShowLoadingDLLForm.h"
#include "XLotInformation.h"
#include "XHistgramByParam.h"
#include "XDateTime.h"
#include "AlertDialog.h"
#include "XShareMasterData.h"
#include "XCSV.h"
#include "XPrinterManager.h"
#include "XPointer.h"
#include "XImageExpand.h"
#include "LensWindowForm.h"
#include "XIntegrationComm.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "XResize.h"
#include "XResultAnalizer.h"

ClipboardAlgorithmItem::ClipboardAlgorithmItem(void)
{	
	Page=-1;
	Layer=-1;
	Vector=NULL;	
}

bool	ClipboardAlgorithmItem::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,ItemData)==false){
		return false;
	}
	if(::Save(f,ItemClassType)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(Vector==NULL){
		if(::Save(f,false)==false){
			return false;
		}
	}
	else{
		if(::Save(f,true)==false){
			return false;
		}
		int	id=Vector->GetID();
		if(::Save(f,id)==false){
			return false;
		}
		if(Vector->Save(f)==false){
			return false;
		}
	}

	return true;
}
bool	ClipboardAlgorithmItem::Load(QIODevice *f)
{
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,ItemData)==false){
		return false;
	}
	if(::Load(f,ItemClassType)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	bool	VectorMode;
	if(::Load(f,VectorMode)==false){
		return false;
	}
	if(VectorMode==true){
		int	id;
		if(::Load(f,id)==false){
			return false;
		}
		if(Vector!=NULL){
			delete	Vector;
		}
		Vector=VectorLineBase::Create(id);
		if(Vector==NULL){
			return false;
		}
		if(Vector->Load(f)==false){
			return false;
		}
	}

	return true;
}
bool	ClipboardAlgorithmItem::Draw(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col)
{
	bool	RetArea=Area.Draw(dx,dy ,&pnt ,Col.rgba()	,ZoomRate ,movx ,movy);
	bool	RetVector=false;
	if(Vector!=NULL){
		RetVector=Vector->DrawShift(dx,dy ,pnt ,Col.rgba(),ZoomRate ,movx ,movy);
	}
	if(RetArea==true || RetVector==true){
		return true;
	}
	return false;
}

ClipboardAlgorithmItem	&ClipboardAlgorithmItem::operator=(ClipboardAlgorithmItem &src)
{
	Area			=src.Area;
	ItemData		=src.ItemData;
	ItemClassType	=src.ItemClassType;
	Page			=src.Page;
	Layer			=src.Layer;
	if(Vector!=NULL){
		delete	Vector;
		Vector=NULL;
	}
	if(src.Vector!=NULL){
		int	id=src.Vector->GetID();
		Vector=VectorLineBase::Create(id);
		*Vector=*src.Vector;
	}
	return *this;
}

bool	ClipboardAlgorithm::Save(int localPage,QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(Base->GetDLLName(DLLRoot ,DLLName)==true){
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		int64	N=0;
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Page==localPage){
				N++;
			}
		}
		if(::Save(f,N)==false){
			return false;
		}
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Page==localPage){
				if(c->Save(f)==false){
					return false;
				}
			}
		}
		if(::Save(f,Remark)==false){
			return false;
		}
		return true;
	}
	return false;
}
bool	ClipboardAlgorithm::Load(int localPage,QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	Base=LBase->GetAlgorithmBase(DLLRoot ,DLLName);
	int64	N;
	if(::Load(f,N)==false){
		return false;
	}
	if(localPage==0){
		Items.RemoveAll();
	}
	for(int i=0;i<(int)N;i++){
		ClipboardAlgorithmItem *c=new ClipboardAlgorithmItem();
		if(c->Load(f)==false){
			delete	c;
			return false;
		}
		Items.AppendList(c);
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	return true;
}


bool	ClipboardAlgorithm::Save(QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(Base->GetDLLName(DLLRoot ,DLLName)==true){
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		int64	N=Items.GetCount();
		if(::Save(f,N)==false){
			return false;
		}
		for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->Save(f)==false){
				return false;
			}
		}
		if(::Save(f,Remark)==false){
			return false;
		}
		return true;
	}
	return false;
}
bool	ClipboardAlgorithm::Load(QIODevice *f)
{
	QString DLLRoot;
	QString DLLName;
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	Base=LBase->GetAlgorithmBase(DLLRoot ,DLLName);
	int64	N;
	if(::Load(f,N)==false){
		return false;
	}
	Items.RemoveAll();
	for(int i=0;i<(int)N;i++){
		ClipboardAlgorithmItem *c=new ClipboardAlgorithmItem();
		if(c->Load(f)==false){
			delete	c;
			return false;
		}
		Items.AppendList(c);
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	return true;
}
bool	ClipboardAlgorithm::Draw(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &Col)
{
	bool	Ret=false;
	for(ClipboardAlgorithmItem *c=Items.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Page==localPage){
			if(c->Draw(dx,dy,pnt, movx ,movy ,ZoomRate ,Col)==true){
				Ret=true;
			}
		}
	}
	return Ret;
}
ClipboardAlgorithm	&ClipboardAlgorithm::operator=(ClipboardAlgorithm &src)
{
	LBase	=src.LBase;
	Base	=src.Base;
	Items.RemoveAll();
	for(ClipboardAlgorithmItem *a=src.Items.GetFirst();a!=NULL;a=a->GetNext()){
		ClipboardAlgorithmItem *b=new ClipboardAlgorithmItem();
		*b= *a;
		Items.AppendList(b);
	}
	CreatedTime	=src.CreatedTime;
	Remark	=src.Remark;

	return *this;
}

void	ClipboardAlgorithm::CopyInPages(ClipboardAlgorithm &src ,IntList &LocalPages)
{
	LBase	=src.LBase;
	Base	=src.Base;
	Items.RemoveAll();
	for(ClipboardAlgorithmItem *a=src.Items.GetFirst();a!=NULL;a=a->GetNext()){
		if(LocalPages.IsInclude(a->Page)==true){
			ClipboardAlgorithmItem *b=new ClipboardAlgorithmItem();
			*b= *a;
			Items.AppendList(b);
		}
	}
	CreatedTime	=src.CreatedTime;
	Remark	=src.Remark;
}

void	ClipboardAlgorithm::Absorb(ClipboardAlgorithm *From)
{
	ClipboardAlgorithmItem	*c;
	while((c=From->Items.GetFirst())!=NULL){
		From->Items.RemoveList(c);
		Items.AppendList(c);
	}
}

ClipboardList::~ClipboardList(void)
{
	ClipboardAlgorithm	*p;
	while((p=GetFirst())!=NULL){
		RemoveList(p);
	}
}

void	ClipboardList::AppendList(ClipboardAlgorithm *item ,bool EnableDup)
{
	if(GetNumber()>=5){
		ClipboardAlgorithm	*a=GetFirst();
		RemoveList(a);
		delete	a;
	}
	if(EnableDup==false){
		for(ClipboardAlgorithm *a=GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Base==item->Base){
				RemoveList(a);
				delete a;
				break;
			}
		}
	}
	NPListPack<ClipboardAlgorithm>::AppendList(item);
}
ClipboardAlgorithm	*ClipboardList::Find(XDateTime &CreatedTime)
{
	for(ClipboardAlgorithm *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetCreatedTime()==CreatedTime){
			return a;
		}
	}
	return NULL;
}

PageAndLayerList::PageAndLayerList(void)
{
	Page= -1;
	Layer= -1;
}
PageAndLayerList	&PageAndLayerList::operator=(PageAndLayerList &src)
{
	Page=src.Page;
	Layer=src.Layer;
	return *this;
}

bool	PageAndLayerList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
bool	PageAndLayerList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

PageAndLayerFlagList::PageAndLayerFlagList(void)
{
	Page	= -1;
	Layer	= -1;
	Done	=false;
}
PageAndLayerFlagList::PageAndLayerFlagList(int page ,int layer)
{
	Page	=page;
	Layer	=layer;
	Done	=false;
}

PageAndLayerFlagList	&PageAndLayerFlagList::operator=(PageAndLayerFlagList &src)
{
	Page	=src.Page;
	Layer	=src.Layer;
	Done	=src.Done;
	return *this;
}

bool	PageAndLayerFlagList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Done)==false){
		return false;
	}
	return true;
}
bool	PageAndLayerFlagList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Done)==false){
		return false;
	}
	return true;
}

PageAndLayerFlagListContainer	&PageAndLayerFlagListContainer::operator+=(PageAndLayerFlagListContainer &src)
{
	for(PageAndLayerFlagList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		PageAndLayerFlagList	*d=new PageAndLayerFlagList();
		*d= *s;
		AppendList(d);
	}
	return *this;
}

PasteListMatrix::PasteListMatrix(void)
{
	GlobalPage	=-1;
	XPos		=0;
	YPos		=0;
}

bool	PasteListMatrix::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,XPos)==false)
		return false;
	if(::Save(f,YPos)==false)
		return false;
	return true;
}

bool	PasteListMatrix::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,XPos)==false)
		return false;
	if(::Load(f,YPos)==false)
		return false;
	return true;
}
PasteListMatrix	&PasteListMatrix::operator=(PasteListMatrix &src)
{
	GlobalPage	=src.GlobalPage;
	Layers		=src.Layers;
	XPos		=src.XPos;
	YPos		=src.YPos;
	return *this;
}

bool	PasteListMatrixContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(PasteListMatrix *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	PasteListMatrixContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		PasteListMatrix	*a=new PasteListMatrix();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
	
bool	PasteListMatrixContainer::Save(QStringListListCSV &csv)
{
	csv.clear();
	int	Row=0;
	for(PasteListMatrix *a=GetFirst();a!=NULL;a=a->GetNext(),Row++){
		csv.Set(0,Row,QString::number(a->GlobalPage));
		csv.Set(1,Row,QString::number(a->XPos));
		csv.Set(2,Row,QString::number(a->YPos));
	}
	return true;
}

bool	PasteListMatrixContainer::Load(QStringListListCSV &csv)
{
	RemoveAll();
	for(int Row=0;Row<csv.GetRowCount();Row++){
		PasteListMatrix	*a=new PasteListMatrix();
		bool	ok;
		a->GlobalPage	=csv.Get(0,Row).toInt(&ok);
		if(ok==false)
			return false;
		a->XPos			=csv.Get(1,Row).toInt(&ok);
		if(ok==false)
			return false;
		a->YPos			=csv.Get(2,Row).toInt(&ok);
		if(ok==false)
			return false;
		AppendList(a);
	}
	return true;
}
PasteListMatrixContainer	&PasteListMatrixContainer::operator=(PasteListMatrixContainer &src)
{
	RemoveAll();
	for(PasteListMatrix *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		PasteListMatrix	*b=new PasteListMatrix();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

//====================================================================================================
ThreadImageCompresserInPage::ThreadImageCompresserInPage(LayersBase *base,DataInPage *p)
:ServiceForLayers(base),ParentPage(p)
{	
	CloseMode=false;
}
ThreadImageCompresserInPage::~ThreadImageCompresserInPage(void)
{
	if(isRunning()==true){
		CloseMode=true;
		wait(300);
	}
}
void	ThreadImageCompresserInPage::Set(NGImageContainerInPage *point)
{
	Accessor.lock();
	NGImageContainerInPageContainer.AppendList(new NGImageContainerInPagePointerList(point));
	Accessor.unlock();
}

void ThreadImageCompresserInPage::run()
{
	for(;;){
		if((GetLayersBase()->GetOnTerminating()==true) || (CloseMode==true)){
			return;
		}
		msleep(10);
			
		Accessor.lock();
		NGImageContainerInPagePointerList	*r=NGImageContainerInPageContainer.GetFirst();
		if(r!=NULL){
			NGImageContainerInPageContainer.RemoveList(r);
		}
		Accessor.unlock();
		if(r!=NULL){
			r->GetPoint()->CompressImages();
			delete	r;
		}
	}
}
bool	ThreadImageCompresserInPage::IsDone(void)
{
	Accessor.lock();
	int	n=NGImageContainerInPageContainer.GetCount();
	Accessor.unlock();
	if(n==0)
		return true;
	return false;
}
int		ThreadImageCompresserInPage::GetCountOfCompressing(void)
{
	Accessor.lock();
	int	n=NGImageContainerInPageContainer.GetCount();
	Accessor.unlock();
	return n;
}
//====================================================================================================

DataInLayer::ConstructionData::ConstructionData(DataInLayer *parent)
{
	if(parent->GetEntryPoint()!=NULL){
		ResNumb=(int)pow(2.0,parent->GetEntryPoint()->GetParamGlobal()->CameraResolutionBit);
	}
	else{
		ResNumb=256;
	}
	if((ResNumb>65536) || (ResNumb<0)){
		Alert("Invalid Camera resolution bit");
	}
	RBrightTable=new BYTE[ResNumb];
	GBrightTable=new BYTE[ResNumb];
	BBrightTable=new BYTE[ResNumb];
	for(int i=0;i<ResNumb;i++){
		RBrightTable[i]=(BYTE)i;
		GBrightTable[i]=(BYTE)i;
		BBrightTable[i]=(BYTE)i;
	}
}

DataInLayer::ConstructionData::~ConstructionData(void)
{
	delete	[]RBrightTable;
	delete	[]GBrightTable;
	delete	[]BBrightTable;
	RBrightTable=NULL;
	GBrightTable=NULL;
	BBrightTable=NULL;
}

bool    DataInLayer::ConstructionData::SaveBrightTable(QIODevice *f)
{
	if(::Save(f,ResNumb)==false){
		return false;
	}
	if(f->write((const char *)RBrightTable,ResNumb*sizeof(RBrightTable[0]))!=ResNumb*sizeof(RBrightTable[0])){
		return false;
	}
	if(f->write((const char *)GBrightTable,ResNumb*sizeof(GBrightTable[0]))!=ResNumb*sizeof(GBrightTable[0])){
		return false;
	}
	if(f->write((const char *)BBrightTable,ResNumb*sizeof(BBrightTable[0]))!=ResNumb*sizeof(BBrightTable[0])){
		return false;
	}
	return true;
}
bool    DataInLayer::ConstructionData::LoadBrightTable(QIODevice *f)
{
	int32	iResNumb;
	if(::Load(f,iResNumb)==false){
		return false;
	}
	if(iResNumb<=ResNumb){
		ResNumb=iResNumb;
	}
	else{
		delete	[]RBrightTable;
		delete	[]GBrightTable;
		delete	[]BBrightTable;
		ResNumb=iResNumb;
		RBrightTable=new BYTE[iResNumb];
		GBrightTable=new BYTE[iResNumb];
		BBrightTable=new BYTE[iResNumb];
	}
	if(f->read((char *)RBrightTable,ResNumb*sizeof(RBrightTable[0]))!=ResNumb*sizeof(RBrightTable[0])){
		return false;
	}
	if(f->read((char *)GBrightTable,ResNumb*sizeof(GBrightTable[0]))!=ResNumb*sizeof(GBrightTable[0])){
		return false;
	}
	if(f->read((char *)BBrightTable,ResNumb*sizeof(BBrightTable[0]))!=ResNumb*sizeof(BBrightTable[0])){
		return false;
	}
	return true;
}

bool    DataInLayer::SaveAttr(QIODevice *f)
{
	if(CData.SaveBrightTable(f)==false){
		return false;
	}
	return true;
}
bool    DataInLayer::LoadAttr(QIODevice *f)
{
	if(CData.LoadBrightTable(f)==false){
		return false;
	}
	return true;
}

bool    DataInLayer::Save(QIODevice *f)
{
	bool	MasterBuffOk= !MasterBuff->IsNull();
	if(::Save(f,MasterBuffOk)==false){
		return false;
	}
	if(MasterBuffOk==true){
		if(MasterBuff->Save(f)==false){
			return false;
		}
	}
	bool	TargetBuffOk= !TargetBuff->IsNull();
	if(::Save(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuff->Save(f)==false){
			return false;
		}
	}
	ImageBuffer	Dummy;
	if(Dummy.Save(f)==false){
		return false;
	}
	if(Dummy.Save(f)==false){
		return false;
	}
	return true;
}
bool    DataInLayer::Load(QIODevice *f)
{
	bool	MasterBuffOk;
	if(::Load(f,MasterBuffOk)==false){
		return false;
	}
	if(MasterBuffOk==true){
		if(MasterBuff->Load(f)==false){
			return false;
		}
	}
	bool	TargetBuffOk;
	if(::Load(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuff->Load(f)==false){
			return false;
		}
	}
	ImageBuffer	Dummy;
	if(Dummy.Load(f)==false){
		return false;
	}
	if(Dummy.Load(f)==false){
		return false;
	}
	return true;
}

bool	DataInLayer::SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	bool	MasterBuffOk=!MasterBuff->IsNull();
	if(::Save(f,MasterBuffOk)==false){
		return false;
	}
	if(MasterBuffOk==true){
		if(MasterBuff->SavePartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	TargetBuffOk=!TargetBuff->IsNull();
	if(::Save(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuff->SavePartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	MinBuffOk=false;
	::Save(f,MinBuffOk);
	bool	MaxBuffOk=false;
	::Save(f,MaxBuffOk);

	return true;
}
bool	DataInLayer::LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	bool	MasterBuffOk;
	if(::Load(f,MasterBuffOk)==false){
		return false;
	}
	if(MasterBuffOk==true){
		if(MasterBuff->LoadPartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	TargetBuffOk;
	if(::Load(f,TargetBuffOk)==false){
		return false;
	}
	if(TargetBuffOk==true){
		if(TargetBuff->LoadPartially(f,X1,Y1,X2,Y2)==false){
			return false;
		}
	}
	bool	MinBuffOk;
	if(::Load(f,MinBuffOk)==false){
		return false;
	}
	bool	MaxBuffOk;
	if(::Load(f,MaxBuffOk)==false){
		return false;
	}
	return true;
}
void	DataInLayer::CopyImage(int sourceImageType ,int destImageType)
{
	ImageBuffer	*Src=NULL;	
	switch(sourceImageType){
		case ImageBufferMaster:
			Src= &GetMasterBuff();
			break;
		case ImageBufferTarget:
			Src= &GetTargetBuff();
			break;
	}
	ImageBuffer	*Dst=NULL;	
	switch(destImageType){
		case ImageBufferMaster:
			Dst= &GetMasterBuff();
			break;
		case ImageBufferTarget:
			Dst= &GetTargetBuff();
			break;
	}
	if((Src!=NULL) && (Dst!=NULL)){
		*Dst= *Src;
	}
}
//---------------------------------------------------------------------------
DataInLayer::DataInLayer(EntryPointBase	*pEntryPoint ,DataInPage *parent) 
: Exchanged(false),EntryPoint(pEntryPoint),CData(this),ParentPage(parent)
{
	Layer			=0;
	MasterBuff		=NULL;
	TargetBuff		=NULL;
	TargetTRBuff	=NULL;
	RawTargetBuff	=NULL;
	TempTargetBuff	=NULL;
	ViewTargetBuff	=NULL;
	CamTargetBuff	=NULL;
	BitBuff			=NULL;
}

DataInLayer::~DataInLayer(void)
{
	if(MasterBuff!=NULL){
		delete	MasterBuff;
		MasterBuff=NULL;
	}
	if(TargetBuff!=NULL){
		delete	TargetBuff;
		TargetBuff=NULL;
	}
	if(TargetTRBuff!=NULL){
		delete	TargetTRBuff;
		TargetTRBuff=NULL;
	}
	if(RawTargetBuff!=NULL){
		delete	RawTargetBuff;
		RawTargetBuff=NULL;
	}

	if(TempTargetBuff!=NULL){
		delete	TempTargetBuff;
		TempTargetBuff=NULL;
	}
	if(ViewTargetBuff!=NULL){
		delete	ViewTargetBuff;
		ViewTargetBuff=NULL;
	}
	if(CamTargetBuff!=NULL){
		delete	CamTargetBuff;
		CamTargetBuff=NULL;
	}
	if(BitBuff!=NULL){
		delete	BitBuff;
		BitBuff=NULL;
	}
}
void	DataInLayer::Initial(bool EnabledImageMemoryAllocation)
{
	MasterBuff		=new ImageBuffer();
	TargetBuff		=new ImageBuffer();
	TargetTRBuff	=new ImageBuffer();
	RawTargetBuff	=new ImageBuffer();
	ViewTargetBuff	=new ImageBuffer();
	CamTargetBuff	=new ImageBuffer();
	BitBuff			=new ImageBuffer();

	if(EnabledImageMemoryAllocation==true && GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			MasterBuff->Set(GetPage(),ImageBufferMaster ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		}
		if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
			if(GetParamGlobal()->AllocateTargetBuff==true){
				TargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			}
			if(GetParamGlobal()->AllocateTargetTRBuff==true){
				TargetTRBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->MaxLines,GetParamGlobal()->DotPerLine);
			}
		}
		else{
			DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
			if(GetParamGlobal()->AllocateTargetBuff==true){
				TargetBuff->SetDependency(P0L->GetTargetBuff());
			}
			if(GetParamGlobal()->AllocateTargetTRBuff==true){
				TargetTRBuff->SetDependency(P0L->GetTargetTRBuff());
			}
		}
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			RawTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		}
		if(GetParamGlobal()->AllocViewTargetBuffer==true){
			ViewTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		}
		if(GetParamGlobal()->AllocCamTargetBuffer==true){
			CamTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		}
		if(GetParamGlobal()->AllocBitBuffer==true){
			BitBuff->Set(GetPage(),ImageBufferBitBuffer ,(GetParamGlobal()->DotPerLine+7)/8 ,GetParamGlobal()->MaxLines);
		}
		else{
			if(GetParamGlobal()->AllocateTargetBuff==true){
				ViewTargetBuff->MakeDup(*TargetBuff);
			}
		}
	}
}

QString	DataInLayer::GetFileNameToSwapBuffer(void)
{
	return QString("SwapBuff-")+QString::number(GetPhase())
		  +QString("-")+QString::number(GetPage())
		  +QString("-")+QString::number(GetLayer())
		  +QString(".swp");
}

void	DataInLayer::SwapImageOutOfBuffer(int ImageDataType)
{
	QString	FileName=GetFileNameToSwapBuffer();

	QFile	File(FileName);

	if(File.open(QIODevice::WriteOnly)==true){
		if((ImageDataType & ImageBufferMaster)!=0){
			MasterBuff		->Save(&File);
			delete	MasterBuff;
			MasterBuff		=NULL;
		}
		if((ImageDataType & ImageBufferTarget)!=0){
			TargetBuff		->Save(&File);
			delete	TargetBuff;
			TargetBuff		=NULL;
		}
		if((ImageDataType & ImageBufferRawTarget)!=0){
			RawTargetBuff	->Save(&File);
			delete	RawTargetBuff;
			RawTargetBuff	=NULL;
		}
		//ViewTargetBuff	->Save(&File);
		//delete	ViewTargetBuff;
		//ViewTargetBuff	=NULL;
	}
}
void	DataInLayer::SwapImageInToBuffer(int ImageDataType)
{
	QString	FileName=GetFileNameToSwapBuffer();

	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		Initial(true);
		if((ImageDataType & ImageBufferMaster)!=0)
			MasterBuff		->Load(&File);
		if((ImageDataType & ImageBufferTarget)!=0)
			TargetBuff		->Load(&File);
		if((ImageDataType & ImageBufferRawTarget)!=0)
			RawTargetBuff	->Load(&File);
		//ViewTargetBuff->Load(&File);
	}
}

void	DataInLayer::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		ImageBuffer	*Tmp=NULL;
		if(GetParamGlobal()->AllocateMasterBuff==true){
			if(MasterBuff==NULL){
				MasterBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,MasterBuff->GetWidth(),MasterBuff->GetHeight());
			}
			if(Tmp!=NULL && MasterBuff->IsNull()==false){
				*Tmp=*MasterBuff;
			}
			MasterBuff->Set(GetPage(),ImageBufferMaster ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			if(Tmp!=NULL){
				MasterBuff->PartialCopy(*Tmp ,0,0);
			}
		}
		if(GetParamGlobal()->AllocateTargetBuff==true){
			if(TargetBuff==NULL){
				TargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,TargetBuff->GetWidth(),TargetBuff->GetHeight());
			}
			if(Tmp!=NULL && TargetBuff->IsNull()==false){
				*Tmp=*TargetBuff;
			}
			if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
				TargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			}
			else{
				DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
				TargetBuff->SetDependency(P0L->GetTargetBuff());
			}
			if(Tmp!=NULL){
				TargetBuff->PartialCopy(*Tmp ,0,0);
			}
		}
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			if(TargetTRBuff==NULL){
				TargetTRBuff=new ImageBuffer();
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,TargetTRBuff->GetWidth(),TargetTRBuff->GetHeight());
			}
			if(Tmp!=NULL && TargetTRBuff->IsNull()==false){
				*Tmp=*TargetTRBuff;
			}
			TargetTRBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->MaxLines,GetParamGlobal()->DotPerLine);
			if(Tmp!=NULL){
				TargetTRBuff->PartialCopy(*Tmp ,0,0);
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
		}
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			if(RawTargetBuff==NULL){
				RawTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,RawTargetBuff->GetWidth(),RawTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && RawTargetBuff->IsNull()==false){
				*Tmp=*RawTargetBuff;
			}
			RawTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			if(Tmp!=NULL){
				RawTargetBuff->PartialCopy(*Tmp ,0,0);
			}
		}
		if(GetParamGlobal()->AllocViewTargetBuffer==true){
			if(ViewTargetBuff==NULL){
				ViewTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,ViewTargetBuff->GetWidth(),ViewTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && ViewTargetBuff->IsNull()==false){
				*Tmp=*ViewTargetBuff;
			}
			ViewTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			if(Tmp!=NULL){
				ViewTargetBuff->PartialCopy(*Tmp ,0,0);
			}
		}
		else{
			if(ViewTargetBuff==NULL){
				ViewTargetBuff=new ImageBuffer();
			}
			if(GetParamGlobal()->AllocateTargetBuff==true){
				ViewTargetBuff->MakeDup(*TargetBuff);
			}
		}
		if(GetParamGlobal()->AllocCamTargetBuffer==true){
			if(CamTargetBuff==NULL){
				CamTargetBuff=new ImageBuffer();
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,CamTargetBuff->GetWidth(),CamTargetBuff->GetHeight());
			}
			if(Tmp!=NULL && CamTargetBuff->IsNull()==false){
				*Tmp=*CamTargetBuff;
			}
			CamTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			if(Tmp!=NULL){
				CamTargetBuff->PartialCopy(*Tmp ,0,0);
			}
		}
		if(GetParamGlobal()->AllocBitBuffer==true){
			if(BitBuff==NULL){
				BitBuff=new ImageBuffer();
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
			if(Tmp==NULL){
				Tmp=new ImageBuffer();
				Tmp->Set(0,ImageBufferMaster ,BitBuff->GetWidth(),BitBuff->GetHeight());
			}
			if(Tmp!=NULL && BitBuff->IsNull()==false){
				*Tmp=*BitBuff;
			}
			BitBuff->Set(GetPage(),ImageBufferBitBuffer ,(GetParamGlobal()->DotPerLine+7)/8 ,GetParamGlobal()->MaxLines);
			if(Tmp!=NULL){
				BitBuff->PartialCopy(*Tmp ,0,0);
			}
			if(Tmp!=NULL){
				delete	Tmp;
				Tmp=NULL;
			}
		}
		if(Tmp!=NULL){
			delete	Tmp;
		}
	}
}
	
void	DataInLayer::ReallocMemoryMaster(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(MasterBuff!=NULL){
			delete	MasterBuff;
		}
		MasterBuff		=new ImageBuffer();
		if(GetParamGlobal()->AllocateMasterBuff==true){
			MasterBuff->Set(GetPage(),ImageBufferMaster ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		}
	}
}

void	DataInLayer::ReallocMemoryTarget(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(TargetBuff!=NULL){
			delete	TargetBuff;
		}
		TargetBuff		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetBuff==true){
			if(GetParamGlobal()->CommonTargetBetweenPhases==false || GetPhase()==0){
				TargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
			}
			else{
				DataInLayer	*P0L=GetLayersBase()->GetPageDataPhase(0)->GetPageData(GetPage())->GetLayerData(GetLayer());
				TargetBuff->SetDependency(P0L->GetTargetBuff());
			}
		}
		if(TargetTRBuff!=NULL){
			delete	TargetTRBuff;
		}
		TargetTRBuff		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			TargetTRBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->MaxLines ,GetParamGlobal()->DotPerLine);
		}
	}
}
void	DataInLayer::ReallocUseBufferToTarget(BYTE **Buff)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(TargetBuff!=NULL){
			delete	TargetBuff;
		}
		TargetBuff		=new ImageBuffer();
		if(GetParamGlobal()->AllocateTargetBuff==true){
			TargetBuff->Set(Buff,ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines,true);
		}
	}
}


void	DataInLayer::AllocateTargetTRBuff(void)
{
	if(TargetTRBuff->IsNull()==true){
		TargetTRBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->MaxLines,GetParamGlobal()->DotPerLine);
	}
}

void	DataInLayer::ReleaseTargetTRBuff(void)
{
	if(GetParamGlobal()->AllocateTargetTRBuff==false){
		delete	TargetTRBuff;
		TargetTRBuff=new ImageBuffer();
	}
}


void	DataInLayer::Mirror(bool XMode ,bool YMode)
{
	if(GetMasterBuffPointer()!=NULL)		GetMasterBuffPointer()		->Mirror(XMode,YMode);
	if(GetTargetBuffPointer()!=NULL)		GetTargetBuffPointer()		->Mirror(XMode,YMode);
	if(GetTargetTRBuffPointer()!=NULL)		GetTargetTRBuffPointer()	->Mirror(YMode,XMode);
	if(GetRawTargetBuffPointer()!=NULL)		GetRawTargetBuffPointer()	->Mirror(XMode,YMode);
	if(GetDelayedViewBuffPointer()!=NULL)	GetDelayedViewBuffPointer()	->Mirror(XMode,YMode);
	if(GetCamTargetBuffPointer()!=NULL)		GetCamTargetBuffPointer()	->Mirror(XMode,YMode);
	if(GetBitBuffPointer()!=NULL)			GetBitBuffPointer()			->Mirror(XMode,YMode);
}
void	DataInLayer::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	x1=ParentPage->GetOutlineOffset()->x;
	y1=ParentPage->GetOutlineOffset()->y;
	x2=ParentPage->GetOutlineOffset()->x+GetParamGlobal()->DotPerLine;
	y2=ParentPage->GetOutlineOffset()->y+GetParamGlobal()->MaxLines;
}

ImageBuffer	&DataInLayer::GetMasterBuff(void)
{	
	if(Exchanged==false){
		return *MasterBuff;
	}	
	return *TargetBuff;
}
	
ImageBuffer	&DataInLayer::GetTargetBuff(void)
{	
	if(Exchanged==false){
		return *TargetBuff;
	}
	return *MasterBuff;
}
	
ImageBuffer	&DataInLayer::GetTargetTRBuff(void)
{	
	return *TargetTRBuff;
}
ImageBuffer	&DataInLayer::GetRawTargetBuff(void)
{	
	return *RawTargetBuff;
}
ImageBuffer     &DataInLayer::GetDelayedViewBuff(void)
{
	return *ViewTargetBuff;
}
ImageBuffer     &DataInLayer::GetCamTargetBuff(void)
{
	return *CamTargetBuff;
}
ImageBuffer     &DataInLayer::GetBitBuff(void)
{
	return *BitBuff;
}


ImageBuffer	*DataInLayer::GetMasterBuffPointer(void)
{	
	if(Exchanged==false){
		return MasterBuff;
	}
	return TargetBuff;
}
	
ImageBuffer	*DataInLayer::GetTargetBuffPointer(void)
{	
	if(Exchanged==false){
		return TargetBuff;
	}
	return MasterBuff;
}
ImageBuffer	*DataInLayer::GetTargetTRBuffPointer(void)
{	
	return TargetTRBuff;
}
ImageBuffer	*DataInLayer::GetRawTargetBuffPointer(void)
{	
	return RawTargetBuff;
}
ImageBuffer	*DataInLayer::GetDelayedViewBuffPointer(void)
{
	return ViewTargetBuff;
}
ImageBuffer	*DataInLayer::GetCamTargetBuffPointer(void)
{
	return CamTargetBuff;
}
ImageBuffer	*DataInLayer::GetBitBuffPointer(void)
{
	return BitBuff;
}

bool	DataInLayer::IsMasterBuffEnabled(void)
{
	if(MasterBuff!=NULL && MasterBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsTargetBuffEnabled(void)
{
	if(TargetBuff!=NULL && TargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsTargetTRBuffEnabled(void)
{
	if(TargetTRBuff!=NULL && TargetTRBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsRawTargetBuffEnabled(void)
{
	if(RawTargetBuff!=NULL && RawTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsDelayedViewBuffEnabled(void)
{
	if(ViewTargetBuff!=NULL && ViewTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsCamTargetBuffEnabled(void)
{
	if(CamTargetBuff!=NULL && CamTargetBuff->IsNull()==false)
		return true;
	return false;
}

bool	DataInLayer::IsBitBuffEnabled(void)
{
	if(BitBuff!=NULL && BitBuff->IsNull()==false)
		return true;
	return false;
}
bool	DataInLayer::HasDataInBitBuff(void)
{
	if(IsBitBuffEnabled()==false)
		return false;
	int	XByte=BitBuff->GetWidth();
	for(int y=0;y<GetMaxLines();y++){
		BYTE	*d=BitBuff->GetY(y);
		for(int x=0;x<XByte;x++){
			if(d[x]!=0){
				return true;
			}
		}
	}
	return false;
}

void	DataInLayer::SetToMasterBuff(ImageBuffer &Img)
{
	if(Exchanged==false){
		*TargetBuff=Img;
	}
	*MasterBuff=Img;
}

void	DataInLayer::SetToTargetBuff(ImageBuffer &Img)
{
	if(Exchanged==false){
		*MasterBuff=Img;
	}
	*TargetBuff=Img;
}

void	DataInLayer::CopyToDelayedView(void)
{
	if(GetParamGlobal()->AllocViewTargetBuffer==true){
		*ViewTargetBuff = *TargetBuff;
	}
}

bool	DataInLayer::IsEdited(void)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			return MasterBuff->IsChanged();
		}
		if(GetParamGlobal()->AllocateTargetBuff==true){
			return TargetBuff->IsChanged();
		}
	}
	return false;
}
bool	DataInLayer::IsCalcDone(void)
{
	return true;
}
void	DataInLayer::SetEdited(bool edited)
{
	if(GetParamComm()->ImageBufferNecessary()==true){
		if(GetParamGlobal()->AllocateMasterBuff==true){
			//MasterBuff->SetChanged(edited);
		}
		if(GetParamGlobal()->AllocateTargetBuff==true){
			//TargetBuff->SetChanged(edited);
		}
	}
}
void	DataInLayer::SetCalcDone(bool calcdone)
{
}

void	DataInLayer::CreateAndCopyTempTargetBuff(void)
{
	if(TempTargetBuff!=NULL){
		delete	TempTargetBuff;
	}

	if((TargetBuff!=NULL) && (TargetBuff->IsNull()==false)){
		TempTargetBuff=new ImageBuffer();
		TempTargetBuff->Set(GetPage(),ImageBufferTarget ,GetParamGlobal()->DotPerLine ,GetParamGlobal()->MaxLines);
		*TempTargetBuff= *TargetBuff;
	}
}

void	DataInLayer::CopyTempToTargetBuff(void)
{
	if((TargetBuff!=NULL) && (TargetBuff->IsNull()==false)){
		*TargetBuff= *TempTargetBuff;
	}
}


void	DataInLayer::ReleaseTempTargetBuff(void)
{
	if(TempTargetBuff!=NULL){
		*TargetBuff= *TempTargetBuff;
		delete	TempTargetBuff;
		TempTargetBuff=NULL;
	}
}
void	DataInLayer::CopyTargetImageToRaw(void)
{
	if((TargetBuff!=NULL) && (RawTargetBuff!=NULL) && (TargetBuff->IsNull()==false) && (RawTargetBuff->IsNull()==false)){
		*RawTargetBuff= *TargetBuff;
	}
}
void	DataInLayer::CopyTargetToTransposition(void)
{
	if((TargetBuff!=NULL) && (TargetTRBuff!=NULL) && (TargetBuff->IsNull()==false) && (TargetTRBuff->IsNull()==false)){
		if(TargetTRBuff->GetFlagCaptured()==false){
			TargetTRBuff->TranspositionXY(*TargetBuff);
		}
	}
}
void	DataInLayer::CopyBitBuffToTransposition(void)
{
	if((BitBuff!=NULL) && (TargetTRBuff!=NULL) && (BitBuff->IsNull()==false) && (TargetTRBuff->IsNull()==false)){
		TargetTRBuff->TranspositionXY(*BitBuff);
	}
}
void	DataInLayer::RestoreTargetImageFromRaw(void)
{
	if((TargetBuff!=NULL) && (RawTargetBuff!=NULL) && (TargetBuff->IsNull()==false) && (RawTargetBuff->IsNull()==false)){
		*TargetBuff =*RawTargetBuff;
	}
}
bool	DataInLayer::CopyFrom(QImage &SrcImg ,bool ToMaster)
{
	ImageBuffer *DestBuff;
	if(ToMaster==true){
		DestBuff= &GetMasterBuff();
	}
	else{
		DestBuff= &GetTargetBuff();
	}

	QImage	Img=SrcImg.convertToFormat(QImage::Format_ARGB32);
	int	YLen=min(Img.height(),GetMaxLines());
	int	XLen=min(Img.width() ,GetDotPerLine());

	for(int y=0;y<YLen;y++){
		BYTE	*s=Img.scanLine(y);
		BYTE	*d2=DestBuff->GetY(y);
		for(int x=0;x<XLen;x++){
			*d2= *s;
			s+=4;
			d2++;
		}
	}
	return true;
}

void	DataInLayer::UndoPasteRect(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false){
		return;
	}
	DisplayImage::DisplayType	DType=(DisplayImage::DisplayType)d;
	ImageBuffer	*DBuff=NULL;
	if(DType==DisplayImage::__Target){
		DBuff=&GetTargetBuff();
	}
	else if(DType==DisplayImage::__Master){
		DBuff=&GetMasterBuff();
	}
	else if(DType==DisplayImage::__DelayedView){
		DBuff=&GetDelayedViewBuff();
	}
	else if(DType==DisplayImage::__RawTarget){
		DBuff=&GetRawTargetBuff();
	}
	else if(DType==DisplayImage::__CamTarget){
		DBuff=&GetCamTargetBuff();
	}
	FlexAreaImage	UndoAreaImage;
	if(UndoAreaImage.Load(f)==false){
		return;
	}
	UndoAreaImage.CopyToBuffer(*DBuff);
}
void	DataInLayer::UndoMoveImage(QIODevice *f)
{
	int		XDir,YDir;
	bool	FlagMaster;
	bool	FlagTarget;

	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(::Load(f,XDir)==false){
		return;
	}
	if(::Load(f,YDir)==false){
		return;
	}
	if(FlagMaster==true){
		FlexAreaImage	UndoAreaImageV;
		FlexAreaImage	UndoAreaImageH;
		UndoAreaImageV.Load(f);
		UndoAreaImageH.Load(f);
		GetMasterBuff().MoveImage(-XDir,-YDir);
		UndoAreaImageV.CopyToBuffer(GetMasterBuff());
		UndoAreaImageH.CopyToBuffer(GetMasterBuff());
	}
	if(FlagTarget==true){
		FlexAreaImage	UndoAreaImageV;
		FlexAreaImage	UndoAreaImageH;
		UndoAreaImageV.Load(f);
		UndoAreaImageH.Load(f);
		GetTargetBuff().MoveImage(-XDir,-YDir);
		UndoAreaImageV.CopyToBuffer(GetTargetBuff());
		UndoAreaImageH.CopyToBuffer(GetTargetBuff());
	}
}

void	DataInLayer::UndoRotateImage(QIODevice *f)
{
	double	Angle;
	bool	FlagMaster;
	bool	FlagTarget;

	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(::Load(f,Angle)==false){
		return;
	}
	if(FlagMaster==true){
		GetMasterBuff().Load(f);
	}
	if(FlagTarget==true){
		GetTargetBuff().Load(f);
	}
}
//---------------------------------------------------------------------------

DataInPage::ConstructionData::ConstructionData(DataInPage *parent)
{
	OutlineOffset.x=parent->GetParamGlobal()->DotPerLine * parent->Page;
	OutlineOffset.y=0;
}

DataInPage::ConstructionData::~ConstructionData(void)
{
}

bool    DataInPage::ConstructionData::Save(QIODevice *f)
{
	if(::Save(f,OutlineOffset)==false){
		return false;
	}
	return true;
}
bool    DataInPage::ConstructionData::Load(QIODevice *f)
{
	if(::Load(f,OutlineOffset)==false){
		return false;
	}
	return true;
}

DataInPage::DataInPage(int page,PageDataInOnePhase	*parentPhase) 
: Parent(parentPhase->GetLayersBase()),ParentPhase(parentPhase)
,EntryPoint(parentPhase->GetLayersBase()->GetEntryPoint()),Page(page),CData(this),CDataBack(this)
,ThreadImageCompresser(parentPhase->GetLayersBase(),this)
,LearningInPage(page,parentPhase->GetLayersBase())
{
	IsWaitingReq		=false;
	LayerData		=NULL;
	UncoveredMap	=NULL;
	UncoveredXByte	=0;
	UncoveredYLen	=0;
	OKCounter		=0;
	NGCounter		=0;

	DynamicMaskMap		=NULL;
	DynamicMaskMapXByte	=0;
	DynamicMaskMapYLen	=0;
}

DataInPage::~DataInPage(void)
{
    Release();
}

void    DataInPage::Initial(bool EnabledImageMemoryAllocation)
{
	if(LayerData!=NULL){
		delete	[]LayerData;
	}

	AllocatedLayerNumb	=GetLayerNumb();
	LayerData			=new DataInLayer*[GetLayerNumb()];
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]=new DataInLayer(EntryPoint,this);
		LayerData[Ly]->Layer				=Ly;
		//LayerData[Ly]->ParentPage		=this;
		LayerData[Ly]->Initial(EnabledImageMemoryAllocation);
	}
	if(GetParamGlobal()->ModeCompressNGImage==true && GetParamGlobal()->OutputResult==true && GetParamGlobal()->OMPResultCompress==true){
		ThreadImageCompresser.start();
	}
}
void    DataInPage::ReleaseInside(void)
{
	LoadedInfoList	*r;
	while((r=ResultLoaded.GetFirst())!=NULL){
		ResultLoaded.RemoveList(r);
		delete	r;
	}
	AllocatedLayerNumb=0;
	ThreadImageCompresser.CloseMode=true;
	ThreadImageCompresser.wait(10000);
}
void    DataInPage::Release(void)
{
	if(LayerData!=NULL){
		for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
			delete	LayerData[Ly];
		}
		delete	[]LayerData;
		LayerData=NULL;
	}

	if(UncoveredMap!=NULL){
		DeleteMatrixBuff(UncoveredMap,UncoveredYLen);
		UncoveredMap=NULL;
	}
	UncoveredXByte	=0;
	UncoveredYLen	=0;

	//_heapchk();
	ResultLoaded.RemoveAll();
	if(DynamicMaskMap!=NULL){
		DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
		DynamicMaskMap		=NULL;
		DynamicMaskMapXByte	=0;
		DynamicMaskMapYLen	=0;
	}
}

void	DataInPage::SetResultLoaded(LoadedInfoContainerInPhase &res)
{	
	ResultLoaded=res;
}

LoadedInfoContainerInPhase	&DataInPage::GetResultLoaded(void)
{	
	return ResultLoaded;
}

void	DataInPage::ClearResultLoaded(void)
{	
	ResultLoaded.RemoveAll();
}

bool	DataInPage::AllocateDynamicMasking(void)
{
	int	iXByte=(GetDotPerLine()+7)/8;
	if((iXByte!=GetDynamicMaskMapXByte()) || (GetDynamicMaskMapYLen()!=GetMaxLines()) || DynamicMaskMap==NULL){
		if(DynamicMaskMap!=NULL){
			DeleteMatrixBuff(DynamicMaskMap,DynamicMaskMapYLen);
		}
		DynamicMaskMapXByte	=iXByte;
		DynamicMaskMapYLen	=GetMaxLines();
		DynamicMaskMap	=MakeMatrixBuff(DynamicMaskMapXByte ,DynamicMaskMapYLen);
	}
	return true;
}
bool	DataInPage::Reallocate(int newLayerNumb)
{
	if(AllocatedLayerNumb<newLayerNumb){
		DataInLayer	**tLayerData	=new DataInLayer*[newLayerNumb];
		int	Ly;
		for(Ly=0;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]==NULL){
				break;
			}
			tLayerData[Ly]=LayerData[Ly];
		}
		LayerData=tLayerData;
		for(;Ly<newLayerNumb;Ly++){
			LayerData[Ly]=new DataInLayer(EntryPoint,this);
			LayerData[Ly]->Layer				=Ly;
			//LayerData[Ly]->ParentPage		=this;
			LayerData[Ly]->Initial(true);
		}
	}
	else if(AllocatedLayerNumb>newLayerNumb){
		for(int Ly=newLayerNumb;Ly<AllocatedLayerNumb;Ly++){
			if(LayerData[Ly]!=NULL){
				delete	LayerData[Ly];
				LayerData[Ly]=NULL;
			}
		}
	}
	AllocatedLayerNumb=newLayerNumb;
	return true;
}
void	DataInPage::ClearDynamicMaskMap(void)
{
	if(DynamicMaskMap==NULL){
		AllocateDynamicMasking();
	}
	if(DynamicMaskMap!=NULL){
		MatrixBuffClear	(DynamicMaskMap ,0 ,DynamicMaskMapXByte ,DynamicMaskMapYLen);
	}
}

void	DataInPage::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
		}
	}
}
	
void	DataInPage::ReallocMemoryMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocMemoryMaster();
		}
	}
}

void	DataInPage::ReallocMemoryTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReallocMemoryTarget();
		}
	}
}

void	DataInPage::AllocateTargetTRBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->AllocateTargetTRBuff();
		}
	}
}

void	DataInPage::ReleaseTargetTRBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]!=NULL){
			LayerData[Ly]->ReleaseTargetTRBuff();
		}
	}
}
void	DataInPage::LockTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessTarget.lock();
	}
}
void	DataInPage::UnlockTarget(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessTarget.unlock();
	}
}
void	DataInPage::LockMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessMaster.lock();
	}
}
void	DataInPage::UnlockMaster(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->AccessMaster.unlock();
	}
}

void	DataInPage::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwapImageOutOfBuffer(ImageDataType);
	}
}

void	DataInPage::SwapImageInToBuffer(int ImageDataType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwapImageInToBuffer(ImageDataType);
	}
}

XYData	*DataInPage::GetOutlineOffset(void)
{	
	if(GetLayersBase()->GetDefaultArrangeMode()==false){
		return &CData.OutlineOffset;
	}
	else{
		switch(GetLayersBase()->GetParamGlobal()->DefaultImageArrange){
			case 1:
				CDataBack.OutlineOffset.x=GetLayersBase()->GetParamGlobal()->DotPerLine*GetPage();
				CDataBack.OutlineOffset.y=0;
				break;
			case 2:
				CDataBack.OutlineOffset.x=0;
				CDataBack.OutlineOffset.y=GetLayersBase()->GetParamGlobal()->MaxLines*GetPage();
				break;
			default:
				CDataBack.OutlineOffset.x=0;
				CDataBack.OutlineOffset.y=0;
		}
		return &CDataBack.OutlineOffset;
	}
}
void	DataInPage::SetGlobalOutlineOffset(int X ,int Y)
{
	CData.OutlineOffset.x=X;
	CData.OutlineOffset.y=Y;
}

XYData	*DataInPage::GetGlobalOutlineOffset(void)
{
	int	GPage=Parent->GetGlobalPageFromLocal(GetPage());
	XYData	*XY=Parent->GetGlobalOutlineOffset(GPage);
	return XY;
}

void	DataInPage::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	x1=CData.OutlineOffset.x;
	y1=CData.OutlineOffset.y;
	x2=CData.OutlineOffset.x+GetParamGlobal()->DotPerLine;
	y2=CData.OutlineOffset.y+GetParamGlobal()->MaxLines;
}

bool    DataInPage::SaveAttr(QIODevice *f)
{
	ConstructionData	CDataDummy(this);
	if(CDataDummy.Save(f)==false){
		return false;
	}
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->SaveAttr(f)==false){
			return false;
		}
	}
	return true;
}
bool    DataInPage::LoadAttr(QIODevice *f)
{
	ConstructionData	CDataDummy(this);
	if(CDataDummy.Load(f)==false){
		return false;
	}
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;Ly<(AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->LoadAttr(f)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(EntryPoint,this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.LoadAttr(f)==false){
				return false;
			}
		}
	}
	return true;
}
bool    DataInPage::Save(QIODevice *f)
{
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    DataInPage::Load(QIODevice *f)
{
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;(Ly<AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->Load(f)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(EntryPoint,this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.Load(f)==false){
				return false;
			}
		}
	}

	return true;
}
bool	DataInPage::SaveImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	int32	LayerNumb=AllocatedLayerNumb;
	if(::Save(f,LayerNumb)==false){
		return false;
	}
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		if(LayerData[Ly]->SaveImage(f ,X1 ,Y1 ,X2, Y2)==false){
			return false;
		}
	}
	return true;
}
bool	DataInPage::LoadImage(QIODevice *f ,int X1 ,int Y1 ,int X2, int Y2)
{
	int32	iLayerNumb;
	if(::Load(f,iLayerNumb)==false){
		return false;
	}
	int	Ly;
	for(Ly=0;(Ly<AllocatedLayerNumb) && (Ly<iLayerNumb);Ly++){
		if(LayerData[Ly]->LoadImage(f ,X1 ,Y1 ,X2, Y2)==false){
			return false;
		}
	}
	if(Ly<iLayerNumb){
		DataInLayer	Dummy(EntryPoint,this);
		for(;Ly<iLayerNumb;Ly++){
			if(Dummy.LoadImage(f ,X1 ,Y1 ,X2, Y2)==false){
				return false;
			}
		}
	}
	return true;
}

bool	DataInPage::ClipAreaGlobal(FlexArea &Area)
{
	int x1 ,y1 ,x2 ,y2;
	GetArea(x1 ,y1 ,x2 ,y2);
	Area.ClipArea(x1 ,y1 ,x2 ,y2);
	if(Area.IsNull()==true){
		return false;
	}
	return true;
}
bool	DataInPage::ClipAreaLocal(FlexArea &Area)
{
	Area.ClipArea(0 ,0 , GetWidth()-1, GetHeight()-1);
	if(Area.IsNull()==true){
		return false;
	}
	return true;
}

bool	DataInPage::ClipMoveAreaFromGlobal(FlexArea &GlobalArea)
{
	GlobalArea.MoveToNoClip(-GetOutlineOffset()->x ,-GetOutlineOffset()->y);
	return ClipAreaLocal(GlobalArea);
}


bool	DataInPage::ClipMoveVectorFromGlobal(VectorLineBase *GlobalVector)
{
	GlobalVector->MoveTo(-GetOutlineOffset()->x ,-GetOutlineOffset()->y);
	return ClipVectorLocal(GlobalVector);
}

bool	DataInPage::ClipVectorLocal(VectorLineBase *LocalVector)
{
	LocalVector->ClipArea(0 ,0 , GetWidth(), GetHeight());
	if(LocalVector->IsNull()==true){
		return false;
	}
	return true;
}


void	DataInPage::GetLocalMatrixFromGlobalInMaster(int globalX ,int globalY ,int &localX ,int &localY)
{
	localX=globalX-GetOutlineOffset()->x;
	localY=globalY-GetOutlineOffset()->y;
}
void	DataInPage::GetGlobalMatrixFromLocalInMaster(int localX ,int localY ,int &globalX ,int &globalY)
{
	globalX=localX+GetOutlineOffset()->x;
	globalY=localY+GetOutlineOffset()->y;
}
bool	DataInPage::IsInclude(int localX ,int localY)
{
	if((localX<0) || (GetParamGlobal()->DotPerLine<=localX)
		|| (localY<0) || (GetParamGlobal()->MaxLines<=localY)){
		return false;
	}
	return true;
}


bool	DataInPage::IsOverlapped(FlexArea &globalArea)
{
	return globalArea.CheckOverlapRectangle( CData.OutlineOffset.x,CData.OutlineOffset.y
											,CData.OutlineOffset.x+GetParamGlobal()->DotPerLine ,CData.OutlineOffset.y+GetParamGlobal()->MaxLines );
}

bool	DataInPage::IsOverlapped(VectorLineBase *Vector)
{
	return Vector->CheckOverlapRectangle( CData.OutlineOffset.x,CData.OutlineOffset.y
											,CData.OutlineOffset.x+GetParamGlobal()->DotPerLine ,CData.OutlineOffset.y+GetParamGlobal()->MaxLines );
}
void	DataInPage::IncrementNGCounterWithMutex(int result)
{
	MutexNGCounter.lockForWrite();
	if(result>1){
		NGCounter++;
	}
	else if(result==1){
		OKCounter++;
	}
	MutexNGCounter.unlock();
}
void	DataInPage::AddNGCounter(int NGCount)
{
	MutexNGCounter.lockForWrite();
	NGCounter+=NGCount;
	MutexNGCounter.unlock();
}

int		DataInPage::GetNGCounter(void)
{
	MutexNGCounter.lockForRead();
	int	ret=NGCounter;
	MutexNGCounter.unlock();
	return ret;
}
int		DataInPage::GetOKCounter(void)
{
	MutexNGCounter.lockForRead();
	int	ret=OKCounter;
	MutexNGCounter.unlock();
	return ret;
}
void	DataInPage::ClearNGCounterWithMutex(void)
{
	MutexNGCounter.lockForWrite();
	NGCounter=0;
	OKCounter=0;
	MutexNGCounter.unlock();
}

void	DataInPage::SwitchImageBuff(void)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->SwitchImageBuff();
	}
}
void	DataInPage::CopyImage(int sourceImageType ,int destImageType)
{
	for(int Ly=0;Ly<AllocatedLayerNumb;Ly++){
		LayerData[Ly]->CopyImage(sourceImageType ,destImageType);
	}
}
void	DataInPage::GetMasterImages(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetMasterBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetTargetImages(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetTargetBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetTargetTRImages(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetTargetTRBuff());
		Images.AppendList(r);
	}
}void	DataInPage::GetBitImages(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetBitBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetDelayedViewImages(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetDelayedViewBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetRawTargetImages	(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetRawTargetBuff());
		Images.AppendList(r);
	}
}
void	DataInPage::GetCamTargetImages	(ImagePointerContainer &Images)
{
	Images.RemoveAll();
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		ImagePointerList	*r=new ImagePointerList(&p->GetCamTargetBuff());
		Images.AppendList(r);
	}
}

bool	DataInPage::IsEdited(void)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		if(p->IsEdited()==true){
			return true;
		}
	}
	return false;
}
bool	DataInPage::IsCalcDone(void)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		if(p->IsCalcDone()==false){
			return false;
		}
	}
	return false;
}
void	DataInPage::SetEdited(bool edited)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		p->SetEdited(edited);
	}
}
void	DataInPage::SetCalcDone(bool calcdone)
{
	for(int i=0;i<GetLayerNumb();i++){
		DataInLayer	*p=GetLayerData(i);
		p->SetCalcDone(calcdone);
	}
}

void	DataInPage::CopyTargetImageToRaw(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetImageToRaw();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetImageToRaw();
		}
	}
}
void	DataInPage::CopyTargetToTransposition(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyTargetToTransposition();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyTargetToTransposition();
		}
	}
}

void	DataInPage::CopyBitBuffToTransposition(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->CopyBitBuffToTransposition();
		}
	}
	else{
		IntList	LayerList;
		GetParamGlobal()->GetStrategyLayer(GetLayersBase()->GetCurrentStrategicNumberForCalc()
						,GetPage(),LayerList);

		for(IntClass *s=LayerList.GetFirst();s!=NULL;s=s->GetNext()){
			int	Layer=s->GetValue();
			GetLayerData(Layer)->CopyBitBuffToTransposition();
		}
	}
}

void	DataInPage::SetCompressedContainer(NGImageContainerInPage *point)
{
	ThreadImageCompresser.Set(point);
	point->SetCompressedFlag(false);
}

void	DataInPage::MakeUncoveredMap(void)
{
	if(UncoveredMap==NULL){
		UncoveredXByte	=(GetDotPerLine()+7)/8;
		UncoveredYLen	=GetMaxLines();
		UncoveredMap=MakeMatrixBuff(UncoveredXByte,UncoveredYLen);
	}
	MatrixBuffClear(UncoveredMap ,0 ,UncoveredXByte ,UncoveredYLen);
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->MakeUncoveredMap(GetPage() ,UncoveredMap, UncoveredXByte ,UncoveredYLen);
	}
	MatrixBuffNot(UncoveredMap, UncoveredXByte ,UncoveredYLen);
	BYTE	**TmpMap=MakeMatrixBuff(UncoveredXByte,UncoveredYLen);
	for(int i=0;i<GetParamGlobal()->ShrinkDotUncoveredArea;i++){
		ThinArea(UncoveredMap
				,TmpMap
				,UncoveredXByte ,UncoveredYLen);
	}
	DeleteMatrixBuff(TmpMap,UncoveredYLen);
}

const BYTE	**DataInPage::GetUncoveredMap(int &XByte ,int &YLen)
{
	XByte	=UncoveredXByte;
	YLen	=UncoveredYLen;
	return (const BYTE **)UncoveredMap;
}

void	DataInPage::LockTxComm(void)	
{	
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()!=0){
//		CommTxLock.lock();
	}
}
void	DataInPage::UnlockTxComm(void)
{	
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()!=0){
//		CommTxLock.unlock();	
	}
}
void	DataInPage::LockRxComm(void)	
{	
//	CommRxLock.lock();
}
void	DataInPage::UnlockRxComm(void)
{	
//	CommRxLock.unlock();	
}

bool	DataInPage::IsIncludeFromGlobal(int GlobalX ,int GlobalY)
{
	int	localX ,localY;
	GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,localX ,localY);
	return IsInclude(localX ,localY);
}

bool	DataInPage::CopyFrom(QImage &SrcImg ,bool ToMaster)
{
	ImageBuffer **DestBuff=new ImageBuffer*[GetLayerNumb()];
	for(int layer=0;layer<GetLayerNumb();layer++){
		if(ToMaster==true){
			DestBuff[layer]= &GetLayerData(layer)->GetMasterBuff();
		}
		else{
			DestBuff[layer]= &GetLayerData(layer)->GetTargetBuff();
		}
	}
	bool	ret=CopyFrom(DestBuff,SrcImg);
	delete	[]DestBuff;
	return ret;
}
void	DataInPage::CopyToDelayedView(void)
{
	for(int layer=0;layer<GetLayerNumb();layer++){
		GetLayerData(layer)->CopyToDelayedView();
	}
}

bool	DataInPage::CopyFrom(ImageBuffer *DestBuff[],QImage &SrcImg)
{
	QImage	Img=SrcImg.convertToFormat(QImage::Format_ARGB32);
	int	YLen=min(Img.height(),GetMaxLines());
	int	XLen=min(Img.width() ,GetDotPerLine());
	if(GetLayerNumb()>=3){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			BYTE	*d1;
			BYTE	*d2;
			d0=DestBuff[0]->GetY(y);
			d1=DestBuff[1]->GetY(y);
			d2=DestBuff[2]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d2= *s;
				*d1= *(s+1);
				*d0= *(s+2);
				s+=4;
				d0++;
				d1++;
				d2++;
			}
		}
	}
	if(GetLayerNumb()==2){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			BYTE	*d1;
			d0=DestBuff[0]->GetY(y);
			d1=DestBuff[1]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d0= *s;
				*d1= *(s+1);
				s+=4;
				d0++;
				d1++;
			}
		}
	}
	if(GetLayerNumb()==1){
		for(int y=0;y<YLen;y++){
			BYTE	*s=Img.scanLine(y);
			BYTE	*d0;
			d0=DestBuff[0]->GetY(y);
			for(int x=0;x<XLen;x++){
				*d0= *s;
				s+=4;
				d0++;
			}
		}
	}
	return true;
}
bool	DataInPage::CopyTo(QImage &DstImg ,bool ToMaster)
{
	ImageBuffer **SrcBuff=new ImageBuffer*[GetLayerNumb()];
	for(int layer=0;layer<GetLayerNumb();layer++){
		if(ToMaster==true){
			SrcBuff[layer]= &GetLayerData(layer)->GetMasterBuff();
		}
		else{
			SrcBuff[layer]= &GetLayerData(layer)->GetTargetBuff();
		}
	}

	QImage	Img(GetDotPerLine(),GetMaxLines(),QImage::Format_ARGB32);
	int	YLen=GetMaxLines();
	int	XLen=GetDotPerLine();
	if(GetLayerNumb()>=3){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Img.scanLine(y);
			BYTE	*s0=SrcBuff[0]->GetY(y);
			BYTE	*s1=SrcBuff[1]->GetY(y);
			BYTE	*s2=SrcBuff[2]->GetY(y);
			for(int x=0;x<XLen;x++){
				*(d+0)= *s2;
				*(d+1)= *s1;
				*(d+2)= *s0;
				*(d+3)=0xFF;
				d+=4;
				s0++;
				s1++;
				s2++;
			}
		}
	}
	if(GetLayerNumb()==2){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Img.scanLine(y);
			BYTE	*s0=SrcBuff[0]->GetY(y);
			BYTE	*s1=SrcBuff[1]->GetY(y);
			for(int x=0;x<XLen;x++){
				*(d+0)= *s1;
				*(d+1)= *s0;
				*(d+2)= *s0;
				*(d+3)=0xFF;
				d+=4;
				s0++;
				s1++;
			}
		}
	}
	if(GetLayerNumb()==1){
		for(int y=0;y<YLen;y++){
			BYTE	*d=Img.scanLine(y);
			BYTE	*s0=SrcBuff[0]->GetY(y);
			BYTE	*s1=SrcBuff[1]->GetY(y);
			for(int x=0;x<XLen;x++){
				*(d+0)= *s0;
				*(d+1)= *s0;
				*(d+2)= *s0;
				*(d+3)=0xFF;
				d+=4;
				s0++;
			}
		}
	}
	delete	[]SrcBuff;
	DstImg=Img;
	return true;
}
void	DataInPage::UndoCopyImageInPhases(QIODevice *f)
{
	bool	FlagMaster;
	bool	FlagTarget;
	int		LayerNumb;
	int		SrcPhase;
	int		DstPhase;

	if(::Load(f,SrcPhase)==false){
		return;
	}
	if(::Load(f,DstPhase)==false){
		return;
	}
	if(::Load(f,LayerNumb)==false){
		return;
	}
	if(::Load(f,FlagMaster)==false){
		return;
	}
	if(::Load(f,FlagTarget)==false){
		return;
	}
	if(0<=SrcPhase && SrcPhase<GetPhaseNumb() && 0<=DstPhase && DstPhase<GetPhaseNumb()){
		PageDataInOnePhase	*PhSrc=GetLayersBase()->GetPageDataPhase(SrcPhase);
		PageDataInOnePhase	*PhDst=GetLayersBase()->GetPageDataPhase(DstPhase);
		DataInPage *PageSrc=PhSrc->GetPageData(GetPage());
		DataInPage *PageDst=PhDst->GetPageData(GetPage());
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			DataInLayer	*LySrc=PageSrc->GetLayerData(Layer);
			DataInLayer	*LyDst=PageDst->GetLayerData(Layer);

			if(FlagMaster==true){
				LyDst->GetMasterBuff().Load(f);
				LyDst->GetMasterBuff().SetChanged(true);
			}

			if(FlagTarget==true){
				LyDst->GetTargetBuff().Load(f);
				LyDst->GetTargetBuff().SetChanged(true);
			}
		}
	}
}
int		DataInPage::GetCountOfCompressing(void)
{
	return ThreadImageCompresser.GetCountOfCompressing();
}
//---------------------------------------------------------------------------
PageDataInOnePhase::PageDataInOnePhase(int phaseCode ,LayersBase *parent)
{
	PhaseCode		=phaseCode;
	Parent			=parent;
	PageData		=NULL;
	FilterContainer	=NULL;
	AllocatedPageNumb=0;
	MasterCode		=-1;
	FromSourcePhase	=-1;
	LotAutoCount	=-1;
}
PageDataInOnePhase::~PageDataInOnePhase(void)
{
	Release();
}

void	PageDataInOnePhase::InitialCreate(LayersBase *Base ,bool EnabledImageMemoryAllocation)
{
	if(PageData!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			if(PageData[page]!=NULL){
				PageData[page]->ReleaseInside();
			}
		}
	}

	if(FilterContainer!=NULL){
	    for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;
		FilterContainer=NULL;
	}

	if(PageData!=NULL){
	    for(int i=0;i<AllocatedPageNumb;i++){
		    PageData[i]->Release();
			delete	PageData[i];
	        }
		delete	[]PageData;
		PageData=NULL;
	}

	AllocatedPageNumb	=Base->GetPageNumb();
	PageData		=new DataInPage*[AllocatedPageNumb];

	FilterContainer=new FilterInstanceContainer*[AllocatedPageNumb];
	for(int page=0;page<AllocatedPageNumb;page++){
		FilterContainer[page]=new FilterInstanceContainer(GetLayersBase());
	}

	for(int i=0;i<AllocatedPageNumb;i++){
		PageData[i]=new DataInPage(i,this);
		//PageData[i]->Parent=this;
		PageData[i]->Initial(EnabledImageMemoryAllocation);
		PageData[i]->Page=i;
	}
}
void	PageDataInOnePhase::Release(void)
{
	if(PageData!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			PageData[page]->ReleaseInside();
		}
	    for(int page=0;page<AllocatedPageNumb;page++){
		    PageData[page]->Release();
			delete	PageData[page];
	        }
		delete	[]PageData;
		PageData=NULL;
	}
	if(FilterContainer!=NULL){
	    for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;
		FilterContainer=NULL;
	}
	AllocatedPageNumb=0;
}

void	PageDataInOnePhase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	for(int i=0;i<AllocatedPageNumb;i++){
		if(PageData[i]!=NULL){
			PageData[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
		}
	}
}
bool	PageDataInOnePhase::Reallocate(int newPageNumb ,int newLayerNumb)
{
	if(FilterContainer!=NULL){
	    for(int page=0;page<AllocatedPageNumb;page++){
			FilterContainer[page]->ReleaseAll();
			delete	FilterContainer[page];
		}
		delete	[]FilterContainer;
		FilterContainer=NULL;
	}
	FilterContainer=new FilterInstanceContainer*[newPageNumb];
	for(int page=0;page<newPageNumb;page++){
		FilterContainer[page]=new FilterInstanceContainer(GetLayersBase());
	}
	if(AllocatedPageNumb<newPageNumb){
		DataInPage	**tPageData=new DataInPage*[newPageNumb];
		int	i;
		for(i=0;i<AllocatedPageNumb;i++){
			if(PageData[i]==NULL){
				break;
			}
			tPageData[i]=PageData[i];
			PageData[i]=NULL;
			tPageData[i]->Reallocate(newLayerNumb);
		}
		delete	[]PageData;
		PageData=tPageData;
		for(;i<newPageNumb;i++){
			PageData[i]=new DataInPage(i,this);
			//PageData[i]->Parent=this;
			PageData[i]->Initial(true);
			PageData[i]->Page=i;
		}
	}
	else if(AllocatedPageNumb>newPageNumb){
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
		for(int i=newPageNumb;i<AllocatedPageNumb;i++){
			PageData[i]->Release();
			delete	PageData[i];
			PageData[i]=NULL;
		}
	}
	else{
		if(PageData==NULL){
			PageData=new DataInPage*[newPageNumb];
			for(int i=0;i<newPageNumb;i++){
				PageData[i]=NULL;
			}
		}
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=new DataInPage(i,this);
				//PageData[i]->Parent=this;
				PageData[i]->Initial(true);
				PageData[i]->Page=i;
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
	}
	AllocatedPageNumb	=newPageNumb;

	return true;
}
bool	PageDataInOnePhase::LoadFilterContainer(QIODevice *f)
{
	if(FilterContainer!=NULL){
		int32	Ver;
		if(::Load(f,Ver)==false){
			return false;
		}
		if(Ver>=100000){
			int32	PageNumb;
			if(::Load(f,PageNumb)==false){
				return false;
			}
			int	n=max(PageNumb,GetAllocatedPageNumb());
			int	page;
			for(page=0;page<GetAllocatedPageNumb();page++){
				delete	FilterContainer[page];
			}
			delete	[]FilterContainer;
					
			FilterContainer=new FilterInstanceContainer*[n];
			for(page=0;page<GetAllocatedPageNumb();page++){
				FilterContainer[page]=new FilterInstanceContainer(GetLayersBase());
			}
			for(page=0;page<PageNumb && page<GetAllocatedPageNumb();page++){
				if(FilterContainer[page]->Load(f)==false){
					return false;
				}
			}
			while(page<PageNumb){
				FilterInstanceContainer *DummyContainer=new FilterInstanceContainer(GetLayersBase());
				if(DummyContainer->Load(f)==false){
					delete	DummyContainer;
					return false;
				}
				delete	DummyContainer;
				page++;
			}
			return true;
		}
	}
	return false;
}
bool	PageDataInOnePhase::SaveFilterContainer(QIODevice *f)
{
	if(FilterContainer!=NULL){
		int32	Ver=100000;
		if(::Save(f,Ver)==false){
			return false;
		}
		int32	PageNumb=GetAllocatedPageNumb();
		if(::Save(f,PageNumb)==false){
			return false;
		}
		for(int page=0;page<PageNumb;page++){
			if(FilterContainer[page]->Save(f)==false){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool	PageDataInOnePhase::SavePhaseSource(QIODevice *f)
{
	if(::Save(f,FromSourcePhase)==false){
		return false;
	}
	return true;
}
bool	PageDataInOnePhase::LoadPhaseSource(QIODevice *f)
{
	if(::Load(f,FromSourcePhase)==false){
		return false;
	}
	return true;
}

bool	PageDataInOnePhase::ExecuteFilterBeforeScan(LayersBase *Base)
{
	bool	Ret=true;

	int strategic = GetLayersBase()->GetCurrentStrategicNumber();
	StrategicListContainer SList;
	GetLayersBase()->GetParamGlobal()->GetStrategy(strategic,SList);

	QList<int> execPageList;
	for(StrategicList *item = SList.GetFirst(); item!=NULL; item=item->GetNext()){
		execPageList.append( item->Page );
	}

	for(int page=0;page<GetAllocatedPageNumb();page++){
		if(execPageList.contains(page)==false){
			continue;
		}
		FilterContainer[page]->ExecuteBeforeScan();
	}
	return Ret;
}

bool	PageDataInOnePhase::ExecuteFilteringMaster(LayersBase *Base)
{
	ImageBuffer *IBuff[100];
	ImageBuffer **IPointer;
	bool	Ret=true;

	if(Base->GetLayerNumb()>sizeof(IBuff)/sizeof(IBuff[0])){
		IPointer=new ImageBuffer*[Base->GetLayerNumb()];
	}
	else{
		IPointer=IBuff;
	}
	int strategic = GetLayersBase()->GetCurrentStrategicNumber();
	StrategicListContainer SList;
	GetLayersBase()->GetParamGlobal()->GetStrategy(strategic,SList);

	QList<int> execPageList;
	for(StrategicList *item = SList.GetFirst(); item!=NULL; item=item->GetNext()){
		execPageList.append( item->Page );
	}

	for(int page=0;page<GetAllocatedPageNumb();page++){
		if(execPageList.contains(page)==false){
			continue;
		}
		for(int L=0;L<Base->GetLayerNumb();L++){
			IPointer[L]=&GetPageData(page)->GetLayerData(L)->GetMasterBuff();
		}
		if(FilterContainer[page]->ExecuteImage(IPointer,Base->GetLayerNumb())==false){
			Ret=false;
			break;
		}
	}
	if(IPointer!=IBuff){
		delete	[]IPointer;
	}
	return Ret;
}
bool	PageDataInOnePhase::ExecuteFilteringTarget(LayersBase *Base)
{
	ImageBuffer *IBuff[100];
	ImageBuffer **IPointer;
	bool	Ret=true;

	if(Base->GetLayerNumb()>sizeof(IBuff)/sizeof(IBuff[0])){
		IPointer=new ImageBuffer*[Base->GetLayerNumb()];
	}
	else{
		IPointer=IBuff;
	}

	if(Base->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetAllocatedPageNumb();page++){
			for(int L=0;L<Base->GetLayerNumb();L++){
				IPointer[L]=&GetPageData(page)->GetLayerData(L)->GetTargetBuff();
			}
			if(FilterContainer[page]->ExecuteImage(IPointer,Base->GetLayerNumb())==false){
				Ret=false;
				break;
			}
		}
	}
	else{
		StrategicListContainer SList;
		Base->GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),SList);
		int	N=0;
		int	PageType[10];
		int	PageTypeNumb=0;
		for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			int	i;
			for(i=0;i<PageTypeNumb;i++){
				if(PageType[i]==s->Page){
					break;
				}
			}
			if(i>=PageTypeNumb){
				PageType[PageTypeNumb]=s->Page;
				PageTypeNumb++;
				if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
					break;
			}
		}
	
		//éÊÇËçûÇ›ÇëÅÇ≠Ç∑ÇÈÇΩÇﬂÇ…êÊÇ…GetImageÇæÇØÇçsÇ§
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
		for(int camcode=0;camcode<PageTypeNumb;camcode++){
			int	BuffNumb=0;
			int	CamNo=Base->GetParamGlobal()->GetCameraNo(PageType[camcode]);
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				if(PageType[camcode]!=s->Page)
					continue;

				IPointer[BuffNumb]=&GetPageData(s->Page)->GetLayerData(s->Layer)->GetTargetBuff();
				BuffNumb++;
			}
			if(FilterContainer[PageType[camcode]]->ExecuteImage(IPointer,BuffNumb)==false){
				Ret=false;
				break;
			}
		}
	}
	if(IPointer!=IBuff){
		delete	[]IPointer;
	}
	return Ret;
}

void	PageDataInOnePhase::CopyImageMasterFrom(LayersBase *Base,PageDataInOnePhase *src)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		for(int L=0;L<Base->GetLayerNumb();L++){
			GetPageData(page)->GetLayerData(L)->GetMasterBuff()=src->GetPageData(page)->GetLayerData(L)->GetMasterBuff();
		}
	}
}

void	PageDataInOnePhase::CopyImageTargetFrom(LayersBase *Base,PageDataInOnePhase *src)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		for(int L=0;L<Base->GetLayerNumb();L++){
			GetPageData(page)->GetLayerData(L)->GetTargetBuff()=src->GetPageData(page)->GetLayerData(L)->GetTargetBuff();
		}
	}
}
void	PageDataInOnePhase::CopyTargetToTransposition(void)
{
	for(int page=0;page<GetAllocatedPageNumb();page++){
		GetPageData(page)->CopyTargetToTransposition();
	}
}
bool	PageDataInOnePhase::GetMasterInfo(int32 &MachineID ,QString &MasterName ,QString &Remark)
{
	XDateTime	RegTime;
	int32		Version;
	XDateTime	LastEditTime;
	int32		CategoryID;
	int16		MasterType;

	DatabaseLoader	*DLoader=GetLayersBase()->GetDatabaseLoader();
	if(DLoader!=NULL){
		bool	ret=DLoader->G_SQLGetMasterInfo(GetLayersBase()->GetDatabase()
									,MasterCode
									,MachineID
									,RegTime
									,MasterName ,Remark
									,Version
									,LastEditTime
									,CategoryID
									,MasterType);
		return ret;
	}
	return false;
}

bool	PageDataInOnePhase::GetLotInfo(QString &LotID ,QString &LotName,QString &Remark)
{
	XDateTime LastUpdated;

	DatabaseLoader	*DLoader=GetLayersBase()->GetDatabaseLoader();
	if(DLoader!=NULL){
		bool	ret=DLoader->G_GetInspectionLot(GetLayersBase()->GetDatabase()
								,LotAutoCount,MasterCode
								,LastUpdated
								,LotID
								,LotName
								,Remark);
		return ret;
	}
	return false;
}
bool	PageDataInOnePhase::IsEdited(void)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		if(GetPageData(page)->IsEdited()==true){
			return true;
		}
	}
	return false;
}

void	PageDataInOnePhase::SetEdited(bool edited)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SetEdited(edited);
	}
}

void	PageDataInOnePhase::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SwapImageOutOfBuffer(ImageDataType);
	}
}
void	PageDataInOnePhase::SwapImageInToBuffer(int ImageDataType)
{
	for(int page=0;page<AllocatedPageNumb;page++){
		GetPageData(page)->SwapImageInToBuffer(ImageDataType);
	}
}
int		PageDataInOnePhase::GetCountOfCompressing(void)
{
	int	Count=0;
	for(int page=0;page<AllocatedPageNumb;page++){
		Count+=GetPageData(page)->GetCountOfCompressing();
	}
	return Count;
}
bool    PageDataInOnePhase::SaveRegulation(QIODevice *f)
{
	int32	PageNumb=Parent->GetPageNumb();
	if(::Save(f,PageNumb)==false)
		return false;
	for(int page=0;page<PageNumb;page++){
		if(GetPageData(page)->GetRegulation().Save(f)==false){
			return false;
		}
	}
	return true;
}

bool    PageDataInOnePhase::LoadRegulation(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false)
		return false;
	for(int page=0;page<iPageNumb && page<Parent->GetPageNumb();page++){
		if(GetPageData(page)->GetRegulation().Load(f)==false){
			return false;
		}
	}
	return true;

}
void	PageDataInOnePhase::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	DataInPage	*Pg=GetPageData(0);
	x1=Pg->GetOutlineOffset()->x;
	y1=Pg->GetOutlineOffset()->y;
	x2=Pg->GetOutlineOffset()->x+Parent->GetDotPerLine();
	y2=Pg->GetOutlineOffset()->y+Parent->GetMaxLines();
	for(int page=1;page<Parent->GetPageNumb();page++){
		DataInPage	*Pg=GetPageData(page);
		int	ix1=Pg->GetOutlineOffset()->x;
		int	iy1=Pg->GetOutlineOffset()->y;
		int	ix2=Pg->GetOutlineOffset()->x+Parent->GetDotPerLine();
		int	iy2=Pg->GetOutlineOffset()->y+Parent->GetMaxLines();
		x1=min(x1,ix1);
		y1=min(x1,iy1);
		x2=max(x2,ix2);
		y2=max(x2,iy2);
	}
}
//==================================================================================================
LayersBase::LayersBase(const QString &_TypeName ,LayersBase *ParentLayer)
:TypeName(_TypeName)
,OnTerminating(false)
,ResultHistryData(this)
,TopView(256,256,QImage::Format_RGB32)
,ArrangementDLLStock(this)
,LogCreater("")
,UndoDataStocker(this),RedoDataStocker(this)
,ChangingDataStructure(QMutex::Recursive)
{
	Parent					=NULL;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
	InstShowLoadingDLLForm	=NULL;

	OnChanging				=false;
	MilisecExecuteFilter	=0;
	InsideLearningEditor	=false;
	ResultThread			=NULL;
	FRegistry				=new FileRegistry(ParentLayer->GetFRegistry()->GetFileName());
	int	LanguageCode=GetFRegistry()->LoadRegInt("Language",0);
	LanguagePackageData		=new LanguagePackage();
	LoadLanguageSolution(ParentLayer->GetLocalLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	ParamGlobalData			=new ParamGlobal(this);
	ParamCommData			=new ParamComm(this);
	ParamCommData->Mastered	=true;

	ParamGUIData			=NULL;
	RCmdBase				=NULL;
	GlobalOffset			=NULL;
	SendingData				=NULL;
	GlobalPageNumb			=0;

	RIntegrationCmdBase		=NULL;
	IntegrationSendingData	=NULL;

	DefaultArrangeMode		=false;
	EntryPoint				=NULL;
	RootDBase				=NULL;
	OriginalRootDBase		=true;
	CurrentStrategicNumber	=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	StopCommSender			=false;
	MasterCode				= -1;
	PageData				=NULL;
	PageDataPhase			=NULL;
	DrawPageIndex			=NULL;
	CurrentPhase			=0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb		=0;
	//MachineID				=0;
	RegTime					=XDateTime::currentDateTime();
	WorkerID				= -1;
	Version					=RegulusVersion;
	LoadedVersion			=RegulusVersion;
	LastEditTime			=RegTime;
	StartInspectionTime		=RegTime;
	CategoryID				= -1;
	_CurrentInspectID		=0;
	_LastInspectID			=0;
	InspectionRemark		=0;
	LotInfo					=NULL;
	ExecuterDim				=NULL;
	AllocExecuterDim		=0;
	CurrentCalcPoint		=0;
	CurrentDrawPoint		=0;
	LastCurrentCalcPoint	=0;
	AlgoDLLContPointer		=new AlgorithmDLLContainer(this);
	LogicDLLBase			=new LogicDLLBaseClass(this);;
	ResultDLLBase			=new ResultDLLBaseClass(this);
	SequenceInstance		=NULL;
	MesssageOutForSequence	=NULL;
	InspectionTimeMilisec	=0;
	DBLoader				=NULL;
	MasterType				=0;		//0:MasterData 1:PieceData
	PieceStock				=NULL;
	BootingLevel			=0;
	OnProcessing			=NULL;
	ErrorOccurs				=0;
	AckFlag					=NULL;
	AllocatedAckFlag		=0;
	DirectCommBase			=NULL;
	ProcessingReEntrant		=0;
	LightBase				=NULL;
	ForceChangedInspectID	=false;

	MTransfer				=NULL;
	MainWidget				=NULL;
	LocalParamStocker		=NULL;
	AppPointer	=(QApplication *)QCoreApplication::instance();
	ShouldWriteResult		=true;
	FilterBank				=NULL;
	OutlineOffsetWriter		=NULL;
	LogoStockerInstance		=NULL;
	AnyData					=NULL;
	GeneralStockerData		=NULL;
	ErrorContainer			=NULL;
	LatchedInspectionNumber	=0;
	InsideReEntrant			=0;
	ResultWrittenID			=0;
	PasswordHolder			=NULL;
	SyncGUIData				=NULL;
	StatusControllerData	=NULL;
	LearningRegisterData	=NULL;

	RCmdDirectCommBase		=NULL; 
	LearningRegData			=NULL;
	TmpHidingProcessingForm	=false;
	ListOfQImageStockerData	=NULL;

	MachineID				=-1;
	MachineIDFromMaster		=MachineID;
	CurrentScanPhaseNumber	=0;
	CurrentLibFolderID		=-1;
	DataOfShareMasterContainer	=NULL;
	MainThread	=QThread::currentThreadId();
	PasteListMatrixContainerBase	=NULL;
	OperationLoggerData		=NULL;
	PrinterClassPackData	=NULL;
	ShrinkingPackContainerInstance	=NULL;
	LensWindow				=NULL;
	ZoneWindow				=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm		=0;
	IntegrationBaseData		=NULL;
	ResizeData				=NULL;
	ResultAnalizerDLLPack		=NULL;
	ResultAnalizerItemBasePack	=NULL;
}
LayersBase::~LayersBase(void)
{
//	if(_CrtCheckMemory()==false)
//		ErrorOccurs++;

	OnTerminating=true;

	GUICmdContainer			.RemoveAll();
	DirectCmdContainer		.RemoveAll();
	IntegrationCmdContainer	.RemoveAll();

	ReleaseAll();
	_heapchk();

	MainThread				=NULL;
	AppPointer				=NULL;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
}

bool    LayersBase::InitialDatabaseLoader(QString &Msg)
{
	if(GetDatabaseLoader()==NULL){
		DBLoader=new DatabaseLoader(this);
		if(GetDatabaseLoader()->InitialLoad("ServiceForDBLib")==false){
			Msg="ServiceForDBLib.dll does not exist.";
			return false;
		}
	}
	return true;
}

bool    LayersBase::Initial(EntryPointBase *pEntryPoint ,QString &Msg)
{
	qRegisterMetaType<ResultInspection *>("ResultInspection *");
	qRegisterMetaType<XDateTime>("XDateTime");

	//omp_set_nested(1);
	if(InitialDatabaseLoader(Msg)==false){
		return false;
	}
	InitialCreatePages(pEntryPoint);
	GetLocalParamStocker()->Load();
	OnProcessing	=new OnProcessingForm(this);

	GetLogoStockerInstance()->LoadFromLogoListFile(this);

	GUICmdContainer=new GUICmdReqBmpForTopView(this,QString("ANY"),QString("ANY"));
	GUICmdContainer=new GUICmdSendBmpForTopView(this,QString("ANY"),QString("ANY"));
	GUICmdContainer=new CmdReqSaveMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new CmdReqLoadMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new CmdAckLoadMasterForPage(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendAlgorithmItemIndependentPack(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqAlgorithmGeneralData(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendAlgorithmGeneralData(this,QString("ANY"),QString("ANY"),-1);
	
	GUICmdContainer=new GUICmdReqCopiedList(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendCopiedList(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqCopiedForSave(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckCopiedForSave(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqCopiedForDelete(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSendCopiedForLoad(this,QString("ANY"),QString("ANY"),-1);

	GUICmdContainer=new GUICmdReqImageCheckByte(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckImageCheckByte(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSndImageMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdReqAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdAckAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);
	GUICmdContainer=new GUICmdSndAlgoDataMixTransfer(this,QString("ANY"),QString("ANY"),-1);

	GUICmdContainer=new ResultCmdSaveSlave				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqPartialImage			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendPartialImage			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendProcessing			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendProcessingAdd			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendClose					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendAck					(this ,"ANY","ANY",-1);
	GUICmdContainer=new CmdCameraErrorOccursMsg			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdCopyImage					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetForceChangedInspectID	(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSendParameters			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqUpdateAlgorithmOnPiece	(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckUpdateAlgorithmOnPiece	(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqEdited			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendEdited		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetEdited			(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetCalcDone		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendOffset		(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqCheckSlave		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckCheckSlave		(this ,"ANY","ANY",-1);

	GUICmdContainer=new CmdReqRemoveStockedResult		(this ,"ANY","ANY",-1);
	GUICmdContainer=new ResultCmdReqLotChangedSlave		(this ,"ANY","ANY",-1);

	GUICmdContainer=new CmdWritternResult				(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdLoadPixWithAlgorithm		(this ,"ANY","ANY",-1);
	GUICmdContainer=new CmdReportError					(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendInspectionNumber		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendMachineID				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSendAllComms				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqSetCurrentPhase		(this,"ANY","ANY",-1);

	PacketWritternResult=new CmdWritternResult			(this ,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdMakeUncoveredMap			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqRewindExecuter			(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqEnumHistgram			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckEnumHistgram			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqHistgram				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckHistgram				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqInfoForHistgram		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckInfoForHistgram		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqInfoForHistDirect		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckInfoForHistDirect		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqAlgorithmUsageLib		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckAlgorithmUsageLib		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqHistgramLib			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckHistgramLib			(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdChangeLotInfo				(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdDeliverManualExecuter		(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSetCurrentScanPhaseNumber	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdForceStrategicNumber		(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdSetLibFolderID			(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdReqChangedAlgo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckChangedAlgo			(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdDeliverChangedAlgo		(this,"ANY","ANY",-1);

	GUICmdContainer=new GUICmdSendResultAnalizerData	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdReqResultAnalizerShowData	(this,"ANY","ANY",-1);
	GUICmdContainer=new GUICmdAckResultAnalizerShowData	(this,"ANY","ANY",-1);

	DirectCmdContainer	=new SlaveCommForkStart	(this,"ANY","ANY",-1);
	DirectCmdContainer	=new SlaveCommJoin		(this,"ANY","ANY",-1);

	LearningRegisterData->InitialInSystem(GUICmdContainer);
	GUICmdContainer=PacketWritternResult;

	return true;
}

void	LayersBase::InitialCreatePages(EntryPointBase *pEntryPoint ,bool EnabledImageMemoryAllocation)
{
	EntryPoint=pEntryPoint;
	//QMessageBox::warning(NULL,"","1");
	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			delete	PageDataPhase[i];
		}
		delete	[]PageDataPhase;
	}
	//QMessageBox::warning(NULL,"",QString("NN:")
	//							+QString::number(GetPhaseNumb())
	//							+QString(",")
	//							+QString::number(GetPageNumb())
	//							+QString(",")
	//							+QString::number(GetLayerNumb())
	//							);
	AllocatedPhaseNumb=GetPhaseNumb();
	if(AllocatedPhaseNumb==0)
		AllocatedPhaseNumb=1;
	PageDataPhase=new PageDataInOnePhase*[AllocatedPhaseNumb];
	for(int i=0;i<AllocatedPhaseNumb;i++){
		PageDataPhase[i]=new PageDataInOnePhase(i,this);
		PageDataPhase[i]->InitialCreate(this,EnabledImageMemoryAllocation);
	}

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
	PageData=PageDataPhase[0];
	DrawPageIndex	=new DataInPage*[GetPageNumb()];
	//AllocatedPageNumb	=GetPageNumb();
	for(int i=0;i<GetPageNumb();i++){
		DrawPageIndex[i]=PageData->GetPageData(i);
	}

	if(GetOutlineOffsetWriter()!=NULL){
		GetOutlineOffsetWriter()->Initial();
	}
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;

	if((pEntryPoint!=NULL) && (pEntryPoint->IsMasterPC()==true)){
		GlobalPageNumb=GetPageNumb();
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
		if(GetIntegrationBasePointer()!=NULL){
			int	SlaveNumb=GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			if(SlaveNumb==0)
				SlaveNumb=1;
			IntegrationSendingData=new bool[SlaveNumb];
		}
	}
}

void	LayersBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	LockChangingDataStructure();

	if(GetParamGlobal()->DotPerLine!=NewDotPerLine || GetParamGlobal()->MaxLines !=NewMaxLines){
		SetOnChanging(true);
		GSleep(1000);
		GetParamGlobal()->DotPerLine	=NewDotPerLine;
		GetParamGlobal()->MaxLines		=NewMaxLines;
		for(int i=0;i<AllocatedPhaseNumb;i++){
			if(PageDataPhase[i]!=NULL){
				PageDataPhase[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
			}
		}
		for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
			a->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
		}
		EntryPointBase	*EBase=GetEntryPoint();
		if(EBase!=NULL){
			ExecuteInspectBase	*E=EBase->GetExecuteInspect();
			if(E!=NULL){
				E->ReallocXYPixels(NewDotPerLine ,NewMaxLines);
			}
		}

		SetOnChanging(false);
		emit	SignalChangedXY();
	}
	UnlockChangingDataStructure();
}

bool	LayersBase::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(newPhaseNumb<=0){
		newPhaseNumb=GetParamGlobal()->GetPhaseNumb();
	}
	if(newPageNumb<=0){
		newPageNumb=GetParamGlobal()->GetPageNumb();
	}
	if(newLayerNumb<=0){
		newLayerNumb=GetParamGlobal()->GetLayerNumb();
	}
	if(GetParamGlobal()->PhaseNumb	==newPhaseNumb
	&& GetParamGlobal()->PageNumb	==newPageNumb
	&& GetParamGlobal()->LayerNumb	==newLayerNumb)
		return true;

	LockChangingDataStructure();

	SetOnChanging(true);
	GSleep(1000);

	GetParamGlobal()->PhaseNumb	=newPhaseNumb;
	GetParamGlobal()->PageNumb	=newPageNumb;
	GetParamGlobal()->LayerNumb	=newLayerNumb;
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocatedPhaseNumb){
			PageDataInOnePhase	**iPageDataPhase=new PageDataInOnePhase*[newPhaseNumb];
			for(int i=0;i<AllocatedPhaseNumb;i++){
				iPageDataPhase[i]=PageDataPhase[i];
				PageDataPhase[i]=NULL;
				iPageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
			}
			PageDataInOnePhase	**tmpPhaseDim=PageDataPhase;
			PageDataPhase=iPageDataPhase;
			for(int i=AllocatedPhaseNumb;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new PageDataInOnePhase(i,this);
				iPageDataPhase[i]->InitialCreate(this,true);
			}
			delete	[]tmpPhaseDim;
		}
		else if(newPhaseNumb<AllocatedPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
			for(int i=newPhaseNumb;i<AllocatedPhaseNumb;i++){
				delete	PageDataPhase[i];
				PageDataPhase[i]=NULL;
			}
		}
		else{
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new PageDataInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate(this,true);
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
		}
		AllocatedPhaseNumb=newPhaseNumb;
	}
	else{
		InitialCreatePages(EntryPoint ,true);
	}
	if(CurrentPhase>=AllocatedPhaseNumb)
		CurrentPhase=AllocatedPhaseNumb-1;
	PageData=PageDataPhase[CurrentPhase];

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
	DrawPageIndex	=new DataInPage*[newPageNumb];
	//AllocatedPageNumb	=newPageNumb;
	for(int i=0;i<newPageNumb;i++){
		DrawPageIndex[i]=PageData->GetPageData(i);
	}
	if(GetOutlineOffsetWriter()!=NULL){
		GetOutlineOffsetWriter()->Initial();
	}
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;

	if((EntryPoint!=NULL) && (EntryPoint->IsMasterPC()==true)){
		GlobalPageNumb=newPageNumb;
		if(GlobalOffset!=NULL){
			delete	[]GlobalOffset;
		}
		GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			GlobalOffset[page].OutlineOffset= *GetPageData(page)->GetOutlineOffset();
		}
		SendingData=new bool[GlobalPageNumb];
		for(int page=0;page<GlobalPageNumb;page++){
			SendingData[page]=false;
		}
	}
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();
	emit	SignalChangedPhasePageLayer();
	return true;
}
bool	LayersBase::RemovePhase(int RemovedPhaseCode)
{
	if(GetParamGlobal()->PhaseNumb<=1){
		return false;
	}
	if(RemovedPhaseCode<0 || GetParamGlobal()->PhaseNumb<=RemovedPhaseCode){
		return false;
	}

	LockChangingDataStructure();

	SetOnChanging(true);
	GSleep(1000);

	GetParamGlobal()->PhaseNumb	=GetParamGlobal()->PhaseNumb-1;
	if(PageDataPhase!=NULL){
		delete	PageDataPhase[RemovedPhaseCode];
		int	MaxAllocatedPhaseNumb=max(AllocatedPhaseNumb,GetParamGlobal()->PhaseNumb);
		for(int phase=RemovedPhaseCode+1;phase<MaxAllocatedPhaseNumb;phase++){
			PageDataPhase[phase-1]=PageDataPhase[phase];
		}
		for(int phase=GetParamGlobal()->PhaseNumb;phase<AllocatedPhaseNumb;phase++){
			PageDataPhase[phase]=0;
		}
	}
	if(CurrentPhase>=GetParamGlobal()->PhaseNumb){
		CurrentPhase=GetParamGlobal()->PhaseNumb-1;
	}
	PageData=PageDataPhase[CurrentPhase];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->SetPhaseCode(phase);
	}

	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->RemovePhase(RemovedPhaseCode);
		}
	}
	LoadFilterDef();
	if(GetResultThread()!=NULL){
		GetResultThread()->RemovePhase(RemovedPhaseCode);
	}
	LoadOutlineOffsetForDatabase();

	EntryPointBase	*E=GetEntryPoint();
	if(E!=NULL){
		ExecuteInspectBase	*Ex=E->GetExecuteInspect();
		if(Ex!=NULL){
			Ex->RemovePhase(RemovedPhaseCode);
		}
	}
	SetOnChanging(false);
	UnlockChangingDataStructure();

	return true;
}

void	LayersBase::SetGlobalOffset(int	_GlobalPageNumb ,DataInPage::ConstructionData *_GlobalOffset)
{
	GlobalPageNumb=_GlobalPageNumb;
	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
	}
	GlobalOffset=new DataInPage::ConstructionData[GlobalPageNumb];
	for(int page=0;page<GlobalPageNumb;page++){
		GlobalOffset[page].OutlineOffset=(_GlobalOffset+page)->OutlineOffset;
	}
}

void	LayersBase::ChangeGlobalOffset(int _GlobalPage ,XYData &Dest)
{
	if(0<=_GlobalPage && _GlobalPage<GlobalPageNumb){
		GlobalOffset[_GlobalPage].OutlineOffset=Dest;
	}
}

LotInformation			*LayersBase::GetLot(int n)
{	
	return LotInfo->GetLot(n);
}

void    LayersBase::InitialAlgorithm(RootNameListContainer &List ,char *AlgorithmPath,bool LoadAll)
{
	GetGeneralStocker()->OpenDLL();
	GetGeneralStocker()->Initial();

	GetAlgoDLLContPointer()->SearchAddDLL(List,this,QString(AlgorithmPath),LoadAll);
	GetLogicDLLBase()->AddDLLs(*GetAlgoDLLContPointer(),this);

	QStringList	ErrorMsg;
	if(GetLogicDLLBase()->CheckDuplicatedAlgorithm(ErrorMsg)==true){
		QString	Msg;
		for(int i=0;i<ErrorMsg.count();i++){
			Msg +=ErrorMsg[i];
		}
		QMessageBox::critical(0,"Duplicated algorithm dll",Msg);
	}
	CreateAlgorithmPointer();
}

void    LayersBase::CopyAlgorithm(const LayersBase *parent ,RootNameListContainer &List ,char *AlgorithmPath,bool LoadAll)
{
	GetGeneralStocker()->OpenDLL();
	GetGeneralStocker()->Initial();

	GetAlgoDLLContPointer()->CopyAddDLL((const AlgorithmDLLContainer *)(parent->GetAlgoDLLContPointer()));
	GetLogicDLLBase()->AddDLLs(*GetAlgoDLLContPointer(),this);

	QStringList	ErrorMsg;
	if(GetLogicDLLBase()->CheckDuplicatedAlgorithm(ErrorMsg)==true){
		QString	Msg;
		for(int i=0;i<ErrorMsg.count();i++){
			Msg +=ErrorMsg[i];
		}
		QMessageBox::critical(0,"Duplicated algorithm dll",Msg);
	}
	CreateAlgorithmPointer();
}
void	LayersBase::InitializeToStart(void)
{
	CurrentCalcPoint	=0;
	CurrentDrawPoint	=0;
	LastCurrentCalcPoint=0;

	_CurrentInspectID	=0;
	_LastInspectID		=0;
	CurrentStrategicNumber			=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicQueue.RemoveAll();
	CurrentScanPhaseNumber			=0;
	InspectionNumber				=0;
	LatchedInspectionNumber			=0;
}
void    LayersBase::InitialAfterParamLoaded(void)
{
	GetLogicDLLBase()->InitialAfterParamLoaded();
}
void    LayersBase::ReallocAlgorithm(void)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->ReallocAlgorithmBase(GetEntryPoint());
	}
}

bool    LayersBase::InitialLight(bool OutputMode)
{
	if(GetLightBase()==NULL){
		LightBase=new LightClassPack(this);
		if(GetLightBase()->Initial(ErrorOccurs,OutputMode)==false){
			delete	LightBase;
			LightBase=NULL;
			return false;
		}
		if(QFile::exists(GetParamGlobal()->LightSettingFileName)==true){
			QFile	File(GetParamGlobal()->LightSettingFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(GetLightBase()->Load(&File)==true){
					GetLightBase()->SetPattern(0);
					if(GetParamGlobal()->InitialLightON==true){
						GetLightBase()->LightOn();
					}
					else{
						GetLightBase()->LightOff();
					}
					return true;
				}
			}
		}
	}
	else{
		return true;
	}
	return false;
}

bool    LayersBase::InitialFilterBank(void)
{
	if(GetFilterBank()!=NULL){
		GetFilterBank()->SearchAddDLL(ErrorOccurs);
	}
	if(ErrorOccurs!=Error_Nothing){
		return false;
	}
	return true;
}
bool    LayersBase::InitialResultAnalizer(void)
{
	if(GetResultAnalizerDLLContainer()!=NULL){
		if(GetResultAnalizerDLLContainer()->OpenDLL()==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::InitialPrinter(void)
{
	if(GetPrinterClassPackData()==NULL){
		PrinterClassPackData=new PrinterClassPack(this);
		if(GetPrinterClassPackData()->Initial(ErrorOccurs)==false){
			delete	PrinterClassPackData;
			PrinterClassPackData=NULL;
			return false;
		}
		if(QFile::exists(GetParamGlobal()->LightSettingFileName)==true){
			QFile	File(GetParamGlobal()->LightSettingFileName);
			if(File.open(QIODevice::ReadOnly)==true){
				if(GetPrinterClassPackData()->Load(&File)==true){
					return true;
				}
			}
		}
		return true;
	}
	else{
		return true;
	}
}
bool    LayersBase::InitialSyncGUI(void)
{
	if(SyncGUIData!=NULL && GetParamGlobal()->SyncGUIFileName.isEmpty()==false){
		QString	Path=GetCurrentPath();
		QDir::setCurrent(Path);
		QFile	F(GetParamGlobal()->SyncGUIFileName);
		if(F.open(QIODevice::ReadOnly)==true){
			if(SyncGUIData->Load(&F)==false){
				return false;
			}
			SyncGUIData->Start();
			return true;
		}
		return false;
	}
	else{
		return true;
	}
	return false;
}

void    LayersBase::CreateAlgorithmPointer(void)
{
	PreAlignmentBase	.RemoveAll();
	AlignmentBase		.RemoveAll();
	PreProcessingBase	.RemoveAll();
	ProcessingBase		.RemoveAll();
	PostProcessingBase	.RemoveAll();
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePreAlignment){
				PreAlignmentBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypeAlignment){
				AlignmentBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePreProcessing){
				PreProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypeProcessing){
				ProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
			else if(L->MaskAlgorithmType(AlgorithmBit_TypeMask)==AlgorithmBit_TypePostProcessing){
				PostProcessingBase.AppendList(new AlgorithmBasePointerList(L->GetInstance()));
			}
		}
	}
}
void    LayersBase::InitialAlgorithmBlob(void)
{
	if(IsDatabaseOk()==true){
		GetLogicDLLBase()->CheckAndCreateBlobInMasterPageTable(GetDatabase());
	}
}
void    LayersBase::InitialAlgorithmLibrary(void)
{
	GetLogicDLLBase()->InitialLibrary(this);
	GetLibType()->LoadFromDatabase(this);
}

void    LayersBase::InitialFinalize(QWidget *mainform ,int TransferListenPort)
{
	if(GetMTransfer()==NULL){
		MTransfer=new MixTransferComm(this,mainform);
		GetMTransfer()->StartServer(TransferListenPort);
	}
}

void    LayersBase::DeliverOutlineOffset(void)
{
	if(GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendOffset	RCmd(this,"ANY","ANY",page);
			RCmd.InitialInMaster();
			RCmd.Send(NULL,page,0);
		}
	}
}

bool    LayersBase::OpenCommsForDirectComm(void)
{
	if(GetDirectCommBase()==NULL){
		if(GetEntryPoint()->IsMasterPC()==false || GetParamComm()->ConnectedPCNumb==0){
			if(GetDirectCommBase()==NULL){
				DirectComm	*p=GetEntryPoint()->CreateDirectComm(GetMainWidget());
				SetDirectCommBase(p);
			}
		}
	}
	return true;
}

bool    LayersBase::DeliverAllCommsForDirectComm(int WaitingMiliSec)
{
	bool	Ret=true;
	if(GetEntryPoint()->IsMasterPC()==true && GetParamComm()->GetConnectedPCNumb()>0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendAllComms	RCmd(this,"ANY","ANY",page);
			RCmd.Initial();
			RCmd.Data.WaitingTimeToConnect=WaitingMiliSec;
			if(RCmd.SendOnly(page,0,WaitingMiliSec)==false)
				Ret=false;
		}
	}
	return Ret;
}


void    LayersBase::CheckSlave(NPListPack<ErrorInfoList>  &ErrorPages)
{
	int	tmpMaxWaitingCommMilisec=GetParamGlobal()->MaxWaitingCommMilisec;
	if(GetParamGlobal()->MaxWaitingCommMilisec<2000){
		GetParamGlobal()->MaxWaitingCommMilisec=2000;
	}
	if(GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCheckSlave	SCmd(this,"ANY","ANY",page);
			GUICmdAckCheckSlave	RCmd(this,"ANY","ANY",page);
			if(SCmd.Send(page,0,RCmd)==false){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages.append("No response");
				a->ReqReboot=false;
				ErrorPages.AppendList(a);
			}
			else if(RCmd.Ret==GUICmdAckCheckSlave::_ReqReboot){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages=RCmd.Messages;
				a->ReqReboot=true;
				ErrorPages.AppendList(a);
			}
			else if(RCmd.Ret==GUICmdAckCheckSlave::_ErrorOccurs){
				ErrorInfoList	*a=new ErrorInfoList();
				a->Page	=page;
				a->Messages=RCmd.Messages;
				a->ReqReboot=false;
				ErrorPages.AppendList(a);
			}
		}
	}
	GetParamGlobal()->MaxWaitingCommMilisec=tmpMaxWaitingCommMilisec;
}

bool	LayersBase::CheckInstalledAlgorithm(RootNameListContainer &FromGUI,RootNameListContainer &LackOfAlgorithm)
{
	return GetLogicDLLBase()->CheckInstalledAlgorithm(FromGUI,LackOfAlgorithm);
}

bool	LayersBase::SendInfo(int globalPage)
{
	return true;
}


void    LayersBase::MakeAlgorithmBlobList(ExcludedListPack &List)
{
	GetLogicDLLBase()->MakeFieldList(List);
}

void    LayersBase::InitialAllocExecuterDim(void)
{
	if(AllocExecuterDim!=GetParamGlobal()->NGCacheNumb){
		if(ExecuterDim!=NULL){
			for(int i=0;i<AllocExecuterDim;i++){
				delete	ExecuterDim[i];
			}
			delete	[]ExecuterDim;
		}
		AllocExecuterDim=GetParamGlobal()->NGCacheNumb;
		ExecuterDim=new DataInExecuter*[AllocExecuterDim];
		for(int i=0;i<AllocExecuterDim;i++){
			ExecuterDim[i]=new DataInExecuter(i,this);
		}
	}
}

void    LayersBase::InitialResult(void)
{
	if(GetResultThread()!=NULL){
		GetResultThread()->Initial(EntryPoint);

		GetResultThread()->SetMastered(GetParamComm()->Mastered);
		if(GetResultThread()->isRunning()==false && GetInsideLearningEditor()==false){
			GetResultThread()->start();
		}
	}
	if(GetResultDLLBase()!=NULL){
		GetResultDLLBase()->RemoveAll();
		/*
		if(GetParamGlobal()->ResultDLLPathName.isEmpty()==false){
			GetResultDLLBase()->SearchAddDLL(GetParamGlobal()->ResultDLLPathName);
		}
		*/
		if(GetParamGlobal()->ResultDLLFileName.isEmpty()==false){
			GetResultDLLBase()->LoadDLL(GetParamGlobal()->ResultDLLFileName);
		}
	}
	if(GetLotBase()!=NULL){
		GetLotBase()->Initial();
	}
}

void    LayersBase::PrepareResult(void)
{
	GetResultDLLBase()->Prepare();
}

bool	LayersBase::CheckResultDLL(void)
{
	if(GetResultDLLBase()!=NULL){
		if(GetParamGlobal()->ResultDLLFileName.isEmpty()==false){
			if(GetResultDLLBase()->IsEmpty()==true){
				return false;
			}
		}
	}
	return true;
}

void    LayersBase::InitialExecuter(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->SetCurrentResultForCalc(GetResultThread()->GetResult(i));
		ExecuterDim[i]->Initial();
	}
}
void    LayersBase::InitialArrangementDLL(void)
{
	GetArrangementDLLStock()->SearchAddDLL(GetParamGlobal()->ArrangementDLLPath);
}

bool    LayersBase::OpenDatabase(XUpdateDatabase &dbase)
{
	SetDatabase(&dbase.DBase);
	RootDBase=GetDatabaseLoader()->S_OpenDatabase(RootDBase);
	OriginalRootDBase=true;
	if(GetDatabaseLoader()->S_IsValidDatabase(RootDBase)==false){
		return false;
	}
	return true;
}
bool    LayersBase::CloseDatabase(void)
{
	if(RootDBase!=NULL && OriginalRootDBase==true){
		RootDBase=GetDatabaseLoader()->S_CloseDatabase(RootDBase);
	}
	return true;
}
void	LayersBase::SetDatabase(QSqlDatabase *dbase)
{
	RootDBase=dbase;
}

DataInPage *LayersBase::GetPageDataByPoint(int globalX ,int globalY)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int	x1,y1,x2,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<=x2) && (y1<=globalY) && (globalY<=y2)){
			return P;
		}
	}
	return NULL;
}


AlgorithmBase	*LayersBase::GetAlgorithmBase(const QString &_DLLRoot ,const QString &_DLLName)
{
	if(GetLogicDLLBase()==NULL){
		return NULL;
	}
	LogicDLL	*L=GetLogicDLLBase()->Search(_DLLRoot ,_DLLName);
	if(L!=NULL){
		return L->GetInstance();
	}
	return NULL;
}
LogicDLL		*LayersBase::GetAlgorithmDLL(const QString &_DLLRoot ,const QString &_DLLName)
{
	if(GetLogicDLLBase()==NULL){
		return NULL;
	}
	LogicDLL	*L=GetLogicDLLBase()->Search(_DLLRoot ,_DLLName);
	return L;
}

GUIFormBase	*LayersBase::FindByName(const QString &FormRoot ,const QString &FormName ,const QString &InstName)
{
	if(GetGUIInstancePack()!=NULL){
		GUIFormBase	*hg=GetGUIInstancePack()->FindByName(FormRoot ,FormName ,InstName);
		if(hg!=NULL){
			return hg;
		}

		if(GetEntryPoint()!=NULL){
			for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
				GUIFormBase	*h=c->FindByName(FormRoot ,FormName ,InstName);
				if(h!=NULL){
					return h;
				}
			}
		}
	}
	return NULL;
}
GUIFormBase	*LayersBase::FindByName(const QString &InstName)
{
	if(GetGUIInstancePack()!=NULL){
		GUIFormBase	*hg=GetGUIInstancePack()->FindByName(InstName);
		if(hg!=NULL){
			return hg;
		}

		if(GetEntryPoint()!=NULL){
			for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
				GUIFormBase	*h=c->FindByName(InstName);
				if(h!=NULL){
					return h;
				}
			}
		}
	}
	return NULL;
}
void	LayersBase::SetAreaSizeInImagePanel(bool DrawWholeMode)
{
	if(GetEntryPoint()!=NULL){
		for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
			c->SetAreaSizeInImagePanel(DrawWholeMode);
		}
	}
}
int LayersBase::EnumGUIInst(const QString &FormRoot ,const QString &FormName ,GUIFormBase *Ret[] ,int MaxRet)
{
	int	RetN=0;
	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		int	n=cg->EnumGUIInst(FormRoot ,FormName ,&Ret[RetN] ,MaxRet-RetN);
		RetN+=n;
		return RetN;
	}
	/*
	for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
		int	n=c->EnumGUIInst(FormRoot ,FormName ,&Ret[RetN] ,MaxRet-RetN);
		RetN+=n;
	}
	return RetN;
	*/
	return 0;
}

int LayersBase::EnumGUI(GUIFormBase *Ret[] ,int MaxRet)
{
	int	RetN=0;
	GUIInstancePack *cg=GetGUIInstancePack();
	if(cg!=NULL){
		for(GUIItemInstance *g=cg->NPListPack<GUIItemInstance>::GetFirst();g!=NULL;g=g->GetNext()){
			GUIFormBase	*f=g->GetForm();
			if(f!=NULL && RetN<MaxRet){
				Ret[RetN]=f;
				RetN++;
			}
		}
	}
	return RetN;
}
bool	LayersBase::ChangeGUI(const QString &GUIFileData)
{
	return true;
}

bool	LayersBase::IsValidDatabase(void)
{
	return GetDatabaseLoader()->S_IsValidDatabase(RootDBase);
}


void    LayersBase::Release(void)
{
	if(LogicDLLBase!=NULL){
		delete	LogicDLLBase;
		LogicDLLBase=NULL;
	}
	if(ResultDLLBase!=NULL){
		delete	ResultDLLBase;
		ResultDLLBase=NULL;
	}

	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			PageDataPhase[i]->Release();
		}
		delete	[]PageDataPhase;
		PageDataPhase=NULL;
	}
	PageData=NULL;

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}
}

void    LayersBase::ReleaseBeforeReleasingGUI(void)
{
	if(MainWidget!=NULL){
		disconnect(MainWidget,SLOT(SlotCommand(int)));
		disconnect(MainWidget,SLOT(SlotWroteSlave(XDateTime)));
		disconnect(MainWidget,SLOT(SlotChangeLotInfo(int))	);
	}
	for(int phase=0;phase<AllocatedPhaseNumb;phase++){
		for(int page=0;page<GetPageNumb();page++){
			GetPageDataPhase(phase)->GetPageData(page)->ReleaseInside();
		}
	}

	if(ParamGUIData!=NULL){
		delete	ParamGUIData	;
		ParamGUIData=NULL;
	}
	if(OperationLoggerData!=NULL){
		delete	OperationLoggerData;
		OperationLoggerData=NULL;
	}
	//delete	PacketWritternResult;
	PacketWritternResult=NULL;

	if(RCmdBase!=NULL){
		ReceiverList	*r;
		while((r=RCmdBase->GetFirst())!=NULL){
			if(r->Point!=NULL){
				GUICmdPacketBase	*Point=r->Point;
				if(RemovePacket(Point)==false){
					RCmdBase->RemoveList(r);
					if(Point->GetGlobalPage()>=0){
						delete	Point;
					}
					delete	r;
				}
				else{
					if(Point->GlobalPage>=0){
						delete	Point;
					}
				}
			}
		}
		delete	RCmdBase		;
		RCmdBase			=NULL;
	}
	if(RCmdDirectCommBase!=NULL){
		DirectCommReceiverList	*r;
		while((r=RCmdDirectCommBase->GetFirst())!=NULL){
			DirectCommPacketBase	*Point=r->Point;
			if(r->Point!=NULL){
				if(RemoveDirectCommPacket(Point)==false){
					RCmdDirectCommBase->RemoveList(r);
					if(Point->GetGlobalPageFrom()>=0){
						delete	Point;
					}
					delete	r;
				}
				else{
					if(Point->GetGlobalPageFrom()>=0){
						delete	Point;
					}
				}
			}
		}
		delete	RCmdDirectCommBase;
		RCmdDirectCommBase	=NULL;
	}
	if(RIntegrationCmdBase!=NULL){
		ReceiverList	*r;
		//_heapchk();
		while((r=RIntegrationCmdBase->GetFirst())!=NULL){
			if(r->IntegrationPoint!=NULL){
				IntegrationCmdPacketBase	*Point=r->IntegrationPoint;
				if(RemoveIntegrationPacket(Point)==false){
					RIntegrationCmdBase->RemoveList(r);
					if(Point->GetSlaveNo()>=0){
						delete	Point;
					}
					delete	r;
				}
				else{
					if(Point->GetSlaveNo()>=0){
						delete	Point;
					}
				}
			}
		}
		delete	RIntegrationCmdBase		;
		RIntegrationCmdBase			=NULL;
	}
	if(ListOfQImageStockerData!=NULL){
		delete	ListOfQImageStockerData;
		ListOfQImageStockerData=NULL;
	}
}
void    LayersBase::ReleaseAll(void)
{
	UndoDataStocker.RemoveAll();
	RedoDataStocker.RemoveAll();
	CreateAlgorithmPointer();


	if(ResultThread!=NULL){
		//ResultThread.terminate();
		ResultThread->SetCmdFinish(true);
		ResultThread->wait(5000);
		//if(ResultDLLBase!=NULL)
		//	ResultDLLBase->Release();
		delete	ResultThread;
		ResultThread=NULL;
	}

	if(MainWidget!=NULL){
		MainWidget->deleteLater();
		MainWidget=NULL;
	}

	GUICmdContainer.RemoveAll();

	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			PageDataPhase[i]->Release();
		}
		delete	[]PageDataPhase;
		PageDataPhase=NULL;
	}
	PageData=NULL;

	if(Parent==NULL){
		if(ShrinkingPackContainerInstance!=NULL){
			delete	ShrinkingPackContainerInstance;
			ShrinkingPackContainerInstance=NULL;
		}
	}
	else{
		ShrinkingPackContainerInstance=NULL;
	}

	if(DrawPageIndex!=NULL){
		delete	[]DrawPageIndex;
		DrawPageIndex=NULL;
	}

	if(MTransfer!=NULL){
		delete	MTransfer;
		MTransfer=NULL;
	}

	//_CrtCheckMemory();
	if(ErrorContainer!=NULL){
		delete	ErrorContainer;
		ErrorContainer=NULL;
	}

	//AllocatedPageNumb=0;
	if(LogicDLLBase!=NULL){
		delete	LogicDLLBase;
		LogicDLLBase=NULL;
	}

	if(ResultDLLBase!=NULL){
		delete	ResultDLLBase;
		ResultDLLBase=NULL;
	}

	if(PieceStock!=NULL){
		delete	PieceStock;
		PieceStock=NULL;
	}

	//CloseDatabase();
	if(DBLoader!=NULL){
		DBLoader->Release();
		delete	DBLoader;
		DBLoader=NULL;
	}

	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			delete	ExecuterDim[i];
		}
		delete	[]ExecuterDim;
		ExecuterDim=NULL;
	}

	if(ParamGlobalData!=NULL){
		delete	ParamGlobalData	;
		ParamGlobalData=NULL;
	}
	if(ParamCommData!=NULL){
		delete	ParamCommData	;
		ParamCommData=NULL;
	}

	if(AckFlag!=NULL){
		delete	[]AckFlag			;
		AckFlag=NULL;
	}
	if(LightBase!=NULL){
		delete	LightBase		;
		LightBase=NULL;
	}
	if(LocalParamStocker!=NULL){
		delete	LocalParamStocker;
		LocalParamStocker=NULL;
	}
	if(OnProcessing!=NULL){
		delete	OnProcessing;
		OnProcessing=NULL;
	}
	if(FilterBank!=NULL){
		delete	FilterBank;
		FilterBank=NULL;
	}
	if(OutlineOffsetWriter!=NULL){
		delete	OutlineOffsetWriter;
		OutlineOffsetWriter=NULL;
	}
	if(LogoStockerInstance!=NULL){
		delete	LogoStockerInstance;
		LogoStockerInstance=NULL;
	}
	if(AnyData!=NULL){
		delete	AnyData;
		AnyData=NULL;
	}
	if(GeneralStockerData!=NULL){
		delete	GeneralStockerData;
		GeneralStockerData=NULL;
	}
	if(LearningRegData!=NULL){
		delete	LearningRegData;
		LearningRegData=NULL;
	}
	if(GlobalOffset!=NULL){
		delete	[]GlobalOffset;
		GlobalOffset=NULL;
	}
	if(SendingData!=NULL){
		delete	[]SendingData;
		SendingData=NULL;
	}
	if(IntegrationSendingData!=NULL){
		delete	[]IntegrationSendingData;
		IntegrationSendingData=NULL;
	}
	if(PasswordHolder!=NULL){
		delete	PasswordHolder;
		PasswordHolder=NULL;
	}
	if(SyncGUIData!=NULL){
		delete	SyncGUIData;
		SyncGUIData=NULL;
	}
	if(StatusControllerData!=NULL){
		delete	StatusControllerData;
		StatusControllerData=NULL;
	}
	if(AlgoDLLContPointer!=NULL){
		delete	AlgoDLLContPointer;
		AlgoDLLContPointer=NULL;
	}
	if(LearningRegisterData!=NULL){
		delete	LearningRegisterData;
		LearningRegisterData=NULL;
	}
	if(LotInfo!=NULL){
		delete	LotInfo;
		LotInfo=NULL;
	}
	if(InstShowLoadingDLLForm!=NULL){
		delete	InstShowLoadingDLLForm;
		InstShowLoadingDLLForm=NULL;
	}
	if(Parent==NULL){
		if(LanguagePackageData!=NULL){
			delete	LanguagePackageData;
			LanguagePackageData=NULL;
		}
	}
	else{
		LanguagePackageData=NULL;
	}
	if(DataOfShareMasterContainer!=NULL){
		delete	DataOfShareMasterContainer;
		DataOfShareMasterContainer	=NULL;
	}

	//delete	RootDBase;
	if(PasteListMatrixContainerBase!=NULL){
		delete	PasteListMatrixContainerBase;
		PasteListMatrixContainerBase=NULL;
	}

	if(PrinterClassPackData!=NULL){
		delete	PrinterClassPackData;
		PrinterClassPackData=NULL;
	}
	if(FRegistry!=NULL){
		delete	FRegistry;
		FRegistry=NULL;
	}
	/*
	DirectCommBase is allocated in XGUIExe.cpp as global param, and released in global
	if(DirectCommBase!=NULL){
		delete	DirectCommBase;
		DirectCommBase=NULL;
	}
	*/
	if(IntegrationBaseData!=NULL){
		delete	IntegrationBaseData;
		IntegrationBaseData=NULL;
	}
	if(LensWindow!=NULL){
		delete	LensWindow;
		LensWindow=NULL;
	}
	if(ZoneWindow!=NULL){
		delete	ZoneWindow;
		ZoneWindow=NULL;
	}
	if(ResizeData!=NULL){
		delete	ResizeData;
		ResizeData=NULL;
	}
	if(ResultAnalizerDLLPack!=NULL){
		delete	ResultAnalizerDLLPack;
		ResultAnalizerDLLPack=NULL;
	}
	if(ResultAnalizerItemBasePack!=NULL){
		delete	ResultAnalizerItemBasePack;
		ResultAnalizerItemBasePack=NULL;
	}
	CurrentZoneWindowComponent=NULL;
}

bool	LayersBase::SetLanguageCode(int _LanguageCode,bool EnableAlgorithm,bool EnableGUI,bool EnableGeneralStocker)
{
	LanguagePackageData->SetLanguage(_LanguageCode);
	LangLibSolver.SetLanguage(GetLanguagePackageData(),LanguagePackageData->GetLanguageCode());
	if(EnableAlgorithm==true){
		if(GetLogicDLLBase()!=NULL && GetLogicDLLBase()->SetLanguageCode(LanguagePackageData->GetLanguageCode())==false){
			return false;
		}
	}
	if(EnableGUI==true){
		if(GetEntryPoint()!=NULL){
			GetEntryPoint()->SetLanguageCode(LanguagePackageData->GetLanguageCode());
		}
	}
	if(EnableGeneralStocker==true){
		if(GetGeneralStocker()!=NULL){
			GetGeneralStocker()->SetLanguage(LanguagePackageData->GetLanguageCode());
		}
	}
	return true;
}
int		LayersBase::GetLanguageCode(void)
{
	return LanguagePackageData->GetLanguageCode();
}
bool	LayersBase::SetLanguageCode(bool AlgorithmMode,bool GUIMode ,bool GeneralStockerMode)
{
	int	LanguageCode=GetFRegistry()->LoadRegInt("Language",0);
	return SetLanguageCode(LanguageCode,AlgorithmMode,GUIMode ,GeneralStockerMode);
}
bool	LayersBase::LoadLanguageSolution(const QString &LNGFileName)
{
	LocalLanguageSolutionFileName=LNGFileName;
	return LanguagePackageData->LoadSolutionFromFile(LNGFileName);
}

void	LayersBase::SetDefaultCodec(void)
{
	LanguagePackageData->SetDefaultCodec();
}

void	LayersBase::RestoreCodec(void)
{
	LanguagePackageData->RestoreCodec();
}

int		LayersBase::GetGlobalPage(int globalX ,int globalY)
{
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		if(DefaultArrangeMode==false){
			for(int i=0;i<GetPageNumb();i++){
				int x1 ,y1 ,x2 ,y2;
				if((*PageData)[i]!=NULL){
					(*PageData)[i]->GetArea(x1 ,y1 ,x2 ,y2);
					if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
						return GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),i);
						//return i;
					}
				}
			}
		}
		else{
			for(int i=0;i<GetPageNumb();i++){
				int	x1=GetParamGlobal()->GetDotPerLine()*i;
				int	y1=0;
				int	x2=GetParamGlobal()->GetDotPerLine()*(i+1)-1;
				int	y2=GetParamGlobal()->GetMaxLines();
				if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
					return i;
				}
			}
		}
	}
	else{
		for(int i=0;i<GlobalPageNumb;i++){
			int x1 ,y1 ,x2 ,y2;
			XYData	XY=GlobalOffset[i].OutlineOffset;
			if((XY.x<=globalX) && (globalX<XY.x+GetDotPerLine()) && (XY.y<=globalY) && (globalY<XY.y+GetMaxLines())){
				return i;
			}
		}
	}
	return -1;
}

void	LayersBase::GetGlobalPage(int globalX1 ,int globalY1 ,int globalX2 ,int globalY2 ,IntList &PageList)
{
	PageList.RemoveAll();
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int Lx1 ,Ly1 ,Lx2 ,Ly2;
			P->GetArea(Lx1 ,Ly1 ,Lx2 ,Ly2);
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				int gpage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				PageList.AppendList(new IntClass(gpage));
			}
		}
	}
	else{
		for(int i=0;i<GlobalPageNumb;i++){
			int x1 ,y1 ,x2 ,y2;
			XYData	XY=GlobalOffset[i].OutlineOffset;
			int	Lx1=XY.x;
			int	Ly1=XY.y;
			int	Lx2=XY.x+GetDotPerLine();
			int	Ly2=XY.y+GetMaxLines();
			if(CheckOverlapRectRect(globalX1 ,globalY1 ,globalX2 ,globalY2
				,Lx1 ,Ly1 ,Lx2 ,Ly2)==true){
				PageList.AppendList(new IntClass(i));
			}
		}
	}
}


void	LayersBase::BroadcastMachineID(void)
{
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendMachineID	RCmd(this,"ANY","ANY",page);
			RCmd.MachineID=GetMachineID();
			RCmd.Send(NULL,page,0);
		}
	}
}

bool	LayersBase::MachineIDExists(void)
{
	if(GetDatabaseLoader()!=NULL){
		return GetDatabaseLoader()->G_MachineIDExists(GetDatabase() ,GetMachineID());
	}
	return false;
}



bool    LayersBase::SavePixWithAlgorithm(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqPixWithAlgorithm	RCmd(this,"ANY","ANY",page);
		GUICmdAckPixWithAlgorithm	ACmd(this,"ANY","ANY",page);
		RCmd.Send(page,0,ACmd);
		int64	L=ACmd.Buff.size();
		if(::Save(f,L)==false){
			return false;
		}
		if(f->write(ACmd.Buff)!=L){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadPixWithAlgorithm(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdLoadPixWithAlgorithm	RCmd(this,"ANY","ANY",page);
		int64	L;
		if(::Load(f,L)==false){
			return false;
		}
		RCmd.Buff=f->read(L);
		if(RCmd.Buff.size()!=L){
			return false;
		}
		RCmd.Send(NULL,page,0);
	}
	return true;
}

bool    LayersBase::SaveResult(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqResultInfo	RCmd(this,"ANY","ANY",page);
		GUICmdAckResultInfo	ACmd(this,"ANY","ANY",page);
		if(RCmd.Send(page,0,ACmd)==true){
			int64	L=ACmd.Buff.size();
			if(::Save(f,L)==false){
				return false;
			}
			if(f->write(ACmd.Buff)!=L){
				return false;
			}
		}
	}
	return true;
}

bool    LayersBase::LoadResult(QIODevice *f)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdLoadResultInfo	RCmd(this,"ANY","ANY",page);
		int64	L;
		if(::Load(f,L)==false){
			return false;
		}
		RCmd.Buff=f->read(L);
		if(RCmd.Buff.size()!=L){
			return false;
		}
		RCmd.Send(NULL,page,0);
	}
	return true;
}

bool	LayersBase::CopyImage(int sourceImageType ,int destImageType)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdCopyImage	RCmd(this,"ANY","ANY",page);
		RCmd.srcImageType=sourceImageType;
		RCmd.dstImageType=destImageType;
		if(RCmd.Send(NULL,page,0)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::GetArea(int &x1 ,int &y1 ,int &x2 ,int &y2)
{
	x1=  99999999;
	y1=  99999999;
	x2= -99999999;
	y2= -99999999;
	for(int L=0;L<GetPageNumb();L++){
		int	px1,py1,px2,py2;
		if(IsValidData()==true){
			GetPageData(L)->GetArea(px1,py1,px2,py2);
			x1=min(x1,px1);
			y1=min(y1,py1);
			x2=max(x2,px2);
			y2=max(y2,py2);
		}
	}
}

void	LayersBase::ClearInspectID(void)
{	
	GetResultThread()->FlushWaitForWrite();
	_CurrentInspectID=_LastInspectID=GetParamGlobal()->TopOfID;
}
	
void	LayersBase::SetCurrentInspectID(int64 id)	
{	
	//GetResultThread()->FlushWaitForWrite();
	_LastInspectID=_CurrentInspectID;	
	_CurrentInspectID=id;			
}

void	LayersBase::SetForceChangedInspectID(void)
{	
	static	bool	ReEntrant=false;
	if(ReEntrant==false){
		ReEntrant=true;
		GetResultThread()->FlushWaitForWrite();
		ForceChangedInspectID=true;		
		if(GetParamComm()->Mastered==true){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdSetForceChangedInspectID	RCmd(this,"ANY","ANY",page);
				RCmd.Send(NULL,page,0);
			}
		}
		ReEntrant=false;
	}
}

bool    LayersBase::SaveAttrDefault(void)
{
	if(GetParamGlobal()->WriteEnableToDefaultFile()==true){
		QFile	f(GetParamGlobal()->LayerDefaultFileName);
		if(f.open(QIODevice::WriteOnly)==false){
			return false;
		}
		if(SaveAttr(&f)==false){
			return false;
		}
		//if(GetParamComm()->Mastered==true){
		//	if(SaveOutlineOffsetForDatabase()==false){
		//		return false;
		//	}
		//}
	}
	return true;
}
bool    LayersBase::LoadAttrDefault(void)
{
	QFile	f(GetParamGlobal()->LayerDefaultFileName);
	if(f.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(LoadAttr(&f)==false){
		return false;
	}
	return true;
}

bool    LayersBase::SaveAttr(QIODevice *f)
{
	int32	ID=0x5eea;
	if(::Save(f,ID)==false){
		return false;
	}
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	int32	PageNumb=GetPageNumb();
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int page=0;page<PageNumb;page++){
		DataInPage *p=GetPageData(page);
		if(p->SaveAttr(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadAttr(QIODevice *f)
{
	int32	ID;
	if(::Load(f,ID)==false){
		return false;
	}
	if(ID!=0x5eea){
		return false;
	}
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->LoadAttr(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::SaveImages(QIODevice *f)
{
	int32	PageNumb=GetPageNumb();
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int page=0;page<PageNumb;page++){
		DataInPage *p=GetPageData(page);
		if(p->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool    LayersBase::LoadImages(QIODevice *f)
{
	int32	iPageNumb;
	if(::Load(f,iPageNumb)==false){
		return false;
	}
	for(int page=0;(page<GetPageNumb()) && (page<iPageNumb);page++){
		DataInPage *p=GetPageData(page);
		if(p->Load(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::SaveHeader(QIODevice *f)
{
	if(::Save(f,MasterCode	)==false){
		return false;
	}
	if(::Save(f,MasterName)==false){
		return false;
	}
	if(::Save(f,Remark)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,RegTime)==false){
		return false;
	}
	if(::Save(f,WorkerID)==false){
		return false;
	}
	if(::Save(f,WorkerName)==false){
		return false;
	}
	if(::Save(f,Version)==false){
		return false;
	}
	if(::Save(f,LastEditTime)==false){
		return false;
	}
	if(::Save(f,CategoryID)==false){
		return false;
	}
	return true;
}
bool    LayersBase::LoadHeader(QIODevice *f)
{
	if(::Load(f,MasterCode	)==false){
		return false;
	}
	if(::Load(f,MasterName)==false){
		return false;
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}
	if(::Load(f,RegTime)==false){
		return false;
	}
	if(::Load(f,WorkerID)==false){
		return false;
	}
	if(::Load(f,WorkerName)==false){
		return false;
	}
	if(::Load(f,Version)==false){
		return false;
	}
	if(::Load(f,LastEditTime)==false){
		return false;
	}
	if(::Load(f,CategoryID)==false){
		return false;
	}
	return true;
}
bool    LayersBase::SaveRegulation(QIODevice *f)
{
	if(::Save(f,(int32)GetPhaseNumb())==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->SaveRegulation(f)==false){
			return false;
		}
	}
	return true;
}

bool    LayersBase::LoadRegulation(QIODevice *f)
{
	int32	iPhaseNumb;
	if(::Load(f,iPhaseNumb)==false)
		return false;
	for(int phase=0;phase<GetPhaseNumb() && phase<iPhaseNumb;phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->LoadRegulation(f)==false){
			return false;
		}
	}
	return true;
}

bool	LayersBase::AddMasterFieldData(const QString &FieldName, const QVariant &data)
{
	if(IsDatabaseOk()==true){
		return GetDatabaseLoader()->G_SQLAddMasterFieldData(GetDatabase() ,MasterCode ,FieldName, data);
	}
	return false;
}
bool	LayersBase::LoadMasterFieldData(const QString &FieldName,QVariant &data)
{
	if(IsDatabaseOk()==true){
		return GetDatabaseLoader()->G_SQLLoadMasterFieldData(GetDatabase() ,MasterCode ,FieldName, data);
	}
	return false;
}


bool    LayersBase::SaveAllAlgorithm(QIODevice *f)
{
	return GetLogicDLLBase()->Save(f);
}
bool    LayersBase::LoadAllAlgorithm(QIODevice *f)
{
	return GetLogicDLLBase()->Load(f);
}

QString	LayersBase::GetColorString(int gx ,int gy)
{
	QString	ret;
	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*Lp=GetPageData(page);
		for(int layer=0;layer<Lp->GetLayerNumb();layer++){
			DataInLayer	*Ly=Lp->GetLayerData(layer);
			int	px1,py1,px2,py2;
			Ly->GetArea(px1,py1,px2,py2);
			if((px1<=gx) && (gx<px2) && (py1<=gy) && (gy<py2) && (0<=gy) && (gy<Ly->GetMasterBuff().GetHeight())){
				int	c=Ly->GetMasterBuff().GetY(gy)[gx];
				ret = ret + QString::number(c) + QString(" ");
			}
		}
	}
	return(ret);
}
void	LayersBase::GetGlobalPage(int globalX ,int globalY,IntList &PageList)
{
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int	LocalX=globalX-P->GetOutlineOffset()->x;
			int	LocalY=globalY-P->GetOutlineOffset()->y;
			if(0<=LocalX && LocalX<GetDotPerLine() && 0<=LocalY && LocalY<GetMaxLines()){
				PageList.AppendList(new IntClass(page));
			}
		}
	}
	else{
		for(int page=0;page<GlobalPageNumb;page++){
			int	LocalX=globalX-GlobalOffset[page].OutlineOffset.x;
			int	LocalY=globalY-GlobalOffset[page].OutlineOffset.y;
			if(0<=LocalX && LocalX<GetDotPerLine() && 0<=LocalY && LocalY<GetMaxLines()){
				PageList.AppendList(new IntClass(page));
			}
		}
	}
}

int		LayersBase::GetLocalPageFromArea(FlexArea &Area ,IntList &List)
{
	int	ret=0;
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			List.AppendList(new IntClass(page));
			ret++;
		}
	}
	return ret;
}

int		LayersBase::GetLocalPageFromArea(DisplayImage *p ,FlexArea &Area ,IntList &List)
{
	int	ret=0;
	if(p->ModeShowOnlyTopTurn==false){
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=GetPageData(page);
			int x1 ,y1 ,x2 ,y2;
			P->GetArea(x1 ,y1 ,x2 ,y2);
			if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				List.AppendList(new IntClass(page));
				ret++;
			}
		}
	}
	else{
		int	page=GetDrawturn(0)->GetPage();
			
		DataInPage *P=GetPageData(page);
		if(P!=NULL){
			int x1 ,y1 ,x2 ,y2;
			P->GetArea(x1 ,y1 ,x2 ,y2);
			if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
				List.AppendList(new IntClass(page));
				ret++;
			}
		}
	}
	return ret;
}

int		LayersBase::GetLocalPageFromVector(VectorLineBase *v,IntList &PageList)
{
	int	ret=0;
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(v->CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			PageList.AppendList(new IntClass(page));
			ret++;
		}
	}
	return ret;
}

int		LayersBase::GetLocalPageFromAreaFromDrawingTop(FlexArea &Area)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if(Area.CheckOverlapRectangle(x1 ,y1 ,x2 ,y2)==true){
			return P->GetPage();
		}
	}
	return -1;
}

int		LayersBase::GetLocalPageFromAreaFromDrawingTop(int globalX ,int globalY)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetDrawturn(page);
		int x1 ,y1 ,x2 ,y2;
		P->GetArea(x1 ,y1 ,x2 ,y2);
		if((x1<=globalX) && (globalX<x2) && (y1<=globalY) && (globalY<y2)){
			return P->GetPage();
		}
	}
	return -1;
}

	
int		LayersBase::GetLocalPageFromGlobal	(int globalPage)
{
	return GetParamComm()->GetLocalPageFromGlobal(*GetParamGlobal(),globalPage);
}
int		LayersBase::GetGlobalPageFromLocal	(int localPage)
{
	return GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage);
}

int		LayersBase::GetLocalMatrixFromGlobal(int globalX ,int globalY ,int &localX ,int &localY)
{	
	if((GetEntryPoint()!=NULL) && (GetEntryPoint()->IsMasterPC()==true)){
		int	gpage=GetGlobalPage(globalX ,globalY);
		int	lPage=GetLocalPageFromGlobal(gpage);
		if((lPage<0) || (lPage>=GetPageNumb())){
			XYData	*p=GetGlobalOutlineOffset(gpage);
			if(p!=NULL){
				localX=globalX - p->x;
				localY=globalY - p->y;
				return gpage;
			}
		}
		else{
			GetPageData(lPage)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
			return gpage;
		}
	}
	else{
		for(int page=0;page<GlobalPageNumb;page++){
			int	LocalX=globalX-GlobalOffset[page].OutlineOffset.x;
			int	LocalY=globalY-GlobalOffset[page].OutlineOffset.y;
			if(0<=LocalX && LocalX<GetDotPerLine() && 0<=LocalY && LocalY<GetMaxLines()){
				localX=LocalX;
				localY=LocalY;
				return page;
			}
		}
	}
	return -1;
}
void	LayersBase::GetGlobalMatrixFromLocal(int localPage ,int localX ,int localY ,int &globalX ,int &globalY)
{
	int	gpage=GetGlobalPageFromLocal(localPage);
	XYData	*p=GetGlobalOutlineOffset(gpage);
	if(p!=NULL){
		globalX=localX+p->x;
		globalY=localY+p->y;
	}
}
bool	LayersBase::GetRealMatrixFromGlobal(int globalX ,int globalY ,double &realX ,double &realY)
{
	int		localX ,localY;
	int	Page=GetLocalMatrixFromGlobal(globalX ,globalY ,localX ,localY);
	if(Page<0 || GetPageNumb()<=Page)
		return false;
	DataInPage	*P=GetPageData(Page);
	if(P->TransformImageToReal(localX ,localY,realX ,realY)==false){
		realX=((double)localX)/((double)GetParamGlobal()->ResolutionXNano)/1000000.0;
		realY=((double)localY)/((double)GetParamGlobal()->ResolutionYNano)/1000000.0;
	}
	return true;
}

XYData	*LayersBase::GetGlobalOutlineOffset(int globalpage)
{	
	static	XYData	_XYData;
	if(GlobalOffset==NULL || globalpage<0 || globalpage>=GlobalPageNumb){
		_XYData.x=0;
		_XYData.y=0;
		return &_XYData;
	}
	return &GlobalOffset[globalpage].OutlineOffset;	
}

DataInExecuter	*LayersBase::GetExecuter(const XDateTime &Key)
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetResultInspection()->GetStartTimeForInspection()==Key){
			return ExecuterDim[i];
		}
	}
	return NULL;
}
DataInExecuter	*LayersBase::GetExecuter(ResultInspection *Res)
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetResultInspection()==Res){
			return ExecuterDim[i];
		}
	}
	return NULL;
}
void	LayersBase::ClearAllReceivedResultCounts(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->ClearReceivedResultCounts();
	}
}

void	LayersBase::PushExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->PushState();
	}
}
void	LayersBase::PopExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->PopState();
	}
}

ExeResult	LayersBase::ExecuteInitialAfterEdit	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	for(int p=0;p<AllocExecuterDim;p++){
		ExecuterDim[p]->ExecuteInitialAfterEditLoop(p);
	}
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=ExecuterDim[CurrentCalcPoint]->ExecuteInitialAfterEdit(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);
	}
	if(ResultDLLBase!=NULL){
		ResultDLLBase->ExecuteInitialAfterEdit(CurrentCalcPoint,&GetCurrentResultForCalc());
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->SetEdited(false);
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteInitialAfterEdit(CurrentCalcPoint);
	}

	return Ret;
}
ExeResult	LayersBase::ExecuteStartByScanOnly	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteStartByScanOnly(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);
	}
	if(ResultDLLBase!=NULL){
		ResultDLLBase->ExecuteStartByInspection(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
	}

	return Ret;
}
ExeResult	LayersBase::ExecuteStartByInspection(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	LastCurrentCalcPoint=CurrentCalcPoint;
	if(GetParamGlobal()->AllocateTargetTRBuff==true){
		CopyTargetToTransposition();
	}
	int	tCurrentCalcPoint=CurrentCalcPoint;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteStartByInspection(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecuteStartByInspection(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
		if(ProgressStep==true){
			if(GetParamGlobal()->GetMaxScanStrategy()<=1
			|| GetParamGlobal()->GetMaxScanStrategy()<=(GetCurrentStrategicNumber()+1)){
				if((GetCurrentScanPhaseNumber()+1)>=GetParamGlobal()->GetScanPhaseCount()){
					CurrentCalcPoint++;
					if(CurrentCalcPoint>=AllocExecuterDim){
						CurrentCalcPoint=0;
					}
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteStartByInspection(tCurrentCalcPoint);
	}

	return Ret;
}
	
DataInExecuter::ExecutingState	LayersBase::GetCurrentStateInexecuter(int index)
{
	return ExecuterDim[index]->GetState();
}

int		LayersBase::GetIndexInCurrentStateExecuter(DataInExecuter::ExecutingState state)
{
	for(int i=0;i<AllocExecuterDim;i++){
		if(ExecuterDim[i]->GetState()==state){
			return i;
		}
	}
	return -1;
}
bool	LayersBase::SetCurrentStateInExecuter(int index ,DataInExecuter::ExecutingState state)
{
	if(0<=index && index<AllocExecuterDim){
		ExecuterDim[index]->ForceState(state);
		return true;
	}
	return false;
}

ExeResult	LayersBase::ExecutePreAlignment		(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteStartByInspection
			|| ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteStartByScanOnly){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePreAlignment	(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);

				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePreAlignment(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreAlignment(Point);
	}
	return Ret;
}
ExeResult	LayersBase::ExecuteAlignment		(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePreAlignment){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteAlignment(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);

				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteAlignment(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteAlignment(Point);
	}
	return Ret;
}
ExeResult	LayersBase::ExecutePreProcessing	(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteAlignment){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePreProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePreProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreProcessing(Point);
	}
	return Ret;
}
ExeResult	LayersBase::ExecuteProcessing		(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePreProcessing){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteProcessing(Point);
	}
	return Ret;
}
ExeResult	LayersBase::ExecuteProcessingRevived(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteProcessing){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecuteProcessingRevived(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecuteProcessingRevived(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteProcessingRevived(Point);
	}
	return Ret;
}
ExeResult	LayersBase::PretendFinishProcessing	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteStartByInspection
			|| ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteStartByScanOnly){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->PretendFinishProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
			}
		}
	}

	return Ret;
}

ExeResult	LayersBase::ExecutePostProcessing	(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	int	Point=0;
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecuteProcessingRevived
			|| ExecuterDim[i]->GetState()==DataInExecuter::NowExecuteStartByInspection){
				bool	RetryMode;
				do{
					RetryMode=false;
					ExeResult	RR=	ExecuterDim[i]->ExecutePostProcessing(i);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}while(RetryMode==true);
				Point=i;
				if(ResultDLLBase!=NULL){
					ResultDLLBase->ExecutePostProcessing(i,ExecuterDim[i]->GetResultInspection());
				}
			}
		}
		CurrentDrawPoint=LastCurrentCalcPoint;
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecutePostProcessing(Point);
	}
	return Ret;
}

ExeResult	LayersBase::ExecutePreScanning	(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecutePreScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecutePreScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecutePreScanning(CurrentCalcPoint);
	}
	return Ret;
}
ExeResult	LayersBase::ExecuteScanning	(bool ProgressStep)
{
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecuteScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecuteScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecuteScanning(CurrentCalcPoint);
	}
	return Ret;
}
ExeResult	LayersBase::ExecutePostScanning	(bool ProgressStep)
{	
	ExeResult	Ret=_ER_true;
	if(ExecuterDim!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			ExeResult	RR=	ExecuterDim[CurrentCalcPoint]->ExecutePostScanning(CurrentCalcPoint);
			if(RR==_ER_ReqRetryLater){
				RetryMode=true;
			}
			else{
				Ret=RR;
			}
		}while(RetryMode==true);

		if(ResultDLLBase!=NULL){
			ResultDLLBase->ExecutePostScanning(CurrentCalcPoint,ExecuterDim[CurrentCalcPoint]->GetResultInspection());
		}
	}
	if(GetEntryPoint()!=NULL && GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetEntryPoint()->GetExecuteInspect()->ExecutePostScanning(CurrentCalcPoint);
	}
	return Ret;
}

void	LayersBase::StandardManageResult(ResultInspection *Res)
{
	Res->BuildNGImages();
	//Res->BuildNGImages2();
}
bool	LayersBase::PutCurrentResult(void)
{
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetState()==DataInExecuter::FinExecutePostProcessing && ExecuterDim[i]->GetDonePutCurrentResult()==false){
				ExecuterDim[i]->PutCurrentResult();
				return true;
			}
		}
	}
	return false;
}

bool	LayersBase::PutForceResult(int InspectionID)
{
	if(ExecuterDim!=NULL){
		for(int i=0;i<AllocExecuterDim;i++){
			if(ExecuterDim[i]->GetResultInspection()->GetInspectionID()==InspectionID){
				ExecuterDim[i]->PutForceCurrentResult();
				return true;
			}
		}
	}
	return false;
}

ResultInspection	&LayersBase::GetCurrentResultForCalc(void)
{
	if(ExecuterDim!=NULL){
		ResultInspection	*Ret=ExecuterDim[LastCurrentCalcPoint]->GetResultInspection();
		return *Ret;
	}
	return *((ResultInspection *)NULL);
}
ResultInspection	&LayersBase::GetNextResultForCalc(void)
{
	if(ExecuterDim!=NULL){
		ResultInspection	*Ret=ExecuterDim[CurrentCalcPoint]->GetResultInspection();
		return *Ret;
	}
	return *((ResultInspection *)NULL);
}
void	LayersBase::RewindCalcPoint(void)
{
	CurrentCalcPoint=LastCurrentCalcPoint;
}

void	LayersBase::GetCalcPoint(int CPoints[])
{
	CPoints[0]=CurrentCalcPoint;
	CPoints[1]=CurrentDrawPoint;
	CPoints[2]=LastCurrentCalcPoint;
}
void	LayersBase::SetCalcPoint(int CPoints[])
{
	ExecuterDim[CPoints[0]]->ClearReceivedResultCounts();
	if(CPoints[0]+1>=AllocExecuterDim){
		ExecuterDim[0]->ClearReceivedResultCounts();
		}
	else{
		ExecuterDim[CPoints[0]+1]->ClearReceivedResultCounts();
	}

	CurrentCalcPoint	=CPoints[0];
	CurrentDrawPoint	=CPoints[1];
	LastCurrentCalcPoint=CPoints[2];
}
void	LayersBase::DecPoint(void)
{
	CurrentCalcPoint--;
	if(CurrentCalcPoint<0){
		CurrentCalcPoint=AllocExecuterDim-1;
	}
}

void	LayersBase::SetCurrentScanPhaseNumber(int n)
{	
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		CurrentScanPhaseNumber=n;
		IntList PhaseCodes;
		GetParamGlobal()->GetPhaseNumber(PhaseCodes ,CurrentScanPhaseNumber);
		if(PhaseCodes.GetCount()>0){
			int	Ph=PhaseCodes[0];
			SetCurrentPhase(Ph);
		}
	}
}
void	LayersBase::IncreaseCurrentScanPhaseNumber(void)
{
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		CurrentScanPhaseNumber++;
		if(CurrentScanPhaseNumber>=GetPhaseNumb()){
			CurrentScanPhaseNumber=0;
		}
	}
}

void	LayersBase::TF_SetCurrentScanPhaseNumber(int n)
{
	if(GetParamGlobal()->UseScanPhaseNumber==true){
		SetCurrentScanPhaseNumber(n);
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetGlobalPageFromLocal(page);
			GUICmdSetCurrentScanPhaseNumber	Cmd(this,"ANY","ANY",globalPage);
			Cmd.CurrentScanPhaseNumber=n;
			Cmd.Send(NULL,globalPage ,0);
		}
	}
}

void	LayersBase::GetCurrentPhaseFromScanPhase(IntList &PhaseCodes)
{
	PhaseCodes.RemoveAll();
	if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseCodes.Add(phase);
		}
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
		GetParamGlobal()->GetPhaseNumber(PhaseCodes ,CurrentScanPhaseNumber);
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteStartByInspection>=0){
		PhaseCodes.Add(GetParamGlobal()->ModePhaseExecuteStartByInspection);
	}
}

void	LayersBase::GetPhaseFromScanPhase(int ScanPhaseNumber ,IntList &PhaseCodes)
{
	GetParamGlobal()->GetPhaseNumber(PhaseCodes ,ScanPhaseNumber);
}

void	LayersBase::GetScanPhaseFromPhase(int phase ,int &RetScanPhaseNumber)
{
	GetParamGlobal()->GetScanPhaseFromPhase(phase ,RetScanPhaseNumber);
}

ResultInspection	&LayersBase::GetCurrentResultForDraw(void)
{
	static	ResultInspection	Dummy(NULL);
	/*
	if(CurrentResultForDraw==NULL){
		return GetLogicDLLBase()->GetResultData();
	}
	else{
		return *CurrentResultForDraw;
	}
	*/
	if(ExecuterDim==NULL){
		return Dummy;
	}
	ResultInspection	*Ret=ExecuterDim[CurrentDrawPoint]->GetResultInspection();
	return *Ret;
}

ResultInspection	*LayersBase::GetBufferedResult(int64 inspectionID)
{
	return GetResultThread()->GetBufferedResult(inspectionID);
}

ResultInspection	*LayersBase::GetBufferedOlderResult(int64 inspectionID, int GenerationLevel)
{
	return GetResultThread()->GetBufferedOlderResult(inspectionID, GenerationLevel);
}

void	LayersBase::ExecuteCopy(const QString &AlgoRoot ,const QString &AlgoName ,int localPage 
								,const XDateTime &createdTime,IntList &LayerList,bool EnableDup)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckDLL(AlgoRoot,AlgoName)==true){
			ClipboardAlgorithm	*C=L->ExecuteCopy(localPage ,createdTime,LayerList);
			if(C!=NULL){
				for(ClipboardAlgorithm *c=GetClipboardDatas()->GetFirst();c!=NULL;c=c->GetNext()){
					if(c->GetCreatedTime()==createdTime){
						c->Absorb(C);
						goto	QNext;
					}
				}
				GetClipboardDatas()->AppendList(C,EnableDup);
			}
QNext:;
		}
	}
}
void	LayersBase::Draw(QImage &img, int movx ,int movy ,double ZoomRate)
{
	for(int page=0;page<GetPageNumb();page++){
		DataInPage *P=GetPageData(page);
		P->Draw(img, movx ,movy ,ZoomRate);
	}
}

ClipboardAlgorithm	*LayersBase::SearchClipboard(const XDateTime &id)
{
	for(ClipboardAlgorithm *c=GetClipboardDatas()->GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetCreatedTime()==id){
			return c;
		}
	}
	return NULL;
}

int		LayersBase::GetSelectedItemCount(const QString &DLLRoot ,const QString &DLLName)
{
	AlgorithmBase	*A=GetAlgorithmBase(DLLRoot ,DLLName);
	if(A!=NULL){
		return A->GetSelectedItemCount();
	}
	return 0;
}
AlgorithmBase	*LayersBase::GetAlgorithmBase(int LibType)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->GetLibType()==LibType){
			return L->GetInstance();
		}
	}
	return NULL;
}

void	LayersBase::GetAlgorithmByType(AlgorithmBasePointerContainer &Bases ,int AlgorithmType)
{
	Bases.RemoveAll();
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckAlgorithmType(AlgorithmType)==true){
			Bases.Add(L->GetInstance());
		}
	}
}

void	LayersBase::SetStartInspectTime(const XDateTime &d)
{	
	StartInspectionTime=d;
	//InspectionTimeMilisec=GetComputerMiliSec();
}
void	LayersBase::SetEndInspectionTime(const XDateTime &d)
{	
	EndInspectionTime=d;
}
XDateTime	&LayersBase::GetStartInspectTime(void)
{	
	return StartInspectionTime;	
}
XDateTime	&LayersBase::GetEndInspectionTime(void)	
{	
	return EndInspectionTime;	
}
	
void	LayersBase::SetMainForm(GUIFormBase *form)
{
	if(form!=NULL){
		MainWidget=form;
		MainWidget->setObjectName(/**/"MainForm");
		connect(this,SIGNAL(SignalMainFormCommand(int)),MainWidget,SLOT(SlotCommand(int)),Qt::QueuedConnection);
		connect(ResultThread,SIGNAL(SignalWroteSlave(XDateTime))	,MainWidget,SLOT(SlotWroteSlave(XDateTime))	,Qt::QueuedConnection);
		connect(ResultThread,SIGNAL(SignalChangeLotInfo(int))			,MainWidget,SLOT(SlotChangeLotInfo(int))		,Qt::QueuedConnection);
		MainWidget->GiveName(NULL);
	}
}
void	LayersBase::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	if(GetGUIInstancePack()!=NULL && GetEntryPoint()!=NULL){
		for(GUIInstancePack *c=GetEntryPoint()->GetGUIInstancePack();c!=NULL;c=c->GetNext()){
			for(GUIItemInstance *d=c->NPListPack<GUIItemInstance>::GetFirst();d!=NULL;d=d->GetNext()){
				d->GetForm()->TransmitDirectly(packet);
			}
		}
	}
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmBase	*B=a->GetInstance();
			B->DeliverTransmitDirectly(packet);
		}
	}
	if(GetLightBase()!=NULL){
		for(LightClass *L=GetLightBase()->GetFirst();L!=NULL;L=L->GetNext()){
			L->TransmitDirectly(packet);
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *R=GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
			R->GetDLLPoint()->TransmitDirectly(packet);
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *R=GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
			R->GetDLLPoint()->TransmitDirectly(packet);
		}
	}
	for(int phase=0;phase!=GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetPageDataPhase(phase);
		for(int page=0;page!=GetPageNumb();page++){
			FilterInstanceContainer	*F=Ph->GetFilterContainer(page);
			for(FilterInstanceList *f=F->GetFirst();f!=NULL;f=f->GetNext()){
				f->TransmitDirectly(packet);
			}
		}
	}			
}

void	LayersBase::WroteSlave(const XDateTime &tm)
{
	ResultInspectionForStock	*r=GetResultThread()->Pickup(tm);
	if(r!=NULL){
		ResultWrittenID=r->GetInspectionID();
		if(GetParamComm()->Mastered==false){
			PacketWritternResult->InspectedTime=tm;
			PacketWritternResult->SendFromSlaveToMaster(GetGlobalPageFromLocal(0),0);
		}
	}
	else{
		ErrorOccurs++;
	}
}
void	LayersBase::SetResultWrittenID(int64 id)
{	
	ResultWrittenID=id;
	if(GetMainWidget()!=NULL){
		GetMainWidget()->BroadcastWroteResult(id);
	}
}

int64	LayersBase::GetUnsavedMinimumID(void)
{
	return GetResultThread()->GetUnsavedMinimumID();
}

void	LayersBase::CommandSaveResultToSlave(ResultInspection *res)
{
	ResultInspectionPointerStocker.AddPoint(res);
	emit	SignalMainFormCommand(ResultCmdSaveSlaveCommand);
}

void	LayersBase::CommandOutputInLotChangedToSlave(void)
{
	emit	SignalMainFormCommand(ResultCmdLotChangedSlaveCommand);
}
void	LayersBase::MainFormCommand(int cmd)
{
	static	QString	LStr;
	if(cmd==ResultCmdSaveSlaveCommand){
		ResultInspection	*Res=ResultInspectionPointerStocker.PopPointer();
		if(Res!=NULL){
			LStr=Res->GetStartTimeForInspection().toString("hhmmss");
			char	buff[50];
			QString2Char(LStr,buff ,sizeof(buff));
			GetLogCreater()->PutLogA2(__LINE__,"MainFormCommand",buff,Res->GetInspectionID());

			QBuffer	LotBuff;
			LotBuff.open(QIODevice::ReadWrite);
			::Save(&LotBuff,Res->GetLotID());
			::Save(&LotBuff,Res->GetLotName());
			//::Save(&LotBuff,GetLotBase()->GetLotID());
			//::Save(&LotBuff,GetLotBase()->GetLotName());

			for(int phase=0;phase<GetPhaseNumb();phase++){
				for(int page=0;page<GetPageNumb();page++){
					ResultCmdSaveSlave	Cmd(this,"ANY","ANY",page);
					Cmd.InspectedTime	=Res->GetStartTimeForInspection();
					Cmd.MachineID		=Res->GetLayersBase()->MachineID;
					Cmd.LotData			=LotBuff.buffer();
					Cmd.MasterID		=GetMasterCode();
					Cmd.Phase			=phase;
					Cmd.DeliveryInfo	=Res->GetDeliveredInfo();
					Cmd.Send(NULL,page ,0);
				}
			}
		}
		//delete	Res;
	}
	else if(cmd==ResultCmdLotChangedSlaveCommand){
		if(GetParamComm()->Mastered==true){
			ShowProcessingForm(/**/"Changing lot");
			for(int page=0;page<GetPageNumb();page++){
				ResultCmdReqLotChangedSlave	Cmd(this,"ANY","ANY",page);
				//GUICmdSendAck	Ack(this,"ANY","ANY",page);
				//Cmd.Send(page ,0,Ack);
				Cmd.Send(NULL,page,0);
				//Cmd.SendFromSlaveToMaster(GetGlobalPageFromLocal(page),0);
			}
			WaitAllAcknowledged(60*100);
			CloseProcessingForm();
		}
	}
	else if(cmd==ReportErrorFromSlaveCommand){
		if(GetParamComm()->Mastered==false){
			CmdReportError	SCmd(this,"ANY","ANY");
			ErrorCodeList	*e;
			for(;;){
				e=PopError();
				if(e==NULL){
					break;
				}
				SCmd.SetError(*e);
				delete	e;
				SCmd.SendFromSlaveToMaster(GetGlobalPageFromLocal(0),0);
			}
		}
	}
	else if(cmd==ShowCriticalErrorCommand){
		static	bool	ReEntrant=false;
		if(ReEntrant==false){
			ReEntrant=true;
			QString	S=GetAnyData()->ToString("CriticalError");
			AlertDialog		*Dlg=new AlertDialog(S);
			Dlg->exec();
			CloseOne();
			Dlg->deleteLater();
			ReEntrant=false;
		}
	}
	else if(cmd==BroadcastShowInPlayerCommand){
		if(GetMainWidget()!=NULL){
			GetMainWidget()->BroadcastShowInPlayer(GetCurrentInspectIDForDisplay());
		}
	}
}

bool	LayersBase::CreatePartialData(int globalX1 ,int globalY1 ,int globalX2, int globalY2
							,QIODevice *createdGlobalParam ,QIODevice *createdPix)
{
	bool	Ret=true;
	ParamGlobal	GParam(this);

	int	globalW=globalX2-globalX1;
	int	globalH=globalY2-globalY1;
	if(createdGlobalParam!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(GetParamGlobal()->SaveParam(&Buff)==false){
			return false;
		}
		Buff.seek(0);
		if(GParam.LoadParam(&Buff)==false){
			return false;
		}
		GParam.PageNumb=1;
		GParam.DotPerLine=globalW;
		GParam.MaxLines	 =globalH;
		GParam.TotalCameraNumb=1;
		if(GParam.SaveParam(createdGlobalParam)==false){
			return false;
		}
	}
	if(createdPix!=NULL){
		ImageBuffer		**PartialImage=new ImageBuffer*[GetLayerNumb()];
		for(int layer=0;layer<GetLayerNumb();layer++){
			PartialImage[layer]=new ImageBuffer();
			PartialImage[layer]->Set(0,ImageBufferOther,globalW,globalH);
		}

		for(int p=0;p<GetPageNumb();p++){
			DataInPage *P=GetDrawturn(p);
			int		localX1=globalX1-P->GetOutlineOffset()->x;
			int		localY1=globalY1-P->GetOutlineOffset()->y;
			int		localX2=globalX2-P->GetOutlineOffset()->x;
			int		localY2=globalY2-P->GetOutlineOffset()->y;
			if((localX1>=GetDotPerLine()) || (localY1>=GetMaxLines()) || ((localX2<0) || (localY2<0))){
				continue;
			}
			if(localX1<0){
				localX1=0;
			}
			if(localY1<0){
				localY1=0;
			}
			if(localX2>GetDotPerLine()){
				localX2=GetDotPerLine();
			}
			if(localY2>GetMaxLines()){
				localY2=GetMaxLines();
			}
			if((localX1==localX2) || (localY1==localY2)){
				continue;
			}
			GUICmdReqPartialImage	CmdReqPartialImage (this,"ANY","ANY",P->GetPage());
			GUICmdSendPartialImage	CmdSendPartialImage(this,"ANY","ANY",P->GetPage());

			CmdReqPartialImage.localX1=localX1;
			CmdReqPartialImage.localY1=localY1;
			CmdReqPartialImage.localX2=localX2;
			CmdReqPartialImage.localY2=localY2;
			CmdReqPartialImage.LayerNumb=GetLayerNumb();
			if(CmdReqPartialImage.Send(P->GetPage(),0,CmdSendPartialImage)==true){
				int	mx=localX1+P->GetOutlineOffset()->x-globalX1;
				int	my=localY1+P->GetOutlineOffset()->y-globalY1;
				int	localW=localX2-localX1;
				int	localH=localY2-localY1;
				for(int layer=0;layer<GetLayerNumb();layer++){
					for(int y=0;y<localH;y++){
						memcpy(PartialImage[layer]->GetY(my+y)+mx,CmdSendPartialImage.GetLayer(layer)->GetY(y),localW);
					}
				}
				//break;
			}
		}

		DWORD	ID=0xA55AE01F;
		int32	D=1;

		if(::Save(createdPix,ID)==false){
			Ret=false;
			goto	ErrorOut;
		}
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=globalW;
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=globalH;
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}
		D=GetLayerNumb();
		if(::Save(createdPix,D)==false){
			Ret=false;
			goto	ErrorOut;
		}

		for(int layer=0;layer<GetLayerNumb();layer++){
			for(int y=0;y<globalH;y++){
				BYTE    *dp=PartialImage[layer]->GetY(y);
				if(createdPix->write((const char *)dp ,globalW)!=globalW){
					Ret=false;
					goto	ErrorOut;
				}
            }
		}
		ErrorOut:;
		for(int layer=0;layer<GetLayerNumb();layer++){
			delete	PartialImage[layer];
		}
		delete	[]PartialImage;
	}
	return Ret;
}

void	LayersBase::CloseAll(void)
{
	SetOnChanging(true);
	GSleep(1000);
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSendClose	MCmd(this,"ANY","ANY",page);
		MCmd.Send(NULL,page,0);
	}
	OnTerminating=true;
	for(time_t t=time(NULL);time(NULL)-t<3;){
		QApplication::processEvents();
	}
}

void	LayersBase::CloseOne(void)
{
	OnTerminating=true;
	SetOnChanging(true);
	GSleep(1000);
}


void	LayersBase::ShowProcessingForm (const QString &Title ,bool CancelMode,int MaxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	//if(GetOnProcessing()!=NULL && GetParamGlobal()->ViewProcessingWindow==true){
	if(GetOnProcessing()!=NULL){
		GetOnProcessing()->setWindowTitle(Title);
		GetOnProcessing()->SetCancelMode(CancelMode);
		GetOnProcessing()->SetMax(MaxValue);
		for(int page=0;page<GetPageNumb();page++){
			GetOnProcessing()->SetValue(page,0);
		}
		GetOnProcessing()->Show();
		GetOnProcessing()->update();
		GetOnProcessing()->raise();
		//QApplication::processEvents();
		
		TmpHidingProcessingForm=false;
	}
	ProcessingReEntrant--;
}
void	LayersBase::StepProcessing(int localpage ,const QString &message)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			if(localpage>=0){
				GetOnProcessing()->SetMessage(message);
				GetOnProcessing()->Step(localpage);
				GetOnProcessing()->update();
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					GetOnProcessing()->SetMessage(message);
					GetOnProcessing()->Step(page);
					GetOnProcessing()->update();
				}
			}
			if(GetParamComm()->Mastered==true){
				QCoreApplication::processEvents();
			}
		}
		else if(GetParamComm()->Mastered==false){
			if(localpage>=0){
				int	globalPage=GetGlobalPageFromLocal(localpage);
				GUICmdSendProcessing	MCmd(this,"ANY","ANY",globalPage);
				MCmd.SendFromSlaveToMaster(globalPage,0);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					int	globalPage=GetGlobalPageFromLocal(page);
					GUICmdSendProcessing	MCmd(this,"ANY","ANY",globalPage);
					MCmd.SendFromSlaveToMaster(globalPage,0);
				}
			}
		}
	}
	ProcessingReEntrant--;
}

void	LayersBase::SetMaxProcessing(int maxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			GetOnProcessing()->SetMax(maxValue);
			GetOnProcessing()->update();
		}
		else if(GetParamComm()->Mastered==false){
			GUICmdSendProcessing	MCmd(this,"ANY","ANY",0);
			MCmd.MaxValue	 =maxValue;
			MCmd.SendFromSlaveToMaster(0,1);
		}
	}
	ProcessingReEntrant--;
}

void	LayersBase::AddMaxProcessing(int localpage ,int maxValue)
{
	if(ProcessingReEntrant!=0){
		return;
	}
	ProcessingReEntrant++;
	if(GetOnProcessing()!=NULL){
		if(GetOnProcessing()->isVisible()==true){
			GetOnProcessing()->AddMax(localpage,maxValue);
			GetOnProcessing()->update();
		}
		else if(GetParamComm()->Mastered==false){
			if(localpage>=0){
				int	globalPage=GetGlobalPageFromLocal(localpage);
				GUICmdSendProcessingAdd	MCmd(this,"ANY","ANY",globalPage);
				MCmd.MaxValue	 =maxValue;
				MCmd.SendFromSlaveToMaster(globalPage,1);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					int	globalPage=GetGlobalPageFromLocal(page);
					GUICmdSendProcessingAdd	MCmd(this,"ANY","ANY",globalPage);
					MCmd.MaxValue	 =maxValue;
					MCmd.SendFromSlaveToMaster(globalPage,1);
				}
			}
		}
	}
	ProcessingReEntrant--;
}
void	LayersBase::CloseProcessingForm(void)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	GetOnProcessing()->Hide();
	TmpHidingProcessingForm=false;
}

void	LayersBase::DelayedCloseProcessingForm(int sec)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	GetOnProcessing()->DelayedHide(sec);
	GetOnProcessing()->update();
	TmpHidingProcessingForm=false;
}

void	LayersBase::TmpHideProcessingForm(void)
{
	if(GetOnProcessing()==NULL){
		return;
	}
	if(GetOnProcessing()->isHidden()==false){
		GetOnProcessing()->hide();
		TmpHidingProcessingForm=true;
	}
}
	
void	LayersBase::TmpRercoverProcessingForm(void)
{
	if(TmpHidingProcessingForm==true){
		TmpHidingProcessingForm=false;
		if(GetOnProcessing()!=NULL){
			GetOnProcessing()->show();
		}
	}
}

void	LayersBase::SendAckToMaster(int localpage,int FilterdID)
{
	int	gpage=GetGlobalPageFromLocal(localpage);
	GUICmdSendAck	Cmd(this ,"ANY","ANY",0);
	Cmd.AckFilterID	=FilterdID;
	Cmd.SendFromSlaveToMaster(gpage ,0);
	SetAckFlag(localpage,FilterdID);
}
void	LayersBase::SendErrorAckToMaster(int localPage
						,int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level
						,int FilterdID)
{
	int	gpage=GetGlobalPageFromLocal(localPage);
	GUICmdSendAck	Cmd(this ,"ANY","ANY",0);
	Cmd.AckFilterID	=FilterdID;
	Cmd.SetError(errorCode ,errorMessage,level);
	Cmd.SendFromSlaveToMaster(gpage ,0);
	SetAckFlag(localPage,FilterdID);
}

void	LayersBase::SetAckFlag(int localPage,int FilterdID)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
		for(int page=0;page<GetPageNumb();page++){
			AckFlag[page]=false;
		}
	}
	if(AckFilterID==FilterdID || AckFilterID==-1){
		AckFlag[localPage]=true;
	}
}
void	LayersBase::ClearAllAckFlag(int FilterdID)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
	}
	GetEntryPoint()->WaitReadyReadAll(300);
	for(int page=0;page<GetPageNumb();page++){
		AckFlag[page]=false;
	}
	AckFilterID=FilterdID;
}
bool	LayersBase::IsAllAcknowledged(void)
{
	if((AckFlag!=NULL) && (AllocatedAckFlag!=GetPageNumb())){
		delete	[]AckFlag;
		AckFlag=NULL;
		AllocatedAckFlag=0;
	}
	if(AckFlag==NULL){
		AckFlag=new bool[GetPageNumb()];
		AllocatedAckFlag=GetPageNumb();
		for(int page=0;page<GetPageNumb();page++){
			AckFlag[page]=false;
		}
	}
	for(int page=0;page<GetPageNumb();page++){
		if(AckFlag[page]==false){
			return false;
		}
	}
	return true;
}
bool	LayersBase::WaitAllAcknowledged(int waitsecond ,bool CallProcessEvent)
{
	if(GetParamComm()->GetConnectedPCNumb()==0){
		return true;
	}
	StopCommSender=true;
	for(time_t	t=time(NULL);(time(NULL)-t)<waitsecond;){
		if(IsAllAcknowledged()==true){
			StopCommSender=false;
			return true;
		}
		if(GetOnProcessing()!=NULL){
			if(GetOnProcessing()->isVisible()==true){
				GetOnProcessing()->update();
				GetOnProcessing()->repaint();
			}
		}
		if(CallProcessEvent==true){
			QCoreApplication::processEvents ();
		}
		GetEntryPoint()->WaitReadyReadAll(300);
	}
	StopCommSender=false;
	return false;
}

DataInPage	*LayersBase::GetDrawturn(int TurnForPage)
{
	if(DrawPageIndex!=NULL){
		return DrawPageIndex[TurnForPage];
	}
	return GetPageData(TurnForPage);
}
void	LayersBase::SetTopInPage(DataInPage	*CurrentPage)
{
	if(DrawPageIndex==NULL){
		return;
	}
	DataInPage	*TmpTop=NULL;
	for(int page=0;page<GetPageNumb();page++){
		if(DrawPageIndex[page]->GetPage()==CurrentPage->GetPage()){
			TmpTop=DrawPageIndex[page];
			for(int i=page;i>0;i--){
				DrawPageIndex[i]=DrawPageIndex[i-1];
			}
			DrawPageIndex[0]=TmpTop;
			return;
		}
	}
}
bool	LayersBase::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}
void	LayersBase::ClearExecuterState(void)
{
	for(int i=0;i<AllocExecuterDim;i++){
		ExecuterDim[i]->InitializeState();
	}
}

void	LayersBase::SwitchImageBuff(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GetPageData(page)->SwitchImageBuff();
	}
}
	

void	LayersBase::SendSettingsToSlave(void)
{
	if(GetParamComm()->Mastered==true && GetParamComm()->GetConnectedPCNumb()!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSendParameters	SCmd(this,"ANY","ANY",page);
			SCmd.Initial();
			SCmd.Send(NULL,GetGlobalPageFromLocal(page),0);
		}
	}
}

void	LayersBase::WriteAllSettingFiles(void)
{
	if(GetParamComm()->Mastered==true){
		if(GetParamGlobal()->WriteEnableToDefaultFile()==true){
			QFile	FGeneral(CurrentPath
							+GetSeparator()+GetParamGlobal()->GetSavedFileName());
			if(FGeneral.open(QIODevice::WriteOnly)==true){
				GetParamGlobal()->SaveParam(&FGeneral);
			}
			/*
			QFile	FComm(GetParamComm()->GetSavesdFileName());
			if(FComm.open(QIODevice::WriteOnly)==true){
				GetParamComm()->SaveParam(&FComm);
			}
			*/
			if(GetResultDLLBase()!=NULL){
				for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					ResultDLLBaseRoot	*H=L->GetDLLPoint();
					QFile	FResult(CurrentPath
									+GetSeparator()+H->GetSavedFileName());
					if(FResult.open(QIODevice::WriteOnly)==true){
						H->SaveParam(&FResult);					
					}
				}
			}
			if(GetLogicDLLBase()!=NULL){		
				for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
					ParamBaseForAlgorithm	*P=L->GetInstance();
					QFile	FAlgprithm(CurrentPath
									 +GetSeparator()+P->GetSavedFileName());
					if(FAlgprithm.open(QIODevice::WriteOnly)==true){
						P->SaveParam(&FAlgprithm);
					}
				}
			}
			QFile	FShareMData(CurrentPath
							+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
			if(FShareMData.open(QIODevice::WriteOnly)==true){
				DataOfShareMasterContainer->Save(&FShareMData);
			}
		}
	}
}
ShareMasterDestination	*LayersBase::GetDataOfShareMaster(void)
{	
	return DataOfShareMasterContainer->FindDestination(GetMachineID());		
}

void	LayersBase::ReadBaseSettingFiles(bool Initialized,int BootSmall)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		QFile	FGeneral(CurrentPath
						+GetSeparator()+GetParamGlobal()->GetSavedFileName());
		if(FGeneral.open(QIODevice::ReadOnly)==true){
			GetParamGlobal()->LoadParam(&FGeneral);
		}
		if(BootSmall>=1){
			GetParamGlobal()->DotPerLine=100;
			GetParamGlobal()->MaxLines=100;
			GetParamGlobal()->PageNumb=BootSmall;
		}
	}
}

void	LayersBase::ReadOtherSettingFiles(bool Initialized,int BootSmall)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		if(GetResultDLLBase()!=NULL){
			QString	GmFileName;
			QString	tFileName;
			for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ResultDLLBaseRoot	*H=L->GetDLLPoint();
				GmFileName=CurrentPath;
				GmFileName=GmFileName+GetSeparator();
				tFileName=H->GetSavedFileName();
				GmFileName=GmFileName+tFileName;
				QFile	FResult(GmFileName);
				if(FResult.open(QIODevice::ReadOnly)==true){
					H->LoadParam(&FResult);					
				}
			}
		}
		//ReadLogicSettingFiles(Initialized);

		QFile	FShareMData(CurrentPath
						+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
		if(FShareMData.open(QIODevice::ReadOnly)==true){
			DataOfShareMasterContainer->Load(&FShareMData);
		}
	}
}

void	LayersBase::ReadAllSettingFiles(bool Initialized,int BootSmall)
{
	ReadBaseSettingFiles(Initialized,BootSmall);
	ReadOtherSettingFiles(Initialized,BootSmall);
}

void	LayersBase::ReadLogicSettingFiles(bool Initialized)
{
	if((GetParamComm()->Mastered==true) || (Initialized==true)){
		if(GetLogicDLLBase()!=NULL){		
			for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ParamBaseForAlgorithm	*P=L->GetInstance();
				if(L!=NULL){
					QFile	FAlgprithm(CurrentPath
									 +GetSeparator()+P->GetSavedFileName());
					if(FAlgprithm.open(QIODevice::ReadOnly)==true){
						P->LoadParam(&FAlgprithm);
					}
				}
			}
		}
	}
}

int		LayersBase::GetCurrentStrategicNumber(void)
{	
	return CurrentStrategicNumber;
}

void	LayersBase::IncreaseCurrentStrategicNumber(void)
{
	MutexCurrentStrategic.lock();
	CurrentStrategicNumber++;
	if(CurrentStrategicNumber>=GetParamGlobal()->GetMaxScanStrategy()){
		CurrentStrategicNumber=0;
	}
	if(GetParamGlobal()->BufferedProcessing==true){
		CurrentStrategicQueue.AppendList(new IntClass(CurrentStrategicNumber));
	}
	MutexCurrentStrategic.unlock();
}

void	LayersBase::SetCurrentStrategicNumber(int n)
{
	if((0<=n) && (n<GetParamGlobal()->GetMaxScanStrategy())){
		CurrentStrategicNumber=n;
		if(GetParamGlobal()->BufferedProcessing==true){
			CurrentStrategicQueue.AppendList(new IntClass(CurrentStrategicNumber));
		}
	}
}
void	LayersBase::PopCurrentStrategicNumberForCalc(void)
{
	MutexCurrentStrategic.lock();
	IntClass	*c=CurrentStrategicQueue.GetFirst();
	if(c==NULL){
		if((0<=CurrentStrategicNumber) && (CurrentStrategicNumber<GetParamGlobal()->GetMaxScanStrategy())){
			CurrentStrategicNumberForCalc=CurrentStrategicNumber;
		}
	}
	else{
		if((0<=c->GetValue()) && (c->GetValue()<GetParamGlobal()->GetMaxScanStrategy())){
			CurrentStrategicNumberForCalc=c->GetValue();
		}
		CurrentStrategicQueue.RemoveList(c);
		delete	c;
	}
	MutexCurrentStrategic.unlock();
}
void	LayersBase::ClearCurrentStrategicNumberForCalc(void)
{
	MutexCurrentStrategic.lock();
	CurrentStrategicQueue.RemoveAll();
	MutexCurrentStrategic.unlock();
}

void	LayersBase::ForceStrategicNumber(int n)
{
	MutexCurrentStrategic.lock();
	CurrentStrategicQueue.RemoveAll();
	if((0<=n) && (n<GetParamGlobal()->GetMaxScanStrategy())){
		CurrentStrategicNumber			=n;
		CurrentStrategicNumberForCalc	=n;
	}
	CurrentStrategicNumberForSeq	=n;
	MutexCurrentStrategic.unlock();

	int CPoints[10];
	GetCalcPoint(CPoints);

	if(GetParamComm()->Mastered==true && IsLocalCamera()==false){
		for(int page=0;page<GetPageNumb();page++){
			int	globalpage=GetGlobalPageFromLocal(page);
			GUICmdForceStrategicNumber	SCmd(this,"ANY","ANY",globalpage);
			SCmd.StrategicNumber	=n;
			SCmd.CPoints[0]=CPoints[0];
			SCmd.CPoints[1]=CPoints[1];
			SCmd.CPoints[2]=CPoints[2];

			SCmd.Send(NULL,globalpage,0);
		}
	}
}

bool	LayersBase::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	if(GetAlgoDLLContPointer()!=NULL){		
		for(AlgorithmDLLList *L=GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckSystemVersion(Str)==false){
				Ret=false;
			}
		}
	}
	if(GetResultDLLBase()!=NULL){
		for(ResultDLL *L=GetResultDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			if(L->CheckSystemVersion(Str)==false){
				Ret=false;
			}
		}
	}
	for(ArrangementDLLClass *a=GetArrangementDLLStock()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetLightBase()!=NULL){
		if(GetLightBase()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetFilterBank()!=NULL){
		if(GetFilterBank()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetGeneralStocker()!=NULL){
		if(GetGeneralStocker()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetPrinterClassPackData()!=NULL){
		if(GetPrinterClassPackData()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	if(GetResultAnalizerDLLContainer()!=NULL){
		if(GetResultAnalizerDLLContainer()->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	LayersBase::ExecuteLogoInGUIForm(GUIFormBase *W ,const QString &dllroot ,const QString &dllname)
{
	GetLogoStockerInstance()->ExecuteInGUIForm(W ,dllroot ,dllname);
}
	
void	LayersBase::ExecuteLogoInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname)
{
	GetLogoStockerInstance()->ExecuteInQWidget(W ,_typename ,dllroot ,dllname);
}

void	LayersBase::MessageSocketError(IntList &ErrorPages)
{
	QString	S=QString("Socket error!!");
	for(IntClass *s=ErrorPages.GetFirst();s!=NULL;s=s->GetNext()){
		S=S+QString("  Page:")+QString::number(s->GetValue());
	}
	CloseProcessingForm();
	GetAnyData()->Set("CriticalError",S);
	emit	SignalMainFormCommand(ShowCriticalErrorCommand);
}

void	LayersBase::PushCapturedPageLayer(PageAndLayerFlagListContainer &CurrentCapturedPageLayerList)
{
	MutexCapturedPageLayerList.lock();
	CapturedPageLayerList+=CurrentCapturedPageLayerList;
	MutexCapturedPageLayerList.unlock();
}
int		LayersBase::GetTopPageInCapturedPageLayer(void)
{
	int	RetPage= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetPage=CapturedPageLayerList.GetFirst()->Page;
	}
	MutexCapturedPageLayerList.unlock();
	return RetPage;
}
int		LayersBase::GetTopPageInCapturedPageLayer(bool DoneFlag)
{
	int	RetPage= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetPage=CapturedPageLayerList.GetFirst()->Page;
		CapturedPageLayerList.GetFirst()->Done=DoneFlag;
	}
	MutexCapturedPageLayerList.unlock();
	return RetPage;
}
bool	LayersBase::GetTopFlagInCaptured(void)
{
	bool	DoneFlag=false;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		DoneFlag=CapturedPageLayerList.GetFirst()->Done;
	}
	MutexCapturedPageLayerList.unlock();
	return DoneFlag;
}
int		LayersBase::GetTopLayerInCapturedPageLayer(void)
{
	int	RetLayer= -1;
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		RetLayer=CapturedPageLayerList.GetFirst()->Layer;
	}
	MutexCapturedPageLayerList.unlock();
	return RetLayer;
}

void	LayersBase::ClearTopInCapturedPageLayer(void)
{
	MutexCapturedPageLayerList.lock();
	if(CapturedPageLayerList.GetFirst()!=NULL){
		PageAndLayerFlagList *L=CapturedPageLayerList.GetFirst();
		CapturedPageLayerList.RemoveList(L);
		delete L;
	}
	MutexCapturedPageLayerList.unlock();
}


bool	LayersBase::IsEdited(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return false;
	}
	ReEntrant=true;

	for(int phase=0;phase<AllocatedPhaseNumb && phase<GetPhaseNumb();phase++){
		if(GetPageDataPhase(phase)->IsEdited()==true){
			ReEntrant=false;
			return true;
		}
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqEdited		ReqCmd(this ,"ANY","ANY",page);
			GUICmdSendEdited	SendCmd(this ,"ANY","ANY",page);
			ReqCmd.Send(page,0,SendCmd);
			if(SendCmd.Edited==true){
				ReEntrant=false;
				return true;
			}
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsEdited()==true){
			ReEntrant=false;
			return true;
		}
	}
	ReEntrant=false;

	return false;
}

bool	LayersBase::IsCalcDone(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if(GetPageData(page)->IsCalcDone()==false){
			return false;
		}
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqCalcDone	ReqCmd(this ,"ANY","ANY",page);
			GUICmdSendCalcDone	SendCmd(this ,"ANY","ANY",page);
			ReqCmd.Send(page,0,SendCmd);
			if(SendCmd.CalcDone==false){
				return false;
			}
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}


void	LayersBase::SetEdited(bool edited)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	for(int phase=0;phase<AllocatedPhaseNumb && phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->SetEdited(edited);
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetEdited		ReqCmd(this ,"ANY","ANY",page);
			ReqCmd.Edited=edited;
			ReqCmd.Send(NULL,page,0);
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->SetEdited(edited);
	}
	ReEntrant=false;
}
void	LayersBase::SetCalcDone(bool calcdone)
{
	for(int page=0;page<GetPageNumb();page++){
		GetPageData(page)->SetCalcDone(calcdone);
	}
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetCalcDone		ReqCmd(this ,"ANY","ANY",page);
			ReqCmd.CalcDone=calcdone;
			ReqCmd.Send(NULL,page,0);
		}
	}
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->SetCalcDone(calcdone);
	}
}

void	LayersBase::RemoveStockedResult(void)
{
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			CmdReqRemoveStockedResult	RCmd(this ,"ANY","ANY",page);
			RCmd.Send(NULL,page,0);
		}
	}

	ResultInspection	*Ref;
	for(;;){
		Ref=GetResultThread()->NeedDeleteResult();
		if(Ref==NULL){
			break;
		}
		GetLogicDLLBase()->ExecuteRemoveResult(GetMasterCode()
											,LotInfo//GetLotAutoCount()
											,Ref->GetInspectionID()
											,Ref);
	}
}

int		LayersBase::GeneralStockerShowDialog(const QString &Keyword)
{
	int	n=GetGeneralStocker()->GetCountOfEffectiveShowDialog(Keyword);
	if(n==0){
		return -1;
	}
	else if(n==1){
		return GetGeneralStocker()->ShowDialog(Keyword,GetMainWidget());
	}
	else{
		NPListPack<GeneralStockerPointerList>	Dim;
		for(int i=0;i<n;i++){
			Dim.AppendList(new GeneralStockerPointerList(GetGeneralStocker()->GetShowDialogPointer(i)));
		}
		SelectGeneralStocker	D(this,Dim,GetMainWidget());
		if(D.exec()==(int)true){
			return D.Selected->ShowDialog(Keyword,GetMainWidget());
		}
	}
	return -1;
}

int		LayersBase::GetErrorCount(void)
{
	ErrorMutex.lock();
	int	ret=GetErrorContainer()->GetNumber();
	ErrorMutex.unlock();
	return ret;
}

void	LayersBase::ClearErrorCount(void)
{
	ErrorMutex.lock();
	GetErrorContainer()->RemoveAll();
	ErrorMutex.unlock();
}

bool	LayersBase::GetError(int index ,ErrorCodeList &Ret)
{
	if((0<=index) && (index<GetErrorContainer()->GetNumber())){
		ErrorMutex.lock();
		ErrorCodeList	*r=GetErrorContainer()->GetItem(index);
		Ret= *r;
		ErrorMutex.unlock();
		return true;
	}
	return false;
}

ErrorCodeList	*LayersBase::PopError(void)
{
	ErrorMutex.lock();
	ErrorCodeList	*r=GetErrorContainer()->GetFirst();
	GetErrorContainer()->RemoveList(r);
	ErrorMutex.unlock();
	return r;
}

void	LayersBase::SendErrorToMaster(int errorCode , const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	ErrorCodeList *e=new ErrorCodeList(level,errorMessage ,errorCode);
	ErrorMutex.lock();
	GetErrorContainer()->AppendList(e);
	ErrorMutex.unlock();

	emit	SignalMainFormCommand(ReportErrorFromSlaveCommand);
}

void	LayersBase::BroadcastInspectionNumber(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSendInspectionNumber	Cmd(this,"ANY","ANY",page);
		Cmd.InspectionNumber=GetInspectionNumber();
		Cmd.Send(NULL,page,0);
	}
}

bool	LayersBase::IsDoneCompressed(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			if(GetPageData(page)->IsDoneCompressed()==false){
				return false;
			}
		}
	}
	else{
		IntList PageList;
		GetParamGlobal()->GetStrategyPage(GetCurrentStrategicNumber(),PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			if(GetPageData(page)->IsDoneCompressed()==false){
				return false;
			}
		}
	}
	return true;
}

int			LayersBase::SetCurrentPhase(int phase)
{
	static	bool	ReEntrantSetCurrentPhase=false;

	if(ReEntrantSetCurrentPhase==false){
		ReEntrantSetCurrentPhase=true;
		if(AllocatedPhaseNumb>phase){
			PageData=PageDataPhase[phase];
			CurrentPhase=phase;
			if(GetParamComm()->Mastered==true && GetParamComm()->GetConnectedPCNumb()!=0){
				for(int page=0;page<GetPageNumb();page++){
					GUICmdReqSetCurrentPhase	Cmd(this,"ANY","ANY",page);
					Cmd.CurrentPhase=GetCurrentPhase();
					Cmd.Send(NULL,page,0);
				}
			}
		}
	}
	ReEntrantSetCurrentPhase=false;
	return CurrentPhase;
}

QString	LayersBase::GetFilterDefFileName(void)
{
	QString	Path=GetCurrentPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	QString	FileName=Path+GetParamGlobal()->FilterDefFile;
	return FileName;
}
bool	LayersBase::LoadFilterDef(void)
{
	QString	FileName=GetFilterDefFileName();
	QFile	f(FileName);
	if(f.open(QIODevice::ReadOnly)==true){
		return LoadFilterDef(&f);
	}
	return false;
}
bool	LayersBase::LoadFilterDef(QIODevice *f)
{
	int32	Ph;
	if(::Load(f,Ph)==false){
		return false;
	}
	for(int phase=0;phase<Ph && phase<GetPhaseNumb();phase++){
		if(PageDataPhase[phase]->LoadFilterContainer(f)==false){
			return false;
		}
		if(PageDataPhase[phase]->LoadPhaseSource(f)==false){
			return false;
		}
	}
	return true;
}

bool	LayersBase::SaveFilterDef(void)
{
	QString	Path=GetCurrentPath();
	if(Path.right(1)!="\\" && Path.right(1)!="/"){
		Path=Path+GetSeparator();
	}
	QString	FileName=Path+GetParamGlobal()->FilterDefFile;
	QFile	f(FileName);
	if(f.open(QIODevice::WriteOnly)==true){
		return SaveFilterDef(&f);
	}
	return false;
}

bool	LayersBase::SaveFilterDef(QIODevice *f)
{
	int32	Ph=GetPhaseNumb();
	if(::Save(f,Ph)==false){
		return false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(PageDataPhase[phase]->SaveFilterContainer(f)==false){
			return false;
		}
		if(PageDataPhase[phase]->SavePhaseSource(f)==false){
			return false;
		}
	}
	return true;
}
bool	LayersBase::ExecuteFilterBeforeScan(void)
{
	bool	Ret=true;
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->ExecuteFilterBeforeScan(this)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LayersBase::ExecuteFilteringMaster()
{
	bool	Ret=true;
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageMasterFrom(this,CP);
		}
		if(P->ExecuteFilteringMaster(this)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	LayersBase::ExecuteFilteringTarget()
{
	bool	Ret=true;
	StartTimeExecuteFilter=QTime::currentTime ();
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	{
		IntList PhaseCodes;
 		GetCurrentPhaseFromScanPhase(PhaseCodes);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			bool	NoChange=false;
			for(IntClass *d=PhaseCodes.GetFirst();d!=NULL;d=d->GetNext()){
				if(phase==d->GetValue()){
					NoChange=true;
					break;
				}
			}
			if(NoChange==true){
				PageDataInOnePhase	*P=GetPageDataPhase(phase);
				if(P->GetFromSourcePhase()==GetCurrentPhase() && CP->GetPhaseCode()!=P->GetPhaseCode()){
					P->CopyImageTargetFrom(this,CP);
				}
			}
		}
	}
	{
		IntList PhaseCodes;
 		GetCurrentPhaseFromScanPhase(PhaseCodes);
		for(int phase=0;phase<GetPhaseNumb();phase++){
			bool	NoChange=false;
			for(IntClass *d=PhaseCodes.GetFirst();d!=NULL;d=d->GetNext()){
				if(phase==d->GetValue()){
					NoChange=true;
					break;
				}
			}
			if(NoChange==true){
				PageDataInOnePhase	*P=GetPageDataPhase(phase);
				if(P->ExecuteFilteringTarget(this)==false){
					Ret=false;
				}
			}
		}
	}
	MilisecExecuteFilter=StartTimeExecuteFilter.msecsTo (QTime::currentTime());

	return Ret;
}

void	LayersBase::RemoveResultFromOldest(int n)
{
	ResultInspectionForStock	*r=GetResultThread()->RemoveResultFromOldest(n);
	if(r!=NULL){
		GetResultHistryData()->RemoveResult(r->GetStartTimeForInspection());
		emit	SignalMainFormCommand(BroadcastShowInPlayerCommand);
	}
}

void	LayersBase::SetStatusModes(GUIFormBase *f,const QStringList &modes)
{
	//if(GetStatusController()!=NULL){
	//	GetStatusController()->SetStatusModes(f,modes);
	//}
}
void	LayersBase::SetStatusModes(GUIFormBase *f,const QString &mode)
{
	QStringList	L;
	L.append(mode);
	SetStatusModes(f,L);
}

bool	LayersBase::DeliverMakeUncoveredArea(void)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdMakeUncoveredMap	RCmd(this,/**/"ANY",/**/"ANY",page);
		if(RCmd.SendOnly(page,0)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::GetAlignmentForProcessing(int Page ,AlignmentPacketBase &Packet)
{
	LogicDLL	*L=GetLogicDLLBase()->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	if(L==NULL){
		return;
	}
	L->GetAlignmentForProcessing(Page,Packet);
}

void	LayersBase::DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
							,bool Mastered
							,const QColor &LColor
							,int OffsetX ,int OffsetY)
{
	for(int page=0;page<GetPageNumb();page++){
		XYData	*xy=GetPageData(page)->GetOutlineOffset();
		GetPageData(page)->DrawImage(Img, movx ,movy ,ZoomRate
							,Mastered
							,LColor
							,OffsetX+xy->x,OffsetY+xy->y);
	}
}
void	LayersBase::SendToOtherPhaseMaster(void)
{
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(phase==GetCurrentPhase()){
			continue;
		}
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageMasterFrom(this,CP);
			P->ExecuteFilteringMaster(this);
		}
	}
}
void	LayersBase::SendToOtherPhaseTarget(void)
{
	PageDataInOnePhase	*CP=GetCurrentPageDataPhase();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(phase==GetCurrentPhase()){
			continue;
		}
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		if(P->GetFromSourcePhase()==GetCurrentPhase()){
			P->CopyImageTargetFrom(this,CP);
			P->ExecuteFilteringTarget(this);
		}
	}
}

int32	LayersBase::GetIDForUndo(void)
{
	UndoTopic	*L=UndoDataStocker.GetCurrentTopic();
	if(L!=NULL){
		return L->GetIDForUndo();
	}
	return -1;
}

void	LayersBase::AddUndo(UndoTopic *a)
{
	UndoDataStocker.AppendList(a);
	UndoDataStocker.IDBase++;
}

void	LayersBase::AddRedo(UndoTopic *a)
{
	RedoDataStocker.AppendList(a);
	RedoDataStocker.IDBase++;
}

void	LayersBase::TestLoadDLL(const QString &FileName)
{
	if(IsMainThread()==true){
		if(InstShowLoadingDLLForm==NULL){
			InstShowLoadingDLLForm=new ShowLoadingDLLForm(this,NULL);
			if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
				InstShowLoadingDLLForm->show();
			}
		}
		InstShowLoadingDLLForm->TestAdd(FileName);
		if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
			InstShowLoadingDLLForm->show();
		}
		QCoreApplication::processEvents();
	}
}
void	LayersBase::InformToLoadDLL(const QString &FileName)
{
	if(IsMainThread()==true){
		if(InstShowLoadingDLLForm==NULL){
			InstShowLoadingDLLForm=new ShowLoadingDLLForm(this,NULL);
			if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
				InstShowLoadingDLLForm->show();
			}
		}
		InstShowLoadingDLLForm->Add(FileName);
		if(GetParamGlobal()->ModeToShowLoadingDLLWindow==true){
			InstShowLoadingDLLForm->show();
			InstShowLoadingDLLForm->update();
		}
		//QCoreApplication::processEvents();
	}
}

void	LayersBase::CloseInformed(void)
{
	if(InstShowLoadingDLLForm!=NULL){
		InstShowLoadingDLLForm->close();
		InstShowLoadingDLLForm->deleteLater();
		InstShowLoadingDLLForm=NULL;
	}
}

bool	LayersBase::IsMainThread(void)
{
	if(MainThread==QThread::currentThreadId()){
		return true;
	}
	return false;
}

void	LayersBase::CenterizeDialog(QWidget *f)
{
	QWidget	*s=GetMainWidget();
	f->setParent(NULL);
	f->move( s->geometry().x()+(s->width ()-f->width ())/2 
			,s->geometry().y()+(s->height()-f->height())/2);
}

void	LayersBase::ClearHistgramData(void)
{
	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		if(ABase!=NULL){
			ABase->ClearHistgram();
		}
	}
}
bool	LayersBase::SaveHistgram(QIODevice *f)
{
	int32	N=GetLogicDLLBase()->GetCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		QString	DLLRoot;
		QString	DLLName;
		ABase->GetAlgorithmRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		if(ABase->SaveHistgram(f)==false){
			return false;
		}
	}
	return true;
}
	
bool	LayersBase::LoadHistgram(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(f,DLLRoot)==false){
			return false;
		}
		if(::Load(f,DLLName)==false){
			return false;
		}
		AlgorithmBase	*ABase=GetAlgorithmBase(DLLRoot,DLLName);
		if(ABase==NULL){
			return false;
		}
		if(ABase->LoadHistgram(f)==false){
			return false;
		}
	}
	return true;
}

void	LayersBase::LoopOnIdle(void)
{
	if(GetLogicDLLBase()!=NULL){
		for(LogicDLL *L=GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmBase	*ABase=L->GetInstance();
			if(ABase!=NULL){
				ABase->LoopOnIdle();
			}
		}
	}
	if(GetLightBase()!=NULL){
		GetLightBase()->LoopOnIdle();
	}
}
int		LayersBase::GetCountOfCompressing(void)
{
	int	Count=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		Count	+=	P->GetCountOfCompressing();
	}
	return Count;
}

void	LayersBase::SwapImageOutOfBuffer(int ImageDataType)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->SwapImageOutOfBuffer(ImageDataType);
	}
}
void	LayersBase::SwapImageInToBuffer(int ImageDataType)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*P=GetPageDataPhase(phase);
		P->SwapImageInToBuffer(ImageDataType);
	}
}


void	LayersBase::InstallOperationLog(QObject *window)
{
	if(GetOperationLoggerData()!=NULL){
		GetOperationLoggerData()->Install(window);
	}
}

bool	EntryPointBase::IsMasterPC(void)
{
	return GetParamComm()->Mastered;
}

bool	LayersBase::ThinAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(ShrinkingPackContainerInstance==NULL)
		return false;
	return ShrinkingPackContainerInstance->ThinAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,ForceZone
				,EnableThread);
}
bool   LayersBase::FatAreaN(BYTE **bmpdata
				,BYTE **bitoperation
				,int xbyte ,int YLenDot 
				,int Numb
				,FlexArea *ForceZone
				,bool EnableThread)
{
	if(ShrinkingPackContainerInstance==NULL)
		return false;
	return ShrinkingPackContainerInstance->FatAreaN(bmpdata
				,bitoperation
				,xbyte ,YLenDot 
				,Numb
				,ForceZone
				,EnableThread);
}

void	LayersBase::SetLibFolderID(int libFolderID ,int originalLibFolder ,bool TransferToSlave)
{	
	CurrentLibFolderID=libFolderID;	
	if(TransferToSlave==true && GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdSetLibFolderID	RCmd(this,"ANY","ANY",page);
			RCmd.LibFolderID		=libFolderID;
			RCmd.originalLibFolder	=originalLibFolder;
			RCmd.Send(NULL,page,0);
		}
	}
}

QString		LayersBase::GetLibFolderName(int libFolderID)
{
	if(GetDatabaseLoader()!=NULL && GetDatabaseLoader()->S_LibFolderFindData!=NULL){
		QString FolderName;
		int		ParentID;
		int		NumberInFolder;
		if(GetDatabaseLoader()->S_LibFolderFindData(GetDatabase(),libFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
			return FolderName;
		}
	}
	return /**/"";
}
bool	LayersBase::ScanChangedInSlave(void)
{
	ChangedAlgo.ChangedPreAlignment		=false;
	ChangedAlgo.ChangedAlignment		=false;
	ChangedAlgo.ChangedPreProcessing	=false;
	ChangedAlgo.ChangedProcessing		=false;
	ChangedAlgo.ChangedProcessingRevived=false;
	ChangedAlgo.ChangedPostProcessing	=false;
	ChangedAlgo.ChangedNoProcessing		=false;
	ChangedAlgo.ChangedPieceProcessing	=false;
	ChangedAlgo.ChangedPreScanning		=false;
	ChangedAlgo.ChangedScanning			=false;
	ChangedAlgo.ChangedPostScanning		=false;
	ChangedAlgo.ChangedMatchAlignment	=false;
	ChangedAlgo.ChangedManageResult		=false;
	ChangedAlgo.ChangedMasking			=false;
	ChangedAlgo.ChangedDynamicMasking	=false;
	if(GetParamComm()->Mastered==true){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdReqChangedAlgo	RCmd(this,"ANY","ANY",page);
			GUICmdAckChangedAlgo	ACmd(this,"ANY","ANY",page);
			if(RCmd.Send(page,0,ACmd)==true){
				if(ACmd.ChangedAlgo.ChangedPreAlignment==true)
					ChangedAlgo.ChangedPreAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedAlignment==true)
					ChangedAlgo.ChangedAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedPreAlignment==true)
					ChangedAlgo.ChangedPreAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedPreProcessing==true)
					ChangedAlgo.ChangedPreProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedProcessing==true)
					ChangedAlgo.ChangedProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedProcessingRevived==true)
					ChangedAlgo.ChangedProcessingRevived	=true;

				if(ACmd.ChangedAlgo.ChangedPostProcessing==true)
					ChangedAlgo.ChangedPostProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedNoProcessing==true)
					ChangedAlgo.ChangedNoProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedPieceProcessing==true)
					ChangedAlgo.ChangedPieceProcessing	=true;

				if(ACmd.ChangedAlgo.ChangedPreScanning==true)
					ChangedAlgo.ChangedPreScanning	=true;

				if(ACmd.ChangedAlgo.ChangedScanning==true)
					ChangedAlgo.ChangedScanning	=true;

				if(ACmd.ChangedAlgo.ChangedPostScanning==true)
					ChangedAlgo.ChangedPostScanning	=true;

				if(ACmd.ChangedAlgo.ChangedMatchAlignment==true)
					ChangedAlgo.ChangedMatchAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedMatchAlignment==true)
					ChangedAlgo.ChangedMatchAlignment	=true;

				if(ACmd.ChangedAlgo.ChangedManageResult==true)
					ChangedAlgo.ChangedManageResult	=true;

				if(ACmd.ChangedAlgo.ChangedMasking==true)
					ChangedAlgo.ChangedMasking	=true;

				if(ACmd.ChangedAlgo.ChangedDynamicMasking==true)
					ChangedAlgo.ChangedDynamicMasking	=true;
			}
			else{
				return false;
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			GUICmdDeliverChangedAlgo	DCmd(this,"ANY","ANY",page);
			DCmd.ChangedAlgo	=ChangedAlgo;
			DCmd.Send(NULL,page,0);
		}
	}
	return true;
}
bool	LayersBase::IsChanged(int AlgorithmBit_Type)
{
	bool	Ret=false;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreAlignment		)!=0)	Ret=(ChangedAlgo.ChangedPreAlignment		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeAlignment			)!=0)	Ret=(ChangedAlgo.ChangedAlignment			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreProcessing		)!=0)	Ret=(ChangedAlgo.ChangedPreProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeProcessing			)!=0)	Ret=(ChangedAlgo.ChangedProcessing			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeProcessingRevived	)!=0)	Ret=(ChangedAlgo.ChangedProcessingRevived	==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePostProcessing		)!=0)	Ret=(ChangedAlgo.ChangedPostProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeNoProcessing		)!=0)	Ret=(ChangedAlgo.ChangedNoProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePieceProcessing	)!=0)	Ret=(ChangedAlgo.ChangedPieceProcessing		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePreScanning		)!=0)	Ret=(ChangedAlgo.ChangedPreScanning			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeScanning			)!=0)	Ret=(ChangedAlgo.ChangedScanning			==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypePostScanning		)!=0)	Ret=(ChangedAlgo.ChangedPostScanning		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeMatchAlignment		)!=0)	Ret=(ChangedAlgo.ChangedMatchAlignment		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeManageResult		)!=0)	Ret=(ChangedAlgo.ChangedManageResult		==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeMasking			)!=0)	Ret=(ChangedAlgo.ChangedMasking				==true)?true:Ret;
	if((AlgorithmBit_Type & AlgorithmBit_TypeDynamicMasking		)!=0)	Ret=(ChangedAlgo.ChangedDynamicMasking		==true)?true:Ret;

	return Ret;
}
void	LayersBase::SetAllModeLoadSaveInPlayer(bool b)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->SetModeLoadSaveInPlayer(b);
		}
	}
}

void	LayersBase::ShowLensWindow(bool ON)
{
	if(ON==true){
		if(LensWindow==NULL){
			LensWindow=new LensWindowForm(this);
		}
		LensWindow->show();
	}
	else{
		if(LensWindow!=NULL){
			LensWindow->hide();
		}
	}
}

void	LayersBase::CopyTargetToTransposition(void)
{
	if(GetParamGlobal()->CommonTargetBetweenPhases==false){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PageDataInOnePhase	*P=GetPageDataPhase(phase);
			P->CopyTargetToTransposition();
		}
	}
	else{
		PageDataInOnePhase	*P=GetPageDataPhase(0);
		P->CopyTargetToTransposition();
	}
}

void	LayersBase::ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY)
{
	if(LensWindow!=NULL){
		LensWindow->ShowLens(_TargetPanel ,GlobalX ,GlobalY , _TargetPanel->GetDisplayType());
	}
}

void	LayersBase::SetZoneWindow(GUIFormBase *w)
{
	if(ZoneWindow!=NULL){
		delete	ZoneWindow;
		ZoneWindow=NULL;
	}
	QWidget	*P=w->parentWidget();
	if(P!=NULL){
		ZoneWindow=new ZoneWindowForEdit();

		int	x1=w->geometry().left();
		int	y1=w->geometry().top();
		int	x2=w->geometry().right();
		int	y2=w->geometry().bottom();

		//w->setParent(NULL);
		ZoneWindow->setParent(P);
		//w->setParent(P);
		ZoneWindow->stackUnder(w);
		//w->move(x1,y1);
		//w->resize(x2-x1+1,y2-y1+1);
		ZoneWindow->show();
		CurrentZoneWindowComponent	=w;
		SetMoveZoneWindow(w);
	}
}
void	LayersBase::SetMoveZoneWindow(GUIFormBase *w)
{
	if(ZoneWindow!=NULL && w!=NULL && w==CurrentZoneWindowComponent){
		ZoneWindow->move(w->geometry().left()-2,w->geometry().top()-2);
		ZoneWindow->resize(w->width()+4,w->height()+4);
		ZoneWindow->update();
	}
}

QString			LayersBase::GetLibraryName(int LibType ,int LibID)
{
	return GetDatabaseLoader()->G_GetLibraryName2(*GetDataBase(),LibType ,LibID);
}

void	LayersBase::SetProcessDone(bool b)
{
	for(LogicDLL *a=GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetInstance()!=NULL){
			a->GetInstance()->SetProcessDone(b);
		}
	}
}