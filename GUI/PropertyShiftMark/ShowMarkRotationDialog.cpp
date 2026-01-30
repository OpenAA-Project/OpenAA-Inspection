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

#include "PropertyShiftMarkResource.h"
#include "ShowMarkRotationDialog.h"
#include "ui_ShowMarkRotationDialog.h"
#include "XShiftMark.h"
#include "XPropertyShiftMarkPacket.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowMarkRotationDialog::ShowMarkRotationDialog(LayersBase *base 
                                                ,int _Page ,int _ItemID ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::ShowMarkRotationDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    Phase       =GetLayersBase()->GetCurrentPhase();
    GlobalPage  =_Page;
    ItemID      =_ItemID;

    GUICmdReqRotationPoint  RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
    GUICmdAckRotationPoint  ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
    RCmd.Phase  =Phase;
    RCmd.ItemID =ItemID;

    if(RCmd.Send(GlobalPage,0,ACmd)==true){
        EdgeArea    =ACmd.EdgeArea;
        MarkArea    =ACmd.MarkArea;
    }
    int N=EdgeArea.GetCount();

    ui->horizontalSliderAngleNumber->setMaximum(N-1);
    ui->horizontalSliderAngleNumber->setValue(N/2);
    on_horizontalSliderAngleNumber_valueChanged(0);
}

ShowMarkRotationDialog::~ShowMarkRotationDialog()
{
    delete ui;
}

void ShowMarkRotationDialog::on_horizontalSliderAngleNumber_valueChanged(int value)
{
    int n=ui->horizontalSliderAngleNumber->value();
    FlexAreaColorRotatedImage   *E=EdgeArea[n];
    FlexAreaColorRotatedImage   *M=MarkArea[n];

    ui->labelAngle  ->setText(QString::number(E->GetAngleRadian()*360/(2*M_PI),'f',3));

    {
        QImage  ImgE(ui->labelEdge->width(),ui->labelEdge->height(),QImage::Format_RGB32);
        double  EZx=((double)ui->labelEdge->width ())/((double)E->GetWidth ());
        double  EZy=((double)ui->labelEdge->height())/((double)E->GetHeight());

        ImgE.fill(Qt::black);
        E->DrawImage(-E->GetMinX(),-E->GetMinY(),&ImgE
                    ,max(EZx,EZy) ,0,0
	    			,true ,true,true);
        ImgEdge=ImgE;
        ui->labelEdge->setPixmap(QPixmap::fromImage(ImgEdge));
    }
    {
        QImage  ImgM(ui->labelMark->width(),ui->labelMark->height(),QImage::Format_RGB32);
        double  MZx=((double)ui->labelMark->width ())/((double)M->GetWidth ());
        double  MZy=((double)ui->labelMark->height())/((double)M->GetHeight());

        ImgM.fill(Qt::black);
        M->DrawImage(-M->GetMinX(),-M->GetMinY(),&ImgM
                    ,max(MZx,MZy) ,0,0
	    			,true ,true,true);
        ImgMark=ImgM;
        ui->labelMark->setPixmap(QPixmap::fromImage(ImgMark));
    }
}


void ShowMarkRotationDialog::on_pushButtonClose_clicked()
{
    done(true);
}
