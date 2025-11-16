/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureLineMove\PropertyMeasureLineMoveForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYMEASURELINEMOVEFORM_H
#define PROPERTYMEASURELINEMOVEFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMeasureLineMoveForm.h"
#include "XGUIPacketForDLL.h"
#include "XColorSpace.h"
#include "XVector.h"
#include "ShowRGBCube.h"
#include "XMeasureLineMove.h"
#include "XStandardPropertyForm.h"

class PropertyMeasureLineMoveForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

	LineMoveListForPacketPack	ListInfo;
	LineMoveListForPacket		**LTable;
public:
	PropertyMeasureLineMoveForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMeasureLineMoveForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	MeasureLineMoveBase	*GetMeasureLineMoveBase(void);
	void	ShowListGrid(void);

	ShowRGBSpace	ColorGenerator;

	int		AlignmentPoint;
	bool	AlignmentImage;
	VectorItemDouble	ImagePoint[3];
	VectorItemDouble	ItemPoint[3];


private:
	Ui::PropertyMeasureLineMoveFormClass ui;

private slots:
	void on_pushButtonExecuteAlign_clicked();
	void on_pushButtonLoadCSV_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonUpdate_clicked();
	void on_pushButtonCreateNew_clicked();
	void on_pushButtonEditLibFolder_clicked();
        void on_pushButtonEditLibrary_clicked();
        void on_toolButtonModeLine_clicked();
        void on_toolButtonModeArc_clicked();
        void on_toolButtonModeDistance_clicked();
        void on_tableWidgetLineMoveList_clicked(const QModelIndex &index);
        void on_tableWidgetLineMoveList_doubleClicked(const QModelIndex &index);
        void on_toolButtonModeMark_clicked();
        void on_checkBoxSelect1_clicked();
        void on_checkBoxSelect2_clicked();
};

#endif // PROPERTYMEASURELINEMOVEFORM_H
