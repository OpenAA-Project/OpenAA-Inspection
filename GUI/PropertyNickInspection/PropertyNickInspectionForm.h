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

#ifndef PROPERTYNICKINSPECTIONFORM_H
#define PROPERTYNICKINSPECTIONFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XNickInspection.h"

namespace Ui {
class PropertyNickInspectionForm;
}

class	NickInspectionBase;
class	NickInspectionLibrary;

class PropertyNickInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyNickInspectionForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyNickInspectionForm();
    
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	
private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);

private:
    Ui::PropertyNickInspectionForm *ui;
    
	//NickInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	void	ShowSelectedLibList(void);
	void	ShowLibList(void);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	AlgorithmLibraryListContainer	SelectedLibList;

	NickInspectionBase	*GetNickInspectionBase(void);
	void	ShowListGrid(void);

	NickInspectionListForPacketPack	NickInspectionItemList;
	void	ShowItemList(void);
};

#endif // PROPERTYNICKINSPECTIONFORM_H