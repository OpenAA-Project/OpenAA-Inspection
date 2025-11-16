/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v52\GeneralSource\XGUIInterfaceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XGUIInterfaceDLL_H)
#define	XGUIInterfaceDLL_H

#include <QObject>
#include "NList.h"
#include <QString>
#include <QStringList>
#include <QIODevice>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include <QtGui>
#include <QVariant>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XMacroFunction.h"
#include "XGUIFormBase.h"
#include "XDLLManager.h"
#include "XSingleExecuteBySocket.h"

class	StructList;
class	GUIInitializer;
class	ErrorCodeList;
class	GUIFastComm;
class	ShowLoadingDLLForm;
class	IntegrationCommPack;
class	GUIIntegrationCommPack;
class	LanguageStringList;

class	GuiDLLItem : public NPList<GuiDLLItem> ,public DLLManager,public ServiceForLayers ,public DLLMacroFunc
{
	QLibrary 	DllLib;

	bool		(*DLL_GetName)(QString &Root ,QString &Name);
	WORD		(*DLL_GetDLLType)(void);
	WORD		(*DLL_GetVersion)(void);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguageCommon)(LanguagePackage &Pkg ,int LanguageCode);
	void		(*DLL_SetLanguage)		(LanguagePackage &Pkg ,int LanguageCode);
	void		(*DLL_Initial)(LayersBase *Base);
	void		(*DLL_Close)(void);
	void		(*DLL_InitialQt)(QApplication *AppBase);
	bool		(*DLL_ReceivePacket)(LayersBase *Base,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);
	bool		(*DLL_ReceivePacketDirectComm)(LayersBase *Base,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);
	bool		(*DLL_ReceiveIntegrationPacket)(LayersBase *Base,int32 cmd ,int32 SlaveNo ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);

	GUIFormBase	*(*DLL_CreateInstance)(LayersBase *Base ,QWidget *parent);
	void		(*DLL_DeleteInstance)(GUIFormBase *);
	int32		(*DLL_GetPropertyString)(void	*Instance ,struct	PropertyClass Data[] ,WORD maxDataDim);
	void		(*DLL_GetGuiAdditionalDatabase)(NPListPack<GuiAdditionalDatabase> &Data);

	QIcon		*(*DLL_GetIcon)(void);
	void		(*DLL_EntryAlgorithm)(LayersBase *Base,RootNameListContainer &List);
	void		(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	int32		(*DLL_RegistMacroFunction)(ExportFuncForMacro Functions[],int MaxBuffer);

	QIcon		*icondata;

public:
	QString		FileName;
	QString		RootName;
	QString		Name;
	QString		Explain;
	QString		Copyright;
	QString		Error;
	bool		UsedInGUI;

	explicit	GuiDLLItem(LayersBase *Base);
	~GuiDLLItem(void);

	bool	LoadDLL(LayersBase *Base,const QString &filename ,DWORD &ErrorCode);
	bool	Close(void);
	bool	SetLanguageCode(int LanguageCode);
	bool	CheckSystemVersion(QStringList &Str);
	virtual	void	EntryAlgorithm		(RootNameListContainer &List);
	virtual	void	AssociateComponent	(ComponentListContainer &List);
	WORD	GetVersion(void);
	QString	GetFileName(void){	return FileName;	}
	QString		GetDLLRoot(void)		{	return RootName;		}
	QString		GetDLLName(void)		{	return Name;			}
	const QString	GetExplain(void)	{	return Explain;			}

	GUIFormBase	*CreateInstance(LayersBase *Base,QWidget *parent);
	void	DeleteInstance(GUIFormBase *Instance)	{	if(DLL_DeleteInstance!=NULL)	DLL_DeleteInstance(Instance);	}
	int32	GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD maxDataDim)
											{	return((DLL_GetPropertyString!=NULL)?DLL_GetPropertyString(Instance ,Data ,maxDataDim):NULL);	}
	QIcon	GetIcon(void);
	bool	ReceivePacket(int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
						,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData)
			{	return(DLL_ReceivePacket(GetLayersBase(),cmd ,globalPage ,EmitterRoot ,EmitterName ,ClassName,buff,IDForUndo,ErrorData));	}
	bool	ReceivePacketDirectComm(int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
						,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData)
			{	return(DLL_ReceivePacketDirectComm(GetLayersBase(),cmd ,globalPage ,EmitterRoot ,EmitterName ,ClassName,buff,IDForUndo,ErrorData));	}
	bool	ReceiveIntegrationPacket(int32 cmd ,int32 SlaveNo ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
						,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData)
			{	if(DLL_ReceiveIntegrationPacket==NULL)	return false;
				return(DLL_ReceiveIntegrationPacket(GetLayersBase(),cmd ,SlaveNo ,EmitterRoot ,EmitterName ,ClassName,buff,IDForUndo,ErrorData));
			}

	bool	InitialAdditionalFieldFromGUI(QSqlDatabase &DB);
	bool	CreateExcludedList(ExcludedListPack &EList);

	virtual	void	GetExportFunctions(QStringList &Str)	override;
	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)	override;

	virtual	bool	SetLanguage(GUIFormBase *Instance ,const QString &MemberName,LanguageStringList *s);
	virtual	void	PickupGUILanguage(GUIFormBase *Handle ,GUILanguageContainer &GUILanguageContainerInst);
};


class	GuiDLLItemContainer : public NPListPack<GuiDLLItem>
{
public:
	GuiDLLItemContainer(void){}

	bool	Close(void);
};

//===========================================
class	MouseEater : public QObject
{
	GUIFormBase	*Parent;
public:
	explicit	MouseEater(GUIFormBase *parent){	Parent=parent;}
protected:
	bool eventFilter(QObject *obj, QEvent *event);
};


#endif