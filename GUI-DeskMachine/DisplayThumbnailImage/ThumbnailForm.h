/*
 * Copyright (C) 2022
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

#ifndef THUMBNAILFORM_H
#define THUMBNAILFORM_H

#include <QWidget>
#include <QHBoxLayout>
#include "XGUIFormBase.h"
#include "mtFrameDraw.h"
#include "DisplayThumbnailImage.h"
#include "XResult.h"


class mtFrameDrawCustom : public mtFrameDraw
{
public:
	mtFrameDrawCustom(QWidget *parent = 0){}
	~mtFrameDrawCustom(){}

protected:
	void	mousePressEvent	(QMouseEvent *Ev)	{	QWidget::mousePressEvent(Ev);	}
	void	wheelEvent		(QWheelEvent *Ev)	{	QWidget::wheelEvent(Ev);		}
};

class ThumbnailForm : public QFrame
{
	Q_OBJECT

    QHBoxLayout		*horizontalLayout;

public:
	ThumbnailForm(LayersBase *Base,QWidget *parent = 0);
	~ThumbnailForm();

	mtFrameDrawCustom	MasterCanvas;
	mtFrameDrawCustom	TargetCanvas;

	DisplayThumbnailImage	*GetDTImageClass()	{	return DTImageClass;	}

	void	SetCurrentRow(int Row)		{	CurrentRow=Row;			}
	void	SetCenterXY(int X,int Y)	{	CenterX=X;	CenterY=Y;	}
	void	SetZoomRate(double Rate)	{	ZoomRate=Rate;			}
	void	SetFrameColor(bool Enable);

	void	ExecMousePressEvent(GUIFormBase	*DNGListButtonForm=NULL);

protected:
	virtual	void	mousePressEvent(QMouseEvent *event)	override;
	virtual	void	wheelEvent(QWheelEvent *event)		override;
///	virtual	void	keyPressEvent(QKeyEvent *event)		override;

private slots:
	void	SlotOnMasterPaint(QPainter &pnt);
	void	SlotOnTargetPaint(QPainter &pnt);

private:
	LayersBase	*LBase;
	DisplayThumbnailImage	*DTImageClass;
	int		CurrentRow;
	int		CenterX,CenterY;
	double	ZoomRate;
	double	ZoomInRate;

	QString strDefaultBackgroundStyleSheet;	//�\���g�Ή�
	QString strColorBackgroundStyleSheet;	//�\���g�Ή�

	void	ExecuteSlotOnPaint(QPainter &pnt,bool Mastered=true,bool ShowNG=false,bool BlinkNG=false,bool BlinkOn=true);
};

//---------------------------------------------------------
class ThumbnailDialog : public QDialog
{
	Q_OBJECT

    QHBoxLayout		*horizontalLayout;

public:
	ThumbnailDialog(LayersBase *Base,double Rate,QWidget *parent = 0);
	~ThumbnailDialog();

	mtFrameDrawCustom	MasterCanvas;
	mtFrameDrawCustom	TargetCanvas;

	void	SetCenterXY(int X,int Y)	{	CenterX=X;	CenterY=Y;	}
	void	SetZoomRate(double Rate)	{	ZoomRate=Rate;			}

protected:
	virtual	void	mousePressEvent(QMouseEvent *event)	override;
	virtual	void	keyPressEvent(QKeyEvent *event)		override;
	virtual	void	wheelEvent(QWheelEvent *event)		override;

private slots:
	void	SlotOnMasterPaint(QPainter &pnt);
	void	SlotOnTargetPaint(QPainter &pnt);

private:
	LayersBase	*LBase;
	ThumbnailForm	*ThumForm;
	int		CenterX,CenterY;
	double	ZoomRate;

	void	ExecZoomOut();
	void	ExecZoomIn();

	void	ExecuteSlotOnPaint(QPainter &pnt,bool Mastered=true,bool ShowNG=false,bool BlinkNG=false,bool BlinkOn=true);
};

//---------------------------------------------------------
class	GUICmdReqThumbnailBmp : public GUICmdPacketBase
{
public:
	double	ZoomRate;
	bool	Mastered;
	bool	ShowNG;
	int32	ShowFixedPhase;
	int		CanvasWidth;
	int		CanvasHeight;
	int		CenterX;
	int		CenterY;

	GUICmdReqThumbnailBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendThumbnailBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;

	GUICmdSendThumbnailBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendThumbnailBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(bool Mastered ,double ZoomRate
					 ,int localPage
					 ,LayersBase &LocalLBase
					 ,bool ShowNG
					 ,int32 ShowFixedPhase
					 ,int CanvasWidth,int CanvasHeight
					 ,int CenterX,int CenterY);
};

class	CmdGetZoomRate	:public GUIDirectMessage
{
public:
	double	ZoomRate;
};

//---------------------------------------------------------

class	GUICmdReqOkNG : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOkNG : public GUICmdPacketBase
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	GUICmdSendOkNG(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // THUMBNAILFORM_H