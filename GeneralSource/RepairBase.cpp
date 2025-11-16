#include "RepairStationResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\RepairBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include <QMessageBox>
#include <QDir>
#include <QBuffer>
#include <QTextStream>
#include "RepairBase.h"
#include "clientmainRepair.h"
#include "ImageDataUnit.h"
#include "XGeneralFunc.h"
#include "hasplib.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDomDocument>
#include "time.h"

//個片コンボボックス
//PieceListEditor::PieceListEditor(QStringList &List,QWidget *widget)
//	:QComboBox(widget)
PieceListEditor::PieceListEditor(QStringList &List)
	:QComboBox()
{
	List.sort();

	for (int i=0,j=0;i<List.count();i++){
		if(List[i]==LangSolver.GetString(RepairBase_LS,LID_461)/*""*/){
			continue;
		}
		insertItem(j,List[i]);
		setItemData(j++,false,Qt::CheckStateRole);
	}

//	populateList();
	setEditable(true);
	setFont(QFont(LangSolver.GetString(RepairBase_LS,LID_462)/*"Helvetica"*/,10));

	connect(this,SIGNAL(activated(int)),this,SLOT(SlotCurIndexChanged(int)));
}

PieceListEditor::~PieceListEditor()
{
//	clear();
}

void PieceListEditor::SlotCurIndexChanged(int Index)
{
	showPopup();
	bool Checked=itemData(Index,Qt::CheckStateRole).toBool();
	setItemData(Index,!(Checked),Qt::CheckStateRole);
	QStringList NGPieceNoList;
	for(int Row=0;Row<count();Row++){
		if(itemData(Row,Qt::CheckStateRole).toBool()==true){
			NGPieceNoList.append(itemText(Row));
		}
	}
	setEditText(NGPieceNoList.join(LangSolver.GetString(RepairBase_LS,LID_463)/*","*/));
}

void PieceListEditor::populateList()
{
}

//NGポイントデータ格納クラス
NGPointList::NGPointList(int X,int Y, const QString &Str)
{
	x=X;
	y=Y;
	colorAlg=Str;
}

NGPointList::~NGPointList()
{
}

//NGポイントデータBase格納クラス
NGPointBaseList::NGPointBaseList()
{
}

NGPointBaseList::~NGPointBaseList()
{
}

//NGPタグデータ格納クラス
NGPTagDataList::NGPTagDataList()
{
}

NGPTagDataList::NGPTagDataList(int X,int Y,QString RAL,int PG)
{
	x	=X;
	y	=Y;
	ral	=RAL;
	pg	=PG;
}

NGPTagDataList::~NGPTagDataList()
{
}

PieceInfoData::PieceInfoData()
{
	PieceCoordinates=NULL;
	DataCount		=0;
}

PieceInfoData::~PieceInfoData()
{
	if(PieceCoordinates!=NULL){
		delete []PieceCoordinates;
	}
}

void PieceInfoData::SetPieceData(RepairBase *parent,const QByteArray *PieceData,QList<ImageInPage *> &ImageList)
{
///	int		NowPage	=parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_464)/*"PAGE=\"*/LangSolver.GetString(RepairBase_LS,LID_465)/*","*/\LangSolver.GetString(RepairBase_LS,LID_466)/*""*/).toInt();
///	char	NowShape=parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_467)/*"AREA=\"*/LangSolver.GetString(RepairBase_LS,LID_468)/*",1).at(0);
///*/	QList<QByteArray> AREAList=parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_469)/*"AREA=\"*/LangSolver.GetString(RepairBase_LS,LID_470)/*","*/\LangSolver.GetString(RepairBase_LS,LID_471)/*""*/).mid(1).split(',');
	int		NowPage	=parent->GetString(PieceData,/**/"PAGE=\"",/**/"\"").toInt();
	char	NowShape=parent->GetString(PieceData,/**/"AREA=\"",1).at(0);
	QList<QByteArray> AREAList=parent->GetString(PieceData,/**/"AREA=\"",/**/"\"").mid(1).split(/**/',');

#ifdef DEBUG
	int OrgOffsetX,OrgOffsetY;
	OrgOffsetX=ImageList[NowPage]->OrgOffsetX;
	OrgOffsetY=ImageList[NowPage]->OrgOffsetY;
	int X1,X2,Y1,Y2;
	X1=AREAList[0].toInt();
	Y1=AREAList[1].toInt();
	X2=AREAList[2].toInt();
	Y2=AREAList[3].toInt();
///	PieceName	=parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_472)/*"PIECENAME=\"*/#LangSolver.GetString(RepairBase_LS,LID_473)/*","*/\LangSolver.GetString(RepairBase_LS,LID_474)/*""*/);
	PieceName	=parent->GetString(PieceData,/**/"PIECENAME=\"#",/**/"\"");
#endif

	//同じ個片名称でどちらも矩形だったら、くっ付けて１つの矩形にする
	if(DataCount>0 && PieceShape=='R' && NowShape=='R'){
//		if((NowPage-PiecePageList.last())==1 && AREAList[0].toInt()==0 && PieceCoordinates[0].Y==AREAList[1].toInt() && PieceCoordinates[1].Y==AREAList[3].toInt()){
//		if((NowPage-PiecePageList.last())==1 && PieceCoordinates[0].Y==AREAList[1].toInt() && PieceCoordinates[1].Y==AREAList[3].toInt()){
		if(PiecePageList.count()==0){
			return;
		}
		int PrePage=PiecePageList.last();
		int NowOrgOffsetY=ImageList[NowPage]->OrgOffsetY;
		int PreOrgOffsetY=ImageList[PrePage]->OrgOffsetY;
		if((NowPage-PrePage)==1 && (AREAList[1].toInt()+NowOrgOffsetY)==(PieceCoordinates[0].wY+PreOrgOffsetY) && (AREAList[3].toInt()+NowOrgOffsetY)==(PieceCoordinates[1].wY+PreOrgOffsetY)){
			PiecePageList.append(NowPage);
			PieceCoordinates[1].X=AREAList[2].toInt();
			PieceCoordinates[0].wY=AREAList[1].toInt();
			PieceCoordinates[1].wY=AREAList[3].toInt();
			QPolygon Polygon(QRect(QPoint(AREAList[0].toInt(),AREAList[1].toInt()),QPoint(AREAList[2].toInt(),AREAList[3].toInt())));
			SetPolygon(NowPage,Polygon);
			return;
		}
	}

	PiecePageList.append(NowPage);
///	PieceName	=parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_475)/*"PIECENAME=\"*/#LangSolver.GetString(RepairBase_LS,LID_476)/*","*/\LangSolver.GetString(RepairBase_LS,LID_477)/*""*/);
	PieceName	=parent->GetString(PieceData,/**/"PIECENAME=\"#",/**/"\"");
	DataCount	=(AREAList.count()>>1);
///	SetPieceShape(parent->GetString(PieceData,LangSolver.GetString(RepairBase_LS,LID_478)/*"AREA=\"*/LangSolver.GetString(RepairBase_LS,LID_479)/*",1).at(0));
	SetPieceShape(parent->GetString(PieceData,/**/"AREA=\"",1).at(0));
	switch(PieceShape){
		case 'R':
		case 'E':
			for(int i=0,j=0;j<AREAList.count();i++){
				PieceCoordinates[i].X=AREAList[j++].toInt();
				PieceCoordinates[i].Y=PieceCoordinates[i].wY=AREAList[j++].toInt();
			}
			break;
		case 'P':
			QPolygon Polygon;
			for(int i=0,j=0;j<AREAList.count();i++){
				PieceCoordinates[i].X=AREAList[j++].toInt();
				PieceCoordinates[i].Y=AREAList[j++].toInt();
				Polygon << QPoint(PieceCoordinates[i].X,PieceCoordinates[i].Y);
			}
			SetPolygon(NowPage,Polygon);
			return;
	}
	QPolygon Polygon(QRect(QPoint(PieceCoordinates[0].X,PieceCoordinates[0].Y),QPoint(PieceCoordinates[1].X,PieceCoordinates[1].Y)));
	SetPolygon(NowPage,Polygon);
}

void PieceInfoData::SetPieceShape(char Shape)
{
	PieceShape	=Shape;
	PieceCoordinates=new PieceInfoCoordinates[DataCount];
/*
	switch(PieceShape){
		case 'R':
		case 'E':
			PieceCoordinates=new PieceInfoCoordinates[DataCount];
			break;
		case 'P':
			PieceCoordinates=new PieceInfoCoordinates[DataCount];
			break;
	}
*/
}

void PieceInfoData::SetPolygon(int Page,QPolygon Polygon)
{
	QPair<int,QPolygon> Pair;
	Pair.first	=Page;
	Pair.second	=Polygon;
	PolygonList.append(Pair);
}

QPolygon PieceInfoData::GetPolygon(int Page)
{
	for(int i=0;i<PolygonList.count();i++){
		if(PolygonList[i].first==Page){
			return PolygonList[i].second;
		}
	}
	return QPolygon();
}

bool PieceInfoData::isInside(int X,int Y,int P)
{
	switch(PieceShape){	
		case 'R':
		case 'E':	//楕円の場合はちゃんと求める必要あり（暫定）
		case 'P':
//			return Polygon.containsPoint(QPoint(X,Y),Qt::OddEvenFill);
			return GetPolygon(P).containsPoint(QPoint(X,Y),Qt::OddEvenFill);
	}
	return false;
}

int PieceInfoData::GetDistanceFromCenter(int X,int Y,int OffsetX1,int OffsetY1,int OffsetX2,int OffsetY2)
{
	if(PieceCoordinates==NULL){
		return -1;
	}
	//Offsetを取得
//	int OffsetX1=IDataUnit->MImageClassList[SType]->ImageList[GetFirstPiecePage()]	->OrgOffsetX;
//	int OffsetY1=IDataUnit->MImageClassList[SType]->ImageList[GetFirstPiecePage()]	->OrgOffsetY;
//	int OffsetX2=IDataUnit->MImageClassList[SType]->ImageList[GetLastPiecePage()]	->OrgOffsetX;
//	int OffsetY2=IDataUnit->MImageClassList[SType]->ImageList[GetLastPiecePage()]	->OrgOffsetY;
	//PieceCoordinates[0]の(X,Y)座標が左上でPieceCoordinates[1]の(X,Y)座標が左下
	int dX,dY;
	if(X<=(dX=PieceCoordinates[0].X+OffsetX1)){
		if(Y<=(dY=PieceCoordinates[0].Y+OffsetY1)){
			return (dX-X)*(dX-X)+(dY-Y)*(dY-Y);
		}
		else if(Y>=(dY=PieceCoordinates[1].Y+OffsetY2)){
			return (dX-X)*(dX-X)+(Y-dY)*(Y-dY);
		}
		else{
			return (dX-X)*(dX-X);
		}
	}
	else if(X>=(dX=PieceCoordinates[1].X+OffsetX2)){
		if(Y<=(dY=PieceCoordinates[0].Y+OffsetY1)){
			return (X-dX)*(X-dX)+(dY-Y)*(dY-Y);
		}
		else if(Y>=(dY=PieceCoordinates[1].Y+OffsetY2)){
			return (X-dX)*(X-dX)+(Y-dY)*(Y-dY);
		}
		else{
			return (X-dX)*(X-dX);
		}
	}
	else{
		if(Y<=(dY=PieceCoordinates[0].Y+OffsetY1)){
			return (dY-Y)*(dY-Y);
		}
		else if(Y>=(dY=PieceCoordinates[1].Y+OffsetY2)){
			return (Y-dY)*(Y-dY);
		}
		else{
			return 0;
		}
	}
	return -1;
}

//XMLのデータ格納クラス
//RepairBase::RepairBase(QWidget *parent, Qt::WindowFlags flags)
RepairBase::RepairBase()
{
	strXML[0]				=strXML[1]				=LangSolver.GetString(RepairBase_LS,LID_480)/*""*/;
	xmlCont[0]				=xmlCont[1]				=NULL;
//	NGPList					=NULL;
	ISTElement[0]			=ISTElement[1]			=NULL;
	NGPTagList[0]			=NGPTagList[1]			=NULL;
	ImgCnt					=NULL;
	BuffPG					=NULL;
	JDTDataList[0]			=JDTDataList[1]			=NULL;
	NGITagList[0]			=NGITagList[1]			=NULL;
	wjdtCount				=0;
	LotIDInType[0]			=LotIDInType[1]			=LangSolver.GetString(RepairBase_LS,LID_481)/*""*/;
	iSide					=0;
	ListFIndex				=ListFIndex				=0;
	FirstXMLContact			=true;
	NGPList[0]				=NGPList[1]				=NULL;
	MasterIDInType[0]		=MasterIDInType[1]		=LangSolver.GetString(RepairBase_LS,LID_482)/*""*/;
	MasterNMInType[0]		=MasterNMInType[1]		=LangSolver.GetString(RepairBase_LS,LID_483)/*""*/;
	LotIDInType[0]			=LotIDInType[1]			=LangSolver.GetString(RepairBase_LS,LID_484)/*""*/;
	LotNMInType[0]			=LotNMInType[1]			=LangSolver.GetString(RepairBase_LS,LID_485)/*""*/;
	CategoryIDInType[0]		=CategoryIDInType[1]	=LangSolver.GetString(RepairBase_LS,LID_486)/*""*/;

	MachineRemarkInType[0]	=MachineRemarkInType[1]	=LangSolver.GetString(RepairBase_LS,LID_487)/*""*/;
	InspectionIDInType[0]	=InspectionIDInType[1]	=LangSolver.GetString(RepairBase_LS,LID_488)/*""*/;
	NGKohenNumbInType[0]	=NGKohenNumbInType[1]	=0;
	NGNumbInType[0]			=NGNumbInType[1]		=0;
	KohenNoInType[0]		=KohenNoInType[1]		=LangSolver.GetString(RepairBase_LS,LID_489)/*""*/;
	NGNoInType[0]			=NGNoInType[1]			=0;
	PCNoInType[0]			=PCNoInType[1]			=0;
	TaiouKohenNumbInType[0]	=TaiouKohenNumbInType[1]=1;
	NGPointXInType[0]		=NGPointXInType[1]		=LangSolver.GetString(RepairBase_LS,LID_490)/*""*/;
	NGPointYInType[0]		=NGPointYInType[1]		=LangSolver.GetString(RepairBase_LS,LID_491)/*""*/;

	JDTDataListCountPage[0]	=JDTDataListCountPage[1]=0;

	SigVolume				=SigBright				=-1;

	iSide					=iSideOld				=Front;

	bReverseOrderDisplay	=false;
	bNextCheck				=false;
	bEnterCheck				=false;
	NotShowHaltFlag			=false;
	bNotShowHalt			=false;
	SumFRowCnt				=SumBRowCnt				=0;
	SumFRowCntInImage		=SumBRowCntInImage		=0;

	PieceInfoDataCount[0]	=PieceInfoDataCount[1]	=0;
	PieceInfoDataList[0]	=PieceInfoDataList[1]	=NULL;

	wErrNextBS				=false;
	wNGBS					=false;
	wBackBS					=false;
	wUnloadDone				=false;
	wMacEmergency			=false;
	FirstUpdateFlag			=true;

	vNGI					=NULL;
	vSide					=NULL;
	vARA					=NULL;
	vIDX					=NULL;
	vIndex					=NULL;
	vRealARA				=NULL;

	cbPieceListEditor		=NULL;;

	NGImageOffset			=0;
	PlusRed					=0;
	PlusGreen				=0;
	PlusBlue				=0;

	//PluginDLL
	DLL_GetName					=NULL;
	DLL_SetLogInfo				=NULL;
	DLL_AppendNGInfo			=NULL;
	DLL_OutputLog				=NULL;
	DLL_IsOutputLog				=NULL;
	DLL_SetIsOutputLog			=NULL;
	DLL_RemoveNGInfo			=NULL;
	DLL_AllCheckedFormShow		=NULL;
	DLL_AllCheckedFormClose		=NULL;
	DLL_UnloadCommentFormShow	=NULL;
	DLL_UnloadCommentFormClose	=NULL;
	DLL_SaveNGImage				=NULL;
	DLL_ClearNGInfoList			=NULL;
	DLL_PreNext					=NULL;
	DLL_ErrorFormShow			=NULL;
	DLL_ErrorFormClose			=NULL;
	DLL_OKCheckFormShow			=NULL;
	DLL_OKCheckFormClose		=NULL;
	DLL_GetThreadInstance		=NULL;
	DLL_SaveLotNameFile			=NULL;
	DLL_GetReviewEnable			=NULL;
	DLL_SetReviewEnable			=NULL;
	DLL_IsAllCheckedFormShow	=NULL;
	DLL_IsUnloadCommentFormShow	=NULL;
	DLL_IsPreNext				=NULL;
	DLL_IsErrorFormShow			=NULL;
	DLL_SetMessageFormLabel		=NULL;
	DLL_SetMessageForm			=NULL;
	DLL_MessageFormShow			=NULL;
	DLL_MessageFormClose		=NULL;
	DLL_SaveHistoryList			=NULL;
	DLL_GetShowPickupForm		=NULL;
	DLL_GetShowPickupEnable		=NULL;
	DLL_SetShowPickupEnable		=NULL;
	DLL_SetLogInfoHDNameList	=NULL;
	DLL_StartProcessCheckThread	=NULL;
	DLL_GetCheckThreadInstance	=NULL;

	DLL_SetMMCSettingList		=NULL;
	DLL_GetShowOKMsg			=NULL;
	DLL_GetShowNGArea			=NULL;
	DLL_GetPickupNGAreaNumbA	=NULL;
	DLL_GetPickupNGAreaNumbB	=NULL;
	DLL_GetPickupNGAreaNumbC	=NULL;
	DLL_GetNotShowEID			=NULL;
	DLL_SetMMCParameter			=NULL;
	DLL_GetOKDoubleDone			=NULL;
	DLL_GetNGListControl		=NULL;
}

RepairBase::~RepairBase()
{
	for(int Cnt=0;Cnt<2;Cnt++){
		if(xmlCont[Cnt]!=NULL)
			delete xmlCont[Cnt];
	}
}

