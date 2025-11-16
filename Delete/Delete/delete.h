/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Delete\Delete\delete.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DELETE_H
#define DELETE_H

#include <QWidget>
#include "ui_delete.h"
#include <QDir>
#include <QLibrary>
#include <QProgressBar>

class Delete : public QWidget
{
	Q_OBJECT

public:
	Delete(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
private:
	Ui::DeleteClass ui;
	
	void setFilters();
	void setFilters_Source();
	void DeleteMain(const QString &ChildDir);
	void removeFile(QDir &NowDir,const QString &NowPath);
	bool shouldDeleteFile(const QString &FileName);
	void removeSvn(const QString &NowPath);
	void removeSvnFile(const QString &SvnDir);
	void removeSvnDir(const QString &SvnDir);

	QStringList nameFilters;
private slots:
	void on_pushButtonSource_clicked();
	void on_pushButton_clicked();
};

#endif // DELETE_H
