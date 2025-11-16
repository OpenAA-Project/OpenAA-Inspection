#include "CameraSharerDLL.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "XCameraDLL.h"
#include "XDataInLayer.h"
#include "XCameraSharerCommon.h"
#include "swap.h"
#include <QApplication>
#include "SelectShareNoDialog.h"
//#include "SettingDialog.h"
#include <omp.h>

#define	Bool3ToBool(b)	(((b)==true3)?true:false)


//	return	DLL type for CameraDLL
WORD	DLL_GetDLLType(void)
{
	return(DLLCameraMode);
}

//	return DLL-Name. 
bool	DLL_GetName(QString &str)
{
	str="CameraSharerDLL";
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


DEFFUNCEX	CameraHandle*_cdecl	DLL_Initial(int CameraNoInThisComputer , LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//				CamInfo : Set unique several attributes in this function
{
	int32	ShareNo=CameraNoInThisComputer;	
	QFile	File(CameraAccessSettingFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		::Load(&File,ShareNo);
	}
	CameraSharerHandle	*L=new CameraSharerHandle(CameraNoInThisComputer,base,ShareNo);
	if(L->OpenForClient()==false)
		return NULL;

	struct	CameraSharerHandleHeader	*Header=L->GetHeader();

	L->Lock();
	Header->Response=none3;

	Header->CamNo		=CameraNoInThisComputer;
	Header->XSize		=CamInfo.XLen;
	Header->YSize		=CamInfo.YLen;
	Header->LayerNumb	=CamInfo.LayerNumber;
	Header->Command	=CameraSharerCommand_Allocate;
	L->Unlock();

	bool	Ret=false;
	while(L->ShouldFinish==false){
		L->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			L->Unlock();
			break;
		}
		L->Unlock();
		GSleep(30);
	}
	//if(L->AllocateForClient()==false)
	//	return NULL;

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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->ShouldFinish=true;
	GSleep(500);
	delete	H;
	return true;
}



DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{

	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	SelectShareNoDialog	Dlg(H->ShareNo);
	int	DlgResult=Dlg.exec();
	if(DlgResult==(int)true){
		H->ShareNo=Dlg.ShareNo;
		QFile	File(CameraAccessSettingFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			::Save(&File,H->ShareNo);
		}
	}
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_PrepareCapture;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
		H->Lock();
		if(Header->Response!=none3){
			Ret=Bool3ToBool(Header->Response);
			H->Unlock();
			break;
		}
		H->Unlock();
		if(H->Base->IsMainThread ()==true){
			QApplication::processEvents();
		}
		else{
			GSleep(30);
		}
	}
	return Ret;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_StartCapture;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_HaltCapture;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_GetStatus;
	H->Unlock();

	int	Ret=0;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_GetLineCount;
	H->Unlock();

	int	Ret=0;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_ClearError;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_ClearBit;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_GetImage;
	int	LayerNumb=Header->LayerNumb;
	int	XLen	=Header->XSize;
	int	YLen	=Header->YSize;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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
		H->AllocateForClient();
		H->Lock();
		int	MaxLayerNumb=min(BufferDimCounts,LayerNumb);
		for(int Layer=0;Layer<MaxLayerNumb;Layer++){
			BYTE	*src=H->GetLayerBufferPointer(Layer);
			int	MaxYLen=min(YLen,Buff[Layer]->GetHeight());
			int	MaxXLen=min(XLen,Buff[Layer]->GetWidth());
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<MaxYLen;y++){
					BYTE *s=&src[y*XLen];
					memcpy(Buff[Layer]->GetY(y),s,MaxXLen);
				}
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
	CameraSharerHandle	*H=(CameraSharerHandle *)handle;
	H->Lock();
	struct	CameraSharerHandleHeader	*Header=H->GetHeader();
	Header->CamNo	=H->GetCamNo();
	Header->Response=none3;
	Header->Command	=CameraSharerCommand_ReqCameraError;
	H->Unlock();

	bool	Ret=false;
	while(H->Base->GetOnTerminating()==false && H->ShouldFinish==false){
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