/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\PropertyCategorizedShader\XPropertyCategorizedShaderPacketPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPROPERTYCategorizedShaderPACKET_H)
#define	XPROPERTYCategorizedShaderPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XCategorizedShader.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"



class	CmdCategorizedShaderDrawModePacket : public GUIDirectMessage
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedArea
	}Mode;

	CmdCategorizedShaderDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CategorizedShaderImagePanel;
class	CmdCategorizedShaderDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	CategorizedShaderImagePanel	*ImagePanelPoint;

	CmdCategorizedShaderDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCategorizedShaderShowAttrPacket: public GUIDirectMessage
{
public:
	IntList		LibIDList;
	enum{
		_Block 	}Mode;

	CmdCategorizedShaderShowAttrPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CategorizedShaderDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	CmdCategorizedShaderDrawModePacket::DrawMode	Mode;

	CategorizedShaderDrawAttr(void):ServiceForLayers(NULL){}
	CategorizedShaderDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	CategorizedShaderDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	CategorizedShaderDrawAttr	&operator=(CategorizedShaderDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	CategorizedShaderDrawAttr	&CategorizedShaderDrawAttr::operator=(CategorizedShaderDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	return *this;
}
inline	bool	CategorizedShaderDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	return true;
}
inline	bool	CategorizedShaderDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	return true;
}


class	CategorizedShaderItem;
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

class	GUICmdReqSelectedCategorizedShaderItemAttr : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedCategorizedShaderItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedCategorizedShaderItemAttr : public GUICmdPacketBase
{
public:
	bool		ExistSelected;
	QByteArray	BItem;

	GUICmdSendSelectedCategorizedShaderItemAttr(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	Make(int localPage ,LayersBase *Base);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==========================================================================

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
