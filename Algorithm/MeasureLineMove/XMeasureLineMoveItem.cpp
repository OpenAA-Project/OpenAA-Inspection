/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\XMeasureLineMove.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureLineMove.h"
#include "omp.h"
#include "XDrawFunc.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "XMeasureLineMovePacket.h"
#include "XLearningRegist.h"
#include "XTransform.h"
#include "XCrossObj.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

bool    MeasureLineMoveItemBase::Save(QIODevice *f)
{
	int32	Ver=3;

	if(AlgorithmItemPI::Save(f)==false)
		return false;
	if(::Save(f,Ver)==false)
		return false;

	//if(::Save(f,ItemName)==false)
	//	return false;

	if(::Save(f,TransferInfo)==false)
		return false;
	return true;
}

bool    MeasureLineMoveItemBase::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(Ver==1){
		QString	tItemName;
		if(::Load(f,tItemName)==false)
			return false;
		SetItemName(tItemName);
	}
	if(Ver>=3){
		if(::Load(f,TransferInfo)==false)
			return false;
	}
	else{
		TransferInfo=-1;
	}
	return true;
}
AlgorithmItemPI	&MeasureLineMoveItemBase::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);

	const MeasureLineMoveItemBase	*p=dynamic_cast<const MeasureLineMoveItemBase *>(&src);
	if(p!=NULL){
		AVector	=p->AVector;
		AMx		=p->AMx;
		AMy		=p->AMy;
		TResultImage	=p->TResultImage;
		LResultImage	=p->LResultImage;
		TransferInfo	=p->TransferInfo;
	}
	return *this;
}

void	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(ExecuteInitialAfterEditInfo &EInfo)
{
	AMx=0;
	AMy=0;
	if(GetLayersBase()->GetResultDLLBase()!=NULL){
		ResultDLL	*R=GetLayersBase()->GetResultDLLBase()->GetFirst();
		if(R!=NULL){
			ResultDLLBaseRoot	*Rp=R->GetDLLPoint();
			if(Rp!=NULL){
				CreateImage(Rp->NGImageWidth ,Rp->NGImageHeight);
			}
		}
	}
}
double	MeasureLineMoveItemBase::ExpFunc(double c ,double MasterC)
{
	if(MasterC>0.0){
		double	k=(c-MasterC)/MasterC/0.1;	//10%‚Ì•Ï‰»‚Å‚P
		double	p=exp(-(k*k));
		return p;
	}
	double	p=exp(-(c*c));
	return p;
}

void	MeasureLineMoveItemBase::CreateImage(int Width ,int Height)
{
	if(TResultImage.width()!=Width || TResultImage.height()!=Height){
		TResultImage=QImage(Width,Height,QImage::Format_RGB32);
	}
	if(LResultImage.width()!=Width || LResultImage.height()!=Height){
		LResultImage=QImage(Width,Height,QImage::Format_ARGB32);
	}
}

//=================================================================================

MeasureLineMoveLineItem::MeasureLineMoveLineItem(void)
{
	X1OnMaster	=0;
	Y1OnMaster	=0;
	X2OnMaster	=0;
	Y2OnMaster	=0;
	Vx=0;
	Vy=0;
	AvrSideA	=0.0;
	AvrSideB	=0.0;
	OffsetForDark=7;
	MatchStartPos	=0.0;
	MatchEndPos		=1.0;
	ResultShift		=0;
}


bool	MeasureLineMoveLineItem::Save(QIODevice *f)
{
	int32	Ver=3;

	if(MeasureLineMoveItemBase::Save(f)==false)
		return false;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,X1OnMaster)==false)
		return false;
	if(::Save(f,Y1OnMaster)==false)
		return false;
	if(::Save(f,X2OnMaster)==false)
		return false;
	if(::Save(f,Y2OnMaster)==false)
		return false;
	if(::Save(f,OffsetForDark)==false)
		return false;
	if(::Save(f,MatchStartPos)==false)
		return false;
	if(::Save(f,MatchEndPos)==false)
		return false;
	return true;
}
bool	MeasureLineMoveLineItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(MeasureLineMoveItemBase::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,X1OnMaster)==false)
		return false;
	if(::Load(f,Y1OnMaster)==false)
		return false;
	if(::Load(f,X2OnMaster)==false)
		return false;
	if(::Load(f,Y2OnMaster)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,OffsetForDark)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,MatchStartPos)==false)
			return false;
		if(::Load(f,MatchEndPos)==false)
			return false;
	}
	return true;
}
bool	MeasureLineMoveLineItem::Transform(TransformBase &Param)
{
	double	tPosX1	;
	double	tPosY1	;
	double	tPosX2	;
	double	tPosY2	;
	Param.Transform(X1OnMaster,Y1OnMaster,tPosX1,tPosY1);
	Param.Transform(X2OnMaster,Y2OnMaster,tPosX2,tPosY2);
	X1OnMaster	=tPosX1;
	Y1OnMaster	=tPosY1;
	X2OnMaster	=tPosX2;
	Y2OnMaster	=tPosY2;

	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}

	return true;
}

void	MeasureLineMoveLineItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveLineItem *src=(MeasureLineMoveLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
			MatchStartPos	=src->MatchStartPos;
			MatchEndPos		=src->MatchEndPos;
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureLineMoveLineItem *)Data)->GetLibID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveLineItem *src=(MeasureLineMoveLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
			MatchStartPos	=src->MatchStartPos;
			MatchEndPos		=src->MatchEndPos;
		}
	}
}
AlgorithmItemPI	&MeasureLineMoveLineItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureLineMoveItemBase::operator=(src);

	const MeasureLineMoveLineItem	*p=dynamic_cast<const MeasureLineMoveLineItem *>(&src);
	if(p!=NULL){
		X1OnMaster	=p->X1OnMaster;
		Y1OnMaster	=p->Y1OnMaster;
		Y2OnMaster	=p->Y2OnMaster;
		Y2OnMaster	=p->Y2OnMaster;
		MatchStartPos	=p->MatchStartPos;
		MatchEndPos		=p->MatchEndPos;
	}

	return *this;
}

VectorLineBase	*MeasureLineMoveLineItem::CreateVectorBase(void)
{
	VectorLineDouble	*R=new VectorLineDouble();
	R->AppendItemBase(R->CreateItem());
	R->AppendItemBase(R->CreateItem());
	return R;
}

bool	MeasureLineMoveLineItem::SetLocalData(MeasureLineMoveInPage *ParentPage)
{
	if(GetVector()==NULL)
		return false;

	VectorItemBase	*d1=GetVector()->GetFirstItem();
	if(d1==NULL){
		return false;
	}
	VectorItemBase	*d2=d1->GetNext();
	if(d2==NULL){
		return false;
	}
	VectorItemDouble	*v1=dynamic_cast<VectorItemDouble *>(d1);
	VectorItemDouble	*v2=dynamic_cast<VectorItemDouble *>(d2);
	if(v1==NULL || v2==NULL){
		return false;
	}
	X1OnMaster	=v1->GetX();
	Y1OnMaster	=v1->GetY();
	X2OnMaster	=v2->GetX();
	Y2OnMaster	=v2->GetY();

	return true;
}
void	MeasureLineMoveLineItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::MoveTo(GlobalDx ,GlobalDy);
		X1OnMaster+=GlobalDx;
		Y1OnMaster+=GlobalDy;
		X2OnMaster+=GlobalDx;
		Y2OnMaster+=GlobalDy;
		//AreaWithIdeal.MoveToNoClip(GlobalDx,GlobalDy);
		AreaWithIdealContainer.MoveToNoClip(GlobalDx,GlobalDy);

		AreaSideA.MoveToNoClip(GlobalDx,GlobalDy);
		AreaSideB.MoveToNoClip(GlobalDx,GlobalDy);
	}
}

void	MeasureLineMoveLineItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	QColor	col2(Qt::red);
	col2.setAlpha(80);
	AreaSideA.DrawAlpha(0,0 ,&pnt ,col2.rgba() ,ZoomRate ,movx ,movy);

	int	x1=(X1OnMaster+movx)*ZoomRate;
	int	y1=(Y1OnMaster+movy)*ZoomRate;

	int	x2=(X2OnMaster+movx)*ZoomRate;
	int	y2=(Y2OnMaster+movy)*ZoomRate;

	//AreaWithIdeal.DrawImage(0,0,&pnt
	//					,ZoomRate ,movx ,movy
	//					,false,false,true
	//					,0x40);
	for(FlexAreaImageList *a=AreaWithIdealContainer.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawImage(0,0,&pnt
						,ZoomRate ,movx ,movy
						,false,false,true
						,0x40);
	}

	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(x1,y1,x2,y2);

	if(ZoomRate>2.0){
		Pnt.setPen(Qt::red);
		Pnt.setBrush(Qt::cyan);
		double	Cx=(X1OnMaster+X2OnMaster)/2;
		double	Cy=(Y1OnMaster+Y2OnMaster)/2;
		int	R=GetThresholdR()->SearchDot;
		DrawArrow(Cx,Cy,Cx+Vx*R,Cy+Vy*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
		DrawArrow(Cx,Cy,Cx-Vx*R,Cy-Vy*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
	}
}

void	MeasureLineMoveLineItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		VectorLineDouble	*v=(VectorLineDouble *)GetVector();
		VectorItemBase	*V1	=v->GetItemAt(0);
		VectorItemBase	*V2	=v->GetItemAt(1);
		if(V1!=NULL && V2!=NULL){
			//int	x1=V1->GetX();
			//int	y1=V1->GetY();
			//int	x2=V2->GetX();
			//int	y2=V2->GetY();
			int	x1=X1OnMaster;
			int	y1=Y1OnMaster;
			int	x2=X2OnMaster;
			int	y2=Y2OnMaster;

			for(FlexAreaImageList *a=AreaWithIdealContainer.GetFirst();a!=NULL;a=a->GetNext()){
				a->DrawImage(ResultShift*Vx+Res->GetAlignedX(),ResultShift*Vy+Res->GetAlignedY()
								,&IData
								,ZoomRate ,MovX ,MovY
								,false,false,true
								,0x40);
			}
			PData.setPen(Qt::yellow);
			PData.drawLine((x1+MovX)*ZoomRate,(y1+MovY)*ZoomRate
						  ,(x2+MovX)*ZoomRate,(y2+MovY)*ZoomRate);
			
			PData.setPen(Qt::red);
			//int	Rnd=+GetID()%5;
			PData.drawLine((x1+ResultShift*Vx+MovX+Res->GetAlignedX())*ZoomRate,(y1+ResultShift*Vy+MovY+Res->GetAlignedY())*ZoomRate
						  ,(x2+ResultShift*Vx+MovX+Res->GetAlignedX())*ZoomRate,(y2+ResultShift*Vy+MovY+Res->GetAlignedY())*ZoomRate);

			if(IsUnitMode()==true){
				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate
								,QString::number(GetID())+QString(":")+TransformPixelToUnitStr(ResultShift)
																		+QString(" (")
																		+QString::number(ResultShift)
																		+QString(")")
																		);

				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate+20
								,QString("Dx,Dy=")  +TransformPixelToUnitStr(Res->GetAlignedX())
													+QString(" (")
													+QString::number(Res->GetAlignedX())
													+QString("),")
													+TransformPixelToUnitStr(Res->GetAlignedY())
													+QString(" (")
													+QString::number(Res->GetAlignedY())
													+QString(")")
													);
			}
			else{
				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate
								,QString::number(GetID())+QString(":")+QString::number(ResultShift));

				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate+20
								,QString("Dx,Dy=")+QString::number(Res->GetAlignedX())+QString(",")+QString::number(Res->GetAlignedY()));
			}
		}
	}
}
void	MeasureLineMoveLineItem::DrawNumber(QImage &IData ,QPainter &PData
											,int MovX ,int MovY ,double ZoomRate
											,int Number)
{
	int	x1=X1OnMaster;
	int	y1=Y1OnMaster;
	int	x2=X2OnMaster;
	int	y2=Y2OnMaster;
	PData.setBrush(Qt::green);
	PData.setPen(Qt::green);
	PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
					,((y1+y2)/2+MovY)*ZoomRate+32
					,QString::number(Number));
}

double	MeasureLineMoveLineItem::CalcCoeff(int dx ,int dy ,ImageBuffer &IBuff ,bool BrightnessMatch)
{
	double	Avr=0;
	int		N=0;
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	for(FlexAreaImageList *a=AreaWithIdealContainer.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeff	*t=(FlexAreaImageListCoeff *)a;
		double	D=fabs(t->CalcCoeff(dx ,dy ,IBuff));
		if(BrightnessMatch==true){
			if(RThr->PrevailRight==true){
				int	t=AreaRightContainer[N]->GetAverage(IBuff,dx,dy);
				int MinBrightness,MaxBrightness;
				AreaRightContainer[N]->GetMinMaxBrightness(IBuff,dx,dy ,MinBrightness,MaxBrightness);
				if((MaxBrightness-MinBrightness>20) && (MaxBrightness-MinBrightness)>t*0.25){
					D=0;
				}
				else{
					int	m=RThr->BrightnessMasterRight[N];
					int	s=m*0.2;
					if(s<10)
 						s=10;
					if((t>=m && t-m>4*s) || (t<m && m-t>s)){
						D=0;
					}
				}
			}
			if(RThr->PrevailLeft==true){
				int	t=AreaLeftContainer[N]->GetAverage(IBuff,dx,dy);
				int MinBrightness,MaxBrightness;
				AreaLeftContainer[N]->GetMinMaxBrightness(IBuff,dx,dy ,MinBrightness,MaxBrightness);
				if((MaxBrightness-MinBrightness>20) && (MaxBrightness-MinBrightness)>t*0.25){
					D=0;
				}
				else{
					int	m=RThr->BrightnessMasterLeft[N];
					int	s=m*0.2;
					if(s<10)
						s=10;
					if((t>=m && t-m>4*s) || (t<m && m-t>s)){
						D=0;
					}
				}
			}
		}

		Avr+=D;
		N++;
	}
	if(N==0)
		return 0;
	return Avr/N;
}

double	MeasureLineMoveLineItem::CalcCoeffOnlySameColor(int dx ,int dy ,ImageBuffer &IBuff ,bool BrightnessMatch)
{
	double	Avr=0;
	int		N=0;
	int		Counter=0;
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	for(FlexAreaImageList *a=AreaWithIdealContainer.GetFirst();a!=NULL;a=a->GetNext(),Counter++){
		FlexAreaImageListCoeff	*t=(FlexAreaImageListCoeff *)a;
		double	D=fabs(t->CalcCoeff(dx ,dy ,IBuff));
		if(BrightnessMatch==true){
			if(RThr->PrevailRight==true){
				int	t=AreaRightContainer[Counter]->GetAverage(IBuff,dx,dy);
				int MinBrightness,MaxBrightness;
				AreaRightContainer[Counter]->GetMinMaxBrightness(IBuff,dx,dy ,MinBrightness,MaxBrightness);
				if((MaxBrightness-MinBrightness>20) && (MaxBrightness-MinBrightness)>t*0.25){
					continue;
				}
				else{
					int	m=RThr->BrightnessMasterRight[Counter];
					int	s=m*0.2;
					if(s<10)
 						s=10;
					if((t>=m && t-m>4*s) || (t<m && m-t>s)){
						continue;
					}
				}
			}
			if(RThr->PrevailLeft==true){
				int	t=AreaLeftContainer[Counter]->GetAverage(IBuff,dx,dy);
				int MinBrightness,MaxBrightness;
				AreaLeftContainer[Counter]->GetMinMaxBrightness(IBuff,dx,dy ,MinBrightness,MaxBrightness);
				if((MaxBrightness-MinBrightness>20) && (MaxBrightness-MinBrightness)>t*0.25){
					continue;
				}
				else{
					int	m=RThr->BrightnessMasterLeft[Counter];
					int	s=m*0.2;
					if(s<10)
						s=10;
					if((t>=m && t-m>4*s) || (t<m && m-t>s)){
						continue;
					}
				}
			}
		}
		Avr+=D;
		N++;
	}
	if(Counter>5 && N<=3)
		return 0;
	if(N==0)
		return 0;
	return Avr/N;
}

void	MeasureLineMoveLineItem::GetCenterPoint(double &cx, double &cy)
{
	cx=(X1OnMaster+X2OnMaster)/2.0;
	cy=(Y1OnMaster+Y2OnMaster)/2.0;
}

void	MeasureLineMoveLineItem::Move(double dx ,double dy)
{
	ExecuteMove(dx,dy,true);
}

void	MeasureLineMoveLineItem::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx=(X1OnMaster+X2OnMaster)/2;
		int	cy=(Y1OnMaster+Y2OnMaster)/2;
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	Move(mx,my);
}

ExeResult	MeasureLineMoveLineItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(EInfo);
	SetLocalData((MeasureLineMoveInPage *)GetParentInPage());
	double	A= Y2OnMaster-Y1OnMaster;
	double	B=-X2OnMaster+X1OnMaster;
	double	M=hypot(A,B);

	Vx=0;
	Vy=0;

	if(M>0){
		Vx=A/M;
		Vy=B/M;
	}

	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);	
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	if(RThr->SearchType==0){
		ExecuteInitialAfterEditMakeC(EInfo);	
		double	MaxD=0;
		double	MaxR=0;
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			int		dx=r*Vx;
			int		dy=r*Vy;
			double	D=fabs(CalcCoeff(dx ,dy ,*MasterImageList[0]));
			double	ca=AreaSideA	.GetAverage(*MasterImageList[0],dx,dy);
			double	cb=AreaSideB	.GetAverage(*MasterImageList[0],dx,dy);
			double	M=D*ExpFunc(ca,AvrSideA)*ExpFunc(cb,AvrSideB);
			if(M>MaxD){
				MaxD=M;
				iMaxR=r;
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.1){
			double	rdx=R*Vx;
			double	rdy=R*Vy;
			double	D=fabs(CalcCoeff(rdx ,rdy ,*MasterImageList[0]));
			double	ca=AreaSideA	.GetAverage(*MasterImageList[0],rdx,rdy);
			double	cb=AreaSideB	.GetAverage(*MasterImageList[0],rdx,rdy);
			double	M=D*ExpFunc(ca,AvrSideA)*ExpFunc(cb,AvrSideB);
			if(M>MaxD){
				MaxD=M;
				MaxR=R;
			}
		}
		if(RThr->ModeToSetInInitial==true){
			X1OnMaster+=MaxR*Vx;
			Y1OnMaster+=MaxR*Vy;
			X2OnMaster+=MaxR*Vx;
			Y2OnMaster+=MaxR*Vy;
			ExecuteInitialAfterEditMakeC(EInfo);
		}
	}
	else if(RThr->SearchType==1 || RThr->SearchType==2 || RThr->SearchType==3){
		AreaLeftContainer.RemoveAll();
		AreaRightContainer.RemoveAll();
		PureFlexAreaList	*L=new PureFlexAreaList();
		XYClassContainer PL;
		PL.AppendList(new XYClass(X1OnMaster,Y1OnMaster));
		PL.AppendList(new XYClass(X1OnMaster+Vx*RThr->EdgeWidth,Y1OnMaster+Vy*RThr->EdgeWidth));
		PL.AppendList(new XYClass(X2OnMaster+Vx*RThr->EdgeWidth,Y2OnMaster+Vy*RThr->EdgeWidth));
		PL.AppendList(new XYClass(X2OnMaster,Y2OnMaster));
		L->MakeConvexPolygon(PL);
		AreaLeftContainer.AppendList(L);

		PureFlexAreaList	*R=new PureFlexAreaList();
		XYClassContainer PR;
		PR.AppendList(new XYClass(X1OnMaster,Y1OnMaster));
		PR.AppendList(new XYClass(X1OnMaster-Vx*RThr->EdgeWidth,Y1OnMaster-Vy*RThr->EdgeWidth));
		PR.AppendList(new XYClass(X2OnMaster-Vx*RThr->EdgeWidth,Y2OnMaster-Vy*RThr->EdgeWidth));
		PR.AppendList(new XYClass(X2OnMaster,Y2OnMaster));
		R->MakeConvexPolygon(PR);
		AreaRightContainer.AppendList(R);
	}
	ResultShift=0;

	int	cx=(X1OnMaster+X2OnMaster)/2;
	int	cy=(Y1OnMaster+Y2OnMaster)/2;
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	int	N=AreaWithIdealContainer.GetCount();

	if(RThr->BrightnessMasterRight!=NULL){
		delete	[]RThr->BrightnessMasterRight;
	}
	GetThresholdW()->BrightnessMasterRight	=new BYTE[N+1];
	int	n=0;
	for(PureFlexAreaList *R=AreaRightContainer.GetFirst();R!=NULL;R=R->GetNext(),n++){
		GetThresholdW()->BrightnessMasterRight[n]=R->GetAverage(*MasterImageList[0],0,0);
	}

	if(RThr->BrightnessMasterLeft!=NULL){
		delete	[]RThr->BrightnessMasterLeft;
	}
	GetThresholdW()->BrightnessMasterLeft	=new BYTE[N+1];
	n=0;
	for(PureFlexAreaList *R=AreaLeftContainer.GetFirst();R!=NULL;R=R->GetNext(),n++){
		GetThresholdW()->BrightnessMasterLeft[n]=R->GetAverage(*MasterImageList[0],0,0);
	}

	return _ER_true;
}
void	MeasureLineMoveLineItem::ExecuteInitialAfterEditMakeC(ExecuteInitialAfterEditInfo &EInfo)
{
	AreaWithIdealContainer.RemoveAll();
	AreaRightContainer.RemoveAll();
	AreaLeftContainer.RemoveAll();

	double	Dx=X2OnMaster-X1OnMaster;
	double	Dy=Y2OnMaster-Y1OnMaster;
	double	L=hypot(Dx,Dy);

	int	StartL	=MatchStartPos*L;
	int	EndL	=MatchEndPos*L;

	for(int H=StartL;H<EndL;H+=10){
		ExecuteInitialAfterEditMakeSmall(H ,H+12,EInfo);
	}
}

