/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\PropertyPixelInspectionForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
