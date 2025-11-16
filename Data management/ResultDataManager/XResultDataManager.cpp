#include "ResultDataManagerResource.h"
#include "XResultDataManager.h"
#include "XMLClient.h"
#include "XDatabaseLoader.h"
#include "XMLGeneralFunc.h"
#include "XDirectoryAPI.h"
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QRegularExpression>
#include "DeleteThread.h"

extern	DeleteThread *DelThread;

ResultDataManagerParam::ResultDataManagerParam(void)
{
	ImageDrive	=/**/"Z:";

	XML_IPAddress	=/**/"localhost";
	XML_Port		=12345;

	DatabaseHost	=/**/"localhost";
	DatabasePort	=3051;
	DatabaseFileName=/**/"c:/Data/Regulus64.fdb";
	WaitMilisec		=20;

	SetParam(&ImageDrive				, /**/"Setting" ,/**/"ImageDrive"		,LangSolver.GetString(XResultDataManager_LS,LID_48)/*"NG画像のフォルダパス(Z:)"*/											,0);
	SetParam(&XML_IPAddress				, /**/"Setting" ,/**/"XML_IPAddress"	,LangSolver.GetString(XResultDataManager_LS,LID_49)/*"XMLサーバーを起動しているPCのIPアドレス(192.168.0.200)"*/			,0);
	SetParam(&XML_Port					, /**/"Setting" ,/**/"XML_Port"			,LangSolver.GetString(XResultDataManager_LS,LID_50)/*"XMLサーバーへの接続ポート番号(12345)"*/								,0);
	SetParam(&DatabaseHost				, /**/"Setting" ,/**/"DatabaseHost"		,LangSolver.GetString(XResultDataManager_LS,LID_51)/*"データベースのホスト名(IPアドレスまたはPC名)"*/						,0);
	SetParam(&DatabasePort				, /**/"Setting" ,/**/"DatabasePort"		,LangSolver.GetString(XResultDataManager_LS,LID_52)/*"FireBirdの接続ポート番号(3051)"*/									,0);
	SetParamFileName(&DatabaseFileName	, /**/"Setting" ,/**/"DatabaseFileName"	,LangSolver.GetString(XResultDataManager_LS,LID_53)/*"データベースファイルへのフルパス(C:/Data/Regulus64.fdb)"*/			,0);
	SetParam(&WaitMilisec				, /**/"Setting" ,/**/"WaitMilisec"		,LangSolver.GetString(XResultDataManager_LS,LID_54)/*"Wait milisec for access Items"*/									,0);
}



void DeleteJDT(const QString &ResultStr
				,ResultDataManagerParam	*SParam, QString *filepath)
{
	QString NGJFile;
	if(GetXMLAttrStr (ResultStr,/**/"NGJ",NGJFile)==true){

		QString	FileName=SParam->ImageDrive + QDir::separator()+NGJFile;
		QStringList	List=SParam->ImageDrive.split(QRegularExpression(/**/"[/\\\\]"),QString::SplitBehavior::SkipEmptyParts);
		int	LPoint=0;
		while(LPoint<List.count()){
			if((NGJFile.at(0)=='/' || NGJFile.at(0)=='\\') && (NGJFile.at(0)=='/' || NGJFile.at(0)=='\\')){
				NGJFile=NGJFile.remove(0,2);
				if(NGJFile.contains(/**/"NGImage2")==true){
					NGJFile=NGJFile.section('/',1);
					NGJFile=QString(/**/"NGImage2/")+NGJFile;
				}
				else if(NGJFile.contains(/**/"NGImage")==true){
					NGJFile=NGJFile.section('/',1);
					NGJFile=QString(/**/"NGImage/")+NGJFile;
				}
				FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
			}
			else if(NGJFile.at(0)=='/' || NGJFile.at(0)=='\\'){
				NGJFile=NGJFile.remove(0,1);
				FileName=SParam->ImageDrive + QDir::separator()+NGJFile;
			}
			else if(NGJFile.left(List[LPoint].count())==List[LPoint]){
				NGJFile=NGJFile.mid(List[LPoint].count());
				FileName=SParam->ImageDrive + QDir::separator()+NGJFile;
				LPoint++;
			}
			else{
				FileName=SParam->ImageDrive + QDir::separator()+NGJFile;
				break;
			}
		}

		QFileInfo finfo(FileName);
		QString fileDirPath = finfo.path();
		QStringList	FileList= GetDirectoryFileList( fileDirPath, finfo.fileName());
		
		QStringList filePathList;
		for(int j=0;j<FileList.count();j++){
			filePathList << (fileDirPath + QDir::separator() + FileList[j]);
		}

		DelThread->addDelFile(filePathList);
		//for(int j=0;j<FileList.count();j++){
		//	DeleteFileApi(fileDirPath + QDir::separator() + FileList[j]);
		//	//QFile	JdtFile(FInfo.absolutePath() + ::GetSeparator()+FileList[j]);
		//	//JdtFile.remove();
		//}

		//サブフォルダ内にファイルがないときフォルダごと削除する
		//QStringList	ZeroSearchFilter;
		//FileSearchFilter.append("*.jdt");

		//FileList=SearchName.entryList(ZeroSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
		//if(FileList.count()==0){
		//	QDir	D;
		//	D.rmdir(FInfo.absolutePath());
		//}
		if(filepath!=NULL){
			*filepath = SParam->ImageDrive + QDir::separator() + NGJFile;
		}
	}
}

