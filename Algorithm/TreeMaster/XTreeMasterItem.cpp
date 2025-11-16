/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TreeMaster\XTreeMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTreeMaster.h"
#include "XGeneralFunc.h"
#include <QColor>
#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>

//=============================================================================
TreeMasterItem::TreeMasterItem(void)
{	
	MasterCode		=-1;
	ResultE			=1.0;
	ResultShape		=1.0;
	ResultColor		=1.0;
	AlertMark		=false;

	TMItemID			=0;
	ResultDx=ResultDy	=0;
	ResultOk			=true;

}
TreeMasterItem::~TreeMasterItem(void)
{
}

bool    TreeMasterItem::Save(QIODevice *f)
{
	if(AlgorithmItemPI::Save(f)==false)
		return false;

	WORD	Ver=3;

	if(::Save(f,Ver)==false)
		return(false);
	if(::Save(f,TMItemID)==false)
		return false;
	if(::Save(f,MasterCode)==false)
		return false;
	if(::Save(f,CatName)==false)
		return false;
	if(::Save(f,MasterName)==false)
		return false;

	if(MatchingArea.Save(f)==false)
		return false;
	if(ShapeMask.Save(f)==false)
		return false;
	if(ShapeList.Save(f)==false)
		return false;
	if(::Save(f,AlertMark)==false)
		return false;

	return true;
}
bool    TreeMasterItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(f,LBase)==false)
		return false;

	WORD	Ver;
	if(::Load(f,Ver)==false)
		return(false);
	if(::Load(f,TMItemID)==false)
		return false;
	if(::Load(f,MasterCode)==false)
		return(false);
	if(::Load(f,CatName)==false)
		return false;
	if(::Load(f,MasterName)==false)
		return false;

	if(MatchingArea.Load(f)==false)
		return false;
	if(ShapeMask.Load(f)==false)
		return false;
	if(Ver>=2){
		if(ShapeList.Load(f)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,AlertMark)==false)
			return false;
	}

	return true;
}

QString	TreeMasterItem::GetShapeCode(void)
{
	QStringList	List=MasterName.split("-");
	return List[0];
}

void	TreeMasterItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	//QRgb	acol=qRgba(40,255,0,128);
	//QRgb scol = qRgba(255,40,0,128);

	TreeMasterDrawAttr	*tAttr=dynamic_cast<TreeMasterDrawAttr *>(Attr);
	if(tAttr!=NULL){
		if(tAttr->ShowingMasterCode==-1 || tAttr->ShowingMasterCode==MasterCode){
			for(AreaWithColor *a=MatchingArea.GetFirst();a!=NULL;a=a->GetNext()){
				if(GetSelected()){
					a->GetArea().DrawAlpha(0,0,&pnt,Attr->SelectedColor.rgba(),ZoomRate,movx,movy,false);
				}	
				else{
					a->GetArea().DrawAlpha(0,0,&pnt ,Attr->NormalColor.rgba()
											,ZoomRate ,movx ,movy
											,false);
				}
			}
			for(FlexAreaImageList *b=ShapeList.GetFirst();b!=NULL;b=b->GetNext()){
				if(GetSelected()){
					b->DrawImage(0,0 ,&pnt	
								,ZoomRate ,movx ,movy
								,true ,false ,true,0x80);
				}
				else{
					b->DrawImage(0,0 ,&pnt	
								,ZoomRate ,movx ,movy
								,false,true ,true,0x80);
				}
			}

			QRgb	mcol=qRgba(160,220,0,128);
			ShapeMask.DrawAlpha(0,0,&pnt ,mcol
										,ZoomRate ,movx ,movy
										,false);
		}
	}
}

void	TreeMasterItem::RemoveArea(void)
{
	ShapeList.RemoveAll();
	MatchingArea.RemoveAll();
}

void	TreeMasterItem::ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems)
{
	AlgorithmItemPI::ExecuteMove(GlobalDx,GlobalDy,AllItems);

	if(((GetEditLocked()==false) && (GetVisible()==true)) || AllItems==true){
		MatchingArea.MoveTo(GlobalDx,GlobalDy);
		ShapeMask.MoveToNoClip(GlobalDx,GlobalDy);
	}
}

