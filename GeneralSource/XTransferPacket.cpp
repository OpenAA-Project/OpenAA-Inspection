/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTransferPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XTransferInterface.h"
#include "XTransfer.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "swap.h"
#include "XDateTime.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XGUIFormBase.h"
#include "XDataAlgorithm.h"

GUICmdReqImageCheckByte::GUICmdReqImageCheckByte(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	MasterMode=true;
}
bool	GUICmdReqImageCheckByte::Save(QIODevice *f)
{
	if(::Save(f, MasterMode) == false)
		return false;
	return true;
}
bool	GUICmdReqImageCheckByte::Load(QIODevice *f)
{
	if(::Load(f, MasterMode) == false)
		return false;
	return true;
}
void	GUICmdReqImageCheckByte::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GUICmdAckImageCheckByte *SendBack=GetSendBack(GUICmdAckImageCheckByte, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	for(int phase=0;phase < GetPhaseNumb();phase++) {
		PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(phase);
		DataInPage *Pg=Ph->GetPageData(localPage);
		for(int Layer=0;Layer < Pg->GetLayerNumb();Layer++) {
			DataInLayer *Ly=Pg->GetLayerData(Layer);
			DWORD	Src;
			if(MasterMode == true) {
				Src=Ly->GetMasterBuff().MakeCheckByte();
			}
			else {
				Src=Ly->GetTargetBuff().MakeCheckByte();
			}
			PhasePageLayerD *d=new PhasePageLayerD();
			d->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			d->Phase=phase;
			d->Layer=Layer;
			d->ImageCheckData=Src;
			SendBack->CheckData.AppendList(d);
		}
	}

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}

GUICmdAckImageCheckByte::GUICmdAckImageCheckByte(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}


bool	GUICmdAckImageCheckByte::Save(QIODevice *f)
{
	if(CheckData.Save(f) == false)
		return false;
	return true;
}

bool	GUICmdAckImageCheckByte::Load(QIODevice *f)
{
	if(CheckData.Load(f) == false)
		return false;
	return true;
}

//-------------------------------------------

GUICmdReqImageMixTransfer::GUICmdReqImageMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	Phase=-1;
	Layer=1;
	TopY=-1;
	BundleCount=0;
	MasterMode=true;
}

bool	GUICmdReqImageMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, MasterMode) == false)
		return false;
	if(::Save(f, Phase) == false)
		return false;
	if(::Save(f, Layer) == false)
		return false;
	if(::Save(f, TopY) == false)
		return false;
	if(::Save(f, BundleCount) == false)
		return false;
	return true;
}

bool	GUICmdReqImageMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, MasterMode) == false)
		return false;
	if(::Load(f, Phase) == false)
		return false;
	if(::Load(f, Layer) == false)
		return false;
	if(::Load(f, TopY) == false)
		return false;
	if(::Load(f, BundleCount) == false)
		return false;
	return true;
}

void	GUICmdReqImageMixTransfer::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GUICmdAckImageMixTransfer *SendBack=GetSendBack(GUICmdAckImageMixTransfer, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(Ph != NULL) {
		DataInPage *Pg=Ph->GetPageData(localPage);
		if(Pg != NULL) {
			DataInLayer *Ly=Pg->GetLayerData(Layer);
			if(Ly != NULL) {
				SendBack->BundleCount=(TopY + BundleCount < Pg->GetMaxLines())?BundleCount:Pg->GetMaxLines() - TopY;
				SendBack->Len=0;
				SendBack->Data=new BYTE[Pg->GetDotPerLine() * SendBack->BundleCount];
				BYTE *fp=SendBack->Data;
				for(int n=0;n < SendBack->BundleCount;n++) {
					BYTE *s;
					if(MasterMode == true) {
						s=Ly->GetMasterBuff().GetY(TopY + n);
					}
					else {
						s=Ly->GetTargetBuff().GetY(TopY + n);
					}
					memcpy(fp, s, Pg->GetDotPerLine());
					fp+=Pg->GetDotPerLine();
					SendBack->Len+=Pg->GetDotPerLine();
				}
			}
		}
	}

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}


GUICmdAckImageMixTransfer::GUICmdAckImageMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	Data=NULL;
	Len=0;
}
GUICmdAckImageMixTransfer::~GUICmdAckImageMixTransfer(void)
{
	if(Data != NULL) {
		delete	Data;
	}
	Data=NULL;
	Len=0;
}

bool	GUICmdAckImageMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, Len) == false)
		return false;
	if(::Save(f, BundleCount) == false)
		return false;
	if(f->write((const char *)Data, Len) != Len)
		return false;
	return true;
}
bool	GUICmdAckImageMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, Len) == false)
		return false;
	if(::Load(f, BundleCount) == false)
		return false;
	if(Data != NULL) {
		delete[]Data;
	}
	Data=new BYTE[Len];
	if(f->read((char *)Data, Len) != Len)
		return false;
	return true;
}

//-------------------------------------------

