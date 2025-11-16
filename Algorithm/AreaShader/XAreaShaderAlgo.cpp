/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaShader\XAreaShaderAlgo.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaShader.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaShaderPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "XDisplayBitImage.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


ExeResult	AreaShaderItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	int	gap=((AreaShaderBase *)GetParentBase())->OmitZoneDot;
	GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	LCellSize=GetThresholdR()->CellSize;
	LCalcSize=LCellSize*2;

	WCount=(W+LCellSize-1)/LCellSize;
	HCount=(H+LCellSize-1)/LCellSize;

	if(SDim!=NULL){
		delete	[]SDim;
	}
	SDim=new struct	ShaderStruct[WCount*HCount];

	double	AdoptRate=GetThresholdR()->AdoptRate;
	GetArea().CalcAvrVar(0,0,GetMasterBuff(),Avr,Var
						,AdoptRate/100.0,AdoptRate/100.0
						,0,0,GetArea().GetMaxX(),GetArea().GetMaxY());
	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	return _ER_true;
}

bool	AreaShaderItem::PPProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx=0;
	int	my=0;
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

	AreaShaderInLayer	*P=(AreaShaderInLayer *)GetParentInLayer();

	double	AdoptRate=GetThresholdR()->AdoptRate;
	double	RPj=sqrt(Var);

	if(GetThresholdR()->Fixed==true){
		Avr=GetThresholdR()->Average;
		RPj=GetThresholdR()->Sigma;
	}

	FlexArea	&A=GetArea();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int h=0;h<HCount;h++){	
			for(int w=0;w<WCount;w++){
				int	rx1=w*LCellSize+A.GetMinX();
				int	ry1=h*LCellSize+A.GetMinY();
				int	rx2=rx1+LCellSize;
				int	ry2=ry1+LCellSize;
				if(rx2>GetDotPerLine())
					rx2=GetDotPerLine();
				if(ry2>GetMaxLines())
					ry2=GetMaxLines();

				int	kx1=rx1-(LCalcSize-LCellSize)/2;
				int	ky1=ry1-(LCalcSize-LCellSize)/2;
				int	kx2=rx2+(LCalcSize-LCellSize)/2;
				int	ky2=ry2+(LCalcSize-LCellSize)/2;

				if(kx1<0){
					kx2-=kx1;
					kx1=0;
				}
				if(ky1<0){
					ky2-=ky1;
					ky1=0;
				}
				if(kx2>=GetDotPerLine()){
					kx1-=kx2-GetDotPerLine();
					kx2=GetDotPerLine();
				}
				if(ky2>=GetMaxLines()){
					ky1-=ky2-GetMaxLines();
					ky2=GetMaxLines();
				}

				int	Index=h*WCount+w;
				struct	ShaderStruct	*R=&SDim[Index];
				R->Ax1=rx1;
				R->Ay1=ry1;
				R->Ax2=rx2;
				R->Ay2=ry2;
				R->Avr=-1.0;
				if(P->DynamicMaskMap==NULL){
					A.CalcAvrVar(mx,my,GetTargetBuff(),R->Avr,R->Var
								,AdoptRate/100.0,AdoptRate/100.0
								,kx1+mx,ky1+my,kx2+mx,ky2+my);
				}
				else{
					CalcAvrVar(A,GetTargetBuff(),R->Avr,R->Var
							,AdoptRate/100.0
							,kx1+mx,ky1+my,kx2+mx,ky2+my
							 ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
				}
			}
		}
	}

	#pragma omp parallel                  
	{                                                
		#pragma omp for
		for(int h=0;h<HCount;h++){	
			for(int w=0;w<WCount;w++){
				int	Index=h*WCount+w;
				struct	ShaderStruct	*R=&SDim[Index];
				if(R->Avr<0)
					continue;
				int	rx1=R->Ax1+mx;
				int	ry1=R->Ay1+my;
				int	rx2=R->Ax2+mx;
				int	ry2=R->Ay2+my;
				double	MPj=sqrt(R->Var);
				double	MulVar;
				if(MPj>0)
					MulVar=RPj/MPj;
				else
					MulVar=1.0;
				int	n=A.GetFLineLen();

				for(int i=0;i<n;i++){
					int	Y=A.GetFLineAbsY(i)+my;
					if(ry1<=Y && Y<ry2){
						BYTE	*p=GetTargetBuff().GetY(Y);
						int	X1=A.GetFLineLeftX(i)+mx;
						int	X2=A.GetFLineRightX(i)+mx;
						int	hx1=max(X1,rx1);
						int	hx2=min(X2,rx2);
						for(int x=hx1;x<hx2;x++){
							int	d=((p[x])-R->Avr)*MulVar+Avr;
							if(d<0)
								p[x]=0;
							else if(d<256)
								p[x]=d;
							else{
								p[x]=255;
							}
						}
					}
					else if(ry2<=Y){
						break;
					}
				}
			}
		}
	}
	return true;
}

void	AreaShaderItem::CalcAvrVar(FlexArea &Area,ImageBuffer &buff,double &Avr ,double &Var
							 ,double AdoptRate
							 ,int AreaX1,int AreaY1 ,int AreaX2 ,int AreaY2
							 ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int	CTable[256];

	int	YSep=1;
	int	XSep=1;
	if(Area.GetHeight()>200){
		YSep=5;
	}
	else if(Area.GetHeight()>100){
		YSep=3;
	}
	else if(Area.GetHeight()>50){
		YSep=2;
	}
	if(Area.GetWidth()>200){
		XSep=5;
	}
	else if(Area.GetWidth()>100){
		XSep=3;
	}
	else if(Area.GetWidth()>50){
		XSep=2;
	}

	memset(CTable,0,sizeof(CTable));
	int	DotCount=0;
    for(int i=0;i<Area.GetFLineLen();i++){
        int y =Area.GetFLineAbsY(i);
		if(y<AreaY1 || AreaY2<=y){
			continue;
		}
		if((y%YSep)!=0){
			continue;
		}
		int	x1=max(Area.GetFLineLeftX(i) ,AreaX1);
		int	x2=min(Area.GetFLineRightX(i),AreaX2);
		int	Numb=x2-x1;
		if(Numb<=0){
			continue;
		}
        BYTE	*p=buff.GetY(y)+x1;
		BYTE	*mask=DynamicMaskMap[y];

        for(int x=0;x<Numb;x+=XSep ,p+=XSep){
			int	X=x1+x;
			if((mask[X>>3] & (0x80>>(X&7)))==0){
	            CTable[*p]++;
				DotCount++;
			}
        }
    }
	int	AbandanDot=(1.0-AdoptRate)*DotCount/2;
	int	L1;
	int	L2;
	int	D=0;
	for(L1=0;L1<256;L1++){
		if(D+CTable[L1]>=AbandanDot){
			break;
		}
		D+=CTable[L1];
	}
	D=0;
	for(L2=255;L2>=0;L2--){
		if(D+CTable[L2]>=AbandanDot){
			break;
		}
		D+=CTable[L2];
	}
	DotCount=0;
	double	A=0;
	double	A2=0;
	for(int i=L1;i<=L2;i++){
		DotCount+=CTable[i];
		A+=((double)i)*((double)CTable[i]);
		A2+=((double)i*i)*((double)CTable[i]);
	}
	if(DotCount==0){
		return;
	}
	Avr=A/DotCount;
	Var=(A2 - DotCount*Avr*Avr)/DotCount;
}

