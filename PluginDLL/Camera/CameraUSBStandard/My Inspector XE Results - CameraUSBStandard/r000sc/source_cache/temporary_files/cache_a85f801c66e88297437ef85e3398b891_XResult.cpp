/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ServiceLibResource.h"
#include <QtGui>
#include <QColor>
#include "XResult.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XResultDLLManager.h"
#include "swap.h"
#include "XLearningRegist.h"
#include "XLotInformation.h"
#include "XCriticalFunc.h"

void	ResultVectorLine::Add(ResultVectorItem *t)
{
	AppendList(t);
}
ResultVectorItem &ResultVectorItem::operator=(const ResultVectorItem &src)
{
	TreePointList::operator=(*((TreePointList *)&src));
	return *this;
}

ResultVectorLine	&ResultVectorLine::operator=(TreeLine &src)
{
	TreeLine::operator=(src);
	return *this;
}

TmpNGRectClass::TmpNGRectClass(void)
{
	x1=0;
	y1=0;
	x2=0;
	y2=0;
	attr=0;
	mx=0;
	my=0;
	Count=0;
	ImportanceLevel=100;
	PieceAreaNumber=-1;
	NGSize	=0;
}

TmpNGRectClass   &TmpNGRectClass::operator=(TmpNGRectClass &src)
{
    x1	=src.x1;
	y1	=src.y1;
	x2	=src.x2;
	y2	=src.y2;
    attr=src.attr;
	mx	=src.mx;
	my	=src.my;
	Count=src.Count;
	ImportanceLevel=src.ImportanceLevel;
	PieceAreaNumber=src.PieceAreaNumber;
	NGSize=src.NGSize;
	return *this;
}

int	TmpNGRectClass::Compare(TmpNGRectClass &src)
{
	return NGSize - src.NGSize;
}

bool    TmpNGRectClass::Save(QIODevice *f)
{
	if(::Save(f,x1)==false){
		return false;
	}
	if(::Save(f,y1)==false){
		return false;
	}
	if(::Save(f,x2)==false){
		return false;
	}
	if(::Save(f,y2)==false){
		return false;
	}
	if(::Save(f,attr)==false){
		return false;
	}
	if(::Save(f,mx)==false){
		return false;
	}
	if(::Save(f,my)==false){
		return false;
	}
	if(::Save(f,Count)==false){
		return false;
	}
	if(::Save(f,ImportanceLevel)==false){
		return false;
	}
	if(::Save(f,PieceAreaNumber)==false){
		return false;
	}
	if(::Save(f,NGSize)==false){
		return false;
	}
	return true;
}

bool    TmpNGRectClass::Load(QIODevice *f)
{
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,attr)==false){
		return false;
	}
	if(::Load(f,mx)==false){
		return false;
	}
	if(::Load(f,my)==false){
		return false;
	}
	if(::Load(f,Count)==false){
		return false;
	}
	if(::Load(f,ImportanceLevel)==false){
		return false;
	}
	if(::Load(f,PieceAreaNumber)==false){
		return false;
	}
	if(::Load(f,NGSize)==false){
		return false;
	}
	return true;
}
bool	TmpNGRectClass::IsInclude(int x ,int y)
{
	if(x1<=x && x<=x2 && y1<=y && y<=y2)
		return true;
	return false;
}


class	RectClassWithCause : public TmpNGRectClass
{
public:
	QString	CauseStr;
	QString	ItemName;
};


ResultPosList::ResultPosList(void)
{
	result	=0x10000;
	ResultType			=_ResultDWORD;
	Px		=0;       
    Py		=0;

	Rx		=0;
    Ry		=0;	
	NGTypeUniqueCode	=-1;
	ImportanceLevel		=100;
	PieceAreaNumber		=-1;
	NGSize				=0;
}

ResultPosList::ResultPosList(ResultPosList &src)
{
	operator=(src);
}

ResultPosList::ResultPosList(int px ,int py)
{
	result	=0x10000;
	ResultType			=_ResultDWORD;
	Px=px;
	Py=py;
	Rx=0;
	Ry=0;
	NGTypeUniqueCode	=-1;
	ImportanceLevel		=100;
	PieceAreaNumber		=-1;
	NGSize				=0;
}

bool    ResultPosList::Load(QIODevice *f)
{
	int16	Ver;

	if(::Load(f,Ver	)==false){
		return false;
	}
	if(::Load(f,result	)==false){
		return false;
	}
	if(Ver>=4){
		BYTE	BResultType;
		if(::Load(f,BResultType	)==false){
			return false;
		}
		ResultType=(_ResultType)BResultType;
	}

	if(::Load(f,result1	)==false){
		return false;
	}
	if(::Load(f,result2	)==false){
		return false;
	}

	if(::Load(f,Px)==false){
		return false;
	}
	if(::Load(f,Py)==false){
		return false;
	}
	if(::Load(f,Rx)==false){
		return false;
	}
	if(::Load(f,Ry)==false){
		return false;
	}
	if(::Load(f,AreaNames)==false){
		return false;
	}
	if(NGShape.Load(f)==false){
		return false;
	}
	if(::Load(f,Message)==false){
		return false;
	}
	if(Vector.Load(f)==false){
		return false;
	}
	if(Ver>=2){
		if(::Load(f,ImportanceLevel)==false){
			return false;
		}
		if(::Load(f,PieceAreaNumber)==false){
			return false;
		}
	}	
	if(Ver>=3){
		if(::Load(f,NGSize)==false){
			return false;
		}
	}	

	return(true);
}
bool    ResultPosList::Save(QIODevice *f)
{
	int16	Ver=4;

	if(::Save(f,Ver	)==false){
		return false;
	}
	if(::Save(f,result	)==false){
		return false;
	}
	BYTE	BResultType=(BYTE)ResultType;
	if(::Save(f,BResultType	)==false){
		return false;
	}
	if(::Save(f,result1	)==false){
		return false;
	}
	if(::Save(f,result2	)==false){
		return false;
	}

	if(::Save(f,Px)==false){
		return false;
	}
	if(::Save(f,Py)==false){
		return false;
	}
	if(::Save(f,Rx)==false){
		return false;
	}
	if(::Save(f,Ry)==false){
		return false;
	}
	if(::Save(f,AreaNames)==false){
		return false;
	}
	if(NGShape.Save(f)==false){
		return false;
	}
	if(::Save(f,Message)==false){
		return false;
	}
	if(Vector.Save(f)==false){
		return false;
	}
	if(::Save(f,ImportanceLevel)==false){
		return false;
	}
	if(::Save(f,PieceAreaNumber)==false){
		return false;
	}
	if(::Save(f,NGSize)==false){
		return false;
	}

	return(true);
}

void    ResultPosList::Move(int dx ,int dy)
{
	Px+=dx;
	Py+=dy;
	NGShape.MoveToNoClip(dx,dy);
	Vector.MoveTo(dx,dy);
}
ResultPosList	&ResultPosList::operator=(ResultPosList &src)
{
	result		=src.result;
	ResultType	=src.ResultType;
	result1		=src.result1;
	result2		=src.result2;
	Px=src.Px;
	Py=src.Py;
	Rx=src.Rx;
	Ry=src.Ry;
	AreaNames	=src.AreaNames;
	NGShape		=src.NGShape;
	Message		=src.Message;
	Vector		=src.Vector;
	NGTypeUniqueCode	=src.NGTypeUniqueCode;
	ImportanceLevel		=src.ImportanceLevel;
	PieceAreaNumber		=src.PieceAreaNumber;
	NGSize				=src.NGSize;
	return(*this);
}

int32	ResultPosList::GetByte(void)
{
	return(sizeof(result)
		 + sizeof(ResultType)
		 + sizeof(result1)
		 + sizeof(result2)
		 + sizeof(Px)
		 + sizeof(Py)
		 + sizeof(Rx)
		 + sizeof(Ry)
		 + sizeof(NGTypeUniqueCode)
		 + sizeof(ImportanceLevel)
		 + sizeof(PieceAreaNumber)
		 + sizeof(NGSize));
}

void	ResultPosList::DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData 
									,int MovX ,int MovY ,double ZoomRate
									,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)
{
	int	R=ZoomRate;
	if(R<MinimumRadius){
		R=MinimumRadius;
	}
	int	R2=R+R;
	int	x1=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate-R;
	int y1=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate-R;
	int	x2=x1+R2;
	int	y2=y1+R2;
	if(0<=x2 && x1<IData.width() && 0<=y2 && y1<IData.height()){
		LibraryListWithNGType	*AType=NULL;
		if(parent!=NULL){
			AlgorithmItemRoot	*AItem=parent->GetAlgorithmItem();
			if(AItem!=NULL && AItem->AlgorithmItemRoot::GetCurrentResult()!=NULL){
				AlgorithmBase	*ABase=AItem->GetParentBase();
				if(ABase!=NULL){
					AType=ABase->GetNGTypeList(AItem->GetLibID());
				}
			}
		}
		if(AType!=NULL && AType->NGList.GetCount()>0){
			AType->Draw(PData,x1+R,y2+R,MinimumRadius*2);
		}
		else{
			PData.setBrush(Qt::NoBrush);
			QColor	RCol=QColor(255-qRed(Col),255-qGreen(Col),255-qBlue(Col));
			if(ImportanceLevel<100){
				if(CircleWidth==0){
					if(DrawBlueNGMark==true){
						PData.setPen(RCol);
						PData.drawEllipse(x1-4,y1-4,R2+8,R2+8);
					}
					PData.setPen(QColor(Col));
					PData.drawEllipse(x1-3,y1-3,R2+6,R2+6);
					PData.setPen(QColor(Col));
					PData.drawEllipse(x1-2,y1-2,R2+4,R2+4);
					PData.drawEllipse(x1,y1,R2,R2);
				}
				else{
					if(DrawBlueNGMark==true){
						QPen	cpen(RCol,CircleWidth);
						PData.setPen(cpen);
						PData.drawEllipse(x1-CircleWidth-3,y1-CircleWidth-3
										,R2+CircleWidth*2+6 ,R2+CircleWidth*2+6);
					}
					QPen	dpen(QColor(Col),CircleWidth);
					PData.setPen(dpen);
					PData.drawEllipse(x1-2,y1-2,R2+4,R2+4);
					PData.drawEllipse(x1,y1,R2,R2);
				}
			}
			else{
				if(CircleWidth==0){
					if(DrawBlueNGMark==true){
						PData.setPen(RCol);
						PData.drawEllipse(x1-1,y1-1,R2+2,R2+2);
					}
					PData.setPen(QColor(Col));
					PData.drawEllipse(x1,y1,R2,R2);
				}
				else{
					if(DrawBlueNGMark==true){
						QPen	cpen(RCol,CircleWidth);
						PData.setPen(cpen);
						PData.drawEllipse(x1-CircleWidth-1	,y1-CircleWidth-1
										 ,R2+CircleWidth*2+2,R2+CircleWidth*2+2);
					}
					QPen	dpen(QColor(Col),CircleWidth);
					PData.setPen(dpen);
					PData.drawEllipse(x1,y1,R2,R2);
				}
			}
		}
	}
	if(Vector.IsNull()==false){
		QRgb	LCol;
		LCol=qRgb(qRed(Col),qGreen(Col),qBlue(Col));
		Vector.DrawCircleOnLine(IData,PData,LCol,MovX+Rx ,MovY+Ry,ZoomRate,R);
	}
}
void	ResultPosList::DrawResultDetail(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
										,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)
{
	if(NGShape.IsNull()==true){
		DrawResult(parent ,IData ,PData ,MovX ,MovY ,ZoomRate,MinimumRadius,Col,CircleWidth,DrawBlueNGMark);
	}
	else{
		NGShape.DrawAlpha(parent->GetAlignedX()+Rx
						, parent->GetAlignedY()+Ry
						,&IData ,Col
						,ZoomRate ,MovX ,MovY);
	}
	if(Vector.IsNull()==false){
		QRgb	LCol;
		LCol=qRgb(qRed(Col),qGreen(Col),qBlue(Col));
		Vector.Draw(IData,PData,LCol,MovX ,MovY,ZoomRate);
	}
	if(Message.isEmpty()==false){
		int	x=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
		int y=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
		QRgb	CCol;
		CCol=qRgb(qRed(Col),qGreen(255),qBlue(Col));
		PData.setPen(CCol);
		PData.drawText(x+10,y+10,Message);
	}
}
bool	ResultPosList::IsOverlap(FlexArea &Area)
{
	if(NGShape.CheckOverlap(&Area)==true){
		return true;
	}
	if(Area.IsInclude(Px+Rx,Py+Ry)==true){
		return true;
	}
	return false;
}

void	ResultPosList::GetXY(int &x1,int &y1,int &x2,int &y2)
{
	x2=x1=Px+Rx;
	y2=y1=Py+Ry;
	if(NGShape.IsNull()==true){
		if(Vector.IsNull()==false){
			Vector.GetXY(x1,y1,x2,y2);
		}
		return;
	}
	NGShape.GetXY(x1 ,y1 ,x2 ,y2);
}


ResultPosListContainer	&ResultPosListContainer::operator=(ResultPosListContainer &src)
{
	RemoveAll();
	for(ResultPosList *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		ResultPosList	*D=new ResultPosList();
		*D= *L;
		AppendList(D);
	}
	return *this;
}

//=====================================================================================

bool	NGAreaList::Load(QIODevice *f)
{
	if(::Load(f,AreaName)==false){
		return false;
	}
	if(::Load(f,NGCount)==false){
		return false;
	}
	return true;
}


bool	NGAreaList::Save(QIODevice *f)
{
	if(::Save(f,AreaName)==false){
		return false;
	}
	if(::Save(f,NGCount)==false){
		return false;
	}
	return true;
}
NGAreaList	&NGAreaList::operator=(NGAreaList &src)
{
	AreaName=src.AreaName;
	NGCount	=src.NGCount;
	return *this;
}

bool	NGAreaListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		NGAreaList *c=new NGAreaList();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}

bool	NGAreaListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(NGAreaList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}

NGAreaListContainer	&NGAreaListContainer::operator=(NGAreaListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
NGAreaListContainer	&NGAreaListContainer::operator+=(NGAreaListContainer &src)
{
	for(NGAreaList *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		NGAreaList *d=new NGAreaList();
		*d= *c;
		AppendList(d);
	}
	return *this;
}

NGAreaList	*NGAreaListContainer::Search(const QString &areaname)
{
	for(NGAreaList *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetAreaName()==areaname){
			return c;
		}
	}
	return NULL;
}


//=====================================================================================

ResultInItemRoot::ResultInItemRoot(void)
{
	Error	=0;
	ResultType=_ResultDWORD;
	result1	=0;
	result2	=0;		
	ItemSearchedX	=0;
	ItemSearchedY	=0;
	AlignedX		=0;
    AlignedY		=0;

	ItemID			=0;
    SmallPartsID	=0;
	PosList.RemoveAll();
 
	AddedDataForRepairByte	=0;
	AddedDataForRepairType	=(DWORD)-1;
	AddedDataForRepair		=NULL;

	AddedDataByte			=0;
	AddedDataType			=(DWORD)-1;
	AddedData				=0;
	AlgorithmItemPointer	=NULL;
}

ResultInItemRoot::~ResultInItemRoot(void)
{
	PosList.RemoveAll();
	if(AddedDataForRepair!=NULL){
		delete	AddedDataForRepair;
	}
	AddedDataForRepair=NULL;
	
	if(AddedData!=NULL){
		delete	AddedData;
	}
	if(AlgorithmItemPointer!=NULL){
		if(AlgorithmItemPointer->GetCurrentResult()==this){
			AlgorithmItemPointer->SetCurrentResult(NULL);
		}
		AlgorithmItemPointer=NULL;
	}
	AddedData=NULL;
}

