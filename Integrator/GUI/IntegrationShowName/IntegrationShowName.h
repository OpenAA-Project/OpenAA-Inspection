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

#ifndef INTEGRATIONSHOWNAME_H
#define INTEGRATIONSHOWNAME_H

#include "integrationshowname_global.h"
#include "XGUIFormBase.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

class	IntegrationShowName : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QLabel	LabelTitleNumber;
	QLabel	LabelTitleName	;
	QLabel	LabelTitleRemark;
	QLabel	LabelDataNumber	;
	QLabel	LabelDataName	;
	QLabel	LabelDataRemark	;
public:
	QFont	TitleFont;
	QFont	CharFont;
	QString	TitleMasterNumber;
	QString	TitleMasterName;
	QString	TitleRemark;
	QColor	TitleColor;

	IntegrationShowName(LayersBase *Base ,QWidget *parent = 0);
	~IntegrationShowName();

	virtual void	Prepare(void)	override;
private:
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
	void	ResizeAction();
};

class	CmdShowNameInfo : public SpecifiedBroadcaster
{
public:
	QString	MasterNumber;
	QString	MasterName;
	QString	Remark;
};

#endif // INTEGRATIONSHOWNAME_H