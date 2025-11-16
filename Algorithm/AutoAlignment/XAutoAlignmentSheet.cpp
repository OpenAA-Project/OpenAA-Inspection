/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignmentSheet.cpp
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
#include "XColorSpace.h"
#include "XDisplayBitImage.h"
#include "XPointer.h"
#include "XCriticalFunc.h"
#include "XImageProcess.h"
#define _USE_MATH_DEFINES
#include "math.h"

int	PDbg=0;
static	int	AADbg=0;
static	int	AADbgX=5500;
static	int	AADbgY=14400;

AutoAlignmentSheet::AutoAlignmentSheet(void)
{
	MasterMap=NULL;
	Picos	=NULL;
	PicosCount=0;
	CreatedManual=false;

	PickupBmp=NULL;
}
AutoAlignmentSheet::~AutoAlignmentSheet(void)
{
	DeleteMatrixBuff(MasterMap,GetMaxLines());
	MasterMap=NULL;
	if(Picos!=NULL){
		for(int i=0;i<PicosCount;i++){
			delete	Picos[i];
		}
		delete	[]Picos;
		Picos=NULL;
	}
	PicosCount=0;
	CPicoDim.RemoveAll();

	DeleteMatrixBuff(PickupBmp,GetMaxLines());
	PickupBmp=NULL;
}

bool    AutoAlignmentSheet::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;
	if(::Save(file,CreatedManual)==false)
		return false;
	return true;
}
bool    AutoAlignmentSheet::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;
	if(::Load(file,CreatedManual)==false)
		return false;
	return true;
}

ExeResult	AutoAlignmentSheet::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),6);
	GetLayersBase()->StepProcessing(GetPage());

	//PickupTestのロジックを関数にまとめる
	int		TransW;
	int		NoiseShrink;
	BYTE	**TmpMap,**TmpMap2;
	MakePickupTest(&TmpMap,&TmpMap2,TransW,NoiseShrink);

	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)GetParentInPage();
	AutoAlignmentBase	*PBase=(AutoAlignmentBase *)GetParentBase();

	BYTE	**OtherMap	=MakeMatrixBuff(XByte,GetMaxLines());

	GetLayersBase()->FatAreaN(MasterMap
					,TmpMap
					,XByte,GetMaxLines()
					,NoiseShrink);

	GetLayersBase()->ThinAreaN(MasterMap
					,TmpMap
					,XByte,GetMaxLines()
					,NoiseShrink);

	if(NoiseShrink>0){
		for(int i=0;i<1;i++){
			::ThinArea(MasterMap
						,TmpMap
						,XByte,GetMaxLines());
		}
		for(int i=0;i<1;i++){
			::FatArea(MasterMap
						,TmpMap
						,XByte,GetMaxLines());
		}
	}
	MatrixBuffCopy(TmpMap2					,XByte,GetMaxLines()
                 , (const BYTE **)MasterMap	,XByte,GetMaxLines());
	PureFlexAreaListContainer MasterFPack;
	PickupFlexArea(MasterMap ,XByte ,GetDotPerLine(),GetMaxLines() ,MasterFPack);

	GetLayersBase()->StepProcessing(GetPage());

	/*
	for(int i=0;i<2;i++){
		::ThinArea(TmpMap2
				,TmpMap
				,XByte,GetMaxLines());
	}
	*/
	for(int i=0;i<1;i++){
		::FatArea(MasterMap
					,TmpMap
					,XByte,GetMaxLines());
	}

	MatrixBuffNotAnd(MasterMap,(const BYTE **)TmpMap2,XByte,GetMaxLines());
	//ここで輪郭化
	PureFlexAreaListContainer OutlineFPack;
	PickupFlexArea(MasterMap ,XByte ,GetDotPerLine(),GetMaxLines() ,OutlineFPack);

	for(PureFlexAreaList *f=MasterFPack.GetFirst();f!=NULL;f=f->GetNext()){
		if(f->IsInclude(AADbgX,AADbgY)==true){
			AADbg++;
		}
		if(f->GetWidth()<PBase->MaxHoleSize && f->GetHeight()<PBase->MaxHoleSize){
			XYClassCluster XY;
			f->MakeOutlineDot(XY);
			if(XY.GetCount()>=2){
				XYClassArea	*t1=XY.GetFirst();
				XYClassArea	*t2=t1->NPList<XYClassArea>::GetNext();
				int	Cx,Cy;
				//内側輪郭を抽出する
				if(t1->GetDotCount()>t2->GetDotCount()){
					XYClass	*a=t2->NPListPack<XYClass>::GetFirst();
					Cx=a->x;
					Cy=a->y;
				}
				else{
					XYClass	*a=t1->NPListPack<XYClass>::GetFirst();
					Cx=a->x;
					Cy=a->y;
				}
				//穴と思われる内側輪郭を排除する
				for(PureFlexAreaList *g=OutlineFPack.GetFirst();g!=NULL;g=g->GetNext()){
					if(g->IsInclude(Cx,Cy)==true
					|| g->IsInclude(Cx-1,Cy-1)==true
					|| g->IsInclude(Cx  ,Cy-1)==true
					|| g->IsInclude(Cx+1,Cy-1)==true
					|| g->IsInclude(Cx-1,Cy  )==true
					|| g->IsInclude(Cx+1,Cy  )==true
					|| g->IsInclude(Cx-1,Cy+1)==true
					|| g->IsInclude(Cx  ,Cy+1)==true
					|| g->IsInclude(Cx+1,Cy+1)==true){
						OutlineFPack.RemoveList(g);
						delete	g;
						break;
					}
				}
			}
		}
	}

	GetLayersBase()->StepProcessing(GetPage());

	MatrixBuffClear(MasterMap,0,XByte,GetMaxLines());
	for(PureFlexAreaList *a=OutlineFPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->MakeBitData(MasterMap,GetDotPerLine(),GetMaxLines());
	}
	GetLayersBase()->FatAreaN(MasterMap
					,TmpMap
					,XByte,GetMaxLines()
					,TransW-1);

	MatrixBuffCopy(OtherMap						,XByte,GetMaxLines()
					, (const BYTE **)PickupBmp	,XByte,GetMaxLines());

	int	MaxPicoShift=0;
	for(AlgorithmItemPI	*p=PPage->GetFirstData();p!=NULL;p=p->GetNext()){
		AutoAlignmentSheet	*aSeet;
		aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL && aSeet!=this){
			if(aSeet->GetThresholdR(GetLayersBase())->PicoShift>MaxPicoShift){
				MaxPicoShift=aSeet->GetThresholdR(GetLayersBase())->PicoShift;
			}
		}
	}
	const	AutoAlignmentThreshold	*RThr=GetThresholdR();
	GetLayersBase()->FatAreaN(OtherMap
				 ,TmpMap
				 ,XByte,GetMaxLines()
				 ,RThr->PicoShift+MaxPicoShift);

	//MatrixBuffNotAnd(OtherMap
	//				,PickupBmp
	//				,XByte,GetMaxLines());


	GetLayersBase()->StepProcessing(GetPage());

	MatrixBuffCopy(TmpMap2						,XByte,GetMaxLines()
					, (const BYTE **)MasterMap	,XByte,GetMaxLines());

	GetLayersBase()->FatAreaN(TmpMap2
				 ,TmpMap
				 ,XByte,GetMaxLines()
				 ,RThr->FringeWidth);

	/*
	if(Picos!=NULL){
		for(int i=0;i<PicosCount;i++){
			delete	Picos[i];
		}
		delete	[]Picos;
	}
	
	int	x1,y1,x2,y2;
	GetXY(x1,y1,x2,y2);
	PicoDimYNumb=(y2-y1+PBase->PicoSize-1)/PBase->PicoSize;
	PicoDimXNumb=(x2-x1+PBase->PicoSize-1)/PBase->PicoSize;
	PicoDim=new AutoAlignmentInPico**[PicoDimYNumb];
	for(int y=0;y<PicoDimYNumb;y++){
		PicoDim[y]=new AutoAlignmentInPico*[PicoDimXNumb];
	}

	GetLayersBase()->StepProcessing();

	PicosCount=0;
	int	MaxSearchDot=PPage->GetMaxSearchDot()+1;
	for(int y=0;y<PicoDimYNumb;y++){
		for(int x=0;x<PicoDimXNumb;x++){
			PicoDim[y][x]=new AutoAlignmentInPico(this,x,y);
			int	mx1=x*PBase->PicoSize+x1-MaxSearchDot;
			int	my1=y*PBase->PicoSize+y1-MaxSearchDot;
			int	mx2=(x+1)*PBase->PicoSize+x1+MaxSearchDot;
			int	my2=(y+1)*PBase->PicoSize+y1+MaxSearchDot;
			if(mx1<0){
				mx1=0;
			}
			if(my1<0){
				my1=0;
			}
			if(mx2>=GetDotPerLine()){
				mx2=GetDotPerLine()-1;
			}
			if(my2>=GetMaxLines()){
				my2=GetMaxLines()-1;
			}
			PicoDim[y][x]->Area.SetRectangle(mx1,my1,mx2,my2);
			PicoDim[y][x]->ExecuteInitialAfterEdit(MasterMap,XByte,GetMaxLines());
			PicoDim[y][x]->PickupArea.BuildFromRaster(PickupBmp,XByte,GetMaxLines()
													,0 ,0
													,mx1,my1,mx2,my2);
			PicoDim[y][x]->PickupAreaTarget=PicoDim[y][x]->PickupArea;
			PicoDim[y][x]->OtherArea.BuildFromRaster(OtherMap,XByte,GetMaxLines()
													,0 ,0
													,mx1,my1,mx2,my2);
			PicoDim[y][x]->FringeArea.BuildFromRaster(TmpMap2,XByte,GetMaxLines()
													,0 ,0
													,mx1,my1,mx2,my2);
			PicoDim[y][x]->MakeXYIndex();
			PicosCount++;
		}
	}
	*/
	GetLayersBase()->StepProcessing(GetPage());

	DeleteMatrixBuff(OtherMap	,GetMaxLines());
	DeleteMatrixBuff(TmpMap		,GetMaxLines());
	DeleteMatrixBuff(TmpMap2	,GetMaxLines());
///	DeleteMatrixBuff(PickupBmp,GetMaxLines());

	/*
	Picos=new AutoAlignmentInPico*[PicosCount];
	int	k=0;
	for(int y=0;y<PicoDimYNumb;y++){
		for(int x=0;x<PicoDimXNumb;x++){
			Picos[k]=PicoDim[y][x];
			k++;
		}
	}
	*/

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<PicosCount;i++){
			Picos[i]->OMasterArea.Sub(Picos[i]->OtherArea,Picos[i]->PickupArea);
			Picos[i]->OTargetArea.Sub(Picos[i]->OtherArea,Picos[i]->PickupAreaTarget);
		}
	}


	GetLayersBase()->StepProcessing(GetPage());

	return _ER_true;
}
ExeResult	AutoAlignmentSheet::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->ExecuteStartByInspection();
	}
	AutoAlignmentInPage	*APage=(AutoAlignmentInPage	*)GetParentInPage();
	GetArea().FillData(0x7F,(BYTE **)APage->ResultPerPixXFromTarget);
	GetArea().FillData(0x7F,(BYTE **)APage->ResultPerPixYFromTarget);
	return _ER_true;
}

struct	TmpAvrSL
{
	AutoAlignmentInPico	*P;
	double	dL;
};

