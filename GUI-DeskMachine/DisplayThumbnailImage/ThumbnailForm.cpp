#include "DisplayThumbnailImageResource.h"
#include "ThumbnailForm.h"
#include "XAlgorithmBase.h"
#include "DisplayThumbnailImagePacket.h"
#include "XResultDLLManager.h"
#include "DisplayNGListButton.h"

ThumbnailForm::ThumbnailForm(LayersBase *Base,QWidget *parent)
	: QFrame(parent) ,LBase(Base)
{
	MasterCanvas.SetMode(mtFrameDraw::fdNone);
	TargetCanvas.SetMode(mtFrameDraw::fdNone);

	//レイアウト
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(6);
	horizontalLayout->setContentsMargins(11, 11, 11, 11);
	horizontalLayout->setObjectName(QString::fromUtf8(/**/"horizontalLayout"));
	horizontalLayout->addWidget(&MasterCanvas);
	horizontalLayout->addWidget(&TargetCanvas);

	DTImageClass=(DisplayThumbnailImage *)parent;
	CenterX=CenterY=-1;
	ZoomRate=1;
	ZoomInRate=1;

	//表示枠対応
	strDefaultBackgroundStyleSheet	= /**/"background-color: "
									+ palette().color(QPalette::Window).name();
	strColorBackgroundStyleSheet	= /**/"background-color: "
									+ QColor(Qt::yellow).name();
	setStyleSheet(strDefaultBackgroundStyleSheet);
}

ThumbnailForm::~ThumbnailForm()
{
}

void	ThumbnailForm::SetFrameColor(bool Enable)
{
	if(Enable==true){
		setStyleSheet(strColorBackgroundStyleSheet);
	}
	else{
		setStyleSheet(strDefaultBackgroundStyleSheet);
	}
}

void	ThumbnailForm::ExecMousePressEvent(GUIFormBase	*DNGListButtonForm)
{
	double Rate=DTImageClass->ZoomInRate/ZoomRate;
	ThumbnailDialog ThumDialog(LBase,Rate,this);
	ThumDialog.SetCenterXY(CenterX,CenterY);
	ThumDialog.SetZoomRate(DTImageClass->ZoomInRate);
	ThumDialog.exec();

	//フォーカス移動
	if(DNGListButtonForm==NULL){
		DNGListButtonForm=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
	}
	if(DNGListButtonForm!=NULL){
		((DisplayNGListButton *)DNGListButtonForm)->GetNGListForm()->activateWindow();
	}
}

void	ThumbnailForm::mousePressEvent(QMouseEvent *event)
{
	//NGリスト
	GUIFormBase	*DNGListButtonForm=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");

	if(CenterX==-1 || CenterY==-1){
		//フォーカス移動
		if(DNGListButtonForm!=NULL){
			((DisplayNGListButton *)DNGListButtonForm)->GetNGListForm()->activateWindow();
		}
		event->accept();
		return;
	}

	//NGリスト移動
	if(DNGListButtonForm!=NULL){
		CmdSetCurrentRow	CmdSetCurRow(LBase);
		CmdSetCurRow.CurrentRow	=CurrentRow;
		DNGListButtonForm->TransmitDirectly(&CmdSetCurRow);
	}

	//拡大表示
	ExecMousePressEvent(DNGListButtonForm);
/*
	//フォーカス移動
	DTImageClass->setFocus();
/*
	//フォーカス移動
	if(DNGListButtonForm!=NULL){
		CmdSetCurrentFocus	CmdSetCurFocus(LBase);
		DNGListButtonForm->TransmitDirectly(&CmdSetCurFocus);
	}
*/
	event->accept();
}

void	ThumbnailForm::wheelEvent(QWheelEvent *event)
{
	//サムネイルをページ移動する
	GUIFormBase	*DNGListButtonForm=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
	if(DNGListButtonForm!=NULL){
		QCoreApplication::sendEvent(DNGListButtonForm,event);
	}
}

//void	ThumbnailForm::keyPressEvent(QKeyEvent *event)
//{
//	GUIFormBase	*DisplayNGList=LBase->FindByName(/**/"Button" ,/**/"DisplayNGListButton" ,/**/"");
//	if(DisplayNGList==NULL){
//		return;
//	}
//	QCoreApplication::sendEvent(DisplayNGList,event);
//}

