/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XNaming.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "NamingResource.h"
#include "XNaming.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "swap.h"
#include "XAlgorithmDLL.h"
#include <ctype.h>
#include "XDataInLayer.h"
#include "XNamingPacket.h"
#include "malloc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

NamingNameReq::NamingNameReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	NamingNameReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	NamingNameReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
NamingNameSend::NamingNameSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	Row=0;
	Column=0;
}

void	NamingNameSend::ConstructList(NamingNameReq *reqPacket,NamingBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			NamingItem	*BItem=(NamingItem *)item;
			AreaName	=BItem->GetItemName();
			Row			=BItem->Row;
			Column		=BItem->Column;
		}
	}
}

bool	NamingNameSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	return true;
}
bool	NamingNameSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Row)==false)
		return false;
	if(::Load(f,Column)==false)
		return false;
	return true;
}

//=====================================================================================

bool	NamingPointer::SetName(char *FormatStr ,int MaxX ,int MaxY)
{
	char	Buff[1000];

	char	*fp=FormatStr;
	char	*dp=Buff;
	while(*fp!=0){
		if(*fp!='['){
			*dp=*fp;
			fp++;
			dp++;
		}
		else{
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			bool	Minus=false;
			if(*fp=='-'){
				Minus=true;
				fp++;
				while(*fp==' ' || *fp=='\t')
					fp++;
			}
			else if(*fp=='+'){
				Minus=false;
				fp++;
				while(*fp==' ' || *fp=='\t')
					fp++;
			}
			char	CType;
			if(*fp=='A')
				CType='A';
			else if(*fp=='a')
				CType='a';
			else if(*fp=='N' || *fp=='n')
				CType='N';
			else
				return false;
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			int	index=0;
			int	MaxN=0;
			if(*fp=='X' || *fp=='x'){
				index=IndexX;
				MaxN=MaxX;
			}
			else if(*fp=='Y' || *fp=='y'){
				index=IndexY;
				MaxN=MaxY;
			}
			else
				return false;
			
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			
			int	Number=1;

			if(*fp!=']'){
				if(CType=='A' || CType=='a'){
					Number=GetAlphaNumber(fp);
				}
				else if(CType=='N'){
					if(sscanf(fp,/**/"%d",&Number)!=1)
						return false;
				}
				fp=strchr(fp,']');
				if(fp==NULL)
					return false;
			}
			fp++;

			if(CType=='A'){
				if(Minus==false)
					dp=SetAlphaA(dp,Number+index);
				else
					dp=SetAlphaA(dp,Number+MaxN-index);
			}
			if(CType=='a'){
				if(Minus==false)
					dp=SetAlphaa(dp,Number+index);
				else
					dp=SetAlphaa(dp,Number+MaxN-index);
			}
			if(CType=='N'){
				if(Minus==false)
					dp=SetNumber(dp,Number+index);
				else
					dp=SetNumber(dp,Number+MaxN-index);
			}
			if(dp==NULL)
				return false;
		}
	}
	*dp=0;
	AreaName=Buff;
	return true;
}

QString	NamingPointer::SetNameOnly(char *FormatStr ,int X ,int Y ,int MaxX ,int MaxY,int &Column ,int &Row)
{
	char	Buff[1000];

	char	*fp=FormatStr;
	char	*dp=Buff;
	char	IndexType;
	while(*fp!=0){
		if(*fp!='['){
			*dp=*fp;
			fp++;
			dp++;
		}
		else{
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			bool	Minus=false;
			if(*fp=='-'){
				Minus=true;
				fp++;
				while(*fp==' ' || *fp=='\t')
					fp++;
			}
			else if(*fp=='+'){
				Minus=false;
				fp++;
				while(*fp==' ' || *fp=='\t')
					fp++;
			}
			char	CType;
			if(*fp=='A')
				CType='A';
			else if(*fp=='a')
				CType='a';
			else if(*fp=='N' || *fp=='n')
				CType='N';
			else
				return /**/"";
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			int	index=0;
			int	MaxN=0;
			if(*fp=='X' || *fp=='x'){
				IndexType='X';
				index=X;
				MaxN=MaxX;
			}
			else if(*fp=='Y' || *fp=='y'){
				IndexType='Y';
				index=Y;
				MaxN=MaxY;
			}
			else
				return /**/"";
			
			fp++;
			while(*fp==' ' || *fp=='\t')
				fp++;
			
			int	Number=1;

			if(*fp!=']'){
				if(CType=='A' || CType=='a'){
					Number=GetAlphaNumber(fp);
				}
				else if(CType=='N'){
					if(sscanf(fp,/**/"%d",&Number)!=1)
						return /**/"";
				}
				fp=strchr(fp,']');
				if(fp==NULL)
					return /**/"";
			}
			fp++;
			int	HNumber=0;
			if(Minus==false)
				HNumber=Number+index;
			else
				HNumber=Number+MaxN-index;

			if(CType=='A'){
				dp=SetAlphaA(dp,HNumber);
			}
			if(CType=='a'){
				dp=SetAlphaa(dp,HNumber);
			}
			if(CType=='N'){
				dp=SetNumber(dp,HNumber);
			}
			if(IndexType=='X')
				Column	=HNumber;
			else if(IndexType=='Y')
				Row		=HNumber;

			if(dp==NULL)
				return /**/"";
		}
	}
	*dp=0;

	return Buff;
}


int	NamingPointer::GetAlphaNumber(char *fp)
{
	int	N=0;
	while(isalpha(*fp)!=0){
		N*=26;
		N += toupper(*fp)-'A';
		fp++;
	}
	return N;
}

char	*NamingPointer::SetAlphaA(char *dp,int N)
{
	int	B=26;
	for(int i=0;i<10;i++){
		if(N<B){
			B/=26;
			break;
		}
		B*=26;
	}
	do{
		int	x=N/B;
		if(N<26){
			*dp='A'+x;
		}
		else{
			*dp='A'+x-1;
		}
		dp++;
		N -= x*B;
		B/=26;
	}while(B>=1);

	return dp;
}
char	*NamingPointer::SetAlphaa(char *dp,int N)
{
	int	B=26;
	for(int i=0;i<10;i++){
		if(N<B){
			B/=26;
			break;
		}
		B*=26;
	}
	do{
		int	x=N/B;
		if(N<26){
			*dp='a'+x;
		}
		else{
			*dp='a'+x-1;
		}
		dp++;
		N -= x*B;
		B/=26;
	}while(B!=0);

	return dp;
}

char	*NamingPointer::SetNumber(char *dp,int N)
{
	int	B=10;
	for(int i=0;i<10;i++){
		if(N<B){
			B/=10;
			break;
		}
		B*=10;
	}
	do{
		int	x=N/B;
		*dp='0'+x;
		dp++;
		N -= x*B;
		B/=10;
	}while(B!=0);

	return dp;
}




NamingThreshold::NamingThreshold(NamingItem *parent):AlgorithmThreshold(parent)
{
}



