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

#ifndef SETTINGDIALOGAUTO_H
#define SETTINGDIALOGAUTO_H

#include <QDialog>
#include "XTypeDef.h"
#include "XIntClass.h"
#include <QString>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialogAuto;
}

class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SetAutoThresholdByHistogramForm;

class SettingDialogAuto : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SetAutoThresholdByHistogramForm *Parent;
public:
    int32   LibType;
    int32   LibID;
    IntList HistID;
    int32   Strength;
	QString	ButtonName;

    explicit SettingDialogAuto(SetAutoThresholdByHistogramForm *p,QWidget *parent = nullptr);
    ~SettingDialogAuto();

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_itemSelectionChanged();
    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);
    void on_listWidgetCurrentUse_doubleClicked(const QModelIndex &index);
    void on_pushButtonUseCurrent_clicked();
    void on_pushButtonReturnCurrent_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void	SlotSelectLibFolderSelect(int libFolderID ,QString FolderName);

private:
    Ui::SettingDialogAuto *ui;

	int								LibFolderID;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryLevelContainer	*LLib;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;

    void ShowHistList(void);
    void ShowUsageHistList(void);
};

#endif // SETTINGDIALOGAUTO_H