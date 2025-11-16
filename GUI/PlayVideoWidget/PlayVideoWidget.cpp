/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PlayVideoWidget\PlayVideoWidget.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PlayVideoWidget.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

#define SLIDER_RANGE 8

const   char* sRoot =/**/"Video";
const   char* sName =/**/"PlayWidget";



DEFFUNCEX	bool	DLL_GetName(QString& Root, QString& Name)
{
    Root = sRoot;
    Name = sName;
    return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
    return(/**/"Widget to play movie(video)");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage& Pkg, int LanguageCode)
{
    //LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase* Base)
{
    Q_INIT_RESOURCE(ServiceLib);

    return true;
}
DEFFUNCEX	void	DLL_Close(void)
{

    Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase* DLL_CreateInstance(LayersBase* Base, QWidget* parent)
{
    return(new PlayVideoWidget(Base, parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase* Instance)
{
    delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void* Instance, struct	PropertyClass Data[], WORD	maxDataDim)
{
    if (maxDataDim < 0)
        return(-1);

    return(0);
}

DEFFUNCEX	QIcon* DLL_GetIcon(void)
{
    return(new QIcon(QPixmap(/**/":Resources/PlayVideoWidget.png")));
}

//==================================================================================================

MediaVideoWidget::MediaVideoWidget(PlayVideoWidget* player, QWidget* parent) :
    QVideoWidget(parent), m_player(player), m_action(this)
{
    m_action.setCheckable(true);
    m_action.setChecked(false);
    m_action.setShortcut(QKeySequence(Qt::AltModifier + Qt::Key_Return));
    m_action.setShortcutContext(Qt::WindowShortcut);
    connect(&m_action, SIGNAL(toggled(bool)), SLOT(setFullScreen(bool)));
    addAction(&m_action);
    setAcceptDrops(true);
}

void MediaVideoWidget::setFullScreen(bool enabled)
{
    setFullScreen(enabled);
    emit fullScreenChanged(enabled);
}

void MediaVideoWidget::mouseDoubleClickEvent(QMouseEvent* e)
{
    setFullScreen(!isFullScreen());
    QVideoWidget::event(e);
}

void MediaVideoWidget::keyPressEvent(QKeyEvent* e)
{
    if (!e->modifiers()) {
        // On non-QWERTY Symbian key-based devices, there is no space key.
        // The zero key typically is marked with a space character.
        if (e->key() == Qt::Key_Space || e->key() == Qt::Key_0) {
            m_player->playPause();
            e->accept();
            return;
        }

        // On Symbian devices, there is no key which maps to Qt::Key_Escape
        // On devices which lack a backspace key (i.e. non-QWERTY devices),
        // the 'C' key maps to Qt::Key_Backspace
        else if (e->key() == Qt::Key_Escape || e->key() == Qt::Key_Backspace) {
            setFullScreen(false);
            e->accept();
            return;
        }
    }
    QVideoWidget::keyPressEvent(e);
}

bool MediaVideoWidget::event(QEvent* e)
{
    switch (e->type())
    {
    case QEvent::Close:
        //we just ignore the cose events on the video widget
        //this prevents ALT+F4 from having an effect in fullscreen mode
        e->ignore();
        return true;
    case QEvent::MouseMove:
#ifndef QT_NO_CURSOR
        unsetCursor();
#endif
        //fall through
    case QEvent::WindowStateChange:
    {
        //we just update the state of the checkbox, in case it wasn't already
        m_action.setChecked(windowState() & Qt::WindowFullScreen);
        const Qt::WindowFlags flags = m_player->windowFlags();
        if (windowState() & Qt::WindowFullScreen) {
            m_timer.start(1000, this);
        }
        else {
            m_timer.stop();
#ifndef QT_NO_CURSOR
            unsetCursor();
#endif
        }
    }
    break;
    default:
        break;
    }

    return QVideoWidget::event(e);
}

void MediaVideoWidget::timerEvent(QTimerEvent* e)
{
    if (e->timerId() == m_timer.timerId()) {
        //let's store the cursor shape
#ifndef QT_NO_CURSOR
        setCursor(Qt::BlankCursor);
#endif
    }
}

void MediaVideoWidget::dropEvent(QDropEvent* e)
{
    m_player->handleDrop(e);
}

void MediaVideoWidget::dragEnterEvent(QDragEnterEvent* e) {
    if (e->mimeData()->hasUrls())
        e->acceptProposedAction();
}

//==================================================================================================

PlayVideoWidget::PlayVideoWidget(LayersBase* Base, QWidget* parent)
    :GUIFormBase(Base, parent)
{
    VideoWidget = new MediaVideoWidget(this);
    VideoWidget->setParent(this);
    LastState   =QMediaPlayer::StoppedState;

    Player  = new QMediaPlayer(this);
    Player->setVideoOutput(VideoWidget);

    bool    DbgRet=connect(Player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)), this, SLOT(stateChanged(QMediaPlayer::PlaybackState)));
    int Error = 0;
    if (!connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()))) {
        Error = 1;
    }
}

PlayVideoWidget::~PlayVideoWidget()
{
    delete	VideoWidget;
    delete	Player;
}

void	PlayVideoWidget::Prepare(void)
{
}
void	PlayVideoWidget::ReadyParam(void)
{
    //QVBoxLayout *videoLayout = new QVBoxLayout();
    //videoLayout->addWidget(m_videoWidget);
    //videoLayout->setContentsMargins(0, 0, 0, 0);
    //setLayout(videoLayout);
}

void	PlayVideoWidget::ResizeAction()
{
    int	W = width();
    int	H = height();
    VideoWidget->setGeometry(0, 0, W, H);

    //slider->move(width(), 0);
    //volume->move(width(), 0);
}

void PlayVideoWidget::handleDrop(QDropEvent* e)
{
    Player->play();
}

void PlayVideoWidget::dropEvent(QDropEvent* e)
{
    if (e->mimeData()->hasUrls() && e->proposedAction() != Qt::LinkAction) {
        e->acceptProposedAction();
        handleDrop(e);
    }
    else {
        e->ignore();
    }
}

void PlayVideoWidget::dragEnterEvent(QDragEnterEvent* e)
{
    dragMoveEvent(e);
}

void PlayVideoWidget::dragMoveEvent(QDragMoveEvent* e)
{
    if (e->mimeData()->hasUrls()) {
        if (e->proposedAction() == Qt::CopyAction || e->proposedAction() == Qt::MoveAction) {
            e->acceptProposedAction();
        }
    }
}

void PlayVideoWidget::playPause()
{
    if (Player->playbackState() == QMediaPlayer::PlayingState)
        Player->pause();
    else {
        if (Player->position() == Player->duration())
            Player->setPosition(0);
        Player->setPlaybackRate(1.0);
        Player->play();
    }
}

void PlayVideoWidget::setFile(const QString& fileName)
{
    setWindowTitle(fileName.right(fileName.length() - fileName.lastIndexOf('/') - 1));
    Player->setSource(QUrl::fromLocalFile(fileName));
    Player->play();
}

void PlayVideoWidget::updateInfo()
{
}

void PlayVideoWidget::updateTime()
{
    long len = Player->duration();
    long pos = Player->position();
    QString timeString;
    if (pos || len)
    {
        int sec = pos / 1000;
        int min = sec / 60;
        int hour = min / 60;
        int msec = pos;

        QTime playTime(hour % 60, min % 60, sec % 60, msec % 1000);
        sec = len / 1000;
        min = sec / 60;
        hour = min / 60;
        msec = len;

        QTime stopTime(hour % 60, min % 60, sec % 60, msec % 1000);
        QString timeFormat = "m:ss";
        if (hour > 0)
            timeFormat = "h:mm:ss";
        timeString = playTime.toString(timeFormat);
        if (len)
            timeString += " / " + stopTime.toString(timeFormat);
    }
    // timeLabel->setText(timeString);
}

void PlayVideoWidget::rewind()
{
    Player->setPosition(0);
}

void PlayVideoWidget::forward()
{
    Player->setPlaybackRate(2.0);
    Player->play();
}

bool PlayVideoWidget::playPauseForDialog()
{
    // If we're running on a small screen, we want to pause the video when
    // popping up dialogs. We neither want to tamper with the state if the
    // user has paused.
    //if (m_smallScreen && m_MediaObject.hasVideo()) {
    if (Player->isAvailable() && Player->hasVideo()) {
        if (QMediaPlayer::PlayingState == Player->playbackState()) {
            Player->pause();
            return true;
        }
    }
    return false;
}

