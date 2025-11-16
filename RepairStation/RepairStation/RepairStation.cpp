/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\RepairStation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QSqlQuery>
#include <QHeaderView>
#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>
#include <QSqlRecord>
#include <QGlobal.h>
#include <QMessageBox>

#include "RepairStation.h"
#include "XDataInLayerForRepair.h"
#include "ImageData.h"
#include "ImageDataUnit.h"
#include "LotSelectForm.h"
#include "XGeneralDialog.h"
#include "GeneralSettingForm.h"
#include "WorkerSelectForm.h"
#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include "XSequenceRepairLocal.h"
#include "clientmainRepair.h"
#include "XMainSchemeMemoryForRepair.h"
#include "XForWindows.h"
#include "XNetworkDrive.h"
#include "SearchMasterDataForm.h"
#include <omp.h>
#include <QTime>
#include "swap.h"
#include "RepairStationResource.h"

#include "PasswordEventOperator.h"

//extern	EntryPointForGlobal	EntryPointToFunc;

RepairStation::RepairStation(QString XmlConnect_DotFileName, QString RepairSetting_DotFileName, QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{	
	//初期処理
	Init(XmlConnect_DotFileName);

	//画像データ格納クラスユニットのインスタンスの作成
	IDataUnit=new ImageDataUnit();
	SetImageDataUnit(IDataUnit);

	//表面用マスターイメージ
	MakeFrontMaster();

	//個片マスターイメージ
	MasterImagePiece *MImagePiece=new MasterImagePiece();
	IDataUnit->AddImage(MImagePiece);

	//個片NGイメージ
	NGImagePiece *NGImgPiece=new NGImagePiece();
	IDataUnit->AddImage(NGImgPiece);
///	NGImgPiece->GetVScroll()->setVisible(false);
///	NGImgPiece->GetHScroll()->setVisible(false);

	//全体マスター表示部
	dwMasterImage2->setGeometry(dwMasterImage2->x(),dwMasterImage2->y(),dwMasterImage2->width(),0);
	dwMasterImage2->setMaximumHeight(0);

	//個片マスター表示部
	dwNGMasterPix->setWidget(IDataUnit->MImagePieceList[0]);
	dwNGInspectionPix->setWidget(IDataUnit->NGImagePieceList[0]);

	//マスターツリー表示
	MTFieldNames << LangSolver.GetString(RepairStation_LS,LID_59)/*"FOLDERNAME"*/ << LangSolver.GetString(RepairStation_LS,LID_60)/*"REMARK"*/ << LangSolver.GetString(RepairStation_LS,LID_61)/*"CATEGORYID"*/;
	MainFrame->ui.trMasterList->setColumnCount(MTFieldNames.count());
	MainFrame->ui.trMasterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	MainFrame->ui.trMasterList->setSelectionMode(QAbstractItemView::SingleSelection);
	MainFrame->ui.trMasterList->setSelectionBehavior(QAbstractItemView::SelectRows);
	MainFrame->ui.trMasterList->setHeaderLabels(MTFieldNames);
	MainFrame->ui.trMasterList->header()->setSectionResizeMode(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_62)/*"FOLDERNAME"*/),QHeaderView::Stretch);
	MainFrame->ui.trMasterList->hideColumn(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_63)/*"CATEGORYID"*/));

	//マスターツリーの表示
	ShowMasterTree();

	//マスターテーブル表示
	MFieldNames << LangSolver.GetString(RepairStation_LS,LID_64)/*"MASTERCODE"*/ << LangSolver.GetString(RepairStation_LS,LID_65)/*"MASTERNAME"*/ << LangSolver.GetString(RepairStation_LS,LID_66)/*"REGTIME"*/ << LangSolver.GetString(RepairStation_LS,LID_67)/*"REMARK"*/ << LangSolver.GetString(RepairStation_LS,LID_888)/*"MACHINEID"*/;
	MainFrame->ui.twMasterList->setColumnCount(MFieldNames.count());
	MainFrame->ui.twMasterList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	MainFrame->ui.twMasterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	MainFrame->ui.twMasterList->setSelectionMode(QAbstractItemView::SingleSelection);
	MainFrame->ui.twMasterList->setSelectionBehavior(QAbstractItemView::SelectRows);
	MainFrame->ui.twMasterList->setHorizontalHeaderLabels(MFieldNames);
	MainFrame->ui.twMasterList->setColumnWidth(MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_68)/*"MASTERCODE"*/),35);
	MainFrame->ui.twMasterList->setColumnWidth(MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_69)/*"REGTIME"*/),70);
	MainFrame->ui.twMasterList->setColumnWidth(MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_889)/*"MACHINEID"*/),30);
	MainFrame->ui.twMasterList->horizontalHeader()->setSectionResizeMode(MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_67)/*"REMARK"*/),QHeaderView::Stretch);

	//履歴テーブル表示
//	HFieldNames << tr("Key") << tr("EID") << tr("TIM") << tr("NGP") << tr("DAY") << tr("RES1") << tr("RES2") << tr("QNO1") << tr("QNO2") << tr("Key1") << tr("Key2");
//	HFieldNames << tr("Key") << tr("INM") << tr("EID") << tr("TIM") << tr("NGP") << tr("RES1") << tr("RES2") << tr("QNO1") << tr("QNO2") << tr("Key1") << tr("Key2");
	HFieldNames << LangSolver.GetString(RepairStation_LS,LID_70)/*"Key"*/ << LangSolver.GetString(RepairStation_LS,LID_71)/*"INM"*/ << LangSolver.GetString(RepairStation_LS,LID_72)/*"EID"*/ << LangSolver.GetString(RepairStation_LS,LID_73)/*"TIM"*/ << LangSolver.GetString(RepairStation_LS,LID_74)/*"NGP"*/ << LangSolver.GetString(RepairStation_LS,LID_75)/*"NG Area"*/ << LangSolver.GetString(RepairStation_LS,LID_76)/*"RES1"*/ << LangSolver.GetString(RepairStation_LS,LID_77)/*"RES2"*/ << LangSolver.GetString(RepairStation_LS,LID_78)/*"QNO1"*/ << LangSolver.GetString(RepairStation_LS,LID_79)/*"QNO2"*/ << LangSolver.GetString(RepairStation_LS,LID_80/*"Key1"*/) << LangSolver.GetString(RepairStation_LS,LID_81)/*"Key2"*/;
	dwHistoryList->ui.twHistoryList->setColumnCount(HFieldNames.count());
    dwHistoryList->ui.twHistoryList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dwHistoryList->ui.twHistoryList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dwHistoryList->ui.twHistoryList->setSelectionMode(QAbstractItemView::SingleSelection);
    dwHistoryList->ui.twHistoryList->setSelectionBehavior(QAbstractItemView::SelectRows);
	dwHistoryList->ui.twHistoryList->setHorizontalHeaderLabels(HFieldNames);
//	dwHistoryList->ui.twHistoryList->horizontalHeader()->setSectionResizeMode(HFieldNames.indexOf("NG Area"),QHeaderView::Stretch);
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_82)/*"Key"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_83)/*"INM"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_84)/*"NG Area"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_85)/*"RES1"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_86)/*"RES2"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_87)/*"QNO1"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_88)/*"QNO2"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_89)/*"Key1"*/));
	dwHistoryList->ui.twHistoryList->hideColumn		(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_90)/*"Key2"*/));
	dwHistoryList->ui.twHistoryList->setColumnWidth	(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_91)/*"INM"*/),40);
	dwHistoryList->ui.twHistoryList->setColumnWidth	(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_92)/*"EID"*/),40);
	dwHistoryList->ui.twHistoryList->setColumnWidth	(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_93)/*"TIM"*/),60);
	dwHistoryList->ui.twHistoryList->setColumnWidth	(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_94)/*"NGP"*/),45);
	dwHistoryList->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_95)/*"Helvetica"*/,10));

	//NGリストテーブル表示
//	NGFieldNames << tr("X, Y") << tr("RAL") << tr("NGJ") << tr("NGI") << tr("NGP") << tr("Side");
	NGFieldNames << LangSolver.GetString(RepairStation_LS,LID_96)/*"X, Y"*/ << LangSolver.GetString(RepairStation_LS,LID_97)/*"RAL"*/ << LangSolver.GetString(RepairStation_LS,LID_98)/*"ARA"*/ << LangSolver.GetString(RepairStation_LS,LID_99)/*"ARAIndex"*/ << LangSolver.GetString(RepairStation_LS,LID_100)/*"NGJ"*/ << LangSolver.GetString(RepairStation_LS,LID_101)/*"NGI"*/ << LangSolver.GetString(RepairStation_LS,LID_102)/*"NGP"*/ << LangSolver.GetString(RepairStation_LS,LID_103)/*"Side"*/ << LangSolver.GetString(RepairStation_LS,LID_104)/*"RowIndex"*/ << LangSolver.GetString(RepairStation_LS,LID_105)/*"wARA"*/;
	dwNGList->twNGList->setColumnCount(NGFieldNames.count());
    dwNGList->twNGList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dwNGList->twNGList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dwNGList->twNGList->setSelectionMode(QAbstractItemView::SingleSelection);
    dwNGList->twNGList->setSelectionBehavior(QAbstractItemView::SelectRows);
	dwNGList->twNGList->setHorizontalHeaderLabels(NGFieldNames);
//	dwNGList->twNGList->horizontalHeader()->setSectionResizeMode(NGFieldNames.indexOf("RAL"),QHeaderView::Stretch);
	dwNGList->twNGList->horizontalHeader()->setSectionResizeMode(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_106)/*"ARA"*/),QHeaderView::Stretch);
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_107)/*"ARAIndex"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_108)/*"NGJ"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_109)/*"NGI"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_110)/*"NGP"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_111)/*"Side"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_112)/*"RowIndex"*/));
	dwNGList->twNGList->hideColumn		(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_113)/*"wARA"*/));
	dwNGList->twNGList->setColumnWidth	(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_114)/*"X, Y"*/),80);
	dwNGList->twNGList->setColumnWidth	(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_115)/*"RAL"*/),80);

	//シグナル・スロット
	connect(MainFrame->ui.pbSearch,								SIGNAL(clicked()),												this,							SLOT(pbSearchClicked()));
	connect(MainFrame->ui.pbMasterSelect,						SIGNAL(clicked()),												this,							SLOT(pbMasterSelectClicked()));
	connect(MainFrame->ui.chNGPoint,							SIGNAL(toggled(bool)),											this,							SLOT(chNGPointToggled(bool)));
	connect(MainFrame->ui.chShowPieceLine,						SIGNAL(toggled(bool)),											this,							SLOT(chShowPieceLineToggled(bool)));
	connect(dwHistoryList->ui.pbUpdate,							SIGNAL(clicked()),												this,							SLOT(pbUpdateClicked()));
	connect(dwHistoryList->ui.pbChangeLot,						SIGNAL(clicked()),												this,							SLOT(pbChangeLotClicked()));
	connect(pbGeneralSetting,									SIGNAL(clicked()),												this,							SLOT(pbGeneralSettingClicked()));
	connect(pbSimulateSequence,									SIGNAL(clicked()),												this,							SLOT(pbSimulateSequenceClicked()));
	connect(pbClose,											SIGNAL(clicked()),												this,							SLOT(pbCloseClicked()));
	connect(pbShutdown,											SIGNAL(clicked()),												this,							SLOT(pbShutdownClicked()));
	connect(MainFrame->ui.twMasterList,							SIGNAL(doubleClicked(QModelIndex)),								this,							SLOT(pbMasterSelectClicked()));
	connect(chEditEnable,										SIGNAL(toggled(bool)),											this,							SLOT(chEditEnableToggled(bool)));
	connect(chNotShowHalt,										SIGNAL(toggled(bool)),											this,							SLOT(chNotShowHaltToggled(bool)));
	connect(dwHistoryList->ui.chReverseOrderDisplay,			SIGNAL(toggled(bool)),											this,							SLOT(chReverseOrderDisplayToggled(bool)));
	connect(MainFrame->ui.trMasterList,							SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,							SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	connect(MainFrame->ui.twMasterList->selectionModel(),		SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),				this,							SLOT(MasterListRowChanged(QModelIndex)));
	connect(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),				this,							SLOT(HistoryListRowChanged(QModelIndex)));
	connect(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),				this,							SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	connect(dwNGList->twNGList,									SIGNAL(SignalKeyLeft()),										this,							SLOT(SlotKeyLeft()));
	connect(dwNGList->twNGList,									SIGNAL(SignalKeyRight()),										this,							SLOT(SlotKeyRight()));
	connect(dwNGList->twNGList,									SIGNAL(SignalKeyEnter()),										this,							SLOT(SlotKeyEnter()));
	connect(dwNGList->twNGList,									SIGNAL(SignalKeyInsert()),										this,							SLOT(SlotKeyInsert()));
	connect(dwNGList->twNGList,									SIGNAL(SignalKeyInsertAll()),									this,							SLOT(SlotKeyInsertAll()));
	connect(IDataUnit->MImagePieceList[0],						SIGNAL(SignalOnPaint(QPainter &)),								this,							SLOT(SlotOnMPiecePaint(QPainter &)));
	connect(IDataUnit->MImagePieceList[0],						SIGNAL(SignalOnPieceRectChange(int,int)),						IDataUnit->MImageClassList[0],	SLOT(SlotMMouseLDown(int,int)));
	connect(IDataUnit->NGImagePieceList[0],						SIGNAL(SignalOnPaint(QPainter &)),								this,							SLOT(SlotOnNGPiecePaint(QPainter &)));
	connect(&tNGBlink,											SIGNAL(SignalRepaint()),										this,							SLOT(SlotNGRepaint()),Qt::QueuedConnection);
	connect(&tOKWindow,											SIGNAL(SignalRepaint(QColor)),									this,							SLOT(SlotOKRepaint(QColor)));
	connect(&tErrNext,											SIGNAL(SignalIsChanged()),										this,							SLOT(SlotIsChanged()),Qt::QueuedConnection);
	connect(&tXMLAppend,										SIGNAL(SignalClient_Update(QString)),							this,							SLOT(SlotClient_Update(QString)),Qt::QueuedConnection);
//	connect(&tXMLAppend,										SIGNAL(SignalClient_Update()),									this,							SLOT(SlotClient_Update()),Qt::QueuedConnection);

	//初期フォーカス（選択）の設定
	if(MainFrame->ui.trMasterList->topLevelItemCount()>0){
		MainFrame->ui.trMasterList->setCurrentItem(MainFrame->ui.trMasterList->topLevelItem(0));
		MainFrame->ui.trMasterList->setFocus();
	}
	MainFrame->ui.trMasterList->expandItem(MainFrame->ui.trMasterList->currentItem());
	if(MainFrame->ui.twMasterList->rowCount()>0){
		MainFrame->ui.twMasterList->selectRow(0);
	}

	//RepairSetting.datの読み込み
	SetRepairSettingFileName(RepairSetting_DotFileName);
	SetNGBlink(true);
	QStringList List;
	if(LoadFile(LangSolver.GetString(RepairStation_LS,LID_116)/*"./RepairSetting.dat"*/,List)){
		SetRepairSettingList(List);
		SetParameter();
		dwHistoryList	->ui.chReverseOrderDisplay	->setChecked(GetReverseOrderDisplay());
		chNotShowHalt								->setChecked(GetNotShowHalt());
	}

	//画像のシグモイド補正の適用
	SetSigmoid(GetSigVolume(),GetSigBright(),Brightness);
	//アルゴリズム別エラーの丸表示の色設定
	ColorSetting(citemList);

	if(GetNGBlink()){
		tNGBlink.start();
	}

	//NG赤丸表示チェック
	MainFrame->ui.chNGPoint->setChecked(true);
//	MainFrame->ui.chNGPoint->setChecked(false);

	//PluginDLL
	if(DLL_GetName!=NULL){
		//NG送りスレッドをSTART
		tErrNext.start();
		//チェックプログラム監視スレッドをSTART
		connect(DLL_GetCheckThreadInstance(),SIGNAL(SignalError(QString)),this,SLOT(SlotProcessCheck(QString)),Qt::QueuedConnection);
		DLL_StartProcessCheckThread(true);

		//MMCSetting.datの読み込み
		QStringList MMCSettingList;
		if(LoadFile(LangSolver.GetString(RepairStation_LS,LID_117)/*"./MMCSetting.dat"*/,MMCSettingList)){
			DLL_SetMMCSettingList(MMCSettingList);
			DLL_SetMMCParameter(dwHistoryList->ui.twHistoryList,HFieldNames);
			//NGリストの制御
			dwNGList->twNGList->SetEnableListControl(DLL_GetNGListControl());
		}
		dwHistoryList->ui.twHistoryList->showColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_118)/*"INM"*/));
		dwHistoryList->ui.twHistoryList->showColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_119)/*"NG Area"*/));
		dwHistoryList->ui.twHistoryList->horizontalHeader()->setSectionResizeMode(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_120)/*"NG Area"*/),QHeaderView::Stretch);
	}
	else{
		dwHistoryList->ui.twHistoryList->horizontalHeader()->setSectionResizeMode(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_121)/*"TIM"*/),QHeaderView::Stretch);
	}
}

RepairStation::~RepairStation()
{
	delete IDataUnit;
}

//マスター名称での検索
void RepairStation::pbSearchClicked()
{
	//マスター選択詳細画面の表示
	SearchMasterDataForm SearchMasterDataDialog(this,MTFieldNames,MFieldNames,0);
	if(!SearchMasterDataDialog.exec()){
		return;
	}

	//マスター選択
	if(MainFrame->ui.trMasterList->topLevelItemCount()>0){
		MainFrame->ui.trMasterList->setCurrentItem(MainFrame->ui.trMasterList->topLevelItem(0));
	}
	int RowCnt=MainFrame->ui.twMasterList->rowCount();
	int row;
	int column=MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_122)/*"MASTERCODE"*/);
	for(row=0;row<RowCnt;row++){
		if(MainFrame->ui.twMasterList->item(row,column)->text()==SearchMasterDataDialog.GetMasterCode()){
			break;
		}
	}
	if(row==RowCnt){
		return;
	}
	MainFrame->ui.twMasterList->selectRow(row);

	pbMasterSelectClicked();
}

void RepairStation::pbMasterSelectClicked(int BackMasterCode,bool IsBackLot)
{
	//カテゴリツリーリストのカレントがNULLの場合の処理
	if(MainFrame->ui.trMasterList->currentItem()==NULL){
		QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_123)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_124)/*"Please choose category list."*/);
		return;
	}

	//両面対応"RELATIONCODE"
	int BMCode=-1;

	//裏表対応
	if(BackMasterCode!=-1 || (BMCode=GetRelationCode())!=-1){
		if(BMCode!=-1){
			//裏面も読み込むかどうかの確認
			QMessageBox::StandardButton Btn=QMessageBox::information(this,LangSolver.GetString(RepairStation_LS,LID_894)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_888)/*"Do you read back side data?"*/,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,QMessageBox::Cancel);
			if(Btn==QMessageBox::Yes){
				if(IDataUnit->MImageClassList[SType]->ImageList.count()>0){
					MakeFrontMaster();
					SType=Front;
				}
			}
			else if(Btn==QMessageBox::No){
				BMCode=-1;
			}
			else{
				return;
			}
		}
	}
	if(BMCode==-1){
		if(IDataUnit->MImageClassList[SType]->ImageList.count()>0){
			//自動的に表面データとして再読み込みさせる
			if(DLL_GetName!=NULL){
				MakeFrontMaster();
				SType=Front;
			}
			else{
				QMessageBox::StandardButton Btn=QMessageBox::Yes;
				if(BackMasterCode==-1){
					Btn=QMessageBox::information(this,LangSolver.GetString(RepairStation_LS,LID_125)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_126)/*"Do you read as the back side data?"*/,QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,QMessageBox::Cancel);
				}
				if(Btn==QMessageBox::Yes){
					MakeBackMaster();
					SType=Back;
					if(GetMImageSplitter()==Qt::Vertical){
						dwMasterImage1->setGeometry(dwMasterImage1->x(),dwMasterImage1->y(),dwMasterImage->widget()->width(),(dwMasterImage->widget()->height()>>1)+5);
						dwMasterImage1->setMaximumHeight((dwMasterImage->widget()->height()>>1));
						dwMasterImage1->setMinimumHeight((dwMasterImage->widget()->height()>>1));
						dwMasterImage1->setMaximumWidth	(dwMasterImage->widget()->width());
						dwMasterImage1->setMinimumWidth	(dwMasterImage->widget()->width());
						dwMasterImage2->setGeometry(dwMasterImage2->x(),dwMasterImage2->y(),dwMasterImage->widget()->width()-2,(dwMasterImage->widget()->height()>>1)+5);
						dwMasterImage2->setMaximumHeight((dwMasterImage->widget()->height()>>1));
						dwMasterImage2->setMinimumHeight((dwMasterImage->widget()->height()>>1));
						dwMasterImage2->setMaximumWidth	(dwMasterImage1->width());
						dwMasterImage2->setMinimumWidth	(dwMasterImage1->width());
					}
					else{
						dwMasterImage1->setGeometry(dwMasterImage1->x(),dwMasterImage1->y(),(dwMasterImage->widget()->width()>>1)-8,dwMasterImage->widget()->height());
						dwMasterImage1->setMaximumHeight(dwMasterImage->widget()->height());
						dwMasterImage1->setMinimumHeight(dwMasterImage->widget()->height());
						dwMasterImage1->setMaximumWidth	((dwMasterImage->widget()->width()>>1));
						dwMasterImage1->setMinimumWidth	((dwMasterImage->widget()->width()>>1));
						dwMasterImage2->setGeometry(dwMasterImage2->x(),dwMasterImage2->y(),(dwMasterImage->widget()->width()>>1)-8,dwMasterImage->widget()->height());
						dwMasterImage2->setMaximumHeight(dwMasterImage1->height());
						dwMasterImage2->setMinimumHeight(dwMasterImage1->height());
						dwMasterImage2->setMaximumWidth	((dwMasterImage->widget()->width()>>1));
						dwMasterImage2->setMinimumWidth	((dwMasterImage->widget()->width()>>1));
					}
					MasterImageSplitter->addWidget(dwMasterImage2);
					dwMasterImage2->setVisible(true);
				}
				else if(Btn==QMessageBox::No){
					MakeFrontMaster();
					SType=Front;
				}
				else{
					return;
				}
			}
		}
	}
	IDataUnit->MImageClassList[SType]->ImgRate=GetImgRate();

	//「処理中」画面の表示
	::SetWidgetCenter(MainProcessing);
	MainProcessing->show();
	MainProcessing->SetUpdate(0);

	//マスター画像の表示
	if(!ShowMasterImage(BackMasterCode)){
		MainProcessing->close();
		return;
	}

	//XMLサーバとの接続
	if(!XMLConnection(LangSolver.GetString(RepairStation_LS,LID_127)/*"./XmlConnect-r.dat"*/,SType)){
		MainProcessing->close();
		return;
	}

	//NGリストのクリアの前にcbPieceListEditorをdelete
	if(cbPieceListEditor!=NULL){
		delete cbPieceListEditor;
		cbPieceListEditor=NULL;
	}

	//履歴、NGリストのクリア
	disconnect	(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	dwHistoryList->ui.twHistoryList->setRowCount(0);
	connect		(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	disconnect	(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	dwNGList->twNGList->setRowCount(0);
	connect		(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));

	//「処理中」画面のCLOSE
	MainProcessing->close();

	//ロット選択画面の表示
	lwBoardName->item((int)SType)->setText(MName);
	SetMasterID		(SType,MCode);
	SetMasterName	(SType,MName);
	SetCategoryID	(SType,MainFrame->ui.trMasterList->currentItem()->text(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_128)/*"CATEGORYID"*/)));

	LotSelectForm *LotSelectDialog=new LotSelectForm(this);
//	if(BackMasterCode==-1){
	if(IsBackLot==false){
		if(BMCode!=-1){
			LotSelectDialog->SetBoth(true);
		}
		GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),LotSelectDialog,this);
		D->exec();
		if(LotSelectDialog->GetResult()==false){
			delete LotSelectDialog;
			delete D;
			return;
		}
		IsBackLot=LotSelectDialog->GetBoth();
		delete LotSelectDialog;
		delete D;
	}
	else{
		//ロット指定の両面対応
		if(LotSelectDialog->ExecSelectLot(GetLotName(Front),GetLotID(Front))==false){
			GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),LotSelectDialog,this);
			D->exec();
			if(LotSelectDialog->GetResult()==false){
				delete LotSelectDialog;
				delete D;
				return;
			}
			delete LotSelectDialog;
			delete D;
		}
		else{
			delete LotSelectDialog;
		}
	}
/*
	GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),LotSelectDialog,this);
	D->exec();
	if(LotSelectDialog->GetResult()==false){
		delete LotSelectDialog;
		delete D;
		return;
	}
	delete LotSelectDialog;
	delete D;
*/
	//ロット選択後の処理
	lwLotName->item((int)SType)->setText(GetLotName(SType));
	ShowHistoryList(dwHistoryList->ui.twHistoryList,IDataUnit->MImageClassList.count(),HFieldNames);

	//表示順
	if(dwHistoryList->ui.chReverseOrderDisplay->isChecked()){
		chReverseOrderDisplayToggled(true);
	}
	else{
		chReverseOrderDisplayToggled(false);
	}

	//個片情報表示設定
	SetPieceInfoData(SType);

	//初期フォーカス（選択）の設定
	if(dwHistoryList->ui.twHistoryList->rowCount()>0){
		dwHistoryList->ui.twHistoryList->selectRow(0);
	}

	//履歴数を表示
	dwHistoryList->ui.leHistoryNumb->setText(QString::number(dwHistoryList->ui.twHistoryList->rowCount()));

	//プラグインDLL対応
	if(DLL_GetName!=NULL){
		MainFrame->ui.leLotName->setText(GetLotName(SType));
		QTableWidgetItem *Item;
		if((Item=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_129)/*"INM"*/)))!=NULL){
			MainFrame->ui.leLotCount->setText(Item->text());
		}
	}

	//両面対応"RELATIONCODE"
	if(BMCode!=-1){
		pbMasterSelectClicked(BMCode,IsBackLot);
	}
}

