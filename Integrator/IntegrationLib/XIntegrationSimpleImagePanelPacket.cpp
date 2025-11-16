#include "XIntegrationSimpleImagePanel.h"
#include "XIntegrationSimpleImagePanelPacket.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "swap.h"
#include <QGestureEvent>
#include <QPinchGesture>
#include "XGeneralFunc.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmBase.h"
#include "XTransform.h"

//=============================================================================================

IntegrationReqPanelImage::IntegrationReqPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&PanelImageInfo,sizeof(PanelImageInfo))!=sizeof(PanelImageInfo)){
		return false;
	}
	return true;
}
bool	IntegrationReqPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&PanelImageInfo,sizeof(PanelImageInfo))!=sizeof(PanelImageInfo)){
		return false;
	}
	return true;
}

void	IntegrationReqPanelImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckPanelImage	*SendBack=GetSendBackIntegration(IntegrationAckPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		SendBack->Allocate(	 PanelImageInfo.CanvasWidth
							,PanelImageInfo.CanvasHeight
							,PanelImageInfo.CountOfLayer);

		MakeImage(SendBack->ImageBuff);
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

void	IntegrationReqPanelImage::MakeImage(BYTE *ImageBuff)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(PanelImageInfo.Phase);
	if(Ph==NULL)
		return;
	int	x1,y1,x2,y2;
	x1=y1=x2=y2=0;
	Ph->GetXY(x1,y1,x2,y2);

	double	Z=1.0/PanelImageInfo.ZoomRate;
	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*Pg=Ph->GetPageData(page);
		int	gx1=(Pg->GetOutlineOffset()->x+PanelImageInfo.Movx)*PanelImageInfo.ZoomRate;
		int	gy1=(Pg->GetOutlineOffset()->y+PanelImageInfo.Movy)*PanelImageInfo.ZoomRate;
		int	gx2=(Pg->GetOutlineOffset()->x+PanelImageInfo.Movx+Pg->GetDotPerLine()	)*PanelImageInfo.ZoomRate;
		int	gy2=(Pg->GetOutlineOffset()->y+PanelImageInfo.Movy+Pg->GetMaxLines()	)*PanelImageInfo.ZoomRate;

		gx1=max(gx1,0);
		gy1=max(gy1,0);
		gx2=min(gx2,PanelImageInfo.CanvasWidth);
		gy2=min(gy2,PanelImageInfo.CanvasHeight);
		int	X1=Clipping((int)(gx1*Z-Pg->GetOutlineOffset()->x-PanelImageInfo.Movx),0,Pg->GetDotPerLine());
		int	X2=Clipping((int)(gx2*Z-Pg->GetOutlineOffset()->x-PanelImageInfo.Movx),0,Pg->GetDotPerLine());
		if(Pg->GetLayerNumb()==1){
			ImageBuffer	&Buff0=Pg->GetLayerData(0)->GetMasterBuff();
			int	YNumb=gy2-gy1;
			int	WByte	=PanelImageInfo.CanvasWidth;
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				//for(int y=gy1;y<gy2;y++){
				for(int t=0;t<YNumb;t++){
					int	y=gy1+t;
					//QRgb	*d=(QRgb *)Image.scanLine(y);
					BYTE	*d=&ImageBuff[y*WByte];
					d+=gx1;
					int	Y =Clipping((int)(y*Z-Pg->GetOutlineOffset()->y-PanelImageInfo.Movy)
									,0,Pg->GetMaxLines());
					BYTE	*s=Buff0.GetY(Y);
					
					for(double DX=X1;DX<X2;DX+=Z,d++){
						BYTE	c=s[(int)DX];
						//*d=qRgba(c,c,c,255);
						*d=c;
					}
				}
			}
		}
		else
		if(Pg->GetLayerNumb()==2){
			ImageBuffer	&Buff0=Pg->GetLayerData(0)->GetMasterBuff();
			ImageBuffer	&Buff1=Pg->GetLayerData(1)->GetMasterBuff();
			int	YNumb=gy2-gy1;
			int	WByte	=PanelImageInfo.CanvasWidth*2;
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				//for(int y=gy1;y<gy2;y++){
				for(int t=0;t<YNumb;t++){
					int	y=gy1+t;
					//QRgb	*d=(QRgb *)Image.scanLine(y);
					BYTE	*d=&ImageBuff[y*WByte];
					d+=gx1;
					int	Y =Clipping((int)(y*Z-Pg->GetOutlineOffset()->y-PanelImageInfo.Movy)
									,0,Pg->GetMaxLines());
					BYTE	*s0=Buff0.GetY(Y);
					BYTE	*s1=Buff1.GetY(Y);
					for(double DX=X1;DX<X2;DX+=Z,d+=2){
						BYTE	c0=s0[(int)DX];
						BYTE	c1=s1[(int)DX];
						//*d=qRgba(c0,c0,c1,255);
						*d	=c0;
						*(d+1)=c1;
					}
				}
			}
		}
		else
		if(Pg->GetLayerNumb()>=3){
			ImageBuffer	&Buff0=Pg->GetLayerData(0)->GetMasterBuff();
			ImageBuffer	&Buff1=Pg->GetLayerData(1)->GetMasterBuff();
			ImageBuffer	&Buff2=Pg->GetLayerData(2)->GetMasterBuff();
			int	YNumb=gy2-gy1;
			int	WByte	=PanelImageInfo.CanvasWidth*3;
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				//for(int y=gy1;y<gy2;y++){
				for(int t=0;t<YNumb;t++){
					int	y=gy1+t;
					//QRgb	*d=(QRgb *)Image.scanLine(y);
					BYTE	*d=&ImageBuff[y*WByte];
					d+=gx1;
					int	Y =Clipping((int)(y*Z-Pg->GetOutlineOffset()->y-PanelImageInfo.Movy)
									,0,Pg->GetMaxLines());
					BYTE	*s0=Buff0.GetY(Y);
					BYTE	*s1=Buff1.GetY(Y);
					BYTE	*s2=Buff2.GetY(Y);
					
					for(double DX=X1;DX<X2;DX+=Z,d+=3){
						int	X=(int)DX;
						BYTE	c0=s0[X];
						BYTE	c1=s1[X];
						BYTE	c2=s2[X];
						*d=qRgba(c0,c1,c2,255);
						*d	=c0;
						*(d+1)=c1;
						*(d+2)=c2;
					}
				}
			}
		}
	}
}

