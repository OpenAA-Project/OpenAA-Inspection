/*
 * Copyright (C) 2024
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "FilterShrinkImage.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingShrinkForm.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="Shrink";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Shrink image";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterShrinkImage(base);
}

DEFFUNCEX	bool	DLL_Load(FilterClassBase *handle ,QIODevice &str)
//	Load filter attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return handle->Load(&str);
}

DEFFUNCEX	bool	DLL_Save(FilterClassBase *handle ,QIODevice &str)
//	Save filter attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}
DEFFUNCEX	bool	DLL_ShowSetting(FilterClassBase *handle, QWidget *parent)
//	This function shows dialog to set filter(handle) information
//	if dialog can't be shown, it returns false
{
	FilterShrinkImage	*H=(FilterShrinkImage *)handle;
	SettingShrinkForm	D(handle->GetLayersBase(),H->ShrinkRate,H->ShrinkMethod,parent);
	if(D.exec()==(int)true){
		H->ShrinkRate	=D.ShrinkRate;
		H->ShrinkMethod	=D.ShrinkMethod;
	}
	return true;
}
DEFFUNCEX	bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterShrinkImage::FilterShrinkImage(LayersBase *base)
:FilterClassBase(base)
{	
	ShrinkRate	=50;
	ShrinkMethod=0;
	IndexTable	=NULL;
	AllocSize	=0;
}

bool	FilterShrinkImage::Save(QIODevice *f)
{
	if(::Save(f,ShrinkRate)==false)
		return false;
	if(::Save(f,ShrinkMethod)==false)
		return false;
	return true;
}
bool	FilterShrinkImage::Load(QIODevice *f)
{
	if(::Load(f,ShrinkRate)==false)
		return false;
	if(::Load(f,ShrinkMethod)==false)
		return false;

	Initial();
	return true;
}

bool	FilterShrinkImage::Initial(void)
{
	if(IndexTable==NULL || AllocSize!=max(GetDotPerLine(),GetMaxLines())){
		if(IndexTable!=NULL){
			delete	[]IndexTable;
		}
		AllocSize=max(GetDotPerLine(),GetMaxLines());
		IndexTable=new int[AllocSize];
	}
	int	s=0;
	int	d=0;
	while(s<AllocSize){
		IndexTable[d]=s*100/ShrinkRate;
		d++;
		s++;
	}
	return true;
}

bool	FilterShrinkImage::Release(void)
{
	if(IndexTable!=NULL){
		delete	[]IndexTable;
		IndexTable=NULL;
	}
	IndexTable	=NULL;
	AllocSize	=0;
	return true;
}

bool	FilterShrinkImage::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	bool	Ret;
	switch(ShrinkMethod){
		case 0:
			Ret=ExecuteSimple(Buff,BufferDimCounts);
			break;
		case 1:
			Ret=ExecuteHighest(Buff,BufferDimCounts);
			break;
		case 2:
			Ret=ExecuteLowest(Buff,BufferDimCounts);
			break;
		case 3:
			Ret=ExecuteAverage(Buff,BufferDimCounts);
			break;
		default:
			Ret=false;
	}
	return Ret;
}

bool	FilterShrinkImage::ExecuteSimple(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	DestXLen=GetDotPerLine()*ShrinkRate/100;
	int	DestYLen=GetMaxLines()  *ShrinkRate/100;

	for(int i=0;i<BufferDimCounts;i++){
		int	y;
		for(y=0;y<DestYLen;y++){
			int	Y=IndexTable[y];
			BYTE	*s=Buff[i]->GetY(Y);
			BYTE	*d=Buff[i]->GetY(y);
			int	x=0;
			for(x=0;x<DestXLen;x++){
				int	X=IndexTable[x];
				d[x]=s[X];
			}
			memset(&d[x],0,GetDotPerLine()-x);
		}
		for(;y<GetMaxLines();y++){
			BYTE	*d=Buff[i]->GetY(y);
			memset(d,0,GetDotPerLine());
		}
	}
	return true;
}

bool	FilterShrinkImage::ExecuteHighest(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	DestXLen=GetDotPerLine()*ShrinkRate/100;
	int	DestYLen=GetMaxLines()  *ShrinkRate/100;

	for(int i=0;i<BufferDimCounts;i++){
		int	y;
		for(y=0;y<DestYLen;y++){
			int	Y1=IndexTable[y];
			int	Y2=IndexTable[y+1];
			BYTE	*d=Buff[i]->GetY(y);
			int	x;
			for(x=0;x<DestXLen;x++){
				int	X1=IndexTable[x];
				int	X2=IndexTable[x+1];
				int	D=0;
				for(int sY=Y1;sY<Y2;sY++){
					BYTE	*s=Buff[i]->GetY(sY);
					for(int sx=X1;sx<X2;sx++){
						if(D<s[sx]){
							D=s[sx];
						}
					}
				}
				d[x]=D;
			}
			memset(&d[x],0,GetDotPerLine()-x);
		}
		for(;y<GetMaxLines();y++){
			BYTE	*d=Buff[i]->GetY(y);
			memset(d,0,GetDotPerLine());
		}
	}
	return true;
}

bool	FilterShrinkImage::ExecuteLowest(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	DestXLen=GetDotPerLine()*ShrinkRate/100;
	int	DestYLen=GetMaxLines()  *ShrinkRate/100;

	for(int i=0;i<BufferDimCounts;i++){
		int	y;
		for(y=0;y<DestYLen;y++){
			int	Y1=IndexTable[y];
			int	Y2=IndexTable[y+1];
			BYTE	*d=Buff[i]->GetY(y);
			int	x;
			for(x=0;x<DestXLen;x++){
				int	X1=IndexTable[x];
				int	X2=IndexTable[x+1];
				int	D=255;
				for(int sY=Y1;sY<Y2;sY++){
					BYTE	*s=Buff[i]->GetY(sY);
					for(int sx=X1;sx<X2;sx++){
						if(D>s[sx]){
							D=s[sx];
						}
					}
				}
				d[x]=D;
			}
			memset(&d[x],0,GetDotPerLine()-x);
		}
		for(;y<GetMaxLines();y++){
			BYTE	*d=Buff[i]->GetY(y);
			memset(d,0,GetDotPerLine());
		}
	}
	return true;
}

bool	FilterShrinkImage::ExecuteAverage(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	DestXLen=GetDotPerLine()*ShrinkRate/100;
	int	DestYLen=GetMaxLines()  *ShrinkRate/100;

	for(int i=0;i<BufferDimCounts;i++){
		int	y;
		for(y=0;y<DestYLen;y++){
			int	Y1=IndexTable[y];
			int	Y2=IndexTable[y+1];
			BYTE	*d=Buff[i]->GetY(y);
			int	x;
			for(x=0;x<DestXLen;x++){
				int	X1=IndexTable[x];
				int	X2=IndexTable[x+1];
				int	D=0;
				int	N=0;
				for(int sY=Y1;sY<Y2;sY++){
					BYTE	*s=Buff[i]->GetY(sY);
					for(int sx=X1;sx<X2;sx++){
						D+=s[sx];
						N++;
					}
				}
				d[x]=D/N;
			}
			memset(&d[x],0,GetDotPerLine()-x);
		}
		for(;y<GetMaxLines();y++){
			BYTE	*d=Buff[i]->GetY(y);
			memset(d,0,GetDotPerLine());
		}
	}
	return true;
}
