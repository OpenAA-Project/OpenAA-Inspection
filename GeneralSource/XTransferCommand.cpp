/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XTransferCommand.cpp
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

//=======================================================================================================
MixTransferLeaf *MixTransferComm::CreateNewLeaf(int ID)
{
	return new MixTransferLeaf(ID, this);
}
bool	MixTransferComm::ReqGlobalParam(ParamGlobal &TmpGlobalParam, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	QByteArray	Dummy;
	if(Packet.TxData(CmdMixTransfer_TxReqGlobalParam, &Dummy, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == true && Packet.GetNowCmd() == CmdMixTransfer_RxReqGlobalParam) {
		QBuffer	RBuff(&Packet.Data);
		if(RBuff.open(QIODevice::ReadOnly) == true) {
			if(TmpGlobalParam.LoadParam(&RBuff, -1) == false)
				return false;
			return true;
		}
	}
	return false;
}

bool	MixTransferComm::SndGlobalParam(DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(GetParamGlobal()->SaveParam(&Buff, -1) == false)
		return false;
	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(Packet.TxData(CmdMixTransfer_TxSndGlobalParam, &Buff, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == true && Packet.GetNowCmd() == CmdMixTransfer_RxSndGlobalParam) {
		return true;
	}
	return false;
}

bool	MixTransferComm::ReqMasterData(DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	QByteArray	Dummy;
	if(Packet.TxData(CmdMixTransfer_TxReqMasterDataImageCheckByte, &Dummy, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterDataImageCheckByte) {
		return false;
	}
	QByteArray	R1Data=Packet.Data;
	QBuffer	R1Buff(&R1Data);
	if(R1Buff.open(QIODevice::ReadOnly) == false)
		return false;
	int32	tPageNumb;
	int32	tPhaseNumb;
	int32	tLayerNumb;
	int32	BundleCount;
	int32	tDotPerLine;
	int32	tMaxLines;
	if(::Load(&R1Buff, tPageNumb) == false)
		return false;
	if(::Load(&R1Buff, tPhaseNumb) == false)
		return false;
	if(::Load(&R1Buff, tLayerNumb) == false)
		return false;
	if(::Load(&R1Buff, BundleCount) == false)
		return false;
	if(::Load(&R1Buff, tDotPerLine) == false)
		return false;
	if(::Load(&R1Buff, tMaxLines) == false)
		return false;
	for(int phase=0;phase < GetPhaseNumb() && phase < tPhaseNumb;phase++) {
		PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page < GetPageNumb() && page < tPageNumb;page++) {
			DataInPage *Pg=Ph->GetPageData(page);
			for(int Layer=0;Layer < GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
				DataInLayer *Ly=Pg->GetLayerData(Layer);
				DWORD	Src=Ly->GetMasterBuff().MakeCheckByte();
				DWORD	Dst;
				if(::Load(&R1Buff, Dst) == false)
					return false;
				if(Src != Dst) {
					int	N=(Pg->GetMaxLines() + BundleCount - 1) / BundleCount;
					for(int i=0;i < N;i++) {
						struct	MixTreansferImagePacketInfo	Info;
						Info.Phase	=phase;
						Info.Page	=page;
						Info.Layer	=Layer;
						Info.TopY	=BundleCount * i;
						Info.LineCount=BundleCount;
						Packet.ClearReceived();
						QByteArray	InfoData((const char *)&Info,sizeof(Info));
						if(Packet.TxData(CmdMixTransfer_TxReqMasterDataImage, &InfoData, ErrorData) == false)
							return false;
						Packet.WaitReadyRead(WaitingTime);
						QCoreApplication::processEvents();
						if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterDataImage) {
							return false;
						}
						QBuffer	DBuff(&Packet.Data);
						if(DBuff.open(QIODevice::ReadOnly) == false)
							return false;
						if(DBuff.read((char *)&Info, sizeof(Info)) != sizeof(Info))
							return false;

						GUICmdSndImageMixTransfer	TCmd(GetLayersBase(), "ANY", "ANY", page);
						TCmd.Phase=phase;
						TCmd.Layer=Layer;
						TCmd.TopY=Info.TopY;
						TCmd.BundleCount=Info.LineCount;
						TCmd.Len=Pg->GetDotPerLine() * Info.LineCount;
						TCmd.Data=new BYTE[TCmd.Len];
						DBuff.read((char *)TCmd.Data, TCmd.Len);

						TCmd.Send(NULL, page, 0);
					}
				}
			}
		}
	}

	for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL != NULL;DLL=DLL->GetNext()) {
		for(int32 page=0;page < GetPageNumb();page++) {
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			::Save(&TxBuff, page);
			::Save(&TxBuff, DLL->GetDLLRoot());
			::Save(&TxBuff, DLL->GetDLLName());
			Packet.ClearReceived();
			if(Packet.TxData(CmdMixTransfer_TxReqMasterAlgo, &TxBuff, ErrorData) == false) {
				return false;
			}
			Packet.WaitReadyRead(WaitingTime);
			QCoreApplication::processEvents();
			if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterAlgo) {
				return false;
			}
			GUICmdSndAlgoDataMixTransfer	RCmd(GetLayersBase(), "ANY", "ANY", page);
			RCmd.AlgoRoot=DLL->GetDLLRoot();
			RCmd.AlgoName=DLL->GetDLLName();
			RCmd.Data=Packet.Data;
			RCmd.Send(NULL, page, 0);
		}
	}
	return true;
}

