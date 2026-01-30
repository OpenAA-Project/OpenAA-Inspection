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

#ifndef PROPERTYSHIFTMARKFORM_H
#define PROPERTYSHIFTMARKFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XShiftMark.h"
#include "XStandardPropertyForm.h"
#include "XPropertyShiftMarkPacket.h"

namespace Ui {
class PropertyShiftMarkForm;
}

class	ShiftMarkItem;
class	ShiftMarkBase;
class	AlgorithmLibraryLevelContainer;

class PropertyShiftMarkForm : public GUIFormBase ,public StandardPropertyForm
{
    Q_OBJECT


	ShiftMarkListForPacketPack	ListInfo;
	ShiftMarkListForPacket		**LTable;
    int                         LTableCount;
public:
    explicit PropertyShiftMarkForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyShiftMarkForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 

	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonEditLibrary_clicked();
    void on_toolButtonAddLine_clicked();
    void on_toolButtonAddEdge_clicked();
    void on_toolButtonAddMark_clicked();
    void on_pushButtonShowMarkRotation_clicked();

private:
    Ui::PropertyShiftMarkForm *ui;

	ShiftMarkBase	*GetShiftMarkBase(void);
	AlgorithmLibraryLevelContainer		*LLib;
	int				LibType;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	bool	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	void	ShowListGrid(void);
};

#endif // PROPERTYSHIFTMARKFORM_H