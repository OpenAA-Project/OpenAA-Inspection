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

#include "ServiceLibResource.h"
#include "ImageDialog.h"
#include "ui_ImageDialog.h"
#include "XGeneralFunc.h"
#include <QPixmap>
#include <QFileDialog>


ImageDialog::ImageDialog(const QImage &sImage ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->labelImage->setPixmap(QPixmap::fromImage(sImage));
    SetWidgetCenter(this);
    //setWindowFlags(Qt::WindowTitleHint);
}

ImageDialog::~ImageDialog()
{
    delete ui;
}


void ImageDialog::on_pushButtonSave_clicked()
{
    const	QPixmap	*p=ui->labelImage->pixmap();
    if(p==NULL)
        return;

    QString	FileName=QFileDialog::getSaveFileName (this, /**/"Save Image", QString(), /**/"Images (*.png *.xpm *.jpg);;All file (*.*)");
    if(FileName.isEmpty()==false){
        p->save(FileName);
    }
}

void ImageDialog::on_pushButtonLoad_clicked()
{
    QString	FileName=QFileDialog::getOpenFileName (this, /**/"Load Image", QString(), /**/"Images (*.png *.xpm *.jpg);;All file (*.*)");
    if(FileName.isEmpty()==false){
        QPixmap	P;
        if(P.load(FileName)==true){
            ui->labelImage->setPixmap(P);
        }
    }
}

void ImageDialog::on_pushButtonCancel_clicked()
{
    const QPixmap	*p=ui->labelImage->pixmap();
    if(p!=NULL){
        SImage=p->toImage();
    }
    close();
}

void ImageDialog::on_pushButtonClear_clicked()
{
    QPixmap	DummyMap;
    ui->labelImage->setPixmap(DummyMap);
}