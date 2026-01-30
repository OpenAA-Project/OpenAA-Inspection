/*
 * Copyright (C) 2023
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


#include <QFileDialog>
#include <QMessageBox>
#include "proofreader.h"
#include "ProofGraph.h"
#include "WhiteBalanceForm.h"
#include "XDataInLayer.h"
#include "mtGraphicUnit.h"
#include "XGeneralFunc.h"

//#include "XForHalcon.h"

Proofreader::Proofreader(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.tbExpansion->setCheckable(true);
	ui.tbRectangle->setCheckable(true);

	guMasterImage=new mtGraphicUnit();
	ui.dwMasterImage->setWidget(guMasterImage);
	guMasterImage->SetMode(mtFrameDraw::fdNone);
	guMasterImage->SetFrameColor(QColor(Qt::red));

	img=NULL;
	iDotPerLine=iMaxLines=0;
	ThresholdDotArray=NULL;
	dxList.clear();
	dyList.clear();
	dxAverageList.clear();
	CntClick=0;
//	CntClick=CntDraw=0;
	StartPointX=StartPointY=EndPointX=EndPointY=0;
	iPageNumb=iLayerNumb=0;
	Buff=NULL;
	CurrentIndex=0;

	connect(ui.pbLoadMasterImage,	SIGNAL(clicked()),				  this,SLOT(pbLoadMasterImage_clicked()));
	connect(ui.pbThreshold,			SIGNAL(clicked()),				  this,SLOT(pbThreshold_clicked()));
	connect(ui.pbLabelingX,			SIGNAL(clicked()),				  this,SLOT(pbLabelingX_clicked()));
	connect(ui.pbLabelingY,			SIGNAL(clicked()),				  this,SLOT(pbLabelingY_clicked()));
	connect(ui.pbSave,				SIGNAL(clicked()),				  this,SLOT(pbSave_clicked()));
	connect(ui.pbShowGraph,			SIGNAL(clicked()),				  this,SLOT(pbShowGraph_clicked()));
	connect(ui.pbShowGraphFromCsv,	SIGNAL(clicked()),				  this,SLOT(pbShowGraphFromCsv_clicked()));
	connect(ui.pbWhiteBalance,		SIGNAL(clicked()),				  this,SLOT(pbWhiteBalance_clicked()));
	connect(ui.pbClose,				SIGNAL(clicked()),				  this,SLOT(pbClose_clicked()));
	connect(guMasterImage,			SIGNAL(SignalOnPaint(QPainter&)), this,SLOT(SlotOnPaint(QPainter &)));
	connect(ui.tbExpansion,			SIGNAL(toggled(bool)),			  this,SLOT(tbExpansionToggled(bool)));
	connect(ui.tbWhole,				SIGNAL(clicked()),				  this,SLOT(tbWholeClicked()));
	connect(ui.tbRectangle,			SIGNAL(toggled(bool)),			  this,SLOT(tbRectangleToggled(bool)));
	connect(guMasterImage,			SIGNAL(SignalMouseLDown(int,int)),this,SLOT(SlotMouseLDown(int,int)));
	connect(guMasterImage,			SIGNAL(SignalDrawEnd()),		  this,SLOT(SlotDrawEnd()));
	connect(guMasterImage,			SIGNAL(SignalMouseRDown(int,int)),this,SLOT(SlotMouseRDown(int,int)));

	connect(ui.cbCamera,			SIGNAL(currentIndexChanged(int)), this,SLOT(cbCameraIndexChanged(int)));
	connect(ui.chkReverse,			SIGNAL(toggled(bool)),			  this,SLOT(chkReverseToggled(bool)));

	connect(ui.pbLoadPixHalcon,		SIGNAL(clicked()),				  this,SLOT(pbLoadPixHalconClicked()));
}

Proofreader::~Proofreader()
{
	for(int Y=0;Y<iMaxLines;Y++)
		delete ThresholdDotArray[Y];
	delete ThresholdDotArray;
	delete guMasterImage;
}

void Proofreader::pbLoadMasterImage_clicked()
{
	QString MasterImagePath=QFileDialog::getOpenFileName(
							this,tr("Please choose a '.pix' file."),"","ImageBuffer (*.pix)");
	if(MasterImagePath.isEmpty())
		return;

	QFile	RFile(MasterImagePath);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return;

	int wiPageNumb	=iPageNumb;
	int wiLayerNumb	=iLayerNumb;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return;
	int	iYCountBase;
	if(::Load(&RFile,iPageNumb)==false)
		return;
	if(::Load(&RFile,iLayerNumb)==false)
		return;
	if(::Load(&RFile,iDotPerLine)==false)
		return;
	if(::Load(&RFile,iMaxLines)==false)
		return;
	if(::Load(&RFile,iYCountBase)==false)
		return;

	if(Buff!=NULL){
		for(int page=0;page<wiPageNumb;page++){
			for(int Layer=0;Layer<wiLayerNumb;Layer++){
				delete Buff[page][Layer];
				Buff[page][Layer]=NULL;
			}
			delete Buff[page];
			Buff[page]=NULL;
		}
		delete Buff;
		Buff=NULL;
	}

	disconnect(ui.cbCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(cbCameraIndexChanged(int)));
	ui.cbCamera->clear();
	Buff=new ImageBuffer**[iPageNumb];
	for(int page=0;page<iPageNumb;page++){
		Buff[page]=new ImageBuffer*[iLayerNumb];
		for(int Layer=0;Layer<iLayerNumb;Layer++){
			Buff[page][Layer]=new ImageBuffer();
			Buff[page][Layer]->Set(page,1,iDotPerLine,iMaxLines);
		}
		//�J�����؂��ւ��R���{�{�b�N�X�̕\��
		QString item="Camera-" + QString::number(page);
		ui.cbCamera->addItem(item);
	}
	connect(ui.cbCamera,SIGNAL(currentIndexChanged(int)),this,SLOT(cbCameraIndexChanged(int)));

	for(int page=0;page<iPageNumb;page++){
		int	YCount=iYCountBase;
		int	TopY;
		for(TopY=0;TopY<iMaxLines;TopY+=YCount){
			if(TopY+YCount>iMaxLines)
				YCount=iMaxLines-TopY;
			int	Layer;
			for(Layer=0;Layer<iLayerNumb;Layer++){
				QByteArray Data=RFile.read(YCount*iDotPerLine);
				BYTE	*Src=(BYTE *)Data.data();
				int		YLenFromData=Data.size()/iDotPerLine;
				int		N=0;
				for(int y=TopY;y<TopY+YCount && N<YLenFromData;y++,N++){
					if(y<iMaxLines){
						memcpy(Buff[page][Layer]->GetY(y),Src,iDotPerLine);
						Src+=iDotPerLine;
					}
				}
			}
		}
	}

	//�}�X�^�[�摜�̕\��
	if(img!=NULL){
		for(int page=0;page<wiPageNumb;page++){
			delete img[page];
			img[page]=NULL;
		}
		delete img;
		img=NULL;
	}
	img=new QImage*[iPageNumb];
	for(int page=0;page<iPageNumb;page++){
		img[page]=new QImage(iDotPerLine,iMaxLines,QImage::Format_RGB32);
		if(iLayerNumb==1){
			for(int Y=0;Y<iMaxLines;Y++){
				QRgb *pYLine=(QRgb *)img[page]->scanLine(Y);
				BYTE *pBuff=Buff[page][0]->GetY(Y);
				for(int X=0;X<iDotPerLine;X++)
					*pYLine++=qRgb(pBuff[X],pBuff[X],pBuff[X]);
			}
		}
		else if(iLayerNumb==3){
			for(int Y=0;Y<iMaxLines;Y++){
				QRgb *pYLine=(QRgb *)img[page]->scanLine(Y);
				BYTE *pRed	=Buff[page][0]->GetY(Y);
				BYTE *pGreen=Buff[page][1]->GetY(Y);
				BYTE *pBlue	=Buff[page][2]->GetY(Y);
				for(int X=0;X<iDotPerLine;X++)
					*pYLine++=qRgb(pRed[X],pGreen[X],pBlue[X]);
			}
		}
	}
	guMasterImage->GetCanvas()->SetImage(img[0]);

	//�Q�l���E���x�����O�����p�������̊m��
	ThresholdDotArray=new short*[iMaxLines];
	for(int Y=0;Y<iMaxLines;Y++)
		ThresholdDotArray[Y]=new short[iDotPerLine];

	guMasterImage->SetAreaSize(iDotPerLine,iMaxLines);
	guMasterImage->ZoomDrawWhole();
	QMessageBox::information(this,tr("Message"),"OK");
}

void Proofreader::pbThreshold_clicked()
{
	//�Q�l��
	if(StartPointX>EndPointX){
		int wX=EndPointX;
		EndPointX=StartPointX;
		StartPointX=wX;
	}
	if(StartPointY>EndPointY){
		int wY=EndPointY;
		EndPointY=StartPointY;
		StartPointY=wY;
	}
	Threshold=ui.sbThreshold->value();

	int i=iLayerNumb&0x02;
	int Index=ui.cbCamera->currentIndex();
	for(int Y=0;Y<iMaxLines;Y++){
		QRgb *pYLine=(QRgb *)img[Index]->scanLine(Y);
		for(int X=0;X<iDotPerLine;X++){
			if(X<StartPointX || X>=EndPointX || Y<StartPointY || Y>=EndPointY){
				ThresholdDotArray[Y][X]=-1;
				*pYLine++=qRgb(Buff[Index][0]->GetY(Y)[X],Buff[Index][i>>1]->GetY(Y)[X],Buff[Index][i]->GetY(Y)[X]);
				continue;
			}
			if(ui.chkReverse->isChecked()){
				if(GetThreshold(X,Y)<Threshold){
					ThresholdDotArray[Y][X]=0;
					*pYLine++=64770;
				}
				else{
					ThresholdDotArray[Y][X]=-1;
					*pYLine++=qRgb(Buff[Index][0]->GetY(Y)[X],Buff[Index][i>>1]->GetY(Y)[X],Buff[Index][i]->GetY(Y)[X]);
				}
			}
			else{
				if(GetThreshold(X,Y)>=Threshold){
					ThresholdDotArray[Y][X]=0;
					*pYLine++=64770;
				}
				else{
					ThresholdDotArray[Y][X]=-1;
					*pYLine++=qRgb(Buff[Index][0]->GetY(Y)[X],Buff[Index][i>>1]->GetY(Y)[X],Buff[Index][i]->GetY(Y)[X]);
				}
			}
		}
	}
	QMessageBox::information(this,tr("Message"),"OK");
}

void Proofreader::pbLabelingX_clicked()
{
	//���x�����O����
	int iLabel=1;
	CoGListX.clear();
	CoGListY.clear();
	for(int Y=0;Y<iMaxLines;Y++){
		for(int X=0;X<iDotPerLine;X++){
			if(ThresholdDotArray[Y][X]==0)
				SetLabel(X,Y,iLabel++);
		}
	}
	QMessageBox::information(this,tr("Message"),QString().setNum(iLabel-1));
	dxAverageList.clear();

	//�d�S�̕��ρi�h�b�g���j������
	int wX,wY,wwX,wwY;
	wX=wwX=CoGListX.at(0);
	wY=wwY=CoGListY.at(0);
	for(int XY=0,SumXY=CoGListX.at(0)+CoGListY.at(0);XY<CoGListX.count();XY++){
		if((CoGListX.at(XY)+CoGListY.at(XY))<SumXY){
			SumXY=CoGListX.at(XY)+CoGListY.at(XY);		//���ԍ����̏d�S�����߂�
			wX=wwX=CoGListX.at(XY);
			wY=wwY=CoGListY.at(XY);
		}
	}
	double SumX;
	for(int X=wX,i=0;X<iDotPerLine;X++){
		if(i>0){
			if(NextX(wwX,wwY)==false)		//X��(��)�����ɏd�S���T��
				break;
			X=wX=wwX;
			wY=wwY;
		}
		SumX=wX;
		nowAverageList.clear();
		nowAverageList << X;
		for(int Y=wY+1;Y<iMaxLines;Y++){			//Y��(�c)�����ɏd�S���T��
			if(ThresholdDotArray[Y][X]!=ThresholdDotArray[wY][wX] && ThresholdDotArray[Y][X]>0 && ThresholdDotArray[wY][wX]>0){
				nowAverageList << CoGListX.at(ThresholdDotArray[Y][X]-1);
				wX=CoGListX.at(ThresholdDotArray[Y][X]-1);
				Y=wY=CoGListY.at(ThresholdDotArray[Y][X]-1);
				X=wX;
			}
		}
		double SumAverageList=0;
		int YLine;
		int Y1=nowAverageList.count();
		int Y2=oldAverageList.count();
		if(i>0){
			for(YLine=0;YLine<nowAverageList.count() && YLine<oldAverageList.count();YLine++)
				SumAverageList+=(nowAverageList.at(YLine)-oldAverageList.at(YLine));
			dxAverageList << SumAverageList/YLine;
		}
		else{
			for(YLine=0;YLine<nowAverageList.count();YLine++)
				SumAverageList+=nowAverageList.at(YLine);
			dxAverageList << SumAverageList/YLine;
			i++;
		}
		oldAverageList=nowAverageList;
	}
	QMessageBox::information(this,tr("Message"),QString().setNum(dxAverageList.count()));
}

void Proofreader::pbLabelingY_clicked()
{
	//���x�����O����
	int iLabel=1;
	CoGListX.clear();
	CoGListY.clear();
	for(int Y=0;Y<iMaxLines;Y++){
		for(int X=0;X<iDotPerLine;X++){
			if(ThresholdDotArray[Y][X]==0)
				SetLabel(X,Y,iLabel++);
		}
	}
	QMessageBox::information(this,tr("Message"),QString().setNum(iLabel-1));
	dxAverageList.clear();

	//�d�S�̕��ρi�h�b�g���j������
	int wX,wY,wwX,wwY;
	wX=wwX=CoGListX.at(0);
	wY=wwY=CoGListY.at(0);
	for(int XY=0,SumXY=CoGListX.at(0)+CoGListY.at(0);XY<CoGListX.count();XY++){
		if((CoGListX.at(XY)+CoGListY.at(XY))<SumXY){
			SumXY=CoGListX.at(XY)+CoGListY.at(XY);		//���ԍ����̏d�S�����߂�
			wX=wwX=CoGListX.at(XY);
			wY=wwY=CoGListY.at(XY);
		}
	}
	double SumY;
	for(int Y=wY,i=0;Y<iMaxLines;Y++){
		if(i>0){
			if(NextY(wwX,wwY)==false)		//Y��(�c)�����ɏd�S���T��
				break;
			wX=wwX;
			Y=wY=wwY;
		}
		SumY=wY;
		nowAverageList.clear();
		nowAverageList << Y;
		for(int X=wX+1;X<iDotPerLine;X++){			//X��(��)�����ɏd�S���T��
			if(ThresholdDotArray[Y][X]!=ThresholdDotArray[wY][wX] && ThresholdDotArray[Y][X]>0 && ThresholdDotArray[wY][wX]>0){
				nowAverageList << CoGListY.at(ThresholdDotArray[Y][X]-1);
				wX=CoGListX.at(ThresholdDotArray[Y][X]-1);
				Y=wY=CoGListY.at(ThresholdDotArray[Y][X]-1);
				X=wX;
			}
		}
		double SumAverageList=0;
		int YLine;
		int Y1=nowAverageList.count();
		int Y2=oldAverageList.count();
		if(i>0){
			for(YLine=0;YLine<nowAverageList.count() && YLine<oldAverageList.count();YLine++)
				SumAverageList+=(nowAverageList.at(YLine)-oldAverageList.at(YLine));
			dxAverageList << SumAverageList/YLine;
		}
		else{
			for(YLine=0;YLine<nowAverageList.count();YLine++)
				SumAverageList+=nowAverageList.at(YLine);
			dxAverageList << SumAverageList/YLine;
			i++;
		}
		oldAverageList=nowAverageList;
	}
	QMessageBox::information(this,tr("Message"),QString().setNum(dxAverageList.count()));
}

void Proofreader::pbSave_clicked()
{
	//�t�@�C���ɍ��W���ۑ�
	QString MasterDotData=QFileDialog::getSaveFileName(
							this,tr("Save File"),"","CSV Data (*.csv)");
	if(MasterDotData=="")
		return;
	QFile file(MasterDotData);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	for(int i=0;i<dxAverageList.count();i++)
//	for(int i=2;i<dxAverageList.count()-1;i++)
		out << dxAverageList.at(i) << "\n";
	file.close();
}

void Proofreader::pbShowGraph_clicked()
{
	//�ʃE�B���h�E�ŃO���t���\��������
	ProofGraph GraphDialog(dxAverageList,iDotPerLine);
	GraphDialog.exec();
}

void Proofreader::pbShowGraphFromCsv_clicked()
{
	//�ʃE�B���h�E�œǍ�����Csv�t�@�C�������O���t���\��������
	QString CsvPath=QFileDialog::getOpenFileName(
							this,tr("Please choose a '.csv' file."),"","csv file (*.csv)");
	if(CsvPath.isEmpty())
		return;

	QFile	RFile(CsvPath);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return;

	dxAverageList.clear();

	QTextStream mystream(&RFile);
	QString myString;
	while (!mystream.atEnd()){
		myString=mystream.readLine();
		dxAverageList << myString.toDouble();
	}
	RFile.close();

	ProofGraph GraphDialog(dxAverageList,iDotPerLine);
	GraphDialog.exec();
}

void Proofreader::pbWhiteBalance_clicked()
{
	//�̈�
	if(StartPointX>EndPointX){
		int wX=EndPointX;
		EndPointX=StartPointX;
		StartPointX=wX;
	}
	if(StartPointY>EndPointY){
		int wY=EndPointY;
		EndPointY=StartPointY;
		StartPointY=wY;
	}
	if(StartPointX==0 && EndPointX==0 && StartPointY==0 && EndPointY==0){
		EndPointX=iDotPerLine;
		EndPointY=iMaxLines;
	}

	//�z���C�g�o�����X����
	RDataList.clear();
	GDataList.clear();
	BDataList.clear();
	int CountY=EndPointY-StartPointY;
	int Index=ui.cbCamera->currentIndex();
	for(int X=StartPointX;X<EndPointX;X++){
		int RData=0,GData=0,BData=0;
		for(int Y=StartPointY;Y<EndPointY;Y++){
			BYTE *pRed	=Buff[Index][0]->GetY(Y);
			BYTE *pGreen=Buff[Index][1]->GetY(Y);
			BYTE *pBlue	=Buff[Index][2]->GetY(Y);
			RData+=pRed[X];
			GData+=pGreen[X];
			BData+=pBlue[X];
		}
		RDataList.append(RData/CountY);
		GDataList.append(GData/CountY);
		BDataList.append(BData/CountY);
	}
	WhiteBalanceForm WhiteBalanceDialog(&RDataList,&GDataList,&BDataList,StartPointX);
	WhiteBalanceDialog.SetDotPerLine(iDotPerLine);
	WhiteBalanceDialog.exec();
}

void Proofreader::pbClose_clicked()
{
	close();
}

void Proofreader::SlotOnPaint(QPainter& Pnt)
{
	if(img==NULL)
		return;
	int Index=ui.cbCamera->currentIndex();
//	Pnt.drawImage(guMasterImage->GetMovx(),guMasterImage->GetMovy(),img->scaled(guMasterImage->width(),guMasterImage->height(),Qt::KeepAspectRatio));
//	int XXX=guMasterImage->GetMovx();
//	int YYY=guMasterImage->GetMovy();
//	Pnt.drawImage(guMasterImage->GetMovx(),guMasterImage->GetMovy(),img->copy(guMasterImage->GetMovx()/guMasterImage->GetZoomRate(),guMasterImage->GetMovy()/guMasterImage->GetZoomRate(),guMasterImage->width()/guMasterImage->GetZoomRate(),guMasterImage->height()/guMasterImage->GetZoomRate()).scaled(guMasterImage->width(),guMasterImage->height(),Qt::KeepAspectRatio));
//	Pnt.drawImage(0,0,img->copy(XonU+guMasterImage->GetMovx(),YonU+guMasterImage->GetMovy(),guMasterImage->width()/guMasterImage->GetZoomRate(),guMasterImage->height()/guMasterImage->GetZoomRate()).scaled(guMasterImage->width(),guMasterImage->height(),Qt::KeepAspectRatio));
///	Pnt.drawImage(0,0,img->copy(-guMasterImage->GetMovx(),-guMasterImage->GetMovy(),guMasterImage->width()/guMasterImage->GetZoomRate(),guMasterImage->height()/guMasterImage->GetZoomRate()).scaled(guMasterImage->width(),guMasterImage->height(),Qt::KeepAspectRatio));
	Pnt.drawImage(0,0,img[Index]->copy(-guMasterImage->GetMovx(),-guMasterImage->GetMovy(),guMasterImage->width()/guMasterImage->GetZoomRate(),guMasterImage->height()/guMasterImage->GetZoomRate()).scaled(guMasterImage->width(),guMasterImage->height(),Qt::KeepAspectRatio));
}

void Proofreader::tbExpansionToggled(bool Toggled)
{
	if(ui.tbRectangle->isDown())
		ui.tbRectangle->setChecked(false);
	ui.tbExpansion->setDown(Toggled);
}

void Proofreader::tbWholeClicked()
{
	guMasterImage->ZoomDrawWhole();
}

void Proofreader::tbRectangleToggled(bool Toggled)
{
	if(ui.tbExpansion->isDown())
		ui.tbExpansion->setChecked(false);
	if(Toggled)
		guMasterImage->SetMode(mtFrameDraw::fdRectangle);
	else
		guMasterImage->SetMode(mtFrameDraw::fdNone);
	ui.tbRectangle->setDown(Toggled);
}

void Proofreader::SlotMouseLDown(int X,int Y)
{
	if(ui.tbExpansion->isDown()){
		guMasterImage->ZoomIn((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		CntClick++;
	}
}

void Proofreader::SlotDrawEnd()
{
	if(ui.tbExpansion->isDown()){
		int X=guMasterImage->GetCanvas()->SData.UData.PointData.x;
		int Y=guMasterImage->GetCanvas()->SData.UData.PointData.y;
		guMasterImage->ZoomIn((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		CntClick++;
	}
	if(ui.tbRectangle->isDown()){
		StartPointX	=guMasterImage->GetCanvas()->SData.UData.RectangleData.x1;
		StartPointY	=guMasterImage->GetCanvas()->SData.UData.RectangleData.y1;
		EndPointX	=guMasterImage->GetCanvas()->SData.UData.RectangleData.x2;
		EndPointY	=guMasterImage->GetCanvas()->SData.UData.RectangleData.y2;
	}
}

void Proofreader::SlotMouseRDown(int X,int Y)
{
	if(ui.tbExpansion->isDown() && CntClick>0){
///		guMasterImage->ZoomOut((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		guMasterImage->ZoomOut((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		CntClick--;
	}
	if(ui.tbRectangle->isDown()){
		StartPointX	=0;
		StartPointY	=0;
		EndPointX	=0;
		EndPointY	=0;
	}
}
/*
void Proofreader::SlotMouseRDown(int X,int Y)
{
	if(ui.tbExpansion->isDown() && CntClick>0){
///		guMasterImage->ZoomOut((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		guMasterImage->ZoomOut((guMasterImage->GetMovx()+X)*guMasterImage->GetZoomRate(),(guMasterImage->GetMovy()+Y)*guMasterImage->GetZoomRate());
		CntClick--;
	}
	if(ui.tbRectangle->isDown() && CntDraw==1){
		StartPointX=0;
		StartPointY=0;
		CntDraw--;
	}
	else if(ui.tbRectangle->isDown() && CntDraw==2){
		EndPointX=0;
		EndPointY=0;
		CntDraw--;
	}
}
*/
void Proofreader::cbCameraIndexChanged(int Index)
{
	QImage *wImg=new QImage(iDotPerLine,iMaxLines,QImage::Format_RGB32);
	*wImg=*img[CurrentIndex];
	guMasterImage->GetCanvas()->SetImage(img[Index]);
	img[CurrentIndex]=wImg;
	CurrentIndex=Index;
}

