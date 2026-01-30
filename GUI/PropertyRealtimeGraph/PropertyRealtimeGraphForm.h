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

#ifndef PROPERTYREALTIMEGRAPHFORM_H
#define PROPERTYREALTIMEGRAPHFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyRealtimeGraphForm.h"

class PropertyRealtimeGraphForm : public GUIFormBase
{
	Q_OBJECT

	int	CamNumb;
public:
	QStringList	RelatedRealtimeGraph;

	PropertyRealtimeGraphForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyRealtimeGraphForm();

	virtual void	AfterStartSequence(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	Ui::PropertyRealtimeGraphFormClass ui;

private slots:
};

#endif // PROPERTYREALTIMEGRAPHFORM_H