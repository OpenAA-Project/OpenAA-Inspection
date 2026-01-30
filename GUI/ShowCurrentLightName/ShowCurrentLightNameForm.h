/*
 * Copyright (C) 2019
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

#ifndef SHOWCURRENTLIGHTNAMEFORM_H
#define SHOWCURRENTLIGHTNAMEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class ShowCurrentLightNameForm;
}

class ShowCurrentLightNameForm : public GUIFormBase
{
    Q_OBJECT

public:
	QFont	CFont;

    explicit ShowCurrentLightNameForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowCurrentLightNameForm();

	virtual void	Prepare		(void) override;
	virtual void	ShowInEdit	(void) override;
private slots:
		void	ResizeAction();
private:
    Ui::ShowCurrentLightNameForm *ui;
};

#endif // SHOWCURRENTLIGHTNAMEFORM_H