/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XColorDifferenceItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XColorDifferenceResource.h"
#include "XColorDifference.h"
#include "XColorDifferenceLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "XLearningRegist.h"
#include "swap.h"

//=====================================================================================

ColorDifferenceThreshold::ColorDifferenceThreshold(ColorDifferenceItem *parent)
:AlgorithmThreshold(parent)
{
	AdoptedRate	=75;
	JudgeMethod	=0;
	THDeltaE	=10;
	dH			=5;
	dSL			=10;
	dSH			=10;
	dVL			=20;
	dVH			=10;
	AdaptAlignment	=true;
}
ColorDifferenceThreshold::ColorDifferenceThreshold(ColorDifferenceRegulation *parent)
:AlgorithmThreshold(parent)
{
	AdoptedRate	=75;
	JudgeMethod	=0;
	THDeltaE	=10;
	dH			=5;
	dSL			=10;
	dSH			=10;
	dVL			=20;
	dVH			=10;
	AdaptAlignment	=true;
}
bool	ColorDifferenceThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ColorDifferenceThreshold	*s=(const ColorDifferenceThreshold *)&src;

	if(AdoptedRate	==s->AdoptedRate
	&& JudgeMethod	==s->JudgeMethod
	&& THDeltaE		==s->THDeltaE
	&& dH			==s->dH
	&& dSL			==s->dSL
	&& dSH			==s->dSH
	&& dVL			==s->dVL
	&& dVH			==s->dVH
	&& AdaptAlignment==s->AdaptAlignment)
		return true;

	return false;
}
void	ColorDifferenceThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const	ColorDifferenceThreshold	*s=(const ColorDifferenceThreshold *)&src;
	AdoptedRate	=s->AdoptedRate;
	JudgeMethod	=s->JudgeMethod;
	THDeltaE	=s->THDeltaE;
	dH			=s->dH		;
	dSL			=s->dSL		;
	dSH			=s->dSH		;
	dVL			=s->dVL		;
	dVH			=s->dVH		;
	AdaptAlignment	=s->AdaptAlignment;
}
bool	ColorDifferenceThreshold::Save(QIODevice *file)
{
	WORD	Ver=3;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,AdoptedRate)==false)
		return(false);
	if(::Save(file,JudgeMethod)==false)
		return(false);
	if(::Save(file,THDeltaE)==false)
		return(false);
	if(::Save(file,dH)==false)
		return(false);
	if(::Save(file,dSL)==false)
		return(false);
	if(::Save(file,dSH)==false)
		return(false);
	if(::Save(file,dVL)==false)
		return(false);
	if(::Save(file,dVH)==false)
		return(false);
	if(::Save(file,AdaptAlignment)==false)
		return(false);
	return(true);
}
bool	ColorDifferenceThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,AdoptedRate)==false)
		return(false);
	if(Ver>=2){
		if(::Load(file,JudgeMethod)==false)
			return(false);
	}
	if(::Load(file,THDeltaE)==false)
		return(false);
	if(Ver>=2){
		if(::Load(file,dH)==false)
			return(false);
		if(::Load(file,dSL)==false)
			return(false);
		if(::Load(file,dSH)==false)
			return(false);
		if(::Load(file,dVL)==false)
			return(false);
		if(::Load(file,dVH)==false)
			return(false);
	}
	if(Ver>=3){
		if(::Load(file,AdaptAlignment)==false)
			return(false);
	}
	return(true);
}
void	ColorDifferenceThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ColorDifferenceLibrary	*s=(ColorDifferenceLibrary *)src;
	AdoptedRate	=s->AdoptedRate;
	JudgeMethod	=s->JudgeMethod;
	THDeltaE	=s->THDeltaE;
	dH			=s->dH		;
	dSL			=s->dSL		;
	dSH			=s->dSH		;
	dVL			=s->dVL		;
	dVH			=s->dVH		;
	AdaptAlignment	=s->AdaptAlignment;
}
void	ColorDifferenceThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	ColorDifferenceLibrary	*d=(ColorDifferenceLibrary *)Dest;
	d->AdoptedRate	=AdoptedRate;
	d->JudgeMethod	=JudgeMethod;
	d->THDeltaE		=THDeltaE	;
	d->dH			=dH		;
	d->dSL			=dSL		;
	d->dSH			=dSH		;
	d->dVL			=dVL		;
	d->dVH			=dVH		;
	d->AdaptAlignment	=AdaptAlignment;
}

