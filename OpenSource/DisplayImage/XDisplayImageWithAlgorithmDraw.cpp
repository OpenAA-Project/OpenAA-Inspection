#include "DisplayImageResource.h"
#define	_USE_MATH_DEFINES
#include <QMessageBox>
#include <QMenu>
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XTypeDef.h"
#include "XCrossObj.h"
#include "SelectPasteForm.h"
#include "XGeneralDialog.h"
#include "SelectItemForm.h"
#include "SelectByLibraryDialog.h"
#include "ExpandedPasteForm.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include <omp.h>
#include <math.h>
#include "SelectPages.h"
#include "MoveImageForm.h"
#include "SelectByOrigin.h"
#include "SelectMovePastePage.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "SaveImageOnPointDialog.h"
#include "RegulateBrightnessForm.h"
#include "XGeneralStocker.h"
#include "mtImageToolButtonWithBalloon.h"
#include "mtImageToolButtonColored.h"
#include "swap.h"
#include "InputRotate.h"
#include "InputMirror.h"
#include "SelectOneItemForm.h"
#include "EditItemNameDialog.h"
#include "SetectSearchItemDialog.h"
#include "SelectPageItemDialog.h"



void	DisplayImageWithAlgorithm::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(GetEditMode()==true){
		return;
	}
	if(ReEntrant==true){
		return;
	}
	if(GetLayersBase()->IsValidData()==false){
		return;
	}

	ReEntrant=true;

	if(MainCanvas!=NULL){
		if(ShowOnePage<0){
			DrawItems(this,pnt ,MainCanvas->GetZoomRate(),MainCanvas->GetMovx(),MainCanvas->GetMovy());
		}
		else if(ShowOnePage<GetPageNumb()){
			DrawItemsOnePage(this,pnt ,MainCanvas->GetZoomRate(),MainCanvas->GetMovx(),MainCanvas->GetMovy());
		}
	}
	ReEntrant=false;
}

