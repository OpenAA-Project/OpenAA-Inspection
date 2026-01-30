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

#ifndef CREATETUNNELFORM_H
#define CREATETUNNELFORM_H

#include <QDialog>
#include "ui_CreateTunnelForm.h"
#include "XTunnelCrack.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CreateTunnelForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	CreateTunnelForm(LayersBase *base ,QWidget *parent = 0);
	~CreateTunnelForm();

	TunnelCrackLibrary	*TempLib;
	int	SelectedLibID;
private:
	Ui::CreateTunnelFormClass ui;

	TunnelCrackBase	*GetTunnelCrackBase(void);
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	int		LibType;

private slots:
	void on_ButtonOK_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // CREATETUNNELFORM_H