void DeleteJDT(const QStringList &ResultStrList
				,ResultDataManagerParam	*SParam, QString *filepath)
{
	DelThread->pause();
	for(int i=0; i<ResultStrList.count(); i++){
		DeleteJDT(ResultStrList[i], SParam, filepath);
	}
	DelThread->pause(false);
}

void DeleteEmptyDirectory(QString filepath)
{
	if(filepath.isEmpty()==false){
		//QDir SearchName(filepath);
		//QStringList FileSearchFilter;
		//QStringList	ZeroSearchFilter;
		//QStringList FileList;
		//FileSearchFilter.append("*.*");

		//FileList=SearchName.entryList(ZeroSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
		//if(FileList.count()==0){
		if(IsEmptyDirectory(filepath)==true){
			QDir	D;
			D.rmdir(filepath);
		}
	}
}

void DeleteTable(const QString &TableStr
					,XMLServerHandle	*XMLServer
					,std::shared_ptr<DatabaseLoader>	SQLDatabase ,QSqlDatabase &DB
					,ResultDataManagerParam	*SParam, QString *filepath)

{
	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		return;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
	if(OpeHandle==NULL){
		return;
	}

	int MachineID=-1;
	int MasterCode=-1;
	QString LotFilename;

	QString		OutputStr	=QString(/**/"<IST NGJ/>");
	QString		SearchStr	=QString(/**/"<IST */>");
	QStringList	ResultListStr;
	bool	SelectRet=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
	if(SelectRet==true){
		int	N=ResultListStr.count();
		DeleteJDT(ResultListStr, SParam, filepath);
	}

	QRegularExpression exp;
	const QString filt = /**/"(\\d+)-(\\d+)/(.+)";
	bool SelectRet2 = false;

	exp.setPattern(filt);
	if(exp.exactMatch(TableStr)==true){
		MachineID = exp.cap(1).toInt();
		MasterCode = exp.cap(2).toInt();
		LotFilename = exp.cap(3);

		SelectRet2 = true;
	}

	if(SelectRet2==false){
		QStringList list = TableStr.split('/');

		if(list.count()==2){
			LotFilename = list.last();
			QStringList codeList = list.first().split('-');
			if(codeList.count()==2){
				MachineID = codeList.first().toInt();
				MasterCode = codeList.last().toInt();
				SelectRet2 = true;
			}
		}
	}
	//// 検査履歴をデータベースから削除する
	//OutputStr	=QString("<LOTINFO LAT/>");
	//SearchStr	=QString("<LOTINFO/>");
	//QString		ResultStr;
	//int			LotAutoCount=0;
	//bool	SelectRet1=OpeHandle->SelectFirst(OutputStr,SearchStr,"",ResultStr);// 検査ロットのユニーク番号取得
	//if(SelectRet1==true){
	//	QString	LotAutoCountStr;
	//	GetXMLAttrStr (ResultStr,"LAT",LotAutoCountStr);
	//	bool	ok;
	//	LotAutoCount	=LotAutoCountStr.toInt(&ok);
	//	if(ok==false){
	//		SelectRet1=false;
	//	}
	//}
	int LotAutoCount = ReadLotAutoCount(TableStr, XMLServer);// マスターコード検索情報

	if(SelectRet2==false){
		OutputStr	=QString(/**/"<IST><MASTERINFO MASTER/></IST>");
		SearchStr	=QString(/**/"<IST><MASTERINFO */></IST>");
		QString ResultStr;
		SelectRet2=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスターコード取得1
		if(SelectRet2==true){
			QString	MasterCodeStr;
			GetXMLAttrStr (ResultStr,/**/"MASTER",MasterCodeStr);
			bool ok;
			MasterCode	=MasterCodeStr.toInt(&ok);
			if(ok==false){
				SelectRet2=false;
			}
		}
	}
	if(SelectRet2==false){
		OutputStr	=QString(/**/"<IST><MASTER MID/></IST>");
		SearchStr	=QString(/**/"<IST><MASTER */></IST>");
		QString ResultStr;
		bool SelectRet2=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスターコード取得2
		if(SelectRet2==true){
			QString	MasterCodeStr;
			GetXMLAttrStr (ResultStr,/**/"MID",MasterCodeStr);
			bool ok;
			MasterCode	=MasterCodeStr.toInt(&ok);
			if(ok==false){
				SelectRet2=false;
			}
		}
	}
	if(SelectRet2==false){
		OutputStr = /**/"<IST><MNM MID/></IST>";
		SearchStr = /**/"<IST><MNM */></IST>";
		QString ResultStr;
		SelectRet2=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスター名称取得 -> データベースからマスターコード検索・取得
		if(SelectRet2==true){
			QString	MasterName;
			GetXMLAttrStr(ResultStr, /**/"MID", MasterName);
			bool ok;
			//MasterCode = MasterCodeStr.toInt(&ok);
			//if(ok==false){
			//	SelectRet2=false;
			//}
			QSqlQuery query(DB);
			query.exec(QString(/**/"SELECT MASTERCODE FROM MASTERDATA WHERE MASTERNAME=\'%1\'").arg(MasterName));
			if(query.next()==true){
				MasterCode = query.record().value(/**/"MASTERCODE").toInt();
			}else{
				SelectRet2 = false;
			}
		}
	}
	XMLServer->CloseXMLOperation(OpeHandle);
	if(SelectRet2==true){
		if(LotAutoCount!=-1){
			SQLDatabase->G_DeleteInspectionLot(DB,LotAutoCount,MasterCode);
		}else{
			QString qstr = QString(/**/"DELETE * FROM INSPECTIONLOT WHERE IDNAME=\'%1\'").arg(LotFilename);
			QSqlQuery query;
			query.exec(qstr);
		}
	}
	XMLServer->DeleteTable(TableStr);
}

