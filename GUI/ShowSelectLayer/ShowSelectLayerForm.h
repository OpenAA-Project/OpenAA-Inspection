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

#ifndef SHOWSELECTLAYERFORM_H
#define SHOWSELECTLAYERFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QStringList>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImageHook.h"
#include "XDisplayImage.h"
#include "XMultiLayerColor.h"

namespace Ui {
class ShowSelectLayerForm;
}

class ShowSelectLayerForm : public GUIFormBase,public FunctionServerClass
{
    Q_OBJECT

    DisplayImage    **DisplayImagePointDim;
    MultiLayerColor Color;
public:
    QStringList DisplayImageInst;

    explicit ShowSelectLayerForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ShowSelectLayerForm();

    virtual void	ReadyParam(void)    override;
    void    ShowXY(DisplayImage *DImage,int GlobalPosX,int GlobalPosY);
private:
    Ui::ShowSelectLayerForm *ui;

    virtual void paintEvent(QPaintEvent *event) override;
};

class GUICmdReqMultiLayerColor : public GUICmdPacketBase
{
public:
	DisplayType	DType;
	int			LocalX,LocalY;

	GUICmdReqMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};

class GUICmdAckMultiLayerColor : public GUICmdPacketBase
{
public:
	MultiLayerColor Color;

	GUICmdAckMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName){}
};

#endif // SHOWSELECTLAYERFORM_H