bool    NamingItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;
	//if(::Save(f,AreaName)==false)
	//	return false;
	if(::Save(f,GroupID)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	return true;
}
bool    NamingItem::Load(QIODevice *f,LayersBase *LBase)
{
	GetParentBase()->SetLoadedVersion(1);
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;
	if(GetLoadedVersion()==2){
		QString	tAreaName;
		if(::Load(f,tAreaName)==false)
			return false;
		SetItemName(tAreaName);
	}
	if(GetLoadedVersion()>=2){
		if(::Load(f,GroupID)==false)
			return false;
	}
	if(GetLoadedVersion()>=4){
		if(::Load(f,Row)==false)
			return false;
		if(::Load(f,Column)==false)
			return false;
	}
	return true;
}
bool	NamingItem::SaveUnique(QIODevice *f)
{
	if(AlgorithmItemPI::SaveUnique(f)==false)
		return false;
	//if(::Save(f,AreaName)==false)
	//	return false;
	if(::Save(f,GroupID)==false)
		return false;
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	return true;
}
bool	NamingItem::LoadUnique(QIODevice *f)
{
	GetParentBase()->SetLoadedVersion(1);
	if(AlgorithmItemPI::LoadUnique(f)==false)
		return false;
	if(GetLoadedVersion()==2){
		QString	tAreaName;
		if(::Load(f,tAreaName)==false)
			return false;
		SetItemName(tAreaName);
	}
	if(GetLoadedVersion()>=2){
		if(::Load(f,GroupID)==false)
			return false;
	}
	if(GetLoadedVersion()>=4){
		if(::Load(f,Row)==false)
			return false;
		if(::Load(f,Column)==false)
			return false;
	}
	return true;
}

void	NamingItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	NamingDrawAttr	*LAttr=dynamic_cast<NamingDrawAttr *>(Attr);
	if(LAttr!=NULL){

	}
	AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	int	H=y2-y1;

	QRect	rect1((x1+movx)*ZoomRate,(y1+movy)*ZoomRate
				 ,(x2-x1)*ZoomRate  ,(H/2)*ZoomRate);
	QRect	rect2((x1+movx)*ZoomRate,(y1+H/2+movy)*ZoomRate
				 ,(x2-x1)*ZoomRate  ,(H/2)*ZoomRate);
	QString	PosStr=LangSolver.GetString(XNaming_LS,LID_10)/*"Row:"*/+QString::number(Row)+LangSolver.GetString(XNaming_LS,LID_12)/*"  Col:"*/+QString::number(Column);

	GetLayersBase()->LockDraw();
	QPainter	P(&pnt);
	P.drawText (rect1, Qt::AlignHCenter | Qt::AlignVCenter ,GetItemName());
	P.drawText (rect2, Qt::AlignHCenter | Qt::AlignVCenter ,PosStr);

	GetLayersBase()->UnlockDraw();
}

