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


#ifndef PROPERTYAUTOMASKINGPIFORM_H
#define PROPERTYAUTOMASKINGPIFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoMaskingPIForm.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPropertyAutoMaskingPIPacket.h"

class	GeneralLibFolderForm;

class PropertyAutoMaskingPIForm : public GUIFormBase
{
	Q_OBJECT
	AutoMaskingPIListForPacketPack	MaskInfo;
public:
	PropertyAutoMaskingPIForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAutoMaskingPIForm();
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private:
	Ui::PropertyAutoMaskingPIFormClass ui;
	void	ShowAreaGrid(void);

	AutoMaskingPIBase	*GetAutoMaskingPIBase(void);

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//AutoMaskingPILibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_toolButtonCompositeMask_clicked();
	void on_toolButtonIneffectiveMask_clicked();
	void on_toolButtonAutoMask_clicked();
	void on_pushButtonGenerateDefault_clicked();
	void on_pushButtonGenerateLib_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_toolButtonEffectiveMask_clicked();
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // PROPERTYAUTOMASKINGPIFORM_H