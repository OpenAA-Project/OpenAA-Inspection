
/*
 * Copyright (C) 2024
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

//#include "AlignmentShiftRotationResource.h"
#include "XAlgorithmDLL.h"
#include "AlignmentShiftRotation.h"
#include "XAlignmentShiftRotation.h"
#include "XAlignmentShiftRotationLibrary.h"
#include "EditAlignmentShiftRotationForm.h"
//#include "XPacketAlignmentShiftRotation.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"AlignmentShiftRotation";

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
	Root=sRoot;
	Name=sName;
	return true;
}
DEFFUNCEX	WORD		DLL_GetVersion(void)
{
	return AlignmentShiftRotationVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "形状での回転アラインメント";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"AlignmentShiftRotation";
}
DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypePreAlignment | AlgorithmBit_TypeAlignment;
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	AlgorithmBase	*base=new AlignmentShiftRotationBase(Base);
	base->Initial(Base);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new AlignmentShiftRotationLibraryContainer(Base);
}

DEFFUNCEX	AlignmentPacketBase	*DLL_GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY ,AlgorithmItemRoot *Item,bool FromGlobal)
{
	AlignmentShiftRotationBase	*abase=dynamic_cast<AlignmentShiftRotationBase *>(base);
	if(abase!=NULL){
		return ((AlignmentShiftRotationInPage *)(abase->GetPageDataPhase(Item->GetPhaseCode())
											->GetPageData(localPage)))
											->AppendAlignmentShiftRotationPacket2D(Item,localX,localY,FromGlobal);
	}
	return NULL;
}
DEFFUNCEX	int			DLL_GetPriority(int AlgorithmBit_Type)
{
	if(AlgorithmBit_Type==PriorityType_ExecuteInitialAfterEdit)
		return 100000;
	if(AlgorithmBit_Type==PriorityType_ExecuteAlignment)
		return 100000;
	return 100;
}
DEFFUNCEX	void	DLL_GetAlignmentForProcessing(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet)
{
	AlignmentShiftRotationBase	*abase=dynamic_cast<AlignmentShiftRotationBase *>(base);
	if(abase!=NULL){
		AlignmentPacket2D	*p2d=static_cast<AlignmentPacket2D *>(&Packet);
		if(p2d!=NULL)
			((AlignmentShiftRotationInPage *)(abase->GetPageData(localPage)))->GetAlignmentShiftRotation(*p2d);
	}
}
DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((AlignmentShiftRotationItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((AlignmentShiftRotationItem *)item)->Load(f,LBase);
}

DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	EditAlignmentShiftRotationForm	*DForm=new EditAlignmentShiftRotationForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);
