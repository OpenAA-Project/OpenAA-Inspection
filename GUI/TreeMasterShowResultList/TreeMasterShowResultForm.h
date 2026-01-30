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

#ifndef TREEMASTERSHOWRESULTFORM_H
#define TREEMASTERSHOWRESULTFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XTreeMasterPacket.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
    class TreeMasterShowResultForm;
}

class TreeMasterShowResultForm : public GUIFormBase
{
    Q_OBJECT

	TreeMasterResultListForPacketPack	TreeMasterInfo;
public:
    explicit TreeMasterShowResultForm(LayersBase *base,QWidget *parent = 0);
    ~TreeMasterShowResultForm();

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::TreeMasterShowResultForm *ui;
};

class	GUICmdReqTreeMasterResultList : public GUICmdPacketBase
{
public:
	GUICmdReqTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendTreeMasterResultList : public GUICmdPacketBase
{
public:
	TreeMasterResultListForPacketPack	TreeMasterInfo;

	GUICmdSendTreeMasterResultList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeTreeMasterResultList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif // TREEMASTERSHOWRESULTFORM_H