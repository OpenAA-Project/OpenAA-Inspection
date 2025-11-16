#include "ShowThumbnailResource.h"
#include "ShowThumbnail.h"
#include "ReviewStructureItems.h"
#include "ReviewStructurePacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "../XGUIReviewCommonPacket.h"
#include "XReviewCommonPacket.h"
#include "../XGUIReviewGlobal.h"
#include "../ShowHistoryListForReview/ShowHistoryListForReviewPacket.h"
#include "../WholeImageForReview/WholeImageForReviewPacket.h"
#include "SettingDialog.h"
#include "ShowThumbnailProperty.h"
#include "ChooseNextDialog.h"
#include "SWAP.h"
#include <QColorDialog>


char	*sRoot=/**/"Review";
char	*sName=/**/"ShowThumbnail";


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
	return(/**/"Show Thumbnail");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowThumbnail(Base,parent));
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

	Data[0].Type = /**/"bool";
	Data[0].VariableNameWithRoute=/**/"SkipSamePiece";
	Data[0].Pointer	=&((ShowThumbnail *)Instance)->SkipSamePiece;	//int32 rowCount;
	//int32 columnCount;
	//int32 NGSignSize;
	//int32 viewMaster;
	//int32 delayMSec;
	//int32 moveMode;
	
	//Data[0].Type = /**/"int32";
	//Data[0].VariableNameWithRoute=/**/"RowCount";
	//Data[0].Pointer				 =&((ShowThumbnail *)Instance)->reqData.rowCount;
	//Data[1].Type = /**/"int32";
	//Data[1].VariableNameWithRoute=/**/"ColumnCount";
	//Data[1].Pointer				 =&((ShowThumbnail *)Instance)->reqData.columnCount;
	//Data[2].Type = /**/"int32";
	//Data[2].VariableNameWithRoute=/**/"NGRoundSize";
	//Data[2].Pointer				 =&((ShowThumbnail *)Instance)->reqData.NGSignSize;
	//Data[3].Type = /**/"int32";
	//Data[3].VariableNameWithRoute=/**/"MasterView";
	//Data[3].Pointer				 =&((ShowThumbnail *)Instance)->reqData.viewMaster;
	//Data[4].Type = /**/"int32";
	//Data[4].VariableNameWithRoute=/**/"DelayMiliSecForNextCheck";
	//Data[4].Pointer				 =&((ShowThumbnail *)Instance)->reqData.delayMSec;
	//Data[5].Type = /**/"int32";
	//Data[5].VariableNameWithRoute=/**/"InitialMoveMode";
	//Data[5].Pointer				 =&((ShowThumbnail *)Instance)->reqData.moveMode;
	//Data[6].Type = /**/"bool";
	//Data[6].Pointer				 =&((ShowThumbnail *)Instance)->reqData.enableExpandDialog;
	//Data[6].VariableNameWithRoute=/**/"ExpandDialogEnable";

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowThumbnail.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ShowThumbnail
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShowThumbnail::ShowThumbnail(LayersBase *Base,QWidget *parent)
	:GUIFormBase(Base, parent)
	,m_ThumbnailBook(new QStackedWidget)
	,m_ExpandDialog(new ExpandThumbnailDialog(this))
	,m_InfoLabel(new QLabel)
	,m_mainLayout(new QVBoxLayout(this))
	,m_settingDialog(NULL)
	,m_contextMenu(new QMenu(this))
	,m_controlInfoDialog(new ControlInfoDialog(this))
	,m_pageWaitTimeLine(new QTimeLine(1000, this))
	,m_pageWaitProgressBar(new QProgressBar)
	,m_drawNGSingEnable(true)
	,LabelInfo(new QLabel(this))
{
	// プロパティ設定ダイアログの初期化
	initProperty();
	LangSolver.SetUI(this);

	//layoutWidget = new QWidget(this);
	//mainLayout = new QGridLayout(layoutWidget);
	setCurrentPage(-1);
	setCurrentColumn(-1);
	setCurrentRow(-1);
	setExpandThumbnail(NULL);
	setCurrentEID(-1);
	SkipSamePiece		=true;

	m_ExpandDialog->Initial();
	
	setExpandThumbnailVisible( false );

	QPalette palette;
	QBrush brush(QColor(255, 255, 255, 255));
	brush.setStyle(Qt::SolidPattern);
	palette.setBrush(QPalette::Active, QPalette::Base, brush);
	palette.setBrush(QPalette::Active, QPalette::Window, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
	palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
	palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
	infoLabel()->setPalette(palette);
	infoLabel()->setAutoFillBackground(true);
	infoLabel()->setFrameShape(QFrame::Box);
	infoLabel()->setAlignment(Qt::AlignCenter);
	QFont font = infoLabel()->font();
	font.setPointSize(14);
	infoLabel()->setFont(font);

	//HelpLabel->setPalette(palette);
	//HelpLabel->setAutoFillBackground(true);
	//HelpLabel->setFrameShape(QFrame::Box);
	//HelpLabel->setAlignment(Qt::AlignCenter);

	pageWaitProgressBar()->setFormat(/**/"PageCheckWaitTime");
	pageWaitProgressBar()->setTextVisible(true);
	pageWaitProgressBar()->setRange(0, 100);
	pageWaitProgressBar()->setValue(100);
	pageWaitTimeLine()->setFrameRange(0, 100);

	LabelInfo->setParent(this);
	LabelInfo->setGeometry(0,0,200,40);
	LabelInfo->setText(/**/"XXXXXXXX");

	mainLayout()->addWidget(infoLabel(), 0, Qt::AlignTop);
	mainLayout()->addWidget(thumbnailBook());
	//mainLayout->addWidget(HelpLabel, 0, Qt::AlignBottom);
	mainLayout()->addWidget(pageWaitProgressBar(), 0, Qt::AlignBottom);
	mainLayout()->addWidget(LabelInfo, 0, Qt::AlignBottom);

	//reqData.rowCount = 3;
	//reqData.columnCount = 5;
	//reqData.NGSignSize = 10;
	//reqData.delayMSec = 150;
	//reqData.viewMaster = 0;
	//reqData.moveMode = 0;
	//reqData.enableExpandDialog = true;

	//setRowCount(reqData.rowCount);
	//setColumnCount(reqData.columnCount);
	//setNGSignSize(reqData.NGSignSize);
	//setMoveDelay(reqData.delayMSec);
	//setViewMaster(true);
	//setMoveMode(_moveMode::PerPage);
	setKeyPressedState(false);

	setSettingDialog(new SettingDialog(getRowCount(), getColumnCount(), getNGSignSize(), this));


	setMinimumSize(200, 200);
}

void ShowThumbnail::Prepare()
{
	//checkData();
	m_settingAction		=new QAction(LangSolver.GetString(ShowThumbnail_LS,LID_31)/*"Setting"*/, this);	//,HelpLabel(new QLabel)
	m_controlInfoAction	=new QAction(LangSolver.GetString(ShowThumbnail_LS,LID_32)/*"Control Info"*/, this);

	if(GetEditMode()==false){
		connect(pageWaitTimeLine(), SIGNAL(frameChanged(int)), pageWaitProgressBar(), SLOT(setValue(int)));
		connect(settingDialog(), SIGNAL(valueChanged(int,int)), this, SLOT(changedRowColumnCount(int,int)));
		connect(settingDialog(), SIGNAL(valueChanged(int)), this, SLOT(changedNGSignSize(int)));
		connect(settingDialog(), SIGNAL(changeCheckedMasterVisible(int)), this, SLOT(slotSetMasterVisible(int)));
		connect(settingDialog(), SIGNAL(sortOrderChanged(int)), this, SLOT(slotSortOrderChanged(int)));
		
		QString	s1=LangSolver.GetString(ShowThumbnail_LS,LID_5)/*"set view of thumbnail GUI"*/;
		settingAction()->setStatusTip(s1);
		connect(settingAction(), SIGNAL(triggered()), this, SLOT(showSettingDialog()));

		contextMenu()->addAction(settingAction());

		controlInfoDialog()->append(/**/"Ctrl Key", LangSolver.GetString(ShowThumbnail_LS,LID_6)/*"swap mode(PerPage <-> PerThumbnail)"*/);
		controlInfoDialog()->append(/**/"Arrow Key", LangSolver.GetString(ShowThumbnail_LS,LID_7)/*"move thumbnail(PerThumbnail) or move page(PerPage)"*/);
		controlInfoDialog()->append(/**/"Enter or Retrun Key", LangSolver.GetString(ShowThumbnail_LS,LID_8)/*"show ExpandThumbnail if it's enable(PerThumbnail), set check all on Page after time elapsed enough(PerPage)"*/);
		controlInfoDialog()->append(/**/"F1-12", LangSolver.GetString(ShowThumbnail_LS,LID_9)/*"set F Key type to current thumbnail(PerThumbnail)"*/);

		controlInfoAction()->setStatusTip(LangSolver.GetString(ShowThumbnail_LS,LID_10)/*"show control list"*/);
		connect(controlInfoAction(), SIGNAL(triggered()), controlInfoDialog(), SLOT(show()));

		contextMenu()->addAction(controlInfoAction());
	}else{
		createEditerThumbnail();
	}
}

void ShowThumbnail::setRowCount(int size){ getProperty().RowCount = size; };
void ShowThumbnail::setColumnCount(int size){ getProperty().ColumnCount = size; };
void ShowThumbnail::setNGSignSize(int size){ getProperty().NGSignSize = size; };
void ShowThumbnail::setViewMaster(bool view){ getProperty().MasterPieceImageView = view; };
void ShowThumbnail::setCurrentSide(Review::SideType side){ m_currentSide = side; };
void ShowThumbnail::setCurrentPage(int page){ m_currentPage = page; };
void ShowThumbnail::setCurrentRow(int row){ m_currentRow = row; };
void ShowThumbnail::setCurrentColumn(int column){ m_currentColumn = column; };
void ShowThumbnail::setCurrentThumbnail(Thumbnail *thumbnail){ m_currentThumbnail = thumbnail; };
void ShowThumbnail::setMoveMode(_moveMode mode){ m_moveMode = mode; };
void ShowThumbnail::setExpandThumbnail(Thumbnail *thumbnail){ m_ExpandDialog->setThumbnail(thumbnail); };
void ShowThumbnail::setExpandThumbnailVisible(bool v){ m_ExpandDialog->setVisible(v); };
void ShowThumbnail::setMoveDelay(int miliSec){ m_delayMSec = miliSec; };
void ShowThumbnail::setKeyPressedState(bool pressed){ m_keyPressed = pressed; };
void ShowThumbnail::setEnableExpandThumbnal	(bool enable){ getProperty().ExpandThumbnailEnable	= enable; };
void ShowThumbnail::setModeShowPageByPiece	(bool enable){ getProperty().ModeShowPageByPiece	= enable; };
void ShowThumbnail::setFKeyList(const QList<QColor> &list){ getProperty().FKeyColorList = list; };
void ShowThumbnail::setCurrentEID(int id){ m_currentEID = id; };

int ShowThumbnail::getRowCount() const { return  (m_property==NULL)?1:getProperty().RowCount; };
int ShowThumbnail::getColumnCount() const { return  (m_property==NULL)?1:getProperty().ColumnCount; };
int ShowThumbnail::getNGSignSize() const { return  (m_property==NULL)?10:getProperty().NGSignSize; };
bool ShowThumbnail::isViewMaster() const { return (m_property==NULL)?false:getProperty().MasterPieceImageView; };
Review::SideType ShowThumbnail::getCurrentSide() const { return m_currentSide; };
int ShowThumbnail::getCurrentPage() const { return m_currentPage; };
int ShowThumbnail::getCurrentRow() const { return m_currentRow; };
int ShowThumbnail::getCurrentColumn() const { return m_currentColumn; };
Thumbnail *ShowThumbnail::getCurrentThumbnail() const { return m_currentThumbnail; };
int ShowThumbnail::getThumbnailCount(Review::SideType side) const { return (side==Review::Front) ? m_FrontThumbnailList.count() : m_BackThumbnailList.count(); };
int ShowThumbnail::getThumbnailCountAll() const { return m_FrontThumbnailList.count() + m_BackThumbnailList.count(); };
int ShowThumbnail::getCurrentThumbnailCount() const { return getThumbnailCount(getCurrentSide()); };
int ShowThumbnail::getCurrentThumbnailTotalNumb() const { return m_FrontThumbnailList.count() + m_BackThumbnailList.count(); };
ShowThumbnail::_moveMode	ShowThumbnail::getMoveMode() const { return m_moveMode; };
int ShowThumbnail::getThumbnailCountInPage() const { return getRowCount() * getColumnCount(); };
Thumbnail *ShowThumbnail::getExpandThumbnail() const { return m_ExpandDialog->getThumbnail(); };
bool ShowThumbnail::getExpandThumbnailVisible() const { return m_ExpandDialog->isVisible(); };
bool ShowThumbnail::isEnableExpandThumbnal() const { return  (m_property==NULL)?false:getProperty().ExpandThumbnailEnable; };
bool ShowThumbnail::isModeShowPageByPiece () const { return  (m_property==NULL)?false:getProperty().ModeShowPageByPiece; };
int ShowThumbnail::getCurrentEID() const { return m_currentEID; };
	
ThumbnailList &ShowThumbnail::getThumbnailList(Review::SideType side){ return ((side==Review::Front) ? m_FrontThumbnailList : m_BackThumbnailList); };
const ThumbnailList &ShowThumbnail::getThumbnailList(Review::SideType side) const { return ((side==Review::Front) ? m_FrontThumbnailList : m_BackThumbnailList); };

ThumbnailPageList &ShowThumbnail::getThumbnailPageList(Review::SideType side){ return ((side==Review::Front) ? m_FrontThumbnailPageList : m_BackThumbnailPageList); };
const ThumbnailPageList &ShowThumbnail::getThumbnailPageList(Review::SideType side) const { return ((side==Review::Front) ? m_FrontThumbnailPageList : m_BackThumbnailPageList); };

ThumbnailList &ShowThumbnail::getCurrentThumbnailList(){ return getThumbnailList(getCurrentSide()); };
const ThumbnailList &ShowThumbnail::getCurrentThumbnailList() const { return getThumbnailList(getCurrentSide()); };

ThumbnailPageList &ShowThumbnail::getCurrentThumbnailPageList(){ return getThumbnailPageList(getCurrentSide()); };
const ThumbnailPageList &ShowThumbnail::getCurrentThumbnailPageList() const { return getThumbnailPageList(getCurrentSide()); };

int ShowThumbnail::getCurrentPageCount(){ return getPageCount(getCurrentSide()); };
int ShowThumbnail::getCurrentPageLastIndex(){ return getCurrentPageCount()-1; };
int ShowThumbnail::getCurrentThumbnailCountInLastPage(){ int lastcount = (getCurrentThumbnailList().count() % (getRowCount() * getColumnCount())); return (lastcount==0 ? getRowCount() * getColumnCount() : lastcount); };
int ShowThumbnail::getLastRow(Review::SideType side){ return ((getThumbnailCount(side)-1) / getColumnCount()) % getRowCount(); };
int ShowThumbnail::getLastColumn(Review::SideType side){ return getColumnCount() - (((getPageCount(getCurrentSide()) * getRowCount() * getColumnCount()) - getThumbnailCount(side)) % getColumnCount()); };
int ShowThumbnail::getCurrentLastRow(){ return getLastRow(getCurrentSide()); };
int ShowThumbnail::getCurrentLastColumn(){ return getLastColumn(getCurrentSide()); };
int ShowThumbnail::getCurrentThumbnailLastGlobalIndex(){ return getCurrentThumbnailTotalNumb()-1; };

int ShowThumbnail::getPageCount(Review::SideType side)
{ 
	return getThumbnailPageList(side).count();
	//return (getThumbnailList(side).size() / (getRowCount() * getColumnCount()) + ((getThumbnailList(side).size() % (getRowCount() * getColumnCount())!=0) ? 1 : 0));
}


int ShowThumbnail::getMoveDelay(){
	if(getCurrentThumbnail()==NULL){
		return m_delayMSec;
	}
	if(GetEditMode()==true){
		return m_delayMSec;
	}

	int AnyDataLibWait=-1;// AnyDataInLibraryによるウェイトタイム設定値の取得]

	if(getMoveMode()==_moveMode::PerPage){// ページモード
		int priority = -1;// 現在優先度
		for(int k=0;k<getThumbnailPageList(getCurrentSide())[getCurrentPage()].count();k++){
			Thumbnail *Thm=getThumbnailPageList(getCurrentSide())[getCurrentPage()][k];
			const ReviewNGPointList list = Thm->getNGNailItem().NGPointList;
			for(int i=0; i<list.count(); i++){
				if(list[i].Tag.TCode!=-1 && list[i].LibCode!=-1 && list[i].Tag.NGPriority){//LCとTCが適当で優先度が高い場合
					AnyDataLibWait = list[i].Tag.Wait;
					priority = list[i].Tag.NGPriority;
				}
			}
		}
	}else{// サムネイルモード
		int priority = -1;// 現在優先度
		const ReviewNGPointList list = getCurrentThumbnail()->getNGNailItem().NGPointList;
		for(int i=0; i<list.count(); i++){
			if(list[i].Tag.TCode!=-1 && list[i].LibCode!=-1 && list[i].Tag.NGPriority){//LCとTCが適当で優先度が高い場合
				AnyDataLibWait = list[i].Tag.Wait;
				priority = list[i].Tag.NGPriority;
			}
		}
	}

	if(AnyDataLibWait==-1){
		return m_delayMSec;// デフォルト
	}else{
		return AnyDataLibWait;
	}
};
int ShowThumbnail::getPageDelay(const ThumbnailPage *pageWidget)
{
	if(pageWidget!=NULL){
		int sumDelay = 0;
		int defDelay = getMoveDelay();// プロパティ設定によるデフォルトの待機時間
		for(int i=0; i<pageWidget->count(); i++){// 各サムネイルでの待機時間の総和を取る
			if(pageWidget->item(i)!=NULL){
				int addDelay = defDelay;// サムネイルの基本待機時間
				int nowPriority = INT_MAX;// 優先度
				if(pageWidget->item(i)->isChecked()==true){// チェック済みなら待機時間なし
					addDelay = 0;
				}else{// 未チェックのサムネイル
					for(int j=0; j<pageWidget->item(i)->getNGNailItem().NGPointList.count(); j++){
						int NGWait = pageWidget->item(i)->getNGNailItem().NGPointList[j].Tag.Wait;
						int priority = pageWidget->item(i)->getNGNailItem().NGPointList[j].Tag.NGPriority;
						if(NGWait>defDelay && NGWait>addDelay && priority<nowPriority){// 待機時間より長く、かつ現在の待機時間より大きく、かつ優先度がより高い場合
							addDelay = NGWait;
						}
					}
				}
				sumDelay += addDelay;
			}else{
				sumDelay += defDelay;
			}
		}
		return sumDelay;
	}
	return -1;
};

bool ShowThumbnail::isKeyPressed() const { return m_keyPressed; };

bool ShowThumbnail::existCurrentThumbnail() const { return (getCurrentThumbnail()!=NULL); };

void ShowThumbnail::createEditerThumbnail()
{
	updateFKeyColorList();

	OrganizedHistoryItem oitem;
	HistoryItem *hitem = new HistoryItem(GetReviewAlgorithm());
	hitem->InspectedTime = XDateTime::currentDateTime();
	hitem->setInspectID(1);
	hitem->NGCount = getRowCount()*getColumnCount()*2;

	NGNailList Nails;

	for(int i=0; i<getRowCount()*getColumnCount()*2; i++){
		NGNailItem item;
		item.MasterPosX = 0;
		item.MasterPosY = 0;
		item.TargetPosX = 0;
		item.TargetPosY = 0;
		item.isChecked = false;
		item.phase = 0;
		item.page = 0;
		item.FKey = Review::IntToFKey(i%(Review::NoFKey+1));
		//item.NGImage = new NGImageReader;
		//item.NGImage->setPos(0, 0);
		item.setDummyImage(createEditerImage(300, 600, QColor(Qt::GlobalColor::lightGray), Review::IntToFKey(i%(Review::NoFKey+1))));
		//item.NGImage->setDummyImage( createEditerImage(300, 600, QColor(Qt::GlobalColor::lightGray), Review::IntToFKey(i%(Review::NoFKey+1))) );
		item.NGImageWidth = 300;
		item.NGImageHeight = 600;

		ReviewNGPoint p;
		qsrand(time(NULL));
		p.x = (int)(300*qrand()/(double)RAND_MAX);
		p.y = (int)(600*qrand()/(double)RAND_MAX);
		p.AlignedX = 0;
		p.AlignedY = 0;
		p.Error = 2;
		p.ItemSearchedX = 0;
		p.ItemSearchedY = 0;
		p.Ral = /**/"Editer NG";

		item.NGPointList.append(p);

		Nails.append(item);
	}

	hitem->setNGNails(Nails);

	oitem.setHistoryItem(hitem, Review::Front);
	setThumbnailList(&oitem);
}

QImage ShowThumbnail::createEditerImage(int width, int height, QColor backgroundColor, Review::FKey key)
{
	QImage image(width, height, QImage::Format_RGB32);
	image.fill(QColor(Qt::white).rgb());
	//image.fill(backgroundColor.rgb());

	//QString drawStr;
	//if(key==Review::NoFKey){
	//	drawStr = "NoFKey";
	//}else{
	//	drawStr = QString("FKey_%1").arg(Review::FKeyToInt(key)+1);
	//}

	//QPainter painter;
	//painter.begin(&image);

	//painter.drawText(image.rect(), drawStr, QTextOption(Qt::AlignCenter));

	//painter.end();

	return image;
}


void ShowThumbnail::mousePressEvent(QMouseEvent *event)
{
	GUIFormBase::mousePressEvent(event);
	if(GetEditMode()==false){
		setFocus();
	}
}

void ShowThumbnail::showSettingDialog()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqSortNGOrder Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		settingDialog()->setCurrentSortOrder(Send.order);
	}

	settingDialog()->show();
}

