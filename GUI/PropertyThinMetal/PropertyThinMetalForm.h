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

#ifndef PROPERTYTHINMETALFORM_H
#define PROPERTYTHINMETALFORM_H

#include <QWidget>
#include "XThinMetal.h"
#include "XThinMetalLibrary.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "ShowSampleForm.h"

namespace Ui {
class PropertyThinMetalForm;
}
class	AlgorithmLibraryLevelContainer;

class PropertyThinMetalForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyThinMetalForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyThinMetalForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	StartPage	(void)	override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	//void	GenerateThinMetals(void);

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private slots:
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateArea_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonLibSave_clicked();
	void	MListSectionClicked ( int logicalIndex );

    void on_tableWidgetItems_clicked(const QModelIndex &index);
    void on_tableWidgetItems_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyThinMetalForm *ui;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	ThinMetalBase	*GetThinMetalBase(void);
	QTabBar	TabBarThinMetalOnMouse;

	struct	ThinMetalItemWithPageLayer{
		ThinMetalItem	*ThinMetalInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	ThinMetalItemWithPageLayer	BInfo[100];
	void		ShowThinMetalInfoList(void);

	ThinMetalInfoContainer	ThinMetalInfos;
	FlexArea	GlobalPickupArea;
	ShowSampleForm	*ShowSampleFormInst;
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
};

#endif // PROPERTYTHINMETALFORM_H