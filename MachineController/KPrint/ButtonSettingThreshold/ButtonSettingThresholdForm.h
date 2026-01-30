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

#ifndef BUTTONSETTINGTHRESHOLDFORM_H
#define BUTTONSETTINGTHRESHOLDFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>

namespace Ui {
class ButtonSettingThresholdForm;
}
class	MenuThresholdDialog;
class	IntegrationReqTryInspection;
class	IntegrationAckTryInspection;
class	IntegrationReqThresholdPanelImage;
class	IntegrationAckThresholdPanelImage;
class	PanelShowResultImage;
class	EachThresholdWholeForm;


class ThresholdWholeHistoryList : public NPListSaveLoad<ThresholdWholeHistoryList>
{
public:
	int		LibType;
	int		LibID;
	int		BrightnessDark;
	int		BrightnessLight;
	int		Shift;
	DWORD	OKDotB;
	DWORD	OKLengthB;
	DWORD	OKDotN;
	DWORD	OKLengthN;
	DWORD	RedOKDot;
	DWORD	MultiSpotDot;
	DWORD	MultiSpotCount;
	WORD	AreaSearchX;
	WORD	AreaSearchY;
	WORD	SelfSearch;
	bool	Enabled;
	FlexArea	Area;
	XDateTime	ATime;

	ThresholdWholeHistoryList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class ThresholdWholeHistoryListContainer : public NPListPackSaveLoad<ThresholdWholeHistoryList>
{
public:
	ThresholdWholeHistoryListContainer(void){}

	virtual	ThresholdWholeHistoryList	*Create(void)	{	return new ThresholdWholeHistoryList();	}
};


class ButtonSettingThresholdForm : public GUIFormBase
{
	friend	class	IntegrationReqTryInspection;
	friend	class	IntegrationAckTryInspection;
	friend	class	IntegrationReqThresholdPanelImage;
	friend	class	IntegrationAckThresholdPanelImage;
	friend	class	PanelShowResultImage;
	friend	class	EachThresholdWholeForm;

    Q_OBJECT
    
	MenuThresholdDialog	*Window;

	QImage	TargetImageWithNG;
	BYTE	*TargetImageWithNGBuff;
	int		TargetImageWithNGXLen;
	int		TargetImageWithNGYLen;

public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
		
	ThresholdWholeHistoryListContainer	HistoryContainer;

	explicit ButtonSettingThresholdForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSettingThresholdForm();
    
	virtual	void	Prepare(void)	override;
	virtual void	ReadyParam(void) override;
	void	ShowMenuWindow(void);
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	bool	SaveDataIntoMasterData(void);
	bool	LoadDataFromMasterData(void);

private slots:
    void on_PushButtonThreshold_clicked();
	void	ResizeAction();
	void	SlotShowWindow();
	void	SlotReqDetail(EachMaster *m ,InspectionList *Result, InspectionList *CurrentInspection, NGPoint *RepresentativePoint
						,int Phase ,int Page ,IntList &ItemID);
signals:
	void	SignalShowWindow();

private:
    Ui::ButtonSettingThresholdForm *ui;
};

class	IntegrationClickSettingThresholdForm : public GUIDirectMessage
{
public:
	IntegrationClickSettingThresholdForm(LayersBase *base):GUIDirectMessage(base){}
	IntegrationClickSettingThresholdForm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // BUTTONSETTINGTHRESHOLDFORM_H