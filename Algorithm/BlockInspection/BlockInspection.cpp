/*
 * Copyright (C) 2023
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



#include "XAlgorithmDLL.h"
#include "BlockInspection.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "HistogramForm.h"
#include "BlockFormResource.h"
#include "ChangeShiftForm.h"
#include "XBlockAlgoPacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Basic";
const	char	*sName=/**/"BlockInspection";

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
	return BlockInspectionVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "ブロック検査";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"BlockIns";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	BlockBase	*base=new BlockBase(Base);
	base->Initial(Base);
	Base->SetUseDynamicMasking(true);

	(*Base)=new SlaveCommReqLibraryInMaskOfBlock(Base,sRoot,sName);
	(*Base)=new SlaveCommAckLibraryInMaskOfBlock(Base,sRoot,sName);

	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}
DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new BlockLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing | AlgorithmBit_TypePreProcessing | AlgorithmBit_TypeProcessingRevived;
}
DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	HistogramForm	*DForm=new HistogramForm(InstBase->GetLayersBase());
	DForm->Initial(InstBase ,Data);
	DForm->show();
	return DForm;
}
DEFFUNCEX	QWidget	*DLL_ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	ChangeShiftForm	*CForm=new ChangeShiftForm(InstBase->GetLayersBase());
	CForm->Initial(parent ,InstBase ,Data);
	CForm->show();
	return CForm;
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultBaseForAlgorithmPLI(parent);
}


DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return ((BlockItem *)item)->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return ((BlockItem *)item)->Load(f,LBase);
}


static	bool	SetNGSizeNarrow(AlgorithmBase *Instance ,QStringList &Args);
static	bool	SetBrightnessNarrow(AlgorithmBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetBrightnessNarrow";
		Functions[ret].Explain.append(/**/"Set Brightness Narrow");
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].ArgName.append(/**/"Low");
		Functions[ret].ArgName.append(/**/"High");
		Functions[ret].DLL_ExcuteMacroAlgo	=SetBrightnessNarrow;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetNGSizeNarrow";
		Functions[ret].Explain.append(/**/"Set NG size Narrow");
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].ArgName.append(/**/"Pixels in low");
		Functions[ret].ArgName.append(/**/"Pixels in high");
		Functions[ret].DLL_ExcuteMacroAlgo	=SetNGSizeNarrow;
		ret++;
	}
	return ret;
}

static	bool	SetBrightnessNarrow(AlgorithmBase *Instance ,QStringList &Args)
{
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	BrightnessLow=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	BrightnessHigh=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}

	return true;
}

static	bool	SetNGSizeNarrow(AlgorithmBase *Instance ,QStringList &Args)
{
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	PixelsLow=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	PixelsHigh=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}

	return true;
}