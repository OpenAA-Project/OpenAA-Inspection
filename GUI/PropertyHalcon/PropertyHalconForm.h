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

#ifndef PROPERTYHALCONFORM_H
#define PROPERTYHALCONFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyHalconForm.h"
#include "XGUIPacketForDLL.h"
#include "XPropertyHalconInspectionPacket.h"

class	GeneralLibFolderForm;

class PropertyHalconForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyHalconForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyHalconForm();

	HalconSampleList		*TempSample;
	HalconInspectionLibrary	*TempLib;

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	QString	ImagePanelName;

private:
	Ui::PropertyHalconFormClass ui;

	GeneralLibFolderForm	*pLibFolderForm;

	int		LibType;
	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	HalconInspectionBase	*GetHalconInspectionBase(void);
	void ShowSampleList(void);

private slots:
	void SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void tableViewSampleListDoubleClicked(const QModelIndex &CIndex);
	void on_pushButtonDelete_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonRegist_2_clicked();
	void on_pushButtonDeleteLib_clicked();
	void on_pushButtonUpdateLib_clicked();
	void on_pushButtonRegistLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
};

#endif // PROPERTYHALCONFORM_H