IntegrationAckPanelImage::IntegrationAckPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	ImageBuff=NULL;
}
IntegrationAckPanelImage::~IntegrationAckPanelImage(void)
{
	if(ImageBuff!=NULL){
		delete	[]ImageBuff;
		ImageBuff=NULL;
	}
}
void	IntegrationAckPanelImage::Allocate(int CanvasWidth,int CanvasHeight,int CountOfLayer)
{
	if(ImageBuff!=NULL && (PanelImageInfo.XLen!=CanvasWidth || PanelImageInfo.YLen!=CanvasHeight)){
		delete	[]ImageBuff;
		ImageBuff=NULL;
	}
	if(ImageBuff==NULL){
		PanelImageInfo.XLen			=CanvasWidth;
		PanelImageInfo.YLen			=CanvasHeight;
		PanelImageInfo.CountOfLayer	=CountOfLayer;
		ImageBuff=new BYTE[CanvasWidth*CanvasHeight*CountOfLayer];
	}
}
bool	IntegrationAckPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&PanelImageInfo,sizeof(PanelImageInfo))!=sizeof(PanelImageInfo)){
		return false;
	}
	Allocate(PanelImageInfo.XLen,PanelImageInfo.YLen,PanelImageInfo.CountOfLayer);

	int	WByte=PanelImageInfo.XLen*PanelImageInfo.CountOfLayer;
	if(f->read((char *)ImageBuff,WByte*PanelImageInfo.YLen)!=WByte*PanelImageInfo.YLen){
		return false;
	}
	return true;
}
bool	IntegrationAckPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&PanelImageInfo,sizeof(PanelImageInfo))!=sizeof(PanelImageInfo)){
		return false;
	}
	int	WByte=PanelImageInfo.XLen*PanelImageInfo.CountOfLayer;
	if(f->write((const char *)ImageBuff,WByte*PanelImageInfo.YLen)!=WByte*PanelImageInfo.YLen){
		return false;
	}

	return true;
}
void	IntegrationAckPanelImage::CopyToImage(QImage &Img)
{
	int	XLen=min(PanelImageInfo.XLen,Img.width());
	int	YLen=min(PanelImageInfo.YLen,Img.height());
	int	WByte=PanelImageInfo.XLen*PanelImageInfo.CountOfLayer;
	if(PanelImageInfo.CountOfLayer==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				QRgb	*d=(QRgb *)Img.scanLine(y);
				BYTE	*s=&ImageBuff[y*WByte];
				for(int x=0;x<XLen;x++){
					*d=qRgb(*s,*s,*s);
					d++;
					s++;
				}
			}
		}
	}
	else
	if(PanelImageInfo.CountOfLayer==2){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				QRgb	*d=(QRgb *)Img.scanLine(y);
				BYTE	*s=&ImageBuff[y*WByte];
				for(int x=0;x<XLen;x++){
					BYTE	c0=*s;
					BYTE	c1=*(s+1);
					*d=qRgb(c0,c1,c1);
					d++;
					s+=2;
				}
			}
		}
	}
	if(PanelImageInfo.CountOfLayer==1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				QRgb	*d=(QRgb *)Img.scanLine(y);
				BYTE	*s=&ImageBuff[y*WByte];
				for(int x=0;x<XLen;x++){
					BYTE	c0=*s;
					BYTE	c1=*(s+1);
					BYTE	c2=*(s+2);
					*d=qRgb(c0,c1,c2);
					d++;
					s+=3;
				}
			}
		}
	}
}

