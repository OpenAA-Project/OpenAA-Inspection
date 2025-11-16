/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include <omp.h>
#include "XCrossObj.h"
#include "XLanguageClass.h"
#include "ShowThresholdHistgramForm.h"
#include "XHistgramByParam.h"
#include <iostream>
#include "XImageProcess.h"
#include "XWriteResultThread.h"
#include "XDataAlgorithmList.h"
#include "XDataInLayerCmdLocal.h"
#include "Regulus64System.h"
#include "XTransform.h"
#include "XAnyData.h"
#include "XCriticalFunc.h"

extern	LangSolverNew	LangLibSolver;


ExecuteInitialAfterEditInfo::ExecuteInitialAfterEditInfo(void)
{
	ExecuteInitialAfterEdit_Changed	=false;
	CalledInLoadMaster				=false;
	CalledInFirst					=false;
	HasChangedOnlyImage				=false;
	ApplicableArea					=NULL;
}
	
ExecuteInitialAfterEditInfo::ExecuteInitialAfterEditInfo(const ExecuteInitialAfterEditInfo &src)
{
	ExecuteInitialAfterEdit_Changed	=src.ExecuteInitialAfterEdit_Changed;
	CalledInLoadMaster				=src.CalledInLoadMaster				;
	CalledInFirst					=src.CalledInFirst					;
	HasChangedOnlyImage				=src.HasChangedOnlyImage			;
	ApplicableArea					=src.ApplicableArea					;
}


ExecuteInitialAfterEditInfo	&ExecuteInitialAfterEditInfo::operator=(const ExecuteInitialAfterEditInfo &src)
{
	ExecuteInitialAfterEdit_Changed	=src.ExecuteInitialAfterEdit_Changed;
	CalledInLoadMaster				=src.CalledInLoadMaster				;
	CalledInFirst					=src.CalledInFirst					;
	HasChangedOnlyImage				=src.HasChangedOnlyImage			;
	ApplicableArea					=src.ApplicableArea					;

	return *this;
}

bool	ExecuteInitialAfterEditInfo::Save(QIODevice *f)
{
	if(::Save(f,ExecuteInitialAfterEdit_Changed)==false)	return false;
	if(::Save(f,CalledInLoadMaster)==false)	return false;
	if(::Save(f,CalledInFirst)==false)		return false;
	if(::Save(f,HasChangedOnlyImage)==false)return false;
	return true;
}
bool	ExecuteInitialAfterEditInfo::Load(QIODevice *f)
{
	if(::Load(f,ExecuteInitialAfterEdit_Changed)==false)	return false;
	if(::Load(f,CalledInLoadMaster)==false)	return false;
	if(::Load(f,CalledInFirst)==false)		return false;
	if(::Load(f,HasChangedOnlyImage)==false)return false;
	return true;
}

//========================================================================================
AlgorithmDrawAttr	&AlgorithmDrawAttr::operator=(const AlgorithmDrawAttr &src)
{
	DType			=src.DType;
	UncoveredColor	=src.UncoveredColor;
	NormalColor		=src.NormalColor;
	SelectedColor	=src.SelectedColor;
	ActiveColor		=src.ActiveColor;
	ModeDrawRental	=src.ModeDrawRental;
	LineWidth		=src.LineWidth;
	return *this;
}

bool	AlgorithmDrawAttr::SaveAttr(QIODevice *f)
{
	if(::Save(f,DType)==false){
		return false;
	}
	if(::Save(f,UncoveredColor)==false){
		return false;
	}
	if(::Save(f,NormalColor)==false){
		return false;
	}
	if(::Save(f,SelectedColor)==false){
		return false;
	}
	if(::Save(f,ActiveColor)==false){
		return false;
	}
	if(Save(f)==false){
		return false;
	}
	if(::Save(f,ModeDrawRental)==false){
		return false;
	}
	if(::Save(f,LineWidth)==false){
		return false;
	}
	return true;
}
bool	AlgorithmDrawAttr::LoadAttr(QIODevice *f)
{
	if(::Load(f,DType)==false){
		return false;
	}
	if(::Load(f,UncoveredColor)==false){
		return false;
	}
	if(::Load(f,NormalColor)==false){
		return false;
	}
	if(::Load(f,SelectedColor)==false){
		return false;
	}
	if(::Load(f,ActiveColor)==false){
		return false;
	}
	if(Load(f)==false){
		return false;
	}
	if(::Load(f,ModeDrawRental)==false){
		return false;
	}
	if(::Load(f,LineWidth)==false){
		return false;
	}
	return true;
}

bool	AlgorithmDrawAttr::Save(QIODevice *f)
{
	return true;
}
bool	AlgorithmDrawAttr::Load(QIODevice *f)
{
	return true;
}

//========================================================================================

void	AlignmentPacketBase::Set(AlgorithmItemRoot *src)
{
	Page	=src->GetPage();
	Layer	=src->GetLayer();
	SourceID=src->GetID();
}
bool	AlignmentPacketBase::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,SourceID)==false){
		return false;
	}
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,Calculated)==false){
		return false;
	}
	return true;
}
bool	AlignmentPacketBase::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,SourceID)==false){
		return false;
	}
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,Calculated)==false){
		return false;
	}
	return true;
}

bool	AlignmentPacket2D::Save(QIODevice *f)
{
	if(AlignmentPacketBase::Save(f)==false){
		return false;
	}
	if(::Save(f,PosXOnTarget)==false){
		return false;
	}
	if(::Save(f,PosYOnTarget)==false){
		return false;
	}
	if(::Save(f,ShiftX)==false){
		return false;
	}
	if(::Save(f,ShiftY)==false){
		return false;
	}
	if(::Save(f,Rotation)==false){
		return false;
	}
	if(::Save(f,Priority)==false){
		return false;
	}
	return false;
}
bool	AlignmentPacket2D::Load(QIODevice *f)
{
	if(AlignmentPacketBase::Load(f)==false){
		return false;
	}
	if(::Load(f,PosXOnTarget)==false){
		return false;
	}
	if(::Load(f,PosYOnTarget)==false){
		return false;
	}
	if(::Load(f,ShiftX)==false){
		return false;
	}
	if(::Load(f,ShiftY)==false){
		return false;
	}
	if(::Load(f,Rotation)==false){
		return false;
	}
	if(::Load(f,Priority)==false){
		return false;
	}
	return false;
}

//========================================================================================

class	CmdAlgorithmItemCreatePacket: public GUIDirectMessage
{
public:
	AlgorithmItemRoot	*Item;

	CmdAlgorithmItemCreatePacket(LayersBase *base):GUIDirectMessage(base),Item(NULL){}
};


//========================================================================================
SubtractItem::SubtractItem(const SubtractItem &src)
{
	ItemID			=src.ItemID;
	LibID			=src.LibID;
	IndexAfterEdit	=src.IndexAfterEdit;
}

bool    SubtractItem::Save(QIODevice *file)
{
	if(::Save(file,ItemID)==false){
		return false;
	}
	if(::Save(file,LibID)==false){
		return false;
	}
	return true;
}
bool    SubtractItem::Load(QIODevice *file)
{
	if(::Load(file,ItemID)==false){
		return false;
	}
	if(::Load(file,LibID)==false){
		return false;
	}
	return true;
}

SubtractItemContainer::SubtractItemContainer(const SubtractItemContainer &src)
{
	for(SubtractItem *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		SubtractItem	*d=new SubtractItem(*s);
		AppendList(d);
	}
}
SubtractItemContainer	&SubtractItemContainer::operator=(const SubtractItemContainer &src)
{
	for(SubtractItem *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		SubtractItem	*d=new SubtractItem(*s);
		AppendList(d);
	}
	return *this;
}
IntList	SubtractItemContainer::MakeBlockIDList(void)
{
	IntList	Ret;
	for(SubtractItem *s=GetFirst();s!=NULL;s=s->GetNext()){
		Ret.Add(s->ItemID);
	}
	return Ret;
}

//=====================================================================

bool	AlgorithmItemCountInPage::Save(QIODevice *f)
{
	if(CountInLayer.Save(f)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemCountInPage::Load(QIODevice *f)
{
	if(CountInLayer.Load(f)==false){
		return false;
	}
	return true;
}

AlgorithmItemCountInBase	&AlgorithmItemCountInBase::operator=(const AlgorithmItemCountInBase &src)
{
	CountInPage.RemoveAll();
	for(AlgorithmItemCountInPage *a=src.CountInPage.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemCountInPage *b=new AlgorithmItemCountInPage();
		*b=*a;
		CountInPage.AppendList(b);
	}
	AlgoRoot	=src.AlgoRoot;
	AlgoName	=src.AlgoName;
	return *this;
}
bool	AlgorithmItemCountInBase::Save(QIODevice *f)
{
	int32	N=CountInPage.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmItemCountInPage *p=CountInPage.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemCountInBase::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	CountInPage.RemoveAll();
	for(int i=0;i<N;i++){
		AlgorithmItemCountInPage *p=new AlgorithmItemCountInPage();
		if(p->Load(f)==false){
			return false;
		}
		CountInPage.AppendList(p);
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;
}

//=====================================================================
AlgorithmItemPropertyBase::AlgorithmItemPropertyBase(LayersBase *base)
:ServiceForLayers(base)
{
	LibID= -1;
}
AlgorithmItemPropertyBase::~AlgorithmItemPropertyBase(void)
{}
bool	AlgorithmItemPropertyBase::Save(QIODevice *f)
{
	if(ParamBase::SaveParam(f)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,DLLRoot)==false){
		return false;
	}
	if(::Save(f,DLLName)==false){
		return false;
	}
	if(::Save(f,ItemPage)==false){
		return false;
	}
	if(::Save(f,Itemlayer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemPropertyBase::Load(QIODevice *f)
{
	if(ParamBase::LoadParam(f)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	if(::Load(f,ItemPage)==false){
		return false;
	}
	if(::Load(f,Itemlayer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}


AlgorithmItemPropertyContainer	&AlgorithmItemPropertyContainer::operator=(const AlgorithmItemPropertyContainer &src)
{
	RemoveAll();
	for(AlgorithmItemPropertyBase *b=src.GetFirst();b!=NULL;b=b->GetNext()){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		b->Save(&Buff);
		Buff.seek(0);
		AlgorithmItemPropertyBase *c=b->Create();
		c->Load(&Buff);
		AppendList(c);
	}
	return *this;
}
AlgorithmParentFromItem::~AlgorithmParentFromItem(void)
{
	delete	[]ItemDimPointer;
	ItemDimPointer=NULL;
	ItemDimPointerNumb=0;

	if(AnyData!=NULL){
		delete	AnyData;
		AnyData=NULL;
	}
}
class	DummyItem	:public AlgorithmItemRoot
{
public:
	DummyItem(void){}

	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return NULL;	}
	virtual	void	CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)	override{}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DummyItem();	}

	virtual	ResultInItemRoot	*GetResult(ResultInPageRoot *Rp)	override{	return NULL;	}
	virtual	void	SetParentVirtual(AlgorithmParentFromItem *parent)	override{}
	virtual	void		SetItemID(void)									override{}
	virtual	XYData						GetOutlineOffset(void)			override;
	virtual	AlgorithmBase				*GetParentBase(void)				const	override{	return NULL;	}
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override{	return NULL;	}
	virtual	AlgorithmInPageRoot			*GetParentInPage(void)				const	override{	return NULL;	}
	virtual	AlgorithmInLayerRoot		*GetParentInLayer(void)				const	override{	return NULL;	}
	virtual	AlgorithmParentFromItem		*GetParentAlgorithm(void)			const	override{	return NULL;	}
 
	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)									override{	return false;	}
	virtual	bool	SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)	override{	return true;	}
	virtual	AlgorithmThreshold	*GetThresholdDummy(void)												override{	return NULL;	}

	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override{	return true;	}
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL)								override{	return true;	}
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)							override{	return true;	}
};

inline	XYData	DummyItem::GetOutlineOffset(void)
{
	XYData	d;
	return d;
}

static	int	SortAlgorithmItemRootFunc(const void *a ,const void *b)
{
	AlgorithmItemRoot	*pa=((AlgorithmItemRoot **)a)[0];
	AlgorithmItemRoot	*pb=((AlgorithmItemRoot **)b)[0];
	int	d=pa->GetID()-pb->GetID();
	return d;
}

void	AlgorithmParentFromItem::SortDimPointer(void)
{
	QSort(ItemDimPointer,ItemDimPointerNumb,sizeof(AlgorithmItemRoot *),SortAlgorithmItemRootFunc);
}

AlgorithmItemRoot	*AlgorithmParentFromItem::FastSearchIDItem(int itemID)	const
{
	DummyItem	Key;
	AlgorithmItemRoot	*KeyPointer[1];
	KeyPointer[0]=&Key;

	Key.SetID(itemID);
	AlgorithmItemRoot	**k=(AlgorithmItemRoot	**)EqualSearch(KeyPointer ,ItemDimPointer,ItemDimPointerNumb,sizeof(AlgorithmItemRoot *),SortAlgorithmItemRootFunc);
	if(k!=NULL){
		return *k;
	}
	return NULL;
}

//=====================================================================
ItemSearchGroup::ItemPointerList::ItemPointerList(void)
{	
	ItemPointer	=NULL;
	ItemID		=-1;
}
ItemSearchGroup::ItemPointerList::ItemPointerList(AlgorithmItemRoot *item)
{	
	ItemPointer=item;
	if(item==NULL){
		ItemID=-1;
	}
	else{
		ItemID=item->GetID();
	}
}

bool	ItemSearchGroup::ItemPointerList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}

bool	ItemSearchGroup::ItemPointerList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}


ItemSearchGroup::ItemSearchGroup(void)
{
	SearchID	=-1;
	SearchDot	=0;
}
	
bool	ItemSearchGroup::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,SearchID)==false){
		return false;
	}
	if(::Save(f,SearchDot)==false){
		return false;
	}
	int32	N=Items.GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	ItemSearchGroup::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,SearchID)==false){
		return false;
	}
	if(::Load(f,SearchDot)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Items.RemoveAll();
	for(int i=0;i<N;i++){
		ItemPointerList *a=new ItemPointerList();
		if(a->Load(f)==false){
			return false;
		}
		Items.AppendList(a);
	}
	return true;
}

void	ItemSearchGroup::ClearAllItems(void)
{
	Items.RemoveAll();
}

void	ItemSearchGroup::AppendItem(AlgorithmItemRoot *item)
{
	ItemPointerList *a=new ItemPointerList(item);
	Items.AppendList(a);
}


bool	ItemSearchGroupContainer::SaveGroup(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}

	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemSearchGroup *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	ItemSearchGroupContainer::LoadGroup(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}

	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ItemSearchGroup *a=new ItemSearchGroup();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//=====================================================================

AlgorithmItemRoot::AlgorithmItemRoot(void)
	:ThresholdStocker(this)
{
	ItemID				= -1;
	PartsID				= -1;			// ピン番号
    PartsAllocID		= -1;       //部品配置ＩＤ
    PartsItemID			= -1;
	CalcDone			=false;
	ProcessDone			=false;
	Changed				=true;
	LibID				= -1;
	EditLocked			=false;
	Effective			=true;
	Selected			=false;
	Active				=false;
	Visible				=true;
	InvertLogic			=false;
	FromRental			=false;
	CalcEnable			=true;
	MultiSelection		=false;
	ResultInThisTime	=NULL;
	Editable			=true;
	ManualCreated		=false;
	LoadedVersion		=0;
	ModeReferedAttr		=false;
	LastMakeHistgramData=false;
	ThroughAllPhases	=false;
	VBase				=NULL;
	Origin				=NULL;
	NGTypePoint			=NULL;
	MasterNo			=0;
	ThresholdStockerPointer	=&ThresholdStocker;
	GeneratedOrigin		=_OriginType_FromUnknown;
}
AlgorithmItemRoot::AlgorithmItemRoot(FlexArea &area)
	:ThresholdStocker(this)
{
	ItemID				= -1;
    PartsID				= -1;			// ピン番号
    PartsAllocID		= -1;       //部品配置ＩＤ
    PartsItemID			= -1;
	CalcDone			=false;
	ProcessDone			=false;
	Changed				=true;
	LibID				= -1;
	EditLocked			=false;
	Effective			=true;
	Selected			=false;
	Active				=false;
	Visible				=true;
	InvertLogic			=false;
	FromRental			=false;
	ResultInThisTime	=NULL;
	Editable			=true;
	ManualCreated		=false;
	ModeReferedAttr		=false;
	LastMakeHistgramData=false;
	ThroughAllPhases	=false;
	CalcEnable			=true;
	MultiSelection		=false;
	MasterNo			=0;
	SetArea(area);
	VBase				=NULL;
	Origin				=NULL;
	NGTypePoint			=NULL;
	ThresholdStockerPointer	=&ThresholdStocker;
	GeneratedOrigin		=_OriginType_FromUnknown;
}
AlgorithmItemRoot::AlgorithmItemRoot(FlexArea *area)
	:ThresholdStocker(this)
{
	ItemID				= -1;
    PartsID				= -1;			// ピン番号
    PartsAllocID		= -1;       //部品配置ＩＤ
    PartsItemID			= -1;
	CalcDone			=false;
	ProcessDone			=false;
	Changed				=true;
	LibID				= -1;
	EditLocked			=false;
	Effective			=true;
	Selected			=false;
	Active				=false;
	Visible				=true;
	InvertLogic			=false;
	FromRental			=false;
	CalcEnable			=true;
	MultiSelection		=false;
	ResultInThisTime	=NULL;
	Editable			=true;
	ManualCreated		=false;
	ModeReferedAttr		=false;
	LastMakeHistgramData=false;
	ThroughAllPhases	=false;
	MasterNo			=0;
	MoveAreaPointer	(area);
	VBase				=NULL;
	Origin				=NULL;
	NGTypePoint			=NULL;
	ThresholdStockerPointer	=&ThresholdStocker;
	GeneratedOrigin		=_OriginType_FromUnknown;
}

AlgorithmItemRoot::~AlgorithmItemRoot(void)
{
	if(ResultInThisTime!=NULL){
		ResultInThisTime->SetAlgorithmItem(NULL);
	}
	ResultInThisTime=NULL;
	if(VBase!=NULL){
		delete	VBase;
		VBase=NULL;
	}
}

FlexArea	&AlgorithmItemRoot::GetArea(void)				
{	
	return Area;
}
const FlexArea	&AlgorithmItemRoot::GetArea(void)	const
{
	return Area;
}
void		AlgorithmItemRoot::SetArea(const FlexArea &area)
{	
	if(Editable==true){	
		Area=area;
		Changed=true;
		CalcDone=false;
	}
}
bool	AlgorithmItemRoot::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const
{	
	if(GetArea().IsNull()==false){
		return GetArea().GetXY(x1,y1,x2,y2);
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		return GetVector()->GetXY(x1,y1,x2,y2);
	}
	return false;
}
bool	AlgorithmItemRoot::GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)const
{
	if(GetArea().IsNull()==false){
		int	ix1,iy1,ix2,iy2;
		bool	ret=GetArea().GetXY(ix1,iy1,ix2,iy2);
		x1=ix1;
		y1=iy1;
		x2=ix2;
		y2=iy2;
		return ret;
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		return GetVector()->GetXY(x1,y1,x2,y2);
	}
	return false;
}
bool	AlgorithmItemRoot::ReallocateMasterCount(int CountMaster)
{	
	return true;
}
void	AlgorithmItemRoot::MoveAreaPointer(FlexArea *area)
{
	if(Editable==true){	
		Area.SuckFrom(*area);
		Changed=true;
		CalcDone=false;
	}
}
FlexArea	AlgorithmItemRoot::GetInspectedArea(void)
{
	return GetArea();
}

bool		AlgorithmItemRoot::IsEffective(void)	const
{	
	return Effective;
}
void		AlgorithmItemRoot::SetEffective(bool effective)
{	
	Effective=effective;
}

void	AlgorithmItemRoot::SetVector(VectorLineBase &src)
{
	if(VBase!=NULL){
		delete	VBase;
	}
	int	id=src.GetID();
	VBase=VectorLineBase::Create(id);
	*VBase=src;
}
void	AlgorithmItemRoot::SetVector(VectorLineBase *src)
{
	if(VBase!=NULL){
		delete	VBase;
	}
	VBase=src;
}
bool	AlgorithmItemRoot::GetCenter(int &cx ,int &cy)			const
{	
	if(GetArea().IsNull()==false){
		GetArea().GetCenter(cx,cy);
		return true;
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		GetVector()->GetCenter(cx,cy);
		return true;
	}
	return false;
}
bool	AlgorithmItemRoot::GetCenter(double &cx ,double &cy)	const
{	
	if(GetArea().IsNull()==false){
		GetArea().GetCenter(cx,cy);
		return true;
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		GetVector()->GetCenter(cx,cy);
		return true;
	}
	return false;
}
bool	AlgorithmItemRoot::CheckInAreaAfterShift(int mx ,int my ,int MerginX,int MerginY)
{
	int	x1=GetArea().GetMinX()+mx;
	int	y1=GetArea().GetMinY()+my;
	int	x2=GetArea().GetMaxX()+mx;
	int	y2=GetArea().GetMaxY()+my;
	if(MerginX<=x1 && x2<GetDotPerLine()-MerginX
	&& MerginY<=y1 && y2<GetMaxLines()-MerginY){
		return true;
	}
	return false;
}

struct	AlgorithmItemRootStructVer11
{
	bool	Editable;			//部品から生成されたようなときの編集可?属性
	bool	ManualCreated;
	int64	ItemID;				//無設定時 -1
	int64	LibID;
	int32	PartsID;			//部品番号		無設定時 -1
	int32	PartsAllocID;       //部品配置ＩＤ
	int32	PartsItemID;
	int32	SearchGroupID;		//探索グル?プ??無設定時?１
	bool	ModeReferedAttr;	//部品由来のデ??のときtrue
	bool	VBaseExist;
	int32	CountOfSubBlock;
	bool	EnabledThreshold;
	bool	BLocked;
	bool	OriginMode;
	WORD	CreatedVer;

	bool	Effective:1;
	bool	Selected:1;
	bool	Active:1;
	bool	EditLocked:1;
	bool	Visible:1;
	bool	InvertLogic:1;
	bool	FromRental:1;
	bool	CalcEnable:1;
};

struct	AlgorithmItemRootStructVer14
{
	int64	ItemID;				//無設定時 -1
	int64	LibID;
	int32	PartsID;			//部品番号		無設定時 -1
	int32	PartsAllocID;       //部品配置ＩＤ
	int32	PartsItemID;
	int32	SearchGroupID;		//探索グル?プ??無設定時?１
	int32	CountOfSubBlock;
	WORD	CreatedVer;
	short	OType;

	bool	Editable		:1;	//部品から生成されたようなときの編集可?属性
	bool	ManualCreated	:1;
	bool	ModeReferedAttr	:1;	//部品由来のデ??のときtrue
	bool	VBaseExist		:1;
	bool	BLocked			:1;
	bool	OriginMode		:1;

	bool	Effective:1;
	bool	Selected:1;
	bool	Active:1;
	bool	EditLocked:1;
	bool	Visible:1;
	bool	InvertLogic:1;
	bool	FromRental:1;
	bool	CalcEnable:1;
};
#pragma	pack(push,1)
struct	AlgorithmItemRootStructVer15
{
	int64	ItemID;				//無設定時 -1
	int64	LibID;
	int32	PartsID;			//部品番号		無設定時 -1
	int32	PartsAllocID;       //部品配置ＩＤ
	int32	PartsItemID;
	int32	SearchGroupID;		//探索グル?プ??無設定時?１
	int32	CountOfSubBlock;
	int32	MasterNo;
	WORD	CreatedVer;
	short	OType;

	bool	Editable		:1;	//部品から生成されたようなときの編集可?属性
	bool	ManualCreated	:1;
	bool	ModeReferedAttr	:1;	//部品由来のデ??のときtrue
	bool	VBaseExist		:1;
	bool	BLocked			:1;
	bool	OriginMode		:1;

	bool	Effective:1;
	bool	Selected:1;
	bool	Active:1;
	bool	EditLocked:1;
	bool	Visible:1;
	bool	InvertLogic:1;
	bool	FromRental:1;
	bool	CalcEnable:1;
	bool	ThroughAllPhases:1;
};
#pragma	pack(pop)

