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


#ifndef PROPERTYCOLORBLOCKFORM_H
#define PROPERTYCOLORBLOCKFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyColorBlockForm.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "mtToolButtonColored.h"
#include "XStandardPropertyForm.h"

class PropertyColorBlockForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyColorBlockForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyColorBlockForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private:
	Ui::PropertyColorBlockFormClass ui;

	//ColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	ColorBlockBase	*GetColorBlockBase(void);
	QTabBar	TabBarBlockOnMouse;
	void		ShowLibList(void);
	void		ShowSelectedLibList(void);
	virtual	void		SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	struct	BlockItemWithPage{
		ColorBlockItem	*ColorBlockInfoOnMouse;
		int			Page;
	};

	struct	BlockItemWithPage	BInfo[100];
	void		ShowBlockInfoList(void);
	void		ShowTab(void);

	NPListPack<ColorBlockInfoList>	ColorBlockInfos;
	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;
	FlexArea	GlobalPickupArea;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
	GUIFormBase	*GetImageControlToolsPointer(void);

private slots:
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_tableWidgetBlockInfo_cellClicked(int,int);
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_toolButtonCreateBlock_clicked();
	void on_toolButtonLibrary_clicked();
	void on_pushButtonEditLibFolder_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_ButtonGenerateLibs_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonLibSave_clicked();
	void	TabBarBlockOnMouseChanged(int);
	void on_ToolButton_clicked();
	void	MListSectionClicked ( int logicalIndex );
};

#endif // PROPERTYCOLORBLOCKFORM_H