/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\FileRegistryEditor\FileRegistryEditor.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef FILEREGISTRYEDITOR_H
#define FILEREGISTRYEDITOR_H

#include <QMainWindow>
#include "ui_FileRegistryEditor.h"
#include "XFileRegistry.h"
#include "XServiceForLayers.h"

class FileRegistryEditor : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

public:
	FileRegistryEditor(LayersBase *base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~FileRegistryEditor();

private:
	Ui::FileRegistryEditorClass ui;

	FileRegistry	*FRegistry;
	QString PathName;
	void	ShowInfo();

	bool	SQLLoadMachine(void);


private slots:
	void on_pushButtonLoadDatabase_clicked();
	void on_pushButtonSelectFolder_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // FILEREGISTRYEDITOR_H
