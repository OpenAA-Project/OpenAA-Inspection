/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\XDisplayPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XImageProcess.h"
#include "XDisplayImagePacket.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XPointer.h"
#include "XDataAlgorithmList.h"
#include <typeinfo>

//#include "XGUI.h"
#include <omp.h>


//=======================================================================
GUICmdSyncDrawingMode::GUICmdSyncDrawingMode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSyncDrawingMode::Save(QIODevice *f)
{
	int32	N=(int32)DMode;
	if(::Save(f,N)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	if(::Save(f,localX)==false){
		return false;
	}
	if(::Save(f,localY)==false){
		return false;
	}
	return true;
}
bool	GUICmdSyncDrawingMode::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	DMode=(DisplayImage::__DrawingMode)N;
	if(::Load(f,InstName)==false){
		return false;
	}
	if(::Load(f,localX)==false){
		return false;
	}
	if(::Load(f,localY)==false){
		return false;
	}
	return true;
}

void	GUICmdSyncDrawingMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	A->SetDrawingMode(DMode);
	//if(DMode==DisplayImage::_PasteMove){
	//	int Gx ,Gy;
	//	A->ChangeDxy2Gxy(localX,localY,Gx ,Gy);
	//	A->SetMouseCursorPos(Gx,Gy);
	//}
	SendAck(localPage);
}

//=======================================================================
GUICmdReqPixelColor::GUICmdReqPixelColor(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	DType=dtype;
	MasterNo=0;
}

bool	GUICmdReqPixelColor::Save(QIODevice *f)
{
	if(f->write((const char *)&DType  ,sizeof(DType))!=sizeof(DType)){
		return false;
	}
	if(f->write((const char *)&LocalX,sizeof(LocalX))!=sizeof(LocalX)){
		return false;
	}
	if(f->write((const char *)&LocalY,sizeof(LocalY))!=sizeof(LocalY)){
		return false;
	}
	if(f->write((const char *)&MasterNo,sizeof(MasterNo))!=sizeof(MasterNo)){
		return false;
	}
	return true;
}
bool	GUICmdReqPixelColor::Load(QIODevice *f)
{
	if(f->read((char *)&DType  ,sizeof(DType))!=sizeof(DType)){
		return false;
	}
	if(f->read((char *)&LocalX,sizeof(LocalX))!=sizeof(LocalX)){
		return false;
	}
	if(f->read((char *)&LocalY,sizeof(LocalY))!=sizeof(LocalY)){
		return false;
	}
	if(f->read((char *)&MasterNo,sizeof(MasterNo))!=sizeof(MasterNo)){
		return false;
	}
	return true;
}


void	GUICmdReqPixelColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendPixelColor	*SendBack=GetSendBack(GUICmdSendPixelColor,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	if(P!=NULL){
		if(0<=LocalX && LocalX<P->GetDotPerLine()
			&& 0<=LocalY && LocalY<P->GetMaxLines()){
			if(P->GetLayerNumb()==1){
				ImageBuffer	*SBuff;
				if((DType&DisplayImage::__Master)!=0){
					SBuff=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					SBuff=&P->GetLayerData(0)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					SBuff=&P->GetLayerData(0)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					SBuff=&P->GetLayerData(0)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					SBuff=&P->GetLayerData(0)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff=&P->GetLayerData(0)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					SBuff=&P->GetLayerData(0)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					SBuff=&P->GetLayerData(0)->GetCamTargetBuff();
				}
				else{
					SBuff=NULL;
				}
				if(SBuff!=NULL && SBuff->IsNull()==false){
					if(LocalX<SBuff->GetWidth() && LocalY<SBuff->GetHeight()){
						if((DType&DisplayImage::__BitBuff)==0){
							int	c=SBuff->GetY(LocalY)[LocalX];
							SendBack->Col.setRed  (c);
							SendBack->Col.setGreen(c);
							SendBack->Col.setBlue (c);
						}
						else{
							if(GetBmpBitOnY(SBuff->GetY(LocalY),LocalX)==0){
								SendBack->Col.setRed  (0);
								SendBack->Col.setGreen(0);
								SendBack->Col.setBlue (0);
							}
							else{
								SendBack->Col.setRed  (255);
								SendBack->Col.setGreen(255);
								SendBack->Col.setBlue (255);
							}
						}
					}
				}
			}
			else if(P->GetLayerNumb()==2){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				if((DType&DisplayImage::__Master)!=0){
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						int	c0=SBuff0->GetY(LocalY)[LocalX];
						int	c1=SBuff1->GetY(LocalY)[LocalX];
						SendBack->Col.setRed  (c0);
						SendBack->Col.setGreen(c1);
						SendBack->Col.setBlue (c1);
					}
					else{
						int	c0=0;
						int	c1=0;
						if(GetBmpBitOnY(SBuff0->GetY(LocalY),LocalX)!=0)
							c0=255;
						if(GetBmpBitOnY(SBuff1->GetY(LocalY),LocalX)!=0)
							c1=255;

						SendBack->Col.setRed  (c0);
						SendBack->Col.setGreen(c1);
						SendBack->Col.setBlue (c1);
					}
				}
			}
			else if(P->GetLayerNumb()>=3){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				ImageBuffer	*SBuff2;
				if((DType&DisplayImage::__Master)!=0){
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
					SBuff2=&P->GetLayerData(2)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
					SBuff2=&P->GetLayerData(2)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
					SBuff2=&P->GetLayerData(2)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
					SBuff2=&P->GetLayerData(2)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
					SBuff2=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& SBuff2!=NULL && SBuff2->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						int	c0=SBuff0->GetY(LocalY)[LocalX];
						int	c1=SBuff1->GetY(LocalY)[LocalX];
						int	c2=SBuff2->GetY(LocalY)[LocalX];
						SendBack->Col.setRed  (c0);
						SendBack->Col.setGreen(c1);
						SendBack->Col.setBlue (c2);
					}
					else{
						int	c0=0;
						int	c1=0;
						int	c2=0;
						if(GetBmpBitOnY(SBuff0->GetY(LocalY),LocalX)!=0)
							c0=255;
						if(GetBmpBitOnY(SBuff1->GetY(LocalY),LocalX)!=0)
							c1=255;
						if(GetBmpBitOnY(SBuff2->GetY(LocalY),LocalX)!=0)
							c2=255;

						SendBack->Col.setRed  (c0);
						SendBack->Col.setGreen(c1);
						SendBack->Col.setBlue (c2);
					}
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendPixelColor::GUICmdSendPixelColor(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

GUICmdSendPixelColor::~GUICmdSendPixelColor(void)
{
}

bool	GUICmdSendPixelColor::Load(QIODevice *f)
{
	QString	c;
	if(::Load(f,c)==false){
		return false;
	}
	Col=::QString2QColor(c);
	return true;
}
bool	GUICmdSendPixelColor::Save(QIODevice *f)
{
	QString	c=::QColor2QString(Col);
	if(::Save(f,c)==false){
		return false;
	}
	return true;
}

void	GUICmdSendPixelColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================
GUICmdDrawColor::GUICmdDrawColor(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	DType=dtype;
	MasterNo=0;
}

bool	GUICmdDrawColor::Save(QIODevice *f)
{
	f->write((const char *)&DType  ,sizeof(DType));
	QString	c=::QColor2QString(Col);
	if(::Save(f,c)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	return true;
}
bool	GUICmdDrawColor::Load(QIODevice *f)
{
	f->read((char *)&DType  ,sizeof(DType));
	QString	c;
	if(::Load(f,c)==false){
		return false;
	}
	Col=::QString2QColor(c);
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	return true;
}


void	GUICmdDrawColor::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	QRgb	Drgb=Col.rgb();
	int		m=(int)Drgb;
	for(int layer=min(P->GetLayerNumb(),3)-1;layer>=0;layer--){
		DataInLayer	*L=P->GetLayerData(layer);

		ImageBuffer	*DBuff=NULL;
		if((DType&DisplayImage::__Master)!=0){
			DBuff=&L->GetMasterBuff(MasterNo);
		}
		else if((DType&DisplayImage::__BackGround)!=0){
			DBuff=&L->GetBackGroundBuff();
		}
		else if((DType&DisplayImage::__Target)!=0){
			DBuff=&L->GetTargetBuff();
		}
		else if((DType&DisplayImage::__TargetTR)!=0){
			DBuff=&L->GetTargetTRBuff();
		}
		else if((DType&DisplayImage::__DelayedView)!=0){
			DBuff=&L->GetDelayedViewBuff();
		}
		else if((DType&DisplayImage::__RawTarget)!=0){
			DBuff=&L->GetRawTargetBuff();
		}
		else if((DType&DisplayImage::__CamTarget)!=0){
			DBuff=&L->GetCamTargetBuff();
		}
		if(DBuff!=NULL){
			DBuff->SetChanged(true);
			UndoDataInLayer	*UndoPointer=new UndoDataInLayer(L ,&DataInLayer::UndoPasteRect);
			BYTE	d=(BYTE)DType;
			::Save(UndoPointer->GetWritePointer(),d);
			FlexAreaImage	UndoAreaImage;
			UndoAreaImage.Set(Area,*DBuff);
			UndoAreaImage.Save(UndoPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

			Area.PaintWithColor(*DBuff, m&0xFF,0,0);
		}
		m>>=8;
	}
}

//=======================================================================
GUICmdDrawDot::GUICmdDrawDot(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	DType=dtype;
	MasterNo=0;
}

bool	GUICmdDrawDot::Save(QIODevice *f)
{
	f->write((const char *)&DType  ,sizeof(DType));
	QString	c=::QColor2QString(Col);
	if(::Save(f,c)==false){
		return false;
	}
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	return true;
}
bool	GUICmdDrawDot::Load(QIODevice *f)
{
	f->read((char *)&DType  ,sizeof(DType));
	QString	c;
	if(::Load(f,c)==false){
		return false;
	}
	Col=::QString2QColor(c);
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	return true;
}


void	GUICmdDrawDot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	QRgb	Drgb=Col.rgb();
	int		m=(int)Drgb;
	for(int layer=min(P->GetLayerNumb(),3)-1;layer>=0;layer--){
		DataInLayer	*L=P->GetLayerData(layer);
		if((DType&DisplayImage::__Master)!=0){
			L->GetMasterBuff(MasterNo).GetY(LocalY)[LocalX]=m&0xFF;
			L->GetMasterBuff(MasterNo).SetChanged(true);
		}
		else if((DType&DisplayImage::__BackGround)!=0){
			L->GetBackGroundBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetBackGroundBuff().SetChanged(true);
		}
		else if((DType&DisplayImage::__Target)!=0){
			L->GetTargetBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetTargetBuff().SetChanged(true);
		}
		else if((DType&DisplayImage::__TargetTR)!=0){
			L->GetTargetTRBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetTargetTRBuff().SetChanged(true);
		}
		else if((DType&DisplayImage::__DelayedView)!=0){
			L->GetDelayedViewBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetDelayedViewBuff().SetChanged(true);
		}
		else if((DType&DisplayImage::__RawTarget)!=0){
			L->GetRawTargetBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetRawTargetBuff().SetChanged(true);
		}
		else if((DType&DisplayImage::__CamTarget)!=0){
			L->GetCamTargetBuff().GetY(LocalY)[LocalX]=m&0xFF;
			L->GetCamTargetBuff().SetChanged(true);
		}
		m>>=8;
	}
}

//=======================================================================
GUICmdSelectItems::GUICmdSelectItems(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	MultiSelect=false;
}
bool	GUICmdSelectItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);

	if(Ab!=NULL){
		if(Phase==-2){
			IntList PhaseList;
			ActivePhaseList(PhaseList);
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->SelectItems(Area ,LayerList,MultiSelect);
				}
			}
		}
		else
		if(Phase==-1){
			int phase=GetLayersBase()->GetCurrentPhase();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectItems(Area ,LayerList,MultiSelect);
			}
		}
		else if(0<=Phase && Phase<GetPhaseNumb()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectItems(Area ,LayerList,MultiSelect);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdSelectAll::GUICmdSelectAll(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base->GetLayersBase(),emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	base->GetDLLName(AlgoRoot ,AlgoName);
}
bool	GUICmdSelectAll::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdSelectAll::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectAll(LayerList);
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdSelectLocked::GUICmdSelectLocked(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base->GetLayersBase(),emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	base->GetDLLName(AlgoRoot ,AlgoName);
}
bool	GUICmdSelectLocked::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdSelectLocked::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectLocked::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectLocked(LayerList);
			}
		}
	}
	SendAck(localPage);
}



//=======================================================================
GUICmdCutItems::GUICmdCutItems(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	MultiSelect=true;
	Phase=-1;
}

bool	GUICmdCutItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MultiSelect)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdCutItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MultiSelect)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdCutItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		if(Phase==-2){
			IntList PhaseList;
			ActivePhaseList(PhaseList);
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->CutArea(Area,LayerList,MultiSelect);
				}
			}
		}
		else if(Phase==-1){
			int phase=GetLayersBase()->GetCurrentPhase();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->CutArea(Area,LayerList,MultiSelect);
			}
		}
		else if(0<=Phase && Phase<GetPhaseNumb()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->CutArea(Area,LayerList,MultiSelect);
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdSeparateItems::GUICmdSeparateItems(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	Phase=-1;
}

bool	GUICmdSeparateItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdSeparateItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdSeparateItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		if(Phase==-2){
			IntList PhaseList;
			ActivePhaseList(PhaseList);
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->SeparateItems(Area,LayerList);
				}
			}
		}
		else if(Phase==-1){
			int phase=GetLayersBase()->GetCurrentPhase();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SeparateItems(Area,LayerList);
			}
		}
		else if(0<=Phase && Phase<GetPhaseNumb()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SeparateItems(Area,LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdRegistArea::GUICmdRegistArea(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdRegistArea::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(Area.Load(f)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdRegistArea::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdRegistArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->RegistArea(Area,LayerList);
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdOperationDelete::GUICmdOperationDelete(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	Phase=-1;
}

bool	GUICmdOperationDelete::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdOperationDelete::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationDelete::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		if(Phase==-2){
			IntList PhaseList;
			ActivePhaseList(PhaseList);
			for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
				int phase=v->GetValue();
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->DeleteSelectedItems(LayerList);
				}
			}
		}
		else if(Phase==-1){
			int phase=GetLayersBase()->GetCurrentPhase();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->DeleteSelectedItems(LayerList);
			}
		}
		else if(0<=Phase && Phase<GetPhaseNumb()){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->DeleteSelectedItems(LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdOperationLock::GUICmdOperationLock(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdOperationLock::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdOperationLock::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationLock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->LockSelectedItems(LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdOperationUnlock::GUICmdOperationUnlock(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdOperationUnlock::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdOperationUnlock::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationUnlock::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->UnlockAll(LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdOperationGroup::GUICmdOperationGroup(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdOperationGroup::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdOperationGroup::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationGroup::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->BindSelectedItems(LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================

GUICmdActivateOnItem::GUICmdActivateOnItem(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdActivateOnItem::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,PosX)==false){
		return false;
	}
	if(::Load(f,PosY)==false){
		return false;
	}
	return true;
}
bool	GUICmdActivateOnItem::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,PosX)==false){
		return false;
	}
	if(::Save(f,PosY)==false){
		return false;
	}
	return true;
}

void	GUICmdActivateOnItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	GUICmdSendActivateOnItem	*SendBack=(GUICmdSendActivateOnItem *)((GetSendBackPacket()==NULL)?new GUICmdSendActivateOnItem(Ab ,EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				if(cmd==0){
					Ap->Activate(PosX,PosY ,LayerList,SendBack->ItemList);
				}
				else{
					Ap->Inactivate();
				}
			}
		}
	}
	SendBack->AlgoRoot=AlgoRoot;
	SendBack->AlgoName=AlgoName;
	SendBack->LayerList=LayerList;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendActivateOnItem::GUICmdSendActivateOnItem(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdSendActivateOnItem::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(ItemList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendActivateOnItem::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(ItemList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendActivateOnItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

GUICmdActivateOnItemDirect::GUICmdActivateOnItemDirect(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdActivateOnItemDirect::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}
bool	GUICmdActivateOnItemDirect::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}

void	GUICmdActivateOnItemDirect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->Activate(Layer,ItemID);
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdReqClearTemporaryItems::GUICmdReqClearTemporaryItems(AlgorithmBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}

bool	GUICmdReqClearTemporaryItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}

	return(true);
}
bool	GUICmdReqClearTemporaryItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}

	return(true);
}

void	GUICmdReqClearTemporaryItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(L!=NULL){
		L->GetPageData(localPage)->ClearTemporaryItems();
	}
}