static	int	TmpAvrSLDataFunc(const void *a ,const void *b)
{
	double	L=((struct TmpAvrSL *)a)->dL - ((struct TmpAvrSL *)b)->dL;
	if(L>0){
		return 1;
	}
	else if(L<0){
		return -1;
	}
	return 0;
}

struct VectorDim
{
	double	ShiftX,ShiftY;
};

static	int	FuncVectorDimX(const void *a ,const void *b)
{
	double	L=((struct VectorDim *)a)->ShiftX - ((struct VectorDim *)b)->ShiftX;
	if(L>0){
		return 1;
	}
	else if(L<0){
		return -1;
	}
	return 0;
}
static	int	FuncVectorDimY(const void *a ,const void *b)
{
	double	L=((struct VectorDim *)a)->ShiftY - ((struct VectorDim *)b)->ShiftY;
	if(L>0){
		return 1;
	}
	else if(L<0){
		return -1;
	}
	return 0;
}

ExeResult	AutoAlignmentSheet::ExecuteAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AutoAlignmentInPage	*APage=(AutoAlignmentInPage	*)GetParentInPage();
	AutoAlignmentBase	*pBase=(AutoAlignmentBase *)GetParentBase();

	if(pBase->Enabled==true){
		if(GetParamGlobal()->CalcSingleThread==false){
			#pragma omp parallel
			{
				#pragma omp for
				for(int i=0;i<PicosCount;i++){
					Picos[i]->ExecuteAlignment(APage->AlignedDx,APage->AlignedDy,APage->AlignedTheta);
				}
			}
		}
		else{
			for(int i=0;i<PicosCount;i++){
				Picos[i]->ExecuteAlignment(APage->AlignedDx,APage->AlignedDy,APage->AlignedTheta);
			}
		}
	}
	else{
		for(int i=0;i<PicosCount;i++){
			Picos[i]->ShiftX=0;
			Picos[i]->ShiftY=0;
			Picos[i]->MatchResult=0;
		}
	}

	for(ClusteredPicoDim *fm=CPicoDim.GetFirst();fm!=NULL;fm=fm->GetNext()){
		fm->CheckAbnormalVector();
	}

	//周囲と極端に異なるベクトルのPicoを不採用にする
	int	VectorMergin=pBase->VectorMergin;
	for(int i=0;i<PicosCount;i++){
		if(Picos[i]->Adopted==true){
			struct VectorDim	VDimX[250];
			struct VectorDim	VDimY[250];
			int		ANumb=0;
			for(int j=0;j<PicosCount;j++){
				int	nx=Picos[i]->Xn-Picos[j]->Xn;
				int	ny=Picos[i]->Yn-Picos[j]->Yn;
				if(abs(nx)<=2 && abs(ny)<=2 && Picos[j]->Adopted==true){
					VDimX[ANumb].ShiftX=Picos[j]->ShiftX;
					VDimX[ANumb].ShiftY=Picos[j]->ShiftY;
					ANumb++;
				}
			}
			if(ANumb>=3){
				memcpy(VDimY,VDimX,sizeof(VDimX[0])*ANumb);
				qsort(VDimX,ANumb,sizeof(VDimX[0]),FuncVectorDimX);
				qsort(VDimY,ANumb,sizeof(VDimY[0]),FuncVectorDimY);
				int	rN=ANumb/3;
				double	AShiftX=0;
				double	AShiftY=0;
				int	AKNumb=0;
				for(int k=rN;k<ANumb-rN;k++){
					AShiftX+=VDimX[k].ShiftX;
					AShiftY+=VDimY[k].ShiftY;
					AKNumb++;
				}
				if(AKNumb>0){
					AShiftX=AShiftX/AKNumb;
					AShiftY=AShiftY/AKNumb;
					if(Picos[i]->ShiftX<(AShiftX-VectorMergin) || (AShiftX+VectorMergin)<Picos[i]->ShiftX
					|| Picos[i]->ShiftY<(AShiftY-VectorMergin) || (AShiftY+VectorMergin)<Picos[i]->ShiftY){
						Picos[i]->ShiftX=AShiftX;
						Picos[i]->ShiftY=AShiftY;
					}
				}
			}
		}
	}
			

	//不採用Picoを周囲Picoを使って計算する
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PicosCount;i++){
				if(Picos[i]->Effective==false || Picos[i]->Adopted==false){
					Picos[i]->CalcFromSurround();
				}
			}
		}
	}
	else{
		for(int i=0;i<PicosCount;i++){
			if(Picos[i]->Effective==false || Picos[i]->Adopted==false){
				Picos[i]->CalcFromSurround();
			}
		}
	}
	//不採用Picoが周囲と２以上異なるとき、補正する
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PicosCount;i++){
				if(Picos[i]->Effective==false || Picos[i]->Adopted==false){
					Picos[i]->CalcAdjust();
				}
			}
		}
	}
	else{
		for(int i=0;i<PicosCount;i++){
			if(Picos[i]->Effective==false || Picos[i]->Adopted==false){
				Picos[i]->CalcAdjust();
			}
		}
	}
	bool	Changed;
	for(int k=0;k<30;k++){
		Changed=false;
		for(int i=0;i<PicosCount;i++){
			if(Picos[i]->Effective==false || Picos[i]->Adopted==false){
				if(Picos[i]->CalcAdjustAll()==true){
					Changed=true;
				}
			}
		}
		if(Changed==false){
			break;
		}
	}

	return _ER_true;
}

void	ClusteredPicoDim::CheckAbnormalVector(void)
{
	int	KxNumb=PicoDimXNumb/3;
	int	KyNumb=PicoDimYNumb/3;
	if(Parent->GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int xn=0;xn<=KxNumb;xn++){
				for(int yn=0;yn<=KyNumb;yn++){
					CheckAbnormalVector(KxNumb,KyNumb,xn,yn,3);
				}
			}
		}
	}
	else{
		for(int xn=0;xn<=KxNumb;xn++){
			for(int yn=0;yn<=KyNumb;yn++){
				CheckAbnormalVector(KxNumb,KyNumb,xn,yn,3);
			}
		}
	}
}


