#include "CameraUSBStandard.h"
#include "jpeglib.h"
#include "turbojpeg.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "SettingCameraDialog.h"
#include "XHidCommand.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "SelectCameraDialog.h"
#include "LibWMFCamera.h"
#include "CameraUSBStandard.h"
#include "XCameraCommon.h"
#include "swap.h"
#include "XLogOut.h"
#include "libusb.h"

#define		CameraNameID	"USB Camera"

//---------------------------------------------------------------

DEFFUNCEX	WORD	DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}
DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="Standard USB camera for windows";
	return(true);
}

DEFFUNCEX	WORD		_cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}

bool	ExistVendorID(QStringList &OtherVendorIDs,int VendorID)
{
	for(int i=0;i<OtherVendorIDs.count();i++){
		bool	ok;
		if(OtherVendorIDs[i].toUpper()==/**/"FIX")
			continue;
		if(OtherVendorIDs[i].toUpper()==/**/"SMOOTHING")
			continue;
		int	n=OtherVendorIDs[i].toInt(&ok);
		if(ok==true){
			if(n==VendorID){
				return true;
			}
		}
	}
	return false;
}

const	int	FixedVendorID	=0x04f2;
static	bool	Initialized=false;

const int	FixedProductID[]=	{	 0x1601	//L836
									,0xa007	//L835
								};

char	*FixedCameraName[]={	 /**/"USB Camera L-837"
								,/**/"USB Camera L-836"
								,/**/"USB Camera L-834"
								,/**/"HOZAN USB Camera"
								,/**/"Ostec 5Mega Pixels USB Camera"
								,/**/"USB Camera L835"
								,/**/" USB Camera"
								,/**/"USB Camera L-835"
								};


bool	CheckCameraName(const QString &CamName)
{
	int	N=sizeof(FixedCameraName)/sizeof(FixedCameraName[0]);
	for(int i=0;i<N;i++){
		if(FixedCameraName[i]==CamName){
			return true;
		}
	}
	return false;
}

DEFFUNCEX	int		_cdecl	DLL_GetCameraCount(LayersBase *base,const QString &CameraParameter)
{
	//libusb_init(NULL);
	//libusb_device **list;
	//int cnt = libusb_get_device_list(NULL, &list);
	//int	tcount=0;
	//for (int i = 0; i < cnt; i++) {
	//	libusb_device *device = list[i];
	//	struct libusb_device_descriptor desc;
	//	libusb_device_handle *handle;
	//	libusb_get_device_descriptor(device, &desc);
	//	int	ret = libusb_open(device, &handle);
	//
	//	/* handle ‚Æ desc ‚ðŽg‚Á‚Ä‰½‚©‚·‚é */
	//	unsigned char text[512];
	//	if (ret == 0) {
	//	  libusb_get_string_descriptor_ascii(
	//	      handle, desc.iProduct, text, sizeof(text));
	//	  tcount++;
	//	}
	//}
	//libusb_free_device_list(list, 1);
	//libusb_exit(NULL);



	if(Initialized==false){
		InitialUVCSystem();
		Initialized=true;
	}
	struct DeviceInfo DevDim[100];
	QStringList	CameraNameList;
	int		N=GetDeviceCount(DevDim,CameraNameList);

	int	PermissionVendorID[100];
	int	PermissionVendorIDNumb=0;
	PermissionVendorID[PermissionVendorIDNumb]=FixedVendorID;
	PermissionVendorIDNumb++;
	QStringList	OtherVendorIDs=CameraParameter.split(',');
	for(int i=0;i<OtherVendorIDs.count();i++){
		bool	ok;
		if(OtherVendorIDs[i].toUpper()==/**/"FIX")
			continue;
		if(OtherVendorIDs[i].toUpper()==/**/"SMOOTHING")
			continue;
		PermissionVendorID[PermissionVendorIDNumb]=OtherVendorIDs[i].toInt(&ok);
		if(ok==true){
			PermissionVendorIDNumb++;
		}
	}
	int	CamNumb=0;
	for(int i=0;i<N;i++){
		if(CheckCameraName(CameraNameList[i])==true){
			for(int j=0;j<PermissionVendorIDNumb;j++){
				if(DevDim[i].VendorID==PermissionVendorID[j]){
					CamNumb++;
					break;
				}
			}
		}
	}

	return CamNumb;
}

