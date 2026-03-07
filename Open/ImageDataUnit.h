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

#ifndef IMAGEDATAUNIT_H
#define IMAGEDATAUNIT_H

#include <QWidget>
#include <QTableWidget>
#include <QTransform>
#include "mtFrameDraw.h"
#include "mtGraphicUnit.h"

//class ImageDataBase;
class MasterImage;
class MasterImagePiece;
class NGImagePiece;
class CameraImage;
class CameraSnapImage;
class MasterSnapImage;
class ImageInPage;
class NGPointList;
class NGPointBaseList;
class PieceInfoData;


class ImageDataUnit
{
public:
	ImageDataUnit();
	~ImageDataUnit();

	enum	AlignmentType{
				 mtHorizon	
				,mtVertical	
	};
	AlignmentType	AType;

	QList<MasterImage *>		MImageClassList;
	QList<MasterImagePiece *>	MImagePieceList;
	QList<NGImagePiece *>		NGImagePieceList;
	QList<CameraImage *>		CImageList;
	QList<CameraSnapImage *>	CSnapImageList;
	QList<MasterSnapImage *>	MSnapImageList;

	void	AddImage	(MasterImage		*ImageClass);
	void	ReplaceImage(int Index,MasterImage *ImageClass);
	void	AddImage	(MasterImagePiece	*ImageClass);
	void	AddImage	(NGImagePiece		*ImageClass);
	void	AddImage	(CameraImage		*ImageClass);
	void	AddImage	(CameraSnapImage	*ImageClass);
	void	AddImage	(MasterSnapImage	*ImageClass);

	//????????????
	void	SetAlignment(MasterImage		*ImageClass, AlignmentType type);
	void	SetAlignment(MasterImagePiece	*ImageClass, AlignmentType type);
	void	SetAlignment(NGImagePiece		*ImageClass, AlignmentType type);
	void	SetAlignment(CameraImage		*ImageClass, AlignmentType type);

protected:

private slots:

private:
};

class ImageBase
{
//	Q_OBJECT

public:
	ImageBase(QWidget *parent);
//	ImageBase(mtFrameDraw *parent=0);
	~ImageBase();

	int		CameraNumb;	
	double	MScaled;	
	double	wMScaled,MScaledX,MScaledY;
	QTransform	Matrix;
	int		UniverseX,UniverseY;
	double	Scaled;

	int		ImageRotation;

	void         AlgColorGet(QString Str, QList<QPair<QString, QString> > citemList, QColor &color);

//	void	SetScaled(Qt::AspectRatioMode RMode)	{	RatioMode=RMode;	}
//	Qt::AspectRatioMode GetScaled()					{	return RatioMode;	}
	void	SetMAreaSize(int xlen,int ylen);
	virtual void	SetWholeImage(int CanvasWidth,int CanvasHeight);
	void	SetMScaledX(double X);
	void	SetMScaledY(double Y);
//	QMatrix	GetMScaled()							{	return Matrix;		}

	virtual void DrawPaint(QPainter &Pnt)			{};
	void	SetRotate(int Rotate)					{	ImageRotation=Rotate;	}
//	QMatrix	GetRotate()								{	return Matrix;		}

	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);
	int		ColorClip(int ColorInt,double dColor,int i);

protected:
//	int CanvasX,CanvasY;

private slots:

private:
	QWidget *ImgParent;
//	mtFrameDraw *ImgParent;
//	Qt::AspectRatioMode RatioMode;
	double wX,wY;
};


class MasterImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	MasterImage(QWidget *parent = 0);
	~MasterImage();

	QList<ImageInPage *> ImageList;
	int	RectX, RectY, RectWidth, RectHeight;
	int	wRectX,wRectY,wRectWidth,wRectHeight;
	int	gmovx,gmovy;
	int uX,uY,uW,uH;

	int ImgRate,ImgRateCount;
	int SType;	//?\??????

	int		IX,IY,IW,IH;
	QAction	*FirstMacOrgAct;
	QAction	*SecondMacOrgAct;
	QAction	*ThirdMacOrgAct;
	QAction	*FirstImgOrgAct;
	QAction	*SecondImgOrgAct;
	QAction	*ThirdImgOrgAct;
	bool	OrgRegist;
	bool	FirstMacOrg;
	bool	SecondMacOrg;
	bool	ThirdMacOrg;
	bool	FirstImgOrg;
	bool	SecondImgOrg;
	bool	ThirdImgOrg;
	int		MX1,MY1,MX2,MY2,MX3,MY3;
	int		IX1,IY1,IX2,IY2,IX3,IY3;
	double	a,b,c,d,e,f;
	virtual	void AfinConvert(){};

	void DrawRect(QPainter &Pnt, QRect &rect, QPen &pen);
	void DrawRect(QRect &rect, QPen &pen);
	virtual void DrawPaint		(QPainter &Pnt);
