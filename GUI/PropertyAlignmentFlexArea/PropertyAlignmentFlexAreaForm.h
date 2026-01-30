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

#ifndef PROPERTYALIGNMENTFLEXAREAFORM_H
#define PROPERTYALIGNMENTFLEXAREAFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentFlexAreaForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "XAlignmentFlexArea.h"
#include "XAlignmentFlexAreaLibrary.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyAlignmentFlexAreaForm;
}

class	ShowMarkListForm;
class	AlgorithmLibraryLevelContainer;

class PropertyAlignmentFlexAreaForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT
    
	AlignmentFlexAreaAreaListPack	AreaList;
	AlignmentFlexAreaInfoListPack	AlignmentFlexAreaInfos;
	AlignmentWholeMatchListPack		WholeMatchInfo;
	AlignmentPointListContainer		CurrentPointList;
public:
    explicit PropertyAlignmentFlexAreaForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentFlexAreaForm();

	virtual	void	Prepare(void) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	BuildForShow(void) override;
	virtual void	SetupLibFolder(int LibFolderID,int originalLibFolder) override;
	virtual	void	ShowInEdit(void) override;
	void	CreateAndShowPointGrid(void);
	virtual void	StartPage	(void) override;

	void	CreateAlignmentArea(FlexArea &area);
	void	CreateAlignmentPoint(FlexArea &area ,int MoveDot);
	void	GenerateAreaFromMask(int Priority,int ItemLibID);
	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	SelectModeType(int ModeType);
	void	CreateAreaInMaskingArea(int priority);
    void	GenerateAlignmentFlexArea(void);

	struct	BlockItemWithPage{
		AlignmentFlexAreaItem	*AlignmentFlexAreaInfoOnMouse;
		int			Page;
	};

private slots:
	void on_pushButtonEditLibrary_clicked();
    void on_ButtonLibSave_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonPickupTest_clicked();
    void on_pushButtonGenerate_clicked();
    void on_pushButtonClearPickup_clicked();
    void on_tableWidgetAlignmentFlexAreaInfo_clicked(const QModelIndex &index);
    void on_pushButtonEditLibFolder_clicked();
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_toolButtonGenerate_clicked();
    void on_toolButtonOutline_clicked();
    void on_toolButtonAlignmrntFlexAreaArea_clicked();
    void on_tableWidgetArea_clicked(const QModelIndex &index);
    void on_tableWidgetArea_doubleClicked(const QModelIndex &index);
    void on_toolButtonWholeMatch_clicked();
    void on_toolButtonMark_clicked();

    void on_tableWidgetWholeMatch_clicked(const QModelIndex &index);
    void on_tableWidgetAlignmentFlexAreaInfo_doubleClicked(const QModelIndex &index);
    void on_toolButtonBaseMatch_clicked();
    void on_tableWidgetBaseMatch_clicked(const QModelIndex &index);
    void on_pushButtonGenerateBaseMatch_clicked();
    void on_pushButtonExecuteBaseMatch_clicked();

    void on_tableWidgetMarkList_clicked(const QModelIndex &index);

private:
    Ui::PropertyAlignmentFlexAreaForm *ui;

	ShowMarkListForm	*ShowMarkListFormInst;
	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowAreaGrid(void);
	void	ShowWholeMatchGrid(void);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	void	DrawBaseMatchList(void);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	AlignmentFlexAreaBase	*GetAlignmentFlexAreaBase(void);

	void		ShowAlignmentFlexAreaInfoList(void);
	void		ShowTab(void);
	GUIFormBase	*GetImagePanel(void);
	void		RepaintImage(void);
	void		ShowPointList(int Page,int AreaID);

	FlexArea	GlobalPickupArea;
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;


};
#endif // PROPERTYALIGNMENTFLEXAREAFORM_H