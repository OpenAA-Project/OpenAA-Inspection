#include "ButtonToShowTotalNGMapResource.h"
#include "ButtonToShowTotalNGMap.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewCommonPacket.h"



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"ButtonToShowTotalNGMap";


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
	return(/**/"Show total NGs in Map");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ButtonToShowTotalNGMap *form = new ButtonToShowTotalNGMap(Base,parent);
	form->resize(120, 35);
	return form;
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

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonToShowTotalNGMap.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ButtonToShowTotalNGMap
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ButtonToShowTotalNGMap::ButtonToShowTotalNGMap(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent),m_map(Base, GetReviewAlgorithm(), this)
{
	//ui.setupUi(this);
	m_Btn.setParent(this);

	QRect rect = geometry();

	rect.setWidth(m_Btn.geometry().width());
	rect.setHeight(m_Btn.geometry().height());

	setGeometry(rect);

	connect(this, SIGNAL(SignalResize()), SLOT(ResizeAction()));
	connect(&m_map, SIGNAL(resized()), this, SLOT(updateMapImage()));
	
	if(GetEditMode()==false){
		connect(&m_Btn, SIGNAL(clicked()), this, SLOT(clicked()));
		m_Btn.setEnabled(false);
	}

	initProperty();
}

ButtonToShowTotalNGMap::~ButtonToShowTotalNGMap()
{
}
void	ButtonToShowTotalNGMap::Prepare(void)
{
	m_Btn.setText(LangSolver.GetString(ButtonToShowTotalNGMap_LS,LID_1)/*"Show Total NG Map"*/);
}
void ButtonToShowTotalNGMap::updateMapImage()
{
	//ReviewPIBase *RBase = GetReviewAlgorithm();

	//if(RBase!=NULL){
	//	CmdReqMasterImageList reqMImgList(GetLayersBase());
	//	QSize s = m_map.viewAreaSize();

	//	CmdReqWholeImage reqWImg(GetLayersBase());

	//	reqWImg.setReqSize(s);
	//	reqWImg.setReqPhase(0);

	//	RBase->TransmitDirectly(&reqWImg);

	//	int phase = m_map.currentPhase();

	//	m_map.setImage(Review::Front, phase, reqWImg.getWholePic(Review::Front));
	//	m_map.setImage(Review::Back, phase, reqWImg.getWholePic(Review::Back));

	//	CmdReqOrganizedHistoryList NGSend(GetLayersBase());
	//	RBase->TransmitDirectly(&NGSend);
	//	if(NGSend.Ret==true){
	//		m_map.setNGPoints(NGSend.listPtr);// マップを更新
	//	}else{
	//		m_map.clearPointList();
	//	}
	//}
}
void ButtonToShowTotalNGMap::paintEvent(QPaintEvent *event)
{
	if(GetEditMode()==true){
		//QPainter painter(this);

		//QRect dr = rect();

		//dr.setTopLeft(QPoint(1,1));
		//dr.setBottomRight(dr.bottomRight() - QPoint(1,1));

		//painter.drawRect(dr);
	}
}

