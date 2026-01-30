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

#pragma once

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include "LightUnitStruct.h"
#include "LightDeviceStruct.h"
#include "DeviceStruct.h"
#include <QTcpSocket>

#define	LEDControllerPort	12777
#define	MaxPatternCount		64

class	LEDControl16KDSBeltDialog;

class	LEDControl16KDSBeltPanel : public LightDLLBaseClass
{
	Q_OBJECT

	bool	Opened;
	QString Param;
	QTcpSocket	Sock;
	QString		AccessIPAddress;
	int			AccessPort;
	QMutex		AccessHID;
	bool		Received;

	unsigned char	ReceivedDipSW;
	unsigned char	ReceivedCmd;
	unsigned short	ReceivedLen;
	BYTE			*ReceivedData;
	int				ReceivedMaxLen;
	LEDControl16KDSBeltDialog	*GIOForm;

	static	QString	DefFileName;
	static	QString	DefaultFileName;

public:
	struct  TimingData	*TimingDim;
	int		AllocTimingDim;
	int		WPointTiming;

public:
	
    LightBoard  BoardData[MaxBoardCount];
    int32		BoardCount;

    int			UsageLines;
    struct      LightLineUnit	LineData[DimCountOfLineData];

	struct	KDSBeltPIOStruct		GIOStructData;

	QString		VersionStr;

	int	CurrentPattern;

	LEDControl16KDSBeltPanel(LayersBase *base ,const QString &LightParamStr);
	~LEDControl16KDSBeltPanel(void);

	bool	Initial(bool OutputMode);
	bool	Open(void);
	bool	Close(void);

	void	GetVersion(void);
	void	Transfer(int PatternNumber,QProgressBar *Bar);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

	bool	SaveDef(QIODevice *f);
	bool	LoadDef(QIODevice *f);
	bool	LoadDef(void);
	bool	SaveDef(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	bool	SaveDefault(void);
	bool	LoadDefault(void);

	bool	SetOnOff(bool OnMode);

	bool	GetPatternOnOff		(int UnitNumber ,int BoardNumber);					//Into DefBuffer
	bool	SetPatternOnOff		(int UnitNumber ,int BoardNumber);					//From DefBuffer

	virtual	bool	ShowSettingDialog(void)					override;

	bool	LoadInputData(int BoardNumber);

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

	bool	WriteRegister(BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short DataLen);
	bool	ReadRegister (BYTE DipSW,BYTE Cmd ,BYTE Data[] ,unsigned short SendDataLen 
						,BYTE &RecCmd ,int &ReceivedByte ,int MaxDataLen
						,int WaitingMilisec=2000);

	bool	SendGio(void);
	bool	RequireGio(void);


private slots:
	void    SlotReadyRead();
};
