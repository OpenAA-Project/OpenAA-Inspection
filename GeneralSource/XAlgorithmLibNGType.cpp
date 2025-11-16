/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmLibNGType.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XAlgorithmLibNGType.h"
#include "XGeneralFunc.h"

	
LibNGTypeItem::LibNGTypeItem(LayersBase *base)
	:ServiceForLayers(base)
{
	TypeUniqueCode	=-1;
	TypeCode		=-1;
	NGColor			=Qt::red;
	Blink			=false;
	NGShape			=NG_Circle;
	Priority		=100;
	NextJumpMilisec	=30;
	NGName			=/**/"XXX";
}

LibNGTypeItem	&LibNGTypeItem::operator=(const LibNGTypeItem &src)
{
	TypeUniqueCode	=src.TypeUniqueCode;
	TypeCode		=src.TypeCode;
	NGColor			=src.NGColor;
	Blink			=src.Blink;
	NGShape			=src.NGShape;
	Priority		=src.Priority;
	NextJumpMilisec	=src.NextJumpMilisec;
	NGName			=src.NGName;
	return *this;
}

bool	LibNGTypeItem::SaveCommon(QIODevice *f)
{
	int32	SystemVer=1;
	if(::Save(f,SystemVer)==false)
		return false;

	if(::Save(f,TypeUniqueCode)==false)
		return false;
	if(::Save(f,TypeCode)==false)
		return false;
	if(::Save(f,NGColor)==false)
		return false;
	if(::Save(f,Blink)==false)
		return false;
	BYTE	d=(BYTE)NGShape;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,NextJumpMilisec)==false)
		return false;
	if(::Save(f,NGName)==false)
		return false;
	return true;
}
bool	LibNGTypeItem::LoadCommon(QIODevice *f)
{
	int32	SystemVer;
	if(::Load(f,SystemVer)==false)
		return false;

	if(::Load(f,TypeUniqueCode)==false)
		return false;
	if(::Load(f,TypeCode)==false)
		return false;
	if(::Load(f,NGColor)==false)
		return false;
	if(::Load(f,Blink)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	NGShape=(NGShapeType)d;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,NextJumpMilisec)==false)
		return false;
	if(::Load(f,NGName)==false)
		return false;
	return true;
}