void ShowThumbnail::contextMenuEvent(QContextMenuEvent *event)
{
	if(GetEditMode()==false){
		QPoint p = event->pos() + geometry().topLeft();
		if(parentWidget()!=NULL){
			p += parentWidget()->geometry().topLeft();
		}
		contextMenu()->exec(p);
	}
}

void ShowThumbnail::changedRowColumnCount(int rowCount, int columnCount)
{
	if(getRowCount()==rowCount && getColumnCount()==columnCount)return;

	setRowCount(rowCount);
	setColumnCount(columnCount);

	updateGUI();
}

void ShowThumbnail::changedNGSignSize(int size)
{
	
	for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
		getThumbnailList(Review::Front)[i]->setNGSignSize(size);
	}
	for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
		getThumbnailList(Review::Back)[i]->setNGSignSize(size);
	}
	if(expandDialog()!=NULL){
		if(expandDialog()->getThumbnail()!=NULL){
			expandDialog()->getThumbnail()->setNGSignSize(size);
			expandDialog()->updateImage();
		}
	}
	setNGSignSize(size);
}

void ShowThumbnail::slotSetMasterVisible(int state)
{
	bool _viewMaster;
	if(state==Qt::CheckState::Checked){
		_viewMaster = true;
	}else{
		_viewMaster = false;
	}
	for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
		getThumbnailList(Review::Front)[i]->setViewMasterImage(_viewMaster);
	}
	for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
		getThumbnailList(Review::Back)[i]->setViewMasterImage(_viewMaster);
	}
	setViewMaster(_viewMaster);

	thumbnailBook()->repaint();
}