//NGマーク表示
void RepairStation::chNGPointToggled(bool Tog)
{
	if(!tNGBlink.StopFlag)
		return;
	IDataUnit->NGImagePieceList[0]->NGPointVisible=Tog;
	IDataUnit->NGImagePieceList[0]->repaint();
	dwNGList->twNGList->setFocus();
}

//個片枠表示
void RepairStation::chShowPieceLineToggled(bool Tog)
{
	IDataUnit->NGImagePieceList[0]->PieceLineVisible=Tog;
	IDataUnit->NGImagePieceList[0]->repaint();
	dwNGList->twNGList->setFocus();
}

void RepairStation::pbUpdateClicked()
{
	//Updateリトライカウンター
	int RetryCount	=6;
	int	RetryCounter=0;
	int	HistoryListRow;

	//「処理中」画面の表示
	::SetWidgetCenter(MainProcessing);
	MainProcessing->show();
	MainProcessing->SetUpdate(20);

	//更新前に退避しておく
	int cCategoryID	=GetCategoryID(SType).toInt();
	int cMasterID	=GetMasterID(SType).toInt();
	int ColQNO=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_130)/*"QNO1"*/);
	int NGRow=dwNGList->twNGList->currentRow();
	QString QueryNo;
	if((HistoryListRow=dwHistoryList->ui.twHistoryList->rowCount())>0){
		QTableWidgetItem *Item;
		if((Item=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColQNO))!=NULL){
			QueryNo	=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColQNO)->text();
		}
		else{
			QueryNo	=LangSolver.GetString(RepairStation_LS,LID_131)/*"-1"*/;
		}
	}
	if(QueryNo==LangSolver.GetString(RepairStation_LS,LID_132)/*"-1"*/){
		ColQNO=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_133)/*"QNO2"*/);
		QTableWidgetItem *Item;
		if((Item=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColQNO))!=NULL){
			QueryNo	=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColQNO)->text();
		}
	}
	int wiSide=iSide;

	//表示順
	bool RODCheck=dwHistoryList->ui.chReverseOrderDisplay->isChecked();

	//プラグインDLL対応
	if(DLL_GetName!=NULL){
		//Show NG Area
		if(DLL_GetShowNGArea()==true){
			if(HistoryNGColList!=NULL){
				delete []HistoryNGColList;
			}
			HistoryNGColList=new QString[HistoryListRow];
			int Col=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_134)/*"NG Area"*/);
			QTableWidgetItem *Item;
			if(RODCheck){
				for(int Cnt=0,Row=HistoryListRow-1;Cnt<HistoryListRow;Cnt++,Row--){
					if((Item=dwHistoryList->ui.twHistoryList->item(Row,Col))!=NULL){
						HistoryNGColList[Cnt]=Item->text();
					}
				}
			}
			else{
				for(int Row=0;Row<HistoryListRow;Row++){
					if((Item=dwHistoryList->ui.twHistoryList->item(Row,Col))!=NULL){
						HistoryNGColList[Row]=Item->text();
					}
				}
			}
		}
	}

	//マスターリストの更新
	ShowMasterTree(false);

	//リフレッシュ動作の表示
	disconnect(MainFrame->ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	MainFrame->ui.twMasterList->clearContents();
	MainFrame->ui.twMasterList->setRowCount(0);
	disconnect	(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	dwHistoryList->ui.twHistoryList->clearContents();
	dwHistoryList->ui.twHistoryList->setRowCount(0);
	disconnect	(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	dwNGList->twNGList->clearContents();
	dwNGList->twNGList->setRowCount(0);
	NGCountInBoard=0;
	repaint();
	connect(MainFrame->ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	MainFrame		->ui.twMasterList	->setUpdatesEnabled(false);
	dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(false);
	dwNGList		->twNGList			->setUpdatesEnabled(false);

	MainProcessing->SetUpdate(40);

	//初期フォーカス（選択）の設定
	if(MainFrame->ui.trMasterList->topLevelItemCount()>0){
		//QTreeWidgetItemの検索
		QTreeWidgetItem *TrW=CheckTrMasterList(MainFrame->ui.trMasterList->topLevelItem(0),MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_135)/*"CATEGORYID"*/),cCategoryID);
		MainFrame->ui.trMasterList->setCurrentItem(TrW);
		MainFrame->ui.trMasterList->setFocus();
		if(cMasterID!=-1){
			int Col=MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_136)/*"MASTERCODE"*/);
			for(int Row=0;Row<MainFrame->ui.twMasterList->rowCount();Row++){
				if(MainFrame->ui.twMasterList->item(Row,Col)->text().toInt()==cMasterID){
					MainFrame->ui.twMasterList->selectRow(Row);
					MainFrame->ui.twMasterList->setFocus();
					break;
				}
			}
		}
	}
	MainFrame->ui.trMasterList->expandItem(MainFrame->ui.trMasterList->currentItem());
	MainProcessing->SetUpdate(60);

	//XMLデータを読込むかどうかの判断
	if(GetLotID(SType).isEmpty()){
		MainFrame->ui.trMasterList->setCurrentItem(MainFrame->ui.trMasterList->topLevelItem(0));
		MainProcessing->close();
		MainFrame		->ui.trMasterList	->setUpdatesEnabled(true);
		MainFrame		->ui.twMasterList	->setUpdatesEnabled(true);
		dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(true);
		dwNGList		->twNGList			->setUpdatesEnabled(true);
		return;
	}

	//裏表対応
	if(IDataUnit->MImageClassList.count()==0){
		MainProcessing->close();
		MainFrame		->ui.trMasterList	->setUpdatesEnabled(true);
		MainFrame		->ui.twMasterList	->setUpdatesEnabled(true);
		dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(true);
		dwNGList		->twNGList			->setUpdatesEnabled(true);
		return;
	}
	int MImageCnt=IDataUnit->MImageClassList.count();

Retry:
	for(int Cnt=0;Cnt<MImageCnt;Cnt++){
		switch(Cnt){
			case 0:	SType=Front;	break;
			case 1:	SType=Back;		break;
		}
		QList<QByteArray> RetList;
		//XMLサーバとの接続確認（接続なしの場合は再接続）
		if(!XMLRetryConnection(SType)){
			MainProcessing->close();
			return;
		}
/*		if(GetLotID(SType)=="*"){
			//全ロット選択時の処理
		}
		else{
			//マスターIDとロットIDでClient_MasterStart
			if(!XMLMasterStart(&GetMasterID(SType),&GetLotID(SType),Cnt)){
				MainProcessing->close();
				return;
			}
			//XMLサーバからデータをTagSelect
			RetList.clear();
*/			QString strQueryXML=LangSolver.GetString(RepairStation_LS,LID_137)/*"IST"*/;
			if(!XMLSelect(&strQueryXML.toLocal8Bit().data(),&RetList,SType)){
				MainProcessing->close();
				MainFrame		->ui.trMasterList	->setUpdatesEnabled(true);
				MainFrame		->ui.twMasterList	->setUpdatesEnabled(true);
				dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(true);
				dwNGList		->twNGList			->setUpdatesEnabled(true);
				return;
			}
//		}
		SetRetXMLDataList(SType,&RetList);

		//履歴、NGリストのクリア
		disconnect	(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
		dwHistoryList->ui.twHistoryList->setRowCount(0);
		disconnect	(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
		dwNGList->twNGList->setRowCount(0);

		if(MImageCnt==1){
			ShowHistoryList(dwHistoryList->ui.twHistoryList,IDataUnit->MImageClassList.count(),HFieldNames);
		}
		else if(Cnt==1){
			ShowHistoryList(dwHistoryList->ui.twHistoryList,IDataUnit->MImageClassList.count(),HFieldNames,Cnt);
		}
	}
	connect		(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	connect		(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	MainProcessing->SetUpdate(80);
	UpdateFlg=true;

	//表示順
	chReverseOrderDisplayToggled(RODCheck);

	//プラグインDLL対応
	if(DLL_GetName!=NULL){
		//Show NG Area
		if(DLL_GetShowNGArea()==true){
			ShowNGArea(RODCheck,HistoryListRow);
		}
		//更新しても履歴が増えていない場合はリトライする
		if(HistoryListRow==dwHistoryList->ui.twHistoryList->rowCount() && RetryCounter<RetryCount){
			//Waitを置く
			for(time_t t=time(NULL);time(NULL)-t<2;){}
			RetryCounter++;
			goto	Retry;
		}
		//すべての検査結果が取得できたかどうか、<Page>タグで判断する
/*		QString		PageName;
		QStringList	PageNameList;
		for(int i=0;(PageName=GetString(&QString(GetRetXMLDataList(SType)->at(0)),"</Page",">",i)).isEmpty()==false;i++){
			PageNameList.append(PageName);
		}
*/
		//更新で抜けるのは異常信号を受け取った場合、もしくはタイムアウト
		if(SeqControlParamData->MacEmergency==true || RetryCounter==RetryCount){
			if(SeqControlParamData->MacErrorCode==0){								//A-20091106
				MainProcessing->close();
				MainFrame		->ui.trMasterList	->setUpdatesEnabled(true);
				MainFrame		->ui.twMasterList	->setUpdatesEnabled(true);
				dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(true);
				dwNGList		->twNGList			->setUpdatesEnabled(true);
				if(RetryCounter==RetryCount){
					DLL_SetMessageFormLabel(LangSolver.GetString(RepairStation_LS,LID_138)/*"検査結果を全て読込めませんでした！\n検査PC側で全て書込めなかった可能性があります\n\nOKボタンで異常を発生します。"*/);
					SeqControlParamData->ErrorCode|=0x40;
					SeqControlParamData->ErrorCount++;
					SeqControlParamData->ErrorIndex=22;
					//IsOutputLogをfalseに戻しておく（エラーメッセージが出るように）
					DLL_SetIsOutputLog(false);
				}
				return;
			}
		}
		if(GetRetXMLDataList(SType)->count()==0){
			//Waitを置く
			for(time_t t=time(NULL);time(NULL)-t<2;){}
			goto	Retry;
		}
		int PageTabCount=GetRetXMLDataList(SType)->last().count(LangSolver.GetString(RepairStation_LS,LID_139)/*"<Page"*/);
		if(PageTabCount!=PNumbForBase){
			//Waitを置く
			for(time_t t=time(NULL);time(NULL)-t<2;){}
			goto	Retry;
		}

//		//現在の検査番号を格納する
//		QString strInspectionNumb=GetString(&QString(GetRetXMLDataList(SType)->last()),"<INM>","</INM>");
//		SeqControlParamData->InspectionNumb=Item->text().toInt();

		//最後の（一番新しい）NG行に移動
		if(dwHistoryList->ui.chReverseOrderDisplay->isChecked()){
			dwHistoryList->ui.twHistoryList->selectRow(0);
		}
		else{
			dwHistoryList->ui.twHistoryList->selectRow(dwHistoryList->ui.twHistoryList->rowCount()-1);
		}
		NGRow=0;

		//ロット名称のセット
//		if(leLotName->text().isEmpty()){
		if(lwLotName->item((int)SType)->text().isEmpty()){
			lwLotName->item((int)SType)->setText(GetLotName(SType));
			MainFrame->ui.leLotName->setText(GetLotName(SType));
		}

		//Lot数のセット
		QTableWidgetItem *Item;
		if((Item=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_140)/*"INM"*/)))!=NULL){
			MainFrame->ui.leLotCount->setText(Item->text());
			SeqControlParamData->InspectionNumb=Item->text().toInt();	//現在の検査番号を格納する
		}

		//最初の更新時後は、ボタン操作をOnにさせる
		if(FirstUpdateFlag==true){
			DLL_SetReviewEnable(true);
			FirstUpdateFlag=false;
		}
	}
	else{
		for(int Row=0;Row<dwHistoryList->ui.twHistoryList->rowCount();Row++){
			if(dwHistoryList->ui.twHistoryList->item(Row,ColQNO)->text()==QueryNo){
				dwHistoryList->ui.twHistoryList->selectRow(Row);
				break;
			}
		}
	}
	MainProcessing->SetUpdate(100);

	iSide=wiSide;
	if(dwNGList->twNGList->rowCount()>0){
		dwNGList->twNGList->selectRow(NGRow);
		dwNGList->twNGList->setFocus();
	}
	UpdateFlg=false;

	MainFrame		->ui.trMasterList	->setUpdatesEnabled(true);
	MainFrame		->ui.twMasterList	->setUpdatesEnabled(true);
	dwHistoryList	->ui.twHistoryList	->setUpdatesEnabled(true);
	dwNGList		->twNGList			->setUpdatesEnabled(true);
	MainProcessing->close();

	//履歴数を表示
	dwHistoryList->ui.leHistoryNumb->setText(QString::number(dwHistoryList->ui.twHistoryList->rowCount()));
}

void RepairStation::pbChangeLotClicked()
{
	//ロット選択画面の表示
	if(IDataUnit->MImageClassList.count()==0){
		QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_141)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_142)/*"Please choose Master data."*/);
		return;
	}

	NGListFlag=false;
	disconnect(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	disconnect(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));

	bool IsBackLot=false;
	for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
		switch(Cnt){
			case 0:	SType=Front;	break;
			case 1:	SType=Back;		break;
		}
		LotSelectForm *LotSelectDialog=new LotSelectForm(this);
		if(IDataUnit->MImageClassList.count()==2 && Cnt==0){
			LotSelectDialog->SetBoth(true);
		}
		if(IsBackLot==false){
			GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),LotSelectDialog,this);
			D->exec();
			if(LotSelectDialog->GetResult()==false){
				delete LotSelectDialog;
				delete D;
				continue;
			}
			IsBackLot=LotSelectDialog->GetBoth();
			delete LotSelectDialog;
			delete D;
		}
		else{
			//???b?g?w?e?I???E?I??
			if(LotSelectDialog->ExecSelectLot(GetLotName(Front),GetLotID(Front))==false){
				GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),LotSelectDialog,this);
				D->exec();
				if(LotSelectDialog->GetResult()==false){
					delete LotSelectDialog;
					delete D;
					continue;
				}
				delete LotSelectDialog;
				delete D;
			}
			else{
				delete LotSelectDialog;
			}
		}

		//ロット選択後の処理
		//履歴、NGリストのクリア
		dwHistoryList->ui.twHistoryList->setRowCount(0);
		dwNGList->twNGList->setRowCount(0);

		lwLotName->item((int)SType)->setText(GetLotName(SType));

		if(IDataUnit->MImageClassList.count()==1){
			ShowHistoryList(dwHistoryList->ui.twHistoryList,IDataUnit->MImageClassList.count(),HFieldNames);
		}
		else{
			ShowHistoryList(dwHistoryList->ui.twHistoryList,IDataUnit->MImageClassList.count(),HFieldNames,Cnt);
		}

		//直前のXMLデータをクリアする
		strXML[Cnt]=LangSolver.GetString(RepairStation_LS,LID_143)/*""*/;
	}
	connect(dwHistoryList->ui.twHistoryList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(HistoryListRowChanged(QModelIndex)));
	connect(dwNGList->twNGList->selectionModel(),				SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	NGListFlag=true;

	//表示順
	if(dwHistoryList->ui.chReverseOrderDisplay->isChecked())
		chReverseOrderDisplayToggled(true);
	else
		chReverseOrderDisplayToggled(false);

	//個片情報表示設定
	SetPieceInfoData(SType);

	//初期フォーカス（選択）の設定
	if(dwHistoryList->ui.twHistoryList->rowCount()>0){
		dwHistoryList->ui.twHistoryList->selectRow(0);
	}

	//履歴数を表示
	dwHistoryList->ui.leHistoryNumb->setText(QString::number(dwHistoryList->ui.twHistoryList->rowCount()));

	//プラグインDLL対応
	if(DLL_GetName!=NULL){
		MainFrame->ui.leLotName->setText(GetLotName(SType));
		//ロット選択後は、ボタン操作をOffにさせる
		DLL_SetReviewEnable(false);
		FirstUpdateFlag=true;
		//デバッグログ出力
		if(OpenDebugLogFile(LangSolver.GetString(RepairStation_LS,LID_144)/*"D:/"*/,QDateTime::currentDateTime().toString(LangSolver.GetString(RepairStation_LS,LID_145)/*"yyyyMMdd_HHmmss"*/))==false){
			WriteDebugLogFile(LangSolver.GetString(RepairStation_LS,LID_146)/*"File Open Error."*/);
		}
	}
	else{
		if(GetOutputDebugLog()==true){
			//デバッグログ出力
			if(OpenDebugLogFile(LangSolver.GetString(RepairStation_LS,LID_147)/*"C:/"*/,QDateTime::currentDateTime().toString(LangSolver.GetString(RepairStation_LS,LID_148)/*"yyyyMMdd_HHmmss"*/))==false){
				WriteDebugLogFile(LangSolver.GetString(RepairStation_LS,LID_149)/*"File Open Error."*/);
			}
		}
	}
}

void RepairStation::pbGeneralSettingClicked()
{
	//一般設定画面の表示
	GeneralSettingForm GeneralSettingDialog(this,0);

	if(!GeneralSettingDialog.exec()){
		return;
	}

	if(dwMasterImage2->isVisible()==true){
		if(GetMImageSplitter()==Qt::Vertical){
			dwMasterImage1->setGeometry(dwMasterImage1->x(),dwMasterImage1->y(),dwMasterImage->widget()->width(),(dwMasterImage->widget()->height()>>1)+5);
			dwMasterImage1->setMaximumHeight((dwMasterImage->widget()->height()>>1));
			dwMasterImage1->setMinimumHeight((dwMasterImage->widget()->height()>>1));
			dwMasterImage1->setMaximumWidth	(dwMasterImage->widget()->width());
			dwMasterImage1->setMinimumWidth	(dwMasterImage->widget()->width());
			dwMasterImage2->setMaximumHeight((dwMasterImage->widget()->height()>>1));
			dwMasterImage2->setMinimumHeight((dwMasterImage->widget()->height()>>1));
			dwMasterImage2->setMaximumWidth	(dwMasterImage1->width());
			dwMasterImage2->setMinimumWidth	(dwMasterImage1->width());
		}
		else{
			dwMasterImage1->setGeometry(dwMasterImage1->x(),dwMasterImage1->y(),(dwMasterImage->widget()->width()>>1)-8,dwMasterImage->widget()->height());
			dwMasterImage1->setMaximumHeight(dwMasterImage->widget()->height());
			dwMasterImage1->setMinimumHeight(dwMasterImage->widget()->height());
			dwMasterImage1->setMaximumWidth	((dwMasterImage->widget()->width()>>1));
			dwMasterImage1->setMinimumWidth	((dwMasterImage->widget()->width()>>1));
			dwMasterImage2->setMaximumHeight(dwMasterImage1->height());
			dwMasterImage2->setMinimumHeight(dwMasterImage1->height());
			dwMasterImage2->setMaximumWidth	((dwMasterImage->widget()->width()>>1));
			dwMasterImage2->setMinimumWidth	((dwMasterImage->widget()->width()>>1));
		}
	}
	MasterImageSplitter->setOrientation((Qt::Orientation)GetMImageSplitter());	//Master Image Splitter
}

void RepairStation::pbSimulateSequenceClicked()
{
	if(EntryPointToFuncGlobal->GetThreadSequence()!=NULL)
		EntryPointToFuncGlobal->GetThreadSequence()->ShowSimulateSequence(this);
}

void RepairStation::pbCloseClicked()
{
	close();
}

void RepairStation::pbShutdownClicked()
{
	//PCシャットダウン
//	MtShutdownSelfPC(true,false);
}

void RepairStation::chEditEnableToggled(bool toggled)
{
	if(toggled){
		//表示設定
		setWindowFlags(Qt::WindowMinMaxButtonsHint);
		show();
//		MainFrame			->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwMasterImage		->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwMasterImage1		->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwMasterImage2		->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwNGMasterPix		->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwNGInspectionPix	->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwHistoryList		->setFeatures(QDockWidget::AllDockWidgetFeatures);
//		dwNGList			->setFeatures(QDockWidget::AllDockWidgetFeatures);

		MainFrame						->setMinimumSize(10,10);
		MainFrame						->setMaximumSize(16777215,16777215);
		MainFrame->ui.trMasterList		->setMinimumSize(10,10);
		MainFrame->ui.trMasterList		->setMaximumSize(16777215,16777215);
		MainFrame->ui.twMasterList		->setMinimumSize(10,10);
		MainFrame->ui.twMasterList		->setMaximumSize(16777215,16777215);
//		MainFrame->ui.layoutWidget		->setMinimumSize(10,10);
//		MainFrame->ui.layoutWidget		->setMaximumSize(16777215,16777215);
		dwMasterImage					->setMinimumSize(10,10);
		dwMasterImage					->setMaximumSize(16777215,16777215);
		dwMasterImage1					->setMinimumSize(10,10);
		dwMasterImage1					->setMaximumSize(16777215,16777215);
		dwMasterImage2					->setMinimumSize(10,10);
		dwMasterImage2					->setMaximumSize(16777215,16777215);
		dwNGMasterPix					->setMinimumSize(10,10);
		dwNGMasterPix					->setMaximumSize(16777215,16777215);
		dwNGInspectionPix				->setMinimumSize(10,10);
		dwNGInspectionPix				->setMaximumSize(16777215,16777215);
		dwHistoryList					->setMinimumSize(10,10);
		dwHistoryList					->setMaximumSize(16777215,16777215);
		dwHistoryList->ui.twHistoryList	->setMinimumSize(10,10);
		dwHistoryList->ui.twHistoryList	->setMaximumSize(16777215,16777215);
		dwHistoryList->ui.layoutWidget	->setMinimumSize(10,10);
		dwHistoryList->ui.layoutWidget	->setMaximumSize(16777215,16777215);
		dwNGList						->setMinimumSize(10,10);
		dwNGList						->setMaximumSize(16777215,16777215);
		dwNGList->twNGList				->setMinimumSize(10,10);
		dwNGList->twNGList				->setMaximumSize(16777215,16777215);
		dwNGList->ui.layoutWidget		->setMinimumSize(10,10);
		dwNGList->ui.layoutWidget		->setMaximumSize(16777215,16777215);

//		MainFrame			->SetTitle(false);
//		dwMasterImage		->SetTitle(false);
//		dwMasterImage1		->SetTitle(false);
//		dwMasterImage2		->SetTitle(false);
//		dwNGMasterPix		->SetTitle(false);
//		dwNGInspectionPix	->SetTitle(false);
//		dwHistoryList		->SetTitle(false);
//		dwNGList			->SetTitle(false);
	}
	else{
//		MainFrame			->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwMasterImage		->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwMasterImage1		->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwMasterImage2		->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwNGMasterPix		->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwNGInspectionPix	->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwHistoryList		->setFeatures(QDockWidget::NoDockWidgetFeatures);
//		dwNGList			->setFeatures(QDockWidget::NoDockWidgetFeatures);

		MainFrame						->setMinimumSize(MainFrame						->width(),MainFrame							->height());
		MainFrame						->setMaximumSize(MainFrame						->width(),MainFrame							->height());
		MainFrame->ui.trMasterList		->setMinimumSize(MainFrame->ui.trMasterList		->width(),MainFrame->ui.trMasterList		->height());
		MainFrame->ui.trMasterList		->setMaximumSize(MainFrame->ui.trMasterList		->width(),MainFrame->ui.trMasterList		->height());
		MainFrame->ui.twMasterList		->setMinimumSize(MainFrame->ui.twMasterList		->width(),MainFrame->ui.twMasterList		->height());
		MainFrame->ui.twMasterList		->setMaximumSize(MainFrame->ui.twMasterList		->width(),MainFrame->ui.twMasterList		->height());
//		MainFrame->ui.layoutWidget		->setMinimumSize(MainFrame->ui.layoutWidget		->width(),MainFrame->ui.layoutWidget		->height());
//		MainFrame->ui.layoutWidget		->setMaximumSize(MainFrame->ui.layoutWidget		->width(),MainFrame->ui.layoutWidget		->height());
		dwMasterImage					->setMinimumSize(dwMasterImage					->width(),dwMasterImage						->height());
		dwMasterImage					->setMaximumSize(dwMasterImage					->width(),dwMasterImage						->height());
		dwMasterImage1					->setMinimumSize(dwMasterImage1					->width(),dwMasterImage1					->height());
		dwMasterImage1					->setMaximumSize(dwMasterImage1					->width(),dwMasterImage1					->height());
		dwMasterImage2					->setMinimumSize(dwMasterImage2					->width(),dwMasterImage2					->height());
		dwMasterImage2					->setMaximumSize(dwMasterImage2					->width(),dwMasterImage2					->height());
		dwNGMasterPix					->setMinimumSize(dwNGMasterPix					->width(),dwNGMasterPix						->height());
		dwNGMasterPix					->setMaximumSize(dwNGMasterPix					->width(),dwNGMasterPix						->height());
		dwNGInspectionPix				->setMinimumSize(dwNGInspectionPix				->width(),dwNGInspectionPix					->height());
		dwNGInspectionPix				->setMaximumSize(dwNGInspectionPix				->width(),dwNGInspectionPix					->height());
		dwHistoryList					->setMinimumSize(dwHistoryList					->width(),dwHistoryList						->height());
		dwHistoryList					->setMaximumSize(dwHistoryList					->width(),dwHistoryList						->height());
		dwHistoryList->ui.twHistoryList	->setMinimumSize(dwHistoryList->ui.twHistoryList->width(),dwHistoryList->ui.twHistoryList	->height());
		dwHistoryList->ui.twHistoryList	->setMaximumSize(dwHistoryList->ui.twHistoryList->width(),dwHistoryList->ui.twHistoryList	->height());
		dwHistoryList->ui.layoutWidget	->setMinimumSize(dwHistoryList->ui.layoutWidget	->width(),dwHistoryList->ui.layoutWidget	->height());
		dwHistoryList->ui.layoutWidget	->setMaximumSize(dwHistoryList->ui.layoutWidget	->width(),dwHistoryList->ui.layoutWidget	->height());
		dwNGList						->setMinimumSize(dwNGList						->width(),dwNGList							->height());
		dwNGList						->setMaximumSize(dwNGList						->width(),dwNGList							->height());
		dwNGList->twNGList				->setMinimumSize(dwNGList->twNGList				->width(),dwNGList->twNGList				->height());
		dwNGList->twNGList				->setMaximumSize(dwNGList->twNGList				->width(),dwNGList->twNGList				->height());
		dwNGList->ui.layoutWidget		->setMinimumSize(dwNGList->ui.layoutWidget		->width(),dwNGList->ui.layoutWidget			->height());
		dwNGList->ui.layoutWidget		->setMaximumSize(dwNGList->ui.layoutWidget		->width(),dwNGList->ui.layoutWidget			->height());

//		MainFrame			->SetTitle(true);
//		dwMasterImage		->SetTitle(true);
//		dwMasterImage1		->SetTitle(true);
//		dwMasterImage2		->SetTitle(true);
//		dwNGMasterPix		->SetTitle(true);
//		dwNGInspectionPix	->SetTitle(true);
//		dwHistoryList		->SetTitle(true);
//		dwNGList			->SetTitle(true);

		setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint);
		show();
	}
}

