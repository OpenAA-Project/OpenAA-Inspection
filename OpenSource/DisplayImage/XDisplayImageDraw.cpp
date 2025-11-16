#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"


void	DisplayImage::DrawInsideFunc(QPainter &pnt ,QImage &PntImage ,IntList &_LayerList)
{
	//DWORD	t	=::GetComputerMiliSec();
	//if(t-LastTimeToDraw<MinInterval)
	//	return;
	if(GetLayersBase()->IsPossibleToUpdateDisplay()==true){
		MainCanvas->SetFModeRepaintOnMouseMove(FModeRepaintOnMouseMove);

		if(HookedExecutePaintFirst(pnt,PntImage)==true){
			//DWORD	t1=::GetComputerMiliSec()-t;
			if(GetDisplayType()!=__NoImage){
				if(0<=ShowOnePage && ShowOnePage<GetPageNumb()){
					if(DrawImageOnePage(pnt ,PntImage,_LayerList)==false){
						return;
					}
				}
				else if(ShowOnePage<0){
					if(DrawImage(pnt ,PntImage,_LayerList)==false){
						return;
					}
				}
			}
			else{
				//PntImage.fill(Qt::black);
				::ClearImage(PntImage, 255);
			}

			emit	SignalDrawFunc(pnt ,PntImage ,_LayerList);

			//DWORD	t2=::GetComputerMiliSec()-t;
			DrawMeasure(pnt ,PntImage);					
			//DWORD	t3=::GetComputerMiliSec()-t;
			DrawExpandedPaste(pnt,PntImage);			
			//DWORD	t4=::GetComputerMiliSec()-t;
			DrawSaveImageOnPoint(pnt,PntImage);			

			//DWORD	t5=::GetComputerMiliSec()-t;
			DrawAfterImage(pnt,PntImage);				
			//DWORD	t6=::GetComputerMiliSec()-t;
			DrawPaste(pnt,PntImage);					
		}
		HookedExecutePaintLast(pnt,PntImage);
		//DWORD	t7=::GetComputerMiliSec()-t;
		DrawScale(pnt);
	}
	//LastTimeToDraw=t;
}

void	DisplayImage::StartDrawInBack(void)
{
	ModeToMakeImageInThread=true;
	//DisplayImageThreadInst.start();
}

