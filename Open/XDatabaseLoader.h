/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDatabaseLoader.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDATABASELOADER_H)
#define	XDATABASELOADER_H

#include <QtGui>
#include <QString>
#include <QBuffer>
#include <QMutex>
#include "XTypeDef.h"
#include"NList.h"
#include "XDatabaseType.h"
#include "XServiceForLayers.h"
#include "XDateTime.h"
#include "XLearningRegist.h"

class	QSqlDatabase;
class	QSqlQuery;

class	XTable;
class	XField;
class	XGenerator;
class	XIndex;
class	XTrigger;
class	XPocket;
class	XIndexTmp;
class	XFieldPointer;
class	XUpdateDatabase;
class	CommonDataInLibTypeListContainer;
class	CommonDataInLibType;

class	LayersBase;
class	DataInPage;
class   AlgorithmLibraryLevelContainer;
class	AlgorithmLibraryContainer;
class	AlgorithmLibraryListContainer;
class	AlgorithmLibrary;
class	ParamGlobal;
class	ParamComm;
class	ExcludedListPack;
class	ColorSampleList;
class	OutlineOffsetInBlob;
class	RelationMasterList;
class	LibNGTypeItem;
class	IntList;

class	DatabaseLoader: public ServiceForLayers
{
	QLibrary 	DllLib;
	QMutex		Mutex;
public:

	void		(*G_LockDB)(void);
	void		(*G_UnlockDB)(void);

	int		(*G_SQLSaveNewMasterData)(QSqlDatabase &DB ,LayersBase *Base);
	bool	(*G_SQLUpdateMasterData)(QSqlDatabase &DB ,LayersBase *Base ,ParamGlobal *GParam
										  ,QBuffer &GeneralBuff 
										  ,QBuffer &SettingBuff 
										  ,QBuffer &LightBuff 
										  ,QBuffer &GeneralStockerBuff
										  ,QBuffer &ResultAnalizerBuff
										  ,QBuffer &TopViewBuff);
	bool	(*G_SQLLoadMasterData)(QSqlDatabase &DB ,LayersBase *Base ,int masterCode
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
	bool	(*G_SQLLoadMasterData2)(QSqlDatabase &DB
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

	bool	(*G_SQLGetMasterInfo)(QSqlDatabase &DB ,int masterCode
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


	bool	(*G_SQLCheckMasterName)(QSqlDatabase &DB
										,int32 MachineID
										,QString MasterName
										,IntList &RetMasterCodes);

	QImage	*(*G_SQLLoadMasterTopview)(QSqlDatabase &DB ,int masterCode);
	bool	(*G_SQLLoadMasterSetting)(QSqlDatabase &DB ,int masterCode,QBuffer &SettingBuff );

	bool	(*G_SQLLoadWorker)(QSqlDatabase &DB ,int workerID ,QString &RetName);

	bool	(*G_SQLSavePage)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff,QBuffer &ImageBuff);
	bool	(*G_SQLLoadPage)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff ,QBuffer &ImageBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion);
					  
	bool	(*G_SQLSavePageNoImage)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
								,ParamGlobal *GParam ,ParamComm *CParam
								,QBuffer &GeneralBuff ,QBuffer &SettingBuff);
	bool	(*G_SQLLoadPageNoImage)(QSqlDatabase &DB ,DataInPage *PageBase,int32 masterCode
					  ,ParamGlobal *GParam ,ParamComm *CParam
					  ,QBuffer &GeneralBuff,QBuffer &SettingBuff
					  ,QByteArray LogicDLLBuff[],bool ValidLogicDLLBuff[]
						,int &iVersion);
	bool	(*G_SQLAddMasterFieldData)	 (QSqlDatabase &DB ,int32 masterCode	,const QString &fieldName, const QVariant &data);
	bool	(*G_SQLAddRelationFieldData) (QSqlDatabase &DB ,int32 RelationCode	,const QString &fieldName, const QVariant &data);
	bool	(*G_SQLLoadMasterFieldData)	 (QSqlDatabase &DB ,int32 masterCode	,const QString &fieldName, QVariant &data);
	bool	(*G_SQLLoadRelationFieldData)(QSqlDatabase &DB ,int32 RelationCode	,const QString &fieldName, QVariant &data);

	bool	(*G_SQLSaveOutlineOfset)(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter);
	bool	(*G_SQLLoadOutlineOfset)(QSqlDatabase &DB ,int32 MachineID
								,OutlineOffsetInBlob	*OutlineOffsetWriter);