void Proofreader::chkReverseToggled(bool Toggled)
{
}

void Proofreader::pbLoadPixHalconClicked()
{
	//HALCON��PIX���ǂ܂���
	QString MasterImagePath=QFileDialog::getOpenFileName(
							this,tr("Please choose a '.pix' file."),"","ImageBuffer (*.pix)");
	if(MasterImagePath.isEmpty())
		return;

	QFile	RFile(MasterImagePath);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return;

	int wiPageNumb	=iPageNumb;
	int wiLayerNumb	=iLayerNumb;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return;
	int	iYCountBase;
	if(::Load(&RFile,iPageNumb)==false)
		return;
	if(::Load(&RFile,iLayerNumb)==false)
		return;
	if(::Load(&RFile,iDotPerLine)==false)
		return;
	if(::Load(&RFile,iMaxLines)==false)
		return;
	if(::Load(&RFile,iYCountBase)==false)
		return;

	if(Buff!=NULL){
		for(int page=0;page<wiPageNumb;page++){
			for(int Layer=0;Layer<wiLayerNumb;Layer++){
				delete Buff[page][Layer];
				Buff[page][Layer]=NULL;
			}
			delete Buff[page];
			Buff[page]=NULL;
		}
		delete Buff;
		Buff=NULL;
	}

	ui.cbCamera->clear();
	Buff=new ImageBuffer**[iPageNumb];
	for(int page=0;page<iPageNumb;page++){
		Buff[page]=new ImageBuffer*[iLayerNumb];
		for(int Layer=0;Layer<iLayerNumb;Layer++){
			Buff[page][Layer]=new ImageBuffer();
			Buff[page][Layer]->Set(page,1,iDotPerLine,iMaxLines);
		}
	}
	for(int page=0;page<iPageNumb;page++){
		int	YCount=iYCountBase;
		int	TopY;
		for(TopY=0;TopY<iMaxLines;TopY+=YCount){
			if(TopY+YCount>iMaxLines)
				YCount=iMaxLines-TopY;
			int	Layer;
			for(Layer=0;Layer<iLayerNumb;Layer++){
				QByteArray Data=RFile.read(YCount*iDotPerLine);
				BYTE	*Src=(BYTE *)Data.data();
				int		YLenFromData=Data.size()/iDotPerLine;
				int		N=0;
				for(int y=TopY;y<TopY+YCount && N<YLenFromData;y++,N++){
					if(y<iMaxLines){
						memcpy(Buff[page][Layer]->GetY(y),Src,iDotPerLine);
						Src+=iDotPerLine;
					}
				}
			}
		}
	}
	//HALCON�ɓn��
//	for(int page=0;page<iPageNumb;page++){
//		XHalcon.CreateImage(Buff[page],iLayerNumb);
//	}

/*	//HALCON�ɓn��
	unsigned char *image=new unsigned char[iDotPerLine*iMaxLines];
	for(int page=0;page<iPageNumb;page++){
		if(iLayerNumb==1){
			for(int Y=0;Y<iMaxLines;Y++){
				BYTE *pBuff=Buff[page][0]->GetY(Y);
				for(int X=0;X<iDotPerLine;X++)
					image[Y*iDotPerLine+X]=pBuff[X];
			}
		}
		else if(iLayerNumb==3){
			for(int Y=0;Y<iMaxLines;Y++){
				BYTE *pBuff=Buff[page][0]->GetY(Y);
				for(int X=0;X<iDotPerLine;X++)
					image[Y*iDotPerLine+X]=pBuff[X];
			}
		}
	}
//	ExecuteHalcon(iDotPerLine,iMaxLines,image);
*/
}