static	void NamingFunc(ResultInItemRoot *Item ,void *Something)
{
	static	QMutex	LockInside;

	NamingItem	*NItem=(NamingItem *)Something;
	if(NItem->GetParentInPage()->GetPage()==Item->GetPage()){
		for(ResultPosList *c=Item->GetPosListFirst();c!=NULL;c=c->GetNext()){
			if(NItem->GetArea().IsInclude(c->Px,c->Py)==true){
				if(Item->GetPosListFirst()==NULL)
					break;
				LockInside.lock();
				QString	Str=NItem->GetItemName();
				c->AreaNames.append(Str);
				LockInside.unlock();
				if(c->IsOK()==false){
					NItem->Result=2;
				}
			}
		}
	}
}
void	NamingItem::ClearResult(void)
{
	Result=0;
}
ExeResult	NamingItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(NGAreaDim!=NULL)
		delete	[]NGAreaDim;
	if(GetLayersBase()==NULL)
		return _ER_true;
	if(GetLayersBase()->GetResultDLLBase()==NULL)
		return _ER_true;
	if(GetLayersBase()->GetResultDLLBase()->GetFirst()==NULL)
		return _ER_true;

	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
	if(RBase==NULL)
		return _ER_true;

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	BBL	  =RBase->NGImageBevel;
	NGAreaXLen=RBase->NGImageWidth-BBL*2;
	NGAreaYLen=RBase->NGImageHeight-BBL*2;
	NGAreaXNumb	=(W+NGAreaXLen-1)/NGAreaXLen;
	NGAreaYNumb	=(H+NGAreaYLen-1)/NGAreaYLen;
	NGAreaDim=new NGAreaNaming[NGAreaXNumb*NGAreaYNumb];

	for(int y=0;y<NGAreaYNumb;y++){
		for(int x=0;x<NGAreaXNumb;x++){
			NGAreaDim[y*NGAreaXNumb+x].x1	=GetArea().GetMinX()+NGAreaXLen*x-BBL;
			NGAreaDim[y*NGAreaXNumb+x].y1	=GetArea().GetMinY()+NGAreaYLen*y-BBL;
			NGAreaDim[y*NGAreaXNumb+x].x2	=min(GetArea().GetMaxX(),NGAreaDim[y*NGAreaXNumb+x].x1+NGAreaXLen)+BBL;
			NGAreaDim[y*NGAreaXNumb+x].y2	=min(GetArea().GetMaxY(),NGAreaDim[y*NGAreaXNumb+x].y1+NGAreaYLen)+BBL;
		}
	}

	return _ER_true;
}
ExeResult	NamingItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetItemName()==/**/"")
		return _ER_true;

	if(AVector!=NULL){
		ShiftX=AVector->ShiftX;
		ShiftY=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		ShiftX=V.ShiftX;
		ShiftY=V.ShiftY;
	}
	Result=1;

	for(int y=0;y<NGAreaYNumb;y++){
		for(int x=0;x<NGAreaXNumb;x++){
			NGAreaDim[y*NGAreaXNumb+x].NGNumb=0;
		}
	}
	ResultInspection	*R=Res->GetResultInspection();
	R->ExecuteInAllItems(GetPhaseCode(),NamingFunc,this);
	return _ER_true;
}
void	NamingItem::DrawResult(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(GetVisible()==false){
			return;
		}
		AlgorithmBase	*ABase=GetParentBase();
		if(ABase!=NULL && ABase->GetModeToShowNGMark()==false){
			return;
		}

		int	CircleWidth=0;
		bool	DrawBlueNGMark=false;
		if(GetParamGlobal()!=NULL){
			CircleWidth=GetParamGlobal()->ResultNGCircleWidth;
			DrawBlueNGMark=GetParamGlobal()->DrawBlueNGMark;

			if(Result>=2){
				QColor	NGColor=GetParamGlobal()->NGCircleColor;
				NGColor.setAlpha(GetParamGlobal()->NGColorTranparency);
				QRgb	Col=NGColor.rgba();
				QColor	RCol=QColor(255-qRed(Col),255-qGreen(Col),255-qBlue(Col));
				int	Cx,Cy;
				GetCenter(Cx,Cy);
				int	R=ZoomRate;
				if(R<GetParamGlobal()->NGMarkRadius){
					R=GetParamGlobal()->NGMarkRadius;
				}
				int	R2=R+R;
				int	x1=(Cx+Res->GetAlignedX()+MovX)*ZoomRate-R;
				int y1=(Cy+Res->GetAlignedY()+MovY)*ZoomRate-R;

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
		}
	}
}
void	NamingItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			NamingItem	*Src=dynamic_cast<NamingItem *>(Data);
			if(Src!=NULL){
				SetItemName(Src->GetItemName());
				Row=Src->Row;
				Column=Src->Column;
			}
		}
	}
}
void	NamingItem::BindResult(ResultInItemRoot *Item,ResultPosList *RPos)
{
	NamingBase	*ABase=(NamingBase *)GetParentBase();

	if(ABase->BindResultByArea==true){

		if(Item->IsOk()==false && RPos->IsOverlap(GetArea())==true){
			int	x1,y1,x2,y2;
			RPos->AreaNames.append(GetItemName());

			int	Mx=Item->GetAlignedX()+RPos->Rx;
			int	My=Item->GetAlignedY()+RPos->Ry;
			RPos->GetXY(x1,y1,x2,y2);

			if(NGAreaXLen==0 || NGAreaYLen==0)
				return;
			int	mx1=(x1+Mx-GetArea().GetMinX())/NGAreaXLen;
			int	mx2=(x2+My-GetArea().GetMinX())/NGAreaXLen;
			int	my1=(y1+Mx-GetArea().GetMinY())/NGAreaYLen;
			int	my2=(y2+My-GetArea().GetMinY())/NGAreaYLen;
			if(NGAreaXLen<=mx1 || mx2<0 || NGAreaYLen<=my1 || my2<0)
				return;
			mx1=max(0,mx1);
			my1=max(0,my1);
			mx2=min(mx2,NGAreaXLen-1);
			my2=min(my2,NGAreaYLen-1);

			for(int y=my1;y<=my2;y++){
				for(int x=mx1;x<=mx2;x++){
					NGAreaDim[y*NGAreaXNumb+x].NGNumb++;
				}
			}
			/*
			ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
			ResultInspection	*p=Item->GetResultInspection();
			NGImageContainerInPhase	*NGPhase=p->GetNGImageInPhase(GetPhaseCode());
			if(NGPhase!=NULL){
				NGImageContainerInPage	*h=NGPhase->GetNGImageInPage(GetPage());
				if(x1==x2 && y1==y2){
					ErrorGroup *e;
					for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
						ErrorGroupNaming	*g=(ErrorGroupNaming *)e;
						if(g->Item!=this)
							continue;
						int	ex1,ey1,ex2,ey2;
						e->GetXY(ex1,ey1,ex2,ey2);
						int	rx1=min(ex1,x1+Mx);
						int	ry1=min(ey1,y1+My);
						int	rx2=max(ex2,x1+Mx);
						int	ry2=max(ey2,y1+My);
						if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							g->SetRectangle(rx1,ry1,rx2,ry2);
							break;
						}
					}
					if(e==NULL){
						ErrorGroupNaming	*g=new ErrorGroupNaming(GetLayersBase());
						g->SetRectangle(x1+Mx,y1+My,x2+Mx,y2+My);
						g->Item=this;
						g->SetName(GetItemName());
						h->AddErrorGroupData(g);
					}
				}
				else{
					ErrorGroup *e;
					for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
						ErrorGroupNaming	*g=(ErrorGroupNaming *)e;
						if(g->Item!=this)
							continue;
						int	ex1,ey1,ex2,ey2;
						e->GetXY(ex1,ey1,ex2,ey2);
						int	rx1=min(ex1,x1+Mx);
						int	ry1=min(ey1,y1+My);
						int	rx2=max(ex2,x2+Mx);
						int	ry2=max(ey2,y2+My);
						if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							g->SetRectangle(rx1,ry1,rx2,ry2);
							break;
						}
					}
					if(e==NULL){
						if((x2-x1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (y2-y1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							ErrorGroupNaming	*g=new ErrorGroupNaming(GetLayersBase());
							g->SetRectangle(x1+Mx,y1+My,x2+Mx,y2+My);
							g->Item=this;
							g->SetName(GetItemName());
							h->AddErrorGroupData(g);
						}
						else{
							FlexArea	A;
							FlexArea	B;
							A.Sub(RPos->NGShape, GetArea());
							B.Sub(RPos->NGShape,A);
							B.GetCenter(x1,y1);
							ErrorGroupNaming	*g=new ErrorGroupNaming(GetLayersBase());
							g->SetRectangle( x1+Mx-RBase->NGImageWidth /2+RBase->NGImageBevel,y1+My-RBase->NGImageHeight/2+RBase->NGImageBevel
											,x2+Mx+RBase->NGImageWidth /2-RBase->NGImageBevel,y2+My+RBase->NGImageHeight/2-RBase->NGImageBevel);
							g->Item=this;
							g->SetName(GetItemName());
							h->AddErrorGroupData(g);
						}
					}
				}
			}
			*/
		}
	}
}

void	NamingItem::MakeErrorGroup(NGImageContainerInPage *h)
{
	for(int y=0;y<NGAreaYNumb;y++){
		for(int x=0;x<NGAreaXNumb;x++){
			NGAreaNaming	*A=&NGAreaDim[y*NGAreaXNumb+x];
			if(A->NGNumb!=0){
				ErrorGroupNaming	*g=new ErrorGroupNaming(GetLayersBase());
				g->SetRectangle(A->x1,A->y1,A->x2,A->y2);
				g->Item=this;
				g->SetName(GetItemName());
				h->AddErrorGroupData(g);
			}
		}
	}
}
void	NamingItem::SetError(short e)
{
	AlgorithmItemPI::SetError(e);
	if(e==1){
		Result=1;
	}
	else if(e>=2){
		Result=2;
	}
	else{
		Result=0;
	}
}
QString	NamingItem::GetComment(Type_ItemComment t)
{
	return QString::number(Column)+QString(/**/",")+QString::number(Row)+QString(/**/":")+GetItemName();
}

//====================================================================

static	int	SortFuncDim(const void *a ,const void *b)
{
	AlgorithmItemPI	**ai=(AlgorithmItemPI **)a;
	AlgorithmItemPI	**bi=(AlgorithmItemPI **)b;
	int	x1=ai[0]->GetArea().GetMinX();
	int	x2=bi[0]->GetArea().GetMinX();
	int	k= x1-x2;
	if(k!=0)
		return k;
	int	w1=ai[0]->GetArea().GetWidth();
	int	w2=bi[0]->GetArea().GetWidth();
	return w1-w2;
}

