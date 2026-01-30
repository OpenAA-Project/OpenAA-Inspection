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

#ifndef CREATEMANUALThinMetalFORM_H
#define CREATEMANUALThinMetalFORM_H

#include <QDialog>
#include "XThinMetal.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualThinMetalForm;
}
class	GeneralLibFolderForm;
class	ThinMetalLibrary;
class	AlgorithmLibraryLevelContainer;

class CreateManualThinMetalForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
 	int	SelectedLibID;   
public:
    explicit CreateManualThinMetalForm(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualThinMetalForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	ThinMetalItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::CreateManualThinMetalForm *ui;

	void	GetDataFromWindow(ThinMetalItem &data);
	AlgorithmLibraryLevelContainer	*LLib;
	int				ThinMetalLibID;
};

#endif // CREATEMANUALThinMetalFORM_H