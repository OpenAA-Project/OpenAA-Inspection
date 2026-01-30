/*
 * Copyright (C) 2017
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

#ifndef AUTOSTARTEACHPARAM_H
#define AUTOSTARTEACHPARAM_H

#include <QDialog>
#include "ui_AutoStartEachParam.h"
#include "XTypeDef.h"

class AutoStartEachParam : public QDialog
{
	Q_OBJECT

public:
	AutoStartEachParam(const QString &_ExeFilePath,const QString &_Parameters,const QString &_WorkingPath,int32	_Location ,int32 _BootingWaitTime
						,QWidget *parent = 0);
	~AutoStartEachParam();

	QString	ExeFilePath;
	QString	Parameters;
	QString	WorkingPath;
	int32	Location;
	int32	BootingWaitTime;

private:
	Ui::AutoStartEachParamClass ui;

private slots:
	void on_pushButtonFile_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // AUTOSTARTEACHPARAM_H