#include "LiveCameraAlgoNTSCResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\LiveCameraAlgoNTSC\LiveCameraAlgoNTSC.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <Windows.h>
#include <QMenu>
#include "LiveCameraAlgoNTSC.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XReviewCommonPacket.h"
#include "LiveCameraCommonPacket.h"

#include "XGUIReviewGlobal.h"
#include "ReviewStructurePacket.h"

#include <QDebug>


extern /**/"C" {
	#include "xcliball.h"
	#include "xclibex2.h"
}

#if !defined(UNITS)
    #define UNITS	1
#endif
#define UNITSMAP    ((1<<UNITS)-1)  /* shorthand - bitmap of all units */



static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"LiveCameraAlgoNTSC";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Live Algo NTSC-Camera");
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new LiveCameraAlgoNTSC(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/LiveCameraAlgoNTSC.PNG")));
}

inline	BYTE	Clip255(int d)
{
	if(d<0)
		return 0;
	if(d>255)
		return 255;
	return d;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==============================================================================================================
//ThreadView
//==============================================================================================================

void ThreadView::run()
{
	while(!m_flg_stop){
		if(m_flg_updateEnable)
			emit update();
		msleep(m_intervalTime);
	}
}

//==============================================================================================================
//CameraView
//==============================================================================================================

CameraView::CameraView(QWidget *parent, bool EditMode, int refleshTime)
	:QLabel(parent),m_Image(),m_Thread(NULL),m_SettingForm(NULL),m_paintWidget(this)
{
	m_EditMode = EditMode;

	// 枠表示
	setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	setLineWidth(2);

	if(m_EditMode)return;

	// フリッカ防止
	//setUpdatesEnabled(false);

	// 各色バイアス値初期化
	m_PlusRed = m_PlusGreen = m_PlusBlue = 0;

	// 輝度アレイ初期化
	for(int i=0; i<256; i++){
		m_BrightArray[i] = i;
	}

	// 画面更新用スレッド生成
	m_Thread = new ThreadView(refleshTime);

	// デバイスオープン
	if(Open()==false)
		return;

	// ライブスタート
	StartLive();

	// メモリ生成
	CreateImageBuffer(pxd_imageXdim(), pxd_imageYdim());

	// 表示更新タイミングをスレッドのシグナルにあわせる
	connect(m_Thread, SIGNAL(update()), this, SLOT(Update()), Qt::QueuedConnection);

	// 設定ダイアログ生成
	m_SettingForm = new CameraSettingForm(&m_PlusRed, &m_PlusGreen, &m_PlusBlue);
	m_SettingForm->setWindowFlags(Qt::WindowStaysOnTopHint);// 常に手前に表示

	// 設定ダイアログのOKボタンを親のSaveスロットに接続
	connect(m_SettingForm, SIGNAL(accepted()), parent, SLOT(Save()));

	// スレッド開始
	StartUpdate();
}

CameraView::~CameraView()
{
	if(m_EditMode)return;

	// スレッドの消去
	if(m_Thread!=NULL){
		m_Thread->stop();
		m_Thread->wait();
		delete m_Thread;
	}

	//カメラライブの停止
	StopLive();
	
	//カメラの終了
	if(Close()==false){
		QMessageBox::warning(this, /**/"Close Error", LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_1)/*"Camera GUI couldn't close Device."*/, QMessageBox::Ok);
	}

	// 既存データ破棄
	if(m_iData.size()!=0){
		for(int i=0; i<m_iData.size(); i++){
			for(int j=0; j<m_iData[i].size(); j++){
				delete m_iData[i][j];
			}
		}
	}

	// イメージインスタンス破棄
	m_Image = QImage();

	if(m_SettingForm)delete m_SettingForm;
}

// 画面更新
void CameraView::Update()
{
	//GetCameraImageModify();
	GetCameraImageFast();
}

