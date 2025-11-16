#include "XTypeDef.h"
#include <QSqlDatabase>
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XTransfer.h"
#include "XResultDLLManager.h"
#include <QThread>
#include "XForWindows.h"
#include "XShareMasterData.h"
#include "XLotInformation.h"
#include "XGeneralStocker.h"
#include "XAlgorithmDLL.h"
#include "XResultAnalizer.h"
#include "XGUIPacketGeneral.h"



GUICmdReleaseSelectImagePanel::GUICmdReleaseSelectImagePanel(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReleaseSelectImagePanel::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;
}
bool	GUICmdReleaseSelectImagePanel::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}

void	GUICmdReleaseSelectImagePanel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*P=Ah->GetPageData(localPage);
			if(P!=NULL){
				P->ReleaseAllSelectedItem();
			}
		}
	}
	SendAck(localPage);
}


//=======================================================================
GUICmdSelectByLibs::GUICmdSelectByLibs(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}

bool	GUICmdSelectByLibs::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(SelectedList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectByLibs::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(SelectedList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectByLibs::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		Ap->SelectLibs(SelectedList);
	}
	SendAck(localPage);
}