#include <QPainter>
#include "PrecisionChecker.h"
#include "XDataInLayer.h"
#include "QFileDialog"
#include "XImageBufferFunctions.h"
#include "XPointer.h"

PrecisionChecker::PrecisionChecker(LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base)
{
	ui.setupUi(this);

	nThreshValue = 50;

	ImagePanel.setParent(ui.frameImagePanel);
	ImagePanel.move(0,0);
	ImagePanel.resize(ui.frameImagePanel->width(),ui.frameImagePanel->height());
	ImagePanel.SetAreaSize(1000,1000);
	ImagePanel.SetMode(mtFrameDraw::fdNone);
	connect(&ImagePanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));
	connect(&ImagePanel,SIGNAL(SignalMouseWheel(int,int,int)),this,SLOT(SlotMouseWheel(int,int,int)));

	ui.pushButton_2->setEnabled(false);
	ui.pushButton_3->setEnabled(false);
	ui.pushButton_4->setEnabled(false);
	ui.pushButton_5->setEnabled(false);
	ui.pushButton_6->setEnabled(false);
	ui.btnHistgram->setEnabled(false);

	//ui.pushButton_2->setVisible(false);
}

PrecisionChecker::~PrecisionChecker()
{

}

void	PrecisionChecker::SlotOnPaint(QPainter &pnt)
{
	int	DotPerLine	=GetParamGlobal()->DotPerLine;
	int	MaxLines	=GetParamGlobal()->MaxLines;
	QImage	Img(DotPerLine,MaxLines,QImage::Format_RGB32);

	double	IZoomRate=1.0/ImagePanel.GetZoomRate();
	int64	AddX=(int64)(0x100000000*IZoomRate);
	if(CurrentPage<0)
		return;
	ImageBuffer	*SBuff=&GetLayersBase()->GetPageData(CurrentPage)->GetLayerData(0)->GetMasterBuff();
	if(SBuff->IsNull()==true)
		return;

	DWORD	ColTable[256];
	for(int i=0;i<256;i++){
		ColTable[i]=(DWORD)(qRgb (i,i,i));
	}
	DWORD onCls = (DWORD)(qRgb(255,0,0));
	DWORD onCls2 = (DWORD)(qRgb(0,0,255));

	int	LGx=ImagePanel.GetCanvasWidth();
	int	LGy=ImagePanel.GetCanvasHeight();
	int	movx=-ImagePanel.GetMovx();
	int	movy=-ImagePanel.GetMovy();

	for(int y=0;y<LGy;y++){
		DWORD	*d=(DWORD *)Img.scanLine(y);
		int		ry=movy+y*IZoomRate;
		if(ry<0 || ry>=MaxLines){
			memset(d,0,LGx*4);
		}
		else{
			int	x=0;
			int64	mx=0;
			if(movx<0){
				for(;x<LGx;x++){
					if((mx>>32)+movx>=0)
						break;
					*d=0;
					d++;
					mx+=AddX;
				}
			}
			BYTE	*s=SBuff->GetY(ry)+movx;
			for(;x<LGx;x++){
				if((mx>>32)+movx>=DotPerLine)
					break;
				*d=ColTable[*(s+(mx>>32))];
				if ( ui.chkViewBit->checkState() == Qt::Checked ) {
					if ( chkBit(CurrentPage,(mx>>32)+movx,ry) == true ) {
						*d = onCls2;
					}
				}
				if ( ui.chkFlexArea->checkState() == Qt::Checked ) {
					switch( chkFlexArea(CurrentPage,(mx>>32)+movx,ry) ) {
					case 1 :
						*d = onCls;
						break;
					case 2 :
						*d = onCls2;
						break;
					}
				}
				d++;
				mx+=AddX;
			}
			for(;x<LGx;x++){
				*d=0;
				d++;
			}
		}
	}
	pnt.drawImage(0,0,Img);
}

void	PrecisionChecker::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)
{
	Gx=(Dx+ImagePanel.GetMovx())*ImagePanel.GetZoomRate();
	Gy=(Dy+ImagePanel.GetMovy())*ImagePanel.GetZoomRate();
}

void	PrecisionChecker::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		int Gx ,Gy;
		ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
		ImagePanel.ZoomIn(Gx ,Gy);
	}
	else if(delta<0){
		int Gx ,Gy;
		ChangeDxy2Gxy(globalX, globalY,Gx ,Gy);
		ImagePanel.ZoomOut(Gx ,Gy);
	}
	ImagePanel.Repaint();
}


