/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\PropertyMeasureHoleForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