bool    ResultInItemRoot::Save(QIODevice *f)
{
	WORD	Ver=2;

	if(f->write((const char *)&Ver		,sizeof(Ver)	)!=sizeof(Ver	)){
		return(false);
	}
	if(f->write((const char *)&Error	,sizeof(Error)	)!=sizeof(Error	)){
		return(false);
	}
	if(f->write((const char *)&ResultType	,sizeof(ResultType))!=sizeof(ResultType)){
		return(false);
	}
	if(f->write((const char *)&result1	,sizeof(result1))!=sizeof(result1)){
		return(false);
	}
	if(f->write((const char *)&result2	,sizeof(result2))!=sizeof(result2)){
		return(false);
	}

	if(f->write((const char *)&ItemID	,sizeof(ItemID)	)!=sizeof(ItemID)){
		return(false);
	}
	if(f->write((const char *)&SmallPartsID	,sizeof(SmallPartsID))!=sizeof(SmallPartsID)){
		return(false);
	}

	if(f->write((const char *)&ItemSearchedX	,sizeof(ItemSearchedX))!=sizeof(ItemSearchedX)){
		return(false);
	}
	if(f->write((const char *)&ItemSearchedY	,sizeof(ItemSearchedY))!=sizeof(ItemSearchedY)){
		return(false);
	}
	if(f->write((const char *)&AlignedX	,sizeof(AlignedX))!=sizeof(AlignedX)){
		return(false);
	}
	if(f->write((const char *)&AlignedY	,sizeof(AlignedY))!=sizeof(AlignedY)){
		return(false);
	}

	int32	N=PosList.GetNumber();
	if(f->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(ResultPosList *P=PosList.GetFirst();P!=NULL;P=P->GetNext()){
		if(P->Save(f)==false){
			return(false);
		}
	}

	if(f->write((const char *)&AddedDataForRepairByte,sizeof(AddedDataForRepairByte))!=sizeof(AddedDataForRepairByte)){
		return(false);
	}
	if(AddedDataForRepairByte!=0 && AddedDataForRepair!=NULL){
		if(f->write((const char *)&AddedDataForRepairType,sizeof(AddedDataForRepairType))!=sizeof(AddedDataForRepairType)){
			return(false);
		}
		LogicDLL	*Logic=GetLogicDLL();
		if(Logic==NULL){
			return(false);
		}
		if(Logic->SaveAddedResultData(f,AddedDataForRepair,AddedDataForRepairType)==false){
			return(false);
		}
	}
	if(f->write((const char *)&AddedDataByte,sizeof(AddedDataByte))!=sizeof(AddedDataByte)){
		return(false);
	}
	if(AddedDataByte!=0 && AddedData!=NULL){
		if(f->write((const char *)&AddedDataType,sizeof(AddedDataType))!=sizeof(AddedDataType)){
			return(false);
		}
		LogicDLL	*Logic=GetLogicDLL();
		if(Logic==NULL){
			return(false);
		}
		if(Logic->SaveAddedResultData(f,AddedData,AddedDataType)==false){
			return(false);
		}
	}
	return(true);
}
bool    ResultInItemRoot::Load(QIODevice *f)
{
	WORD	Ver;

	if(f->read((char *)&Ver		,sizeof(Ver)	)!=sizeof(Ver	)){
		return(false);
	}
	if(f->read((char *)&Error	,sizeof(Error)	)!=sizeof(Error	)){
		return(false);
	}
	if(Ver>=2){
		if(f->read((char *)&ResultType	,sizeof(ResultType))!=sizeof(ResultType)){
			return(false);
		}
	}
	if(f->read((char *)&result1	,sizeof(result1))!=sizeof(result1)){
		return(false);
	}
	if(f->read((char *)&result2	,sizeof(result2))!=sizeof(result2)){
		return(false);
	}

	if(f->read((char *)&ItemID	,sizeof(ItemID)	)!=sizeof(ItemID)){
		return(false);
	}
	if(f->read((char *)&SmallPartsID	,sizeof(SmallPartsID))!=sizeof(SmallPartsID)){
		return(false);
	}

	if(f->read((char *)&ItemSearchedX	,sizeof(ItemSearchedX))!=sizeof(ItemSearchedX)){
		return(false);
	}
	if(f->read((char *)&ItemSearchedY	,sizeof(ItemSearchedY))!=sizeof(ItemSearchedY)){
		return(false);
	}
	if(f->read((char *)&AlignedX		,sizeof(AlignedX))!=sizeof(AlignedX)){
		return(false);
	}
	if(f->read((char *)&AlignedY		,sizeof(AlignedY))!=sizeof(AlignedY)){
		return(false);
	}

	int32	N;
	if(f->read((char *)&N	,sizeof(N))!=sizeof(N)){
		return(false);
	}
	PosList.RemoveAll();
	for(int i=0;i<N;i++){
		ResultPosList *r=new ResultPosList();
		if(r->Load(f)==false){
			return(false);
		}
		PosList.AppendList(r);
	}

	if(f->read((char *)&AddedDataForRepairByte,sizeof(AddedDataForRepairByte))!=sizeof(AddedDataForRepairByte)){
		return(false);
	}
	if(AddedDataForRepairByte!=0){
		LogicDLL	*Logic=GetLogicDLL();
		if(Logic==NULL){
			return(false);
		}
		if(AddedDataForRepair!=NULL){
			Logic->RemoveAddedResultData(AddedDataForRepair);
		}
		if(f->read((char *)&AddedDataForRepairType,sizeof(AddedDataForRepairType))!=sizeof(AddedDataForRepairType)){
			return(false);
		}
		AddedDataForRepair=Logic->LoadAddedResultData(f,AddedDataForRepairType);
		if(AddedDataForRepair==NULL){
			return(false);
		}
	}
	else{
		if(AddedDataForRepair!=NULL){
			LogicDLL	*Logic=GetLogicDLL();
			if(Logic==NULL){
				return(false);
			}
			Logic->RemoveAddedResultData(AddedDataForRepair);
		}
		AddedDataForRepair=NULL;
	}

	if(f->read((char *)&AddedDataByte,sizeof(AddedDataByte))!=sizeof(AddedDataByte)){
		return(false);
	}
	if(AddedDataByte!=0){
		LogicDLL	*Logic=GetLogicDLL();
		if(Logic==NULL){
			return(false);
		}
		if(AddedData!=NULL){
			Logic->RemoveAddedResultData(AddedData);
		}

		if(f->read((char *)&AddedDataType,sizeof(AddedDataType))!=sizeof(AddedDataType)){
			return(false);
		}
		AddedData=Logic->LoadAddedResultData(f,AddedDataType);
		if(AddedData==NULL){
			return(false);
		}
	}
	else{
		if(AddedData!=NULL){
			LogicDLL	*Logic=GetLogicDLL();
			if(Logic==NULL){
				return(false);
			}
			Logic->RemoveAddedResultData(AddedData);
		}
		AddedData=NULL;
	}
	return(true);
}
bool	ResultInItemRoot::GetDistanceVector(int x ,int y ,double &RetLength)
{
	bool	Ret=false;
	RetLength=99999999;
	for(ResultPosList *p=PosList.GetFirst();p!=NULL;p=p->GetNext()){
		double	D=p->Vector.GetDistance(x ,y);
		if(D<RetLength){
			Ret=true;
			RetLength=D;
		}
	}
	return Ret;
}
bool	ResultInItemRoot::GetDistanceArea(int x ,int y,double &RetLength)
{
	RetLength=99999999;
	bool	Ret=false;
	for(ResultPosList *p=PosList.GetFirst();p!=NULL;p=p->GetNext()){
		int	X=p->Px+p->Rx;
		int	Y=p->Py+p->Ry;
		double	D=hypot(X-x,Y-y);
		if(RetLength>D){
			RetLength=D;
			Ret=true;
		}
	}
	return Ret;
}
void    ResultInItemRoot::Move(int dx ,int dy)
{
	for(ResultPosList *P=PosList.GetFirst();P!=NULL;P=P->GetNext()){
		P->Move(dx,dy);
	}
}

BYTE	ResultInItemRoot::GetResultByte(int Index)
{
	if(0<=Index && Index<8)
		return ResultB.ResultB[Index];
	return 0;
}

void	ResultInItemRoot::SetResultByte(int Index ,BYTE d)
{
	if(0<=Index && Index<8)
		ResultB.ResultB[Index]=d;
}


WORD	ResultInItemRoot::GetResultWord(int Index)
{
	if(0<=Index && Index<4)
		return ResultW.ResultW[Index];
	return 0;
}

void	ResultInItemRoot::SetResultWord(int Index ,WORD d)
{
	if(0<=Index && Index<4)
		ResultW.ResultW[Index]=d;
}


ResultInItemRoot  &ResultInItemRoot::operator=(ResultInItemRoot &src)
{
	Error		=src.Error;
	ResultType	=src.ResultType;
	result1		=src.result1;
	result2		=src.result2;
	ResultQInt	=src.ResultQInt;

	ItemID	=src.ItemID;
    SmallPartsID=src.SmallPartsID;

	ItemSearchedX=src.ItemSearchedX;
	ItemSearchedY=src.ItemSearchedY;
	AlignedX=src.AlignedX;
	AlignedY=src.AlignedY;

	PosList.RemoveAll();
	for(ResultPosList *P=src.PosList.GetFirst();P!=NULL;P=P->GetNext()){
		ResultPosList *Q=new ResultPosList();
		*Q= *P;
		PosList.AppendList(Q);
	}

	LogicDLL	*Logic=GetLogicDLL();
	if(Logic!=NULL){
		AddedDataForRepairByte=src.AddedDataForRepairByte;
		if(AddedDataForRepair!=NULL){
			Logic->RemoveAddedResultData(AddedDataForRepair);
		}
		if(src.AddedDataForRepair!=NULL){
			QBuffer	buff;
			buff.open(QIODevice::ReadWrite);
			if(Logic->SaveAddedResultData(&buff,src.AddedDataForRepair,src.AddedDataForRepairType)==true){
				AddedDataForRepairType=src.AddedDataForRepairType;
				buff.seek(0);
				AddedDataForRepair=Logic->LoadAddedResultData(&buff,AddedDataForRepairType);
			}
		}
		AddedDataByte=src.AddedDataByte;
		if(AddedData!=NULL){
			Logic->RemoveAddedResultData(AddedData);
		}
		if(src.AddedData!=NULL){
			QBuffer	buff;
			buff.open(QIODevice::ReadWrite);
			if(Logic->SaveAddedResultData(&buff,src.AddedData,src.AddedDataType)==true){
				AddedDataType=src.AddedDataType;
				buff.seek(0);
				AddedData=Logic->LoadAddedResultData(&buff,AddedDataType);
			}
		}
	}

	return(*this);
}

int32	ResultInItemRoot::GetByte(void)
{
	int32	ret	=sizeof(Error)
				+sizeof(ResultType)
				+sizeof(result1)
				+sizeof(result2)

				+ sizeof(ItemSearchedX)
				+ sizeof(ItemSearchedY)
				+ sizeof(AlignedX)
				+ sizeof(AlignedY)
				+sizeof(ItemID)	
				+sizeof(SmallPartsID);

	for(ResultPosList *P=PosList.GetFirst();P!=NULL;P=P->GetNext()){
		ret+=P->GetByte();
	}

	ret+=sizeof(AddedDataForRepairByte);
	if(AddedDataForRepair!=NULL){
		ret+=AddedDataForRepairByte;
	}
	
	ret+=sizeof(AddedDataByte);
	if(AddedData!=NULL){
		ret+=AddedDataByte;
	}
	return(ret);
}

void	ResultInItemRoot::InitialInspection(void)
{
	Error=0;
	PosList.RemoveAll();
}

QString	ResultInItemRoot::GetPosString(void)
{
	int	AddX=0;
	int	AddY=0;
	int	N=0;
	for(ResultPosList *p=PosList.GetFirst();p!=NULL;p=p->GetNext()){
		AddX+=p->Px;
		AddY+=p->Py;
		N++;
	}
	if(N==0){
		return(QString(LangLibSolver.GetString(XResult_LS,LID_343)/*"Nothing"*/));
	}
	AddX/=N;
	AddY/=N;
	return(QString::number(AddX)+QString(LangLibSolver.GetString(XResult_LS,LID_344)/*","*/)+QString::number(AddY));
}

void	ResultInItemRoot::GetCenter(int &cx, int &cy)
{
	int	AddX=0;
	int	AddY=0;
	int	N=0;
	for(ResultPosList *p=PosList.GetFirst();p!=NULL;p=p->GetNext() ,N++){
		AddX+=p->Px;
		AddY+=p->Py;
	}
	if(N==0){
		AlgorithmItemRoot	*Item=GetAlgorithmItem();
		if(Item!=NULL){
			Item->GetCenter(cx,cy);
		}
		else{
			cx=cy=0;
		}
	}
	else{
		cx=AddX/N;
		cy=AddY/N;
	}
}

QString	ResultInItemRoot::ResultItemToString(void)
{
	LogicDLL	*a=GetLogicDLL();
	if(a!=NULL){
		char	Buff[1000];
		if(a->ResultItemToString(this,Buff,sizeof(Buff)-1)==true){
			Buff[sizeof(Buff)-1]=0;
			return QString(Buff);
		}
	}
	return /**/"";
}

bool	ResultInItemRoot::IsNGNearXY(FlexArea &area)
{
	if(Error>=2){
		for(ResultPosList *p=PosList.GetFirst();p!=NULL;p=p->GetNext()){
			if(area.IsInclude(p->Px,p->Py)==true){
				return true;
			}
		}
	}
	return false;
}

void	ResultInItemRoot::BindNGAreaListContainer(NGAreaListContainer &List)
{
	if(Error>=2){
		for(ResultPosList *s=PosList.GetFirst();s!=NULL;s=s->GetNext()){
			for(int i=0;i<s->AreaNames.count();i++){
				QString	AName=s->AreaNames[i];
				if(AName.isEmpty()==false){
					NGAreaList	*c=List.Search(AName);
					if(c==NULL){
						NGAreaList	*d=new NGAreaList(AName,1);
						List.AppendList(d);
					}
					else{
						c->SetNGCount(c->GetNGCount()+1);
					}
				}
			}
		}
	}
}

bool	ResultInItemRoot::IsOverlap(FlexArea &Area)
{
	for(ResultPosList *r=PosList.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsOverlap(Area)==true){
			return true;
		}
	}
	return false;
}

int		ResultInItemRoot::GetNGPointCount(void)
{
	return PosList.GetCount();
}

void	ResultInItemRoot::ReviveResult(LearningImage *c)
{
	for(ResultPosList *r=PosList.GetFirst();r!=NULL;){
		ResultPosList *NextR=r->GetNext();
		if(c->IsIncludeOrg(r->Px,r->Py)==true){
			PosList.RemoveList(r);
			delete	r;
		}
		r=NextR;
	}
	if(PosList.GetFirst()==NULL){
		SetError(1);
	}
}

int	ResultInItemRoot::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(ResultPosList *r=PosList.GetFirst();r!=NULL;r=r->GetNext()){
		if(OverlapArea.IsInclude(r->Px,r->Py)==true){
			if(N<MaxCount){
				RetDim[N]=r;
				N++;
			}
		}
	}
	return N;
}

//=============================================================================================
NGImage::NGImage(void)
{
	SrcImage[0]		=NULL;
	SrcImage[1]		=NULL;
	SrcImage[2]		=NULL;
	SrcImageXLen	=0;
	SrcImageYLen	=0;
    CompressedPtn	=NULL;
    PtnByte			=0;
	GlobalPage		=0;
	Number			=0;
    x1=0;
	y1=0;
	x2=0;
	y2=0;
	Mx=0;
	My=0;
	SuccessCompress=false;
	TmpLinearBuff	=NULL;
	AllocatedLinearBuffSize	=0;

}
NGImage::~NGImage(void)
{
	if(CompressedPtn!=NULL){
		delete	[]CompressedPtn;
	}
	CompressedPtn=NULL;
	PtnByte	=0;
	for(int i=0;i<3;i++){
		if(SrcImage[i]!=NULL){
			DeleteMatrixBuff(SrcImage[i],SrcImageYLen);
		}
		SrcImage[i]=NULL;
	}
	if(TmpLinearBuff!=NULL){
		delete	[]TmpLinearBuff;
		TmpLinearBuff=NULL;
	}
	AllocatedLinearBuffSize	=0;
}

int		AlarmNGImage=0;
bool    NGImage::SaveJDT(QIODevice *f,int offsetX, int offsetY)
{
	DWORD	Ver=Version_NGImage;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(::Save(f,Number)==false){
		return false;
	}
	if(::Save(f,x1+offsetX)==false){
		return false;
	}
	if(::Save(f,y1+offsetY)==false){
		return false;
	}
	if(::Save(f,x2+offsetX)==false){
		return false;
	}
	if(::Save(f,y2+offsetY)==false){
		return false;
	}
	if(::Save(f,PtnByte)==false){
		return false;
	}
	if(PtnByte==0){
		AlarmNGImage++;
	}
	if(PtnByte!=0 && CompressedPtn!=NULL){
		if(f->write((const char *)CompressedPtn	,PtnByte)!=PtnByte){
			return(false);
		}
	}
	/*
	if(::Save(f,Mx)==false){
		return false;
	}
	if(::Save(f,My)==false){
		return false;
	}
	*/
	return(true);    
}
bool    NGImage::LoadJDT(QIODevice *f)
{
	DWORD	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	if(::Load(f,Number)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,PtnByte)==false){
		return false;
	}
	if(PtnByte!=0){
		if(CompressedPtn!=NULL){
			delete	[]CompressedPtn;
		}
		CompressedPtn=new BYTE[PtnByte];
		if(f->read((char *)CompressedPtn	,PtnByte)!=PtnByte){
			return(false);
		}
	}
	/*
	if(::Load(f,Mx)==false){
		return false;
	}
	if(::Load(f,My)==false){
		return false;
	}
	*/
	return(true);    
}

bool    NGImage::SaveRawImage(QIODevice *f,int offsetX, int offsetY)
{
	DWORD	Ver=Version_NGImage;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(::Save(f,Number)==false){
		return false;
	}
	if(::Save(f,x1+offsetX)==false){
		return false;
	}
	if(::Save(f,y1+offsetY)==false){
		return false;
	}
	if(::Save(f,x2+offsetX)==false){
		return false;
	}
	if(::Save(f,y2+offsetY)==false){
		return false;
	}
	if(::Save(f,SrcImageXLen)==false){
		return false;
	}
	if(::Save(f,SrcImageYLen)==false){
		return false;
	}
	for(int layer=0;layer<3;layer++){
		if(::Save(f,SrcImage[layer],SrcImageXLen,SrcImageYLen)==false)
			return false;
	}
	return(true);    
}
bool    NGImage::LoadRawImage(QIODevice *f)
{
	DWORD	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	if(::Load(f,Number)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	for(int layer=0;layer<3;layer++){
		if(SrcImage[layer]!=NULL){
			DeleteMatrixBuff(SrcImage[layer],SrcImageYLen);
			SrcImage[layer]=NULL;
		}
	}
	if(::Load(f,SrcImageXLen)==false){
		return false;
	}
	if(::Load(f,SrcImageYLen)==false){
		return false;
	}
	for(int layer=0;layer<3;layer++){
		SrcImage[layer]=MakeMatrixBuff(SrcImageXLen,SrcImageYLen);
		if(::Load(f,SrcImage[layer],SrcImageXLen,SrcImageYLen)==false){
			return false;
		}
	}
	return(true);    
}
bool    NGImage::Save(QIODevice *f,int offsetX, int offsetY)
{
	DWORD	Ver=Version_NGImage;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(::Save(f,Number)==false){
		return false;
	}
	if(::Save(f,x1+offsetX)==false){
		return false;
	}
	if(::Save(f,y1+offsetY)==false){
		return false;
	}
	if(::Save(f,x2+offsetX)==false){
		return false;
	}
	if(::Save(f,y2+offsetY)==false){
		return false;
	}
	if(::Save(f,PtnByte)==false){
		return false;
	}
	if(PtnByte==0){
		AlarmNGImage++;
	}
	if(PtnByte!=0 && CompressedPtn!=NULL){
		if(f->write((const char *)CompressedPtn	,PtnByte)!=PtnByte){
			return(false);
		}
	}
	if(::Save(f,Mx)==false){
		return false;
	}
	if(::Save(f,My)==false){
		return false;
	}

	if(::Save(f,SrcImageXLen)==false){
		return false;
	}
	if(::Save(f,SrcImageYLen)==false){
		return false;
	}
	for(int i=0;i<3;i++){
		bool	ImageNull=(SrcImage[i]==NULL)?true:false;
		if(::Save(f,ImageNull)==false){
			return false;
		}
		if(ImageNull==false){
			if(::Save(f,SrcImage[i],SrcImageXLen ,SrcImageYLen)==false){
				return false;
			}
		}
	}
	return(true);    
}
bool    NGImage::Load(QIODevice *f)
{
	DWORD	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	if(::Load(f,Number)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,PtnByte)==false){
		return false;
	}
	if(PtnByte!=0){
		if(CompressedPtn!=NULL){
			delete	[]CompressedPtn;
		}
		CompressedPtn=new BYTE[PtnByte];
		if(f->read((char *)CompressedPtn	,PtnByte)!=PtnByte){
			return(false);
		}
	}
	if(::Load(f,Mx)==false){
		return false;
	}
	if(::Load(f,My)==false){
		return false;
	}
	if(Ver>=4){
		if(::Load(f,SrcImageXLen)==false){
			return false;
		}
		if(::Load(f,SrcImageYLen)==false){
			return false;
		}
		for(int i=0;i<3;i++){
			if(SrcImage[i]!=NULL){
				DeleteMatrixBuff(SrcImage[i],SrcImageYLen);
			}
			bool	ImageNull;
			if(::Load(f,ImageNull)==false){
				return false;
			}
			if(ImageNull==false){
				SrcImage[i]=MakeMatrixBuff(SrcImageXLen ,SrcImageYLen);
				if(::Load(f,SrcImage[i],SrcImageXLen ,SrcImageYLen)==false){
					return false;
				}
			}
			else{
				SrcImage[i]=NULL;
			}
		}
	}
	return(true);    
}

int     NGImage::GetByte(void)
{
    int	ret	=sizeof(PtnByte)
			+PtnByte
			+sizeof(GlobalPage)
			+sizeof(Number)
			+sizeof(x1)
			+sizeof(y1)
			+sizeof(x2)
			+sizeof(y2)
			+sizeof(Mx)
			+sizeof(My);
	return(ret);
}
NGImage &NGImage::operator=(NGImage &src)
{	
	if(PtnByte==src.PtnByte){
		if(PtnByte!=0){
			memcpy(CompressedPtn,src.CompressedPtn,PtnByte);
		}
	}
	else{
	    PtnByte		=src.PtnByte;
		if(CompressedPtn!=NULL){
			delete	[]CompressedPtn;
		}
		if(PtnByte!=0){
			CompressedPtn=new BYTE[PtnByte];
			memcpy(CompressedPtn,src.CompressedPtn,PtnByte);
		}
		else{
			CompressedPtn=NULL;
		}
	}
	GlobalPage		=src.GlobalPage;
	Number			=src.Number;
    x1				=src.x1;
	y1				=src.y1;
	x2				=src.x2;
	y2				=src.y2;
	Mx				=src.Mx;
	My				=src.My;
	SuccessCompress	=src.SuccessCompress;

	if(SrcImageXLen!=src.SrcImageXLen 
	|| SrcImageYLen!=src.SrcImageYLen 
	|| IsNullPointer(SrcImage[0])!=IsNullPointer(src.SrcImage[0])
	|| IsNullPointer(SrcImage[1])!=IsNullPointer(src.SrcImage[1])
	|| IsNullPointer(SrcImage[2])!=IsNullPointer(src.SrcImage[2])){
		for(int i=0;i<3;i++){
			if(SrcImage[i]!=NULL){
				DeleteMatrixBuff(SrcImage[i],SrcImageYLen);
			}
			if(IsNullPointer(src.SrcImage[i])==false){
				SrcImage[i]=MakeMatrixBuff(src.SrcImageXLen ,src.SrcImageYLen);
			}
			else{
				SrcImage[i]=NULL;
			}
		}

	}
	SrcImageXLen=src.SrcImageXLen;
	SrcImageYLen=src.SrcImageYLen;
	for(int i=0;i<3;i++){
		SrcImage[i]=MakeMatrixBuff(SrcImageXLen ,SrcImageYLen);
		 MatrixBuffCopy	(SrcImage[i]					,SrcImageXLen ,SrcImageYLen
						,(const BYTE **)src.SrcImage[i]	,SrcImageXLen ,SrcImageYLen);
	}
	return(*this);
}