bool CameraView::CreateImageBuffer(int width, int height)
{
	// 入力チェック
	if(width<=0 || height<=0)return false;

	// 縦横サイズ取得
	m_CapXLen = width;
	m_CapYLen = height;

	// 既存データ破棄
	if(m_iData.size()!=0){
		for(int i=0; i<m_iData.size(); i++){
			for(int j=0; j<m_iData[i].size(); j++){
				delete []m_iData[i][j];
			}
		}
	}

	// メモリ生成
	m_iData.resize(height);
	for(int i=0; i<m_iData.size(); i++){
		m_iData[i].resize(3);
		for(int j=0; j<m_iData[i].size(); j++){
			m_iData[i][j] = new unsigned char[width];
		}
	}

	// イメージインスタンス再生成
	m_Image = QImage(width, height, QImage::Format_RGB32);

	return true;
}

void CameraView::ShowSettingForm()
{
	if(m_SettingForm->isVisible()){
		m_SettingForm->setVisible(false);
	}else{// 非表示の場合に再表示
		m_SettingForm->ResetRGB(&m_PlusRed, &m_PlusGreen, &m_PlusBlue);
		m_SettingForm->setVisible(true);
	}
}

// カメラ画像の取得・表示
// 高速版(コンストラクタのsetUpdatesEnabled(false)のコメントを外すこと)
void CameraView::GetCameraImageFast()
{
	static QImage preImg;

	if(m_paintWidget==NULL){
		return;
	}

	QPixmap pix;

	HDC hDC = m_paintWidget->getDC();
	HDC memDC = CreateCompatibleDC(hDC);
	
	SetStretchBltMode(hDC, STRETCH_DELETESCANS);
	SetStretchBltMode(memDC, STRETCH_DELETESCANS);

	QSize s(pxd_imageXdim(), pxd_imageYdim());

	s.scale(m_paintWidget->size(), Qt::KeepAspectRatio);

	if(preImg.size()!=s){
		preImg = QImage(s, QImage::Format_RGB32);
	}

	HBITMAP memBmp = CreateCompatibleBitmap(hDC, s.width(), s.height());

	SelectObject(memDC, memBmp);

	pxbuffer_t  buf = 1;
	
	pxd_renderStretchDIBits(1, buf, 0, 0, -1, -1, 0,
		memDC, 0, 0, s.width(), s.height(), 0);

	pix = QPixmap::fromWinHBITMAP(memBmp);

	m_paintWidget->releaseDC(hDC);

	DeleteDC(memDC);
	DeleteObject(memBmp);

	QImage img = pix.toImage();
	if(img==preImg){
		Restart();
	}
	preImg = img;

	if(pix.isNull()==false && m_PlusRed==0 && m_PlusGreen==0 && m_PlusBlue==0){
		m_paintWidget->setPixmap(pix);
		if(m_paintWidget!=this){
			m_paintWidget->update();
		}
	}else{
		QRgb *rgbData = (QRgb*)img.bits();
		int count = img.byteCount() / sizeof(QRgb);
		for(int i=0; i<count; i++){
			QRgb *rgb = rgbData + i;
			*rgb = qRgb(
				Clip255(qRed(*rgb) + m_PlusRed),
				Clip255(qGreen(*rgb) + m_PlusGreen),
				Clip255(qBlue(*rgb) + m_PlusBlue)
				);
		}
		m_paintWidget->setPixmap(QPixmap::fromImage(img));
		if(m_paintWidget!=this){
			m_paintWidget->update();
		}
	}
}