IntegrationCmdUndo::IntegrationCmdUndo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdUndo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->ExecuteUndoInMaster()==false){
		SetError(Error_Comm , /**/"Send error : IntegrationCmdUndo",ErrorCodeList::_Alart);
	}
	SendAck(slaveNo);
}
IntegrationCmdRedo::IntegrationCmdRedo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdRedo::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->ExecuteRedoInMaster()==false){
		SetError(Error_Comm , /**/"Send error : IntegrationCmdRedo",ErrorCodeList::_Alart);
	}
	SendAck(slaveNo);
}



//=============================================================================================

IntegrationReqAlgorithmPanelImage::IntegrationReqAlgorithmPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationReqAlgorithmPanelImage::Load(QIODevice *f)
{
	if(f->read((char *)&ReqAlgorithmPanelInfo,sizeof(ReqAlgorithmPanelInfo))!=sizeof(ReqAlgorithmPanelInfo)){
		return false;
	}
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,DrawAtterData)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	return true;
}
bool	IntegrationReqAlgorithmPanelImage::Save(QIODevice *f)
{
	if(f->write((const char *)&ReqAlgorithmPanelInfo,sizeof(ReqAlgorithmPanelInfo))!=sizeof(ReqAlgorithmPanelInfo)){
		return false;
	}
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,DrawAtterData)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;

	return true;
}

void	IntegrationReqAlgorithmPanelImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckAlgorithmPanelImage	*SendBack=GetSendBackIntegration(IntegrationAckAlgorithmPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){

		if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==false){
			slaveNo=0;
		}
		GUIFormBase *Ret[100];
		IntegrationAlgoSimpleImagePanel	*P=NULL;
		int	N=GetLayersBase()->EnumGUIInst(EmitterRoot,EmitterName,Ret,100);
		for(int i=0;i<N;i++){
			IntegrationAlgoSimpleImagePanel	*p=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Ret[i]);
			if(p!=NULL){
				P=p;
				SendBack->ImageBuff=p->TransferedImage[slaveNo];
				break;
			}
		}
		if(P!=NULL){
			if(P->CanvasWidthDim[slaveNo]	 !=ReqAlgorithmPanelInfo.CanvasWidth
			|| P->CanvasHeightDim[slaveNo]	 !=ReqAlgorithmPanelInfo.CanvasHeight
			|| P->CanvasCountOfLayer[slaveNo]!=ReqAlgorithmPanelInfo.CountOfLayer){
				P->CanvasWidthDim[slaveNo]	  =ReqAlgorithmPanelInfo.CanvasWidth ;
				P->CanvasHeightDim[slaveNo]	  =ReqAlgorithmPanelInfo.CanvasHeight;
				P->CanvasCountOfLayer[slaveNo]=ReqAlgorithmPanelInfo.CountOfLayer;
				if(P->TransferedImage[slaveNo]!=NULL){
					delete	[]P->TransferedImage[slaveNo];
				}
				P->TransferedImage[slaveNo]=NULL;
			}
			if(P->TransferedImage[slaveNo]==NULL){
				int	WByte=ReqAlgorithmPanelInfo.CanvasWidth*ReqAlgorithmPanelInfo.CanvasHeight*(ReqAlgorithmPanelInfo.CountOfLayer+1);
				P->TransferedImage[slaveNo]=new BYTE[WByte];
				
				if(P->TRansferedBuffer[slaveNo]!=NULL){
					delete	[]P->TRansferedBuffer[slaveNo];
				}
				P->TRansferedBuffer[slaveNo]=new BYTE[WByte];
			}
			SendBack->ImageBuff=P->TransferedImage[slaveNo];
			SendBack->AckAlgorithmPanelInfo.CanvasWidth	=ReqAlgorithmPanelInfo.CanvasWidth;
			SendBack->AckAlgorithmPanelInfo.CanvasHeight=ReqAlgorithmPanelInfo.CanvasHeight;
			SendBack->AckAlgorithmPanelInfo.CountOfLayer=ReqAlgorithmPanelInfo.CountOfLayer;

			P->MakeImageBuff(SendBack->ImageBuff
					,ReqAlgorithmPanelInfo.CanvasWidth,ReqAlgorithmPanelInfo.CanvasHeight,ReqAlgorithmPanelInfo.CountOfLayer
					,ReqAlgorithmPanelInfo.ZoomRate,ReqAlgorithmPanelInfo.Movx,ReqAlgorithmPanelInfo.Movy
					,ReqAlgorithmPanelInfo.Phase,LayerList
					,DrawAtterData
					,AlgoDLLRoot,AlgoDLLName
					,ReqAlgorithmPanelInfo.OnSelection
					,ReqAlgorithmPanelInfo.OnMoving
					,ReqAlgorithmPanelInfo.SelectionDx,ReqAlgorithmPanelInfo.SelectionDy);
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckAlgorithmPanelImage::IntegrationAckAlgorithmPanelImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	ImageBuff=NULL;
}
IntegrationAckAlgorithmPanelImage::~IntegrationAckAlgorithmPanelImage(void)
{
	ImageBuff=NULL;
}
bool	IntegrationAckAlgorithmPanelImage::Load(QIODevice *f)
{
	struct _AckAlgorithmPanelInfo	tAckAlgorithmPanelInfo;

	if(f->read((char *)&tAckAlgorithmPanelInfo,sizeof(tAckAlgorithmPanelInfo))!=sizeof(tAckAlgorithmPanelInfo)){
		return false;
	}

	int	slaveNo=GetSlaveNo();
	if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==false){
		slaveNo=0;
	}
	GUIFormBase *Ret[100];
	IntegrationAlgoSimpleImagePanel	*P=NULL;
	int	N=GetLayersBase()->EnumGUIInst(GetEmitterRoot(),GetEmitterName(),Ret,100);
	for(int i=0;i<N;i++){
		IntegrationAlgoSimpleImagePanel	*p=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Ret[i]);
		if(p!=NULL && p->GetSlaveNo()==slaveNo){
			P=p;
			ImageBuff=P->TransferedImage[slaveNo];
			break;
		}
	}

	if(P!=NULL){
		int	W4=tAckAlgorithmPanelInfo.CanvasWidth*(tAckAlgorithmPanelInfo.CountOfLayer+1);
		if(tAckAlgorithmPanelInfo.CanvasWidth !=AckAlgorithmPanelInfo.CanvasWidth
		|| tAckAlgorithmPanelInfo.CanvasHeight!=AckAlgorithmPanelInfo.CanvasHeight){
			if(P->TransferedImage[slaveNo]!=NULL){
				delete	[]P->TransferedImage[slaveNo];
			}
			delete	[]P->TransferedImage[slaveNo];
			P->TransferedImage[slaveNo]=new BYTE [W4*tAckAlgorithmPanelInfo.CanvasHeight];
			ImageBuff=P->TransferedImage[slaveNo];

			if(P->TRansferedBuffer[slaveNo]!=NULL){
				delete	[]P->TRansferedBuffer[slaveNo];
			}
			P->TRansferedBuffer[slaveNo]=new BYTE[W4*tAckAlgorithmPanelInfo.CanvasHeight];
		}
		AckAlgorithmPanelInfo=tAckAlgorithmPanelInfo;

		
		if(f->read((char *)P->TransferedImage[slaveNo],AckAlgorithmPanelInfo.CanvasHeight*W4)!=AckAlgorithmPanelInfo.CanvasHeight*W4){
			return false;
		}
		//if(f->read((char *)P->TRansferedBuffer[slaveNo],AckAlgorithmPanelInfo.CanvasHeight*W4)!=AckAlgorithmPanelInfo.CanvasHeight*W4){
		//	return false;
		//}

	}
	return true;
}
bool	IntegrationAckAlgorithmPanelImage::Save(QIODevice *f)
{
	int	slaveNo=GetSlaveNo();
	if(GetLayersBase()->GetIntegrationBasePointer()->IsMastered()==false){
		slaveNo=0;
	}

	GUIFormBase *Ret[100];
	IntegrationAlgoSimpleImagePanel	*P=NULL;
	int	N=GetLayersBase()->EnumGUIInst(GetEmitterRoot(),GetEmitterName(),Ret,100);
	for(int i=0;i<N;i++){
		IntegrationAlgoSimpleImagePanel	*p=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Ret[i]);
		if(p!=NULL){
			P=p;
			ImageBuff=P->TransferedImage[slaveNo];
			break;
		}
	}

	if(f->write((char *)&AckAlgorithmPanelInfo,sizeof(AckAlgorithmPanelInfo))!=sizeof(AckAlgorithmPanelInfo)){
		return false;
	}

	if(P!=NULL){
		int	W4=AckAlgorithmPanelInfo.CanvasWidth*(AckAlgorithmPanelInfo.CountOfLayer+1);

		if(f->write((char *)P->TransferedImage[slaveNo],AckAlgorithmPanelInfo.CanvasHeight*W4)!=AckAlgorithmPanelInfo.CanvasHeight*W4){
			return false;
		}
		//if(f->write((char *)P->TRansferedBuffer[slaveNo],AckAlgorithmPanelInfo.CanvasHeight*W4)!=AckAlgorithmPanelInfo.CanvasHeight*W4){
		//	return false;
		//}
	}
	return true;
}

