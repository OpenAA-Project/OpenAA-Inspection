/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "XLearningRule.h"
#include "XPassword.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"



void	DataInPage::Draw(QImage &img, int movx ,int movy ,double ZoomRate)
{
	if(img.depth()!=32){
		return;
	}
	int		gx1=(GetOutlineOffset()->x+movx)*ZoomRate;
	int		gy1=(GetOutlineOffset()->y+movy)*ZoomRate;
	int		gx2=(GetOutlineOffset()->x+movx+GetDotPerLine() )*ZoomRate;
	int		gy2=(GetOutlineOffset()->y+movy+GetMaxLines())*ZoomRate;

	if(gx1<0){
		gx1=0;
	}
	if(gy1<0){
		gy1=0;
	}
	if(gx2>img.width()){
		gx2=img.width();
	}
	if(gy2>img.height()){
		gy2=img.height();
	}
	int	Lx1=gx1/ZoomRate-(GetOutlineOffset()->x+movx);
	int	Ly1=gy1/ZoomRate-(GetOutlineOffset()->y+movy);
	//int	Lw=(gx2-gx1)/ZoomRate;
	//int	Lh=(gy2-gy1)/ZoomRate;
	double	ZZoomRate=1.0/ZoomRate;
	if(GetLayerNumb()==1){
		double	DLy=Ly1;
		for(int y=gy1;y<gy2;y++,DLy+=ZZoomRate){
			if(DLy<0){
				continue;
			}
			if(DLy>=GetMaxLines()){
				break;
			}
			BYTE	*dst=img.scanLine(y);
			dst+=gx1*4;
			double	DLx=Lx1;
			BYTE	*src=GetLayerData(0)->GetMasterBuff().GetY((int)DLy);
			for(int x=gx1;x<gx2;x++,DLx+=ZZoomRate){
				if(DLx<0){
					continue;
				}
				if(DLx>=GetDotPerLine()){
					break;
				}
				BYTE	c= *(src+(int)DLx);
				*dst=c;
				*(dst+1)=c;
				*(dst+2)=c;
				dst+=4;
			}
		}
	}
	else if(GetLayerNumb()==2){
		double	DLy=Ly1;
		for(int y=gy1;y<gy2;y++,DLy+=ZZoomRate){
			if(DLy<0){
				continue;
			}
			if(DLy>=GetMaxLines()){
				break;
			}
			BYTE	*dst=img.scanLine(y);
			dst+=gx1*4;
			double	DLx=Lx1;
			BYTE	*src1=GetLayerData(0)->GetMasterBuff().GetY((int)DLy);
			BYTE	*src2=GetLayerData(1)->GetMasterBuff().GetY((int)DLy);
			for(int x=gx1;x<gx2;x++,DLx+=ZZoomRate){
				if(DLx<0){
					continue;
				}
				if(DLx>=GetDotPerLine()){
					break;
				}
				BYTE	c1= *(src1+(int)DLx);
				BYTE	c2= *(src2+(int)DLx);
				*dst=c1;
				*(dst+1)=c1;
				*(dst+2)=c2;
				dst+=4;
			}
		}
	}
	else if(GetLayerNumb()>=3){
		double	DLy=Ly1;
		for(int y=gy1;y<gy2;y++,DLy+=ZZoomRate){
			if(DLy<0){
				continue;
			}
			if(DLy>=GetMaxLines()){
				break;
			}
			BYTE	*dst=img.scanLine(y);
			dst+=gx1*4;
			double	DLx=Lx1;
			BYTE	*src1=GetLayerData(0)->GetMasterBuff().GetY((int)DLy);
			BYTE	*src2=GetLayerData(1)->GetMasterBuff().GetY((int)DLy);
			BYTE	*src3=GetLayerData(2)->GetMasterBuff().GetY((int)DLy);
			for(int x=gx1;x<gx2;x++,DLx+=ZZoomRate){
				if(DLx<0){
					continue;
				}
				if(DLx>=GetDotPerLine()){
					break;
				}
				BYTE	c1= *(src1+(int)DLx);
				BYTE	c2= *(src2+(int)DLx);
				BYTE	c3= *(src3+(int)DLx);
				*dst=c1;
				*(dst+1)=c2;
				*(dst+2)=c3;
				dst+=4;
			}
		}
	}

}