//-----------------------------------------------------------------
ColorDifferenceItem::ColorDifferenceItem(void)
{
	AVector	=NULL;
	OutputConstantly	=false;
	StatisticData.HAvr=0;
	StatisticData.SAvr=0;
	StatisticData.VAvr=0;
	StatisticData.Hvl	=0;
	StatisticData.Hvh	=0;
	StatisticData.Svl	=0;
	StatisticData.Svh	=0;
	StatisticData.Vvl	=0;
	StatisticData.Vvh	=0;
	Reference1			=NULL;
	Reference2			=NULL;
}
AlgorithmItemPI	&ColorDifferenceItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);

	const	ColorDifferenceItem	*Item=dynamic_cast<const ColorDifferenceItem *>(&src);
	if(Item!=NULL){
		StatisticData	=Item->StatisticData;
		OutputConstantly=Item->OutputConstantly;
		OKBrightness	=Item->OKBrightness	;
		NGBrightness	=Item->NGBrightness	;
		FlowBrightness	=Item->FlowBrightness;
		MasterColor		=Item->MasterColor	;
		TargetColor		=Item->TargetColor	;
		Reference1		=Item->Reference1	;
		Reference2		=Item->Reference2	;
		ReferedCurrentColor	=Item->ReferedCurrentColor;
		ResultDeltaE		=Item->ResultDeltaE;
		MasterCx			=Item->MasterCx;
		MasterCy			=Item->MasterCy;
	}

	return *this;
}

void	ColorDifferenceItem::CopyThreshold(ColorDifferenceItem &src)
{
	OKBrightness	=src.OKBrightness	;
	NGBrightness	=src.NGBrightness	;
	MasterColor		=src.MasterColor	;
	TargetColor		=src.TargetColor	;
	FlowBrightness	=src.FlowBrightness	;
	MasterCx		=src.MasterCx;
	MasterCy		=src.MasterCy;
}

bool    ColorDifferenceItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	QString	tItemName=GetItemName();
	if(::Save(f,tItemName)==false)
		return false;
	if(OKBrightness.Save(f)==false)
		return false;
	if(NGBrightness.Save(f)==false)
		return false;

	if(MasterColor.Save(f)==false)
		return false;
	if(FlowBrightness.Save(f)==false)
		return false;
	if(::Save(f,OutputConstantly)==false)
		return false;
	if(f->write((const char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
		return(false);

	return true;
}
bool    ColorDifferenceItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	
	QString	tItemName;
	if(::Load(f,tItemName)==false)
		return false;
	SetItemName(tItemName);

	if(OKBrightness.Load(f)==false)
		return false;
	if(NGBrightness.Load(f)==false)
		return false;

	if(MasterColor.Load(f)==false)
		return false;
	if(Ver>=3){
		if(FlowBrightness.Load(f)==false)
			return false;
		CalcFlowCenterColor();

		if(::Load(f,OutputConstantly)==false)
			return false;
		if(f->read((char *)&StatisticData,sizeof(StatisticData))!=sizeof(StatisticData))
			return(false);
	}
	return true;
}

void	ColorDifferenceItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SetVisible(true);
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr,qRgba(255,160,0,80));

	int	kx=(MasterCx+movx)*ZoomRate;
	int	ky=(MasterCy+movy)*ZoomRate;
	if(0<=kx && (kx+120)<pnt.width() && 0<=ky && (ky+40)<pnt.height()){
		QRect	rect(0,0,pnt.width(),pnt.height());
		QPainter	PData(&pnt);	
		ColorDifferenceBase	*ABase=tGetParentBase();
		PData.setPen(ABase->TextColor);
		PData.setBrush(ABase->TextColor);
		PData.drawText(kx,ky,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Pg=")+QString::number(GetPage()) 
						+QString(/**/",ID=")+QString::number(GetID()) 
						,&rect);
	}
}

void	ColorDifferenceItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		GetCenter(MasterCx,MasterCy);
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			ColorDifferenceBase	*ABase=tGetParentBase();
			int	kx=(MasterCx+MovX)*ZoomRate;
			int	ky=(MasterCy+MovY)*ZoomRate;
			if(Res->IsOk()==false && ZoomRate>1.0){
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					PData.setPen(ABase->TextColor);
					PData.setBrush(ABase->TextColor);
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Pg=")+QString::number(GetPage())
						+QString(/**/",ID=")+QString::number(GetID())
						,&rect);
				}
			}
			PData.setPen(ABase->TextColor);
			PData.setBrush(ABase->TextColor);
			const	ColorDifferenceThreshold	*RThr=GetThresholdR();
			if(RThr->JudgeMethod==0){
			}
			else if(RThr->JudgeMethod==1){
				PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"deltaE=")
						+QString::number(ResultDeltaE,'f',1));
			}
			else if(RThr->JudgeMethod==2){
				PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"dH,dS,dV=")
						+QString::number(ResultDiffR,'f',1)+QString(/**/",")
						+QString::number(ResultDiffG,'f',1)+QString(/**/",")
						+QString::number(ResultDiffB,'f',1));
			}
		}
	}
}

