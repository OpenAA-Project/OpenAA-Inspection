#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"
#include "XInterpolation.h"
#include "XCrossObj.h"

const	int		MaxLinePoint=5000;

int	DotColorMatchingItem::ExecuteProcessingPickLine(ResultInItemRoot *Res
													,BYTE **Map,int MapXByte,int MapXLen,int MapYLen
													,int MapXPoint,int MapYPoint
													,int mx,int my)
{
	DotColorMatchingBase	*ABase=((DotColorMatchingBase *)GetParentBase());

	const	DotColorMatchingThreshold	*Th=GetThresholdR();
	int	DotPerLine	=GetDotPerLine();
	int	MaxLines	=GetMaxLines();
	int	LayerNumb=GetLayerNumb();

	PureFlexAreaListContainer FPack;
	PickupFlexArea(Map ,MapXByte ,MapXLen,MapYLen ,FPack);
	for(PureFlexAreaList *s=FPack.GetFirst();s!=NULL;){
		PureFlexAreaList *NextS=s->GetNext();
		if(s->GetPatternByte()<Th->LineMinCluster){
			s->MakeNotBitData(Map ,MapXLen,MapYLen);
			FPack.RemoveList(s);
			delete	s;
		}
		s=NextS;
	}

	double	X[MaxLinePoint];
	double	Y[MaxLinePoint];
	double	A,B,C;
	int		N=0;
	for(int y=0;y<MapYLen;y++){
		BYTE	*s=Map[y];
		for(int x=0;x<MapXLen;x++){
			if(GetBmpBitOnY(s,x)!=0){
				if(N<MaxLinePoint){
					X[N]=x;
					Y[N]=y;
					N++;
				}
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
				MatrixBuffClear	(Map ,0,MapXByte ,MapYLen);
				for(int i=0;i<Nn;i++){
					SetBmpBit1(Map,(int)Xn[i],(int)Yn[i]);
				}


				PureFlexAreaListContainer LFPack;
				PickupFlexArea(Map,MapXByte,MapXLen,MapYLen,LFPack);

				FlexArea	F;
				for(PureFlexAreaList *p=LFPack.GetFirst();p!=NULL;p=p->GetNext()){
					F+=*p;
				}
				F.MoveToNoClip(MapXPoint,MapYPoint);

				int	Cx,Cy;
				F.GetCenter(Cx,Cy);
				DotColorMatchingResultPosList	*r=new DotColorMatchingResultPosList(Cx,Cy ,0,0);
				r->result =0x10850 ;	//NG
				r->SetResult1(Nn );
				r->SetResult2(Len);
				r->NGShape.SuckFrom(F);
				r->NGSize=Nn;
				r->NGLine=true;
				r->X1=Vx*MinT+X0+MapXPoint;
				r->Y1=Vy*MinT+Y0+MapYPoint;
				r->X2=Vx*MaxT+X0+MapXPoint;
				r->Y2=Vy*MaxT+Y0+MapYPoint;
				ResultPosListContainer	NowList;
				NowList.AppendList(r);

				Res->MovePosList(NowList);
				Res->SetAlignedXY(mx,my);
				ResultDx=mx;
				ResultDy=my;
				ResultCode=2;
				Res->SetResult1(Nn);
				Res->SetResult2(Nn);
				Res->SetResultDouble(Len);
				return 2;				//NG
			}
		}
	}
	return 0;
}