/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignmentPico.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoAlignmentResource.h"
#include "XAutoAlignment.h"
#include "XDoubleClass.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XAutoMaskingPI.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XStatisticPacket.h"
#include "XPointer.h"
#include "XFlexArea.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "stdlib.h"

AutoAlignmentInPico::CalcedData::CalcedData(void)
{
	MasterAddA	=0;
	MasterAddA2	=0;
	StepX=StepY	=1;
}

void	AutoAlignmentInPico::CalcedData::SetStep(int xs ,int ys)
{
	StepX=xs;
	StepY=ys;
}

void	AutoAlignmentInPico::CalcedData::InitialCalc(ImageBuffer &Buff ,FlexArea &Area)
{
	int	N=Area.GetFLineLen();
	MasterAddA	=0;
	MasterAddA2	=0;
	DotCount=0;
	for(int i=0;i<N;i++){
		int	Y	=Area.GetFLineAbsY(i);
		if((Y%StepY)==0){
			int	X	=Area.GetFLineLeftX(i);
			int	Numb=Area.GetFLineNumb(i);
			int	iMasterAddA	=0;
			int	iMasterAddA2=0;
			BYTE	*s=Buff.GetY(Y)+X;
			for(int x=0;x<Numb;x+=StepX){
				int	d=s[x];
				iMasterAddA+=d;
				iMasterAddA2+=d*d;
				DotCount++;
			}
			MasterAddA	+=iMasterAddA;
			MasterAddA2	+=iMasterAddA2;
		}
	}
}

double	AutoAlignmentInPico::CalcedData::GetMasterVar(void)
{
	double	AvrS=MasterAddA/DotCount;
	double	M=MasterAddA2-AvrS*AvrS*DotCount;
	if(M>=0){
		return sqrt(M);
	}
	return 0.0;
}



//=========================================================================================

AutoAlignmentInPico::AutoAlignmentInPico(AutoAlignmentSheet *parent,int xn ,int yn)
:Parent(parent)
{
	Effective=false;
	NeedAdjust=true;
	for(int i=0;i<sizeof(ConnectedPico)/sizeof(ConnectedPico[0]);i++){
		ConnectedPico[i]=NULL;
	}
	Xn=xn;
	Yn=yn;
	DimPoint=NULL;

	MatchResult=0;
	ShiftX=0;
	ShiftY=0;
	ConnectedPico[0]=NULL;
	ConnectedPico[1]=NULL;
	BasePointer		=NULL;
}

AutoAlignmentInPico::~AutoAlignmentInPico(void)
{
}

void	AutoAlignmentInPico::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AutoAlignmentDrawAttr	*a=dynamic_cast<AutoAlignmentDrawAttr *>(Attr);
	if(a!=NULL){
		if(a->Mastered==true){
			if((a->DrawPico&1)!=0)
				TransArea.Draw(0,0 ,&pnt ,qRgba(255,0,255,192)	,ZoomRate ,movx ,movy);
			if((a->DrawPico&2)!=0)
				PickupArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
			if((a->DrawPico&4)!=0)
				OtherArea.Draw(0,0 ,&pnt ,qRgba(255,0,192,192)	,ZoomRate ,movx ,movy);
			if((a->DrawPico&16)!=0)
				FringeArea.Draw(0,0 ,&pnt ,qRgba(160,0,255,192)	,ZoomRate ,movx ,movy);
		}
		else{
			if((a->DrawPico&1)!=0)
				TransArea.Draw(0,0 ,&pnt ,qRgba(255,0,255,192)		,ZoomRate ,movx+ShiftX ,movy+ShiftY);
			if((a->DrawPico&2)!=0)
				PickupArea.Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx+ShiftX ,movy+ShiftY);
			if((a->DrawPico&4)!=0)
				OtherArea.Draw(0,0 ,&pnt ,qRgba(255,0,192,192)		,ZoomRate ,movx+ShiftX ,movy+ShiftY);
			if((a->DrawPico&16)!=0)
				FringeArea.Draw(0,0 ,&pnt ,qRgba(160,0,255,192)		,ZoomRate ,movx+ShiftX ,movy+ShiftY);
		}

		QPainter	Pnt(&pnt);
		Pnt.setPen(Qt::red);
		int	x1=(GetArea().GetMinX()+movx)*ZoomRate;
		int	y1=(GetArea().GetMinY()+movy)*ZoomRate;
		int	x2=(GetArea().GetMaxX()+movx)*ZoomRate;
		int	y2=(GetArea().GetMaxY()+movy)*ZoomRate;
		Pnt.drawLine(x1,y1,x1,y2);
		Pnt.drawLine(x1,y2,x2,y2);
		Pnt.drawLine(x2,y2,x2,y1);
		Pnt.drawLine(x2,y1,x1,y1);

		if((a->DrawPico&8)!=0)
			DrawInfo(Pnt ,movx,movy,ZoomRate);
	}
}

void	AutoAlignmentInPico::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	QColor	c=Qt::green;
	c.setAlpha(100);
	GetArea().Draw(0,0,&IData ,c.rgba()
						,ZoomRate ,MovX ,MovY);
	int	dx=ShiftX;
	int	dy=ShiftY;
	QColor	d=Qt::red;
	d.setAlpha(100);
	GetArea().Draw(dx,dy,&IData ,d.rgba()
						,ZoomRate ,MovX ,MovY);
	DrawInfo(PData ,MovX,MovY,ZoomRate);
}

void	AutoAlignmentInPico::DrawInfo(QPainter &Pnt ,int MovX ,int MovY ,double ZoomRate)
{
	int	W=Area.GetWidth();
	int	H=Area.GetHeight();
	int	L=(W+H)/6*ZoomRate;
	if(L>10){
		int	Cx,Cy;
		Area.GetCenter(Cx,Cy);
		int	X1=(Cx+MovX)*ZoomRate;
		int	Y1=(Cy+MovY)*ZoomRate;
		int	X2=(Cx+ShiftX+MovX)*ZoomRate;
		int	Y2=(Cy+ShiftY+MovY)*ZoomRate;
		Pnt.setPen(Qt::cyan);
		Pnt.drawLine(X1,Y1,X2,Y2);
		double	s=GetSita(-ShiftX,-ShiftY);
		double	s1=s+M_PI/6;
		double	s2=s-M_PI/6;
		int	ArrowR=5;
		Pnt.drawLine(X2,Y2,ArrowR*cos(s1)+X2,ArrowR*sin(s1)+Y2);
		Pnt.drawLine(X2,Y2,ArrowR*cos(s2)+X2,ArrowR*sin(s2)+Y2);
		char	buff[100];
		sprintf(buff,/**/"Xn,Yn=%d,%d",Xn,Yn);
		Pnt.drawText(X1,Y1,buff);
		sprintf(buff,/**/"Dx,Dy=%.1lf ,%.1lf",ShiftX,ShiftY);
		Pnt.drawText(X1,Y1+16,buff);
		sprintf(buff,/**/"Match=%.3lf",MatchResult);
		Pnt.drawText(X1,Y1+16*2,buff);
		if(Effective==true && Adopted==true){
			sprintf(buff,/**/"E:true && A:true");
			Pnt.drawText(X1,Y1+16*3,buff);
		}
		else{
			if(Effective==false && Adopted==true){
				sprintf(buff,/**/"E:false && A:true");
			}
			else if(Effective==true && Adopted==false){
				sprintf(buff,/**/"E:true && A:false");
			}
			else{
				sprintf(buff,/**/"E:false && A:false");
			}
			Pnt.drawText(X1,Y1+16*3,buff);

			if(ConnectedPico[0]!=NULL && ConnectedPico[1]!=NULL){
				sprintf(buff,/**/"Conn Xn1,Yn1=%d,%d",ConnectedPico[0]->Xn,ConnectedPico[0]->Yn);
				Pnt.drawText(X1,Y1+16*4,buff);
				sprintf(buff,/**/"Conn Xn2,Yn2=%d,%d",ConnectedPico[1]->Xn,ConnectedPico[1]->Yn);
				Pnt.drawText(X1,Y1+16*5,buff);
			}
		}
	}
}

static	int	AutoADbg=0;
static	int	AutoAXn=14;
static	int	AutoAYn=8;

bool	AutoAlignmentInPico::ExecuteInitialAfterEdit(BYTE **MasterMap ,int MasterXByte ,int MasterYLen
													,ExecuteInitialAfterEditInfo &EInfo)
{
	if(AutoAXn==Xn && AutoAYn==Yn){
		AutoADbg++;
	}
	BasePointer=NULL;
	Area.GetCenter(CenterX,CenterY);
	int	XLen=Area.GetWidth();
	int	YLen=Area.GetHeight();
	int	XByte=(XLen+7)/8;
	BYTE	**Map	=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(Map ,0 ,XByte,YLen);
	const AutoAlignmentThreshold	*RThr=Parent->GetThresholdR();

	int	Dx=Area.GetMinX();
	int	Dy=Area.GetMinY();
	int	DotCount=0;

	for(int y=0;y<YLen;y++){
		if((Dy+y)<0 || (Dy+y)>=Parent->GetMaxLines()){
			continue;
		}
		BYTE	*s=MasterMap[Dy+y];
		BYTE	*d=Map[y];
		for(int x=0;x<XLen;x++){
			int	X=Dx+x;
			if(X<0 || X>=Parent->GetDotPerLine()){
				continue;
			}
			if(GetBmpBitOnY(s,X)!=0){
				SetBmpBitOnY1(d,x);
				DotCount++;
			}
		}
	}
	if(DotCount>20){
		Effective=true;
		TransArea.BuildFromRaster(Map,XByte,YLen,Dx,Dy);
		AutoAlignmentBase	*pBase=(AutoAlignmentBase *)(Parent->GetParentBase());

		AlgorithmInPageRoot	*PPage=Parent->GetParentInPage();
		ImagePointerContainer Images;
		PPage->GetDataInPage()->GetMasterImages(Images);

		int	x1=GetArea().GetMinX();
		int	y1=GetArea().GetMinY();
		int	x2=GetArea().GetMaxX();
		int	y2=GetArea().GetMaxY();
		int	DotPerLine	=Parent->GetDotPerLine();
		int	MaxLines	=Parent->GetMaxLines();

		ImageBuffer *LMasterBuff;
		CalcedData	*CalcFirst;
		CalcedData	*CalcDetail;

		if(GetLayerNumb()>=3){
			CalcFirstR.SetStep(2,2);
			CalcFirstG.SetStep(2,2);
			CalcFirstB.SetStep(2,2);
			CalcDetailR.SetStep(1,1);
			CalcDetailG.SetStep(1,1);
			CalcDetailB.SetStep(1,1);

			ImagePointerList *RBuff=Images.GetItem(0);
			ImagePointerList *GBuff=Images.GetItem(1);
			ImagePointerList *BBuff=Images.GetItem(2);

			CalcFirstR.InitialCalc(*RBuff->GetImage(),TransArea);
			CalcFirstG.InitialCalc(*GBuff->GetImage() ,TransArea);
			CalcFirstB.InitialCalc(*BBuff->GetImage() ,TransArea);
			CalcDetailR.InitialCalc(*RBuff->GetImage() ,TransArea);
			CalcDetailG.InitialCalc(*GBuff->GetImage() ,TransArea);
			CalcDetailB.InitialCalc(*BBuff->GetImage() ,TransArea);

			//ï™éUÇ™ç≈Ç‡ëÂÇ´Ç¢êFÇëIë
			double	VR=CalcFirstR.GetMasterVar();
			double	VG=CalcFirstG.GetMasterVar();
			double	VB=CalcFirstB.GetMasterVar();
			if(VR>=VG && VR>=VB){
				SelectFirst=0;
			}
			if(VG>=VR && VG>=VB){
				SelectFirst=1;
			}
			if(VB>=VR && VB>=VG){
				SelectFirst=2;
			}

			//àÍíËó ó£ÇÍÇΩé©ï™é©êgÇ∆àÍívÇ∑ÇÈÇ∆Ç´ñ≥å¯óÃàÊÇ…Ç∑ÇÈ
			if(SelectFirst==0){
				LMasterBuff=RBuff->GetImage();
				CalcFirst=&CalcFirstR;
				CalcDetail=&CalcDetailR;
			}
			else if(SelectFirst==1){
				LMasterBuff=GBuff->GetImage();
				CalcFirst=&CalcFirstG;
				CalcDetail=&CalcDetailG;
			}
			else if(SelectFirst==2){
				LMasterBuff=BBuff->GetImage();
				CalcFirst=&CalcFirstB;
				CalcDetail=&CalcDetailB;
			}
		}
		else if(GetLayerNumb()==1){
			SelectFirst=0;
			CalcFirstR.SetStep(2,2);
			CalcDetailR.SetStep(1,1);

			ImagePointerList *RBuff=Images.GetItem(0);

			CalcFirstR.InitialCalc(*RBuff->GetImage(),TransArea);
			CalcDetailR.InitialCalc(*RBuff->GetImage() ,TransArea);


			//àÍíËó ó£ÇÍÇΩé©ï™é©êgÇ∆àÍívÇ∑ÇÈÇ∆Ç´ñ≥å¯óÃàÊÇ…Ç∑ÇÈ
			LMasterBuff=RBuff->GetImage();
			CalcFirst=&CalcFirstR;
			CalcDetail=&CalcDetailR;
		}

		double	MaxD=0;
		int	hAlignedDx=0;
		int	hAlignedDy=0;
		int	PicoShift=RThr->PicoShift;

		double	d;
		for(int L=5;L<(PicoShift+pBase->SearchDot+4);L+=2){
			int	dy=-L;
			int	dx;
			for(dx=-L;dx<L;dx+=2){
				if(0<=(x1+dx) && (x2+dx)<DotPerLine && 0<=(y1+dy) && (y2+dy)<MaxLines){
					d=CalcFirst->CoefCalc(*LMasterBuff ,*LMasterBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
			dx=L;
			for(dy=-L;dy<L;dy+=2){
				if(0<=(x1+dx) && (x2+dx)<DotPerLine && 0<=(y1+dy) && (y2+dy)<MaxLines){
					d=CalcFirst->CoefCalc(*LMasterBuff ,*LMasterBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
			dy=L;
			for(dx=L;dx>-L;dx-=2){
				if(0<=(x1+dx) && (x2+dx)<DotPerLine && 0<=(y1+dy) && (y2+dy)<MaxLines){
					d=CalcFirst->CoefCalc(*LMasterBuff ,*LMasterBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
			dx=-L;
			for(dy=L;dy>-L;dy-=2){
				if(0<=(x1+dx) && (x2+dx)<DotPerLine && 0<=(y1+dy) && (y2+dy)<MaxLines){
					d=CalcFirst->CoefCalc(*LMasterBuff ,*LMasterBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
		}
		MaxD=0;
		for(int ky=-1;ky<=1;ky++){
			for(int kx=-1;kx<=1;kx++){
				if(0<=(x1+hAlignedDx+kx) && (x2+hAlignedDx+kx)<DotPerLine && 0<=(y1+hAlignedDy+ky) && (y2+hAlignedDy+ky)<MaxLines){
					d=CalcDetail->CoefCalc(*LMasterBuff ,*LMasterBuff ,TransArea,hAlignedDx+kx ,hAlignedDy+ky);
					if(MaxD<d){
						MaxD=d;
					}
				}
			}
		}

		if(MaxD>RThr->CompletelyMatchingRate){
			for(ClusteredPicoDim *fm=Parent->CPicoDim.GetFirst();fm!=NULL;fm=fm->GetNext()){
				if(fm->PicoDimXNumb>2 && fm->PicoDimYNumb>2){
					Effective=false;
					break;
				}
			}
		}
	}
	DeleteMatrixBuff(Map,YLen);

	MatchResult=0;
	ShiftX=0;
	ShiftY=0;
	ConnectedPico[0]=NULL;
	ConnectedPico[1]=NULL;
	return true;
}

void	AutoAlignmentInPico::MakeXYIndex(void)
{
	ImagePointerContainer Images;
	AlgorithmInPageRoot	*PPage=Parent->GetParentInPage();
	PPage->GetDataInPage()->GetMasterImages(Images);
	AutoAlignmentBase	*ABase=(AutoAlignmentBase *)PPage->GetParentBase();

	if(GetLayerNumb()>=3){
		ImagePointerList *RBuff=Images.GetItem(0);
		ImagePointerList *GBuff=Images.GetItem(1);
		ImagePointerList *BBuff=Images.GetItem(2);

		IndexDataR.Initial(TransArea,*RBuff->GetImage(),ABase->MinTransDot);
		IndexDataG.Initial(TransArea,*GBuff->GetImage(),ABase->MinTransDot);
		IndexDataB.Initial(TransArea,*BBuff->GetImage(),ABase->MinTransDot);
	}
	else if(GetLayerNumb()==1){
		ImagePointerList *RBuff=Images.GetItem(0);
		IndexDataR.Initial(TransArea,*RBuff->GetImage(),ABase->MinTransDot);
	}
}

bool	AutoAlignmentInPico::ExecuteStartByInspection(void)
{
	ConnectedPico[0]=NULL;
	ConnectedPico[1]=NULL;
	MatchResult=0;
	NeedAdjust=true;

	return true;
}


bool	AutoAlignmentInPico::ExecuteAlignment(double Dx, double Dy,double Theta)
{
	if(Effective==false){
		return false;
	}
	if(AutoAXn==Xn && AutoAYn==Yn){
		AutoADbg++;
	}
	const	AutoAlignmentThreshold	*RThr=Parent->GetThresholdR(NULL);
	int	PicoShift=RThr->PicoShift;

	MatchResult=0;

	double d=0;
	int	mx,my;
	if(GetLayerNumb()>=3){
		AlgorithmInPageRoot	*PPage=Parent->GetParentInPage();
		ImagePointerContainer MasterImages;
		PPage->GetDataInPage()->GetMasterImages(MasterImages);
		ImageBuffer	*RMasterBuff=MasterImages.GetItem(0)->GetImage();
		ImageBuffer	*GMasterBuff=MasterImages.GetItem(1)->GetImage();
		ImageBuffer	*BMasterBuff=MasterImages.GetItem(2)->GetImage();
		ImagePointerContainer TargetImages;
		PPage->GetDataInPage()->GetTargetImages(TargetImages);
		ImageBuffer *RTargetBuff=TargetImages.GetItem(0)->GetImage();
		ImageBuffer *GTargetBuff=TargetImages.GetItem(1)->GetImage();
		ImageBuffer *BTargetBuff=TargetImages.GetItem(2)->GetImage();

		d=ExecuteAlignmentIndex(Dx, Dy
						, RMasterBuff,GMasterBuff,BMasterBuff
						, RTargetBuff,GTargetBuff,BTargetBuff
						,mx,my);
		if(d>RThr->CompletelyMatchingRate){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
		if(d<-10.0){
			return true;
		}	

		d=ExecuteAlignmentInside3(mx, my
									,1
									,RThr->CompletelyMatchingRate
									,RMasterBuff,GMasterBuff,BMasterBuff
									,RTargetBuff,GTargetBuff,BTargetBuff);
		if(d>=0){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
		d=ExecuteAlignmentInside3(mx, my
									,2
									,RThr->AdptedMatchingRate
									,RMasterBuff,GMasterBuff,BMasterBuff
									,RTargetBuff,GTargetBuff,BTargetBuff);
		if(d>=0){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
	}
	else if(GetLayerNumb()==1){
		AlgorithmInPageRoot	*PPage=Parent->GetParentInPage();
		ImagePointerContainer MasterImages;
		PPage->GetDataInPage()->GetMasterImages(MasterImages);
		ImageBuffer	*RMasterBuff=MasterImages.GetItem(0)->GetImage();
		ImagePointerContainer TargetImages;
		PPage->GetDataInPage()->GetTargetImages(TargetImages);
		ImageBuffer *RTargetBuff=TargetImages.GetItem(0)->GetImage();

		d=ExecuteAlignmentIndex(Dx, Dy
						, RMasterBuff,RMasterBuff,RMasterBuff
						, RTargetBuff,RTargetBuff,RTargetBuff
						,mx,my);
		if(d>RThr->CompletelyMatchingRate){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
		if(d<-10.0){
			return true;
		}	

		d=ExecuteAlignmentInside3(mx, my
									,1
									,RThr->CompletelyMatchingRate
									,RMasterBuff,RMasterBuff,RMasterBuff
									,RTargetBuff,RTargetBuff,RTargetBuff);
		if(d>=0){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
		d=ExecuteAlignmentInside3(mx, my
									,2
									,RThr->AdptedMatchingRate
									,RMasterBuff,RMasterBuff,RMasterBuff
									,RTargetBuff,RTargetBuff,RTargetBuff);
		if(d>=0){
			ShiftX=mx;
			ShiftY=my;
			MatchResult=d;
			return true;
		}
	}

	return true;
}


double	AutoAlignmentInPico::ExecuteAlignmentIndex(int Dx, int Dy
												  ,ImageBuffer *RMasterBuff
												  ,ImageBuffer *GMasterBuff
												  ,ImageBuffer *BMasterBuff
												  ,ImageBuffer *RTargetBuff
												  ,ImageBuffer *GTargetBuff
												  ,ImageBuffer *BTargetBuff
												  ,int &ResMx,int &ResMy)
{
	double	MaxD=0;
	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();
	int	DotPerLine	=Parent->GetDotPerLine();
	int	MaxLines	=Parent->GetMaxLines();

	CalcedIndexData	*CalcPointer=NULL;
	ImageBuffer *MasterBuffPointer=NULL;
	ImageBuffer *TargetBuffPointer=NULL;
	if(SelectFirst==0){
		CalcPointer=&IndexDataR;
		MasterBuffPointer=RMasterBuff;
		TargetBuffPointer=RTargetBuff;
	}
	else if(SelectFirst==1){
		CalcPointer=&IndexDataG;
		MasterBuffPointer=GMasterBuff;
		TargetBuffPointer=GTargetBuff;
	}
	else if(SelectFirst==2){
		CalcPointer=&IndexDataB;
		MasterBuffPointer=BMasterBuff;
		TargetBuffPointer=BTargetBuff;
	}
	int	PicoShift=Parent->GetThresholdR(NULL)->PicoShift;
	double	MaxM=0.0;

	int		Px,Py;

	for(int dy=Dy-PicoShift*3;dy<=Dy+PicoShift*3;dy+=2){
		for(int dx=Dx-PicoShift*3;dx<=Dx+PicoShift*3;dx+=2){
			double	d=CalcPointer->CoefCalc(dx ,dy
											,*MasterBuffPointer,*TargetBuffPointer);
			if(d<-1.0){
				return -100.0;
			}
			if(d>MaxM){
				MaxM=d;
				Px=dx;
				Py=dy;
			}
		}
	}

	for(int dy=Dy-PicoShift*3+1;dy<=Dy+PicoShift*3-1;dy+=2){
		for(int dx=Dx-PicoShift*3+1;dx<=Dx+PicoShift*3-1;dx+=2){
			double	d=CalcPointer->CoefCalc(dx ,dy
											,*MasterBuffPointer,*TargetBuffPointer);
			if(d>MaxM){
				MaxM=d;
				Px=dx;
				Py=dy;
			}
		}
	}

	MaxM=0.0;
	for(int dy=Py-1;dy<=Py+1;dy++){
		for(int dx=Px-1;dx<=Px+1;dx++){
			double	d=CalcPointer->CoefCalc(dx ,dy
											,*MasterBuffPointer,*TargetBuffPointer);
			if(d>MaxM){
				MaxM=d;
				ResMx=dx;
				ResMy=dy;
			}
		}
	}
	return MaxM;
}


double	AutoAlignmentInPico::ExecuteAlignmentInside2(double Dx, double Dy,double Theta 
													,int PLen ,int Step
													,double CompletelyMatchingRate
													,ImageBuffer *RMasterBuff
													,ImageBuffer *GMasterBuff
													,ImageBuffer *BMasterBuff
													,ImageBuffer *RTargetBuff
													,ImageBuffer *GTargetBuff
													,ImageBuffer *BTargetBuff
													,double &MaxRoughMatch,int &ResMx,int &ResMy)
{
	double	MaxD=0;
	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();
	int	DotPerLine	=Parent->GetDotPerLine();
	int	MaxLines	=Parent->GetMaxLines();

	CalcedData	*CalfPointer=NULL;
	ImageBuffer *MasterBuffPointer=NULL;
	ImageBuffer *TargetBuffPointer=NULL;
	if(SelectFirst==0){
		CalfPointer=&CalcFirstR;
		MasterBuffPointer=RMasterBuff;
		TargetBuffPointer=RTargetBuff;
	}
	else if(SelectFirst==1){
		CalfPointer=&CalcFirstG;
		MasterBuffPointer=GMasterBuff;
		TargetBuffPointer=GTargetBuff;
	}
	else if(SelectFirst==2){
		CalfPointer=&CalcFirstB;
		MasterBuffPointer=BMasterBuff;
		TargetBuffPointer=BTargetBuff;
	}

	int	mx,my;

	double	d,r;
	MaxD=0;

	mx=Dx-PLen;
	my=Dy-PLen;
	for(;mx<=Dx+PLen;mx+=Step){
		if(0<=(MinX+mx) && (MaxX+mx)<DotPerLine && 0<=(MinY+my) && (MaxY+my)<MaxLines){
			d=CalfPointer->CoefCalc(*MasterBuffPointer ,*TargetBuffPointer ,TransArea,mx ,my);
			if(d>=CompletelyMatchingRate){
				int	LStep=Step-1;
				r=ExecuteAlignmentInside3(mx, my
										,LStep
										,CompletelyMatchingRate
										,RMasterBuff,GMasterBuff,BMasterBuff
										,RTargetBuff,GTargetBuff,BTargetBuff);
				if(r>=CompletelyMatchingRate){
					return r;
				}
				if(MatchResult<r){
					MatchResult=r;
				}
			}
			if(MaxRoughMatch<d){
				MaxRoughMatch=d;
				ResMx=mx;
				ResMy=my;
			}
		}
	}
	mx=Dx+PLen;
	my=Dy-PLen;
	for(;my<=Dy+PLen;my+=Step){
		if(0<=(MinX+mx) && (MaxX+mx)<DotPerLine && 0<=(MinY+my) && (MaxY+my)<MaxLines){
			d=CalfPointer->CoefCalc(*MasterBuffPointer ,*TargetBuffPointer ,TransArea,mx ,my);
			if(d>=CompletelyMatchingRate){
				int	LStep=Step-1;
				r=ExecuteAlignmentInside3(mx, my
										,LStep
										,CompletelyMatchingRate
										,RMasterBuff,GMasterBuff,BMasterBuff
										,RTargetBuff,GTargetBuff,BTargetBuff);
				if(r>=CompletelyMatchingRate){
					return r;
				}
				if(MatchResult<r){
					MatchResult=r;
				}
			}
			if(MaxRoughMatch<d){
				MaxRoughMatch=d;
				ResMx=mx;
				ResMy=my;
			}
		}
	}
	mx=Dx+PLen;
	my=Dy+PLen;
	for(;mx>=Dx+PLen;mx-=Step){
		if(0<=(MinX+mx) && (MaxX+mx)<DotPerLine && 0<=(MinY+my) && (MaxY+my)<MaxLines){
			d=CalfPointer->CoefCalc(*MasterBuffPointer ,*TargetBuffPointer ,TransArea,mx ,my);
			if(d>=CompletelyMatchingRate){
				int	LStep=Step-1;
				r=ExecuteAlignmentInside3(mx, my
										,LStep
										,CompletelyMatchingRate
										,RMasterBuff,GMasterBuff,BMasterBuff
										,RTargetBuff,GTargetBuff,BTargetBuff);
				if(r>=CompletelyMatchingRate){
					return r;
				}
				if(MatchResult<r){
					MatchResult=r;
				}
			}
			if(MaxRoughMatch<d){
				MaxRoughMatch=d;
				ResMx=mx;
				ResMy=my;
			}
		}
	}
	mx=Dx-PLen;
	my=Dy+PLen;
	for(;my>=Dy+PLen;my-=Step){
		if(0<=(MinX+mx) && (MaxX+mx)<DotPerLine && 0<=(MinY+my) && (MaxY+my)<MaxLines){
			d=CalfPointer->CoefCalc(*MasterBuffPointer ,*TargetBuffPointer ,TransArea,mx ,my);
			if(d>=CompletelyMatchingRate){
				int	LStep=Step-1;
				r=ExecuteAlignmentInside3(mx, my
										,LStep
										,CompletelyMatchingRate
										,RMasterBuff,GMasterBuff,BMasterBuff
										,RTargetBuff,GTargetBuff,BTargetBuff);
				if(r>=CompletelyMatchingRate){
					return r;
				}
				if(MatchResult<r){
					MatchResult=r;
				}
			}
			if(MaxRoughMatch<d){
				MaxRoughMatch=d;
				ResMx=mx;
				ResMy=my;
			}
		}
	}

	return -1.0;
}

double	AutoAlignmentInPico::ExecuteAlignmentInside3(double mx, double my
													,int	LStep
													,double CompletelyMatchingRate
													,ImageBuffer *RMasterBuff
													,ImageBuffer *GMasterBuff
													,ImageBuffer *BMasterBuff
													,ImageBuffer *RTargetBuff
													,ImageBuffer *GTargetBuff
													,ImageBuffer *BTargetBuff)
{
	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();
	int	DotPerLine	=Parent->GetDotPerLine();
	int	MaxLines	=Parent->GetMaxLines();

	double	fMatchResult=0;
	ShiftX=0;
	ShiftY=0;
	double	d;
	if(GetLayerNumb()>=3){
		for(int dy=my-LStep;dy<=my+LStep;dy++){
			for(int dx=mx-LStep;dx<=mx+LStep;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					d=CalcDetailR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy)
					 *CalcDetailG.CoefCalc(*GMasterBuff ,*GTargetBuff ,TransArea,dx ,dy)
					 *CalcDetailB.CoefCalc(*BMasterBuff ,*BTargetBuff ,TransArea,dx ,dy);
					if(fMatchResult<d){
						fMatchResult=d;
						ShiftX=dx;
						ShiftY=dy;
					}
				}
			}
		}
	}
	else if(GetLayerNumb()==1){
		for(int dy=my-LStep;dy<=my+LStep;dy++){
			for(int dx=mx-LStep;dx<=mx+LStep;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					d=CalcDetailR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					d=d*d*d;
					if(fMatchResult<d){
						fMatchResult=d;
						ShiftX=dx;
						ShiftY=dy;
					}
				}
			}
		}
	}
	if(fMatchResult>=CompletelyMatchingRate){
		return fMatchResult;
	}
	return -1.0;
}

double	AutoAlignmentInPico::ExecuteAlignmentInside(double Dx, double Dy,double Theta 
													,int	PicoShift
													,int turn)
{
	AlgorithmInPageRoot	*PPage=Parent->GetParentInPage();
	ImagePointerContainer MasterImages;
	double	MaxD=0;
	int	hAlignedDx=0;
	int	hAlignedDy=0;
	int	MinX=Area.GetMinX();
	int	MinY=Area.GetMinY();
	int	MaxX=Area.GetMaxX();
	int	MaxY=Area.GetMaxY();
	int	DotPerLine	=Parent->GetDotPerLine();
	int	MaxLines	=Parent->GetMaxLines();
	int	tAlignedDx;
	int	tAlignedDy;

	MaxD=0;
	double	fMatchResult=0;
	const	AutoAlignmentThreshold	*RThr=Parent->GetThresholdR(NULL);

	if(GetLayerNumb()>=3){
		PPage->GetDataInPage()->GetMasterImages(MasterImages);
		ImageBuffer	*RMasterBuff=MasterImages.GetItem(0)->GetImage();
		ImageBuffer	*GMasterBuff=MasterImages.GetItem(1)->GetImage();
		ImageBuffer	*BMasterBuff=MasterImages.GetItem(2)->GetImage();
		ImagePointerContainer TargetImages;
		PPage->GetDataInPage()->GetTargetImages(TargetImages);
		ImageBuffer *RTargetBuff=TargetImages.GetItem(0)->GetImage();
		ImageBuffer *GTargetBuff=TargetImages.GetItem(1)->GetImage();
		ImageBuffer *BTargetBuff=TargetImages.GetItem(2)->GetImage();

		for(int dy=Dy-PicoShift;dy<=Dy+PicoShift;dy+=2){
			for(int dx=Dx-PicoShift;dx<=Dx+PicoShift;dx+=2){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d=0;
					if(SelectFirst==0){
						d=CalcFirstR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					}
					else if(SelectFirst==1){
						d=CalcFirstG.CoefCalc(*GMasterBuff ,*GTargetBuff ,TransArea,dx ,dy);
					}
					else if(SelectFirst==2){
						d=CalcFirstB.CoefCalc(*BMasterBuff ,*BTargetBuff ,TransArea,dx ,dy);
					}
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
		}
		MaxD=0;
		tAlignedDx=hAlignedDx;
		tAlignedDy=hAlignedDy;

		for(int dy=hAlignedDy-1;dy<=hAlignedDy+1;dy++){
			for(int dx=hAlignedDx-1;dx<=hAlignedDx+1;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d=0;
					if(SelectFirst==0){
						d=CalcFirstR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					}
					else if(SelectFirst==1){
						d=CalcFirstG.CoefCalc(*GMasterBuff ,*GTargetBuff ,TransArea,dx ,dy);
					}
					else if(SelectFirst==2){
						d=CalcFirstB.CoefCalc(*BMasterBuff ,*BTargetBuff ,TransArea,dx ,dy);
					}
					if(MaxD<d){
						MaxD=d;
						tAlignedDx=dx;
						tAlignedDy=dy;
					}
				}
			}
		}
		if(turn==0){
			if(MaxD<RThr->CompletelyMatchingRate){
				return 0;
			}
		}
		ShiftX=0;
		ShiftY=0;
		for(int dy=tAlignedDy-1;dy<=tAlignedDy+1;dy++){
			for(int dx=tAlignedDx-1;dx<=tAlignedDx+1;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d;
					d=CalcDetailR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy)
					 *CalcDetailG.CoefCalc(*GMasterBuff ,*GTargetBuff ,TransArea,dx ,dy)
					 *CalcDetailB.CoefCalc(*BMasterBuff ,*BTargetBuff ,TransArea,dx ,dy);
					if(fMatchResult<d){
						fMatchResult=d;
						ShiftX=dx;
						ShiftY=dy;
					}
				}
			}	
		}
	}
	else if(GetLayerNumb()==1){
		PPage->GetDataInPage()->GetMasterImages(MasterImages);
		ImageBuffer	*RMasterBuff=MasterImages.GetItem(0)->GetImage();
		ImagePointerContainer TargetImages;
		PPage->GetDataInPage()->GetTargetImages(TargetImages);
		ImageBuffer *RTargetBuff=TargetImages.GetItem(0)->GetImage();

		for(int dy=Dy-PicoShift;dy<=Dy+PicoShift;dy+=2){
			for(int dx=Dx-PicoShift;dx<=Dx+PicoShift;dx+=2){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d=CalcFirstR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						hAlignedDx=dx;
						hAlignedDy=dy;
					}
				}
			}
		}
		MaxD=0;
		tAlignedDx=hAlignedDx;
		tAlignedDy=hAlignedDy;

		for(int dy=hAlignedDy-1;dy<=hAlignedDy+1;dy++){
			for(int dx=hAlignedDx-1;dx<=hAlignedDx+1;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d=CalcFirstR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					if(MaxD<d){
						MaxD=d;
						tAlignedDx=dx;
						tAlignedDy=dy;
					}
				}
			}
		}
		if(turn==0){
			if(MaxD<RThr->CompletelyMatchingRate){
				return 0;
			}
		}

		ShiftX=0;
		ShiftY=0;
		for(int dy=tAlignedDy-1;dy<=tAlignedDy+1;dy++){
			for(int dx=tAlignedDx-1;dx<=tAlignedDx+1;dx++){
				if(0<=(MinX+dx) && (MaxX+dx)<DotPerLine && 0<=(MinY+dy) && (MaxY+dy)<MaxLines){
					double	d;
					d=CalcDetailR.CoefCalc(*RMasterBuff ,*RTargetBuff ,TransArea,dx ,dy);
					d=d*d*d;
					if(fMatchResult<d){
						fMatchResult=d;
						ShiftX=dx;
						ShiftY=dy;
					}
				}
			}
		}
	}

	return fMatchResult;
}



void	AutoAlignmentInPico::CalcFromSurround(void)
{
	//ãﬂñTÇÃÇQÇ¬ÇÃÇoÇhÇbÇnÇíTÇµÇƒåvéZÇ∏ÇÈ
	
	ShiftX=0;
	ShiftY=0;
	AutoAlignmentInPico	*Surround[100];
	int		SurroundCount=0;
	int	MaxL=max(DimPoint->PicoDimXNumb,DimPoint->PicoDimYNumb);
	for(int L=1;L<MaxL;L++){
		//SurroundCount=0;
		int	yn=Yn-L;
		int	xn;
		for(xn=Xn-L;xn<Xn+L;xn++){
			if(0<=xn && xn<DimPoint->PicoDimXNumb && 0<=yn && yn<DimPoint->PicoDimYNumb){
				AutoAlignmentInPico	*P=DimPoint->PicoDim[yn][xn];
				if(P->Effective==true && P->Adopted==true){
					Surround[SurroundCount]=P;
					SurroundCount++;
				}
			}
		}
		xn=Xn+L;
		for(yn=Yn-L;yn<Yn+L;yn++){
			if(0<=xn && xn<DimPoint->PicoDimXNumb && 0<=yn && yn<DimPoint->PicoDimYNumb){
				AutoAlignmentInPico	*P=DimPoint->PicoDim[yn][xn];
				if(P->Effective==true && P->Adopted==true){
					Surround[SurroundCount]=P;
					SurroundCount++;
				}
			}
		}
		yn=Yn+L;
		for(xn=Xn+L;xn>Xn-L;xn--){
			if(0<=xn && xn<DimPoint->PicoDimXNumb && 0<=yn && yn<DimPoint->PicoDimYNumb){
				AutoAlignmentInPico	*P=DimPoint->PicoDim[yn][xn];
				if(P->Effective==true && P->Adopted==true){
					Surround[SurroundCount]=P;
					SurroundCount++;
				}
			}
		}
		xn=Xn-L;
		for(yn=Yn+L;yn>Yn-L;yn--){
			if(0<=xn && xn<DimPoint->PicoDimXNumb && 0<=yn && yn<DimPoint->PicoDimYNumb){
				AutoAlignmentInPico	*P=DimPoint->PicoDim[yn][xn];
				if(P->Effective==true && P->Adopted==true){
					Surround[SurroundCount]=P;
					SurroundCount++;
				}
			}
		}
		if(SurroundCount>=3){
			int	dPx=0;
			int	dPy=0;
			for(int i=0;i<SurroundCount;i++){
				dPx	+=Surround[i]->ShiftX;
				dPy	+=Surround[i]->ShiftY;
			}
			ConnectedPico[0]=NULL;
			ConnectedPico[1]=NULL;
			ShiftX=((double)dPx)/((double)SurroundCount);
			ShiftY=((double)dPy)/((double)SurroundCount);
			if(L==1){
				NeedAdjust=false;
			}
			break;
		}
		else if(SurroundCount>=2){
			ConnectedPico[0]=Surround[0];
			ConnectedPico[1]=Surround[1];

			int	Px	=Surround[0]->Xn;
			int	Py	=Surround[0]->Yn;
			int	dPx	=Surround[0]->ShiftX;
			int	dPy	=Surround[0]->ShiftY;
			int	Qx	=Surround[1]->Xn;
			int	Qy	=Surround[1]->Yn;
			int	dQx	=Surround[1]->ShiftX;
			int	dQy	=Surround[1]->ShiftY;
			int	Rx	=Xn;
			int	Ry	=Yn;

			int	PQx=Px-Qx;
			int	PQy=Py-Qy;
			int	dPQx=dPx-dQx;
			int	dPQy=dPy-dQy;

			int	M=PQx*PQx + PQy*PQy;
			if(M!=0){
				double	a=((double)(dPQx*PQx+dPQy*PQy))/((double)M);
				double	b=((double)(dPQx*PQy-dPQy*PQx))/((double)M);
				double	c=dPx-a*Px-b*Py;
				double	d=dPy+b*Px-a*Py;
				ShiftX= a*Rx+b*Ry+c;
				ShiftY=-b*Rx+a*Ry+d;
			}
			else{
				int	Lx1=CenterX-Surround[0]->CenterX;
				int	Ly1=CenterY-Surround[0]->CenterY;
				int	Lx2=CenterX-Surround[1]->CenterX;
				int	Ly2=CenterY-Surround[1]->CenterY;
				if((Lx2+Lx1)!=0){
					ShiftX=(Lx2*Surround[0]->ShiftX + Lx1*Surround[1]->ShiftX)/(Lx2+Lx1);
				}
				else{
					ShiftX=Surround[0]->ShiftX;
				}
				if((Ly2+Ly1)!=0){
					ShiftY=(Ly2*Surround[0]->ShiftY + Ly1*Surround[1]->ShiftY)/(Ly2+Ly1);
				}
				else{
					ShiftY=Surround[0]->ShiftY;
				}
			}
			break;
		}
	}
}



void	AutoAlignmentInPico::PutShiftMapAll(char **ResultPerPixXFromTarget,
											char **ResultPerPixYFromTarget,
											char **ResultPerPixXFromMaster,
											char **ResultPerPixYFromMaster,
											int XLen,
											int YLen)
{
	int	N=Area.GetFLineLen();
	char	Sx=(char)RInt(ShiftX);
	char	Sy=(char)RInt(ShiftY);
	for(int i=0;i<N;i++){
		int	Y	=Area.GetFLineAbsY(i);
		int	X	=Area.GetFLineLeftX(i);
		int	Numb=Area.GetFLineNumb(i);

		if(Y<0 || Y>=Parent->GetMaxLines()){
			continue;
		}
		if(X<0 || X>=Parent->GetDotPerLine()){
			continue;
		}

		char *iResultPerPixXFromMaster=ResultPerPixXFromMaster[Y];
		char *iResultPerPixYFromMaster=ResultPerPixYFromMaster[Y];
		memset(&iResultPerPixXFromMaster[X],Sx,Numb);
		memset(&iResultPerPixYFromMaster[X],Sy,Numb);

		int	y=Y+Sy;
		if(y<0 || YLen<=y){
			continue;
		}
		int	x1=X+Sx;
		int	x2=X+Numb+Sx;
		if(x1<0){
			x1=0;
		}
		if(x2>XLen){
			x2=XLen;
		}
		int	numb=x2-x1;
		if(numb>0){
			char *iResultPerPixXFromTarget=ResultPerPixXFromTarget[y];
			char *iResultPerPixYFromTarget=ResultPerPixYFromTarget[y];
			memset(&iResultPerPixXFromTarget[x1],-Sx,numb);
			memset(&iResultPerPixYFromTarget[x1],-Sy,numb);
		}
	}
}
void	AutoAlignmentInPico::PutShiftMap(char **ResultPerPixXFromTarget,
										 char **ResultPerPixYFromTarget,
										 char **ResultPerPixXFromMaster,
										 char **ResultPerPixYFromMaster,
										 char **ResultRelativeXFromTarget,
										 char **ResultRelativeYFromTarget,
										 char **ResultRelativeXFromMaster,
										 char **ResultRelativeYFromMaster,
										 int XLen,
										 int YLen)
{
	int	N=PickupArea.GetFLineLen();
	char	Sx=(char)RInt(ShiftX);
	char	Sy=(char)RInt(ShiftY);
	for(int i=0;i<N;i++){
		int	Y	=PickupArea.GetFLineAbsY(i);
		int	X	=PickupArea.GetFLineLeftX(i);
		int	Numb=PickupArea.GetFLineNumb(i);

		if(Y<0 || Y>=Parent->GetMaxLines()){
			continue;
		}
		if(X<0 || X>=Parent->GetDotPerLine()){
			continue;
		}

		char *iResultPerPixXFromMaster=ResultPerPixXFromMaster[Y];
		char *iResultPerPixYFromMaster=ResultPerPixYFromMaster[Y];
		char *iResultRelativeXFromMaster=ResultRelativeXFromMaster[Y];
		char *iResultRelativeYFromMaster=ResultRelativeYFromMaster[Y];
		memset(&iResultPerPixXFromMaster[X],Sx,Numb);
		memset(&iResultPerPixYFromMaster[X],Sy,Numb);

		char	RelativeShiftX=0;
		char	RelativeShiftY=0;
		if(BasePointer!=NULL){
			RelativeShiftX=(char)RInt(ShiftX-BasePointer->ShiftX);
			RelativeShiftY=(char)RInt(ShiftY-BasePointer->ShiftY);
			memset(&iResultRelativeXFromMaster[X],RelativeShiftX,Numb);
			memset(&iResultRelativeYFromMaster[X],RelativeShiftY,Numb);
		}
		int	y=Y+Sy;
		if(y<0 || YLen<=y){
			continue;
		}
		int	x1=X+Sx;
		int	x2=X+Numb+Sx;
		if(x1<0){
			x1=0;
		}
		if(x2>XLen){
			x2=XLen;
		}
		int	numb=x2-x1;
		if(numb>0){
			char *iResultPerPixXFromTarget=ResultPerPixXFromTarget[y];
			char *iResultPerPixYFromTarget=ResultPerPixYFromTarget[y];
			memset(&iResultPerPixXFromTarget[x1],-Sx,numb);
			memset(&iResultPerPixYFromTarget[x1],-Sy,numb);

			if(BasePointer!=NULL){
				char *iResultRelativeXFromTarget=ResultRelativeXFromTarget[y];
				char *iResultRelativeYFromTarget=ResultRelativeYFromTarget[y];
				memset(&iResultRelativeXFromTarget[x1],-RelativeShiftX,numb);
				memset(&iResultRelativeYFromTarget[x1],-RelativeShiftY,numb);
			}
		}
	}
}

void	AutoAlignmentInPico::AvoidOverlap(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)Parent->GetParentInPage();
	int	iShiftX=ShiftX;
	int	iShiftY=ShiftY;
	PickupAreaTarget.MoveToNoClip(iShiftX,iShiftY);

	int	N;
	N=OMasterArea.GetFLineLen();
	//MasterâÊëúè„Ç≈ÇÕPickupAreaóÃàÊè„Ç…Ç»Ç¢ç¿ïWÇ™Ç∏ÇÍÇÈÇ∆Targetè„Ç≈PickupAreaè„Ç…Ç≠ÇÈÇ∆Ç´ÅAï‚ê≥Ç∑ÇÈ
	for(int i=0;i<N;i++){
		int	MasterY	=OMasterArea.GetFLineAbsY(i);
		int	X		=OMasterArea.GetFLineLeftX(i);
		int	Numb	=OMasterArea.GetFLineNumb(i);

		if(MasterY<0 || MasterY>=Parent->GetMaxLines()){
			continue;
		}

		for(int n=0;n<Numb;n++){
			int	MasterX=X+n;
			if(MasterX<0 || MasterX>=Parent->GetDotPerLine()){
				continue;
			}
			int	MasterShiftX=PPage->GetShiftXFromMaster(MasterX,MasterY);
			int	MasterShiftY=PPage->GetShiftYFromMaster(MasterX,MasterY);
			if(PickupAreaTarget.IsInclude(MasterX+MasterShiftX,MasterY+MasterShiftY)==true){
				double	Len=hypot(MasterShiftX,MasterShiftY);
				if(Len==0.0){
					Len=1.0;
				}
				int ResultX ,ResultY;
				if(AvoidOverlapMaster( MasterX ,MasterY 
									,MasterShiftX ,MasterShiftY 
									,Len ,ResultX ,ResultY)==true){
					PPage->ResultRelativeXFromMaster[MasterY][MasterX] +=ResultX-PPage->ResultPerPixXFromMaster[MasterY][MasterX];
					PPage->ResultRelativeYFromMaster[MasterY][MasterX] +=ResultY-PPage->ResultPerPixYFromMaster[MasterY][MasterX];
					PPage->ResultPerPixXFromMaster[MasterY][MasterX]=ResultX;
					PPage->ResultPerPixYFromMaster[MasterY][MasterX]=ResultY;
				}
				else{
					PPage->ResultPerPixXFromMaster[MasterY][MasterX]=0;
					PPage->ResultPerPixYFromMaster[MasterY][MasterX]=0;
					PPage->ResultRelativeXFromMaster[MasterY][MasterX]=0;
					PPage->ResultRelativeYFromMaster[MasterY][MasterX]=0;
				}
			}
		}
	}
	//TargetâÊëúè„Ç≈ÇÕPickupAreaóÃàÊè„Ç…Ç»Ç¢ç¿ïWÇ™Ç∏ÇÍÇñﬂÇ∑Ç∆Masterè„Ç≈PickupAreaè„Ç…Ç≠ÇÈÇ∆Ç´ÅAï‚ê≥Ç∑ÇÈ
	N=OTargetArea.GetFLineLen();
	for(int i=0;i<N;i++){
		int	TargetY	=OTargetArea.GetFLineAbsY(i);
		int	X		=OTargetArea.GetFLineLeftX(i);
		int	Numb	=OTargetArea.GetFLineNumb(i);

		if(TargetY<0 || TargetY>=Parent->GetMaxLines()){
			continue;
		}

		for(int n=0;n<Numb;n++){
			int	TargetX=X+n;
			if(TargetX<0 || TargetX>=Parent->GetDotPerLine()){
				continue;
			}
			int	TargetShiftX=PPage->GetShiftXFromTarget(TargetX,TargetY);
			int	TargetShiftY=PPage->GetShiftYFromTarget(TargetX,TargetY);
			if(PickupArea.IsInclude(TargetX+TargetShiftX,TargetY+TargetShiftY)==true){
				double	Len=hypot(TargetShiftX,TargetShiftY);
				if(Len==0.0){
					Len=1.0;
				}
				int	ResultX ,ResultY;
				if(AvoidOverlapTarget( TargetX ,TargetY 
								,TargetShiftX ,TargetShiftY 
								,Len ,ResultX ,ResultY)==true){
					PPage->ResultRelativeXFromTarget[TargetY][TargetX] += ResultX-PPage->ResultPerPixXFromTarget[TargetY][TargetX];
					PPage->ResultRelativeYFromTarget[TargetY][TargetX] += ResultY-PPage->ResultPerPixYFromTarget[TargetY][TargetX];
					PPage->ResultPerPixXFromTarget[TargetY][TargetX]=ResultX;
					PPage->ResultPerPixYFromTarget[TargetY][TargetX]=ResultY;
				}
				else{
					PPage->ResultPerPixXFromTarget[TargetY][TargetX]=0;
					PPage->ResultPerPixYFromTarget[TargetY][TargetX]=0;
					PPage->ResultRelativeXFromTarget[TargetY][TargetX]=0;
					PPage->ResultRelativeYFromTarget[TargetY][TargetX]=0;
				}
			}
		}
	}
	PickupAreaTarget.MoveToNoClip(-iShiftX,-iShiftY);
}

bool	AutoAlignmentInPico::AvoidOverlapMaster( int MasterX ,int MasterY 
												,int MasterShiftX ,int MasterShiftY 
												,double Len ,int &ResultX ,int &ResultY)
{
	double	XL=((double)MasterShiftX)/Len;
	double	YL=((double)MasterShiftY)/Len;
	for(double H=Len-1.0;H>=0;H-=1.0){
		ResultX=(int)(XL*H);
		ResultY=(int)(YL*H);
		if(PickupAreaTarget.IsInclude(MasterX+ResultX,MasterY+ResultY)==false){
			return true;
		}
	}
	for(int L=1;L<100;L++){
		ResultY=-L;
		for(ResultX=-L;ResultX<L;ResultX++){
			if(PickupAreaTarget.IsInclude(MasterX+ResultX,MasterY+ResultY)==false){
				return true;
			}
		}
		ResultX=L;
		for(ResultY=-L;ResultY<L;ResultY++){
			if(PickupAreaTarget.IsInclude(MasterX+ResultX,MasterY+ResultY)==false){
				return true;
			}
		}
		ResultY=L;
		for(ResultX=L;ResultX>-L;ResultX--){
			if(PickupAreaTarget.IsInclude(MasterX+ResultX,MasterY+ResultY)==false){
				return true;
			}
		}
		ResultX=-L;
		for(ResultY=L;ResultY>-L;ResultY--){
			if(PickupAreaTarget.IsInclude(MasterX+ResultX,MasterY+ResultY)==false){
				return true;
			}
		}
	}
	return false;
}
bool	AutoAlignmentInPico::AvoidOverlapTarget( int TargetX ,int TargetY 
												,int TargetShiftX ,int TargetShiftY 
												,double Len ,int &ResultX ,int &ResultY)
{
	double	XL=((double)TargetShiftX)/Len;
	double	YL=((double)TargetShiftY)/Len;
	for(double H=Len-1.0;H>=0;H-=1.0){
		ResultX=(int)(XL*H);
		ResultY=(int)(YL*H);
		if(PickupArea.IsInclude(TargetX+ResultX,TargetY+ResultY)==false){
			return true;
		}
	}
	for(int L=1;L<100;L++){
		ResultY=-L;
		for(ResultX=-L;ResultX<L;ResultX++){
			if(PickupArea.IsInclude(TargetX+ResultX,TargetY+ResultY)==false){
				return true;
			}
		}
		ResultX=L;
		for(ResultY=-L;ResultY<L;ResultY++){
			if(PickupArea.IsInclude(TargetX+ResultX,TargetY+ResultY)==false){
				return true;
			}
		}
		ResultY=L;
		for(ResultX=L;ResultX>-L;ResultX--){
			if(PickupArea.IsInclude(TargetX+ResultX,TargetY+ResultY)==false){
				return true;
			}
		}
		ResultX=-L;
		for(ResultY=L;ResultY>-L;ResultY--){
			if(PickupArea.IsInclude(TargetX+ResultX,TargetY+ResultY)==false){
				return true;
			}
		}
	}
	return false;
}


#if	defined(NeedFringeBit)
void	AutoAlignmentInPico::SetTransBit(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)Parent->GetParentInPage();
	FringeArea.MakeBitData(PPage->ResultBitTransFromMaster,PPage->XLen,PPage->YLen);
	FringeArea.MakeBitData(PPage->ResultBitTransFromTarget,(int)ShiftX,(int)ShiftY,PPage->XLen,PPage->YLen);
}

void	AutoAlignmentInPico::SetFirstTransBit(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)Parent->GetParentInPage();
	FringeArea.MakeBitData(PPage->ResultBitFirstTransFromMaster,PPage->XLen,PPage->YLen);
	FringeArea.MakeBitData(PPage->ResultBitFirstTransFromTarget,(int)ShiftX,(int)ShiftY,PPage->XLen,PPage->YLen);
}
#endif
void	AutoAlignmentInPico::SetPickupBit(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)Parent->GetParentInPage();
	PickupArea.MakeBitData(PPage->ResultBitPickupFromMaster,PPage->XLen,PPage->YLen);
	PickupArea.MakeBitData(PPage->ResultBitPickupFromTarget,(int)ShiftX,(int)ShiftY,PPage->XLen,PPage->YLen);
}

void	AutoAlignmentInPico::SetFirstPickupBit(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)Parent->GetParentInPage();
	PickupArea.MakeBitData(PPage->ResultBitFirstPickupFromMaster,PPage->XLen,PPage->YLen);
	PickupArea.MakeBitData(PPage->ResultBitFirstPickupFromTarget,(int)ShiftX,(int)ShiftY,PPage->XLen,PPage->YLen);
}

void	AutoAlignmentInPico::CalcAdjust(void)
{
	if(Yn>0){
		if(Xn>0){
			CalcAdjustInner(Xn-1,Yn-1);
		}
			CalcAdjustInner(Xn  ,Yn-1);
		if(Xn<DimPoint->PicoDimXNumb-1){
			CalcAdjustInner(Xn+1,Yn-1);
		}
	}
		if(Xn>0){
			CalcAdjustInner(Xn-1,Yn);
		}
		if(Xn<DimPoint->PicoDimXNumb-1){
			CalcAdjustInner(Xn+1,Yn);
		}
	if(Yn<DimPoint->PicoDimYNumb-1){
		if(Xn>0){
			CalcAdjustInner(Xn-1,Yn+1);
		}
			CalcAdjustInner(Xn  ,Yn+1);
		if(Xn<DimPoint->PicoDimXNumb-1){
			CalcAdjustInner(Xn+1,Yn+1);
		}
	}
}



void	AutoAlignmentInPico::CalcAdjustInner(int x ,int y)
{
	AutoAlignmentInPico	*p=DimPoint->PicoDim[y][x];
	if(p->Effective==true && p->Adopted==true){
		if(NeedAdjust==true){
			if(fabs(p->ShiftX-ShiftX)>1.0){
				if(p->ShiftX>ShiftX){
					ShiftX=p->ShiftX-1;
				}
				else if(p->ShiftX<ShiftX){
					ShiftX=p->ShiftX+1;
				}
			}
			if(fabs(p->ShiftY-ShiftY)>1.0){
				if(p->ShiftY>ShiftY){
					ShiftY=p->ShiftY-1;
				}
				else if(p->ShiftY<ShiftY){
					ShiftY=p->ShiftY+1;
				}
			}
		}
	}
}


bool	AutoAlignmentInPico::CalcAdjustAll(void)
{
	bool	Changed=false;
	if(Yn>0){
		if(Xn>0){
			if(CalcAdjustAllInner(Xn-1,Yn-1)==true){
				Changed=true;
			}
		}
			if(CalcAdjustAllInner(Xn  ,Yn-1)==true){
				Changed=true;
			}
		if(Xn<DimPoint->PicoDimXNumb-1){
			if(CalcAdjustAllInner(Xn+1,Yn-1)==true){
				Changed=true;
			}
		}
	}
		if(Xn>0){
			if(CalcAdjustAllInner(Xn-1,Yn)==true){
				Changed=true;
			}
		}
		if(Xn<DimPoint->PicoDimXNumb-1){
			if(CalcAdjustAllInner(Xn+1,Yn)==true){
				Changed=true;
			}
		}
	if(Yn<DimPoint->PicoDimYNumb-1){
		if(Xn>0){
			if(CalcAdjustAllInner(Xn-1,Yn+1)==true){
				Changed=true;
			}
		}
			if(CalcAdjustAllInner(Xn  ,Yn+1)==true){
				Changed=true;
			}
		if(Xn<DimPoint->PicoDimXNumb-1){
			if(CalcAdjustAllInner(Xn+1,Yn+1)==true){
				Changed=true;
			}
		}
	}
	return Changed;
}

bool	AutoAlignmentInPico::CalcAdjustAllInner(int x ,int y)
{
	bool	Changed=false;
	if(NeedAdjust==true){
		AutoAlignmentInPico	*p=DimPoint->PicoDim[y][x];
		if(p->MatchResult>=MatchResult && p->MatchResult>0){
			if(fabs(p->ShiftX-ShiftX)>1.0){
				if(p->ShiftX>ShiftX){
					ShiftX=p->ShiftX-1;
					Changed=true;
				}
				else if(p->ShiftX<ShiftX){
					ShiftX=p->ShiftX+1;
					Changed=true;
				}
			}
			if(fabs(p->ShiftY-ShiftY)>1.0){
				if(p->ShiftY>ShiftY){
					ShiftY=p->ShiftY-1;
					Changed=true;
				}
				else if(p->ShiftY<ShiftY){
					ShiftY=p->ShiftY+1;
					Changed=true;
				}
			}
		}
	}
	return Changed;
}

void	AutoAlignmentInPico::MakePickupAreaFromPico(BYTE **BMap,int XByte ,int YLen)
{
	PickupArea.MakeBitData(BMap,XByte*8,YLen);
}

