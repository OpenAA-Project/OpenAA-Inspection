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

#pragma once

#include "easyshowngmessagefordatavalidation_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"

class	CheckDataValidationBase;
class	ShowNGMessageForm;

class	EasyShowNGMessageForDataValidation : public GUIFormBase
{
	Q_OBJECT

	ShowNGMessageForm	*NGMessageWindow;
public:
	bool ModeShowNGMessage;

	EasyShowNGMessageForDataValidation(LayersBase *Base ,QWidget *parent);
	~EasyShowNGMessageForDataValidation(void);
	
	virtual void	ReadyParam(void)	override;
	void	SetNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);

private:
	CheckDataValidationBase	*GetCheckDataValidationBase(void);
private slots:
	void    SlotShowNGMessage(int phase ,int page);
	void	SlotNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);
signals:
	void	SignalNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);
};


class	IntegrationCmdShowNGMessage : public IntegrationCmdPacketBase
{
public:
    int		Phase;
	QString	NGMessage;

	IntegrationCmdShowNGMessage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};