void	ThumbnailForm::SlotOnMasterPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrantMaster=false;

	if(ReEntrantMaster==true)
		return;
	if(LBase->IsValidData()==false)
		return;

	ReEntrantMaster=true;

	//実行
	ExecuteSlotOnPaint(pnt);

	ReEntrantMaster=false;
}

void	ThumbnailForm::SlotOnTargetPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrantTarget=false;

	if(ReEntrantTarget==true)
		return;
	if(LBase->IsValidData()==false)
		return;

	ReEntrantTarget=true;

	//実行
	ExecuteSlotOnPaint(pnt,false,DTImageClass->ShowNG,DTImageClass->BlinkNG,DTImageClass->BlinkOn);

	ReEntrantTarget=false;
}

void	ThumbnailForm::ExecuteSlotOnPaint(QPainter &pnt,bool IsMastered,bool IsShowNG,bool IsBlinkNG,bool IsBlinkOn)
{
///	HookedExecutePaintFirst(pnt);

	//初期表示
	if(CenterX==-1 || CenterY==-1){
		QBrush	brush(Qt::lightGray);
		pnt.fillRect (0,0,DTImageClass->GetThumForm(0,0)->MasterCanvas.width(),DTImageClass->GetThumForm(0,0)->MasterCanvas.height(), brush );
		return;
	}

	//NG画像サイズを取得し拡大率を求める
	ResultDLLBaseRoot	*RBase=LBase->GetResultDLLBase()->GetFirst()->GetDLLPoint();
///	double	zx=((double)TargetCanvas.width())/((double)RBase->NGImageWidth);
///	double	zy=((double)TargetCanvas.height())/((double)RBase->NGImageHeight);
	double	zx=((double)TargetCanvas.width())/((double)(RBase->NGImageWidth-RBase->NGImageBevel));
	double	zy=((double)TargetCanvas.height())/((double)(RBase->NGImageHeight-RBase->NGImageBevel));
	ZoomRate=(zx>zy)?zy:zx;

	GUICmdSendThumbnailBmp	**BmpReceiver=new GUICmdSendThumbnailBmp*[DTImageClass->GetPageNumb()];
	GUICmdReqThumbnailBmp	**BmpRequester=new GUICmdReqThumbnailBmp*[DTImageClass->GetPageNumb()];
///	double	ZoomRate=GetZoomRate();
///	double	ZoomRate=1.5;
	if(0.00001<=ZoomRate && ZoomRate<10000){
		bool	CommOK=true;
		for(int page=0;page<DTImageClass->GetPageNumb();page++){
			BmpRequester[page]=new GUICmdReqThumbnailBmp(LBase,QString(/**/"Inspection"),QString(/**/"DisplayThumbnailImage"),page);
			BmpReceiver[page]=new GUICmdSendThumbnailBmp(LBase,QString(/**/"Inspection"),QString(/**/"DisplayThumbnailImage"),page);
			BmpRequester[page]->ZoomRate=ZoomRate;
			BmpRequester[page]->Mastered=IsMastered;
			BmpRequester[page]->ShowFixedPhase=DTImageClass->ShowFixedPhase;
			if(IsShowNG==true && IsBlinkOn==true)
				BmpRequester[page]->ShowNG	=true;
			else
				BmpRequester[page]->ShowNG	=false;
			BmpRequester[page]->CanvasWidth	=DTImageClass->GetThumForm(0,0)->TargetCanvas.width();
			BmpRequester[page]->CanvasHeight=DTImageClass->GetThumForm(0,0)->TargetCanvas.height();
			BmpRequester[page]->CenterX=CenterX;
			BmpRequester[page]->CenterY=CenterY;

			if(BmpRequester[page]->Send(LBase->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==false)
				CommOK=false;
		}
		if(CommOK==true){
///			QBrush	brush(Qt::black);
///			pnt.fillRect (0,0,DTImageClass->GetThumForm(0,0)->TargetCanvas.width(),DTImageClass->GetThumForm(0,0)->TargetCanvas.height(), brush );
			for(int page=0;page<DTImageClass->GetPageNumb();page++){
				DataInPage *p=LBase->GetPageData(page);
				if(BmpReceiver[page]->IData!=NULL){
					pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
								 ,*(const QImage *)BmpReceiver[page]->IData);
				}
			}
		}
		for(int page=0;page<DTImageClass->GetPageNumb();page++){
			delete	BmpRequester[page];
			delete	BmpReceiver[page];
		}
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

///	HookedExecutePaintLast(pnt);
}

//=======================================================================

ThumbnailDialog::ThumbnailDialog(LayersBase *Base,double Rate,QWidget *parent)
	: QDialog(parent) ,LBase(Base)
{
	MasterCanvas.SetMode(mtFrameDraw::fdNone);
	TargetCanvas.SetMode(mtFrameDraw::fdNone);

	//レイアウト
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setSpacing(6);
	horizontalLayout->setContentsMargins(11, 11, 11, 11);
	horizontalLayout->setObjectName(QString::fromUtf8(/**/"horizontalLayout"));
	horizontalLayout->addWidget(&MasterCanvas);
	horizontalLayout->addWidget(&TargetCanvas);

	ThumForm=(ThumbnailForm *)parent;
	CenterX=CenterY=-1;
	ZoomRate=1;

	connect(&MasterCanvas,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnMasterPaint(QPainter&)));
	connect(&TargetCanvas,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnTargetPaint(QPainter&)));