bool RepairBase::XMLConnection(QString strXMLFile,int Side)
{
	if(FirstXMLContact){
		QStringList XMLConnectionList;
		if(LoadFile(strXMLFile,XMLConnectionList)==false)
			return false;
		if(XMLConnectionList.count()<3)
			return false;
		HostName=XMLConnectionList.at(0);		//host
		port	=XMLConnectionList.at(1);		//port
		XMLFilePath	=XMLConnectionList.at(2);	//path
		XMLFileDir	=XMLFilePath.mid(XMLFilePath.lastIndexOf(LangSolver.GetString(RepairBase_LS,LID_492)/*"/"*/)+1);
		FirstXMLContact=false;
	}
	if(xmlCont[Side]!=NULL){
		XMLClose(Side);
		delete xmlCont[Side];
	}

	//Waitを置く
	for(time_t t=time(NULL);time(NULL)-t<1;){}

	xmlCont[Side]=new ClientMain(HostName,port);
	if(!xmlCont[Side]->Client_Connect(Msg)){
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_493)/*"Connect Error"*/),Msg;
		return false;
	}
/*
///////////デバッグ用直打ち////////////////////////////
	if(Side==Front)
		XMLFilePath=QByteArray("H:/Data/137-LOTN8.DBXML");
	else
		XMLFilePath=QByteArray("H:/Data/138-LOTN8.DBXML");
///////////////////////////////////////////////////////

	if(!xmlCont[Side]->Client_MasterStart(XMLFilePath.toLocal8Bit().data(),Msg,ClientNo)){
		QMessageBox::information(&QWidget(),QObject::tr("Start Error"),Msg);
		return false;
	}
//	tXMLAppend.SetXMLClient(xmlCont);
//	tXMLAppend.SetXMLFile(&XMLFile);
	SetXMLFile(Side,&XMLFilePath);
*/
	return true;
}

bool RepairBase::XMLRetryConnection(int Side)
{
	if(xmlCont[Side]!=NULL){
		return true;
	}
	xmlCont[Side]=new ClientMain(HostName,port);
	if(!xmlCont[Side]->Client_Connect(Msg)){
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_494)/*"Connect Error"*/),Msg;
		return false;
	}
	return true;
}

bool RepairBase::LoadFile(QString strPath,QStringList &strList)
{
	strList.clear();
	QFile	mfile(strPath);
	if(mfile.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&mfile);
		QString myString;
		while (!mystream.atEnd()){
			myString=mystream.readLine();
			strList << myString;
		}
		mfile.close();
	}
	else{
		QMessageBox::warning(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_495)/*"Message"*/,strPath + LangSolver.GetString(RepairBase_LS,LID_496)/*" is not found."*/);
		return false;
	}
	return true;
}

bool RepairBase::SaveFile(QString strPath,QStringList *strList)
{
	QFile	mfile(strPath);
	if(mfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&mfile);
		for(int Cnt=0;Cnt<strList->count();Cnt++){
///			mystream << strList->at(Cnt) << LangSolver.GetString(RepairBase_LS,LID_497)/*"\n"*/;
			mystream << strList->at(Cnt) << endl;
		}
		mfile.close();
	}
	else{
		QMessageBox::warning(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_498)/*"Message"*/,strPath + LangSolver.GetString(RepairBase_LS,LID_499)/*" is open error."*/);
		return false;
	}
	return true;
}

void RepairBase::WriteRepairSetting()
{
	RepairSettingList.clear();
	RepairSettingList << MasterDir;														//MasterData Directory
	RepairSettingList << QString::number(bNGBlink);										//NG Blink Enable Check
	RepairSettingList << QString::number(tNGBlink.BlinkTime);							//NG Blink Time
	RepairSettingList << QString::number(IDataUnit->NGImagePieceList[0]->NGMarkSize);	//NG Mark Size
	RepairSettingList << QString::number(CheckedNumb);									//NG Sort Check
	RepairSettingList << QString::number(bShowOK);										//NG Show OK Check
	RepairSettingList << QString::number(ImgRate);										//Master Image Resolution
	RepairSettingList << QString::number(NGWaitTime);									//NG Wait time
	RepairSettingList << QString::number(SigVolume);									//Sigmoid Volume
	RepairSettingList << QString::number(SigBright);									//Sigmoid Brightness
	RepairSettingList << QString::number(bReverseOrderDisplay);							//Reverse Order Display Check
	RepairSettingList << QString::number(bNextCheck);									//Next Check
	RepairSettingList << QString::number(bEnterCheck);									//Enter Check
	RepairSettingList << QString::number(bNotShowHalt);									//Not ShowHaltFlag
	RepairSettingList << QString::number(bEachPieces);									//Each Pieces Check
	RepairSettingList << QString::number(MImageSplitter);								//Master Image Splitter Check
	RepairSettingList << PieceColorString;												//Piece Color String
	RepairSettingList << QString::number(bEnableNGPieceChange);							//Enable NG Piece Change Check
	RepairSettingList << SaveDirNGImage;												//Save NG Image Directory
	RepairSettingList << QString::number(bOutputDebugLog);								//Output Debug Log Check
	RepairSettingList << QString::number(bOutputXMLData);								//Output XML Data Check
	RepairSettingList << QString::number(bShowInsDataMsg);								//Show Inspection Data Message Check
	RepairSettingList << QString::number(ListScrollRowCnt);								//List Scroll Row Count
	RepairSettingList << OnlyFColor;													//Only F Color
	RepairSettingList << OnlyBColor;													//Only B Color
	RepairSettingList << FBColor;														//FB Color
	RepairSettingList << QString::number(NGImageOffset);								//NGImage Offset
	RepairSettingList << QString::number(PlusRed);										//Plus Red
	RepairSettingList << QString::number(PlusGreen);									//Plus Green
	RepairSettingList << QString::number(PlusBlue);										//Plus Blue
	SaveFile(LangSolver.GetString(RepairBase_LS,LID_500)/*"./RepairSetting.dat"*/,&RepairSettingList);
}

//bool RepairBase::XMLTagSelect(QString *strQueryXml,QStringList *selList,int iParent)
bool RepairBase::XMLTagSelect(QString *strQueryXml,QList<QByteArray> *selList,int iParent,int Side)
{
	//SELECT
//	if(!xmlCont->Client_TagSelect(*strQueryXml,XMLFile,Msg,*selList,iParent)){
//	if(!xmlCont->Client_TagSelect(*strQueryXml,XMLFile,QString::number(iParent),Msg,*selList)){	//070903
	if(!xmlCont[Side]->Client_TagSelect(strQueryXml->toLocal8Bit().data(),XMLFile[Side],QByteArray::number(iParent),Msg,*selList)){	//070903
		if(Msg==LangSolver.GetString(RepairBase_LS,LID_501)/*"NoData"*/)
			return true;
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_502)/*"Select Error"*/),Msg;
		return false;
	}
	return true;
}

bool RepairBase::XMLTagToTagSelect(QList<QByteArray> *strQueryXmlList,QList<QByteArray> *selList,int Side)
{
	//TagSELECT
//	if(!xmlCont->Client_TagToTagSelect(*strQueryXmlList,XMLFile,Msg,*selList,iParent)){
	if(!xmlCont[Side]->Client_TagToTagSelect(*strQueryXmlList,XMLFile[Side],Msg,*selList)){
		if(Msg==LangSolver.GetString(RepairBase_LS,LID_503)/*"NoData"*/)
			return true;
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_504)/*"Select Error"*/,Msg);
		return false;
	}
	return true;
}

bool RepairBase::XMLSelect(QByteArray *strTag,QList<QByteArray> *selList,int Side)
{
	//XMLSELECT
	if(!xmlCont[Side]->Client_Select(*strTag,XMLFile[Side],Msg,*selList)){
		if(Msg==LangSolver.GetString(RepairBase_LS,LID_505)/*"NoData"*/)
			return true;
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_506)/*"Select Error"*/,Msg);
		return false;
	}
	return true;
}

bool RepairBase::XMLLotGet(QString *MasterCode,QList<QByteArray> *selList,int Side)
{
	//XMLLotGet
	if(!xmlCont[Side]->Client_LotGet(XMLFilePath.toLocal8Bit().data(),MasterCode->toLocal8Bit().data(),Msg,*selList)){
		if(Msg==LangSolver.GetString(RepairBase_LS,LID_507)/*"NoData"*/)
			return true;
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_508)/*"Lot Select Error"*/,Msg);
		return false;
	}
	return true;
}

bool RepairBase::XMLMasterStart(QString *MasterCode,QString *LotID,int Side)
{
	QString strXMLFilePath;
///	strXMLFilePath=XMLFilePath + LangSolver.GetString(RepairBase_LS,LID_509)/*"/"*/ + (*MasterCode) + LangSolver.GetString(RepairBase_LS,LID_510)/*"-LOT"*/ + (*LotID) + LangSolver.GetString(RepairBase_LS,LID_511)/*".DBXML"*/;
	strXMLFilePath=XMLFilePath + /**/"/" + (*MasterCode) + /**/"-LOT" + (*LotID) + /**/".DBXML";

	//リトライ処理
	for(time_t t=time(NULL);time(NULL)-t<10;){
		if(!xmlCont[Side]->Client_MasterStart(strXMLFilePath.toLocal8Bit().data(),Msg,ClientNo[Side])){
			if(Msg==LangSolver.GetString(RepairBase_LS,LID_512)/*"Closing"*/){
				//Waitを置く
				for(time_t t=time(NULL);time(NULL)-t<1;){}
				continue;
			}
//			else if(Msg=="File not found"){
			else{
				QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_513)/*"Start Error"*/,Msg);
				return false;
			}
		}
		break;
	}
	if(Msg==LangSolver.GetString(RepairBase_LS,LID_514)/*"Closing"*/)
		return false;

	SetXMLFile(Side,&strXMLFilePath);
	return true;
}

bool RepairBase::XMLClose(int Side)
{
	//CLOSE
	if(!xmlCont[Side]->Client_Close(Msg)){
		if(Msg!=LangSolver.GetString(RepairBase_LS,LID_515)/*"Success"*/){
			QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_516)/*"Close Error"*/,Msg);
			return false;
		}
	}
	return true;
}

bool RepairBase::XMLLotGetClose(int Side)
{
	//LotGet CLOSE
	if(!xmlCont[Side]->Client_LotGetClose(Msg)){
		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_517)/*"LotGetClose Error"*/,Msg);
		return false;
	}
	return true;
}

int RepairBase::CheckXMLDataList(SideType Type,QList<QByteArray> *RetXMLData)
{
	//XMLデータを差し替える前に、直近のデータ（IST）２件をチェックする
	int Ret=0;
	if(Type==Front){
		if(RetXMLFDataList.count()>0 && RetXMLData->count()>0){
			PreINM=GetString(&RetXMLFDataList.last(),LangSolver.GetString(RepairBase_LS,LID_518)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_519)/*"</INM>"*/).toInt();
			CurINM=GetString(&RetXMLData->last(),LangSolver.GetString(RepairBase_LS,LID_520)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_521)/*"</INM>"*/).toInt();
			//INMが同じ場合
			if(PreINM==CurINM){
				Ret|=0x04;
			}
			//INMが飛んだ場合
			else if((PreINM+1)!=CurINM){
				Ret|=0x08;
			}
			//NGPタグ以下が同じ場合
			if(GetString(&RetXMLFDataList.last(),LangSolver.GetString(RepairBase_LS,LID_522)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_523)/*""*/)==GetString(&RetXMLData->last(),LangSolver.GetString(RepairBase_LS,LID_524)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_525)/*""*/)){
				Ret|=0x10;
			}
		}
	}
	else{
		if(RetXMLBDataList.count()>0 && RetXMLData->count()>0){
			PreINM=GetString(&RetXMLBDataList.last(),LangSolver.GetString(RepairBase_LS,LID_526)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_527)/*"</INM>"*/).toInt();
			CurINM=GetString(&RetXMLData->last(),LangSolver.GetString(RepairBase_LS,LID_528)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_529)/*"</INM>"*/).toInt();
			//INMが同じ場合
			if(PreINM==CurINM){
				Ret|=0x04;
			}
			//INMが飛んだ場合
			else if((PreINM+1)!=CurINM){
				Ret|=0x08;
			}
			if(GetString(&RetXMLBDataList.last(),LangSolver.GetString(RepairBase_LS,LID_530)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_531)/*""*/)==GetString(&RetXMLData->last(),LangSolver.GetString(RepairBase_LS,LID_532)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_533)/*""*/)){
				Ret|=0x10;
			}
		}
	}
	return Ret;
}

int RepairBase::CheckXMLData(QByteArray &PreStrXML,const QByteArray &CurStrXML)
{
	//XMLデータを差し替える前に、直近のデータ（IST）２件をチェックする
	int Ret=0;
	if(PreStrXML.isEmpty()==false && CurStrXML.isEmpty()==false){
		PreINM=GetString(&PreStrXML,LangSolver.GetString(RepairBase_LS,LID_534)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_535)/*"</INM>"*/).toInt();
		CurINM=GetString(&CurStrXML,LangSolver.GetString(RepairBase_LS,LID_536)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_537)/*"</INM>"*/).toInt();
		if(PreINM==-1 || CurINM==-1){
			return Ret;
		}
		//INMが同じ場合
		if(PreINM==CurINM){
			Ret|=0x04;
		}
		//INMが飛んだ場合
		else if((PreINM+1)!=CurINM){
			Ret|=0x08;
		}
		//NGPタグ以下が同じ場合
		if(PreStrXML.contains(LangSolver.GetString(RepairBase_LS,LID_538)/*"<NGP "*/)==true && CurStrXML.contains(LangSolver.GetString(RepairBase_LS,LID_539)/*"<NGP "*/)==true){
			if(GetString(&PreStrXML,LangSolver.GetString(RepairBase_LS,LID_540)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_541)/*""*/)==GetString(&CurStrXML,LangSolver.GetString(RepairBase_LS,LID_542)/*"<NGP "*/,LangSolver.GetString(RepairBase_LS,LID_543)/*""*/)){
				Ret|=0x10;
			}
		}
	}
	return Ret;
}

//void RepairBase::SetRetXMLDataList(SideType Type,QList<QByteArray> *RetXMLData)
void RepairBase::SetRetXMLDataList(int Type,QList<QByteArray> *RetXMLData)
{
	//EIDでソート
	ComSortXML(RetXMLData->count(),*RetXMLData);

	if(Type==Front){
		RetXMLFDataList=*RetXMLData;
	}
	else{
		RetXMLBDataList=*RetXMLData;
	}
}

QList<QByteArray> *RepairBase::GetRetXMLDataList(SideType Type)
{
	if(Type==Front)
		return &RetXMLFDataList;
	else
		return &RetXMLBDataList;
}

void RepairBase::SetRetPCEDataList(SideType Type,QList<QByteArray> *RetPCEData)
{
	if(Type==Front)
		RetPCEFDataList=*RetPCEData;
	else
		RetPCEBDataList=*RetPCEData;
}

QList<QByteArray> *RepairBase::GetRetPCEDataList(SideType Type)
{
	if(Type==Front)
		return &RetPCEFDataList;
	else
		return &RetPCEBDataList;
}
/*
QString *RepairBase::GetRetXMLData(SideType Type,int Index)
{
	if(Type==Front)
		return &RetXMLFDataList[Index];
	else
		return &RetXMLBDataList[Index];
}
*/
//テーブルリスト１項目にデータをセット
void RepairBase::SetDataToTable(QTableWidget *W,int row,int col,QVariant value)
{
	if(value.isNull())
		value=LangSolver.GetString(RepairBase_LS,LID_544)/*""*/;
	W->model()->setData(W->model()->index(row,col),value);
}

//テーブルリスト１項目にデータと背景色をセット
void RepairBase::SetDataToTable(QTableWidget *W,int row,int col,QVariant value,QColor Color)
{
	if(value.isNull())
		value=LangSolver.GetString(RepairBase_LS,LID_545)/*""*/;
	W->model()->setData(W->model()->index(row,col),value);

	if(W->isColumnHidden(col))
		return;
	W->item(row,col)->setBackgroundColor(Color);
}

