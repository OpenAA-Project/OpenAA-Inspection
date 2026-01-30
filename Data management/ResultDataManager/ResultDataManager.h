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

#ifndef RESULTDATAMANAGER_H
#define RESULTDATAMANAGER_H

#include <QMainWindow>
#include "ui_ResultDataManager.h"
#include "XResultDataManager.h"
#include "XMLClient.h"
#include "DeleteThread.h"
#include "XServiceForLayers.h"

class	LocalDatabaseBasicClass;

class ResultDataManager : public QMainWindow ,public ServiceForLayers
{
	Q_OBJECT

	QStringList	EnumResultList;
	ResultDataManagerParam	RParam;

	LocalDatabaseBasicClass	*KDatabase;

public:
	ResultDataManager(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ResultDataManager();

	bool	ConnectXML(void);
	bool	ConnectDatabase(void);

private slots:
        void on_pushButtonByLot_clicked();

        void on_pushButtonByDayTime_clicked();

        void on_pushButtonSetting_clicked();

        void on_pushButtonClose_clicked();

private:
	Ui::ResultDataManagerClass ui;
};

#endif // RESULTDATAMANAGER_H