void	IntegrationAckAlgorithmPanelImage::ConvertToImage(QImage &CurrentImage)
{
	int	XLen=min(CurrentImage.width() ,AckAlgorithmPanelInfo.CanvasWidth);
	int	YLen=min(CurrentImage.height(),AckAlgorithmPanelInfo.CanvasHeight);
	int	W4=AckAlgorithmPanelInfo.CanvasWidth*(AckAlgorithmPanelInfo.CountOfLayer+1);
	if(AckAlgorithmPanelInfo.CountOfLayer==1){
		for(int y=0;y<YLen;y++){
			BYTE	*s=&ImageBuff[y*W4];
			QRgb	*d=(QRgb *)CurrentImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				BYTE	c0=*s;
				BYTE	a=*(s+1);
				*d=qRgba(c0,c0,c0,a);
				d++;
				s+=2;
			}
		}
	}
	else
	if(AckAlgorithmPanelInfo.CountOfLayer==2){
		for(int y=0;y<YLen;y++){
			BYTE	*s=&ImageBuff[y*W4];
			QRgb	*d=(QRgb *)CurrentImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				BYTE	c0=*s;
				BYTE	c1=*(s+1);
				BYTE	a=*(s+2);
				*d=qRgba(c0,c1,c1,a);
				d++;
				s+=3;
			}
		}
	}
	else
	if(AckAlgorithmPanelInfo.CountOfLayer>=3){
		for(int y=0;y<YLen;y++){
			BYTE	*s=&ImageBuff[y*W4];
			QRgb	*d=(QRgb *)CurrentImage.scanLine(y);
			for(int x=0;x<XLen;x++){
				BYTE	c0=*s;
				BYTE	c1=*(s+1);
				BYTE	c2=*(s+2);
				BYTE	a=*(s+3);
				*d=qRgba(c0,c1,c2,a);
				d++;
				s+=4;
			}
		}
	}

}

