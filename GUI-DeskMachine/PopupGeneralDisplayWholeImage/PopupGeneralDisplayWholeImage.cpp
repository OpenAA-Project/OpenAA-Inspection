#include "PopupGeneralDisplayWholeImage.h"
#include "XGUIFormBase.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include <QGridLayout>


static	char	*sRoot="Button";
static	char	*sName="PopupGeneralDisplayWholeImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root="Button";
	Name="PopupGeneralDisplayWholeImage";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Display popup whole image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	(*Base)=new GUICmdReqWholeBmp	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendWholeBmp(Base,QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PopupGeneralDisplayWholeImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<17)
		return(-1);
	Data[0].Type				 ="QColor";
	Data[0].VariableNameWithRoute="FrameColor";
	Data[0].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->FrameColor;
	Data[1].Type				 ="QColor";
	Data[1].VariableNameWithRoute="ZoneColor";
	Data[1].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->ZoneColor;
	Data[2].Type				 ="QStringList";
	Data[2].VariableNameWithRoute="RelatedPanel";
	Data[2].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->RelatedPanel;
	Data[3].Type				 ="bool";
	Data[3].VariableNameWithRoute="Mastered";
	Data[3].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->Mastered;
	Data[4].Type				 ="bool";
	Data[4].VariableNameWithRoute="ShowNG";
	Data[4].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->ShowNG;
	Data[5].Type				 ="bool";
	Data[5].VariableNameWithRoute="BlinkNG";
	Data[5].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->BlinkNG;
	Data[6].Type				 ="QString";
	Data[6].VariableNameWithRoute="Msg";
	Data[6].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->Msg;
	Data[6].Translatable		 =true;
	Data[7].Type				 ="QColor";
	Data[7].VariableNameWithRoute="CharColor";
	Data[7].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->CharColor;
	Data[8].Type				 ="QColor";
	Data[8].VariableNameWithRoute="BackColor";
	Data[8].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->BackColor;
	Data[9].Type				 ="QFont";
	Data[9].VariableNameWithRoute="CFont";
	Data[9].Pointer				 =&((PopupGeneralDisplayWholeImage *)Instance)->CFont;
	Data[10].Type				 ="int32";
	Data[10].VariableNameWithRoute="PopupFormX";
	Data[10].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->PopupFormX;
	Data[11].Type				 ="int32";
	Data[11].VariableNameWithRoute="PopupFormY";
	Data[11].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->PopupFormY;
	Data[12].Type				 ="int32";
	Data[12].VariableNameWithRoute="PopupFormWidth";
	Data[12].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->PopupFormWidth;
	Data[13].Type				 ="int32";
	Data[13].VariableNameWithRoute="PopupFormHeight";
	Data[13].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->PopupFormHeight;
	Data[14].Type				 ="bool";
	Data[14].VariableNameWithRoute="VisibleButton";
	Data[14].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->VisibleButton;
	Data[15].Type				 ="bool";
	Data[15].VariableNameWithRoute="AnytimeShow";
	Data[15].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->AnytimeShow;
	Data[16].Type				 ="bool";
	Data[16].VariableNameWithRoute="LocationInForm";
	Data[16].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->LocationInForm;
	Data[17].Type				 ="int32";
	Data[17].VariableNameWithRoute="ShowFixedPhase";
	Data[17].Pointer			 =&((PopupGeneralDisplayWholeImage *)Instance)->ShowFixedPhase;

	return(18);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/PopupGeneralDisplayWholeImage.png")));
}


//===================================================================================================
PopupGeneralDisplayWholeImage::PopupGeneralDisplayWholeImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent) ,DisplayImageHooked(this)
{
	ShowFixedPhase	=-1;
	Mastered	=true;
	BlinkOn		=true;
	ShowNG		=false;
	BlinkNG		=false;

	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"PopupGeneralDisplayWholeImage");
	Msg="Show whole image";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));

	FrameColor=Qt::red;
	ZoneColor=Qt::yellow;
	PopupForm=new GeneralDisplayWholeImageForm(Base,this);
