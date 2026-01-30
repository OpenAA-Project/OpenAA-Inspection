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

#ifndef EDITFlatInspectionLIBRARYDIALOG_H
#define EDITFlatInspectionLIBRARYDIALOG_H

#include <QDialog>
#include "XFlatInspection.h"
#include "XFlatInspectionLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditFlatInspectionLibraryDialog;
}
class	GeneralLibFolderForm;
class AlgorithmLibraryLevelContainer;

class EditFlatInspectionLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditFlatInspectionLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditFlatInspectionLibraryDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;

	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	FlatInspectionBase	*GetFlatInspectionBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_toolButtonPickup_clicked();
    void on_toolButtonInspect_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_doubleSpinBoxSelfSearch_valueChanged(double arg1);
    void on_toolButtonExplain_clicked();
    void on_EditAreaSearchX_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchX_valueChanged(double arg1);
    void on_EditAreaSearchY_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchY_valueChanged(double arg1);

    void on_EditOKDotB_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotB_valueChanged(double arg1);
    void on_EditOKDotN_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotN_valueChanged(double arg1);

private:
    Ui::EditFlatInspectionLibraryDialog *ui;
};

#endif // EDITFlatInspectionLIBRARYDIALOG_H