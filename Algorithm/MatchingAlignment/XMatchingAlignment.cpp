/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\MatchingAlignment\XMatchingAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XMatchingAlignmentResource.h"
#include "XMatchingAlignment.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XCrossObj.h"

MatchingAlignmentThreshold::MatchingAlignmentThreshold(MatchingAlignmentItem *parent)
:AlgorithmThreshold(parent)
{
	MatchingRate=0.6;
}

void	MatchingAlignmentThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const MatchingAlignmentThreshold *s=(const MatchingAlignmentThreshold *)&src;
    MatchingRate=s->MatchingRate;
}
bool	MatchingAlignmentThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const MatchingAlignmentThreshold *s=(const MatchingAlignmentThreshold *)&src;
	if(MatchingRate!=s->MatchingRate)	return false;
	return true;
}
bool	MatchingAlignmentThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,MatchingRate)==false)
		return(false);
	if(::Save(file,SearchDot)==false)
		return(false);
	return(true);
}
bool	MatchingAlignmentThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,MatchingRate)==false)
		return(false);
	if(::Load(file,SearchDot)==false)
		return(false);
	return(true);
}

MatchingAlignmentItem::MatchingAlignmentItem(void)
{
	for(int i=0;i<sizeof(TopAreas)/sizeof(TopAreas[0]);i++){
		TopAreas[i]=NULL;
	}
	AreasList=NULL;
}

MatchingAlignmentItem::~MatchingAlignmentItem(void)
{
	if(AreasList!=NULL){
		delete	[]AreasList;
		AreasList=NULL;
	}
}

AlgorithmItemPLI	&MatchingAlignmentItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    MatchingAlignmentItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	if(MatchingAreas.Save(f)==false){
		return false;
	}
	return true;
}
bool    MatchingAlignmentItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false){
			return false;
	}
	if(MatchingAreas.Load(f)==false){
		return false;
	}
	MakeInnerData();

	return true;
}

void	MatchingAlignmentItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	MatchingAlignmentBase	*ABase=(MatchingAlignmentBase	*)GetParentBase();
	MatchingAlignmentDrawAttr	*a=dynamic_cast<MatchingAlignmentDrawAttr *>(Attr);
	if(a!=NULL && ABase!=NULL){
		if(a->ModeSpecified==false){
			AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,a);
		}
		else if(a->ModeSpecified==true){
			if(GetSelected()==true){
				for(FlexAreaImageList *k=MatchingAreas.GetFirst();k!=NULL;k=k->GetNext()){
					k->DrawAlpha(0,0 ,&pnt ,Attr->SelectedColor.rgba()
								,ZoomRate ,movx ,movy);
				}
			}
			else if(GetActive()==true){
				for(FlexAreaImageList *k=MatchingAreas.GetFirst();k!=NULL;k=k->GetNext()){
					k->DrawAlpha(0,0 ,&pnt ,Attr->ActiveColor.rgba()
								,ZoomRate ,movx ,movy);
				}
			}
			else{
				for(FlexAreaImageList *k=MatchingAreas.GetFirst();k!=NULL;k=k->GetNext()){
					k->DrawAlpha(0,0 ,&pnt ,Attr->NormalColor.rgba()
								,ZoomRate ,movx ,movy);
				}
			}
		}
	}
	else{
		AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

class	VarAreaList : public NPList<VarAreaList>
{
public:
	FlexArea	Area;
	double		Var;
	int			Xn,Yn;
	bool		Enabled;
};

int	VTableFunc(const void *a ,const void *b)
{
	VarAreaList	**A=(VarAreaList **)a;
	VarAreaList	**B=(VarAreaList **)b;
	if((*A)->Var>(*B)->Var)
		return -1;
	if((*A)->Var<(*B)->Var)
		return 1;
	return 0;
}


void	MatchingAlignmentItem::CreateMatchingAreas(double CoverRate, double PickUpVar, int BlockSize)
{
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	int	B=BlockSize/2;
	int	WNumb2=(W+B-1)/B;
	int	HNumb2=(H+B-1)/B;
	int	BW=(W+WNumb2-1)/WNumb2;
	int	BH=(H+HNumb2-1)/HNumb2;

	int	WBlock=BW*2;
	int	WBlockNumb=WNumb2-1;
	int	HBlock=BH*2;
	int	HBlockNumb=HNumb2-1;

	NPListPack<VarAreaList>	VarAreas;
	for(int y=0;y<HBlockNumb;y++){
		for(int x=0;x<WBlockNumb;x++){
			int	x1=x*BW+GetArea().GetMinX();
			int	x2=x1+WBlock;
			int	y1=y*BH+GetArea().GetMinY();
			int	y2=y1+HBlock;
			FlexArea	A;
			A.SetRectangle(x1,y1,x2,y2);
			A&=GetArea();
			if(A.GetPatternByte()>2){
				VarAreaList	*a=new VarAreaList();
				a->Area=A;
				a->Xn=x;
				a->Yn=y;
				VarAreas.AppendList(a);
			}
		}
	}

BindNext:;
	for(VarAreaList *a=VarAreas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Area.GetPatternByte()<25){
			for(VarAreaList *b=VarAreas.GetFirst();b!=NULL;b=b->GetNext()){
				if(b==a){
					continue;
				}
				if(abs(b->Xn-a->Xn)<=1 && abs(b->Yn-a->Yn)<=1){
					b->Area+=a->Area;
					VarAreas.RemoveList(a);
					delete	a;
					goto	BindNext;
				}
			}
		}
	}

	VarAreaList	**VTable=new VarAreaList*[VarAreas.GetNumber()];
	int	N=0;
	for(VarAreaList *a=VarAreas.GetFirst();a!=NULL;a=a->GetNext(),N++){
		double Avr;
		a->Area.CalcAvrVar(0,0,GetMasterBuff(),Avr ,a->Var,1.0,1.0);
		VTable[N]=a;
		a->Enabled=false;
	}
	QSort(VTable,N,sizeof(VTable[0]),VTableFunc);

	int	AdCount=N*CoverRate;
	int	Index;
	for(Index=0;Index<AdCount && Index<N;Index++){
		VTable[Index]->Enabled=true;
	}
	for(;Index<N;Index++){
		if(VTable[Index]->Var>=PickUpVar){
			VTable[Index]->Enabled=true;
		}
	}
	delete	[]VTable;

	MatchingAreas.RemoveAll();
	for(VarAreaList *a=VarAreas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Enabled==true){
			FlexAreaImageListCoeff	*k=new FlexAreaImageListCoeff();
			k->Set(a->Area,GetMasterBuff());
			MatchingAreas.AppendList(k);
		}
	}
	MakeInnerData();
}

