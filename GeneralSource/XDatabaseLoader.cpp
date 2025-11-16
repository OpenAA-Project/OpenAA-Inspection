/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDatabaseLoader.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XDatabaseLoader.h"
#include <QSqlDatabase>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"

DatabaseLoader::DatabaseLoader(LayersBase *base)
	:ServiceForLayers(base)
{
	G_LockDB							=NULL;
	G_UnlockDB							=NULL;
	G_SQLSaveNewMasterData				=NULL;
	G_SQLUpdateMasterData				=NULL;
	G_SQLLoadMasterData					=NULL;
	G_SQLLoadMasterData2				=NULL;
	G_SQLGetMasterInfo					=NULL;
	G_SQLCheckMasterName				=NULL;
	G_SQLLoadMasterTopview				=NULL;
	G_SQLLoadMasterSetting				=NULL;

	G_SQLSavePage						=NULL;
	G_SQLLoadPage						=NULL;
	G_SQLLoadWorker						=NULL;
				
	G_SQLSavePageNoImage				=NULL;
	G_SQLLoadPageNoImage				=NULL;
	G_SQLAddMasterFieldData				=NULL;
	G_SQLAddRelationFieldData			=NULL;
	G_SQLLoadMasterFieldData			=NULL;
	G_SQLLoadRelationFieldData			=NULL;

	G_SQLSaveOutlineOfset				=NULL;
	G_SQLLoadOutlineOfset				=NULL;

	G_CheckAndCreateLibTypeInDatabase	=NULL;
	G_EnumLibrary						=NULL;
	G_EnumLibraryByType					=NULL;
	G_EnumLibraryByTypeInt				=NULL;
	G_EnumAllLibraryByType				=NULL;
	G_EnumAllLibraryByLibFolder			=NULL;
	G_GetLibraryNames					=NULL;
	G_GetLibraryName					=NULL;
	G_GetLibraryName2					=NULL;
	G_GetLibraryColor					=NULL;
	G_GetLibraryComment					=NULL;
	G_SaveNew							=NULL;
	G_SaveNewWithLibID					=NULL;
	G_Update							=NULL;
	G_Load								=NULL;
	G_Delete							=NULL;

	S_LibFolderFindFirst				=NULL;
	S_CreateQuery						=NULL;
	S_FindNext							=NULL;
	S_DeleteQuery						=NULL;
	S_LibFolderGetData					=NULL;
	S_LibFolderFindData					=NULL;
	S_LibFolderFindFirstByParentID		=NULL;
	S_LibFolderCreatenew				=NULL;
	S_LibFolderUpdate					=NULL;
	S_LibCopy							=NULL;
	S_GetFirstLibFolderByMasterCode		=NULL;
	S_GetLibraryLayers					=NULL;
	S_GetLibrarySourceID				=NULL;
	S_EnumLibraryInSourceID				=NULL;
	S_GetLibraryFolderID				=NULL;

	S_ColorFolderFindFirst				=NULL;
	S_ColorFolderGetData				=NULL;
	S_ColorFolderFindFirstByParentID	=NULL;
	S_ColorFolderCreatenew				=NULL;
	S_ColorFolderUpdate					=NULL;

	S_MasterCategoryFindFirst			=NULL;
	S_MasterCategoryGetData				=NULL;
	S_MasterCategoryFindFirstByParentID	=NULL;
	S_MasterCategoryCreatenew			=NULL;
	S_MasterCategoryUpdate				=NULL;

	S_GetLibraryTypeFirst				=NULL;
	S_GetLibraryTypeData				=NULL;
	S_DeleteLibraryType					=NULL;

	S_LightFindFirst					=NULL;
	S_GetFieldValue						=NULL;
	S_GetLight							=NULL;
	S_CreateNewLight					=NULL;
	S_LightFindLast						=NULL;
	S_UpdateLight						=NULL;
	S_DeleteLight						=NULL;
	S_CheckAndCreateBlobInMasterPageTable=NULL;
	S_OpenDatabase						=NULL;
	S_CloseDatabase						=NULL;
	S_IsValidDatabase					=NULL;

	G_XUpdateDatabase					=NULL;
	G_XUpdateDatabaseClose				=NULL;
	G_XGetTableAndFieldList				=NULL;
	G_XTableCheck						=NULL;
	G_XGetField							=NULL;
	G_XFieldCheckType					=NULL;
	G_XFieldCheckNull					=NULL;
	G_XUpdateDatabaseCreateDatabase		=NULL;
	G_XUpdateDatabaseCheck				=NULL;
	G_XUpdateDatabaseCheckGenerator		=NULL;
	G_XTableCheckIndex					=NULL;
	G_XGetIndex							=NULL;
	G_XTableCheckTrigger				=NULL;
	G_XTableCreateTable					=NULL;
	G_XUpdateDatabaseSaveField			=NULL;
	G_XUpdateDatabaseDropAllIndex		=NULL;
	G_XUpdateDatabaseChange				=NULL;
	G_XUpdateDatabaseChangeGenerator	=NULL;
	G_XIndexCreateIndex					=NULL;
	G_XTableChangeIndex					=NULL;
	G_XTriggerCreateTrigger				=NULL;
	G_XTableChangeTrigger				=NULL;
	G_LocalDatabaseBasicClassConnect	=NULL;
	G_LocalDatabaseBasicClassDisconnect	=NULL;

	G_EnumColorSample					=NULL;
	G_SaveNewColorSample				=NULL;
	G_UpdateColorSample					=NULL;
	G_LoadColorSample					=NULL;
	G_DeleteColorSample					=NULL;

	G_EnumMachine						=NULL;
	G_GetMachineInfo					=NULL;
	G_MachineIDExists					=NULL;

	G_CreateNewMasterRelation			=NULL;
	G_UpdateMasterRelation				=NULL;
	G_FindMasterRelation				=NULL;
	G_SetRelationOnMasterData			=NULL;
	G_SearchMasterCode					=NULL;
	G_GetRelationCode					=NULL;
	G_GetMasterRelation					=NULL;
	G_EnumMasterRelation				=NULL;
	G_UpdateLastLoadedTimeMasterRelation=NULL;

	G_GetMaxLearningIDAndInsertEmpty	=NULL;
	G_UpdateLearning					=NULL;
	G_InsertLearningParam				=NULL;
	G_DeleteLearning					=NULL;
	G_InsertLearningInDB				=NULL;
	G_UpdateLearningInDB				=NULL;
	G_LoadLearningInDB					=NULL;
		
	S_GetNGTypeEnum						=NULL;
	S_GetNGTypData						=NULL;
	S_SaveNewNGTypData					=NULL;
	S_UpdateNGTypData					=NULL;
	S_DeleteNGTypData					=NULL;

	G_GetInspectionLot					=NULL;
	G_DeleteInspectionLot				=NULL;

	G_EnumCommonDataInLibType			=NULL;
	G_SaveNewCommonDataInLibType		=NULL;
	G_UpdateCommonDataInLibType			=NULL;
	G_LoadCommonDataInLibType			=NULL;
	G_DeleteCommonDataInLibType			=NULL;

	S_LevelFindFirst					=NULL;
	S_LevelGetData						=NULL;
	S_LevelFindData						=NULL;
	S_LevelFindFirstByParentID			=NULL;
	S_LevelCreatenew					=NULL;
	S_LevelUpdate						=NULL;
	S_EnumLevelID						=NULL;
	S_RemoveLevel						=NULL;

	S_ThresholdStockerFindFirst			=NULL;
	S_ThresholdStockerGetData			=NULL;
	S_ThresholdStockerFindFirst			=NULL;
	S_ThresholdStockerCreatenew			=NULL;
	S_ThresholdStockerUpdate			=NULL;
	S_DeleteThresholdStocker			=NULL;
}