//=============================================================================================
IntegrationCmdAlgorithmPanelAddItem::IntegrationCmdAlgorithmPanelAddItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Phase=0;
}
bool	IntegrationCmdAlgorithmPanelAddItem::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	if(::Load(f,SomethingData)==false)
		return false;
	return true;
}
bool	IntegrationCmdAlgorithmPanelAddItem::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	if(::Save(f,SomethingData)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelAddItem::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		GUIFormBase		*Form=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL && Form!=NULL){
			IntegrationAlgoSimpleImagePanel	*GForm=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Form);
			if(GForm!=NULL){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
				if(Ah!=NULL){
					IntList	PageList;
					GetLayersBase()->GetLocalPageFromArea(Area,PageList);
					if(PageList.GetCount()>0){
						GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Add item in Integrator");
						for(IntClass *v=PageList.GetFirst();v!=NULL;v=v->GetNext()){
							int	Page=v->GetValue();
							AlgorithmInPageRoot	*Ap=Ah->GetPageData(Page);
							DataInPage	*pdata=GetLayersBase()->GetPageData(Page);
							if(Ap!=NULL && pdata!=NULL){
								FlexArea	A=Area;
								pdata->ClipMoveAreaFromGlobal(A);
								if(A.GetPatternByte()>0){
									GForm->AddItemInAlgorithm(slaveNo,Ap,LayerList ,A,Data,SomethingData);
								}
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================================
IntegrationCmdAlgorithmPanelDeleteSelectItems::IntegrationCmdAlgorithmPanelDeleteSelectItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Phase=0;
}
bool	IntegrationCmdAlgorithmPanelDeleteSelectItems::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	if(::Load(f,SomethingData)==false)
		return false;
	
	return true;
}
bool	IntegrationCmdAlgorithmPanelDeleteSelectItems::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	if(::Save(f,SomethingData)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelDeleteSelectItems::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase		*Form=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	IntegrationAlgoSimpleImagePanel	*GForm=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Form);
	if(GForm!=NULL){
		if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
			if(Ab!=NULL){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
				if(Ah!=NULL){
					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Delete selected items in Integrator");
					for(int page=0;page<GetPageNumb();page++){
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
						if(Ap!=NULL){
							IntList	LayerList;
							for(int layer=0;layer<Ap->GetLayerNumb();layer++){
								LayerList.Add(layer);
							}
							GForm->DelSelectedItemsInAlgorithm(slaveNo,Ap,LayerList,SomethingData);
						}
					}
				}
			}
		}
	}
}

//=============================================================================================
IntegrationCmdAlgorithmPanelCutItem::IntegrationCmdAlgorithmPanelCutItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Phase=0;
}
bool	IntegrationCmdAlgorithmPanelCutItem::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	if(::Load(f,SomethingData)==false)
		return false;	
	return true;
}
bool	IntegrationCmdAlgorithmPanelCutItem::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	if(::Save(f,SomethingData)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelCutItem::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase		*Form=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	IntegrationAlgoSimpleImagePanel	*GForm=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Form);
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				IntList	PageList;
				GetLayersBase()->GetLocalPageFromArea(Area,PageList);
				if(PageList.GetCount()>0){
					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Cut item in Integrator");
					for(IntClass *v=PageList.GetFirst();v!=NULL;v=v->GetNext()){
						int	Page=v->GetValue();
						DataInPage	*pdata=GetLayersBase()->GetPageData(Page);
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(Page);
						if(Ap!=NULL && pdata!=NULL){
							FlexArea	A=Area;
							pdata->ClipMoveAreaFromGlobal(A);
							if(A.GetPatternByte()>0){
								GForm->CutItemInAlgorithm	(GetSlaveNo(),Ap ,LayerList ,A ,SomethingData);
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================================

IntegrationCmdAlgorithmPanelSelectArea::IntegrationCmdAlgorithmPanelSelectArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Phase=0;
}
bool	IntegrationCmdAlgorithmPanelSelectArea::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	if(::Load(f,SomethingData)==false)
		return false;
	return true;
}
bool	IntegrationCmdAlgorithmPanelSelectArea::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	if(::Save(f,SomethingData)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelSelectArea::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlgorithmPanelSelectArea	*SendBack=GetSendBackIntegration(IntegrationCmdAckAlgorithmPanelSelectArea,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(EmitterRoot ,EmitterName ,Ret ,100);
	SendBack->SelectedContainer.RemoveAll();
	for(int i=0;i<N;i++){
		IntegrationAlgoSimpleImagePanel	*p=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Ret[i]);
		if(p!=NULL){
			//if(GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(p->MachineCode)==slaveNo){
				p->SelectItem(Phase,LayerList,Area,SendBack->SelectedContainer,SomethingData);
				break;
			//}
		}
	}

	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

	
IntegrationCmdAckAlgorithmPanelSelectArea::IntegrationCmdAckAlgorithmPanelSelectArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckAlgorithmPanelSelectArea::Load(QIODevice *f)
{
	if(SelectedContainer.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckAlgorithmPanelSelectArea::Save(QIODevice *f)
{
	if(SelectedContainer.Save(f)==false)
		return false;
	return true;
}

IntegrationCmdAlgorithmPanelSelectItems::IntegrationCmdAlgorithmPanelSelectItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAlgorithmPanelSelectItems::Load(QIODevice *f)
{
	if(SelectedContainer.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAlgorithmPanelSelectItems::Save(QIODevice *f)
{
	if(SelectedContainer.Save(f)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelSelectItems::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase *Ret[100];
	int	N=GetLayersBase()->EnumGUIInst(EmitterRoot ,EmitterName ,Ret ,100);
	for(int i=0;i<N;i++){
		IntegrationAlgoSimpleImagePanel	*p=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Ret[i]);
		if(p!=NULL){
			//if(GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(p->MachineCode)==slaveNo){
				p->SelectItem(SelectedContainer);
				break;
			//}
		}
	}
}


//=============================================================================================
IntegrationCmdAlgorithmPanelReleaseSelection::IntegrationCmdAlgorithmPanelReleaseSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAlgorithmPanelReleaseSelection::Load(QIODevice *f)
{
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	return true;
}
bool	IntegrationCmdAlgorithmPanelReleaseSelection::Save(QIODevice *f)
{
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelReleaseSelection::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			Ab->ReleaseAllSelectedItem();
		}
	}
}

//=============================================================================================
IntegrationCmdAlgorithmPanelMoveSelection::IntegrationCmdAlgorithmPanelMoveSelection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAlgorithmPanelMoveSelection::Load(QIODevice *f)
{
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	return true;
}
bool	IntegrationCmdAlgorithmPanelMoveSelection::Save(QIODevice *f)
{
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	return true;
}

void	IntegrationCmdAlgorithmPanelMoveSelection::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase		*Form=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	IntegrationAlgoSimpleImagePanel	*GForm=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(Form);
	if(GForm!=NULL){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Move selected items in Integrator");
		GForm->ExecuteMoveItems(AlgoDLLRoot,AlgoDLLName,Dx,Dy);
	}
}

IntegrationCmdReqHasSelectedItem::IntegrationCmdReqHasSelectedItem(LayersBase *Base 
																,const QString &EmitterRoot,const QString &EmitterName 
																,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqHasSelectedItem::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,AlgoDLLRoot)==false)
		return false;
	if(::Load(f,AlgoDLLName)==false)
		return false;
	return true;
}
bool	IntegrationCmdReqHasSelectedItem::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,AlgoDLLRoot)==false)
		return false;
	if(::Save(f,AlgoDLLName)==false)
		return false;
	return true;
}