UFloatShort	MakeAverage(int BTable[],int AbandonDot)
{
	int	L;
	int	n=0;
	for(L=0;L<256;L++){
		if((n+BTable[L])>AbandonDot){
			break;
		}
		n+=+BTable[L];
	}
	int	H;
	n=0;
	for(H=255;L>=0;H--){
		if((n+BTable[H])>AbandonDot){
			break;
		}
		n+=+BTable[H];
	}
	double	A=0.0;
	int		NCount=0;
	for(int i=L;i<=H;i++){
		A+=BTable[i]*i;
		NCount+=BTable[i];
	}
	if(NCount>0){
		return UFloatShort((double)(A/NCount));
	}
	else{
		return UFloatShort(0.0);
	}
}

void	MakeAverageColor(FlexArea &Area ,ImageBuffer *ImageList[] ,int mx ,int my 
						,int DotPerLine ,int MaxLines 
						,double AdoptedRate
						,PreciseColor &Ret)
{
	int	N=Area.GetFLineLen();
	int	BTableR[256];
	int	BTableG[256];
	int	BTableB[256];
	memset(BTableR,0,sizeof(BTableR));
	memset(BTableG,0,sizeof(BTableG));
	memset(BTableB,0,sizeof(BTableB));
	int	DCount=0;
	for(int i=0;i<N;i++){
		int	Y=Area.GetFLineAbsY(i)+my;
		if(Y<0 || MaxLines<=Y)
			continue;
		int	X1=Area.GetFLineLeftX(i) +mx;
		int	X2=Area.GetFLineRightX(i)+mx;
		if(X1<0)
			X1=0;
		if(DotPerLine<X2)
			X2=DotPerLine;
		if(X1<X2){
			BYTE	*sR=ImageList[0]->GetY(Y)+X1;
			BYTE	*sG=ImageList[1]->GetY(Y)+X1;
			BYTE	*sB=ImageList[2]->GetY(Y)+X1;
			for(int X=X1;X<X2;X++){
				BTableR[*sR]++;
				BTableG[*sG]++;
				BTableB[*sB]++;
				sR++;
				sG++;
				sB++;
			}
			DCount+=X2-X1;
		}
	}
	int	AbandonDot=DCount*(1.0-AdoptedRate/100.0)/2;
	Ret.Red		=MakeAverage(BTableR,AbandonDot);
	Ret.Green	=MakeAverage(BTableG,AbandonDot);
	Ret.Blue	=MakeAverage(BTableB,AbandonDot);
}

ExeResult	ColorDifferenceItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	//_CrtCheckMemory();
	GetCenter(MasterCx,MasterCy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	Reference1	=NULL;
	Reference2	=NULL;
	ColorDifferenceInPage	*Pg=(ColorDifferenceInPage *)GetParentInPage();
	for(AlgorithmItemPI	*L=Pg->GetFirstData();L!=NULL;L=L->GetNext()){
		ColorDifferenceRegulation	*B=dynamic_cast<ColorDifferenceRegulation *>(L);
		if(B!=NULL){
			if(B->GetArea().GetMinX()<=MasterCx && MasterCx<=B->GetArea().GetMaxX()){
				Reference1	=B;
				break;
			}
		}
	}
	if(Reference1==NULL){
		for(AlgorithmItemPI	*L=Pg->GetFirstData();L!=NULL;L=L->GetNext()){
			ColorDifferenceRegulation	*B=dynamic_cast<ColorDifferenceRegulation *>(L);
			if(B!=NULL){
				Reference1	=B;
				break;
			}
		}
	}
	if(Reference1!=NULL){
		for(AlgorithmItemPI	*L=Pg->GetFirstData();L!=NULL;L=L->GetNext()){
			ColorDifferenceRegulation	*B=dynamic_cast<ColorDifferenceRegulation *>(L);
			if(B!=NULL && Reference1!=B){
				if(B->GetArea().GetMinX()<=MasterCx && MasterCx<=B->GetArea().GetMaxX()){
					Reference2	=B;
					break;
				}
			}
		}
		if(Reference2==NULL){
			for(AlgorithmItemPI	*L=Pg->GetFirstData();L!=NULL;L=L->GetNext()){
				ColorDifferenceRegulation	*B=dynamic_cast<ColorDifferenceRegulation *>(L);
				if(B!=NULL && Reference1!=B){
					Reference2	=B;
					break;
				}
			}
		}
	}

	const	ColorDifferenceThreshold	*RThr=GetThresholdR();
	if(GetLayerNumb()>=3){
		ImageBuffer *ImageList[100];
		GetMasterBuffList	(ImageList);
		MakeAverageColor(GetArea(),ImageList ,0,0
							,GetDotPerLine() ,GetMaxLines()
							,RThr->AdoptedRate
							,MasterColor);
	}
	return Ret;
}