bool	DatabaseLoader::DatabaseInitialLoad(const QString &PathAndFileName)
{
	GetLayersBase()->TestLoadDLL(PathAndFileName);

	DllLib.setFileName(PathAndFileName);
	if(DllLib.load()==false)
		return(false);

	G_LockDB						=(void (*)(void))DllLib.resolve("__G_LockDB");
	G_UnlockDB						=(void (*)(void))DllLib.resolve("__G_UnlockDB");
	G_SQLSaveNewMasterData			=(int (*)(QSqlDatabase &DB ,LayersBase *Base))DllLib.resolve("__G_SQLSaveNewMasterData");
	G_SQLUpdateMasterData			=(bool (*)(QSqlDatabase &DB ,LayersBase *Base ,ParamGlobal *GParam
										  ,QBuffer &GeneralBuff ,QBuffer	&SettingBuff , QBuffer &LightBuff ,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
										  ,QBuffer &TopViewBuff))DllLib.resolve("__G_SQLUpdateMasterData");
	G_SQLLoadMasterData				=(bool (*)(QSqlDatabase &DB ,LayersBase *Base ,int masterCode
										,QBuffer &GeneralBuff ,QBuffer	&SettingBuff ,QBuffer &LightBuff,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
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
										,int32 &ThresholdLevelParentID))DllLib.resolve("__G_SQLLoadMasterData");
	G_SQLLoadMasterData2			=(bool (*)(QSqlDatabase &DB
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
										,int32 &ThresholdLevelParentID))DllLib.resolve("__G_SQLLoadMasterData2");

	G_SQLGetMasterInfo				=(bool (*)(QSqlDatabase &DB ,int masterCode
										,int32 &MachineID
										,XDateTime &RegTime
										,QString &MasterName ,QString &Remark
										,int32 &Version
										,XDateTime &LastEditTime
										,int32 &CategoryID
										,int16 &MasterType
										,int32 &LibFolderID
										,int32 &ThresholdLevelID
										,int32 &ThresholdLevelParentID))DllLib.resolve("__G_SQLGetMasterInfo");
	G_SQLCheckMasterName			=(bool	(*)(QSqlDatabase &DB
										,int32 MachineID
										,QString MasterName
										,IntList &RetMasterCodes))DllLib.resolve("__G_SQLCheckMasterName");
		
	G_SQLLoadMasterTopview			=(QImage *(*)(QSqlDatabase &DB ,int masterCode))DllLib.resolve("__G_SQLLoadMasterTopview");
	G_SQLLoadMasterSetting			=(bool (*)(QSqlDatabase &DB ,int masterCode,QBuffer &SettingBuff ))DllLib.resolve("__G_SQLLoadMasterSetting");

	G_SQLLoadWorker					=(bool (*)(QSqlDatabase &DB ,int workerID ,QString &RetName))DllLib.resolve("__G_SQLLoadWorker");

	G_SQLSavePage					=(bool (*)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff,QBuffer &ImageBuff))DllLib.resolve("__G_SQLSavePage");
	G_SQLLoadPage					=(bool (*)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff ,QBuffer &ImageBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion))DllLib.resolve("__G_SQLLoadPage");
					  
	G_SQLSavePageNoImage			=(bool (*)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff))DllLib.resolve("__G_SQLSavePageNoImage");
	G_SQLLoadPageNoImage			=(bool (*)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion))DllLib.resolve("__G_SQLLoadPageNoImage");
	G_SQLAddMasterFieldData			=(bool (*)(QSqlDatabase &DB ,int32 masterCode	,const QString &fieldName,const QVariant &data))DllLib.resolve("__G_SQLAddMasterFieldData");
	G_SQLAddRelationFieldData		=(bool (*)(QSqlDatabase &DB ,int32 RelationCode ,const QString &fieldName,const QVariant &data))DllLib.resolve("__G_SQLAddRelationFieldData");
	G_SQLLoadMasterFieldData		=(bool (*)(QSqlDatabase &DB ,int32 masterCode	,const QString &fieldName,QVariant &data))DllLib.resolve("__G_SQLLoadMasterFieldData");
	G_SQLLoadRelationFieldData		=(bool (*)(QSqlDatabase &DB ,int32 RelationCode ,const QString &fieldName,QVariant &data))DllLib.resolve("__G_SQLLoadRelationFieldData");

	G_SQLSaveOutlineOfset			=(bool (*)(QSqlDatabase &DB ,int32 MachineID ,OutlineOffsetInBlob	*OutlineOffsetWriter))DllLib.resolve("__G_SQLSaveOutlineOfset");
	G_SQLLoadOutlineOfset			=(bool (*)(QSqlDatabase &DB ,int32 MachineID ,OutlineOffsetInBlob	*OutlineOffsetWriter))DllLib.resolve("__G_SQLLoadOutlineOfset");

	G_CheckAndCreateLibTypeInDatabase=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base))DllLib.resolve("__G_CheckAndCreateLibTypeInDatabase");
	G_EnumLibrary					=(int (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList))DllLib.resolve("__G_EnumLibrary");
	G_EnumLibraryByType				=(int (*)(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList))DllLib.resolve("__G_EnumLibraryByType");
	G_EnumLibraryByTypeInt			=(int (*)(QSqlDatabase &DB ,int LibType,int LibFolderID ,int IDList[] ,int MaxDimCount))DllLib.resolve("__G_EnumLibraryByTypeInt");
	G_EnumAllLibraryByType			=(int (*)(QSqlDatabase &DB ,int LibType		,AlgorithmLibraryListContainer &LibIDList))DllLib.resolve("__G_EnumAllLibraryByType");
	G_EnumAllLibraryByLibFolder		=(int (*)(QSqlDatabase &DB ,int LibFolderID	,AlgorithmLibraryListContainer &LibIDList))DllLib.resolve("__G_EnumAllLibraryByLibFolder");
	G_GetLibraryNames				=(void (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryListContainer &LibIDList))DllLib.resolve("__G_GetLibraryNames");
	G_GetLibraryName				=(QString (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibID))DllLib.resolve("__G_GetLibraryName");
	G_GetLibraryName2				=(QString (*)(QSqlDatabase &DB , int LibType ,int LibID))DllLib.resolve("__G_GetLibraryName2");
	G_GetLibraryColor				=(QColor (*)(QSqlDatabase &DB , int LibType ,int LibID))DllLib.resolve("__G_GetLibraryColor");
	G_GetLibraryComment				=(QString (*)(QSqlDatabase &DB ,int LibType ,int LibID))DllLib.resolve("__G_GetLibraryComment");
	G_SaveNew						=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data))DllLib.resolve("__G_SaveNew");
	G_SaveNewWithLibID				=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data))DllLib.resolve("__G_SaveNewWithLibID");
	G_Update						=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data))DllLib.resolve("__G_Update");
	G_Load							=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data))DllLib.resolve("__G_Load");
	G_Delete						=(bool (*)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int32 LibID))DllLib.resolve("__G_Delete");

	S_LibFolderFindFirst			=(QSqlQuery *(*)(QSqlDatabase &DB))DllLib.resolve("__S_LibFolderFindFirst");
	S_CreateQuery					=(QSqlQuery *(*)(QSqlDatabase &DB,const QString &Str))DllLib.resolve("__S_CreateQuery");
	S_FindNext						=(bool (*)(QSqlQuery *query))DllLib.resolve("__S_FindNext");
	S_DeleteQuery					=(bool (*)(QSqlQuery *query))DllLib.resolve("__S_DeleteQuery");
	S_LibFolderGetData				=(void (*)(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder))DllLib.resolve("__S_LibFolderGetData");
	S_LibFolderFindData				=(bool (*)(QSqlDatabase &DB,int LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder))DllLib.resolve("__S_LibFolderFindData");
	S_LibFolderFindFirstByParentID	=(QSqlQuery *(*)(QSqlDatabase &DB ,int parentID))DllLib.resolve("__S_LibFolderFindFirstByParentID");
	S_LibFolderCreatenew			=(int (*)(QSqlDatabase &DB))DllLib.resolve("__S_LibFolderCreatenew");
	S_LibFolderUpdate				=(void (*)(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int LibFolderID ,int MasterCode))DllLib.resolve("__S_LibFolderUpdate");
	S_LibCopy						=(void (*)(QSqlDatabase &DB ,int sourceFolderID ,int destFolderID ,int LibType))DllLib.resolve("__S_LibCopy");
	S_GetFirstLibFolderByMasterCode	=(int (*)(QSqlDatabase &DB ,int MasterCode ,QString &FolderName))DllLib.resolve("__S_GetFirstLibFolderByMasterCode");

	S_ColorFolderFindFirst			=(QSqlQuery *(*)(QSqlDatabase &DB))DllLib.resolve("__S_ColorFolderFindFirst");
	S_ColorFolderGetData			=(void (*)(QSqlQuery *query ,int &ColorFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder))DllLib.resolve("__S_ColorFolderGetData");
	S_ColorFolderFindFirstByParentID=(QSqlQuery *(*)(QSqlDatabase &DB ,int parentID))DllLib.resolve("__S_ColorFolderFindFirstByParentID");
	S_ColorFolderCreatenew			=(int (*)(QSqlDatabase &DB))DllLib.resolve("__S_ColorFolderCreatenew");
	S_ColorFolderUpdate				=(void (*)(QSqlDatabase &DB ,int ParentID ,QString FolderName, int ColorFolderID))DllLib.resolve("__S_ColorFolderUpdate");
	S_GetLibraryLayers				=(bool (*)(QSqlDatabase &DB ,int LibType,int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers))DllLib.resolve("__S_GetLibraryLayers");
	S_GetLibrarySourceID			=(int (*)(QSqlDatabase &DB ,int LibType,int LibID))DllLib.resolve("__S_GetLibrarySourceID");
	S_EnumLibraryInSourceID			=(int (*)(QSqlDatabase &DB ,int LibType,int SourceLibID ,IntList &RetLibID))DllLib.resolve("__S_EnumLibraryInSourceID");
	S_GetLibraryFolderID			=(int (*)(QSqlDatabase &DB ,int LibType,int LibID))DllLib.resolve("__S_GetLibraryFolderID");

	S_MasterCategoryFindFirst		=(QSqlQuery *(*)(QSqlDatabase &DB))DllLib.resolve("__S_MasterCategoryFindFirst");
	S_MasterCategoryGetData			=(void (*)(QSqlQuery *query ,int &CategoryID ,QString &FolderName ,int &ParentID ,QString &Remark))DllLib.resolve("__S_MasterCategoryGetData");
	S_MasterCategoryFindFirstByParentID	=(QSqlQuery *(*)(QSqlDatabase &DB ,int parentID))DllLib.resolve("__S_MasterCategoryFindFirstByParentID");
	S_MasterCategoryCreatenew		=(int (*)(QSqlDatabase &DB))DllLib.resolve("__S_MasterCategoryCreatenew");
	S_MasterCategoryUpdate			=(void (*)(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int FolderID,const QString &Remark))DllLib.resolve("__S_MasterCategoryUpdate");

	S_GetLibraryTypeFirst			=(QSqlQuery *(*)(QSqlDatabase &DB))DllLib.resolve("__S_GetLibraryTypeFirst");
	S_GetLibraryTypeData			=(void (*)(QSqlQuery *query,int &LibType,QString &LibName))DllLib.resolve("__S_GetLibraryTypeData");
	S_DeleteLibraryType				=(void (*)(QSqlQuery *query))DllLib.resolve("__S_DeleteLibraryType");

	S_LightFindFirst				=(QSqlQuery *(*)(QSqlDatabase &DB ,int MachineCode))DllLib.resolve("__S_LightFindFirst");
	S_GetFieldValue					=(bool (*)(QSqlQuery *query,const char *FieldName,QVariant &v))DllLib.resolve("__S_GetFieldValue");
	S_GetLight						=(QSqlQuery *(*)(QSqlDatabase &DB ,int MachineCode,int LightID))DllLib.resolve("__S_GetLight");
	S_CreateNewLight				=(bool (*)(QSqlDatabase &DB ,int MachineID ,QString DLLIDName ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage))DllLib.resolve("__S_CreateNewLight");
	S_LightFindLast					=(QSqlQuery *(*)(QSqlDatabase &DB ,int MachineCode))DllLib.resolve("__S_LightFindLast");
	S_UpdateLight					=(bool (*)(QSqlDatabase &DB ,int MachineID,int LightID ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage))DllLib.resolve("__S_UpdateLight");
	S_DeleteLight					=(bool (*)(QSqlDatabase &DB ,int MachineID,int LightID))DllLib.resolve("__S_DeleteLight");

	S_CheckAndCreateBlobInMasterPageTable	=(bool (*)(const QSqlDatabase &db ,QString &BlobName))DllLib.resolve("__S_CheckAndCreateBlobInMasterPageTable");
	S_OpenDatabase					=(QSqlDatabase *(*)(QSqlDatabase *DB))DllLib.resolve("__S_OpenDatabase");
	S_CloseDatabase					=(QSqlDatabase *(*)(QSqlDatabase *DB))DllLib.resolve("__S_CloseDatabase");
	S_IsValidDatabase				=(bool (*)(QSqlDatabase *DB))DllLib.resolve("__S_IsValidDatabase");

	G_XUpdateDatabase				=(void (*)(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port
											  ,QString TransIP ,int TransPort))DllLib.resolve("__G_XUpdateDatabase");
	G_XUpdateDatabaseClose			=(void (*)(QSqlDatabase &DBase))DllLib.resolve("__G_XUpdateDatabaseClose");
	G_XGetTableAndFieldList			=(bool (*)(std::shared_ptr<DatabaseLoader> &DBLoader
										,QSqlDatabase &DBase
										,QString DBName
										,NPListPack<XTable> &TableList))DllLib.resolve("__G_XGetTableAndFieldList");
	G_XGetField						=(bool (*)(XTable *This ,QSqlQuery *QrField ,XField &Field))DllLib.resolve("__G_XGetField");
	G_XTableCheck					=(bool (*)(XTable *This ,QSqlQuery *QrField ,NPListPack<XField> &FieldList,QStringList &MismatchList ,ExcludedListPack *ExcludedList,QString &Name))DllLib.resolve("__G_XTableCheck");
	G_XFieldCheckType				=(bool (*)(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList
							,FieldType dType ,bool &Found,int Size 
							,QString Name))DllLib.resolve("__G_XFieldCheckType");
	G_XFieldCheckNull				=(bool (*)(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList ,QString Name,bool NotNull))DllLib.resolve("__G_XFieldCheckNull");
	G_XUpdateDatabaseCreateDatabase	=(bool (*)(QSqlDatabase &DBase ,QString DBName ,int DatabasePageSize,QStringList &MismatchList))DllLib.resolve("__G_XUpdateDatabaseCreateDatabase");
	G_XUpdateDatabaseCheck			=(bool (*)(QSqlDatabase &DBase ,QStringList &MismatchList
								,ExcludedListPack *ExcludedList
								,QString DBName
								,NPListPack<XGenerator> &GeneratorList
								,NPListPack<XTable> &TableList))DllLib.resolve("__G_XUpdateDatabaseCheck");
	G_XUpdateDatabaseCheckGenerator	=(bool (*)(QSqlDatabase &DBase ,QString DBName
													,NPListPack<XGenerator> &GeneratorList
													,QStringList &MismatchList))DllLib.resolve("__G_XUpdateDatabaseCheckGenerator");
	G_XTableCheckIndex				=(bool (*)(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList 
									   ,QString Name
									   ,XIndex &PrimaryKey
									   ,NPListPack<XIndex> &IndexList))DllLib.resolve("__G_XTableCheckIndex");
	G_XGetIndex						=(bool (*)(QSqlDatabase &db ,QSqlQuery *QrField
										,QString Name
										,NPListPack<XField> &FieldList
										,NPListPack<XIndex> &RetIndexList))DllLib.resolve("__G_XGetIndex");
	G_XTableCheckTrigger			=(bool (*)(QSqlQuery *QrTrig ,QStringList &MismatchList,QString Name,NPListPack<XTrigger> &TriggerList))DllLib.resolve("__G_XTableCheckTrigger");
	G_XTableCreateTable				=(bool (*)(QSqlQuery *QrExe ,QStringList &MismatchList ,QString Name ,bool &Found
										,NPListPack<XField> &FieldList
										,XIndex &PrimaryKey))DllLib.resolve("__G_XTableCreateTable");
	G_XUpdateDatabaseSaveField		=(void (*)(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f
									,QString TmpFieldName
									,QString &SaveFieldType
									,NPListPack<XPocket> &PocketList))DllLib.resolve("__G_XUpdateDatabaseSaveField");
	G_XUpdateDatabaseDropAllIndex	=(bool (*)(QSqlDatabase &DBase ,NPListPack<XIndexTmp> &DroppedIndex,QString &tblName))DllLib.resolve("__G_XUpdateDatabaseDropAllIndex");
	G_XUpdateDatabaseChange			=(bool (*)(QSqlDatabase &DBase ,QStringList &MismatchList ,ExcludedListPack *ExcludedList
											,NPListPack<XTable> &TableList
											,bool &IsOKTableRemove
											,bool &IsOKFieldRemove
											,QString &TmpFieldName
											,XUpdateDatabase *This))DllLib.resolve("__G_XUpdateDatabaseChange");
	G_XUpdateDatabaseChangeGenerator=(bool    (*)(QSqlDatabase &DBase ,QSqlQuery *QrExe ,QStringList &MismatchList
													,NPListPack<XGenerator> &GeneratorList))DllLib.resolve("__G_XUpdateDatabaseChangeGenerator");
	G_XIndexCreateIndex				=(bool (*)(QSqlQuery *QrExe,XTable *x
										,bool Unique ,bool Ascending
										,QString &Name
										,NPListPack<XFieldPointer> &KeyField))DllLib.resolve("__G_XIndexCreateIndex");
	G_XTableChangeIndex				=(bool (*)(QSqlDatabase &db ,QSqlQuery *QrExe 
										,QSqlQuery *QrField 
										,QStringList &MismatchList ,QString &Name
										,XIndex &PrimaryKey
										,bool &Found
										,NPListPack<XIndex> &IndexList
										,XTable *This))DllLib.resolve("__G_XTableChangeIndex");
	G_XTriggerCreateTrigger			=(bool (*)(QSqlQuery *QrExe ,XTable *x ,QString &Name
											,TriggerAction Action
											,int Position
											,char *Contents))DllLib.resolve("__G_XTriggerCreateTrigger");
	G_XTableChangeTrigger			=(bool (*)(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList 
										  ,QString &Name
										  ,NPListPack<XTrigger> &TriggerList
										  ,XTable *This))DllLib.resolve("__G_XTableChangeTrigger");
	G_LocalDatabaseBasicClassConnect=(bool (*)(QSqlDatabase &DBase))DllLib.resolve("__G_LocalDatabaseBasicClassConnect");
	G_LocalDatabaseBasicClassDisconnect=(bool (*)(QSqlDatabase &DBase))DllLib.resolve("__G_LocalDatabaseBasicClassDisconnect");

	G_EnumColorSample				=(int (*)(QSqlDatabase &DB ,int SelectedColorFolder,ColorSampleList EnumData[] ,int MaxNumb))DllLib.resolve("__G_EnumColorSample");
	G_SaveNewColorSample			=(bool (*)(QSqlDatabase &DB ,ColorSampleList &Data))DllLib.resolve("__G_SaveNewColorSample");
	G_UpdateColorSample				=(bool (*)(QSqlDatabase &DB ,ColorSampleList &Data))DllLib.resolve("__G_UpdateColorSample");
	G_LoadColorSample				=(bool (*)(QSqlDatabase &DB ,ColorSampleList &Data,QBuffer &DataBuff))DllLib.resolve("__G_LoadColorSample");
	G_DeleteColorSample				=(bool (*)(QSqlDatabase &DB ,ColorSampleList &Data))DllLib.resolve("__G_DeleteColorSample");

	G_EnumMachine					=(int (*)(QSqlDatabase &DB ,int MachineIDList[] ,int MaxList))DllLib.resolve("__G_EnumMachine");
	G_GetMachineInfo				=(bool (*)(QSqlDatabase &DB ,int MachineID 
										,QString &NetID
										,QString &Name
										,QString &Version
										,QString &Remark))DllLib.resolve("__G_GetMachineInfo");
	G_MachineIDExists				=(bool (*)(QSqlDatabase &DB ,int MachineID))DllLib.resolve("__G_MachineIDExists");

	G_CreateNewMasterRelation		=(bool (*)(QSqlDatabase &DB 
										,int &RetRelationCode
										,const QString &RelationNumber
										,const QString &RelationName
										,const QString &Remark
										,int RelationType
										,QByteArray &CommonData
										,int32 ThresholdLevelID))DllLib.resolve("__G_CreateNewMasterRelation");
	G_UpdateMasterRelation			=(bool (*)(QSqlDatabase &DB 
										,int RelationCode
										,const QString &RelationNumber
										,const QString &RelationName
										,const QString &Remark
										,int RelationType
										,QByteArray &CommonData
										,int32 ThresholdLevelID))DllLib.resolve("__G_UpdateMasterRelation");
	G_FindMasterRelation			=(bool	(*)(QSqlDatabase &DB 
										,const QString &RelationName
										,const QString &RelationNumber
										,const QString &Remark
										,IntList &RelationCodes))DllLib.resolve("__G_FindMasterRelation");
	G_SetRelationOnMasterData		=(bool (*)(QSqlDatabase &DB ,int MasterCode,int RelationCode ,int RelationID))DllLib.resolve("__G_SetRelationOnMasterData");
	G_SearchMasterCode				=(int (*)(QSqlDatabase &DB, int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount))DllLib.resolve("__G_SearchMasterCode");
	G_GetRelationCode				=(int (*)(QSqlDatabase &DB ,int MasterCode))DllLib.resolve("__G_GetRelationCode");
	G_GetMasterRelation				=(bool	(*)(QSqlDatabase &DB 
										,int RelationCode
										,QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID))DllLib.resolve("__G_GetMasterRelation");
	G_EnumMasterRelation			=(bool (*)(QSqlDatabase &DB 
											   ,IntList &RelationCodes))DllLib.resolve("__G_EnumMasterRelation");
	G_UpdateLastLoadedTimeMasterRelation	=(bool (*)(QSqlDatabase &DB 
												,int RelationCode))DllLib.resolve("__G_UpdateLastLoadedTimeMasterRelation");

	G_GetMaxLearningIDAndInsertEmpty=(int (*)(QSqlDatabase &DB))DllLib.resolve("__G_GetMaxLearningIDAndInsertEmpty");
	G_UpdateLearning				=(bool (*)(QSqlDatabase &DB 
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
										,const QByteArray &Alignment))DllLib.resolve("__G_UpdateLearning");
	G_InsertLearningParam			=(int (*)(QSqlDatabase &DB 
									,int LearningID
									,int LibType
									,int LibID
									,const QByteArray &AlgoItems))DllLib.resolve("__G_InsertLearningParam");
	G_DeleteLearning				=(bool (*)(QSqlDatabase &DB 
										,int LearningID))DllLib.resolve("__G_DeleteLearning");
	G_InsertLearningInDB			=(bool (*)(QSqlDatabase &DB ,LearningInDB &src))DllLib.resolve("__G_InsertLearningInDB");
	G_UpdateLearningInDB			=(bool (*)(QSqlDatabase &DB ,LearningInDB &src))DllLib.resolve("__G_UpdateLearningInDB");
	G_LoadLearningInDB				=(bool (*)(QSqlDatabase &DB ,int LearningID,LearningInDB &src))DllLib.resolve("__G_LoadLearningInDB");


	S_GetNGTypeEnum					=(bool	(*)(QSqlDatabase &DB ,int LibType ,int LibID ,IntList &NGTypeList))DllLib.resolve("__S_GetNGTypeEnum");
	S_GetNGTypData					=(bool	(*)(QSqlDatabase &DB
												,int LibType ,int LibID ,int NGTypeID
												,LibNGTypeItem *Item
												,QByteArray	&SpecifiedData))DllLib.resolve("__S_GetNGTypData");

	S_SaveNewNGTypData				=(bool	(*)(QSqlDatabase &DB
												,int LibType ,int LibID 
												,LibNGTypeItem *Item
												,QByteArray	&SpecifiedData))DllLib.resolve("__S_SaveNewNGTypData");
	S_UpdateNGTypData				=(bool	(*)(QSqlDatabase &DB
												,int LibType ,int LibID ,int NGTypeID
												,LibNGTypeItem *Item
												,QByteArray	&SpecifiedData))DllLib.resolve("__S_UpdateNGTypData");
	S_DeleteNGTypData				=(bool	(*)(QSqlDatabase &DB
												,int LibType ,int LibID ,int NGTypeID))DllLib.resolve("__S_DeleteNGTypData");
	G_GetInspectionLot				=(bool	(*)(QSqlDatabase &DB 
												,int LotAutoCount,int MasterCode
												,XDateTime &LastUpdated
												,QString &IDName
												,QString &LotName
												,QString &Remark))DllLib.resolve("__G_GetInspectionLot");

	G_DeleteInspectionLot			=(bool	(*)(QSqlDatabase &DB 
												,int LotAutoCount,int MasterCode))DllLib.resolve("__G_DeleteInspectionLot");

	G_EnumCommonDataInLibType		=(int	(*)(QSqlDatabase &DB ,int LibType 
												,CommonDataInLibTypeListContainer &RetContainer))DllLib.resolve("__G_EnumCommonDataInLibType");
	G_SaveNewCommonDataInLibType	=(bool	(*)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data))DllLib.resolve("__G_SaveNewCommonDataInLibType");
	G_UpdateCommonDataInLibType		=(bool	(*)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data))DllLib.resolve("__G_UpdateCommonDataInLibType");
	G_LoadCommonDataInLibType		=(bool	(*)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data))DllLib.resolve("__G_LoadCommonDataInLibType");
	G_DeleteCommonDataInLibType		=(bool	(*)(QSqlDatabase &DB ,int LibType ,int32 CommonID))DllLib.resolve("__G_DeleteCommonDataInLibType");

	S_LevelFindFirst			=(QSqlQuery *(*)(QSqlDatabase &DB))DllLib.resolve("__S_LevelFindFirst");
	S_LevelGetData				=(void (*)(QSqlQuery *query ,int &LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID ,QString &Remark)
									)DllLib.resolve("__S_LevelGetData");
	S_LevelFindData				=(bool (*)(QSqlDatabase &DB,int LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID ,QString &Remark)
									)DllLib.resolve("__S_LevelFindData");
	S_LevelFindFirstByParentID	=(QSqlQuery *(*)(QSqlDatabase &DB ,int ParentID)
									)DllLib.resolve("__S_LevelFindFirstByParentID");
	S_LevelCreatenew			=(int (*)(QSqlDatabase &DB))DllLib.resolve("__S_LevelCreatenew");
	S_LevelUpdate				=(void (*)(QSqlDatabase &DB ,int LevelID ,int LevelValue ,const QString &LevelName, int ParentID ,const QString &Remark)
									)DllLib.resolve("__S_LevelUpdate");
	S_EnumLevelID				=(int (*)(QSqlDatabase &DB ,int parentID ,IntList &LevelIDs)
									)DllLib.resolve("__S_EnumLevelID");
	S_RemoveLevel				=(bool (*)(QSqlDatabase &DB ,int LevelID))DllLib.resolve("__S_RemoveLevel");


	S_ThresholdStockerGetData	=(void (*)(QSqlQuery *query
										,int &LibType,int &FolderID,int &LibID,int &ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark
										,QByteArray &ThresholdData))DllLib.resolve("__S_ThresholdStockerGetData");
	S_ThresholdStockerFindFirst	=(QSqlQuery *(*)(QSqlDatabase &DB ,int LibType,int FolderID))DllLib.resolve("__S_ThresholdStockerFindFirst");
	S_ThresholdStockerCreatenew	=(int (*)(QSqlDatabase &DB,int LibType))DllLib.resolve("__S_ThresholdStockerCreatenew");
	S_ThresholdStockerUpdate	=(void (*)(QSqlDatabase &DB ,int LibType,int FolderID,int LibID,int ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark,QByteArray &ThresholdData))DllLib.resolve("__S_ThresholdStockerUpdate");
	S_DeleteThresholdStocker	=(bool (*)(QSqlDatabase &DB ,int LibType ,int32 ThresholdID))DllLib.resolve("__S_DeleteThresholdStocker");

	if(G_LockDB==NULL)					{	return false;	}
	if(G_UnlockDB==NULL)				{	return false;	}
	if(G_SQLSaveNewMasterData==NULL)	{	return false;	}
	if(G_SQLUpdateMasterData==NULL)		{	return false;	}
	if(G_SQLLoadMasterData==NULL)		{	return false;	}
	if(G_SQLLoadMasterData2==NULL)		{	return false;	}
	if(G_SQLGetMasterInfo==NULL)		{	return false;	}
	if(G_SQLCheckMasterName==NULL)		{	return false;	}
	if(G_SQLLoadMasterTopview==NULL)	{	return false;	}
	if(G_SQLSavePage==NULL)				{	return false;	}
	if(G_SQLLoadPage==NULL)				{	return false;	}
	if(G_SQLLoadWorker==NULL)			{	return false;	}
				
	if(G_SQLSavePageNoImage	==NULL)		{	return false;	}
	if(G_SQLLoadPageNoImage	==NULL)		{	return false;	}
	if(G_SQLAddMasterFieldData==NULL)	{	return false;	}
	if(G_SQLAddRelationFieldData==NULL)	{	return false;	}
	if(G_SQLLoadMasterFieldData	==NULL)	{	return false;	}
	if(G_SQLLoadRelationFieldData==NULL){	return false;	}

	if(G_SQLSaveOutlineOfset==NULL)		{	return false;	}
	if(G_SQLLoadOutlineOfset==NULL)		{	return false;	}

	if(G_CheckAndCreateLibTypeInDatabase==NULL)	{	return false;	}
	if(G_EnumLibrary==NULL)				{	return false;	}
	if(G_EnumLibraryByType==NULL)		{	return false;	}
	if(G_EnumLibraryByTypeInt==NULL)	{	return false;	}
	if(G_EnumAllLibraryByType==NULL)	{	return false;	}
	if(G_EnumAllLibraryByLibFolder==NULL){	return false;	}
	if(G_GetLibraryNames==NULL)			{	return false;	}
	if(G_GetLibraryName==NULL)			{	return false;	}
	if(G_GetLibraryName2==NULL)			{	return false;	}
	if(G_GetLibraryColor==NULL)			{	return false;	}
	if(G_GetLibraryComment==NULL)		{	return false;	}
	if(G_SaveNew==NULL)					{	return false;	}
	if(G_SaveNewWithLibID==NULL)		{	return false;	}
	if(G_Update==NULL)					{	return false;	}
	if(G_Load==NULL)					{	return false;	}
	if(G_Delete==NULL)					{	return false;	}

	if(S_LibFolderFindFirst==NULL)		{	return false;	}
	if(S_CreateQuery==NULL)				{	return false;	}
	if(S_FindNext==NULL)				{	return false;	}
	if(S_DeleteQuery==NULL)				{	return false;	}
	if(S_LibFolderGetData==NULL)		{	return false;	}
	if(S_LibFolderFindData==NULL)		{	return false;	}
	if(S_LibFolderFindFirstByParentID==NULL)	{	return false;	}
	if(S_LibFolderCreatenew==NULL)		{	return false;	}
	if(S_LibFolderUpdate==NULL)			{	return false;	}
	if(S_LibCopy==NULL)					{	return false;	}
	if(S_GetFirstLibFolderByMasterCode==NULL)		{	return false;	}
	if(S_GetLibraryLayers==NULL)		{	return false;	}
	if(S_GetLibrarySourceID==NULL)		{	return false;	}
	if(S_EnumLibraryInSourceID==NULL)	{	return false;	}
	if(S_GetLibraryFolderID==NULL)		{	return false;	}

	if(S_MasterCategoryFindFirst==NULL)	{	return false;	}
	if(S_MasterCategoryGetData==NULL)	{	return false;	}
	if(S_MasterCategoryFindFirstByParentID==NULL)	{	return false;	}
	if(S_MasterCategoryCreatenew==NULL)	{	return false;	}
	if(S_MasterCategoryUpdate==NULL)	{	return false;	}

	if(S_GetLibraryTypeFirst==NULL)		{	return false;	}
	if(S_GetLibraryTypeData	==NULL)		{	return false;	}

	if(S_CheckAndCreateBlobInMasterPageTable==NULL)	{	return false;	}

	if(G_XUpdateDatabase==NULL)			{	return false;	}
	if(G_XUpdateDatabaseClose==NULL)	{	return false;	}
	if(G_XGetTableAndFieldList==NULL)	{	return false;	}
	if(G_XGetField==NULL)				{	return false;	}
	if(G_XTableCheck==NULL)				{	return false;	}
	if(G_XFieldCheckType==NULL)			{	return false;	}
	if(G_XFieldCheckNull==NULL)			{	return false;	}
	if(G_XUpdateDatabaseCreateDatabase==NULL)	{	return false;	}
	if(G_XUpdateDatabaseCheck==NULL)	{	return false;	}
	if(G_XUpdateDatabaseCheckGenerator==NULL)	{	return false;	}
	if(G_XTableCheckIndex==NULL)		{	return false;	}
	if(G_XGetIndex==NULL)				{	return false;	}
	if(G_XTableCheckTrigger	==NULL)		{	return false;	}
	if(G_XTableCreateTable	==NULL)		{	return false;	}
	if(G_XUpdateDatabaseSaveField==NULL){	return false;	}
	if(G_XUpdateDatabaseDropAllIndex==NULL)		{	return false;	}
	if(G_XUpdateDatabaseChange	==NULL)	{	return false;	}
	if(G_XUpdateDatabaseChangeGenerator==NULL)	{	return false;	}
	if(G_XIndexCreateIndex	==NULL)			{	return false;	}
	if(G_XTableChangeIndex	==NULL)			{	return false;	}
	if(G_XTriggerCreateTrigger	==NULL)		{	return false;	}
	if(G_XTableChangeTrigger==NULL)			{	return false;	}
	if(G_LocalDatabaseBasicClassConnect==NULL)	{	return false;	}
	if(G_LocalDatabaseBasicClassDisconnect==NULL)	{	return false;	}
	if(G_EnumColorSample==NULL)				{	return false;	}
	if(G_SaveNewColorSample==NULL)			{	return false;	}
	if(G_UpdateColorSample==NULL)			{	return false;	}
	if(G_LoadColorSample==NULL)				{	return false;	}
	if(G_DeleteColorSample==NULL)			{	return false;	}
	if(G_GetMachineInfo==NULL)				{	return false;	}
	if(G_MachineIDExists==NULL)				{	return false;	}

	if(G_CreateNewMasterRelation==NULL)		{	return false;	}
	if(G_UpdateMasterRelation==NULL)		{	return false;	}
	if(G_FindMasterRelation==NULL)			{	return false;	}
	if(G_SetRelationOnMasterData==NULL)		{	return false;	}
	if(G_SearchMasterCode==NULL)			{	return false;	}
	if(G_GetRelationCode==NULL)				{	return false;	}
	if(G_GetMasterRelation==NULL)			{	return false;	}
	if(G_EnumMasterRelation==NULL)			{	return false;	}
	if(G_UpdateLastLoadedTimeMasterRelation==NULL)			{	return false;	}

	if(G_GetMaxLearningIDAndInsertEmpty==NULL){	return false;	}
	if(G_UpdateLearning==NULL)				{	return false;	}
	if(G_InsertLearningParam==NULL)			{	return false;	}
	if(G_DeleteLearning==NULL)				{	return false;	}
	if(G_InsertLearningInDB==NULL)			{	return false;	}
	if(G_UpdateLearningInDB==NULL)			{	return false;	}
	if(G_LoadLearningInDB==NULL)			{	return false;	}

	if(S_GetNGTypeEnum==NULL)				{	return false;	}
	if(S_GetNGTypData==NULL)				{	return false;	}
	if(S_SaveNewNGTypData==NULL)			{	return false;	}
	if(S_UpdateNGTypData==NULL)				{	return false;	}
	if(S_DeleteNGTypData==NULL)				{	return false;	}
	if(G_GetInspectionLot==NULL)			{	return false;	}
	if(G_DeleteInspectionLot==NULL)			{	return false;	}

	if(G_EnumCommonDataInLibType==NULL)		{	return false;	}
	if(G_SaveNewCommonDataInLibType==NULL)	{	return false;	}
	if(G_UpdateCommonDataInLibType==NULL)	{	return false;	}
	if(G_LoadCommonDataInLibType==NULL)		{	return false;	}
	if(G_DeleteCommonDataInLibType==NULL)	{	return false;	}

	if(S_LevelFindFirst				==NULL)	{	return false;	}
	if(S_LevelGetData				==NULL)	{	return false;	}
	if(S_LevelFindData				==NULL)	{	return false;	}
	if(S_LevelFindFirstByParentID	==NULL)	{	return false;	}
	if(S_LevelCreatenew				==NULL)	{	return false;	}
	if(S_LevelUpdate				==NULL)	{	return false;	}
	if(S_EnumLevelID				==NULL)	{	return false;	}
	if(S_RemoveLevel				==NULL)	{	return false;	}

	if(S_ThresholdStockerGetData	==NULL)	{	return false;	}
	if(S_ThresholdStockerFindFirst	==NULL)	{	return false;	}
	if(S_ThresholdStockerCreatenew	==NULL)	{	return false;	}
	if(S_ThresholdStockerUpdate		==NULL)	{	return false;	}
	if(S_DeleteThresholdStocker		==NULL)	{	return false;	}


	if(GetLayersBase()!=NULL){
		GetLayersBase()->InformToLoadDLL(PathAndFileName);
	}
	return true;
}

bool	DatabaseLoader::DatabaseRelease(void)
{
	if(DllLib.isLoaded()==true){
		DllLib.unload();
	}
	return true;
}
void	DatabaseLoader::DatabaseLock(void)
{
	Mutex.lock();
}

void	DatabaseLoader::DatabaseUnlock(void)
{
	Mutex.unlock();
}
