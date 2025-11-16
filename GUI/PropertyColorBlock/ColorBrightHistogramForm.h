/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorBrightHistogramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef COLORBRIGHTHISTOGRAMFORM_H
#define COLORBRIGHTHISTOGRAMFORM_H

#include <QDialog>
#include "ui_ColorBrightHistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XFlexArea.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"

class	ColorBlockImagePanel;

class ColorBrightHistogramForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ColorBrightHistogramForm(FlexArea &area ,ColorBlockImagePanel *parentPanel 
													,int pickupRL,int pickupRH
													,int pickupGL,int pickupGH
													,int pickupBL,int pickupBH
													,QWidget *parent);
	~ColorBrightHistogramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThreshR;
	mtGStick						GraphThreshG;
	mtGStick						GraphThreshB;
	FlexArea						GlobalArea;
	ColorBlockImagePanel			*ParentPanel;
	int								PickupRL;
	int								PickupRH;
	int								PickupGL;
	int								PickupGH;
	int								PickupBL;
	int								PickupBH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect( int pickupRL ,int pickupRH
					,int pickupGL ,int pickupGH
					,int pickupBL ,int pickupBH);

private:
	Ui::ColorBrightHistogramFormClass ui;

	mtToolButtonColored	*SelRButton;
	mtToolButtonColored	*SelGButton;
	mtToolButtonColored	*SelBButton;
	int	MaxY;
	int	CurrentColor;

private slots:
	void on_toolButtonL3_clicked();
	void on_toolButtonL2_clicked();
	void on_toolButtonL1_clicked();
	void on_EditPickupBH_valueChanged(int);
	void on_EditPickupBL_valueChanged(int);
	void on_EditPickupGH_valueChanged(int);
	void on_EditPickupGL_valueChanged(int);
	void on_EditPickupRH_valueChanged(int);
	void on_EditPickupRL_valueChanged(int);
	void on_ButtonClose_clicked();
	void on_ButtonReflect_clicked();
	void	SlotLineGraphDClick(int ,int );
};


#endif // COLORBRIGHTHISTOGRAMFORM_H
