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

#ifndef EASYMAKEAVERAGEIMAGEFORM_H
#define EASYMAKEAVERAGEIMAGEFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XMakeAverageImage.h"

namespace Ui {
class EasyMakeAverageImageForm;
}

class EasyMakeAverageImageForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	TargetSlaveNo;	//-1:All


    explicit EasyMakeAverageImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyMakeAverageImageForm();
    
	virtual void	ReadyParam(void)	override;
	virtual void	LeavePage	(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonScan_clicked();
    void on_toolButtonGenerateImage_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
	void	SlotScanningDone	(int SlaveNo,int64 InspectionID);

    void on_toolButtonViewMaster_clicked();
    void on_toolButtonViewLowSide_clicked();
    void on_toolButtonViewHighSide_clicked();
    void on_toolButtonViewVariation_clicked();
    void on_toolButtonViewAverage_clicked();

    void on_toolButtonResetAverage_clicked();
	void	SlotRun(bool pushed);

private:
    Ui::EasyMakeAverageImageForm *ui;
	void	ShowCountList(void);
	void	RedrawImage(void);

};


class	IntegrationCmdStartScan : public IntegrationCmdPacketBase
{
public:
	bool	OnMode;

	IntegrationCmdStartScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationReqScanningCount : public IntegrationCmdPacketBase
{
public:
	IntegrationReqScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
class	IntegrationAckScanningCount : public IntegrationCmdPacketBase
{
public:
	int32	*ScanningCountInPhase	;	
	int32	ScanningCountInPhaseNumb;

	IntegrationAckScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	~IntegrationAckScanningCount(void);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:
};

class	IntegrationClearScanningCount : public IntegrationCmdPacketBase
{
public:
	int	Phase;

	IntegrationClearScanningCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationGenerateAverageImage: public IntegrationCmdPacketBase
{
public:
	IntegrationGenerateAverageImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationResetAverageImage: public IntegrationCmdPacketBase
{
public:
	IntegrationResetAverageImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	CmdReqAverageDrawMode : public GUIDirectMessage
{
public:
	MakeAverageImageDrawAttr::_DrawMode	DrawAttr;
	CmdReqAverageDrawMode(LayersBase *base):GUIDirectMessage(base){}
};


#endif // EASYMAKEAVERAGEIMAGEFORM_H