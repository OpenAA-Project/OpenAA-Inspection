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

GUIInitializer::GUIInitializer(LayersBase *base,QObject *parent)
:QObject(parent),ServiceForLayers(base)
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
