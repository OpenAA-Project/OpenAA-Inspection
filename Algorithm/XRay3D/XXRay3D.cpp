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


#include "XXRay3D.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplaySimPanel.h"
#include "XDisplayBitImage.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

//===========================================================================================

XRay3DInPage::XRay3DInPage(AlgorithmBase *parent)
	:AlgorithmInPagePITemplate<XRay3DItem,XRay3DBase>(parent)
{
	ImageDim=NULL;
	CountImageDim = 0;
	PointToDraw	=0;
}
XRay3DInPage::~XRay3DInPage(void)
{
	if(ImageDim!=NULL){
		delete ImageDim;
		ImageDim=NULL;
	}
	CountImageDim = 0;
}

void	XRay3DInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	int	W = pnt.width();
	int	H = pnt.height();
	double	Z = 1.0/ZoomRate;
	if(ImageDim!=NULL){
		ImageBufferListContainer	*S=&ImageDim[(int)PointToDraw];
		if(GetLayerNumb()==1){
			for(int y=0;y<H;y++){
				int	Y=y*Z-movy;
				if(0<=Y && Y<S->GetHeight()){
					QRgb *Line=(QRgb *)pnt.scanLine(y);
					ImageBufferList	*L0=S->GetFirst();
					BYTE	*sL = L0->GetY(Y);
					for(int x=0;x<W;x++){
						int	X = x*Z-movx;
						if(0<=X && X<L0->GetWidth()){
							BYTE *p = sL+X;
							Line[x] = qRgb(*p,*p,*p);
						}
						else{
							Line[x] = qRgb(0,0,0);
						}
					}
				}
				else{
					QRgb *Line=(QRgb *)pnt.scanLine(y);
					for(int x=0;x<W;x++){
						Line[x] = qRgb(0,0,0);
					}
				}
			}
		}
	}
}

void	XRay3DInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadImages *CmdLoadImagesVar = dynamic_cast<CmdLoadImages *>(packet);
	if(CmdLoadImagesVar!=NULL){
		if(ImageDim!=NULL){
			delete ImageDim;
			ImageDim=NULL;
		}
		CountImageDim = CmdLoadImagesVar->ImageFileNames.count();
		ImageDim = new ImageBufferListContainer[CountImageDim];
		for(int i=0;i<CountImageDim;i++){
			QImage Img(CmdLoadImagesVar->ImageFileNames[i]);
			if(Img.isNull()==false){
				ImageDim[i].FromImage(Img,GetLayerNumb());
			}
		}
		PointToDraw = 0;
		return;
	}
	CmdSetPointY *CmdSetPointYVar = dynamic_cast<CmdSetPointY *>(packet);
	if(CmdSetPointYVar!=NULL){
		PointToDraw = CmdSetPointYVar->PointToDraw;
		return;
	}
	CmdReqSmooth *CmdReqSmoothVar = dynamic_cast<CmdReqSmooth *>(packet);
	if(CmdReqSmoothVar!=NULL){
		if(ImageDim!=NULL){
			for(int i=0;i<CountImageDim;i++){
				ImageBufferListContainer	*S=&ImageDim[i];
				for(int layer=0;layer<GetLayerNumb();layer++){
					ImageBuffer	*L=S->GetItem(layer);
					ExeSmooth(L);
				}
			}
		}
		return;
	}
	CmdReqEmphasize *CmdReqEmphasizeVar = dynamic_cast<CmdReqEmphasize *>(packet);
	if(CmdReqEmphasizeVar!=NULL){
		if(ImageDim!=NULL){
			for(int i=0;i<CountImageDim;i++){
				ImageBufferListContainer	*S=&ImageDim[i];
				for(int layer=0;layer<GetLayerNumb();layer++){
					ImageBuffer	*L=S->GetItem(layer);
					ExeEmphasize(L);
				}
			}
		}
		return;
	}
	CmdMatchFile *CmdMatchFileVar = dynamic_cast<CmdMatchFile *>(packet);
	if(CmdMatchFileVar!=NULL){
		QImage Img(CmdMatchFileVar->FileName);
		ImageBufferListContainer LBuff;
		LBuff.FromImage(Img,GetLayerNumb());
		ImageBuffer *L0 = LBuff.GetFirst();
		double	RetX,RetY;
		double	MaxD=0;
		int		MaxLayer=0;
		for(int i=0;i<CountImageDim;i++){
			ImageBufferListContainer	*S=&ImageDim[i];
			ImageBuffer	*L=S->GetItem(0);
			int	X,Y;
			double	D=ExeMatch(*L,*L0,X,Y);
			if(D>MaxD){
				MaxD=D;
				RetX= X;
				RetY= Y;
				MaxLayer=i;
			}
		}
		CmdMatchFileVar->RetFileNo = MaxLayer;
		CmdMatchFileVar->RetX = RetX;
		CmdMatchFileVar->RetY = RetY;
		return;
	}
}