void	ClusteredPicoDim::CheckAbnormalVector(int KxNumb ,int KyNumb ,int xn ,int yn ,int DivN)
{
	//異常方向の移動ベクトルを不採用にする
	AutoAlignmentBase	*pBase=(AutoAlignmentBase *)Parent->GetParentBase();
	int	XCount=DivN;
	if(xn==KxNumb){
		XCount=PicoDimXNumb-xn*DivN;
	}
	int	YCount=DivN;
	if(yn==KyNumb){
		YCount=PicoDimYNumb-yn*3;
	}
	if(XCount==0 || YCount==0){
		return;
	}
	const	AutoAlignmentThreshold	*RThr=Parent->GetThresholdR(NULL);
	double	AddedVx=0;
	double	AddedVy=0;
	int		ACount=0;
	for(int x=0;x<XCount;x++){
		for(int y=0;y<YCount;y++){
			AutoAlignmentInPico	*P=PicoDim[y+yn*3][x+xn*3];
			if(P->Effective==true && P->MatchResult>RThr->AdptedMatchingRate){
				AddedVx+=P->ShiftX;
				AddedVy+=P->ShiftY;
				ACount++;
			}
		}
	}
	double	AvrVx=AddedVx/ACount;
	double	AvrVy=AddedVy/ACount;
	//double	AvrS=GetSita(AvrVx,AvrVy);
	double	AvrL=hypot(AvrVx,AvrVy);

	struct	TmpAvrSL	TmpAvrSLData[100];
	int	TmpAvrSLDataCount=0;

	for(int x=0;x<XCount;x++){
		for(int y=0;y<YCount;y++){
			AutoAlignmentInPico	*P=PicoDim[y+yn*3][x+xn*3];
			if(P->Effective==true){
				if(P->MatchResult>RThr->AdptedMatchingRate){
					double	L=hypot(P->ShiftX-AvrVx,P->ShiftY-AvrVy);
					TmpAvrSLData[TmpAvrSLDataCount].P=P;
					TmpAvrSLData[TmpAvrSLDataCount].dL=L;
					TmpAvrSLDataCount++;
				}
				else{
					P->Adopted=false;
				}
			}
		}
	}
	if(TmpAvrSLDataCount>4){
		Parent->CalcMutex.lock();
		QSort(TmpAvrSLData,TmpAvrSLDataCount,sizeof(TmpAvrSLData[0]),TmpAvrSLDataFunc);
		Parent->CalcMutex.unlock();
		for(int i=0;i<4 && i<TmpAvrSLDataCount;i++){
			TmpAvrSLData[i].P->Adopted=true;
		}
		for(int i=4;i<TmpAvrSLDataCount;i++){
			if(TmpAvrSLData[i].P->MatchResult>=RThr->CompletelyMatchingRate){
				TmpAvrSLData[i].P->Adopted=true;
			}
			else{
				TmpAvrSLData[i].P->Adopted=false;
			}
		}
	}
	else{
		for(int i=0;i<TmpAvrSLDataCount;i++){
			if(TmpAvrSLData[i].P->MatchResult>=RThr->AdptedMatchingRate){
				TmpAvrSLData[i].P->Adopted=true;
			}
			else{
				TmpAvrSLData[i].P->Adopted=false;
			}
		}
	}
}

void	AutoAlignmentSheet::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	if(Attr!=NULL){
		AutoAlignmentDrawAttr	*A=(AutoAlignmentDrawAttr *)Attr;
		if(A!=NULL && ((A->SelectedLDList.IsEmpty()==true) || A->SelectedLDList.IsInclude(GetLibID(),CreatedManual))){
			for(int i=0;i<PicosCount;i++){
				Picos[i]->Draw(pnt, movx ,movy ,ZoomRate ,Attr);
			}
			if(A->DrawSheetMode==1){
				if(GetSelected()==true){
					QColor	c=Attr->SelectedColor.rgba();
					c.setAlpha(100);
					GetArea().Draw(0,0 ,&pnt ,c.rgba()	,ZoomRate ,movx ,movy);
				}
				else if(A->DrawPico==false){
					QColor	c=Attr->NormalColor.rgba();
					c.setAlpha(100);
					GetArea().Draw(0,0 ,&pnt ,c.rgba()	,ZoomRate ,movx ,movy);
				}
			}
			else if(A->DrawSheetMode==2){
				if(MasterMap!=NULL){
					QColor	c=Attr->NormalColor.rgba();
					c.setAlpha(100);
					DrawBitImage(pnt,(const BYTE **)MasterMap ,GetDotPerLine() ,XByte ,GetMaxLines()
						,movx ,movy ,ZoomRate
						,0 ,0
						,c);
				}
			}
			else if(A->DrawSheetMode==3){
				if(PickupBmp!=NULL){
///					BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
					QColor	c=Attr->NormalColor.rgba();
					c.setAlpha(100);
					DrawBitImage(pnt, (const BYTE **)PickupBmp ,GetDotPerLine() ,XByte ,GetMaxLines()
						,movx ,movy ,ZoomRate
						,0,0
						,c/*BBase->ColorPickup*/);
				}
			}
		}
	}
	else{
		QColor	c=Qt::green;
		c.setAlpha(100);
		GetArea().Draw(0,0 ,&pnt ,c.rgba()	,ZoomRate ,movx ,movy);
	}
}
void	AutoAlignmentSheet::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);
	}
}

void	AutoAlignmentSheet::PickupMaster(BYTE **TmpMap)
{
	ImagePointerContainer Images;
	GetDataInPage()->GetMasterImages(Images);
	PickupBitmap(Images,MasterMap);
}


