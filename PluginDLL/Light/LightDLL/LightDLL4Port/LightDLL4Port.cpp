#include "LightDLL4Port.h"
#include "XLightDLL.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "LED64CTRLib.h"
#include "LightDLL4PortForm.h"

static  LightDLL4PortForm	*LightForm=NULL;

const	int		LightDimNumb=256;
LightDLLBase	*LightDim[LightDimNumb];
//LightDLLBase	*LightDim;
//LED64ctr			CLED[LEDBARNUMB];

//=================================================================================================

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLLightMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LightDLL";
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
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Light 4 Port";
}

LightDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr,bool OutputMode)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(LightDim[H]==NULL){
			LightDim[H]=new LightDLL1(base);
			break;
		}
	}
	if(H<LightDimNumb){
		LightDim[H]->InitialLED();
		return dynamic_cast<LightDLLBaseClass *>(LightDim[H]);
	}
	return NULL;
}

bool		_cdecl	DLL_Close(LightDLLBaseClass *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		if(LightDim[H]!=NULL){
			delete	LightDim[H];
			LightDim[H]=NULL;
		}
	}
	return true;
}

bool		_cdecl	DLL_Load(LightDLLBaseClass *handle ,QIODevice &str)
//	Load light attribution(setting) information of handle
//	This function must load information from stream
//	In this function, light attribution information must be set to a handle
//	if process fails, it returns false
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		return LightDim[H]->LEDLoad(str);
	}
	return false;
}

bool		_cdecl	DLL_Save(LightDLLBaseClass *handle ,QIODevice &str)
//	Save light attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		return LightDim[H]->LEDSave(str);
	}
	return false;
}

bool		_cdecl	DLL_ShowSetting(LightDLLBaseClass *handle, QWidget *parent)
//	This function shows dialog to set light(handle) information
//	In this dialog in function, it must set followings
//		1: Pattern Count
//		2:Lighting pattern(Which light is on, or level)
//		3:Set these data to a handle
//	if dialog can't be shown, it returns false
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}

	if(H<LightDimNumb){
		LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);

		if(p==NULL)
			return false;
		if(LightForm==NULL){
			LightForm=new LightDLL4PortForm(p,parent);
		}
	//	LightForm->LanguageCode=languagecode;
		LightForm->InspectionLight=LightDim[H];
		LightForm->BLight=*p;

		bool Ret;
		if(Ret=LightForm->exec()){
			*p=LightForm->BLight;
		}
		//delete LightForm;
		//LightForm=NULL;

		return Ret;
	}
	return false;
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
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		return LightDim[H]->LightOn();
	}
	return false;
}

bool		_cdecl	DLL_LightOff(LightDLLBaseClass *handle)
//	Turn off handle-light
//	This function must return soon
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		return LightDim[H]->LightOff();
	}
	return false;
}

bool		_cdecl	DLL_SetPattern(LightDLLBaseClass *handle ,int PatternNo)
//	This function set Light-pattern
//	This function must return as soon as possible
//	If LightOff was set before this function, Light must be enlightened with this pattern when LightOn function is called
//	if process fails, it returns false
//	In one case, this fuction is called from Sequence.dat
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		if(dynamic_cast<LightDLLBaseClass *>(LightDim[H])==handle)
			break;
	}
	if(H<LightDimNumb){
		LightDim[H]->TransferLED();
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
