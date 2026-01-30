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

#ifndef BUTTONSAVEMATRIXCELL_H
#define BUTTONSAVEMATRIXCELL_H

#include "buttonsavematrixcell_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonSaveMatrixCell : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonSaveMatrixCell(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	SaveMatrixCell(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqAlgorithmData : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	AlgorithmRoot;
	QString	AlgorithmName;


	GUICmdReqAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmData : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QBuffer	Data;

	GUICmdSendAlgorithmData(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONSAVEMATRIXCELL_H