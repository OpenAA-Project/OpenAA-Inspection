#include "DeviceStruct.h"
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include <QIODevice>


bool    JioFixedStruct::Save(QIODevice *f)
{
    int32   Ver=7;

    if(::Save(f,Ver)==false){
        return false;
	}

	if(::Save(f, ConveyerLength)==false)
		return false;
	if(::Save(f, GateOpenTerm)==false)
		return false;
	if(::Save(f, MulInputA)==false)
		return false;
	if(::Save(f, MulInputB)==false)
		return false;
    if(::Save(f, MulInputC)==false)
        return false;
    if(::Save(f, MulInputD)==false)
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
	if(::Save(f, ResultAAcceptStart)==false)
		return false;
	if(::Save(f, ResultBAcceptStart)==false)
		return false;
	if(::Save(f, ResultCAcceptStart)==false)
		return false;
	if(::Save(f, ResultDAcceptStart)==false)
		return false;
	if(::Save(f, ResultACloseAccept)==false)
		return false;
	if(::Save(f, ResultBCloseAccept)==false)
		return false;
	if(::Save(f, ResultCCloseAccept)==false)
		return false;
	if(::Save(f, ResultDCloseAccept)==false)
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

    if(::Save(f, TriggerFilterWorkLen)==false)
        return false;
    if(::Save(f, DelayedCountForStack)==false)
        return false;
    if(::Save(f, ModeOutResultError)==false)
        return false;

    return true;
}

bool    JioFixedStruct::Load(QIODevice *f)
{
    int32   Ver;

    if(::Load(f,Ver)==false){
        return false;
	}

	if(::Load(f, ConveyerLength)==false)
		return false;
	if(::Load(f, GateOpenTerm)==false)
		return false;
	if(::Load(f, MulInputA)==false)
		return false;
	if(::Load(f, MulInputB)==false)
		return false;
    if(::Load(f, MulInputC)==false)
        return false;
    if(::Load(f, MulInputD)==false)
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
	if(::Load(f, ResultAAcceptStart)==false)
		return false;
	if(::Load(f, ResultBAcceptStart)==false)
		return false;
	if(::Load(f, ResultCAcceptStart)==false)
		return false;
	if(::Load(f, ResultDAcceptStart)==false)
		return false;
	if(::Load(f, ResultACloseAccept)==false)
		return false;
	if(::Load(f, ResultBCloseAccept)==false)
		return false;
	if(::Load(f, ResultCCloseAccept)==false)
		return false;
	if(::Load(f, ResultDCloseAccept)==false)
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
    if(Ver>=5){
        if(::Load(f, TriggerFilterWorkLen)==false)
            return false;
    }
    if(Ver>=6){
        if(::Load(f, DelayedCountForStack)==false)
            return false;
    }
    if(Ver>=7){
        if(::Load(f, ModeOutResultError)==false)
            return false;
    }
    return true;
}


bool    JioStruct::Save(QIODevice *f)
{
    if(JioFixedData.Save(f)==false)
		return false;

    for(int i=0;i<sizeof(AllocateGOut)/sizeof(AllocateGOut[0]);i++){
        if(::Save(f,AllocateGOut[i])==false)
            return false;
    }
    return true;
}

bool    JioStruct::Load(QIODevice *f)
{
    if(JioFixedData.Load(f)==false)
		return false;

    for(int i=0;i<sizeof(AllocateGOut)/sizeof(AllocateGOut[0]);i++){
        if(::Load(f,AllocateGOut[i])==false)
            return false;
    }
    return true;
}

