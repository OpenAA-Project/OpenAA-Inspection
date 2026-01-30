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

#include "XDisplayImage3D.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XImageProcess.h"
#include "XDisplayImage3DPacket.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XPointer.h"
#include "XDataAlgorithmList.h"
#include <typeinfo>
#include "X3DCommon.h"
#include "XDataModelPageItem3D.h"

//#include "XGUI.h"
#include <omp.h>


//====================================================================================

GUICmdReqBmp3D::GUICmdReqBmp3D(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Data.RedCircleMode	=true;
	Data.ShowFixedPhase	=-1;
}

bool	GUICmdReqBmp3D::Save(QIODevice *f)
{
	if(ReqData3D.Save(f)==false)
		return false;
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(::Save(f,AlgoRoot)==false)	return false;
	if(::Save(f,AlgoName)==false)	return false;
	if(::Save(f,InstName)==false)	return false;
	if(::Save(f,DAttrArray)==false)	return false;

	return true;
}
bool	GUICmdReqBmp3D::Load(QIODevice *f)
{
	if(ReqData3D.Load(f)==false)
		return false;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(::Load(f,AlgoRoot)==false)	return false;
	if(::Load(f,AlgoName)==false)	return false;
	if(::Load(f,InstName)==false)	return false;
	if(::Load(f,DAttrArray)==false)	return false;

	return true;
}


void	GUICmdReqBmp3D::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBmp3D	*SendBack=GetSendBack(GUICmdSendBmp3D,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	QBuffer	DAttrBuff(&DAttrArray);
	DAttrBuff.open(QIODevice::ReadOnly);
	ModePoint->Load(&DAttrBuff);

	SendBack->MakeImage(ModePoint
						,AlgoRoot,AlgoName
						,ReqData3D
						,localPage
						,*GetLayersBase()
						,Data.RedCircleMode
						,Data.ShowFixedPhase);
	delete	ModePoint;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendBmp3D::GUICmdSendBmp3D(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData	=NULL;
	NGData	=NULL;
	PntFromIData=NULL;
	PntFromNGData=NULL;
}

GUICmdSendBmp3D::~GUICmdSendBmp3D(void)
{
	if(PntFromIData!=NULL){
		delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromNGData!=NULL){
		delete	PntFromNGData;
		PntFromNGData=NULL;
	}

	if(IData!=NULL){
		delete	IData;
		IData=NULL;
	}
	if(NGData!=NULL){
		delete	NGData;
		NGData=NULL;
	}
}

struct	GUICmdSendBmpData3D
{
	int32	W,H;
};


bool	GUICmdSendBmp3D::Load(QIODevice *f)
{
	struct	GUICmdSendBmpData3D	Data;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}

	if(IData==NULL){
		IData =new QImage(Data.W,Data.H,QImage::Format_ARGB32);
		NGData=new QImage(Data.W,Data.H,QImage::Format_ARGB32);

		if(PntFromIData!=NULL){
			delete	PntFromIData;
			PntFromIData=NULL;
		}
		if(PntFromNGData!=NULL){
			delete	PntFromNGData;
			PntFromNGData=NULL;
		}
	}
	else
	if(IData->width()!=Data.W || IData->height()!=Data.H){
		if(PntFromIData!=NULL){
			delete	PntFromIData;
		}
		if(PntFromNGData!=NULL){
			delete	PntFromNGData;
		}
		delete	IData;
		delete	NGData;

		IData =new QImage(Data.W,Data.H,QImage::Format_ARGB32);
		NGData=new QImage(Data.W,Data.H,QImage::Format_ARGB32);

		PntFromIData=NULL;
		PntFromNGData=NULL;
	}
	if(PntFromIData==NULL){
		PntFromIData=new QPainter(IData);
	}
	if(PntFromNGData==NULL){
		PntFromNGData=new QPainter(NGData);
	}
	int	W4=Data.W*4;
	for(int h=0;h<Data.H;h++){
		char	*s=(char *)IData->scanLine(h);
		if(f->read(s,W4)!=W4){
			return false;
		}
	}
	for(int h=0;h<Data.H;h++){
		char	*s=(char *)NGData->scanLine(h);
		if(f->read(s,W4)!=W4){
			return false;
		}
	}

	return true;
}
bool	GUICmdSendBmp3D::Save(QIODevice *f)
{
	struct	GUICmdSendBmpData3D	Data;
	Data.H=IData->height();
	Data.W=IData->width();

	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	int	W4=Data.W*4;
	for(int h=0;h<Data.H;h++){
		char	*s=(char *)IData->scanLine(h);
		if(f->write(s,W4)!=W4){
			return false;
		}
	}
	for(int h=0;h<Data.H;h++){
		char	*s=(char *)NGData->scanLine(h);
		if(f->write(s,W4)!=W4){
			return false;
		}
	}

	return true;
}

bool	GUICmdSendBmp3D::MakeImage(AlgorithmDrawAttr *ModePoint
								 ,const QString &AlgoRoot,const QString &AlgoName
								 , const Canvas3D &CInfo
								 ,int localPage
								 ,LayersBase &LocalLBase
								 ,bool RedCircleMode
								 ,int32 ShowFixedPhase)
{
	DataInLayer	*LayerBuff[1000];

	LocalLBase.LockRChangingDataStructure();

	AlgorithmBase	*L=LocalLBase.GetAlgorithmBase(AlgoRoot,AlgoName);
	if(L==NULL){
		return false;
	}
	if(ShowFixedPhase<0){
		for(int phase=0;phase<LocalLBase.GetPhaseNumb();phase++){
			AlgorithmInPageInOnePhase	*Ah=L->GetPageDataPhase(phase);
			AlgorithmInPage3DPI	*Ap=dynamic_cast<AlgorithmInPage3DPI *>(Ah->GetPageData(localPage));
			if(Ap!=NULL){
				Ap->GetColorForDraw(*IData,CInfo,ModePoint);
			}
		}
	}
	else{
		AlgorithmInPageInOnePhase	*Ah=L->GetPageDataPhase(ShowFixedPhase);
		if(Ah!=NULL){
			AlgorithmInPage3DPI	*Ap=dynamic_cast<AlgorithmInPage3DPI *>(Ah->GetPageData(localPage));
			if(Ap!=NULL){
				Ap->GetColorForDraw(*IData,CInfo,ModePoint);
			}
		}
	}

	LocalLBase.UnlockChangingDataStructure();
		
	return true;
}