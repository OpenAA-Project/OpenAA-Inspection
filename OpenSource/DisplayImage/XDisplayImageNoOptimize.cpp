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
#include "XAnyData.h"
#include "XFileRegistry.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"

bool DisplayImage::OnIdle(void)
{
	if(ModeToMakeImageInThread==true){
		return OnIdleFunc();
	}
	return true;
}


bool	DisplayImage::OnIdleFunc(void)
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


void	DisplayImage::CanvasSlotOnPaint(QPainter &pnt)
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
	if(ModeToMakeImageInThread==false){
		OnIdleFunc();
	}

	ReEntrant=true;
	CurrentState=GetDrawingState();		//??????Y?I?i????O?a??

	LayerList=CurrentState.LayerList;
	if(FirstDraw==true){
		LockPaintMutex();
		pnt.fillRect(0,0,width(),height(),Qt::black);
		UnlockPaintMutex();
		FirstDraw=false;
	}
	DWORD	t1;

	t1	=::GetComputerMiliSec();
	//pnt.drawPixmap(0,0,PixmapInIdle);
	//if(LBase->GetAnyData()->Remove(/**/"HookOverlap")==false){
	//	t1++;
	//}
	pnt.drawImage(0,0,PainterInIdle);
	//pnt.drawImage(0,0,PainterInIdle,0,0,-1,-1,Qt::AutoColor | Qt::NoFormatConversion);


	//QImage	Img(PainterInIdle);
	//TestImage.append(Img);
	//
	//if(TestImage.count()>3000){
	//	int	N=TestImage.count();
	//	for(int i=0;i<N;i++){
	//		QString	SFileName=QString(/**/"SFile")+QString::number(i)+QString(/**/".png");
	//		TestImage[i].save(SFileName,/**/"PNG");
	//	}
	//}


	WorkingTime	=::GetComputerMiliSec()-t1;

	LastState=CurrentState;				//??????Y?I?i????O?i????A
	ReEntrant=false;
	//DWORD	SpanPaint=t-LastTimeToPaint;
	LastTimeToPaint=t;
}