void	IntegrationCmdReqHasSelectedItem::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckHasSelectedItem	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckHasSelectedItem,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
	if(Ab!=NULL){
		AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
		if(Ah!=NULL){
			SendBack->SelectedItemCount=Ah->GetSelectedItemCount();
		}
	}
	int	LocalPage=cmd;
	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckHasSelectedItem::IntegrationCmdAckHasSelectedItem(LayersBase *Base 
								,const QString &EmitterRoot,const QString &EmitterName 
								,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	SelectedItemCount=0;
}
bool	IntegrationCmdAckHasSelectedItem::Load(QIODevice *f)
{
	if(::Load(f,SelectedItemCount)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckHasSelectedItem::Save(QIODevice *f)
{
	if(::Save(f,SelectedItemCount)==false)
		return false;
	return true;
}

//=============================================================================================

IntegrationCmdReqAlgoDataWithControlPoints::IntegrationCmdReqAlgoDataWithControlPoints(LayersBase *Base 
										,const QString &EmitterRoot,const QString &EmitterName 
										,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdReqAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(::Load(f,ShadowLevel	)==false)	return false;
	if(::Load(f,ShadowNumber)==false)	return false;
	if(::Load(f,Phase		)==false)	return false;
	if(AlgorithmList.Load(f)==false)	return false;
	if(::Load(f,CopyToSlaveInfo	)==false)	return false;
	if(::Load(f,DLLRoot		)==false)	return false;
	if(::Load(f,DLLName		)==false)	return false;
	return true;
}
bool	IntegrationCmdReqAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(::Save(f,ShadowLevel	)==false)	return false;
	if(::Save(f,ShadowNumber)==false)	return false;
	if(::Save(f,Phase		)==false)	return false;
	if(AlgorithmList.Save(f)==false)	return false;
	if(::Save(f,CopyToSlaveInfo	)==false)	return false;
	if(::Save(f,DLLRoot		)==false)	return false;
	if(::Save(f,DLLName		)==false)	return false;
	return true;
}

void	IntegrationCmdReqAlgoDataWithControlPoints::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlgoDataWithControlPoints	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckAlgoDataWithControlPoints,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);
	LayersBase	*L=GetLayersBase()->GetShadowTree(ShadowLevel ,ShadowNumber);

	AlgorithmBase	*GUIABase=NULL;
	IntegrationAlgoSimpleImagePanel	*P=NULL;
	GUIFormBase	*f=GetLayersBase()->FindByName(DLLRoot,DLLName,/**/"");
	if(f!=NULL){
		P=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(f);
		if(P!=NULL){
			GUIABase=P->GetAlgorithmBase();
		}
	}
	int	LocalPage=cmd;

	SendBack->ControlPointsForPages=L->GetControlPointsForPages(Phase,LocalPage);
	for(LogicDLL *DLL=L->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
		if(AlgorithmList.GetCount()==0
		|| AlgorithmList.Exists(DLL->GetDLLRoot(),DLL->GetDLLName())==true){
			AlgorithmBase	*ABase=DLL->GetInstance();
			AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
				if(GUIABase!=NULL && P!=NULL){
					QByteArray	RetData;
					if(P->LoadCopyToSlaveInfo(CopyToSlaveInfo,Ap,RetData)==true){
						AlgoListArray	*a=new AlgoListArray();
						a->DLLRoot=DLL->GetDLLRoot();
						a->DLLName=DLL->GetDLLName();
						a->Array	=RetData;
						SendBack->AlgoList.AppendList(a);
					}
					else{
						P=NULL;
					}
				}
				if(GUIABase==NULL || P==NULL){
					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					Ap->Save(&Buff);
					AlgoListArray	*a=new AlgoListArray();
					a->DLLRoot=DLL->GetDLLRoot();
					a->DLLName=DLL->GetDLLName();
					a->Array	=Buff.buffer();
					SendBack->AlgoList.AppendList(a);
				}
			}
		}
	}

	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}