//裏表の両方のデータを表示する
void RepairBase::SetBothDataToTable(QTableWidget *W)
{
	//一旦表裏の合計行を確保する
	int SumRow;
	W->clearContents();
	W->setRowCount(SumRow=(GetRetXMLDataList(Front)->count()+GetRetXMLDataList(Back)->count()));

	if(SumRow==0)
		return;

	int FrontCnt=0,BackCnt=0;
	int FrontEID,BackEID;
	int Row;

	if(NotShowHaltFlag==false){
		for(Row=0;Row<SumRow;Row++){
			//表側と裏側で検査ID(EID)を比較
			if((FrontCnt<GetRetXMLDataList(Front)->count() && BackCnt==GetRetXMLDataList(Back)->count())){
				//表側のデータを表示
				SetXMLDataToTable(W,Row,FrontCnt,Front,twHistoryFrontColor);
				if((++FrontCnt)==GetRetXMLDataList(Front)->count())
					break;
			}
			else if((FrontCnt==GetRetXMLDataList(Front)->count() && BackCnt<GetRetXMLDataList(Back)->count())){
				//裏側のデータを表示
				SetXMLDataToTable(W,Row,BackCnt,Back,twHistoryBackColor);
				if((++BackCnt)==GetRetXMLDataList(Back)->count())
					break;
			}
	///		else if((FrontEID=GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_546)/*"EID=\"*/LangSolver.GetString(RepairBase_LS,LID_547)/*","*/\LangSolver.GetString(RepairBase_LS,LID_548)/*""*/).toInt())<(BackEID=GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),LangSolver.GetString(RepairBase_LS,LID_549)/*"EID=\"*/LangSolver.GetString(RepairBase_LS,LID_550)/*","*/\LangSolver.GetString(RepairBase_LS,LID_551)/*""*/).toInt())){
			else if((FrontEID=GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),/**/"EID=\"",/**/"\"").toInt())<(BackEID=GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),/**/"EID=\"",/**/"\"").toInt())){
				//表側のデータを表示
				SetXMLDataToTable(W,Row,FrontCnt,Front,twHistoryFrontColor);
				FrontCnt++;
			}
			else if(FrontEID>BackEID){
				//裏側のデータを表示
				SetXMLDataToTable(W,Row,BackCnt,Back,twHistoryBackColor);
				BackCnt++;
			}
			else{
				//両面のデータを表示
				for(int Col=0;Col<W->columnCount();Col++){
					QString HeaderLabel=W->horizontalHeaderItem(Col)->text();
					if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_552)/*"Key"*/){
	///					SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_553)/*"EID=\"*/LangSolver.GetString(RepairBase_LS,LID_554)/*","*/\LangSolver.GetString(RepairBase_LS,LID_555)/*""*/).rightJustified(8,'0'),twHistoryBothColor);
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),/**/"EID=\"",/**/"\"").rightJustified(8,'0'),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_556)/*"NGP"*/){
						SetDataToTable(W,Row,Col,GetRetXMLDataList(Front)->at(FrontCnt).count(LangSolver.GetString(RepairBase_LS,LID_557)/*"<NGP"*/)+GetRetXMLDataList(Back)->at(BackCnt).count(LangSolver.GetString(RepairBase_LS,LID_558)/*"<NGP"*/),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_559)/*"TIM"*/){
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_560)/*"<TIM>"*/,LangSolver.GetString(RepairBase_LS,LID_561)/*"</TIM>"*/),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_562)/*"QNO1"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_563)/*""*/,LangSolver.GetString(RepairBase_LS,LID_564)/*":"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_565)/*"QNO2"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),LangSolver.GetString(RepairBase_LS,LID_566)/*""*/,LangSolver.GetString(RepairBase_LS,LID_567)/*":"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_568)/*"RES1"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_569)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_570)/*"</RES>"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_571)/*"RES2"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),LangSolver.GetString(RepairBase_LS,LID_572)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_573)/*"</RES>"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_574)/*"Key1"*/)
						SetDataToTable(W,Row,Col,FrontCnt,twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_575)/*"Key2"*/)
						SetDataToTable(W,Row,Col,BackCnt,twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_576)/*"INM"*/){
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_577)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_578)/*"</INM>"*/),twHistoryBothColor);
					}
					else	//EID
	///					SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),HeaderLabel + LangSolver.GetString(RepairBase_LS,LID_579)/*"=\"*/LangSolver.GetString(RepairBase_LS,LID_580)/*","*/\LangSolver.GetString(RepairBase_LS,LID_581)/*""*/),twHistoryBothColor);
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),HeaderLabel + /**/"=\"",/**/"\""),twHistoryBothColor);
				}
				FrontCnt++;
				BackCnt++;
				if(FrontCnt==GetRetXMLDataList(Front)->count() && BackCnt==GetRetXMLDataList(Back)->count())
					break;
			}
		}
	}
	else{
		//HALTは表示しない
		for(Row=0;Row<SumRow;Row++){
			//?\???A?????A????CID(EID)?d?a?r
			if((FrontCnt<GetRetXMLDataList(Front)->count() && BackCnt==GetRetXMLDataList(Back)->count())){
				if(GetRetXMLDataList(Front)->at(FrontCnt).contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Front)->at(FrontCnt).contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(Front)->removeAt(FrontCnt);
					Row--;
					continue;
				}
				//?\???I?f?[?^?d?\?|
				SetXMLDataToTable(W,Row,FrontCnt,Front,twHistoryFrontColor);
				if((++FrontCnt)==GetRetXMLDataList(Front)->count())
					break;
			}
			else if((FrontCnt==GetRetXMLDataList(Front)->count() && BackCnt<GetRetXMLDataList(Back)->count())){
				if(GetRetXMLDataList(Back)->at(BackCnt).contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Back)->at(BackCnt).contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(Back)->removeAt(BackCnt);
					Row--;
					continue;
				}
				//?????I?f?[?^?d?\?|
				SetXMLDataToTable(W,Row,BackCnt,Back,twHistoryBackColor);
				if((++BackCnt)==GetRetXMLDataList(Back)->count())
					break;
			}
			else if((FrontEID=GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),/**/"EID=\"",/**/"\"").toInt())<(BackEID=GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),/**/"EID=\"",/**/"\"").toInt())){
				if(GetRetXMLDataList(Front)->at(FrontCnt).contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Front)->at(FrontCnt).contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(Front)->removeAt(FrontCnt);
					Row--;
					continue;
				}
				//?\???I?f?[?^?d?\?|
				SetXMLDataToTable(W,Row,FrontCnt,Front,twHistoryFrontColor);
				FrontCnt++;
			}
			else if(FrontEID>BackEID){
				if(GetRetXMLDataList(Back)->at(BackCnt).contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Back)->at(BackCnt).contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(Back)->removeAt(BackCnt);
					Row--;
					continue;
				}
				//?????I?f?[?^?d?\?|
				SetXMLDataToTable(W,Row,BackCnt,Back,twHistoryBackColor);
				BackCnt++;
			}
			else{
				if(GetRetXMLDataList(Front)	->at(FrontCnt)	.contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Front)	->at(FrontCnt)	.contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)
				|| GetRetXMLDataList(Back)	->at(BackCnt)	.contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(Back)	->at(BackCnt)	.contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(Front)->removeAt(FrontCnt);
					GetRetXMLDataList(Back)	->removeAt(BackCnt);
					Row--;
					continue;
				}
				//両面のデータを表示
				for(int Col=0;Col<W->columnCount();Col++){
					QString HeaderLabel=W->horizontalHeaderItem(Col)->text();
					if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_552)/*"Key"*/){
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),/**/"EID=\"",/**/"\"").rightJustified(8,'0'),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_556)/*"NGP"*/){
						SetDataToTable(W,Row,Col,GetRetXMLDataList(Front)->at(FrontCnt).count(LangSolver.GetString(RepairBase_LS,LID_557)/*"<NGP"*/)+GetRetXMLDataList(Back)->at(BackCnt).count(LangSolver.GetString(RepairBase_LS,LID_558)/*"<NGP"*/),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_559)/*"TIM"*/){
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_560)/*"<TIM>"*/,LangSolver.GetString(RepairBase_LS,LID_561)/*"</TIM>"*/),twHistoryBothColor);
					}
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_562)/*"QNO1"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_563)/*""*/,LangSolver.GetString(RepairBase_LS,LID_564)/*":"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_565)/*"QNO2"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),LangSolver.GetString(RepairBase_LS,LID_566)/*""*/,LangSolver.GetString(RepairBase_LS,LID_567)/*":"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_568)/*"RES1"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_569)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_570)/*"</RES>"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_571)/*"RES2"*/)
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Back)->at(BackCnt)),LangSolver.GetString(RepairBase_LS,LID_572)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_573)/*"</RES>"*/),twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_574)/*"Key1"*/)
						SetDataToTable(W,Row,Col,FrontCnt,twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_575)/*"Key2"*/)
						SetDataToTable(W,Row,Col,BackCnt,twHistoryBothColor);
					else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_576)/*"INM"*/){
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),LangSolver.GetString(RepairBase_LS,LID_577)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_578)/*"</INM>"*/),twHistoryBothColor);
					}
					else	//EID
						SetDataToTable(W,Row,Col,GetString(&QString(GetRetXMLDataList(Front)->at(FrontCnt)),HeaderLabel + /**/"=\"",/**/"\""),twHistoryBothColor);
				}
				FrontCnt++;
				BackCnt++;
				if(FrontCnt==GetRetXMLDataList(Front)->count() && BackCnt==GetRetXMLDataList(Back)->count())
					break;
			}
		}
	}
	W->setRowCount(Row+1);
}

void RepairBase::SetXMLDataToTable(QTableWidget *W,int Row,int Index,SideType Type,QColor FieldColor)
{
	//XMLデータを表示
	QString Str;
	QString DDD;
	for(int Col=0;Col<W->columnCount();Col++){
		QString HeaderLabel=W->horizontalHeaderItem(Col)->text();
		if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_582)/*"Key"*/){
//			SetDataToTable(W,Row,Col,QString::number(Row).rightJustified(8,'0'),FieldColor);
///			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_583)/*"EID=\"*/LangSolver.GetString(RepairBase_LS,LID_584)/*","*/\LangSolver.GetString(RepairBase_LS,LID_585)/*""*/).rightJustified(8,'0'),FieldColor);
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),/**/"EID=\"",/**/"\"").rightJustified(8,'0'),FieldColor);
		}
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_586)/*"NGP"*/)
			SetDataToTable(W,Row,Col,GetRetXMLDataList(Type)->at(Index).count(LangSolver.GetString(RepairBase_LS,LID_587)/*"<NGP"*/),FieldColor);
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_588)/*"TIM"*/)
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_589)/*"<TIM>"*/,LangSolver.GetString(RepairBase_LS,LID_590)/*"</TIM>"*/),FieldColor);
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_591)/*"RES1"*/ && Type==Front)
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_592)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_593)/*"</RES>"*/),FieldColor);
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_594)/*"RES2"*/ && Type==Back)
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_595)/*"<RES>"*/,LangSolver.GetString(RepairBase_LS,LID_596)/*"</RES>"*/),FieldColor);
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_597)/*"QNO1"*/){
			if(Type==Front)
				SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_598)/*""*/,LangSolver.GetString(RepairBase_LS,LID_599)/*":"*/),FieldColor);
			else
				SetDataToTable(W,Row,Col,-1,FieldColor);
		}
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_600)/*"QNO2"*/){
			if(Type==Back)
				SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_601)/*""*/,LangSolver.GetString(RepairBase_LS,LID_602)/*":"*/),FieldColor);
			else
				SetDataToTable(W,Row,Col,-1,FieldColor);
		}
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_603)/*"Key1"*/){
			if(Type==Front)
				SetDataToTable(W,Row,Col,Index,FieldColor);
			else
				SetDataToTable(W,Row,Col,-1,FieldColor);
		}
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_604)/*"Key2"*/){
			if(Type==Back)
				SetDataToTable(W,Row,Col,Index,FieldColor);
			else
				SetDataToTable(W,Row,Col,-1,FieldColor);
		}
		else if(HeaderLabel==LangSolver.GetString(RepairBase_LS,LID_605)/*"INM"*/){
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),LangSolver.GetString(RepairBase_LS,LID_606)/*"<INM>"*/,LangSolver.GetString(RepairBase_LS,LID_607)/*"</INM>"*/),FieldColor);
		}
		else{	//EID
///			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),HeaderLabel + LangSolver.GetString(RepairBase_LS,LID_608)/*"=\"*/LangSolver.GetString(RepairBase_LS,LID_609)/*","*/\LangSolver.GetString(RepairBase_LS,LID_610)/*""*/),FieldColor);
			SetDataToTable(W,Row,Col,GetString(&GetRetXMLDataList(Type)->at(Index),HeaderLabel + /**/"=\"",/**/"\""),FieldColor);
		}
	}
}

void RepairBase::SetColorToTable(QTableWidget *W,int Row,QColor FieldColor)
{
//	for(int Col=0;!W->isColumnHidden(Col);Col++)
	for(int Col=0;Col<W->columnCount();Col++){
		if(W->isColumnHidden(Col)){
			continue;
		}
		if(W->rowCount()>Row){
			W->item(Row,Col)->setBackgroundColor(FieldColor);
		}
	}
}

//文字列から目的のデータを切り取る（QString）
QString RepairBase::GetString(const QString *value,QString FirstStr,QString EndStr,int Index)
{
	int FirstIndex,wFirstIndex=0;
	int EndIndex,wEndIndex;
	for(int Cnt=0;Cnt<=Index;Cnt++,wFirstIndex=EndIndex+EndStr.length()){
		if(FirstStr==LangSolver.GetString(RepairBase_LS,LID_611)/*""*/)
			FirstIndex=0;
		else if((FirstIndex=value->indexOf(FirstStr,wFirstIndex))==-1)
			return LangSolver.GetString(RepairBase_LS,LID_612)/*""*/;
		FirstIndex+=FirstStr.length();
		if(EndStr==LangSolver.GetString(RepairBase_LS,LID_613)/*""*/)
			EndIndex=FirstIndex-1;
		else if((EndIndex=value->indexOf(EndStr,FirstIndex))==-1)
			return LangSolver.GetString(RepairBase_LS,LID_614)/*""*/;
	}
	return value->mid(FirstIndex,EndIndex-FirstIndex);
}

//文字列から目的のデータを切り取る（QByteArray）
QByteArray RepairBase::GetString(const QByteArray *value,QString FirstStr,QString EndStr,int Index)
{
	int FirstIndex,wFirstIndex=0;
	int EndIndex,wEndIndex;
	for(int Cnt=0;Cnt<=Index;Cnt++,wFirstIndex=EndIndex+EndStr.length()){
		if(FirstStr==LangSolver.GetString(RepairBase_LS,LID_615)/*""*/)
			FirstIndex=0;
		else if((FirstIndex=value->indexOf(FirstStr,wFirstIndex))==-1)
			return LangSolver.GetString(RepairBase_LS,LID_616)/*""*/;
		FirstIndex+=FirstStr.length();
		if(EndStr==LangSolver.GetString(RepairBase_LS,LID_617)/*""*/)
			EndIndex=FirstIndex-1;
		else if((EndIndex=value->indexOf(EndStr,FirstIndex))==-1)
			return LangSolver.GetString(RepairBase_LS,LID_618)/*""*/;
	}
	return value->mid(FirstIndex,EndIndex-FirstIndex);
}

//文字列から目的のデータを指定された文字数分切り取る（QByteArray）
QByteArray RepairBase::GetString(const QByteArray *value,QString FirstStr,int Count)
{
	int FirstIndex=0;
	int EndIndex;
	if(FirstStr==LangSolver.GetString(RepairBase_LS,LID_619)/*""*/)
		FirstIndex=0;
	else if((FirstIndex=value->indexOf(FirstStr))==-1)
		return LangSolver.GetString(RepairBase_LS,LID_620)/*""*/;
	FirstIndex+=FirstStr.length();
	return value->mid(FirstIndex,Count);
}

int RepairBase::GetStringCount(const QString *value,QString strData)
{
	int Cnt,Index=0;
	for(Cnt=0;;Cnt++,Index++){
		if((Index=value->indexOf(strData,Index))==-1)
			break;
	}
	return Cnt;
}

QString RepairBase::SearchXMLData(QList<QByteArray> *XMLDataList,QString SearchStr,int Side)
{
	for(int Index=0;Index<XMLDataList->count();Index++){
		if(QString(XMLDataList->at(Index)).contains(SearchStr)){
			SetListIndex(Side,Index);
			return QString(XMLDataList->at(Index));
		}
	}
	return LangSolver.GetString(RepairBase_LS,LID_621)/*""*/;
}

void RepairBase::SetWorkerID(QString *WID)
{
	if(WID==NULL)
		WorkerID=LangSolver.GetString(RepairBase_LS,LID_622)/*"-1"*/;
	else
		WorkerID=*WID;
}

void RepairBase::SetWorkerName(QString *Name)
{
	if(Name==NULL)
		WorkerName=LangSolver.GetString(RepairBase_LS,LID_623)/*""*/;
	else
		WorkerName=*Name;
}

//bool RepairBase::GetNGImage(QTableWidget *W,int Row,QStringList *HeaderLabels,QImage *Image,int &ImageX,int &ImageY,int &ImageW,int &ImageH)
bool RepairBase::GetNGImage(QTableWidget *W,int Row,int Index,QStringList *HeaderLabels,QImage *Image,int &ImageX,int &ImageY,int &ImageW,int &ImageH)
{
//	QString strNGJ	=W->item(Row,HeaderLabels->indexOf("NGJ"))->text();
	int iNGI		=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_624)/*"NGI"*/))->text().toInt();
	iSide			=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_625)/*"Side"*/))->text().toInt();

	//HistoryListColor
	if(iSide==Front){
		NowFBColor=twHistoryFrontColor;
	}
	else{
		NowFBColor=twHistoryBackColor;
	}

	if(JDTDataList[iSide]==NULL || iNGI==-1){
		//NG画像がない場合
//		SetMasterNGParam(Row,IDataUnitInBase->NGImagePieceList[0]->GetCanvasWidth(),IDataUnitInBase->NGImagePieceList[0]->GetCanvasHeight(),ImageX,ImageY,ImageW,ImageH);
//		SetMasterNGParam(Row,NGShowW,NGShowH,ImageX,ImageY,ImageW,ImageH);
		SetMasterNGParam(Index,NGShowW,NGShowH,ImageX,ImageY,ImageW,ImageH);
		return false;
	}

	if(NGITagList[iSide]!=NULL){
		for(XMLTagAttr *TA=NGITagList[iSide][iNGI]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
		    if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_626)/*"X"*/)==0)
//				ImageX=TA->iAttrData;
				ImageX=TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_627)/*"Y"*/)==0)
				ImageY=TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_628)/*"W"*/)==0)
				ImageW=TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_629)/*"H"*/)==0)
				ImageH=TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_630)/*"IDX"*/)==0)
				iIDX=TA->iAttrData;
			else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_631)/*"Index"*/)==0)
				iIndex=TA->iAttrData;	
		}
	}
	if(iIDX<0 || iIDX>=JDTDataListCountPage[iSide] || iIndex<0 || iIndex>=JDTDataListCountJpg[iSide][iIDX]){
		//NG画像がない場合
//		SetMasterNGParam(Row,IDataUnitInBase->NGImagePieceList[0]->GetCanvasWidth(),IDataUnitInBase->NGImagePieceList[0]->GetCanvasHeight(),ImageX,ImageY,ImageW,ImageH);
//		SetMasterNGParam(Row,NGShowW,NGShowH,ImageX,ImageY,ImageW,ImageH);
		SetMasterNGParam(Index,NGShowW,NGShowH,ImageX,ImageY,ImageW,ImageH);
		return false;
	}

	//画像データ（ＪＰＥＧデータ）
	if(JDTDataList[iSide][iIDX]==NULL)
		return false;
	if(!Image->loadFromData(JDTDataList[iSide][iIDX][iIndex]))
		return false;
	return true;
}

bool RepairBase::GetByte(QFile *f,int ByteCnt,int &iRet)
{
	char buffer;
	if(f->read(&buffer,ByteCnt)!=ByteCnt){
		QMessageBox::warning(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_632)/*"Error"*/,LangSolver.GetString(RepairBase_LS,LID_633)/*"NG Image File read error!"*/);
		f->close();
		return false;
	}
	iRet=*(int *)&buffer;
	return true;
}

bool RepairBase::GetByteArray(QFile *f,int ByteCnt,QImage *Img)
{
	QByteArray ByteArray;
	if((ByteArray=f->read(ByteCnt)).isEmpty()){
		QMessageBox::warning(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_634)/*"Error"*/,LangSolver.GetString(RepairBase_LS,LID_635)/*"NG Image File read error!"*/);
		f->close();
		return false;
	}
	Img->loadFromData(ByteArray,0);
	return true;
}

bool RepairBase::PassByteArray(QFile *f,int ByteCnt)
{
	if(f->read(ByteCnt).isEmpty()){
		QMessageBox::warning(&QWidget(),(LangSolver.GetString(RepairBase_LS,LID_636)/*"Error"*/,LangSolver.GetString(RepairBase_LS,LID_637)/*"NG Image File read error!"*/);
		f->close();
		return false;
	}
	return true;
}
/*
bool RepairBase::GetBinary(QFile *f,int ByteCnt,char *buffer)
{
	if(f->read(buffer,ByteCnt)!=ByteCnt){
		QMessageBox::warning(&QWidget(),QObject::tr("Error"),QObject::tr("NG Image File read error!"));
		f->close();
		return false;
	}
	return true;
}
*/
bool RepairBase::GetBinary(QFile *f,int ByteCnt,QByteArray &Buffer)
{
	if((Buffer=f->read(ByteCnt)).isEmpty()){
		QMessageBox::warning(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_638)/*"Error"*/,LangSolver.GetString(RepairBase_LS,LID_639)/*"NG Image File read error!"*/);
		f->close();
		return false;
	}
	return true;
}


//void RepairBase::SetMasterNGParam(QTableWidget *W,int Row,QStringList *HeaderLabels,QImage *Image,int Width,int Height,int &ImageX,int &ImageY,int &ImageW,int &ImageH)
//void RepairBase::SetMasterNGParam(int Index,int Width,int Height,int &ImageX,int &ImageY,int &ImageW,int &ImageH)
NGPointBaseList	*RepairBase::SetMasterNGParam(int Index,int Width,int Height,int &ImageX,int &ImageY,int &ImageW,int &ImageH)
{
	int RectX1,RectX2;
	int RectY1,RectY2;
///	RectX1=RectX2=NGPointList[iSide][Index].at(0).x();
///	RectY1=RectY2=NGPointList[iSide][Index].at(0).y();
///	for(int Cnt=1;Cnt<NGPointList[iSide][Index].count();Cnt++){
///		int wRectX=NGPointList[iSide][Index].at(Cnt).x();
///		int wRectY=NGPointList[iSide][Index].at(Cnt).y();
//	NGPointList *P=NGPList[iSide][Index].GetFirst();
//	RectX1=RectX2=P->x;
//	RectY1=RectY2=P->y;
//	for(P=P->GetNext();P!=NULL;P=P->GetNext()){
//		int wRectX=P->x;
//		int wRectY=P->y;
	int BCnt=0;
	NGPointBaseList	*PB;
	for(PB=NGPListForVRS[iSide].GetFirst();PB!=NULL;PB=PB->GetNext(),BCnt++){
		if(BCnt==Index){
			NGPointList *P=PB->NGListForVRS.GetFirst();
			RectX1=RectX2=P->x;
			RectY1=RectY2=P->y;
			for(P=P->GetNext();P!=NULL;P=P->GetNext()){
				int wRectX=P->x;
				int wRectY=P->y;
				if(RectX1>wRectX)
					RectX1=wRectX;
				if(RectY1>wRectY)
					RectY1=wRectY;
				if(RectX2<wRectX)
					RectX2=wRectX;
				if(RectY2<wRectY)
					RectY2=wRectY;
			}
			break;
		}
	}
	if(PB!=NULL){
		ImageX=RectX1-((Width-(RectX2-RectX1)) >> 1);
		ImageY=RectY1-((Height-(RectY2-RectY1)) >> 1);
		ImageW=Width;
		ImageH=Height;
	}
	return PB;
}

bool RepairBase::CheckJDTFile(QString strNGJ,int Side)
{
	//ネットワークパスのプリペンド
///	strNGJ.replace(LangSolver.GetString(RepairBase_LS,LID_640)/*"\\"*/,LangSolver.GetString(RepairBase_LS,LID_641)/*"/"*/);
	strNGJ.replace(/**/"\\",/**/"/");

	//XMLディレクトリのアクセス確認
	QString sNGJ=LangSolver.GetString(RepairBase_LS,LID_642)/*"//"*/ + HostName + LangSolver.GetString(RepairBase_LS,LID_643)/*"/"*/ + XMLFileDir + LangSolver.GetString(RepairBase_LS,LID_644)/*"/"*/;

	if(QDir(sNGJ).exists()==true){
		strNGJ.prepend(sNGJ);
	}
	else{
		strNGJ=XMLFilePath + QDir::separator() + strNGJ;
	}

	//JDTDataListのメモリ管理
	int jdtCount=PNumbForBase;
	if(ImgCnt!=NULL){
		delete []ImgCnt;
		ImgCnt=NULL;
	}
	if(BuffPG!=NULL){
		for(int Cnt=0;Cnt<jdtCount;Cnt++)
			delete BuffPG[Cnt];
		delete []BuffPG;
		BuffPG=NULL;
	}
	if(JDTDataList[Side]!=NULL){
		for(int Cnt=0;Cnt<jdtCount;Cnt++)
			delete []JDTDataList[Side][Cnt];
		delete JDTDataList[Side];
		JDTDataList[Side]=NULL;
	}
	ImgCnt	=new int[PNumbForBase];
	BuffPG	=new int*[PNumbForBase];
	JDTDataList[Side]	=new QByteArray*[PNumbForBase];
	JDTDataListCountPage[Side]=PNumbForBase;
	QString wstrNGJ=strNGJ;
	for(int Cnt=0;Cnt<PNumbForBase;Cnt++){
		BuffPG[Cnt]=NULL;
		JDTDataList[Side][Cnt]=NULL;
		JDTDataListCountJpg[Side][Cnt]=0;
		ImgCnt[Cnt]=0;
		if(QFile(strNGJ.replace(LangSolver.GetString(RepairBase_LS,LID_645)/*"*"*/,QString::number(Cnt))).exists()){
			NGFile.setFileName(strNGJ);
			//画像バッファの保持
			//NG画像有りの場合、画像ファイルをオープンして、画像情報の取得
			if(NGFile.open(QIODevice::ReadOnly)){
				if(NGFile.fileName().right(4)==LangSolver.GetString(RepairBase_LS,LID_646)/*".jdt"*/){
					//画像情報個数（バージョン情報は読み跳ばす）
					int ImageCnt;
					if(GetByte(&NGFile,4,ImageCnt)){
						ImgCnt[Cnt]	=ImageCnt;
						if(ImageCnt>0){
							BuffPG[Cnt]	=new int[ImageCnt];
							JDTDataList[Side][Cnt]=new QByteArray[ImageCnt];
							JDTDataListCountJpg[Side][Cnt]=ImageCnt;
							wjdtCount=jdtCount;
							for(int i=0;i<ImageCnt;i++){
								if(!PassByteArray(&NGFile,2))
									break;
								//ページ番号の取得
								int iPG;
								if(!GetByte(&NGFile,4,iPG) || !PassByteArray(&NGFile,20))
									break;
								BuffPG[Cnt][i]=iPG;
								//画像データの取得
								int ImageByte;
								if(!GetByte(&NGFile,4,ImageByte))
									break;
								if(ImageByte==0)
									continue;
								if(!GetBinary(&NGFile,ImageByte,JDTDataList[Side][Cnt][i]))
									break;
							}
						}
					}
				}
				NGFile.close();
			}
		}
		strNGJ=wstrNGJ;
	}
	return true;
}

bool RepairBase::CheckInsideNGPoint(int X,int Y,int W,int H,int wPG)
{
	if(wPG!=PG){
		return false;
	}

	if(X>(MaxX-W) && X<(MinX+W) && Y>(MaxY-H) && Y<(MinY+H)){
		return true;
	}
	return false;
}

void RepairBase::ShowHistoryList(QTableWidget *TableWidget,int MasterCount,QStringList &HeaderLabels,int InsDataDialogFlag)
{
	//検査データのSelect結果を表示する
	if(GetShowInsDataMsg()==true){
		InsDataDialog.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
		InsDataDialog.SetDialog(SType,GetRetXMLDataList(Front),GetRetXMLDataList(Back),MasterCount,InsDataDialogFlag);
		if(MasterCount==1 || InsDataDialogFlag!=0){
//			InsDataDialog.exec();
			InsDataDialog.show();
		}
	}

	TableWidget->setUpdatesEnabled(false);
	if(MasterCount==1){
		//表面のみ
		int XMLDataListCnt;
		TableWidget->clearContents();
		TableWidget->setRowCount(XMLDataListCnt=GetRetXMLDataList(SType)->count());
		int Row=0;
		for(int Counter=0;Counter<XMLDataListCnt;Counter++){
			if(NotShowHaltFlag==true){
				if(GetRetXMLDataList(SType)->at(Row).contains(LangSolver.GetString(RepairBase_LS,LID_647)/*"<RES>MaxOver</RES>"*/) || GetRetXMLDataList(SType)->at(Row).contains(LangSolver.GetString(RepairBase_LS,LID_648)/*"<RES>TimeOver</RES>"*/)){
					GetRetXMLDataList(SType)->removeAt(Row);
					continue;
				}
			}
			if(!GetRetXMLDataList(SType)->at(Row).contains(LangSolver.GetString(RepairBase_LS,LID_649)/*"<NGP"*/)){
				if(GetRes()==LangSolver.GetString(RepairBase_LS,LID_650)/*"OK"*/){
///					if(GetRetXMLDataList(SType)->at(Row).contains(LangSolver.GetString(RepairBase_LS,LID_651)/*"<RES>OK</RES>"*/)){
						GetRetXMLDataList(SType)->removeAt(Row);
						continue;
///					}
				}
///				else{
///					if(GetRetXMLDataList(SType)->at(Row).contains(LangSolver.GetString(RepairBase_LS,LID_652)/*"<RES>NG</RES>"*/)){
///						GetRetXMLDataList(SType)->removeAt(Row);
///						continue;
///					}
///				}
			}
			SetXMLDataToTable(TableWidget,Row,Row,SType,twHistoryFrontColor);
			Row++;
		}
		TableWidget->setRowCount(Row);
	}
	else{
		//裏表対応
		for(int i=0;i<MasterCount;i++){
			SideType	sType;
			switch(i){
				case 0:	sType=Front;	break;
				case 1:	sType=Back;		break;
			}

			int XMLDataListCnt=GetRetXMLDataList(sType)->count();
			for(int RowIndex=0,Counter=0;Counter<XMLDataListCnt;Counter++){
				if(!GetRetXMLDataList(sType)->at(RowIndex).contains(LangSolver.GetString(RepairBase_LS,LID_653)/*"<NGP"*/)){
					if(GetRes()==LangSolver.GetString(RepairBase_LS,LID_654)/*"OK"*/){
///						if(GetRetXMLDataList(sType)->at(RowIndex).contains(LangSolver.GetString(RepairBase_LS,LID_655)/*"<RES>OK</RES>"*/)){
							GetRetXMLDataList(sType)->removeAt(RowIndex);
							continue;
///						}
					}
				}
				RowIndex++;
			}
		}

		SetBothDataToTable(TableWidget);
	}
	TableWidget->setUpdatesEnabled(true);

	//個片情報データのセットの前にcbPieceListEditorをdelete
	if(cbPieceListEditor!=NULL){
		delete cbPieceListEditor;
		cbPieceListEditor=NULL;
	}

	//個片情報データのセット
	QStringList PieceNameList;
	if(GetRetPCEDataList(SType)->count()>0){
		PieceNameList.append(LangSolver.GetString(RepairBase_LS,LID_656)/*""*/);	//個片名称なしのものを予め含めておく
	}
	for(int i=0;i<GetRetPCEDataList(SType)->count();i++){
///		QString PieceName=GetString(&GetRetPCEDataList(SType)->at(i),LangSolver.GetString(RepairBase_LS,LID_657)/*"PIECENAME=\"*/#LangSolver.GetString(RepairBase_LS,LID_658)/*","*/\LangSolver.GetString(RepairBase_LS,LID_659)/*""*/);
		QString PieceName=GetString(&GetRetPCEDataList(SType)->at(i),/**/"PIECENAME=\"#",/**/"\"");
		if(PieceNameList.contains(PieceName)){
			continue;
		}
		PieceNameList.append(PieceName);
	}
	SetKohenNameList(SType,&PieceNameList);

	//ログデータ（ヘッダー部）のセット
	if(DLL_GetName!=NULL){
		if(GetRetXMLDataList(SType)->count()>0){
			//ロット名称のセット
			if(GetLotName(SType).isEmpty()){
				QString LotName;
				QString StartStr=/**/"<LOT LID=\""
									+ GetLotID(SType)
									+ /**/"\">";
				LotName=GetString(&QString(GetRetXMLDataList(SType)->at(0)),StartStr,LangSolver.GetString(RepairBase_LS,LID_664)/*"</LOT>"*/);
				SetLotName(SType,LotName);
				//デバッグログ出力
				WriteDebugLogFile(LangSolver.GetString(RepairBase_LS,LID_665)/*"LOT.No "*/ + GetLotName(SType));

				//現在のロット名称をファイルに保存//不使用
				//DLL_SaveLotNameFile(GetLotName(SType));

				//DLL_SetLogInfo("品種","ロット番号","上下","HD名のリスト","個片名称のリスト");
				DLL_SetLogInfo(&GetMasterName(SType),&GetLotName(SType),GetMachineRemark(SType),GetHDNameList(SType),GetKohenNameList(SType));

				//履歴リストの内容（タイトル部）をファイルに保存する
				DLL_SaveHistoryList(TableWidget,HeaderLabels,true);
				return;
			}
			//DLL_SetLogInfo("品種","ロット番号","上下","HD名のリスト","個片名称のリスト");
			DLL_SetLogInfo(&GetMasterName(SType),&GetLotName(SType),GetMachineRemark(SType),GetHDNameList(SType),GetKohenNameList(SType));
		}
	}
}

void RepairBase::xmlMacGet(QByteArray Info, QByteArray &MAC)
{
	QDomDocument d;
	d.setContent(Info);
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {	
		if (n.tagName()==LangSolver.GetString(RepairBase_LS,LID_666)/*"IST"*/){
			MAC=n.attribute(LangSolver.GetString(RepairBase_LS,LID_667)/*"MAC"*/).toLocal8Bit().data();//2:検査装置番号
		}
		return ;
	}
}

//個片情報表示設定
void RepairBase::SetPieceInfoData(SideType Type)
{
	int PCEDataCount=GetRetPCEDataList(Type)->count();
	PieceInfoDataCount[Type]=GetKohenNameList(Type)->count();
	if(PieceInfoDataCount[Type]>0){
		if(PieceInfoDataList[Type]!=NULL){
			delete []PieceInfoDataList[Type];
		}
		PieceInfoDataList[Type]=new PieceInfoData[PieceInfoDataCount[Type]];
		for(int i=0;i<PCEDataCount;i++){
///			int PieceNameIndex=GetKohenNameList(Type)->indexOf(GetString(&GetRetPCEDataList(Type)->at(i),LangSolver.GetString(RepairBase_LS,LID_668)/*"PIECENAME=\"*/#LangSolver.GetString(RepairBase_LS,LID_669)/*","*/\LangSolver.GetString(RepairBase_LS,LID_670)/*""*/));
			int PieceNameIndex=GetKohenNameList(Type)->indexOf(GetString(&GetRetPCEDataList(Type)->at(i),/**/"PIECENAME=\"#",/**/"\""));
			PieceInfoDataList[Type][PieceNameIndex].SetPieceData(this,&GetRetPCEDataList(Type)->at(i),IDataUnit->MImageClassList[Type]->ImageList);
		}
	}
}

