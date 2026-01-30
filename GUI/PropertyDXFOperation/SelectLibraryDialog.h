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

#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmBase.h"
#include "NList.h"
#include "XAlgorithmLibrary.h"
#include "XDXFOperation.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	PropertyDXFOperationForm;

class	LogicDLLPointer : public NPList<LogicDLLPointer>
{
public:
	LogicDLL *Pointer;

	LogicDLLPointer(LogicDLL *p):Pointer(p){}
};

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
  
	PropertyDXFOperationForm	*Parent;
	NPListPack<LogicDLLPointer>		LogicDLLPointerContainer;
public:
    explicit SelectLibraryDialog(DWORD AlgorithmType ,PropertyDXFOperationForm *p,LayersBase *base, QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	AlgorithmLibraryListContainer	Selected;

private slots:
    void on_tableWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	int								CurrentLibType;
	int								CurrentLibFolderID;
	AlgorithmLibraryListContainer	LibIDListSelect;

	void	ShowFolder(int LibType);

};

#endif // SELECTLIBRARYDIALOG_H