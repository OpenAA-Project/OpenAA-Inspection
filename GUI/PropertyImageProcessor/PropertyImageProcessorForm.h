/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\PropertyImageProcessorForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYIMAGEPROCESSORFORM_H
#define PROPERTYIMAGEPROCESSORFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "ui_PropertyImageProcessorForm.h"
#include "XImageProcessor.h"

class	ImageProcessorScrollPanel;
class	FilterBase;

class PropertyImageProcessorForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyImageProcessorForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyImageProcessorForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	BuildForShow(void)							override;

	ImageProcessBase	*GetAlgorithmBase(void);

private:
	Ui::PropertyImageProcessorFormClass ui;
	ImageProcessorScrollPanel	*ScrollPanel;
	FilterBase					*TempFilter;
	QString		CurrentTitle;

	enum	_ItemMode{
		_Nothing
		,_OnMove
		,_OnSelectSourceItem
	}ItemMode;


	void	ShowProgramList(void);
	void	ShowFileNames(void);
	void	ClickSelectItem(FilterBase *Item);
	void	CreatePanelArea(void);

private slots:
	void on_ButtonConnectPartial_clicked();
	void on_ButtonPickupWeb_clicked();
	void on_FilterLineEmphasizerButton_clicked();
	void on_FilterMosaicButton_clicked();
	void on_FilterMedianButton_clicked();
	void on_AverageBinarizeButton_clicked();
	void on_ButtonDelAllProgram_clicked();
	void on_ButtonLoadDef_clicked();
	void on_ButtonMakeMaxPath_clicked();
	void on_ButtonConnectNearBy_clicked();
	void on_ButtonRemoveSpot_clicked();
	void on_ButtonErgod_clicked();
	void on_ButtonDisorderRegular_clicked();
	void on_ButtonRemoveStandalone_clicked();
	void on_MatchLearnButton_clicked();
	void on_ButtonRemoveNoise_clicked();
	void on_LinearizeButton_clicked();
	void on_StatisticButton_clicked();
	void on_FractalDimButton_clicked();
	void on_DigitalFilterLineNotchButton_clicked();
	void on_LoadImageButton_clicked();
	void on_ButtonExecuteAll_clicked();
	void on_ButtonStartOne_clicked();
	void on_pushButtonDownArrowFile_clicked();
	void on_pushButtonUpArrowFile_clicked();
	void on_tableWidgetItem_cellChanged(int,int);
	void on_listWidgetProgram_clicked(const QModelIndex &);
	void on_FilterAllocButton_clicked();
	void on_FilterThresholdButton_clicked();
	void on_FilterNotButton_clicked();
	void on_FilterXorButton_clicked();
	void on_FilterOrButton_clicked();
	void on_FilterAndButton_clicked();
	void on_FilterRelativeBinarizeButton_clicked();
	void on_FilterShrinkButton_clicked();
	void on_FilterEnfatButton_clicked();
	void on_FilterBinarizeButton_clicked();
	void on_ButtonDiverse_clicked();
	void on_ButtonTransLog_clicked();
	void on_ButtonGradiant_clicked();
	void on_ButtonLaplace_clicked();
	void on_ButtonFilterLineEmphasis_clicked();
	void on_FilterCoefButton_clicked();
	void on_FilterMulButton_clicked();
	void on_FilterSubButton_clicked();
	void on_FilterAddButton_clicked();
	void on_ButtonOpposite_clicked();
	void on_FilterMonoButton_clicked();
	void on_ButtonDelFile_clicked();
	void on_ButtonAddFile_clicked();
	void on_ButtonDelProgram_clicked();
	void on_ButtonAddProgram_clicked();

	void	SlotMouseLClickPanel(int x ,int y);
	void	SlotMouseRClickPanel(int x ,int y);
	void	SlotMouseMovePanel(int x ,int y);

	void	SlotMoveItem();
	void	SlotDeleteItem();
	void	SlotSelectSource();
	void	SlotDeleteTargetChain();
};


class	ImageProcessorScrollPanel : public QWidget
{
	Q_OBJECT
public:
	PropertyImageProcessorForm	*Form;

	ImageProcessorScrollPanel(QWidget *parent, Qt::WindowFlags flag);

	virtual	void mousePressEvent ( QMouseEvent * event )	override;
	virtual	void mouseMoveEvent ( QMouseEvent * event )		override;
	virtual	void paintEvent ( QPaintEvent * event )			override;
signals:
	void	SignalMouseLClickPanel(int x ,int y);
	void	SignalMouseRClickPanel(int x ,int y);
	void	SignalMouseMovePanel(int x ,int y);
};


#endif // PROPERTYIMAGEPROCESSORFORM_H
