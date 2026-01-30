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

#ifndef INTEGRATIONSHOWOKNG_H
#define INTEGRATIONSHOWOKNG_H

#include "integrationshowokng_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XResult.h"

class	IntegrationShowOKNG : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	bool3	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;
	int		CurrentInspectionID;
	QString	SpecialMessage;
public:
	QFont	MessageSize;
	ResultInspection::CriticalErrorMode	CriticalError;
	QColor	ColorOK;
	QColor	ColorNG;
	QColor	ColorHalt;
	QString	MsgOK;
	QString	MsgNG;

	QString	Message1;
	QString	Message2;

	IntegrationShowOKNG(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:

private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	CmdSendOkNG : public GUIDirectMessage
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	CmdSendOkNG(LayersBase *base):GUIDirectMessage(base){}
};

#endif // INTEGRATIONSHOWOKNG_H