void	MeasureLineMoveLineItem::ExecuteInitialAfterEditMakeSmall(double t1 ,double t2,ExecuteInitialAfterEditInfo &EInfo)
{
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	R	=RThr->EdgeWidth;

	double	Dx=X2OnMaster-X1OnMaster;
	double	Dy=Y2OnMaster-Y1OnMaster;
	double	L=hypot(Dx,Dy);
	if(L<=0.0001){
		return;
	}
	Dx /=L;
	Dy /=L;
	double	Px1=X1OnMaster + Dx*t1;
	double	Py1=Y1OnMaster + Dy*t1;
	double	Px2=X1OnMaster + Dx*t2;
	double	Py2=Y1OnMaster + Dy*t2;
	double	hVx=Vx*R;
	double	hVy=Vy*R;

	FlexAreaImageListCoeff	*A=new FlexAreaImageListCoeff();
	XYClassContainer	P;
	P.Add(Px1+hVx,Py1+hVy);
	P.Add(Px2+hVx,Py2+hVy);
	P.Add(Px2-hVx,Py2-hVy);
	P.Add(Px1-hVx,Py1-hVy);
	A->MakeConvexPolygon(P);
	A->AllocateOnly();

	int	N=A->GetFLineLen();
	struct  FlexLine    *FLRight=new struct FlexLine[N];
	struct  FlexLine    *FLLeft=new struct FlexLine[N];
	int		RPoint=0;
	int		LPoint=0;
	int		RPointY=-9999999;
	int		LPointY=-9999999;

	double	C=Dx*Py1 - Dy*Px1;
	BYTE	*p=A->GetData();
	for(int i=0;i<N;i++){
		int	x1	=A->GetFLineLeftX(i);
		int	Numb=A->GetFLineNumb(i);
		int	AbsY=A->GetFLineAbsY(i);
		for(int n=0;n<Numb;n++){
			int	x=x1+n;
			if(Dy*x-Dx*AbsY+C>=0){
				*p=0xFF;
				if(RPointY!=AbsY){
					if(RPointY<0){
						RPointY=AbsY;
						FLRight[RPoint]._LeftX	=x;
						FLRight[RPoint]._AbsY	=AbsY;
					}
					else{
						RPoint++;
						FLRight[RPoint]._LeftX	=x;
						FLRight[RPoint]._AbsY	=AbsY;
					}
					RPointY=AbsY;
				}
				FLRight[RPoint]._Numb=x-FLRight[RPoint]._LeftX;
			}
			else{
				*p=0;
				if(LPointY!=AbsY){
					if(LPointY<0){
						LPointY=AbsY;
						FLLeft[LPoint]._LeftX	=x;
						FLLeft[LPoint]._AbsY	=AbsY;
					}
					else{
						LPoint++;
						FLLeft[LPoint]._LeftX	=x;
						FLLeft[LPoint]._AbsY	=AbsY;
					}
					LPointY=AbsY;
				}
				FLLeft[LPoint]._Numb=x-FLLeft[LPoint]._LeftX;
			}
			p++;
		}
	}
	A->MakeSum();
	AreaWithIdealContainer.AppendList(A);

	PureFlexAreaList	*Rp=new PureFlexAreaList();
	Rp->SetFLine(FLRight,RPoint+1);
	AreaRightContainer.AppendList(Rp);

	PureFlexAreaList	*Lp=new PureFlexAreaList();
	Lp->SetFLine(FLLeft,LPoint+1);
	AreaLeftContainer.AppendList(Lp);
}
	


ExeResult	MeasureLineMoveLineItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx=(X1OnMaster+X2OnMaster)/2;
		int	cy=(Y1OnMaster+Y2OnMaster)/2;
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	ImageBuffer *TargetImageList[100];
	GetTargetBuffList(TargetImageList);	
	Res->SetAlignedXY(mx,my);
	AMx=mx;
	AMy=my;
	double	MaxR=GetResultShift(mx ,my ,TargetImageList[0]);

	//ResultShift=MaxR+OffsetForDark;
	ResultShift=MaxR;
	SetCalcDone(true);
	return _ER_true;
}

double	MeasureLineMoveLineItem::GetResultShift(int mx ,int my ,ImageBuffer *TargetImage)
{
	double	MaxD=0;
	double	MaxR=0;
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	if(RThr->SearchType==0){
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			double	D=fabs(CalcCoeffOnlySameColor(mx+dx ,my+dy ,*TargetImage,true));
			double	M=D;
			if(M>=MaxD){
				MaxD=M;
				iMaxR=r;
			}
		}
		if(iMaxR>=RThr->SearchDot || iMaxR<-RThr->SearchDot
		|| (RThr->PrevailRight==false && RThr->PrevailLeft==false)){
			MaxD=0;
			MaxR=0;
			iMaxR=0;
			for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
				double	dx=r*Vx;
				double	dy=r*Vy;
				//double	D=fabs(CalcCoeffOnlySameColor(mx+dx ,my+dy ,*TargetImageList[0],true));
				int	N=min(AreaRightContainer.GetCount(),AreaLeftContainer.GetCount());
				double	MM=0;
				for(int i=0;i<N;i++){
					double	DR=AreaRightContainer[i]->GetAverage(*TargetImage,mx+dx ,my+dy);
					double	DL=AreaLeftContainer [i]->GetAverage(*TargetImage,mx+dx ,my+dy);
					MM+=(DR-DL)*(DR-DL);
				}
				if(MM>=MaxD){
					MaxD=MM;
					iMaxR=r;
				}
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.1){
			double	rdx=R*Vx;
			double	rdy=R*Vy;
			double	D=fabs(CalcCoeffOnlySameColor(mx+rdx ,my+rdy ,*TargetImage,true));
			double	M=D;
			if(M>=MaxD){
				MaxD=M;
				MaxR=R;
			}
		}
	}
	else if(RThr->SearchType==1){
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			double	DR=GetAvrageBrightness(mx+dx ,my+dy ,AreaRightContainer,*TargetImage);
			double	DL=GetAvrageBrightness(mx+dx ,my+dy ,AreaLeftContainer ,*TargetImage);

			double	sa1=fabs(DR-RThr->BrightnessIdealRight);
			double	sa2=fabs(DL-RThr->BrightnessIdealLeft);
			double	d1=exp(-sa1/10)*exp(-sa2/10);

			double	sb1=fabs(DR-RThr->BrightnessIdealLeft);
			double	sb2=fabs(DL-RThr->BrightnessIdealRight);
			double	d2=exp(-sb1/10)*exp(-sb2/10);
			double	Dif=max(d1,d2);

			double	Brighter=(DR+DL)/2;
			if(Brighter>0){
				double	D=fabs(DR-DL)/Brighter*Dif;
				if(MaxD<D){
					iMaxR=r;
					MaxD=D;
				}
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.2){
			double	dx=R*Vx;
			double	dy=R*Vy;
			double	DR=GetAvrageBrightness(mx+dx ,my+dy ,AreaRightContainer,*TargetImage);
			double	DL=GetAvrageBrightness(mx+dx ,my+dy ,AreaLeftContainer ,*TargetImage);
			double	sa1=fabs(DR-RThr->BrightnessIdealRight);
			double	sa2=fabs(DL-RThr->BrightnessIdealLeft);
			double	d1=exp(-sa1/10)*exp(-sa2/10);

			double	sb1=fabs(DR-RThr->BrightnessIdealLeft);
			double	sb2=fabs(DL-RThr->BrightnessIdealRight);
			double	d2=exp(-sb1/10)*exp(-sb2/10);
			double	Dif=max(d1,d2);

			double	Brighter=(DR+DL)/2;
			if(Brighter>0){
				double	D=fabs(DR-DL)/Brighter*Dif;
				if(MaxD<D){
					MaxR=R;
					MaxD=D;
				}
			}
		}
	}
	else if(RThr->SearchType==2){
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			double	D=GetMatchingForType2(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				iMaxR=r;
				MaxD=D;
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.2){
			double	dx=R*Vx;
			double	dy=R*Vy;
			double	D=GetMatchingForType2(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				MaxR=R;
				MaxD=D;
			}
		}
	}
	else if(RThr->SearchType==3){
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			double	D=GetMatchingForType3(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				iMaxR=r;
				MaxD=D;
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.2){
			double	dx=R*Vx;
			double	dy=R*Vy;
			double	D=GetMatchingForType3(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				MaxR=R;
				MaxD=D;
			}
		}
	}
	else if(RThr->SearchType==4){
		int		iMaxR=0;
		for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			double	D=GetMatchingForType4(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				iMaxR=r;
				MaxD=D;
			}
		}
		MaxD=0;
		for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.2){
			double	dx=R*Vx;
			double	dy=R*Vy;
			double	D=GetMatchingForType4(mx+dx ,my+dy ,*TargetImage);
			if(MaxD<D){
				MaxR=R;
				MaxD=D;
			}
		}
	}
	else if(RThr->SearchType==5){
		int	MoveLen=RThr->SearchDot;
		double	BrDim[10000];
		double	RDim[10000];
		int	n=0;
		for(double r=-MoveLen;r<=MoveLen && n<10000;r+=0.3,n++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			RDim[n]=r;
			BrDim[n]=GetLineAverage(mx+dx ,my+dy ,*TargetImage);
		}
		if(n>=3){
			double	OutsideAverage=(BrDim[0]+BrDim[1]+BrDim[2])/3.0;
			double	InsideAverage =(BrDim[n-1]+BrDim[n-2]+BrDim[n-3])/3.0;
			double	ThresholdBr=fabs(InsideAverage-OutsideAverage)*RThr->ThresholdRate;
			if(ThresholdBr<5)
				ThresholdBr=5;
			if(ThresholdBr>40)
				ThresholdBr=40;

			if(OutsideAverage<InsideAverage){
				for(int k=0;k<n;k++){
					double	d=BrDim[k]-OutsideAverage;
					if(d>ThresholdBr){
						MaxR=RDim[k];
						break;
					}
				}
			}
			else{
				for(int k=0;k<n;k++){
					double	d=OutsideAverage-BrDim[k];
					if(d>ThresholdBr){
						MaxR=RDim[k];
						break;
					}
				}
			}
		}
	}
	else if(RThr->SearchType==6){
		int	MoveLen=RThr->SearchDot;
		double	BrDim[10000];
		double	RDim[10000];
		int	n=0;
		for(double r=-MoveLen;r<=MoveLen && n<10000;r+=0.3,n++){
			double	dx=r*Vx;
			double	dy=r*Vy;
			RDim[n]=r;
			BrDim[n]=GetLineAverage(mx+dx ,my+dy ,*TargetImage);
		}
		if(n>=3){
			double	OutsideAverage=(BrDim[0]+BrDim[1]+BrDim[2])/3.0;
			double	InsideAverage =(BrDim[n-1]+BrDim[n-2]+BrDim[n-3])/3.0;
			double	CenterAverage =(OutsideAverage+InsideAverage)/2;

			for(int k=2;k<n-2;k++){
				if((BrDim[k-1]<CenterAverage && CenterAverage<=BrDim[k])
				|| (BrDim[k-1]>CenterAverage && CenterAverage>=BrDim[k])){
					MaxR=RDim[k];
					break;
				}
			}
		}
	}
	else if(RThr->SearchType==7){
		if(RThr->BrightnessIdealRight==0.0 && RThr->BrightnessIdealLeft==0.0){
			int		iMaxR=0;
			for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
				double	dx=r*Vx;
				double	dy=r*Vy;
				double	D=fabs(CalcDeviationDiff(mx+dx ,my+dy ,*TargetImage));
				double	M=D;
				if(M>=MaxD){
					MaxD=M;
					iMaxR=r;
				}
			}
			MaxR=iMaxR;
		}
		else{
			int		iMaxR=0;
			for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
				double	dx=r*Vx;
				double	dy=r*Vy;
				double	D=fabs(CalcDeviationDiff(mx+dx ,my+dy ,*TargetImage
												,RThr->BrightnessIdealRight	,RThr->BrightnessIdealRightRange
												,RThr->BrightnessIdealLeft	,RThr->BrightnessIdealLeftRange));
				double	M=D;
				if(M>=MaxD){
					MaxD=M;
					iMaxR=r;
				}
			}
			MaxR=iMaxR;
		}
	}
	return MaxR;
}


double	MeasureLineMoveLineItem::CalcDeviationDiff(double dx ,double dy ,ImageBuffer &TargetImage)
{
	double	Len=hypot(X1OnMaster-X2OnMaster,Y1OnMaster-Y2OnMaster);
	double	Hx=(X2OnMaster-X1OnMaster)/Len;
	double	Hy=(Y2OnMaster-Y1OnMaster)/Len;

	int	VLen=GetThresholdR()->EdgeWidth;
	double	Vx=-Hy;
	double	Vy=Hx;

	double	A=0;
	double	AA=0;
	int		ANumb=0;
	for(int V=-1;V>=-VLen;V--){
		for(int L=0;L<Len;L++){
			int	Px=(int)(((double)X1OnMaster)+dx+Hx*L)+Vx*V;
			int	Py=(int)(((double)Y1OnMaster)+dy+Hy*L)+Vy*V;
			if(0<=Py && Py<GetMaxLines()
			&& 0<=Px && Px<GetDotPerLine()){
				int	d=TargetImage.GetY(Py)[Px];
				A+=d;
				AA+=d*d;
				ANumb++;
			}
		}
	}
	double	B=0;
	double	BB=0;
	int		BNumb=0;
	for(int V=1;V<=VLen;V++){
		for(int L=0;L<Len;L++){
			int	Px=(int)(((double)X1OnMaster)+dx+Hx*L)+Vx*V;
			int	Py=(int)(((double)Y1OnMaster)+dy+Hy*L)+Vy*V;
			if(0<=Py && Py<GetMaxLines()
			&& 0<=Px && Px<GetDotPerLine()){
				int	d=TargetImage.GetY(Py)[Px];
				B+=d;
				BB+=d*d;
				BNumb++;
			}
		}
	}
	if(ANumb>0 && BNumb>0){
		double	AvrA=A/ANumb;
		double	AvrB=B/BNumb;
		return fabs(AvrA-AvrB)*log(((AvrA>AvrB)?AvrA:AvrB));
		//double	Va=(AA-ANumb*AvrA*AvrA)/ANumb;
		//double	Vb=(BB-BNumb*AvrB*AvrB)/BNumb;
		//if(Va>0 && Va<Vb){
		//	return fabs(Va-Vb)*log(Va);
		//}
		//else if(Vb>0){
		//	return fabs(Va-Vb)*log(Vb);
		//}
		//else{
		//	return fabs(Va-Vb);
		//}
	}
	return 0;
}


double	MeasureLineMoveLineItem::CalcDeviationDiff(double dx ,double dy ,ImageBuffer &TargetImage
													,int Col1,int ColRange1
													,int Col2,int ColRange2)
{
	double	Len=hypot(X1OnMaster-X2OnMaster,Y1OnMaster-Y2OnMaster);
	double	Hx=(X2OnMaster-X1OnMaster)/Len;
	double	Hy=(Y2OnMaster-Y1OnMaster)/Len;

	int	VLen=GetThresholdR()->EdgeWidth;
	double	Vx=-Hy;
	double	Vy=Hx;

	double	A=0;
	double	AA=0;
	double	B=0;
	double	BB=0;
	int		Numb=0;
	for(int V=1;V<=VLen;V++){
		for(int L=0;L<Len;L++){
			int	Px1=(int)(((double)X1OnMaster)+dx+Hx*L)+Vx*V;
			int	Py1=(int)(((double)Y1OnMaster)+dy+Hy*L)+Vy*V;
			int	Px2=(int)(((double)X1OnMaster)+dx+Hx*L)-Vx*V;
			int	Py2=(int)(((double)Y1OnMaster)+dy+Hy*L)-Vy*V;
			if(0<=Py1 && Py1<GetMaxLines()
			&& 0<=Px1 && Px1<GetDotPerLine()
			&& 0<=Py2 && Py2<GetMaxLines()
			&& 0<=Px2 && Px2<GetDotPerLine()){
				int	d1=TargetImage.GetY(Py1)[Px1];
				int	d2=TargetImage.GetY(Py2)[Px2];
				if(((Col1-ColRange1)<=d1 && d1<=(Col1+ColRange1) && (Col2-ColRange2)<=d2 && d2<=(Col2+ColRange2))
				|| ((Col1-ColRange1)<=d2 && d2<=(Col1+ColRange1) && (Col2-ColRange2)<=d1 && d1<=(Col2+ColRange2))){
					B+=d1;
					BB+=d1*d1;
					A+=d2;
					AA+=d2*d2;
					Numb++;
				}
			}
		}
	}
	if(Numb>0){
		double	AvrA=A/Numb;
		double	AvrB=B/Numb;
		return fabs(AvrA-AvrB)*log(((AvrA>AvrB)?AvrA:AvrB));
	}
	return 0;
}

double	MeasureLineMoveLineItem::GetLineAverage(double dx ,double dy ,ImageBuffer &TargetImage)
{
	double	Len=hypot(X1OnMaster-X2OnMaster,Y1OnMaster-Y2OnMaster);
	double	Hx=(X2OnMaster-X1OnMaster)/Len;
	double	Hy=(Y2OnMaster-Y1OnMaster)/Len;
	double	Avr=0;
	int		Numb=0;
	for(int L=0;L<Len;L++){
		int	Px=(int)(((double)X1OnMaster)+dx+Hx*L);
		int	Py=(int)(((double)Y1OnMaster)+dy+Hy*L);
		if(0<=Py && Py<GetMaxLines()
		&& 0<=Px && Px<GetDotPerLine()){
			Avr+=TargetImage.GetY(Py)[Px];
			Numb++;
		}
	}
	if(Numb>0){
		return Avr/Numb;
	}
	return 0;
}

double	MeasureLineMoveLineItem::GetMatchingForType2(int mx ,int my,ImageBuffer &TargetImage)
{
	PureFlexAreaList *R1=AreaRightContainer	.GetFirst();
	PureFlexAreaList *R2=AreaLeftContainer	.GetFirst();
	if(R1!=NULL && R2!=NULL){
		double	DAvr1,V1;
		if(R1->CalcAvrVar(mx ,my ,TargetImage,DAvr1,V1
					,0.5,0.5)==false)
			return 0;
		double	DAvr2,V2;
		if(R2->CalcAvrVar(mx ,my ,TargetImage,DAvr2,V2
					,0.5,0.5)==false)
			return 0;
		/*
		double	V1=R1->GetVar(mx ,my ,TargetImage,DAvr1);
		double	DAvr2;
		double	V2=R2->GetVar(mx ,my ,TargetImage,DAvr2);
		*/
		double	M=max(V1,V2);
		double	LMin=min(DAvr1,DAvr2);
		if(LMin<=0.0)
			return 0;
		if(M==0)
			return 0;
		return fabs(V2-V1)/M/LMin;
	}
	return 0;
}

double	MeasureLineMoveLineItem::GetMatchingForType3(int mx ,int my,ImageBuffer &TargetImage)
{
	PureFlexAreaList *R1=AreaRightContainer	.GetFirst();
	PureFlexAreaList *R2=AreaLeftContainer	.GetFirst();
	if(R1!=NULL && R2!=NULL){
		double	V1=R1->GetAverage(mx ,my ,TargetImage,0.5,0.5);
		double	V2=R2->GetAverage(mx ,my ,TargetImage,0.5,0.5);
		return fabs(V2-V1);
	}
	return 0;
}