bool	DisplayImage::DrawImage(QPainter &pnt  ,QImage &PntImage,IntList &LayerList)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	LayersBase	*LBase=GetLayersBase();
	LBase->GetArea(globalX1,globalY1 ,globalX2,globalY2);
	AllocInnerBuff();

	for(int page=0;page<LBase->GetPageNumb();page++){
		int	globalPage=LBase->GetGlobalPageFromLocal(page);
		if(LBase->GetSendingData(globalPage)==true){
			return false;
		}
	}

	//??????M??t??????O??N??????A
	for(int page=0;page<LBase->GetPageNumb();page++){
		BmpReceiver[page]->ClearReceivedFlag();
	}
	if(ModeShowOnlyTopTurn==false){
		int	N=0;
		for(int page=0;page<LBase->GetPageNumb();page++){
			//??O??????[??o??????y??[??W??O?I?I?i??
			int	globalPage=LBase->GetGlobalPageFromLocal(page);

			DataInPage *P=LBase->GetPageData(page);
			//??????z??L??????????o??X??I?i????I?i????a??i??I?`??????I?i??
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);	//??????a??i??`??????I?i????????????E?i??W??E?I?i??
			ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, MainCanvas->GetCanvasWidth(), MainCanvas->GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==false){
				continue;
			}
			BmpRequester[N]->Data.DType		=DType;
			BmpRequester[N]->Data.MasterNo	=CurrentMasterNo;
			BmpRequester[N]->Data.ShowFixedPhase	=ShowFixedPhase;
			//??g??a?|??A??????s??U?i????E?i????Y?i??
			BmpRequester[N]->Data.ZoomRate	=MainCanvas->GetZoomRate();
			BmpRequester[N]->Data.Yz		=Yz;
			BmpRequester[N]->Data.MovX		=MainCanvas->GetMovx()+P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.MovY		=MainCanvas->GetMovy()+P->GetOutlineOffset()->y;
			//if(BmpRequester[N]->Data.MovX>0){
			//	BmpRequester[N]->Data.MovX=0;
			//}
			//if(BmpRequester[N]->Data.MovY>0){
			//	BmpRequester[N]->Data.MovY=0;
			//}
			BmpRequester[N]->Data.GlobalPage	=globalPage;
			BmpReceiver[N]->SetGlobalPage(globalPage);
			if(Gx1<0){
				Gx1=0;
			}
			if(Gy1<0){
				Gy1=0;
			}
			//??????E?I?I?I?i??????
			if(Gx2>MainCanvas->GetCanvasWidth()){
				Gx2=MainCanvas->GetCanvasWidth();
			}
			if(Gy2>MainCanvas->GetCanvasHeight()){
				Gy2=MainCanvas->GetCanvasHeight();
			}
			//??f??[??^??????R??}??????h??p??P??b??g??E?R??s??[
			BmpRequester[N]->Data.RedCircleMode=RedCircleMode;
			BmpRequester[N]->LayerList	=LayerList;		//??`??a??i??C??????[
			BmpRequester[N]->Data.Gx1		=Gx1;
			BmpRequester[N]->Data.Gy1		=Gy1;
			BmpRequester[N]->Data.Gx2		=Gx2;
			BmpRequester[N]->Data.Gy2		=Gy2;
			ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
			ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
			BmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.TransparentLevelInBitBuff	=TransparentLevelInBitBuff;
			BmpRequester[N]->Data.ShowNGMarkInTarget	=ShowNGMarkInTarget;
			BmpRequester[N]->Data.RepaintContinuously	=RepaintContinuously;
			N++;
		}
		if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()!=0){
			if(N>1){
				NPListPack<GUICmdPacketDim>	GUICmdDim;
				for(int n=0;n<N;n++){
					if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
					&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
						GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[n],BmpReceiver[n],BmpRequester[n]->Data.GlobalPage,0));
					}
				}
				if(LBase->PacketSender(GUICmdDim,5000)==false){
					return false;
				}
			}
			else if(N>=1){
				BmpRequester[0]->Send(BmpRequester[0]->Data.GlobalPage,0,*BmpReceiver[0],5000);
			}
		}
		else{
			for(int n=0;n<N;n++){
				if(BmpReceiver[n]->MakeImage(DType
								 , BmpRequester[n]->Data.Gx1, BmpRequester[n]->Data.Gy1 , BmpRequester[n]->Data.Gx2, BmpRequester[n]->Data.Gy2
								 , BmpRequester[n]->Data.Dx1, BmpRequester[n]->Data.Dy1 , BmpRequester[n]->Data.Dx2, BmpRequester[n]->Data.Dy2
								 , BmpRequester[n]->Data.MovX, BmpRequester[n]->Data.MovY,  BmpRequester[n]->Data.ZoomRate, BmpRequester[n]->Data.Yz
								 , LBase->GetLocalPageFromGlobal(BmpRequester[n]->Data.GlobalPage)
								 ,*LBase
								 ,CurrentMasterNo
								 ,LayerList
								 , RedCircleMode
								 , ShowFixedPhase
								 , TransparentLevelInBitBuff
								 ,ShowNGMarkInTarget
								 ,RepaintContinuously)==false){
					return false;
				}
				BmpReceiver[n]->SetReceived(true);

				//BmpReceiver[n]->NGData->save("TestPNG.png");
			}
		}
		if(LBase->GetOnTerminating()==true){
			return false;
		}
		LockPaintMutex();
		QBrush	brush(Qt::black);
		pnt.fillRect (0,0,MainCanvas->GetCanvas()->width(),MainCanvas->GetCanvas()->height(), brush );
	
		for(int page=LBase->GetPageNumb()-1;page>=0;page--){
			//??`??a????O?I?a??
			int	n=LBase->GetDrawturn(page)->GetPage();
			if(0<=n && n<N){
				if(BmpReceiver[n]->IsReceived()==true && BmpReceiver[n]->IData!=NULL){
					if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
						&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
						//??`????
						pnt.drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
								 ,*(const QImage *)BmpReceiver[n]->IData);
					}
				}
			}
		}
		if((DType==DisplayImage::__Target || DType==DisplayImage::__DelayedView)
		&& ShowNGMarkInTarget==true){
			pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
			for(int page=LBase->GetPageNumb()-1;page>=0;page--){
				//??`??a????O?I?a??
				int	n=LBase->GetDrawturn(page)->GetPage();
				if(0<=n && n<N){
					if(BmpReceiver[n]->IsReceived()==true && BmpReceiver[n]->RetNGData==true && BmpReceiver[n]->NGData!=NULL){
						if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
							&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
							//??`????
							pnt.drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
								 ,*(const QImage *)BmpReceiver[n]->NGData);
						}
					}
				}
			}
		}
		UnlockPaintMutex();
	}
	else{
		int	N=0;
		int	Pn=LBase->GetDrawturn(0)->GetPage();

		int	globalPage=LBase->GetGlobalPageFromLocal(Pn);

		DataInPage *P=LBase->GetPageData(Pn);
		int	Dx1	=P->GetOutlineOffset()->x;
		int	Dy1	=P->GetOutlineOffset()->y;
		int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
		int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
		int	Gx1,Gy1,Gx2,Gy2;
		ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);	//??????a??i??`??????I?i????????????E?i??W??E?I?i??
		ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
		if(CheckOverlapRectRectFast(0, 0, MainCanvas->GetCanvasWidth(), MainCanvas->GetCanvasHeight()
									,Gx1, Gy1, Gx2, Gy2)==false){
			return false;
		}
		BmpRequester[Pn]->Data.DType			=DType;
		BmpRequester[Pn]->Data.MasterNo			=CurrentMasterNo;
		BmpRequester[Pn]->Data.ShowFixedPhase	=ShowFixedPhase;

		BmpRequester[Pn]->Data.ZoomRate			=MainCanvas->GetZoomRate();
		BmpRequester[Pn]->Data.Yz				=Yz;
		BmpRequester[Pn]->Data.MovX				=MainCanvas->GetMovx()+P->GetOutlineOffset()->x;
		BmpRequester[Pn]->Data.MovY				=MainCanvas->GetMovy()+P->GetOutlineOffset()->y;

		BmpRequester[Pn]->Data.GlobalPage		=globalPage;
		BmpReceiver[Pn]->SetGlobalPage(globalPage);
		if(Gx1<0){
			Gx1=0;
		}
		if(Gy1<0){
			Gy1=0;
		}
		if(Gx2>MainCanvas->GetCanvasWidth()){
			Gx2=MainCanvas->GetCanvasWidth();
		}
		if(Gy2>MainCanvas->GetCanvasHeight()){
			Gy2=MainCanvas->GetCanvasHeight();
		}

		BmpRequester[Pn]->Data.RedCircleMode=RedCircleMode;
		BmpRequester[Pn]->LayerList	=LayerList;		//??`??a??i??C??????[
		BmpRequester[Pn]->Data.Gx1		=Gx1;
		BmpRequester[Pn]->Data.Gy1		=Gy1;
		BmpRequester[Pn]->Data.Gx2		=Gx2;
		BmpRequester[Pn]->Data.Gy2		=Gy2;
		ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
		ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
		BmpRequester[Pn]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
		BmpRequester[Pn]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
		BmpRequester[Pn]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
		BmpRequester[Pn]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
		BmpRequester[Pn]->Data.TransparentLevelInBitBuff=TransparentLevelInBitBuff;
		BmpRequester[Pn]->Data.ShowNGMarkInTarget		=ShowNGMarkInTarget;
		BmpRequester[Pn]->Data.RepaintContinuously		=RepaintContinuously;
		N++;

		if(GetParamComm()->GetConnectedPCNumb()!=0){
			BmpRequester[Pn]->Send(globalPage,0,*BmpReceiver[Pn]);
			if(LBase->GetOnTerminating()==true){
				return false;
			}
		}
		else{
			if(BmpReceiver[Pn]->MakeImage(DType
						 ,BmpRequester[Pn]->Data.Gx1, BmpRequester[Pn]->Data.Gy1 , BmpRequester[Pn]->Data.Gx2		, BmpRequester[Pn]->Data.Gy2
						 ,BmpRequester[Pn]->Data.Dx1, BmpRequester[Pn]->Data.Dy1 , BmpRequester[Pn]->Data.Dx2		, BmpRequester[Pn]->Data.Dy2
						 ,BmpRequester[Pn]->Data.MovX,BmpRequester[Pn]->Data.MovY, BmpRequester[Pn]->Data.ZoomRate	, BmpRequester[Pn]->Data.Yz
						 ,LBase->GetLocalPageFromGlobal(BmpRequester[Pn]->Data.GlobalPage)
						 ,*LBase
						 ,CurrentMasterNo
						 ,LayerList
						 ,RedCircleMode
						 ,ShowFixedPhase
						 ,TransparentLevelInBitBuff
						 ,ShowNGMarkInTarget
						 ,RepaintContinuously)==false){
				return false;
			}
			BmpReceiver[Pn]->SetReceived(true);
		}

		LockPaintMutex();

		PntImage.fill(Qt::black);
		//::ClearImage(PntImage, 255);
		
		if(BmpReceiver[Pn]->IsReceived()==true && BmpReceiver[Pn]->IData!=NULL){
			if(BmpRequester[Pn]->Data.Gx1!=BmpRequester[Pn]->Data.Gx2
				&& BmpRequester[Pn]->Data.Gy1!=BmpRequester[Pn]->Data.Gy2){
				//pnt.drawImage(BmpRequester[Pn]->Data.Gx1 ,BmpRequester[Pn]->Data.Gy1
				//		 ,*(const QImage *)BmpReceiver[Pn]->IData);
				CopyPixels(PntImage ,*BmpReceiver[Pn]->IData
							,BmpRequester[Pn]->Data.Gx1 ,BmpRequester[Pn]->Data.Gy1
							,LBase->GetNumThreads());
			}
		}

		if((DType==DisplayImage::__Target || DType==DisplayImage::__DelayedView)
		&& ShowNGMarkInTarget==true){
			pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
			for(int page=LBase->GetPageNumb()-1;page>=0;page--){
				//??`??a????O?I?a??
				int	n=LBase->GetDrawturn(page)->GetPage();
				if(BmpReceiver[n]->IsReceived()==true && BmpReceiver[n]->RetNGData==true && BmpReceiver[n]->NGData!=NULL){
					if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
						&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
						pnt.drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
									,*(const QImage *)BmpReceiver[n]->NGData);
					}
				}
			}
			if(GetParamComm()->GetConnectedPCNumb()==0){
				//BmpReceiver[Pn]->NGData->fill(qRgba(0,0,0,0));
				::ClearImage(*BmpReceiver[Pn]->NGData, 0);
				bool	RetNGData=false;
				for(int page=LBase->GetPageNumb()-1;page>=0;page--){
					//??`??a????O?I?a??
					int	n=LBase->GetDrawturn(page)->GetPage();
					if(BmpReceiver[n]->IsReceived()==false){
						bool	TmpRetNGData;
						LBase->MakeImageNGCircle(BmpReceiver[Pn]->NGData ,BmpReceiver[Pn]->PntFromNGData
										,DType
										, Gx1, Gy1 , Gx2		, Gy2
										, BmpRequester[Pn]->Data.MovX,BmpRequester[Pn]->Data.MovY, BmpRequester[Pn]->Data.ZoomRate
										, n
										, RedCircleMode
										,ShowNGMarkInTarget
										,TmpRetNGData);
						if(TmpRetNGData==true){
							RetNGData=true;
						}
					}
				}
				if(RetNGData==true && BmpReceiver[Pn]->NGData!=NULL){
					MultiplyImage(*BmpReceiver[Pn]->NGData,0.4);
					pnt.drawImage(BmpRequester[Pn]->Data.Gx1 ,BmpRequester[Pn]->Data.Gy1
								,*(const QImage *)BmpReceiver[Pn]->NGData);
				}
			}
		}
		UnlockPaintMutex();
	}
	return true;
}