///	resize(ThumForm->width()*Rate,ThumForm->height()*Rate);
	//resize(ThumForm->MasterCanvas.width()*Rate,ThumForm->MasterCanvas.height()*Rate);
	//resize(ThumForm->TargetCanvas.width()*Rate,ThumForm->TargetCanvas.height()*Rate);
	resize((ThumForm->TargetCanvas.width()<<1)*Rate,ThumForm->TargetCanvas.height()*Rate);
}

ThumbnailDialog::~ThumbnailDialog()
{
}

void	ThumbnailDialog::mousePressEvent(QMouseEvent *event)
{
	//閉じる
	close();
}

void	ThumbnailDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
		case Qt::Key_Return:
		case Qt::Key_Enter:
			//サムネイル時、拡大画像を閉じる
			close();
			break;
		case Qt::Key_Up:
		case Qt::Key_PageUp:
			ExecZoomIn();
			break;
		case Qt::Key_Down:
		case Qt::Key_PageDown:
			ExecZoomOut();
			break;
	}
}

void	ThumbnailDialog::wheelEvent(QWheelEvent *event)
{
	//イメージを拡大縮小する
	if(event->delta()>0){
		ExecZoomIn();
	}
	else{
		ExecZoomOut();
	}
}

void	ThumbnailDialog::SlotOnMasterPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrantMaster=false;

	if(ReEntrantMaster==true)
		return;
	if(LBase->IsValidData()==false)
		return;

	ReEntrantMaster=true;

	//実行
	ExecuteSlotOnPaint(pnt);

	ReEntrantMaster=false;
}

void	ThumbnailDialog::SlotOnTargetPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrantTarget=false;

	if(ReEntrantTarget==true)
		return;
	if(LBase->IsValidData()==false)
		return;

	ReEntrantTarget=true;

	//実行
	ExecuteSlotOnPaint(pnt,false,ThumForm->GetDTImageClass()->ShowNG,ThumForm->GetDTImageClass()->BlinkNG,ThumForm->GetDTImageClass()->BlinkOn);

	ReEntrantTarget=false;
}

void	ThumbnailDialog::ExecZoomOut()
{
	ZoomRate/=2.0;
	repaint();
}

void	ThumbnailDialog::ExecZoomIn()
{
	ZoomRate*=2.0;
	repaint();
}