void	NamingInPage::GenerateIndex(bool OnlySelected)
{
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		if(OnlySelected==false || p->GetSelected()==true){
			NamingItem	*Item=dynamic_cast<NamingItem *>(p);
			Item->Row	=-1;
			Item->Column=-1;
		}
	}
	for(int Row=0;;Row++){
		AlgorithmItemPI	*LeftXY=NULL;
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(OnlySelected==false || p->GetSelected()==true){
				NamingItem	*Item=dynamic_cast<NamingItem *>(p);
				if(Item->Row==-1){
					LeftXY=Item;
					break;
				}
			}
		}
		if(LeftXY==NULL){
			break;
		}
		int	Ky1=LeftXY->GetArea().GetMinY();
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(OnlySelected==false || p->GetSelected()==true){
				NamingItem	*Item=dynamic_cast<NamingItem *>(p);
				if(Item->Row==-1){
					int	My1=p->GetArea().GetMinY();
					if(My1<Ky1){
						LeftXY=p;
						Ky1=My1;
					}
				}
			}
		}
		int	Ky2=LeftXY->GetArea().GetMaxY();
		int	L=Ky2-Ky1;
		AlgorithmItemPI	*Dim[1000];
		int				DimCount=0;
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(OnlySelected==false || p->GetSelected()==true){
				NamingItem	*Item=dynamic_cast<NamingItem *>(p);
				if(Item->Row==-1){
					int	Cx,Cy;
					p->GetArea().GetCenter(Cx,Cy);
					if(Ky1+L/4<=Cy && Cy<Ky2-L/4){
						Dim[DimCount]=p;
						DimCount++;
					}
				}
			}
		}
		if(DimCount==0)
			break;
		QSort(Dim,DimCount,sizeof(Dim[0]),SortFuncDim);
		for(int i=0;i<DimCount;i++){
			if(OnlySelected==false || Dim[i]->GetSelected()==true){
				NamingItem	*Item=dynamic_cast<NamingItem *>(Dim[i]);
				Item->Column=i;
				Item->Row	=Row;
			}
		}
		if(DimCount>0){
			int	AddedColumn=0;
			for(int page=0;page<GetLayersBase()->GetGlobalPageNumb();page++){
				if(page==GetGlobalPage())
					continue;
				SlaveCommReqOverlappedIndex	RCmd(GetLayersBase(),sRoot,sName,page);
				SlaveCommAckOverlappedIndex	ACmd(GetLayersBase(),sRoot,sName,page);
				RCmd.GlobalArea		=Dim[0]->GetArea();
				RCmd.GlobalArea.MoveToNoClip(GetGlobalOutlineOffset()->x,GetGlobalOutlineOffset()->y);
				if(RCmd.Send(page,0,ACmd)==true){
					if(ACmd.Found==true){
						AddedColumn=ACmd.Column;
						break;
					}
				}
			}
			for(int i=0;i<DimCount;i++){
				if(OnlySelected==false || Dim[i]->GetSelected()==true){
					NamingItem	*Item=dynamic_cast<NamingItem *>(Dim[i]);
					Item->Column=AddedColumn+i;
				}
			}
		}
	}
}
ExeResult	NamingInPage::ExecuteInitialAfterEdit	(int ExeID 
													,ResultInPageRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmInPagePI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);

	NamingBase	*PBase=(NamingBase *)GetParentBase();
	if(PBase->ResetIndexAfterEdit==true){
		GenerateIndex(false);
	}

	return _ER_true;
}

void	NamingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddNamingAreaPacket	*AddNamingAreaPacketVar=dynamic_cast<AddNamingAreaPacket *>(packet);
	if(AddNamingAreaPacketVar!=NULL){
		NamingItem	*item=(NamingItem *)CreateItem();
		item->SetItemName(AddNamingAreaPacketVar->AreaName);
		item->SetArea(AddNamingAreaPacketVar->Area);
		item->Column	=AddNamingAreaPacketVar->Column;
		item->Row		=AddNamingAreaPacketVar->Row;
		item->SetManualCreated(true);
		AppendItem(item);
		return;
	}
	ReqBuildItemPointerNaming	*ReqBuildItemPointerNamingVar=dynamic_cast<ReqBuildItemPointerNaming *>(packet);
	if(ReqBuildItemPointerNamingVar!=NULL){
		BuildItemPointer(*ReqBuildItemPointerNamingVar->Stocker);
		return;
	}
	ReqSetItemPointerNaming	*ReqSetItemPointerNamingVar=dynamic_cast<ReqSetItemPointerNaming *>(packet);
	if(ReqSetItemPointerNamingVar!=NULL){
		SetItemPointer(*ReqSetItemPointerNamingVar->Stocker);
		return;
	}
	ReqBuildItemPointerNamingPage	*ReqBuildItemPointerNamingPageVar=dynamic_cast<ReqBuildItemPointerNamingPage *>(packet);
	if(ReqBuildItemPointerNamingPageVar!=NULL){
		GetItemPointer(*ReqBuildItemPointerNamingPageVar->Stocker);
		return;
	}
	ReqItemFromAreaName	*ReqItemFromAreaNameVar=dynamic_cast<ReqItemFromAreaName *>(packet);
	if(ReqItemFromAreaNameVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(ReqItemFromAreaNameVar->AreaName==((NamingItem *)p)->GetItemName()){
				ReqItemFromAreaNameVar->Item=((NamingItem *)p);
			}
		}
		return;
	}
	ReqNamingAreas	*ReqNamingAreasVar=dynamic_cast<ReqNamingAreas *>(packet);
	if(ReqNamingAreasVar!=NULL){
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			NamingItem	*item=(NamingItem *)p;
			ReqNamingAreasVar->Areas.append(item->GetItemName());
		}
		return;
	}
	ReqGenerateIndex	*ReqGenerateIndexVar=dynamic_cast<ReqGenerateIndex *>(packet);
	if(ReqGenerateIndexVar!=NULL){
		GenerateIndex(true);
		return;
	}
	CmdFindOverlappedItem	*CmdFindOverlappedItemVar=dynamic_cast<CmdFindOverlappedItem *>(packet);
	if(CmdFindOverlappedItemVar!=NULL){
		int		AreaDot=0;
		for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
			if(p->GetArea().CheckOverlap(CmdFindOverlappedItemVar->Area)==true){
				FlexArea	K=p->GetArea();
				K &=*CmdFindOverlappedItemVar->Area;
				int	t=K.GetPatternByte();
				if(t>AreaDot){
					AreaDot=t;
					CmdFindOverlappedItemVar->Item=(NamingItem *)p;
				}
			}
		}
		return;
	}
}