//void RepairBase::ShowNGList(QTableWidget *TableWidget,int NGCount,int XMLIndex,QStringList *HeaderLabels,int BothSide)
//void RepairBase::ShowNGList(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int BothSide)
//void RepairBase::ShowNGList(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide)
int RepairBase::ShowNGList(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide)
{
	int BX;
	int BY;
	int SumImgCnt=0;

	int Ret=0;

	QString TagNGJ;
	NGPTagDataList *NGPTagDList[2];
	NGPTagDList[0]	=NGPTagDList[1]		=NULL;
	bool *FindNGCntList[2];
	FindNGCntList[0]=FindNGCntList[1]	=NULL;
	TableWidget->clearContents();
	TableWidget->setRowCount(NGCount);
	TableWidget->setColumnCount(HeaderLabels->count());
///	for(int Cnt=0;Cnt<NGPointList.count();Cnt++)
///		NGPointList[Cnt].clear();
//	NGPointList[0].clear();
//	NGPointList[1].clear();
	IDXJDT.clear();

	//NGリストのクリアの前にcbPieceListEditorをdelete
	if(cbPieceListEditor!=NULL){
		delete cbPieceListEditor;
		cbPieceListEditor=NULL;
	}

	//VRS用NGリストのクリア
	NGPListForVRS[0].RemoveAll();
	NGPListForVRS[1].RemoveAll();

	if(NGCount==0){
		for(int BothCnt=0;BothCnt<=BothSide;BothCnt++){
			if(BothCnt==0){
				if(XMLIndex1!=-1){
					Ret=CheckXMLData(strXML[BothCnt],GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex1));
					strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex1);
				}
				SetListIndex(BothCnt,XMLIndex1);
			}
			else{
				if(XMLIndex2!=-1){
					Ret=CheckXMLData(strXML[BothCnt],GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex2));
					strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex2);
				}
				SetListIndex(BothCnt,XMLIndex2);
			}
			if(GetOutputXMLData()==true){
				WriteDebugLogFile(strXML[BothCnt]);
			}
		}
		return Ret;
	}

	int NGICount=0;
	int NGICnt=0;
	int NGPCount=0;
	int	FindNGCnt=0;
	int NGIX,NGIY,NGIW,NGIH;
	QString PieceNM;
	QStringList PieceNMList;
	int X,Y,iPG;
	SumFRowCntInImage=SumBRowCntInImage=0;

	SumFRowCnt	=0;
	SumBRowCnt	=0;
	int RowCnt	=0;
	int RowIndex=0;

	for(int BothCnt=0;BothCnt<=BothSide;BothCnt++){
///	for(BothCnt=0;BothCnt<=BothSide;BothCnt++){
///		int RowCnt	=0;
		RowCnt	=0;
		QString TagNGI=LangSolver.GetString(RepairBase_LS,LID_671)/*"Init"*/;		//Init:初期値
		if(BothCnt==0){
			if(XMLIndex1==-1){
				SetListIndex(BothCnt,XMLIndex1);
				continue;
			}
			Ret=CheckXMLData(strXML[BothCnt],GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex1));
			strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex1);
			SetListIndex(BothCnt,XMLIndex1);

			//デバッグログ出力
			if(GetOutputXMLData()==true){
				WriteDebugLogFile(strXML[BothCnt]);
			}
		}
		else{
			if(XMLIndex2==-1){
				SetListIndex(BothCnt,XMLIndex2);
				continue;
			}
			Ret=CheckXMLData(strXML[BothCnt],GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex2));
			strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex2);
			SetListIndex(BothCnt,XMLIndex2);

			//デバッグログ出力
			if(GetOutputXMLData()==true){
				WriteDebugLogFile(strXML[BothCnt]);
			}
		}
		if(strXML[BothCnt].isEmpty())
			continue;

		//IDを取り除く
		strXML[BothCnt]=strXML[BothCnt].mid(strXML[BothCnt].indexOf(LangSolver.GetString(RepairBase_LS,LID_672)/*"<IST"*/));
		//MacIDとoffset
		MAC=LangSolver.GetString(RepairBase_LS,LID_673)/*""*/;
		xmlMacGet(strXML[BothCnt], MAC);
		if(MachineID[BothCnt]!=MAC.toInt()){
			//OutlineOffsetの取得
			MachineID[BothCnt]=MAC.toInt();
			QList<int>	OffsetXList,OffsetYList;
			if(GetOutlineOffset(MachineID[BothCnt],&OffsetXList,&OffsetYList)==true){
				for(int i=0; i<Pagenumb && i<OffsetXList.count(); i++){
					IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetX	=OffsetXList.at(i);	//OutlineOffsetの取得
					IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetY	=OffsetYList.at(i);
					IDataUnit->MImageClassList[SType]->ImageList[i]->OffsetX	=(IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetX)>>IDataUnit->MImageClassList[SType]->ImgRate;	//OutlineOffsetの取得
					IDataUnit->MImageClassList[SType]->ImageList[i]->OffsetY	=(IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetY)>>IDataUnit->MImageClassList[SType]->ImgRate;
				}
			}
		}
		//XMLElement
//		int Len=strXML.count()+2;
//		char *buff=new char[Len];
//		int	n=::QString2Char(strXML, buff, Len);
		char *buff;
		buff=strXML[BothCnt].data();
		if(ISTElement[BothCnt]!=NULL)
			delete ISTElement[BothCnt];
		ISTElement[BothCnt]=new XMLElement(NULL);
		ISTElement[BothCnt]->Analyze(buff);
//		delete []buff;
/*
		//データの確認
		for(XMLElement *E=ISTElement->GetFirst();E!=NULL;E=E->GetNext()){
			for(XMLTagAttr *TA=E->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				QString TAName=TA->AttrName;
				QString TAData=TA->AttrData;
			}
			for(XMLElement *E=ISTElement->Datas.GetFirst();E!=NULL;E=E->GetNext()){
				QString TName=E->StartTag.TagName;
				QString TData=E->StrData;
				for(XMLTagAttr *TA=E->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
					QString TAName=TA->AttrName;
					QString TAData=TA->AttrData;
				}
			}
		}
*/
		TagNGJ=LangSolver.GetString(RepairBase_LS,LID_674)/*""*/;
		for(XMLTagAttr *TA=ISTElement[BothCnt]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
			if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_675)/*"NGJ"*/)==0){
				TagNGJ=TA->AttrData->GetString();
				break;
			}
		}
		if(TagNGJ.isEmpty()){
			QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_676)/*"Not Found NGJ"*/,LangSolver.GetString(RepairBase_LS,LID_677)/*"Not Found NGJ"*/);
			return Ret;
		}

		//NGIタグの保持
///		int NGICount=strXML.count("<NGI");
		NGICount=strXML[BothCnt].count(LangSolver.GetString(RepairBase_LS,LID_678)/*"<NGI"*/);
		if(NGITagList[BothCnt]!=NULL)
			delete []NGITagList[BothCnt];
		NGITagList[BothCnt]=new XMLElement*[NGICount];

		//ARAの重複数
		int ARACount=0;

		//.jdtファイル内のデータを保持
		XMLElement *E1=NULL;
///		int NGICnt=0;
		NGICnt=0;
///		int NGPCount=strXML.count("<NGP");
		NGPCount=strXML[BothCnt].count(LangSolver.GetString(RepairBase_LS,LID_679)/*"<NGP"*/);
		if(CheckJDTFile(TagNGJ,BothCnt)){
			//画像ファイル数を数える
//			int SumImgCnt=0;
			SumImgCnt=0;
			for(int Cnt=0;Cnt<PNumbForBase;Cnt++){
				SumImgCnt+=ImgCnt[Cnt];
			}
			//NGPデータのソート前処理（ソートはNGのX座標かY座標か切り返れるように）
			if(NGPTagList[BothCnt]!=NULL)
				delete []NGPTagList[BothCnt];
			NGPTagList[BothCnt]=new XMLElement*[NGPCount];
			int NGPCnt=0;
			for(XMLElement *E=ISTElement[BothCnt]->Datas.GetFirst();E!=NULL;E=E->GetNext()){
				if(strcmp(E->StartTag.TagName->GetString(),LangSolver.GetString(RepairBase_LS,LID_680)/*"NGP"*/)==0)
					NGPTagList[BothCnt][NGPCnt++]=E;
				else if(strcmp(E->StartTag.TagName->GetString(),LangSolver.GetString(RepairBase_LS,LID_681)/*"NGI"*/)==0)
					NGITagList[BothCnt][NGICnt++]=E;
			}
			if(SumImgCnt<NGICnt){
				Ret|=0x20;
			}
			//NGPコムソート
			ComSortNGP(NGPCnt,NGPTagList[BothCnt],BothCnt);
			//NGIコムソート
			ComSortNGI(NGICnt,NGITagList[BothCnt],BothCnt);

			//NGPタグデータ格納クラスにデータを保持
			NGPTagDList[BothCnt]=new NGPTagDataList[NGPCount];

			//出現NGポイント格納リスト
			FindNGCntList[BothCnt]=new bool[NGPCount];

			//初期化
			#pragma omp parallel
			{
				#pragma omp for
				for(int Cnt=0;Cnt<NGPCount;Cnt++){
///				for(Cnt=0;Cnt<NGPCount;Cnt++){
					FindNGCntList[BothCnt][Cnt]=false;	//falseに初期化

					for(XMLTagAttr *TA=NGPTagList[BothCnt][Cnt]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
					    if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_682)/*"X"*/)==0)
							NGPTagDList[BothCnt][Cnt].x=TA->iAttrData;
					    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_683)/*"Y"*/)==0)
							NGPTagDList[BothCnt][Cnt].y=TA->iAttrData;
					    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_684)/*"RAL"*/)==0)
							NGPTagDList[BothCnt][Cnt].ral=QString(TA->AttrData->GetString()).mid(6);	//Basic:BlockInspection
					    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_685)/*"PG"*/)==0)
							NGPTagDList[BothCnt][Cnt].pg=TA->iAttrData;
					    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_686)/*"ARA"*/)==0)
							NGPTagDList[BothCnt][Cnt].ara=QString(TA->AttrData->GetString()).mid(1);
					}
//					NGPTagDList[BothCnt][Cnt].Checked=NULL;
					#pragma omp critical
					ARACount+=NGPTagDList[BothCnt][Cnt].ara.count(',');
				}
			}
		}
		//NGポイントデータ格納クラスの作成
		if(NGPList[BothCnt]!=NULL){
			delete []NGPList[BothCnt];
		}
		NGPList[BothCnt]=new NPListPack<NGPointList>[NGICount+ARACount];

		//画像なしNGポイントデータの削除
		NGPListForVRS[BothCnt].RemoveAll();

		QString sRAL,sARA;
		QStringList ARAList;

		//NGチェック済みかどうかの判断<RCH>タグを検索
		bool	CheckNG;
		CheckNG=isCheckedNGPoint(BothCnt);

		int		NextComCnt	=0;
///		int		FindNGCnt	=0;
		FindNGCnt	=0;
		for(int Row=0;Row<NGICnt;Row++){
///			CheckNG=false;
///			int NGIX,NGIY,NGIW,NGIH;
///			QString PieceNM;
			for(XMLTagAttr *TA=NGITagList[BothCnt][Row]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
			    if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_687)/*"X"*/)==0)
					NGIX=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_688)/*"Y"*/)==0)
					NGIY=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_689)/*"W"*/)==0)
					NGIW=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_690)/*"H"*/)==0)
					NGIH=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_691)/*"IDX"*/)==0)
					iIDX=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_692)/*"Index"*/)==0)
					iIndex=TA->iAttrData;
			}
			//iIDXの値が不正でないかどうか判断
			if(iIDX>=0 && iIDX<PNumbForBase){
				//iIndexの値が不正でないかどうか判断
				if(iIndex>=0 && iIndex<ImgCnt[iIDX]){
					if(BuffPG[iIDX]==NULL){
						PG	=iIDX;
					}
					else{
						PG	=BuffPG[iIDX][iIndex];
					}
				}
				else{
					PG	=iIDX;
				}
			}
			else{
				PG	=0;
			}

			//PieceInfoDataList
			PieceNMList	=GetPieceNMList(NGIX,NGIY,NGIW,NGIH,PG,BothCnt);

#ifdef DEBUG
			PieceNM=PieceNMList[0];
			if(PieceNMList.count()>1){
				PieceNM=PieceNMList[1];
			}
#endif
			NGIX1	=NGIX+NGImageOffset;
			NGIY1	=NGIY+NGImageOffset;
			NGIX2	=NGIX+NGIW-NGImageOffset;
			NGIY2	=NGIY+NGIH-NGImageOffset;
			bool	FirstComming	=true;
			bool	FirstNotMatch	=true;
			bool	IsARAList		=false;
			bool	ARAListFlag		=false;
			for(int ComCnt=NextComCnt;ComCnt<NGPCount;ComCnt++){
///				int X,Y,iPG;
				char *colorAlg;
				//QString sRAL;
				X	=NGPTagDList[BothCnt][ComCnt].x;
				Y	=NGPTagDList[BothCnt][ComCnt].y;
				iPG	=NGPTagDList[BothCnt][ComCnt].pg;
				sRAL=NGPTagDList[BothCnt][ComCnt].ral;
				sARA=NGPTagDList[BothCnt][ComCnt].ara;

				NGPCompair	NGPComp=CompairSortValue(X,Y,iPG,BothCnt);
				if(NGPComp==Less){
					continue;
				}
				else if(NGPComp==Large){
					if(FirstNotMatch)
						NextComCnt=ComCnt;
					break;
				}
				else if(NGPComp==NotMatch){
					if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
						NextComCnt=ComCnt;
						FirstNotMatch=false;
					}
					continue;
				}
				if(FindNGCntList[BothCnt][ComCnt]){
					continue;
				}

				//個片情報での判別
				int sARAListCnt=0;
				if(sARA.isEmpty()==false){
					if(sARA.contains(',')==true){
						if(FirstComming==false && IsARAList==false){
							if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
								NextComCnt=ComCnt;
								FirstNotMatch=false;
							}
							ARAListFlag=true;
							continue;
						}
						QStringList sARAList=sARA.split(',');
						sARAListCnt=sARAList.count();
//						if(NGPTagDList[BothCnt][ComCnt].Checked==NULL){
//							NGPTagDList[BothCnt][ComCnt].Checked=new bool[sARAListCnt];
//							for(int i=0;i<sARAListCnt;i++)
//								NGPTagDList[BothCnt][ComCnt].Checked[i]=false;
//						}
						int i;
						for(i=0;i<sARAListCnt;i++){
//							if(NGPTagDList[BothCnt][ComCnt].Checked[i]==true)
//								continue;
							int j;
							for(j=0;j<PieceNMList.count();j++){
								if(sARAList[i]==PieceNMList[j]){
//									sARA=sARAList[i];
//									NGPTagDList[BothCnt][ComCnt].Checked[i]=true;
									break;
								}
							}
							if(j!=PieceNMList.count()){
								break;
							}
						}
						if(i==sARAListCnt){
							if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
								NextComCnt=ComCnt;
								FirstNotMatch=false;
							}
							continue;
						}
						IsARAList=true;
					}
					else{
						if(IsARAList==true){
							if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
								NextComCnt=ComCnt;
								FirstNotMatch=false;
							}
							ARAListFlag=true;
							continue;
						}
						int j;
						for(j=0;j<PieceNMList.count();j++){
							if(sARA==PieceNMList[j]){
								break;
							}
						}
						if(j==PieceNMList.count()){
							if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
								NextComCnt=ComCnt;
								FirstNotMatch=false;
							}
							continue;
						}
					}
					if(ARAList.contains(sARA)==false)
						ARAList.append(sARA);
				}
				else{
					int j;
					for(j=0;j<PieceNMList.count();j++){
						if(sARA==PieceNMList[j]){
							break;
						}
					}
					if(j==PieceNMList.count()){
						if(FirstNotMatch && FindNGCntList[BothCnt][ComCnt]==false){
							NextComCnt=ComCnt;
							FirstNotMatch=false;
						}
						continue;
					}
				}

				X+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetX;
				Y+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetY;
				if(FirstComming){
///					CheckNG=true;
					int ARAIndex;
					if((ARAIndex=ARAList.indexOf(sARA))==-1)
						ARAIndex=99999999;
					for(int Col=0;Col<HeaderLabels->count();Col++){
						if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_693)/*"X, Y"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString().setNum(X) + LangSolver.GetString(RepairBase_LS,LID_694)/*", "*/ + QString().setNum(Y));
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_695)/*"RAL"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sRAL);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_696)/*"ARA"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_697)/*"ARAIndex"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString::number(ARAIndex).rightJustified(8,'0'));
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_698)/*"NGJ"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,TagNGJ);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_699)/*"NGI"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,Row);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_700)/*"NGP"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,ComCnt);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_701)/*"Side"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BothCnt);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_702)/*"RowIndex"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,RowIndex++);
						else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_703)/*"wARA"*/)
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
					}
					FirstComming=false;

					NGPointList *p=new NGPointList(X,Y, sRAL);
					NGPList[BothCnt][RowCnt].AppendList(p);
					MaxX=MinX=X;
					MaxY=MinY=Y;
					RowCnt++;
				}
				else{
					NGPointList *p=new NGPointList(X,Y,sRAL);
					NGPList[BothCnt][RowCnt-1].AppendList(p);
					if(X<MinX)
						MinX=X;
					if(X>MaxX)
						MaxX=X;
					if(Y<MinY)
						MinY=Y;
					if(Y>MaxY)
						MaxY=Y;
				}
///				//NGチェック済みかどうかの判断<RCH>タグをSELECT
///				if(CheckNG && !isCheckedNGPoint(PG,X,Y,BothCnt))
///					CheckNG=false;

//				if(NGPTagDList[BothCnt][ComCnt].Checked==NULL){
					FindNGCntList[BothCnt][ComCnt]=true;
					FindNGCnt++;