//	PopupForm.setParent(this);
//	MainCanvas.setParent(&PopupForm);
	MainCanvas.SetMode(mtFrameDraw::fdRectangle);
	MainCanvas.SetFrameColor(Qt::red);
	connect(&MainCanvas,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter&)));
	connect(&MainCanvas,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	RealPos.setTop(0);
	RealPos.setLeft(0);
	int	x1,y1,x2,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);
	RealPos.setRight(x2);
	RealPos.setBottom(y2);
	TM.setInterval(500);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	PopupFormX		=0;
	PopupFormY		=0;
	PopupFormWidth	=250;
	PopupFormHeight	=250;
	VisibleButton	=true;
	AnytimeShow		=false;
	LocationInForm	=true;

	//Layout
	QGridLayout *gridLayout=new QGridLayout(PopupForm);;
	gridLayout->setSpacing	(6);
	gridLayout->setMargin	(0);
	gridLayout->addWidget	(&MainCanvas,0,0,1,1);
}

PopupGeneralDisplayWholeImage::~PopupGeneralDisplayWholeImage()
{
}

void	PopupGeneralDisplayWholeImage::Prepare(void)
{
	MainCanvas.SetFrameColor(FrameColor);
	MainCanvas.ZoomRate=GetZoomRate();
///	TM.start();

	Button.setText		(Msg);
	Button.setFont		(CFont);
	Button.setVisible	(VisibleButton);

	if(AnytimeShow==true){
//		PopupForm->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
///		PopupForm->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowTitleHint);
		SlotClicked(true);
	}
	else if(VisibleButton==false){
///		PopupForm->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowTitleHint);
	}
	else{
///		PopupForm->setWindowFlags(Qt::WindowStaysOnTopHint);	//í‚É‘O–Ê‚É•\Ž¦
	}

	ResizeAction();
}
void	PopupGeneralDisplayWholeImage::ResizeAction()
{
	Button.resize(width(),height());
//	MainCanvas.resize(width(),height());
}

void	PopupGeneralDisplayWholeImage::SlotTimeout()
{
	if(ShowNG==true && BlinkNG==true){
		BlinkOn=!BlinkOn;
		MainCanvas.repaint();
	}
}

void	PopupGeneralDisplayWholeImage::ReceiveFromRelated(int32 cmd ,void *data)
{
	if(cmd==CmdDerivePosition){
		RealPos=*(QRect *)data;
		MainCanvas.repaint();
	}
}

void	PopupGeneralDisplayWholeImage::SlotClicked (bool checked)
{
//	LogoInQWidget(GetLayersBase(),&PopupForm,sRoot ,sName);

	int x=0,y=0;
	if(LocationInForm==true){
		QWidget *f=parentWidget();
		while(f->parentWidget()!=NULL){
			f=f->parentWidget();
		}
		x+=f->x();
		y+=f->y();
	}
	PopupForm->move	(PopupFormX+x,PopupFormY+y);
	PopupForm->resize(PopupFormWidth,PopupFormHeight);
	PopupForm->show	();
}

void	PopupGeneralDisplayWholeImage::SlotDrawEnd(void)
{
	RealPos.setTop	 (MainCanvas.SData.UData.RectangleData.y1);
	RealPos.setLeft	 (MainCanvas.SData.UData.RectangleData.x1);
	RealPos.setRight (MainCanvas.SData.UData.RectangleData.x2);
	RealPos.setBottom(MainCanvas.SData.UData.RectangleData.y2);

	for(int i=0;i<RelatedPanel.count();i++){
		QString	str=RelatedPanel.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
		if(m!=NULL){
			m->SetDrawPosition(MainCanvas.SData.UData.RectangleData.x1,MainCanvas.SData.UData.RectangleData.y1
							  ,MainCanvas.SData.UData.RectangleData.x2,MainCanvas.SData.UData.RectangleData.y2);
		}
	}
	MainCanvas.Clear();
	MainCanvas.repaint();
}
double	PopupGeneralDisplayWholeImage::GetZoomRate(void)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	double	zx=((double)MainCanvas.width())/((double)globalX2);
	double	zy=((double)MainCanvas.height())/((double)globalY2);
	double	ZoomRate=(zx>zy)?zy:zx;
	return ZoomRate;
}


void	PopupGeneralDisplayWholeImage::BuildForShow(void)
{
	MainCanvas.repaint();
}

