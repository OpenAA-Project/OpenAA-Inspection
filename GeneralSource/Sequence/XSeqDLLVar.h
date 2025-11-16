#if	!defined(XSeqDLLVar_h)
#define	XSeqDLLVar_h

#include <QString>
#include <QApplication>
#include "XDLLManager.h"
#include "XTypeDef.h"

class	GUIDirectMessage;
class	LayersBase;

class   DLLVarInterface : public DLLManager
{
public:
	WORD	(*DLL_GetDLLType)(void);
	bool	(*DLL_GetName)(QString &str);
	const char	*(*DLL_GetExplain)(void);
	WORD	(*DLL_GetVersion)(void);
	bool	(*DLL_CheckCopyright)(QString &CopyrightString);

    void	( *LGetDLLVersion)(char *buff);
	void *( *DLLInitial)(LayersBase *Base ,const QString &param);
    bool ( *DLLCmd)			(void *handle ,QApplication &,const QString &cmd);
    bool ( *DLLCmdStr)		(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr);
    bool ( *DLLCmdStrInt)	(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr,int *datastr2);
    bool ( *DLLCmdStrRet)	(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr ,QByteArray &Buff);
    bool ( *DLLCmdStrRetInt)(void *handle ,QApplication &,const QString &cmd ,const QByteArray &datastr ,QByteArray &Buff ,int *datastr2);
    bool ( *DLLCmdInt)		(void *handle ,QApplication &,const QString &cmd ,int *datastr);
    bool ( *DLLCmdFloat)	(void *handle ,QApplication &,const QString &cmd ,double *datastr);
    bool ( *DLLCmdInt2)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2);
    bool ( *DLLCmdInt3)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2,int *datastr3);
    bool ( *DLLCmdInt4)		(void *handle ,QApplication &,const QString &cmd ,int *datastr1,int *datastr2,int *datastr3,int *datastr4);
    void ( *DLLClose)		(void *handle);
    void ( *DLLDebugShow)	(void *handle ,QApplication &);
	void ( *DLL_TransmitDirectly)(void *handle ,GUIDirectMessage *packet);
	QLibrary 	DllLib;
	void		*Handle;
  public:
    QString  FileName;
	QString  Param;

    QString  Data;
    QString  VersionStr;


    DLLVarInterface(void);
    ~DLLVarInterface(void);

	bool	IsDLLVarDLL(void)	const;
	bool	LoadDLL(LayersBase *base ,const QString &filename);
    QString	GetDLLVarName(void)	const;
    virtual	void	GetExportFunctions(QStringList &Str)	override;
    
	QString	GetFileName(void)	const;
	void	SetFileName(const QString filename);
	void	SetParam(const QString &param);
	
	QString	GetCopyright(void)	const;
	WORD	GetVersion(void)	const;
	WORD	GetDLLType(void)	const;
	const QString	GetExplain(void)	const;
	
	bool    OpenInitialize(LayersBase *base);
	bool    IsDebugMode(void)	const;
	void    DLLDebug(QApplication *app);
	
	void	TransmitDirectly(GUIDirectMessage *packet);

};



#endif
