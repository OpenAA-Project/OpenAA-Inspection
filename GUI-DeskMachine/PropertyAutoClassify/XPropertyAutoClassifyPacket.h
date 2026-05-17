/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\PropertyAutoClassify\XPropertyAutoClassifyPacketPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYAUTOCLASSIFYPACKET_H)
#define	XPROPERTYAUTOCLASSIFYPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAutoClassify.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"


class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//AutoClassifyLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList				LayerList;

	GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdPickupTestList(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdTestClear: public GUICmdPacketBase
{
public:
	GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdGenerateAreas : public GUICmdPacketBase
{
public:
	IntList			LibList;
	IntList			LayerList;

	GUICmdGenerateAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateAreas(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdAutoClassifyDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedArea
	}Mode;

	CmdAutoClassifyDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	AutoClassifyImagePanel;
class	CmdAutoClassifyDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	AutoClassifyImagePanel	*ImagePanelPoint;

	CmdAutoClassifyDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdAutoClassifyShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	enum{
		_Block 	}Mode;

	CmdAutoClassifyShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	AutoClassifyDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdAutoClassifyDrawModePacket::DrawMode	Mode;

	QColor		ColorPickup;
	QColor		AreaColor0;
	QColor		AreaColor1;
	QColor		AreaColor2;
	QColor		AreaColor3;
	QColor		AreaColor4;
	QColor		AreaColor5;
	QColor		AreaColor6;
	QColor		AreaColor7;

	AutoClassifyDrawAttr(void):ServiceForLayers(NULL){}
	AutoClassifyDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	AutoClassifyDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &areaColor0
				, QColor &areaColor1
				, QColor &areaColor2
				, QColor &areaColor3
				, QColor &areaColor4
				, QColor &areaColor5
				, QColor &areaColor6
				, QColor &areaColor7);

	void	Initial(void);

	AutoClassifyDrawAttr	&operator=(AutoClassifyDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	AutoClassifyDrawAttr	&AutoClassifyDrawAttr::operator=(AutoClassifyDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	AreaColor0	=src.AreaColor0;
	AreaColor1	=src.AreaColor1;
	AreaColor2	=src.AreaColor2;
	AreaColor3	=src.AreaColor3;
	AreaColor4	=src.AreaColor4;
	AreaColor5	=src.AreaColor5;
	AreaColor6	=src.AreaColor6;
	AreaColor7	=src.AreaColor7;
	return *this;
}
inline	bool	AutoClassifyDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	AutoClassifyDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}


class	AutoClassifyItem;
class	GUICmdSendAddManualArea : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdSendAddManualArea(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendModifySelectedArea : public GUICmdPacketBase
{
public:
	QByteArray	BItem;

	GUICmdSendModifySelectedArea(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdExecuteMouseLDown: public GUIDirectMessage
{
public:
	IntList	PageList;
	IntList	IDList;

	CmdExecuteMouseLDown(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdReqSelectedAutoClassifyItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedAutoClassifyItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedAutoClassifyItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedAutoClassifyItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================


class	GUICmdReqAreaInfoList : public GUICmdPacketBase
{
public:
	GUICmdReqAreaInfoList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAreaInfoList : public GUICmdPacketBase
{
public:
	NPListPack<AreaInfoList>	AreaInfos;

	GUICmdSendAreaInfoList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	Make(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqSetButtonMode : public GUICmdPacketBase
{
public:
	enum	ButtonMode
	{
		_LibraryTest	=1
		,_CreateBlock	=2
	}Mode;
	QString	InstForm;

	GUICmdReqSetButtonMode(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqSetButtonMode : public GUIDirectMessage
{
public:
	GUICmdReqSetButtonMode::ButtonMode	Mode;

	CmdReqSetButtonMode(LayersBase *base):GUIDirectMessage(base){}
};


#endif
