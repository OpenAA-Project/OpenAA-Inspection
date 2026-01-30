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


#ifndef DISPLAYNGLIST_H
#define DISPLAYNGLIST_H

#include "displaynglist_global.h"
#include <QPushButton>
#include <QTableWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"

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
	virtual	void mousePressEvent ( QMouseEvent * event )	override;
	virtual	void keyPressEvent(QKeyEvent *event)			override;
signals:
	void	SignalClicked();
};

class	DisplayNGList :public GUIFormBase
{
    Q_OBJECT
	
	int							LastSelectedRow;
	NPListPack<ShowingQueue>	ShowingQueueData;
	DWORD	LastTime;
	int		LastRow;
	GUICmdReqNGList		**CmdReq;
	GUICmdSendNGList	**CmdAck;
public:
	int					AllocatedPageCount;
	ErrorGroupPack		***ErrorGroupData;
public:
	int32	WidthLineNumber;
	int32	WidthPhaseNumber;
	int32	WidthPageNumber;
	int32	WidthPosition;
	int32	WidthLocationName;
	int32	WidthCause;
	int32	WidthMessage;
	int32	MinTimToNext;

	NGListWidget	NGList;
	int				PhaseNumb;
	QString			TargetImagePanelName;
	QStringList		TargetImagePanelNames;

	DisplayNGList(LayersBase *Base ,QWidget *parent);
	~DisplayNGList(void);

	virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	SignalOperandInt	*ioEffective;
	SignalOperandInt	*ioNG_X;
	SignalOperandInt	*ioNG_Y;
	SignalOperandInt	*ioNGCount;
	SignalOperandInt	*ioCurrentNG;
	bool				ResetPosition;
//
protected:
//	void mousePressEvent(QMouseEvent *);
	virtual	void keyReleaseEvent ( QKeyEvent * event ) override;

	void	AllocateMemory(void);
	void	ReleaseMemory(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
signals:

private slots:
	void	ResizeAction();
	void	ListItemClicked ( QTableWidgetItem * item );
	void	ListItemSelectionChanged ();
	//void	SlotCurrentCellChanged ( int currentRow, int currentColumn, int previousRow, int previousColumn );
	void	OperandChanged();
	void	SlotClicked ();
	void	SlotChangedPhasePageLayer();
};

class	GUICmdReqNGList : public GUICmdPacketBase
{
public:
	int		ShownInspectionID;
	bool	ShowCause;

	GUICmdReqNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGList : public GUICmdPacketBase
{
public:
	ErrorGroupPack	*ErrorGroupData;

	GUICmdSendNGList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendNGList(void);

	void	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // DISPLAYNGLIST_H