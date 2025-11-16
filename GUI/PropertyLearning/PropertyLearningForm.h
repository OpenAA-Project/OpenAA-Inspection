/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\PropertyLearningForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYLEARNINGFORM_H
#define PROPERTYLEARNINGFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyLearningForm.h"
#include "XGUIPacketForDLL.h"
#include "AddFileDialog.h"


class PropertyLearningForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyLearningForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyLearningForm();
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	AddFileDialog	*AddFileDialogVar;
	
	LearningFileListContainer	*StoredList;
	LearningFileListContainer	*PickedList;
	int	SelectedPickupList;

private:
	Ui::PropertyLearningFormClass ui;

	void ShowTrialList(void);
	void ShowAreaGrid(void);

	LearningAreaListContainer	AreaList;

private slots:
	void on_pushButtonDelTrialFile_clicked();
	void on_pushButtonAddTrialFile_clicked();
	void on_tableWidgetAreaList_clicked(const QModelIndex &);
	void on_tableWidgetTrialList_doubleClicked(QModelIndex);
};

#endif // PROPERTYLEARNINGFORM_H
