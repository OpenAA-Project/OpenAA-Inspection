/*
 * Copyright (C) 2024
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

#ifndef PROPERTYDOTCOLORMATCHINGFORM_H
#define PROPERTYDOTCOLORMATCHINGFORM_H

#include "XGUIFormBase.h"
#include "XDotColorMatching.h"
#include "XDotColorMatchingLibrary.h"
#include "XStandardPropertyForm.h"
#include <QModelIndex>

namespace Ui {
class PropertyDotColorMatchingForm;
}

class	DotColorMatchingItem;
class	DotColorMatchingBase;
class	ItemListForPageContainer;
class	ItemListForm;

class PropertyDotColorMatchingForm : public GUIFormBase ,public StandardPropertyForm
{
    Q_OBJECT

	ItemListForPageContainer	*ItemListForPageData;
	ItemListForm				*ItemListWindow;
public:
    explicit PropertyDotColorMatchingForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyDotColorMatchingForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)		override;
	virtual void	BuildForShow(void)		override;
	virtual void	StartPage	(void)		override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateDotColorMatchings(void);
	void	ShowEditLibrary(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_pushButtonBlockList_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyDotColorMatchingForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	DotColorMatchingBase	*GetDotColorMatchingBase(void);

	struct	DotColorMatchingItemWithPageLayer{
		DotColorMatchingItem	*DotColorMatchingInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	DotColorMatchingItemWithPageLayer	BInfo[100];
	void		ShowDotColorMatchingInfoList(void);
	void		ShowTab(void);
	void		ShowItemList(void);
	FlexArea	GlobalPickupArea;
};

#endif // PROPERTYDOTCOLORMATCHINGFORM_H