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


#ifndef EDITBLOCKLIBRARY_H
#define EDITBLOCKLIBRARY_H

#include <QDialog>
#include "ui_EditBlockLibrary.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	GeneralLibFolderForm;

class EditBlockLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditBlockLibrary(LayersBase *base ,QWidget *parent);
	~EditBlockLibrary();

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private:
	Ui::EditBlockLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//BlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	BlockBase	*GetBlockBase(void);
	void		ShowSubtractList(BlockLibrary &data);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;

private slots:
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_ButtonDelSubtractLib_clicked();
	void on_ButtonAddSubtractLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
	void	MListSectionClicked ( int logicalIndex );
    void on_checkBoxGenerateMultiLayer_clicked();
    void on_checkBoxPickupMultiLayer_clicked();
};

#endif // EDITBLOCKLIBRARY_H