double	MeasureLineMoveLineItem::GetMatchingForType4(int mx ,int my,ImageBuffer &TargetImage)
{
	PureFlexAreaList *R1=AreaRightContainer	.GetFirst();
	PureFlexAreaList *R2=AreaLeftContainer	.GetFirst();
	if(R1!=NULL && R2!=NULL){
		double	V1=R1->GetAverage(mx ,my ,TargetImage,0.5,0.5);
		double	V2=R2->GetAverage(mx ,my ,TargetImage,0.5,0.5);
		double	M=hypot(V1,V2);
		if(M==0.0)
			return 0;
		return fabs(V2-V1)/M;
	}
	return 0;
}
double	MeasureLineMoveLineItem::GetAvrageBrightness(int mx ,int my ,PureFlexAreaListContainer &LRArea ,ImageBuffer &TargetImage)
{
	int	n=0;
	double	Avr=0;
	for(PureFlexAreaList *R=LRArea.GetFirst();R!=NULL;R=R->GetNext(),n++){
		Avr+=R->GetAverage(TargetImage,mx,my);
	}
	if(n>0){
		Avr/=n;
	}
	return Avr;
}

double	MeasureLineMoveLineItem::GetIsolation(double x ,double y)
{
	double	A= Y2OnMaster-Y1OnMaster;
	double	B=-X2OnMaster+X1OnMaster;
	double	C=(X2OnMaster-X1OnMaster)*Y1OnMaster-(Y2OnMaster-Y1OnMaster)*X1OnMaster;
	double	M=hypot(A,B);

	if(M>0){
		double	t=-((X1OnMaster-x)*(X2OnMaster-X1OnMaster)+(Y1OnMaster-y)*(Y2OnMaster-Y1OnMaster))/(M*M);
		if(0<=t && t<1.0){
			return fabs(A*x+B*y+C)/M;
		}
	}
	return 99999999;
}

double	MeasureLineMoveLineItem::GetDrawParam(double x ,double y)
{
	if(y==Y1OnMaster){
		return x-X1OnMaster;
	}
	if(x==X1OnMaster){
		return y-Y1OnMaster;
	}
	return hypot(x-X1OnMaster,y-Y1OnMaster);
}
double	MeasureLineMoveLineItem::GetTParam(double x1 ,double y1 ,double x2 ,double y2)
{
	double X ,Y;
	if(GetCrossPoint(X1OnMaster,Y1OnMaster,X2OnMaster,Y2OnMaster,x1,y1,x2,y2 , X ,Y)==true){
		double	M=hypot(X2OnMaster-X1OnMaster,Y2OnMaster-Y1OnMaster);
		double	L=hypot(X-X1OnMaster,Y-Y1OnMaster);
		if(M>0.000001){
			double	A=L/M;
			double	px=X1OnMaster+(X2OnMaster-X1OnMaster)*A;
			double	py=Y1OnMaster+(Y2OnMaster-Y1OnMaster)*A;
			if(hypot(px-X,py-Y)<0.1){
				return L;
			}
			else{
				return -L;
			}
		}
	}
	return 0;
}
void	MeasureLineMoveLineItem::GetDrawPoint(double Param ,double &x ,double &y)
{
	double	dx=X2OnMaster-X1OnMaster;
	double	dy=Y2OnMaster-Y1OnMaster;
	double	M=hypot(dx,dy);
	if(M==0.0){
		x=X1OnMaster;
		y=Y1OnMaster;
	}
	x=dx*Param/M+X1OnMaster;
	y=dy*Param/M+Y1OnMaster;
}

void	MeasureLineMoveLineItem::GetShiftVector(double &sx, double &sy)
{
	sx=ResultShift*Vx+AMx;
	sy=ResultShift*Vy+AMy;
}

double	MeasureLineMoveLineItem::GetDistance(double Px ,double Py)
{
	double	dx=X2OnMaster-X1OnMaster;
	double	dy=Y2OnMaster-Y1OnMaster;
	double	M=hypot(dx,dy);
	if(M==0)
		return 0;
	double	a=dy/M;
	double	b=-dx/M;
	double	c=-a*X1OnMaster-b*Y1OnMaster;
	return a*Px+b*Py+c;
}
void	MeasureLineMoveLineItem::SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)
{
	GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)reqPacket->ItemLine.GetThresholdR()));
	ExecuteProcessing(0,0,Packet->Result);

	Packet->PosDiffX	=ResultShift;
	Packet->PosDiffY	=0;
	Packet->Error		=0;
}

bool	MeasureLineMoveLineItem::IsInclude(int x ,int y)	const
{
	if(((MeasureLineMoveLineItem *)this)->AreaRightContainer.IsInclude(x-ResultShift*Vx,y-ResultShift*Vy)==true)
		return true;
	if(((MeasureLineMoveLineItem *)this)->AreaLeftContainer.IsInclude(x-ResultShift*Vx,y-ResultShift*Vy)==true)
		return true;
	return false;
}

void	MeasureLineMoveLineItem::MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
												,bool EnableMakeImage ,bool EnableDrawLine)
{
	int	ImageWL=TResultImage.width();
	int	ImageHL=TResultImage.height();

	if(ImageWL!=0 && ImageHL!=0){
		double	cx,cy;
		GetCenterPoint(cx,cy);
		double	sx,sy;
		GetShiftVector(sx,sy);

		ImagePointerContainer TargetImageList;
		GetTargetBuffList(TargetImageList);

		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);

		double	Zx=99999999;
		double	Zy=99999999;
		if(x1!=x2)
			Zx=ImageWL/((double)(x2-x1));
		if(y1!=y2)
			Zy=ImageHL/((double)(y2-y1));

		ImageZoomRate=min(Zx,Zy);
		double	Z=1.0/ImageZoomRate;

		ImageX1=cx+sx-ImageWL*Z/2.0;
		ImageY1=cy+sy-ImageHL*Z/2.0;
		if(EnableMakeImage==true){
			TargetImageList.MakeImage(TResultImage,-ImageX1,-ImageY1,ImageZoomRate,false);
		}

		LResultImage.fill(qRgba(0,0,0,0));
		VectorLineDouble	*v=(VectorLineDouble *)GetVector();
		VectorItemBase	*V1	=v->GetItemAt(0);
		VectorItemBase	*V2	=v->GetItemAt(1);
		if(V1!=NULL && V2!=NULL){
			int	x1=X1OnMaster;
			int	y1=Y1OnMaster;
			int	x2=X2OnMaster;
			int	y2=Y2OnMaster;

			int	MovX=-(ImageX1-sx);
			int	MovY=-(ImageY1-sy);
			if(EnableDrawLine==true){
				QPainter	Pnt(&LResultImage);
				Pnt.setPen(Qt::yellow);
				Pnt.drawLine((x1+MovX)*ImageZoomRate,(y1+MovY)*ImageZoomRate
							,(x2+MovX)*ImageZoomRate,(y2+MovY)*ImageZoomRate);
				
				Pnt.setPen(Qt::red);
				//int	Rnd=+GetID()%5;
				Pnt.drawLine((x1+MovX+sx)*ImageZoomRate,(y1+MovY+sy)*ImageZoomRate
							,(x2+MovX+sx)*ImageZoomRate,(y2+MovY+sy)*ImageZoomRate);
			}
		}
	}
}
//=================================================================================

MeasureLineMoveRxLineItem::MeasureLineMoveRxLineItem(void)
{
	HookedItem	=NULL;

	X1OnMaster	=0;
	Y1OnMaster	=0;
	X2OnMaster	=0;
	Y2OnMaster	=0;
	Vx=0;
	Vy=0;
	ResultShift		=0;

	HookedItemID	=-1;
	RxID			=0;
	Received		=false;
}


bool	MeasureLineMoveRxLineItem::Save(QIODevice *f)
{
	int32	Ver=1;

	if(MeasureLineMoveItemBase::Save(f)==false)
		return false;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,X1OnMaster)==false)
		return false;
	if(::Save(f,Y1OnMaster)==false)
		return false;
	if(::Save(f,X2OnMaster)==false)
		return false;
	if(::Save(f,Y2OnMaster)==false)
		return false;

	if(::Save(f,HookedItemID)==false)
		return false;
	if(::Save(f,RxID)==false)
		return false;
	return true;
}
bool	MeasureLineMoveRxLineItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(MeasureLineMoveItemBase::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,X1OnMaster)==false)
		return false;
	if(::Load(f,Y1OnMaster)==false)
		return false;
	if(::Load(f,X2OnMaster)==false)
		return false;
	if(::Load(f,Y2OnMaster)==false)
		return false;

	if(::Load(f,HookedItemID)==false)
		return false;
	if(::Load(f,RxID)==false)
		return false;

	return true;
}
bool	MeasureLineMoveRxLineItem::Transform(TransformBase &Param)
{
	double	tPosX1	;
	double	tPosY1	;
	double	tPosX2	;
	double	tPosY2	;
	Param.Transform(X1OnMaster,Y1OnMaster,tPosX1,tPosY1);
	Param.Transform(X2OnMaster,Y2OnMaster,tPosX2,tPosY2);
	X1OnMaster	=tPosX1;
	Y1OnMaster	=tPosY1;
	X2OnMaster	=tPosX2;
	Y2OnMaster	=tPosY2;

	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}

	return true;
}

void	MeasureLineMoveRxLineItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveRxLineItem *src=(MeasureLineMoveRxLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			HookedItemID	=src->HookedItemID;
			RxID			=src->RxID;
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureLineMoveLineItem *)Data)->GetLibID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveLineItem *src=(MeasureLineMoveLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
}
AlgorithmItemPI	&MeasureLineMoveRxLineItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureLineMoveItemBase::operator=(src);

	const MeasureLineMoveRxLineItem	*p=dynamic_cast<const MeasureLineMoveRxLineItem *>(&src);
	if(p!=NULL){
		X1OnMaster	=p->X1OnMaster;
		Y1OnMaster	=p->Y1OnMaster;
		Y2OnMaster	=p->Y2OnMaster;
		Y2OnMaster	=p->Y2OnMaster;
		HookedItemID=p->HookedItemID;
		RxID		=p->RxID;
	}

	return *this;
}

VectorLineBase	*MeasureLineMoveRxLineItem::CreateVectorBase(void)
{
	VectorLineDouble	*R=new VectorLineDouble();
	R->AppendItemBase(R->CreateItem());
	R->AppendItemBase(R->CreateItem());
	return R;
}

bool	MeasureLineMoveRxLineItem::SetLocalData(MeasureLineMoveInPage *ParentPage)
{
	if(GetVector()==NULL)
		return false;

	VectorItemBase	*d1=GetVector()->GetFirstItem();
	if(d1==NULL){
		return false;
	}
	VectorItemBase	*d2=d1->GetNext();
	if(d2==NULL){
		return false;
	}
	VectorItemDouble	*v1=dynamic_cast<VectorItemDouble *>(d1);
	VectorItemDouble	*v2=dynamic_cast<VectorItemDouble *>(d2);
	if(v1==NULL || v2==NULL){
		return false;
	}
	X1OnMaster	=v1->GetX();
	Y1OnMaster	=v1->GetY();
	X2OnMaster	=v2->GetX();
	Y2OnMaster	=v2->GetY();

	return true;
}
void	MeasureLineMoveRxLineItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::MoveTo(GlobalDx ,GlobalDy);
		X1OnMaster+=GlobalDx;
		Y1OnMaster+=GlobalDy;
		X2OnMaster+=GlobalDx;
		Y2OnMaster+=GlobalDy;
	}
}

void	MeasureLineMoveRxLineItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	int	x1=(X1OnMaster+movx)*ZoomRate;
	int	y1=(Y1OnMaster+movy)*ZoomRate;

	int	x2=(X2OnMaster+movx)*ZoomRate;
	int	y2=(Y2OnMaster+movy)*ZoomRate;

	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(x1,y1,x2,y2);
}

void	MeasureLineMoveRxLineItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		VectorLineDouble	*v=(VectorLineDouble *)GetVector();
		VectorItemBase	*V1	=v->GetItemAt(0);
		VectorItemBase	*V2	=v->GetItemAt(1);
		if(V1!=NULL && V2!=NULL){
			int	x1=X1OnMaster;
			int	y1=Y1OnMaster;
			int	x2=X2OnMaster;
			int	y2=Y2OnMaster;

			PData.setPen(Qt::yellow);
			PData.drawLine((x1+MovX)*ZoomRate,(y1+MovY)*ZoomRate
						  ,(x2+MovX)*ZoomRate,(y2+MovY)*ZoomRate);
			
			if(Received==true){
				PData.setPen(Qt::red);
				//int	Rnd=+GetID()%5;
				PData.drawLine((x1+ResultShift*Vx+MovX+Res->GetAlignedX())*ZoomRate,(y1+ResultShift*Vy+MovY+Res->GetAlignedY())*ZoomRate
							  ,(x2+ResultShift*Vx+MovX+Res->GetAlignedX())*ZoomRate,(y2+ResultShift*Vy+MovY+Res->GetAlignedY())*ZoomRate);
			}
			if(IsUnitMode()==true){
				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate
								,QString::number(GetID())+QString(":")+TransformPixelToUnitStr(ResultShift)
																		+QString(" (")
																		+QString::number(ResultShift)
																		+QString(")")
																		);

				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate+20
								,QString("Dx,Dy=")  +TransformPixelToUnitStr(Res->GetAlignedX())
													+QString(" (")
													+QString::number(Res->GetAlignedX())
													+QString("),")
													+TransformPixelToUnitStr(Res->GetAlignedY())
													+QString(" (")
													+QString::number(Res->GetAlignedY())
													+QString(")")
													);
			}
			else{
				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate
								,QString::number(GetID())+QString(":")+QString::number(ResultShift));

				PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
								,((y1+y2)/2+MovY)*ZoomRate+20
								,QString("Dx,Dy=")+QString::number(Res->GetAlignedX())+QString(",")+QString::number(Res->GetAlignedY()));
			}
		}
	}
}
void	MeasureLineMoveRxLineItem::DrawNumber(QImage &IData ,QPainter &PData
											,int MovX ,int MovY ,double ZoomRate
											,int Number)
{
	int	x1=X1OnMaster;
	int	y1=Y1OnMaster;
	int	x2=X2OnMaster;
	int	y2=Y2OnMaster;
	PData.setBrush(Qt::green);
	PData.setPen(Qt::green);
	PData.drawText(  ((x1+x2)/2+MovX)*ZoomRate
					,((y1+y2)/2+MovY)*ZoomRate+32
					,QString::number(Number));
}

void	MeasureLineMoveRxLineItem::GetCenterPoint(double &cx, double &cy)
{
	cx=(X1OnMaster+X2OnMaster)/2.0;
	cy=(Y1OnMaster+Y2OnMaster)/2.0;
}

void	MeasureLineMoveRxLineItem::Move(double dx ,double dy)
{
	ExecuteMove(dx,dy,true);
}

void	MeasureLineMoveRxLineItem::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx=(X1OnMaster+X2OnMaster)/2;
		int	cy=(Y1OnMaster+Y2OnMaster)/2;
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	Move(mx,my);
}

ExeResult	MeasureLineMoveRxLineItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(EInfo);
	SetLocalData((MeasureLineMoveInPage *)GetParentInPage());
	double	A= Y2OnMaster-Y1OnMaster;
	double	B=-X2OnMaster+X1OnMaster;
	double	M=hypot(A,B);

	Vx=0;
	Vy=0;

	if(M>0){
		Vx=A/M;
		Vy=B/M;

		Hx=-B/M;
		Hy= A/M;
	}
	ResultShift=0;
	HookedItem	=dynamic_cast<MeasureCommon *>(GetParentInPage()->SearchIDItem(HookedItemID));

	return _ER_true;
}


ExeResult	MeasureLineMoveRxLineItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	Res->SetAlignedXY(0,0);
	AMx=0;
	AMy=0;
	Received=false;

	if(HookedItem==NULL){
		HookedItem	=dynamic_cast<MeasureCommon *>(GetParentInPage()->SearchIDItem(HookedItemID));
	}
	if(HookedItem!=NULL){
		double	HookedCx,HookedCy;
		HookedItem->GetCenterPoint(HookedCx,HookedCy);
		double	HookedSx,HookedSy;
		HookedItem->GetShiftVector(HookedSx,HookedSy);
		double	Qx=HookedCx+HookedSx;
		double	Qy=HookedCy+HookedSy;

		double	Px,Py;
		GetCenterPoint(Px,Py);

		MeasureLineMoveInPage	*Ap=(MeasureLineMoveInPage *)GetParentInPage();
		TransferItem	*f=Ap->FindTransferItem(GetLayersBase()->GetCurrentInspectIDForExecute(),RxID);
		if(f==NULL){
			f=Ap->FindTransferItem(GetLayersBase()->GetCurrentInspectIDForExecute()-1,RxID);
		}
		double	PixelLen=0;
		if(f!=NULL){
			QBuffer	Buff(&f->Data);
			Buff.open(QIODevice::ReadWrite);
			double	RealLen;
			if(::Load(&Buff,RealLen)==true && isfinite(RealLen)==true){
				PixelLen=TransformPixelFromUnit(RealLen);
				Received=true;
			}
		}

		//Px+Vx*t+Hx*s=Qx
		//Py+Vy*t+Hy*s=Qy

		//(Px+Vx*t)*Hy-(Py+Vy*t)*Hx=Qx*Hy-Qy*Hx
		//(Vx*Hy-Vy*Hx)t=Qx*Hy-Qy*Hx-(Px*Hy-Py*Hx)

		double	M=Vx*Hy-Vy*Hx;
		double	t=(Qx*Hy-Qy*Hx-(Px*Hy-Py*Hx))/M;
		
		//(Px+Hx*s)*Vy-(Py+Hy*s)*Vx=Qx*Vy-Qy*Vx
		//Px*Vy-Py*Vx+(Hx*Vy-Hy*Vx)*s=Qx*Vy-Qy*Vx
		double	s=-(Qx*Vy-Qy*Vx-(Px*Vy-Py*Vx))/M;

		if(t>0){
			double	Ux=Qx-Hx*s-PixelLen*Vx;
			double	Uy=Qy-Hy*s-PixelLen*Vy;
			ResultShift=t-PixelLen;
		}
		else{
			double	Ux=Qx-Hx*s+PixelLen*Vx;
			double	Uy=Qy-Hy*s+PixelLen*Vy;
			ResultShift=PixelLen+t;
		}

	}
	//ResultShift=MaxR+OffsetForDark;
	SetCalcDone(true);
	return _ER_true;
}


double	MeasureLineMoveRxLineItem::GetIsolation(double x ,double y)
{
	double	A= Y2OnMaster-Y1OnMaster;
	double	B=-X2OnMaster+X1OnMaster;
	double	C=(X2OnMaster-X1OnMaster)*Y1OnMaster-(Y2OnMaster-Y1OnMaster)*X1OnMaster;
	double	M=hypot(A,B);

	if(M>0){
		double	t=-((X1OnMaster-x)*(X2OnMaster-X1OnMaster)+(Y1OnMaster-y)*(Y2OnMaster-Y1OnMaster))/(M*M);
		if(0<=t && t<1.0){
			return fabs(A*x+B*y+C)/M;
		}
	}
	return 99999999;
}

double	MeasureLineMoveRxLineItem::GetDrawParam(double x ,double y)
{
	return hypot(x-X1OnMaster,y-Y1OnMaster);
}
double	MeasureLineMoveRxLineItem::GetTParam(double x1 ,double y1 ,double x2 ,double y2)
{
	double X ,Y;
	if(GetCrossPoint(X1OnMaster,Y1OnMaster,X2OnMaster,Y2OnMaster,x1,y1,x2,y2 , X ,Y)==true){
		double	M=hypot(X2OnMaster-X1OnMaster,Y2OnMaster-Y1OnMaster);
		double	L=hypot(X-X1OnMaster,Y-Y1OnMaster);
		if(M>0.000001){
			double	A=L/M;
			double	px=X1OnMaster+(X2OnMaster-X1OnMaster)*A;
			double	py=Y1OnMaster+(Y2OnMaster-Y1OnMaster)*A;
			if(hypot(px-X,py-Y)<0.1){
				return L;
			}
			else{
				return -L;
			}
		}
	}
	return 0;
}
void	MeasureLineMoveRxLineItem::GetDrawPoint(double Param ,double &x ,double &y)
{
	double	dx=X2OnMaster-X1OnMaster;
	double	dy=Y2OnMaster-Y1OnMaster;
	double	M=hypot(dx,dy);
	if(M==0.0){
		x=X1OnMaster;
		y=Y1OnMaster;
	}
	x=dx*Param/M+X1OnMaster;
	y=dy*Param/M+Y1OnMaster;
}

void	MeasureLineMoveRxLineItem::GetShiftVector(double &sx, double &sy)
{
	sx=ResultShift*Vx+AMx;
	sy=ResultShift*Vy+AMy;
}

