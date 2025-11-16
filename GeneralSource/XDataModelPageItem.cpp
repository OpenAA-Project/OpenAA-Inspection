/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataModelPageItem.cpp
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
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#include "XBsearch.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XDataModelPageItem.h"
#include "XCriticalFunc.h"
#include "XCrossObj.h"
#include "XErrorMessage.h"
#include "XResultAnalizer.h"
#include "XDisplayImagePacket.h"
#include "XFileThread.h"
#include "XDataAlgorithmList.h"
#include "XDataAlgorithmConfirm.h"

//===========================================================================================================
AlgorithmInPageRoot		*ResultInPagePI::GetAlgorithmInPage(void)	const
{	
	if(Parent==NULL){
		return NULL;
	}
	if(Parent->GetLogicDLL()==NULL){
		return NULL;
	}
	if(Parent->GetLogicDLL()->GetInstance()==NULL){
		return NULL;
	}
	int	phase=GetPhaseParent()->GetPhaseCode();
	return Parent->GetLogicDLL()->GetInstance()->GetPageDataPhase(phase)->GetPageData(GetPage());
}

void	AlgorithmItemPI::SetItemID(void)
{	
	if(Parent!=NULL){
		ItemID=Parent->GetIncStartItemID();	
	}
}
XYData	AlgorithmItemPI::GetOutlineOffset(void)	
{	
	if (GetDataInLayer() != NULL) {
		return *GetDataInLayer()->GetOutlineOffset();
	}
	XYData	d;
	return d;
}
AlgorithmBase			*AlgorithmItemPI::GetParentBase(void)	const
{	
	if(Parent==NULL){
		return NULL;
	}
	return Parent->GetParentBase();
}
AlgorithmInPageRoot		*AlgorithmItemPI::GetParentInPage(void)	const
{	
	return Parent;
}
AlgorithmInLayerRoot	*AlgorithmItemPI::GetParentInLayer(void)	const
{	
	return NULL;
}
ImageBuffer				**AlgorithmItemPI::GetMasterBuff(void)	
{	
	return(Parent->MasterBuffDim[0]);
}
ImageBuffer				**AlgorithmItemPI::GetMasterBuff(int n)	
{	
	if(n<0){
		n=0;
	}
	return(Parent->MasterBuffDim[n]);
}
ImageBuffer				**AlgorithmItemPI::GetTargetBuff(void)
{	
	return(Parent->TargetBuffDim);
}
ImageBuffer				**AlgorithmItemPI::GetTargetTRBuff(void)
{	
	return(Parent->TargetTRBuffDim);
}
ImageBuffer				**AlgorithmItemPI::GetBitBuff(void)
{	
	return(Parent->BitBuffDim);
}

AlgorithmInPageRoot	*AlgorithmInPagePI::GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	const
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(_DLLRoot ,_DLLName);
	if(Ab==NULL){
		return NULL;
	}
	AlgorithmInPageRoot	*p=dynamic_cast<AlgorithmInPageRoot *>(Ab->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage()));
	return p;
}
AlgorithmItemRoot	*ResultInItemPI::GetAlgorithmItemRoot(void)	const
{
	if(GetAlgorithmItem()!=NULL)
		return GetAlgorithmItem();
	AlgorithmInPagePI *cParent=(AlgorithmInPagePI *)Parent->GetAlgorithmInPage();
	return cParent->SearchIDItem(GetItemID());
}

//===========================================================================================================

ResultInItemRoot	*ResultInItemPI::Clone(void)
{
	ResultInItemPI	*r=new ResultInItemPI();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Save(&Buff);
	Buff.seek(0);
	r->Load(&Buff);
	return r;
}
LogicDLL		*ResultInItemPI::GetLogicDLL(void)	const
{
	if(Parent==NULL){
		return NULL;
	}
	if(Parent->Parent==NULL){
		return NULL;
	}
	return Parent->Parent->GetLogicDLL();
}

int		ResultInItemPI::GetDotPerLine(void)	const
{
	if(Parent==NULL)
		return 0;
	if(Parent->GetAlgorithmInPage()==NULL)
		return 0;
	return Parent->GetAlgorithmInPage()->GetDotPerLine();
}
int		ResultInItemPI::GetMaxLines(void)	const
{
	if(Parent==NULL)
		return 0;
	if(Parent->GetAlgorithmInPage()==NULL)
		return 0;
	return Parent->GetAlgorithmInPage()->GetMaxLines();
}

AlgorithmBase		*ResultInItemPI::GetAlgorithmBase(void)	const
{
	if(Parent!=NULL){
		return Parent->GetAlgorithmBase();
	}
	return NULL;
}

ResultInPagePI::ResultInPagePI(ResultBasePhase *pPhaseParent,DataInPage *pPage)
:ResultInPageRoot(pPhaseParent,pPage)
{
	Parent			=NULL;
	AllocatedResultCount=0;
	Result.RemoveAll();
	Release();
}
ResultInPagePI::~ResultInPagePI(void)
{
	Result.RemoveAll();
	Release();
	AllocatedResultCount=0;
}

bool	ResultInPagePI::Initial(ResultBaseForAlgorithmRoot *parent)
{
	Release();
	Parent=parent;
	Result.RemoveAll();
	AllocatedResultCount=0;
	AllocateForFastSearch(0);

	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);
	AlgorithmInPagePI *Pg=(AlgorithmInPagePI *)GetAlgorithmInPage();
	if(Pg!=NULL){
		Alloc(Pg);
		SetDataInPage(parent->GetLayersBase()->GetPageData(GetPage()));
	}
	return true;
}
void	ResultInPagePI::Alloc(AlgorithmInPagePI *algopage)
{
	if(algopage!=NULL
	&& algopage->GetParentBase()->GetLogicDLL()!=NULL 
	&& algopage->GetParentBase()->GetLogicDLL()->CheckAlgorithmType(AlgorithmBit_TypePreAlignment
																	| AlgorithmBit_TypePreAlignment
																	| AlgorithmBit_TypeAlignment	
																	| AlgorithmBit_TypePreProcessing
																	| AlgorithmBit_TypeProcessing		
																	| AlgorithmBit_TypeProcessingRevived
																	| AlgorithmBit_TypePostProcessing
																	| AlgorithmBit_TypePieceProcessing)==true){
		int	N=algopage->GetItemCount();
		AllocatedResultCount=Result.GetCount();
		if(N>AllocatedResultCount){
			for(int i=AllocatedResultCount;i<N;i++){
				ResultInItemPI	*r=(ResultInItemPI *)CreateItem();
				r->SetParent(this);
				Result.AppendList(r);
				AllocatedResultCount++;
			}
		}
		else if(N<AllocatedResultCount){
			while(N<AllocatedResultCount){
				ResultInItemPI	*r=Result.GetLast();
				if(r==NULL){
					break;
				}
				Result.RemoveList(r);
				delete	r;
				AllocatedResultCount--;
				if(N==AllocatedResultCount){
					break;
				}
			}
		}
		ResultInItemPI	*r=Result.GetFirst();
		for(AlgorithmItemPI *a=algopage->GetFirstData();a!=NULL && r!=NULL;a=a->GetNext(),r=r->GetNext()){
			r->SetItemID(a->GetID());
		}
	}
}

void	ResultInPagePI::Release(void)
{
}
bool    ResultInPagePI::Save(QIODevice *f)
{
	if(ResultInPageRoot::Save(f)==false){
		return false;
	}
	AllocatedResultCount=(int32)Result.GetNumber();
	if(::Save(f,AllocatedResultCount)==false){
		return(false);
	}
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Save(f)==false){
			return(false);
		}
	}
	return(true);
}
bool    ResultInPagePI::Load(QIODevice *f)
{
	if(ResultInPageRoot::Load(f)==false){
		return false;
	}
	if(f->read((char *)&AllocatedResultCount,sizeof(AllocatedResultCount))!=sizeof(AllocatedResultCount)){
		return(false);
	}
	Result.RemoveAll();
	for(int i=0;i<AllocatedResultCount;i++){
		ResultInItemPI	*r=(ResultInItemPI *)CreateItem();
		r->SetParent(this);
		if(r->Load(f)==false){
			return(false);
		}
		Result.AppendList(r);
	}
	return(true);
}

void	ResultInPagePI::InitialInspection(void)
{
	AllocatedResultCount=0;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		r->InitialInspection();
		AllocatedResultCount++;
	}
	CalcDone		=false;
	DoneBindImage	=false;
}

void	ResultInPagePI::MoveMerge(ResultInPageRoot &Dst)
{
	ResultInPagePI	*D= (ResultInPagePI	*)&Dst;
	Result.RemoveAll();
	for(ResultInItemPI *b=D->Result.GetFirst();b!=NULL;b=D->Result.GetFirst()){
		D->Result.RemoveList(b);
		Result.AppendList(b);
	}
	AllocatedResultCount=D->AllocatedResultCount;
	D->Initial(D->Parent);
}
ResultInItemPI		*ResultInPagePI::GetItem(int number)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetItemID()==number){
			return r;
		}
	}
	return NULL;
}

bool	ResultInPagePI::GatherResult(bool3 &OK)	const
{
	if(CalcDone==false){
		OK=none3;
		return true;
	}
	OK=true3;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		//if(AlgoPointer->IsCalcDone()==false && r->IsDone()==false){
		if(r->IsOk()==false){
			OK=false3;
			return true;
		}
	}
	return true;
}
bool	ResultInPagePI::GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const
{
	if(CalcDone==false){
		OK=none3;
		return true;
	}
	OK=true3;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		//if(AlgoPointer->IsCalcDone()==false && r->IsDone()==false){
		if(r->IsOk()==false){
			for(ResultPosList *a=r->GetPosList().GetFirst();a!=NULL;a=a->GetNext()){
				ResultPosInfo	*E=new ResultPosInfo();
				E->AItem=r->GetAlgorithmItem();
				E->RItem=r;
				E->RPos	=a;
				RContainer.AppendList(E);
			}
			OK=false3;
		}
	}
	return true;
}

void	ResultInPagePI::SetCurentCalcDone(bool b)
{
	CalcDone=b;
	if(b==false){
		DoneBindImage=false;
	}
}

ResultInItemRoot	*ResultInPagePI::FindResultInItem(int layer ,int ItemID)	const
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetItemID()==ItemID){
			return r;
		}
	}
	return NULL;
}
ResultInItemRoot	*ResultInPagePI::FastSearchIDItem(int layer ,int ItemID)	const
{
	if(ItemDimPointer==NULL){
		ResultInItemRoot	*r=FindResultInItem(layer ,ItemID);
		return r;
	}
	ResultInItemRoot	*r=FastSearchIDItemInside(ItemID);
	return r;
}

void	ResultInPagePI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		ErrorGroupPack EGroup;
		r->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect ,EGroup);
		SpecializedGroup+=EGroup;
	}
}

void	ResultInPagePI::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		ErrorGroupPack EGroup;
		r->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim ,EGroup);
		SpecializedGroup+=EGroup;
	}
}


ResultDLLBaseRoot	*ResultInPagePI::GetResultDLLBase(void)	const
{
	return Parent->GetResultDLLBase();
}

int		ResultInPagePI::GetNGCount(void)	const
{
	int	NGCount=0;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsOk()==false){
			NGCount++;
		}
	}
	return NGCount;
}
int		ResultInPagePI::GetNGPointCount(void)	const
{
	int	NGCount=0;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		NGCount+=r->GetNGPointCount();
	}
	return NGCount;
}
void	ResultInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)
{
	LayersBase	*LBase=GetLayersBase();
	bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;
	LogicDLLBaseClass	*LC=LBase->GetLogicDLLBase();

	for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOk()==false){
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				QStringList	AreaNames;
				if(p->AreaNames.count()==0){
					QString	AreaName;
					if(LC->LocalPos2Name(GetPage()  ,p->Px	//+a->GetAlignedX()+p->Rx
													,p->Py	//+a->GetAlignedY()+p->Ry 
													,AreaName)==true){
						AreaNames.append(AreaName);
					}
				}
				else{
					AreaNames=p->AreaNames;
				}
				int32	cPx=p->Px+a->GetAlignedX()+p->Rx;
				int32	cPy=p->Py+a->GetAlignedY()+p->Ry;
				LBase->ConvertToTop(cPx,cPy);
				int32	aPx=a->GetAlignedX();
				int32	aPy=a->GetAlignedY();
				LBase->ConvertToTop(aPx,aPy);
				int32	rPx=p->Rx;
				int32	rPy=p->Ry;
				LBase->ConvertToTop(rPx,rPy);

				QString	Msg
						=QString(/**/"<NGP X=\"")
						+QString::number(cPx)
						+QString(/**/"\" Y=\"")
						+QString::number(cPy)
						+QString(/**/"\" MX=\"")
						+QString::number(aPx)
						+QString(/**/"\" MY=\"")
						+QString::number(aPy)
						+QString(/**/"\" HX=\"")
						+QString::number(rPx)
						+QString(/**/"\" HY=\"")
						+QString::number(rPy);

				if(AreaNames.count()!=0){
					int	AreaNameCount=0;
					for(int k=0;k<AreaNames.count();k++){
						if(AreaNames[k].length()!=0){
							AreaNameCount++;
						}
					}
					if(AreaNameCount!=0){
						Msg=Msg+QString(/**/"\" ARA=\"#");
						for(int k=0;k<AreaNames.count();k++){
							Msg=Msg+AreaNames[k];
							if(k<AreaNames.count()-1){
								Msg=Msg+QString(",");
							}
						}
					}
				}
				if(OutputNGCause==true){
					if(a->GetAlgorithmItem()!=NULL){
						Msg=Msg	+QString(/**/"\" LC=\"")
							+QString::number(a->GetAlgorithmItem()->GetLibID());
					}
					if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
						LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
						if(t!=NULL){
							Msg=Msg	+QString(/**/"\" TC=\"")
									+QString::number(t->TypeCode);
						}
					}
				}
				
				AlgorithmItemRoot	*aitem=a->GetAlgorithmItem();
				QString	m;
				if(aitem!=NULL)
					m=aitem->OutputResult(p);
				if(m.isEmpty()==false){
					Msg =Msg+QString(" ")+m;
				}
				if(p->ResultType==ResultPosList::_ResultDWORD){
					Msg=Msg	+QString(/**/"\" RS1=\"")
							+QString::number(p->GetResult1())
							+QString(/**/"\" RS2=\"")
							+QString::number(p->GetResult2())
							+QString(/**/"\" RAL=\"")
							+LogicDLLPoint->GetDLLRoot()
							+QString(/**/":")
							+LogicDLLPoint->GetDLLName()
							+QString(/**/"\" LY=\"")
							+QString::number(0)
							+QString(/**/"\"/>");
				}
				else if(p->ResultType==ResultPosList::_ResultDouble){
					Msg=Msg	+QString(/**/"\" RS1=\"")
							+QString::number(p->GetResultDouble())
							+QString(/**/"\" RAL=\"")
							+LogicDLLPoint->GetDLLRoot()
							+QString(/**/":")
							+LogicDLLPoint->GetDLLName()
							+QString(/**/"\" LY=\"")
							+QString::number(0)
							+QString(/**/"\"/>");
				}

				ResList<<Msg;
			}
		}
	}
}

bool	ResultInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)
{
	//bool	OutputNGCause=GetLayersBase()->GetParamGlobal()->OutputNGCause;
	WrittenNGCount=0;
	int32	N=0;
	for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOk()==false){
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				N++;
			}
		}
	}
	if(N==0){
		for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsOk()==false){
				N++;
			}
		}
	}
	if(::Save(f,N)==false){
		return false;
	}
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsOk()==false){
				int	UniqueID2=0;
				for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext(),UniqueID2++){
					QByteArray	EData;
					QStringList	AreaNames;
					if(p->AreaNames.count()==0){
						QString	AreaName;
						if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
							AreaName=/**/"";
							AreaNames.append(AreaName);
						}
						else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																							,p->Py	//+a->GetAlignedY()+p->Ry 
																							,AreaName)==true){
							AreaNames.append(AreaName);
						}
					}
					else{
						AreaNames=p->AreaNames;
					}
					ResultPositionInfomation	RData;
					RData.Error=a->GetError();
					RData.PosResult	=p->result;
					RData.X			=p->Px+a->GetAlignedX()+p->Rx;
					RData.Y			=p->Py+a->GetAlignedY()+p->Ry;
					RData.MX		=a->GetAlignedX();
					RData.MY		=a->GetAlignedY();
					RData.HX		=p->Rx;
					RData.HY		=p->Ry;
					RData.UniqueID2	=UniqueID2;

					LBase->ConvertToTop(RData.X,RData.Y);
					LBase->ConvertToTop(RData.MX,RData.MY);
					LBase->ConvertToTop(RData.HX,RData.HY);

					p->GetExtraData(EData);
					RData.ExtraDataByte	=EData.size();

					if(AreaNames.count()!=0){
						QString	AName;
						int	AreaNameCount=0;
						for(int k=0;k<AreaNames.count();k++){
							if(AreaNames[k].length()!=0){
								AreaNameCount++;
							}
						}
						if(AreaNameCount!=0){
							for(int k=0;k<AreaNames.count();k++){
								AName=AName+AreaNames[k];
								if(k<AreaNames.count()-1){
									AName=AName+QString(",");
								}
							}
						}					
						::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
					}
					else{
						memset(&RData.AreaName,0,sizeof(RData.AreaName));
					}
					AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
					if(AItem==NULL){
						AlgorithmInPageRoot		*APage=a->GetParent()->GetAlgorithmInPage();
						if(APage!=NULL){
							AItem=APage->FastSearchIDItem(a->GetItemID());
						}
					}
					if(AItem!=NULL){
						RData.LibID		=AItem->GetLibID();
						RData.UniqueID1	=AItem->GetID();
					}
					else{
						RData.LibID	=-1;
					}

					RData.NGTypeUniqueCode	=-1;	
					if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
						LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
						if(t!=NULL){
							RData.NGTypeUniqueCode	=t->TypeCode;
						}
					}
					if(p->ResultType==ResultPosList::_ResultDWORD){
						RData.ResultType	=_ResultDWORD;
						RData.result1	=p->GetResult1();
						RData.result2	=p->GetResult2();
					}
					else if(p->ResultType==ResultPosList::_ResultDouble){
						RData.ResultType	=_ResultDouble;
						RData.ResultValue.ResultDouble=p->GetResultDouble();
					}
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					else{
						if(p->Message.isEmpty()==false){
							QByteArray	B=p->Message.toLocal8Bit();
							strncpy((char *)RData.Something,B.data(),min((int)B.length(),(int)sizeof(RData.Something)));
						}
						RData.LibType=0;
					}
					RData.Layer		=0;

					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					if(RData.ExtraDataByte>0){
						if(f->write(EData)!=RData.ExtraDataByte){
							return false;
						}
					}
					WrittenNGCount++;
				}
			}
		}
		if(WrittenNGCount==0){
			for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->IsOk()==false){
					int	UniqueID2=0;
					QByteArray	EData;
					ResultPositionInfomation	RData;
					RData.Error=a->GetError();
					RData.PosResult	=0x10000+1;
					int	cx,cy;
					a->GetCenter(cx, cy);
					RData.X			=cx+a->GetAlignedX();
					RData.Y			=cy+a->GetAlignedY();
					RData.MX		=a->GetAlignedX();
					RData.MY		=a->GetAlignedY();
					RData.HX		=0;
					RData.HY		=0;
					RData.UniqueID2	=UniqueID2;

					LBase->ConvertToTop(RData.X,RData.Y);
					LBase->ConvertToTop(RData.MX,RData.MY);
					LBase->ConvertToTop(RData.HX,RData.HY);

					RData.ExtraDataByte	=0;

					memset(&RData.AreaName,0,sizeof(RData.AreaName));

					AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
					if(AItem==NULL){
						AlgorithmInPageRoot		*APage=a->GetParent()->GetAlgorithmInPage();
						if(APage!=NULL){
							AItem=APage->FastSearchIDItem(a->GetItemID());
						}
					}
					if(AItem!=NULL){
						RData.LibID		=AItem->GetLibID();
						RData.UniqueID1	=AItem->GetID();
					}
					else{
						RData.LibID	=-1;
					}

					RData.NGTypeUniqueCode	=-1;	
					if(a->GetResultType()==ResultPosList::_ResultDWORD){
						RData.ResultType	=_ResultDWORD;
						RData.result1	=a->GetResult1();
						RData.result2	=a->GetResult2();
					}
					else if(a->GetResultType()==ResultPosList::_ResultDouble){
						RData.ResultType	=_ResultDouble;
						RData.ResultValue.ResultDouble=a->GetResultDouble();
					}
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					else{
						RData.LibType=0;
					}
					RData.Layer		=0;

					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					if(RData.ExtraDataByte>0){
						if(f->write(EData)!=RData.ExtraDataByte){
							return false;
						}
					}
					WrittenNGCount++;
				}
			}
		}
	}
	return true;
}