void	PopupGeneralDisplayWholeImage::ShowInPlayer(int64 shownInspectionID)
{
	if(Mastered==true){
		return;
	}

	bool IsNG=false;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqOkNG		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendOkNG		CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			if(CmdAck.ResultTimeOut==true || CmdAck.ResultMaxError==true){
				IsNG=true;
			}
			else if(CmdAck.ResultOk==false){
				IsNG=true;
			}
		}
	}

	if(IsNG==true){
		MainCanvas.repaint();
		SlotClicked(true);
	}
	else{
		PopupForm->hide();
	}
}

void	PopupGeneralDisplayWholeImage::SlotOnPaint(QPainter &pnt)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	//HookedExecutePaintFirst(pnt);

	ReEntrant=true;
	GUICmdSendWholeBmp	**BmpReceiver=new GUICmdSendWholeBmp*[GetPageNumb()];
	GUICmdReqWholeBmp	**BmpRequester=new GUICmdReqWholeBmp*[GetPageNumb()];
	double	ZoomRate=GetZoomRate();
	if(0.00001<=ZoomRate && ZoomRate<10000){
		bool	CommOK=true;
		for(int page=0;page<GetPageNumb();page++){
			BmpRequester[page]=new GUICmdReqWholeBmp(GetLayersBase(),QString(sRoot),QString(sName),page);
			BmpReceiver[page]=new GUICmdSendWholeBmp(GetLayersBase(),QString(sRoot),QString(sName),page);
			BmpRequester[page]->ZoomRate=ZoomRate;
			BmpRequester[page]->Mastered=Mastered;
			BmpRequester[page]->ShowFixedPhase=ShowFixedPhase;
			if(ShowNG==true && BlinkOn==true)
				BmpRequester[page]->ShowNG	=true;
			else
				BmpRequester[page]->ShowNG	=false;

			if(BmpRequester[page]->Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,*BmpReceiver[page])==false)
				CommOK=false;
		}
		if(CommOK==true){
			QBrush	brush(Qt::black);
			pnt.fillRect (0,0,MainCanvas.width(),MainCanvas.width(), brush );
			for(int page=0;page<GetPageNumb();page++){
				DataInPage *p=GetLayersBase()->GetPageData(page);
				if(BmpReceiver[page]->IData!=NULL){
					pnt.drawImage(p->GetOutlineOffset()->x*ZoomRate ,p->GetOutlineOffset()->y*ZoomRate
								 ,*(const QImage *)BmpReceiver[page]->IData);
				}
			}
		}
		for(int page=0;page<GetPageNumb();page++){
			delete	BmpRequester[page];
			delete	BmpReceiver[page];
		}
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	x1=RealPos.left()*ZoomRate;
	int	y1=RealPos.top()*ZoomRate;
	int	x2=RealPos.right()*ZoomRate;
	int	y2=RealPos.bottom()*ZoomRate;

	pnt.setPen(ZoneColor);
	pnt.drawLine(x1,y1,x1,y2);
	pnt.drawLine(x1,y2,x2,y2);
	pnt.drawLine(x2,y2,x2,y1);
	pnt.drawLine(x2,y1,x1,y1);

	//HookedExecutePaintLast(pnt);

	ReEntrant=false;
}

void	PopupGeneralDisplayWholeImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetZoomRate	*CmdGetZoomRateVar=dynamic_cast<CmdGetZoomRate *>(packet);
	if(CmdGetZoomRateVar!=NULL){
		CmdGetZoomRateVar->ZoomRate=GetZoomRate();
		return;
	}
}

//=======================================================================

GUICmdReqWholeBmp::GUICmdReqWholeBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ZoomRate=0.1;
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
	IData->load(f,"PNG");
	return(true);
}
bool	GUICmdSendWholeBmp::Save(QIODevice *f)
{
	IData->save(f,"PNG");
	return(true);
}

void	GUICmdSendWholeBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

void	GUICmdSendWholeBmp::MakeImage( bool Mastered ,double ZoomRate
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
	int	LGx=P->GetDotPerLine()*ZoomRate;
	int	LGy=P->GetMaxLines()*ZoomRate;
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
	if(P->GetLayerNumb()==3){
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
					BYTE	*s2=SBuff2->GetY(NowY);
					int	iDotPerLine=LocalLBase.GetParamGlobal()->DotPerLine;
					for(;x<LGx;x++){
						int	NowX=mx>>32;
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
					if(Res->DrawResult(ShowFixedPhase,PntFromIData ,IData ,0,0,ZoomRate ,localPage)==false){
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
