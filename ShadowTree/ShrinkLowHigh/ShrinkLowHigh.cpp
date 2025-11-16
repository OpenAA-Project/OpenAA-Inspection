#include "ShrinkLowHigh.h"
#include "XShadowControlDLL.h"
#include "SettingShrinkHighLowDialog.h"

WORD		DLL_GetDLLType(void)
{
	return DLLShadowControl;
}

bool		DLL_GetName(QString &str)
{
	str="ShrinkLowHigh";
	return true;
}
WORD		DLL_GetVersion(void)
{
	return  1;
}
const char	*DLL_GetExplain(void)
{
	return "Shrinked High/Low";
}
void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
}
bool		DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="Copyright(c) MEGATRADE 2022.2";
	return true;
}

ShadowTree	*DLL_Initial(int ShadowNumber,LayersBase *ParentBase
						,const QString &GlobalParamFileName
						,const QString &GUIFileName)
{
	return new ShrinkLowHigh(ShadowNumber,ParentBase);
}
bool		DLL_Close(ShadowTree *handle)
{
	delete	handle;
	return true;
}
bool		DLL_ShowSetting(ShadowTree *handle, QWidget *parent)
{
	ShrinkLowHigh	*h=dynamic_cast<ShrinkLowHigh *>(handle);
	if(h!=NULL){
		SettingShrinkHighLowDialog	D(h);
		if(D.exec()==true){
			return true;
		}
	}
	return false;
}

//================================================================