bool    AlgorithmItemRoot::Save(QIODevice *f)
{
	int32	Ver=18;

	if(::Save(f,Ver)==false){
		return false;
	}

	struct	AlgorithmItemRootStructVer15	ItemData15;

	ItemData15.Editable			=Editable;
	ItemData15.ManualCreated	=ManualCreated;
	ItemData15.ItemID			=ItemID;
	ItemData15.LibID			=LibID;
	ItemData15.PartsID			=PartsID;
	ItemData15.PartsAllocID		=PartsAllocID;
	ItemData15.PartsItemID		=PartsItemID;
	ItemData15.SearchGroupID	=-1;
	ItemData15.ModeReferedAttr	=ModeReferedAttr;
	ItemData15.VBaseExist		=(VBase==NULL)?false:true;
	ItemData15.CountOfSubBlock	=SubBlock.GetCount();
	ItemData15.MasterNo			=MasterNo;
	ItemData15.BLocked			=GetEditLocked();
	ItemData15.OriginMode		=(Origin!=NULL)?true:false;

	ItemData15.Effective		=Effective;
	ItemData15.Selected			=Selected;
	ItemData15.Active			=Active;
	ItemData15.EditLocked		=EditLocked;
	ItemData15.Visible			=Visible;
	ItemData15.InvertLogic		=InvertLogic;
	ItemData15.FromRental		=FromRental;
	ItemData15.CalcEnable		=CalcEnable;
	ItemData15.ThroughAllPhases	=ThroughAllPhases;

	ItemData15.OType			=(short)GeneratedOrigin;
	ItemData15.CreatedVer=0xFFFF;
	if(GetParentBase()!=NULL && GetParentBase()->GetLogicDLL()!=NULL){
		ItemData15.CreatedVer=GetParentBase()->GetLogicDLL()->GetVer();
	}

	if(f->write((const char *)&ItemData15,sizeof(ItemData15))!=sizeof(ItemData15))
		return false;

	if(Area.Write(f)==false){
		return(false);
	}
	if(VBase!=NULL){
		if(VBase->Save(f)==false){
			return false;
		}
	}
	FlexArea	FLineSubtractDummy;
	if(FLineSubtractDummy.Write(f)==false){
		return(false);
	}
	for(SubtractItem *a=SubBlock.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	if(ThresholdStocker.SaveWithThreshold(f)==false){
		return false;
	}
	if(ThresholdStocker.SaveMember(f)==false){
		return false;
	}

	if(Origin!=NULL){
		QString	DLLRoot;
		QString	DLLName;
		if(Origin->GetDLLName(DLLRoot,DLLName)==true){
			if(::Save(f,DLLRoot)==false){
				return false;
			}
			if(::Save(f,DLLName)==false){
				return false;
			}
		}
		else{
			return false;
		}
	}
	if(::Save(f,ItemName)==false)
		return false;

	return(true);
}
bool    AlgorithmItemRoot::Load(QIODevice *f ,LayersBase *LBase)
{
	if(::Load(f,LoadedVersion)==false){
		return false;
	}

	if(LoadedVersion<=10){
		if(::Load(f,ItemID)==false){
			return false;
		}
		if(::Load(f,PartsID)==false){
			return false;
		}
		if(::Load(f,PartsAllocID)==false){
			return false;
		}
		if(::Load(f,PartsItemID)==false){
			return false;
		}
		if(::Load(f,LibID)==false){
			return false;
		}
		if(Area.Read(f)==false){
			return(false);
		}

		if(LoadedVersion>=3){
			bool	VectEnable;
			if(::Load(f,VectEnable)==false){
				return false;
			}
			if(VectEnable==true){
				if(VBase!=NULL){
					delete	VBase;
				}
				VBase=CreateVectorBase();
				if(VBase==NULL){
					std::cout << /**/"This class needs virtual CreateVectorBase() function" << std::endl;
					return false;
				}
				if(VBase->Load(f)==false){
					return false;
				}
			}
			else{
				if(VBase!=NULL){
					delete	VBase;
				}
				VBase=NULL;
			}
		}
		FlexArea	FLineSubtractDummy;
		if(FLineSubtractDummy.Read(f)==false){
			return(false);
		}

		SubBlock.RemoveAll();
		int32	N;
		if(::Load(f,N)==false){
			return false;
		}
		for(int i=0;i<N;i++){
			SubtractItem *a=new SubtractItem();
			if(a->Load(f)==false){
				return false;
			}
			SubBlock.AppendList(a);
		}
		if(LoadedVersion>=2){
			bool	tEditable;
			if(::Load(f,tEditable)==false){
				return false;
			}
			Editable=tEditable;
			bool	tModeReferedAttr;
			if(::Load(f,tModeReferedAttr)==false){
				return false;
			}
			ModeReferedAttr=tModeReferedAttr;
			if(LoadedVersion>=4){
				bool	EnabledThreshold;
				if(::Load(f,EnabledThreshold)==false){
					return false;
				}
				if(EnabledThreshold==true){
					AlgorithmThreshold	*Threshold=CreateThresholdInstance();
					if(Threshold->Load(f)==false){
						return false;
					}
					Threshold->SetThresholdLevelID(LBase->GetThresholdLevelID());
					ThresholdStocker.AppendList(Threshold);
				}
			}
			else{
				AlgorithmThreshold	*Threshold=GetThresholdBaseWritable();
				if(Threshold==NULL){
					Threshold=CreateThresholdInstance();
					ThresholdStocker.AppendList(Threshold);
				}
				if(Threshold->Load(f)==false){
					return false;
				}
				Threshold->SetThresholdLevelID(LBase->GetThresholdLevelID());
				for(AlgorithmThreshold *s=ThresholdStocker.GetFirst();s!=NULL;s=s->GetNext()){
					if(s!=Threshold){
						s->CopyFrom(*Threshold);
					}
				}
			}
		}
		if(LoadedVersion>=6){
			bool	BLocked;
			if(::Load(f,BLocked)==false){
				return false;
			}
			SetEditLocked(BLocked);
		}
		if(LoadedVersion>=7){
			bool	BOrigin;
			if(::Load(f,BOrigin)==false){
				return false;
			}
			if(BOrigin==true){
				QString	DLLRoot;
				QString	DLLName;
				if(::Load(f,DLLRoot)==false){
					return false;
				}
				if(::Load(f,DLLName)==false){
					return false;
				}
				Origin=LBase->GetAlgorithmBase(DLLRoot,DLLName);
			}
			else{
				Origin=NULL;
			}
			bool	tManualCreated;
			if(::Load(f,tManualCreated)==false){
				return false;
			}
			ManualCreated=tManualCreated;
		}
		if(LoadedVersion>=8){
			bool	gInvertLogic;
			if(::Load(f,gInvertLogic)==false){
				return false;
			}
			InvertLogic=gInvertLogic;
		}
		int32	iSearchGroupID=-1;
		if(LoadedVersion>=9){
			if(::Load(f,iSearchGroupID)==false){
				return false;
			}
		}

		if(LoadedVersion>=10){
			WORD	CreatedVer;
			if(::Load(f,CreatedVer)==false){
				return false;
			}
			if(GetParentBase()!=NULL){
				GetParentBase()->SetLoadedVersion(CreatedVer);
			}
		}
		MasterNo=0;
	}
	else if(LoadedVersion>=11 && LoadedVersion<14){
		struct	AlgorithmItemRootStructVer11	ItemData11;
		if(f->read((char *)&ItemData11,sizeof(ItemData11))!=sizeof(ItemData11))
			return false;

		Editable		=ItemData11.Editable			;
		ManualCreated	=ItemData11.ManualCreated;
		ItemID			=ItemData11.ItemID		;
		LibID			=ItemData11.LibID		;
		PartsID			=ItemData11.PartsID		;
		PartsAllocID	=ItemData11.PartsAllocID;
		PartsItemID		=ItemData11.PartsItemID	;
		ModeReferedAttr	=ItemData11.ModeReferedAttr;

		Effective		=ItemData11.Effective	;
		Selected		=ItemData11.Selected	;
		Active			=ItemData11.Active		;
		EditLocked		=ItemData11.EditLocked	;
		InvertLogic		=ItemData11.InvertLogic	;
		FromRental		=ItemData11.FromRental	;
		CalcEnable		=ItemData11.CalcEnable	;
		MasterNo=0;
		if(Area.Read(f)==false){
			return(false);
		}

		if(ItemData11.VBaseExist==true){
			if(VBase!=NULL){
				delete	VBase;
			}
			VBase=CreateVectorBase();
			if(VBase==NULL){
				std::cout << /**/"This class needs virtual CreateVectorBase() function" << std::endl;
				return false;
			}
			if(VBase->Load(f)==false){
				return false;
			}
		}
		else if(VBase!=NULL){
			delete	VBase;
			VBase=NULL;
		}
		FlexArea	FLineSubtractDummy;
		if(FLineSubtractDummy.Read(f)==false){
			return(false);
		}
		SubBlock.RemoveAll();

		for(int i=0;i<ItemData11.CountOfSubBlock;i++){
			SubtractItem *a=new SubtractItem();
			if(a->Load(f)==false){
				return false;
			}
			SubBlock.AppendList(a);
		}
		if(ItemData11.EnabledThreshold==true){
			AlgorithmThreshold	*Threshold=GetThresholdBaseWritable();
			if(Threshold->Load(f)==false){
				return false;
			}
			Threshold->SetThresholdLevelID(LBase->GetThresholdLevelID());
			for(AlgorithmThreshold *s=ThresholdStocker.GetFirst();s!=NULL;s=s->GetNext()){
				if(s!=Threshold){
					s->CopyFrom(*Threshold);
				}
			}
		}

		SetEditLocked(ItemData11.BLocked);

		if(ItemData11.OriginMode==true){
			QString	DLLRoot;
			QString	DLLName;
			if(::Load(f,DLLRoot)==false){
				return false;
			}
			if(::Load(f,DLLName)==false){
				return false;
			}
			Origin=LBase->GetAlgorithmBase(DLLRoot,DLLName);
		}
		else{
			Origin=NULL;
		}
		if(LoadedVersion>=12){
			if(::Load(f,ItemName)==false){
				return false;
			}
		}

		if(GetParentBase()!=NULL){
			GetParentBase()->SetLoadedVersion(ItemData11.CreatedVer);
		}
		if(LoadedVersion>=13){
			short	OType;
			if(::Load(f,OType)==false){
				return false;
			}
			GeneratedOrigin=(OriginType)OType;
		}
	}
	else if(LoadedVersion==14){
		struct	AlgorithmItemRootStructVer14	ItemData14;
		if(f->read((char *)&ItemData14,sizeof(ItemData14))!=sizeof(ItemData14))
			return false;

		Editable		=ItemData14.Editable	;
		ManualCreated	=ItemData14.ManualCreated;
		ItemID			=ItemData14.ItemID		;
		LibID			=ItemData14.LibID		;
		PartsID			=ItemData14.PartsID		;
		PartsAllocID	=ItemData14.PartsAllocID;
		PartsItemID		=ItemData14.PartsItemID	;
		ModeReferedAttr	=ItemData14.ModeReferedAttr;

		Effective		=ItemData14.Effective	;
		Selected		=ItemData14.Selected	;
		Active			=ItemData14.Active		;
		EditLocked		=ItemData14.EditLocked	;
		InvertLogic		=ItemData14.InvertLogic	;
		FromRental		=ItemData14.FromRental	;
		CalcEnable		=ItemData14.CalcEnable	;
		GeneratedOrigin	=(OriginType)ItemData14.OType;
		MasterNo		=0;
		if(Area.Read(f)==false){
			return(false);
		}
		if(ItemData14.VBaseExist==true){
			if(VBase!=NULL){
				delete	VBase;
			}
			VBase=CreateVectorBase();
			if(VBase==NULL){
				std::cout << /**/"This class needs virtual CreateVectorBase() function" << std::endl;
				return false;
			}
			if(VBase->Load(f)==false){
				return false;
			}
		}
		else if(VBase!=NULL){
			delete	VBase;
			VBase=NULL;
		}
		FlexArea	FLineSubtractDummy;
		if(FLineSubtractDummy.Read(f)==false){
			return(false);
		}
		SubBlock.RemoveAll();

		for(int i=0;i<ItemData14.CountOfSubBlock;i++){
			SubtractItem *a=new SubtractItem();
			if(a->Load(f)==false){
				return false;
			}
			SubBlock.AppendList(a);
		}
		if(ThresholdStocker.Load(f)==false){
			return false;
		}
		SetEditLocked(ItemData14.BLocked);

		if(ItemData14.OriginMode==true){
			QString	DLLRoot;
			QString	DLLName;
			if(::Load(f,DLLRoot)==false){
				return false;
			}
			if(::Load(f,DLLName)==false){
				return false;
			}
			Origin=LBase->GetAlgorithmBase(DLLRoot,DLLName);
		}
		else{
			Origin=NULL;
		}
		if(LoadedVersion>=12){
			if(::Load(f,ItemName)==false){
				return false;
			}
		}

		if(GetParentBase()!=NULL){
			GetParentBase()->SetLoadedVersion(ItemData14.CreatedVer);
		}
	}
	else if (LoadedVersion>=16) {
		struct	AlgorithmItemRootStructVer15	ItemData15;
		if(f->read((char *)&ItemData15,sizeof(ItemData15))!=sizeof(ItemData15))
			return false;

		Editable		=ItemData15.Editable	;
		ManualCreated	=ItemData15.ManualCreated;
		ItemID			=ItemData15.ItemID		;
		LibID			=ItemData15.LibID		;
		PartsID			=ItemData15.PartsID		;
		PartsAllocID	=ItemData15.PartsAllocID;
		PartsItemID		=ItemData15.PartsItemID	;
		ModeReferedAttr	=ItemData15.ModeReferedAttr;

		Effective		=ItemData15.Effective	;
		Selected		=ItemData15.Selected	;
		Active			=ItemData15.Active		;
		EditLocked		=ItemData15.EditLocked	;
		InvertLogic		=ItemData15.InvertLogic	;
		FromRental		=ItemData15.FromRental	;
		CalcEnable		=ItemData15.CalcEnable	;
		GeneratedOrigin	=(OriginType)ItemData15.OType;
		MasterNo		=ItemData15.MasterNo	;
		ThroughAllPhases=ItemData15.ThroughAllPhases;
		if(Area.Read(f)==false){
			return(false);
		}

		if(ItemData15.VBaseExist==true){
			if(VBase!=NULL){
				delete	VBase;
			}
			VBase=CreateVectorBase();
			if(VBase==NULL){
				std::cout << /**/"This class needs virtual CreateVectorBase() function" << std::endl;
				return false;
			}
			if(VBase->Load(f)==false){
				return false;
			}
		}
		else if(VBase!=NULL){
			delete	VBase;
			VBase=NULL;
		}
		FlexArea	FLineSubtractDummy;
		if(FLineSubtractDummy.Read(f)==false){
			return(false);
		}
		SubBlock.RemoveAll();

		for(int i=0;i<ItemData15.CountOfSubBlock;i++){
			SubtractItem *a=new SubtractItem();
			if(a->Load(f)==false){
				return false;
			}
			SubBlock.AppendList(a);
		}
		if(LoadedVersion==15){
			if(ThresholdStocker.Load(f)==false){
				return false;
			}
			if(ThresholdStocker.GetCount()==1){
				AlgorithmThreshold	*Thr=ThresholdStocker.GetFirst();
				Thr->SetThresholdLevelID(LBase->GetThresholdLevelID());
			}
		}
		else if(LoadedVersion>=16){
			if(ThresholdStocker.LoadWithThreshold(f,LBase)==false){
				return false;
			}
		}
		if(LoadedVersion>=18){
			if(ThresholdStocker.LoadMember(f)==false){
				return false;
			}
		}

		SetEditLocked(ItemData15.BLocked);

		if(ItemData15.OriginMode==true){
			QString	DLLRoot;
			QString	DLLName;
			if(::Load(f,DLLRoot)==false){
				return false;
			}
			if(::Load(f,DLLName)==false){
				return false;
			}
			Origin=LBase->GetAlgorithmBase(DLLRoot,DLLName);
		}
		else{
			Origin=NULL;
		}
		if(LoadedVersion>=12){
			if(::Load(f,ItemName)==false){
				return false;
			}
		}

		if(GetParentBase()!=NULL){
			GetParentBase()->SetLoadedVersion(ItemData15.CreatedVer);
		}
	}
	if(LoadedVersion<17){
		ThroughAllPhases=false;
	}

	Changed=true;
	CalcDone=false;
	return(true);
}
bool	AlgorithmItemRoot::Transform(TransformBase &Param)
{
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);

	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	
	return true;
}
bool	AlgorithmItemRoot::IsValid(void)
{
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	if(x1<0 || x1>x2 || GetDotPerLine()<=x2
	|| y1<0 || y1>y2 || GetMaxLines()<=y2){
		if(HasVector()==true){
			if(GetVector()->GetLength()>0.0){
				return true;
			}
		}
		return false;
	}
	return true;
}
AlgorithmItemIndex	AlgorithmItemRoot::GetIndex(void)
{
	AlgorithmItemIndex	Index(*this);
	return Index;
}
int		AlgorithmItemRoot::GetGlobalPage(void)
{
	return GetLayersBase()->GetGlobalPageFromLocal(GetPage());
}
	
bool	AlgorithmItemRoot::SaveHistgram(QIODevice *f)
{
	return GetThresholdBaseWritable()->SaveHistgram(f);
}

bool	AlgorithmItemRoot::LoadHistgram(QIODevice *f)
{
	return GetThresholdBaseWritable()->LoadHistgram(f);
}

bool	AlgorithmItemRoot::IsCrossed(int x1, int y1 ,int x2, int y2)const
{
	if(GetArea().IsNull()==false){
		return GetArea().CheckOverlapRectangle(x1,y1,x2,y2);
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		return GetVector()->CheckOverlapRectangle(x1,y1,x2,y2);
	}
	return false;
}
int		AlgorithmItemRoot::GetPhaseCode(void)	const
{
	return GetAlgorithmInPageInOnePhase()->GetPhaseCode();
}

bool	AlgorithmItemRoot::SaveForLearning(QIODevice *f)
{
	return Save(f);
}

bool	AlgorithmItemRoot::LoadForLearning(QIODevice *f,LayersBase *LBase)
{
	return Load(f,LBase);
}

void	AlgorithmItemRoot::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	AlgorithmItemRoot::SetNewThresholdInstance(LayersBase *base ,int __ThresholdLevelID)
{
	if(base==NULL){
		base=GetLayersBase();
	}
	int	ThresholdLevel;
	if(__ThresholdLevelID<0){
		ThresholdLevel=(base!=NULL)?base->GetThresholdLevelID():0;
	}
	else{
		ThresholdLevel=__ThresholdLevelID;
	}
	if(ThresholdLevel<=0){
		if(ThresholdStocker.GetCount()==0){
			AlgorithmThreshold	*Threshold=CreateThresholdInstance();
			Threshold->SetThresholdLevelID(ThresholdLevel);
			ThresholdStocker.AppendList(Threshold);
		}
	}
	else{
		while(ThresholdStocker.GetAlgorithmThreshold(ThresholdLevel)==NULL){
			AlgorithmThreshold	*Threshold=CreateThresholdInstance();
			Threshold->SetThresholdLevelID(ThresholdLevel);
			ThresholdStocker.AppendList(Threshold);
		}
	}
}
AlgorithmThreshold			*AlgorithmItemRoot::GetThresholdBaseWritable(LayersBase *base,int ThresholdLevelID)	
{
	if(base==NULL){
		base=GetLayersBase();
	}
	if(ThresholdLevelID<0){
		ThresholdLevelID=(base!=NULL)?base->GetThresholdLevelID():0;
	}
	if((ModeReferedAttr==false) || (GetParamGlobal()==NULL) || (GetParamGlobal()->ChangeThresholdFromPartsOrigin==true)){
		AlgorithmThreshold	*r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
		bool	CreatedMode=false;
		if(r==NULL){
			SetNewThresholdInstance(base,ThresholdLevelID);
			r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
			CreatedMode=true;
		}
		if(r==NULL){
			AlgorithmThreshold	*Threshold=CreateThresholdInstance();
			Threshold->SetThresholdLevelID((ThresholdLevelID>=0)?ThresholdLevelID:0);
			ThresholdStocker.AppendList(Threshold);
			r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
		}
		if(CreatedMode==true && r!=NULL){
			AlgorithmThreshold	*Src=ThresholdStockerPointer->GetFirst();
			r->CopyFrom(*Src);
		}
		return r;
	}	
	else{
		return GetThresholdDummy();
	}
}
const	AlgorithmThreshold	*AlgorithmItemRoot::GetThresholdBaseReadable(LayersBase *base,int ThresholdLevelID)	
{		
	if(base==NULL){
		base=GetLayersBase();
	}
	if(ThresholdLevelID<0){
		ThresholdLevelID=(base!=NULL)?base->GetThresholdLevelID():0;
	}
	AlgorithmThreshold	*r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
	if(r==NULL){
		SetNewThresholdInstance(base,ThresholdLevelID);
		r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
	}
	if(r==NULL){
		AlgorithmThreshold	*Threshold=CreateThresholdInstance();
		Threshold->SetThresholdLevelID((ThresholdLevelID>=0)?ThresholdLevelID:0);
		ThresholdStocker.AppendList(Threshold);
		r=ThresholdStockerPointer->GetAlgorithmThreshold((ThresholdLevelID>=0)?ThresholdLevelID:0);
	}
	return r;
}
void	AlgorithmItemRoot::SwitchThresholdLevel(int OldLevelID ,int NewLevelID)
{
	if(ThresholdStockerPointer==&ThresholdStocker){
		if(OldLevelID<0){
			OldLevelID=0;
		}
		if(NewLevelID<0){
			NewLevelID=0;
		}
		AlgorithmThreshold	*w=ThresholdStockerPointer->GetItem(0);
		AlgorithmThreshold	*r;
		while((r=ThresholdStockerPointer->GetAlgorithmThreshold(NewLevelID))==NULL){
			AlgorithmThreshold	*Threshold=CreateThresholdInstance();
			ThresholdStockerPointer->AppendList(Threshold);		
			if(w!=NULL){
				Threshold->CopyFrom(*w);
				Threshold->SetThresholdLevelID(NewLevelID);
			}
		}
	}
}

void	AlgorithmItemRoot::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	if(ThresholdStockerPointer==&ThresholdStocker){
		if(SourceLevelID<0){
			SourceLevelID=0;
		}
		if(DestLevelID<0){
			DestLevelID=0;
		}
		AlgorithmThreshold	*w=ThresholdStockerPointer->GetItem(0);
		AlgorithmThreshold	*Dest;
		while((Dest=ThresholdStockerPointer->GetAlgorithmThreshold(DestLevelID))==NULL){
			AlgorithmThreshold	*Threshold=CreateThresholdInstance();
			ThresholdStockerPointer->AppendList(Threshold);		
			if(w!=NULL){
				Threshold->CopyFrom(*w);
				Threshold->SetThresholdLevelID(DestLevelID);
			}
		}
		AlgorithmThreshold	*Src=ThresholdStockerPointer->GetAlgorithmThreshold(SourceLevelID);
		if(Src!=NULL){
			Dest->CopyFrom(*Src);
			Dest->SetThresholdLevelID(DestLevelID);
		}
	}
}
void	AlgorithmItemRoot::CopyThresholdFromLibrary(AlgorithmLibraryLevelContainer *src)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase==NULL){
		if(src->GetParent()!=NULL){
			LBase=src->GetParent()->GetLayersBase();
		}
	}
	for(AlgorithmLibrary *Lib=src->GetFirst();Lib!=NULL;Lib=Lib->GetNext()){
		AlgorithmThreshold	*a=GetThresholdBaseWritable(LBase,Lib->GetThresholdLevelID());
		a->FromLibrary(Lib);
	}
}
void	AlgorithmItemRoot::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	Area.SetRefereneFrom(&src->Area);
	//Area.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
	Area.MoveToNoClip(OffsetX,OffsetY);

	if(VBase!=NULL){
		delete	VBase;
		VBase=NULL;
	}
	if(src->VBase!=NULL){
		VBase=src->CreateVectorBase();
		*VBase= *src->VBase;
	}
	if(VBase!=NULL){
		VBase->MoveTo(OffsetX,OffsetY);
	}

	ThresholdStocker	=src->ThresholdStocker;

	ModeReferedAttr	=true;
}
void	AlgorithmItemRoot::CopyAttrFrom(AlgorithmItemRoot *SrcItem)
{
	Effective		=SrcItem->Effective;
	LibID			=SrcItem->LibID;
	InvertLogic		=SrcItem->InvertLogic;
	FromRental		=SrcItem->FromRental;
	GeneratedOrigin	=SrcItem->GeneratedOrigin;

	//QBuffer	Buff;
	//Buff.open(QIODevice::ReadWrite);

	ThresholdStocker	=SrcItem->ThresholdStocker;
}

void	AlgorithmItemRoot::SetPartsData(int _PartsID ,int _PartsAllocID ,int _PartsItemID)
{
	PartsID		=_PartsID;
	PartsAllocID=_PartsAllocID;
	PartsItemID	=_PartsItemID;
}
bool	AlgorithmItemRoot::ShrinkItems(int ExpandPixels,BYTE **Mask)
{
	if(ExpandPixels>0){
		FlexArea	A=GetArea();
		A.FatAreaN(ExpandPixels);
		if(Mask!=NULL){
			int	XLen=GetDotPerLine();
			int	YLen=GetMaxLines();
			A.ClipByMask(Mask,XLen,YLen);
		}
		SetArea(A);
	}
	else if(ExpandPixels<0){
		FlexArea	A=GetArea();
		A.ThinAreaN(-ExpandPixels);
		SetArea(A);
	}
	return true;
}
AlgorithmItemRoot	&AlgorithmItemRoot::operator=(const AlgorithmItemRoot &src)
{
	LoadedVersion	=src.LoadedVersion;
	ItemID			=src.ItemID;
	PartsID			=src.PartsID;
	PartsAllocID	=src.PartsAllocID;
	PartsItemID		=src.PartsItemID;
	MasterNo		=src.MasterNo;

	if(src.Editable==true){
		Area			=src.GetArea();
		if(VBase!=NULL){
			delete	VBase;
			VBase=NULL;
		}
		if(src.VBase!=NULL){
			VBase=((AlgorithmItemRoot *)&src)->CreateVectorBase();
			*VBase= *src.VBase;
		}
	}
	if(src.IsEditable()==true){
		ThresholdStocker	=src.ThresholdStocker;
	}

	Editable		=src.Editable;
	ManualCreated	=src.ManualCreated;
	ItemName		=src.ItemName;
	if((ModeReferedAttr==false) && (src.ModeReferedAttr==false)){
		ThresholdStockerPointer=&ThresholdStocker;
	}
	else if((ModeReferedAttr==true) && (src.ModeReferedAttr==false)){
		ThresholdStockerPointer=&ThresholdStocker;
	}
	else if((ModeReferedAttr==false) && (src.ModeReferedAttr==true)){
		ThresholdStockerPointer=src.ThresholdStockerPointer;
	}
	else if((ModeReferedAttr==true) && (src.ModeReferedAttr==true)){
		ThresholdStockerPointer=src.ThresholdStockerPointer;
	}
	ModeReferedAttr	=src.ModeReferedAttr;
	LibID			=src.LibID;
	SubBlock.RemoveAll();
	for(SubtractItem *a=src.SubBlock.GetFirst();a!=NULL;a=a->GetNext()){
		SubtractItem *b=new SubtractItem();
		*b= *a;
		SubBlock.AppendList(b);
	}
	InvertLogic		=src.InvertLogic;
	FromRental		=src.FromRental;
	SetOriginType(src.GetOriginType());

	ResultInThisTime	=src.ResultInThisTime;
	Origin				=src.Origin;
	NGTypePoint			=src.NGTypePoint;

	Changed			=true;
	CalcDone		=false;
	return(*this);
}
void	AlgorithmItemRoot::CopyFrom(AlgorithmItemRoot *src)
{
	operator=(*src);
}
void	AlgorithmItemRoot::TransformCopyFrom(TransformBase &Param,const AlgorithmItemRoot &src)
{
	LoadedVersion	=src.LoadedVersion;
	ItemID			=src.ItemID;
	PartsID			=src.PartsID;
	PartsAllocID	=src.PartsAllocID;
	PartsItemID		=src.PartsItemID;
	MasterNo		=src.MasterNo;

	if(src.Editable==true){
		Area=src.GetArea();
		Area.Transform(Param);

		if(VBase!=NULL){
			delete	VBase;
			VBase=NULL;
		}
		if(src.VBase!=NULL){
			VBase=((AlgorithmItemRoot *)&src)->CreateVectorBase();
			*VBase= *src.VBase;
		}
	}
	if(src.IsEditable()==true){
		ThresholdStocker	=src.ThresholdStocker;
	}

	Editable		=src.Editable;
	ManualCreated	=src.ManualCreated;
	ItemName		=src.ItemName;
	if((ModeReferedAttr==false) && (src.ModeReferedAttr==false)){
		ThresholdStockerPointer=&ThresholdStocker;
	}
	else if((ModeReferedAttr==true) && (src.ModeReferedAttr==false)){
		ThresholdStockerPointer=&ThresholdStocker;
	}
	else if((ModeReferedAttr==false) && (src.ModeReferedAttr==true)){
		ThresholdStockerPointer=src.ThresholdStockerPointer;
	}
	else if((ModeReferedAttr==true) && (src.ModeReferedAttr==true)){
		ThresholdStockerPointer=src.ThresholdStockerPointer;
	}
	ModeReferedAttr	=src.ModeReferedAttr;
	LibID			=src.LibID;
	SubBlock.RemoveAll();
	for(SubtractItem *a=src.SubBlock.GetFirst();a!=NULL;a=a->GetNext()){
		SubtractItem *b=new SubtractItem();
		*b= *a;
		SubBlock.AppendList(b);
	}
	InvertLogic		=src.InvertLogic;
	FromRental		=src.FromRental;
	SetOriginType(src.GetOriginType());

	Changed			=true;
	CalcDone		=false;
}


void	AlgorithmBasePointerContainer::Add(AlgorithmBase *a)
{
	AppendList(new AlgorithmBasePointerList(a));
}

void	AlgorithmBasePointerContainer::Merge(AlgorithmBase *p)
{
	for(AlgorithmBasePointerList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetAlgorithmBase()==p){
			return;
		}
	}
	AlgorithmBasePointerList	*a=new AlgorithmBasePointerList(p);
	AppendList(a);
}

