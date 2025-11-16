/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAreaFilter\PropertyAreaFilterForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYAREAFILTERFORM_H
#define PROPERTYAREAFILTERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAreaFilterForm.h"
#include "XAreaFilter.h"
#include "XStandardPropertyForm.h"
#include "XAreaFilterPacket.h"

class	GeneralLibFolderForm;

class PropertyAreaFilterForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

	AreaFilterListForPacketPack	ItemListInfo;
public:
	PropertyAreaFilterForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAreaFilterForm();

	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;
private:
	Ui::PropertyAreaFilterFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;

	//AreaFilterLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	AreaFilterBase	*GetAreaFilterBase(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QDoubleValidator qdoublevalidator;

	void SynchronizeModeAndProperty(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	ShowItemGrid(void);

private slots:
	void on_radioButtonTypeLineEmphasize_toggled(bool);
	void on_radioButtonTypeVerticalEmphasize_toggled(bool);
	void on_radioButtonTypePatternInverted_toggled(bool);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_radioButtonTypeLineLargeEnflat_toggled(bool checked);
    void on_radioButtonTypeHorizontalEmphasize_toggled(bool checked);
    void on_tableWidgetItems_clicked(const QModelIndex &index);
    void on_radioButtonTypeDifferential_toggled(bool checked);
};

#endif // PROPERTYAREAFILTERFORM_H
