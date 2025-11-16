/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\PropertyMeasureHoleForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYMEASUREHOLEPOSFORM_H
#define PROPERTYMEASUREHOLEPOSFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMeasureHolePosForm.h"
#include "XGUIPacketForDLL.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XMeasureHolePos.h"
#include "XMeasureHolePosPacket.h"
#include "XStandardPropertyForm.h"

class PropertyMeasureHolePosForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

	HolePosListForPacketPack	ListInfo;
public:
	PropertyMeasureHolePosForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMeasureHolePosForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyMeasureHolePosFormClass ui;

	//MeasureHolePosLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	MeasureHolePosBase	*GetMeasureHolePosBase(void);
	void	ShowListGrid(void);

	ShowRGBSpace	ColorGenerator;

private slots:
	void on_pushButtonNColor_clicked();
	void on_tableWidgetBlockInfo_clicked(const QModelIndex &);
        void on_pushButtonCreateNew_clicked();
        void on_pushButtonUpdate_clicked();
        void on_pushButtonEditLibrary_clicked();
        void on_pushButtonCreateNewMono_clicked();
        void on_pushButtonUpdateMono_clicked();
        void on_pushButtonEditLibFolder_clicked();
        void on_toolButtonArea_clicked();
        void on_toolButtonHole_clicked();
        void on_toolButtonEdge_clicked();
        void on_tableWidgetHoleList_clicked(const QModelIndex &index);
        void on_tableWidgetHoleList_doubleClicked(const QModelIndex &index);
};

#endif // PROPERTYMEASUREHOLEPOSFORM_H
