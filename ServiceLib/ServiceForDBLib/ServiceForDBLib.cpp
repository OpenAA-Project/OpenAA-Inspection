/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceForDBLib\servicefordblib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QBuffer>
#include <QPainter>
#include <QImage>
#include <QSqlRecord>
#include <QSqlError>
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h" 
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"
#include "ServiceForDBLib.h"
#include "XColorSpace.h"
#include "XOutlineOffset.h"
#include "XAlgorithmLibNGType.h"
#include "XParamDatabase.h"
#include "XLearningRegist.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

void	LockDB(void);
void	UnlockDB(void);

void __G_LockDB(void)
{
	LockDB();
}
void __G_UnlockDB(void)
{
	UnlockDB();
}

int	__G_SQLSaveNewMasterData(QSqlDatabase &DB ,LayersBase *Base)
{
	if(Base->IsDatabaseOk()==false){
		return 0;
	}
	int	MasterCode=0;
	LockDB();
	{
		QSqlQuery query(DB);
		query.prepare("SELECT MAX(MASTERCODE) from MASTERDATA");
		if(query.exec()==false){
			GSleep(3000);
			if(query.exec()==false){
				goto	FuncEnd;
			}
		}
		if(query.next()==false){
			goto	FuncEnd;
		}
		MasterCode = query.value(0).toInt()+1;
	
	
	
		PAgain:;
		DB.transaction();
		bool	InsertOK=false;
		{
			for(int i=0;i<10;i++){
				QSqlQuery queryInsert(DB);
	
				queryInsert.prepare("INSERT INTO MASTERDATA(MASTERCODE) "
								"VALUES(:IN_MASTERCODE);");		
				queryInsert.bindValue(0	, MasterCode);
				if(queryInsert.exec()==true){
					InsertOK=true;
					break;
				}
				MasterCode++;
			}
		}
		if(InsertOK==false){
			goto	FuncEnd;
		}
		{
			QSqlQuery queryInsert(DB);
			queryInsert.prepare("UPDATE MASTERDATA "
								"SET MACHINEID=:IN_MACHINEID "
								"WHERE MASTERCODE=:IN_MASTERCODE;");
			queryInsert.bindValue(0	, Base->GetMachineID());
			queryInsert.bindValue(1 , MasterCode);
			if(queryInsert.exec()==false){
				DB.rollback();
	
				goto	FuncEnd;
			}
			{
				QString	S=QString("SELECT * FROM MASTERDATA where MASTERCODE=")+QString::number(MasterCode)
						 +QString(" and MACHINEID=")+QString::number(Base->GetMachineID());
				QSqlQuery query2(S,DB);
				if(query2.next ()==false){
					DB.rollback();
					goto PAgain;
				}
			}
		}
		DB.commit();
FuncEnd:;
	}
	UnlockDB();

	return MasterCode;
}


bool	__G_SQLUpdateMasterData(QSqlDatabase &DB ,LayersBase *Base ,ParamGlobal *GParam
							  ,QBuffer &GeneralBuff ,QBuffer &SettingBuff 
							  ,QBuffer &LightDataArray 
							  ,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
							  ,QBuffer &TopViewBuff)
{
	if(Base->IsDatabaseOk()==false){
		return false;
	}
	bool	Ret=true;
	int	ThresholdLevel			=Base->GetThresholdLevelID();
	int	ThresholdParentLevelID	=Base->GetThresholdParentLevelID();
	LockDB();
	{
		QSqlQuery query(DB);
		query.prepare("UPDATE MASTERDATA "
					 "SET MACHINEID=:MACHINEID"
					 ", REGTIME=:REGTIME"
					 ", WORKERID=:WORKERID"
					 ", MASTERNAME=:MASTERNAME"
					 ",REMARK=:REMARK"
					 ",VERSION=:VERSION"
					 ",LASTEDITTIME=:LASTEDITTIME"
					 ",CATEGORYID=:CATEGORYID"
					 ",TOPVIEW=:TOPVIEW"
					 ",DOTPERLINE=:DOTPERLINE"
					 ",MAXLINES=:MAXLINES"
					 ",PAGENUMB=:PAGENUMB"
					 ",LAYERNUMB=:LAYERNUMB"
					 ",PHASENUMB=:PHASENUMB"
					 ",GENERALDATA=:GENERALDATA"
					 ",SETTINGDATA=:SETTINGDATA "
					 ",MASTERTYPE=:MASTERTYPE "
					 ",LIGHTDATA=:LIGHTDATA "
					 ",GENERALSTOCKER=:GENERALSTOCKER "
					 ",RESULTANALIZER=:RESULTANALIZER "
					 ",LIBFOLDERID=:LIBFOLDERID "
					 ",THRESHOLDLEVELID=:THRESHOLDLEVELID "
					 ",THRESHOLDLEVELPARENTID=:THRESHOLDLEVELPARENTID "
					 "WHERE MASTERCODE=:IN_MASTERCODE;");

		query.bindValue(0	, Base->GetMachineIDFromMaster());
		query.bindValue(1	, Base->GetRegTime().GetQDateTime());
		query.bindValue(2	, Base->GetWorkerID());
		query.bindValue(3	, Base->GetMasterName());
		query.bindValue(4	, Base->GetRemark());
		query.bindValue(5	, Base->GetVersion());
		query.bindValue(6	, Base->GetLastEditTime().GetQDateTime());
		query.bindValue(7	, Base->GetCategoryID());
		query.bindValue(8	, TopViewBuff.buffer());
		query.bindValue(9	, GParam->DotPerLine);
		query.bindValue(10	, GParam->MaxLines);
		query.bindValue(11	, GParam->PageNumb);
		query.bindValue(12	, GParam->LayerNumb);
		query.bindValue(13	, GParam->PhaseNumb);
		query.bindValue(14	, GeneralBuff.buffer());
		query.bindValue(15	, SettingBuff.buffer());
		query.bindValue(16	, Base->GetMasterType());
		query.bindValue(17	, LightDataArray.buffer());
		query.bindValue(18	, GeneralStockerBuff.buffer());
		query.bindValue(19	, ResultAnalizerBuff.buffer());
		query.bindValue(20	, Base->GetLibFolderID());
		query.bindValue(21	, ThresholdLevel);
		query.bindValue(22	, ThresholdParentLevelID);
		query.bindValue(23	, Base->GetMasterCode());
		if(query.exec()==false){
			Ret=false;
			goto	FuncEnd;
		}
FuncEnd:;
	}

	UnlockDB();

	return Ret;
}

bool	__G_SQLLoadMasterData(QSqlDatabase &DB ,LayersBase *Base 
							,int masterCode
							,QBuffer &GeneralBuff ,QBuffer &SettingBuff ,QBuffer &LightBuff,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
							,int32 &MasterCode ,int32 &MachineID
							,XDateTime &RegTime
							,QString &MasterName ,QString &Remark
							,int32 &Version
							,XDateTime &LastEditTime
							,int32 &CategoryID
							,int16 &MasterType
							,QImage &TopView
							,int32 &LibFolderID
							,int32 &ThresholdLevelID
							,int32 &ThresholdLevelParentID)
{
	if(Base->IsDatabaseOk()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QString	S=QString("SELECT * FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			MasterCode		=query.value(query.record().indexOf("MASTERCODE")).toInt();
			MachineID		=query.value(query.record().indexOf("MACHINEID"	)).toInt();
			RegTime			=query.value(query.record().indexOf("REGTIME"	)).toDateTime();
			//Base->WorkerID		=query.value(query.record().indexOf("WORKERID"	)).toInt();
			MasterName		=query.value(query.record().indexOf("MASTERNAME")).toString();
			Remark			=query.value(query.record().indexOf("REMARK"	)).toString();
			Version			=query.value(query.record().indexOf("VERSION"	)).toInt();
			LastEditTime	=query.value(query.record().indexOf("LASTEDITTIME")).toDateTime();
			CategoryID		=query.value(query.record().indexOf("CATEGORYID")).toInt();
			MasterType		=query.value(query.record().indexOf("MASTERTYPE")).toInt();
			QByteArray	Gd	=query.value(query.record().indexOf("GENERALDATA")).toByteArray();
			GeneralBuff.setData(Gd);

			QByteArray	Sd=query.value(query.record().indexOf("SETTINGDATA")).toByteArray();
			SettingBuff.setData(Sd);

			QByteArray	Tv	=query.value(query.record().indexOf("TOPVIEW")).toByteArray();
			TopView.loadFromData(Tv);

			QByteArray	Ld=query.value(query.record().indexOf("LIGHTDATA")).toByteArray();
			LightBuff.setData(Ld);

			QByteArray	Gs=query.value(query.record().indexOf("GENERALSTOCKER")).toByteArray();
			GeneralStockerBuff.setData(Gs);
			QByteArray	RA=query.value(query.record().indexOf("RESULTANALIZER")).toByteArray();
			ResultAnalizerBuff.setData(RA);

			LibFolderID				=query.value(query.record().indexOf("LIBFOLDERID"	)).toInt();
			ThresholdLevelID		=query.value(query.record().indexOf("THRESHOLDLEVELID")).toInt();
			ThresholdLevelParentID	=query.value(query.record().indexOf("THRESHOLDLEVELPARENTID")).toInt();
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLLoadMasterData2(QSqlDatabase &DB
							,int masterCode
							,int32 &MachineID
							,XDateTime &RegTime
							,QString &MasterName ,QString &Remark
							,int32 &Version
							,XDateTime &LastEditTime
							,int32 &CategoryID
							,int16 &MasterType
							,int &iDotPerLine
							,int &iMaxLines
							,int &iLayerNumb
							,int &iPageNumb
							,int &iPhaseNumb
							,int32 &LibFolderID
							,int32 &ThresholdLevelID
							,int32 &ThresholdLevelParentID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QString	S=QString("SELECT * FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			MachineID				=query.value(query.record().indexOf("MACHINEID"	)).toInt();
			RegTime					=query.value(query.record().indexOf("REGTIME"	)).toDateTime();
			MasterName				=query.value(query.record().indexOf("MASTERNAME")).toString();
			Remark					=query.value(query.record().indexOf("REMARK"	)).toString();
			Version					=query.value(query.record().indexOf("VERSION"	)).toInt();
			LastEditTime			=query.value(query.record().indexOf("LASTEDITTIME")).toDateTime();
			CategoryID				=query.value(query.record().indexOf("CATEGORYID")).toInt();
			MasterType				=query.value(query.record().indexOf("MASTERTYPE")).toInt();

			iDotPerLine				=query.value(query.record().indexOf("DOTPERLINE")).toInt();
			iMaxLines				=query.value(query.record().indexOf("MAXLINES")).toInt();
			iLayerNumb				=query.value(query.record().indexOf("LAYERNUMB")).toInt();
			iPageNumb				=query.value(query.record().indexOf("PAGENUMB")).toInt();
			iPhaseNumb				=query.value(query.record().indexOf("PHASENUMB")).toInt();
			LibFolderID				=query.value(query.record().indexOf("LIBFOLDERID")).toInt();
			ThresholdLevelID		=query.value(query.record().indexOf("THRESHOLDLEVELID")).toInt();
			ThresholdLevelParentID	=query.value(query.record().indexOf("THRESHOLDLEVELPARENTID")).toInt();
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
DEFFUNCEX	bool	__G_SQLCheckMasterName(QSqlDatabase &DB
										,int32 MachineID
										,QString MasterName
										,IntList &RetMasterCodes)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QString	S =QString("SELECT MASTERCODE FROM MASTERDATA where MASTERNAME=\'")+MasterName
				  +QString("\' and MACHINEID=")+QString::number(MachineID);
		QSqlQuery query(S,DB);
		if(query.next ()==true){
			do{
				int	iMasterCode		=query.value(query.record().indexOf("MASTERCODE")).toInt();
				RetMasterCodes.Add(iMasterCode);
			}while(query.next ()==true);
			goto	FuncEnd;
		}
FuncEnd:;
	}

	UnlockDB();

	return true;
}

bool	__G_SQLGetMasterInfo(QSqlDatabase &DB ,int masterCode
										,int32 &MachineID
										,XDateTime &RegTime
										,QString &MasterName ,QString &Remark
										,int32 &Version
										,XDateTime &LastEditTime
										,int32 &CategoryID
										,int16 &MasterType
										,int32 &LibFolderID
										,int32 &ThresholdLevelID
										,int32 &ThresholdLevelParentID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	QString	S=QString("SELECT * FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	LockDB();
	{
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			MachineID				=query.value(query.record().indexOf("MACHINEID"	)).toInt();
			RegTime					=query.value(query.record().indexOf("REGTIME"	)).toDateTime();
			MasterName				=query.value(query.record().indexOf("MASTERNAME")).toString();
			Remark					=query.value(query.record().indexOf("REMARK"	)).toString();
			Version					=query.value(query.record().indexOf("VERSION"	)).toInt();
			LastEditTime			=query.value(query.record().indexOf("LASTEDITTIME")).toDateTime();
			CategoryID				=query.value(query.record().indexOf("CATEGORYID")).toInt();
			MasterType				=query.value(query.record().indexOf("MASTERTYPE")).toInt();
			LibFolderID				=query.value(query.record().indexOf("LIBFOLDERID")).toInt();
			ThresholdLevelID		=query.value(query.record().indexOf("THRESHOLDLEVELID")).toInt();
			ThresholdLevelParentID	=query.value(query.record().indexOf("THRESHOLDLEVELPARENTID")).toInt();
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

QImage	*__G_SQLLoadMasterTopview(QSqlDatabase &DB ,int masterCode)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QImage	*D=NULL;
	LockDB();
	{
		QString	S=QString("SELECT TOPVIEW FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			goto	FuncEnd;
		}
		{
			QByteArray	Gd	=query.value(query.record().indexOf("TOPVIEW")).toByteArray();
			D=new QImage();
			D->loadFromData(Gd);
		}
FuncEnd:;
	}
	UnlockDB();
	return D;
}

bool	__G_SQLLoadMasterSetting(QSqlDatabase &DB ,int masterCode,QBuffer &SettingBuff )
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QString	S=QString("SELECT SETTINGDATA FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			QByteArray	Sd=query.value(query.record().indexOf("SETTINGDATA")).toByteArray();
			SettingBuff.setData(Sd);
		}
FuncEnd:;
	}
	UnlockDB();
	return Ret;
}

bool	__G_SQLLoadWorker(QSqlDatabase &DB ,int workerID ,QString &RetName)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
	QString	S=QString("SELECT NAME FROM WORKER where WORKERID=")+QString::number(workerID);
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		RetName	=query.value(query.record().indexOf("NAME")).toString();
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLSavePage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff ,QBuffer &SettingBuff,QBuffer &ImageBuff)
{
	if(DB.isValid()==false){
		return false;
	}
	int	globalPage=CParam->GetGlobalPageFromLocal(*GParam,PageBase->GetPage());
	QString	S=QString("SELECT MASTERCODE FROM MASTERPAGE where MASTERCODE=")+QString::number(masterCode)
			 +QString(" and PAGECODE=")+QString::number(globalPage);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			QSqlQuery queryInsrt(DB);
			queryInsrt.prepare("INSERT INTO MASTERPAGE(MASTERCODE,PAGECODE) "
				"VALUES(:MASTERCODE,:PAGECODE);");		
			queryInsrt.bindValue(0	, masterCode);
			queryInsrt.bindValue(1	, globalPage);
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
		{
			GeneralBuff.seek(0);
			SettingBuff.seek(0);

			QSqlQuery queryUpdate(DB);
			QString	QStr="UPDATE MASTERPAGE "
						 "SET VERSION=:VERSION"
						 ",DOTPERLINE=:DOTPERLINE"
						 ",MAXLINES=:MAXLINES"
						 ",LAYERNUMB=:LAYERNUMB"
						 ",GENERALDATA=:GENERALDATA"
						 ",SETTINGDATA=:SETTINGDATA"
						 ",MASTERIMAGE=:MASTERIMAGE ";
			for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
				if(p->GetBlobName().isEmpty()==true){
					continue;
				}
				AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
				if(base==NULL){
					continue;
				}
				//AlgorithmInPageRoot	*ap=base->GetPageData(PageBase->GetPage());
				//if(ap==NULL)
				//	continue;
				QStr=QStr + QString(",") +p->GetBlobName() + QString("=:")+p->GetBlobName();
			}
			QStr=QStr + " WHERE MASTERCODE=:IN_MASTERCODE and PAGECODE=:IN_PAGECODE;";

			queryUpdate.prepare(QStr);
			queryUpdate.bindValue(0	, PageBase->GetLayersBase()->GetVersion());
			queryUpdate.bindValue(1	, GParam->DotPerLine);
			queryUpdate.bindValue(2	, GParam->MaxLines);
			queryUpdate.bindValue(3	, GParam->LayerNumb);
			queryUpdate.bindValue(4	, GeneralBuff.buffer());
			queryUpdate.bindValue(5	, SettingBuff.buffer());
			queryUpdate.bindValue(6	, ImageBuff.buffer());

			int	N=7;
			if(PageBase->GetLayersBase()->GetVersion()<=10){
				for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext(),N++){
					if(p->GetBlobName().isEmpty()==true){
						continue;
					}
					AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					AlgorithmInPageRoot	*ap=base->GetPageData(PageBase->GetPage());
					if(ap==NULL){
						continue;
					}

					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					base->SaveOnlyBase(&Buff);
					if(ap->Save(&Buff)==false){
						Ret=false;
						goto	FuncEnd;
					}
					queryUpdate.bindValue(N, Buff.buffer());
				}
			}
			{
				queryUpdate.bindValue(N	, masterCode);
				queryUpdate.bindValue(N+1, globalPage);
				if(queryUpdate.exec()==false){
					Ret=false;
					goto	FuncEnd;
				}
			}
		}
FuncEnd:;
	}
	UnlockDB();
	
	return Ret;
}
bool	__G_SQLLoadPage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff 
					  ,QBuffer &ImageBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion)
{
	if(DB.isValid()==false){
		return false;
	}
	int	globalPage=CParam->GetGlobalPageFromLocal(*GParam,PageBase->GetPage());
	QString	S=QString("SELECT * FROM MASTERPAGE where MASTERCODE=")+QString::number(masterCode)
		+QString(" and PAGECODE=")+QString::number(globalPage);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			iVersion		=query.value(query.record().indexOf("VERSION"	)).toInt();
			QByteArray	Gd=query.value(query.record().indexOf("GENERALDATA")).toByteArray();
			GeneralBuff.setData(Gd);

			QByteArray	Sd=query.value(query.record().indexOf("SETTINGDATA")).toByteArray();
			SettingBuff.setData(Sd);

			int	iLayerNumb		=query.value(query.record().indexOf("LAYERNUMB"	)).toInt();
			QByteArray	Mi=query.value(query.record().indexOf("MASTERIMAGE")).toByteArray();
			ImageBuff.setData(Mi);

			if(iVersion<=10){
				int	n=0;
				for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext(),n++){
					ValidLogicDLLBuff[n]=false;
					if(p->GetBlobName().isEmpty()==true){
						continue;
					}
					AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					AlgorithmInPageRoot	*ap=base->GetPageData(PageBase->GetPage());
					if(ap==NULL){
						continue;
					}
					LogicDLLBuff[n]=query.value(query.record().indexOf(p->GetBlobName())).toByteArray();
					ValidLogicDLLBuff[n]=true;
				}
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
bool	__G_SQLSavePageNoImage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff ,QBuffer &SettingBuff)
{
	if(DB.isValid()==false){
		return false;
	}
	int	globalPage=CParam->GetGlobalPageFromLocal(*GParam,PageBase->GetPage());
	QString	S=QString("SELECT MASTERCODE FROM MASTERPAGE where MASTERCODE=")+QString::number(masterCode)
		+QString(" and PAGECODE=")+QString::number(globalPage);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			QSqlQuery queryInsrt(DB);
			queryInsrt.prepare("INSERT INTO MASTERPAGE(MASTERCODE,PAGECODE) "
				"VALUES(:MASTERCODE,:PAGECODE);");		
			queryInsrt.bindValue(0	, masterCode);
			queryInsrt.bindValue(1	, globalPage);
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
		{
			GeneralBuff.seek(0);
			SettingBuff.seek(0);

			QSqlQuery queryUpdate(DB);
			QString	QStr="UPDATE MASTERPAGE "
						 "SET VERSION=:VERSION"
						 ",DOTPERLINE=:DOTPERLINE"
						 ",MAXLINES=:MAXLINES"
						 ",LAYERNUMB=:LAYERNUMB"
						 ",GENERALDATA=:GENERALDATA"
						 ",SETTINGDATA=:SETTINGDATA";
			if(PageBase->GetLayersBase()->GetVersion()<=10){
				for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext()){
					if(p->GetBlobName().isEmpty()==true){
						continue;
					}
					AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					QStr=QStr + QString(",") +p->GetBlobName() + QString("=:")+p->GetBlobName();
				}
			}
			QStr=QStr + " WHERE MASTERCODE=:IN_MASTERCODE and PAGECODE=:IN_PAGECODE;";

			queryUpdate.prepare(QStr);
			queryUpdate.bindValue(0	, PageBase->GetLayersBase()->GetVersion());
			queryUpdate.bindValue(1	, GParam->DotPerLine);
			queryUpdate.bindValue(2	, GParam->MaxLines);
			queryUpdate.bindValue(3	, GParam->LayerNumb);
			queryUpdate.bindValue(4	, GeneralBuff.buffer());
			queryUpdate.bindValue(5	, SettingBuff.buffer());

			int	N=6;
			if(PageBase->GetLayersBase()->GetVersion()<=10){
				for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext(),N++){
					if(p->GetBlobName().isEmpty()==true){
						continue;
					}
					AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					AlgorithmInPageRoot	*ap=base->GetPageData(PageBase->GetPage());
					if(ap==NULL){
						continue;
					}

					QBuffer	Buff;
					Buff.open(QIODevice::ReadWrite);
					base->SaveOnlyBase(&Buff);
					if(ap->Save(&Buff)==false){
						Ret=false;
						goto	FuncEnd;
					}
					queryUpdate.bindValue(N, Buff.buffer());
				}
			}
			{
				queryUpdate.bindValue(N	, masterCode);
				queryUpdate.bindValue(N+1, globalPage);
				if(queryUpdate.exec()==false){
					Ret=false;
					goto	FuncEnd;
				}
			}
		}
FuncEnd:;
	}
	UnlockDB();
	
	return Ret;
}
bool	__G_SQLLoadPageNoImage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion)
{
	if(DB.isValid()==false){
		return false;
	}
	int	globalPage=CParam->GetGlobalPageFromLocal(*GParam,PageBase->GetPage());
	QString	S=QString("SELECT * FROM MASTERPAGE where MASTERCODE=")+QString::number(masterCode)
		 	+QString(" and PAGECODE=")+QString::number(globalPage);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			iVersion	=query.value(query.record().indexOf("VERSION"	)).toInt();
			QByteArray	Gd=query.value(query.record().indexOf("GENERALDATA")).toByteArray();
			GeneralBuff.setData(Gd);

			QByteArray	Sd=query.value(query.record().indexOf("SETTINGDATA")).toByteArray();
			SettingBuff.setData(Sd);

			int	iLayerNumb		=query.value(query.record().indexOf("LAYERNUMB"	)).toInt();

			if(iVersion<=10){
				int	n=0;
				for(LogicDLL *p=PageBase->GetLayersBase()->GetLogicDLLBase()->GetFirst();p!=NULL;p=p->GetNext(),n++){
					ValidLogicDLLBuff[n]=false;
					if(p->GetBlobName().isEmpty()==true){
						continue;
					}
					AlgorithmBase	*base=PageBase->GetLayersBase()->GetAlgorithmBase(p->GetDLLRoot(),p->GetDLLName());
					if(base==NULL){
						continue;
					}
					AlgorithmInPageRoot	*ap=base->GetPageData(PageBase->GetPage());
					if(ap==NULL){
						continue;
					}
					LogicDLLBuff[n]=query.value(query.record().indexOf(p->GetBlobName())).toByteArray();
					ValidLogicDLLBuff[n]=true;
				}
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLAddMasterFieldData(QSqlDatabase &DB ,int32 masterCode ,const QString &fieldName, const QVariant &data)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		QString	QStr=QString("UPDATE MASTERDATA SET ")+fieldName+QString("=:IN_DATA")
				+QString(" WHERE MASTERCODE=:IN_MASTERCODE");

		queryUpdate.prepare(QStr);
		queryUpdate.bindValue(0	, data);
		queryUpdate.bindValue(1	, masterCode);
		if(queryUpdate.exec()==false){
			Ret=false;
			goto	FuncEnd;
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLAddRelationFieldData(QSqlDatabase &DB ,int32 RelationCode ,const QString &fieldName, const QVariant &data)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		QString	QStr=QString("UPDATE MASTERRELATION SET ")+fieldName+QString("=:IN_DATA")
				+QString(" WHERE RELATIONCODE=:IN_RELATIONCODE");

		queryUpdate.prepare(QStr);
		queryUpdate.bindValue(0	, data);
		queryUpdate.bindValue(1	, RelationCode);
		if(queryUpdate.exec()==false){
			Ret=false;
			goto	FuncEnd;
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
bool	__G_SQLLoadMasterFieldData(QSqlDatabase &DB ,int32 masterCode ,const QString &fieldName, QVariant &data)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT ")+fieldName
			 +QString(" FROM MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		data=query.value(query.record().indexOf(fieldName));
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLLoadRelationFieldData(QSqlDatabase &DB ,int32 RelationCode ,const QString &fieldName, QVariant &data)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT ")+fieldName
			 +QString(" FROM MASTERRELATION where RELATIONCODE=")+QString::number(RelationCode);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		data=query.value(query.record().indexOf(fieldName));
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SQLSaveOutlineOfset(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT * FROM MACHINE where MACHINEID=")+QString::number(MachineID);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			QSqlQuery queryUpdate(DB);
			QString	QStr=QString("UPDATE MACHINE SET OUTLINEOFFSET=:IN_DATA")
					+QString(" WHERE MACHINEID=")+QString::number(MachineID);

			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			OutlineOffsetWriter->Save(&Buff);

			queryUpdate.prepare(QStr);
			queryUpdate.bindValue(0	, Buff.buffer());
			if(queryUpdate.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
bool	__G_SQLLoadOutlineOfset(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT * FROM MACHINE where MACHINEID=")+QString::number(MachineID);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			QVariant	data=query.value(query.record().indexOf("OUTLINEOFFSET"));
			QByteArray	BArray=data.toByteArray();
			QBuffer	Buff(&BArray);
			Buff.open(QIODevice::ReadWrite);
			if(OutlineOffsetWriter->Load(&Buff)==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

//=====================================================================================

bool	__G_CheckAndCreateLibTypeInDatabase(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT LIBTYPE FROM INSPECTLIBTYPE where LIBTYPE=")+QString::number(Base->GetLibType());
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			Ret=true;
			goto	FuncEnd;
		}
		{
			QSqlQuery queryInsrt(DB);
			queryInsrt.prepare("INSERT INTO INSPECTLIBTYPE(LIBTYPE,TYPENAME) "
								"VALUES(:LIBTYPE,:TYPENAME);");
			queryInsrt.bindValue(0	, Base->GetLibType());
			queryInsrt.bindValue(1	, QString(Base->GetLibTypeName()));
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}


int		__G_EnumLibrary(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList)
{
	if(DB.isValid()==false){
		return 0;
	}
	return __G_EnumLibraryByType(DB ,Base->GetLibType(),LibFolderID ,LibIDList);
}
int		__G_EnumLibraryByType(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	N=0;
	LibIDList.RemoveAll();
	QString	S=QString("SELECT LIBID,LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
			+QString(" AND LIBFOLDERID=")+QString::number(LibFolderID)
			+QString(" order by LIBID;");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			do{
				int		LibID	=query.value(query.record().indexOf("LIBID"		)).toInt();
				QString	LibName	=query.value(query.record().indexOf("LIBNAME"	)).toString();
				LibIDList.AppendList(new AlgorithmLibraryList(LibType,LibID,LibName));
				N++;
			}while(query.next ()==true);
		}
	}
	UnlockDB();

	return N;
}
int		__G_EnumLibraryByTypeInt(QSqlDatabase &DB ,int LibType,int LibFolderID ,int IDList[] ,int MaxDimCount)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	N=0;
	QString	S=QString("SELECT LIBID,LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
			 +QString(" AND LIBFOLDERID=")+QString::number(LibFolderID)
			 +QString(" order by LIBID;");
	LockDB();
	{
		if(MaxDimCount>0){
			QSqlQuery query(S ,DB);
			if(query.next ()==true){
				do{
					int		LibID	=query.value(query.record().indexOf("LIBID"		)).toInt();
					IDList[N]=LibID;
					N++;
				}while(query.next ()==true && N<MaxDimCount);
			}
		}
	}
	UnlockDB();

	return N;
}
int		__G_EnumAllLibraryByType(QSqlDatabase &DB ,int LibType,AlgorithmLibraryListContainer &LibIDList)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	N=0;
	LibIDList.RemoveAll();
	QString	S=QString("SELECT LIBID,LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
			 +QString(" order by LIBID;");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			do{
				int		LibID	=query.value(query.record().indexOf("LIBID"		)).toInt();
				QString	LibName	=query.value(query.record().indexOf("LIBNAME"	)).toString();
				LibIDList.AppendList(new AlgorithmLibraryList(LibType,LibID,LibName));
				N++;
			}while(query.next ()==true);
		}
	}
	UnlockDB();

	return N;
}
int		__G_EnumAllLibraryByLibFolder	(QSqlDatabase &DB ,int LibFolderID	,AlgorithmLibraryListContainer &LibIDList)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	N=0;
	LibIDList.RemoveAll();
	QString	S=QString("SELECT LIBTYPE,LIBID,LIBNAME FROM INSPECTLIB where LIBFOLDERID=")+QString::number(LibFolderID)
			 +QString(" order by LIBTYPE,LIBID;");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			do{
				int		LibType	=query.value(query.record().indexOf("LIBTYPE"	)).toInt();
				int		LibID	=query.value(query.record().indexOf("LIBID"		)).toInt();
				QString	LibName	=query.value(query.record().indexOf("LIBNAME"	)).toString();
				LibIDList.AppendList(new AlgorithmLibraryList(LibType,LibID,LibName));
				N++;
			}while(query.next ()==true);
		}
	}
	UnlockDB();

	return N;
}
void		__G_GetLibraryNames(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryListContainer &LibIDList)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	{
		for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext()){
			QString	S=QString("SELECT LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(Base->GetLibType())
					 +QString(" AND LIBID=")+QString::number(a->GetLibID());
			QSqlQuery query(S ,DB);
			if(query.next ()==true){
				a->SetLibName(query.value(query.record().indexOf("LIBNAME"	)).toString());
			}
		}
	}
	UnlockDB();
}

QString		__G_GetLibraryName(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibID)
{
	if(DB.isValid()==false){
		return "";
	}
	QString	RetStr;
	QString	S=QString("SELECT LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(Base->GetLibType())
			 +QString(" AND LIBID=")+QString::number(LibID);
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			RetStr=query.value(query.record().indexOf("LIBNAME"	)).toString();
		}
	}
	UnlockDB();
	return RetStr;
}

QString		__G_GetLibraryName2(QSqlDatabase &DB ,int LibType ,int LibID)
{
	if(DB.isValid()==false){
		return "";
	}
	QString	RetStr;
	QString	S=QString("SELECT LIBNAME FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
				+QString(" AND LIBID=")+QString::number(LibID);
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			RetStr=query.value(query.record().indexOf("LIBNAME"	)).toString();
		}
	}
	UnlockDB();
	return RetStr;
}

