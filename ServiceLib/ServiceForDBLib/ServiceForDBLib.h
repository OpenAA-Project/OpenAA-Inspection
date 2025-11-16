/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceForDBLib\ServiceForDBLib.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SERVICEFORDBLIB_H
#define SERVICEFORDBLIB_H

#include <QSqlQuery>
#include <QString>
#include <QBuffer>
#include <QImage>
#include "XDateTime.h"
#include "XTypeDef.h"

class	LayersBase;
class	DataInPage;
class AlgorithmLibraryLevelContainer;
class	AlgorithmLibraryContainer;
class	AlgorithmLibraryListContainer;
class	AlgorithmLibrary;
class	ParamGlobal;
class	ParamComm;
class	ColorSampleList;
class	OutlineOffsetInBlob;
class	RelationMasterList;
class	LibNGTypeItem;
class	IntList;
class	CommonDataInLibTypeListContainer;
class	CommonDataInLibType;
class	LearningInDB;

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

extern	"C"{
DEFFUNCEX	void	__G_LockDB(void);
DEFFUNCEX	void	__G_UnlockDB(void);
DEFFUNCEX	int		__G_SQLSaveNewMasterData(QSqlDatabase &DB ,LayersBase *Base);
DEFFUNCEX	bool	__G_SQLUpdateMasterData(QSqlDatabase &DB ,LayersBase *Base ,ParamGlobal *GParam
										  ,QBuffer &GeneralBuff ,QBuffer &SettingBuff 
										  ,QBuffer &LightDataArray ,QBuffer &GeneralStockerBuff,QBuffer &ResultAnalizerBuff
										  ,QBuffer &TopViewBuff);
DEFFUNCEX	bool	__G_SQLLoadMasterData(QSqlDatabase &DB ,LayersBase *Base ,int masterCode
										,QBuffer &GeneralBuff ,QBuffer	&SettingBuff 
										,QBuffer &LightBuff
										,QBuffer &GeneralStockerBuff
										,QBuffer &ResultAnalizerBuff
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
										,int32 &ThresholdLevelParentID);
DEFFUNCEX	bool	__G_SQLLoadMasterData2(QSqlDatabase &DB
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
							,int32 &ThresholdLevelParentID);

DEFFUNCEX	bool	__G_SQLGetMasterInfo(QSqlDatabase &DB ,int masterCode
										,int32 &MachineID
										,XDateTime &RegTime
										,QString &MasterName ,QString &Remark
										,int32 &Version
										,XDateTime &LastEditTime
										,int32 &CategoryID
										,int16 &MasterType
										,int32 &LibFolderID
										,int32 &ThresholdLevelID
										,int32 &ThresholdLevelParentID);

DEFFUNCEX	bool	__G_SQLCheckMasterName(QSqlDatabase &DB
										,int32 MachineID
										,QString MasterName
										,IntList &RetMasterCodes);

DEFFUNCEX	QImage	*__G_SQLLoadMasterTopview(QSqlDatabase &DB ,int masterCode);
DEFFUNCEX	bool	__G_SQLLoadMasterSetting(QSqlDatabase &DB ,int masterCode,QBuffer &SettingBuff );

DEFFUNCEX	bool	__G_SQLLoadWorker(QSqlDatabase &DB ,int workerID ,QString &RetName);

DEFFUNCEX	bool	__G_SQLSavePage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff,QBuffer &ImageBuff);
DEFFUNCEX	bool	__G_SQLLoadPage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff ,QBuffer &ImageBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
					  ,int &iVersion);
					  
DEFFUNCEX	bool	__G_SQLSavePageNoImage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff);
DEFFUNCEX	bool	__G_SQLLoadPageNoImage(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
					  ,int &iVersion);
DEFFUNCEX	bool	__G_SQLAddMasterFieldData	(QSqlDatabase &DB ,int32 masterCode  ,const QString &fieldName, const QVariant &data);
DEFFUNCEX	bool	__G_SQLAddRelationFieldData	(QSqlDatabase &DB ,int32 RelationCode,const QString &fieldName, const QVariant &data);
DEFFUNCEX	bool	__G_SQLLoadMasterFieldData	(QSqlDatabase &DB ,int32 masterCode  ,const QString &fieldName, QVariant &data);
DEFFUNCEX	bool	__G_SQLLoadRelationFieldData(QSqlDatabase &DB ,int32 RelationCode,const QString &fieldName, QVariant &data);

DEFFUNCEX	bool	__G_SQLSaveOutlineOfset(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter);
DEFFUNCEX	bool	__G_SQLLoadOutlineOfset(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter);