void	AutoAlignmentSheet::PickupBitmap(ImagePointerContainer &SrcImg ,BYTE **Map)
{
	MatrixBuffClear(Map,0,XByte,GetMaxLines());
	AutoAlignmentThreshold	*R=(AutoAlignmentThreshold	*)GetThresholdR();

	int	N=GetArea().GetFLineLen();
	if(SrcImg.GetCount()>=3){
		ImageBuffer	*rBuff=SrcImg.GetItem(0)->GetImage();
		ImageBuffer	*gBuff=SrcImg.GetItem(1)->GetImage();
		ImageBuffer	*bBuff=SrcImg.GetItem(2)->GetImage();
		for(int i=0;i<N;i++){
			int	Y=GetArea().GetFLineAbsY(i);
			int	X=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*r=&rBuff->GetY(Y)[X];
			BYTE	*g=&gBuff->GetY(Y)[X];
			BYTE	*b=&bBuff->GetY(Y)[X];
			BYTE	*iMap=Map[Y];
			while(Numb>=8){
				BYTE	s=R->PickupColor.Calc8(r,g,b,0);
				iMap[X>>3    ] |= s>>(X&7);
				iMap[(X>>3)+1] |= s<<(8-(X&7));
				X+=8;
				r+=8;
				g+=8;
				b+=8;
				Numb-=8;
			}
			for(int x=0;x<Numb;x++){
				if(R->PickupColor.Calc(*r,*g,*b,0)==true){
					iMap[X>>3] |= 0x80>>(X&7);
				}
				r++;
				g++;
				b++;
				X++;
			}
		}
	}
	else if(SrcImg.GetCount()==2){
		ImageBuffer	*rBuff=SrcImg.GetItem(0)->GetImage();
		ImageBuffer	*gBuff=SrcImg.GetItem(1)->GetImage();
		for(int i=0;i<N;i++){
			int	Y=GetArea().GetFLineAbsY(i);
			int	X=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*r=&rBuff->GetY(Y)[X];
			BYTE	*g=&gBuff->GetY(Y)[X];
			BYTE	*iMap=Map[Y];
			while(Numb>=8){
				BYTE	s=R->PickupColor.Calc8(r,g,g,0);
				iMap[X>>3    ] |= s>>(X&7);
				iMap[(X>>3)+1] |= s<<(8-(X&7));
				X+=8;
				r+=8;
				g+=8;
				Numb-=8;
			}
			for(int x=0;x<Numb;x++){
				if(R->PickupColor.Calc(*r,*g,*g,0)==true){
					iMap[X>>3] |= 0x80>>(X&7);
				}
				r++;
				g++;
				X++;
			}
		}
	}
	else if(SrcImg.GetCount()==1){
		ImageBuffer	*rBuff=SrcImg.GetItem(0)->GetImage();
		int		ColL, ColH;
		R->PickupColor.GetMonoColorRange(ColL, ColH);
		for(int i=0;i<N;i++){
			int	Y=GetArea().GetFLineAbsY(i);
			int	X=GetArea().GetFLineLeftX(i);
			int	Numb=GetArea().GetFLineNumb(i);
			BYTE	*r=&rBuff->GetY(Y)[X];
			BYTE	*iMap=Map[Y];
			for(int x=0;x<Numb;x++){
				if(ColL<=*r && *r<=ColH){
					iMap[X>>3] |= 0x80>>(X&7);
				}
				r++;
				X++;
			}
		}
	}
}

bool	AutoAlignmentSheet::ColorIsIncluded(AlignmentPacketWithColor *c ,int Mergin)
{
	AutoAlignmentThreshold	*Thr=(AutoAlignmentThreshold *)GetThresholdR();
	return Thr->PickupColor.Calc((BYTE)(c->R),(BYTE)(c->G),(BYTE)(c->B),Mergin);
}

bool	AutoAlignmentSheet::GetAlignment(AlignmentPacketWithColor *p)
{
	/*
	if(p!=NULL){
		for(int i=0;i<PicosCount;i++){
			if(Picos[i]->GetArea().IsInclude(p->PosXOnTarget,p->PosYOnTarget)==true){
				p->ShiftX=Picos[i]->AlignedDx;
				p->ShiftY=Picos[i]->AlignedDy;
				return true;
			}
		}
	}
	*/
	return false;
}

void	AutoAlignmentSheet::SetBasePointer(AutoAlignmentSheet	*BaseSheet)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->SetBasePointer(BaseSheet->Picos[i]);
	}
}


void	AutoAlignmentSheet::PutShiftMapAll(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)GetParentInPage();
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PicosCount;i++){
				Picos[i]->PutShiftMapAll(
								PPage->ResultPerPixXFromTarget,
								PPage->ResultPerPixYFromTarget,
								PPage->ResultPerPixXFromMaster,
								PPage->ResultPerPixYFromMaster,
								PPage->XLen,
								PPage->YLen);
			}
		}
	}
	else{
		for(int i=0;i<PicosCount;i++){
			Picos[i]->PutShiftMapAll(
								PPage->ResultPerPixXFromTarget,
								PPage->ResultPerPixYFromTarget,
								PPage->ResultPerPixXFromMaster,
								PPage->ResultPerPixYFromMaster,
								PPage->XLen,
								PPage->YLen);
		}
	}
}
void	AutoAlignmentSheet::PutShiftMap(void)
{
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)GetParentInPage();
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PicosCount;i++){
				Picos[i]->PutShiftMap(
								PPage->ResultPerPixXFromTarget,
								PPage->ResultPerPixYFromTarget,
								PPage->ResultPerPixXFromMaster,
								PPage->ResultPerPixYFromMaster,
								PPage->ResultRelativeXFromTarget,
								PPage->ResultRelativeYFromTarget,
								PPage->ResultRelativeXFromMaster,
								PPage->ResultRelativeYFromMaster,
								PPage->XLen,
								PPage->YLen);
			}
		}
	}
	else{
		for(int i=0;i<PicosCount;i++){
			Picos[i]->PutShiftMap(
								PPage->ResultPerPixXFromTarget,
								PPage->ResultPerPixYFromTarget,
								PPage->ResultPerPixXFromMaster,
								PPage->ResultPerPixYFromMaster,
								PPage->ResultRelativeXFromTarget,
								PPage->ResultRelativeYFromTarget,
								PPage->ResultRelativeXFromMaster,
								PPage->ResultRelativeYFromMaster,
								PPage->XLen,
								PPage->YLen);
		}
	}
}