ExeResult	TreeMasterItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	AlgorithmItemPITemplate<TreeMasterInPage,TreeMasterBase>::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	ImageBuffer	*ImageList[10];
	GetMasterBuffList(ImageList);
	ImageBuffer *Buffer=ImageList[1];
	for(FlexAreaImageList *b=ShapeList.GetFirst();b!=NULL;b=b->GetNext()){
		FlexAreaImageListCoeff	*Lb=(FlexAreaImageListCoeff *)b;
		Lb->MakeSum();
	}

	return _ER_true;
}

ExeResult	TreeMasterItem::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

	if(MatchingArea.IsEmpty()==true && ShapeList.IsEmpty()==true)
		return _ER_true;

	TreeMasterBase	*Tb=(TreeMasterBase *)GetParentBase();
	if(Tb->PickedMasterCode>=0 && Tb->PickedMasterCode!=MasterCode){
		ResultColor=0;
		ResultShape=0;
		ResultOk=true;
		ResultE=0;
		return _ER_true;
	}
	const TreeMasterThreshold	*R=GetThresholdR();

	ResultShape=0;
	ResultDx=0;
	ResultDy=0;
	if(Tb->PickedMasterCode==MasterCode){

		int	SearchDot=R->SearchDot;
		ImageBuffer	*ImageList[10];
		GetTargetBuffList(ImageList);
		ImageBuffer *Buffer=ImageList[1];
		//#pragma omp parallel
		//{
			//#pragma omp for
			for(int dy=-SearchDot;dy<=SearchDot;dy++){
				for(int dx=-SearchDot;dx<=SearchDot;dx++){
					double	MatchD=1.0;
					for(FlexAreaImageList *b=ShapeList.GetFirst();b!=NULL;b=b->GetNext()){
						FlexAreaImageListCoeff	*Lb=(FlexAreaImageListCoeff *)b;
						double	d=Lb->CalcCoeff(dx	,dy	,*Buffer);
						MatchD*=d;
					}
					#pragma omp critical
					if(MatchD>ResultShape){
						ResultDx=dx;
						ResultDy=dy;
						ResultShape=MatchD;
					}
				}
			}
		//}
	}

	ExecutePreProcessingColor	(ResultDx,ResultDy);

	if(MasterCode==GetLayersBase()->GetMasterCode()){
		TreeMasterInPage* Page = (TreeMasterInPage *)Parent;
	}
	if(ResultShape>0){
		ResultE=ResultShape*ResultColor;
	}
	else{
		ResultE=1.0;
	}

	if(R->ThreColor>ResultColor || R->ThreShape>ResultShape){
		ResultOk=false;
		Res->SetError(2);
	}
	else{
		ResultOk=true;
		Res->SetError(1);
	}

	return _ER_true;
}

ExeResult	TreeMasterItem::ExecutePreProcessingColor	(int dx ,int dy)
{
	ResultColor=1.0;
	for(AreaWithColor *a=MatchingArea.GetFirst();a!=NULL;a=a->GetNext()){
		double	D=GetColorLength(*a ,dx,dy);
		double	E=exp(-D/20);
		ResultColor*=E;
	}
	return _ER_true;
}

double	TreeMasterItem::GetColorLength(AreaWithColor &s ,int mx ,int my)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer *[Ln];
	else
		ImagePoint=ImageList;

	GetTargetBuffList(ImagePoint);

	FlexArea	&A=s.GetArea();

	QRgb	c=s.Color.GetFirstBase()->GetCenter();
	int		cR=qRed(c);
	int		cG=qGreen(c);
	int		cB=qBlue(c);

	if(Ln>=3){
		double	DMin=99999999;
		for(int i=0;i<A.GetFLineLen();i++){
			int	y =A.GetFLineAbsY  (i)+my;
			int	x1=A.GetFLineLeftX (i)+mx;
			int	x2=A.GetFLineRightX(i)+mx;
			BYTE	*srcR=ImagePoint[0]->GetY(y);
			BYTE	*srcG=ImagePoint[1]->GetY(y);
			BYTE	*srcB=ImagePoint[2]->GetY(y);

			for(int x=x1;x<x2;x++){
				double	D=(srcR[x]-cR)*(srcR[x]-cR) + (srcG[x]-cG)*(srcG[x]-cG) + (srcB[x]-cB)*(srcB[x]-cB);
				if(DMin>D){
					DMin=D;
				}
			}
		}
		return DMin;
	}
	return 99999999;
}
