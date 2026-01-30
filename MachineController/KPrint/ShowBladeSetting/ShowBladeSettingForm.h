/*
 * Copyright (C) 2024
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

#ifndef SHOWBLADESETTINGFORM_H
#define SHOWBLADESETTINGFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include <QModelIndex>

namespace Ui {
class ShowBladeSettingForm;
}

class	EasyPropertyDentMeasureForm;

class ShowBladeSettingForm : public GUIFormBase
{
    Q_OBJECT
    EasyPropertyDentMeasureForm	*PropertyForm;

public:
    explicit ShowBladeSettingForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowBladeSettingForm();
	virtual void	BuildForShow(void)	override;
    virtual void	StartPage	(void)	override;
private slots:
    void on_tableWidgetBladeWidth_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeY_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeX_doubleClicked(const QModelIndex &index);
    void on_tableWidgetBladeR_doubleClicked(const QModelIndex &index);

	void	ResizeAction();

private:
    Ui::ShowBladeSettingForm *ui;

    EasyPropertyDentMeasureForm *GetEasyPropertyDentMeasureForm(void);
};

#endif // SHOWBLADESETTINGFORM_H