bool	ResultInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f
									,int &WrittenNGCount)
{
	//bool	OutputNGCause=GetLayersBase()->GetParamGlobal()->OutputNGCause;

	WrittenNGCount=0;
	int32	N=0;
	for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOk()==false){
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				N++;
			}
		}
	}
	if(N==0){
		for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsOk()==false){
				N++;
			}
		}
	}
	if(f->Save(N)==false){
		return false;
	}
	LayersBase	*LBase=GetLayersBase();
	if(LBase!=NULL){
		for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsOk()==false){
				int	UniqueID2=0;
				for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext(),UniqueID2++){
					QByteArray	EData;
					QStringList	AreaNames;
					if(p->AreaNames.count()==0){
						QString	AreaName;
						if(LBase==NULL || LBase->GetLogicDLLBase()==NULL){
							AreaName=/**/"";
							AreaNames.append(AreaName);
						}
						else if(LBase->GetLogicDLLBase()->LocalPos2Name(GetPage() ,p->Px	//+a->GetAlignedX()+p->Rx
																							,p->Py	//+a->GetAlignedY()+p->Ry 
																							,AreaName)==true){
							AreaNames.append(AreaName);
						}
					}
					else{
						AreaNames=p->AreaNames;
					}
					ResultPositionInfomation	RData;
					RData.Error=a->GetError();
					RData.PosResult	=p->result;
					RData.X			=p->Px+a->GetAlignedX()+p->Rx;
					RData.Y			=p->Py+a->GetAlignedY()+p->Ry;
					RData.MX		=a->GetAlignedX();
					RData.MY		=a->GetAlignedY();
					RData.HX		=p->Rx;
					RData.HY		=p->Ry;
					RData.UniqueID2	=UniqueID2;

					LBase->ConvertToTop(RData.X,RData.Y);
					LBase->ConvertToTop(RData.MX,RData.MY);
					LBase->ConvertToTop(RData.HX,RData.HY);

					p->GetExtraData(EData);
					RData.ExtraDataByte	=EData.size();

					if(AreaNames.count()!=0){
						QString	AName;
						int	AreaNameCount=0;
						for(int k=0;k<AreaNames.count();k++){
							if(AreaNames[k].length()!=0){
								AreaNameCount++;
							}
						}
						if(AreaNameCount!=0){
							for(int k=0;k<AreaNames.count();k++){
								AName=AName+AreaNames[k];
								if(k<AreaNames.count()-1){
									AName=AName+QString(",");
								}
							}
						}					
						::QString2Char(AName ,RData.AreaName ,sizeof(RData.AreaName));
					}
					else{
						memset(&RData.AreaName,0,sizeof(RData.AreaName));
					}
					AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
					if(AItem==NULL){
						AlgorithmInPageRoot		*APage=a->GetParent()->GetAlgorithmInPage();
						if(APage!=NULL){
							AItem=APage->FastSearchIDItem(a->GetItemID());
						}
					}
					if(AItem!=NULL){
						RData.LibID		=AItem->GetLibID();
						RData.UniqueID1	=AItem->GetID();
					}
					else{
						RData.LibID	=-1;
					}

					RData.NGTypeUniqueCode	=-1;	
					if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
						LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
						if(t!=NULL){
							RData.NGTypeUniqueCode	=t->TypeCode;
						}
					}
					if(p->ResultType==ResultPosList::_ResultDWORD){
						RData.ResultType	=_ResultDWORD;
						RData.result1	=p->GetResult1();
						RData.result2	=p->GetResult2();
					}
					else if(p->ResultType==ResultPosList::_ResultDouble){
						RData.ResultType	=_ResultDouble;
						RData.ResultValue.ResultDouble=p->GetResultDouble();
					}
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					else{
						if(p->Message.isEmpty()==false){
							QByteArray	B=p->Message.toLocal8Bit();
							strncpy((char *)RData.Something,B.data(),min((int)B.length(),(int)sizeof(RData.Something)));
						}
						RData.LibType=0;
					}
					RData.Layer		=0;

					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					if(RData.ExtraDataByte>0){
						if(f->write(EData)!=RData.ExtraDataByte){
							return false;
						}
					}
					WrittenNGCount++;
				}
			}
		}
		if(WrittenNGCount==0){
			for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->IsOk()==false){
					int	UniqueID2=0;
					QByteArray	EData;
					ResultPositionInfomation	RData;
					RData.Error=a->GetError();
					RData.PosResult	=0x10000+1;
					int	cx,cy;
					a->GetCenter(cx, cy);
					RData.X			=cx+a->GetAlignedX();
					RData.Y			=cy+a->GetAlignedY();
					RData.MX		=a->GetAlignedX();
					RData.MY		=a->GetAlignedY();
					RData.HX		=0;
					RData.HY		=0;
					RData.UniqueID2	=UniqueID2;

					LBase->ConvertToTop(RData.X,RData.Y);
					LBase->ConvertToTop(RData.MX,RData.MY);
					LBase->ConvertToTop(RData.HX,RData.HY);

					RData.ExtraDataByte	=0;

					memset(&RData.AreaName,0,sizeof(RData.AreaName));

					AlgorithmItemRoot	*AItem=a->GetAlgorithmItem();
					if(AItem==NULL){
						AlgorithmInPageRoot		*APage=a->GetParent()->GetAlgorithmInPage();
						if(APage!=NULL){
							AItem=APage->FastSearchIDItem(a->GetItemID());
						}
					}
					if(AItem!=NULL){
						RData.LibID		=AItem->GetLibID();
						RData.UniqueID1	=AItem->GetID();
					}
					else{
						RData.LibID	=-1;
					}

					RData.NGTypeUniqueCode	=-1;	
					if(a->GetResultType()==ResultPosList::_ResultDWORD){
						RData.ResultType	=_ResultDWORD;
						RData.result1	=a->GetResult1();
						RData.result2	=a->GetResult2();
					}
					else if(a->GetResultType()==ResultPosList::_ResultDouble){
						RData.ResultType	=_ResultDouble;
						RData.ResultValue.ResultDouble=a->GetResultDouble();
					}
					AlgorithmLibraryContainer	*pLibContainer=LogicDLLPoint->GetLibContainer();
					if(pLibContainer!=NULL){
						RData.LibType=pLibContainer->GetLibType();
					}
					else{
						RData.LibType=0;
					}
					RData.Layer		=0;

					if(f->write((const char *)&RData,sizeof(RData))!=sizeof(RData)){
						return false;
					}
					if(RData.ExtraDataByte>0){
						if(f->write(EData)!=RData.ExtraDataByte){
							return false;
						}
					}
					WrittenNGCount++;
				}
			}
		}
	}
	return true;
}

void	ResultInPagePI::OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,char *ResList)
{
	LayersBase	*LBase=GetLayersBase();
	bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;
	LogicDLLBaseClass	*LC=LBase->GetLogicDLLBase();

	char	Text[100];
	*ResList=0;
	for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOk()==false){
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				QStringList	AreaNames;
				if(p->AreaNames.count()==0){
					QString	AreaName;
					if(LC->LocalPos2Name(GetPage()  ,p->Px	//+a->GetAlignedX()+p->Rx
													,p->Py	//+a->GetAlignedY()+p->Ry 
													,AreaName)==true){
						AreaNames.append(AreaName);
					}
				}
				else{
					AreaNames=p->AreaNames;
				}
				int32	cPx=p->Px+a->GetAlignedX()+p->Rx;
				int32	cPy=p->Py+a->GetAlignedY()+p->Ry;
				LBase->ConvertToTop(cPx,cPy);
				int32	aPx=a->GetAlignedX();
				int32	aPy=a->GetAlignedY();
				LBase->ConvertToTop(aPx,aPy);
				int32	rPx=p->Rx;
				int32	rPy=p->Ry;
				LBase->ConvertToTop(rPx,rPy);

				strcat(ResList,/**/"<NGP X=\"");
				::ToStr(Text,cPx);
				strcat(ResList,Text);

				strcat(ResList,/**/"\" Y=\"");
				::ToStr(Text,cPy);
				strcat(ResList,Text);

				strcat(ResList,/**/"\" MX=\"");
				::ToStr(Text,aPx);
				strcat(ResList,Text);

				strcat(ResList,/**/"\" MY=\"");
				::ToStr(Text,aPy);
				strcat(ResList,Text);

				strcat(ResList,/**/"\" HX=\"");
				::ToStr(Text,rPx);
				strcat(ResList,Text);

				strcat(ResList,/**/"\" HY=\"");
				::ToStr(Text,rPy);
				strcat(ResList,Text);


				if(AreaNames.count()!=0){
					int	AreaNameCount=0;
					for(int k=0;k<AreaNames.count();k++){
						if(AreaNames[k].length()!=0){
							AreaNameCount++;
						}
					}
					if(AreaNameCount!=0){
						strcat(ResList,/**/"\" ARA=\"#");

						for(int k=0;k<AreaNames.count();k++){
							::QString2Char(AreaNames[k] ,Text ,sizeof(Text));
							strcat(ResList,Text);
							if(k<AreaNames.count()-1){
								strcat(ResList,/**/",");
							}
						}
					}
				}
				if(OutputNGCause==true){
					if(a->GetAlgorithmItem()!=NULL){
						strcat(ResList,/**/"\" LC=\"");
						::ToStr(Text,a->GetAlgorithmItem()->GetLibID());
						strcat(ResList,Text);
					}
					if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
						LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
						if(t!=NULL){
							strcat(ResList,/**/"\" TC=\"");
							::ToStr(Text,t->TypeCode);
							strcat(ResList,Text);
						}
					}
				}
				
				AlgorithmItemRoot	*aitem=a->GetAlgorithmItem();
				QString	m;
				if(aitem!=NULL)
					m=aitem->OutputResult(p);
				if(m.isEmpty()==false){
					strcat(ResList,/**/" ");
					::QString2Char(m ,Text ,sizeof(Text));
					strcat(ResList,Text);
				}

				if(p->ResultType==ResultPosList::_ResultDWORD){
					strcat(ResList,/**/"\" RS1=\"");
					::ToStr(Text,(int)p->GetResult1());
					strcat(ResList,Text);

					strcat(ResList,/**/"\" RS2=\"");
					::ToStr(Text,(int)p->GetResult2());
					strcat(ResList,Text);
				}
				else if(p->ResultType==ResultPosList::_ResultDouble){
					strcat(ResList,/**/"\" RS1=\"");
					::ToStr(Text,p->GetResultDouble());
					strcat(ResList,Text);
				}
				strcat(ResList,/**/"\" RAL=\"");
				::QString2Char(LogicDLLPoint->GetDLLRoot() ,Text ,sizeof(Text));
				strcat(ResList,Text);
				::QString2Char(LogicDLLPoint->GetDLLName() ,Text ,sizeof(Text));
				strcat(ResList,Text);

				strcat(ResList,/**/"\" LY=\"");
				strcat(ResList,/**/"0");
				strcat(ResList,/**/"\"/>");
			}
		}
	}
}

void	ResultInPagePI::OutputResult(FlexArea &Area ,int OffsetX ,int OffsetY
								,int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)
{
	LayersBase	*LBase=GetLayersBase();
	bool	OutputNGCause=LBase->GetParamGlobal()->OutputNGCause;
	LogicDLLBaseClass	*LC=LBase->GetLogicDLLBase();

	for(ResultInItemPI *a=Result.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsOk()==false){
			for(ResultPosList *p=a->GetPosListFirst();p!=NULL;p=p->GetNext()){
				if(Area.IsInclude(p->Px,p->Py)==true){
					QStringList	AreaNames;
					if(p->AreaNames.count()==0){
						QString	AreaName;
						if(LC->LocalPos2Name(GetPage()  
														,p->Px	//+a->GetAlignedX()+p->Rx + OffsetX
														,p->Py	//+a->GetAlignedY()+p->Ry + OffsetY
														,AreaName)==true){
							AreaNames.append(AreaName);
						}
					}
					else{
						AreaNames=p->AreaNames;
					}

					int32	cPx=p->Px+a->GetAlignedX()+p->Rx+OffsetX;
					int32	cPy=p->Py+a->GetAlignedY()+p->Ry+OffsetY;
					LBase->ConvertToTop(cPx,cPy);
					int32	aPx=a->GetAlignedX();
					int32	aPy=a->GetAlignedY();
					LBase->ConvertToTop(aPx,aPy);
					int32	rPx=p->Rx;
					int32	rPy=p->Ry;
					LBase->ConvertToTop(rPx,rPy);
					QString	Msg
						=QString(/**/"<NGP X=\"")
						+QString::number(cPx +OffsetX)
						+QString(/**/"\" Y=\"")
						+QString::number(cPy)
						+QString(/**/"\" MX=\"")
						+QString::number(aPx)
						+QString(/**/"\" MY=\"")
						+QString::number(aPy)
						+QString(/**/"\" HX=\"")
						+QString::number(rPx)
						+QString(/**/"\" HY=\"")
						+QString::number(rPy);

					if(AreaNames.count()!=0){
						int	AreaNameCount=0;
						for(int k=0;k<AreaNames.count();k++){
							if(AreaNames[k].length()!=0){
								AreaNameCount++;
							}
						}
						if(AreaNameCount!=0){
							Msg=Msg+QString(/**/"\" ARA=\"#");
							for(int k=0;k<AreaNames.count();k++){
								Msg=Msg+AreaNames[k];
								if(k<AreaNames.count()-1){
									Msg=Msg+QString(",");
								}
							}
						}
					}
					if(OutputNGCause==true){
						if(a->GetAlgorithmItem()!=NULL){
							Msg=Msg	+QString(/**/"\" LC=\"")
								+QString::number(a->GetAlgorithmItem()->GetLibID());
						}
						if(GetAlgorithmInPage()!=NULL && GetAlgorithmInPage()->GetParentBase()!=NULL){
							LibNGTypeItem	*t=GetAlgorithmInPage()->GetParentBase()->GetLibNGTypeItem(p->NGTypeUniqueCode);
							if(t!=NULL){
								Msg=Msg	+QString(/**/"\" TC=\"")
										+QString::number(t->TypeCode);
							}
						}
					}
					if(p->ResultType==ResultPosList::_ResultDWORD){
						Msg=Msg	+QString(/**/"\" RS1=\"")
								+QString::number(p->GetResult1())
								+QString(/**/"\" RS2=\"")
								+QString::number(p->GetResult2())
								+QString(/**/"\" RAL=\"")
								+LogicDLLPoint->GetDLLRoot()
								+QString(/**/":")
								+LogicDLLPoint->GetDLLName()
								+QString(/**/"\" LY=\"")
								+QString::number(0)
								+QString(/**/"\"/>");
					}
					else if(p->ResultType==ResultPosList::_ResultDouble){
						Msg=Msg	+QString(/**/"\" RS1=\"")
								+QString::number(p->GetResultDouble())
								+QString(/**/"\" RS2=\"")
								+LogicDLLPoint->GetDLLRoot()
								+QString(/**/":")
								+LogicDLLPoint->GetDLLName()
								+QString(/**/"\" LY=\"")
								+QString::number(0)
								+QString(/**/"\"/>");
					}
					ResList<<Msg;
				}
			}
		}
	}
}

void	ResultInPagePI::ExecuteInAllItems(void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		Func(r,Something);
	}
}

void	ResultInPagePI::GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsNGNearXY(area)==true){
			ResultInItemRootPointerList	*d=new ResultInItemRootPointerList(r);
			Ret.AppendList(d);
		}
	}
}
void	ResultInPagePI::GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetErrorGroupID()==ErrorGroupID){
			ResultInItemRootPointerList	*d=new ResultInItemRootPointerList(r);
			Ret.AppendList(d);
		}
	}
}
void	ResultInPagePI::BindNGAreaListContainer(NGAreaListContainer &List)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		r->BindNGAreaListContainer(List);
	}
}
void	ResultInPagePI::ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item,void *_Something),void *Something)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		ItemFunc(r,Something);
	}
}
void	ResultInPagePI::ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		for(ResultPosList *p=r->GetPosListFirst();p!=NULL;p=p->GetNext()){
			PosFunc(r,p,Something);
		}
	}
}
void	ResultInPagePI::SetResultMarkForLearning(void)
{
	DataInPage		*dp=GetDataInPage();
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsOk()==false){
			for(ResultPosList *p=r->GetPosListFirst();p!=NULL;p=p->GetNext()){
				dp->SetResultMarkForLearning(0,p->Px,p->Py);
			}
		}
	}
}

void	ResultInPagePI::ReviveResult(LearningImage *c)
{
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		r->ReviveResult(c);
	}
}

int		ResultInPagePI::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(ResultInItemPI *r=Result.GetFirst();r!=NULL;r=r->GetNext()){
		int	count=r->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}
void	ResultInPagePI::MakeResultDetailInNG(DetailResultInfoListContainerAll &List)
{
	AlgorithmBase	*ABase=GetAlgorithmBase();
	for(ResultInItemPI *R=Result.GetFirst();R!=NULL;R=R->GetNext()){
		if(R->IsOk()==false){
			AlgorithmItemRoot	*Item=R->GetAlgorithmItem();
			DetailResultInfoListContainer *RetList=new DetailResultInfoListContainer();
			for(ResultPosList *r=R->GetPosListFirst();r!=NULL;r=r->GetNext()){
				ABase->GetDrawResultDetail(Item,r,*RetList);
			}
			List.AppendList(RetList);
		}
	}
}

