#include "ActivatedLicense.h"
#include "XDLLType.h"
#include "XHaspDLL.h"


//=================================================================================================

DEFFUNCEX	WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLHaspMode;
}

DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="ActivatedLicenseDLL";
	return true;
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
//	return Hasp DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2021.06";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Activated License control";
}

HaspHandleContainer		*_cdecl	DLL_Initial(LayersBase *base,const QString &ParamStr)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	HaspHandleContainer	*H=new HaspHandleContainer();
	ActivatedLicense	*p=new ActivatedLicense(base);
	H->AppendList(p);
	return H;
}

bool		_cdecl	DLL_Close(HaspHandleContainer *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	HaspHandleContainer	*H=(HaspHandleContainer *)handle;
	if(H!=NULL){
		delete	H;
	}

	return true;
}
