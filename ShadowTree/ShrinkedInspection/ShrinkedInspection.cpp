#include "XShadowControlDLL.h"
#include "ShrinkedInspection.h"
#include "ShadowSettingDialog.h"

WORD		DLL_GetDLLType(void)
{
	return DLLShadowControl;
}

bool		DLL_GetName(QString &str)
{
	str="ShrinkedInspection";
	return true;
}
WORD		DLL_GetVersion(void)
{
	return  1;
}
const char	*DLL_GetExplain(void)
{
	return "Shrinked inspection";
}
void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
}
bool		DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="Copyright(c) MEGATRADE 2021.12";
	return true;
}

ShadowTree	*DLL_Initial(int ShadowNumber,LayersBase *ParentBase
						,const QString &GlobalParamFileName
						,const QString &GUIFileName)
{
	return new ShrinkedInspection(ShadowNumber,ParentBase);
}
bool		DLL_Close(ShadowTree *handle)
{
	delete	handle;
	return true;
}
bool		DLL_ShowSetting(ShadowTree *handle, QWidget *parent)
{
	ShrinkedInspection	*h=dynamic_cast<ShrinkedInspection *>(handle);
	if(h!=NULL){
		ShadowSettingDialog	D(h);
		if(D.exec()==true){
			return true;
		}
	}
	return false;
}

//================================================================
