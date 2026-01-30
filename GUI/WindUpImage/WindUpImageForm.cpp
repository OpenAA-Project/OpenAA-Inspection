/*
 * Copyright (C) 2024
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

#include "WindUpImageResource.h"
#include "WindUpImageForm.h"
#include "ui_WindUpImageForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

WindUpImageForm::WindUpImageForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::WindUpImageForm)
{
    ui->setupUi(this);

	ui->spinBoxShiftDown	->setValue(ControlRememberer::GetInt(ui->spinBoxShiftDown	,2000));
	ui->spinBoxWindUp		->setValue(ControlRememberer::GetInt(ui->spinBoxWindUp		,3000));
	ui->spinBoxBrightness	->setValue(ControlRememberer::GetInt(ui->spinBoxBrightness	,20));
}

WindUpImageForm::~WindUpImageForm()
{
    delete ui;
}

void WindUpImageForm::on_pushButtonExecuteWindup_clicked()
{
	int	ShiftDown	=ui->spinBoxShiftDown->value();
	int	WindUp		=ui->spinBoxWindUp	->value();
	int	Brightness	=ui->spinBoxBrightness->value();

	ControlRememberer::SetValue(ui->spinBoxShiftDown	,ui->spinBoxShiftDown->value()	);
	ControlRememberer::SetValue(ui->spinBoxWindUp		,ui->spinBoxWindUp->value()		);
	ControlRememberer::SetValue(ui->spinBoxBrightness	,ui->spinBoxBrightness->value()	);

	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdExecuteWindUp	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.ShiftDown	=ShiftDown;
		RCmd.WindUp		=WindUp;
		RCmd.Brightness	=Brightness;
		RCmd.SendOnly(globalPage,0,10000);
	}
}


//===========================================================================================

GUICmdExecuteWindUp::GUICmdExecuteWindUp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ShiftDown	=0;
	WindUp		=0;
	Brightness	=0;
}
bool	GUICmdExecuteWindUp::Load(QIODevice *f)
{
	if(::Load(f,ShiftDown)==false){
		return false;
	}
	if(::Load(f,WindUp)==false){
		return false;
	}
	if(::Load(f,Brightness)==false){
		return false;
	}
	return true;
}

bool	GUICmdExecuteWindUp::Save(QIODevice *f)
{
	if(::Save(f,ShiftDown)==false){
		return false;
	}
	if(::Save(f,WindUp)==false){
		return false;
	}
	if(::Save(f,Brightness)==false){
		return false;
	}
	return true;
}


void	GUICmdExecuteWindUp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Dp=GetLayersBase()->GetPageData(localPage);
	for(int layer=0;layer<GetLayerNumb(localPage);layer++){
		DataInLayer	*Lp=Dp->GetLayerData(layer);
		ImageBuffer	&IBuff=Lp->GetMasterBuff();

		ImageBuffer	Buff(0,Dp->GetDotPerLine(),Dp->GetMaxLines());
		//���摜���o�b�t�@�փR�s�[
		Buff=IBuff;

		//�摜�ړ�
		IBuff.MoveImage(0,ShiftDown);
		if(ShiftDown>0){
			//�S�̂����Ɉړ������Ƃ��A���̋󂫗̈����h���Ԃ�
			for(int y=0;y<Dp->GetMaxLines() && y<ShiftDown;y++){
				BYTE	*d=IBuff.GetY(y);
				memset(d,Brightness,Dp->GetDotPerLine());
			}
		}
		else{
			//�S�̂����Ɉړ������Ƃ��A���̋󂫗̈����h���Ԃ�
			for(int y=Dp->GetMaxLines()+ShiftDown;y<Dp->GetMaxLines();y++){
				BYTE	*d=IBuff.GetY(y);
				memset(d,Brightness,Dp->GetDotPerLine());
			}
		}
		if(WindUp>=Dp->GetMaxLines()){
			WindUp=Dp->GetMaxLines();
		}
		if(ShiftDown>0){
			//�摜�����Ɉړ������Ƃ��A�����グ�͉�����WindUp���C���������փR�s�[
			for(int n=0;n<WindUp;n++){
				BYTE	*d=IBuff.GetY(n);
				BYTE	*s=Buff.GetY(Dp->GetMaxLines()-WindUp+n);
				memcpy(d,s,Dp->GetDotPerLine());
			}
		}
		else{
			//�摜�����Ɉړ������Ƃ��A�����グ�͏ォ��WindUp���C���������փR�s�[
			for(int n=0;n<WindUp;n++){
				BYTE	*d=IBuff.GetY(Dp->GetMaxLines()-WindUp+n);
				BYTE	*s=Buff.GetY(n);
				memcpy(d,s,Dp->GetDotPerLine());
			}
		}
	}
	SendAck(localPage);
}