ExeResult	ResultInPagePI::ExecuteInitialAfterEditPrev(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteInitialAfterEdit	(int ExeID)
{
	AlgoPointer=PhaseParent->AlgoPointer->GetPageData(Page);
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteInitialAfterEditPost(ExeID,c);
			}
		}
	}
	int	ResultCount=GetItemCount();
	AllocateForFastSearch(ResultCount);
	int	t=0;
	for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext(),t++){
		ItemDimPointer[t]=c;
	}
	SortResultDimPointer();

	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteInitialAfterEditPost(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteStartByInspection	(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteStartByInspectionPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteCaptured		(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteCapturedPost(ExeID,c,CapturedList);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecutePreAlignment		(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecutePreAlignmentPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteAlignment			(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteAlignmentPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecutePreProcessing		(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecutePreProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteProcessing			(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteProcessingRevived	(int ExeID)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecuteProcessingRevivedPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecutePostProcessing		(int ExeID)
{
	CalcDone	=true;
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetResultAnalizerItemBaseContainer()!=NULL){
		ResultAnalizerItemBaseContainer	*A=LBase->GetResultAnalizerItemBaseContainer();
		if(A->GetCount()>0){
			for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
				A->ExecutePostProcessingPost(ExeID,c);
			}
		}
	}
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecutePreScanning		(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecuteScanning			(int ExeID)
{
	return _ER_true;
}
ExeResult	ResultInPagePI::ExecutePostScanning		(int ExeID)
{
	return _ER_true;
}

AlgorithmInPageInOnePhase	*ResultInPagePI::GetAlgorithmInPageInOnePhase(void)	const
{
	return GetAlgorithmBase()->GetPageDataPhase(GetPhaseCode());
}

AlgorithmBase				*ResultInPagePI::GetAlgorithmBase(void)	const
{
	return Parent->GetLogicDLL()->GetInstance();
}
void	ResultInPagePI::ClearResult(void)
{
	for(ResultInItemPI *c=Result.GetFirst();c!=NULL;c=c->GetNext()){
		c->ClearResult();
	}
}


ResultBaseForAlgorithmPI::ResultBaseForAlgorithmPI(LogicDLL *parent)
:ResultBaseForAlgorithmRoot(parent)
{
}
ResultBaseForAlgorithmPI::~ResultBaseForAlgorithmPI(void)
{
}
	
ResultInPageRoot	*ResultBaseForAlgorithmPI::CreatePage(int phase ,int page)
{	
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetPageDataPhase(phase)!=NULL){
		return new ResultInPagePI(GetPageDataPhase(phase),LBase->GetPageDataPhase(phase)->GetPageData(page));	
	}
	return NULL;
}
ResultBaseForAlgorithmRoot	*ResultBaseForAlgorithmPI::CreateResultBaseForAlgorithm(void)
{
	ResultBaseForAlgorithmPI	*r=new ResultBaseForAlgorithmPI(GetLogicDLL());
	r->Initial();
	return r;
}

bool	ResultBaseForAlgorithmPI::DrawResult(int32 ShowFixedPhase
											, QPainter &PntFromIData ,QImage *IData 
											,int MovX ,int MovY ,double ZoomRate,int localPage)
{
	if(GetLogicDLL()!=NULL){
		return GetLogicDLL()->DrawResultBase(ShowFixedPhase,this ,PntFromIData ,IData ,MovX ,MovY ,ZoomRate,localPage);
	}
	return true;
}


void	ResultBaseForAlgorithmPI::ExecuteInAllItems(void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase		*Ph=GetPageDataPhase(phase);
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			ResultInPageRoot	*P=Ph->GetPageData(localPage);
			if(P!=NULL){
				P->ExecuteInAllItems(Func,Something);
			}
		}
	}
}

void	ResultBaseForAlgorithmPI::ExecuteInAllItems(int phase,void (*Func)(ResultInItemRoot *,void *),void *Something)
{
	ResultBasePhase		*Ph=GetPageDataPhase(phase);
	for(int localPage=0;localPage<GetPageNumb();localPage++){
		ResultInPageRoot	*P=Ph->GetPageData(localPage);
		if(P!=NULL){
			P->ExecuteInAllItems(Func,Something);
		}
	}
}


//===========================================================================================================

AlgorithmItemPI::AlgorithmItemPI(void): AlgorithmItemRoot()
{
	Parent=NULL;	
}
AlgorithmItemPI::AlgorithmItemPI(FlexArea &area) : AlgorithmItemRoot(area)
{
	Parent=NULL;	
}
AlgorithmItemPI::AlgorithmItemPI(FlexArea *area) : AlgorithmItemRoot(area)
{
	Parent=NULL;	
}

void	AlgorithmItemPI::SetParentVirtual(AlgorithmParentFromItem *parent)
{
	SetParent(dynamic_cast<AlgorithmInPagePI *>(parent));
}

void	AlgorithmItemPI::SetParent(AlgorithmInPagePI *parent)
{	
	Parent=parent;	
	if(Parent!=NULL){
		SetLearn(Parent->GetLayersBase());
		GetThresholdBaseWritable()->SetLearn(Parent->GetLayersBase());
	}
}
AlgorithmInPageInOnePhase	*AlgorithmItemPI::GetAlgorithmInPageInOnePhase(void)	const
{
	return GetParentInPage()->GetParentPhase();
}
AlgorithmParentFromItem	*AlgorithmItemPI::GetParentAlgorithm(void)	const
{	
	return Parent;
}

AlgorithmItemPI	&AlgorithmItemPI::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemRoot::operator=(src);
	Parent			=((AlgorithmItemPI *)&src)->Parent;
	return(*this);
}
ExeResult	AlgorithmItemPI::ExecuteInitialAfterEdit	(int ExeID 
														,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemRoot::ExecuteInitialAfterEdit	(ExeID,ThreadNo,Res,EInfo);
	for(SubtractItem *b=SubBlock.GetFirst();b!=NULL;b=b->GetNext()){
		b->IndexAfterEdit=Parent->SearchIDItem(b->ItemID);
	}
	return Ret;
}
ResultInItemRoot	*AlgorithmItemPI::GetCurrentResult(void)
{
	if(AlgorithmItemRoot::GetCurrentResult()!=NULL){
		return AlgorithmItemRoot::GetCurrentResult();
	}

	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase	*Ph=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(GetParentInPage()->GetPage()));
		if(Rp!=NULL){
			ResultInItemPI		*rItem=Rp->GetItem(GetID());
			return rItem;
		}
	}
	return NULL;
}
ResultInItemRoot	*AlgorithmItemPI::GetResult(ResultInPageRoot *Rp)
{
	ResultInPagePI	*R=dynamic_cast<ResultInPagePI *>(Rp);
	ResultInItemPI	*rItem=R->GetItem(GetID());
	return rItem;
}

ClipboardAlgorithmItem	*AlgorithmItemPI::CreateClipboardItem(void)
{
	if(GetSelected()==true){
		ClipboardAlgorithmItem	*Dest=new ClipboardAlgorithmItem();
		QBuffer	Buff(&Dest->ItemData);
		Buff.open(QIODevice::ReadWrite);
		Save(&Buff);
		Dest->Area			=GetArea();
		Dest->Page			=GetPage();
		Dest->ItemClassType	=GetItemClassType();
		Dest->Layer			=0;
		return Dest;
	}
	return NULL;
}

int	AlgorithmItemPI::GetMasterBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllMasterBuff()){
		iMasterNo=GetCountAllMasterBuff()-1;
	}
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetMasterBuffPointer(iMasterNo);
	}
	return layer;
}
int	AlgorithmItemPI::GetMasterBuffList(int n,ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetMasterBuffPointer(n);
	}
	return layer;
}

int	AlgorithmItemPI::GetBackGroundBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllBackGroundBuff()){
		iMasterNo=GetCountAllBackGroundBuff()-1;
	}
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetBackGroundBuffPointer(iMasterNo);
	}
	return layer;
}
int	AlgorithmItemPI::GetBackGroundBuffList(int n,ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetBackGroundBuffPointer(n);
	}
	return layer;
}
int	AlgorithmItemPI::GetTargetBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTargetBuff();
	}
	return layer;
}
int	AlgorithmItemPI::GetTargetTRBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTargetTRBuff();
	}
	return layer;
}
int	AlgorithmItemPI::GetBitBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetBitBuff();
	}
	return layer;
}
int	AlgorithmItemPI::GetTrialTargetBuffList	(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTrialTargetBuff();
	}
	return layer;
}

int	AlgorithmItemPI::GetMasterBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllMasterBuff()){
		iMasterNo=GetCountAllMasterBuff()-1;
	}
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetMasterBuffPointer(iMasterNo));
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmItemPI::GetMasterBuffList(int n,ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetMasterBuffPointer(n));
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmItemPI::GetBackGroundBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	iMasterNo=GetMasterNo();
	if(iMasterNo<0){
		iMasterNo=0;
	}
	if(iMasterNo>=GetCountAllBackGroundBuff()){
		iMasterNo=GetCountAllBackGroundBuff()-1;
	}
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetBackGroundBuffPointer(iMasterNo));
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmItemPI::GetBackGroundBuffList(int n,ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetBackGroundBuffPointer(n));
		ImageList.AppendList(a);
	}
	return layer;
}
int	AlgorithmItemPI::GetTargetBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTargetBuff());
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmItemPI::GetTargetTRBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTargetTRBuff());
		ImageList.AppendList(a);
	}
	return layer;
}
int	AlgorithmItemPI::GetBitBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetBitBuff());
		ImageList.AppendList(a);
	}
	return layer;
}
int	AlgorithmItemPI::GetTrialTargetBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetParentInPage()->GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTrialTargetBuff());
		ImageList.AppendList(a);
	}
	return layer;
}


void	AlgorithmItemPI::GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
	if(GetSelected()==true){
		int	gx1,gy1,gx2,gy2;
		int	x1,y1,x2,y2;
		LayersBase	*L=GetLayersBase();
		int	globalPage=L->GetGlobalPageFromLocal(GetPage());
		GetXY(gx1 ,gy1 ,gx2 ,gy2);
		x1=gx1+dx+L->GetGlobalOutlineOffset(globalPage)->x;
		y1=gy1+dy+L->GetGlobalOutlineOffset(globalPage)->y;
		x2=gx2+dx+L->GetGlobalOutlineOffset(globalPage)->x;
		y2=gy2+dy+L->GetGlobalOutlineOffset(globalPage)->y;

		int	Lx1,Ly1,Lx2,Ly2;
		DataInPage	*Pg=GetDataInPage();
		ItemPointerListInPage	*LPg=OutsideItems.GetFirst();
		for(int page=0;page<MaxGlobalPage && LPg!=NULL;page++,LPg=LPg->GetNext()){
			if(page!=globalPage){
				Lx1=x1 - L->GetGlobalOutlineOffset(page)->x;
				Ly1=y1 - L->GetGlobalOutlineOffset(page)->y;
				Lx2=Lx1+(x2-x1);
				Ly2=Ly1+(y2-y1);
				if(CheckOverlapRectRect(0,0, Pg->GetDotPerLine(), Pg->GetMaxLines()
					,Lx1,Ly1,Lx2,Ly2)==true){
					ItemPointerListInLayer	*L=new ItemPointerListInLayer(0);
					LPg->LayerList.AppendList(L);
					L->ItemList.AppendList(new ItemPointerList(this,Lx1-gx1,Ly1-gy1));
				}
			}
		}
	}
}

bool	AlgorithmItemPI::GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInPageRoot	*p=GetParentInPage();
	return p->GetReflectionMap(Mode ,Map ,LibData ,Anything);
}
bool	AlgorithmItemPI::GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,void *Anything)
{
	AlgorithmInPageRoot	*p=GetParentInPage();
	return p->GetReflectionMap(Mode ,Map ,Anything);
}
bool	AlgorithmItemPI::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInPageRoot	*p=GetParentInPage();
	return p->GetReflectionVector(Mode ,Vector ,LibData ,Anything);
}
bool	AlgorithmItemPI::GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything)
{
	AlgorithmInPageRoot	*p=GetParentInPage();
	return p->GetReflectionVector(Mode ,Vector ,Anything);
}
bool	AlgorithmItemPI::IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything)
{
	AlgorithmInPageRoot	*p=GetParentInPage();
	return p->IncludeLibInReflection(Mode ,LibData ,Anything);
}

void	AlgorithmItemPI::CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)
{
	AlgorithmItemPI	*s=dynamic_cast<AlgorithmItemPI *>(src);
	if(s!=NULL){
		if(s->GetParent()!=NULL){
			SetParent(s->GetParent());
		}
		else{
			AlgorithmInPagePI	*p=dynamic_cast<AlgorithmInPagePI *>(P);
			if(p!=NULL){
				SetParent(p);
			}
		}
	}
}

void	AlgorithmItemPI::CopyFrom(AlgorithmItemRoot *src)
{
	if(GetParent()==NULL){
		SetParent(((AlgorithmItemPI *)src)->GetParent());
	}
	operator=(*src);
}
bool	AlgorithmItemPI::SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)
{
	AlgorithmInPageInOnePhase	*Ph=InstBase->GetPageDataPhase(PhaseCode);
	if(Ph!=NULL){
		int	LPage=InstBase->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		AlgorithmInPageRoot *Pg=Ph->GetPageData(LPage);
		if(Pg!=NULL){
			Parent=(AlgorithmInPagePI *)Pg;
			return true;
		}
	}
	return false;
}


//===========================================================================================================
AlgorithmInPagePI::OMPAlgorithmItemStruct::OMPAlgorithmItemStruct(void)
{
	CalcThread	=NULL;
	Result		=NULL;
}
AlgorithmInPagePI::OMPAlgorithmItemStruct::~OMPAlgorithmItemStruct(void)
{
	if(CalcThread!=NULL){
		delete	[]CalcThread;
		CalcThread=NULL;
	}
	if(Result!=NULL){
		delete	[]Result;
		Result=NULL;
	}
	CalcThreadCount=0;
}
void	AlgorithmInPagePI::OMPAlgorithmItemStruct::Alloc(AlgorithmInPagePI *parent ,int threadNo,int N)
{
	Parent=parent;
	ThreadNo=threadNo;
	CalcThreadCount=N;
	if(N!=0){
		CalcThread	=new AlgorithmItemPI*[N];
		Result		=new ResultInItemPI*[N];
		for(int i=0;i<N;i++){
			CalcThread[i]=NULL;
			Result[i]=NULL;
		}
	}
}
void	AlgorithmInPagePI::OMPAlgorithmItemStruct::Set(int n,AlgorithmItemPI	*c,ResultInItemPI	*r)
{
	CalcThread[n]=c;
	Result[n]=r;
}

ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteInitialAfterEdit	(ExeID,ThreadNo,Result[i],EInfo);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteStartByInspection(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteStartByInspection	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteCaptured	(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteCaptured	(ExeID,ThreadNo,Result[i],CapturedList);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecutePreAlignment	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreAlignment	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteAlignment		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteAlignment	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecutePreProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreProcessing	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteProcessing		(int ExeID)
{
	LayersBase	*LBase=Parent->GetLayersBase();
	DWORD	StartMilisec=LBase->GetStartInspectionTimeMilisec();
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			if(GetComputerMiliSec()-StartMilisec>=Parent->GetParamGlobal()->MaxInspectMilisec){
				break;
			}
			if(Parent->GetNGCounter()<=Parent->GetParamGlobal()->MaxNGCountsPerCam
			&& CalcThread[i]->IsEffective()==true){
				Result[i]->SetAlgorithmItem(CalcThread[i]);
				ExeResult	RR=CalcThread[i]->ExecuteProcessing	(ExeID,ThreadNo,Result[i]);
				if(RR!=_ER_true){
					Ret=RR;
				}
				if(CalcThread[i]->GetInvertLogic()==true){
					if(Result[i]->GetError()==1){
						Result[i]->SetError(2);
					}
					else if(Result[i]->GetError()>=2){
						Result[i]->SetError(1);
					}
					if(Result[i]->GetPosListFirst()==NULL){
						int	cx,cy;
						CalcThread[i]->GetCenter(cx,cy);
						Result[i]->GetPosList().AppendList(new ResultPosList(cx,cy));
					}
				}

				if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
					#ifdef _MSC_VER
					if(_CrtCheckMemory()==false){
						ErrorOccurs();
					}
					#endif
				}
				if(Result[i]->GetError()>=2){
					if(LBase->GetResultFromAlgorithm()==0){
						LBase->SetResultFromAlgorithm(1);
					}
				}
				Parent->IncrementNGCounterWithMutex(Result[i]->GetError());
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecutePostProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePostProcessing	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}

ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecutePreScanning	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePreScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecuteScanning		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecuteScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}
ExeResult	AlgorithmInPagePI::OMPAlgorithmItemStruct::ExecutePostScanning		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	for(int i=0;i<CalcThreadCount;i++){
		if(CalcThread[i]!=NULL){
			ExeResult	RR=CalcThread[i]->ExecutePostScanning	(ExeID,ThreadNo,Result[i]);
			if(RR!=_ER_true){
				Ret=RR;
			}
			if(CalcThread[i]->GetParamGlobal()->DebugLevel>=2){
				#ifdef _MSC_VER
				if(_CrtCheckMemory()==false){
					ErrorOccurs();
				}
				#endif
			}
		}
	}
	return Ret;
}

struct	PriorityMapClass
{
	AlgorithmItemPI *Point;
	int			DrawingPriority;
	int			PriorityCode;
};

static	int	PriorityMapSortFunc(const void *a ,const void *b)
{
	if(((struct PriorityMapClass *)a)->PriorityCode<((struct PriorityMapClass *)b)->PriorityCode){
		return -1;
	}
	if (((struct PriorityMapClass*)a)->PriorityCode>((struct PriorityMapClass*)b)->PriorityCode) {
		return 1;
	}

	if(((struct PriorityMapClass *)a)->DrawingPriority>((struct PriorityMapClass *)b)->DrawingPriority){
		return -1;
	}
	if(((struct PriorityMapClass *)a)->DrawingPriority<((struct PriorityMapClass *)b)->DrawingPriority){
		return 1;
	}
	return 0;
}


AlgorithmInPagePI::AlgorithmInPagePI(AlgorithmBase *parent)
{
	Parent				=parent;
	CalcThreadDim		=NULL;
	CalcThreadDataCount	=0;
	DrawResultTableNumb	=0;
	DrawResultATable	=NULL;
	DrawResultRTable	=NULL;
	AllocatedCountMasterBuff	=0;
	AllocatedCountBackGroundBuff=0;
	MasterBuffDim		=NULL;
	BackGroundBuffDim	=NULL;
	TargetBuffDim		=NULL;
	TargetTRBuffDim		=NULL;
	BitBuffDim			=NULL;
	TrialTargetBuffDim	=NULL;
	ThresholdDummy		=NULL;
	#pragma omp parallel                             
	{                                                
		ThreadNumb=omp_get_num_threads();
	}
}
AlgorithmInPagePI::~AlgorithmInPagePI(void)
{
	ReleaseData();
	if(CalcThreadDim!=NULL){
		delete	[]CalcThreadDim;
	}
	CalcThreadDim=NULL;

	if(DrawResultATable!=NULL){
		delete	[]DrawResultATable;
	}
	DrawResultATable=NULL;

	if(DrawResultRTable!=NULL){
		delete	[]DrawResultRTable;
	}
	DrawResultRTable=NULL;

	for(int i=0;i<AllocatedCountMasterBuff;i++){
		if(MasterBuffDim[i]!=NULL){
			delete	[]MasterBuffDim[i];
		}
	}
	if(MasterBuffDim!=NULL){
		delete	[]MasterBuffDim;
	}
	MasterBuffDim=NULL;

	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		if(BackGroundBuffDim[i]!=NULL){
			delete	[]BackGroundBuffDim[i];
		}
	}
	if(BackGroundBuffDim!=NULL){
		delete	[]BackGroundBuffDim;
	}
	BackGroundBuffDim=NULL;

	if(TargetBuffDim!=NULL){
		delete	[]TargetBuffDim;
	}
	TargetBuffDim=NULL;

	if(TargetTRBuffDim!=NULL){
		delete	[]TargetTRBuffDim;
	}
	TargetTRBuffDim=NULL;

	if(BitBuffDim!=NULL){
		delete	[]BitBuffDim;
		BitBuffDim=NULL;
	}
	if(TrialTargetBuffDim!=NULL){
		delete	[]TrialTargetBuffDim;
	}
	TrialTargetBuffDim=NULL;

	if(ThresholdDummy!=NULL){
		delete	ThresholdDummy;
		ThresholdDummy=NULL;
	}
}

