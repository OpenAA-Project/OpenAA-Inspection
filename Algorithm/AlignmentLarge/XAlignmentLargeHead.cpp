#define	_USE_MATH_DEFINES
#include <math.h>
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XAffin.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
	
int	AlignmentLargeInPage::ExecuteHeadAlignmentY(ImagePointerContainer &Images)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	int	LayerNumb=GetLayerNumb();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	int	StepY=ABase->HeadAlignmentStep;
	float	ZStepY=1.0/((float)StepY);
	if(ABase->SkipHeadAlignmentX>=0 && ABase->SkipHeadAlignmentY>=0 && ABase->MaxHeadAlignmentY>=0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int Layer=0;Layer<LayerNumb;Layer++){
				ImageBuffer	*IBuff=Images[Layer];
				short	*pXDim=HeadXDim[Layer];
				XLen=min(GetDotPerLine(),IBuff->GetWidth());
				YLen=min(GetMaxLines()	,IBuff->GetHeight());
				for(int y=0;y<StepY;y++){
					int	Y=ABase->SkipHeadAlignmentY+y;
					if(0<=Y && Y<YLen){
						BYTE	*s=IBuff->GetYWithoutDepended(Y);
						if(y==0){
							for(int x=0;x<XLen;x++){
								pXDim[x]=s[x];
							}
						}
						else{
							for(int x=0;x<XLen;x++){
								pXDim[x]+=s[x];
							}
						}
					}
				}
				for(int x=0;x<XLen;x++){
					pXDim[x]*=ZStepY;
				}
			}
		}

		for(int y=ABase->SkipHeadAlignmentY;y<ABase->MaxHeadAlignmentY && y<YLen;y+=StepY){
			for(int Layer=0;Layer<LayerNumb;Layer++){
				ImageBuffer	*IBuff=Images[Layer];
				BYTE	*s=IBuff->GetYWithoutDepended(y);
				short	*pXDim=HeadXDim[Layer];
				for(int x=ABase->SkipHeadAlignmentX;x<XLen-ABase->SkipHeadAlignmentX;x++){
					int	C=s[x]-pXDim[x];
					int	X1=x;
					if(abs(C)>=ABase->HeadAlignmentDifColor){
						for(;x<XLen-ABase->SkipHeadAlignmentX;x++){
							C=s[x]-pXDim[x];
							if(abs(C)<ABase->HeadAlignmentDifColor){
								break;
							}
						}
						if(x-X1>ABase->HeadAlignmentMinSize){
							return y;
						}
					}
				}
			}
		}
	}
	return 0;
}


int	AlignmentLargeInPage::ExecuteHeadAlignmentX(ImagePointerContainer &Images)
{
	AlignmentLargeBase	*ABase=(AlignmentLargeBase *)GetParentBase();
	int	LayerNumb=GetLayerNumb();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	int	StepX=ABase->HeadAlignmentStep;
	float	ZStepX=1.0/((float)StepX);

	if(ABase->MaxHeadAlignmentX>=0 && ABase->SkipHeadAlignmentX && ABase->SkipHeadAlignmentY>=0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int Layer=0;Layer<LayerNumb;Layer++){
				ImageBuffer	*IBuff=Images[Layer];
				short	*pYDim=HeadYDim[Layer];
				XLen=min(GetDotPerLine(),IBuff->GetWidth());
				YLen=min(GetMaxLines()	,IBuff->GetHeight());
				for(int x=0;x<StepX;x++){
					if(x==0){
						for(int y=0;y<YLen;y++){
							BYTE	*s=IBuff->GetYWithoutDepended(y);
							int	X=ABase->SkipHeadAlignmentX+x;
							if(0<=X && X<XLen){
								pYDim[y]=s[X];
							}
						}
					}
					else{
						for(int y=0;y<YLen;y++){
							BYTE	*s=IBuff->GetYWithoutDepended(y);
							int	X=ABase->SkipHeadAlignmentX+x;
							if(0<=X && X<XLen){
								pYDim[y]+=s[X];
							}
						}
					}
				}
				for(int y=0;y<YLen;y++){
					pYDim[y]*=ZStepX;
				}
			}
		}

		for(int x=ABase->SkipHeadAlignmentX;x<ABase->MaxHeadAlignmentX && x<XLen;x+=StepX){
			for(int Layer=0;Layer<LayerNumb;Layer++){
				ImageBuffer	*IBuff=Images[Layer];
				short	*pYDim=HeadYDim[Layer];
				for(int y=ABase->SkipHeadAlignmentY;y<YLen-ABase->SkipHeadAlignmentY && y<YLen;y++){
					BYTE	*s=IBuff->GetYWithoutDepended(y);

					int	C=s[x]-pYDim[y];
					int	Y1=y;
					if(abs(C)>=ABase->HeadAlignmentDifColor){
						for(;y<YLen-ABase->SkipHeadAlignmentY;y++){
							s=IBuff->GetYWithoutDepended(y);
							C=s[x]-pYDim[y];
							if(abs(C)<ABase->HeadAlignmentDifColor){
								break;
							}
						}
						if(y-Y1>ABase->HeadAlignmentMinSize){
							return x;
						}
					}
				}
			}
		}
	}
	return 0;
}