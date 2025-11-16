/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\ImageDataUnit.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ImageDataUnit.h"
#include "RepairBase.h"
#include <QPainter>
#include <QMenu>
#include <QContextMenuEvent>
#include <QFile>
#include <QTextStream>

#include <QMessageBox>

//**********************************
//　画像データ格納クラスユニット
//**********************************
ImageDataUnit::ImageDataUnit()
{
}

ImageDataUnit::~ImageDataUnit()
{
	for(int Cnt=0;Cnt<MImageClassList.count();Cnt++)
		delete MImageClassList[Cnt];
	for(int Cnt=0;Cnt<MImagePieceList.count();Cnt++)
		delete MImagePieceList[Cnt];
	for(int Cnt=0;Cnt<NGImagePieceList.count();Cnt++)
		delete NGImagePieceList[Cnt];
	for(int Cnt=0;Cnt<CImageList.count();Cnt++)
		delete CImageList[Cnt];
}

//画像データクラスをリストに格納
void	ImageDataUnit::AddImage(MasterImage *ImageClass)
{
	MImageClassList.append(ImageClass);
}
void	ImageDataUnit::ReplaceImage(int Index,MasterImage *ImageClass)
{
	MImageClassList.replace(Index,ImageClass);
}

void	ImageDataUnit::AddImage(MasterImagePiece *ImageClass)
{
	MImagePieceList.append(ImageClass);
}

void	ImageDataUnit::AddImage(NGImagePiece *ImageClass)
{
	NGImagePieceList.append(ImageClass);
}

void	ImageDataUnit::AddImage(CameraImage *ImageClass)
{
	CImageList.append(ImageClass);
}

void	ImageDataUnit::AddImage(CameraSnapImage *ImageClass)
{
	CSnapImageList.append(ImageClass);
}

void	ImageDataUnit::AddImage(MasterSnapImage *ImageClass)
{
	MSnapImageList.append(ImageClass);
}

//画像の並べ方の設定
void	ImageDataUnit::SetAlignment(MasterImage *ImageClass, AlignmentType type)
{
}

void	ImageDataUnit::SetAlignment(MasterImagePiece *ImageClass, AlignmentType type)
{
}

void	ImageDataUnit::SetAlignment(NGImagePiece *ImageClass, AlignmentType type)
{
}

void	ImageDataUnit::SetAlignment(CameraImage *ImageClass, AlignmentType type)
{
}
//********************************************
//　画像クラスベース
//********************************************
ImageBase::ImageBase(QWidget *parent)
{
	ImgParent=parent;
	MScaledX=MScaledY=wX=wY=wMScaled=1;
	Matrix.reset();
	ImageRotation=0;
}

ImageBase::~ImageBase()
{
}
/*
void ImageBase::SetMAreaSize(int xlen,int ylen)
{
	UniverseX=xlen;
	UniverseY=ylen;
	wMScaled=1;
	Matrix.reset();
}
*/
void ImageBase::SetMAreaSize(int xlen,int ylen)
{
	if(ImageRotation==0 || ImageRotation==180){
		UniverseX=xlen;
		UniverseY=ylen;
	}
	else if(ImageRotation==90 || ImageRotation==-90){
		UniverseX=ylen;
		UniverseY=xlen;
	}
	wMScaled=1;
	Matrix.reset();
}

void ImageBase::SetWholeImage(int CanvasWidth,int CanvasHeight)
{
	double W,H;
	Matrix.reset();
	Scaled=(W=(double)CanvasWidth/UniverseX)<(H=(double)CanvasHeight/UniverseY) ? W : H;
	Matrix.scale(Scaled,Scaled);
}

void ImageBase::SetMScaledX(double X)
{
	MScaledX=X/wX;
	wX=X;
	Matrix.scale(MScaledX,MScaledY);
}