void RepairStation::chNotShowHaltToggled(bool toggled)
{
	//HALTデータを表示するかどうかのチェック
	if(toggled){
		SetNotShowHaltFlag(true);
	}
	else{
		SetNotShowHaltFlag(false);
	}
}

void RepairStation::chReverseOrderDisplayToggled(bool toggled)
{
	if(GetLotID(SType)==LangSolver.GetString(RepairStation_LS,LID_150)/*"*"*/ || GetLotID(SType)==LangSolver.GetString(RepairStation_LS,LID_151)/*"-1"*/){
		if(toggled)
			dwHistoryList->ui.twHistoryList->sortByColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_152)/*"TIM"*/),Qt::DescendingOrder);
		else
			dwHistoryList->ui.twHistoryList->sortByColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_153)/*"TIM"*/),Qt::AscendingOrder);
	}
	else{
		if(toggled)
			dwHistoryList->ui.twHistoryList->sortByColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_154)/*"Key"*/),Qt::DescendingOrder);
		else
			dwHistoryList->ui.twHistoryList->sortByColumn(HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_155)/*"Key"*/),Qt::AscendingOrder);
	}

	//リスト行のヘッダーラベルの数字も逆順対応
	SetRowHeaderLabel(toggled);
}

void RepairStation::MasterTreeRowChanged(QTreeWidgetItem *CIndex)
{
	//マスターテーブルにデータをセット
	disconnect(MainFrame->ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	MainFrame->ui.twMasterList->clearContents();
	MainFrame->ui.twMasterList->setRowCount(0);
	connect(MainFrame->ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	QSqlQuery query;
	int CID;
	if((CID=CIndex->text(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_156)/*"CATEGORYID"*/)).toInt())==-1)
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA order by MASTERCODE");
	else{
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID=? order by MASTERCODE");
		query.addBindValue(CID);
	}
	query.exec();
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			MainFrame->ui.twMasterList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			MainFrame->ui.twMasterList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<MainFrame->ui.twMasterList->columnCount();Col++){
			SetDataToTable(MainFrame->ui.twMasterList,Row,Col,query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}
}

void RepairStation::MasterListRowChanged(const QModelIndex &CIndex)
{
	QSqlQuery query;
	query.prepare(LangSolver.GetString(RepairStation_LS,LID_159)/*"select MACHINEID,TOPVIEW,DOTPERLINE,MAXLINES,PAGENUMB,LAYERNUMB from MASTERDATA where MASTERCODE=?"*/);
	query.addBindValue(MainFrame->ui.twMasterList->item(CIndex.row(),0)->text());
	query.exec();
	if(query.next()==false){
		return;
	}
///	MachineID=query.value(query.record().indexOf("MACHINEID")).toString();;
	DotPerLine=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_160)/*"DOTPERLINE"*/)).toInt();
	MaxLines=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_161)/*"MAXLINES"*/)).toInt();
	PageNumb=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_162)/*"PAGENUMB"*/)).toInt();
	LayerNumb=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_163)/*"LAYERNUMB"*/)).toInt();
}

void RepairStation::HistoryListRowChanged(const QModelIndex &CIndex)
{
	//Clear時（削除時）は何もしない
	if(CIndex.row()==-1){
		return;
	}

	iSide=Front;
	NGListFlag=false;

	//履歴リスト選択時のNGリスト表示
	int Ret=0;
	
	//更新の一時停止
	dwNGList->twNGList->setUpdatesEnabled(false);
	//データ更新中のシグナルの発信によるスロットの実行を無効化
	disconnect(dwNGList->twNGList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	//マスター画像に配置されているFキーによるNG描画ポイント削除

	if(FrontMImage!=NULL)FrontMImage->clearDrawNGPoint();
	if(BackMImage!=NULL)BackMImage->clearDrawNGPoint();
	
	//レイアウトの調整
	NGShowW=IDataUnit->NGImagePieceList[0]->width()-34;		//メモリ幅分引く(34)
	NGShowH=IDataUnit->NGImagePieceList[0]->height()-32;	//メモリ幅分引く(32)
	
	//NGリスト表示
	if(IDataUnit->MImageClassList.count()==1){
		//表側のみ
		Ret=ShowNGList(dwNGList->twNGList,
			NGCountInBoard=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_164)/*"NGP"*/))->text().toInt(),
			dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_165)/*"Key1"*/))->text().toInt(),
			dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_166)/*"Key2"*/))->text().toInt(),
			&NGFieldNames,
			NGShowW,
			NGShowH);
	}
	else{
		//裏表対応
		Ret=ShowNGList(dwNGList->twNGList,NGCountInBoard=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_167)/*"NGP"*/))->text().toInt(),dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_168)/*"Key1"*/))->text().toInt(),dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_169)/*"Key2"*/))->text().toInt(),&NGFieldNames,NGShowW,NGShowH,1);
	}
	//XMLデータのチェック結果を表示する
	ShowCheckXMLData(Ret);

	//シグナルスロット再接続
	connect(dwNGList->twNGList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(NGListRowChanged(QModelIndex,QModelIndex)));
	//更新許可
	dwNGList->twNGList->setUpdatesEnabled(true);

	if(NGCountInBoard==0){
		for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++)
			IDataUnit->MImageClassList[Cnt]->repaint();
		IDataUnit->MImagePieceList[0]->repaint();
		IDataUnit->NGImagePieceList[0]->repaint();
	}

	dwNGList->ui.leNGCount->setText(QString::number(dwNGList->twNGList->rowCount()));
	strQNO1=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_170)/*"QNO1"*/))->text().toLocal8Bit().data();
	strQNO2=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_171)/*"QNO2"*/))->text().toLocal8Bit().data();

	//TimeOver・MaxOver対応→画面全体の色を変える。OKでも色を変える
	QString strRES1=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_172)/*"RES1"*/))->text();
	QString strRES2=dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_173)/*"RES2"*/))->text();
	if(strRES1==LangSolver.GetString(RepairStation_LS,LID_174)/*"TimeOver"*/ || strRES1==LangSolver.GetString(RepairStation_LS,LID_175)/*"MaxOver"*/ || strRES2==LangSolver.GetString(RepairStation_LS,LID_176)/*"TimeOver"*/ || strRES2==LangSolver.GetString(RepairStation_LS,LID_177)/*"MaxOver"*/){
		tOKWindow.Stop();
		while(tOKWindow.isRunning()){}
		SetWindowColor(QColor(Qt::yellow));
	}
	else if((strRES1==LangSolver.GetString(RepairStation_LS,LID_178)/*"OK"*/ && strRES2.isEmpty()) || (strRES1.isEmpty() && strRES2==LangSolver.GetString(RepairStation_LS,LID_179)/*"OK"*/) || (strRES1==LangSolver.GetString(RepairStation_LS,LID_180)/*"OK"*/ && strRES2==LangSolver.GetString(RepairStation_LS,LID_181)/*"OK"*/)){
		//グラデーションで表示
		tOKWindow.Stop();
		while(tOKWindow.isRunning()){}
		QColor color(Qt::green);
		tOKWindow.SetColor(color);
		tOKWindow.start();
	}
	else{
		tOKWindow.Stop();
		while(tOKWindow.isRunning()){}
		SetWindowColorDefault();
	}

	//NGリストのエリアコードでの並び替え
	if(GetEachPieces()==true){
		dwNGList->twNGList->sortByColumn(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_182)/*"ARA"*/),Qt::AscendingOrder);
	}
	else{
		dwNGList->twNGList->sortByColumn(NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_183)/*"ARAIndex"*/),Qt::AscendingOrder);
	}

	//初期フォーカス（選択）の設定
	if(!UpdateFlg){
		if(dwNGList->twNGList->rowCount()>0)
			dwNGList->twNGList->selectRow(0);
		dwNGList->twNGList->setFocus();
	}

	//OKも表示の場合、OKからNGがある履歴に戻ると画面が更新されない現象を回避
	if(NGCountInBoard==0){
		NoNGFlg=true;
	}

	//マスター全体画像上に表示するNGポイントの追加
	for(int row=0; row < dwNGList->twNGList->rowCount(); row++){
		int side = dwNGList->twNGList->item(row, NGFieldNames.indexOf(/**/"Side"))->text().toInt();
		QColor bakColor = dwNGList->twNGList->item(row, 0)->backgroundColor();
		QStringList PosList = dwNGList->twNGList->item(row, 0)->text().split(',');
		if(ColorFKey.contains(bakColor)){
			switch(side){
			case SideType::Front:
				FrontMImage->addDrawNGPoint(PosList[0].toInt(), PosList[1].toInt(), bakColor);
				break;
			case SideType::Back:
				BackMImage->addDrawNGPoint(PosList[0].toInt(), PosList[1].toInt(), bakColor);
				break;
			default:
				break;
			}
		}
	}

	//マスター全体画面の更新
	for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
		IDataUnit->MImageClassList[Cnt]->repaint();
	}

	//履歴リスト送り表示制御
	if(GetListScrollRowCnt()>0){
		dwHistoryList->ui.twHistoryList->verticalScrollBar()->setSliderPosition(CIndex.row()-GetListScrollRowCnt()+1);
	}

	//ログデータのセット
	if(DLL_GetName!=NULL){
		if(dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_184)/*"INM"*/))==NULL){
			SetInspectionID(SType,&QString(LangSolver.GetString(RepairStation_LS,LID_185)/*"????"*/));
		}
		else{
			SetInspectionID(SType,&dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_186)/*"INM"*/))->text());
		}
		SetNGNumb(SType,dwNGList->twNGList->rowCount());

		//MaxOverの場合、メッセージを出す
		if(UpdateFlg==true){
			if(strRES1==LangSolver.GetString(RepairStation_LS,LID_187)/*"TimeOver"*/ || strRES1==LangSolver.GetString(RepairStation_LS,LID_188)/*"MaxOver"*/ || strRES2==LangSolver.GetString(RepairStation_LS,LID_189)/*"TimeOver"*/ || strRES2==LangSolver.GetString(RepairStation_LS,LID_190)/*"MaxOver"*/){
				if((Ret&0x04)==0 && (Ret&0x08)==0){
					QString MessageText;
					MessageText	=LangSolver.GetString(RepairStation_LS,LID_191)/*"LOT数"*/;
					MessageText+=QString::number(GetCurINM());
					MessageText+=LangSolver.GetString(RepairStation_LS,LID_192)/*"は\n"*/;
					MessageText+=LangSolver.GetString(RepairStation_LS,LID_193)/*"候補数過多により検査確認を終了します。\n\nOKボタンで基板を搬送します。"*/;
					DLL_SetMessageFormLabel(MessageText);
				}
				SeqControlParamData->ErrorCode|=0x80;
				SeqControlParamData->ErrorCount++;
				SeqControlParamData->ErrorIndex=23;
			}
		}

		//IsOutputLogをfalseに戻しておく（ログが書き出せるように）
		DLL_SetIsOutputLog(false);
		//基板１個前のNG情報をクリアしておく
		DLL_ClearNGInfoList();
		//直前のNGリストの行保持ワークをクリアしておく
		PrevNGRow.clear();
		//個片名称リストをクリアしておく
		NGAreaNameList[Front].clear();
		NGAreaNameList[Back].clear();
		//HD名のセット
		QString		HDName;
		QStringList	HDNameList;
		dwHistoryList->ui.twHistoryList->item(CIndex.row(),HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_194)/*"Key1"*/))->text().toInt();
		for(int i=0;(HDName=GetString(&strXML[SType],LangSolver.GetString(RepairStation_LS,LID_195)/*"<RMK>"*/,LangSolver.GetString(RepairStation_LS,LID_196)/*"</RMK>"*/,i)).isEmpty()==false;i++){
			HDNameList.append(HDName);
		}
		SetHDNameList(SType,&HDNameList);
		DLL_SetLogInfoHDNameList(GetHDNameList(SType));

		//OKの場合、、、
		if(NGCountInBoard==0 && UpdateFlg==true){
			wErrNextBS=true;
			OKWaitFlag=true;
		}
/*
		//OKの場合、即ログを出力する
		if(NGCountInBoard==0){
			DLL_SetReviewEnable(false);
			int Ret;
			//DLL_OutputLog("基板番号","キズ候補数");
			if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType)))==-1){
				SeqControlParamData->ErrorCode|=0x01;
//				QMessageBox::warning(this,tr("Error"),tr("Not complete save log."));
				return;
			}
			SeqControlParamData->ReviewResult=Ret;
            for(time_t t=time(NULL);;){
				if(time(NULL)-t>3){
					SeqControlParamData->ErrorCode|=0x04;
//					QMessageBox::warning(this,tr("Error"),tr("Review result error."));
					return;
				}
				if(SeqControlParamData->ReviewFinished==false){
					break;
				}
			}
			//Waitを置く
            for(time_t t=time(NULL);time(NULL)-t<3;){}
			SeqControlParamData->ReviewFinished=true;
			//フォームを表示
			if(DLL_IsUnloadCommentFormShow==false){
				DLL_AllCheckedFormShow();
			}
		}
*/
	}
}

void RepairStation::NGListRowChanged(const QModelIndex &CIndex,const QModelIndex &PIndex)
{
	//NG個片番号の変更を許可する
	int ColARA=NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_197)/*"ARA"*/);
	if(GetEnableNGPieceChange()==true){
		if(GetKohenNameList(SType)->count()>0){
			//コンボボックスの作成
			if(cbPieceListEditor!=NULL){
/*				//移動前のコンボボックス欄の値を取得
				if(PIndex.row()>=0){
					QString strPreItem=cbPieceListEditor->currentText();
					SetDataToTable(dwNGList->twNGList,PIndex.row(),ColARA,strPreItem);
				}
*/
				delete cbPieceListEditor;
				cbPieceListEditor=NULL;
			}
//			cbPieceListEditor=new PieceListEditor(*GetKohenNameList(SType),this);
			cbPieceListEditor=new PieceListEditor(*GetKohenNameList(SType));

			//現在の行のARAの値を取得
			QString strCurItem=LangSolver.GetString(RepairStation_LS,LID_198)/*""*/;
			QTableWidgetItem *CurItem=dwNGList->twNGList->item(CIndex.row(),ColARA);
			if(CurItem!=NULL){
				strCurItem=CurItem->text();
			}
			//コンボボックスをARA列にセット
			dwNGList->twNGList->setCellWidget(CIndex.row(),ColARA,cbPieceListEditor);
			//コンボボックスにチェックを付ける
			QStringList CurItemList=strCurItem.split(LangSolver.GetString(RepairStation_LS,LID_199)/*","*/);
			for(int i=0;i<CurItemList.count();i++){
				int Index=cbPieceListEditor->findText(CurItemList.at(i));
				cbPieceListEditor->setItemData(Index,true,Qt::CheckStateRole);
			}
			cbPieceListEditor->setEditText(strCurItem);
			connect(cbPieceListEditor,SIGNAL(editTextChanged(QString)),this,SLOT(PieceListEditorTextChanged(QString)));
		}
	}

	//NG赤丸ブリンクスレッド停止
	tNGBlink.ChangeFlag=true;

	//NG画像の表示
	if(IDataUnit->NGImagePieceList[0]->hasImage()==true){
		IDataUnit->NGImagePieceList[0]->delImage();
	}
	IDataUnit->NGImagePieceList[0]->AddImage(new QImage());

	int Index,CIndexRow;
	if(dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_200)/*"RowIndex"*/))==NULL){
		return;
	}
	int RowIndex=CIndexRow=dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_200)/*"RowIndex"*/))->text().toInt();
	if(RowIndex>=(Index=SumFRowCnt+SumBRowCntInImage)){
		RowIndex-=Index;
	}
	else if(RowIndex>=SumFRowCntInImage && RowIndex<SumFRowCnt){
		RowIndex-=SumFRowCntInImage;
	}
//	int ImageX,ImageY,ImageW,ImageH;
//	bool GetNG=GetNGImage(dwNGList->twNGList,Row,&NGFieldNames,IDataUnit->NGImagePieceList[0]->Image,ImageX,ImageY,ImageW,ImageH);
	bool GetNG=GetNGImage(dwNGList->twNGList,CIndex.row(),RowIndex,&NGFieldNames,IDataUnit->NGImagePieceList[0]->GetImage(),ImageX,ImageY,ImageW,ImageH);
	IDataUnit->NGImagePieceList[0]->SetNGImage();
	IDataUnit->NGImagePieceList[0]->SetNGBrightness(Brightness);
	IDataUnit->NGImagePieceList[0]->SetNGImageExist(GetNG);
	IDataUnit->NGImagePieceList[0]->SetImageTopLeftPos(ImageX, ImageY);

	int iNGP=dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_201)/*"NGP"*/))->text().toInt();
	int CountNGP=0;

	//マスター個片画像の位置(X,Y)座標の計算（カメラ毎）、アライメント補正ズレ量
	if(NGPTagList[iSide]!=NULL){
		for(XMLTagAttr *TA=NGPTagList[iSide][iNGP]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
			if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_202)/*"MX"*/)==0)
				MX=-TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_203)/*"MY"*/)==0)
				MY=-TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_204)/*"HX"*/)==0)
				HX=-TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_205)/*"HY"*/)==0)
				HY=-TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_206)/*"PG"*/)==0)
				SetPG(TA->iAttrData);
		}
		IDataUnit->NGImagePieceList[0]->SetCorrectionX(MX+HX);
		IDataUnit->NGImagePieceList[0]->SetCorrectionY(MY+HY);
	}
	else{
		IDataUnit->NGImagePieceList[0]->SetCorrectionX(0);
		IDataUnit->NGImagePieceList[0]->SetCorrectionY(0);
	}

	//NG画像の拡大率の設定
	double W,H;
	double Scaled=(W=(double)IDataUnit->NGImagePieceList[0]->GetCanvasWidth()/ImageW)<(H=(double)IDataUnit->NGImagePieceList[0]->GetCanvasHeight()/ImageH) ? W : H;
	if(GetNG){
		ImageX+=IDataUnit->MImageClassList[iSide]->ImageList[GetPG()]->OrgOffsetX+MX+HX;
		ImageY+=IDataUnit->MImageClassList[iSide]->ImageList[GetPG()]->OrgOffsetY+MY+HY;
		IDataUnit->NGImagePieceList[0]->SetZoomRate(Scaled);
	}
	else{
		IDataUnit->NGImagePieceList[0]->SetZoomRate(IDataUnit->MImageClassList[iSide]->ImgRateCount);
	}

	//NG赤丸の表示
	if(iSide==Front){
//		IDataUnit->NGImagePieceList[0]->NGList=&NGPointList[iSide][CIndex.row()];
//		IDataUnit->NGImagePieceList[0]->NGList=&NGPList[iSide][CIndex.row()];
		if(CIndexRow<SumFRowCntInImage){
			IDataUnit->NGImagePieceList[0]->SetNGList(NGPList[iSide][RowIndex]);
		}
		else{
			IDataUnit->NGImagePieceList[0]->SetNGList(*GetNGPListForVRS(iSide,RowIndex));
		}
	}
	else{
//		IDataUnit->NGImagePieceList[0]->NGList=&NGPointList[iSide][CIndex.row()-SumFRowCnt];
//		IDataUnit->NGImagePieceList[0]->NGList=&NGPList[iSide][CIndex.row()-SumFRowCnt];
		if(CIndexRow<(SumFRowCnt+SumBRowCntInImage)){
			IDataUnit->NGImagePieceList[0]->SetNGList(NGPList[iSide][RowIndex-SumFRowCnt]);
		}
		else{
			IDataUnit->NGImagePieceList[0]->SetNGList(*GetNGPListForVRS(iSide,RowIndex));
		}
	}
	NGListFlag=true;

	//NG赤丸ブリンクスレッド開始
//	while(!tNGBlink.TheadEnd){}
//	tNGBlink.start();


	//現在の個片名称をマスター全体画像に反映
	QString CurrentPieceName;
	IDataUnit->MImageClassList[iSide]->SetPieceName(CurrentPieceName=dwNGList->twNGList->item(CIndex.row(),ColARA)->text());

	//描画トリガ
	if(iSide==Front){
		emit SignalFMMouseLDown(ImageX>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageY>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageW>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageH>>IDataUnit->MImageClassList[iSide]->ImgRate);
	}
	else{
		emit SignalBMMouseLDown(ImageX>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageY>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageW>>IDataUnit->MImageClassList[iSide]->ImgRate,ImageH>>IDataUnit->MImageClassList[iSide]->ImgRate);
	}

	//NG画像がない場合、マスター個片画像と同じ画像を出力
	QPalette P;
	if(!GetNG){
//		*IDataUnit->NGImagePieceList[0]->Image=IDataUnit->MImagePieceList[0]->Image;
		IDataUnit->NGImagePieceList[0]->delImage();
		//NG表示ウィンドウのタイトルに現物画像と表示し赤くする
		P.setColor(QPalette::Base,QColor(Qt::red));
//		dwNGInspectionPix->leNGInspectionPixTitle->setText(tr("Actual Image"));
		dwNGInspectionPix->leNGInspectionPixTitle->setText(LangSolver.GetString(DockMasterPiece_LS,LID_53)/*"Master Image"*/);
		dwNGInspectionPix->leNGInspectionPixTitle->setPalette(P);
	}
	else{
		//画面の表示を元に戻す
		P.setColor(QPalette::Base,QColor(Qt::white));
//		dwNGInspectionPix->leNGInspectionPixTitle->setText(tr("NG Image"));
		dwNGInspectionPix->leNGInspectionPixTitle->setText(LangSolver.GetString(DockNGPiece_LS,LID_54)/*"NG Image"*/);
		dwNGInspectionPix->leNGInspectionPixTitle->setPalette(P);
	}

	//描画設定
	IDataUnit->NGImagePieceList[0]->ZoomDraw(-ImageX,-ImageY,Scaled);

	//OKも表示さしている時に、OKからNGがある履歴に戻ると画面が更新されない現象を回避
	if(NoNGFlg){
		for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
			IDataUnit->MImageClassList[Cnt]->repaint();
		}
		IDataUnit->MImagePieceList[0]->repaint();
		NoNGFlg=false;
	}
	//表面⇔裏面に切り替わった時、再描画
	if(iSide!=iSideOld){
		IDataUnit->MImageClassList[iSideOld]->wRectClear();
		IDataUnit->MImageClassList[iSideOld]->repaint();
		iSideOld=iSide;
	}

	//NGリスト送り表示制御
	if(GetListScrollRowCnt()>0){
		dwNGList->twNGList->verticalScrollBar()->setSliderPosition(CIndex.row()-GetListScrollRowCnt()+1);
	}

	//チェック済情報をXMLに書き出す
	if(dwNGList->twNGList->currentItem()==NULL){
		return;
	}
	if(dwNGList->twNGList->currentItem()->backgroundColor().value()==0){
		//選択された行をチェック済色にする
		SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),twNGListCheckColor);

		int RowCount=dwNGList->twNGList->rowCount();
		int Row;
		for(Row=RowCount-1;Row>=0;Row--){
			if(dwNGList->twNGList->item(Row,0)->backgroundColor().value()==0){
				break;
			}
		}
		if(Row==-1){
			QString sRetTag;
			if(!CheckedXML(sRetTag,ErrMsg)){
				//選択された行をXML書出しエラー色にする
				SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),QColor(255,180,180));
			}
			else{
				QString UpXML=LangSolver.GetString(RepairStation_LS,LID_207)/*""*/;
				SetRetXMLData(Insert,&UpXML,&sRetTag);
			}
		}
	}

	//PluginDLL対応
	if(DLL_GetName!=NULL){
		//ログデータのセット
//		SetKohenNo		(SType,&CurrentPieceName);
		SetKohenNo		(SType,&dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_208)/*"wARA"*/))->text());
		SetRealKohenNo	(SType,&CurrentPieceName);
		SetNGNo			(SType,dwNGList->twNGList->currentRow());
		SetPCNo			(SType,GetPG());
		SetNGPointX		(SType,&GetString(&(dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_209)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_210)/*""*/,LangSolver.GetString(RepairStation_LS,LID_211)/*","*/));
		SetNGPointY		(SType,&GetString(&(dwNGList->twNGList->item(CIndex.row(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_212)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_213)/*", "*/,LangSolver.GetString(RepairStation_LS,LID_214)/*""*/));
		if(GetPG()<3){
			dwNGInspectionPix->leNGInspectionPixTitle->setText(LangSolver.GetString(RepairStation_LS,LID_215)/*"PC 1"*/);
		}
		else{
			dwNGInspectionPix->leNGInspectionPixTitle->setText(LangSolver.GetString(RepairStation_LS,LID_216)/*"PC 2"*/);
		}
	}
}

