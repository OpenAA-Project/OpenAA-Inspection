/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XGeneralDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XGENERALDIALOG_H)
#define	XGENERALDIALOG_H

#include<QDialog>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	LibFolderForm;

class	GeneralDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	QWidget	*Client;
	QObject	*ClientParent;
	bool DeleteCliInClose;

public:
	GeneralDialog(LayersBase *Base,QWidget *cli ,QWidget * parent,bool _DeleteCliInClose=true);
	/*
	parentをNULLにすると、親子関係がなくなってウインドウを探せなくなるのでデフォルトNULLを廃止
	*/

	~GeneralDialog(void);

	virtual	void closeEvent ( QCloseEvent * event ) 	override;

protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;

private slots:
	void SlotClose();
};

class GeneralLibFolderForm : public QObject
{
	Q_OBJECT

	LibFolderForm	*pLibFolderForm;
public:
	GeneralLibFolderForm(int LibType,LayersBase *base,QWidget *parent);
	~GeneralLibFolderForm();

    int		CreateNewFolder(void);
    int		SetLibType(int libType);
    void	SetCurrentLibFolder(int LibFolderID);
    void	Show(void);
    void	Drop(int FolderParentID ,int LibFolderID , QWidget *w);
    void	FitToFrame(QWidget *ParentFrame);

	void	move(int x,int y);
	void	resize(int w ,int h);
signals:
    void	SelectLibFolder(int LibFolderID ,QString FolderName);
    void	SignalDrop(int FolderParentID ,int LibFolderID , QWidget *w);
private slots:
	void	SlotSelectLibFolder(int,QString s);
	void	SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w);
};

bool	ExeSelectLibFolderDialog(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibFolderID
								 ,QString &RetSelectedFolderName);
bool	ExeSelectLibraryForm(int LibType ,LayersBase * base, QWidget *parent
								 ,int	&RetSelectedLibID
								 ,QString &RetSelectedLibName);

bool	ExeSelectPhasePageLayerDialog(LayersBase *base
									,int &RetSelectPhase
									,int &RetSelectPage
									,int &RetSelectLayer);
#endif