//===========================================================================================
XRay3DBase::XRay3DBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ModeParallelForPhase.ModeParallelExecuteProcessing=false;

	ColorNormal			=Qt::darkGreen;
	ColorSelected		=Qt::green;
	ColorActive			=Qt::red;
	Color0				=Qt::green;
	Color1				=Qt::yellow;
	Color2				=Qt::darkRed;
	Color3				=Qt::cyan;
	Color4				=Qt::magenta;
	Color5				=Qt::darkGreen;
	Color6				=Qt::darkYellow;
	Color7				=Qt::darkCyan;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"		,"Color for Area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"	,"Color for Selected Area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"		,"Color for Active Area");

	SetParam(&Color0			, /**/"Color"	,/**/"Color0"		,"Level Color 0");
	SetParam(&Color1			, /**/"Color"	,/**/"Color1"		,"Level Color 1");
	SetParam(&Color2			, /**/"Color"	,/**/"Color2"		,"Level Color 2");
	SetParam(&Color3			, /**/"Color"	,/**/"Color3"		,"Level Color 3");
	SetParam(&Color4			, /**/"Color"	,/**/"Color4"		,"Level Color 4");
	SetParam(&Color5			, /**/"Color"	,/**/"Color5"		,"Level Color 5");
	SetParam(&Color6			, /**/"Color"	,/**/"Color6"		,"Level Color 6");
	SetParam(&Color7			, /**/"Color"	,/**/"Color7"		,"Level Color 7");
}

AlgorithmDrawAttr	*XRay3DBase::CreateDrawAttr(void)
{
	return new XRay3DDrawAttr();
}

XRay3DInPage	*XRay3DBase::NewChild(AlgorithmBase *parent)
{	
	return(new XRay3DInPage(parent));
}
void	XRay3DBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCreateTempXRay3DItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempXRay3DItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new XRay3DItem();
		return;
	}
	CmdCreateByteArrayFromXRay3DItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromXRay3DItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
	}
	CmdLoadXRay3DItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadXRay3DItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
	}
}

bool	XRay3DBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==XRay3DHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==XRay3DReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*XRay3DBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==XRay3DReqThresholdReqCommand){
		return new XRay3DThresholdReq();
	}
	else if(Command==XRay3DReqThresholdSendCommand){
		XRay3DThresholdSend	*pSend=new XRay3DThresholdSend();
		if(reqData!=NULL){
			XRay3DThresholdReq	*req=(XRay3DThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}

	return NULL;
}
bool	XRay3DBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==XRay3DReqThresholdReqCommand){
		XRay3DThresholdReq	*p=(XRay3DThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==XRay3DReqThresholdSendCommand){
		XRay3DThresholdSend	*p=(XRay3DThresholdSend *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
	return false;
}
bool	XRay3DBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==XRay3DReqThresholdReqCommand){
		XRay3DThresholdReq	*p=(XRay3DThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==XRay3DReqThresholdSendCommand){
		XRay3DThresholdSend	*p=(XRay3DThresholdSend *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}

	return false;
}
bool	XRay3DBase::GeneralDataReply(int32 Command,void *data)
{
	 if(Command==XRay3DReqThresholdReqCommand){
		XRay3DThresholdReq	*p=(XRay3DThresholdReq *)data;
		return true;
	}
	else if(Command==XRay3DReqThresholdSendCommand){
		XRay3DThresholdSend	*p=(XRay3DThresholdSend *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}

	return false;
}