void RepairStation::Next()
{
	if(dwNGList->twNGList->hasFocus()){
		if(GetNextCheck()==true || GetEnterCheck()==true){
			int RowCnt=dwNGList->twNGList->rowCount();
			for(int Row=0;Row<RowCnt;Row++){
				if(dwNGList->twNGList->item(Row,0)->backgroundColor().value()==0){
					return;
				}
			}
		}
		if(dwHistoryList->ui.twHistoryList->currentIndex().row()+1<dwHistoryList->ui.twHistoryList->rowCount()){
			dwHistoryList->ui.twHistoryList->selectRow(dwHistoryList->ui.twHistoryList->currentIndex().row()+1);
		}
	}
}

void RepairStation::Previous()
{
	if(dwNGList->twNGList->hasFocus()){
		if(dwHistoryList->ui.twHistoryList->currentIndex().row()-1>=0){
			dwHistoryList->ui.twHistoryList->selectRow(dwHistoryList->ui.twHistoryList->currentIndex().row()-1);
		}
	}
}

void RepairStation::SlotKeyLeft()
{
	if(dwNGList->twNGList->hasFocus()){
		if(GetNextCheck()==false){
			Previous();
		}
	}
}

void RepairStation::SlotKeyRight()
{
	if(dwNGList->twNGList->hasFocus()){
		if(GetNextCheck()==false){
			Next();
		}
	}
}

void RepairStation::SlotKeyEnter()
{
	if(GetEnterCheck()==true){
		//履歴確認済みの意味で赤表示に
		SetColorToTable(dwHistoryList->ui.twHistoryList,dwHistoryList->ui.twHistoryList->currentIndex().row(),twNGListCheckColor);
		Next();
	}
}

void RepairStation::SlotKeyInsert()
{
	//NG画像の保存
	SaveImageFlag=true;
	dwNGInspectionPix->repaint();

	//NGリストの次の行に移動する
	if(dwNGList->twNGList->currentRow()+1<dwNGList->twNGList->rowCount())
		dwNGList->twNGList->selectRow(dwNGList->twNGList->currentRow()+1);
}

void RepairStation::SlotKeyInsertAll()
{
	//NG画像の保存
	int ColInsID=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_217)/*"EID"*/);
	QString InspectID;
	if(dwHistoryList->ui.twHistoryList->rowCount()>0)
		InspectID=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColInsID)->text();
	if(SaveNGImage(InspectID))
		QMessageBox::information(this,LangSolver.GetString(RepairStation_LS,LID_218)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_219)/*"Complete save NG image all."*/);
	else
		QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_220)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_221)/*"Not complete save NG image!"*/);
}

void RepairStation::FMasterSlotOnPaint(QPainter &Pnt)
{
	if(IDataUnit->MImageClassList[Front]->ImageList.count()==0)
		return;
	IDataUnit->MImageClassList[Front]->SetWholeImage(IDataUnit->MImageClassList[Front]->width(),IDataUnit->MImageClassList[Front]->height());
	IDataUnit->MImageClassList[Front]->SetExpand();
	IDataUnit->MImageClassList[Front]->DrawPaint(Pnt);
	//Show piece information(XML)
	IDataUnit->MImageClassList[Front]->DrawPieceInfo(Pnt,PieceInfoDataCount[Front],PieceInfoDataList[Front],QColor(GetPieceColorString()),&NGAreaNameList[Front],GetKohenNameList(Front));

	if(NGCountInBoard==0)
		return;
	if(dwNGList->twNGList->rowCount()>0){
		IDataUnit->MImageClassList[Front]->SetPieceDraw	(IDataUnit->MImagePieceList[0]->GetCanvasWidth(),IDataUnit->MImagePieceList[0]->GetCanvasHeight(),IDataUnit->MImagePieceList[0]->GetZoomRate());
//		IDataUnit->MImageClassList[Front]->DrawNGDot	(Pnt,dwNGList->twNGList,NGFieldNames.indexOf("Side"),NGPList[Front], SumFRowCnt);
//		IDataUnit->MImageClassList[Front]->DrawNGDot	(Pnt,dwNGList->twNGList,NGFieldNames.indexOf("Side"),NGPList[Front], SumFRowCnt, citemList);
		IDataUnit->MImageClassList[Front]->DrawNGDot	(Pnt,dwNGList->twNGList,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_222)/*"Side"*/),NGPList[Front],&NGPListForVRS[Front],SumFRowCntInImage, citemList);
		if(iSide==Front)
			IDataUnit->MImageClassList[Front]->DrawPieceRect(Pnt);
	}
}

void RepairStation::BMasterSlotOnPaint(QPainter &Pnt)
{
	if(IDataUnit->MImageClassList[Back]->ImageList.count()==0)
		return;
	IDataUnit->MImageClassList[Back]->SetWholeImage(IDataUnit->MImageClassList[Back]->width(),IDataUnit->MImageClassList[Back]->height());
	IDataUnit->MImageClassList[Back]->SetExpand();
	IDataUnit->MImageClassList[Back]->DrawPaint(Pnt);
	//Show piece information(XML)
	IDataUnit->MImageClassList[Back]->DrawPieceInfo(Pnt,PieceInfoDataCount[Back],PieceInfoDataList[Back],QColor(GetPieceColorString()),&NGAreaNameList[Back],GetKohenNameList(Back));

	if(dwNGList->twNGList->rowCount()>0){
		IDataUnit->MImageClassList[Back]->SetPieceDraw	(IDataUnit->MImagePieceList[0]->GetCanvasWidth(),IDataUnit->MImagePieceList[0]->GetCanvasHeight(),IDataUnit->MImagePieceList[0]->GetZoomRate());
//		IDataUnit->MImageClassList[Back]->DrawNGDot		(Pnt,dwNGList->twNGList,NGFieldNames.indexOf("Side"),NGPList[Back],SumBRowCnt);
//		IDataUnit->MImageClassList[Back]->DrawNGDot		(Pnt,dwNGList->twNGList,NGFieldNames.indexOf("Side"),NGPList[Back],SumBRowCnt, citemList);
		IDataUnit->MImageClassList[Back]->DrawNGDot		(Pnt,dwNGList->twNGList,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_223)/*"Side"*/),NGPList[Back],&NGPListForVRS[Back],SumBRowCntInImage, citemList);
		if(iSide==Back)
			IDataUnit->MImageClassList[Back]->DrawPieceRect	(Pnt);
	}
}

//SignalOnMouseLDownのスロット
void RepairStation::SlotOnMouseLDown(int X,int Y,MasterImage *MImageClass)
{
	if(IDataUnit->MImageClassList.count()==0)
		return;
	if(MImageClass->ImageList.count()==0)
		return;

	IDataUnit->MImagePieceList[0]->SetZoomRate(MImageClass->ImgRateCount);
	IDataUnit->MImagePieceList[0]->ZoomDraw(-(X<<MImageClass->ImgRate),-(Y<<MImageClass->ImgRate),1);
}

//マスター個片画像の描画
void RepairStation::SlotOnMPiecePaint(QPainter &Pnt)
{
	if(IDataUnit->MImageClassList.count()==0)
		return;
	if(IDataUnit->MImageClassList[0]->ImageList.count()==0)
		return;
	if(NGCountInBoard==0){
		IDataUnit->MImagePieceList[0]->DrawNoPaint(Pnt);
		return;
	}

	IDataUnit->MImagePieceList[0]->DrawPaint(Pnt,IDataUnit,iSide);
}

void RepairStation::SlotOnNGPiecePaint(QPainter &Pnt)
{
	//描画
	NGPiecePaint(Pnt);

	if(SaveImageFlag==true){
		int ColInsID=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_224)/*"EID"*/);
		QString InspectID;
		if(dwHistoryList->ui.twHistoryList->rowCount()<=0)
			return;
		InspectID=dwHistoryList->ui.twHistoryList->item(dwHistoryList->ui.twHistoryList->currentRow(),ColInsID)->text();
		QString strDir;
		if(GetSaveDirNGImage()==LangSolver.GetString(RepairStation_LS,LID_225)/*""*/){
			strDir=GetMasterDir() + LangSolver.GetString(RepairStation_LS,LID_226)/*"/"*/ + LangSolver.GetString(RepairStation_LS,LID_227)/*"MID-"*/ + GetMasterID(SType) + LangSolver.GetString(RepairStation_LS,LID_228)/*"/"*/ + LangSolver.GetString(RepairStation_LS,LID_229)/*"Lot-"*/ + GetLotName(SType);
		}
		else{
			strDir=GetSaveDirNGImage() + LangSolver.GetString(RepairStation_LS,LID_230)/*"/"*/ + QDate::currentDate().toString(LangSolver.GetString(RepairStation_LS,LID_231)/*"yyyyMMdd"*/) + LangSolver.GetString(RepairStation_LS,LID_232)/*"/"*/ + LangSolver.GetString(RepairStation_LS,LID_233)/*"MID-"*/ + GetMasterID(SType) + LangSolver.GetString(RepairStation_LS,LID_234)/*"/"*/ + LangSolver.GetString(RepairStation_LS,LID_235)/*"Lot-"*/ + GetLotName(SType);
		}
		QDir Dir;
		Dir.mkpath(strDir);
		QString strSaveNGPath(strDir + LangSolver.GetString(RepairStation_LS,LID_236)/*"/"*/ + InspectID.rightJustified(3,'0') + LangSolver.GetString(RepairStation_LS,LID_237)/*"_"*/ + QString::number(dwNGList->twNGList->currentRow()).rightJustified(3,'0') + LangSolver.GetString(RepairStation_LS,LID_238)/*".jpg"*/);

		QImage *image=new QImage(ImageW,ImageH,QImage::Format_RGB32);
		QPainter painter(image);
		NGPiecePaint(painter);
		if(!image->save(strSaveNGPath,LangSolver.GetString(RepairStation_LS,LID_239)/*"JPG"*/))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_240)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_241)/*"Not complete save NG image!"*/);
		SaveImageFlag=false;
//		delete image;
	}
/*
	if(IDataUnit->NGImagePieceList.count()==0)
		return;
	if(IDataUnit->NGImagePieceList[0]->NGList==NULL)
		return;
	if(NGCountInBoard==0){
		IDataUnit->NGImagePieceList[0]->DrawNoPaint(Pnt);
		return;
	}

	IDataUnit->NGImagePieceList[0]->DrawPaint(Pnt,IDataUnit,iSide);
	IDataUnit->NGImagePieceList[0]->DrawNGPoint(Pnt,MaxX,MinX,MaxY,MinY, citemList);

	//チェック済情報をXMLに書き出す
	if(dwNGList->twNGList->currentItem()==NULL)
		return;
	if(dwNGList->twNGList->currentItem()->backgroundColor().value()==0){
		QString sRetTag;
		if(!CheckedXML(sRetTag,ErrMsg)){
			//選択された行をXML書出しエラー色にする
			SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),QColor(255,180,180));
			return;
		}
		//選択された行をチェック済色にする
		SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),twNGListCheckColor);
		QString UpXML="";
		SetRetXMLData(Insert,&UpXML,&sRetTag);
	}
*/
}

void RepairStation::NGPiecePaint(QPainter &Pnt)
{
	if(IDataUnit->NGImagePieceList.count()==0){
		return;
	}
	if(NGCountInBoard==0){
		IDataUnit->NGImagePieceList[0]->DrawNoPaint(Pnt);
		return;
	}
	if(NGListFlag==false){
		return;
	}

	//背景の描画
	if(IDataUnit->MImageClassList.count()>1){
		Pnt.fillRect(0,0,IDataUnit->NGImagePieceList[0]->GetCanvasWidth(),IDataUnit->NGImagePieceList[0]->GetCanvasHeight(),NowFBColor);
	}

//	IDataUnit->NGImagePieceList[0]->DrawPaint(Pnt);
	IDataUnit->NGImagePieceList[0]->DrawPaint(Pnt,IDataUnit,iSide);
//	IDataUnit->NGImagePieceList[0]->DrawNGPoint(Pnt,MaxX,MinX,MaxY,MinY);
	IDataUnit->NGImagePieceList[0]->DrawNGPoint(Pnt,MaxX,MinX,MaxY,MinY, citemList);
	IDataUnit->NGImagePieceList[0]->DrawPieceLine(Pnt,PieceInfoDataCount[SType],PieceInfoDataList[SType],GetKohenNameList(SType),IDataUnit->MImageClassList[SType]);
/*
	//チェック済情報をXMLに書き出す
	if(dwNGList->twNGList->currentItem()==NULL){
		return;
	}
	if(dwNGList->twNGList->currentItem()->backgroundColor().value()==0){
		QString sRetTag;
		if(!CheckedXML(sRetTag,ErrMsg)){
			//選択された行をXML書出しエラー色にする
			SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),QColor(255,180,180));
			return;
		}
		//選択された行をチェック済色にする
		SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),twNGListCheckColor);
		QString UpXML="";
		SetRetXMLData(Insert,&UpXML,&sRetTag);
	}
*/
}

void RepairStation::ShowCheckXMLData(int Ret)
{
	if(DLL_GetName==NULL){
		return;
	}

	//XMLデータのチェック結果を表示する
	if(Ret!=0){
		QString MessageText;
		if((Ret&0x04)!=0){
			MessageText	=LangSolver.GetString(RepairStation_LS,LID_242)/*"LOT数"*/;
			MessageText+=QString::number(GetPreINM());
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_243)/*"が続きました。\n\n"*/;
			SeqControlParamData->ErrorIndex=12;
		}
		else if((Ret&0x08)!=0){
			MessageText	=LangSolver.GetString(RepairStation_LS,LID_244)/*"LOT数"*/;
			MessageText+=QString::number(GetPreINM());
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_245)/*"の次に"*/;
			MessageText+=QString::number(GetCurINM());
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_246)/*"が来ました。\n\n"*/;
			SeqControlParamData->ErrorIndex=13;
		}
		if((Ret&0x10)!=0){
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_247)/*"LOT数"*/;
			MessageText+=QString::number(GetPreINM());
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_248)/*"と"*/;
			MessageText+=QString::number(GetCurINM());
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_249)/*"の検査結果が同じです！\n\nOKボタンで異常を発生します。"*/;
			SeqControlParamData->ErrorIndex=14;
		}
		else if((Ret&0x20)!=0){
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_250)/*"NG候補画像を全て読込めませんでした！\n検査PC側で保存出来ていない可能性があります\n\nOKボタンで異常を発生します。"*/;
			SeqControlParamData->ErrorIndex=15;
		}
		else{
			MessageText+=LangSolver.GetString(RepairStation_LS,LID_251)/*"OKボタンで画面を閉じます。"*/;
			SeqControlParamData->ErrorIndex=16;
		}
		DLL_SetMessageFormLabel(MessageText);
		SeqControlParamData->ErrorCode|=Ret;
		SeqControlParamData->ErrorCount++;
	}
}

//履歴リストにNGとされた個片番号を記述する
void RepairStation::ShowNGAreaNameList()
{
/*	int Col=HFieldNames.indexOf("NG Area");
	QSet<QString> Set=QSet<QString>::fromList(NGAreaNameList[SType]);
	QStringList List=Set.toList();
	List.sort();
	SetDataToTable(dwHistoryList->ui.twHistoryList,0,Col,List.join(","));
*/
	int Col=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_252)/*"NG Area"*/);
	QStringList wNGAreaNameList;
	for(int i=0;i<NGAreaNameList[SType].count();i++){
		if(wNGAreaNameList.contains(NGAreaNameList[SType][i])==false){
			wNGAreaNameList.append(NGAreaNameList[SType][i]);
		}
	}
	SetDataToTable(dwHistoryList->ui.twHistoryList,0,Col,wNGAreaNameList.join(LangSolver.GetString(RepairStation_LS,LID_253)/*","*/));
}

//void RepairStation::SlotOnMouseLDrag(int X,int Y,int W,int H)
void RepairStation::SlotOnMouseLDrag(int X,int Y,int W,int H,MasterImage *MImageClass)
{
	int qX,qY,qW,qH;
	double Scaled,WScaled,HScaled;
	if((WScaled=(double)MImageClass->width()/W)<(HScaled=(double)MImageClass->height()/H)){
		Scaled=WScaled;
		qW=W;
		qH=MImageClass->height()/Scaled;
		qX=X;
		qY=Y-((qH-H)>>1);
	}
	else{
//		Scaled=(double)IDataUnit->MImageClassList[0]->height()/H;
		Scaled=HScaled;
//		qW=IDataUnit->MImageClassList[0]->width()/Scaled;
		qW=MImageClass->width()/Scaled;
		qH=H;
		qX=X-((qW-W)>>1);
		qY=Y;
	}
	MImageClass->movx=-qX;
	MImageClass->movy=-qY;
	MImageClass->ZoomRate=Scaled;
	MImageClass->SetMAreaSize(qW,qH);
	MImageClass->SetWholeImage(MImageClass->width(),MImageClass->height());

	MImageClass->repaint();
}

//void RepairStation::SlotOnMouseRClick()
void RepairStation::SlotOnMouseRClick(MasterImage *MImageClass)
{
//	IDataUnit->MImageClassList[0]->movx=0;
//	IDataUnit->MImageClassList[0]->movy=0;
//	IDataUnit->MImageClassList[0]->SetMAreaSize(InitW,InitH);
//	IDataUnit->MImageClassList[0]->SetWholeImage(IDataUnit->MImageClassList[0]->width(),IDataUnit->MImageClassList[0]->height());
//	IDataUnit->MImageClassList[0]->SetExpand();
//	IDataUnit->MImageClassList[0]->repaint();
	MImageClass->movx=0;
	MImageClass->movy=0;
	MImageClass->SetMAreaSize(InitW,InitH);
	MImageClass->SetWholeImage(MImageClass->width(),MImageClass->height());
	MImageClass->SetExpand();
	MImageClass->repaint();
}

void RepairStation::SlotOnMouseLClick(int x, int y, MasterImage *MImageClass)
{
	int gx, gy;
	int rowMax = dwNGList->twNGList->rowCount();
	QList<QPair<int, QPoint> > list;

	//クリック元が表か裏を判定
	int TargetSide;
	if(MImageClass==FrontMImage){
		TargetSide = SideType::Front;
	}else if(MImageClass==BackMImage){
		TargetSide = SideType::Back;
	}else{
		return;
	}

	qDebug() << "(x,y) = (" << x << "," << y << ")";

	//対応する面のデータを取得
	for(int row=0; row<dwNGList->twNGList->rowCount(); row++){
		int side = dwNGList->twNGList->item(row, NGFieldNames.indexOf(/**/"Side"))->text().toInt();
		if(side==TargetSide){
			QStringList PosStrList = dwNGList->twNGList->item(row, NGFieldNames.indexOf(/**/"X, Y"))->text().split(',');
			QPair<int, QPoint> pair;
			pair.first = row;
			pair.second = QPoint(PosStrList[0].toInt(), PosStrList[1].toInt());
			list.append(pair);
		}
	}

	if(list.size()==0)return;

	//一番近いポイントを取得
	int nearPosRow=-1;
	int nearPosLen=7;
	for(int i=0; i<list.size(); i++){
		int gx, gy;
		MImageClass->GetUniverseToCanvas(list[i].second.x() + MImageClass->movx, list[i].second.y() + MImageClass->movy, gx, gy);
		qDebug() << QString("%1:(gx,gy)=(%2,%3)").arg(i).arg(gx).arg(gy).toLocal8Bit();
		int len = abs(gx-x)+abs(gy-y);
		if( len <= nearPosLen ){
			nearPosLen = len;
			nearPosRow = list[i].first;
		}
	}

	//なければ終了
	if(nearPosRow==-1)return;

	//NGリストの移動
	dwNGList->twNGList->setCurrentCell(nearPosRow, dwNGList->twNGList->currentColumn());
}

void RepairStation::SlotNGRepaint(bool NGVisibled)
{
	IDataUnit->NGImagePieceList[0]->NGPointVisible=NGVisibled;
	IDataUnit->NGImagePieceList[0]->repaint();
}

//void RepairStation::SlotOKRepaint(int r,int g,int b)
void RepairStation::SlotOKRepaint(QColor RGB)
{
//	SetWindowColor(QColor(r,g,b));
	SetWindowColor(RGB);
}

void RepairStation::SlotIsChanged()
{
	//SeqControlParamDataがnewされるまでNULLなのでチェック
	if(SeqControlParamData==NULL){
		return;
	}

	//メッセージワーク
	QString strText=LangSolver.GetString(RepairStation_LS,LID_254)/*""*/;

	//フラグの退避ワーク
	bool TempFlag;

	//排出コメント表示要求信号
	if(SeqControlParamData->UnloadDone==true){
		//排出コメントフォームを表示
		DLL_UnloadCommentFormShow();
		//フォームを閉じる
		DLL_AllCheckedFormClose();
		SeqControlParamData->UnloadDone=false;
	}

	//排出コメントClose要求信号
	if(SeqControlParamData->UnloadCloseDone==true){
		//排出コメントフォームを閉じる
		DLL_UnloadCommentFormClose();
		DLL_SetReviewEnable(true);
		SeqControlParamData->UnloadCloseDone=false;
	}

	//PLCロットズレ検出信号
	if(SeqControlParamData->MacIDMismatch==true){
		//メッセージを出す
		strText=LangSolver.GetString(RepairStation_LS,LID_255)/*"LOTズレを検出しました！"*/;	//とりあえず日本語で表示させる
		QPalette palette;
		palette.setColor(QPalette::WindowText,QColor(Qt::black));
		palette.setColor(QPalette::Background,QColor(Qt::yellow));
		MainFrame->ui.lbMessage->setPalette(palette);
		MainFrame->ui.lbMessage	->setText(strText);
		MainFrame->ui.lbMessage	->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_256)/*"Helvetica"*/,20));
	}
	else{
		QPalette palette;
		palette.setColor(QPalette::Background,MainFrame->ui.lbLotName->palette().color(QPalette::Background));
		MainFrame->ui.lbMessage->setPalette(palette);
	}

	//異常発生信号
	if((TempFlag=SeqControlParamData->MacEmergency)==true){
/////////////////////↓A-20091106/////////////////////
		if(SeqControlParamData->MacErrorCode==1){
			if(DLL_GetReviewEnable()==true){
				wReviewEnableFlag=true;
			}
			DLL_SetReviewEnable(false);
			//エラーフォームを表示
			DLL_ErrorFormShow(1);
			wMacEmergency	=TempFlag;
			wMacEmgRestart	=TempFlag;
			//メッセージを出す
			if(strText.isEmpty()==true){
				QPalette palette;
				palette.setColor(QPalette::WindowText,QColor(Qt::green));
				MainFrame->ui.lbMessage->setPalette(palette);
//				strText+="次の検査結果の更新待ちです。\nしばらくお待ち下さい。";
				strText=LangSolver.GetString(RepairStation_LS,LID_257)/*"待機中"*/;
				MainFrame->ui.lbMessage->setText(strText);		//とりあえず日本語で表示させる
				MainFrame->ui.lbMessage->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_258)/*"Helvetica"*/,50));
			}
		}
		else{
/////////////////////↑A-20091106/////////////////////
			//フォームを閉じる
			if(wMacEmgRestart==true){	//A-20091106
				DLL_ErrorFormClose();	//A-20091106 一旦エラーフォームも閉じる
			}							//A-20091106
			DLL_AllCheckedFormClose();
			DLL_UnloadCommentFormClose();
			DLL_PreNext(true);
			DLL_OKCheckFormClose();
			DLL_MessageFormClose();
			DLL_SetReviewEnable(false);
			//エラーフォームを表示
//			DLL_ErrorFormShow();		//D-20091106
			DLL_ErrorFormShow(0);		//A-20091106
			wMacEmergency=TempFlag;
			wMacEmgRestart=false;		//A-20091106
			//メッセージを出す
			if(strText.isEmpty()==true){
				QPalette palette;
				palette.setColor(QPalette::WindowText,QColor(Qt::green));
				MainFrame->ui.lbMessage->setPalette(palette);
//				strText+="次の検査結果の更新待ちです。\nしばらくお待ち下さい。";
				strText=LangSolver.GetString(RepairStation_LS,LID_259)/*"待機中"*/;
				MainFrame->ui.lbMessage->setText(strText);		//とりあえず日本語で表示させる
				MainFrame->ui.lbMessage->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_260)/*"Helvetica"*/,50));
			}
			SeqControlParamData->ErrorCode=0;	//エラーコードをクリアさせる
			FlagPreNextDoubleOK=false;
			FlagPreNextDoubleNG=false;
		}	//A-20091106
	}
	else if(wMacEmergency==true){
		DLL_ErrorFormClose();
		wMacEmergency=false;
		if(wMacEmgRestart==true){
			if(wReviewEnableFlag==true){	//A-20091106
				DLL_SetReviewEnable(true);	//A-20091106
			}								//A-20091106
		}									//A-20091106
		else{								//A-20091106
			FirstUpdateFlag=true;
		}									//A-20091106
		wReviewEnableFlag=false;			//A-20091106
	}

	//ログ書き出し後は何もしない
	if(DLL_IsOutputLog()==true){
		if(strText.isEmpty()==true){
			QPalette palette;
			palette.setColor(QPalette::WindowText,QColor(Qt::green));
			MainFrame->ui.lbMessage->setPalette(palette);
			strText=LangSolver.GetString(RepairStation_LS,LID_261)/*"待機中"*/;
			MainFrame->ui.lbMessage->setText(strText);		//とりあえず日本語で表示させる
			MainFrame->ui.lbMessage->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_262)/*"Helvetica"*/,50));
		}
		MainFrame->ui.leLotCount->setEchoMode(QLineEdit::Normal);
		return;
	}

	//ソフトエラー検出の場合
	int Ret;
	if((Ret=SeqControlParamData->ErrorCode)!=0){
		if(DLL_IsAllCheckedFormShow()==false && DLL_IsUnloadCommentFormShow()==false && DLL_IsErrorFormShow()==false){
			//0x01：ログファイル(csv)の保存に失敗
			//0x02：NG候補画像の保存に失敗
			//0x04：INMが同じ
			//0x08：INMが飛んだ
			//0x10：検査結果が同じ
			//0x20：NG候補画像が全て読込めない
			//0x40：検査結果を全て読込めない
			//0x80：MaxOver判定
			if((Ret&0x80)!=0 && ((Ret&0x04)!=0 || (Ret&0x08)!=0)){
				DLL_MessageFormShow(false);
			}
			else if((Ret&0x80)!=0){
				DLL_SetMessageForm(QColor(Qt::white),QColor(Qt::black));
				DLL_MessageFormShow(false);
			}
			else if((Ret&0x01)!=0 || (Ret&0x02)!=0 || (Ret&0x10)!=0 || (Ret&0x20)!=0 || (Ret&0x40)!=0 || (Ret&0x80)!=0){
				DLL_MessageFormShow(true);
			}
			else{
				DLL_MessageFormShow(false);
			}
			//OKボタン
			if((TempFlag=SeqControlParamData->ErrNextBS)!=wErrNextBS){
				if(TempFlag==true){
					DLL_MessageFormClose();
					//0x80：MaxOver判定の場合、ログ（csv）だけを出力して基板を搬送させる
					if((Ret&0x80)!=0){
						if((Ret&0x04)!=0 || (Ret&0x08)!=0){
							if((Ret&0x04)!=0){
								SeqControlParamData->ErrorCode^=0x04;
							}
							else if((Ret&0x08)!=0){
								SeqControlParamData->ErrorCode^=0x08;
							}
							QString MessageText;
							MessageText	=LangSolver.GetString(RepairStation_LS,LID_263)/*"LOT数"*/;
							MessageText+=QString::number(GetCurINM());
							MessageText+=LangSolver.GetString(RepairStation_LS,LID_264)/*"は\n"*/;
							MessageText+=LangSolver.GetString(RepairStation_LS,LID_265)/*"候補数過多により検査確認を終了します。\n\nOKボタンで基板を搬送します。"*/;
							DLL_SetMessageFormLabel(MessageText);
							wErrNextBS=TempFlag;
							return;
						}
						//ログデータ（MaxOverだと分かるように）のセット
						//DLL_AppendNGInfo("個片番号","候補番号","ＰＣ","対応個片数","候補座標Ｘ","候補座標Ｙ","判定結果");
						DLL_AppendNGInfo(GetKohenNo(SType),GetNGNo(SType),GetPCNo(SType),GetTaiouKohenNumb(SType),GetNGPointX(SType),GetNGPointY(SType),LangSolver.GetString(RepairStation_LS,LID_266)/*"MaxOver"*/,GetRealKohenNo(SType));
						int Ret;
						QStringList NGKohenNoList;
						//DLL_OutputLog("基板番号","キズ候補数","NG個片名称リスト");
//						if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList))==-1){
						if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList,GetDebugLogFileStream()))==-1){
							SeqControlParamData->ErrorCode|=0x01;
							SeqControlParamData->ErrorCount++;
							SeqControlParamData->ErrorIndex=17;
							QString MessageText=LangSolver.GetString(RepairStation_LS,LID_267)/*"ログファイル(csv)の保存に失敗しました！"*/;
							DLL_SetMessageFormLabel(MessageText);
							return;
						}
						//フォームを表示
						bool MaxOver=true;
						Ret=DLL_AllCheckedFormShow(NGKohenNoList,SeqControlParamData->LotName,MaxOver);
						//履歴リストの内容（最新の１行）をファイルに保存する
						DLL_SaveHistoryList(dwHistoryList->ui.twHistoryList,HFieldNames,false);
						//次の検査履歴の読込み準備完了
						SeqControlParamData->ReviewResult	=Ret;
						SeqControlParamData->NGPieceNumbers	=GetListNumbers(NGKohenNoList);
						SeqControlParamData->MaxOver		=MaxOver;
						SeqControlParamData->ReviewFinished	=true;
						DLL_SetReviewEnable(false);
					}
					SeqControlParamData->ErrorCode=0;
					wErrNextBS=TempFlag;
					return;
				}
				wErrNextBS=TempFlag;
			}