DEFFUNCEX	bool	__G_CheckAndCreateLibTypeInDatabase(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base);
DEFFUNCEX	int		__G_EnumLibrary(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
DEFFUNCEX	int		__G_EnumLibraryByType	(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
DEFFUNCEX	int		__G_EnumLibraryByTypeInt(QSqlDatabase &DB ,int LibType,int LibFolderID ,int IDList[] ,int MaxDimCount);
DEFFUNCEX	int		__G_EnumAllLibraryByType		(QSqlDatabase &DB ,int LibType		,AlgorithmLibraryListContainer &LibIDList);
DEFFUNCEX	int		__G_EnumAllLibraryByLibFolder	(QSqlDatabase &DB ,int LibFolderID		,AlgorithmLibraryListContainer &LibIDList);
DEFFUNCEX	void	__G_GetLibraryNames(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryListContainer &LibIDList);
DEFFUNCEX	QString	__G_GetLibraryName (QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibID);
DEFFUNCEX	QString	__G_GetLibraryName2(QSqlDatabase &DB ,int LibType ,int LibID);
DEFFUNCEX	QColor	__G_GetLibraryColor(QSqlDatabase &DB ,int LibType ,int LibID);
DEFFUNCEX	QString	__G_GetLibraryComment(QSqlDatabase &DB ,int LibType ,int LibID);
DEFFUNCEX	bool	__G_SaveNew			(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
DEFFUNCEX	bool	__G_SaveNewWithLibID(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
DEFFUNCEX	bool	__G_Update			(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
DEFFUNCEX	bool	__G_Load			(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
DEFFUNCEX	bool	__G_Delete			(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int32 LibID);

DEFFUNCEX	QSqlQuery *__S_LibFolderFindFirst(QSqlDatabase &DB);
DEFFUNCEX	QSqlQuery *__S_CreateQuery(QSqlDatabase &DB,const QString &Str);
DEFFUNCEX	bool	__S_FindNext(QSqlQuery *query);
DEFFUNCEX	bool	__S_DeleteQuery(QSqlQuery *query);
DEFFUNCEX	void	__S_LibFolderGetData(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
DEFFUNCEX	bool	__S_LibFolderFindData(QSqlDatabase &DB,int LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
DEFFUNCEX	QSqlQuery *__S_LibFolderFindFirstByParentID(QSqlDatabase &DB ,int parentID);
DEFFUNCEX	int		__S_LibFolderCreatenew(QSqlDatabase &DB);
DEFFUNCEX	void	__S_LibFolderUpdate(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int LibFolderID ,int MasterCode);
DEFFUNCEX	void	__S_LibCopy(QSqlDatabase &DB ,int sourceFolderID ,int destFolderID ,int LibType);
DEFFUNCEX	int		__S_GetFirstLibFolderByMasterCode(QSqlDatabase &DB ,int MasterCode ,QString &FolderName);
DEFFUNCEX	bool	__S_GetLibraryLayers(QSqlDatabase &DB ,int LibType,int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers);
DEFFUNCEX	int		__S_GetLibrarySourceID(QSqlDatabase &DB ,int LibType,int LibID);
DEFFUNCEX	int		__S_EnumLibraryInSourceID(QSqlDatabase &DB ,int LibType,int SourceLibID ,IntList &RetLibID);
DEFFUNCEX	int		__S_GetLibraryFolderID(QSqlDatabase &DB ,int LibType,int LibID);


DEFFUNCEX	QSqlQuery *__S_ColorFolderFindFirst(QSqlDatabase &DB);
DEFFUNCEX	void	__S_ColorFolderGetData(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
DEFFUNCEX	QSqlQuery *__S_ColorFolderFindFirstByParentID(QSqlDatabase &DB ,int parentID);
DEFFUNCEX	int		__S_ColorFolderCreatenew(QSqlDatabase &DB);
DEFFUNCEX	void	__S_ColorFolderUpdate(QSqlDatabase &DB ,int ParentID ,QString FolderName, int LibFolderID);

DEFFUNCEX	QSqlQuery *__S_MasterCategoryFindFirst(QSqlDatabase &DB);
DEFFUNCEX	void	__S_MasterCategoryGetData(QSqlQuery *query ,int &CategoryID ,QString &FolderName ,int &ParentID ,QString &Remark);
DEFFUNCEX	QSqlQuery *__S_MasterCategoryFindFirstByParentID(QSqlDatabase &DB ,int parentID);
DEFFUNCEX	int __S_MasterCategoryCreatenew(QSqlDatabase &DB);
DEFFUNCEX	void	__S_MasterCategoryUpdate(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int FolderID,const QString &Remark);

DEFFUNCEX	QSqlQuery *__S_GetLibraryTypeFirst(QSqlDatabase &DB);
DEFFUNCEX	void	__S_GetLibraryTypeData(QSqlQuery *query,int &LibType,QString &LibName);
DEFFUNCEX	void	__S_DeleteLibraryType(QSqlQuery *query);

DEFFUNCEX	QSqlQuery *__S_LightFindFirst(QSqlDatabase &DB ,int MachineCode);
DEFFUNCEX	bool	__S_GetFieldValue(QSqlQuery *query,const char *FieldName,QVariant &v);
DEFFUNCEX	QSqlQuery *__S_GetLight(QSqlDatabase &DB ,int MachineCode,int LightID);
DEFFUNCEX	bool	__S_CreateNewLight(QSqlDatabase &DB ,int MachineID 
									   ,QString DLLIDName ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage);
DEFFUNCEX	QSqlQuery *__S_LightFindLast(QSqlDatabase &DB ,int MachineCode);
DEFFUNCEX	bool	__S_UpdateLight(QSqlDatabase &DB ,int MachineCode,int LightID ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage);
DEFFUNCEX	bool	__S_DeleteLight(QSqlDatabase &DB ,int MachineCode,int LightID);

DEFFUNCEX	bool	__S_CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db ,QString &BlobName);
DEFFUNCEX	QSqlDatabase	*__S_OpenDatabase(QSqlDatabase *DB);
DEFFUNCEX	QSqlDatabase	*__S_CloseDatabase(QSqlDatabase *DB);
DEFFUNCEX	bool	__S_IsValidDatabase(QSqlDatabase *DB);

DEFFUNCEX	int		__G_EnumColorSample		(QSqlDatabase &DB ,int SelectedColorFolder,ColorSampleList EnumData[] ,int MaxNumb);
DEFFUNCEX	bool	__G_SaveNewColorSample	(QSqlDatabase &DB ,ColorSampleList &Data);
DEFFUNCEX	bool	__G_UpdateColorSample	(QSqlDatabase &DB ,ColorSampleList &Data);
DEFFUNCEX	bool	__G_LoadColorSample		(QSqlDatabase &DB ,ColorSampleList &Data,QBuffer &DataBuff);
DEFFUNCEX	bool	__G_DeleteColorSample	(QSqlDatabase &DB ,ColorSampleList &Data);

DEFFUNCEX	bool	__G_EnumMasterRelation(QSqlDatabase &DB ,IntList &RelationCodes);
DEFFUNCEX	bool	__G_UpdateLastLoadedTimeMasterRelation(QSqlDatabase &DB 
												,int RelationCode);

DEFFUNCEX	int		__G_EnumMachine(QSqlDatabase &DB ,int MachineIDList[] ,int MaxList);
DEFFUNCEX	bool	__G_GetMachineInfo(QSqlDatabase &DB ,int MachineID 
								,QString &NetID
								,QString &Name
								,QString &Version
								,QString &Remark);
DEFFUNCEX	bool	__G_MachineIDExists(QSqlDatabase &DB ,int MachineID);

DEFFUNCEX	bool	__G_CreateNewMasterRelation(QSqlDatabase &DB 
												,int &RetRelationCode
												,const QString &RelationNumber
												,const QString &RelationName
												,const QString &Remark
												,int RelationType
												,QByteArray &CommonData
												,int32 ThresholdLevelID);
DEFFUNCEX	bool	__G_UpdateMasterRelation(QSqlDatabase &DB 
												,int RelationCode
												,const QString &RelationNumber
												,const QString &RelationName
												,const QString &Remark
												,int RelationType
												,QByteArray &CommonData
												,int32 ThresholdLevelID);
DEFFUNCEX	bool	__G_FindMasterRelation(QSqlDatabase &DB 
										,const QString &RelationName
										,const QString &RelationNumber
										,const QString &Remark
										,IntList &RelationCodes);
DEFFUNCEX	bool	__G_SetRelationOnMasterData(QSqlDatabase &DB ,int MasterCode,int RelationCode ,int RelationID);
DEFFUNCEX	int		__G_SearchMasterCode(QSqlDatabase &DB ,int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount);
DEFFUNCEX	int		__G_GetRelationCode(QSqlDatabase &DB ,int MasterCode);
DEFFUNCEX	bool	__G_GetMasterRelation(QSqlDatabase &DB 
										,int RelationCode
										,QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID);

DEFFUNCEX	int		__G_GetMaxLearningIDAndInsertEmpty(QSqlDatabase &DB);
DEFFUNCEX	bool	__G_UpdateLearning(QSqlDatabase &DB 
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
								,const QByteArray &Alignment);
DEFFUNCEX	int		__G_InsertLearningParam(QSqlDatabase &DB 
									,int LearningID
									,int LibType
									,int LibID
									,const QByteArray &AlgoItems);
DEFFUNCEX	bool	__G_DeleteLearning(QSqlDatabase &DB 
								,int LearningID);
DEFFUNCEX	bool	__G_InsertLearningInDB(QSqlDatabase &DB ,LearningInDB &src);
DEFFUNCEX	bool	__G_UpdateLearningInDB(QSqlDatabase &DB ,LearningInDB &src);
DEFFUNCEX	bool	__G_LoadLearningInDB(QSqlDatabase &DB ,int LearningID,LearningInDB &src);

DEFFUNCEX	bool	__S_GetNGTypeEnum(QSqlDatabase &DB ,int LibType ,int LibID ,IntList &NGTypeList);
DEFFUNCEX	bool	__S_GetNGTypData(QSqlDatabase &DB
									,int LibType ,int LibID ,int NGTypeID
									,LibNGTypeItem *Item
									,QByteArray	&SpecifiedData);
DEFFUNCEX	bool	__S_SaveNewNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID 
							,LibNGTypeItem *Item
							,QByteArray	&SpecifiedData);
DEFFUNCEX	bool	__S_UpdateNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID
								,LibNGTypeItem *Item
								,QByteArray	&SpecifiedData);
DEFFUNCEX	bool	__S_DeleteNGTypData(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID);

DEFFUNCEX	bool	__G_GetInspectionLot(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode
								,XDateTime &LastUpdated
								,QString &IDName
								,QString &LotName
								,QString &Remark);
DEFFUNCEX	bool	__G_DeleteInspectionLot(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode);

DEFFUNCEX	int		__G_EnumCommonDataInLibType		(QSqlDatabase &DB ,int LibType ,CommonDataInLibTypeListContainer &RetContainer);
DEFFUNCEX	bool	__G_SaveNewCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
DEFFUNCEX	bool	__G_UpdateCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
DEFFUNCEX	bool	__G_LoadCommonDataInLibType		(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
DEFFUNCEX	bool	__G_DeleteCommonDataInLibType	(QSqlDatabase &DB ,int LibType ,int32 CommonID);

DEFFUNCEX	QSqlQuery  *__S_LevelFindFirst(QSqlDatabase &DB);
DEFFUNCEX	void		__S_LevelGetData(QSqlQuery *query ,int &LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID,QString &Remark);
DEFFUNCEX	bool		__S_LevelFindData(QSqlDatabase &DB,int LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID,QString &Remark);
DEFFUNCEX	QSqlQuery  *__S_LevelFindFirstByParentID(QSqlDatabase &DB ,int ParentID);
DEFFUNCEX	int			__S_LevelCreatenew(QSqlDatabase &DB);
DEFFUNCEX	void		__S_LevelUpdate(QSqlDatabase &DB ,int LevelID ,int LevelValue ,const QString &LevelName, int ParentID,const QString &Remark);
DEFFUNCEX	bool		__S_RemoveLevel(QSqlDatabase &DB ,int LevelID);
DEFFUNCEX	int			__S_EnumLevelID(QSqlDatabase &DB ,int parentID ,IntList &LevelIDs);

DEFFUNCEX	void	__S_ThresholdStockerGetData(QSqlQuery *query
										,int &LibType,int &FolderID,int &LibID,int &ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark
										,QByteArray &ThresholdData);
DEFFUNCEX	QSqlQuery *__S_ThresholdStockerFindFirst(QSqlDatabase &DB ,int LibType,int FolderID);
DEFFUNCEX	int		__S_ThresholdStockerCreatenew(QSqlDatabase &DB,int LibType);
DEFFUNCEX	void	__S_ThresholdStockerUpdate(QSqlDatabase &DB ,int LibType,int FolderID,int LibID,int ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark,QByteArray &ThresholdData);
DEFFUNCEX	bool	__S_DeleteThresholdStocker(QSqlDatabase &DB ,int LibType ,int32 ThresholdID);
};

#endif // SERVICEFORDBLIB_H
