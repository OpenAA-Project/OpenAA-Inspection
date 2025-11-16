/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorHistogramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COLORHISTOGRAMFORM_H
#define COLORHISTOGRAMFORM_H

#include <QWidget>
#include <QToolBar>
#include "ui_ColorHistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

class	mtColorFrame;
class	mtToolButtonColored;

class ColorHistogramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
	Q_OBJECT

	int	Page;
public:
	ColorHistogramForm(LayersBase *Base,QWidget *parent = 0);
	~ColorHistogramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::ColorHistogramFormClass ui;

	DisplaySimPanel		SimPanel;
	QToolBar	LayerBar;
	mtToolButtonColored	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraph;
	mtGStick						GraphColMaster;
	mtGStick						GraphColTarget;
	mtGStick						GraphThresh;
	AlgorithmItemIndependentPack	*IData;
	int								YMax;

	WORD	CenterBrightR,CenterBrightG,CenterBrightB;
	short	NBrightWidthRL;	
	short	NBrightWidthRH;	
	short	BBrightWidthRL;	
	short	BBrightWidthRH;	


	short	AbsNBrightWidthRL;
	short	AbsNBrightWidthRH;
	short	AbsBBrightWidthRL;
	short	AbsBBrightWidthRH;

	short	NBrightWidthGL;	
	short	NBrightWidthGH;	
	short	BBrightWidthGL;	
	short	BBrightWidthGH;	

	short	AbsNBrightWidthGL;
	short	AbsNBrightWidthGH;
	short	AbsBBrightWidthGL;
	short	AbsBBrightWidthGH;

	short	NBrightWidthBL;	
	short	NBrightWidthBH;	
	short	BBrightWidthBL;	
	short	BBrightWidthBH;	

	short	AbsNBrightWidthBL;
	short	AbsNBrightWidthBH;
	short	AbsBBrightWidthBL;
	short	AbsBBrightWidthBH;

	WORD	RNMinNGCountL;
	WORD	RNMinNGCountH;
	WORD	RBMinNGCountL;
	WORD	RBMinNGCountH;

	WORD	GNMinNGCountL;
	WORD	GNMinNGCountH;
	WORD	GBMinNGCountL;
	WORD	GBMinNGCountH;

	WORD	BNMinNGCountL;
	WORD	BNMinNGCountH;
	WORD	BBMinNGCountL;
	WORD	BBMinNGCountH;

	WORD	RBOKLengthL;
	WORD	RBOKLengthH;
	WORD	RNOKLengthL;
	WORD	RNOKLengthH;

	WORD	GBOKLengthL;
	WORD	GBOKLengthH;
	WORD	GNOKLengthL;
	WORD	GNOKLengthH;

	WORD	BBOKLengthL;
	WORD	BBOKLengthH;
	WORD	BNOKLengthL;
	WORD	BNOKLengthH;


	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);
	void	GetActiveLayerList(IntList &LayerList);

	mtColorFrame	*MasterPanel;
	mtColorFrame	*TargetPanel;
	mtColorFrame	*ThresholdPanel;
	int				LastLayer;
signals:
	void	SignalStartCalc();
private slots:
	void	SlotStartCalc();
	void on_pushButtonChangeLib_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonRelrectSaveParts_clicked();
	void on_ButtonCalc_clicked();
	void on_EditBBrightWidthH_valueChanged(int);
	void on_EditBBrightWidthL_valueChanged(int);
	void on_EditNBrightWidthH_valueChanged(int);
	void on_EditNBrightWidthL_valueChanged(int);
	void on_tabWidgetInspect_currentChanged(int);
	void on_ButtonReflectAllBlocks_clicked();
	void on_ButtonRelrectOnlyBlock_clicked();
	void on_ButtonClose_clicked();
	void	SlotLineGraphDClick(int X,int Y);
	void	SlotLayerClicked();
    void on_toolButtonSimShowBlock_clicked();
    void on_toolButtonSimShowBright_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditNOKDotL_valueChanged(int arg1);
    void on_EditNOKDotH_valueChanged(int arg1);
    void on_EditNOKLengthL_valueChanged(int arg1);
    void on_EditNOKLengthH_valueChanged(int arg1);
    void on_EditBOKDotL_valueChanged(int arg1);
    void on_EditBOKDotH_valueChanged(int arg1);
    void on_EditBOKLengthL_valueChanged(int arg1);
    void on_EditBOKLengthH_valueChanged(int arg1);
    void on_checkBModeWhiteMask_clicked(bool checked);
    void on_checkBModeBlackMask_clicked(bool checked);
    void on_checkBModeAdjustable_clicked(bool checked);
    void on_EditAdjustBlack_valueChanged(int arg1);
    void on_EditAdjustWhite_valueChanged(int arg1);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_checkBModeCommonMovable_clicked(bool checked);
    void on_EditCommonMoveDot_valueChanged(int arg1);
};



#endif // COLORHISTOGRAMFORM_H