void	NamingInPage::BuildItemPointer(NamingPointerStock &NStocker)
{
	int	globalPage=GetLayersBase()->GetLocalPageFromGlobal(GetPage());
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		if(p->GetSelected()==true){
			NamingPointer	*c=new NamingPointer();
			c->ItemID=p->GetID();
			c->AreaName=((NamingItem *)p)->GetItemName();
			c->GlobalPage=globalPage;
			p->GetXY(c->GlobalX1,c->GlobalY1,c->GlobalX2,c->GlobalY2);
			c->LocalX1=c->GlobalX1;
			c->LocalY1=c->GlobalY1;
			c->LocalX2=c->GlobalX2;
			c->LocalY2=c->GlobalY2;
			NStocker.AppendList(c);
		}
	}
}
void	NamingInPage::GetItemPointer(NamingPointerStock &NStocker)
{
	int	globalPage=GetLayersBase()->GetLocalPageFromGlobal(GetPage());
	for(AlgorithmItemPI	*p=GetFirstData();p!=NULL;p=p->GetNext()){
		NamingPointer	*c=new NamingPointer();
		c->ItemID=p->GetID();
		c->AreaName=((NamingItem *)p)->GetItemName();
		c->GlobalPage=globalPage;
		p->GetXY(c->GlobalX1,c->GlobalY1,c->GlobalX2,c->GlobalY2);
		c->GlobalX1+=GetDataInPage()->GetOutlineOffset()->x;
		c->GlobalY1+=GetDataInPage()->GetOutlineOffset()->y;
		c->GlobalX2+=GetDataInPage()->GetOutlineOffset()->x;
		c->GlobalY2+=GetDataInPage()->GetOutlineOffset()->y;
		c->LocalX1=c->GlobalX1;
		c->LocalY1=c->GlobalY1;
		c->LocalX2=c->GlobalX2;
		c->LocalY2=c->GlobalY2;
		NStocker.AppendList(c);
	}
}

void	NamingInPage::SetItemPointer(NamingPointerStock &NStocker)
{
	for(NamingPointer *c=NStocker.GetFirst();c!=NULL;c=c->GetNext()){
		AlgorithmItemRoot	*P=GetItemData(0,c->ItemID);
		NamingItem	*NamingItemPoint=dynamic_cast<NamingItem *>(P);
		if(NamingItemPoint!=NULL){
			NamingItemPoint->SetItemName(c->AreaName);
		}
	}
}

NamingItem	*NamingInPage::FindItem(const QString &areaname)
{
	for(AlgorithmItemPI	*c=GetFirstData();c!=NULL;c=c->GetNext()){
		NamingItem *f=(NamingItem *)c;
		if(f->GetItemName()==areaname)
			return f;
	}
	return NULL;
}

static	void PosFunc(ResultInItemRoot *Item,ResultPosList *RPos,void *Something)
{
	((NamingItem *)Something)->BindResult(Item,RPos);
}

static	void NoAreaFunc(ResultInItemRoot *Item,ResultPosList *RPos,void *Something)
{
	if(RPos->AreaNames.count()==0){
		NGImageContainerInPage	*h=(NGImageContainerInPage	*)Something;
		
		if(Item!=NULL){
			LayersBase	*Base=Item->GetLayersBase();
			if(Base!=NULL && Base->GetResultDLLBase()!=NULL && Base->GetResultDLLBase()->GetFirst()!=NULL){
				ResultDLLBaseRoot	*RBase=Item->GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
				int	x1,y1,x2,y2;
				RPos->GetXY(x1,y1,x2,y2);
				if(x1==x2 && y1==y2){
					ErrorGroup *e;
					for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
						ErrorGroupNaming	*g=(ErrorGroupNaming *)e;
						if(g->Item!=NULL)
							continue;
						int	ex1,ey1,ex2,ey2;
						e->GetXY(ex1,ey1,ex2,ey2);
						int	rx1=min(ex1,x1);
						int	ry1=min(ey1,y1);
						int	rx2=max(ex2,x1);
						int	ry2=max(ey2,y1);
						if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							g->SetRectangle(rx1,ry1,rx2,ry2);
							g->SetRepresentativeItem(Item,RPos);
							break;
						}
					}
					if(e==NULL){
						ErrorGroupNaming	*g=new ErrorGroupNaming(Item->GetLayersBase());
						g->SetRectangle(x1,y1,x2,y2);
						g->SetCause(Item->ResultItemToString());
						g->Item=NULL;
						g->SetMxy(Item->GetAlignedX(),Item->GetAlignedY());
						g->SetRepresentativeItem(Item,RPos);
						h->AddErrorGroupData(g);
					}
				}
				else{
					ErrorGroup *e;
					for(e=h->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
						ErrorGroupNaming	*g=(ErrorGroupNaming *)e;
						if(g->Item!=NULL)
							continue;
						int	ex1,ey1,ex2,ey2;
						e->GetXY(ex1,ey1,ex2,ey2);
						int	rx1=min(ex1,x1);
						int	ry1=min(ey1,y1);
						int	rx2=max(ex2,x2);
						int	ry2=max(ey2,y2);
						if((rx2-rx1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (ry2-ry1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							g->SetRectangle(rx1,ry1,rx2,ry2);
							g->SetRepresentativeItem(Item,RPos);
							break;
						}
					}
					if(e==NULL){
						if((x2-x1)<=RBase->NGImageWidth-2*RBase->NGImageBevel && (y2-y1)<=RBase->NGImageHeight-2*RBase->NGImageBevel){
							ErrorGroupNaming	*g=new ErrorGroupNaming(Item->GetLayersBase());
							g->SetRectangle(x1,y1,x2,y2);
							g->SetCause(Item->ResultItemToString());
							g->Item=NULL;
							g->SetMxy(Item->GetAlignedX(),Item->GetAlignedY());
							g->SetRepresentativeItem(Item,RPos);
							h->AddErrorGroupData(g);
						}
						else{
							RPos->NGShape.GetCenter(x1,y1);
							ErrorGroupNaming	*g=new ErrorGroupNaming(Item->GetLayersBase());
							g->SetRectangle( x1-RBase->NGImageWidth /2+RBase->NGImageBevel,y1-RBase->NGImageHeight/2+RBase->NGImageBevel
											,x2+RBase->NGImageWidth /2-RBase->NGImageBevel,y2+RBase->NGImageHeight/2-RBase->NGImageBevel);
							g->SetCause(Item->ResultItemToString());
							g->Item=NULL;
							g->SetMxy(Item->GetAlignedX(),Item->GetAlignedY());
							g->SetRepresentativeItem(Item,RPos);
							h->AddErrorGroupData(g);
						}
					}
				}
			}
		}
	}
}


bool	NamingInPage::ExecuteManageResult	(int ExeID ,ResultInspection *Res)
{
	NamingBase	*ABase=(NamingBase *)GetParentBase();

	if(ABase->BindResultByArea==true){
		NGImageContainerInPhase	*Ph=Res->GetNGImageInPhase(GetPhaseCode());
		if(Ph!=NULL){
			NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
			if(h!=NULL){
				h->ClearErrorGroupData();
				h->ClearNGImageData();
			}
			for(ResultBaseForAlgorithmRoot *rb=Res->GetResultBaseDimFirst();rb!=NULL;rb=rb->GetNext()){
				ResultBasePhase		*H=rb->GetPageDataPhase(GetPhaseCode());
				ResultInPageRoot	*rp=H->GetPageData(GetPage());
				if(rp==NULL)
					continue;
				for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
					rp->ExecuteFuncInAllItemPos(PosFunc,item);
				}
				NGImageContainerInPage	*h=Ph->GetNGImageInPage(GetPage());
				rp->ExecuteFuncInAllItemPos(NoAreaFunc,h);
			}

			for(AlgorithmItemPI	*item=GetFirstData();item!=NULL;item=item->GetNext()){
				NamingItem	*NItem=dynamic_cast<NamingItem *>(item);
				if(NItem!=NULL){
					NItem->MakeErrorGroup(h);
				}
			}
		}
	}
	else{
		if(GetPage()==0){
			GetLayersBase()->StandardManageResult(Res);
		}
	}
	return true;
}