QColor	__G_GetLibraryColor(QSqlDatabase &DB ,int LibType ,int LibID)
{
	QColor	LibColor;
	QString	S=QString("SELECT LIBCOLOR FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
				+QString(" AND LIBID=")+QString::number(LibID);
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			QByteArray	Ld	=query.value(query.record().indexOf("LIBCOLOR"	)).toByteArray();
			QBuffer		LBuff(&Ld);
			LBuff.open(QIODevice::ReadWrite);
			
			::Load(&LBuff,LibColor);
		}
	}
	UnlockDB();
	return LibColor;
}
QString	__G_GetLibraryComment(QSqlDatabase &DB ,int LibType ,int LibID)
{
	QString	LibComment;
	QString	S=QString("SELECT LIBCOMMENT FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType)
				+QString(" AND LIBID=")+QString::number(LibID);
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			QByteArray	Ld	=query.value(query.record().indexOf("LIBCOMMENT"	)).toByteArray();
			QBuffer		LBuff(&Ld);
			LBuff.open(QIODevice::ReadWrite);
			
			::Load(&LBuff,LibComment);
		}
	}
	UnlockDB();
	return LibComment;
}

bool	__G_SaveNew(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	Data.SetLibID(1);
	QString	S=QString("SELECT MAX(LIBID) FROM INSPECTLIB where LIBTYPE=")+QString::number(Base->GetLibType());
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			Data.SetLibID(query.value(0).toInt()+1);
		}

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS,SOURCEID,LIBCOLOR,LIBCOMMENT) "
			"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ADAPTEDLAYERS,:SOURCEID,:LIBCOLOR,:LIBCOMMENT);");
		queryInsrt.bindValue(0	, Base->GetLibType());
		queryInsrt.bindValue(1	, Data.GetLibID());
		queryInsrt.bindValue(2	, Data.GetLibFolderID());
		queryInsrt.bindValue(3	, Data.GetLibName());
		queryInsrt.bindValue(4	, Data.GetLastWorker());
		queryInsrt.bindValue(5	, Data.GetLastUpdated().GetQDateTime());

		int	DataVersion=-Data.GetDataVersion();
		queryInsrt.bindValue(6	, DataVersion);
		{
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			if(Data.SaveBlob(&Buff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			{
				QByteArray	AData=Buff.buffer();
				queryInsrt.bindValue(7	, AData);
				//if(queryInsrt.exec()==false){
				//	UnlockDB();
				//	return false;
				//}
			}
		}

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(Data.GetAdaptedPickLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			if(Data.GetAdaptedGenLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			{
				QByteArray	AData=LBuff.buffer();
				queryInsrt.bindValue(8	, AData);
				//if(queryInsrt.exec()==false){
				//	UnlockDB();
				//	return false;
				//}
			}
		}
		queryInsrt.bindValue(9	, Data.GetSourceID());

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibColor())==false){
				Ret=false;
				goto	FuncEnd;
			}
			{
				QByteArray	AData=LBuff.buffer();
				queryInsrt.bindValue(10	, AData);
				//if(queryInsrt.exec()==false){
				//	UnlockDB();
				//	return false;
				//}
			}
		}
		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibComment())==false){
				Ret=false;
				goto	FuncEnd;
			}
			{
				QByteArray	AData=LBuff.buffer();
				queryInsrt.bindValue(11	, AData);
				if(queryInsrt.exec()==false){
					Ret=false;
					goto	FuncEnd;
				}
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

bool	__G_SaveNewWithLibID(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS,SOURCEID,LIBCOLOR,LIBCOMMENT) "
			"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ADAPTEDLAYERS,:SOURCEID,:LIBCOLOR,:LIBCOMMENT);");
		queryInsrt.bindValue(0	, Base->GetLibType());
		queryInsrt.bindValue(1	, Data.GetLibID());
		queryInsrt.bindValue(2	, Data.GetLibFolderID());
		queryInsrt.bindValue(3	, Data.GetLibName());
		queryInsrt.bindValue(4	, Data.GetLastWorker());
		queryInsrt.bindValue(5	, Data.GetLastUpdated().GetQDateTime());
		int	DataVersion=-Data.GetDataVersion();
		queryInsrt.bindValue(6	, DataVersion);
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(Data.SaveBlob(&Buff)==false){
			Ret=false;
			goto	FuncEnd;
		}
		queryInsrt.bindValue(7	, Buff.buffer());
