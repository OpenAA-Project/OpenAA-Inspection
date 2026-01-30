/*
 * Copyright (C) 2024
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

#pragma once

#include "displaynglistcategorized_global.h"
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <QTimer>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XTypeDef.h"

class	SignalOperandInt;
class	DisplayImage;
class	GUICmdReqNGList;
class	GUICmdSendNGList;

class	ShowingQueue : public NPList<ShowingQueue>
{
public:
	DisplayImage	*d;
	int				CPhase;
	int				Cx,Cy;

	ShowingQueue(void){	d=NULL;	}
};

class	NGListWidget : public QTableWidget
{
	Q_OBJECT

public:
	NGListWidget ( QWidget * parent = 0 ) : QTableWidget(parent){}

protected:
	virtual	void mousePressEvent (QMouseEvent * event)	override;
	virtual	void keyPressEvent(QKeyEvent *event)		override;
signals:
	void	SignalClicked();
};

class NGListData : public NPList<NGListData>
{
public:
	int		ShadowLevel ;
	int		ShadowNumber;
	int32	Phase;
	int32	Page;
	int32	CenterXInMaster,CenterYInMaster;
	ErrorGroup	*E;
	QString	Cause;
	QString	Message;

	NGListData(){}

};

class NGListContainer : public NPListPack<NGListData>
{
public:
	int		CategoryID;
	QString	CategoryName;

	NGListContainer(void){}

};
class	ErrorGroupPackWithShadowTree : public ErrorGroupPack ,public NPList<ErrorGroupPackWithShadowTree>
{
public:
	int		ShadowLevel ;
	int		ShadowNumber;

	ErrorGroupPackWithShadowTree(void);

    ErrorGroupPackWithShadowTree  &operator=(const ErrorGroupPackWithShadowTree &src);
	ErrorGroupPackWithShadowTree  &operator=(const ErrorGroupPack &src);
    ErrorGroupPackWithShadowTree  &operator+=(const ErrorGroupPackWithShadowTree &src);
	bool    Load(QIODevice *f,LayersBase *Base);
    bool    Save(QIODevice *f);	
	bool    Save(FileThread *f);	
};

class	ErrorGroupPackWithShadowTreePack : public NPListPack<ErrorGroupPackWithShadowTree>
{
public:
	ErrorGroupPackWithShadowTreePack(void){}

    ErrorGroupPackWithShadowTreePack  &operator=(const ErrorGroupPackWithShadowTreePack &src);
	bool    Load(QIODevice *f,LayersBase *Base);
    bool    Save(QIODevice *f);	
	bool    Save(FileThread *f);	
};


class	DisplayNGListCategorized :public GUIFormBase
{
    Q_OBJECT

	int							LastSelectedRow;
	NPListPack<ShowingQueue>	ShowingQueueData;
	DWORD	LastTime;
	int		LastRow;
	GUICmdReqNGList		**CmdReq;
	GUICmdSendNGList	**CmdAck;
	int					AllocatedPageCount;
	ErrorGroupPackWithShadowTreePack	***ErrorGroupData;
	int				PhaseNumb;

	NGListContainer	NGListContainerDim[100];
	int				ColCount;
	QTimer			TM;
	int64			ShownInspectionID;
public:
	int32	MinTimToNext;
	bool	FirstPointAfterInspection;
	NGListWidget	NGList;

	QString			TargetImagePanelName;
	QStringList		TargetImagePanelNames;

	DisplayNGListCategorized(LayersBase *Base ,QWidget *parent);
	~DisplayNGListCategorized(void);

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	SignalOperandInt	*ioEffective;
	SignalOperandInt	*ioNG_X;
	SignalOperandInt	*ioNG_Y;
	SignalOperandInt	*ioNGCount;
	SignalOperandInt	*ioCurrentNG;
	bool				ResetPosition;
//
protected:
//	void mousePressEvent(QMouseEvent *);
	void keyReleaseEvent ( QKeyEvent * event ) 	override;

	void	AllocateMemory(void);
	void	ReleaseMemory(void);

private slots:
	void	ResizeAction();
	void	ListItemClicked ( QTableWidgetItem * item );
	void	ListItemSelectionChanged ();
	//void	SlotCurrentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn );
	void	OperandChanged();
	void	SlotClicked ();
	void	SlotChangedPhasePageLayer();
	void	SlotTimeout();
};

class	GUICmdReqNGList : public GUICmdPacketBase
{
public:
	int		ShownInspectionID;

	GUICmdReqNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGList : public GUICmdPacketBase
{
public:
	ErrorGroupPackWithShadowTreePack	*ErrorGroupData;

	GUICmdSendNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendNGList(void);

	void	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};