bool	IsInsideH(double mH ,double dH ,double tH)
{
	double	mHL=mH-dH;
	double	mHH=mH+dH;
	if(mHL<0){
		mHL+=360;
		if(mHL<=tH || tH<=mHH)
			return true;
		return false;
	}
	if(mHH>=360){
		mHH-=360;
		if(mHL<=tH || tH<=mHH)
			return true;
		return false;
	}
	if(mHL<=tH && tH<=mHH)
		return true;
	return false;
}

double	CalcInterpolation(float Y
						 ,float Y1,float X1
						 ,float Y2,float X2)
{
	/*
		a*x1+b=Y1
		a*x2+b=Y2
	
		a(x1-x2)=Y1-Y2
		a=(Y1-Y2)/(x1-x2)
		b=Y1-a*x1
	*/
	double	M=X1-X2;
	if(M==0)
		return Y;
	double	a=(Y1-Y2)/M;
	if(a==0)
		return Y;
	double	b=Y1-a*X1;
	return (Y-b)/a;
}

ExeResult	ColorDifferenceItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	GetCenter(MasterCx,MasterCy);
	const	ColorDifferenceThreshold	*RThr=GetThresholdR();
	if(GetLayerNumb()>=3){
		ImageBuffer *ImageList[100];
		GetTargetBuffList	(ImageList);
		MakeAverageColor(GetArea(),ImageList ,mx,my
							,GetDotPerLine() ,GetMaxLines()
							,RThr->AdoptedRate
							,TargetColor);
		double	R,G,B;
		if(Reference1!=NULL && Reference2!=NULL){
			R=CalcInterpolation(TargetColor.Red.GetFloat()
								,Reference1->TargetColor.Red.GetFloat(),Reference1->MasterColor.Red.GetFloat()
								,Reference2->TargetColor.Red.GetFloat(),Reference2->MasterColor.Red.GetFloat());
			G=CalcInterpolation(TargetColor.Green.GetFloat()
								,Reference1->TargetColor.Green.GetFloat(),Reference1->MasterColor.Green.GetFloat()
								,Reference2->TargetColor.Green.GetFloat(),Reference2->MasterColor.Green.GetFloat());
			B=CalcInterpolation(TargetColor.Blue.GetFloat()
								,Reference1->TargetColor.Blue.GetFloat(),Reference1->MasterColor.Blue.GetFloat()
								,Reference2->TargetColor.Blue.GetFloat(),Reference2->MasterColor.Blue.GetFloat());
		}
		else
		if(Reference1!=NULL){
			R=TargetColor.Red  .GetFloat()-(Reference1->TargetColor.Red  .GetFloat()-Reference1->MasterColor.Red  .GetFloat());
			G=TargetColor.Green.GetFloat()-(Reference1->TargetColor.Green.GetFloat()-Reference1->MasterColor.Green.GetFloat());
			B=TargetColor.Blue .GetFloat()-(Reference1->TargetColor.Blue .GetFloat()-Reference1->MasterColor.Blue .GetFloat());
			ReferedCurrentColor=PreciseColor(R,G,B);
		}
		else{
			R=TargetColor.Red.GetFloat();
			G=TargetColor.Green.GetFloat();
			B=TargetColor.Blue.GetFloat();
			ReferedCurrentColor=PreciseColor(R,G,B);
		}
		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(0,0);

		if(((ColorDifferenceInPage *)GetParentInPage())->RegistInFlowMode==true){
			PreciseColorList	*S=new PreciseColorList(R,G,B);
			FlowBrightness.AppendList(S);
			CalcFlowCenterColor();
		}
		else{
			double	MR=MasterColor.Red.GetFloat();
			double	MG=MasterColor.Green.GetFloat();
			double	MB=MasterColor.Blue.GetFloat();

			double	mX ,mY ,mZ;
			RGB2XYZ(MR,MG ,MB,mX ,mY ,mZ);
			double	tX ,tY ,tZ;
			RGB2XYZ(R,G ,B,tX ,tY ,tZ);

			double	mL,mA,mB;
			XYZ2LAB(mX ,mY ,mZ,mL,mA,mB);
			double	tL,tA,tB;
			XYZ2LAB(tX ,tY ,tZ,tL,tA,tB);

			ColorDifferenceBase	*ABase=tGetParentBase();
			if(ABase->DeltaE2000==true)
				ResultDeltaE=GetDeltaE2000(mL,mA,mB,tL,tA,tB);
			else
				ResultDeltaE=GetDeltaE76(mL,mA,mB,tL,tA,tB);

			Res->SetResultDouble(ResultDeltaE);

			if(RThr->JudgeMethod==0){
				if(OKBrightness.GetCount()>0 && NGBrightness.GetCount()>0){
					RGBSample	S(qRgb(R,G,B));
					double	LenOK=OKBrightness.GetClosedLength(S);
					double	LenNG=NGBrightness.GetClosedLength(S);

					ColorDifferenceResultPosList	*ROK=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
					ROK->SetResult(LenOK);
					ROK->result			=1;
					Res->AddPosList(ROK);

					ColorDifferenceResultPosList	*RNG=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
					RNG->SetResult(LenNG);
					RNG->result			=2;
					Res->AddPosList(RNG);

					if(LenNG<LenOK){
						Res->SetError(2);
						RNG->result			=0x10000+2;
					}
					else{
						Res->SetError(1);
					}
				}
				else{
					if(ResultDeltaE>RThr->THDeltaE){
						Res->SetError(2);
						
					}
					else{
						Res->SetError(1);
					}
				}
			}
			else if(RThr->JudgeMethod==1){
				if(ResultDeltaE>RThr->THDeltaE){
					ColorDifferenceResultPosList	*RNG=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
					RNG->SetResult(ResultDeltaE);
					RNG->result			=0x10100;
					Res->AddPosList(RNG);
					Res->SetError(2);
				}
				else{
					Res->SetError(1);
				}
			}
			else if(RThr->JudgeMethod==2){
				double	tH,tS,tV;
				RGB2HSV(tH,tS,tV,R ,G ,B);
				if(StatisticData.HAvr!=0 || StatisticData.SAvr!=0 || StatisticData.VAvr!=0){
					if(IsInsideH(StatisticData.HAvr ,RThr->dH,tH)==true
					&& (StatisticData.SAvr-RThr->dSL)<=tS && tS<=(StatisticData.SAvr+RThr->dSH)
					&& (StatisticData.VAvr-RThr->dVL)<=tV && tV<=(StatisticData.VAvr+RThr->dVH)){
						Res->SetError(1);
					}
					else{
						ColorDifferenceResultPosList	*RNG=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
						RNG->SetResult(ResultDeltaE);
						RNG->result			=0x10200;
						Res->AddPosList(RNG);
						Res->SetError(2);
					}
				}
				else{
					double	mH,mS,mV;
					RGB2HSV(mH,mS,mV,MR ,MG ,MB);
					double	dH=mH-tH;
					if(dH>180)
						dH=360-dH;
					if(dH<0){
						dH=-dH;
						if(dH>180){
							dH=360-dH;
						}
					}
					double	dS=tS-mS;
					double	dV=tV-mV;

					ResultDiffR=dH;
					ResultDiffG=dS;
					ResultDiffB=dV;

					if(dH<=RThr->dH 
					&& ((dS<0 && (-dS)<=RThr->dSL) || (dS>=0 && dS<=RThr->dSH))
					&& ((dV<0 && (-dV)<=RThr->dVL) || (dV>=0 && dV<=RThr->dVH))){
						Res->SetError(1);
					}
					else{
						ColorDifferenceResultPosList	*RNG=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
						RNG->SetResult(ResultDeltaE);
						RNG->result			=0x10200;
						Res->AddPosList(RNG);
						Res->SetError(2);
					}
				}
			}
			if(OutputConstantly==true){
				double	tH,tS,tV;
				RGB2HSV(tH,tS,tV,R ,G ,B);
				
				ColorDifferenceResultPosList	*RH=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
				RH->SetResult(tH);
				RH->result			=11;
				Res->AddPosList(RH);

				ColorDifferenceResultPosList	*RS=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
				RS->SetResult(tS);
				RS->result			=12;
				Res->AddPosList(RS);

				ColorDifferenceResultPosList	*RV=new ColorDifferenceResultPosList(this,MasterCx,MasterCy);
				RV->SetResult(tV);
				RV->result			=13;
				Res->AddPosList(RV);
			}
		}
	}
	FinishCalc();
	return _ER_true;
}
void	ColorDifferenceItem::AddSampleColor(bool OK)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;

		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ImageBuffer *ImageList[100];
	GetTargetBuffList	(ImageList);

	PreciseColor Color;
	const	ColorDifferenceThreshold	*RThr=GetThresholdR();
	MakeAverageColor(GetArea(),ImageList ,mx,my
						,GetDotPerLine() ,GetMaxLines()
						,RThr->AdoptedRate
						,Color);
	RGBSample	*s=new RGBSample(qRgb(Color.Red.GetInt(),Color.Green.GetInt(),Color.Blue.GetInt()));
	if(OK==true){
		OKBrightness.AppendList(s);
	}
	else{
		NGBrightness.AppendList(s);
	}
}
void	ColorDifferenceItem::CalcFlowCenterColor(void)
{
	double	R=0;
	double	G=0;
	double	B=0;
	for(PreciseColorList *s=FlowBrightness.GetFirst();s!=NULL;s=s->GetNext()){
		R+=s->GetRed();
		G+=s->GetGreen();
		B+=s->GetBlue();
	}
	if(FlowBrightness.GetCount()>0){
		R/=FlowBrightness.GetCount();
		G/=FlowBrightness.GetCount();
		B/=FlowBrightness.GetCount();
		FlowCenterColor=PreciseColor(R,G,B);
	}
}

