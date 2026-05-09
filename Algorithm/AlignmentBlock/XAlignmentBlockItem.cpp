/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "XAlignmentBlock.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XAlignmentBlockLibrary.h"
#include "XFlexArea.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=====================================================================================

AlignmentBlockThreshold::AlignmentBlockThreshold(AlignmentBlockItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDot	=200;
	MaxDegree	=10;
	LineLength	=20;
	MinVar		=5;
	ThreDiv		=20;
	DustSize	=10;
}

void	AlignmentBlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const AlignmentBlockThreshold *s=(const AlignmentBlockThreshold *)&src;
	SearchDot		=s->SearchDot;
	MaxDegree	=s->MaxDegree	;
	LineLength	=s->LineLength	;
	MinVar		=s->MinVar		;
	ThreDiv		=s->ThreDiv		;
	DustSize	=s->DustSize	;
}
bool	AlignmentBlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const AlignmentBlockThreshold *s=(const AlignmentBlockThreshold *)&src;
	if(SearchDot		==s->SearchDot)
		return true;
	if(MaxDegree		==s->MaxDegree)
		return true;
	if(LineLength		==s->LineLength)
		return true;
	if(MinVar			==s->MinVar)
		return true;
	if(ThreDiv			==s->ThreDiv)
		return true;
	if(DustSize			==s->DustSize)
		return true;
	return false;
}
bool	AlignmentBlockThreshold::Save(QIODevice *f)
{
	WORD	Ver=AlignmentBlockVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,MaxDegree)==false)
		return false;
	if(::Save(f,LineLength)==false)
		return false;
	if(::Save(f,MinVar)==false)
		return false;
	if(::Save(f,ThreDiv)==false)
		return false;
	if(::Save(f,DustSize)==false)
		return false;
	return true;
}

bool	AlignmentBlockThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,MaxDegree)==false)
		return false;
	if(::Load(f,LineLength)==false)
		return false;
	if(::Load(f,MinVar)==false)
		return false;
	if(Ver>=4){
		if(::Load(f,ThreDiv)==false)
			return false;
	}
	if(Ver>=7){
	if(::Load(f,DustSize)==false)
		return false;
	}
	return true;
}

void	AlignmentBlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	AlignmentBlockLibrary	*s=dynamic_cast<AlignmentBlockLibrary *>(src);
	if(s!=NULL){
		SearchDot	=s->SearchDot;
		MaxDegree	=s->MaxDegree;
		LineLength	=s->LineLength;
		MinVar		=s->MinVar	;
		ThreDiv		=s->ThreDiv	;
		DustSize	=s->DustSize;
	}
}
void	AlignmentBlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	AlignmentBlockLibrary	*d=dynamic_cast<AlignmentBlockLibrary *>(Dest);
	if(d!=NULL){
		d->SearchDot	=SearchDot;
		d->MaxDegree	=MaxDegree;
		d->LineLength	=LineLength;
		d->MinVar		=MinVar	;
		d->ThreDiv		=ThreDiv;
		d->DustSize		=DustSize;
	}
}

//===========================================================================================

AlignmentBlockItem::AlignmentBlockItem(void)
{
	CurrentRotationPatternNo=0;
	EffectiveResult=false;

	Result	=0;
	ResultRadian	=0;
	ResultDx		=0;
	ResultDy		=0;
	EffectiveResult	=false;
	MaxNeighborMatching	=0;
	LaplacianValue	=0;
}

AlignmentBlockItem::~AlignmentBlockItem(void)
{
}

AlignmentBlockItem &AlignmentBlockItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((AlignmentBlockItem *)&src));
	EffectiveResult	=((AlignmentBlockItem *)&src)->EffectiveResult;
	return *this;
}

void	AlignmentBlockItem::CopyThreshold(AlignmentBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((AlignmentBlockThreshold *)src.GetThresholdR()));
}

void	AlignmentBlockItem::CopyThresholdOnly(AlignmentBlockItem &src)
{
	GetThresholdW()->CopyFrom(*((AlignmentBlockThreshold *)src.GetThresholdR()));
}

bool    AlignmentBlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	return true;
}
bool    AlignmentBlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	return true;
}

void	AlignmentBlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((AlignmentBlockItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((AlignmentBlockItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((AlignmentBlockItem *)Data));
		}
	}
}

void	AlignmentBlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
}
void	AlignmentBlockItem::CopyArea(AlignmentBlockItem &src)
{
	SetArea(src.GetArea());
}

void	AlignmentBlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlignmentBlockDrawAttr	*BAttr=dynamic_cast<AlignmentBlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		AlgorithmItemPI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		if(BAttr->ShowLines==true){
			double	MinRadian=99999999;
			RotatedMatchingPattern *MinR=NULL;
			for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->NPList<RotatedMatchingPattern>::GetNext()){
				double	L=fabs(r->Radian-BAttr->Radian);
				if(L<MinRadian){
					MinRadian	=L;
					MinR		=r;
				}
			}
			if(MinR!=NULL){
				QColor	LineCol(255,255,0,128);
				MinR->DrawLine(pnt,LineCol,movx ,movy ,ZoomRate);
			}
		}
		QPainter	Pnt(&pnt);
		int	cx,cy;
		GetCenter(cx,cy);

		//DrawInside(Pnt,(cx+movx)*ZoomRate,(cy+movy)*ZoomRate,QFont::ExtraBold,Qt::green);
		DrawInside(Pnt,(cx+movx)*ZoomRate,(cy+movy)*ZoomRate,QFont::Normal,Qt::black);
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

void	AlignmentBlockItem::DrawInside(QPainter &Pnt,int cx ,int cy ,int FontSize ,const QColor &Col)
{
	QFont font = Pnt.font();
	font.setPointSizeF(12.0);           // 文字の大きさ（見やすくするため）
	font.setWeight((QFont::Weight)FontSize);        // 文字の太さ（QFont::Black なども指定可）
    
	Pnt.setFont(font);              // QPainterにフォントを適用
	Pnt.setPen(Col);

	QString	s0 = QString("ItemID=")+QString::number(GetID());
	QString	s1 = QString("RotNo=")+QString::number(CurrentRotationPatternNo);
	QString	s2 = QString("Radian=")+QString::number(ResultRadian,'f',3);
	QString	s3 = QString("(Dx,Dy)=")+QString::number(ResultDx)+QString(",")+QString::number(ResultDy);
	QString	s4 = QString("Result=")+QString::number(Result,'f',3);
	QString	s5 = QString("Neighbor=")+QString::number(MaxNeighborMatching,'f',3);
	QString	s6 = QString("Laplacian=")+QString::number(LaplacianValue);

	Pnt.drawText(cx,cy-60,s0);
	Pnt.drawText(cx,cy-40,s1);
	Pnt.drawText(cx,cy-20,s2);
	Pnt.drawText(cx,cy+0 ,s3);
	Pnt.drawText(cx,cy+20,s4);
	Pnt.drawText(cx,cy+40,s5);
	Pnt.drawText(cx,cy+60,s6);
}

void	AlignmentBlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		QColor	cm=Qt::green;
		cm.setAlpha(100);
		GetArea().Draw(0,0,&IData ,cm.rgba()
						,ZoomRate ,MovX ,MovY);

		QColor	ct=Qt::red;
		ct.setAlpha(100);
		GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,ct.rgba()
						,ZoomRate ,MovX ,MovY);

		int	GWidth	=IData.width();
		int	GHeight=IData.height();

		PData.setBrush(Qt::yellow);
		PData.setPen(Qt::yellow);
	}
}