DEFFUNCEX	CameraHandle*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//				CamInfo : Set unique several attributes in this function
{
	if(Initialized==false){
		InitialUVCSystem();
		Initialized=true;
	}

	struct DeviceInfo DevDim[100];
	QStringList	CameraNameList;
	int		N=GetDeviceCount(DevDim,CameraNameList);

	int	PermissionVendorID[100];
	int	PermissionVendorIDNumb=0;
	PermissionVendorID[PermissionVendorIDNumb]=FixedVendorID;
	PermissionVendorIDNumb++;
	QStringList	OtherVendorIDs=CameraParameter.split(',');
	for(int i=0;i<OtherVendorIDs.count();i++){
		bool	ok;
		if(OtherVendorIDs[i].toUpper()==/**/"FIX")
			continue;
		if(OtherVendorIDs[i].toUpper()==/**/"SMOOTHING")
			continue;
		PermissionVendorID[PermissionVendorIDNumb]=OtherVendorIDs[i].toInt(&ok);
		if(ok==true){
			PermissionVendorIDNumb++;
		}
	}

	bool	FixResolution=false;
	bool	Smoothing=false;
	bool	NoLoad=false;
	for(int i=0;i<OtherVendorIDs.count();i++){
		bool	ok;
		if(OtherVendorIDs[i].toUpper()==/**/"FIX")
			FixResolution=true;
		if(OtherVendorIDs[i].toUpper()==/**/"SMOOTHING")
			Smoothing=true;
	}

	int	CamNumb=0;
	int	VendoredProductIDList[100];
	for(int i=0;i<N;i++){
		if(CheckCameraName(CameraNameList[i])==true){
			for(int j=0;j<PermissionVendorIDNumb;j++){
				if(DevDim[i].VendorID==PermissionVendorID[j]){
					for(int k=0;k<sizeof(FixedProductID)/sizeof(FixedProductID[0]);k++){
						if(DevDim[i].ProductID==FixedProductID[k]){
							VendoredProductIDList[CamNumb]=DevDim[i].ProductID;
							CamNumb++;
							goto	CamBreak;
						}
					}
				}
			}
		CamBreak:;
		}
	}
	LibWMFCamera	*Handle=NULL;

	if(CamNumb<=CameraNoInThisComputer)
		return NULL;
	if(FixResolution==true && CamNumb>1){
		if(CameraNoInThisComputer==0){
			SelectCameraDialog	D(VendoredProductIDList,CamNumb,base);
			D.exec();
			int	LayerNumb=base->GetMaxLayerNumb();
			base->Reallocate(base->GetPhaseNumb(),1,LayerNumb);
			base->GetParamGlobal()->TotalCameraNumb=1;
			int	CNumb=0;
			for(int i=0;i<N;i++){
				if(CheckCameraName(CameraNameList[i])==true){
					for(int j=0;j<PermissionVendorIDNumb;j++){
						if(DevDim[i].VendorID==PermissionVendorID[j]){
							if(CNumb==D.SelectedNo){
								Handle=new LibWMFCamera(CameraNoInThisComputer,base,i,DevDim[i]);
								goto	FoundCamera;
							}
							else{
								CNumb++;
							}
							break;
						}
					}
				}
			}
		}
		else{
			return NULL;
		}
	}
	else if(CameraNoInThisComputer<CamNumb){
		int	CNumb=0;
		for(int i=0;i<N;i++){
			if(CheckCameraName(CameraNameList[i])==true){
				for(int j=0;j<PermissionVendorIDNumb;j++){
					if(DevDim[i].VendorID==PermissionVendorID[j]){
						if(CNumb==CameraNoInThisComputer){
							Handle=new LibWMFCamera(CameraNoInThisComputer,base,i,DevDim[i]);
							goto	FoundCamera;
						}
						else{
							CNumb++;
						}
						break;
					}
				}
			}
		}

	}

FoundCamera:;
	if(Handle==NULL){
		base->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_Initial Handle==NULL");
		return NULL;
	}
	if(Handle->Initial()==false){
		base->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_Initial Initial=false");
		return NULL;
	}
	if(Handle->getProperty()==false){
		base->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_Initial getProperty=false");
		return NULL;
	}
	//if(Handle->SetFastestSize(Handle->GetDotPerLine(),Handle->GetMaxLines())==false){
	//	base->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_Initial SetFastestSize=false");
	//	return NULL;
	//}

	return Handle;
}

DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		delete	Handle;
	}
	return true;
}
DEFFUNCEX	bool	_cdecl	DLL_GetCameraDLLInfo(CameraHandle *handle ,CameraDLLInfo &CamInfo)
{
	CamInfo.MutexInDLL=true;
	return true;
}
DEFFUNCEX	bool	_cdecl	DLL_ResetToDefault(CameraHandle *handle)
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		Handle->RestoreDefault();
		return true;
	}
	return false;
}
DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		struct StructMediaType MediaDim[100];
		int	MCount=Handle->EnumMediaType(MediaDim ,100);
		int	MaxFPS=0;
		int	Index=-1;
		for(int i=0;i<MCount;i++){
			if(Handle->GetRotationAngle()==0 || Handle->GetRotationAngle()==180){
				if(MediaDim[i].Width==caminfo.XLen && MediaDim[i].Height==caminfo.YLen){
					if(MaxFPS<=MediaDim[i].FPS){
						Index=i;
					}
				}
			}
			else{
				if(MediaDim[i].Width==caminfo.YLen && MediaDim[i].Height==caminfo.XLen){
					if(MaxFPS<=MediaDim[i].FPS){
						Index=i;
					}
				}
			}
		}
		if(Index>=0){
			if(Handle->SetMediaType(MediaDim[Index])==false){
				GSleep(1000);
				if(Handle->SetMediaType(MediaDim[Index])==false){
					Handle->GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"CameraUSBStandard:DLL_ChangeInfo SetMediaType=false",Index);
					return false;
				}
			}
			Handle->ReallocXY(caminfo.XLen,caminfo.YLen);
			return true;
		}
		int	MinArea=2000000000;
		MaxFPS=0;
		for(int i=0;i<MCount;i++){
			if(Handle->GetRotationAngle()==0 || Handle->GetRotationAngle()==180){
				if(MediaDim[i].Width>=caminfo.XLen && MediaDim[i].Height>=caminfo.YLen
				&& MediaDim[i].Width*MediaDim[i].Height<=MinArea){
					if(MaxFPS<=MediaDim[i].FPS){
						Index=i;
						MinArea=MediaDim[i].Width*MediaDim[i].Height;
					}
				}
			}
		}
		if(Index>=0){
			if(Handle->SetMediaType(MediaDim[Index])==false){
				Handle->GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"CameraUSBStandard:DLL_ChangeInfo SetMediaType=false",Index);
				return false;
			}
			Handle->ReallocXY(caminfo.XLen,caminfo.YLen);
			return true;
		}
		CameraUSBStandardAnyData	*anydata=dynamic_cast<CameraUSBStandardAnyData *>(caminfo.AnyData);
		if(anydata!=NULL){
			Index=0;
			if(Handle->SetMediaType(MediaDim[Index])==false){
				GSleep(1000);
				if(Handle->SetMediaType(MediaDim[Index])==false){
					Handle->GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"CameraUSBStandard:DLL_ChangeInfo SetMediaType=false",Index);
					return false;
				}
			}
			Handle->GetLayersBase()->ReallocXYPixels(MediaDim[Index].Width,MediaDim[Index].Height);
			return true;

		}
	}
	return false;
}
DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		if(Handle->Load(&str)==false){
			Handle->GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_ChangeInfo DLL_Load=false");
			return false;
		}
		Handle->setProperty();
		return true;
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		if(Handle->Save(&str)==false){
			Handle->GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"CameraUSBStandard:DLL_ChangeInfo DLL_Save=false");
			return false;
		}
		return true;
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		SettingCameraDialog	D(Handle->GetLayersBase(),Handle,parent);
		if(D.exec()==(int)true){
			return true;
		}
	}
	return false;
}
	

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	Start capruting till then end of Y lines. 
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCaptureContinuously(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Start capruting till DLL_StopCaptureContinuously. 
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StopCaptureContinuously(CameraHandle *handle)
//	stop to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
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
//					Bit7		0:Buffer empty( enable to capture)	1:Buffer full
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL){
		if(Handle->IsErrored()==true){
			if(Info->DetailResult==NULL){
				Info->DetailResult=new CameraInfoDetail();
			}
			((CameraInfoDetail *)Info->DetailResult)->ErrorCode=Handle->GetErrorCode();
			return 0x10;
		}
		if(Handle->IsEnableRingBuffer()==true){
			if(Handle->IsRingBuferCaptured()==true){
				return 0;
			}
		}
		else{
			if(Handle->IsCaptured()==true){
				return 0;
			}
		}
	}
	return 1;
}

