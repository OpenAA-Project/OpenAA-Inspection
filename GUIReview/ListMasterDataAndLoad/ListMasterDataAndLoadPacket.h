/*
 * Copyright (C) 2022
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

#pragma once

#include "XDLLOnly.h"

#include "XReviewCommon.h"
#include "../XGUIReviewGlobal.h"
#include "../XGUIReviewCommonPacket.h"

#include "ReviewStructurePacket.h"

#include "XGeneralFunc.h"

//////////////////////////////////
// ��GUI���瑗�M�������R�}���h
// [GUI���ʍ���]
//  *�X�V -> NGPosList�̍X�V
//   GUICmdReviewUpdateLocal

//////////////////////////////////
// ���M�����R�}���h
//  
// 

//////////////////////////////////////
// �}�X�^�[�X���[�u�R�}���h
// [GUI���ʍ���]
//  *�X�V -> NGPosList�̍X�V
//   GUICmdReviewUpdate
// 

// �}�X�^�[�摜�̓ǂݍ��ݕԐM�p�P�b�g
class	GUICmdAckLoadSlaveMaster : public GUICmdPacketBase
{
public:
	bool	Ret;		// ����
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

// �}�X�^�[�摜�̓ǂݍ��ݗv���p�P�b�g
class	GUICmdReqLoadSlaveMaster : public GUICmdPacketBase
{
public:
	int		MasterCode;	// �}�X�^�[�R�[�h
	int		MachineID;	// �}�V��ID
	int		PhaseCode;	// �t�F�[�Y�ԍ�
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