void	ThumbnailDialog::ExecuteSlotOnPaint(QPainter &pnt,bool IsMastered,bool IsShowNG,bool IsBlinkNG,bool IsBlinkOn)
{
///	HookedExecutePaintFirst(pnt);

	//初期表示
	if(CenterX==-1 || CenterY==-1){
		QBrush	brush(Qt::lightGray);
		pnt.fillRect (0,0,TargetCanvas.width(),TargetCanvas.height(), brush );
		return;
	}

	GUICmdSendThumbnailBmp	**BmpReceiver=new GUICmdSendThumbnailBmp*[ThumForm->GetDTImageClass()->GetPageNumb()];
	GUICmdReqThumbnailBmp	**BmpRequester=new GUICmdReqThumbnailBmp*[ThumForm->GetDTImageClass()->GetPageNumb()];
///	double	ZoomRate=GetZoomRate();
///	double	ZoomRate=1.5;
	if(0.00001<=ZoomRate && ZoomRate<10000){
		bool	CommOK=true;
		for(int page=0;page<ThumForm->GetDTImageClass()->GetPageNumb();page++){
			BmpRequester[page]=new GUICmdReqThumbnailBmp(LBase,QString(/**/"Inspection"),QString(/**/"DisplayThumbnailImage"),page);
			BmpReceiver[page]=new GUICmdSendThumbnailBmp(LBase,QString(/**/"Inspection"),QString(/**/"DisplayThumbnailImage"),page);
			BmpRequester[page]->ZoomRate=ZoomRate;
			BmpRequester[page]->Mastered=IsMastered;
			BmpRequester[page]->ShowFixedPhase=ThumForm->GetDTImageClass()->ShowFixedPhase;
			if(IsShowNG==true && IsBlinkOn==true)
				BmpRequester[page]->ShowNG	=true;
			else
				BmpRequester[page]->ShowNG	=false;
			BmpRequester[page]->CanvasWidth	=TargetCanvas.width();
			BmpRequester[page]->CanvasHeight=TargetCanvas.height();
			BmpRequester[page]->CenterX=CenterX;
			BmpRequester[page]->CenterY=CenterY;

			if(BmpRequester[page]->Send(LBase->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==false)
				CommOK=false;
		}
		if(CommOK==true){
///			QBrush	brush(Qt::black);
///			pnt.fillRect (0,0,TargetCanvas.width(),TargetCanvas.height(), brush );
			for(int page=0;page<ThumForm->GetDTImageClass()->GetPageNumb();page++){
				DataInPage *p=LBase->GetPageData(page);
				if(BmpReceiver[page]->IData!=NULL){
					pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
								 ,*(const QImage *)BmpReceiver[page]->IData);
				}
			}
		}
		for(int page=0;page<ThumForm->GetDTImageClass()->GetPageNumb();page++){
			delete	BmpRequester[page];
			delete	BmpReceiver[page];
		}
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

///	HookedExecutePaintLast(pnt);
}
//=======================================================================

GUICmdReqThumbnailBmp::GUICmdReqThumbnailBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ZoomRate=0.1;
}

bool	GUICmdReqThumbnailBmp::Save(QIODevice *f)
{
	if(::Save(f,ZoomRate)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,ShowNG)==false)
		return false;
	if(::Save(f,ShowFixedPhase)==false)
		return false;
	if(::Save(f,CanvasWidth)==false)
		return false;
	if(::Save(f,CanvasHeight)==false)
		return false;
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	return(true);
}
bool	GUICmdReqThumbnailBmp::Load(QIODevice *f)
{
	if(::Load(f,ZoomRate)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,ShowNG)==false)
		return false;
	if(::Load(f,ShowFixedPhase)==false)
		return false;
	if(::Load(f,CanvasWidth)==false)
		return false;
	if(::Load(f,CanvasHeight)==false)
		return false;
	if(::Load(f,CenterX)==false)
		return false;
	if(::Load(f,CenterY)==false)
		return false;
	return(true);
}


void	GUICmdReqThumbnailBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendThumbnailBmp	*SendBack=GetSendBack(GUICmdSendThumbnailBmp,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeImage(Mastered,ZoomRate
						,localPage
						,*GetLayersBase()
						,ShowNG
						,ShowFixedPhase
						,CanvasWidth,CanvasHeight
						,CenterX,CenterY);
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendThumbnailBmp::GUICmdSendThumbnailBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData=NULL;
}

GUICmdSendThumbnailBmp::~GUICmdSendThumbnailBmp(void)
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

