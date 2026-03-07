/*
 * Copyright (C) 2021
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

#include "AutofocusWithCameraResource.h"
#include "SettingFocusAreaDialog.h"
#include "ui_SettingFocusAreaDialog.h"
#include "swap.h"
#include "AutofocusWithCameraForm.h"

SettingFocusAreaDialog::SettingFocusAreaDialog(AutofocusWithCameraForm *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingFocusAreaDialog)
{
    ui->setupUi(this);
	Parent=p;

	ImagePanel.setParent(ui->frame);
	ImagePanel.move(0,0);
	ImagePanel.resize(ui->frame->width(),ui->frame->height());
	bool	Ret=(connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &))))?true:false;
			Ret=(connect(&ImagePanel,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void))))?true:false;
	ImagePanel.SetMode(fdRectangle);
	ImagePanel.SetFrameColor(Qt::red);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingFocusAreaDialog::~SettingFocusAreaDialog()
{
    delete ui;
}

void	SettingFocusAreaDialog::Initial(QImage &Image ,int x1, int y1 ,int x2, int y2)
{
	SampleImage	=Image;
	FocusAreaX1=x1;
	FocusAreaY1=y1;
	FocusAreaX2=x2;
	FocusAreaY2=y2;

	double	Zx=((double)ui->frame->width ())/(double)Image.width();
	double	Zy=((double)ui->frame->height())/(double)Image.height();
	double	Z=min(Zx,Zy);
	ImagePanel.SetZoomRate(Z);
	ImagePanel.SetMovXY(0,0);
	ImagePanel.SetAreaSize(Image.width(),Image.height());
	ImagePanel.show();
}

void SettingFocusAreaDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SettingFocusAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void	SettingFocusAreaDialog::SlotOnPaint(QPainter &pnt)
{
	pnt.drawImage(0,0,SampleImage.scaled(ImagePanel.width(),ImagePanel.height(),Qt::KeepAspectRatio));
}

void	SettingFocusAreaDialog::SlotDrawEnd(void)
{
	double	Zx=(double)SampleImage.width()/(double)ImagePanel.width();
	double	Zy=(double)SampleImage.height()/(double)ImagePanel.height();
	double	Z=max(Zx,Zy);
	FocusAreaX1	=ImagePanel.GetRawSDataPoint()->UData.RectangleData.x1;
	FocusAreaY1	=ImagePanel.GetRawSDataPoint()->UData.RectangleData.y1;
	FocusAreaX2	=ImagePanel.GetRawSDataPoint()->UData.RectangleData.x2;
	FocusAreaY2	=ImagePanel.GetRawSDataPoint()->UData.RectangleData.y2;
}
void SettingFocusAreaDialog::on_pushButtonSetDarkLightSetting_clicked()
{
	Parent->SaveDarkLightData();
}