void ShowThumbnail::slotSortOrderChanged(int index)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdSetSortNGOrder Send(GetLayersBase());
		Send.order = (Review::OrderOfSortNG)(index);
		RBase->TransmitDirectly(&Send);

		//ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListPiece);
		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::ShowThumbnail);
		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		ReviewGUI::UpdateHistoryGUI(GetLayersBase(), ReviewGUI::Name::WholeImageForReview);
	}
}

ShowThumbnail::~ShowThumbnail()
{
	if(thumbnailBook()!=NULL)delete thumbnailBook();
	delete infoLabel();
	delete mainLayout();
	//if(FrontThumbnailList.isEmpty()==false){// delete ThumbnailBook につられてすでに delete されているらしい
	//	qDeleteAll(FrontThumbnailList);
	//}
	//if(BackThumbnailList.isEmpty()==false){
	//	qDeleteAll(BackThumbnailList);
	//}
	delete settingDialog();
	delete m_property;
}

void ShowThumbnail::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReviewUpdateLocal *GUICmdReviewUpdateLocalVar = dynamic_cast<GUICmdReviewUpdateLocal *>(packet);
	if(GUICmdReviewUpdateLocalVar!=NULL){
		updateGUI();
		GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview);
		if(Base!=NULL){
			GUICmdSetCurrentNGView Cmd(GetLayersBase());
			if(getMoveMode()==_moveMode::PerPage){
				if(isModeShowPageByPiece()==false)
					Cmd.visible = false;
				else
					Cmd.visible = true;
			}else{
				Cmd.visible = true;
			}
			Base->TransmitDirectly(&Cmd);
			GUICmdUpdateWholeImage WholeNGView(GetLayersBase());
			Base->TransmitDirectly(&WholeNGView);
		}
		if(getMoveMode()!=_moveMode::PerThumbnail){
			if(getCurrentThumbnail()!=NULL){
				CmdSetNGChecked NGCheckCmd(GetLayersBase());
				NGCheckCmd.side = getCurrentSide();
				NGCheckCmd.begin = getGlobalIndex(getCurrentPage(), getCurrentRow(), getCurrentColumn(), getCurrentSide());
				NGCheckCmd.length = getRowCount() * getColumnCount();	//1;// そのNGのみ
				ReviewPIBase *RBase = GetReviewAlgorithm();
				if(RBase!=NULL){
					RBase->TransmitDirectly(&NGCheckCmd);
				}
				for(int row=0;row<getRowCount();row++){
					for(int column=0;column<getColumnCount();column++){
						int	n=getLocalIndex(getCurrentPage(), row, column, getCurrentSide());
						if(0<=n && n<getThumbnailList(getCurrentSide()).count()){
							getThumbnailList(getCurrentSide())[n]->setChecked(true);
						}
					}
				}
			}
		}
		//update();
		return;
	}

	GUICmdUpdateCurrentHistory *GUICmdUpdateCurrentHistoryVar = dynamic_cast<GUICmdUpdateCurrentHistory *>(packet);
	if(GUICmdUpdateCurrentHistoryVar!=NULL){
		updateGUI();
		GUIFormBase *Base = GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview);
		if(Base!=NULL){
			GUICmdSetCurrentNGView Cmd(GetLayersBase());
			if(getMoveMode()==_moveMode::PerPage){
				Cmd.visible = false;
			}else{
				Cmd.visible = true;
			}
			Base->TransmitDirectly(&Cmd);
			GUICmdUpdateWholeImage WholeNGView(GetLayersBase());
			Base->TransmitDirectly(&WholeNGView);
		}
		//update();
		return;
	}

	GUICmdSetFocus *GUICmdSetFocusVar = dynamic_cast<GUICmdSetFocus *>(packet);
	if(GUICmdSetFocusVar!=NULL){
		setFocus();
		//update();
		return;
	}
	GUICmdSetCurrentNGNail *GUICmdSetCurrentNGNailVar = dynamic_cast<GUICmdSetCurrentNGNail *>(packet);
	if(GUICmdSetCurrentNGNailVar!=NULL){
		showPage(Review::ListLocate::Manual, GUICmdSetCurrentNGNailVar->GlobalIndex);
		return;
	}
	
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		CmdReqSettingPropertyDialogVar->setDialog(getPropertyDialog());
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::Thumbnail);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::ShowThumbnail);
		return;
	}
	GUICmdSetCurrentNGNailPageTop	*GUICmdSetCurrentNGNailPageTopVar=dynamic_cast<GUICmdSetCurrentNGNailPageTop *>(packet);
	if(GUICmdSetCurrentNGNailPageTopVar!=NULL){		
		for(int page=0; page<getThumbnailPageList(GUICmdSetCurrentNGNailPageTopVar->Side).count(); page++){
			Thumbnail	*Thm=getThumbnailPageList(GUICmdSetCurrentNGNailPageTopVar->Side)[page][0];
			QString	Area=Thm->getNGNailItem().getArea();
			QStringList	LList=Area.split(',');
			Area=LList[0];
			if(Area==GUICmdSetCurrentNGNailPageTopVar->PieceName){
				setCurrentThumbnail(Thm);
				showPage(GUICmdSetCurrentNGNailPageTopVar->Side, Thm->getPage(), Review::First);
				setFocus();
				break;
			}
		}

		return;
	}
	GUICmdReqCurrentNailItem	*GUICmdReqCurrentNailItemVar=dynamic_cast<GUICmdReqCurrentNailItem *>(packet);
	if(GUICmdReqCurrentNailItemVar!=NULL){
		if(getCurrentThumbnail()!=NULL){
			*GUICmdReqCurrentNailItemVar->NailIndex=getCurrentThumbnail()->getNGNailItem();
		}
		return;
	}
}

void ShowThumbnail::paintEvent(QPaintEvent *event)
{
	GUIFormBase::paintEvent(event);
	QRect rect = geometry();
	rect.setTop(0);
	rect.setLeft(0);
	rect.setWidth(width());
	rect.setHeight(height());
	mainLayout()->setGeometry(rect);

	if(GetEditMode()==true){
		QPainter painter(this);
		painter.drawRect(this->rect());
	}
}
void	ShowThumbnail::SetFKeyIndex(int GlobalIndex ,Review::FKey key)
{
	NGNailItem	NGItem;
	if(GlobalIndex<getThumbnailList(Review::Front).count()){
		int page = GlobalIndex / (getRowCount() * getColumnCount());
		int row = (GlobalIndex % (getRowCount() * getColumnCount())) / getColumnCount();
		int column = GlobalIndex % getColumnCount();
		ThumbnailPageItem	M=getThumbnailPageList(Review::Front)[page];
		for(int i=0;i<M.count();i++){
			if(M[i]->getRow()==row && M[i]->getColumn()==column){
				m_FrontThumbnailList[page][i].setFKey(key);
				break;
			}
		}
	}else{
		int bindex = GlobalIndex - getThumbnailList(Review::Front).count();// 裏のみで見たインデックス
		int page = bindex / (getRowCount() * getColumnCount());
		int row = (bindex % (getRowCount() * getColumnCount())) / getColumnCount();
		int column = bindex % getColumnCount();
		ThumbnailPageItem	M=getThumbnailPageList(Review::Back)[page];
		for(int i=0;i<M.count();i++){
			if(M[i]->getRow()==row && M[i]->getColumn()==column){
				m_BackThumbnailList[page][i].setFKey(key);
				break;
			}
		}
	}
}