bool	NGImage::AllocateBuffer(int LayerNumb)
{
	if(LayerNumb==0){
		return false;
	}
	if(LayerNumb==1){
		if(SrcImage[0]!=NULL){
			if(SrcImageXLen!=GetWidth() || SrcImageYLen!=GetHeight()){
				DeleteMatrixBuff(SrcImage[0],SrcImageYLen);
				SrcImage[0]=NULL;
			}
		}
		if(SrcImage[0]==NULL){
			SrcImageXLen=GetWidth();
			SrcImageYLen=GetHeight();
			SrcImage[0]=MakeMatrixBuff(SrcImageXLen ,SrcImageYLen);
		}
	}
	if(LayerNumb==2){
		for(int i=0;i<2;i++){
			if(SrcImage[i]!=NULL){
				if(SrcImageXLen!=GetWidth() || SrcImageYLen!=GetHeight()){
					DeleteMatrixBuff(SrcImage[i],SrcImageYLen);
					SrcImage[i]=NULL;
				}
			}
		}
		SrcImageXLen=GetWidth();
		SrcImageYLen=GetHeight();
		for(int i=0;i<2;i++){
			if(SrcImage[i]==NULL){
				SrcImage[i]=MakeMatrixBuff(SrcImageXLen ,SrcImageYLen);
			}
		}
	}
	if(LayerNumb>=3){
		for(int i=0;i<3;i++){
			if(SrcImage[i]!=NULL){
				if(SrcImageXLen!=GetWidth() || SrcImageYLen!=GetHeight()){
					DeleteMatrixBuff(SrcImage[i],SrcImageYLen);
					SrcImage[i]=NULL;
				}
			}
		}
		SrcImageXLen=GetWidth();
		SrcImageYLen=GetHeight();
		for(int i=0;i<3;i++){
			if(SrcImage[i]==NULL){
				SrcImage[i]=MakeMatrixBuff(SrcImageXLen ,SrcImageYLen);
			}
		}
	}
	return true;
}

void	NGImage::CopyImageFromTarget(DataInPage *PData)
{
	AllocateBuffer(PData->GetLayerNumb());
	if(PData->GetLayerNumb()==1){
		ImageBuffer	&P0=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(0)->GetRawTargetBuff():PData->GetLayerData(0)->GetTargetBuff();
		for(int y=0;y<SrcImageYLen;y++){
			BYTE	*src=P0.GetY(y1+y)+x1;
			memcpy(SrcImage[0][y],src,SrcImageXLen);
		}
	}
	if(PData->GetLayerNumb()==2){
		ImageBuffer	&P0=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(0)->GetRawTargetBuff():PData->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	&P1=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(1)->GetRawTargetBuff():PData->GetLayerData(1)->GetTargetBuff();
		for(int y=0;y<SrcImageYLen;y++){
			BYTE	*src0=P0.GetY(y1+y)+x1;
			BYTE	*src1=P1.GetY(y1+y)+x1;
			memcpy(SrcImage[0][y],src0,SrcImageXLen);
			memcpy(SrcImage[1][y],src1,SrcImageXLen);
		}
	}
	if(PData->GetLayerNumb()>=3){
		ImageBuffer	&P0=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(0)->GetRawTargetBuff():PData->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	&P1=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(1)->GetRawTargetBuff():PData->GetLayerData(1)->GetTargetBuff();
		ImageBuffer	&P2=(PData->GetParamGlobal()->AllocRawTargetBuffForNGImage==true && PData->GetParamGlobal()->AdoptRawForResultImage==true)?PData->GetLayerData(2)->GetRawTargetBuff():PData->GetLayerData(2)->GetTargetBuff();
		for(int y=0;y<SrcImageYLen;y++){
			BYTE	*src0=P0.GetY(y1+y)+x1;
			BYTE	*src1=P1.GetY(y1+y)+x1;
			BYTE	*src2=P2.GetY(y1+y)+x1;
			memcpy(SrcImage[0][y],src0,SrcImageXLen);
			memcpy(SrcImage[1][y],src1,SrcImageXLen);
			memcpy(SrcImage[2][y],src2,SrcImageXLen);
		}
	}
}

bool	NGImage::IsOverlapped(FlexArea &Area)
{
	if(Area.CheckOverlapRectangle(x1,y1,x2,y2)==true){
		return true;
	}
	return false;
}

void	NGImage::MoveTo(int dx,int dy)
{
	x1+=dx;
	y1+=dy;
	x2+=dx;
	y2+=dy;
}


//=============================================================================================
ErrorGroup::ErrorGroup(LayersBase *Base)
:ServiceForLayers(Base)
{	
	x1=0;
	y1=0;	
	x2=0;
	y2=0;
	Page=0;
	mx=0;
	my=0;
	ImportanceLevel	=100;
	PieceAreaNumber	=-1;
	NGSize			=0;
	SentCompressor	=false;
}

ErrorGroup  &ErrorGroup::operator=(ErrorGroup &src)
{
    x1=src.x1;
    y1=src.y1;
    x2=src.x2;
    y2=src.y2;
	mx=src.mx;
	my=src.my;
	Page=src.Page;
	Name=src.Name;
	Cause	=src.Cause;
	ImportanceLevel	=src.ImportanceLevel;
	PieceAreaNumber	=src.PieceAreaNumber;
	NGSize			=src.NGSize;
	SentCompressor	=src.SentCompressor;
	
	return(*this);
}
bool    ErrorGroup::Load(QIODevice *f)
{
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,Name)==false){
		return false;
	}
	if(::Load(f,Cause)==false){
		return false;
	}
	if(::Load(f,mx)==false){
		return false;
	}
	if(::Load(f,my)==false){
		return false;
	}
	if(::Load(f,ImportanceLevel)==false){
		return false;
	}
	if(::Load(f,PieceAreaNumber)==false){
		return false;
	}
	if(::Load(f,NGSize)==false){
		return false;
	}
	return true;
}
bool    ErrorGroup::Save(QIODevice *f)
{
	if(::Save(f,x1)==false){
		return false;
	}
	if(::Save(f,y1)==false){
		return false;
	}
	if(::Save(f,x2)==false){
		return false;
	}
	if(::Save(f,y2)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,Name)==false){
		return false;
	}
	if(::Save(f,Cause)==false){
		return false;
	}
	if(::Save(f,mx)==false){
		return false;
	}
	if(::Save(f,my)==false){
		return false;
	}
	if(::Save(f,ImportanceLevel)==false){
		return false;
	}
	if(::Save(f,PieceAreaNumber)==false){
		return false;
	}
	if(::Save(f,NGSize)==false){
		return false;
	}
	return true;
}
QString	ErrorGroup::GetName(void)
{	
	return Name;
}
void	ErrorGroup::SetName(const QString &name)
{	
	Name=name;
}

ErrorGroupPack  &ErrorGroupPack::operator=(ErrorGroupPack &src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
ErrorGroupPack  &ErrorGroupPack::operator+=(ErrorGroupPack &src)
{
	for(ErrorGroup *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		ErrorGroup *d=new ErrorGroup(c->GetLayersBase());
		*d= *c;
		AppendList(d);
	}
	return *this;
}
bool    ErrorGroupPack::Load(QIODevice *f,LayersBase *Base)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ErrorGroup *c=new ErrorGroup(Base);
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}
bool    ErrorGroupPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ErrorGroup *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}


//=============================================================================================
/*
ResultByAlgorithm::ResultByAlgorithm(ResultInLayer *parent ,int32 attr)
{
	Parent				=parent;
	Attr				=attr;
	AllocatedResultNumb	=0;
	Result				=NULL;
	NGImageData.RemoveAll();	
	TimeOutBreak		=false;
	MaxErrorBreak		=false;
	DynamicLogicID		=0;
}
ResultByAlgorithm::~ResultByAlgorithm(void)
{
	if(Result!=NULL)
		delete	[]Result;
	Result=NULL;
	NGImageData.RemoveAll();	
}

void	ResultByAlgorithm::InitialAllocate(int N)
{
	if(Result!=NULL)
		delete	[]Result;
	AllocatedResultNumb=N;
	Result=new ResultData[AllocatedResultNumb];
	for(int i=0;i<AllocatedResultNumb;i++){
		Result[i].Parent=this;
	}
}

int		ResultByAlgorithm::GetNGNumber(void)
{
	int	N=0;
	for(int i=0;i<AllocatedResultNumb;i++){
		if(Result[i].Error>=2)
			N++;
	}
	return(N);
}
bool    ResultByAlgorithm::Save(QIODevice *f)
{
	WORD	Ver=1;

    if(f->write((const char *)&Ver		,sizeof(Ver)	)!=sizeof(Ver))
		return(false);
    if(f->write((const char *)&Attr			,sizeof(Attr			))!=sizeof(Attr			))
		return(false);
    if(f->write((const char *)&TimeOutBreak	,sizeof(TimeOutBreak	))!=sizeof(TimeOutBreak	))
		return(false);
    if(f->write((const char *)&MaxErrorBreak,sizeof(MaxErrorBreak	))!=sizeof(MaxErrorBreak))
		return(false);
    if(f->write((const char *)&AllocatedResultNumb	,sizeof(AllocatedResultNumb)	)!=sizeof(AllocatedResultNumb))
		return(false);
    if(f->write((const char *)&DynamicLogicID	,sizeof(DynamicLogicID)	)!=sizeof(DynamicLogicID))
		return(false);
	for(int i=0;i<AllocatedResultNumb;i++){
		if(Result[i].Save(f)==false)
			return(false);
	}
	int32	N=NGImageData.GetNumber();
    if(f->write((const char *)&N	,sizeof(N)	)!=sizeof(N))
		return(false);
	for(NGImage *a=NGImageData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return(false);
	}
	return(true);
}

bool    ResultByAlgorithm::Load(QIODevice *f)
{
	WORD	Ver;

    if(f->read((char *)&Ver		,sizeof(Ver)	)!=sizeof(Ver))
		return(false);
    if(f->read((char *)&Attr			,sizeof(Attr			))!=sizeof(Attr			))
		return(false);
    if(f->read((char *)&TimeOutBreak	,sizeof(TimeOutBreak	))!=sizeof(TimeOutBreak	))
		return(false);
    if(f->read((char *)&MaxErrorBreak,sizeof(MaxErrorBreak	))!=sizeof(MaxErrorBreak))
		return(false);
    if(f->read((char *)&AllocatedResultNumb	,sizeof(AllocatedResultNumb)	)!=sizeof(AllocatedResultNumb))
		return(false);
    if(f->read((char *)&DynamicLogicID	,sizeof(DynamicLogicID)	)!=sizeof(DynamicLogicID))
		return(false);
	InitialAllocate(AllocatedResultNumb);

	for(int i=0;i<AllocatedResultNumb;i++){
		if(Result[i].Load(f)==false)
			return(false);
	}
	int32	N;
    if(f->read((char *)&N	,sizeof(N)	)!=sizeof(N))
		return(false);
	NGImageData.RemoveAll();
	for(int i=0;i<N;i++){
		NGImage *a=new NGImage();
		if(a->Load(f)==false)
			return(false);
		NGImageData.AppendList(a);
	}
	return(true);
}

void	ResultByAlgorithm::MakeErrorGroup(NPListPack<ErrorGroup> &ErrorGroupData)
{
}

void	ResultByAlgorithm::InitialInspection(void)
{
	for(int i=0;i<AllocatedResultNumb;i++){
		Result[i].InitialInspection();
	}
	NGImageData.RemoveAll();
}
*/

//=============================================================================================
ResultInLayerRoot::ResultInLayerRoot(DataInLayer *pDataInLayer)
:ServiceForLayers(pDataInLayer->GetLayersBase())
{
	//PDataInLayer	=pDataInLayer;
	Layer	=0;
	AlgoPointer		=NULL;
}
ResultInLayerRoot::~ResultInLayerRoot(void)
{
}

bool    ResultInLayerRoot::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false ;
	}
	return(true);
}
bool    ResultInLayerRoot::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return(false);
	}
	return(true);
}

int		ResultInLayerRoot::GetPage(void)
{
	return GetAlgorithmInPage()->GetPage();
}
int		ResultInLayerRoot::GetPhaseCode(void)
{
	return GetAlgorithmInPage()->GetPhaseCode();
}

//=============================================================================================
ResultInPageRoot::ResultInPageRoot(ResultBasePhase *pPhaseParent,DataInPage *pDataInPage)
:ServiceForLayers(pDataInPage->GetLayersBase()) ,PhaseParent(pPhaseParent)
{
	Page			=0;
	PDataInPage		=pDataInPage;
	AlgoPointer		=NULL;
}
ResultInPageRoot::~ResultInPageRoot(void)
{
}

bool    ResultInPageRoot::Save(QIODevice *file)
{
	if(::Save(file,Page)==false){
		return(false);
	}
	return(true);
}
bool    ResultInPageRoot::Load(QIODevice *file)
{
	if(::Load(file,Page)==false){
		return(false);
	}
	return(true);
}

LayersBase	*ResultInPageRoot::GetLayersBase(void)
{	
	return PDataInPage->GetLayersBase();	
}

void	ResultInPageRoot::CalcNGCounterAgain(void)
{
	DataInPage	*P=GetDataInPage();
	P->AddNGCounter(GetNGCount());
}
DataInPage		*ResultInPageRoot::GetDataInPage(void)
{
	return GetLayersBase()->GetPageData(GetPage());
}

int	ResultInPageRoot::GetPhaseCode(void)
{
	return PDataInPage->GetPhaseCode();	
}

//=============================================================================================
ResultBasePhase::ResultBasePhase(int phaseCode ,ResultBaseForAlgorithmRoot *parent)
{
	PhaseCode		=phaseCode;
	Parent			=parent;
	AllocPageNumb	=0;
	PageData		=NULL;
	AlgoPointer		=NULL;
}
ResultBasePhase::~ResultBasePhase(void)
{
	Release();
}

bool	ResultBasePhase::Initial(ResultBaseForAlgorithmRoot *p)
{
	AlgoPointer	=p->GetAlgorithm()->GetPageDataPhase(PhaseCode);
	if(AllocPageNumb!=p->GetParamGlobal()->PageNumb){
		Release();
		AllocPageNumb=p->GetParamGlobal()->PageNumb;
		PageData=new ResultInPageRoot*[AllocPageNumb];
		for(int L=0;L<AllocPageNumb;L++){
			PageData[L]=p->CreatePage(PhaseCode,L);
			PageData[L]->SetPage(L);
		}
	}
	for(int L=0;L<AllocPageNumb;L++){
		//PageData[L]->PhaseParent=this;
		PageData[L]->SetPage(L);
		if(PageData[L]->Initial(p)==false)
			return false;
	}
	return true;
}
void	ResultBasePhase::Release(void)
{
	for(int L=0;L<AllocPageNumb;L++){
		delete	PageData[L];
	}
	if(PageData!=NULL){
		delete	[]PageData;
	}
	PageData=NULL;
	AllocPageNumb=0;
}
bool	ResultBasePhase::Reallocate(int newPageNumb ,int newLayerNumb)
{
	AlgoPointer	=Parent->GetAlgorithm()->GetPageDataPhase(PhaseCode);
	if(AllocPageNumb<newPageNumb){
		ResultInPageRoot	**tPageData=new ResultInPageRoot*[newPageNumb];
		int	i;
		for(i=0;i<AllocPageNumb;i++){
			if(PageData[i]==NULL){
				break;
			}
			tPageData[i]=PageData[i];
			tPageData[i]->Reallocate(newLayerNumb);
		}
		delete	[]PageData;
		PageData=tPageData;
		for(;i<newPageNumb;i++){
			PageData[i]=Parent->CreatePage(PhaseCode,i);
			//PageData[i]->Parent=this;
			PageData[i]->SetPage(i);
			PageData[i]->Initial(Parent);
		}
	}
	else if(AllocPageNumb>newPageNumb){
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=Parent->CreatePage(PhaseCode,i);
				//PageData[i]->Parent=this;
				PageData[i]->SetPage(i);
				PageData[i]->Initial(Parent);
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
		for(int i=newPageNumb;i<AllocPageNumb;i++){
			if(PageData[i]!=NULL){
				delete	PageData[i];
				PageData[i]=NULL;
			}
		}
		AllocPageNumb	=newPageNumb;
	}
	else{
		for(int i=0;i<newPageNumb;i++){
			if(PageData[i]==NULL){
				PageData[i]=Parent->CreatePage(PhaseCode,i);
				//PageData[i]->Parent=this;
				PageData[i]->SetPage(i);
				PageData[i]->Initial(Parent);
			}
			else{
				PageData[i]->Reallocate(newLayerNumb);
			}
		}
	}
	return true;
}
void	ResultBasePhase::MoveMerge(ResultBaseForAlgorithmRoot *p,ResultBasePhase &dst)
{
	AlgoPointer	=p->GetAlgorithm()->GetPageDataPhase(PhaseCode);
	if(AllocPageNumb==dst.AllocPageNumb){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int L=0;L<AllocPageNumb;L++){
				PageData[L]->MoveMerge(*dst.PageData[L]);
			}
		}
	}
	else{
		for(int L=0;L<AllocPageNumb;L++){
			delete	PageData[L];
		}
		if(PageData!=NULL){
			delete	[]PageData;
		}
		AllocPageNumb=dst.AllocPageNumb;
		PageData=new ResultInPageRoot*[AllocPageNumb];
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int L=0;L<AllocPageNumb;L++){
				PageData[L]=p->CreatePage(PhaseCode,L);
				PageData[L]->SetPage(L);
				PageData[L]->Initial(p);		
				PageData[L]->MoveMerge(*dst.PageData[L]);
			}
		}
	}
}
bool	ResultBasePhase::Save(ResultBaseForAlgorithmRoot *p,QIODevice *file)
{
	if(::Save(file,AllocPageNumb)==false){
		return(false);
	}
	for(int L=0;L<AllocPageNumb;L++){
		if(PageData[L]->Save(file)==false){
			return(false);
		}
	}
	return true;
}
bool	ResultBasePhase::Load(ResultBaseForAlgorithmRoot *p,QIODevice *file)
{
	int32	iAllocPageNumb;
	if(::Load(file,iAllocPageNumb)==false){
		return(false);
	}
	if(iAllocPageNumb>AllocPageNumb){
		for(int L=0;L<AllocPageNumb;L++){
			delete	PageData[L];
		}
		if(PageData!=NULL){
			delete	[]PageData;
		}
		PageData=new ResultInPageRoot*[iAllocPageNumb];
		AllocPageNumb=iAllocPageNumb;
		for(int L=0;L<AllocPageNumb;L++){
			PageData[L]=p->CreatePage(PhaseCode,L);
		}
	}
	for(int L=0;L<AllocPageNumb;L++){
		if(PageData[L]->Load(file)==false){
			return(false);
		}
	}
	return true;
}
void	ResultBasePhase::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> *TmpRect,ErrorGroupPack SpecializedGroup[])
{
	if(AllocPageNumb<=1){
		for(int localPage=0;localPage<AllocPageNumb;localPage++){
			ResultInPageRoot *P=GetPageData(localPage);
			if(P!=NULL){
				P->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect[localPage],SpecializedGroup[localPage]);
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for
			for(int localPage=0;localPage<AllocPageNumb;localPage++){
				ResultInPageRoot *P=GetPageData(localPage);
				if(P!=NULL){
					P->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect[localPage],SpecializedGroup[localPage]);
				}
			}
		}
	}
}
void	ResultBasePhase::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim TmpRectDim[],ErrorGroupPack SpecializedGroup[])
{
	if(AllocPageNumb<=1){
		for(int localPage=0;localPage<AllocPageNumb;localPage++){
			ResultInPageRoot *P=GetPageData(localPage);
			if(P!=NULL){
				P->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim[localPage],SpecializedGroup[localPage]);
			}
		}
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for
			for(int localPage=0;localPage<AllocPageNumb;localPage++){
				ResultInPageRoot *P=GetPageData(localPage);
				if(P!=NULL){
					P->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim[localPage],SpecializedGroup[localPage]);
				}
			}
		}
	}
}

