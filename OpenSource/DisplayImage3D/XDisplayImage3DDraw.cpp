#include "XDisplayImage3D.h"
#include "XDisplayImage3DPacket.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include <QMenu>
#include "XDataInLayer.h"
#include "XGeneralStocker.h"
#include "XCrossObj.h"
#include "XImageStocker.h"
#include "swap.h"

bool DisplayImage3DAlgo::OnIdle(void)
{
	//DWORD	tt,tt1;
	if(GetLayersBase()->GetOnChanging()==false && GetViewing()==true){
		DWORD	DrawnTime	=::GetComputerMiliSec();
		if(DrawnTime-LastDrawnTime>25){
			DWORD	Ct	=::GetComputerMiliSec();
			int	CanvasWidth	=GetCanvasWidth();
			int	CanvasHeight=GetCanvasHeight();

			if(PainterInIdle.width()!=CanvasWidth || PainterInIdle.height()!=CanvasHeight){
				if(IdlePainter!=NULL){
					delete	IdlePainter;
				}
				PainterInIdle=QImage(CanvasWidth,CanvasHeight ,QImage::Format_RGB32);
				IdlePainter=new QPainter(&PainterInIdle);
			}

			if(CheckHidden(this)==false){
				//tt=::GetComputerMiliSec()-Ct;

				DrawInsideFunc(*IdlePainter ,PainterInIdle ,LayerList);
				//tt1=::GetComputerMiliSec()-Ct;
			}
			//PixmapInIdle=QPixmap::fromImage(*PainterInIdle);
			//DWORD	DrawCalcTime=DrawnTime-LastDrawnTime;
			LastDrawnTime=DrawnTime;
		}
		else{
			DrawnTime++;
		}
	}
	return true;
}


void	DisplayImage3DAlgo::CanvasSlotOnPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrant=false;

	LayersBase	*LBase=GetLayersBase();

	if(LBase->GetEventPriority()>1){
		return;
	}
	DWORD	t	=::GetComputerMiliSec();
	if(GetEditMode()==true){
		return;
	}
	if(ReEntrant==true){	//??A?A??h??~
		return;
	}
	if(LBase->IsValidData()==false){
		return;
	}
	if(LBase->GetOnTerminating()==true){	//??I????????
		return;
	}
	if(CheckHidden(this)==true){
		return;
	}
	int	PageCount=LBase->GetPageNumb();
	for(int page=0;page<PageCount;page++){
		int	globalPage=LBase->GetGlobalPageFromLocal(page);
		if(LBase->GetSendingData(globalPage)==true){
			return;
		}
	}

	int	CanvasWidth	=GetCanvasWidth();
	int	CanvasHeight=GetCanvasHeight();

	if(PainterInIdle.width()!=CanvasWidth || PainterInIdle.height()!=CanvasHeight){
		if(IdlePainter!=NULL){
			delete	IdlePainter;
		}
		PainterInIdle=QImage(CanvasWidth,CanvasHeight ,QImage::Format_RGB32);
		IdlePainter=new QPainter(&PainterInIdle);
	}
	DrawInsideFunc(*IdlePainter ,PainterInIdle ,LayerList);



	ReEntrant=true;
	//CurrentState=GetDrawingState();
	//
	//LayerList=CurrentState.LayerList;
	//if(FirstDraw==true){
	//	LockPaintMutex();
	//	pnt.fillRect(0,0,width(),height(),Qt::black);
	//	UnlockPaintMutex();
	//	FirstDraw=false;
	//}
	//DWORD	t1	=::GetComputerMiliSec();

	pnt.drawImage(0,0,PainterInIdle);

	//LastState=CurrentState;		
	ReEntrant=false;

	//LastTimeToPaint=t;
}

//=====================================================================================