void	ColorDifferenceItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOneColorDifference){
		ColorDifferenceItem *src=dynamic_cast<ColorDifferenceItem *>(Data);
		if(src!=NULL){
			if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
				ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
				UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
				::Save(UPointer->GetWritePointer(),GetID());
				Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				SetItemName(src->GetItemName());
				OutputConstantly=src->OutputConstantly;
				OKBrightness	=src->OKBrightness	;
				NGBrightness	=src->NGBrightness	;
				MasterColor		=src->MasterColor	;
				TargetColor		=src->TargetColor	;
				MasterCx		=src->MasterCx;
				MasterCy		=src->MasterCy;
				const	ColorDifferenceThreshold	*RThr=src->GetThresholdR(GetLayersBase());
				GetThresholdW()->AdoptedRate	=RThr->AdoptedRate	;
				GetThresholdW()->THDeltaE		=RThr->THDeltaE		;
				GetThresholdW()->JudgeMethod	=RThr->JudgeMethod	;
				GetThresholdW()->dH				=RThr->dH			;	
				GetThresholdW()->dSL			=RThr->dSL			;
				GetThresholdW()->dSH			=RThr->dSH			;
				GetThresholdW()->dVL			=RThr->dVL			;
				GetThresholdW()->dVH			=RThr->dVH			;
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_AllColorDifference){
		ColorDifferenceItem *src=dynamic_cast<ColorDifferenceItem *>(Data);
		if(src!=NULL){
			if(GetLibID()==src->GetLibID()){
				ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
				UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
				::Save(UPointer->GetWritePointer(),GetID());
				Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				const	ColorDifferenceThreshold	*RThr=src->GetThresholdR(GetLayersBase());
				GetThresholdW()->AdoptedRate	=RThr->AdoptedRate	;
				GetThresholdW()->THDeltaE		=RThr->THDeltaE		;
				GetThresholdW()->JudgeMethod	=RThr->JudgeMethod	;
				GetThresholdW()->dH				=RThr->dH			;	
				GetThresholdW()->dSL			=RThr->dSL			;
				GetThresholdW()->dSH			=RThr->dSH			;
				GetThresholdW()->dVL			=RThr->dVL			;
				GetThresholdW()->dVH			=RThr->dVH			;
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessThis){
		ColorDifferenceItem *src=dynamic_cast<ColorDifferenceItem *>(Data);
		if(src!=NULL){
			if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
				ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
				UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
				::Save(UPointer->GetWritePointer(),GetID());
				Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				//ColorDifferenceItem *src=(ColorDifferenceItem *)Data;
				//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessAll){
		if(GetLibID()==((ColorDifferenceItem *)Data)->GetLibID()){
			ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
			UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			//ColorDifferenceItem *src=(ColorDifferenceItem *)Data;
			//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		ColorDifferenceItem *src=dynamic_cast<ColorDifferenceItem *>(Data);
		if(src!=NULL){
			if(GetLibID()==src->GetLibID()){
				ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
				UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemNameDataCommand);
				::Save(UPointer->GetWritePointer(),GetID());
				::Save(UPointer->GetWritePointer(),GetItemName());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

				SetItemName(src->GetItemName());
			}
		}
	}
}

static	int	SortFuncDouble(const void *a ,const void *b)
{
	double	d=(*(double *)a) - (*(double *)b);
	if(d>0)
		return 1;
	if(d<0)
		return -1;
	return 0;
}
static	double	MakeAverage(double *Dim,int N,int LNumb)
{
	double	Avr=0;
	for(int i=LNumb;i<N-LNumb;i++){
		Avr+=Dim[i];
	}
	int	Count=N-2*LNumb;
	if(Count<=0)
		return 0;
	return Avr/Count;
}
static	void	MakeV(double *Dim ,double Avr ,int N ,int LNumb
					,double &Ls ,double &Hs)
{
	double	L=0;
	double	H=0;
	int	Ln=0;
	int	Hn=0;
	
	for(int i=LNumb;i<N-LNumb;i++){
		if(Dim[i]<=Avr){
			L+=(Dim[i]-Avr)*(Dim[i]-Avr);
			Ln++;
		}
		if(Dim[i]>=Avr){
			H+=(Dim[i]-Avr)*(Dim[i]-Avr);
			Hn++;
		}
	}
	if(Ln!=0)
		Ls=sqrt(L/Ln);
	if(Hn!=0)
		Hs=sqrt(H/Hn);
}

void	ColorDifferenceItem::SetStatisticThreshold(double SigmaH ,double SigmaS ,double SigmaV)
{
	int	N=FlowBrightness.GetCount();
	double	*HDim=new double[N];
	double	*SDim=new double[N];
	double	*VDim=new double[N];

	int	n=0;
	for(PreciseColorList *s=FlowBrightness.GetFirst();s!=NULL;s=s->GetNext()){
		double	H,S,V;
		double	R=s->GetRed();
		double	G=s->GetGreen();
		double	B=s->GetBlue();
		RGB2HSV(H,S,V,R,G,B);
		HDim[n]=H;
		SDim[n]=S;
		VDim[n]=V;
		n++;
	}
	qsort(HDim,N,sizeof(double),SortFuncDouble);
	qsort(SDim,N,sizeof(double),SortFuncDouble);
	qsort(VDim,N,sizeof(double),SortFuncDouble);

	const	ColorDifferenceThreshold	*RThr=GetThresholdR();
	int	LNumb=(int)(N*(100.0-RThr->AdoptedRate)/100.0/2.0);
	if(LNumb==0)
		LNumb=1;

	StatisticData.HAvr=MakeAverage(HDim,N,LNumb);
	MakeV(HDim ,StatisticData.HAvr ,N ,LNumb ,StatisticData.Hvl,StatisticData.Hvh);
	StatisticData.SAvr=MakeAverage(SDim,N,LNumb);
	MakeV(SDim ,StatisticData.SAvr ,N ,LNumb ,StatisticData.Svl,StatisticData.Svh);
	StatisticData.VAvr=MakeAverage(VDim,N,LNumb);
	MakeV(VDim ,StatisticData.VAvr ,N ,LNumb ,StatisticData.Vvl,StatisticData.Vvh);

	GetThresholdW()->dH=max(StatisticData.Hvl,StatisticData.Hvh)*SigmaH;
	GetThresholdW()->dSL=StatisticData.Svl*SigmaS;
	GetThresholdW()->dSH=StatisticData.Svh*SigmaS;
	GetThresholdW()->dVL=StatisticData.Vvl*SigmaV;
	GetThresholdW()->dVH=StatisticData.Vvh*SigmaV;

	delete	[]HDim;
	delete	[]SDim;
	delete	[]VDim;
}
void	ColorDifferenceItem::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
	
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	MoveTo(mx,my);
}

//-----------------------------------------------------------------
ColorDifferenceRegulation::ColorDifferenceRegulation(void)
{
	AVector	=NULL;
}
AlgorithmItemPI	&ColorDifferenceRegulation::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);

	const	ColorDifferenceRegulation	*Item=dynamic_cast<const ColorDifferenceRegulation *>(&src);
	if(Item!=NULL){
		Brightness		=Item->Brightness;
		MasterColor		=Item->MasterColor;
		TargetColor		=Item->TargetColor;
		MasterCx		=Item->MasterCx;
		MasterCy		=Item->MasterCy;
	}

	return *this;
}

