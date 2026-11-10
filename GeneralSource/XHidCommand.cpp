/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* XHidCommand.cpp */
#include "XHidCommand.h"
#include <QtGlobal>

// =========================================================================
// Windows Implementation
// =========================================================================
#if defined(Q_OS_WIN)

extern "C" {
#include <Windows.h>
#include <hidsdi.h>
#include <setupapi.h>
#include <dbt.h>
}

class HidCommandArm : public HidCommand
{
    bool        Opened;
    GUID        HidGuid;
    HANDLE      DeviceHandle;
    HANDLE      ReadHandle;
    HANDLE      WriteHandle;
    HIDP_CAPS   Capabilities;
    PSP_DEVICE_INTERFACE_DETAIL_DATA detailData;
    HANDLE      hEventObject;
    OVERLAPPED  HIDOverlapped;
    HDEVNOTIFY  DeviceNotificationHandle;
public:
    HidCommandArm(QWidget *parent);
    virtual ~HidCommandArm(void);

    virtual bool OpenHid(int Vid, int Pid, int Number);
    virtual bool CloseHid(void);
    virtual bool IsOpened(void);

    virtual bool SendStr(BYTE *Data, int Len);
    virtual bool ReceiveStr(BYTE *Data, int &ReceivedLen, int waitmilisec=6000);

private:
    void RegisterForDeviceNotifications(void);
    void GetDeviceCapabilities();
    void PrepareForOverlappedTransfer();
};

HidCommandArm::HidCommandArm(QWidget *parent)
    : HidCommand(parent)
{
    Opened = false;
    DeviceHandle = 0;
    ReadHandle = 0;
    WriteHandle = 0;
    hEventObject = 0;
    DeviceNotificationHandle = NULL;
}

HidCommandArm::~HidCommandArm(void)
{
    CloseHid();
}

bool HidCommandArm::OpenHid(int VendorID, int ProductID, int Number)
{
    HIDD_ATTRIBUTES Attributes;
    DWORD DeviceUsage;
    SP_DEVICE_INTERFACE_DATA devInfoData;
    bool LastDevice = false;
    int MemberIndex = 0;
    LONG Result;
    ULONG Length = 0;
    HANDLE hDevInfo;
    ULONG Required;
    bool Ret = false;
    int FoundNumber = 0;

    Opened = false;
    detailData = NULL;
    DeviceHandle = NULL;

    HidD_GetHidGuid(&HidGuid);

    hDevInfo = SetupDiGetClassDevs(&HidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    devInfoData.cbSize = sizeof(devInfoData);
    MemberIndex = 0;
    LastDevice = false;

    do {
        Result = SetupDiEnumDeviceInterfaces(hDevInfo, 0, &HidGuid, MemberIndex, &devInfoData);
        if (Result != 0) {
            Result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, NULL, 0, &Length, NULL);
            detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
            detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
            Result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, detailData, Length, &Required, NULL);

            DeviceHandle = CreateFile(detailData->DevicePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, NULL);
            Attributes.Size = sizeof(Attributes);
            Result = HidD_GetAttributes(DeviceHandle, &Attributes);

            if (Attributes.VendorID == VendorID && Attributes.ProductID == ProductID) {
                if (FoundNumber == Number) {
                    Opened = true;
                    RegisterForDeviceNotifications();
                    GetDeviceCapabilities();
                    DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;
                    WriteHandle = CreateFile(detailData->DevicePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, 0, NULL);
                    PrepareForOverlappedTransfer();
                    free(detailData);
                    Ret = true;
                    break;
                } else {
                    CloseHandle(DeviceHandle);
                    DeviceHandle = NULL;
                    FoundNumber++;
                }
            } else {
                CloseHandle(DeviceHandle);
                DeviceHandle = NULL;
            }
            free(detailData);
        } else {
            LastDevice = TRUE;
        }
        MemberIndex = MemberIndex + 1;
    } while ((LastDevice == false) && (Opened == false));

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return Ret;
}

void HidCommandArm::RegisterForDeviceNotifications(void)
{
    DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
    DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
    DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;
    DeviceNotificationHandle = RegisterDeviceNotification((HANDLE)Parent->winId(), &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);
}

