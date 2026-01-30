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


#ifndef PROPERTYAUTOCLASSIFYFORM_H
#define PROPERTYAUTOCLASSIFYFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoClassifyForm.h"
#include "XAutoClassify.h"
#include "XPropertyAutoClassifyPacket.h"

class	AutoClassifyItem;
class	AutoClassifyBase;

class PropertyAutoClassifyForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyAutoClassifyForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAutoClassifyForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)		override;
	virtual void	StartPage	(void)		override;

private:
	Ui::PropertyAutoClassifyFormClass ui;

	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	AutoClassifyBase	*GetAutoClassifyBase(void);

	NPListPack<AreaInfoList>	AreaInfos;
	void		ShowAreaInfoList(void);

private slots:
	void on_toolButtonAreaMode_clicked();
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_tableWidgetBlockInfo_clicked(const QModelIndex &);
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_pushButtonEditLibFolder_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonLibSave_clicked();
};

#endif // PROPERTYAUTOCLASSIFYFORM_H