void	AlgorithmInPagePI::ReleaseData(void)
{
}

void	AlgorithmInPagePI::Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)
{
	AlgorithmInPageRoot::Initial(phaseParent,Base);

	for(int i=0;i<AllocatedCountMasterBuff;i++){
		if(MasterBuffDim[i]!=NULL){
			delete	[]MasterBuffDim[i];
		}
	}
	if(MasterBuffDim!=NULL){
		delete	[]MasterBuffDim;
	}
	MasterBuffDim=NULL;

	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		if(BackGroundBuffDim[i]!=NULL){
			delete	[]BackGroundBuffDim[i];
		}
	}
	if(BackGroundBuffDim!=NULL){
		delete	[]BackGroundBuffDim;
	}
	BackGroundBuffDim=NULL;

	if(TargetBuffDim!=NULL){
		delete	[]TargetBuffDim;
	}
	TargetBuffDim=NULL;

	if(TargetTRBuffDim!=NULL){
		delete	[]TargetTRBuffDim;
	}
	TargetTRBuffDim=NULL;

	if(BitBuffDim!=NULL){
		delete	[]BitBuffDim;
	}
	BitBuffDim=NULL;

	if(TrialTargetBuffDim!=NULL){
		delete	[]TrialTargetBuffDim;
	}
	TrialTargetBuffDim=NULL;

	AllocatedCountMasterBuff=Base->GetCountAllMasterBuff();
	MasterBuffDim	=new ImageBuffer **[AllocatedCountMasterBuff];
	for(int i=0;i<AllocatedCountMasterBuff;i++){
		MasterBuffDim[i]=new ImageBuffer *[GetLayerNumb()];
	}
	AllocatedCountBackGroundBuff=Base->GetCountAllBackGroundBuff();
	BackGroundBuffDim	=new ImageBuffer **[AllocatedCountBackGroundBuff];
	for(int i=0;i<AllocatedCountBackGroundBuff;i++){
		BackGroundBuffDim[i]=new ImageBuffer *[GetLayerNumb()];
	}
	TargetBuffDim		=new ImageBuffer *[GetLayerNumb()];
	TargetTRBuffDim		=new ImageBuffer *[GetLayerNumb()];
	BitBuffDim			=new ImageBuffer *[GetLayerNumb()];
	TrialTargetBuffDim	=new ImageBuffer *[GetLayerNumb()];
	for(int L=0;L<GetLayerNumb();L++){
		if(GetDataInLayer(L)!=NULL){
			for(int i=0;i<AllocatedCountMasterBuff;i++){
				(MasterBuffDim[i])[L]=GetDataInLayer(L)->GetMasterBuffPointer(i);
			}
			for(int i=0;i<AllocatedCountBackGroundBuff;i++){
				(BackGroundBuffDim[i])[L]=GetDataInLayer(L)->GetBackGroundBuffPointer(i);
			}
			TargetBuffDim[L]		=&GetDataInLayer(L)->GetTargetBuff();
			TargetTRBuffDim[L]		=&GetDataInLayer(L)->GetTargetTRBuff();
			BitBuffDim	 [L]		=&GetDataInLayer(L)->GetBitBuff();
			TrialTargetBuffDim[L]	=&GetDataInLayer(L)->GetTrialTargetBuff();
		}
	}
}

void	AlgorithmInPagePI::Release(void)
{
	ReleaseData();
}
void	AlgorithmInPagePI::InitializeToStart(void)
{
	RemoveAllDatas();
}
void	AlgorithmInPagePI::InitialAfterParamLoaded(void)
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->InitialAfterParamLoaded();
	}
}

void	AlgorithmInPagePI::SizeChanged(LayersBase *Base)
{
	Initial(GetParentPhase(),Base);
}
bool	AlgorithmInPagePI::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	bool	Ret=true;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ReallocXYPixels(NewDotPerLine ,NewMaxLines)==false){
			Ret=false;
		}
	}

	PDataInPage	=GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());
	AlgorithmItemPointerListContainer	Container;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	x1,y1,x2,y2;
		c->GetXY(x1,y1,x2,y2);
		if(x1<0 || NewDotPerLine<=x2 || y1<0 || NewMaxLines<=y2){
			AlgorithmItemPointerList	*k=new AlgorithmItemPointerList(c);
			Container.AppendList(k);
		}
	}
	for(AlgorithmItemPointerList *k=Container.GetFirst();k!=NULL;k=k->GetNext()){
		RemoveItem(k->GetItem());
	}
	return Ret;
}
bool	AlgorithmInPagePI::Reallocate(int newLayerNumb)
{	
	PDataInPage	=GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());
	return true;
}
bool	AlgorithmInPagePI::ReallocateMasterCount(int CountMaster)
{
	bool	Ret=true;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->ReallocateMasterCount(CountMaster)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	AlgorithmInPagePI::CopyShadowAlgorithmPage(ShadowTree *Child ,const AlgorithmInPageRoot &SrcParent)
{
	bool	Ret=true;
	for(const AlgorithmItemPI *c=((AlgorithmInPagePI *)&SrcParent)->GetFirstData();c!=NULL;c=c->GetNext()){
		if(Child->CopyShadowAlgorithmItem(this,*c)==false){
			Ret=false;
		}
	}
	return Ret;
}

bool	AlgorithmInPagePI::Save(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::Save(f)==false){
			return false;
		}
		int32	Ver=2;
		if(::Save(f,Ver)==false){
			return(false);
		}

		int32	N=Data.GetNumber();
		if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
			return(false);
		}
		for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
			int32	ItemClassType	=c->GetItemClassType();
			if(::Save(f,ItemClassType)==false){
				return false;
			}
			if(c->Save(f)==false){
                return(false);
			}
		}
	}
    return(true);
}
bool	AlgorithmInPagePI::Load(QIODevice *f)
{
	Data.RemoveAll();
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::Load(f)==false){
			return false;
		}
		int32	Ver;
		if(::Load(f,Ver)==false){
			return(false);
		}

		int32	N;
		if(::Load(f,N)==false){
			return(false);
		}
		for(int i=0;i<N;i++){
			int32	ItemClassType=0;
			if(Ver>=2){
				if(::Load(f,ItemClassType)==false){
					return false;
				}
			}
			AlgorithmItemRoot	*c=CreateItem(ItemClassType);
			if(c==NULL){
				::SendErrorMessage(QString(/**/"CreateItem returns NULL in AlgorithmInPagePI::Load : ")+QString(typeid(*this).name())+QString(/**/" Arg : ")+QString::number(ItemClassType));
				return false;
			}
			((AlgorithmItemPI *)c)->SetParent(this);
			if(c->Load(f,GetLayersBase())==false){
				::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInPagePI::Load : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(i));
                return(false);
			}
			AppendItemFromLoad(c);
			if(c->GetID()>=StartItemID){
				StartItemID=c->GetID()+1;
			}
		}
	}
	Changed=false;
    return(true);
}
bool	AlgorithmInPagePI::LoadByTransform(QIODevice *f ,TransformBase &Param)
{
	if(Load(f)==false){
		return false;
	}
	int	n=0;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),n++){
		if(c->Transform(Param)==false){
			::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInPagePI::LoadByTransform : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(n));
			return(false);
		}
	}
	Changed=false;
    return(true);
}

bool    AlgorithmInPagePI::LoadAppend(QIODevice *f)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->GetModeLoadSaveInPlayer()==true || (ABase->GetModeLoadSaveInPlayer()==false && GetLayersBase()->GetModeInspectionPlayer()==false)){
		if(AlgorithmInPageRoot::LoadAppend(f)==false){
			return false;
		}
		int32	Ver;
		if(::Load(f,Ver)==false){
			return false;
		}
		int32	N;
		if(f->read((char *)&N,sizeof(N))!=sizeof(N)){
			return(false);
		}
		for(int i=0;i<N;i++){
			int32	ItemClassType=0;
			if(Ver>=2){
				if(::Load(f,ItemClassType)==false){
					return false;
				}
			}
			AlgorithmItemRoot	*c=CreateItem(ItemClassType);
			if(c==NULL){
				::SendErrorMessage(QString(/**/"CreateItem returns NULL in AlgorithmInPagePI::LoadAppend : ")+QString(typeid(*this).name())+QString(/**/" Arg : ")+QString::number(ItemClassType));
				return false;
			}
			((AlgorithmItemPI *)c)->SetParent(this);
			if(c->Load(f,GetLayersBase())==false){
				::SendErrorMessage(QString(/**/"Item->Load returns false in AlgorithmInPagePI::LoadAppend : ")+QString(typeid(*this).name())+QString(/**/" Turn : ")+QString::number(i));
                return(false);
			}
			for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				if(a->GetID()==c->GetID()){
					c->SetID(StartItemID);
					StartItemID++;
				}
			}
			AppendItemFromLoad(c);
			if(c->GetID()>=StartItemID){
				StartItemID=c->GetID()+1;
			}
		}
		Changed=true;
	}
    return(true);
}
	
bool	AlgorithmInPagePI::SaveHistgram(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	int32	N=Data.GetNumber();
	if(::Save(f,N)==false){
		return(false);
	}
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(::Save(f,c->GetID())==false){
			return(false);
		}		
		if(c->SaveHistgram(f)==false){
            return(false);
		}
	}
    return(true);
}

bool	AlgorithmInPagePI::LoadHistgram(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return(false);
	}

	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ItemID;
		if(::Load(f,ItemID)==false){
			return false;
		}
		AlgorithmItemRoot	*c=FastSearchIDItem(ItemID);
		if(c!=NULL){
			if(c->LoadHistgram(f)==false){
				return(false);
			}
		}
		else{
			AlgorithmDummyItem	Dummy;
			if(Dummy.LoadHistgram(f)==false){
				return(false);
			}
		}
	}
    return(true);
}

void	AlgorithmInPagePI::ClearHistgram(void)
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->ClearHistgram();
	}
}
bool	AlgorithmInPagePI::SaveOnlyThreshold(QIODevice *f)
{
	int32	N=GetItemCount();
	if(::Save(f,N)==false){
		return false;
	}

	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetThresholdBaseWritable()!=NULL){
			int32	ID=c->GetID();
			if(::Save(f,ID)==false){
				return false;
			}
			int32	ItemClassType=c->GetItemClassType();
			if(::Save(f,ItemClassType)==false){
				return false;
			}

			if(c->GetThresholdBaseWritable()->Save(f)==false){
				return false;
			}
		}
	}
	return true;
}
bool	AlgorithmInPagePI::LoadOnlyThreshold(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ID;
		if(::Load(f,ID)==false){
			return false;
		}
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return false;
		}
		AlgorithmItemRoot	*c=FastSearchIDItem(ID);
		if(c!=NULL){
			if(c->GetThresholdBaseWritable()->Load(f)==false){
				return false;
			}
		}
		else{
			AlgorithmItemRoot	*d=CreateItem(ItemClassType);
			if(d==NULL){
				return false;
			}
			AlgorithmThreshold	*t=d->CreateThresholdInstance();
			if(t==NULL){
				delete	d;
				return false;
			}
			if(t->Load(f)==false){
				delete	d;
				return false;
			}
			delete	d;
		}
	}
	return true;
}
void	AlgorithmInPagePI::LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		ItemFunc(c,Something);
	}
}

void	AlgorithmInPagePI::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	AlgorithmInPagePI::DeliverTransmitDirectly(GUIDirectMessage *packet)
{
	TransmitDirectly(packet);
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->TransmitDirectly(packet);
	}
}

void	AlgorithmInPagePI::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	N=Data.GetNumber();
	struct	PriorityMapClass	*PriorityMap=new struct	PriorityMapClass[N];
	int	k=0;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),k++){
		PriorityMap[k].Point=c;
		PriorityMap[k].DrawingPriority=0x60000000 | c->GetDrawPriprity(movx ,movy ,ZoomRate ,Attr);
		PriorityMap[k].PriorityCode=0;
		if(c->GetSelected()==true){
			PriorityMap[k].PriorityCode=1;
			PriorityMap[k].DrawingPriority &= ~0x20000000;
		}
		if(c->GetActive()==true){
			PriorityMap[k].PriorityCode=2;
			PriorityMap[k].DrawingPriority &= ~0x40000000;
		}
	}
	QSort(PriorityMap,N,sizeof(struct PriorityMapClass),PriorityMapSortFunc);

	for(int i=0;i<N;i++){
		PriorityMap[i].Point->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	delete	[]PriorityMap;
}
void	AlgorithmInPagePI::DrawMove(int dx ,int dy ,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		c->DrawMove(dx,dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
	MutexTemporaryItem.lock();
	for(ItemPointerList *L=TemporaryItemList.GetFirst();L!=NULL;L=L->GetNext()){
		L->ItemPointer->DrawMoveTemporary(L->Dx,L->Dy,pnt, movx ,movy ,ZoomRate ,Col,Attr);
	}
	MutexTemporaryItem.unlock();
}

bool	AlgorithmInPagePI::DrawResult(ResultInPageRoot *R,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	ResultInPagePI	&Res=*((ResultInPagePI *)R);
	int	Numb=GetItemCount();
	if(DrawResultTableNumb<Numb){
		ResultInItemPI *r=Res.GetResultFirst();
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL && r!=NULL;){
			if(a->GetID()==r->GetItemID()){
				a->DrawResult(r,IData ,PData ,MovX ,MovY ,ZoomRate);
				r=r->GetNext();
				a=a->GetNext();
			}
			else if(a->GetID()<r->GetItemID()){
				a=a->GetNext();
			}
			else{
				r=r->GetNext();
			}
		}
		return true;

		//if(DrawResultATable!=NULL){
		//	delete	[]DrawResultATable;
		//}
		//if(DrawResultRTable!=NULL){
		//	delete	[]DrawResultRTable;
		//}
		//DrawResultATable	=new AlgorithmItemPI*[Numb];
		//DrawResultRTable	=new ResultInItemPI *[Numb];
		//DrawResultTableNumb	=Numb;
		//for(int i=0;i<Numb;i++){
		//	DrawResultATable[i]=NULL;
		//	DrawResultRTable[i]=NULL;
		//}
		//ExecuteInitialAfterEditInfo EInfo;
		//LayersBase	*LBase=GetLayersBase();
		//LBase->MakeExecuteInitialAfterEditInfo(EInfo);
		//LBase->ExecuteInitialAfterEdit(EInfo);
		//return false;
	}
	else{
		int	N=0;
		ResultInItemPI	*r=Res.GetResultFirst();
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL && r!=NULL;a=a->GetNext(),r=r->GetNext(),N++){
			DrawResultATable[N]=a;
			DrawResultRTable[N]=r;
		}

		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
			for(int i=0;i<N;i++){
				AlgorithmItemPI	*a=DrawResultATable[i];
				ResultInItemPI	*r=DrawResultRTable[i];
				if(a!=NULL && r!=NULL){
					a->DrawResult(r,IData ,PData ,MovX ,MovY ,ZoomRate);
				}
			}
		//}
	}
	return true;
}
bool	AlgorithmInPagePI::DrawResultItem(ResultInPageRoot *R,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)
{
	ResultInPagePI	&Res=*((ResultInPagePI *)R);
	int	Numb=GetItemCount();
	if(DrawResultTableNumb<Numb){
		ResultInItemPI *r=Res.GetResultFirst();
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL && r!=NULL;){
			if(a->GetID()==r->GetItemID()){
				a->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate ,OnlyNG);
				r=r->GetNext();
				a=a->GetNext();
			}
			else if(a->GetID()<r->GetItemID()){
				a=a->GetNext();
			}
			else{
				r=r->GetNext();
			}
		}
		return true;

		//if(DrawResultATable!=NULL){
		//	delete	[]DrawResultATable;
		//}
		//if(DrawResultRTable!=NULL){
		//	delete	[]DrawResultRTable;
		//}
		//DrawResultATable	=new AlgorithmItemPI*[Numb];
		//DrawResultRTable	=new ResultInItemPI *[Numb];
		//DrawResultTableNumb	=Numb;
		//for(int i=0;i<Numb;i++){
		//	DrawResultATable[i]=NULL;
		//	DrawResultRTable[i]=NULL;
		//}
		//ExecuteInitialAfterEditInfo EInfo;
		//LayersBase	*LBase=GetLayersBase();
		//LBase->MakeExecuteInitialAfterEditInfo(EInfo);
		//LBase->ExecuteInitialAfterEdit(EInfo);
		//return false;
	}
	int	N=0;
	ResultInItemPI	*r=Res.GetResultFirst();
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL && r!=NULL;a=a->GetNext(),r=r->GetNext(),N++){
		DrawResultATable[N]=a;
		DrawResultRTable[N]=r;
	}

	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int i=0;i<N;i++){
			AlgorithmItemPI	*a=DrawResultATable[i];
			ResultInItemPI	*r=DrawResultRTable[i];
			if(a!=NULL && r!=NULL){
				a->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate ,OnlyNG);
			}
		}
	//}
	return true;
}
void	AlgorithmInPagePI::DrawMonoBitmap(BYTE **BmpPoint)
{
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->DrawMonoBitmap(BmpPoint);
	}
}
void	AlgorithmInPagePI::DrawItems(QImage &IData ,QPainter &PData ,IntList &LayerList ,int movx ,int movy ,double ZoomRate,DWORD DrawType)
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)){
			c->Draw(IData, movx ,movy ,ZoomRate ,NULL);
		}
		if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)){
			c->Draw(IData, movx ,movy ,ZoomRate ,NULL);
		}
	}
}
void	AlgorithmInPagePI::DrawResultItem(ResultInPageRoot *R,QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)
{
	if(R!=NULL){
		ResultInPagePI	&Res=*((ResultInPagePI *)R);
		int	N=0;
		int	Numb=GetItemCount();
		for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),N++){
			if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)
			&& N<Numb && N<Res.GetItemCount()){
				ResultInItemPI		*r=Res.GetResultItem(N);
				c->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
			if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)
			&& N<Numb && N<Res.GetItemCount()){
				ResultInItemPI		*r=Res.GetResultItem(N);
				c->DrawResultItem(r,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
		}
	}
	else{
		for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetSelected()==true && ((DrawType&DrawType_Selected)!=0)){
				c->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
			if(c->GetActive()==true && ((DrawType&DrawType_Active)!=0)){
				c->DrawResultItem(NULL,IData ,PData ,MovX ,MovY ,ZoomRate,false);
			}
		}
	}
}


AlgorithmItemPI	*AlgorithmInPagePI::GetItem(int localX ,int localY)	const
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->IsInclude(localX ,localY)==true){
			return c;
		}
	}
	return NULL;
}

