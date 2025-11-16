#include "DeviceStruct.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QIODevice>


bool    KDSBeltPIOFixedStruct::Save(QIODevice *f)
{
    int32   Ver=1;

    if(::Save(f,Ver)==false)
        return false;

	if(::Save(f, MulInput)==false)
		return false;

	if(::Save(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Save(f, TriggerFilterMinON)==false)
		return false;

    return true;
}

bool    KDSBeltPIOFixedStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

    if(::Load(f, MulInput)==false)
		return false;
	if(::Load(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Load(f, TriggerFilterMinON)==false)
		return false;

    return true;
}


bool    KDSBeltPIOStruct::Save(QIODevice *f)
{
    if(KDSBeltPIOFixedData.Save(f)==false)
		return false;
    return true;
}

bool    KDSBeltPIOStruct::Load(QIODevice *f)
{
    if(KDSBeltPIOFixedData.Load(f)==false)
		return false;
    return true;
}

