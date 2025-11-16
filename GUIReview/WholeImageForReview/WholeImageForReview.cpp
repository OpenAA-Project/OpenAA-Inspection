#include "WholeImageForReviewResource.h"
#include "WholeImageForReview.h"
#include "WholeDisplay.h"
#include "XGeneralFunc.h"
#include "WholeImageForReviewPacket.h"
#include "XReviewCommonPacket.h"
#include "WholeImageForReviewProperty.h"

#include "ReviewStructurePacket.h"
#include "../XGUIReviewGlobal.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"WholeImageForReview";


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Export Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Whole Image");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new WholeImageForReview(Base, parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	Data[0].Type					= /**/"double";
	Data[0].VariableNameWithRoute	=/**/"ZoomImageFromFile";
	Data[0].Pointer					=&((WholeImageForReview *)Instance)->ZoomImageFromFile;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/WholeImageForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WholeImageForReview
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WholeImageForReview::WholeImageForReview(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),FrontImageList(),BackImageList(),mainLayout(new QGridLayout),frontLayout(new QGridLayout),backLayout(new QGridLayout)
	,m_property(),m_propertyUi(NULL),m_propertyDialog(NULL)
{
	initProperty();

	setMinimumSize(100, 100);
	ZoomImageFromFile	=1.0;

	LangSolver.SetUI(this);
}


QList<WholeDisplay *> WholeImageForReview::getImageList(Review::SideType side){
	if(Review::isFront(side)==true){
		return FrontImageList;
	}else{
		return BackImageList;
	}
}

void WholeImageForReview::paintEvent(QPaintEvent *event)
{
	GUIFormBase::paintEvent(event);

	if(GetEditMode()==false)return;

	QPainter painter(this);

	QPen pen;
	pen.setColor(QColor(Qt::black));
	pen.setWidth(1);

	QPen oldPen = painter.pen();

	painter.setPen(pen);

	QRect frect(0, 0, width(), height() );
	int w = lineWidth();
	frect.setTopLeft( QPoint(0, 0) );
	frect.setBottomRight( frect.bottomRight() - QPoint(w, w) );

	painter.drawRect( frect );

	painter.setPen(oldPen);
}

WholeDisplay *WholeImageForReview::getWholeDisplay(Review::SideType side, int phase)
{
	if(phase<getImageList(side).count()){
		return getImageList(side)[phase];
	}else{
		return NULL;
	}
}

WholeDisplay_impl *WholeImageForReview::getWholeDisplayCanvas(Review::SideType side, int phase)
{
	if(getWholeDisplay(side, phase)!=NULL){
		return getWholeDisplay(side, phase)->getDisplay();
	}else{
		return NULL;
	}
}


void WholeImageForReview::connectDisplay(Review::SideType side, int phase)
{
	if(phase<0)return;

	if(side==Review::Front){
		if(phase>=FrontImageList.count())return;

		//connect(FrontImageList[phase], SIGNAL(SignalSelectNG(int)), this, SLOT(SlotFrontNGSelect(int)));
		//connect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalResize()), this, SLOT(loadImageFront()));
		connect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicPiece(Review::SideType,int,QRect)), this, SLOT(SlotSetDragRectImage(Review::SideType,int,QRect)));
		connect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicOrg(Review::SideType,int)), this, SLOT(SlotSetOrgImage(Review::SideType,int)));
	}else{
		if(phase>=BackImageList.count())return;

		//connect(BackImageList[phase], SIGNAL(SignalSelectNG(int)), this, SLOT(SlotBackNGSelect(int)));
		//connect(BackImageList[phase]->getDisplay(), SIGNAL(SignalResize()), this, SLOT(loadImageBack()));
		connect(BackImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicPiece(Review::SideType,int,QRect)), this, SLOT(SlotSetDragRectImage(Review::SideType,int,QRect)));
		connect(BackImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicOrg(Review::SideType,int)), this, SLOT(SlotSetOrgImage(Review::SideType,int)));
	}
}

void WholeImageForReview::disconnectDisplay(Review::SideType side, int phase)
{
	if(phase<0)return;

	if(side==Review::Front){
		if(phase>=FrontImageList.count())return;

		//disconnect(FrontImageList[phase], SIGNAL(SignalSelectNG(int)), this, SLOT(SlotFrontNGSelect(int)));
		//disconnect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalResize()), this, SLOT(loadImageFront()));
		disconnect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicPiece(Review::SideType,int,QRect)), this, SLOT(SlotSetDragRectImage(Review::SideType,int,QRect)));
		disconnect(FrontImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicOrg(Review::SideType,int)), this, SLOT(SlotSetOrgImage(Review::SideType,int)));
	}else{
		if(phase>=BackImageList.count())return;

		//disconnect(BackImageList[phase], SIGNAL(SignalSelectNG(int)), this, SLOT(SlotBackNGSelect(int)));
		//disconnect(BackImageList[phase]->getDisplay(), SIGNAL(SignalResize()), this, SLOT(loadImageBack()));
		disconnect(BackImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicPiece(Review::SideType,int,QRect)), this, SLOT(SlotSetDragRectImage(Review::SideType,int,QRect)));
		disconnect(BackImageList[phase]->getDisplay(), SIGNAL(SignalReqWholePicOrg(Review::SideType,int)), this, SLOT(SlotSetOrgImage(Review::SideType,int)));
	}
}

WholeImageForReview::~WholeImageForReview()
{
	for(int i=0; i<FrontImageList.count(); i++){
		disconnectDisplay(Review::Front, i);
	}
	for(int i=0; i<BackImageList.count(); i++){
		disconnectDisplay(Review::Back, i);
	}
	qDeleteAll(FrontImageList);
	qDeleteAll(BackImageList);
	//if(FrontImage!=0)delete FrontImage;
	//if(BackImage!=0)delete BackImage;
}

