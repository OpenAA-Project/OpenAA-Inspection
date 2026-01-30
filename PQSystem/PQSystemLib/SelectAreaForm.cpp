/*
 * Copyright (C) 2025
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

#include "SelectAreaForm.h"
#include "PQSystemService.h"
#include "ui_SelectAreaForm.h"
#include "XIntegrationBase.h"
#include "swap.h"
#include "XDisplayImage.h"

SelectAreaForm::SelectAreaForm(PQSystemRunner *runner ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(runner->GetLayersBase())
	,Parent(runner)
    ,ui(new Ui::SelectAreaForm)
{
    ui->setupUi(this);

	GPanel.setParent(ui->frame);
	connect(&GPanel,SIGNAL(SignalOnPaint(QPainter &))	 ,this,SLOT(SlotOnPaint(QPainter &)));
	connect(&GPanel,SIGNAL(SignalMouseWheel(int,int,int)),this,SLOT(SlotMouseWheel(int,int,int)));
	connect(&GPanel,SIGNAL(SignalDrawEnd(void))			 ,this,SLOT(SlotDrawEnd(void)));

	ui->comboBoxSelectSlave->clear();
	IntegrationBase	*LBase=GetLayersBase()->GetIntegrationBasePointer();
	for(EachMaster *m=LBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		ui->comboBoxSelectSlave->addItem(m->GetMachineName());
	}
	GPanel.SetMode(mtFrameDraw::fdRectangle);
	GPanel.SetFrameColor(Qt::red);
	GPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	EachMaster	*M=LBase->MasterDatas[0];
	if(M!=NULL){
		int	mx1,my1,mx2,my2;
		M->GetXY(mx1,my1,mx2,my2);
		GPanel.SetAreaSize(mx2,my2);
		GPanel.ZoomDrawFit();
	}
}

SelectAreaForm::~SelectAreaForm()
{
    delete ui;
}

void	SelectAreaForm::resizeEvent(QResizeEvent *event)
{
	ui->frameBottom->setGeometry(0,height()-ui->frameBottom->height()
								 ,width(),ui->frameBottom->height());
	ui->frame->setGeometry(0,ui->frame->geometry().top()
						   ,width(),height()-ui->frame->geometry().top()-ui->frameBottom->height());
	GPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
}

void SelectAreaForm::on_comboBoxSelectSlave_currentIndexChanged(int index)
{
	repaint();
}

void SelectAreaForm::on_pushButtonSelectArea_clicked()
{
	done(true);
}

void SelectAreaForm::on_pushButtonCancel_clicked()
{
	done(false);
}
void	SelectAreaForm::SlotOnPaint(QPainter &pnt)
{
	int	Index=ui->comboBoxSelectSlave->currentIndex();
	if(Index<0)
		Index=0;
	IntegrationBase	*LBase=GetLayersBase()->GetIntegrationBasePointer();
	EachMaster	*M=LBase->MasterDatas[Index];
	int		MovX	=GPanel.GetMovx();
	int		MovY	=GPanel.GetMovy();
	double	ZoomRate=GPanel.GetZoomRate();

	int	mx1,my1,mx2,my2;
	M->GetXY(mx1,my1,mx2,my2);
	GPanel.SetAreaSize(mx2,my2);

	int	GWidth	=GPanel.GetCanvasWidth();
	int	GHeight	=GPanel.GetCanvasHeight();
	QImage	MasterImage(GWidth,GHeight ,QImage::Format_ARGB32);
	
	int	Phase=0;
	Parent->DrawMasterImage(M ,MasterImage,Phase ,MovX,MovY ,ZoomRate);

	pnt.drawImage(0,0,MasterImage);

	QImage	MaskImage(GWidth,GHeight ,QImage::Format_ARGB32);
	QRgb Col=qRgba(255,0,0,160);
	SelectArea.DrawAlpha(0,0 ,&MaskImage ,Col
									,ZoomRate ,MovX,MovY);
	pnt.drawImage(0,0,MaskImage);
}
void	SelectAreaForm::SlotMouseWheel(int delta ,int x,int y)
{
	int		MovX	=GPanel.GetMovx();
	int		MovY	=GPanel.GetMovy();
	double	ZoomRate=GPanel.GetZoomRate();
	int	X=(x+MovX)*ZoomRate;
	int	Y=(y+MovY)*ZoomRate;
	if(delta>0){
		GPanel.ZoomIn(X,Y);
	}
	else{
		GPanel.ZoomOut(X,Y);
	}
}
void	SelectAreaForm::SlotDrawEnd(void)
{
	DisplayImage::ToFlexArea( GPanel.GetCanvas()->SData ,SelectArea);
}