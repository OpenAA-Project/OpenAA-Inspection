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

#ifndef PROPERTYALIGNMENTBLOCKFORM_H
#define PROPERTYALIGNMENTBLOCKFORM_H

#include "XGUIFormBase.h"
#include "XAlignmentBlock.h"
#include "XAlignmentBlockLibrary.h"
#include "XAlignmentBlockCommon.h"
#include "XStandardPropertyForm.h"
#include <QModelIndex>

namespace Ui {
class PropertyAlignmentBlockForm;
}

class PropertyAlignmentBlockForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyAlignmentBlockForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyAlignmentBlockForm();

    virtual	void	BuildForShow(void)	    override;
 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
    virtual	void	SetTargetPage(int page) override;

private slots:
    void on_pushButtonAutoGenerate_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();

    void on_tableWidget_itemSelectionChanged();

private:
    Ui::PropertyAlignmentBlockForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

    AlignmentBlockItemListContainer BlockItems;

	AlignmentBlockBase	*GetAlignmentBlockBase(void);
    void                ShowItemList(void);

};

#endif // PROPERTYALIGNMENTBLOCKFORM_H