double	MeasureLineMoveRxLineItem::GetDistance(double Px ,double Py)
{
	double	dx=X2OnMaster-X1OnMaster;
	double	dy=Y2OnMaster-Y1OnMaster;
	double	M=hypot(dx,dy);
	if(M==0)
		return 0;
	double	a=dy/M;
	double	b=-dx/M;
	double	c=-a*X1OnMaster-b*Y1OnMaster;
	return a*Px+b*Py+c;
}
void	MeasureLineMoveRxLineItem::SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)
{
	GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)reqPacket->ItemLine.GetThresholdR()));
	ExecuteProcessing(0,0,Packet->Result);

	Packet->PosDiffX	=ResultShift;
	Packet->PosDiffY	=0;
	Packet->Error		=0;
}

bool	MeasureLineMoveRxLineItem::IsInclude(int x ,int y)	const
{
	if(GetLengthLine2Point(X1OnMaster,Y1OnMaster,X2OnMaster,Y2OnMaster,(double)x  ,(double)y)<10)
		return true;
	return false;
}

void	MeasureLineMoveRxLineItem::MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
												,bool EnableMakeImage ,bool EnableDrawLine)
{
	int	ImageWL=TResultImage.width();
	int	ImageHL=TResultImage.height();

	if(ImageWL!=0 && ImageHL!=0){
		double	cx,cy;
		GetCenterPoint(cx,cy);
		double	sx,sy;
		GetShiftVector(sx,sy);

		ImagePointerContainer TargetImageList;
		GetTargetBuffList(TargetImageList);

		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);

		double	Zx=99999999;
		double	Zy=99999999;
		if(x1!=x2)
			Zx=ImageWL/((double)(x2-x1));
		if(y1!=y2)
			Zy=ImageHL/((double)(y2-y1));

		ImageZoomRate=min(Zx,Zy);
		double	Z=1.0/ImageZoomRate;

		ImageX1=cx+sx-ImageWL*Z/2.0;
		ImageY1=cy+sy-ImageHL*Z/2.0;
		if(EnableMakeImage==true){
			TargetImageList.MakeImage(TResultImage,-ImageX1,-ImageY1,ImageZoomRate,false);
		}

		LResultImage.fill(qRgba(0,0,0,0));
		VectorLineDouble	*v=(VectorLineDouble *)GetVector();
		VectorItemBase	*V1	=v->GetItemAt(0);
		VectorItemBase	*V2	=v->GetItemAt(1);
		if(V1!=NULL && V2!=NULL){
			int	x1=X1OnMaster;
			int	y1=Y1OnMaster;
			int	x2=X2OnMaster;
			int	y2=Y2OnMaster;

			int	MovX=-(ImageX1-sx);
			int	MovY=-(ImageY1-sy);
			if(EnableDrawLine==true){
				QPainter	Pnt(&LResultImage);
				Pnt.setPen(Qt::yellow);
				Pnt.drawLine((x1+MovX)*ImageZoomRate,(y1+MovY)*ImageZoomRate
							,(x2+MovX)*ImageZoomRate,(y2+MovY)*ImageZoomRate);
				
				Pnt.setPen(Qt::red);
				//int	Rnd=+GetID()%5;
				Pnt.drawLine((x1+MovX+sx)*ImageZoomRate,(y1+MovY+sy)*ImageZoomRate
							,(x2+MovX+sx)*ImageZoomRate,(y2+MovY+sy)*ImageZoomRate);
			}
		}
	}
}

double	MeasureLineMoveRxLineItem::TrasnformUnitFromPixel(double Pixel)
{
	double	RealLen=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),Pixel*Vx,Pixel*Vy);
	return RealLen;
}
double	MeasureLineMoveRxLineItem::TransformPixelFromUnit(double Unit)
{
	double	RealLen=GetParamGlobal()->TransformUnitDistanceToPixel(GetPage(),Unit*Vx,Unit*Vy);
	return RealLen;
}

//=======================================================================================================

MeasureLineMoveCornerRItem::MeasureLineMoveCornerRItem(void)
{
	CxOnMaster	=0;
	CyOnMaster	=0;
	RxOnMaster	=0;
	RyOnMaster	=0;
	AngleS1		=0;
	AngleS2		=0;

	Avr1I	=0.0;
	Avr1O	=0.0;
	Avr2I	=0.0;
	Avr2O	=0.0;
	Avr3I	=0.0;
	Avr3O	=0.0;

	Vx1=Vy1	=0;
	Vx2=Vy2	=0;
	Vx3=Vy3	=0;
	Cx1=Cy1	=0;
	Cx2=Cy2	=0;
	Cx3=Cy3	=0;

	ResultDifR	=0;
	ResultCx=ResultCy	=0;
}


bool	MeasureLineMoveCornerRItem::Save(QIODevice *f)
{
	int32	Ver=1;

	if(MeasureLineMoveItemBase::Save(f)==false)
		return false;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,CxOnMaster)==false)
		return false;
	if(::Save(f,CyOnMaster)==false)
		return false;
	if(::Save(f,RxOnMaster)==false)
		return false;
	if(::Save(f,RyOnMaster)==false)
		return false;
	if(::Save(f,AngleS1)==false)
		return false;
	if(::Save(f,AngleS2)==false)
		return false;
	return true;
}
bool	MeasureLineMoveCornerRItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(MeasureLineMoveItemBase::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,CxOnMaster)==false)
		return false;
	if(::Load(f,CyOnMaster)==false)
		return false;
	if(::Load(f,RxOnMaster)==false)
		return false;
	if(::Load(f,RyOnMaster)==false)
		return false;
	if(::Load(f,AngleS1)==false)
		return false;
	if(::Load(f,AngleS2)==false)
		return false;
	return true;
}
bool	MeasureLineMoveCornerRItem::Transform(TransformBase &Param)
{
	double	Sx=RxOnMaster*cos(AngleS1);
	double	Sy=RyOnMaster*sin(AngleS1);
	double	tSx;
	double	tSy;
	double	tCenterX	;
	double	tCenterY	;
	double	Ex=RxOnMaster*cos(AngleS2);
	double	Ey=RyOnMaster*sin(AngleS2);
	double	tEx;
	double	tEy;
	double	MiddleAngle=::GetMiddleAngle(AngleS1 ,AngleS2);
	double	Mx=RxOnMaster*cos(MiddleAngle);
	double	My=RyOnMaster*sin(MiddleAngle);
	double	tMx;
	double	tMy;

	Param.Transform(CxOnMaster,CyOnMaster,tCenterX,tCenterY);
	Param.Transform(Sx,Sy,tSx,tSy);
	Param.Transform(Ex,Ey,tEx,tEy);
	double	Gx,Gy;
	Param.Transform(0,0,Gx,Gy);
	Param.Transform(Mx,My,tMx,tMy);

	CxOnMaster	=tCenterX;
	CyOnMaster	=tCenterY;
	RxOnMaster	=hypot(tSx-Gx,tSy-Gy);
	RyOnMaster	=hypot(tSx-Gx,tSy-Gy);
	AngleS1	=GetSita(tSx-Gx,tSy-Gy);
	AngleS2	=GetSita(tEx-Gx,tEy-Gy);
	MiddleAngle	=GetSita(tMx-Gx,tMy-Gy);
	if(IsInsideAngle(MiddleAngle,AngleS1,AngleS2)==false){
		swap(AngleS1,AngleS2);
	}
	FlexArea	tArea=GetArea().Transform(Param);
	SetArea(tArea);
	if(GetVector()!=NULL){
		GetVector()->Transform(Param);
	}
	return true;
}

AlgorithmItemPI	&MeasureLineMoveCornerRItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureLineMoveItemBase::operator=(src);

	const MeasureLineMoveCornerRItem	*p=dynamic_cast<const MeasureLineMoveCornerRItem *>(&src);
	if(p!=NULL){
		CxOnMaster	=p->CxOnMaster;
		CyOnMaster	=p->CyOnMaster;
		RxOnMaster	=p->RxOnMaster;
		RyOnMaster	=p->RyOnMaster;
		AngleS1		=p->AngleS1;
		AngleS2		=p->AngleS2;
	}

	return *this;
}
void	MeasureLineMoveCornerRItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::MoveTo(GlobalDx,GlobalDy);
		CxOnMaster+=GlobalDx;
		CyOnMaster+=GlobalDy;
		Cx1+=GlobalDx;
		Cy1+=GlobalDy;
		Cx2+=GlobalDx;
		Cy2+=GlobalDy;
		Cx3+=GlobalDx;
		Cy3+=GlobalDy;
		AreaWithIdeal1.MoveToNoClip(GlobalDx,GlobalDy);
		AreaWithIdeal2.MoveToNoClip(GlobalDx,GlobalDy);
		AreaWithIdeal3.MoveToNoClip(GlobalDx,GlobalDy);

		Area1I.MoveToNoClip(GlobalDx,GlobalDy);
		Area1O.MoveToNoClip(GlobalDx,GlobalDy);
		Area2I.MoveToNoClip(GlobalDx,GlobalDy);
		Area2O.MoveToNoClip(GlobalDx,GlobalDy);
		Area3I.MoveToNoClip(GlobalDx,GlobalDy);
		Area3O.MoveToNoClip(GlobalDx,GlobalDy);
	}
}

void	MeasureLineMoveCornerRItem::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
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
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ExecuteMove(mx,my,true);
}
void	MeasureLineMoveCornerRItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	QColor	col(Qt::green);
	col.setAlpha(128);
	AreaWithIdeal1.DrawAlpha(0,0 ,&pnt ,col.rgba() ,ZoomRate ,movx ,movy);
	AreaWithIdeal2.DrawAlpha(0,0 ,&pnt ,col.rgba() ,ZoomRate ,movx ,movy);
	AreaWithIdeal3.DrawAlpha(0,0 ,&pnt ,col.rgba() ,ZoomRate ,movx ,movy);

	QColor	col2(Qt::red);
	col2.setAlpha(128);
	Area1I.DrawAlpha(0,0 ,&pnt ,col2.rgba() ,ZoomRate ,movx ,movy);
	Area2I.DrawAlpha(0,0 ,&pnt ,col2.rgba() ,ZoomRate ,movx ,movy);
	Area3I.DrawAlpha(0,0 ,&pnt ,col2.rgba() ,ZoomRate ,movx ,movy);

	double	s=AngleS2-AngleS1;
	while(s<0){
		s+=2.0*M_PI;
	}
	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::yellow);
	Pnt.drawArc ( (CxOnMaster-RxOnMaster+movx)*ZoomRate, (CyOnMaster-RyOnMaster+movy)*ZoomRate
		, RxOnMaster*2.0*ZoomRate, RyOnMaster*2.0*ZoomRate
		,(int)16*360*(1.0-AngleS2/(2.0*M_PI)) 
		,(int)(s*16*360/(2.0*M_PI)));

	if(ZoomRate>2.0){
		Pnt.setPen(Qt::red);
		Pnt.setBrush(Qt::cyan);
		int	R=GetThresholdR()->SearchDot;
		DrawArrow(Cx1,Cy1,Cx1+Vx1*R,Cy1+Vy1*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
		DrawArrow(Cx1,Cy1,Cx1-Vx1*R,Cy1-Vy1*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);

		DrawArrow(Cx2,Cy2,Cx2+Vx2*R,Cy2+Vy2*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
		DrawArrow(Cx2,Cy2,Cx2-Vx2*R,Cy2-Vy2*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);

		DrawArrow(Cx3,Cy3,Cx3+Vx3*R,Cy3+Vy3*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
		DrawArrow(Cx3,Cy3,Cx3-Vx3*R,Cy3-Vy3*R
				 ,Pnt ,movx ,movy ,ZoomRate,30);
	}

}

VectorLineBase	*MeasureLineMoveCornerRItem::CreateVectorBase(void)
{
	VectorLineArc	*R=new VectorLineArc();
	R->SetArc(CxOnMaster,CyOnMaster,(RxOnMaster+RyOnMaster)/2.0,AngleS1,AngleS2);
	return R;
}

bool	MeasureLineMoveCornerRItem::SetLocalData(MeasureLineMoveInPage *ParentPage)
{
	if(GetVector()==NULL)
		return false;
	VectorLineArc	*R=dynamic_cast<VectorLineArc *>(GetVector());
	if(R==NULL){
		return false;
	}
	R->GetArc(CxOnMaster,CyOnMaster,RxOnMaster,AngleS1,AngleS2);
	RyOnMaster=RxOnMaster;

	return true;
}

void	MeasureLineMoveCornerRItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	//VectorLineArc	*R=(VectorLineArc *)GetVector();
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		PData.setPen(Qt::yellow);
		double	s=AngleS2-AngleS1;
		while(s<0){
			s+=2.0*M_PI;
		}
		PData.drawArc ( (CxOnMaster-RxOnMaster+MovX)*ZoomRate, (CyOnMaster-RyOnMaster+MovY)*ZoomRate
						, RxOnMaster*2.0*ZoomRate, RyOnMaster*2.0*ZoomRate
						,(int)16*360*(1.0-AngleS2/(2.0*M_PI)) 
						,(int)(s*16*360/(2.0*M_PI)));

		PData.setPen(Qt::red);
		//double	Rnd=((GetID()%11)-5)*0.5;

		double	RxR=RxOnMaster+ResultDifR;
		double	RyR=RyOnMaster+ResultDifR;
		PData.drawArc ( (ResultCx-RxR+MovX+Res->GetAlignedX())*ZoomRate, (ResultCy-RyR+MovY+Res->GetAlignedY())*ZoomRate
						, RxR*2.0*ZoomRate, RyR*2.0*ZoomRate
						,(int)16*360*(1.0-AngleS2/(2.0*M_PI)) 
						,(int)(s*16*360/(2.0*M_PI)));
		double	hs=(AngleS2+AngleS1)/2;
		int	kx=CxOnMaster+RxOnMaster*cos(hs);
		int	ky=CyOnMaster+RyOnMaster*sin(hs);

		PData.drawText(  (kx+MovX)*ZoomRate
						,(ky+MovY)*ZoomRate
						,QString("Diff:")+QString::number(ResultDifR));
		PData.drawText(  (kx+MovX)*ZoomRate
						,(ky+MovY)*ZoomRate+16
						,QString("R:")+QString::number(RxR));
	}
}

ExeResult	MeasureLineMoveCornerRItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(EInfo);
	ExecuteInitialAfterEditMakeC(EInfo);

	AVector=(AlignmentPacket2D *)GetAlignmentPointer(Cx2,Cy2);
	if(AVector!=NULL)
		AVector->Set(this);


	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);	
	
	double	r1=ExecuteProcessingInner ( 0,0,MasterImageList ,AreaWithIdeal1	,Area1I,Avr1I ,Area1O,Avr1O ,Vx1 ,Vy1);
	double	r2=ExecuteProcessingInner ( 0,0,MasterImageList ,AreaWithIdeal2	,Area2I,Avr2I ,Area2O,Avr2O ,Vx2 ,Vy2);
	double	r3=ExecuteProcessingInner ( 0,0,MasterImageList ,AreaWithIdeal3	,Area3I,Avr3I ,Area3O,Avr3O ,Vx3 ,Vy3);

	VectorLineArc	V;
	V.SetPoints( Cx1+r1*Vx1, Cy1+r1*Vy1
				,Cx2+r2*Vx2, Cy2+r2*Vy2
				,Cx3+r3*Vx3, Cy3+r3*Vy3);

	double	tR ,tStartS ,tEndS;
	V.GetArc(ResultCx,ResultCy ,tR ,tStartS ,tEndS);

	CxOnMaster=ResultCx;
	CyOnMaster=ResultCy;
	RxOnMaster=tR;
	RyOnMaster=tR;

	ExecuteInitialAfterEditMakeC(EInfo);

	return _ER_true;
}
void	MeasureLineMoveCornerRItem::ExecuteInitialAfterEditMakeC(ExecuteInitialAfterEditInfo &EInfo)
{
	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);
	AreaWithIdeal1.Clear();
	AreaWithIdeal2.Clear();
	AreaWithIdeal3.Clear();

	double	Dif3;
	if(AngleS2<AngleS1){
		Dif3	=(2*M_PI+AngleS2-AngleS1)/5;
	}
	else{
		Dif3	=(AngleS2-AngleS1)/5;
	}
	MakeArcArea(RegulateAngle(AngleS1+Dif3*0) ,RegulateAngle(AngleS1+Dif3*1),AreaWithIdeal1,Area1I,Area1O);
	MakeArcArea(RegulateAngle(AngleS1+Dif3*2) ,RegulateAngle(AngleS1+Dif3*3),AreaWithIdeal2,Area2I,Area2O);
	MakeArcArea(RegulateAngle(AngleS1+Dif3*4) ,RegulateAngle(AngleS1+Dif3*5),AreaWithIdeal3,Area3I,Area3O);

	AreaWithIdeal1.SetAndCalc(*MasterImageList[0]);
	AreaWithIdeal2.SetAndCalc(*MasterImageList[0]);
	AreaWithIdeal3.SetAndCalc(*MasterImageList[0]);
	MakeIdeal(AreaWithIdeal1);
	MakeIdeal(AreaWithIdeal2);
	MakeIdeal(AreaWithIdeal3);
	AreaWithIdeal1.MakeSum();
	AreaWithIdeal2.MakeSum();
	AreaWithIdeal3.MakeSum();

	Avr1I=Area1I.GetAverage(*MasterImageList[0],0,0);
	Avr1O=Area1O.GetAverage(*MasterImageList[0],0,0);
	Avr2I=Area2I.GetAverage(*MasterImageList[0],0,0);
	Avr2O=Area2O.GetAverage(*MasterImageList[0],0,0);
	Avr3I=Area3I.GetAverage(*MasterImageList[0],0,0);
	Avr3O=Area3O.GetAverage(*MasterImageList[0],0,0);

	double	Mid1=AngleS1+Dif3*0+Dif3/2;
	double	Mid2=AngleS1+Dif3*2+Dif3/2;
	double	Mid3=AngleS1+Dif3*4+Dif3/2;
	double	R=hypot(RxOnMaster,RyOnMaster);
	Cx1=CxOnMaster+RxOnMaster*cos(Mid1);
	Cy1=CyOnMaster+RyOnMaster*sin(Mid1);
	Cx2=CxOnMaster+RxOnMaster*cos(Mid2);
	Cy2=CyOnMaster+RyOnMaster*sin(Mid2);
	Cx3=CxOnMaster+RxOnMaster*cos(Mid3);
	Cy3=CyOnMaster+RyOnMaster*sin(Mid3);
	Vx1=RxOnMaster*cos(Mid1)/R;
	Vy1=RyOnMaster*sin(Mid1)/R;
	Vx2=RxOnMaster*cos(Mid2)/R;
	Vy2=RyOnMaster*sin(Mid2)/R;
	Vx3=RxOnMaster*cos(Mid3)/R;
	Vy3=RyOnMaster*sin(Mid3)/R;

}

void	MeasureLineMoveCornerRItem::MakeArcArea(double StartS ,double EndS 
												,FlexAreaImageListCoeff &Area
												,FlexArea &AreaI
												,FlexArea &AreaO)
{
	int	R	=GetThresholdR()->EdgeWidth;

	int	x1	=floor(CxOnMaster-RxOnMaster-R);
	int	y1	=floor(CyOnMaster-RyOnMaster-R);
	int	x2	=ceil(CxOnMaster+RxOnMaster+R);
	int	y2	=ceil(CyOnMaster+RyOnMaster+R);

	try{
		struct FlexLine	*Dim=new struct FlexLine[(y2-y1+1)*2+2];
		int	Len=0;
		for(int y=y1;y<y2;y++){
			int x=x1;
			while(x<x2){
				for(;x<x2;x++){
					double	dx=x-CxOnMaster;
					double	dy=y-CyOnMaster;
					double	s=GetSita(dx,dy);
					if((StartS<EndS && StartS<=s && s<=EndS) || (StartS>EndS && (StartS<=s || s<=EndS))){
						double	r=fabs(hypot(dx,dy)-RxOnMaster);
						if(r<=R){
							break;
						}
					}
				}
				if(x<x2){
					int	kx1=x;
					x++;
					for(;x<x2;x++){
						double	dx=x-CxOnMaster;
						double	dy=y-CyOnMaster;
						double	s=GetSita(dx,dy);
						if((StartS<EndS && (s<StartS || EndS<s)) || (StartS>EndS && (s<StartS && EndS<s))){
							break;
						}
						double	r=fabs(hypot(dx,dy)-RxOnMaster);
						if(r>R){
							break;
						}
					}
					int	kx2=x;
					Dim[Len]._Set(kx1,kx2-1,y);
					Len++;
				}
			}
		}
		Area.SetFLine(Dim,Len);
	}
	catch(...){}

	double	R2=R/2.0;
	try{
		struct FlexLine	*Dim=new struct FlexLine[(y2-y1+1)*2+2];
		int	Len=0;
		for(int y=y1;y<y2;y++){
			int x=x1;
			while(x<x2){
				for(;x<x2;x++){
					double	dx=x-CxOnMaster;
					double	dy=y-CyOnMaster;
					double	s=GetSita(dx,dy);
					if((StartS<EndS && StartS<=s && s<=EndS) || (StartS>EndS && (StartS<=s || s<=EndS))){
						double	r=fabs(hypot(dx,dy)-(RxOnMaster-R2));
						if(r<=R2){
							break;
						}
					}
				}
				if(x<x2){
					int	kx1=x;
					x++;
					for(;x<x2;x++){
						double	dx=x-CxOnMaster;
						double	dy=y-CyOnMaster;
						double	s=GetSita(dx,dy);
						if((StartS<EndS && (s<StartS || EndS<s)) || (StartS>EndS && (s<StartS && EndS<s))){
							break;
						}
						double	r=fabs(hypot(dx,dy)-(RxOnMaster-R2));
						if(r>R2){
							break;
						}
					}
					int	kx2=x;
					Dim[Len]._Set(kx1,kx2-1,y);
					Len++;
				}
			}
		}
		AreaI.SetFLine(Dim,Len);
	}
	catch(...){}

	try{
		struct FlexLine	*Dim=new struct FlexLine[(y2-y1+1)*2+2];
		int	Len=0;
		for(int y=y1;y<y2;y++){
			int x=x1;
			while(x<x2){
				for(;x<x2;x++){
					double	dx=x-CxOnMaster;
					double	dy=y-CyOnMaster;
					double	s=GetSita(dx,dy);
					if((StartS<EndS && StartS<=s && s<=EndS) || (StartS>EndS && (StartS<=s || s<=EndS))){
						double	r=fabs(hypot(dx,dy)-(RxOnMaster+R2));
						if(r<=R2){
							break;
						}
					}
				}
				if(x<x2){
					int	kx1=x;
					x++;
					for(;x<x2;x++){
						double	dx=x-CxOnMaster;
						double	dy=y-CyOnMaster;
						double	s=GetSita(dx,dy);
						if((StartS<EndS && (s<StartS || EndS<s)) || (StartS>EndS && (s<StartS && EndS<s))){
							break;
						}
						double	r=fabs(hypot(dx,dy)-(RxOnMaster+R2));
						if(r>R2){
							break;
						}
					}
					int	kx2=x;
					Dim[Len]._Set(kx1,kx2-1,y);
					Len++;
				}
			}
		}
		AreaO.SetFLine(Dim,Len);
	}
	catch(...){}
}
void	MeasureLineMoveCornerRItem::MakeIdeal(FlexAreaImageListCoeff &Area)
{
	int	KLen=Area.GetFLineLen();
	BYTE	*D=Area.GetData();
	for(int i=0;i<KLen;i++){
		int	y	=Area.GetFLineAbsY (i);
		int	x1	=Area.GetFLineLeftX(i);
		int	numb=Area.GetFLineNumb (i);
		for(int n=0;n<numb;n++){
			int	x=x1+n;
			double	dx=x-CxOnMaster;
			double	dy=y-CyOnMaster;
			double	r=hypot(dx,dy)-RxOnMaster;
			if(r<=0){
				*D=0xFF;
			}
			else{
				*D=0;
			}
			D++;
		}
	}
}

ExeResult	MeasureLineMoveCornerRItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		V.PosXOnTarget=Cx2;
		V.PosYOnTarget=Cy2;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ImageBuffer *TargetImageList[100];
	GetTargetBuffList(TargetImageList);	
	Res->SetAlignedXY(mx,my);
	AMx=mx;
	AMy=my;

	double	r1=ExecuteProcessingInner ( mx,my,TargetImageList ,AreaWithIdeal1	,Area1I,Avr1I ,Area1O,Avr1O ,Vx1 ,Vy1);
	double	r2=ExecuteProcessingInner ( mx,my,TargetImageList ,AreaWithIdeal2	,Area2I,Avr2I ,Area2O,Avr2O ,Vx2 ,Vy2);
	double	r3=ExecuteProcessingInner ( mx,my,TargetImageList ,AreaWithIdeal3	,Area3I,Avr3I ,Area3O,Avr3O ,Vx3 ,Vy3);

	VectorLineArc	V;
	V.SetPoints( Cx1+r1*Vx1, Cy1+r1*Vy1
				,Cx2+r2*Vx2, Cy2+r2*Vy2
				,Cx3+r3*Vx3, Cy3+r3*Vy3);

	double	tR ,tStartS ,tEndS;
	V.GetArc(ResultCx,ResultCy ,tR ,tStartS ,tEndS);

	ResultDifR=tR-RxOnMaster;
	SetCalcDone(true);
	return _ER_true;
}

double	MeasureLineMoveCornerRItem::ExecuteProcessingInner ( int mx,int my
															,ImageBuffer *ImageList[]
															,FlexAreaImageListCoeff &AreaWithIdeal
															,FlexArea &AreaI ,double AvrI
															,FlexArea &AreaO ,double AvrO
															,double vx ,double vy)
{

	double	MaxD=0;
	double	MaxR=0;
	int		iMaxR=0;
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	for(int r=-RThr->SearchDot;r<=RThr->SearchDot;r++){
		int		dx=r*vx;
		int		dy=r*vy;
		double	D=fabs(AreaWithIdeal.CalcCoeff(mx+dx ,my+dy ,*ImageList[0]));
		double	ca=AreaI	.GetAverage(*ImageList[0],mx+dx,my+dy);
		double	cb=AreaO	.GetAverage(*ImageList[0],mx+dx,my+dy);
		double	M=D*ExpFunc(ca,AvrI)*ExpFunc(cb,AvrO);
		if(M>MaxD){
			MaxD=M;
			iMaxR=r;
		}
	}
	MaxD=0;
	for(double	R=iMaxR-0.9;R<=iMaxR+0.9;R+=0.1){
		double	rdx=R*vx;
		double	rdy=R*vy;
		double	D=fabs(AreaWithIdeal.CalcCoeff(mx+rdx ,my+rdy ,*ImageList[0]));
		double	ca=AreaI	.GetAverage(*ImageList[0],mx+rdx,my+rdy);
		double	cb=AreaO	.GetAverage(*ImageList[0],mx+rdx,my+rdy);
		double	M=D*ExpFunc(ca,AvrI)*ExpFunc(cb,AvrO);
		if(M>MaxD){
			MaxD=M;
			MaxR=R;
		}
	}
	return MaxR;
}


void	MeasureLineMoveCornerRItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveCornerRItem *src=(MeasureLineMoveCornerRItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetItemName(src->GetItemName());
			SetEffective(src->IsEffective());
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureLineMoveLineItem *)Data)->GetLibID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveCornerRItem *src=(MeasureLineMoveCornerRItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
}

void	MeasureLineMoveCornerRItem::SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)
{
	GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)reqPacket->ItemArc.GetThresholdR()));
	ExecuteProcessing(0,0,Packet->Result);

	Packet->PosDiffX	=ResultCx - CxOnMaster;
	Packet->PosDiffY	=ResultCy - CyOnMaster;
	Packet->Error		=0;
	Packet->DiffR		=	ResultDifR;
}
bool	MeasureLineMoveCornerRItem::IsInclude(int x ,int y)	const
{
	if(AreaWithIdeal1.IsInclude(x,y)==true)
		return true;
	if(AreaWithIdeal2.IsInclude(x,y)==true)
		return true;
	if(AreaWithIdeal3.IsInclude(x,y)==true)
		return true;
	return false;
}

void	MeasureLineMoveCornerRItem::MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
													,bool EnableMakeImage ,bool EnableDrawLine)
{
	int	ImageWL=TResultImage.width();
	int	ImageHL=TResultImage.height();

	if(ImageWL!=0 && ImageHL!=0){
		double	cx,cy;
		GetCenter(cx,cy);

		ImagePointerContainer TargetImageList;
		GetTargetBuffList(TargetImageList);

		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);

		double	Zx=99999999;
		double	Zy=99999999;
		if(x1!=x2)
			Zx=ImageWL/((double)(x2-x1));
		if(y1!=y2)
			Zy=ImageHL/((double)(y2-y1));

		ImageZoomRate=min(Zx,Zy);
		double	Z=1.0/ImageZoomRate;

		ImageX1=cx+AMx-ImageWL/2;
		ImageY1=cy+AMy-ImageHL/2;
		if(EnableMakeImage==true){
			TargetImageList.MakeImage(TResultImage,-ImageX1,-ImageY1,ImageZoomRate,false);
		}
		LResultImage.fill(qRgba(0,0,0,0));

		if(EnableDrawLine==true){
			QPainter	Pnt(&LResultImage);
			Pnt.setPen(Qt::yellow);
			double	s=AngleS2-AngleS1;
			while(s<0){
				s+=2.0*M_PI;
			}
			int	MovX=-ImageWL/2*Z;
			int	MovY=-ImageHL/2*Z;

			Pnt.drawArc ((CxOnMaster-RxOnMaster+MovX)*ImageZoomRate, (CyOnMaster-RyOnMaster+MovY)*ImageZoomRate
						, RxOnMaster*2.0*ImageZoomRate, RyOnMaster*2.0*ImageZoomRate
						,(int)16*360*(1.0-AngleS2/(2.0*M_PI)) 
						,(int)(s*16*360/(2.0*M_PI)));

			Pnt.setPen(Qt::red);

			double	RxR=RxOnMaster+ResultDifR;
			double	RyR=RyOnMaster+ResultDifR;
			Pnt.drawArc ( (ResultCx-RxR+MovX+AMx)*ImageZoomRate, (ResultCy-RyR+MovY+AMy)*ImageZoomRate
							, RxR*2.0*ImageZoomRate, RyR*2.0*ImageZoomRate
							,(int)16*360*(1.0-AngleS2/(2.0*M_PI)) 
							,(int)(s*16*360/(2.0*M_PI)));
		}
	}
}
//=================================================================================

MeasureLineMoveMarkItem::MeasureLineMoveMarkItem(void)
{
	VLineX=VLineY1=VLineY2	=0;
	HLineX1=HLineX2=HLineY	=0;
	VDot	=NULL;
	HDot	=NULL;
	AddedS	=0;
	AddedSS	=0;

	XOnMaster	=0;
	YOnMaster	=0;

	ResultMatch	=0;
	ResultDx	=0;
	ResultDy	=0;
}

MeasureLineMoveMarkItem::~MeasureLineMoveMarkItem(void)
{
	if(VDot!=NULL){
		delete	[]VDot;
		VDot=NULL;
	}
	if(HDot!=NULL){
		delete	[]HDot;
		HDot=NULL;
	}
}
bool	MeasureLineMoveMarkItem::Save(QIODevice *file)
{
	int32	Ver=1;

	if(MeasureLineMoveItemBase::Save(file)==false)
		return false;

	if(::Save(file,Ver)==false)
		return false;

   if(TransArea	.Save(file)==false)
		return(false);

	if(::Save(file,VLineX)==false)
		return false;
	if(::Save(file,VLineY1)==false)
		return false;
	if(::Save(file,VLineY2)==false)
		return false;
	if(::Save(file,HLineX1)==false)
		return false;
	if(::Save(file,HLineX2)==false)
		return false;
	if(::Save(file,HLineY)==false)
		return false;

	bool	VExist;
	if(VDot!=NULL){
		VExist=true;
		if(::Save(file,VExist)==false)
			return false;
		int	Len=VLineY2-VLineY1+1;
	    if(file->write((const char *)VDot	,Len)!=Len)
			return(false);
	}
	else{
		VExist=false;
		if(::Save(file,VExist)==false)
			return false;
	}
	bool	HExist;
	if(HDot!=NULL){
		HExist=true;
		if(::Save(file,HExist)==false)
			return false;
		int	Len=HLineX2-HLineX1+1;
	    if(file->write((const char *)HDot	,Len)!=Len)
			return(false);
	}
	else{
		HExist=false;
		if(::Save(file,HExist)==false)
			return false;
	}
	    
    if(iTransArea	.Save(file)==false)
		return(false);
    if(oTransArea	.Save(file)==false)
		return(false);

	return(true);
}
bool	MeasureLineMoveMarkItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(MeasureLineMoveItemBase::Load(file,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(file,Ver)==false)
		return false;


	if(TransArea	.Load(file)==false)
		return(false);

	if(::Load(file,VLineX)==false)
		return false;
	if(::Load(file,VLineY1)==false)
		return false;
	if(::Load(file,VLineY2)==false)
		return false;
	if(::Load(file,HLineX1)==false)
		return false;
	if(::Load(file,HLineX2)==false)
		return false;
	if(::Load(file,HLineY)==false)
		return false;

	bool	VExist;
	if(::Load(file,VExist)==false)
		return false;
	if(VExist==true){
		int	Len=VLineY2-VLineY1+1;
		VDot=new BYTE[Len];
	    if(file->read((char *)VDot	,Len)!=Len)
			return false;
	}
	else{
		if(VDot!=NULL){
			delete	[]VDot;
		}
		VDot=NULL;
	}

	bool	HExist;
	if(::Load(file,HExist)==false)
		return false;
	if(HExist==true){
		int	Len=HLineX2-HLineX1+1;
		HDot=new BYTE[Len];
	    if(file->read((char *)HDot	,Len)!=Len)
			return false;
	}
	else{
		if(HDot!=NULL){
			delete	[]HDot;
		}
		HDot=NULL;
	}

	if(iTransArea	.Load(file)==false)
		return(false);
	if(oTransArea	.Load(file)==false)
		return(false);

	return(true);
}

void	MeasureLineMoveMarkItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveLineItem *src=(MeasureLineMoveLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureLineMoveLineItem *)Data)->GetLibID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveLineItem *src=(MeasureLineMoveLineItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
}
AlgorithmItemPI	&MeasureLineMoveMarkItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureLineMoveItemBase::operator=(src);

	const MeasureLineMoveMarkItem	*p=dynamic_cast<const MeasureLineMoveMarkItem *>(&src);
	if(p!=NULL){
        TransArea	=p->TransArea;

		SetArea		(p->GetArea());
		ResultMatch	=p->ResultMatch;
        ResultDx	=p->ResultDx;
        ResultDy	=p->ResultDy;

		VLineX		=p->VLineX;
		VLineY1		=p->VLineY1;
		VLineY2		=p->VLineY2;
		HLineX1		=p->HLineX1;
		HLineX2		=p->HLineX2;
		HLineY		=p->HLineY;
	}

	return *this;
}

VectorLineBase	*MeasureLineMoveMarkItem::CreateVectorBase(void)
{
	VectorLineDouble	*R=new VectorLineDouble();
	R->AppendItemBase(R->CreateItem());
	R->AppendItemBase(R->CreateItem());
	return R;
}

bool	MeasureLineMoveMarkItem::SetLocalData(MeasureLineMoveInPage *ParentPage)
{
	/*
	if(GetVector()==NULL)
		return false;

	VectorItemBase	*d1=GetVector()->GetFirstItem();
	if(d1==NULL){
		return false;
	}
	VectorItemBase	*d2=d1->GetNext();
	if(d2==NULL){
		return false;
	}
	VectorItemDouble	*v1=dynamic_cast<VectorItemDouble *>(d1);
	VectorItemDouble	*v2=dynamic_cast<VectorItemDouble *>(d2);
	if(v1==NULL || v2==NULL){
		return false;
	}
	X1OnMaster	=v1->GetX();
	Y1OnMaster	=v1->GetY();
	X2OnMaster	=v2->GetX();
	Y2OnMaster	=v2->GetY();
	*/

	return true;
}
void	MeasureLineMoveMarkItem::ExecuteMove(int dx,int dy,bool AllItems)
{
	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		AlgorithmItemPI::MoveTo(dx ,dy);
		//GetArea()	.MoveToNoClip(dx,dy);
        TransArea	.MoveToNoClip(dx,dy);
		iTransArea	.MoveToNoClip(dx,dy);
		oTransArea	.MoveToNoClip(dx,dy);

		VLineX	+=dx;
		VLineY1	+=dy;
		VLineY2	+=dy;
		HLineX1	+=dx;
		HLineX2	+=dx;
		HLineY	+=dy;
		XOnMaster	+=dx;
		YOnMaster	+=dy;
	}
}
void	MeasureLineMoveMarkItem::MoveForAlignment(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
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
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ExecuteMove(mx,my,true);
}
void	MeasureLineMoveMarkItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	QRgb	TransCol=qRgba(180,220,0,128);
	if(GetActive()==true){
		GetArea().Draw(0,0 ,&pnt ,Attr->ActiveColor.rgba()	,ZoomRate ,movx ,movy);
		TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
	}
	else if(GetSelected()==true){
		GetArea().Draw(0,0 ,&pnt ,Attr->SelectedColor.rgba()	,ZoomRate ,movx ,movy);
		TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
	}
	else{
		GetArea().Draw(0,0 ,&pnt ,Attr->NormalColor.rgba()	,ZoomRate ,movx ,movy);
		TransArea.Draw(0,0 ,&pnt ,TransCol,ZoomRate ,movx ,movy);
	}
	QPainter	LPnt(&pnt);
	QColor	LCol(255,0,0,196);
	LPnt.setPen(LCol);
	LPnt.drawLine((VLineX+movx)*ZoomRate,(VLineY1+movy)*ZoomRate,(VLineX+movx)*ZoomRate,(VLineY2+movy)*ZoomRate);
	LPnt.drawLine((HLineX1+movx)*ZoomRate,(HLineY+movy)*ZoomRate,(HLineX2+movx)*ZoomRate,(HLineY+movy)*ZoomRate);
}

void	MeasureLineMoveMarkItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		int	cx,cy;
		GetArea().GetCenter(cx,cy);

		QColor	c=Qt::green;
		c.setAlpha(100);

		GetArea().Draw(0,0,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
		QRgb	TCol=qRgba(180,0,180,128);
		TransArea.Draw(0,0 ,&IData ,TCol,ZoomRate ,MovX ,MovY);

		QColor	d=Qt::red;
		d.setAlpha(180);
		QRgb	TransCol=qRgba(180,220,0,168);

		GetArea().Draw(ResultDx,ResultDy,&IData ,d.rgba()
							,ZoomRate ,MovX ,MovY);

		TransArea.Draw(ResultDx,ResultDy ,&IData ,TransCol,ZoomRate ,MovX ,MovY);

		PData.drawText((cx+ResultDx+MovX)*ZoomRate,(cy+ResultDy+MovY)*ZoomRate+32
			,QString(/**/"Dx=")+QString::number((int)ResultDx)
			+QString(/**/",Dy=")+QString::number((int)ResultDy));
		PData.drawText((cx+ResultDx+MovX)*ZoomRate,(cy+ResultDy+MovY)*ZoomRate+48
			,QString(/**/"Match=")+QString::number(ResultMatch));

		PData.drawText((cx+ResultDx+MovX)*ZoomRate,(cy+ResultDy+MovY)*ZoomRate+64
			,QString(/**/"Adopted"));


		PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate
			,QString(/**/"Max:")+QString::number((int)GetThresholdR()->SearchDot));
		PData.drawText((cx+MovX)*ZoomRate,(cy+MovY)*ZoomRate+16
			,QString(/**/"MasterX=") +QString::number((int)XOnMaster)
			+QString(/**/",MasterY=")+QString::number((int)YOnMaster));
	}
}
	
void	MeasureLineMoveMarkItem::GetCenterPoint(double &cx, double &cy)
{
	cx=XOnMaster;
	cy=YOnMaster;
}

void	MeasureLineMoveMarkItem::Move(double dx ,double dy)
{
	ExecuteMove(dx,dy,true);
}

