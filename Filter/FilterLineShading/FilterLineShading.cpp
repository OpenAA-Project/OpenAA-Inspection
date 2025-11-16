/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterLineShading\FilterLineShading.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterLineShading.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingDialog.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "XPointer.h"
#include "XGeneralFunc.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="LineShading";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shading for line";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterLineShading(base);
}

bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterLineShading	*H=(FilterLineShading *)handle;
	SettingDialog	D(H->GetLayersBase(),H,parent);
	
	if(D.exec()==(int)true){
	}
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterLineShading::FilterLineShading(LayersBase *base)
:FilterClassBase(base)
{	
	MultiplePerDot=NULL;
	LayerNumb	=0;
	XLen		=0;
	YLen		=0;
	FValue		=NULL;
	ImgMax		=NULL;
	ImgAvr		=NULL;
	MinX		=0;
	MaxX		=99999;
}

FilterLineShading::~FilterLineShading(void)
{
	Release();
}

bool	FilterLineShading::Save(QIODevice *f)
{
	if(::Save(f,XLen)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(::Save(f,LayerNumb)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,MinX)==false)
		return false;
	if(::Save(f,MaxX)==false)
		return false;

	bool	EnableMultiplePerDot=(MultiplePerDot!=NULL)?true:false;
	if(::Save(f,EnableMultiplePerDot)==false)
		return false;

	if(EnableMultiplePerDot==true){
		for(int Layer=0;Layer<LayerNumb;Layer++){
			if(f->write((const char *)MultiplePerDot[Layer],XLen*MaxBrightness)!=XLen*MaxBrightness){
				return false;
			}
		}
		if(f->write((const char *)FValue,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
			return false;
		}
		if(f->write((const char *)ImgMax,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
			return false;
		}
		if(f->write((const char *)ImgAvr,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
			return false;
		}
	}
	return true;
}
bool	FilterLineShading::Load(QIODevice *f)
{
	Release();

	if(::Load(f,XLen)==false)
		return false;
	if(::Load(f,YLen)==false)
		return false;
	if(::Load(f,LayerNumb)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,MinX)==false)
		return false;
	if(::Load(f,MaxX)==false)
		return false;

	bool	EnableMultiplePerDot;
	if(::Load(f,EnableMultiplePerDot)==false)
		return false;

	if(EnableMultiplePerDot==true){
		if(XLen!=0 && LayerNumb!=0){
			MultiplePerDot=new BYTE*[LayerNumb];
			for(int Layer=0;Layer<LayerNumb;Layer++){
				MultiplePerDot[Layer]=new BYTE[XLen*MaxBrightness];
			}
			FValue		=new double[LayerNumb];
			ImgMax		=new double[LayerNumb];
			ImgAvr		=new double[LayerNumb];

			for(int Layer=0;Layer<LayerNumb;Layer++){
				if(f->read((char *)MultiplePerDot[Layer],XLen*MaxBrightness)!=XLen*MaxBrightness){
					return false;
				}
			}
			if(f->read((char *)FValue,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
				return false;
			}
			if(f->read((char *)ImgMax,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
				return false;
			}
			if(f->read((char *)ImgAvr,LayerNumb*sizeof(double))!=LayerNumb*sizeof(double)){
				return false;
			}
		}
	}
	else{
		Release();
	}

	return true;
}

bool	FilterLineShading::Initial(void)
{
	if(MultiplePerDot==NULL){
		LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();

		MultiplePerDot=new BYTE*[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			MultiplePerDot[Layer]=new BYTE[XLen*MaxBrightness];
			for(int x=0;x<XLen;x++){
				for(int c=0;c<MaxBrightness;c++){
					(MultiplePerDot[Layer])[x*256+c]=c;
				}
			}
		}
		FValue		=new double[LayerNumb];
		ImgMax		=new double[LayerNumb];
		ImgAvr		=new double[LayerNumb];
	}
	return true;
}

bool	FilterLineShading::Release(void)
{
	if(MultiplePerDot!=NULL){
		for(int Layer=0;Layer<LayerNumb;Layer++){
			delete	[]MultiplePerDot[Layer];
		}
		delete	[]MultiplePerDot;
	}
	MultiplePerDot=NULL;

	delete	FValue;
	delete	ImgMax;
	delete	ImgAvr;

	LayerNumb	=0;
	XLen		=0;
	YLen		=0;
	FValue		=NULL;
	ImgMax		=NULL;
	ImgAvr		=NULL;
	return true;
}
bool	FilterLineShading::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(XLen==NewDotPerLine)
		return;
	return FilterClassBase::ReallocXYPixels(NewDotPerLine ,NewMaxLines);
}

bool	FilterLineShading::Reallocate(int newLayerNumb)
{
	if(LayerNumb==newLayerNumb)
		return false;
	return FilterClassBase::Reallocate(newLayerNumb);
}

bool	FilterLineShading::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	if(MultiplePerDot==NULL)
		return false;

	int	MinXLen=min(XLen,GetDotPerLine());
	//int	MinYLen=min(YLen,GetMaxLines());
	int	MinYLen=GetMaxLines();
	for(int L=0;L<LayerNumb && L<BufferDimCounts;L++){
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<MinYLen;y++){
				BYTE	*d=Buff[L]->GetY(y);
				BYTE	*m=MultiplePerDot[L];
				for(int x=0;x<MinXLen;x++){
					*d=m[(x<<8)+(*d)];
					d++;
				}
			}
		}
	}

	return true;
}
void	FilterLineShading::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdFilterLineShadingClear	*CmdFilterLineShadingClearVar=dynamic_cast<CmdFilterLineShadingClear *>(packet);
	if(CmdFilterLineShadingClearVar!=NULL){
		Release();
		LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		XLen	=GetDotPerLine();
		YLen	=GetMaxLines();

		MultiplePerDot=new BYTE*[LayerNumb];
		FValue		=new double[LayerNumb];
		ImgMax		=new double[LayerNumb];
		ImgAvr		=new double[LayerNumb];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			MultiplePerDot[Layer]=new BYTE[XLen*MaxBrightness];
			for(int x=0;x<XLen;x++){
				for(int c=0;c<MaxBrightness;c++){
					(MultiplePerDot[Layer])[x*256+c]=c;
				}
			}
			FValue[Layer]=0;
			ImgMax[Layer]=0;
			ImgAvr[Layer]=0;
		}
		return;
	}
	CmdFilterLineShadingRegist	*CmdFilterLineShadingRegistVar=dynamic_cast<CmdFilterLineShadingRegist *>(packet);
	if(CmdFilterLineShadingRegistVar!=NULL){
		DataInPage *Dp=GetPageData();
		if(Dp!=NULL){
			ImageBuffer *Images[3];
			int	n=Dp->GetTargetImages	(Images,3);
			MinX=CmdFilterLineShadingRegistVar->MinX;
			MaxX=CmdFilterLineShadingRegistVar->MaxX;
			FValue[0]=CmdFilterLineShadingRegistVar->FValue[0];
			FValue[1]=CmdFilterLineShadingRegistVar->FValue[1];
			FValue[2]=CmdFilterLineShadingRegistVar->FValue[2];
			Analize(Images ,n
					,CmdFilterLineShadingRegistVar->MinX
					,CmdFilterLineShadingRegistVar->ShadingArea.GetMinY()
					,CmdFilterLineShadingRegistVar->MaxX
					,CmdFilterLineShadingRegistVar->ShadingArea.GetMaxY()
					,CmdFilterLineShadingRegistVar->FValue);
		}
		return;
	}
}

