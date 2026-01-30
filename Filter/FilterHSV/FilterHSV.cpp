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



#include "FilterHSV.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"

bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="HSV";
	return(true);
}

WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Convert to HSV";
}

FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterHSV(base);
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
	return true;
}
bool	DLL_ExecuteImage(FilterClassBase *handle ,ImageBuffer *Buff[],int BufferDimCounts)
//	Execute filtering image data
//	if process fails, it returns false
{
	return handle->Execute(Buff,BufferDimCounts);
}

//================================================================================================
FilterHSV::FilterHSV(LayersBase *base)
	:FilterClassBase(base)
{
	STable=NULL;
	HTable=NULL;
}
FilterHSV::~FilterHSV(void)
{
	Release();
}

bool	FilterHSV::Initial(void)
{
	Release();

	STable=new BYTE*[256];
	BYTE	*d=new BYTE[256*256];
	for(int i=0;i<256;i++){
		STable[i]=&d[i*256];
	}
	for(int V=0;V<256;V++){
		for(int X=0;X<256;X++){
			if(V==0){
				*(STable[V]+X)=0;
			}
			else{
				*(STable[V]+X)=(V-X)/V;
			}
		}
	}

	HTable=new float*[513];
	float	*e=new float[513*256];
	for(int i=0;i<512;i++){
		HTable[i]=&e[i*256];
	}
	for(int dV=0;dV<256;dV++){
		for(int dX=-256;dX<=256;dX++){
			if(dV==0){
				*(HTable[dX+256]+dV)=0;
			}
			else{
				*(HTable[dX+256]+dV)=42.66*dX/dV;
			}
		}
	}
	return true;
}
bool	FilterHSV::Release(void)
{
	if(STable!=NULL){
		delete	[]STable[0];
		delete	[]STable;
		STable=NULL;
	}
	if(HTable!=NULL){
		delete	[]HTable[0];
		delete	[]HTable;
		HTable=NULL;
	}
	return true;
}


bool	FilterHSV::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	YNumb=GetMaxLines();
	if(BufferDimCounts!=3){
		return true;
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*R=Buff[0]->GetY(y);
			BYTE	*G=Buff[1]->GetY(y);
			BYTE	*B=Buff[2]->GetY(y);
			for(int x=0;x<GetDotPerLine();x++){
				if(R[x]>=G[x] && R[x]>=B[x]){
					BYTE	V=R[x];
					BYTE	X=min(G[x],B[x]);
					BYTE	S;
					if(V==0){
						S=0;
					}
					else{
						S=*(STable[V]+X);
					}
					BYTE	H=*(HTable[256+G[x]-B[x]]+(V-X));	//42.66*(G[x]-B[x])/(V-X);

					R[x]=H;
					G[x]=S;
					B[x]=V;
				}
				else if(G[x]>=R[x] && G[x]>=B[x]){
					BYTE	V=G[x];
					BYTE	X=min(R[x],B[x]);
					BYTE	S;
					if(V==0){
						S=0;
					}
					else{
						S=*(STable[V]+X);
					}
					BYTE	H=85.33+*(HTable[256+B[x]-R[x]]+(V-X));
					R[x]=H;
					G[x]=S;
					B[x]=V;
				}
				else{
					BYTE	V=B[x];
					BYTE	X=min(R[x],G[x]);
					BYTE	S;
					if(V==0){
						S=0;
					}
					else{
						S=*(STable[V]+X);
					}
					BYTE	H=170.666+*(HTable[256+R[x]-G[x]]+(V-X));
					R[x]=H;
					G[x]=S;
					B[x]=V;
				}
			}
		}
	}
	return true;
}