	bool	(*G_CheckAndCreateLibTypeInDatabase)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base);
	int		(*G_EnumLibrary)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
	int		(*G_EnumLibraryByType	)(QSqlDatabase &DB ,int LibType,int LibFolderID ,AlgorithmLibraryListContainer &LibIDList);
	int		(*G_EnumLibraryByTypeInt)(QSqlDatabase &DB ,int LibType,int LibFolderID ,int IDList[] ,int MaxDimCount);
	int		(*G_EnumAllLibraryByType)(QSqlDatabase &DB ,int LibType,AlgorithmLibraryListContainer &LibIDList);
	int		(*G_EnumAllLibraryByLibFolder)(QSqlDatabase &DB ,int LibFolderID	,AlgorithmLibraryListContainer &LibIDList);
	void	(*G_GetLibraryNames)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryListContainer &LibIDList);
	QString	(*G_GetLibraryName2)(QSqlDatabase &DB , int LibType ,int LibID);
	QString	(*G_GetLibraryName)	(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int LibID);
	QColor	(*G_GetLibraryColor)(QSqlDatabase &DB , int LibType ,int LibID);
	QString	(*G_GetLibraryComment)(QSqlDatabase &DB ,int LibType ,int LibID);
	bool	(*G_SaveNew			)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
	bool	(*G_SaveNewWithLibID)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
	bool	(*G_Update			)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
	bool	(*G_Load			)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,AlgorithmLibraryLevelContainer &Data);
	bool	(*G_Delete			)(QSqlDatabase &DB ,AlgorithmLibraryContainer *Base ,int32 LibID);

	QSqlQuery *(*S_LibFolderFindFirst)(QSqlDatabase &DB);
	QSqlQuery *(*S_CreateQuery)(QSqlDatabase &DB,const QString &Str);
	bool	(*S_FindNext)(QSqlQuery *query);
	bool	(*S_DeleteQuery)(QSqlQuery *query);
	void	(*S_LibFolderGetData)(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
	bool	(*S_LibFolderFindData)(QSqlDatabase &DB,int LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
	QSqlQuery *(*S_LibFolderFindFirstByParentID)(QSqlDatabase &DB ,int parentID);
	int		(*S_LibFolderCreatenew)(QSqlDatabase &DB);
	void	(*S_LibFolderUpdate)(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int LibFolderID ,int MasterCode);
	void	(*S_LibCopy)(QSqlDatabase &DB ,int sourceFolderID ,int destFolderID ,int LibType);
	int		(*S_GetFirstLibFolderByMasterCode)(QSqlDatabase &DB ,int MasterCode ,QString &FolderName);
	bool	(*S_GetLibraryLayers)(QSqlDatabase &DB ,int LibType,int LibID ,IntList &AdaptedPickLayers ,IntList &AdaptedGenLayers);
	int		(*S_GetLibrarySourceID)(QSqlDatabase &DB ,int LibType,int LibID);
	int		(*S_EnumLibraryInSourceID)(QSqlDatabase &DB ,int LibType,int SourceLibID ,IntList &RetLibID);
	int		(*S_GetLibraryFolderID)(QSqlDatabase &DB ,int LibType,int LibID);

	QSqlQuery *(*S_ColorFolderFindFirst)(QSqlDatabase &DB);
	void	(*S_ColorFolderGetData)(QSqlQuery *query ,int &LibFolderID ,QString &FolderName ,int &ParentID ,int &NumberInFolder);
	QSqlQuery *(*S_ColorFolderFindFirstByParentID)(QSqlDatabase &DB ,int parentID);
	int		(*S_ColorFolderCreatenew)(QSqlDatabase &DB);
	void	(*S_ColorFolderUpdate)(QSqlDatabase &DB ,int ParentID ,QString FolderName, int LibFolderID);

	QSqlQuery *(*S_MasterCategoryFindFirst)(QSqlDatabase &DB);
	void	(*S_MasterCategoryGetData)(QSqlQuery *query ,int &CategoryID ,QString &FolderName ,int &ParentID ,QString &Remark);
	QSqlQuery *(*S_MasterCategoryFindFirstByParentID)(QSqlDatabase &DB ,int parentID);
	int		(*S_MasterCategoryCreatenew)(QSqlDatabase &DB);
	void	(*S_MasterCategoryUpdate)(QSqlDatabase &DB ,int ParentID ,const QString &FolderName, int FolderID,const QString &Remark);

	QSqlQuery *(*S_GetLibraryTypeFirst)(QSqlDatabase &DB);
	void	(*S_GetLibraryTypeData)(QSqlQuery *query,int &LibType,QString &LibName);
	void	(*S_DeleteLibraryType)(QSqlQuery *query);

	QSqlQuery *(*S_LightFindFirst)(QSqlDatabase &DB ,int MachineCode);
	bool	(*S_GetFieldValue)(QSqlQuery *query,const char *FieldName,QVariant &v);
	QSqlQuery *(*S_GetLight)(QSqlDatabase &DB ,int MachineCode,int LightID);
	bool	(*S_CreateNewLight)(QSqlDatabase &DB ,int MachineID 
								,QString DLLIDName ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage);
	QSqlQuery *(*S_LightFindLast)(QSqlDatabase &DB ,int MachineCode);
	bool	(*S_UpdateLight)(QSqlDatabase &DB ,int MachineCode,int LightID ,QString Name ,QString Remark ,QByteArray &LightData ,QByteArray &LightImage);
	bool	(*S_DeleteLight)(QSqlDatabase &DB ,int MachineCode,int LightID);

	void	(*G_XUpdateDatabase)(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port
								,QString TransIP ,int TransPort);
	void	(*G_XUpdateDatabaseClose)(QSqlDatabase &DBase);
	bool    (*G_XGetTableAndFieldList)(std::shared_ptr<DatabaseLoader> &DBLoader
										,QSqlDatabase &DBase
										,QString DBName
										,NPListPack<XTable> &TableList);
	bool    (*G_XTableCheck)(XTable *This ,QSqlQuery *QrField ,NPListPack<XField> &FieldList,QStringList &MismatchList ,ExcludedListPack *ExcludedList,QString &Name);
	bool    (*G_XGetField)(XTable *This ,QSqlQuery *QrField ,XField &Field);
	bool    (*G_XFieldCheckType)(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList
							,FieldType dType ,bool &Found,int Size 
							,QString Name);
	bool    (*G_XFieldCheckNull)(XTable *p,QSqlQuery *QrField ,QStringList &MismatchList ,QString Name,bool NotNull);
	bool    (*G_XUpdateDatabaseCreateDatabase)(QSqlDatabase &DBase ,QString DBName ,int DatabasePageSize,QStringList &MismatchList);
	bool    (*G_XUpdateDatabaseCheck)(QSqlDatabase &DBase ,QStringList &MismatchList
								,ExcludedListPack *ExcludedList
								,QString DBName
								,NPListPack<XGenerator> &GeneratorList
								,NPListPack<XTable> &TableList);
	bool    (*G_XUpdateDatabaseCheckGenerator)(QSqlDatabase &DBase ,QString DBName
													,NPListPack<XGenerator> &GeneratorList
													,QStringList &MismatchList);
	bool    (*G_XTableCheckIndex)(QSqlDatabase &db ,QSqlQuery *QrField ,QStringList &MismatchList 
									   ,QString Name
									   ,XIndex &PrimaryKey
									   ,NPListPack<XIndex> &IndexList);
	bool    (*G_XGetIndex)(QSqlDatabase &db ,QSqlQuery *QrField
							   ,QString Name
							   ,NPListPack<XField> &FieldList
							   ,NPListPack<XIndex> &RetIndexList);
	bool    (*G_XTableCheckTrigger)(QSqlQuery *QrTrig ,QStringList &MismatchList,QString Name,NPListPack<XTrigger> &TriggerList);
	bool    (*G_XTableCreateTable)(QSqlQuery *QrExe ,QStringList &MismatchList ,QString Name ,bool &Found
										,NPListPack<XField> &FieldList
										,XIndex &PrimaryKey);
	void    (*G_XUpdateDatabaseSaveField)(QSqlQuery *QrExe ,QSqlQuery *QrField
                                    ,XTable *x ,XField *f
									,QString TmpFieldName
									,QString &SaveFieldType
									,NPListPack<XPocket> &PocketList);
	bool    (*G_XUpdateDatabaseDropAllIndex)(QSqlDatabase &DBase ,NPListPack<XIndexTmp> &DroppedIndex,QString &tblName);
	bool    (*G_XUpdateDatabaseChange)(QSqlDatabase &DBase ,QStringList &MismatchList ,ExcludedListPack *ExcludedList
											,NPListPack<XTable> &TableList
											,bool &IsOKTableRemove
											,bool &IsOKFieldRemove
											,QString &TmpFieldName
											,XUpdateDatabase *This);
	bool    (*G_XUpdateDatabaseChangeGenerator)(QSqlDatabase &DBase ,QSqlQuery *QrExe ,QStringList &MismatchList
													,NPListPack<XGenerator> &GeneratorList);
	bool    (*G_XIndexCreateIndex)(QSqlQuery *QrExe,XTable *x
										,bool Unique ,bool Ascending
										,QString &Name
										,NPListPack<XFieldPointer> &KeyField);
	bool    (*G_XTableChangeIndex)(QSqlDatabase &db ,QSqlQuery *QrExe 
										,QSqlQuery *QrField 
										,QStringList &MismatchList ,QString &Name
										,XIndex &PrimaryKey
										,bool &Found
										,NPListPack<XIndex> &IndexList
										,XTable *This);
	bool    (*G_XTriggerCreateTrigger)(QSqlQuery *QrExe ,XTable *x ,QString &Name
											,TriggerAction Action
											,int Position
											,char *Contents);
	bool    (*G_XTableChangeTrigger)(QSqlQuery *QrExe ,QSqlQuery *QrTrig ,QStringList &MismatchList 
										  ,QString &Name
										  ,NPListPack<XTrigger> &TriggerList
										  ,XTable *This);
	bool	(*G_LocalDatabaseBasicClassConnect)(QSqlDatabase &DBase);
	bool	(*G_LocalDatabaseBasicClassDisconnect)(QSqlDatabase &DBase);

	bool	(*S_CheckAndCreateBlobInMasterPageTable)(const QSqlDatabase &db ,QString &BlobName);
	QSqlDatabase	*(*S_OpenDatabase)(QSqlDatabase *DB);
	QSqlDatabase	*(*S_CloseDatabase)(QSqlDatabase *DB);
	bool	(*S_IsValidDatabase)(QSqlDatabase *DB);

	int		(*G_EnumColorSample		)(QSqlDatabase &DB ,int SelectedColorFolder,ColorSampleList EnumData[] ,int MaxNumb);
	bool	(*G_SaveNewColorSample	)(QSqlDatabase &DB ,ColorSampleList &Data);
	bool	(*G_UpdateColorSample	)(QSqlDatabase &DB ,ColorSampleList &Data);
	bool	(*G_LoadColorSample		)(QSqlDatabase &DB ,ColorSampleList &Data,QBuffer &DataBuff);
	bool	(*G_DeleteColorSample	)(QSqlDatabase &DB ,ColorSampleList &Data);

	int		(*G_EnumMachine)(QSqlDatabase &DB ,int MachineIDList[] ,int MaxList);
	bool	(*G_GetMachineInfo)(QSqlDatabase &DB ,int MachineID 
								,QString &NetID
								,QString &Name
								,QString &Version
								,QString &Remark);

	bool	(*G_MachineIDExists)(QSqlDatabase &DB ,int MachineID);

	bool	(*G_CreateNewMasterRelation)(QSqlDatabase &DB 
										,int &RetRelationCode
										,const QString &RelationNumber
										,const QString &RelationName
										,const QString &Remark
										,int RelationType
										,QByteArray &CommonData
										,int32 ThresholdLevelID);
	bool	(*G_UpdateMasterRelation)(QSqlDatabase &DB 
										,int RelationCode
										,const QString &RelationNumber
										,const QString &RelationName
										,const QString &Remark
										,int RelationType
										,QByteArray &CommonData
										,int32 ThresholdLevelID);
	bool	(*G_FindMasterRelation)(QSqlDatabase &DB 
										,const QString &RelationName
										,const QString &RelationNumber
										,const QString &Remark
										,IntList &RelationCodes);
	bool	(*G_SetRelationOnMasterData)(QSqlDatabase &DB ,int MasterCode,int RelationCode ,int RelationID);
	int		(*G_SearchMasterCode)(QSqlDatabase &DB ,int RelationCode ,RelationMasterList MasterListDim[] ,int MaxListCount);
	int		(*G_GetRelationCode)(QSqlDatabase &DB ,int MasterCode);
	bool	(*G_GetMasterRelation)(QSqlDatabase &DB 
										,int RelationCode
										,QString &RetRelationNumber
										,QString &RetRelationName
										,QString &RetRemark
										,int &RetRelationType
										,QByteArray &CommonData
										,int32 &ThresholdLevelID);
	bool	(*G_EnumMasterRelation)(QSqlDatabase &DB ,IntList &RelationCodes);
	bool	(*G_UpdateLastLoadedTimeMasterRelation)(QSqlDatabase &DB 
												,int RelationCode);

	int		(*G_GetMaxLearningIDAndInsertEmpty)(QSqlDatabase &DB);
	bool	(*G_UpdateLearning)(QSqlDatabase &DB 
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
	int		(*G_InsertLearningParam)(QSqlDatabase &DB 
									,int LearningID
									,int LibType
									,int LibID
									,const QByteArray &AlgoItems);
	bool	(*G_DeleteLearning)(QSqlDatabase &DB 
								,int LearningID);
	bool	(*G_InsertLearningInDB)(QSqlDatabase &DB ,LearningInDB &src);
	bool	(*G_UpdateLearningInDB)(QSqlDatabase &DB ,LearningInDB &src);
	bool	(*G_LoadLearningInDB)(QSqlDatabase &DB ,int LearningID,LearningInDB &src);

	bool	(*S_GetNGTypeEnum)(QSqlDatabase &DB ,int LibType ,int LibID ,IntList &NGTypeList);
	bool	(*S_GetNGTypData)(QSqlDatabase &DB
							,int LibType ,int LibID ,int NGTypeID
							,LibNGTypeItem *Item
							,QByteArray	&SpecifiedData);
	bool	(*S_SaveNewNGTypData)(QSqlDatabase &DB
								,int LibType ,int LibID 
							,LibNGTypeItem *Item
							,QByteArray	&SpecifiedData);
	bool	(*S_UpdateNGTypData)(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID
								,LibNGTypeItem *Item
								,QByteArray	&SpecifiedData);
	bool	(*S_DeleteNGTypData)(QSqlDatabase &DB
								,int LibType ,int LibID ,int NGTypeID);

	bool	(*G_GetInspectionLot)(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode
								,XDateTime &LastUpdated
								,QString &IDName
								,QString &LotName
								,QString &Remark);
	bool	(*G_DeleteInspectionLot)(QSqlDatabase &DB 
								,int LotAutoCount,int MasterCode);

	int		(*G_EnumCommonDataInLibType		)(QSqlDatabase &DB ,int LibType ,CommonDataInLibTypeListContainer &RetContainer);
	bool	(*G_SaveNewCommonDataInLibType	)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
	bool	(*G_UpdateCommonDataInLibType	)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
	bool	(*G_LoadCommonDataInLibType		)(QSqlDatabase &DB ,int LibType ,CommonDataInLibType &Data);
	bool	(*G_DeleteCommonDataInLibType	)(QSqlDatabase &DB ,int LibType ,int32 CommonID);

	QSqlQuery *(*S_LevelFindFirst)(QSqlDatabase &DB);
	void	(*S_LevelGetData)(QSqlQuery *query ,int &LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID,QString &Remark);
	bool	(*S_LevelFindData)(QSqlDatabase &DB,int LevelID ,int &LevelValue ,QString &LevelName ,int &ParentID,QString &Remark);
	QSqlQuery *(*S_LevelFindFirstByParentID)(QSqlDatabase &DB ,int ParentID);
	int		(*S_LevelCreatenew)(QSqlDatabase &DB);
	void	(*S_LevelUpdate)(QSqlDatabase &DB ,int LevelID ,int LevelValue ,const QString &LevelName, int ParentID,const QString &Remark);
	bool	(*S_RemoveLevel)(QSqlDatabase &DB ,int LevelID);
	int		(*S_EnumLevelID)(QSqlDatabase &DB ,int parentID ,IntList &LevelIDs);

	void	(*S_ThresholdStockerGetData)(QSqlQuery *query
										,int &LibType,int &FolderID,int &LibID,int &ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark
										,QByteArray &ThresholdData);
	QSqlQuery *(*S_ThresholdStockerFindFirst)(QSqlDatabase &DB ,int LibType,int FolderID);
	int		(*S_ThresholdStockerCreatenew)(QSqlDatabase &DB,int LibType);
	void	(*S_ThresholdStockerUpdate)(QSqlDatabase &DB ,int LibType,int FolderID,int LibID,int ThresholdID
										,QString &ThresholdName,QString &ThresholdRemark,QByteArray &ThresholdData);
	bool	(*S_DeleteThresholdStocker	)(QSqlDatabase &DB ,int LibType ,int32 ThresholdID);


	explicit	DatabaseLoader(LayersBase *base);

	bool	DatabaseInitialLoad(const QString &PathAndFileName);
	bool	DatabaseRelease(void);

	void	DatabaseLock(void);
	void	DatabaseUnlock(void);

};
#endif