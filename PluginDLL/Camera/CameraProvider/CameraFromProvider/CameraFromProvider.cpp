#include "CameraFromProvider.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "XCameraDLL.h"
#include "XCameraProviderCommon.h"
#include "swap.h"
#include "SettingDialog.h"

//	return	DLL type for CameraDLL
WORD	DLL_GetDLLType(void)
{
	return(DLLCameraMode);
}

//	return DLL-Name. 
bool	DLL_GetName(QString &str)
{
	str="CameraFromProvider";
	return(true);
}

//	return Camera DLL version
WORD	DLL_GetVersion(void)
{
	return(1);
}


DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
}
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString)
{
	return true;
}

const	char	*CameraAccessSettingFileName="CameraAccessSettingFileName.dat";


DEFFUNCEX	CameraHandle*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//				CamInfo : Set unique several attributes in this function
{
	int32	CameraNo=CameraNoInThisComputer;	
	QFile	File(CameraAccessSettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		::Load(&File,CameraNo);
	}
	CameraProviderHandle	*L=new CameraProviderHandle(base,CameraNo);

	if(L->OpenForClient()==false)
		return NULL;
	return L;
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	delete	H;
	return true;
}

#define	Bool3ToBool(b)	(((b)==true3)?true:false)


DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	QByteArray	BArray;
	if(::Load(&str,BArray)==false)
		return false;
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;

	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	memcpy(Header->StreamData,BArray.data(),BArray.size());
	Header->StreamByte	=BArray.size();
	Header->Command	=CameraProviderCommand_Load;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;

}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_Save;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			QByteArray	BArray((const char *)Header->StreamData,Header->StreamByte);
			::Save(&str,BArray);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	bool	Ret=false;
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	SettingDialog	Dlg(H->GetCamNo());
	int	DlgResult=Dlg.exec();
	if(DlgResult==(int)true){
		H->SetCamNo(Dlg.CameraNo);
		QFile	File(CameraAccessSettingFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			::Save(&File,H->GetCamNo());
		}

		H->Lock();
		struct	CameraProviderHandleHeader	*Header=H->GetHeader();
		Header->Response=none3;
		Header->Command	=CameraProviderCommand_ShowSetting;
		H->Unlock();

		for(;;){
			H->Lock();
			if(Header->Response!=none3){
				Ret=Bool3ToBool(Header->Response);
				H->Unlock();
				break;
			}
			H->Unlock();
			GSleep(30);
		}
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_PrepareCapture;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_StartCapture;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}


DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_HaltCapture;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}


DEFFUNCEX	int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
//					Bit5		1:Start DMA transfer
//								Set bit soon after DMA starts in frame capturing
//								Set bit soon after one DMA frame starts in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit6		1:Finish DMA transfer
//								Set bit soon after DMA finishes in frame capturing
//								Set bit soon after 1 DMA frame finishes in continuous capturing
//								This bit must be kept until DLL_ClearBit
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_GetStatus;
	H->Unlock();

	int	Ret=0;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Header->RespondedValue;
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}


DEFFUNCEX	int			_cdecl	DLL_GetCurrentLineCount(CameraHandle *handle)
//	Return captured line count on capturing mode
//	This must return quickly.
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_GetLineCount;
	H->Unlock();

	int	Ret=0;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Header->RespondedValue;
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_ClearError;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_ClearBit(CameraHandle *handle)
//	Clear status bit
//	This function must return soon
//	if process fails, it returns false
//	This function is used to reset Bit5 of GetStatus from application
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_ClearBit;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_GetImage;
	int	LayerNumb=Header->LayerNumb;
	int	XLen	=Header->XSize;
	int	YLen	=Header->YSize;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	if(Ret==true){
		H->Lock();
		for(int Layer=0;Layer<BufferDimCounts && Layer<LayerNumb;Layer++){
			BYTE	*s=H->GetLayerBufferPointer(Layer);
			for(int y=0;y<YLen && y<Buff[Layer]->GetHeight();y++){
				memcpy(Buff[Layer]->GetY(y),s,min(XLen,Buff[Layer]->GetWidth()));
				s+=XLen;
			}
		}
		H->Unlock();
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_ReqCameraError(CameraHandle *handle ,QStringList &Msg)
//	Request camera error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	CameraProviderHandle	*H=(CameraProviderHandle *)handle;
	H->Lock();
	struct	CameraProviderHandleHeader	*Header=H->GetHeader();
	Header->Response=none3;
	Header->Command	=CameraProviderCommand_ReqCameraError;
	H->Unlock();

	bool	Ret=false;
	for(;;){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			Msg.append(QString(Header->CameraError));
			H->Unlock();
			break;
		}
		H->Unlock();
		GSleep(30);
	}
	return Ret;
}

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
}