IntegrationCmdAckAlgoDataWithControlPoints::IntegrationCmdAckAlgoDataWithControlPoints(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdAckAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(ControlPointsForPages.Load(f)==false)
		return false;
	if(AlgoList.Load(f)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(ControlPointsForPages.Save(f)==false)
		return false;
	if(AlgoList.Save(f)==false)
		return false;
	return true;
}
	
IntegrationCmdSetAlgoDataWithControlPoints::IntegrationCmdSetAlgoDataWithControlPoints(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSetAlgoDataWithControlPoints::Load(QIODevice *f)
{
	if(::Load(f,ShadowLevel	)==false)	return false;
	if(::Load(f,ShadowNumber)==false)	return false;
	if(::Load(f,Phase		)==false)	return false;
	if(ControlPointsForPages.Load(f)==false)
		return false;
	if(AlgoList.Load(f)==false)
		return false;
	if(::Load(f,GUIRoot		)==false)	return false;
	if(::Load(f,GUIName		)==false)	return false;
	if(::Load(f,ClearBeforeCopy)==false)	return false;
	return true;
}
bool	IntegrationCmdSetAlgoDataWithControlPoints::Save(QIODevice *f)
{
	if(::Save(f,ShadowLevel	)==false)	return false;
	if(::Save(f,ShadowNumber)==false)	return false;
	if(::Save(f,Phase		)==false)	return false;
	if(ControlPointsForPages.Save(f)==false)
		return false;
	if(AlgoList.Save(f)==false)
		return false;
	if(::Save(f,GUIRoot		)==false)	return false;
	if(::Save(f,GUIName		)==false)	return false;
	if(::Save(f,ClearBeforeCopy)==false)	return false;
	return true;
}

void	IntegrationCmdSetAlgoDataWithControlPoints::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase()->GetShadowTree(ShadowLevel ,ShadowNumber);
	int		LocalPage=cmd;
	GUIFormBase	*f=L->FindByName(GUIRoot,GUIName,/**/"");
	TransformBase	*Param=TransformBase::MakeTransformParamControlPoints(L->GetControlPointsForPages(Phase,LocalPage) ,ControlPointsForPages);
	if(f!=NULL && Param!=NULL){
		IntegrationAlgoSimpleImagePanel	*AlgoF=dynamic_cast<IntegrationAlgoSimpleImagePanel *>(f);
		if(AlgoF!=NULL){
			for(LogicDLL *DLL=L->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
				for(AlgoListArray *a=AlgoList.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->DLLRoot==DLL->GetDLLRoot() && a->DLLName==DLL->GetDLLName()){
						AlgorithmBase	*ABase=DLL->GetInstance();
						AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(Phase);
						AlgorithmInPageRoot		*Ap=Ah->GetPageData(LocalPage);
						AlgoF->SaveCopyToSlaveInfo(a->Array,Ap,Param,ClearBeforeCopy);
					}
				}
			}
		}
	}
	delete	Param;
}

