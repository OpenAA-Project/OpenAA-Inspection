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
//�@�摜�f�[�^�i�[�N���X���j�b�g
//********************************************
class ImageDataUnit
{
//	Q_OBJECT

public:
	ImageDataUnit();
	~ImageDataUnit();

	//�����摜�N���X�������̏ꍇ�̕\������
	enum	AlignmentType{
				 mtHorizon		//���ɕ��ׂ�
				,mtVertical		//�c�ɕ��ׂ�
	};
	AlignmentType	AType;

	QList<MasterImage *>		MImageClassList;
	QList<MasterImagePiece *>	MImagePieceList;
	QList<NGImagePiece *>		NGImagePieceList;
	QList<CameraImage *>		CImageList;
	QList<CameraSnapImage *>	CSnapImageList;
	QList<MasterSnapImage *>	MSnapImageList;

	//�摜�f�[�^�N���X�����X�g�Ɋi�[
//	void	AddImage	(ImageBase			*ImageClass);
	void	AddImage	(MasterImage		*ImageClass);
	void	ReplaceImage(int Index,MasterImage *ImageClass);
	void	AddImage	(MasterImagePiece	*ImageClass);
	void	AddImage	(NGImagePiece		*ImageClass);
	void	AddImage	(CameraImage		*ImageClass);
	void	AddImage	(CameraSnapImage	*ImageClass);
	void	AddImage	(MasterSnapImage	*ImageClass);

	//�摜�̕��ו��̐ݒ�
	void	SetAlignment(MasterImage		*ImageClass, AlignmentType type);
	void	SetAlignment(MasterImagePiece	*ImageClass, AlignmentType type);
	void	SetAlignment(NGImagePiece		*ImageClass, AlignmentType type);
	void	SetAlignment(CameraImage		*ImageClass, AlignmentType type);

protected:

private slots:

private:
};

//********************************************
//�@�摜�N���X�x�[�X
//********************************************
class ImageBase
{
//	Q_OBJECT

public:
	ImageBase(QWidget *parent);
//	ImageBase(mtFrameDraw *parent=0);
	~ImageBase();

	int		CameraNumb;		//�J�����䐔
	double	MScaled;		//�g�嗦
	double	wMScaled,MScaledX,MScaledY;
	QMatrix	Matrix;
	int		UniverseX,UniverseY;
	double	Scaled;

	int		ImageRotation;	//�摜�̉��]�p�x

	//�A���S���Y�����T���ĐF�̐ݒ�������
	void         AlgColorGet(QString Str, QList<QPair<QString, QString> > citemList, QColor &color);

	//�摜�̉��ʂւ̕\���ݒ��i�c�����j
//	void	SetScaled(Qt::AspectRatioMode RMode)	{	RatioMode=RMode;	}
//	Qt::AspectRatioMode GetScaled()					{	return RatioMode;	}
	void	SetMAreaSize(int xlen,int ylen);
	virtual void	SetWholeImage(int CanvasWidth,int CanvasHeight);
	void	SetMScaledX(double X);
	void	SetMScaledY(double Y);
//	QMatrix	GetMScaled()							{	return Matrix;		}

	//�摜�`���֐�
	virtual void DrawPaint(QPainter &Pnt)			{};

	//�摜���C�ӂ̊p�x�ɉ��]�i0,90,-90,180�j
	void	SetRotate(int Rotate)					{	ImageRotation=Rotate;	}
//	QMatrix	GetRotate()								{	return Matrix;		}

	//�f�[�^���W(ux,uy)�����ʍ��W(gx,gy)�ɕϊ�����
	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);

	//�F�͈͂�0-255�Ń��[�v�����悤�ɐݒ�
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
//�@�}�X�^�[�摜�i�[�N���X
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
	int SType;	//�\������

/********** ��MasterImg�N���X�i�q�N���X�j�Ŏg�p�������� **********/
	int		IX,IY,IW,IH;	//�}�X�^�[�摜���ŋ��`�I���������W
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
/********** ��MasterImg�N���X�i�q�N���X�j�Ŏg�p�������� **********/

	//�摜�`���֐�
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

	//�m�F���Ă����ӏ����l�p���g�ň͂��ŕ\������(�}�E�X�N���b�N�C�x���g)
	virtual	void mtMouseLDown(QMouseEvent *Ev ,int x ,int y);
	virtual	void MMouseLDown(int x,int y,int w,int h,bool FlagTrans);
//	void SetRectArea(int W,int H,double Expand);

	//�m�F���Ă����ӏ����l�p���g�ň͂��ŕ\������(�}�E�X�N���b�N�C�x���g)