void ShowThumbnail::updateGUI()
{
	setUpdatesEnabled(false);

	// 現在のサムネイルアイテムを破棄
	clearThumbnailList();

	// Fキーカラー取得
	updateFKeyColorList();

	// 再取得
	updateThumbnailList();

	// レイアウト再構成
	createThumbnailBook();

	// ステータス初期化
	setCurrentPage(-1);
	setCurrentRow(-1);
	setCurrentColumn(-1);
	setCurrentSide(Review::Front);
	setCurrentThumbnail(NULL);

	if(isModeShowPageByPiece()==false){
	// 現在選択中のNGNailを探して表示する
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase!=NULL){
			CmdReqAdjacentCurrentNG Send(GetLayersBase());
			RBase->TransmitDirectly(&Send);

			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				if(getThumbnailList(Review::Front)[i]->getNGNailItem() == *Send.currentNG()){
					showPage(Review::Manual, getThumbnailList(Review::Front)[i]->getIndexInGlobal());
					setExpandThumbnail(getThumbnailList(Review::Front)[i]->createDup());
					break;
				}
			}
			for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
				if(getThumbnailList(Review::Back)[i]->getNGNailItem() == *Send.currentNG()){
					showPage(Review::Manual, getThumbnailList(Review::Back)[i]->getIndexInGlobal());
					setExpandThumbnail(getThumbnailList(Review::Back)[i]->createDup());
					break;
				}
			}
		}
	}
	else{
		showPage(Review::Front,0, Review::First);
	}
	setUpdatesEnabled(true);
	//update();
}

void ShowThumbnail::updateFKeyColorList()
{
	CmdReqFKeyColorList ReqFKeyColorListCmd(GetLayersBase());
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		RBase->TransmitDirectly(&ReqFKeyColorListCmd);
		if(ReqFKeyColorListCmd.Ret==true){
			setFKeyColorList(ReqFKeyColorListCmd.list);
		}
	}
}

int ShowThumbnail::calcPage(int localIndex) const
{
	return localIndex / getThumbnailCountInPage();
}

void ShowThumbnail::ResizeAction()
{
	//mainLayout->setGeometry(QRect(0, 0, width(), height()));
	if(thumbnailBook()!=NULL){
		thumbnailBook()->setGeometry(geometry());
	}
}

void ShowThumbnail::updateThumbnailList()
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdReqCurrentHistory Send(GetLayersBase());
		RBase->TransmitDirectly(&Send);
		if(Send.Ret==true){
			setThumbnailList(Send.historyPrt());
		}
	}
}