void PrecisionChecker::on_pushButtonLoadImage_clicked()
{
	//QString	FileName=QFileDialog::getOpenFileName (0, "Load PIX", "C:/Data", "*.pix");
	QString	FileName=QFileDialog::getOpenFileName (0, "Load PIX", "H:/PIX", "*.pix");

	if(FileName.isEmpty()==false){
		setPrm();

		QFile	mFile(FileName);
		int32	Ver;
		int32	iDotPerLine;
		int32	iMaxLines;
		int32	iPageNumb;
		int32	iLayerNumb;
		int32	iYCountBase;

		GetLayersBase()->LoadPIXInfo(mFile
							,Ver
							,iDotPerLine
							,iMaxLines
							,iPageNumb
							,iLayerNumb
							,iYCountBase);

		GetParamGlobal()->DotPerLine=iDotPerLine;
		GetParamGlobal()->MaxLines	=iMaxLines;
		GetParamGlobal()->PageNumb	=iPageNumb;
		GetParamGlobal()->LayerNumb	=iLayerNumb;
		GetLayersBase()->InitialCreatePages(NULL);

		ImageBuffer ***Buff=new ImageBuffer **[iPageNumb];
		for(int page=0;page<iPageNumb;page++){
			Buff[page]=new ImageBuffer *[iLayerNumb];
			DataInPage	*Dp=GetLayersBase()->GetPageData(page);
			for(int layer=0;layer<iLayerNumb;layer++){
				Buff[page][layer]=&Dp->GetLayerData(layer)->GetMasterBuff();
			}
		}
		GetLayersBase()->LoadPIX(mFile,Buff,iPageNumb,iLayerNumb);
		if(iLayerNumb>=3){
			for(int page=0;page<iPageNumb;page++){
				ImageBuffer	*IBuff[3];
				DataInPage	*Dp=GetLayersBase()->GetPageData(page);
				IBuff[0]=&Dp->GetLayerData(0)->GetMasterBuff();
				IBuff[1]=&Dp->GetLayerData(1)->GetMasterBuff();
				IBuff[2]=&Dp->GetLayerData(2)->GetMasterBuff();
				TransColorToMono(IBuff ,&Dp->GetLayerData(0)->GetMasterBuff());
			}
		}

		BuildShow(GetLayersBase(),0);

		ui.comboBoxPage->clear();
		for(int page=0;page<iPageNumb;page++){
			ui.comboBoxPage->addItem(QString("Page ")+QString::number(page));
		}
		ui.comboBoxPage->setCurrentIndex(0);
		CurrentPage=0;

		ImagePanel.SetAreaSize(iDotPerLine,iMaxLines);
		ImagePanel.ZoomDrawWhole();

		ImagePanel.Repaint();

		for(int page=0;page<iPageNumb;page++){
			delete	[]Buff[page];
		}
		delete	[]Buff;

		ui.pushButton_2->setEnabled(true);
		ui.pushButton_3->setEnabled(true);
		ui.pushButton_4->setEnabled(true);
		ui.pushButton_5->setEnabled(true);
		ui.pushButton_6->setEnabled(true);
		ui.btnHistgram->setEnabled(true);
		int wid = getImgWid();
		int hei = getImgHei();
		ui.txtX_1->setMaximum(wid);
		ui.txtX_2->setMaximum(wid);
		ui.txtY_1->setMaximum(hei);
		ui.txtY_2->setMaximum(hei);
		ui.txtX_2->setValue(wid);
		ui.txtY_2->setValue(hei);
	}
}

void PrecisionChecker::on_comboBoxPage_currentIndexChanged(int index)
{
	CurrentPage=index;
	ImagePanel.Repaint();
}

void PrecisionChecker::on_chkViewBit_stateChanged(int)
{
	ImagePanel.Repaint();
}

void PrecisionChecker::on_chkFlexArea_stateChanged(int)
{
	ImagePanel.Repaint();
}

void PrecisionChecker::on_pushButton_clicked()
{
	on_ParamButton_clicked();
}

void PrecisionChecker::on_pushButton_2_clicked()
{
	on_GRP_clicked(ui.txtX_1->value(),ui.txtY_1->value(),ui.txtX_2->value(),ui.txtY_2->value());
}

void PrecisionChecker::on_pushButton_6_clicked()
{
	on_Focus_clicked();
}

void PrecisionChecker::on_pushButton_4_clicked()
{
	on_Brightness_clicked();
}

void PrecisionChecker::on_pushButton_3_clicked()
{
	on_Resolution_clicked();
}

void PrecisionChecker::on_pushButton_5_clicked()
{
	on_Angle_clicked();
}



void PrecisionChecker::on_btnHistgram_clicked()
{
	on_Histgram_clicked(ui.txtX_1->value(),ui.txtY_1->value(),ui.txtX_2->value(),ui.txtY_2->value());
}

void PrecisionChecker::on_pushButton_7_clicked()
{
	BuildShow(GetLayersBase(),0);
}