void ButtonToShowTotalNGMap::TransmitDirectly(GUIDirectMessage *packet){
	ReviewPIBase *RBase = GetReviewAlgorithm();

	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUICmdReviewUpdateLocalVar->Ret = true;
		return;
	}

	//GUICmdUpdateCurrentLot *GUICmdUpdateCurrentLotVar = dynamic_cast<GUICmdUpdateCurrentLot *>(packet);
	//if(GUICmdUpdateCurrentLotVar!=NULL){
	//	// マスターデータ情報取得
	//	CmdReqMasterDataInfo minfo(GetLayersBase());
	//	RBase->TransmitDirectly(&minfo);

	//	// マスターデータの片面両面判定および表示設定
	//	Review::OrganizedSideType side = minfo.sideType();
	//	if(side==Review::OrganizedSideType::None){
	//		ui.cbSide->setEnabled(false);
	//		ui.cbPhase->setEnabled(false);
	//	}else{
	//		ui.cbSide->setEnabled(true);
	//		ui.cbPhase->setEnabled(true);
	//	}
	//	if(side==Review::OrganizedSideType::FrontOnly){
	//		ui.cbSide->setHidden(true);
	//		ui.cbSide->setCurrentIndex(0);	// 表のみの場合は強制的に表側へ設定
	//	}else{
	//		ui.cbSide->setHidden(false);
	//	}

	//	// Phaseの個数を取得、コンボボックスへ設定
	//	MasterDataInfo cminfo;
	//	if(ui.cbSide->currentIndex()==0){
	//		cminfo = minfo.FrontMasterDataInfo;
	//	}else{
	//		cminfo = minfo.BackMasterDataInfo;
	//	}
	//	int oldIndex = ui.cbPhase->currentIndex();
	//	ui.cbPhase->clear();
	//	for(int i=0; i<cminfo.PhaseNumb; i++){
	//		ui.cbPhase->addItem(QString::number(i));
	//	}
	//	if(oldIndex>=ui.cbPhase->count()){
	//		oldIndex = 0;
	//	}
	//	ui.cbPhase->setCurrentIndex(oldIndex);

	//	// 全体画像を取得
	//	CmdReqWholeImage wi(GetLayersBase());
	//	wi.setReqPhase( ui.cbPhase->currentIndex() );
	//	wi.setReqSize(ui.gvImageView->viewport()->size() );

	//	RBase->TransmitDirectly( &wi );

	//	// 表示画像を設定
	//	QImage img;
	//	if(ui.cbSide->currentIndex()==0){
	//		img = wi.getWholePic(Review::Front);
	//	}else{
	//		img = wi.getWholePic(Review::Back);
	//	}
	//	ui.gvImageView->setImage(img);
	//}

	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		//CmdReqSettingPropertyDialogVar->dialog = getPropertyDialog();
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Global);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ButtonToShowTotalNGMap);
		return;
	}
}

void ButtonToShowTotalNGMap::updateGUI()
{
	GUIFormBase::update();

	// ReviewStructureへのアクセスポインタ取得
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		m_map.setUpdatesEnabled(false);
		
		//// NG箇所のデータ更新
		//CmdReqOrganizedHistoryList NGSend(GetLayersBase());// 履歴リストのアクセスポインタを要求
		//RBase->TransmitDirectly(&NGSend);
		//if(NGSend.Ret==true){// 取得成功
		//	m_map.setNGPoints(NGSend.listPtr);// マップを更新
		//}else{
		//	m_map.clearPointList();
		//}

		//// マスター画像情報を取得
		//CmdReqWholeImageInfo reqWholeInfoCmd(GetLayersBase());
		//RBase->TransmitDirectly(&reqWholeInfoCmd);

		//// マスター画像を取得
		//CmdReqMasterDataInfo reqMasterDataInfoCmd(GetLayersBase());
		//RBase->TransmitDirectly(&reqMasterDataInfoCmd);

		//CmdReqWholeImage img(GetLayersBase());
		//QList<QImage> FrontImageList,BackImageList;
		//for(int phase=0; phase<reqMasterDataInfoCmd.getInfo(Review::Front).PhaseNumb; phase++){
		//	// 全体画像の更新
		//	img.setReqSize(reqWholeInfoCmd.getWholeOriginalSize(Review::Front, phase));
		//	img.setReqPhase(phase);
		//	RBase->TransmitDirectly(&img);
		//	FrontImageList << img.getWholePic(Review::Front);
		//}
		//for(int phase=0; phase<reqMasterDataInfoCmd.getInfo(Review::Back).PhaseNumb; phase++){
		//	// 全体画像の更新
		//	img.setReqSize(reqWholeInfoCmd.getWholeOriginalSize(Review::Back, phase));
		//	img.setReqPhase(phase);
		//	RBase->TransmitDirectly(&img);
		//	BackImageList << img.getWholePic(Review::Back);
		//}

		//m_map.setImage(FrontImageList, BackImageList);

		CmdReqMasterDataInfo minfo(GetLayersBase());
		RBase->TransmitDirectly(&minfo);

		if(minfo.FrontMasterDataInfo.isEmpty()==false){
			m_Btn.setEnabled( true );// 使用可ならボタンを有効化
			m_map.setUpdatesEnabled(true);
		}else{
			m_Btn.setEnabled( false );
			m_map.setUpdatesEnabled(false);
		}
	}
}

void ButtonToShowTotalNGMap::ResizeAction()
{
	int w,h;
	int min_w = 138;
	int min_h = 23;

	if(width()<min_w){
		resize(min_w, height());
	}else{
		w = width();
	}

	if(height()<min_h){
		resize(width(), min_h);
	}
	else{
		h = height();
	}
	m_Btn.resize(width(), height());
}