void HidCommandArm::PrepareForOverlappedTransfer()
{
    ReadHandle = CreateFile(detailData->DevicePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (hEventObject == 0) {
        hEventObject = CreateEvent(NULL, TRUE, TRUE, L"");
        HIDOverlapped.hEvent = hEventObject;
        HIDOverlapped.Offset = 0;
        HIDOverlapped.OffsetHigh = 0;
    }
}

void HidCommandArm::GetDeviceCapabilities()
{
    PHIDP_PREPARSED_DATA PreparsedData;
    HidD_GetPreparsedData(DeviceHandle, &PreparsedData);
    HidP_GetCaps(PreparsedData, &Capabilities);
    HidD_FreePreparsedData(PreparsedData);
}

bool HidCommandArm::CloseHid(void)
{
    if (DeviceNotificationHandle != NULL) {
        UnregisterDeviceNotification(DeviceNotificationHandle);
        DeviceNotificationHandle = NULL;
    }
    if (DeviceHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(DeviceHandle);
        DeviceHandle = 0;
    }
    if (ReadHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(ReadHandle);
        ReadHandle = 0;
    }
    if (WriteHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(WriteHandle);
        WriteHandle = 0;
    }
    Opened = false;
    return true;
}

bool HidCommandArm::IsOpened(void)
{
    return Opened;
}

bool HidCommandArm::SendStr(BYTE *Data, int Len)
{
    DWORD BytesWritten = 0;
    char OutputReport[256];
    BOOL Result = false;

    OutputReport[0] = 0;
    memcpy(&OutputReport[1], Data, Len);

    if (WriteHandle != INVALID_HANDLE_VALUE) {
        Result = WriteFile(WriteHandle, OutputReport, Capabilities.OutputReportByteLength, &BytesWritten, NULL);
    }
    return Result != FALSE;
}

bool HidCommandArm::ReceiveStr(BYTE *Data, int &ReceivedLen, int waitmilisec)
{
    LONG Result;
    DWORD NumberOfBytesRead = 0;
    char InputReport[256];

    InputReport[0] = 0;
    if (ReadHandle != INVALID_HANDLE_VALUE) {
        Result = ReadFile(ReadHandle, InputReport, Capabilities.InputReportByteLength, &NumberOfBytesRead, (LPOVERLAPPED)&HIDOverlapped);
    }

    Result = WaitForSingleObject(hEventObject, waitmilisec);
    bool Ret = false;

    switch (Result) {
    case WAIT_OBJECT_0:
        memcpy(Data, &InputReport[1], Capabilities.InputReportByteLength - 1);
        Ret = true;
        break;
    case WAIT_TIMEOUT:
        Ret = false;
        CancelIo(ReadHandle);
        break;
    default:
        Ret = false;
        break;
    }
    ResetEvent(hEventObject);
    return Ret;
}

// =========================================================================
// Linux / Raspberry Pi Implementation
// =========================================================================
#elif defined(Q_OS_LINUX) || defined(Q_OS_UNIX)

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <linux/hidraw.h>
#include <sys/ioctl.h>
#include <cstring>

class HidCommandArm : public HidCommand
{
    bool Opened;
    int fd;

public:
    HidCommandArm(QWidget *parent) : HidCommand(parent), Opened(false), fd(-1) {}
    virtual ~HidCommandArm(void) { CloseHid(); }

    bool OpenHid(int Vid, int Pid, int Number) override
    {
        CloseHid();
        QDir dir("/sys/class/hidraw");
        if (!dir.exists()) return false;

        int FoundNumber = 0;
        QStringList filters;
        filters << "hidraw*";
        QFileInfoList list = dir.entryInfoList(filters, QDir::Dirs | QDir::NoDotAndDotDot);

        for (const QFileInfo &info : list) {
            QFile ueventFile(info.absoluteFilePath() + "/device/uevent");
            if (ueventFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&ueventFile);
                QString line;
                bool match = false;
                
                while (in.readLineInto(&line)) {
                    if (line.startsWith("HID_ID=")) {
                        // HID_ID format: BUS:VID:PID (in Hexadecimal)
                        QStringList parts = line.mid(7).split(":");
                        if (parts.size() >= 3) {
                            int currentVid = parts[1].toInt(nullptr, 16);
                            int currentPid = parts[2].toInt(nullptr, 16);
                            if (currentVid == Vid && currentPid == Pid) {
                                match = true;
                                break;
                            }
                        }
                    }
                }
                ueventFile.close();

                if (match) {
                    if (FoundNumber == Number) {
                        QString devPath = QString("/dev/%1").arg(info.fileName());
                        fd = ::open(devPath.toLocal8Bit().constData(), O_RDWR | O_NONBLOCK);
                        if (fd >= 0) {
                            Opened = true;
                            return true;
                        }
                    } else {
                        FoundNumber++;
                    }
                }
            }
        }
        return false;
    }

    bool CloseHid(void) override
    {
        if (fd >= 0) {
            ::close(fd);
            fd = -1;
        }
        Opened = false;
        return true;
    }

    bool IsOpened(void) override { return Opened; }

    bool SendStr(BYTE *Data, int Len) override
    {
        if (!Opened || fd < 0) return false;

        BYTE OutputReport[256];
        OutputReport[0] = 0; // Report ID
        int copyLen = qMin(Len, 255);
        memcpy(&OutputReport[1], Data, copyLen);

        // Send with +1 length (for Report ID) to match Windows behavior.
        // If the HID device only accepts fixed lengths, specify 65, etc.
        ssize_t bytesWritten = ::write(fd, OutputReport, copyLen + 1);
        return (bytesWritten >= 0);
    }

    bool ReceiveStr(BYTE *Data, int &ReceivedLen, int waitmilisec = 6000) override
    {
        if (!Opened || fd < 0) return false;

        struct pollfd pfd;
        pfd.fd = fd;
        pfd.events = POLLIN;

        // Wait for specified milliseconds (Read with timeout)
        int ret = ::poll(&pfd, 1, waitmilisec);
        if (ret > 0 && (pfd.revents & POLLIN)) {
            BYTE InputReport[256];
            ssize_t bytesRead = ::read(fd, InputReport, sizeof(InputReport));
            if (bytesRead > 0) {
                // Skip the first byte as Report ID and return the rest
                int copyLen = qMin((int)bytesRead - 1, 255);
                if (copyLen > 0) {
                    memcpy(Data, &InputReport[1], copyLen);
                    ReceivedLen = copyLen;
                } else {
                    ReceivedLen = 0;
                }
                return true;
            }
        }
        return false;
    }
};

#endif // Q_OS_LINUX

// =========================================================================
// Common Factory Implementation
// =========================================================================

HidCommand::HidCommand(QWidget *parent)
{   
    Parent = parent;
}

HidCommand *HidCommand::Create(QWidget *parent)
{
    // Returns the platform-specific HidCommandArm instance
    return new HidCommandArm(parent);
}