//		if(queryInsrt.exec()==false){
//			UnlockDB();
//			return false;
//		}

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(Data.GetAdaptedPickLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			if(Data.GetAdaptedGenLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryInsrt.bindValue(8	, LBuff.buffer());
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
		queryInsrt.bindValue(9	, Data.GetSourceID());

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibColor())==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryInsrt.bindValue(10	, LBuff.buffer());
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibComment())==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryInsrt.bindValue(11	, LBuff.buffer());
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
bool	__G_Update (QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data)
{
	if(DB.isValid()==false){
		return false;
	}
	if(Data.GetLibID()==-1){
		return false;
	}
	bool	Ret=true;
	QString	QStr="UPDATE INSPECTLIB "
				 "SET LIBFOLDERID=:LIBFOLDERID"
				 ",LIBNAME=:LIBNAME"
				 ",LASTWORKER=:LASTWORKER"
				 ",LASTUPDATED=:LASTUPDATED"
				 ",DATAVERSION=:DATAVERSION"
				 ",LIBDATA=:LIBDATA"
				 ",ADAPTEDLAYERS=:ADAPTEDLAYERS"
				 ",SOURCEID=:SOURCEID"
				 ",LIBCOLOR=:LIBCOLOR"
				 ",LIBCOMMENT=:LIBCOMMENT";
	QStr=QStr + " where LIBTYPE=:IN_LIBTYPE AND LIBID=:IN_LIBID;";
	LockDB();
	{
		QSqlQuery queryUpdate(DB);

		queryUpdate.prepare(QStr);
		queryUpdate.bindValue(0	, Data.GetLibFolderID());
		queryUpdate.bindValue(1	, Data.GetLibName());
		queryUpdate.bindValue(2	, Data.GetLastWorker());
		queryUpdate.bindValue(3	, Data.GetLastUpdated().GetQDateTime());
		int	DataVersion=-Data.GetDataVersion();
		queryUpdate.bindValue(4	, DataVersion);
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(Data.SaveBlob(&Buff)==false){
			Ret=false;
			goto	FuncEnd;
		}
		queryUpdate.bindValue(5	, Buff.buffer());

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(Data.GetAdaptedPickLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			if(Data.GetAdaptedGenLayers().Save(&LBuff)==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryUpdate.bindValue(6	, LBuff.buffer());
		}

		queryUpdate.bindValue(7	, Data.GetSourceID());

		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibColor())==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryUpdate.bindValue(8	, LBuff.buffer());
		}
		{
			QBuffer	LBuff;
			LBuff.open(QIODevice::ReadWrite);
			if(::Save(&LBuff,Data.GetLibComment())==false){
				Ret=false;
				goto	FuncEnd;
			}
			queryUpdate.bindValue(9	, LBuff.buffer());
		}
		{
			queryUpdate.bindValue(10	, Base->GetLibType());
			queryUpdate.bindValue(11, Data.GetLibID());
			
			if(queryUpdate.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
bool	__G_Load   (QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	QString	S=QString("SELECT * FROM INSPECTLIB where LIBTYPE=")+QString::number(Base->GetLibType())
		+QString(" AND LIBID=")+QString::number(Data.GetLibID());
	LockDB();
	{
		QSqlQuery *query=new QSqlQuery(S ,DB);
		if(query->next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		int	LibID=query->value(query->record().indexOf("LIBID"			)).toInt();
		if(LibID==0){
			Ret=false;
			goto	FuncEnd;
		}
		{
			Data.SetLibID		(LibID);
			Data.SetLibFolderID	(query->value(query->record().indexOf("LIBFOLDERID"	)).toInt());
			Data.SetLibName		(query->value(query->record().indexOf("LIBNAME"		)).toString());
			Data.SetLastWorker	(query->value(query->record().indexOf("LASTWORKER"	)).toInt());
			Data.SetLastUpdated	(query->value(query->record().indexOf("LASTUPDATED"	)).toDateTime());
			int	DataVersion	=query->value(query->record().indexOf("DATAVERSION"	)).toInt();
			Data.SetDataVersion	(abs(DataVersion));
			Data.SetSourceID	(query->value(query->record().indexOf("SOURCEID"		)).toInt());

			QByteArray	Gd	=query->value(query->record().indexOf("LIBDATA"		)).toByteArray();
			QBuffer		Buff(&Gd);
			Buff.open(QIODevice::ReadWrite);
			if(DataVersion<=0){
				if(Data.LoadBlob(&Buff)==false){
					Ret=false;
					goto	FuncEnd;
				}
			}
			else{
				AlgorithmLibrary	*a=Data.GetFirst();
				if(a==NULL){
					AlgorithmLibraryContainer	*Container=Data.GetParent();
					if(Container!=NULL){
						a=Container->CreateNew();
						a->SetThresholdLevelID(1);
						Data.AppendList(a);
						a->SetParent(&Data);
					}
				}
				if(a!=NULL){
					if(a->LoadBlob(&Buff)==false){
						Ret=false;
						goto	FuncEnd;
					}
					a->SetParent(&Data);
				}
			}
		}
		{
			{
				QByteArray	Ld	=query->value(query->record().indexOf("ADAPTEDLAYERS"		)).toByteArray();
				QBuffer		LBuff(&Ld);
				LBuff.open(QIODevice::ReadWrite);
				IntList		LayersList;
				if(LayersList.Load(&LBuff)==true){
					Data.SetAdaptedPickLayers(LayersList);
				}
				else{
					IntList		HLayersList;
					Data.SetAdaptedPickLayers(HLayersList);
				}
				if(LayersList.Load(&LBuff)==true){
					Data.SetAdaptedGenLayers(LayersList);
				}
				else{
					IntList		HLayersList;
					Data.SetAdaptedGenLayers(HLayersList);
				}
			}
		}
		{
			{
				QByteArray	Ld	=query->value(query->record().indexOf("LIBCOLOR"	)).toByteArray();
				QBuffer		LBuff(&Ld);
				LBuff.open(QIODevice::ReadWrite);
				QColor	LibColor;
				if(::Load(&LBuff,LibColor)==true){
					Data.SetLibColor(LibColor);
				}
			}
			{
				QByteArray	Ld	=query->value(query->record().indexOf("LIBCOMMENT"	)).toByteArray();
				QBuffer		LBuff(&Ld);
				LBuff.open(QIODevice::ReadWrite);
				QString	LibComment;
				if(::Load(&LBuff,LibComment)==true){
					Data.SetLibComment(LibComment);
				}
			}
		}
	FuncEnd:;
		delete	query;
	}
	UnlockDB();
	return Ret;
}

bool	__G_Delete (QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int32 LibID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("DELETE FROM INSPECTLIB WHERE LIBTYPE=:LIBTYPE and LIBID=:LIBID");
		queryDelete.bindValue(0	, Base->GetLibType());
		queryDelete.bindValue(1	, LibID);
		if(queryDelete.exec()==false){
			Ret=false;
			goto	FuncEnd;
		}
FuncEnd:;
	}
	UnlockDB();
	return Ret;
}


QSqlQuery *__S_LibFolderFindFirst(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QSqlQuery *query;
	QString	S=QString("SELECT NUMBERINFOLDER,LIBFOLDERID,LIBPARENTID,FOLDERNAME FROM LIBFOLDER where LIBPARENTID=0 ORDER BY NUMBERINFOLDER;");
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}

QSqlQuery *__S_CreateQuery(QSqlDatabase &DB,const QString &Str)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(Str,DB);
	}
	UnlockDB();
	return query;
}

bool	__S_FindNext(QSqlQuery *query)
{
	if(query==NULL){
		return false;
	}
	bool	ret;
	LockDB();
	{
		ret=query->next();
	}
	UnlockDB();
	return ret;
}

bool	__S_DeleteQuery(QSqlQuery *query)
{
	if(query==NULL){
		return false;
	}
	LockDB();
	{
		delete	query;
	}
	UnlockDB();

	return true;
}

void	__S_LibFolderGetData(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder)
{
	LockDB();
	{
		LibFolderID		=query->value(query->record().indexOf("LIBFOLDERID")).toInt();
		FolderName		=query->value(query->record().indexOf("FOLDERNAME")).toString();
		ParentID		=query->value(query->record().indexOf("LIBPARENTID")).toInt();
		NumberInFolder	=query->value(query->record().indexOf("NUMBERINFOLDER")).toInt();
	}
	UnlockDB();
}
bool	__S_LibFolderFindData(QSqlDatabase &DB,int LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=false;
	QString	S=QString("SELECT NUMBERINFOLDER,LIBPARENTID,FOLDERNAME FROM LIBFOLDER where LIBFOLDERID=")+QString::number(LibFolderID);
			  
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			FolderName		=query.value(query.record().indexOf("FOLDERNAME")).toString();
			ParentID		=query.value(query.record().indexOf("LIBPARENTID")).toInt();
			NumberInFolder	=query.value(query.record().indexOf("NUMBERINFOLDER")).toInt();
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}
QSqlQuery *__S_LibFolderFindFirstByParentID(QSqlDatabase &DB ,int parentID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT NUMBERINFOLDER,LIBFOLDERID,LIBPARENTID,FOLDERNAME FROM LIBFOLDER where LIBPARENTID=")
			 +QString::number(parentID)
			 +QString(" order by NUMBERINFOLDER;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}

int __S_LibFolderCreatenew(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	ret;
	LockDB();
	{
		DB.transaction();
		QSqlQuery queryInsert(DB);
		//queryInsert.prepare("CALL PROCMASTERCATEGORYINSERT");
		queryInsert.prepare("EXECUTE PROCEDURE PROCLIBFOLDERINSERT");
		queryInsert.exec();

		QSqlQuery query("SELECT MAX(LIBFOLDERID) from LIBFOLDER" ,DB);
		query.next ();
		ret=query.value(0).toInt();
		DB.commit();
	}
	UnlockDB();

	return ret;
}

void	__S_LibFolderUpdate(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int LibFolderID ,int MasterCode)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	if(MasterCode>=0){
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE LIBFOLDER "
							"SET LIBPARENTID=:LIBPARENTID"
							", FOLDERNAME=:FOLDERNAME "
							 "WHERE LIBFOLDERID=:IN_LIBFOLDERID;");

		queryUpdate.bindValue(0, ParentID);
		queryUpdate.bindValue(1, FolderName);
		queryUpdate.bindValue(2, LibFolderID);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	else{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE LIBFOLDER "
							"SET LIBPARENTID=:LIBPARENTID"
							", FOLDERNAME=:FOLDERNAME "
							" ,RELATEDMASTERCODE=:RELATEDMASTERCODE "
							 "WHERE LIBFOLDERID=:IN_LIBFOLDERID;");

		queryUpdate.bindValue(0, ParentID);
		queryUpdate.bindValue(1, FolderName);
		queryUpdate.bindValue(2, MasterCode);
		queryUpdate.bindValue(3, LibFolderID);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	UnlockDB();
}

void	__S_LibCopy(QSqlDatabase &DB ,int sourceFolderID ,int destFolderID ,int LibType)
{
	if(DB.isValid()==false){
		return;
	}
	if(sourceFolderID==destFolderID){
		return;
	}

	bool	Ret=true;
	if(LibType>=0){
		QString	Sid=QString("SELECT MAX(LIBID) FROM INSPECTLIB where LIBTYPE=")+QString::number(LibType);
		LockDB();
		{
			QSqlQuery GetMaxIDQuery(Sid ,DB);
			int	MaxID=1;
			if(GetMaxIDQuery.next()==true){
				MaxID=GetMaxIDQuery.value(0).toInt();
			}

			QString	S=QString("SELECT LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS FROM INSPECTLIB where LIBFOLDERID=")
					 +QString::number(sourceFolderID)
					 +QString(" and  LIBTYPE=")
					 +QString::number(LibType);
			QSqlQuery query(S ,DB);
			if(query.next()==true){
				do{
					//int	LibType		=query.value(query.record().indexOf("LIBTYPE")).toInt();

					int	LibFolderID	=destFolderID;
					int			LibID			=query.value(query.record().indexOf("LIBID")).toInt();
					QString		LibName			=query.value(query.record().indexOf("LIBNAME")).toString();
					int			LastWorker		=query.value(query.record().indexOf("LASTWORKER")).toInt();
					XDateTime	LastUpdated		=query.value(query.record().indexOf("LASTUPDATED")).toDateTime();
					int			DataVersion		=query.value(query.record().indexOf("DATAVERSION")).toInt();
					QByteArray	LibData			=query.value(query.record().indexOf("LIBDATA")).toByteArray();
					QByteArray	AdaptedLayers	=query.value(query.record().indexOf("ADAPTEDLAYERS")).toByteArray();
					MaxID++;

					LastUpdated=XDateTime::currentDateTime();

					QSqlQuery queryInsrt(DB);
					queryInsrt.prepare("INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS,SOURCEID) "
						"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ADAPTEDLAYERS,:SOURCEID);");
					queryInsrt.bindValue(0	, LibType		);
					queryInsrt.bindValue(1	, MaxID			);
					queryInsrt.bindValue(2	, LibFolderID	);
					queryInsrt.bindValue(3	, LibName		);
					queryInsrt.bindValue(4	, LastWorker	);
					queryInsrt.bindValue(5	, LastUpdated.GetQDateTime()	);
					queryInsrt.bindValue(6	, DataVersion	);
					queryInsrt.bindValue(7	, LibData		);
					queryInsrt.bindValue(8	, AdaptedLayers	);
					queryInsrt.bindValue(9	, LibID	);			//SourceID=LibID
					if(queryInsrt.exec()==false){
						goto	FuncEnd;
					}
				}while(query.next()==true);
			}
			FuncEnd:;
		}
		UnlockDB();
	}
	else{	//Copy all libraries in folder
		QString	S=QString("SELECT LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS FROM INSPECTLIB where LIBFOLDERID=")
				 +QString::number(sourceFolderID);
		
		LockDB();
		{
			QSqlQuery query(S ,DB);
			if(query.next()==true){
				do{
					//int	LibType		=query.value(query.record().indexOf("LIBTYPE")).toInt();

					int	LibFolderID	=destFolderID;
					int			tLibType		=query.value(query.record().indexOf("LIBTYPE")).toInt();
					int			LibID			=query.value(query.record().indexOf("LIBID")).toInt();				
					QString		LibName			=query.value(query.record().indexOf("LIBNAME")).toString();
					int			LastWorker		=query.value(query.record().indexOf("LASTWORKER")).toInt();
					XDateTime	LastUpdated		=query.value(query.record().indexOf("LASTUPDATED")).toDateTime();
					int			DataVersion		=query.value(query.record().indexOf("DATAVERSION")).toInt();
					QByteArray	LibData			=query.value(query.record().indexOf("LIBDATA")).toByteArray();
					QByteArray	AdaptedLayers	=query.value(query.record().indexOf("ADAPTEDLAYERS")).toByteArray();
				

					LastUpdated=XDateTime::currentDateTime();
	
					QString	Sid=QString("SELECT MAX(LIBID) FROM INSPECTLIB where LIBTYPE=")+QString::number(tLibType);
					QSqlQuery GetMaxIDQuery(Sid ,DB);
					int	MaxID=1;
					if(GetMaxIDQuery.next()==true){
						MaxID=GetMaxIDQuery.value(0).toInt();
					}
					MaxID++;

					QSqlQuery queryInsrt(DB);
					queryInsrt.prepare("INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ADAPTEDLAYERS,SOURCEID) "
						"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ADAPTEDLAYERS,:SOURCEID);");
					queryInsrt.bindValue(0	, tLibType		);
					queryInsrt.bindValue(1	, MaxID			);
					queryInsrt.bindValue(2	, LibFolderID	);
					queryInsrt.bindValue(3	, LibName		);
					queryInsrt.bindValue(4	, LastWorker	);
					queryInsrt.bindValue(5	, LastUpdated.GetQDateTime()	);
					queryInsrt.bindValue(6	, DataVersion	);
					queryInsrt.bindValue(7	, LibData		);
					queryInsrt.bindValue(8	, AdaptedLayers	);
					queryInsrt.bindValue(9	, LibID	);			//SourceID=LibID
					if(queryInsrt.exec()==false){
						goto	FuncEnd2;
					}
				}while(query.next()==true);
			}
			FuncEnd2:;
		}
		UnlockDB();
	}
}

int		__S_GetFirstLibFolderByMasterCode(QSqlDatabase &DB ,int MasterCode ,QString &FolderName)
{
	if(DB.isValid()==false){
		return 0;
	}
	QString	S=QString("SELECT LIBFOLDERID,FOLDERNAME FROM LIBFOLDER where RELATEDMASTERCODE=")
			 +QString::number(MasterCode)
			 +QString(" order by LIBFOLDERID;");
	int		LibFolderID=-1;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			int		LibFolderID=query.value(query.record().indexOf("LIBFOLDERID")).toInt();
			FolderName	=query.value(query.record().indexOf("FOLDERNAME")).toString();
			goto	FuncEnd;
		}
	FuncEnd:;
	}
	UnlockDB();

	return -1;
}
DEFFUNCEX	bool	__S_GetLibraryLayers(QSqlDatabase &DB ,int LibType,int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers)
{
	if(DB.isValid()==false){
		return false;
	}
	QString	S=QString("SELECT ADAPTEDLAYERS FROM INSPECTLIB where LIBTYPE=")
		+QString::number(LibType)
		+QString(" and  LIBID=")
		+QString::number(LibID);
	bool	Ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			QByteArray	AdaptedLayers	=query.value(query.record().indexOf("ADAPTEDLAYERS")).toByteArray();
			QBuffer		LBuff(&AdaptedLayers);
			LBuff.open(QIODevice::ReadWrite);
			IntList		LayersList;
			AdaptedPickLayers.Load(&LBuff);
			AdaptedGenLayers.Load(&LBuff);
			Ret=true;
			goto	FuncEnd;
		}
	FuncEnd:;
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	int	__S_GetLibrarySourceID(QSqlDatabase &DB ,int LibType,int LibID)
{
	if(DB.isValid()==false){
		return 0;
	}
	QString	S=QString("SELECT SOURCEID FROM INSPECTLIB where LIBTYPE=")
			 +QString::number(LibType)
			 +QString(" and  LIBID=")
			 +QString::number(LibID);
	int	Ret=-1;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			Ret=query.value(0).toInt();
		}
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	int		__S_EnumLibraryInSourceID(QSqlDatabase &DB ,int LibType,int SourceLibID ,IntList &RetLibID)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	N=0;
	RetLibID.RemoveAll();
	QString	S=QString("SELECT LIBID FROM INSPECTLIB where LIBTYPE=")
		+QString::number(LibType)
		+QString(" and  SOURCEID=")
		+QString::number(SourceLibID)
		+QString(" order by LIBID;");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			do{
				int		LibID	=query.value(query.record().indexOf("LIBID"	)).toInt();
				RetLibID.Add(LibID);
				N++;
			}while(query.next ()==true);
		}
	}
	UnlockDB();
	return N;
}
DEFFUNCEX	int		__S_GetLibraryFolderID(QSqlDatabase &DB ,int LibType,int LibID)
{
	if(DB.isValid()==false){
		return 0;
	}
	QString	S=QString("SELECT LIBFOLDERID FROM INSPECTLIB where LIBTYPE=")
			 +QString::number(LibType)
			 +QString(" and  LIBID=")
			 +QString::number(LibID);
	int	Ret=-1;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			Ret=query.value(0).toInt();
		}
	}
	UnlockDB();
	return Ret;
}

//========================================================================================================

QSqlQuery *__S_ColorFolderFindFirst(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT NUMBERINFOLDER,COLORFOLDERID,COLORPARENTID,FOLDERNAME FROM COLORSAMPLEFOLDER where COLORPARENTID=0 ORDER BY NUMBERINFOLDER;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
void	__S_ColorFolderGetData(QSqlQuery *query ,int &ColorFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder)
{
	if(query==NULL){
		return;
	}
	LockDB();
	{
		ColorFolderID	=query->value(query->record().indexOf("COLORFOLDERID"))	.toInt();
		FolderName		=query->value(query->record().indexOf("FOLDERNAME"))	.toString();
		ParentID		=query->value(query->record().indexOf("COLORPARENTID"))	.toInt();
		NumberInFolder	=query->value(query->record().indexOf("NUMBERINFOLDER")).toInt();
	}
	UnlockDB();
}
QSqlQuery *__S_ColorFolderFindFirstByParentID(QSqlDatabase &DB ,int parentID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT NUMBERINFOLDER,COLORFOLDERID,COLORPARENTID,FOLDERNAME FROM COLORSAMPLEFOLDER where COLORPARENTID=")
			 +QString::number(parentID)
			 +QString(" order by NUMBERINFOLDER;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
int		__S_ColorFolderCreatenew(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	ret;
	LockDB();
	{
		DB.transaction();
		QSqlQuery queryInsert(DB);
		//queryInsert.prepare("CALL PROCMASTERCATEGORYINSERT");
		queryInsert.prepare("EXECUTE PROCEDURE PROCCOLORFOLDERINSERT");
		queryInsert.exec();

		QSqlQuery query("SELECT MAX(COLORFOLDERID) from COLORSAMPLEFOLDER" ,DB);
		query.next ();
		ret=query.value(0).toInt();
		DB.commit();
	}
	UnlockDB();

	return ret;
}
void	__S_ColorFolderUpdate(QSqlDatabase &DB ,int ParentID ,QString FolderName, int ColorFolderID)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE COLORSAMPLEFOLDER "
							"SET COLORPARENTID=:COLORPARENTID"
							", FOLDERNAME=:FOLDERNAME "
							 "WHERE COLORFOLDERID=:IN_COLORFOLDERID;");
		queryUpdate.bindValue(0, ParentID);
		queryUpdate.bindValue(1, FolderName);
		queryUpdate.bindValue(2, ColorFolderID);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	UnlockDB();
}



//========================================================================================================
QSqlQuery *__S_MasterCategoryFindFirst(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT CATEGORYID,PARENTID,FOLDERNAME,REMARK FROM MASTERCATEGORY where PARENTID=0;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();

	return query;
}
	
void	__S_MasterCategoryGetData(QSqlQuery *query ,int &CategoryID ,QString &FolderName ,int &ParentID ,QString &Remark)
{
	if(query==NULL){
		return;
	}
	LockDB();
	{
		CategoryID	=query->value(query->record().indexOf("CATEGORYID")).toInt();
		FolderName	=query->value(query->record().indexOf("FOLDERNAME")).toString();
		ParentID	=query->value(query->record().indexOf("PARENTID")).toInt();
		Remark		=query->value(query->record().indexOf("REMARK")).toString();
	}
	UnlockDB();
}

QSqlQuery *__S_MasterCategoryFindFirstByParentID(QSqlDatabase &DB ,int parentID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT CATEGORYID,PARENTID,FOLDERNAME,REMARK FROM MASTERCATEGORY where PARENTID=")
		+QString::number(parentID);
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}

int __S_MasterCategoryCreatenew(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return 0;
	}
	int	ret;
	LockDB();
	{
		DB.transaction();
		QSqlQuery queryInsert(DB);
		//queryInsert.prepare("CALL PROCMASTERCATEGORYINSERT");
		queryInsert.prepare("EXECUTE PROCEDURE PROCMASTERCATEGORYINSERT");
		queryInsert.exec();

		QSqlQuery query("SELECT MAX(CATEGORYID) from MASTERCATEGORY" ,DB);
		query.next ();
		ret=query.value(0).toInt();
		DB.commit();
	}
	UnlockDB();
	return ret;
}