//			wErrNextBS=false;
		}
		return;
	}

	//現在の行がない場合、OKの場合
	if(dwNGList->twNGList->currentItem()==NULL){
		if(OKWaitFlag==true){
			if(DLL_IsAllCheckedFormShow()==false && DLL_IsUnloadCommentFormShow()==false){
				//OKメッセージを出すかどうか
				if(DLL_GetShowOKMsg()==false){
					goto NOTSHOWOKMSG;
				}
				//OKボタン、又はNGボタン
				if(((TempFlag=SeqControlParamData->ErrNextBS)!=wErrNextBS) || ((TempFlag=SeqControlParamData->NGBS)!=wNGBS)){
					if(TempFlag==true){
						DLL_OKCheckFormClose();
NOTSHOWOKMSG:
						int Ret;
						QStringList NGKohenNoList;
						//DLL_OutputLog("基板番号","キズ候補数","NG個片名称リスト");
//						if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList))==-1){
						if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList,GetDebugLogFileStream()))==-1){
							SeqControlParamData->ErrorCode|=0x01;
							SeqControlParamData->ErrorCount++;
							SeqControlParamData->ErrorIndex=17;
							QString MessageText=LangSolver.GetString(RepairStation_LS,LID_268)/*"ログファイル(csv)の保存に失敗しました！"*/;
							DLL_SetMessageFormLabel(MessageText);
							OKWaitFlag=false;
//							QMessageBox::warning(this,tr("Error"),tr("Not complete save log."));
							return;
						}
						//フォームを表示
						bool MaxOver=false;
						Ret=DLL_AllCheckedFormShow(NGKohenNoList,SeqControlParamData->LotName,MaxOver);
						OKWaitFlag=false;
						//履歴リストの内容（最新の１行）をファイルに保存する
						DLL_SaveHistoryList(dwHistoryList->ui.twHistoryList,HFieldNames,false);
						//次の検査履歴の読込み準備完了
						SeqControlParamData->ReviewResult	=Ret;
						SeqControlParamData->NGPieceNumbers	=GetListNumbers(NGKohenNoList);
						SeqControlParamData->MaxOver		=MaxOver;
						SeqControlParamData->ReviewFinished	=true;
						return;
					}
					else{
						DLL_OKCheckFormShow();
						wErrNextBS=wNGBS=false;
						DLL_SetReviewEnable(false);
					}
				}
			}
		}
		return;
	}

	//レビュー操作制御
	if(DLL_GetReviewEnable()==false){
		if(SeqControlParamData->MacEmergency==true){
			SlotIsChangedCounter++;
			if(SlotIsChangedCounter>20){
				SlotIsChangedIndex^=1;
				MainFrame->ui.leLotCount->setEchoMode((QLineEdit::EchoMode)SlotIsChangedIndex);	//QLineEdit::Normal(0),QLineEdit::NoEcho(1)
				SlotIsChangedCounter=0;
			}
		}
		else{
			MainFrame->ui.leLotCount->setEchoMode(QLineEdit::Normal);
		}
		return;
	}

	//表示設定
	if(strText.isEmpty()==true){
		QPalette palette;
		palette.setColor(QPalette::WindowText,QColor(Qt::red));
		MainFrame->ui.lbMessage->setPalette(palette);
//		strText+="検査結果が表示されました。\nレビューを開始して下さい。";
		strText=LangSolver.GetString(RepairStation_LS,LID_269)/*"検査中"*/;
		MainFrame->ui.lbMessage->setText(strText);	//とりあえず日本語で表示させる
		MainFrame->ui.lbMessage->setFont(QFont(LangSolver.GetString(RepairStation_LS,LID_270)/*"Helvetica"*/,50));
	}
	SlotIsChangedCounter++;
	if(SlotIsChangedCounter>20){
		SlotIsChangedIndex^=1;
		MainFrame->ui.leLotCount->setEchoMode((QLineEdit::EchoMode)SlotIsChangedIndex);	//QLineEdit::Normal(0),QLineEdit::NoEcho(1)
		SlotIsChangedCounter=0;
	}

	//OKボタン
	if((TempFlag=SeqControlParamData->ErrNextBS)!=wErrNextBS){
		if(TempFlag==true){
			//ログ書き出し後は何もしない
			if(DLL_IsOutputLog()==false){
				//フォーカス（選択）の設定
				int		Row=0;
				int		RowCnt;
				int		NextRow;
				bool	Enabled=false;
				if((RowCnt=dwNGList->twNGList->rowCount())>0){
					int CurrentRow=dwNGList->twNGList->currentRow();
					if(PrevNGRow.count()>0 && CurrentRow==PrevNGRow.last()){
						Row=RowCnt;
					}
					else{
						//ログデータ（NG毎）のセット
						//DLL_AppendNGInfo("個片番号","候補番号","ＰＣ","対応個片数","候補座標Ｘ","候補座標Ｙ","判定結果");
						DLL_AppendNGInfo(GetKohenNo(SType),GetNGNo(SType),GetPCNo(SType),GetTaiouKohenNumb(SType),GetNGPointX(SType),GetNGPointY(SType),LangSolver.GetString(RepairStation_LS,LID_271)/*"OK"*/,GetRealKohenNo(SType));
						//１個前の行を覚えておく
						PrevNGRow.append(CurrentRow);
						//選択された行を緑色にする
						SetColorToTable(dwNGList->twNGList,CurrentRow,QColor(Qt::green));

						if((Row=CurrentRow+1)<RowCnt){
							//NGとされた個片は飛ばすようにする
							QString AreaName;
							int IndexARA=NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_272)/*"ARA"*/);
							for(;Row<RowCnt;Row++){
								QString NextARA=dwNGList->twNGList->item(Row,IndexARA)->text();
								QStringList List=NextARA.split(',');
								int i;
								for(i=0;i<List.count();i++){
									if(NGAreaNameList[SType].contains(List[i])==false){
										break;
									}
								}
								if(i==List.count()){
									//ログデータ（NDデータ）のセット
									int iNGP=dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_273)/*"NGP"*/))->text().toInt();
									if(NGPTagList[iSide]!=NULL){
										for(XMLTagAttr *TA=NGPTagList[iSide][iNGP]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
											if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_274)/*"PG"*/)==0){
												SetPG(TA->iAttrData);
											}
										}
										//DLL_AppendNGInfo("個片番号","候補番号","ＰＣ","対応個片数","候補座標Ｘ","候補座標Ｙ","判定結果");
//										DLL_AppendNGInfo(&NextARA,Row,GetPG(),GetTaiouKohenNumb(SType),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf("X, Y"))->text()),"",","),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf("X, Y"))->text()),", ",""),"ND");
										DLL_AppendNGInfo(&dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_275)/*"wARA"*/))->text(),Row,GetPG(),GetTaiouKohenNumb(SType),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_276)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_277)/*""*/,LangSolver.GetString(RepairStation_LS,LID_278)/*","*/),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_279)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_280)/*", "*/,LangSolver.GetString(RepairStation_LS,LID_281)/*""*/),LangSolver.GetString(RepairStation_LS,LID_282)/*"ND"*/,&NextARA);
									}
									continue;
								}
								dwNGList->twNGList->selectRow(Row);
								break;
							}
						}
					}
					if(Row==RowCnt){
						//最終確認画面のOKボタン２回押し対応
						if(DLL_GetOKDoubleDone()==true && FlagPreNextDoubleOK==true){
							FlagPreNextDoubleOK=false;
							//デバッグログ出力
							WriteDebugLogFile(*(GetInspectionID(SType)) + LangSolver.GetString(RepairStation_LS,LID_283)/*" DLL_GetOKDoubleDone()."*/);
						}
						else{
							if(DLL_PreNext(false)==true){
								//Selectionをクリア
								dwNGList->twNGList->clearSelection();
								//最後の個片NG色が更新されない現象を回避
								for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
									IDataUnit->MImageClassList[Cnt]->repaint();
								}
								FlagPreNextDoubleOK=true;
								FlagPreNextDoubleNG=true;
								//デバッグログ出力
								WriteDebugLogFile(*(GetInspectionID(SType)) + LangSolver.GetString(RepairStation_LS,LID_284)/*"DLL_PreNext().[OK]"*/);
							}
							else{
								DLL_SetReviewEnable(false);
								FlagPreNextDoubleNG=false;
								//ログの書き出し
								int Ret;
								QStringList NGKohenNoList;
								//DLL_OutputLog("基板番号","キズ候補数","NG個片名称リスト");
//								if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList))==-1){
								if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList,GetDebugLogFileStream()))==-1){
									//デバッグログ出力
									WriteDebugLogFile(*(GetInspectionID(SType)) + LangSolver.GetString(RepairStation_LS,LID_285)/*"DLL_OutputLog() false."*/);

									SeqControlParamData->ErrorCode|=0x01;
									SeqControlParamData->ErrorCount++;
									SeqControlParamData->ErrorIndex=18;
									QString MessageText=LangSolver.GetString(RepairStation_LS,LID_286)/*"ログファイル(csv)の保存に失敗しました！\n\nOKボタンで異常を発生します。"*/;
									DLL_SetMessageFormLabel(MessageText);
									return;
								}
								//フォームを表示
								bool MaxOver=false;
								Ret=DLL_AllCheckedFormShow(NGKohenNoList,SeqControlParamData->LotName,MaxOver);
								//NG画像（JPG）を保存
								if(SaveNGImage(dwNGList->twNGList,&NGFieldNames)==false){
									SeqControlParamData->ErrorCode|=0x02;
									SeqControlParamData->ErrorCount++;
									SeqControlParamData->ErrorIndex=19;
									QString MessageText=LangSolver.GetString(RepairStation_LS,LID_287)/*"NG候補画像の保存に失敗しました！\n\nOKボタンで異常を発生します。"*/;
									DLL_SetMessageFormLabel(MessageText);
								}
								//履歴リストの内容（最新の１行）をファイルに保存する
								DLL_SaveHistoryList(dwHistoryList->ui.twHistoryList,HFieldNames,false);
								//次の検査履歴の読込み準備完了
								SeqControlParamData->ReviewResult	=Ret;
								SeqControlParamData->NGPieceNumbers	=GetListNumbers(NGKohenNoList);
								SeqControlParamData->MaxOver		=MaxOver;
								SeqControlParamData->ReviewFinished	=true;
							}
						}
					}
				}
			}
		}
		wErrNextBS=TempFlag;
	}
	//NGボタン
	else if((TempFlag=SeqControlParamData->NGBS)!=wNGBS){
		if(TempFlag==true){
			//ログ書き出し後は何もしない
			if(DLL_IsOutputLog()==false){
				int Row=0;
				int RowCnt=dwNGList->twNGList->rowCount();
				if(RowCnt>0){
					int CurrentRow=dwNGList->twNGList->currentRow();
					if(PrevNGRow.count()>0 && CurrentRow==PrevNGRow.last()){
						Row=RowCnt;
					}
					else{
						//ログデータ（NG毎）のセット
						//DLL_AppendNGInfo("個片番号","候補番号","ＰＣ","対応個片数","候補座標Ｘ","候補座標Ｙ","判定結果");
						DLL_AppendNGInfo(GetKohenNo(SType),GetNGNo(SType),GetPCNo(SType),GetTaiouKohenNumb(SType),GetNGPointX(SType),GetNGPointY(SType),LangSolver.GetString(RepairStation_LS,LID_288)/*"NG"*/,GetRealKohenNo(SType));
						//１個前の行を覚えておく
						PrevNGRow.append(CurrentRow);
						//選択された行を黄色にする
						SetColorToTable(dwNGList->twNGList,CurrentRow,QColor(Qt::yellow));
						//次のエリアコードのNGリストまで移動
						QString AreaName;
						int IndexARA;
						if((AreaName=dwNGList->twNGList->item(CurrentRow,(IndexARA=NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_289)/*"ARA"*/)))->text()).isEmpty()){
							//NGボタンが押された時のARA(外)を退避しておく
							NGAreaNameList[SType].append(GetEmptyARA(GetString(&(dwNGList->twNGList->item(CurrentRow,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_290)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_291)/*""*/,LangSolver.GetString(RepairStation_LS,LID_292)/*","*/).toInt(),GetString(&(dwNGList->twNGList->item(CurrentRow,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_293)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_294)/*", "*/,LangSolver.GetString(RepairStation_LS,LID_295)/*""*/).toInt()));
							if((Row=CurrentRow+1)<RowCnt){
								dwNGList->twNGList->selectRow(Row);
							}
						}
						else{
							QStringList List=AreaName.split(/**/',');
							for(int i=0;i<List.count();i++){
								//NGボタンが押された時のARAを退避しておく
								NGAreaNameList[SType].append(List[i]);
							}
							for(Row=CurrentRow+1;Row<RowCnt;Row++){
								QString NextARA;
								if((NextARA=dwNGList->twNGList->item(Row,IndexARA)->text())!=AreaName){
									QStringList NextARAList=NextARA.split(/**/',');
									int i;
									for(i=0;i<NextARAList.count();i++){
										if(NGAreaNameList[SType].contains(NextARAList[i])==false){
											dwNGList->twNGList->selectRow(Row);
											break;
										}
									}
									if(i<NextARAList.count()){
										break;
									}
								}
								//ログデータ（NDデータ）のセット
								int iNGP=dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_296)/*"NGP"*/))->text().toInt();
								if(NGPTagList[iSide]!=NULL){
									for(XMLTagAttr *TA=NGPTagList[iSide][iNGP]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
										if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairStation_LS,LID_297)/*"PG"*/)==0){
											SetPG(TA->iAttrData);
										}
									}
								}
								//DLL_AppendNGInfo("個片番号","候補番号","ＰＣ","対応個片数","候補座標Ｘ","候補座標Ｙ","判定結果");
//								DLL_AppendNGInfo(&dwNGList->twNGList->item(Row,NGFieldNames.indexOf("ARA"))->text(),Row,GetPG(),GetTaiouKohenNumb(SType),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf("X, Y"))->text()),"",","),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf("X, Y"))->text()),", ",""),"ND");
								DLL_AppendNGInfo(&dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_298)/*"wARA"*/))->text(),Row,GetPG(),GetTaiouKohenNumb(SType),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_299)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_300)/*""*/,LangSolver.GetString(RepairStation_LS,LID_301)/*","*/),&GetString(&(dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_302)/*"X, Y"*/))->text()),LangSolver.GetString(RepairStation_LS,LID_303)/*", "*/,LangSolver.GetString(RepairStation_LS,LID_304)/*""*/),LangSolver.GetString(RepairStation_LS,LID_305)/*"ND"*/,&dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_306)/*"ARA"*/))->text());
							}
						}
						//履歴リストにNGとされた個片番号を記述する
						if(DLL_GetShowNGArea()==true){
							ShowNGAreaNameList();
						}
					}
					if(Row==RowCnt){
						//最終確認画面のOKボタン２回押し対応
						if(FlagPreNextDoubleNG==false){
							if(DLL_PreNext(false)==true){
								//Selectionをクリア
								dwNGList->twNGList->clearSelection();
								//最後の個片NG色が更新されない現象を回避
								for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
									IDataUnit->MImageClassList[Cnt]->repaint();
								}
								FlagPreNextDoubleOK=true;
								FlagPreNextDoubleNG=true;
								//デバッグログ出力
								WriteDebugLogFile(*(GetInspectionID(SType)) + LangSolver.GetString(RepairStation_LS,LID_307)/*"DLL_PreNext().[NG]"*/);
							}
							else{
								//ここに入ってくる事は無い？？？
								DLL_SetReviewEnable(false);
								//ログの書き出し
								int Ret;
								QStringList NGKohenNoList;
								//DLL_OutputLog("基板番号","キズ候補数","NG個片名称リスト");
//								if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList))==-1){
								if((Ret=DLL_OutputLog(GetInspectionID(SType),GetNGNumb(SType),NGKohenNoList,GetDebugLogFileStream()))==-1){
									SeqControlParamData->ErrorCode|=0x01;
									SeqControlParamData->ErrorCount++;
									SeqControlParamData->ErrorIndex=20;
									QString MessageText=LangSolver.GetString(RepairStation_LS,LID_308)/*"ログファイル(csv)の保存に失敗しました！\n\nOKボタンで異常を発生します。"*/;
									DLL_SetMessageFormLabel(MessageText);
									return;
								}
								//フォームを表示
								bool MaxOver=false;
								Ret=DLL_AllCheckedFormShow(NGKohenNoList,SeqControlParamData->LotName,MaxOver);
								//NG画像（JPG）を保存
								if(SaveNGImage(dwNGList->twNGList,&NGFieldNames)==false){
									SeqControlParamData->ErrorCode|=0x02;
									SeqControlParamData->ErrorCount++;
									SeqControlParamData->ErrorIndex=21;
									QString MessageText=LangSolver.GetString(RepairStation_LS,LID_309)/*"NG候補画像の保存に失敗しました！\n\nOKボタンで異常を発生します。"*/;
									DLL_SetMessageFormLabel(MessageText);
								}
								//履歴リストの内容（最新の１行）をファイルに保存する
								DLL_SaveHistoryList(dwHistoryList->ui.twHistoryList,HFieldNames,false);
								//次の検査履歴の読込み準備完了
								SeqControlParamData->ReviewResult	=Ret;
								SeqControlParamData->NGPieceNumbers	=GetListNumbers(NGKohenNoList);
								SeqControlParamData->MaxOver		=MaxOver;
								SeqControlParamData->ReviewFinished	=true;
							}
						}
					}
				}
			}
		}
		wNGBS=TempFlag;
	}
	//戻るボタン
	else if((TempFlag=SeqControlParamData->BackBS)!=wBackBS){
		if(TempFlag==true){
			//ログ書き出し後は何もしない
			if(DLL_IsOutputLog()==false){
				if(PrevNGRow.count()>0){
					int Row;
					if(DLL_PreNext(true)==true){
						Row=dwNGList->twNGList->rowCount()-1;
						FlagPreNextDoubleOK=false;
						FlagPreNextDoubleNG=false;
					}
					else{
						Row=dwNGList->twNGList->currentIndex().row()-1;
					}
					//ログデータ（NGデータ）のRemove
					QString PrevARA;
					for(;Row>=PrevNGRow.last();Row--){
						//DLL_RemoveNGInfo("個片番号");
//						DLL_RemoveNGInfo(&(PrevARA=dwNGList->twNGList->item(Row,NGFieldNames.indexOf("ARA"))->text()));
						DLL_RemoveNGInfo(&dwNGList->twNGList->item(Row,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_310)/*"wARA"*/))->text());
					}
					PrevARA=dwNGList->twNGList->item(Row+1,NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_311)/*"ARA"*/))->text();
					//フォーカス設定
					dwNGList->twNGList->selectRow(PrevNGRow.last());
					//直前のNGリストの行を削除
					PrevNGRow.removeLast();
					//直前がNGと判定した行の場合、個片名称リストから退避してあるARAを削除
					if(dwNGList->twNGList->currentItem()->backgroundColor()==QColor(Qt::yellow)){
						int Cnt=PrevARA.count(',')+1;
						for(int i=0;i<Cnt;i++){
							if(NGAreaNameList[SType].count()>0){
								NGAreaNameList[SType].removeLast();
							}
						}
						IDataUnit->MImageClassList[SType]->repaint();
					}
					//現在の行をチェック済色に戻す
					SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentIndex().row(),twNGListCheckColor);
					//履歴リストにNGとされた個片番号を記述する
					if(DLL_GetShowNGArea()==true){
						ShowNGAreaNameList();
					}
				}
			}
		}
		wBackBS=TempFlag;
	}
}

void RepairStation::SlotClient_Update(QString strXML)
{
	//表面データか裏面データかの判断
	for(int i=0;i<IDataUnit->MImageClassList.count();i++){
		QByteArray QNO;
		if(i==Front){
			if(strQNO1.toInt()==-1){
				continue;
			}
			else{
				QNO=strQNO1;
			}
		}
		else{
			if(strQNO2.toInt()==-1){
				continue;
			}
			else{
				QNO=strQNO2;
			}
		}
		QByteArray ErrMsg;
		xmlCont[i]->Client_Update(QNO,strXML.toLocal8Bit().data(),GetXMLFile(i),ErrMsg,QString::number(ClientNo[i]).toLocal8Bit().data());
	}
/*
	//表面データか裏面データかの判断
	QByteArray QNO;
	if(iSide==Front)
		QNO=strQNO1;
	else
		QNO=strQNO2;

	QByteArray ErrMsg;
	xmlCont[iSide]->Client_Update(QNO,strXML.toLocal8Bit().data(),GetXMLFile(iSide),ErrMsg,QString::number(ClientNo[iSide]).toLocal8Bit().data());
*/
}

//NGリスト上の個片コンボボックスかのeditTextChanged
void RepairStation::PieceListEditorTextChanged(const QString &Text)
{
	IDataUnit->MImageClassList[SType]->SetPieceName(Text);

	//移動前のコンボボックス欄の値を取得
	SetDataToTable(dwNGList->twNGList,dwNGList->twNGList->currentRow(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_312)/*"ARA"*/),Text);

	//PluginDLL対応
	if(DLL_GetName!=NULL){
		//ログデータのセット
		QString CurrentPieceName=Text;
		SetRealKohenNo(SType,&CurrentPieceName);
	}

	//再描画
	for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
		IDataUnit->MImageClassList[Cnt]->repaint();
	}
}

void RepairStation::SlotError(int Index)
{
//	SeqControlParamData->SoftEmergency=true;
	DLL_SetMessageFormLabel(LangSolver.GetString(RepairStation_LS,LID_313)/*"NG候補画像の保存に失敗しました！\n\nOKボタンで異常を発生します。"*/);
	SeqControlParamData->ErrorCode|=0x02;
	SeqControlParamData->ErrorCount++;
	SeqControlParamData->ErrorIndex=Index;
}