void	AlignmentBlockItem::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdAlignmentBlockResultInItem	*CmdAlignmentBlockResultInItemVar=dynamic_cast<CmdAlignmentBlockResultInItem *>(packet);
	//if(CmdAlignmentBlockResultInItemVar!=NULL){
	//	if(0<=CmdAlignmentBlockResultInItemVar->ResultIndex
	//	&& CmdAlignmentBlockResultInItemVar->ResultIndex<Results.ResultCount){
	//		RotatedMatchingPattern	*R=GetRotPattern(Results.ResultList[CmdAlignmentBlockResultInItemVar->ResultIndex].RotatedIndex
	//												,Results.ResultList[CmdAlignmentBlockResultInItemVar->ResultIndex].ZoomSizeIndex);
	//		if(R!=NULL){
	//			CmdAlignmentBlockResultInItemVar->Radian=R->Radian;
	//		}
	//	}
	//	return;
	//}
}

void	AlignmentBlockItem::MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)
{
	AlgorithmItemPITemplate<AlignmentBlockInPage,AlignmentBlockBase>::MakeIndependentItems(AInd,LocalX ,LocalY);

	//QBuffer	Buff;
	//Buff.open(QIODevice::ReadWrite);
	//MasterPositions.Save(&Buff);
	//AInd->Something=Buff.buffer();
}

static	int	DbgPage=1;
static	int	DbgID	=2;
static	int	DbgCounter=0;


ExeResult	AlignmentBlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	if(GetPage()==DbgPage && GetID()==DbgID){
		DbgCounter++;
	}
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	ExecuteInitialAfterEditInner();

	return Ret;
}

void	AlignmentBlockItem::ExecuteInitialAfterEditInner(void)
{
	AlignmentBlockBase	*BBase=tGetParentBase();
	double	RLen=hypot(GetArea().GetWidth(),GetArea().GetHeight())/2.0;
	double	DivDegR=3.0*180.0*atan(1.0/RLen)/M_PI;
	int	N=ceil(GetThresholdR()->MaxDegree/DivDegR/2.0);

	for(int k=-N;k<=N;k++){
		RotatedMatchingPattern	*r=new RotatedMatchingPattern(this ,k*DivDegR*M_PI/180.0);
		r->Enabled=true;
		RotatedContainer.AppendList(r);
	}
	ConstMapBufferListContainer MaskMap;
	if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		int	CountRotatedContainer=RotatedContainer.GetCount();
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int i=0;i<CountRotatedContainer;i++){
				RotatedMatchingPattern	*v=RotatedContainer[i];
				v->BuildInitial(BBase->ModeCalcIncline
								,Map.GetBitMap() ,Map.GetXByte() ,Map.GetXLen(),Map.GetYLen());
				if(v->MLines.GetCount()==0){
					v->Enabled=false;
				}
			}
		}
	}
	for(RotatedMatchingPattern	*v=RotatedContainer.GetFirst();v!=NULL;){
		RotatedMatchingPattern	*vNext=v->GetNext();
		if(v->Enabled==false){
			RotatedContainer.RemoveList(v);
			delete v;
		}
		v=vNext;
	}
	AlgorithmLibraryLevelContainer	*Lib=GetLibrary();
	AlignmentBlockLibrary	*ALib=dynamic_cast<AlignmentBlockLibrary *>(Lib->GetLibrary());
	ImagePointerContainer	MasterImages;
	GetMasterBuffList		(MasterImages);
	GetFlatness(MasterImages,ALib->LaplaceFilterSize);
	MatchNeighbor(MasterImages,ALib->NeighborArea);
}