//=============================================================================

NamingBase::NamingBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNaming			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorNaming		=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	BindResultByArea	=true;
	ResetIndexAfterEdit	=false;

	SetParam(&ColorNaming		, /**/"Color" ,/**/"ColorNaming"		,LangSolver.GetString(XNaming_LS,LID_1)/*"Color for Naming area"*/);
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,LangSolver.GetString(XNaming_LS,LID_3)/*"Color for Selected Piece"*/);
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XNaming_LS,LID_5)/*"Color for Active Piece"*/);
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XNaming_LS,LID_7)/*"Color for Transparent display level"*/);
	SetParam(&NegColorNaming	, /**/"Color" ,/**/"NegColorNaming"		,LangSolver.GetString(XNaming_LS,LID_9)/*"Color for Negative Naming area"*/);
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XNaming_LS,LID_11)/*"Color for Negative selected Naming"*/);
	SetParam(&BindResultByArea	, /**/"Setting" ,/**/"BindResultByArea"	,LangSolver.GetString(XNaming_LS,LID_13)/*"Bind result by naming area"*/);
	SetParam(&ResetIndexAfterEdit, /**/"Setting" ,/**/"ResetIndexAfterEdit"	,LangSolver.GetString(XNaming_LS,LID_14)/*"Reset Column/Row index after Edit/Load"*/);
}

AlgorithmDrawAttr	*NamingBase::CreateDrawAttr(void)
{
	return new NamingDrawAttr();
}

void	NamingBase::TransmitDirectly(GUIDirectMessage *packet)
{
	AddNamingGenerateName	*AddNamingGenerateNameVar=dynamic_cast<AddNamingGenerateName *>(packet);
	if(AddNamingGenerateNameVar!=NULL){
		NamingPointerStock	&NStocker=AddNamingGenerateNameVar->Stocker;
		for(NamingPointer *c=NStocker.GetFirst();c!=NULL;c=c->GetNext()){	
			XYData	*Offset=GetLayersBase()->GetPageData(c->GlobalPage)->GetOutlineOffset();
			c->GlobalX1 += Offset->x;
			c->GlobalY1 += Offset->y;
			c->GlobalX2 += Offset->x;
			c->GlobalY2 += Offset->y;
		}
		QString	FormatStr=AddNamingGenerateNameVar->FormatStr;

		int	MaxYLine=100000;
		NamingPointerStock	**NStockerDim=new NamingPointerStock*[MaxYLine];
		for(int YLine=0;YLine<MaxYLine;YLine++){
			NStockerDim[YLine]=NULL;
		}
		bool	Swapped;
		int YLine;
		for(YLine=0;YLine<MaxYLine;YLine++){
		//?!?P?n?d???o??E?e
			NamingPointer	*a=NStocker.GetFirst();
			if(a==NULL)
				break;
			NStockerDim[YLine]=new NamingPointerStock();
			NamingPointer *c=a->GetNext();
			NStocker.RemoveList(a);
			NStockerDim[YLine]->AppendList(a);
			while(c!=NULL){
				if(a->GetCenterY()-a->GetHeight()/5 < c->GetCenterY() && c->GetCenterY()<a->GetCenterY()+a->GetHeight()/5){
					NamingPointer	*NextA=c->GetNext();
					NStocker.RemoveList(c);
					NStockerDim[YLine]->AppendList(c);
					c=NextA;
				}
				else{
					c=c->GetNext();
				}
			}
			do{
				Swapped=false;
				for(NamingPointer *h1=NStockerDim[YLine]->GetFirst();h1!=NULL;h1=h1->GetNext()){
					NamingPointer *h2=h1->GetNext();
					if(h2==NULL)
						break;
					if(h1->GetCenterX()>h2->GetCenterX()){
						NStockerDim[YLine]->Swap(h1,h2);
						h1=h2;
						Swapped=true;
					}
				}
			}while(Swapped==true);
		}
		//?c?I?\?[?g?d?s??
		do{
			Swapped=false;
			for(int y1=0;y1<YLine-1;y1++){
				NamingPointer *c1=NStockerDim[y1  ]->GetFirst();
				NamingPointer *c2=NStockerDim[y1+1]->GetFirst();
				if(c1->GetCenterY()>c2->GetCenterY()){
					NamingPointerStock	*TmpL=NStockerDim[y1];
					NStockerDim[y1  ]=NStockerDim[y1+1];
					NStockerDim[y1+1]=TmpL;
					Swapped=true;					
				}
			}
		}while(Swapped==true);

		int	YIndex=0;
		int	MaxY=0;
		for(int y=0;y<YLine;y++){
			bool OverlappedNaming=false;
			for(NamingPointer *c=NStockerDim[y]->GetFirst();c!=NULL;c=c->GetNext()){
				if(c->LocalY2>=GetMaxLines(c->GlobalPage)){
					OverlappedNaming=true;
					break;
				}
			}
			for(NamingPointer *c=NStockerDim[y]->GetFirst();c!=NULL;c=c->GetNext()){
				c->IndexY=YIndex;
				if(MaxY<YIndex)
					MaxY=YIndex;
			}
			if(OverlappedNaming==false)
				YIndex++;
		}		
		NamingPointer **XDim=new NamingPointer *[YLine];
		int	X=0;
		for(int y=0;y<YLine;y++){
			XDim[y]=NStockerDim[y]->GetFirst();
		}
		int	MaxX=0;
		for(;;){
			NamingPointer *Left=NULL;
			for(int y=0;y<YLine;y++){
				if(XDim[y]!=NULL){
					Left=XDim[y];
					break;
				}
			}
			if(Left==NULL)
				break;
			for(int y=0;y<YLine;y++){
				if(XDim[y]==NULL)
					continue;
				if(Left->GetCenterX()>XDim[y]->GetCenterX())
					Left=XDim[y];
			}
			bool	OverlappedX=false;
			for(int y=0;y<YLine;y++){
				if(XDim[y]==NULL)
					continue;
				if(Left->GetCenterX()-Left->GetWidth()/5<XDim[y]->GetCenterX() && XDim[y]->GetCenterX()<Left->GetCenterX()+Left->GetWidth()/5){
					if(XDim[y]->LocalX2>=GetDotPerLine(Left->GlobalPage))
						OverlappedX=true;
					XDim[y]->IndexX=X;
					XDim[y]=XDim[y]->GetNext();
					if(MaxX<X)
						MaxX=X;
				}
			}
			if(OverlappedX==false)
				X++;
		}
		delete	[]XDim;

		char	FormatStrBuff[1000];
		QString2Char(FormatStr ,FormatStrBuff ,sizeof(FormatStrBuff));
		for(int y=0;y<YLine;y++){
			for(NamingPointer *c=NStockerDim[y]->GetFirst();c!=NULL;c=c->GetNext()){
				c->SetName(FormatStrBuff,MaxX,MaxY);
			}
		}
		for(int y=0;y<YLine;y++){
			NamingPointer *c;
			while((c=NStockerDim[y]->GetFirst())!=NULL){
				NStockerDim[y]->RemoveList(c);
				NStocker.AppendList(c);
			}
		}
		for(int y=0;y<YLine;y++){
			delete	NStockerDim[y];
		}
		delete	[]NStockerDim;
		return;
	}
	MakeAreaNamePacket	*MakeAreaNamePacketVar=dynamic_cast<MakeAreaNamePacket *>(packet);
	if(MakeAreaNamePacketVar!=NULL){
		char	FormatStrBuff[1000];
		QString2Char(MakeAreaNamePacketVar->FormatStr ,FormatStrBuff ,sizeof(FormatStrBuff));
		MakeAreaNamePacketVar->AreaName	=NamingPointer::SetNameOnly(FormatStrBuff,MakeAreaNamePacketVar->X ,MakeAreaNamePacketVar->Y
																	,MakeAreaNamePacketVar->CountX,MakeAreaNamePacketVar->CountY
																	,MakeAreaNamePacketVar->Column,MakeAreaNamePacketVar->Row);
		return;
	}
	ReqBuildItemPointerNamingPage	*ReqBuildItemPointerNamingPageVar=dynamic_cast<ReqBuildItemPointerNamingPage *>(packet);
	if(ReqBuildItemPointerNamingPageVar!=NULL){
		GetPageData(ReqBuildItemPointerNamingPageVar->Page)->TransmitDirectly(ReqBuildItemPointerNamingPageVar);
		return;
	}
	ReqNameFromPoint	*ReqNameFromPointVar=dynamic_cast<ReqNameFromPoint *>(packet);
	if(ReqNameFromPointVar!=NULL){
		GlobalPos2Name(ReqNameFromPointVar->XGlobalPos
					 , ReqNameFromPointVar->YGlobalPos 
					 , ReqNameFromPointVar->AreaName);
		return;
	}
	ReqMaxGroupID	*ReqMaxGroupIDVar=dynamic_cast<ReqMaxGroupID *>(packet);
	if(ReqMaxGroupIDVar!=NULL){
		ReqMaxGroupIDVar->MaxGroupID=GetMaxGroupID();
		return;
	}
	SetGroupCmd		*SetGroupCmdVar=dynamic_cast<SetGroupCmd *>(packet);
	if(SetGroupCmdVar!=NULL){
		NamingGroupList *a;
		for(a=GroupData.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GroupID==SetGroupCmdVar->GroupID){
				a->GroupName	=SetGroupCmdVar->GroupString;
				break;
			}
		}
		if(a==NULL){
			NamingGroupList	*g=new NamingGroupList();
			g->GroupID	=SetGroupCmdVar->GroupID;
			g->GroupName=SetGroupCmdVar->GroupString;
			GroupData.AppendList(g);
		}
		return;
	}
	ClearGroupCmd	*ClearGroupCmdVar=dynamic_cast<ClearGroupCmd *>(packet);
	if(ClearGroupCmdVar!=NULL){
		for(NamingGroupList *a=GroupData.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GroupID==ClearGroupCmdVar->GroupID){
				GroupData.RemoveList(a);
				break;
			}
		}
		return;
	}
	ReqGroupData	*ReqGroupDataVar=dynamic_cast<ReqGroupData *>(packet);
	if(ReqGroupDataVar!=NULL){
		ReqGroupDataVar->GroupPointer=&GroupData;
		return;
	}
}