void RepairStation::SlotProcessCheck(QString ProcessName)
{
	if(ProcessName==LangSolver.GetString(RepairStation_LS,LID_314)/*"Messager.exe"*/){
		QString Message=ProcessName + LangSolver.GetString(RepairStation_LS,LID_315)/*" が起動していません！\n"*/
						+ ProcessName + LangSolver.GetString(RepairStation_LS,LID_316)/*" を起動してから確認ソフトを立ち上げて下さい。\n\n"*/
						+ LangSolver.GetString(RepairStation_LS,LID_317)/*"アプリケーションを終了します。"*/;
		QMessageBox::critical(this,LangSolver.GetString(RepairStation_LS,LID_318)/*"エラー"*/,Message);
		exit(-1);
	}
	else{
		QString Message=ProcessName + LangSolver.GetString(RepairStation_LS,LID_319)/*" が起動していません！\n"*/
						+ ProcessName + LangSolver.GetString(RepairStation_LS,LID_320)/*" を起動して下さい。"*/;
		QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_321)/*"警告"*/,Message);
		DLL_StartProcessCheckThread(true);
	}
}

void RepairStation::Init(QString XmlConnect_DotFileName)
{
	PasswordEventOperator *peo = new PasswordEventOperator(this);

	//タイトルの表示欄にサーバーパスも表示
	QString Title=/**/"RepairStation(";
	SetXmlConnectFileName(XmlConnect_DotFileName);
	QStringList	XmlConnectDatList;
	if(LoadFile(XmlConnect_DotFileName,XmlConnectDatList)){
		Title+=XmlConnectDatList.at(0);		//hostname
		Title+=/**/")"/*LangSolver.GetString(RepairStation_LS,LID_890)*//*")"*/;
	}
	setWindowTitle(Title);

	FrontMImage	=NULL;
	BackMImage	=NULL;

//	showMaximized();		//画面の最大化
//	showFullScreen();		//フルスクリーン表示
	SType			=Front;
	FKey			=-1;
	UpdateFlg		=false;
	NoNGFlg			=false;
	NGListFlag		=false;
	SaveImageFlag	=false;

	//Widgetの作成
	MainFrame			=new MainWidget			();
	MasterImageSplitter	=new QSplitter			();
	dwMasterImage		=new DockMasterWhole	();
	dwMasterImage1		=new DockMasterWhole1	();
	dwMasterImage2		=new DockMasterWhole2	();
	dwNGMasterPix		=new DockMasterPiece	();
	dwNGInspectionPix	=new DockNGPiece		();
	dwHistoryList		=new DockHistoryList	();
	dwNGList			=new DockNGList			();
	pbGeneralSetting	=new QPushButton		();
	pbSimulateSequence	=new QPushButton		();
	pbClose				=new QPushButton		();
	dwWorker			=new QDockWidget		(LangSolver.GetString(RepairStation_LS,LID_322)/*"Worker"*/);
	leWorker			=new QLineEdit			();
	dwBoardName			=new QDockWidget		(LangSolver.GetString(RepairStation_LS,LID_323)/*"Board Name"*/);
	lwBoardName			=new QListWidget		();
	dwLotName			=new QDockWidget		(LangSolver.GetString(RepairStation_LS,LID_324)/*"Lot Name"*/);
	lwLotName			=new QListWidget		();
	chEditEnable		=new QCheckBox			();
	chNotShowHalt		=new QCheckBox			();
	MainProcessing		=new ProcessingForm		();
	pbShutdown			=new QPushButton		();

	//パスワードボタンの登録
	peo->addButton(&pbGeneralSetting);
	peo->addButton(&pbSimulateSequence);
	peo->addButton(&pbClose);
	peo->addButton(&pbShutdown);

	//Widgetの登録
	SetHFieldNames	(HFieldNames);
	SetHistoryList	(dwHistoryList->ui.twHistoryList);
	SetNGList		(dwNGList->twNGList);

	//オブジェクト名の設定
	setObjectName(/**/"RepairStation");
	pbGeneralSetting	->setObjectName(/**/"pbGeneralSetting");
	pbSimulateSequence	->setObjectName(/**/"pbSimulateSequence");
	pbClose				->setObjectName(/**/"pbClose");
	dwWorker			->setObjectName(/**/"dwWorker");
	dwBoardName			->setObjectName(/**/"dwBoardName");
	dwLotName			->setObjectName(/**/"dwLotName");
	chEditEnable		->setObjectName(/**/"chEditEnable");
	chNotShowHalt		->setObjectName(/**/"chNotShowHalt");
	pbShutdown			->setObjectName(/**/"pbShutdown");

	//Widgetの配置
	MasterImageSplitter->addWidget(dwMasterImage1);
	dwMasterImage->setWidget(MasterImageSplitter);
	dwMasterImage2->setVisible(false);
	QMainWindow::setCorner(Qt::TopLeftCorner,	Qt::LeftDockWidgetArea);
	QMainWindow::setCorner(Qt::TopRightCorner,	Qt::RightDockWidgetArea);

	//Widgetのサイズ
	LoadLocation();
	setCentralWidget(MainFrame);

	//Prorerty
	addDockWidget(Qt::LeftDockWidgetArea,	dwMasterImage);
	addDockWidget(Qt::TopDockWidgetArea,	dwNGMasterPix);
	addDockWidget(Qt::TopDockWidgetArea,	dwNGInspectionPix);
	addDockWidget(Qt::RightDockWidgetArea,	dwNGList);
	addDockWidget(Qt::RightDockWidgetArea,	dwHistoryList);

	dwWorker	->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwBoardName	->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwLotName	->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwWorker	->setMinimumWidth(170);
	dwBoardName	->setMinimumWidth(170);
	lwBoardName	->setMaximumHeight(30);
	dwLotName	->setMinimumWidth(170);
	lwLotName	->setMaximumHeight(30);
	dwWorker	->setWidget(leWorker);
	dwBoardName	->setWidget(lwBoardName);
	dwLotName	->setWidget(lwLotName);
	leWorker	->setReadOnly(true);
	lwBoardName	->addItem(LangSolver.GetString(RepairStation_LS,LID_335)/*""*/);
	lwBoardName	->addItem(LangSolver.GetString(RepairStation_LS,LID_336)/*""*/);
	lwBoardName	->setSelectionMode(QAbstractItemView::NoSelection);
	lwLotName	->addItem(LangSolver.GetString(RepairStation_LS,LID_337)/*""*/);
	lwLotName	->addItem(LangSolver.GetString(RepairStation_LS,LID_338)/*""*/);
	lwLotName	->setSelectionMode(QAbstractItemView::NoSelection);
	pbShutdown	->setVisible(false);

	//Window
	pbGeneralSetting	->setText(LangSolver.GetString(RepairStation_LS,LID_339)/*"General Setting"*/);
	pbGeneralSetting	->setFixedSize(100,40);
	chEditEnable		->setText(LangSolver.GetString(RepairStation_LS,LID_340)/*"Edit Enable"*/);
	chNotShowHalt		->setText(LangSolver.GetString(RepairStation_LS,LID_341)/*"Not Show HALT"*/);
	pbSimulateSequence	->setText(LangSolver.GetString(RepairStation_LS,LID_342)/*"Show Sequence"*/);
	pbSimulateSequence	->setFixedSize(100,40);
	pbClose				->setText(LangSolver.GetString(RepairStation_LS,LID_343)/*"Close"*/);
	pbClose				->setFixedSize(100,40);
	pbShutdown			->setText(LangSolver.GetString(RepairStation_LS,LID_344)/*"Shutdown"*/);
	pbShutdown			->setFixedSize(100,40);

	//Layout
	QHBoxLayout *HLayout=new QHBoxLayout();
	HLayout->addWidget(dwWorker,			0,Qt::AlignLeft);
	HLayout->addWidget(dwBoardName,			0,Qt::AlignLeft);
	HLayout->addWidget(dwLotName,			0,Qt::AlignLeft);
	HLayout->addWidget(pbGeneralSetting,	0,Qt::AlignLeft);
	HLayout->addWidget(chEditEnable,		0,Qt::AlignLeft);
	HLayout->addWidget(chNotShowHalt,		0,Qt::AlignLeft);
	HLayout->addWidget(pbSimulateSequence,	0,Qt::AlignLeft);
	HLayout->addWidget(pbShutdown,			1,Qt::AlignRight);
	HLayout->addWidget(pbClose,				1,Qt::AlignRight);
	QFrame *MFrame	=new QFrame();
	MFrame	->setLayout(HLayout);
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint);

	//ツールバーメニュー
	MainToolBar=addToolBar(LangSolver.GetString(RepairStation_LS,LID_345)/*"Main"*/);
	MainToolBar->addWidget(MFrame);

	//色の設定
	palette.setColor(QPalette::Base,QColor(Qt::cyan));
	twHistoryFrontColor	=twNGListFrontColor	=QColor(Qt::green);
	twHistoryBackColor	=twNGListBackColor	=QColor(Qt::blue);
	twHistoryBothColor	=QColor(Qt::magenta);
	twNGListCheckColor	=QColor(Qt::red);
	ColorFKey.append(QColor(Qt::green));
	ColorFKey.append(QColor(Qt::blue));
	ColorFKey.append(QColor(Qt::cyan));
	ColorFKey.append(QColor(Qt::yellow));
	ColorFKey.append(QColor(Qt::gray));
	ColorFKey.append(QColor(Qt::darkRed));
	ColorFKey.append(QColor(Qt::darkGreen));
	ColorFKey.append(QColor(Qt::darkBlue));
	ColorFKey.append(QColor(Qt::darkCyan));
	ColorFKey.append(QColor(Qt::darkMagenta));
	ColorFKey.append(QColor(Qt::darkYellow));
	ColorFKey.append(QColor(Qt::darkGray));
	leWorker			->setPalette(palette);
	lwBoardName			->setPalette(palette);
	lwLotName			->setPalette(palette);

	//表示設定
	MainFrame			->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwMasterImage		->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwMasterImage1		->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwMasterImage2		->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwNGMasterPix		->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwNGInspectionPix	->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwHistoryList		->setFeatures(QDockWidget::NoDockWidgetFeatures);
	dwNGList			->setFeatures(QDockWidget::NoDockWidgetFeatures);
//	MainToolBar			->setAllowedAreas(Qt::TopToolBarArea);
	MainToolBar			->setFloatable(false);
	MainToolBar			->setMovable(false);

/*	dwHistoryList->ui.chReverseOrderDisplay->setVisible(false);
	dwHistoryList->ui.pbChangeLot->setVisible(false);
	dwHistoryList->ui.gridLayout->widget();
*/
	//輝度テーブル値の初期化
	for(int i=0;i<=255;i++){
		Brightness[i]=i;
	}

	//プラグインDLL（OutputLog.dll：MMC用DLL）
	QLibrary myLib(/**/"./OutputLog.dll");
	if(myLib.isLibrary(/**/"./OutputLog.dll")==false){
		return;
	}
	if(myLib.load()==false){
//		MainFrame->ui.trMasterList->resize(MainFrame->ui.trMasterList->width(),1000);
///		MainFrame->ui.trMasterList->setMinimumHeight(MainFrame->height());
		delete MainFrame->ui.lbMessage;
		delete MainFrame->ui.lbLotName;
		delete MainFrame->ui.leLotName;
		delete MainFrame->ui.lbLotCount;
		delete MainFrame->ui.leLotCount;
		delete MainFrame->ui.lbProductCount;
		delete MainFrame->ui.leProductCount;
		delete MainFrame->ui.vboxLayout;
		MainFrame->ui.layoutWidget->setMinimumSize(0,0);
		MainFrame->ui.layoutWidget->setMaximumSize(0,0);
		return;
	}
	if(myLib.isLoaded()==false){
		return;
	}

	DLL_GetName					=(bool (*)(QString &str))myLib.resolve(/**/"DLL_GetName");
	DLL_SetLogInfo				=(void (*)(QString *Hinsh,QString *Lot,QString *Jouge,QStringList *HDNameList,QStringList *KohenNameList))myLib.resolve(/**/"DLL_SetLogInfo");
	DLL_AppendNGInfo			=(void (*)(QString *KohenName,int NGNo,int PCNo,int TaiouKohenNumb,QString *X,QString *Y,QString HanteiKekka,QString *RealKohenName))myLib.resolve(/**/"DLL_AppendNGInfo");
	DLL_OutputLog				=(int (*)(QString *KibanNo,int NGNumb,QStringList &NGKohenNoList,QTextStream &FileStream))myLib.resolve(/**/"DLL_OutputLog");
	DLL_IsOutputLog				=(bool (*)(void))myLib.resolve(/**/"DLL_IsOutputLog");
	DLL_SetIsOutputLog			=(void (*)(bool IsOutputLog))myLib.resolve(/**/"DLL_SetIsOutputLog");
	DLL_RemoveNGInfo			=(void (*)(QString *KohenName))myLib.resolve(/**/"DLL_RemoveNGInfo");
	DLL_AllCheckedFormShow		=(int (*)(QStringList &NGKohenNoList,QString LotName,bool &IsMaxOver))myLib.resolve(/**/"DLL_AllCheckedFormShow");
	DLL_AllCheckedFormClose		=(void (*)(void))myLib.resolve(/**/"DLL_AllCheckedFormClose");
	DLL_UnloadCommentFormShow	=(void (*)(void))myLib.resolve(/**/"DLL_UnloadCommentFormShow");
	DLL_UnloadCommentFormClose	=(void (*)(void))myLib.resolve(/**/"DLL_UnloadCommentFormClose");
//	DLL_SaveNGImage				=(bool (*)(QByteArray *NGDataList,QString *KohenName,int NGNo,QString *strTime))myLib.resolve(/**/"DLL_SaveNGImage");
//	DLL_SaveNGImage				=(bool (*)(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGCount,QString *strTime))myLib.resolve(/**/"DLL_SaveNGImage");
	DLL_SaveNGImage				=(bool (*)(QByteArray **NGDataList[],int *NGI,int *Side,int *IDX,int *Index,QString *KohenName,int NGCount,QString *strTime,QString *RealKohenName))myLib.resolve(/**/"DLL_SaveNGImage");
	DLL_ClearNGInfoList			=(void (*)(void))myLib.resolve(/**/"DLL_ClearNGInfoList");
	DLL_PreNext					=(bool (*)(bool IsBack))myLib.resolve(/**/"DLL_PreNext");
//	DLL_ErrorFormShow			=(void (*)(void))myLib.resolve(/**/"DLL_ErrorFormShow");		//D-20091106
	DLL_ErrorFormShow			=(void (*)(int Code))myLib.resolve(/**/"DLL_ErrorFormShow");	//A-20091106
	DLL_ErrorFormClose			=(void (*)(void))myLib.resolve(/**/"DLL_ErrorFormClose");
	DLL_OKCheckFormShow			=(void (*)(void))myLib.resolve(/**/"DLL_OKCheckFormShow");
	DLL_OKCheckFormClose		=(void (*)(void))myLib.resolve(/**/"DLL_OKCheckFormClose");
	DLL_GetThreadInstance		=(QObject *(*)(void))myLib.resolve(/**/"DLL_GetThreadInstance");
	DLL_SaveLotNameFile			=(bool (*)(QString &LotName))myLib.resolve(/**/"DLL_SaveLotNameFile");
	DLL_GetReviewEnable			=(bool (*)(void))myLib.resolve(/**/"DLL_GetReviewEnable");
	DLL_SetReviewEnable			=(void (*)(bool Enable))myLib.resolve(/**/"DLL_SetReviewEnable");
	DLL_IsAllCheckedFormShow	=(bool (*)(void))myLib.resolve(/**/"DLL_IsAllCheckedFormShow");
	DLL_IsUnloadCommentFormShow	=(bool (*)(void))myLib.resolve(/**/"DLL_IsUnloadCommentFormShow");
	DLL_IsPreNext				=(bool (*)(void))myLib.resolve(/**/"DLL_IsPreNext");
	DLL_IsErrorFormShow			=(bool (*)(void))myLib.resolve(/**/"DLL_IsErrorFormShow");
	DLL_SetMessageFormLabel		=(void (*)(QString &Message))myLib.resolve(/**/"DLL_SetMessageFormLabel");
	DLL_SetMessageForm			=(void (*)(QColor &TextColor,QColor &BackgroundColor))myLib.resolve(/**/"DLL_SetMessageForm");
	DLL_MessageFormShow			=(void (*)(bool BlinkEnable))myLib.resolve(/**/"DLL_MessageFormShow");
	DLL_MessageFormClose		=(void (*)(void))myLib.resolve(/**/"DLL_MessageFormClose");
	DLL_SaveHistoryList			=(bool (*)(QTableWidget *W,QStringList &HeaderList,bool IsFirst))myLib.resolve(/**/"DLL_SaveHistoryList");
	DLL_GetShowPickupForm		=(bool (*)(void))myLib.resolve(/**/"DLL_GetShowPickupForm");
	DLL_GetShowPickupEnable		=(bool (*)(void))myLib.resolve(/**/"DLL_GetShowPickupEnable");
	DLL_SetShowPickupEnable		=(void (*)(bool Enable))myLib.resolve(/**/"DLL_SetShowPickupEnable");
	DLL_SetLogInfoHDNameList	=(void (*)(QStringList *HDNameList))myLib.resolve(/**/"DLL_SetLogInfoHDNameList");
	DLL_StartProcessCheckThread	=(void (*)(bool Enable))myLib.resolve(/**/"DLL_StartProcessCheckThread");
	DLL_GetCheckThreadInstance	=(QObject *(*)(void))myLib.resolve(/**/"DLL_GetCheckThreadInstance");

	DLL_SetMMCSettingList		=(bool (*)(QStringList &List))myLib.resolve(/**/"DLL_SetMMCSettingList");
	DLL_GetShowOKMsg			=(bool (*)(void))myLib.resolve(/**/"DLL_GetShowOKMsg");
	DLL_GetShowNGArea			=(bool (*)(void))myLib.resolve(/**/"DLL_GetShowNGArea");
	DLL_GetPickupNGAreaNumbA	=(int (*)(void))myLib.resolve(/**/"DLL_GetPickupNGAreaNumbA");
	DLL_GetPickupNGAreaNumbB	=(int (*)(void))myLib.resolve(/**/"DLL_GetPickupNGAreaNumbB");
	DLL_GetPickupNGAreaNumbC	=(int (*)(void))myLib.resolve(/**/"DLL_GetPickupNGAreaNumbC");
	DLL_GetNotShowEID			=(bool (*)(void))myLib.resolve(/**/"DLL_GetNotShowEID");
	DLL_SetMMCParameter			=(void (*)(QTableWidget *W,QStringList &HeaderList))myLib.resolve(/**/"DLL_SetMMCParameter");
	DLL_GetOKDoubleDone			=(bool (*)(void))myLib.resolve(/**/"DLL_GetOKDoubleDone");
	DLL_GetNGListControl		=(bool (*)(void))myLib.resolve(/**/"DLL_GetNGListControl");

	if(DLL_GetName					==NULL)
		return;
	if(DLL_SetLogInfo				==NULL)
		return;
	if(DLL_AppendNGInfo				==NULL)
		return;
	if(DLL_OutputLog				==NULL)
		return;
	if(DLL_IsOutputLog				==NULL)
		return;
	if(DLL_SetIsOutputLog			==NULL)
		return;
	if(DLL_RemoveNGInfo				==NULL)
		return;
	if(DLL_AllCheckedFormShow		==NULL)
		return;
	if(DLL_AllCheckedFormClose		==NULL)
		return;
	if(DLL_UnloadCommentFormShow	==NULL)
		return;
	if(DLL_UnloadCommentFormClose	==NULL)
		return;
	if(DLL_SaveNGImage				==NULL)
		return;
	if(DLL_ClearNGInfoList			==NULL)
		return;
	if(DLL_PreNext					==NULL)
		return;
	if(DLL_ErrorFormShow			==NULL)
		return;
	if(DLL_ErrorFormClose			==NULL)
		return;
	if(DLL_GetThreadInstance		==NULL)
		return;
	if(DLL_SaveLotNameFile			==NULL)
		return;
	if(DLL_GetReviewEnable			==NULL)
		return;
	if(DLL_SetReviewEnable			==NULL)
		return;
	if(DLL_IsAllCheckedFormShow		==NULL)
		return;
	if(DLL_IsUnloadCommentFormShow	==NULL)
		return;
	if(DLL_IsPreNext				==NULL)
		return;
	if(DLL_IsErrorFormShow			==NULL)
		return;
	if(DLL_OKCheckFormShow			==NULL)
		return;
	if(DLL_OKCheckFormClose			==NULL)
		return;
	if(DLL_SetMessageFormLabel		==NULL)
		return;
	if(DLL_SetMessageForm			==NULL)
		return;
	if(DLL_MessageFormShow			==NULL)
		return;
	if(DLL_MessageFormClose			==NULL)
		return;
	if(DLL_SaveHistoryList			==NULL)
		return;
	if(DLL_GetShowPickupForm		==NULL)
		return;
	if(DLL_GetShowPickupEnable		==NULL)
		return;
	if(DLL_SetShowPickupEnable		==NULL)
		return;
	if(DLL_SetLogInfoHDNameList		==NULL)
		return;
	if(DLL_StartProcessCheckThread	==NULL)
		return;
	if(DLL_GetCheckThreadInstance	==NULL)
		return;

	if(DLL_SetMMCSettingList		==NULL)
		return;
	if(DLL_GetShowOKMsg				==NULL)
		return;
	if(DLL_GetShowNGArea			==NULL)
		return;
	if(DLL_GetPickupNGAreaNumbA		==NULL)
		return;
	if(DLL_GetPickupNGAreaNumbB		==NULL)
		return;
	if(DLL_GetPickupNGAreaNumbC		==NULL)
		return;
	if(DLL_GetNotShowEID			==NULL)
		return;
	if(DLL_SetMMCParameter			==NULL)
		return;
	if(DLL_GetOKDoubleDone			==NULL)
		return;
	if(DLL_GetNGListControl			==NULL)
		return;

	//初期化
	SlotIsChangedCounter=0;
	SlotIsChangedIndex	=0;
	OKWaitFlag			=false;
	HistoryNGColList	=NULL;
	FlagPreNextDoubleOK	=false;
	FlagPreNextDoubleNG	=false;

	//画面設定
	MainFrame->ui.splitter->setOrientation(Qt::Vertical);
	dwNGMasterPix->setVisible(false);
	QMainWindow::setCorner(Qt::TopLeftCorner,	Qt::TopDockWidgetArea);
	QMainWindow::setCorner(Qt::TopRightCorner,	Qt::TopDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea,	dwMasterImage);
	addDockWidget(Qt::LeftDockWidgetArea,	dwNGInspectionPix);
	addDockWidget(Qt::RightDockWidgetArea,	dwNGList);
	addDockWidget(Qt::RightDockWidgetArea,	dwHistoryList);

//	addDockWidget(Qt::LeftDockWidgetArea,	dwNGInspectionPix);
//	addDockWidget(Qt::TopDockWidgetArea,	dwMasterImage);
//	addDockWidget(Qt::RightDockWidgetArea,	dwNGList);
//	addDockWidget(Qt::RightDockWidgetArea,	dwHistoryList);
	MainFrame->ui.lbLotName		->setMinimumHeight(40);
	MainFrame->ui.leLotName		->setMinimumHeight(60);
	MainFrame->ui.lbProductCount->setMinimumHeight(40);
	MainFrame->ui.leProductCount->setMinimumHeight(60);
	MainFrame->ui.lbLotCount	->setMinimumHeight(40);
	MainFrame->ui.leLotCount	->setMinimumHeight(60);
	MainFrame->ui.lbMessage		->setMinimumHeight(300);
	dwHistoryList	->ui.twHistoryList	->setMinimumHeight(300);
	dwHistoryList	->ui.label			->setText(LangSolver.GetString(RepairStation_LS,LID_346)/*"履歴数"*/);	//とりあえず日本語で表示させる
	dwNGList		->twNGList			->setMinimumHeight(350);
	QFont f(LangSolver.GetString(RepairStation_LS,LID_347)/*"Helvetica"*/,18);
	MainFrame		->SetFont(f);
	f.setPointSize(14);
	dwHistoryList	->SetFont(f);
	dwNGList		->SetFont(f);

	connect(DLL_GetThreadInstance(),SIGNAL(SignalError(int)),this,SLOT(SlotError(int)),Qt::QueuedConnection);
}

