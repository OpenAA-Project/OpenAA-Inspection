/*
 * Copyright (C) 2022
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

#ifndef INTEGRATIONCHANGEPHASEFORM_H
#define INTEGRATIONCHANGEPHASEFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "mtPushButtonColored.h"
#include "XSwitchPhase.h"

namespace Ui {
class IntegrationChangePhaseForm;
}

class	ChangePhaseButton : public mtPushButtonColored
{
    Q_OBJECT
public:
	int		ID;

	ChangePhaseButton(int id ,const QColor &col ,QWidget * parent=0);

private slots:
	void	SlotClicked();

signals:
	void	SignalClicked(int id);
};

class	ChangePhaseButtonEnabler :  public ButtonRightClickEnabler
{
    Q_OBJECT
public:
	ChangePhaseButton	*Button;

	ChangePhaseButtonEnabler(ChangePhaseButton *button);

private slots:
	void	SlotDoubleClicked(QAbstractButton *obj);

signals:
	void	SignalDoubleClicked(int id);
};


class	EnableExecuteButton : public QPushButton
{
	Q_OBJECT
public:
	int	Phase;

	EnableExecuteButton(int phase);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int phase);
};

class IntegrationChangePhaseForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	ChangePhaseButtonEnabler	**PhaseButtons;
	int		AllocatedPhaseNumb;
    
public:
	int		MachineCode;
	bool	ShowEnable;
	QString	AlgoRootToShowEnable;
	QString	AlgoNameToShowEnable;

    explicit IntegrationChangePhaseForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationChangePhaseForm();
    
	virtual void	Prepare(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;

private slots:
    void on_pushButtonAddPhase_clicked();
    void on_pushButtonSubPhase_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
	void	SlotClicked(int id);
	void	SlotDoubleClicked(int id);
	void	ResizeAction();
    void on_pushButtonGetCurrent_clicked();
	void	SlotEnableExecuteClicked(int phase);
signals:
	void	SignalChangePhase(int NewPhase);

private:
    Ui::IntegrationChangePhaseForm *ui;

	void ShowList(void);
	void ShowCurrentPhase(void);
};

//===========================================================================

class	IntegrationReqCurrentPhase: public IntegrationCmdPacketBase
{
public:

	IntegrationReqCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckCurrentPhase: public IntegrationCmdPacketBase
{
public:
	int	CurrentPhase;
	PhaseItemResultContainer	SwitchPhaseValues;

	IntegrationAckCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	IntegrationReqEnableExecute : public IntegrationCmdPacketBase
{
public:
	QString	AlgoRootToShowEnable;
	QString	AlgoNameToShowEnable;

	IntegrationReqEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckEnableExecute : public IntegrationCmdPacketBase
{
public:
	BoolList	EnableExecute;

	IntegrationAckEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationSendEnableExecute : public IntegrationCmdPacketBase
{
public:
	QString	AlgoRootToShowEnable;
	QString	AlgoNameToShowEnable;
	BoolList	EnableExecute;

	IntegrationSendEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqEnableExecute : public GUICmdPacketBase
{
public:
	QString	AlgoRootToShowEnable;
	QString	AlgoNameToShowEnable;
	GUICmdReqEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckEnableExecute : public GUICmdPacketBase
{
public:
	BoolList	EnableExecute;

	GUICmdAckEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSendEnableExecute : public GUICmdPacketBase
{
public:
	QString	AlgoRootToShowEnable;
	QString	AlgoNameToShowEnable;
	BoolList	EnableExecute;

	GUICmdSendEnableExecute(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // INTEGRATIONCHANGEPHASEFORM_H