void	AutoAlignmentSheet::AvoidOverlap(void)
{
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{
			#pragma omp for
			for(int i=0;i<PicosCount;i++){
				Picos[i]->AvoidOverlap();
			}
		}
	}
}

#if	defined(NeedFringeBit)
void	AutoAlignmentSheet::SetTransBit(void)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->SetTransBit();
	}
}

void	AutoAlignmentSheet::SetFirstTransBit(void)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->SetFirstTransBit();
	}
}
#endif
void	AutoAlignmentSheet::SetPickupBit(void)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->SetPickupBit();
	}
}

void	AutoAlignmentSheet::SetFirstPickupBit(void)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->SetFirstPickupBit();
	}
}

void	AutoAlignmentSheet::MakePickupAreaFromPico(BYTE **BMap,int XByte ,int YLen)
{
	for(int i=0;i<PicosCount;i++){
		Picos[i]->MakePickupAreaFromPico(BMap,XByte ,YLen);
	}
}


bool	AutoAlignmentSheet::ExistArea(int localX ,int localY)
{
	for(int i=0;i<PicosCount;i++){
		if(Picos[i]->Area.IsInclude(localX ,localY)==true){
			return true;
		}
	}
	return false;
}

FlexArea	&AutoAlignmentSheet::GetArea(int UniqueAreaType_Code)
{
	RetFlexArea.Clear();
	if(Picos!=NULL){
		if(UniqueAreaType_Code==0){
			for(int i=0;i<PicosCount;i++){
				RetFlexArea+=Picos[i]->PickupArea;
			}
		}
		else if(UniqueAreaType_Code==1){
			for(int i=0;i<PicosCount;i++){
				RetFlexArea+=Picos[i]->PickupAreaTarget;
			}
		}
		else if(UniqueAreaType_Code==2){
			for(int i=0;i<PicosCount;i++){
				RetFlexArea+=Picos[i]->Area;
			}
		}
	}
	return RetFlexArea;
}

ClusteredPicoDim::ClusteredPicoDim(AutoAlignmentSheet *parent)
{
	Parent			=parent;
	PicoDim			=NULL;
	PicoDimXNumb	=0;
	PicoDimYNumb	=0;
	XByte			=0;
}

ClusteredPicoDim::~ClusteredPicoDim(void)
{
	if(PicoDim!=NULL){
		for(int y=0;y<PicoDimYNumb;y++){
			delete	[]PicoDim[y];
		}
		delete	[]PicoDim;
	}
	PicoDim			=NULL;
	PicoDimXNumb	=0;
	PicoDimYNumb	=0;
}