void	LibNGTypeItem::Draw(QPainter &pnt ,int x ,int y ,int radius)
{
	int	R=radius;
	if(R==0)
		R=1;
	int	size=radius*2;
	if(NGShape==NG_Circle){
		pnt.setPen(NGColor);
		pnt.drawArc(x-R,y-R ,size,size,0,5760);
	}
	else if(NGShape==NG_FilledCircle){
		pnt.setPen(NGColor);
		pnt.setBrush(NGColor);
		pnt.drawEllipse(x-R,y-R ,size,size);
	}
	else if(NGShape==NG_Rectangle){
		pnt.setPen(NGColor);
		pnt.drawLine(x-R,y-R ,x+R,y-R);
		pnt.drawLine(x+R,y-R ,x+R,y+R);
		pnt.drawLine(x+R,y+R ,x-R,y+R);
		pnt.drawLine(x-R,y+R ,x-R,y-R);
	}
	else if(NGShape==NG_FilledRect){
		pnt.setPen(NGColor);
		pnt.setBrush(NGColor);
		pnt.drawRect(x-R,y-R ,size,size);
	}
	else if(NGShape==NG_X){
		pnt.setPen(NGColor);
		pnt.drawLine(x-R,y-R ,x+R,y+R);
		pnt.drawLine(x+R,y-R ,x-R,y+R);
	}
	else if(NGShape==NG_Star){
		pnt.setPen(NGColor);
		QPoint	P[11];
		P[0].setX(x+0);
		P[0].setY(y-R);
		P[1].setX(x+0.29389262614623656458435297731954*R);
		P[1].setY(y-0.40450849718747371205114670859141*R);
		P[2].setX(x+0.95105651629515357211643933337938*R);
		P[2].setY(y-0.30901699437494742410229341718282*R);
		P[3].setX(x+0.47552825814757678605821966668969*R);
		P[3].setY(y+0.15450849718747371205114670859141*R);
		P[4].setX(x+0.58778525229247312916870595463907*R);
		P[4].setY(y+0.80901699437494742410229341718282*R);
		P[5].setX(x+ 0);
		P[5].setY(y+0.5*R);
		P[6].setX(x-0.58778525229247312916870595463907*R);
		P[6].setY(y+0.80901699437494742410229341718282*R);
		P[7].setX(x-0.47552825814757678605821966668969*R);
		P[7].setY(y+0.15450849718747371205114670859141*R);
		P[8].setX(x-0.95105651629515357211643933337938*R);
		P[8].setY(y-0.30901699437494742410229341718282*R);
		P[9].setX(x-0.29389262614623656458435297731954*R);
		P[9].setY(y-0.40450849718747371205114670859141*R);
		P[10].setX(x+0);
		P[10].setY(y-R);

		for(int i=0;i<10;i++){
			pnt.drawLine(P[i].x(),P[i].y(),P[i+1].x(),P[i+1].y());
		}
	}
	else if(NGShape==NG_FilledStar){
		pnt.setPen(NGColor);
		pnt.setBrush(NGColor);
		QPoint	P[11];
		P[0].setX(x+0);
		P[0].setY(y-R);
		P[1].setX(x+0.29389262614623656458435297731954*R);
		P[1].setY(y-0.40450849718747371205114670859141*R);
		P[2].setX(x+0.95105651629515357211643933337938*R);
		P[2].setY(y-0.30901699437494742410229341718282*R);
		P[3].setX(x+0.47552825814757678605821966668969*R);
		P[3].setY(y+0.15450849718747371205114670859141*R);
		P[4].setX(x+0.58778525229247312916870595463907*R);
		P[4].setY(y+0.80901699437494742410229341718282*R);
		P[5].setX(x+ 0);
		P[5].setY(y+0.5*R);
		P[6].setX(x-0.58778525229247312916870595463907*R);
		P[6].setY(y+0.80901699437494742410229341718282*R);
		P[7].setX(x-0.47552825814757678605821966668969*R);
		P[7].setY(y+0.15450849718747371205114670859141*R);
		P[8].setX(x-0.95105651629515357211643933337938*R);
		P[8].setY(y-0.30901699437494742410229341718282*R);
		P[9].setX(x-0.29389262614623656458435297731954*R);
		P[9].setY(y-0.40450849718747371205114670859141*R);
		P[10].setX(x+0);
		P[10].setY(y-R);

		pnt.drawPolygon(P,10);
		//pnt.drawPolygon(P,10,Qt::WindingFill);
	}
	else if(NGShape==NG_Cross){
		pnt.setPen(NGColor);
		pnt.drawLine(x-R,y ,x+R,y);
		pnt.drawLine(x,y-R ,x,y+R);
	}
	else if(NGShape==NG_Sharp){
		int D=(size+1)/6;
		if(D==0)
			D=1;
		pnt.setPen(NGColor);
		pnt.drawLine(x-R,y+D ,x+R,y+D);
		pnt.drawLine(x-R,y-D ,x+R,y-D);
		pnt.drawLine(x+D,y-R ,x+D,y+R);
		pnt.drawLine(x-D,y-R ,x-D,y+R);
	}
}

//===================================================

bool	LibNGTypeInAlgorithm::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LibNGTypeItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		if(item->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	LibNGTypeInAlgorithm::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LibNGTypeItem *item=CreateNewItem();
		if(item->Load(f)==false)
			return false;
		AppendList(item);
	}
	return true;
}

void	LibNGTypeInAlgorithm::Draw(QPainter &pnt ,int x ,int y ,int size)
{
	for(LibNGTypeItem *item=GetFirst();item!=NULL;item=item->GetNext()){
		item->Draw(pnt ,x ,y,size);
	}
}

static	int	FuncLDim(const void *a ,const void *b)
{
	if( ((LibNGTypeItem	**)a)[0]->Priority < ((LibNGTypeItem	**)b)[0]->Priority){
		return 1;
	}
	if( ((LibNGTypeItem	**)a)[0]->Priority > ((LibNGTypeItem	**)b)[0]->Priority){
		return -1;
	}
	return 0;
}

void	LibNGTypeInAlgorithm::SortInPriority(void)
{
	LibNGTypeItem	**LDim = new LibNGTypeItem*[GetCount()];
	int	n=0;
	for(;;){
		LibNGTypeItem *k=GetFirst();
		if(k==NULL){
			break;
		}
		RemoveList(k);
		LDim[n]=k;
		n++;
	}
	QSort(LDim,n,sizeof(LDim[0]),FuncLDim);
	for(int i=0;i<n;i++){
		AppendList(LDim[i]);
	}
	delete	[]LDim;
}

void	LibraryListWithNGType::Draw(QPainter &pnt ,int x ,int y ,int size)
{
	NGList.Draw(pnt ,x ,y,size);
}

void	LibraryListWithNGTypeContainer::SortInPriority(void)
{
	for(LibraryListWithNGType *c=GetFirst();c!=NULL;c=c->GetNext()){
		c->NGList.SortInPriority();
	}
}
LibraryListWithNGType	*LibraryListWithNGTypeContainer::GetNGTypeList(int libID)
{
	for(LibraryListWithNGType *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->LibID==libID){
			return c;
		}
	}
	return NULL;
}