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

#ifndef PROPERTYSTATISTICBLOCKFORM_H
#define PROPERTYSTATISTICBLOCKFORM_H

#include <QWidget>
#include <QTabBar>
#include "ui_PropertyStatisticBlockForm.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "XStandardPropertyForm.h"

class PropertyStatisticBlockForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyStatisticBlockForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyStatisticBlockForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual	void	StartPage(void)		override;
private:
	Ui::PropertyStatisticBlockFormClass ui;
	//StatisticBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	StatisticBlockBase	*GetStatisticBlockBase(void);
	QTabBar	TabBarStatisticBlockOnMouse;

	struct	StatisticBlockItemWithPageLayer{
		StatisticBlockItem	*StatisticBlockInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	StatisticBlockItemWithPageLayer	BInfo[100];
	void		ShowBlockInfoList(void);
	void		ShowTab(void);
	GUIFormBase	*GetImageControlToolsPointer(void);

	NPListPack<StatisticBlockInfoList>	StatisticBlockInfos;


private slots:
	void on_tableWidgetBlockInfo_cellClicked(int,int);
	void on_tableWidgetGeneratedLibList_itemDoubleClicked(QTableWidgetItem*);
	void on_tableWidgetLibList_cellDoubleClicked(int,int);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_tableWidgetGeneratedLibList_cellDoubleClicked(int,int);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_pushButtonEditLibFolder_clicked();
	void on_toolButtonCreateBlock_clicked();
	void on_toolButtonLibrary_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_pushButtonEditLibrary_clicked();
	void	TabBarBlockOnMouseChanged(int);
};

#endif // PROPERTYSTATISTICBLOCKFORM_H