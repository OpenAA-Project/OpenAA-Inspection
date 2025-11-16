
extern "C" {
#include <Windows.h>
#include "hidsdi.h"
#include <setupapi.h>
#include <dbt.h>
}

#include "XHidCommand.h"


class	HidCommandArm : public HidCommand
{
	bool		Opened;
	GUID		HidGuid;
	HANDLE		DeviceHandle;
	HANDLE		ReadHandle;
	HANDLE		WriteHandle;
	HIDP_CAPS	Capabilities;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	HANDLE		hEventObject;
	OVERLAPPED	HIDOverlapped;
	HDEVNOTIFY	DeviceNotificationHandle;
public:
	HidCommandArm(QWidget *parent);
	virtual	~HidCommandArm(void);

	virtual	bool	OpenHid(int Vid, int Pid,int Number);
	virtual	bool	CloseHid(void);
	virtual	bool	IsOpened(void);

	virtual	bool	SendStr(BYTE *Data ,int Len);
	virtual	bool	ReceiveStr(BYTE *Data ,int &ReceivedLen ,int waitmilisec=6000);

private:
	void	RegisterForDeviceNotifications(void);
	void	GetDeviceCapabilities();
	void	PrepareForOverlappedTransfer();
};

HidCommand::HidCommand(QWidget *parent)
{	
	Parent=parent;
}

HidCommand	*HidCommand::Create(QWidget *parent)
{
	return new HidCommandArm(parent);
}


HidCommandArm::HidCommandArm(QWidget *parent)
	:HidCommand(parent)
{
	Opened=false;
	DeviceHandle	=0;
	ReadHandle		=0;
	WriteHandle		=0;
	hEventObject	=0;
	DeviceNotificationHandle	=NULL;
}

HidCommandArm::~HidCommandArm(void)
{
	CloseHid();
}

bool	HidCommandArm::OpenHid(int VendorID, int ProductID ,int Number)
{
	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = false;
	int									MemberIndex = 0;
	LONG								Result;	
	ULONG								Length;
	HANDLE								hDevInfo;
	ULONG								Required;
	bool	Ret=false;
	int	FoundNumber=0;

	Opened=false;
	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	/*
	API function: HidD_GetHidGuid
	Get the GUID for all system HIDs.
	Returns: the GUID in HidGuid.
	*/

	HidD_GetHidGuid(&HidGuid);	
	
	/*
	API function: SetupDiGetClassDevs
	Returns: a handle to a device information set for all installed devices.
	Requires: the GUID returned by GetHidGuid.
	*/
	
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want. 
	//Quit on detecting the desired device or checking all available devices without success.

	MemberIndex = 0;
	LastDevice = false;

	do
	{
		/*
		API function: SetupDiEnumDeviceInterfaces
		On return, MyDeviceInterfaceData contains the handle to a
		SP_DEVICE_INTERFACE_DATA structure for a detected device.
		Requires:
		The DeviceInfoSet returned in SetupDiGetClassDevs.
		The HidGuid returned in GetHidGuid.
		An index to specify a device.
		*/

		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
			//A device has been detected, so get more information about it.

			/*
			API function: SetupDiGetDeviceInterfaceDetail
			Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
			containing information about a device.
			To retrieve the information, call this function twice.
			The first time returns the size of the structure in Length.
			The second time returns a pointer to the data in DeviceInfoSet.
			Requires:
			A DeviceInfoSet returned by SetupDiGetClassDevs
			The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.
			
			The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
			This application doesn't retrieve or use the structure.			
			If retrieving the structure, set 
			MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
			and pass the structure's address.
			*/
			
			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.

			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			
			//Set cbSize in the detailData structure.

			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Call the function again, this time passing it the returned buffer size.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);

			// Open a handle to the device.
			// To enable retrieving information about a system mouse or keyboard,
			// don't request Read or Write access for this handle.

			/*
			API function: CreateFile
			Returns: a handle that enables reading and writing to the device.
			Requires:
			The DevicePath in the detailData structure
			returned by SetupDiGetDeviceInterfaceDetail.
			*/

			DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);


				/*
				API function: HidD_GetAttributes
				Requests information from the device.
				Requires: the handle returned by CreateFile.
				Returns: a HIDD_ATTRIBUTES structure containing
				the Vendor ID, Product ID, and Product Version Number.
				Use this information to decide if the detected device is
				the one we're looking for.
				*/

				//Set the Size to the number of bytes in the structure.

			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
					(DeviceHandle, 
					&Attributes);
			
			
			//Is it the desired device?


			if (Attributes.VendorID == VendorID
			&& Attributes.ProductID == ProductID){
				if(FoundNumber==Number){
					//Both the Vendor ID and Product ID match.
						
					Opened=true;
					RegisterForDeviceNotifications();

					//Get the device's capablities.
					GetDeviceCapabilities();

					// Find out if the device is a system mouse or keyboard.
					DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;

					// Get a handle for writing Output reports.
					WriteHandle=CreateFile 
							(detailData->DevicePath, 
							GENERIC_WRITE, 
							FILE_SHARE_READ|FILE_SHARE_WRITE, 
							(LPSECURITY_ATTRIBUTES)NULL,
							OPEN_EXISTING, 
							0, 
							NULL);

					PrepareForOverlappedTransfer();
					free(detailData);
					Ret=true;
					break;
				}
				else{
					CloseHandle(DeviceHandle);
					DeviceHandle=NULL;
					FoundNumber++;
				}

			} //if (Attributes.ProductID == ProductID)

			else{
				//The Product ID doesn't match.
				CloseHandle(DeviceHandle);
				DeviceHandle=NULL;
			}

			//Free the memory used by the detailData structure (no longer needed).
			free(detailData);

		}  //if (Result != 0)

		else{
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
			LastDevice=TRUE;
		}
		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.

		MemberIndex = MemberIndex + 1;

	}while ((LastDevice == false) && (Opened == false));

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return Ret;
}

void HidCommandArm::RegisterForDeviceNotifications(void)
{

	// Request to receive messages when a device is attached or removed.
	// Also see WM_DEVICECHANGE in BEGIN_MESSAGE_MAP(CUsbhidiocDlg, CDialog).

	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;

	DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
	DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;

	DeviceNotificationHandle =
		RegisterDeviceNotification((HANDLE)Parent->winId(), &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

}

void HidCommandArm::PrepareForOverlappedTransfer()
{
	//Get a handle to the device for the overlapped ReadFiles.

	ReadHandle=CreateFile 
		(detailData->DevicePath, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);


	//Get an event object for the overlapped structure.

	/*API function: CreateEvent
	Requires:
	  Security attributes or Null
	  Manual reset (true). Use ResetEvent to set the event object's state to non-signaled.
	  Initial state (true = signaled) 
	  Event object name (optional)
	Returns: a handle to the event object
	*/

	if (hEventObject == 0){
		hEventObject = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			L"");

		//Set the members of the overlapped structure.

		HIDOverlapped.hEvent = hEventObject;
		HIDOverlapped.Offset = 0;
		HIDOverlapped.OffsetHigh = 0;
	}
}
void HidCommandArm::GetDeviceCapabilities()
{
	//Get the Capabilities structure for the device.

	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/

	HidD_GetPreparsedData 
		(DeviceHandle, 
		&PreparsedData);

	/*
	API function: HidP_GetCaps
	Learn the device's capabilities.
	For standard devices such as joysticks, you can find out the specific
	capabilities of the device.
	For a custom device, the software will probably know what the device is capable of,
	and the call only verifies the information.
	Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
	Returns: a Capabilities structure containing the information.
	*/
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities);

	HidD_FreePreparsedData(PreparsedData);
}

bool	HidCommandArm::CloseHid(void)
{
	if(DeviceNotificationHandle!=NULL){
		UnregisterDeviceNotification(DeviceNotificationHandle);
		DeviceNotificationHandle=NULL;
	}
	if (DeviceHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(DeviceHandle);
		DeviceHandle=0;
		}

	if (ReadHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(ReadHandle);
		ReadHandle=0;
		}

	if (WriteHandle != INVALID_HANDLE_VALUE)
		{
		CloseHandle(WriteHandle);
		WriteHandle=0;
		}
	Opened=false;
	return true;
}
bool	HidCommandArm::IsOpened(void)
{
	return Opened;
}

bool	HidCommandArm::SendStr(BYTE *Data ,int Len)
{
	DWORD		BytesWritten = 0;
	char		OutputReport[256];
	BOOL		Result=false;

	//The first byte is the report number.
	OutputReport[0]=0;
	memcpy(&OutputReport[1],Data,Len);

	if(WriteHandle != INVALID_HANDLE_VALUE){
		Result = WriteFile (WriteHandle, 
							OutputReport, 
							Capabilities.OutputReportByteLength, 
							&BytesWritten, 
							NULL);
	}
	if (!Result){
		return false;
	}
	return true;
}
bool	HidCommandArm::ReceiveStr(BYTE *Data ,int &ReceivedLen,int waitmilisec)
{
	LONG		Result;
	DWORD		NumberOfBytesRead=0;
	char		InputReport[256];

	//The first byte is the report number.
	InputReport[0]=0;

	if (ReadHandle != INVALID_HANDLE_VALUE){
		Result = ReadFile (ReadHandle, 
							InputReport, 
							Capabilities.InputReportByteLength, 
							&NumberOfBytesRead,
							(LPOVERLAPPED) &HIDOverlapped); 
	}
	memcpy(Data,&InputReport[1],Capabilities.InputReportByteLength-1);

	/*API call:WaitForSingleObject
	'Used with overlapped ReadFile.
	'Returns when ReadFile has received the requested amount of data or on timeout.
	'Requires an event object created with CreateEvent
	'and a timeout value in milliseconds.
	*/

	Result = WaitForSingleObject (hEventObject,waitmilisec);
	bool	Ret=false;
 
	switch (Result){
		case WAIT_OBJECT_0:
			Ret=true;
			break;
		case WAIT_TIMEOUT:
			Ret=false;
			Result = CancelIo(ReadHandle);
			break;
		default:
			Ret=false;
			break;
	}
	ResetEvent(hEventObject);

	return Ret;
}



