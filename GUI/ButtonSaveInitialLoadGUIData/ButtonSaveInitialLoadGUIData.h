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

#include "buttonsaveinitialloadguidata_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>


class	GUIDataList : public NPListSaveLoad<GUIDataList>
{
public:
	QString		DLLRoot	;
	QString		DLLName	;
	QString		InstName;
	QByteArray	Data	;

	GUIDataList(void){}
	GUIDataList(const GUIDataList &src);

	bool	operator=(const GUIDataList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class GUIDataListContainer : public NPListPackSaveLoad<GUIDataList>
{
public:
	GUIDataListContainer(){}

	virtual GUIDataList *Create(void)	override;

	bool	HasSameData(GUIDataList *data);
	bool	GetContentData(GUIInitializer *GInitialier);
	bool	RefrectContentData(GUIInitializer *GInitialier);
};

//================================================================


class	ButtonSaveInitialLoadGUIData : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	InitialFileName;

	GUIDataListContainer	Data;

	ButtonSaveInitialLoadGUIData(LayersBase *Base ,QWidget *parent);
	~ButtonSaveInitialLoadGUIData(void);
	
	virtual void	Prepare(void)				override;
	virtual void	AfterStartSequence(void)	override;

	bool	SaveData(void);
	bool	LoadDataAndReflect(void);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};