void	MatchingAlignmentItem::MakeInnerData(void)
{
	FlexAreaImageListCoeff	*Ka=NULL;
	FlexAreaImageListCoeff	*Kb=NULL;
	FlexAreaImageListCoeff	*Kc=NULL;
	double	MaxA=0;

	for(FlexAreaImageListCoeff	*a=(FlexAreaImageListCoeff *)MatchingAreas.GetFirst();a!=NULL;a=(FlexAreaImageListCoeff *)a->GetNext()){
		double	Cx1,Cy1;
		a->GetCenter(Cx1,Cy1);
		for(FlexAreaImageListCoeff	*b=(FlexAreaImageListCoeff *)a->GetNext();b!=NULL;b=(FlexAreaImageListCoeff *)b->GetNext()){
			double	Cx2,Cy2;
			b->GetCenter(Cx2,Cy2);
			for(FlexAreaImageListCoeff	*c=(FlexAreaImageListCoeff *)b->GetNext();c!=NULL;c=(FlexAreaImageListCoeff *)c->GetNext()){
				double	Cx3,Cy3;
				c->GetCenter(Cx3,Cy3);
				double	A=GetAreaDot(Cx1,Cy1,Cx2,Cy2,Cx3,Cy3);
				if(A>MaxA){
					MaxA=A;
					Ka=a;
					Kb=b;
					Kc=c;
				}
			}
		}
	}
	bool	ReTry;
	do{
		ReTry=false;
		if(Ka!=NULL && Kb!=NULL && Ka->GetPatternByte()<Kb->GetPatternByte()){
			FlexAreaImageListCoeff	*tmp=Ka;
			Ka=Kb;
			Kb=tmp;
			ReTry=true;
		}
		if(Kb!=NULL && Kc!=NULL && Kb->GetPatternByte()<Kc->GetPatternByte()){
			FlexAreaImageListCoeff	*tmp=Kb;
			Kb=Kc;
			Kc=tmp;
			ReTry=true;
		}
	}while(ReTry==true);

	TopAreas[0]=Ka;
	TopAreas[1]=Kb;
	TopAreas[2]=Kc;

	if(AreasList!=NULL){
		delete	[]AreasList;
	}
	AreasList=new FlexAreaImageListCoeff*[MatchingAreas.GetNumber()];
	int	Hc=0;
	for(FlexAreaImageListCoeff	*a=(FlexAreaImageListCoeff *)MatchingAreas.GetFirst();a!=NULL;a=(FlexAreaImageListCoeff *)a->GetNext(),Hc++){
		AreasList[Hc]=a;
	}
	AreasListCount=Hc;
}