void WholeImageForReview::Prepare()
{
	//checkData();
	FrontImageList.append(new WholeDisplay(GetReviewAlgorithm(),Review::Front, 0));
	FrontImageList[0]->setInfoString(LangSolver.GetString(WholeImageForReview_LS,LID_0)/*"FrontWholeImage"*/);
	setPropertyToDisplay(FrontImageList[0], Review::Front);

	BackImageList.append(new WholeDisplay(GetReviewAlgorithm(),Review::Back, 0));
	BackImageList[0]->setInfoString(LangSolver.GetString(WholeImageForReview_LS,LID_1)/*"BackWholeImage"*/);
	setPropertyToDisplay(BackImageList[0], Review::Front);

	// レイアウト設定
	frontLayout->setContentsMargins(0, 0, 0, 0);
	frontLayout->setHorizontalSpacing(1);
	backLayout->setContentsMargins(0, 0, 0, 0);
	backLayout->setHorizontalSpacing(1);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setHorizontalSpacing(1);

	// メインレイアウトを貼り付け
	setLayout(mainLayout);

	// 表裏配置ウィジェット生成
	FrontWidget = new QWidget;
	BackWidget = new QWidget;

	// 表裏のフェイズレイアウト貼り付け
	FrontWidget->setLayout(frontLayout);
	BackWidget->setLayout(backLayout);

	// 最初の全体画像ウィジェット貼り付け
	frontLayout->addWidget(FrontImageList[0], 0, 0);
	backLayout->addWidget(BackImageList[0], 0, 0);

	//connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	//FrontImage->getDisplay()->GetVScroll()->setVisible(false);
	//FrontImage->getDisplay()->GetHScroll()->setVisible(false);
	FrontImageList[0]->getDisplay()->setWholeImage(QImage());// 画像なし

	//BackImage->getDisplay()->GetVScroll()->setVisible(false);
	//BackImage->getDisplay()->GetHScroll()->setVisible(false);
	BackImageList[0]->getDisplay()->setWholeImage(QImage());// 画像なし

	// 初期値設定
	FrontMasterCode = -1;
	BackMasterCode = -1;
	currentIndex = -1;
	currentSide = Review::Front;
	currentEID = -1;
	currentPhase = -1;


	if(GetEditMode()==false){
		//FrontImage->getDisplay()->installEventFilter(this);
		//FrontImage->getDisplay()->GetCanvas()->installEventFilter(this);
		//BackImage->getDisplay()->installEventFilter(this);
		//BackImage->getDisplay()->GetCanvas()->installEventFilter(this);
		QImage Imagef = QImage(FrontImageList.front()->getDisplay()->GetCanvas()->size(), QImage::Format_RGB32);
		Imagef.fill(palette().window().color().rgb());
		FrontImageList[0]->getDisplay()->setWholeImage(Imagef);
		FrontImageList[0]->setVisible(true);
		connectDisplay(Review::Front, 0);

	}else{
		QRect frect( rect() );
		frect.moveTopLeft( frect.topLeft() - QPoint(1,1) );
		frect.setSize( frect.size() - QSize(1,1) );
		setFrameRect( frect );
		QImage Image = QImage(500, 1000, QImage::Format_RGB32);
		Image.fill(QColor(Qt::black).rgb());
		FrontImageList[0]->getDisplay()->setWholeImage(Image);
	}

	setPropertyToUi();
	updateProperty();
}

//void WholeImageForReview::checkData()
//{
//	// 縦横の並び設定
//	if((reqData.viewFrontBackMode&1)==0){
//		viewFrontBackMode = Qt::Vertical;
//	}else{
//		viewFrontBackMode = Qt::Horizontal;
//	}
//
//	if((reqData.viewPhaseMode&1)==0){
//		viewPhaseMode = Qt::Horizontal;
//	}else{
//		viewPhaseMode = Qt::Vertical;
//	}
//
//	setOrientation();
//
//	// 現在NGNailの中心で十字表示する設定
//	viewNGNailCross = reqData.viewNGNailCross;
//
//	for(int i=0; i<FrontImageList.count(); i++){
//		FrontImageList[i]->getDisplay()->setCurrentNGCrossView(viewNGNailCross);
//	}
//	for(int i=0; i<BackImageList.count(); i++){
//		BackImageList[i]->getDisplay()->setCurrentNGCrossView(viewNGNailCross);
//	}
//
//	// NG箇所を表示する設定
//	viewNGPoint = reqData.viewNGPoint;
//	
//	for(int i=0; i<FrontImageList.count(); i++){
//		FrontImageList[i]->getDisplay()->setNGPointView(viewNGPoint);
//	}
//	for(int i=0; i<BackImageList.count(); i++){
//		BackImageList[i]->getDisplay()->setNGPointView(viewNGPoint);
//	}
//
//	// 現在NGNailのみ表示する設定
//	viewOnlyCurrentNail = reqData.viewOnlyCurrentNail;
//
//	for(int i=0; i<FrontImageList.count(); i++){
//		FrontImageList[i]->getDisplay()->setCurrentNGRectOnlyView(viewOnlyCurrentNail);
//	}
//	for(int i=0; i<BackImageList.count(); i++){
//		BackImageList[i]->getDisplay()->setCurrentNGRectOnlyView(viewOnlyCurrentNail);
//	}
//	
//	for(int i=0; i<FrontImageList.count(); i++){
//		FrontImageList[i]->getDisplay()->updateImage();
//	}
//	for(int i=0; i<BackImageList.count(); i++){
//		BackImageList[i]->getDisplay()->updateImage();
//	}
//
//	//updateGUI();
//}

void WholeImageForReview::clearCurrent()
{
	currentIndex = -1;
	currentSide = Review::Front;
	currentEID = -1;

	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->removeCurrentIndex();
		FrontImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()));
		//FrontImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->removeCurrentIndex();
		BackImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()));
		//BackImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
	}
}

void WholeImageForReview::clear()
{
	clearCurrent();

	FrontMasterCode = -1;

	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->removeCurrentIndex();
		FrontImageList[i]->getDisplay()->clearWholeImage();
	}

	BackMasterCode = -1;
	
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->removeCurrentIndex();
		BackImageList[i]->getDisplay()->clearWholeImage();
	}
}

void WholeImageForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *UpdateCmd = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(UpdateCmd!=NULL){
		updateGUI();
		UpdateCmd->Ret = true;
		return;
	}

	GUICmdLoadMasterImage *LoadMImage = dynamic_cast<GUICmdLoadMasterImage *>(packet);
	if(LoadMImage!=NULL){
		loadImage(LoadMImage->side);
		return;
	}

	GUICmdUpdateCurrentHistory *GUICmdUpdateCurrentHistoryVar = dynamic_cast<GUICmdUpdateCurrentHistory *>(packet);
	if(GUICmdUpdateCurrentHistoryVar!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdReqCurrentHistory ReqCurrHistry(GetLayersBase());
			RBase->TransmitDirectly(&ReqCurrHistry);

			if(ReqCurrHistry.Ret==true && ReqCurrHistry.historyPrt()!=NULL){
				//QList<QPoint> FList,BList;
				if(ReqCurrHistry.historyPrt()->hasFront()==true){
					for(int i=0; i<FrontImageList.count(); i++){
						FrontImageList[i]->getDisplay()->setNGNailPosList(*ReqCurrHistry.historyPrt()->getFront(), true);
					}
				}else{
					for(int i=0; i<FrontImageList.count(); i++){
						FrontImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()), true);
					}
				}

				if(ReqCurrHistry.historyPrt()->hasBack()==true){
					for(int i=0; i<BackImageList.count(); i++){
						BackImageList[i]->getDisplay()->setNGNailPosList(*ReqCurrHistry.historyPrt()->getBack(), true);
					}
				}else{
					for(int i=0; i<BackImageList.count(); i++){
						BackImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()), true);
					}
				}
			}else{
				for(int i=0; i<FrontImageList.count(); i++){
					FrontImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()), true);
				}
				for(int i=0; i<BackImageList.count(); i++){
					BackImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()), true);
				}
			}
		}

		GUICmdUpdateCurrentNGNail updateNGIndex(GetLayersBase());
		TransmitDirectly( &updateNGIndex );

		return;
	}

	GUICmdUpdateCurrentNGNail *UpdateCurrentNG = dynamic_cast<GUICmdUpdateCurrentNGNail *>(packet);
	if(UpdateCurrentNG!=NULL){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		CmdReqAdjacentCurrentNG Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			if(Send.existCurrentHistory()==false || Send.existCurrentNG()==false){
				clearCurrent();
				return;
			}

			for(int i=0; i<FrontImageList.count(); i++){
				FrontImageList[i]->getDisplay()->removeCurrentIndex();
			}
			for(int i=0; i<BackImageList.count(); i++){
				BackImageList[i]->getDisplay()->removeCurrentIndex();
			}
			
			if(Send.existCurrentHistory()==true){
				currentEID = Send.currentHistory()->getInspectID();
			}else{
				currentEID = -1;
			}
			currentIndex = Send.currentNGIndex();
			currentSide = Send.currentSide();

			if(Send.existCurrentNG()==true){
				currentPhase = Send.currentNG()->phase;
			}else{
				currentPhase = 0;
			}

			int sum=0;
			for(int i=0; i<FrontImageList.count(); i++){
				sum += FrontImageList[i]->getDisplay()->getHistory().getNGNails().count();
			}
			for(int i=0; i<BackImageList.count(); i++){
				sum += BackImageList[i]->getDisplay()->getHistory().getNGNails().count();
			}

			if(currentIndex<0 || sum<=currentIndex){
				return;
			}

			if(currentSide==Review::Front){
				int startInd = 0;
				if(currentPhase>0){
					for(int i=0; i<currentPhase; i++){
						startInd += FrontImageList[i]->getDisplay()->getHistory().getNGNails().count();
					}
				}
				FrontImageList[currentPhase]->getDisplay()->setCurrentIndex(currentIndex - startInd);
			}else{
				int startInd = 0;
				for(int i=0; i<FrontImageList.count(); i++){
					startInd += FrontImageList[i]->getDisplay()->getHistory().getNGNails().count();
				}
				if(currentPhase>0){
					for(int i=0; i<currentPhase; i++){
						startInd += BackImageList[i]->getDisplay()->getHistory().getNGNails().count();
					}
				}
				BackImageList[currentPhase]->getDisplay()->setCurrentIndex(currentIndex - startInd);
			}

			//if(currentIndex<0 || currentIndex>=(FrontImageList[currentPhase]->getDisplay()->getHistory().NGNails.count() + BackImageList[currentPhase]->getDisplay()->getHistory().NGNails.count())){

			//}else if(currentIndex<FrontImageList[currentPhase]->getDisplay()->getHistory().NGNails.count()){
			//	FrontImageList[currentPhase]->getDisplay()->setCurrentIndex(currentIndex);
			//	BackImageList[currentPhase]->getDisplay()->removeCurrentIndex();
			//}else{
			//	FrontImageList[currentPhase]->getDisplay()->removeCurrentIndex();
			//	BackImageList[currentPhase]->getDisplay()->setCurrentIndex(currentIndex-FrontImageList[currentPhase]->getDisplay()->getHistory().NGNails.count());
			//}
		}else{
			clearCurrent();
			for(int i=0; i<FrontImageList.count(); i++){
				FrontImageList[i]->getDisplay()->removeCurrentIndex();
			}
			for(int i=0; i<BackImageList.count(); i++){
				BackImageList[i]->getDisplay()->removeCurrentIndex();
			}
		}
		for(int i=0; i<FrontImageList.count(); i++){
			FrontImageList[i]->getDisplay()->updateImage();
		}
		for(int i=0; i<BackImageList.count(); i++){
			BackImageList[i]->getDisplay()->updateImage();
		}
		return;
	}

	GUICmdUpdateCurrentLot *GUICmdUpdateCurrentLotVar = dynamic_cast<GUICmdUpdateCurrentLot *>(packet);
	if(GUICmdUpdateCurrentLotVar!=NULL){
		updatePCEArea();
		GUICmdUpdateCurrentHistory histUpCmd(GetLayersBase());
		GUICmdUpdateCurrentNGNail nailUpCmd(GetLayersBase());
		TransmitDirectly(&histUpCmd);
		TransmitDirectly(&nailUpCmd);

		updateImages();

		return;
	}

	GUICmdLockDrawZoom *GUICmdLockDrawZoomVar = dynamic_cast<GUICmdLockDrawZoom *>(packet);
	if(GUICmdLockDrawZoomVar!=NULL){
		setDrawZoomLock(GUICmdLockDrawZoomVar->doLock);
		return;
	}

	//GUICmdSetHistory *SetHistoryCmd = dynamic_cast<GUICmdSetHistory *>(packet);
	//if(SetHistoryCmd!=NULL){
	//	for(int i=0; i<FrontImageList.count(); i++){
	//		FrontImageList[i]->getDisplay()->setNGNailPosList(*SetHistoryCmd->FrontHistoryPtr);
	//	}
	//	for(int i=0; i<BackImageList.count(); i++){
	//		BackImageList[i]->getDisplay()->setNGNailPosList(*SetHistoryCmd->BackHistoryPtr);
	//	}
	//	SetHistoryCmd->Ret = true;
	//	return;
	//}

	GUICmdSetNGNailDrawType *NGNailDrawType = dynamic_cast<GUICmdSetNGNailDrawType *>(packet);
	if(NGNailDrawType!=NULL){
		// 表側
		if(NGNailDrawType->defaultColorPtr!=NULL){
			for(int i=0; i<FrontImageList.count(); i++){
				FrontImageList[i]->getDisplay()->setNGSingDefaultColor(*NGNailDrawType->defaultColorPtr, NGNailDrawType->redraw);
			}
			for(int i=0; i<BackImageList.count(); i++){
				BackImageList[i]->getDisplay()->setNGSingDefaultColor(*NGNailDrawType->defaultColorPtr, NGNailDrawType->redraw);
			}
		}
		
		// 裏側
		if(NGNailDrawType->currentColorPtr!=NULL){
			for(int i=0; i<FrontImageList.count(); i++){
				FrontImageList[i]->getDisplay()->setNGSingCurrentColor(*NGNailDrawType->currentColorPtr, NGNailDrawType->redraw);
			}
			for(int i=0; i<BackImageList.count(); i++){
				BackImageList[i]->getDisplay()->setNGSingCurrentColor(*NGNailDrawType->currentColorPtr, NGNailDrawType->redraw);
			}
		}
		return;
	}

	GUICmdSetCurrentNGView *GUICmdSetCurrentNGViewVar = dynamic_cast<GUICmdSetCurrentNGView *>(packet);
	if(GUICmdSetCurrentNGViewVar!=NULL){
		for(int i=0; i<FrontImageList.count(); i++){
			FrontImageList[i]->getDisplay()->setCurrentNGRectVisible(GUICmdSetCurrentNGViewVar->visible, GUICmdSetCurrentNGViewVar->redraw);
		}
		for(int i=0; i<BackImageList.count(); i++){
			BackImageList[i]->getDisplay()->setCurrentNGRectVisible(GUICmdSetCurrentNGViewVar->visible, GUICmdSetCurrentNGViewVar->redraw);
		}
		GUICmdSetCurrentNGViewVar->Ret = true;
		return;
	}

	GUICmdUpdateWholeImage *GUICmdUpdateWholeImageVar = dynamic_cast<GUICmdUpdateWholeImage *>(packet);
	if(GUICmdUpdateWholeImageVar!=NULL){
		for(int i=0; i<FrontImageList.count(); i++){
			FrontImageList[i]->getDisplay()->updateImage();
		}
		for(int i=0; i<BackImageList.count(); i++){
			BackImageList[i]->getDisplay()->updateImage();
		}
		return;
	}

	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::WholeImageForReview);
		return;
	}
}

