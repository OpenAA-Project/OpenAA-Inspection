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

#ifndef PANELXYSIZEFORM_H
#define PANELXYSIZEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PanelXYSizeForm;
}
class	SignalOperandInt;


class PanelXYSizeForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandInt	*iRegXSize;
	SignalOperandInt	*iRegYSize;
public:
	int32		LimitMaxX;
	int32		LimitMaxY;
	int			XSize;
	int			YSize;

    explicit PanelXYSizeForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelXYSizeForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::PanelXYSizeForm *ui;
};

#endif // PANELXYSIZEFORM_H