void ImageBase::SetMScaledY(double Y)
{
	MScaledY=Y/wY;
	wY=Y;
	Matrix.scale(MScaledX,MScaledY);
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void ImageBase::GetUniverseToCanvas(double ux,double uy,int &gx,int &gy)
{
	gx=ux*Scaled;
	gy=uy*Scaled;
}

//色範囲を0-255でループするように設定
int ImageBase::ColorClip(int ColorInt,double dColor,int i)
{
	int RetColorInt=ColorInt+dColor*i;
	if(RetColorInt>255)
		return RetColorInt-255;
	return RetColorInt;
}

void ImageBase::AlgColorGet(QString Str, QList<QPair<QString, QString> > citemList, QColor &color)
{//アルゴリズム別エラーの丸表示の色設定
	color=QColor(Qt::red);
	int count=citemList.count();
	for(int i=0; i<count; i++){
		QPair<QString, QString> item = citemList[i];
		//QString str = "Peter Pan";
		//str.contains("peter", Qt::CaseInsensitive);
		//if(Str.contains(item.first, Qt::CaseInsensitive)==true){
		if(Str.mid(Str.indexOf(":")+1)==item.first){
			color=QColor(item.second);
			return;
		}
	}
}
//********************************************
//　マスター画像格納クラス
//********************************************
MasterImage::MasterImage(QWidget *parent) : ImageBase(this)
{
	RectWidth=RectHeight=0;
	Wid=Hei=0;
	NGDotColor=QColor(Qt::red);
	NGDotWidth=3;
	PieceRectColor=QColor(Qt::magenta);
	PieceRectWidth=2;
	PieceRectStyle=Qt::SolidLine;
	wRectX=wRectY=wRectWidth=wRectHeight=0;
	SetMode(fdNone);
	gmovx=gmovy=0;
}

MasterImage::~MasterImage()
{
	for(int Cnt=0;Cnt<ImageList.count();Cnt++){
		if(ImageList[Cnt]!=NULL)
			delete ImageList[Cnt];
	}
	ImageList.clear();
}

void MasterImage::DrawPaint(QPainter &MPnt)
{
	//画像の描画
	for(int Cnt=0;Cnt<CameraNumb;Cnt++){
		int gx,gy;
		GetUniverseToCanvas(ImageList[Cnt]->OffsetX,ImageList[Cnt]->OffsetY,gx,gy);
		GetUniverseToCanvas(movx,movy,gmovx,gmovy);
//		MPnt.drawImage(gx,gy,ImageList[Cnt]->Image->transformed(Matrix));
		MPnt.drawImage(gx+gmovx,gy+gmovy,ImageList[Cnt]->Image->transformed(Matrix));
	}
}

void MasterImage::SetPieceDraw(int CanvasWidth,int CanvasHeight,double ExpRate)
{
	Wid=CanvasWidth;
	Hei=CanvasHeight;
	MImagePieceExpand=ExpRate;


}

//void MasterImage::DrawNGDot(QPainter &Pnt,QTableWidget *W,int Index,NPListPack<NGPointList> *pNGPointList,int NGCnt, QList<QPair<QString, QString> > citemList)
void MasterImage::DrawNGDot(QPainter &Pnt,QTableWidget *W,int Index,NPListPack<NGPointList> *pNGPointList,NPListPack<NGPointBaseList> *pNoImageNGPointList,int NGCnt, QList<QPair<QString, QString> > citemList)
{
	//マスター全体画像上にNGポイントを表示
	for(int Row=0;Row<NGCnt;Row++){
		for(NGPointList *P=pNGPointList[Row].GetFirst();P!=NULL;P=P->GetNext()){
			int gX,gY;
			GetUniverseToCanvas(P->x>>ImgRate,P->y>>ImgRate,gX,gY);	
			AlgColorGet(P->colorAlg, citemList, NGDotColor);
			Pnt.fillRect(gX-(NGDotWidth>>1)+gmovx,gY-(NGDotWidth>>1)+gmovy,NGDotWidth,NGDotWidth,NGDotColor);
		}
	}
	for(NGPointBaseList *PBase=pNoImageNGPointList->GetFirst();PBase!=NULL;PBase=PBase->GetNext()){
		for(NGPointList *P=PBase->NGListForVRS.GetFirst();P!=NULL;P=P->GetNext()){
			int gX,gY;
			GetUniverseToCanvas(P->x>>ImgRate,P->y>>ImgRate,gX,gY);	
			AlgColorGet(P->colorAlg, citemList, NGDotColor);
			Pnt.fillRect(gX-(NGDotWidth>>1)+gmovx,gY-(NGDotWidth>>1)+gmovy,NGDotWidth,NGDotWidth,NGDotColor);
		}
	}
}

void MasterImage::DrawPieceRect(QPainter &Pnt)
{
	//表示エリア矩形の描画
	Pnt.setPen(QPen(PieceRectColor,PieceRectWidth,PieceRectStyle));
	Pnt.drawRect(RectX+gmovx,RectY+gmovy,RectWidth,RectHeight);

}

void MasterImage::DrawRect(QPainter &Pnt, QRect &rect, QPen &pen)
{
	//Pnt.setPen(pen);
	//Pnt.drawRect(rect);
}

void MasterImage::DrawRect(QRect &rect, QPen &pen)
{
	//Pnt.setPen(pen);
	//Pnt.drawRect(rect);
	//repaint();
}

//Show piece information(XML)
void MasterImage::DrawPieceInfo(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QColor PieceColor,QStringList *NGAreaNameList,QStringList *AreaNameList)
{
	//NULLチェック
	if(pPieceInfoDataList==NULL){
		return;
	}

	int	PieceColorAlpha	=100;
	Pnt.setFont(QFont("Helvetica", 15));
	PieceColor.setAlpha(100);
	Pnt.setPen(QPen(PieceColor));
	QColor NGAreaColor=QColor(Qt::yellow);
	NGAreaColor.setAlpha(PieceColorAlpha);

//	int		PieceColorRed	=PieceColor.red();
//	int		PieceColorGreen	=PieceColor.green();
//	int		PieceColorBlue	=PieceColor.blue();
//	double	dPieceColor		=255.0/AreaNameList->count();

	for(int i=0;i<Count;i++){
		//NULLチェック
		if(pPieceInfoDataList[i].PieceCoordinates==NULL){
			continue;
		}
		//現在のNG位置の個片を網掛けする
		QStringList CurrentPieceNameList=CurrentPieceName.split(',');
		for(int j=0;j<CurrentPieceNameList.count();j++){
			if(pPieceInfoDataList[i].GetPieceName()==CurrentPieceNameList[j]){
				Pnt.setBrush(PieceColor);
				break;
			}
		}
		//NGとされた個片を網掛けする
		if(NGAreaNameList->contains(pPieceInfoDataList[i].GetPieceName())==true){
			Pnt.setBrush(NGAreaColor);
		}
		//個片ごとに色分けする
///		PieceColor.setRgb(ColorClip(PieceColorRed,dPieceColor,i),ColorClip(PieceColorGreen,dPieceColor,i),ColorClip(PieceColorBlue,dPieceColor,i),PieceColorAlpha);
///		Pnt.setPen(QPen(PieceColor));
		switch(AreaNameList->indexOf(pPieceInfoDataList[i].GetPieceName())){
			case 1:
			case 7:
			case 13:
				Pnt.setPen(QPen(QColor(Qt::blue)));
				break;
			case 2:
			case 8:
			case 14:
				Pnt.setPen(QPen(QColor(Qt::cyan)));
				break;
			case 3:
			case 9:
			case 15:
				Pnt.setPen(QPen(QColor(Qt::magenta)));
				break;
			case 4:
			case 10:
			case 16:
				Pnt.setPen(QPen(QColor(Qt::yellow)));
				break;
			case 5:
			case 11:
			case 17:
				Pnt.setPen(QPen(QColor(Qt::gray)));
				break;
			case 6:
			case 12:
			case 18:
				Pnt.setPen(QPen(Qt::white));
				break;
			default:
				Pnt.setPen(QPen(QColor(Qt::green)));
		}
		switch(pPieceInfoDataList[i].GetPieceShape()){
			case 'R':
				int gX1,gY1;
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[0].X>>ImgRate,pPieceInfoDataList[i].PieceCoordinates[0].Y>>ImgRate,gX1,gY1);
				int gX2,gY2;
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[1].X>>ImgRate,pPieceInfoDataList[i].PieceCoordinates[1].Y>>ImgRate,gX2,gY2);
				int OffsetX1,OffsetY1;
				GetUniverseToCanvas(ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetX,ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetY,OffsetX1,OffsetY1);
				int OffsetX2,OffsetY2;
				int LastPiecePage;
				if((LastPiecePage=pPieceInfoDataList[i].GetLastPiecePage())>=0){
					GetUniverseToCanvas(ImageList[LastPiecePage]->OffsetX,ImageList[LastPiecePage]->OffsetY,OffsetX2,OffsetY2);
				}
				Pnt.drawRect(gmovx+gX1+OffsetX1,gmovy+gY1+OffsetY1,gX2+OffsetX2-gX1-OffsetX1,gY2+OffsetY2-gY1-OffsetY1);
				Pnt.drawText(gmovx+gX1+OffsetX1,gmovy+gY1+OffsetY1,gX2+OffsetX2-gX1-OffsetX1,gY2+OffsetY2-gY1-OffsetY1,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
			case 'E':
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[0].X>>ImgRate,pPieceInfoDataList[i].PieceCoordinates[0].Y>>ImgRate,gX1,gY1);
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[1].X>>ImgRate,pPieceInfoDataList[i].PieceCoordinates[1].Y>>ImgRate,gX2,gY2);
				Pnt.drawEllipse	(gX1,gY1,gX2-gX1,gY2-gY1);
				Pnt.drawText	(gX1,gY1,gX2-gX1,gY2-gY1,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
			case 'P':
				QPolygon polygon;
//				int Size=sizeof(pPieceInfoDataList[i].PieceCoordinates)/sizeof(pPieceInfoDataList[i].PieceCoordinates[0]);
//				for(int Cnt=0;Cnt<Size;Cnt++){
				for(int Cnt=0;Cnt<pPieceInfoDataList[i].DataCount;Cnt++){
					int gX,gY;
					GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[Cnt].X>>ImgRate,pPieceInfoDataList[i].PieceCoordinates[Cnt].Y>>ImgRate,gX,gY);
					polygon << QPoint(gX,gY);
				}
				Pnt.drawConvexPolygon(polygon);
				int MinX=0,MinY=0,MaxX=0,MaxY=0;
//				for(int Cnt=0;Cnt<Size;Cnt++){
				for(int Cnt=0;Cnt<pPieceInfoDataList[i].DataCount;Cnt++){
					int X,Y;
					if(MinX>(X=polygon.point(Cnt).x()))
						MinX=X;
					else if(MaxX<X)
						MaxX=X;
					if(MinY>(Y=polygon.point(Cnt).y()))
						MinY=Y;
					else if(MaxY<Y)
						MaxY=Y;
				}
				Pnt.drawText(MinX,MinY,MaxX-MinX,MaxY-MinY,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
		}
		Pnt.setBrush(QColor(0,0,0,0));
	}
}

void MasterImage::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	int gw,gh;
	GetUniverseToCanvas(Wid/MImagePieceExpand,Hei/MImagePieceExpand,gw,gh);

	if((RectX=x-(gw>>1))<0)
		RectX=0;
	if((RectY=y-(gh>>1))<0)
		RectY=0;

	MMouseLDown(RectX,RectY,gw,gh,true);
}

//SignalMMouseLDownのスロット
void MasterImage::SlotMMouseLDown(int x,int y,int w,int h)
{
	uX=x;
	uY=y;
	uW=w;
	uH=h;
	//データ座標を画面座標に変換する
	int gX,gY,gW,gH;
	GetUniverseToCanvas(uX,uY,gX,gY);
	GetUniverseToCanvas(uW,uH,gW,gH);

	MMouseLDown(gX,gY,gW,gH,false);
}

void MasterImage::MMouseLDown(int x,int y,int w,int h,bool FlagTrans)
{
	RectX=x;
	RectY=y;
	RectWidth=w;
	RectHeight=h;

	if(RectX==wRectX && RectY==wRectY && RectWidth==wRectWidth && RectHeight==wRectHeight){
		repaint();
		return;
	}


	//再描画
	wRectX=RectX;
	wRectY=RectY;
	wRectWidth=RectWidth;
	wRectHeight=RectHeight;
	if(!FlagTrans){
		repaint();
	}

	//拡大率の設定
//	ZoomRate=MScaled;
	ZoomRate=Scaled;

	//シグナルの発行
	if(FlagTrans){
		GetCanvasToUniverse(RectX,RectY,uX,uY);
		RectX-=gmovx;
		RectY-=gmovy;
	}
	emit SignalOnMouseLDown(uX,uY,this);
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void MasterImage::GetUniverseToCanvas(double ux,double uy,int &gx,int &gy)
{
	gx=ux*ZoomRate;
	gy=uy*ZoomRate;
}

void MasterImage::SetExpand()
{
	ZoomRate=Scaled;
}

//画像の輝度補正
void MasterImage::SetMasterBrightness(int Brightness[])
{
	for(int Page=0;Page<ImageList.count();Page++){
		ImageList[Page]->SetMasterBrightness(Brightness);
	}
}

//保持座標のクリア
void MasterImage::wRectClear()
{
	wRectX=0;
	wRectY=0;
	wRectWidth=0;
	wRectHeight=0;
}

void MasterImage::mouseMoveEvent(QMouseEvent *e)
{
	mtFrameDraw::mouseMoveEvent(e);

}
//********************************************
//　個片マスター画像格納クラス
//********************************************
MasterImagePiece::MasterImagePiece(QWidget *parent) : ImageBase(this)
{
	SetMode(mtFrameDraw::fdNone);
	ExpRate=1;
}

MasterImagePiece::~MasterImagePiece()
{
}

void MasterImagePiece::SetZoomRate(double Exp)
{
	ExpRate=Exp;
}

void MasterImagePiece::DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase,int Side)
{
	//画像の描画
//	int		AAA=-GetMovx();
//	int		BBB=-GetMovy();
//	int		CCC=GetCanvasWidth();
//	int		DDD=GetCanvasHeight();
//	double	EEE=GetZoomRate();
	int uW=GetCanvasWidth()/GetZoomRate();
	int uH=GetCanvasHeight()/GetZoomRate();
	QMatrix matrix;
	matrix.scale(IDBase->MImageClassList[Side]->ImgRateCount,IDBase->MImageClassList[Side]->ImgRateCount);
	int TransMovx=(GetMovx()>>IDBase->MImageClassList[Side]->ImgRate);
	int TransMovy=(GetMovy()>>IDBase->MImageClassList[Side]->ImgRate);
	for(int Cnt=0;Cnt<IDBase->MImageClassList[Side]->ImageList.count();Cnt++){
		int uOffsetX=IDBase->MImageClassList[Side]->ImageList[Cnt]->OffsetX;
		int uOffsetY=IDBase->MImageClassList[Side]->ImageList[Cnt]->OffsetY;
		int ImageW=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->width();
		int ImageH=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->height();
		//選択矩形が画像中に収まる場合
		if(-TransMovx>=uOffsetX && (-TransMovx+uW)<=(uOffsetX+ImageW) && -TransMovy>=uOffsetY && (-TransMovy+uH)<=(uOffsetY+ImageH)){
			Pnt.drawImage(0,0,Image=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(-TransMovx-uOffsetX,-TransMovy-uOffsetY,uW,uH).transformed(matrix));
			break;
		}
		else{
			int X,Y,W,H;
			//選択矩形が画像の右端をまたぐ場合
			if(-TransMovx<(uOffsetX+ImageW) && (-TransMovx+uW)>(uOffsetX+ImageW) && (-TransMovy+uH)>=uOffsetY && -TransMovy<(uOffsetY+ImageH))
				Pnt.drawImage(0,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,Image=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(-TransMovx-uOffsetX,-TransMovy-uOffsetY+Y,uOffsetX+ImageW+TransMovx,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
			//選択矩形が画像の左端をまたぐ場合
			else if(-TransMovx<uOffsetX && (-TransMovx+uW)>uOffsetX && (-TransMovy+uH)>=uOffsetY && -TransMovy<(uOffsetY+ImageH))
				Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,Image=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
			//選択矩形が画像の下端をまたぐ場合
			else if(-TransMovy<(uOffsetY+ImageH) && (-TransMovy+uH)>(uOffsetY+ImageH) && (-TransMovx+uW)>=uOffsetX && -TransMovx<(uOffsetX+ImageW))
				Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,Image=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
			//選択矩形が画像の上端をまたぐ場合
			else if(-TransMovy<uOffsetY && (-TransMovy+uH)>uOffsetY && (-TransMovx+uW)>=uOffsetX && -TransMovx<(uOffsetX+ImageW))
				Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,Image=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
		}
	}
	//シグナルの発行
	int gx,gy;
	MScaled=IDBase->MImageClassList[Side]->MScaled;
	GetUniverseToCanvas(-TransMovx+(((int)(GetCanvasWidth()/GetZoomRate()))>>1),-TransMovy+(((int)(GetCanvasHeight()/GetZoomRate()))>>1),gx,gy);
	emit SignalOnPieceRectChange(gx,gy);
}

void MasterImagePiece::DrawNoPaint(QPainter &Pnt)
{
	//画像の描画
	Pnt.setPen(QColor(Qt::lightGray));
	Pnt.drawRect(0,0,GetCanvasWidth(),GetCanvasHeight());
}

//********************************************
//　個片ＮＧ画像格納クラス
//********************************************
NGImagePiece::NGImagePiece(QWidget *parent) : ImageBase(this)
{
	SetMode(mtFrameDraw::fdNone);
	Image=wImage=NULL;
	NGPointVisible=true;
	NGMarkSize=10;
	PieceLineVisible=false;
	NoNGColor=QColor(Qt::blue);

	shiftX=0;
	shiftY=0;
}

NGImagePiece::~NGImagePiece()
{
}

void NGImagePiece::SetZoomRate(double Exp)
{
	matrix.reset();
	matrix.scale(Exp,Exp);
}

//void NGImagePiece::DrawPaint(QPainter &Pnt)
void NGImagePiece::AddImage(QImage *image, int posX, int posY){
	Image = image;
	shiftX = posX;
	shiftY = posY;
}

bool NGImagePiece::hasImage(){
	if(Image==NULL)
		return false;
	else
		return true;
}

void NGImagePiece::delImage(){
	if(Image)
		delete Image;
	Image = NULL;
}

void NGImagePiece::SetImageTopLeftPos(int posX, int posY){
	shiftX = posX;
	shiftY = posY;
}

QImage* NGImagePiece::GetImage(){
	return Image;
}

void NGImagePiece::DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase,int Side)
{
	//画像の回転角度による座標変換
	int CanvasWidth,CanvasHeight;
	if(ImageRotation==0 || ImageRotation==180){
		CanvasWidth	=GetCanvasWidth();
		CanvasHeight=GetCanvasHeight();
	}
	else{
		CanvasWidth	=GetCanvasHeight();
		CanvasHeight=GetCanvasWidth();
	}

	//画像の描画
	if(Image!=NULL){
//		QMatrix matrix;
//		matrix.scale(GetZoomRate(),GetZoomRate());
		Pnt.drawImage((GetMovx() + shiftX)*GetZoomRate(),(GetMovy() + shiftY)*GetZoomRate(),Image->transformed(matrix));
	}
	else{
///		int uW=CanvasWidth/IDBase->MImagePieceList[0]->GetZoomRate();
///		int uH=CanvasHeight/IDBase->MImagePieceList[0]->GetZoomRate();
		int uW=CanvasWidth/matrix.m11();
		int uH=CanvasHeight/matrix.m22();
//		QMatrix matrix;
//		matrix.scale(IDBase->MImageClassList[Side]->ImgRateCount,IDBase->MImageClassList[Side]->ImgRateCount);
		int TransMovx=(GetMovx()>>IDBase->MImageClassList[Side]->ImgRate);
		int TransMovy=(GetMovy()>>IDBase->MImageClassList[Side]->ImgRate);
		for(int Cnt=0;Cnt<IDBase->MImageClassList[Side]->ImageList.count();Cnt++){
			int uOffsetX=IDBase->MImageClassList[Side]->ImageList[Cnt]->OffsetX;
			int uOffsetY=IDBase->MImageClassList[Side]->ImageList[Cnt]->OffsetY;
			int ImageW=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->width();
			int ImageH=IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->height();
			//選択矩形が画像中に収まる場合
			if(-TransMovx>=uOffsetX && (-TransMovx+uW)<=(uOffsetX+ImageW) && -TransMovy>=uOffsetY && (-TransMovy+uH)<=(uOffsetY+ImageH)){
				Pnt.drawImage(0,0,IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(-TransMovx-uOffsetX,-TransMovy-uOffsetY,uW,uH).transformed(matrix));
				break;
			}
			else{
				int X,Y,W,H;
				//選択矩形が画像の右端をまたぐ場合
				if(-TransMovx<(uOffsetX+ImageW) && (-TransMovx+uW)>(uOffsetX+ImageW) && (-TransMovy+uH)>=uOffsetY && -TransMovy<(uOffsetY+ImageH))
					Pnt.drawImage(0,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(-TransMovx-uOffsetX,-TransMovy-uOffsetY+Y,uOffsetX+ImageW+TransMovx,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
				//選択矩形が画像の左端をまたぐ場合
				else if(-TransMovx<uOffsetX && (-TransMovx+uW)>uOffsetX && (-TransMovy+uH)>=uOffsetY && -TransMovy<(uOffsetY+ImageH))
					Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
				//選択矩形が画像の下端をまたぐ場合
				else if(-TransMovy<(uOffsetY+ImageH) && (-TransMovy+uH)>(uOffsetY+ImageH) && (-TransMovx+uW)>=uOffsetX && -TransMovx<(uOffsetX+ImageW))
					Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
				//選択矩形が画像の上端をまたぐ場合
				else if(-TransMovy<uOffsetY && (-TransMovy+uH)>uOffsetY && (-TransMovx+uW)>=uOffsetX && -TransMovx<(uOffsetX+ImageW))
					Pnt.drawImage((uOffsetX+TransMovx)<<IDBase->MImageClassList[Side]->ImgRate,Y=(-TransMovy<uOffsetY) ? (uOffsetY+TransMovy)<<IDBase->MImageClassList[Side]->ImgRate : 0,IDBase->MImageClassList[Side]->ImageList[Cnt]->Image->copy(0,-TransMovy-uOffsetY+Y,-TransMovx+uW-uOffsetX,((-TransMovy+uH)>(H=uOffsetY+ImageH)) ? H+TransMovy : uH-Y).transformed(matrix));
			}
		}
	}
}

void NGImagePiece::DrawNoPaint(QPainter &Pnt)
{
	//画像の描画
	Pnt.setPen(QColor(Qt::lightGray));
	Pnt.drawRect(0,0,GetCanvasWidth(),GetCanvasHeight());
}

void NGImagePiece::DrawNGPoint(QPainter &Pnt,int &MaxPointX,int &MinPointX,int &MaxPointY,int &MinPointY, QList<QPair<QString, QString> > citemList)
{
	//NGがない場合の判断
	if(NGList.GetNumber()==0){
		return;
	}

	if(NGPointVisible==false){
		return;
	}

	//NG赤丸の描画
	//Pnt.setPen(QPen(QColor(Qt::red),2));
	//Pnt.setPen(QPen(QColor(Qt::red),2));
	int PointX,PointY;
	QColor color;
	QString Str;
	MaxPointX=MinPointX=NGList.GetFirst()->x;
	MaxPointY=MinPointY=NGList.GetFirst()->y;
	for(NGPointList *P=NGList.GetFirst();P!=NULL;P=P->GetNext()){
		PointX=P->x;
		PointY=P->y;
		Str=P->colorAlg;
		AlgColorGet(Str, citemList, color);
		//NG丸の描画
		if(NGImageExist==true){
			Pnt.setPen(QPen(color,2));
		}
		else{
///			//NG画像が無い場合、青丸で表示
///			Pnt.setPen(QPen(QColor(Qt::blue),2));
			//NG画像が無い場合の丸色
			Pnt.setPen(QPen(NoNGColor,2));
		}
		Pnt.drawEllipse((PointX+GetMovx()+Dx)*GetZoomRate()-(NGMarkSize>>1),(PointY+GetMovy()+Dy)*GetZoomRate()-(NGMarkSize>>1),NGMarkSize,NGMarkSize);
		//NGのX,Y座標の最小値と最大値を求める
		if(PointX>MaxPointX)
			MaxPointX=PointX;
		if(PointX<MinPointX)
			MinPointX=PointX;
		if(PointY>MaxPointY)
			MaxPointY=PointY;
		if(PointY<MinPointY)
			MinPointY=PointY;
	}
}

void NGImagePiece::DrawMPaint(QPainter &Pnt,ImageDataUnit *IDBase)
{
	//画像の描画
	QMatrix matrix;
	matrix.scale(GetZoomRate(),GetZoomRate());
	int uW=GetCanvasWidth()/GetZoomRate();
	int uH=GetCanvasHeight()/GetZoomRate();
	for(int MCnt=0;MCnt<IDBase->MImageClassList.count();MCnt++){
		for(int Cnt=0;Cnt<IDBase->MImageClassList[MCnt]->ImageList.count();Cnt++){
			int uOffsetX=IDBase->MImageClassList[MCnt]->ImageList[Cnt]->OffsetX;
			int uOffsetY=IDBase->MImageClassList[MCnt]->ImageList[Cnt]->OffsetY;
			int ImageW=IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->width();
			int ImageH=IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->height();
			//選択矩形が画像中に収まる場合
			if(-GetMovx()>=uOffsetX && (-GetMovx()+uW)<=(uOffsetX+ImageW) && -GetMovy()>=uOffsetY && (-GetMovy()+uH)<=(uOffsetY+ImageH))
				Pnt.drawImage(0,0,IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->copy(-GetMovx()-uOffsetX,-GetMovy()-uOffsetY,uW,uH).transformed(matrix));
			else{
				int X,Y,W,H;
				//選択矩形が画像の右端をまたぐ場合
				if(-GetMovx()<(uOffsetX+ImageW) && (-GetMovx()+uW)>(uOffsetX+ImageW) && (-GetMovy()+uH)>=uOffsetY && -GetMovy()<(uOffsetY+ImageH))
					Pnt.drawImage(0,Y=(-GetMovy()<uOffsetY) ? (uOffsetY+GetMovy())*GetZoomRate() : 0,IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->copy(-GetMovx()-uOffsetX,-GetMovy()-uOffsetY+Y,uOffsetX+ImageW+GetMovx(),((-GetMovy()+uH)>(H=uOffsetY+ImageH)) ? H+GetMovy() : uH-Y).transformed(matrix));
				//選択矩形が画像の左端をまたぐ場合
				else if(-GetMovx()<uOffsetX && (-GetMovx()+uW)>uOffsetX && (-GetMovy()+uH)>=uOffsetY && -GetMovy()<(uOffsetY+ImageH))
					Pnt.drawImage((uOffsetX+GetMovx())*GetZoomRate(),Y=(-GetMovy()<uOffsetY) ? (uOffsetY+GetMovy())*GetZoomRate() : 0,IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->copy(0,-GetMovy()-uOffsetY+Y,-GetMovx()+uW-uOffsetX,((-GetMovy()+uH)>(H=uOffsetY+ImageH)) ? H+GetMovy() : uH-Y).transformed(matrix));
				//選択矩形が画像の下端をまたぐ場合
				else if(-GetMovy()<(uOffsetY+ImageH) && (-GetMovy()+uH)>(uOffsetY+ImageH) && (-GetMovx()+uW)>=uOffsetX && -GetMovx()<(uOffsetX+ImageW))
					Pnt.drawImage((uOffsetX+GetMovx())*GetZoomRate(),Y=(-GetMovy()<uOffsetY) ? (uOffsetY+GetMovy())*GetZoomRate() : 0,IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->copy(0,-GetMovy()-uOffsetY+Y,-GetMovx()+uW-uOffsetX,((-GetMovy()+uH)>(H=uOffsetY+ImageH)) ? H+GetMovy() : uH-Y).transformed(matrix));
				//選択矩形が画像の上端をまたぐ場合
				else if(-GetMovy()<uOffsetY && (-GetMovy()+uH)>uOffsetY && (-GetMovx()+uW)>=uOffsetX && -GetMovx()<(uOffsetX+ImageW))
					Pnt.drawImage((uOffsetX+GetMovx())*GetZoomRate(),Y=(-GetMovy()<uOffsetY) ? (uOffsetY+GetMovy())*GetZoomRate() : 0,IDBase->MImageClassList[MCnt]->ImageList[Cnt]->Image->copy(0,-GetMovy()-uOffsetY+Y,-GetMovx()+uW-uOffsetX,((-GetMovy()+uH)>(H=uOffsetY+ImageH)) ? H+GetMovy() : uH-Y).transformed(matrix));
			}
		}
	}
}

//個片枠の表示
void NGImagePiece::DrawPieceLine(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QStringList *AreaNameList,MasterImage *MImage)
{
	if(PieceLineVisible==false){
		return;
	}

	int	PieceColorAlpha	=100;
//	Pnt.setFont(QFont("Helvetica", 15));
//	PieceColor.setAlpha(100);
//	Pnt.setPen(QPen(PieceColor));
//	QColor PieceLineColor=QColor(Qt::yellow);
//	PieceLineColor.setAlpha(PieceColorAlpha);
//	Pnt.setPen(QPen(PieceLineColor));

	for(int i=0;i<Count;i++){
		//NULLチェック
		if(pPieceInfoDataList[i].PieceCoordinates==NULL){
			continue;
		}
		//個片ごとに色分けする
///		PieceColor.setRgb(ColorClip(PieceColorRed,dPieceColor,i),ColorClip(PieceColorGreen,dPieceColor,i),ColorClip(PieceColorBlue,dPieceColor,i),PieceColorAlpha);
///		Pnt.setPen(QPen(PieceColor));
		switch(AreaNameList->indexOf(pPieceInfoDataList[i].GetPieceName())){
			case 1:
			case 7:
			case 13:
				Pnt.setPen(QPen(QColor(Qt::blue)));
				break;
			case 2:
			case 8:
			case 14:
				Pnt.setPen(QPen(QColor(Qt::cyan)));
				break;
			case 3:
			case 9:
			case 15:
				Pnt.setPen(QPen(QColor(Qt::magenta)));
				break;
			case 4:
			case 10:
			case 16:
				Pnt.setPen(QPen(QColor(Qt::yellow)));
				break;
			case 5:
			case 11:
			case 17:
				Pnt.setPen(QPen(QColor(Qt::gray)));
				break;
			case 6:
			case 12:
			case 18:
				Pnt.setPen(QPen(Qt::white));
				break;
			default:
				Pnt.setPen(QPen(QColor(Qt::black)));
		}
		switch(pPieceInfoDataList[i].GetPieceShape()){
			case 'R':
				int gX1,gY1;
//				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[0].X,pPieceInfoDataList[i].PieceCoordinates[0].Y,gX1,gY1);
				gX1=pPieceInfoDataList[i].PieceCoordinates[0].X;
				gY1=pPieceInfoDataList[i].PieceCoordinates[0].Y;
				int gX2,gY2;
//				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[1].X,pPieceInfoDataList[i].PieceCoordinates[1].Y,gX2,gY2);
				gX2=pPieceInfoDataList[i].PieceCoordinates[1].X;
				gY2=pPieceInfoDataList[i].PieceCoordinates[1].Y;
				int OffsetX1,OffsetY1;
//				GetUniverseToCanvas(ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetX,ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetY,OffsetX1,OffsetY1);
				OffsetX1=MImage->ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetX<<MImage->ImgRate;
				OffsetY1=MImage->ImageList[pPieceInfoDataList[i].GetFirstPiecePage()]->OffsetY<<MImage->ImgRate;
				int OffsetX2,OffsetY2;
				int LastPiecePage;
				if((LastPiecePage=pPieceInfoDataList[i].GetLastPiecePage())>=0){
//					GetUniverseToCanvas(ImageList[LastPiecePage]->OffsetX,ImageList[LastPiecePage]->OffsetY,OffsetX2,OffsetY2);
					OffsetX2=MImage->ImageList[LastPiecePage]->OffsetX<<MImage->ImgRate;
					OffsetY2=MImage->ImageList[LastPiecePage]->OffsetY<<MImage->ImgRate;
				}
				Pnt.drawRect(GetMovx()+gX1+OffsetX1,GetMovy()+gY1+OffsetY1,gX2+OffsetX2-gX1-OffsetX1,gY2+OffsetY2-gY1-OffsetY1);
//				Pnt.drawText(movx+gX1+OffsetX1,movy+gY1+OffsetY1,gX2+OffsetX2-gX1-OffsetX1,gY2+OffsetY2-gY1-OffsetY1,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
			case 'E':
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[0].X,pPieceInfoDataList[i].PieceCoordinates[0].Y,gX1,gY1);
				GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[1].X,pPieceInfoDataList[i].PieceCoordinates[1].Y,gX2,gY2);
				Pnt.drawEllipse	(gX1,gY1,gX2-gX1,gY2-gY1);
//				Pnt.drawText	(gX1,gY1,gX2-gX1,gY2-gY1,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
			case 'P':
				QPolygon polygon;
				for(int Cnt=0;Cnt<pPieceInfoDataList[i].DataCount;Cnt++){
					int gX,gY;
					GetUniverseToCanvas(pPieceInfoDataList[i].PieceCoordinates[Cnt].X,pPieceInfoDataList[i].PieceCoordinates[Cnt].Y,gX,gY);
					polygon << QPoint(gX,gY);
				}
				Pnt.drawConvexPolygon(polygon);
				int MinX=0,MinY=0,MaxX=0,MaxY=0;
				for(int Cnt=0;Cnt<pPieceInfoDataList[i].DataCount;Cnt++){
					int X,Y;
					if(MinX>(X=polygon.point(Cnt).x()))
						MinX=X;
					else if(MaxX<X)
						MaxX=X;
					if(MinY>(Y=polygon.point(Cnt).y()))
						MinY=Y;
					else if(MaxY<Y)
						MaxY=Y;
				}
//				Pnt.drawText(MinX,MinY,MaxX-MinX,MaxY-MinY,Qt::AlignCenter,pPieceInfoDataList[i].GetPieceName());
				break;
		}
//		Pnt.setBrush(QColor(0,0,0,0));
	}
}

void NGImagePiece::SetNGBrightness(int Brightness[])
{
	if(Image==NULL || wImage==NULL)
		return;
	int MaxLinesInImage		=wImage->height();
	int DotPerLineInImage	=wImage->width();
	for(int Y=0;Y<MaxLinesInImage;Y++){
		QRgb *pYLine	=(QRgb *)Image	->scanLine(Y);
		QRgb *pYLineOrg	=(QRgb *)wImage	->scanLine(Y);
		for(int X=0;X<DotPerLineInImage;X++,pYLineOrg++){
			*pYLine++=qRgb(Brightness[qRed(*pYLineOrg)],Brightness[qGreen(*pYLineOrg)],Brightness[qBlue(*pYLineOrg)]);
		}
	}
}

//********************************************
//　カメラ画像格納クラス
//********************************************
//CameraImage::CameraImage(QWidget *parent) : ImageBase(this)
CameraImage::CameraImage(int W,int H) : ImageBase(this)
{
	SetMode(mtFrameDraw::fdNone);
	Wid=W;
	Hei=H;
	AspectER=0;
	AspectRatio=(double)W/H;
	Image=NULL;
	ZoomRate=3.5;
}

CameraImage::~CameraImage()
{
}

void CameraImage::DrawPaint(QPainter &Pnt)
{
	int X,Y;
	double wAspectER;
	if(AspectRatio<((double)width()/height())){
		wAspectER=(double)width()/Wid;
		X=0;
		Y=-(Hei*wAspectER-height())/2;
	}
	else{
		wAspectER=(double)height()/Hei;
		X=-(Wid*wAspectER-width())/2;
		Y=0;
	}
	if(AspectER!=wAspectER){
		AspectER=wAspectER;
		matrix.reset();
		matrix.scale(AspectER,AspectER);
	}
	Pnt.drawImage(X,Y,Image->transformed(matrix));
}

void CameraImage::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	int dx=x-(width()>>1);
	int dy=y-(height()>>1);

	double wAspectER;
	if(AspectRatio<((double)width()/height()))
		wAspectER=(double)width()/Wid;
	else
		wAspectER=(double)height()/Hei;
	if(AspectER!=wAspectER)
		AspectER=wAspectER;

	emit SignalOnMoveXY((dx/AspectER)/(Wid>>1),(dy/AspectER)/(Hei>>1));
}