void ShowThumbnail::clearThumbnailList()
{
	//for(int i=0; i<FrontThumbnailList.count(); i++){
	//	disconnect(FrontThumbnailList[i], SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
	//}
	for(ThumbnailList::Iterator it=getThumbnailList(Review::Front).begin(); it!=getThumbnailList(Review::Front).end(); it++){
		if((*it)->isDummy()==false){
			if(GetEditMode()==false && isEnableExpandThumbnal()==true){
				disconnect(*it, SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
			}
		}
		delete *it;
	}
	getThumbnailList(Review::Front).clear();
	getThumbnailPageList(Review::Front).clear();

	//for(int i=0; i<BackThumbnailList.count(); i++){
	//	disconnect(BackThumbnailList[i], SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
	//}
	for(ThumbnailList::Iterator it=getThumbnailList(Review::Back).begin(); it!=getThumbnailList(Review::Back).end(); it++){
		if((*it)->isDummy()==false){
			if(GetEditMode()==false){
				disconnect(*it, SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
			}
		}
		delete *it;
	}
	getThumbnailList(Review::Back).clear();
	getThumbnailPageList(Review::Back).clear();

	if(expandDialog()!=NULL){
		expandDialog()->setThumbnail(NULL);
	}
}

void ShowThumbnail::setThumbnailList(OrganizedHistoryIndex orgHistoryPtr)
{
	clearThumbnailList();

	// 全NGリストの再構成
	if(orgHistoryPtr==NULL)return;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return;

	CmdReqMasterImagePiece ReqMPieceCmd(GetLayersBase());
	setCurrentEID(orgHistoryPtr->getInspectID());

	CmdReqInsLib InsLibCmd(GetLayersBase());
	RBase->TransmitDirectly(&InsLibCmd);

	//int globalIndex = 0;

	CmdReqWholeImageInfo ReqMWInfo(GetLayersBase());
	RBase->TransmitDirectly( &ReqMWInfo );

	if(orgHistoryPtr->hasFront()==true && orgHistoryPtr->getFront()->getNGNails().count()>0){
		// サムネイルアイテム作成
		HistoryIndex FHistory = orgHistoryPtr->getFront();

		CmdReqForSaveNGList	hCmdReqForSaveNGList(GetLayersBase());
		hCmdReqForSaveNGList.Top=true;
		hCmdReqForSaveNGList.NGPoints=FHistory->getNGNails().count();

		for(int i=0; i<FHistory->getNGNails().count(); i++){
			NGNailItem	&NItem=FHistory->getNGNails()[i];
			int phase	= NItem.phase;
			int page	= NItem.page;
			Thumbnail *thumb = new Thumbnail(this);
			thumb->setSide(Review::Front);
			thumb->setNGNailItem( NItem );
			if(ReqMWInfo.FrontOutlineOffset.count()>phase && ReqMWInfo.FrontOutlineOffset[phase].count()>page){
				ReqMPieceCmd.side = Review::Front;
				ReqMPieceCmd.phase = NItem.phase;
				ReqMPieceCmd.page = NItem.page;
				ReqMPieceCmd.setData(Review::Front, NItem);
				ReqMPieceCmd.MasterX = NItem.MasterPosX;
				ReqMPieceCmd.MasterY = NItem.MasterPosY;
				if( NItem.NGPointList.count()>0){
					ReqMPieceCmd.MasterX -= NItem.NGPointList[0].AlignedX;
					ReqMPieceCmd.MasterY -= NItem.NGPointList[0].AlignedY;
				}
				RBase->TransmitDirectly(&ReqMPieceCmd);
				thumb->setMasterPieceImage(QPixmap::fromImage(ReqMPieceCmd.image));
			}else{
				thumb->setMasterPieceImage(QPixmap::fromImage(NItem.image()));
			}

			ForSaveNGPoint	*ForSaveNGPointer=new ForSaveNGPoint(i);
			ForSaveNGPointer->Top=hCmdReqForSaveNGList.Top;
			hCmdReqForSaveNGList.Data.NGList.AppendList(ForSaveNGPointer);
			ForSaveNGPointer->Side	=1;
			if(ReqMWInfo.FrontOutlineOffset.count()>phase && ReqMWInfo.FrontOutlineOffset[phase].count()>page){
				ForSaveNGPointer->Position=QPoint(NItem.TargetPosX + ReqMWInfo.FrontOutlineOffset[phase][page].x()
												, NItem.TargetPosY + ReqMWInfo.FrontOutlineOffset[phase][page].y());
			}

			thumb->setNGSignSize(getNGSignSize());
			thumb->setViewMasterImage( isViewMaster() );
			thumb->setFKeyColor(getFKeyColorList()[NItem.FKey]);
			if(NItem.getLibraryRal().isEmpty()==false && InsLibCmd.FrontInsLibHash.isEmpty()==false){
				QString tip;
				QList<InsLibraryItem> LibList = InsLibCmd.FrontInsLibHash.values(NItem.getLibraryRal());
				for(QList<InsLibraryItem>::ConstIterator LibItem=LibList.constBegin(); LibItem!=LibList.constEnd(); LibItem++){
					if(LibItem->LibCode==NItem.getLibraryCode()){
						tip = LibItem->LibName;
						ForSaveNGPointer->Cause=LibItem->LibName;
						break;
					}
				}
				tip += /**/"[" + NItem.getLibraryRal() + /**/"]";
				thumb->setToolTip(tip);
			}

			getThumbnailList(Review::Front).append( thumb );
			if(GetEditMode()==false && isEnableExpandThumbnal()==true){
				connect(thumb, SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
			}
		}
		RBase->TransmitDirectly(&hCmdReqForSaveNGList);
	}

	if(orgHistoryPtr->hasBack()==true && orgHistoryPtr->getBack()->getNGNails().count()>0){
		// サムネイルアイテム作成
		HistoryIndex BHistory = orgHistoryPtr->getBack();

		CmdReqForSaveNGList	hCmdReqForSaveNGList(GetLayersBase());
		hCmdReqForSaveNGList.Top=false;
		hCmdReqForSaveNGList.NGPoints=BHistory->getNGNails().count();

		for(int i=0; i<BHistory->getNGNails().count(); i++){
			NGNailItem	&NItem=BHistory->getNGNails()[i];
			int phase = NItem.phase;
			int page  = NItem.page;
			Thumbnail *thumb = new Thumbnail(this);
			thumb->setSide(Review::Back);
			thumb->setNGNailItem( NItem );
			if(ReqMWInfo.BackOutlineOffset.count()>phase && ReqMWInfo.BackOutlineOffset[phase].count()>page){
				ReqMPieceCmd.side = Review::Back;
				ReqMPieceCmd.phase = phase;
				ReqMPieceCmd.page = page;
				ReqMPieceCmd.setData(Review::Back, NItem);
				ReqMPieceCmd.MasterX = NItem.MasterPosX/* + ReqMWInfo.BackOutlineDrawOffset[phase][page].x()*/;
				ReqMPieceCmd.MasterY = NItem.MasterPosY/* + ReqMWInfo.BackOutlineDrawOffset[phase][page].y()*/;
				if( NItem.NGPointList.count()>0){
					ReqMPieceCmd.MasterX -= NItem.NGPointList[0].AlignedX;
					ReqMPieceCmd.MasterY -= NItem.NGPointList[0].AlignedY;
				}
				RBase->TransmitDirectly(&ReqMPieceCmd);
				thumb->setMasterPieceImage(QPixmap::fromImage(ReqMPieceCmd.image));
			}else{
				thumb->setMasterPieceImage(QPixmap::fromImage(NItem.image()));
			}

			ForSaveNGPoint	*ForSaveNGPointer=new ForSaveNGPoint(i);
			ForSaveNGPointer->Top=hCmdReqForSaveNGList.Top;
			hCmdReqForSaveNGList.Data.NGList.AppendList(ForSaveNGPointer);
			ForSaveNGPointer->Side	=2;
			if(ReqMWInfo.BackOutlineOffset.count()>phase && ReqMWInfo.BackOutlineOffset[phase].count()>page){
				ForSaveNGPointer->Position=QPoint(NItem.TargetPosX +  ReqMWInfo.BackOutlineOffset[phase][page].x()
												, NItem.TargetPosY +  ReqMWInfo.BackOutlineOffset[phase][page].y());
			}

			thumb->setNGSignSize(getNGSignSize());
			thumb->setViewMasterImage( isViewMaster() );
			thumb->setFKeyColor(getFKeyColorList()[NItem.FKey]);
			if(NItem.getLibraryRal().isEmpty()==false && InsLibCmd.BackInsLibHash.isEmpty()==false){
				QString tip;
				QList<InsLibraryItem> LibList = InsLibCmd.BackInsLibHash.values(NItem.getLibraryRal());
				for(QList<InsLibraryItem>::ConstIterator LibItem=LibList.constBegin(); LibItem!=LibList.constEnd(); LibItem++){
					if(LibItem->LibCode==NItem.getLibraryCode()){
						tip = LibItem->LibName;
						ForSaveNGPointer->Cause=LibItem->LibName;
						break;
					}
				}
				tip += /**/"[" + NItem.getLibraryRal() + /**/"]";
				thumb->setToolTip(tip);
			}
			thumb->setDrawEdge(GetEditMode());
			getThumbnailList(Review::Back).append( thumb );
			if(GetEditMode()==false && isEnableExpandThumbnal()){
				connect(thumb, SIGNAL(clicked(Thumbnail *)), this, SLOT(slotSetCurrentThumbnail(Thumbnail *)));
			}
		}
		RBase->TransmitDirectly(&hCmdReqForSaveNGList);
	}

	if(isModeShowPageByPiece()==false)
		createThumbnailPageList();
	else
		createThumbnailPageListByPiece();
}

void ShowThumbnail::createThumbnailPageList()
{
	getThumbnailPageList(Review::Front).clear();
	getThumbnailPageList(Review::Back).clear();

	int globalIndex = 0;
	// ページの作成
	int frontPageMax = getThumbnailList(Review::Front).count() / (getThumbnailCountInPage());// 作るべきページの数
	if((getThumbnailList(Review::Front).count() % getThumbnailCountInPage())!=0){
		frontPageMax++;
	}
	for(int page=0; page<frontPageMax; page++){
		getThumbnailPageList(Review::Front).append(ThumbnailPageItem(page));// ページ作成
	}
	// ページリストの作成
	for(int i=0; i<getThumbnailList(Review::Front).count(); i++, globalIndex++){
		int page = i / (getRowCount() * getColumnCount());// ページ番号
		int row =  (i - page * (getRowCount() * getColumnCount())) / getColumnCount(); // 縦位置
		int column = (i - page * (getRowCount() * getColumnCount())) % getColumnCount();// 横位置
		getThumbnailList(Review::Front)[i]->setPosision(page,row, column);// 位置情報設定
		getThumbnailList(Review::Front)[i]->setIndexInLocal(i);
		getThumbnailList(Review::Front)[i]->setIndexInGlobal(globalIndex);
		getThumbnailPageList(Review::Front)[page].append(getThumbnailList(Review::Front)[i]);// ページリストに追加
	}
	
	// ページの作成
	int backPageMax = getThumbnailList(Review::Back).count() / (getRowCount() * getColumnCount());// 作るべきページの数
	if((getThumbnailList(Review::Back).count() % getThumbnailCountInPage())!=0){
		backPageMax++;
	}
	for(int page=0; page<backPageMax; page++){
		getThumbnailPageList(Review::Back).append(ThumbnailPageItem(page));// ページ作成
	}
	// ページリストの作成
	for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
		int page = i / (getRowCount() * getColumnCount());// ページ番号
		int row =  (i - page * (getRowCount() * getColumnCount())) / getColumnCount(); // 縦位置
		int column = (i - page * (getRowCount() * getColumnCount())) % getColumnCount();// 横位置
		getThumbnailList(Review::Back)[i]->setPosision(page,row, column);// 位置情報設定
		getThumbnailList(Review::Back)[i]->setIndexInLocal(i);
		getThumbnailList(Review::Back)[i]->setIndexInGlobal(globalIndex);
		globalIndex++;
		getThumbnailPageList(Review::Back)[page].append(getThumbnailList(Review::Back)[i]);// ページリストに追加
	}
}

void ShowThumbnail::createThumbnailPageListByPiece()
{
	QStringList	FrontPieceList;
	QStringList	BackPieceList;
	GUIFormBase *GUIForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ListPiece, /**/"");
	if(GUIForm!=NULL){
		GUICmdReqAreaList	UpdateCmd(GetLayersBase());
		UpdateCmd.Side=Review::Front;
		GUIForm->TransmitDirectly(&UpdateCmd);
		FrontPieceList=UpdateCmd.PieceList;
	}
	if(GUIForm!=NULL){
		GUICmdReqAreaList	UpdateCmd(GetLayersBase());
		UpdateCmd.Side=Review::Back;
		GUIForm->TransmitDirectly(&UpdateCmd);
		BackPieceList=UpdateCmd.PieceList;
	}

	getThumbnailPageList(Review::Front).clear();
	getThumbnailPageList(Review::Back).clear();

	int globalIndex = 0;
	int frontPageMax=0;
	if(FrontPieceList.count()!=0){
		// ページの作成
		int		*TmpNailCountInPiece=new int[FrontPieceList.count()];
		for(int t=0;t<FrontPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
			QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
			QStringList	LList=Area.split(',');
			Area=LList[0];
			for(int t=0;t<FrontPieceList.count();t++){
				if(FrontPieceList[t]==Area && getThumbnailList(Review::Front)[i]->getNGNailItem().phase==0){
					TmpNailCountInPiece[t]++;
					break;
				}
			}
		}
		for(int i=0;i<FrontPieceList.count();i++){
			frontPageMax+=(TmpNailCountInPiece[i]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
		}
		for(int page=0; page<frontPageMax; page++){
			getThumbnailPageList(Review::Front).append(ThumbnailPageItem(page));// ページ作成
		}
		for(int t=0;t<FrontPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int t=0;t<FrontPieceList.count();t++){
			// ページリストの作成
			int	GPage=0;
			for(int h=0;h<t;h++){
				GPage+=(TmpNailCountInPiece[h]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
			}
			int	LocalIndex=0;
			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
				QStringList	LList=Area.split(',');
				Area=LList[0];
				if(FrontPieceList[t]==Area && getThumbnailList(Review::Front)[i]->getNGNailItem().phase==0){
					int page = TmpNailCountInPiece[t] / getThumbnailCountInPage();// ページ番号
					int row =  (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) / getColumnCount(); // 縦位置
					int column = (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) % getColumnCount();// 横位置
					getThumbnailList(Review::Front)[i]->setPosision(GPage+page ,row, column);// 位置情報設定
					getThumbnailList(Review::Front)[i]->setIndexInLocal(LocalIndex);
					getThumbnailList(Review::Front)[i]->setIndexInGlobal(globalIndex);
					getThumbnailPageList(Review::Front)[GPage+page].append(getThumbnailList(Review::Front)[i]);// ページリストに追加
					TmpNailCountInPiece[t]++;
					globalIndex++;
					LocalIndex++;
				}
			}
		}
		delete	[]TmpNailCountInPiece;
	}
	bool	BackInPhase=false;
	if(BackPieceList.count()!=0){
		//Phase対応
		// ページの作成
		int		*TmpNailCountInPiece=new int[BackPieceList.count()];
		for(int t=0;t<BackPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
			QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
			QStringList	LList=Area.split(',');
			Area=LList[0];
			for(int t=0;t<BackPieceList.count();t++){
				if(BackPieceList[t]==Area && getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1){
					TmpNailCountInPiece[t]++;
					break;
				}
			}
		}
		int backPageMax=0;
		for(int i=0;i<BackPieceList.count();i++){
			backPageMax+=(TmpNailCountInPiece[i]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
		}
		//for(int page=0; page<frontPageMax; page++){
		//	getThumbnailPageList(Review::Back).append(ThumbnailPageItem(page));// dummy ページ作成
		//}
		for(int page=0; page<backPageMax; page++){
			getThumbnailPageList(Review::Back).append(ThumbnailPageItem(frontPageMax+page));// ページ作成
		}
		for(int t=0;t<BackPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int t=0;t<BackPieceList.count();t++){
			// ページリストの作成
			int	GPage=0;
			for(int h=0;h<t;h++){
				GPage+=(TmpNailCountInPiece[h]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
			}
			int	LocalIndex=0;
			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
				QStringList	LList=Area.split(',');
				Area=LList[0];
				if(BackPieceList[t]==Area && getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1){
					int page = TmpNailCountInPiece[t] / getThumbnailCountInPage();// ページ番号
					int row =  (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) / getColumnCount(); // 縦位置
					int column = (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) % getColumnCount();// 横位置
					getThumbnailList(Review::Front)[i]->setPosision(GPage+page,row, column);// 位置情報設定
					getThumbnailList(Review::Front)[i]->setIndexInLocal(LocalIndex);
					getThumbnailList(Review::Front)[i]->setIndexInGlobal(globalIndex);
					getThumbnailPageList(Review::Back)[GPage+page].append(getThumbnailList(Review::Front)[i]);// ページリストに追加
					TmpNailCountInPiece[t]++;
					globalIndex++;
					LocalIndex++;
					BackInPhase=true;
				}
			}
		}
		delete	[]TmpNailCountInPiece;
	}
	if(BackInPhase==false && BackPieceList.count()!=0){
		// ページの作成
		int		*TmpNailCountInPiece=new int[BackPieceList.count()];
		for(int t=0;t<BackPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
			QString	Area=getThumbnailList(Review::Back)[i]->getNGNailItem().getArea();
			QStringList	LList=Area.split(',');
			Area=LList[0];
			for(int t=0;t<BackPieceList.count();t++){
				if(BackPieceList[t]==Area){
					TmpNailCountInPiece[t]++;
					break;
				}
			}
		}
		int backPageMax=0;
		for(int i=0;i<BackPieceList.count();i++){
			backPageMax+=(TmpNailCountInPiece[i]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
		}
		for(int page=0; page<backPageMax; page++){
			getThumbnailPageList(Review::Back).append(ThumbnailPageItem(page));// ページ作成
		}
		for(int t=0;t<BackPieceList.count();t++){
			TmpNailCountInPiece[t]=0;
		}
		for(int t=0;t<BackPieceList.count();t++){
			// ページリストの作成
			int	GPage=0;
			for(int h=0;h<t;h++){
				GPage+=(TmpNailCountInPiece[h]+getThumbnailCountInPage()-1)/getThumbnailCountInPage();
			}
			int	LocalIndex=0;
			for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
				QString	Area=getThumbnailList(Review::Back)[i]->getNGNailItem().getArea();
				QStringList	LList=Area.split(',');
				Area=LList[0];
				if(BackPieceList[t]==Area){
					int page = TmpNailCountInPiece[t] / getThumbnailCountInPage();// ページ番号
					int row =  (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) / getColumnCount(); // 縦位置
					int column = (TmpNailCountInPiece[t] - page * getThumbnailCountInPage()) % getColumnCount();// 横位置
					getThumbnailList(Review::Back)[i]->setPosision(GPage+page,row, column);// 位置情報設定
					getThumbnailList(Review::Back)[i]->setIndexInLocal(LocalIndex);
					getThumbnailList(Review::Back)[i]->setIndexInGlobal(globalIndex);
					getThumbnailPageList(Review::Back)[GPage+page].append(getThumbnailList(Review::Back)[i]);// ページリストに追加
					TmpNailCountInPiece[t]++;
					globalIndex++;
					LocalIndex++;
				}
			}
		}
		delete	[]TmpNailCountInPiece;
	}
}

bool ShowThumbnail::setCurrentNG(Review::SideType side, int page, int row, int column)
{
	if(row<0 || getRowCount()<=row || column<0 || getColumnCount()<=column)return false;// 無効インデックス
	//if((row+1)*(column+1)>getThumbnailList(side).count())return false;// インデックスオーバー

	ReviewPIBase *RBase = GetReviewAlgorithm();
	if(RBase!=NULL){
		CmdSetCurrentNGNail Send(GetLayersBase());
		Send.refType = Review::Ref_Index;// ロケートによる指定
		Send.locate = Review::Manual;// インデックスの直接指定
		Send.Index = getGlobalIndex(page, row, column, side);// インデックス設定
		RBase->TransmitDirectly(&Send);// 送信

		if(Send.Ret==true){// 移動成功
			Thumbnail	*Thm=getThumbnail(side,  page,  row,  column);
			if(Thm!=NULL){
				if(getCurrentThumbnail()!=NULL){// 前の選択サムネイルがある場合
					getCurrentThumbnail()->setSelected(false);// 非選択状態に戻す
				}

				setCurrentSide(side);
				setCurrentPage(page);
				setCurrentRow(row);
				setCurrentColumn(column);
				setCurrentThumbnail(Thm);
				setExpandThumbnail(Thm->createDup());

				setExpandThumbnailVisible(getExpandThumbnailVisible());
				

				// チェック済み付与 ただしサムネイルモードのときのみ
				if(getMoveMode()==_moveMode::PerThumbnail && getCurrentThumbnail()!=NULL && getCurrentThumbnail()->isChecked()==false){
					CmdSetNGChecked NGCheckCmd(GetLayersBase());
					NGCheckCmd.side = getCurrentSide();
					if(getMoveMode()==_moveMode::PerThumbnail){// サムネイル単位モードなら現在NGNailだけ
						NGCheckCmd.begin = getCurrentThumbnail()->getIndexInLocal();// 現在NGNail
						NGCheckCmd.length = 1;// そのNGのみ
						RBase->TransmitDirectly(&NGCheckCmd);
					}else{
						//NGCheckCmd.begin = getCurrentPage() * getThumbnailCountInPage();// 現在のページにおける最初のNGNail
						//NGCheckCmd.length = getThumbnailCountInPage();// 1ページ分
					}
					if(NGCheckCmd.Ret==true){
						getCurrentThumbnail()->setChecked(true);
						GUIFormBase *GBase = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
						if(GBase!=NULL){
							GUICmdUpdateCurrentHistoryChecked Send(GetLayersBase());
							GBase->TransmitDirectly(&Send);
						}
					}
				}

				// 矢印キーによる移動がサムネイル単位ならば
				if(getMoveMode()==_moveMode::PerThumbnail){
					getCurrentThumbnail()->setSelected(true);// 選択状態の表示形式へ変更
				}

				return true;
			}
		}else{
			return false;
		}
	}else{
		return false;
	}

	return true;
}

ThumbnailList *ShowThumbnail::currentThumbnailList()
{
	return &getThumbnailList(getCurrentSide());
}

ThumbnailPageList *ShowThumbnail::currentThumbnailPageList()
{
	return &getThumbnailPageList(getCurrentSide());
}

// 指定サイドのみのインデックス
int ShowThumbnail::getLocalIndex(int page, int row, int column, Review::SideType side) const
{
	for(int i=0; i<getThumbnailList(side).count(); i++){
		if(getThumbnailList(side)[i]->getPage()==page
		&& getThumbnailList(side)[i]->getColumn()==column
		&& getThumbnailList(side)[i]->getRow()==row){
			 return getThumbnailList(side)[i]->getIndexInLocal();
		}
	}
	if(side==Review::Back){
		for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
			if(getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1
			&& getThumbnailList(Review::Front)[i]->getPage()==page
			&& getThumbnailList(Review::Front)[i]->getColumn()==column
			&& getThumbnailList(Review::Front)[i]->getRow()==row){
				 return getThumbnailList(Review::Front)[i]->getIndexInLocal();
			}
		}
	}

	if(page<0)return -1;
	int index = (page * getRowCount() * getColumnCount()) + (row * getColumnCount()) + column;
	if(side==Review::Front){
		if(index >= getThumbnailList(Review::Front).count()){
			return -1;
		}else{
			return index;
		}
	}else{
		if(index >= getThumbnailList(Review::Back).count()){
			return -1;
		}else{
			return index;
		}
	}
}

// 表後ろ合わせたインデックス
int ShowThumbnail::getGlobalIndex(int page, int row, int column, Review::SideType side) const
{
	for(int i=0; i<getThumbnailList(side).count(); i++){
		if(getThumbnailList(side)[i]->getPage()==page
		&& getThumbnailList(side)[i]->getColumn()==column
		&& getThumbnailList(side)[i]->getRow()==row){
			 return getThumbnailList(side)[i]->getIndexInGlobal();
		}
	}
	if(side==Review::Back){
		for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
			if(getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1
			&& getThumbnailList(Review::Front)[i]->getPage()==page
			&& getThumbnailList(Review::Front)[i]->getColumn()==column
			&& getThumbnailList(Review::Front)[i]->getRow()==row){
				 return getThumbnailList(Review::Front)[i]->getIndexInGlobal();
			}
		}
	}
	int index = getLocalIndex(page, row, column, side);
	if(side==Review::Back){
		index += getThumbnailList(Review::Front).count();// 裏の場合、表の分を合わせたインデックスにする
	}
	return index;
}

void ShowThumbnail::updateInfoLabel()
{
	QString side = (getCurrentSide()==Review::Front ? /**/"Front" : /**/"Back");
	int page = getCurrentPage()+1;
	int pageMax = getCurrentPageCount();
	QString mode = getMoveMode()==_moveMode::PerThumbnail ? /**/"Thumbnail" : /**/"Page";
	QString eid;
	if(getCurrentEID()==-1){
		eid = /**/"";
	}else{
		eid = QString(/**/"EID=%1").arg(getCurrentEID());
	}
	if(isModeShowPageByPiece()==false)
		infoLabel()->setText((QString(/**/"(%5) [%1] %2 / %3 - \"%4") + QString(/**/"Mode") + /**/'\"').arg(side).arg(page).arg(pageMax).arg(mode).arg(eid));
	else{
		if(getCurrentThumbnail()!=NULL){
			QString	Area=getCurrentThumbnail()->getNGNailItem().getArea();
			QStringList	LList=Area.split(',');
			Area=LList[0];
			if(getCurrentThumbnail()->getNGNailItem().phase==0)
				side= /**/"Front";
			else
				side=/**/"Back";
			infoLabel()->setText((QString(/**/"%5 [%1] %2 / %3 - \"%4") + QString(/**/"Mode") + /**/'\"').arg(side).arg(page).arg(pageMax).arg(mode).arg(Area));
		}
		else{
			infoLabel()->setText((QString(/**/"(%5) [%1] %2 / %3 - \"%4") + QString(/**/"Mode") + /**/'\"').arg(side).arg(page).arg(pageMax).arg(mode).arg(eid));
		}
	}
}

void ShowThumbnail::createThumbnailBook()
{
	if(thumbnailBook()!=NULL){
		thumbnailBook()->setParent(NULL);

		while(thumbnailBook()->count()!=0){
			if(GetEditMode()==true){
				ThumbnailPage *tpage = dynamic_cast<ThumbnailPage *>(thumbnailBook()->widget(0));
				if(tpage!=NULL){
					for(int page=0; page<getThumbnailPageList(Review::Front).count(); page++){
						for(int i=0; i<getThumbnailPageList(Review::Front)[page].count(); i++){
							tpage->removeThumbnail(getThumbnailPageList(Review::Front)[page][i]);
							getThumbnailPageList(Review::Front)[page][i]->setParent(NULL);
						}
					}
				}
			}
			QWidget	*w=thumbnailBook()->widget(0);
			thumbnailBook()->removeWidget(w);
			delete	w;
		}

		clearThumbnailBook();
		//if(GetEditMode()==true){
		//	createEditerThumbnail();
		//}
	}


	setThumbnailBook(new QStackedWidget(this));

	thumbnailBook()->setUpdatesEnabled(false);

	for(int page=0; page<getThumbnailPageList(Review::Front).count(); page++){
		ThumbnailPage *curPage = new ThumbnailPage;
		for(int i=0; i<getThumbnailPageList(Review::Front)[page].count(); i++){
			getThumbnailPageList(Review::Front)[page][i]->setParent(NULL);
			curPage->addThumnail(getThumbnailPageList(Review::Front)[page][i]);
		}
		// 穴埋め
		if(getThumbnailPageList(Review::Front)[page].count() != getThumbnailCountInPage()){// ページのサムネイル枠に空きがあるとき
			int fillCount = getThumbnailCountInPage() - getThumbnailPageList(Review::Front)[page].count();// 空きの数を計算
			int lastLocalIndex = getThumbnailPageList(Review::Front)[page].last()->getIndexInLocal();
			for(int i=0; i<fillCount; i++){
				int nowLocalIndex = lastLocalIndex + i + 1;
				int row    =  (nowLocalIndex % getThumbnailCountInPage()) / getColumnCount(); // 縦位置
				int column =  (nowLocalIndex % getThumbnailCountInPage()) % getColumnCount(); // 横位置
				
				Thumbnail *thumb = new Thumbnail(this);
				thumb->setDummy(true);
				thumb->setSide(Review::Front);
				thumb->setPosision(page,row, column);
				NGNailItem dummyItem;
				dummyItem.NGImageWidth = getThumbnailPageList(Review::Front)[page].front()->getNGNailItem().NGImageWidth;
				dummyItem.NGImageHeight = getThumbnailPageList(Review::Front)[page].front()->getNGNailItem().NGImageHeight;
				thumb->setNGNailItem(dummyItem);
				thumb->setViewMasterImage( isViewMaster() );
				thumb->setNGSignSize(getNGSignSize());
				curPage->addThumnail(thumb);
			}
		}

		thumbnailBook()->addWidget(curPage);
	}

	for(int page=0; page<getThumbnailPageList(Review::Back).count(); page++){
		ThumbnailPage *curPage = new ThumbnailPage;
		for(int i=0; i<getThumbnailPageList(Review::Back)[page].count(); i++){
			getThumbnailPageList(Review::Back)[page][i]->setParent(NULL);
			curPage->addThumnail(getThumbnailPageList(Review::Back)[page][i]);
		}
		// 穴埋め
		if(getThumbnailPageList(Review::Back)[page].count() != getThumbnailCountInPage()){// ページのサムネイル枠に空きがあるとき
			int fillCount = getThumbnailCountInPage() - getThumbnailPageList(Review::Back)[page].count();// 空きの数を計算
			int lastLocalIndex = getThumbnailPageList(Review::Back)[page].last()->getIndexInLocal();
			for(int i=0; i<fillCount; i++){
				int nowLocalIndex = lastLocalIndex + i + 1;
				int row    =  (nowLocalIndex % getThumbnailCountInPage()) / getColumnCount(); // 縦位置
				int column =  (nowLocalIndex % getThumbnailCountInPage()) % getColumnCount(); // 横位置
				
				Thumbnail *thumb = new Thumbnail(this);
				thumb->setDummy(true);
				thumb->setSide(Review::Back);
				thumb->setPosision(page,row, column);
				NGNailItem dummyItem;
				dummyItem.NGImageWidth = getThumbnailPageList(Review::Back)[page].front()->getNGNailItem().NGImageWidth;
				dummyItem.NGImageHeight = getThumbnailPageList(Review::Back)[page].front()->getNGNailItem().NGImageHeight;
				thumb->setNGNailItem(dummyItem);
				thumb->setViewMasterImage( isViewMaster() );
				thumb->setNGSignSize(getNGSignSize());
				curPage->addThumnail(thumb);
			}
		}

		thumbnailBook()->addWidget(curPage);
	}

	thumbnailBook()->setGeometry(0, 0, width(), height());
	thumbnailBook()->setVisible(true);
	
	thumbnailBook()->setUpdatesEnabled(true);
	//mainLayout->addWidget(ThumbnailBook);
	mainLayout()->insertWidget(1, thumbnailBook());
}

void ShowThumbnail::startPageWaitTimeLine(int interval){
	pageWaitTimeLine()->stop();
	if(interval>0){
		pageWaitProgressBar()->setValue(0);

		pageWaitTimeLine()->setCurrentTime(0);
		pageWaitTimeLine()->setDuration(interval);
		pageWaitTimeLine()->start();
	}else{
		pageWaitProgressBar()->setValue( pageWaitProgressBar()->maximum() );
	}
}

void ShowThumbnail::showPage(Review::SideType side, int page, Review::ListLocate locate, int row, int column)
{
	GUIFormBase *GUIForm = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ListPiece, /**/"");
	if(GUIForm!=NULL){
		for(int i=0; i<getThumbnailList(side).count(); i++){
			if(getThumbnailList(side)[i]->getPage()==page
			&& getThumbnailList(side)[i]->getColumn()==column
			&& getThumbnailList(side)[i]->getRow()==row){

				GUICmdSetCurrentFocusOnNail	CurrentFocusOnNailCmd(GetLayersBase());
				CurrentFocusOnNailCmd.Side		=side;
				QString	Area=getThumbnailList(side)[i]->getNGNailItem().getArea();
				QStringList	LList=Area.split(',');
				Area=LList[0];
				CurrentFocusOnNailCmd.PieceName	=Area;
				GUIForm->TransmitDirectly(&CurrentFocusOnNailCmd);
				break;
			}
		}
		for(int i=0; i<getThumbnailList(side).count(); i++){
			if(getThumbnailList(side)[i]->getPage()==page
			&& getThumbnailList(side)[i]->getColumn()==0 && column<0
			&& getThumbnailList(side)[i]->getRow()==0 && row<0){

				GUICmdSetCurrentFocusOnNail	CurrentFocusOnNailCmd(GetLayersBase());
				CurrentFocusOnNailCmd.Side		=side;
				QString	Area=getThumbnailList(side)[i]->getNGNailItem().getArea();
				QStringList	LList=Area.split(',');
				Area=LList[0];
				CurrentFocusOnNailCmd.PieceName	=Area;
				GUIForm->TransmitDirectly(&CurrentFocusOnNailCmd);
				break;
			}
		}
		if(side==Review::Back){
			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				if(getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1
				&& getThumbnailList(Review::Front)[i]->getPage()==page
				&& getThumbnailList(Review::Front)[i]->getColumn()==column
				&& getThumbnailList(Review::Front)[i]->getRow()==row){

					GUICmdSetCurrentFocusOnNail	CurrentFocusOnNailCmd(GetLayersBase());
					CurrentFocusOnNailCmd.Side		=side;
					QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
					QStringList	LList=Area.split(',');
					Area=LList[0];
					CurrentFocusOnNailCmd.PieceName	=Area;
					GUIForm->TransmitDirectly(&CurrentFocusOnNailCmd);
					break;
				}
			}
			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				if(getThumbnailList(Review::Front)[i]->getNGNailItem().phase==1
				&& getThumbnailList(Review::Front)[i]->getPage()==page
				&& getThumbnailList(Review::Front)[i]->getColumn()==0 && column<0
				&& getThumbnailList(Review::Front)[i]->getRow()==0 && row<0){

					GUICmdSetCurrentFocusOnNail	CurrentFocusOnNailCmd(GetLayersBase());
					CurrentFocusOnNailCmd.Side		=side;
					QString	Area=getThumbnailList(Review::Front)[i]->getNGNailItem().getArea();
					QStringList	LList=Area.split(',');
					Area=LList[0];
					CurrentFocusOnNailCmd.PieceName	=Area;
					GUIForm->TransmitDirectly(&CurrentFocusOnNailCmd);
					break;
				}
			}
		}
	}

	if(page!=getCurrentPage() || getCurrentSide()!=side){// 表示するページ・表裏のどちらかが違う場合
		if(thumbnailBook()!=NULL && page>=0 && page<getPageCount(side)){
			if(side==Review::Front){
				thumbnailBook()->setCurrentIndex(page);
			}else{
				thumbnailBook()->setCurrentIndex( getPageCount(Review::Front) + page);
			}

			int	tm= getPageDelay( dynamic_cast<ThumbnailPage*>(thumbnailBook()->currentWidget()) );
			if(tm>0){
				startPageWaitTimeLine(tm );
			}
		}
	}
	if(page!=getCurrentPage() || getCurrentSide()!=side || getCurrentRow()!=row || getCurrentColumn()!=column){// サムネイルの場所が違う場合
		// サムネイルを選択する
		if(locate==Review::First){// 一番前
			setCurrentNG(side, page, 0, 0);
		}else if(locate==Review::End){
			setCurrentNG(side, page,
			(getThumbnailPageList(side)[page].count()-1) / getColumnCount(),
			(getThumbnailPageList(side)[page].count()-1) % getColumnCount());
		}else{
			if(getLocalIndex(page, row, column, side)==-1){// 無効インデックス
				return;
			}
			setCurrentNG(side, page, row, column);
		}

		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
		ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);

		GUIFormBase *GUIBase = GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::WholeImageForReview, /**/"");
		if(GUIBase!=NULL){
			GUICmdUpdateCurrentNGNail Send(GetLayersBase());
			GUIBase->TransmitDirectly(&Send);
		}
	}

	updateInfoLabel();
}