//	virtual void SetDraw		(int CanvasWidth,int CanvasHeight,double ExpRate);
	virtual void SetPieceDraw	(int CanvasWidth,int CanvasHeight,double ExpRate);
//	virtual void DrawNGDot		(QPainter &Pnt,QTableWidget *W,int Index,QList<QList<QPoint> > *pNGPointList,int NGCnt);
//	virtual void DrawNGDot		(QPainter &Pnt,QTableWidget *W,int Index,NPListPack<NGPointList> *pNGPointList,int NGCnt, QList<QPair<QString, QString> > citemList);
	virtual void DrawNGDot		(QPainter &Pnt,QTableWidget *W,int Index,NPListPack<NGPointList> *pNGPointList,NPListPack<NGPointBaseList> *pNoImageNGPointList,int NGCnt, QList<QPair<QString, QString> > citemList);
	virtual void DrawNGDot		(QPainter &Pnt,QTableWidget *W,int Index,NPListPack<NGPointBaseList> *pNGPointList,int NGCnt, QList<QPair<QString, QString> > citemList){};
	virtual void DrawPieceRect	(QPainter &Pnt);
	virtual void DrawPieceInfo	(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QColor PieceColor,QStringList *NGAreaNameList,QStringList *AreaNameList);

	void		 SetNGDotColor		(QColor color)		{	NGDotColor=color;		}
	QColor		 GetNGDotColor		()					{	return	NGDotColor;		}
	void		 SetPieceRectColor	(QColor color)		{	PieceRectColor=color;	}
	QColor		 GetPieceRectColor	()					{	return	PieceRectColor;	}
	void		 SetNGDotWidth		(int width)			{	NGDotWidth=width;		}
	int			 GetNGDotWidth		()					{	return	NGDotWidth;		}
	void		 SetPieceRectWidth	(int width)			{	PieceRectWidth=width;	}
	int			 GetPieceRectWidth	()					{	return	PieceRectWidth;	}
	void		 SetPieceRectStyle	(Qt::PenStyle style){	PieceRectStyle=style;	}
	Qt::PenStyle GetPieceRectStyle	()					{	return	PieceRectStyle;	}
	void		 SetPieceName		(QString Name)		{	CurrentPieceName=Name;	}
	QString		 GetPieceName		()					{	return CurrentPieceName;}
//	void		 SetNGAreaNameList	(QStringList *List)	{	NGAreaNameList=*List;	}
//	QStringList	 GetNGAreaNameList	()					{	return NGAreaNameList;	}

	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);
	virtual	void MMouseLDown(int x,int y,int w,int h,bool FlagTrans);

	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);

	void	SetExpand();
	void	SetMasterBrightness(int Brightness[]);
	void	wRectClear();

public slots:
	virtual void SlotMMouseLDown(int x,int y,int w,int h);

protected:
//	void contextMenuEvent(QContextMenuEvent *event);
	void mouseMoveEvent(QMouseEvent *e);

signals:
//	void SignalOnMouseLDown(int x,int y);
	void SignalOnMouseLDown(int x,int y,MasterImage *MImageClass);

private:
	int Wid,Hei;
	double MImagePieceExpand;

	int			 NGDotWidth,PieceRectWidth;
	QColor		 NGDotColor,PieceRectColor;
	Qt::PenStyle PieceRectStyle;
	QString		 CurrentPieceName;
//	QStringList	 NGAreaNameList;
};


class MasterImagePiece : public mtGraphicUnit, public ImageBase
{
	Q_OBJECT

public:
	MasterImagePiece(QWidget *parent = 0);
	~MasterImagePiece();

	QImage Image;

	void SetZoomRate(double Exp);
	double GetZoomRate()			{	return ExpRate;	}

//	virtual void DrawPaint(QPainter &Pnt,QImage *Img,double MasterScaled);
//	virtual void DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase);
	void DrawPaint	(QPainter &Pnt,ImageDataUnit *IDBase,int Side);
	virtual void DrawNoPaint(QPainter &Pnt);

protected:

signals:
	void SignalOnPieceRectChange(int x,int y);

private slots:

private:
	double ExpRate;
};


class NGImagePiece : public mtGraphicUnit, public ImageBase
{
	Q_OBJECT