bool	DisplayImage::DrawImageOnePage(QPainter &pnt ,QImage &PntImage ,IntList &LayerList)
{
	if(ShowOnePage<0 || GetPageNumb()<=ShowOnePage)
		return false;
	LayersBase	*LBase=GetLayersBase();
	DataInPage *P=LBase->GetPageData(ShowOnePage);
	int	globalX2=P->GetDotPerLine();
	int	globalY2=P->GetMaxLines();
	
	AllocInnerBuff();

	int	globalPage=LBase->GetGlobalPageFromLocal(ShowOnePage);
	if(LBase->GetSendingData(globalPage)==true){
		return false;
	}

	//MainCanvas->SetAreaSize(globalX2+globalX2/20,globalY2+globalY2/20);
	MainCanvas->SetAreaSize(globalX2,globalY2);

	//??????M??t??????O??N??????A
	BmpReceiver[ShowOnePage]->ClearReceivedFlag();

	//??????z??L??????????o??X??I?i????I?i????a??i??I?`??????I?i??
	int	Dx1	=P->GetOutlineOffset()->x;
	int	Dy1	=P->GetOutlineOffset()->y;
	int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
	int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
	int	Gx1,Gy1,Gx2,Gy2;
	ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);	//??????a??i??`??????I?i????????????E?i??W??E?I?i??
	ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);

	GUICmdReqBmp	*Rb=BmpRequester[ShowOnePage];
	int	MainCanvasWidth	=MainCanvas->GetCanvasWidth();
	int	MainCanvasHeight=MainCanvas->GetCanvasHeight();

	if(CheckOverlapRectRectFast(0, 0, MainCanvasWidth, MainCanvasHeight
								,Gx1, Gy1, Gx2, Gy2)==true){
		Rb->Data.DType			=DType;
		Rb->Data.MasterNo		=CurrentMasterNo;
		Rb->Data.ShowFixedPhase	=ShowFixedPhase;
		//??g??a?|??A??????s??U?i????E?i????Y?i??
		Rb->Data.ZoomRate		=MainCanvas->GetZoomRate();
		Rb->Data.Yz				=Yz;
		Rb->Data.MovX			=MainCanvas->GetMovx();
		Rb->Data.MovY			=MainCanvas->GetMovy();
		Rb->Data.GlobalPage	=globalPage;
		BmpReceiver[ShowOnePage]->SetGlobalPage(globalPage);
		if(Gx1<0){
			Gx1=0;
		}
		if(Gy1<0){
			Gy1=0;
		}
		//??????E?I?I?I?i??????
		if(Gx2>MainCanvasWidth){
			Gx2=MainCanvasWidth;
		}
		if(Gy2>MainCanvasHeight){
			Gy2=MainCanvasHeight;
		}
		//??f??[??^??????R??}??????h??p??P??b??g??E?R??s??[
		Rb->Data.RedCircleMode=RedCircleMode;
		Rb->LayerList	=LayerList;		//??`??a??i??C??????[
		Rb->Data.Gx1		=Gx1;
		Rb->Data.Gy1		=Gy1;
		Rb->Data.Gx2		=Gx2;
		Rb->Data.Gy2		=Gy2;
		ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
		ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
		Rb->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
		Rb->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
		Rb->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
		Rb->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
		Rb->Data.TransparentLevelInBitBuff	=TransparentLevelInBitBuff;
		Rb->Data.ShowNGMarkInTarget			=ShowNGMarkInTarget;
		Rb->Data.RepaintContinuously		=RepaintContinuously;
	}

	if(GetParamComm()->GetConnectedPCNumb()!=0){
		if(Rb->Data.Gx1!=Rb->Data.Gx2
		&& Rb->Data.Gy1!=Rb->Data.Gy2){
			if(Rb->Send(globalPage,0,*BmpReceiver[ShowOnePage])==false){
				return false;
			}
		}
	}
	else{
		if(BmpReceiver[ShowOnePage]->MakeImage(DType
							 , Rb->Data.Gx1 ,Rb->Data.Gy1 , Rb->Data.Gx2	 , Rb->Data.Gy2
							 , Rb->Data.Dx1 ,Rb->Data.Dy1 , Rb->Data.Dx2	 , Rb->Data.Dy2
							 , Rb->Data.MovX,Rb->Data.MovY, Rb->Data.ZoomRate, Rb->Data.Yz
							 , LBase->GetLocalPageFromGlobal(Rb->Data.GlobalPage)
							 ,*LBase
							 ,CurrentMasterNo
							 ,LayerList
							 , RedCircleMode
							 , ShowFixedPhase
							 , TransparentLevelInBitBuff
							 ,ShowNGMarkInTarget
							 ,RepaintContinuously)==false){
			return false;
		}
		BmpReceiver[ShowOnePage]->SetReceived(true);
	}
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	LockPaintMutex();
	
	if(BmpReceiver[ShowOnePage]->IsReceived()==true
	&& Rb->Data.Gx1!=Rb->Data.Gx2
	&& Rb->Data.Gy1!=Rb->Data.Gy2
	&& BmpReceiver[ShowOnePage]->IData!=NULL){
		
		int	hx1=Rb->Data.Gx1;
		int	hy1=Rb->Data.Gy1;
		//if(ModeDrawOutOfView==true){

			int	hx2=hx1+((const QImage *)BmpReceiver[ShowOnePage]->IData)->width();
			int	hy2=hy1+((const QImage *)BmpReceiver[ShowOnePage]->IData)->height();
			//pnt.fillRect (0,0  ,MainCanvasWidth,hy1+1, brush );
			//pnt.fillRect (0,hy2,MainCanvasWidth,MainCanvasHeight-hy2, brush );
			//pnt.fillRect (0,hy1,hx1+1,hy2-hy1, brush );
			//pnt.fillRect (hx2,hy1,MainCanvasWidth-hx2,hy2-hy1, brush );
			QRgb	B=qRgb(0,0,0);
			if(hy1>0){
				DrawRect(PntImage,B,0  ,0  ,MainCanvasWidth,hy1 );
			}
			if(hy2<MainCanvasHeight){
				DrawRect(PntImage,B,0  ,hy2,MainCanvasWidth,MainCanvasHeight);
			}
			if(hx1>0){
				DrawRect(PntImage,B,0  ,hy1,hx1			 ,hy2);
			}
			if(hx2<MainCanvasWidth){
				DrawRect(PntImage,B,hx2,hy1,MainCanvasWidth,hy2);
			}
			ModeDrawOutOfView=false;
		//}
		//static	XDateTime	DrawTime[100];
		//static	int			IndexDrawTime=0;
		//DrawTime[IndexDrawTime]=XDateTime::currentDateTime();
		//IndexDrawTime++;
		//if(IndexDrawTime>=100)
		//	IndexDrawTime=0;
		// 
		//pnt.drawImage(hx1 ,hy1 ,*(const QImage *)BmpReceiver[ShowOnePage]->IData);
		::CopyPixels(PntImage, *BmpReceiver[ShowOnePage]->IData ,hx1 ,hy1
					,LBase->GetNumThreads());
	}
	else{
		//PntImage.fill(Qt::black);
		::ClearImage(PntImage, 255);
	}
	//2024.08.08
	if((DType==DisplayImage::__Target || DType==DisplayImage::__DelayedView)
	&& ShowNGMarkInTarget==true && BmpReceiver[ShowOnePage]->NGData!=NULL){
		if(BmpReceiver[ShowOnePage]->IsReceived()==true
		&& Rb->Data.Gx1!=Rb->Data.Gx2
		&& Rb->Data.Gy1!=Rb->Data.Gy2
		 && BmpReceiver[ShowOnePage]->RetNGData==true){
			pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
			pnt.drawImage(Rb->Data.Gx1 ,Rb->Data.Gy1
						,*(const QImage *)BmpReceiver[ShowOnePage]->NGData);
		}
	}
	UnlockPaintMutex();
	return true;
}
void	DisplayImage::DrawMeasure(QPainter &pnt ,QImage &PntImage)
{
	if(MeasureBtn!=NULL && MeasureBtn->isChecked()==true){
		if(DrawingMode==_MeasureSecond || DrawingMode==_MeasureDone){
			int	LocalX1;
			int	LocalY1;
			int	LocalX2;
			int	LocalY2;
			IntList PageList;
			GetLayersBase()->GetGlobalPage(MeasureStartGlobalX ,MeasureStartGlobalY
										,MeasureCurrentGlobalX ,MeasureCurrentGlobalY
										,PageList);
			ChangeDxy2Gxy(MeasureStartGlobalX,MeasureStartGlobalY ,LocalX1 ,LocalY1);
			ChangeDxy2Gxy(MeasureCurrentGlobalX,MeasureCurrentGlobalY ,LocalX2 ,LocalY2);

			LockPaintMutex();
			pnt.setPen(GetParamGlobal()->MeassurementColor);
			QBrush	Br(GetParamGlobal()->MeassurementColor);
			pnt.setBrush(Br);
			pnt.drawLine(LocalX1,LocalY1,LocalX2,LocalY2);
			double	L=hypot(MeasureStartGlobalX-MeasureCurrentGlobalX,MeasureStartGlobalY-MeasureCurrentGlobalY);
			QString	MeasureStr=QString::number(L,'f',2);
			pnt.drawLine(LocalX1,LocalY1,LocalX2,LocalY2);

			double	s=GetSita(LocalX2-LocalX1,LocalY2-LocalY1);
			QPoint	APoint[4];
			APoint[0].setX(LocalX1);
			APoint[0].setY(LocalY1);
			APoint[1].setX(LocalX1+20*cos(s+M_PI/6));
			APoint[1].setY(LocalY1+20*sin(s+M_PI/6));
			APoint[2].setX(LocalX1+10*cos(s));
			APoint[2].setY(LocalY1+10*sin(s));
			APoint[3].setX(LocalX1+20*cos(s-M_PI/6));
			APoint[3].setY(LocalY1+20*sin(s-M_PI/6));
			pnt.drawPolygon (APoint,4);

			s=GetSita(LocalX1-LocalX2,LocalY1-LocalY2);
			APoint[0].setX(LocalX2);
			APoint[0].setY(LocalY2);
			APoint[1].setX(LocalX2+20*cos(s+M_PI/6));
			APoint[1].setY(LocalY2+20*sin(s+M_PI/6));
			APoint[2].setX(LocalX2+10*cos(s));
			APoint[2].setY(LocalY2+10*sin(s));
			APoint[3].setX(LocalX2+20*cos(s-M_PI/6));
			APoint[3].setY(LocalY2+20*sin(s-M_PI/6));
			pnt.drawPolygon (APoint,4);

			int	StrW=pnt.fontMetrics().boundingRect(MeasureStr).width();
			int	StrH=pnt.fontMetrics().height();
			int rx1=(LocalX1+LocalX2)/2-StrW/2;
			int	ry1=(LocalY1+LocalY2)/2-StrH/2;
			int rx2=(LocalX1+LocalX2)/2+StrW/2;
			int	ry2=(LocalY1+LocalY2)/2+StrH/2;
			int	k;
			int	Page=ShowOnePage;
			if(PageList.GetCount()==1){
				Page=PageList.GetFirst()->GetValue();
			}
			for(k=0;k<40;k++){
				if(CheckOverlapRectLine(rx1, ry1+k, rx2, ry2+k ,LocalX1,LocalY1,LocalX2,LocalY2)==false){
					if(IsUnitMode()==true){
						pnt.drawText((LocalX1+LocalX2)/2-StrW/2,(LocalY1+LocalY2)/2+k+StrH/2,TransformPixelToUnitStr(Page,L)
																							+QString(" (")
																							+MeasureStr
																							+QString(")"));
					}
					else{
						pnt.drawText((LocalX1+LocalX2)/2-StrW/2,(LocalY1+LocalY2)/2+k+StrH/2,MeasureStr);
					}
					break;
				}
			}
			if(k>=40){
				for(k=0;k<200;k+=10){
					if(CheckOverlapRectLine(rx1+k, ry1, rx2+k, ry2 ,LocalX1,LocalY1,LocalX2,LocalY2)==false){
						if(IsUnitMode()==true){
							pnt.drawText((LocalX1+LocalX2)/2+k-StrW/2,(LocalY1+LocalY2)/2-StrH/2,TransformPixelToUnitStr(Page,L)
																							+QString(" (")
																							+MeasureStr
																							+QString(")"));
						}
						else{
							pnt.drawText((LocalX1+LocalX2)/2+k-StrW/2,(LocalY1+LocalY2)/2-StrH/2,MeasureStr);
						}
						break;
					}
				}
			}
			UnlockPaintMutex();
		}
	}
}