void	DataInPage::DrawImage(QImage &Img, int movx ,int movy ,double ZoomRate
							,bool Mastered
							,const QColor &LColor
							,int OffsetX ,int OffsetY)
{
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	ImageBuffer	*SBuff[3];
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		if(Mastered==true){
			SBuff[Layer]=&GetLayerData(Layer)->GetMasterBuff();
		}
		else{
			SBuff[Layer]=&GetLayerData(Layer)->GetTargetBuff();
		}
	}
	int	LGx=Img.width();
	int	LGy=Img.height();

	int	iHx1=(movx+OffsetX)*ZoomRate;
	int	iHy1=(movy+OffsetY)*ZoomRate;
	int	iHx2=(GetDotPerLine()+movx+OffsetX)*ZoomRate;
	int	iHy2=(GetMaxLines()  +movy+OffsetY)*ZoomRate;

	int	iHyNumb=iHy2-iHy1;
	int	iHxNumb=iHx2-iHx1;

	if(iHyNumb+iHy1>=LGy){
		iHyNumb=LGy-iHy1;
	}
	if(iHxNumb+iHx1>=LGx){
		iHxNumb=LGx-iHx1;
	}
	if(iHxNumb<=0){
		return;
	}
	if(iHyNumb<=0){
		return;
	}

	if(GetLayerNumb()>=3){
		int32	ColMask=LColor.alpha()<<24;
		#pragma omp parallel                             
		{
			#pragma omp for
			for(int y=0;y<iHyNumb;y++){
				int	Y=iHy1+y;
				if(Y<0){
					continue;
				}
				int	Sy=y*IZoomRate;
				if(Sy>=GetMaxLines()){
					continue;
				}
				DWORD	*d=(DWORD *)Img.scanLine(Y);
				int64	mx=0;
				BYTE	*sR=SBuff[0]->GetY(Sy);
				BYTE	*sG=SBuff[1]->GetY(Sy);
				BYTE	*sB=SBuff[2]->GetY(Sy);
				for(int x=0;x<iHxNumb;x++){
					if((x+iHx1)<0){
						mx+=AddX;
						continue;
					}
					int	NowX=mx>>32;
					((int32 *)d)[x+iHx1]=ColMask+((*(sR+NowX))<<16)+((*(sG+NowX))<<8)+((*(sB+NowX)));
					mx+=AddX;
				}
			}
		}
	}
	else if(GetLayerNumb()==2){
		int32	ColMask=LColor.alpha()<<24;
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<iHyNumb;y++){
				int	Y=iHy1+y;
				if(Y<0){
					continue;
				}
				int	Sy=y*IZoomRate;
				if(Sy>=GetMaxLines()){
					continue;
				}
				DWORD	*d=(DWORD *)Img.scanLine(Y);
				int64	mx=0;
				BYTE	*sR=SBuff[0]->GetY(Sy);
				BYTE	*sG=SBuff[1]->GetY(Sy);
				for(int x=0;x<iHxNumb;x++){
					if((x+iHx1)<0){
						mx+=AddX;
						continue;
					}
					int	NowX=mx>>32;
					((int32 *)d)[x+iHx1]=ColMask+((*(sR+NowX))<<16)+((*(sG+NowX))<<8)+((*(sG+NowX)));
					mx+=AddX;
				}
			}
		}
	}
	else if(GetLayerNumb()==1){
		DWORD	ColTable[256];
		for(int i=0;i<256;i++){
			ColTable[i]=(DWORD)(qRgba ((LColor.red()*i)>>8,(LColor.green()*i)>>8,(LColor.blue()*i)>>8,LColor.alpha()));
		}
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<iHyNumb;y++){
				int	Y=iHy1+y;
				if(Y<0){
					continue;
				}
				int	Sy=y*IZoomRate;
				if(Sy>=GetMaxLines()){
					continue;
				}
				DWORD	*d=(DWORD *)Img.scanLine(Y);
				int64	mx=0;
				BYTE	*sR=SBuff[0]->GetY(Sy);
				for(int x=0;x<iHxNumb;x++){
					if((x+iHx1)<0){
						mx+=AddX;
						continue;
					}
					int	NowX=mx>>32;
					((int32 *)d)[x+iHx1]=ColTable[*(sR+NowX)];
					mx+=AddX;
				}
			}
		}
	}
}