void ShowThumbnail::showPage(Review::SideType side, Review::ListLocate locate)
{
	if(locate==Review::First){
		showPage(side, 0, locate);
	}else if(locate==Review::End){
		showPage(side, getPageCount(side)-1, Review::ListLocate::End);
	}else{
		showPage(side, getCurrentPage(), locate);
	}
}

void ShowThumbnail::showPage(Review::ListLocate locate, int GlobalIndex)
{
	if(locate==Review::First){
		if(getPageCount(Review::Front)!=0){
			showPage(Review::Front, 0, locate);
		}else{
			showPage(Review::Back, 0, locate);
		}
	}else if(locate==Review::End){
		if(getPageCount(Review::Front)!=0){
			showPage(Review::Front, getPageCount(Review::Front), locate);
		}else{
			showPage(Review::Back, getPageCount(Review::Back), locate);
		}
	}else{
		if(GlobalIndex<0 || GlobalIndex>=getThumbnailList(Review::Front).count()+getThumbnailList(Review::Back).count())return;// インデックスオーバー

		if(GlobalIndex<getThumbnailList(Review::Front).count()){
			for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
				Thumbnail	*Thm=getThumbnailList(Review::Front)[i];
				if(Thm->getIndexInGlobal()==GlobalIndex){
					int page	= Thm->getPage();;
					int row		= Thm->getRow();
					int column	= Thm->getColumn();
					showPage(Review::Front, page, Review::Manual, row, column);
				}
			}
		}else{
			for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
				Thumbnail	*Thm=getThumbnailList(Review::Back)[i];
				if(Thm->getIndexInGlobal()==GlobalIndex){
					int page	= Thm->getPage();;
					int row		= Thm->getRow();
					int column	= Thm->getColumn();
					showPage(Review::Back, page, Review::Manual, row, column);
				}
			}
		}
	}
}