void	DisplayImage::DrawExpandedPaste(QPainter &pnt ,QImage &PntImage)
{
	if(ExpandedPasteBtn!=NULL && ExpandedPasteBtn->isChecked()==true && ExpandedPasteCurrent.IsEffective()==true){
		ExpandedPasteCurrent.Draw(this,pnt ,Qt::yellow,GetMovx(),GetMovy(),GetZoomRate(),GetCanvasWidth(),GetCanvasHeight());
		double	sita=GetSita(ExpandedPasteCurrent.ExpandedPasteFrame[1].X-ExpandedPasteCurrent.ExpandedPasteFrame[0].X
							,ExpandedPasteCurrent.ExpandedPasteFrame[1].Y-ExpandedPasteCurrent.ExpandedPasteFrame[0].Y);
		if(DrawingMode==_ExpandedPasteMove){
			ExpandedPasteCurrent.Draw(this,pnt ,Qt::red,GetMovx(),GetMovy(),GetZoomRate(),GetCanvasWidth(),GetCanvasHeight());
		}
		else{
			if(DrawingMode==_ExpandedPasteZoom01 || DrawingMode==_ExpandedPaste){
				double	X=(ExpandedPasteCurrent.ExpandedPasteFrame[0].X+ExpandedPasteCurrent.ExpandedPasteFrame[1].X)/2;
				double	Y=(ExpandedPasteCurrent.ExpandedPasteFrame[0].Y+ExpandedPasteCurrent.ExpandedPasteFrame[1].Y)/2;
				DrawEZooomArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,X,Y,sita);
			}
			if(DrawingMode==_ExpandedPasteZoom12 || DrawingMode==_ExpandedPaste){
				double	X=(ExpandedPasteCurrent.ExpandedPasteFrame[1].X+ExpandedPasteCurrent.ExpandedPasteFrame[2].X)/2;
				double	Y=(ExpandedPasteCurrent.ExpandedPasteFrame[1].Y+ExpandedPasteCurrent.ExpandedPasteFrame[2].Y)/2;
				DrawEZooomArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,X,Y,sita+M_PI/2.0);
			}
			if(DrawingMode==_ExpandedPasteZoom23 || DrawingMode==_ExpandedPaste){
				double	X=(ExpandedPasteCurrent.ExpandedPasteFrame[2].X+ExpandedPasteCurrent.ExpandedPasteFrame[3].X)/2;
				double	Y=(ExpandedPasteCurrent.ExpandedPasteFrame[2].Y+ExpandedPasteCurrent.ExpandedPasteFrame[3].Y)/2;
				DrawEZooomArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,X,Y,sita+M_PI);
			}
			if(DrawingMode==_ExpandedPasteZoom30 || DrawingMode==_ExpandedPaste){
				double	X=(ExpandedPasteCurrent.ExpandedPasteFrame[3].X+ExpandedPasteCurrent.ExpandedPasteFrame[0].X)/2;
				double	Y=(ExpandedPasteCurrent.ExpandedPasteFrame[3].Y+ExpandedPasteCurrent.ExpandedPasteFrame[0].Y)/2;
				DrawEZooomArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,X,Y,sita+3.0*M_PI/2.0);
			}
			if(DrawingMode==_ExpandedPasteRotate0 || DrawingMode==_ExpandedPaste){
				double	Cx,Cy;
				ExpandedPasteCurrent.GetCenter(Cx,Cy);
				DrawERotateArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,Cx,Cy,ExpandedPasteCurrent.ExpandedPasteFrame[0].X,ExpandedPasteCurrent.ExpandedPasteFrame[0].Y);
			}
			if(DrawingMode==_ExpandedPasteRotate1 || DrawingMode==_ExpandedPaste){
				double	Cx,Cy;
				ExpandedPasteCurrent.GetCenter(Cx,Cy);
				DrawERotateArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,Cx,Cy,ExpandedPasteCurrent.ExpandedPasteFrame[1].X,ExpandedPasteCurrent.ExpandedPasteFrame[1].Y);
			}
			if(DrawingMode==_ExpandedPasteRotate2 || DrawingMode==_ExpandedPaste){
				double	Cx,Cy;
				ExpandedPasteCurrent.GetCenter(Cx,Cy);
				DrawERotateArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,Cx,Cy,ExpandedPasteCurrent.ExpandedPasteFrame[2].X,ExpandedPasteCurrent.ExpandedPasteFrame[2].Y);
			}
			if(DrawingMode==_ExpandedPasteRotate3 || DrawingMode==_ExpandedPaste){
				double	Cx,Cy;
				ExpandedPasteCurrent.GetCenter(Cx,Cy);
				DrawERotateArrow(pnt ,(DrawingMode!=_ExpandedPaste)?true:false,Cx,Cy,ExpandedPasteCurrent.ExpandedPasteFrame[3].X,ExpandedPasteCurrent.ExpandedPasteFrame[3].Y);
			}
		}
	}
}

