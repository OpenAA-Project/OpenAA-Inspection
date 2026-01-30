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

#ifndef BUTTONTOSELECTRESULTLOTFRAMEFORM_H
#define BUTTONTOSELECTRESULTLOTFRAMEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonToSelectResultLotFrameForm;
}

class ButtonToSelectResultLotFrameForm : public GUIFormBase
{
    Q_OBJECT

	bool	LoadLastID;

	QString		iLotID;
	QString		iLotName;
	QString		iRemark;
	int			iIDNumber;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int		MaxLines;
	IntList	GroupList;

    explicit ButtonToSelectResultLotFrameForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonToSelectResultLotFrameForm();

	virtual	void	Prepare(void)			override;
	virtual	void	BuildForShow(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)		override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();

private:
    Ui::ButtonToSelectResultLotFrameForm *ui;

	void SetLotToSystem(int iLotAutoCount
						,QString iLotID
						,QString iLotName);
};

//----------------------------------------------------------------------------------

class	GUICmdReqGroupList : public GUICmdPacketBase
{
public:
	GUICmdReqGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckGroupList : public GUICmdPacketBase
{
public:
	IntList		GroupList;

	GUICmdAckGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//----------------------------------------------------------------------------------

class	GUICmdSelectFrameLot : public GUICmdPacketBase
{
public:
	int			LotAutoCount;
	QString		LotID;
	QString		LotName;
	QString		Remark;
	XDateTime	CurrentInspectTime;

	GUICmdSelectFrameLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONTOSELECTRESULTLOTFRAMEFORM_H