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


#ifndef PROPERTYTRUECOLORBLOCKFORM_H
#define PROPERTYTRUECOLORBLOCKFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyTrueColorBlockForm.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "ShowRGBCube.h"
#include "XStandardPropertyForm.h"

class PropertyTrueColorBlockForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyTrueColorBlockForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyTrueColorBlockForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private:
	//TrueColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowSelectedLibList(void);
	void	ShowLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	TrueColorBlockBase	*GetTrueColorBlockBase(void);
	QTabBar	TabBarBlockOnMouse;

	ShowRGBSpace	ColorGenerator;
	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

	struct	BlockItemWithPageLayer{
		TrueColorBlockItem	*TrueColorBlockInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	BlockItemWithPageLayer	BInfo[100];
	void		ShowBlockInfoList(void);
	void		ShowTab(void);

	NPListPack<TrueColorBlockInfoList>	TrueColorBlockInfos;
	FlexArea	GlobalPickupArea;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private:
	Ui::PropertyTrueColorBlockFormClass ui;

private slots:
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_tableWidgetBlockInfo_clicked(const QModelIndex &);
	void on_pushButtonEditLibrary_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_pushButtonEditLibFolder_clicked();
	void on_toolButtonCreateBlock_clicked();
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_ButtonPickupClearTest_clicked();
	void on_pushButtonGColor_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupTest_clicked();
	void on_toolButtonLibrary_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonLibSave_clicked();
	void	TabBarBlockOnMouseChanged(int);
};

#endif // PROPERTYTRUECOLORBLOCKFORM_H