AlgorithmBase	*AlgorithmBasePointerContainer::FindAlgorithmBase(int LibType)
{
	for(AlgorithmBasePointerList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetAlgorithmBase()->GetLibType()==LibType){
			return a->GetAlgorithmBase();
		}
	}
	return NULL;
}


int		AlgorithmItemRoot::GetLoadedVersion(void)
{
	if(GetParentBase()==NULL){
		return -1;
	}
	return GetParentBase()->GetLoadedVersion();
}
int		AlgorithmItemRoot::GetLibType(void)	const
{
	if(GetLibraryContainer()!=NULL){
		return GetLibraryContainer()->GetLibType();
	}
	return -1;
}

bool	AlgorithmItemRoot::GetLibrary(AlgorithmLibraryLevelContainer &Dest)
{
	if(GetLibraryContainer()==NULL)
		return false;
	return GetLibraryContainer()->GetLibrary(GetLibID(),Dest);
}
AlgorithmLibraryLevelContainer	*AlgorithmItemRoot::GetLibFromManagedCacheLib(void)
{
	if(GetLibraryContainer()==NULL)
		return NULL;
	AlgorithmBase				*ABase=GetParentBase();
	if(ABase!=NULL){
		AlgorithmLibraryLevelContainer	*Lib=ABase->FindLibFromManagedCacheLib(GetLibID());
		if(Lib==NULL){
			ABase->LoadManagedCacheLib(GetLibID());
			Lib=ABase->FindLibFromManagedCacheLib(GetLibID());
		}
		if(Lib!=NULL){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	LevelID=GetLayersBase()->GetThresholdLevelID();
			AlgorithmLibrary	*SrcLib=Lib->GetLibrary(LevelID);
			if(SrcLib!=NULL){
				AlgorithmLibraryLevelContainer	*L=new AlgorithmLibraryLevelContainer(GetLibraryContainer());
				*L=*Lib;
				//AlgorithmLibrary	*a=GetLibraryContainer()->CreateNew();
				//a->SetParent(L);
				//SrcLib->Save(&Buff);
				//Buff.seek(0);
				//a->Load(&Buff);
				//a->SetThresholdLevelID(LevelID);
				//L->AppendList(a);
				return L;
			}
		}
	}
	
	return GetLibrary();
}

AlgorithmLibraryLevelContainer	*AlgorithmItemRoot::GetLibrary(void)
{
	if(GetLibraryContainer()==NULL)
		return NULL;
	AlgorithmLibraryLevelContainer	*L=new AlgorithmLibraryLevelContainer(GetLibraryContainer());
	if(GetLibrary(*L)==false){
		delete	L;
		return NULL;
	}
	return L;
}

ItemDataListWithID	*AlgorithmItemRoot::MakeItemForLearning(int AddedX,int AddedY,bool OkMode)
{
	ResultInItemRoot	*R=GetCurrentResult();
	ItemDataListWithID	*h=new ItemDataListWithID();
	QBuffer	HBuff(&h->IData);
	HBuff.open(QIODevice::WriteOnly);

	h->LibID	=GetLibID();
	h->ItemID	=GetID();
	h->ItemClassType=GetItemClassType();
	if(::Save(&HBuff,h->ItemClassType)==false){
		return NULL;
	}
	AlgorithmItemRoot *Dmy=Clone();
	QBuffer	TmpBuff;
	TmpBuff.open(QIODevice::ReadWrite);
	Save(&TmpBuff);
	TmpBuff.seek(0);
	Dmy->Load(&TmpBuff,GetLayersBase());

	if(R!=NULL){
		AddedX+=R->GetItemSearchedX();
		AddedY+=R->GetItemSearchedY();
		h->Error=R->GetError();
	}
	Dmy->MoveTo(AddedX,AddedY);
	if((OkMode==true && h->Error>=2) || OkMode==false){
		if(Dmy->SaveForLearning(&HBuff)==false){
			delete	Dmy;
			delete	h;
			return NULL;
		}
	}
	delete	Dmy;
	return h;
}

bool	AlgorithmItemRoot::IsInclude(int x ,int y)	const
{	
	if(GetArea().IsInclude(x,y)==true){
		return true;
	}
	if(VBase!=NULL){
		if(VBase->GetDistance(x,y)<10){
			return true;
		}
	}
	return false;
}

bool	AlgorithmItemRoot::IsCrossed(FlexArea *b)	const
{
	if(GetArea().IsNull()==false){
		return(GetArea().CheckOverlap(b));
	}
	else if(VBase!=NULL){
		return VBase->CheckOverlap(*b);
	}
	return false;
}

ExeResult	AlgorithmItemRoot::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	if(FromRental==false && Res!=NULL){
		if(Res->GetDotPerLine()!=0 || Res->GetMaxLines()!=0){
			GetArea().ClipArea(0,0,Res->GetDotPerLine(),Res->GetMaxLines());
		}
		else{
			GetArea().ClipArea(0,0,GetDotPerLine(),GetMaxLines());
		}
	}
	LibraryListWithNGType	*NGType=NULL;
	if(GetParentBase()!=NULL){
		NGType=GetParentBase()->GetNGTypeList(GetLibID());
		if(NGType!=NULL){
			NGTypePoint=NGType->GetLibNGTypeInAlgorithm();
		}
	}

	CalcDone=true;
	return _ER_true;
}
void	AlgorithmItemRoot::SetCurrentResult(ResultInItemRoot *d)
{	
	if(ResultInThisTime!=NULL){
		ResultInThisTime->SetAlgorithmItem(NULL);
	}
	ResultInThisTime=d;
	if(ResultInThisTime!=NULL){
		ResultInThisTime->SetAlgorithmItem(this);
		//ResultInThisTime->SetItemID(GetID());
	}
}
ListPhasePageLayerItem		AlgorithmItemRoot::GetItemIndex(void)
{
	ListPhasePageLayerItem	ItemIndex;
	ItemIndex.Data.ItemID	=GetID();
	ItemIndex.Data.Layer	=GetLayer();
	ItemIndex.Data.Page		=GetPage();
	ItemIndex.Data.Phase	=GetPhaseCode();
	return ItemIndex;
}

int		AlgorithmItemRoot::GetLayerNumb(void)	const
{	
	if(GetParentInPage()!=NULL){
		return GetParentInPage()->GetLayerNumb();
	}
	return (GetParamGlobal()==NULL)?0:GetParamGlobal()->LayerNumb;
}

ExeResult	AlgorithmItemRoot::ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	SetCurrentResult(Res);
	return _ER_true;
}

ExeResult	AlgorithmItemRoot::ExecutePostProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{	
	if(GetParamGlobal()->OutputNGCause==true){
		for(ResultPosList *p=Res->GetPosList().GetFirst();p!=NULL;p=p->GetNext()){
			LibraryListWithNGType	*L=NULL;
			if(GetParentBase()!=NULL){
				L=GetParentBase()->GetNGTypeList(GetLibID());
				if(L!=NULL){
					LibNGTypeItem	*NGItem=GetParentBase()->SearchNGCause(L,this,p);
					if(NGItem!=NULL){
						p->NGTypeUniqueCode=NGItem->TypeUniqueCode;
					}
				}
			}
		}
	}
	return _ER_true;
}

bool	AlgorithmItemRoot::CanBeProcessing(void)
{
	for(SubtractItem *sb=SubBlock.GetFirst();sb!=NULL;sb=sb->GetNext()){
		if((sb->IndexAfterEdit!=NULL)
		&& (sb->IndexAfterEdit->IsCalced()==false)){
			return false;
		}
	}
	return true;
}

void	AlgorithmItemRoot::ClearHistgram(void)
{
	GetThresholdBaseWritable()->ClearHistgram();
}

void    AlgorithmItemRoot::MoveTo(int dx ,int dy)
{
	if((Editable==true) && (Visible==true)){
		GetArea().MoveToNoClip(dx,dy);

		if(VBase!=NULL){
			VBase->MoveTo(dx,dy);
		}

		Changed		=true;
		CalcDone	=false;
	}
}
void	AlgorithmItemRoot::ClipPage(void)
{
	if(GetArea().IsNull()==false){
		if((GetArea().GetMinX()<0) || (GetDotPerLine()<=GetArea().GetMaxX())
		|| (GetArea().GetMinY()<0) || (GetMaxLines()<=GetArea().GetMaxY())){
			GetArea().ClipArea(0,0,GetDotPerLine(),GetMaxLines());
			Changed		=true;
			CalcDone	=false;
		}
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		if(GetVector()->ClipArea(0,0,GetDotPerLine(),GetMaxLines())==true){
			Changed		=true;
			CalcDone	=false;
		}
	}
}
void	AlgorithmItemRoot::ClipPage(int DotPerLine ,int MaxLines)
{
	if(GetArea().IsNull()==false){
		if((GetArea().GetMinX()<0) || (DotPerLine<=GetArea().GetMaxX())
		|| (GetArea().GetMinY()<0) || (MaxLines<=GetArea().GetMaxY())){
			GetArea().ClipArea(0,0,DotPerLine,MaxLines);
			Changed		=true;
			CalcDone	=false;
		}
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		if(GetVector()->ClipArea(0,0,DotPerLine,MaxLines)==true){
			Changed		=true;
			CalcDone	=false;
		}
	}
}

int		AlgorithmItemRoot::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100; 
}

void	AlgorithmItemRoot::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,Attr);
	DrawVector(GetVector(),pnt, movx ,movy ,ZoomRate ,Attr);
}
void	AlgorithmItemRoot::DrawArea(FlexArea &area ,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if(Attr!=NULL){
		if(GetSelected()==true){
			area.Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()
				,ZoomRate ,movx ,movy);
		}
		else if(GetActive()==true){
			area.Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()
				,ZoomRate ,movx ,movy);
		}
		else{
			area.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()
				,ZoomRate ,movx ,movy);
		}
	}
	else{
		if(GetSelected()==true){
			area.Draw(0,0 ,&pnt ,qRgba(255,255,0,80)
				,ZoomRate ,movx ,movy);
		}
		else if(GetActive()==true){
			area.Draw(0,0 ,&pnt ,qRgba(255,0,0,80)
				,ZoomRate ,movx ,movy);
		}
		else{
			area.Draw(0,0 ,&pnt ,qRgba(0,255,0,80)
				,ZoomRate ,movx ,movy);
		}

	}
}
void	AlgorithmItemRoot::DrawVector(VectorLineBase *V,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}
	if(V!=NULL){
		QPainter	P(&pnt);
		if(Attr!=NULL){
			if(Attr->LineWidth<=1){
				if(GetSelected()==true){
					P.setPen(Attr->SelectedColor);
				}
				else if(GetActive()==true){
					P.setPen(Attr->ActiveColor);
				}
				else{
					P.setPen(Attr->NormalColor);
				}
			}
			else{
				QPen	LPen;
				if(GetSelected()==true){
					LPen.setColor(Attr->SelectedColor);
				}
				else if(GetActive()==true){
					LPen.setColor(Attr->ActiveColor);
				}
				else{
					LPen.setColor(Attr->NormalColor);
				}
				LPen.setWidth(Attr->LineWidth);
				P.setPen(LPen);
			}
		}
		else{
			if(GetSelected()==true){
				P.setPen(Qt::green);
			}
			else if(GetActive()==true){
				P.setPen(Qt::red);
			}
			else{
				P.setPen(Qt::blue);
			}
		}
		V->Draw(P,movx,movy,ZoomRate);
	}
}

void	AlgorithmItemRoot::DrawAlpha(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr,const QColor &DefaultColor)
{
	if(GetVisible()==false){
		return;
	}

	if(Attr!=NULL){
		if(GetSelected()==true){
			GetArea().DrawAlpha(0,0 ,&pnt ,Attr->SelectedColor.rgba()
				,ZoomRate ,movx ,movy);
		}
		else if(GetActive()==true){
			GetArea().DrawAlpha(0,0 ,&pnt ,Attr->ActiveColor.rgba()
				,ZoomRate ,movx ,movy);
		}
		else{
			GetArea().DrawAlpha(0,0 ,&pnt ,Attr->NormalColor.rgba()
				,ZoomRate ,movx ,movy);
		}
	}
	else{
		GetArea().DrawAlpha(0,0 ,&pnt ,DefaultColor.rgba()
			,ZoomRate ,movx ,movy);
	}
	if(VBase!=NULL){
		QPainter	P(&pnt);
		P.setPen(Qt::blue);
		VBase->Draw(P,movx,movy,ZoomRate);
	}
}
void	AlgorithmItemRoot::DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if(GetVisible()==false){
		return;
	}

	if((GetSelected()==true) && (GetEditLocked()==false)){
		GetArea().Draw(dx,dy ,&pnt ,Col.rgba()
				,ZoomRate ,movx ,movy);
	}
}
void	AlgorithmItemRoot::DrawMoveTemporary(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	GetArea().Draw(dx,dy ,&pnt ,Col.rgba()
				,ZoomRate ,movx ,movy);
}
void	AlgorithmItemRoot::DrawResult(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	if(GetVisible()==false){
		return;
	}
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase!=NULL && ABase->GetModeToShowNGMark()==false){
		return;
	}

	ParamGlobal	*PG=GetParamGlobal();
	if(PG!=NULL){
		int	CircleWidth=PG->ResultNGCircleWidth;

		bool	DrawBlueNGMark=PG->DrawBlueNGMark;

		if(Res==NULL){
			Res=GetCurrentResult();
		}

		if(Res!=NULL){
			if(PG->DrawResultDetail==false){
				if(Res->GetError()>=2){
					//QRgb	Col=qRgba(255,0,0,PG->NGColorTranparency);
					QColor	NGColor=PG->NGCircleColor;
					NGColor.setAlpha(PG->NGColorTranparency);
					QRgb	Col=NGColor.rgba();
					QColor	RCol=QColor(255-qRed(Col),255-qGreen(Col),255-qBlue(Col));
					if(Res->GetPosListFirst()!=NULL){
						for(ResultPosList *p=Res->GetPosListFirst();p!=NULL;p=p->GetNext()){
							if(p->result>=0x10000){
								p->DrawResult(Res ,IData ,PData ,MovX ,MovY ,ZoomRate
										,PG->NGMarkRadius,Col
										,CircleWidth,DrawBlueNGMark);
							}
						}
					}
					else{
						/*
						QColor	c=Qt::red;
						c.setAlpha(PG->NGColorTranparency);
						GetArea().DrawAlpha( Res.GetTotalShiftedX()
											,Res.GetTotalShiftedY()
											,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
						*/
						int	Cx,Cy;
						GetCenter(Cx,Cy);
						int	R=ZoomRate;
						if(R<PG->NGMarkRadius){
							R=PG->NGMarkRadius;
						}
						int	R2=R+R;
						int	x1=(Cx+Res->GetAlignedX()+MovX)*ZoomRate-R;
						int y1=(Cy+Res->GetAlignedY()+MovY)*ZoomRate-R;

						if(CircleWidth==0){
							PData.setPen(RCol);
							PData.drawEllipse(x1-4,y1-4,R2+8,R2+8);
							PData.setPen(QColor(Col));
							PData.drawEllipse(x1-3,y1-3,R2+6,R2+6);
							PData.setPen(QColor(Col));
							PData.drawEllipse(x1-2,y1-2,R2+4,R2+4);
							PData.drawEllipse(x1,y1,R2,R2);
						}
						else{
							QPen	cpen(RCol,CircleWidth);
							PData.setPen(cpen);
							PData.drawEllipse(x1-CircleWidth-3,y1-CircleWidth-3
											,R2+CircleWidth*2+6 ,R2+CircleWidth*2+6);
							QPen	dpen(QColor(Col),CircleWidth);
							PData.setPen(dpen);
							PData.drawEllipse(x1-2,y1-2,R2+4,R2+4);
							PData.drawEllipse(x1,y1,R2,R2);
						}
					}
				}
			}
			else{
				int	Level=PG->DrawResultDetailLevel;
				if(Res->GetPosListFirst()!=NULL){
					for(ResultPosList *p=Res->GetPosListFirst();p!=NULL;p=p->GetNext()){
						if((ZoomRate>=1.0) && ((Level==0) || ((Level>=1) && (p->result>=0x10000)))){
							QRgb NGColor;
							if(p->result<0x10000)	//OK
								NGColor=qRgba(100,200,0,PG->NGColorTranparency);
							else
								NGColor=qRgba(255,0,0,PG->NGColorTranparency);

							DetailResultInfoListContainer	RetList;
							GetParentBase()->GetLogicDLL()->DrawResultDetail(this,p,RetList);
							RetList.Data.LibType=ABase->GetLibType();
							RetList.Data.Phase	=GetPhaseCode();
							RetList.Data.Page	=GetPage();
							RetList.Data.Layer	=GetLayer();
							RetList.Data.ItemID	=GetID();
							RetList.Data.LibID	=GetLibID();							
							p->GetPosInTarget(Res,RetList.Data.PosX,RetList.Data.PosY);

							QStringList	RetListStr;
							RetList.GetInfoStringList(RetListStr);

							if(Level>=20){
								int	r=qRed	(NGColor);
								int	g=qGreen(NGColor);
								int	b=qBlue	(NGColor);
								NGColor=qRgba(r,g,b,PG->NGColorTranparency);
							}
							p->DrawResultDetail(Res ,IData ,PData ,MovX ,MovY ,ZoomRate,PG->NGMarkRadius,NGColor
												,CircleWidth,DrawBlueNGMark);
							int	X=(p->Px+p->Rx+MovX)*ZoomRate;
							int	Y=(p->Py+p->Ry+MovY)*ZoomRate;
							QRect Rect=PData.boundingRect ( 10, 10, 10000,10000, Qt::AlignLeft,"W");
							int	MaxL=0;
							for(int i=0;i<RetList.count();i++){
								if(MaxL<RetListStr[i].length()){
									MaxL=RetListStr[i].length();
								}
							}

							if((X>IData.width()) || ((X+Rect.width()*MaxL)<0)
							|| (Y>=IData.height()) || ((Y+Rect.height()*RetList.count())<0)){
								continue;
							}
							if(Level<=1){
								for(int i=0;i<RetList.count();i++){
									PData.drawText(X,Y,RetListStr[i]);
									Y+=Rect.height();
								}
							}
						}
						else{
							if(Level==0 || (p->result>=0x10000)){
								QRgb NGColor;
								if(p->result<0x10000)	//OK
									NGColor=qRgba(100,200,0,PG->NGColorTranparency);
								else
									NGColor=qRgba(255,0,0,PG->NGColorTranparency);
								p->DrawResultDetail(Res ,IData ,PData ,MovX ,MovY ,ZoomRate,PG->NGMarkRadius,NGColor
													,CircleWidth,DrawBlueNGMark);
							}
						}
					}
				}
				else if(Res->GetError()>=2){
					QColor	c=Qt::red;
					c.setAlpha(PG->NGColorTranparency);
					GetArea().DrawAlpha( Res->GetTotalShiftedX()
										,Res->GetTotalShiftedY()
										,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);
				}

				if(Level>=10 && (ZoomRate>=1.0)){
					if(Res->GetPosListFirst()!=NULL){
						for(ResultPosList *p=Res->GetPosListFirst();p!=NULL;p=p->GetNext()){
							if(p->result>=0x10000){
								p->DrawResult(Res ,IData ,PData ,MovX ,MovY ,ZoomRate,PG->NGMarkRadius,qRgba(255,0,0,PG->NGColorTranparency)
												,CircleWidth,DrawBlueNGMark);
							}
						}
					}
				}
			}
		}
	}
}

void	AlgorithmItemRoot::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(GetVisible()==false){
		return;
	}

	if(Res==NULL){
		Res=GetCurrentResult();
	}

	if(Res!=NULL){
		if((OnlyNG==false) || (Res->GetError()>=2)){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().DrawAlpha( Res->GetTotalShiftedX()
								,Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
		}
	}
}
void	AlgorithmItemRoot::DrawMonoBitmap(BYTE **BmpPoint)
{
	GetArea().MakeBitData(BmpPoint,GetDotPerLine(),GetMaxLines());
}

void	AlgorithmItemRoot::SetIndependentItemData(int32 Command
													,int32 LocalPage,int32 Layer
													,AlgorithmItemRoot *Data
													,IntList &EdittedMemberID
													,QByteArray &Something
													,QByteArray &AckData)
{
}
bool	AlgorithmItemRoot::GeneralDataRelease(int32 Command,void *data)
{
	return true;
}
void	*AlgorithmItemRoot::GeneralDataCreate(int32 Command,void *reqData)
{
	return NULL;
}
bool	AlgorithmItemRoot::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	return true;
}
bool	AlgorithmItemRoot::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	return true;
}
bool	AlgorithmItemRoot::GeneralDataReply(int32 Command,void *data)
{
	return true;
}

AlignmentPacketBase	*AlgorithmItemRoot::GetAlignmentPointer(int localX ,int localY ,bool FromGlobal)
{
	AlignmentPacketBase	*Ret;
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	LogicDLL	*L=LC->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	while(L!=NULL){
		Ret=L->GetAlignmentPointer(GetPage(),localX,localY,this,FromGlobal);
		if(Ret!=NULL){
			return Ret;
		}
		L=LC->NextByAlgorithmType(L,AlgorithmBit_TypeAlignment);
	}
	return(NULL);

}
void			AlgorithmItemRoot::GetAlignmentForProcessing(AlignmentPacketBase &Packet)
{
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	LogicDLL	*L=LC->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	if(L==NULL){
		return;
	}
	L->GetAlignmentForProcessing(GetPage(),Packet);
}

ClipboardAlgorithmItem	*AlgorithmItemRoot::CreateClipboardItem(void)
{
	if(Selected==true){
		ClipboardAlgorithmItem	*Dest=new ClipboardAlgorithmItem();
		QBuffer	Buff(&Dest->ItemData);
		Buff.open(QIODevice::ReadWrite);
		Save(&Buff);
		Dest->Area=GetArea();
		Dest->Page	=GetPage();
		Dest->Layer	=GetLayer();
		if(VBase!=NULL){
			int	id=VBase->GetID();
			Dest->Vector=VectorLineBase::Create(id);
			*Dest->Vector=*VBase;
		}
		Dest->ItemClassType	=GetItemClassType();
		return Dest;
	}
	return NULL;
}
bool	AlgorithmItemRoot::FromClipboardItem(ClipboardAlgorithmItem *Src,LayersBase *LBase)
{
	QBuffer	Buff(&Src->ItemData);
	Buff.open(QIODevice::ReadWrite);
	return Load(&Buff,LBase);
}

void	AlgorithmItemRoot::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (Visible==true)) || AllItems==true){
		MoveTo(GlobalDx,GlobalDy);
		GetArea().ClipArea(0,0,GetDotPerLine(),GetMaxLines());
	}
}
bool	AlgorithmItemRoot::IsNull(void)const
{	
	if(GetArea().IsNull()==false || (VBase!=NULL && VBase->IsNull()==false))
		return false;
	return true;
}

void	AlgorithmItemRoot::SetError(short e)
{
	if(GetCurrentResult()!=NULL){
		GetCurrentResult()->SetError(e);
	}
}

void	AlgorithmItemRoot::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	int	gx1,gy1,gx2,gy2;
	int	x1,y1,x2,y2;
	GetXY(gx1 ,gy1 ,gx2 ,gy2);
	LayersBase	*L=GetLayersBase();
	int	globalPage=L->GetGlobalPageFromLocal(GetPage());
	x1=gx1+GlobalDx+GetLayersBase()->GetGlobalOutlineOffset(globalPage)->x;
	y1=gy1+GlobalDy+GetLayersBase()->GetGlobalOutlineOffset(globalPage)->y;
	x2=gx2+GlobalDx+GetLayersBase()->GetGlobalOutlineOffset(globalPage)->x;
	y2=gy2+GlobalDy+GetLayersBase()->GetGlobalOutlineOffset(globalPage)->y;
	int	Lx1,Ly1,Lx2,Ly2;
	int	MaxGlobalPage=GetLayersBase()->GetGlobalPageNumb();
	for(int page=0;page<MaxGlobalPage;page++){
		Lx1=x1 - GetLayersBase()->GetGlobalOutlineOffset(page)->x;
		Ly1=y1 - GetLayersBase()->GetGlobalOutlineOffset(page)->y;
		Lx2=Lx1+(x2-x1);
		Ly2=Ly1+(y2-y1);
		if(CheckOverlapRectRect(0,0,GetDotPerLine(),GetMaxLines()
			,Lx1,Ly1,Lx2,Ly2)==true){
				IntClass *c;
				for(c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
					if(c->GetValue()==page){
						break;
					}
				}
				if(c==NULL){
					PageList.Add(page);
				}
		}
	}
}


bool	AlgorithmItemRoot::IsEdited(void)const
{
	if(Changed==true){
		return true;
	}
	return false;
}
bool	AlgorithmItemRoot::IsCalcDone(void)const
{
	if(CalcDone==true){
		return true;
	}
	return false;
}
void	AlgorithmItemRoot::SetEdited(bool edited)
{
	Changed=edited;
}
void	AlgorithmItemRoot::SetCalcDone(bool calcdone)
{
	CalcDone=calcdone;
}

void	AlgorithmItemRoot::GetOutsideItems(int movx ,int movy ,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
}
void	AlgorithmItemRoot::DrawItemListsForPaste(int dx ,int dy ,QImage &Img,double ZoomRate ,int movx ,int movy)
{
	GetArea().DrawAlpha(dx,dy
			,&Img
			,qRgba (128 + ((GetID()&0x7)<<4), 128+ ((GetID()&0x3)<<5), 64,160) 
			,ZoomRate ,movx ,movy);
}
void	AlgorithmItemRoot::ExecuteTransformSelectedItem(TransformBase &M)
{
	double	cx,cy;
	GetCenter(cx,cy);

	double	gx;
	double	gy;
	M.Transform(cx,cy,gx,gy);

	MoveTo(gx-cx,gy-cy);
}

bool	AlgorithmItemRoot::ReloadFromLibrary(void)
{
	AlgorithmLibraryContainer	*LContainer=GetLibraryContainer();
	if(LContainer!=NULL){
		AlgorithmLibraryLevelContainer	*Lv=new AlgorithmLibraryLevelContainer(LContainer);
		if(LContainer->GetLibrary(GetLibID() ,*Lv)==true){
			GetThresholdBaseWritable()->FromLibrary(Lv->GetLibrary());
			delete	Lv;
			return true;
		}
	}
	return false;
}

void	AlgorithmItemRoot::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	GetArea().Rotate(AngleDegree ,Cx, Cy);
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		double	Radian=AngleDegree*M_PI/180.0;
		double	Cos=cos(Radian);
		double	Sin=sin(Radian);
		//X= (x-cx)*Cos+(y-cy)*Sin+cx
		//Y=-(x-cx)*Sin+(y-cy)*Cos+cy
		TransformAffin	D(Cos,Sin,Cx-Cx*Cos-Cy*Sin,-Sin,Cos,Cy+Cx*Sin-Cy*Cos);
		GetVector()->Transform(D);
	}
	Changed		=true;
	CalcDone	=false;
}
void	AlgorithmItemRoot::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	if(MirrorMode==AlgorithmItemRoot::_XMirror){
		GetArea().MirrorY(PointX);
	}
	else if(MirrorMode==AlgorithmItemRoot::_YMirror){
		GetArea().MirrorX(PointY);		
	}
	if(GetVector()!=NULL && GetVector()->IsNull()==false){
		if(MirrorMode==AlgorithmItemRoot::_XMirror){
			//X= -(x-PointX)+PointX
			TransformAffin	D(-1,0,2*PointX,0,1,0);
			GetVector()->Transform(D);
		}
		else if(MirrorMode==AlgorithmItemRoot::_YMirror){
			//Y= -(y-PointY)+PointY
			TransformAffin	D(1,0,0,0,-1,PointY*2);
			GetVector()->Transform(D);
		}
	}
	Changed		=true;
	CalcDone	=false;
}

