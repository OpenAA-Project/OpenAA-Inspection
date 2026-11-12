#pragma once

#pragma pack(push, 1)

#include "XCommunicationData.h"
struct  SocketPacket
{
    unsigned char   Command;    //1:Set light   2;Set Output    3:Set trigger   4:Get information

    struct CommDataCam1BMoSi    Data1;
    struct CommDataCam1BMiSo    Data2;
};

#pragma pack(pop)