ExeResult	NamingBase::ExecuteInitialAfterEdit	(int ExeID 
												,ResultBaseForAlgorithmRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	if(BindResultByArea==true){
		ChangeAlgorithmType(AlgorithmBit_TypeNoProcessing | AlgorithmBit_TypeManageResult | AlgorithmBit_TypePostProcessing);
	}
	else{
		ChangeAlgorithmType(AlgorithmBit_TypeNoProcessing | AlgorithmBit_TypePostProcessing);
	}
	return AlgorithmBase::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
}


bool	NamingBase::SaveOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::SaveOnlyBase(f)==false)
		return false;
	return true;
}
bool	NamingBase::LoadOnlyBase(QIODevice *f)
{
	if(AlgorithmBase::LoadOnlyBase(f)==false)
		return false;
	return true;
}

int		NamingBase::GetMaxGroupID(void)
{
	int	MaxGroupID=0;
	for(NamingGroupList *a=GroupData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GroupID>MaxGroupID){
			MaxGroupID=a->GroupID;
		}
	}
	return MaxGroupID;
}

ExeResult	NamingBase::ExecuteManageResult		(int ExeID ,ResultInspection *Res)
{
	if(BindResultByArea==true){
		if(GetParamGlobal()->GetMaxScanStrategy()<=1){
			for(int page=0;page<GetPageNumb();page++){
				ExecuteManageResultOnPage(ExeID ,Res  ,page);
			}
		}
		else{
			IntList PageList;
			GetParamGlobal()->GetStrategyPage(GetLayersBase()->GetCurrentStrategicNumberForCalc(),PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				ExecuteManageResultOnPage(ExeID ,Res  ,s->GetValue());
			}
		}
	}
	return _ER_true;
}
bool	NamingBase::ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage)
{
	if(BindResultByArea==true){

		int	ImageW	=Res->GetResultDLLBase()->NGImageWidth;
		int	ImageH	=Res->GetResultDLLBase()->NGImageHeight;
		//int	Bevel	=Res->GetResultDLLBase()->NGImageBevel;
		//int	quality	=Res->GetResultDLLBase()->NGImageQuality;
		if(GetParamGlobal()->ModePhaseExecuteManageResult==-2){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				bool	b=ExecuteManageResultOnPagePhase(ExeID ,Res 
													,phase,localPage
													,ImageW,ImageH);
				if(b==false){
					return false;
				}
			}
		}
		else
		if(GetParamGlobal()->ModePhaseExecuteManageResult==-1){
			int	phase=GetLayersBase()->GetCurrentPhase();
			bool	b=ExecuteManageResultOnPagePhase(ExeID ,Res 
													,phase,localPage
													,ImageW,ImageH);
			if(b==false){
				return false;
			}
		}
		else if(0<=GetParamGlobal()->ModePhaseExecuteManageResult && GetParamGlobal()->ModePhaseExecuteManageResult<GetPhaseNumb()){
			int	phase=GetParamGlobal()->ModePhaseExecuteManageResult;
			bool	b=ExecuteManageResultOnPagePhase(ExeID ,Res 
													,phase,localPage
													,ImageW,ImageH);
			if(b==false){
				return false;
			}
		}
	}
	return true;
}