qint64 PlayVideoWidget::openFile(QString& fileName)
{
    const bool hasPausedForDialog = playPauseForDialog();

    if (hasPausedForDialog)
        Player->play();

    Player->setSource(QUrl::fromLocalFile(fileName));
    return Player->duration();
}
//
//void PlayVideoWidget::setSaturation(int val)
//{
//    VideoWidget->setSaturation(val / qreal(SLIDER_RANGE));
//}
//
//void PlayVideoWidget::setHue(int val)
//{
//    VideoWidget->setHue(val / qreal(SLIDER_RANGE));
//}
//
//void PlayVideoWidget::setBrightness(int val)
//{
//    VideoWidget->setBrightness(val / qreal(SLIDER_RANGE));
//}
//
//void PlayVideoWidget::setContrast(int val)
//{
//    VideoWidget->setContrast(val / qreal(SLIDER_RANGE));
//}

void PlayVideoWidget::finished()
{
}

int VDbg=0;
void PlayVideoWidget::stateChanged(QMediaPlayer::PlaybackState state)
{
    if(state==QMediaPlayer::StoppedState){
        VDbg++;
    }
}

void	PlayVideoWidget::TransmitDirectly(GUIDirectMessage* packet)
{
    CmdVideo_Rewind* CmdVideo_RewindVar = dynamic_cast<CmdVideo_Rewind*>(packet);
    if (CmdVideo_RewindVar != NULL) {
        rewind();
        return;
    }
    CmdVideo_Forward* CmdVideo_ForwardVar = dynamic_cast<CmdVideo_Forward*>(packet);
    if (CmdVideo_ForwardVar != NULL) {
        forward();
        return;
    }
    CmdVideo_Play* CmdVideo_PlayVar = dynamic_cast<CmdVideo_Play*>(packet);
    if (CmdVideo_PlayVar != NULL) {
        playPause();
        return;
    }
    CmdVideo_LoadFile* CmdVideo_LoadFileVar = dynamic_cast<CmdVideo_LoadFile*>(packet);
    if (CmdVideo_LoadFileVar != NULL) {
        CmdVideo_LoadFileVar->TotalTime = openFile(CmdVideo_LoadFileVar->FileName);
        return;
    }
    CmdVideo_GetCurrentTime* CmdVideo_GetCurrentTimeVar = dynamic_cast<CmdVideo_GetCurrentTime*>(packet);
    if (CmdVideo_GetCurrentTimeVar != NULL) {
        QMediaPlayer::PlaybackState state=Player->playbackState();
        if (state == QMediaPlayer::PlayingState) {
            CmdVideo_GetCurrentTimeVar->IsPlaying = true;
            qint64  duration=Player->duration();
            qint64  position=Player->position();
            CmdVideo_GetCurrentTimeVar->MaxTime     = duration;
            CmdVideo_GetCurrentTimeVar->CurrentTime = position;
            LastPosition=position;
            LastDuration=duration;
        }
        else {
            if(LastState==QMediaPlayer::PlayingState){
                CmdVideo_GetCurrentTimeVar->MaxTime     = LastDuration;
                CmdVideo_GetCurrentTimeVar->CurrentTime = LastDuration;
                CmdVideo_GetCurrentTimeVar->IsPlaying = true;
            }
            else{
                CmdVideo_GetCurrentTimeVar->MaxTime = Player->duration();
                CmdVideo_GetCurrentTimeVar->CurrentTime = Player->position();
                CmdVideo_GetCurrentTimeVar->IsPlaying = false;
            }
        }
        LastState=state;
        return;
    }
    CmdVideo_SetPlaybackRate* CmdVideo_SetPlaybackRateVar = dynamic_cast<CmdVideo_SetPlaybackRate*>(packet);
    if (CmdVideo_SetPlaybackRateVar != NULL) {
        Player->setPlaybackRate(CmdVideo_SetPlaybackRateVar->PlaybackRate);
        return;
    }
    CmdVideo_GetPlaybackRate* CmdVideo_GetPlaybackRateVar = dynamic_cast<CmdVideo_GetPlaybackRate*>(packet);
    if (CmdVideo_GetPlaybackRateVar != NULL) {
        CmdVideo_GetPlaybackRateVar->PlaybackRate= Player->playbackRate();
        return;
    }
}