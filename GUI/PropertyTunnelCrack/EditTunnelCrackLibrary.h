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

#ifndef EDITTUNNELCRACKLIBRARY_H
#define EDITTUNNELCRACKLIBRARY_H

#include <QDialog>
#include "ui_EditTunnelCrackLibrary.h"
#include "XTunnelCrack.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class EditTunnelCrackLibrary : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditTunnelCrackLibrary(LayersBase *base ,QWidget *parent = 0);
	~EditTunnelCrackLibrary();

private:
	Ui::EditTunnelCrackLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	TunnelCrackLibrary	*TempLib;
	int		LibType;
	void	ShowLibrary(TunnelCrackLibrary &data);
	void	GetLibraryFromWindow(TunnelCrackLibrary &data);

	TunnelCrackBase	*GetTunnelCrackBase(void);
	void		ShowSubtractList(TunnelCrackLibrary &data);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITTUNNELCRACKLIBRARY_H