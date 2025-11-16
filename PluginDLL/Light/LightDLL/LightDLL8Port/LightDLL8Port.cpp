#include "LightDLL8Port.h"
#include "XLightDLL.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "LED64CTRLib.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <QDir.h>
#include <QFile.h>

#if KindOfLight==1
	#include "LightDLL1Form.h"
	static  LightDLL1Form	*LightForm=NULL;
#elif   KindOfLight==2
	#include "LightDLL2Form.h"
	static  LightDLL2Form	*LightForm=NULL;
#elif   KindOfLight==3
	#include "LightDLL6PortForm.h"
	static  LightDLL6PortForm	*LightForm=NULL;
#elif   KindOfLight==4
	#include "LightDLL8PortForm.h"
	static  LightDLL8PortForm	*LightForm=NULL;
#elif   KindOfLight==10
	#include "LightDLL2Form.h"
	static  LightDLL2Form	*LightForm=NULL;
#endif

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
	return "Light 8 Port";
}

LightDLLBaseClass		*_cdecl	DLL_Initial(LayersBase *base,const QString &LightParamStr,bool OutputMode)
//	Initialize Light DLL. 
//		This function must create and open handle. 
//	return:		Light handle(memory block)
//				if proocess fails, return 0
{
	int H;
	for(H=0;H<LightDimNumb;H++){
		LightDim[H]=NULL;
	}

	for(H=0;H<LightDimNumb;H++){
		if(LightDim[H]==NULL){
			#if KindOfLight==1
				LightDim[H]=new LightDLL1(base);
			#elif	KindOfLight==2
				LightDim[H]=new LightDLL2(base);
			#elif	KindOfLight==3
				LightDim[H]=new LightDLL1(base);
			#elif	KindOfLight==4
				LightDim[H]=new LightDLL1(base);
			#elif KindOfLight==10
				LightDim[H]=new LightDLL1(base);
			#endif
			break;
		}
	}
/*
	//WinDriver
//	WDC_DEVICE_HANDLE	hDev = NULL;

	// Initialize the WD_REGISTER library
	DWORD	dwStatus = WD_REGISTER_LibInit();
	if (WD_STATUS_SUCCESS != dwStatus){
		WD_REGISTER_ERR("wd_register_diag: Failed to initialize the WD_REGISTER library: %s",
			WD_REGISTER_GetLastErr());
		return NULL;
	}

	// Open a handle to the device
	hDev[H] = WD_REGISTER_DeviceOpen();
	if (!hDev[H]){
		WD_REGISTER_ERR("wd_register_diag: Failed opening a handle to the device: %s",
			WD_REGISTER_GetLastErr());
		return NULL;
	}

	// Find the first active address space
	DWORD	dwAddrSpace = ACTIVE_ADDR_SPACE_NEEDS_INIT;
	WDC_ADDR_MODE	mode = WDC_MODE_8;
	for (dwAddrSpace = 0; dwAddrSpace < WD_REGISTER_ADDR_SPACES_NUM; dwAddrSpace++){
		if (WDC_AddrSpaceIsActive(hDev[H], dwAddrSpace))
			break;
	}
*/
	if(H<LightDimNumb){
		LightDim[H]->InitialLED();

		LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);
		if(p!=NULL){
			QString	FileName=base->GetUserPath()+ ::GetSeparator()+/**/"ConfigLight8.dat";
			QFile	File(FileName);
			if(File.open(QIODevice::ReadOnly)==true){
				for(int i=0;i<LEDBARNUMB;i++){
					if(::Load(&File,p->BarComment[i])==false){
						break;
					}
				}
			}
		}
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
		#if KindOfLight==1
			LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);
		#elif	KindOfLight==2
			LightDLL2	*p=dynamic_cast<LightDLL2 *>(LightDim[H]);
		#elif	KindOfLight==3
			LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);
		#elif	KindOfLight==4
			LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);
		#elif	KindOfLight==10
			LightDLL1	*p=dynamic_cast<LightDLL1 *>(LightDim[H]);
		#endif
		if(p==NULL)
			return false;
		if(LightForm==NULL){
			#if KindOfLight==1
				LightForm=new LightDLL1Form(p,parent);
			#elif   KindOfLight==2
				LightForm=new LightDLL2Form(p,parent);
			#elif   KindOfLight==3
				LightForm=new LightDLL6PortForm(p,parent);
			#elif   KindOfLight==4
				LightForm=new LightDLL8PortForm(p,parent);
			#elif KindOfLight==10
				LightForm=new LightDLL2Form(p,parent);
			#endif
		}
	//	LightForm->LanguageCode=languagecode;
		LightForm->InspectionLight=LightDim[H];
		LightForm->BLight=*p;

		bool Ret;
		if(Ret=LightForm->exec()){
			*p=LightForm->BLight;
			QString	FileName=p->GetLayersBase()->GetUserPath()+ ::GetSeparator()+/**/"ConfigLight8.dat";
			QFile	File(FileName);
			if(File.open(QIODevice::WriteOnly)==true){
				for(int i=0;i<LEDBARNUMB;i++){
					if(::Save(&File,LightForm->BLight.BarComment[i])==false){
						break;
					}
				}
			}
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
