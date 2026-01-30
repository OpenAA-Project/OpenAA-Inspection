/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "LiveCameraAlgoNTSCResource.h"

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

	// �g�\��
	setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	setLineWidth(2);

	if(m_EditMode)return;

	// �t���b�J�h�~
	//setUpdatesEnabled(false);

	// �e�F�o�C�A�X�l������
	m_PlusRed = m_PlusGreen = m_PlusBlue = 0;

	// �P�x�A���C������
	for(int i=0; i<256; i++){
		m_BrightArray[i] = i;
	}

	// ���ʍX�V�p�X���b�h����
	m_Thread = new ThreadView(refleshTime);

	// �f�o�C�X�I�[�v��
	if(Open()==false)
		return;

	// ���C�u�X�^�[�g
	StartLive();

	// ����������
	CreateImageBuffer(pxd_imageXdim(), pxd_imageYdim());

	// �\���X�V�^�C�~���O���X���b�h�̃V�O�i���ɂ��킹��
	connect(m_Thread, SIGNAL(update()), this, SLOT(Update()), Qt::QueuedConnection);

	// �ݒ��_�C�A���O����
	m_SettingForm = new CameraSettingForm(&m_PlusRed, &m_PlusGreen, &m_PlusBlue);
	m_SettingForm->setWindowFlags(Qt::WindowStaysOnTopHint);// ���Ɏ��O�ɕ\��

	// �ݒ��_�C�A���O��OK�{�^�����e��Save�X���b�g�ɐڑ�
	connect(m_SettingForm, SIGNAL(accepted()), parent, SLOT(Save()));

	// �X���b�h�J�n
	StartUpdate();
}

CameraView::~CameraView()
{
	if(m_EditMode)return;

	// �X���b�h�̏���
	if(m_Thread!=NULL){
		m_Thread->stop();
		m_Thread->wait();
		delete m_Thread;
	}

	//�J�������C�u�̒��~
	StopLive();
	
	//�J�����̏I��
	if(Close()==false){
		QMessageBox::warning(this, /**/"Close Error", LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_1)/*"Camera GUI couldn't close Device."*/, QMessageBox::Ok);
	}

	// �����f�[�^�j��
	if(m_iData.size()!=0){
		for(int i=0; i<m_iData.size(); i++){
			for(int j=0; j<m_iData[i].size(); j++){
				delete m_iData[i][j];
			}
		}
	}

	// �C���[�W�C���X�^���X�j��
	m_Image = QImage();

	if(m_SettingForm)delete m_SettingForm;
}

// ���ʍX�V
void CameraView::Update()
{
	//GetCameraImageModify();
	GetCameraImageFast();
}

bool CameraView::CreateImageBuffer(int width, int height)
{
	// ���̓`�F�b�N
	if(width<=0 || height<=0)return false;

	// �c���T�C�Y�擾
	m_CapXLen = width;
	m_CapYLen = height;

	// �����f�[�^�j��
	if(m_iData.size()!=0){
		for(int i=0; i<m_iData.size(); i++){
			for(int j=0; j<m_iData[i].size(); j++){
				delete []m_iData[i][j];
			}
		}
	}

	// ����������
	m_iData.resize(height);
	for(int i=0; i<m_iData.size(); i++){
		m_iData[i].resize(3);
		for(int j=0; j<m_iData[i].size(); j++){
			m_iData[i][j] = new unsigned char[width];
		}
	}

	// �C���[�W�C���X�^���X�Đ���
	m_Image = QImage(width, height, QImage::Format_RGB32);

	return true;
}

void CameraView::ShowSettingForm()
{
	if(m_SettingForm->isVisible()){
		m_SettingForm->setVisible(false);
	}else{// ���\���̏ꍇ�ɍĕ\��
		m_SettingForm->ResetRGB(&m_PlusRed, &m_PlusGreen, &m_PlusBlue);
		m_SettingForm->setVisible(true);
	}
}

// �J�����摜�̎擾�E�\��
// ������(�R���X�g���N�^��setUpdatesEnabled(false)�̃R�����g���O������)
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

