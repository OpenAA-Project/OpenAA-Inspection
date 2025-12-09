#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "XBitImageProcessor.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XFlatInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XUndo.h"
#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspectionAlgoPacket.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"
#include "XInterpolation.h"


const	int		MaxLinePoint=5000;
void	BindClusterize(PureFlexAreaListContainer &FPackIn ,PureFlexAreaListContainer &Binded ,double Distance);


int	FlatInspectionItem::ExecuteProcessingPickLine(ResultInItemRoot *Res
													,BYTE **Map
													,int OffsetX,int OffsetY)
{
	FlatInspectionBase	*ABase=((FlatInspectionBase *)GetParentBase());

	const	FlatInspectionThreshold	*Th=GetThresholdR();
	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	int	LayerNumb=GetLayerNumb();

	PureFlexAreaListContainer FPackIn;
	PickupFlexArea(Map ,NGMapXByte ,NGMapXLen,NGMapYLen ,FPackIn);
	for(PureFlexAreaList *s=FPackIn.GetFirst();s!=NULL;){
		PureFlexAreaList *NextS=s->GetNext();
		if(s->GetPatternByte()<Th->LineMinCluster){
			//s->MakeNotBitData(Map ,NGMapXByte,NGMapYLen);
			FPackIn.RemoveList(s);
			delete	s;
		}
		s=NextS;
	}

	PureFlexAreaListContainer Binded;
	BindClusterize(FPackIn ,Binded ,Th->LineOKMinLength);

	int		NGDotCount=0;
	int		NGLen=0;
	bool	FoundNG=false;
	for(PureFlexAreaList *f=Binded.GetFirst();f!=NULL;f=f->GetNext()){
		double	X[MaxLinePoint];
		double	Y[MaxLinePoint];
		double	A,B,C;
		int		N=0;
		int		AreaX1=NGMapOffsetX;
		int		AreaY1=NGMapOffsetY;
		int	NLen=f->GetFLineLen();
		for(int i=0;i<NLen;i++){
			int	y=f->GetFLineAbsY(i);
			int	X1=f->GetFLineLeftX(i);
			int	X2=f->GetFLineRightX(i);
			for(int x=X1;x<X2;x++){
				if(N<MaxLinePoint){
					X[N]=x+AreaX1;
					Y[N]=y+AreaY1;
					N++;
				}
			}
		}

		double	Xn[MaxLinePoint];
		double	Yn[MaxLinePoint];
		int		Nn=0;
		double	LineWidth=Th->LineMaxWidth*0.5;
		if(MakeInterpolatedLine(X ,Y ,N ,A,B,C)==true){
			double	m=hypot(A,B);
			if(fabs(m)<0.001)
				return 0;
			m=1.0/m;
			double	X0=0;
			double	Y0=0;
			if(fabs(A)>fabs(B)){
				X0=-C/A;
				Y0=0;
			}
			else{
				Y0=-C/B;
				X0=0;
			}
			double	Vx=B*m;
			double	Vy=-A*m;
			double	MaxT=-99999999;
			double	MinT= 99999999;
			for(int i=0;i<N;i++){
				double	D=(X[i]*A+Y[i]*B+C)*m;
				if(fabs(D)<=LineWidth){
					Xn[Nn]=X[i];
					Yn[Nn]=Y[i];
					double	fX,fY;
					if(GetLinePointFoot(A,B,C
										,X[i] ,Y[i],fX ,fY)==true){
						//Vx*t+X0=fX
						//Vy*y+Y0=fY
						double	t;
						if(fabs(Vx)>fabs(Vy))
							t=(fX-X0)/Vx;
						else
							t=(fY-Y0)/Vy;
						if(MaxT<t){
							MaxT=t;
						}
						if(MinT>t){
							MinT=t;
						}
						Nn++;
					}
				}
			}
			int	iMinT=floor(MinT);
			int	iMaxT=ceil(MaxT);
			int	iLen=iMaxT-iMinT+1;
			bool	FootEnable[MaxLinePoint];
			for(int i=0;i<iLen;i++){
				FootEnable[i]=false;
			}
			for(int i=0;i<Nn;i++){
				double	fX,fY;
				if(GetLinePointFoot(A,B,C
									,Xn[i] ,Yn[i],fX ,fY)==true){
					double	t;
					if(fabs(Vx)>fabs(Vy))
						t=(fX-X0)/Vx;
					else
						t=(fY-Y0)/Vy;

					int	k=(int)(t-MinT);
					FootEnable[k]=true;
					if(0<=k-1){
						FootEnable[k-1]=true;
					}
					if(k+1<iLen){
						FootEnable[k+1]=true;
					}
				}
			}
			int	DotLineCount=0;
			for(int i=0;i<iLen;i++){
				if(FootEnable[i]==true){
					DotLineCount++;
				}
			}

			if(Nn>=4){
				double	Len=MaxT-MinT;
				if(Len>=Th->LineOKMinLength
				&& ((double)DotLineCount)/((double)iLen)>=Th->LineMinDensityPercent/100.0){
					MatrixBuffClear	(Map ,0,NGMapXByte ,NGMapYLen);
					for(int i=0;i<Nn;i++){
						SetBmpBit1(Map,(int)Xn[i]-AreaX1,(int)Yn[i]-AreaY1);
					}


					PureFlexAreaListContainer LFPack;
					PickupFlexArea(Map,NGMapXByte,NGMapXLen,NGMapYLen,LFPack);

					FlexArea	F;
					for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
						F+=*p;
					}
					F.MoveToNoClip(AreaX1,AreaY1);
					F.MoveToNoClip(OffsetX,OffsetY);

					int	Cx,Cy;
					F.GetCenter(Cx,Cy);
					FlatInspectionResultPosList	*r=new FlatInspectionResultPosList(Cx,Cy ,0,0);
					r->result =0x10850 ;	//NG
					r->SetResult1(Nn );
					r->SetResult2(Len);
					r->NGShape.SuckFrom(F);
					r->NGSize=Nn;
					r->NGLine=true;
					r->X1=Vx*MinT+X0+OffsetX;
					r->Y1=Vy*MinT+Y0+OffsetY;
					r->X2=Vx*MaxT+X0+OffsetX;
					r->Y2=Vy*MaxT+Y0+OffsetY;
					ResultPosListContainer	NowList;
					NowList.AppendList(r);

					Res->AddMovePosList(NowList);
					NGDotCount=Nn;
					NGLen=Len;
					FoundNG=true;
				}
			}
		}
	}
	if(FoundNG==true){
		Res->SetAlignedXY(OffsetX,OffsetY);
		Res->SetResult1(NGDotCount);
		Res->SetResult2(NGDotCount);
		Res->SetResultDouble(NGLen);
		Res->SetError(2);
		return 2;				//NG
	}
	return 0;
}