bool	GUICmdSendThumbnailBmp::Load(QIODevice *f)
{
	if(IData==NULL)
		IData=new QImage();
	IData->load(f,/**/"PNG");
	return(true);
}
bool	GUICmdSendThumbnailBmp::Save(QIODevice *f)
{
	IData->save(f,/**/"PNG");
	return(true);
}

void	GUICmdSendThumbnailBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendThumbnailBmp::MakeImage( bool Mastered ,double ZoomRate
								 ,int localPage
								 ,LayersBase &LocalLBase
								 ,bool ShowNG
								 ,int32 ShowFixedPhase
								 ,int CanvasWidth,int CanvasHeight
								 ,int CenterX,int CenterY)
{
	DataInPage *P;
	if(ShowFixedPhase==-1){
		P=LocalLBase.GetPageData(localPage);
	}
	else{
		P=LocalLBase.GetPageDataPhase(ShowFixedPhase)->GetPageData(localPage);
	}
//	int	LGx=P->GetWidth()*ZoomRate;
//	int	LGy=P->GetHeight()*ZoomRate;
	int	LGx=CanvasWidth;
	int	LGy=CanvasHeight;
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	if(P->GetLayerNumb()==1){
		IData=new QImage(LGx,LGy,QImage::Format_Indexed8);
		//IData->setNumColors(256);
		ImageBuffer	*SBuff=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();

		if(SBuff->IsNull()==true)
			return;
		for(int i=0;i<256;i++){
			IData->setColor ( i, qRgb (i,i,i));
		}
		#pragma omp parallel                  
		{                                                
			#pragma omp for
			for(int y=0;y<LGy;y++){
				BYTE	*d=IData->scanLine(y);
				int		ry=y/ZoomRate;
				if(ry<0 || ry>=LocalLBase.GetParamGlobal()->MaxLines){
					for(int x=0;x<LGx;x++){
						*((BYTE *)d)=0;
						d++;
					}
				}
				else{
					int	x=0;
					int64	mx=0;
					BYTE	*s=SBuff->GetY(ry);
					int	iDotPerLine=LocalLBase.GetParamGlobal()->DotPerLine;
					for(;x<LGx;x++){
						if((mx>>32)>=iDotPerLine)
							break;
						int	NowX=*(s+(mx>>32));
						*((BYTE *)d)=NowX;
						d++;
						mx+=AddX;
					}
					for(;x<LGx;x++){
						*((BYTE *)d)=0;
						d++;
					}
				}
			}
		}
	}
	else
	if(P->GetLayerNumb()==2){
		IData=new QImage(LGx,LGy,QImage::Format_RGB32);
		ImageBuffer	*SBuff0=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	*SBuff1=(Mastered==true)?&P->GetLayerData(1)->GetMasterBuff():&P->GetLayerData(1)->GetTargetBuff();
		if(SBuff0->IsNull()==true)
			return;
		if(SBuff1->IsNull()==true)
			return;
		#pragma omp parallel                  
		{                                                
			#pragma omp for
			for(int y=0;y<LGy;y++){
				BYTE	*d=IData->scanLine(y);
				int	NowY=y/ZoomRate;
				if(NowY<0 || NowY>=LocalLBase.GetParamGlobal()->MaxLines){
					for(int x=0;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;
					}
				}
				else{
					int	x=0;
					int64	mx=0;
					BYTE	*s0=SBuff0->GetY(NowY);
					BYTE	*s1=SBuff1->GetY(NowY);
					int	iDotPerLine=LocalLBase.GetParamGlobal()->DotPerLine;
					for(;x<LGx;x++){
						int	NowX=mx>>32;
						if(NowX>=iDotPerLine)
							break;
						*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8);
						d+=4;
						mx+=AddX;
					}
					for(;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;
					}
				}
			}
		}
	}
	else
	if(P->GetLayerNumb()>=3){
		IData=new QImage(LGx,LGy,QImage::Format_RGB32);
		ImageBuffer	*SBuff0=(Mastered==true)?&P->GetLayerData(0)->GetMasterBuff():&P->GetLayerData(0)->GetTargetBuff();
		ImageBuffer	*SBuff1=(Mastered==true)?&P->GetLayerData(1)->GetMasterBuff():&P->GetLayerData(1)->GetTargetBuff();
		ImageBuffer	*SBuff2=(Mastered==true)?&P->GetLayerData(2)->GetMasterBuff():&P->GetLayerData(2)->GetTargetBuff();
		if(SBuff0->IsNull()==true)
			return;
		if(SBuff1->IsNull()==true)
			return;
		if(SBuff2->IsNull()==true)
			return;
		#pragma omp parallel                  
		{                                                
			#pragma omp for
			for(int y=0;y<LGy;y++){
				BYTE	*d=IData->scanLine(y);
///				int	NowY=y/ZoomRate;
				int	NowY=CenterY+y/ZoomRate-(CanvasHeight>>1)/ZoomRate;
				if(NowY<0 || NowY>=LocalLBase.GetParamGlobal()->MaxLines){
					for(int x=0;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;
					}
				}
				else{
					int	x=0;
					int64	mx=0;
					BYTE	*s0=SBuff0->GetY(NowY);
					BYTE	*s1=SBuff1->GetY(NowY);
					BYTE	*s2=SBuff2->GetY(NowY);
					int	iDotPerLine=LocalLBase.GetParamGlobal()->DotPerLine;
					for(;x<LGx;x++){
///						int	NowX=mx>>32;
						int	NowX=CenterX+(mx>>32)-(CanvasWidth>>1)/ZoomRate;
						if(NowX>=iDotPerLine)
							break;
						*((int32 *)d)=0xFF000000+((*(s0+NowX))<<16)+((*(s1+NowX))<<8)+((*(s2+NowX)));
						d+=4;
						mx+=AddX;
					}
					for(;x<LGx;x++){
						*((int32 *)d)=0;
						d+=4;
					}
				}
			}
		}
	}

	if(ShowNG==true){
		QPainter PntFromIData(IData);
		PntFromIData.setPen(Qt::red);
//		PntFromIData.setBrush(Qt::red);
		ResultInspection	*DRes=LocalLBase.GetCurrentResultForDraw();
		if(DRes!=NULL){
			for(LogicDLL *L=LocalLBase.GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				ResultBaseForAlgorithmRoot *Res=DRes->GetResultBaseForAlgorithm(L->GetInstance());
				if(Res!=NULL){
	///				if(Res->DrawResult(ShowFixedPhase,PntFromIData ,IData ,0,0,ZoomRate ,localPage)==false){
					if(Res->DrawResult(ShowFixedPhase,PntFromIData ,IData ,-(CenterX-(CanvasWidth>>1)/ZoomRate) ,-(CenterY-(CanvasHeight>>1)/ZoomRate) ,ZoomRate ,localPage)==false){
						break;
					}
				}
			}
		}
	}
}

