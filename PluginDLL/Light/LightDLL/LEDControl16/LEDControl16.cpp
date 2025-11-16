#include "LEDControl16.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLightDLL.h"
#include <QDir.h>
#include <QFile.h>
#include "SettingDialog.h"

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLLightMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LEDControl16";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2016.03";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "LEDControl16";
}

LightDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr,bool OutputMode)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	LEDControl16Panel	*H=new LEDControl16Panel(base ,LightParamStr);
	H->Initial(OutputMode);
	return H;
}

bool		_cdecl	DLL_Close(LightDLLBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	LEDControl16Panel	*H=(LEDControl16Panel *)handle;
	if(H!=NULL){
		H->Close();
		delete	H;
	}

	return true;
}

bool		_cdecl	DLL_Load(LightDLLBaseClass *handle ,QIODevice &str)
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false
{
	return handle->Load(&str);
}

bool		_cdecl	DLL_Save(LightDLLBaseClass *handle ,QIODevice &str)
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return handle->Save(&str);
}

bool		_cdecl	DLL_ShowSetting(LightDLLBaseClass *handle, QWidget *parent)
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	return handle->ShowSettingDialog();
}

int		_cdecl	DLL_GetLightPatternCount(LightDLLBaseClass *handle)
//	This function must return Pattern-Count on handle
{
	return 1;
}

bool		_cdecl	DLL_LightOn(LightDLLBaseClass *handle)
//	Turn on handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	handle->ReflectPhysicalTurnOn(true);
	return true;
}


bool		_cdecl	DLL_LightOff(LightDLLBaseClass *handle)
//	Turn off handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	handle->ReflectPhysicalTurnOn(false);
	return true;
}


bool		_cdecl	DLL_SetPattern(LightDLLBaseClass *handle ,int PatternNo)
//	This function set Light-pattern
//	This function must return as soon as possible
//	If LightOff was set before this function, Light must be enlightened with this pattern when LightOn function is called
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	LEDControl16Panel	*p=static_cast<LEDControl16Panel *>(handle);
	if(p!=NULL){
		p->CurrentPattern=PatternNo;
		p->Transfer(p->CurrentPattern,NULL);
		p->SetOnOff(true);
	}
	return true;
}

bool		_cdecl	DLL_ReqLightError(LightDLLBaseClass *handle ,QStringList &Msg)
//	Request light error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	return true;
}

