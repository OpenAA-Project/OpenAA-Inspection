/*
 * Copyright (C) 2025
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

#ifndef EDITANYDATAINLIBRARY_H
#define EDITANYDATAINLIBRARY_H

#include <QMainWindow>
#include "ui_EditAnyDataInLibrary.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"

class	GeneralLibFolderForm;
class	LibNGTypeItem;

class EditAnyDataInLibrary : public QMainWindow ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditAnyDataInLibrary(LayersBase *base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditAnyDataInLibrary();

private:
	Ui::EditAnyDataInLibraryClass ui;

	void	ShowListLibType(void);
	IntList	LibTypeIDList;
	int	LibTypeID;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	IntList	LibraryIDList;
	int		SelectedLibID;

	IntList	AnyDataList;
	int		SelectedNGTypeID;

	LibNGTypeItem	*SelectedItem;

private slots:
	void on_pushButtonDelete_clicked();
	void on_pushButtonCreateNew_clicked();
	void on_pushButtonPasteFromCB_clicked();
	void on_pushButtonCopyToCB_clicked();
	void on_pushButtonSpecifiedData_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonColor_clicked();
	void on_pushButtonClose_clicked();
	void on_tableWidgetAnyData_clicked(const QModelIndex &);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_tableWidgetLibType_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // EDITANYDATAINLIBRARY_H