bool ShowThumbnail::isMoveHistoryEnable()
{
	return isCurrentHistoryAllChecked();// 今は全チェックのみ確認
}

bool ShowThumbnail::moveHistory(Review::Direction direction, Review::ListLocate NGLocate, bool *historyExisted)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	if(RBase==NULL)return false;
	
	CmdReqAdjacentCurrentNG NGAdjacentCmd(GetLayersBase());// カレントNGの移動域確認
	RBase->TransmitDirectly(&NGAdjacentCmd);
	if(NGAdjacentCmd.Ret==false)return false;

	const OrganizedHistoryIndex tmp_current = NGAdjacentCmd.currentHistory();
	
	if(direction==Review::Direction::Next){
		if(NGAdjacentCmd.existNextHistory()==false){
			if(historyExisted!=NULL)*historyExisted=false;
			return false;
		}else{
			if(historyExisted!=NULL)*historyExisted=true;
		}
	}else{
		if(NGAdjacentCmd.existPreviousHistory()==false){
			if(historyExisted!=NULL)*historyExisted=false;
			return false;
		}else{
			if(historyExisted!=NULL)*historyExisted=true;
		}
	}

	CmdMoveCurrentHistoryToNGBoard MoveHistoryCmd(GetLayersBase());// NGBoard単位で移動
	MoveHistoryCmd.direction = direction;
	RBase->TransmitDirectly(&MoveHistoryCmd);
	if(MoveHistoryCmd.Ret==false)return false;

	if(MoveHistoryCmd.CurrentHistoryPtr == tmp_current)return true;// NGBoardの移動先がなかったので移動していない場合は以降の処理をしない

	if(MoveHistoryCmd.CurrentHistoryPtr==NULL)return false;

	CmdSetCurrentNGNail MoveNGNailCmd(GetLayersBase());
	MoveNGNailCmd.refType = Review::RefType::Ref_Index;
	MoveNGNailCmd.locate = NGLocate;
	RBase->TransmitDirectly(&MoveNGNailCmd);
	if(MoveNGNailCmd.Ret==false)return false;

	GUIFormBase *GBase;
	GBase = GetReviewGUIForm(ReviewGUI::Name::WholeImageForReview);
	if(GBase!=NULL){
		GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
		GBase->TransmitDirectly(&Cmd);
		GUICmdUpdateWholeImage WholeNGView(GetLayersBase());
		GBase->TransmitDirectly(&WholeNGView);
	}
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::ListPiece);
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageForReview);
	ReviewGUI::UpdateGUI(GetLayersBase(), ReviewGUI::Name::NGImageListForReview);
	GBase = GetReviewGUIForm(ReviewGUI::Name::ShowHistoryListForReview);
	if(GBase!=NULL){
		GUICmdUpdateCurrentHistory Cmd(GetLayersBase());
		GBase->TransmitDirectly(&Cmd);
	}
	updateGUI();


	return true;
}

