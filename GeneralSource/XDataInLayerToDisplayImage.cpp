#include "XTypeDef.h"
#include <QSqlDatabase>
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XTransfer.h"
#include "XResultDLLManager.h"
#include <QThread>
#include "XForWindows.h"
#include "XShareMasterData.h"
#include "XLotInformation.h"
#include "XGeneralStocker.h"
#include "XAlgorithmDLL.h"
#include "XResultAnalizer.h"
#include "XDataInLayerToDisplayImage.h"

GUICmdReqBmpForTopView::GUICmdReqBmpForTopView(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
		:GUICmdReqBmp(Base,typeid(this).name(),EmitterRoot,EmitterName ,DisplayImage::__Master ,globalPage)
{
}
GUICmdReqBmpForTopView::~GUICmdReqBmpForTopView(void)
{
}

void	GUICmdReqBmpForTopView::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBmp	*SendBack=GetSendBack(GUICmdSendBmpForTopView,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeImage(Data.DType
						,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
						,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
						,Data.MovX,Data.MovY,Data.ZoomRate,Data.Yz
						,localPage
						,*GetLayersBase()
						,Data.MasterNo
						,LayerList
						,Data.RedCircleMode
						,0
						,128
						,false
						,false);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


//====================================================================================
GUICmdSendBmpForTopView::GUICmdSendBmpForTopView(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
: GUICmdSendBmp(Base,typeid(this).name(),EmitterRoot,EmitterName ,globalPage)
{
}
GUICmdSendBmpForTopView::~GUICmdSendBmpForTopView(void)
{
}

//====================================================================================

GUICmdReqBmp::GUICmdReqBmp(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Data.DType			=dtype;
	Data.RedCircleMode	=true;
	Data.ShowFixedPhase				=-1;
	Data.TransparentLevelInBitBuff	=0;
	Data.ShowNGMarkInTarget			=true;
}

GUICmdReqBmp::GUICmdReqBmp(LayersBase *Base,QString className,const QString &EmitterRoot,const QString &EmitterName ,DisplayImage::DisplayType dtype ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,className,globalPage)
{
	Data.DType			=dtype;
	Data.RedCircleMode	=true;
	Data.ShowFixedPhase				=-1;
	Data.TransparentLevelInBitBuff	=0;
	Data.ShowNGMarkInTarget			=true;
}
bool	GUICmdReqBmp::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(LayerList.Save(f)==false){
		return false;
	}

	return true;
}
bool	GUICmdReqBmp::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	if(LayerList.Load(f)==false){
		return false;
	}

	return true;
}


void	GUICmdReqBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendBmp	*SendBack=GetSendBack(GUICmdSendBmp,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeImage(Data.DType
						,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
						,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
						,Data.MovX,Data.MovY,Data.ZoomRate,Data.Yz
						,localPage
						,*GetLayersBase()
						,Data.MasterNo
						,LayerList
						,Data.RedCircleMode
						,Data.ShowFixedPhase
						,Data.TransparentLevelInBitBuff
						,Data.ShowNGMarkInTarget
						,Data.RepaintContinuously);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendBmp::GUICmdSendBmp(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData	=NULL;
	NGData	=NULL;
	PntFromIData=NULL;
	PntFromNGData=NULL;
	ShowNGMarkInTarget	=true;
	RetNGData	=false;
}

GUICmdSendBmp::GUICmdSendBmp(LayersBase *Base,QString className,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,className,globalPage)
{
	IData	=NULL;
	NGData	=NULL;
	PntFromIData=NULL;
	PntFromNGData=NULL;
	ShowNGMarkInTarget	=true;
	RetNGData	=false;
}

GUICmdSendBmp::~GUICmdSendBmp(void)
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

struct	GUICmdSendBmpData
{
	int32	W,H;
	bool	ShowNGMarkInTarget;
};


bool	GUICmdSendBmp::Load(QIODevice *f)
{
	struct	GUICmdSendBmpData	Data;
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data)){
		return false;
	}
	ShowNGMarkInTarget=Data.ShowNGMarkInTarget;

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
	if(::Load(f,RetNGData)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendBmp::Save(QIODevice *f)
{
	struct	GUICmdSendBmpData	Data;
	Data.H=IData->height();
	Data.W=IData->width();
	Data.ShowNGMarkInTarget	=ShowNGMarkInTarget;

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
	if(::Save(f,RetNGData)==false){
		return false;
	}
	return true;
}


//=======================================================================
