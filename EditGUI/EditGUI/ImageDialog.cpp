#include "XTypeDef.h"
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
    QPixmap	p=ui->labelImage->pixmap();
    QString	FileName=QFileDialog::getSaveFileName (this, /**/"Save Image", QString(), /**/"Images (*.png *.xpm *.jpg);;All file (*.*)");
    if(FileName.isEmpty()==false){
        p.save(FileName);
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
    QPixmap	p=ui->labelImage->pixmap();
    SImage=p.toImage();
    close();
}

void ImageDialog::on_pushButtonClear_clicked()
{
    QPixmap	DummyMap;
    ui->labelImage->setPixmap(DummyMap);
}