//=======================================================================

GUICmdReqTemporaryItems::GUICmdReqTemporaryItems(DisplayImageWithAlgorithm *form ,AlgorithmBase *base 
									,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Form=form;
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}
GUICmdReqTemporaryItems::~GUICmdReqTemporaryItems(void)
{
}

bool	GUICmdReqTemporaryItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,InstName)==false){
		return false;
	}
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}

	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	if(ModePoint->LoadAttr(f)==false){
		delete	ModePoint;
		return false;
	}
	delete	ModePoint;

	if(LayerList.Load(f)==false){
		return false;
	}

	return(true);
}
bool	GUICmdReqTemporaryItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	if(ModePoint->SaveAttr(f)==false){
		delete	ModePoint;
		return false;
	}
	delete	ModePoint;

	if(LayerList.Save(f)==false){
		return false;
	}

	return(true);
}

void	GUICmdReqTemporaryItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	int	GlobalPageNumb=GetLayersBase()->GetGlobalPageNumb();
	int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	GUICmdAckTemporaryItems	*SendBack=GetSendBack(GUICmdAckTemporaryItems,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	if(A->GetEnableOutsideItems()==true){
		NPListPack<ItemPointerListInPage>	OutsideItems;
		for(int page=0;page<GlobalPageNumb;page++){
			OutsideItems.AppendList(new ItemPointerListInPage(page));
		}
		if(L!=NULL){
			AlgorithmInPageRoot	*Pg=L->GetPageData(localPage);
			Pg->GetOutsideItems(Data.MoveGlobalDx ,Data.MoveGlobalDy,OutsideItems ,GlobalPageNumb);

			for(ItemPointerListInPage *p=OutsideItems.GetFirst();p!=NULL;p=p->GetNext()){
				int	s_globalPage=p->Page;
				if(CurrentGlobalPage!=s_globalPage){
					if(p->GetItemsCount()!=0){
						SlaveCommSendTemporaryItems	SItem(L
													, EmitterRoot,EmitterName ,s_globalPage);
						SItem.SetData(p);
						SItem.Send(NULL,s_globalPage ,0);
					}
				}
			}
		}
	}

	SendBack->Send(this ,globalPage,0);
	CloseSendBack(SendBack);
}

GUICmdAckTemporaryItems::GUICmdAckTemporaryItems(LayersBase *base 
					, const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
//=======================================================================
GUICmdReqItemsBmp::GUICmdReqItemsBmp(DisplayImageWithAlgorithm *form ,AlgorithmBase *base 
									,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Form=form;
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}
GUICmdReqItemsBmp::~GUICmdReqItemsBmp(void)
{
}

bool	GUICmdReqItemsBmp::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,InstName)==false){
		return false;
	}
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}

	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	if(ModePoint->LoadAttr(f)==false){
		delete	ModePoint;
		return false;
	}
	delete	ModePoint;

	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,DAttrArray)==false){
		return false;
	}

	return(true);
}
bool	GUICmdReqItemsBmp::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	if(ModePoint->SaveAttr(f)==false){
		delete	ModePoint;
		return false;
	}
	delete	ModePoint;

	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,DAttrArray)==false){
		return false;
	}

	return(true);
}

void	GUICmdReqItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	//int	GlobalPageNumb=GetLayersBase()->GetGlobalPageNumb();
	//int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	GUICmdSendItemsBmp	*SendBack=(GUICmdSendItemsBmp *)((GetSendBackPacket()==NULL)?new GUICmdSendItemsBmp(L ,EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmDrawAttr	*ModePoint=Form->CreateDrawAttrPointer();
	QBuffer	DAttrBuff(&DAttrArray);
	DAttrBuff.open(QIODevice::ReadOnly);
	ModePoint->Load(&DAttrBuff);
	ModePoint->DType	=(int32)Data.DType;
	SendBack->MakeImage(ModePoint
						,LayerList
						,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
						,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
						,Data.MovX,Data.MovY,Data.ZoomRate
						,localPage
						,Data.Mode
						,Data.MoveGlobalDx ,Data.MoveGlobalDy
						,A
						,Data.DType
						,*GetLayersBase()
						,EmitterRoot,EmitterName);
	delete	ModePoint;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendItemsBmp::GUICmdSendItemsBmp(AlgorithmBase *base 
									  ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
									  :GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	IData=NULL;
}

GUICmdSendItemsBmp::~GUICmdSendItemsBmp(void)
{
	if(IData!=NULL){
		delete	IData;
		IData=NULL;
	}
}

bool	GUICmdSendItemsBmp::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	//IData->load(f,"PNG");
	int32	W,H;
	if(::Load(f,W)==false){
		return false;
	}
	if(::Load(f,H)==false){
		return false;
	}
	if(IData==NULL || IData->width()!=W || IData->height()!=H){
		if(IData!=NULL){
			delete	IData;
		}
		//IData=new QImage(W,H,QImage::Format_ARGB32_Premultiplied);
		IData=new QImage(W,H,QImage::Format_ARGB32);
	}
	for(int h=0;h<H;h++){
		char	*s=(char *)IData->scanLine(h);
		if(f->read(s,W*4)!=W*4){
			return false;
		}
	}
	return(true);
}
bool	GUICmdSendItemsBmp::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	int32	W=IData->width();
	if(::Save(f,W)==false){
		return false;
	}

	int32	H=IData->height();
	if(::Save(f,H)==false){
		return false;
	}
	
	for(int h=0;h<H;h++){
		char	*s=(char *)IData->scanLine(h);
		if(f->write(s,W*4)!=W*4){
			return false;
		}
	}
	//IData->save(f,"PNG");
	return(true);
}

void	GUICmdSendItemsBmp::MakeImage(AlgorithmDrawAttr	*ModePoint
								 ,IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,DisplayImage::__DrawingMode	DMode
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,DisplayImageWithAlgorithm	*A
								 ,DisplayImage::DisplayType	DType
								 ,LayersBase &LocalLBase
								 ,QString &EmitterRoot,QString &EmitterName)
{
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	AlgorithmBase	*L=LocalLBase.GetAlgorithmBase(AlgoRoot,AlgoName);
	if(L==NULL){
		return;
	}
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		delete	IData;
		IData=NULL;
	}
	if(IData==NULL){
		//IData=new QImage(LGx,LGy,QImage::Format_ARGB32_Premultiplied);
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
	}
	//IData->fill(0);
	::ClearImage(*IData, 0);
	L->GetPageData(localPage)->Draw(*IData, LayerList,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate ,ModePoint);
	if(DMode==DisplayImage::_PasteMove
	|| DMode==DisplayImage::_PasteMovePreStart 
	|| DMode==DisplayImage::_PasteCreateShape 
	|| DMode==DisplayImage::_PasteCreateShapeStart
	|| DMode==DisplayImage::_CutByShape
	|| DMode==DisplayImage::_CutByShapePreStart){
		QColor	Col=Qt::darkMagenta;
		Col.setAlpha(100);
		A->PastedItemsDraw(localPage ,MoveGlobalDx ,MoveGlobalDy
			,*IData, MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,Col);
		int	CurrentGlobalPage=LocalLBase.GetGlobalPageFromLocal(localPage);
		QPainter	pnt(IData);
		pnt.setCompositionMode (QPainter::CompositionMode_SourceOver); 
		for(int globalpage=0;globalpage<LocalLBase.GetGlobalPageNumb();globalpage++){
			if(CurrentGlobalPage==globalpage){
				continue;
			}
			//XYData	*DrawnXY	=GetLayersBase()->GetGlobalOutlineOffset(globalpage);
			SlaveCommReqPasteShape	RCmd(&LocalLBase,EmitterRoot,EmitterName,CurrentGlobalPage);
			SlaveCommAckPasteShape	ACmd(&LocalLBase,EmitterRoot,EmitterName,CurrentGlobalPage);
			RCmd.DrawnGlobalPage=CurrentGlobalPage;
			RCmd.MoveGlobalDx	=MoveGlobalDx;
			RCmd.MoveGlobalDy	=MoveGlobalDy;
			RCmd.Gx1			=Gx1;
			RCmd.Gy1			=Gy1;
			RCmd.Gx2			=Gx2;
			RCmd.Gy2			=Gy2;
			RCmd.Col			=Col;
			RCmd.Movx			=MovX;
			RCmd.Movy			=MovY;
			RCmd.ZoomRate		=ZoomRate;
			RCmd.InstName		=A->GetName();
			if(RCmd.Send(globalpage,0,ACmd)==true){
				if(ACmd.Drawn==true){
					pnt.drawImage(ACmd.DrawnPosX,ACmd.DrawnPosY,ACmd.Pnt);
				}
			}
		}
	}
	if(DMode==DisplayImage::_ItemMove){
		QColor	Col=Qt::darkMagenta;
		Col.setAlpha(100);
		L->DrawMove(localPage,MoveGlobalDx ,MoveGlobalDy,*IData, MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate ,Col,ModePoint);
		/*
		AlgorithmInPageRoot	*Pg=L->GetPageData(localPage);
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		ItemPointerListInPage *pp=OutsideItems.GetItem(globalPage);
		Pg->GetOutsideItems(MoveGlobalDx ,MoveGlobalDy,pp ,LocalLBase.GetGlobalPageNumb());
		*/
	}
	if(DMode==DisplayImage::_DrawUncoveredArea){
		DataInPage* P = LocalLBase.GetPageData(localPage);
		int XByte ,YLen;
		const BYTE	**BMap=P->GetUncoveredMap(XByte ,YLen);
		if(BMap==NULL){
			P->MakeUncoveredMap();
		}
		if(MovX>0){
			MovX=0;
		}
		if(MovY>0){
			MovY=0;
		}
		DrawBitImage(*IData, BMap,XByte*8 ,XByte ,YLen
					,MovX ,MovY ,ZoomRate
					,0,0
					,ModePoint->UncoveredColor);
	}
}

//=======================================================================
GUICmdReqItemIndependentPack::GUICmdReqItemIndependentPack(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SubResultMoving=true;
	TargetPhase		=-1;
}
bool	GUICmdReqItemIndependentPack::Load(QIODevice *f)
{
	if(::Load(f,localX)==false){
		return false;
	}
	if(::Load(f,localY)==false){
		return false;
	}
	if(::Load(f,SubResultMoving)==false){
		return false;
	}
	if(::Load(f,TargetPhase)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemIndependentPack::Save(QIODevice *f)
{
	if(::Save(f,localX)==false){
		return false;
	}
	if(::Save(f,localY)==false){
		return false;
	}
	if(::Save(f,SubResultMoving)==false){
		return false;
	}
	if(::Save(f,TargetPhase)==false){
		return false;
	}
	return true;
}

void	GUICmdReqItemIndependentPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendIndependentPack *SendBack=(GUICmdSendIndependentPack *)((GetSendBackPacket()==NULL)?new GUICmdSendIndependentPack(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		L->MakeIndependentItems(TargetPhase,localPage,SubResultMoving,localX ,localY,L->GetInstance(),SendBack->IData);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendIndependentPack::GUICmdSendIndependentPack(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage),IData(base)
{
}
bool	GUICmdSendIndependentPack::Load(QIODevice *f)
{
	IData.Load(f);
	return true;
}
bool	GUICmdSendIndependentPack::Save(QIODevice *f)
{
	IData.Save(f);
	return true;
}

void	GUICmdSendIndependentPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//=======================================================================
GUICmdReqItemIndependentsPack::GUICmdReqItemIndependentsPack(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	LibType		=0;
	LibID		=-1;
	TargetPhase	=-1;	//-1:Any phase
	Layer		=0;
}
bool	GUICmdReqItemIndependentsPack::Load(QIODevice *f)
{
	if(::Load(f,LibType)==false){
		return false;
	}
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,TargetPhase)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(Items.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemIndependentsPack::Save(QIODevice *f)
{
	if(::Save(f,LibType)==false){
		return false;
	}
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,TargetPhase)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(Items.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqItemIndependentsPack::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendIndependentPack *SendBack=(GUICmdSendIndependentPack *)((GetSendBackPacket()==NULL)?new GUICmdSendIndependentPack(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		int	Phase=0;
		if(TargetPhase==-1){
			Phase=GetLayersBase()->GetCurrentPhase();
		}
		else if(0<=TargetPhase && TargetPhase<GetPhaseNumb()){
			Phase=TargetPhase;
		}
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot		*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->MakeIndependentItems(Layer,Items,SendBack->IData);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================

DisplayImageCopyStructureMemoryList::DisplayImageCopyStructureMemoryList(void)
{	
	DataBytes=0;	
	Data=NULL;	
}
DisplayImageCopyStructureMemoryList::~DisplayImageCopyStructureMemoryList(void)
{	
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
	DataBytes=0;
}

bool	DisplayImageCopyStructureMemoryList::Save(QIODevice *f)
{
	if(::Save(f,DataBytes)==false){
		return false;
	}
	if(Data!=NULL){
		if(::Save(f,(char *)Data,(int64)DataBytes)==false){
			return false;
		}
	}
	return true;
}
bool	DisplayImageCopyStructureMemoryList::Load(QIODevice *f)
{
	if(::Load(f,DataBytes)==false){
		return false;
	}
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=new BYTE[DataBytes];
	int64 len;
	if(::Load(f,(char *)Data,len ,DataBytes)==false){
		return false;
	}
	if(len!=DataBytes){
		return false;
	}
	return true;
}

DisplayImageCopyStructure::DisplayImageCopyStructure(const DisplayImageCopyStructure &src)
{
	GlobalPage		=src.GlobalPage;
	DType			=src.DType;
	LayerList		=src.LayerList;
	MasterNo		=src.MasterNo;
	ImageWithAreas.RemoveAll();
	for(FlexAreaImageList *s=src.ImageWithAreas.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaImageList	*d=new FlexAreaImageList ();
		*d=*s;
		ImageWithAreas.AppendList(d);
	}
}

void	DisplayImageCopyStructure::Capture(FlexArea &area ,DataInPage *PageData ,DisplayImage::DisplayType &dtype)
{
	LayerList.RemoveAll();
	ImageWithAreas.RemoveAll();
	for(int layer=0;layer<PageData->GetLayerNumb();layer++){
		LayerList.Add(layer);
		FlexAreaImageList	*v=new FlexAreaImageList();
		if((dtype&DisplayImage::__Master)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetMasterBuff(MasterNo));
		}
		else if((dtype&DisplayImage::__BackGround)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetBackGroundBuff());
		}
		else if((dtype&DisplayImage::__Target)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetTargetBuff());
		}
		else if((dtype&DisplayImage::__TargetTR)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetTargetTRBuff());
		}
		else if((dtype&DisplayImage::__DelayedView)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetDelayedViewBuff());
		}
		else if((dtype&DisplayImage::__RawTarget)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetRawTargetBuff());
		}
		else if((dtype&DisplayImage::__CamTarget)!=0){
			v->Set(area,PageData->GetLayerData(layer)->GetCamTargetBuff());
		}
		ImageWithAreas.AppendList(v);
	}
	GlobalPage=PageData->GetLayersBase()->GetGlobalPageFromLocal(PageData->GetPage());
	DType=dtype;
}

void	DisplayImageCopyStructure::Draw(QImage &Img ,int dx ,int dy 
				,int movx ,int movy ,double zoomrate)
{
	if(LayerList.GetCount()>=3){
		FlexAreaImageList	*a1=ImageWithAreas.GetFirst();
		FlexAreaImageList	*a2=a1->GetNext();
		FlexAreaImageList	*a3=a2->GetNext();
		double	Z=1.0/zoomrate;
		BYTE	*s1	=a1->GetData();
		BYTE	*s2	=a2->GetData();
		BYTE	*s3	=a3->GetData();
	    for(int i=0;i<a1->GetFLineLen();i++){
		    int x1		=a1->GetFLineLeftX(i);
			int Numb	=a1->GetFLineNumb(i);
			int	y		=a1->GetFLineAbsY(i);
			int	Y =(y +dy+movy)*zoomrate;
			int	X1=(x1+dx+movx)*zoomrate;
			int	X2=(x1+Numb+dx+movx)*zoomrate;
			if(Y<0 || Y>=Img.height()){
				s1+=Numb;
				s2+=Numb;
				s3+=Numb;
				continue;
			}
			if(X1>=Img.width() || X2<0){
				s1+=Numb;
				s2+=Numb;
				s3+=Numb;
				continue;
			}
			if(X1<0){
				X1=0;
			}
			if(X2>=Img.width()){
				X2=Img.width();
			}
			BYTE	*d=Img.scanLine(Y);
			for(int x=X1;x<X2;x++){
				int	ix=x*Z-dx-movx;
				if(0<=(ix-x1) && (ix-x1)<Numb){
					d[x*4+0]=s1[ix-x1];
					d[x*4+1]=s2[ix-x1];
					d[x*4+2]=s3[ix-x1];
					d[x*4+3]=0x80;
				}
			}
			s1+=Numb;
			s2+=Numb;
			s3+=Numb;
		}
	}
	else if(LayerList.GetCount()==2){
		FlexAreaImageList	*a1=ImageWithAreas.GetFirst();
		FlexAreaImageList	*a2=a1->GetNext();
		double	Z=1.0/zoomrate;
		BYTE	*s1	=a1->GetData();
		BYTE	*s2	=a2->GetData();
	    for(int i=0;i<a1->GetFLineLen();i++){
		    int x1		=a1->GetFLineLeftX(i);
			int Numb	=a1->GetFLineNumb(i);
			int	y		=a1->GetFLineAbsY(i);
			int	Y =(y +dy+movy)*zoomrate;
			int	X1=(x1+dx+movx)*zoomrate;
			int	X2=(x1+Numb+dx+movx)*zoomrate;
			if(Y<0 || Y>=Img.height()){
				s1+=Numb;
				s2+=Numb;
				continue;
			}
			if(X1>=Img.width() || X2<0){
				s1+=Numb;
				s2+=Numb;
				continue;
			}
			if(X1<0){
				X1=0;
			}
			if(X2>=Img.width()){
				X2=Img.width();
			}
			BYTE	*d=Img.scanLine(Y);
			for(int x=X1;x<X2;x++){
				int	ix=x*Z-dx-movx;
				if(0<=(ix-x1) && (ix-x1)<Numb){
					d[x*4+0]=s1[ix-x1];
					d[x*4+1]=s2[ix-x1];
					d[x*4+2]=s2[ix-x1];
					d[x*4+3]=0x80;
				}
			}
			s1+=Numb;
			s2+=Numb;
		}
	}
	else if(LayerList.GetCount()==1){
		FlexAreaImageList	*a1=ImageWithAreas.GetFirst();
		double	Z=1.0/zoomrate;
		BYTE	*s1	=a1->GetData();
	    for(int i=0;i<a1->GetFLineLen();i++){
		    int x1		=a1->GetFLineLeftX(i);
			int Numb	=a1->GetFLineNumb(i);
			int	y		=a1->GetFLineAbsY(i);
			int	Y =(y +dy+movy)*zoomrate;
			int	X1=(x1+dx+movx)*zoomrate;
			int	X2=(x1+Numb+dx+movx)*zoomrate;
			if(Y<0 || Y>=Img.height()){
				s1+=Numb;
				continue;
			}
			if(X1>=Img.width() || X2<0){
				s1+=Numb;
				continue;
			}
			if(X1<0){
				X1=0;
			}
			if(X2>=Img.width()){
				X2=Img.width();
			}
			BYTE	*d=Img.scanLine(Y);
			for(int x=X1;x<X2;x++){
				int	ix=x*Z-dx-movx;
				if(0<=(ix-x1) && (ix-x1)<Numb){
					d[x*4+0]=s1[ix-x1];
					d[x*4+1]=s1[ix-x1];
					d[x*4+2]=s1[ix-x1];
					d[x*4+3]=0x80;
				}
			}
			s1+=Numb;
		}
	}
}

bool	DisplayImageCopyStructure::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false){
		return false;
	}
	int32	N=ImageWithAreas.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(FlexAreaImageList *a=ImageWithAreas.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	if(::Save(f,(int32)DType)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	return true;
}

bool	DisplayImageCopyStructure::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false){
		return false;
	}
	int32	N;
	ImageWithAreas.RemoveAll();
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		FlexAreaImageList *a=new FlexAreaImageList();
		if(a->Load(f)==false){
			return false;
		}
		ImageWithAreas.AppendList(a);
	}

	if(::Load(f,GlobalPage)==false){
		return false;
	}

	if(::Load(f,N)==false){
		return false;
	}
	DType=(DisplayImage::DisplayType)N;
	if(::Load(f,MasterNo)==false){
		return false;
	}

	return true;
}