void	DisplayImage::DrawSaveImageOnPoint(QPainter &pnt ,QImage &PntImage)
{
	if(SaveImageOnPointBtn!=NULL && SaveImageOnPointBtn->isChecked()==true){
		LockPaintMutex();
		QPen	EPen(FrameColor);
		EPen.setWidth(1);
		pnt.setPen(EPen);
		int	XN=SaveImageXCount/2;
		int	YN=SaveImageYCount/2;
		for(int yn=-YN;yn<=YN;yn++){
			for(int xn=-XN;xn<=XN;xn++){
				int	x1=(SaveImageSizeXDot*xn+SaveImageX-SaveImageSizeXDot/2+GetMovx())*GetZoomRate();
				int	y1=(SaveImageSizeYDot*yn+SaveImageY-SaveImageSizeYDot/2+GetMovy())*GetZoomRate();
				int	x2=(SaveImageSizeXDot*xn+SaveImageX+SaveImageSizeXDot/2+GetMovx())*GetZoomRate();
				int	y2=(SaveImageSizeYDot*yn+SaveImageY+SaveImageSizeYDot/2+GetMovy())*GetZoomRate();
				pnt.drawLine(x1,y1,x2,y1);
				pnt.drawLine(x2,y1,x2,y2);
				pnt.drawLine(x2,y2,x1,y2);
				pnt.drawLine(x1,y2,x1,y1);
			}
		}
		UnlockPaintMutex();
	}
}


