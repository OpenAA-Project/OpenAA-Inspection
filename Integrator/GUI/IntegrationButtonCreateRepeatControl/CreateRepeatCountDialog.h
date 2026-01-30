/*
 * Copyright (C) 2025
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

#ifndef CREATEREPEATCOUNTDIALOG_H
#define CREATEREPEATCOUNTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class CreateRepeatCountDialog;
}

class CreateRepeatCountDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit CreateRepeatCountDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~CreateRepeatCountDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreateRepeatCountDialog *ui;
};

//==============================================================================
class	IntegrationCmdReqRepeatCount: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationCmdAckRepeatCount: public IntegrationCmdPacketBase
{
public:
	int	RepeatCount;

	IntegrationCmdAckRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetRepeatCount: public IntegrationCmdPacketBase
{
public:
	int	RepeatCount;

	IntegrationCmdSetRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};

#endif // CREATEREPEATCOUNTDIALOG_H