//================================================================================


bool    LayersBase::SaveMasterImage(const QString &filename)
{
	QFile	file(filename);

	if(file.open(QIODevice::WriteOnly)==true){
		DWORD	ID=0xA55AE01F;

		if(file.write((const char *)&ID ,sizeof(ID))!=sizeof(ID)){
            return(false);
		}

		int32	D=GetPageNumb();
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetParamGlobal()->DotPerLine;
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetParamGlobal()->MaxLines;
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetMaxLayerNumb();
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}

		for(int p=0;p<GetPageNumb();p++){
            DataInPage *P=GetPageData(p);
            for(int r=0;r<GetLayerNumb(p);r++){
				DataInLayer	*Ly=P->GetLayerData(r);	
				int y;
				int	Lx	=min(P->GetDotPerLine()	,GetParamGlobal()->DotPerLine	,Ly->GetTargetBuff().GetWidth());
				int	LinY=min(P->GetMaxLines()	,GetParamGlobal()->MaxLines		,Ly->GetTargetBuff().GetHeight());
                for(y=0;y<LinY;y++){
                    BYTE    *dp=Ly->GetMasterBuff().GetY(y);
					if(file.write((const char *)dp ,Lx)!=Lx){
                        return(false);
					}
                }
                BYTE    qdp[20000];
				memset(qdp,0,sizeof(qdp));
                for(;y<GetParamGlobal()->MaxLines;y++){
					if(file.write((const char *)qdp ,Lx)!=Lx){
                        return(false);						
                    }
                }
            }
        }
	}
    return(false);
}

bool    LayersBase::LoadMasterImage(const QString &filename)
{
	QFile	file(filename);

	if(file.exists()==true){
		if(file.open(QIODevice::ReadOnly)==true){
            int32    mMaxScans;
            int32    mDotPerLine;
            int32    mMaxLines;
            int32    mLayer;
            DWORD	ID;
			if(file.read((char *)&ID     ,sizeof(ID     ))!=sizeof(ID     )){
				return(false);
			}
            if(ID==0xA55AE01F){
				if(file.read((char *)&mMaxScans     ,sizeof(mMaxScans		))!=sizeof(mMaxScans	)){
                    return(false);
				}
				if(file.read((char *)&mDotPerLine   ,sizeof(mDotPerLine		))!=sizeof(mDotPerLine	)){
                    return(false);
				}
				if(file.read((char *)&mMaxLines     ,sizeof(mMaxLines		))!=sizeof(mMaxLines	)){
                    return(false);
				}
				if(file.read((char *)&mLayer        ,sizeof(mLayer			))!=sizeof(mLayer		)){
                    return(false);
				}
	            for(int p=0;(p<mMaxScans) && (p<GetParamGlobal()->PageNumb);p++){
					DataInPage	*P=GetPageData(p);
					for(int L=0;(L<mLayer) && (L<P->GetLayerNumb());L++){
						DataInLayer	*Ly=P->GetLayerData(L);
		                int y;
			            for(y=0;(y<mMaxLines) && (y<GetParamGlobal()->MaxLines);y++){
				            int Len=min(GetParamGlobal()->DotPerLine,mDotPerLine,P->GetDotPerLine());
					        BYTE    *dp=Ly->GetMasterBuff().GetY(y);
							if(file.read((char *)dp,Len)!=Len){
								return(false);
							}
							if(mDotPerLine>Len){
								int d=mDotPerLine-Len;
	                            while(d>0){
									if(Len>d){
			                            Len=d;
									}
				                    dp=Ly->GetMasterBuff().GetY(0);
									if(file.read((char *)dp,Len)!=Len){
										return(false);
									}
						            d-=Len;
							        }
	                            }
		                    }
			            for(;y<mMaxLines;y++){
							int Len=min(GetParamGlobal()->DotPerLine,mDotPerLine,P->GetDotPerLine());
					        BYTE    *dp=Ly->GetMasterBuff().GetY(0);
							if(file.read((char *)dp,Len)!=Len){
								return(false);
							}
							if(mDotPerLine>Len){
								int d=mDotPerLine-Len;
								while(d>0){
									if(Len>d){
		                                Len=d;
									}
			                        dp=Ly->GetMasterBuff().GetY(0);
									if(file.read((char *)dp,Len)!=Len){
										return(false);
									}
					                d-=Len;
								}
                            }
                        }
                    }
                }
            }
        }
	}
    return(true);
}
bool    LayersBase::LoadMasterImageInPage(const QString &filename ,int LPage)
{
	QFile	file(filename);

	if(file.exists()==true){
		if(file.open(QIODevice::ReadOnly)==true){
            int32    mMaxScans;
            int32    mDotPerLine;
            int32    mMaxLines;
            int32    mLayer;
            DWORD	ID;
			if(file.read((char *)&ID     ,sizeof(ID     ))!=sizeof(ID     )){
				return(false);
			}
            if(ID==0xA55AE01FU){
				if(file.read((char *)&mMaxScans     ,sizeof(mMaxScans		))!=sizeof(mMaxScans	)){
                    return(false);
				}
				if(file.read((char *)&mDotPerLine   ,sizeof(mDotPerLine		))!=sizeof(mDotPerLine	)){
                    return(false);
				}
				if(file.read((char *)&mMaxLines     ,sizeof(mMaxLines		))!=sizeof(mMaxLines	)){
                    return(false);
				}
				if(file.read((char *)&mLayer        ,sizeof(mLayer			))!=sizeof(mLayer		)){
                    return(false);
				}
				DataInPage	*P=GetPageData(LPage);
				for(int L=0;(L<mLayer) && (L<P->GetLayerNumb());L++){
					DataInLayer	*Ly=P->GetLayerData(L);
		            int y;
					int	MinY=min(mMaxLines,GetParamGlobal()->MaxLines,P->GetMaxLines());
					int Len =min(GetParamGlobal()->DotPerLine,mDotPerLine,P->GetDotPerLine());
					for(y=0;y<MinY;y++){					
						BYTE    *dp=Ly->GetMasterBuff().GetY(y);
						if(file.read((char *)dp,Len)!=Len){
							return(false);
						}
						if(mDotPerLine>Len){
							int d=mDotPerLine-Len;
							while(d>0){
								if(Len>d){
									Len=d;
								}
								dp=Ly->GetMasterBuff().GetY(0);
								if(file.read((char *)dp,Len)!=Len){
									return(false);
								}
								d-=Len;
							}
						}
					}
					for(;y<mMaxLines;y++){
						BYTE    *dp=Ly->GetMasterBuff().GetY(0);
						if(file.read((char *)dp,Len)!=Len){
							return(false);
						}
						if(mDotPerLine>Len){
							int d=mDotPerLine-Len;
							while(d>0){
								if(Len>d){
									Len=d;
								}
								dp=Ly->GetMasterBuff().GetY(0);
								if(file.read((char *)dp,Len)!=Len){
									return(false);
								}
								d-=Len;
							}
						}
					}
				}
			}
		}
	}
	
    return(true);
}

bool    LayersBase::SaveTargetImage(const QString &filename)
{
	QFile	file(filename);

	if(file.open(QIODevice::WriteOnly)==true){
		DWORD	ID=0xA55AE01F;

		if(file.write((const char *)&ID ,sizeof(ID))!=sizeof(ID)){
            return(false);
		}

		int32	D=GetPageNumb();
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetParamGlobal()->DotPerLine;
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetParamGlobal()->MaxLines;
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}
		D=GetMaxLayerNumb();
		if(file.write((const char *)&D ,sizeof(D))!=sizeof(D)){
            return(false);
		}

		for(int p=0;p<GetPageNumb();p++){
            DataInPage *P=GetPageData(p);
            for(int r=0;r<P->GetLayerNumb();r++){
				DataInLayer	*Ly=P->GetLayerData(r);	
				int y;
				int	Lx	=min(GetParamGlobal()->DotPerLine,Ly->GetTargetBuff().GetWidth() ,P->GetDotPerLine());
				int	MinY=min(GetParamGlobal()->MaxLines	 ,Ly->GetTargetBuff().GetHeight(),P->GetMaxLines());

                for(y=0;y<MinY;y++){
                    BYTE    *dp=Ly->GetTargetBuff().GetY(y);
					if(file.write((const char *)dp ,Lx)!=Lx){
                        return(false);
					}
                }
                BYTE    qdp[20000];
				memset(qdp,0,sizeof(qdp));
                for(;y<GetParamGlobal()->MaxLines;y++){
					if(file.write((const char *)qdp ,Lx)!=Lx){
                        return(false);
						}	
                    }
                }
            }
        return(true);
        }
    return(false);
}

bool    LayersBase::LoadTargetImage(const QString &filename)
{
	QFile	file(filename);

	if(file.exists()==true){
		if(file.open(QIODevice::ReadOnly)==true){
            int32    mMaxScans;
            int32    mDotPerLine;
            int32    mMaxLines;
            int32    mLayer;
            DWORD	ID;
			if(file.read((char *)&ID     ,sizeof(ID     ))!=sizeof(ID     )){
				return(false);
			}
            if(ID==0xA55AE01F){
				if(file.read((char *)&mMaxScans     ,sizeof(mMaxScans		))!=sizeof(mMaxScans	)){
                    return(false);
				}
				if(file.read((char *)&mDotPerLine   ,sizeof(mDotPerLine		))!=sizeof(mDotPerLine	)){
                    return(false);
				}
				if(file.read((char *)&mMaxLines     ,sizeof(mMaxLines		))!=sizeof(mMaxLines	)){
                    return(false);
				}
				if(file.read((char *)&mLayer        ,sizeof(mLayer			))!=sizeof(mLayer		)){
                    return(false);
				}

	            for(int p=0;(p<mMaxScans) && (p<GetPageNumb());p++){
					DataInPage	*P=GetPageData(p);
					int Len =min(GetParamGlobal()->DotPerLine,mDotPerLine,P->GetDotPerLine());
					int	MinY=min(GetParamGlobal()->MaxLines  ,mMaxLines	 ,P->GetMaxLines());

					for(int L=0;(L<mLayer) && (L<P->GetLayerNumb());L++){
						DataInLayer	*Ly=P->GetLayerData(L);
		                int y;
			            for(y=0;y<MinY;y++){
					        BYTE    *dp=Ly->GetTargetBuff().GetY(y);
							if(file.read((char *)dp,Len)!=Len){
								return(false);
							}
							if(mDotPerLine>Len){
								int d=mDotPerLine-Len;
	                            while(d>0){
									if(Len>d){
			                            Len=d;
									}
				                    dp=Ly->GetTargetBuff().GetY(0);
									if(file.read((char *)dp,Len)!=Len){
										return(false);
									}
						            d-=Len;
							        }
	                            }
		                    }
			            for(;y<mMaxLines;y++){
					        BYTE    *dp=Ly->GetTargetBuff().GetY(0);
							if(file.read((char *)dp,Len)!=Len){
								return(false);
							}
							if(mDotPerLine>Len){
								int d=mDotPerLine-Len;
								while(d>0){
									if(Len>d){
		                                Len=d;
									}
			                        dp=Ly->GetTargetBuff().GetY(0);
									if(file.read((char *)dp,Len)!=Len){
										return(false);
									}
					                d-=Len;
								}
                            }
                        }
                    }
                }
            }
        }
	}
    return(true);
}