HistgramByParamBase	*AlgorithmItemRoot::GetHistgramBase(int HistID)
{
	return GetThresholdBaseWritable()->GetHistgramBase(HistID);
}

void	AlgorithmItemRoot::MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)
{
	FlexArea	F=GetInspectedArea();
	F.MakeBitData(BMap,XByte*8,YLen);
}
void	AlgorithmItemRoot::SetItemName(const QString &ItemName , bool OnlySelected)
{
	if(OnlySelected==false || GetSelected()==true){
		SetItemName(ItemName);
	}
}
AlgorithmItemRoot	*AlgorithmItemRoot::SeparateItem(FlexArea &DividedMask)
{
	FlexArea	Area1;
	Area1.Sub(GetArea(),DividedMask);
	FlexArea	Area2;
	Area2.Sub(GetArea(),Area1);
	if(Area1.GetPatternByte()==0 || Area2.GetPatternByte()==0){
		return NULL;
	}
	AlgorithmItemRoot	*v=Clone();
	SetArea(Area1);
	v->SetArea(Area2);
	return v;
}

XYData	*AlgorithmItemRoot::GetGlobalOutlineOffset(void)
{
	int	GlobalPage=GetGlobalPage();
	return GetLayersBase()->GetGlobalOutlineOffset(GlobalPage);
}
void	AlgorithmItemRoot::CutArea(FlexArea &localArea ,bool &_Changed)
{
	if(GetEditLocked()==false  && GetVisible()==true && GetArea().CheckOverlap(&localArea)==true){

		UndoAlgorithmItemRoot	*UndoPointer=new UndoAlgorithmItemRoot(this ,GetParentAlgorithm(),&AlgorithmItemRoot::UndoCutArea);
		Save(UndoPointer->GetWritePointer());
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

		FlexArea	A=GetArea();
		A.Sub(GetArea(), localArea);
		SetArea(A);
		Changed=true;
		CalcDone=false;
		_Changed=true;
	}
}
bool	AlgorithmItemRoot::IsOriginTypeSelection(struct OriginTypeSelection &SelectMode)
{
	if((GeneratedOrigin==_OriginType_FromUnknown && SelectMode._FromUnknown==true)
	|| (GeneratedOrigin==_OriginType_FromLibrary && SelectMode._FromLibrary==true)
	|| (GeneratedOrigin==_OriginType_FromManual && SelectMode._FromManual==true)
	|| (GeneratedOrigin==_OriginType_FromParts && SelectMode._FromParts==true)
	|| (GeneratedOrigin==_OriginType_FromMPA && SelectMode._FromMPA==true)
	|| (GeneratedOrigin==_OriginType_FromCAD && SelectMode._FromCAD==true)){
		if(SelectMode.Origin==NULL
		|| (GetParentBase()!=NULL && SelectMode.Origin->GetLibType()==GetParentBase()->GetLibType())){
			return true;
		}
	}
	return false;
}
void	AlgorithmItemRoot::UndoCutArea(QIODevice *f)
{
	Load(f,GetLayersBase());
	Changed=true;
	CalcDone=false;
}

bool	AlgorithmItemRoot::TF_EnumHistList(HistgramTypeListInAlgoContainer &RetLists)
{
	int	localPage	=GetPage();
	int	GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	AlgorithmBase	*ABase=GetParentBase();

	if(ABase!=NULL){
		GUICmdReqEnumHistgram	RCmd(GetLayersBase(),"ANY","ANY" ,GlobalPage);
		GUICmdAckEnumHistgram	SCmd(GetLayersBase(),"ANY","ANY" ,GlobalPage);

		RCmd.ItemID		=GetID();
		ABase->GetAlgorithmRootName(RCmd.AlgoRoot,RCmd.AlgoName);
		RCmd.Phase		=GetPhaseCode();
		RCmd.GlobalPage	=GlobalPage;
		RCmd.Layer		=GetLayer();

		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			RetLists=SCmd.RetLists;
			return true;
		}
	}
	return false;
}


void	AlgorithmItemRoot::ShrinkArea(int ShrinkDot)
{
	int	Mergin=abs(ShrinkDot)+16;
	int	XLen=GetArea().GetWidth()+Mergin+Mergin;
	int	YLen=GetArea().GetHeight()+Mergin+Mergin;
	int	XByte=(XLen+7)/8;
	BYTE	BitMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BitMap=MakeMatrixBuff(XByte,YLen,BitMapBuff,sizeof(BitMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BitMap ,0 ,XByte,YLen);
	GetArea().MakeBitData(BitMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);
	if(ShrinkDot>0){
		GetLayersBase()->ThinAreaN(BitMap
					,TmpMap
					,XByte ,YLen
					,ShrinkDot);
	}
	else if(ShrinkDot<0){
		GetLayersBase()->FatAreaN(BitMap
					,TmpMap
					,XByte ,YLen
					,-ShrinkDot);
	}
	FlexArea	A;
	A.BuildFromRaster(BitMap ,XByte ,YLen
                    ,GetArea().GetMinX()-Mergin ,GetArea().GetMinY()-Mergin
					,0,0,GetDotPerLine(),GetMaxLines()
					,GetDotPerLine(),GetMaxLines());
	SetArea(A);

	if(BitMap!=(BYTE **)BitMapBuff){
		DeleteMatrixBuff(BitMap,YLen);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,YLen);
	}
}

	
void	AlgorithmItemRoot::ShrinkHalf(void)
{
	int	Mergin=16;
	int	XLen=GetArea().GetWidth()+Mergin+Mergin;
	int	YLen=GetArea().GetHeight()+Mergin+Mergin;
	int	XByte=(XLen+7)/8;

	BYTE	BitMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BitMap=MakeMatrixBuff(XByte,YLen,BitMapBuff,sizeof(BitMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BitMap ,0 ,XByte,YLen);
	GetArea().MakeBitData(BitMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);
	FlexArea	S=GetArea();
	S.MoveToNoClip(1,0);
	MatrixBuffClear	(TmpMap ,0 ,XByte,YLen);
	S.MakeBitData(TmpMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);

	MatrixBuffAnd	(BitMap ,(const BYTE **)TmpMap ,XByte,YLen);

	S.MoveToNoClip(-1,1);
	MatrixBuffClear	(TmpMap ,0 ,XByte,YLen);
	S.MakeBitData(TmpMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);

	MatrixBuffAnd	(BitMap ,(const BYTE **)TmpMap ,XByte,YLen);

	FlexArea	A;
	A.BuildFromRaster(BitMap ,XByte ,YLen
                    ,GetArea().GetMinX()-Mergin ,GetArea().GetMinY()-Mergin
					,0,0,GetDotPerLine(),GetMaxLines()
					,GetDotPerLine(),GetMaxLines());
	SetArea(A);

	if(BitMap!=(BYTE **)BitMapBuff){
		DeleteMatrixBuff(BitMap,YLen);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,YLen);
	}
}

void	AlgorithmItemRoot::ExpandHalf(void)
{
	int	Mergin=16;
	int	XLen=GetArea().GetWidth()+Mergin+Mergin;
	int	YLen=GetArea().GetHeight()+Mergin+Mergin;
	int	XByte=(XLen+7)/8;

	BYTE	BitMapBuff[10000];
	BYTE	TmpMapBuff[10000];
	BYTE	**BitMap=MakeMatrixBuff(XByte,YLen,BitMapBuff,sizeof(BitMapBuff));
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen,TmpMapBuff,sizeof(TmpMapBuff));
	MatrixBuffClear	(BitMap ,0 ,XByte,YLen);
	GetArea().MakeBitData(BitMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);
	FlexArea	S=GetArea();
	S.MoveToNoClip(1,0);
	MatrixBuffClear	(TmpMap ,0 ,XByte,YLen);
	S.MakeBitData(TmpMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);
	MatrixBuffOr	(BitMap ,(const BYTE **)TmpMap ,XByte,YLen);

	S.MoveToNoClip(-1,1);
	MatrixBuffClear	(TmpMap ,0 ,XByte,YLen);
	S.MakeBitData(TmpMap 
						,-GetArea().GetMinX()+Mergin ,-GetArea().GetMinY()+Mergin
						,XLen, YLen);
	MatrixBuffOr	(BitMap ,(const BYTE **)TmpMap ,XByte,YLen);

	FlexArea	A;
	A.BuildFromRaster(BitMap ,XByte ,YLen
                    ,GetArea().GetMinX()-Mergin ,GetArea().GetMinY()-Mergin
					,0,0,GetDotPerLine(),GetMaxLines()
					,GetDotPerLine(),GetMaxLines());
	SetArea(A);

	if(BitMap!=(BYTE **)BitMapBuff){
		DeleteMatrixBuff(BitMap,YLen);
	}
	if(TmpMap!=(BYTE **)TmpMapBuff){
		DeleteMatrixBuff(TmpMap,YLen);
	}
}
bool	AlgorithmItemRoot::ManualExecuteAll(ManualExecuter &ManualExecuterData)
{
	return ManualExecuterData.Execute(this);
}
//----------- Unit-------------
	
bool	AlgorithmItemRoot::IsUnitMode(void)
{
	return GetParamGlobal()->IsUnitMode();
}

double	AlgorithmItemRoot::TransformPixelToUnit(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnit(GetPage(),pixel);
}

double	AlgorithmItemRoot::TransformUnitToPixel(double unit)
{
	return GetParamGlobal()->TransformUnitToPixel(GetPage(),unit);
}

QString	AlgorithmItemRoot::TransformPixelToUnitStr(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitStr(GetPage(),pixel);
}

QString	AlgorithmItemRoot::GetUnitStr(double unit)
{
	return GetParamGlobal()->GetUnitStr(unit);
}


double	AlgorithmItemRoot::TransformPixelToUnitSquare(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquare(GetPage(),pixel);
}

double	AlgorithmItemRoot::TransformUnitToPixelSquare(double unit)
{
	return GetParamGlobal()->TransformUnitToPixelSquare(GetPage(),unit);
}

QString	AlgorithmItemRoot::TransformPixelToUnitSquareStr(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquareStr(GetPage(),pixel);
}

QString	AlgorithmItemRoot::GetUnitSquareStr(double unit)
{
	return GetParamGlobal()->GetUnitSquareStr(unit);
}
void	AlgorithmItemRoot::ClearSubBlock(void)
{
	SubBlock.RemoveAll();
}
void	AlgorithmItemRoot::SetSubBlock(const SubtractItemContainer	&src)
{
	SubBlock=src;
}

struct	ItemLinkStruct
{
	AlgorithmItemRoot	*ItemPointer;
	int		X1,Y1,X2,Y2;
};

static	int	LinkFunc(const void *a ,const void *b)
{
	struct	ItemLinkStruct	*pa=(struct	ItemLinkStruct *)a;
	struct	ItemLinkStruct	*pb=(struct	ItemLinkStruct *)b;

	return (pa->Y1-pb->Y1);
}

void	MakeLinkItemByOverlap(const AlgorithmItemPointerListContainer &Src ,const AlgorithmItemPointerListContainer &Dst
							, NPListPack<LinkItemPointerList> &RetLink)
{
	int	DDimCount=Dst.GetCount();
	if(DDimCount==0)
		return;

	struct ItemLinkStruct *DDim=new struct ItemLinkStruct[DDimCount];

	int	MinX=99999999;
	int	MinY=99999999;
	int	MaxX=-99999999;
	int	MaxY=-99999999;
	int	dnumb=0;
	for(AlgorithmItemPointerList *d=Dst.GetFirst();d!=NULL;d=d->GetNext()){
		DDim[dnumb].ItemPointer=d->GetItem();
		d->GetItem()->GetXY(DDim[dnumb].X1,DDim[dnumb].Y1,DDim[dnumb].X2,DDim[dnumb].Y2);
		MinX=min(MinX,DDim[dnumb].X1);
		MinY=min(MinY,DDim[dnumb].Y1);
		MaxX=max(MaxX,DDim[dnumb].X2);
		MaxY=max(MaxY,DDim[dnumb].Y2);
		dnumb++;
	}
	int	XLen=1000;
	int	YLen=1000;
	int	XNumb=(MaxX-MinX+XLen-1)/XLen;
	int	YNumb=(MaxY-MinY+YLen-1)/YLen;
	if(XNumb<=0)
		XNumb=1;
	if(YNumb<=0)
		YNumb=1;
	XLen=(MaxX-MinX)/XNumb;
	YLen=(MaxY-MinY)/YNumb;

	AlgorithmItemPointerListContainer	**DMatrix=new AlgorithmItemPointerListContainer*[YNumb];
	for(int y=0;y<YNumb;y++){
		DMatrix[y]=new AlgorithmItemPointerListContainer[XNumb];
	}
	for(int i=0;i<dnumb;i++){
		int	ix1=(DDim[i].X1-MinX)/XLen;
		int	iy1=(DDim[i].Y1-MinY)/YLen;
		int	ix2=(DDim[i].X2-MinX)/XLen;
		int	iy2=(DDim[i].Y2-MinY)/YLen;
		for(int x=ix1;x<=ix2 && x<XNumb;x++){
			for(int y=iy1;y<=iy2 && y<YNumb;y++){
				(DMatrix[y])[x].AppendList(new AlgorithmItemPointerList(DDim[i].ItemPointer));
			}
		}
	}
	for(AlgorithmItemPointerList *s=Src.GetFirst();s!=NULL;s=s->GetNext()){	
		double	X1,Y1,X2,Y2;
		s->GetItem()->GetXY(X1,Y1,X2,Y2);
		int	ix1=(X1-MinX)/XLen;
		int	iy1=(Y1-MinY)/YLen;
		int	ix2=(X2-MinX)/XLen;
		int	iy2=(Y2-MinY)/YLen;
		for(int x=ix1;x<=ix2 && x<XNumb;x++){
			for(int y=iy1;y<=iy2 && y<YNumb;y++){
				for(AlgorithmItemPointerList *k=(DMatrix[y])[x].GetFirst();k!=NULL;k=k->GetNext()){
					if(s->GetItem()->IsCrossed(&k->GetItem()->GetArea())==true
					|| k->GetItem()->IsCrossed(&s->GetItem()->GetArea())==true){
						LinkItemPointerList	*a=new LinkItemPointerList(s->GetItem(),k->GetItem());
						RetLink.AppendList(a);
						goto	QNext;
					}
				}
			}
		}
QNext:;
	}
	for(int y=0;y<YNumb;y++){
		delete	[]DMatrix[y];
	}
	delete	[]DMatrix;
	delete	[]DDim;
}

class	AlgorithmItemPointerListWithCenter : public AlgorithmItemPointerList
{
public:
	double	Cx,Cy;

	AlgorithmItemPointerListWithCenter(void){}
	AlgorithmItemPointerListWithCenter(AlgorithmItemRoot *item);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

	
bool	AlgorithmItemPointerListWithCenter::Save(QIODevice *f)
{
	if(AlgorithmItemPointerList::Save(f)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	return true;
}

bool	AlgorithmItemPointerListWithCenter::Load(QIODevice *f)
{
	if(AlgorithmItemPointerList::Load(f)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	return true;
}


AlgorithmItemPointerListWithCenter::AlgorithmItemPointerListWithCenter(AlgorithmItemRoot *item):AlgorithmItemPointerList(item)
{
	item->GetCenter(Cx,Cy);
}
void	MakeLinkItemClosed(const AlgorithmItemPointerListContainer &Src ,const AlgorithmItemPointerListContainer &Dst
							, NPListPack<LinkItemPointerList> &RetLink)
{
	int	DDimCount=Dst.GetCount();
	if(DDimCount==0)
		return;

	struct ItemLinkStruct *DDim=new struct ItemLinkStruct[DDimCount];

	int	MinX=99999999;
	int	MinY=99999999;
	int	MaxX=-99999999;
	int	MaxY=-99999999;
	int	dnumb=0;
	for(AlgorithmItemPointerList *d=Dst.GetFirst();d!=NULL;d=d->GetNext()){
		DDim[dnumb].ItemPointer=d->GetItem();
		d->GetItem()->GetXY(DDim[dnumb].X1,DDim[dnumb].Y1,DDim[dnumb].X2,DDim[dnumb].Y2);
		MinX=min(MinX,DDim[dnumb].X1);
		MinY=min(MinY,DDim[dnumb].Y1);
		MaxX=max(MaxX,DDim[dnumb].X2);
		MaxY=max(MaxY,DDim[dnumb].Y2);
		dnumb++;
	}
	int	XLen=1000;
	int	YLen=1000;
	int	XNumb=(MaxX-MinX+XLen-1)/XLen;
	int	YNumb=(MaxY-MinY+YLen-1)/YLen;
	if(XNumb<=0)
		XNumb=1;
	if(YNumb<=0)
		YNumb=1;
	if(YNumb<=0 || XNumb<=0){
		delete	[]DDim;
		return;
	}
	XLen=(MaxX-MinX)/XNumb;
	YLen=(MaxY-MinY)/YNumb;

	AlgorithmItemPointerListContainer	**DMatrix=new AlgorithmItemPointerListContainer*[YNumb];
	for(int y=0;y<YNumb;y++){
		DMatrix[y]=new AlgorithmItemPointerListContainer[XNumb];
	}
	for(int i=0;i<dnumb;i++){
		int	ix1=(DDim[i].X1-MinX)/XLen;
		int	iy1=(DDim[i].Y1-MinY)/YLen;
		int	ix2=(DDim[i].X2-MinX)/XLen;
		int	iy2=(DDim[i].Y2-MinY)/YLen;
		for(int x=ix1;x<=ix2 && x<XNumb;x++){
			for(int y=iy1;y<=iy2 && y<YNumb;y++){
				(DMatrix[y])[x].AppendList(new AlgorithmItemPointerListWithCenter(DDim[i].ItemPointer));
			}
		}
	}
	double	Cx;
	double	Cy;

	int	SDimCount=Src.GetCount();
	AlgorithmItemPointerList **SDim=new AlgorithmItemPointerList *[SDimCount];
	SDimCount=0;
	for(AlgorithmItemPointerList *s=Src.GetFirst();s!=NULL;s=s->GetNext()){	
		SDim[SDimCount]=s;
		SDimCount++;
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int m=0;m<SDimCount;m++){
			AlgorithmItemPointerList *s=SDim[m];
		//for(AlgorithmItemPointerList *s=Src.GetFirst();s!=NULL;s=s->GetNext()){	
			double	X1,Y1,X2,Y2;
			s->GetItem()->GetXY(X1,Y1,X2,Y2);
			int	ix1=(X1-MinX)/XLen;
			int	iy1=(Y1-MinY)/YLen;
			int	ix2=(X2-MinX)/XLen;
			int	iy2=(Y2-MinY)/YLen;
			for(int x=ix1;x<=ix2 && x<XNumb;x++){
				if(x<0)
					continue;
				for(int y=iy1;y<=iy2 && y<YNumb;y++){
					if(y<0)
						continue;
					for(AlgorithmItemPointerList *k=(DMatrix[y])[x].GetFirst();k!=NULL;k=k->GetNext()){
						if(s->GetItem()->IsCrossed(&k->GetItem()->GetArea())==true
						|| k->GetItem()->IsCrossed(&s->GetItem()->GetArea())==true){
							LinkItemPointerList	*a=new LinkItemPointerList(s->GetItem(),k->GetItem());
							#pragma omp critical
							{
								RetLink.AppendList(a);
							}
							goto	QNext;
						}
					}
				}
			}
			double	MinLen;
			AlgorithmItemPointerList	*ClosedItem;
			{
				Cx=(X1+X2)/2;
				Cy=(Y1+Y2)/2;
				MinLen		=99999999;
				ClosedItem	=NULL;
				for(int x=ix1;x<=ix2 && x<XNumb;x++){
					if(x<0)
						continue;
					for(int y=iy1;y<=iy2 && y<YNumb;y++){
						if(y<0)
							continue;
						for(AlgorithmItemPointerList *k=(DMatrix[y])[x].GetFirst();k!=NULL;k=k->GetNext()){
							AlgorithmItemPointerListWithCenter	*kk=static_cast<AlgorithmItemPointerListWithCenter *>(k);
							double	Len=hypot(kk->Cx-Cx,kk->Cy-Cy);
							if(Len<MinLen){
								MinLen=Len;
								ClosedItem=k;
							}
						}
					}
				}
			}
			{
				if(ClosedItem!=NULL){
					LinkItemPointerList	*a=new LinkItemPointerList(s->GetItem(),ClosedItem->GetItem());
					#pragma omp critical
					{
						RetLink.AppendList(a);
					}
					goto	QNext;
				}
			}

			{
				AlgorithmItemRoot			*ClosedOne=NULL;
				for(int i=0;i<DDimCount;i++){
					double	DCx=(DDim[i].X1+DDim[i].X2)/2;
					double	DCy=(DDim[i].Y1+DDim[i].Y2)/2;
					double	Len=hypot(DCx-Cx,DCy-Cy);
					if(Len<MinLen){
						MinLen=Len;
						ClosedOne=DDim[i].ItemPointer;
					}
				}
				if(ClosedOne!=NULL){
					LinkItemPointerList	*a=new LinkItemPointerList(s->GetItem(),ClosedOne);
					#pragma omp critical
					{
						RetLink.AppendList(a);
					}
					goto	QNext;
				}
			}

QNext:;
		}
	}
	for(int y=0;y<YNumb;y++){
		delete	[]DMatrix[y];
	}
	delete	[]DMatrix;
	delete	[]DDim;
	delete	[]SDim;
}

//==========================================================================
AlgorithmItemIndex::AlgorithmItemIndex(void)
{
	memset(&IndexInAlgorithm,0,sizeof(IndexInAlgorithm));
	IndexInAlgorithm.ShadowNumber	=0;
	IndexInAlgorithm.ShadowLevel	=0;
}
AlgorithmItemIndex::AlgorithmItemIndex(int _ItemID,int _Layer ,int _Page ,int _Phase
										,int _ShadowNumber,int _ShadowLevel)
{
	IndexInAlgorithm.ShadowNumber	=_ShadowNumber;
	IndexInAlgorithm.ShadowLevel	=_ShadowLevel;
	IndexInAlgorithm.ItemID			=_ItemID;
	IndexInAlgorithm.Page			=_Page;
	IndexInAlgorithm.Layer			=_Layer;
	IndexInAlgorithm.Phase			=_Phase;
}
AlgorithmItemIndex::AlgorithmItemIndex(int _ItemID,int _Layer ,int _Page ,int _Phase 
					,const QString &dllRoot,const QString &dllName)
{
	IndexInAlgorithm.ItemID	=_ItemID;
	IndexInAlgorithm.Page	=_Page;
	IndexInAlgorithm.Layer	=_Layer;
	IndexInAlgorithm.Phase	=_Phase;
	DLLRoot		=dllRoot;
	DLLName		=dllName;
}
AlgorithmItemIndex::AlgorithmItemIndex(int _ItemID,int _Layer ,int _Page ,int _Phase 
						,int _ShadowNumber,int _ShadowLevel
						,const QString &dllRoot,const QString &dllName)
{
	IndexInAlgorithm.ShadowNumber	=_ShadowNumber;
	IndexInAlgorithm.ShadowLevel	=_ShadowLevel;
	IndexInAlgorithm.ItemID	=_ItemID;
	IndexInAlgorithm.Page	=_Page;
	IndexInAlgorithm.Layer	=_Layer;
	IndexInAlgorithm.Phase	=_Phase;
	DLLRoot		=dllRoot;
	DLLName		=dllName;
}

AlgorithmItemIndex::AlgorithmItemIndex(const AlgorithmItemIndex &src)
{
	IndexInAlgorithm=src.IndexInAlgorithm;
	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
}
AlgorithmItemIndex::AlgorithmItemIndex(const AlgorithmItemRoot &Item)
{
	IndexInAlgorithm.ItemID	=Item.GetID();
	IndexInAlgorithm.Page	=Item.GetPage();
	IndexInAlgorithm.Layer	=Item.GetLayer();
	IndexInAlgorithm.Phase	=Item.GetPhaseCode();
	AlgorithmBase	*A=Item.GetParentBase();
	if(A!=NULL){
		A->GetDLLName(DLLRoot,DLLName);
	}
	LayersBase	*Base=Item.GetLayersBase();
	if(Base!=NULL){
		IndexInAlgorithm.ShadowNumber	=Base->GetShadowNumber();
		IndexInAlgorithm.ShadowLevel	=Base->GetShadowLevel();
	}
}
void	AlgorithmItemIndex::Set(int _ItemID,int _Layer ,int _Page ,int _Phase 
						,const QString &dllRoot,const QString &dllName)
{
	IndexInAlgorithm.ItemID	=_ItemID;
	IndexInAlgorithm.Page	=_Page;
	IndexInAlgorithm.Layer	=_Layer;
	IndexInAlgorithm.Phase	=_Phase;
	DLLRoot		=dllRoot;
	DLLName		=dllName;
}
void	AlgorithmItemIndex::Set(int _ItemID,int _Layer ,int _Page ,int _Phase 
						,int _ShadowNumber,int _ShadowLevel
						,const QString &dllRoot,const QString &dllName)
{
	IndexInAlgorithm.ShadowNumber	=_ShadowNumber;
	IndexInAlgorithm.ShadowLevel	=_ShadowLevel;
	IndexInAlgorithm.ItemID	=_ItemID;
	IndexInAlgorithm.Page	=_Page;
	IndexInAlgorithm.Layer	=_Layer;
	IndexInAlgorithm.Phase	=_Phase;
	DLLRoot		=dllRoot;
	DLLName		=dllName;
}
void	AlgorithmItemIndex::Set(const AlgorithmItemRoot &Item)
{
	IndexInAlgorithm.ItemID	=Item.GetID();
	IndexInAlgorithm.Page	=Item.GetPage();
	IndexInAlgorithm.Layer	=Item.GetLayer();
	IndexInAlgorithm.Phase	=Item.GetPhaseCode();
	AlgorithmBase	*A=Item.GetParentBase();
	if(A!=NULL){
		A->GetDLLName(DLLRoot,DLLName);
	}
	LayersBase	*Base=Item.GetLayersBase();
	if(Base!=NULL){
		IndexInAlgorithm.ShadowNumber	=Base->GetShadowNumber();
		IndexInAlgorithm.ShadowLevel	=Base->GetShadowLevel();
	}
}
AlgorithmItemIndex	&AlgorithmItemIndex::operator=(const AlgorithmItemIndex &src)
{
	IndexInAlgorithm=src.IndexInAlgorithm;
	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
	return *this;
}

bool	AlgorithmItemIndex::Save(QIODevice *f)
{
	if(f->write((const char *)&IndexInAlgorithm,sizeof(IndexInAlgorithm))!=sizeof(IndexInAlgorithm)){
		return false;
	}
	if(::Save(f,DLLRoot)==false){
		return false;
	}
	if(::Save(f,DLLName)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemIndex::Load(QIODevice *f)
{
	if(f->read((char *)&IndexInAlgorithm,sizeof(IndexInAlgorithm))!=sizeof(IndexInAlgorithm)){
		return false;
	}
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	return true;
}
//==========================================================================

ChangedMap::ChangedMap(void)
{
	Map=NULL;
	MapByte=0;
}
ChangedMap::~ChangedMap(void)
{
	if(Map!=NULL){
		delete	[]Map;
		Map=NULL;
	}
	MapByte=0;
}

void	ChangedMap::AllocateByte(int n)
{
	if(Map!=NULL){
		delete	[]Map;
		Map=NULL;
	}
	MapByte=n;
	Map=new BYTE[MapByte];
	memset(Map,0,MapByte);
}
void	ChangedMap::SetChanged(int offset)
{
	Map[offset>>3] |= 0x80>>(offset&7);
}
bool	ChangedMap::IsChanged(int offset)
{
	if((Map[offset>>3] & (0x80>>(offset&7)))==0){
		return false;
	}
	return true;
}
bool	ChangedMap::Save(QIODevice *f)
{
	if(::Save(f,MapByte)==false){
		return false;
	}
	if(f->write((const char *)Map,MapByte)!=MapByte){
		return false;
	}
	return true;
}
bool	ChangedMap::Load(QIODevice *f)
{
	int32	tMapByte;
	if(::Load(f,tMapByte)==false){
		return false;
	}
	if(MapByte!=tMapByte){
		if(Map!=NULL){
			delete	[]Map;
		}
		MapByte=tMapByte;
		Map=new BYTE[MapByte];
	}
	if(f->read((char *)Map,MapByte)!=MapByte){
		return false;
	}
	return true;
}
ChangedMap	&ChangedMap::operator=(const ChangedMap &src)
{
	if(this!=&src){
		if(MapByte!=src.MapByte){
			if(Map!=NULL){
				delete	[]Map;
			}
			MapByte=src.MapByte;
			Map=new BYTE [MapByte];
		}
		memcpy(Map,src.Map,MapByte);
	}
	return *this;
}

//==========================================================================
AlgorithmParentFromItem::AlgorithmParentFromItem(void)
{	
	ItemDimPointer=NULL;	
	ItemDimPointerNumb=0;
	AnyData	=new AnyDataContainer();

	ModeParallel.ModeParallelExecuteInitialAfterEditPrev=false;
	ModeParallel.ModeParallelExecuteInitialAfterEdit	=false;
	ModeParallel.ModeParallelExecuteInitialAfterEditPost=false;
	ModeParallel.ModeParallelExecuteStartByInspection	=true;
	ModeParallel.ModeParallelExecuteCaptured			=true;
	ModeParallel.ModeParallelExecutePreAlignment		=true;
	ModeParallel.ModeParallelExecuteAlignment			=true;
	ModeParallel.ModeParallelExecutePreProcessing		=true;
	ModeParallel.ModeParallelExecuteProcessing			=true;
	ModeParallel.ModeParallelExecuteProcessingRevived	=true;
	ModeParallel.ModeParallelExecutePostProcessing		=true;
	ModeParallel.ModeParallelExecutePreScanning			=true;
	ModeParallel.ModeParallelExecuteScanning			=true;
	ModeParallel.ModeParallelExecutePostScanning		=true;
}
//==========================================================================

AlgorithmInLayerRoot::AlgorithmInLayerRoot(void)
	:PipeClass(this)
{
	CreatedTime	=XDateTime::currentDateTime();
//	PDataInLayer	=NULL;
	PInspectionData	=NULL;
	StartItemID		=0;
	Changed			=false;
	CalcDone		=false;
}
AlgorithmInLayerRoot::~AlgorithmInLayerRoot(void)
{
}

void	AlgorithmInLayerRoot::Initial(void)
{
	SetLearn(GetLayersBase());
}

void	AlgorithmInLayerRoot::GetAlignmentForProcessing(AlignmentPacketBase &Packet)
{
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	LogicDLL	*L=LC->SearchByAlgorithmType(AlgorithmBit_TypeAlignment);
	if(L==NULL){
		return;
	}
	L->GetAlignmentForProcessing(GetPage(),Packet);
}

int		AlgorithmInLayerRoot::GetLoadedVersion(void)
{
	if(GetParentBase()==NULL)
		return -1;
	return GetParentBase()->GetLoadedVersion();
}
bool    AlgorithmInLayerRoot::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,StartItemID)==false){
		return(false);
	}
    return(true);

}
bool    AlgorithmInLayerRoot::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,StartItemID)==false){
		return(false);
	}
	Changed		=false;
	CalcDone	=false;
    return(true);
}