//				}
//				else{
//					int i;
//					for(i=0;i<sARAListCnt;i++){
//						if(NGPTagDList[BothCnt][ComCnt].Checked[i]==false)
//							break;
//					}
//					if(i==sARAListCnt){
//						FindNGCntList[BothCnt][ComCnt]=true;
//						FindNGCnt++;
//					}
//				}
			}
			if(CheckNG){
				SetColorToTable(TableWidget,SumFRowCnt+RowCnt-1,twNGListCheckColor);
			}

			int FK;
			if(CheckFKey(FK,BothCnt)){
				SetColorToTable(TableWidget,SumFRowCnt+RowCnt-1,ColorFKey[FK]);
			}
			if(ARAListFlag==true){
				Row--;
			}
		}
		//画像ありの件数の保持
		if(BothCnt==0){
			SumFRowCntInImage=RowCnt;
		}
		else{
			SumBRowCntInImage=RowCnt;
		}
		//画像なしの場合の処理
		NextComCnt	=0;
		for(int BaseCnt=0;BaseCnt<NGPCount;BaseCnt++){
			if(FindNGCntList[BothCnt][BaseCnt]){
				continue;
			}

			//画像なしエラーフラグを立てる
			Ret|=0x20;

//			int BX		=NGPTagDList[BothCnt][BaseCnt].x;
//			int BY		=NGPTagDList[BothCnt][BaseCnt].y;
			BX		=NGPTagDList[BothCnt][BaseCnt].x;
			BY		=NGPTagDList[BothCnt][BaseCnt].y;
			PG			=NGPTagDList[BothCnt][BaseCnt].pg;
			QString BRal=NGPTagDList[BothCnt][BaseCnt].ral;
			QString sARA=NGPTagDList[BothCnt][BaseCnt].ara;

			if(sARA.isEmpty()==false && ARAList.contains(sARA)==false){
				ARAList.append(sARA);
			}

///			CheckNG=true;
			int ARAIndex;
			if((ARAIndex=ARAList.indexOf(sARA))==-1){
				ARAIndex=99999999;
			}
			BX+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetX;
			BY+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetY;
			for(int Col=0;Col<HeaderLabels->count();Col++){
				if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_704)/*"X, Y"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString().setNum(BX) + LangSolver.GetString(RepairBase_LS,LID_705)/*", "*/ + QString().setNum(BY));
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_706)/*"RAL"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BRal);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_707)/*"ARA"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_708)/*"ARAIndex"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString::number(ARAIndex).rightJustified(8,'0'));
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_709)/*"NGJ"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,TagNGJ);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_710)/*"NGI"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,-1);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_711)/*"NGP"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BaseCnt);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_712)/*"Side"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BothCnt);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_713)/*"RowIndex"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,RowIndex++);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_714)/*"wARA"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
			}
///			//NGチェック済みかどうかの判断<RCH>タグをSELECT
///			if(CheckNG && !isCheckedNGPoint(PG,BX,BY,BothCnt)){
///				CheckNG=false;
///			}

			NGPointList *p=new NGPointList(BX,BY,BRal);
			NGPBaseList=new NGPointBaseList();
			NGPBaseList->NGListForVRS.AppendList(p);
			NGPListForVRS[BothCnt].AppendList(NGPBaseList);
			FindNGCntList[BothCnt][RowCnt]=true;
			MinX	=MaxX	=BX;
			MinY	=MaxY	=BY;
			NGIX1	=MaxX-W;
			NGIY1	=MaxY-H;
			NGIX2	=MinX+W;
			NGIY2	=MinY+H;
			RowCnt++;
			bool FirstNotMatch=true;

			for(int CompCnt=BaseCnt+1;CompCnt<NGPCount;CompCnt++){
				if(FindNGCntList[BothCnt][CompCnt])
					continue;
				int X		=NGPTagDList[BothCnt][CompCnt].x;
				int Y		=NGPTagDList[BothCnt][CompCnt].y;
				int wPG		=NGPTagDList[BothCnt][CompCnt].pg;
				QString wARA=NGPTagDList[BothCnt][CompCnt].ara;
				X+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[wPG]->OrgOffsetX;
				Y+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[wPG]->OrgOffsetY;

				//NGポイントが最初の点もしくは隣接する点を含めてさらに描画エリア内に含まれるかどうかの判断
				NGPCompair	NGPComp=CompairSortValue(X,Y,wPG,BothCnt);
				if(NGPComp==Less)
					continue;
				else if(NGPComp==Large){
					if(FirstNotMatch)
						NextComCnt=CompCnt;
					break;
				}
				else if(NGPComp==NotMatch){
					if(FirstNotMatch && FindNGCntList[BothCnt][CompCnt]==false){
						NextComCnt=CompCnt;
						FirstNotMatch=false;
					}
					continue;
				}

				//個片情報での判別
				if(sARA!=wARA)
					continue;

///				//NGチェック済みかどうかの判断<RCH>タグをSELECT
///				if(CheckNG && !isCheckedNGPoint(wPG,X,Y,BothCnt))
///					CheckNG=false;
				if(X<MinX)
					MinX=X;
				if(X>MaxX)
					MaxX=X;
				if(Y<MinY)
					MinY=Y;
				if(Y>MaxY)
					MaxY=Y;
				NGIX1	=MaxX-W;
				NGIY1	=MaxY-H;
				NGIX2	=MinX+W;
				NGIY2	=MinY+H;
				NGPointList *p=new NGPointList(X,Y, BRal);
				NGPBaseList->NGListForVRS.AppendList(p);
				FindNGCntList[BothCnt][CompCnt]=true;
			}

			if(CheckNG){
				SetColorToTable(TableWidget,RowCnt-1,twNGListCheckColor);
			}

			int FK;
			if(CheckFKey(FK,BothCnt)){
				SetColorToTable(TableWidget,RowCnt-1,ColorFKey[FK]);
			}
		}
		if(BothCnt==0){
			SumFRowCnt=RowCnt;
		}
		else{
			SumBRowCnt=RowCnt;
		}
		if(NGPTagDList[BothCnt]!=NULL){
			delete []NGPTagDList[BothCnt];
		}
		if(FindNGCntList[BothCnt]!=NULL){
			delete []FindNGCntList[BothCnt];
		}
	}
	TableWidget->setRowCount(SumFRowCnt+SumBRowCnt);

/*		for(int Row=0;FindNGCnt<NGPCount;Row++){
			//NG画像無し
			bool FirstComming=true;
			for(int ComCnt=0;ComCnt<NGPCount;ComCnt++){
				if(FindNGCntList[BothCnt][ComCnt])
					continue;
				X	=NGPTagDList[BothCnt][ComCnt].x;
				Y	=NGPTagDList[BothCnt][ComCnt].y;
				PG	=NGPTagDList[BothCnt][ComCnt].pg;
				sRAL=NGPTagDList[BothCnt][ComCnt].ral;
				if(FirstComming){
					CheckNG=true;
//					PG=GetString(&TagNGP," PG=\"","\"").toInt();
					X+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OffsetX;
					Y+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OffsetY;
					for(int Col=0;Col<HeaderLabels->count();Col++){
						if(HeaderLabels->at(Col)=="X, Y")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString().setNum(X) + ", " + QString().setNum(Y));
						else if(HeaderLabels->at(Col)=="RAL")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sRAL);
						else if(HeaderLabels->at(Col)=="NGJ")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,TagNGJ);
						else if(HeaderLabels->at(Col)=="NGI")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,-1);
						else if(HeaderLabels->at(Col)=="NGP")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,ComCnt);
						else if(HeaderLabels->at(Col)=="Side")
							SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BothCnt);
					}
					//NGチェック済みかどうかの判断<RCH>タグをSELECT
					if(CheckNG && !isCheckedNGPoint(PG,X,Y,BothCnt))
						CheckNG=false;

					FirstComming=false;
					RowCnt++;
					NGPointList *p=new NGPointList(X,Y,sRAL);
					NGPList[BothCnt][Row].AppendList(p);
					FindNGCntList[BothCnt][ComCnt]=true;
					MinX=MaxX=X;
					MinY=MaxY=Y;
				}
			}
			if(CheckNG)
				SetColorToTable(TableWidget,RowCnt-1,twNGListCheckColor);
			int FK;
			if(CheckFKey(FK,BothCnt))
				SetColorToTable(TableWidget,RowCnt-1,ColorFKey[FK]);
		}
		if(BothCnt==0)
			SumFRowCnt=RowCnt;
		else
			SumBRowCnt=RowCnt;
		if(NGPTagDList[BothCnt]!=NULL)
			delete []NGPTagDList[BothCnt];
		if(FindNGCntList[BothCnt]!=NULL)
			delete []FindNGCntList[BothCnt];
	}
	TableWidget->setRowCount(SumFRowCnt+SumBRowCnt);
*/
	return Ret;
}

//void RepairBase::ShowNGListForVRS(QTableWidget *TableWidget,int NGCount,int XMLIndex,QStringList *HeaderLabels,int W,int H,int BothSide)
void RepairBase::ShowNGListForVRS(QTableWidget *TableWidget,int NGCount,int XMLIndex1,int XMLIndex2,QStringList *HeaderLabels,int W,int H,int BothSide)
{
	NGPTagDataList *NGPTagDList[2];
	NGPTagDList[0]	=NGPTagDList[1]		=NULL;
	bool *FindNGCntList[2];
	FindNGCntList[0]=FindNGCntList[1]	=NULL;
	TableWidget->clearContents();
	TableWidget->setRowCount(NGCount);
	TableWidget->setColumnCount(HeaderLabels->count());

	//初期化処理
	NGPListForVRS[0].RemoveAll();
	NGPListForVRS[1].RemoveAll();

	if(NGCount==0){
		return;
	}

	SumFRowCnt	=0;
	SumBRowCnt	=0;
	int RowIndex=0;
	for(int BothCnt=0;BothCnt<=BothSide;BothCnt++){
		int RowCnt	=0;
		if(BothCnt==0){
			if(XMLIndex1==-1){
				SetListIndex(BothCnt,XMLIndex1);
				continue;
			}
			strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex1);
			SetListIndex(BothCnt,XMLIndex1);

			//デバッグログ出力
			if(GetOutputXMLData()==true){
				WriteDebugLogFile(strXML[BothCnt]);
			}
		}
		else{
			if(XMLIndex2==-1){
				SetListIndex(BothCnt,XMLIndex2);
				continue;
			}
			strXML[BothCnt]=GetRetXMLDataList((SideType)BothCnt)->at(XMLIndex2);
			SetListIndex(BothCnt,XMLIndex2);

			//デバッグログ出力
			if(GetOutputXMLData()==true){
				WriteDebugLogFile(strXML[BothCnt]);
			}
		}
		if(strXML[BothCnt].isEmpty())
			continue;

		//IDを取り除く
		strXML[BothCnt]=strXML[BothCnt].mid(strXML[BothCnt].indexOf(LangSolver.GetString(RepairBase_LS,LID_715)/*"<IST"*/));

		//MacIDとoffset
		MAC=LangSolver.GetString(RepairBase_LS,LID_716)/*""*/;
		xmlMacGet(strXML[BothCnt], MAC);
		if(MachineID[BothCnt]!=MAC.toInt()){
			//OutlineOffsetの取得
			MachineID[BothCnt]=MAC.toInt();
			QList<int>	OffsetXList,OffsetYList;
			if(GetOutlineOffset(MachineID[BothCnt],&OffsetXList,&OffsetYList)==true){
				for(int i=0; i<Pagenumb && i<OffsetXList.count(); i++){
					IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetX	=OffsetXList.at(i);	//OutlineOffsetの取得
					IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetY	=OffsetYList.at(i);
					IDataUnit->MImageClassList[SType]->ImageList[i]->OffsetX	=(IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetX)>>IDataUnit->MImageClassList[SType]->ImgRate;	//OutlineOffsetの取得
					IDataUnit->MImageClassList[SType]->ImageList[i]->OffsetY	=(IDataUnit->MImageClassList[SType]->ImageList[i]->OrgOffsetY)>>IDataUnit->MImageClassList[SType]->ImgRate;
				}
			}
		}

		//XMLElement
		char *buff;
		buff=strXML[BothCnt].data();
		if(ISTElement[BothCnt]!=NULL)
			delete ISTElement[BothCnt];
		ISTElement[BothCnt]=new XMLElement(NULL);
		ISTElement[BothCnt]->Analyze(buff);

		int NGPCount=strXML[BothCnt].count(LangSolver.GetString(RepairBase_LS,LID_717)/*"<NGP"*/);
		if(NGPTagList[BothCnt]!=NULL)
			delete []NGPTagList[BothCnt];
		NGPTagList[BothCnt]=new XMLElement*[NGPCount];
		int NGPCnt=0;
		for(XMLElement *E=ISTElement[BothCnt]->Datas.GetFirst();E!=NULL;E=E->GetNext()){
			if(strcmp(E->StartTag.TagName->GetString(),LangSolver.GetString(RepairBase_LS,LID_718)/*"NGP"*/)==0)
				NGPTagList[BothCnt][NGPCnt++]=E;
		}
		//NGPコムソート
		ComSortNGP(NGPCnt,NGPTagList[BothCnt],BothCnt);

		//NGPタグデータ格納リスト
		NGPTagDList[BothCnt]=new NGPTagDataList[NGPCount];

		//出現NGポイント格納リスト
		FindNGCntList[BothCnt]=new bool[NGPCount];

		//初期化
		#pragma omp parallel
		{
			#pragma omp for
			for(int Cnt=0;Cnt<NGPCount;Cnt++){
				FindNGCntList[BothCnt][Cnt]=false;	//falseに初期化

				for(XMLTagAttr *TA=NGPTagList[BothCnt][Cnt]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				    if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_719)/*"X"*/)==0)
						NGPTagDList[BothCnt][Cnt].x=TA->iAttrData;
				    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_720)/*"Y"*/)==0)
						NGPTagDList[BothCnt][Cnt].y=TA->iAttrData;
				    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_721)/*"RAL"*/)==0)
						NGPTagDList[BothCnt][Cnt].ral=QString(TA->AttrData->GetString()).mid(6);	//Basic:BlockInspection
				    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_722)/*"PG"*/)==0)
						NGPTagDList[BothCnt][Cnt].pg=TA->iAttrData;
				    else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_723)/*"ARA"*/)==0)
						NGPTagDList[BothCnt][Cnt].ara=QString(TA->AttrData->GetString());
				}
			}
		}

		//NGチェック済みかどうかの判断<RCH>タグを検索
		bool	CheckNG;
		CheckNG=isCheckedNGPoint(BothCnt);

		int		NextComCnt	=0;
		QStringList ARAList;
		for(int BaseCnt=0;BaseCnt<NGPCount;BaseCnt++){
			if(FindNGCntList[BothCnt][BaseCnt])
				continue;
			int BX		=NGPTagDList[BothCnt][BaseCnt].x;
			int BY		=NGPTagDList[BothCnt][BaseCnt].y;
			PG			=NGPTagDList[BothCnt][BaseCnt].pg;
			QString BRal=NGPTagDList[BothCnt][BaseCnt].ral;
			QString sARA=NGPTagDList[BothCnt][BaseCnt].ara;

			if(sARA.isEmpty()==false && ARAList.contains(sARA)==false)
				ARAList.append(sARA);

///			CheckNG=true;
			int ARAIndex;
			if((ARAIndex=ARAList.indexOf(sARA))==-1)
				ARAIndex=99999999;
			BX+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetX;
			BY+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[PG]->OrgOffsetY;
			for(int Col=0;Col<HeaderLabels->count();Col++){
				if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_724)/*"X, Y"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString().setNum(BX) + LangSolver.GetString(RepairBase_LS,LID_725)/*", "*/ + QString().setNum(BY));
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_726)/*"RAL"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BRal);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_727)/*"ARA"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_728)/*"ARAIndex"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,QString::number(ARAIndex).rightJustified(8,'0'));
//				else if(HeaderLabels->at(Col)=="NGJ")
//					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,TagNGJ);
//				else if(HeaderLabels->at(Col)=="NGI")
//					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,-1);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_729)/*"NGP"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BaseCnt);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_730)/*"Side"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,BothCnt);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_731)/*"RowIndex"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,RowIndex++);
				else if(HeaderLabels->at(Col)==LangSolver.GetString(RepairBase_LS,LID_732)/*"wARA"*/)
					SetDataToTable(TableWidget,SumFRowCnt+RowCnt,Col,sARA);
			}
///			//NGチェック済みかどうかの判断<RCH>タグをSELECT
///			if(CheckNG && !isCheckedNGPoint(PG,BX,BY,BothCnt))
///				CheckNG=false;

			NGPointList *p=new NGPointList(BX,BY,BRal);
			NGPBaseListForVRS=new NGPointBaseList();
			NGPBaseListForVRS->NGListForVRS.AppendList(p);
			NGPListForVRS[BothCnt].AppendList(NGPBaseListForVRS);
//			FindNGCntList[BothCnt][BaseCnt]=true;
			FindNGCntList[BothCnt][RowCnt]=true;
			MinX	=MaxX	=BX;
			MinY	=MaxY	=BY;
			NGIX1	=MaxX-W;
			NGIY1	=MaxY-H;
			NGIX2	=MinX+W;
			NGIY2	=MinY+H;
			RowCnt++;
			bool FirstNotMatch=true;

			for(int CompCnt=BaseCnt+1;CompCnt<NGPCount;CompCnt++){
				if(FindNGCntList[BothCnt][CompCnt])
					continue;
				int X	=NGPTagDList[BothCnt][CompCnt].x;
				int Y	=NGPTagDList[BothCnt][CompCnt].y;
				int wPG	=NGPTagDList[BothCnt][CompCnt].pg;
				X+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[wPG]->OrgOffsetX;
				Y+=IDataUnitInBase->MImageClassList[BothCnt]->ImageList[wPG]->OrgOffsetY;

				//NGポイントが最初の点もしくは隣接する点を含めてさらに描画エリア内に含まれるかどうかの判断
				NGPCompair	NGPComp=CompairSortValue(X,Y,wPG,BothCnt);
				if(NGPComp==Less)
					continue;
				else if(NGPComp==Large){
					if(FirstNotMatch)
						NextComCnt=CompCnt;
					break;
				}
				else if(NGPComp==NotMatch){
					if(FirstNotMatch && FindNGCntList[BothCnt][CompCnt]==false){
						NextComCnt=CompCnt;
						FirstNotMatch=false;
					}
					continue;
				}

///				//NGチェック済みかどうかの判断<RCH>タグをSELECT
///				if(CheckNG && !isCheckedNGPoint(wPG,X,Y,BothCnt))
///					CheckNG=false;
				if(X<MinX)
					MinX=X;
				if(X>MaxX)
					MaxX=X;
				if(Y<MinY)
					MinY=Y;
				if(Y>MaxY)
					MaxY=Y;
				NGIX1	=MaxX-W;
				NGIY1	=MaxY-H;
				NGIX2	=MinX+W;
				NGIY2	=MinY+H;
				NGPointList *p=new NGPointList(X,Y, BRal);
				NGPBaseListForVRS->NGListForVRS.AppendList(p);
				FindNGCntList[BothCnt][CompCnt]=true;
			}

			if(CheckNG){
				SetColorToTable(TableWidget,SumFRowCnt+RowCnt-1,twNGListCheckColor);
			}

			int FK;
			if(CheckFKey(FK,BothCnt)){
				SetColorToTable(TableWidget,RowCnt-1,ColorFKey[FK]);
			}
		}
		if(BothCnt==0){
			SumFRowCnt=RowCnt;
		}
		else{
			SumBRowCnt=RowCnt;
		}
		if(NGPTagDList[BothCnt]!=NULL){
			delete []NGPTagDList[BothCnt];
		}
		if(FindNGCntList[BothCnt]!=NULL){
			delete []FindNGCntList[BothCnt];
		}
	}
	TableWidget->setRowCount(SumFRowCnt+SumBRowCnt);
}
/*
bool RepairBase::isCheckedNGPoint(int pNumb,int X,int Y,int Side)
{
	for(XMLElement *E=ISTElement[Side]->Datas.GetFirst();E!=NULL;E=E->GetNext()){
		if(strcmp(E->StartTag.TagName->GetString(),"RCH")==0){
			int RCHX1,RCHY1,RCHX2,RCHY2;
			XMLTagAttr *TA;
			for(TA=E->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				if(strcmp(TA->AttrName->GetString(),"PG")==0){
					if(TA->iAttrData!=pNumb)
						break;
				}
			    else if(strcmp(TA->AttrName->GetString(),"X1")==0)
					RCHX1=TA->iAttrData;
			    else if(strcmp(TA->AttrName->GetString(),"Y1")==0)
					RCHY1=TA->iAttrData;
			    else if(strcmp(TA->AttrName->GetString(),"X2")==0)
					RCHX2=TA->iAttrData;
			    else if(strcmp(TA->AttrName->GetString(),"Y2")==0)
					RCHY2=TA->iAttrData;
			}
			if(TA!=NULL)
				continue;
			if(X>=RCHX1 && X<=RCHX2 && Y>=RCHY1 && Y<=RCHY2)
				return true;
		}
	}
	return false;
}
*/
bool RepairBase::isCheckedNGPoint(int Side)
{
	for(XMLElement *E=ISTElement[Side]->Datas.GetFirst();E!=NULL;E=E->GetNext()){
		if(strcmp(E->StartTag.TagName->GetString(),LangSolver.GetString(RepairBase_LS,LID_733)/*"RCH"*/)==0){
			return true;
		}
	}
	return false;
}

