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


#ifndef PROPERTYAREASHADERFORM_H
#define PROPERTYAREASHADERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAreaShaderForm.h"
#include "XAreaShader.h"
#include "XStandardPropertyForm.h"

//===========================================================================

class PropertyAreaShaderForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyAreaShaderForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAreaShaderForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyAreaShaderFormClass ui;

	AreaShaderBase	*GetAreaShaderBase(void);
	void	ShowAreaGrid(void);

	AreaShaderListForPacketPack	AreaShaderInfo;

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);

	//AreaShaderLibrary		*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

private slots:
	void on_tableWidgetAreaShader_clicked(const QModelIndex &);
        void on_pushButtonEditLibFolder_clicked();
        void on_tableWidgetLibList_clicked(const QModelIndex &index);
        void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
        void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
        void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
        void on_pushButtonSetFrom_clicked();
        void on_pushButtonGetBack_clicked();
        void on_pushButtonSetFromAll_clicked();
        void on_pushButtonGetBackAll_clicked();
        void on_ButtonPickupTest_clicked();
        void on_ButtonPickupClearTest_clicked();
        void on_pushButtonEditLibrary_clicked();
        void on_ButtonGenerateLibs_clicked();
        void on_ButtonLibSave_clicked();
        void on_tabWidget_currentChanged(int index);
};

//===========================================================================


#endif // PROPERTYAREASHADERFORM_H