// �J�����ݒ蔽�f��
// QImage�ɃJ�����摜���R�s�[����RGB�𒲐�����
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

	//�f�[�^�ւ̃A�N�Z�X
	//#pragma omp parallel
	{
		//#pragma omp for
		for(int y=0;y<m_CapYLen;y++){
			//unsigned char *bufR = new unsigned char[XLength];				// �T�C�Y>= # �s�N�Z�� per AOI���C��
			//unsigned char *bufG = new unsigned char[XLength];				// �T�C�Y>= # �s�N�Z�� per AOI���C��
			//unsigned char *bufB = new unsigned char[XLength];				// �T�C�Y>= # �s�N�Z�� per AOI���C��

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

//�P�x�A���C���ݒ� 255
void	CameraView::SetBrightness(int BArray[])
{
	memcpy(m_BrightArray,BArray,sizeof(int[256]));
}

// �J�����f�o�C�X�̃I�[�v��
bool CameraView::Open()
{
	//�W����NTSC�t�H�[�}�b�g�ŃI�[�v��
	if (pxd_PIXCIopen(/**/"", /**/"", /**/"./SV5.fmt") < 0){
		pxd_mesgFault(1);
		return false;
	}
	return true;
}

// �J�����f�o�C�X�̃N���[�Y
bool	CameraView::Close()
{
	pxd_PIXCIclose();
	return true;
}

//�X�i�b�v�V���b�g�B�e
bool	CameraView::SingleShot()
{
	int err;
	err = pxd_doSnap(UNITSMAP, 1, 0);
	if (err < 0)
		return false;
	return true;
}

//���C�u���~
bool	CameraView::StopLive()
{
	pxd_goUnLive(UNITSMAP);
	StopUpdate();
	return true;
}

//���C�u�J�n
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
	// GUI�\���t���Řg�����Ă����ق������₷��
	m_CameraView.setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	m_CameraView.setLineWidth(2);

	// �e�ۑ�
	m_parent = parent;

	if(!Load()){
		m_CameraView.SetRGB(0, 0, 0);
		Save();
	}

	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));

	// �R���e�L�X�g���j���[�쐬
	m_ContextMenu = new QMenu(this);

	// �J�����ݒ��A�N�V�����ǉ�
	m_SettingAction = new QAction(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_2)/*"�J�����ݒ�"*/, this);
	m_SettingAction->setStatusTip(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_3)/*"�J�����f���Ɋւ����ݒ����s���܂�"*/);
	connect(m_SettingAction, SIGNAL(triggered()), this, SLOT(SettingAction()));
	m_ContextMenu->addAction(m_SettingAction);

	m_ResetAction = new QAction(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_4)/*"�J�������Z�b�g"*/, this);
	m_ResetAction->setStatusTip(LangSolver.GetString(LiveCameraAlgoNTSC_LS,LID_5)/*"�J�������C�u���ăX�^�[�g���܂�"*/);
	connect(m_ResetAction, SIGNAL(triggered()), this, SLOT(RestartAction()));
	m_ContextMenu->addAction(m_ResetAction);

	//m_SnapAction = new QAction(tr(/**/"�X�i�b�v�e�X�g"), this);
	//m_SnapAction->setStatusTip(/**/"�X�i�b�v�C���[�W���e�X�g���܂�");
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
	//�J�����̏�����
	//�e�F�o�C�A�X�l������
	m_PlusRed=m_PlusGreen=m_PlusBlue=0;

	//�P�x�A���C������
	for(int i=0;i<256;i++){
		m_BrightArray[i]=i;
	}

	//�J�����r���[�E�B�W�F�b�g�̃T�C�Y���ύX
	m_CameraView.resize(width(), height());
}

void	LiveCameraAlgoNTSC::ResizeAction()
{
	m_CameraView.resize(this->size());
}

//�eRGB�̃o�C�A�X�l�ݒ�
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
	// �Z�[�u
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
	// ���[�h
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