bool	MixTransferComm::SndMasterData(DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	QByteArray	Dummy;
	if(Packet.TxData(CmdMixTransfer_TxReqMasterDataImageCheckByte, &Dummy, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterDataImageCheckByte) {
		return false;
	}
	QByteArray	R1Data=Packet.Data;
	QBuffer	R1Buff(&R1Data);
	if(R1Buff.open(QIODevice::ReadOnly) == false)
		return false;
	int32	tPageNumb;
	int32	tPhaseNumb;
	int32	tLayerNumb;
	int32	BundleCount;
	int32	tDotPerLine;
	int32	tMaxLines;
	if(::Load(&R1Buff, tPageNumb) == false)
		return false;
	if(::Load(&R1Buff, tPhaseNumb) == false)
		return false;
	if(::Load(&R1Buff, tLayerNumb) == false)
		return false;
	if(::Load(&R1Buff, BundleCount) == false)
		return false;
	if(::Load(&R1Buff, tDotPerLine) == false)
		return false;
	if(::Load(&R1Buff, tMaxLines) == false)
		return false;
	for(int phase=0;phase < GetPhaseNumb() && phase < tPhaseNumb;phase++) {
		PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page < GetPageNumb() && page < tPageNumb;page++) {
			DataInPage *Pg=Ph->GetPageData(page);
			for(int Layer=0;Layer < GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
				DataInLayer *Ly=Pg->GetLayerData(Layer);
				DWORD	Src=Ly->GetMasterBuff().MakeCheckByte();
				DWORD	Dst;
				if(::Load(&R1Buff, Dst) == false)
					return false;
				if(Src != Dst) {
					int	LineCount=(1024 * 1024 * 3) / Pg->GetDotPerLine();
					int	N=(Pg->GetMaxLines() + BundleCount - 1) / BundleCount;
					for(int i=0;i < N;i++) {
						GUICmdReqImageMixTransfer	RCmd(GetLayersBase(), "ANY", "ANY", page);
						GUICmdAckImageMixTransfer	SCmd(GetLayersBase(), "ANY", "ANY", page);
						RCmd.Phase=phase;
						RCmd.Layer=Layer;
						RCmd.TopY=BundleCount * i;
						RCmd.BundleCount=LineCount;
						if(RCmd.Send(page, 0, SCmd) == false)
							return false;

						struct	MixTreansferImagePacketInfo	Info;
						Info.Phase=phase;
						Info.Page=page;
						Info.Layer=Layer;
						Info.TopY=RCmd.TopY;
						Info.LineCount=SCmd.BundleCount;

						QBuffer	TxBuff;
						TxBuff.open(QIODevice::WriteOnly);
						TxBuff.write((const char *)&Info, sizeof(Info));
						TxBuff.write((const char *)SCmd.Data, SCmd.Len);

						Packet.ClearReceived();
						if(Packet.TxData(CmdMixTransfer_TxSndMasterDataImage, &TxBuff, ErrorData) == false)
							return false;
						Packet.WaitReadyRead(WaitingTime);
						QCoreApplication::processEvents();
						if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxSndMasterDataImage) {
							return false;
						}
					}
				}
			}
		}
	}

	for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL != NULL;DLL=DLL->GetNext()) {
		for(int32 page=0;page < GetPageNumb();page++) {
			GUICmdReqAlgoDataMixTransfer	RCmd(GetLayersBase(), "ANY", "ANY", page);
			GUICmdAckAlgoDataMixTransfer	SCmd(GetLayersBase(), "ANY", "ANY", page);
			RCmd.AlgoRoot=DLL->GetDLLRoot();
			RCmd.AlgoName=DLL->GetDLLName();
			if(RCmd.Send(page, 0, SCmd) == false) {
				return false;
			}

			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			::Save(&TxBuff, page);
			::Save(&TxBuff, DLL->GetDLLRoot());
			::Save(&TxBuff, DLL->GetDLLName());
			::Save(&TxBuff, SCmd.Data);
			Packet.ClearReceived();
			if(Packet.TxData(CmdMixTransfer_TxSndMasterAlgo, &TxBuff, ErrorData) == false) {
				return false;
			}
			Packet.WaitReadyRead(WaitingTime);
			QCoreApplication::processEvents();
			if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterAlgo) {
				return false;
			}
		}
	}
	return true;
}

