/*
 * Copyright (C) 2023
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

#ifndef PANELSAVEIMAGE_H
#define PANELSAVEIMAGE_H

#include "panelsaveimage_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QIODevice>
#include <QFont>

class	PanelSaveImage :public GUIFormBase
{
    Q_OBJECT

	QListWidget	MainList;
public:
	QFont	MessageSize;

	PanelSaveImage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
	void	ResizeAction();
	void itemDoubleClicked ( QListWidgetItem * item );
};


class	GUICmdChangeCurrentFolder : public GUICmdPacketBase
{
public:
	int		FolderNumber;

	GUICmdChangeCurrentFolder(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // PANELSAVEIMAGE_H