void	ResultBasePhase::InitialInspection(ResultBaseForAlgorithmRoot *p)
{
	if(p->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int L=0;L<AllocPageNumb;L++){
			PageData[L]->InitialInspection();
		}
	}
	else if(p->GetParamGlobal()->BufferedProcessing==false){
		int	StrN=p->GetLayersBase()->GetCurrentStrategicNumber();
		if(StrN==0){
			for(int L=0;L<AllocPageNumb;L++){
				PageData[L]->InitialInspection();
			}	
		}
		else{
			IntList	PageList;
			p->GetParamGlobal()->GetStrategyPage (StrN
											,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();
				ResultInPageRoot	*R=GetPageData(page);
				R->InitialInspection();
			}
		}
	}
	else{
		int	Pg=p->GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			R->InitialInspection();
		}
	}
}
int		ResultBasePhase::GetNGCount(void)
{
	int	NGCount=0;

	if(PageData==NULL){
		return 0;
	}
	if(PageData!=NULL){
		for(int L=0;L<AllocPageNumb;L++){
			NGCount+=PageData[L]->GetNGCount(); 
		}
	}
	return NGCount;
}

int		ResultBasePhase::GetNGPointCount(void)
{
	int	NGCount=0;

	if(PageData==NULL){
		return 0;
	}
	if(PageData!=NULL){
		for(int L=0;L<AllocPageNumb;L++){
			NGCount+=PageData[L]->GetNGPointCount();
		}
	}
	return NGCount;
}

bool	ResultBasePhase::GatherResult(bool3 &OK)
{
	OK=true3;
	for(int L=0;L<AllocPageNumb;L++){
		bool3	tOK;
		PageData[L]->GatherResult(tOK);
		if(tOK==none3){
			OK=none3;
			return true;
		}
		if(tOK==false3){
			OK=false3;
		}
	}
	return true;
}

bool	ResultBasePhase::GatherResult(int page,bool3 &OK)
{
	OK=true3;

	bool3	tOK;
	PageData[page]->GatherResult(tOK);
	if(tOK==none3){
		OK=none3;
		return true;
	}
	if(tOK==false3){
		OK=false3;
	}
	return true;
}

void	ResultBasePhase::BindNGAreaListContainer(int localpage,NGAreaListContainer &List)
{
	if(localpage>0){
		ResultInPageRoot *P=GetPageData(localpage);
		P->BindNGAreaListContainer(List);
	}
	else{
		for(int localPage=0;localPage<AllocPageNumb;localPage++){
			ResultInPageRoot *P=GetPageData(localPage);
			P->BindNGAreaListContainer(List);
		}
	}
}
void	ResultBasePhase::SetResultMarkForLearning(int page)
{
	ResultInPageRoot *P=GetPageData(page);
	P->SetResultMarkForLearning();
}

void	ResultBasePhase::ReviveResult(LearningImage *c)
{
	for(int localPage=0;localPage<AllocPageNumb;localPage++){
		ResultInPageRoot *P=GetPageData(localPage);
		P->ReviveResult(c);
	}
}
LayersBase	*ResultBasePhase::GetLayersBase(void)
{
	return Parent->GetLayersBase();
}
void	ResultBasePhase::CalcNGCounterAgain(void)
{
	for(int localPage=0;localPage<AllocPageNumb;localPage++){
		ResultInPageRoot *P=GetPageData(localPage);
		P->CalcNGCounterAgain();
	}
}

ExeResult	ResultBasePhase::ExecuteInitialAfterEdit	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgoPointer	=Parent->GetAlgorithm()->GetPageDataPhase(PhaseCode);
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
		ResultInPageRoot	*R=GetPageData(page);
		ExeResult	RR=Ap->GetPageData(page)->ExecuteInitialAfterEdit(ExeID ,R);
		if(RR!=_ER_true){
			Ret=RR;
		}
		RR=R->ExecuteInitialAfterEdit(ExeID);
		if(RR!=_ER_true){
			Ret=RR;
		}
		Ap->GetPageData(page)->EndMilisecExecuteInitialAfterEdit();
	}
	return Ret;

}
ExeResult	ResultBasePhase::ExecuteStartByInspection(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteStartByInspection(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteStartByInspection(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteStartByInspection();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		if(GetLayersBase()->GetCurrentStrategicNumber()==0){
			for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
				ResultInPageRoot	*R=GetPageData(page);
				ExeResult	RR=Ap->GetPageData(page)->ExecuteStartByInspection(ExeID ,R);
				if(RR!=_ER_true){
					Ret=RR;
				}
				RR=R->ExecuteStartByInspection(ExeID);
				if(RR!=_ER_true){
					Ret=RR;
				}
				Ap->GetPageData(page)->EndMilisecExecuteStartByInspection();
			}
		}
		/*
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteStartByInspection(R,pInspectionData);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteStartByInspection();
		}
		*/
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecuteStartByInspection(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteStartByInspection(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecuteStartByInspection();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecutePreAlignment		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}

	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		int	PageNumb=GetLayersBase()->GetAllocatedPageNumb();

		if(PageNumb==1 || Ap->GetPageData(0)->IsModeParallelExecutePreAlignment()==false){
			for(int page=0;page<PageNumb;page++){
				ResultInPageRoot	*R=GetPageData(page);
				ExeResult	RR=Ap->GetPageData(page)->ExecutePreAlignment(ExeID ,R);
				if(RR!=_ER_true){
					Ret=RR;
				}
				RR=R->ExecutePreAlignment(ExeID);
				if(RR!=_ER_true){
					Ret=RR;
				}
				Ap->GetPageData(page)->EndMilisecExecutePreAlignment();
			}
		}
		else{
			#pragma omp parallel                             
			{                                                
				#pragma omp for schedule(dynamic)
				for(int page=0;page<PageNumb;page++){
					ResultInPageRoot	*R=GetPageData(page);
					ExeResult	RR=Ap->GetPageData(page)->ExecutePreAlignment(ExeID ,R);
					if(RR!=_ER_true){
						Ret=RR;
					}
					RR=R->ExecutePreAlignment(ExeID);
					if(RR!=_ER_true){
						Ret=RR;
					}
					Ap->GetPageData(page)->EndMilisecExecutePreAlignment();
				}
			}
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePreAlignment(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreAlignment(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePreAlignment();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecutePreAlignment(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreAlignment(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecutePreAlignment();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecuteAlignment		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}

	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteAlignment(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteAlignment(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteAlignment();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteAlignment(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteAlignment(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteAlignment();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecuteAlignment(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteAlignment(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecuteAlignment();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecutePreProcessing	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}

	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePreProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePreProcessing();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePreProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePreProcessing();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecutePreProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecutePreProcessing();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecuteProcessing		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteProcessing();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteProcessing();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecuteProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecuteProcessing();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecuteProcessingRevived(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteProcessingRevived(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessingRevived(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteProcessingRevived();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteProcessingRevived(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessingRevived(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteProcessingRevived();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecuteProcessingRevived(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteProcessingRevived(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecuteProcessingRevived();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecutePostProcessing	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;

	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(Ap->GetEnableExecute()==false){
		return _ER_true;
	}
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePostProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePostProcessing();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePostProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePostProcessing();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecutePostProcessing(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostProcessing(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecutePostProcessing();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecutePreScanning	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;

	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePreScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePreScanning();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePreScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePreScanning();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecutePreScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePreScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecutePreScanning();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecuteScanning	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteScanning();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecuteScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecuteScanning();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecuteScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecuteScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecuteScanning();
		}
	}
	return Ret;
}
ExeResult	ResultBasePhase::ExecutePostScanning	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;

	AlgorithmInPageInOnePhase	*Ap=Base->GetPageDataPhase(PhaseCode);
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePostScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePostScanning();
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			ExeResult	RR=Ap->GetPageData(page)->ExecutePostScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(page)->EndMilisecExecutePostScanning();
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			ExeResult	RR=Ap->GetPageData(Pg)->ExecutePostScanning(ExeID ,R);
			if(RR!=_ER_true){
				Ret=RR;
			}
			RR=R->ExecutePostScanning(ExeID);
			if(RR!=_ER_true){
				Ret=RR;
			}
			Ap->GetPageData(Pg)->EndMilisecExecutePostScanning();
		}
	}
	return Ret;
}

int		ResultBasePhase::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(int localPage=0;localPage<AllocPageNumb;localPage++){
		ResultInPageRoot *r=GetPageData(localPage);
		int	count=r->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}
void	ResultBasePhase::SetCurentCalcDone(bool b)
{
	if(GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetLayersBase()->GetAllocatedPageNumb();page++){
			ResultInPageRoot	*R=GetPageData(page);
			R->SetCurentCalcDone(b);
		}
	}
	else if(GetLayersBase()->GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetLayersBase()->GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			ResultInPageRoot	*R=GetPageData(page);
			R->SetCurentCalcDone(b);
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			ResultInPageRoot	*R=GetPageData(Pg);
			R->SetCurentCalcDone(b);
		}
	}
}

//=============================================================

ResultBaseForAlgorithmRoot::ResultBaseForAlgorithmRoot(LogicDLL *parent)
:ServiceForLayers(parent->GetLayersBase())
{
	LogicDLLPoint	=parent;
	Parent			=NULL;

	PageDataPhase	=NULL;
	AllocPhaseNumb	=0;
}
ResultBaseForAlgorithmRoot::~ResultBaseForAlgorithmRoot(void)
{
	LogicDLLPoint	=NULL;
	Parent			=NULL;
	Release();
}

//ResultInPageRoot	*ResultBaseForAlgorithmRoot::GetPageData(int page)
//{	
//	return (PageDataPhase!=NULL)?PageDataPhase[GetLayersBase()->GetCurrentPhase()]->GetPageData(page):NULL;
//}


void	ResultBaseForAlgorithmRoot::GetAlgorithm(QString &DLLRoot,QString &DLLName)
{
	if(LogicDLLPoint!=NULL){
		DLLRoot=LogicDLLPoint->GetDLLRoot();
		DLLName=LogicDLLPoint->GetDLLName();
	}
}

bool	ResultBaseForAlgorithmRoot::Initial(void)
{
	if(AllocPhaseNumb!=GetParamGlobal()->PhaseNumb){
		Release();
		AllocPhaseNumb=GetParamGlobal()->PhaseNumb;
		PageDataPhase=new ResultBasePhase*[AllocPhaseNumb];
		for(int L=0;L<AllocPhaseNumb;L++){
			PageDataPhase[L]=new ResultBasePhase(L,this);
		}
	}
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->SetPhaseCode(L);
		if(PageDataPhase[L]->Initial(this)==false){
			return false;
		}
	}
	return true;
}
void	ResultBaseForAlgorithmRoot::Release(void)
{
	if(PageDataPhase!=NULL){
		for(int L=0;L<AllocPhaseNumb;L++){
			delete	PageDataPhase[L];
		}
		delete	[]PageDataPhase;
	}
	PageDataPhase	=NULL;
	AllocPhaseNumb	=0;
}
bool	ResultBaseForAlgorithmRoot::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(PageDataPhase!=NULL){
		if(newPhaseNumb>AllocPhaseNumb){
			ResultBasePhase	**iPageDataPhase=new ResultBasePhase*[newPhaseNumb];
			int	i;
			for(i=0;i<AllocPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					break;
				}
				iPageDataPhase[i]=PageDataPhase[i];
				iPageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
			}
			delete	[]PageDataPhase;
			PageDataPhase=iPageDataPhase;
			AllocPhaseNumb=newPhaseNumb;
			for(;i<newPhaseNumb;i++){
				iPageDataPhase[i]=new ResultBasePhase(i,this);
				iPageDataPhase[i]->Initial(this);
			}
		}
		else if(newPhaseNumb<AllocPhaseNumb){
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new ResultBasePhase(i,this);
					PageDataPhase[i]->Initial(this);
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
			for(int i=newPhaseNumb;i<AllocPhaseNumb;i++){
				if(PageDataPhase[i]!=NULL){
					delete	PageDataPhase[i];
					PageDataPhase[i]=NULL;
				}
			}
			AllocPhaseNumb=newPhaseNumb;
		}
		else{
			AllocPhaseNumb=newPhaseNumb;
			for(int i=0;i<newPhaseNumb;i++){
				if(PageDataPhase[i]==NULL){
					PageDataPhase[i]=new ResultBasePhase(i,this);
					PageDataPhase[i]->Initial(this);
				}
				else{
					PageDataPhase[i]->Reallocate(newPageNumb ,newLayerNumb);
				}
			}
		}
	}
	else{
		Initial();
	}
	return true;
}

bool	ResultBaseForAlgorithmRoot::RemovePhase(int RemovedPhaseCode)
{
	if(PageDataPhase!=NULL){
		if(0<=RemovedPhaseCode && RemovedPhaseCode<AllocPhaseNumb){
			delete	PageDataPhase[RemovedPhaseCode];
			for(int phase=RemovedPhaseCode+1;phase<AllocPhaseNumb;phase++){
				PageDataPhase[phase-1]=PageDataPhase[phase];
			}
			AllocPhaseNumb--;
		}
	}
	return true;
}
bool    ResultBaseForAlgorithmRoot::Save(QIODevice *file)
{
	if(::Save(file,LogicDLLPoint->GetDLLRoot())==false){
		return false;
	}
	if(::Save(file,LogicDLLPoint->GetDLLName())==false){
		return false;
	}
	if(::Save(file,AllocPhaseNumb)==false){
		return false;
	}
	for(int L=0;L<AllocPhaseNumb;L++){
		if(PageDataPhase[L]->Save(this,file)==false){
			return(false);
		}
	}
	return(true);
}
bool    ResultBaseForAlgorithmRoot::Load(QIODevice *file)
{
	QString	aDLLRoot;
	QString	aDLLName;
	if(::Load(file,aDLLRoot)==false){
		return false;
	}
	if(::Load(file,aDLLName)==false){
		return false;
	}
	LogicDLLPoint=GetLayersBase()->GetLogicDLLBase()->Search(aDLLRoot,aDLLName);

	if(::Load(file,AllocPhaseNumb)==false){
		return false;
	}
	Initial();
	for(int L=0;L<AllocPhaseNumb;L++){
		if(PageDataPhase[L]->Load(this,file)==false){
			return(false);
		}
	}

	return(true);
}
bool    ResultBaseForAlgorithmRoot::SaveOnlyPage(QIODevice *file,int page)
{
	if(::Save(file,LogicDLLPoint->GetDLLRoot())==false){
		return false;
	}
	if(::Save(file,LogicDLLPoint->GetDLLName())==false){
		return false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase	*Ph=GetPageDataPhase(phase);
		ResultInPageRoot	*p=Ph->GetPageData(page);
		if(p->Save(file)==false){
			return false;
		}
	}
	return true;
}


bool    ResultBaseForAlgorithmRoot::LoadOnlyPage(QIODevice *file,int page)
{
	QString	aDLLRoot;
	QString	aDLLName;
	if(::Load(file,aDLLRoot)==false){
		return false;
	}
	if(::Load(file,aDLLName)==false){
		return false;
	}
	LogicDLLPoint=GetLayersBase()->GetLogicDLLBase()->Search(aDLLRoot,aDLLName);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase	*Ph=GetPageDataPhase(phase);
		ResultInPageRoot	*p=Ph->GetPageData(page);
		if(p->Load(file)==false){
			return false;
		}
	}
	return true;
}

void	ResultBaseForAlgorithmRoot::MoveMerge(ResultBaseForAlgorithmRoot &dst)
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->MoveMerge(this,*dst.PageDataPhase[L]);
	}
}

void	ResultBaseForAlgorithmRoot::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> **TmpRect,ErrorGroupPack SpecializedGroup[])
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect[L],SpecializedGroup);
	}
}

void	ResultBaseForAlgorithmRoot::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim **TmpRectDim,ErrorGroupPack SpecializedGroup[])
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRectDim[L],SpecializedGroup);
	}
}

void	ResultBaseForAlgorithmRoot::InitialInspection(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(GetLayersBase()->GetCurrentScanPhaseNumber()==0){
			for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
				PageDataPhase[L]->InitialInspection(this);
			}
		}
		else{
			IntList PhaseCodes;
			GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
				PageDataPhase[v->GetValue()]->InitialInspection(this);
			}
		}
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		int	StrN=GetLayersBase()->GetCurrentStrategicNumber();
		if(StrN==0){
			if(GetLayersBase()->GetCurrentScanPhaseNumber()==0){
				for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
					PageDataPhase[L]->InitialInspection(this);
				}
			}
			else{
				IntList PhaseCodes;
				GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
				for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
					PageDataPhase[v->GetValue()]->InitialInspection(this);
				}
			}
		}
		else{
			IntList PhaseCodes;
			GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
			for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
				PageDataPhase[v->GetValue()]->InitialInspection(this);
			}
		/*
			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (StrN
												,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();
				ResultInPageRoot	*R=GetPageData(page);
				R->InitialInspection();
			}
			*/
		}
	}
	else{
		int	Pg=GetLayersBase()->GetTopPageInCapturedPageLayer();
		if(Pg>=0){
			int	phase=GetLayersBase()->GetCurrentPhase();
			ResultBasePhase		*Ph=GetPageDataPhase(phase);
			ResultInPageRoot	*R=Ph->GetPageData(Pg);
			R->InitialInspection();
		}
	}
}
int		ResultBaseForAlgorithmRoot::GetNGCount(void)
{
	int	NGCount=0;
	if(PageDataPhase==NULL){
		Initial();
	}
	if(PageDataPhase==NULL){
		return 0;
	}
	if(PageDataPhase!=NULL){
		for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
			NGCount+=PageDataPhase[L]->GetNGCount();
		}
	}
	return NGCount;
}

int		ResultBaseForAlgorithmRoot::GetNGPointCount(void)
{
	int	NGCount=0;
	if(PageDataPhase==NULL){
		Initial();
	}
	if(PageDataPhase==NULL){
		return 0;
	}
	if(PageDataPhase!=NULL){
		for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
			NGCount+=PageDataPhase[L]->GetNGPointCount();
		}
	}
	return NGCount;
}

void	ResultBaseForAlgorithmRoot::BindNGAreaListContainer(int localpage,NGAreaListContainer &List)
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->BindNGAreaListContainer(localpage,List);
	}
}

ResultDLLBaseRoot	*ResultBaseForAlgorithmRoot::GetResultDLLBase(void)
{
	if(GetLayersBase()->GetResultDLLBase()==NULL || GetLayersBase()->GetResultDLLBase()->GetFirst()==NULL){
		return NULL;
	}
	return GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
}

void	ResultBaseForAlgorithmRoot::SetResultMarkForLearning(int page)
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->SetResultMarkForLearning(page);
	}
}

void	ResultBaseForAlgorithmRoot::ReviveResult(LearningImage *c)
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->ReviveResult(c);
	}
}

void	ResultBaseForAlgorithmRoot::CalcNGCounterAgain(void)
{
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		PageDataPhase[L]->CalcNGCounterAgain();
	}
}

ExeResult	ResultBaseForAlgorithmRoot::ExecuteInitialAfterEdit	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-1){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			//if(phase==GetLayersBase()->GetCurrentPhase() || GetLayersBase()->GetPageDataPhase(phase)->GetFromSourcePhase()==GetLayersBase()->GetCurrentPhase()){
			ExeResult	RR=PageDataPhase[phase]->ExecuteInitialAfterEdit	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteInitialAfterEdit	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteInitialAfterEdit && GetParamGlobal()->ModePhaseExecuteInitialAfterEdit<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteInitialAfterEdit;
		ExeResult	RR=PageDataPhase[phase]->ExecuteInitialAfterEdit	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteInitialAfterEdit	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecuteStartByInspection(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecuteStartByInspection	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteStartByInspection	(ExeID ,Base );
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteStartByInspection && GetParamGlobal()->ModePhaseExecuteStartByInspection<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteStartByInspection;
		ExeResult	RR=PageDataPhase[phase]->ExecuteStartByInspection	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteStartByInspection>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteStartByInspection	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecutePreAlignment		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecutePreAlignment==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecutePreAlignment	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreAlignment==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecutePreAlignment	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePreAlignment && GetParamGlobal()->ModePhaseExecutePreAlignment<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecutePreAlignment;
		ExeResult	RR=PageDataPhase[phase]->ExecutePreAlignment	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreAlignment>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecutePreAlignment	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}

	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecuteAlignment		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteAlignment==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecuteAlignment	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteAlignment==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteAlignment	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteAlignment && GetParamGlobal()->ModePhaseExecuteAlignment<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteAlignment;
		ExeResult	RR=PageDataPhase[phase]->ExecuteAlignment	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteAlignment>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteAlignment	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecutePreProcessing	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecutePreProcessing==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecutePreProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreProcessing==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecutePreProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePreProcessing && GetParamGlobal()->ModePhaseExecutePreProcessing<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecutePreProcessing;
		ExeResult	RR=PageDataPhase[phase]->ExecutePreProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreProcessing>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecutePreProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecuteProcessing		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteProcessing==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecuteProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteProcessing==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteProcessing && GetParamGlobal()->ModePhaseExecuteProcessing<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteProcessing;
		ExeResult	RR=PageDataPhase[phase]->ExecuteProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteProcessing>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecuteProcessingRevived(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteProcessingRevived==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecuteProcessingRevived	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteProcessingRevived==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteProcessingRevived	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteProcessingRevived && GetParamGlobal()->ModePhaseExecuteProcessingRevived<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteProcessingRevived;
		ExeResult	RR=PageDataPhase[phase]->ExecuteProcessingRevived	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteProcessingRevived>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteProcessingRevived	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecutePostProcessing	(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecutePostProcessing==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecutePostProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePostProcessing==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecutePostProcessing	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePostProcessing && GetParamGlobal()->ModePhaseExecutePostProcessing<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecutePostProcessing;
		ExeResult	RR=PageDataPhase[phase]->ExecutePostProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePostProcessing>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecutePostProcessing	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecutePreScanning		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecutePreScanning==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecutePreScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreScanning==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecutePreScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePreScanning && GetParamGlobal()->ModePhaseExecutePreScanning<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecutePreScanning;
		ExeResult	RR=PageDataPhase[phase]->ExecutePreScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreScanning>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecutePreScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecuteScanning			(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecuteScanning==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecuteScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteScanning==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecuteScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteScanning && GetParamGlobal()->ModePhaseExecuteScanning<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecuteScanning;
		ExeResult	RR=PageDataPhase[phase]->ExecuteScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteScanning>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecuteScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}
ExeResult	ResultBaseForAlgorithmRoot::ExecutePostScanning		(int ExeID ,AlgorithmBase *Base)
{
	ExeResult	Ret=_ER_true;
	if(GetParamGlobal()->ModePhaseExecutePostScanning==-1){
		IntList	PhaseList;
		GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
		for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			ExeResult	RR=PageDataPhase[phase]->ExecutePostScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePostScanning==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			ExeResult	RR=PageDataPhase[phase]->ExecutePostScanning	(ExeID ,Base);
			if(RR!=_ER_true){
				Ret=RR;
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePostScanning && GetParamGlobal()->ModePhaseExecutePostScanning<GetPhaseNumb()){
		int	phase=GetParamGlobal()->ModePhaseExecutePostScanning;
		ExeResult	RR=PageDataPhase[phase]->ExecutePostScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePostScanning>=GetPhaseNumb()){
		int	phase=GetLayersBase()->GetCurrentPhase();
		ExeResult	RR=PageDataPhase[phase]->ExecutePostScanning	(ExeID ,Base);
		if(RR!=_ER_true){
			Ret=RR;
		}
	}
	return Ret;
}

int		ResultBaseForAlgorithmRoot::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(int L=0;L<AllocPhaseNumb && L<GetParamGlobal()->PhaseNumb;L++){
		int	count=PageDataPhase[L]->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}
AlgorithmBase		*ResultBaseForAlgorithmRoot::GetAlgorithm(void)
{
	return LogicDLLPoint->GetInstance();
}

bool	ResultBaseForAlgorithmRoot::GatherResult(bool3 &OK)
{
	OK=true3;
	if(LogicDLLPoint!=NULL){
		if(LogicDLLPoint->IsProcessAlgorithm()==false)
			return false;
	}
	for(int phase=0;phase<AllocPhaseNumb && phase<GetParamGlobal()->PhaseNumb;phase++){
		bool3 tOK=true3;
		ResultBasePhase		*Ph=GetPageDataPhase(phase);
		if(Ph->GatherResult(tOK)==true){
			if(tOK==false3 && OK==true3)
				OK=false3;
			if(tOK==none3)
				OK=none3;
		}
	}
	return true;
}
bool	ResultBaseForAlgorithmRoot::GatherResult(int page ,bool3 &OK)
{
	OK=true3;
	for(int phase=0;phase<AllocPhaseNumb && phase<GetParamGlobal()->PhaseNumb;phase++){
		bool3 tOK=true3;
		ResultBasePhase		*Ph=GetPageDataPhase(phase);
		if(Ph->GatherResult(page,tOK)==true){
			if(tOK==false3 && OK==true3)
				OK=false3;
			if(tOK==none3)
				OK=none3;
		}
	}
	return true;
}
void	ResultBaseForAlgorithmRoot::SetCurentCalcDone(bool b)
{
	IntList	PhaseList;
	GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
	for(IntClass *c=PhaseList.GetFirst();c!=NULL;c=c->GetNext()){
		int	phase=c->GetValue();
		PageDataPhase[phase]->SetCurentCalcDone(b);
	}
}

//================================================================================
static	int	DbgNGImageContainerInPage;
NGImageContainerInPage::~NGImageContainerInPage(void)
{
	DbgNGImageContainerInPage++;
}
int		NGImageContainerInPage::GetNGImageCount(void)
{	
	NGImageAccessor.lockForRead();
	int	Ret=NGImageData.GetNumber();
	NGImageAccessor.unlock();
	return Ret;
}


void		NGImageContainerInPage::AddNGImageData(NGImage *b)
{	
	NGImageAccessor.lockForWrite();
	NGImageData.AppendList(b);
	NGImageAccessor.unlock();
}
int			NGImageContainerInPage::GetNGImageDataCount(void)
{	
	NGImageAccessor.lockForRead();
	int	Ret=NGImageData.GetNumber();
	NGImageAccessor.unlock();
	return Ret;
}
NGImage		*NGImageContainerInPage::GetNGImageDataFirst(void)
{	
	return NGImageData.GetFirst();		
}
void		NGImageContainerInPage::ClearNGImageData(void)
{	
	NGImageAccessor.lockForWrite();
	NGImage	*a;
	while((a=NGImageData.GetFirst())!=NULL){
		NGImageData.RemoveList(a);
		NGImageStockker.AppendList(a);
	}
	Compressed=false;
	NGImageAccessor.unlock();
}

ExeResult	NGImageContainerInPage::ExecuteInitialAfterEdit	(int ExeID)
{
	ResultDLLBaseClass		*R=GetLayersBase()->GetResultDLLBase();
	if(R==NULL)
		return _ER_false;
	ResultDLL	*r=R->GetFirst();
	if(r==NULL)
		return _ER_false;
	ResultDLLBaseRoot	*DR=r->GetDLLPoint();
	if(DR==NULL)
		return _ER_false;

	int	ImageW	=DR->NGImageWidth;
	int	ImageH	=DR->NGImageHeight;
	int	Bevel	=DR->NGImageBevel;

	if(NGImageStockker.GetCount()<GetParamGlobal()->CountOfNGImageForPrepararion){
		NGImage	*d=new NGImage();
		d->SetRectangle(0,0, ImageW,ImageH);
		d->SetNumber(NGImageStockker.GetCount());
		d->SetGlobalPage(GlobalPage);
		d->AllocateBuffer(GetLayerNumb());
		NGImageStockker.AppendList(d);
	}
	return _ER_true;
}

NGImage		*NGImageContainerInPage::GetNGImageFromStockker(void)
{
	NGImageAccessor.lockForWrite();
	NGImage	*d=NGImageStockker.GetFirst();
	if(d!=NULL){
		NGImageStockker.RemoveList(d);
	}
	NGImageAccessor.unlock();
	return d;
}

NGImageContainerInPage	&NGImageContainerInPage::operator=(NGImageContainerInPage &src)
{
	NGImageAccessor.lockForWrite();
	NGImageData.RemoveAll();
	for(NGImage *c=src.NGImageData.GetFirst();c!=NULL;c=c->GetNext()){
		NGImage *d=new NGImage();
		*d= *c;
		NGImageData.AppendList(d);
	}
	NGImageAccessor.unlock();

	ErrorGroupData=src.ErrorGroupData;
	GlobalPage	=src.GlobalPage;
	Compressed	=src.Compressed;
	return *this;
}

bool    NGImageContainerInPage::Save(QIODevice *file)
{
	NGImageAccessor.lockForRead();
	int32	N=NGImageData.GetNumber();
	if(::Save(file,N)==false){
		NGImageAccessor.unlock();
		return false;
	}
	for(NGImage *a=NGImageData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(file)==false){
			NGImageAccessor.unlock();
			return false;
		}
	}
	NGImageAccessor.unlock();
	if(ErrorGroupData.Save(file)==false){
		return false;
	}
	if(::Save(file,GlobalPage)==false){
		return false;
	}
	return true;
}

bool    NGImageContainerInPage::Load(QIODevice *file,LayersBase *Base)
{
	int32	N;
	if(::Load(file,N)==false){
		return false;
	}
	NGImageAccessor.lockForRead();
	NGImageData.RemoveAll();
	for(int i=0;i<N;i++){
		NGImage *a=new NGImage();
		if(a->Load(file)==false){
			NGImageAccessor.unlock();
			return false;
		}
		NGImageData.AppendList(a);
	}
	NGImageAccessor.unlock();
	if(ErrorGroupData.Load(file,Base)==false){
		return false;
	}
	if(::Load(file,GlobalPage)==false){
		return false;
	}
	return true;
}

NGImageContainerInPhase::NGImageContainerInPhase(int phase ,LayersBase *base)
:ServiceForLayers(base)
{
	Phase=phase;
}

bool	NGImageContainerInPhase::IsDoneCompressed(void)
{
	for(NGImageContainerInPage *h=NGImageInPage.GetFirst();h!=NULL;h=h->GetNext()){
		if(h->IsDoneCompressed()==false){
			return false;
		}
	}
	return true;
}

bool	NGImageContainerInPhase::IsResultOK(int page)
{
	NGImageContainerInPage *h=NGImageInPage[page];
	if(h!=NULL){
		if(h->GetNGImageCount()==0){
			return true;
		}
	}
	return false;
}

NGImageContainerInPage	*NGImageContainerInPhase::GetNGImageInPage(int localpage)
{	
	NGImageContainerInPage	*h=NGImageInPage.GetItem(localpage);
	if(h==NULL){
		h=new NGImageContainerInPage(GetLayersBase()->GetGlobalPageFromLocal(localpage)
									,GetLayersBase());
		NGImageInPage.AppendList(h);
	}
	return h;
}

int		NGImageContainerInPhase::GetNGImageCount(void)
{
	int	NGCount=0;
	for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
		NGCount+=p->GetNGImageCount();
	}
	return NGCount;
}
void	NGImageContainerInPhase::ClearAll(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
			p->ClearNGImageData();
			p->ClearErrorGroupData();
		}
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		int	StrN=GetLayersBase()->GetCurrentStrategicNumber();
		if(StrN==0){
			for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
				p->ClearNGImageData();
				p->ClearErrorGroupData();
			}
		}
		else{
			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (StrN
											,PageList);

			for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
				if(PageList.IsInclude(GetLayersBase()->GetLocalPageFromGlobal(p->GetGlobalPage()))==true){
					p->ClearNGImageData();
					p->ClearErrorGroupData();
				}
			}
		}
	}
}
ExeResult	NGImageContainerInPhase::ExecuteInitialAfterEdit(int ExeID)
{
	for(int page=0;page<GetPageNumb();page++){
		GetNGImageInPage(page);
		NGImageContainerInPage	*h=NGImageInPage.GetItem(page);
		h->ExecuteInitialAfterEdit(ExeID);
	}
	return _ER_true;
}
bool	NGImageContainerInPhase::SaveNGImage(QIODevice *OStr ,int localPage)
{
	DWORD	Ver=Version_NGImage;

	if(::Save(OStr,Ver)==false){
		return false;
	}
	if(::Save(OStr,Phase)==false){
		return false;
	}
	int16	SaveMode=(GetParamGlobal()->ModeCompressNGImage==true)?1:0;
	if(::Save(OStr,SaveMode)==false){
		return false;
	}
	NGImageContainerInPage	*s=NGImageInPage.GetItem(localPage);
	if(s!=NULL){
		int32	N=s->GetNGImageDataCount();
		if(::Save(OStr,N)==false){
			return false;
		}
		s->NGImageAccessor.lockForRead();
		for(NGImage *c=s->GetNGImageDataFirst();c!=NULL;c=c->GetNext()){
			if(GetParamGlobal()->ModeCompressNGImage==true){
				if(c->SaveJDT(OStr)==false){
					s->NGImageAccessor.unlock();
					return false;
				}
			}
			else{
				if(c->SaveRawImage(OStr)==false){
					s->NGImageAccessor.unlock();
					return false;
				}
			}
		}
		s->NGImageAccessor.unlock();
		return true;
	}
	return false;
}

bool	NGImageContainerInPhase::SaveNGImage(FlexArea &OverlappedArea
						,int offsetX ,int offsetY
						,QIODevice *OStr ,int localPage)
{
	DWORD	Ver=Version_NGImage;

	if(::Save(OStr,Ver)==false){
		return false;
	}
	if(::Save(OStr,Phase)==false){
		return false;
	}
	int16	SaveMode=(GetParamGlobal()->ModeCompressNGImage==true)?1:0;
	if(::Save(OStr,SaveMode)==false){
		return false;
	}
	NGImageContainerInPage	*s=NGImageInPage.GetItem(localPage);
	if(s!=NULL){
		int32	N=s->GetNGImageDataCount();
		if(::Save(OStr,N)==false){
			return false;
		}
		s->NGImageAccessor.lockForRead();
		for(NGImage *c=s->GetNGImageDataFirst();c!=NULL;c=c->GetNext()){
			if(c->IsOverlapped(OverlappedArea)==true){
				if(GetParamGlobal()->ModeCompressNGImage==true){
					if(c->SaveJDT(OStr,offsetX,offsetY)==false){
						s->NGImageAccessor.unlock();
						return false;
					}
				}
				else{
					if(c->SaveRawImage(OStr,offsetX,offsetY)==false){
						s->NGImageAccessor.unlock();
						return false;
					}
				}
			}
		}
		s->NGImageAccessor.unlock();
		return true;
	}
	return false;
}

bool	NGImageContainerInPhase::SaveOnlyPage(QIODevice *f,int page)
{
	NGImageContainerInPage *g=NGImageInPage.GetItem(page);
	if(g!=NULL){
		bool	ExistNGImageContainerInPage=true;
		if(::Save(f,ExistNGImageContainerInPage)==false){
			return false;
		}
		if(g->Save(f)==false){
			return false;
		}
	}
	else{
		bool	ExistNGImageContainerInPage=false;
		if(::Save(f,ExistNGImageContainerInPage)==false){
			return false;
		}
	}
	return true;
}

bool	NGImageContainerInPhase::LoadOnlyPage(QIODevice *f,int page)
{
	bool	ExistNGImageContainerInPage=false;
	if(::Load(f,ExistNGImageContainerInPage)==false){
		return false;
	}
	if(ExistNGImageContainerInPage==true){
		NGImageContainerInPage *g=new NGImageContainerInPage(GetLayersBase()->GetGlobalPageFromLocal(page)
															,GetLayersBase());
		if(g->Load(f,GetLayersBase())==false){
			return false;
		}
		NGImageInPage.AppendList(g);
	}
	return true;
}
void	NGImageContainerInPhase::ClearAllErrorGroup(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
			p->ClearErrorGroupData();
		}
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		int	StrN=GetLayersBase()->GetCurrentStrategicNumber();
		if(StrN==0){
			for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
				p->ClearErrorGroupData();
			}
		}
		else{
			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (StrN
											,PageList);

			for(NGImageContainerInPage *p=NGImageInPage.GetFirst();p!=NULL;p=p->GetNext()){
				if(PageList.IsInclude(GetLayersBase()->GetLocalPageFromGlobal(p->GetGlobalPage()))==true){
					p->ClearErrorGroupData();
				}
			}
		}
	}
}
//=============================================================================================
ResultInspection::ResultInspection(LayersBase *base)
:ServiceForLayers(base)
{	
	StartTimeForInspection.setTime_t(0);
	InspectionTimeMilisec=0;
	InspectionNumber=0;
	InspectionID=-1;
	ReceivedResultCountsAllocated=0;
	ReceivedResultCounts=NULL;
	if(base!=NULL && base->GetEntryPoint()!=NULL){
		ReceivedResultCountsAllocated=base->GetPageNumb();
		ReceivedResultCounts=new ReceivedResultCountsParam[ReceivedResultCountsAllocated];
		for(int page=0;page<ReceivedResultCountsAllocated;page++){
			ReceivedResultCounts[page].Result=-1;
			ReceivedResultCounts[page].MaxErrorBreak=false;
			ReceivedResultCounts[page].TimeOutBreak =false;
		}
	}
	AliveTillPush=true;
	OutputCode	=-1;
	CriticalError	=_NoError;
}
ResultInspection::~ResultInspection(void)
{	
	Release();
}
void	ResultInspection::Release(void)
{
	ResultBaseForAlgorithmRoot	*h;
	while((h=ResultBaseDim.GetFirst())!=NULL){
		ResultBaseDim.RemoveList(h);
		delete	h;
	}
	if(ReceivedResultCounts!=NULL){
		delete	[]ReceivedResultCounts;
	}
	ReceivedResultCounts=NULL;
	NGImageInPhase.RemoveAll();
}

bool	ResultInspection::Initial(LogicDLLBaseClass *LBase)
{
	if(LBase!=NULL){
		ResultBaseForAlgorithmRoot	*A=ResultBaseDim.GetFirst();
		LogicDLL *L=LBase->GetFirst();
		for(;L!=NULL && A!=NULL;L=L->GetNext() ,A=A->GetNext()){
			if(A->GetLogicDLL()!=L){
				break;
			}
		}
		if(L!=NULL || A!=NULL){
			ResultBaseDim.RemoveAll();
			for(LogicDLL *L=LBase->GetFirst();L!=NULL;L=L->GetNext()){
				ResultBaseForAlgorithmRoot	*a=L->CreateResultBaseForAlgorithm(this);
				if(a==NULL){
					return false;
				}
				ResultBaseDim.AppendList(a);
			}
		}
		for(ResultBaseForAlgorithmRoot	*a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Initial()==false){
				return false;
			}
		}
	}
	if(ReceivedResultCounts!=NULL){
		delete	[]ReceivedResultCounts;
		ReceivedResultCounts=NULL;
	}
	if(GetLayersBase()!=NULL && ReceivedResultCounts==NULL){
		ReceivedResultCountsAllocated=GetPageNumb();
		ReceivedResultCounts=new ReceivedResultCountsParam[ReceivedResultCountsAllocated];
		for(int page=0;page<ReceivedResultCountsAllocated;page++){
			ReceivedResultCounts[page].Result=-1;
			ReceivedResultCounts[page].MaxErrorBreak=false;
			ReceivedResultCounts[page].TimeOutBreak =false;
		}
	}
	StartTimeForInspection=XDateTime::currentDateTime();
	CriticalError	=_NoError;
	return true;
}
bool	ResultInspection::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		a->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	if(ReceivedResultCounts!=NULL){
		delete	[]ReceivedResultCounts;
		ReceivedResultCounts=NULL;
	}
	if(GetLayersBase()!=NULL && ReceivedResultCounts==NULL){
		ReceivedResultCountsAllocated=newPageNumb;
		ReceivedResultCounts=new ReceivedResultCountsParam[ReceivedResultCountsAllocated];
		for(int page=0;page<ReceivedResultCountsAllocated;page++){
			ReceivedResultCounts[page].Result=-1;
			ReceivedResultCounts[page].MaxErrorBreak=false;
			ReceivedResultCounts[page].TimeOutBreak =false;
		}
	}
	if(NGImageInPhase.GetCount()>0){
		if(NGImageInPhase.GetCount()<newPhaseNumb){
			for(int ph=NGImageInPhase.GetCount();ph<newPhaseNumb;ph++){
				NGImageContainerInPhase	*p=new NGImageContainerInPhase(ph,GetLayersBase());
				NGImageInPhase.AppendList(p);
			}
		}
		else{
			while(NGImageInPhase.GetCount()>newPhaseNumb){
				NGImageContainerInPhase	*p=NGImageInPhase.GetLast();
				if(p!=NULL){
					NGImageInPhase.RemoveList(p);
					delete	p;
				}
			}
		}
	}
	return true;
}
bool	ResultInspection::RemovePhase(int RemovedPhaseCode)
{
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		a->RemovePhase(RemovedPhaseCode);
	}

	if(NGImageInPhase.GetCount()>0){
		for(NGImageContainerInPhase *p=NGImageInPhase.GetFirst();p!=NULL;){
			NGImageContainerInPhase *NextP=p->GetNext();
			if(p->GetPhaseCode()==RemovedPhaseCode){
				NGImageInPhase.RemoveList(p);
				delete	p;
			}
			p=NextP;
		}
		int	Phase=0;
		for(NGImageContainerInPhase *p=NGImageInPhase.GetFirst();p!=NULL;p=p->GetNext(),Phase++){
			p->SetPhaseCode(Phase);
		}
	}
	return true;
}