void RepairStation::SetParameter()
{
	for(int Cnt=0;Cnt<GetRepairSettingList().count();Cnt++){
		switch(Cnt){
			case 0:
				SetMasterDir(GetRepairSettingList().at(Cnt));			//MasterData Directory
/*				//ドライブを通す
				int AAA=0;
				int Len=MasterDir.length()+1;
				char *NetworkDriveBuff=new char[Len];
				QString2Char(MasterDir, NetworkDriveBuff, Len);
				if(CreateNetworkDrive(false,NetworkDriveBuff[0]-'A',"//localhost/Data","","")==true){
					AAA++;
				}
*/				break;
			case 1:
				SetNGBlink(GetRepairSettingList()[Cnt].toInt());	//NG Blink Enable Check
				break;
			case 2:
				tNGBlink.BlinkTime	=GetRepairSettingList()[Cnt].toInt();	//MasterData Directory
				break;
			case 3:
				IDataUnit->NGImagePieceList[0]->NGMarkSize=GetRepairSettingList()[Cnt].toInt();	//NG Mark Size
				break;
			case 4:
				SetCheckedNumb(GetRepairSettingList()[Cnt].toInt());
				if(GetCheckedNumb()==TopToBottom){
					SetNGSortXY(LangSolver.GetString(RepairStation_LS,LID_348)/*"Y"*/);						//NG Sort Top to Bottom Check
					SetNGSortOrder(LangSolver.GetString(RepairStation_LS,LID_349)/*"A"*/);
				}
				else if(GetCheckedNumb()==BottomToTop){
					SetNGSortXY(LangSolver.GetString(RepairStation_LS,LID_350)/*"Y"*/);						//NG Sort Bottom to Top Check
					SetNGSortOrder(LangSolver.GetString(RepairStation_LS,LID_351)/*"D"*/);
				}
				else if(GetCheckedNumb()==LeftToRight){
					SetNGSortXY(LangSolver.GetString(RepairStation_LS,LID_352)/*"X"*/);						//NG Sort Left to Right Check
					SetNGSortOrder(LangSolver.GetString(RepairStation_LS,LID_353)/*"A"*/);
				}
				else if(GetCheckedNumb()==RightToLeft){
					SetNGSortXY(LangSolver.GetString(RepairStation_LS,LID_354)/*"X"*/);						//NG Sort Right to Left Check
					SetNGSortOrder(LangSolver.GetString(RepairStation_LS,LID_355)/*"D"*/);
				}
				break;
			case 5:
				SetShowOK(GetRepairSettingList()[Cnt].toInt());
				if(GetShowOK())
					SetRes(LangSolver.GetString(RepairStation_LS,LID_356)/*"ALL"*/);								//NG Show OK
				else
					SetRes(LangSolver.GetString(RepairStation_LS,LID_357)/*"OK"*/);								//NG Show NG Only
				break;
			case 6:
				SetImgRate(GetRepairSettingList()[Cnt].toInt());	//Master Image Resolution
				break;
			case 7:
				SetNGWaitTime(GetRepairSettingList()[Cnt].toInt());	//NG Wait Time
//				dwNGList->twNGList->SetWaitTime(NGWaitTime);
				SetWaitTime(GetNGWaitTime());
				break;
			case 8:
				SetSigVolume(GetRepairSettingList()[Cnt].toDouble());	//Sigmoid Volume
				break;
			case 9:
				SetSigBright(GetRepairSettingList()[Cnt].toInt());		//Sigmoid Brightness
				break;
			case 10:
				SetReverseOrderDisplay(GetRepairSettingList()[Cnt].toInt());	//Reverse Order Display Check
				dwHistoryList->ui.chReverseOrderDisplay->setChecked(GetReverseOrderDisplay());
				break;
			case 11:
				SetNextCheck(GetRepairSettingList()[Cnt].toInt());		//Next Check
				break;
			case 12:
				SetEnterCheck(GetRepairSettingList()[Cnt].toInt());		//Enter Check
				break;
			case 13:
				SetNotShowHaltFlag(GetRepairSettingList()[Cnt].toInt());
				SetNotShowHalt(GetNotShowHaltFlag());	//NotShowHaltFlag
				chNotShowHalt->setChecked(GetNotShowHalt());
				break;
			case 14:
				SetEachPieces(GetRepairSettingList()[Cnt].toInt());		//Each Pieces Check
				break;
			case 15:
				SetMImageSplitter(GetRepairSettingList()[Cnt].toInt());	//Master Image Splitter Check
				MasterImageSplitter->setOrientation((Qt::Orientation)GetRepairSettingList()[Cnt].toInt());
				break;
			case 16:
				SetPieceColorString(GetRepairSettingList()[Cnt]);		//Pieces Color String
				break;
			case 17:
				SetEnableNGPieceChange(GetRepairSettingList()[Cnt].toInt());	//Enable NG Piece Change
				break;
			case 18:
				SetSaveDirNGImage(GetRepairSettingList().at(Cnt));		//Save NG Image Directory
				break;
			case 19:
				SetOutputDebugLog(GetRepairSettingList()[Cnt].toInt());		//Output Debug Log
				break;
			case 20:
				SetOutputXMLData(GetRepairSettingList()[Cnt].toInt());		//Output XML Data
				break;
			case 21:
				SetShowInsDataMsg(GetRepairSettingList()[Cnt].toInt());			//Show Inspection Data Message
				break;
			case 22:
				SetListScrollRowCnt(GetRepairSettingList()[Cnt].toInt());		//List Scroll Row Count
				break;
			case 23:
				SetOnlyFColor(GetRepairSettingList()[Cnt]);						//Only F Color
				if(GetOnlyFColor()==pbClose->palette().color(QPalette::Button).name()){
					twHistoryFrontColor	=twNGListFrontColor	=QColor(Qt::green);
				}
				else{
					twHistoryFrontColor	=twNGListFrontColor	=QColor(GetOnlyFColor());
				}
				break;
			case 24:
				SetOnlyBColor(GetRepairSettingList()[Cnt]);						//Only B Color
				if(GetOnlyBColor()==pbClose->palette().color(QPalette::Button).name()){
					twHistoryBackColor	=twNGListBackColor	=QColor(Qt::blue);
				}
				else{
					twHistoryBackColor	=twNGListBackColor	=QColor(GetOnlyBColor());
				}
				break;
			case 25:
				SetFBColor(GetRepairSettingList()[Cnt]);							//FB Color
				if(GetFBColor()==pbClose->palette().color(QPalette::Button).name()){
					twHistoryBothColor	=QColor(Qt::magenta);
				}
				else{
					twHistoryBothColor	=QColor(GetFBColor());
				}
				break;
			case 26:
				SetNGImageOffset(GetRepairSettingList()[Cnt].toInt());		//NGImage Offset
				break;
		}
	}
}

void RepairStation::MakeFrontMaster()
{
	//表面用マスターイメージ
	if(FrontMImage!=NULL){
		disconnect(FrontMImage,	SIGNAL(SignalOnPaint(QPainter &)),							this,		SLOT(FMasterSlotOnPaint(QPainter &)));
		disconnect(FrontMImage,	SIGNAL(SignalOnMouseLDown(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLDown(int,int,MasterImage *)));
		disconnect(this,		SIGNAL(SignalFMMouseLDown(int,int,int,int)),				FrontMImage,SLOT(SlotMMouseLDown(int,int,int,int)));
		disconnect(FrontMImage,	SIGNAL(SignalOnMouseLDrag(int,int,int,int,MasterImage *)),	this,		SLOT(SlotOnMouseLDrag(int,int,int,int,MasterImage *)));
		disconnect(FrontMImage,	SIGNAL(SignalOnMouseRClick(MasterImage *)),					this,		SLOT(SlotOnMouseRClick(MasterImage *)));
		disconnect(FrontMImage, SIGNAL(SignalOnMouseLClick(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLClick(int,int,MasterImage *)));
		delete FrontMImage;
//		FrontMImage=new MasterImage();
		FrontMImage=new MasterImg();
		IDataUnit->ReplaceImage(0,FrontMImage);
	}
	else{
//		FrontMImage=new MasterImage();
		FrontMImage=new MasterImg();
		IDataUnit->AddImage(FrontMImage);
	}
	connect(FrontMImage,SIGNAL(SignalOnPaint(QPainter &)),							this,		SLOT(FMasterSlotOnPaint(QPainter &)));
	connect(FrontMImage,SIGNAL(SignalOnMouseLDown(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLDown(int,int,MasterImage *)));
	connect(this,		SIGNAL(SignalFMMouseLDown(int,int,int,int))			,		FrontMImage,SLOT(SlotMMouseLDown(int,int,int,int)));
	connect(FrontMImage,SIGNAL(SignalOnMouseLDrag(int,int,int,int,MasterImage *)),	this,		SLOT(SlotOnMouseLDrag(int,int,int,int,MasterImage *)));
	connect(FrontMImage,SIGNAL(SignalOnMouseRClick(MasterImage *)),					this,		SLOT(SlotOnMouseRClick(MasterImage *)));
	connect(FrontMImage,SIGNAL(SignalOnMouseLClick(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLClick(int,int,MasterImage *)));
	dwMasterImage1->setWidget(FrontMImage);
}

void RepairStation::MakeBackMaster()
{
	//裏面用マスターイメージ
	if(BackMImage!=NULL){
		disconnect(BackMImage,	SIGNAL(SignalOnPaint(QPainter &)),							this,		SLOT(BMasterSlotOnPaint(QPainter &)));
		disconnect(BackMImage,	SIGNAL(SignalOnMouseLDown(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLDown(int,int,MasterImage *)));
		disconnect(this,		SIGNAL(SignalBMMouseLDown(int,int,int,int)),				BackMImage,	SLOT(SlotMMouseLDown(int,int,int,int)));
		disconnect(BackMImage,	SIGNAL(SignalOnMouseLDrag(int,int,int,int,MasterImage *)),	this,		SLOT(SlotOnMouseLDrag(int,int,int,int,MasterImage *)));
		disconnect(BackMImage,	SIGNAL(SignalOnMouseRClick(MasterImage *)),					this,		SLOT(SlotOnMouseRClick(MasterImage *)));
		disconnect(BackMImage,  SIGNAL(SignalOnMouseLClick(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLClick(int,int,MasterImage *)));
		delete BackMImage;
//		BackMImage=new MasterImage();
		BackMImage=new MasterImg();
		IDataUnit->ReplaceImage(1,BackMImage);
	}
	else{
//		BackMImage=new MasterImage();
		BackMImage=new MasterImg();
		IDataUnit->AddImage(BackMImage);
	}
	connect(BackMImage,	SIGNAL(SignalOnPaint(QPainter &)),							this,		SLOT(BMasterSlotOnPaint(QPainter &)));
	connect(BackMImage,	SIGNAL(SignalOnMouseLDown(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLDown(int,int,MasterImage *)));
	connect(this,		SIGNAL(SignalBMMouseLDown(int,int,int,int)),				BackMImage,	SLOT(SlotMMouseLDown(int,int,int,int)));
	connect(BackMImage,	SIGNAL(SignalOnMouseLDrag(int,int,int,int,MasterImage *)),	this,		SLOT(SlotOnMouseLDrag(int,int,int,int,MasterImage *)));
	connect(BackMImage,	SIGNAL(SignalOnMouseRClick(MasterImage *)),					this,		SLOT(SlotOnMouseRClick(MasterImage *)));
	connect(BackMImage, SIGNAL(SignalOnMouseLClick(int,int,MasterImage *)),			this,		SLOT(SlotOnMouseLClick(int,int,MasterImage *)));
	dwMasterImage2->setWidget(BackMImage);
}

int RepairStation::GetRelationCode()
{
	//マスターリスト選択処理
	if(MainFrame->ui.twMasterList->currentIndex().row()==-1){
		return -1;
	}
	MCode=MainFrame->ui.twMasterList->item(MainFrame->ui.twMasterList->currentIndex().row(),MFieldNames.indexOf(/**/"MASTERCODE"))->text();

	QSqlQuery query;
	query.prepare(/**/"select RELATIONCODE,MASTERNAME from MASTERDATA where MASTERCODE=?");
	query.addBindValue(MCode);
	query.exec();
	int RelationCode=-1;
	if(query.next()){
		RelationCode=query.value(query.record().indexOf(/**/"RELATIONCODE")).toInt();
		MName		=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
	}
	if(RelationCode==-1){
		return -1;
	}

	//裏面データが存在するかどうかの確認
	query.prepare(/**/"select MASTERCODE from MASTERDATA where RELATIONCODE=?");
	query.addBindValue(RelationCode);
	query.exec();
	int BMasterCode=-1;
	while(query.next()){
		int BMCode=query.value(query.record().indexOf(/**/"MASTERCODE")).toInt();
		if(BMCode==MCode.toInt()){
			continue;
		}
		BMasterCode=BMCode;
		break;
	}
	return BMasterCode;
}

bool RepairStation::ShowMasterImage(int BackMasterCode)
{
	//マスターリスト選択処理
	if(MainFrame->ui.twMasterList->currentIndex().row()==-1){
		return false;
	}
///	MCode=MainFrame->ui.twMasterList->item(MainFrame->ui.twMasterList->currentIndex().row(),MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_358)/*"MASTERCODE"*/))->text();
///	MName=MainFrame->ui.twMasterList->item(MainFrame->ui.twMasterList->currentIndex().row(),MFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_359)/*"MASTERNAME"*/))->text();

	if(BackMasterCode!=-1){
		MCode=QString::number(BackMasterCode);

		QSqlQuery query;
		query.prepare(/**/"select MASTERNAME from MASTERDATA where MASTERCODE=?");
		query.addBindValue(MCode);
		query.exec();
		if(query.next()){
			MName=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
		}
	}

	QString MasterSearchStr;
	QStringList	SList;
	QString MasterPath;

	QSqlQuery query;
	query.prepare(/**/"select PAGECODE,DOTPERLINE,MAXLINES,LAYERNUMB from MASTERPAGE where MASTERCODE=? order by PAGECODE");
	query.addBindValue(MCode);
	query.exec();
	int PNumb=0;
	int DotPerLineInImage,MaxLinesInImage;
	if(query.next()){
		DotPerLineInPage	=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_361)/*"DOTPERLINE"*/)).toInt();
		MaxLinesInPage		=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_362)/*"MAXLINES"*/)).toInt();
		DotPerLineInImage	=DotPerLineInPage>>IDataUnit->MImageClassList[SType]->ImgRate;
		MaxLinesInImage		=MaxLinesInPage>>IDataUnit->MImageClassList[SType]->ImgRate;
		LayerNumbInPage		=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_363)/*"LAYERNUMB"*/)).toInt();

		//MASTERDATAテーブルのGENERALDATAのBLOBデータを読込んで、画像オフセットの取得
		QList<int>	OffsetXList,OffsetYList;
		QSqlQuery MQuery;
		MQuery.prepare(LangSolver.GetString(RepairStation_LS,LID_364)/*"select MACHINEID, PAGENUMB, SETTINGDATA, GENERALDATA  from MASTERDATA where MASTERCODE=?"*/);
		MQuery.addBindValue(MCode);
		MQuery.exec();
		if(MQuery.next()){
			MachineID[SType]	=MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_365)/*"MACHINEID"*/)).toInt();
			Pagenumb			=MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_366)/*"PAGENUMB"*/)).toInt();
/*
			OutlineOffsetWriter=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetOutlineOffsetWriter();
			OutlineOffsetWriter=new OutlineOffsetInBlob();
			QSqlQuery MacQuery;
			MacQuery.prepare("select OUTLINEOFFSET from MACHINE where MACHINEID=?");
			MacQuery.addBindValue(MachineID);
			MacQuery.exec();
			if(MacQuery.next()){
				if(!MacQuery.value(MacQuery.record().indexOf("OUTLINEOFFSET")).isNull()){
					QBuffer Buff(&MacQuery.value(MacQuery.record().indexOf("OUTLINEOFFSET")).toByteArray());
					if(Buff.open(QIODevice::ReadWrite)){
						OutlineOffsetWriter->Load(&Buff);
						for(int i=0; i<Pagenumb; i++){
							OutlineOffsetInPage	data;
							data=OutlineOffsetWriter->GetData(i);
							OffsetXList.append(data.Dx);
							OffsetYList.append(data.Dy);
						}
					}
				}
			}
*/
			//OutlineOffsetの取得
			OffsetXList.clear();
			if(GetOutlineOffset(MachineID[SType],&OffsetXList,&OffsetYList)==false){
				if(!MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_367)/*"GENERALDATA"*/)).isNull()){
					QBuffer Buff(&MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_368)/*"GENERALDATA"*/)).toByteArray());
					if(Buff.open(QIODevice::ReadOnly)){
						EntryPointToFuncGlobal->DLL_GetLayersBase()->Load(&Buff);
						for(int i=0;i<EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageNumb();i++){
							OffsetXList.append(EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(i)->GetOutlineOffset()->x);
							OffsetYList.append(EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(i)->GetOutlineOffset()->y);
						}
					}
				}
			}
			if(!MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_369)/*"SETTINGDATA"*/)).isNull()){
				QBuffer Buff(&MQuery.value(MQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_370)/*"SETTINGDATA"*/)).toByteArray());
				if(Buff.open(QIODevice::ReadOnly)){
					EntryPointToFuncGlobal->DLL_GetLayersBase()->GetParamGlobal()->LoadParam(&Buff);
				}
			}
		}
/*

	//マスターリスト選択処理
	MCode=MainFrame->ui.twMasterList->item(MainFrame->ui.twMasterList->currentIndex().row(),MFieldNames.indexOf("MASTERCODE"))->text();
	MName=MainFrame->ui.twMasterList->item(MainFrame->ui.twMasterList->currentIndex().row(),MFieldNames.indexOf("MASTERNAME"))->text();

	QSqlQuery query;
	query.prepare("select PAGECODE,DOTPERLINE,MAXLINES,LAYERNUMB from MASTERPAGE where MASTERCODE=? order by PAGECODE");
	query.addBindValue(MCode);
	query.exec();

	int PNumb=0;
//	int XXX=0;
//	int AAA=0;
//	int BBB=0;
//	int CCC=0;
//	int DDD=0;
	int DotPerLineInImage,MaxLinesInImage;
	if(query.next()){
		DotPerLineInPage	=query.value(query.record().indexOf("DOTPERLINE")).toInt();
		MaxLinesInPage		=query.value(query.record().indexOf("MAXLINES")).toInt();
		DotPerLineInImage	=DotPerLineInPage>>IDataUnit->MImageClassList[SType]->ImgRate;
		MaxLinesInImage		=MaxLinesInPage>>IDataUnit->MImageClassList[SType]->ImgRate;
		LayerNumbInPage		=query.value(query.record().indexOf("LAYERNUMB")).toInt();

		//MASTERDATAテーブルのGENERALDATAのBLOBデータを読込んで、画像オフセットの取得
		QList<int>	OffsetXList,OffsetYList;
		QSqlQuery MQuery;
		MQuery.prepare("select GENERALDATA,SETTINGDATA from MASTERDATA where MASTERCODE=?");
		MQuery.addBindValue(MCode);
		MQuery.exec();

		if(MQuery.next()){
			if(!MQuery.value(MQuery.record().indexOf("GENERALDATA")).isNull()){
				QBuffer Buff(&MQuery.value(MQuery.record().indexOf("GENERALDATA")).toByteArray());
				if(Buff.open(QIODevice::ReadOnly)){
					EntryPointToFuncGlobal->DLL_GetLayersBase()->Load(&Buff);
//					XXX=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageNumb();
//					AAA=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(0)->GetOutlineOffset()->x;
//					BBB=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(0)->GetOutlineOffset()->y;
//					CCC=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(1)->GetOutlineOffset()->x;
//					DDD=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(1)->GetOutlineOffset()->y;
					for(int i=0;i<EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageNumb();i++){
						OffsetXList.append(EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(i)->GetOutlineOffset()->x);
						OffsetYList.append(EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(i)->GetOutlineOffset()->y);
					}
				}
			}
			if(!MQuery.value(MQuery.record().indexOf("SETTINGDATA")).isNull()){
				QBuffer Buff(&MQuery.value(MQuery.record().indexOf("SETTINGDATA")).toByteArray());
				if(Buff.open(QIODevice::ReadOnly)){
					EntryPointToFuncGlobal->DLL_GetLayersBase()->GetParamGlobal()->LoadParam(&Buff);
				}
			}
		}
*/
		//ProgressCounter
		int ProgressCounter=100/query.numRowsAffected()/(LayerNumbInPage+1);

		EntryPointToFuncGlobal->DLL_GetLayersBase()->InitialCreatePages(EntryPointToFuncGlobal);

		do{
			int iPage=query.value(query.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_371)/*"PAGECODE"*/)).toInt();
			//マスターデータファイル名の取得
			//QString	MasterSearch=GetMasterDir() + QDir::separator() + QString(/**/"Image") + MCode + QString(/**/"-")
			//					+ QString(/**/"Page") + QString::number(iPage) + QString(/**/"-")
			//					+ QString(/**/"Mac") + QString::number(MachineID[SType]) + QString(/**/".img");
			MasterSearchStr=QString(/**/"Image") + MCode + QString(/**/"-")
							+ QString(/**/"Page") + QString::number(iPage) + QString(/**/"-")
							+ QString(/**/"Mac*.img");
			QStringList	MasterSearchStrs;
			MasterSearchStrs.append(MasterSearchStr);
			QDir	SearchImager(GetMasterDir());
			SList=SearchImager.entryList(MasterSearchStrs);
			if(SList.count()>=1){
				MasterPath=GetMasterDir() + QDir::separator() + SList[0];
				//マスターデータファイルのチェック
				if(!QFile(MasterPath).exists()){
					QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_378)/*"Message"*/,MasterPath + LangSolver.GetString(RepairStation_LS,LID_379)/*" is not found."*/);
					return false;
				}

				QFile Buff(MasterPath);
				if(Buff.open(QIODevice::ReadOnly)==false){
					QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_380)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_381)/*"Buffer open error!"*/);
					return false;
				}

				bool FalseFlag=false;
				for(int LNumb=0;LNumb<LayerNumbInPage;LNumb++){
					DataInLayer	*L=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(LNumb);
					if(L->GetMasterBuff().Load(&Buff)==false)
						FalseFlag=true;
					ImageBufferForRepair	Dummy;
					if(Dummy.Load(&Buff)==false)
						FalseFlag=true;
					if(Dummy.Load(&Buff)==false)
						FalseFlag=true;
					//プログレスバーの更新
					MainProcessing->SetUpdate(ProgressCounter*(((LayerNumbInPage+1)*PNumb)+1+LNumb));
				}
				Buff.close();

				if(FalseFlag)
					return false;
			}

			IDataUnit->MImageClassList[SType]->ImageList << new ImageInPage();
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OrgOffsetX	=OffsetXList.at(PNumb);	//OutlineOffsetの取得
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OrgOffsetY	=OffsetYList.at(PNumb);
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OffsetX	=(IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OrgOffsetX)>>IDataUnit->MImageClassList[SType]->ImgRate;	//OutlineOffsetの取得
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OffsetY	=(IDataUnit->MImageClassList[SType]->ImageList[PNumb]->OrgOffsetY)>>IDataUnit->MImageClassList[SType]->ImgRate;
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->Image		=new QImage(DotPerLineInImage,MaxLinesInImage,QImage::Format_RGB32);
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->wImage		=new QImage(DotPerLineInImage,MaxLinesInImage,QImage::Format_RGB32);

			//Color or Mono
			IDataUnit->MImageClassList[SType]->ImgRateCount=1;
			for(int i=0;i<IDataUnit->MImageClassList[SType]->ImgRate;i++)
				IDataUnit->MImageClassList[SType]->ImgRateCount*=2;
			if(LayerNumbInPage==1){
				#pragma omp parallel
				{
					BYTE *pGray;
					#pragma omp for
					for(int Y=0;Y<MaxLinesInImage;Y++){
						pGray=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(0)->GetMasterBuff().GetY(Y);
						QRgb *pYLine=(QRgb *)IDataUnit->MImageClassList[SType]->ImageList[PNumb]->Image->scanLine(Y);
						for(int X=0;X<DotPerLineInImage;X++,pGray++){
//							IDataUnit->MImageClassList[SType]->ImageList[PNumb]->Image->setPixel(X,Y,qRgb(*pGray,*pGray,*pGray));
							*pYLine++=qRgb(*pGray,*pGray,*pGray);
						}
					}
				}
			}
			else{
				#pragma omp parallel
				{
					BYTE *pR,*pG,*pB;
					#pragma omp for
					for(int Y=0;Y<MaxLinesInImage;Y++){
						pR=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(0)->GetMasterBuff().GetY(Y);
						pG=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(1)->GetMasterBuff().GetY(Y);
						pB=EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(2)->GetMasterBuff().GetY(Y);
						QRgb *pYLine=(QRgb *)IDataUnit->MImageClassList[SType]->ImageList[PNumb]->Image->scanLine(Y);
						for(int X=0;X<DotPerLineInImage;X++,pR++,pG++,pB++)
//							IDataUnit->MImageClassList[SType]->ImageList[PNumb]->Image->setPixel(X,Y,qRgb(*pR,*pG,*pB));
							*pYLine++=qRgb(*pR,*pG,*pB);
					}
				}
			}
			//QImageの退避
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->SetMasterImage();
			//QImageの補正
			IDataUnit->MImageClassList[SType]->ImageList[PNumb]->SetMasterBrightness(Brightness);

			for(int LNumb=0;LNumb<LayerNumbInPage;LNumb++)
				EntryPointToFuncGlobal->DLL_GetLayersBase()->GetPageData(PNumb)->GetLayerData(LNumb)->GetMasterBuff().Free();

			//プログレスバーの更新
			MainProcessing->SetUpdate(ProgressCounter*(LayerNumbInPage+1)*(PNumb+1));
			PNumb++;
		}while(query.next());
	}
	//メモリの開放
	query.clear();

	PNumbForBase=PNumb;
	if(PNumb==0){
		QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_382)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_383)/*"There is no image."*/);
		return false;
	}
	IDataUnit->MImageClassList[SType]->CameraNumb=PNumb;

	//表示エリアの設定ー複数カメラの場合の処理（横並び／縦並び）
	int MaxOffsetX,wMaxOffsetX,MaxOffsetY,wMaxOffsetY;
	MaxOffsetX=IDataUnit->MImageClassList[SType]->ImageList[0]->OffsetX;
	MaxOffsetY=IDataUnit->MImageClassList[SType]->ImageList[0]->OffsetY;
	for(int Cnt=1;Cnt<PNumb;Cnt++){
		MaxOffsetX=(MaxOffsetX>(wMaxOffsetX=IDataUnit->MImageClassList[SType]->ImageList[Cnt]->OffsetX)) ? MaxOffsetX : wMaxOffsetX;
		MaxOffsetY=(MaxOffsetY>(wMaxOffsetY=IDataUnit->MImageClassList[SType]->ImageList[Cnt]->OffsetY)) ? MaxOffsetY : wMaxOffsetY;
	}

	IDataUnit->MImageClassList[SType]->SetMAreaSize(InitW=MaxOffsetX+DotPerLineInImage,InitH=MaxOffsetY+MaxLinesInImage);
	IDataUnit->MImageClassList[SType]->movx=0;
	IDataUnit->MImageClassList[SType]->movy=0;
	IDataUnit->MImageClassList[SType]->repaint();

	//マスター個片エリアの設定ー複数カメラの場合の処理（横並び／縦並び）
	IDataUnit->MImagePieceList[0]	->SetAreaSize(MaxOffsetX+DotPerLineInPage,MaxOffsetY+MaxLinesInPage);
	IDataUnit->NGImagePieceList[0]	->SetAreaSize(MaxOffsetX+DotPerLineInPage,MaxOffsetY+MaxLinesInPage);

	return true;
}

