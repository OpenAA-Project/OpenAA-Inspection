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


#ifndef PROPERTYPIXELINSPECTIONFORM_H
#define PROPERTYPIXELINSPECTIONFORM_H


#include <QTabBar>
#include "XGUIFormBase.h"
#include "ui_PropertyPixelInspectionForm.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPropertyPixelInspectionPacket.h"

class	GeneralLibFolderForm;

class PropertyPixelInspectionForm : public GUIFormBase
{
	Q_OBJECT
	
public:
	PropertyPixelInspectionForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyPixelInspectionForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	QString				ImagePanelName;

private:
	Ui::PropertyPixelInspectionFormClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//PixelInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	AlgorithmLibraryListContainer	LibList;

	PixelInspectionBase	*GetPixelInspectionBase(void);
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);


private slots:
	void	pbClearNewClicked();
	void	pbDeleteClicked();
	void	pbSaveNewClicked();
	void	pbUpdateClicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void	tableWidgetLibListClicked(const QModelIndex &);
};

#endif // PROPERTYPIXELINSPECTIONFORM_H