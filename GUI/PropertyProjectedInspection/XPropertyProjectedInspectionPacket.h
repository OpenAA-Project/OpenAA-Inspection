/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyProjectedInspection\XPropertyProjectedInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPropertyProjectedInspectionPacket_H)
#define	XPropertyProjectedInspectionPacket_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XProjectedInspection.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	ProjectedInspectionImagePanel;
class	CmdProjectedInspectionExecuteDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		LayerList;
	ProjectedInspectionImagePanel	*ImagePanelPoint;

	CmdProjectedInspectionExecuteDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdProjectedInspectionExecuteDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ProjectedInspectionItem;
class	GUICmdSendAddManualProjectedInspection : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualProjectedInspection(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdPickupTestList : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	//ProjectedInspectionLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;

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

class	GUICmdGenerateProjectedInspection : public GUICmdPacketBase
{
public:
	IntList			LibList;
	IntList			LayerList;

	GUICmdGenerateProjectedInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdGenerateProjectedInspection(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif
