#include "XServerLayerBase.h"
#include "XGUIFormBase.h"
#include <QSqlDatabase>
#include "XDataInLayer.h"
#include "XParamDatabase.h"
#include "Regulus64System.h"
#include "XDataComponent.h"

LayersBase			*ServerEntryPoint::GetLayersBase(void)	const
{	
	return Base;	
}

ServerLayerBase::ServerLayerBase(LayersBase *_ParentLayerBase ,EntryPointBase *PInspectionData)
	:LayersBase((const LayersBase *)_ParentLayerBase)
	,ParentLayerBase(_ParentLayerBase)
{
	QString	Msg;
	EntryPoint	=PInspectionData;
	//RootDBase=new QSqlDatabase(*ParentLayerBase->GetDataBase());
	RootDBase=ParentLayerBase->GetDataBase();
	OriginalRootDBase	=true;
	//Initial(PInspectionData,Msg);
	ShrinkingPackContainerInstance	=_ParentLayerBase->GetShrinkingPackContainer();
}
ServerLayerBase::~ServerLayerBase(void)
{
	RootDBase=NULL;
	DBLoader=NULL;
	ShrinkingPackContainerInstance=NULL;
	ParentLayerBase	=NULL;
	PointArea.Clear();
	ReleaseAll();
}
bool	ServerLayerBase::InitialForServer(int XSize ,int YSize ,int Layer)
{
	QString	Msg;

	DBLoader=ParentLayerBase->GetDatabaseLoader();

	GetParamGlobal()->DotPerLine=XSize;
	GetParamGlobal()->MaxLines	=YSize;
	GetParamGlobal()->LayerNumb	=Layer;
	GetParamGlobal()->PageNumb	=1;
	GetParamGlobal()->PhaseNumb	=1;
	GetParamGlobal()->TotalCameraNumb	=1;
	GetParamGlobal()->MaxNGCountsPerCam	=100;
	GetParamGlobal()->MaxNGImageForHaltPerCam	=100;
	GetParamGlobal()->MaxInspectMilisec		=1000000;
	GetParamGlobal()->MaxHistoryCounts	=2;
	GetParamGlobal()->AllocateMasterBuff	=true;
	GetParamGlobal()->AllocateTargetBuff	=true;
	GetParamGlobal()->AllocateGrayBuff		=false;
	GetParamGlobal()->AllocRawTargetBuffForNGImage	=false;
	GetParamGlobal()->MaxNGImageNumbPerPage	=0;
	GetParamGlobal()->BufferedProcessing	=false;
	GetParamGlobal()->CalcSingleThread		=false;
	GetParamGlobal()->KeepFilteredImage		=false;
	GetParamGlobal()->DrawResultDetail		=false;
	GetParamGlobal()->DrawResultDetailLevel	=0;
	GetParamGlobal()->DebugLevel			=0;	//0:NoDebug
	GetParamGlobal()->OutputLogMode			=false;
	GetParamGlobal()->ReDrawByInspection	=false;

	InitialCreatePages(GetEntryPoint());
	GetLocalParamStocker()->Load();

	InitialAllocExecuterDim();
	InitialResult(false);

	RootNameListContainer	AlgorithmRootNameList;
	CopyAlgorithm(GetParent(),AlgorithmRootNameList,DefAlgorithmPath,true);
	InitialAlgorithmBlob();
	InitialAlgorithmLibrary();

	CloseInformed();
	return true;
}

bool	ServerLayerBase::LoadItemParamData(int LibType , int LibID ,QByteArray &Array)
{
	AlgorithmBase	*Ab=GetAlgorithmBase(LibType);
	if(Ab==NULL)
		return false;
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(0);

	ItemDataListWithIDContainer	CData;

	ItemDataListWithID	*C=new ItemDataListWithID();
	C->IData=Array;
	CData.AppendList(C);
	if(Ap->LoadItemsForLearning(CData ,0,0)==false)
		return false;
	return true;
}
