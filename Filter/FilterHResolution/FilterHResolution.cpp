/*
 * Copyright (C) 2023
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



#include "FilterHResolution.h"
#include "XFilterDLL.h"
#include "XMainSchemeMemory.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <omp.h>
#include "swap.h"
#include "SettingHResolutionDialog.h"

DEFFUNCEX	bool	DLL_GetName(QString &str)
//	return DLL-Name.
{
	str="FilterHResolution";
	return(true);
}

DEFFUNCEX	WORD	DLL_GetVersion(void)
//	return Filter DLL version
{
	return(1);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Extend resolution in horizontal direction";
}

DEFFUNCEX	FilterClassBase	*DLL_Initial(LayersBase *base)
//	Initialize Filter DLL. 
//		This function must create and open handle. 
//	return:		Filter handle(memory block)
//				if proocess fails, return 0
{
	return new FilterHResolution(base);
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

	SettingHResolutionDialog	D(handle->GetLayersBase(),((FilterHResolution *)handle)->Rate);
	if(D.exec()==(int)true){
		((FilterHResolution *)handle)->Rate	=D.Rate;
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
FilterHResolution::FilterHResolution(LayersBase *base)
:FilterClassBase(base)
{	
	Rate		=1;
	IndxRoot	=NULL;
	MultA		=NULL;
	MultB		=NULL;
}

FilterHResolution::~FilterHResolution(void)
{
	Release();
}

bool	FilterHResolution::Save(QIODevice *f)
{
	if(::Save(f,Rate)==false)
		return false;

	return true;
}
bool	FilterHResolution::Load(QIODevice *f)
{
	if(::Load(f,Rate)==false)
		return false;

	return true;
}

bool	FilterHResolution::Initial(void)
{
	if(IndxRoot!=NULL){
		delete	[]IndxRoot;
	}
	if(MultA!=NULL){
		delete	[]MultA;
	}
	if(MultB!=NULL){
		delete	[]MultB;
	}
	IndxRoot	=new int[GetDotPerLine()];
	MultA		=new int[GetDotPerLine()];
	MultB		=new int[GetDotPerLine()];

	for(int x=0;x<GetDotPerLine();x++){
		int	Mx=x*Rate;
		if(Mx>=GetDotPerLine()-2){
			Mx=GetDotPerLine()-2;
		}
		IndxRoot[x]=Mx;
		double	a=x*Rate-Mx;
		MultA[x]=(1.0-a)*256.0;
		MultB[x]=a*256.0;
	}


	return true;
}

bool	FilterHResolution::Release(void)
{
	if(IndxRoot!=NULL){
		delete	[]IndxRoot;
	}
	if(MultA!=NULL){
		delete	[]MultA;
	}
	if(MultB!=NULL){
		delete	[]MultB;
	}
	IndxRoot	=NULL;
	MultA		=NULL;
	MultB		=NULL;

	return true;
}

bool	FilterHResolution::Execute(ImageBuffer *Buff[],int BufferDimCounts)
{
	int	XN=GetDotPerLine();
	int	YN=GetMaxLines();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YN;y++){
			BYTE	TmpBuff[100000];
			for(int i=0;i<BufferDimCounts;i++){
				BYTE	*d=Buff[i]->GetY(y);
				memcpy(TmpBuff,d,XN);
				for(int x=0;x<XN-1;x++){
					int	k=IndxRoot[x];
					d[x]=((int)(TmpBuff[k]*MultA[x]+TmpBuff[k+1]*MultB[x]))>>8;
				}
			}
		}
	}

	return true;
}

void	FilterHResolution::TransmitDirectly(GUIDirectMessage *packet)
{
}