void	DisplayImage3DAlgo::DrawInsideFunc(QPainter &pnt ,QImage &PntImage ,IntList &_LayerList)
{
	//DWORD	t	=::GetComputerMiliSec();
	//if(t-LastTimeToDraw<MinInterval)
	//	return;
	if(GetLayersBase()->IsPossibleToUpdateDisplay()==true){
		//MainCanvas->SetFModeRepaintOnMouseMove(FModeRepaintOnMouseMove);

		if(HookedExecutePaintFirst(pnt,PntImage)==true){
			//DWORD	t1=::GetComputerMiliSec()-t;
			if(DrawImage(pnt ,PntImage,_LayerList)==false){
				return;
			}
			else{
				//PntImage.fill(Qt::black);
				::ClearImage(PntImage, 255);
			}

			//emit	SignalDrawFunc(pnt ,PntImage ,_LayerList);

			//DWORD	t2=::GetComputerMiliSec()-t;
			DrawMeasure(pnt ,PntImage);					
			//DWORD	t3=::GetComputerMiliSec()-t;
			DrawExpandedPaste(pnt,PntImage);			
			//DWORD	t4=::GetComputerMiliSec()-t;

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

bool	DisplayImage3DAlgo::DrawImage(QPainter &pnt  ,QImage &PntImage,IntList &LayerList)
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

	for(int page=0;page<LBase->GetPageNumb();page++){
		BmpReceiver[page]->ClearReceivedFlag();
	}
	AlgorithmDrawAttr	*Attr=CreateDrawAttrPointer();
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Attr->Save(&Buff);

	int	N=0;
	for(int page=0;page<LBase->GetPageNumb();page++){
		//??O??????[??o??????y??[??W??O?I?I?i??
		int	globalPage=LBase->GetGlobalPageFromLocal(page);

		DataInPage *P=LBase->GetPageData(page);

		BmpReceiver[N]->SetGlobalPage(globalPage);

		BmpRequester[N]->Data.RedCircleMode	=RedCircleMode;
		BmpRequester[N]->Data.ShowFixedPhase=ShowFixedPhase;
		BmpRequester[N]->Form		=this;
		BmpRequester[N]->AlgoRoot	=AlgoRoot;
		BmpRequester[N]->AlgoName	=AlgoName;
		BmpRequester[N]->InstName	=GetName();
		BmpRequester[N]->DAttrArray	=Buff.buffer();
		N++;
	}
	if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()!=0){
		if(N>1){
			NPListPack<GUICmdPacketDim>	GUICmdDim;
			for(int page=0;page<N;page++){
				int	globalPage=LBase->GetGlobalPageFromLocal(page);
				GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[page],BmpReceiver[page],globalPage,0));
			}
			if(LBase->PacketSender(GUICmdDim,5000)==false){
				return false;
			}
		}
		else if(N>=1){
			int	globalPage=LBase->GetGlobalPageFromLocal(0);
			BmpRequester[0]->Send(globalPage,0,*BmpReceiver[0],5000);
		}
	}
	else{
		for(int page=0;page<N;page++){
			if(BmpReceiver[page]->MakeImage(Attr
										,AlgoRoot,AlgoName
										,MainCanvas->GetCanvas3DInfo()
										,page
										,*LBase
										, RedCircleMode
										, ShowFixedPhase)==false){
				return false;
			}
			BmpReceiver[page]->SetReceived(true);

			//BmpReceiver[page]->NGData->save("TestPNG.png");
		}
	}
	
	delete	Attr;

	if(LBase->GetOnTerminating()==true){
		return false;
	}
	LockPaintMutex();
	QBrush	brush(Qt::black);
	pnt.fillRect (0,0,GetCanvasWidth(),GetCanvasHeight(), brush );
	
	for(int page=LBase->GetPageNumb()-1;page>=0;page--){
		//??`??a????O?I?a??
		int	n=LBase->GetDrawturn(page)->GetPage();
		if(0<=n && n<N){
			if(BmpReceiver[n]->IsReceived()==true && BmpReceiver[n]->IData!=NULL){
				pnt.drawImage(0,0
							 ,*(const QImage *)BmpReceiver[n]->IData);
			}
		}
	}
	//if((DType==DisplayImage::__Target || DType==DisplayImage::__DelayedView)
	//&& ShowNGMarkInTarget==true){
	//	pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
	//	for(int page=LBase->GetPageNumb()-1;page>=0;page--){
	//		//??`??a????O?I?a??
	//		int	n=LBase->GetDrawturn(page)->GetPage();
	//		if(0<=n && n<N){
	//			if(BmpReceiver[n]->IsReceived()==true && BmpReceiver[n]->RetNGData==true && BmpReceiver[n]->NGData!=NULL){
	//				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
	//					&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
	//					//??`????
	//					pnt.drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
	//						 ,*(const QImage *)BmpReceiver[n]->NGData);
	//				}
	//			}
	//		}
	//	}
	//}
	UnlockPaintMutex();

	return true;
}