void DeleteTable(const QString &TableStr, int LotAutoCount, int MasterCode
	,XMLServerHandle *XMLServer
	,std::shared_ptr<DatabaseLoader>	SQLDatabase, QSqlDatabase &DB
	,ResultDataManagerParam *SParam, QString *filepath)
{
	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		return;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
	if(OpeHandle==NULL){
		return;
	}

	QString		OutputStr	=QString(/**/"<IST NGJ/>");
	QString		SearchStr	=QString(/**/"<IST */>");
	QStringList	ResultListStr;
	bool	SelectRet=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
	if(SelectRet==true){
		int	N=ResultListStr.count();
		for(int i=0;i<N;i++){
			DeleteJDT(ResultListStr[i], SParam, filepath);
		}
	}

	XMLServer->CloseXMLOperation(OpeHandle);
	OpeHandle->Close();
	delete OpeHandle;

	XMLServer->DeleteTable(TableStr);
	SQLDatabase->G_DeleteInspectionLot(DB, LotAutoCount, MasterCode);
}

int ReadLotAutoCount(const QString &TableStr, XMLServerHandle *XMLServer)
{
	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		return -1;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
	if(OpeHandle==NULL){
		return -1;
	}

	// 検査履歴をデータベースから削除する
	QString OutputStr	=QString(/**/"<LOTINFO LAT/>");
	QString SearchStr	=QString(/**/"<LOTINFO */>");
	QString		ResultStr;
	int			LotAutoCount=-1;
	bool	SelectRet1=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// 検査ロットのユニーク番号取得
	
	if(SelectRet1==true){
		QString	LotAutoCountStr;
		GetXMLAttrStr (ResultStr,/**/"LAT",LotAutoCountStr);
		bool	ok;
		LotAutoCount	=LotAutoCountStr.toInt(&ok);
		if(ok==false){
			LotAutoCount = -1;
		}
	}

	XMLServer->CloseXMLOperation(OpeHandle);
	OpeHandle->Close();
	delete OpeHandle;

	return LotAutoCount;
}