// カメラ設定反映版
// QImageにカメラ画像をコピーしてRGBを調整する
void CameraView::GetCameraImageModify()
{
	static QImage prePix;

	prePix = m_Image;

	if(m_paintWidget==NULL){
		return;
	}

	m_Thread->setUpdateEnable(false);
	m_paintWidget->setUpdatesEnabled(false);

	if(m_Image.size()!=QSize(m_CapYLen, m_CapXLen)){
		m_Image = QImage(m_CapYLen, m_CapXLen, QImage::Format_RGB32);
	}

	//データへのアクセス
	//#pragma omp parallel
	{
		//#pragma omp for
		for(int y=0;y<m_CapYLen;y++){
			//unsigned char *bufR = new unsigned char[XLength];				// サイズ>= # ピクセル per AOIライン
			//unsigned char *bufG = new unsigned char[XLength];				// サイズ>= # ピクセル per AOIライン
			//unsigned char *bufB = new unsigned char[XLength];				// サイズ>= # ピクセル per AOIライン

			//pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, bufR, XLength, /**/"RofRGB");
			//pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, bufG, XLength, /**/"GofRGB");
			//pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, bufB, XLength, /**/"BofRGB");

			pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, m_iData[y][0], m_CapXLen, /**/"RofRGB");
			pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, m_iData[y][1], m_CapXLen, /**/"GofRGB");
			pxd_readuchar(UNITSMAP, 1, 0, y, -1, y+1, m_iData[y][2], m_CapXLen, /**/"BofRGB");

			QRgb *pYLine=(QRgb*)m_Image.scanLine(y);

			#pragma omp parallel
			{
				#pragma omp for
				for(int x=0;x<m_CapXLen;x++){
					pYLine[x]=qRgb(
						Clip255(m_BrightArray[m_iData[y][0][x]]+m_PlusRed),
						Clip255(m_BrightArray[m_iData[y][1][x]]+m_PlusGreen),
						Clip255(m_BrightArray[m_iData[y][2][x]]+m_PlusBlue)
						);
				}
			}

			//delete bufR;
			//delete bufG;
			//delete bufB;
		}
	}

	m_paintWidget->setPixmap(QPixmap::fromImage(m_Image.scaled(m_paintWidget->width() - m_paintWidget->lineWidth()*2, m_paintWidget->height() - m_paintWidget->lineWidth()*2, Qt::KeepAspectRatio)));
	m_paintWidget->update();

	if(prePix.isNull()==false && m_Image.isNull()==false && m_Image == prePix){
		Restart();
	}

	m_paintWidget->setUpdatesEnabled(true);
	m_Thread->setUpdateEnable(true);
}

bool CameraView::GetCameraImage(QImage *image)
{
	if(image==NULL)return false;
	if(image->width()<=0 || image->height()<=0)return false;

	m_Thread->stop();
	m_Thread->wait();
	m_Thread->setStopFlag(false);
	StopLive();

	if(!SingleShot()){
		StartLive();
		m_Thread->start();
		return false;
	}

	GetCameraImageModify();

	*image = m_Image.scaled(image->size(), Qt::KeepAspectRatio);

	StartLive();
	m_Thread->start();

	return true;
}

//輝度アレイを設定 255
void	CameraView::SetBrightness(int BArray[])
{
	memcpy(m_BrightArray,BArray,sizeof(int[256]));
}

// カメラデバイスのオープン
bool CameraView::Open()
{
	//標準のNTSCフォーマットでオープン
	if (pxd_PIXCIopen(/**/"", /**/"", /**/"./SV5.fmt") < 0){
		pxd_mesgFault(1);
		return false;
	}
	return true;
}

// カメラデバイスのクローズ
bool	CameraView::Close()
{
	pxd_PIXCIclose();
	return true;
}

//スナップショット撮影
bool	CameraView::SingleShot()
{
	int err;
	err = pxd_doSnap(UNITSMAP, 1, 0);
	if (err < 0)
		return false;
	return true;
}

//ライブ停止
bool	CameraView::StopLive()
{
	pxd_goUnLive(UNITSMAP);
	StopUpdate();
	return true;
}

//ライブ開始
bool	CameraView::StartLive()
{
	pxd_goLive(UNITSMAP, 1);
	StartUpdate();
	return true;
}

void	CameraView::Restart()
{
	StopUpdate();
	StopLive();
	Close();
	Open();
	StartLive();
	StartUpdate();
}

void	CameraView::StartUpdate()
{
	if(m_Thread->isRunning())
		return;
	m_Thread->setStopFlag(false);
	m_Thread->start();
}

