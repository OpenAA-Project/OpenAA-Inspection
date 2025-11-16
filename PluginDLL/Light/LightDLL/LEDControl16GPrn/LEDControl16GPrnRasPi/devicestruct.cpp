#include "DeviceStruct.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QIODevice>


bool    GioFixedStruct::Save(QIODevice *f)
{
    int32   Ver=4;

    if(::Save(f,Ver)==false)
        return false;

	if(::Save(f, ConveyerLength)==false)
		return false;
	if(::Save(f, GateOpenTerm)==false)
		return false;
	if(::Save(f, MulInputA)==false)
		return false;
	if(::Save(f, MulInputB)==false)
		return false;
	if(::Save(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Save(f, TriggerFilterMinON)==false)
		return false;
	if(::Save(f, DelayFrameTriggerA)==false)
		return false;
	if(::Save(f, DelayFrameTriggerB)==false)
		return false;
	if(::Save(f, DelayFrameTriggerC)==false)
		return false;
	if(::Save(f, DelayFrameTriggerD)==false)
		return false;
    if(::Save(f, DefDelayedCount)==false)
		return false;
    
    if(::Save(f,TriggerDelayParameter)==false)
        return false;

    if(::Save(f,FlipFrameTriggerModeA)==false)
        return false;
    if(::Save(f,FlipFrameTriggerModeB)==false)
        return false;
    if(::Save(f,FlipFrameTriggerModeC)==false)
        return false;
    if(::Save(f,FlipFrameTriggerModeD)==false)
        return false;

    if(::Save(f,ResultOutParameter)==false)
        return false;
    return true;
}

bool    GioFixedStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false)
        return false;

	if(::Load(f, ConveyerLength)==false)
		return false;
	if(::Load(f, GateOpenTerm)==false)
		return false;
	if(::Load(f, MulInputA)==false)
		return false;
	if(::Load(f, MulInputB)==false)
		return false;
	if(::Load(f, TriggerFilterMinOFF)==false)
		return false;
	if(::Load(f, TriggerFilterMinON)==false)
		return false;
	if(::Load(f, DelayFrameTriggerA)==false)
		return false;
	if(::Load(f, DelayFrameTriggerB)==false)
		return false;
	if(::Load(f, DelayFrameTriggerC)==false)
		return false;
	if(::Load(f, DelayFrameTriggerD)==false)
		return false;
    if(::Load(f, DefDelayedCount)==false)
		return false;
    
    if(::Load(f,TriggerDelayParameter)==false)
        return false;

    if(Ver>=3){
        if(::Load(f,FlipFrameTriggerModeA)==false)
            return false;
        if(::Load(f,FlipFrameTriggerModeB)==false)
            return false;
        if(::Load(f,FlipFrameTriggerModeC)==false)
            return false;
        if(::Load(f,FlipFrameTriggerModeD)==false)
            return false;
    }
    if(Ver>=4){
        if(::Load(f,ResultOutParameter)==false)
            return false;
    }
    return true;
}


bool    GioStruct::Save(QIODevice *f)
{
	if(GioFixedData.Save(f)==false)
		return false;
    return true;
}

bool    GioStruct::Load(QIODevice *f)
{
	if(GioFixedData.Load(f)==false)
		return false;
    return true;
}