AlgorithmItemRoot	*AlgorithmInPagePI::SearchIDItem(int itemID)	const
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetID()==itemID){
			return(c);
		}
	}
	return(NULL);
}
AlgorithmItemRoot	*AlgorithmInPagePI::SearchItemByName(const QString &ItemName)	const
{
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetItemName()==ItemName){
			return(c);
		}
	}
	return(NULL);
}
void	AlgorithmInPagePI::FastSearchIDItemStart(void)
{
	if(ItemDimPointer!=NULL){
		delete	[]ItemDimPointer;
	}
	ItemDimPointerNumb=Data.GetCount();
	ItemDimPointer=new AlgorithmItemRoot *[ItemDimPointerNumb];
	int	i=0;
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext(),i++){
		ItemDimPointer[i]=c;
	}
	SortDimPointer();
}
bool	AlgorithmInPagePI::AppendItem(AlgorithmItemRoot *item)
{
	((AlgorithmItemPI *)item)->SetParent(this);
	((AlgorithmItemPI *)item)->ItemID=GetIncStartItemID();
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPI *)item);
	//item->GetArea().SetLimit(GetDotPerLine(),GetMaxLines());
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	item->SetEdited(true);
	Changed=true;
	CalcDone=false;
	return true;
}
bool	AlgorithmInPagePI::AppendItem(int Layer ,AlgorithmItemRoot *item)
{
	return AppendItem(item);
}
bool	AlgorithmInPagePI::AppendItemFromLoad(AlgorithmItemRoot *item)
{
	((AlgorithmItemPI *)item)->SetParent(this);
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPI *)item);
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	Changed=true;
	CalcDone=false;
	return true;
}

void	AlgorithmInPagePI::RemoveItem(AlgorithmItemRoot *item)
{
	Data.RemoveList((AlgorithmItemPI *)item);
	Changed=true;
	CalcDone =false;
}

bool		AlgorithmInPagePI::AppendItems(AlgorithmItemPointerListContainer &items)
{
	for(AlgorithmItemPointerList *L=items.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*Item=L->GetItem();
		AppendItem(Item);
		Changed=true;
	}
	return true;
}

bool		AlgorithmInPagePI::RemoveItems(AlgorithmItemPointerListContainer &items)
{
	for(AlgorithmItemPointerList *L=items.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*Item=L->GetItem();
		RemoveItem(Item);
		delete	Item;
		L->SetPointer(NULL);
		Changed=true;
	}
	return true;
}
void	AlgorithmInPagePI::RemoveAllDatasByManual(bool CreatedManually)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPI	*NextP=p->GetNext();
		if(p->GetManualCreated()==CreatedManually){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
void	AlgorithmInPagePI::RemoveAllDatasWithoutLocked(void)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPI	*NextP=p->GetNext();
		if(p->GetEditLocked()==false){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
void	AlgorithmInPagePI::RemoveAllDatasWithoutManual(void)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;){
		AlgorithmItemPI	*NextP=p->GetNext();
		if(p->GetManualCreated()==false){
			RemoveItem(p);
			delete	p;
			Changed=true;
		}
		p=NextP;
	}
}
bool	AlgorithmInPagePI::AppendItem(AlgorithmItemRoot *item ,int64 itemID)
{
	((AlgorithmItemPI *)item)->Parent=this;
	((AlgorithmItemPI *)item)->ItemID=itemID;
	item->SetOrigin(item->GetParentBase());
	Data.AppendList((AlgorithmItemPI *)item);
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	Changed=true;
	CalcDone =false;
	return true;
}

void	AlgorithmInPagePI::RemoveAllDatas(void)
{
	Data.RemoveAll();
	ClearStartItemID();
	Changed=true;
	CalcDone =false;
}

void	AlgorithmInPagePI::InsertItem(AlgorithmItemRoot *item,AlgorithmItemRoot *Key)
{
	((AlgorithmItemPI *)item)->SetParent(this);
	((AlgorithmItemPI *)item)->ItemID=GetIncStartItemID();
	item->SetOrigin(item->GetParentBase());
	Data.InsertLater((AlgorithmItemPI *)Key,(AlgorithmItemPI *)item);
	//item->GetArea().SetLimit(GetDotPerLine(),GetMaxLines());
	if(GetParamGlobal()->MakeHistgramData==true){	// && item->GetModeReferedAttr()==false){
		item->GetThresholdBaseWritable()->RegistHist();
	}
	item->SetMakeHistgramData(GetParamGlobal()->MakeHistgramData);
	Changed=true;
	CalcDone=false;
}
int64		AlgorithmInPagePI::GetMaxItemID(void)	const
{
	int64	MaxItemID=0;
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		if(p->GetID()>MaxItemID){
			MaxItemID=p->GetID();
		}
	}
	return MaxItemID;
}

void	AlgorithmInPagePI::InitialThreadBufferForExecute(void)
{
	int	iCalcThreadDataCount=GetItemCount();
	int	N=(iCalcThreadDataCount+ThreadNumb-1)/ThreadNumb;
	
	if(CalcThreadDataCount!=iCalcThreadDataCount){
		CalcThreadDataCount=iCalcThreadDataCount;
		if(CalcThreadDim!=NULL){
			delete	[]CalcThreadDim;
		}
		CalcThreadDim	=new OMPAlgorithmItemStruct[ThreadNumb];
		for(int i=0;i<ThreadNumb;i++){
			CalcThreadDim[i].Alloc(this ,i,N);
		}
	}
}
AlgorithmItemRoot	*AlgorithmInPagePI::GetItemData(int layer ,int itemID)	const
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		if(p->GetID()==itemID){
			return p;
		}
	}
	return NULL;
}
AlgorithmItemRoot	*AlgorithmInPagePI::FindFastItemData(int layer ,int itemID)	const
{
	return SearchIDItem(itemID);
}

void	AlgorithmInPagePI::ClearResult(void)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		p->ClearResult();
	}
}

ExeResult	AlgorithmInPagePI::ExecuteInitialAfterEditPrev(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEditPrev();
	FastSearchIDItemStart();

	ExeResult	Ret=FuncExecuteInitialAfterEditPrev(ExeID ,R,EInfo);

	FastSearchIDItemStart();
	EndMilisecExecuteInitialAfterEditPrev();
	if(Ret==_ER_true){
		CalcDone =false;
	}
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteInitialAfterEditPrev(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEditPrev(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInPagePI *Res=(ResultInPagePI *)R;

	Res->Alloc(this);

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase	*Ph=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(GetPage()));
		if(Rp!=NULL){
			ResultInItemPI		*r=Rp->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				c->SetCurrentResult(r);
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEditPrev==true){
		AlgorithmItemPI	*CDim[10000];
		AlgorithmItemPI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			ResultInItemPI	*r=Res->GetResultFirst();
			if(r!=NULL){
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,r,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}
			else{
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEditPrev(ExeID ,0,NULL,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}

ExeResult	AlgorithmInPagePI::ExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEdit();
	FastSearchIDItemStart();

	ExeResult	Ret=FuncExecuteInitialAfterEdit(ExeID ,R,EInfo);

	FastSearchIDItemStart();
	EndMilisecExecuteInitialAfterEdit();
	if(Ret==_ER_true){
		CalcDone =false;
	}
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEdit(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInPagePI *Res=(ResultInPagePI *)R;

	Res->Alloc(this);

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase	*Ph=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(GetPage()));
		if(Rp!=NULL){
			ResultInItemPI		*r=Rp->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				c->SetCurrentResult(r);
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEdit==true){
		AlgorithmItemPI	*CDim[10000];
		AlgorithmItemPI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			ResultInItemPI	*r=Res->GetResultFirst();
			if(r!=NULL){
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,r,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}
			else{
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEdit(ExeID ,0,NULL,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}
		}while(RetryMode==true);
	}
	if(GetParamGlobal()->MakeHistgramData==true){
		for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetMakeHistgramData()==false){	// && c->GetModeReferedAttr()==false){
				c->GetThresholdBaseWritable()->RegistHist();
				c->SetMakeHistgramData(true);
			}
		}
	}
	return Ret;
}

ExeResult	AlgorithmInPagePI::ExecuteInitialAfterEditPost(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	StartMilisecExecuteInitialAfterEditPost();
	FastSearchIDItemStart();

	ExeResult	Ret=FuncExecuteInitialAfterEditPost(ExeID ,R,EInfo);

	FastSearchIDItemStart();
	EndMilisecExecuteInitialAfterEditPost();
	if(Ret==_ER_true){
		CalcDone =false;
	}
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteInitialAfterEditPost(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteInitialAfterEditPost(ExeID ,R,EInfo);
	if(Ret!=_ER_true){
		return Ret;
	}

	InitialThreadBufferForExecute();
	ResultInPagePI *Res=(ResultInPagePI *)R;

	Res->Alloc(this);

	FastSearchIDItemStart();
	ResultInspection	*DRes=GetLayersBase()->GetCurrentResultForDraw();
	if(DRes!=NULL){
		ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(GetParentBase());
		ResultBasePhase	*Ph=rbase->GetPageDataPhase(GetPhaseCode());
		ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(GetPage()));
		if(Rp!=NULL){
			ResultInItemPI		*r=Rp->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				c->SetCurrentResult(r);
			}
		}
	}

	if(GetParamGlobal()->CalcSingleThread==false && Data.GetCount()>4 && ModeParallel.ModeParallelExecuteInitialAfterEditPost==true){
		AlgorithmItemPI	*CDim[10000];
		AlgorithmItemPI	**C=NULL;
		int	n;
		if(Data.GetCount()<sizeof(CDim)/sizeof(CDim[0])){
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				CDim[n]=t;
			}
			C=CDim;
		}
		else{
			C=new AlgorithmItemPI *[Data.GetCount()];
			n=0;
			for(AlgorithmItemPI	*t=Data.GetFirst();t!=NULL;t=t->GetNext(),n++){
				C[n]=t;
			}
		}

		volatile	bool	RetryMode;
		do{
			RetryMode=false;

			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<n;i++){
					AlgorithmItemPI	*c=C[i];
					ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,c->GetCurrentResult(),EInfo);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
		if(C!=CDim){
			delete	[]C;
		}
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			ResultInItemPI	*r=Res->GetResultFirst();
			if(r!=NULL){
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,r,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}
			else{
				for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
					ExeResult	RR=c->ExecuteInitialAfterEditPost(ExeID ,0,NULL,EInfo);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else if(RR!=_ER_true){
						Ret=RR;
					}
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}

ExeResult	AlgorithmInPagePI::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecuteStartByInspection();
	ExeResult	Ret=FuncExecuteStartByInspection(ExeID ,R);
	EndMilisecExecuteStartByInspection();
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteStartByInspection(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteStartByInspection(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteStartByInspection==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteStartByInspection(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecuteStartByInspection(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	
	return Ret;
}

ExeResult	AlgorithmInPagePI::ExecuteCaptured(int ExeID ,ResultInPageRoot *R,ListPhasePageLayerPack &CapturedList)
{
	StartMilisecExecuteCaptured();
	ExeResult	Ret=FuncExecuteCaptured	(ExeID ,R,CapturedList);
	EndMilisecExecuteCaptured();
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteCaptured(int ExeID ,ResultInPageRoot *R,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteCaptured(ExeID ,R,CapturedList);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePreAlignment==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteCaptured(ExeID,CapturedList);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecuteCaptured(ExeID ,0,r,CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}

ExeResult	AlgorithmInPagePI::ExecutePreAlignment	(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecutePreAlignment();
	ExeResult	Ret=FuncExecutePreAlignment	(ExeID ,R);
	EndMilisecExecutePreAlignment();
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecutePreAlignment	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreAlignment(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePreAlignment==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreAlignment(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecutePreAlignment(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecuteAlignment		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecuteAlignment();
	ExeResult	Ret=FuncExecuteAlignment(ExeID ,R);
	EndMilisecExecuteAlignment();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecuteAlignment		(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteAlignment(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteAlignment==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteAlignment(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecuteAlignment(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecutePreProcessing		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecutePreProcessing();
	ExeResult	Ret=FuncExecutePreProcessing	(ExeID ,R);
	EndMilisecExecutePreProcessing();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecutePreProcessing	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreProcessing(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePreProcessing==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecutePreProcessing(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else if(RR!=_ER_true){
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecuteProcessing		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecuteProcessing();
	ExeResult	Ret=FuncExecuteProcessing	(ExeID ,R);
	EndMilisecExecuteProcessing();
	return Ret;
}

ExeResult	AlgorithmInPagePI::FuncExecuteProcessing	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteProcessing(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	if(GetParamGlobal()->KeepFilteredImage==false){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetDataInLayer(layer)->CreateAndCopyTempTargetBuff();
		}
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	int		MaxInspectMilisec=Parent->GetParamGlobal()->MaxInspectMilisec;
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecuteProcessing==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else if(RR!=_ER_true){
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();

		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				DWORD	NowTime=GetComputerMiliSec();
				if(GetNGCounter()<=GetParamGlobal()->MaxNGCountsPerCam
				&& NowTime-StartMilisec<=MaxInspectMilisec
				&& c->IsEffective()==true){
					r->SetAlgorithmItem(c);
					ExeResult	RR=c->ExecuteProcessing(ExeID ,0,r);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
					if(c->GetInvertLogic()==true){
						if(r->GetError()==1){
							r->SetError(2);
						}
						else if(r->GetError()>=2){
							r->SetError(1);
						}
						if(r->GetPosListFirst()==NULL){
							int	cx,cy;
							c->GetCenter(cx,cy);
							r->GetPosList().AppendList(new ResultPosList(cx,cy));
						}
					}
					IncrementNGCounterWithMutex(r->GetError());
				}
			}
		}while(RetryMode==true);
	}
	if(GetParamGlobal()->KeepFilteredImage==false){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetDataInLayer(layer)->ReleaseTempTargetBuff();
		}
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecuteProcessingRevived		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecuteProcessingRevived();
	ExeResult	Ret=FuncExecuteProcessingRevived(ExeID ,R);
	EndMilisecExecuteProcessingRevived();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecuteProcessingRevived	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteProcessingRevived(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	if(GetParamGlobal()->KeepFilteredImage==false){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetDataInLayer(layer)->CreateAndCopyTempTargetBuff();
		}
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}

	//‰æ‘œ‚ðØ‚è‘Ö‚¦‚é‚½‚ßAOpenMP‚É‚Å‚«‚È‚¢
	DWORD	StartMilisec=GetLayersBase()->GetStartInspectionTimeMilisec();
	int		MaxInspectMilisec=GetParamGlobal()->MaxInspectMilisec;

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecutePostProcessing		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecutePostProcessing();
	ExeResult	Ret=FuncExecutePostProcessing	(ExeID ,R);
	EndMilisecExecutePostProcessing();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecutePostProcessing	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePostProcessing(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	ResultInPagePI *Res=(ResultInPagePI *)R;
	if(Res->GetResultCount()<GetItemCount()){
		Res->Alloc(this);
	}
	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>=MIN_COUNT_ForTHREAD && ThreadNumb>=MIN_COUNT_ForTHREAD && ModeParallel.ModeParallelExecutePostProcessing==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePostProcessing(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecutePostProcessing(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecutePreScanning		(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecutePreScanning();
	ExeResult	Ret=FuncExecutePreScanning	(ExeID ,R);
	EndMilisecExecutePreScanning();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecutePreScanning	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePreScanning(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInPagePI *Res=(ResultInPagePI *)R;

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecutePreScanning==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePreScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecutePreScanning(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecuteScanning	(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecuteScanning();
	ExeResult	Ret=FuncExecuteScanning	(ExeID ,R);
	EndMilisecExecuteScanning();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecuteScanning	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecuteScanning(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInPagePI *Res=(ResultInPagePI *)R;

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecuteScanning==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecuteScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecuteScanning(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}
ExeResult	AlgorithmInPagePI::ExecutePostScanning	(int ExeID ,ResultInPageRoot *R)
{
	StartMilisecExecutePostScanning();
	ExeResult	Ret=FuncExecutePostScanning	(ExeID ,R);
	EndMilisecExecutePostScanning();
	return Ret;
}
ExeResult	AlgorithmInPagePI::FuncExecutePostScanning	(int ExeID ,ResultInPageRoot *R)
{
	ExeResult	Ret=AlgorithmInPageRoot::ExecutePostScanning(ExeID ,R);
	if(Ret!=_ER_true){
		return Ret;
	}

	if(CalcThreadDim==NULL || CalcThreadDataCount!=GetItemCount()){
		InitialThreadBufferForExecute();
	}
	ResultInPagePI *Res=(ResultInPagePI *)R;

	int	n=0;
	ResultInItemPI	*r=Res->GetResultFirst();
	for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL;c=c->GetNext()){
		int	k=n/ThreadNumb;
		int	h=n%ThreadNumb;
		CalcThreadDim[h].Set(k,c,r);
		if(r!=NULL){
			r=r->GetNext();
		}
		n++;
	}
	if(GetParamGlobal()->CalcSingleThread==false && n>1 && ThreadNumb>1 && ModeParallel.ModeParallelExecutePostScanning==true){
		volatile	bool	RetryMode;
		do{
			RetryMode=false;
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int i=0;i<ThreadNumb;i++){
					ExeResult	RR=CalcThreadDim[i].ExecutePostScanning(ExeID);
					if(RR==_ER_ReqRetryLater){
						#pragma omp critical
						{
							RetryMode=true;
						}
					}
					else{
						#pragma omp critical
						{
							Ret=RR;
						}
					}
				}
			}
		}while(RetryMode==true);
	}
	else{
		bool	RetryMode;
		do{
			RetryMode=false;
			r=Res->GetResultFirst();
			for(AlgorithmItemPI *c=Data.GetFirst();c!=NULL && r!=NULL;c=c->GetNext(),r=r->GetNext()){
				ExeResult	RR=c->ExecutePostScanning(ExeID ,0,r);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}

	return Ret;
}

void	AlgorithmInPagePI::MoveForAlignment(void)
{
	AlgorithmBase	*ABase=GetParentBase();
	if(ABase->EnableMoveForAlignment==true){
		for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			L->MoveForAlignment();
		}
		RemoveInvalidItems();
	}
}

void	AlgorithmInPagePI::RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->RefreshByMap(Mode,Map);
	}
}

void	AlgorithmInPagePI::RefreshByMap(int layer ,ReflectionMode Mode,ConstMapBufferListContainer &Map)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->RefreshByMap(Mode,Map);
	}
}

void	AlgorithmInPagePI::ReleaseAllSelectedItem(void)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->SetSelected(false);
	}
}

void	AlgorithmInPagePI::GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)
{
	MatrixBuffClear(Dst ,0,XByte,YLen);
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->IsEffective()==true){
			a->GetArea().MakeBitData(Dst,XLen,YLen);
		}
		else{
			a->GetArea().MakeNotBitData(Dst,XLen,YLen);
		}
	}
}

void	AlgorithmInPagePI::SelectAll(const IntList &LayerList)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		L->SetSelected(true);
	}
}
void	AlgorithmInPagePI::SelectLocked(const IntList &LayerList)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==true){
			L->SetSelected(true);
		}
		else{
			L->SetSelected(false);
		}
	}
}
void	AlgorithmInPagePI::SelectLibs(SelectLibListContainer &SelectedList)
{
	ReleaseAllSelectedItem();
	for(SelectLibList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
		for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==a->LibID){
				L->SetSelected(true);
			}
		}
	}
}

void	AlgorithmInPagePI::RemoveInvalidItems(void)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPI *NextL=L->GetNext();
		if(L->IsValid()==false){
			RemoveItem(L);
		}
		L=NextL;
	}
}

void	AlgorithmInPagePI::SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode	,const IntList &LayerList)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->IsOriginTypeSelection(SelectMode)==true){
			L->SetSelected(true);
		}
		else{
			L->SetSelected(false);
		}
	}
}
void	AlgorithmInPagePI::SelectArea(FlexArea &localArea,bool MultiSelect)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetVisible()==true){
			if(L->IsCrossed(&localArea)==true){
				L->SetSelected(true);
			}
			else if(L->GetVector()!=NULL){
				if(L->GetVector()->CheckOverlap(localArea)==true){
					L->SetSelected(true);
				}
			}
		}
	}
}
void	AlgorithmInPagePI::SelectPoint(int localX, int localY)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetVisible()==true){
			if(L->GetArea().IsInclude(localX, localY)==true){
				L->SetSelected(true);
			}
			else if(L->GetVector()!=NULL){
				if(L->GetVector()->GetDistance(localX,localY)<3){
					L->SetSelected(true);
				}
			}
		}
	}
}
class	IDXYList : public NPList<IDXYList>
{
public:
	int	ID,Cx,Cy;
	IDXYList(void){}
	IDXYList(int id ,int cx,int cy):ID(id),Cx(cx),Cy(cy){}
};