/*
void Proofreader::mousePressEvent(QMouseEvent *event)
{
	int AAA=ui.dwMasterImage->geometry().left();
	int AA=guMasterImage->GetCanvas()->geometry().left();
	int BBB=ui.dwMasterImage->geometry().right();
	int BB=guMasterImage->GetVScroll()->geometry().width();
	if(event->x()>(ui.dwMasterImage->geometry().left()+guMasterImage->GetCanvas()->geometry().left()) && event->x()<ui.dwMasterImage->geometry().right()-guMasterImage->GetVScroll()->geometry().width()){
		if(event->y()>(ui.dwMasterImage->geometry().top()+guMasterImage->GetCanvas()->geometry().top()) && event->y()<ui.dwMasterImage->geometry().bottom()-guMasterImage->GetHScroll()->geometry().height()){
			guMasterImage->ZoomIn(event->x(),event->y());
		}
	}
}
*/
int Proofreader::GetThreshold(int X,int Y)
{
	int i=iLayerNumb&0x02;
	int Index=ui.cbCamera->currentIndex();
	return qGray(Buff[Index][0]->GetY(Y)[X],Buff[Index][i>>1]->GetY(Y)[X],Buff[Index][i]->GetY(Y)[X]);
}

void Proofreader::SetLabel(int iStartX,int iStartY,int iLabel)
{
	double Sumdx=0,Sumdy=0;
	ThresholdDotArray[iStartY][iStartX]=iLabel;		//�܂��J�n�ʒu�Ƀ��x�����ݒ�
//	ScanThreshold(iStartX,iStartY,iLabel);
	dxList << iStartX;
	dyList << iStartY;
	for(int i=0;i<dxList.count();i++){
		ScanThreshold(dxList.at(i),dyList.at(i),iLabel);
		Sumdx+=dxList.at(i);
		Sumdy+=dyList.at(i);
	}

	//�d�S�����߂�
	CoGListX << Sumdx/dxList.count();
	CoGListY << Sumdy/dyList.count();

	dxList.clear();
	dyList.clear();
//	ScanLabel(iStartX,iStartY,iLabel);
}