void	ResultInspection::InitialForInspection(void)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	if(GetLayersBase()->GetCurrentScanPhaseNumber()==0){
		InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		TimeOutBreak	=false;
		MaxErrorBreak	=false;
		OutputCode		=-1;
		CriticalError	=_NoError;
	}
	for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
		NGImageContainerInPhase *ph=NGImageInPhase[v->GetValue()];
		ph->ClearAll();
	}
	RemarkData.clear();
}

void	ResultInspection::MoveResult(ResultInspection &CurrentRes)
{
	ResultBaseForAlgorithmRoot *RDim[1000];
	ResultBaseForAlgorithmRoot *EDim[1000];
	int	N=0;
	for(ResultBaseForAlgorithmRoot *r=CurrentRes.ResultBaseDim.GetFirst();r!=NULL && N<1000;r=r->GetNext(),N++){
		RDim[N]=r;
		EDim[N]=ResultBaseDim.GetItem(N);
	}
	for(int i=0;i<N;i++){
		EDim[i]->MoveMerge(*RDim[i]);
	}
	memcpy(ReceivedResultCounts,CurrentRes.ReceivedResultCounts,sizeof(ReceivedResultCounts[0])*ReceivedResultCountsAllocated);
	TimeOutBreak	=CurrentRes.TimeOutBreak;
	MaxErrorBreak	=CurrentRes.MaxErrorBreak;
	OutputCode		=CurrentRes.OutputCode;
	CriticalError	=CurrentRes.CriticalError;
	ExecTime		=CurrentRes.ExecTime;
	DeliveredInfo	=CurrentRes.DeliveredInfo;
	RemarkData		=CurrentRes.RemarkData;
	CalcDoneByPhase	=CurrentRes.CalcDoneByPhase;

	NGImageInPhase.RemoveAll();
	NGImageInPhase.Move(CurrentRes.NGImageInPhase);
	CurrentRes.AliveTillPush=false;
	AliveTillPush=true;
}

int		ResultInspection::GetNGCount(void)
{
	int	NGCount=0;
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetNGCount();
	}
	return NGCount;
}

int		ResultInspection::GetNGImageCount(void)
{
	int	NGCount=0;
	for(NGImageContainerInPhase *p=NGImageInPhase.GetFirst();p!=NULL;p=p->GetNext()){
		NGCount+=p->GetNGImageCount();
	}
	return NGCount;
}
int		ResultInspection::GetNGPointCount(void)
{
	int	NGCount=0;
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		NGCount+=a->GetNGPointCount();
	}
	return NGCount;
}

void	ResultInspection::SetResultReceivedFlag(int Page ,int64 resultCounts,bool TimeOutBreak,bool MaxErrorBreak)
{
	if(ReceivedResultCountsAllocated<=Page || ReceivedResultCountsAllocated<GetPageNumb()){
		if(ReceivedResultCounts!=NULL){
			delete	[]ReceivedResultCounts;
		}
		ReceivedResultCountsAllocated=max(GetPageNumb(),Page+1);
		ReceivedResultCounts=new ReceivedResultCountsParam[ReceivedResultCountsAllocated];
	}
	ReceivedResultCounts[Page].Result=resultCounts;
	ReceivedResultCounts[Page].MaxErrorBreak	=MaxErrorBreak;
	ReceivedResultCounts[Page].TimeOutBreak		=TimeOutBreak;
}

bool	ResultInspection::IsResultOK(void)
{
	for(int page=0;page<ReceivedResultCountsAllocated;page++){
		if(ReceivedResultCounts[page].Result>0 || ReceivedResultCounts[page].TimeOutBreak==true || ReceivedResultCounts[page].MaxErrorBreak==true){
			return false;
		}
	}
	return true;
}
bool	ResultInspection::IsResultTimeOut(void)
{
	for(int page=0;page<ReceivedResultCountsAllocated;page++){
		if(ReceivedResultCounts[page].TimeOutBreak==true){
			return true;
		}
	}
	return false;
}
bool	ResultInspection::IsResultMaxError(void)
{
	for(int page=0;page<ReceivedResultCountsAllocated;page++){
		if(ReceivedResultCounts[page].MaxErrorBreak==true){
			return true;
		}
	}
	return false;
}

void	ResultInspection::ResetCalcDone(void)
{
	while(CalcDoneByPhase.GetCount()<GetPhaseNumb()){
		CalcDoneByPhase.Add(false);
	}
	for(BoolClass *b=CalcDoneByPhase.GetFirst();b!=NULL;b=b->GetNext()){
		b->SetValue(false);
	}
}
void	ResultInspection::SetCalcDone(int phase)
{
	if(phase<CalcDoneByPhase.GetCount()){
		CalcDoneByPhase.GetItem(phase)->SetValue(true);
	}
}
bool	ResultInspection::IsCalcDone(int phase)
{
	if(phase<CalcDoneByPhase.GetCount()){
		return CalcDoneByPhase.GetItem(phase)->GetValue();
	}
	return false;
}
bool	ResultInspection::IsAllCalcDone(void)
{
	int	phase=0;
	for(BoolClass *b=CalcDoneByPhase.GetFirst();b!=NULL && phase<GetPhaseNumb();b=b->GetNext(),phase++){
		if(CalcDoneByPhase.GetItem(phase)->GetValue()==false){
			return false;
		}
	}
	return true;
}

bool	ResultInspection::GatherResult(bool3 &OK ,bool &MaxError , bool &TimeOver)
{
	OK=true3;
	MaxError=false;
	TimeOver=false;
	for(ResultBaseForAlgorithmRoot *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		bool3 tOK=true3;
		if(r->GatherResult(tOK)==true){
			if(tOK==false3 && OK==true3)
				OK=false3;
			if(tOK==none3)
				OK=none3;
		}
	}
	TimeOver=GetTimeOutBreak();
	MaxError=GetMaxErrorBreak();
	return true;
}
bool	ResultInspection::GatherResult(int page ,bool3 &OK ,bool &MaxError , bool &TimeOver)
{
	OK=true3;
	MaxError=false;
	TimeOver=false;
	for(ResultBaseForAlgorithmRoot *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		bool3 tOK=true3;
		if(r->GatherResult(page,tOK)==true){
			if(tOK==false3 && OK==true3)
				OK=false3;
			if(tOK==none3)
				OK=none3;
		}
	}
	TimeOver=GetTimeOutBreak();
	MaxError=GetMaxErrorBreak();
	return true;
}
void	ResultInspection::SetCurentCalcDone(bool b)
{
	for(ResultBaseForAlgorithmRoot *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		r->SetCurentCalcDone(b);
	}
}
bool	ResultInspection::GetResultInPhases(IntList &PhaseCodes
							, bool &ResultOk)
{
	for(IntClass *v=PhaseCodes.GetFirst();v!=NULL;v=v->GetNext()){
		int	phase=v->GetValue();
		NGImageContainerInPhase *ph=NGImageInPhase[phase];
		if(ph!=NULL){
			for(int page=0;page<ReceivedResultCountsAllocated;page++){
				if(ph->IsResultOK(page)==false){
					ResultOk=false;
					return true;
				}
			}
		}
		else{
			return false;
		}
	}
	ResultOk=true;
	return true;
}
ResultBaseForAlgorithmRoot	*ResultInspection::GetResultBaseForAlgorithm(AlgorithmBase *base)
{
	for(ResultBaseForAlgorithmRoot *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetLogicDLL()->GetInstance()==base){
			return r;
		}
	}
	return NULL;
}


TmpNGDim::TmpNGDim(void)
	:ServiceForLayers(NULL)
{
	Dim	=NULL;
	XLen	=0;
	YLen	=0;
	XNumb	=0;
	YNumb	=0;

}
TmpNGDim::~TmpNGDim(void)
{
	if(Dim!=NULL){
		for(int y=0;y<YNumb;y++){
			delete	[]Dim[y];
		}
		delete	[]Dim;
		Dim=NULL;
	}
	XLen	=0;
	YLen	=0;
	XNumb	=0;
	YNumb	=0;
}


void	TmpNGDim::Set(LayersBase *Base)
{
	SetLayersBase(Base);

	if(GetLayersBase()->GetResultDLLBase()==NULL || GetLayersBase()->GetResultDLLBase()->GetFirst()==NULL)
		return;
	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
	if(RBase!=NULL){
		XLen	=RBase->NGImageWidth-2*RBase->NGImageBevel;
		YLen	=RBase->NGImageHeight-2*RBase->NGImageBevel;

		XNumb	=(GetDotPerLine()+XLen-1)/XLen;
		YNumb	=(GetMaxLines()  +YLen-1)/YLen;

		Dim=new NPListPack<TmpNGRectClass> *[YNumb];
		for(int y=0;y<YNumb;y++){
			Dim[y]=new NPListPack<TmpNGRectClass>[XNumb];
		}
	}
}

NPListPack<TmpNGRectClass>	*TmpNGDim::GetPoint(int X ,int Y)
{
	if(XLen==0 || YLen==0)
		return NULL;
	int	Xn=X/XLen;
	int	Yn=Y/YLen;
	if(0<=Xn && Xn<XNumb && 0<=Yn && Yn<YNumb){
		return &(Dim[Yn])[Xn];
	}
	return NULL;
}

void	ResultInItemRoot::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect ,ErrorGroupPack &SpecializedGroup)
{
	if(Error<2){
		return;
	}
	if(GetLogicDLL()->BindSpecialResult(this ,SpecializedGroup)==true){
		return;
	}

	if(PosList.GetFirst()!=NULL){
		for(ResultPosList *k=PosList.GetFirst();k!=NULL;k=k->GetNext()){
			int	X,Y;
			bool	Found=false;
			k->GetPosInTarget(this,X,Y);
			TmpNGRectClass *c;
			for(c=TmpRect.GetFirst();c!=NULL;c=c->GetNext()){
				if(c->IsInclude(X,Y)==true && c->PieceAreaNumber==k->PieceAreaNumber){
					Found=true;
					break;
				}
			}
			if(Found==true){
				if(c->ImportanceLevel>k->ImportanceLevel){
					c->ImportanceLevel=k->ImportanceLevel;
				}
				c->PieceAreaNumber=k->PieceAreaNumber;
				if(c->NGSize<k->NGSize){
					c->NGSize=k->NGSize;
				}
			}
			else{
				TmpNGRectClass *CMin=NULL;
				int	CArea=10000*10000;
				for(TmpNGRectClass *c=TmpRect.GetFirst();c!=NULL;c=c->GetNext()){
					int	x1=min(c->x1,X);
					int	y1=min(c->y1,Y);
					int	x2=max(c->x2,X);
					int	y2=max(c->y2,Y);
					if((x2-x1)<(ImageW-Bevel*2) && (y2-y1)<(ImageH-Bevel*2)
					&&  c->PieceAreaNumber==k->PieceAreaNumber){
						int	carea=(x2-x1)*(y2-y1);
						if(carea<CArea){
							CMin=c;
							CArea=carea;
						}
					}
				}
				if(CMin!=NULL){
					CMin->x1=min(CMin->x1,X);
					CMin->y1=min(CMin->y1,Y);
					CMin->x2=max(CMin->x2,X);
					CMin->y2=max(CMin->y2,Y);
					CMin->mx+=AlignedX+k->Rx;
					CMin->my+=AlignedY+k->Ry;
					CMin->Count++;
					if(CMin->ImportanceLevel>k->ImportanceLevel){
						CMin->ImportanceLevel=k->ImportanceLevel;
					}
					if(CMin->NGSize<k->NGSize){
						CMin->NGSize=k->NGSize;
					}
					continue;
				}
				RectClassWithCause *cs=new RectClassWithCause();
				cs->x1=X;
				cs->y1=Y;
				cs->x2=X;
				cs->y2=Y;
				cs->CauseStr=ResultItemToString();
				cs->ItemName=(GetAlgorithmItem()!=NULL)?GetAlgorithmItem()->GetItemName():/**/"";
				cs->mx+=AlignedX+k->Rx;
				cs->my+=AlignedY+k->Ry;
				cs->ImportanceLevel=k->ImportanceLevel;
				cs->PieceAreaNumber=k->PieceAreaNumber;
				cs->NGSize=k->NGSize;
				cs->Count++;
				TmpRect.AppendList(cs);
			}
		}
	}
	else{
		int	X,Y;
		bool	Found=false;
		GetCenter(X,Y);
		TmpNGRectClass *c;
		for(c=TmpRect.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->IsInclude(X,Y)==true){
				Found=true;
				break;
			}
		}
		if(Found==false){
			TmpNGRectClass *CMin=NULL;
			int	CArea=10000*10000;
			for(TmpNGRectClass *c=TmpRect.GetFirst();c!=NULL;c=c->GetNext()){
				int	x1=min(c->x1,X);
				int	y1=min(c->y1,Y);
				int	x2=max(c->x2,X);
				int	y2=max(c->y2,Y);
				if((x2-x1)<(ImageW-Bevel*2) && (y2-y1)<(ImageH-Bevel*2)){
					int	carea=(x2-x1)*(y2-y1);
					if(carea<CArea){
						CMin=c;
						CArea=carea;
					}
				}
			}
			if(CMin!=NULL){
				CMin->x1=min(CMin->x1,X);
				CMin->y1=min(CMin->y1,Y);
				CMin->x2=max(CMin->x2,X);
				CMin->y2=max(CMin->y2,Y);
				CMin->mx+=AlignedX+ItemSearchedX;
				CMin->my+=AlignedY+ItemSearchedY;
				CMin->Count++;
			}
			RectClassWithCause *cs=new RectClassWithCause();
			cs->x1=X;
			cs->y1=Y;
			cs->x2=X;
			cs->y2=Y;
			cs->CauseStr=ResultItemToString();
			cs->ItemName=(GetAlgorithmItem()!=NULL)?GetAlgorithmItem()->GetItemName():/**/"";
			cs->mx+=AlignedX+ItemSearchedX;
			cs->my+=AlignedY+ItemSearchedY;
			cs->Count++;
			TmpRect.AppendList(cs);
		}
	}
}

void	ResultInItemRoot::BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim ,ErrorGroupPack &SpecializedGroup)
{
	if(Error<2){
		return;
	}
	if(GetLogicDLL()->BindSpecialResult(this ,SpecializedGroup)==true){
		return;
	}

	if(PosList.GetFirst()!=NULL){
		for(ResultPosList *k=PosList.GetFirst();k!=NULL;k=k->GetNext()){
			int	X,Y;
			bool	Found=false;
			k->GetPosInTarget(this,X,Y);
			TmpNGRectClass *c;
			NPListPack<TmpNGRectClass>	*L=TmpRectDim.GetPoint(X,Y);
			if(L!=NULL){
				TmpNGRectClass *c;
				for(c=L->GetFirst();c!=NULL;c=c->GetNext()){
					if(c->PieceAreaNumber==k->PieceAreaNumber){
						break;
					}
				}
				if(c==NULL){
					RectClassWithCause *cs=new RectClassWithCause();
					cs->x1=X;
					cs->y1=Y;
					cs->x2=X;
					cs->y2=Y;
					cs->CauseStr=ResultItemToString();
					cs->ItemName=(GetAlgorithmItem()!=NULL)?GetAlgorithmItem()->GetItemName():/**/"";
					cs->mx+=AlignedX+k->Rx;
					cs->my+=AlignedY+k->Ry;
					cs->ImportanceLevel=k->ImportanceLevel;
					cs->PieceAreaNumber=k->PieceAreaNumber;
					cs->NGSize=k->NGSize;
					cs->Count++;
					L->AppendList(cs);
				}
				else{
					if(c->ImportanceLevel>k->ImportanceLevel){
						c->ImportanceLevel=k->ImportanceLevel;
					}
					c->PieceAreaNumber=k->PieceAreaNumber;
					if(c->NGSize<k->NGSize){
						c->NGSize=k->NGSize;
					}
					c->x1=min(c->x1,X);
					c->y1=min(c->y1,Y);
					c->x2=max(c->x2,X);
					c->y2=max(c->y2,Y);
					c->mx+=AlignedX+k->Rx;
					c->my+=AlignedY+k->Ry;
					c->Count++;
				}
			}
		}
	}
	else{
		int	X,Y;
		bool	Found=false;
		GetCenter(X,Y);
		NPListPack<TmpNGRectClass>	*L=TmpRectDim.GetPoint(X,Y);
		if(L!=NULL){
			RectClassWithCause *cs=new RectClassWithCause();
			cs->x1=X;
			cs->y1=Y;
			cs->x2=X;
			cs->y2=Y;
			cs->CauseStr=ResultItemToString();
			cs->ItemName=(GetAlgorithmItem()!=NULL)?GetAlgorithmItem()->GetItemName():/**/"";
			cs->mx+=AlignedX+ItemSearchedX;
			cs->my+=AlignedY+ItemSearchedY;
			cs->Count++;
			L->AppendList(cs);
		}
	}
}


