#pragma once

#include "XDLLOnly.h"

#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"
#include "../XGUIReviewCommonPacket.h"

#include "ReviewStructurePacket.h"

#include "XGeneralFunc.h"

//////////////////////////////////
// 他GUIから送信されるコマンド
// [GUI共通項目]
//  *更新 -> NGPosListの更新
//   GUICmdReviewUpdateLocal

//////////////////////////////////
// 送信するコマンド
//  
// 

//////////////////////////////////////
// マスタースレーブコマンド
// [GUI共通項目]
//  *更新 -> NGPosListの更新
//   GUICmdReviewUpdate
// 

// マスター画像の読み込み返信パケット
class	GUICmdAckLoadSlaveMaster : public GUICmdPacketBase
{
public:
	bool	Ret;		// 結果
	int		PhaseCount;

	GUICmdAckLoadSlaveMaster(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage){};

	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,Ret)==false)
			return false;
		if(::Load(f,PhaseCount)==false)
			return false;
		return true;
	};
	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,Ret)==false)
			return false;
		if(::Save(f,PhaseCount)==false)
			return false;
		return true;
	};

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

// マスター画像の読み込み要求パケット
class	GUICmdReqLoadSlaveMaster : public GUICmdPacketBase
{
public:
	int		MasterCode;	// マスターコード
	int		MachineID;	// マシンID
	int		PhaseCode;	// フェーズ番号
	GUICmdReqLoadSlaveMaster(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1)
		:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage){};

	virtual	bool	Load(QIODevice *f){
		if(::Load(f,MasterCode)==false)
			return false;
		if(::Load(f,MachineID)==false)
			return false;
		if(::Load(f,PhaseCode)==false)
			return false;
		return true;
	};
	virtual	bool	Save(QIODevice *f){
		if(::Save(f,MasterCode)==false)
			return false;
		if(::Save(f,MachineID)==false)
			return false;
		if(::Save(f,PhaseCode)==false)
			return false;
		return true;
	};

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){
		GUICmdAckLoadSlaveMaster	*SendBack=GetSendBack(GUICmdAckLoadSlaveMaster,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

		ReviewPIBase *RBase = GetReviewAlgorithm();
		if(RBase==NULL){
			SendBack->Ret=false;
		}
		else{
			CmdLoadSlave	CmdLoadSlaveIns(GetLayersBase());
			CmdLoadSlaveIns.MasterCode	=MasterCode;
			CmdLoadSlaveIns.MachineID	=MachineID;
			CmdLoadSlaveIns.PhaseCode	=PhaseCode;
			CmdLoadSlaveIns.LocalPage	=localPage;
			RBase->TransmitDirectly(&CmdLoadSlaveIns);

			LogicDLL *p;
			AlgorithmInPageRoot	*ap;
			int		GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			
			PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(PhaseCode);
			DataInPage	*Dp=Ph->GetPageData(localPage);

			for(p=GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
				if(p->GetBlobName().isEmpty()==true){
					continue;
				}
				AlgorithmBase	*base=GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
				if(base==NULL){
					continue;
				}
				if(RBase==base){
					continue;
				}
				AlgorithmInPageInOnePhase	*pbase=base->GetPageDataPhase(PhaseCode);
				ap=pbase->GetPageData(GlobalPage);
				if(ap==NULL){
					continue;
				}

				QStringList pathList = GetParamGlobal()->ImageFilePath.split(/**/";", QString::SkipEmptyParts);
				
				for(int pi=0; pi<pathList.count(); pi++){
					QString filename = Dp->CreateLogicFileName(MasterCode,p,MachineID,pathList[pi]
																,0,0);
					if(QFile::exists(filename)==false){
						continue;
					}
					QFile	LogicFile(filename);
					LogicFile.open(QIODevice::ReadOnly);
					base->LoadOnlyBase(&LogicFile);
					if(ap->Load(&LogicFile)==false){
						//ErrorMsg=QString("Error of Saving Algorithm ")+p->GetDLLRoot() +QString(":")+ p->GetDLLName();
						continue;
					}
				}
			}


			SendBack->Ret=true;
		}
		SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	};	
};