void	DisplayImageWithAlgorithm::DrawItems(DisplayImage *Target,QPainter &pnt ,double ZoomRate ,int Movx ,int Movy)
{
	static	volatile	bool	ReEntrant=false;

	if(GetEditMode()==true){
		return;
	}
	if(ReEntrant==true){
		return;
	}
	if(GetLayersBase()->IsValidData()==false){
		return;
	}
	if(CheckHidden(this)==true){
		return;
	}

	ReEntrant=true;
	IntList	LayerList;
	GetActiveLayerList(LayerList);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		if(GetLayersBase()->GetSendingData(globalPage)==true){
			ReEntrant=false;
			return;
		}
	}

	AllocInnerBuffWithAlgorithm();
	if(ModeShowOnlyTopTurn==false){
		if(GetLayersBase()->GetParamComm()->Mastered==true){
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,page);
				GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
				if(CmdReqClearTemporaryItems.Send(NULL,page,0)==false){
					SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
				}
			}
		}
		else{
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,page);
				GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
				if(CmdReqClearTemporaryItems.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0)==false){
					SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
				}
			}
		}

		try{
			int	globalX1;
			int	globalY1;
			int	globalX2;
			int	globalY2;
			GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				ItemsBmpReceiver[page]->ClearReceivedFlag();
			}
			int	N=0;
			for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

				GUICmdReqItemsBmp		*ItemReq=ItemsBmpRequester[N];
				GUICmdReqTemporaryItems	*TempReq=CmdReqTemporaryItems[N];

				TempReq->LayerList	=ItemReq->LayerList	=LayerList;
				//if(TempReq->ModePoint!=NULL){
				//	delete	TempReq->ModePoint;
				//}
				//TempReq->ModePoint	=ItemReq->ModePoint	=CreateDrawAttrPointer();

				DataInPage *P=GetLayersBase()->GetPageData(page);
				int	Dx1	=P->GetOutlineOffset()->x;
				int	Dy1	=P->GetOutlineOffset()->y;
				int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
				int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
				int	Gx1,Gy1,Gx2,Gy2;
				Target->ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
				Target->ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);

				TempReq->Data.DType		=ItemReq->Data.DType		=GetDisplayType();
				TempReq->Data.ZoomRate	=ItemReq->Data.ZoomRate		=ZoomRate;
				TempReq->Data.MovX		=ItemReq->Data.MovX			=Movx+P->GetOutlineOffset()->x;
				TempReq->Data.MovY		=ItemReq->Data.MovY			=Movy+P->GetOutlineOffset()->y;
				TempReq->Data.GlobalPage=ItemReq->Data.GlobalPage	=globalPage;
				ItemsBmpReceiver[N]->SetGlobalPage(globalPage);
				if(CheckOverlapRectRectFast(0, 0, Target->GetCanvasWidth(), Target->GetCanvasHeight()
											,Gx1, Gy1, Gx2, Gy2)==true){
					if(Gx1<0){
						Gx1=0;
					}
					if(Gy1<0){
						Gy1=0;
					}
					if(Gx2>Target->GetCanvasWidth()){
						Gx2=Target->GetCanvasWidth();
					}
					if(Gy2>Target->GetCanvasHeight()){
						Gy2=Target->GetCanvasHeight();
					}
					TempReq->Data.Gx1	=ItemReq->Data.Gx1	=Gx1;
					TempReq->Data.Gy1	=ItemReq->Data.Gy1	=Gy1;
					TempReq->Data.Gx2	=ItemReq->Data.Gx2	=Gx2;
					TempReq->Data.Gy2	=ItemReq->Data.Gy2	=Gy2;
					Target->ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
					Target->ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
					TempReq->Data.Dx1	=ItemReq->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
					TempReq->Data.Dy1	=ItemReq->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
					TempReq->Data.Dx2	=ItemReq->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
					TempReq->Data.Dy2	=ItemReq->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
				}
				else{
					TempReq->Data.Gx1	=ItemReq->Data.Gx1	=0;
					TempReq->Data.Gy1	=ItemReq->Data.Gy1	=0;
					TempReq->Data.Gx2	=ItemReq->Data.Gx2	=0;
					TempReq->Data.Gy2	=ItemReq->Data.Gy2	=0;
					TempReq->Data.Dx1	=ItemReq->Data.Dx1	=0;
					TempReq->Data.Dy1	=ItemReq->Data.Dy1	=0;
					TempReq->Data.Dx2	=ItemReq->Data.Dx2	=0;
					TempReq->Data.Dy2	=ItemReq->Data.Dy2	=0;
				}
				TempReq->Data.Mode			=ItemReq->Data.Mode			=DrawingMode;
				TempReq->Data.MoveGlobalDx	=ItemReq->Data.MoveGlobalDx	=MoveCurrentGlobalX - MoveStartGlobalX;
				TempReq->Data.MoveGlobalDy	=ItemReq->Data.MoveGlobalDy	=MoveCurrentGlobalY - MoveStartGlobalY;
				TempReq->InstName			=ItemReq->InstName			=GetName();
				N++;
			}
			AlgorithmDrawAttr	*DAttr=CreateDrawAttrPointer();

			if(GetParamComm()->IsMastered()==true && GetParamComm()->GetConnectedPCNumb()!=0){
				QBuffer	DAttrBuff;
				DAttrBuff.open(QIODevice::ReadWrite);
				DAttr->Save(&DAttrBuff);

				for(int n=0;n<N;n++){
					ItemsBmpRequester[n]->DAttrArray	=DAttrBuff.buffer();
				}
				NPListPack<GUICmdPacketDim>	GUICmdDimTmp;
				NPListPack<GUICmdPacketDim>	GUICmdDim;
				for(int n=0;n<N;n++){
					int	GlobalPage=CmdReqTemporaryItems[n]->Data.GlobalPage;
					DataInPage	*Pg=GetLayersBase()->GetPageData(GetLayersBase()->GetLocalPageFromGlobal(GlobalPage));
					if(Pg->IsWaitingReq==false){
						GUICmdDimTmp.AppendList(new GUICmdPacketDim(CmdReqTemporaryItems[n],CmdAckTemporaryItems[n],GlobalPage,0));
						if(ItemsBmpRequester[n]->Data.Gx1!=ItemsBmpRequester[n]->Data.Gx2
						&& ItemsBmpRequester[n]->Data.Gy1!=ItemsBmpRequester[n]->Data.Gy2){
							GUICmdDim	.AppendList(new GUICmdPacketDim(ItemsBmpRequester[n],ItemsBmpReceiver[n],GlobalPage,0));
						}
					}
				}

				for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
					int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					if(GetLayersBase()->GetSendingData(globalPage)==true){
						ReEntrant=false;
						return;
					}
				}
				if(GetLayersBase()->PacketSender(GUICmdDimTmp,GetParamGlobal()->MaxWaitingCommMilisec)==false){
					IntList	ErrorPages;
					for(GUICmdPacketDim *c=GUICmdDimTmp.GetFirst();c!=NULL;c=c->GetNext()){
						ErrorPages.Add(c->GetPage());
					}
					GetLayersBase()->MessageSocketError(ErrorPages);
					ReEntrant=false;
					return;
				}
				if(GetLayersBase()->PacketSender(GUICmdDim,GetParamGlobal()->MaxWaitingCommMilisec)==false){
					IntList	ErrorPages;
					for(GUICmdPacketDim *c=GUICmdDim.GetFirst();c!=NULL;c=c->GetNext()){
						ErrorPages.Add(c->GetPage());
					}
					GetLayersBase()->MessageSocketError(ErrorPages);
					ReEntrant=false;
					return;
				}
			}
			else{
				for(int n=0;n<N;n++){
					int	GlobalPage=CmdReqTemporaryItems[n]->Data.GlobalPage;
					CmdReqTemporaryItems[n]->Send(GlobalPage,0,*CmdAckTemporaryItems[n]);
				}
				for(int n=0;n<N;n++){
					ItemsBmpReceiver[n]->MakeImage(DAttr
											,LayerList
									 , ItemsBmpRequester[n]->Data.Gx1, ItemsBmpRequester[n]->Data.Gy1 , ItemsBmpRequester[n]->Data.Gx2, ItemsBmpRequester[n]->Data.Gy2
									 , ItemsBmpRequester[n]->Data.Dx1, ItemsBmpRequester[n]->Data.Dy1 , ItemsBmpRequester[n]->Data.Dx2, ItemsBmpRequester[n]->Data.Dy2
									 , ItemsBmpRequester[n]->Data.MovX,ItemsBmpRequester[n]->Data.MovY, ItemsBmpRequester[n]->Data.ZoomRate
									 , GetLayersBase()->GetLocalPageFromGlobal(ItemsBmpRequester[n]->Data.GlobalPage)
									 , ItemsBmpRequester[n]->Data.Mode
									 , ItemsBmpRequester[n]->Data.MoveGlobalDx ,ItemsBmpRequester[n]->Data.MoveGlobalDy
									 , this
									 , ItemsBmpRequester[n]->Data.DType
									 , *GetLayersBase()
									 , EmitterRoot,EmitterName);
					ItemsBmpReceiver[n]->SetReceived(true);
				}
			}
			delete	DAttr;

			pnt.setCompositionMode (QPainter::CompositionMode_SourceOver); 
			//for(int n=0;n<N;n++){
			if(CountOfMaskPaint==0){
				for(int page=GetLayersBase()->GetPageNumb()-1;page>=0;page--){
					int	n=GetLayersBase()->GetDrawturn(page)->GetPage();
					if(ItemsBmpReceiver[n]->IsReceived()==true && ItemsBmpReceiver[n]->IData!=NULL
					&& ItemsBmpRequester[n]->Data.Gx1!=ItemsBmpRequester[n]->Data.Gx2
					&& ItemsBmpRequester[n]->Data.Gy1!=ItemsBmpRequester[n]->Data.Gy2){
						QImage	*img=dynamic_cast<QImage *>(ItemsBmpReceiver[n]->IData);
						if(img!=NULL && img->isNull()==false && pnt.isActive()==true){
							if(GetDisplayType()!=__NoImage){
								::AddAlphaChannel(*img,128);
							}
							int	gw=img->width();
							int	gh=img->height();
							const QImage tImg=*img;
							int	tw=tImg.width();
							int	th=tImg.height();
							if(gw>0 && gh>0 && tw>0 && th>0){
								pnt.drawImage(ItemsBmpRequester[n]->Data.Gx1	//+P->CData.OutlineOffset.x*GetZoomRate()
											 ,ItemsBmpRequester[n]->Data.Gy1	//+P->CData.OutlineOffset.y*GetZoomRate()
											 ,tImg);
							}
						}
						else{
							IntList	ErrorPages;
							ErrorPages.Add(n);
							GetLayersBase()->MessageSocketError(ErrorPages);
						}
					}
				}
			}
			else{
				CountOfMaskPaint--;
			}
		}
		catch(...){}
	}
	else{
		int	page=GetLayersBase()->GetDrawturn(0)->GetPage();
		if(GetLayersBase()->GetParamComm()->Mastered==true){
			GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,page);
			GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
			if(CmdReqClearTemporaryItems.Send(NULL,page,0)==false){
				SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
			}
		}
		else{
			GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,page);
			GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
			if(CmdReqClearTemporaryItems.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0)==false){
				SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
			}
		}

		try{
			int	globalX1;
			int	globalY1;
			int	globalX2;
			int	globalY2;
			GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

			ItemsBmpReceiver[page]->ClearReceivedFlag();

			AlgorithmDrawAttr	*DAttr=CreateDrawAttrPointer();
			QBuffer	DAttrBuff;
			DAttrBuff.open(QIODevice::ReadWrite);
			DAttr->Save(&DAttrBuff);
			delete	DAttr;
			int	N=0;

			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			ItemsBmpRequester[N]->DAttrArray	=DAttrBuff.buffer();
			CmdReqTemporaryItems[N]->LayerList	=ItemsBmpRequester[N]->LayerList	=LayerList;
			//if(CmdReqTemporaryItems[N]->ModePoint!=NULL){
			//	delete	CmdReqTemporaryItems[N]->ModePoint;
			//}
			//CmdReqTemporaryItems[N]->ModePoint	=ItemsBmpRequester[N]->ModePoint	=CreateDrawAttrPointer();

			DataInPage *P=GetLayersBase()->GetPageData(page);
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			Target->ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
			Target->ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);

			CmdReqTemporaryItems[N]->Data.DType		=ItemsBmpRequester[N]->Data.DType		=GetDisplayType();
			CmdReqTemporaryItems[N]->Data.ZoomRate	=ItemsBmpRequester[N]->Data.ZoomRate	=ZoomRate;
			CmdReqTemporaryItems[N]->Data.MovX		=ItemsBmpRequester[N]->Data.MovX		=Movx+P->GetOutlineOffset()->x;
			CmdReqTemporaryItems[N]->Data.MovY		=ItemsBmpRequester[N]->Data.MovY		=Movy+P->GetOutlineOffset()->y;
			CmdReqTemporaryItems[N]->Data.GlobalPage=ItemsBmpRequester[N]->Data.GlobalPage	=globalPage;
			ItemsBmpReceiver[N]->SetGlobalPage(globalPage);
			if(CheckOverlapRectRectFast(0, 0, Target->GetCanvasWidth(), Target->GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==true){
				if(Gx1<0){
					Gx1=0;
				}
				if(Gy1<0){
					Gy1=0;
				}
				if(Gx2>Target->GetCanvasWidth()){
					Gx2=Target->GetCanvasWidth();
				}
				if(Gy2>Target->GetCanvasHeight()){
					Gy2=Target->GetCanvasHeight();
				}
				CmdReqTemporaryItems[N]->Data.Gx1	=ItemsBmpRequester[N]->Data.Gx1		=Gx1;
				CmdReqTemporaryItems[N]->Data.Gy1	=ItemsBmpRequester[N]->Data.Gy1		=Gy1;
				CmdReqTemporaryItems[N]->Data.Gx2	=ItemsBmpRequester[N]->Data.Gx2		=Gx2;
				CmdReqTemporaryItems[N]->Data.Gy2	=ItemsBmpRequester[N]->Data.Gy2		=Gy2;
				Target->ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
				Target->ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
				CmdReqTemporaryItems[N]->Data.Dx1	=ItemsBmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
				CmdReqTemporaryItems[N]->Data.Dy1	=ItemsBmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
				CmdReqTemporaryItems[N]->Data.Dx2	=ItemsBmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
				CmdReqTemporaryItems[N]->Data.Dy2	=ItemsBmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			}
			else{
				CmdReqTemporaryItems[N]->Data.Gx1	=ItemsBmpRequester[N]->Data.Gx1	=0;
				CmdReqTemporaryItems[N]->Data.Gy1	=ItemsBmpRequester[N]->Data.Gy1	=0;
				CmdReqTemporaryItems[N]->Data.Gx2	=ItemsBmpRequester[N]->Data.Gx2	=0;
				CmdReqTemporaryItems[N]->Data.Gy2	=ItemsBmpRequester[N]->Data.Gy2	=0;
				CmdReqTemporaryItems[N]->Data.Dx1	=ItemsBmpRequester[N]->Data.Dx1	=0;
				CmdReqTemporaryItems[N]->Data.Dy1	=ItemsBmpRequester[N]->Data.Dy1	=0;
				CmdReqTemporaryItems[N]->Data.Dx2	=ItemsBmpRequester[N]->Data.Dx2	=0;
				CmdReqTemporaryItems[N]->Data.Dy2	=ItemsBmpRequester[N]->Data.Dy2	=0;
			}
			CmdReqTemporaryItems[N]->Data.Mode			=ItemsBmpRequester[N]->Data.Mode		=DrawingMode;
			CmdReqTemporaryItems[N]->Data.MoveGlobalDx	=ItemsBmpRequester[N]->Data.MoveGlobalDx=MoveCurrentGlobalX - MoveStartGlobalX;
			CmdReqTemporaryItems[N]->Data.MoveGlobalDy	=ItemsBmpRequester[N]->Data.MoveGlobalDy=MoveCurrentGlobalY - MoveStartGlobalY;
			CmdReqTemporaryItems[N]->InstName			=ItemsBmpRequester[N]->InstName			=GetName();


			NPListPack<GUICmdPacketDim>	GUICmdDimTmp;
			NPListPack<GUICmdPacketDim>	GUICmdDim;

			int	GlobalPage=CmdReqTemporaryItems[N]->Data.GlobalPage;
			DataInPage	*Pg=GetLayersBase()->GetPageData(GetLayersBase()->GetLocalPageFromGlobal(GlobalPage));
			if(Pg->IsWaitingReq==false){
				GUICmdDimTmp.AppendList(new GUICmdPacketDim(CmdReqTemporaryItems[N],CmdAckTemporaryItems[N],GlobalPage,0));
				if(ItemsBmpRequester[N]->Data.Gx1!=ItemsBmpRequester[N]->Data.Gx2
				&& ItemsBmpRequester[N]->Data.Gy1!=ItemsBmpRequester[N]->Data.Gy2){
					GUICmdDim	.AppendList(new GUICmdPacketDim(ItemsBmpRequester[N],ItemsBmpReceiver[N],GlobalPage,0));
				}
			}
			
			if(GetLayersBase()->GetSendingData(globalPage)==true){
				ReEntrant=false;
				return;
			}
			if(GetLayersBase()->PacketSender(GUICmdDimTmp,GetParamGlobal()->MaxWaitingCommMilisec)==false){
				IntList	ErrorPages;
				for(GUICmdPacketDim *c=GUICmdDimTmp.GetFirst();c!=NULL;c=c->GetNext()){
					ErrorPages.Add(c->GetPage());
				}
				GetLayersBase()->MessageSocketError(ErrorPages);
				ReEntrant=false;
				return;
			}
			if(GetLayersBase()->PacketSender(GUICmdDim,GetParamGlobal()->MaxWaitingCommMilisec)==false){
				IntList	ErrorPages;
				for(GUICmdPacketDim *c=GUICmdDim.GetFirst();c!=NULL;c=c->GetNext()){
					ErrorPages.Add(c->GetPage());
				}
				GetLayersBase()->MessageSocketError(ErrorPages);
				ReEntrant=false;
				return;
			}

			pnt.setCompositionMode (QPainter::CompositionMode_SourceOver); 
			if(CountOfMaskPaint==0){
				if(ItemsBmpReceiver[N]->IsReceived()==true && ItemsBmpReceiver[N]->IData!=NULL
				&& ItemsBmpRequester[N]->Data.Gx1!=ItemsBmpRequester[N]->Data.Gx2
				&& ItemsBmpRequester[N]->Data.Gy1!=ItemsBmpRequester[N]->Data.Gy2){
					QImage	*img=dynamic_cast<QImage *>(ItemsBmpReceiver[N]->IData);
					if(img!=NULL && img->isNull()==false && pnt.isActive()==true){
						int	gw=img->width();
						int	gh=img->height();
						const QImage tImg=*img;
						int	tw=tImg.width();
						int	th=tImg.height();
						if(gw>0 && gh>0 && tw>0 && th>0){
							pnt.drawImage(ItemsBmpRequester[N]->Data.Gx1	//+P->CData.OutlineOffset.x*GetZoomRate()
										 ,ItemsBmpRequester[N]->Data.Gy1	//+P->CData.OutlineOffset.y*GetZoomRate()
										 ,tImg);
						}
					}
					else{
						IntList	ErrorPages;
						ErrorPages.Add(N);
						GetLayersBase()->MessageSocketError(ErrorPages);
					}
				}
				
			}
		}
		catch(...){}
	}
	
	ReEntrant=false;
}

