/*
 * Copyright (C) 2023
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


#ifndef PROPERTYBLOCKFORM_H
#define PROPERTYBLOCKFORM_H

#include <QWidget>
#include <QTabBar>
#include "ui_PropertyBlockForm.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "XStandardPropertyForm.h"

class	BlockItem;
class	BlockBase;

class PropertyBlockForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    PropertyBlockForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyBlockForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	SetupLibFolder(int LibFolderID,int originalLibFolder) override;

	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateBlocks(void);

	bool	CommandSetOutlineInLib(int LibID,int OutlineDot);
	bool	CommandSetNGSizeInBlock(int LibID,int BlockType,int NGSize);
	bool	CommandSetSearchDotInBlock(int LibID,int SearchDot);

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private:
    Ui::PropertyBlockFormClass ui;

	//BlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
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
	BlockBase	*GetBlockBase(void);
	QTabBar	TabBarBlockOnMouse;

	struct	BlockItemWithPageLayer{
		BlockItem	*BlockInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	BlockItemWithPageLayer	BInfo[100];
	void		ShowBlockInfoList(void);
	void		ShowTab(void);

	NPListPack<BlockInfoList>	BlockInfos;
	FlexArea	GlobalPickupArea;
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_pushButtonEditLibFolder_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_tableWidgetBlockInfo_cellClicked(int,int);
	void on_toolButtonCreateBlock_clicked();
	void on_toolButtonLibrary_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupTest_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonLibSave_clicked();
	void	TabBarBlockOnMouseChanged(int);
	void	MListSectionClicked ( int logicalIndex );
    void on_pushButtonShrink_clicked();
    void on_pushButtonShrinkHalf_clicked();
    void on_pushButtonExpandHalf_clicked();
    void on_toolButtonArea_clicked();
    void on_toolButtonEdge_clicked();
    void on_toolButtonInside_clicked();
    void on_toolButtonDirUp_clicked();
    void on_toolButtonDirRight_clicked();
    void on_toolButtonDirLeft_clicked();
    void on_toolButtonDirBottom_clicked();
    void on_toolButtonSkipSearch_clicked();
    void on_toolButtonBeforeShrink_clicked();
    void on_toolButtonOmitMatchLineArea_clicked();
};
#endif // PROPERTYBLOCKFORM_H