ExeResult	AlignmentBlockItem::ExecuteAlignment(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	EffectiveResult=false;
	if(GetPage()==DbgPage && GetID()==DbgID){
		DbgCounter++;
	}

	AlignmentBlockBase	*BBase=tGetParentBase();
	ImagePointerContainer TargetImages;
	GetTargetBuffList(TargetImages);

	int	SearchDot=GetThresholdR()->SearchDot;
	int	CountRotatedContainer=RotatedContainer.GetCount();
	if(GetParamGlobal()->CalcSingleThread==false){
		#pragma omp parallel
		{                                                
			#pragma omp for
			for(int i=0;i<CountRotatedContainer;i++){
				RotatedMatchingPattern	*v=RotatedContainer[i];
				v->MatchByLine(BBase->ModeCalcIncline,TargetImages,SearchDot);
			}
		}
	}
	else{
		for(int i=0;i<CountRotatedContainer;i++){
			RotatedMatchingPattern	*v=RotatedContainer[i];
			v->MatchByLine(BBase->ModeCalcIncline,TargetImages,SearchDot);
		}
	}

	int	iN=0;
	double	MaxResult=0;
	RotatedMatchingPattern *MaxR=NULL;
	for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->NPList<RotatedMatchingPattern>::GetNext(),iN++){
		if(MaxResult<r->Result){
			MaxResult=r->Result;
			MaxR=r;
			CurrentRotationPatternNo	=iN;
		}
	}
	Result	=MaxResult;
	if(MaxR!=NULL){	
		Result		=MaxResult;
		ResultRadian=MaxR->Radian;
		ResultDx	=MaxR->ResultDx;
		ResultDy	=MaxR->ResultDy;
		EffectiveResult=true;
		SetCalcDone(true);
	}
	Res->SetAlignedXY(ResultDx,ResultDy);
	return _ER_true;
}

void	AlignmentBlockItem::CalcByNeighbor(void)
{
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	AlignmentBlockItem *Neighbor=NULL;
	double	MaxLen=99999999;
	for(AlignmentBlockItem *item=tGetParentInPage()->tGetFirstData();item!=NULL;item=item->tGetNext()){
		if(item->IsCalcDone()==true){
			int	icx,icy;
			item->GetCenter(icx,icy);
			double	Len=hypot(Cx-icx,Cy-icy);
			if(Len<MaxLen){
				MaxLen=Len;
				Neighbor=item;
			}
		}
	}
	if(Neighbor!=NULL){
		ResultRadian=Neighbor->ResultRadian;
		ResultDx	=Neighbor->ResultDx;
		ResultDy	=Neighbor->ResultDy;
	}
	else{
		ResultRadian=0;
		ResultDx	=0;
		ResultDy	=0;
	}
}
RotatedMatchingPattern	*AlignmentBlockItem::GetRotatedPattern(int n)
{
	return RotatedContainer[n];
}

double	AlignmentBlockItem::MatchNeighbor(ImagePointerContainer &Images,int32 NeighborArea)
{
	AlignmentBlockBase	*BBase=tGetParentBase();
	int	CountRotatedContainer=RotatedContainer.GetCount();
	for(int i=0;i<CountRotatedContainer;i++){
		RotatedMatchingPattern	*v=RotatedContainer[i];
		v->MatchByLine(BBase->ModeCalcIncline,Images,NeighborArea,10);	//max(10,NeighborArea/2));
	}
	int	iN=0;
	MaxNeighborMatching=0;
	RotatedMatchingPattern *MaxR=NULL;
	for(RotatedMatchingPattern *r=RotatedContainer.GetFirst();r!=NULL;r=r->NPList<RotatedMatchingPattern>::GetNext(),iN++){
		if(MaxNeighborMatching<r->Result){
			MaxNeighborMatching=r->Result;
			MaxR=r;
		}
	}
	return MaxNeighborMatching;
}

double	AlignmentBlockItem::GetFlatness(ImagePointerContainer &Images,int32 LaplaceFilterSize)
{
	double	MaxVar=0;
	for(ImagePointerList *s=Images.GetFirst();s!=NULL;s=s->GetNext()){
		double	Var=GetFlatness(*s->GetImage(),LaplaceFilterSize);
		MaxVar=max(MaxVar,Var);
	}
	LaplacianValue = MaxVar;
	return MaxVar;
}
//	int	CountRotatedContainer=RotatedContainer.GetCount();
//	double	MinVar = 99999999;
//	for(int i=0;i<CountRotatedContainer;i++){
//		RotatedMatchingPattern	*v=RotatedContainer[i];
//		double	MaxValue=0;
//		for(ImagePointerList *s=Images.GetFirst();s!=NULL;s=s->GetNext()){
//			ImageBuffer	*Image=s->GetImage();
//			double	D=v->GetFlatness(*Image,LaplaceFilterSize);
//			if(D>MaxValue){
//				MaxValue=D;
//			}
//		}
//		if(MinVar>MaxValue){
//			MinVar=MaxValue;
//		}
//	}
//	LaplacianValue = MinVar;
//	return MinVar;
//}


