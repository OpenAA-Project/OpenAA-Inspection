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

#ifndef SELECTBYLIMITEDDIALOG_H
#define SELECTBYLIMITEDDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectByLimitedDialog;
}
class SelectLibrariesForAnyType;

class SelectByLimitedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectByLimitedDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectByLimitedDialog();

	SelectLibrariesForAnyType		*Libs;
	bool	RetOK;
	void	SetSelected(AlgorithmLibraryListContainer &selectedList);
	AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_ButtonSelectAll_clicked();
    void on_ButtonSelectOneAtLeast_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectByLimitedDialog *ui;
};

#endif // SELECTBYLIMITEDDIALOG_H