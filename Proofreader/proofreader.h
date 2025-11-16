/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\proofreader.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef PROOFREADER_H
#define PROOFREADER_H

#include <QMainWindow>
#include <QList>
#include "ui_proofreader.h"
#include "XGUI.h"

//#include "XForHalcon.h"

class mtGraphicUnit;

class Proofreader : public QMainWindow
{
	Q_OBJECT

public:
	Proofreader(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Proofreader();

private slots:
	void pbLoadMasterImage_clicked	();
	void pbThreshold_clicked		();
	void pbLabelingX_clicked		();
	void pbLabelingY_clicked		();
	void pbSave_clicked				();
	void pbShowGraph_clicked		();
	void pbShowGraphFromCsv_clicked	();
	void pbWhiteBalance_clicked		();
	void pbClose_clicked			();
	void SlotOnPaint				(QPainter &Pnt);
	void tbExpansionToggled			(bool Toggled);
	void tbWholeClicked				();
	void tbRectangleToggled			(bool Toggled);
	void SlotMouseLDown				(int X,int Y);
	void SlotDrawEnd				();
	void SlotMouseRDown				(int X,int Y);

	void cbCameraIndexChanged		(int Index);
	void chkReverseToggled			(bool Toggled);

	void pbLoadPixHalconClicked		();

protected:
//	virtual void mousePressEvent(QMouseEvent *event);

private:
	Ui::ProofreaderClass ui;
	mtGraphicUnit *guMasterImage;
	int		GetThreshold	(int X,int Y);
	void	SetLabel		(int iStartX,int iStartY,int iLabel);
	void	ScanThreshold	(int iStartX,int iStartY,int iLabel);
	bool	NextX			(int &X,int &Y);
	bool	NextY			(int &X,int &Y);
	int		Threshold;
//	int		MaxX,MaxY;
	int		iDotPerLine;
	int		iMaxLines;
	short	**ThresholdDotArray;
	int		CntClick;
//	int		CntClick,CntDraw;
	int		StartPointX,StartPointY,EndPointX,EndPointY;
	int		MaskMaxX,MaskMaxY;
	QList<double>	dxList;							//ラベリング時のX座標リスト
	QList<double>	dyList;							//ラベリング時のY座標リスト
	QList<double>	CoGListX;						//重心のX座標リスト
	QList<double>	CoGListY;						//重心のY座標リスト
	QList<double>	dxAverageList;
	QList<double>	nowAverageList,oldAverageList;
	QImage	**img;
	int		CurrentIndex;
//	int		LNumb;
	int		iPageNumb;
	int		iLayerNumb;
//	BYTE	*pBuff[3];
//	BYTE	***Buff;
	ImageBuffer	***Buff;
	QList<int> RDataList,GDataList,BDataList;

//	XForHalcon XHalcon;
};

#endif // PROOFREADER_H
