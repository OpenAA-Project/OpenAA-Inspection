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

#ifndef PANELRESOLUTIONSIZEFORM_H
#define PANELRESOLUTIONSIZEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class PanelResolutionSizeForm;
}

class PanelResolutionSizeForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    QString Unit;

    explicit PanelResolutionSizeForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelResolutionSizeForm();
    
    virtual void	Prepare(void)	override;
private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::PanelResolutionSizeForm *ui;
};
//============================================================================================

class	GUICmdResolutionSize : public GUICmdPacketBase
{
public:
    int32   ResolutionXNano;
    int32   ResolutionYNano;
    int32   XLen;
    int32   YLen;

	GUICmdResolutionSize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PANELRESOLUTIONSIZEFORM_H