/*
 * Copyright (C) 2021
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

#pragma once

#include <QString>
#include <QStringList>
#include <QTranslator>
#include <QColor>
#include <QFont>
#include "XGUIFormBase.h"
#include <QPushButton>
#include <QWebSocket>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	TypeDefinition : public GUIFormBase
{
    Q_OBJECT

	QPushButton	Button;
	QWebSocket  Web;
	volatile	bool		Received;
	QString		Ack;
	int			WaitingMilisec;
public:
	QString		ApplicationHashTag;
	QString		ApplicationName;
	QString		ServerAddress;

	QString		Msg;
	QColor		CharColor;
	QColor		NormalColor;
	QColor		PushedColor;
	QFont		CFont;

	enum	ActivatedResult
	{
		 _AR_ExpiredByDate
		,_AR_NoRegistration
		,_AR_DestroyedRegistry
		,_AR_ErrorHardware
		,_AR_NoMatchActivation
		,_AR_ActivatedOK
	};

	TypeDefinition(LayersBase *Base ,QWidget *parent);
	~TypeDefinition(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	ActivatedResult	IsActivated(qint64 SpanSecFromInstall=-1);
	bool	ActivateByOrderCode(const QString &OrderCodeStr);
	bool	ActivateByLicenseFile(const QString &FileName);
	bool	ActivateByCode(const QString &ActivationCode);
	QString	GetPCCode(void);

	bool	SavePCInfo	(const QString &LicenseKey ,const QString &FileName);
	bool	LoadActivation(const QString &FileName);

private slots:
    void	SlotBinaryMessageReceived(const QByteArray &message);
	void	SlotClicked ();
	void	SlotWebConnected();
	void	ResizeAction();

	bool	ActivationByOrderCode(const QByteArray &LicenseKey);
	bool	RegisterActivation(const QByteArray	&LicenseData);
};


class	CmdCheckByDate : public GUIDirectMessage
{
public:
	qint64 SpanSecFromInstall;
	TypeDefinition::ActivatedResult	Result;

	CmdCheckByDate(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCheckActivated : public GUIDirectMessage
{
public:

	TypeDefinition::ActivatedResult	Result;

	CmdCheckActivated(LayersBase *base):GUIDirectMessage(base){}
};