bool	MixTransferComm::ReqImageData(bool SrcMasterImage, bool DstMasterImage ,bool ChangeXY, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf	*P=FindLeaf(IPAddress ,Port);
	if(P==NULL){
		P=AddReqConnection(NULL ,IPAddress,Port);
		if(P->StartConnect(WaitingTime) == false){
			delete	P;
			return false;
		}
	}

	ErrorCodeList ErrorData;
	P->ClearReceived();
	if(SrcMasterImage == true) {
		QByteArray	Dummy;
		if(P->TxData(CmdMixTransfer_TxReqMasterDataImageCheckByte, &Dummy, ErrorData) == false)
			return false;
		P->WaitReadyRead(WaitingTime);
		QCoreApplication::processEvents();
		if(P->IsReceived() == false || P->GetNowCmd() != CmdMixTransfer_RxReqMasterDataImageCheckByte) {
			return false;
		}
	}
	else {
		QByteArray	Dummy;
		if(P->TxData(CmdMixTransfer_TxReqTargetDataImageCheckByte, &Dummy, ErrorData) == false)
			return false;
		P->WaitReadyRead(WaitingTime);
		QCoreApplication::processEvents();
		if(P->IsReceived() == false || P->GetNowCmd() != CmdMixTransfer_RxReqTargetDataImageCheckByte) {
			return false;
		}
	}
	QByteArray	R1Data=P->Data;
	QBuffer	R1Buff(&R1Data);
	if(R1Buff.open(QIODevice::ReadOnly) == false)
		return false;
	int32	tPageNumb;
	int32	tPhaseNumb;
	int32	tLayerNumb;
	int32	tDotPerLine;
	int32	tMaxLines;
	int32	BundleCount;
	if(::Load(&R1Buff, tPageNumb) == false)
		return false;
	if(::Load(&R1Buff, tPhaseNumb) == false)
		return false;
	if(::Load(&R1Buff, tLayerNumb) == false)
		return false;
	if(::Load(&R1Buff, BundleCount) == false)
		return false;
	if(::Load(&R1Buff, tDotPerLine) == false)
		return false;
	if(::Load(&R1Buff, tMaxLines) == false)
		return false;
	for(int phase=0;phase < GetPhaseNumb() && phase < tPhaseNumb;phase++) {
		PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page < GetPageNumb() && page < tPageNumb;page++) {
			DataInPage *Pg=Ph->GetPageData(page);
			for(int Layer=0;Layer < GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
				DataInLayer *Ly=Pg->GetLayerData(Layer);
				DWORD	Src=Ly->GetMasterBuff().MakeCheckByte();
				DWORD	Dst;
				if(::Load(&R1Buff, Dst) == false)
					return false;
				if(Src != Dst) {
					int	N=(Pg->GetMaxLines() + BundleCount - 1) / BundleCount;
					for(int i=0;i < N;i++) {
						struct	MixTreansferImagePacketInfo	Info;
						Info.Phase=phase;
						Info.Page=page;
						Info.Layer=Layer;
						Info.TopY=BundleCount * i;
						Info.LineCount=BundleCount;
						QByteArray	InfoData((const char *)&Info,sizeof(Info));
						P->ClearReceived();
						if(SrcMasterImage == true) {
							if(P->TxData(CmdMixTransfer_TxReqMasterDataImage, &InfoData, ErrorData) == false)
								return false;
							do{
								P->WaitReadyRead(WaitingTime);
								QCoreApplication::processEvents();
							}while(P->IsReceived()==false && P->IsReceivedPiece()==true);

							if(P->IsReceived() == false || P->GetNowCmd() != CmdMixTransfer_RxReqMasterDataImage) {
								return false;
							}
						}
						else {
							if(P->TxData(CmdMixTransfer_TxReqTargetDataImage, &InfoData, ErrorData) == false)
								return false;
							do{
								P->WaitReadyRead(WaitingTime);
								QCoreApplication::processEvents();
							}while(P->IsReceived()==false && P->IsReceivedPiece()==true);

							if(P->IsReceived() == false || P->GetNowCmd() != CmdMixTransfer_RxReqTargetDataImage) {
								return false;
							}
						}
						QBuffer	DBuff(&P->Data);
						if(DBuff.open(QIODevice::ReadOnly) == false)
							return false;
						if(DBuff.read((char *)&Info, sizeof(Info)) != sizeof(Info))
							return false;

						GUICmdSndImageMixTransfer	TCmd(GetLayersBase(), "ANY", "ANY", page);
						TCmd.MasterMode	=DstMasterImage;
						TCmd.Phase		=phase;
						TCmd.Layer		=Layer;
						TCmd.TopY		=Info.TopY;
						TCmd.BundleCount=Info.LineCount;
						TCmd.DotPerLine	=tDotPerLine;
						TCmd.MaxLines	=tMaxLines;
						TCmd.Len		=Pg->GetDotPerLine() * Info.LineCount;
						TCmd.Data		=new BYTE[TCmd.Len];
						DBuff.read((char *)TCmd.Data, TCmd.Len);

						TCmd.Send(NULL, page, 0);
					}
				}
			}
		}
	}

	return true;
}

