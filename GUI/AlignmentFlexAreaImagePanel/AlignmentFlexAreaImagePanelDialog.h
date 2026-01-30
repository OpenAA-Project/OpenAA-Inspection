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

#ifndef ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H
#define ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class AlignmentFlexAreaImagePanelDialog;
}

class AlignmentFlexAreaImagePanelDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	bool	OnChanging;
public:
    explicit AlignmentFlexAreaImagePanelDialog(int ItemID ,int GlobalSearchDot ,int SearchDot ,bool KeepBW ,LayersBase *base ,QWidget *parent = 0);
    ~AlignmentFlexAreaImagePanelDialog();

	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;

    int     Page;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();

    void on_spinBoxGlobalSearchDot_valueChanged(int arg1);

    void on_spinBoxSearchDot_valueChanged(int arg1);

private:
    Ui::AlignmentFlexAreaImagePanelDialog *ui;
};

#endif // ALIGNMENTFLEXAREAIMAGEPANELDIALOG_H