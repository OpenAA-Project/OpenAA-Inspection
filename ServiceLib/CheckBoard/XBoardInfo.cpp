#include<CheckBoard.h>


#include <windows.h>
#include <devguid.h>
#include <devpkey.h>
#include <setupapi.h>
//#define INITGUID
#include <pciprop.h>
#include <regstr.h>
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <iomanip>
#include <cfgmgr32.h>
#include <sstream>


// setupapi.lib をリンクする指示（MSVC用）
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "cfgmgr32.lib")

static const GUID GUID_PciDevice = { 0x4340a6c5, 0x93fa, 0x4706, { 0x97, 0x2c, 0x7b, 0x64, 0x80, 0x08, 0xa5, 0xa7 } };

// PID (Property ID)
//static const DEVPROPID PID_PciDevice_CurrentLinkSpeed = 9;
//static const DEVPROPID PID_PciDevice_CurrentLinkWidth = 10;



// PCI Gen速度を読みやすい文字列に変換するヘルパー関数
std::wstring GetPciGenSpeedString(UINT32 speedCode) {
    switch (speedCode) {
    case 1: return L"2.5 GT/s (Gen1)";
    case 2: return L"5.0 GT/s (Gen2)";
    case 3: return L"8.0 GT/s (Gen3)";
    case 4: return L"16.0 GT/s (Gen4)";
    case 5: return L"32.0 GT/s (Gen5)"; // 将来的な拡張
    case 6: return L"64.0 GT/s (Gen6)"; 
    default: return L"Unknown (" + std::to_wstring(speedCode) + L")";
    }
}

// SetupAPIを使ってデバイスプロパティを取得するヘルパー関数
template <typename T>
bool GetDeviceProperty(HDEVINFO hDevInfo, PSP_DEVINFO_DATA pDevInfoData, const DEVPROPKEY* propKey, T& outValue) {
    DEVPROPTYPE propType;
    DWORD requiredSize = 0;
    
    // まずサイズを取得
    SetupDiGetDevicePropertyW(hDevInfo, pDevInfoData, propKey, &propType, NULL, 0, &requiredSize, 0);

    if (requiredSize == 0) return false;

    std::vector<BYTE> buffer(requiredSize);
    if (!SetupDiGetDevicePropertyW(hDevInfo, pDevInfoData, propKey, &propType, buffer.data(), requiredSize, NULL, 0)) {
        return false;
    }

    // 型チェックと値のコピー
    if (sizeof(T) <= requiredSize) {
        memcpy(&outValue, buffer.data(), sizeof(T));
        return true;
    }
    return false;
}

bool CheckBoard::GetBoardInfo(NPListPack<BoardInfoList> &BoardInfo)
{
    HDEVINFO hDevInfo = SetupDiGetClassDevs(
        NULL,
        L"PCI", 
        NULL,
        DIGCF_PRESENT | DIGCF_ALLCLASSES
    );

    if (hDevInfo == INVALID_HANDLE_VALUE) {
        return false;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // デバイスを列挙するループ
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &deviceInfoData); i++) {
        DWORD dataT;
        wchar_t buffer[2048]; // 情報を格納するバッファ
        DWORD buffersize = sizeof(buffer);

        // 1. デバイスの説明（フレンドリーネーム）を取得
        // まずは FriendlyName (SPDRP_FRIENDLYNAME) を試みる
        if (!SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &deviceInfoData,
            SPDRP_FRIENDLYNAME,
            &dataT,
            (PBYTE)buffer,
            buffersize,
            NULL)) {
            
            // FriendlyNameがない場合は DeviceDesc (SPDRP_DEVICEDESC) を取得
            if (!SetupDiGetDeviceRegistryProperty(
                hDevInfo,
                &deviceInfoData,
                SPDRP_DEVICEDESC,
                &dataT,
                (PBYTE)buffer,
                buffersize,
                NULL)) {
                wcscpy_s(buffer, L"Unknown");
            }
        }
        std::wstring deviceName = buffer;

        // 2. ハードウェアIDを取得
        std::wstring hardwareID = L"";
        if (SetupDiGetDeviceRegistryProperty(
            hDevInfo,
            &deviceInfoData,
            SPDRP_HARDWAREID,
            &dataT,
            (PBYTE)buffer,
            buffersize,
            NULL)) {
            // ハードウェアIDは通常複数行の文字列（MULTI_SZ）ですが、最初の1つだけ取得して表示します
            hardwareID = buffer;
        }

        // リンク速度 (CurrentLinkSpeed) を取得
        UINT32 linkSpeed;
        ULONG size;
		DEVPROPTYPE propType;
        size = sizeof(linkSpeed);
        if (CM_Get_DevNode_PropertyW(deviceInfoData.DevInst, &DEVPKEY_PciDevice_CurrentLinkSpeed,
                                     &propType, (PBYTE)&linkSpeed, &size, 0) != CR_SUCCESS
            || propType != DEVPROP_TYPE_UINT32) {
            continue;
        }
        // リンク幅 (CurrentLinkWidth) を取得
        UINT32 linkWidth;
        size = sizeof(linkWidth);
        if (CM_Get_DevNode_PropertyW(deviceInfoData.DevInst, &DEVPKEY_PciDevice_CurrentLinkWidth,
                                     &propType, (PBYTE)&linkWidth, &size, 0) != CR_SUCCESS
            || propType != DEVPROP_TYPE_UINT32) {
            continue;
        }
        
		BoardInfoList *List = new BoardInfoList();
		List->BoardName = QString::fromStdWString(deviceName);
        List->HardwareID=QString::fromStdWString(hardwareID);
		List->LinkWidth = static_cast<int>(linkWidth);

		BoardInfo.AppendList(List);
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);

	return true;
}