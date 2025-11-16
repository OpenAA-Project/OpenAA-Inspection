#include "DustReducerAI.h"
#include "XResultAnalizerDLL.h"
#include "XLanguageClass.h"
#include "XGeneralFunc.h"
#include "ShowResultDialog.h"
#include "SettingParamDialog.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "swap.h"


double	DustRegList::Calc(BYTE *SrcPattern[3],int SrcLayerNumb ,int SrcXLen ,int SrcYLen,IntList &AdaptedLayer)
{
	double	Result=1.0;
	if(XLen==SrcXLen && YLen==SrcYLen && LayerNumb==SrcLayerNumb){
		int	Len=XLen*YLen;		
		//for(int layer=0;layer<LayerNumb;layer++){
		for(IntClass *c=AdaptedLayer.GetFirst();c!=NULL;c=c->GetNext()){
			int	layer=c->GetValue();
			int		B=0;
			double	BB=0;
			double	AB=0;
			BYTE	*s=Pattern[layer];
			BYTE	*d=SrcPattern[layer];
			for(int i=0;i<Len;i++){
				BYTE	b=*(d++);
				B+=b;
				BB+=b*b;
				AB+=*(s++)*b;
			}
			double	AvrA=A[layer]/Len;
			double	AvrB=((double)B)/Len;

			double	M=(AA[layer]-Len*AvrA*AvrA)*(BB-Len*AvrB*AvrB);
			if(M<=0){
				return 0;
			}
			M=sqrt(M);
			double	K=AB-Len*AvrA*AvrB;
			Result*=K/M;
		}
	}
	else{
		int	NYLen=min(YLen,SrcYLen);
		int	NXLen=min(XLen,SrcXLen);
		int	Len=NXLen*NYLen;
		for(int layer=0;layer<LayerNumb;layer++){
			int		S=0;
			double	SS=0;
			int		B=0;
			double	BB=0;
			double	AB=0;
			for(int y=0;y<NYLen;y++){
				BYTE	*s=&Pattern[layer][y*XLen];
				BYTE	*d=&SrcPattern[layer][y*SrcXLen];
				for(int x=0;x<NXLen;x++){
					BYTE	a=*(s++);
					BYTE	b=*(d++);
					S+=a;
					SS+=a*a;
					B+=b;
					BB+=b*b;
					AB+=a*b;
				}
			}	
			double	AvrA=((double)S)/Len;
			double	AvrB=((double)B)/Len;

			double	M=(SS-Len*AvrA*AvrA)*(BB-Len*AvrB*AvrB);
			if(M<=0){
				return 0;
			}
			M=sqrt(M);
			double	K=AB-Len*AvrA*AvrB;
			Result*=K/M;
		}
	}
	return Result;
}

void	DustReducerAI::MakePattern(int Phase,int Page,int X,int Y)
{
	int	X1=X-XLen/2;
	int	Y1=Y-YLen/2;
	int	Len=XLen*YLen;
	if(0<=X1 && (X1+XLen)<GetDotPerLine(Page) && 0<=Y1 && (Y1+YLen)<GetMaxLines(Page)){
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			ImageBuffer	&TBuff=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer)->GetTargetBuff();
			if(CurrentPattern[Layer]==NULL){
				CurrentPattern[Layer]=new BYTE[Len];
			}
			BYTE	*p=CurrentPattern[Layer];
			for(int y=0;y<YLen;y++){
				BYTE	*s=&TBuff.GetY(Y1+y)[X1];
				for(int x=0;x<XLen;x++){
					*(p++)=*(s++);
				}
			}
		}
	}
	else{
		for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
			ImageBuffer	&TBuff=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer)->GetTargetBuff();
			if(CurrentPattern[Layer]==NULL){
				CurrentPattern[Layer]=new BYTE[Len];
			}
			BYTE	*p=CurrentPattern[Layer];
			for(int y=0;y<YLen;y++){
				int	Ys=Y1+y;
				if(0<=Ys && Ys<GetMaxLines(Page)){
					BYTE	*s=TBuff.GetY(Ys);
					for(int x=0;x<XLen;x++){
						int	Xs=X1+x;
						if(0<=Xs && Xs<GetDotPerLine(Page)){
							*(p++)=s[Xs];
						}
						else{
							*(p++)=0;
						}
					}
				}
				else{
					for(int x=0;x<XLen;x++){
						*(p++)=0;
					}
				}
			}
		}
	}
}