void WholeImageForReview::updateGUI()
{
	updateProperty();

	// 各イメージを初期化
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->removeCurrentIndex();
		FrontImageList[i]->getDisplay()->clearNGNailPosList();
		FrontImageList[i]->getDisplay()->clearWholeImage();
		//FrontImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->removeCurrentIndex();
		BackImageList[i]->getDisplay()->clearNGNailPosList();
		BackImageList[i]->getDisplay()->clearWholeImage();
		//FrontImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
	}

	// ReviewStructureへのアクセスポインタ
	ReviewPIBase *RBase = GetReviewAlgorithm();
	setUpdatesEnabled(false);
	if(RBase!=NULL){
		// 配置を整え
		setOrientation(getProperty().viewFrontBackOrientation, getProperty().viewPhaseOrientation);

		// 画像を読み込み
		loadImage(Review::Front);
		loadImage(Review::Back);

		updatePCEArea();

		CmdReqCurrentHistory ReqCurrHistry(GetLayersBase());
		RBase->TransmitDirectly(&ReqCurrHistry);

		if(ReqCurrHistry.Ret==true && ReqCurrHistry.historyPrt()!=NULL){
			//QList<QPoint> FList,BList;
			if(ReqCurrHistry.historyPrt()->hasFront()==true){
				for(int i=0; i<FrontImageList.count(); i++){
					FrontImageList[i]->getDisplay()->setNGNailPosList(*ReqCurrHistry.historyPrt()->getFront());
					//FrontImageList[i]->getDisplay()->setOutlineOffset(ReqInfoCmd.FrontOutlineDrawOffset[i]);
				}
			}

			if(ReqCurrHistry.historyPrt()->hasBack()==true){
				for(int i=0; i<BackImageList.count(); i++){
					BackImageList[i]->getDisplay()->setNGNailPosList(*ReqCurrHistry.historyPrt()->getBack());
					//BackImageList[i]->getDisplay()->setOutlineOffset(ReqInfoCmd.BackOutlineDrawOffset[i]);
				}
			}
		}else{
			for(int i=0; i<FrontImageList.count(); i++){
				FrontImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()));
				//FrontImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
			}
			for(int i=0; i<BackImageList.count(); i++){
				BackImageList[i]->getDisplay()->setNGNailPosList(HistoryItem(GetReviewAlgorithm()));
				//BackImageList[i]->getDisplay()->setOutlineOffset(QList<QPoint>());
			}
		}
		
		CmdReqWholeImageInfo ReqInfoCmd(GetLayersBase());
		RBase->TransmitDirectly(&ReqInfoCmd);

		for(int i=0; i<FrontImageList.count(); i++){
			FrontImageList[i]->getDisplay()->setOutlineOffset(ReqInfoCmd.FrontOutlineDrawOffset[i]);
		}
		for(int i=0; i<BackImageList.count(); i++){
			BackImageList[i]->getDisplay()->setOutlineOffset(ReqInfoCmd.BackOutlineDrawOffset[i]);
		}
		
	}

	GUICmdUpdateCurrentNGNail selfCmd(GetLayersBase());
	TransmitDirectly(&selfCmd);

	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->updateImage();
		FrontImageList[i]->getDisplay()->update();
	}

	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->updateImage();
		BackImageList[i]->getDisplay()->update();
	}

	//checkData();

	setUpdatesEnabled(true);
}

bool WholeImageForReview::eventFilter(QObject *target, QEvent *event)
{
	bool targetFlg = false;

	for(int i=0; i<FrontImageList.count(); i++){
		if(FrontImageList[i]==target || FrontImageList[i]->getDisplay()==target){
			targetFlg = true;
			break;
		}
	}

	if(targetFlg==false){
		for(int i=0; i<BackImageList.count(); i++){
			if(BackImageList[i]==target || FrontImageList[i]->getDisplay()==target){
				targetFlg = true;
				break;
			}
		}
	}

	if(targetFlg==true){
		if(event->type()==QEvent::MouseButtonPress ||// マウスボタン押下
			event->type()==QEvent::MouseMove ||// マウスカーソル移動
			event->type()==QEvent::MouseButtonRelease ||// マウスボタン離し
			event->type()==QEvent::MouseButtonDblClick){// マウスボタンダブルクリック
			return true;
		}
	}

	return QObject::eventFilter(target, event);
}