//********************************************
//　カメラスナップ画像格納クラス
//********************************************
CameraSnapImage::CameraSnapImage(int ANum) : ImageBase(this)
{
	Image		=NULL;
	AlignmentNum=ANum;
///	First		=true;
	Finish		=false;

	connect(this,SIGNAL(SignalDrawEnd()),this,SLOT(SlotDrawEnd()));
}

CameraSnapImage::~CameraSnapImage()
{
	if(Image!=NULL){
		delete Image;
	}
}

void CameraSnapImage::DrawPaint(QPainter &Pnt)
{
	Pnt.drawImage(0,0,*Image);
	if(Finish){
		Pnt.setBrush(QColor(255,0,0,127));
		Pnt.drawRect(X1,Y1,X2-X1,Y2-Y1);
	}
}
/*
void CameraSnapImage::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	if(Finish)
		return;

	if(First){
		X1=x;
		Y1=y;
		First=false;
	}
	else{
		X2=x;
		Y2=y;
	}
}
*/
void CameraSnapImage::mtMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	if(Finish){
		Finish	=false;
		emit SignalOnCalc(false);
	}
/*
	if(Finish){
		First	=false;
		Finish	=false;
		emit SignalOnCalc(false);
	}
	else
		First	=true;
*/
}
/*
void CameraSnapImage::DrawEnd()
{
	//選択された部分を赤く網掛け表示する
	if(X1>X2){
		int wX=X2;
		X2=X1;
		X1=wX;
	}
	if(Y1>Y2){
		int wY=Y2;
		Y2=Y1;
		Y1=wY;
	}

	//重心の計算
	CalcGravity();
	emit SignalOnCalc(true);

	Finish=true;
}
*/
void CameraSnapImage::SetArea(int W,int H)
{
	Wid=W;
	Hei=H;
	AspectER=0;
	AspectRatio=(double)W/H;
}

