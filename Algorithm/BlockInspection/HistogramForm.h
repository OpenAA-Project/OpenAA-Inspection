/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\HistogramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef HISTOGRAMFORM_H
#define HISTOGRAMFORM_H

#include <QWidget>
#include <QToolBar>
#include "ui_HistogramForm.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XGUIComponent.h"

class	mtColorFrame;

class HistogramForm : public AlgorithmComponentWindow,public ServiceForLayers ,public PasswordInQWodget
{
	Q_OBJECT

public:
	HistogramForm(LayersBase *Base,QWidget *parent = 0);
	~HistogramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::HistogramFormClass ui;

	DisplaySimPanel		SimPanel;
	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	mtLineGraph						LGraph;
	//mtGLine							GraphColMaster;
	//mtGLine							GraphColTarget;
	mtGStick						GraphColMaster;
	mtGStick						GraphColTarget;
	mtGStick						GraphThresh;
	AlgorithmItemIndependentPack	*IData;
	int								YMax;
	int								Page;

	AlgorithmBase *InstBase;
	int32	OldLibID		;
	WORD	OldCenterBright	;
	short	OldNBrightWidthL;		
	short	OldNBrightWidthH;		
	short	OldBBrightWidthL;		
	short	OldBBrightWidthH;	
	int32	NewLibID		;
	WORD	NewCenterBright	;
	short	NewNBrightWidthL;		
	short	NewNBrightWidthH;		
	short	NewBBrightWidthL;		
	short	NewBBrightWidthH;	

	WORD	CenterBright;
	short	NBrightWidthL;		
	short	NBrightWidthH;		
	short	BBrightWidthL;		
	short	BBrightWidthH;		

	short	AbsNBrightWidthL;	
	short	AbsNBrightWidthH;	
	short	AbsBBrightWidthL;	
	short	AbsBBrightWidthH;	

	WORD	NMinNGCountL;
	WORD	NMinNGCountH;
	WORD	BMinNGCountL;
	WORD	BMinNGCountH;
	BYTE	NConnectLen;	
	BYTE	BConnectLen;	

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

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	SetColoriseByManual(void);
	bool	OnChanging;
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
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_toolButtonSimShowBlock_clicked();
    void on_toolButtonSimShowBright_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditBOKDotL_valueChanged(int arg1);
    void on_EditBOKDotH_valueChanged(int arg1);
    void on_EditBOKLengthL_valueChanged(int arg1);
    void on_EditBOKLengthH_valueChanged(int arg1);
    void on_EditNOKDotL_valueChanged(int arg1);
    void on_EditNOKDotH_valueChanged(int arg1);
    void on_EditNOKLengthL_valueChanged(int arg1);
    void on_EditNOKLengthH_valueChanged(int arg1);
    void on_EditAdjustBlack_valueChanged(int arg1);
    void on_checkBModeAdjustable_clicked(bool checked);
    void on_EditAdjustWhite_valueChanged(int arg1);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_EditCommonMoveDot_valueChanged(int arg1);
    void on_checkBModeWhiteMask_clicked(bool checked);
    void on_checkBModeBlackMask_clicked(bool checked);
    void on_EditNMaxNGDotL_valueChanged(int arg1);
    void on_EditNMaxNGDotH_valueChanged(int arg1);
    void on_EditBMaxNGDotL_valueChanged(int arg1);
    void on_EditBMaxNGDotH_valueChanged(int arg1);
    void on_checkBModeInvertLogic_clicked();
    void on_checkBModeSearchDetail_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_EditBConnectLen_valueChanged(int arg1);
    void on_EditBMinNGCountL_valueChanged(int arg1);
    void on_EditBMinNGCountH_valueChanged(int arg1);
    void on_checkBModeBindBWBroad_clicked();
    void on_EditNMinNGCountL_valueChanged(int arg1);
    void on_EditNMinNGCountH_valueChanged(int arg1);
    void on_EditNConnectLen_valueChanged(int arg1);
    void on_checkBModeBindBWNarrow_clicked();
    void on_checkBModeAdoptBiggest_clicked();
    void on_doubleSpinBoxBOKDotL_valueChanged(double arg1);
    void on_doubleSpinBoxBOKDotH_valueChanged(double arg1);
    void on_doubleSpinBoxBOKLengthL_valueChanged(double arg1);
    void on_doubleSpinBoxBOKLengthH_valueChanged(double arg1);
    void on_doubleSpinBoxBMaxNGDotL_valueChanged(double arg1);
    void on_doubleSpinBoxBMaxNGDotH_valueChanged(double arg1);
    void on_doubleSpinBoxNOKDotL_valueChanged(double arg1);
    void on_doubleSpinBoxNOKDotH_valueChanged(double arg1);
    void on_doubleSpinBoxNOKLengthL_valueChanged(double arg1);
    void on_doubleSpinBoxNOKLengthH_valueChanged(double arg1);
    void on_doubleSpinBoxNMaxNGDotL_valueChanged(double arg1);
    void on_doubleSpinBoxNMaxNGDotH_valueChanged(double arg1);
    void on_doubleSpinBoxSelfSearch_valueChanged(double arg1);
    void on_doubleSpinBoxCommonMoveDot_valueChanged(double arg1);
    void on_checkBoxUseRegularBrightness_clicked();
    void on_checkBPermitInverted_clicked();
    void on_pushButtonClearManualChange_clicked();
    void on_checkBModeOppositeRange_clicked();
    void on_checkBModeUseGlobalLine_clicked();
    void on_pushButtonRestore_clicked();
};



#endif // HISTOGRAMFORM_H
