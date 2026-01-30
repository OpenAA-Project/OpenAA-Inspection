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


#if	!defined(XPropertyBCRPacket_H)
#define	XPropertyBCRPacket_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XBCRInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	CmdReqBCodeInItem : public GUIDirectMessage
{
public:
	int						ItemID;
	int						CheckType;		//0:Read	1:Quality Check
    double					QuilityGrade;
    BCRGradeListContainer	GradeList;

	CmdReqBCodeInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBCodeInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//--------------------------------------------------------
class	GUICmdReqBCodeList : public GUICmdPacketBase
{
public:
	GUICmdReqBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckBCodeList : public GUICmdPacketBase
{
public:
	BCRContainer	BCode;

	GUICmdAckBCodeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqBCode : public GUIDirectMessage
{
public:
	BCRContainer	GridList;

	CmdReqBCode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBCode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//--------------------------------------------------------

class	GUICmdReqBCodeTest : public GUICmdPacketBase
{
public:
	int		ItemID;
	bool	Mastered;

	GUICmdReqBCodeTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBCodeTest : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		Result;

	GUICmdAckBCodeTest(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//--------------------------------------------------------
class	GUICmdAddBCodeArea : public GUICmdPacketBase
{
public:
	FlexArea		Area;
	int				BCRType;

	int				CheckType;		//0:Read	1:Quality Check
	double			QuilityGrade;
	BCRGradeListContainer	GradeList;
	bool			BarcodeIsOnlyDigit;

	GUICmdAddBCodeArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//--------------------------------------------------------

class	GUICmdReqBCodeInfoByID : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdReqBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBCodeInfoByID : public GUICmdPacketBase
{
public:
	int						BCRType;
	int						CheckType;		//0:Read	1:Quality Check
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	bool					BarcodeIsOnlyDigit;

	GUICmdAckBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetBCodeInfoByID : public GUICmdPacketBase
{
public:
	int						Phase;
	int						ItemID;
	int						BCRType;
	int						CheckType;		//0:Read	1:Quality Check
	double					QuilityGrade;
	BCRGradeListContainer	GradeList;
	bool					BarcodeIsOnlyDigit;

	GUICmdSetBCodeInfoByID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=====================================================================

#endif