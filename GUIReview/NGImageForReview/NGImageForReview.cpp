#include "NGImageForReviewResource.h"
#include "NGImageForReview.h"
#include "NGImageForReviewPacket.h"
#include "ReviewStructurePacket.h"
#include "XReviewCommonPacket.h"
#include "XReviewStructure.h"
#include "../XGUIReviewGlobal.h"
#include "NGImageForReviewProperty.h"

char	*sRoot=/**/"Review";
char	*sName=/**/"NGImageForReview";



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
	return(/**/"Show NG Image for Review");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new NGImageForReview(Base,parent));
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
	if(maxDataDim<0)
		return(-1);
	Data[0].Type = /**/"int32";
	Data[0].VariableNameWithRoute=/**/"HorizontalVirtical";
	Data[0].Pointer				 =&((NGImageForReview *)Instance)->reqOrientation;
	Data[1].Type = /**/"bool";
	Data[1].VariableNameWithRoute=/**/"MasterImageView";
	Data[1].Pointer				 =&((NGImageForReview *)Instance)->isMasterView;
	Data[2].Type = /**/"bool";
	Data[2].VariableNameWithRoute=/**/"NGImageView";
	Data[2].Pointer				 =&((NGImageForReview *)Instance)->isNGImageView;
	return(3);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	RootNameList *item = new RootNameList(/**/"Review", /**/"ReviewStructure");
	List.AppendList(item);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/NGImageForReview.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NGImageForReview
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NGImageForReview::NGImageForReview(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),viewType(Qt::Vertical),vLayout(NULL),hLayout(NULL),mainLayout(new QGridLayout),MasterPImage(),NGNailImage(),reqOrientation(0)
	,isMasterView(true),isNGImageView(true)
{
	connect(this, SIGNAL(SignalResize()), SLOT(ResizeAction()));
	LangSolver.SetUI(this);

	setLayout(mainLayout);

	MasterLabel.setText(LangSolver.GetString(NGImageForReview_LS,LID_0)/*"Master Piece"*/);
	NGNailLabel.setText(LangSolver.GetString(NGImageForReview_LS,LID_1)/*"NG Image"*/);

	MasterLabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	NGNailLabel.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	MasterLabel.setFrameStyle(QFrame::Shape::Box | QFrame::Shadow::Plain);
	NGNailLabel.setFrameStyle(QFrame::Shape::Box | QFrame::Shadow::Plain);

	MasterLabel.setAlignment(Qt::AlignCenter);
	NGNailLabel.setAlignment(Qt::AlignCenter);
	
	DefaultMasterLabelWindowColor = MasterLabel.palette().color(QPalette::ColorRole::Window);
	DefaultNGNailLabelWindowColor = NGNailLabel.palette().color(QPalette::ColorRole::Window);

	// 初期状態は横並び
	setOrientation(Qt::Horizontal);

	if(GetEditMode()==true){
		QImage image(30, 60, QImage::Format_RGB32);
		image.fill(palette().window().color().rgb());
		MasterPImage.setImage(image);
		NGNailImage.setImage(image);
	}else{
		connect(&MasterPImage, SIGNAL(SignalImageStateChanged(int,int,int)), &NGNailImage, SLOT(SlotSetImageState(int,int,int)));
		connect(&NGNailImage, SIGNAL(SignalImageStateChanged(int,int,int)), &MasterPImage, SLOT(SlotSetImageState(int,int,int)));
	}

	setMinimumSize(100, 70);

	initProperty();
	SetKeyGrab(false);
}

NGImageForReview::~NGImageForReview()
{
	// レイアウトだけ削除では全部消えているかわからないので、手動で順番に全部削除
	//delete FrontMasterImage;
	//delete BackMasterImage;
	//delete NGNailImage;
	delete mainLayout;
}

void NGImageForReview::ResizeAction()
{
}

void NGImageForReview::checkOrientation()
{
	if((reqOrientation&1)==0){
		viewType = Qt::Vertical;
		setOrientation(Qt::Horizontal);
		viewType = Qt::Horizontal;
	}else{
		viewType = Qt::Horizontal;
		setOrientation(Qt::Vertical);
		viewType = Qt::Vertical;
	}
}

void NGImageForReview::Prepare()
{
	checkOrientation();
	MasterLabel.setVisible(isMasterView);
	MasterPImage.setVisible(isMasterView);
	NGNailLabel.setVisible(isNGImageView);
	NGNailImage.setVisible(isNGImageView);
}