XYData	*AlgorithmInLayerRoot::GetOutlineOffset(void)	const
{
	return GetDataInLayer()->GetOutlineOffset();
}

ImageBuffer &AlgorithmInLayerRoot::GetMasterBuff(void)
{
	return GetDataInLayer()->GetMasterBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetMasterBuff(int n)
{
	return GetDataInLayer()->GetMasterBuff(n);
}
ImageBuffer &AlgorithmInLayerRoot::GetBackGroundBuff(void)
{
	return GetDataInLayer()->GetBackGroundBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetTargetBuff(void)
{
	return GetDataInLayer()->GetTargetBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetTargetTRBuff(void)
{
	return GetDataInLayer()->GetTargetTRBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetRawTargetBuff(void)
{
	return GetDataInLayer()->GetRawTargetBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetDelayedViewBuff(void)
{
	return GetDataInLayer()->GetDelayedViewBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetCamTargetBuff(void)
{
	return GetDataInLayer()->GetCamTargetBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetBitBuff(void)
{
	return GetDataInLayer()->GetBitBuff();
}
ImageBuffer &AlgorithmInLayerRoot::GetTrialTargetBuff(void)
{
	return GetDataInLayer()->GetTrialTargetBuff();
}
ImageBuffer     *AlgorithmInLayerRoot::GetMasterBuffPointer(void)
{
	return GetDataInLayer()->GetMasterBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetMasterBuffPointer(int n)
{
	return GetDataInLayer()->GetMasterBuffPointer(n);
}
ImageBuffer     *AlgorithmInLayerRoot::GetBackGroundBuffPointer(void)
{
	return GetDataInLayer()->GetBackGroundBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetTargetBuffPointer(void)
{
	return GetDataInLayer()->GetTargetBuffPointer();
}
ImageBuffer		*AlgorithmInLayerRoot::GetTargetTRBuffPointer(void)
{
	return GetDataInLayer()->GetTargetTRBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetRawTargetBuffPointer(void)
{
	return GetDataInLayer()->GetRawTargetBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetDelayedViewBuffPointer(void)
{
	return GetDataInLayer()->GetDelayedViewBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetCamTargetBuffPointer(void)
{
	return GetDataInLayer()->GetCamTargetBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetBitBuffPointer(void)
{
	return GetDataInLayer()->GetBitBuffPointer();
}
ImageBuffer     *AlgorithmInLayerRoot::GetTrialTargetBuffPointer(void)
{
	return GetDataInLayer()->GetTrialTargetBuffPointer();
}
bool	AlgorithmInLayerRoot::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionMap(Mode,Map ,GetPhaseCode(),GetPage(),GetLayer(),LibData ,Anything);
}
bool	AlgorithmInLayerRoot::GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionMap(Mode,Map ,GetPhaseCode(),GetPage(),GetLayer(),Anything);
}
bool	AlgorithmInLayerRoot::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionVector(Mode,Vector ,GetPhaseCode(),GetPage(),GetLayer(),Anything);

}
bool	AlgorithmInLayerRoot::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionVector(Mode,Vector ,GetPhaseCode(),GetPage(),GetLayer(),Anything);
}

bool	AlgorithmInLayerRoot::IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->IncludeLibInReflection(Mode,GetPage(),GetLayer(),LibData ,Anything);
}

bool	AlgorithmInLayerRoot::GetUsageLibInReflection(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret)
{
	return GetLayersBase()->GetLogicDLLBase()->GetUsageLibInReflection(Mode,GetPage(),GetLayer(),Ret);
}


int		AlgorithmInLayerRoot::GetPhaseCode(void)	const
{
	return GetAlgorithmInPageInOnePhase()->GetPhaseCode();
}

int		AlgorithmInLayerRoot::GetLayerNumb(void)
{	
	if(GetParentInPage()!=NULL){
		return GetParentInPage()->GetLayerNumb();
	}
	return GetLayersBase()->GetParamGlobal()->LayerNumb;
}
	
//----------- Unit-------------
	
bool	AlgorithmInLayerRoot::IsUnitMode(void)
{
	return GetParamGlobal()->IsUnitMode();
}

double	AlgorithmInLayerRoot::TransformPixelToUnit(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnit(GetPage(),pixel);
}

double	AlgorithmInLayerRoot::TransformUnitToPixel(double unit)
{
	return GetParamGlobal()->TransformUnitToPixel(GetPage(),unit);
}

QString	AlgorithmInLayerRoot::TransformPixelToUnitStr(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitStr(GetPage(),pixel);
}

QString	AlgorithmInLayerRoot::GetUnitStr(double unit)
{
	return GetParamGlobal()->GetUnitStr(unit);
}


double	AlgorithmInLayerRoot::TransformPixelToUnitSquare(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquare(GetPage(),pixel);
}

double	AlgorithmInLayerRoot::TransformUnitToPixelSquare(double unit)
{
	return GetParamGlobal()->TransformUnitToPixelSquare(GetPage(),unit);
}

QString	AlgorithmInLayerRoot::TransformPixelToUnitSquareStr(double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquareStr(GetPage(),pixel);
}

QString	AlgorithmInLayerRoot::GetUnitSquareStr(double unit)
{
	return GetParamGlobal()->GetUnitSquareStr(unit);
}
//==========================================================================
ExecuteTimeClass::ExecuteTimeClass(void)
{
	ClearExecuteTime();
}

void	ExecuteTimeClass::ClearExecuteTime(void)
{
	MilisecExecuteInitialAfterEditPrev	=0;
	MilisecExecuteInitialAfterEdit		=0;
	MilisecExecuteInitialAfterEditPost	=0;
	MilisecExecuteStartByInspection		=0;
	MilisecExecuteCaptured				=0;
	MilisecExecutePreAlignment			=0;
	MilisecExecuteAlignment				=0;
	MilisecExecutePreProcessing			=0;
	MilisecExecuteProcessing			=0;
	MilisecExecuteProcessingRevived		=0;
	MilisecExecutePostProcessing		=0;
	MilisecExecutePreScanning			=0;
	MilisecExecuteScanning				=0;
	MilisecExecutePostScanning			=0;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteInitialAfterEditPrev(void)	const
{
	return MilisecExecuteInitialAfterEditPrev;
}
DWORD	ExecuteTimeClass::GetMilisecExecuteInitialAfterEdit(void)	const
{
	return MilisecExecuteInitialAfterEdit;
}
DWORD	ExecuteTimeClass::GetMilisecExecuteInitialAfterEditPost(void)	const
{
	return MilisecExecuteInitialAfterEditPost;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteStartByInspection(void)	const
{
	return MilisecExecuteStartByInspection;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteCaptured(void)	const
{
	return MilisecExecuteCaptured;
}

DWORD	ExecuteTimeClass::GetMilisecExecutePreAlignment(void)	const
{
	return MilisecExecutePreAlignment;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteAlignment(void)	const
{
	return MilisecExecuteAlignment;
}

DWORD	ExecuteTimeClass::GetMilisecExecutePreProcessing(void)	const
{
	return MilisecExecutePreProcessing;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteProcessing(void)	const
{
	return MilisecExecuteProcessing;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteProcessingRevived(void)	const
{
	return MilisecExecuteProcessingRevived;
}

DWORD	ExecuteTimeClass::GetMilisecExecutePostProcessing(void)	const
{
	return MilisecExecutePostProcessing;
}

DWORD	ExecuteTimeClass::GetMilisecExecutePreScanning(void)	const
{
	return MilisecExecutePreScanning;
}

DWORD	ExecuteTimeClass::GetMilisecExecuteScanning(void)	const
{
	return MilisecExecuteScanning;
}

DWORD	ExecuteTimeClass::GetMilisecExecutePostScanning(void)	const
{
	return MilisecExecutePostScanning;
}
bool    ExecuteTimeClass::Save(QIODevice *f)
{
	if(::Save(f,MilisecExecuteInitialAfterEditPrev)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteInitialAfterEdit)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteInitialAfterEditPost)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteStartByInspection)==false){
		return false;
	}
	if(::Save(f,MilisecExecutePreAlignment)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteAlignment)==false){
		return false;
	}
	if(::Save(f,MilisecExecutePreProcessing)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteProcessing)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteProcessingRevived)==false){
		return false;
	}
	if(::Save(f,MilisecExecutePostProcessing)==false){
		return false;
	}
	if(::Save(f,MilisecExecutePreScanning)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteScanning)==false){
		return false;
	}
	if(::Save(f,MilisecExecutePostScanning)==false){
		return false;
	}
	if(::Save(f,MilisecExecuteCaptured)==false){
		return false;
	}
	return true;
}
bool    ExecuteTimeClass::Load(QIODevice *f)
{
	if(::Load(f,MilisecExecuteInitialAfterEditPrev)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteInitialAfterEdit)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteInitialAfterEditPost)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteStartByInspection)==false){
		return false;
	}
	if(::Load(f,MilisecExecutePreAlignment)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteAlignment)==false){
		return false;
	}
	if(::Load(f,MilisecExecutePreProcessing)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteProcessing)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteProcessingRevived)==false){
		return false;
	}
	if(::Load(f,MilisecExecutePostProcessing)==false){
		return false;
	}
	if(::Load(f,MilisecExecutePreScanning)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteScanning)==false){
		return false;
	}
	if(::Load(f,MilisecExecutePostScanning)==false){
		return false;
	}
	if(::Load(f,MilisecExecuteCaptured)==false){
		return false;
	}
	return true;
}

ExecuteTimeClass	&ExecuteTimeClass::operator=(const ExecuteTimeClass &src)
{
	MilisecExecuteInitialAfterEditPrev	=src.MilisecExecuteInitialAfterEditPrev;
	MilisecExecuteInitialAfterEdit		=src.MilisecExecuteInitialAfterEdit;
	MilisecExecuteInitialAfterEditPost	=src.MilisecExecuteInitialAfterEditPost;
	MilisecExecuteStartByInspection		=src.MilisecExecuteStartByInspection;
	MilisecExecuteCaptured				=src.MilisecExecuteCaptured;
	MilisecExecutePreAlignment			=src.MilisecExecutePreAlignment;
	MilisecExecuteAlignment				=src.MilisecExecuteAlignment;
	MilisecExecutePreProcessing			=src.MilisecExecutePreProcessing;
	MilisecExecuteProcessing			=src.MilisecExecuteProcessing;
	MilisecExecuteProcessingRevived		=src.MilisecExecuteProcessingRevived;
	MilisecExecutePostProcessing		=src.MilisecExecutePostProcessing;
	MilisecExecutePreScanning			=src.MilisecExecutePreScanning;
	MilisecExecuteScanning				=src.MilisecExecuteScanning;
	MilisecExecutePostScanning			=src.MilisecExecutePostScanning;	
	return *this;
}

GeneralPipeInfo::GeneralPipeInfo(AlgorithmBase *OriginBase)
{
	Cmd			=_GI_Nothing;

	BmpMap		=NULL;
	DriftMap	=NULL;
	OmitMap		=NULL;
	XByte		=0;
	YLen		=0;
	Vector		=NULL;
	LibID		=-1;
	Origin		=OriginBase;
}
GeneralPipeInfo::~GeneralPipeInfo(void)
{
	BmpMap		=NULL;
	DriftMap	=NULL;
	OmitMap		=NULL;
	XByte		=0;
	YLen		=0;
	Vector		=NULL;
	LibID		=-1;
}

AlgorithmInPageRoot::AlgorithmInPageRoot(void)
:PipeClass(this)
{
	CreatedTime	=XDateTime::currentDateTime();
	Page				=0;
	PDataInPage			=NULL;
	PInspectionData		=NULL;
	StartItemID			=0;
	Changed				=false;
	CalcDone			=false;
	ParentPhase			=NULL;

	ClearExecuteTime();
}

AlgorithmInPageRoot::~AlgorithmInPageRoot(void)
{
}

void	AlgorithmInPageRoot::Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)
{
	ParentPhase		=phaseParent;
	if(Base->GetPageDataPhase(phaseParent->GetPhaseCode())!=NULL){
		PDataInPage		=Base->GetPageDataPhase(phaseParent->GetPhaseCode())->GetPageData(GetPage());
	}
	PInspectionData	=Base->GetEntryPoint();
	SetLearn(Base);
}

int		AlgorithmInPageRoot::GetPhaseCode(void)	const
{
	if(ParentPhase!=NULL){
		return ParentPhase->GetPhaseCode();
	}
	return -1;
}
int		AlgorithmInPageRoot::GetLayerNumb(void)		const
{	
	if(GetDataInPage()!=NULL){
		return GetDataInPage()->GetLayerNumb();
	}
	return(GetLayersBase()->GetParamGlobal()->LayerNumb);
}

int		AlgorithmInPageRoot::GetGlobalPage(void)
{
	return GetLayersBase()->GetGlobalPageFromLocal(GetPage());
}
XYData	*AlgorithmInPageRoot::GetGlobalOutlineOffset(void)
{
	if(GetLayersBase()!=NULL){
		XYData	*XP=GetLayersBase()->GetGlobalOutlineOffset(GetGlobalPage());
		return XP;
	}
	return NULL;
}
void	AlgorithmInPageRoot::GetAlignmentForProcessing(AlignmentPacketBase &Packet)
{
	GetLayersBase()->GetAlignmentForProcessing(GetPage() ,Packet);
}
bool    AlgorithmInPageRoot::Save(QIODevice *f)
{
	return true;
}
bool    AlgorithmInPageRoot::Load(QIODevice *f)
{
	Changed=false;
	CalcDone=false;
	return true;
}

XYData	*AlgorithmInPageRoot::GetOutlineOffset(void)	const
{
	return GetDataInPage()->GetOutlineOffset();
}

ResultInPageRoot	*AlgorithmInPageRoot::GetResultPointer(ResultInspection *Res)	const
{
	ResultBaseForAlgorithmRoot	*R=Res->GetResultBaseForAlgorithm(GetParentBase());
	if(R!=NULL){
		ResultBasePhase		*Rh=R->GetPageDataPhase(GetPhaseCode());
		if(Rh!=NULL){
			ResultInPageRoot	*Rp=Rh->GetPageData(GetPage());
			if(Rp!=NULL){
				return Rp;
			}
		}
	}
	return NULL;
}

void	AlgorithmInPageRoot::MirrorItems(AlgorithmItemRoot::_MirrorMode MirrorMode,int PageNumb,QByteArray BuffData[])
{
	AlgorithmItemPointerListContainer	**Pointers=new AlgorithmItemPointerListContainer*[PageNumb];

	int	X1=99999999;
	int	Y1=99999999;
	int	X2=-99999999;
	int	Y2=-99999999;
	for(int globalpage=0;globalpage<PageNumb;globalpage++){
		Pointers[globalpage]=new AlgorithmItemPointerListContainer[GetLayerNumb()];
		QBuffer	Buff(&BuffData[globalpage]);
		Buff.open(QIODevice::ReadOnly);

		int32	Numb;
		::Load(&Buff,Numb);
		XYData	* XY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
		for(int k=0;k<Numb;k++){
			int32	Layer;
			if(::Load(&Buff,Layer)==false)
			break;
			int32	ItemClassType;
			if(::Load(&Buff,ItemClassType)==false)
				break;
			AlgorithmItemRoot	*Item=CreateItem(ItemClassType);
			if(Item==NULL)
				break;
			if(Item->Load(&Buff,GetLayersBase())==false)
				break;
			//Item->MoveTo(XY->x,XY->y);
			int	x1,y1,x2,y2;
			Item->GetXY(x1,y1,x2,y2);
			X1=min(X1,x1+XY->x);
			Y1=min(Y1,y1+XY->y);
			X2=max(X2,x2+XY->x);
			Y2=max(Y2,y2+XY->y);
			(Pointers[globalpage])[Layer].Add(Item);
		}
	}

	int	Cx=(X1+X2)/2;
	int	Cy=(Y1+Y2)/2;
	int	CurrentPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	AlgorithmItemPointerListContainer SelectedItemPointers;
	GetSelectedItems(SelectedItemPointers);

	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoMirrorItems);
	int	LayerNumb=GetLayerNumb();
	::Save(UndoPointer->GetWritePointer(),LayerNumb);

	for(int Layer=0;Layer<LayerNumb;Layer++){
		AlgorithmItemPointerListContainer	DestItemPointers;
		for(int globalpage=0;globalpage<PageNumb;globalpage++){
			XYData	* XY=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
			XYData	*cXY=GetLayersBase()->GetGlobalOutlineOffset(CurrentPage);
			for(AlgorithmItemPointerList *L=(Pointers[globalpage])[Layer].GetFirst();L!=NULL;){
				AlgorithmItemPointerList *NextP=L->GetNext();
				AlgorithmItemRoot	*Item=L->GetItem();
				Item->MirrorItem(MirrorMode,Cx-(XY->x+cXY->x)/2,Cy-(XY->y+cXY->y)/2);
				
				//Cx-(nx+XY->x-Cx)-cXY->x
				//2Cx - nx -XY->x - xXY->x

				Item->ClipPage(GetDotPerLine() ,GetMaxLines());
				if(Item->GetArea().GetPatternByte()==0){
					(Pointers[globalpage])[Layer].RemoveList(L);
					delete	Item;
					delete	L;
				}
				else{
					DestItemPointers.Add(Item);
				}
				L=NextP;
			}
		}
		int32	SelectedItemCount=0;
		for(AlgorithmItemPointerList *s=SelectedItemPointers.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetItem()!=NULL && s->GetItem()->GetLayer()==Layer){
				SelectedItemCount++;
			}
		}
		IntList	SelectedItemIDList;
		::Save(UndoPointer->GetWritePointer(),SelectedItemCount);
		for(AlgorithmItemPointerList *s=SelectedItemPointers.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetItem()!=NULL && s->GetItem()->GetLayer()==Layer){
				int32	ItemClassType=s->GetItem()->GetItemClassType();	
				::Save(UndoPointer->GetWritePointer(),ItemClassType);
				s->GetItem()->Save(UndoPointer->GetWritePointer());
				SelectedItemIDList.Add(s->GetItem()->GetID());
				s->SetPointer(NULL);
			}
		}
		RemoveItemsInPage(Layer,SelectedItemIDList);

		int	AddedItemCount=DestItemPointers.GetCount();
		::Save(UndoPointer->GetWritePointer(),AddedItemCount);

		AppendItemsInPage(Layer,DestItemPointers);

		for(AlgorithmItemPointerList *d=DestItemPointers.GetFirst();d!=NULL;d=d->GetNext()){
			::Save(UndoPointer->GetWritePointer(),d->GetItem()->GetID());
		}
	}		
	for(int globalpage=0;globalpage<PageNumb;globalpage++){
		delete	[]Pointers[globalpage];
	}
	delete	[]Pointers;

	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}

void	AlgorithmInPageRoot::UndoMirrorItems(QIODevice *f)
{
	int32	LayerNumb;

	if(::Load(f,LayerNumb)==false)
		return;
	for(int Layer=0;Layer<LayerNumb;Layer++){
		int32	SelectedItemCount;
		if(::Load(f,SelectedItemCount)==false)
			return;
		AlgorithmItemPointerListContainer SelectedItemPointers;
		for(int i=0;i<SelectedItemCount;i++){
			int32	ItemClassType;	
			if(::Load(f,ItemClassType)==false)
				return;
			AlgorithmItemRoot	*Item=CreateItem(ItemClassType);
			if(Item==NULL)
				break;
			if(Item->Load(f,GetLayersBase())==false)
				break;
			SelectedItemPointers.Add(Item);
		}
		int32	AddedItemCount;
		if(::Load(f,AddedItemCount)==false)
			return;
		IntList	IDList;
		for(int i=0;i<AddedItemCount;i++){
			int32	ID;
			if(::Load(f,ID)==false)
				return;
			IDList.Add(ID);
		}
		RemoveItemsInPage(Layer,IDList);
		AppendItemsInPage(Layer,SelectedItemPointers);
	}
}

bool	AlgorithmInPageRoot::IsInclude(int localX ,int localY)	const
{
	return GetDataInPage()->IsInclude(localX ,localY);
}
int	AlgorithmInPageRoot::GetMasterBuffList(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= L->GetMasterBuffPointer();
	}
	return layer;
}
int	AlgorithmInPageRoot::GetMasterBuffList(int n,ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= L->GetMasterBuffPointer(n);
	}
	return layer;
}
int	AlgorithmInPageRoot::GetTargetBuffList(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= &L->GetTargetBuff();
	}
	return layer;
}
int	AlgorithmInPageRoot::GetTargetTRBuffList(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= &L->GetTargetTRBuff();
	}
	return layer;
}
int	AlgorithmInPageRoot::GetDelayedViewBuffList(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= &L->GetDelayedViewBuff();
	}
	return layer;
}
int	AlgorithmInPageRoot::GetBitBuffList(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= &L->GetBitBuff();
	}
	return layer;
}
int	AlgorithmInPageRoot::GetTrialTargetBuffList	(ImageBuffer *ImageList[])	const
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	tLayerNumb=GetLayerNumb();
	for(layer=0;layer<tLayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]= &L->GetTrialTargetBuff();
	}
	return layer;
}
bool	AlgorithmInPageRoot::GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything)
{
	bool	Ret=true;
	int	tLayerNumb=GetLayerNumb();
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	for(int layer=0;layer<tLayerNumb;layer++){
		if(Map[layer]==NULL){
			Map.AppendList(new ConstMapBufferList());
		}
		if(Map[layer]->GetMapBuffer()!=NULL){
			if(LC->GetReflectionMap(Mode,*Map[layer]->GetMapBuffer() ,GetPhaseCode(),GetPage(),layer,LibData ,Anything)==false){
				Ret=false;
			}
		}
		else{
			ConstMapBuffer	*m=new ConstMapBuffer();
			if(LC->GetReflectionMap(Mode,*m ,GetPhaseCode(),GetPage(),layer,LibData ,Anything)==false){
				delete	m;
				Ret=false;
			}
			else{
				Map[layer]->Set(m);
			}
		}
	}
	return Ret;
}

bool	AlgorithmInPageRoot::GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,void *Anything)
{
	bool	Ret=true;
	int	tLayerNumb=GetLayerNumb();
	LogicDLLBaseClass	*LC=GetLayersBase()->GetLogicDLLBase();
	for(int layer=0;layer<tLayerNumb;layer++){
		if(Map[layer]==NULL){
			Map.AppendList(new ConstMapBufferList());
		}
		if(Map[layer]->GetMapBuffer()!=NULL){
			Map[layer]->GetMapBuffer()->ClearAll();
			if(LC->GetReflectionMap(Mode,*Map[layer]->GetMapBuffer()  ,GetPhaseCode(),GetPage(),layer ,Anything)==false){
				Ret=false;
			}
		}
		else{
			ConstMapBuffer	*m=new ConstMapBuffer();
			if(LC->GetReflectionMap(Mode,*m ,GetPhaseCode(),GetPage(),layer ,Anything)==false){
				delete	m;
				Ret=false;
			}
			else{
				Map[layer]->Set(m);
			}
		}
	}
	return Ret;
}
bool	AlgorithmInPageRoot::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionVector(Mode,Vector ,GetPhaseCode(),GetPage(),0,LibData ,Anything);
}
bool	AlgorithmInPageRoot::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->GetReflectionVector(Mode,Vector ,GetPhaseCode(),GetPage(),0,Anything);
}
bool	AlgorithmInPageRoot::IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything)
{
	return GetLayersBase()->GetLogicDLLBase()->IncludeLibInReflection(Mode,GetPage(),0,LibData ,Anything);
}

