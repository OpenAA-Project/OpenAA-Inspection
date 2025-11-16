#include "DeviceStruct.h"
#include "NListRPi.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"


bool    EOIStruct::Save(QIODevice *f)
{
    int32   Ver=2;

    if(::Save(f,Ver)==false)
        return false;

    if(::Save(f, Conveyer1Pulse)==false)
        return false;
    if(::Save(f, MulInput)==false)
        return false;
    if(::Save(f,DelayFrameTriggerA)==false)
        return false;
    if(::Save(f,DelayFrameTriggerB)==false)
        return false;
    if(::Save(f,FrameCycle)==false)
        return false;
    if(::Save(f,DropLength)==false)
        return false;
    if(::Save(f,DropFlapONLength)==false)
        return false;
    return true;
}

bool    EOIStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

    if(::Load(f, Conveyer1Pulse)==false)
        return false;
    if(::Load(f, MulInput)==false)
        return false;
    if(::Load(f,DelayFrameTriggerA)==false)
        return false;
    if(::Load(f,DelayFrameTriggerB)==false)
        return false;
    if(::Load(f,FrameCycle)==false)
        return false;
    if(::Load(f,DropLength)==false)
        return false;
    if(::Load(f,DropFlapONLength)==false)
        return false;
    return true;
}


