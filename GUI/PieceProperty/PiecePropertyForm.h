/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceProperty\PiecePropertyForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECEPROPERTYFORM_H
#define PIECEPROPERTYFORM_H

#include "XGUIFormBase.h"
#include "ui_PiecePropertyForm.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QScrollArea>
#include "XGUIPacketForDLL.h"
#include "XFlexArea.h"
#include "XPieceArrange.h"

class	PiecePropertyForm;
class	PieceArrangeItem;


class	QSqlPieceMasterModel : public QSqlTableModel
{
public:
	PiecePropertyForm	*ParentForm;

	QSqlPieceMasterModel(PiecePropertyForm *parentForm ,QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class	QSqlPieceMasterModelAuto : public QSqlTableModel
{
public:
	PiecePropertyForm	*ParentForm;

	QSqlPieceMasterModelAuto(PiecePropertyForm *parentForm ,QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class	AlgorithmToolButton : public QToolButton
{
public:
	QString	DLLRoot;
	QString	DLLName;

	AlgorithmToolButton(QWidget *parent = 0):QToolButton(parent){}
};


class PiecePropertyForm : public GUIFormBase
{
	Q_OBJECT

	QScrollArea			AlgorithmArea;
	QFrame				AlgorithmFrame;
	AlgorithmToolButton	**AlgorithmButtons;
	int					AlgorithmButtonNumb;
	PieceGridContainer	*PieceGridTable;
public:
	PiecePropertyForm(LayersBase *Base ,QWidget *parent = 0);
	~PiecePropertyForm();

	int		CategoryID;
	int		CategoryIDAuto;
	
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	int	GetSelectedMasterCode(void);
	int	GetSelectedMasterCodeAuto(void);
	IntList			AutoSelectedMasterList;

private:
	Ui::PiecePropertyFormClass ui;
	MasterCategoryForm	*MasterCategory;

	MasterCategoryForm	*MasterCategoryAuto;
	QTableView			*MListViewAuto;

	//ListPageIDPack		ListForShow;
	void ShowAutoCurrentGrid(void);
	PieceGridList	*GetPieceGridListFromRow(int Row);

private slots:
	void on_pushButtonAutoExecute_clicked();
	void on_tableWidgetAutoCurrent_doubleClicked(QModelIndex);
	void on_pushButtonPushBask_clicked();
	void on_pushButtonAutoPopLoad_clicked();
	void on_pushButtonExecuteAlignment_clicked();
	void on_pushButtonUpdate_clicked();
	void on_tablePieceArrange_doubleClicked(QModelIndex);
	void on_toolButtonArrange_clicked();
	void on_toolButtonCutPiece_clicked();
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	void	SlotAlgorithmToolBottonClicked(bool checked);

	void	SlotSelectCategoryAuto(int CategoryID ,QString FolderName ,QString Remark);
	void	SlotMListViewAutoClicked ( const QModelIndex & index ) ;
    void on_pushButtonStartAutoSearch_clicked();
    void on_tableWidgetAutoSearch_clicked(const QModelIndex &index);
    void on_pushButtonCopyByAutoSearch_clicked();
    void on_tableViewMList_clicked(const QModelIndex &index);
    void on_tableViewMList_doubleClicked(const QModelIndex &index);
    void on_tablePieceArrange_clicked(const QModelIndex &index);
};

class	GUICmdAddPiece : public GUICmdPacketBase
{
public:
	int			MasterCode;
	FlexArea	Area;
	ReflectionAttrPack	ReflectionData;

	GUICmdAddPiece(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdExecuteAutoAlignment : public GUICmdPacketBase
{
public:
	IntList			AutoSelectedMasterList;

	GUICmdExecuteAutoAlignment(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdUpdateParts : public GUICmdPacketBase
{
public:
	GUICmdUpdateParts(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // PIECEPROPERTYFORM_H
