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

#ifndef PROPERTYAUTOPCBHOLEALIGNERFORM_H
#define PROPERTYAUTOPCBHOLEALIGNERFORM_H

#include "XGUIFormBase.h"
#include "XAutoPCBHoleAligner.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyAutoPCBHoleAlignerForm;
}

class PropertyAutoPCBHoleAlignerForm : public GUIFormBase, public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyAutoPCBHoleAlignerForm(LayersBase* Base, QWidget *parent = 0);
    ~PropertyAutoPCBHoleAlignerForm();
    
    virtual	void	TransmitDirectly(GUIDirectMessage* packet)	override;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_tableWidgetAreaList_clicked(const QModelIndex &index);

    void on_pushButtonEditLibFolder_clicked();

private:
    Ui::PropertyAutoPCBHoleAlignerForm *ui;
    AutoPCBHoleAlignerBase* GetAutoPCBHoleAlignerBase(void);

    void	ShowLibList(void);
    void	ShowSelectedLibList(void);
    void	ShowAreaList(void);
    virtual void	BuildForShow(void)	override;

    //AutoPCBHoleAlignerLibrary* TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
    int						LibType;
    AAHoleInfos				AAInfos;

    AlgorithmLibraryListContainer	LibList;
    AlgorithmLibraryListContainer	SelectedLibList;
    int		LibFolderID;
    virtual	void	SetLibFolder(int LibFolderID, const QString& LinFolderName)	override;
};

#endif // PROPERTYAUTOPCBHOLEALIGNERFORM_H