// 画像の伸縮・マスター画像の拡大率調整
void NGImageForReview::adjustImageSize(void)
{
	mainLayout->setGeometry(rect());
}

void NGImageForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	// NG画像の取得要求
	GUICmdReqSetNGImage *GUICmdReqSetNGImageVar = dynamic_cast<GUICmdReqSetNGImage *>(packet);
	if(GUICmdReqSetNGImageVar!=NULL){
		// NG画像なし(クリア)
		if(GUICmdReqSetNGImageVar->NGNailPtr==NULL){
			NGNailImage.setImage(QImage());
			NGNailImage.setNGPoints(QList<ReviewNGPoint>());
			MasterPImage.setImage(QImage());
			GUICmdReqSetNGImageVar->Ret = true;
			return;
		}
		NGNailImage.setNGPoints(GUICmdReqSetNGImageVar->NGNailPtr->NGPointList);

		Review::Rotate rotate = getProperty().rotate;

		QRect rect(GUICmdReqSetNGImageVar->NGNailPtr->MasterPosX, GUICmdReqSetNGImageVar->NGNailPtr->MasterPosY, GUICmdReqSetNGImageVar->NGNailPtr->NGImageWidth, GUICmdReqSetNGImageVar->NGNailPtr->NGImageHeight);

		Review::rotateRectRoundCneter(rect, Review::toIntFromRotate(rotate));

		CmdReqMasterImagePiece ReqMPiece(GetLayersBase());// = CmdReqMasterImagePiece::fromNGNailItem(GetLayersBase(), GUICmdReqSetNGImageVar->side, *GUICmdReqSetNGImageVar->NGNailPtr);
		ReqMPiece.side = GUICmdReqSetNGImageVar->side;
		ReqMPiece.phase = GUICmdReqSetNGImageVar->NGNailPtr->phase;
		ReqMPiece.page = GUICmdReqSetNGImageVar->NGNailPtr->page;
		ReqMPiece.MasterX = rect.left();
		ReqMPiece.MasterY = rect.top();
		ReqMPiece.Width = rect.width();
		ReqMPiece.Height = rect.height();

		ReviewPIBase *RBase = GetReviewAlgorithm();
		RBase->TransmitDirectly(&ReqMPiece);
		
		QImage ngImage;
		bool noNGImage = false;
		if(GUICmdReqSetNGImageVar->NGNailPtr->image().isNull()==false){
			ngImage = GUICmdReqSetNGImageVar->NGNailPtr->image().transformed(QTransform().rotate(Review::toIntFromRotate(rotate)));
			NGNailImage.setImage(ngImage);
		}else{
			noNGImage = true;
			NGNailImage.setImage(ReqMPiece.image);
		}

		if(ReqMPiece.Ret==true){
			MasterPImage.setImage(ReqMPiece.image);
		}else{
			MasterPImage.setImage(ngImage);
		}
		GUICmdReqSetNGImageVar->Ret = true;

		if(noNGImage==true){
			QMessageBox::warning(this, LangSolver.GetString(NGImageForReview_LS,LID_2)/*"No NG Image"*/, LangSolver.GetString(NGImageForReview_LS,LID_3)/*"NG image was not loaded.\nIt maybe not found folder or not exist the file."*/);
		}

		return;
	}

	GUICmdExchangeNGVisible *GUICmdExchangeNGVisibleVar = dynamic_cast<GUICmdExchangeNGVisible *>(packet);
	if(GUICmdExchangeNGVisibleVar!=NULL){
		NGNailImage.exhangeNGVisible();
		return;
	}

	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		//CmdReqSettingPropertyDialogVar->dialog = getPropertyDialog();
		//CmdReqSettingPropertyDialogVar->setDialog(NULL);
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Standard);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::NGImageForReview);
		return;
	}
}

void NGImageForReview::setOrientation(Qt::Orientation orient)
{
	if(mainLayout->indexOf(&MasterLabel)==-1){
		mainLayout->addWidget(&MasterLabel, 0, 0);
		mainLayout->addWidget(&MasterPImage, 1, 0);
		if(orient==Qt::Horizontal){
			// 横並び
			mainLayout->addWidget(&NGNailLabel, 0, 1);
			mainLayout->addWidget(&NGNailImage, 1, 1);
		}else{
			// 縦並び
			mainLayout->addWidget(&NGNailLabel, 2, 0);
			mainLayout->addWidget(&NGNailImage, 3, 0);
		}

		MasterPImage.setVisible(true);
		NGNailImage.setVisible(true);

		viewType = orient;
		return;
	}
	// 配置が現在と違う場合に実行
	if(viewType!=orient){
		// レイアウトにNG画像がある場合、レイアウトから除外する
		int NGIndex = mainLayout->indexOf(&NGNailImage);
		if(NGIndex!=-1){// 
			mainLayout->removeWidget(&NGNailLabel);
			mainLayout->removeWidget(&NGNailImage);
		}
		if(orient==Qt::Horizontal){
			// 横並び
			mainLayout->addWidget(&NGNailLabel, 0, 1);
			mainLayout->addWidget(&NGNailImage, 1, 1);
		}else{
			// 縦並び
			mainLayout->addWidget(&NGNailLabel, 2, 0);
			mainLayout->addWidget(&NGNailImage, 3, 0);
		}
		viewType = orient;
	}
}