bool WholeImageForReview::loadImage(QString filename, unsigned int nPhase, unsigned int nPage)
{
	//QFile file(filename);
	//int32	iVer, iDotPerLine, iMaxLines, iPageNumb, iLayerNumb, iYCountBase;

	//if(file.open(QIODevice::ReadOnly)==true){
	//	switch(nPhase){
	//	case 0:
	//		if(FrontImageList.size()<nPage+1){
	//			int addCount = nPage - FrontImageList.size() + 1;
	//			for(int i=0; i<addCount; i++){
	//				FrontImageList.append(NULL);
	//			}
	//			FrontImageList[nPage] = new DisplayImageForReviewSuperClass(GetLayersBase(), sRoot, sName, DisplayImage::DisplayType::__Master, this);
	//		}
	//		
	//		if(GetLayersBase()->LoadPIXInfo(file, iVer, iDotPerLine, iMaxLines, iPageNumb, iLayerNumb, iYCountBase)==false){
	//			QMessageBox::warning(this, "Load Pix Error", "False load pix : pix info is not enable.");
	//			return false;
	//		}

	//		return true;
	//		break;
	//	case 1:
	//		if(BackImageList.size()<nPage+1){
	//			int addCount = nPage - BackImageList.size() + 1;
	//			for(int i=0; i<addCount; i++){
	//				BackImageList.append(NULL);
	//			}
	//			BackImageList[nPage] = new DisplayImageForReviewSuperClass(GetLayersBase(), sRoot, sName, DisplayImage::DisplayType::__Master, this);
	//		}
	//		return true;
	//		break;
	//	default:
	//		return false;
	//	}
	//}
	//return false;
	return false;
}

void WholeImageForReview::setOrientation(Qt::Orientation orientationFrontBack, Qt::Orientation orientationPhase)
{
	static bool first = true;
	setUpdatesEnabled(false);
	if(first==true){
		mainLayout->addWidget(FrontWidget, 0, 0);
		first = false;
		setUpdatesEnabled(true);
		return;
	}
	
	// 表裏ウィジェットの取り外し
	mainLayout->removeWidget(FrontWidget);
	mainLayout->removeWidget(BackWidget);

	// 非表示化
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->setVisible(false);
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->setVisible(false);
	}

	// フェイズウィジェットの取り外し
	while(frontLayout->count()!=0){
		frontLayout->takeAt(0);
	}
	while(backLayout->count()!=0){
		backLayout->takeAt(0);
	}

	// フェイズウィジェットの再配置
	if(orientationPhase==Qt::Horizontal){
		// 前面再配置
		for(int i=0; i<FrontImageList.count(); i++){
			frontLayout->addWidget(FrontImageList[i], 0, i);
		}
		// 後面再配置
		for(int i=0; i<BackImageList.count(); i++){
			backLayout->addWidget(BackImageList[i], 0, i);
		}
	}else{
		// 前面再配置
		for(int i=0; i<FrontImageList.count(); i++){
			frontLayout->addWidget(FrontImageList[i], i, 0);
		}
		// 後面再配置
		for(int i=0; i<BackImageList.count(); i++){
			backLayout->addWidget(BackImageList[i], i, 0);
		}
	}

	// 表裏ウィジェット再配置
	if(orientationFrontBack==Qt::Horizontal){
		mainLayout->addWidget(FrontWidget, 0, 0);
		mainLayout->addWidget(BackWidget, 0, 1);
	}else{
		mainLayout->addWidget(FrontWidget, 0, 0);
		mainLayout->addWidget(BackWidget, 1, 0);
	}

	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->setVisible( FrontImageList[i]->getDisplay()->hasImage() );
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->setVisible( BackImageList[i]->getDisplay()->hasImage() );
	}

	setUpdatesEnabled(true);
}

void WholeImageForReview::setOrientation()
{
	setOrientation(getProperty().viewFrontBackOrientation, getProperty().viewPhaseOrientation);
};

void WholeImageForReview::setNGCrossView(bool view)
{
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->setCurrentNGCrossView(view);
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->setCurrentNGCrossView(view);
	}
}

void WholeImageForReview::setNGPointView(bool view)
{	
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->setNGPointView(view);
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->setNGPointView(view);
	}
}

void WholeImageForReview::setOnlyCurrentNGNailRectView(bool view)
{
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->setCurrentNGRectOnlyView(view);
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->setCurrentNGRectOnlyView(view);
	}
}

