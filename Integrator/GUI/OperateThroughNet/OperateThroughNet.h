/*
 * Copyright (C) 2020
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

#ifndef OPERATETHROUGHNET_H
#define OPERATETHROUGHNET_H

#include "operatethroughnet_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationTransferEvent;
class	IntegrationReqImageGUIFormBase;
class	IntegrationAckImageGUIFormBase;

class OperateThroughNet :public GUIFormBase,public IntegratorRelation
{
	GUIFormBase	*Target;
	IntegrationTransferEvent		*IntegrationTransferEventPointer		;
	IntegrationReqImageGUIFormBase	*IntegrationReqImageGUIFormBasePointer	;
	IntegrationAckImageGUIFormBase	*IntegrationAckImageGUIFormBasePointer	;
	QImage	*TargetImage;
public:
	QString	TargetGUIRoot;
	QString	TargetGUIName;
	QString	TargetGUIInst;
	int32	TargetSlaveNo;

	OperateThroughNet(LayersBase *Base ,QWidget *parent = 0);
	~OperateThroughNet();

	virtual void	ReadyParam(void) override;
private:
	virtual void paintEvent ( QPaintEvent * event ) override;
	virtual void mouseMoveEvent ( QMouseEvent * event ) override;
	virtual void mousePressEvent ( QMouseEvent * event ) override;
	virtual void mouseReleaseEvent ( QMouseEvent * event ) override;
	virtual void keyPressEvent ( QKeyEvent * event ) override;
	virtual void keyReleaseEvent ( QKeyEvent * event ) override;
};



class	IntegrationTransferEvent : public IntegrationCmdPacketBase
{
public:
	QString	TargetGUIRoot;
	QString	TargetGUIName;
	QString	TargetGUIInst;

	QEvent::Type	EventType;

	Qt::MouseButton		Button;
	Qt::MouseButtons	Buttons;
	int	x;
	int	y;
	int	Key;
	QString	KeyText;
	Qt::KeyboardModifiers	KeyModifiers;

	IntegrationTransferEvent(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};


class	IntegrationReqImageGUIFormBase: public IntegrationCmdPacketBase
{
public:
	QString	TargetGUIRoot;
	QString	TargetGUIName;
	QString	TargetGUIInst;

	IntegrationReqImageGUIFormBase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckImageGUIFormBase: public IntegrationCmdPacketBase
{
public:
	BYTE	*Data;
	int		DatByteCount;
	int		Width;
	int		Height;

	IntegrationAckImageGUIFormBase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	virtual	~IntegrationAckImageGUIFormBase(void);

	void	Allocate(int w ,int h);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};




#endif // OPERATETHROUGHNET_H