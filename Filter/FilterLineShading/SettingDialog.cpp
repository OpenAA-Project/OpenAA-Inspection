#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterLineShading.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include "swap.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "ButtonLoadBmpJpg.h"
#include "LoadImageTargetButton.h"

SettingDialog::SettingDialog(LayersBase *Base,FilterLineShading *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    XLen=GetDotPerLine(0);
    LayerNumb=min(3,GetLayersBase()->GetMaxLayerNumb());
    for(int layer=0;layer<3;layer++){
        for(int c=0;c<256;c++){
            if(BrightnessTable[layer][c]!=NULL){
                BrightnessTable[layer][c]=NULL;
            }
        }
    }
    for(int layer=0;layer<LayerNumb;layer++){
         for(int c=0;c<256;c++){
             BrightnessTable[layer][c]=new int[XLen];
             for(int x=0;x<XLen;x++){
                 BrightnessTable[layer][c][x]=0;
             }
         }
    }
    ui->labelL1             ->setVisible((LayerNumb>=1)?true:false);
    ui->doubleSpinBoxSetR   ->setVisible((LayerNumb>=1)?true:false);
    ui->doubleSpinBoxMaxR   ->setVisible((LayerNumb>=1)?true:false);
    ui->doubleSpinBoxAvrR   ->setVisible((LayerNumb>=1)?true:false);
    ui->labelL1             ->setText(GetParamGlobal()->GetLayerName(0));

    ui->labelL2             ->setVisible((LayerNumb>=2)?true:false);
    ui->doubleSpinBoxSetG   ->setVisible((LayerNumb>=2)?true:false);
    ui->doubleSpinBoxMaxG   ->setVisible((LayerNumb>=2)?true:false);
    ui->doubleSpinBoxAvrG   ->setVisible((LayerNumb>=2)?true:false);
    ui->labelL2             ->setText(GetParamGlobal()->GetLayerName(1));

    ui->labelL3             ->setVisible((LayerNumb>=3)?true:false);
    ui->doubleSpinBoxSetB   ->setVisible((LayerNumb>=3)?true:false);
    ui->doubleSpinBoxMaxB   ->setVisible((LayerNumb>=3)?true:false);
    ui->doubleSpinBoxAvrB   ->setVisible((LayerNumb>=3)?true:false);
    ui->labelL3             ->setText(GetParamGlobal()->GetLayerName(2));

    if(LayerNumb>=1){
        if(Parent->FValue!=NULL)
            ui->doubleSpinBoxSetR->setValue(Parent->FValue[0]);
        if(Parent->ImgMax!=NULL)
            ui->doubleSpinBoxMaxR->setValue(Parent->ImgMax[0]);
        if(Parent->ImgAvr!=NULL)
            ui->doubleSpinBoxAvrR->setValue(Parent->ImgAvr[0]);
    }
    if(LayerNumb>=2){
        if(Parent->FValue!=NULL)
            ui->doubleSpinBoxSetG->setValue(Parent->FValue[1]);
        if(Parent->ImgMax!=NULL)
            ui->doubleSpinBoxMaxG->setValue(Parent->ImgMax[1]);
        if(Parent->ImgAvr!=NULL)
            ui->doubleSpinBoxAvrG->setValue(Parent->ImgAvr[1]);
    }
    if(LayerNumb>=3){
        if(Parent->FValue!=NULL)
            ui->doubleSpinBoxSetB->setValue(Parent->FValue[2]);
        if(Parent->ImgMax!=NULL)
            ui->doubleSpinBoxMaxB->setValue(Parent->ImgMax[2]);
        if(Parent->ImgAvr!=NULL)
            ui->doubleSpinBoxAvrB->setValue(Parent->ImgAvr[2]);
    }
    ui->spinBoxMinX->setValue(Parent->MinX);
    ui->spinBoxMaxX->setValue(Parent->MaxX);
    ui->lineEditFileName->setText(Parent->FileName);
    //ui->pushButtonSetOK->setEnabled(false);
}

SettingDialog::~SettingDialog()
{
    delete ui;
    for(int layer=0;layer<3;layer++){
        for(int c=0;c<256;c++){
            if(BrightnessTable[layer][c]!=NULL){
                delete  []BrightnessTable[layer][c];
                BrightnessTable[layer][c]=NULL;
            }
        }
    }
    XLen=0;
    LayerNumb=0;
}

void SettingDialog::on_pushButtonFileName_clicked()
{
    QString  FileName=QFileDialog::getOpenFileName(nullptr
                            , "Load image file"
                            , QString()
                            //, /**/"Jpeg(*.jpg);;Bmp(*.bmp);;PNG(*.png);;PIX(*.pix)");
                            , /**/"Jpeg(*.jpg);;Bmp(*.bmp);;PNG(*.png)");
    if(FileName.isEmpty()==false){
        ui->lineEditFileName->setText(FileName);
    }
}

