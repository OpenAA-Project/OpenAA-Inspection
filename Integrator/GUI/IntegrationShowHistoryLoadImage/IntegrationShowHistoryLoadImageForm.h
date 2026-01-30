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

#ifndef INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H
#define INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class IntegrationShowHistoryLoadImageForm;
}

class	InspectionLine : public NPList<InspectionLine>
{
public:
	InspectionList	*InspectionPointer[100];
	int				ID;

	InspectionLine(void);

	XDateTime	GetTime(void);
	bool	IsAllOK(void);
};


class IntegrationShowHistoryLoadImageForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QLabel	*FileNameLabel[100];	
	ImageBuffer	*Image[100];

	NPListPack<InspectionLine>	Inspections;
	int		labelFileNameS0Height;
public:
	bool	DefaultNGOnly;

    explicit IntegrationShowHistoryLoadImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowHistoryLoadImageForm();

	virtual void	Prepare(void)		override;
	virtual void	StartLot(void)		override;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
	void	ResizeAction();
    void on_toolButtonOnlyNG_clicked();

private:
    Ui::IntegrationShowHistoryLoadImageForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
};

#endif // INTEGRATIONSHOWHISTORYLOADIMAGEFORM_H