void	DisplayImage::DrawPaste(QPainter &pnt ,QImage &PntImage)
{
	if(PasteBtn!=NULL && PasteBtn->isChecked()==true && ClippedImageStructure.GetFirst()!=NULL){
		LockPaintMutex();
		QImage	img(MainCanvas->GetCanvasWidth(),MainCanvas->GetCanvasHeight(),QImage::Format_ARGB32);
		//img.fill(0);
		::ClearImage(img, 0);
		for(DisplayImageCopyStructure *v=ClippedImageStructure.GetFirst();v!=NULL;v=v->GetNext()){
			int	LocalPage=GetLayersBase()->GetLocalPageFromGlobal(v->GlobalPage);
			int	dx=(ShowOnePage<0 || GetPageNumb()<=ShowOnePage)?GetLayersBase()->GetPageData(LocalPage)->GetOutlineOffset()->x:0;
			int	dy=(ShowOnePage<0 || GetPageNumb()<=ShowOnePage)?GetLayersBase()->GetPageData(LocalPage)->GetOutlineOffset()->y:0;
			v->Draw(img	,ClippedImageGlobalPosX-ClippedImageGlobalCx+dx
						,ClippedImageGlobalPosY-ClippedImageGlobalCy+dy
					, GetMovx(),GetMovy(),GetZoomRate());
		}
		pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
		pnt.drawImage(0,0,img);
		UnlockPaintMutex();
	}
}