void	AlgorithmInPageRoot::SetStartTimeMilisec(void)
{
	StartTimeMilisec=::GetComputerMiliSec();
}

bool	AlgorithmInPageRoot::GetUsageLibInReflection(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret)
{
	return GetLayersBase()->GetLogicDLLBase()->GetUsageLibInReflection(Mode,GetPage(),0,Ret);
}


bool	AlgorithmInPageRoot::SaveMasterData(void)
{
	int MasterCode	=GetLayersBase()->GetMasterCode();
	int	MachineCode	=GetLayersBase()->GetMachineID();
	if(MasterCode<0 || MachineCode<0){
		return false;
	}
	QString ErrorMsg;
	bool	Ret=GetLayersBase()->SaveAlgorithmDataInMasterData(MasterCode,MachineCode
											,this
											,ErrorMsg);
	return Ret;
}

bool	AlgorithmInPageRoot::LoadMasterData(void)
{
	int MasterCode	=GetLayersBase()->GetMasterCode();
	int	MachineCode	=GetLayersBase()->GetMachineID();
	if(MasterCode<0 || MachineCode<0){
		return false;
	}
	QString ErrorMsg;
	bool	Ret=GetLayersBase()->LoadAlgorithmDataInMasterData(MasterCode,MachineCode
											,this
											,ErrorMsg);
	return Ret;
}

int		AlgorithmInPageRoot::GetLoadedVersion(void)
{
	if(GetParentBase()==NULL)
		return -1;
	return GetParentBase()->GetLoadedVersion();
}

void	AlgorithmInPageRoot::GetAffinParam(double SrcX1,double SrcY1
										,  double SrcX2,double SrcY2
										,  double SrcX3,double SrcY3
										,  double TargetX1,double TargetY1
										,  double TargetX2,double TargetY2
										,  double TargetX3,double TargetY3
										,  double Dest[6])
{
	double  PP[3][2];
	double  PQ[3][2];
	PP[0][0]=SrcX1;
	PP[0][1]=SrcY1;
	PP[1][0]=SrcX2;
	PP[1][1]=SrcY2;
	PP[2][0]=SrcX3;
	PP[2][1]=SrcY3;

	PQ[0][0]=TargetX1;
	PQ[0][1]=TargetY1;
	PQ[1][0]=TargetX2;
	PQ[1][1]=TargetY2;
	PQ[2][0]=TargetX3;
	PQ[2][1]=TargetY3;
	if(Get3LevelResolve(PP , PQ ,Dest)==false){
		Dest[0]=1.0;
		Dest[1]=0.0;
		Dest[2]=0.0;
		Dest[3]=0.0;
		Dest[4]=1.0;
		Dest[5]=0.0;
	}
}

void	AlgorithmInPageRoot::ClearExecuteTime(void)
{
	ExecuteTimeData.ClearExecuteTime();
}

void	AlgorithmInPageRoot::StartMilisecExecuteInitialAfterEditPrev(void)
{
	StartTimeExecuteInitialAfterEditPrev=QTime::currentTime ();
}
void	AlgorithmInPageRoot::StartMilisecExecuteInitialAfterEdit(void)
{
	StartTimeExecuteInitialAfterEdit	=QTime::currentTime ();
}
void	AlgorithmInPageRoot::StartMilisecExecuteInitialAfterEditPost(void)
{
	StartTimeExecuteInitialAfterEditPost=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteStartByInspection(void)
{
	StartTimeExecuteStartByInspection=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteCaptured(void)
{
	StartTimeExecuteCaptured=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecutePreAlignment(void)
{
	StartTimeExecutePreAlignment=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteAlignment(void)
{
	StartTimeExecuteAlignment=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecutePreProcessing(void)
{
	StartTimeExecutePreProcessing=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteProcessing(void)
{
	StartTimeExecuteProcessing=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteProcessingRevived(void)
{
	StartTimeExecuteProcessingRevived=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecutePostProcessing(void)
{
	StartTimeExecutePostProcessing=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecutePreScanning(void)
{
	StartTimeExecutePreScanning=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecuteScanning(void)
{
	StartTimeExecuteScanning=QTime::currentTime ();
}

void	AlgorithmInPageRoot::StartMilisecExecutePostScanning(void)
{
	StartTimeExecutePostScanning=QTime::currentTime ();
}


void	AlgorithmInPageRoot::EndMilisecExecuteInitialAfterEditPrev(void)
{
	ExecuteTimeData.MilisecExecuteInitialAfterEditPrev=StartTimeExecuteInitialAfterEditPrev.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteInitialAfterEdit(void)
{
	ExecuteTimeData.MilisecExecuteInitialAfterEdit=StartTimeExecuteInitialAfterEdit.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteInitialAfterEditPost(void)
{
	ExecuteTimeData.MilisecExecuteInitialAfterEditPost=StartTimeExecuteInitialAfterEditPost.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteStartByInspection(void)
{
	ExecuteTimeData.MilisecExecuteStartByInspection=StartTimeExecuteStartByInspection.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteCaptured(void)
{
	ExecuteTimeData.MilisecExecuteCaptured=StartTimeExecuteCaptured.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecutePreAlignment(void)
{
	ExecuteTimeData.MilisecExecutePreAlignment=StartTimeExecutePreAlignment.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteAlignment(void)
{
	ExecuteTimeData.MilisecExecuteAlignment=StartTimeExecuteAlignment.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecutePreProcessing(void)
{
	ExecuteTimeData.MilisecExecutePreProcessing=StartTimeExecutePreProcessing.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteProcessing(void)
{
	ExecuteTimeData.MilisecExecuteProcessing=StartTimeExecuteProcessing.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteProcessingRevived(void)
{
	ExecuteTimeData.MilisecExecuteProcessingRevived=StartTimeExecuteProcessingRevived.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecutePostProcessing(void)
{
	ExecuteTimeData.MilisecExecutePostProcessing=StartTimeExecutePostProcessing.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecutePreScanning(void)
{
	ExecuteTimeData.MilisecExecutePreScanning=StartTimeExecutePreScanning.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecuteScanning(void)
{
	ExecuteTimeData.MilisecExecuteScanning=StartTimeExecuteScanning.msecsTo (QTime::currentTime());
}

void	AlgorithmInPageRoot::EndMilisecExecutePostScanning(void)
{
	ExecuteTimeData.MilisecExecutePostScanning=StartTimeExecutePostScanning.msecsTo (QTime::currentTime());
}


DWORD	AlgorithmInPageRoot::GetMilisecExecuteInitialAfterEditPrev(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteInitialAfterEditPrev();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteInitialAfterEdit(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteInitialAfterEdit();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteInitialAfterEditPost(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteInitialAfterEditPost();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteStartByInspection(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteStartByInspection();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteCaptured(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteCaptured();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecutePreAlignment(void)	const
{
	return ExecuteTimeData.GetMilisecExecutePreAlignment();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteAlignment(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteAlignment();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecutePreProcessing(void)	const
{
	return ExecuteTimeData.GetMilisecExecutePreProcessing();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteProcessing(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteProcessing();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteProcessingRevived(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteProcessingRevived();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecutePostProcessing(void)	const
{
	return ExecuteTimeData.GetMilisecExecutePostProcessing();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecutePreScanning(void)	const
{
	return ExecuteTimeData.GetMilisecExecutePreScanning();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecuteScanning(void)	const
{
	return ExecuteTimeData.GetMilisecExecuteScanning();
}

DWORD	AlgorithmInPageRoot::GetMilisecExecutePostScanning(void)	const
{
	return ExecuteTimeData.GetMilisecExecutePostScanning();
}
	
//----------- Unit-------------
	
bool	AlgorithmInPageRoot::IsUnitMode(void)	const
{
	return GetParamGlobal()->IsUnitMode();
}

double	AlgorithmInPageRoot::TransformPixelToUnit(double pixel)	const
{
	return GetParamGlobal()->TransformPixelToUnit(GetPage(),pixel);
}

double	AlgorithmInPageRoot::TransformUnitToPixel(double unit)	const
{
	return GetParamGlobal()->TransformUnitToPixel(GetPage(),unit);
}

QString	AlgorithmInPageRoot::TransformPixelToUnitStr(double pixel)	const
{
	return GetParamGlobal()->TransformPixelToUnitStr(GetPage(),pixel);
}

QString	AlgorithmInPageRoot::GetUnitStr(double unit)	const
{
	return GetParamGlobal()->GetUnitStr(unit);
}


double	AlgorithmInPageRoot::TransformPixelToUnitSquare(double pixel)	const
{
	return GetParamGlobal()->TransformPixelToUnitSquare(GetPage(),pixel);
}

double	AlgorithmInPageRoot::TransformUnitToPixelSquare(double unit)	const
{
	return GetParamGlobal()->TransformUnitToPixelSquare(GetPage(),unit);
}

QString	AlgorithmInPageRoot::TransformPixelToUnitSquareStr(double pixel)	const
{
	return GetParamGlobal()->TransformPixelToUnitSquareStr(GetPage(),pixel);
}

QString	AlgorithmInPageRoot::GetUnitSquareStr(double unit)	const
{
	return GetParamGlobal()->GetUnitSquareStr(unit);
}
//===========================================================================================================
AlgorithmInPageInOnePhase::AlgorithmInPageInOnePhase(int phaseCode ,AlgorithmBase *Base)
{
	ParentBase	=Base;
	Parent		=Base->GetLayersBase();
	PhaseCode=phaseCode;
	PageData=NULL;
	AllocatedPageNumb=0;
	EffectivePageNumb=0;
	EnableExecute	=true;
}
AlgorithmInPageInOnePhase::~AlgorithmInPageInOnePhase(void)
{
	Release();
}

void	AlgorithmInPageInOnePhase::InitialCreate()
{
	EffectivePageNumb=ParentBase->GetPageNumb();
	if(PageData!=NULL){
		if(AllocatedPageNumb<ParentBase->GetPageNumb()){
			Release();
		}
		else{
			for(int i=0;i<ParentBase->GetPageNumb();i++){
				if(PageData[i]==NULL){
					PageData[i]=ParentBase->NewChild(ParentBase);
				}
				PageData[i]->SetPage(i);
				PageData[i]->Set(this);
				PageData[i]->Initial(this,ParentBase->GetLayersBase());
			}
		}
	}
	if(PageData==NULL){
		AllocatedPageNumb=2*ParentBase->GetPageNumb();
		if(AllocatedPageNumb<20){
			AllocatedPageNumb=20;
		}
		PageData=new AlgorithmInPageRoot*[AllocatedPageNumb];
		for(int i=0;i<AllocatedPageNumb;i++){
			PageData[i]=NULL;
		}
		for(int i=0;i<ParentBase->GetPageNumb();i++){
			PageData[i]=ParentBase->NewChild(ParentBase);
			PageData[i]->SetPage(i);
			PageData[i]->Set(this);
			PageData[i]->Initial(this,ParentBase->GetLayersBase());
		}
	}
}
void	AlgorithmInPageInOnePhase::Release(void)
{
	if(PageData!=NULL){
		for(int i=0;i<AllocatedPageNumb;i++){
			if(PageData[i]!=NULL){
				delete	PageData[i];
			}
		}
		delete	[]PageData;
	}
	PageData=NULL;
	AllocatedPageNumb=0;
	EffectivePageNumb=0;
}
bool	AlgorithmInPageInOnePhase::Reallocate(int newPageNumb ,int newLayerNumb)
{
	if(AllocatedPageNumb<newPageNumb){
		AlgorithmInPageRoot	**tPageData=new AlgorithmInPageRoot*[newPageNumb];
		int	i;
		for(i=0;i<AllocatedPageNumb;i++){
			if(PageData[i]==NULL){
				break;
			}
			tPageData[i]=PageData[i];
			tPageData[i]->Reallocate(newLayerNumb);
		}
		delete	[]PageData;
		PageData=tPageData;
		for(;i<newPageNumb;i++){
			PageData[i]=ParentBase->NewChild(ParentBase);
			//PageData[i]->Parent=this;
			PageData[i]->SetPage(i);
			PageData[i]->Set(this);
			PageData[i]->Initial(this,ParentBase->GetLayersBase());
		}
	}
	else if(AllocatedPageNumb>newPageNumb){
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=ParentBase->NewChild(ParentBase);
				//PageData[i]->Parent=this;
				PageData[i]->SetPage(i);
				PageData[i]->Set(this);
				PageData[i]->Initial(this,ParentBase->GetLayersBase());
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
		for(int i=newPageNumb;i<AllocatedPageNumb;i++){
			if(PageData[i]!=NULL){
				delete	PageData[i];
				PageData[i]=NULL;
			}
		}
		AllocatedPageNumb	=newPageNumb;
	}
	else{
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=ParentBase->NewChild(ParentBase);
				//PageData[i]->Parent=this;
				PageData[i]->SetPage(i);
				PageData[i]->Set(this);
				PageData[i]->Initial(this,ParentBase->GetLayersBase());
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
	}
	EffectivePageNumb	=newPageNumb;
	return true;
}
bool	AlgorithmInPageInOnePhase::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		if(PageData[i]->ReallocateMasterCount(CountMaster)==false){
			Ret=false;
		}
	}
	return Ret;
}
	
bool	AlgorithmInPageInOnePhase::InsertPage(int IndexPage)	//Create page before Indexed page
{
	LayersBase	*LBase=ParentBase->GetLayersBase();
	int	sPageNumb=AllocatedPageNumb;
	AlgorithmInPageRoot	**tPageData=new AlgorithmInPageRoot*[sPageNumb+1];
	if(0<=IndexPage){
		if(0<=IndexPage){
		    int dpage=0;
			int spage=0;
			for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
				tPageData[dpage]=PageData[spage];
				PageData[spage]=NULL;
			}
			tPageData[dpage]=ParentBase->NewChild(ParentBase);
			//PageData[i]->Parent=this;
			tPageData[dpage]->SetPage(dpage);
			tPageData[dpage]->Set(this);
			DataInPage	*Dp=LBase->GetPageDataPhase(GetPhaseCode())->GetPageData(dpage);
			tPageData[dpage]->SetPDataInPage(Dp);
			tPageData[dpage]->SetPInspectionData(LBase->GetEntryPoint());
			tPageData[dpage]->Initial(this,LBase);
			dpage++;
			for(;spage<AllocatedPageNumb && dpage<sPageNumb+1;dpage++,spage++){
				tPageData[dpage]=PageData[spage];
				tPageData[dpage]->SetPage(dpage);
				PageData[spage]=NULL;
			}
		}
		else{
		    int dpage=0;
			int spage=0;
			for(;spage<AllocatedPageNumb;spage++,dpage++){
				tPageData[dpage]=PageData[spage];
				PageData[spage]=NULL;
			}
			tPageData[dpage]=ParentBase->NewChild(ParentBase);
			//PageData[i]->Parent=this;
			tPageData[dpage]->SetPage(dpage);
			tPageData[dpage]->Set(this);
			DataInPage	*Dp=LBase->GetPageDataPhase(GetPhaseCode())->GetPageData(dpage);
			tPageData[dpage]->SetPDataInPage(Dp);
			tPageData[dpage]->SetPInspectionData(LBase->GetEntryPoint());
			tPageData[dpage]->Initial(this,ParentBase->GetLayersBase());
		}
		delete	[]PageData;
		PageData=tPageData;
		AllocatedPageNumb	=sPageNumb+1;
		EffectivePageNumb	=sPageNumb+1;
	}
	return true;
}

bool	AlgorithmInPageInOnePhase::RemovePage(int IndexPage)
{
	int	sPageNumb=AllocatedPageNumb;
	AlgorithmInPageRoot	**tPageData=new AlgorithmInPageRoot*[sPageNumb-1];
	if(0<=IndexPage){
	    int dpage=0;
		int spage=0;
		for(;spage<AllocatedPageNumb && spage<IndexPage;spage++,dpage++){
			tPageData[dpage]=PageData[spage];
			PageData[dpage]=NULL;
		}
		delete	PageData[spage];
		spage++;
		for(;spage<AllocatedPageNumb && dpage<sPageNumb;dpage++,spage++){
			tPageData[dpage]=PageData[spage];
			tPageData[dpage]->SetPage(dpage);
			PageData[dpage]=NULL;
		}
		delete	[]PageData;
		PageData=tPageData;

		AllocatedPageNumb	=sPageNumb-1;
		EffectivePageNumb	=sPageNumb-1;
	}
	return true;
}


void	AlgorithmInPageInOnePhase::InitializeFromParts(void)
{
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		PageData[i]->InitializeFromParts();
	}
}
void	AlgorithmInPageInOnePhase::InitializeToStart(void)
{
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		PageData[i]->InitializeToStart();
	}
}
void	AlgorithmInPageInOnePhase::InitialAfterParamLoaded(void)
{
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		PageData[i]->InitialAfterParamLoaded();
	}
}

bool	AlgorithmInPageInOnePhase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		if(PageData[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	AlgorithmInPageInOnePhase::SizeChanged(AlgorithmBase *Base)
{
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		PageData[i]->SizeChanged(Base->GetLayersBase());
	}
}
bool	AlgorithmInPageInOnePhase::RemovePage(AlgorithmInPageRoot *pData)
{
	for(int i=0;i<AllocatedPageNumb;i++){
		if(PageData[i]==pData){
			pData->Release();
			delete	pData;
			PageData[i]=NULL;
			return true;
		}	
	}
	return false;
}

void	AlgorithmInPageInOnePhase::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	for(int i=0;i<ParentBase->GetPageNumb();i++){
		if(GetPageData(i)!=NULL){
			GetPageData(i)->DeliverTransmitDirectly(packet);
		}
	}
}

AlgorithmInPageRoot	*AlgorithmInPageInOnePhase::SetPageData(int page,AlgorithmInPageRoot *pData)
{
	AlgorithmInPageRoot	*Ret=PageData[page];
	PageData[page]=pData;
	return Ret;
}
bool	AlgorithmInPageInOnePhase::Save(AlgorithmBase *Base,QIODevice *f)
{
	if(Base->GetModeLoadSaveInPlayer()==true || (Base->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(::Save(f,EnableExecute)==false){
			return false;
		}
		for(int i=0;i<ParentBase->GetPageNumb();i++){
			if(GetPageData(i)!=NULL && GetPageData(i)->Save(f)==false){
			    return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::Load(AlgorithmBase *Base,QIODevice *f)
{
	if(PageData!=NULL){
		Release();
	}
	if(Base->GetModeLoadSaveInPlayer()==true || (Base->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		AllocatedPageNumb=Base->GetPageNumb();
		EffectivePageNumb=Base->GetPageNumb();
		EnableExecute=true;
		if(Base->GetLayersBase()->GetVersion()>=12){
			if(::Load(f,EnableExecute)==false){
				return false;
			}
		}

		PageData=new AlgorithmInPageRoot*[AllocatedPageNumb];
		int	i;
		for(i=0;i<Base->GetPageNumb();i++){
			PageData[i]=Base->NewChild(Base);
			PageData[i]->SetPage(i);
			PageData[i]->Set(this);
			PageData[i]->SetPDataInPage(Base->GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(i));
			PageData[i]->SetPInspectionData(Base->GetLayersBase()->GetEntryPoint());
			if(PageData[i]->Load(f)==false){
                return(false);
			}
		}
		/*
		for(;i<N;i++){
			AlgorithmInPageRoot  *L=Base->NewChild(Base);
			L->SetPage(i);
			L->SetPDataInPage		(Base->GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(i));
			L->SetPInspectionData	(Base->GetLayersBase()->GetEntryPoint());
			if(L->Load(f)==false){
                return(false);
			}
			delete	L;
		}
		*/
	}
	return true;
}
	
bool	AlgorithmInPageInOnePhase::SaveOnly(QIODevice *f)
{
	if(::Save(f,EnableExecute)==false){
		return false;
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::LoadOnly(QIODevice *f)
{
	if(::Load(f,EnableExecute)==false){
		return false;
	}
	return true;
}

bool	AlgorithmInPageInOnePhase::SaveHistgram(AlgorithmBase *Base,QIODevice *f)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL && GetPageData(i)->SaveHistgram(f)==false){
            return false;
		}
	}
	return true;
}

bool	AlgorithmInPageInOnePhase::LoadHistgram(AlgorithmBase *Base,QIODevice *f)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL && GetPageData(i)->LoadHistgram(f)==false){
            return false;
		}
	}
	return true;
}
	
bool	AlgorithmInPageInOnePhase::SaveOnlyThreshold(QIODevice *f)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL){
			if(GetPageData(i)->SaveOnlyThreshold(f)==false){
				return false;
			}
		}
	}
	return true;
}	
bool	AlgorithmInPageInOnePhase::LoadOnlyThreshold(QIODevice *f)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL){
			if(GetPageData(i)->LoadOnlyThreshold(f)==false){
				return false;
			}
		}
	}
	return true;
}
void	AlgorithmInPageInOnePhase::ClearHistgram(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL){
			GetPageData(i)->ClearHistgram();
		}
	}
}

void	AlgorithmInPageInOnePhase::EnumLibID(IntList &LibIDList)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int i=0;i<tPageNumb;i++){
		if(GetPageData(i)!=NULL){
			GetPageData(i)->EnumLibID(LibIDList);
		}
	}
}

void	AlgorithmInPageInOnePhase::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(int i=0;i<GetEffectivePageNumb();i++){
		if(GetPageData(i)!=NULL){
			GetPageData(i)->Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
	}
}
void	AlgorithmInPageInOnePhase::DrawMove(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if((0<=localPage) && (localPage<GetEffectivePageNumb())){
		if(GetPageData(localPage)!=NULL){
			GetPageData(localPage)->DrawMove(dx,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
		}
	}
}

bool	AlgorithmInPageInOnePhase::DrawResultBase(ResultBasePhase *Res,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	PntFromIData.setPen(Qt::red);
	if(Res!=NULL){
		ResultInPageRoot	*R=Res->GetPageData(localPage);
		if(R==NULL){
			R=Res->GetPageData(localPage);
		}
		if(GetPageData(localPage)!=NULL
		&& GetPageData(localPage)->DrawResult(R,IData ,PntFromIData ,MovX ,MovY ,ZoomRate)==false){
			return false;
		}
	}
	else{
		if(GetPageData(localPage)!=NULL
		&& GetPageData(localPage)->DrawResult(NULL,IData ,PntFromIData ,MovX ,MovY ,ZoomRate)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::DrawResultItem(ResultBasePhase *Res,IntList &LayerList ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	PntFromIData.setPen(Qt::red);
	for(int page=0;page<GetEffectivePageNumb();page++){
		if(Res!=NULL){
			ResultInPageRoot	*R=Res->GetPageData(page);
			if(R==NULL){
				R=Res->GetPageData(page);
			}
			if(GetPageData(page)!=NULL
			&& GetPageData(page)->DrawResultItem(R,LayerList ,IData ,PntFromIData ,MovX ,MovY ,ZoomRate,OnlyNG)==false){
				return false;
			}
		}
		else{
			if(GetPageData(page)!=NULL
			&& GetPageData(page)->DrawResultItem(NULL,LayerList ,IData ,PntFromIData ,MovX ,MovY ,ZoomRate,OnlyNG)==false){
				return false;
			}
		}
	}
	return true;
}
AlgorithmItemRoot	*AlgorithmInPageInOnePhase::FindItem(const AlgorithmItemIndex &Index) const
{
	AlgorithmInPageRoot		*d=GetPageData(Index.GetPage());
	if(d!=NULL){
		return d->FindItem(Index);
	}
	return NULL;
}
bool	AlgorithmInPageInOnePhase::IsCalcDone(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::IsEdited(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL && d->IsEdited()==true){
			return true;
		}
	}
	return false;
}

void	AlgorithmInPageInOnePhase::SetEdited(bool edited)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->SetEdited(edited);
		}
	}
}
int		AlgorithmInPageInOnePhase::GetLoadedVersion(void)
{
	if(GetParentBase()==NULL)
		return -1;
	return GetParentBase()->GetLoadedVersion();
}
bool	AlgorithmInPageInOnePhase::ManualExecuteAll(ManualExecuter &ManualExecuterData)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			if(d->ManualExecuteAll(ManualExecuterData)==false){
				return false;
			}
		}
	}
	return true;
}
AlgorithmItemRoot	*AlgorithmInPageInOnePhase::SearchItemByName(const QString &ItemName ,int *Page ,int *Layer)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			AlgorithmItemRoot	*r=d->SearchItemByName(ItemName);
			if(r!=NULL){
				if(Page!=NULL){
					*Page=page;
				}
				if(Layer!=NULL){
					*Layer=r->GetLayer();
				}
				return r;
			}
		}
	}
	return NULL;
}
void	AlgorithmInPageInOnePhase::ResetProcessDone(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->ResetProcessDone();
		}
	}
}

bool	AlgorithmInPageInOnePhase::IsProcessDone(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			if(d->IsProcessDone()==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmInPageInOnePhase::SetProcessDone(bool b)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->SetProcessDone(b);
		}
	}
}

void	AlgorithmInPageInOnePhase::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->SwitchThresholdLevel(OldLevel ,NewLevel);
		}
	}
}
void	AlgorithmInPageInOnePhase::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->CopyThresholdLevel(SourceLevelID ,DestLevelID);
		}
	}
}
void	AlgorithmInPageInOnePhase::ClearResult(void)
{
	int	tPageNumb=ParentBase->GetPageNumb();
	for(int page=0;page<tPageNumb;page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->ClearResult();
		}
	}
}

void	AlgorithmInPageInOnePhase::MoveItemsToDispatcherForLoadingParts(void)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot		*P=GetPageData(page);
		if(P!=NULL){
			P->MoveItemsToDispatcherForLoadingParts();
		}
	}
}
void	AlgorithmInPageInOnePhase::CopyItemsFormDispatcherForParts(void)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot		*P=GetPageData(page);
		if(P!=NULL){
			P->CopyItemsFormDispatcherForParts();
		}
	}
}
void	AlgorithmInPageInOnePhase::RemoveItemFormDispatcher(void)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot		*P=GetPageData(page);
		if(P!=NULL){
			P->RemoveItemFormDispatcher();
		}
	}
}
bool	AlgorithmInPageInOnePhase::GeneralDataRelease(int32 Command,void *data)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL && P->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	*AlgorithmInPageInOnePhase::GeneralDataCreate(int32 Command,void *reqData)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL){
			void	*ret=P->GeneralDataCreate(Command,reqData);
			if(ret!=NULL){
				return ret;
			}
		}
	}
	return NULL;
}
bool	AlgorithmInPageInOnePhase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL && P->GeneralDataLoad(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL && P->GeneralDataSave(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::GeneralDataReply(int32 Command,void *data)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL && P->GeneralDataReply(Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPageInOnePhase::SaveCSVMasterReport(QStringListListCSV &CSVData)
{
	QStringListListCSV AlgoSVData;
	for(int page=0;page<ParentBase->GetPageNumb();page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		QStringListListCSV CSVDataInPage;
		if(d!=NULL && d->SaveCSVMasterReport(CSVDataInPage)==true){
			return false;
		}
		if(CSVDataInPage.count()!=0){
			AlgoSVData+=CSVDataInPage;
		}
	}
	if(AlgoSVData.count()!=0){
		QStringList	AlgoTitle;
		AlgoTitle.append(DefAlgorithmPath);
		AlgoTitle.append(QString("Phase")+QString::number(PhaseCode));
		AlgoTitle.append(ParentBase->GetLogicDLL()->GetDLLRoot());
		AlgoTitle.append(ParentBase->GetLogicDLL()->GetDLLName());
		CSVData<<AlgoTitle;
		CSVData<<AlgoSVData;
	}
	return true;
}

void	AlgorithmInPageInOnePhase::EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		P->EnumItems(caller,Items , func);
	}
}

void	AlgorithmInPageInOnePhase::ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		P->ScanItems(caller,func);
	}
}

