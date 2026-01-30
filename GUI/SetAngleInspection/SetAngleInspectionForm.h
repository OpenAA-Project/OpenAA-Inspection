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

#ifndef SETANGLEINSPECTIONFORM_H
#define SETANGLEINSPECTIONFORM_H

#include "XGUIFormBase.h"
#include <QIODevice>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class SetAngleInspectionForm;
}

class SetAngleInspectionForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit SetAngleInspectionForm(LayersBase *base,QWidget *parent = nullptr);
    ~SetAngleInspectionForm();

    virtual void	BuildForShow(void)  override;

private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::SetAngleInspectionForm *ui;
};

//============================================================================================

class	GUICmdSetAngleInspection : public GUICmdPacketBase
{
public:
	double		OKAngleL;
	double		OKAngleH;

	GUICmdSetAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAngleInspection : public GUICmdPacketBase
{
public:

	GUICmdReqAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAngleInspection : public GUICmdPacketBase
{
public:
	double		OKAngleL;
	double		OKAngleH;

	GUICmdAckAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif // SETANGLEINSPECTIONFORM_H