void	DisplayImage::ExpandedPasteData::Draw(DisplayImage *Parent ,QPainter &pnt ,const QColor &_FrameColor 
											,double movx ,double movy ,double ZoomRate
											,int ImageWidth ,int ImageHeight)
{
	QPen	EPen(_FrameColor);
	EPen.setWidth(1);
	pnt.setPen(EPen);
	int	MinX=99999999;
	int	MaxX=-99999999;
	int	MinY=99999999;
	int	MaxY=-99999999;
	//for(ExpandedSelectedItemList *p=SelectedItemLists.GetFirst();p!=NULL;p=p->GetNext()){
	for(int i=0;i<SelectedItemLists.GetCount();i++){
		ExpandedSelectedItemList *p=SelectedItemLists.Get(i);
		if(MinX>p->X1){
			MinX=p->X1;
		}
		if(MinY>p->Y1){
			MinY=p->Y1;
		}
		if(MaxX<p->X2){
			MaxX=p->X2;
		}
		if(MaxY<p->Y2){
			MaxY=p->Y2;
		}
	}

	Parent->DrawInsideExpandedPaste( pnt ,movx,movy,ZoomRate
									,SelectedItemLists,ExpandedItems
									,ImageWidth ,ImageHeight
									,(MinX+MaxX)/2 ,(MinY+MaxY)/2);


	for(ExpandedItemPos *e=ExpandedItems.GetFirst();e!=NULL;e=e->GetNext()){
		pnt.drawLine((e->Pos[0].X+movx)*ZoomRate,(e->Pos[0].Y+movy)*ZoomRate
					,(e->Pos[1].X+movx)*ZoomRate,(e->Pos[1].Y+movy)*ZoomRate);
		pnt.drawLine((e->Pos[1].X+movx)*ZoomRate,(e->Pos[1].Y+movy)*ZoomRate
					,(e->Pos[2].X+movx)*ZoomRate,(e->Pos[2].Y+movy)*ZoomRate);
		pnt.drawLine((e->Pos[2].X+movx)*ZoomRate,(e->Pos[2].Y+movy)*ZoomRate
					,(e->Pos[3].X+movx)*ZoomRate,(e->Pos[3].Y+movy)*ZoomRate);
		pnt.drawLine((e->Pos[3].X+movx)*ZoomRate,(e->Pos[3].Y+movy)*ZoomRate
					,(e->Pos[0].X+movx)*ZoomRate,(e->Pos[0].Y+movy)*ZoomRate);
	}
	/*
		int	cx=(e->Pos[0].X+e->Pos[1].X+e->Pos[2].X+e->Pos[3].X)/4;
		int	cy=(e->Pos[0].Y+e->Pos[1].Y+e->Pos[2].Y+e->Pos[3].Y)/4;

		for(ExpandedSelectedItemList *p=SelectedItemLists.GetFirst();p!=NULL;p=p->GetNext()){
			Parent->DrawInsideExpandedPaste( pnt ,movx,movy,ZoomRate
											,p->X1,p->Y1
											,cx-(MinX+MaxX)/2,cy-(MinY+MaxY)/2
											,p->Page,p->Layer,p->ItemID
											,p->X2-p->X1,p->Y2-p->Y1);
		}
	}
	*/
		
	EPen.setWidth(3);
	pnt.setPen(EPen);
	pnt.drawLine((ExpandedPasteFrame[0].X+movx)*ZoomRate,(ExpandedPasteFrame[0].Y+movy)*ZoomRate
				,(ExpandedPasteFrame[1].X+movx)*ZoomRate,(ExpandedPasteFrame[1].Y+movy)*ZoomRate);
	pnt.drawLine((ExpandedPasteFrame[1].X+movx)*ZoomRate,(ExpandedPasteFrame[1].Y+movy)*ZoomRate
				,(ExpandedPasteFrame[2].X+movx)*ZoomRate,(ExpandedPasteFrame[2].Y+movy)*ZoomRate);
	pnt.drawLine((ExpandedPasteFrame[2].X+movx)*ZoomRate,(ExpandedPasteFrame[2].Y+movy)*ZoomRate
				,(ExpandedPasteFrame[3].X+movx)*ZoomRate,(ExpandedPasteFrame[3].Y+movy)*ZoomRate);
	pnt.drawLine((ExpandedPasteFrame[3].X+movx)*ZoomRate,(ExpandedPasteFrame[3].Y+movy)*ZoomRate
				,(ExpandedPasteFrame[0].X+movx)*ZoomRate,(ExpandedPasteFrame[0].Y+movy)*ZoomRate);
}