void	AlgorithmInPagePI::CutArea(FlexArea &localArea ,const IntList &LayerList,bool MultiSelect,const QByteArray &Something)
{
	int	N=GetItemCount();
	AlgorithmItemPI **Pointer=new AlgorithmItemPI *[N];
	int	k=0;
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL && k<N;L=L->GetNext(),k++){
		Pointer[k]=L;
	}
	bool	FoundSelected=false;
	#pragma omp parallel                             
	{                                                
		#pragma omp for schedule(dynamic)
		for(int i=0;i<N;i++){
			AlgorithmItemPI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				FoundSelected=true;
			}
		}
	}
	NPListPack<IDXYList>	ChangesIDList;
	if(FoundSelected==false){
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for schedule(dynamic)
			for(int i=0;i<N;i++){
				AlgorithmItemPI *L=Pointer[i];
				bool	_Changed;
				int	cx,cy;
				L->GetMultiSelectOrign(cx,cy);
				L->CutArea(localArea,_Changed);
				if(_Changed==true){
					Changed=true;
					CalcDone=false;

					if(L->GetSelected()==true){
						#pragma omp critical
						{
							ChangesIDList.AppendList(new IDXYList(i,cx,cy));
						}
					}
				}
			}
		//}
	}
	else{
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for schedule(dynamic)
			for(int i=0;i<N;i++){
				AlgorithmItemPI *L=Pointer[i];
				if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
					bool	_Changed;
					int	cx,cy;
					L->GetMultiSelectOrign(cx,cy);
					L->CutArea(localArea,_Changed);
					if(_Changed==true){
						Changed=true;
						CalcDone=false;

						if(L->GetSelected()==true){
							#pragma omp critical
							{
								ChangesIDList.AppendList(new IDXYList(i,cx,cy));
							}
						}
					}
				}
			}
		//}
	}
	if(MultiSelect==true){
		for(IDXYList *c=ChangesIDList.GetFirst();c!=NULL;c=c->GetNext()){
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for schedule(dynamic)
				for(int i=0;i<N;i++){
					AlgorithmItemPI *L=Pointer[i];
					if(L->GetSelected()==true){
						bool	Found=false;
						for(IDXYList *d=ChangesIDList.GetFirst();d!=NULL;d=d->GetNext()){
							if(d->ID==i){
								Found=true;
								break;
							}
						}
						if(Found==false){
							int	cx,cy;
							L->GetMultiSelectOrign(cx,cy);
							FlexArea	A=localArea;
							A.MoveToNoClip(cx-c->Cx,cy-c->Cy);

							bool	_Changed;
							L->CutArea(A,_Changed);
							if(_Changed==true){
								Changed=true;
								CalcDone=false;
							}
						}
					}
				}
			//}
		}
	}
	

	delete	[]Pointer;

	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPI *NextL=L->GetNext();
		if(L->IsNull()==true){
			RemoveItem(L);
		}
		L=NextL;
	}
}

void	AlgorithmInPagePI::SeparateItems(FlexArea &localArea ,const IntList &LayerList)
{
	int	N=GetItemCount();
	AlgorithmItemPI **Pointer=new AlgorithmItemPI *[N];
	int	k=0;
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL && k<N;L=L->GetNext(),k++){
		Pointer[k]=L;
	}
	bool	FoundSelected=false;
	#pragma omp parallel                             
	{                                                
		#pragma omp for schedule(dynamic)
		for(int i=0;i<N;i++){
			AlgorithmItemPI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				FoundSelected=true;
			}
		}
	}
	AlgorithmItemPointerListContainer	AddedItemsContainer;
	if(FoundSelected==false){
		for(int i=0;i<N;i++){
			AlgorithmItemPI *L=Pointer[i];
			if(L->GetArea().CheckOverlap(&localArea)==true){
				AlgorithmItemRoot	*v=L->SeparateItem(localArea);
				if(v!=NULL){
					AddedItemsContainer.Add(v);
				}
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			AlgorithmItemPI *L=Pointer[i];
			if(L->GetSelected()==true && L->GetArea().CheckOverlap(&localArea)==true){
				AlgorithmItemRoot	*v=L->SeparateItem(localArea);
				if(v!=NULL){
					AddedItemsContainer.Add(v);
				}
			}
		}
	}
	for(AlgorithmItemPointerList *p=AddedItemsContainer.GetFirst();p!=NULL;p=p->GetNext()){
		AppendItem(0,p->GetItem());
	}

	delete	[]Pointer;
}

void	AlgorithmInPagePI::RegistArea(FlexArea &localArea ,const IntList &LayerList)
{
}

void	AlgorithmInPagePI::DeleteSelectedItems(const IntList &LayerList)
{
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoDeleteSelectedItems);
	int32	ItemCount=0;
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true && L->GetEditLocked()==false && L->GetVisible()==true){
			ItemCount++;
		}
	}
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;){
		AlgorithmItemPI *NextL=L->GetNext();
		if(L->GetSelected()==true && L->GetEditLocked()==false && L->GetVisible()==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			L->Save(UndoPointer->GetWritePointer());

			SetChanged();
			RemoveItem(L);
			delete	L;
			Changed=true;
			CalcDone =false;
		}
		L=NextL;
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInPagePI::GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		ItemPointers.Add(item);
	}
}
void	AlgorithmInPagePI::EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(LibIDs.IsInclude(item->GetLibID())==true){
			ItemPointers.Add(item);
		}
	}
}
void	AlgorithmInPagePI::EnumItemsByLib(int layer ,IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)
{
	EnumItemsByLib(LibIDs ,ItemPointers);
}
void	AlgorithmInPagePI::EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		ItemPointers.Add(item);
	}
}
void	AlgorithmInPagePI::EnumAllItems(int layer,AlgorithmItemPointerListContainer &ItemPointers)
{
	EnumAllItems(ItemPointers);
}
void	AlgorithmInPagePI::GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			ItemPointers.Add(item);
		}
	}
}
void	AlgorithmInPagePI::EnumSelectedItems(ListPageLayerIDPack &Items)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			Items.AppendList(new ListPageLayerID(GetPage(),0,item->GetID()));
		}
	}
}

void	AlgorithmInPagePI::AppendItemsInPage(int Layer,AlgorithmItemPointerListContainer &SrcPointers)
{
	for(AlgorithmItemPointerList *L=SrcPointers.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*Item=L->GetItem();
		AppendItem(Item);
	}
}
void	AlgorithmInPagePI::RemoveItemsInPage(int Layer,IntList &IDList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;){
		AlgorithmItemPI *NextP=item->GetNext();
		if(IDList.IsInclude(item->GetID())==true){
			RemoveItem(item);
			delete	item;
		}
		item=NextP;
	}
}

void	AlgorithmInPagePI::SwitchThresholdLevel(int OldLevel ,int NewLevel)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SwitchThresholdLevel(OldLevel ,NewLevel);
	}
}
void	AlgorithmInPagePI::CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->CopyThresholdLevel(SourceLevelID ,DestLevelID);
	}
}

void	AlgorithmInPagePI::UndoDeleteSelectedItems(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}

	for(int i=0;i<ItemCount;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return;
		}
		AlgorithmItemRoot	*L=CreateItem(ItemClassType);
		if(L->Load(f,GetLayersBase())==false){
			delete	L;
			return;
		}
		AppendItem(L);
	}
	Changed=true;
	CalcDone=false;	
}

void	AlgorithmInPagePI::LockSelectedItems(const IntList &LayerList)
{
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoLockSelectedItems);
	int32	ItemCount=GetItemCount();
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		int32	ItemID=L->GetID();
		bool	Locked=L->GetEditLocked();
		::Save(UndoPointer->GetWritePointer(),ItemID);
		::Save(UndoPointer->GetWritePointer(),Locked);

		if(L->GetSelected()==true){
			L->SetEditLocked(true);
		}
		else{
			L->SetEditLocked(false);
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInPagePI::UndoLockSelectedItems(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}
	FastSearchIDItemStart();
	for(int i=0;i<ItemCount;i++){
		int32	ItemID;
		bool	Locked;
		if(::Load(f,ItemID)==false){
			return;
		}
		if(::Load(f,Locked)==false){
			return;
		}
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			L->SetEditLocked(Locked);
		}
	}
}

void	AlgorithmInPagePI::UnlockAll(const IntList &LayerList)
{
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoUnlockAll);
	int32	ItemCount=GetItemCount();
	::Save(UndoPointer->GetWritePointer(),ItemCount);

	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		int32	ItemID=L->GetID();
		bool	Locked=L->GetEditLocked();
		::Save(UndoPointer->GetWritePointer(),ItemID);
		::Save(UndoPointer->GetWritePointer(),Locked);

		L->SetEditLocked(false);
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}

void	AlgorithmInPagePI::UndoUnlockAll(QIODevice *f)
{
	int32	ItemCount;
	if(::Load(f,ItemCount)==false){
		return;
	}
	FastSearchIDItemStart();
	for(int i=0;i<ItemCount;i++){
		int32	ItemID;
		bool	Locked;
		if(::Load(f,ItemID)==false){
			return;
		}
		if(::Load(f,Locked)==false){
			return;
		}
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			L->SetEditLocked(Locked);
		}
	}
}


void	AlgorithmInPagePI::BindSelectedItems(const IntList &LayerList)
{
	AlgorithmItemPI *Seed=NULL;
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			Seed=L;
			break;
		}
	}
	if(Seed!=NULL){
		UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoBindSelectedItems);
		int32	ItemID=Seed->GetID();
		::Save(UndoPointer->GetWritePointer(),ItemID);
		Seed->Save(UndoPointer->GetWritePointer());

		int32	SelectedCount=0;
		for(AlgorithmItemPI *L=Seed->GetNext();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				SelectedCount++;
			}
		}
		::Save(UndoPointer->GetWritePointer(),SelectedCount);

		for(AlgorithmItemPI *L=Seed->GetNext();L!=NULL;){
			AlgorithmItemPI *NextL=L->GetNext();
			if(L->GetSelected()==true){
				int32	ItemClassType=L->GetItemClassType();
				::Save(UndoPointer->GetWritePointer(),ItemClassType);
				L->Save(UndoPointer->GetWritePointer());
			
				FlexArea	A=Seed->GetArea();
				A+=L->GetArea();
				Seed->SetArea(A);
				RemoveItem(L);
				Changed=true;
				CalcDone =false;
			}
			L=NextL;	
		}
	}
}

void	AlgorithmInPagePI::UndoBindSelectedItems(QIODevice *f)
{
	int32	ItemID;
	if(::Load(f,ItemID)==false){
		return;
	}
	AlgorithmItemRoot	*L=SearchIDItem(ItemID);
	if(L!=NULL){
		if(L->Load(f,GetLayersBase())==false){
			return;
		}
		int32	SelectedCount;
		if(::Load(f,SelectedCount)==false){
			return;
		}

		for(int i=0;i<SelectedCount;i++){
			int32	ItemClassType;
			if(::Load(f,ItemClassType)==false){
				return;
			}
			AlgorithmItemRoot	*L=CreateItem(ItemClassType);
			if(L->Load(f,GetLayersBase())==false){
				delete	L;
				return;
			}
			AppendItem(L);
		}
		Changed=true;
		CalcDone=false;
	}
}

void	AlgorithmInPagePI::Activate(int localX ,int localY ,IntList &LayerList,ListLayerAndIDPack &RetItem)
{
	int	Numb=GetItemCount();
	AlgorithmItemPI **ADim=new AlgorithmItemPI *[Numb];
	int	k=0;
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->IsInclude(localX,localY)==true){
				ADim[i]->SetActive(true);
			}
			else{
				ADim[i]->SetActive(false);
			}
		}
	}
	for(int i=0;i<Numb;i++){
		if(ADim[i]->GetActive()==true){
			RetItem.AppendList(new ListLayerAndID(0,ADim[i]->GetID()));
		}
	}
	delete	[]ADim;
}
void	AlgorithmInPagePI::Inactivate(void)
{
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->SetActive(false);
	}
}
void	AlgorithmInPagePI::Activate(int Layer ,int ItemID)
{
	int	Numb=GetItemCount();
	AlgorithmItemPI **ADim=new AlgorithmItemPI *[Numb];
	int	k=0;
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->GetID()==ItemID){
				ADim[i]->SetActive(true);
			}
			else{
				ADim[i]->SetActive(false);
			}
		}
	}
	delete	[]ADim;
}

void	AlgorithmInPagePI::AddActivate(int Layer ,int ItemID)
{
	int	Numb=GetItemCount();
	AlgorithmItemPI **ADim=new AlgorithmItemPI *[Numb];
	int	k=0;
	for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext(),k++){
		ADim[k]=a;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<Numb;i++){
			if(ADim[i]->GetID()==ItemID){
				ADim[i]->SetActive(true);
			}
		}
	}
	delete	[]ADim;
}
void	AlgorithmInPagePI::MakeIndependentItems(bool SubResultMoving, ResultInPageRoot *RPage,int localX ,int localY,AlgorithmItemIndependentPack &AData)
{
	static	bool	Error=false;
	static	int		ErrorID=8517;

	ResultInPagePI	*RP=dynamic_cast<ResultInPagePI *>(RPage);
	if(RP!=NULL){
		if(RP->GetItemCount()<0){
			RP->Alloc(this);
		}
		FastSearchIDItemStart();
		RP->SortResultDimPointer();

		for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
			ResultInItemRoot	*RItem=NULL;
			if(L->GetID()==ErrorID){
				Error=false;
			}
			if(SubResultMoving==true && RP!=NULL){
				RItem=RP->FastSearchIDItem(0,L->GetID());
			}
			if(RItem!=NULL && RItem->GetError()==0x8080){
				Error=true;
				return;
			}
			if(RItem!=NULL && RItem->GetPosList().IsValid()==false){
				Error=true;
				return;
			}
			double	RetDistance;
			if((RItem!=NULL && L->IsInclude( localX-(RItem->GetAlignedX()+RItem->GetItemSearchedX())
											,localY-(RItem->GetAlignedY()+RItem->GetItemSearchedY()))==true)
			|| (RItem!=NULL && L->GetVector()!=NULL &&  L->GetVector()->GetDistance( localX-(RItem->GetAlignedX()+RItem->GetItemSearchedX())
																					,localY-(RItem->GetAlignedY()+RItem->GetItemSearchedY()))<10)
			|| (RItem!=NULL && RItem->GetDistanceVector	(localX,localY,RetDistance)==true && RetDistance<10)
			|| (RItem!=NULL && RItem->GetDistanceArea	(localX,localY,RetDistance)==true && RetDistance<10)
			|| (RItem==NULL && L->IsInclude(localX,localY)==true)){
				AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(GetLayersBase());
				A->Data=CreateItem(L->GetItemClassType());
				((AlgorithmItemPI *)(A->Data))->SetParent(this);
				*A->Data	=*L;
				A->PhaseCode=L->GetPhaseCode();
				A->Layer	=0;
				A->ItemID	=L->GetID();
				A->LibID	=L->GetLibID();
				A->ItemClassType=L->GetItemClassType();
				A->Result	=(RItem!=NULL)?RItem->GetError():-1;
				A->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				GetParentBase()->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
				L->MakeIndependentItems(A,localX,localY);
				AData.Items.AppendList(A);
			}
		}
	}
}
void	AlgorithmInPagePI::MakeIndependentItems(int Layer ,IntList &Items,AlgorithmItemIndependentPack &Data)
{
	FastSearchIDItemStart();
	for(IntClass *d=Items.GetFirst();d!=NULL;d=d->GetNext()){
		AlgorithmItemRoot *L=FastSearchIDItem(d->GetValue());
		if(L!=NULL){
			AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(GetLayersBase());
			A->Data=CreateItem(L->GetItemClassType());
			((AlgorithmItemPI *)(A->Data))->SetParent(this);
			*A->Data	=*L;
			A->PhaseCode=L->GetPhaseCode();
			A->Layer	=0;
			A->ItemID	=L->GetID();
			A->LibID	=L->GetLibID();
			A->ItemClassType=L->GetItemClassType();
			A->Result	=(L->GetCurrentResult()!=NULL)?L->GetCurrentResult()->GetError():-1;
			A->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
			GetParentBase()->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
			Data.Items.AppendList(A);
		}
	}
}
void	AlgorithmInPagePI::SetIndependentItemData(int32 Command
												,int32 LocalPage,int32 Layer,int32 ItemID
												,AlgorithmItemRoot *Data
												,IntList &EdittedMemberID
												,QByteArray &Something
												,QByteArray &AckData)
{
	int	N=GetItemCount();
	AlgorithmItemPI **ATable=new AlgorithmItemPI *[N];
	int	i=0;
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext(),i++){
		ATable[i]=L;
	}
	//#pragma omp parallel                             
	//{                                                
	//	#pragma omp for
	if(Data==NULL){
		Data=SearchIDItem(ItemID);
	}
	if(Data!=NULL){
		for(int i=0;i<N;i++){
			ATable[i]->SetIndependentItemData(Command,LocalPage,Layer,Data,EdittedMemberID,Something,AckData);
		}
	}
	//}
	delete	[]ATable;
}

bool	AlgorithmInPagePI::GeneralDataRelease(int32 Command,void *data)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataRelease(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	*AlgorithmInPagePI::GeneralDataCreate(int32 Command,void *reqData)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		void	*ret=L->GeneralDataCreate(Command,reqData);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}
bool	AlgorithmInPagePI::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataLoad(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPagePI::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataSave(f,Command,data)==false){
			return false;
		}
	}
	return true;
}
bool	AlgorithmInPagePI::GeneralDataReply(int32 Command,void *data)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GeneralDataReply(Command,data)==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInPagePI::ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		ClipboardAlgorithmItem	*C=L->CreateClipboardItem();
		if(C!=NULL){
			Pack.Items.AppendList(C);
		}
	}
}
int		AlgorithmInPagePI::GetSelectedItemCount(void)
{
	int	ret=0;
	AlgorithmItemPI	*a;
	//#pragma omp parallel
	//#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		//#pragma omp task
		{
			if(a->GetSelected()==true){
				//#pragma omp atomic
				ret++;
			}
		}
	}
	return ret;
}
int		AlgorithmInPagePI::GetItemCount(void)
{	
	return Data.GetNumber();
}