void	ColorDifferenceRegulation::CopyThreshold(ColorDifferenceRegulation &src)
{
	Brightness		=src.Brightness;
	MasterColor		=src.MasterColor;
	TargetColor		=src.TargetColor;
	MasterCx		=src.MasterCx;
	MasterCy		=src.MasterCy;
}

bool    ColorDifferenceRegulation::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	WORD	Ver=2;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);

	QString	tItemName=GetItemName();
	if(::Save(f,tItemName)==false)
		return false;
	if(Brightness.Save(f)==false)
		return false;
	if(MasterColor.Save(f)==false)
		return false;

	return true;
}
bool    ColorDifferenceRegulation::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	
	QString	tItemName;
	if(::Load(f,tItemName)==false)
		return false;
	SetItemName(tItemName);

	if(Brightness.Load(f)==false)
		return false;
	if(MasterColor.Load(f)==false)
		return false;

	return true;
}

void	ColorDifferenceRegulation::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SetVisible(true);
	QColor	SaveColor=Attr->NormalColor;
	Attr->NormalColor=QColor(255,0,255);
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	Attr->NormalColor=SaveColor;

	int	kx=(MasterCx+movx)*ZoomRate;
	int	ky=(MasterCy+movy)*ZoomRate;
	if(0<=kx && (kx+120)<pnt.width() && 0<=ky && (ky+40)<pnt.height()){
		QRect	rect(0,0,pnt.width(),pnt.height());
		QPainter	PData(&pnt);	
		PData.drawText(kx,ky,pnt.width()-kx,pnt.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/"Reference")
						,&rect);
	}
}

