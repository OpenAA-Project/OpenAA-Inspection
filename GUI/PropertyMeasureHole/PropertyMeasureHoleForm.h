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

#ifndef PROPERTYMEASUREHOLEFORM_H
#define PROPERTYMEASUREHOLEFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMeasureHoleForm.h"
#include "XGUIPacketForDLL.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XMeasureHole.h"
#include "XStandardPropertyForm.h"

class PropertyMeasureHoleForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyMeasureHoleForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMeasureHoleForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

	//MeasureHoleLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	MeasureHoleBase	*GetMeasureHoleBase(void);

	ShowRGBSpace	ColorGenerator;

private:
	Ui::PropertyMeasureHoleFormClass ui;

private slots:
	void on_pushButtonUpdate_clicked();
	void on_pushButtonCreateNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonEditLibFolder_clicked();
        void on_pushButtonCreateNewMono_clicked();
        void on_pushButtonUpdateMono_clicked();
};



#endif // PROPERTYMEASUREHOLEFORM_H