void	AlgorithmInPagePI::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	int	N=0;
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true){
			N++;
		}
	}
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoExecuteMove);
	::Save(UndoPointer->GetWritePointer(),N);
	::Save(UndoPointer->GetWritePointer(),GlobalDx);
	::Save(UndoPointer->GetWritePointer(),GlobalDy);

	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			int32	ItemID=L->GetID();
			::Save(UndoPointer->GetWritePointer(),ItemID);
			L->Save(UndoPointer->GetWritePointer());

			L->ExecuteMove(GlobalDx,GlobalDy,AllItems);
			if(L->IsNull()==true){
				AlgorithmItemPI *NextL=L->GetNext();
				RemoveItem(L);
				delete	L;
				L=NextL;
			}
			else{
				L=L->GetNext();
			}
			Changed=true;
			CalcDone =false;
		}
		else{
			L=L->GetNext();
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}

void	AlgorithmInPagePI::ExecuteMove(int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items,bool AllItems)
{
	Items.MakeLinearDim();
	int	N=0;
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true && Items.IsIncludeByLinear(GetPage(),0,L->GetID())==true){
			N++;
		}
	}
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoExecuteMove);
	::Save(UndoPointer->GetWritePointer(),N);
	::Save(UndoPointer->GetWritePointer(),GlobalDx);
	::Save(UndoPointer->GetWritePointer(),GlobalDy);

	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;){
		AlgorithmItemPI *NextL=L->GetNext();
		if((L->GetSelected()==true || AllItems==true) && L->GetEditLocked()==false  && L->GetVisible()==true && Items.IsIncludeByLinear(GetPage(),0,L->GetID())==true){
			int32	ItemClassType=L->GetItemClassType();
			::Save(UndoPointer->GetWritePointer(),ItemClassType);
			int32	ItemID=L->GetID();
			::Save(UndoPointer->GetWritePointer(),ItemID);
			//L->Save(UndoPointer->GetWritePointer());
			L->ExecuteMove(GlobalDx,GlobalDy,AllItems);
			//if(L->IsNull()==true){
			//	RemoveItem(L);
			//	delete	L;
			//}
			Changed=true;
			CalcDone =false;
		}
		L=NextL;
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInPagePI::UndoExecuteMove(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false){
		return;
	}
	int	GlobalDx,GlobalDy;
	if(::Load(f,GlobalDx)==false){
		return;
	}
	if(::Load(f,GlobalDy)==false){
		return;
	}

	FastSearchIDItemStart();
	for(int i=0;i<N;i++){
		int32	ItemClassType;
		if(::Load(f,ItemClassType)==false){
			return;
		}
		int32	ItemID;
		if(::Load(f,ItemID)==false){
			return;
		}		
		AlgorithmItemRoot	*L=FastSearchIDItem(ItemID);
		if(L!=NULL){
			//if(L->Load(f,GetLayersBase())==false){
			//	return;
			//}
			L->ExecuteMove(-GlobalDx,-GlobalDy,true);
		}
		else{
			//L=CreateItem(ItemClassType);
			//if(L!=NULL){
			//	if(L->Load(f,GetLayersBase())==false){
			//		return;
			//	}
			//	AppendItem(L,ItemID);
			//}
		}
	}
}
void	AlgorithmInPagePI::GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetSelected()==true){
			L->GetPageListForExecuteMove(PageList ,GlobalDx,GlobalDy);
		}
	}
}


void	AlgorithmInPagePI::GetItemIDListOnPoint(int localX,int localY,IntList &RetList)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsInclude(localX,localY)==true && L->GetVisible()==true){
			RetList.Add(L->GetID());
		}
	}
}
void	AlgorithmInPagePI::GetItemIDListOnPoint(FlexArea &CoveredArea ,IntList &RetList)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->IsCrossed(&CoveredArea)==true){
			RetList.Add(L->GetID());
		}
	}
}

void	AlgorithmInPagePI::SelectItems(FlexArea &Area ,const IntList &LayerList,bool MultiSelect)
{
	SelectArea(Area,MultiSelect);
}
void	AlgorithmInPagePI::SelectItems(const IntList &ItemIDs)
{
	for(AlgorithmItemPI *L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(ItemIDs.IsInclude(L->GetID())==true){
			L->SetSelected(true);
		}
	}
}
void	AlgorithmInPagePI::GetLayerAndItemID(int LocalX ,int LocalY ,ListLayerIDLibNamePack &ItemList ,const IntList &LayerList)
{
	IntList RetList;
	GetItemIDListOnPoint(LocalX,LocalY,RetList);
	FastSearchIDItemStart();
	for(IntClass *d=RetList.GetFirst();d!=NULL;d=d->GetNext()){
		int	ItemID=d->GetValue();
		AlgorithmItemRoot	*item=FastSearchIDItem(ItemID);
		if(item!=NULL){
			ListLayerIDLibName	*k=new ListLayerIDLibName(0,ItemID,item->GetLibID());
			ItemList.AppendList(k);		
		}
	}
}
void	AlgorithmInPagePI::GetLayerAndItemID(FlexArea &CoveredArea ,ListLayerAndIDPack &ItemList ,const IntList &LayerList)
{
	IntList RetList;		
	GetItemIDListOnPoint(CoveredArea,RetList);
	for(IntClass *d=RetList.GetFirst();d!=NULL;d=d->GetNext()){
		ItemList.AppendList(new ListLayerAndID(0,d->GetValue()));		
	}
}
void	AlgorithmInPagePI::GetItems(ListLayerAndIDPack &ItemList ,AlgorithmItemPointerListContainer &Items)
{
	FastSearchIDItemStart();

	for(ListLayerAndID *L=ItemList.GetFirst();L!=NULL;L=L->GetNext()){
		bool	Found=false;
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetItem()->GetID()==L->ID){
				Found=true;
				break;
			}
		}
		if(Found==false){
			AlgorithmItemRoot	*item=FastSearchIDItem(L->ID);
			if(item!=NULL){
				Items.Add(item);
			}
		}
	}
}
void	AlgorithmInPagePI::EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)
{
	for(AlgorithmItemPI *L=Data.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetOriginType()==b){
			Items.Add(L);
		}
	}
}
void	AlgorithmInPagePI::EnumOriginTypeItems(int layer ,OriginType b ,AlgorithmItemPointerListContainer &Items)
{
	EnumOriginTypeItems(b ,Items);
}
void	AlgorithmInPagePI::EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(func!=NULL){
			if(func(caller,item)==true){
				Items.Add(item);
			}
		}
		else{
			Items.Add(item);
		}
	}
}
void	AlgorithmInPagePI::EnumItems(int layer ,void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))
{
	EnumItems(caller,Items , func);
}
void	AlgorithmInPagePI::ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		func(caller,item);
	}
}
void	AlgorithmInPagePI::ScanItems(int layer ,void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))
{
	ScanItems(caller,func);
}
void	AlgorithmInPagePI::SelectItemByID(ListLayerAndIDPack &SelectedItem)
{
	for(ListLayerAndID *L=SelectedItem.GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmItemRoot	*a=SearchIDItem(L->ID);
		if(a!=NULL){
			a->SetSelected(true);
		}
	}
}


bool	AlgorithmInPagePI::ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
														,FlexArea &area ,AlgorithmBase *OriginBase
														,int ItemClass)
{
	AlgorithmItemRoot	*a=CreateItem(ItemClass);
	if(Buff.isOpen()==false){
		Buff.open(QIODevice::ReadOnly);
	}
	else{
		Buff.close();
		Buff.open(QIODevice::ReadOnly);
		Buff.seek(0);
	}
	bool	Ret;
	if(a!=NULL && a->Load(&Buff,GetLayersBase())==true){
		a->SetArea(area);
		if((PastedLayer==-1 || PastedLayer==item->Layer) && AppendItem(a)==true){
			UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
			::Save(UPointer->GetWritePointer(),a->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			a->SetOrigin(OriginBase);
			Changed=true;
			CalcDone =false;
			Ret=true;
		}
		else{
			delete	a;
			Ret=false;
		}
	}
	else{
		delete	a;
		Ret=false;
	}
	return Ret;
}

bool	AlgorithmInPagePI::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste)
{
	AlgorithmItemRoot	*a=CreateItem(item->ItemClassType);
	QBuffer	Buff(&item->ItemData);
	Buff.open(QIODevice::ReadOnly);
	bool	Ret;
	if(a->Load(&Buff,GetLayersBase())==true){
		a->SetArea(area);
		if(AppendItem(a)==true){
			if(SelectModeAfterPaste==true){
				a->SetSelected(true);
			}
			UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
			::Save(UPointer->GetWritePointer(),a->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			Changed=true;
			CalcDone =false;
			Ret=true;
		}
		else{
			delete	a;
			Ret=false;
		}
	}
	else{
		delete	a;
		Ret=false;
	}
	return Ret;
}
bool	AlgorithmInPagePI::ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,VectorLineBase *Vector,bool SelectModeAfterPaste)
{
	AlgorithmItemRoot	*a=CreateItem(item->ItemClassType);
	QBuffer	Buff(&item->ItemData);
	Buff.open(QIODevice::ReadOnly);
	bool	Ret;
	if(a->Load(&Buff,GetLayersBase())==true){
		a->SetVector(*Vector);
		if(AppendItem(a)==true){
			if(SelectModeAfterPaste==true){
				a->SetSelected(true);
			}
			UndoElement<AlgorithmInPagePI>	*UPointer	=new UndoElement<AlgorithmInPagePI>(this,&AlgorithmInPagePI::UndoExecutePaste);
			::Save(UPointer->GetWritePointer(),a->GetID());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			Changed=true;
			CalcDone =false;
			Ret=true;
		}
		else{
			delete	a;
			Ret=false;
		}
	}
	else{
		delete	a;
		Ret=false;
	}
	return Ret;
}

void	AlgorithmInPagePI::UndoExecutePaste(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*L=SearchIDItem(ItemID);
	if(L!=NULL){
		RemoveItem(L);
		delete	L;
	}
}

void	AlgorithmInPagePI::GenerateAlgorithmItemCount(AlgorithmItemCountInPage &Ret)
{
	int	N=GetItemCount();
	Ret.CountInLayer.Add(N);
}
void	AlgorithmInPagePI::CopyFrom(AlgorithmBase *DestParent
									,AlgorithmInPageRoot *src 
									,int OffsetX,int OffsetY
									,int PartsMaster ,int PartsID
									,bool ReferedThresholdMode)
{
	Parent=DestParent;
	AlgorithmInPagePI	*srcD=dynamic_cast<AlgorithmInPagePI *>(src);
	if(srcD!=NULL){
		int	N=srcD->GetItemCount();
		AlgorithmItemPI **ItemList=new AlgorithmItemPI*[N];
		AlgorithmItemPI **NewItemList=new AlgorithmItemPI*[N];
		int	i=0;
		for(AlgorithmItemPI *Item=srcD->GetFirstData();Item!=NULL;Item=Item->GetNext()){
			ItemList[i]=Item;
			i++;
		}
		LayersBase	*DestBase=DestParent->GetLayersBase();

		#pragma omp parallel                             
		{                                                
			#pragma omp for schedule(dynamic)
			for(int k=0;k<N;k++){
				AlgorithmItemPI *Item=ItemList[k];
				AlgorithmItemRoot	*d=CreateItem(Item->GetItemClassType());
				((AlgorithmItemPI *)d)->SetParent(this);
				d->SetPartsData(PartsMaster ,PartsID ,Item->GetID());
				d->SetRefereneFrom(Item,OffsetX,OffsetY);
				d->SetNewThresholdInstance(DestBase);
				if(d->IsNull()==false){
					d->CopyAttrFrom(Item);
				}
				else{
					delete	d;
					d=NULL;
				}
				NewItemList[k]=(AlgorithmItemPI *)d;
			}
		}
		for(int k=0;k<N;k++){
			if(NewItemList[k]!=NULL){
				AppendItem(NewItemList[k]);
			}
		}
		if(N!=NULL){
			Changed=true;
			CalcDone=false;
		}
		delete	[]ItemList;
		delete	[]NewItemList;
	}
}
void	AlgorithmInPagePI::InitializeFromParts(void)
{
	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;){
		AlgorithmItemPI *NextItem=Item->GetNext();
		if(Item->PartsID>=0){
			RemoveItem(Item);
			delete	Item;
			Changed=true;
		}
		Item=NextItem;
	}	
}

void	AlgorithmInPagePI::CopyItems(FlexArea &SrcArea ,int mx ,int my)
{
	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		if(Item->GetArea().CheckOverlap(&SrcArea)==true){
			FlexArea	A=Item->GetArea();
			A.ClipArea(SrcArea);
			A.MoveToClip(mx,my,0,0,GetDotPerLine(),GetMaxLines());
			if(A.IsNull()==false){
				AlgorithmItemRoot	*d=CreateItem(Item->GetItemClassType());
				((AlgorithmItemPI *)d)->SetParent(this);
				d->SetArea(A);
				d->CopyAttrFrom(Item);
				AppendItem(d);
				Changed=true;
			}
		}
	}
	CalcDone =false;
}

void	AlgorithmInPagePI::MoveItemsToDispatcherForLoadingParts(void)
{
	Dispatcher.RemoveAll();
	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;){
		if(Item->IsOriginParts()==true){
			AlgorithmItemPI *NextItem=Item->GetNext();
			RemoveItem(Item);
			Dispatcher.AppendList(Item);
			Changed=true;
			CalcDone=false;
			Item=NextItem;
		}
		else{
			Item=Item->GetNext();
		}
	}
}

static	int	CopyItemsFormDispatcherForPartsFunc(const void *a , const void *b)
{
	AlgorithmItemPI	**ka=(AlgorithmItemPI **)a;
	AlgorithmItemPI	**kb=(AlgorithmItemPI **)b;

	if((*ka)->GetPartsID()>(*kb)->GetPartsID()){
		return -1;
	}
	if((*ka)->GetPartsID()<(*kb)->GetPartsID()){
		return 1;
	}
	if((*ka)->GetPartsAllocID()>(*kb)->GetPartsAllocID()){
		return -1;
	}
	if((*ka)->GetPartsAllocID()<(*kb)->GetPartsAllocID()){
		return 1;
	}
	if((*ka)->GetPartsItemID()>(*kb)->GetPartsItemID()){
		return -1;
	}
	if((*ka)->GetPartsItemID()<(*kb)->GetPartsItemID()){
		return 1;
	}
	return 0;
}

void	AlgorithmInPagePI::CopyItemsFormDispatcherForParts(void)
{
	int	DestTableNumb=GetItemCount();
	AlgorithmItemPI	**DestTable=new AlgorithmItemPI*[DestTableNumb];
	int	N=0;
	for(AlgorithmItemPI *Dest=GetFirstData();Dest!=NULL;Dest=Dest->GetNext()){
		DestTable[N]=Dest;
		N++;
	}
	QSort(DestTable,N,sizeof(DestTable[0]),CopyItemsFormDispatcherForPartsFunc);

	for(AlgorithmItemPI *Src=Dispatcher.GetFirst();Src!=NULL;Src=Src->GetNext()){
		AlgorithmItemPI *Key=Src;
		AlgorithmItemPI **Dest=(AlgorithmItemPI **)EqualSearch(&Key,DestTable,N,sizeof(DestTable[0]),CopyItemsFormDispatcherForPartsFunc);

		if(Dest!=NULL){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			Src->SaveUnique(&Buff);
			Buff.seek(0);
			(*Dest)->LoadUnique(&Buff);
		}
	}
	delete	[]DestTable;
}

void	AlgorithmInPagePI::RemoveItemFormDispatcher(void)
{
	Dispatcher.RemoveAll();
}
void	AlgorithmInPagePI::GetOriginRootNames(NPListPack<OriginNames> &OriginNameList ,const IntList &LayerList)
{
	AlgorithmBase	*Dim[1000];
	int				DimNumb=0;
	int				ItemNumb[1000];

	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		int i;
		for(i=0;i<DimNumb;i++){
			if(Dim[i]==item->GetOrigin()){
				ItemNumb[i]++;
				break;
			}
		}
		if(i>=DimNumb && i<sizeof(Dim)/sizeof(Dim[0])){
			Dim[DimNumb]=item->GetOrigin();
			ItemNumb[DimNumb]=1;
			DimNumb++;
		}
	}
	for(int i=0;i<DimNumb;i++){
		OriginNames	*v=new OriginNames();
		Dim[i]->GetDLLName(v->DLLRoot ,v->DLLName);
		v->Numb=ItemNumb[i];
		OriginNameList.AppendList(v);
	}
}

void	AlgorithmInPagePI::SelectOriginRootNames(AlgorithmBase *OriginBase,const IntList &LayerList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetOrigin()==OriginBase){
			item->SetSelected(true);
		}
	}
}

void	AlgorithmInPagePI::VisibleAll(const IntList &LayerList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetVisible(true);
	}
}

void	AlgorithmInPagePI::InvisibleAll(const IntList &LayerList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetVisible(false);
	}
}

void	AlgorithmInPagePI::InvisibleSelected(const IntList &LayerList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->SetVisible(false);
		}
		else{
			item->SetVisible(true);
		}
	}
}

void	AlgorithmInPagePI::SelectManualCreature(const IntList &LayerList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetManualCreated()==true){
			item->SetSelected(true);
		}
		else{
			item->SetSelected(false);
		}
	}
}

bool	AlgorithmInPagePI::IsEdited(void)
{
	if(Changed==true){
		return true;
	}
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsEdited()==true){
			return true;
		}
	}
	return false;
}
bool	AlgorithmInPagePI::IsCalcDone(void)
{
	if(CalcDone==false){
		return false;
	}
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsCalcDone()==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInPagePI::SetEdited(bool edited)
{
	Changed=edited;
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetEdited(edited);
	}
}
void	AlgorithmInPagePI::SetCalcDone(bool calcdone)
{
	CalcDone=calcdone;
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetCalcDone(calcdone);
	}
}
void	AlgorithmInPagePI::ResetProcessDone(void)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->ResetProcessDone();
	}
}
bool	AlgorithmInPagePI::IsProcessDone(void)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsProcessDone()==false){
			return false;
		}
	}
	return true;
}
void	AlgorithmInPagePI::SetProcessDone(bool b)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetProcessDone(b);
	}
}
void	AlgorithmInPagePI::GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->GetOutsideItems(dx,dy,OutsideItems,MaxGlobalPage);
	}
}

void	AlgorithmInPagePI::ClearTemporaryItems(void)
{
	MutexTemporaryItem.lock();
	TemporaryItemList.RemoveAll();
	MutexTemporaryItem.unlock();
}
void	AlgorithmInPagePI::SetTemporaryItems(ItemPointerListInPage *Pg)
{
	MutexTemporaryItem.lock();
	for(ItemPointerListInLayer *p=Pg->LayerList.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Layer==0){
			TemporaryItemList.AddMove(p->ItemList);
		}
	}
	MutexTemporaryItem.unlock();
}

