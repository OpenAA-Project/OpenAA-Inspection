/*
 * Copyright (C) 2017
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

#pragma once

#include "ui_EditRemainTimeForm.h"
#include "ShowSumTimerForm.h"
#include "XServiceForLayers.h"

class EditRemainTimeForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditRemainTimeForm(LayersBase *base, QWidget *parent=NULL);

public:
	void setHour(quint64 val);
	void setMinuite(quint32 val);
	void setSecond(quint32 val);
	void setMiliSecond(quint32 val);
	void fromMiliSecond(quint64 mili);

	LongTime time() const;

private:
	Ui::EditRemainTimeClass ui;
};