void	ColorDifferenceRegulation::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false && ZoomRate>1.0){
				int	kx=(MasterCx+MovX)*ZoomRate;
				int	ky=(MasterCy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						,QString(/**/"Pg=")+QString::number(GetPage()) +QString(/**/" ")
						,&rect);
				}
			}
		}
	}
}

ExeResult	ColorDifferenceRegulation::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	//_CrtCheckMemory();
	GetCenter(MasterCx,MasterCy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	if(GetLayerNumb()>=3){
		ImageBuffer *ImageList[3];
		GetMasterBuffList	(ImageList);
		const	ColorDifferenceThreshold	*RThr=GetThresholdR();
		MakeAverageColor(GetArea(),ImageList ,0,0
							,GetDotPerLine() ,GetMaxLines()
							,RThr->AdoptedRate
							,MasterColor);
	}

	return Ret;
}

ExeResult	ColorDifferenceRegulation::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	const	ColorDifferenceThreshold	*RThr=GetThresholdR();
	if(RThr->AdaptAlignment==true){
		if(AVector!=NULL){
			mx=AVector->ShiftX;
			my=AVector->ShiftY;
		}
		else{
			AlignmentPacket2D	V;
			V.PosXOnTarget=MasterCx;
			V.PosYOnTarget=MasterCy;
			V.ShiftX=0;
			V.ShiftY=0;
			GetAlignmentForProcessing(V);
			mx=V.ShiftX;
			my=V.ShiftY;
		}
	}
	else{
		mx=0;
		my=0;
	}
	if(GetLayerNumb()>=3){
		ImageBuffer *ImageList[3];
		GetTargetBuffList	(ImageList);
		MakeAverageColor(GetArea(),ImageList ,mx,my
							,GetDotPerLine() ,GetMaxLines()
							,RThr->AdoptedRate
							,TargetColor);
	}

	FinishCalc();
	return _ER_true;
}
void	ColorDifferenceRegulation::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;

		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	MoveTo(mx,my);
}

