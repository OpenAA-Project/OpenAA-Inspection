
#include "XSeqDLLVar.h"
#include "XDLLType.h"


DLLVarInterface::DLLVarInterface(void)
{
///    Data=0;	//D-20051026

	DLL_GetDLLType		=NULL;
	DLL_GetName			=NULL;
	DLL_GetExplain		=NULL;
	DLL_GetVersion		=NULL;
	DLL_CheckCopyright	=NULL;

    LGetDLLVersion		=NULL;
	DLLInitial			=NULL;
    DLLCmd				=NULL;
    DLLCmdStr		    =NULL;
    DLLCmdStrInt		=NULL;
    DLLCmdStrRet	    =NULL;
    DLLCmdStrRetInt		=NULL;
    DLLCmdInt			=NULL;
	DLLCmdFloat			=NULL;
    DLLCmdInt2		    =NULL;
	DLLCmdInt3		    =NULL;
	DLLCmdInt4		    =NULL;
	DLLClose			=NULL;
    DLLDebugShow	    =NULL;
	DLL_TransmitDirectly=NULL;
	Handle				=NULL;
}

DLLVarInterface::~DLLVarInterface(void)
{
	if(DLLClose!=NULL){
		DLLClose(Handle);
	}
}

QString	DLLVarInterface::GetFileName(void)	const
{
	return FileName;
}
void	DLLVarInterface::SetFileName(const QString filename)
{
	FileName=filename;
}
void	DLLVarInterface::SetParam(const QString &param)
{
	Param=param;
}

bool    DLLVarInterface::IsDebugMode(void)	const
{
    if(DLLDebugShow!=NULL)
        return(true);
    return(false);
}

void    DLLVarInterface::DLLDebug(QApplication *app)
{
    if(DLLDebugShow!=NULL)
        DLLDebugShow(Handle,*app);
}


bool    DLLVarInterface::OpenInitialize(LayersBase *base)
{
	return LoadDLL(base,FileName);
}

bool	DLLVarInterface::IsDLLVarDLL(void)	const
{
	if(DLL_GetVersion!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLSeqDLLVarMode){
			return(true);
		}
	}
	return(false);
}

bool	DLLVarInterface::LoadDLL(LayersBase *base ,const QString &filename)
{
	if(FileName!=filename){
		FileName=filename;
	}

	DllLib.setFileName(filename);
	if(DllLib.load()==false)
		return(false);
	DLL_GetDLLType		=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetName			=(bool (*)(QString &str))DllLib.resolve("DLL_GetName");
	DLL_GetExplain		=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_GetVersion		=(WORD	(*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_CheckCopyright	=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLLInitial		= (void *(*)(LayersBase * ,const QString &))DllLib.resolve("DLLSeq_Initial");
	DLLCmd			= (bool (*)(void *handle ,QApplication &,const QString &))DllLib.resolve("DLLSeq_Cmd");
	DLLCmdStr       = (bool (*)(void *handle ,QApplication &,const QString &, const QByteArray &))DllLib.resolve("DLLSeq_CmdStr");
    DLLCmdStrInt    = (bool (*)(void *handle ,QApplication &,const QString &, const QByteArray & ,int *))DllLib.resolve("DLLSeq_CmdStrInt");
    DLLCmdStrRet    = (bool (*)(void *handle ,QApplication &,const QString &, const QByteArray & ,QByteArray &))DllLib.resolve("DLLSeq_CmdStrRet");
    DLLCmdStrRetInt = (bool (*)(void *handle ,QApplication &,const QString &, const QByteArray & ,QByteArray & ,int *))DllLib.resolve("DLLSeq_CmdStrRetInt");
    DLLCmdInt       = (bool (*)(void *handle ,QApplication &,const QString &, int *))DllLib.resolve("DLLSeq_CmdInt");
	DLLCmdFloat     = (bool (*)(void *handle ,QApplication &,const QString &, double *))DllLib.resolve("DLLSeq_CmdFloat");
    DLLCmdInt2      = (bool (*)(void *handle ,QApplication &,const QString &, int *,int *))DllLib.resolve("DLLSeq_CmdInt2");
    DLLCmdInt3      = (bool (*)(void *handle ,QApplication &,const QString &, int *,int *,int *))DllLib.resolve("DLLSeq_CmdInt3");
    DLLCmdInt4      = (bool (*)(void *handle ,QApplication &,const QString &, int *,int *,int *,int *))DllLib.resolve("DLLSeq_CmdInt4");
    LGetDLLVersion  = (void (*)(char *))DllLib.resolve("DLLSeq_GetDLLVersion");
    DLLClose        = (void (*)(void *handle))DllLib.resolve("DLLSeq_Close");
    DLLDebugShow    = (void (*)(void *handle ,QApplication &))DllLib.resolve("DLLSeq_DebugShow");
	DLL_TransmitDirectly	=(void (*)(void *handle ,GUIDirectMessage *packet))DllLib.resolve("DLL_TransmitDirectly");

    if(LGetDLLVersion!=NULL){
        char    Buff[256];
        LGetDLLVersion(Buff);
        VersionStr=QString(Buff);
        }
	if(DLLInitial!=NULL && base!=NULL){
		Handle=DLLInitial(base,Param);
	}

    return(true);
}


void	DLLVarInterface::TransmitDirectly(GUIDirectMessage *packet)
{
	if(DLL_TransmitDirectly!=NULL){
		DLL_TransmitDirectly(Handle,packet);
	}
}

QString	DLLVarInterface::GetDLLVarName(void)	const
{
	if(DLL_GetName!=NULL){
		QString	Str;
		if(DLL_GetName(Str)==true){
			return Str;
		}
	}
	return QString(/**/"");
}

WORD	DLLVarInterface::GetVersion(void)	const
{
	if(DLL_GetVersion!=NULL){
		return DLL_GetVersion();
	}
	return 0;
}

WORD	DLLVarInterface::GetDLLType(void)	const
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
QString	DLLVarInterface::GetCopyright(void)	const
{
	QString	Copyright;
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return Copyright;
		}
	}
	return QString(/**/"");
}

const QString	DLLVarInterface::GetExplain(void)	const
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

void	DLLVarInterface::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(LGetDLLVersion!=NULL){
		Str.append("LGetDLLVersion");
	}
	if(DLLInitial!=NULL){
		Str.append("DLLInitial");
	}
	if(DLLCmd!=NULL){
		Str.append("DLLCmd");
	}
	if(DLLCmdStr!=NULL){
		Str.append("DLLCmdStr");
	}
	if(DLLCmdStrInt!=NULL){
		Str.append("DLLCmdStrInt");
	}
	if(DLLCmdStrRet!=NULL){
		Str.append("DLLCmdStrRet");
	}
	if(DLLCmdStrRetInt!=NULL){
		Str.append("DLLCmdStrRetInt");
	}
	if(DLLCmdInt!=NULL){
		Str.append("DLLCmdInt");
	}
	if(DLLCmdInt2!=NULL){
		Str.append("DLLCmdInt2");
	}
	if(DLLClose!=NULL){
		Str.append("DLLClose");
	}
	if(DLLDebugShow!=NULL){
		Str.append("DLLDebugShow");
	}
}
