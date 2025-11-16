#include "DFSFilterMJC.h"
#include "XDFSFilterDLL.h"
#include <QString>
#include "XDFS.h"

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
{
	str=/**/"DFSFilterMJC";
	return true;
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
{
	return 1;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"DFS filter for MJC";
}

DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString=/**/"Copyright(c) MEGATRADE 2016.11";
	return true;
}


DEFFUNCEX	XDFSFilterBase		*_cdecl	DLL_Initial(const QString &ParamStr)
{
	return new DFSFilterMJC(ParamStr);
}

DEFFUNCEX	bool		_cdecl	DLL_Close(XDFSFilterBase *handle)
{
	delete	handle;
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_Load(XDFSFilterBase *handle ,QIODevice &str)
{
	return handle->Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_Save(XDFSFilterBase *handle ,QIODevice &str)
{
	return handle->Load(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(XDFSFilterBase *handle, QWidget *parent)
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_ExecuteSaveFileInDFS(XDFSFilterBase *handle ,FileSaveAttr *SavedAttr 
														,const QString &Provider ,const QString &LocalPath
														,int &Permit)
{
	QStringList	LList=SavedAttr->FileName.split('_');
	for(int i=LList.count()-1;i>=0;i--){
		if(LList[i].left(1)==/**/"X"){
			bool	ok;
			double	XPos=LList[i].mid(1).toInt(&ok)/1000.0;
			if(ok==false){
				Permit=100;
				return true;
			}

			int	W=327.0/4;
			int	N=XPos/W;
			if(N==0 && Provider.toUpper()==/**/"SLAVEPC-A"){
				Permit=0;
				return true;
			}
			else if(N==1 && Provider.toUpper()==/**/"SLAVEPC-B"){
				Permit=0;
				return true;
			}
			else if(N==2 && Provider.toUpper()==/**/"SLAVEPC-C"){
				Permit=0;
				return true;
			}
			else if(N==3 && Provider.toUpper()==/**/"SLAVEPC-D"){
				Permit=0;
				return true;
			}
			else if(Provider==/**/"MASTERPC"){
				Permit=20;
				return true;
			}
			break;
		}
	}
	Permit=-1;
	return true;
}

//==================================================================================================================

DFSFilterMJC::DFSFilterMJC(const QString &ParamStr)
{

}

DFSFilterMJC::~DFSFilterMJC()
{

}
