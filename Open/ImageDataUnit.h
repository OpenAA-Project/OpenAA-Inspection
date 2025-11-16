/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\ImageDataUnit.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef IMAGEDATAUNIT_H
#define IMAGEDATAUNIT_H

#include <QWidget>
#include <QTableWidget>
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

//********************************************
//　画像データ格納クラスユニット
//********************************************
class ImageDataUnit
{
//	Q_OBJECT

public:
	ImageDataUnit();
	~ImageDataUnit();

	//同一画像クラスが複数の場合の表示整列
	enum	AlignmentType{
				 mtHorizon		//横に並べる
				,mtVertical		//縦に並べる
	};
	AlignmentType	AType;

	QList<MasterImage *>		MImageClassList;
	QList<MasterImagePiece *>	MImagePieceList;
	QList<NGImagePiece *>		NGImagePieceList;
	QList<CameraImage *>		CImageList;
	QList<CameraSnapImage *>	CSnapImageList;
	QList<MasterSnapImage *>	MSnapImageList;

	//画像データクラスをリストに格納
//	void	AddImage	(ImageBase			*ImageClass);
	void	AddImage	(MasterImage		*ImageClass);
	void	ReplaceImage(int Index,MasterImage *ImageClass);
	void	AddImage	(MasterImagePiece	*ImageClass);
	void	AddImage	(NGImagePiece		*ImageClass);
	void	AddImage	(CameraImage		*ImageClass);
	void	AddImage	(CameraSnapImage	*ImageClass);
	void	AddImage	(MasterSnapImage	*ImageClass);

	//画像の並べ方の設定
	void	SetAlignment(MasterImage		*ImageClass, AlignmentType type);
	void	SetAlignment(MasterImagePiece	*ImageClass, AlignmentType type);
	void	SetAlignment(NGImagePiece		*ImageClass, AlignmentType type);
	void	SetAlignment(CameraImage		*ImageClass, AlignmentType type);

protected:

private slots:

private:
};

//********************************************
//　画像クラスベース
//********************************************
class ImageBase
{
//	Q_OBJECT

public:
	ImageBase(QWidget *parent);
//	ImageBase(mtFrameDraw *parent=0);
	~ImageBase();

	int		CameraNumb;		//カメラ台数
	double	MScaled;		//拡大率
	double	wMScaled,MScaledX,MScaledY;
	QMatrix	Matrix;
	int		UniverseX,UniverseY;
	double	Scaled;

	int		ImageRotation;	//画像の回転角度

	//アルゴリズムを探して色の設定をする
	void         AlgColorGet(QString Str, QList<QPair<QString, QString> > citemList, QColor &color);

	//画像の画面への表示設定（縦横比）
//	void	SetScaled(Qt::AspectRatioMode RMode)	{	RatioMode=RMode;	}
//	Qt::AspectRatioMode GetScaled()					{	return RatioMode;	}
	void	SetMAreaSize(int xlen,int ylen);
	virtual void	SetWholeImage(int CanvasWidth,int CanvasHeight);
	void	SetMScaledX(double X);
	void	SetMScaledY(double Y);
//	QMatrix	GetMScaled()							{	return Matrix;		}

	//画像描画関数
	virtual void DrawPaint(QPainter &Pnt)			{};

	//画像を任意の角度に回転（0,90,-90,180）
	void	SetRotate(int Rotate)					{	ImageRotation=Rotate;	}
//	QMatrix	GetRotate()								{	return Matrix;		}

	//データ座標(ux,uy)を画面座標(gx,gy)に変換する
	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);

	//色範囲を0-255でループするように設定
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

//********************************************
//　マスター画像格納クラス
//********************************************
//class MasterImage : public ImageDataFD
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
	int SType;	//表か裏か

/********** ↓MasterImgクラス（子クラス）で使用するもの **********/
	int		IX,IY,IW,IH;	//マスター画像上で矩形選択した座標
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
/********** ↑MasterImgクラス（子クラス）で使用するもの **********/

	//画像描画関数
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

	//確認している箇所を四角く枠で囲んで表示する(マウスクリックイベント)
	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);
	virtual	void MMouseLDown(int x,int y,int w,int h,bool FlagTrans);
//	void SetRectArea(int W,int H,double Expand);

	//確認している箇所を四角く枠で囲んで表示する(マウスクリックイベント)
//	virtual	void mtMouseRDown(QMouseEvent *Ev ,int x ,int y);

	//データ座標(ux,uy)を画面座標(gx,gy)に変換する
	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);

	void	SetExpand();

	//画像の輝度補正
	void	SetMasterBrightness(int Brightness[]);

	//保持座標のクリア
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

