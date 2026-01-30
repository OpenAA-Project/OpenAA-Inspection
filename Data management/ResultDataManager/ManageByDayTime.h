/*
 * Copyright (C) 2022
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

#ifndef MANAGEBYDAYTIME_H
#define MANAGEBYDAYTIME_H

#include <QDialog>
#include "XResultDataManager.h"
#include "XServiceForLayers.h"
#include "NList.h"
#include "XMLClient.h"
#include "XDatabaseLoader.h"

namespace Ui {
    class ManageByDayTime;
}

class ManageByDayTime : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ResultDataManagerParam	*SParam;

	XMLServerHandle	*XMLServer;
	std::shared_ptr<DatabaseLoader>	SQLDatabase;
	RServerParam	ServerParam;

	QStringList		EnumResultList;

public:
    explicit ManageByDayTime(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent = 0);
    ~ManageByDayTime();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonExecuteDelete_clicked();

private:
    Ui::ManageByDayTime *ui;
};

#endif // MANAGEBYDAYTIME_H