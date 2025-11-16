/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\XDisplayPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XImageProcess.h"
#include "XDisplayImagePacket.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XPointer.h"
#include "XEntryPoint.h"
//#include "XGUI.h"
#include <omp.h>



bool	GUICmdSendBmp::MakeImage( DisplayImage::DisplayType dtype 
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate,double Yz
								 ,int localPage
								 ,LayersBase &LocalLBase
								 ,int MasterNo
								 ,IntList &LayerList
								 ,bool RedCircleMode
								 ,int32 ShowFixedPhase
								 ,int32 TransparentLevelInBitBuff
								 ,bool _ShowNGMarkInTarget
								 ,bool RepaintContinuously)
{
	RetNGData=false;
	ShowNGMarkInTarget	=_ShowNGMarkInTarget;
	DataInLayer	*LayerBuff[1000];

	DataInPage *P;
	if(ShowFixedPhase==-1){
		P=LocalLBase.GetPageData(localPage);
	}
	else{
		P=LocalLBase.GetPageDataPhase(ShowFixedPhase)->GetPageData(localPage);
	}
	if(P==NULL){
		 qDebug() << "GUICmdSendBmp::MakeImage makes :DataInPage *P=NULL localPage=" <<QString::number(localPage)
					<<" ShowFixedPhase="<<QString::number(ShowFixedPhase);
		 return false;
	}
	//if(LocalLBase.TryLockRChangingDataStructure()==false){
	//	return false;
	//}
	LocalLBase.LockRChangingDataStructure();

	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;
	int	IDataWidth	=(IData!=NULL)?IData->width():0;
	int	IDataHeight	=(IData!=NULL)?IData->height():0;
	if(IData!=NULL && (IDataWidth!=LGx || IDataHeight!=LGy || (IData->format()!=QImage::Format_ARGB32 && IData->format()!=QImage::Format_ARGB32_Premultiplied))){
		if(PntFromIData!=NULL){
			delete	PntFromIData;
			PntFromIData=NULL;
		}
		if(PntFromNGData!=NULL){
			delete	PntFromNGData;
			PntFromNGData=NULL;
		}
		delete	IData;
		delete	NGData;
		IData=NULL;
		NGData=NULL;
	}
	if(IData==NULL){
		IData =new QImage(LGx,LGy,QImage::Format_ARGB32);
		NGData=new QImage(LGx,LGy,QImage::Format_ARGB32);

		//NGData->fill(qRgba(0,0,0,0));
		::ClearImage(*NGData, 0);

		if(PntFromIData!=NULL){
			delete	PntFromIData;
			PntFromIData=NULL;
		}
		if(PntFromNGData!=NULL){
			delete	PntFromNGData;
			PntFromNGData=NULL;
		}
		//IData->fill(0);
		::ClearImage(*IData, 0);
	}
	if(PntFromIData==NULL){
		PntFromIData=new QPainter(IData);
	}
	if(PntFromNGData==NULL){
		PntFromNGData=new QPainter(NGData);
	}
	if(P->GetLayerNumb()==1){
		//if(LayerList.GetNumber()==1){
			MakeImageOneLayer( dtype 
							,IData ,P ,0, LocalLBase.GetParamGlobal()->Layer0Color
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,Yz);		
		//}
	}
	else if(LocalLBase.GetParamGlobal()->EnableToColorizeFor3Layers==false
	|| LayerList.GetCount()==1 || (LayerList.GetCount()==2 && P->GetLayerNumb()>=3)){
		if(LayerList.GetCount()==0){
			//IData->fill(0);
			::ClearImage(*IData, 0);
		}
		else if(LayerList.GetCount()==1){
			int	Layer=LayerList.GetFirst()->GetValue();
			MakeImageOneLayer( dtype 
							,IData ,P ,Layer, LocalLBase.GetParamGlobal()->GetOneLayerColor(Layer)
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,Yz);		
		}
		else if(LayerList.GetCount()>1){
			MakeImageMultiLayer( dtype
							,LayerList
							,IData ,P ,LocalLBase.GetParamGlobal()->GetOneLayerColor(LayerList.GetFirst()->GetValue())
							,MasterNo
							,LGx,LGy
							,Dx1,Dy1
							,P->GetDotPerLine() ,P->GetMaxLines()
							, ZoomRate,Yz);
		}
	}
	else
	if(P->GetLayerNumb()==2){
		double	IZoomRate=1.0/ZoomRate;
		int32	AddX=(int32)(0x10000*IZoomRate);
		ImageBuffer	*SBuff0;
		ImageBuffer	*SBuff1;
		BYTE	*CTable0=P->GetLayerData(0)->CData.RBrightTable;
		BYTE	*CTable1=P->GetLayerData(1)->CData.RBrightTable;
		bool	LockMaster=false;
		bool	LockTarget=false;
		int	DotPerLine=P->GetDotPerLine();
		LayerBuff[0]=P->GetLayerData(0);
		LayerBuff[1]=P->GetLayerData(1);

		if(GetParamGlobal()->AllocateMasterBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Master))!=0){
			LayerBuff[0]->AccessMaster.lock();
			LayerBuff[1]->AccessMaster.lock();
			SBuff0=LayerBuff[0]->GetMasterBuffPointer(MasterNo);
			SBuff1=LayerBuff[1]->GetMasterBuffPointer(MasterNo);
			LockMaster=true;
		}
		else
		if(GetParamGlobal()->AllocateTargetBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Target))!=0){
			LayerBuff[0]->AccessTarget.lock();
			LayerBuff[1]->AccessTarget.lock();
			SBuff0=LayerBuff[0]->GetDelayedViewBuffPointer();
			SBuff1=LayerBuff[1]->GetDelayedViewBuffPointer();
			LockTarget=true;
		}
		else
		if(GetParamGlobal()->AllocateBackGroundBuff==true 
		&& (dtype&DisplayImage::__BackGround)!=0){
			SBuff0=P->GetLayerData(0)->GetBackGroundBuffPointer();
			SBuff1=P->GetLayerData(1)->GetBackGroundBuffPointer();
		}
		else
		if(GetParamGlobal()->AllocateTargetTRBuff==true 
		&& (dtype&DisplayImage::__TargetTR)!=0){
			SBuff0=P->GetLayerData(0)->GetTargetTRBuffPointer();
			SBuff1=P->GetLayerData(1)->GetTargetTRBuffPointer();
		}
		else
		if((dtype&DisplayImage::__DelayedView)!=0){
			SBuff0=P->GetLayerData(0)->GetDelayedViewBuffPointer();
			SBuff1=P->GetLayerData(1)->GetDelayedViewBuffPointer();
		}
		else
		if((dtype&DisplayImage::__RawTarget)!=0){
			SBuff0=P->GetLayerData(0)->GetRawTargetBuffPointer();
			SBuff1=P->GetLayerData(1)->GetRawTargetBuffPointer();
		}
		else
		if((dtype&DisplayImage::__CamTarget)!=0){
			SBuff0=P->GetLayerData(0)->GetCamTargetBuffPointer();
			SBuff1=P->GetLayerData(1)->GetCamTargetBuffPointer();
		}
		else{
			SBuff0=NULL;
			SBuff1=NULL;
		}

		if(SBuff0!=NULL && SBuff0->IsNull()==false
		&& SBuff1!=NULL && SBuff1->IsNull()==false){
			int	XCounter1=0;
			int	XCounter2=0;
			int	XCounter3=0;
			int	iDx1=Dx1;
			int32	Start2Mx=0;
			try{
				int	x=0;
				int32	mx=0;
				if(Dx1<0){
					for(;x<LGx;x++){
						if((mx>>16)+Dx1>=0){
							break;
						}
						mx+=AddX;
						iDx1++;
						XCounter1++;
					}
				}
				Start2Mx=mx;
				for(;x<LGx;x++){
					if((mx>>16)+iDx1>=DotPerLine){
						break;
					}
					mx+=AddX;
					XCounter2++;
				}
				for(;x<LGx;x++){
					XCounter3++;
				}
			}
			catch(...)
			{}

			if(LocalLBase.GetNumThreads()>4){
				#pragma omp parallel                             
				{                                                
					#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=Dy1+y/(ZoomRate*Yz);
						if(NowY<0 || NowY>=P->GetMaxLines()){
							for(int x=0;x<LGx;x++){
								*((int32 *)d)=CTable0[0];
								d+=4;
							}
						}
						else{
							for(int x=0;x<XCounter1;x++){
								*((int32 *)d)=0;
								d+=4;
							}
							BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
							BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
							int32	mx=Start2Mx;
							//#pragma omp simd
							for(int x=0;x<XCounter2;x++){
								int	NowX=mx>>16;
								*((int32 *)d)=0xFF000000+((CTable0[*(s0+NowX)])<<16)+((CTable1[*(s1+NowX)])<<8);
								d+=4;
								mx+=AddX;
							}
							for(int x=0;x<XCounter3;x++){
								*((int32 *)d)=0;
								d+=4;
							}
						}
					}
				}
			}
			else{
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=Dy1+y/(ZoomRate*Yz);
						if(NowY<0 || NowY>=P->GetMaxLines()){
							for(int x=0;x<LGx;x++){
								*((int32 *)d)=CTable0[0];
								d+=4;
							}
						}
						else{
							for(int x=0;x<XCounter1;x++){
								*((int32 *)d)=0;
								d+=4;
							}
							BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
							BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
							int32	mx=Start2Mx;
							//#pragma omp simd
							for(int x=0;x<XCounter2;x++){
								int	NowX=mx>>16;
								*((int32 *)d)=0xFF000000+((CTable0[*(s0+NowX)])<<16)+((CTable1[*(s1+NowX)])<<8);
								d+=4;
								mx+=AddX;
							}
							for(int x=0;x<XCounter3;x++){
								*((int32 *)d)=0;
								d+=4;
							}
						}
					}
			}
		}

		if(LockMaster==true){
			LayerBuff[0]->AccessMaster.unlock();
			LayerBuff[1]->AccessMaster.unlock();
		}
		else if(LockTarget==true){
			LayerBuff[0]->AccessTarget.unlock();
			LayerBuff[1]->AccessTarget.unlock();
		}
	}
	else
	if(P->GetLayerNumb()>=3){
		double	IZoomRate=1.0/ZoomRate;
		double	IyZoomRate=1.0/(ZoomRate*Yz);
		int32	AddX=(int32)(0x10000*IZoomRate);
		ImageBuffer	*SBuff0;
		ImageBuffer	*SBuff1;
		ImageBuffer	*SBuff2;
		bool	LockMaster=false;
		bool	LockTarget=false;

		bool	UseTable= ((P->GetLayerData(0)->CData.UseTable==true)
						|| (P->GetLayerData(1)->CData.UseTable==true)
						|| (P->GetLayerData(2)->CData.UseTable==true))?true:false;

		LayerBuff[0]=P->GetLayerData(0);
		LayerBuff[1]=P->GetLayerData(1);
		LayerBuff[2]=P->GetLayerData(2);
		if(GetParamGlobal()->AllocateMasterBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Master))!=0){
			LayerBuff[0]->AccessMaster.lock();
			LayerBuff[1]->AccessMaster.lock();
			LayerBuff[2]->AccessMaster.lock();
			SBuff0=LayerBuff[0]->GetMasterBuffPointer(MasterNo);
			SBuff1=LayerBuff[1]->GetMasterBuffPointer(MasterNo);
			SBuff2=LayerBuff[2]->GetMasterBuffPointer(MasterNo);
			LockMaster=true;
		}
		else
		if(GetParamGlobal()->AllocateTargetBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Target))!=0){
			LayerBuff[0]->AccessTarget.lock();
			LayerBuff[1]->AccessTarget.lock();
			LayerBuff[2]->AccessTarget.lock();
			SBuff0=LayerBuff[0]->GetDelayedViewBuffPointer();
			SBuff1=LayerBuff[1]->GetDelayedViewBuffPointer();
			SBuff2=LayerBuff[2]->GetDelayedViewBuffPointer();
			LockTarget=true;
		}
		else
		if(GetParamGlobal()->AllocateBackGroundBuff==true 
		&& (dtype&(DisplayImage::__BackGround))!=0){
			SBuff0=LayerBuff[0]->GetBackGroundBuffPointer();
			SBuff1=LayerBuff[1]->GetBackGroundBuffPointer();
			SBuff2=LayerBuff[2]->GetBackGroundBuffPointer();
		}
		else
		if(GetParamGlobal()->AllocateTargetTRBuff==true 
		&& (dtype&DisplayImage::__TargetTR)!=0){
			SBuff0=P->GetLayerData(0)->GetTargetTRBuffPointer();
			SBuff1=P->GetLayerData(1)->GetTargetTRBuffPointer();
			SBuff2=P->GetLayerData(2)->GetTargetTRBuffPointer();
		}
		else
		if((dtype&DisplayImage::__DelayedView)!=0){
			LayerBuff[0]->AccessTarget.lock();
			LayerBuff[1]->AccessTarget.lock();
			LayerBuff[2]->AccessTarget.lock();
			SBuff0=P->GetLayerData(0)->GetDelayedViewBuffPointer();
			SBuff1=P->GetLayerData(1)->GetDelayedViewBuffPointer();
			SBuff2=P->GetLayerData(2)->GetDelayedViewBuffPointer();
			LockTarget=true;
		}
		else
		if((dtype&DisplayImage::__RawTarget)!=0){
			SBuff0=P->GetLayerData(0)->GetRawTargetBuffPointer();
			SBuff1=P->GetLayerData(1)->GetRawTargetBuffPointer();
			SBuff2=P->GetLayerData(2)->GetRawTargetBuffPointer();
		}
		else
		if((dtype&DisplayImage::__CamTarget)!=0){
			SBuff0=P->GetLayerData(0)->GetCamTargetBuffPointer();
			SBuff1=P->GetLayerData(1)->GetCamTargetBuffPointer();
			SBuff2=P->GetLayerData(2)->GetCamTargetBuffPointer();
		}
		else{
			SBuff0=NULL;
			SBuff1=NULL;
			SBuff2=NULL;
		}

		if(SBuff0!=NULL && SBuff0->IsNull()==false
		&& SBuff1!=NULL && SBuff1->IsNull()==false
		&& SBuff2!=NULL && SBuff2->IsNull()==false){
			int	DotPerLine=P->GetDotPerLine();
			int	XCounter1=0;
			int	XCounter2=0;
			int	XCounter3=0;
			int	iDx1=Dx1;
			int32	Start2Mx=0;
			try{
				int	x=0;
				int32	mx=0;
				if(Dx1<0){
					for(;x<LGx;x++){
						if((mx>>16)+Dx1>=0){
							break;
						}
						mx+=AddX;
						iDx1++;
						XCounter1++;
					}
				}
				Start2Mx=mx;
				for(;x<LGx;x++){
					if((mx>>16)+iDx1>=DotPerLine){
						break;
					}
					mx+=AddX;
					XCounter2++;
				}
				for(;x<LGx;x++){
					XCounter3++;
				}
			}
			catch(...)
			{}
			int	XCounter34=XCounter3*4;

			//OpenMP is effective , but overhead cost is more than process
			if(UseTable==true){
				BYTE	*CTableR=P->GetLayerData(0)->CData.RBrightTable;
				BYTE	*CTableG=P->GetLayerData(1)->CData.RBrightTable;
				BYTE	*CTableB=P->GetLayerData(2)->CData.RBrightTable;
				if(LocalLBase.GetNumThreads()>4){
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int y=0;y<LGy;y++){
							BYTE	*d=IData->scanLine(y);
							int	NowY=Dy1+y*IyZoomRate;
							if(d!=NULL && NowY<SBuff0->GetHeight()){
								if(NowY<0 || NowY>=P->GetMaxLines()){
									memset(d,0,LGx*sizeof(int32));
								}
								else{
									for(int x=0;x<XCounter1;x++){
										*((int32 *)d)=0;
										d+=4;
									}
									BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
									BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
									BYTE	*s2=SBuff2->GetY(NowY)+iDx1;
									int32	mx=Start2Mx;
									//#pragma omp simd
									for(int x=0;x<XCounter2;x++){
										int	NowX=mx>>16;
										*((int32 *)d)=0xFF000000+((CTableR[*(s0+NowX)])<<16)+((CTableG[*(s1+NowX)])<<8)+((CTableB[*(s2+NowX)]));
										d+=4;
										mx+=AddX;
									}
									if(XCounter34!=0){
										memset(d,0,XCounter34);
									}
								}
							}
						}
					}
				}
				else{
						for(int y=0;y<LGy;y++){
							BYTE	*d=IData->scanLine(y);
							int	NowY=Dy1+y*IyZoomRate;
							if(d!=NULL && NowY<SBuff0->GetHeight()){
								if(NowY<0 || NowY>=P->GetMaxLines()){
									memset(d,0,LGx*sizeof(int32));
								}
								else{
									for(int x=0;x<XCounter1;x++){
										*((int32 *)d)=0;
										d+=4;
									}
									BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
									BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
									BYTE	*s2=SBuff2->GetY(NowY)+iDx1;
									int32	mx=Start2Mx;
									//#pragma omp simd
									for(int x=0;x<XCounter2;x++){
										int	NowX=mx>>16;
										*((int32 *)d)=0xFF000000+((CTableR[*(s0+NowX)])<<16)+((CTableG[*(s1+NowX)])<<8)+((CTableB[*(s2+NowX)]));
										d+=4;
										mx+=AddX;
									}
									if(XCounter34!=0){
										memset(d,0,XCounter34);
									}
								}
							}
						}
				}
			}
			else{
				int	MaxBuffY=SBuff0->GetHeight();
				int	MaxLines=P->GetMaxLines();
				static	bool	EvenLine=false;
				int	StartLine=0;
				int	YStep=1;
				if(RepaintContinuously==true){
					StartLine=(EvenLine==true)?0:1;
					YStep=2;
				}
				EvenLine=!EvenLine;
				if(LGy<400){
					//#pragma omp parallel                             
					//{                                                
					//	#pragma omp for
						for(int y=StartLine;y<LGy;y+=YStep){
							BYTE	*d=IData->scanLine(y);
							int	NowY=Dy1+y*IyZoomRate;
							if(d!=NULL && NowY<MaxBuffY){
								if(NowY<0 || NowY>=MaxLines){
									memset(d,0,LGx*sizeof(int32));
								}
								else{
									for(int x=0;x<XCounter1;x++){
										*((int32 *)d)=0;
										d+=4;
									}
									if(MaxBuffY>SBuff0->GetHeight()){
										MaxBuffY=SBuff0->GetHeight();
									}
									BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
									BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
									BYTE	*s2=SBuff2->GetY(NowY)+iDx1;
									int32	mx=Start2Mx;
									for(int x=0;x<XCounter2;x++){
										int	NowX=mx>>16;
										*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
										d+=4;
										mx+=AddX;
									}
									if(XCounter34!=0){
										memset(d,0,XCounter34);
									}
								}
							}
						}
					//}
				}
				else{
					int	N=(LGy-StartLine)/YStep;
					//#pragma omp parallel num_threads(2)                        
					//{                                                
					//	#pragma omp for 
						for(int i=0;i<N;i++){
							int	y=i*YStep+StartLine;
							BYTE	*d=IData->scanLine(y);
							int	NowY=Dy1+y*IyZoomRate;
							if(d!=NULL && NowY<MaxBuffY){
								if(NowY<0 || NowY>=MaxLines){
									memset(d,0,LGx*sizeof(int32));
								}
								else{
									if(XCounter1!=0){
										memset(d,0,XCounter1*4);
										d+=XCounter1*4;
									}
									if(MaxBuffY>SBuff0->GetHeight()){
										MaxBuffY=SBuff0->GetHeight();
									}
									BYTE	*s0=SBuff0->GetY(NowY)+iDx1;
									BYTE	*s1=SBuff1->GetY(NowY)+iDx1;
									BYTE	*s2=SBuff2->GetY(NowY)+iDx1;
//#if	!defined(WIN64)
									int32	mx=Start2Mx;
									if(AddX<0x10000){
#if	!defined(WIN64)
										DWORD	D=0;
										int	NowX2=-99999999;
										for(int x=0;x<XCounter2;x++){
											int	NowX=mx>>16;
											if(NowX!=NowX2){
												D=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
												*((int32 *)d)=D;
												NowX2=NowX;
											}
											else{
												*((int32 *)d)=D;
											}
											mx+=AddX;
											d+=4;
										}

#else
										_asm{
											mov		r8,s0
											mov		rbx,s1
											mov		r10,s2
											mov		ecx,XCounter2
											mov		r11,d
											xor		rdx,rdx
											xor		rsi,rsi
											mov		edx,Start2Mx
											mov		esi,AddX
											mov		r9,0xff00
											mov		r12,4
											mov		r13,-99999999

											SLabel1:;
											mov		rdi,rdx
											shr		rdi,16
											cmp		rdi,r13
											je		CopyLast1

											mov		rax,r9		//eax=0x00ff00
											mov		al,byte ptr [r8+rdi]
											shl		eax,16
											mov		al,byte ptr [r10+rdi]
											mov		r13,rdi
											mov		ah,byte ptr [rbx+rdi]

											CopyLast1:;
											mov		[r11],eax
											add		rdx,rsi
											add		r11,r12		//add,r11,4
											loop	SLabel1
										}
#endif
									}
									else if(AddX==0x10000){
										int	NowX=mx>>16;
										s0+=NowX;
										s1+=NowX;
										s2+=NowX;
										for(int x=0;x<XCounter2;x++,NowX++){
											*((int32 *)d)=0xFF000000+((*(s0))<<16)+((*(s1))<<8)+((*(s2)));
											s0++;
											s1++;
											s2++;
											d+=4;
										}
									}
									else{
#if	!defined(WIN64)
										for(int x=0;x<XCounter2;x++){
											int	NowX=mx>>16;
											*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
											mx+=AddX;
											d+=4;
										}
#else
										_asm{
											mov		r8,s0
											mov		rbx,s1
											mov		r10,s2
											mov		ecx,XCounter2
											shr		ecx,1
											mov		r11,d
											xor		rdx,rdx
											xor		rsi,rsi
											mov		edx,Start2Mx
											mov		esi,AddX
											mov		r9,0xff00
											mov		r12,8
											jecxz	LLEnd2
											

											SLabel1:;
											mov		rdi,rdx
											mov		rax,r9		//eax=0x00ff00
											shr		rdi,16
											mov		al,byte ptr [r8+rdi]
											shl		rax,16
											add		rdx,rsi
											mov		al,byte ptr [r10+rdi]
											mov		ah,byte ptr [rbx+rdi]

											shl		rax,16
											mov		rdi,rdx
											mov		ah,0xFF		//eax=0x00ff00
											shr		rdi,16
											mov		al,byte ptr [r8+rdi]
											shl		rax,16
											mov		al,byte ptr [r10+rdi]
											mov		ah,byte ptr [rbx+rdi]
											rol		rax,32

											mov		[r11],rax
											add		rdx,rsi
											add		r11,r12		//add,r11,4
											loop	SLabel1

LLEnd2:;
											mov		ecx,XCounter2
											and		ecx,1
											cmp		cl,0
											je		LLEnd1

											mov		rdi,rdx
											mov		rax,rdx		//eax=0x00ff00
											shr		rdi,16
											mov		al,byte ptr [r8+rdi]
											shl		eax,16
											mov		al,byte ptr [r10+rdi]
											mov		ah,byte ptr [rbx+rdi]
											mov		[r11],eax
											LLEnd1:;
										}
#endif
									}
									if(XCounter34!=0){
										memset(d,0,XCounter34);
									}
									//for(int x=0;x<XCounter3;x++){
									//	*((int32 *)d)=0;
									//	d+=4;						
									//}
								}
							}
						//}
					}
				}
			}
		}

		if(LockMaster==true){
			LayerBuff[0]->AccessMaster.unlock();
			LayerBuff[1]->AccessMaster.unlock();
			LayerBuff[2]->AccessMaster.unlock();
		}
		else if(LockTarget==true){
			LayerBuff[0]->AccessTarget.unlock();
			LayerBuff[1]->AccessTarget.unlock();
			LayerBuff[2]->AccessTarget.unlock();
		}
	}
	if(((dtype&DisplayImage::__BitBuff)!=0)
	&& GetEntryPoint()->GUIIsEditMode()==false
	&& GetParamGlobal()->AllocBitBuffer==true){
		MultiplyImage(*IData, TransparentLevelInBitBuff/256.0);
		MakeImageBitLayer(IData ,P
						,LGx,LGy
						,Dx1,Dy1
						,P->GetDotPerLine() ,P->GetMaxLines()
						, ZoomRate,Yz);
		//QPainter	LPnt(IData);
		//LPnt.drawImage(0,0,TmpIData);
		//IData->save("Test.png","PNG");
	}
	if(ShowNGMarkInTarget==true){
		DrawRect(*NGData,qRgba(0,0,0,0),0, 0,NGData->width(),NGData->height());
		//NGData->fill(qRgba(0,0,0,0));
	}
	LocalLBase.MakeImageNGCircle(NGData ,PntFromNGData
					,(int)dtype 
					,Gx1,Gy1 ,Gx2,Gy2
					,MovX,MovY, ZoomRate
					,localPage
					,RedCircleMode
					,ShowNGMarkInTarget
					,RetNGData);
	LocalLBase.UnlockChangingDataStructure();
		
	return true;
}


bool	GUICmdSendBmp::MakeImageBitLayer(QImage *IData , DataInPage *P
										 ,int LGx,int LGy
										 ,int Dx1,int Dy1
										 ,int DotPerLine ,int MaxLines
										, double ZoomRate ,double Yz)
{
	double	IZoomRate=1.0/ZoomRate;
	double	IyZoomRate=1.0/(ZoomRate*Yz);
	int32	AddX=(int32)(0x10000*IZoomRate);
	ImageBuffer	*SBuff0=NULL;
	ImageBuffer	*SBuff1=NULL;
	ImageBuffer	*SBuff2=NULL;

	if(GetLayersBase()->TryLockRChangingDataStructure()==false){
		return false;
	}

	DWORD	ColTable[256];
	if(P->GetLayerNumb()==1){
		SBuff0=P->GetLayerData(0)->GetBitBuffPointer();
		if(SBuff0==NULL){
			return false;
		}
		ColTable[0]=(DWORD)(qRgb (0,0,0));
		ColTable[1]=(DWORD)(qRgb (255,255,255));
	}
	else if(P->GetLayerNumb()==2){
		SBuff0=P->GetLayerData(0)->GetBitBuffPointer();
		SBuff1=P->GetLayerData(1)->GetBitBuffPointer();
		if(SBuff0==NULL || SBuff1==NULL){
			return false;
		}
		ColTable[0]=(DWORD)(qRgb (0,0,0));
		ColTable[1]=(DWORD)(qRgb (128,128,128));
		ColTable[2]=(DWORD)(qRgb (200,200,200));
		ColTable[3]=(DWORD)(qRgb (255,255,255));
	}
	else if(P->GetLayerNumb()>=3){
		SBuff0=P->GetLayerData(0)->GetBitBuffPointer();
		SBuff1=P->GetLayerData(1)->GetBitBuffPointer();
		SBuff2=P->GetLayerData(2)->GetBitBuffPointer();
		if(SBuff0==NULL || SBuff1==NULL || SBuff2==NULL){
			return false;
		}
		ColTable[0]=(DWORD)(qRgb (	0	,0	,0	));
		ColTable[1]=(DWORD)(qRgb (	255	,0	,0	));
		ColTable[2]=(DWORD)(qRgb (	0	,255,0	));
		ColTable[3]=(DWORD)(qRgb (	255	,255,0	));
		ColTable[4]=(DWORD)(qRgb (	0	,0	,255));
		ColTable[5]=(DWORD)(qRgb (	255	,0	,255));
		ColTable[6]=(DWORD)(qRgb (	0	,255,255));
		ColTable[7]=(DWORD)(qRgb (	255	,255,255));
	}
	
	int	XCounter1=0;
	int	XCounter2=0;
	int	XCounter3=0;
	int	iDx1=Dx1;
	int32	Start2Mx=0;
	try{
		int	x=0;
		int32	mx=0;
		if(Dx1<0){
			for(;x<LGx;x++){
				if((mx>>16)+Dx1>=0){
					break;
				}
				mx+=AddX;
				iDx1++;
				XCounter1++;
			}
		}
		Start2Mx=mx;
		for(;x<LGx;x++){
			if((mx>>16)+iDx1>=DotPerLine){
				break;
			}
			mx+=AddX;
			XCounter2++;
		}
		for(;x<LGx;x++){
			XCounter3++;
		}
	}
	catch(...)
	{}

	if(P->GetLayerNumb()==1){
		if(GetLayersBase()->GetNumThreads()>4){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B=SBuff0->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							if(GetBmpBitOnY(B,k)!=0)
								*d=ColTable[1];
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B=SBuff0->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							if(GetBmpBitOnY(B,k)!=0)
								*d=ColTable[1];
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
		}
	}
	else if(P->GetLayerNumb()==2){
		if(GetLayersBase()->GetNumThreads()>4){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B0=SBuff0->GetY(ry);
						BYTE	*B1=SBuff1->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							int	c=0;
							if(GetBmpBitOnY(B0,k)!=0)
								c |=1;
							if(GetBmpBitOnY(B1,k)!=0)
								c |=2;
							if(c!=0){
								*d=ColTable[c];
							}
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B0=SBuff0->GetY(ry);
						BYTE	*B1=SBuff1->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							int	c=0;
							if(GetBmpBitOnY(B0,k)!=0)
								c |=1;
							if(GetBmpBitOnY(B1,k)!=0)
								c |=2;
							if(c!=0){
								*d=ColTable[c];
							}
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
		}
	}
	else if(P->GetLayerNumb()>=3){
		if(GetLayersBase()->GetNumThreads()>4){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B0=SBuff0->GetY(ry);
						BYTE	*B1=SBuff1->GetY(ry);
						BYTE	*B2=SBuff2->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							int	c=0;
							if(GetBmpBitOnY(B0,k)!=0)
								c |=1;
							if(GetBmpBitOnY(B1,k)!=0)
								c |=2;
							if(GetBmpBitOnY(B2,k)!=0)
								c |=4;
							if(c!=0){
								*d=ColTable[c];
							}
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx*4);
					}
					else{
						for(int x=0;x<XCounter1;x++){
							*d=0;
							d++;
						}
						int32	mx=Start2Mx;
						BYTE	*B0=SBuff0->GetY(ry);
						BYTE	*B1=SBuff1->GetY(ry);
						BYTE	*B2=SBuff2->GetY(ry);
						//#pragma omp simd
						for(int x=0;x<XCounter2;x++){
							int	k=iDx1+(mx>>16);
							int	c=0;
							if(GetBmpBitOnY(B0,k)!=0)
								c |=1;
							if(GetBmpBitOnY(B1,k)!=0)
								c |=2;
							if(GetBmpBitOnY(B2,k)!=0)
								c |=4;
							if(c!=0){
								*d=ColTable[c];
							}
							d++;
							mx+=AddX;
						}
						for(int x=0;x<XCounter3;x++){
							*d=0;
							d++;
						}
					}
				}
		}
	}
	GetLayersBase()->UnlockChangingDataStructure();
	return true;
}
bool	GUICmdSendBmp::MakeImageOneLayer( DisplayImage::DisplayType dtype 
										 ,QImage *IData , DataInPage *P ,int Layer , QColor LColor
										 ,int MasterNo
										 ,int LGx,int LGy
										 ,int Dx1,int Dy1
										 ,int DotPerLine ,int MaxLines
										, double ZoomRate ,double Yz)
{
	double	IZoomRate=1.0/ZoomRate;
	double	IyZoomRate=1.0/(ZoomRate*Yz);
	int32	AddX=(int32)(0x1000*IZoomRate);
	ImageBuffer	*SBuff;
	bool	LockMaster=false;
	bool	LockTarget=false;
	DataInLayer	*LayerBuff=P->GetLayerData(Layer);

	if(GetParamGlobal()->AllocateMasterBuff==true 
	&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Master))!=0){
		SBuff=LayerBuff->GetMasterBuffPointer(MasterNo);
		LayerBuff->AccessMaster.lock();
		LockMaster=true;
	}
	else
	if(GetParamGlobal()->AllocateTargetBuff==true 
	&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Target))!=0){
		SBuff=LayerBuff->GetDelayedViewBuffPointer();
		LayerBuff->AccessTarget.lock();
		LockTarget=true;
	}
	else
	if(GetParamGlobal()->AllocateBackGroundBuff==true 
	&& (dtype&(DisplayImage::__BackGround))!=0){
		SBuff=LayerBuff->GetBackGroundBuffPointer();
	}
	else
	if(GetParamGlobal()->AllocateTargetTRBuff==true 
	&& (dtype&DisplayImage::__TargetTR)!=0){
		SBuff=LayerBuff->GetTargetTRBuffPointer();
	}
	else
	if((dtype&DisplayImage::__DelayedView)!=0){
		SBuff=LayerBuff->GetDelayedViewBuffPointer();
	}
	else
	if((dtype&DisplayImage::__RawTarget)!=0){
		SBuff=LayerBuff->GetRawTargetBuffPointer();
	}
	else
	if((dtype&DisplayImage::__CamTarget)!=0){
		SBuff=LayerBuff->GetCamTargetBuffPointer();
	}
	else{
		SBuff=NULL;
	}
	GetLayersBase()->LockRChangingDataStructure();
	if(SBuff!=NULL && SBuff->IsNull()==false){
		DotPerLine	=min(DotPerLine,SBuff->GetWidth());
		MaxLines	=min(MaxLines,SBuff->GetHeight());
		int	XCounter1=0;
		int	XCounter2=0;
		int	XCounter3=0;
		int	iDx1=Dx1;
		int32	Start2Mx=0;
		try{
			int	x=0;
			int32	mx=0;
			if(Dx1<0){
				for(;x<LGx;x++){
					if((mx>>12)+Dx1>=0){
						break;
					}
					mx+=AddX;
					iDx1++;
					XCounter1++;
				}
			}
			Start2Mx=mx;
			for(;x<LGx;x++){
				if((mx>>12)+iDx1>=DotPerLine){
					break;
				}
				mx+=AddX;
				XCounter2++;
			}
			for(;x<LGx;x++){
				XCounter3++;
			}
		}
		catch(...)
		{}


		BYTE	*MTable=P->GetLayerData(Layer)->CData.RBrightTable;
		DWORD	MonoTable[256];
		for(int i=0;i<256;i++){
			MonoTable[i]=(DWORD)qRgb(MTable[i],MTable[i],MTable[i]);
		}

		//なぜかOpenMPでMonoTableが異常になる
		//#pragma omp parallel                       
		//{                                                
		//	#pragma omp for 
			for(int y=0;y<LGy;y++){
				DWORD	*d=(DWORD *)IData->scanLine(y);
				int		ry=Dy1+y*IyZoomRate;
				if(ry<0 || ry>=MaxLines){
					memset(d,0,LGx*4);
				}
				else{
					for(int x=0;x<XCounter1;x++){
						*d=0;
						d++;
					}
					int32	mx=Start2Mx;
					BYTE	*s=SBuff->GetY(ry)+iDx1;
					//#pragma omp simd
					for(int x=0;x<XCounter2;x++){
						if(mx>=0){
							*d = MonoTable[*(s + (mx >> 12))];
						}
						d++;
						mx+=AddX;
					}
					for(int x=0;x<XCounter3;x++){
						*d=0;
						d++;
					}
				}
			}
		//}
	}
	else{
		//IData->fill(0);
		::ClearImage(*IData, 0);
	}
	GetLayersBase()->UnlockChangingDataStructure();

	if(LockMaster==true){
		LayerBuff->AccessMaster.unlock();
	}
	else if(LockTarget==true){
		LayerBuff->AccessTarget.unlock();
	}
	return true;
}
bool	GUICmdSendBmp::MakeImageMultiLayer( DisplayImage::DisplayType dtype 
										   ,IntList &LayerList
										 ,QImage *IData , DataInPage *P ,QColor LColor
										 ,int MasterNo
										 ,int LGx,int LGy
										 ,int Dx1,int Dy1
										 ,int DotPerLine ,int MaxLines
										, double ZoomRate ,double Yz)
{
	double	IZoomRate=1.0/ZoomRate;
	double	IyZoomRate=1.0/(ZoomRate*Yz);
	int32	AddX=(int32)(0x10000*IZoomRate);
	ImageBuffer	*SBuff[1000];
	DataInLayer	*LayerBuff[1000];
	bool	LockMaster=false;
	bool	LockTarget=false;

	int	N=0;
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext(),N++){
		int	Layer=L->GetValue();
		LayerBuff[N]=P->GetLayerData(Layer);
		if(GetParamGlobal()->AllocateMasterBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Master))!=0){
			SBuff[N]=LayerBuff[N]->GetMasterBuffPointer(MasterNo);
			LayerBuff[N]->AccessMaster.lock();
			LockMaster=true;
		}
		else
		if(GetParamGlobal()->AllocateTargetBuff==true 
		&& (dtype&(DisplayImage::__BitBuff | DisplayImage::__Target))!=0){
			SBuff[N]=LayerBuff[N]->GetDelayedViewBuffPointer();
			LayerBuff[N]->AccessTarget.lock();
			LockTarget=true;
		}
		else
		if(GetParamGlobal()->AllocateBackGroundBuff==true 
		&& (dtype&DisplayImage::__BackGround)!=0){
			SBuff[N]=LayerBuff[N]->GetBackGroundBuffPointer();
		}
		else
		if(GetParamGlobal()->AllocateTargetTRBuff==true 
		&& (dtype&DisplayImage::__TargetTR)!=0){
			SBuff[N]=LayerBuff[N]->GetTargetTRBuffPointer();
		}
		else
		if((dtype&DisplayImage::__DelayedView)!=0){
			SBuff[N]=LayerBuff[N]->GetDelayedViewBuffPointer();
		}
		else
		if((dtype&DisplayImage::__RawTarget)!=0){
			SBuff[N]=LayerBuff[N]->GetRawTargetBuffPointer();
		}
		else
		if((dtype&DisplayImage::__CamTarget)!=0){
			SBuff[N]=LayerBuff[N]->GetCamTargetBuffPointer();
		}
		else{
			SBuff[N]=NULL;
		}
	}
	bool	Available=true;
	for(int i=0;i<N;i++){
		if(SBuff[i]==NULL || SBuff[i]->IsNull()==true){
			Available=false;
			break;
		}
	}
	if(GetLayersBase()->TryLockRChangingDataStructure()==false){
		return false;
	}
	if(Available==true){
		DWORD	ColTable[256];
		for(int i=0;i<256;i++){
			//ColTable[i]=(DWORD)(qRgb (LColor.red()*i/255,LColor.green()*i/255,LColor.blue()*i/255));
			ColTable[i]=(DWORD)(qRgb ((LColor.red()*i)>>8,(LColor.green()*i)>>8,(LColor.blue()*i)>>8));
		}
		if(GetLayersBase()->GetNumThreads()>4){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx);
					}
					else{
						int	x=0;
						int32	mx=0;
						int	iDx1=Dx1;
						if(Dx1<0){
							for(;x<LGx;x++){
								if((mx>>16)+Dx1>=0){
									break;
								}
								*d=0;
								d++;
								mx+=AddX;
								iDx1++;
							}
						}
						BYTE	*s[1000];
						for(int i=0;i<N;i++){
							s[i]=SBuff[i]->GetY(ry)+iDx1;
						}
						for(;x<LGx;x++){
							if((mx>>16)+iDx1>=DotPerLine){
								break;
							}
							int	h=0;
							for(int i=0;i<N;i++){
								h=max(h,*(s[i]+(mx>>16)));
							}
							*d=ColTable[h];
							d++;
							mx+=AddX;
						}
						for(;x<LGx;x++){
							*d=0;
							d++;
						}
					}
				}
			}
		}
		else{
				for(int y=0;y<LGy;y++){
					DWORD	*d=(DWORD *)IData->scanLine(y);
					int		ry=Dy1+y*IyZoomRate;
					if(ry<0 || ry>=MaxLines){
						memset(d,0,LGx);
					}
					else{
						int	x=0;
						int32	mx=0;
						int	iDx1=Dx1;
						if(Dx1<0){
							for(;x<LGx;x++){
								if((mx>>16)+Dx1>=0){
									break;
								}
								*d=0;
								d++;
								mx+=AddX;
								iDx1++;
							}
						}
						BYTE	*s[1000];
						for(int i=0;i<N;i++){
							s[i]=SBuff[i]->GetY(ry)+iDx1;
						}
						for(;x<LGx;x++){
							if((mx>>16)+iDx1>=DotPerLine){
								break;
							}
							int	h=0;
							for(int i=0;i<N;i++){
								h=max(h,*(s[i]+(mx>>16)));
							}
							*d=ColTable[h];
							d++;
							mx+=AddX;
						}
						for(;x<LGx;x++){
							*d=0;
							d++;
						}
					}
				}
		}
	}
	else{
		//IData->fill(0);
		::ClearImage(*IData, 0);
	}
	GetLayersBase()->UnlockChangingDataStructure();

	if(LockMaster==true){
		for(int i=0;i<N;i++){
			LayerBuff[i]->AccessMaster.unlock();
		}
	}
	else if(LockTarget==true){
		for(int i=0;i<N;i++){
			LayerBuff[i]->AccessTarget.unlock();
		}
	}
	return true;
}