	NPListPack<NGPointList> NGList;
	NGPointBaseList			*NGPBaseList;
public:
	QImage *Image;
	QImage *wImage;
public:
	NGImagePiece(QWidget *parent = 0);
	~NGImagePiece();
//	QList<QPoint> *NGList;

	bool	NGPointVisible;
	int		NGMarkSize;
	int		Dx,Dy;
	bool	PieceLineVisible;
	int		shiftX,shiftY;

	QTransform matrix;
//	virtual void DrawPaint		(QPainter &Pnt);
	void DrawPaint		(QPainter &Pnt,ImageDataUnit *IDBase,int Side);
	virtual void DrawNoPaint	(QPainter &Pnt);
	virtual void DrawNGPoint	(QPainter &Pnt,int &MaxPointX,int &MinPointX,int &MaxPointY,int &MinPointY, QList<QPair<QString, QString> > citemList);
	virtual void DrawMPaint		(QPainter &Pnt,ImageDataUnit *IDBase);
	virtual void DrawPieceLine	(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QStringList *AreaNameList,MasterImage *MImage);

	void SetCorrectionX		(int x)	{	Dx=x;	}
	void SetCorrectionY		(int y)	{	Dy=y;	}

	void SetNGImage			()		{	if(wImage!=NULL)*wImage=*Image;	}
	void SetNGList(NPListPack<NGPointList> &nglist);

	void SetNGBrightness(int Brightness[]);

	virtual void SetZoomRate(double Exp);

	NGPointBaseList			*GetNGPBaseList()		{	return NGPBaseList;		}
	void SetNGPBaseList(NGPointBaseList *NGPBList)	{	NGPBaseList=NGPBList;	}

	void SetNGImageExist(bool Exist)	{	NGImageExist=Exist;	}

	void SetNoNGColor(QColor color)	{	NoNGColor=color;	}

	void AddImage(QImage *image, int posX=0, int posY=0);
	bool hasImage();
	void delImage();
	void SetImageTopLeftPos(int posX, int posY);
	QImage* GetImage();

protected:

private slots:

private:
	bool NGImageExist;
	QColor NoNGColor;
};

//class CameraImage : public ImageDataFD
class CameraImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	double AspectRatio;

//	CameraImage(QWidget *parent = 0);
	CameraImage(int W,int H);
	~CameraImage();
	QImage *Image;

	virtual void DrawPaint(QPainter &Pnt);
	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);

protected:

signals:
	void SignalOnMoveXY(double x,double y);

private slots:

private:
	QTransform	matrix;
	int		Wid,Hei;
	double	AspectER;
};


class CameraSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	CameraSnapImage(int ANum);
	~CameraSnapImage();
	QImage *Image;		
	int		AlignmentNum;
	int		GX,GY;		
	double	AspectRatio;

	virtual void DrawPaint(QPainter &Pnt);

///	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);
	virtual	void mtMouseRDown(QMouseEvent *Ev ,int x ,int y);
///	virtual	void DrawEnd();

	void	SetArea(int Width,int Height);

signals:
	void	SignalOnCalc(bool Enable);
	void	SignalOnMoveXY(double x,double y);

private slots:
	void	SlotDrawEnd();

private:
///	bool	First,Finish;
	bool	Finish;
	int		X1,Y1,X2,Y2;
	int		Wid,Hei;
	double	AspectER;

	void	CalcGravity();
};

class MasterSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	MasterSnapImage(int ANum=0,int T=0);
	~MasterSnapImage();
	QImage *Image;		
	int		AlignmentNum;
	int		GX,GY;		
	int		Wid,Hei;	
	int		Type;		

//	virtual void DrawPaint(QPainter &Pnt);
	virtual void DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase);

///	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);
	virtual	void mtMouseRDown(QMouseEvent *Ev ,int x ,int y);
///	virtual	void DrawEnd();

signals:
	void	SignalOnCalc(bool Enable);

private slots:
	void	SlotDrawEnd();

private:
///	bool	First,Finish;
	bool	Finish;
	int		X1,Y1,X2,Y2;

	void	CalcGravity	();
};

class ImageInPage
{
//	Q_OBJECT

public:
	ImageInPage(int X=0,int Y=0);
	~ImageInPage();

	QImage *Image;	
	QImage *wImage;	
	int OrgOffsetX,OrgOffsetY;
	int OffsetX,OffsetY;

	void	SetMasterImage()	{	*wImage=*Image;	}
	void	SetMasterBrightness(int Brightness[]);

protected:

private slots:

private:
};

#endif // IMAGEDATAUNIT_H