bool RepairBase::CheckedXML(QString &strAppXML,QString &ErrMsg)
{
	//IST内にApend
	strAppXML=LangSolver.GetString(RepairBase_LS,LID_734)/*"<RCH></RCH>"*/;
///	strAppXML=QString("<RCH WID=\"") + GetWorkerID()
///			+ QString("\" PG=\"") + QString::number(PG)
///			+ QString("\" X1=\"") + QString::number(MinX)
///			+ QString("\" Y1=\"") + QString::number(MinY)
///			+ QString("\" X2=\"") + QString::number(MaxX)
///			+ QString("\" Y2=\"") + QString::number(MaxY)
///			+ QString("\"></RCH>");

//	SetXML(&strAppXML);
	tXMLAppend.SetXML(&strAppXML);
	tXMLAppend.start();
	return true;
}

QString RepairBase::CreateFunctionStr(int FKey)
{
	QString Ret;

	Ret =	QString(/**/"<RFC PG=\"")	+ QString::number(PG)
		+	QString(/**/"\" X1=\"")		+ QString::number(MinX)
		+	QString(/**/"\" Y1=\"")		+ QString::number(MinY)
		+	QString(/**/"\" X2=\"")		+ QString::number(MaxX)
		+	QString(/**/"\" Y2=\"")		+ QString::number(MaxY)
		+	QString(/**/"\" FK=\"");

	Ret	+=	(FKey>=0 ? QString::number(FKey) : QString(""));

	Ret	+= QString(/**/"\"></RFC>");

	return Ret;
}

bool RepairBase::DeleteXMLStr(int Side, QString &str)
{
	//表面データか裏面データかの判断
	if(Side==0)
		strQNO=strQNO1;
	else
		strQNO=strQNO2;

	//送信リスト
	QList<QByteArray> list;
	list.append(str.toLocal8Bit().data());

	if(!xmlCont[Side]->Client_Delete(
		list,
		XMLFile[Side],
		Msg
		)){
		QMessageBox::information(&QWidget(),QObject::tr(/**/"Client_Delete Error"),Msg);
		return false;
	}
	return true;
}

//bool RepairBase::CheckedFunction(int KeyNumber,bool FChecked,int DelFKey,QString *strDelTag,QString *strUpTag)
bool RepairBase::CheckedFunction(int KeyNumber,bool FChecked,int DelFKey,QString *strDelTag,QString *strUpTag,int Side)
{
	//表面データか裏面データかの判断
	if(Side==0)
		strQNO=strQNO1;
	else
		strQNO=strQNO2;

	//ファンクションキー設定の前記述
	QString wstrTag;
		wstrTag=QString(/**/"<RFC PG=\"") + QString::number(PG)
			+ QString(/**/"\" X1=\"") + QString::number(MinX)
			+ QString(/**/"\" Y1=\"") + QString::number(MinY)
			+ QString(/**/"\" X2=\"") + QString::number(MaxX)
			+ QString(/**/"\" Y2=\"") + QString::number(MaxY)
			+ QString(/**/"\" FK=\"");
	//ファンクションキーデータがあるかのチェック
	if(FChecked)
		*strUpTag=LangSolver.GetString(RepairBase_LS,LID_747)/*""*/;
	else{
		*strUpTag=wstrTag + QString::number(KeyNumber)
				+ QString(/**/"\"></RFC>");
		if(KeyNumber==DelFKey){
			//TagAppend
			if(!xmlCont[Side]->Client_Update(
				strQNO,
				strUpTag->toLocal8Bit().data(),
				XMLFile[Side],
				Msg,
				QString::number(ClientNo[Side]).toLocal8Bit().data())
				){
				QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_750)/*"Client_Update Error"*/,Msg);
				return false;
			}
			return true;
		}
	}
	//TagDel
	*strDelTag=wstrTag + QString::number(DelFKey)
			+ QString(/**/"\"></RFC>");
///	if(!xmlCont[Side]->Client_TagDel(strQNO,strDelTag->toLocal8Bit().data(),strUpTag->toLocal8Bit().data(),XMLFile[Side],Msg)){
///		QMessageBox::information(&QWidget(),LangSolver.GetString(RepairBase_LS,LID_753)/*"Client_TagDel Error"*/,Msg);
///		return false;
///	}
	return true;
}

bool RepairBase::CheckFKey(int &FK,int Side)
{
	for(XMLElement *E=ISTElement[Side]->Datas.GetFirst();E!=NULL;E=E->GetNext()){
		if(strcmp(E->StartTag.TagName->GetString(),LangSolver.GetString(RepairBase_LS,LID_754)/*"RFC"*/)==0){
			int wPG,RCHX1,RCHY1,RCHX2,RCHY2;
			XMLTagAttr *TA;
			for(TA=E->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_755)/*"PG"*/)==0){
					if((TA->iAttrData)!=PG)
						break;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_756)/*"X1"*/)==0){
					if((TA->iAttrData)!=MinX)
						break;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_757)/*"Y1"*/)==0){
					if((TA->iAttrData)!=MinY)
						break;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_758)/*"X2"*/)==0){
					if((TA->iAttrData)!=MaxX)
						break;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_759)/*"Y2"*/)==0){
					if((TA->iAttrData)!=MaxY)
						break;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_760)/*"FK"*/)==0)
					FK=TA->iAttrData;
			}
			if(TA!=NULL)
				continue;
			return true;
		}
	}
	return false;
}

QTreeWidgetItem *RepairBase::CheckTrMasterList(QTreeWidgetItem *item,int col,int data)
{
	if(item->text(col).toInt()==data)
		return item;
	for(int i=0;i<item->childCount();i++){
		QTreeWidgetItem *itemChild=item->child(i);
		if(CheckTrMasterList(itemChild,col,data)!=NULL)
			return itemChild;
	}
	return NULL;
}

bool RepairBase::HaspCheck(QString strKey)
{
	QStringList RetList;
	Hasplib Hasp;
	if(Hasp.HaspExecute(RetList)==false)
		return false;
	for(int Cnt=0;Cnt<RetList.count();Cnt++){
		if(RetList.at(Cnt)==strKey){
			if(QDate::currentDate()<=QDate::fromString(RetList.at(Cnt-1),LangSolver.GetString(RepairBase_LS,LID_761)/*"yyyyMMdd"*/))
				return true;
		}
	}
	return false;
}

void RepairBase::SetSigmoid(double Volume,int Bright,int BrightArray[])
{
	if(Volume==0){
		return;
	}

	if(Volume==1 || Volume==-1){
		//Volumeが１またはー１の値の時は、直線でグラフを表示
		for(int i=0;i<=255;i++){
			BrightArray[i]=i;
		}
		return;
	}

	if(Volume>1){
		//Volumeが１より大きい値の時は、シグモイド関数でグラフを表示
		double OffsetY1	=255*(1/(1+pow(Volume,Bright/255.)));
		double dy1		=OffsetY1/Bright;
		double OffsetY2	=255*(1/(1+pow(Volume,-(255-Bright)/255.)));
		double dy2		=(255-OffsetY2)/(255-Bright);
		for(int i=0;i<=255;i++){
			if(i<Bright){
				BrightArray[i]=255*(1/(1+pow(Volume,-(i-Bright)/255.)))+dy1*(i-Bright);
			}
			else{
				BrightArray[i]=255*(1/(1+pow(Volume,-(i-Bright)/255.)))+dy2*(i-Bright);
			}
		}
	}
	else{
		//Volumeが１より小さい値の時は、対数関数でグラフを表示
		double Exp=255/log10(256.);
		for(int i=0;i<=255;i++){
//			BrightArray[i]=((Exp*(log10((double)(i+1))))-i)*Volume+i;
			BrightArray[i]=((Exp*(log10((double)(i+1))))-i)*(Volume+(1-Volume)*(i/255.))+i;
		}

/*		BrightArray[0]=0;
		double wExp=-log10(Volume);	//log10(0.0000000001) = -10
		double Exp=255/(log10(256.)+wExp);	//log10(0.0000000001) = -10
		for(int i=1;i<=255;i++){
//			BrightArray[i]=((Exp*(log10((double)(i))+wExp))-i)*Volume+i;
			BrightArray[i]=Exp*(log10((double)(i))+wExp);
		}
*/
	}
}

bool RepairBase::GetOutlineOffset(int MacID,QList<int> *DataX,QList<int> *DataY)
{
	QSqlQuery MacQuery;
	MacQuery.prepare(LangSolver.GetString(RepairBase_LS,LID_762)/*"select OUTLINEOFFSET,REMARK from MACHINE where MACHINEID=?"*/);
	MacQuery.addBindValue(MacID);
	MacQuery.exec();
	if(MacQuery.next()){
		//ログデータ（ヘッダー部）の為の情報を取得
		if(DLL_GetName!=NULL){
			if(!MacQuery.value(MacQuery.record().indexOf(LangSolver.GetString(RepairBase_LS,LID_763)/*"REMARK"*/)).isNull())
				SetMachineRemark(SType,&MacQuery.value(MacQuery.record().indexOf(LangSolver.GetString(RepairBase_LS,LID_764)/*"REMARK"*/)).toString());
		}
		if(!MacQuery.value(MacQuery.record().indexOf(LangSolver.GetString(RepairBase_LS,LID_765)/*"OUTLINEOFFSET"*/)).isNull()){
			QBuffer Buff(&MacQuery.value(MacQuery.record().indexOf(LangSolver.GetString(RepairBase_LS,LID_766)/*"OUTLINEOFFSET"*/)).toByteArray());
			if(Buff.open(QIODevice::ReadWrite)){
				int32	Ver;
				if(::Load(&Buff,Ver)==false)
					return false;
				int32	iOutlineOffsetInPageDimNumb;
				if(::Load(&Buff,iOutlineOffsetInPageDimNumb)==false)
					return false;
				for(int i=0;i<iOutlineOffsetInPageDimNumb;i++){
					int Dx,Dy;
					if(::Load(&Buff,Dx)==false){
						DataX->clear();
						DataY->clear();
						return false;
					}
					DataX->append(Dx);
					if(::Load(&Buff,Dy)==false){
						DataX->clear();
						DataY->clear();
						return false;
					}
					DataY->append(Dy);
				}
				return true;
			}
		}
	}
	return false;
}

bool RepairBase::SaveNGImage(QString InsID)
{
	for(int Cnt=0;Cnt<IDataUnit->MImageClassList.count();Cnt++){
		for(int i=0;i<PNumbForBase;i++){
			for(int j=0;j<ImgCnt[i];j++){
				if(!SaveNGImage(Cnt,i,j,InsID))
					return false;
			}
		}
	}
	return true;
}

bool RepairBase::SaveNGImage(int Both,int Page,int Cnt,QString InsID)
{
	QString strDir;
	if(GetSaveDirNGImage()==LangSolver.GetString(RepairBase_LS,LID_767)/*""*/){
		strDir=LangSolver.GetString(RepairBase_LS,LID_768)/*"//"*/ + HostName + LangSolver.GetString(RepairBase_LS,LID_769)/*"/"*/ + XMLFileDir + LangSolver.GetString(RepairBase_LS,LID_770)/*"/"*/ + LangSolver.GetString(RepairBase_LS,LID_771)/*"MID-"*/ + GetMasterID(SideType(Both)) + LangSolver.GetString(RepairBase_LS,LID_772)/*"/"*/ + LangSolver.GetString(RepairBase_LS,LID_773)/*"Lot-"*/ + GetLotName(SideType(Both));
	}
	else{
		strDir=GetSaveDirNGImage() + LangSolver.GetString(RepairBase_LS,LID_774)/*"/"*/ + QDate::currentDate().toString(LangSolver.GetString(RepairBase_LS,LID_775)/*"yyyyMMdd"*/) + LangSolver.GetString(RepairBase_LS,LID_776)/*"/"*/ + LangSolver.GetString(RepairBase_LS,LID_777)/*"MID-"*/ + GetMasterID(SideType(Both)) + LangSolver.GetString(RepairBase_LS,LID_778)/*"/"*/ + LangSolver.GetString(RepairBase_LS,LID_779)/*"Lot-"*/ + GetLotName(SideType(Both));
	}
	QDir Dir;
	Dir.mkpath(strDir);
	QFile file(strDir + LangSolver.GetString(RepairBase_LS,LID_780)/*"/"*/ + InsID.rightJustified(3,'0') + LangSolver.GetString(RepairBase_LS,LID_781)/*"-"*/ + QString::number(Page) + LangSolver.GetString(RepairBase_LS,LID_782)/*"_"*/ + QString::number(Cnt).rightJustified(3,'0') + LangSolver.GetString(RepairBase_LS,LID_783)/*".jpg"*/);
	if (!file.open(QIODevice::WriteOnly))
		return false;
	file.write(JDTDataList[Both][Page][Cnt]);
	file.close();
	return true;
}

bool RepairBase::SaveNGImage(QTableWidget *W,QStringList *HeaderLabels)
{
/*	//NGリストからNG画像を保存
	QString strTime=QDateTime::currentDateTime().toString("hhmmss");
	int RowCnt=W->rowCount();
	for(int Row=0;Row<RowCnt;Row++){
		int vNGI	=W->item(Row,HeaderLabels->indexOf("NGI"))->text().toInt();
		int vSide	=W->item(Row,HeaderLabels->indexOf("Side"))->text().toInt();
		QString vARA=W->item(Row,HeaderLabels->indexOf("ARA"))->text();
		if(JDTDataList[vSide]==NULL || vNGI==-1){
			//NG画像がない場合
			continue;
		}
		if(NGITagList[vSide]!=NULL){
			int vIDX,vIndex;
			for(XMLTagAttr *TA=NGITagList[vSide][vNGI]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				if(strcmp(TA->AttrName->GetString(),"IDX")==0)
					vIDX	=TA->iAttrData;
				else if(strcmp(TA->AttrName->GetString(),"Index")==0)
					vIndex	=TA->iAttrData;
			}
			//画像データ（JPEGデータ）
			if(JDTDataList[vSide][vIDX]==NULL)
				continue;
			if(DLL_SaveNGImage(&JDTDataList[vSide][vIDX][vIndex],&vARA,Row,&strTime)==false)
				return false;
		}
	}
	return true;
*/
	QString strTime=QDateTime::currentDateTime().toString(LangSolver.GetString(RepairBase_LS,LID_784)/*"hhmmss"*/);
	int RowCnt=W->rowCount();

	if(vNGI!=NULL){
		delete []vNGI;
	}
	vNGI	=new int[RowCnt];
	if(vSide!=NULL){
		delete []vSide;
	}
	vSide	=new int[RowCnt];
	if(vARA!=NULL){
		delete []vARA;
	}
	vARA	=new QString[RowCnt];
	if(vIDX!=NULL){
		delete []vIDX;
	}
	vIDX	=new int[RowCnt];
	if(vIndex!=NULL){
		delete []vIndex;
	}
	vIndex	=new int[RowCnt];
	if(vRealARA!=NULL){
		delete []vRealARA;
	}
	vRealARA=new QString[RowCnt];

	for(int Row=0;Row<RowCnt;Row++){
		vNGI[Row]		=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_785)/*"NGI"*/))->text().toInt();
		vSide[Row]		=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_786)/*"Side"*/))->text().toInt();
//		vARA[Row]		=W->item(Row,HeaderLabels->indexOf("ARA"))->text();
		vARA[Row]		=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_787)/*"wARA"*/))->text();
		vRealARA[Row]	=W->item(Row,HeaderLabels->indexOf(LangSolver.GetString(RepairBase_LS,LID_788)/*"ARA"*/))->text();
		if(JDTDataList[vSide[Row]]==NULL || vNGI[Row]==-1){
			//NG画像がない場合
			continue;
		}
		if(NGITagList[vSide[Row]]!=NULL){
			for(XMLTagAttr *TA=NGITagList[vSide[Row]][vNGI[Row]]->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
				if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_789)/*"IDX"*/)==0){
					vIDX[Row]	=TA->iAttrData;
				}
				else if(strcmp(TA->AttrName->GetString(),LangSolver.GetString(RepairBase_LS,LID_790)/*"Index"*/)==0){
					vIndex[Row]	=TA->iAttrData;
				}
			}
			if(vIDX[Row]<0 || vIDX[Row]>=JDTDataListCountPage[iSide] || vIndex[Row]<0 || vIndex[Row]>=JDTDataListCountJpg[vSide[Row]][vIDX[Row]]){
				//NG画像がない場合
				vIDX[Row]=-1;
				continue;
			}
		}
	}
	if(DLL_SaveNGImage(JDTDataList,vNGI,vSide,vIDX,vIndex,vARA,RowCnt,&strTime,vRealARA)==false){
		return false;
	}
	return true;
}

