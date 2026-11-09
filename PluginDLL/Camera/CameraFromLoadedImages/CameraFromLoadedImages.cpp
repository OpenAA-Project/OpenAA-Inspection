/*
 * Copyright (C) 2025
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

#include "CameraFromLoadedImages.h"
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include <QFileDialog>
#include <stdlib.h>
#include "XDataInLayer.h"
#include "LoadImageFilesForm.h"

CameraFromLoadedImages::CameraFromLoadedImages(LayersBase *Base)
	:CameraHandle(0,Base)
{
	Form=new LoadImageFilesForm(this);
	Form->show();
	RPoint=-1;

	Images=NULL;
	PageCount=0;
	Reallocate(GetPhaseNumb() , GetPageNumb() ,GetLayerNumb(0));
}

CameraFromLoadedImages::~CameraFromLoadedImages(void)
{
	Form->deleteLater();
	Form=NULL;
}

void    CameraFromLoadedImages::ShowSetting(void)
{
	Form->raise();
}

bool	CameraFromLoadedImages::Save(QIODevice *f)
{
	if(::Save(f,ImageFiles)==false)
		return false;
	return true;
}
bool	CameraFromLoadedImages::Load(QIODevice *f)
{
	if(::Load(f,ImageFiles)==false)
		return false;
	return true;
}

bool	CameraFromLoadedImages::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(PageCount!=newPageNumb){
		delete	[]Images;
		PageCount=newPageNumb;
		Images=new ImageBufferListContainer[PageCount];
	}

	for(int page=0;page<PageCount;page++){
		Images[page].Reallocate(newLayerNumb);
		Images[page].Set(0 ,GetDotPerLine(), GetMaxLines());
	}
	return true;
}

bool	CameraFromLoadedImages::LoadImages(const QStringList &List)
{
	for(int i=0;i<List.count() && i<PageCount;i++){
		QFile	File(List[i]);
		if(File.open(QIODevice::ReadOnly)==true){
			LoadPix(&File,i);
		}
	}
	return true;
}

bool	CameraFromLoadedImages::LoadPix(QIODevice *f,int N)
{
	int	iDotPerLine[100][100];
	int	iMaxLines[100][100];
	int	iLayerNumb[100][100];
	int	iYCountBase=100;
	int	iPageNumb[100];
	int	iPhaseNumb=1;
	int	SkipPage=0;

	int	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,iPhaseNumb)==false)
		return false;

	int	MaxCount=0;
	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		if(::Load(f,iPageNumb[phase])==false)
			return false;
		for(int page=0;page<iPageNumb[phase] && page<Ph->GetPageNumb();page++){
			DataInPage *Dp=Ph->GetPageData(page);
			if(::Load(f,iLayerNumb[phase][page])==false)
				return false;
			if(::Load(f,iDotPerLine[phase][page])==false)
				return false;
			if(::Load(f,iMaxLines[phase][page])==false)
				return false;

			int	ProcessCount=0;

			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<Dp->GetMaxLines() && TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page]){
					YCount=iMaxLines[phase][page]-TopY;
				}
				ProcessCount++;
			}
			if(TopY<iMaxLines[phase][page]){
				for(;TopY<iMaxLines[phase][page];TopY+=YCount){
					if(TopY+YCount>iMaxLines[phase][page]){
						YCount=iMaxLines[phase][page]-TopY;
					}
					ProcessCount++;
				}			
			}
			ProcessCount++;

			MaxCount=max(MaxCount,ProcessCount);
		}
	}

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<SkipPage && page<iPageNumb[phase];page++){
			DataInPage *Dp=Ph->GetPageData(page);
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page])
					YCount=iMaxLines[phase][page]-TopY;
				int	Layer;
				for(Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
					f->read(YCount*iDotPerLine[phase][page]);
				}
			}
		}

		for(int page=0;page<Ph->GetPageNumb() && page<iPageNumb[phase];page++){
			DataInPage *Dp=Ph->GetPageData(page);
			ImageBufferListContainer	*B=&Images[page];
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<Dp->GetMaxLines() && TopY<iMaxLines[phase][page];TopY+=YCount){
				if(TopY+YCount>iMaxLines[phase][page])
					YCount=iMaxLines[phase][page]-TopY;
				int	Layer;
				for(Layer=0;Layer<Dp->GetLayerNumb() && Layer<iLayerNumb[phase][page];Layer++){
					ImageBuffer	*BL=B->GetItem(Layer);

					QByteArray	Data=f->read(YCount*iDotPerLine[phase][page]);
					
					BYTE	*Src=(BYTE *)Data.data();
					int		SrcByte=Data.size();
					int	XLen=min(iDotPerLine[phase][page],BL->GetWidth());
					for(int y=TopY;y<TopY+YCount;y++){
						if(y<BL->GetHeight() && SrcByte>=XLen){
							memcpy(BL->GetY(y),Src,XLen);
							Src+=iDotPerLine[phase][page];
							SrcByte-=XLen;
						}
					}
				}
				if(Layer<iLayerNumb[phase][page]){
					for(;Layer<iLayerNumb[phase][page];Layer++){
						f->read(YCount*iDotPerLine[phase][page]);
					}
				}
			}
			if(TopY<iMaxLines[phase][page]){
				for(;TopY<iMaxLines[phase][page];TopY+=YCount){
					if(TopY+YCount>iMaxLines[phase][page])
						YCount=iMaxLines[phase][page]-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb[phase][page];Layer++){
						f->read(YCount*iDotPerLine[phase][page]);
					}
				}			
			}
		}
	}
	return true;
}
    
void    CameraFromLoadedImages::ResetStrategicNumber()
{
	GetLayersBase()->SetCurrentStrategicNumberInExe(0);
	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
	GetLayersBase()->SetCurrentStrategicNumber(0);
}
    
void    CameraFromLoadedImages::ResetScanPhaseNumber()
{
	GetLayersBase()->SetCurrentScanPhaseNumber(0);
}

//================================================================================

DEFFUNCEX	WORD	DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="Camera from Image Files";
	return(true);
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}

DEFFUNCEX	CameraHandle	*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	CameraFromLoadedImages	*I=new CameraFromLoadedImages(base);
	return(I);
}

DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	delete	((CameraFromLoadedImages *)handle);
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	((CameraFromLoadedImages *)handle)->Load(&str);
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	((CameraFromLoadedImages *)handle)->Save(&str);
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraFromLoadedImages	*p=((CameraFromLoadedImages *)handle);
	p->ShowSetting();
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle,CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

DEFFUNCEX	int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	CameraFromLoadedImages	*p=((CameraFromLoadedImages *)handle);
	if(p->RPoint<0){
		return 1;
	}
	return(0);
}

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}
DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraFromLoadedImages	*p=((CameraFromLoadedImages *)handle);
	ImageBufferListContainer	*B=&p->Images[p->RPoint];

	for(int L=0;L<BufferDimCounts && L<B->GetCount();L++){
		*Buff[L]=*B->GetItem(L);
	}
	p->RPoint++;
	if(p->RPoint>=p->PageCount){
		p->RPoint=-1;
	}

	return(true);
}