//********************************************
//　個片マスター画像格納クラス
//********************************************
//class MasterImagePiece : public ImageDataGU
class MasterImagePiece : public mtGraphicUnit, public ImageBase
{
	Q_OBJECT

public:
	MasterImagePiece(QWidget *parent = 0);
	~MasterImagePiece();

	//画像
	QImage Image;

	//画像表示の拡大率の設定
	void SetZoomRate(double Exp);
	double GetZoomRate()			{	return ExpRate;	}

	//画像描画関数
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

//********************************************
//　個片ＮＧ画像格納クラス
//********************************************
//class NGImagePiece : public ImageDataGU
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

	//画像表示の拡大率の設定Matrix
	QMatrix matrix;

	//画像描画関数
//	virtual void DrawPaint		(QPainter &Pnt);
	void DrawPaint		(QPainter &Pnt,ImageDataUnit *IDBase,int Side);
	virtual void DrawNoPaint	(QPainter &Pnt);
	virtual void DrawNGPoint	(QPainter &Pnt,int &MaxPointX,int &MinPointX,int &MaxPointY,int &MinPointY, QList<QPair<QString, QString> > citemList);
	virtual void DrawMPaint		(QPainter &Pnt,ImageDataUnit *IDBase);
	virtual void DrawPieceLine	(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QStringList *AreaNameList,MasterImage *MImage);

	//補正値
	void SetCorrectionX		(int x)	{	Dx=x;	}
	void SetCorrectionY		(int y)	{	Dy=y;	}

	//画像の退避
	void SetNGImage			()		{	if(wImage!=NULL)*wImage=*Image;	}
	void SetNGList(NPListPack<NGPointList> &nglist);
	
	//画像の輝度補正
	void SetNGBrightness(int Brightness[]);

	//画像表示の拡大率の設定
	virtual void SetZoomRate(double Exp);

	NGPointBaseList			*GetNGPBaseList()		{	return NGPBaseList;		}
	void SetNGPBaseList(NGPointBaseList *NGPBList)	{	NGPBaseList=NGPBList;	}

	//NG画像が有るか無いかの設定
	void SetNGImageExist(bool Exist)	{	NGImageExist=Exist;	}

	//NG画像が無い場合の丸色のセット
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
	QColor NoNGColor;	//NG画像が無い場合の丸色
};

//********************************************
//　カメラ画像格納クラス
//********************************************
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

	//画像描画関数
	virtual void DrawPaint(QPainter &Pnt);

	//左クリックでX-Y微動
	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);

protected:

signals:
	void SignalOnMoveXY(double x,double y);

private slots:

private:
	QMatrix	matrix;
	int		Wid,Hei;
	double	AspectER;
};

//********************************************
//　カメラスナップ画像格納クラス
//********************************************
//class CameraImage : public ImageDataFD
class CameraSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	CameraSnapImage(int ANum);
	~CameraSnapImage();
	QImage *Image;			//カメラスナップ画像
	int		AlignmentNum;	//アライメント番号（０～２）
	int		GX,GY;			//重心の座標
	double	AspectRatio;

	//画像描画関数
	virtual void DrawPaint(QPainter &Pnt);

	//四角く枠で囲む
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

//********************************************
//　マスタースナップ画像格納クラス
//********************************************
class MasterSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	MasterSnapImage(int ANum=0,int T=0);
	~MasterSnapImage();
	QImage *Image;			//マスタースナップ画像
	int		AlignmentNum;	//アライメント番号（０～２）
	int		GX,GY;			//重心の座標
	int		Wid,Hei;		//矩形領域の幅と高さ
	int		Type;			//表か裏か（０,１）

	//画像描画関数
//	virtual void DrawPaint(QPainter &Pnt);
	virtual void DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase);

	//四角く枠で囲む
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

//********************************************
//　カメラ毎クラス
//********************************************
class ImageInPage
{
//	Q_OBJECT

public:
	ImageInPage(int X=0,int Y=0);
	~ImageInPage();

	QImage *Image;		//画像
	QImage *wImage;		//オリジナルの退避
	int OrgOffsetX,OrgOffsetY;		//X-Yオフセット
	int OffsetX,OffsetY;

	//画像の退避
	void	SetMasterImage()	{	*wImage=*Image;	}

	//画像の輝度補正
	void	SetMasterBrightness(int Brightness[]);

protected:

private slots:

private:
};

#endif // IMAGEDATAUNIT_H
