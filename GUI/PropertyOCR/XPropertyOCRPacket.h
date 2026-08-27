/*
 * Copyright (C) 2026
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
	QImage		OCRImage;

	GUICmdAckOCRTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//--------------------------------------------------------
class	GUICmdAddOCRArea : public GUICmdPacketBase
{
public:
	int32		Mergin;

	FlexArea	Area;
	QString		ItemName;
	int			RegNumber;
	bool		InspectMatching;
	bool		SaveIntoResult;
	bool		OKByFailingRecognition;
	QStringList	CorrectList;

	int			AngleDegree;
	QString		Patterns;
	bool		TextOneLine;
	bool		Darker;
	int			Layer;
	int			ThresholdBrightness;
	int			ReducedNoiseSize;
	int			ShrinkImage;

	GUICmdAddOCRArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//--------------------------------------------------------
class	GUICmdUpdateOCRArea : public GUICmdPacketBase
{
public:
	int32		Mergin;

	int				ItemID;
	QString			ItemName;
	int				RegNumber;
	bool			InspectMatching;
	bool			SaveIntoResult;
	bool			OKByFailingRecognition;
	QStringList		CorrectList;

	int				AngleDegree;
	QString			Patterns;
	bool			TextOneLine;
	bool			Darker;
	int				Layer;
	int				ThresholdBrightness;
	int				ReducedNoiseSize;
	int				ShrinkImage;

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