bool    MeasureLineMoveMarkItem::MakeArea(ImageBuffer &Buff ,ImageBuffer *specialData)
{
    int     x1;
    int     y1;
    int     x2;
    int     y2;
	if(IsOriginParts()==true){
		return true;
	}
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	TransArea.Clear();
	int	ccol=GetThreshLevel(Buff);
	int	OutlineWidth	=RThr->EdgeWidth;

	if(GetArea().GetPatternByte()==0)
		return false;
    if(GetArea().GetXY(x1 ,y1 ,x2 ,y2)==false)
		return false;

	int		PointX1=GetArea().GetMinX()-4-OutlineWidth;
	int		PointY1=GetArea().GetMinY()-4-OutlineWidth;
	int		XLen=GetArea().GetWidth()+8 +2*OutlineWidth;
    int		YLen=GetArea().GetHeight()+8+2*OutlineWidth;

	int		MoveDot=RThr->SearchDot;

	if((PointX1<MoveDot) || (GetDotPerLine()<(PointX1+XLen+MoveDot))
	|| (PointY1<MoveDot) || (GetMaxLines()  <(PointY1+YLen+MoveDot)))
		return false;

    int XByte=(XLen+7)/8;

    ImageBuffer *DPoint;
    if(specialData==NULL){
		DPoint=&Buff;
    }
    else{
        DPoint=specialData;
    }

	BYTE	**TmpPtn=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp1=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp2=MakeMatrixBuff(XByte,YLen);
	BYTE	**Tmp3=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(TmpPtn,0,XByte,YLen);

	for(int i=0;i<GetArea().GetFLineLen();i++){
		int y=GetArea().GetFLineAbsY(i);
		int x1=GetArea().GetFLineLeftX(i);
		int N=GetArea().GetFLineNumb(i);
		BYTE    *src=DPoint->GetY(y)+x1;
		BYTE	*dst=TmpPtn[y-PointY1];
        for(int n=0;n<N;n++,src++){
			if(*src>=ccol){
				int mx=x1+n-PointX1;
				dst[(mx>>3)]|=(BYTE)(0x80>>(mx&7));
			}
		}
	}

	ThinArea(TmpPtn
			,Tmp3
			,XByte, YLen);
	FatArea(TmpPtn
			,Tmp3
			,XByte, YLen);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpPtn,XByte ,XLen,YLen ,FPack);
	if(FPack.IsEmpty()==true)
		return false;


	PureFlexAreaList	*MaxSizeArea=FPack.GetFirst();
	int64		MaxSize=MaxSizeArea->GetPatternByte();
	for(PureFlexAreaList *f=MaxSizeArea->GetNext();f!=NULL;f=f->GetNext()){
		int64	d=f->GetPatternByte();
		if(d>MaxSize){
			MaxSize=d;
			MaxSizeArea=f;
		}
	}
	MatrixBuffClear(TmpPtn,0,XByte,YLen);
	MaxSizeArea->MakeBitData(TmpPtn,GetDotPerLine(),GetMaxLines());

	MatrixBuffCopy(Tmp1,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);
	MatrixBuffCopy(Tmp2,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);

	GetLayersBase()->FatAreaN (Tmp1
				,Tmp3
				,XByte, YLen
				,OutlineWidth);
	GetLayersBase()->ThinAreaN(Tmp2
				,Tmp3
				,XByte, YLen
				,OutlineWidth);

	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);

	FlexArea	tArea(XLen,YLen);
	tArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	tArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	TransArea=tArea;
	TransArea.MoveToNoClip(PointX1,PointY1);

	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);
	MatrixBuffXor	(Tmp1,(const BYTE **)TmpPtn,XByte ,YLen);
	FlexArea	oArea(XLen,YLen);
	oArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	oArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	oTransArea=oArea;
	oTransArea.MoveToNoClip(PointX1,PointY1);

	MatrixBuffCopy(Tmp1,XByte,YLen ,(const BYTE **)TmpPtn,XByte,YLen);
	MatrixBuffXor	(Tmp1,(const BYTE **)Tmp2,XByte ,YLen);
	FlexArea	iArea(XLen,YLen);
	iArea.BuildFromRaster(Tmp1,XByte,YLen,0,0);
	iArea.ClipArea(4+OutlineWidth+OutlineWidth+2 ,4+OutlineWidth+OutlineWidth+2
				,XLen-4-OutlineWidth-OutlineWidth-2,YLen-4-OutlineWidth-OutlineWidth-2);
	iTransArea=iArea;
	iTransArea.MoveToNoClip(PointX1,PointY1);

	VLineX	=PointX1+XLen/2;
	VLineY1	=PointY1+4+OutlineWidth;
	VLineY2	=PointY1+YLen-4-OutlineWidth;
	HLineX1	=PointX1+4+OutlineWidth;
	HLineX2	=PointX1+XLen-4-OutlineWidth;
	HLineY	=PointY1+YLen/2;

	MakeHVDot(Buff);
    TransArea.Regulate();
	TransArea.SetAndCalc(Buff);
	TransArea.MakeSum();

	DeleteMatrixBuff(Tmp1,YLen);
	DeleteMatrixBuff(Tmp2,YLen);
	DeleteMatrixBuff(Tmp3,YLen);
	DeleteMatrixBuff(TmpPtn,YLen);

	ResultDx=0;
	ResultDy=0;
	GetArea().GetCenter(XOnMaster,YOnMaster);
	return true;
}


void	MeasureLineMoveMarkItem::MakeHVDot(ImageBuffer &Buff)
{
	if(VDot!=NULL){
		delete	[]VDot;
	}
	VDot=new BYTE[VLineY2-VLineY1+1];

	if(HDot!=NULL){
		delete	[]HDot;
	}
	HDot=new BYTE[HLineX2-HLineX1+1];

	AddedS=0;
	AddedSS=0;

	int	L=0;
	for(int y=VLineY1;y<=VLineY2;y+=2){
		BYTE	*s=Buff.GetY(y);
		int		c=s[VLineX];
		VDot[L]=c;
		AddedS+=c;
		AddedSS+=c*c;
		L++;
	}
	L=0;
	BYTE	*s=Buff.GetY(HLineY);
	for(int x=HLineX1;x<=HLineX2;x+=2){
		int	c=s[x];
		HDot[L]=c;
		AddedS+=c;
		AddedSS+=c*c;
		L++;
	}
}
double    MeasureLineMoveMarkItem::GetThreshLevel(ImageBuffer &data ,int dx ,int dy)
{
    int LTable[256];

    memset(LTable,0,sizeof(LTable));

	GetArea().MakeBrightList(LTable,GetDotPerLine(),GetMaxLines(),data,dx ,dy,1);

	int	DotSum=0;
	for(int i=0;i<256;i++){
		DotSum+=LTable[i];
	}

	int	PeakH;
	int	PeakL;
    for(PeakH=255;PeakH>1;PeakH--){
		if(LTable[PeakH]>=LTable[PeakH-1] && LTable[PeakH]>=LTable[PeakH-2] && (LTable[PeakH]+LTable[PeakH-1]+LTable[PeakH-2])>DotSum/32)
			break;
	}
	for(PeakL=0;PeakL<254;PeakL++){
		if(LTable[PeakL]>LTable[PeakL+1] && LTable[PeakL]>LTable[PeakL+2] && (LTable[PeakL]+LTable[PeakL+1]+LTable[PeakL+2])>DotSum/32)
			break;
	}

	int	MinL=0;
	int	MinD=99999999;
	for(int L=PeakL;L<PeakH;L++){
		if(L==0)
			continue;
		if(L==255)
			break;
		if(MinD>LTable[L]){
			MinD=LTable[L];
			MinL=L;
		}
	}

    return(MinL);
}

ExeResult	MeasureLineMoveMarkItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(EInfo);
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID,ThreadNo,Res,EInfo);

	if(IsOriginParts()==false){
		if(VDot!=NULL && HDot!=NULL){
			int	L=0;
			AddedS=0;
			AddedSS=0;
			for(int y=VLineY1;y<=VLineY2;y+=2){
				int	s=VDot[L];
				AddedS+=s;
				AddedSS+=s*s;
				L++;
			}
			L=0;
			for(int x=HLineX1;x<=HLineX2;x+=2){
				int	s=HDot[L];
				AddedS+=s;
				AddedSS+=s*s;
				L++;
			}
		}
		GetArea().GetCenter(XOnMaster,YOnMaster);
	}

	return Ret;
}
void	MeasureLineMoveMarkItem::InitialInCreation(void)
{
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	Layer=RThr->UsageLayer;
	if(Layer<0 || GetLayerNumb()<=Layer)
		return;
	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);	
	MakeArea(*MasterImageList[Layer]);
}
void	MeasureLineMoveMarkItem::CutArea(FlexArea &localArea,bool &_Changed)
{
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	Layer=RThr->UsageLayer;
	if(Layer<0 || GetLayerNumb()<=Layer)
		return;
	AlgorithmItemPI::CutArea(localArea,_Changed);
	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);	
	MakeArea(*MasterImageList[Layer]);
}

void	MeasureLineMoveMarkItem::MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)
{
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	Layer=RThr->UsageLayer;
	if(Layer<0 || GetLayerNumb()<=Layer)
		return;
	AlgorithmItemPI::MirrorItem(MirrorMode ,PointX ,PointY);
	ImageBuffer *MasterImageList[100];
	GetMasterBuffList(MasterImageList);	
	MakeArea(*MasterImageList[Layer]);
}
double    MeasureLineMoveMarkItem::MatchBrightCenter(double &mx ,double &my ,ImageBuffer &Target ,int offsetX,int offsetY)
{
	//DataInPage	*Lp=GetDataInPage();
	if(GetArea().GetPatternByte()==0
	|| (GetArea().GetMinX()+offsetX)<0 
	|| (GetArea().GetMaxX()+offsetX)>=GetDotPerLine() 
	|| (GetArea().GetMinY()+offsetY)<0 
	|| (GetArea().GetMaxY()+offsetY)>=GetMaxLines()){
		mx=offsetX;
		my=offsetY;
		ResultDx=offsetX;
		ResultDy=offsetY;
		return 0;
	}
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	MoveDot		=RThr->SearchDot;
	int	OutlineWidth=RThr->EdgeWidth;

	double	MaxD=0;
	double	MaxDx,MaxDy;
	for(int x=-MoveDot;x<=MoveDot;x+=2){
		for(int y=-MoveDot;y<=MoveDot;y+=2){
			double	D=fabs(MatchCross(Target ,offsetX+x,offsetY+y));
			if(D>MaxD){
				MaxD=D;
				MaxDx=x;
				MaxDy=y;
			}
		}
	}

	if(MaxD==0){
		ResultDx=offsetX;
		ResultDy=offsetY;
		return 0;
	}

	double	hMaxD=0;
	int		hMaxDX=0;
	int		hMaxDY=0;
	for(int y=-OutlineWidth;y<=OutlineWidth;y+=2){
		for(int x=-OutlineWidth;x<=OutlineWidth;x+=2){
			double	d=fabs(TransArea.CalcCoeff(MaxDx+x,MaxDy+y	,Target));
			if(d>=hMaxD){
				hMaxD=d;
				hMaxDX=x;
				hMaxDY=y;
			}
		}
	}

	double	qMaxD=0;
	int		qMaxDX=0;
	int		qMaxDY=0;
	for(int y=-1;y<=1;y++){
		for(int x=-1;x<=1;x++){
			double	d=fabs(TransArea.CalcCoeff(MaxDx+hMaxDX+x,MaxDy+hMaxDY+y	,Target));
			if(d>=qMaxD){
				qMaxD=d;
				qMaxDX=x;
				qMaxDY=y;
			}
		}
	}
	int	vx=MaxDx+hMaxDX+qMaxDX;
	int	vy=MaxDy+hMaxDY+qMaxDY;

	ResultMatch	=qMaxD;
	ResultDx	=vx;
	ResultDy	=vy;
	return qMaxD;
}

double	MeasureLineMoveMarkItem::MatchCross(ImageBuffer &Target ,int dx,int dy)
{
	int	L=0;
	int		AddedD=0;
	int		AddedDD=0;
	int		AddedSD=0;
	int		SDCount=0;
	for(int y=VLineY1;y<=VLineY2;y+=2){
		BYTE	*D=Target.GetY(y+dy);
		int	s=VDot[L];
		int	d=D[VLineX+dx];
		AddedD+=d;
		AddedDD+=d*d;
		AddedSD+=s*d;
		SDCount++;
		L++;
	}
	L=0;
	BYTE	*D=Target.GetY(HLineY+dy);
	for(int x=HLineX1;x<=HLineX2;x+=2){
		int	s=HDot[L];
		int	d=D[x+dx];
		AddedD+=d;
		AddedDD+=d*d;
		AddedSD+=s*d;
		SDCount++;
		L++;
	}
	if(SDCount==0){
		return 0;
	}
	double	AvrS=((double)AddedS)/SDCount;
	double	AvrD=((double)AddedD)/SDCount;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}
	
ExeResult	MeasureLineMoveMarkItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;

		V.PosXOnTarget=XOnMaster;
		V.PosYOnTarget=YOnMaster;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	ImageBuffer *TargetImageList[100];
	GetTargetBuffList(TargetImageList);	
	Res->SetAlignedXY(mx,my);
	
	double	Mx=0;
	double	My=0;

	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	int	Layer=RThr->UsageLayer;
	if(0<=Layer && Layer<GetLayerNumb()){
		ImageBuffer *TargetImageList[100];
		GetTargetBuffList(TargetImageList);	
		MatchBrightCenter(Mx ,My ,*TargetImageList[Layer] ,mx,my);
	}

	//GetThresholdW()->AddHist(Hist_AlighmentLargeShiftX	,ResultDx);
	//GetThresholdW()->AddHist(Hist_AlighmentLargeShiftY	,ResultDy);
	
	SetCalcDone(true);

	return _ER_true;
}

void	MeasureLineMoveMarkItem::SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)
{
	GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)reqPacket->ItemLine.GetThresholdR()));
	ExecuteProcessing(0,0,Packet->Result);

	Packet->PosDiffX	=ResultDx;
	Packet->PosDiffY	=ResultDx;
	Packet->Error		=ResultMatch;
}

double	MeasureLineMoveMarkItem::GetIsolation(double x ,double y)
{
	if(GetArea().IsInclude(x,y)==true)
		return 0;
	return hypot(x-XOnMaster,y-YOnMaster);
}

double	MeasureLineMoveMarkItem::GetDrawParam(double x ,double y)
{
	return hypot(x-XOnMaster,y-YOnMaster);
}
double	MeasureLineMoveMarkItem::GetTParam(double x1 ,double y1 ,double x2 ,double y2)
{
	double	X,Y;
	if(GetLimitlessLinePointFoot(x1,y1,x2,y2,XOnMaster ,YOnMaster ,X ,Y)==true){
		return hypot(X-XOnMaster,Y-YOnMaster);
	}
	return 0;
}
void	MeasureLineMoveMarkItem::GetDrawPoint(double Param ,double &x ,double &y)
{
	x=XOnMaster;
	y=YOnMaster;
}
void	MeasureLineMoveMarkItem::GetShiftVector(double &sx, double &sy)
{
	sx=ResultDx+AMx;
	sy=ResultDy+AMy;
}
bool	MeasureLineMoveMarkItem::IsInclude(int x ,int y)	const
{
	return GetArea().IsInclude(x,y);
}

void	MeasureLineMoveMarkItem::MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
												,bool EnableMakeImage ,bool EnableDrawLine)
{
	int	ImageWL=TResultImage.width();
	int	ImageHL=TResultImage.height();

	if(ImageWL!=0 && ImageHL!=0){
		double	cx,cy;
		GetCenterPoint(cx,cy);

		ImagePointerContainer TargetImageList;
		GetTargetBuffList(TargetImageList);

		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);

		double	Zx=99999999;
		double	Zy=99999999;
		if(x1!=x2)
			Zx=ImageWL/((double)(x2-x1));
		if(y1!=y2)
			Zy=ImageHL/((double)(y2-y1));

		ImageZoomRate=min(Zx,Zy);
		double	Z=1.0/ImageZoomRate;

		ImageX1=cx+AMx-ImageWL/2;
		ImageY1=cy+AMy-ImageHL/2;
		if(EnableMakeImage==true){
			TargetImageList.MakeImage(TResultImage,-ImageX1,-ImageY1,ImageZoomRate,false);
		}

		LResultImage.fill(qRgba(0,0,0,0));
		if(EnableDrawLine==true){
			QPainter	Pnt(&LResultImage);

			GetArea().GetCenter(cx,cy);
			int	MovX=-ImageWL/2*Z;
			int	MovY=-ImageHL/2*Z;

			QColor	c=Qt::green;
			c.setAlpha(100);

			GetArea().Draw(0,0,&LResultImage ,c.rgba()
									,ImageZoomRate ,MovX ,MovY);
			QRgb	TCol=qRgba(180,0,180,128);
			TransArea.Draw(0,0 ,&LResultImage ,TCol,ImageZoomRate ,MovX ,MovY);

			QColor	d=Qt::red;
			d.setAlpha(180);
			QRgb	TransCol=qRgba(180,220,0,168);

			GetArea().Draw(ResultDx,ResultDy,&LResultImage ,d.rgba()
								,ImageZoomRate ,MovX ,MovY);

			TransArea.Draw(ResultDx,ResultDy ,&LResultImage ,TransCol,ImageZoomRate ,MovX ,MovY);
		}
	}
}
//=======================================================================================================

void	LineMoveResultPosList::GetExtraData(QByteArray &EData)
{
	MeasureLineMoveDistanceItem	*DItem=dynamic_cast<MeasureLineMoveDistanceItem *>(AItem);
	if(DItem!=NULL){
		EData=DItem->ResultExtraData;
	}
}

MeasureLineMoveDistanceItem::MeasureLineMoveDistanceItem(void)
{
	MeasurePointNo	=-1;
	LineType1	=-1;
	LineType2	=-1;
	NoCalc		=false;
	Line1InGlobalPage	=-1;
	LineID1		=-1;
	Line2InGlobalPage	=-1;
	LineID2		=-1;
	DrawPoint1	=0;
	DrawPoint2	=0;
	DifLen		=0;
	ResultLen	=0;
}


bool	MeasureLineMoveDistanceItem::Save(QIODevice *f)
{
	int32	Ver=5;

	if(MeasureLineMoveItemBase::Save(f)==false)
		return false;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MeasurePointNo)==false)
		return false;
	if(::Save(f,LineType1)==false)
		return false;
	if(::Save(f,LineType2)==false)
		return false;
	if(::Save(f,LineID1)==false)
		return false;
	if(::Save(f,LineID2)==false)
		return false;
	if(::Save(f,DrawPoint1)==false)
		return false;
	if(::Save(f,DrawPoint2)==false)
		return false;

	if(::Save(f,Line1InGlobalPage)==false)
		return false;
	if(::Save(f,Line2InGlobalPage)==false)
		return false;
	if(::Save(f,NoCalc)==false)
		return false;

	if(f->write((const char *)&GenData,sizeof(GenData))!=sizeof(GenData))
		return false;

	return true;
}
bool	MeasureLineMoveDistanceItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(MeasureLineMoveItemBase::Load(f,LBase)==false)
		return false;

	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=4){
		if(::Load(f,MeasurePointNo)==false)
			return false;
	}
	if(::Load(f,LineType1)==false)
		return false;
	if(::Load(f,LineType2)==false)
		return false;
	if(::Load(f,LineID1)==false)
		return false;
	if(::Load(f,LineID2)==false)
		return false;
	if(::Load(f,DrawPoint1)==false)
		return false;
	if(::Load(f,DrawPoint2)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,Line1InGlobalPage)==false)
			return false;
		if(::Load(f,Line2InGlobalPage)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,NoCalc)==false)
			return false;
	}
	if(Ver>=5){
		if(f->read((char *)&GenData,sizeof(GenData))!=sizeof(GenData))
			return false;
	}
	return true;
}

void	MeasureLineMoveDistanceItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveDistanceItem *src=(MeasureLineMoveDistanceItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			TransferInfo	=src->TransferInfo;
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((MeasureLineMoveLineItem *)Data)->GetLibID()){
			MeasureLineMoveInPage	*Ly=dynamic_cast<MeasureLineMoveInPage *>(GetParentInPage());
			UndoElement<MeasureLineMoveInPage>	*UPointer=new UndoElement<MeasureLineMoveInPage>(Ly,&MeasureLineMoveInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			MeasureLineMoveDistanceItem *src=(MeasureLineMoveDistanceItem *)Data;
			GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)src->GetThresholdR(GetLayersBase())));
			TransferInfo	=src->TransferInfo;
			SetLibID(src->GetLibID());
			SetEffective(src->IsEffective());
		}
	}
}
AlgorithmItemPI	&MeasureLineMoveDistanceItem::operator=(const AlgorithmItemRoot &src)
{
	MeasureLineMoveItemBase::operator=(src);

	const MeasureLineMoveDistanceItem	*p=dynamic_cast<const MeasureLineMoveDistanceItem *>(&src);
	if(p!=NULL){
		LineID1			=p->LineID1;
		LineID2			=p->LineID2;
		DrawPoint1		=p->DrawPoint1;
		DrawPoint2		=p->DrawPoint2;
		MeasurePointNo	=p->MeasurePointNo;
	}

	return *this;
}

void	MeasureLineMoveDistanceItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);

	MeasureLineMoveDrawAttr	*MAttr=dynamic_cast<MeasureLineMoveDrawAttr *>(Attr);
	bool	Exist1=false;
	bool	Exist2=false;
	double	X1,Y1;
	double	X2,Y2;
	DataInPage	*DP=GetDataInPage();
	if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		SlaveCommReqPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
		SlaveCommAckPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
		RCmd.ItemID		=LineID1;
		RCmd.DrawPoint	=DrawPoint1;
		if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
			int GlobalX ,GlobalY;
			GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
			int	LocalX,LocalY;
			DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
			X1=LocalX;
			Y1=LocalY;
			Exist1=true;
		}
	}
	else{
		MeasureCommon	*p1=GetFirstPointOnMaster();
		if(p1!=NULL){
			p1->GetDrawPoint(DrawPoint1,X1,Y1);
			Exist1=true;
		}
	}

	if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		SlaveCommReqPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
		SlaveCommAckPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
		RCmd.ItemID		=LineID2;
		RCmd.DrawPoint	=DrawPoint2;
		if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
			int GlobalX ,GlobalY;
			GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
			int	LocalX,LocalY;
			DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
			X2=LocalX;
			Y2=LocalY;
			Exist2=true;
		}
	}
	else{
		MeasureCommon	*p2=GetSecondPointOnMaster();
		if(p2!=NULL){
			p2->GetDrawPoint(DrawPoint2,X2,Y2);
			Exist2=true;
		}
	}

	if(Exist1==true && Exist2==true){
		QPainter	Pnt(&pnt);
		if(MAttr!=NULL && MAttr->ShowingItemID==GetID()){
			Pnt.setPen(Qt::magenta);
			Pnt.setBrush(Qt::magenta);
		}
		else{
			Pnt.setPen(Qt::yellow);
			Pnt.setBrush(Qt::yellow);
		}
		DrawArrow((X1+X2)/2,(Y1+Y2)/2,X1,Y1
				,Pnt ,movx ,movy ,ZoomRate
				//,0,0,GetDotPerLine(),GetMaxLines()
				,20);
		DrawArrow((X1+X2)/2,(Y1+Y2)/2,X2,Y2
				,Pnt ,movx ,movy ,ZoomRate
				//,0,0,GetDotPerLine(),GetMaxLines()
				,20);

		Pnt.setPen(Qt::red);
		Pnt.setBrush(Qt::red);
		Pnt.drawText((X1+movx)*ZoomRate+32,(Y1+movy)*ZoomRate,QString(/**/"1"));
		Pnt.drawText((X2+movx)*ZoomRate+32,(Y2+movy)*ZoomRate,QString(/**/"2"));
	}
}

VectorLineBase	*MeasureLineMoveDistanceItem::CreateVectorBase(void)
{
	VectorLineDouble	*R=new VectorLineDouble();
	R->AppendItemBase(R->CreateItem());
	R->AppendItemBase(R->CreateItem());
	return R;
}
bool	MeasureLineMoveDistanceItem::SetLocalData(MeasureLineMoveInPage *ParentPage)
{
	if(GetVector()==NULL)
		return false;

	VectorItemBase	*d1=GetVector()->GetFirstItem();
	if(d1==NULL){
		return false;
	}
	VectorItemBase	*d2=d1->GetNext();
	if(d2==NULL){
		return false;
	}
	VectorItemDouble	*v1=dynamic_cast<VectorItemDouble *>(d1);
	VectorItemDouble	*v2=dynamic_cast<VectorItemDouble *>(d2);
	if(v1==NULL || v2==NULL){
		return false;
	}
	int	x1=v1->GetX();
	int	y1=v1->GetY();
	int	x2=v2->GetX();
	int	y2=v2->GetY();
	int	NearBy=20;

	if(LineID1>=0){
		AlgorithmItemRoot	*p=ParentPage->SearchIDItem(LineID1);
		MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
		if(a==NULL){
			LineID1=-1;
		}
		else{
			DrawPoint1=a->GetDrawParam(x1,y1);
		}
	}
	if(LineID1<0){
		for(AlgorithmItemPI	*p=ParentPage->GetFirstData();p!=NULL;p=p->GetNext()){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				if(a->GetIsolation(x1,y1)<NearBy){
					LineType1=1;
					LineID1	=a->GetItemID();
					DrawPoint1=a->GetDrawParam(x1,y1);
					break;
				}
			}
		}
		if(LineID1<0){
			AlgorithmBase	*AHole=ParentPage->GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
			if(AHole!=NULL){
				AlgorithmInPagePI	*HPage=(AlgorithmInPagePI *)AHole->GetPageData(ParentPage->GetPage());

				for(AlgorithmItemPI	*p=HPage->GetFirstData();p!=NULL;p=p->GetNext()){
					MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
					if(a!=NULL){
						if(a->GetIsolation(x1,y1)<NearBy){
							LineType1=2;
							LineID1	=a->GetItemID();
							DrawPoint1=a->GetDrawParam(x1,y1);
							break;
						}
					}
				}
			}
		}
	}

	if(LineID2>=0){
		AlgorithmItemRoot	*p=ParentPage->SearchIDItem(LineID2);
		MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
		if(a==NULL){
			LineID2=-1;
		}
		else{
			DrawPoint2=a->GetDrawParam(x2,y2);
		}
	}
	if(LineID2<0){
		for(AlgorithmItemPI	*p=ParentPage->GetFirstData();p!=NULL;p=p->GetNext()){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				if(a->GetIsolation(x2,y2)<NearBy){
					LineType2=1;
					LineID2	=a->GetItemID();
					DrawPoint2=a->GetDrawParam(x2,y2);
					break;
				}
			}
		}
		if(LineID2<0){
			AlgorithmBase	*AHole=ParentPage->GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
			if(AHole!=NULL){
				AlgorithmInPagePI	*HPage=(AlgorithmInPagePI *)AHole->GetPageData(ParentPage->GetPage());

				for(AlgorithmItemPI	*p=HPage->GetFirstData();p!=NULL;p=p->GetNext()){
					MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
					if(a!=NULL){
						if(a->GetIsolation(x2,y2)<NearBy){
							LineType2=2;
							LineID2	=a->GetItemID();
							DrawPoint2=a->GetDrawParam(x2,y2);
							break;
						}
					}
				}
			}
		}
	}
	if(LineID1>=0 && LineID2>=0){
		return true;
	}
	return false;
}
void	MeasureLineMoveDistanceItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	double	X1,Y1;
	double	X2,Y2;
	double	Sx1,Sy1;
	double	Sx2,Sy2;
	bool	Exist1=false;
	bool	Exist2=false;

	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		MeasureCommon	*p1=NULL;
		MeasureCommon	*p2=NULL;

		MeasureLineMoveBase	*ABase=(MeasureLineMoveBase	*)GetParentBase();
		DataInPage	*DP=GetDataInPage();
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			RCmd.ItemID		=LineID1;
			RCmd.DrawPoint	=DrawPoint1;
			if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==true){
					int GlobalX ,GlobalY;
					GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
					int	LocalX,LocalY;
					DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
					X1=LocalX;
					Y1=LocalY;
					Sx1=ACmd.ShiftX;
					Sy1=ACmd.ShiftY;
					Exist1=true;
				}
			}
		}
		else{
			p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
				p1->GetShiftVector(Sx1,Sy1);
				Exist1=true;
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			RCmd.ItemID		=LineID2;
			RCmd.DrawPoint	=DrawPoint2;
			if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==true){
					int GlobalX ,GlobalY;
					GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
					int	LocalX,LocalY;
					DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
					X2=LocalX;
					Y2=LocalY;
					Sx2=ACmd.ShiftX;
					Sy2=ACmd.ShiftY;
					Exist2=true;
				}
			}
		}
		else{
			p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
				p2->GetShiftVector(Sx2,Sy2);
				Exist2=true;
			}
		}
		if(Exist1==true && Exist2==true){
			double	dx=X2-X1;
			double	dy=Y2-Y1;
			double	M =hypot(dx,dy);
			if(M>0){
				double	Mx=dx/M;
				double	My=dy/M;

				double	t1=Sx1*Mx+Sy1*My;
				double	t2=Sx2*Mx+Sy2*My;
				double	mX1=X1+Sx1;
				double	mY1=Y1+Sy1;
				double	mX2=X2+Sx2;
				double	mY2=Y2+Sy2;

				DifLen=t2-t1;

				PData.setPen(Qt::red);
				PData.setBrush(Qt::red);
				DrawArrow((mX1+mX2)/2,(mY1+mY2)/2,mX1,mY1
						,PData ,MovX ,MovY ,ZoomRate,20);
				DrawArrow((mX1+mX2)/2,(mY1+mY2)/2,mX2,mY2
						,PData ,MovX ,MovY ,ZoomRate,20);

				int	kx=(mX2+mX1)/2;
				int	ky=(mY1+mY2)/2;
				PData.setPen	(ABase->ResultColor);
				PData.setBrush	(ABase->ResultColor);
				double	PixelLen=hypot(fabs(dx)-Sx1*Mx+Sx2*Mx,fabs(dy)-Sy1*My+Sy2*My);
				RealLen =GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),fabs(dx)-Sx1*Mx+Sx2*Mx,fabs(dy)-Sy1*My+Sy2*My);
				if(IsUnitMode()==true){
					PData.drawText(  (kx+MovX)*ZoomRate
									,(ky+MovY)*ZoomRate
									,QString(/**/"Diff:")
										+TransformPixelToUnitStr(DifLen)
										+QString(" (")
										+QString::number(DifLen)
										+QString(")"));
					PData.drawText(  (kx+MovX)*ZoomRate
									,(ky+MovY)*ZoomRate+16
									,QString(/**/"Len:")
										+QString::number(RealLen,'f',GetParamGlobal()->SmallNumberFigure)
										+GetParamGlobal()->UnitName
										+QString(" (")
										+QString::number(PixelLen,'f',GetParamGlobal()->SmallNumberFigure)
										+QString(")"));
				}
				else{
					PData.drawText(  (kx+MovX)*ZoomRate
									,(ky+MovY)*ZoomRate
									,QString(/**/"Diff:")+QString::number(DifLen,'f',GetParamGlobal()->SmallNumberFigure));
					PData.drawText(  (kx+MovX)*ZoomRate
									,(ky+MovY)*ZoomRate+16
									,QString(/**/"Len:")+QString::number(PixelLen,'f',GetParamGlobal()->SmallNumberFigure));
				}
			}
			if(p1!=NULL){
				p1->DrawNumber(IData ,PData,MovX ,MovY ,ZoomRate,1);
			}
			if(p2!=NULL){
				p2->DrawNumber(IData ,PData,MovX ,MovY ,ZoomRate,2);
			}
		}
	}
}

double	MeasureLineMoveDistanceItem::GetResultDistance(void)
{
	double	X1,Y1;
	double	X2,Y2;
	double	Sx1,Sy1;
	double	Sx2,Sy2;
	bool	Exist1=false;
	bool	Exist2=false;

	DataInPage	*DP=GetDataInPage();
	if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
		SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
		RCmd.ItemID		=LineID1;
		RCmd.DrawPoint	=DrawPoint1;
		if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
			if(ACmd.CalcDone==true){
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X1=LocalX;
				Y1=LocalY;
				Sx1=ACmd.ShiftX;
				Sy1=ACmd.ShiftY;
				Exist1=true;
			}
		}
	}
	else{
		MeasureCommon	*p1=GetFirstPointOnMaster();
		if(p1!=NULL){
			p1->GetDrawPoint(DrawPoint1,X1,Y1);
			p1->GetShiftVector(Sx1,Sy1);
			Exist1=true;
		}
	}
	
	if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
		SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
		RCmd.ItemID		=LineID2;
		RCmd.DrawPoint	=DrawPoint2;
		if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
			if(ACmd.CalcDone==true){
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X2=LocalX;
				Y2=LocalY;
				Sx2=ACmd.ShiftX;
				Sy2=ACmd.ShiftY;
				Exist2=true;
			}
		}
	}
	else{
		MeasureCommon	*p2=GetSecondPointOnMaster();
		if(p2!=NULL){
			p2->GetDrawPoint(DrawPoint2,X2,Y2);
			p2->GetShiftVector(Sx2,Sy2);
			Exist2=true;
		}
	}
	if(Exist1==true && Exist2==true){
		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;
			double	PixelLen=hypot(dx-Sx1*Mx+Sx2*Mx,dy-Sy1*My+Sy2*My);
			return PixelLen;
		}
	}
	return 0;
}

MeasureCommon	*MeasureLineMoveDistanceItem::GetFirstPointOnMaster(void) const
{
	MeasureCommon	*Ret=NULL;

	if(LineType1==1){
		AlgorithmInPagePI	*PPage=(AlgorithmInPagePI *)GetParentInPage();
		AlgorithmItemRoot	*p=PPage->SearchIDItem(LineID1);
		if(p!=NULL){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				Ret=a;
			}
		}
	}
	else if(LineType1==2){
		AlgorithmBase	*AHole=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
		AlgorithmInPagePI	*HPage=(AlgorithmInPagePI *)AHole->GetPageData(GetPage());
		AlgorithmItemRoot	*p=HPage->SearchIDItem(LineID1);
		if(p!=NULL){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				Ret=a;
			}
		}
	}
	return Ret;
}

MeasureCommon	*MeasureLineMoveDistanceItem::GetSecondPointOnMaster(void) const
{
	MeasureCommon	*Ret=NULL;

	if(LineType2==1){
		AlgorithmInPagePI	*PPage=(AlgorithmInPagePI *)GetParentInPage();
		AlgorithmItemRoot	*p=PPage->SearchIDItem(LineID2);
		if(p!=NULL){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				Ret=a;
			}
		}
	}
	else if(LineType2==2){
		AlgorithmBase	*AHole=GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
		AlgorithmInPagePI	*HPage=(AlgorithmInPagePI *)AHole->GetPageData(GetPage());
		AlgorithmItemRoot	*p=HPage->SearchIDItem(LineID2);
		if(p!=NULL){
			MeasureCommon	*a=dynamic_cast<MeasureCommon *>(p);
			if(a!=NULL){
				Ret=a;
			}
		}
	}
	return Ret;
}

bool	MeasureLineMoveDistanceItem::MakeDataToTransfer(QIODevice *f)
{
	if(::Save(f,RealLen)==false)
		return false;
	return true;
}


bool	MeasureLineMoveDistanceItem::GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2) const
{
	x1=y1=x2=y2=0;

	if(GetVector()==NULL)
		return false;

	double	X1,Y1,X2,Y2;
	MeasureCommon	*p1=GetFirstPointOnMaster();
	if(p1==NULL)
		return false;
	p1->GetDrawPoint(DrawPoint1,X1,Y1);

	MeasureCommon	*p2=GetSecondPointOnMaster();
	if(p2==NULL)
		return false;
	p2->GetDrawPoint(DrawPoint2,X2,Y2);
	
	x1=floor(min(X1,X2));
	y1=floor(min(Y1,Y2));
	x2=ceil(max(X1,X2));
	y2=ceil(max(Y1,Y2));
	return true;
}

double	MeasureLineMoveDistanceItem::GetDistanceInMaster(double	&X1,double &Y1,double &X2,double &Y2)
{
	MeasureCommon	*p1=GetFirstPointOnMaster();
	if(p1==NULL)
		return -1;
	p1->GetDrawPoint(DrawPoint1,X1,Y1);

	MeasureCommon	*p2=GetSecondPointOnMaster();
	if(p2==NULL)
		return -1;
	p2->GetDrawPoint(DrawPoint2,X2,Y2);

	return hypot(X1-X2,Y1-Y2);
}

ExeResult	MeasureLineMoveDistanceItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
																,ResultInItemRoot *Res
																,ExecuteInitialAfterEditInfo &EInfo)
{
	MeasureLineMoveItemBase::ExecuteInitialAfterEdit_InFunc(EInfo);
	if(GetVector()==NULL)
		return _ER_true;

	double	X1,Y1,X2,Y2;
	double	MasterLen=GetDistanceInMaster(X1,Y1,X2,Y2);
	if(MasterLen<0){
		return _ER_true;
	}
	double	Dx=X1-X2;
	double	Dy=Y1-Y2;
	double	L=hypot(Dx,Dy);
	if(L<=0.00001)
		return _ER_true;
	Dx/=L;
	Dy/=L;
	Dx*=10;
	Dy*=10;
	double	Vx=Dy;
	double	Vy=-Dx;

	XYClassArea	XYArea;
	XYArea.NPListPack<XYClass>::AppendList(new XYClass(X1-Vx,Y1-Vy));
	XYArea.NPListPack<XYClass>::AppendList(new XYClass(X1+Vx,Y1+Vy));
	XYArea.NPListPack<XYClass>::AppendList(new XYClass(X2+Vx,Y2+Vy));
	XYArea.NPListPack<XYClass>::AppendList(new XYClass(X2-Vx,Y2-Vy));
	XYArea.NPListPack<XYClass>::AppendList(new XYClass(X1-Vx,Y1-Vy));
	FlexArea	Area;
	XYArea.TransTo(Area);
	SetArea(Area);
	const MeasureLineMoveThreshold	*RThr=GetThresholdR();
	if(RThr->ModeToSetInInitial==true){
		GetThresholdW()->ThresholdM=MasterLen-GetParamGlobal()->TransformUnitToPixel(GetPage(),RThr->OKRangeInInitial);
		GetThresholdW()->ThresholdP=MasterLen+GetParamGlobal()->TransformUnitToPixel(GetPage(),RThr->OKRangeInInitial);
	}
	
	if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
	}
	else{
		double	Cx=(X1+X2)/2.0;
		double	Cy=(Y1+Y2)/2.0;
		MeasureCommon	*p1=GetFirstPointOnMaster();
		if(p1!=NULL){
			MeasureLineMoveLineItem	*L1=dynamic_cast<MeasureLineMoveLineItem *>(p1->GetAlgorithmItem());
			if(L1!=NULL){
				const MeasureLineMoveThreshold	*RThr=L1->GetThresholdR(GetLayersBase());
				if((RThr->SearchType==2
				 || RThr->SearchType==3 
				 || RThr->SearchType==5
				 || RThr->SearchType==6)){
					double	a=L1->GetDistance(Cx,Cy);
					double	LineLen=hypot(L1->X2OnMaster-L1->X1OnMaster,L1->Y2OnMaster-L1->Y1OnMaster);
					double	LineCx=(L1->X2OnMaster+L1->X1OnMaster)/2.0;
					double	LineCy=(L1->Y2OnMaster+L1->Y1OnMaster)/2.0;
					double	LVx=(L1->Y2OnMaster-L1->Y1OnMaster)/LineLen;
					double	LVy=-(L1->X2OnMaster-L1->X1OnMaster)/LineLen;

					if(a>0){
						L1->GetThresholdW()->PrevailLeft	=true;
						L1->GetThresholdW()->PrevailRight	=false;
					}
					else{
						L1->GetThresholdW()->PrevailLeft	=false;
						L1->GetThresholdW()->PrevailRight	=true;
					}
					double	d1=hypot(Cx-(LineCx+LVx),Cy-(LineCy+LVy));
					double	d2=hypot(Cx-(LineCx-LVx),Cy-(LineCy-LVy));
					if(d1<d2){
						L1->Vx=LVx;
						L1->Vy=LVy;
					}
					else{
						L1->Vx=-LVx;
						L1->Vy=-LVy;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bFrom0==false
					&& GenData.bHorizontal==true){
						L1->Vx=-L1->Vx;
						L1->Vy=-L1->Vy;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bFrom0==true
					&& GenData.bHorizontal==true){
						L1->GetThresholdW()->SearchType=6;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bHorizontal==false){
						L1->GetThresholdW()->SearchType=6;
					}
				}
			}
		}

		MeasureCommon	*p2=GetSecondPointOnMaster();
		if(p2!=NULL){
			MeasureLineMoveLineItem	*L2=dynamic_cast<MeasureLineMoveLineItem *>(p2->GetAlgorithmItem());
			if(L2!=NULL){
				const MeasureLineMoveThreshold	*RThr=L2->GetThresholdR(GetLayersBase());
				if((RThr->SearchType==2 
				 || RThr->SearchType==3 
				 || RThr->SearchType==5
				 || RThr->SearchType==6)){
					double	a=L2->GetDistance(Cx,Cy);
					double	LineLen=hypot(L2->X2OnMaster-L2->X1OnMaster,L2->Y2OnMaster-L2->Y1OnMaster);
					double	LineCx=(L2->X2OnMaster+L2->X1OnMaster)/2.0;
					double	LineCy=(L2->Y2OnMaster+L2->Y1OnMaster)/2.0;
					double	LVx=(L2->Y2OnMaster-L2->Y1OnMaster)/LineLen;
					double	LVy=-(L2->X2OnMaster-L2->X1OnMaster)/LineLen;
					if(a>0){
						L2->GetThresholdW()->PrevailLeft	=false;
						L2->GetThresholdW()->PrevailRight	=true;
					}
					else{
						L2->GetThresholdW()->PrevailLeft	=true;
						L2->GetThresholdW()->PrevailRight	=false;
					}
					double	d1=hypot(Cx-(LineCx+LVx),Cy-(LineCy+LVy));
					double	d2=hypot(Cx-(LineCx-LVx),Cy-(LineCy-LVy));
					if(d1<d2){
						L2->Vx=LVx;
						L2->Vy=LVy;
					}
					else{
						L2->Vx=-LVx;
						L2->Vy=-LVy;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bFrom0==true
					&& GenData.bHorizontal==true){
						L2->Vx=-L2->Vx;
						L2->Vy=-L2->Vy;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bFrom0==false
					&& GenData.bHorizontal==true){
						L2->GetThresholdW()->SearchType=6;
					}
					if(GenData.bOnlyInside==false
					&& GenData.bHorizontal==false){
						L2->GetThresholdW()->SearchType=6;
					}
				}
			}
		}
	}
	

	return _ER_true;
}

ExeResult	MeasureLineMoveDistanceItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	double	X1=0,Y1=0;
	double	X2=0,Y2=0;
	double	Sx1=0,Sy1=0;
	double	Sx2=0,Sy2=0;

	if(NoCalc==false || GetLayersBase()->GetGlobalPageNumb()==1){
		DataInPage	*DP=GetDataInPage();
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			RCmd.ItemID		=LineID1;
			RCmd.DrawPoint	=DrawPoint1;
			if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X1=LocalX;
				Y1=LocalY;
				Sx1=ACmd.ShiftX;
				Sy1=ACmd.ShiftY;
			}
		}
		else{
			MeasureCommon	*p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				if(p1->GetAlgorithmItem()->IsCalcDone()==false){
					return _ER_ReqRetryLater;
				}
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
				p1->GetShiftVector(Sx1,Sy1);
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			RCmd.ItemID		=LineID2;
			RCmd.DrawPoint	=DrawPoint2;
			if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false){
					return _ER_ReqRetryLater;
				}
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X2=LocalX;
				Y2=LocalY;
				Sx2=ACmd.ShiftX;
				Sy2=ACmd.ShiftY;
			}
		}
		else{
			MeasureCommon	*p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				if(p2->GetAlgorithmItem()->IsCalcDone()==false){
					return _ER_ReqRetryLater;
				}
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
				p2->GetShiftVector(Sx2,Sy2);
			}
		}
		
		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		RealLen=1.0;
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;

			double	t1=Sx1*Mx+Sy1*My;
			double	t2=Sx2*Mx+Sy2*My;

			DifLen=-t1+t2;

			ResultLen=hypot(X2-X1,Y2-Y1)+DifLen;
			RealLen=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),fabs(dx)-Sx1*Mx+Sx2*Mx,fabs(dy)-Sy1*My+Sy2*My);

		}
		const MeasureLineMoveThreshold	*RThr=GetThresholdR();
		if(RThr->OutputType==0){
			Res->SetResultDouble(RealLen);
		}
		else if(RThr->OutputType==1){
			double	CenterV=(RThr->ThresholdM+RThr->ThresholdP)/2.0;
			Res->SetResultDouble(GetParamGlobal()->TransformPixelToUnit(GetPage(),ResultLen-CenterV));
		}
		if(RThr->ThresholdM<=ResultLen && ResultLen<=RThr->ThresholdP){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
			LineMoveResultPosList	*r=new LineMoveResultPosList(this);
			GetArea().GetCenter(r->Px,r->Py);
			r->result=0x10000;
			r->ResultType=ResultPosList::_ResultDouble;
			r->SetResult(ResultLen);
			r->NGSize=99999999;
			Res->AddPosList(r);
		}
	}
	return _ER_true;
}

double	MeasureLineMoveDistanceItem::TrasnformUnitFromPixel(double Pixel)
{
	double	X1=0,Y1=0;
	double	X2=0,Y2=0;

	if(NoCalc==false || GetLayersBase()->GetGlobalPageNumb()==1){
		DataInPage	*DP=GetDataInPage();
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			RCmd.ItemID		=LineID1;
			RCmd.DrawPoint	=DrawPoint1;
			if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X1=LocalX;
				Y1=LocalY;
			}
		}
		else{
			MeasureCommon	*p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			RCmd.ItemID		=LineID2;
			RCmd.DrawPoint	=DrawPoint2;
			if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X2=LocalX;
				Y2=LocalY;
			}
		}
		else{
			MeasureCommon	*p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
			}
		}
		
		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		RealLen=1.0;
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;
			RealLen=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),Pixel*Mx,Pixel*My);
			return RealLen;
		}
		return 0;
	}
	return GetParamGlobal()->TransformPixelToUnit(GetPage(),Pixel);
}
double	MeasureLineMoveDistanceItem::TransformPixelFromUnit(double Unit)
{
	double	X1=0,Y1=0;
	double	X2=0,Y2=0;

	if(NoCalc==false || GetLayersBase()->GetGlobalPageNumb()==1){
		DataInPage	*DP=GetDataInPage();
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			RCmd.ItemID		=LineID1;
			RCmd.DrawPoint	=DrawPoint1;
			if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X1=LocalX;
				Y1=LocalY;
			}
		}
		else{
			MeasureCommon	*p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			RCmd.ItemID		=LineID2;
			RCmd.DrawPoint	=DrawPoint2;
			if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X2=LocalX;
				Y2=LocalY;
			}
		}
		else{
			MeasureCommon	*p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
			}
		}
		
		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		RealLen=1.0;
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;
			RealLen=GetParamGlobal()->TransformUnitDistanceToPixel(GetPage(),Unit*Mx,Unit*My);
			return RealLen;
		}
		return 0;
	}
	return GetParamGlobal()->TransformUnitToPixel(GetPage(),Unit);
}


void	MeasureLineMoveDistanceItem::ExecuteProcessingLocal(MeasureCommon *TargetLine1,MeasureCommon *TargetLine2,ResultInItemRoot *Res)
{
	double	X1=0,Y1=0;
	double	X2=0,Y2=0;
	double	Sx1=0,Sy1=0;
	double	Sx2=0,Sy2=0;

	if(NoCalc==false || GetLayersBase()->GetGlobalPageNumb()==1){
		TargetLine1->GetDrawPoint(DrawPoint1,X1,Y1);
		TargetLine1->GetShiftVector(Sx1,Sy1);

		TargetLine2->GetDrawPoint(DrawPoint2,X2,Y2);
		TargetLine2->GetShiftVector(Sx2,Sy2);

		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		RealLen=1.0;
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;

			double	t1=Sx1*Mx+Sy1*My;
			double	t2=Sx2*Mx+Sy2*My;

			DifLen=-t1+t2;

			ResultLen=hypot(X2-X1,Y2-Y1)+DifLen;
			RealLen=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),dx,dy);

		}
		const MeasureLineMoveThreshold	*RThr=GetThresholdR();
		if(RThr->OutputType==0){
			Res->SetResultDouble(RealLen);
		}
		else if(RThr->OutputType==1){
			double	CenterV=(RThr->ThresholdM+RThr->ThresholdP)/2.0;
			Res->SetResultDouble(GetParamGlobal()->TransformPixelToUnit(GetPage(),ResultLen-CenterV));
		}
		if(RThr->ThresholdM<=ResultLen && ResultLen<=RThr->ThresholdP){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
			LineMoveResultPosList	*r=new LineMoveResultPosList(this);
			GetArea().GetCenter(r->Px,r->Py);
			r->result=0x10000;
			r->ResultType=ResultPosList::_ResultDouble;
			r->SetResult(ResultLen);
			r->NGSize=99999999;
			Res->AddPosList(r);
		}
	}
}
void	MeasureLineMoveDistanceItem::SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	GetThresholdW()->Save(&Buff);
	LayersBase	*Base=GetLayersBase();
	GetThresholdW()->CopyFrom(*((MeasureLineMoveThreshold *)reqPacket->ItemDistance.GetThresholdR(Base)));
	ExecuteProcessing(0,0,Packet->Result);
	Packet->PosDiffX	=ResultLen;
	Packet->PosDiffY	=0;
	Packet->Error		=0;
	Packet->Distance	=ResultLen;
	Packet->RealDistance=Packet->Result->GetResultDouble();

	Buff.seek(0);
	GetThresholdW()->Load(&Buff);
}

bool	MeasureLineMoveDistanceItem::IsInclude(int x ,int y)	const
{
	double	X1=0,Y1=0;
	double	X2=0,Y2=0;
	double	Sx1,Sy1;
	double	Sx2,Sy2;

	if(NoCalc==false || GetLayersBase()->GetGlobalPageNumb()==1){
		DataInPage	*DP=GetDataInPage();
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line1InGlobalPage);
			RCmd.ItemID		=LineID1;
			RCmd.DrawPoint	=DrawPoint1;
			if(RCmd.Send(Line1InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line1InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X1=LocalX;
				Y1=LocalY;
				Sx1=ACmd.ShiftX;
				Sy1=ACmd.ShiftY;
			}
			else{
				return false;
			}
		}
		else{
			MeasureCommon	*p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
				p1->GetShiftVector(Sx1,Sy1);
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
			SlaveCommReqResultPosition	RCmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			SlaveCommAckResultPosition	ACmd(GetLayersBase(),sRoot,sName,Line2InGlobalPage);
			RCmd.ItemID		=LineID2;
			RCmd.DrawPoint	=DrawPoint2;
			if(RCmd.Send(Line2InGlobalPage,0,ACmd)==true){
				if(ACmd.CalcDone==false)
					return _ER_ReqRetryLater;
				int GlobalX ,GlobalY;
				GetLayersBase()->GetGlobalMatrixFromLocal(Line2InGlobalPage,ACmd.MasterLocalX ,ACmd.MasterLocalY,GlobalX ,GlobalY);
				int	LocalX,LocalY;
				DP->GetLocalMatrixFromGlobalInMaster(GlobalX ,GlobalY ,LocalX,LocalY);
				X2=LocalX;
				Y2=LocalY;
				Sx2=ACmd.ShiftX;
				Sy2=ACmd.ShiftY;
			}
		}
		else{
			MeasureCommon	*p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
				p2->GetShiftVector(Sx2,Sy2);
			}
		}
		double	L=GetLengthLine2Point(X1,Y1,X2,Y2,(double)x,(double)y);
		if(L<10){
			return true;
		}
	}
	return false;
}

void	MeasureLineMoveDistanceItem::SetEndPoint(int EndNo ,int X ,int Y)
{
	double	X1,Y1,X2,Y2;
	GetDistanceInMaster(X1,Y1,X2,Y2);

	double	dx=X2-X1;
	double	dy=Y2-Y1;
	double	Len=hypot(dx,dy);
	if(Len<0.00000001)
		return;

	MeasureCommon	*P=NULL;
	double	*DrawPoint=NULL;
	if(EndNo==0){
		P=GetFirstPointOnMaster();
		DrawPoint=&DrawPoint1;
	}
	else{
		P=GetSecondPointOnMaster();
		DrawPoint=&DrawPoint2;
	}

	if(P==NULL)
		return;
	double	OldCx,OldCy;
	P->GetCenterPoint(OldCx,OldCy);
	P->Move(X-OldCx,Y-OldCy);
	//double	Cx,Cy;
	//P->GetCenterPoint(Cx,Cy);
	*DrawPoint=P->GetTParam(X1,Y1,X2,Y2);
}

ExeResult	MeasureLineMoveDistanceItem::ExecutePostProcessing	(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ExeResult	Ret=MeasureLineMoveItemBase::ExecutePostProcessing	(ExeID,ThreadNo,Res);

	MeasureCommon	*p1=GetFirstPointOnMaster();
	MeasureCommon	*p2=GetSecondPointOnMaster();
	if(p1!=NULL && p2!=NULL){
		MeasureLineMoveItemBase *L1=(MeasureLineMoveItemBase *)(p1->GetAlgorithmItem());
		MeasureLineMoveItemBase *L2=(MeasureLineMoveItemBase *)(p2->GetAlgorithmItem());
		struct ResultDistanceForExtraData	RData;

		MeasureLineMoveBase	*ABase=(MeasureLineMoveBase *)GetParentBase();
		bool	ArrowEnableMakeImage	=ABase->ResultArrowEnableMakeImage		;
		bool	ArrowEnableDrawLine		=ABase->ResultArrowEnableDrawLine		;
		bool	DistanceEnableMakeImage	=ABase->ResultDistanceEnableMakeImage	;
		bool	DistanceEnableDrawLine	=ABase->ResultDistanceEnableDrawLine	;

		bool	CreatedImage=false;
		if(Res->IsOk()==false
		&& L1->IsEnableMakeImage()==true
		&& L2->IsEnableMakeImage()==true
		&& IsEnableMakeImage()==true){
			L1->MakeResultImage(RData.TargetImageSide1X1,RData.TargetImageSide1Y1,RData.TargetImageSide1ZoomRate
								,ArrowEnableMakeImage,ArrowEnableDrawLine);
			L2->MakeResultImage(RData.TargetImageSide2X1,RData.TargetImageSide2Y1,RData.TargetImageSide2ZoomRate
								,ArrowEnableMakeImage,ArrowEnableDrawLine);
			MakeResultImage(RData.TargetImageX1,RData.TargetImageY1,RData.TargetImageZoomRate
							,DistanceEnableMakeImage,DistanceEnableDrawLine);
			CreatedImage=true;
		}
		double	Sx1,Sy1;
		double	Sx2,Sy2;
		double	Cx1,Cy1;
		double	Cx2,Cy2;
		double	X1,Y1,X2,Y2;
		p1->GetCenterPoint(Cx1,Cy1);
		p1->GetShiftVector(Sx1,Sy1);
		p1->GetDrawPoint(DrawPoint1,X1,Y1);

		p2->GetCenterPoint(Cx2,Cy2);
		p2->GetShiftVector(Sx2,Sy2);
		p2->GetDrawPoint(DrawPoint2,X2,Y2);

		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;
			RData.Cx1=Cx1;
			RData.Cy1=Cy1;
			RData.Sx1=Sx1;
			RData.Sy1=Sy1;
			RData.Cx2=Cx2;
			RData.Cy2=Cy2;
			RData.Sx2=Sx2;
			RData.Sy2=Sy2;
			RData.DistanceX1=X1;
			RData.DistanceY1=Y1;
			RData.DistanceX2=X2;
			RData.DistanceY2=Y2;
			RData.DistanceThresholdM	=GetThresholdR()->ThresholdM;
			RData.DistanceThresholdP	=GetThresholdR()->ThresholdP;
			RData.DistanceThresholdMMM	=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),GetThresholdR()->ThresholdM*Mx,GetThresholdR()->ThresholdM*My);
			RData.DistanceThresholdPMM	=GetParamGlobal()->TransformPixelDistanceToUnit(GetPage(),GetThresholdR()->ThresholdP*Mx,GetThresholdR()->ThresholdP*My);
			RData.ResultDistanceMM		=RealLen;
			RData.ResultDistance		=ResultLen;

			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			Buff.write((const char *)&RData,sizeof(RData));
			if(ABase->SaveItemImage==true && CreatedImage==true){
				::Save(&Buff,L1->TResultImage);
				::Save(&Buff,L1->LResultImage);
				::Save(&Buff,L2->TResultImage);
				::Save(&Buff,L2->LResultImage);
				::Save(&Buff,TResultImage);
				::Save(&Buff,LResultImage);
			}
			ResultExtraData=Buff.buffer();
		}
	}
	return Ret;
}

void	MeasureLineMoveDistanceItem::MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)
{
	int	ImageWL=TResultImage.width();
	int	ImageHL=TResultImage.height();
	MeasureCommon	*p1=NULL;
	MeasureCommon	*p2=NULL;
	double	Sx1,Sy1;
	double	Sx2,Sy2;
	double	X1,Y1;
	double	X2,Y2;
	DataInPage	*DP=GetDataInPage();
	if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
	}
	else{
		p1=GetFirstPointOnMaster();
		if(p1!=NULL){
			if(p1->GetAlgorithmItem()->IsCalcDone()==false){
				return;
			}
			p1->GetDrawPoint(DrawPoint1,X1,Y1);
			p1->GetShiftVector(Sx1,Sy1);
		}
	}
	
	if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
	}
	else{
		p2=GetSecondPointOnMaster();
		if(p2!=NULL){
			if(p2->GetAlgorithmItem()->IsCalcDone()==false){
				return;
			}
			p2->GetDrawPoint(DrawPoint2,X2,Y2);
			p2->GetShiftVector(Sx2,Sy2);
		}
	}

	int	x1,y1,x2,y2;
	if(ImageWL!=0 && ImageHL!=0 && p1!=NULL && p2!=NULL 
	&& GetXY(x1,y1,x2,y2)==true){
		double	cx=(x1+x2)/2.0;
		double	cy=(y1+y2)/2.0;

		ImagePointerContainer TargetImageList;
		GetTargetBuffList(TargetImageList);

		double	Zx=99999999;
		double	Zy=99999999;
		if(x1!=x2)
			Zx=ImageWL/((double)(x2-x1));
		if(y1!=y2)
			Zy=ImageHL/((double)(y2-y1));

		ImageZoomRate=min(Zx,Zy);
		double	Z=1.0/ImageZoomRate;
		double	sx=(Sx1+Sx2)/2;
		double	sy=(Sy1+Sy2)/2;

		ImageX1=cx+sx-ImageWL*Z/2;
		ImageY1=cy+sy-ImageHL*Z/2;
		if(EnableMakeImage==true){
			TargetImageList.MakeImage(TResultImage,-ImageX1,-ImageY1,ImageZoomRate,false);
		}
		LResultImage.fill(qRgba(0,0,0,0));

		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		if(M>0){
			double	Mx=dx/M;
			double	My=dy/M;

			double	t1=Sx1*Mx+Sy1*My;
			double	t2=Sx2*Mx+Sy2*My;
			double	mX1=X1+Sx1;
			double	mY1=Y1+Sy1;
			double	mX2=X2+Sx2;
			double	mY2=Y2+Sy2;
			int	MovX=-ImageX1;
			int	MovY=-ImageY1;

			DifLen=t2-t1;

			if(EnableDrawLine==true){
				QPainter	Pnt(&LResultImage);
				Pnt.setPen(Qt::red);
				Pnt.setBrush(Qt::red);
				DrawArrow((mX1+mX2)/2,(mY1+mY2)/2,mX1,mY1
						,Pnt ,MovX ,MovY ,ImageZoomRate,20);
				DrawArrow((mX1+mX2)/2,(mY1+mY2)/2,mX2,mY2
						,Pnt ,MovX ,MovY ,ImageZoomRate,20);
			}
		}
	}
}
void	MeasureLineMoveDistanceItem::UpdateThreshold(int LearningMenuID ,LearningResource &LRes)
{
	if(LearningMenuID==LearningMenu_MeasureLineMove_OK_ByDistance){
		MeasureCommon	*p1=NULL;
		MeasureCommon	*p2=NULL;
		double	X1=0,Y1=0;
		double	X2=0,Y2=0;
		if(Line1InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		}
		else{
			p1=GetFirstPointOnMaster();
			if(p1!=NULL){
				p1->GetDrawPoint(DrawPoint1,X1,Y1);
			}
		}
		
		if(Line2InGlobalPage>=0 && GetLayersBase()->GetGlobalPageNumb()>1){
		}
		else{
			p2=GetSecondPointOnMaster();
			if(p2!=NULL){
				p2->GetDrawPoint(DrawPoint2,X2,Y2);
			}
		}

		double	dx=X2-X1;
		double	dy=Y2-Y1;
		double	M =hypot(dx,dy);
		if(M>0 && p1!=NULL && p2!=NULL){
			double	Mx=dx/M;
			double	My=dy/M;

			double	RUnit=LRes.DoubleCause;
			double	RPixels =GetParamGlobal()->TransformUnitDistanceToPixel(GetPage(),RUnit*Mx,RUnit*My);

			MeasureLineMoveThreshold	*WThr=GetThresholdW();
			if(RPixels<WThr->ThresholdM){
				WThr->ThresholdM=RPixels;
			}
			else
			if(RPixels>WThr->ThresholdP){
				WThr->ThresholdP=RPixels;
			}
		}
	}
	if(LearningMenuID==LearningMenu_MeasureLineMove_OK_BySide1){
		MeasureCommon	*p1=GetFirstPointOnMaster();
		if(p1!=NULL){
			MeasureLineMoveThreshold	*WThr=(MeasureLineMoveThreshold *)p1->GetAlgorithmItem()->GetThresholdBaseWritable();
			WThr->SearchDot+=2;
		}
	}
	if(LearningMenuID==LearningMenu_MeasureLineMove_OK_BySide2){
		MeasureCommon	*p2=GetSecondPointOnMaster();
		if(p2!=NULL){
			MeasureLineMoveThreshold	*WThr=(MeasureLineMoveThreshold *)p2->GetAlgorithmItem()->GetThresholdBaseWritable();
			WThr->SearchDot+=2;
		}

	}
}
//=======================================================================================================