bool	NamingBase::ExecuteManageResultOnPagePhase(int ExeID ,ResultInspection *Res 
													,int phase,int localPage
													,int ImageW,int	ImageH)
{
	AlgorithmInPageInOnePhase	*Ah=GetPageDataPhase(phase);
	((NamingInPage *)(Ah->GetPageData(localPage)))->ExecuteManageResult(ExeID ,Res);
	LayersBase	*LBase=GetLayersBase();
	NGImageContainerInPhase	*Ph=Res->GetNGImageInPhase(phase);
	if(Ph!=NULL){
		NGImageContainerInPage	*s=Ph->GetNGImageInPage(localPage);
		if(s!=NULL){
			s->ClearNGImageData();
			int32	N=0;
			for(ErrorGroup *e=s->GetErrorGroupDataFirst();e!=NULL && N<GetParamGlobal()->MaxNGImageNumbPerPage;e=e->GetNext()){
				if(e->IsSentCompressor()==true)
					continue;
				e->SetSentCompressor(true);
				int	Cx,Cy;
				e->GetCenter(Cx,Cy);
				NGImage	*d=s->GetNGImageFromStockker();
				if(d==NULL){
					d=new NGImage(LBase);
				}

				int	dx1,dy1,dx2,dy2;
				dx1=Cx-ImageW/2;
				dy1=Cy-ImageH/2;
				dx2=dx1+ImageW;
				dy2=dy1+ImageH;
				if(dx1<0){
					dx1=0;
					dx2=dx1+ImageW;
				}
				if(dy1<0){
					dy1=0;
					dy2=dy1+ImageH;
				}
				if(dx2>=GetDotPerLine(localPage)){
					dx2=GetDotPerLine(localPage)-1;
					dx1=dx2-ImageW;
				}
				if(dy2>=GetMaxLines(localPage)){
					dy2=GetMaxLines(localPage)-1;
					dy1=dy2-ImageH;
				}
				d->SetRectangle(dx1,dy1,dx2,dy2);
				d->SetNumber(N);
				d->SetGlobalPage(LBase->GetGlobalPageFromLocal(localPage));
				//d->CopyImageFromTarget(LBase->GetPhaseData()[phase]->GetPageData(localPage));
				s->AddNGImageData(d);			
				N++;
			}
			//_heapchk();
			for(NGImage	*d=s->GetNGImageDataFirst();d!=NULL;d=d->GetNext()){
				d->AllocateBuffer(GetLayerNumb(localPage));
			}
				
			if(N!=0){
				NGImage	**dDim=(NGImage**)alloca(N*sizeof(NGImage**));
				int	row = 0;
				for (NGImage* d = s->GetNGImageDataFirst(); d != NULL; d = d->GetNext(),row++) {
					dDim[row] = d;
				}
				#pragma omp parallel   num_threads(6)                          
				{
					#pragma omp for
					for (int i = 0; i < N; i++) {
						dDim[i]->CopyImageFromTarget(LBase->GetPhaseData()[phase]->GetPageData(localPage));
					}
				}
				DataInPage	*P=LBase->GetPageDataPhase(phase)->GetPageData(localPage);
				P->SetCompressedContainer(s);
				/*
				NGImage	*NGImageDim[1000];
				NGImage	**NGImageDimPointer=NGImageDim;
				if(N>sizeof(NGImageDim)/sizeof(NGImageDim[0])){
					NGImageDimPointer=new NGImage*[N];
				}
				NGImage	*c=s->GetNGImageDataFirst();
				for(int i=0;i<N && c!=NULL;i++,c=c->GetNext()){
					NGImageDimPointer[i]=c;
				}
	
				DataInPage	*P=LBase->GetPageData(localPage);
				#pragma omp parallel   num_threads(6)                          
				{                                                
					#pragma omp for
					for(int i=0;i<N;i++){
						NGImageDimPointer[i]->CompressImage(P,quality);
					}
				}
	
				if(NGImageDimPointer!=NGImageDim){
					delete	[]NGImageDimPointer;
				}
				*/
			}
			else{
				s->SetCompressedFlag(true);
			}

		}
	}
	
	return true;
}


bool	NamingBase::Name2GloalPos(QString Name ,int &XGlobalPos, int &YGlobalPos)
{
	for(int page=0;page<GetPageNumb();page++){
		NamingItem	*f=((NamingInPage *)GetPageData(page))->FindItem(Name);
		if(f!=NULL){
			int	cx,cy;
			f->GetCenter(cx,cy);
			
			XGlobalPos=cx+GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
			YGlobalPos=cy+GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
			return true;
		}
	}
	return false;
}
bool	NamingBase::Name2LocalPos(QString Name ,int &Page ,int &XLocalPos, int &YLocalPos)
{
	for(int page=0;page<GetPageNumb();page++){
		NamingItem	*f=((NamingInPage *)GetPageData(page))->FindItem(Name);
		if(f!=NULL){
			int	cx,cy;
			f->GetCenter(cx,cy);
			
			XLocalPos=cx;
			YLocalPos=cy;
			Page	=page;
			return true;
		}
	}
	return false;
}
bool	NamingBase::LocalPos2Name(int Page ,int XLocalPos, int YLocalPos ,QString &Name)
{
	AlgorithmItemPI	*f=((NamingInPage *)GetPageData(Page))->GetItem(XLocalPos,YLocalPos);
	if(f!=NULL){
		NamingItem	*N=(NamingItem *)f;
		Name=N->GetItemName();
		return true;
	}
	return false;
}
bool	NamingBase::GlobalPos2Name(int XGlobalPos, int YGlobalPos ,QString &Name)
{
	IntList PageList;
	GetLayersBase()->GetGlobalPage(XGlobalPos, YGlobalPos ,XGlobalPos, YGlobalPos ,PageList);
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	page=c->GetValue();
		int	XLocalPos=XGlobalPos-GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int	YLocalPos=YGlobalPos-GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		if(LocalPos2Name(page ,XLocalPos, YLocalPos ,Name)==true)
			return true;
	}
	return false;
}

bool	NamingBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		delete	data;
		return true;
	}
	else if(Command==NamingReqNameSendCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*NamingBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==NamingReqNameReqCommand){
		return new NamingNameReq();
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*pSend=new NamingNameSend();
		if(reqData!=NULL){
			NamingNameReq	*req=(NamingNameReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
	return NULL;
}
bool	NamingBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return p->Load(f);
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	NamingBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return p->Save(f);
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
	return false;
}
bool	NamingBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==NamingReqNameReqCommand){
		NamingNameReq	*p=(NamingNameReq *)data;
		return true;
	}
	else if(Command==NamingReqNameSendCommand){
		NamingNameSend	*p=(NamingNameSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
	return false;
}
