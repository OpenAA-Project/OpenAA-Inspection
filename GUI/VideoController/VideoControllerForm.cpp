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

#include "VideoControllerForm.h"
#include "ui_VideoControllerForm.h"
#include "XVideoCommon.h"

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
	PlayVideoWidgetPointer	=GetLayersBase()->FindByName(/**/"Video",/**/"PlayWidget",/**/"");
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
			ui->toolButtonForwardMovie->setChecked(false);
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
		if(ui->toolButtonRunMovie->isChecked()==false){
			CmdVideo_Pause	Cmd(GetLayersBase());
			if (PlayVideoWidgetPointer != NULL) {
				PlayVideoWidgetPointer->TransmitDirectly(&Cmd);
			}
		}
		else{
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
								,"H264(*.mp4);;MPeg file(*.mpg);;AVI file(*.avi);;Motion JPEG(*.mjpg);;All files(*.*)");
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
			ui->toolButtonRunMovie->setChecked(true);
			ui->horizontalSliderMovie->setMaximum(Cmd.MaxTime);
			ui->horizontalSliderMovie->setValue((int)Cmd.CurrentTime);
		}
		else{
			ui->toolButtonRunMovie->setChecked(false);
			ui->horizontalSliderMovie->setMaximum(Cmd.MaxTime);
			ui->horizontalSliderMovie->setValue((int)Cmd.CurrentTime);
		}
	}
}