bool	ResultInspection::BuildNGImages(void)
{
	if(GetResultDLLBase()==NULL){
		return true;
	}

	NPListPack<TmpNGRectClass>	**TmpRect=new NPListPack<TmpNGRectClass>*[GetPhaseNumb()];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		TmpRect[phase]=new NPListPack<TmpNGRectClass>[GetPageNumb()];
	}
	int	ImageW	=GetResultDLLBase()->NGImageWidth;
	int	ImageH	=GetResultDLLBase()->NGImageHeight;
	int	Bevel	=GetResultDLLBase()->NGImageBevel;

	ErrorGroupPack *SpecializedGroup=new ErrorGroupPack[GetPageNumb()];
	for(ResultBaseForAlgorithmRoot *B=ResultBaseDim.GetFirst();B!=NULL;B=B->GetNext()){
		B->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect,SpecializedGroup);
	}
	IntList	PhaseList;
	//GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());
	if(GetParamGlobal()->ModePhaseExecuteManageResult==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteManageResult==-1){
		GetParamGlobal()->GetPhaseNumber(PhaseList ,GetLayersBase()->GetCurrentScanPhaseNumber());
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteManageResult>=0){
		PhaseList.Add(GetParamGlobal()->ModePhaseExecuteManageResult);
	}


	for(IntClass *phi=PhaseList.GetFirst();phi!=NULL;phi=phi->GetNext()){
		int	phase=phi->GetValue();
		NGImageContainerInPhase	*Ph=NGImageInPhase[phase];
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}
		else{
			Ph->ClearAll();
		}
		
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
			if(s==NULL){
				s=new NGImageContainerInPage(GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage)
																,GetLayersBase());
				Ph->AppendListPageData(s);
			}
			for(TmpNGRectClass *c=(TmpRect[phase])[localPage].GetFirst();c!=NULL;c=c->GetNext()){
				RectClassWithCause	*cc=dynamic_cast<RectClassWithCause *>(c);
				ErrorGroup	*k=new ErrorGroup(GetLayersBase());
				k->SetRectangle(c->x1,c->y1,c->x2,c->y2);
				k->SetPage(localPage);
				k->SetImportanceLevel(c->ImportanceLevel);
				k->SetPieceAreaNumber(c->PieceAreaNumber);
				k->SetNGSize(c->NGSize);
				if(cc!=NULL){
					k->SetCause(cc->CauseStr);
					k->SetName(cc->ItemName);
				}
				k->SetMxy(c->GetMx(),c->GetMy());
				s->AddErrorGroupData(k);	
			}
			for(;;){
				ErrorGroup *g=SpecializedGroup[localPage].GetFirst();
				if(g==NULL){
					break;
					}
				SpecializedGroup[localPage].RemoveList(g);
				s->AddErrorGroupData(g);
				TmpNGRectClass *c;
				int	gx1,gy1,gx2,gy2;
				g->GetXY(gx1,gy1,gx2,gy2);
				for(c=(TmpRect[phase])[localPage].GetFirst();c!=NULL;c=c->GetNext()){
					if(c->x1<=gx1 && gx2<=c->x2 && c->y1<=gy1 && gy2<=c->y2
					&& c->PieceAreaNumber==g->GetPieceAreaNumber()){
						break;
					}
				}
				if(c==NULL){
					for(c=(TmpRect[phase])[localPage].GetFirst();c!=NULL;c=c->GetNext()){
						int	x1=min(c->x1,gx1);
						int	y1=min(c->y1,gy1);
						int	x2=max(c->x2,gx2);
						int	y2=max(c->y2,gy2);
						if(x2-x1<ImageW-2*Bevel && y2-y1<ImageH-2*Bevel
						&& c->PieceAreaNumber==g->GetPieceAreaNumber()){
							c->x1=x1;
							c->y1=y1;
							c->x2=x2;
							c->y2=y2;
							c->mx+=g->GetMx();
							c->my+=g->GetMy();
							if(c->ImportanceLevel>g->GetImportanceLevel()){
								c->ImportanceLevel	=g->GetImportanceLevel();
							}
							if(c->NGSize<g->GetNGSize()){
								c->NGSize	=g->GetNGSize();
							}
							c->Count++;
							break;
						}
					}
					if(c==NULL){
						c=new RectClassWithCause();
						c->x1=gx1;
						c->y1=gy1;
						c->x2=gx2;
						c->y2=gy2;
						c->mx+=g->GetMx();
						c->my+=g->GetMy();
						c->ImportanceLevel	=g->GetImportanceLevel();
						c->PieceAreaNumber	=g->GetPieceAreaNumber();
						c->NGSize			=g->GetNGSize();
						c->Count++;
						(TmpRect[phase])[localPage].AppendList(c);
					}
				}
			}
		}
	}
	delete	[]SpecializedGroup;

	for(IntClass *phi=PhaseList.GetFirst();phi!=NULL;phi=phi->GetNext()){
		int	phase=phi->GetValue();
		NGImageContainerInPhase	*Ph=NGImageInPhase[phase];
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}

		for(int localPage=0;localPage<GetPageNumb();localPage++){
			NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
			int32	N=0;
			(TmpRect[phase])[localPage].Sort();
			for(TmpNGRectClass *c=(TmpRect[phase])[localPage].GetFirst();c!=NULL && N<GetParamGlobal()->MaxNGCountsPerCam && N<GetParamGlobal()->MaxNGImageNumbPerPage;c=c->GetNext(),N++){
				int	Cx,Cy;
				c->GetCenter(Cx,Cy);
				NGImage	*d=s->GetNGImageFromStockker();
				if(d==NULL){
					d=new NGImage();
				}
				int	gx1=Cx-ImageW/2;
				int	gy1=Cy-ImageH/2;
				int	gx2=gx1+ImageW;
				int	gy2=gy1+ImageH;
				if(gx1<0){
					gx1=0;
					gx2=gx1+ImageW;
				}
				if(gy1<0){
					gy1=0;
					gy2=gy1+ImageH;
				}
				if(gx2>=GetParamGlobal()->DotPerLine){
					gx2=GetParamGlobal()->DotPerLine-1;
					gx1=gx2-ImageW;
				}
				if(gy2>=GetParamGlobal()->MaxLines){
					gy2=GetParamGlobal()->MaxLines-1;
					gy1=gy2-ImageH;
				}
				d->SetRectangle(gx1,gy1, gx2,gy2);
				d->SetMxy(c->GetMx(),c->GetMy());
				d->SetNumber(N);
				d->SetGlobalPage(GetLayersBase()->GetGlobalPageFromLocal(localPage));
				s->AddNGImageData(d);			
			}
			if(N!=0){
				s->SetCompressedFlag(false);
				DataInPage	*P=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(localPage);
				s->CopyImageFromTarget(P);
				if(GetParamGlobal()->BufferedProcessing==false){
					P->SetCompressedContainer(s);
				}
				else{
					s->CompressImages();
				}
			}
			else{
				s->SetCompressedFlag(true);
			}
		}
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		delete	[]TmpRect[phase];
	}
	delete	[]TmpRect;

	return true;
}

bool	ResultInspection::BuildNGImages2(void)
{
	if(GetResultDLLBase()==NULL){
		return true;
	}

	TmpNGDim	**TmpRect=new TmpNGDim*[GetPhaseNumb()];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		TmpRect[phase]=new TmpNGDim[GetPageNumb()];
		for(int page=0;page<GetPageNumb();page++){
			(TmpRect[phase])[page].Set(GetLayersBase());
		}
	}
	int	ImageW	=GetResultDLLBase()->NGImageWidth;
	int	ImageH	=GetResultDLLBase()->NGImageHeight;
	int	Bevel	=GetResultDLLBase()->NGImageBevel;

	ErrorGroupPack *SpecializedGroup=new ErrorGroupPack[GetPageNumb()];
	for(ResultBaseForAlgorithmRoot *B=ResultBaseDim.GetFirst();B!=NULL;B=B->GetNext()){
		B->BuildNGImages(ImageW ,ImageH ,Bevel ,TmpRect,SpecializedGroup);
	}
	IntList	PhaseList;
	//GetParamGlobal()->GetPhaseNumber(PhaseList,GetLayersBase()->GetCurrentScanPhaseNumber());

	if(GetParamGlobal()->ModePhaseExecuteManageResult==-2){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteManageResult==-1){
		GetParamGlobal()->GetPhaseNumber(PhaseList ,GetLayersBase()->GetCurrentScanPhaseNumber());
	}
	else
	if(GetParamGlobal()->ModePhaseExecuteManageResult>=0){
		PhaseList.Add(GetParamGlobal()->ModePhaseExecuteManageResult);
	}

	for(IntClass *phi=PhaseList.GetFirst();phi!=NULL;phi=phi->GetNext()){
		int	phase=phi->GetValue();
		NGImageContainerInPhase	*Ph=NGImageInPhase[phase];
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}
		else{
			Ph->ClearAll();
		}
		
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
			if(s==NULL){
				s=new NGImageContainerInPage(GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),localPage)
																,GetLayersBase());
				Ph->AppendListPageData(s);
			}
			TmpNGDim	&L=(TmpRect[phase])[localPage];
			for(int Yn=0;Yn<L.YNumb;Yn++){
				for(int Xn=0;Xn<L.XNumb;Xn++){
					NPListPack<TmpNGRectClass>	&P=(L.Dim[Yn])[Xn];
					for(TmpNGRectClass *c=P.GetFirst();c!=NULL;c=c->GetNext()){
						RectClassWithCause	*cc=dynamic_cast<RectClassWithCause *>(c);
						ErrorGroup	*k=new ErrorGroup(GetLayersBase());
						k->SetRectangle(c->x1,c->y1,c->x2,c->y2);
						k->SetPage(localPage);
						k->SetImportanceLevel(c->ImportanceLevel);
						k->SetPieceAreaNumber(c->PieceAreaNumber);
						k->SetNGSize(c->NGSize);
						if(cc!=NULL){
							k->SetCause(cc->CauseStr);
							k->SetName(cc->ItemName);
						}
						k->SetMxy(c->GetMx(),c->GetMy());
						s->AddErrorGroupData(k);
					}
				}
			}
			for(;;){
				ErrorGroup *g=SpecializedGroup[localPage].GetFirst();
				if(g==NULL){
					break;
				}
				SpecializedGroup[localPage].RemoveList(g);
				s->AddErrorGroupData(g);
				TmpNGRectClass *c=NULL;
				int	gx1,gy1,gx2,gy2;
				g->GetXY(gx1,gy1,gx2,gy2);
				NPListPack<TmpNGRectClass>	*P=L.GetPoint((gx1+gx2)/2 ,(gy1+gy2)/2);

				if(P!=NULL){
					for(c=P->GetFirst();c!=NULL;c=c->GetNext()){
						if(c->x1<=gx1 && gx2<=c->x2 && c->y1<=gy1 && gy2<=c->y2
						&& c->PieceAreaNumber==g->GetPieceAreaNumber()){
							break;
						}
					}
				}
				if(c==NULL){
					c=new RectClassWithCause();
					c->x1=gx1;
					c->y1=gy1;
					c->x2=gx2;
					c->y2=gy2;
					c->mx+=g->GetMx();
					c->my+=g->GetMy();
					c->ImportanceLevel	=g->GetImportanceLevel();
					c->PieceAreaNumber	=g->GetPieceAreaNumber();
					c->NGSize			=g->GetNGSize();
					c->Count++;
					P->AppendList(c);
				}
			}
		}
	}
	delete	[]SpecializedGroup;

	for(IntClass *phi=PhaseList.GetFirst();phi!=NULL;phi=phi->GetNext()){
		int	phase=phi->GetValue();
		NGImageContainerInPhase	*Ph=NGImageInPhase[phase];
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}
		for(int localPage=0;localPage<GetPageNumb();localPage++){
			NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
			TmpNGDim	&L=(TmpRect[phase])[localPage];
			int32	N=0;
			for(int Yn=0;Yn<L.YNumb;Yn++){
				for(int Xn=0;Xn<L.XNumb;Xn++){
					NPListPack<TmpNGRectClass>	&P=(L.Dim[Yn])[Xn];
					for(TmpNGRectClass *c=P.GetFirst();c!=NULL;c=c->GetNext()){
						if(N<GetParamGlobal()->MaxNGCountsPerCam && N<GetParamGlobal()->MaxNGImageNumbPerPage){
							int	Cx,Cy;
							c->GetCenter(Cx,Cy);
							NGImage	*d=s->GetNGImageFromStockker();
							if(d==NULL){
								d=new NGImage();
							}
							int	gx1=Cx-ImageW/2;
							int	gy1=Cy-ImageH/2;
							int	gx2=gx1+ImageW;
							int	gy2=gy1+ImageH;
							if(gx1<0){
								gx1=0;
								gx2=gx1+ImageW;
							}
							if(gy1<0){
								gy1=0;
								gy2=gy1+ImageH;
							}
							if(gx2>=GetParamGlobal()->DotPerLine){
								gx2=GetParamGlobal()->DotPerLine-1;
								gx1=gx2-ImageW;
							}
							if(gy2>=GetParamGlobal()->MaxLines){
								gy2=GetParamGlobal()->MaxLines-1;
								gy1=gy2-ImageH;
							}
							d->SetRectangle(gx1,gy1, gx2,gy2);
							d->SetMxy(c->GetMx(),c->GetMy());
							d->SetNumber(N);
							d->SetGlobalPage(GetLayersBase()->GetGlobalPageFromLocal(localPage));
							s->AddNGImageData(d);
							N++;
						}
					}
				}
			}
			if(N!=0){
				s->SetCompressedFlag(false);
				DataInPage	*P=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(localPage);
				s->CopyImageFromTarget(P);
				if(GetParamGlobal()->BufferedProcessing==false){
					P->SetCompressedContainer(s);
				}
				else{
					s->CompressImages();
				}
			}
			else{
				s->SetCompressedFlag(true);
			}
		}
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		delete	[]TmpRect[phase];
	}
	delete	[]TmpRect;

	return true;
}

void	NGImageContainerInPage::CompressImages(void)
{
	if(GetParamGlobal()->ModeCompressNGImage==true){
		NGImage	**NGImageDimPointer;
		int	N=GetNGImageDataCount();

		NGImageDimPointer=new NGImage*[N];
		NGImageAccessor.lockForRead();
		NGImage	*c=GetNGImageDataFirst();
		for(int i=0;i<N && c!=NULL;i++,c=c->GetNext()){
			NGImageDimPointer[i]=c;
		}
	
		int	localPage=GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
		DataInPage	*P=GetLayersBase()->GetPageData(localPage);
		int	quality=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint()->NGImageQuality;
		if(GetParamGlobal()->OMPResultCompress==true){
			#pragma omp parallel       num_threads(GetParamGlobal()->OMPResultCompressNum)
			{                                                
				#pragma omp for
				for(int i=0;i<N;i++){
					NGImageDimPointer[i]->CompressImage(P,quality);
				}
			}
		}
		else{
			for(int i=0;i<N;i++){
				NGImageDimPointer[i]->CompressImage(P,quality);
			}
		}
		
		NGImageAccessor.unlock();
		delete	[]NGImageDimPointer;
	}
	Compressed=true;
}

void	NGImageContainerInPage::CopyImageFromTarget(DataInPage *PData)
{
	if(GetParamGlobal()->OutputResult==true){
		NGImage	*NGImageDim[10000];
		NGImage	**NGImageDimPointer=NGImageDim;
		NGImageAccessor.lockForRead();
		int	N=GetNGImageDataCount();

		if(N>sizeof(NGImageDim)/sizeof(NGImageDim[0])){
			NGImageDimPointer=new NGImage*[N];
		}
		NGImage	*c=GetNGImageDataFirst();
		for(int i=0;i<N && c!=NULL;i++,c=c->GetNext()){
			NGImageDimPointer[i]=c;
		}
		for(NGImage	*d=GetNGImageDataFirst();d!=NULL;d=d->GetNext()){
			d->AllocateBuffer(GetLayerNumb());
		}
		if(N>0){
			#pragma omp parallel   num_threads(GetParamGlobal()->OMPResultCompressNum)                          
			{                                                
				#pragma omp for
				for(int i=0;i<N;i++){
					NGImageDimPointer[i]->CopyImageFromTarget(PData);
				}
			}
		}
		if(NGImageDimPointer!=NGImageDim){
			delete	[]NGImageDimPointer;
		}
		NGImageAccessor.unlock();
	}
}

bool	ResultInspection::SaveNGImage(QIODevice *OStr ,int localPage)
{
	DWORD	Ver=Version_NGImage+0x80000000U;

	if(::Save(OStr,Ver)==false){
		return false;
	}
	int32	N=GetPhaseNumb();
	if(::Save(OStr,N)==false){
		return false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGImageContainerInPhase	*a=GetNGImageInPhase(phase);
		if(a!=NULL){
			if(a->SaveNGImage(OStr ,localPage)==false){
				return false;
			}
		}
	}
	return true;
}

bool	ResultInspection::SaveNGImage(FlexArea &OverlappedArea
							,int offsetX ,int offsetY
							,QIODevice *f ,int localPage)
{
	DWORD	Ver=Version_NGImage+0x80000000U;

	if(::Save(f,Ver)==false){
		return false;
	}
	int32	N=GetPhaseNumb();
	if(::Save(f,N)==false){
		return false;
	}
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGImageContainerInPhase	*a=GetNGImageInPhase(phase);
		if(a!=NULL){
			if(a->SaveNGImage(OverlappedArea
							, offsetX ,offsetY
							,f ,localPage)==false){
				return false;
			}
		}
	}
	return true;
}

ExecutedTime::ExecutedTime(void)
{
	TM_ExecutePreAlignment		=0;
	TM_ExecuteAlignment			=0;
	TM_ExecutePreProcessing		=0;
	TM_ExecuteProcessing		=0;
	TM_ExecuteProcessingRevived	=0;
	TM_ExecutePostProcessing	=0;
}

ExecutedTime	&ExecutedTime::operator=(ExecutedTime &src)
{
	TM_ExecutePreAlignment		=src.TM_ExecutePreAlignment;
	TM_ExecuteAlignment			=src.TM_ExecuteAlignment;
	TM_ExecutePreProcessing		=src.TM_ExecutePreProcessing;
	TM_ExecuteProcessing		=src.TM_ExecuteProcessing;
	TM_ExecuteProcessingRevived	=src.TM_ExecuteProcessingRevived;
	TM_ExecutePostProcessing	=src.TM_ExecutePostProcessing;
	return *this;
}

ResultDLLBaseRoot	*ResultInspection::GetResultDLLBase(void)
{
	if(GetLayersBase()->GetResultDLLBase()==NULL || GetLayersBase()->GetResultDLLBase()->GetFirst()==NULL){
		return NULL;
	}
	return GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
}
XDateTime	&ResultInspection::GetStartTimeForInspection(void)
{	
	return StartTimeForInspection;
}
void	ResultInspection::SetStartTimeForInspect(const XDateTime &d)
{	
	static	QString	LStr;
	LStr=d.toString(/**/"yy/MM/dd hh:mm:ss");
	StartTimeForInspection=d;
}
ExeResult	ResultInspection::ExecuteInitialAfterEdit	(int ExeID)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		NGImageContainerInPhase *Ph=NGImageInPhase.GetItem(phase);
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}
		Ph->ExecuteInitialAfterEdit	(ExeID);
	}
	return _ER_true;
}
void	ResultInspection::ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)
{
	for(ResultBaseForAlgorithmRoot *c=ResultBaseDim.GetFirst();c!=NULL;c=c->GetNext()){
		c->ExecuteInAllItems(Func,Something);
	}
}
void	ResultInspection::BindNGAreaListContainer(int localpage,NGAreaListContainer &List)
{
	for(ResultBaseForAlgorithmRoot *c=ResultBaseDim.GetFirst();c!=NULL;c=c->GetNext()){
		c->BindNGAreaListContainer(localpage,List);
	}
}
void	ResultInspection::ClearAllErrorGroup(void)
{
	for(NGImageContainerInPhase *a=NGImageInPhase.GetFirst();a!=NULL;a=a->GetNext()){
		a->ClearAllErrorGroup();
	}
}
bool	ResultInspection::SaveWithoutPage(QIODevice *f)
{
	WORD		Ver=3;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,StartTimeForInspection)==false){
		return false;
	}
	if(::Save(f,NGFileName)==false){
		return false;
	}
	if(::Save(f,IndexForNGFileName)==false){
		return false;
	}
	if(::Save(f,InspectionTimeMilisec)==false){
		return false;
	}
	//if(::Save(f,Compressed)==false){
	//	return false;
	//}
	if(::Save(f,InspectionID)==false){
		return false;
	}
	if(::Save(f,InspectionNumber)==false){
		return false;
	}
	if(::Save(f,IDStr)==false){
		return false;
	}
	if(::Save(f,TimeOutBreak)==false){
		return false;
	}
	if(::Save(f,MaxErrorBreak)==false){
		return false;
	}
	if(::Save(f,OutputCode)==false){
		return false;
	}
	BYTE d=(BYTE)CriticalError;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,DeliveredInfo)==false){
		return false;
	}
	if(::Save(f,RemarkData)==false){
		return false;
	}
	return true;
}
bool	ResultInspection::LoadWithoutPage(QIODevice *f)
{
	WORD		Ver;

	if(::Load(f,Ver)==false){
		return false;
	}

	if(::Load(f,StartTimeForInspection)==false){
		return false;
	}

	if(::Load(f,NGFileName)==false){
		return false;
	}
	if(::Load(f,IndexForNGFileName)==false){
		return false;
	}
	if(::Load(f,InspectionTimeMilisec)==false){
		return false;
	}
	NGImageInPhase.RemoveAll();

	//if(::Load(f,Compressed)==false){
	//	return false;
	//}
	if(::Load(f,InspectionID)==false){
		return false;
	}
	if(::Load(f,InspectionNumber)==false){
		return false;
	}
	if(::Load(f,IDStr)==false){
		return false;
	}
	if(::Load(f,TimeOutBreak)==false){
		return false;
	}
	if(::Load(f,MaxErrorBreak)==false){
		return false;
	}
	if(::Load(f,OutputCode)==false){
		return false;
	}
	BYTE d;
	if(::Load(f,d)==false){
		return false;
	}
	CriticalError=(CriticalErrorMode)d;
	if(Ver>=2){
		if(::Load(f,DeliveredInfo)==false){
			return false;
		}
	}
	if(Ver>=3){
		if(::Load(f,RemarkData)==false){
			return false;
		}
	}

	return true;
}
bool	ResultInspection::SaveOnlyPage(QIODevice *f,int page)
{
	int32	ResultBaseForAlgorithmRootCount=ResultBaseDim.GetNumber();
	if(::Save(f,ResultBaseForAlgorithmRootCount)==false){
		return false;
	}
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		QString DLLRoot;
		QString DLLName;
		a->GetAlgorithm(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false){
			return false;
		}
		if(::Save(f,DLLName)==false){
			return false;
		}
		if(a->SaveOnlyPage(f,page)==false){
			return false;
		}
	}
	int32	PhaseNumb=GetPhaseNumb();
	if(::Save(f,PhaseNumb)==false){
		return false;
	}
	for(int phase=0;phase<PhaseNumb;phase++){
		if(NGImageInPhase[phase]->SaveOnlyPage(f,page)==false){
			return false;
		}
	}
	return true;
}
bool	ResultInspection::LoadOnlyPage(QIODevice *f,int page)
{
	int32	ResultBaseForAlgorithmRootCount;
	if(::Load(f,ResultBaseForAlgorithmRootCount)==false){
		return false;
	}
	for(int i=0;i<ResultBaseForAlgorithmRootCount;i++){
		QString DLLRoot;
		QString DLLName;
		if(::Load(f,DLLRoot)==false){
			return false;
		}
		if(::Load(f,DLLName)==false){
			return false;
		}
		for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
			QString iDLLRoot;
			QString iDLLName;
			a->GetAlgorithm(iDLLRoot,iDLLName);
			if(DLLRoot==iDLLRoot && DLLName==iDLLName){
				if(a->LoadOnlyPage(f,page)==false){
					return false;
				}
				break;
			}
		}
	}
	int32	PhaseNumb;
	if(::Load(f,PhaseNumb)==false){
		return false;
	}
	for(int phase=0;phase<PhaseNumb;phase++){
		NGImageContainerInPhase	*Ph=NGImageInPhase[phase];
		if(Ph==NULL){
			Ph=new NGImageContainerInPhase(phase,GetLayersBase());
			NGImageInPhase.AppendList(Ph);
		}
		if(Ph->LoadOnlyPage(f,page)==false){
			return false;
		}
	}
	return true;
}