bool	MatchingAlignmentItem::ExecuteMatch	(ImageBuffer &TargetImage,int cx, int cy ,double &Result)
{
	const MatchingAlignmentThreshold	*RThr=GetThresholdR();
	if(TopAreas[0]!=NULL && TopAreas[1]!=NULL && TopAreas[2]!=NULL){
		Result=GetCoefImage(TopAreas,3,RThr->SearchDot,TargetImage,cx,cy);
		if(Result<RThr->MatchingRate){
			return false;
		}
	}

	Result=GetCoefImage(AreasList,AreasListCount,RThr->SearchDot,TargetImage,cx,cy);
	if(Result<RThr->MatchingRate){
		return false;
	}
	return true;
}

double	MatchingAlignmentItem::GetCoefImage(FlexAreaImageListCoeff **AreaList,int AreaCount
											,int SearchDot,ImageBuffer &TargetImage
											,int cx,int cy)
{
	double	Sx	=0;
	double	Sxx	=0;
	double	Sy	=0;
	double	Syy	=0;
	double	Sxy	=0;
	int		SCount=0;

	for(int i=0;i<AreaCount;i++){
		Sx +=AreaList[i]->GetSumA();
		Sxx+=AreaList[i]->GetSumA2();
		SCount+=AreaList[i]->GetDataLen();
		//int	mcx=AreaList[i]->GetMinX();
		//int	mcy=AreaList[i]->GetMinY();
		int	KLen=AreaList[i]->GetFLineLen();

		double	MaxM=0;
		double	MaxSxy=0;
		double	MaxSy=0;
		double	MaxSyy=0;

		double	jMaxM[100];
		double	jMaxSxy[100];
		double	jMaxSy[100];
		double	jMaxSyy[100];
		int		iSCount=AreaList[i]->GetDataLen();
		double	iAx=(double)(AreaList[i]->GetSumA())/(double)(iSCount);

		int	N=SearchDot*2+1;
		for(int j=0;j<N;j++){
			jMaxM[j]	=0;
			jMaxSxy[j]	=0;
			jMaxSy[j]	=0;
			jMaxSyy[j]	=0;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int j=0;j<N;j++){
				int	dy=j-SearchDot;
				for(int dx=-SearchDot;dx<=SearchDot;dx++){
					BYTE	*d=AreaList[i]->GetData();
					double	iSxy	=0;
					double	iSy		=0;
					double	iSyy	=0;
					for(int k=0;k<KLen;k++){
						int	y =AreaList[i]->GetFLineAbsY(k)  +cy+dy;
						int	x1=AreaList[i]->GetFLineLeftX(k) +cx+dx;
						int	x2=AreaList[i]->GetFLineRightX(k)+cx+dx;
						if(y<0 || TargetImage.GetHeight()<=y){
							d+=x2-x1;
						}
						else{
							BYTE	*s=TargetImage.GetY(y);
							int	hSy=0;
							int	hSyy=0;
							int	hSxy=0;
							for(int x=x1;x<x2;x++,d++){
								if(0<=x && x<TargetImage.GetWidth()){
									hSy+=s[x];
									hSyy+=((int)s[x])*((int)s[x]);
									hSxy+=((int)s[x])*(*d);
								}
							}
							iSy	+=hSy;
							iSyy+=hSyy;
							iSxy+=hSxy;
						}
					}
					double	iAy	=iSy/iSCount;
					double	Di=(AreaList[i]->GetSumA2()-iSCount*iAx*iAx)*(iSyy-iSCount*iAy*iAy);
					Di=sqrt(Di);
					double	m=(iSxy-iSCount*iAx*iAy)/Di;
					if(m>jMaxM[j]){
						jMaxM[j]	=m;
						jMaxSxy[j]	=iSxy;
						jMaxSy[j]	=iSy;
						jMaxSyy[j]	=iSyy;
					}
				}
			}
		}
		for(int j=0;j<N;j++){
			if(MaxM<jMaxM[j]){
				MaxM=jMaxM[j];
			}
			if(MaxSxy<jMaxSxy[j]){
				MaxSxy=jMaxSxy[j];
			}
			if(MaxSy<jMaxSy[j]){
				MaxSy=jMaxSy[j];
			}
			if(MaxSyy<jMaxSyy[j]){
				MaxSyy=jMaxSyy[j];
			}
		}

		Sxy	+=MaxSxy;
		Sy	+=MaxSy;
		Syy	+=MaxSyy;
	}
	if(SCount==0){
		return 0;
	}
	double	Ax	=Sx/SCount;
	double	Ay	=Sy/SCount;

	double	D=(Sxx-SCount*Ax*Ax)*(Syy-SCount*Ay*Ay);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	return (Sxy-SCount*Ax*Ay)/D;
}


