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

#ifndef PROPERTYLEARNINGFORM_H
#define PROPERTYLEARNINGFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyLearningForm.h"
#include "XGUIPacketForDLL.h"
#include "AddFileDialog.h"


class PropertyLearningForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyLearningForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyLearningForm();
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	AddFileDialog	*AddFileDialogVar;
	
	LearningFileListContainer	*StoredList;
	LearningFileListContainer	*PickedList;
	int	SelectedPickupList;

private:
	Ui::PropertyLearningFormClass ui;

	void ShowTrialList(void);
	void ShowAreaGrid(void);

	LearningAreaListContainer	AreaList;

private slots:
	void on_pushButtonDelTrialFile_clicked();
	void on_pushButtonAddTrialFile_clicked();
	void on_tableWidgetAreaList_clicked(const QModelIndex &);
	void on_tableWidgetTrialList_doubleClicked(QModelIndex);
};

#endif // PROPERTYLEARNINGFORM_H