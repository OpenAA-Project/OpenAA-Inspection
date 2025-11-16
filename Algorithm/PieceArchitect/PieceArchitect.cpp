/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PieceArchitect\PieceArchitect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "PieceArrangeResource.h"
#include "XAlgorithmDLL.h"
#include "XPieceArchitect.h"
#include "PieceArchitect.h"
#include "XPieceArrange.h"
#include "XGUI.h"

DEFFUNCEX	bool		DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD		DLL_GetDLLType(void)
{
	return DLLAlgorithmMode;
}
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Basic";
	Name=/**/"PieceArrange";
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return PieceArchtectVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "部品化処理";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"PieceArrange";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeNoProcessing | AlgorithmBit_TypePieceProcessing;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	PieceArrangeBase	*base=new PieceArrangeBase(Base);
	base->Initial(Base);
	if(Base->GetBootingLevel()==0){
		base->ClearTempFiles();
	}
	return base;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((PieceArrangeItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((PieceArrangeItem *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}


DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

GUIInitializer::GUIInitializer(LayersBase *base)
:ServiceForLayers(base)
{
	GuiDLLPack	=NULL;
	IntegrationComm				=NULL;
	//IntegrationPageDirectlyComm	=NULL;
}
GUIInitializer::~GUIInitializer(void)
{
}
bool	GUIInitializer::TxData(int32 globalPage 
							   ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							   ,int CommID ,QBuffer *f
							   ,ErrorCodeList &ErrorData)
{
	return false;
}
bool	GUIInitializer::TxData(int32 globalPage 
							   ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
							   ,int CommID ,QByteArray *f
							   ,ErrorCodeList &ErrorData)
{
	return false;
}


bool	GUIInitializer::TxIntegrationData(int32 slaveNo 
										  ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
										  ,QBuffer *f
										  ,ErrorCodeList &ErrorData)
{
	return false;
}


QTcpSocket	*GUIInitializer::GetSocket(int ComNo)
{
	return NULL;
}
QTcpSocket	*GUIInitializer::GetIntegrationSocket(int slaveNo)
{
	return NULL;
}

