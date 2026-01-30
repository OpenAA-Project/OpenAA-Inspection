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

#ifndef MESSAGER_H
#define MESSAGER_H

#include <QMainWindow>
#include "ui_Messager.h"
#include "NList.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "XDateTime.h"
#include <QFile>
#include "PopupWindow.h"
#include "DiskReporterForm.h"
#include "XServiceForLayers.h"

class	MStringList : public NPList<MStringList>
{
public:
	QString		Msg;
	XDateTime	EventTime;

	MStringList(void);
};

class Messager : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QTcpServer	SockServer;
	NPListPack<MStringList>	MStringData;
	NPListPack<MStringList>	MStringDataGeneral;
	QString		LogFileName;

public:
	PopupWindow			*PopupW;
	DiskReporterForm	*PopDiskReporter;

	Messager(LayersBase *base,int Port,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Messager();

	void	PutMessage(int TypeValue,int GlobalPage,const QString &MessageStr);
	void	PutMessage(int GlobalPage,const QString &MessageStr);

private:
	Ui::MessagerClass ui;
	void	WriteLog(int GlobalPage,const QString &MessageStr);
	void	WriteLog(int TypeValue,int GlobalPage,const QString &MessageStr);
	void	WriteLog(QFile &FL,const QString &MessageStr);

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonSequence_clicked();
	void SlotNewConnection();
};

class	MessagePopper : public QObject
{
	Q_OBJECT
public:
	QTcpSocket	*Sv;
	Messager	*Parent;

	MessagePopper(Messager *parent){	Sv=NULL;	Parent=parent;	}

private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};


#endif // MESSAGER_H