void    FilterLineShading::Analize(ImageBuffer *Image[] ,int tLayerNumb
									,int StartX,int StartY,int EndX,int EndY
									,double _FValue[])
{
    int SXLen=GetDotPerLine();
    int SYLen=GetMaxLines  ();
	int     *BrightnessTable[3][256];

	int tMinX=StartX;
	int tMaxX=EndX;
	tMinX=max(tMinX,0);
	tMaxX=min(tMaxX,SXLen);

	if(StartY<0)
		StartY=0;
	if(EndY>SYLen)
		EndY=SYLen;
	for(int Layer=0;Layer<LayerNumb && Layer<tLayerNumb && Layer<3;Layer++){
		for(int c=0;c<256;c++){
			BrightnessTable[Layer][c]=new int[SXLen];
			memset(BrightnessTable[Layer][c],0,SXLen*sizeof(int));
		}
	}
	for(int Layer=0;Layer<LayerNumb && Layer<tLayerNumb && Layer<3;Layer++){
		for(int y=StartY;y<EndY;y++){
		    BYTE	*s=Image[Layer]->GetY(y);
		    for(int x=tMinX;x<tMaxX;x++){
				int	c=s[x];
				BrightnessTable[Layer][c][x]++;
			}
		}
	}

    for(int layer=0;layer<LayerNumb && layer<tLayerNumb && layer<3;layer++){
        double MaxC=0;
        double AvrC=0;
        int    Numb=0;
        int    MaxN=0;
        for(int x=tMinX;x<tMaxX;x++){
            for(int c=0;c<256;c++){
                if(BrightnessTable[layer][c][x]>MaxN){
                    MaxN=BrightnessTable[layer][c][x];
                    MaxC=c;
                }
                AvrC+=BrightnessTable[layer][c][x]*c;
                Numb+=BrightnessTable[layer][c][x];
            }
        }
        AvrC/=Numb;
		ImgMax[layer]=MaxC;
		ImgAvr[layer]=AvrC;
    }

     for(int Layer=0;Layer<LayerNumb && Layer<tLayerNumb && Layer<3;Layer++){
        for(int x=tMinX;x<tMaxX;x++){
            double  AvrC=0;
            int     Numb=0;
            for(int c=0;c<MaxBrightness;c++){
                AvrC+=BrightnessTable[Layer][c][x]*c;
                Numb+=BrightnessTable[Layer][c][x];
            }
            AvrC/=Numb;
            double  M=_FValue[Layer]/AvrC;
            for(int c=0;c<MaxBrightness;c++){
				int	cm=c*M;
                MultiplePerDot[Layer][x*256+c]=Saturation256(cm);
            }
        }
        for(int x=0;x<tMinX;x++){
            for(int c=0;c<MaxBrightness;c++){
                MultiplePerDot[Layer][x*256+c]=MultiplePerDot[Layer][tMinX*256+c];
            }
        }
        for(int x=tMaxX;x<SXLen;x++){
            for(int c=0;c<MaxBrightness;c++){
                MultiplePerDot[Layer][x*256+c]=MultiplePerDot[Layer][(tMaxX-1)*256+c];
            }
        }
	 }
	for(int Layer=0;Layer<LayerNumb && Layer<tLayerNumb && Layer<3;Layer++){
		for(int c=0;c<256;c++){
			delete	[]BrightnessTable[Layer][c];
		}
	}
	//MinX=tMinX;
	//MaxX=tMaxX;
	//for(int Layer=0;Layer<LayerNumb && Layer<tLayerNumb && Layer<3;Layer++){
	//	FValue[Layer]=_FValue[Layer];
	//}
}