void CameraSnapImage::SlotDrawEnd()
{
	//選択された部分を赤く網掛け表示する
	//ux=gx/ZoomRate-movx;
	X1=(SData.UData.RectangleData.x1+movx)*ZoomRate;
	Y1=(SData.UData.RectangleData.y1+movy)*ZoomRate;
	X2=(SData.UData.RectangleData.x2+movx)*ZoomRate;
	Y2=(SData.UData.RectangleData.y2+movy)*ZoomRate;
/*
	X1	=SData.UData.RectangleData.x1;
	Y1	=SData.UData.RectangleData.y1;
	X2	=SData.UData.RectangleData.x2;
	Y2	=SData.UData.RectangleData.y2;
*/
	//重心の計算
	CalcGravity();
	emit SignalOnCalc(true);

	Finish=true;
}

void CameraSnapImage::CalcGravity()
{
	GX=(X1+X2)>>1;
	GY=(Y1+Y2)>>1;

	int dx=GX-(width()>>1);
	int dy=GY-(height()>>1);

	double wAspectER;
	if(AspectRatio<((double)width()/height()))
		wAspectER=(double)width()/Wid;
	else
		wAspectER=(double)height()/Hei;
	if(AspectER!=wAspectER)
		AspectER=wAspectER;

	emit SignalOnMoveXY((dx/AspectER)/(Wid>>1),(dy/AspectER)/(Hei>>1));
}