bool WholeImageForReview::loadImage(Review::SideType side)
{
	//WholeDisplay *TargetImage;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return false;

	// 読み込まれているマスターデータの情報を取得
	CmdReqMasterDataInfo ReqMInfoCmd(GetLayersBase());
	RBase->TransmitDirectly(&ReqMInfoCmd);
	
	if(ReqMInfoCmd.Ret==false)return false;

	// ターゲット選択
	QList<WholeDisplay *> *targetList;
	MasterDataInfo targetInfo;
	int *targetMasterCode;
	if(side==Review::Front){
		targetList = &FrontImageList;
		targetInfo = ReqMInfoCmd.FrontMasterDataInfo;
		FrontMasterCode = ReqMInfoCmd.FrontMasterDataInfo.MasterCode;
		targetMasterCode = &FrontMasterCode;
	}else{
		targetList = &BackImageList;
		targetInfo = ReqMInfoCmd.BackMasterDataInfo;
		BackMasterCode = ReqMInfoCmd.BackMasterDataInfo.MasterCode;
		targetMasterCode = &BackMasterCode;
	}

	// 現在のデータをクリア
	//qDeleteAll(targetList->begin(), targetList->end());
	//targetList->clear();

	// 現在のシグナルスロット接続を切断
	for(int i=0; i<targetList->count(); i++){
		disconnectDisplay(side, i);
	}

	// 画像を削除
	for(int i=targetInfo.PhaseNumb; i<targetList->count(); i++){
		(*targetList)[i]->getDisplay()->clearWholeImage();
	}

	// 余分なバッファを削除
	while(targetList->count()>targetInfo.PhaseNumb){
		delete targetList->takeAt(targetInfo.PhaseNumb);
	}

	// フェイズ数だけバッファを作成
	while(targetList->count()<targetInfo.PhaseNumb){
		WholeDisplay *tmp = new WholeDisplay(GetReviewAlgorithm(),side, targetList->count());
		tmp->setVisible(false);
		targetList->append(tmp);
	}
	
	// ディスプレイとのシグナルスロット接続
	for(int i=0; i<targetList->count(); i++){
		connectDisplay(side, i);
	}

	// プロパティ設定を適用
	for(int i=0; i<targetList->count(); i++){
		setPropertyToDisplay((*targetList)[i], side);
	}

	// マスターコードが設定されていない場合は画像をクリアして終了
	if(targetInfo.MasterCode==-1){
		*targetMasterCode = -1;
		for(int i=0; i<targetList->count(); i++){
			(*targetList)[i]->getDisplay()->clearWholeImage();
		}
		return true;
	}

	for(int phase=0; phase<ReqMInfoCmd.getInfo(side).PhaseNumb; phase++){
		loadImage(side, phase);
	}

	//if(side==Review::Front){
	//	//if(FrontMasterCode==ReqMInfoCmd.FrontMasterDataInfo.MasterCode)return true;// 同じマスターデータなら処理を終了
	//	if(ReqMInfoCmd.FrontMasterDataInfo.MasterCode==-1){
	//		FrontMasterCode = -1;
	//		for(int i=0; i<FrontImageList.count(); i++){
	//			FrontImageList[i]->getDisplay()->setWholeImage(NULL);
	//		}
	//		return true;
	//	}

	//	CmdReqWholeImage ReqWholeImage(GetLayersBase());
	//	ReqWholeImage.ReqWidth = FrontImage->getDisplay()->GetCanvasWidth();
	//	ReqWholeImage.ReqHeight = FrontImage->getDisplay()->GetCanvasHeight();
	//	RBase->TransmitDirectly(&ReqWholeImage);
	//	
	//	FrontMasterCode = ReqMInfoCmd.FrontMasterDataInfo.MasterCode;
	//	//ReqWholeImage.FrontWholePic.save("FrontWholeViewPic.png", "PNG");
	//	FrontImage->getDisplay()->setWholeImage( new QImage(ReqWholeImage.FrontWholePic), &ReqWholeImage.FrontWholeOrizinalSize );
	//	FrontImage->setVisible(true);

	//	//QMessageBox::about(this, "WH", QString("%1,%2").arg(ReqWholeImage.FrontWholePic.size().width()).arg(ReqWholeImage.FrontWholePic.size().height()));
	//}else{
	//	//if(BackMasterCode==ReqMInfoCmd.BackMasterDataInfo.MasterCode)return true;// 同じマスターデータなら処理を終了
	//	if(ReqMInfoCmd.BackMasterDataInfo.MasterCode==-1){
	//		BackMasterCode = -1;
	//		BackImage->getDisplay()->setWholeImage(NULL);
	//		BackImage->setVisible(false);
	//		return true;
	//	}

	//	CmdReqWholeImage ReqWholeImage(GetLayersBase());
	//	ReqWholeImage.ReqWidth = FrontImage->getDisplay()->GetCanvasWidth();
	//	ReqWholeImage.ReqHeight = FrontImage->getDisplay()->GetCanvasHeight();
	//	RBase->TransmitDirectly(&ReqWholeImage);

	//	BackMasterCode = ReqMInfoCmd.BackMasterDataInfo.MasterCode;
	//	//qDebug() << ReqWholeImage.BackWholePic.size();
	//	BackImage->getDisplay()->setWholeImage( new QImage(ReqWholeImage.BackWholePic), &ReqWholeImage.BackWholeOrizinalSize );
	//	BackImage->setVisible(true);
	//}

	// 現在の画像の消去(画像が無い場合は何もしない)
	//TargetImage->GetCanvas()->DelImage();

	//BYTE *pR,*pG,*pB;
	//QList<QImage> BuffImgList;
	//for(int page=0; page<GetLayersBase()->GetPageNumb(); page++){
	//	QImage image(GetLayersBase()->GetPageData(page)->GetDotPerLine(), GetLayersBase()->GetPageData(page)->GetMaxLines(), QImage::Format_RGB32);
	//	for(int Y=0;Y<GetLayersBase()->GetParamGlobal()->GetMaxLines();Y++){
	//		pR=GetLayersBase()->GetPageData(page)->GetLayerData(0)->GetMasterBuff().GetY(Y);
	//		pG=GetLayersBase()->GetPageData(page)->GetLayerData(1)->GetMasterBuff().GetY(Y);
	//		pB=GetLayersBase()->GetPageData(page)->GetLayerData(2)->GetMasterBuff().GetY(Y);
	//		QRgb *pYLine=(QRgb *)image.scanLine(Y);
	//		for(int X=0;X<GetLayersBase()->GetPageData(page)->GetDotPerLine();X++,pR++,pG++,pB++){
	//			*pYLine = qRgb(*pR,*pG,*pB);
	//			pYLine++;
	//		}
	//	}
	//	BuffImgList.append(image);
	//	OutlineList->append(QPoint(GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x,GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y));
	//}


	//if(OutlineList->count()>0){
	//	int minX,maxX;
	//	int minY,maxY;
	//	minX = maxX = OutlineList->first().x();
	//	minY = maxY = OutlineList->first().y();

	//	for(int i=1; i<OutlineList->count(); i++){
	//		if(minX<OutlineList->at(i).x()){
	//			minX = OutlineList->at(i).x();
	//		}
	//		if(maxX>OutlineList->at(i).x()){
	//			maxX = OutlineList->at(i).x();
	//		}
	//		if(minY<OutlineList->at(i).y()){
	//			minY = OutlineList->at(i).y();
	//		}
	//		if(maxY>OutlineList->at(i).y()){
	//			maxY = OutlineList->at(i).y();
	//		}
	//	}

	//	QPoint p(-minX, -minY);

	//	int w = qAbs(maxX - minX) + GetLayersBase()->GetDotPerLine();
	//	int h = qAbs(maxY - minY) + GetLayersBase()->GetMaxLines();

	//	QList<QPoint> shiftOutlineList;
	//	for(int i=0; i<OutlineList->count(); i++){
	//		shiftOutlineList.append(QPoint(OutlineList->at(i) + p));
	//	}

	//	QImage *WholeImage = new QImage(w, h, QImage::Format_RGB32);
	//	WholeImage->fill(QColor(Qt::black).rgb());
	//	QPainter painter;
	//	painter.begin(WholeImage);
	//	for(int i=0; i<BuffImgList.count(); i++){
	//		painter.drawImage(shiftOutlineList.at(i).x(), shiftOutlineList.at(i).y(), BuffImgList.at(i));
	//	}
	//	painter.end();

	//	TargetImage->setWholeImage(WholeImage);
	//	//TargetImage->GetCanvas()->SetImage(WholeImage);

	//	//int ImageWidth = TargetImage->GetCanvasWidth();
	//	//int ImageHeight = TargetImage->GetCanvasHeight();
	//	//int MWidth = WholeImage->width();
	//	//int MHeight = WholeImage->height();
	//	//double zoomRate;

	//	//// キャンバスの大きさに合わせてマスター画像の拡大率を調整
	//	//if( (ImageHeight/(double)ImageWidth) < (MHeight/(double)MWidth) ){
	//	//	zoomRate = ImageHeight / (double)MHeight;
	//	//}else{
	//	//	zoomRate = ImageWidth / (double)MWidth;
	//	//}
	//	//TargetImage->ZoomDraw(0, 0, zoomRate);
	//}

	//ResizeAction();

	setOrientation();

	return true;
}