bool RepairStation::Save(QIODevice *file)
{
	int X=x();
	X+=3;
	if(file->write((const char *)&X,sizeof(X))!=sizeof(X))
		return false;

	int Y=y();
//	Y+=29;		//WinXP Style
	Y+=22;		//Win2k Style
	if(file->write((const char *)&Y,sizeof(Y))!=sizeof(Y))
		return false;

	int W=width();
	if(file->write((const char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H=height();
	if(file->write((const char *)&H,sizeof(H))!=sizeof(H))
		return false;

	return true;
}

bool RepairStation::Load(QIODevice *file)
{
	int X;
	if(file->read((char *)&X,sizeof(X))!=sizeof(X))
		return false;

	int Y;
	if(file->read((char *)&Y,sizeof(Y))!=sizeof(Y))
		return false;

	int W;
	if(file->read((char *)&W,sizeof(W))!=sizeof(W))
		return false;

	int H;
	if(file->read((char *)&H,sizeof(H))!=sizeof(H))
		return false;

	setGeometry(X,Y,W,H);
	return true;
}

void RepairStation::closeEvent(QCloseEvent *event)
{
	if(maybeClose()){
/*		if(xmlCont[Front]!=NULL){
			XMLClose(Front);
			delete xmlCont[Front];
		}
		if(xmlCont[Back]!=NULL){
			XMLClose(Back);
			delete xmlCont[Back];
		}
*/
		//スレッドの停止
		tErrNext	.Stop();
		tNGBlink	.Stop();
		tOKWindow	.Stop();

		//RepairSetting.datの書き込み
		if(GetReverseOrderDisplay()!=dwHistoryList	->ui.chReverseOrderDisplay	->isChecked() || GetNotShowHalt()!=chNotShowHalt->isChecked()){
			SetReverseOrderDisplay	(dwHistoryList	->ui.chReverseOrderDisplay	->isChecked());
			SetNotShowHalt			(chNotShowHalt								->isChecked());
			WriteRepairSetting();
		}
		while(tErrNext.isRunning()==true){}

		//画面の位置とロケーションを保存する
		SaveLocation();

		//デバッグログファイルがOpenしている場合、closeする
		if(GetDebugLogFile().isOpen()==true){
			WriteDebugLogFile(LangSolver.GetString(RepairStation_LS,LID_384)/*"File Close. End Application."*/);
			GetDebugLogFile().close();
		}

		//プラグインDLL対応
		if(DLL_GetName!=NULL){
			//フォームを閉じる
			DLL_AllCheckedFormClose();
			DLL_UnloadCommentFormClose();
			DLL_ErrorFormClose();
			DLL_PreNext(true);

			//PCスタンバイをOffにする
			SeqControlParamData->PCStandBy=false;
			//チェックプログラム監視スレッドをSTOP
			DLL_StartProcessCheckThread(false);
			//Waitを置く
			for(time_t t=time(NULL);time(NULL)-t<2;){}
		}
		emit destroyed();
		event->accept();
	}
	else
		event->ignore();
}

void RepairStation::keyPressEvent(QKeyEvent *event)
{
	if(dwNGList->twNGList->selectedItems().count()==0)
		return;

	bool bFKey = true;
	QColor color=dwNGList->twNGList->currentItem()->backgroundColor();

	switch (event->key()){
		case Qt::Key_F1:
			if(color==ColorFKey[0]){
				ExecFunction(0);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=0;
			break;
		case Qt::Key_F2:
			if(color==ColorFKey[1]){
				ExecFunction(1);
				return;
				//bFKey=true;
			}
			else{
				bFKey=false;
			}
			FKey=1;
			break;
		case Qt::Key_F3:
			if(color==ColorFKey[2]){
				ExecFunction(2);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=2;
			break;
		case Qt::Key_F4:
			if(color==ColorFKey[3]){
				ExecFunction(3);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=3;
			break;
		case Qt::Key_F5:
			if(color==ColorFKey[4]){
				ExecFunction(4);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=4;
			break;
		case Qt::Key_F6:
			if(color==ColorFKey[5]){
				ExecFunction(5);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=5;
			break;
		case Qt::Key_F7:
			if(color==ColorFKey[6]){
				ExecFunction(6);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=6;
			break;
		case Qt::Key_F8:
			if(color==ColorFKey[7]){
				ExecFunction(7);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=7;
			break;
		case Qt::Key_F9:
			if(color==ColorFKey[8]){
				ExecFunction(8);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=8;
			break;
		case Qt::Key_F10:
			if(color==ColorFKey[9]){
				ExecFunction(9);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=9;
			break;
		case Qt::Key_F11:
			if(color==ColorFKey[10]){
				ExecFunction(10);
				return;
				//bFKey=true;
			}
			else
				bFKey=false;
			FKey=10;
			break;
		case Qt::Key_Delete:
			if(ColorFKey.contains(color)){
				//戻り値格納用、削除前、削除後の文字列および現在のNG行番号
				QString destStr=QString(/**/"");
				QString deleteXMLStr = CreateFunctionStr(ColorFKey.indexOf(color));
				QString updateXMLStr(/**/"<RFC></RFC>");
				int NGListRow = dwNGList->twNGList->currentRow();
				
				//NG座標取得(データ座標)
				QStringList NGPosStrList = dwNGList->twNGList->item(NGListRow, 0)->text().split(',');
				QPoint NGPos(NGPosStrList[0].toInt(),NGPosStrList[1].toInt());

				//上流下流の判定に基づくバッテン描画分岐処理
				int side = dwNGList->twNGList->item(NGListRow, NGFieldNames.indexOf(/**/"Side"))->text().toInt();
				QByteArray msg;
				QList<QByteArray> sendList;
				switch(side){
				case SideType::Front:
					sendList.append(deleteXMLStr.toLocal8Bit().data());
					FrontMImage->delDrawNGPoint(NGPos);
					FrontMImage->update();
					if(DeleteXMLStr(SideType::Front, deleteXMLStr)){
						QMessageBox::critical(this, "XML Write Error", "XML文の削除が出来ませんでした。");
						return;
					}
					//if(!xmlCont[side]->Client_TagDel(strQNO1, deleteXMLStr.toLocal8Bit().data(), updateXMLStr.toLocal8Bit().data(), GetXMLFile(side), msg)){
					//	QMessageBox::critical(this, "XML Write Error", msg);
					//	return;
					//}
					break;
				case SideType::Back:
					BackMImage->delDrawNGPoint(NGPos);
					BackMImage->repaint();
					if(!xmlCont[side]->Client_TagDel(strQNO2, deleteXMLStr.toLocal8Bit().data(), updateXMLStr.toLocal8Bit().data(), GetXMLFile(side), msg)){
						QMessageBox::critical(this, "XML Write Error", msg);
						return;
					}
					break;
				default:
					return;
					break;
				}
				//XMLデータ文字列に書き込み
				SetRetXMLData(Update,&destStr,&updateXMLStr,&deleteXMLStr);

				//Fキーに合わせた背景色変更
				SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentRow(),twNGListCheckColor);

				//最下部の場合を除いて下へ１つ移動
				if(NGListRow < dwNGList->twNGList->rowCount()-1)
					dwNGList->twNGList->setCurrentCell(NGListRow+1, dwNGList->twNGList->currentColumn());
			}
			return;
			break;
		//case Qt::Key_F12:
		//	if(color==ColorFKey[11]){
		//		ExecFunction(11);
		//		return;
		//		//bFKey=true;
		//	}
		//	else
		//		bFKey=false;
		//	FKey=11;
		//	break;
		case Qt::Key_Escape:
			chNGPointToggled(!MainFrame->ui.chNGPoint->isChecked());
			MainFrame->ui.chNGPoint->setChecked(!MainFrame->ui.chNGPoint->isChecked());
			return;
		case Qt::Key_Enter:
			SlotKeyEnter();
			return;
		default:
			return;
	}
	int DelFKey=FKey;
	QString sISTXML=LangSolver.GetString(RepairStation_LS,LID_385)/*""*/;
	QString sTagSel,sRetDelTag,sRetUpTag;

	// バッテン描画設定
	int NGListRow = dwNGList->twNGList->currentRow();
	int side = dwNGList->twNGList->item(NGListRow, NGFieldNames.indexOf(/**/"Side"))->text().toInt();
	QStringList NGPosStrList = dwNGList->twNGList->item(NGListRow, 0)->text().split(',');
	QPoint NGPos(NGPosStrList[0].toInt(),NGPosStrList[1].toInt());
	switch(side){
	case SideType::Front:
		FrontMImage->addDrawNGPoint(NGPos, ColorFKey[FKey]);
		FrontMImage->repaint();
		break;
	case SideType::Back:
		BackMImage->addDrawNGPoint(NGPos, ColorFKey[FKey]);
		BackMImage->repaint();
		break;
	}

	if(/*bFKey || */color!=twNGListCheckColor){
///		SetRetXMLData(Select,&sISTXML);
		if(!CheckFKey(DelFKey,dwNGList->twNGList->item(dwNGList->twNGList->currentRow(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_386)/*"Side"*/))->text().toInt())){
			ExecFunction(event->key());
			return;
		}
	}
	if(!CheckedFunction(FKey,bFKey,DelFKey,&sRetDelTag,&sRetUpTag,dwNGList->twNGList->item(dwNGList->twNGList->currentRow(),NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_387)/*"Side"*/))->text().toInt()))
		return;

	if(color!=twNGListCheckColor){
		SetRetXMLData(Update,&sISTXML,&sRetUpTag,&sRetDelTag);
		if(bFKey)
			SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentRow(),twNGListCheckColor);
		else
			SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentRow(),ColorFKey[FKey]);
	}
	else{
		SetRetXMLData(Insert,&sISTXML,&sRetUpTag,&sRetDelTag);
		SetColorToTable(dwNGList->twNGList,dwNGList->twNGList->currentRow(),ColorFKey[FKey]);
	}

	qDebug() << GetRetXMLDataList(Front)->at(0);

	//ファンクションキー押下処理
	ExecFunction(event->key());
}

bool RepairStation::maybeClose()
{
	int ret=QMessageBox::information(this, LangSolver.GetString(RepairStation_LS,LID_388)/*"Message"*/,
				LangSolver.GetString(RepairStation_LS,LID_389)/*"Do you want to close the application?"*/,
				QMessageBox::Yes | QMessageBox::Default,
				QMessageBox::Cancel | QMessageBox::Escape);
	if (ret == QMessageBox::Yes)
		return true;
	return false;
}

int RepairStation::ShowMasterTree(bool UpdatesEnabled)
{
	disconnect(MainFrame->ui.trMasterList,SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	MainFrame->ui.trMasterList->clear();
	connect(MainFrame->ui.trMasterList,SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	MainFrame->ui.trMasterList->setUpdatesEnabled(UpdatesEnabled);

	QSqlQuery MainQuery(LangSolver.GetString(RepairStation_LS,LID_390)/*"select FOLDERNAME,REMARK,CATEGORYID from MASTERCATEGORY where PARENTID=0 order by CATEGORYID"*/);
	int Row=0;
	QTreeWidgetItem *RootItem;
	RootItem=new QTreeWidgetItem();
	RootItem->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_391)/*"FOLDERNAME"*/),LangSolver.GetString(RepairStation_LS,LID_392)/*"Root"*/);
	RootItem->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_393)/*"CATEGORYID"*/),QString::number(-1));
	MainFrame->ui.trMasterList->addTopLevelItem(RootItem);
	while(MainQuery.next()){
		QTreeWidgetItem *Item=new QTreeWidgetItem();
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_394)/*"FOLDERNAME"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_395)/*"FOLDERNAME"*/)).toString());
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_396)/*"REMARK"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_397)/*"REMARK"*/)).toString());
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_398)/*"CATEGORYID"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_399)/*"CATEGORYID"*/)).toString());
		RootItem->addChild(Item);
		AddChildTree(Item,&MainQuery.value(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_400)/*"CATEGORYID"*/)));
		Row++;
	}
	return Row;
}

void RepairStation::AddChildTree(QTreeWidgetItem *ParentItem,QVariant *value)
{
	QSqlQuery SubQuery;
	SubQuery.prepare(LangSolver.GetString(RepairStation_LS,LID_401)/*"select FOLDERNAME,REMARK,CATEGORYID from MASTERCATEGORY where PARENTID=? order by CATEGORYID"*/);
	SubQuery.addBindValue(*value);
	SubQuery.exec();
	while(SubQuery.next()){
		QTreeWidgetItem *item=new QTreeWidgetItem();
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_402)/*"FOLDERNAME"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_403)/*"FOLDERNAME"*/)).toString());
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_404)/*"REMARK"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_405)/*"REMARK"*/)).toString());
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_406)/*"CATEGORYID"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(RepairStation_LS,LID_407)/*"CATEGORYID"*/)).toString());
		ParentItem->addChild(item);
		AddChildTree(item,&SubQuery.value(MTFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_408)/*"CATEGORYID"*/)));
	}
}

void RepairStation::SetRetXMLData(SQLType Type,QString *sUpXML,QString *strUpTag,QString *strDelTag)
{
	for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
		int Index = GetListIndex(Cnt);
		if(Index==-1){
			continue;
		}
///		if(sUpXML->isEmpty()){
			*sUpXML=GetRetXMLDataList((SideType)Cnt)->at(Index);
///		}
		switch (Type){
			case Select:
				return;
			case Insert:
				sUpXML->insert(sUpXML->indexOf(LangSolver.GetString(RepairStation_LS,LID_409)/*"</IST>"*/),*strUpTag);
				break;
			case Update:
				sUpXML->replace(*strDelTag,*strUpTag);
				break;
		}
		GetRetXMLDataList((SideType)Cnt)->replace(Index,sUpXML->toLocal8Bit().data());
	}
/*
	int FB=dwNGList->twNGList->item(dwNGList->twNGList->currentRow(),NGFieldNames.indexOf("Side"))->text().toInt();
	int Index=GetListIndex(FB);
	if(sUpXML->isEmpty())
		*sUpXML=GetRetXMLDataList((SideType)FB)->at(Index);

	switch (Type){
		case Select:
			return;
		case Insert:
			sUpXML->insert(sUpXML->indexOf("</IST>"),*strUpTag);
			break;
		case Update:
			sUpXML->replace(*strDelTag,*strUpTag);
			break;
	}
	GetRetXMLDataList((SideType)FB)->replace(Index,sUpXML->toLocal8Bit().data());
*/
}

void RepairStation::SetWindowColor(QColor color)
{
	MainPalette.setColor(QPalette::Window,color);
//	MainFrame		->MFrame		->setAutoFillBackground(true);
//	MainFrame		->MFrame		->setPalette(MainPalette);
//	dwHistoryList	->MDHistoryFrame->setAutoFillBackground(true);
//	dwHistoryList	->MDHistoryFrame->setPalette(MainPalette);
//	dwNGList		->MDNGListFrame	->setAutoFillBackground(true);
//	dwNGList		->MDNGListFrame	->setPalette(MainPalette);

	MainFrame		->setAutoFillBackground(true);
	MainFrame		->setPalette(MainPalette);
	dwHistoryList	->setAutoFillBackground(true);
	dwHistoryList	->setPalette(MainPalette);
	dwNGList		->setAutoFillBackground(true);
	dwNGList		->setPalette(MainPalette);
}

void RepairStation::SetWindowColorDefault()
{
//	MainFrame		->MFrame		->setAutoFillBackground(false);
//	dwHistoryList	->MDHistoryFrame->setAutoFillBackground(false);
//	dwNGList		->MDNGListFrame	->setAutoFillBackground(false);

	//スクロールバーなどに色が残るのを消すための処理
	QColor NowColor=MainPalette.color(QPalette::Window);
	NowColor.setAlpha(-100);
	SetWindowColor(NowColor);

	MainFrame		->setAutoFillBackground(false);
	dwHistoryList	->setAutoFillBackground(false);
	dwNGList		->setAutoFillBackground(false);
}

//ファンクションキーが押された時の処理
void RepairStation::ExecFunction(int KeyName)
{
	//NG画像の保存
	SaveImageFlag=true;
	dwNGInspectionPix->repaint();

	//次のエリアコードのNGリストまで移動
	int CurrentRow		=	dwNGList->twNGList->currentRow();
	int IndexARA		=	NGFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_410)/*"ARA"*/);
	QString AreaName	=	dwNGList->twNGList->item(CurrentRow,IndexARA)->text();

	if(AreaName.isEmpty()){
		if(CurrentRow+1 < dwNGList->twNGList->rowCount()){
			dwNGList->twNGList->selectRow(CurrentRow+1);
			return;
		}
	}
	else{
		int RowCnt=dwNGList->twNGList->rowCount();
		for(int Row = CurrentRow+1; Row < RowCnt; Row++){
			if(dwNGList->twNGList->item(Row,IndexARA)->text()!=AreaName){
				dwNGList->twNGList->selectRow(Row);
				return;
			}
		}
	}
}

//リスト行のヘッダーラベルの数字も逆順対応
void RepairStation::SetRowHeaderLabel(bool Tog)
{
	int RowCnt=dwHistoryList->ui.twHistoryList->rowCount();
	QStringList VerticalHeaderLabels;
	if(Tog){
		for(int Row=RowCnt;Row>0;Row--){
			VerticalHeaderLabels.append(QString::number(Row));
		}
	}
	else{
		for(int Row=1;Row<=RowCnt;Row++){
			VerticalHeaderLabels.append(QString::number(Row));
		}
	}
	dwHistoryList->ui.twHistoryList->setVerticalHeaderLabels(VerticalHeaderLabels);
}

//Show NG Area
void RepairStation::ShowNGArea(bool Tog,int Cnt)
{
	int Col=HFieldNames.indexOf(LangSolver.GetString(RepairStation_LS,LID_411)/*"NG Area"*/);
	int RowCnt=dwHistoryList->ui.twHistoryList->rowCount();
	int Count=min(RowCnt,Cnt);
	if(Tog){
		for(int Cnt=0,Row=RowCnt-1;Cnt<Count;Cnt++,Row--){
			SetDataToTable(dwHistoryList->ui.twHistoryList,Row,Col,HistoryNGColList[Cnt]);
		}
	}
	else{
		for(int Row=0;Row<Count;Row++){
			SetDataToTable(dwHistoryList->ui.twHistoryList,Row,Col,HistoryNGColList[Row]);
		}
	}
}

void RepairStation::LoadLocation()
{
	QFile file(LangSolver.GetString(RepairStation_LS,LID_412)/*"./Window.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!Load(&file)){
			WindowDefault();
		}
		file.close();
	}
	else{
		WindowDefault();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_413)/*"./WindowCentral.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!MainFrame->Load(&file)){
			MainFrameDefault();
		}
		file.close();
	}
	else{
		MainFrameDefault();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_414)/*"./WindowMasterWhole.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!dwMasterImage->Load(&file)){
			dwMasterImageDefault();
		}
		file.close();
	}
	else{
		dwMasterImageDefault();
	}
/*
	file.setFileName("./WindowMasterWhole1.dat");
	if(file.open(QIODevice::ReadOnly)){
		if(!dwMasterImage1->Load(&file))
			dwMasterImage1Default();
		file.close();
	}
	else
		dwMasterImage1Default();

	file.setFileName("./WindowMasterWhole2.dat");
	if(file.open(QIODevice::ReadOnly)){
		if(!dwMasterImage2->Load(&file))
			dwMasterImage2Default();
		file.close();
	}
	else
		dwMasterImage2Default();
*/
	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_415)/*"./WindowMasterPiece.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!dwNGMasterPix->Load(&file)){
			dwNGMasterPixDefault();
		}
		file.close();
	}
	else{
		dwNGMasterPixDefault();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_416)/*"./WindowNGPiece.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!dwNGInspectionPix->Load(&file)){
			dwNGInspectionPixDefault();
		}
		file.close();
	}
	else{
		dwNGInspectionPixDefault();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_417)/*"./WindowHistoryList.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!dwHistoryList->Load(&file)){
			dwHistoryListDefault();
		}
		file.close();
	}
	else{
		dwHistoryListDefault();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_418)/*"./WindowNGList.dat"*/);
	if(file.open(QIODevice::ReadOnly)){
		if(!dwNGList->Load(&file)){
			dwNGListDefault();
		}
		file.close();
	}
	else{
		dwNGListDefault();
	}
}

void RepairStation::SaveLocation()
{
	QFile file(LangSolver.GetString(RepairStation_LS,LID_419)/*"./Window.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_420)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_421)/*"Save error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_422)/*"./WindowCentral.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!MainFrame->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_423)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_424)/*"Save MainWidget error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_425)/*"./WindowMasterWhole.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwMasterImage->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_426)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_427)/*"Save DockMasterWhole error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_428)/*"./WindowMasterWhole1.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwMasterImage1->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_429)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_430)/*"Save DockMasterWhole1 error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_431)/*"./WindowMasterWhole2.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwMasterImage2->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_432)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_433)/*"Save DockMasterWhole2 error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_434)/*"./WindowMasterPiece.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwNGMasterPix->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_435)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_436)/*"Save DockMasterPiece error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_437)/*"./WindowNGPiece.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwNGInspectionPix->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_438)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_439)/*"Save DockNGPiece error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_440)/*"./WindowHistoryList.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwHistoryList->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_441)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_442)/*"Save DockHistoryList error."*/);
		file.close();
	}

	file.setFileName(LangSolver.GetString(RepairStation_LS,LID_443)/*"./WindowNGList.dat"*/);
	if(file.open(QIODevice::WriteOnly)){
		if(!dwNGList->Save(&file))
			QMessageBox::warning(this,LangSolver.GetString(RepairStation_LS,LID_444)/*"Message"*/,LangSolver.GetString(RepairStation_LS,LID_445)/*"Save DockNGList error."*/);
		file.close();
	}
}

void RepairStation::WindowDefault()
{
	setGeometry(3,29,1300,998);
}

void RepairStation::MainFrameDefault()
{
	MainFrame->setMinimumSize(662,280);
	MainFrame->setMaximumSize(662,280);
}

void RepairStation::dwMasterImageDefault()
{
	dwMasterImage->setMinimumWidth(360);
	dwMasterImage->setMaximumWidth(360);
}

void RepairStation::dwMasterImage1Default()
{
	dwMasterImage1->setMinimumWidth(360);
	dwMasterImage1->setMaximumWidth(360);
}

void RepairStation::dwMasterImage2Default()
{
	dwMasterImage2->setMinimumWidth(360);
	dwMasterImage2->setMaximumWidth(360);
//	dwMasterImage2->setMinimumWidth(0);
	dwMasterImage2->setMaximumHeight(0);
}

void RepairStation::dwNGMasterPixDefault()
{
	dwNGMasterPix->setMinimumSize(331,651);
	dwNGMasterPix->setMaximumSize(331,651);
}

void RepairStation::dwNGInspectionPixDefault()
{
	dwNGInspectionPix->setMinimumSize(331,651);
	dwNGInspectionPix->setMaximumSize(331,651);
}

void RepairStation::dwHistoryListDefault()
{
	dwHistoryList->setMinimumSize(240,466);
	dwHistoryList->setMaximumSize(240,466);
}

void RepairStation::dwNGListDefault()
{
	dwNGList->setMinimumSize(240,465);
	dwNGList->setMaximumSize(240,465);
}

void RepairStation::UpdateExec()
{
	pbUpdateClicked();
}

void RepairStation::SetParam(bool ShowSequence)
{
	pbSimulateSequence->setVisible(ShowSequence);

	//作業者選択画面の表示
	WorkerSelectForm *WorkerSelectDialog=new WorkerSelectForm(this);
	GeneralDialog	*D=new GeneralDialog(EntryPointToFuncGlobal->GetLayersBase(),WorkerSelectDialog,this);
	D->exec();
	delete WorkerSelectDialog;
	delete D;
	leWorker->setText(GetWorkerName());
}

void RepairStation::SetWaitTime(int Time)
{
	dwNGList->twNGList->SetWaitTime(Time);
}

NGBlinkThread::NGBlinkThread()
{
	StopFlag	=true;
	ChangeFlag	=false;
	BlinkTime	=500;
}

void NGBlinkThread::run()
{
	LocalNGPointVisible		=true;
	StopFlag				=false;

	QTime	ETime;
	ETime.start();
	int		NowTime=ETime.elapsed();

	while(!StopFlag){
		if(NowTime>=BlinkTime){
			emit SignalRepaint(!LocalNGPointVisible);
			ETime.start();
		}
		if(ChangeFlag){
			emit SignalRepaint(true);
			ChangeFlag=false;
			ETime.start();
		}
		NowTime=ETime.elapsed();
	}
	emit SignalRepaint(true);
}

WindowColorThread::WindowColorThread()
{
	StopFlag	=true;
	ChangeFlag	=true;
	BlinkTime	=500;
	Red=0;
	Green=255;
	Blue=0;
	Alpha=255;
	RGBColor=QColor(Qt::green);
}

void WindowColorThread::run()
{
	StopFlag	=false;
	ChangeFlag	=false;
	Alpha=255;
	while(!StopFlag){
		emit SignalRepaint(RGBColor);
		RGBColor.setAlpha(Alpha-=50);
		if(Alpha<-100)
			break;
		msleep(20);
	}
	RGBColor.setAlpha(-100);
	emit SignalRepaint(RGBColor);
//	ChangeFlag=true;
}