void	DisplayImage3DAlgo::DrawMeasure(QPainter &pnt ,QImage &PntImage)
{
	int	ShowOnePage=0;
	if(MeasureBtn!=NULL && MeasureBtn->isChecked()==true){
		if(DrawingMode==_MeasureSecond || DrawingMode==_MeasureDone){
			int	LocalX1;
			int	LocalY1;
			int	LocalX2;
			int	LocalY2;
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

			int	StrW=pnt.fontMetrics().width(MeasureStr);
			int	StrH=pnt.fontMetrics().height();
			int rx1=(LocalX1+LocalX2)/2-StrW/2;
			int	ry1=(LocalY1+LocalY2)/2-StrH/2;
			int rx2=(LocalX1+LocalX2)/2+StrW/2;
			int	ry2=(LocalY1+LocalY2)/2+StrH/2;
			int	k;
			for(k=0;k<40;k++){
				if(CheckOverlapRectLine(rx1, ry1+k, rx2, ry2+k ,LocalX1,LocalY1,LocalX2,LocalY2)==false){
					if(IsUnitMode()==true){
						pnt.drawText((LocalX1+LocalX2)/2-StrW/2,(LocalY1+LocalY2)/2+k+StrH/2,TransformPixelToUnitStr(ShowOnePage,L)
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
							pnt.drawText((LocalX1+LocalX2)/2+k-StrW/2,(LocalY1+LocalY2)/2-StrH/2,TransformPixelToUnitStr(ShowOnePage,L)
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


void	DisplayImage3DAlgo::DrawScale(QPainter &pnt)
{
	double	movx ,movy;
	GetMovxy(movx ,movy);
	double	ZoomRateX ,ZoomRateY;
	GetZoomRate(ZoomRateX ,ZoomRateY);
	DrawScale(pnt,GetCanvasWidth(),GetCanvasHeight()
				,movx ,movy,ZoomRateX ,ZoomRateY);
}
void	DisplayImage3DAlgo::DrawScale(QPainter &pnt
								,int CanvasWidth ,int CanvasHeight
								,int LMovX, int LMovY ,double ZoomRateX ,double ZoomRateY)
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
	double	ImageLen=GetScaleLen(RealLen);
	if(RealLen==0.0){
		return;
	}
	bool	Scaled=false;
	for(int i=0;i<8;i++){
		if(ImageLen<30){
			RealLen*=5.0;
			ImageLen=GetScaleLen(RealLen);
			if(ImageLen<30){
				RealLen*=2.0;
				ImageLen=GetScaleLen(RealLen);
			}
		}
		else if(ImageLen>=CanvasWidth/2){
			RealLen/=2.0;
			ImageLen=GetScaleLen(RealLen);
			if(ImageLen>=CanvasWidth/2){
				RealLen/=5.0;
				ImageLen=GetScaleLen(RealLen);
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
	int	LeftPos		=(LMovX+XImageMergin)*ZoomRateX+40;
	int	TopPos		=(LMovY+YImageMergin)*ZoomRateY+40;
	int	RightPos	=(XLen+LMovX-XImageMergin)*ZoomRateX-40;
	int	BottomPos	=(YLen+LMovY-YImageMergin)*ZoomRateY-40;

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
	QString	ScaleMsg=QString::number(RealLen,'f',2) + GetParamGlobal()->UnitName;
	QFontMetrics	Mtr(pnt.font());
	QRect	R=Mtr.boundingRect(ScaleMsg);
	pnt.drawText(sx+ImageLen/2-R.width()/2,sy+R.height()+8,ScaleMsg);
}