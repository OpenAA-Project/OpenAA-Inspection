/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\MeasureLineMove.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XMeasureLineMoveResource.h"
#include "XAlgorithmDLL.h"
#include "XMeasureLineMove.h"
#include "MeasureLineMove.h"
#include "EditArcDialog.h"
#include "EditLineDialog.h"
#include "EditDistanceDialog.h"
#include "EditMarkDialog.h"
#include "EditRxLineDialog.h"
#include "XMeasureLineMovePacket.h"

const	char	*sRoot=/**/"Measure";
const	char	*sName=/**/"MeasureLineMove";

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
	return MeasureLineMoveVersion;
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "線間距離計測";
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	const char	*DLL_GetBlobName(void)
{
	return /**/"MeasureLineMove";
}

DEFFUNCEX	AlgorithmBase	*DLL_InitialAlloc(LayersBase *Base)
{
	MeasureLineMoveBase	*base=new MeasureLineMoveBase(Base);
	base->Initial(Base);

	(*Base)=new SlaveCommReqPosition		(Base,sRoot,sName);
	(*Base)=new SlaveCommAckPosition		(Base,sRoot,sName);
	(*Base)=new SlaveCommReqResultPosition	(Base,sRoot,sName);
	(*Base)=new SlaveCommAckResultPosition	(Base,sRoot,sName);

	(*Base)=new GUICmdReqConvertUnitPixel	(Base,sRoot,sName);
	(*Base)=new GUICmdAckConvertUnitPixel	(Base,sRoot,sName);
	return base;
}
DEFFUNCEX	void	DLL_Close(void)
{
}

DEFFUNCEX	AlgorithmLibraryContainer	*DLL_NewLibrary(LayersBase *Base)
{
	return new MeasureLineMoveLibraryContainer(Base);
}

DEFFUNCEX	DWORD		DLL_GetAlgorithmType(void)
{
	return AlgorithmBit_TypeProcessing | AlgorithmBit_TypePostProcessing;
}

DEFFUNCEX	bool	DLL_SaveItem(QIODevice *f,AlgorithmItemRoot *item)
{
	return item->Save(f);
}
DEFFUNCEX	bool	DLL_LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase)
{
	return item->Load(f,LBase);
}
DEFFUNCEX	ResultBaseForAlgorithmRoot	*DLL_CreateResultBaseForAlgorithm(LogicDLL *parent)
{
	return new ResultLineMoveBaseForAlgorithmPI(parent);
}

DEFFUNCEX	QWidget	*DLL_ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something)
{
	for(AlgorithmItemIndependent	*D=Data.Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureLineMoveLineItem	*LineData=dynamic_cast<MeasureLineMoveLineItem *>(DA);
		if(LineData!=NULL){
			EditLineDialog	*EditLineForm=new EditLineDialog(InstBase->GetLayersBase());
			EditLineForm->Initial(InstBase ,Data);
			EditLineForm->show();
			return EditLineForm;
		}
		MeasureLineMoveRxLineItem	*RxLineData=dynamic_cast<MeasureLineMoveRxLineItem *>(DA);
		if(RxLineData!=NULL){
			EditRxLineDialog	*EditRxLineForm=new EditRxLineDialog(InstBase->GetLayersBase());
			EditRxLineForm->Initial(InstBase ,Data);
			EditRxLineForm->show();
			return EditRxLineForm;
		}
		MeasureLineMoveCornerRItem	*ArcData=dynamic_cast<MeasureLineMoveCornerRItem *>(DA);
		if(ArcData!=NULL){
			EditArcDialog	*EditArcForm=new EditArcDialog(InstBase->GetLayersBase());
			EditArcForm->Initial(InstBase ,Data);
			EditArcForm->show();
			return EditArcForm;
		}
		MeasureLineMoveMarkItem	*MarkData=dynamic_cast<MeasureLineMoveMarkItem *>(DA);
		if(MarkData!=NULL){
			EditMarkDialog	*EditMarkForm=new EditMarkDialog(InstBase->GetLayersBase());
			EditMarkForm->Initial(InstBase ,Data);
			EditMarkForm->show();
			return EditMarkForm;
		}
		MeasureLineMoveDistanceItem	*DistanceData=dynamic_cast<MeasureLineMoveDistanceItem *>(DA);
		if(DistanceData!=NULL){
			EditDistanceDialog	*EditDistanceForm=new EditDistanceDialog(InstBase->GetLayersBase());
			EditDistanceForm->Initial(InstBase ,Data);
			EditDistanceForm->show();
			return EditDistanceForm;
		}
	}
	return NULL;
}

DEFFUNCEX	AddedDataClass	*DLL_LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
DEFFUNCEX	bool			DLL_SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
DEFFUNCEX	void			DLL_RemoveAddedResultData(AddedDataClass *d);