void	AlgorithmInPageInOnePhase::MoveForAlignment(void)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*Ap=GetPageData(page);
		if(Ap!=NULL){
			Ap->MoveForAlignment();
		}
	}
}

int		AlgorithmInPageInOnePhase::GetSelectedItemCount(void)
{
	int	ret=0;
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL){
			ret+=P->GetSelectedItemCount();
		}
	}
	return ret;
}
void	AlgorithmInPageInOnePhase::ReleaseAllSelectedItem(void)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL){
			P->ReleaseAllSelectedItem();
		}
	}
}
void	AlgorithmInPageInOnePhase::EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		ListPhasePageLayerLibIDPack TmpIDList;
		AlgorithmInPageRoot	*P=GetPageData(page);
		P->EnumItems(TmpIDList);
		ItemIDList.AddMove(TmpIDList);
	}
}

//===========================================================================================================
bool	AlgorithmBase::RegisteredHistgramList::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	return true;
}
bool	AlgorithmBase::RegisteredHistgramList::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	return true;
}
AlgorithmBase::RegisteredHistgramList	&AlgorithmBase::RegisteredHistgramList::operator=(const AlgorithmBase::RegisteredHistgramList &src)
{
	Name=src.Name;
	ID	=src.ID;
	return *this;
}

bool	AlgorithmBase::RegisteredHistgramListContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(RegisteredHistgramList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	AlgorithmBase::RegisteredHistgramListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		RegisteredHistgramList *a=new RegisteredHistgramList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
AlgorithmBase::RegisteredHistgramListContainer	&AlgorithmBase::RegisteredHistgramListContainer::operator=(const AlgorithmBase::RegisteredHistgramListContainer &src)
{
	RemoveAll();
	for(RegisteredHistgramList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		RegisteredHistgramList *b=new RegisteredHistgramList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

//===========================================================================================================

AlgorithmBase::AlgorithmBase(LayersBase *Base)
:ParamBaseForAlgorithm(),ServiceForLayers(Base)
{
	CreatedTime				=XDateTime::currentDateTime();
	PageDataPhase			=NULL;
	AllocatedPhaseNumb		=0;
	LogicDLLPoint			=NULL;
	CacheLib				=new AlgorithmLibraryListContainer();
	ManagedCacheLib			=new AlgorithmLibraryStocker();
	Changed					=false;
	CalcDone				=false;
	EnableToSave			=true;
	ModeToShowNGMark		=true;
	ModeLoadSaveInPlayer	=true;
	EnableMoveForAlignment	=true;
	MaxMilisecInPage		=1000000;

	ModeParallelForPhase.ModeParallelExecuteInitialAfterEditPrev=true;
	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit	=true;
	ModeParallelForPhase.ModeParallelExecuteInitialAfterEditPost=true;
	ModeParallelForPhase.ModeParallelExecuteStartByInspection	=true;
	ModeParallelForPhase.ModeParallelExecuteCaptured			=true;
	ModeParallelForPhase.ModeParallelExecutePreAlignment		=true;
	ModeParallelForPhase.ModeParallelExecuteAlignment			=true;
	ModeParallelForPhase.ModeParallelExecutePreProcessing		=true;
	ModeParallelForPhase.ModeParallelExecuteProcessing			=false;
	ModeParallelForPhase.ModeParallelExecuteProcessingRevived	=true;
	ModeParallelForPhase.ModeParallelExecutePostProcessing		=true;
	ModeParallelForPhase.ModeParallelExecutePreScanning			=true;
	ModeParallelForPhase.ModeParallelExecuteScanning			=true;
	ModeParallelForPhase.ModeParallelExecutePostScanning		=true;

	SetParam(&ModeToShowNGMark		, /**/"Setting" ,/**/"ModeToShowNGMark"		,"Mode to show NG Mark");
	SetParam(&ModeLoadSaveInPlayer	, /**/"Setting" ,/**/"ModeLoadSaveInPlayer"	,"Mode to save/load data");
	SetParam(&MaxMilisecInPage		, /**/"Setting" ,/**/"MaxMilisecInPage"		,"Maximum milisec for process in each page");
}
AlgorithmBase::~AlgorithmBase(void)
{
	if(CacheLib!=NULL){
		delete	CacheLib;
		CacheLib=NULL;
	}
	if(ManagedCacheLib!=NULL){
		delete	ManagedCacheLib;
		ManagedCacheLib=NULL;
	}
	ReleaseData();
}

void	AlgorithmBase::ReleaseData(void)
{
	if(PageDataPhase!=NULL){
		for(int i=0;i<AllocatedPhaseNumb;i++){
			if(PageDataPhase[i]!=NULL){
				delete	PageDataPhase[i];
			}
		}
		delete	[]PageDataPhase;
	}
	PageDataPhase	=NULL;
	AllocatedPhaseNumb	=0;
}
ModelType	AlgorithmBase::GetModel(void)
{
	AlgorithmInPageRoot	*p=GetPageData(0);
	if(p!=NULL){
		return p->GetModel();
	}
	p=NewChild(this);
	if(p!=NULL){
		ModelType	Ret=p->GetModel();
		delete	p;
		return Ret;
	}
	return Model_PLI;
}

const	QString	AlgorithmBase::GetExplain(void)
{
	LogicDLL	*L=GetLogicDLL();
	if(L!=NULL){
		return L->GetExplain();
	}
	return /**/"";
}
QString	AlgorithmBase::GetNameByCurrentLanguage(void)
{
	QString DLLRoot ,DLLName;
	if(GetAlgorithmRootName(DLLRoot ,DLLName)==true){
		return DLLRoot+QString(':')+DLLName;
	}
	return GetExplain();
}

void	AlgorithmBase::Initial(LayersBase *Base)
{
	if(Base!=NULL){
		SetLayersBase(Base);
	}
	SetLearn(GetLayersBase());

	if(PageDataPhase!=NULL){
		if(AllocatedPhaseNumb<GetLayersBase()->GetPhaseNumb()){
			ReleaseData();
		}
		else{
			for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
				}
				PageDataPhase[i]->InitialCreate();
			}
		}
	}
	if(PageDataPhase==NULL){
		AllocatedPhaseNumb=2*GetLayersBase()->GetPhaseNumb();
		if(AllocatedPhaseNumb<5){
			AllocatedPhaseNumb=5;
		}
		PageDataPhase=new AlgorithmInPageInOnePhase*[AllocatedPhaseNumb];
		for(int i=0;i<AllocatedPhaseNumb;i++){
			PageDataPhase[i]=NULL;
		}
		for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
			PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
			PageDataPhase[i]->InitialCreate();
		}
	}
}
bool	AlgorithmBase::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocatedPhaseNumb){
			AlgorithmInPageInOnePhase	**iPageDataPhase=new AlgorithmInPageInOnePhase*[newPhaseNumb];
			int	i;
			for(i=0;i<AllocatedPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					break;
				}
				iPageDataPhase[i]=PageDataPhase[i];
				iPageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
			}
			delete	[]PageDataPhase;
			PageDataPhase=iPageDataPhase;
			for(;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
				iPageDataPhase[i]->InitialCreate();
			}
		}
		else if(newPhaseNumb<AllocatedPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate();
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
			for(int i=newPhaseNumb;i<AllocatedPhaseNumb;i++){
				if(PageDataPhase[i]!=NULL){
					delete	PageDataPhase[i];
					PageDataPhase[i]=NULL;
				}
			}
		}
		else{
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate();
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
		}
		AllocatedPhaseNumb=newPhaseNumb;
	}
	else{
		Initial(GetLayersBase());
	}
	return true;
}

bool	AlgorithmBase::Reallocate(int newPhaseNumb)
{
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocatedPhaseNumb){
			AlgorithmInPageInOnePhase	**iPageDataPhase=new AlgorithmInPageInOnePhase*[newPhaseNumb];
			int	i;
			for(i=0;i<AllocatedPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					break;
				}
				iPageDataPhase[i]=PageDataPhase[i];
			}
			delete	[]PageDataPhase;
			PageDataPhase=iPageDataPhase;
			for(;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
				iPageDataPhase[i]->InitialCreate();
			}
		}
		else if(newPhaseNumb<AllocatedPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate();
				}
			}
			for(int i=newPhaseNumb;i<AllocatedPhaseNumb;i++){
				if(PageDataPhase[i]!=NULL){
					delete	PageDataPhase[i];
					PageDataPhase[i]=NULL;
				}
			}
		}
		else{
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new AlgorithmInPageInOnePhase(i,this);
					PageDataPhase[i]->InitialCreate();
				}
			}
		}
		AllocatedPhaseNumb=newPhaseNumb;
	}
	else{
		Initial(GetLayersBase());
	}
	return true;
}
bool	AlgorithmBase::RemovePhase(int RemovedPhaseCode)
{
	if(PageDataPhase!=NULL){
		if(0<=RemovedPhaseCode && RemovedPhaseCode<AllocatedPhaseNumb){
			delete	PageDataPhase[RemovedPhaseCode];
		}	
		for(int phase=RemovedPhaseCode+1;phase<AllocatedPhaseNumb;phase++){
			PageDataPhase[phase-1]=PageDataPhase[phase];
		}
		for(int phase=GetParamGlobal()->PhaseNumb;phase<AllocatedPhaseNumb;phase++){
			PageDataPhase[phase]=NULL;
		}
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetPageDataPhase(phase)->SetPhaseCode(phase);
	}
	return true;
}
bool	AlgorithmBase::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->ReallocateMasterCount(CountMaster)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	AlgorithmBase::InsertPage(int IndexPage)
{
	bool	Ret=true;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(GetPageDataPhase(phase)->InsertPage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	AlgorithmBase::RemovePage(int IndexPage)
{
	bool	Ret=true;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(GetPageDataPhase(phase)->RemovePage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}
void	AlgorithmBase::InitializeToStart(void)
{
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		PageDataPhase[i]->InitializeToStart();
	}

}
void	AlgorithmBase::SizeChanged(void)
{
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		PageDataPhase[i]->SizeChanged(this);
	}
}
AlgorithmInPageRoot		*AlgorithmBase::GetPageData(int page)	const
{	
	int	Phase=GetLayersBase()->GetCurrentPhase();
	if(0<=Phase && Phase<GetPhaseNumb()){
		if(PageDataPhase[Phase]!=NULL){
			return PageDataPhase[Phase]->GetPageData(page);
		}
	}
	return NULL;
}
bool	AlgorithmBase::RemovePage(AlgorithmInPageRoot *pData)
{
	return PageDataPhase[GetLayersBase()->GetCurrentPhase()]->RemovePage(pData);
}
AlgorithmInPageRoot	*AlgorithmBase::SetPageData(int page,AlgorithmInPageRoot *pData)
{
	return PageDataPhase[GetLayersBase()->GetCurrentPhase()]->SetPageData(page,pData);
}

void	AlgorithmBase::Release(void)
{
	ReleaseData();
}

void	AlgorithmBase::InitialAfterParamLoaded(void)
{
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		PageDataPhase[i]->InitialAfterParamLoaded();
	}
}

bool	AlgorithmBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	AlgorithmBase::Save(QIODevice *f)
{
	if(SaveOnlyBase(f)==false){
		return false;
	}
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->Save(this,f)==false){
            return(false);
		}
	}
    return(true);
}
bool	AlgorithmBase::Load(QIODevice *f)
{
	if(LoadOnlyBase(f)==false){
		return false;
	}
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->Load(this,f)==false){
            return(false);
		}
	}

	Changed		=false;
	CalcDone	=false;
    return(true);
}

bool	AlgorithmBase::SaveHistgram(QIODevice *f)
{
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->SaveHistgram(this,f)==false){
            return(false);
		}
	}
    return(true);
}

bool	AlgorithmBase::LoadHistgram(QIODevice *f)
{
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]->LoadHistgram(this,f)==false){
            return(false);
		}
	}
    return(true);
}
AlgorithmLibrary	*AlgorithmBase::CreateLibrary(void)
{
	if(GetLibraryContainer()!=NULL){
		return GetLibraryContainer()->CreateNew();
	}
	return NULL;
}
QString		AlgorithmBase::GetLibComment(int LibID)
{
	LayersBase	*L=GetLayersBase();
	if(L!=NULL && L->GetDatabaseLoader()!=NULL){
		QString	s=L->GetDatabaseLoader()->G_GetLibraryComment(L->GetDatabase()
															,GetLibType()
															,LibID);
		return s;
	}
	return /**/"";
}

AlgorithmLibraryList	*AlgorithmBase::FindLibFromCache(int LibID)
{
	return CacheLib->SearchLibrary(GetLibType(), LibID);
}

void	AlgorithmBase::ClearManagedCacheLib(void)
{
	if(ManagedCacheLib!=NULL){
		ManagedCacheLib->RemoveAll();
	}
}
bool	AlgorithmBase::LoadManagedCacheLib(int LibID)
{
	if(ManagedCacheLib!=NULL && GetLibraryContainer()!=NULL){
		AlgorithmLibraryLevelContainer	*Lib=ManagedCacheLib->FindLib(GetLibraryContainer()->GetLibType(), LibID);
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(this);
			if(GetLibraryContainer()->GetLibrary(LibID,*Lib)==false){
				delete	Lib;
				return false;
			}
			AlgorithmLibraryStockerList	*p=new AlgorithmLibraryStockerList(Lib);
			ManagedCacheLib->AppendList(p);
		}
		else{
			if(GetLibraryContainer()->GetLibrary(LibID,*Lib)==false)
				return false;
		}
	}
	return true;
}

AlgorithmLibraryLevelContainer	*AlgorithmBase::ReloadManagedCacheLib(int LibID)
{
	if(ManagedCacheLib!=NULL && GetLibraryContainer()!=NULL){
		AlgorithmLibraryLevelContainer	*Lib=ManagedCacheLib->FindLib(GetLibraryContainer()->GetLibType(), LibID);
		if(Lib==NULL){
			Lib=new AlgorithmLibraryLevelContainer(this);
			if(GetLibraryContainer()->GetLibrary(LibID,*Lib)==false)
				return NULL;
			AlgorithmLibraryStockerList	*p=new AlgorithmLibraryStockerList(Lib);
			ManagedCacheLib->AppendList(p);
			return Lib;
		}
		else{
			if(GetLibraryContainer()->GetLibrary(LibID,*Lib)==true){
				return Lib;
			}
		}
	}
	return NULL;
}

bool	AlgorithmBase::LoadAllManagedCacheLib(void)
{
	if(ManagedCacheLib!=NULL){
		ManagedCacheLib->RemoveAll();
		AlgorithmLibraryListContainer	ALibList;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		Container->EnumLibrary(ALibList);
		for(AlgorithmLibraryList *a=ALibList.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryLevelContainer	*Lib=new AlgorithmLibraryLevelContainer(Container);
			if(GetLibraryContainer()->GetLibrary(a->GetLibID(),*Lib)==false){
				delete	Lib;
				return false;
			}
			AlgorithmLibraryStockerList	*p=new AlgorithmLibraryStockerList(Lib);
			ManagedCacheLib->AppendList(p);
		}
	}
	return true;
}

AlgorithmLibraryLevelContainer	*AlgorithmBase::FindLibFromManagedCacheLib(int LibID)
{
	for(AlgorithmLibraryStockerList *p=ManagedCacheLib->GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetLib().GetLibID()==LibID){
			return &p->GetLib();
		}
	}
	return NULL;
}
AlgorithmLibraryLevelContainer	*AlgorithmBase::FindOrLoadLibFromManagedCacheLib(int LibID)
{
	AlgorithmLibraryLevelContainer	*r=FindLibFromManagedCacheLib(LibID);
	if(r==NULL){
		return ReloadManagedCacheLib(LibID);
	}
	return r;
}

bool	AlgorithmBase::GetDLLName(QString &DLLRoot ,QString &DLLName) const
{
	if(LogicDLLPoint!=NULL){
		DLLRoot=LogicDLLPoint->GetDLLRoot();
		DLLName=LogicDLLPoint->GetDLLName();
		return true;
	}
	return false;
}

WORD	AlgorithmBase::GetDLLVersion(void)
{
	if(LogicDLLPoint!=NULL){
		return LogicDLLPoint->Ver;
	}
	return 0;
}


void	AlgorithmBase::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	AlgorithmBase::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	TransmitDirectly(packet);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph!=NULL){
			Ph->DeliverTransmitDirectly(packet);
		}
	}
}
bool	AlgorithmBase::SaveInPacket(QIODevice *f ,GUIDirectMessage *packet)
{
	QString	ClassName=typeid(packet).name();
	if(::Save(f,ClassName)==false)
		return false;
	return packet->Save(f);
}

QString				AlgorithmBase::LoadInPacket(QIODevice *f)
{
	//return packet->Load(f);
	QString	ClassName;
	if(::Load(f,ClassName)==false)
		return /**/"";
	return ClassName;
}


bool	AlgorithmBase::SaveOnlyBase(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,LogicDLLPoint->GetDLLRoot())==false){
		return false;
	}
	if(::Save(f,LogicDLLPoint->GetDLLName())==false){
		return false;
	}
	int32	iAllocatedPageNumb=0;
	if(::Save(f,iAllocatedPageNumb)==false){
		return(false);
	}
	if(::Save(f,LogicDLLPoint->Ver)==false){
		return false;
	}
	return true;
}
bool	AlgorithmBase::LoadOnlyBase(QIODevice *f,QString &ErrorMsg)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver<0 || Ver>2){
		return false;
	}
	QString	dllRoot,dllName;
	if(::Load(f,dllRoot)==false){
		return false;
	}
	if(::Load(f,dllName)==false){
		return false;
	}
	if(dllRoot!=LogicDLLPoint->GetDLLRoot() || dllName!=LogicDLLPoint->GetDLLName()){
		ErrorMsg=QString("Mismatch  ")+dllRoot+QString(":")+dllName;
		return false;
	}
	int32	iAllocatedPageNumb;
	if(::Load(f,iAllocatedPageNumb)==false){
		return(false);
	}
	if(Ver>=2){
		WORD	LVer;
		if(::Load(f,LVer)==false){
			return false;
		}
		LoadedVersion=LVer;
	}
	return true;
}
bool	AlgorithmBase::LoadOnlyBase(QIODevice *f)
{
	if(ModeLoadSaveInPlayer==true || (ModeLoadSaveInPlayer==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		QString	ErrorMsg;
		return LoadOnlyBase(f,ErrorMsg);
	}
	return true;
}
	
bool	AlgorithmBase::SaveOnlyThreshold(QIODevice *f)
{
	if(ModeLoadSaveInPlayer==true || (ModeLoadSaveInPlayer==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
			if(Ph!=NULL){
				if(Ph->SaveOnlyThreshold(f)==false){
					return false;
				}
			}
		}
	}
	return true;
}
bool	AlgorithmBase::LoadOnlyThreshold(QIODevice *f)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph!=NULL){
			if(Ph->LoadOnlyThreshold(f)==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmBase::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(int i=0;i<GetEffectivePageNumb();i++){
		if(GetPageData(i)!=NULL){
			GetPageData(i)->Draw(pnt, LayerList ,movx ,movy ,ZoomRate ,Attr);
		}
	}
}
void	AlgorithmBase::DrawMove(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	if((0<=localPage) && (localPage<GetEffectivePageNumb())){
		if(GetPageData(localPage)!=NULL){
			GetPageData(localPage)->DrawMove(dx,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
		}
	}
}


AlgorithmLibraryContainer	*AlgorithmBase::GetLibraryContainer(void)
{
	return LogicDLLPoint->LibContainer;
}
void	AlgorithmBase::MoveItemsToDispatcherForLoadingParts(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->MoveItemsToDispatcherForLoadingParts();
	}
}
void	AlgorithmBase::CopyItemsFormDispatcherForParts(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->CopyItemsFormDispatcherForParts();
	}
}
void	AlgorithmBase::RemoveItemFormDispatcher(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		Ph->RemoveItemFormDispatcher();
	}
}

ExeResult	AlgorithmBase::ExecuteInitialAfterEditPrev(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ClearManagedCacheLib();
	if(GetLibraryContainer()!=NULL){
		GetLibraryContainer()->EnumLibrary(GetLibType(),*CacheLib);
	}
	Res->Initial();
	Res->InitialInspection();
	//NGListForInspect.RemoveAll();

	IntList	LibIDList;
	for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
		if(PageDataPhase[i]!=NULL){
			PageDataPhase[i]->EnumLibID(LibIDList);
		}
	}
	for(IntClass *d=LibIDList.GetFirst();d!=NULL;d=d->GetNext()){
		int	LibID=d->GetValue();
		SetNGTypeList(LibID);
	}
	for(IntClass *d=LibIDList.GetFirst();d!=NULL;d=d->GetNext()){
		LoadManagedCacheLib(d->GetValue());
	}
	ExeResult	ret=Res->ExecuteInitialAfterEditPrev(ExeID ,this,EInfo);

	//NGListForInspect.SortInPriority();

	//CalcDone=true;
	return ret;
}

ExeResult	AlgorithmBase::ExecuteInitialAfterEdit	(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	//ClearManagedCacheLib();
	//if(GetLibraryContainer()!=NULL){
	//	GetLibraryContainer()->EnumLibrary(GetLibType(),*CacheLib);
	//}
	//Res->Initial();
	//Res->InitialInspection();
	//
	//IntList	LibIDList;
	//for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
	//	if(PageDataPhase[i]!=NULL){
	//		PageDataPhase[i]->EnumLibID(LibIDList);
	//	}
	//}
	//for(IntClass *d=LibIDList.GetFirst();d!=NULL;d=d->GetNext()){
	//	int	LibID=d->GetValue();
	//	SetNGTypeList(LibID);
	//}
	//for(IntClass *d=LibIDList.GetFirst();d!=NULL;d=d->GetNext()){
	//	LoadManagedCacheLib(d->GetValue());
	//}
	ExeResult	ret=Res->ExecuteInitialAfterEdit	(ExeID ,this,EInfo);

	//NGListForInspect.SortInPriority();

	//CalcDone=true;
	return ret;
}

ExeResult	AlgorithmBase::ExecuteInitialAfterEditPost(int ExeID 
													,ResultBaseForAlgorithmRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	ret=Res->ExecuteInitialAfterEditPost(ExeID ,this,EInfo);

	NGListForInspect.SortInPriority();

	CalcDone=true;
	return ret;
}

