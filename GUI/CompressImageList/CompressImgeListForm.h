/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CompressImageList\CompressImgeListForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef COMPRESSIMGELISTFORM_H
#define COMPRESSIMGELISTFORM_H

#include "XGUIFormBase.h"
#include "ui_CompressImgeListForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAutoSaveImage.h"
#include <QLabel>
#include <QScrollArea>


class	IDAndFileNameList;

class	ScrollerImage : public QLabel
{
public:
	ScrollerImage(QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget ):QLabel(parent,f){}
};



class CompressImgeListForm : public GUIFormBase
{
	Q_OBJECT

	QScrollArea	*ScrollArea;
	ScrollerImage	*SImagePanel;
public:
	bool	ModeToDisplayList;

	CompressImgeListForm(LayersBase *Base ,QWidget *parent = 0);
	~CompressImgeListForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;
	
	IDAndFileNameList	**PDim;
	int					ListNumb;
	NPListPack<IDAndFileNameList>	IDAndFileNames;

private:
	Ui::CompressImgeListFormClass ui;

	AutoSaveImageBase	*GetAutoSaveImageBase(void);
	void	SMakeImage(IDAndFileNameList *p);
private slots:
	void on_tableWidget_clicked(const QModelIndex &);
	void on_pushButtonUpdate_clicked();
	void ResizeAction(void);
};

//-----------------------------------------------------------------

class	IDAndFileNameList : public NPList<IDAndFileNameList>
{
public:
	int64	InspectionID;
	int32	LotAutoCount;
	QString	FileName;
	XDateTime FileStamp;
	QLabel	LabelImage;
};

//-----------------------------------------------------------------

class	GUICmdReqFileEntryList : public GUICmdPacketBase
{
public:

	GUICmdReqFileEntryList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckFileEntryList : public GUICmdPacketBase
{
public:
	FileEntryListContainer	FileEntries;

	GUICmdAckFileEntryList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeData(int LocalPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqLoad : public GUICmdPacketBase
{
public:
	int	InspectionID;
	int	LotAutoCount;
	QString	FileName;

	GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLoad : public GUICmdPacketBase
{
public:

	GUICmdAckLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
#endif // COMPRESSIMGELISTFORM_H