bool	MixTransferComm::SndImageData(bool SrcMasterImage, bool DstMasterImage ,bool ChangeXY, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(SrcMasterImage == true) {
		QByteArray	Dummy;
		if(Packet.TxData(CmdMixTransfer_TxReqMasterDataImageCheckByte, &Dummy, ErrorData) == false)
			return false;
		Packet.WaitReadyRead(WaitingTime);
		QCoreApplication::processEvents();
		if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqMasterDataImageCheckByte) {
			return false;
		}
	}
	else {
		QByteArray	Dummy;
		if(Packet.TxData(CmdMixTransfer_TxReqTargetDataImageCheckByte, &Dummy, ErrorData) == false)
			return false;
		Packet.WaitReadyRead(WaitingTime);
		QCoreApplication::processEvents();
		if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxReqTargetDataImageCheckByte) {
			return false;
		}
	}

	QByteArray	R1Data=Packet.Data;
	QBuffer	R1Buff(&R1Data);
	if(R1Buff.open(QIODevice::ReadOnly) == false)
		return false;
	int32	tPageNumb;
	int32	tPhaseNumb;
	int32	tLayerNumb;
	int32	BundleCount;
	int32	tDotPerLine;
	int32	tMaxLines;
	if(::Load(&R1Buff, tPageNumb) == false)
		return false;
	if(::Load(&R1Buff, tPhaseNumb) == false)
		return false;
	if(::Load(&R1Buff, tLayerNumb) == false)
		return false;
	if(::Load(&R1Buff, BundleCount) == false)
		return false;
	if(::Load(&R1Buff, tDotPerLine) == false)
		return false;
	if(::Load(&R1Buff, tMaxLines) == false)
		return false;

	for(int phase=0;phase < GetPhaseNumb() && phase < tPhaseNumb;phase++) {
		PageDataInOnePhase *Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page < GetPageNumb() && page < tPageNumb;page++) {
			DataInPage *Pg=Ph->GetPageData(page);
			for(int Layer=0;Layer < GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
				DataInLayer *Ly=Pg->GetLayerData(Layer);
				DWORD	Src=Ly->GetMasterBuff().MakeCheckByte();
				DWORD	Dst;
				if(::Load(&R1Buff, Dst) == false)
					return false;
				if(Src != Dst) {
					int	LineCount=(1024 * 1024 * 3) / Pg->GetDotPerLine();
					int	N=(Pg->GetMaxLines() + BundleCount - 1) / BundleCount;
					for(int i=0;i < N;i++) {
						GUICmdReqImageMixTransfer	RCmd(GetLayersBase(), "ANY", "ANY", page);
						GUICmdAckImageMixTransfer	SCmd(GetLayersBase(), "ANY", "ANY", page);
						RCmd.MasterMode	=SrcMasterImage;
						RCmd.Phase		=phase;
						RCmd.Layer		=Layer;
						RCmd.TopY		=BundleCount * i;
						RCmd.BundleCount=LineCount;
						if(RCmd.Send(page, 0, SCmd) == false)
							return false;

						struct	MixTreansferImagePacketInfo	Info;
						Info.Phase		=phase;
						Info.Page		=page;
						Info.Layer		=Layer;
						Info.TopY		=RCmd.TopY;
						Info.LineCount	=SCmd.BundleCount;
						Info.DotPerLine	=GetDotPerLine(page);
						Info.MaxLines	=GetMaxLines(page);

						QBuffer	TxBuff;
						TxBuff.open(QIODevice::WriteOnly);
						TxBuff.write((const char *)&Info, sizeof(Info));
						TxBuff.write((const char *)SCmd.Data, SCmd.Len);

						Packet.ClearReceived();
						if(DstMasterImage == true) {
							if(Packet.TxData(CmdMixTransfer_TxSndMasterDataImage, &TxBuff, ErrorData) == false)
								return false;
							Packet.WaitReadyRead(WaitingTime);
							QCoreApplication::processEvents();
							if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxSndMasterDataImage) {
								return false;
							}
						}
						else {
							if(Packet.TxData(CmdMixTransfer_TxSndTargetDataImage, &TxBuff, ErrorData) == false)
								return false;
							Packet.WaitReadyRead(WaitingTime);
							QCoreApplication::processEvents();
							if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxSndTargetDataImage) {
								return false;
							}
						}
					}
				}
			}
		}
	}

	return true;
}

