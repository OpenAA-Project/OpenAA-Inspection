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

#ifndef INSPECTIONDATAFORM_H
#define INSPECTIONDATAFORM_H

#include <QDialog>
#include <QTimer>
#include "ui_InspectionDataForm.h"

class InspectionDataForm : public QDialog
{
	Q_OBJECT

public:
	InspectionDataForm();
	~InspectionDataForm();

	void SetDialog(int Type,QList<QByteArray> *XMLFData,QList<QByteArray> *XMLBData,int MCount,int Flg);

	void			   SetRetXMLDataList(int Type,QList<QByteArray> *XMLData)	{	XMLDataList[Type]=*XMLData;	}
	QList<QByteArray> *GetRetXMLDataList(int Type)								{	return &XMLDataList[Type];	}

protected:
	virtual	void closeEvent(QCloseEvent *event)	override;

private slots:
	void pbEnterClicked();
	void update();

private:
	Ui::InspectionDataFormClass ui;

	QList<QByteArray>	XMLDataList[2];

	QTimer *timer;
	QPalette PaletteDefault;
	QPalette PaletteAlarm[2];
	char	Index;
};

#endif // INSPECTIONDATAFORM_H