void	MakeMonochrome(ImageBuffer *Buff[]);
static	int	DDbg=0;
static	int	DYLen=0;


DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	bool	Ret=true;
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;
	if(Handle!=NULL && Handle->CapturedBeforeImaging==true){
		//if(Handle->IsEnableRingBuffer()==true){
		//	Handle->RingConvert();
		//}

		Handle->CapturedBeforeImaging=false;
		//Handle->LockBuff();

		bool	ModeMonoChrome;
		if(Handle->GetMonoChrome()==true){
			//ImageBuffer *BWBuff[3];
			handle->GetLayersBase()->LockWChangingDataStructure();
			//Handle->GetBuff(Buff);
			if(Handle->SwapBuff(Buff)==true){
				MakeMonochrome(Buff);
			}
			handle->GetLayersBase()->UnlockChangingDataStructure();
			ModeMonoChrome=true;
		}
		else{
			ModeMonoChrome=false;
		}

		if(Handle->GetMonoChrome()==false){
			handle->GetLayersBase()->LockWChangingDataStructure();
			if(Buff[0]!=NULL){
				//for(int i=0;i<BufferDimCounts;i++){
				Handle->SwapBuff(Buff);
				//}
			}
			else{
				for(int i=0;i<BufferDimCounts;i++){
					Buff[i]=Handle->GetBuffR(i);
					if(Buff[i]==NULL){
						Ret=false;
					}
				}
				//if(Ret==true){
				//	for(int i=0;i<BufferDimCounts;i++){
				//		*Handle->GetBuffR(i)=*Handle->GetBuff(i);
				//	}
				//}
			}
			handle->GetLayersBase()->UnlockChangingDataStructure();
		}
		int	YLen=Buff[0]->GetHeight();
		if(YLen-5>=0){
			int	d=Buff[0]->GetPixel(100,YLen-5);
			if(d==255){
				DDbg++;
			}
			if(DYLen!=YLen){
				DDbg++;
			}
		}
		Handle->SetCapturedTime();
		//Handle->UnlockBuff();

		return Ret;
	}
	else{
		return false;
	}
}

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}
DEFFUNCEX	bool		_cdecl	DLL_ClearBit(CameraHandle *handle)
//	Clear status bit
//	This function must return soon
//	if process fails, it returns false
//	This function is used to reset Bit5 of GetStatus from application
{
	return true;
}

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
{
	LibWMFCamera	*Handle=(LibWMFCamera *)handle;

	if(Handle!=NULL){
		CmdReqResolutionList	*CmdReqResolutionListVar=dynamic_cast<CmdReqResolutionList *>(packet);
		if(CmdReqResolutionListVar!=NULL){
			struct StructMediaType MediaDim[100];
			int	MCount=Handle->EnumMediaType(MediaDim ,100);
			for(int i=0;i<MCount;i++){
				QString	s =  QString("X")
							+QString::number(MediaDim[i].Width)
							+QString("  Y")
							+QString::number(MediaDim[i].Height)
							+QString("  FPS")
							+QString::number(MediaDim[i].FPS);
				CmdReqResolutionListVar->List.append(s);
			}
			CmdReqResolutionListVar->ProductID=Handle->GetProductID();

			struct	StructMediaType Type;
			Handle->GetMediaType(Type);

			CmdReqResolutionListVar->CurrentIndex	=Type.Index;
			CmdReqResolutionListVar->CurrentXLen	=Type.Width;
			CmdReqResolutionListVar->CurrentYLen	=Type.Height;
			return;
		}
		CmdSetResolutionList	*CmdSetResolutionListVar=dynamic_cast<CmdSetResolutionList *>(packet);
		if(CmdSetResolutionListVar!=NULL){
			bool	FlagChange=false;
			int	ListNo=CmdSetResolutionListVar->CurrentIndex;
			struct StructMediaType MediaDim[100];
			int	MCount=Handle->EnumMediaType(MediaDim ,100);

			Handle->SetMediaType(MediaDim[ListNo]);
			return;
		}
		CmdSetImageAttr	*CmdSetImageAttrVar=dynamic_cast<CmdSetImageAttr *>(packet);
		if(CmdSetImageAttrVar!=NULL){
			Handle->GetLayersBase()->LockWChangingDataStructure();
			Handle->SetMirrorX		(CmdSetImageAttrVar->MirrorX);
			Handle->SetMirrorY		(CmdSetImageAttrVar->MirrorY);
			Handle->SetRotationAngle(CmdSetImageAttrVar->RotationAngle);
			Handle->SetMonoChrome	(CmdSetImageAttrVar->MonoChrome);
			Handle->GetLayersBase()->UnlockChangingDataStructure();
			return;
		}
		CmdReqImageAttr	*CmdReqImageAttrVar=dynamic_cast<CmdReqImageAttr *>(packet);
		if(CmdReqImageAttrVar!=NULL){
			Handle->GetLayersBase()->LockWChangingDataStructure();
			CmdReqImageAttrVar->MirrorX			=Handle->GetMirrorX	();
			CmdReqImageAttrVar->MirrorY			=Handle->GetMirrorY	();
			CmdReqImageAttrVar->RotationAngle	=Handle->GetRotationAngle();
			CmdReqImageAttrVar->MonoChrome		=Handle->GetMonoChrome	();
			Handle->GetLayersBase()->UnlockChangingDataStructure();
			return;
		}
		CmdReqStructUSBCamInfoList	*CmdReqStructUSBCamInfoListVar=dynamic_cast<CmdReqStructUSBCamInfoList *>(packet);
		if(CmdReqStructUSBCamInfoListVar!=NULL){
			struct StructMediaType MediaDim[100];
			int	MCount=Handle->EnumMediaType(MediaDim ,100);
			for(int i=0;i<MCount;i++){
				CmdReqStructUSBCamInfoListVar->Dim[i].CamViewSizeX	=MediaDim[i].Width;
				CmdReqStructUSBCamInfoListVar->Dim[i].CamViewSizeY	=MediaDim[i].Height;
				CmdReqStructUSBCamInfoListVar->Dim[i].CamViewFPS	=MediaDim[i].FPS;
			}
			CmdReqStructUSBCamInfoListVar->StructUSBCamInfoCount=MCount;
			return;
		}
		CmdReqCurrentSize	*CmdReqCurrentSizeVar=dynamic_cast<CmdReqCurrentSize *>(packet);
		if(CmdReqCurrentSizeVar!=NULL){
			struct StructMediaType MType;
			Handle->GetMediaType(MType);
			int	Index=CmdReqCurrentSizeVar->Index;

			if(Handle->GetRotationAngle()==0 || Handle->GetRotationAngle()==180){
				CmdReqCurrentSizeVar->RetCamViewSizeX	=MType.Width;
				CmdReqCurrentSizeVar->RetCamViewSizeY	=MType.Height;
				CmdReqCurrentSizeVar->RetCamViewSizeBit	=0;
				CmdReqCurrentSizeVar->RetCamViewFPS		=MType.FPS;
			}
			else{
				CmdReqCurrentSizeVar->RetCamViewSizeX	=MType.Height;
				CmdReqCurrentSizeVar->RetCamViewSizeY	=MType.Width;
				CmdReqCurrentSizeVar->RetCamViewSizeBit	=0;
				CmdReqCurrentSizeVar->RetCamViewFPS		=MType.FPS;
			}

			return;
		}
		CmdReqProperty	*CmdReqPropertyVar=dynamic_cast<CmdReqProperty *>(packet);
		if(CmdReqPropertyVar!=NULL){
			switch(CmdReqPropertyVar->Prop){
			case CAPTURE_BRIGHTNESS:			CmdReqPropertyVar->Item=Handle->GetBrightness	();	break;
			case CAPTURE_CONTRAST:				CmdReqPropertyVar->Item=Handle->GetContrast		();	break;
			case CAPTURE_HUE:					CmdReqPropertyVar->Item=Handle->GetColor		();	break;
			case CAPTURE_SATURATION:			CmdReqPropertyVar->Item=Handle->GetVivid		();	break;
			case CAPTURE_SHARPNESS:				CmdReqPropertyVar->Item=Handle->GetVividation	();	break;
			case CAPTURE_GAMMA:					CmdReqPropertyVar->Item=Handle->GetGamma		();	break;
			//case CAPTURE_COLORENABLE:			CmdReqPropertyVar->Item=Handle->GetExposure		();	break;
			case CAPTURE_WHITEBALANCE:			CmdReqPropertyVar->Item=Handle->GetWhiteBalance	();	break;
			case CAPTURE_BACKLIGHTCOMPENSATION:	CmdReqPropertyVar->Item=Handle->GetReflection	();	break;
			case CAPTURE_GAIN:					CmdReqPropertyVar->Item=Handle->GetGain			();	break;
			case CAPTURE_PAN:					CmdReqPropertyVar->Item=Handle->GetPan			();	break;
			case CAPTURE_TILT:					CmdReqPropertyVar->Item=Handle->GetTilt			();	break;
			case CAPTURE_ROLL:					CmdReqPropertyVar->Item=Handle->GetRotation		();	break;
			case CAPTURE_ZOOM:					CmdReqPropertyVar->Item=Handle->GetZoom			();	break;
			case CAPTURE_EXPOSURE:				CmdReqPropertyVar->Item=Handle->GetExposure		();	break;
			case CAPTURE_IRIS:					CmdReqPropertyVar->Item=Handle->GetIris			();	break;
			case CAPTURE_FOCUS:					CmdReqPropertyVar->Item=Handle->GetFocus		();	break;
			case CAPTURE_POWERLINEFREQUENCY:	CmdReqPropertyVar->PowerlineFrequencyItem=Handle->GetPowerlineFrequency();break;
			//case CAPTURE_PROP_MAX:			CmdReqPropertyVar->Item=Handle->GetExposure		();	break;
			}
			return;
		}
		CmdSetProperty	*CmdSetPropertyVar=dynamic_cast<CmdSetProperty *>(packet);
		if(CmdSetPropertyVar!=NULL){
			if(CmdSetPropertyVar->Item!=NULL){
				CmdSetPropertyVar->Item->setProperty(Handle);
			}
			if(CmdSetPropertyVar->PowerlineFrequencyItem!=NULL){
				CmdSetPropertyVar->PowerlineFrequencyItem->setProperty(Handle);
			}
			return;
		}
		CmdSetPropertyAll	*CmdSetPropertyAllVar=dynamic_cast<CmdSetPropertyAll *>(packet);
		if(CmdSetPropertyAllVar!=NULL){
			Handle->setProperty();
			return;
		}
		CmdResetCameraProperty	*CmdResetCameraPropertyVar=dynamic_cast<CmdResetCameraProperty *>(packet);
		if(CmdResetCameraPropertyVar!=NULL){
			Handle->RestoreDefault();
			return;
		}
		CmdGetAverageSpanTime	*CmdGetAverageSpanTimeVar=dynamic_cast<CmdGetAverageSpanTime *>(packet);
		if(CmdGetAverageSpanTimeVar!=NULL){
			CmdGetAverageSpanTimeVar->SpanTime	=Handle->GetAverageSpanTime();
			return;
		}
	}
}