void	__S_MasterCategoryUpdate(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int FolderID,const QString &Remark)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE MASTERCATEGORY "
							"SET PARENTID=:PARENTID"
							", FOLDERNAME=:FOLDERNAME "
							", REMARK=:REMARK "
							 "WHERE CATEGORYID=:IN_CATEGORYID;");

		queryUpdate.bindValue(0, ParentID);
		queryUpdate.bindValue(1, FolderName);
		queryUpdate.bindValue(2, Remark);
		queryUpdate.bindValue(3, FolderID);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	UnlockDB();
}


QSqlQuery *__S_LightFindFirst(QSqlDatabase &DB ,int MachineCode)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QSqlQuery *query;
	LockDB();
	if(MachineCode==-1){
		QString	S=QString("select * FROM LIGHT");
		query=new QSqlQuery(S ,DB);
	}
	else{
		QString	S=QString("select * FROM LIGHT where MACHINEID=")+QString::number(MachineCode);
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
bool	__S_GetFieldValue(QSqlQuery *query,const char *FieldName,QVariant &v)
{
	if(query==NULL){
		return NULL;
	}
	LockDB();
	{
		int	PointNumber=query->record().indexOf(FieldName);
		v=query->value(PointNumber);
		//v=query->boundValue(FieldName);
	}
	UnlockDB();

	return true;
}
QSqlQuery *__S_GetLight(QSqlDatabase &DB ,int MachineCode,int LightID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	LockDB();
	if(MachineCode==-1){
		QString	S=QString("select * FROM LIGHT where LIGHTID=")+QString::number(LightID);
		QSqlQuery *query=new QSqlQuery(S ,DB);
		UnlockDB();
		return query;
	}
	else{
		QString	S=QString("select * FROM LIGHT where MACHINEID=")+QString::number(MachineCode)
				 +QString(" and LIGHTID=")+QString::number(LightID);
		QSqlQuery *query=new QSqlQuery(S ,DB);
		UnlockDB();
		return query;
	}
}
bool	__S_CreateNewLight(QSqlDatabase &DB ,int MachineID 
							,QString DLLIDName ,QString Name ,QString Remark 
							,QByteArray &LightData ,QByteArray &LightImage)
{
	if(DB.isValid()==false){
		return false;
	}
	QSqlQuery *q=__S_LightFindLast(DB ,MachineID);
	if(q==NULL){
		return false;
	}
	QVariant vLightID;
	if(__S_GetFieldValue(q,"LIGHTID",vLightID)==false){
		return false;
	}
	int	LightID=vLightID.toInt()+1;
	__S_DeleteQuery(q);

	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO LIGHT(MACHINEID,LIGHTID,LIGHTDATA,DLLIDNAME,NAME,REMARK,UPDATETIME,LIGHTIMAGE) "
			"VALUES(:MACHINEID,:LIGHTID,:LIGHTDATA,:DLLIDNAME,:NAME,:REMARK,:UPDATETIME,:LIGHTIMAGE);");
		queryInsrt.bindValue(0	, MachineID);
		queryInsrt.bindValue(1	, LightID);
		queryInsrt.bindValue(2	, LightData);
		queryInsrt.bindValue(3	, DLLIDName);
		queryInsrt.bindValue(4	, Name);
		queryInsrt.bindValue(5	, Remark);
		XDateTime	UpdateTime	=XDateTime::currentDateTime();
		queryInsrt.bindValue(6	, UpdateTime.GetQDateTime());
		queryInsrt.bindValue(7	, LightImage);
		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;

}
QSqlQuery *__S_LightFindLast(QSqlDatabase &DB ,int MachineCode)
{
	if(DB.isValid()==false){
		return NULL;
	}
	LockDB();

	if(MachineCode==-1){
		QString	S=QString("select * FROM LIGHT");
		QSqlQuery *query=new QSqlQuery(S ,DB);
		query->last();
		UnlockDB();
		return query;
	}
	else{
		QString	S=QString("select * FROM LIGHT where MACHINEID=")+QString::number(MachineCode);
		QSqlQuery *query=new QSqlQuery(S ,DB);
		query->last();
		UnlockDB();
		return query;
	}
}
bool	__S_UpdateLight(QSqlDatabase &DB ,int MachineCode,int LightID ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	ret;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE LIGHT "
							"SET NAME=:NAME"
							", REMARK=:REMARK "
							", LIGHTDATA=:LIGHTDATA "
							", LIGHTIMAGE=:LIGHTIMAGE "
							"WHERE MACHINEID=:MACHINEID and LIGHTID=:LIGHTID;");

		queryUpdate.bindValue(0, Name);
		queryUpdate.bindValue(1, Remark);
		queryUpdate.bindValue(2, LightData);
		queryUpdate.bindValue(3, LightImage);
		queryUpdate.bindValue(4, MachineCode);
		queryUpdate.bindValue(5, LightID);
		ret=queryUpdate.exec();
	}
	UnlockDB();
	return ret;
}
bool	__S_DeleteLight(QSqlDatabase &DB ,int MachineCode,int LightID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	ret;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("delete from LIGHT "
							" WHERE MACHINEID=:MACHINEID and LIGHTID=:LIGHTID;");

		queryDelete.bindValue(0, MachineCode);
		queryDelete.bindValue(1, LightID);
		ret=queryDelete.exec();
	}
	UnlockDB();
	return ret;
}

//========================================================================================================
QSqlQuery *__S_GetLibraryTypeFirst(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT LIBTYPE,TYPENAME FROM INSPECTLIBTYPE");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}

void	__S_DeleteLibraryType(QSqlQuery *query)
{
	if(query==NULL){
		return;
	}
	LockDB();
	delete	query;
	UnlockDB();
}

void	__S_GetLibraryTypeData(QSqlQuery *query,int &LibType,QString &LibName)
{
	if(query==NULL){
		return;
	}
	LockDB();
	LibType	=query->value(query->record().indexOf("LIBTYPE")).toInt();
	LibName	=query->value(query->record().indexOf("TYPENAME")).toString();
	UnlockDB();
}

bool	__S_CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db ,QString &BlobName)
{
	bool	Ret=true;
	LockDB();
	{
		QSqlRecord *R=new QSqlRecord();
		*R=db.record ("MASTERPAGE");
		int index=R->indexOf ( BlobName );
		if(index<0){
			QSqlQuery query(db);
			QString	AddedString=QString("ALTER TABLE MASTERPAGE ADD ")
								+BlobName
								+QString(" BLOB SUB_TYPE 0 SEGMENT SIZE 80");
			query.prepare(AddedString);
			if(query.exec()==false){
				Ret=false;
			}
		}
		delete	R;
FuncEnd:;
	}
	UnlockDB();
	//delete	R;
	return Ret;
}
QSqlDatabase	*__S_OpenDatabase(QSqlDatabase *DB)
{
	LockDB();
//	BYTE	*TestS1=new BYTE[100];
//	delete	[]TestS1;				Error occurs

	if(DB==NULL){
		DB=new QSqlDatabase();
	}

	if(DB->isOpen()==false){
		DB->open();
	}
	UnlockDB();
	return DB;
}
QSqlDatabase	*__S_CloseDatabase(QSqlDatabase *DB)
{
	LockDB();
	if(DB!=NULL && DB->isOpen()==true){
		QString	ConStr=DB->connectionName();
		DB->close();
		QSqlDatabase::removeDatabase(ConStr);
	}
	UnlockDB();
	return DB;
}

bool	__S_IsValidDatabase(QSqlDatabase *DB)
{
	if(DB==NULL){
		return false;
	}
	LockDB();
	if(DB->isValid()==false){
		UnlockDB();
		return false;
	}
	if(DB->isOpen()==false){
		UnlockDB();
		return false;
	}
	UnlockDB();
	return true;
}
//========================================================================================================
int		__G_EnumColorSample		(QSqlDatabase &DB ,int SelectedColorFolder,ColorSampleList EnumData[] ,int MaxNumb)
{
	int	L=0;
	LockDB();
	if(SelectedColorFolder<0){
		QString	S=QString("SELECT AUTOCOUNT,NAME FROM COLORSAMPLE");
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			do{
				EnumData[L].SetAutoCount(query.value(query.record().indexOf("AUTOCOUNT")).toInt());
				EnumData[L].SetName		(query.value(query.record().indexOf("NAME")).toString());
				L++;
				if(L>=MaxNumb){
					goto	FuncEnd1;
				}
			}while(query.next()==true);
		}
		FuncEnd1:;
	}
	else{
		QString	S=QString("SELECT AUTOCOUNT,NAME FROM COLORSAMPLE WHERE COLORFOLDERID=")+QString::number(SelectedColorFolder);
		QSqlQuery query(S ,DB);
		int	L=0;
		if(query.next()==true){
			do{
				EnumData[L].SetAutoCount(query.value(query.record().indexOf("AUTOCOUNT")).toInt());
				EnumData[L].SetName		(query.value(query.record().indexOf("NAME")).toString());
				L++;
				if(L>=MaxNumb){
					goto	FuncEnd2;
				}
			}while(query.next()==true);
		}
		FuncEnd2:;
	}
	UnlockDB();
	return L;
}
bool	__G_SaveNewColorSample	(QSqlDatabase &DB ,ColorSampleList &Data)
{
	QString	S=QString("SELECT max(AUTOCOUNT) FROM COLORSAMPLE");
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		Data.SetAutoCount(0);
		if(query.next()==true){
			Data.SetAutoCount(query.value(0).toInt()+1);
		}
		Data.SetUpdateTime(XDateTime::currentDateTime());

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO COLORSAMPLE(AUTOCOUNT,NAME,UPDATETIME,SAMPLETYPE,SAMPLEDATA,COLORFOLDERID) "
			"VALUES(:AUTOCOUNT,:NAME,:UPDATETIME,:SAMPLETYPE,:SAMPLEDATA,:COLORFOLDERID);");
		queryInsrt.bindValue(0	, Data.GetAutoCount());
		queryInsrt.bindValue(1	, Data.GetName());
		queryInsrt.bindValue(2	, Data.GetUpdateTime().GetQDateTime());
		queryInsrt.bindValue(3	, (int)Data.GetDataType());

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(Data.SaveData(&Buff)==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			queryInsrt.bindValue(4	, Buff.buffer());
			queryInsrt.bindValue(5	, Data.GetSelectedColorFolder());
			if(queryInsrt.exec()==false){
				Ret=false;
				goto	FuncEnd;
			}
		}
	FuncEnd:;
	}
	UnlockDB();
	return Ret;
}
bool	__G_UpdateColorSample	(QSqlDatabase &DB ,ColorSampleList &Data)
{
	if(Data.GetAutoCount()<0){
		return false;
	}
	bool	ret=true;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE COLORSAMPLE "
							"SET NAME=:NAME"
							", UPDATETIME=:UPDATETIME "
							", SAMPLETYPE=:SAMPLETYPE "
							", SAMPLEDATA=:SAMPLEDATA "
							", COLORFOLDERID=:COLORFOLDERID "
							"WHERE AUTOCOUNT=:AUTOCOUNT;");

		Data.SetUpdateTime(XDateTime::currentDateTime());
		queryUpdate.bindValue(0, Data.GetName());
		queryUpdate.bindValue(1, Data.GetUpdateTime().GetQDateTime());
		queryUpdate.bindValue(2, (int)Data.GetDataType());
		queryUpdate.bindValue(3, (int)Data.GetSelectedColorFolder());
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		if(Data.SaveData(&Buff)==false){
			ret=false;
			goto	FuncEnd;
		}
		{
			queryUpdate.bindValue(4	, Buff.buffer());
			queryUpdate.bindValue(5, Data.GetAutoCount());
			ret=queryUpdate.exec();
		}
FuncEnd:;
	}
	UnlockDB();
	return ret;
}
bool	__G_LoadColorSample		(QSqlDatabase &DB ,ColorSampleList &Data ,QBuffer &DataBuff)
{
	QString	S=QString("SELECT AUTOCOUNT,NAME,UPDATETIME,SAMPLETYPE,SAMPLEDATA,COLORFOLDERID from COLORSAMPLE where AUTOCOUNT=")
			 +QString::number(Data.GetAutoCount());
	bool	ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			Data.SetAutoCount	(query.value(query.record().indexOf("AUTOCOUNT"	)).toInt());
			Data.SetName		(query.value(query.record().indexOf("NAME"		)).toString());
			Data.SetUpdateTime	(query.value(query.record().indexOf("UPDATETIME")).toDateTime());
			Data.SetDataType	((ColorSampleList::ColorDataType)query.value(query.record().indexOf("SAMPLETYPE")).toInt());
			Data.SetSelectedColorFolder(query.value(query.record().indexOf("COLORFOLDERID")).toInt());

			QByteArray	Gd	=query.value(query.record().indexOf("SAMPLEDATA")).toByteArray();
			DataBuff.setData(Gd);
			ret=true;
		}
	}
	UnlockDB();
	return ret;
}
bool	__G_DeleteColorSample	(QSqlDatabase &DB ,ColorSampleList &Data)
{
	bool	ret;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("delete from COLORSAMPLE "
							" WHERE AUTOCOUNT=:AUTOCOUNT;");

		queryDelete.bindValue(0, Data.GetAutoCount());
		ret=queryDelete.exec();
	}
	UnlockDB();
	return ret;
}

DEFFUNCEX	int		__G_EnumMachine(QSqlDatabase &DB ,int MachineIDList[] ,int MaxList)
{
	QString	S=QString("SELECT MACHINEID FROM MACHINE order by MACHINEID");
	int	n=0;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		while(query.next()==true && n<MaxList){
			MachineIDList[n]=query.value(query.record().indexOf("MACHINEID")).toInt();
			n++;
		}
	}
	UnlockDB();
	return n;
}