void	AlgorithmInPagePI::AddItemsForMove(ItemPointerListInPage *Pg)
{
	IntList	IDList;
	ItemPointerList	*c;
	UndoAlgorithmPage	*UndoPointer=new UndoAlgorithmPage(this ,&AlgorithmInPageRoot::UndoAddItemsForMove);
	for(ItemPointerListInLayer	*Ly=Pg->LayerList.GetFirst();Ly!=NULL;Ly=Ly->GetNext()){
		if(Ly->Layer==0){
			while((c=Ly->ItemList.GetFirst())!=NULL){
				Ly->ItemList.RemoveList(c);
				c->ItemPointer->MoveTo(c->Dx,c->Dy);
				AlgorithmItemPI	*d=dynamic_cast<AlgorithmItemPI *>(c->ItemPointer);
				if(d!=NULL){
					AppendItem(d);
				}
				c->ItemPointer=NULL;
				c->Created=false;
			}
			IDList.Save(UndoPointer->GetWritePointer());
		}
		InitialThreadBufferForExecute();
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
}
void	AlgorithmInPagePI::UndoAddItemsForMove(QIODevice *f)
{
	IntList	IDList;

	if(IDList.Load(f)==true){
		FastSearchIDItemStart();
		for(IntClass *c=IDList.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmItemRoot	*L=FastSearchIDItem(c->GetValue());
			if(L!=NULL){
				RemoveItem(L);
				delete	L;
			}
		}
	}
}
bool	AlgorithmInPagePI::ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)
{
	int	ItemCount=GetItemCount();
	AlgorithmItemRoot	**Source=new AlgorithmItemRoot *[ItemCount];
	AlgorithmItemRoot	**Dest  =new AlgorithmItemRoot *[ItemCount];
	int		CopiedCount=0;
	LayersBase	*LBase=GetLayersBase();

	for(AlgorithmItemPI *Item=GetFirstData();Item!=NULL;Item=Item->GetNext()){
		if(Item->GetSelected()==true){
			Source[CopiedCount]=Item;
			Dest[CopiedCount]=NULL;
			CopiedCount++;
		}
	}
	if(CopiedCount>20){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic)
			for(int i=0;i<CopiedCount;i++){
				if(Source[i]->IsCrossed(-Dx, -Dy,GetDotPerLine()-Dx,GetMaxLines()-Dy)==true){
					Dest[i]=CreateItem(Source[i]->GetItemClassType());
					Dest[i]->SetRefereneFrom(Source[i],Dx,Dy);
					Dest[i]->SetNewThresholdInstance(LBase);
					Dest[i]->CopyFrom(Source[i]);
					Dest[i]->MoveTo(Dx,Dy);
				}
			}
		}
	}
	else{
		for(int i=0;i<CopiedCount;i++){
			if(Source[i]->IsCrossed(-Dx, -Dy,GetDotPerLine()-Dx,GetMaxLines()-Dy)==true){
				Dest[i]=CreateItem(Source[i]->GetItemClassType());
				Dest[i]->SetRefereneFrom(Source[i],Dx,Dy);
				Dest[i]->SetNewThresholdInstance(LBase);
				Dest[i]->CopyFrom(Source[i]);
				Dest[i]->MoveTo(Dx,Dy);
			}
		}
	}
	for(int i=0;i<CopiedCount;i++){
		if(Dest[i]!=NULL){
			AppendItem(Dest[i]);
			Dest[i]->ClipPage();
			Dest[i]->SetSelected(false);
			Changed=true;
			CalcDone=false;
		}
	}
	delete	[]Source;
	delete	[]Dest;
	return true;
}

void	AlgorithmInPagePI::SelectedItemListsForPaste(IntList &LayerList ,ExpandedSelectedItemListContainer &Lists)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			ExpandedSelectedItemList	*c=new ExpandedSelectedItemList();
			c->X1=item->GetArea().GetMinX();
			c->Y1=item->GetArea().GetMinY();
			c->X2=item->GetArea().GetMaxX();
			c->Y2=item->GetArea().GetMaxY();
			c->Page=GetPage();
			c->Layer=0;
			c->ItemID=item->GetID();
			Lists.AppendList(c);
		}
	}
}
void	AlgorithmInPagePI::DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int Layer,int ItemID ,double ZoomRate ,int movx ,int movy,int turn)
{
	if(turn==0){
		FastSearchIDItemStart();
	}
	AlgorithmItemRoot		*Item=FastSearchIDItem(ItemID);
	if(Item!=NULL){
		Item->DrawItemListsForPaste(dx, dy ,Pnt,ZoomRate ,movx ,movy);
	}
}

void	AlgorithmInPagePI::ExecuteTransformSelectedItems(TransformBase &M)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->ExecuteTransformSelectedItem(M);
		}
	}
}

bool	AlgorithmInPagePI::SaveCSVMasterReport(QStringListListCSV &CSVData)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->SaveCSVMasterReport(CSVData)==false){
			return false;
		}
	}
	return true;
}

void	AlgorithmInPagePI::RotateItem(int AngleDegree ,int Cx, int Cy)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->RotateItem(AngleDegree ,Cx, Cy);
		}
	}
}

void	AlgorithmInPagePI::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			item->MirrorItem(MirrorMode ,PointX ,PointY);
		}
	}
}
bool	AlgorithmInPagePI::GetSelectedCenter(DotListContainer &CenterByLayer)
{
	double	MCx=0.0,MCy=0.0;
	int64	AreaDots=0;
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			FlexArea	&Area=item->GetArea();
			int64		N=Area.GetPatternByte();
			double	x,y;
			item->GetCenter(x,y);
			if(N!=0){
				AreaDots+=N;
				MCx+=x*N;
				MCy+=y*N;
			}
			else{
				AreaDots++;
				MCx+=x;
				MCy+=y;
			}
		}
	}
	if(AreaDots==0){
		return false;
	}
	int	Cx=MCx/AreaDots;
	int	Cy=MCy/AreaDots;
	DotList	*a=new DotList(Cx,Cy);
	CenterByLayer.AppendList(a);
	return true;
}
bool	AlgorithmInPagePI::GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	bool	Ret=false;
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			int	x1,y1,x2,y2;
			item->GetXY(x1,y1,x2,y2);
			if(x1<X1){
				X1=x1;
			}
			if(y1<Y1){
				Y1=y1;
			}
			if(x2>X2){
				X2=x2;
			}
			if(y2>Y2){
				Y2=y2;
			}
			Ret=true;
		}
	}
	return Ret;
}
bool	AlgorithmInPagePI::GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)
{
	X1=99999999;
	Y1=99999999;
	X2=-99999999;
	Y2=-99999999;
	AlgorithmItemPI *item;
	bool	Ret=false;
	for(item=GetFirstData();item!=NULL;item=item->GetNext()){
		int	x1,y1,x2,y2;
		item->GetXY(x1,y1,x2,y2);
		if(x1<X1){
			X1=x1;
		}
		if(y1<Y1){
			Y1=y1;
		}
		if(x2>X2){
			X2=x2;
		}
		if(y2>Y2){
			Y2=y2;
		}
		Ret=true;
	}
	return Ret;
}

bool	AlgorithmInPagePI::SaveItemsForLearning(ItemDataListWithIDContainer &Buff
												,FlexArea &LocalArea
												,AlgorithmLibraryListContainer &LibList
												,int AddedX,int AddedY ,bool OkMode)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(LibList.IsInclude(item->GetLibType(),item->GetLibID())==true){
			FlexArea	A=item->GetArea();
			ResultInItemRoot	*R=item->GetCurrentResult();
			if(R!=NULL){
				A.MoveToNoClip(R->GetItemSearchedX(),R->GetItemSearchedY());
			}
			if(A.CheckOverlap(&LocalArea)==true){
				ItemDataListWithID	*h=item->MakeItemForLearning(AddedX,AddedY,OkMode);
				if(h!=NULL){
					Buff.AppendList(h);
				}
			}
		}
	}
	return true;
}

bool	AlgorithmInPagePI::LoadItemsForLearning(ItemDataListWithIDContainer &Buff ,int AddedX ,int AddedY)
{
	for(ItemDataListWithID *c=Buff.GetFirst();c!=NULL;c=c->GetNext()){
		QBuffer	HBuff(&c->IData);
		HBuff.open(QIODevice::ReadOnly);

		if(::Load(&HBuff,c->ItemClassType)==false){
			return false;
		}
		AlgorithmItemRoot *m=CreateItem(c->ItemClassType);
		if(m==NULL)
			return false;
		if(m->LoadForLearning(&HBuff,GetLayersBase())==false){
			return false;
		}
		int64	ItemID=m->GetID();
		m->MoveTo(AddedX,AddedY);
		AppendItem(m);
		m->SetID(ItemID);
	}
	return true;
}
bool	AlgorithmInPagePI::GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->IsInclude(LocalX,LocalY)==true){
			ItemPointerList	*c=new ItemPointerList();
			c->ItemPointer=item;
			c->Dx=0;
			c->Dy=0;
			c->Created=false;
			Items.AppendList(c);
		}
	}
	return true;
}

HistgramByParamBase	*AlgorithmInPagePI::GetHistgramBase(int Layer,int ItemID,int HistID)
{
	AlgorithmItemRoot *item=SearchIDItem(ItemID);
	if(item!=NULL){
		HistgramByParamBase	*r=item->GetThresholdBaseWritable()->GetHistgramBase(HistID);
		return r;
	}
	return NULL;
}
void	AlgorithmInPagePI::MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->MakeUncoveredMap(BMap, XByte ,YLen);
	}
}
void	AlgorithmInPagePI::SetItemName(const QString &ItemName , bool OnlySelected)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		item->SetItemName(ItemName , OnlySelected);
	}
}
bool	AlgorithmInPagePI::ShrinkItems(const IntList &LayerList,int ExpandPixels,bool MaskForSameLib)
{
	bool	Ret=true;
	if(MaskForSameLib==false){
		for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true){
				if(item->ShrinkItems(ExpandPixels)==false){
					Ret=false;
				}
			}
		}
	}
	else{
		int	XLen	=GetDotPerLine();
		int	XByte	=(XLen+7)/8;
		int	YLen	=GetMaxLines();
		BYTE	**Mask=MakeMatrixBuff(XByte,YLen);
		
		IntList	LibIDs;
		for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true){
				LibIDs.Merge(item->GetLibID());
			}
		}
		for(IntClass *c=LibIDs.GetFirst();c!=NULL;c=c->GetNext()){
			MatrixBuffClear	(Mask ,0 ,XByte,YLen);
			for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
				if(c->GetValue()==item->GetLibID()){
					item->GetArea().MakeBitData(Mask,XLen,YLen);
				}
			}
			for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
				if(item->GetSelected()==true && item->GetEditLocked()==false && item->GetVisible()==true
				&& c->GetValue()==item->GetLibID()){
					if(item->ShrinkItems(ExpandPixels,Mask)==false){
						Ret=false;
					}
				}
			}
		}
		DeleteMatrixBuff(Mask,YLen);
	}
	return Ret;
}
void	AlgorithmInPagePI::EnumLibID(IntList &LibIDList)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()>=0){
			if(LibIDList.IsInclude(item->GetLibID())==false){
				LibIDList.Add(item->GetLibID());
			}
		}
	}
}
void	AlgorithmInPagePI::MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()==LibID){
			RetContainer.Add(item);
		}
	}
}

void	AlgorithmInPagePI::EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetHistgramBase(HistID)!=NULL){
			AlgorithmItemPointerList	*a=new AlgorithmItemPointerList(item);
			RetContainer.AppendList(a);
		}
	}
}

void	AlgorithmInPagePI::EnumItemHistgram(int HistID ,int LibID, AlgorithmItemPointerListContainer &RetContainer)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetLibID()==LibID && item->GetHistgramBase(HistID)!=NULL){
			AlgorithmItemPointerList	*a=new AlgorithmItemPointerList(item);
			RetContainer.AppendList(a);
		}
	}
}

ImageBuffer		**AlgorithmInPagePI::GetMasterBuff(void)	
{	
	return(MasterBuffDim[0]);
}
ImageBuffer		**AlgorithmInPagePI::GetMasterBuff(int n)	
{	
	if(n<0){
		n=0;
	}
	return(MasterBuffDim[n]);
}

ImageBuffer		**AlgorithmInPagePI::GetBackGroundBuff(void)	
{	
	return(BackGroundBuffDim[0]);
}
ImageBuffer		**AlgorithmInPagePI::GetBackGroundBuff(int n)	
{	
	if(n<0){
		n=0;
	}
	return(BackGroundBuffDim[n]);
}
ImageBuffer		**AlgorithmInPagePI::GetTargetBuff(void)
{	
	return(TargetBuffDim);
}
ImageBuffer		**AlgorithmInPagePI::GetTargetTRBuff(void)
{	
	return(TargetTRBuffDim);
}
ImageBuffer		**AlgorithmInPagePI::GetBitBuff(void)
{	
	return(BitBuffDim);
}
ImageBuffer		**AlgorithmInPagePI::GetTrialTargetBuff(void)
{	
	return(TrialTargetBuffDim);
}

int	AlgorithmInPagePI::GetMasterBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetMasterBuffPointer();
	}
	return layer;
}
int	AlgorithmInPagePI::GetMasterBuffList(int n,ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetMasterBuffPointer(n);
	}
	return layer;
}
int	AlgorithmInPagePI::GetBackGroundBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetBackGroundBuffPointer();
	}
	return layer;
}
int	AlgorithmInPagePI::GetBackGroundBuffList(int n,ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=L->GetBackGroundBuffPointer(n);
	}
	return layer;
}
int	AlgorithmInPagePI::GetTargetBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTargetBuff();
	}
	return layer;
}
int	AlgorithmInPagePI::GetTargetTRBuffList(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTargetTRBuff();
	}
	return layer;
}
int	AlgorithmInPagePI::GetTrialTargetBuffList	(ImageBuffer *ImageList[])
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImageList[layer]=&L->GetTrialTargetBuff();
	}
	return layer;
}

int	AlgorithmInPagePI::GetMasterBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetMasterBuffPointer());
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmInPagePI::GetMasterBuffList(int n,ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetMasterBuffPointer(n));
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmInPagePI::GetBackGroundBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetBackGroundBuffPointer());
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmInPagePI::GetBackGroundBuffList(int n,ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(L->GetBackGroundBuffPointer(n));
		ImageList.AppendList(a);
	}
	return layer;
}

int	AlgorithmInPagePI::GetTargetBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTargetBuff());
		ImageList.AppendList(a);
	}
	return layer;
}
int	AlgorithmInPagePI::GetTargetTRBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTargetTRBuff());
		ImageList.AppendList(a);
	}
	return layer;
}
int	AlgorithmInPagePI::GetTrialTargetBuffList(ImagePointerContainer &ImageList)
{
	DataInPage	*P=GetDataInPage();
	int	layer;
	int	LayerNumb=GetLayerNumb();
	for(layer=0;layer<LayerNumb;layer++){
		DataInLayer	*L=P->GetLayerData(layer);
		ImagePointerList	*a=new ImagePointerList(&L->GetTrialTargetBuff());
		ImageList.AppendList(a);
	}
	return layer;
}
bool	AlgorithmInPagePI::ManualExecuteAll(ManualExecuter &ManualExecuterData)
{
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->ManualExecuteAll(ManualExecuterData)==false){
			return false;
		}
	}
	return true;
}

void	AlgorithmInPagePI::MakeBindedThreshold(BindedThresholdContainer &Container)
{
	AlgorithmItemPI	**List=new AlgorithmItemPI*[GetItemCount()];
	int	n=0;
	for(AlgorithmItemPI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		List[n]=item;
	}
	for(int i=0;i<n;i++){
		if(List[i]!=NULL){
			AlgorithmThreshold	*A=List[i]->GetThresholdBaseWritable();
			if(A!=NULL){
				BindedThresholdList	*B=new BindedThresholdList;
				B->ItemIDs.Add(List[i]->GetID());
				B->LibID	=List[i]->GetLibID();
				B->Layer	=0;
				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				A->Save(&Buff);
				B->ThresholdData=Buff.buffer();
				List[i]=NULL;
				for(int j=i+1;j<n;j++){
					AlgorithmThreshold	*A2=List[j]->GetThresholdBaseWritable();
					if(A2!=NULL && List[j]->GetLibID()==B->LibID){
						if(A2->IsEqual(*A)==true){
							B->ItemIDs.Add(List[j]->GetID());
							List[j]=NULL;
						}
					}
				}
				
				Container.AppendList(B);
			}
		}
	}
	delete	[]List;
}

void	AlgorithmInPagePI::GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items)
{
	Items.RemoveAll();
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		AlgorithmItemPointerListContainerByLib	*f=Items.FindByLibID(0,a->GetLibID());
		if(f==NULL){
			f=new AlgorithmItemPointerListContainerByLib(0,a->GetLibID());
			Items.AppendList(f);
		}
		f->Container.Add(a);
	}
}
void	AlgorithmInPagePI::UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)
{
	if(ItemID<0){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetLibID()==LibID){
				a->UpdateThreshold(LearningMenuID,LRes);
			}
		}
	}
	else{
		AlgorithmItemRoot	*a=SearchIDItem(ItemID);
		if(a!=NULL){
			a->UpdateThreshold(LearningMenuID,LRes);
		}
	}
}
void	AlgorithmInPagePI::EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)
{
	int	Phase=GetPhaseCode();
	int	Page=GetPage();
	int	Layer=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		int	LibID=a->GetLibID();
		ListPhasePageLayerLibID *L;
		for(L=ItemIDList.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->Data.Phase==Phase
			&& L->Data.Page==Page
			&& L->Data.Layer==Layer
			&& L->Data.LibID==LibID){
				break;
			}
		}
		if(L==NULL){
			L=new ListPhasePageLayerLibID(Phase,Page,Layer,LibID);
			ItemIDList.AppendList(L);
		}
		L->ItemIDs.Add(a->GetID());
	}
}
void	AlgorithmInPagePI::EnumItems(int layer ,ListPhasePageLayerLibIDPack &ItemIDList)
{
	EnumItems(ItemIDList);
}
bool	AlgorithmInPagePI::MakeConfirmItem(ConfirmItemListContainer &ItemList)
{
	AlgorithmBase	*ABase=GetParentBase();
	AlgorithmLibraryContainer	*LibC=ABase->GetLibraryContainer();
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		ResultInItemRoot	*Res=a->GetCurrentResult();
		if(Res!=NULL){
			if(Res->IsOk()==false){
				ConfirmItemList	*d=new ConfirmItemList();
				d->Page=GetPage();
				d->Phase=GetPhaseCode();
				d->Layer=0;
				d->ItemID	=a->GetID();
				d->CType	=CF_NG;

				ResultPosList	*r=Res->GetPosList().GetFirst();
				if(r!=NULL){
					DetailResultInfoListContainer RetList;
					if(ABase->GetDrawResultDetail(a ,r ,RetList)==true){
						QStringList StrList;
						RetList.GetInfoStringList(StrList);
						QString	s;
						for(int i=0;i<StrList.count();i++){
							s+=StrList[i];
						}
						if(s.isEmpty()==false){
							d->Cause=s;
						}
					}
				}
				if(d->Cause.isEmpty()==true){
					d->Cause=Res->ResultItemToString();
				}
				if(d->Cause.isEmpty()==true && LibC!=NULL){				
					d->Cause=LibC->GetLibraryName(a->GetLibID());
				}
				ItemList.AppendList(d);
			}
		}
	}
	return true;
}

AlgorithmItemRoot	*AlgorithmInPagePI::FindItem(const AlgorithmItemIndex &Index)	const
{
	return SearchIDItem(Index.GetItemID());
}

void	AlgorithmInPagePI::MasterImageHasChanged(void)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		a->MasterImageHasChanged();
	}
}