void	CameraView::StopUpdate()
{
	if(!m_Thread->isRunning())
		return;
	m_Thread->stop();
	m_Thread->wait();
}

void	CameraView::SetRGB(int r, int g, int b)
{
	m_PlusRed = r;
	m_PlusGreen = g;
	m_PlusBlue = b;
}

int *CameraView::GetPlusRedPtr()
{
	return &m_PlusRed;
}

int *CameraView::GetPlusGreenPtr()
{
	return &m_PlusGreen;
}

int *CameraView::GetPlusBluePtr()
{
	return &m_PlusBlue;
}

int		CameraView::GetPlusRed()
{
	return m_PlusRed;
}

int		CameraView::GetPlusGreen()
{
	return m_PlusGreen;
}

int		CameraView::GetPlusBlue()
{
	return m_PlusBlue;
}

void	CameraView::SetWindow(QLabel *target)
{
	if(m_paintWidget==target){
		return;
	}

	if(StopLive()==false){
		return;
	}

	if(target==NULL){
		m_paintWidget = this;
	}else{
		m_paintWidget = target;
	}

	StartLive();
}

//==============================================================================================================
//LiveCameraAlgoNTSC
//==============================================================================================================
LiveCameraAlgoNTSC::LiveCameraAlgoNTSC(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent),m_CameraView(this, GetEditMode(), 1000/60.0)
{
	// GUI貼り付けで枠がついていたほうが見やすい
	m_CameraView.setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	m_CameraView.setLineWidth(2);

	// 親保存
	m_parent = parent;

	if(!Load()){
		m_CameraView.SetRGB(0, 0, 0);
		Save();
	}

	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	// コンテキストメニュー作成
	m_ContextMenu = new QMenu(this);

	// カメラ設定アクション追加
	m_SettingAction = new QAction(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_2)/*"カメラ設定"*/, this);
	m_SettingAction->setStatusTip(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_3)/*"カメラ映像に関する設定を行います"*/);
	connect(m_SettingAction, SIGNAL(triggered()), this, SLOT(SettingAction()));
	m_ContextMenu->addAction(m_SettingAction);

	m_ResetAction = new QAction(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_4)/*"カメラリセット"*/, this);
	m_ResetAction->setStatusTip(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_5)/*"カメラライブを再スタートします"*/);
	connect(m_ResetAction, SIGNAL(triggered()), this, SLOT(RestartAction()));
	m_ContextMenu->addAction(m_ResetAction);

	//m_SnapAction = new QAction(tr(/**/"スナップテスト"), this);
	//m_SnapAction->setStatusTip(/**/"スナップイメージをテストします");
	//connect(m_SnapAction, SIGNAL(triggered()), this, SLOT(SnapAction()));
	//m_ContextMenu->addAction(m_SnapAction);

	initProperty();
}

LiveCameraAlgoNTSC::~LiveCameraAlgoNTSC(void)
{
	if(m_ContextMenu)delete m_ContextMenu;
}

void	LiveCameraAlgoNTSC::Prepare(void)
{
	//カメラの初期化
	//各色バイアス値初期化
	m_PlusRed=m_PlusGreen=m_PlusBlue=0;

	//輝度アレイ初期化
	for(int i=0;i<256;i++){
		m_BrightArray[i]=i;
	}

	//カメラビューウィジェットのサイズを変更
	m_CameraView.resize(width(), height());
}

void	LiveCameraAlgoNTSC::ResizeAction()
{
	m_CameraView.resize(this->size());
}

//各RGBのバイアス値設定
void	LiveCameraAlgoNTSC::SetPlusRGB(int Red,int Green,int Blue)
{
	m_PlusRed	=Red;
	m_PlusGreen	=Green;
	m_PlusBlue	=Blue;
}

void	LiveCameraAlgoNTSC::contextMenuEvent(QContextMenuEvent *event)
{
	if(GetEditMode())return;

	QPoint pos;
	if(m_parent!=NULL){
		pos = event->pos() + m_parent->geometry().topLeft() + geometry().topLeft();
	}else{
		pos = event->pos() + geometry().topLeft();
	}

	m_ContextMenu->exec(pos);
}