bool WholeImageForReview::loadImage(Review::SideType side, int phase)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL){
		return false;
	}

	WholeDisplay *widget = getWholeDisplay(side, phase);
	if(widget==NULL){
		return false;
	}
	WholeDisplay_impl *canvas = widget->getDisplay();

	CmdReqWholeImageInfo ReqWholeImageInfo(GetLayersBase());
	RBase->TransmitDirectly( &ReqWholeImageInfo );
	if(ReqWholeImageInfo.getWholeOriginalSize(side, phase).isNull()==true){
		canvas->setWholeImage(QImage());
		return true;
	}

	CmdReqWholeImage ReqWholeImage(GetLayersBase());
	ReqWholeImage.ZoomImageFromFile	=ZoomImageFromFile;
	ReqWholeImage.setReqPhase(phase);
	widget->updateGeometry();

	QSize csize(canvas->GetCanvasSize());
	QSize osize(ReqWholeImageInfo.getWholeOriginalSize(side, phase));

	QRect orect(QPoint(0, 0), osize);
		
	QRect rorect = Review::rotateRect(orect, canvas->rotate());

	QSize ororect = rorect.size();
	ororect.scale(csize, Qt::KeepAspectRatio);

	QRect rrorect = Review::rotateRect(QRect(QPoint(0,0), ororect), -canvas->rotate());
	
	ReqWholeImage.setReqWidth(rrorect.width());
	ReqWholeImage.setReqHeight(rrorect.height());
	RBase->TransmitDirectly(&ReqWholeImage);
	QSize size = ReqWholeImage.getWholeSize(side);
	canvas->setWholeImage( ReqWholeImage.getWholePic(side), &osize );
		
	QString infoStr;
	if(side==Review::Front && phase==0){
		infoStr += LangSolver.GetString(WholeImageForReview_LS,LID_2)/*"FrontWholeImage"*/;
		//connect((*targetList)[i], SIGNAL(SignalResize()), this, SLOT(loadImageFront()));
	}else{
		infoStr += LangSolver.GetString(WholeImageForReview_LS,LID_3)/*"BackWholeImage"*/;
		//connect((*targetList)[i], SIGNAL(SignalResize()), this, SLOT(loadImageBack()));
	}
	if(getImageList(side).count()>1){
		infoStr += QString(/**/" - Phase:%1").arg(phase);
	}

	widget->setInfoString(infoStr);

	return true;
}

//void DisplayImageForReview::Prepare()
//{
//	DisplayImage::Prepare();
//
//	IBar.setVisible(false);
//	
//	if(XPosLabel!=NULL)XPosLabel->setVisible(false);
//	if(YPosLabel!=NULL)YPosLabel->setVisible(false);
//
//	ClientTop=0;
//}

void WholeImageForReview::SlotFrontNGSelect(int phase, int index)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdSetCurrentNGNail Send(GetLayersBase());
	Send.refType = Review::RefType::Ref_Index;
	Send.locate = Review::ListLocate::Manual;
	Send.Index = index;
	RBase->TransmitDirectly(&Send);

	if(Send.Ret==true){
		ReviewGUI::UpdateNGNailGUIAll(GetLayersBase());
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail);
		if(Base!=NULL){
			GUICmdSetCurrentNGNail SetShowThumbnailCurrentNGNail(GetLayersBase());
			SetShowThumbnailCurrentNGNail.GlobalIndex = index;
			Base->TransmitDirectly(&SetShowThumbnailCurrentNGNail);
		}
	}

	if(FrontImageList.count()>phase){
		FrontImageList[phase]->getDisplay()->setCurrentIndex(index, true);
	}
}

void WholeImageForReview::SlotBackNGSelect(int phase, int index)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdSetCurrentNGNail Send(GetLayersBase());
	Send.refType = Review::RefType::Ref_Index;
	Send.locate = Review::ListLocate::Manual;
	Send.Index = index;
	for(int i=0; i<FrontImageList.count(); i++){
		Send.Index += FrontImageList[i]->getDisplay()->getHistory().getNGNails().count();
	}
	RBase->TransmitDirectly(&Send);
	
	if(Send.Ret==true){
		ReviewGUI::UpdateNGNailGUIAll(GetLayersBase());
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::ShowThumbnail);
		if(Base!=NULL){
			GUICmdSetCurrentNGNail SetShowThumbnailCurrentNGNail(GetLayersBase());
			SetShowThumbnailCurrentNGNail.GlobalIndex = Send.Index/*index + FrontImage->getDisplay()->getHistory().NGNails.count()*/;
			Base->TransmitDirectly(&SetShowThumbnailCurrentNGNail);
		}
	}

	if(BackImageList.count()>phase){
		BackImageList[phase]->getDisplay()->setCurrentIndex(index, true);
	}
}