bool    LayersBase::LoadBitmapToMaster(int page ,QIODevice *f)
{
	QImageReader L(f);
	QImage	qimg=L.read();
    int XLen=qimg.width();
    int YLen=qimg.height();
    for(int r=0;r<GetLayerNumb(page);r++){
		DataInPage	*P=GetPageData(page);
        DataInLayer *L=P->GetLayerData(r);
		int	MinY=min(YLen,GetParamGlobal()->MaxLines	,P->GetMaxLines());
		int	MinX=min(XLen,GetParamGlobal()->DotPerLine	,P->GetDotPerLine());
        for(int y=0;y<MinY;y++){
            BYTE    *p=L->GetMasterBuff().GetY(y);
            for(int x=0;x<MinX;x++,p++){
				QRgb  C=qimg.pixel(x,y);
				if(r==0){
					*p=qRed(C);
				}
				else if(r==1){
					*p=qGreen(C);
				}
				else if(r==2){
					*p=qBlue(C);
                }
            }
        }
	}
    return(true);
}
bool    LayersBase::SaveBitmapFromMaster(int page ,QIODevice *f)
{
	DataInPage	*P=GetPageData(page);
	QImage	qimg(P->GetDotPerLine(),P->GetMaxLines(),QImage::Format_RGB32);
	if(GetLayerNumb(page)==1){
		DataInLayer *L=P->GetLayerData(0);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p=L->GetMasterBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p++){
				qimg.setPixel(x,y,qRgb (*p,*p,*p));
			}
		}
	}
	else
	if(GetLayerNumb(page)==2){
		DataInLayer *L1=P->GetLayerData(0);
		DataInLayer *L2=P->GetLayerData(1);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p1=L1->GetMasterBuff().GetY(y);
			BYTE    *p2=L2->GetMasterBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p1++,p2++){
				qimg.setPixel(x,y,qRgb (*p1,*p2,*p2));
			}
		}
	}
	else
	if(GetLayerNumb(page)>=3){
		DataInLayer *L1=P->GetLayerData(0);
		DataInLayer *L2=P->GetLayerData(1);
		DataInLayer *L3=P->GetLayerData(1);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p1=L1->GetMasterBuff().GetY(y);
			BYTE    *p2=L2->GetMasterBuff().GetY(y);
			BYTE    *p3=L3->GetMasterBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p1++,p2++,p3++){
				qimg.setPixel(x,y,qRgb (*p1,*p2,*p3));
			}
		}
	}

	qimg.save(f,"BMP");
    return(true);
}
bool    LayersBase::LoadBitmapToTarget(int page ,QIODevice *f)
{
	QImageReader L(f);
	QImage	qimg=L.read();
    int XLen=qimg.width();
    int YLen=qimg.height();
	DataInPage	*P=GetPageData(page);
	int	MinX=min(XLen,GetParamGlobal()->DotPerLine,P->GetDotPerLine());
	int	MinY=min(YLen,GetParamGlobal()->MaxLines  ,P->GetMaxLines());
    for(int r=0;r<GetLayerNumb(page);r++){
        DataInLayer *L=P->GetLayerData(r);
        for(int		y=0;y<MinY;y++){
            BYTE    *p=L->GetTargetBuff().GetY(y);
            for(int x=0;x<MinX;x++,p++){
				QRgb  C=qimg.pixel(x,y);
				if(r==0){
					*p=qRed(C);
				}
				else if(r==1){
					*p=qGreen(C);
				}
				else if(r==2){
					*p=qBlue(C);
                }
            }
        }
	}
    return(true);
}
bool    LayersBase::SaveBitmapFromTarget(int page ,QIODevice *f)
{
	DataInPage	*P=GetPageData(page);
	QImage	qimg(P->GetDotPerLine(),P->GetMaxLines(),QImage::Format_RGB32);
	if(GetLayerNumb(page)==1){
		DataInLayer *L=P->GetLayerData(0);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p=L->GetTargetBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p++){
				qimg.setPixel(x,y,qRgb (*p,*p,*p));
			}
		}
	}
	else
	if(GetLayerNumb(page)==2){
		DataInLayer *L1=P->GetLayerData(0);
		DataInLayer *L2=P->GetLayerData(1);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p1=L1->GetTargetBuff().GetY(y);
			BYTE    *p2=L2->GetTargetBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p1++,p2++){
				qimg.setPixel(x,y,qRgb (*p1,*p2,*p2));
			}
		}
	}
	else
	if(GetLayerNumb(page)>=3){
		DataInLayer *L1=P->GetLayerData(0);
		DataInLayer *L2=P->GetLayerData(1);
		DataInLayer *L3=P->GetLayerData(1);
		for(int y=0;y<P->GetMaxLines();y++){
			BYTE    *p1=L1->GetTargetBuff().GetY(y);
			BYTE    *p2=L2->GetTargetBuff().GetY(y);
			BYTE    *p3=L3->GetTargetBuff().GetY(y);
			for(int x=0;x<P->GetDotPerLine();x++,p1++,p2++,p3++){
				qimg.setPixel(x,y,qRgb (*p1,*p2,*p3));
			}
		}
	}
	qimg.save(f,"BMP");
    return(true);
}