//********************************************
//　マスタースナップ画像格納クラス
//********************************************
MasterSnapImage::MasterSnapImage(int ANum,int T) : ImageBase(this)
{
	Image			=NULL;
	AlignmentNum	=ANum;
///	First			=true;
	Finish			=false;
	Type			=T;

	connect(this,SIGNAL(SignalDrawEnd()),this,SLOT(SlotDrawEnd()));
}

MasterSnapImage::~MasterSnapImage()
{
	if(Image!=NULL){
		delete Image;
	}
}

void MasterSnapImage::DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase)
{
	//画像の回転角度による描画空間変換
	if(ImageRotation==90)
		Pnt.translate(width(),0);
	else if(ImageRotation==-90)
		Pnt.translate(0,height());
	else if(ImageRotation==180)
		Pnt.translate(width(),height());
	Pnt.rotate(ImageRotation);

	//画像の描画
	QMatrix matrix;
	matrix.scale(ZoomRate,ZoomRate);
//	matrix.rotate(ImageRotation);
	int uW=Wid;
	int uH=Hei;
	for(int Cnt=0;Cnt<IDBase->MImageClassList[Type]->ImageList.count();Cnt++){
		int uOffsetX=IDBase->MImageClassList[Type]->ImageList[Cnt]->OffsetX;
		int uOffsetY=IDBase->MImageClassList[Type]->ImageList[Cnt]->OffsetY;
		int ImageW=IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->width();
		int ImageH=IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->height();
		//選択矩形が画像中に収まる場合
		if(-movx>=uOffsetX && (-movx+uW)<=(uOffsetX+ImageW) && -movy>=uOffsetY && (-movy+uH)<=(uOffsetY+ImageH))
			Pnt.drawImage(0,0,IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY,uW,uH).transformed(matrix));
		else{
			int X,Y,W,H;
			//選択矩形が画像の右端をまたぐ場合
			if(-movx<(uOffsetX+ImageW) && (-movx+uW)>(uOffsetX+ImageW) && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
				Pnt.drawImage(0,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY+Y,uOffsetX+ImageW+movx,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
			//選択矩形が画像の左端をまたぐ場合
			else if(-movx<uOffsetX && (-movx+uW)>uOffsetX && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
				Pnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
			//選択矩形が画像の下端をまたぐ場合
			else if(-movy<(uOffsetY+ImageH) && (-movy+uH)>(uOffsetY+ImageH) && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
				Pnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
			//選択矩形が画像の上端をまたぐ場合
			else if(-movy<uOffsetY && (-movy+uH)>uOffsetY && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
				Pnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,IDBase->MImageClassList[Type]->ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
		}
	}
	Pnt.resetMatrix();
	if(Finish){
		Pnt.setBrush(QColor(255,0,0,127));
		Pnt.drawRect(X1-1,Y1-1,X2-X1,Y2-Y1);
	}
}
/*
void MasterSnapImage::mtMouseLDown(QMouseEvent *Ev ,int x ,int y)
{
	if(Finish)
		return;

	if(First){
		X1=x;
		Y1=y;
		First=false;
	}
	else{
		X2=x;
		Y2=y;
	}
}
*/
void MasterSnapImage::mtMouseRDown(QMouseEvent *Ev ,int x ,int y)
{
	if(Finish){
		Finish	=false;
		emit SignalOnCalc(false);
	}
/*
	if(Finish){
		First	=false;
		Finish	=false;
		emit SignalOnCalc(false);
	}
	else
		First	=true;
*/
}
/*
void MasterSnapImage::DrawEnd()
{
	//選択された部分を赤く網掛け表示する
	if(X1>X2){
		int wX=X2;
		X2=X1;
		X1=wX;
	}
	if(Y1>Y2){
		int wY=Y2;
		Y2=Y1;
		Y1=wY;
	}

	//重心の計算
	CalcGravity();
	emit SignalOnCalc(true);

	Finish=true;
}
*/
void MasterSnapImage::SlotDrawEnd()
{
	//選択された部分を赤く網掛け表示する
	//ux=gx/ZoomRate-movx;
	X1=(SData.UData.RectangleData.x1+movx)*ZoomRate;
	Y1=(SData.UData.RectangleData.y1+movy)*ZoomRate;
	X2=(SData.UData.RectangleData.x2+movx)*ZoomRate;
	Y2=(SData.UData.RectangleData.y2+movy)*ZoomRate;
/*
	X1	=SData.UData.RectangleData.x1;
	Y1	=SData.UData.RectangleData.y1;
	X2	=SData.UData.RectangleData.x2;
	Y2	=SData.UData.RectangleData.y2;
*/
	//重心の計算
	CalcGravity();
	emit SignalOnCalc(true);

	Finish=true;
}

void MasterSnapImage::CalcGravity()
{
	//重心の計算
/*	//マスタースナップ画像の左上座標が(-movx,-movy)で拡大率がZoomRateなので
	GX=(int)((-movx+X1/ZoomRate)+(-movx+X2/ZoomRate))>>1;
	GY=(int)((-movy+Y1/ZoomRate)+(-movy+Y2/ZoomRate))>>1;
*/
	//画像の回転角度による描画空間変換
	if(ImageRotation==0){
		GX=(int)((-movx+X1/ZoomRate)+(-movx+X2/ZoomRate))>>1;
		GY=(int)((-movy+Y1/ZoomRate)+(-movy+Y2/ZoomRate))>>1;
	}
	else if(ImageRotation==90){
		GX=(int)((-movx+Y1/ZoomRate)+(-movx+Y2/ZoomRate))>>1;
		GY=(int)((-movy+(width()-X1)/ZoomRate)+(-movy+(width()-X2)/ZoomRate))>>1;
	}
	else if(ImageRotation==-90){
		GX=(int)((-movx+(height()-Y1)/ZoomRate)+(-movx+(height()-Y2)/ZoomRate))>>1;
		GY=(int)((-movy+X1/ZoomRate)+(-movy+X2/ZoomRate))>>1;
	}
	else if(ImageRotation==180){
//		GX=(int)((-movx+(height()-Y1)/ZoomRate)+(-movx+(height()-Y2)/ZoomRate))>>1;
//		GY=(int)((-movy+(width()-X1)/ZoomRate)+(-movy+(width()-X2)/ZoomRate))>>1;
		GX=(int)((-movx+(width()-X1)/ZoomRate)+(-movx+(width()-X2)/ZoomRate))>>1;
		GY=(int)((-movy+(height()-Y1)/ZoomRate)+(-movy+(height()-Y2)/ZoomRate))>>1;
	}
}

//********************************************
//　カメラ毎クラス
//********************************************
ImageInPage::ImageInPage(int X,int Y)
{
	Image=wImage=NULL;
	OffsetX=X;
	OffsetY=Y;
}

ImageInPage::~ImageInPage()
{
	if(Image!=NULL){
		delete Image;
		Image=NULL;
	}
	if(wImage!=NULL){
		delete wImage;
		wImage=NULL;
	}
}

//画像の輝度補正
void ImageInPage::SetMasterBrightness(int Brightness[])
{
	int MaxLinesInImage		=Image->height();
	int DotPerLineInImage	=Image->width();
	for(int Y=0;Y<MaxLinesInImage;Y++){
		QRgb *pYLine	=(QRgb *)Image	->scanLine(Y);
		QRgb *pYLineOrg	=(QRgb *)wImage	->scanLine(Y);
		for(int X=0;X<DotPerLineInImage;X++,pYLineOrg++){
			*pYLine++=qRgb(Brightness[qRed(*pYLineOrg)],Brightness[qGreen(*pYLineOrg)],Brightness[qBlue(*pYLineOrg)]);
		}
	}
}

void NGImagePiece::SetNGList(NPListPack<NGPointList> &nglist)
{
	NGList.RemoveAll();
	for(NGPointList *s=nglist.GetFirst();s!=NULL;s=s->GetNext()){
		NGPointList *d=new NGPointList(s->x,s->y,s->colorAlg);
		NGList.AppendList(d);
	}
}