bool	__G_GetMachineInfo(QSqlDatabase &DB ,int MachineID 
								,QString &NetID
								,QString &Name
								,QString &Version
								,QString &Remark)
{
	QString	S=QString("SELECT NETID,NAME,VERSION,REMARK FROM MACHINE where MACHINEID=")
		+QString::number(MachineID);
	bool	Ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			//int	LibType		=query.value(query.record().indexOf("LIBTYPE")).toInt();
			NetID		=query.value(query.record().indexOf("NETID")).toString();
			Name		=query.value(query.record().indexOf("NAME")).toString();
			Version		=query.value(query.record().indexOf("VERSION")).toString();
			Remark		=query.value(query.record().indexOf("REMARK")).toString();
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}

bool	__G_MachineIDExists(QSqlDatabase &DB ,int MachineID)
{
	QString	S=QString("SELECT NAME FROM MACHINE where MACHINEID=")
		     +QString::number(MachineID);
	bool	Ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}

bool	__G_CreateNewMasterRelation(QSqlDatabase &DB 
												,int &RetRelationCode
												,const QString &RelationNumber
												,const QString &RelationName
												,const QString &Remark
												,int RelationType
												,QByteArray &CommonData
												,int32 ThresholdLevelID)
{
	QString	S=QString("SELECT max(RELATIONCODE) FROM MASTERRELATION");
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		RetRelationCode=1;
		if(query.next()==true){
			RetRelationCode=query.value(0).toInt()+1;
		}

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO MASTERRELATION(RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,VERSION,RELATIONTYPE,COMMONDATA,THRESHOLDLEVELID) "
			"VALUES(:RELATIONCODE,:REGTIME,:RELATIONNUMBER,:RELATIONNAME,:REMARK,:VERSION,:RELATIONTYPE,:COMMONDATA,:THRESHOLDLEVELID);");
		queryInsrt.bindValue(0	, RetRelationCode);
		queryInsrt.bindValue(1	, XDateTime::currentDateTime().GetQDateTime());
		queryInsrt.bindValue(2	, RelationNumber);
		queryInsrt.bindValue(3	, RelationName);
		queryInsrt.bindValue(4	, Remark);
		queryInsrt.bindValue(5	, (int)RegulusVersion);
		queryInsrt.bindValue(6	, RelationType);
		queryInsrt.bindValue(7	, CommonData);
		queryInsrt.bindValue(8	, ThresholdLevelID);

		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;
}

bool	__G_UpdateMasterRelation(QSqlDatabase &DB 
												,int RelationCode
												,const QString &RelationNumber
												,const QString &RelationName
												,const QString &Remark
												,int RelationType
												,QByteArray &CommonData
												,int32 ThresholdLevelID)
{
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(DB);
		query.prepare("UPDATE MASTERRELATION "
					 "SET RELATIONNAME=:RELATIONNAME"
					 ", RELATIONNUMBER=:RELATIONNUMBER"
					 ", REMARK=:REMARK"
					 ", RELATIONTYPE=:RELATIONTYPE"
					 ", COMMONDATA=:COMMONDATA"
					 ", THRESHOLDLEVELID=:THRESHOLDLEVELID"
					 " WHERE RELATIONCODE=:IN_RELATIONCODE;");

		query.bindValue(0	, RelationName);
		query.bindValue(1	, RelationNumber);
		query.bindValue(2	, Remark);
		query.bindValue(3	, RelationType);
		query.bindValue(4	, CommonData);
		query.bindValue(5	, ThresholdLevelID);
		query.bindValue(6	, RelationCode);
		if(query.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();

	return Ret;
}

bool	__G_FindMasterRelation(  QSqlDatabase &DB 
								,const QString &RelationName
								,const QString &RelationNumber
								,const QString &Remark
								,IntList &RelationCodes)
{
	int	N=0;
	QString	S=QString("SELECT RELATIONCODE FROM MASTERRELATION where RELATIONNAME=\'")
			+ RelationName
			+ QString("\' and RELATIONNUMBER=\'")
			+ RelationNumber
			+ QString("\'");
	LockDB();
	{
		RelationCodes.RemoveAll();
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			do{
				int	RelationCode=query.value(query.record().indexOf("RELATIONCODE")).toInt();
				RelationCodes.Add(RelationCode);
			}while(query.next()==true);
		}
	}
	UnlockDB();
	return true;
}

bool	__G_SetRelationOnMasterData(QSqlDatabase &DB ,int MasterCode,int RelationCode ,int RelationID)
{
	bool	ret;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE MASTERDATA "
							"SET RELATIONCODE=:RELATIONCODE"
							", RELATIONID=:RELATIONID "
							"WHERE MASTERCODE=:MASTERCODE;");

		queryUpdate.bindValue(0, RelationCode);
		queryUpdate.bindValue(1, RelationID);
		queryUpdate.bindValue(2, MasterCode);
		ret=queryUpdate.exec();
	}
	UnlockDB();
	return ret;
}

int		__G_SearchMasterCode(QSqlDatabase &DB ,int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount)
{
	int	N=0;
	QString	S=QString("SELECT MASTERCODE,MACHINEID,RELATIONID FROM MASTERDATA where RELATIONCODE=")
		+QString::number(RelationCode);
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			do{
				if(N>=MaxListCount){
					goto	FuncEnd;
				}
				{
					MasterListDim[N].MasterCode=query.value(query.record().indexOf("MASTERCODE")).toInt();
					MasterListDim[N].MachineID =query.value(query.record().indexOf("MACHINEID")).toInt();
					MasterListDim[N].RelationID=query.value(query.record().indexOf("RELATIONID")).toInt();
				}
				N++;
			}while(query.next()==true);
		}
FuncEnd:;
	}
	UnlockDB();
	return N;
}

int		__G_GetRelationCode(QSqlDatabase &DB ,int MasterCode)
{
	QString	S=QString("SELECT RELATIONCODE FROM MASTERDATA where MASTERCODE=")
			 +QString::number(MasterCode);
	int	RetRelationCode=-1;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			RetRelationCode=query.value(0).toInt();

			QString	S2  =QString("SELECT RELATIONCODE FROM MASTERRELATION where RELATIONCODE=")
						+QString::number(RetRelationCode);
			QSqlQuery query2(S2 ,DB);
			if(query2.next()==true){
			}
		}
	}
	UnlockDB();
	return RetRelationCode;
}
bool	__G_GetMasterRelation(QSqlDatabase &DB 
										,int RelationCode
										,QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID)
{
	QString	S=QString("SELECT RELATIONNUMBER,RELATIONNAME,REMARK,RELATIONTYPE,COMMONDATA,THRESHOLDLEVELID FROM MASTERRELATION where RELATIONCODE=")
			 +QString::number(RelationCode);
	bool	Ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			RetRelationNumber	=query.value(0).toString();
			RetRelationName		=query.value(1).toString();
			RetRemark			=query.value(2).toString();
			RetRelationType		=query.value(3).toInt();
			CommonData			=query.value(query.record().indexOf("COMMONDATA")).toByteArray();
			ThresholdLevelID	=query.value(5).toInt();
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}
bool	__G_EnumMasterRelation(QSqlDatabase &DB ,IntList &RelationCodes)
{
	QString	S=QString("SELECT RELATIONCODE FROM MASTERRELATION");
	LockDB();
	{
		RelationCodes.RemoveAll();

		QSqlQuery query(S ,DB);
		while(query.next()==true){
			int	RelationCode	=query.value(0).toInt();
			RelationCodes.Add(RelationCode);
		}
	}
	UnlockDB();
	return true;
}
bool	__G_UpdateLastLoadedTimeMasterRelation(QSqlDatabase &DB 
												,int RelationCode)
{
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(DB);
		query.prepare("UPDATE MASTERRELATION "
					 "SET LASTLOADEDTIME=:LASTLOADEDTIME"
					 " WHERE RELATIONCODE=:IN_RELATIONCODE;");
		QDateTime	Qm=QDateTime::currentDateTime();

		query.bindValue(0	, Qm);
		query.bindValue(1	, RelationCode);
		if(query.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();

	return Ret;
}



int		__G_GetMaxLearningIDAndInsertEmpty(QSqlDatabase &DB)
{
	int	MaxLearningID=0;
	QString	S=QString("SELECT max(LEARNINGID) FROM LEARNING");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			MaxLearningID=query.value(0).toInt()+1;
		}
		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO LEARNING(LEARNINGID,MACHINEID,UPDATETIME,SAMPLETYPE) "
			"VALUES(:LEARNINGID,:MACHINEID,:UPDATETIME,:SAMPLETYPE);");
		queryInsrt.bindValue(0	, MaxLearningID);
		queryInsrt.bindValue(1	, 0);
		queryInsrt.bindValue(2	, XDateTime::currentDateTime().GetQDateTime());
		queryInsrt.bindValue(3	, 0);

		if(queryInsrt.exec()==false){
			MaxLearningID=-1;
		}
	}
	UnlockDB();
	return MaxLearningID;
}

bool	__G_UpdateLearning(QSqlDatabase &DB 
							,int LearningID
							,int MachineID
							,int MasterCode
							,int SampleType
							,int Priority
							,int Version
							,int XSize ,int YSize
							,int GlobalPosX ,int GlobalPosY
							,int LayerCount
							,const QByteArray &MasterImage
							,const QByteArray &TargetImage
							,const QByteArray &PointData
							,const QByteArray &Alignment)
{
	QString	Str =QString("UPDATE LEARNING ")
				+QString("SET MACHINEID=")		+QString::number(MachineID)
				+QString(",MASTERCODE=")		+QString::number(MasterCode)
				+QString(",SAMPLETYPE=")		+QString::number(SampleType)
				+QString(",PRIORITY=")			+QString::number(Priority)
				+QString(",VERSION=")			+QString::number(Version)
				+QString(",XSIZE=")				+QString::number(XSize)
				+QString(",YSIZE=")				+QString::number(YSize)
				+QString(",LAYER=")				+QString::number(LayerCount)
				+QString(",MASTERIMAGE=:MASTERIMAGE")
				+QString(",TARGETIMAGE=:TARGETIMAGE")
				+QString(",POINTDATA=:POINTDATA")
				+QString(",ALIGNMENT=:ALIGNMENT")
				+QString(" WHERE LEARNINGID=")	+QString::number(LearningID);
	bool	ret1;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare(Str);

		queryUpdate.bindValue(0	, MasterImage);
		queryUpdate.bindValue(1	, TargetImage);
		queryUpdate.bindValue(2	, PointData);
		queryUpdate.bindValue(3	, Alignment);

		ret1=queryUpdate.exec();
	}

	UnlockDB();
	return ret1;
}

int		__G_InsertLearningParam(QSqlDatabase &DB 
								,int LearningID
								,int LibType
								,int LibID
								,const QByteArray &AlgoItems)
{
	int	MaxParamID=0;
	QString	S=QString("SELECT max(PARAMID) FROM LEARNINGPARAM;");
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			MaxParamID=query.value(0).toInt();
		}
		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO LEARNINGPARAM(PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA) "
			"VALUES(:LEARNINGID,:PARAMID,:LIBTYPE,:LIBID,:PARAMDATA);");
		queryInsrt.bindValue(0	, MaxParamID+1);
		queryInsrt.bindValue(1	, LearningID);
		queryInsrt.bindValue(2	, LibType);
		queryInsrt.bindValue(3	, LibID);
		queryInsrt.bindValue(4	, AlgoItems);

		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;
}