double	AlignmentBlockItem::GetFlatness(ImageBuffer &Images,int32 LaplaceFilterSize)
{
	int	W = GetArea().GetWidth();
	int	H = GetArea().GetHeight();

	int	DivNumb=4;

	int	Wn=W/DivNumb;
	int	Hn=H/DivNumb;
	double	MaxDVar=0;
	for(int w=0;w<DivNumb;w++){
		for(int h=0;h<DivNumb;h++){
			FlexArea	A=GetArea();
			A.ClipArea(A.GetMinX()+w*Wn,A.GetMinY()+h*Hn
					  ,A.GetMinX()+(w+1)*Wn,A.GetMinY()+(h+1)*Hn);
			double	DAvr;
			double	DVar=A.GetVar(0,0,Images ,DAvr);
			if(MaxDVar<DVar){
				MaxDVar=DVar;
			}
		}
	}
	return MaxDVar;

	/*
	int		kernelSize=LaplaceFilterSize;
	double	sigma	=2.0;
	int halfSize = kernelSize / 2;
    double	kernel[128][128];
    double sum = 0.0;

    // 1. LoGカーネルの生成
    double sigma2 = sigma * sigma;
    double sigma4 = sigma2 * sigma2;
    // 定数係数（正規化の過程で比率が保たれればよいため、係数部分は省略や調整も可能ですが厳密に計算します）
    double coeff = -1.0 / (M_PI * sigma4);

    for (int y = -halfSize; y <= halfSize; y++) {
        for (int x = -halfSize; x <= halfSize; x++) {
            double r2 = x * x + y * y;
            double value = coeff * (1.0 - (r2 / (2.0 * sigma2))) * std::exp(-r2 / (2.0 * sigma2));
            kernel[y + halfSize][x + halfSize] = value;
            sum += value;
        }
    }

    // カーネルの総和を厳密に0にするための補正（明るさの変動を防ぐ）
    double mean = sum / (kernelSize * kernelSize);
    for (int y = 0; y < kernelSize; y++) {
        for (int x = 0; x < kernelSize; x++) {
            kernel[y][x] -= mean;
        }
    }


	int	w = Images.GetWidth();
	int	h = Images.GetHeight();
	double	SumAbsVal=0;
	int		ValCount = 0;

	int	N = GetArea().GetFLineLen();

	for(int i=0;i<N;i++){
		int	Y	=GetArea().GetFLineAbsY(i);
		int	X1	=GetArea().GetFLineLeftX(i);
		int	Numb=GetArea().GetFLineNumb(i);
		for(int k=0;k<Numb;k++){
			int	X=X1+k;

			int sum = 0;
            double pixelSum=0;
			double absSum;
            // カーネル内の畳み込み演算
            for (int ky = -halfSize; ky <= halfSize; ky++) {
				if(Y+ky<0 || h<=Y+ky){
					goto NextPixel;
				}
				BYTE	*d = Images.GetYWithoutDepended(Y+ky);
                for (int kx = -halfSize; kx <= halfSize; kx++) {
					if(X+kx<0 || w<=X+kx){
						goto NextPixel;
					}

                    pixelSum += d[X+kx] * kernel[ky + halfSize][kx + halfSize];
                }
            }
            
            // 「大きさ」を求めるため絶対値を取る
            //absSum = std::abs(pixelSum);
			absSum = pixelSum*pixelSum;
			SumAbsVal += absSum;
			ValCount++;

			NextPixel:;
		}
	}
	if(ValCount>=10){
		double	AvgAbsVal=SumAbsVal/ValCount;
		LaplacianValue = AvgAbsVal;
		return AvgAbsVal;
	}
	else{
		LaplacianValue = 0;
		return 0;
	}
	*/
}	