DisplayImageCopyStructure	&DisplayImageCopyStructure::operator=(const DisplayImageCopyStructure &src)
{
	GlobalPage		=src.GlobalPage;
	DType			=src.DType;
	LayerList		=src.LayerList;
	MasterNo		=src.MasterNo;
	ImageWithAreas.RemoveAll();
	for(FlexAreaImageList *s=src.ImageWithAreas.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaImageList	*d=new FlexAreaImageList ();
		*d=*s;
		ImageWithAreas.AppendList(d);
	}
	return *this;
}

bool	DisplayImageCopyStructure::SaveDefaultFile(void)
{
	QString	FileName=QDir::tempPath()+QString(/**/"/ImageClip.dat");
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==false){
		return false;
	}
	if(Save(&File)==false){
		return false;
	}
	return true;
}

bool	DisplayImageCopyStructure::LoadDefaultFile(void)
{
	QString	FileName=QDir::tempPath()+QString(/**/"/ImageClip.dat");
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(Load(&File)==false){
		return false;
	}
	return true;
}

GUICmdCopyRectPacket::GUICmdCopyRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdCopyRectPacket::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false){
		return false;
	}
	Source=(DisplayImage::DisplayType)d;
	if(Area.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdCopyRectPacket::Save(QIODevice *f)
{
	if(::Save(f,(int32)Source)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdCopyRectPacket::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	GUICmdSendCopyRectPacket	*SendBack=GetSendBack(GUICmdSendCopyRectPacket,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->ImageClipData.Capture(Area ,P,Source);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendCopyRectPacket::GUICmdSendCopyRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendCopyRectPacket::Load(QIODevice *f)
{
	if(ImageClipData.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendCopyRectPacket::Save(QIODevice *f)
{
	if(ImageClipData.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendCopyRectPacket::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ImageClipData.SaveDefaultFile();
}

GUICmdReqPasteRectPacket::GUICmdReqPasteRectPacket(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	dx=dy=0;
}

bool	GUICmdReqPasteRectPacket::Load(QIODevice *f)
{
	if(::Load(f,dx)==false){
		return false;
	}
	if(::Load(f,dy)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	ImageClipData.RemoveAll();
	for(int i=0;i<N;i++){
		DisplayImageCopyStructure *a=new DisplayImageCopyStructure(MasterNo);
		if(a->Load(f)==false){
			return false;
		}
		ImageClipData.AppendList(a);
	}
	return true;
}

bool	GUICmdReqPasteRectPacket::Save(QIODevice *f)
{
	if(::Save(f,dx)==false){
		return false;
	}
	if(::Save(f,dy)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	int32	N=ImageClipData.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(DisplayImageCopyStructure *a=ImageClipData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

void	GUICmdReqPasteRectPacket::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	int	x1,y1,x2,y2;
    int hx1;
	int Numb;
	int	hy;
	DisplayImageCopyStructure *a;
	XYData	*c;
	XYData	*q;
	DataInPage *Pg=GetLayersBase()->GetPageData(localPage);

	for(a=ImageClipData.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageList	*f=a->ImageWithAreas.GetFirst();
		if(f==NULL){
			continue;
		}
		c=GetLayersBase()->GetGlobalOutlineOffset(a->GlobalPage);
		q=GetLayersBase()->GetGlobalOutlineOffset(GetLayersBase()->GetGlobalPageFromLocal(localPage));
		f->GetXY(x1,y1,x2,y2);
		x1=x1+c->x+dx-q->x;
		y1=y1+c->y+dy-q->y;
		x2=x2+c->x+dx-q->x;
		y2=y2+c->y+dy-q->y;
		if(x2<0 || x1>=Pg->GetDotPerLine() || y2<0 || y1>=Pg->GetMaxLines()){
			continue;
		}
		int	Layer=0;

		int	Dx=c->x+dx-q->x;
		int	Dy=c->y+dy-q->y;

		for(FlexAreaImageList *L=a->ImageWithAreas.GetFirst();L!=NULL;L=L->GetNext(),Layer++){
			BYTE	*s	=L->GetData();
			DataInLayer	*Ly=GetLayersBase()->GetPageData(localPage)->GetLayerData(Layer);
			if(Ly!=NULL){
				ImageBuffer	*DBuff=NULL;
				if((a->DType&DisplayImage::__Target)!=0){
					DBuff=&Ly->GetTargetBuff();
				}
				else if((a->DType&DisplayImage::__TargetTR)!=0){
					DBuff=&Ly->GetTargetTRBuff();
				}
				else if((a->DType&DisplayImage::__Master)!=0){
					DBuff=&Ly->GetMasterBuff(MasterNo);
				}
				else if((a->DType&DisplayImage::__BackGround)!=0){
					DBuff=&Ly->GetBackGroundBuff();
				}
				else if((a->DType&DisplayImage::__DelayedView)!=0){
					DBuff=&Ly->GetDelayedViewBuff();
				}
				else if((a->DType&DisplayImage::__RawTarget)!=0){
					DBuff=&Ly->GetRawTargetBuff();
				}
				else if((a->DType&DisplayImage::__CamTarget)!=0){
					DBuff=&Ly->GetCamTargetBuff();
				}
				DBuff->SetChanged(true);
				UndoDataInLayer	*UndoPointer=new UndoDataInLayer(Ly ,&DataInLayer::UndoPasteRect);
				BYTE	d=(BYTE)a->DType;
				::Save(UndoPointer->GetWritePointer(),d);
				FlexAreaImage	UndoAreaImage;
				FlexArea	aArea=*L;
				aArea.MoveToClip(Dx,Dy,0,0,Pg->GetDotPerLine(),Pg->GetMaxLines());
				UndoAreaImage.Set(aArea,*DBuff);
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

				for(int i=0;i<L->GetFLineLen();i++){
				    hx1		=L->GetFLineLeftX(i);
					Numb	=L->GetFLineNumb(i);
					hy		=L->GetFLineAbsY(i);

					hx1	=hx1+Dx;
					hy	=hy +Dy;
					if(0<=hy && hy<Pg->GetMaxLines()){

						BYTE	*sb=s;
						int	hx2=hx1+Numb;
						if(hx1<0){
							sb-=hx1;
							hx1=0;
						}
						if(hx2>=Pg->GetDotPerLine()){
							hx2=Pg->GetDotPerLine();
						}
						if(hx2>hx1){
							memcpy(DBuff->GetY(hy)+hx1,sb,hx2-hx1);
						}
					}
					s+=Numb;
				}
			}
		}
	}

}


GUICmdReqClippedImage::GUICmdReqClippedImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MasterNo=0;
}
bool	GUICmdReqClippedImage::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Source=(DisplayImage::DisplayType)N;
	if(RealArea.Load(f)==false){
		return false;
	}
	if(::Load(f,ZoomRate)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqClippedImage::Save(QIODevice *f)
{
	if(::Save(f,(int32)Source)==false){
		return false;
	}
	if(RealArea.Save(f)==false){
		return false;
	}
	if(::Save(f,ZoomRate)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	return true;
}

void	GUICmdReqClippedImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendClippedImage	*SendBack=GetSendBack(GUICmdSendClippedImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	//SendBack->ZoomedArea.CreateZoom(ZoomRate,RealArea,Cx,Cy);
	SendBack->CreateImageData(GetLayersBase(),RealArea,ZoomRate,Source,MasterNo);
	SendBack->LayerList=LayerList;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendClippedImage::GUICmdSendClippedImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSendClippedImage::CreateImageData(LayersBase *Base,FlexArea &RealArea
												,double ZoomRate
												,DisplayImage::DisplayType DType
												,int MasterNo)
{
	BuffList.RemoveAll();
	int	LocalPage	=Base->GetLocalPageFromGlobal(GetGlobalPage());
	DataInPage	*PageData=Base->GetPageData(LocalPage);
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		DataInLayer	*Ly=PageData->GetLayerData(L->GetValue());
		BYTE		*D=NULL;
		int BuffBytes=0;
		ZoomedArea=RealArea;
		int	Cx,Cy;
		RealArea.GetCenter(Cx,Cy);
		if((DType&DisplayImage::__Master)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetMasterBuff(MasterNo),BuffBytes);
		}
		else if((DType&DisplayImage::__BackGround)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetBackGroundBuff(),BuffBytes);
		}
		else if((DType&DisplayImage::__Target)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetTargetBuff(),BuffBytes);
		}
		else if((DType&DisplayImage::__TargetTR)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetTargetTRBuff(),BuffBytes);
		}
		else if((DType&DisplayImage::__DelayedView)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetDelayedViewBuff(),BuffBytes);
		}
		else if((DType&DisplayImage::__RawTarget)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetRawTargetBuff(),BuffBytes);
		}
		else if((DType&DisplayImage::__CamTarget)!=0){
			D=ZoomedArea.GetZoomPattern(ZoomRate,Cx,Cy
										,Ly->GetCamTargetBuff(),BuffBytes);
		}
		DisplayImageCopyStructureMemoryList	*a=new DisplayImageCopyStructureMemoryList();
		a->DataBytes=BuffBytes;
		a->Data		=D;
		BuffList.AppendList(a);
	}
}
void	GUICmdSendClippedImage::Draw(QImage &Img ,int GlobalX ,int GlobalY
									,int movx ,int movy ,double ZoomRate)
{
	int	Cx,Cy;
	ZoomedArea.GetCenter(Cx,Cy);
	int	Lx=(GlobalX+movx)*ZoomRate - Cx;
	int	Ly=(GlobalY+movy)*ZoomRate - Cy;

	int	NLen=ZoomedArea.GetFLineLen();
	if(BuffList.GetNumber()>=3){
		int		Layer0=LayerList.GetItem(0)->GetValue();
		int		Layer1=LayerList.GetItem(1)->GetValue();
		int		Layer2=LayerList.GetItem(2)->GetValue();
		BYTE	*Point0=BuffList.GetItem(0)->Data;
		BYTE	*Point1=BuffList.GetItem(1)->Data;
		BYTE	*Point2=BuffList.GetItem(2)->Data;
		for(int i=0;i<NLen;i++){
			int x1=ZoomedArea.GetFLineLeftX (i)+Lx;
			int x2=ZoomedArea.GetFLineRightX(i)+Lx;
			int	Numb=x2-x1;
			int y =ZoomedArea.GetFLineAbsY  (i)+Ly;
			BYTE	*PointTop0=Point0;
			BYTE	*PointTop1=Point1;
			BYTE	*PointTop2=Point2;
			if(x1<0){
				PointTop0+=-x1;
				PointTop1+=-x1;
				PointTop2+=-x1;
				x1=0;
			}
			if(x2>=Img.width()){
				x2=Img.width();
			}
			if(0<=y && y<Img.height()){
				BYTE	*D=(BYTE *)Img.scanLine(y);
				int	n=0;
				for(int x=x1;x<x2;x++,n++){
					*(D+x*4+Layer0)=PointTop0[n];
					*(D+x*4+Layer1)=PointTop1[n];
					*(D+x*4+Layer2)=PointTop2[n];
				}
			}
			Point0+=Numb;
			Point1+=Numb;
			Point2+=Numb;
		}
	}
}


bool	GUICmdSendClippedImage::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	BuffList.RemoveAll();
	for(int i=0;i<N;i++){
		DisplayImageCopyStructureMemoryList	*a=new DisplayImageCopyStructureMemoryList();
		if(a->Load(f)==false){
			return false;
		}
		BuffList.AppendList(a);
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(ZoomedArea.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendClippedImage::Save(QIODevice *f)
{
	int32	N=BuffList.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(DisplayImageCopyStructureMemoryList	*a=BuffList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(ZoomedArea.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendClippedImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================
GUICmdOperationCopy::GUICmdOperationCopy(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}
bool	GUICmdOperationCopy::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,CreatedTime)==false){
		return false;
	}
	if(::Load(f,EnableDup)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}

	return(true);
}
bool	GUICmdOperationCopy::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,CreatedTime)==false){
		return false;
	}
	if(::Save(f,EnableDup)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return(true);
}

void	GUICmdOperationCopy::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GetLayersBase()->ExecuteCopy(AlgoRoot,AlgoName,localPage,CreatedTime,LayerList,EnableDup);
	SendAck(localPage);
}

//=======================================================================
GUICmdOperationPaste::GUICmdOperationPaste(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdOperationPaste::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return(true);
}
bool	GUICmdOperationPaste::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return(true);
}

void	GUICmdOperationPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	SendAck(localPage);
}
//=======================================================================

GUICmdReqSelectCopied::GUICmdReqSelectCopied(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	PastedLayer=-1;
}

bool	GUICmdReqSelectCopied::Save(QIODevice *f)
{
	if(::Save(f,SelectTimeIndex)==false){
		return false;
	}
	if(::Save(f,InstName)==false){
		return false;
	}
	if(::Save(f,PastedLayer)==false){
		return false;
	}
	if(::Save(f,Color)==false){
		return false;
	}
	int32	N=(int32)Mode;
	if(::Save(f,N)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSelectCopied::Load(QIODevice *f)
{
	if(::Load(f,SelectTimeIndex)==false){
		return false;
	}
	if(::Load(f,InstName)==false){
		return false;
	}
	if(::Load(f,PastedLayer)==false){
		return false;
	}
	if(::Load(f,Color)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Mode=(_Mode)N;
	return true;
}

void	GUICmdReqSelectCopied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	if(Mode==_PurePaste){
		A->SetPasteMode(PastedLayer,SelectTimeIndex ,DisplayImage::_PasteMove);
	}
	else if(Mode==_ShapedPaste){
		A->SetPasteMode(PastedLayer,SelectTimeIndex ,DisplayImage::_PasteCreateShape);
	}	
	else if(Mode==_PasteForImage){
		A->SetPasteForImage(Color,SelectTimeIndex);
	}	
	else if(Mode==_CutByShape){
		A->SetPasteMode(PastedLayer,SelectTimeIndex ,DisplayImage::_CutByShape);
	}
}

//=======================================================================

GUICmdReqCutByPasted::GUICmdReqCutByPasted(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqCutByPasted::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	if(::Save(f,Dx)==false){
		return false;
	}
	if(::Save(f,Dy)==false){
		return false;
	}

	return true;
}
bool	GUICmdReqCutByPasted::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	if(::Load(f,Dx)==false){
		return false;
	}
	if(::Load(f,Dy)==false){
		return false;
	}

	return true;
}

void	GUICmdReqCutByPasted::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	A->ExecuteCutItemsByPasted(Dx,Dy);	
	SendAck(localPage);
}

//=======================================================================
GUICmdExecutePaste::GUICmdExecutePaste(LayersBase *Base,_Mode mode,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Mode=mode;
	SamePage=false;
	ItemClass=0;
}

bool	GUICmdExecutePaste::Load(QIODevice *f)
{
	if(::Load(f,InstName)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Mode=(_Mode)N;
	int64	LSize;
	if(::Load(f,LSize)==false){
		return false;
	}
	Buff=f->read(LSize);

	if(::Load(f,OriginRoot)==false){
		return false;
	}
	if(::Load(f,OriginName)==false){
		return false;
	}
	if(::Load(f,Dx)==false){
		return false;
	}
	if(::Load(f,Dy)==false){
		return false;
	}
	if(::Load(f,SamePage)==false){
		return false;
	}
	if(::Load(f,ItemClass)==false){
		return false;
	}

	return true;
}
bool	GUICmdExecutePaste::Save(QIODevice *f)
{
	if(::Save(f,InstName)==false){
		return false;
	}
	int32	N=(int32)Mode;
	if(::Save(f,N)==false){
		return false;
	}
	int64	LSize=Buff.size();
	if(::Save(f,LSize)==false){
		return false;
	}
	if(f->write(Buff)!=LSize){
		return false;
	}
	if(::Save(f,OriginRoot)==false){
		return false;
	}
	if(::Save(f,OriginName)==false){
		return false;
	}
	if(::Save(f,Dx)==false){
		return false;
	}
	if(::Save(f,Dy)==false){
		return false;
	}
	if(::Save(f,SamePage)==false){
		return false;
	}
	if(::Save(f,ItemClass)==false){
		return false;
	}
	return true;
}

void	GUICmdExecutePaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,InstName);
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}
	if(cmd==0){
		GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
		A->ExecutePaste(localPage,Dx,Dy,SamePage);
	}
	else if(cmd==1){
		GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());
		A->ExecutePasteCreateWithShape(localPage,Buff,OriginRoot,OriginName,ItemClass);
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdOperationMoveFromOutside::GUICmdOperationMoveFromOutside(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdOperationMoveFromOutside::Load(QIODevice *f)
{
	if(::Load(f,GlobalDx)==false){
		return false;
	}
	if(::Load(f,GlobalDy)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(PageListForOutside.Load(f)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}	
	return true;
}
bool	GUICmdOperationMoveFromOutside::Save(QIODevice *f)
{
	if(::Save(f,GlobalDx)==false){
		return false;
	}
	if(::Save(f,GlobalDy)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(PageListForOutside.Save(f)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationMoveFromOutside::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	int	GlobalPageNumb;
	int	CurrentGlobalPage;
	ItemPointerListInPage *p;

	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,/**/"");
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		if(A->GetEnableOutsideItems()==true){
			GlobalPageNumb	 =GetLayersBase()->GetGlobalPageNumb();
			CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);

			NPListPack<ItemPointerListInPage>	OutsideItems;
			for(int page=0;page<GlobalPageNumb;page++){
				OutsideItems.AppendList(new ItemPointerListInPage(page));
			}
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			AlgorithmInPageRoot	*Pg=Ah->GetPageData(localPage);
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			Pg->GetOutsideItems(GlobalDx ,GlobalDy,OutsideItems ,GlobalPageNumb);

			for(p=OutsideItems.GetFirst();p!=NULL;p=p->GetNext()){
				globalPage=p->Page;
				if(CurrentGlobalPage!=globalPage){
					for(IntClass *c=PageListForOutside.GetFirst();c!=NULL;c=c->GetNext()){
						if(c->GetValue()==globalPage){
							if(p->GetItemsCount()!=0){
								SlaveCommSendFixTemporaryItems	SItem(Ab
																, EmitterRoot,EmitterName ,globalPage);
								SItem.Phase	=Phase;
								SItem.SetData(p);
								SItem.Send(NULL,globalPage ,0);
							}
							break;
						}
					}
				}
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdOperationMove::GUICmdOperationMove(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdOperationMove::Load(QIODevice *f)
{
	if(::Load(f,GlobalDx)==false){
		return false;
	}
	if(::Load(f,GlobalDy)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(Items.Load(f)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}
	return true;
}
bool	GUICmdOperationMove::Save(QIODevice *f)
{
	if(::Save(f,GlobalDx)==false){
		return false;
	}
	if(::Save(f,GlobalDy)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(Items.Save(f)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}

void	GUICmdOperationMove::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	GUIFormBase	*q=GetLayersBase()->FindByName(EmitterRoot ,EmitterName ,/**/"");
	if(q==NULL){
		return;
	}
	DisplayImageWithAlgorithm	*A=dynamic_cast<DisplayImageWithAlgorithm *>(q);
	if(A==NULL){
		return;
	}

	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
		Ap->ExecuteMove(GlobalDx,GlobalDy,Items);
	}

	SendAck(localPage);
}

//=======================================================================

GUICmdReqMovedPage::GUICmdReqMovedPage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqMovedPage::Load(QIODevice *f)
{
	if(::Load(f,GlobalDx)==false){
		return false;
	}
	if(::Load(f,GlobalDy)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Phase)==false){
		return false;
	}	
	return true;
}
bool	GUICmdReqMovedPage::Save(QIODevice *f)
{
	if(::Save(f,GlobalDx)==false){
		return false;
	}
	if(::Save(f,GlobalDy)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Phase)==false){
		return false;
	}
	return true;
}
void	GUICmdReqMovedPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMovedPage	*SendBack=GetSendBack(GUICmdAckMovedPage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		Ab->GetPageListForExecuteMove(SendBack->PageList,localPage,GlobalDx,GlobalDy);
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
		Ap->EnumSelectedItems(SendBack->Items);
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckMovedPage::GUICmdAckMovedPage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckMovedPage::Load(QIODevice *f)
{
	if(PageList.Load(f)==false){
		return false;
	}
	if(Items.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckMovedPage::Save(QIODevice *f)
{
	if(PageList.Save(f)==false){
		return false;
	}
	if(Items.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdAckMovedPage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

GUICmdReqSelectedItemCount::GUICmdReqSelectedItemCount(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdReqSelectedItemCount::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSelectedItemCount::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSelectedItemCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedItemCount	*SendBack=GetSendBack(GUICmdSendSelectedItemCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->SelectedItemCount=GetLayersBase()->GetSelectedItemCount(AlgoRoot,AlgoName);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSelectedItemCount::GUICmdSendSelectedItemCount(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SelectedItemCount=0;
}

bool	GUICmdSendSelectedItemCount::Load(QIODevice *f)
{
	if(::Load(f,SelectedItemCount)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendSelectedItemCount::Save(QIODevice *f)
{
	if(::Save(f,SelectedItemCount)==false){
		return false;
	}
	return true;
}

void	GUICmdSendSelectedItemCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

GUICmdSetItemNameInSelected::GUICmdSetItemNameInSelected(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetItemNameInSelected::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,ItemName)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetItemNameInSelected::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,ItemName)==false){
		return false;
	}
	return true;
}

void	GUICmdSetItemNameInSelected::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*P=Ab->GetPageData(localPage);
		if(P!=NULL){
			P->SetItemName(ItemName,true);
		}
	}

	SendAck(localPage);
}

//=======================================================================

GUICmdReqItemCountOnLocalPoint::GUICmdReqItemCountOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqItemCountOnLocalPoint::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemCountOnLocalPoint::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqItemCountOnLocalPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendItemCountOnLocalPoint	*SendBack=GetSendBack(GUICmdSendItemCountOnLocalPoint,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->ItemList.RemoveAll();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->GetLayerAndItemID(LocalX,LocalY,SendBack->ItemList ,LayerList);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdSendItemCountOnLocalPoint::GUICmdSendItemCountOnLocalPoint(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendItemCountOnLocalPoint::Load(QIODevice *f)
{
	if(ItemList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendItemCountOnLocalPoint::Save(QIODevice *f)
{
	if(ItemList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendItemCountOnLocalPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdSelectItemByID::GUICmdSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectItemByID::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(SelectedItem.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectItemByID::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(SelectedItem.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectItemByID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->SelectItemByID(SelectedItem);
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdMoveImage::GUICmdMoveImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FlagMaster=false;
	FlagTarget=false;

	XDir=0;
	YDir=0;
}

bool	GUICmdMoveImage::Load(QIODevice *f)
{
	if(::Load(f,FlagMaster)==false){
		return false;
	}
	if(::Load(f,FlagTarget)==false){
		return false;
	}
	if(::Load(f,XDir)==false){
		return false;
	}
	if(::Load(f,YDir)==false){
		return false;
	}
	return true;
}
bool	GUICmdMoveImage::Save(QIODevice *f)
{
	if(::Save(f,FlagMaster)==false){
		return false;
	}
	if(::Save(f,FlagTarget)==false){
		return false;
	}
	if(::Save(f,XDir)==false){
		return false;
	}
	if(::Save(f,YDir)==false){
		return false;
	}
	return true;
}

void	GUICmdMoveImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	for(int i=0;i<P->GetLayerNumb();i++){
		DataInLayer	*L=P->GetLayerData(i);
		UndoDataInLayer	*UndoPointer=new UndoDataInLayer(L ,&DataInLayer::UndoMoveImage);
		::Save(UndoPointer->GetWritePointer(),FlagMaster);
		::Save(UndoPointer->GetWritePointer(),FlagTarget);
		::Save(UndoPointer->GetWritePointer(),XDir);
		::Save(UndoPointer->GetWritePointer(),YDir);

		if(FlagMaster==true){
			if(XDir<0){
				FlexArea	aArea;
				aArea.SetRectangle(0,0,-XDir,P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetMasterBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			else{
				FlexArea	aArea;
				aArea.SetRectangle(P->GetDotPerLine()-XDir,0,P->GetDotPerLine(),P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetMasterBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			if(YDir<0){
				FlexArea	aArea;
				aArea.SetRectangle(0,0,P->GetDotPerLine(),-YDir);
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetMasterBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			else{
				FlexArea	aArea;
				aArea.SetRectangle(0,P->GetMaxLines()-YDir,P->GetDotPerLine(),P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetMasterBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			L->GetMasterBuff().MoveImage(XDir,YDir);
			L->GetMasterBuff().SetChanged(true);
		}
		if(FlagTarget==true){
			if(XDir<0){
				FlexArea	aArea;
				aArea.SetRectangle(0,0,-XDir,P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetTargetBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			else{
				FlexArea	aArea;
				aArea.SetRectangle(P->GetDotPerLine()-XDir,0,P->GetDotPerLine(),P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetTargetBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			if(YDir<0){
				FlexArea	aArea;
				aArea.SetRectangle(0,0,P->GetDotPerLine(),-YDir);
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetTargetBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			else{
				FlexArea	aArea;
				aArea.SetRectangle(0,P->GetMaxLines()-YDir,P->GetDotPerLine(),P->GetMaxLines());
				FlexAreaImage	UndoAreaImage;
				UndoAreaImage.Set(aArea,L->GetTargetBuff());
				UndoAreaImage.Save(UndoPointer->GetWritePointer());
			}
			L->GetTargetBuff().MoveImage(XDir,YDir);
			L->GetTargetBuff().SetChanged(true);
		}
		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
	}
	SendAck(localPage);
}
//=======================================================================

GUICmdRotateImage::GUICmdRotateImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FlagMaster=false;
	FlagTarget=false;

	Angle=0;
}

bool	GUICmdRotateImage::Load(QIODevice *f)
{
	if(::Load(f,FlagMaster)==false){
		return false;
	}
	if(::Load(f,FlagTarget)==false){
		return false;
	}
	if(::Load(f,Angle)==false){
		return false;
	}
	return true;
}
bool	GUICmdRotateImage::Save(QIODevice *f)
{
	if(::Save(f,FlagMaster)==false){
		return false;
	}
	if(::Save(f,FlagTarget)==false){
		return false;
	}
	if(::Save(f,Angle)==false){
		return false;
	}
	return true;
}

void	GUICmdRotateImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			UndoDataInLayer	*UndoPointer=new UndoDataInLayer(L ,&DataInLayer::UndoRotateImage);
			::Save(UndoPointer->GetWritePointer(),FlagMaster);
			::Save(UndoPointer->GetWritePointer(),FlagTarget);
			::Save(UndoPointer->GetWritePointer(),Angle);

			if(FlagMaster==true){
				L->GetMasterBuff().Save(UndoPointer->GetWritePointer());
				L->GetMasterBuff().RotateImage(P->GetDotPerLine()/2.0,P->GetMaxLines()/2.0,Angle*2.0*M_PI/360.0);
				L->GetMasterBuff().SetChanged(true);
			}
			if(FlagTarget==true){
				L->GetTargetBuff().Save(UndoPointer->GetWritePointer());
				L->GetTargetBuff().RotateImage(P->GetDotPerLine()/2.0,P->GetMaxLines()/2.0,Angle*2.0*M_PI/360.0);
				L->GetTargetBuff().SetChanged(true);
			}
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
	}
	SendAck(localPage);
}
//=======================================================================

GUICmdMirrorXYImage::GUICmdMirrorXYImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	FlagMaster	=false;
	FlagTarget	=false;
	MirrorX		=false;
	MirrorY		=false;
}

bool	GUICmdMirrorXYImage::Load(QIODevice *f)
{
	if(::Load(f,FlagMaster)==false){
		return false;
	}
	if(::Load(f,FlagTarget)==false){
		return false;
	}
	if(::Load(f,MirrorX)==false){
		return false;
	}
	if(::Load(f,MirrorY)==false){
		return false;
	}
	return true;
}
bool	GUICmdMirrorXYImage::Save(QIODevice *f)
{
	if(::Save(f,FlagMaster)==false){
		return false;
	}
	if(::Save(f,FlagTarget)==false){
		return false;
	}
	if(::Save(f,MirrorX)==false){
		return false;
	}
	if(::Save(f,MirrorY)==false){
		return false;
	}
	return true;
}

void	GUICmdMirrorXYImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			UndoDataInLayer	*UndoPointer=new UndoDataInLayer(L ,&DataInLayer::UndoMirrorImage);
			::Save(UndoPointer->GetWritePointer(),FlagMaster);
			::Save(UndoPointer->GetWritePointer(),FlagTarget);
			::Save(UndoPointer->GetWritePointer(),MirrorX);
			::Save(UndoPointer->GetWritePointer(),MirrorY);

			if(FlagMaster==true){
				L->GetMasterBuff().Save(UndoPointer->GetWritePointer());
				if(MirrorX==true && MirrorY==false){
					L->GetMasterBuff().LeftsideRight();
					L->GetMasterBuff().SetChanged(true);
				}
				else
				if(MirrorX==false && MirrorY==true){
					L->GetMasterBuff().TopsideBottom();
					L->GetMasterBuff().SetChanged(true);
				}
				else
				if(MirrorX==true && MirrorY==true){
					L->GetMasterBuff().TopsideBottomLeftsideRight();
					L->GetMasterBuff().SetChanged(true);
				}
			}
			if(FlagTarget==true){
				L->GetTargetBuff().Save(UndoPointer->GetWritePointer());
				if(MirrorX==true && MirrorY==false){
					L->GetTargetBuff().LeftsideRight();
					L->GetTargetBuff().SetChanged(true);
				}
				else
				if(MirrorX==false && MirrorY==true){
					L->GetTargetBuff().TopsideBottom();
					L->GetTargetBuff().SetChanged(true);
				}
				else
				if(MirrorX==true && MirrorY==true){
					L->GetTargetBuff().TopsideBottomLeftsideRight();
					L->GetTargetBuff().SetChanged(true);
				}
			}
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdCopyImageInPhases::GUICmdCopyImageInPhases(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SrcPhase	=0;
	DstPhase	=0;
	FlagMaster=false;
	FlagTarget=false;
}

bool	GUICmdCopyImageInPhases::Load(QIODevice *f)
{
	if(::Load(f,FlagMaster)==false){
		return false;
	}
	if(::Load(f,FlagTarget)==false){
		return false;
	}
	if(::Load(f,SrcPhase)==false){
		return false;
	}
	if(::Load(f,DstPhase)==false){
		return false;
	}

	return true;
}
bool	GUICmdCopyImageInPhases::Save(QIODevice *f)
{
	if(::Save(f,FlagMaster)==false){
		return false;
	}
	if(::Save(f,FlagTarget)==false){
		return false;
	}
	if(::Save(f,SrcPhase)==false){
		return false;
	}
	if(::Save(f,DstPhase)==false){
		return false;
	}

	return true;
}

void	GUICmdCopyImageInPhases::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	UndoDataInPage	*UndoPointer=new UndoDataInPage(P ,&DataInPage::UndoCopyImageInPhases);
	::Save(UndoPointer->GetWritePointer(),SrcPhase);
	::Save(UndoPointer->GetWritePointer(),DstPhase);
	int	LayerNumb=P->GetLayerNumb();
	::Save(UndoPointer->GetWritePointer(),LayerNumb);
	::Save(UndoPointer->GetWritePointer(),FlagMaster);
	::Save(UndoPointer->GetWritePointer(),FlagTarget);

	if(0<=SrcPhase && SrcPhase<GetPhaseNumb() && 0<=DstPhase && DstPhase<GetPhaseNumb()){
		PageDataInOnePhase	*PhSrc=GetLayersBase()->GetPageDataPhase(SrcPhase);
		PageDataInOnePhase	*PhDst=GetLayersBase()->GetPageDataPhase(DstPhase);
		DataInPage *PageSrc=PhSrc->GetPageData(localPage);
		DataInPage *PageDst=PhDst->GetPageData(localPage);
		for(int Layer=0;Layer<PageSrc->GetLayerNumb() && PageDst->GetLayerNumb();Layer++){
			DataInLayer	*LySrc=PageSrc->GetLayerData(Layer);
			DataInLayer	*LyDst=PageDst->GetLayerData(Layer);

			if(FlagMaster==true){
				LyDst->GetMasterBuff().Save(UndoPointer->GetWritePointer());
				LyDst->GetMasterBuff()	=	LySrc->GetMasterBuff();
				LyDst->GetMasterBuff().SetChanged(true);
			}

			if(FlagTarget==true){
				LyDst->GetTargetBuff().Save(UndoPointer->GetWritePointer());
				LyDst->GetTargetBuff()	=	LySrc->GetTargetBuff();
				LyDst->GetTargetBuff().SetChanged(true);
			}
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

	SendAck(localPage);
}
//=======================================================================

GUICmdSwapImage::GUICmdSwapImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSwapImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			ImageBuffer	Tmp(0,L->GetMasterBuff().GetWidth(),L->GetMasterBuff().GetHeight());
			Tmp=L->GetMasterBuff();
			L->GetMasterBuff()=L->GetTargetBuff();
			L->GetTargetBuff()=Tmp;
			L->GetMasterBuff().SetChanged(true);
			L->GetTargetBuff().SetChanged(true);
			if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
				L->CopyTargetImageToRaw();
			}	
		}
	}

	SendAck(localPage);
}
//=======================================================================
GUICmdNegPosImage::GUICmdNegPosImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdNegPosImage::Load(QIODevice *f)
{
	if(::Load(f,MasterBuff)==false){
		return false;
	}
	if(::Load(f,TargetBuff)==false){
		return false;
	}
	return true;
}
bool	GUICmdNegPosImage::Save(QIODevice *f)
{
	if(::Save(f,MasterBuff)==false){
		return false;
	}
	if(::Save(f,TargetBuff)==false){
		return false;
	}
	return true;
}

void	GUICmdNegPosImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			if(MasterBuff==true){
				L->GetMasterBuff().ConvertNegPos();
				L->GetMasterBuff().SetChanged(true);
			}
			if(TargetBuff==true){
				L->GetTargetBuff().ConvertNegPos();
				L->GetTargetBuff().SetChanged(true);
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdCopyImageToTarget::GUICmdCopyImageToTarget(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdCopyImageToTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			L->GetTargetBuff()=L->GetMasterBuff();
			L->GetTargetBuff().SetChanged(true);
			if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
				L->CopyTargetImageToRaw();
			}	
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdCopyImageToBackGround::GUICmdCopyImageToBackGround(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdCopyImageToBackGround::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			L->GetBackGroundBuff()=L->GetTargetBuff();
			L->GetBackGroundBuff().SetChanged(true);	
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdCopyImageToMaster::GUICmdCopyImageToMaster(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdCopyImageToMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			L->GetMasterBuff()=L->GetTargetBuff();
			L->GetMasterBuff().SetChanged(true);
		}
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdCopyImageToMasterBuffN::GUICmdCopyImageToMasterBuffN(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SourceMaster=false;
	MasterNo	=-1;
	SwapMode	=false;
}
bool	GUICmdCopyImageToMasterBuffN::Load(QIODevice *f)
{
	if(::Load(f,SourceMaster)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	if(::Load(f,SwapMode)==false){
		return false;
	}
	return true;
}
bool	GUICmdCopyImageToMasterBuffN::Save(QIODevice *f)
{
	if(::Save(f,SourceMaster)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	if(::Save(f,SwapMode)==false){
		return false;
	}
	return true;
}
void	GUICmdCopyImageToMasterBuffN::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	if(MasterNo>=0){
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
			DataInPage	*P=Dh->GetPageData(localPage);
			for(int i=0;i<P->GetLayerNumb();i++){
				DataInLayer	*L=P->GetLayerData(i);
				if(SourceMaster==false && SwapMode==false){
					L->GetMasterBuff(MasterNo)=L->GetTargetBuff();
					L->GetMasterBuff(MasterNo).SetChanged(true);
				}
				else if(SourceMaster==true && SwapMode==false){
					L->GetMasterBuff(MasterNo)=L->GetMasterBuff();
					L->GetMasterBuff(MasterNo).SetChanged(true);
				}
				else if(SourceMaster==false && SwapMode==true){
					L->GetMasterBuff(MasterNo).Swap(L->GetTargetBuff());
					L->GetTargetBuff().SetChanged(true);
					L->GetMasterBuff(MasterNo).SetChanged(true);
				}
				else if(SourceMaster==true && SwapMode==true){
					L->GetMasterBuff(MasterNo).Swap(L->GetMasterBuff());
					L->GetMasterBuff().SetChanged(true);
					L->GetMasterBuff(MasterNo).SetChanged(true);
				}
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================

GUICmdTranspositionTarget::GUICmdTranspositionTarget(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdTranspositionTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntList PhaseList;
	ActivePhaseList(PhaseList);
	for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
		int phase=v->GetValue();
		PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage	*P=Dh->GetPageData(localPage);
		if(GetParamGlobal()->AllocateTargetTRBuff==true){
			for(int i=0;i<P->GetLayerNumb();i++){
				DataInLayer	*L=P->GetLayerData(i);
				L->GetTargetTRBuff().TranspositionXY(L->GetTargetBuff());
				L->GetTargetTRBuff().SetChanged(true);
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdClearImage::GUICmdClearImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Mastered=0;
	TargetPhase=-1;
}

bool	GUICmdClearImage::Load(QIODevice *f)
{
	if(::Load(f,Mastered)==false){
		return false;
	}
	if(::Load(f,Color)==false){
		return false;
	}
	if(::Load(f,TargetPhase)==false){
		return false;
	}
	return true;
}
bool	GUICmdClearImage::Save(QIODevice *f)
{
	if(::Save(f,Mastered)==false){
		return false;
	}
	if(::Save(f,Color)==false){
		return false;
	}
	if(::Save(f,TargetPhase)==false){
		return false;
	}
	return true;
}

void	GUICmdClearImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(TargetPhase<0){
		for(int ph=0;ph<GetPhaseNumb();ph++){
			PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(ph);
			ClearImage(Ph,localPage);
		}
	}
	else{
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(TargetPhase);
		ClearImage(Ph,localPage);
	}
}

void	GUICmdClearImage::ClearImage(PageDataInOnePhase *Ph,int32 localPage)
{
	DataInPage	*P=Ph->GetPageData(localPage);
	if(P->GetLayerNumb()==1){
		DataInLayer	*L=P->GetLayerData(0);
		if(Mastered==0){
			L->GetMasterBuff().Memset(Color.red());
			L->GetMasterBuff().SetChanged(true);
		}
		else if(Mastered==1){
			L->GetTargetBuff().Memset(Color.red());
			L->GetTargetBuff().SetChanged(true);
		}
		else if(Mastered==3){
			L->GetBackGroundBuff().Memset(Color.red());
			L->GetBackGroundBuff().SetChanged(true);
		}
		else if(Mastered==2){
			L->GetBitBuff().Memset(0);
			L->GetBitBuff().SetChanged(true);
		}
	}
	else if(P->GetLayerNumb()==3){
		DataInLayer	*Lr=P->GetLayerData(0);
		DataInLayer	*Lg=P->GetLayerData(1);
		DataInLayer	*Lb=P->GetLayerData(2);
		if(Mastered==0){
			Lr->GetMasterBuff().Memset(Color.red());
			Lg->GetMasterBuff().Memset(Color.green());
			Lb->GetMasterBuff().Memset(Color.blue());
			Lr->GetMasterBuff().SetChanged(true);
			Lg->GetMasterBuff().SetChanged(true);
			Lb->GetMasterBuff().SetChanged(true);
		}
		else if(Mastered==1){
			Lr->GetTargetBuff().Memset(Color.red());
			Lg->GetTargetBuff().Memset(Color.green());
			Lb->GetTargetBuff().Memset(Color.blue());
			Lr->GetTargetBuff().SetChanged(true);
			Lg->GetTargetBuff().SetChanged(true);
			Lb->GetTargetBuff().SetChanged(true);
		}
		else if(Mastered==3){
			Lr->GetBackGroundBuff().Memset(Color.red());
			Lg->GetBackGroundBuff().Memset(Color.green());
			Lb->GetBackGroundBuff().Memset(Color.blue());
			Lr->GetBackGroundBuff().SetChanged(true);
			Lg->GetBackGroundBuff().SetChanged(true);
			Lb->GetBackGroundBuff().SetChanged(true);
		}
		else if(Mastered==2){
			Lr->GetBitBuff().Memset(0);
			Lg->GetBitBuff().Memset(0);
			Lb->GetBitBuff().Memset(0);
			Lr->GetBitBuff().SetChanged(true);
			Lg->GetBitBuff().SetChanged(true);
			Lb->GetBitBuff().SetChanged(true);
		}
	}
	else{
		for(int i=0;i<P->GetLayerNumb();i++){
			DataInLayer	*L=P->GetLayerData(i);
			if(Mastered==0){
				L->GetMasterBuff().Memset(Color.red());
				L->GetMasterBuff().SetChanged(true);
			}
			else if(Mastered==1){
				L->GetTargetBuff().Memset(Color.red());
				L->GetTargetBuff().SetChanged(true);
			}
			else if(Mastered==3){
				L->GetBackGroundBuff().Memset(Color.red());
				L->GetBackGroundBuff().SetChanged(true);
			}
			else if(Mastered==2){
				L->GetBitBuff().Memset(0);
				L->GetBitBuff().SetChanged(true);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================

GUICmdReqSelectByOrigin::GUICmdReqSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSelectByOrigin::Load(QIODevice *f)
{	
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;	
}
bool	GUICmdReqSelectByOrigin::Save(QIODevice *f)
{	
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;	
}

void	GUICmdReqSelectByOrigin::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectByOrigin	*SendBack=GetSendBack(GUICmdAckSelectByOrigin,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->OriginNameList.RemoveAll();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->GetOriginRootNames(SendBack->OriginNameList ,LayerList);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectByOrigin::GUICmdAckSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckSelectByOrigin::Load(QIODevice *f)
{	
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	OriginNameList.RemoveAll();
	for(int i=0;i<N;i++){
		OriginNames *v= new OriginNames();
		if(v->Load(f)==false){
			return false;
		}
		OriginNameList.AppendList(v);
	}
	return true;	
}
bool	GUICmdAckSelectByOrigin::Save(QIODevice *f)
{	
	int32	N=OriginNameList.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(OriginNames *v=OriginNameList.GetFirst();v!=NULL;v=v->GetNext()){
		if(v->Save(f)==false){
			return false;
		}
	}

	return true;	
}

void	GUICmdAckSelectByOrigin::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdSelectByOrigin::GUICmdSelectByOrigin(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectByOrigin::Load(QIODevice *f)
{
	if(Names.Load(f)==false){
		return false;
	}
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,OriginDLLRoot)==false){
		return false;
	}
	if(::Load(f,OriginDLLName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectByOrigin::Save(QIODevice *f)
{
	if(Names.Save(f)==false){
		return false;
	}
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,OriginDLLRoot)==false){
		return false;
	}
	if(::Save(f,OriginDLLName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectByOrigin::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	AlgorithmBase	*Sb=GetLayersBase()->GetAlgorithmBase(OriginDLLRoot ,OriginDLLName);

	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			//AlgorithmInPageInOnePhase	*Sh=Sb->GetPageDataPhase(phase);
			if(Ah!=NULL && Sb!=NULL){
				AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
				if(Ap!=NULL){
					Ap->SelectOriginRootNames(Sb ,LayerList);	//Sb:No problem in function
				}
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdVisibleAll::GUICmdVisibleAll(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}
bool	GUICmdVisibleAll::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,Visible)==false){
		return false;
	}
	return true;
}

bool	GUICmdVisibleAll::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,Visible)==false){
		return false;
	}
	return true;
}

void	GUICmdVisibleAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);

	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				if(Visible==true){
					Ap->VisibleAll(LayerList);
				}
				else{
					Ap->InvisibleAll(LayerList);
				}
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdInvisibleSelected::GUICmdInvisibleSelected(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}
bool	GUICmdInvisibleSelected::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdInvisibleSelected::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdInvisibleSelected::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);

	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->InvisibleSelected(LayerList);
			}
		}
	}
	SendAck(localPage);
}
//=======================================================================
GUICmdSelectManualCreature::GUICmdSelectManualCreature(AlgorithmBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}
bool	GUICmdSelectManualCreature::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdSelectManualCreature::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectManualCreature::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);

	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectManualCreature(LayerList);
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdReqExpandedPaste::GUICmdReqExpandedPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqExpandedPaste::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Px1)==false){
		return false;
	}
	if(::Load(f,Py1)==false){
		return false;
	}
	if(::Load(f,Px2)==false){
		return false;
	}
	if(::Load(f,Py2)==false){
		return false;
	}
	if(::Load(f,Px3)==false){
		return false;
	}
	if(::Load(f,Py3)==false){
		return false;
	}
	if(::Load(f,Px4)==false){
		return false;
	}
	if(::Load(f,Py4)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Mode=(PasteMode)N;
	if(PastedLayer.Load(f)==false){
		return false;
	}
	if(::Load(f,Dx)==false){
		return false;
	}
	if(::Load(f,Dy)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqExpandedPaste::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Px1)==false){
		return false;
	}
	if(::Save(f,Py1)==false){
		return false;
	}
	if(::Save(f,Px2)==false){
		return false;
	}
	if(::Save(f,Py2)==false){
		return false;
	}
	if(::Save(f,Px3)==false){
		return false;
	}
	if(::Save(f,Py3)==false){
		return false;
	}
	if(::Save(f,Px4)==false){
		return false;
	}
	if(::Save(f,Py4)==false){
		return false;
	}
	int32	N=(int)Mode;
	if(::Save(f,N)==false){
		return false;
	}
	if(PastedLayer.Save(f)==false){
		return false;
	}
	if(::Save(f,Dx)==false){
		return false;
	}
	if(::Save(f,Dy)==false){
		return false;
	}
	return true;
}

void	GUICmdReqExpandedPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*A=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(A!=NULL){
		AlgorithmInPageRoot	*Ap=A->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->ExecutePasteFromSelected(PastedLayer,Dx,Dy);
		}
	}
}

//=======================================================================
GUICmdReqSelectedItemListsForPaste::GUICmdReqSelectedItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedItemListsForPaste::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSelectedItemListsForPaste::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSelectedItemListsForPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSelectedItemListsForPaste	*SendBack=GetSendBack(GUICmdSendSelectedItemListsForPaste,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		Ap->SelectedItemListsForPaste(LayerList,SendBack->Lists);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSelectedItemListsForPaste::GUICmdSendSelectedItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSelectedItemListsForPaste::Load(QIODevice *f)
{
	if(Lists.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendSelectedItemListsForPaste::Save(QIODevice *f)
{
	if(Lists.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSendSelectedItemListsForPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================
GUICmdReqDrawItemListsForPaste::GUICmdReqDrawItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqDrawItemListsForPaste::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,ZoomRate)==false){
		return false;
	}
	if(::Load(f,movx)==false){
		return false;
	}
	if(::Load(f,movy)==false){
		return false;
	}
	if(::Load(f,Width)==false){
		return false;
	}
	if(::Load(f,Height)==false){
		return false;
	}
	if(::Load(f,SourceCenterX)==false){
		return false;
	}
	if(::Load(f,SourceCenterY)==false){
		return false;
	}
	if(SelectedItemLists.Load(f)==false){
		return false;
	}
	if(ExpandedItems.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqDrawItemListsForPaste::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,ZoomRate)==false){
		return false;
	}
	if(::Save(f,movx)==false){
		return false;
	}
	if(::Save(f,movy)==false){
		return false;
	}
	if(::Save(f,Width)==false){
		return false;
	}
	if(::Save(f,Height)==false){
		return false;
	}
	if(::Save(f,SourceCenterX)==false){
		return false;
	}
	if(::Save(f,SourceCenterY)==false){
		return false;
	}
	if(SelectedItemLists.Save(f)==false){
		return false;
	}
	if(ExpandedItems.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqDrawItemListsForPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendDrawItemListsForPaste	*SendBack=GetSendBack(GUICmdSendDrawItemListsForPaste,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		SendBack->Width=Width;
		SendBack->Height=Height;
		SendBack->Image=new QImage(SendBack->Width,SendBack->Height,QImage::Format_ARGB32);
		//SendBack->Image->fill(0);
		::ClearImage(*SendBack->Image, 0);
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		int	n=0;
		for(DisplayImage::ExpandedItemPos *e=ExpandedItems.GetFirst();e!=NULL;e=e->GetNext()){
			double	Cx,Cy;
			e->GetCenter(Cx ,Cy);
			//for(ExpandedSelectedItemList *p=SelectedItemLists.GetFirst();p!=NULL;p=p->GetNext()){
			for(int i=0;i<SelectedItemLists.GetCount();i++){
				ExpandedSelectedItemList *p=SelectedItemLists.Get(i);
				Ap->DrawItemListsForPaste(-SourceCenterX,-SourceCenterY,*SendBack->Image,p->Layer,p->ItemID,ZoomRate ,movx+Cx ,movy+Cy,n);
				n++;
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendDrawItemListsForPaste::GUICmdSendDrawItemListsForPaste(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Image=NULL;
}
GUICmdSendDrawItemListsForPaste::~GUICmdSendDrawItemListsForPaste(void)
{
	if(Image!=NULL){
		delete	Image;
		Image=NULL;
	}
}

bool	GUICmdSendDrawItemListsForPaste::Load(QIODevice *f)
{
	if(::Load(f,Width)==false){
		return false;
	}
	if(::Load(f,Height)==false){
		return false;
	}

	if(Image!=NULL){
		delete	Image;
	}
	Image=new QImage(Width,Height,QImage::Format_ARGB32);
	//Image->fill(0);
	::ClearImage(*Image, 0);
	Image->load(f,/**/"PNG");
	return true;
}
bool	GUICmdSendDrawItemListsForPaste::Save(QIODevice *f)
{
	Image->save(f,/**/"PNG");
	if(::Save(f,Width)==false){
		return false;
	}
	if(::Save(f,Height)==false){
		return false;
	}
	return true;
}
void	GUICmdSendDrawItemListsForPaste::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

GUICmdReqSavingImage::GUICmdReqSavingImage(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Mastered=true;
}
bool	GUICmdReqSavingImage::Load(QIODevice *f)
{
	if(::Load(f,MinX)==false){
		return false;
	}
	if(::Load(f,MinY)==false){
		return false;
	}
	if(::Load(f,MaxX)==false){
		return false;
	}
	if(::Load(f,MaxY)==false){
		return false;
	}
	if(::Load(f,Mastered)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSavingImage::Save(QIODevice *f)
{
	if(::Save(f,MinX)==false){
		return false;
	}
	if(::Save(f,MinY)==false){
		return false;
	}
	if(::Save(f,MaxX)==false){
		return false;
	}
	if(::Save(f,MaxY)==false){
		return false;
	}
	if(::Save(f,Mastered)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSavingImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSavingImage	*SendBack=GetSendBack(GUICmdAckSavingImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	QImage	Img(MaxX-MinX,MaxY-MinY,QImage::Format_RGB32);
	int	LY=0;
	if(GetLayerNumb(localPage)==1){
		DataInLayer	*Lr=GetLayersBase()->GetPageData(localPage)->GetLayerData(0);
		ImageBuffer	*Gr;
		if(Mastered==true){
			Gr=&Lr->GetMasterBuff();
		}
		else{
			Gr=&Lr->GetTargetBuff();
		}
	
		for(int y=MinY;y<MaxY;y++,LY++){
			BYTE	*Dst=Img.scanLine(LY);
			BYTE	*Sr=Gr->GetY(y);
			for(int x=MinX;x<MaxX;x++){
				*(Dst+0)	=Sr[x];
				*(Dst+1)	=Sr[x];
				*(Dst+2)	=Sr[x];
				Dst+=4;
			}
		}
	}
	else if(GetLayerNumb(localPage)==2){
		DataInLayer	*Lr=GetLayersBase()->GetPageData(localPage)->GetLayerData(0);
		DataInLayer	*Lg=GetLayersBase()->GetPageData(localPage)->GetLayerData(1);
		ImageBuffer	*Gr;
		ImageBuffer	*Gg;
		if(Mastered==true){
			Gr=&Lr->GetMasterBuff();
			Gg=&Lg->GetMasterBuff();
		}
		else{
			Gr=&Lr->GetTargetBuff();
			Gg=&Lg->GetTargetBuff();
		}
	
		for(int y=MinY;y<MaxY;y++,LY++){
			BYTE	*Dst=Img.scanLine(LY);
			BYTE	*Sr=Gr->GetY(y);
			BYTE	*Sg=Gg->GetY(y);
			for(int x=MinX;x<MaxX;x++){
				*(Dst+0)	=Sg[x];
				*(Dst+1)	=Sg[x];
				*(Dst+2)	=Sr[x];
				Dst+=4;
			}
		}
	}
	else if(GetLayerNumb(localPage)>=3){
		DataInLayer	*Lr=GetLayersBase()->GetPageData(localPage)->GetLayerData(0);
		DataInLayer	*Lg=GetLayersBase()->GetPageData(localPage)->GetLayerData(1);
		DataInLayer	*Lb=GetLayersBase()->GetPageData(localPage)->GetLayerData(2);
		ImageBuffer	*Gr;
		ImageBuffer	*Gg;
		ImageBuffer	*Gb;
		if(Mastered==true){
			Gr=&Lr->GetMasterBuff();
			Gg=&Lg->GetMasterBuff();
			Gb=&Lb->GetMasterBuff();
		}
		else{
			Gr=&Lr->GetTargetBuff();
			Gg=&Lg->GetTargetBuff();
			Gb=&Lb->GetTargetBuff();
		}
	
		for(int y=MinY;y<MaxY;y++,LY++){
			BYTE	*Dst=Img.scanLine(LY);
			BYTE	*Sr=Gr->GetY(y);
			BYTE	*Sg=Gg->GetY(y);
			BYTE	*Sb=Gb->GetY(y);
			for(int x=MinX;x<MaxX;x++){
				*(Dst+0)	=Sb[x];
				*(Dst+1)	=Sg[x];
				*(Dst+2)	=Sr[x];
				Dst+=4;
			}
		}
	}
	SendBack->Img=Img;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSavingImage::GUICmdAckSavingImage(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckSavingImage::Load(QIODevice *f)
{
	if(Img.load(f,/**/"PNG")==false){
		return false;
	}
	return true;
}
bool	GUICmdAckSavingImage::Save(QIODevice *f)
{
	if(Img.save(f,/**/"PNG")==false){
		return false;
	}
	return true;
}

void	GUICmdAckSavingImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================

bool	AvrVarListByLayer::Save(QIODevice *f)
{
	if(::Save(f,Average)==false){
		return false;
	}
	if(::Save(f,Dispersion)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}

bool	AvrVarListByLayer::Load(QIODevice *f)
{
	if(::Load(f,Average)==false){
		return false;
	}
	if(::Load(f,Dispersion)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}

bool	AvrVarListByLayerContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(AvrVarListByLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	AvrVarListByLayerContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		AvrVarListByLayer *L=new AvrVarListByLayer();
		if(L->Load(f)==false){
			return false;
		}
		AppendList(L);
	}
	return true;
}

AvrVarListByLayerContainer	&AvrVarListByLayerContainer::operator=(AvrVarListByLayerContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}


bool	HistgramList::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false){
		return false;
	}
	if(f->write((const char *)BrightList,sizeof(BrightList))!=sizeof(BrightList)){
		return false;
	}
	return true;
}

bool	HistgramList::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false){
		return false;
	}
	if(f->read((char *)BrightList,sizeof(BrightList))!=sizeof(BrightList)){
		return false;
	}
	return true;
}


bool	HistgramListContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(HistgramList *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	HistgramListContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		HistgramList *L=new HistgramList();
		if(L->Load(f)==false){
			return false;
		}
		AppendList(L);
	}
	return true;
}

HistgramListContainer	&HistgramListContainer::operator=(HistgramListContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

GUICmdRegulateBrightness::GUICmdRegulateBrightness(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ImageType	=DisplayImage::__Master;
	MasterNo	=0;
}

bool	GUICmdRegulateBrightness::Load(QIODevice *f)
{
	if(AvrDatas.Load(f)==false){
		return false;
	}
	if(::Load(f,BlockSize)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	BYTE	N;
	if(::Load(f,N)==false){
		return false;
	}
	ImageType=(DisplayImage::DisplayType)N;
	if(Area.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdRegulateBrightness::Save(QIODevice *f)
{
	if(AvrDatas.Save(f)==false){
		return false;
	}
	if(::Save(f,BlockSize)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	BYTE	N=(BYTE)ImageType;
	if(::Save(f,N)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdRegulateBrightness::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(AvrVarListByLayer *c=AvrDatas.GetFirst();c!=NULL;c=c->GetNext()){
		DataInLayer	*L=GetLayersBase()->GetPageData(localPage)->GetLayerData(c->Layer);
		if((ImageType&DisplayImage::__Master)!=0){
			Area.RegulateBrightness(L->GetMasterBuff(MasterNo),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetMasterBuff(MasterNo).SetChanged(true);
		}
		else if((ImageType&DisplayImage::__Target)!=0){
			Area.RegulateBrightness(L->GetTargetBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetTargetBuff().SetChanged(true);
		}
		else if((ImageType&DisplayImage::__BackGround)!=0){
			Area.RegulateBrightness(L->GetBackGroundBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetTargetBuff().SetChanged(true);
		}
		else if((ImageType&DisplayImage::__TargetTR)!=0){
			Area.RegulateBrightness(L->GetTargetTRBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetTargetTRBuff().SetChanged(true);
		}
		else if((ImageType&DisplayImage::__DelayedView)!=0){
			Area.RegulateBrightness(L->GetDelayedViewBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetDelayedViewBuff().SetChanged(true);
		}
		else if((ImageType&DisplayImage::__RawTarget)!=0){
			Area.RegulateBrightness(L->GetRawTargetBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetRawTargetBuff().SetChanged(true);
		}
		else if((ImageType&DisplayImage::__CamTarget)!=0){
			Area.RegulateBrightness(L->GetCamTargetBuff(),c->Average,c->Dispersion,BlockSize
									,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			L->GetCamTargetBuff().SetChanged(true);
		}
	}
	SendAck(localPage);
}


GUICmdGetAvrVar::GUICmdGetAvrVar(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ImageType	=DisplayImage::__Master;
	MasterNo	=0;
}

bool	GUICmdGetAvrVar::Load(QIODevice *f)
{
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,BlockSize)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	BYTE	N;
	if(::Load(f,N)==false){
		return false;
	}
	ImageType=(DisplayImage::DisplayType)N;
	if(Area.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdGetAvrVar::Save(QIODevice *f)
{
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,BlockSize)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	BYTE	N=(BYTE)ImageType;
	if(::Save(f,N)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdGetAvrVar::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAvrVar	*SendBack=GetSendBack(GUICmdAckAvrVar,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->HistDatas.RemoveAll();
	SendBack->AvrDatas.RemoveAll();
	DataInPage *P=GetLayersBase()->GetPageData(localPage);

	for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
		AvrVarListByLayer	*a=new AvrVarListByLayer();
		HistgramList		*h=new HistgramList();
		DataInLayer	*L=P->GetLayerData(c->GetValue());
		a->Average=0;
		a->Dispersion=0;
		if((ImageType&DisplayImage::__Master)!=0){
			Area.CalcAvrVar(0,0,L->GetMasterBuff(MasterNo),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines() ,L->GetMasterBuff(MasterNo));
		}
		else if((ImageType&DisplayImage::__BackGround)!=0){
			Area.CalcAvrVar(0,0,L->GetBackGroundBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetTargetBuff());
		}
		else if((ImageType&DisplayImage::__Target)!=0){
			Area.CalcAvrVar(0,0,L->GetTargetBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetTargetBuff());
		}
		else if((ImageType&DisplayImage::__TargetTR)!=0){
			Area.CalcAvrVar(0,0,L->GetTargetTRBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetTargetTRBuff());
		}
		else if((ImageType&DisplayImage::__DelayedView)!=0){
			Area.CalcAvrVar(0,0,L->GetDelayedViewBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetDelayedViewBuff());
		}
		else if((ImageType&DisplayImage::__RawTarget)!=0){
			Area.CalcAvrVar(0,0,L->GetRawTargetBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetRawTargetBuff());
		}
		else if((ImageType&DisplayImage::__CamTarget)!=0){
			Area.CalcAvrVar(0,0,L->GetCamTargetBuff(),a->Average ,a->Dispersion
							,GetParamGlobal()->AdoptRateLForAvr,GetParamGlobal()->AdoptRateHForAvr);
			Area.MakeBrightList(h->BrightList ,P->GetDotPerLine(),P->GetMaxLines(),L->GetCamTargetBuff());
		}
		SendBack->HistDatas.AppendList(h);
		SendBack->AvrDatas.AppendList(a);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckAvrVar::GUICmdAckAvrVar(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckAvrVar::Load(QIODevice *f)
{
	if(HistDatas.Load(f)==false){
		return false;
	}
	if(AvrDatas.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckAvrVar::Save(QIODevice *f)
{
	if(HistDatas.Save(f)==false){
		return false;
	}
	if(AvrDatas.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdAckAvrVar::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

GUICmdSwapRawToTarget::GUICmdSwapRawToTarget(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdSwapRawToTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage *P=GetLayersBase()->GetPageData(localPage);
	ImageBuffer	TmpBuff(0,P->GetDotPerLine(),P->GetMaxLines());
	for(int Ly=0;Ly<GetLayerNumb(localPage);Ly++){
		DataInLayer	*Lr=GetLayersBase()->GetPageData(localPage)->GetLayerData(Ly);
		TmpBuff=Lr->GetRawTargetBuff();
		Lr->GetRawTargetBuff()=Lr->GetTargetBuff();
		Lr->GetRawTargetBuff().SetChanged(true);
		Lr->GetTargetBuff()=TmpBuff;
		Lr->GetTargetBuff().SetChanged(true);
	}
	SendAck(localPage);
}

GUICmdCopyRawToTarget::GUICmdCopyRawToTarget(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdCopyRawToTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int Ly=0;Ly<GetLayerNumb(localPage);Ly++){
		DataInLayer	*Lr=GetLayersBase()->GetPageData(localPage)->GetLayerData(Ly);
		Lr->GetTargetBuff()=Lr->GetRawTargetBuff();
		Lr->GetTargetBuff().SetChanged(true);
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdGetColorSample::GUICmdGetColorSample(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MasterNo=0;
}

bool	GUICmdGetColorSample::Load(QIODevice *f)
{
	BYTE	D;

	if(::Load(f,D)==false){
		return false;
	}
	ImageType=(DisplayImage::DisplayType)D;
	if(Area.Load(f)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	return true;
}
bool	GUICmdGetColorSample::Save(QIODevice *f)
{
	BYTE	D=(BYTE)ImageType;

	if(::Save(f,D)==false){
		return false;
	}
	if(Area.Save(f)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	return true;
}

void	GUICmdGetColorSample::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorSample	*SendBack=GetSendBack(GUICmdAckColorSample,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	if(Pg!=NULL){
		ImagePointerContainer Images;
		if((ImageType&DisplayImage::__Master)!=0){
			Pg->GetMasterImages(MasterNo,Images);
		}
		else if((ImageType&DisplayImage::__BackGround)!=0){
			Pg->GetTargetImages(Images);
		}
		else if((ImageType&DisplayImage::__Target)!=0){
			Pg->GetTargetImages(Images);
		}
		else if((ImageType&DisplayImage::__TargetTR)!=0){
			Pg->GetTargetTRImages(Images);
		}
		else if((ImageType&DisplayImage::__DelayedView)!=0){
			Pg->GetDelayedViewImages(Images);
		}
		else if((ImageType&DisplayImage::__RawTarget)!=0){
			Pg->GetRawTargetImages(Images);
		}
		else if((ImageType&DisplayImage::__CamTarget)!=0){
			Pg->GetCamTargetImages(Images);
		}
		else{
			return;
		}
		SendBack->MakeData(Images,Area);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorSample::GUICmdAckColorSample(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckColorSample::Load(QIODevice *f)
{
	if(ColorSample.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckColorSample::Save(QIODevice *f)
{
	if(ColorSample.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdAckColorSample::MakeData(ImagePointerContainer &Images,FlexArea &Area)
{
	Area.CreateRGBStock(Images, ColorSample);
}

void	GUICmdAckColorSample::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
//=======================================================================

GUICmdReqRatate::GUICmdReqRatate(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}
bool	GUICmdReqRatate::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Angle)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqRatate::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Angle)==false){
		return false;
	}
	return true;
}

void	GUICmdReqRatate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			DotListContainer CenterBylayer;
			if(Ap->GetSelectedCenter(CenterBylayer)==true){
				int	Cx=0;
				int	Cy=0;
				int	N=0;
				for(DotList *d=CenterBylayer.GetFirst();d!=NULL;d=d->GetNext()){
					Cx+=d->GetX();
					Cy+=d->GetY();
					N++;
				}
				if(N!=0){
					Cx/=N;
					Cy/=N;
					Ap->RotateItem(Angle,Cx,Cy);
				}
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdReqSelectedItems::GUICmdReqSelectedItems(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedItems::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;

}
bool	GUICmdReqSelectedItems::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSelectedItems::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectedItems	*SendBack=GetSendBack(GUICmdAckSelectedItems,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			AlgorithmItemPointerListContainer ItemPointers;
			Ap->GetSelectedItems(ItemPointers);
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);

			int32	Numb=ItemPointers.GetCount();
			::Save(&Buff,Numb);
			for(AlgorithmItemPointerList *p=ItemPointers.GetFirst();p!=NULL;p=p->GetNext()){
				int32	Layer=p->GetItem()->GetLayer();
				::Save(&Buff,Layer);
				int32	ItemClassType=p->GetItem()->GetItemClassType();
				::Save(&Buff,ItemClassType);
				p->GetItem()->Save(&Buff);
			}
			SendBack->BuffData=Buff.buffer();
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectedItems::GUICmdAckSelectedItems(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdAckSelectedItems::Load(QIODevice *f)
{
	if(::Load(f,BuffData)==false)
		return false;
	return true;
}
bool	GUICmdAckSelectedItems::Save(QIODevice *f)
{
	if(::Save(f,BuffData)==false)
		return false;
	return true;
}

//=======================================================================
GUICmdReqMirror::GUICmdReqMirror(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
	BuffData=NULL;
	PageNumb=0;
}

GUICmdReqMirror::~GUICmdReqMirror(void)
{
	if(BuffData!=NULL){
		delete	[]BuffData;
		BuffData=NULL;
	}
	PageNumb=0;
}

bool	GUICmdReqMirror::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,PageNumb)==false){
		return false;
	}
	if(BuffData!=NULL){
		delete	[]BuffData;
		BuffData=NULL;
	}
	BuffData=new QByteArray[PageNumb];
	for(int n=0;n<PageNumb;n++){
		if(::Load(f,BuffData[n])==false)
			return false;
	}
	BYTE	D;
	if(::Load(f,D)==false){
		return false;
	}
	MirrorMode=(AlgorithmItemRoot::_MirrorMode)D;
	return true;

}
bool	GUICmdReqMirror::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,PageNumb)==false){
		return false;
	}
	for(int n=0;n<PageNumb;n++){
		if(::Save(f,BuffData[n])==false)
			return false;
	}

	BYTE	D=(BYTE)MirrorMode;
	if(::Save(f,D)==false){
		return false;
	}
	return true;
}

void	GUICmdReqMirror::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->MirrorItems(MirrorMode,PageNumb,BuffData);
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdSetActivateItem::GUICmdSetActivateItem(AlgorithmBase *base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Layer	=-1;
	ItemID	=-1;
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}
bool	GUICmdSetActivateItem::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,ItemID)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetActivateItem::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,ItemID)==false){
		return false;
	}
	return true;
}

void	GUICmdSetActivateItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->AddActivate(Layer,ItemID);
		}
	}
}

GUICmdClearActivateItem::GUICmdClearActivateItem(AlgorithmBase *base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot,AlgoName);
	}
}
bool	GUICmdClearActivateItem::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;
}
bool	GUICmdClearActivateItem::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}

void	GUICmdClearActivateItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			Ap->Inactivate();
		}
	}
}

//=======================================================================
GUICmdPasteMatrix::GUICmdPasteMatrix(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPasteMatrix::Load(QIODevice *f)
{
	if(::Load(f,CreatedTime)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(MatrixData.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdPasteMatrix::Save(QIODevice *f)
{
	if(::Save(f,CreatedTime)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(MatrixData.Save(f)==false)
		return false;
	return true;
}

void	GUICmdPasteMatrix::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	GPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	DataInPage *P=GetLayersBase()->GetPageData(localPage);
	ClipboardAlgorithm	*C=GetLayersBase()->GetClipboardDatas()->Find(CreatedTime);
	AlgorithmBase	*A=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(C!=NULL && A!=NULL && C->Base==A){
		for(PasteListMatrix	*p=MatrixData.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->GlobalPage==GPage){
				AlgorithmInPageRoot	*APage=A->GetPageData(localPage);
				if(p->Layers.GetFirst()==NULL){
					for(ClipboardAlgorithmItem *item=C->Items.GetFirst();item!=NULL;item=item->GetNext()){
						int	x,y;
						item->Area.GetCenter(x,y);
						FlexArea	Area=item->Area;
						Area.MoveToClip(p->XPos-x, p->YPos-y,0,0,P->GetDotPerLine(),P->GetMaxLines());
						if(Area.GetPatternByte()>0){
							APage->ExecutePaste(0,item ,p->XPos-x, p->YPos-y,Area,true);
						}
					}
				}
				else{
					int	PastedLayer=0;
					for(BoolClass *b=p->Layers.GetFirst();b!=NULL;b=b->GetNext(),PastedLayer++){
						if(b->GetValue()==true){
							for(ClipboardAlgorithmItem *item=C->Items.GetFirst();item!=NULL;item=item->GetNext()){
								int	x,y;
								item->Area.GetCenter(x,y);
								FlexArea	Area=item->Area;
								Area.MoveToClip(p->XPos-x, p->YPos-y,0,0,P->GetDotPerLine(),P->GetMaxLines());
								if(Area.GetPatternByte()>0){
									APage->ExecutePaste(PastedLayer,item ,p->XPos-x, p->YPos-y,Area,true);
								}
							}
						}
					}
				}
			}
		}
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdReqAllItemsForSelect::GUICmdReqAllItemsForSelect(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqAllItemsForSelect::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	return true;
}

bool	GUICmdReqAllItemsForSelect::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	return true;
}

struct	ReqAllItemsForSelectStruct
{
	IntList	LayerList;
	ListPageLayerIDLibNamePack	*ItemInfo;
};

static	void ReqAllItemsForSelectFunc(AlgorithmItemRoot *Item ,void *_Something)
{
	struct	ReqAllItemsForSelectStruct	*s=(struct	ReqAllItemsForSelectStruct *)_Something;
	if(s->LayerList.IsInclude(Item->GetLayer())==true){
		ListPageLayerIDLibName	*a=new ListPageLayerIDLibName();
		a->ID	=Item->GetID();
		a->LibID=Item->GetLibID();
		a->ItemName	=Item->GetItemName();
		a->Page		=Item->GetPage();
		a->Layer	=Item->GetLayer();
		s->ItemInfo->AppendList(a);
	}
}

void	GUICmdReqAllItemsForSelect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAllItemsForSelect	*SendBack=GetSendBack(GUICmdAckAllItemsForSelect,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			struct	ReqAllItemsForSelectStruct	S;
			S.ItemInfo	=&SendBack->ItemInfo;
			S.LayerList	=LayerList;
			Ap->LoopforAllItems(ReqAllItemsForSelectFunc,&S);
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckAllItemsForSelect::GUICmdAckAllItemsForSelect(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
	
bool	GUICmdAckAllItemsForSelect::Load(QIODevice *f)
{
	if(ItemInfo.Load(f)==false)
		return false;
	return true;
}

bool	GUICmdAckAllItemsForSelect::Save(QIODevice *f)
{
	if(ItemInfo.Load(f)==false)
		return false;
	return true;
}

//=======================================================================

GUICmdReqSelectItemByID::GUICmdReqSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	SelectMode=true;
}

bool	GUICmdReqSelectItemByID::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(SelectedItem.Load(f)==false){
		return false;
	}
	if(::Load(f,SelectMode)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqSelectItemByID::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(SelectedItem.Save(f)==false){
		return false;
	}
	if(::Save(f,SelectMode)==false){
		return false;
	}
	return true;
}

void	GUICmdReqSelectItemByID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectItemByID	*SendBack=GetSendBack(GUICmdAckSelectItemByID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
		if(Ap!=NULL){
			if(SelectMode==true){
				Ap->SelectItemByID(SelectedItem);
			}
			AlgorithmItemPointerListContainer Items;
			Ap->GetItems(SelectedItem,Items);
			for(AlgorithmItemPointerList *L=Items.GetFirst();L!=NULL;L=L->GetNext()){
				int	x1,y1,x2,y2;
				L->GetItem()->GetXY(x1,y1,x2,y2);
				SendBack->MinX=min(SendBack->MinX,x1);
				SendBack->MinY=min(SendBack->MinY,y1);
				SendBack->MaxX=max(SendBack->MaxX,x2);
				SendBack->MaxY=max(SendBack->MaxY,y2);
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectItemByID::GUICmdAckSelectItemByID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
}

bool	GUICmdAckSelectItemByID::Load(QIODevice *f)
{
	if(::Load(f,MinX)==false){
		return false;
	}
	if(::Load(f,MinY)==false){
		return false;
	}
	if(::Load(f,MaxX)==false){
		return false;
	}
	if(::Load(f,MaxY)==false){
		return false;
	}
	return true;
}

bool	GUICmdAckSelectItemByID::Save(QIODevice *f)
{
	if(::Save(f,MinX)==false){
		return false;
	}
	if(::Save(f,MinY)==false){
		return false;
	}
	if(::Save(f,MaxX)==false){
		return false;
	}
	if(::Save(f,MaxY)==false){
		return false;
	}
	return true;
}

//=======================================================================

GUICmdMirrorImage::GUICmdMirrorImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdMirrorImage::Load(QIODevice *f)
{
	if(::Load(f,XMode)==false)
		return false;
	if(::Load(f,YMode)==false)
		return false;
	return true;
}

bool	GUICmdMirrorImage::Save(QIODevice *f)
{
	if(::Save(f,XMode)==false)
		return false;
	if(::Save(f,YMode)==false)
		return false;
	return true;
}

void	GUICmdMirrorImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(int layer=0;layer<GetLayerNumb(localPage);layer++){
		GetLayersBase()->GetPageData(localPage)->GetLayerData(layer)->Mirror(XMode,YMode);
	}
	SendAck(localPage);
}

//=======================================================================

GUICmdSelectItemsByOriginType::GUICmdSelectItemsByOriginType(LayersBase	*base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
,SelectMode(NULL)
{
}
bool	GUICmdSelectItemsByOriginType::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(f->read((char *)&SelectMode,sizeof(SelectMode))!=sizeof(SelectMode)){
		return false;
	}
	if(::Load(f,ExistOrigin)==false){
		return false;
	}
	if(ExistOrigin==true){
		if(::Load(f,OriginAlgoRoot)==false){
			return false;
		}
		if(::Load(f,OriginAlgoName)==false){
			return false;
		}
		SelectMode.Origin=GetLayersBase()->GetAlgorithmBase(OriginAlgoRoot,OriginAlgoName);
	}
	else{
		SelectMode.Origin=NULL;
	}
	return true;
}
bool	GUICmdSelectItemsByOriginType::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(f->write((const char *)&SelectMode,sizeof(SelectMode))!=sizeof(SelectMode)){
		return false;
	}
	if(SelectMode.Origin!=NULL){
		ExistOrigin=true;
		SelectMode.Origin->GetAlgorithmRootName(OriginAlgoRoot,OriginAlgoName);
		if(::Save(f,ExistOrigin)==false){
			return false;
		}
		if(::Save(f,OriginAlgoRoot)==false){
			return false;
		}
		if(::Save(f,OriginAlgoName)==false){
			return false;
		}
	}
	else{
		ExistOrigin=false;
		if(::Save(f,ExistOrigin)==false){
			return false;
		}
	}
	return true;
}
void	GUICmdSelectItemsByOriginType::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			if(Ap!=NULL){
				Ap->SelectItemsByOriginType(SelectMode,LayerList);
			}
		}
	}
}

//=======================================================================

GUICmdSetMultiSelectMode::GUICmdSetMultiSelectMode(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetMultiSelectMode::Load(QIODevice *f)
{
	if(::Load(f,ModeMultiSelect)==false){
		return false;
	}
	if(::Load(f,ItemName)==false){
		return false;
	}
	return true;
}
bool	GUICmdSetMultiSelectMode::Save(QIODevice *f)
{
	if(::Save(f,ModeMultiSelect)==false){
		return false;
	}
	if(::Save(f,ItemName)==false){
		return false;
	}
	return true;
}
void	GUICmdSetMultiSelectMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(EmitterRoot,EmitterName,ItemName);
	if(f!=NULL){
		DisplayImageWithAlgorithm	*d=dynamic_cast<DisplayImageWithAlgorithm *>(f);
		if(d!=NULL){
			d->SetMultiSelect(ModeMultiSelect);
		}
	}
	SendAck(localPage);
}


//=======================================================================
GUICmdReqShrink::GUICmdReqShrink(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
	ExpandPixels=0;
}
bool	GUICmdReqShrink::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(::Load(f,ExpandPixels)==false){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}
	if(::Load(f,MaskForSameLib)==false){
		return false;
	}
	return(true);
}
bool	GUICmdReqShrink::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(::Save(f,ExpandPixels)==false){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}
	if(::Save(f,MaskForSameLib)==false){
		return false;
	}
	return(true);
}

void	GUICmdReqShrink::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName )
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		Ap->ShrinkItems(LayerList,ExpandPixels,MaskForSameLib);
	}
	SendAck(localPage);
}

//=======================================================================
GUICmdPourImage::GUICmdPourImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdPourImage::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	DType=(DisplayImage::DisplayType)d;
	if(::Load(f,BrightnessWidth)==false){
		return false;
	}
	if(::Load(f,ExpandedDot)==false){
		return false;
	}
	if(::Load(f,PickedColor)==false){
		return false;
	}
	return(true);
}
bool	GUICmdPourImage::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	BYTE	d=(BYTE)DType;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,BrightnessWidth)==false){
		return false;
	}
	if(::Save(f,ExpandedDot)==false){
		return false;
	}
	if(::Save(f,PickedColor)==false){
		return false;
	}
	return(true);
}
static	void	LoopFunc(void)
{
}

void	GUICmdPourImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	if(P!=NULL){
		if(0<=LocalX && LocalX<P->GetDotPerLine()
		&& 0<=LocalY && LocalY<P->GetMaxLines()){
			ColorLogic Color;
			ImagePointerContainer Images;
			int	c[3];
			if(P->GetLayerNumb()==1){
				ImageBuffer	*SBuff;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff=&P->GetLayerData(0)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff=&P->GetLayerData(0)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff=&P->GetLayerData(0)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetCamTargetBuff();
				}
				else{
					SBuff=NULL;
				}
				if(SBuff!=NULL && SBuff->IsNull()==false){
					if(LocalX<SBuff->GetWidth() && LocalY<SBuff->GetHeight()){
						if((DType&DisplayImage::__BitBuff)==0){
							c[0]=SBuff->GetY(LocalY)[LocalX];
							Color.SetMonoColorRange  (c[0]-BrightnessWidth,c[0]+BrightnessWidth);
						}
					}
				}
			}
			else if(P->GetLayerNumb()==2){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						c[0]=SBuff0->GetY(LocalY)[LocalX];
						c[1]=SBuff1->GetY(LocalY)[LocalX];
						c[2]=c[1];
						ColorBox	*Cb=new ColorBox();
						Color.Add(Cb);
						Cb->Set( c[0]-BrightnessWidth,c[0]+BrightnessWidth
								,c[1]-BrightnessWidth,c[1]+BrightnessWidth
								,c[2]-BrightnessWidth,c[2]+BrightnessWidth);
					}
				}
			}
			else if(P->GetLayerNumb()>=3){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				ImageBuffer	*SBuff2;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
					SBuff2=&P->GetLayerData(2)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
					SBuff2=&P->GetLayerData(2)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
					SBuff2=&P->GetLayerData(2)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
					SBuff2=&P->GetLayerData(2)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
					SBuff2=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& SBuff2!=NULL && SBuff2->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						c[0]=SBuff0->GetY(LocalY)[LocalX];
						c[1]=SBuff1->GetY(LocalY)[LocalX];
						c[2]=SBuff2->GetY(LocalY)[LocalX];
						ColorBox	*Cb=new ColorBox();
						Color.Add(Cb);
						Cb->Set( c[0]-BrightnessWidth,c[0]+BrightnessWidth
								,c[1]-BrightnessWidth,c[1]+BrightnessWidth
								,c[2]-BrightnessWidth,c[2]+BrightnessWidth);
					}
				}
			}
			FlexArea	Area;
			if(Images[0]->IsNull()==false){
				Area.PourFromImageLimitless(Images
								,NULL
								,LocalX,LocalY
								,Color
								,LoopFunc);
			}
			if(ExpandedDot>0){
				Area.FatAreaN(ExpandedDot);
			}
			else
				if (ExpandedDot<0) {
				Area.ThinAreaN(-ExpandedDot);
				PureFlexAreaListContainer	Piece;
				Area.Clusterize(Piece);
				Area.Clear();
				for(PureFlexAreaList *f=Piece.GetFirst();f!=NULL;f=f->GetNext()){
					if(f->IsInclude(LocalX,LocalY)==true){
						Area=*f;
						break;
					}
				}
			}
			if(Area.GetPatternByte()!=0){
				{
					UndoDataInPage	*UndoPointer=new UndoDataInPage(P ,&DataInPage::UndoPourImage);
					BYTE	d=(BYTE)DType;
					::Save(UndoPointer->GetWritePointer(),d);
					::Save(UndoPointer->GetWritePointer(),MasterNo);

					FlexAreaColorImage	UndoAreaImage;
					ImageBuffer *Buffer[3];
					int LayerNumb=Images.GetCount();
					int	t=0;
					for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext(),t++){
						Buffer[t]=p->GetImage();
					}
					UndoAreaImage.Set(Area,Buffer ,LayerNumb);
					UndoAreaImage.Save(UndoPointer->GetWritePointer());
					GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);
				}
				int	Col[3];
				Col[0]=PickedColor.red();
				Col[1]=PickedColor.green();
				Col[2]=PickedColor.blue();
				int	t=0;
				for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext(),t++){
					Area.PaintWithColor(*p->GetImage(), Col[t],0 ,0);
				}
			}
		}
	}
}


//=======================================================================
GUICmdReplaceColorImage::GUICmdReplaceColorImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReplaceColorImage::Load(QIODevice *f)
{
	if(::Load(f,LocalX)==false){
		return false;
	}
	if(::Load(f,LocalY)==false){
		return false;
	}
	if(::Load(f,MasterNo)==false){
		return false;
	}
	BYTE	d;
	if(::Load(f,d)==false){
		return false;
	}
	DType=(DisplayImage::DisplayType)d;
	if(::Load(f,BrightnessWidth)==false){
		return false;
	}
	if(::Load(f,ExpandedDot)==false){
		return false;
	}
	if(::Load(f,PickedColor)==false){
		return false;
	}
	return(true);
}
bool	GUICmdReplaceColorImage::Save(QIODevice *f)
{
	if(::Save(f,LocalX)==false){
		return false;
	}
	if(::Save(f,LocalY)==false){
		return false;
	}
	if(::Save(f,MasterNo)==false){
		return false;
	}
	BYTE	d=(BYTE)DType;
	if(::Save(f,d)==false){
		return false;
	}
	if(::Save(f,BrightnessWidth)==false){
		return false;
	}
	if(::Save(f,ExpandedDot)==false){
		return false;
	}
	if(::Save(f,PickedColor)==false){
		return false;
	}
	return(true);
}
void	GUICmdReplaceColorImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	if(P!=NULL){
		if(0<=LocalX && LocalX<P->GetDotPerLine()
		&& 0<=LocalY && LocalY<P->GetMaxLines()){
			ColorLogic Color;
			ImagePointerContainer Images;
			int	c[3];
			if(P->GetLayerNumb()==1){
				ImageBuffer	*SBuff;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff=&P->GetLayerData(0)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff=&P->GetLayerData(0)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff=&P->GetLayerData(0)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff=&P->GetLayerData(0)->GetCamTargetBuff();
				}
				else{
					SBuff=NULL;
				}
				if(SBuff!=NULL && SBuff->IsNull()==false){
					if(LocalX<SBuff->GetWidth() && LocalY<SBuff->GetHeight()){
						if((DType&DisplayImage::__BitBuff)==0){
							c[0]=SBuff->GetY(LocalY)[LocalX];
							Color.SetMonoColorRange  (c[0]-BrightnessWidth,c[0]+BrightnessWidth);
						}
					}
				}
			}
			else if(P->GetLayerNumb()==2){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						c[0]=SBuff0->GetY(LocalY)[LocalX];
						c[1]=SBuff1->GetY(LocalY)[LocalX];
						c[2]=c[1];
						ColorBox	*Cb=new ColorBox();
						Color.Add(Cb);
						Cb->Set( c[0]-BrightnessWidth,c[0]+BrightnessWidth
								,c[1]-BrightnessWidth,c[1]+BrightnessWidth
								,c[2]-BrightnessWidth,c[2]+BrightnessWidth);
					}
				}
			}
			else if(P->GetLayerNumb()>=3){
				ImageBuffer	*SBuff0;
				ImageBuffer	*SBuff1;
				ImageBuffer	*SBuff2;
				if((DType&DisplayImage::__Master)!=0){
					P->GetMasterImages(MasterNo,Images);
					SBuff0=&P->GetLayerData(0)->GetMasterBuff(MasterNo);
					SBuff1=&P->GetLayerData(1)->GetMasterBuff(MasterNo);
					SBuff2=&P->GetLayerData(2)->GetMasterBuff(MasterNo);
				}
				else if((DType&DisplayImage::__BackGround)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetBackGroundBuff();
					SBuff1=&P->GetLayerData(1)->GetBackGroundBuff();
					SBuff2=&P->GetLayerData(2)->GetBackGroundBuff();
				}
				else if((DType&DisplayImage::__Target)!=0){
					P->GetTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetBuff();
				}
				else if((DType&DisplayImage::__TargetTR)!=0){
					P->GetTargetTRImages(Images);
					SBuff0=&P->GetLayerData(0)->GetTargetTRBuff();
					SBuff1=&P->GetLayerData(1)->GetTargetTRBuff();
					SBuff2=&P->GetLayerData(2)->GetTargetTRBuff();
				}
				else if((DType&DisplayImage::__DelayedView)!=0){
					P->GetDelayedViewImages(Images);
					SBuff0=&P->GetLayerData(0)->GetDelayedViewBuff();
					SBuff1=&P->GetLayerData(1)->GetDelayedViewBuff();
					SBuff2=&P->GetLayerData(2)->GetDelayedViewBuff();
				}
				else if((DType&DisplayImage::__BitBuff)!=0){
					SBuff0=&P->GetLayerData(0)->GetBitBuff();
					SBuff1=&P->GetLayerData(1)->GetBitBuff();
					SBuff2=&P->GetLayerData(2)->GetBitBuff();
				}
				else if((DType&DisplayImage::__RawTarget)!=0){
					P->GetRawTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetRawTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetRawTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetRawTargetBuff();
				}
				else if((DType&DisplayImage::__CamTarget)!=0){
					P->GetCamTargetImages(Images);
					SBuff0=&P->GetLayerData(0)->GetCamTargetBuff();
					SBuff1=&P->GetLayerData(1)->GetCamTargetBuff();
					SBuff2=&P->GetLayerData(2)->GetCamTargetBuff();
				}
				else{
					SBuff0=NULL;
					SBuff1=NULL;
					SBuff2=NULL;
				}
				if(SBuff0!=NULL && SBuff0->IsNull()==false
				&& SBuff1!=NULL && SBuff1->IsNull()==false
				&& SBuff2!=NULL && SBuff2->IsNull()==false
				&& LocalX<SBuff0->GetWidth() && LocalY<SBuff0->GetHeight()){
					if((DType&DisplayImage::__BitBuff)==0){
						c[0]=SBuff0->GetY(LocalY)[LocalX];
						c[1]=SBuff1->GetY(LocalY)[LocalX];
						c[2]=SBuff2->GetY(LocalY)[LocalX];
						ColorBox	*Cb=new ColorBox();
						Color.Add(Cb);
						Cb->Set( c[0]-BrightnessWidth,c[0]+BrightnessWidth
								,c[1]-BrightnessWidth,c[1]+BrightnessWidth
								,c[2]-BrightnessWidth,c[2]+BrightnessWidth);
					}
				}
			}
			FlexArea	Area;
			if(Images[0]->IsNull()==false){
				int	XByte	=(P->GetDotPerLine()+7)/8;
				int	YLen	=P->GetMaxLines();
				BYTE	**Mask=MakeMatrixBuff(XByte,YLen);
				BYTE	**BuffMap=MakeMatrixBuff(XByte,YLen);
				Images.PickupMask(Color,Mask);
				if(ExpandedDot>0){
					GetLayersBase()->FatAreaN(Mask,BuffMap,XByte,YLen,ExpandedDot);
				}
				else{
					GetLayersBase()->ThinAreaN(Mask,BuffMap,XByte,YLen,ExpandedDot);
				}

				UndoDataInPage	*UndoPointer=new UndoDataInPage(P ,&DataInPage::UndoReplaceColorImage);
				BYTE	d=(BYTE)DType;
				::Save(UndoPointer->GetWritePointer(),d);
				::Save(UndoPointer->GetWritePointer(),MasterNo);

				int32 LayerNumb=Images.GetCount();
				::Save(UndoPointer->GetWritePointer(),LayerNumb);
				for(ImagePointerList *p=Images.GetFirst();p!=NULL;p=p->GetNext()){
					p->GetImage()->Save(UndoPointer->GetWritePointer());
				}
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UndoPointer);

				Images.DrawOnMask(PickedColor,Mask);

				DeleteMatrixBuff(Mask	,YLen);
				DeleteMatrixBuff(BuffMap,YLen);
			}
		}
	}
}

//=======================================================================
GUICmdReqChangeLibItem::GUICmdReqChangeLibItem(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqChangeLibItem::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	return true;
}
bool	GUICmdReqChangeLibItem::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	return true;
}

void	GUICmdReqChangeLibItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);
			AlgorithmItemPointerListContainer ItemPointers;
			Ap->GetSelectedItems(ItemPointers);
			for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
				a->GetItem()->ChangeLibID(LibID);
			}
		}
	}
}

//=======================================================================
GUICmdReqSelectedItemLibID::GUICmdReqSelectedItemLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSelectedItemLibID::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	return true;
}
bool	GUICmdReqSelectedItemLibID::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	return true;
}

void	GUICmdReqSelectedItemLibID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectedItemLibID	*SendBack=GetSendBack(GUICmdAckSelectedItemLibID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);

			AlgorithmItemPointerListContainer ItemPointers;
			Ap->GetSelectedItems(ItemPointers);
			for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->GetItem()->GetSelected()==true){
					SendBack->LibList.Merge(a->GetItem()->GetLibID());
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectedItemLibID::GUICmdAckSelectedItemLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckSelectedItemLibID::Load(QIODevice *f)
{
	if(LibList.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckSelectedItemLibID::Save(QIODevice *f)
{
	if(LibList.Save(f)==false)	return false;
	return true;
}

//=======================================================================

GUICmdReqSelectedItemIDInLibID::GUICmdReqSelectedItemIDInLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqSelectedItemIDInLibID::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,LibType	)==false)	return false;
	if(::Load(f,LibID	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	return true;
}
bool	GUICmdReqSelectedItemIDInLibID::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,LibType	)==false)	return false;
	if(::Save(f,LibID	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	return true;
}
void	GUICmdReqSelectedItemIDInLibID::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckSelectedItemIDInLibID	*SendBack=GetSendBack(GUICmdAckSelectedItemIDInLibID,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);

			AlgorithmItemPointerListContainer ItemPointers;
			Ap->GetSelectedItems(ItemPointers);
			for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
				AlgorithmItemRoot	*item=a->GetItem();
				if(item->GetLayer()==Layer && item->GetSelected()==true && item->GetLibID()==LibID){
					SendBack->ItemIDs.Merge(item->GetID());
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckSelectedItemIDInLibID::GUICmdAckSelectedItemIDInLibID(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckSelectedItemIDInLibID::Load(QIODevice *f)
{
	if(ItemIDs.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckSelectedItemIDInLibID::Save(QIODevice *f)
{
	if(ItemIDs.Save(f)==false)	return false;
	return true;
}

//=======================================================================

GUICmdMakeOutlineItem::GUICmdMakeOutlineItem(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeOutlineItem::Load(QIODevice *f)
{
	if(::Load(f,LibType		)==false)	return false;
	if(::Load(f,Phase		)==false)	return false;
	if(::Load(f,OutlineWidth)==false)	return false;
	return true;
}
bool	GUICmdMakeOutlineItem::Save(QIODevice *f)
{
	if(::Save(f,LibType		)==false)	return false;
	if(::Save(f,Phase		)==false)	return false;
	if(::Save(f,OutlineWidth)==false)	return false;
	return true;
}

void	GUICmdMakeOutlineItem::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(LibType);
	if(ABase!=NULL){
		AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			AlgorithmInPageRoot	*Ap=Ah->GetPageData(localPage);

			Ap->MakeOutlineItemsInSelectedItems(OutlineWidth);
		}
	}

}