int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer)
{
	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		return -1;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
	if(OpeHandle==NULL){
		return -1;
	}

	QString OutputStr = /**/"<IST><MASTERINFO MASTER/></IST>";
	QString SearchStr = /**/"<IST><MASTERINFO */></IST>";
	QString ResultStr;

	int MasterCode=0;
	bool SelectRet1=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスターコード取得1
	if(SelectRet1==true){
		QString	MasterCodeStr;
		GetXMLAttrStr (ResultStr,/**/"MASTER",MasterCodeStr);
		bool ok;
		MasterCode = MasterCodeStr.toInt(&ok);
		if(ok==true){
			XMLServer->CloseXMLOperation(OpeHandle);
			OpeHandle->Close();
			delete OpeHandle;
			return MasterCode;
		}
	}

	OutputStr	=QString(/**/"<IST><MASTER MID/></IST>");
	SearchStr	=QString(/**/"<IST><MASTER */></IST>");

	SelectRet1=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスターコード取得2
	if(SelectRet1==true){
		QString	MasterCodeStr;
		GetXMLAttrStr (ResultStr,/**/"MID",MasterCodeStr);
		bool ok;
		MasterCode	=MasterCodeStr.toInt(&ok);
		if(ok==true){
			XMLServer->CloseXMLOperation(OpeHandle);
			OpeHandle->Close();
			delete OpeHandle;
			return MasterCode;
		}
	}
	
	XMLServer->CloseXMLOperation(OpeHandle);
	OpeHandle->Close();
	delete OpeHandle;
	return -1;
}

int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer, QSqlDatabase &DB)
{
	int ret = ReadLotMasterCode(TableStr, XMLServer);// ロットのみで分かれば良し
	if(ret!=-1){
		return ret;
	}

	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		return -1;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
	if(OpeHandle==NULL){
		return -1;
	}

	QString OutputStr = /**/"<IST><MNM MID/></IST>";
	QString SearchStr = /**/"<IST><MNM */></IST>";
	QString ResultStr;
	
	bool SelectRet1=OpeHandle->SelectFirst(OutputStr,SearchStr,/**/"",ResultStr);// マスター名称取得 -> データベースからマスターコード検索・取得
	if(SelectRet1==true){
		QString	MasterName;
		GetXMLAttrStr(ResultStr, /**/"MID", MasterName);
		bool ok;
		//MasterCode = MasterCodeStr.toInt(&ok);
		//if(ok==false){
		//	SelectRet2=false;
		//}
		QSqlQuery query(DB);
		query.exec(QString(/**/"SELECT MASTERCODE FROM MASTERDATA WHERE MASTERNAME=\'%1\'").arg(MasterName));
		if(query.next()==true){
			bool ok;
			int MasterCode;
			MasterCode = query.record().value(/**/"MASTERCODE").toInt(&ok);
			if(ok==true){
				XMLServer->CloseXMLOperation(OpeHandle);
				OpeHandle->Close();
				delete OpeHandle;
				return MasterCode;
			}
		}
	}
	
	XMLServer->CloseXMLOperation(OpeHandle);
	OpeHandle->Close();
	delete OpeHandle;
	return -1;
}