DEFFUNCEX	bool	__G_DeleteLearning(QSqlDatabase &DB 
								,int LearningID)
{
	LockDB();
	bool	ret1;
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("delete from LEARNING "
							" WHERE LEARNINGID=:LEARNINGID;");

		queryDelete.bindValue(0, LearningID);
		ret1=queryDelete.exec();
	}
	bool	ret2;
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("delete from LEARNINGPARAM "
							" WHERE LEARNINGID=:LEARNINGID;");

		queryDelete.bindValue(0, LearningID);
		ret2=queryDelete.exec();
	}
	UnlockDB();
	if(ret1==true && ret2==true){
		return true;
	}
	return false;
}
DEFFUNCEX	bool	__G_InsertLearningInDB(QSqlDatabase &DB ,LearningInDB &src)
{
	LockDB();
	int	LearningID=-1;
	if(src.LearningID>0){
		QString	Str =QString("SELECT MACHINEID FROM LEARNING where LEARNINGID=")
					+QString::number(src.LearningID);

		QSqlQuery querySelect(Str ,DB);
		if(querySelect.next()==false){
			LearningID=src.LearningID;
		}
	}
	int	MaxLearningID=0;
	QString	S=QString("SELECT max(LEARNINGID) FROM LEARNING");
	bool	Ret=true;
	{
		if(LearningID==-1){
			QSqlQuery query(S ,DB);
			if(query.next()==true){
				MaxLearningID=query.value(0).toInt();
			}

			LearningID=MaxLearningID+1;
		}
		src.LearningID=LearningID;
		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO LEARNING(LEARNINGID,MACHINEID,MASTERCODE,UPDATETIME,SAMPLETYPE,PRIORITY,VERSION,XSIZE,YSIZE,LAYER,MASTERIMAGE,TARGETIMAGE,POINTDATA,ALIGNMENT) "
			"VALUES(:LEARNINGID,:MACHINEID,:MASTERCODE,:UPDATETIME,:SAMPLETYPE,:PRIORITY,:VERSION,:XSIZE,:YSIZE,:LAYER,:MASTERIMAGE,:TARGETIMAGE,:POINTDATA,:ALIGNMENT);");
		queryInsrt.bindValue(0	, LearningID);
		queryInsrt.bindValue(1	, src.MachineID);
		queryInsrt.bindValue(2	, src.MasterCode);
		queryInsrt.bindValue(3	, src.UpdateTime);
		queryInsrt.bindValue(4	, src.SampleType);
		queryInsrt.bindValue(5	, src.Priority);
		queryInsrt.bindValue(6	, src.Version);
		queryInsrt.bindValue(7	, src.XSize);
		queryInsrt.bindValue(8	, src.YSize);
		queryInsrt.bindValue(9	, src.Layer);
		queryInsrt.bindValue(10	, src.MasterImage);
		queryInsrt.bindValue(11	, src.TargetImage);
		queryInsrt.bindValue(12	, src.PointData);
		queryInsrt.bindValue(13	, src.Alignment);

		if(queryInsrt.exec()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			int	MaxParamID=0;
			QString	SParam=QString("SELECT max(PARAMID) FROM LEARNINGPARAM;");

			QSqlQuery queryParam(SParam ,DB);
			if(queryParam.next()==true){
				MaxParamID=queryParam.value(0).toInt();
				MaxParamID++;
			}

			for(LearningParamInDB *a=src.NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
				QSqlQuery queryParamInsrt(DB);
				queryParamInsrt.prepare("INSERT INTO LEARNINGPARAM(PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA) "
					"VALUES(:PARAMID,:LEARNINGID,:LIBTYPE,:LIBID,:PARAMDATA);");
				queryParamInsrt.bindValue(0	, MaxParamID);
				queryParamInsrt.bindValue(1	, LearningID);
				queryParamInsrt.bindValue(2	, a->LibType);
				queryParamInsrt.bindValue(3	, a->LibID);
				queryParamInsrt.bindValue(4	, a->ParamData);

				if(queryParamInsrt.exec()==false){
					Ret=false;
					goto	FuncEnd;
				}
				a->ParamID=MaxParamID;
				MaxParamID++;
			}
		}
	FuncEnd:;
	}
	UnlockDB();
	return Ret;

}
DEFFUNCEX	bool	__G_UpdateLearningInDB(QSqlDatabase &DB ,LearningInDB &src)
{
	LockDB();
	{
		QString	Str =QString("SELECT MACHINEID where LEARNINGID=")
					+QString::number(src.LearningID);

		QSqlQuery querySelect(Str ,DB);
		if(querySelect.next()==false){
			UnlockDB();
			return false;
		}
	}

	QString	Str =QString("UPDATE LEARNING ")
				+QString("SET MACHINEID=")		+QString::number(src.MachineID)
				+QString(",MASTERCODE=")		+QString::number(src.MasterCode)
				+QString(",SAMPLETYPE=")		+QString::number(src.SampleType)
				+QString(",PRIORITY=")			+QString::number(src.Priority)
				+QString(",VERSION=")			+QString::number(src.Version)
				+QString(",XSIZE=")				+QString::number(src.XSize)
				+QString(",YSIZE=")				+QString::number(src.YSize)
				+QString(",LAYER=")				+QString::number(src.Layer)
				+QString(",MASTERIMAGE=:MASTERIMAGE")
				+QString(",TARGETIMAGE=:TARGETIMAGE")
				+QString(",POINTDATA=:POINTDATA")
				+QString(",ALIGNMENT=:ALIGNMENT")
				+QString(",UPDATETIME=:UPDATETIME")
				+QString(" WHERE LEARNINGID=")	+QString::number(src.LearningID);
	bool	Ret=true;

	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare(Str);

		queryUpdate.bindValue(0	, src.MasterImage);
		queryUpdate.bindValue(1	, src.TargetImage);
		queryUpdate.bindValue(2	, src.PointData);
		queryUpdate.bindValue(3	, src.Alignment);
		queryUpdate.bindValue(4	, src.UpdateTime);

		Ret=queryUpdate.exec();
		if(Ret==true){
			for(LearningParamInDB *a=src.NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
				QString	StrP=QString("UPDATE LEARNINGPARAM ")
							+QString("SET LIBTYPE=")		+QString::number(a->LibType)
							+QString(",LIBID=")				+QString::number(a->LibID)
							+QString(",PARAMDATA=:PARAMDATA")
							+QString(" WHERE LEARNINGID=")	+QString::number(src.LearningID)
							+QString(" and PARAMID=")		+QString::number(a->ParamID);

				QSqlQuery queryParamUpdate(DB);
				queryParamUpdate.prepare(StrP);
				queryParamUpdate.bindValue(0	, a->ParamData);
				bool	ret2=queryParamUpdate.exec();
				if(ret2==false){
					int	MaxParamID=0;
					QString	SParam=QString("SELECT max(PARAMID) FROM LEARNINGPARAM;");

					QSqlQuery queryParam(SParam ,DB);
					if(queryParam.next()==true){
						MaxParamID=queryParam.value(0).toInt();
						MaxParamID++;
					}
					QSqlQuery queryParamInsrt(DB);
					queryParamInsrt.prepare("INSERT INTO LEARNINGPARAM(PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA) "
						"VALUES(:LEARNINGID,:PARAMID,:LIBTYPE,:LIBID,:PARAMDATA);");
					queryParamInsrt.bindValue(0	, src.LearningID);
					queryParamInsrt.bindValue(1	, MaxParamID);
					queryParamInsrt.bindValue(2	, a->LibType);
					queryParamInsrt.bindValue(3	, a->LibID);
					queryParamInsrt.bindValue(4	, a->ParamData);

					if(queryParamInsrt.exec()==false){
						Ret=false;
						goto	FuncEnd;
					}
					a->ParamID=MaxParamID;
				}
			}
			{
				QString	SParam	=QString("SELECT PARAMID FROM LEARNINGPARAM WHERE LEARNINGID=")
								+QString::number(src.LearningID);

				IntList	DeleteParamIDs;
				QSqlQuery queryParamSelect(SParam ,DB);
				while(queryParamSelect.next()==true){
					int	ParamID=queryParamSelect.value(0).toInt();
					LearningParamInDB *a;
					for(a=src.NPListPackSaveLoad<LearningParamInDB>::GetFirst();a!=NULL;a=a->GetNext()){
						if(a->ParamID==ParamID){
							break;
						}
					}
					if(a==NULL){
						DeleteParamIDs.Add(ParamID);
					}
				}
				for(IntClass *c=DeleteParamIDs.GetFirst();c!=NULL;c=c->GetNext()){
					QSqlQuery queryDelete(DB);
					queryDelete.prepare("delete from LEARNINGPARAM "
										" WHERE LEARNINGID=:LEARNINGID and LEARNINGPARAM=:LEARNINGPARAM;");

					queryDelete.bindValue(0, src.LearningID);
					queryDelete.bindValue(1, c->GetValue());
					int	ret4=queryDelete.exec();
					if(ret4==false){
						Ret=false;
						goto	FuncEnd;
					}
				}
			}
		}
	FuncEnd:;
	}

	UnlockDB();
	return Ret;
}
DEFFUNCEX	bool	__G_LoadLearningInDB(QSqlDatabase &DB ,int LearningID,LearningInDB &src)
{
	bool	Ret=false;
	LockDB();
	{
		QString	Str =QString("SELECT MACHINEID,MASTERCODE,UPDATETIME,SAMPLETYPE,PRIORITY,VERSION,XSIZE,YSIZE,LAYER,MASTERIMAGE,TARGETIMAGE,POINTDATA,ALIGNMENT FROM LEARNING where LEARNINGID=")
					+QString::number(LearningID);

		QSqlQuery querySelect(Str ,DB);
		if(querySelect.next()==true){
			src.MachineID	=querySelect.value(0).toInt();
			src.MasterCode	=querySelect.value(1).toInt();
			src.UpdateTime	=querySelect.value(2).toDateTime();
			src.SampleType	=querySelect.value(3).toInt();
			src.Priority	=querySelect.value(4).toInt();
			src.Version		=querySelect.value(5).toInt();
			src.XSize		=querySelect.value(6).toInt();
			src.YSize		=querySelect.value(7).toInt();
			src.Layer		=querySelect.value(8).toInt();
			src.MasterImage	=querySelect.value(9).toByteArray();
			src.TargetImage	=querySelect.value(10).toByteArray();
			src.PointData	=querySelect.value(11).toByteArray();
			src.Alignment	=querySelect.value(12).toByteArray();

			QString	StrP=QString("SELECT PARAMID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM where LEARNINGID=")
						+QString::number(LearningID);
			src.RemoveAll();
			QSqlQuery queryParamSelect(StrP ,DB);
			while(queryParamSelect.next()==true){
				LearningParamInDB	*d=new LearningParamInDB();
				d->ParamID	=queryParamSelect.value(0).toInt();
				d->LibType	=queryParamSelect.value(1).toInt();
				d->LibID	=queryParamSelect.value(2).toInt();
				d->ParamData=queryParamSelect.value(3).toByteArray();
				src.AppendList(d);
			}
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}

DEFFUNCEX	bool	__S_GetNGTypeEnum(QSqlDatabase &DB 
									  ,int LibType ,int LibID ,IntList &NGTypeList)
{
//	return true;

	NGTypeList.RemoveAll();
	QString	S	=QString("SELECT NGTYPEID FROM ANYDATAINLIB WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and LIBID=")
				+QString::number(LibID);
	LockDB();
	{
		QSqlQuery *query=new QSqlQuery(S ,DB);
		while(query->next()==true){
			int	NGTypeID=query->value(0).toInt();
			NGTypeList.Add(NGTypeID);
		}
		delete	query;
	}
	UnlockDB();
	return true;
}
DEFFUNCEX	bool	__S_GetNGTypData(QSqlDatabase &DB
									,int LibType ,int LibID ,int NGTypeID
									,LibNGTypeItem *Item
									,QByteArray	&SpecifiedData)
{
	QString	S	=QString("SELECT NGTYPEID,TYPEUNIQUEID,NGCOLOR,DATANAME,MARKSHAPE,NEXTWAITINGTIME,PRIORITY,SPECIFIEDDATA FROM ANYDATAINLIB WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and LIBID=")
				+QString::number(LibID)
				+QString(" and NGTYPEID=")
				+QString::number(NGTypeID);
	bool	Ret=false;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			Item->TypeCode			=query.value(query.record().indexOf("NGTYPEID")).toInt();
			Item->TypeUniqueCode	=query.value(query.record().indexOf("TYPEUNIQUEID")).toInt();
						
			QByteArray	ColorBlob	=query.value(query.record().indexOf("NGCOLOR")).toByteArray();
			QBuffer	ColorBuff(&ColorBlob);
			ColorBuff.open(QIODevice::ReadWrite);
			::Load(&ColorBuff,Item->NGColor);

			Item->NGName			=query.value(query.record().indexOf("DATANAME")).toString();
			Item->NGShape			=(LibNGTypeItem::NGShapeType)query.value(query.record().indexOf("MARKSHAPE")).toInt();
			Item->NextJumpMilisec	=query.value(query.record().indexOf("NEXTWAITINGTIME")).toInt();
			Item->Priority			=query.value(query.record().indexOf("PRIORITY")).toInt();
			Item->Blink				=(bool)query.value(query.record().indexOf("BLINK")).toInt();
			
			SpecifiedData				=query.value(query.record().indexOf("SPECIFIEDDATA")).toByteArray();
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	bool	__S_SaveNewNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID 
							,LibNGTypeItem *Item
							,QByteArray	&SpecifiedData)
{
	QString	S	=QString("SELECT max(NGTYPEID) FROM ANYDATAINLIB WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and LIBID=")
				+QString::number(LibID);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		int	NGTypeID=1;
		if(query.next()==true){
			NGTypeID=query.value(0).toInt();
			NGTypeID++;
		}

		QString	Su	=QString("SELECT max(TYPEUNIQUEID) FROM ANYDATAINLIB");
		QSqlQuery query2(Su ,DB);
		int	TypeUniqueID=1;
		if(query2.next()==true){
			TypeUniqueID=query2.value(0).toInt();
			TypeUniqueID++;
		}

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO ANYDATAINLIB(LIBTYPE,LIBID,NGTYPEID,TYPEUNIQUEID,DATANAME,LASTUPDATED,DATAVERSION,NGCOLOR,MARKSHAPE,NEXTWAITINGTIME,PRIORITY,BLINK,SPECIFIEDDATA) "
			"VALUES(:LIBTYPE,:LIBID,:NGTYPEID,:TYPEUNIQUEID,:DATANAME,:LASTUPDATED,:DATAVERSION,:NGCOLOR,:MARKSHAPE,:NEXTWAITINGTIME,:PRIORITY,:BLINK,:SPECIFIEDDATA);");
		queryInsrt.bindValue(0	, LibType);
		queryInsrt.bindValue(1	, LibID);
		queryInsrt.bindValue(2	, NGTypeID);
		queryInsrt.bindValue(3	, TypeUniqueID);
		queryInsrt.bindValue(4	, Item->NGName);
		queryInsrt.bindValue(5	, XDateTime::currentDateTime().GetQDateTime());
		queryInsrt.bindValue(6	, Item->GetVersion());

		QBuffer	ColorBuff;
		ColorBuff.open(QIODevice::ReadWrite);
		::Save(&ColorBuff,Item->NGColor);
		QByteArray	ColorBlob=ColorBuff.data();

		queryInsrt.bindValue(7	, ColorBlob);
		queryInsrt.bindValue(8	, (int)Item->NGShape);
		queryInsrt.bindValue(9	, Item->NextJumpMilisec);
		queryInsrt.bindValue(10	, Item->Priority);
		queryInsrt.bindValue(11	, (int)Item->Blink);
		queryInsrt.bindValue(12	, SpecifiedData);

		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	bool	__S_UpdateNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID
								,LibNGTypeItem *Item
								,QByteArray	&SpecifiedData)
{
	QString	S=QString(	"UPDATE ANYDATAINLIB "
						"SET DATANAME=:DATANAME "
						",LASTUPDATED=:LASTUPDATED "
						",DATAVERSION=:DATAVERSION "
						",NGCOLOR=:NGCOLOR "
						",MARKSHAPE=:MARKSHAPE "
						",NEXTWAITINGTIME=:NEXTWAITINGTIME "
						",PRIORITY=:PRIORITY "
						",BLINK=:BLINK "
						",SPECIFIEDDATA=:SPECIFIEDDATA "
						" WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and LIBID=")
				+QString::number(LibID)
				+QString(" and NGTYPEID=")
				+QString::number(NGTypeID);
	bool	ret;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare(S);

		queryUpdate.bindValue(0	, Item->NGName);
		queryUpdate.bindValue(1	, XDateTime::currentDateTime().GetQDateTime());
		queryUpdate.bindValue(2	, Item->GetVersion());

		QBuffer	ColorBuff;
		ColorBuff.open(QIODevice::ReadWrite);
		::Save(&ColorBuff,Item->NGColor);
		QByteArray	ColorBlob=ColorBuff.data();

		queryUpdate.bindValue(3	, ColorBlob);
		queryUpdate.bindValue(4	, (int)Item->NGShape);
		queryUpdate.bindValue(5	, Item->NextJumpMilisec);
		queryUpdate.bindValue(6	, Item->Priority);
		queryUpdate.bindValue(7	, (int)Item->Blink);
		queryUpdate.bindValue(8	, SpecifiedData);

		ret=queryUpdate.exec();
	}
	UnlockDB();
	return ret;
}
DEFFUNCEX	bool	__S_DeleteNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID)
{
	QString	S=QString(	"delete from ANYDATAINLIB "
						" WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and LIBID=")
				+QString::number(LibID)
				+QString(" and NGTYPEID=")
				+QString::number(NGTypeID);
	bool	ret;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare(S);
	
		ret=queryDelete.exec();
	}
	UnlockDB();
	return ret;
}