GUICmdSndImageMixTransfer::GUICmdSndImageMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
	Data=NULL;
	Len=0;
	MasterMode=true;
}
GUICmdSndImageMixTransfer::~GUICmdSndImageMixTransfer(void)
{
	if(Data != NULL) {
		delete	Data;
	}
	Data=NULL;
	Len=0;
}
bool	GUICmdSndImageMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, MasterMode) == false)
		return false;
	if(::Save(f, Phase) == false)
		return false;
	if(::Save(f, Layer) == false)
		return false;
	if(::Save(f, TopY) == false)
		return false;
	if(::Save(f, Len) == false)
		return false;
	if(::Save(f, BundleCount) == false)
		return false;
	if(::Save(f, DotPerLine) == false)
		return false;
	if(::Save(f, MaxLines) == false)
		return false;
	if(f->write((const char *)Data, Len) != Len)
		return false;
	return true;
}
bool	GUICmdSndImageMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, MasterMode) == false)
		return false;
	if(::Load(f, Phase) == false)
		return false;
	if(::Load(f, Layer) == false)
		return false;
	if(::Load(f, TopY) == false)
		return false;
	if(::Load(f, Len) == false)
		return false;
	if(::Load(f, BundleCount) == false)
		return false;
	if(::Load(f, DotPerLine) == false)
		return false;
	if(::Load(f, MaxLines) == false)
		return false;
	if(Data != NULL) {
		delete[]Data;
	}
	Data=new BYTE[Len];
	if(f->read((char *)Data, Len) != Len)
		return false;
	return true;
}

void	GUICmdSndImageMixTransfer::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(Ph != NULL) {
		DataInPage *Pg=Ph->GetPageData(localPage);
		if(Pg != NULL) {
			DataInLayer *Ly=Pg->GetLayerData(Layer);
			if(Ly != NULL) {
				int	tBundleCount=(TopY + BundleCount < Pg->GetMaxLines())?BundleCount:Pg->GetMaxLines() - TopY;
				BYTE *fp=Data;
				for(int n=0;n < tBundleCount;n++) {
					BYTE *d;
					if((TopY + n)<Ly->GetMaxLines()){
						if(MasterMode == true) {
							d=Ly->GetMasterBuff().GetY(TopY + n);
						}
						else {
							d=Ly->GetTargetBuff().GetY(TopY + n);
						}
						memcpy(d, fp, min(Pg->GetDotPerLine(),DotPerLine));
					}
					fp+=DotPerLine;
				}
			}
		}
	}
}

//-------------------------------------------

GUICmdReqAlgoDataMixTransfer::GUICmdReqAlgoDataMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdReqAlgoDataMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, AlgoRoot) == false)
		return false;
	if(::Save(f, AlgoName) == false)
		return false;
	return true;
}

bool	GUICmdReqAlgoDataMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, AlgoRoot) == false)
		return false;
	if(::Load(f, AlgoName) == false)
		return false;
	return true;
}

void	GUICmdReqAlgoDataMixTransfer::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GUICmdAckAlgoDataMixTransfer *SendBack=GetSendBack(GUICmdAckAlgoDataMixTransfer, GetLayersBase(), EmitterRoot, EmitterName, localPage);

	QBuffer	TxBuff;
	TxBuff.open(QIODevice::WriteOnly);

	::Save(&TxBuff, (int32)GetPhaseNumb());

	AlgorithmBase *ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot, AlgoName);
	for(int Phase=0;Phase < GetPhaseNumb();Phase++) {
		AlgorithmInPageInOnePhase *APhase=ABase->GetPageDataPhase(Phase);
		if(APhase != NULL) {
			AlgorithmInPageRoot *Ap=APhase->GetPageData(localPage);
			Ap->Save(&TxBuff);
		}
	}
	SendBack->Data=TxBuff.buffer();

	SendBack->Send(this, GetLayersBase()->GetGlobalPageFromLocal(localPage), 0);
	CloseSendBack(SendBack);
}

GUICmdAckAlgoDataMixTransfer::GUICmdAckAlgoDataMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdAckAlgoDataMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, Data) == false)
		return false;
	return true;
}

bool	GUICmdAckAlgoDataMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, Data) == false)
		return false;
	return true;
}


GUICmdSndAlgoDataMixTransfer::GUICmdSndAlgoDataMixTransfer(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
	:GUICmdPacketBase(Base, EmitterRoot, EmitterName, typeid(this).name(), globalPage)
{
}

bool	GUICmdSndAlgoDataMixTransfer::Save(QIODevice *f)
{
	if(::Save(f, AlgoRoot) == false)
		return false;
	if(::Save(f, AlgoName) == false)
		return false;
	if(::Save(f, Data) == false)
		return false;
	return true;
}

bool	GUICmdSndAlgoDataMixTransfer::Load(QIODevice *f)
{
	if(::Load(f, AlgoRoot) == false)
		return false;
	if(::Load(f, AlgoName) == false)
		return false;
	if(::Load(f, Data) == false)
		return false;
	return true;
}

void	GUICmdSndAlgoDataMixTransfer::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	QBuffer	TxBuff;
	TxBuff.open(QIODevice::ReadOnly);

	int32	tPhaseNumb;
	if(::Load(&TxBuff, tPhaseNumb) == false)
		return;

	AlgorithmBase *ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot, AlgoName);
	for(int Phase=0;Phase < GetPhaseNumb() && Phase < tPhaseNumb;Phase++) {
		AlgorithmInPageInOnePhase *APhase=ABase->GetPageDataPhase(Phase);
		if(APhase != NULL) {
			AlgorithmInPageRoot *Ap=APhase->GetPageData(localPage);
			Ap->Load(&TxBuff);
		}
	}
}