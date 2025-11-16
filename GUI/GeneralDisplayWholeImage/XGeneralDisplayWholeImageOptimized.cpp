#include "GeneralDisplayWholeImage.h"
#include "XGUIFormBase.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"


void	GeneralDisplayWholeImage::SlotOnPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	if(GetLayersBase()->IsValidData()==false){
		return;
	}

	if(IsShown()==true){

		//DWORD	t=::GetComputerMiliSec();
		//if(t-LastPaintTime>=25){

		//HookedExecutePaintFirst(pnt);

		//QMessageBox::warning(NULL,/**/"Confirm"	,/**/"GeneralDisplayWholeImage::SlotOnPaint .0");
		ReEntrant=true;
		DisplayImage	*m=NULL;
		if(FollowImagePanel==true){
			m=GetCurrentImagePanel();
		}
		double	ZoomRate=GetZoomRate();

		if((m!=NULL && m->GetDisplayType()==DisplayImage::__Master) || (m==NULL && Mastered==true)){
			QPixmap	TmpMap(MainCanvas.width(),MainCanvas.height());
			QPainter	TmpPnt(&TmpMap);

			if(0.00001<=ZoomRate && ZoomRate<10000){
				if(m==NULL || (m!=NULL && m->ShowOnePage<0)){
					if(ShowOnePage<0){
						bool	ShouldRebuidPixmap=false;
						int	Phase=0;
						if(MasterPixMap!=NULL){
							for(int page=0;page<GetPageNumb() && page<AllocatedPageNumb;page++){
								BmpRequester[page]->ZoomRate=ZoomRate;
								if(m==NULL || m->ShowFixedPhase<0){
									Phase=ShowFixedPhase;
									if(Phase<0)
										Phase=GetLayersBase()->GetCurrentPhase();
									if(MasterPixMap[Phase]==NULL || MasterPixMap[Phase][page]==NULL){
										ShouldRebuidPixmap=true;
									}
								}
								else{
									Phase=m->ShowFixedPhase;
									if(Phase<0)
										Phase=GetLayersBase()->GetCurrentPhase();
									if(MasterPixMap[Phase]==NULL || MasterPixMap[Phase][page]==NULL){
										ShouldRebuidPixmap=true;
									}
								}
							}
						}
						else{
							ShouldRebuidPixmap=true;
						}
						if(Phase<0)
							Phase=0;
						
						if(ShouldRebuidPixmap==true){
							AllocatePixmap();						
							for(int page=0;page<GetPageNumb() && page<AllocatedPageNumb;page++){
								bool	CommOK=true;
								BmpRequester[page]->ZoomRate=ZoomRate;
								if(m==NULL){
									BmpRequester[page]->Mastered=Mastered;
									BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
								}
								else{
									if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
										BmpRequester[page]->Mastered=true;
									else
										BmpRequester[page]->Mastered=false;
									BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
								}
								if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
									BmpRequester[page]->ShowNG	=true;
								else
									BmpRequester[page]->ShowNG	=false;

								if(GetParamComm()->GetConnectedPCNumb()!=0){
									if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==false)
										CommOK=false;
								}
								else{
									if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
																,ZoomRate
																,page
																,*GetLayersBase()
																,BmpRequester[page]->ShowNG
																,BmpRequester[page]->ShowFixedPhase)==false){
										//ReEntrant=false;
										//return;
										goto	JmpDrawRect;
									}
								}

								if(CommOK==true && BmpReceiver[page]->IData!=NULL){
									MasterPixMap[Phase][page]=new QPixmap(QPixmap::fromImage (*(const QImage *)BmpReceiver[page]->IData));
								}
							}
						}
						QBrush	brush(Qt::black);
						TmpPnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
						for(int page=0;page<GetPageNumb() && page<AllocatedPageNumb;page++){
							DataInPage *p=GetLayersBase()->GetPageData(page);
							if(MasterPixMap[Phase][page]!=NULL){
								TmpPnt.drawPixmap(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											 ,*MasterPixMap[Phase][page]);
							}
						}
					}
					else{
						int page=ShowOnePage;
						if(page>=GetPageNumb())
							page=GetPageNumb()-1;
						if(page>=AllocatedPageNumb)
							page=AllocatedPageNumb-1;
						BmpRequester[page]->ZoomRate=ZoomRate;
						int	Phase=0;
						if(m==NULL){
							BmpRequester[page]->Mastered=Mastered;
							BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
							Phase=ShowFixedPhase;
						}
						else{
							if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
								BmpRequester[page]->Mastered=true;
							else
								BmpRequester[page]->Mastered=false;
							BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
							Phase=m->ShowFixedPhase;
						}
						if(Phase<0)
							Phase=GetLayersBase()->GetCurrentPhase();

						if(MasterPixMap==NULL || MasterPixMap[Phase]==NULL || MasterPixMap[Phase][page]==NULL){
							AllocatePixmap();
							if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
								BmpRequester[page]->ShowNG	=true;
							else
								BmpRequester[page]->ShowNG	=false;

							if(GetParamComm()->GetConnectedPCNumb()!=0){
								if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==true){
									if(BmpReceiver[page]->IData!=NULL){
										MasterPixMap[Phase][page]=new QPixmap(QPixmap::fromImage (*(const QImage *)BmpReceiver[page]->IData));
									}
								}
							}
							else{
								if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
															,ZoomRate
															,page
															,*GetLayersBase()
															,BmpRequester[page]->ShowNG
															,BmpRequester[page]->ShowFixedPhase)==false){
									//ReEntrant=false;
									//return;
									goto	JmpDrawRect;
								}
								if(BmpReceiver[page]->IData!=NULL){
									MasterPixMap[Phase][page]=new QPixmap(QPixmap::fromImage (*(const QImage *)BmpReceiver[page]->IData));
								}
							}
							QBrush	brush(Qt::black);
							TmpPnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
							DataInPage *p=GetLayersBase()->GetPageData(page);
							if(MasterPixMap[Phase][page]!=NULL){
								TmpPnt.drawPixmap(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											,*MasterPixMap[Phase][page]);
							}
						}
					}
				}
				else{
					if(LastFocusPanel!=m){
						SlotDraw(m);
					}
					LastFocusPanel=m;

					int page=m->ShowOnePage;
					if(page>=GetPageNumb())
						page=GetPageNumb()-1;
					if(page>=AllocatedPageNumb)
						page=AllocatedPageNumb-1;
					int	Phase=0;
					BmpRequester[page]->ZoomRate=ZoomRate;
					if(m==NULL){
						BmpRequester[page]->Mastered=Mastered;
						BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
						Phase=ShowFixedPhase;
					}
					else{
						if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
							BmpRequester[page]->Mastered=true;
						else
							BmpRequester[page]->Mastered=false;
						BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
						Phase=m->ShowFixedPhase;
					}
					if(Phase<0)
						Phase=GetLayersBase()->GetCurrentPhase();
					if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
						BmpRequester[page]->ShowNG	=true;
					else
						BmpRequester[page]->ShowNG	=false;

					if(MasterPixMap==NULL || MasterPixMap[Phase]==NULL || MasterPixMap[Phase][page]==NULL){
						AllocatePixmap();
						if(GetParamComm()->GetConnectedPCNumb()!=0){
							if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==true){
								if(BmpReceiver[page]->IData!=NULL){
									MasterPixMap[Phase][page]=new QPixmap(QPixmap::fromImage (*(const QImage *)BmpReceiver[page]->IData));
								}
							}
						}
						else{
							if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
														,ZoomRate
														,page
														,*GetLayersBase()
														,BmpRequester[page]->ShowNG
														,BmpRequester[page]->ShowFixedPhase)==false){
								//ReEntrant=false;
								//return;
								goto	JmpDrawRect;
							}
							if(BmpReceiver[page]->IData!=NULL){
								MasterPixMap[Phase][page]=new QPixmap(QPixmap::fromImage (*(const QImage *)BmpReceiver[page]->IData));
							}
						}
						QBrush	brush(Qt::black);
						TmpPnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
						DataInPage *p=GetLayersBase()->GetPageData(page);
						if(MasterPixMap[Phase][page]!=NULL){
							TmpPnt.drawPixmap(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
										 ,*MasterPixMap[Phase][page]);
						}
					}
				}
			}
			pnt.drawPixmap(0,0,TmpMap);
		}
		else{
			if(RelatedPanelPointer!=NULL){
				RelatedPanelPointer->SetZoomRate(ZoomRate);
				RelatedPanelPointer->SetMovXY(0,0);
				if(PntImage.width()!=width() || PntImage.height()!=height()){
					if(RPnt!=NULL){
						delete	RPnt;
						RPnt=NULL;
					}
					PntImage=QImage(width(),height(),QImage::Format_ARGB32);
				}
				
				RelatedPanelPointer->HookedExecutePaintFirst	(pnt ,PntImage);
			}
			if(RPnt==NULL){
				RPnt=new QPainter(&PntImage);
			}
			RPnt->setBrush(Qt::black);
			RPnt->drawRect(0,0,width(),height());

			if(0.00001<=ZoomRate && ZoomRate<10000){
				bool	CommOK=true;
				if(m==NULL || (m!=NULL && m->ShowOnePage<0)){
					if(ShowOnePage<0){
						for(int page=0;page<GetPageNumb() && page<AllocatedPageNumb;page++){
							BmpRequester[page]->ZoomRate=ZoomRate;
							if(m==NULL){
								BmpRequester[page]->Mastered=Mastered;
								BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
							}
							else{
								if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
									BmpRequester[page]->Mastered=true;
								else
									BmpRequester[page]->Mastered=false;
								BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
							}
							if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
								BmpRequester[page]->ShowNG	=true;
							else
								BmpRequester[page]->ShowNG	=false;

							if(GetParamComm()->GetConnectedPCNumb()!=0){
								if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==false)
									CommOK=false;
							}
							else{
								if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
															,ZoomRate
															,page
															,*GetLayersBase()
															,BmpRequester[page]->ShowNG
															,BmpRequester[page]->ShowFixedPhase)==false){
									if(RPnt!=NULL){
										pnt.drawPixmap(0,0,DrawMap);
										//ReEntrant=false;
										//return;
									}
								}
							}
						}
						if(CommOK==true){
							if(RPnt==NULL){
								QBrush	brush(Qt::black);
								pnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
							}
							for(int page=0;page<GetPageNumb() && page<AllocatedPageNumb;page++){
								DataInPage *p=GetLayersBase()->GetPageData(page);
								if(BmpReceiver[page]->IData!=NULL){
									if(RPnt!=NULL){
										RPnt->drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
													 ,*(const QImage *)BmpReceiver[page]->IData);
									}
									else{
										pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
													 ,*(const QImage *)BmpReceiver[page]->IData);
									}
								}
							}
						}
					}
					else{
						int page=ShowOnePage;
						if(page>=GetPageNumb())
							page=GetPageNumb()-1;
						BmpRequester[page]->ZoomRate=ZoomRate;
						if(m==NULL){
							BmpRequester[page]->Mastered=Mastered;
							BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
						}
						else{
							if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
								BmpRequester[page]->Mastered=true;
							else
								BmpRequester[page]->Mastered=false;
							BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
						}
						if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
							BmpRequester[page]->ShowNG	=true;
						else
							BmpRequester[page]->ShowNG	=false;

						if(GetParamComm()->GetConnectedPCNumb()!=0){
							if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==true){
								if(RPnt==NULL){
									QBrush	brush(Qt::black);
									pnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
								}
								DataInPage *p=GetLayersBase()->GetPageData(page);
								if(BmpReceiver[page]->IData!=NULL){
									if(RPnt!=NULL){
										RPnt->drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
												 ,*(const QImage *)BmpReceiver[page]->IData);
									}
									else{
										pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
												 ,*(const QImage *)BmpReceiver[page]->IData);
									}
								}
							}
						}
						else{
							if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
														,ZoomRate
														,page
														,*GetLayersBase()
														,BmpRequester[page]->ShowNG
														,BmpRequester[page]->ShowFixedPhase)==false){
								if(RPnt!=NULL){
									pnt.drawPixmap(0,0,DrawMap);
									//ReEntrant=false;
									//return;
								}
								goto	JmpDrawRect;
							}
							DataInPage *p=GetLayersBase()->GetPageData(page);
							if(BmpReceiver[page]->IData!=NULL){
								if(RPnt!=NULL){
									RPnt->drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											 ,*(const QImage *)BmpReceiver[page]->IData);
								}
								else{
									QBrush	brush(Qt::black);
									pnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
									pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											 ,*(const QImage *)BmpReceiver[page]->IData);
								}
							}
						}
					}
				}
				else{
					if(LastFocusPanel!=m){
						SlotDraw(m);
					}
					LastFocusPanel=m;

					int page=m->ShowOnePage;
					if(page>=GetPageNumb())
						page=GetPageNumb()-1;
					if(page>=AllocatedPageNumb)
						page=AllocatedPageNumb-1;
					BmpRequester[page]->ZoomRate=ZoomRate;
					if(m==NULL){
						BmpRequester[page]->Mastered=Mastered;
						BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
					}
					else{
						if(BmpRequester[page]->Mastered==m->GetDisplayType()==DisplayImage::__Master)
							BmpRequester[page]->Mastered=true;
						else
							BmpRequester[page]->Mastered=false;
						BmpRequester[page]->ShowFixedPhase=m->ShowFixedPhase;
					}
					if(ShowNG==true && (BlinkNG==false || BlinkOn==true))
						BmpRequester[page]->ShowNG	=true;
					else
						BmpRequester[page]->ShowNG	=false;

					if(GetParamComm()->GetConnectedPCNumb()!=0){
						if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==true){
							DataInPage *p=GetLayersBase()->GetPageData(page);
							if(BmpReceiver[page]->IData!=NULL){
								if(RPnt!=NULL){
									RPnt->drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											 ,*(const QImage *)BmpReceiver[page]->IData);
								}
								else{
									QBrush	brush(Qt::black);
									pnt.fillRect (0,0,MainCanvas.width(),MainCanvas.height(), brush );
									pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
											 ,*(const QImage *)BmpReceiver[page]->IData);
								}
							}
						}
					}
					else{
						if(BmpReceiver[page]->MakeImage(BmpRequester[page]->Mastered
													,ZoomRate
													,page
													,*GetLayersBase()
													,BmpRequester[page]->ShowNG
													,BmpRequester[page]->ShowFixedPhase)==false){
							pnt.drawPixmap(0,0,DrawMap);
							//ReEntrant=false;
							//return;
							goto	JmpDrawRect;
						}

						DataInPage *p=GetLayersBase()->GetPageData(page);
						QBrush	brush(Qt::black);
						int	x1=p->GetOutlineOffset()->x*ZoomRate;
						int	y1=p->GetOutlineOffset()->y*ZoomRate;
						int	w=BmpReceiver[page]->IData->width();
						int	h=BmpReceiver[page]->IData->height();
						
						if(BmpReceiver[page]->IData!=NULL){
							if(RPnt!=NULL){
								if(y1>0){
									RPnt->fillRect (0,0,MainCanvas.width(),y1, brush );
								}
								if(y1+h<MainCanvas.height()){
									RPnt->fillRect (0,y1+h,MainCanvas.width(),MainCanvas.height()-(y1+h), brush );
								}
								if(x1>0){
									RPnt->fillRect (0,y1,x1, MainCanvas.height()-(y1+h),brush );
								}
								if(x1+w<MainCanvas.width()){
									RPnt->fillRect (x1+w,y1,MainCanvas.width()-(x1+w),MainCanvas.height()-(y1+h), brush );
								}
								RPnt->drawImage(x1,y1
										 ,*(const QImage *)BmpReceiver[page]->IData);
							}
							else{
								if(y1>0){
									pnt.fillRect (0,0,MainCanvas.width(),y1, brush );
								}
								if(y1+h<MainCanvas.height()){
									pnt.fillRect (0,y1+h,MainCanvas.width(),MainCanvas.height()-(y1+h), brush );
								}
								if(x1>0){
									pnt.fillRect (0,y1,x1, MainCanvas.height()-(y1+h),brush );
								}
								if(x1+w<MainCanvas.width()){
									pnt.fillRect (x1+w,y1,MainCanvas.width()-(x1+w),MainCanvas.height()-(y1+h), brush );
								}
								pnt.drawImage(x1,y1
										 ,*(const QImage *)BmpReceiver[page]->IData);
							}
						}
					}
				}
			}
			if(RPnt!=NULL){
				//setUpdatesEnabled(false);
				RelatedPanelPointer->HookedExecutePaintLast	(pnt ,PntImage);
				//pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
						static	bool	PDbg=false;
						static	int		PDbgCount=0;
						if(PDbg==true){
							QString		PntFileName=QString("TestPPP")+QString::number(PDbgCount)+QString(".png");
							PntImage.save(PntFileName,"PNG");
						}
						PDbgCount++;
				DrawMap=QPixmap::fromImage(PntImage);
				pnt.drawPixmap(0,0,DrawMap);
				// 
				//pnt.drawImage(0,0,PntImage);
				//setUpdatesEnabled(true);
			}
		}
		//QMessageBox::warning(NULL,/**/"Confirm"	,/**/"GeneralDisplayWholeImage::SlotOnPaint .1");

JmpDrawRect:;
		int	x1=RealPos.left	()*ZoomRate;
		int	y1=RealPos.top	()*ZoomRate;
		int	x2=RealPos.right()*ZoomRate;
		int	y2=RealPos.bottom()*ZoomRate;
		
		pnt.setPen(ZoneColor);
		pnt.drawLine(x1,y1,x1,y2);
		pnt.drawLine(x1,y2,x2,y2);
		pnt.drawLine(x2,y2,x2,y1);
		pnt.drawLine(x2,y1,x1,y1);
		
		x1++;
		y1++;
		x2--;
		y2--;
		pnt.setPen(QColor(255-ZoneColor.red(),255-ZoneColor.green(),255-ZoneColor.blue()));
		pnt.drawLine(x1,y1,x1,y2);
		pnt.drawLine(x1,y2,x2,y2);
		pnt.drawLine(x2,y2,x2,y1);
		pnt.drawLine(x2,y1,x1,y1);

		//HookedExecutePaintLast(pnt);

		//QMessageBox::warning(NULL,/**/"Confirm"	,/**/"GeneralDisplayWholeImage::SlotOnPaint .2");
		ReEntrant=false;
		
		//LastPaintTime=t;
	}
}