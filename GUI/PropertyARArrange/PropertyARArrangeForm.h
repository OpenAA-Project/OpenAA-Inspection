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

#ifndef PROPERTYARARRANGEFORM_H
#define PROPERTYARARRANGEFORM_H

#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "ui_PropertyARArrangeForm.h"
#include "XPropertyARArrangePacket.h"

class PropertyARArrangeForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyARArrangeForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyARArrangeForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private:
	Ui::PropertyARArrangeFormClass ui;

	LearningImagePointerList	*CurrentLearning;
	LearningImagePointerContainer	LContainer;
	ARItemListContainer				CurrentARItemContainer;

	void	ShowLearningList(void);
	void	ShowArrangeList(void);
	void	ShowLearningImage(LearningImagePointerList	*p);

private slots:
	void on_tableWidgetRegistration_doubleClicked(QModelIndex);
	void on_tableWidgetArrange_doubleClicked(QModelIndex);
	void on_pushButtonUpdate_clicked();
	void on_tableWidgetArrange_clicked(const QModelIndex &);
	void on_tableWidgetRegistration_clicked(const QModelIndex &);
};

#endif // PROPERTYARARRANGEFORM_H