void SettingDialog::on_pushButtonLoad_clicked()
{
    QString  FileName=ui->lineEditFileName->text();
    QFileInfo   FInfo(FileName);
    QString Ext=FInfo.suffix().toLower();
    if(Ext==/**/"jpg" || Ext==/**/"bmp" || Ext==/**/"png"){
        GUIFormBase *f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
        if(f!=NULL){
            CmdLoadBmpJpgPacketQImage   Cmd(GetLayersBase());
            Cmd.FileName=FileName;
            f->TransmitDirectly(&Cmd);
            if(Cmd.Success==true){
                ui->pushButtonSetOK->setEnabled(true);
                Analize(Cmd.Image);
            }
        }
        else{
            QMessageBox::warning(NULL,"Error"
                                 ,"Need Button:ButtonLoadBmpJpg component");
        }
    }
    //else if(Ext==/**/"pix"){
    //    GUIFormBase *f=GetLayersBase()->FindByName(/**/"Inspection",/**/"LoadImageTargetButton",/**/"");
    //    if(f!=NULL){
    //        CmdLoadBmpJpgPacketQImage   Cmd(GetLayersBase());
    //        Cmd.FileName=FileName;
    //        f->TransmitDirectly(&Cmd);
    //        if(Cmd.Success==true){
    //            Analize(Cmd.Image);
    //        }
    //    }
    //
    //}

}

void    SettingDialog::Analize(QImage &Image)
{
    int MinX=ui->spinBoxMinX->value();
    int MaxX=ui->spinBoxMaxX->value();

    int SXLen=Image.width();
    int SYLen=Image.height();
    MinX=max(MinX,0);
    MaxX=min(MaxX,SXLen);
    for(int y=0;y<SYLen;y++){
        QRgb    *s=(QRgb *)Image.scanLine(y);
        for(int x=MinX;x<MaxX;x++){
            if(LayerNumb>=1){
                int c=qRed(*s);
                BrightnessTable[0][c][x]++;
            }
            if(LayerNumb>=2){
                int c=qGreen(*s);
                BrightnessTable[1][c][x]++;
            }
            if(LayerNumb>=3){
                int c=qBlue(*s);
                BrightnessTable[2][c][x]++;
            }
        }
    }
    for(int layer=0;layer<LayerNumb;layer++){
        double MaxC=0;
        double AvrC=0;
        int    Numb=0;
        int    MaxN=0;
        for(int x=MinX;x<MaxX;x++){
            for(int c=0;c<256;c++){
                if(BrightnessTable[layer][c][x]>MaxN){
                    MaxN=BrightnessTable[layer][c][x];
                    MaxC=c;
                }
                AvrC+=BrightnessTable[layer][c][x]*c;
                Numb+=BrightnessTable[layer][c][x];
            }
        }
        AvrC/=Numb;
        if(layer==0){
            ui->doubleSpinBoxMaxR->setValue(MaxC);
            ui->doubleSpinBoxAvrR->setValue(AvrC);
        }
        else
        if(layer==1){
            ui->doubleSpinBoxMaxG->setValue(MaxC);
            ui->doubleSpinBoxAvrG->setValue(AvrC);
        }
        else
        if(layer==2){
            ui->doubleSpinBoxMaxB->setValue(MaxC);
            ui->doubleSpinBoxAvrB->setValue(AvrC);
        }
    }
}

void SettingDialog::on_pushButtonSetOK_clicked()
{
   Parent->MinX=ui->spinBoxMinX->value();
   Parent->MaxX=ui->spinBoxMaxX->value();
   int MinX=Parent->MinX;
   int MaxX=Parent->MaxX;
   MinX=max(MinX,0);
   MaxX=min(MaxX,XLen);

   if(LayerNumb>=1){
        Parent->FValue[0]=ui->doubleSpinBoxSetR->value();
        Parent->ImgMax[0]=ui->doubleSpinBoxMaxR->value();
        Parent->ImgAvr[0]=ui->doubleSpinBoxAvrR->value();
    }
    if(LayerNumb>=2){
        Parent->FValue[1]=ui->doubleSpinBoxSetG->value();
        Parent->ImgMax[1]=ui->doubleSpinBoxMaxG->value();
        Parent->ImgAvr[1]=ui->doubleSpinBoxAvrG->value();
    }
    if(LayerNumb>=3){
        Parent->FValue[2]=ui->doubleSpinBoxSetB->value();
        Parent->ImgMax[2]=ui->doubleSpinBoxMaxB->value();
        Parent->ImgAvr[2]=ui->doubleSpinBoxAvrB->value();
    }
    for(int Layer=0;Layer<LayerNumb;Layer++){
        for(int x=MinX;x<MaxX;x++){
            double  AvrC=0;
            int     Numb=0;
            for(int c=0;c<MaxBrightness;c++){
                AvrC+=BrightnessTable[Layer][c][x]*c;
                Numb+=BrightnessTable[Layer][c][x];
            }
            AvrC/=Numb;
            double  M=Parent->FValue[Layer]/AvrC;
            for(int c=0;c<MaxBrightness;c++){
                int cm=c*M;
                Parent->MultiplePerDot[Layer][x*256+c]=Saturation256(cm);
            }
        }
        for(int x=0;x<MinX;x++){
            for(int c=0;c<MaxBrightness;c++){
                Parent->MultiplePerDot[Layer][x*256+c]=Parent->MultiplePerDot[Layer][MinX*256+c];
            }
        }
        for(int x=MaxX;x<XLen;x++){
            for(int c=0;c<MaxBrightness;c++){
                Parent->MultiplePerDot[Layer][x*256+c]=Parent->MultiplePerDot[Layer][(MaxX-1)*256+c];
            }
        }
    }
    done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
