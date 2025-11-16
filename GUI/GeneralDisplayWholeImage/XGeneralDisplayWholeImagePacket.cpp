#include "GeneralDisplayWholeImage.h"
#include "XGUIFormBase.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "swap.h"

//=======================================================================

GUICmdReqWholeBmp::GUICmdReqWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ZoomRate=0.1;
	ShowFixedPhase	=-1;
}

bool	GUICmdReqWholeBmp::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,ShowNG)==false)
		return false;
	if(::Save(f,ShowFixedPhase)==false)
		return false;
	return(true);
}
bool	GUICmdReqWholeBmp::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,ShowNG)==false)
		return false;
	if(::Load(f,ShowFixedPhase)==false)
		return false;
	return(true);
}


void	GUICmdReqWholeBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendWholeBmp	*SendBack=GetSendBack(GUICmdSendWholeBmp,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeImage(Mastered,ZoomRate
						,localPage
						,*GetLayersBase()
						,ShowNG
						,ShowFixedPhase);
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendWholeBmp::GUICmdSendWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData=NULL;
}

GUICmdSendWholeBmp::~GUICmdSendWholeBmp(void)
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

bool	GUICmdSendWholeBmp::Load(QIODevice *f)
{
	if(IData==NULL)
		IData=new QImage();
	IData->load(f,/**/"PNG");
	return(true);
}
bool	GUICmdSendWholeBmp::Save(QIODevice *f)
{
	IData->save(f,/**/"PNG");
	return(true);
}

void	GUICmdSendWholeBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

bool	GUICmdSendWholeBmp::MakeImage( bool Mastered ,double ZoomRate
								 ,int localPage
								 ,LayersBase &LocalLBase
								 ,bool ShowNG
								 ,int32 ShowFixedPhase)
{
	DataInPage *P;
	if(ShowFixedPhase==-1){
		P=LocalLBase.GetPageData(localPage);
	}
	else{
		P=LocalLBase.GetPageDataPhase(ShowFixedPhase)->GetPageData(localPage);
	}
	if(LocalLBase.TryLockRChangingDataStructure()==false){
		return false;
	}

	int	LGx=P->GetDotPerLine()*ZoomRate;
	int	LGy=P->GetMaxLines()*ZoomRate;
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		delete	IData;
		IData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_RGB32);
	}
	
	if(P->GetLayerNumb()==1){	
		ImageBuffer	*SBuff0=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();
		if(SBuff0->IsNull()==false){
			int	MaxBuffY=SBuff0->GetHeight();
			int	iMaxLines=min(MaxBuffY,P->GetMaxLines());
			bool	UseTable=P->GetLayerData(0)->CData.UseTable ;
			if(UseTable==true){
				BYTE	*CTable0=P->GetLayerData(0)->CData.RBrightTable;
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							int	iDotPerLine=P->GetDotPerLine();
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								int	K=CTable0[*(s0+NowX)];
								*((int32 *)d)=0xFF000000+(K<<16)+(K<<8)+K;
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
			else{
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							int	iDotPerLine=P->GetDotPerLine();
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								int	K=*(s0+NowX);
								*((int32 *)d)=0xFF000000+(K<<16)+(K<<8)+K;
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
		}
	}
	else
	if(P->GetLayerNumb()==2){
		ImageBuffer	*SBuff0=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	*SBuff1=(Mastered==true)?&P->GetLayerData(1)->GetMasterBuff():&P->GetLayerData(1)->GetTargetBuff();
		if(SBuff0->IsNull()==false
		&& SBuff1->IsNull()==false){
			bool	UseTable=( (P->GetLayerData(0)->CData.UseTable==true)
							|| (P->GetLayerData(1)->CData.UseTable==true))?true:false ;
			int	MaxBuffY=SBuff0->GetHeight();
			int	iMaxLines=min(MaxBuffY,P->GetMaxLines());
			if(UseTable==true){
				BYTE	*CTable0=P->GetLayerData(0)->CData.RBrightTable;
				BYTE	*CTable1=P->GetLayerData(1)->CData.RBrightTable;
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							BYTE	*s1=SBuff1->GetY(NowY);
							int	iDotPerLine=P->GetDotPerLine();
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								*((int32 *)d)=0xFF000000+((CTable0[*(s0+NowX)])<<16)+((CTable1[*(s1+NowX)])<<8);
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
			else{
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							BYTE	*s1=SBuff1->GetY(NowY);
							int	iDotPerLine=P->GetDotPerLine();
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8);
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
		}
	}
	else
	if(P->GetLayerNumb()>=3){
		ImageBuffer	*SBuff0=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	*SBuff1=(Mastered==true)?&P->GetLayerData(1)->GetMasterBuff():&P->GetLayerData(1)->GetTargetBuff();
		ImageBuffer	*SBuff2=(Mastered==true)?&P->GetLayerData(2)->GetMasterBuff():&P->GetLayerData(2)->GetTargetBuff();
		if(SBuff0->IsNull()==false
		&& SBuff1->IsNull()==false
		&& SBuff2->IsNull()==false){
			bool	UseTable=( (P->GetLayerData(0)->CData.UseTable==true)
							|| (P->GetLayerData(1)->CData.UseTable==true)
							|| (P->GetLayerData(2)->CData.UseTable==true))?true:false ;
			int	iDotPerLine=P->GetDotPerLine();
			int	MaxBuffY=SBuff0->GetHeight();
			int	iMaxLines=min(MaxBuffY,P->GetMaxLines());
			if(UseTable==true){
				BYTE	*CTable0=P->GetLayerData(0)->CData.RBrightTable;
				BYTE	*CTable1=P->GetLayerData(1)->CData.RBrightTable;
				BYTE	*CTable2=P->GetLayerData(2)->CData.RBrightTable;
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							BYTE	*s1=SBuff1->GetY(NowY);
							BYTE	*s2=SBuff2->GetY(NowY);
							
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								*((int32 *)d)=0xFF000000+((CTable0[*(s0+NowX)])<<16)+((CTable1[*(s1+NowX)])<<8)+((CTable2[*(s2+NowX)]));
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
			else{
				//#pragma omp parallel                  
				//{                                                
				//	#pragma omp for
					for(int y=0;y<LGy;y++){
						BYTE	*d=IData->scanLine(y);
						int	NowY=y/ZoomRate;
						if(NowY<0 || NowY>=iMaxLines){
							memset(d,0,LGx*4);
						}
						else{
							int	x=0;
							int64	mx=0;
							BYTE	*s0=SBuff0->GetY(NowY);
							BYTE	*s1=SBuff1->GetY(NowY);
							BYTE	*s2=SBuff2->GetY(NowY);
							
							for(;x<LGx;x++){
								int	NowX=mx>>32;
								if(NowX>=iDotPerLine)
									break;
								*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
								d+=4;
								mx+=AddX;
							}
							memset(d,0,(LGx-x)*4);
						}
					}
				//}
			}
		}
	}
	if(ShowNG==true){
		QPainter PntFromIData(IData);
//		PntFromIData.setPen(Qt::red);
//		PntFromIData.setBrush(Qt::red);
		ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
		if(DRes!=NULL){
			for(LogicDLL *L=LocalLBase.GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L->GetInstance());
				if(Res!=NULL){
					if(Res->DrawResult(ShowFixedPhase,PntFromIData ,IData ,0,0,ZoomRate ,localPage)==false){
						break;
					}
				}
			}
		}
	}
	LocalLBase.UnlockChangingDataStructure();
	return true;
}