//=====================================================================================
GUICmdReqOkNG::GUICmdReqOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base ,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqOkNG::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}
bool	GUICmdReqOkNG::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqOkNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendOkNG	*SendBack=GetSendBack(GUICmdSendOkNG,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		SendBack->CriticalError	=R->GetCriticalError();
		SendBack->ResultOk		=R->IsResultOK();
		SendBack->ResultTimeOut	=R->IsResultTimeOut();
		SendBack->ResultMaxError=R->IsResultMaxError();
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendOkNG::GUICmdSendOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	CriticalError	=ResultInspection::_NoError;
	ResultOk		=true;
	ResultTimeOut	=false;
	ResultMaxError	=false;
}

bool	GUICmdSendOkNG::Load(QIODevice *f)
{
	WORD	iCriticalError;
	if(::Load(f,iCriticalError)==false)
		return false;
	CriticalError=(ResultInspection::CriticalErrorMode)iCriticalError;

	if(::Load(f,ResultOk)==false)
		return false;
	if(::Load(f,ResultTimeOut )==false)
		return false;
	if(::Load(f,ResultMaxError)==false)
		return false;
	return true;
}
bool	GUICmdSendOkNG::Save(QIODevice *f)
{
	WORD	iCriticalError=(WORD)CriticalError;
	if(::Save(f,iCriticalError)==false)
		return false;

	if(::Save(f,ResultOk)==false)
		return false;
	if(::Save(f,ResultTimeOut )==false)
		return false;
	if(::Save(f,ResultMaxError)==false)
		return false;
	return true;
}

void	GUICmdSendOkNG::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