void	DisplayImageWithAlgorithm::DrawItemsOnePage(DisplayImage *Target,QPainter &pnt ,double ZoomRate ,int Movx ,int Movy)
{
	static	volatile	bool	ReEntrant=false;

	if(GetEditMode()==true){
		return;
	}
	if(ReEntrant==true){
		return;
	}
	if(GetLayersBase()->IsValidData()==false){
		return;
	}
	if(CheckHidden(this)==true){
		return;
	}

	ReEntrant=true;
	IntList	LayerList;
	GetActiveLayerList(LayerList);

	int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(ShowOnePage);
	if(GetLayersBase()->GetSendingData(globalPage)==true){
		ReEntrant=false;
		return;
	}
	if(globalPage>=GetLayersBase()->GetGlobalPageNumb()){
		return;
	}

	AllocInnerBuffWithAlgorithm();
	if(GetLayersBase()->GetParamComm()->Mastered==true){
		GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,globalPage);
		GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
		if(CmdReqClearTemporaryItems.Send(NULL,globalPage,0)==false){
			SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
		}
	}
	else{
		GUICmdReqClearTemporaryItems	CmdReqClearTemporaryItems(GetAlgorithmBase(),EmitterRoot,EmitterName,globalPage);
		GetAlgorithm(CmdReqClearTemporaryItems.AlgoRoot,CmdReqClearTemporaryItems.AlgoName);
		if(CmdReqClearTemporaryItems.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(globalPage),0)==false){
			SetError(Error_Comm , /**/"Send error :DrawAfterImage-GUICmdReqClearTemporaryItems",ErrorCodeList::_Alart);
		}
	}

	try{
		DataInPage *P=GetLayersBase()->GetPageData(ShowOnePage);
		ItemsBmpReceiver[ShowOnePage]->ClearReceivedFlag();

		AlgorithmDrawAttr	*DAttr=CreateDrawAttrPointer();
		QBuffer	DAttrBuff;
		DAttrBuff.open(QIODevice::ReadWrite);
		DAttr->Save(&DAttrBuff);
		delete	DAttr;

		ItemsBmpRequester[ShowOnePage]->DAttrArray	=DAttrBuff.buffer();
		CmdReqTemporaryItems[ShowOnePage]->LayerList	=ItemsBmpRequester[ShowOnePage]->LayerList	=LayerList;

		int	Dx1	=P->GetOutlineOffset()->x;
		int	Dy1	=P->GetOutlineOffset()->y;
		int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
		int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
		int	Gx1,Gy1,Gx2,Gy2;
		Target->ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
		Target->ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);

		CmdReqTemporaryItems[ShowOnePage]->Data.DType		=ItemsBmpRequester[ShowOnePage]->Data.DType		=GetDisplayType();
		CmdReqTemporaryItems[ShowOnePage]->Data.ZoomRate	=ItemsBmpRequester[ShowOnePage]->Data.ZoomRate	=ZoomRate;
		CmdReqTemporaryItems[ShowOnePage]->Data.MovX		=ItemsBmpRequester[ShowOnePage]->Data.MovX		=Movx;
		CmdReqTemporaryItems[ShowOnePage]->Data.MovY		=ItemsBmpRequester[ShowOnePage]->Data.MovY		=Movy;
		CmdReqTemporaryItems[ShowOnePage]->Data.GlobalPage=ItemsBmpRequester[ShowOnePage]->Data.GlobalPage	=globalPage;
		ItemsBmpReceiver[ShowOnePage]->SetGlobalPage(globalPage);
		if(CheckOverlapRectRectFast(0, 0, Target->GetCanvasWidth(), Target->GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==true){
			if(Gx1<0){
				Gx1=0;
			}
			if(Gy1<0){
				Gy1=0;
			}
			if(Gx2>Target->GetCanvasWidth()){
				Gx2=Target->GetCanvasWidth();
			}
			if(Gy2>Target->GetCanvasHeight()){
				Gy2=Target->GetCanvasHeight();
			}
			CmdReqTemporaryItems[ShowOnePage]->Data.Gx1	=ItemsBmpRequester[ShowOnePage]->Data.Gx1		=Gx1;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gy1	=ItemsBmpRequester[ShowOnePage]->Data.Gy1		=Gy1;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gx2	=ItemsBmpRequester[ShowOnePage]->Data.Gx2		=Gx2;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gy2	=ItemsBmpRequester[ShowOnePage]->Data.Gy2		=Gy2;
			Target->ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
			Target->ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
			CmdReqTemporaryItems[ShowOnePage]->Data.Dx1	=ItemsBmpRequester[ShowOnePage]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dy1	=ItemsBmpRequester[ShowOnePage]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dx2	=ItemsBmpRequester[ShowOnePage]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dy2	=ItemsBmpRequester[ShowOnePage]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
		}
		else{
			CmdReqTemporaryItems[ShowOnePage]->Data.Gx1	=ItemsBmpRequester[ShowOnePage]->Data.Gx1	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gy1	=ItemsBmpRequester[ShowOnePage]->Data.Gy1	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gx2	=ItemsBmpRequester[ShowOnePage]->Data.Gx2	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Gy2	=ItemsBmpRequester[ShowOnePage]->Data.Gy2	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dx1	=ItemsBmpRequester[ShowOnePage]->Data.Dx1	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dy1	=ItemsBmpRequester[ShowOnePage]->Data.Dy1	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dx2	=ItemsBmpRequester[ShowOnePage]->Data.Dx2	=0;
			CmdReqTemporaryItems[ShowOnePage]->Data.Dy2	=ItemsBmpRequester[ShowOnePage]->Data.Dy2	=0;
		}
		CmdReqTemporaryItems[ShowOnePage]->Data.Mode			=ItemsBmpRequester[ShowOnePage]->Data.Mode		=DrawingMode;
		CmdReqTemporaryItems[ShowOnePage]->Data.MoveGlobalDx	=ItemsBmpRequester[ShowOnePage]->Data.MoveGlobalDx=MoveCurrentGlobalX - MoveStartGlobalX;
		CmdReqTemporaryItems[ShowOnePage]->Data.MoveGlobalDy	=ItemsBmpRequester[ShowOnePage]->Data.MoveGlobalDy=MoveCurrentGlobalY - MoveStartGlobalY;
		CmdReqTemporaryItems[ShowOnePage]->InstName			=ItemsBmpRequester[ShowOnePage]->InstName			=GetName();

		if(P->IsWaitingReq==false){
			if(CmdReqTemporaryItems[ShowOnePage]->Send(globalPage,0,*CmdAckTemporaryItems[ShowOnePage])==false){
				IntList	ErrorPages;
				ErrorPages.Add(ShowOnePage);
				GetLayersBase()->MessageSocketError(ErrorPages);
				ReEntrant=false;
				return;
			}

			if(ItemsBmpRequester[ShowOnePage]->Send(globalPage,0,*ItemsBmpReceiver[ShowOnePage])==false){
				IntList	ErrorPages;
				ErrorPages.Add(ShowOnePage);
				GetLayersBase()->MessageSocketError(ErrorPages);
				ReEntrant=false;
				return;
			}
		}

		pnt.setCompositionMode (QPainter::CompositionMode_SourceOver); 
		//for(int n=0;n<N;n++){
		if(CountOfMaskPaint==0){
			if(ItemsBmpReceiver[ShowOnePage]->IsReceived()==true && ItemsBmpReceiver[ShowOnePage]->IData!=NULL
			&& ItemsBmpRequester[ShowOnePage]->Data.Gx1!=ItemsBmpRequester[ShowOnePage]->Data.Gx2
			&& ItemsBmpRequester[ShowOnePage]->Data.Gy1!=ItemsBmpRequester[ShowOnePage]->Data.Gy2){
				QImage	*img=dynamic_cast<QImage *>(ItemsBmpReceiver[ShowOnePage]->IData);
				if(img!=NULL && img->isNull()==false && pnt.isActive()==true){
					int	gw=img->width();
					int	gh=img->height();
					const QImage tImg=*img;
					int	tw=tImg.width();
					int	th=tImg.height();
					if(gw>0 && gh>0 && tw>0 && th>0){
						pnt.drawImage(ItemsBmpRequester[ShowOnePage]->Data.Gx1	//+P->CData.OutlineOffset.x*GetZoomRate()
									 ,ItemsBmpRequester[ShowOnePage]->Data.Gy1	//+P->CData.OutlineOffset.y*GetZoomRate()
									 ,tImg);
					}
				}
				else{
					IntList	ErrorPages;
					ErrorPages.Add(ShowOnePage);
					GetLayersBase()->MessageSocketError(ErrorPages);
				}
			}
		}
		else{
			CountOfMaskPaint--;
		}
	}
	catch(...){}
	
	ReEntrant=false;
}
