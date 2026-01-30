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

#ifndef DISKREPORTERFORM_H
#define DISKREPORTERFORM_H

#include <QWidget>
#include "ui_DiskReporterForm.h"
#include "NList.h"
#include "XDateTime.h"
#include <QString>
#include "XFileRegistry.h"

class	DiskReportList:public NPList<DiskReportList>
{
public:
	XDateTime	FTime;
	QString		Tag;
	QString		Data;
};


class DiskReporterForm : public QWidget
{
	Q_OBJECT

	NPListPack<DiskReportList>	DiskReportData;
	FileRegistry	FRegistry;
public:
	DiskReporterForm(QWidget *parent = 0);
	~DiskReporterForm();

	void	SetList(QString Str);

private:
	Ui::DiskReporterFormClass ui;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	void	ShowList(void);

};

#endif // DISKREPORTERFORM_H