//数値リストの中の数値をすべてビットにして返す
//例：数値リスト[2,3,5,6]→54（=32+16+4+2（110110))
int RepairBase::GetListNumbers(const QStringList &List)
{
	int Ret=0;
	for(int i=0;i<List.count();i++){
//		Ret+=(int)pow(2.0,List.at(i).toInt()-1);
		Ret+=(1<<(List.at(i).toInt()-1));
	}
	return Ret;
}

NPListPack<NGPointList> *RepairBase::GetNGPListForVRS(int Side,int ListCount)
{
	int Counter=0;
	for(NGPointBaseList *P=NGPListForVRS[Side].GetFirst();P!=NULL;P=P->GetNext(),Counter++){
		if(Counter==ListCount)
			return &(P->NGListForVRS);
	}
	return NULL;
}

void RepairBase::ComSortNGP(int m_dcnt, XMLElement **m_data, int T)
{
	int	i,j;
	int	sort_cnt,sort_gap,sort_sw;
	sort_gap = sort_cnt = m_dcnt;
	if (sort_cnt<=1)
		goto loop_e;

	if(strcmp(GetNGSortOrder(),LangSolver.GetString(RepairBase_LS,LID_791)/*"A"*/)==0){
loop_1:
		sort_gap = sort_gap * 10 / 13;
		if (sort_gap == 0)
			sort_gap = 1;
		else if (sort_gap == 9 || sort_gap == 10)
			sort_gap = 11;

		sort_sw = 0;
		i = 0;
loop_2:
		j = i + sort_gap;
		if (GetSortValueNGP(m_data[i],T) > GetSortValueNGP(m_data[j],T)){
			XMLElement *Dest;
			Dest = m_data[i];
			m_data[i] = m_data[j];
			m_data[j] = Dest;
			sort_sw = 1;
		}
		if (j + 1 < sort_cnt){
			i++;
			goto loop_2;
		}
		if (sort_sw == 1 || sort_gap > 1)
			goto loop_1;
	}
	else{
loop_10:
		sort_gap = sort_gap * 10 / 13;
		if (sort_gap == 0)
			sort_gap = 1;
		else if (sort_gap == 9 || sort_gap == 10)
			sort_gap = 11;

		sort_sw = 0;
		i = 0;
loop_20:
		j = i + sort_gap;
		if (GetSortValueNGP(m_data[i],T) < GetSortValueNGP(m_data[j],T)){
			XMLElement *Dest;
			Dest = m_data[i];
			m_data[i] = m_data[j];
			m_data[j] = Dest;
			sort_sw = 1;
		}
		if (j + 1 < sort_cnt){
			i++;
			goto loop_20;
		}
		if (sort_sw == 1 || sort_gap > 1)
			goto loop_10;
	}
loop_e:
	return;
}

void RepairBase::ComSortNGI(int m_dcnt, XMLElement **m_data,int T)
{
	int	i,j;
	int	sort_cnt,sort_gap,sort_sw;
	sort_gap = sort_cnt = m_dcnt;
	if (sort_cnt<=1)
		goto loop_e;

	if(strcmp(GetNGSortOrder(),LangSolver.GetString(RepairBase_LS,LID_792)/*"A"*/)==0){
loop_1:
		sort_gap = sort_gap * 10 / 13;
		if (sort_gap == 0)
			sort_gap = 1;
		else if (sort_gap == 9 || sort_gap == 10)
			sort_gap = 11;

		sort_sw = 0;
		i = 0;
loop_2:
		j = i + sort_gap;
		if (GetSortValueNGI(m_data[i],T) > GetSortValueNGI(m_data[j],T)){
			XMLElement *Dest;
			Dest = m_data[i];
			m_data[i] = m_data[j];
			m_data[j] = Dest;
			sort_sw = 1;
		}
		if (j + 1 < sort_cnt){
			i++;
			goto loop_2;
		}
		if (sort_sw == 1 || sort_gap > 1)
			goto loop_1;
	}
	else{
loop_10:
		sort_gap = sort_gap * 10 / 13;
		if (sort_gap == 0)
			sort_gap = 1;
		else if (sort_gap == 9 || sort_gap == 10)
			sort_gap = 11;

		sort_sw = 0;
		i = 0;
loop_20:
		j = i + sort_gap;
		if (GetSortValueNGI(m_data[i],T) < GetSortValueNGI(m_data[j],T)){
			XMLElement *Dest;
			Dest = m_data[i];
			m_data[i] = m_data[j];
			m_data[j] = Dest;
			sort_sw = 1;
		}
		if (j + 1 < sort_cnt){
			i++;
			goto loop_20;
		}
		if (sort_sw == 1 || sort_gap > 1)
			goto loop_10;
	}
loop_e:
	return;
}

int RepairBase::GetSortValueNGP(XMLElement *Src,int T)
{
	int XY,P;
	for(XMLTagAttr *TA=Src->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
		char *Attr;
		if(strcmp((Attr=TA->AttrName->GetString()),GetNGSortXY())==0)
			XY=TA->iAttrData;
		else if(strcmp(Attr,LangSolver.GetString(RepairBase_LS,LID_793)/*"PG"*/)==0)
			P=TA->iAttrData;
	}

	if(strcmp(GetNGSortXY(),LangSolver.GetString(RepairBase_LS,LID_794)/*"X"*/)==0)
		return XY+IDataUnitInBase->MImageClassList[T]->ImageList[P]->OrgOffsetX;
	else
		return XY+IDataUnitInBase->MImageClassList[T]->ImageList[P]->OrgOffsetY;
}

int RepairBase::GetSortValueNGP(int XY,int P,int T)
{
	if(strcmp(GetNGSortXY(),LangSolver.GetString(RepairBase_LS,LID_795)/*"X"*/)==0){
		return XY+IDataUnitInBase->MImageClassList[T]->ImageList[P]->OrgOffsetX-IDataUnitInBase->MImageClassList[T]->ImageList[PG]->OrgOffsetX;
	}
	else{
		return XY+IDataUnitInBase->MImageClassList[T]->ImageList[P]->OrgOffsetY-IDataUnitInBase->MImageClassList[T]->ImageList[PG]->OrgOffsetY;
	}
}

int RepairBase::GetSortValueNGI(XMLElement *Src,int T)
{
	int XY,IDX,Index;
	for(XMLTagAttr *TA=Src->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
		char *Attr;
		if(strcmp((Attr=TA->AttrName->GetString()),GetNGSortXY())==0)
			XY=TA->iAttrData;
		else if(strcmp(Attr,LangSolver.GetString(RepairBase_LS,LID_796)/*"IDX"*/)==0)
			IDX=TA->iAttrData;
		else if(strcmp(Attr,LangSolver.GetString(RepairBase_LS,LID_797)/*"Index"*/)==0)
			Index=TA->iAttrData;
	}
	if(strcmp(GetNGSortXY(),LangSolver.GetString(RepairBase_LS,LID_798)/*"X"*/)==0){
		if(BuffPG[IDX]==NULL || Index>=ImgCnt[IDX])
			return XY+IDataUnitInBase->MImageClassList[T]->ImageList[IDX]->OrgOffsetX;
		else
			return XY+IDataUnitInBase->MImageClassList[T]->ImageList[BuffPG[IDX][Index]]->OrgOffsetX;
	}
	else{
		if(BuffPG[IDX]==NULL || Index>=ImgCnt[IDX])
			return XY+IDataUnitInBase->MImageClassList[T]->ImageList[IDX]->OrgOffsetY;
		else{
			return XY+IDataUnitInBase->MImageClassList[T]->ImageList[BuffPG[IDX][Index]]->OrgOffsetY;
		}
	}
}

int RepairBase::GetSortValue(XMLElement *Src,QString strAttr)
{
	for(XMLTagAttr *TA=Src->StartTag.Attrs.GetFirst();TA!=NULL;TA=TA->GetNext()){
		if(QString(TA->AttrName->GetString())==strAttr)
			return TA->iAttrData;
	}
	return -1;
}

RepairBase::NGPCompair RepairBase::CompairSortValue(int X,int Y,int P,int T)
{
	if(strcmp(GetNGSortXY(),LangSolver.GetString(RepairBase_LS,LID_799)/*"Y"*/)==0){
		if(strcmp(GetNGSortOrder(),LangSolver.GetString(RepairBase_LS,LID_800)/*"A"*/)==0){
			if(P == PG){
				if(Y < NGIY1)
					return Less;
				else if(Y > NGIY2)
					return Large;
				else{
					if(X >= NGIX1 && X <= NGIX2)
						return Match;
					else
						return NotMatch;
				}
			}
			else{
				if(GetSortValueNGP(Y,P,T) > NGIY2)
					return Large;
				else
					return NotMatch;
			}
		}
		else{
			if(P == PG){
				if(Y > NGIY2)
					return Less;
				else if(Y < NGIY1)
					return Large;
				else{
					if(X >= NGIX1 && X <= NGIX2)
						return Match;
					else
						return NotMatch;
				}
			}
			else{
				if(GetSortValueNGP(Y,P,T) < NGIY1)
					return Large;
				else
					return NotMatch;
			}
		}
	}
//	else if(strcmp(GetNGSortXY(),"X")==0){
	else{
		if(strcmp(GetNGSortOrder(),LangSolver.GetString(RepairBase_LS,LID_801)/*"A"*/)==0){
			if(P == PG){
				if(X < NGIX1)
					return Less;
				else if(X > NGIX2)
					return Large;
				else{
					if(Y >= NGIY1 && Y <= NGIY2)
						return Match;
					else
						return NotMatch;
				}
			}
			else{
				if(GetSortValueNGP(X,P,T) > NGIX2)
					return Large;
				else
					return NotMatch;
			}
		}
		else{
			if(P == PG){
				if(X > NGIX2)
					return Less;
				else if(X < NGIX1)
					return Large;
				else{
					if(Y >= NGIY1 && Y <= NGIY2)
						return Match;
					else
						return NotMatch;
				}
			}
			else{
				if(GetSortValueNGP(X,P,T) < NGIX1)
					return Large;
				else
					return NotMatch;
			}
		}
	}
}

void RepairBase::ComSortXML(int m_dcnt, QList<QByteArray> &XMLData)
{
	int	i,j;
	int	sort_cnt,sort_gap,sort_sw;
	sort_gap = sort_cnt = m_dcnt;
	if (sort_cnt<=1){
		goto loop_e;
	}

loop_1:
	sort_gap = sort_gap * 10 / 13;
	if (sort_gap == 0){
		sort_gap = 1;
	}
	else if (sort_gap == 9 || sort_gap == 10){
		sort_gap = 11;
	}

	sort_sw = 0;
	i = 0;
loop_2:
	j = i + sort_gap;
	if (GetSortValueEID(&XMLData[i]) > GetSortValueEID(&XMLData[j])){
		XMLData.swap(i,j);
		sort_sw = 1;
	}
	if (j + 1 < sort_cnt){
		i++;
		goto loop_2;
	}
	if (sort_sw == 1 || sort_gap > 1){
		goto loop_1;
	}
loop_e:
	return;
}

QStringList RepairBase::GetPieceNMList(int X,int Y,int W,int H,int Page,int Type)
{
	QStringList RetList;
//	int CenterX=X+(W>>1);
//	int CenterY=Y+(H>>1);
	for(int i=0;i<PieceInfoDataCount[Type];i++){
		QList<int> PiecePageList=PieceInfoDataList[Type][i].GetPiecePageList();
		int j;
		for(j=0;j<PiecePageList.count();j++){
			if(PiecePageList[j]==Page){
				break;
			}
		}
		if(j==PiecePageList.count()){
			continue;
		}
		//NG画像の四隅で判断する（暫定）
		if(PieceInfoDataList[Type][i].isInside(X,Y,Page)==true)
			RetList.append(PieceInfoDataList[Type][i].GetPieceName());
		else if(PieceInfoDataList[Type][i].isInside(X+W,Y,Page)==true)
			RetList.append(PieceInfoDataList[Type][i].GetPieceName());
		else if(PieceInfoDataList[Type][i].isInside(X,Y+H,Page)==true)
			RetList.append(PieceInfoDataList[Type][i].GetPieceName());
		else if(PieceInfoDataList[Type][i].isInside(X+W,Y+H,Page)==true)
			RetList.append(PieceInfoDataList[Type][i].GetPieceName());
	}
//	if(RetList.count()==0){
		RetList.append(LangSolver.GetString(RepairBase_LS,LID_802)/*""*/);
//	}
	return RetList;
}

QString RepairBase::GetEmptyARA(int X,int Y)
{
	int MinimumDistanceInt=-1;
	int MinimumDistance=INT_MAX;
	for(int i=0;i<PieceInfoDataCount[SType];i++){
		QList<int> PiecePageList=PieceInfoDataList[SType][i].GetPiecePageList();
		int j;
		for(j=0;j<PiecePageList.count();j++){
			if(PiecePageList[j]==PG){
				break;
			}
		}
		if(j==PiecePageList.count()){
			continue;
		}
		//引数のX,Y座標から一番近い個片を調べる
		int Distance=PieceInfoDataList[SType][i].GetDistanceFromCenter(X,Y,IDataUnit->MImageClassList[SType]->ImageList[PieceInfoDataList[SType][i].GetFirstPiecePage()]->OrgOffsetX,IDataUnit->MImageClassList[SType]->ImageList[PieceInfoDataList[SType][i].GetFirstPiecePage()]->OrgOffsetY,IDataUnit->MImageClassList[SType]->ImageList[PieceInfoDataList[SType][i].GetLastPiecePage()]->OrgOffsetX,IDataUnit->MImageClassList[SType]->ImageList[PieceInfoDataList[SType][i].GetLastPiecePage()]->OrgOffsetY);
		if(Distance==-1){
			continue;
		}
		if(Distance<MinimumDistance){
			MinimumDistance		=Distance;
			MinimumDistanceInt	=i;
		}
	}
	if(MinimumDistanceInt==-1){
		return LangSolver.GetString(RepairBase_LS,LID_803)/*""*/;
	}
	return PieceInfoDataList[SType][MinimumDistanceInt].GetPieceName() + LangSolver.GetString(RepairBase_LS,LID_804)/*"外"*/;
}

bool RepairBase::OpenDebugLogFile(QString OutputDir,QString OutputFileName)
{
	//デバッグログファイルがOpenしている場合、closeする
	if(DebugLogFile.isOpen()==true){
		WriteDebugLogFile(LangSolver.GetString(RepairBase_LS,LID_805)/*"File Close. Next is "*/ + OutputFileName);
		DebugLogFile.close();
	}

	//保存先の設定
	QString strPath=OutputDir;
	if(strPath.right(1)!=LangSolver.GetString(RepairBase_LS,LID_806)/*"/"*/){
		strPath+=LangSolver.GetString(RepairBase_LS,LID_807)/*"/"*/;
	}

	//保存先のフォルダが無ければ作る
	char delim = '/';
	QStringList dirs = (strPath).split(delim, QString::SkipEmptyParts);
	QDir dir(dirs[0] + delim);
	for(int i=1; i<dirs.count(); i++){
		if(!dir.exists(dirs[i])){
			if(!dir.mkdir(dirs[i]))
				return false;
		}
		if(!dir.cd(dirs[i]))
			return false;
	}

	//保存ファイル名の設定
	strPath+=OutputFileName + LangSolver.GetString(RepairBase_LS,LID_808)/*".log"*/;

	DebugLogFile.setFileName(strPath);
	if(DebugLogFile.open(QIODevice::Append)==false){
		return false;
	}
	DebugLogFileStream.setDevice(&DebugLogFile);
	WriteDebugLogFile(LangSolver.GetString(RepairBase_LS,LID_809)/*"File Open."*/);
	return true;
}

void RepairBase::WriteDebugLogFile(const QString &WriteMsg)
{
	if(GetOutputDebugLog()==true){
		DebugLogFileStream << QDateTime::currentDateTime().toString(LangSolver.GetString(RepairBase_LS,LID_810)/*"yyyy/MM/dd HH:mm:ss.zzz : "*/) << WriteMsg << endl;
	}
}

void RepairBase::ColorSetting(QList<QPair<QString, QString> > &citemList)
{
	QFile cfile(LangSolver.GetString(RepairBase_LS,LID_811)/*"./Color.dat"*/);
	QTextStream cin(&cfile);
	
	//QList<QPair<int, double> > list;
	QPair<QString, QString> pair;
  
	cfile.open(QIODevice::ReadOnly | QIODevice::Text);
    while (!cin.atEnd()) {
		 pair.first =cin.readLine();
         pair.second =cin.readLine();
		 citemList.append(pair); 
     }
	 cfile.close(); 
}
XMLAppendThread::XMLAppendThread()
{
}

void XMLAppendThread::run()
{
	emit SignalClient_Update(XML);
//	QString ErrMsg;
//	Client->Client_Update(QNO,XML,XMLFile,ErrMsg);
//	if(!Client->Client_Update(QNO,XML,XMLFile,ErrMsg)){
//		QMessageBox::information(&QWidget(),QObject::tr("Client_Update Error"),ErrMsg);
//		return;
//	}
}

ErrNextThread::ErrNextThread()
{
	StopFlag	=true;
}

void ErrNextThread::run()
{
	StopFlag=false;
	while(!StopFlag){
		emit SignalIsChanged();
		msleep(20);
	}
}
