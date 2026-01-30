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


#ifndef LISTBOXALGORITHMCOUNT_H
#define LISTBOXALGORITHMCOUNT_H

#include "listboxalgorithmcount_global.h"
#include <QTableWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ListboxAlgorithmCount : public GUIFormBase
{
	Q_OBJECT

	QTableWidget	MainList;
public:

	ListboxAlgorithmCount(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithmCount(void);
	
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
	void	ResizeAction();
};

//===============================================================================


class	GUICmdReqAlgorithmItemCount : public GUICmdPacketBase
{
public:

	GUICmdReqAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmItemCount : public GUICmdPacketBase
{
public:
	NPListPack<AlgorithmItemCountInBase>	CountInBases;

	GUICmdSendAlgorithmItemCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	void	MakeLists(int localPage ,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // LISTBOXALGORITHMCOUNT_H