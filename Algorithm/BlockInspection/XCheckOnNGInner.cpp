#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"
#include <omp.h>
#include "immintrin.h"

static	BYTE	ShuffleRev[16]	={7,255,6,255,5,255,4,255,3,255,2,255,1,255,0,255};
static	BYTE	ShufflePack[16]	={1,3,5,7,9,11,13,15,255,255,255,255,255,255,255,255};

void	BlockItem::CheckOnNGInner1(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,int &LSum,int &HSum
									,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	ImageBuffer &a=GetTargetBuff();
	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
	LSum=0;
	HSum=0;
	const	BlockThreshold	*RThr=GetThresholdR();

	if(RThr->ThreshouldBag.PointMove.ModeBlackMask==false
	&& RThr->ThreshouldBag.PointMove.ModeWhiteMask==false){

#ifdef _MSC_VER
		__asm{
			MOVDQA		 xmm2,ShuffleRev
			MOVDQA		 xmm5,ShufflePack
			VPBROADCASTB xmm3, BYTE ptr LLevel 
			VPBROADCASTB xmm4, BYTE ptr HLevel
			PSHUFB		xmm3,xmm2
			PSHUFB		xmm4,xmm2
		}
#endif

		for(int i=0;i<fa->GetFLineLen();i++){
			int Y =fa->GetFLineAbsY(i);
			if(Y+dy<BLKMergin)
				continue;
			if(Y+dy>=(YLen-BLKMergin))
				break;
			int X   =fa->GetFLineLeftX(i);
			int Numb=fa->GetFLineNumb(i);
			int x1=X;
			int x2=X+Numb;
			X=x1;
			if((X+Numb+dx)<BLKMergin || (X+dx)>=(XLen-BLKMergin))
				continue;
			if((X+dx)<BLKMergin){
				X=BLKMergin-dx;
				x1=max(x1,X);
				x2=min(x2,X+Numb);
				Numb=min(Numb,x2-x1);
			}
			if((X+Numb+dx)>=(XLen-BLKMergin)){
				Numb=(XLen-BLKMergin)-(X+dx);
			}
			if(Numb<=0)
				continue;

			//int px=X-fa->GetMinX();
			int mdy=Y-starty;
			if(mdy<0)
				continue;
			BYTE	*p=a.GetY(dy+Y)+dx+X;
			int		MPoint=Lx*mdy+((X-fa->GetMinX())>>3);

			BYTE	*qL=&(pMapL[MPoint]);
			BYTE	*qH=&(pMapH[MPoint]);
			BYTE	Mask=0x80>>((X-fa->GetMinX())&7);
			if(DynamicMaskMap==NULL || RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					int	LeftN=(8-((X-fa->GetMinX())&7))&0x7;
					LeftN=min(LeftN,Numb);
					if(LeftN>0){
						for(int k=0;k<LeftN;k++,p++){
							if(*p<LLevel){
								*qL|=Mask;
								LSum++;
							}
							if(HLevel<*p){
								*qH|=Mask;
								HSum++;
							}
							Mask>>=1;
						}
						qL++;
						qH++;
					}
					Numb-=LeftN;
					int	N=Numb>>3;	//	Numb/8

#ifdef _MSC_VER
					__asm{
						mov			rsi,p
						mov			r8,qL
						mov			r9,qH
					}
					for(int i=0;i<N;i++){
						__asm{
							MOVQ	xmm1, mmword ptr [rsi]
							PSHUFB	xmm1,xmm2
							VPSUBW 		xmm0,xmm1,xmm3
							PSHUFB		xmm0,xmm5
							PMOVMSKB	eax,xmm0
							POPCNT		ebx,eax
							add			LSum,ebx
							mov			BYTE ptr [r8],AL

							PCMPGTW 	xmm1,xmm4
							PSHUFB		xmm1,xmm5
							PMOVMSKB	eax,xmm1
							POPCNT		ebx,eax
							add			HSum,ebx
							mov			BYTE ptr [r9],AL
							add			rsi,8
							inc			r8
							inc			r9
						}
					}
					__asm{
						mov		p,rsi
						mov		qL,r8
						mov		qH,r9
					}
					int	RightN=Numb-(N<<3);
					if(RightN>0){
						Mask=0x80;
						for(int k=0;k<RightN;k++,p++){
							if(*p<LLevel){
								*qL|=Mask;
								LSum++;
							}
							if(HLevel<*p){
								*qH|=Mask;
								HSum++;
							}
							Mask>>=1;
						}
					}
#else

						for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							if(*p<LLevel){
								*qL|=(BYTE)Mask;
								LSum++;
							}
							if(HLevel<*p){
								*qH|=(BYTE)Mask;
								HSum++;
							}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
								qH++;
							}
						}
					}
#endif
				}
				else{
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							if(LLevel<*p && *p<HLevel){
								*qL|=(BYTE)Mask;
								LSum++;
								*qH|=(BYTE)Mask;
								HSum++;
							}
							Mask>>=1;
							if(Mask==0){
								Mask=0x80;
								qL++;
								qH++;
							}
						}
					}
				}
			}
			else{
				BYTE	*DMapP=DynamicMaskMap[Y+dy];
				int	MapX=X+dx;
				BYTE	DMapMask=(0x80>>(MapX &0x07));
				BYTE	*DMapPointer=&DMapP[MapX>>3];
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					/*
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							if(((*DMapPointer) & DMapMask)==0){
								if(*p<LLevel){
									*qL|=(BYTE)Mask;
									LSum++;
								}
								if(HLevel<*p){
									*qH|=(BYTE)Mask;
									HSum++;
								}
							}
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
								qH++;
							}
						}
					}
					*/
					for(int k=0;k<Numb;){
						int	NN;
						BYTE	FullDMask;
						if(DMapMask==0x80){					
							NN=min(8,Numb-k);
							FullDMask=0xFF;
						}
						else if(DMapMask==0x40){
							NN=min(7,Numb-k);
							FullDMask=0x7F;
						}
						else if(DMapMask==0x20){
							NN=min(6,Numb-k);
							FullDMask=0x3F;
						}
						else if(DMapMask==0x10){
							NN=min(5,Numb-k);
							FullDMask=0x1F;
						}
						else if(DMapMask==0x08){
							NN=min(4,Numb-k);
							FullDMask=0x0F;
						}
						else if(DMapMask==0x04){
							NN=min(3,Numb-k);
							FullDMask=0x07;
						}
						else if(DMapMask==0x02){
							NN=min(2,Numb-k);
							FullDMask=0x03;
						}
						else if(DMapMask==0x01){
							NN=min(1,Numb-k);
							FullDMask=0x01;
						}
						else
							break;
						if(((*DMapPointer) & FullDMask)==0){
							for(int t=0;t<NN;t++,p++){
								if(*p<LLevel){
									*qL|=(BYTE)Mask;
									LSum++;
								}
								if(HLevel<*p){
									*qH|=(BYTE)Mask;
									HSum++;
								}
								Mask>>=1;
								if(Mask==0){
									Mask=0x80;
									qL++;
									qH++;
								}
							}
						}
						else{
							for(int t=0;t<NN;t++,p++){
								if(((*DMapPointer) & DMapMask)==0){
									if(*p<LLevel){
										*qL|=(BYTE)Mask;
										LSum++;
									}
									if(HLevel<*p){
										*qH|=(BYTE)Mask;
										HSum++;
									}
								}
								DMapMask>>=1;
								Mask>>=1;
								if(Mask==0){
									Mask=0x80;
									qL++;
									qH++;
								}
							}
						}

						DMapPointer++;
						DMapMask=0x80;
						k+=NN;
					}
				}
				else{
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qL>=&pMapL[LByte]){
							//	DbgTest++;
							//	break;
							//}
							//if(qL>=pMapL){
								if(((*DMapPointer) & DMapMask)==0){
									if(LLevel<*p && *p<HLevel){
										*qL|=(BYTE)Mask;
										LSum++;
										*qH|=(BYTE)Mask;
										HSum++;
									}
								}
							//}
							//else{
							//	DbgTest++;
							//}
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask>>=1;
							if(Mask==0){
								Mask=0x80;
								qL++;
								qH++;
							}
						}
					}
				}
			}
		}
	}
	else if(RThr->ThreshouldBag.PointMove.ModeBlackMask==true
		 && RThr->ThreshouldBag.PointMove.ModeWhiteMask==false){
		for(int i=0;i<fa->GetFLineLen();i++){
			int Y =fa->GetFLineAbsY(i);
			if(Y+dy<BLKMergin || Y+dy>=(YLen-BLKMergin))
				continue;
			int X   =fa->GetFLineLeftX(i);
			int Numb=fa->GetFLineNumb(i);
			int x1=X;
			int x2=X+Numb;
			X=x1;
			if((X+Numb+dx)<BLKMergin || (X+dx)>=(XLen-BLKMergin))
				continue;
			if((X+dx)<BLKMergin){
				X=BLKMergin-dx;
				x1=max(x1,X);
				x2=min(x2,X+Numb);
				Numb=min(Numb,x2-x1);
			}
			if((X+Numb+dx)>=(XLen-BLKMergin)){
				Numb=(XLen-BLKMergin)-(X+dx);
			}
			if(Numb<=0)
				continue;

			//int px=X-fa->GetMinX();
			int mdy=Y-starty;
			if(mdy<0)
				continue;
			BYTE	*p=a.GetY(dy+Y)+dx+X;
			BYTE	*qH=&(pMapH[Lx*mdy+((X-fa->GetMinX())>>3)]);
			unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));

			if(DynamicMaskMap==NULL || RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qH>=&pMapH[LByte]){
							//	DbgTest++;
							//	break;
							//}
							//if(qH>=pMapH){
								if(HLevel<*p){
									*qH|=(BYTE)Mask;
									HSum++;
								}
							//}
							//else{
							//	DbgTest++;
							//}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qH++;
							}
						}
					}
				}
				else{
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qH>=&pMapH[LByte]){
							//	DbgTest++;
							//	break;
							//}
							//if(qH>=pMapH){
								if(*p<HLevel){
									*qH|=(BYTE)Mask;
									HSum++;
								}
							//}
							//else{
							//	DbgTest++;
							//}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qH++;
							}
						}
					}
				}
			}
			else{
				BYTE	*DMapP=DynamicMaskMap[Y+dy];
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					int	MapX=X+dx;
					BYTE	DMapMask=(0x80>>(MapX &0x07));
					BYTE	*DMapPointer=&DMapP[MapX>>3];
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qH>=&pMapH[LByte]){
							//	DbgTest++;
							//	break;
							//}
							if(((*DMapPointer) & DMapMask)==0){
								//if(qH>=pMapH){
									if(HLevel<*p){
										*qH|=(BYTE)Mask;
										HSum++;
									}
								//}
								//else{
								//	DbgTest++;
								//}
							}
							//MapX++;
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qH++;
							}
						}
					}
				}
				else{
					int	MapX=X+dx;
					BYTE	DMapMask=(0x80>>(MapX &0x07));
					BYTE	*DMapPointer=&DMapP[MapX>>3];
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qH>=&pMapH[LByte]){
							//	DbgTest++;
							//	break;
							//}
							if(((*DMapPointer) & DMapMask)==0){
								//if(qH>=pMapH){
									if(*p<HLevel){
										*qH|=(BYTE)Mask;
										HSum++;
									}
								//}
								//else{
								//	DbgTest++;
								//}
							}
							//MapX++;
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qH++;
							}
						}
					}
				}
			}
		}
	}
	else if(RThr->ThreshouldBag.PointMove.ModeBlackMask==false
		 && RThr->ThreshouldBag.PointMove.ModeWhiteMask==true){
		for(int i=0;i<fa->GetFLineLen();i++){
			int Y =fa->GetFLineAbsY(i);
			if(Y+dy<BLKMergin || Y+dy>=(YLen-BLKMergin))
				continue;
			int X   =fa->GetFLineLeftX(i);
			int Numb=fa->GetFLineNumb(i);
			int x1=X;
			int x2=X+Numb;
			/*
			if(x2<BLKMergin || x1>=(XLen-BLKMergin-1) || x1>x2)
				continue;
			if(x1<0)
				x1=0;
			if(x2>=XLen-BLKMergin-1)
				x2=XLen-BLKMergin-1;
			Numb=x2-x1;
			*/
			X=x1;
			if((X+Numb+dx)<BLKMergin || (X+dx)>=(XLen-BLKMergin))
				continue;
			if((X+dx)<BLKMergin){
				X=BLKMergin-dx;
				x1=max(x1,X);
				x2=min(x2,X+Numb);
				Numb=min(Numb,x2-x1);
			}
			if((X+Numb+dx)>=(XLen-BLKMergin)){
				Numb=(XLen-BLKMergin)-(X+dx);
			}
			if(Numb<=0)
				continue;

			//int px=X-fa->GetMinX();
			int mdy=Y-starty;
			if(mdy<0)
				continue;
			BYTE	*p=a.GetY(dy+Y)+dx+X;
			BYTE	*qL=&(pMapL[Lx*mdy+((X-fa->GetMinX())>>3)]);
			unsigned int	Mask=(0x8080808080808080u>>((X-fa->GetMinX())&7));

			if(DynamicMaskMap==NULL || RThr->ThreshouldBag.PointMove.ModeDynamicMask==false){
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qL>=&pMapL[LByte]){
							//	DbgTest++;
							//	break;
							//}
							//if(qL>=pMapL){
								if(*p<LLevel){
									*qL|=(BYTE)Mask;
									LSum++;
								}
							//}
							//else{
							//	DbgTest++;
							//}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
							}
						}
					}
				}
				else{
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qL>=&pMapL[LByte]){
							//	DbgTest++;
							//	break;
							//}
							//if(qL>=pMapL){
								if(LLevel<*p){
									*qL|=(BYTE)Mask;
									LSum++;
								}
							//}
							//else{
							//	DbgTest++;
							//}
							Mask=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
							}
						}
					}
				}
			}
			else{
				BYTE	*DMapP=DynamicMaskMap[Y+dy];
				if(RThr->ThreshouldBag.PointMove.ModeOppositeRange==false){
					int	MapX=X+dx;
					BYTE	DMapMask=(0x80>>(MapX &0x07));
					BYTE	*DMapPointer=&DMapP[MapX>>3];
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qL>=&pMapL[LByte]){
							//	DbgTest++;
							//	break;
							//}
							if(((*DMapPointer) & DMapMask)==0){
								//if(qL>=pMapL){
									if(*p<LLevel){
										*qL|=(BYTE)Mask;
										LSum++;
									}
								//}
								//else{
								//	DbgTest++;
								//}
							}
							//MapX++;
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask	=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
							}
						}
					}
				}
				else{
					int	MapX=X+dx;
					BYTE	DMapMask=(0x80>>(MapX &0x07));
					BYTE	*DMapPointer=&DMapP[MapX>>3];
					for(int x=0;x<Numb;x+=8){
						int N=8;
						if(x+8>=Numb)
							N=Numb-x;
						for(int k=0;k<N;k++,p++){
							//if(qL>=&pMapL[LByte]){
							//	DbgTest++;
							//	break;
							//}
							if(((*DMapPointer) & DMapMask)==0){
								//if(qL>=pMapL){
									if(LLevel<*p){
										*qL|=(BYTE)Mask;
										LSum++;
									}
								//}
								//else{
								//	DbgTest++;
								//}
							}
							//MapX++;
							DMapMask>>=1;
							if(DMapMask==0){
								DMapMask=0x80;
								DMapPointer++;
							}
							Mask	=_rotr(Mask,1);
							if((Mask &0x80)!=0){
								qL++;
							}
						}
					}
				}
			}
		}
	}
}
