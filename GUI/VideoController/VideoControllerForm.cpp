#include "VideoControllerForm.h"
#include "ui_VideoControllerForm.h"
#include "PlayVideoWidget.h"

VideoControllerForm::VideoControllerForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::VideoControllerForm)
{
    ui->setupUi(this);

	PlayVideoWidgetPointer=NULL;
	ShowFileOpenButton	=true;
}

VideoControllerForm::~VideoControllerForm()
{
    delete ui;
}

void	VideoControllerForm::ReadyParam(void)
{
	PlayVideoWidgetPointer	=dynamic_cast<PlayVideoWidget *>(GetLayersBase()->FindByName(/**/"Video",/**/"PlayWidget",/**/""));
	if(ShowFileOpenButton==false){
		ui->toolButtonOpenFile->setVisible(false);
	}

	TM.setInterval(100);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}
void	VideoControllerForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadFileAndStart	*CmdLoadFileAndStartVar=dynamic_cast<CmdLoadFileAndStart *>(packet);
	if (CmdLoadFileAndStartVar != NULL) {
		{
			CmdVideo_LoadFile	Cmd(GetLayersBase());
			Cmd.FileName = CmdLoadFileAndStartVar->VideoFileName;
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
				ui->horizontalSliderMovie->setMaximum((int)Cmd.TotalTime);
			}
		}
		{
			CmdVideo_Play		Cmd(GetLayersBase());
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			}
		}
		{
			CmdVideo_GetCurrentTime		Cmd(GetLayersBase());
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
				if (Cmd.IsPlaying == true)
					ui->toolButtonRunMovie->setChecked(true);
				else
					ui->toolButtonRunMovie->setChecked(false);
			}
		}
		return;
	}
}
void VideoControllerForm::on_toolButtonBackwardMovie_clicked()
{
	CmdVideo_Rewind	Cmd(GetLayersBase());
	if(PlayVideoWidgetPointer!=NULL){
		PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
		ui->horizontalSliderMovie->setValue(0);
	}
}

void VideoControllerForm::on_toolButtonRunMovie_clicked()
{
	if (ui->toolButtonForwardMovie->isChecked() == true) {
		CmdVideo_SetPlaybackRate	Cmd(GetLayersBase());
		Cmd.PlaybackRate = 1.0;
		PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
	}
	else {
		{
			CmdVideo_Play	Cmd(GetLayersBase());
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			}
		}
		{
			CmdVideo_GetCurrentTime		Cmd(GetLayersBase());
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
				if (Cmd.IsPlaying == true)
					ui->toolButtonRunMovie->setChecked(true);
				else
					ui->toolButtonRunMovie->setChecked(false);
			}
		}
	}
	ui->toolButtonForwardMovie->setChecked(false);
}

void VideoControllerForm::on_toolButtonForwardMovie_clicked()
{
	
	if(PlayVideoWidgetPointer!=NULL){
		if (ui->toolButtonForwardMovie->isChecked() == true) {
			if (ui->toolButtonRunMovie->isChecked() == false) {
				CmdVideo_Play	Cmd(GetLayersBase());
				if (PlayVideoWidgetPointer != NULL) {
					PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
				}
			}
			{
				CmdVideo_SetPlaybackRate	Cmd(GetLayersBase());
				Cmd.PlaybackRate = 2.0;
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			}
			ui->toolButtonRunMovie->setChecked(false);
		}
		else {
			CmdVideo_SetPlaybackRate	Cmd(GetLayersBase());
			Cmd.PlaybackRate = 1.0;
			PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			ui->toolButtonRunMovie->setChecked(true);
		}
		//ui->horizontalSliderMovie->setValue(ui->horizontalSliderMovie->maximum());
	}
}

void VideoControllerForm::on_horizontalSliderMovie_valueChanged(int value)
{

}

void VideoControllerForm::on_toolButtonOpenFile_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,"Open video file",QString()
								,"MPeg file(*.mpg);;AVI file(*.avi);;Motion JPEG(*.mjpg);;All files(*.*)");
	if(FileName.isNull()==false){	
		CmdVideo_LoadFile	Cmd(GetLayersBase());
		Cmd.FileName=FileName;
		if(PlayVideoWidgetPointer!=NULL){
			PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			ui->horizontalSliderMovie->setMaximum((int)Cmd.TotalTime);
		}
	}
}
void	VideoControllerForm::SlotTimeOut()
{
	CmdVideo_GetCurrentTime	Cmd(GetLayersBase());
	if(PlayVideoWidgetPointer!=NULL){
		PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
		if(Cmd.IsPlaying==true){
			ui->horizontalSliderMovie->setMaximum(Cmd.MaxTime);
			ui->horizontalSliderMovie->setValue((int)Cmd.CurrentTime);
		}
	}
}
