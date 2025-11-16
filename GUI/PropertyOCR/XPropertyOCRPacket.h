/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOCR\XPropertyOCRPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPropertyOCRPacket_H)
#define	XPropertyOCRPacket_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XOCRInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"


//--------------------------------------------------------
class	GUICmdReqOCRList : public GUICmdPacketBase
{
public:
	GUICmdReqOCRList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckOCRList : public GUICmdPacketBase
{
public:
	OCRContainer	OCR;

	GUICmdAckOCRList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//--------------------------------------------------------

class	GUICmdReqOCRTest : public GUICmdPacketBase
{
public:
	int		ItemID;
	bool	Mastered;

	GUICmdReqOCRTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckOCRTest : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		Result;
	bool		Matched;

	GUICmdAckOCRTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//--------------------------------------------------------
class	GUICmdAddOCRArea : public GUICmdPacketBase
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	FlexArea		Area;
	QString			ItemName;
	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	GUICmdAddOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------
class	GUICmdUpdateOCRArea : public GUICmdPacketBase
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Mergin;
	ColorLogic	MaskingColor;
	bool		UseColorLogic;
	double		Rotation;

	int				ItemID;
	QString			ItemName;
	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	GUICmdUpdateOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------
class	GUICmdDeleteOCRArea : public GUICmdPacketBase
{
public:
	int				ItemID;

	GUICmdDeleteOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------
class	GUICmdReqOCRItem : public GUICmdPacketBase
{
public:
	int		ItemID;

	GUICmdReqOCRItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckOCRItem : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdAckOCRItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif