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

#ifndef DISPLAYLIBFOLDERFORM_H
#define DISPLAYLIBFOLDERFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"

namespace Ui {
    class DisplayLibFolderForm;
}

class	GeneralLibFolderForm;

class DisplayLibFolderForm : public GUIFormBase
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	QString FolderName;
public:
    explicit DisplayLibFolderForm(LayersBase *base ,QWidget *parent = 0);
    ~DisplayLibFolderForm();

	int		SelectedLibFolderID;
	QString SelectedFolderName;

private slots:
    void on_pushButtonSet_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::DisplayLibFolderForm *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // DISPLAYLIBFOLDERFORM_H