/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MaskingImagePanel\SelectLibraryInMask\SelectLibraryInMaskForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTLIBRARYINMASKFORM_H
#define SELECTLIBRARYINMASKFORM_H

#include <QWidget>
#include "ui_SelectLibraryInMaskForm.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

class SelectLibrariesForAnyType;

class SelectLibraryInMaskForm : public QWidget ,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectLibraryInMaskForm(bool NewMode ,LayersBase *Base ,QWidget *parent = 0);
	~SelectLibraryInMaskForm();

	SelectLibrariesForAnyType		*Libs;
	bool	RetOK;
	bool	Effective;
	bool	DeleteMode;
	void	SetSelected(AlgorithmLibraryListContainer &selectedList);
	AlgorithmLibraryListContainer		GetSelectedList(void);
private:
	Ui::SelectLibraryInMaskFormClass ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;
signals:
	void	SignalClose(void);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonNotEffective_clicked();
	void on_ButtonEffective_clicked();
    void on_pushButtonDelete_clicked();
};

#endif // SELECTLIBRARYINMASKFORM_H