ExeResult	AlgorithmBase::ExecuteStartByInspection(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	Res->InitialInspection();
	return Res->ExecuteStartByInspection(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecuteCaptured		(int ExeID ,ResultBaseForAlgorithmRoot *Res,ListPhasePageLayerPack &CapturedList)
{
	return Res->ExecuteCaptured		(ExeID ,this,CapturedList);
}
ExeResult	AlgorithmBase::ExecutePreAlignment		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecutePreAlignment		(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecuteAlignment			(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecuteAlignment		(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecutePreProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecutePreProcessing	(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecuteProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecuteProcessing		(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecuteProcessingRevived	(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecuteProcessingRevived (ExeID ,this);
}
ExeResult	AlgorithmBase::ExecutePostProcessing	(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecutePostProcessing	(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecutePreScanning		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecutePreScanning		(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecuteScanning			(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecuteScanning			(ExeID ,this);
}
ExeResult	AlgorithmBase::ExecutePostScanning		(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	return Res->ExecutePostScanning		(ExeID ,this);
}

bool	AlgorithmBase::DrawResultBase(int32 ShowFixedPhase, ResultBaseForAlgorithmRoot *Res,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	if(ShowFixedPhase==-1){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			if(phase==GetLayersBase()->GetCurrentPhase()
			|| GetLayersBase()->GetPageDataPhase(phase)->GetFromSourcePhase()==GetLayersBase()->GetCurrentPhase()){
				if(Res!=NULL){
					ResultBasePhase	*R=Res->GetPageDataPhase(phase);
					PageDataPhase[phase]->DrawResultBase(R,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
				}
				else{
					PageDataPhase[phase]->DrawResultBase(NULL,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
				}
			}
		}
	}
	else{
		if(Res!=NULL){
			ResultBasePhase	*R=Res->GetPageDataPhase(ShowFixedPhase);
			PageDataPhase[ShowFixedPhase]->DrawResultBase(R,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
		}
		else{
			PageDataPhase[ShowFixedPhase]->DrawResultBase(NULL,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
		}
	}
	return true;
}
bool	AlgorithmBase::DrawResultItem(ResultBaseForAlgorithmRoot *Res,IntList &LayerList ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		if(phase==GetLayersBase()->GetCurrentPhase()
		|| GetLayersBase()->GetPageDataPhase(phase)->GetFromSourcePhase()==GetLayersBase()->GetCurrentPhase()){
			if(Res!=NULL){
				ResultBasePhase	*R=Res->GetPageDataPhase(phase);
				PageDataPhase[phase]->DrawResultItem(R,LayerList ,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
			else{
				PageDataPhase[phase]->DrawResultItem(NULL,LayerList ,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,OnlyNG);
			}
		}
	}
	return true;
}
void	AlgorithmBase::DrawMonoBitmap(BYTE **BmpPoint)
{
	for(int page=0;page<GetEffectivePageNumb();page++){
		if(GetPageData(page)!=NULL){
			GetPageData(page)->DrawMonoBitmap(BmpPoint);
		}
	}
}
void	AlgorithmBase::EnumLibID(IntList &LibIDList)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*PhOne=GetPageDataPhase(phase);
		PhOne->EnumLibID(LibIDList);
	}
}

void	AlgorithmBase::ChangeAlgorithmType(DWORD algorithmtype)
{
	LogicDLL	*L=GetLogicDLL();
	L->ChangeAlgorithmType(algorithmtype);
}

void	AlgorithmBase::MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmItemIndependentPack &Data)
{
	int	Phase=0;
	if(TargetPhase>=0){
		Phase=TargetPhase;
	}
	else{
		Phase=GetLayersBase()->GetCurrentPhase();
	}
	AlgorithmInPageInOnePhase	*PhOne=GetPageDataPhase(Phase);
	if(PhOne==NULL){
		return;
	}
	ResultBaseForAlgorithmRoot	*RBase=NULL;
	ResultInspection	*R=GetLayersBase()->GetCurrentResultForDraw();
	if(R!=NULL){
		RBase=R->GetResultBaseForAlgorithm(this);
	}
	if(RBase==NULL){
		ResultInspection	*Ri=GetLayersBase()->GetResultThread()->GetLatest();
		if(Ri!=NULL){
			RBase=Ri->GetResultBaseForAlgorithm(this);
		}
	}
	if(RBase!=NULL){
		AlgorithmInPageRoot	*P=PhOne->GetPageData(localPage);
		ResultInPageRoot	*ResPage=NULL;
		ResultBasePhase		*RPh=RBase->GetPageDataPhase(Phase);
		if(RPh!=NULL){
			ResPage=RPh->GetPageData(localPage);
		}

		if(P!=NULL && ResPage!=NULL && P->IsInclude(localX,localY)==true){
			P->MakeIndependentItems(SubResultMoving, ResPage,localX ,localY,Data);
		}
	}
}

void	AlgorithmBase::SetIndependentItemData(int32 Command
												,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
												,AlgorithmItemRoot *Data
												,IntList &EdittedMemberID
												,QByteArray &Something
												,QByteArray &AckData)
{
	int	Phase=0;
	if(TargetPhase>=0){
		Phase=TargetPhase;
	}
	else{
		Phase=GetLayersBase()->GetCurrentPhase();
	}
	AlgorithmInPageInOnePhase	*PhOne=GetPageDataPhase(Phase);
	if(PhOne==NULL){
		return;
	}

	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot	*P=PhOne->GetPageData(page);
		if(P!=NULL){
			P->SetIndependentItemData(Command,LocalPage,Layer,ItemID,Data,EdittedMemberID,Something,AckData);
		}
	}
}

bool	AlgorithmBase::GeneralDataRelease(int32 Command,void *data)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	*AlgorithmBase::GeneralDataCreate(int32 Command,void *reqData)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		void	*ret=Ph->GeneralDataCreate(Command,reqData);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}
bool	AlgorithmBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->GeneralDataLoad(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->GeneralDataSave(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmBase::GeneralDataReply(int32 Command,void *data)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ph=GetPageDataPhase(phase);
		if(Ph->GeneralDataReply(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmBase::ExecuteCopy(int localPage ,ClipboardAlgorithm &Pack,IntList &LayerList)
{
	AlgorithmInPageRoot	*P=GetPageData(localPage );
	if(P!=NULL){
		P->ExecuteCopy(Pack,LayerList);
	}
}

bool	AlgorithmBase::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste)
{
	FlexArea	area=item->Area;
	if(GetLayersBase()->GetPageData(item->Page)==NULL
	|| GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()==NULL){
		return true;
	}
	area.MoveToNoClip(GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->y);
	area.MoveToNoClip(globalDx,globalDy);
	/*
	for(int page=0;page<GetPageNumb();page++){
		if(GetLayersBase()->GetPageData(page)->IsOverlapped(area)==true){
			GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);
			AlgorithmInPageRoot	*Ap=GetPageData(page);
			if(Ap!=NULL)
				Ap->ExecutePaste(PastedLayer,item ,globalDx, globalDy,area);
		}
	}
	*/
	bool	Ret=true;
	if(GetLayersBase()->GetPageData(item->Page)->IsOverlapped(area)==true){
		GetLayersBase()->GetPageData(item->Page)->ClipMoveAreaFromGlobal(area);
		AlgorithmInPageRoot	*Ap=GetPageData(item->Page);
		if(Ap!=NULL){
			if(Ap->ExecutePaste(PastedLayer,item ,globalDx, globalDy,area,SelectModeAfterPaste)==false){
				Ret=false;
			}
		}
	}
	if(item->Vector!=NULL){
		int	id=item->Vector->GetID();
		VectorLineBase	*v=VectorLineBase::Create(id);
		*v=*item->Vector;
		v->MoveTo(GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->x
				, GetLayersBase()->GetPageData(item->Page)->GetOutlineOffset()->y);
		v->MoveTo(globalDx,globalDy);

		if(GetLayersBase()->GetPageData(item->Page)->IsOverlapped(v)==true){
			GetLayersBase()->GetPageData(item->Page)->ClipMoveVectorFromGlobal(v);
			AlgorithmInPageRoot	*Ap=GetPageData(item->Page);
			if(Ap!=NULL){
				if(Ap->ExecutePaste(PastedLayer,item ,globalDx, globalDy,v,SelectModeAfterPaste)==false){
					Ret=false;
				}
			}
		}
	}
	return Ret;
}


bool	AlgorithmBase::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy
													,const QString &OriginRoot ,const QString &OriginName
													,int ItemClass)
{
	FlexArea	area=item->Area;
	area.MoveToNoClip(globalDx,globalDy);
	int page=item->Page;
	//if(GetLayersBase()->GetPageData(page)->IsInclude(area)==true){
	//	GetLayersBase()->GetPageData(page)->ClipMoveAreaFromGlobal(area);
	area.ClipArea(0,0,GetLayersBase()->GetParamGlobal()->DotPerLine,GetLayersBase()->GetParamGlobal()->MaxLines);
	bool	Ret=true;
	if(area.GetPatternByte()>0){
		AlgorithmInPageRoot	*Ap=GetPageData(page);
		if(Ap!=NULL){
			AlgorithmBase	*OriginBase=GetLayersBase()->GetAlgorithmBase(OriginRoot ,OriginName);
			if(Ap->ExecutePasteCreateWithShape(PastedLayer,item ,Buff,globalDx, globalDy,area,OriginBase,ItemClass)==false){
				Ret=false;
			}
		}
	}
	return Ret;
}
void	AlgorithmBase::ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,bool AllItems)
{
	if((0<=localPage) && (localPage<GetEffectivePageNumb())){
		if(GetParamGlobal()->CommonOperationInAllPhases==false){
			AlgorithmInPageRoot	*Ap=GetPageData(localPage);
			if(Ap!=NULL){
				Ap->ExecuteMove(GlobalDx,GlobalDy,AllItems);
			}
		}
		else{
			for(int phase=0;phase<GetPhaseNumb();phase++){
				AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->ExecuteMove(GlobalDx,GlobalDy,AllItems);
				}
			}
		}
	}
}
void	AlgorithmBase::ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems)
{
	if((0<=localPage) && (localPage<GetEffectivePageNumb())){
		AlgorithmInPageRoot	*P=GetPageData(localPage);
		if(P!=NULL){
			P->ExecuteMove(GlobalDx,GlobalDy,Items,AllItems);
		}
	}
}
void	AlgorithmBase::GetPageListForExecuteMove(IntList &PageList ,int localPage ,int GlobalDx,int GlobalDy)
{
	if((0<=localPage) && (localPage<GetEffectivePageNumb())){
		AlgorithmInPageRoot	*P=GetPageData(localPage);
		if(P!=NULL){
			P->GetPageListForExecuteMove(PageList,GlobalDx,GlobalDy);
		}
	}
}

int		AlgorithmBase::GetSelectedItemCount(void)
{
	int	ret=0;
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL){
			ret+=P->GetSelectedItemCount();
		}
	}
	return ret;
}
void	AlgorithmBase::ReleaseAllSelectedItem(void)
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot	*P=GetPageData(page);
		if(P!=NULL){
			P->ReleaseAllSelectedItem();
		}
	}
}
int		AlgorithmBase::GetLibType(void)
{
	if(GetLibraryContainer()!=NULL){
		return GetLibraryContainer()->GetLibType();
	}
	return -1;
}

void	AlgorithmBase::CopyFrom(AlgorithmBase *src 
								,int OffsetX,int OffsetY
								,int PartsMaster ,int PartsID
								,bool ReferedThresholdMode)
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		AlgorithmInPageRoot		*s=src->GetPageData(page);
		if((d==NULL) || (s==NULL)){
			continue;
		}
		d->CopyFrom(this,s	,OffsetX,OffsetY
						,PartsMaster ,PartsID
						,ReferedThresholdMode);
	}
}

void	AlgorithmBase::InitializeFromParts(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->InitializeFromParts();
		}
	}
}

bool	AlgorithmBase::GetAlgorithmRootName(QString &DLLRoot ,QString &DLLName)
{
	LogicDLL	*L=GetLogicDLL();
	if(L==NULL){
		return false;
	}
	DLLRoot=L->GetDLLRoot();
	DLLName=L->GetDLLName();
	return true;
}
bool	AlgorithmBase::GetAlgorithmRootName(RootNameList &RetRootName)
{
	LogicDLL	*L=GetLogicDLL();
	if(L==NULL){
		return false;
	}
	RetRootName.DLLRoot=L->GetDLLRoot();
	RetRootName.DLLName=L->GetDLLName();
	return true;
}

bool	AlgorithmBase::IsEdited(void)
{
	if(Changed==true){
		return true;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL && Ah->IsEdited()==true){
			return true;
		}
	}
	return false;
}
bool	AlgorithmBase::IsCalcDone(void)
{
	if(CalcDone==false){
		return false;
	}
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmBase::SetEdited(bool edited)
{
	Changed=edited;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->SetEdited(edited);
		}
	}
}

void	AlgorithmBase::SetCalcDone(bool calcdone)
{
	CalcDone=calcdone;
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->SetCalcDone(calcdone);
		}
	}
}
void	AlgorithmBase::ExecuteTransformSelectedItems(TransformBase &M)
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPageRoot		*d=GetPageData(page);
		if(d!=NULL){
			d->ExecuteTransformSelectedItems(M);
		}
	}
}

bool	AlgorithmBase::SaveCSVMasterReport(QStringListListCSV &CSVData)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah->SaveCSVMasterReport(CSVData)==false){
			return false;
		}
	}
	return true;
}

bool	AlgorithmBase::GetNGTypeContainer(int LibID
										, LibNGTypeInAlgorithm &NGTypeContainer)
{
	return GetLibraryContainer()->GetNGTypeContainer(LibID , NGTypeContainer);
}

LibraryListWithNGType	*AlgorithmBase::GetNGTypeList(int libID)
{
	return NGListForInspect.GetNGTypeList(libID);
}

LibraryListWithNGType	*AlgorithmBase::SetNGTypeList(int libID)
{
	
	LibraryListWithNGType	*a=NGListForInspect.GetNGTypeList(libID);
	if(a==NULL){
		a=new LibraryListWithNGType(libID);
		a->NGList.RemoveAll();
		GetNGTypeContainer(libID ,a->NGList);
		NGListForInspect.AppendList(a);
	}
	else{
		a->NGList.RemoveAll();
		GetNGTypeContainer(libID ,a->NGList);
	}
	
	return a;
}

LibNGTypeItem	*AlgorithmBase::GetLibNGTypeItem(int TypeUniqueCode)
{
	for(LibraryListWithNGType *c=NGListForInspect.GetFirst();c!=NULL;c=c->GetNext()){
		for(LibNGTypeItem *item=c->NGList.GetFirst();item!=NULL;item=item->GetNext()){
			if(item->TypeUniqueCode==TypeUniqueCode){
				return item;
			}
		}
	}
	return NULL;
}

LibNGTypeItem	*AlgorithmBase::SearchNGCause(LibraryListWithNGType *L, AlgorithmItemRoot *aitem,ResultPosList *p)
{
	if(L!=NULL){
		for(LibNGTypeItem *item=L->NGList.GetFirst();item!=NULL;item=item->GetNext()){
			return item;
		}
	}
	return NULL;
}

AlgorithmInPageInOnePhase	*AlgorithmBase::GetPageDataPhase(int PhaseCode)	const
{
	if(0<=PhaseCode && PhaseCode<AllocatedPhaseNumb){
		return PageDataPhase[PhaseCode];
	}
	return NULL;
}

void	AlgorithmBase::ClearHistgram(void)
{
	MutexRegistHistgram.lockForWrite();
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->ClearHistgram();
		}
	}
	//RegisteredHistgramContainer.RemoveAll();
	MutexRegistHistgram.unlock();
}
void	AlgorithmBase::RegistHistgram(AlgorithmItemRoot *item ,const QString &_Name ,int id)
{
	MutexRegistHistgram.lockForRead();
	for(RegisteredHistgramList *a=RegisteredHistgramContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==id){
			MutexRegistHistgram.unlock();
			return;
		}
	}
	MutexRegistHistgram.unlock();

	RegisteredHistgramList	*a=new RegisteredHistgramList(_Name,id);
	
	MutexRegistHistgram.lockForWrite();
	RegisteredHistgramContainer.AppendList(a);
	MutexRegistHistgram.unlock();
}

void	AlgorithmBase::EnumHistgram(QStringList &HistNames)
{
	MutexRegistHistgram.lockForRead();
	for(RegisteredHistgramList *a=RegisteredHistgramContainer.GetFirst();a!=NULL;a=a->GetNext()){
		HistNames.append(a->GetName());
	}
	MutexRegistHistgram.unlock();
}

void	AlgorithmBase::EnumHistgram(AlgorithmBase::RegisteredHistgramListContainer &List)
{
	MutexRegistHistgram.lockForRead();
	List=RegisteredHistgramContainer;
	MutexRegistHistgram.unlock();
}

QString	AlgorithmBase::GetHistgramName(int HistID)
{
	MutexRegistHistgram.lockForRead();
	for(RegisteredHistgramList *a=RegisteredHistgramContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==HistID){
			QString	ret=a->GetName();
			MutexRegistHistgram.unlock();
			return ret;
		}
	}
	MutexRegistHistgram.unlock();
	return /**/"";
}

int		AlgorithmBase::GetHistgramID(int row)
{
	MutexRegistHistgram.lockForRead();
	RegisteredHistgramList *a=RegisteredHistgramContainer[row];
	if(a!=NULL){
		int	ID=a->GetID();
		MutexRegistHistgram.unlock();
		return ID;
	}
	MutexRegistHistgram.unlock();
	return -1;
}
bool	AlgorithmBase::ExecuteMacro(const QString &FuncName, QStringList &Args, bool &ExeReturn)
{
	if(LogicDLLPoint!=NULL){
		ExportFuncForMacro	*f=LogicDLLPoint->SearchMacroFunc(FuncName);
		if(f!=NULL){
			if(f->DLL_ExcuteMacroAlgo!=NULL){
				ExeReturn=f->DLL_ExcuteMacroAlgo(this,Args);
				return true;
			}
		}
	}
	return false;
}
bool	AlgorithmBase::ManualExecuteAll(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			if(Ah->ManualExecuteAll(ManualExecuterData)==false){
				return false;
			}
		}
	}
	return true;
}
AlgorithmItemRoot	*AlgorithmBase::SearchItemByName(const QString &ItemName ,int *Phase,int *Page ,int *Layer)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			AlgorithmItemRoot	*r=Ah->SearchItemByName(ItemName ,Page,Layer);
			if(r!=NULL){
				if(Phase!=NULL){
					*Phase=phase;
				}
				return r;
			}
		}
	}
	return NULL;
}
void	AlgorithmBase::ResetProcessDone(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->ResetProcessDone();
		}
	}
}

bool	AlgorithmBase::IsProcessDone(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			if(Ah->IsProcessDone()==false){
				return false;
			}
		}
	}
	return true;
}

void	AlgorithmBase::SetProcessDone(bool b)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->SetProcessDone(b);
		}
	}
}
	
bool	AlgorithmBase::GetDrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	if(LogicDLLPoint!=NULL){
		bool	Ret=LogicDLLPoint->DrawResultDetail(Item ,Pos ,RetList);
		RetList.Data.LibType=GetLibType();
		if(Item!=NULL){
			RetList.Data.Phase	=Item->GetPhaseCode();
			RetList.Data.Page	=Item->GetPage();
			RetList.Data.Layer	=Item->GetLayer();
			RetList.Data.ItemID	=Item->GetID();
			RetList.Data.LibID	=Item->GetLibID();
			Pos->GetPosInTarget(Item->GetCurrentResult(),RetList.Data.PosX,RetList.Data.PosY);
		}
	}
	return false;
}

void	AlgorithmBase::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->SwitchThresholdLevel(OldLevel ,NewLevel);
		}
	}
	if(ManagedCacheLib!=NULL){
		ManagedCacheLib->SwitchThresholdLevel(OldLevel ,NewLevel);
	}
}
void	AlgorithmBase::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->CopyThresholdLevel(SourceLevelID ,DestLevelID);
		}
	}
	if(ManagedCacheLib!=NULL){
		ManagedCacheLib->CopyThresholdLevel(SourceLevelID ,DestLevelID);
	}
}

static	void FuncSetCurrentIntoThresholdLevel(void *caller,AlgorithmItemRoot *item)
{
	AlgorithmItemPointerListContainerByLibContainer *Items=(AlgorithmItemPointerListContainerByLibContainer *)caller;
	for(AlgorithmItemPointerListContainerByLib *a=Items->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==item->GetLibID()){
			a->Container.Add(item);
		}
	}
}

bool	AlgorithmBase::SetCurrentIntoThresholdLevel(int LevelID)
{
	bool	Ret=true;
	AlgorithmLibraryContainer	*LibContainer=GetLibraryContainer();
	if(LibContainer==NULL){
		return false;
	}
	LayersBase	*Base=GetLayersBase();
	if(Base->GetDatabaseLoader()){
		AlgorithmItemPointerListContainerByLibContainer Items;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
			if(Ah!=NULL){
				Ah->ScanItems(&Items,FuncSetCurrentIntoThresholdLevel);
			}
		}
		for(AlgorithmItemPointerListContainerByLib *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmItemRoot	*Item=a->Container[a->Container.GetCount()/2]->GetItem();
			if(Item==NULL){
				Item=a->Container.GetFirst()->GetItem();
			}
			AlgorithmLibraryLevelContainer LibDest(this);
			if(LibContainer->GetLibrary(a->LibID ,LibDest)==true){
				AlgorithmLibrary	*ALib=LibDest.GetLibrary(LevelID);
				if(ALib!=NULL && Item!=NULL){
					const AlgorithmThreshold	*SrcThr=Item->GetThresholdBaseReadable();
					((AlgorithmThreshold	*)SrcThr)->ToLibrary(ALib);
					if(Base->GetDatabaseLoader()->G_Update(Base->GetDatabase(),LibContainer ,LibDest)==false){
						Ret=false;
					}
				}
				else{
					Ret=false;
				}
			}
			else{
				Ret=false;
			}
		}
	}
	return Ret;
}
void	AlgorithmBase::MoveForAlignment(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		if(Ah!=NULL){
			Ah->MoveForAlignment();
		}
	}
}

void	AlgorithmBase::EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		Ah->EnumItems(caller,Items , func);
	}
}

void	AlgorithmBase::ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		Ah->ScanItems(caller,func);
	}
}
void	AlgorithmBase::EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
		Ah->EnumItems(ItemIDList);
	}
}
bool	AlgorithmBase::ReqConfirmItemList(int page,ConfirmItemListContainer	&RetItemList)
{
	GUICmdReqConfirmItemList	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",page);
	GUICmdAckConfirmItemList	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",page);
	GetAlgorithmRootName(RCmd.AlgorithmRoot,RCmd.AlgorithmName);
	if(RCmd.Send(page,0,ACmd)==true){
		RetItemList.AddMove(ACmd.ItemList);
		return true;
	}
	return false;
}

AlgorithmItemRoot	*AlgorithmBase::FindItem(const AlgorithmItemIndex &Index) const
{
	AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(Index.GetPhase());
	if(Ah!=NULL){
		return Ah->FindItem(Index);
	}
	return NULL;
}

void	AlgorithmBase::ChildCopyShadowTreeParamLogicDLL(AlgorithmBase *Parent)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Parent->SaveParam(&Buff);
	Buff.seek(0);
	LoadParam(&Buff);
}

bool	AlgorithmBase::AvailableAlgorithmComponentWindow(void)	const
{
	LogicDLL	*L=GetLogicDLL();
	if(L!=NULL){
		return L->IsAvailableGetShowAndSetItemsForm();
	}
	return false;
}

//============================================================================================
AlgorithmItemIndependent::AlgorithmItemIndependent(LayersBase *base)
{	
	GlobalPage	=-1;
	Layer		=-1;
	ItemID		=-1;
	LibID		=-1;
	ItemClassType=-1;
	Data		=NULL;

	Base=base;
	PhaseCode=-1;	
	Result		=-1;
}

AlgorithmItemIndependent::AlgorithmItemIndependent(LayersBase *base,const QString &algorithmRoot ,const QString &algorithmName)
{
	GlobalPage	=-1;
	Layer		=-1;
	ItemID		=-1;
	LibID		=-1;
	ItemClassType=-1;
	Data		=NULL;

	Base=base;
	AlgorithmRoot=algorithmRoot; 
	AlgorithmName=algorithmName;
	PhaseCode=-1;
	Result		=-1;
}
AlgorithmItemIndependent::AlgorithmItemIndependent(const AlgorithmItemIndependent &src)
{
	PhaseCode		=src.PhaseCode		;
	GlobalPage		=src.GlobalPage		;
	Layer			=src.Layer			;
	ItemID			=src.ItemID			;
	LibID			=src.LibID			;
	ItemClassType	=src.ItemClassType	;
	Data			=src.Data			;
	AlgorithmRoot	=src.AlgorithmRoot	;
	AlgorithmName	=src.AlgorithmName	;
	Base			=src.Base			;
	Something		=src.Something		;
	Result			=src.Result			;
	TypeInNoLib		=src.TypeInNoLib	;
}

AlgorithmItemIndependent	&AlgorithmItemIndependent::operator=(const AlgorithmItemIndependent &src)
{
	PhaseCode		=src.PhaseCode		;
	GlobalPage		=src.GlobalPage		;
	Layer			=src.Layer			;
	ItemID			=src.ItemID			;
	LibID			=src.LibID			;
	ItemClassType	=src.ItemClassType	;
	Data			=src.Data			;
	AlgorithmRoot	=src.AlgorithmRoot	;
	AlgorithmName	=src.AlgorithmName	;
	Base			=src.Base			;
	Something		=src.Something		;
	Result			=src.Result			;
	TypeInNoLib		=src.TypeInNoLib	;
	return *this;
}

bool	AlgorithmItemIndependent::Save(QIODevice *f)
{
	if(::Save(f,PhaseCode)==false){
		return false;
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,ItemClassType)==false){
		return false;
	}
	if(::Save(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Save(f,AlgorithmName)==false){
		return false;
	}
	LogicDLL	*L=Base->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	if(L->SaveItem(f,Data)==false){
		return false;
	}
	if(::Save(f,Something)==false){
		return false;
	}
	if(::Save(f,Result)==false){
		return false;
	}
	if(::Save(f,TypeInNoLib)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemIndependent::Load(QIODevice *f)
{
	if(::Load(f,PhaseCode)==false){
		return false;
	}
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,ItemClassType)==false){
		return false;
	}
	if(::Load(f,AlgorithmRoot)==false){
		return false;
	}
	if(::Load(f,AlgorithmName)==false){
		return false;
	}
	AlgorithmBase	*A=Base->GetAlgorithmBase(AlgorithmRoot,AlgorithmName);
	if(A==NULL){
		return false;
	}
	LogicDLL		*L=Base->GetAlgorithmDLL(AlgorithmRoot,AlgorithmName);
	if(L==NULL){
		return false;
	}
	Data=L->CreateItem(A,ItemClassType);
	if(Data==NULL){
		return false;
	}
	if(L->LoadItem(f,Data)==false){
		return false;
	}
	if(::Load(f,Something)==false){
		return false;
	}
	if(::Load(f,Result)==false){
		return false;
	}
	if(::Load(f,TypeInNoLib)==false){
		return false;
	}
	return true;
}

AlgorithmItemIndependentPack::AlgorithmItemIndependentPack(const AlgorithmItemIndependentPack &src)
{
	Base=src.Base;
	EdittedMemberID=src.EdittedMemberID;
	for(AlgorithmItemIndependent *s=src.Items.GetFirst();s!=NULL;s=s->GetNext()){
		AlgorithmItemIndependent *d=new AlgorithmItemIndependent(*s);
		Items.AppendList(d);
	}
	LocalX	=src.LocalX;
	LocalY	=src.LocalY;
}

bool	AlgorithmItemIndependentPack::Save(QIODevice *f)
{
	if(EdittedMemberID.Save(f)==false){
		return false;
	}
	int32	N=Items.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(AlgorithmItemIndependent *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	return true;
}
bool	AlgorithmItemIndependentPack::Load(QIODevice *f)
{
	if(EdittedMemberID.Load(f)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Items.RemoveAll();
	for(int i=0;i<N;i++){
		AlgorithmItemIndependent *a=new AlgorithmItemIndependent(Base);
		if(a->Load(f)==false){
			return false;
		}
		Items.AppendList(a);
	}
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	return true;
}

AlgorithmItemIndependentPack	&AlgorithmItemIndependentPack::operator=(const AlgorithmItemIndependentPack &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AlgorithmItemIndependentPack *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	AlgorithmItemIndependent *d=Items.GetFirst();
	for(AlgorithmItemIndependent *s=src.Items.GetFirst();(s!=NULL) && (d!=NULL);s=s->GetNext() ,d=d->GetNext()){
		AlgorithmBase	*A=Base->GetAlgorithmBase(s->AlgorithmRoot,s->AlgorithmName);
		int	LocalPage=Base->GetLocalPageFromGlobal(s->GlobalPage);
		d->Data->CopyParentFrom(s->Data,A->GetPageData(LocalPage),s->Layer);
	}

	return *this;
}

//===============================================================================================================
bool	ItemPointerListInPage::Save(QIODevice *f)
{
	if(::Save(f,Page)==false){
		return false;
	}
	int32	N=LayerList.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemPointerListInLayer *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ItemPointerListInPage::Load(QIODevice *f ,AlgorithmInPageRoot *Pg,LayersBase *LBase)
{
	if(::Load(f,Page)==false){
		return false;
	}
	int32	N;
	LayerList.RemoveAll();
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		ItemPointerListInLayer	*L=new ItemPointerListInLayer();
		L->Load(f,Pg,LBase);
		LayerList.AppendList(L);
	}
	return true;
}
int	ItemPointerListInPage::GetItemsCount(void)
{
	int	Ret=0;
	for(ItemPointerListInLayer *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		Ret+=L->GetItemsCount();
	}
	return Ret;
}


bool	ItemPointerListInLayer::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	int32 N=ItemList.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemPointerList *L=ItemList.GetFirst();L!=NULL;L=L->GetNext()){
		int32	ItemClassType=L->ItemPointer->GetItemClassType();
		if(::Save(f,ItemClassType)==false){
			return false;
		}
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ItemPointerListInLayer::Load(QIODevice *f,AlgorithmInPageRoot *Pg,LayersBase *LBase)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	int32	N;
	ItemList.RemoveAll();
	if(::Load(f,N)==false){
		return false;
	}
	AlgorithmInLayerRoot	*Ly=Pg->GetLayerData(Layer);
	if(Ly!=NULL){
		for(int i=0;i<N;i++){
			ItemPointerList	*L=new ItemPointerList();
			int32 ItemClassType;
			if(::Load(f,ItemClassType)==false){
				return false;
			}
			AlgorithmItemRoot	*item=Ly->CreateItem(ItemClassType);
			L->Load(f,item,LBase);
			ItemList.AppendList(L);
		}
	}
	else{
		for(int i=0;i<N;i++){
			ItemPointerList	*L=new ItemPointerList();
			int32 ItemClassType;
			if(::Load(f,ItemClassType)==false){
				return false;
			}
			AlgorithmItemRoot	*item=Pg->CreateItem(ItemClassType);
			if(item!=NULL){
				L->Load(f,item,LBase);
				ItemList.AppendList(L);
			}
		}
	}
	return true;
}
int	ItemPointerListInLayer::GetItemsCount(void)
{
	int	Ret=ItemList.GetNumber();
	return Ret;
}

ItemPointerList::~ItemPointerList(void)
{
	if((Created==true) && (ItemPointer!=NULL)){
		delete	ItemPointer;
	}
	ItemPointer=NULL;
}

bool	ItemPointerList::Save(QIODevice *f)
{
	if(::Save(f,Dx)==false){
		return false;
	}
	if(::Save(f,Dy)==false){
		return false;
	}
	return ItemPointer->Save(f);
}
bool	ItemPointerList::Load(QIODevice *f,AlgorithmItemRoot *CreatedItem,LayersBase *LBase)
{
	if(::Load(f,Dx)==false){
		return false;
	}
	if(::Load(f,Dy)==false){
		return false;
	}
	if(CreatedItem->Load(f,LBase)==false){
		return false;
	}
	ItemPointer=CreatedItem;
	Created=true;
	return true;
}