void	LiveCameraAlgoNTSC::SettingAction()
{
	m_CameraView.ShowSettingForm();
}

void	LiveCameraAlgoNTSC::RestartAction()
{
	m_CameraView.Restart();
}

void	LiveCameraAlgoNTSC::SnapAction()
{
	QImage image(m_CameraView.size(), QImage::Format_RGB32);
	if(m_CameraView.GetCameraImage(&image))
		image.save(/**/"SnapTest.bmp");
}

bool	LiveCameraAlgoNTSC::Save()
{
	// セーブ
	QFile file(/**/"Review-LiveCameraAlgoNTSC.dat");
	if(file.open(QIODevice::WriteOnly)==false){
		return false;
	}

	if(!::Save(&file, (int32)m_CameraView.GetPlusRed())){
		return false;
	}

	if(!::Save(&file, (int32)m_CameraView.GetPlusGreen())){
		return false;
	}

	if(!::Save(&file, (int32)m_CameraView.GetPlusBlue())){
		return false;
	}

	return true;
}

bool	LiveCameraAlgoNTSC::Load()
{
	// ロード
	QFile file(/**/"Review-LiveCameraAlgoNTSC.dat");
	if(file.open(QIODevice::ReadOnly)==false){
		return false;
	}

	int32 r,g,b;
	if(!::Load(&file, r)){
		return false;
	}

	if(!::Load(&file, g)){
		return false;
	}

	if(!::Load(&file, b)){
		return false;
	}

	m_CameraView.SetRGB(r, g, b);

	return true;
}

void	LiveCameraAlgoNTSC::TransmitDirectly(GUIDirectMessage *packet){
	ReviewCommonPacket::CmdReqSettingPropertyDialog *CmdReqSettingPropertyDialogVar = dynamic_cast<ReviewCommonPacket::CmdReqSettingPropertyDialog *>(packet);
	if(CmdReqSettingPropertyDialogVar!=NULL){
		//CmdReqSettingPropertyDialogVar->dialog = getPropertyDialog();
		CmdReqSettingPropertyDialogVar->setDialog(NULL);
		CmdReqSettingPropertyDialogVar->setGroupName(ReviewGUI::PropertyGroupName::VRS);
		CmdReqSettingPropertyDialogVar->setGUIName(ReviewGUI::Name::LiveCameraAlgoNTSC);
		return;
	}

	GUICmdSetCameraWindow *GUICmdSetCameraWindowVar = dynamic_cast<GUICmdSetCameraWindow *>(packet);
	if(GUICmdSetCameraWindowVar!=NULL){
		m_CameraView.SetWindow(GUICmdSetCameraWindowVar->label);
		GUICmdSetCameraWindowVar->ret = true;
		return;
	}

	GUICmdResetCameraWindow *GUICmdResetCameraWindowVar = dynamic_cast<GUICmdResetCameraWindow *>(packet);
	if(GUICmdResetCameraWindowVar!=NULL){
		m_CameraView.SetWindow(NULL);
		GUICmdResetCameraWindowVar->ret = true;
		return;
	}
}

void LiveCameraAlgoNTSC::mousePressEvent(QMouseEvent *event)
{
	GUIFormBase::mousePressEvent(event);

	if(GetEditMode()==true){
		return;
	}

	if((event->buttons() & Qt::MouseButton::LeftButton)==0)return;

	qreal x_rate = event->pos().x() / (qreal)width();
	qreal y_rate = event->pos().y() / (qreal)height();

	qreal x = 2*x_rate - 1;
	qreal y = 2*y_rate - 1;

	CmdMoveVRSOnCameraView moveVRS(GetLayersBase());

	moveVRS.x = x;
	moveVRS.y = y;

	AlgorithmBase *RBase = GetReviewAlgorithmBase();
	RBase->TransmitDirectly( &moveVRS );
}