bool	MixTransferComm::OperationGUIPush(const QString &GUIRoot, const QString &GUIName, const QString &GUIInst, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	QBuffer	TxBuff;
	TxBuff.open(QIODevice::ReadWrite);

	::Save(&TxBuff, GUIRoot);
	::Save(&TxBuff, GUIName);
	::Save(&TxBuff, GUIInst);

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(Packet.TxData(CmdMixTransfer_TxOperationGUIPush, &TxBuff, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxOperationGUIPush) {
		return false;
	}
	return true;
}
bool	MixTransferComm::OperationGUITranssmitDirectly(const QString &GUIRoot, const QString &GUIName, const QString &GUIInst, QByteArray &Data, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	QBuffer	TxBuff;
	TxBuff.open(QIODevice::ReadWrite);

	::Save(&TxBuff, GUIRoot);
	::Save(&TxBuff, GUIName);
	::Save(&TxBuff, GUIInst);
	::Save(&TxBuff, Data);

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(Packet.TxData(CmdMixTransfer_TxOperationGUITranssmitDirectly, &TxBuff, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxOperationGUITranssmitDirectly) {
		return false;
	}
	return true;
}
bool	MixTransferComm::OperationAlgoTranssmitDirectly(const QString &AlgoRoot, const QString &AlgoName, QByteArray &Data, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false)
		return false;

	QBuffer	TxBuff;
	TxBuff.open(QIODevice::ReadWrite);

	::Save(&TxBuff, AlgoRoot);
	::Save(&TxBuff, AlgoName);;
	::Save(&TxBuff, Data);

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(Packet.TxData(CmdMixTransfer_TxOperationAlgoTranssmitDirectly, &TxBuff, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxOperationAlgoTranssmitDirectly) {
		return false;
	}
	return true;
}

bool	MixTransferComm::ChangeGUI(const QString &GUIFileName, DWORD WaitingTime)
{
	QString IPAddress;
	int32	Port;

	if(ReqHost(IPAddress ,Port)==false){
		return false;
	}

	QFile	File(GUIFileName);
	if(File.open(QIODevice::ReadOnly) == false) {
		return false;
	}

	MixTransferLeaf		Packet(GetLayersBase()->GetMTransfer());
	Packet.Set(parent(), IPAddress, Port);
	if(Packet.StartConnect(WaitingTime) == false) {
		return false;
	}

	QByteArray	FileData=File.readAll();

	ErrorCodeList ErrorData;
	Packet.ClearReceived();
	if(Packet.TxData(CmdMixTransfer_TxChangeGUI, &FileData, ErrorData) == false)
		return false;
	Packet.WaitReadyRead(WaitingTime);
	QCoreApplication::processEvents();
	if(Packet.IsReceived() == false || Packet.GetNowCmd() != CmdMixTransfer_RxChangeGUI) {
		return false;
	}
	return true;
}

//--------------  Transmitter side ---------------------
void	MixTransferLeaf::SlotReceived(int ID, int Cmd)
{
	MixTransferRecList *R=UnpackTopRxBuff();
	if(R != NULL) {
		BYTE *fp=R->GetPointer();

		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel() != ErrorCodeList::_None) {
			fp=R->GetError(fp, ErrorData);
		}

		if(fp!=NULL) {
			fp+=sizeof(int64);
			Data=QByteArray((const char *)fp, R->Len-sizeof(int64));
		}

		//-----------------------------------------------
		if(R->Cmd == CmdMixTransfer_TxReqAck) {
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			QString	WinTitle=cParent->GetLayersBase()->GetMainWidget()->windowTitle();
			::Save(&TxBuff,WinTitle);
			TxData(CmdMixTransfer_RxReqAck, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqAck) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqGlobalParam) {
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			cParent->GetParamGlobal()->SaveParam(&TxBuff, -1);
			TxData(CmdMixTransfer_RxReqGlobalParam, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqGlobalParam) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxSndGlobalParam) {
			QBuffer	buff(&Data);
			cParent->GetParamGlobal()->LoadParam(&buff, -1);
			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxSndGlobalParam, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxSndGlobalParam) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqMasterDataImageCheckByte) {
			PhasePageLayerDContainer *Dim=new PhasePageLayerDContainer[cParent->GetPageNumb()];
			for(int page=0;page < cParent->GetPageNumb();page++) {
				GUICmdReqImageCheckByte	RCmd(cParent->GetLayersBase(), "ANY", "ANY", page);
				GUICmdAckImageCheckByte	SCmd(cParent->GetLayersBase(), "ANY", "ANY", page);
				if(RCmd.Send(page, 0, SCmd) == true) {
					Dim[page]=SCmd.CheckData;
				}
			}
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			int32	tPageNumb	=cParent->GetPageNumb();
			int32	tPhaseNumb	=cParent->GetPhaseNumb();
			int32	tLayerNumb	=cParent->GetLayerNumb(0);
			int32	BundleCount	=(1024 * 1024 * 3) / cParent->GetDotPerLine(-1);
			int32	tDotPerLine	=cParent->GetDotPerLine(0);
			int32	tMaxLines	=cParent->GetMaxLines(0);
			::Save(&TxBuff, tPageNumb);
			::Save(&TxBuff, tPhaseNumb);
			::Save(&TxBuff, tLayerNumb);
			::Save(&TxBuff, BundleCount);
			::Save(&TxBuff, tDotPerLine);
			::Save(&TxBuff, tMaxLines);
			for(int phase=0;phase < cParent->GetPhaseNumb();phase++) {
				for(int page=0;page < cParent->GetPageNumb();page++) {
					for(int Layer=0;Layer < cParent->GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
						PhasePageLayerD *d=Dim[page].Find(phase, Layer);
						if(d != NULL) {
							::Save(&TxBuff, d->ImageCheckData);
						}
						else {
							DWORD	dd=0;
							::Save(&TxBuff, dd);
						}
					}
				}
			}
			delete[]Dim;

			TxData(CmdMixTransfer_RxReqMasterDataImageCheckByte, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqMasterDataImageCheckByte) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqTargetDataImageCheckByte) {
			PhasePageLayerDContainer *Dim=new PhasePageLayerDContainer[cParent->GetPageNumb()];
			for(int page=0;page < cParent->GetPageNumb();page++) {
				GUICmdReqImageCheckByte	RCmd(cParent->GetLayersBase(), "ANY", "ANY", page);
				GUICmdAckImageCheckByte	SCmd(cParent->GetLayersBase(), "ANY", "ANY", page);
				RCmd.MasterMode=false;
				if(RCmd.Send(page, 0, SCmd) == true) {
					Dim[page]=SCmd.CheckData;
				}
			}
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			int32	tPageNumb	=cParent->GetPageNumb();
			int32	tPhaseNumb	=cParent->GetPhaseNumb();
			int32	tLayerNumb	=cParent->GetLayerNumb(0);
			int32	tDotPerLine	=cParent->GetDotPerLine(0);
			int32	tMaxLines	=cParent->GetMaxLines(0);
			int32	BundleCount=(1024 * 1024 * 3) / cParent->GetDotPerLine(-1);
			::Save(&TxBuff, tPageNumb);
			::Save(&TxBuff, tPhaseNumb);
			::Save(&TxBuff, tLayerNumb);
			::Save(&TxBuff, BundleCount);
			::Save(&TxBuff, tDotPerLine);
			::Save(&TxBuff, tMaxLines);
			for(int phase=0;phase < cParent->GetPhaseNumb();phase++) {
				for(int page=0;page < cParent->GetPageNumb();page++) {
					for(int Layer=0;Layer < cParent->GetLayerNumb(page) && Layer < tLayerNumb;Layer++) {
						PhasePageLayerD *d=Dim[page].Find(phase, Layer);
						if(d != NULL) {
							::Save(&TxBuff, d->ImageCheckData);
						}
						else {
							DWORD	dd=0;
							::Save(&TxBuff, dd);
						}
					}
				}
			}
			delete[]Dim;

			TxData(CmdMixTransfer_RxReqTargetDataImageCheckByte, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqTargetDataImageCheckByte) {
			NowCmd=R->Cmd;
		}
		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqMasterDataImage) {
			struct	MixTreansferImagePacketInfo	Info;
			int	InfoSize=sizeof(Info);
			int	DataSize=Data.size();
			memcpy((char *)&Info,Data.data(),min(InfoSize,DataSize));

			GUICmdReqImageMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			GUICmdAckImageMixTransfer	SCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			RCmd.Phase=Info.Phase;
			RCmd.Layer=Info.Layer;
			RCmd.TopY=Info.TopY;
			RCmd.BundleCount=Info.LineCount;
			if(RCmd.Send(Info.Page, 0, SCmd) == false) {
				delete	R;
				return;
			}
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			Info.LineCount=SCmd.BundleCount;
			TxBuff.write((char *)&Info, sizeof(Info));
			TxBuff.write((char *)SCmd.Data, SCmd.Len);

			TxData(CmdMixTransfer_RxReqMasterDataImage, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqMasterDataImage) {
			NowCmd=R->Cmd;
		}
		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqTargetDataImage) {
			QBuffer	buff(&Data);
			struct	MixTreansferImagePacketInfo	Info;
			int	InfoSize=sizeof(Info);
			int	DataSize=Data.size();
			memcpy((char *)&Info,Data.data(),min(InfoSize,DataSize));

			GUICmdReqImageMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			GUICmdAckImageMixTransfer	SCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			RCmd.MasterMode=false;
			RCmd.Phase=Info.Phase;
			RCmd.Layer=Info.Layer;
			RCmd.TopY=Info.TopY;
			RCmd.BundleCount=Info.LineCount;
			if(RCmd.Send(Info.Page, 0, SCmd) == false) {
				delete	R;
				return;
			}
			QBuffer	TxBuff;
			TxBuff.open(QIODevice::WriteOnly);
			Info.LineCount=SCmd.BundleCount;
			TxBuff.write((char *)&Info, sizeof(Info));
			TxBuff.write((char *)SCmd.Data, SCmd.Len);

			TxData(CmdMixTransfer_RxReqTargetDataImage, &TxBuff, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxReqTargetDataImage) {
			NowCmd=R->Cmd;
		}
		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxReqMasterAlgo) {
			QBuffer	buff(&Data);
			QByteArray	Array;
			if(::Load(&buff, Array) == false) {
				delete	R;
				return;
			}
			QBuffer	RxBuff(&Array);
			int32	Page;
			QString	AlgoRoot;
			QString	AlgoName;
			::Load(&RxBuff, Page);
			::Load(&RxBuff, AlgoRoot);
			::Load(&RxBuff, AlgoName);

			GUICmdReqAlgoDataMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Page);
			GUICmdAckAlgoDataMixTransfer	SCmd(cParent->GetLayersBase(), "ANY", "ANY", Page);
			RCmd.AlgoRoot=AlgoRoot;
			RCmd.AlgoName=AlgoName;
			if(RCmd.Send(Page, 0, SCmd) == false) {
				delete	R;
				return;
			}
			TxData(CmdMixTransfer_RxReqMasterAlgo, &SCmd.Data, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_TxReqMasterDataImage) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxSndMasterDataImage) {
			QBuffer	buff(&Data);
			struct	MixTreansferImagePacketInfo	Info;

			buff.read((char *)&Info, sizeof(Info));
			GUICmdSndImageMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			RCmd.Phase	=Info.Phase;
			RCmd.Layer	=Info.Layer;
			RCmd.TopY	=Info.TopY;
			RCmd.Len	=Info.LineCount * cParent->GetDotPerLine(Info.Page);
			RCmd.DotPerLine	=Info.DotPerLine;
			RCmd.MaxLines	=Info.MaxLines	;
			RCmd.Data	=new BYTE[RCmd.Len];
			buff.read((char *)RCmd.Data, RCmd.Len);
			RCmd.Send(NULL, Info.Page, 0);

			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxSndMasterDataImage, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxSndMasterDataImage) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxSndTargetDataImage) {
			QBuffer	buff(&Data);
			struct	MixTreansferImagePacketInfo	Info;

			buff.read((char *)&Info, sizeof(Info));
			GUICmdSndImageMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Info.Page);
			RCmd.MasterMode	=false;
			RCmd.Phase		=Info.Phase;
			RCmd.Layer		=Info.Layer;
			RCmd.TopY		=Info.TopY;
			RCmd.DotPerLine	=Info.DotPerLine;
			RCmd.MaxLines	=Info.MaxLines	;
			RCmd.Len		=Info.LineCount * cParent->GetDotPerLine(Info.Page);
			RCmd.Data		=new BYTE[RCmd.Len];
			buff.read((char *)RCmd.Data, RCmd.Len);
			RCmd.Send(NULL, Info.Page, 0);

			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxSndTargetDataImage, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxSndTargetDataImage) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxSndMasterAlgo) {
			QBuffer	buff(&Data);
			int32	Page;
			QString	AlgoRoot;
			QString	AlgoName;
			::Load(&buff, Page);
			GUICmdSndAlgoDataMixTransfer	RCmd(cParent->GetLayersBase(), "ANY", "ANY", Page);
			::Load(&buff, RCmd.AlgoRoot);
			::Load(&buff, RCmd.AlgoName);
			::Load(&buff, RCmd.Data);
			RCmd.Send(NULL, Page, 0);

			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxSndMasterAlgo, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxSndMasterAlgo) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxOperationGUIPush) {
			QBuffer	buff(&Data);
			QString GUIRoot;
			QString GUIName;
			QString GUIInst;

			if(::Load(&buff, GUIRoot) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, GUIName) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, GUIInst) == false) {
				delete	R;
				return;
			}
			GUIFormBase *f=cParent->GetLayersBase()->FindByName(GUIRoot, GUIName, GUIInst);
			if(f != NULL) {
				f->PushButton();
			}
			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxOperationGUIPush, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxOperationGUIPush) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxOperationGUITranssmitDirectly) {
			QBuffer	buff(&Data);
			QString GUIRoot;
			QString GUIName;
			QString GUIInst;
			QByteArray	GUIData;

			if(::Load(&buff, GUIRoot) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, GUIName) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, GUIInst) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, GUIData) == false) {
				delete	R;
				return;
			}
			GUIFormBase *f=cParent->GetLayersBase()->FindByName(GUIRoot, GUIName, GUIInst);
			if(f != NULL) {
				QBuffer	TxBuff(&GUIData);
				TxBuff.open(QIODevice::ReadWrite);
				QString	ClassName=f->LoadInPacket(&TxBuff);
				GUIDirectMessage *cmd=f->LoadInPacket(&TxBuff, ClassName);
				if(cmd != NULL) {
					f->TransmitDirectly(cmd);
				}
			}
			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxOperationGUITranssmitDirectly, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxOperationGUITranssmitDirectly) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxOperationAlgoTranssmitDirectly) {
			QBuffer	buff(&Data);
			QString AlgoRoot;
			QString AlgoName;
			QByteArray	AlgoData;

			if(::Load(&buff, AlgoRoot) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, AlgoName) == false) {
				delete	R;
				return;
			}
			if(::Load(&buff, AlgoData) == false) {
				delete	R;
				return;
			}
			AlgorithmBase *ABase=cParent->GetLayersBase()->GetAlgorithmBase(AlgoRoot, AlgoName);
			if(ABase != NULL) {
				QBuffer	TxBuff(&AlgoData);
				TxBuff.open(QIODevice::ReadWrite);
				QString	ClassName=ABase->LoadInPacket(&TxBuff);
				GUIDirectMessage *cmd=ABase->LoadInPacket(&TxBuff, ClassName);
				if(cmd != NULL) {
					ABase->TransmitDirectly(cmd);
				}
			}
			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxOperationGUITranssmitDirectly, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxOperationGUITranssmitDirectly) {
			NowCmd=R->Cmd;
		}

		//-----------------------------------------------
		else if(R->Cmd == CmdMixTransfer_TxChangeGUI) {
			QBuffer	buff(&Data);
			QByteArray	FileData;
			if(::Load(&buff, FileData) == false) {
				delete	R;
				return;
			}
			cParent->GetLayersBase()->ChangeGUI(FileData);

			QByteArray	Dummy;
			TxData(CmdMixTransfer_RxChangeGUI, &Dummy, ErrorData);
		}
		else if(R->Cmd == CmdMixTransfer_RxChangeGUI) {
			NowCmd=R->Cmd;
		}

		delete	R;
	}

}