void	ColorDifferenceRegulation::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOneColorDifference){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			ColorDifferenceThreshold	*WThr=GetThresholdW();
			ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
			UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ColorDifferenceRegulation *src=(ColorDifferenceRegulation *)Data;
			SetItemName(src->GetItemName());
			const	ColorDifferenceThreshold	*RThr=src->GetThresholdR(GetLayersBase());
			CopyThreshold(*src);
			WThr->AdoptedRate	=RThr->AdoptedRate;
			WThr->THDeltaE		=RThr->THDeltaE;
			WThr->AdaptAlignment=RThr->AdaptAlignment;
		}
	}
	else if(Command==SetIndependentItemDataCommand_AllColorDifference){
		if(GetLibID()==((ColorDifferenceItem *)Data)->GetLibID()){
			ColorDifferenceThreshold	*WThr=GetThresholdW();
			ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
			UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ColorDifferenceRegulation *src=(ColorDifferenceRegulation *)Data;
			const	ColorDifferenceThreshold	*RThr=src->GetThresholdR(GetLayersBase());
			WThr->AdoptedRate	=RThr->AdoptedRate;
			WThr->THDeltaE		=RThr->THDeltaE;
			WThr->AdaptAlignment=RThr->AdaptAlignment;
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessThis){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
			UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			//ColorDifferenceRegulation *src=(ColorDifferenceRegulation *)Data;
			//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemDataCommand_SetThreBrightnessAll){
		if(GetLibID()==((ColorDifferenceItem *)Data)->GetLibID()){
			ColorDifferenceInPage	*Pg=dynamic_cast<ColorDifferenceInPage *>(GetParentInPage());
			UndoElement<ColorDifferenceInPage>	*UPointer=new UndoElement<ColorDifferenceInPage>(Pg,&ColorDifferenceInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			//ColorDifferenceRegulation *src=(ColorDifferenceRegulation *)Data;
			//double	C=GetArea().GetAverage(GetMasterBuff(),0,0);
		}
	}
}


ExeResult	ColorDifferenceItem::ExecutePostProcessing	(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=AlgorithmItemPITemplate<ColorDifferenceInPage,ColorDifferenceBase>::ExecutePostProcessing	(ExeID,ThreadNo,Res);

	struct ResultColorDifferenceForExtraData	RData;
	ColorDifferenceThreshold	*WThr=GetThresholdW();
	RData.ThresholdDeltaE	=WThr->THDeltaE;
	RData.ResultDeltaE		=ResultDeltaE;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Buff.write((const char *)&RData,sizeof(RData));

	ResultExtraData=Buff.buffer();

	return Ret;
}


void	ColorDifferenceItem::UpdateThreshold(int LearningMenuID ,LearningResource &LRes)
{
	if(LearningMenuID==LearningMenu_ColorDifference_OK_ByDeltaE){
		ColorDifferenceThreshold	*WThr=GetThresholdW();
		double	d=LRes.DoubleCause;
		if(WThr->THDeltaE<d){
			WThr->THDeltaE=d;
		}
	}
}