void	AutoAlignmentSheet::MakePickupTest(BYTE ***TmpMap,BYTE ***TmpMap2,int &TransW,int &NoiseShrink)
{
	GetLayersBase()->AddMaxProcessing(GetPage(),5);
	GetLayersBase()->StepProcessing(GetPage());

	const	AutoAlignmentThreshold	*RThr=GetThresholdR();
	TransW=RThr->PickupExpansion;

	XByte		=(GetDotPerLine()+7)/8;
	AutoAlignmentInPage	*PPage=(AutoAlignmentInPage *)GetParentInPage();
	AutoAlignmentBase	*PBase=(AutoAlignmentBase *)GetParentBase();

	PPage->CommonMutex.lock();

	*TmpMap	=MakeMatrixBuff(XByte,GetMaxLines());
	*TmpMap2=MakeMatrixBuff(XByte,GetMaxLines());

	PureFlexAreaListContainer MaskFPack ;
	ConstMapBufferListContainer MaskMap;
	if(PPage->GetReflectionMap(_Reflection_Mask,MaskMap)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		//膨張したマスク領域でラベリング処理によって領域化させる
		MatrixBuffCopy(*TmpMap					,XByte,GetMaxLines()
		             //, (const BYTE **)MaskMap	,XByte,GetMaxLines());
					 , (const BYTE **)Map.GetBitMap()	,XByte,GetMaxLines());
	
		GetLayersBase()->FatAreaN(*TmpMap
					,*TmpMap2
					,XByte,GetMaxLines()
					,10);
		
		PickupFlexArea(*TmpMap,XByte ,GetDotPerLine(),GetMaxLines(),MaskFPack);

		MatrixBuffCopy(*TmpMap					,XByte,GetMaxLines()
		             //, (const BYTE **)MaskMap	,XByte,GetMaxLines());
					 , (const BYTE **)Map.GetBitMap()	,XByte,GetMaxLines());
	}
	DeleteMatrixBuff(*TmpMap2,GetMaxLines());

	//手で作製した同じライブラリで他の領域があるとき、その部分を削除する
	if(CreatedManual==false){
		for(AlgorithmItemPI	*p=PPage->GetFirstData();p!=NULL;p=p->GetNext()){
			AutoAlignmentSheet	*aSeet;
			aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
			if(aSeet!=this && aSeet->CreatedManual==true && aSeet->GetLibID()==GetLibID()){
				aSeet->GetArea().MakeNotBitData(*TmpMap,GetDotPerLine(),GetMaxLines());
			}
		}
		GetArea().BuildFromRaster(*TmpMap,XByte,GetMaxLines(),0,0);
	}
	PPage->CommonMutex.unlock();

	//遷移部分で幅±TransWの領域をMasterMapに取得する
	DeleteMatrixBuff(MasterMap,GetMaxLines());
	MasterMap	=MakeMatrixBuff(XByte,GetMaxLines());

	MatrixBuffClear(*TmpMap,0,XByte,GetMaxLines());
	GetArea().MakeBitData(*TmpMap,GetDotPerLine(),GetMaxLines());
	PickupMaster(MasterMap);
/*
//=================================================
	//MasterMapを保存
	QFile	mfile("F:/Data2/MasterMap.dat");
	if(mfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&mfile);
		for(int y=0;y<GetMaxLines();y++){
			for(int x=0;x<XByte;x++){
				mystream << QString::number(MasterMap[y][x]);
				mystream << ",";
			}
			mystream << endl;
		}
		mfile.close();
	}
//=================================================
*/
	MatrixBuffAnd	(MasterMap ,(const BYTE **)(*TmpMap) ,XByte,GetMaxLines());
	MatrixBuffClear(*TmpMap,0,XByte,GetMaxLines());

	*TmpMap2	=MakeMatrixBuff(XByte,GetMaxLines());

	GetLayersBase()->StepProcessing(GetPage());

	NoiseShrink=RThr->NoiseShrink;
	for(AlgorithmItemPI	*p=PPage->GetFirstData();p!=NULL;p=p->GetNext()){
		AutoAlignmentSheet	*aSheet;
		aSheet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSheet!=NULL && aSheet!=this 
		&& aSheet->GetThresholdR(GetLayersBase())->Priority<RThr->Priority 
		&& aSheet->CreatedManual==false){
			aSheet->MakePickupAreaFromPico(*TmpMap,XByte ,GetMaxLines());
			GetLayersBase()->FatAreaN(*TmpMap
							,*TmpMap2
							,XByte,GetMaxLines()
							,NoiseShrink);
			MatrixBuffNotAnd(MasterMap,(const BYTE **)(*TmpMap),XByte,GetMaxLines());
		}
	}

	GetLayersBase()->StepProcessing(GetPage());

	//小さなものを削除する
	if(RThr->MinDot>0){
		PureFlexAreaListContainer FPack;
		PickupFlexArea(MasterMap ,XByte ,GetDotPerLine(),GetMaxLines() ,FPack);
		PureFlexAreaList *f;
		PureFlexAreaListContainer LargeFPack;
		while((f=FPack.GetFirst())!=NULL){
			FPack.RemoveList(f);
			if(f->GetPatternByte()>RThr->MinDot){
				LargeFPack.AppendList(f);
			}
			else{
				delete	f;
			}
		}
		MatrixBuffClear(MasterMap,0,XByte,GetMaxLines());
		for(PureFlexAreaList *a=LargeFPack.GetFirst();a!=NULL;a=a->GetNext()){
			a->MakeBitData(MasterMap,GetDotPerLine(),GetMaxLines());
		}
	}

	GetLayersBase()->StepProcessing(GetPage());

	//PickupBmp
	if(PickupBmp!=NULL){
		DeleteMatrixBuff(PickupBmp,GetMaxLines());
		PickupBmp=NULL;
	}
	PickupBmp=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffCopy(PickupBmp,XByte,GetMaxLines()
                 , (const BYTE **)MasterMap,XByte,GetMaxLines());
	GetLayersBase()->FatAreaN(PickupBmp
			,*TmpMap
			,XByte,GetMaxLines()
			,RThr->ExpandForPickup);