void	ResultInspection::CopyInspectionAttr(LayersBase *Base)
{
	InspectionTimeMilisec	=Base->GetInspectionTimeMilisec();
	InspectionID			=Base->GetCurrentInspectIDForExecute();
	InspectionNumber		=Base->GetLatchedInspectionNumber();
}

int		ResultInspection::GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)
{
	int	N=0;
	for(ResultBaseForAlgorithmRoot *c=ResultBaseDim.GetFirst();c!=NULL;c=c->GetNext()){
		int	count=c->GetPointerListOfResultPosList(OverlapArea ,&RetDim[N] ,MaxCount-N);
		N+=count;
	}
	return N;
}

NGImageContainerInPhase	*ResultInspection::GetNGImageInPhase(int phase)
{
	NGImageContainerInPhase	*h=NGImageInPhase.GetItem(phase);
	if(h==NULL){
		h=new NGImageContainerInPhase(phase
									,GetLayersBase());
		NGImageInPhase.AppendList(h);
	}
	return h;
}
/*
NGImageContainerInPage	*ResultInspection::GetNGImageInPage(int localpage)
{	
	NGImageContainerInPage	*h=NGImageInPage.GetItem(localpage);
	if(h==NULL){
		h=new NGImageContainerInPage(GetLayersBase()->GetGlobalPageFromLocal(localpage)
									,GetLayersBase());
		NGImageInPage.AppendList(h);
	}
	return h;
}
*/

void	ResultInspection::SetResultMarkForLearning(int page)
{
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		a->SetResultMarkForLearning(page);
	}
}

void	ResultInspection::ReviveResult(LearningImage *c)
{
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		a->ReviveResult(c);
	}
}

bool	ResultInspection::IsDoneCompressed(void)
{
	if(GetParamGlobal()->ModePhaseOutputResult==-3){
		for(NGImageContainerInPhase *h=NGImageInPhase.GetFirst();h!=NULL;h=h->GetNext()){
			if(h->IsDoneCompressed()==true){
				return true;
			}
		}
		return false;
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-2){
		for(NGImageContainerInPhase *h=NGImageInPhase.GetFirst();h!=NULL;h=h->GetNext()){
			if(h->IsDoneCompressed()==false){
				return false;
			}
		}
	}
	else
	if(GetParamGlobal()->ModePhaseOutputResult==-1){
		IntList PhaseCodes;
		GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
		for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
			int	phase=c->GetValue();
			NGImageContainerInPhase *h=NGImageInPhase[phase];
			if(h!=NULL && h->IsDoneCompressed()==false){
				return false;
			}
		}
		return true;
	}
	else
	if(0<=GetParamGlobal()->ModePhaseOutputResult){
		int	phase=GetParamGlobal()->ModePhaseOutputResult;
		NGImageContainerInPhase *h=NGImageInPhase[phase];
		if(h!=NULL && h->IsDoneCompressed()==false){
			return false;
		}
		return true;
	}
	return true;
}

void	ResultInspection::CalcNGCounterAgain(void)
{
	for(ResultBaseForAlgorithmRoot *a=ResultBaseDim.GetFirst();a!=NULL;a=a->GetNext()){
		a->CalcNGCounterAgain();
	}
}
bool	ResultInspection::IsFinished(void)
{
	for(int page=0;page<ReceivedResultCountsAllocated;page++){
		if(ReceivedResultCounts[page].Result<0){
			return false;
		}
	}
	return true;
}

void	ResultInspection::AddRemark(const QString &Str)
{
	RemarkData.append(Str);
}

void	ResultInspection::AddRemark(int N)
{
	RemarkData.append((const char *)&N,sizeof(N));
}

int		ResultInspection::GetRemarkStr(BYTE Buff[],int MaxBuffLen)
{
	int	Len=min(MaxBuffLen,RemarkData.size());
	memcpy(Buff,RemarkData.data(),Len);
	return Len;
}

//===========================================================================

void	ResultInspectionPointerStock::AddPoint(ResultInspection *p)
{
	ResultInspectionPointer	*r=new ResultInspectionPointer();
	r->Res=p;
	StockMutex.lock();
	AppendList(r);
	StockMutex.unlock();
}
	
ResultInspection	*ResultInspectionPointerStock::PopPointer(void)
{
	StockMutex.lock();
	ResultInspectionPointer	*p=GetFirst();
	if(p!=NULL){
		RemoveList(p);
	}
	StockMutex.unlock();
	if(p!=NULL){
		ResultInspection	*R=p->Res;
		delete	p;
		return R;
	}
	return NULL;
}

//=============================================================================================
ResultDLLBaseRoot::ResultDLLBaseRoot(LayersBase *Base)
:ServiceForLayers(Base)
{
	LangLibSolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
	NGImageWidth	=300;
	NGImageHeight	=600;
	NGImageBevel	=30;
	NGImageQuality	=15;
	PathNGImage		=/**/"Z:/NGImage";
	NotSaved		=false;

	SetParam(&NGImageWidth		, /**/"NGImage"	,/**/"NGImageWidth"		,LangLibSolver.GetString(XResult_LS,LID_349)/*"NG Image width"*/);
	SetParam(&NGImageHeight		, /**/"NGImage"	,/**/"NGImageHeight"	,LangLibSolver.GetString(XResult_LS,LID_352)/*"NG Image height"*/);
	SetParam(&NGImageBevel		, /**/"NGImage"	,/**/"NGImageBevel"		,LangLibSolver.GetString(XResult_LS,LID_355)/*"NG Image Bevel width"*/);
	SetParam(&NGImageQuality	, /**/"NGImage"	,/**/"NGImageQuality"	,LangLibSolver.GetString(XResult_LS,LID_358)/*"NG Image quality (0-100) 100 is no compress"*/);
	SetParamPath(&PathNGImage	, /**/"NGImage"	,/**/"PathNGImage"		, LangLibSolver.GetString(XResult_LS,LID_361)/*"Path to store NG Image file"*/);
	SetParam(&NotSaved			, /**/"General"	,/**/"NotSaved"			, LangLibSolver.GetString(XResult_LS,LID_364)/*"Check if result data is not saved"*/);
}

QString	ResultDLLBaseRoot::CreateNGFileNameForCommon(ResultInspection *Res)
{
	XDateTime	nowTm=Res->GetStartTimeForInspection();
	QString	ret=nowTm.toString (/**/"yyMMdd-hh")
				+GetSeparator() 
				+nowTm.toString (/**/"mmss")
				+QString(/**/"-*.jdt");
	QString	LStr;
	if(PathNGImage.right(1)==QString(/**/"\\") || PathNGImage.right(1)==::GetSeparator()){
		LStr=PathNGImage+ret;
	}
	else{
		LStr=PathNGImage+GetSeparator()+ret;
	}

	if(LStr[1]==QChar(':') && (LStr[2]==QChar('\\') || LStr[2]==QChar('/'))){
		LStr=LStr.right(LStr.length()-3);
	}
	else if(LStr[1]==QChar(':')){
		LStr=LStr.right(LStr.length()-2);
	}
	return TransformPathName(LStr);
}
QString	ResultDLLBaseRoot::CreateNGFileNameForSlaveWithDrive(int localPage ,ResultInspection *Res)
{
	XDateTime	nowTm=Res->GetStartTimeForInspection();
	int	Milisec=::GetComputerMiliSec()%1000;
	QString	ret=nowTm.toString (/**/"yyMMdd-hh")
				+GetSeparator() 
				+nowTm.toString (/**/"mmss")
				+QString(/**/"-")
				+QString:: number(Milisec)
				+QString(/**/"-")
				+QString::number(Res->GetLayersBase()->GetGlobalPageFromLocal(localPage))
				+QString(/**/".jdt");
	QString	LStr;
	if(PathNGImage.right(1)==QString(/**/"\\") || PathNGImage.right(1)==::GetSeparator()){
		LStr=PathNGImage+ret;
	}
	else{
		LStr=PathNGImage+GetSeparator()+ret;
	}
	QString	s1=LStr.remove(/**/'\r');
	QString	s2=s1.remove(/**/'\n');
	return TransformPathName(s2);
}


ResultCmdSaveSlave::ResultCmdSaveSlave(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	ResultCmdSaveSlave::Load(QIODevice *f)
{
	if(::Load(f,InspectedTime)==false){
		return false;
	}
	if(::Load(f,MachineID)==false){
		return false;
	}
	if(::Load(f,LotData)==false){
		return false;
	}
	if(::Load(f,MasterID)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	if(::Load(f,DeliveryInfo)==false){
		return false;
	}
	return true;
}
bool	ResultCmdSaveSlave::Save(QIODevice *f)
{
	if(::Save(f,InspectedTime)==false){
		return false;
	}
	if(::Save(f,MachineID)==false){
		return false;
	}
	if(::Save(f,LotData)==false){
		return false;
	}
	if(::Save(f,MasterID)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	if(::Save(f,DeliveryInfo)==false){
		return false;
	}
	return true;
}
void	ResultCmdSaveSlave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		ResultInspectionForStock	*L=GetLayersBase()->GetResultThread()->PickupForWriteInSlave(InspectedTime);
		if(L!=NULL){
			for(int page=0;page<GetPageNumb();page++){
				SlaveOutputResultQueueLeaf	*W=new SlaveOutputResultQueueLeaf(GetLayersBase()
																	,MachineID
																	,InspectedTime
																	,L
																	,Phase
																	,page
																	,LotData
																	,MasterID
																	,DeliveryInfo);
				GetLayersBase()->GetResultThread()->PushSlaveCommand(W);
				//GetLayersBase()->ResultDLLBase->OutputResultSlave (MachineID ,InspectedTime
				//						  ,L,localPage);
			}
		}
	}
}
//=============================================================================================
ResultHistry::ResultHistry(void)
{	
	MasterCode		=-1;
	ClusterID		=-1;
	Result			=-1;
	InspectionID	=-1;
	TimeOutBreak	=false;
	MaxErrorBreak	=false;	
	Written			=false;
}

bool	ResultHistry::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false){
		return false;
	}
	if(::Save(f,ClusterID)==false){
		return false;
	}
	if(::Save(f,Result)==false){
		return false;
	}
	if(::Save(f,ResultTime)==false){
		return false;
	}
	if(::Save(f,InspectionID)==false){
		return false;
	}
	if(::Save(f,TimeOutBreak)==false){
		return false;
	}
	if(::Save(f,MaxErrorBreak)==false){
		return false;
	}
	if(::Save(f,Written)==false){
		return false;
	}
	return true;
}
bool	ResultHistry::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false){
		return false;
	}
	if(::Load(f,ClusterID)==false){
		return false;
	}
	if(::Load(f,Result)==false){
		return false;
	}
	if(::Load(f,ResultTime)==false){
		return false;
	}
	if(::Load(f,InspectionID)==false){
		return false;
	}
	if(::Load(f,TimeOutBreak)==false){
		return false;
	}
	if(::Load(f,MaxErrorBreak)==false){
		return false;
	}
	if(::Load(f,Written)==false){
		return false;
	}
	return true;
}
ResultHistry	&ResultHistry::operator=(ResultHistry &src)
{
	MasterCode		=src.MasterCode;
	ClusterID		=src.ClusterID;
	Result			=src.Result;
	ResultTime		=src.ResultTime;
	InspectionID	=src.InspectionID;
	IDStr			=src.IDStr;
	TimeOutBreak	=src.TimeOutBreak;
	MaxErrorBreak	=src.MaxErrorBreak;	
	Written			=src.Written;
	return *this;
}

bool	ResultCounterList::Save(QIODevice *f)
{
	if(::Save(f,Result)==false){
		return false;
	}
	if(::Save(f,Count)==false){
		return false;
	}
	return true;
}
bool	ResultCounterList::Load(QIODevice *f)
{
	if(::Load(f,Result)==false){
		return false;
	}
	if(::Load(f,Count)==false){
		return false;
	}
	return true;
}
ResultCounterList	&ResultCounterList::operator=(ResultCounterList &src)
{
	Result	=src.Result;
	Count	=src.Count;
	return *this;
}

ResultHistryContainer::ResultHistryContainer(LayersBase	*_Base)
:ServiceForLayers(_Base)
{
}
int		ResultHistryContainer::GetCount(int32 result)
{
	int	Ret=0;
	lock.lockForRead();
	for(ResultCounterList *C=ResultCounter.GetFirst();C!=NULL;C=C->GetNext()){
		if(C->Result==result){
			Ret=C->Count;
			break;
		}
	}
	lock.unlock();
	return Ret;
}
int		ResultHistryContainer::GetAllCount(void)
{
	int	Ret=0;
	lock.lockForRead();
	for(ResultCounterList *C=ResultCounter.GetFirst();C!=NULL;C=C->GetNext()){
		Ret+=C->Count;
	}
	lock.unlock();
	return Ret;
}
void	ResultHistryContainer::SetMaxCount(int count)
{
	lock.lockForWrite();
	int	N=GetNumber()-count;
	if(N>0){
		for(int i=0;i<N;i++){
			ResultHistry *s=GetFirst();
			RemoveList(s);
			delete	s;
		}
	}
	lock.unlock();
}

void	ResultHistryContainer::AddHistry(int32 result ,const XDateTime &ResTime ,int64 inspectionID,const QString &IDStr ,bool TimeOutBreak,bool MaxErrorBreak)
{
	int	N=GetNumber();
	ResultHistry	*s=new ResultHistry();
	s->MasterCode	=GetLayersBase()->GetMasterCode();
	s->ClusterID	=GetLayersBase()->GetLotBase()->GetClusterID();
	s->Result		=result;
	s->ResultTime	=ResTime;
	s->InspectionID	=inspectionID;
	s->TimeOutBreak	=TimeOutBreak;
	s->MaxErrorBreak=MaxErrorBreak;
	s->IDStr		=IDStr;
	lock.lockForWrite();
	if(N>GetLayersBase()->GetParamGlobal()->MaxHistoryCounts){
		ResultHistry *L=GetFirst();
		RemoveList(L);
		delete	L;
	}
	AppendList(s);
	ResultCounterList *C;
	for(C=ResultCounter.GetFirst();C!=NULL;C=C->GetNext()){
		if(C->Result==result){
			C->Count++;
			break;
		}
	}
	if(C==NULL){
		C=new ResultCounterList();
		C->Result=result;
		C->Count=1;
		ResultCounter.AppendList(C);
	}
	lock.unlock();
}

void	ResultHistryContainer::SetWritten(const XDateTime &ResTime ,int64 inspectionID)
{
	lock.lockForRead();
	for(ResultHistry *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->ResultTime==ResTime
			&& L->InspectionID==inspectionID){
				L->Written=true;
				lock.unlock();
				return;
		}
	}
	lock.unlock();
}

bool	ResultHistryContainer::RemoveResult(const XDateTime &ResTime)
{
	for(ResultHistry *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ResultTime==ResTime){
			lock.lockForWrite();
			RemoveList(a);
			for(ResultCounterList *C=ResultCounter.GetFirst();C!=NULL;C=C->GetNext()){
				if(C->Result==a->Result){
					C->Count--;
					if(C->Count==0){
						ResultCounter.RemoveList(C);
						delete	C;
					}
					break;
				}
			}
			lock.unlock();
			delete	a;
			return true;
		}
	}
	return false;
}

ResultHistry *ResultHistryContainer::SetWritten(const XDateTime &ResTime)
{
	lock.lockForRead();
	for(ResultHistry *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->ResultTime==ResTime){
			L->Written=true;
			lock.unlock();
			return L;
		}
	}
	lock.unlock();
	return NULL;
}

void	ResultHistryContainer::Reset(void)
{	
	lock.lockForRead();
	RemoveAll();	
	for(ResultCounterList *C=ResultCounter.GetFirst();C!=NULL;C=C->GetNext()){
		C->Count=0;
	}
	lock.unlock();
}

bool	ResultHistryContainer::Save(QIODevice *f)
{
	lock.lockForRead();
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		lock.unlock();
		return false;
	}
	int32	M=ResultCounter.GetCount();
	if(::Save(f,M)==false){
		lock.unlock();
		return false;
	}

	for(ResultHistry *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			lock.unlock();
			return false;
		}
	}

	for(ResultCounterList *c=ResultCounter.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			lock.unlock();
			return false;
		}
	}
	lock.unlock();
	return true;
}
bool	ResultHistryContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	int32	M;
	if(::Load(f,M)==false){
		return false;
	}

	lock.lockForWrite();
	RemoveAll();
	for(int i=0;i<N;i++){
		ResultHistry *c=new ResultHistry();
		if(c->Load(f)==false){
			lock.unlock();
			return false;
		}
		AppendList(c);
	}

	ResultCounter.RemoveAll();
	for(int i=0;i<M;i++){
		ResultCounterList *c=new ResultCounterList();
		if(c->Load(f)==false){
			lock.unlock();
			return false;
		}
		ResultCounter.AppendList(c);
	}

	lock.unlock();
	return true;
}

ResultHistryContainer	&ResultHistryContainer::operator=(ResultHistryContainer &src)
{
	lock.lockForWrite();
	RemoveAll();
	for(ResultHistry *c=GetFirst();c!=NULL;c=c->GetNext()){
		ResultHistry	*d=new ResultHistry();
		*d=*c;
		AppendList(d);
	}

	for(ResultCounterList *c=ResultCounter.GetFirst();c!=NULL;c=c->GetNext()){
		ResultCounterList	*d=new ResultCounterList();
		*d=*c;
		ResultCounter.AppendList(d);
	}

	lock.unlock();
	return *this;
}