bool	LayersBase::LoadPIX(QIODevice &RFile ,ImageBuffer ***Buff,int PageCount ,int LayerCount)
//	*Buff[Layer][Page]
{
	if(RFile.isOpen()==false){
		if(RFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
	}

	int32	Ver;
	if(::Load(&RFile,Ver)==false){
		return false;
	}
	int32	iDotPerLine;
	int32	iMaxLines;
	int32	iPageNumb;
	int32	iLayerNumb;
	int32	iYCountBase;
	if(::Load(&RFile,iPageNumb)==false){
		return false;
	}
	if(::Load(&RFile,iLayerNumb)==false){
		return false;
	}
	if(::Load(&RFile,iDotPerLine)==false){
		return false;
	}
	if(::Load(&RFile,iMaxLines)==false){
		return false;
	}
	if(::Load(&RFile,iYCountBase)==false){
		return false;
	}

	BYTE	*databuff=new BYTE[iYCountBase*iDotPerLine];
	for(int page=0;(page<PageCount) && (page<iPageNumb);page++){
		int	YCount=iYCountBase;
		int	TopY;
		int	XLen=min(Buff[page][0]->GetWidth(),iDotPerLine);
		for(TopY=0;(TopY<iMaxLines) && (TopY<Buff[page][0]->GetHeight());TopY+=YCount){
			if(TopY+YCount>iMaxLines){
				YCount=iMaxLines-TopY;
			}
			if(TopY+YCount>Buff[page][0]->GetHeight()){
				YCount=Buff[page][0]->GetHeight()-TopY;
			}
			int	Layer;
			for(Layer=0;(Layer<LayerCount) && (Layer<iLayerNumb);Layer++){
				if(RFile.read((char *)databuff,YCount*iDotPerLine)!=(YCount*iDotPerLine)){
					delete	[]databuff;
					return false;
				}
				BYTE	*fp=databuff;
				for(int y=TopY;y<TopY+YCount;y++){
					if((y<iMaxLines) && (y<Buff[page][Layer]->GetHeight())){
						memcpy(Buff[page][Layer]->GetY(y),fp,XLen);
					}
					fp+=iDotPerLine;
				}
			}
			if(Layer<iLayerNumb){
				for(;Layer<iLayerNumb;Layer++){
					if(RFile.read((char *)databuff,YCount*iDotPerLine)!=(YCount*iDotPerLine)){
						delete	[]databuff;
						return false;
					}
				}
			}
		}
		if(TopY<iMaxLines){
			for(;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
				int	Layer;
				for(Layer=0;Layer<iLayerNumb;Layer++){
					if(RFile.read((char *)databuff,YCount*iDotPerLine)!=(YCount*iDotPerLine)){
						delete	[]databuff;
						return false;
					}
				}
			}			
		}
	}
	delete	[]databuff;
	return true;
}

bool	LayersBase::LoadPIXInfo(QIODevice &RFile
								,int32	&Ver
								,int32	&iDotPerLine
								,int32	&iMaxLines
								,int32	&iPageNumb
								,int32	&iLayerNumb
								,int32	&iYCountBase)
{
	if(RFile.isOpen()==false){
		if(RFile.open(QIODevice::ReadOnly)==false){
			return false;
		}
	}
	int64	SPoint=RFile.pos();

	if(::Load(&RFile,Ver)==false){
		return false;
	}
	if(::Load(&RFile,iPageNumb)==false){
		return false;
	}
	if(::Load(&RFile,iLayerNumb)==false){
		return false;
	}
	if(::Load(&RFile,iDotPerLine)==false){
		return false;
	}
	if(::Load(&RFile,iMaxLines)==false){
		return false;
	}
	if(::Load(&RFile,iYCountBase)==false){
		return false;
	}

	RFile.seek(SPoint);
	return true;
}

bool	LayersBase::MakeImageNGCircle(QImage *tNGData ,QPainter *tPntFromNGData
					 ,int dtype //DisplayImage::DisplayType
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,bool RedCircleMode
					 ,bool ShowNGMarkInTarget
					 ,bool &RetNGData)
{
	RetNGData=false;
	if(RedCircleMode==true
	&& (((DisplayImage::DisplayType)dtype)==DisplayImage::__Target
	 || ((DisplayImage::DisplayType)dtype)==DisplayImage::__DelayedView)
	&& ShowNGMarkInTarget==true){
		ParamGlobal	*ParamG=GetParamGlobal();

		if(ZoomRate>0.3 || ParamG->ShowToBindNGForReviewArea==false){
			ResultInspection	*DRes=GetCurrentResultForDraw();
			if(DRes!=NULL){
				for(ResultBaseForAlgorithmRoot *r=DRes->GetResultBaseDimFirst();r!=NULL;r=r->GetNext()){
					AlgorithmBase	*L=r->GetAlgorithm();

					RetNGData=true;

					const	QColor	NoCurrentPhaseColor=Qt::green;
					tPntFromNGData->setBrush(NoCurrentPhaseColor);
					QColor	tNGCircleColor	=ParamG->NGCircleColor;
					ParamG->NGCircleColor=NoCurrentPhaseColor;
					bool	tDrawBlueNGMark	=ParamG->DrawBlueNGMark;
					ParamG->DrawBlueNGMark=false;
					for(int phase=0;phase<GetPhaseNumb();phase++){
						if(phase==GetCurrentPhase())
							continue;
						ResultInPageRoot *R=r->GetPageDataPhase(phase)->GetPageData(localPage);
						L->GetPageDataPhase(phase)->GetPageData(localPage)->DrawResult(R
																					,*tNGData 
																					,*tPntFromNGData
																					,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate);
					}
					ParamG->NGCircleColor	=tNGCircleColor;
					ParamG->DrawBlueNGMark=tDrawBlueNGMark;

					RetNGData=false;
					tPntFromNGData->setBrush(Qt::red);
					int	phase=GetCurrentPhase();
					ResultInPageRoot *R=r->GetPageDataPhase(phase)->GetPageData(localPage);
					L->GetPageDataPhase(phase)->GetPageData(localPage)->DrawResult(R
																					,*tNGData 
																					,*tPntFromNGData
																					,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate);
					
					RetNGData=true;
				}
			}
		}
		else{
			ResultInspection	*DRes=GetCurrentResultForDraw();
			if(DRes!=NULL){
				NGImageContainerInPhase	*Ph=DRes->GetNGImageInPhase(GetCurrentPhase());
				if(Ph!=NULL){
					QPen	dpen(QColor(ParamG->NGCircleColor),(ParamG->NGMarkRadius+1)/2);
					tPntFromNGData->setPen(dpen);
					int	movx=MovX-Gx1/ZoomRate;
					int	movy=MovY-Gy1/ZoomRate;
					NGImageContainerInPage	*Pg=Ph->GetNGImageInPage(localPage);
					if(Pg!=NULL){
						for(ErrorGroup	*e=Pg->GetErrorGroupDataFirst();e!=NULL;e=e->GetNext()){
							int	x1,y1,x2,y2;
							e->GetXY(x1,y1,x2,y2);
							int	w=(x2-x1)*ZoomRate;
							int	h=(y2-y1)*ZoomRate;
							if(w<5)
								w=5;
							if(h<5)
								h=5;
							int	X1=(x1+movx)*ZoomRate;
							int	Y1=(y1+movy)*ZoomRate;
							tPntFromNGData->drawEllipse(X1,Y1,w,h);
							RetNGData=true;
						}
					}
				}
			}
		}

		ShadeMakeImageNGCircle(tNGData ,tPntFromNGData
					 ,dtype 
					 ,Gx1,Gy1 ,Gx2,Gy2
					 ,MovX,MovY, ZoomRate
					 ,localPage
					 ,RedCircleMode
					 ,ShowNGMarkInTarget
					 ,RetNGData);
	}
	return true;
}
