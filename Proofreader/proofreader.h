/*
 * Copyright (C) 2025
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
	QList<double>	dxList;							//���x�����O����X���W���X�g
	QList<double>	dyList;							//���x�����O����Y���W���X�g
	QList<double>	CoGListX;						//�d�S��X���W���X�g
	QList<double>	CoGListY;						//�d�S��Y���W���X�g
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