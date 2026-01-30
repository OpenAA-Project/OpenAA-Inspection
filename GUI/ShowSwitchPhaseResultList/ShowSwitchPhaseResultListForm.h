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

#ifndef SHOWSWITCHPHASERESULTLISTFORM_H
#define SHOWSWITCHPHASERESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowSwitchPhaseResultListForm;
}

class ShowSwitchPhaseResultListForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	bool	Horizontal;

    explicit ShowSwitchPhaseResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowSwitchPhaseResultListForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
    virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::ShowSwitchPhaseResultListForm *ui;

private slots:
	void	ResizeAction();
    void on_pushButtonClear_clicked();
};

//============================================================================================

class	GUICmdReqSwitchPhaseResult : public GUICmdPacketBase
{
public:
	GUICmdReqSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckSwitchPhaseResult : public GUICmdPacketBase
{
public:
	int32	*InspectionCountInPhase;
	int32	InspectionCountInPhaseNumb;

	GUICmdAckSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);
	~GUICmdAckSwitchPhaseResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdClearSwitchPhaseResult : public GUICmdPacketBase
{
public:
	GUICmdClearSwitchPhaseResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SHOWSWITCHPHASERESULTLISTFORM_H