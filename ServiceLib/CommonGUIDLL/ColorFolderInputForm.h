/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\ColorFolderInputForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COLORFOLDERINPUTFORM_H
#define COLORFOLDERINPUTFORM_H

#include <QDialog>
#include "ui_ColorFolderInputForm.h"
#include "XServiceForLayers.h"

class ColorFolderInputForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ColorFolderInputForm(LayersBase *base,const QString &folderName ,QWidget *parent);
	~ColorFolderInputForm();

	QString	FolderName;

	virtual	void closeEvent ( QCloseEvent * event )	override;

private:
	Ui::ColorFolderInputFormClass ui;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // COLORFOLDERINPUTFORM_H