void	DisplayImage::DrawEZooomArrow(QPainter &pnt ,bool Selected ,double globalX, double globalY,double sita)
{
	double	coss=cos(-sita);
	double	sins=sin(-sita);
	double	localX=(globalX+GetMovx())*GetZoomRate();
	double	localY=(globalY+GetMovy())*GetZoomRate();

	double	x,y;
	int	MLen=5;
	QPoint	APoint[10];

	x=MLen;
	y=-MLen;
	APoint[0].setX( x*coss+y*sins+localX);
	APoint[0].setY(-x*sins+y*coss+localY);
	x=2*MLen;
	y=-MLen;
	APoint[1].setX( x*coss+y*sins+localX);
	APoint[1].setY(-x*sins+y*coss+localY);
	x=0;
	y=-2*MLen;
	APoint[2].setX( x*coss+y*sins+localX);
	APoint[2].setY(-x*sins+y*coss+localY);
	x=-2*MLen;
	y=-MLen;
	APoint[3].setX( x*coss+y*sins+localX);
	APoint[3].setY(-x*sins+y*coss+localY);
	x=-MLen;
	y=-MLen;
	APoint[4].setX( x*coss+y*sins+localX);
	APoint[4].setY(-x*sins+y*coss+localY);
	x=-MLen;
	y= MLen;
	APoint[5].setX( x*coss+y*sins+localX);
	APoint[5].setY(-x*sins+y*coss+localY);
	x=-2*MLen;
	y= MLen;
	APoint[6].setX( x*coss+y*sins+localX);
	APoint[6].setY(-x*sins+y*coss+localY);
	x=0;
	y= 2*MLen;
	APoint[7].setX( x*coss+y*sins+localX);
	APoint[7].setY(-x*sins+y*coss+localY);
	x=2*MLen;
	y= MLen;
	APoint[8].setX( x*coss+y*sins+localX);
	APoint[8].setY(-x*sins+y*coss+localY);
	x=MLen;
	y=MLen;
	APoint[9].setX( x*coss+y*sins+localX);
	APoint[9].setY(-x*sins+y*coss+localY);

	QPen	EPen(Qt::cyan);
	pnt.setPen(EPen);
	QBrush	EBrush((Selected==true)?Qt::red : Qt::yellow);
	pnt.setBrush(EBrush);
	pnt.drawPolygon (APoint,10);
}
void	DisplayImage::DrawERotateArrow(QPainter &pnt ,bool Selected ,double globalCx,double globalCy ,double globalPx ,double globalPy)
{
	int	MLen=5;
	int	MGLen=MLen/GetZoomRate();

	double	R=hypot(globalPx-globalCx,globalPy-globalCy);
	double	sita=GetSita(globalPx-globalCx,globalPy-globalCy);
	double	Delta=asin((double)MGLen/R);
	QPoint	APoint[30];
	double	dDelta=Delta/5.0;
	int		N=0;
	double	ds,ds2;
	double	x;
	double	y;
	for(int i=0;i<10;i++){
		ds=dDelta*i + sita-Delta;
		x=(R+MGLen)*cos(ds)+globalCx;
		y=(R+MGLen)*sin(ds)+globalCy;
		APoint[N].setX((x+GetMovx())*GetZoomRate());
		APoint[N].setY((y+GetMovy())*GetZoomRate());
		N++;
	}
	ds=sita+Delta;
	x=(R+MGLen)*cos(ds)+globalCx;
	y=(R+MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	x=(R+MGLen+MGLen)*cos(ds)+globalCx;
	y=(R+MGLen+MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	ds2=sita+Delta+Delta;
	x=R*cos(ds2)+globalCx;
	y=R*sin(ds2)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	x=(R-MGLen-MGLen)*cos(ds)+globalCx;
	y=(R-MGLen-MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	for(int i=0;i<10;i++){
		ds=sita+Delta -dDelta*i;
		x=(R-MGLen)*cos(ds)+globalCx;
		y=(R-MGLen)*sin(ds)+globalCy;
		APoint[N].setX((x+GetMovx())*GetZoomRate());
		APoint[N].setY((y+GetMovy())*GetZoomRate());
		N++;
	}
	ds=sita-Delta;
	x=(R-MGLen)*cos(ds)+globalCx;
	y=(R-MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	x=(R-MGLen-MGLen)*cos(ds)+globalCx;
	y=(R-MGLen-MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	ds2=sita-Delta-Delta;
	x=R*cos(ds2)+globalCx;
	y=R*sin(ds2)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	x=(R+MGLen+MGLen)*cos(ds)+globalCx;
	y=(R+MGLen+MGLen)*sin(ds)+globalCy;
	APoint[N].setX((x+GetMovx())*GetZoomRate());
	APoint[N].setY((y+GetMovy())*GetZoomRate());
	N++;

	QPen	EPen(Qt::cyan);
	pnt.setPen(EPen);
	QBrush	EBrush((Selected==true)?Qt::red : Qt::yellow);
	pnt.setBrush(EBrush);
	pnt.drawPolygon (APoint,N);
}

void	DisplayImage::DrawScale(QPainter &pnt)
{
	DrawScale(pnt,GetCanvasWidth(),GetCanvasHeight()
				,GetMovx(),GetMovy(),GetZoomRate());
}
void	DisplayImage::DrawScale(QPainter &pnt
								,int CanvasWidth ,int CanvasHeight
								,int LMovX, int LMovY ,double LZoomRate)
{
	if((__ScalePosition)Option.ModeShowScale==_ScalePositionNoShow){
		return;
	}
	int	XDrawMergin=0;
	int	YDrawMergin=0;
	int	XImageMergin=0;
	int	YImageMergin=0;
	int		x1 ,y1 ,XLen ,YLen;
	GetLayersBase()->GetXY(x1 ,y1 ,XLen ,YLen);

	double	Zx=CanvasWidth	/((double)XLen);
	double	Zy=CanvasHeight	/((double)YLen);
	double	Z=min(Zx,Zy);
	int	GWidth	=XLen*Z;
	int	GHeight	=YLen*Z;
	if(CanvasWidth>GWidth){
		XDrawMergin=(CanvasWidth-GWidth)/2;
		XImageMergin=XDrawMergin/Z;
	}
	else{
		YDrawMergin=(CanvasHeight-GHeight)/2;
		YImageMergin=YDrawMergin/Z;
	}

	double	RealLen=1.0;
	double	ImageLen=GetScaleLen(RealLen)*LZoomRate/GetZoomRate();
	if(RealLen==0.0){
		return;
	}
	bool	Scaled=false;
	for(int i=0;i<8;i++){
		if(ImageLen<30){
			RealLen*=5.0;
			ImageLen=GetScaleLen(RealLen)*LZoomRate/GetZoomRate();
			if(ImageLen<30){
				RealLen*=2.0;
				ImageLen=GetScaleLen(RealLen)*LZoomRate/GetZoomRate();
			}
		}
		else if(ImageLen>=CanvasWidth/2){
			RealLen/=2.0;
			ImageLen=GetScaleLen(RealLen)*LZoomRate/GetZoomRate();
			if(ImageLen>=CanvasWidth/2){
				RealLen/=5.0;
				ImageLen=GetScaleLen(RealLen)*LZoomRate/GetZoomRate();
			}
		}
		else{
			Scaled=true;
			break;
		}
	}
	//int	LeftPos		=(LMovX)*GetZoomRate()+40;
	//int	TopPos		=(LMovY)*GetZoomRate()+40;
	//int	RightPos	=(GetDotPerLine()+LMovX)*GetZoomRate();
	//int	BottomPos	=(GetMaxLines()+LMovY)*GetZoomRate();
	int	LeftPos		=(LMovX+XImageMergin)*LZoomRate+40;
	int	TopPos		=(LMovY+YImageMergin)*LZoomRate+40;
	int	RightPos	=(XLen+LMovX-XImageMergin)*LZoomRate-40;
	int	BottomPos	=(YLen+LMovY-YImageMergin)*LZoomRate-40;

	int	sx=0,sy=0;
	switch((__ScalePosition)Option.ModeShowScale){
	case _ScalePositionNoShow		:
		break;
	case _ScalePositionLeftTop		:
		sx=max(40,LeftPos);
		sy=max(40,TopPos);
		break;
	case _ScalePositionRightTop		:
		sx=min(CanvasWidth,RightPos)-ImageLen-50;
		sy=max(40,TopPos);
		break;
	case _ScalePositionLeftBottom:
		sx=max(40,LeftPos);
		sy=min(CanvasHeight,BottomPos)-60;
		break;
	case _ScalePositionRightBottom:
		sx=min(CanvasWidth,RightPos)-ImageLen-50;
		sy=min(CanvasHeight,BottomPos)-60;
		break;
	}

	QPen	Pen(GetScaleColor());
	Pen.setWidth(3);
	pnt.setPen(Pen);
	pnt.drawLine(sx,sy,sx+ImageLen,sy);
	pnt.drawLine(sx,sy-10,sx,sy+10);
	pnt.drawLine(sx+ImageLen,sy-10,sx+ImageLen,sy+10);

	pnt.setBrush(ScaleColor);

	QString	ScaleMsg;
	int	iPage=GetTargetPage();
	if(iPage>=0){
		XYRegPointContainer	&C=GetLayersBase()->GetPageData(iPage)->GetRegulation();
		if(C.IsEffective()==true){
			ScaleMsg=QString::number(RealLen,'f',C.UnitFigure) + C.GetUnitName();
		}
	}
	if(ScaleMsg.isEmpty()==true){
		ScaleMsg=QString::number(RealLen,'f',2) + GetParamGlobal()->UnitName;
	}
	QFontMetrics	Mtr(pnt.font());
	QRect	R=Mtr.boundingRect(ScaleMsg);
	pnt.drawText(sx+ImageLen/2-R.width()/2,sy+R.height()+8,ScaleMsg);
}