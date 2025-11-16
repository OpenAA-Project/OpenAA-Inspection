#include "EditWaveGraphDialog.h"
#include "ui_EditWaveGraphDialog.h"
#include "XDataInLayer.h"
#include "XReferencePDF.h"

EditWaveGraphDialog::EditWaveGraphDialog(ReferencePDF *R,LayersBase *Base
                                        ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,RefPDF(R)
    ,ui(new Ui::EditWaveGraphDialog)
{
    ui->setupUi(this);
    GraphImage      =NULL;
    ReferenceName   =RefPDF->ReferenceName;
    ui->EditReferenceName->setText(ReferenceName);
    MakeGraph();
}

EditWaveGraphDialog::~EditWaveGraphDialog()
{
    delete ui;
}
void    EditWaveGraphDialog::SetDeletable(bool Deletable)
{
    ui->pushButtonDelete->setEnabled(Deletable);
}
void EditWaveGraphDialog::on_pushButtonDelete_clicked()
{
    done(1);
}


void EditWaveGraphDialog::on_pushButtonCancel_clicked()
{
    done(2);
}


void EditWaveGraphDialog::on_pushButtonUpdateName_clicked()
{
    ReferenceName   =ui->EditReferenceName->text();
    done(3);
}

void EditWaveGraphDialog::MakeGraph(void)
{
    if(GraphImage!=NULL){
        delete  GraphImage;
    }
    int W=ui->labelGraph->width();
    int H=ui->labelGraph->height();
    GraphImage=new QImage(W,H,QImage::Format_RGB32);

    int XMergin=100;
    int YMergin=60;

    GraphImage->fill(Qt::black);

    QPainter    Pnt(GraphImage);
    Pnt.setPen(Qt::white);
    Pnt.drawLine(0,H-YMergin,W,H-YMergin);
    Pnt.drawLine(XMergin,0,XMergin,H);

    if(RefPDF->CountOfColorDim!=0){
        int XWLen=W-XMergin;
        int YWLen=H-YMergin;
        double  XZoom=((double)RefPDF->CountOfColorDim)/((double)XWLen);
        double  MaxD=0;
        for(int X=0;X<RefPDF->CountOfColorDim;X++){
            if(MaxD<RefPDF->ColorDim[X]){
                MaxD=RefPDF->ColorDim[X];
            }
        }
        int x=0;
        int W1=XWLen/4;
        int W2=XWLen/4;
        int W3=XWLen/4;
        int W4=XWLen/4;
        for(;x<W1;x++){
            int X=x*XZoom;
            int Y=RefPDF->ColorDim[X]*MaxD/YWLen;
            Pnt.setPen(qRgb(x*255/W1,0,0));
            Pnt.drawLine(XMergin+x,H-YMergin,XMergin+x,H-YMergin-Y);
        }
        for (;x<(W1+W2);x++) {
            int X=x*XZoom;
            int Y=RefPDF->ColorDim[X]*MaxD/YWLen;
            Pnt.setPen(qRgb(255*(W1+W2-x)/W2,255*(x-W1)/W2,0));
            Pnt.drawLine(XMergin+x,H-YMergin,XMergin+x,H-YMergin-Y);
        }
        for (;x<(W1+W2+W3);x++) {
            int X=x*XZoom;
            int Y=RefPDF->ColorDim[X]*MaxD/YWLen;
            Pnt.setPen(qRgb(0,255*(W1+W2+W3-x)/W3,255*(x-(W1+W2))/W3));
            Pnt.drawLine(XMergin+x,H-YMergin,XMergin+x,H-YMergin-Y);
        }
        for (;x<(W1+W2+W3+W4);x++) {
            int X=x*XZoom;
            int Y=RefPDF->ColorDim[X]*MaxD/YWLen;
            double  t=(x-(W1+W2+W3))/(double)W4;
            t=t*0.5;
            Pnt.setPen(qRgb(255*t,0,255*(1.0-t)));
            Pnt.drawLine(XMergin+x,H-YMergin,XMergin+x,H-YMergin-Y);
        }    
    }
    ui->labelGraph->setPixmap(QPixmap::fromImage(*GraphImage)); 
}