/*
//=================================================
	//PickupBmpを保存
	QFile	wfile("F:/Data2/PickupBmp.dat");
	if(wfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&wfile);
		for(int y=0;y<GetMaxLines();y++){
			for(int x=0;x<XByte;x++){
				mystream << QString::number(PickupBmp[y][x]);
				mystream << ",";
			}
			mystream << endl;
		}
		wfile.close();
	}
//=================================================
*/
	BYTE	**OtherMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffCopy(OtherMap						,XByte,GetMaxLines()
					, (const BYTE **)PickupBmp	,XByte,GetMaxLines());

	int	MaxPicoShift=0;
	for(AlgorithmItemPI	*p=PPage->GetFirstData();p!=NULL;p=p->GetNext()){
		AutoAlignmentSheet	*aSeet;
		aSeet=dynamic_cast<AutoAlignmentSheet *>(p);
		if(aSeet!=NULL && aSeet!=this){
			if(aSeet->GetThresholdR(GetLayersBase())->PicoShift>MaxPicoShift){
				MaxPicoShift=aSeet->GetThresholdR(GetLayersBase())->PicoShift;
			}
		}
	}
	GetLayersBase()->FatAreaN(OtherMap
				 ,*TmpMap
				 ,XByte,GetMaxLines()
				 ,RThr->PicoShift+MaxPicoShift);
	//MatrixBuffNotAnd(OtherMap
	//				,PickupBmp
	//				,XByte,GetMaxLines());


	MatrixBuffCopy(*TmpMap2						,XByte,GetMaxLines()
					, (const BYTE **)MasterMap	,XByte,GetMaxLines());

	int	TransDot=((AutoAlignmentBase *)GetParentBase())->TransDot;
	TransDot/=2;
	if(TransDot==0)
		TransDot=1;

	GetLayersBase()->FatAreaN(MasterMap
				 ,*TmpMap
				 ,XByte,GetMaxLines()
				 ,TransDot);
	GetLayersBase()->ThinAreaN(*TmpMap2
				 ,*TmpMap
				 ,XByte,GetMaxLines()
				 ,TransDot);

	MatrixBuffNotAnd	(MasterMap ,(const BYTE **)(*TmpMap2) ,XByte,GetMaxLines());

	GetLayersBase()->StepProcessing(GetPage());

	MatrixBuffCopy(*TmpMap2						,XByte,GetMaxLines()
					, (const BYTE **)MasterMap	,XByte,GetMaxLines());

	GetLayersBase()->FatAreaN(*TmpMap2
				 ,*TmpMap
				 ,XByte,GetMaxLines()
				 ,RThr->FringeWidth);

	if(Picos!=NULL){
		for(int i=0;i<PicosCount;i++){
			delete	Picos[i];
		}
		delete	[]Picos;
	}

	PicosCount=0;
	CPicoDim.RemoveAll();

	PureFlexAreaListContainer MaskFPackSorted;
	while(MaskFPack.GetFirst()!=NULL){
		PureFlexAreaList *MaxF=NULL;
		int64		MaxDots=0;
		for(PureFlexAreaList *f=MaskFPack.GetFirst();f!=NULL;f=f->GetNext()){
			int64	Dots=f->GetPatternByte();
			if(Dots>MaxDots){
				Dots=MaxDots;
				MaxF=f;
			}
		}
		MaskFPack.RemoveList(MaxF);
		MaskFPackSorted.AppendList(MaxF);
	}

	int	MaxSearchDot=PPage->GetMaxSearchDot()+1;
	for(PureFlexAreaList *f=MaskFPackSorted.GetFirst();f!=NULL;f=f->GetNext()){
		//Maskの領域が他のPICO領域に完全に内包されるとき、そのMask領域からClusteredPicoDimを作成しない
		//大きい領域から順番に生成したClusteredPicoDimで領域を切り取っていき、残った領域が１０ドット
		//	以下であれば生成しない
		FlexArea	TestArea=*f;
		for(ClusteredPicoDim *a=CPicoDim.GetFirst();a!=NULL;a=a->GetNext()){
			for(int iy=0;iy<a->PicoDimYNumb;iy++){
				for(int ix=0;ix<a->PicoDimXNumb;ix++){
					if(a->PicoDim[iy][ix]!=NULL){
						TestArea -= a->PicoDim[iy][ix]->Area;
					}
				}
			}
		}
		if(TestArea.GetPatternByte()<10){
			continue;
		}

		int	x1,y1,x2,y2;
		GetXY(x1,y1,x2,y2);
		int	kx1,ky1,kx2,ky2;
		f->GetXY(kx1,ky1,kx2,ky2);
		int	Mergin=20;
		kx1-=Mergin;
		ky1-=Mergin;
		kx2+=Mergin;
		ky2+=Mergin;
		x1=max(x1,kx1);
		y1=max(y1,ky1);
		x2=min(x2,kx2);
		y2=min(y2,ky2);

		ClusteredPicoDim	*fm=new ClusteredPicoDim(this);
		fm->PicoDimYNumb=(y2-y1+PBase->PicoSize-1)/PBase->PicoSize;
		fm->PicoDimXNumb=(x2-x1+PBase->PicoSize-1)/PBase->PicoSize;
		fm->PicoDim=new AutoAlignmentInPico**[fm->PicoDimYNumb];
		for(int y=0;y<fm->PicoDimYNumb;y++){
			fm->PicoDim[y]=new AutoAlignmentInPico*[fm->PicoDimXNumb];
		}

		GetLayersBase()->StepProcessing(GetPage());

		for(int y=0;y<fm->PicoDimYNumb;y++){
			for(int x=0;x<fm->PicoDimXNumb;x++){
				fm->PicoDim[y][x]=new AutoAlignmentInPico(this,x,y);
				fm->PicoDim[y][x]->DimPoint=fm;

				int	mx1=x*PBase->PicoSize+x1-MaxSearchDot;
				int	my1=y*PBase->PicoSize+y1-MaxSearchDot;
				int	mx2=(x+1)*PBase->PicoSize+x1+MaxSearchDot;
				int	my2=(y+1)*PBase->PicoSize+y1+MaxSearchDot;
				if(mx1<0){
					mx1=0;
				}
				if(my1<0){
					my1=0;
				}
				if(mx2>=GetDotPerLine()){
					mx2=GetDotPerLine()-1;
				}
				if(my2>=GetMaxLines()){
					my2=GetMaxLines()-1;
				}
				if(mx2>=x2){
					mx1 -= mx2-x2;
					mx2=x2;
				}
				if(my2>=y2){
					my1 -= my2-y2;
					my2=y2;
				}

				fm->PicoDim[y][x]->Area.SetRectangle(mx1,my1,mx2,my2);
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				fm->PicoDim[y][x]->ExecuteInitialAfterEdit(MasterMap,XByte,GetMaxLines(),EInfo);
				fm->PicoDim[y][x]->PickupArea.BuildFromRaster(PickupBmp,XByte,GetMaxLines()
														,0 ,0
														,mx1,my1,mx2,my2
														,GetDotPerLine(),GetMaxLines());

				fm->PicoDim[y][x]->PickupAreaTarget=fm->PicoDim[y][x]->PickupArea;
				fm->PicoDim[y][x]->OtherArea.BuildFromRaster(OtherMap,XByte,GetMaxLines()
														,0 ,0
													,mx1,my1,mx2,my2
													,GetDotPerLine(),GetMaxLines());
				fm->PicoDim[y][x]->FringeArea.BuildFromRaster(*TmpMap2,XByte,GetMaxLines()
														,0 ,0
														,mx1,my1,mx2,my2
														,GetDotPerLine(),GetMaxLines());
				fm->PicoDim[y][x]->MakeXYIndex();
				PicosCount++;
			}
		}
		CPicoDim.AppendList(fm);
	}
	DeleteMatrixBuff(OtherMap,GetMaxLines());

	Picos=new AutoAlignmentInPico*[PicosCount];
	int	k=0;
	for(ClusteredPicoDim *fm=CPicoDim.GetFirst();fm!=NULL;fm=fm->GetNext()){
		for(int y=0;y<fm->PicoDimYNumb;y++){
			for(int x=0;x<fm->PicoDimXNumb;x++){
				Picos[k]=fm->PicoDim[y][x];
				k++;
			}
		}
	}
	PicosCount=k;
}