//===========================================

void	MatchingAlignmentInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CreateSpecifiedPacket	*CreateSpecifiedPacketVar=dynamic_cast<CreateSpecifiedPacket *>(packet);
	if(CreateSpecifiedPacketVar!=NULL){
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			if(a->GetSelected()==true){
				MatchingAlignmentItem	*Item=dynamic_cast<MatchingAlignmentItem *>(a);
				Item->CreateMatchingAreas(CreateSpecifiedPacketVar->CoverRate
										, CreateSpecifiedPacketVar->PickUpVar
										, CreateSpecifiedPacketVar->BlockSize);
			}
		}
	}
}

bool	MatchingAlignmentInLayer::ExecuteMatch	(ImageBuffer &TargetImage,int cx, int cy ,double &Result)
{
	Result=1.0;
	for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
		MatchingAlignmentItem	*Item=dynamic_cast<MatchingAlignmentItem *>(a);
		double	iResult;
		if(Item->ExecuteMatch(TargetImage,cx, cy ,iResult)==false){
			return false;
		}
		Result *=iResult;
	}
	return true;
}


//===========================================

void	MatchingAlignmentInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddMatchingAlignmentAreaPacket	*AddMArea=dynamic_cast<AddMatchingAlignmentAreaPacket *>(packet);
	if(AddMArea!=NULL){
		for(IntClass *d=AddMArea->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			MatchingAlignmentInLayer	*L=(MatchingAlignmentInLayer *)GetLayerData(d->GetValue());
			MatchingAlignmentItem	*MData=(MatchingAlignmentItem	*)L->CreateItem(0);
			MData->GetThresholdW()->MatchingRate	=AddMArea->MatchingRate;
			MData->GetThresholdW()->SearchDot		=AddMArea->SearchDot;
			MData->SetArea(AddMArea->Area);
			MData->SetManualCreated(true);
			L->AppendItem(MData);
		}
		return;
	}
	CreateSpecifiedPacket	*CreateSpecifiedPacketVar=dynamic_cast<CreateSpecifiedPacket *>(packet);
	if(CreateSpecifiedPacketVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
	}
}

ExeResult	MatchingAlignmentInPage::ExecuteMatch	(ImagePointerContainer &TargetImages,int cx, int cy ,double &Result)
{
	Result=1.0;
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		ImagePointerList	*p=TargetImages.GetItem(Layer);
		double iResult;
		if(((MatchingAlignmentInLayer *)GetLayerData(Layer))->ExecuteMatch	(*p->GetImage(),cx, cy ,iResult)==true){
			Result*=iResult;
		}
		else{
			Result=0;
			return _ER_true;
		}
	}
	return _ER_true;
}


//===========================================
MatchingAlignmentBase::MatchingAlignmentBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNormal		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;

	SetParam(&ColorNormal		, /**/"Color" ,/**/"ColorSelected"		,"Color for Normal alignment");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"		,"Color for Selected alignment");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"		,"Color for Active alignment");
	SetParam(&NegColorMask		, /**/"Color" ,/**/"NegColorMask"		,"Color for Negative alignment");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"	,"Color for Selected Negative alignment");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
}

AlgorithmDrawAttr	*MatchingAlignmentBase::CreateDrawAttr(void)
{
	return new MatchingAlignmentDrawAttr();
}