void WholeImageForReview::SlotSetDragRectImage(Review::SideType side, int phase, QRect rect)
{
	if(rect.width()<=0 || rect.height()<=0){
		updateGUI();
		return;
	}

	WholeDisplay_impl *display;
	QImage img;

	if(side==Review::Front && phase==0){
		display = FrontImageList[phase]->getDisplay();
	}else{
		display = BackImageList[phase]->getDisplay();
	}

	int rotate = display->rotate();

	QRect viewRawRect = display->getCurrentViewRect();// 現在表示中の画像生矩形データ(1倍表示は(0,0,-1,-1):isEmpty()==true)
	QSize canvasSize = QSize(display->GetCanvasWidth(), display->GetCanvasHeight());// キャンバスサイズ
	QSize stSize;// 表示されている画像の生サイズ
	
	if(viewRawRect.isEmpty()==true){
		stSize = display->getWholeImageOrgSize();// 1倍はすべて
	}else{
		stSize = viewRawRect.size();// 現在表示している生サイズ
		return;// 現在一回のみ; This will be able to few continue.
	}

	QSize tstSize = stSize;
	tstSize.scale(canvasSize, Qt::KeepAspectRatio);

	qreal zoomRate = display->getWholeImageOrgSize().width() / (qreal)tstSize.width();
	QRect pieceRawRect = rect;//(viewRawRect.left() + rect.left() * zoomRate, viewRawRect.top() + rect.top() * zoomRate, rect.width() * zoomRate, rect.height() * zoomRate);

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqWholeImageInfo ReqWholeImfoCmd(GetLayersBase());
		RBase->TransmitDirectly( &ReqWholeImfoCmd );

		QSize orgSize;
		if(side==Review::Front && phase<ReqWholeImfoCmd.FrontOutlineOffset.count() && ReqWholeImfoCmd.FrontOutlineOffset[phase].isEmpty()==false){
			pieceRawRect.setTop( pieceRawRect.top() + ReqWholeImfoCmd.FrontOutlineOffset[phase][0].x() );
			pieceRawRect.setLeft( pieceRawRect.left() + ReqWholeImfoCmd.FrontOutlineOffset[phase][0].y() );
			orgSize = ReqWholeImfoCmd.FrontWholeOrizinalSize[phase];
		}else if(side==Review::Back && phase<ReqWholeImfoCmd.BackOutlineOffset.count() && ReqWholeImfoCmd.BackOutlineOffset[phase].isEmpty()==false){
			pieceRawRect.setTop( pieceRawRect.top() + ReqWholeImfoCmd.BackOutlineOffset[phase][0].x() );
			pieceRawRect.setLeft( pieceRawRect.left() + ReqWholeImfoCmd.BackOutlineOffset[phase][0].y() );
			orgSize = ReqWholeImfoCmd.BackWholeOrizinalSize[phase];
		}else{
			// none
		}

		CmdReqMasterImagePieceOnOneImage ReqWholePieceCmd(GetLayersBase());
		ReqWholePieceCmd.setData(side, phase, pieceRawRect);

		RBase->TransmitDirectly( &ReqWholePieceCmd );
		if(ReqWholePieceCmd.Ret==true){
			QSize wholeImageSize = ReqWholePieceCmd.image.size();
			QSize rwholeImageSize = Review::rotateRect(QRect(QPoint(0,0), wholeImageSize), display->rotate()).size();

			QSize srwholeImageSize = rwholeImageSize;
			srwholeImageSize.scale(canvasSize, Qt::KeepAspectRatio);
			QSize scalingSize = Review::rotateRect(QRect(QPoint(0,0), srwholeImageSize), -display->rotate()).size();

			QImage image(scalingSize, QImage::Format_RGB32);
			image.fill(0);
			QPainter painter;

			painter.begin(&image);
			painter.drawImage(0, 0, ReqWholePieceCmd.image.scaled(scalingSize, Qt::KeepAspectRatio));
			painter.end();

			//image.save("Test.png", "PNG");
			
			display->setWholeImage(image, &orgSize);
			display->setCurrentViewRect(pieceRawRect);
		}
	}
}

void WholeImageForReview::SlotSetOrgImage(Review::SideType side,int phase)
{
	loadImage(side, phase);
	return;

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	WholeDisplay *TargetDisplay;
	if(side==Review::Front){
		TargetDisplay = FrontImageList[phase];
	}else{
		TargetDisplay = BackImageList[phase];
	}

	CmdReqWholeImage ReqWholeImage(GetLayersBase());
	ReqWholeImage.ZoomImageFromFile	=ZoomImageFromFile;
	ReqWholeImage.setReqPhase(phase);
	
	QSize osize(TargetDisplay->getDisplay()->GetCanvasWidth(), TargetDisplay->getDisplay()->GetCanvasHeight());
	QRect rect(0, 0, osize.width(), osize.height());
	QRect rrect = Review::rotateRect(rect, TargetDisplay->getDisplay()->rotate());
	rrect.moveTopLeft(QPoint(0,0));
	QRect inrect = (rect & rrect);
	ReqWholeImage.setReqSize(inrect.size());

	//ReqWholeImage.ReqWidth = TargetDisplay->getDisplay()->GetCanvasWidth();
	//ReqWholeImage.ReqHeight = TargetDisplay->getDisplay()->GetCanvasHeight();
	RBase->TransmitDirectly(&ReqWholeImage);
	QSize size = ReqWholeImage.getWholeSize(side);
	TargetDisplay->getDisplay()->setWholeImage( QImage(ReqWholeImage.getWholePic(side)), &size, true );
}

void WholeImageForReview::updatePCEArea()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqMasterDataInfo reqMInfoCmd(GetLayersBase());
	RBase->TransmitDirectly(&reqMInfoCmd);

	CmdReqPCEList reqPCECmd(GetLayersBase());
	RBase->TransmitDirectly(&reqPCECmd);

	for(int phase=0; phase<FrontImageList.count(); phase++){
		FrontImageList[phase]->getDisplay()->setPCEArea(reqPCECmd.FrontList);
	}

	for(int phase=0; phase<BackImageList.count(); phase++){
		BackImageList[phase]->getDisplay()->setPCEArea(reqPCECmd.BackList);
	}
}

void WholeImageForReview::updateImages()
{
	for(int i=0; i<FrontImageList.count(); i++){
		FrontImageList[i]->getDisplay()->updateImage();
	}
	for(int i=0; i<BackImageList.count(); i++){
		BackImageList[i]->getDisplay()->updateImage();
	}
}

void WholeImageForReview::setPropertyToDisplay(WholeDisplay *display, Review::SideType side)
{
	if(display==NULL)return;

	const WholeImageForReviewProperty &pro = getProperty();
	display->getDisplay()->setNGPointView(pro.viewNGPoint);
	display->getDisplay()->setCurrentNGCrossView(pro.viewNGNailCross);
	display->getDisplay()->setCurrentNGRectOnlyView(pro.viewOnlyCurrentNail);
	if(side==Review::Front){
		display->getDisplay()->setRotate(Review::toIntFromRotate(pro.viewFrontRotation));
	}else{
		display->getDisplay()->setRotate(Review::toIntFromRotate(pro.viewBackRotation));
	}
}

void WholeImageForReview::setPropertyToDisplay()
{
	for(int i=0; i<FrontImageList.count(); i++){
		setPropertyToDisplay(FrontImageList[i], Review::Front);
	}
	for(int i=0; i<BackImageList.count(); i++){
		setPropertyToDisplay(BackImageList[i], Review::Back);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------



