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

#ifndef BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H
#define BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H

#include "buttonresetthresholddotcolormatching_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	ButtonResetThresholdDotColorMatching: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	NormalColor;
	QColor	PushedColor;
	QFont	CFont;

	ButtonResetThresholdDotColorMatching(LayersBase *Base ,QWidget *parent);

	virtual	void	Prepare(void)	override;
private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	IntegrationCmdResetThresholdDotColorMatching : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdResetThresholdDotColorMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

#endif // BUTTONRESETTHRESHOLDDOTCOLORMATCHING_H