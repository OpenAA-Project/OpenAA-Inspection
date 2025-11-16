#if	!defined(XPrinterManager_H)
#define	XPrinterManager_H

#include <QtGui>
//#include <QSqlDatabase>
#include <QLibrary>
#include <QMutex>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "NList.h"
#include "XDLLManager.h"
#include "XGUIFormBase.h"

class	PrinterDLLBaseClass;

class	PrinterClass : public NPList<PrinterClass> ,public QObject ,public DLLManager ,public ServiceForLayers
{
	QLibrary 	DllLib;

	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	WORD	(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool	(*DLL_CheckCopyright)(QString &CopyrightString);
	void	(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	PrinterDLLBaseClass	*(*DLL_Initial)(LayersBase *base,const QString &LightParamStr);
	void	(*DLL_SetLayersBasePointer)(PrinterDLLBaseClass *handle ,LayersBase *base);
	bool	(*DLL_Close)(PrinterDLLBaseClass *handle);
	bool	(*DLL_Load)(PrinterDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_Save)(PrinterDLLBaseClass *handle ,QIODevice &str);
	bool	(*DLL_ShowSetting)(PrinterDLLBaseClass *handle, QWidget *parent);

	QString		PrinterFileName;
	PrinterDLLBaseClass		*Handle;
	QString		DLLName;
	QString		Copyright;
	QMutex		MutexPrinter;
	bool		LoadedDone;
public:
	PrinterClass(LayersBase *base);
	virtual	~PrinterClass(void);

	bool	Initial(const QString &DLLFileName ,const QString Parameter 
					,int32 &ErrorCode);
	bool	InitialStraightPath(const QString &DLLFileName ,const QString Parameter 
								,int32 &ErrorCode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);
	bool	IsPrinterDLL(void);
	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	bool	ShowSetting(QWidget *parent);
	PrinterDLLBaseClass	*GetHandle(void)	{	return Handle;	}

	bool	LoadDLL(const QString &filename ,int32 &ErrorCode);
	bool	LoadDLLLibrary(int32 &ErrorCode,const QString &FileName,QString Parameter);

	void	GetExportFunctions(QStringList &Str);
	QString	GetFileName(void){	return PrinterFileName;	}
	QString	GetCopyright(void);
	QString	GetName(void);
	WORD	GetVersion(void);
	WORD	GetDLLType(void);
	const QString	GetExplain(void);
	QString	GetDLLName(void)	{	return DLLName;		}

	void	TransmitDirectly(GUIDirectMessage *packet);

	bool	IsLoadedDone(void)		{	return LoadedDone;	}
	void	SetLoadedDone(bool b)	{	LoadedDone=b;		}
};

class	PrinterClassPack : public NPListPack<PrinterClass>,public ServiceForLayers
{
public:
	PrinterClassPack(LayersBase *base):ServiceForLayers(base){}

	int	SearchAddDLL(int32 &ErrorCode);

	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);
	bool	Initial(int32 &ErrorCode);
	void	LoopOnIdle(void);
	PrinterClass	*Search(const QString &DLLName);

	bool	Load(QIODevice *str);
	bool	Save(QIODevice *str);

	void	TransmitDirectly(GUIDirectMessage *packet);
};

#endif