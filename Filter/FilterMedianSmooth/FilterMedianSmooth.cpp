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



#include "FilterMedianSmooth.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "SettingMedianForm.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="MedianSmooth";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Median smoother";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterMedianSmooth(base);
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
	FilterMedianSmooth	*H=(FilterMedianSmooth *)handle;
	SettingMedianForm	D(handle->GetLayersBase(),H->FilterDot,parent);
	if(D.exec()==(int)true){
		H->FilterDot	=D.FilterDot;
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
FilterMedianSmooth::FilterMedianSmooth(LayersBase *base)
:FilterClassBase(base)
{	
	TmpImage=NULL;
	AllocatedLayerCount=0;
	FilterDot	=50;
}

bool	FilterMedianSmooth::Save(QIODevice *f)
{
	if(::Save(f,FilterDot)==false)
		return false;
	return true;
}
bool	FilterMedianSmooth::Load(QIODevice *f)
{
	if(::Load(f,FilterDot)==false)
		return false;

	return true;
}

bool	FilterMedianSmooth::Initial(void)
{
	Release();
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	AllocatedLayerCount=GetLayerNumb(LayerNumb);
	TmpImage=new ImageBuffer*[AllocatedLayerCount];
	for(int i=0;i<AllocatedLayerCount;i++){
		TmpImage[i]=new ImageBuffer(0,GetDotPerLine(),GetMaxLines());
		TmpImage[i]->Memset(0);
	}
	return true;
}

bool	FilterMedianSmooth::Release(void)
{
	if(TmpImage!=NULL){
		for(int i=0;i<AllocatedLayerCount;i++){
			delete	TmpImage[i];
		}
		delete	[]TmpImage;
		TmpImage=NULL;
	}
	return true;
}

int	FuncDimSort(const void *a ,const void *b)
{
	int d=*((BYTE *)a) - *((BYTE *)b);
	return d;
}


bool	FilterMedianSmooth::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	FilterDot2=FilterDot/2;

	int	AreaDot=FilterDot*FilterDot;
	int	Abandon	=(int)(AreaDot*0.4);
	int	Adopt	=(int)(AreaDot*0.2);

	for(int i=0;i<BufferDimCounts;i++){
		int	YN=GetMaxLines()-FilterDot;
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YN;y++){
				int	Dy=y+FilterDot2;
				BYTE	*d=TmpImage[i]->GetY(Dy);
				int	XN=GetDotPerLine()-FilterDot;
				for(int x=0;x<XN;x++){
					int	Dx=x+FilterDot2;
					int	n=0;
					/*
					BYTE	Dim[2000];
					for(int sy=0;sy<FilterDot;sy++){
						BYTE	*s=Buff[i]->GetY(y+sy);
						for(int sx=0;sx<FilterDot;sx++){
							Dim[n]=s[x+sx];
							n++;
						}
					}
					QSort(Dim,n,1,FuncDimSort);
					int	D=0;
					for(int t=0;t<Adopt;t++){
						D+=Dim[t+Abandon];
					}
					*/
					short	Dim[2000];
					for(int sy=0;sy<FilterDot;sy++){
						BYTE	*s=Buff[i]->GetY(y+sy);
						for(int sx=0;sx<FilterDot;sx++){
							Dim[n]=s[x+sx];
							n++;
						}
					}
					for(int k=0;k<Abandon;k++){
						short	m=0;
						int		Index=0;
						for(int t=0;t<n;t++){
							if(Dim[t]>m){
								m=Dim[t];
								Index=t;
							}
						}
						Dim[Index]=-1;
					}
					int	D=0;
					for(int k=0;k<Adopt;k++){
						short	m=0;
						int		Index=0;
						for(int t=0;t<n;t++){
							if(Dim[t]>m){
								m=Dim[t];
								Index=t;
							}
						}
						D+=m;
						Dim[Index]=-1;
					}

					d[Dx]=D/Adopt;
				}
			}
		}
		*Buff[i]=*TmpImage[i];
	}
	return true;
}