DEFFUNCEX	bool	__G_GetInspectionLot(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode
								,XDateTime &LastUpdated
								,QString &IDName
								,QString &LotName
								,QString &Remark)
{
	QString	S=QString("SELECT * FROM INSPECTIONLOT where LOTAUTOCOUNT=")+QString::number(LotAutoCount)
				+QString(" and MASTERCODE=")+QString::number(MasterCode);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			LastUpdated	=query.value(query.record().indexOf("LASTUPDATED")).toDateTime();
			IDName		=query.value(query.record().indexOf("IDNAME"	)).toString();
			LotName		=query.value(query.record().indexOf("LOTNAME"	)).toString();
			Remark		=query.value(query.record().indexOf("REMARK"	)).toString();
		}
FuncEnd:;
	}
	UnlockDB();

	return Ret;
}

DEFFUNCEX	bool	__G_DeleteInspectionLot(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode)
{
	QString	S=QString("DELETE FROM INSPECTIONLOT where LOTAUTOCOUNT=")+QString::number(LotAutoCount)
				+QString(" and MASTERCODE=")+QString::number(MasterCode);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare(S);
		if(queryDelete.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();

	return Ret;
}
DEFFUNCEX	int		__G_EnumCommonDataInLibType		(QSqlDatabase &DB ,int LibType ,CommonDataInLibTypeListContainer &RetContainer)
{
	QString	S=QString("SELECT LIBTYPE,COMMONID,DATANAME FROM COMMONDATAINLIBTYPE order by COMMONID where LIBTYPE=")
				+QString::number(LibType);
	RetContainer.RemoveAll();
	int	n=0;
	LockDB();
	{
		QSqlQuery query(S ,DB);
		while(query.next()==true){
			CommonDataInLibTypeList	*a=new CommonDataInLibTypeList();
			a->CommonID	=query.value(query.record().indexOf("COMMONID")).toInt();
			a->Name		=query.value(query.record().indexOf("DATANAME")).toString();
			RetContainer.AppendList(a);
			n++;
		}
	}
	UnlockDB();
	return n;
}
DEFFUNCEX	bool	__G_SaveNewCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data)
{
	bool	Ret=true;
	LockDB();
	{
		int	CommonID=Data.CommonID;
		if(CommonID<0){
			QString	S	=QString("SELECT max(COMMONID) FROM COMMONDATAINLIBTYPE where LIBTYPE=")
						+QString::number(LibType);
			QSqlQuery query(S ,DB);
			CommonID=1;
			if(query.next()==true){
				CommonID=query.value(0).toInt();
				CommonID++;
			}
			Data.CommonID		=CommonID;
		}
		Data.LastUpdated	=QDateTime::currentDateTime();

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO COMMONDATAINLIBTYPE(LIBTYPE,COMMONID,DATANAME,LASTUPDATED,DATAVERSION,SPECIFIEDDATA) "
			"VALUES(:LIBTYPE,:COMMONID,:DATANAME,:LASTUPDATED,:DATAVERSION,:SPECIFIEDDATA);");
		queryInsrt.bindValue(0	, LibType);
		queryInsrt.bindValue(1	, CommonID);
		queryInsrt.bindValue(2	, Data.Name);
		queryInsrt.bindValue(3	, Data.LastUpdated);
		queryInsrt.bindValue(4	, Data.Version);
		queryInsrt.bindValue(5	, Data.Data);

		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	bool	__G_UpdateCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data)
{
	QString	S=QString(	"UPDATE COMMONDATAINLIBTYPE "
						"SET DATANAME=:DATANAME "
						",LASTUPDATED=:LASTUPDATED "
						",DATAVERSION=:DATAVERSION "
						",SPECIFIEDDATA=:SPECIFIEDDATA "
						" WHERE LIBTYPE=")
				+QString::number(LibType)
				+QString(" and COMMONID=")
				+QString::number(Data.CommonID);
	bool	ret;
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare(S);

		queryUpdate.bindValue(0	, Data.Name);
		queryUpdate.bindValue(1	, QDateTime::currentDateTime());
		queryUpdate.bindValue(2	, Data.Version);
		queryUpdate.bindValue(3	, Data.Data);

		ret=queryUpdate.exec();
	}
	UnlockDB();
	return ret;
}
DEFFUNCEX	bool	__G_LoadCommonDataInLibType		(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data)
{
	QString	S=QString("SELECT * FROM COMMONDATAINLIBTYPE where LIBTYPE=")+QString::number(LibType)
			+ QString(" and COMMONID=")+QString::number(Data.CommonID);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery query(S,DB);
		if(query.next ()==false){
			Ret=false;
			goto	FuncEnd;
		}
		{
			Data.LastUpdated	=query.value(query.record().indexOf("LASTUPDATED")).toDateTime();
			Data.Name			=query.value(query.record().indexOf("DATANAME"	)).toString();
			Data.Version		=query.value(query.record().indexOf("DATAVERSION"	)).toInt();
			Data.Data			=query.value(query.record().indexOf("SPECIFIEDDATA"	)).toByteArray();
		}
	FuncEnd:;
	}
	UnlockDB();

	return Ret;
}
DEFFUNCEX	bool	__G_DeleteCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,int32 CommonID)
{
	QString	S=QString("DELETE FROM COMMONDATAINLIBTYPE where LIBTYPE=")+QString::number(LibType)
				+QString(" and COMMONID=")+QString::number(CommonID);
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare(S);
		if(queryDelete.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();

	return Ret;
}

DEFFUNCEX	QSqlQuery  *__S_LevelFindFirst(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT LEVELID,LEVELVALUE,PARENTID,LEVELNAME,REMARK FROM LEVELFOLDER where PARENTID=0 ORDER BY LEVELID;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
DEFFUNCEX	void	__S_LevelGetData(QSqlQuery *query 
									,int &LevelID 
									,int &LevelValue 
									,QString &LevelName 
									,int &ParentID
									,QString &Remark)
{
	LockDB();
	{
		LevelID		=query->value(query->record().indexOf("LEVELID")).toInt();
		LevelValue	=query->value(query->record().indexOf("LEVELVALUE")).toInt();
		ParentID	=query->value(query->record().indexOf("PARENTID")).toInt();
		LevelName	=query->value(query->record().indexOf("LEVELNAME")).toString();
		Remark		=query->value(query->record().indexOf("REMARK")).toString();
	}
	UnlockDB();
}
DEFFUNCEX	bool	__S_LevelFindData(QSqlDatabase &DB
										,int LevelID 
										,int &LevelValue 
										,QString &LevelName 
										,int &ParentID
										,QString &Remark)

{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=false;
	QString	S=QString("SELECT LEVELID,LEVELVALUE,PARENTID,LEVELNAME,REMARK FROM LEVELFOLDER where LEVELID=")
			 +QString::number(LevelID);
			  
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next()==true){
			LevelValue	=query.value(query.record().indexOf("LEVELVALUE")).toInt();
			ParentID	=query.value(query.record().indexOf("PARENTID")).toInt();
			LevelName	=query.value(query.record().indexOf("LEVELNAME")).toString();
			Remark		=query.value(query.record().indexOf("REMARK")).toString();
			Ret=true;
		}
	}
	UnlockDB();
	return Ret;
}
DEFFUNCEX	QSqlQuery  *__S_LevelFindFirstByParentID(QSqlDatabase &DB ,int ParentID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT LEVELID,LEVELVALUE,PARENTID,LEVELNAME FROM LEVELFOLDER where PARENTID=")
			 +QString::number(ParentID)
			 +QString(" order by LEVELVALUE;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
DEFFUNCEX	int		__S_LevelCreatenew(QSqlDatabase &DB)
{
	if(DB.isValid()==false){
		return -1;
	}
	int	LevelID=-1;
	LockDB();
	{

		QSqlQuery query("SELECT MAX(LEVELID) from LEVELFOLDER" ,DB);
		if(query.next ()==true){
			LevelID=query.value(0).toInt();
		}
		LevelID++;

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO LEVELFOLDER(LEVELID) "
			"VALUES(:LEVELID);");
		queryInsrt.bindValue(0	, LevelID);
		if(queryInsrt.exec()==false){
			LevelID=-1;
		}
	}
	UnlockDB();

	return LevelID;
}
DEFFUNCEX	void	__S_LevelUpdate(QSqlDatabase &DB 
									,int LevelID
									,int LevelValue 
									, const QString &LevelName
									, int ParentID
									, const QString &Remark)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE LEVELFOLDER "
							"SET LEVELVALUE=:LEVELVALUE"
							", PARENTID=:PARENTID "
							" ,LEVELNAME=:LEVELNAME "
							" ,REMARK=:REMARK "
							 "WHERE LEVELID=:IN_LEVELID;");

		queryUpdate.bindValue(0, LevelValue);
		queryUpdate.bindValue(1, ParentID);
		queryUpdate.bindValue(2, LevelName);
		queryUpdate.bindValue(3, Remark);
		queryUpdate.bindValue(4, LevelID);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	UnlockDB();
}
DEFFUNCEX	bool	__S_RemoveLevel(QSqlDatabase &DB ,int LevelID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("DELETE FROM LEVELFOLDER WHERE LEVELID=:IN_LEVELID;");
		queryDelete.bindValue(0	, LevelID);
		if(queryDelete.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return true;

}

DEFFUNCEX	int		__S_EnumLevelID(QSqlDatabase &DB ,int parentID ,IntList &LevelIDs)
{
	if(DB.isValid()==false){
		return 0;
	}
	LevelIDs.RemoveAll();
	int	N=0;
	QString	S=QString("SELECT LEVELID,LEVELVALUE,LEVELNAME FROM LEVELFOLDER where PARENTID=")+QString::number(parentID)
		+QString(" order by LEVELVALUE;");
	LockDB();
	{
		QSqlQuery query(S ,DB);
		if(query.next ()==true){
			do{
				int	LevelID	=query.value(query.record().indexOf("LEVELID")).toInt();
				LevelIDs.Add(LevelID);
				N++;
			}while(query.next ()==true);
		}
	}
	UnlockDB();

	return N;
}

DEFFUNCEX	void	__S_ThresholdStockerGetData(QSqlQuery *query
										,int &LibType,int &FolderID,int &LibID,int &ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark
										,QByteArray &ThresholdData)
{
	LockDB();
	{
		ThresholdID	=query->value(query->record().indexOf("THRESHOLDID")).toInt();
		LibType		=query->value(query->record().indexOf("LIBTYPE")).toInt();
		FolderID	=query->value(query->record().indexOf("LIBFOLDERID")).toInt();
		LibID		=query->value(query->record().indexOf("LIBID")).toInt();
		ThresholdName	=query->value(query->record().indexOf("THRESHOLDNAME")).toString();
		ThresholdRemark	=query->value(query->record().indexOf("THRESHOLDREMARK")).toString();
		ThresholdData	=query->value(query->record().indexOf("THRESHOLDDATA")).toByteArray();
	}
	UnlockDB();
}
DEFFUNCEX	QSqlQuery *__S_ThresholdStockerFindFirst(QSqlDatabase &DB ,int LibType,int FolderID)
{
	if(DB.isValid()==false){
		return NULL;
	}
	QString	S=QString("SELECT THRESHOLDID,LIBTYPE,LIBFOLDERID,LIBID ,THRESHOLDNAME ,THRESHOLDREMARK ,THRESHOLDDATA FROM THRESHOLDSTOCKER where LIBTYPE=")
			 +QString::number(LibType)
			 +QString(" and LIBFOLDERID==")+QString::number(FolderID)
			 +QString(" order by THRESHOLDID;");
	QSqlQuery *query;
	LockDB();
	{
		query=new QSqlQuery(S ,DB);
	}
	UnlockDB();
	return query;
}
DEFFUNCEX	int		__S_ThresholdStockerCreatenew(QSqlDatabase &DB,int LibType)
{
	bool	Ret=true;
	LockDB();
	{
		QString	S	=QString("SELECT max(THRESHOLDID) FROM THRESHOLDSTOCKER where LIBTYPE=")
					+QString::number(LibType);
		QSqlQuery query(S ,DB);
		int	ThresholdID=1;
		if(query.next()==true){
			ThresholdID=query.value(0).toInt();
			ThresholdID++;
		}

		QSqlQuery queryInsrt(DB);
		queryInsrt.prepare("INSERT INTO THRESHOLDSTOCKER(THRESHOLDID,LIBTYPE) "
			"VALUES(:THRESHOLDID,:LIBTYPE);");
		queryInsrt.bindValue(0	, LibType);
		queryInsrt.bindValue(1	, ThresholdID);

		if(queryInsrt.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return Ret;
}

DEFFUNCEX	void	__S_ThresholdStockerUpdate(QSqlDatabase &DB ,int LibType,int FolderID,int LibID,int ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark,QByteArray &ThresholdData)
{
	if(DB.isValid()==false){
		return;
	}
	LockDB();
	{
		QSqlQuery queryUpdate(DB);
		queryUpdate.prepare("UPDATE THRESHOLDSTOCKER "
							"SET THRESHOLDID=:THRESHOLDID"
							", LIBTYPE=:LIBTYPE "
							" ,LIBID=:LIBID "
							" ,LIBFOLDERID=:LIBFOLDERID "
							" ,THRESHOLDNAME=:THRESHOLDNAME "
							" ,THRESHOLDREMARK=:THRESHOLDREMARK "
							" ,UPDATETIME=:UPDATETIME "
							" ,THRESHOLDDATA=:THRESHOLDDATA "
							 "WHERE THRESHOLDID=:IN_THRESHOLDID and LIBTYPE=:IN_LIBTYPE;");

		queryUpdate.bindValue(0, ThresholdID);
		queryUpdate.bindValue(1, LibType);
		queryUpdate.bindValue(2, LibID);
		queryUpdate.bindValue(3, FolderID);
		queryUpdate.bindValue(4, ThresholdName);
		queryUpdate.bindValue(5, ThresholdRemark);
		XDateTime	UpdateTime	=XDateTime::currentDateTime();
		queryUpdate.bindValue(6	, UpdateTime.GetQDateTime());
		queryUpdate.bindValue(7, ThresholdData);
		queryUpdate.bindValue(8, ThresholdID);
		queryUpdate.bindValue(9, LibType);
		queryUpdate.exec();
		QString	M=queryUpdate.executedQuery();
	}
	UnlockDB();
}
DEFFUNCEX	bool	__S_DeleteThresholdStocker(QSqlDatabase &DB ,int LibType ,int32 ThresholdID)
{
	if(DB.isValid()==false){
		return false;
	}
	bool	Ret=true;
	LockDB();
	{
		QSqlQuery queryDelete(DB);
		queryDelete.prepare("DELETE FROM THRESHOLDSTOCKER WHERE THRESHOLDDATA=:THRESHOLDDATA and LIBTYPE=:IN_LIBTYPE ;");
		queryDelete.bindValue(0	, ThresholdID);
		queryDelete.bindValue(0	, LibType);
		if(queryDelete.exec()==false){
			Ret=false;
		}
	}
	UnlockDB();
	return true;
}