//��_�̎��蔪���𑖍����ă��x�����t�^
void Proofreader::ScanThreshold(int iStartX,int iStartY,int iLabel)
{
	if((iStartX+1)<iDotPerLine){
		if(ThresholdDotArray[iStartY][iStartX+1]==0){			//��_�̉E
			ThresholdDotArray[iStartY][iStartX+1]=iLabel;
			dxList << iStartX+1;
			dyList << iStartY;
		}
	}
	if((iStartX+1)<iDotPerLine && (iStartY+1)<iMaxLines){
		if(ThresholdDotArray[iStartY+1][iStartX+1]==0){			//��_�̉E��
			ThresholdDotArray[iStartY+1][iStartX+1]=iLabel;
			dxList << iStartX+1;
			dyList << iStartY+1;
		}
	}
	if((iStartY+1)<iMaxLines){
		if(ThresholdDotArray[iStartY+1][iStartX]==0){			//��_�̉�
			ThresholdDotArray[iStartY+1][iStartX]=iLabel;
			dxList << iStartX;
			dyList << iStartY+1;
		}
	}
	if((iStartX-1)>=0 && (iStartY+1)<iMaxLines){
		if(ThresholdDotArray[iStartY+1][iStartX-1]==0){			//��_�̍���
			ThresholdDotArray[iStartY+1][iStartX-1]=iLabel;
			dxList << iStartX-1;
			dyList << iStartY+1;
		}
	}
	if((iStartX-1)>=0){
		if(ThresholdDotArray[iStartY][iStartX-1]==0){			//��_�̍�
			ThresholdDotArray[iStartY][iStartX-1]=iLabel;
			dxList << iStartX-1;
			dyList << iStartY;
		}
	}
	if((iStartX-1)>=0 && (iStartY-1)>=0){
		if(ThresholdDotArray[iStartY-1][iStartX-1]==0){			//��_�̍���
			ThresholdDotArray[iStartY-1][iStartX-1]=iLabel;
			dxList << iStartX-1;
			dyList << iStartY-1;
		}
	}
	if((iStartY-1)>=0){
		if(ThresholdDotArray[iStartY-1][iStartX]==0){			//��_�̏�
			ThresholdDotArray[iStartY-1][iStartX]=iLabel;
			dxList << iStartX;
			dyList << iStartY-1;
		}
	}
	if((iStartX+1)<iDotPerLine && (iStartY-1)>=0){
		if(ThresholdDotArray[iStartY-1][iStartX+1]==0){			//��_�̉E��
			ThresholdDotArray[iStartY-1][iStartX+1]=iLabel;
			dxList << iStartX+1;
			dyList << iStartY-1;
		}
	}
}

bool Proofreader::NextX(int &X,int &Y)
{
	int wX=X,wY=Y;
	for(wX+=1;wX<iDotPerLine;wX++){
		if(ThresholdDotArray[wY][wX]!=ThresholdDotArray[Y][X] && ThresholdDotArray[wY][wX]>0 && ThresholdDotArray[Y][X]>0){
			X=CoGListX.at(ThresholdDotArray[wY][wX]-1);
			Y=CoGListY.at(ThresholdDotArray[wY][wX]-1);
			return true;
		}
	}
	return false;
}

bool Proofreader::NextY(int &X,int &Y)
{
	int wX=X,wY=Y;
	for(wY+=1;wY<iMaxLines;wY++){
		if(ThresholdDotArray[wY][wX]!=ThresholdDotArray[Y][X] && ThresholdDotArray[wY][wX]>0 && ThresholdDotArray[Y][X]>0){
			X=CoGListX.at(ThresholdDotArray[wY][wX]-1);
			Y=CoGListY.at(ThresholdDotArray[wY][wX]-1);
			return true;
		}
	}
	return false;
}