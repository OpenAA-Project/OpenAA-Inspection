/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Filter\FilterRemoveNoiseLine\FilterRemoveNoiseLine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "FilterRemoveNoiseLine.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "SettingDialog.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="RemoveNoiseLine";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Remove noise line";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterRemoveNoiseLine(base);
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
	FilterRemoveNoiseLine	*v=(FilterRemoveNoiseLine *)handle;
	SettingDialog	D(handle->GetLayersBase(),v,parent);
	D.exec();
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterRemoveNoiseLine::FilterRemoveNoiseLine(LayersBase *base)
:FilterClassBase(base)
{	
	NoiseLineH		=true;
	NoiseLineWidth	=2;
	ThresholdL		=30;
	ThresholdH		=200;
}
FilterRemoveNoiseLine::~FilterRemoveNoiseLine(void)
{
}
	
bool	FilterRemoveNoiseLine::Initial(void)
{
	return true;
}

bool	FilterRemoveNoiseLine::Release(void)
{
	return true;
}

bool	FilterRemoveNoiseLine::Save(QIODevice *f)
{
	if(::Save(f,NoiseLineH)==false)
		return false;
	if(::Save(f,NoiseLineWidth)==false)
		return false;
	if(::Save(f,ThresholdL)==false)
		return false;
	if(::Save(f,ThresholdH)==false)
		return false;
	return true;
}
bool	FilterRemoveNoiseLine::Load(QIODevice *f)
{
	if(::Load(f,NoiseLineH)==false)
		return false;
	if(::Load(f,NoiseLineWidth)==false)
		return false;
	if(::Load(f,ThresholdL)==false)
		return false;
	if(::Load(f,ThresholdH)==false)
		return false;
	return true;
}

bool	FilterRemoveNoiseLine::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	BYTE	*LineAttr=new BYTE[GetMaxLines()];	//1:L 2:M 3:H

	int	NoiseLineWidthHalf=NoiseLineWidth/2;
	int	N=GetMaxLines();
	int	XLen=GetDotPerLine();
	int	Xn=XLen & 0x7FFFFFF8;
	Xn-=8;
	for(int L=0;L<BufferDimCounts;L++){
		ImageBuffer *B=Buff[L];
		#pragma omp parallel
		{
			#pragma omp for		
			for(int y=0;y<N;y++){
				BYTE	*d=B->GetY(y);
				int	NumbL=0;
				int	NumbM=0;
				int	NumbH=0;

				for(int x=0;x<Xn;x+=8){
					short	D=0;
					for(int i=0;i<8;i++){
						D+=d[x+i];
					}
					D>>=3;
					if(D<ThresholdL)
						NumbL++;
					else if(D>ThresholdH)
						NumbH++;
					else
						NumbM++;
				}
				if(NumbL>0 && NumbH==0 && NumbM==0){
					LineAttr[y]=1;
				}
				else if(NumbH>0 && NumbL==0 && NumbM==0){
					LineAttr[y]=3;
				}
				else
					LineAttr[y]=2;
			}
		}
		for(int y=1;y<N-NoiseLineWidth-1;y++){
			for(int i=0;i<NoiseLineWidth;i++){
				if(LineAttr[y+i]!=1){
					goto	NextP1;
				}
			}
			if(LineAttr[y-1]==2 && LineAttr[y+NoiseLineWidth]==2){
				for(int i=0;i<NoiseLineWidthHalf;i++){
					memcpy(B->GetY(y+i),B->GetY(y-1),XLen);
					LineAttr[y+i]=LineAttr[y-1];
				}
				for(int i=NoiseLineWidthHalf;i<NoiseLineWidth;i++){
					memcpy(B->GetY(y+i),B->GetY(y+NoiseLineWidth),XLen);
					LineAttr[y+i]=LineAttr[y+NoiseLineWidth];
				}
			}
NextP1:;
			if(NoiseLineWidth>=2){
				if(LineAttr[y-1]==2 && LineAttr[y]==1 && LineAttr[y+1]==2){
					memcpy(B->GetY(y),B->GetY(y-1),XLen);
					LineAttr[y]=LineAttr[y-1];
				}
			}

			int	Width=0;
			for(int i=0;i<NoiseLineWidth;i++){
				if(LineAttr[y+i]!=3){
					break;
				}
				Width++;
			}
			if(Width>0){
				if((LineAttr[y-1]==1 || LineAttr[y-1]==2) && (LineAttr[y+Width]==1 || LineAttr[y+Width]==2)){
					for(int i=0;i<NoiseLineWidthHalf && i<Width;i++){
						memcpy(B->GetY(y+i),B->GetY(y-1),XLen);
						LineAttr[y+i]=LineAttr[y-1];
					}
					for(int i=NoiseLineWidthHalf;i<NoiseLineWidth && i<Width;i++){
						memcpy(B->GetY(y+i),B->GetY(y+Width),XLen);
						LineAttr[y+i]=LineAttr[y+Width];
					}
				}
			}
			if(NoiseLineWidth>=2){
				if(LineAttr[y-1]==1 && LineAttr[y]!=1 && LineAttr[y+1]==1){
					memcpy(B->GetY(y),B->GetY(y-1),XLen);
					LineAttr[y]=LineAttr[y-1];
				}
			}
		}
	}
	delete	[]LineAttr;

	return true;
}