void NGImageForReview::updateGUI()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	
	CmdReqAdjacentCurrentNG RoundCurrentNG(GetLayersBase());
	RBase->TransmitDirectly(&RoundCurrentNG);

	const NGNailIndex NGNailPtr = RoundCurrentNG.currentNG();

	QString NGImageLabelText;
	QString MasterImageLabelText;
	QColor NGImageLabelColor = DefaultNGNailLabelWindowColor;
	QColor MasterImageLabelColor = DefaultMasterLabelWindowColor;

	if(NGNailPtr!=NULL){// 現在NGがある
		if(RoundCurrentNG.Ret==false){
			NGNailImage.setNGSingColor(Qt::white);
			NGNailImage.setImage(QImage());
			NGNailImage.setNGPoints(QList<ReviewNGPoint>());
			NGNailImage.setTopLeftPos(0, 0);

			MasterPImage.setImage(QImage());
			MasterPImage.setTopLeftPos(0, 0);

			NGImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_4)/*"NG Image - No Data"*/;
			MasterImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_5)/*"Master Piece - No Data"*/;
		}else{// 通常処理
			CmdReqWholeImageInfo ReqWInfoCmd(GetLayersBase());
			RBase->TransmitDirectly( &ReqWInfoCmd );

			QPoint addOffset;
			if(RoundCurrentNG.currentSide()==Review::Front){
				addOffset = ReqWInfoCmd.FrontOutlineOffset[NGNailPtr->phase][NGNailPtr->page];
			}else{
				addOffset = ReqWInfoCmd.BackOutlineOffset[NGNailPtr->phase][NGNailPtr->page];
			}
			ReviewNGPointList list;
			QPoint NailOffset;
			for(int i=0; i<NGNailPtr->NGPointList.count(); i++){
				const ReviewNGPoint &cp = NGNailPtr->NGPointList[i];
				ReviewNGPoint p = cp;
				p.x += addOffset.x();
				p.y += addOffset.y();
				NailOffset += QPoint(cp.AlignedX + cp.ItemSearchedX, cp.AlignedY + cp.ItemSearchedY);
				list.append(p);
			}

			if(NGNailPtr->NGPointList.isEmpty()==false){
				NailOffset /= NGNailPtr->NGPointList.count();
			}

			//QPoint imageCenter(NGNailPtr->MasterPosX + NGNailPtr->NGImageWidth/2, NGNailPtr->MasterPosY + NGNailPtr->NGImageHeight/2);
			//for(int i=0; i<list.count(); i++){
			//	QPoint pos = Review::rotatePoint(QPoint(list[i].x, list[i].y), Review::toIntFromRotate(getProperty().rotate), imageCenter);
			//	list[i].x = pos.x();
			//	list[i].y = pos.y();
			//}
			NGNailImage.setNGPoints(list);
			//QPoint topleftWithOutline(NGNailPtr->TargetPosX + addOffset.x(), NGNailPtr->TargetPosY + addOffset.y());
			//QPoint topleft(NGNailPtr->TargetPosX, NGNailPtr->TargetPosY);
			//topleft = Review::rotatePoint(topleft, Review::toIntFromRotate(getProperty().rotate), imageCenter);
			NGNailImage.setTopLeftPos(NGNailPtr->TargetPosX + addOffset.x(), NGNailPtr->TargetPosY + addOffset.y());

			//QRect rect(topleft, QSize(Review::rotateSize(QSize(NGNailPtr->NGImageWidth, NGNailPtr->NGImageHeight), Review::toIntFromRotate(getProperty().rotate))));
			//
			//CmdReqMasterImagePiece ReqMPiece(GetLayersBase());// = CmdReqMasterImagePiece::fromNGNailItem(GetLayersBase(), GUICmdReqSetNGImageVar->side, *GUICmdReqSetNGImageVar->NGNailPtr);
			//ReqMPiece.side = RoundCurrentNG.currentSide;
			//ReqMPiece.phase = NGNailPtr->phase;
			//ReqMPiece.page = NGNailPtr->page;
			//ReqMPiece.MasterX = rect.left();
			//ReqMPiece.MasterY = rect.top();
			//ReqMPiece.Width = rect.width();
			//ReqMPiece.Height = rect.height();

			CmdReqMasterImagePiece ReqMPiece = CmdReqMasterImagePiece::fromNGNailItem(GetLayersBase(), RoundCurrentNG.currentSide(), *NGNailPtr);
			//ReqMPiece.side = RoundCurrentNG.currentSide;
			//ReqMPiece.phase = NGNailPtr->phase;
			//ReqMPiece.page = NGNailPtr->page;
			//ReqMPiece.MasterX = NGNailPtr->MasterPosX + addOffset.x();
			//ReqMPiece.MasterY = NGNailPtr->MasterPosY + addOffset.y();
			//ReqMPiece.Width = NGNailPtr->NGImageWidth;
			//ReqMPiece.Height = NGNailPtr->NGImageHeight;

			ReqMPiece.MasterX -= NailOffset.x();
			ReqMPiece.MasterY -= NailOffset.y();

			RBase->TransmitDirectly(&ReqMPiece);

			if(NGNailPtr->image().isNull()==false){
				NGNailImage.setNGSingColor(Qt::red);

				QImage image = NGNailPtr->image().transformed(QTransform().rotate(Review::toIntFromRotate(getProperty().rotate)));
				NGNailImage.setImage(image,Review::toIntFromRotate(getProperty().rotate));
				NGImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_6)/*"NG Image"*/;
			}else{
				NGNailImage.setNGSingColor(Qt::blue);
				if(getProperty().BlankImageOnCopyMaster==false){
					NGNailImage.setImage(ReqMPiece.image);
				}
				else{
					NGNailImage.Clear(0);
				}
				NGImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_7)/*"NG Image - CopyMaster"*/;
				NGImageLabelColor = QColor(255, 70, 70);
			}

			if(ReqMPiece.Ret==true){
				MasterPImage.setImage(ReqMPiece.image.transformed(QTransform().rotate(Review::toIntFromRotate(getProperty().rotate))));
				MasterPImage.setTopLeftPos(NGNailPtr->MasterPosX + addOffset.x(), NGNailPtr->MasterPosY + addOffset.y());
				MasterImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_8)/*"Master Piece"*/;
			}else{
				if(NGNailPtr->image().isNull()==false){
					MasterPImage.setImage(QImage());
					MasterPImage.setTopLeftPos(0, 0);
					MasterImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_9)/*"Master Piece - No Data"*/;
				}else{
					QImage image = NGNailPtr->image().transformed(QTransform().rotate(Review::toIntFromRotate(getProperty().rotate)));
					if(getProperty().BlankImageOnCopyMaster==false){
						MasterPImage.setImage(image);
					}
					else{
						MasterPImage.Clear(0);
					}
					MasterPImage.setTopLeftPos(NGNailPtr->MasterPosX + addOffset.x(), NGNailPtr->MasterPosY + addOffset.y());
					MasterImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_10)/*"Master Piece - CopyNGImage"*/;
					MasterImageLabelColor = QColor(60, 60, 200);
				}
			}
		}
	}else{// 現在NGがない
		NGNailImage.setNGSingColor(Qt::white);
		NGNailImage.setImage(QImage());
		NGNailImage.setNGPoints(QList<ReviewNGPoint>());
		NGNailImage.setTopLeftPos(0, 0);

		MasterPImage.setImage(QImage());
		MasterPImage.setTopLeftPos(0, 0);

		NGImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_11)/*"NG Image - No Data"*/;
		MasterImageLabelText = LangSolver.GetString(NGImageForReview_LS,LID_12)/*"Master - No Data"*/;
	}
	QPalette pale;
	
	NGNailLabel.setText(NGImageLabelText);
	NGNailLabel.setAutoFillBackground(true);
	pale = NGNailLabel.palette();
	pale.setColor(QPalette::ColorRole::Window, NGImageLabelColor);
	NGNailLabel.setPalette(pale);

	MasterLabel.setText(MasterImageLabelText);
	MasterLabel.setAutoFillBackground(true);
	pale = MasterLabel.palette();
	pale.setColor(QPalette::ColorRole::Window, MasterImageLabelColor);
	MasterLabel.setPalette(pale);
}