//	virtual	void mtMouseRDown(QMouseEvent *Ev ,int x ,int y);

	//�f�[�^���W(ux,uy)�����ʍ��W(gx,gy)�ɕϊ�����
	void	GetUniverseToCanvas(double ux,double uy,int &gx,int &gy);

	void	SetExpand();

	//�摜�̋P�x�␳
	void	SetMasterBrightness(int Brightness[]);

	//�ێ����W�̃N���A
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
//�@�Ѓ}�X�^�[�摜�i�[�N���X
//********************************************
//class MasterImagePiece : public ImageDataGU
class MasterImagePiece : public mtGraphicUnit, public ImageBase
{
	Q_OBJECT

public:
	MasterImagePiece(QWidget *parent = 0);
	~MasterImagePiece();

	//�摜
	QImage Image;

	//�摜�\���̊g�嗦�̐ݒ�
	void SetZoomRate(double Exp);
	double GetZoomRate()			{	return ExpRate;	}

	//�摜�`���֐�
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
//�@�Ђm�f�摜�i�[�N���X
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

	//�摜�\���̊g�嗦�̐ݒ�Matrix
	QMatrix matrix;

	//�摜�`���֐�
//	virtual void DrawPaint		(QPainter &Pnt);
	void DrawPaint		(QPainter &Pnt,ImageDataUnit *IDBase,int Side);
	virtual void DrawNoPaint	(QPainter &Pnt);
	virtual void DrawNGPoint	(QPainter &Pnt,int &MaxPointX,int &MinPointX,int &MaxPointY,int &MinPointY, QList<QPair<QString, QString> > citemList);
	virtual void DrawMPaint		(QPainter &Pnt,ImageDataUnit *IDBase);
	virtual void DrawPieceLine	(QPainter &Pnt,int Count,PieceInfoData *pPieceInfoDataList,QStringList *AreaNameList,MasterImage *MImage);

	//�␳�l
	void SetCorrectionX		(int x)	{	Dx=x;	}
	void SetCorrectionY		(int y)	{	Dy=y;	}

	//�摜�̑ޔ�
	void SetNGImage			()		{	if(wImage!=NULL)*wImage=*Image;	}
	void SetNGList(NPListPack<NGPointList> &nglist);
	
	//�摜�̋P�x�␳
	void SetNGBrightness(int Brightness[]);

	//�摜�\���̊g�嗦�̐ݒ�
	virtual void SetZoomRate(double Exp);

	NGPointBaseList			*GetNGPBaseList()		{	return NGPBaseList;		}
	void SetNGPBaseList(NGPointBaseList *NGPBList)	{	NGPBaseList=NGPBList;	}

	//NG�摜���L�邩�������̐ݒ�
	void SetNGImageExist(bool Exist)	{	NGImageExist=Exist;	}

	//NG�摜�������ꍇ�̊ېF�̃Z�b�g
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
	QColor NoNGColor;	//NG�摜�������ꍇ�̊ېF
};

//********************************************
//�@�J�����摜�i�[�N���X
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

	//�摜�`���֐�
	virtual void DrawPaint(QPainter &Pnt);

	//���N���b�N��X-Y����
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
//�@�J�����X�i�b�v�摜�i�[�N���X
//********************************************
//class CameraImage : public ImageDataFD
class CameraSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	CameraSnapImage(int ANum);
	~CameraSnapImage();
	QImage *Image;			//�J�����X�i�b�v�摜
	int		AlignmentNum;	//�A���C�����g�ԍ��i�O�`�Q�j
	int		GX,GY;			//�d�S�̍��W
	double	AspectRatio;

	//�摜�`���֐�
	virtual void DrawPaint(QPainter &Pnt);

	//�l�p���g�ň͂�
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
//�@�}�X�^�[�X�i�b�v�摜�i�[�N���X
//********************************************
class MasterSnapImage : public mtFrameDraw, public ImageBase
{
	Q_OBJECT

public:
	MasterSnapImage(int ANum=0,int T=0);
	~MasterSnapImage();
	QImage *Image;			//�}�X�^�[�X�i�b�v�摜
	int		AlignmentNum;	//�A���C�����g�ԍ��i�O�`�Q�j
	int		GX,GY;			//�d�S�̍��W
	int		Wid,Hei;		//���`�̈��̕��ƍ���
	int		Type;			//�\�������i�O,�P�j

	//�摜�`���֐�
//	virtual void DrawPaint(QPainter &Pnt);
	virtual void DrawPaint(QPainter &Pnt,ImageDataUnit *IDBase);

	//�l�p���g�ň͂�
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
//�@�J�������N���X
//********************************************
class ImageInPage
{
//	Q_OBJECT

public:
	ImageInPage(int X=0,int Y=0);
	~ImageInPage();

	QImage *Image;		//�摜
	QImage *wImage;		//�I���W�i���̑ޔ�
	int OrgOffsetX,OrgOffsetY;		//X-Y�I�t�Z�b�g
	int OffsetX,OffsetY;

	//�摜�̑ޔ�
	void	SetMasterImage()	{	*wImage=*Image;	}

	//�摜�̋P�x�␳
	void	SetMasterBrightness(int Brightness[]);

protected:

private slots:

private:
};

#endif // IMAGEDATAUNIT_H