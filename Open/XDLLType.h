/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDLLType.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XDLLTYPE_H)
#define	XDLLTYPE_H

#include "NList.h"
#include <QString>
#include <QStringList>
#include <QColor>

#define	GUILIB_Version	1

#define	ComponentExtName			"dll"

#define	GUILIB_ID					0x0100
#define	DLLAlgorithmMode			0x0001
#define	DLLCameraMode				0x0002
#define	DLLArrangement				0x0003
#define	DLLResultMode				0x0004
#define	DLLLightMode				0x0005
#define	DLLFilterMode				0x0006
#define	DLLGeneralStockerMode		0x0007
#define	DLLExecuteVisualizerMode	0x0008
#define	DLLPIOMode					0x0009
#define	DLLSeqDLLVarMode			0x000A
#define	DLLPQSystemRunner			0x000B
#define	DLLDFSFilterMode			0x000C
#define	DLLPrinterMode				0x000D
#define	DLLResultAnalizerMode		0x000E
#define	DLLHaspMode					0x000F
#define	DLLShadowControl			0x0010
#define	DLLRWDeviceMode				0x0011
#define	DLLRWAlgorithmMode			0x0012
#define	DLLRobotMode				0x0013

#define	DLLModeMask					0x00FF
#define	DLL_ID_RA_ALIGNMENT			0x1000


class	ComponentList : public NPList<ComponentList>
{
public:
	int		DLLType;
	QString	DLLRoot;
	QString	DLLName;

	ComponentList(void);
	ComponentList(const ComponentList &s);
	ComponentList(int dllType,const QString &dllRoot, const QString &dllName);

	ComponentList &operator=(const ComponentList &src);
	bool	operator==(const ComponentList &s)	const;
	bool	operator!=(const ComponentList &s)	const;

	QString	GetPropertyString(void);
};

class	ComponentListContainer : public NPListPack<ComponentList>
{
public:
	ComponentListContainer(void);

	ComponentListContainer	&operator=(const ComponentListContainer &src);
	ComponentListContainer	&operator+=(const ComponentListContainer &src);
	void	Add(int	DLLType,const QString &Root ,const QString &Name);
	void	Merge(const ComponentList &s);

	void	GetPropertyStringList(QStringList &Str);
};

//-------------------------------------------------------------------------

class DetailResultValueList : public NPList<DetailResultValueList>
{
	enum _ResultType
	{
		 _ResultTypeNone		=0
		,_ResultTypeBool		=1
		,_ResultTypeInt			=2
		,_ResultTypeULong		=3
		,_ResultTypeDouble		=4
		,_ResultTypeQString		=5
	};
	_ResultType	ResultType;
public:
	QString			MessageString;
	bool			ResultValueBool;
	int				ResultValueInt;
	unsigned long	ResultValueULong;
	double			ResultValueDouble;
	QString			ResultValueString;

	DetailResultValueList(void);
	DetailResultValueList(const DetailResultValueList &src);

	void	SetMessage(const QString &s){	MessageString=s;	}
	void	SetResultValue(bool b)			;
	void	SetResultValue(int d)			;
	void	SetResultValue(unsigned long d)	;
	void	SetResultValue(double d)		;
	void	SetResultValue(const QString &s);

	DetailResultValueList	&operator=(const DetailResultValueList &src);
	QString	GetResultValue(void);
};


class DetailResultInfoList : public NPList<DetailResultInfoList>
{
public:
	QString		MessageString;
	NPListPack<DetailResultValueList>	ResultValueContainer;
	QRgb		NGColor;

	DetailResultInfoList(void);
	DetailResultInfoList(const QString &s);
	DetailResultInfoList(const DetailResultInfoList &src);

	void	SetMessage(const QString &s){	MessageString=s;	}
	void	SetColor(const QRgb &color)	{	NGColor=color;		}

	void	Add(DetailResultValueList *L);
	void	Add(const QString &msg ,bool b);
	void	Add(const QString &msg ,int d);
	void	Add(const QString &msg ,unsigned long d);
	void	Add(const QString &msg ,double d);
	void	Add(const QString &msg ,const QString &s);

	DetailResultInfoList	&operator=(const DetailResultInfoList &src);
	QString	GetInfoString(void);
	QString	GetMessageOnly(void);
	void	GetInfoStringList(QStringList &RetList);
};

class DetailResultInfoListContainer : public NPListPack<DetailResultInfoList>
									,public NPList<DetailResultInfoListContainer>
{
public:
	struct 
	{
		int		LibType;
		int		Phase;
		int		Page;
		int		Layer;
		int		ItemID;
		int		LibID;
		int		PosX,PosY;
	}Data;

	DetailResultInfoListContainer(void);

	DetailResultInfoListContainer	&operator=(const DetailResultInfoListContainer &src);
	DetailResultInfoListContainer	&operator+=(const DetailResultInfoListContainer &src);
	void	GetInfoStringList(QStringList &RetList);
};

class DetailResultInfoListContainerAll :public NPListPack<DetailResultInfoListContainer>
{
public:
	DetailResultInfoListContainerAll(void){}
};

#endif

