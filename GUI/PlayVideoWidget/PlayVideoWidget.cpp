/*
 * Copyright (C) 2026
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


#include "PlayVideoWidget.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XVideoCommon.h"
#include "XVideoWidget.h"

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
    Player		=NULL;
    VideoWidget =NULL;
    glWidget	=NULL;

    LastDuration=0;
}

PlayVideoWidget::~PlayVideoWidget()
{
    delete	VideoWidget;
    delete	Player;
    delete  glWidget;
}

void	PlayVideoWidget::Prepare(void)
{
    //VideoWidget = new MediaVideoWidget(this);
    //VideoWidget->setParent(this);
    //LastState   =QMediaPlayer::StoppedState;
    //
    //Player  = new QMediaPlayer(this);
    //Player->setVideoOutput(VideoWidget);
    //
    //bool    DbgRet=connect(Player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)), this, SLOT(stateChanged(QMediaPlayer::PlaybackState)));
    
    glWidget=new MMFVideoWidget(this);
    glWidget->setParent(this);
    
    int Error = 0;
    if (!connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()))) {
        Error = 1;
    }
	connect(glWidget,SIGNAL(SignalBlaybackFinished()),this,SLOT(SlotPlaybackFinished()));
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
    if(VideoWidget!=NULL){
        VideoWidget->setGeometry(0, 0, W, H);
    }
    if(glWidget!=NULL){
        glWidget->setGeometry(0, 0, W, H);
    }
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

void PlayVideoWidget::SlotPlaybackFinished()
{
	emit SignalBlaybackFinished();
}

void PlayVideoWidget::playPause()
{
    if(Player!=NULL){
        if (Player->playbackState() == QMediaPlayer::PlayingState)
            Player->pause();
        else {
            if (Player->position() == Player->duration())
                Player->setPosition(0);
            Player->setPlaybackRate(1.0);
            Player->play();
        }
    }
    else if(glWidget!=NULL){
        if(glWidget->IsPlaying()==true){
            glWidget->play();
        }
        else{
            if(glWidget->IsPausing()==true){
                glWidget->restart();
            }
            else{
                glWidget->play();
            }
        }
    }
}

void PlayVideoWidget::setFile(const QString& fileName)
{
    setWindowTitle(fileName.right(fileName.length() - fileName.lastIndexOf('/') - 1));

    if(Player!=NULL){
        Player->setSource(QUrl::fromLocalFile(fileName));
        Player->play();
    }
    else{
        glWidget->setSource(fileName);
        glWidget->play();
    }
}

void PlayVideoWidget::updateInfo()
{
}

void PlayVideoWidget::updateTime()
{
    if(Player!=NULL){
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
    else{
    }
}

void PlayVideoWidget::rewind()
{
    if(Player!=NULL){
        Player->setPosition(0);
    }
    else if(glWidget!=NULL){
        glWidget->rewind();
    }
}

void PlayVideoWidget::forward()
{
    if(Player!=NULL){
        Player->setPlaybackRate(2.0);
        Player->play();
    }
    else if(glWidget!=NULL){
        glWidget->forward();
    }
}
void PlayVideoWidget::pause()
{
    if(Player!=NULL){
        Player->pause();
    }
    else if(glWidget!=NULL){
        glWidget->pause();
    }
}

bool PlayVideoWidget::playPauseForDialog()
{
    if(Player!=NULL){
        if (Player->isAvailable() && Player->hasVideo()) {
            if (QMediaPlayer::PlayingState == Player->playbackState()) {
                Player->pause();
                return true;
            }
        }
    }
    else{
    }
    return false;
}

qint64 PlayVideoWidget::openFile(QString& fileName)
{
    const bool hasPausedForDialog = playPauseForDialog();

    if(Player!=NULL){
        if (hasPausedForDialog){
            Player->play();
            Player->setSource(QUrl::fromLocalFile(fileName));
        }
        return Player->duration();
    }
    else if(glWidget!=NULL){
        glWidget->setSource(fileName);
        
        return glWidget->duration();
    }

}

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
    CmdVideo_Pause  *CmdVideo_PauseVar=dynamic_cast<CmdVideo_Pause *>(packet);
    if(CmdVideo_PauseVar!=NULL){
        pause();
        return;
    }
    CmdVideo_LoadFile* CmdVideo_LoadFileVar = dynamic_cast<CmdVideo_LoadFile*>(packet);
    if (CmdVideo_LoadFileVar != NULL) {
        CmdVideo_LoadFileVar->TotalTime = openFile(CmdVideo_LoadFileVar->FileName);
        return;
    }
    CmdVideo_GetCurrentTime* CmdVideo_GetCurrentTimeVar = dynamic_cast<CmdVideo_GetCurrentTime*>(packet);
    if (CmdVideo_GetCurrentTimeVar != NULL) {
        if(Player!=NULL){
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
        }
        else if(glWidget!=NULL){
            if (glWidget->IsPlaying()==true) {
                CmdVideo_GetCurrentTimeVar->IsPlaying = true;
                qint64  duration=glWidget->duration();
                qint64  position=glWidget->position();
                CmdVideo_GetCurrentTimeVar->MaxTime     = duration;
                CmdVideo_GetCurrentTimeVar->CurrentTime = position;
                LastPosition=position;
                LastDuration=duration;
            }
            else{
                CmdVideo_GetCurrentTimeVar->MaxTime     = LastDuration;
                CmdVideo_GetCurrentTimeVar->CurrentTime = glWidget->position();
                CmdVideo_GetCurrentTimeVar->IsPlaying = false;
            }
        }
        return;
    }
    CmdVideo_SetPlaybackRate* CmdVideo_SetPlaybackRateVar = dynamic_cast<CmdVideo_SetPlaybackRate*>(packet);
    if (CmdVideo_SetPlaybackRateVar != NULL) {
        if(Player!=NULL){
            Player->setPlaybackRate(CmdVideo_SetPlaybackRateVar->PlaybackRate);
        }
        else if(glWidget!=NULL){
            glWidget->setPlaybackRate(CmdVideo_SetPlaybackRateVar->PlaybackRate);
        }
        return;
    }
    CmdVideo_GetPlaybackRate* CmdVideo_GetPlaybackRateVar = dynamic_cast<CmdVideo_GetPlaybackRate*>(packet);
    if (CmdVideo_GetPlaybackRateVar != NULL) {
        if(Player!=NULL){
            CmdVideo_GetPlaybackRateVar->PlaybackRate= Player->playbackRate();
        }
        return;
    }
}