void ShowThumbnail::slotSetCurrentThumbnail(Thumbnail *thumbnail)
{
	static QTime time;
	if(time.isNull()==true){
		time = QTime::currentTime();
		time.start();
	}else if(time.elapsed()<getMoveDelay()){
		return;
	}else{
		time = QTime::currentTime();
		time.start();
	}

	showPage(Review::Manual, thumbnail->getIndexInGlobal());
	setExpandThumbnailVisible(true);
	setFocus();
	if(getMoveMode()==_moveMode::PerPage){
		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL){
			updateInfoLabel();
			return;
		}
		CmdSetNGChecked NGCheckCmd(GetLayersBase());
		NGCheckCmd.side = getCurrentSide();
		NGCheckCmd.begin = getCurrentThumbnail()->getIndexInLocal();// 現在NGNail
		NGCheckCmd.length = 1;// そのNGのみ
		RBase->TransmitDirectly(&NGCheckCmd);
		getCurrentThumbnail()->setChecked(true);
	}
}


bool ShowThumbnail::isCurrentPageAllChecked()
{
	if(getCurrentPage()==-1)return false;
	ThumbnailList::ConstIterator it = getCurrentThumbnailPageList()[getCurrentPage()].constBegin();
	ThumbnailList::ConstIterator itend = getCurrentThumbnailPageList()[getCurrentPage()].constEnd();

	for(; it!=itend; it++){
		if((*it)->isChecked()==false){
			return false;
		}
	}
	return true;
}

bool ShowThumbnail::isPageAllChecked(int GlobalPage)
{
	if(GlobalPage<0 || getThumbnailPageList(Review::Front).count() + getThumbnailPageList(Review::Back).count() <= GlobalPage){
		return false;
	}

	Review::SideType side;
	int localPage;
	if(GlobalPage<getThumbnailPageList(Review::Front).count()){
		side = Review::Front;
		localPage = GlobalPage;
	}else{
		side = Review::Back;
		localPage = GlobalPage - getThumbnailPageList(Review::Front).count();
	}

	ThumbnailList::ConstIterator it = getThumbnailPageList(side)[localPage].constBegin();
	ThumbnailList::ConstIterator itend = getThumbnailPageList(side)[localPage].constEnd();

	for(; it!=itend; it++){
		if((*it)->isChecked()==false){
			return false;
		}
	}
	return true;
}

bool ShowThumbnail::isPageAllChecked(Review::SideType side, int LocalPage)
{
	int globalPage;
	if(side==Review::Front){
		globalPage = LocalPage;
	}else{
		globalPage = LocalPage + getThumbnailCount(Review::Front);
	}

	return isPageAllChecked(globalPage);
}

bool ShowThumbnail::isCurrentHistoryAllChecked()
{
	for(int i=0; i<getThumbnailList(Review::Front).count(); i++){
		if(getThumbnailList(Review::Front)[i]->isChecked()==false){
			return false;
		}
	}
	for(int i=0; i<getThumbnailList(Review::Back).count(); i++){
		if(getThumbnailList(Review::Back)[i]->isChecked()==false){
			return false;
		}
	}

	return true;
}

Thumbnail *ShowThumbnail::getThumbnail(Review::SideType side, int page, int row, int column)
{
	//if(side==Review::Back){
	//	Thumbnail *Thm=getThumbnailPageList(side)[0][0];
	//	if(Thm->getNGNailItem().phase==1){
	//		page-=getThumbnailPageList(Review::Front).count();
	//	}
	//}

	if(page<0 || getThumbnailPageList(side).count()<=page || row<0 || getRowCount()<=row || column<0 || getColumnCount()<=column){
		qDebug() << /**/"Index Error in Thumbnail *ShowThumbnail::getThumbnail(Review::SideType side, int page, int row, int column)";
		return NULL;
	}
	for(int i=0;i<getThumbnailPageList(side)[page].count();i++){
		Thumbnail *Thm=getThumbnailPageList(side)[page][i];
		if(Thm->getPage()==page && Thm->getRow()==row && Thm->getColumn()==column){
			return Thm;
		}
	}

	//return getThumbnailPageList(side)[page][getColumnCount()*row + column];
	return NULL;
}

Thumbnail *ShowThumbnail::getThumbnail(Review::SideType side, int LocalIndex)
{
	for(int page=0;page<getThumbnailPageList(side).count();page++){
		for(int i=0;i<getThumbnailPageList(side)[page].count();i++){
			Thumbnail *Thm=getThumbnailPageList(side)[page][i];
			if(Thm->getIndexInLocal()==LocalIndex){
				return Thm;
			}
		}
	}

	if(LocalIndex<0 || getThumbnailList(side).count()<=LocalIndex){
		qDebug() << /**/"Index Error in Thumbnail *ShowThumbnail::getThumbnail(Review::SideType side, int LocalIndex)";
		return NULL;
	}

	int page = LocalIndex/getThumbnailCountInPage();
	int row = LocalIndex%getThumbnailCountInPage()/getColumnCount();
	int column = LocalIndex%getColumnCount();

	return getThumbnail(side, page, row, column);
}

inline Thumbnail *ShowThumbnail::getThumbnail(int GlobalIndex)
{
	if(GlobalIndex<0 || getThumbnailCountAll()<=GlobalIndex){
		qDebug() << /**/"Index Error in Thumbnail *ShowThumbnail::getThumbnail(int GlobalIndex)";
		return NULL;
	}

	if(GlobalIndex<getThumbnailList(Review::Front).count()){
		return getThumbnail(Review::Front, GlobalIndex);
	}else{
		return getThumbnail(Review::Back, GlobalIndex - getThumbnailList(Review::Front).count());
	}
}
void ShowThumbnail::on_pushButtonColorNoChecked_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().UncheckedColor, NULL, LangSolver.GetString(ShowThumbnail_LS,LID_17)/*"Unchecked color"*/);
	if(Col.isValid()){
		getProperty().UncheckedColor=Col;
	}
}

void ShowThumbnail::on_pushButtonColorChecked_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().CheckedColor, NULL, LangSolver.GetString(ShowThumbnail_LS,LID_18)/*"Checked color"*/);
	if(Col.isValid()){
		getProperty().CheckedColor=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF1_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[0], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_19)/*"F1 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[0]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF2_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[1], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_20)/*"F2 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[1]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF3_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[2], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_21)/*"F3 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[2]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF4_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[3], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_22)/*"F4 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[3]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF5_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[4], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_23)/*"F5 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[4]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF6_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[5], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_24)/*"F6 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[5]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF7_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[6], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_25)/*"F7 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[6]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF8_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[7], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_26)/*"F8 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[7]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF9_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[8], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_27)/*"F9 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[8]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF10_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[9], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_28)/*"F10 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[9]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF11_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[10], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_29)/*"F11 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[10]=Col;
	}
}

void ShowThumbnail::on_pushButtonColorF12_clicked()
{
	QColor Col=QColorDialog::getColor ( getProperty().FKeyColorList[11], NULL, LangSolver.GetString(ShowThumbnail_LS,LID_30)/*"F12 color"*/);
	if(Col.isValid()){
		getProperty().FKeyColorList[11]=Col;
	}
}

ReviewPIBase *ShowThumbnail::GetReviewBase(void)
{
	return GetReviewAlgorithm();
}

void	ShowThumbnail::ShowLabelInfo(const QString &Message)
{
	LabelInfo->setText(Message);
}
