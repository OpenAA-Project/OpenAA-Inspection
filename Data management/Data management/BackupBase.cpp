/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\BackupBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "BackupBase.h"
#include "XGeneralFunc.h"
#include "Regulus64System.h"
#include <QtSql>

extern QStringList MPathList;
QString Path;
BackupBase::BackupBase(QObject *parent) :
    QObject(parent)
{
}
void BackupBase::FieldSave(QIODevice &Device,const QString &Table)
{
	QSqlQuery Query(/**/"SELECT * FROM " + Table);
	int Cnt = Query.record().count();
	QByteArray Type = QByteArray(typeid(this).name());
	::Save(&Device, Type);
	::Save(&Device, Cnt);
	for(int i=0; i<Cnt; i++){
		QString Fieid=Query.record().fieldName(i);
		::Save(&Device, Fieid);
	}
}
void BackupBase::FieldLoad(QIODevice &Device, QStringList &BField)
{
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	QString Field;
	for(int i=0; i<Cnt; i++){
		if(::Load(&Device, Field)==false)
			return ;
		BField.append(Field);
	}
}
void BackupBase::FieldGet(const QString &Table, QStringList &NowField)
{
	QSqlQuery Query(/**/"SELECT * FROM "+ Table);
	int Field = Query.record().count();//フィールド数
	for (int i=0; i<Field ; i++)
		NowField.append(Query.record().fieldName(i));
}
void BackupBase::RestoreField(QStringList &Backup, QStringList &Now, QString &Table, QString &Insert)
{
	QString sInsert;
	QString sAtai;
	for (int i=0; i<Backup.size(); i++){
		if(Now.indexOf(Backup.at(i))!=-1){//現状のデータベースとBackupのフィールドを比較、共通でなければ-1
			if(i!=0){//最初以外
				sInsert.append(/**/",");
				sAtai.append(/**/",");
			}
			sInsert.append(Backup.at(i));
			sAtai.append(/**/"?");
		}
	}
	Insert=/**/"INSERT INTO " + Table + /**/" (" + sInsert + /**/") VALUES (" + sAtai + /**/")";
}
void BackupBase::save(QIODevice &Device,const QVariant &value){
	::Save(&Device,value.type());
	switch(value.type()){
	case  2: ::Save(&Device,value.toInt())		;return;
	case 10: ::Save(&Device,value.toString())	;return;
	//case 12: ::Save(&Device,value.toByteArray());return;
	case 16: ::Save(&Device,value.toDateTime())	;return;
	default: ::Save(&Device,value.toByteArray());return;
	}
}
bool BackupBase::load(QIODevice &Device,QSqlQuery &Query){
	int type;
	if(::Load(&Device,type)==false)
		return false;
	switch(type){
	case  2:
		{
			int i;
			if(::Load(&Device,i)==false)
				return false;
			Query.addBindValue(i);
			break;
		}
	case 10:
		{
			QString str;
			if(::Load(&Device,str)==false)
				return false;
			Query.addBindValue(str);
			break;
		}
	/*case 12:
		{
			QByteArray byte;
			if(::Load(&Device,byte)==false)
				return false;
			Query.addBindValue(byte);
			break;
		}*/
	case 16:
		{
			QDateTime date;
			if(::Load(&Device,date)==false)
				return false;
			Query.addBindValue(date);
			break;
		}
	//default: return false;
	default:
		{
			QByteArray byte;
			if(::Load(&Device,byte)==false)
				return false;
			Query.addBindValue(byte);
			break;
		}
	}
	return true;
}
//================================================
MasterData::MasterData(QObject *parent)
	: BackupBase(parent)
{
	Image	 =new MasterImage	(this);
	Page	 =new MasterPage	(this);
	Category =new MasterCategory(this);
}
//MasterData::~MasterData(){
//	delete Image;
//	delete Page;
//	delete Category;
//}
void MasterData::Update(QStringList &DataList){
	QString OldMacID = getCurrentMachineID(DataList[0]);
	if(OldMacID!=DataList[1])
		Image->UpdateMachineID(DataList[0],DataList[1],OldMacID);
	QSqlQuery updateQuery;
	updateQuery.prepare(/**/"UPDATE MASTERDATA SET REMARK=?,MASTERNAME=?,WORKERID=?,MACHINEID=? WHERE MASTERCODE=?");
	for(int i=4;i>=0;i--){
		updateQuery.addBindValue(DataList[i]);
	}
	updateQuery.exec();
}
QString MasterData::getCurrentMachineID(QString &MasterCode){
	QSqlQuery Query(/**/"SELECT MACHINEID FROM MASTERDATA WHERE MASTERCODE="+ MasterCode);
	if(Query.next()==false)
		return /**/"-1";	
	return Query.value(0).toString();
}
void MasterData::ALLDelete(QString &CATEGORYID)
{
	QString Select=/**/"SELECT MASTERCODE FROM MASTERDATA";
	if(CATEGORYID!=/**/"-1")
		Select.append(/**/" WHERE CATEGORYID=" + CATEGORYID);
	QSqlQuery Query(Select);
	QString MasterCode;
	while(Query.next()){
		MasterCode=Query.value(0).toString();
		Image->Delete(MasterCode);
		Delete(MasterCode);
		Page->Delete(MasterCode);
	}
	if(CATEGORYID==/**/"-1")
		return Category->ALLDlete();
	Category->Delete(CATEGORYID);
	Select=/**/"SELECT CATEGORYID FROM MASTERCATEGORY WHERE PARENTID="+CATEGORYID;
	QSqlQuery SleQuery(Select);
	while(SleQuery.next()){
		QString CATEGORY=Query.value(0).toString();
		ALLDelete(CATEGORY);
	}
}
void MasterData::Delete(const QString &Mastercode)
{
	QSqlQuery MasterQuery(/**/"DELETE FROM MASTERDATA WHERE MASTERCODE=" + Mastercode);
	MasterQuery.exec();
}
void MasterData::Select(QSqlQueryModel *model ,QString &Select, QString &Order)
{
	QString Str;
	Str=/**/"SELECT MASTERDATA.MASTERCODE, MASTERDATA.MASTERNAME, MASTERDATA.MACHINEID, MASTERDATA.REGTIME, MASTERDATA.REMARK, MASTERDATA.LASTEDITTIME, "
							/**/"MASTERDATA.WORKERID, MASTERDATA.VERSION,  MASTERCATEGORY.FOLDERNAME, MASTERDATA.DOTPERLINE, "
							/**/"MASTERDATA.MAXLINES, MASTERDATA.PAGENUMB, MASTERDATA.LAYERNUMB,MASTERDATA.PHASENUMB, MASTERDATA.MASTERTYPE from MASTERDATA LEFT JOIN MASTERCATEGORY ON MASTERDATA.CATEGORYID=MASTERCATEGORY.CATEGORYID ";
	model->setQuery(Str+ Select + Order);
	model->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("NAME"));
	model->setHeaderData(2, Qt::Horizontal, tr("MACID"));
	model->setHeaderData(3, Qt::Horizontal, tr("REGTIME"));
	model->setHeaderData(4, Qt::Horizontal, tr("REMARK"));
	model->setHeaderData(5, Qt::Horizontal, tr("LASTEDITTIME"));
	model->setHeaderData(6, Qt::Horizontal, tr("WORKERID"));
	model->setHeaderData(7, Qt::Horizontal, tr("VERSION"));
	model->setHeaderData(8, Qt::Horizontal, tr("CATEGORYID"));
	model->setHeaderData(9, Qt::Horizontal, tr("DOTPERLINE"));
	model->setHeaderData(10, Qt::Horizontal, tr("MAXLINES"));
	model->setHeaderData(11, Qt::Horizontal, tr("PAGENUMB"));
	model->setHeaderData(12, Qt::Horizontal, tr("LAYERNUMB"));
	model->setHeaderData(13, Qt::Horizontal, tr("PHASENUMB"));
	model->setHeaderData(14, Qt::Horizontal, tr("MASTERTYPE"));
}
void MasterData::Save(QIODevice &Device, const QString &MASTERCODE)
{
	QString Buffer;
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);
	QSqlQuery Query(/**/"SELECT * FROM MASTERDATA WHERE MASTERCODE="+ MASTERCODE);
 	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//DataSelect数
	::Save(&Device, Cnt);
	for (int iX=0; iX<Cnt ; iX++){
		for (int iY=0; iY<iField; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}
void MasterData::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData, QString &MASTERCODE)
{
	QSqlQuery InsertQuery;
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		InsertQuery.prepare(InsertData);
		for (int iY=0; iY<iField; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"MASTERCODE"){
				int type;
				if(::Load(&Device,type)==false)
					return;
				InsertQuery.addBindValue(MASTERCODE.toInt());
				int iMasterID;
				if(::Load(&Device,iMasterID)==false)
					return;
				QString MasterID = QString::number(iMasterID);
				if (MasterID == MASTERCODE)
				{
					QSqlQuery Query(/**/"DELETE FROM MASTERDATA WHERE MASTERCODE=" + MasterID);
					Query.exec();
				}
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}
MasterPage::MasterPage(QObject *parent)
	: BackupBase(parent)
{
}
void MasterPage::Select(QString FolderID, QSqlQueryModel *model)
{
	QString sSel;
	if(FolderID==/**/"-1"){
		sSel=/**/"WHERE MASTERDATA.CATEGORYID<=0";
	}else{
		sSel=/**/"WHERE MASTERDATA.CATEGORYID="+ FolderID;
	}
	QString sOrder=/**/"ORDER BY MASTERDATA.MASTERCODE";

	QString Str=/**/"SELECT MASTERDATA.MASTERCODE, MASTERDATA.MASTERNAME, MASTERDATA.MACHINEID, MASTERDATA.REGTIME, MASTERDATA.REMARK, MASTERDATA.LASTEDITTIME, "
							/**/"MASTERDATA.WORKERID, MASTERDATA.VERSION,  MASTERCATEGORY.FOLDERNAME, MASTERDATA.DOTPERLINE, "
							/**/"MASTERDATA.MAXLINES, MASTERDATA.PAGENUMB, MASTERDATA.LAYERNUMB FROM MASTERDATA LEFT JOIN MASTERCATEGORY ON MASTERDATA.CATEGORYID=MASTERCATEGORY.CATEGORYID ";
	model->setQuery(Str+ sSel + sOrder);
	model->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("NAME"));
	model->setHeaderData(2, Qt::Horizontal, tr("MACID"));
	model->setHeaderData(3, Qt::Horizontal, tr("REGTIME"));
	model->setHeaderData(4, Qt::Horizontal, tr("REMARK"));
	model->setHeaderData(5, Qt::Horizontal, tr("LASTEDITTIME"));
	model->setHeaderData(6, Qt::Horizontal, tr("WORKERID"));
	model->setHeaderData(7, Qt::Horizontal, tr("VERSION"));
	model->setHeaderData(8, Qt::Horizontal, tr("CATEGORYID"));
	model->setHeaderData(9, Qt::Horizontal, tr("DOTPERLINE"));
	model->setHeaderData(10, Qt::Horizontal, tr("MAXLINES"));
	model->setHeaderData(11, Qt::Horizontal, tr("PAGENUMB"));
	model->setHeaderData(12, Qt::Horizontal, tr("LAYERNUMB"));
	model->setHeaderData(13, Qt::Horizontal, tr("MASTERTYPE"));
}
void MasterPage::Save(QIODevice &Device, const QString &MASTERCODE)
{
	QString Buffer;
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);

	QSqlQuery Query(/**/"SELECT * FROM MASTERPAGE WHERE MASTERCODE=" + MASTERCODE);
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
	}else{
		Cnt = Query.numRowsAffected();//DataSelect数
		::Save(&Device, Cnt);
		for (int iX=0; Cnt>iX ; iX++){
			for (int iY=0; iField>iY; iY++){
				save(Device,Query.value(iY));
			}
			Query.next();
		}
	}
}
void MasterPage::ALLDelete()
{
	QSqlQuery DeleteQuery(/**/"DELETE FROM MASTERPAGE");
	DeleteQuery.exec();
}
void MasterPage::Delete(const QString &MasterCode)
{
	QSqlQuery DeleteQuery(/**/"DELETE FROM MASTERPAGE WHERE MASTERCODE=" + MasterCode );
	DeleteQuery.exec();
}
void MasterPage::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData, QString &MASTERCODE)
{
	QSqlQuery InsertQuery;
	QByteArray Type;
	if(::Load(&Device, Type)==false) // {"class MasterPage * __ptr64" size=26}
		return ;
	int iField;
	if(::Load(&Device, iField)==false) // 26	(dist 24)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false) // 2
		return ;
	for (int iX=0;iX<Cnt; iX++){
		InsertQuery.prepare(InsertData);
		for (int iY=0; iY<iField; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"MASTERCODE"){
				int i;
				if(::Load(&Device,i)==false)
					return;
				if(::Load(&Device,i)==false)
					return;
				InsertQuery.addBindValue(MASTERCODE.toInt());
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}
MasterCategory::MasterCategory(QObject *parent)
	: BackupBase(parent)
{
}
void MasterCategory::ALLDlete()
{
	QSqlQuery deleteQuery(/**/"DELETE FROM MASTERCATEGORY");
	deleteQuery.exec();
}
void MasterCategory::Delete(const QString &CategoryID)
{
	QSqlQuery deleteQuery(/**/"DELETE FROM MASTERCATEGORY WHERE CATEGORYID=" + CategoryID );
	deleteQuery.exec();
}
void MasterCategory::Select(QByteArray FolderID, QSqlQueryModel *model)
{
	QString sSel;
	if(FolderID==/**/"-1"){
		sSel=/**/"WHERE MASTERDATA.CATEGORYID<=0";
	}else{
		sSel=/**/"WHERE MASTERDATA.CATEGORYID="+ QString(FolderID);
	}
	QString sOrder=/**/"ORDER BY MASTERDATA.MASTERCODE";

	QString Str=/**/"SELECT MASTERDATA.MASTERCODE, MASTERDATA.MASTERNAME, MASTERDATA.MACHINEID, MASTERDATA.REGTIME, MASTERDATA.REMARK, MASTERDATA.LASTEDITTIME, "
							/**/"MASTERDATA.WORKERID, MASTERDATA.VERSION,  MASTERCATEGORY.FOLDERNAME, MASTERDATA.DOTPERLINE, "
							/**/"MASTERDATA.MAXLINES, MASTERDATA.PAGENUMB, MASTERDATA.LAYERNUMB, MASTERDATA.PHASENUMB,MASTERDATA.MASTERTYPE FROM MASTERDATA LEFT JOIN MASTERCATEGORY ON MASTERDATA.CATEGORYID=MASTERCATEGORY.CATEGORYID ";
	model->setQuery(Str+ sSel + sOrder);
	model->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("NAME"));
	model->setHeaderData(2, Qt::Horizontal, tr("MACID"));
	model->setHeaderData(3, Qt::Horizontal, tr("REGTIME"));
	model->setHeaderData(4, Qt::Horizontal, tr("REMARK"));
	model->setHeaderData(5, Qt::Horizontal, tr("LASTEDITTIME"));
	model->setHeaderData(6, Qt::Horizontal, tr("WORKERID"));
	model->setHeaderData(7, Qt::Horizontal, tr("VERSION"));
	model->setHeaderData(8, Qt::Horizontal, tr("CATEGORYID"));
	model->setHeaderData(9, Qt::Horizontal, tr("DOTPERLINE"));
	model->setHeaderData(10, Qt::Horizontal, tr("MAXLINES"));
	model->setHeaderData(11, Qt::Horizontal, tr("PAGENUMB"));
	model->setHeaderData(12, Qt::Horizontal, tr("LAYERNUMB"));
	model->setHeaderData(13, Qt::Horizontal, tr("PHASENUMB"));
	model->setHeaderData(14, Qt::Horizontal, tr("MASTERTYPE"));
}
void MasterCategory::ParentSave(QIODevice &Device, const QString &CATEGORYID)
{
//親階層の保存
	int Cnt=0;
	QSqlQuery Query(/**/"SELECT PARENTID FROM MASTERCATEGORY WHERE CATEGORYID=" + CATEGORYID );
	if(Query.next()==false){
		::Save(&Device, Cnt);
	}else{
		Cnt = Query.numRowsAffected();//検索結果の数
		::Save(&Device, Cnt);
		for (int i=0; Cnt>i; i++){
			QString ParentID=Query.value(0).toString();
			Save(Device, ParentID);
			ParentSave(Device, ParentID);
			Query.next();
		}
	}
}
void  MasterCategory::Save(QIODevice &Device, const QString &CATEGORYID)
{
	QString Buffer;
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);

	QSqlQuery Query(/**/"SELECT * FROM MASTERCATEGORY WHERE CATEGORYID=" + CATEGORYID );
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
	}else{
		Cnt = Query.numRowsAffected();//CategorySelect数
		::Save(&Device, Cnt);
		for (int iX=0; iX<Cnt ; iX++){
			for (int iY=0; iY<iField; iY++){
				save(Device,Query.value(iY));
			}
			Query.next();
		}
	}
}
void MasterCategory::ParentLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int i=0; Cnt>i; i++){
		Load(Device, Backup, Now, InsertData);
		ParentLoad(Device, Backup, Now, InsertData);
	}
}
void MasterCategory::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QString Buffer;
	QSqlQuery InsertQuery;
	QString CATEGORYID;

	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField ;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;

	for (int iX=0; iX<Cnt ; iX++){
		InsertQuery.prepare(InsertData);
 		for (int iY=0; iY<iField; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			/*if (Backup.at(iY) == "CATEGORYID"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				CATEGORYID = QString::number(iData);
				QSqlQuery Query("SELECT CATEGORYID FROM MASTERCATEGORY WHERE CATEGORYID="+ CATEGORYID );
			/////
				if(Query.next())
					Delete(CATEGORYID);
			//////
				InsertQuery.addBindValue(iData);
				continue;
			}*/
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}
MasterImage::MasterImage(QObject *parent)
	: BackupBase(parent)
{
}
void MasterImage::UpdateMachineID(const QString &MasterCode,const QString &MachineID,const QString &OldMacID){
	QDir Dir;
	for(int iX=0;iX<MPathList.size();iX++){
		QString Path(MPathList.at(iX));
		if(Dir.cd(Path)==false)
			continue;
		QStringList List=Dir.entryList( QStringList(/**/"*"), QDir::Files, QDir::NoSort);
		for(int i=0;i<List.size();i++){
			QString FileName=List.at(i);
			if(FileName.contains(MasterCode+/**/"-") == false || FileName.contains(/**/"-Mac") ==false)
				continue;
			int index = FileName.indexOf(MasterCode);
			if(MasterCode == FileName.mid(index,MasterCode.size())==false)
				continue;
			FileName.prepend(Path + QDir::separator());
			QString NewName=FileName;
			NewName.replace(/**/"Mac"+OldMacID,/**/"Mac"+MachineID);
			Dir.rename(FileName,NewName);
		}
	}
}
void MasterImage::Save(QIODevice &Device, const QString &Mastercode)
{
//BlobFieldの取得
	QStringList BOLBFIELD;
	BlobField(BOLBFIELD);

	QStringList MACHINEID;
	QSqlQuery MacQuery(/**/"SELECT  MACHINEID FROM MASTERDATA WHERE MASTERCODE=" + Mastercode);
	while (MacQuery.next())
		MACHINEID.append(MacQuery.value(0).toString());
	 QSqlQuery PhaseQuery(/**/"SELECT PHASENUMB FROM MASTERDATA WHERE MASTERCODE=" + Mastercode);
	 QString sPhaseNumber;
	 if(PhaseQuery.next())
		sPhaseNumber = PhaseQuery.value(0).toString();
	QStringList PAGECODE;
	QSqlQuery PageQuery(/**/"SELECT  PAGECODE FROM MASTERPAGE WHERE MASTERCODE=" + Mastercode);
	 while (PageQuery.next())
		 PAGECODE.append(PageQuery.value(0).toString());

//Save処理
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);
	::Save(&Device, MACHINEID.size());
	int MaxPhase = 0;
	if(sPhaseNumber.isEmpty()==false)
		MaxPhase = sPhaseNumber.toInt();
	::Save(&Device,MaxPhase);
	::Save(&Device, PAGECODE.size());
//Master画像とBLOBファイルのSave
	QDir Dir;
	ImageFile imgFile(&Device);
	for(int iX=0;iX<MPathList.size();iX++){
		Path=MPathList.at(iX);
		if(Dir.cd(Path)==false)
			continue;
		for(int iMac=0; iMac<MACHINEID.size(); iMac++){
			QString MacID=MACHINEID.at(iMac);
			for(int iPhase=0;iPhase <= MaxPhase;iPhase++){
				for(int iP=0; iP<PAGECODE.size(); iP++){
					QString PageID=PAGECODE.at(iP);
					::Save(&Device, Mastercode);
					::Save(&Device, PageID);
					::Save(&Device, MacID);
					imgFile.SetFilePath(Path,/**/"Image"		,Mastercode,iPhase,PageID,MacID);
					imgFile.Save();
					imgFile.SetFilePath(Path,/**/"LearningImage",Mastercode,iPhase,PageID,MacID);
					imgFile.Save();
					::Save(&Device, BOLBFIELD.size());
					for(int iB=0; iB<BOLBFIELD.size(); iB++){
						QString blb=BOLBFIELD.at(iB);
						imgFile.SetFilePath(Path,blb,Mastercode,iPhase,PageID,MacID);
						imgFile.Save(blb);
						imgFile.SetFilePath(Path,/**/"Learning-"+blb,Mastercode,iPhase,PageID,MacID);
						imgFile.Save(blb);
					}
				}
			 }
			imgFile.SetFilePath(Path,DefGUIPath,Mastercode,0,QString(/**/""),MacID);
			imgFile.Save();
		}
	}
}
void MasterImage::Delete(const QString &Mastercode)
{
	QStringList MACHINEID;
	QStringList PAGECODE;
	QStringList BOLBFIELD;

//Blobのフィールド名を取得
	QSqlQuery FieldQuery(/**/"SELECT * FROM MASTERPAGE");
	for(int i=0; i<FieldQuery.record().count(); i++){
		if(FieldQuery.record().field(i).type()==12)//Bolb
			BOLBFIELD.append(FieldQuery.record().fieldName(i));
	}
	QSqlQuery MacQuery(/**/"SELECT  MACHINEID FROM MASTERDATA WHERE MASTERCODE=" + Mastercode);
	while (MacQuery.next())
		MACHINEID.append(MacQuery.value(0).toString());
	QSqlQuery PhaseQuery(/**/"SELECT PHASENUMB FROM MASTERDATA WHERE MASTERCODE=" + Mastercode);
	QString sPhase;
	if(PhaseQuery.next())
		sPhase = PhaseQuery.value(0).toString();
	int MaxPhase = 0;
	if(sPhase.isEmpty()==false)
		MaxPhase = sPhase.toInt();
	QSqlQuery PageQuery(/**/"SELECT  PAGECODE FROM MASTERPAGE WHERE MASTERCODE=" + Mastercode);
	while (PageQuery.next())
		PAGECODE.append(PageQuery.value(0).toString());
	QDir Dir;
	ImageFile imgFile;
	for(int iX=0;iX<MPathList.size();iX++){
		Path=MPathList.at(iX);
		if(Dir.cd(Path)==false)
			 continue;
		for(int iMac=0; iMac<MACHINEID.size(); iMac++){
			QString MacID=MACHINEID.at(iMac);
			for(int iPhase=0;iPhase <= MaxPhase;iPhase++){
				for(int iP=0; iP<PAGECODE.size(); iP++){
					QString PageID=PAGECODE.at(iP);
					imgFile.SetFilePath(Path,/**/"Image",Mastercode,iPhase,PageID,MacID);
					imgFile.Delete();
					imgFile.SetFilePath(Path,/**/"LearningImage",Mastercode,iPhase,PageID,MacID);
					imgFile.Delete();
					imgFile.DeleteTry(/**/"Image",Path,Mastercode,PageID);
					for(int iB=0; iB<BOLBFIELD.size(); iB++){
						QString blb=BOLBFIELD.at(iB);
						imgFile.SetFilePath(Path,blb,Mastercode,iPhase,PageID,MacID);
						imgFile.Delete();
						imgFile.SetFilePath(Path,/**/"Learning-"+blb,Mastercode,iPhase,PageID,MacID);
						imgFile.Delete();
						imgFile.DeleteTry(blb,Path,Mastercode,PageID);
					}
				}
			}
			imgFile.SetFilePath(Path,DefGUIPath,Mastercode,0,QString(/**/""),MacID);
			imgFile.Delete();
			imgFile.DeleteTry(DefGUIPath,Path,Mastercode);
		}
	}
}
void MasterImage::Load(QIODevice &Device, QString &MASTERID)
{
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int Mac;
	if(::Load(&Device, Mac)==false)	
		return ;
	int MaxPhase;
	if(::Load(&Device,MaxPhase)==false)
		return;
	int MaxPage;
	if(::Load(&Device, MaxPage)==false)
		return ;
	QDir Dir;
	if(Dir.cd(Path)==false)
		return;
	QString Master;
	QString MacID;
	ImageFile imgFile(&Device);
	for(int iMac=0; iMac<Mac; iMac++){
		for(int iPhase = 0;iPhase <= MaxPhase;iPhase++){
			for(int iPage=0; iPage<MaxPage; iPage++){
				if(::Load(&Device, Master)==false)
					return ;
				QString PageID;
				if(::Load(&Device, PageID)==false)
					return ;
				if(::Load(&Device, MacID)==false)
					return ;
				if(MASTERID.isEmpty()==false)
					Master=MASTERID;
				imgFile.SetFilePath (Path,/**/"Image"		 ,Master,iPhase,PageID,MacID);
				if(imgFile.Load()==false)
					return;
				imgFile.SetFilePath (Path,/**/"LearningImage",Master,iPhase,PageID,MacID);
				if(imgFile.Load()==false)
					return;

				int Kind;
				if(::Load(&Device, Kind)==false)
					return ;
				for(int iZ=0; iZ<Kind; iZ++){
					imgFile.SetFilePath(Path,/**/"XXX"		   ,Master,iPhase,PageID,MacID);
					if(imgFile.Load(true)==false)
						return;
					imgFile.SetFilePath(Path,/**/"Learning-XXX",Master,iPhase,PageID,MacID);
					if(imgFile.Load(true)==false)
						return;
				}
			}
		}
		imgFile.SetFilePath(Path,DefGUIPath,Master,0,QString(/**/""),MacID);
		imgFile.Load();
	}
}
void MasterImage::BlobField(QStringList &BOLBFIELD)
{//Blobのフィールド名を取得
	QSqlQuery Query(/**/"SELECT * FROM MASTERPAGE");
	for(int i=0; i<Query.record().count(); i++){
		if(Query.record().field(i).type()==12){//Bolb
			QString Up=Query.record().fieldName(i).mid(0,1).toUpper();
			QString Low=Query.record().fieldName(i).mid(1).toLower();
			QString FieldName=Up+Low;
			BOLBFIELD.append(FieldName);
		}
	}
}
ImageFile::ImageFile(QIODevice *Device){
	this->Device = Device;
}
void ImageFile::Save(QString blb){
	QFile file(FilePath);
	if(file.open(QIODevice::ReadOnly)==false){
		::Save(Device,false);
		return;
	}
	::Save(Device,true);
	if(blb.isEmpty()==false)
		::Save(Device,blb);
	QByteArray Buffer=file.readAll();
	::Save(Device, Buffer);
	file.close();
}
bool ImageFile::Load(bool isBLB){
	bool flag;
	if(::Load(Device,flag)==false)
		return false;
	if(flag==false)
		return true;
	if(isBLB==true){
		QString FileType;
		if(::Load(Device,FileType)==false)
			return false;
		SetFileType(FileType);
	}
	QByteArray Buffer;
	if(::Load(Device, Buffer)==false)
		return false;
	QFile file(FilePath);
	if (file.open(QIODevice::WriteOnly)==false)
		return false;
	char* cd = Buffer.data();
	qint64 qicount = (qint64)(Buffer.size());
	qint64 qioffset = (1024 * 1024 * 32) - (1024 * 512);
	qint64 qisum = 0;
	while (0 < (qicount - qisum)){
		if (qioffset > (qicount - qisum))
			qioffset = qicount - qisum;

		qisum += file.write(cd + qisum, qioffset);
	}
	file.close();
	return true;
}
void ImageFile::DeleteTry(QString Type,const QString &Path,const QString &Mastercode,QString PageID){
	try{
		QDir dir(Path);
		if(!(Type == /**/"Image" || Type == DefGUIPath))
			Type.append('-');
		if(PageID.isEmpty()==false)
			PageID.prepend(/**/"-Page");
		QString exetension(/**/".blb");
		if(Type == /**/"Image")
			exetension = /**/".img";
		QStringList filters;
		filters << Type + Mastercode + PageID + QString(/**/"-Mac*") + exetension;
		dir.setNameFilters(filters);
		QFileInfoList Files = dir.entryInfoList();
		for(int i=0;i<Files.size();i++){
			QFileInfo fInfo = Files[i];
			QFile file(fInfo.absoluteFilePath());
			file.remove();
		}
	}
	catch(...){}
}
void ImageFile::SetFilePath(const QString &Path,QString FileType,const QString &Mastercode,int Phase,const QString &PageID,const QString &MacID){
	FilePath.clear();
	if(FileType.isEmpty())
		FileType = /**/"XXX";
	QString Extension(/**/".blb");
	if(FileType == /**/"Image")
		Extension = /**/".img";
	QString stPhase;
	if(Phase!=0)
		stPhase = /**/"-Phase"+stPhase.setNum(Phase);
	QString Page = /**/"-Page";
	if(FileType == DefGUIPath)
		Page.clear();
	QString Mac = /**/"-Mac";
	if(FileType.left(8) == /**/"Learning")
		Mac = /**/"-MAC";
	if(!(FileType == /**/"Image" || FileType == DefGUIPath || FileType.left(8) == /**/"Learning"))
		FileType.append('-');
	FilePath =  Path + QString(QDir::separator()) + FileType + Mastercode + stPhase + Page + PageID + Mac + MacID + Extension;
}
void ImageFile::SetFileType(QString FileType){
	FilePath.replace(/**/"XXX",FileType);
}

Machine::Machine(QObject *parent)
	: BackupBase(parent)
{
	model = new QSqlQueryModel(this);
}
Machine::~Machine(){
	delete model;
}
void Machine::Select(QSqlQueryModel *model)
{
	model->setQuery(/**/"SELECT MACHINEID,NETID,NAME,VERSION,REMARK FROM MACHINE ORDER BY MACHINEID ");
		//" " + sOrder + " DESC"  'w_'はwで始まる2文字になる VERSION LIKE '%w%'
	model->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("IP"));
	model->setHeaderData(2, Qt::Horizontal, tr("NAME"));
	model->setHeaderData(3, Qt::Horizontal, tr("VERSION"));
	model->setHeaderData(4, Qt::Horizontal, tr("REMARK"));
}
bool Machine::Insert(QStringList &DataList){
	QSqlQuery selectQuery(/**/"SELECT MACHINEID FROM MACHINE WHERE MACHINEID=" + DataList[0]);
	selectQuery.exec();
	if(selectQuery.next()==true)
		return false;
	QSqlQuery insertQuery;
	insertQuery.prepare(/**/"INSERT INTO MACHINE (MACHINEID,NETID,NAME,VERSION,REMARK) "
						/**/"VALUES (?, ?, ?, ?, ?)");
	for(int i=0;i<5;i++){
		insertQuery.addBindValue(DataList[i]);
	}
	insertQuery.exec();
	return true;
}
bool Machine::Update(QStringList &DataList,QString &OldMachineID){
	QSqlQuery updateQuery;
	if(OldMachineID == DataList[0]){
		updateQuery.prepare(/**/"UPDATE MACHINE SET REMARK=?,VERSION=?,NAME=?,NETID=? WHERE MACHINEID=?");
		for(int i=4;i>=0;i--){
			updateQuery.addBindValue(DataList[i]);
		}
		updateQuery.exec();
		return true;
	}
	updateQuery.prepare(/**/"UPDATE MACHINE SET MACHINEID=?,NETID=?,NAME=?,VERSION=?,REMARK=?  WHERE MACHINEID=?");
	if(OldMachineID.isEmpty())
		OldMachineID = DataList[0];
	else{
		QSqlQuery selectQuery(/**/"SELECT MACHINEID FROM MACHINE WHERE MACHINEID=" + DataList[0]);
		selectQuery.exec();
		if(selectQuery.next()==true)
			return false;
	}
	DataList.append(OldMachineID);
	for(int i=0;i<6;i++){
		updateQuery.addBindValue(DataList[i]);
	}
	updateQuery.exec();
	return true;
}
bool Machine::Delete(QString &MachineID)
{
	QSqlQuery selectQuery(/**/"SELECT MACHINEID FROM MACHINE WHERE MACHINEID=" + MachineID);
	selectQuery.exec();
	if(selectQuery.next()==false)
		return false;
	QSqlQuery DeleteQuery(/**/"DELETE FROM MACHINE WHERE MACHINEID=" + MachineID );
	DeleteQuery.exec();
	return true;
}
void Machine::Save(QIODevice &Device)
{
	QString Buffer;
	QByteArray Type = QByteArray(typeid(this).name());
	::Save(&Device, Type);

	QSqlQuery Query(/**/"SELECT * FROM MACHINE");
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);

	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//DataSelect数
	::Save(&Device, Cnt);
	for (int iX=0; Cnt>iX ; iX++){
		for (int iY=0; iField>iY; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}
void Machine::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QSqlQuery InsertQuery;
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"MACHINEID"){
				int type;
				if(::Load(&Device,type)==false)
					return;
				int MacID;
				if(::Load(&Device,MacID)==false)
					return;
				QString MACHINEID = QString::number(MacID);
				QSqlQuery Query(/**/"SELECT MACHINEID FROM MACHINE WHERE MACHINEID=" + MACHINEID);
				if (Query.next() == true)
					Delete(MACHINEID); // 既に存在している場合 //上書きの場合
				InsertQuery.addBindValue(MacID);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}
Worker::Worker(QObject *parent)
	: BackupBase(parent)
{
	model = new QSqlQueryModel(this);
}
Worker::~Worker(){
	delete model;
}
void Worker::Select(QSqlQueryModel *model)
{
	model->setQuery(/**/"SELECT WORKERID,SECTION,NAME,REMARK,UPDATETIME FROM WORKER WHERE ALIVE=1 ORDER BY WORKERID");
	model->setHeaderData(0, Qt::Horizontal, tr("ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("SECTION"));
	model->setHeaderData(2, Qt::Horizontal, tr("NAME"));
	model->setHeaderData(3, Qt::Horizontal, tr("REMARK"));
	model->setHeaderData(4, Qt::Horizontal, tr("UPDATETIME"));
}
bool Worker::Insert(QStringList &DataList,QDateTime &UpdateTime){
	QSqlQuery selectQuery(/**/"SELECT WORKERID,SECTION,NAME,REMARK,UPDATETIME FROM WORKER WHERE WORKERID=" + DataList[0]);
	selectQuery.exec();
	if(selectQuery.next()==true)
		return false;
	QSqlQuery insertQuery;
	insertQuery.prepare(/**/"INSERT INTO WORKER (ALIVE,WORKERID,SECTION,NAME,REMARK,UPDATETIME) "
						/**/"VALUES (?, ?, ?, ?, ?, ?)");
	insertQuery.addBindValue(1);
	for(int i=0;i<4;i++){
		insertQuery.addBindValue(DataList[i]);
	}
	insertQuery.addBindValue(UpdateTime);
	insertQuery.exec();
	return true;
}
bool Worker::Update(QStringList &DataList,QDateTime &UpdateTime,QString &OldWorkerID){
	QSqlQuery updateQuery;
	if(OldWorkerID==DataList[0]){
		updateQuery.prepare(/**/"UPDATE WORKER SET ALIVE=?, UPDATETIME=?, REMARK=?,NAME=?, SECTION=? WHERE WORKERID=?");
		updateQuery.addBindValue(1);
		updateQuery.addBindValue(UpdateTime);
		for(int i=3;i>=0;i--){
			updateQuery.addBindValue(DataList[i]);
		}
		updateQuery.exec();
		return true;
	}
	if(OldWorkerID.isEmpty())
		OldWorkerID = DataList[0];
	else{
		QSqlQuery selectQuery(/**/"SELECT WORKERID FROM WORKER WHERE WORKERID=" + DataList[0]);
		selectQuery.exec();
		if(selectQuery.next()==true)
			return false;
	}
	updateQuery.prepare(/**/"UPDATE WORKER SET ALIVE=?, WORKERID=?, SECTION=?, NAME=?, REMARK=?, UPDATETIME=? WHERE WORKERID=?");
	updateQuery.addBindValue(1);
	for(int i=0;i<4;i++){
		updateQuery.addBindValue(DataList[i]);
	}
	updateQuery.addBindValue(UpdateTime);
	updateQuery.addBindValue(OldWorkerID);
	updateQuery.exec();
	return true;
}
bool Worker::Delete(QString &WorkerID)
{
	QSqlQuery selectQuery(/**/"SELECT WORKERID FROM WORKER WHERE WORKERID=" + WorkerID);
	selectQuery.exec();
	if(selectQuery.next()==false)
		return false;
	QSqlQuery DeleteQuery(/**/"DELETE FROM WORKER WHERE WORKERID=" + WorkerID );
	DeleteQuery.exec();
	return true;
}
void Worker::Save(QIODevice &Device)
{
	QString Buffer;
	QByteArray Type = QByteArray(typeid(this).name());
	::Save(&Device, Type);

	QSqlQuery Query(/**/"SELECT * FROM WORKER");
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);

	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//DataSelect数
	::Save(&Device, Cnt);
	for (int iX=0; Cnt>iX ; iX++){
		for (int iY=0; iField>iY; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}
void Worker::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QSqlQuery InsertQuery;
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"WORKERID"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				InsertQuery.addBindValue(iData);
				QString WORKERID = QString::number(iData);
				QSqlQuery Query(/**/"SELECT MACHINEID FROM MACHINE WHERE MACHINEID=" + WORKERID);
				if (Query.next() == true)
					Delete(WORKERID); // 既に存在している場合 //上書きの場合
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}


LibFolder::LibFolder(QObject *parent)
	: BackupBase(parent)
{
}
void LibFolder::RetFolderID(QString Mid, QStringList &idList)
{
	idList.clear();
	//RELATEDMASTERCODEをLIBFOLDERIDを探す
	QString Select=/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE RELATEDMASTERCODE="+ Mid +/**/" ORDER BY LIBFOLDERID";
	QSqlQuery q(Select);

	for (int i = 0; i < q.record().count(); ++i)
		idList.append(q.record().value(0).toString());

}
void LibFolder::SubSave(QString &Target, QIODevice &Device, QString &FolderID)
{
//親階層の保存
//子供の保存
	QString Select;
	int Cnt=0;
	::Save(&Device, Target);
	if(Target==/**/"Parent"){//自分が持つParentIDを返す
		Select=/**/"SELECT LIBPARENTID FROM LIBFOLDER WHERE LIBFOLDERID=" + FolderID + /**/" ORDER BY LIBFOLDERID";
	}else if(Target==/**/"Child"){	//FolderIDを親に持つ子供の検索
		Select=/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBPARENTID="+ FolderID +/**/" ORDER BY LIBFOLDERID";
	}
	QSqlQuery Query(Select);
	if(Query.next()==false){
		::Save(&Device, Cnt);
	}else{
		Cnt = Query.numRowsAffected();//検索結果の数
		::Save(&Device, Cnt);
		for (int i=0; i<Cnt; i++){
			QString LIBFOLDERID=Query.value(0).toString();
			Save(Device, LIBFOLDERID);//自分自身の保存
			SubSave(Target, Device, LIBFOLDERID);
			if(Target==/**/"Child")
				Lib->Save(Device, LIBFOLDERID);
			Query.next();
		}
	}
}
void LibFolder::Save(QIODevice &Device, QString &FolderID)
{//自分自身の保存
	QString Select;
	QByteArray Buffer;
	QByteArray Type = QByteArray(typeid(this).name());
	::Save(&Device, Type);

	if(FolderID==/**/"-1"){//Rootの場合全保存
		Select=/**/"SELECT * FROM LIBFOLDER ORDER BY LIBFOLDERID";
	}else{
		Select=/**/"SELECT * FROM LIBFOLDER WHERE LIBFOLDERID=" + FolderID;//自分自身の保存
	}
	QSqlQuery Query(Select);
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//検索結果の数
	::Save(&Device, Cnt);
	for (int iX=0; Cnt>iX ; iX++){
		for (int iY=0; iField>iY; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}

void LibFolder::SubLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
//親階層の読込み
//子供の読込み
	QString Target;
	if(::Load(&Device, Target)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int i=0; i<Cnt; i++){
		Load(Target, Device, Backup, Now, InsertData);
		SubLoad(Device, Backup, Now, InsertData);
		if(Target==/**/"Child")
			Lib->Load(Device, Backup, Now, InsertData);
	}
}
void LibFolder::Load(QString &Target, QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QByteArray Buffer;
	QSqlQuery InsertQuery;

	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		QString FOLDERID;
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"LIBFOLDERID"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				InsertQuery.addBindValue(iData);
				QString FOLDERID = QString::number(iData);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		QSqlQuery SelQuery(/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBFOLDERID="+ FOLDERID);
		if(SelQuery.next()==true)//既に存在している場合
			Delete(FOLDERID);//上書きの場合
		if(Target!=/**/"Parent")
			InsertQuery.exec();
		//InsertQuery.clear();
	}
}

void LibFolder::RootSubLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
//親階層の読込み
//子供の読込み
	QString Target;
	if(::Load(&Device, Target)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int i=0;i<Cnt; i++){
		RootLoad(Device, Backup, Now, InsertData);
		RootSubLoad(Device, Backup, Now, InsertData);
		if(Target==/**/"Child")
			Lib->Load(Device, Backup, Now, InsertData);
	}
}
void LibFolder::RootLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QByteArray Buffer;
	QSqlQuery InsertQuery;

	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		QString FOLDERID, ParentID;
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"LIBPARENTID" || Backup.at(iY) == /**/"LIBFOLDERID"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				InsertQuery.addBindValue(iData);
				if  (Backup.at(iY) == /**/"LIBPARENTID")
					ParentID = QString::number(iData);
				else
					FOLDERID = QString::number(iData);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		QSqlQuery SelQuery(/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBFOLDERID="+ FOLDERID);
		if(SelQuery.next()==true)//既に存在している場合
			Delete(FOLDERID);//上書きの場合
		InsertQuery.exec();
		InsertQuery.clear();
		QSqlQuery PQuery(/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBFOLDERID="+ ParentID);
		if(PQuery.next()==false){//存在していない場合
			QSqlQuery upQuery(/**/"UPDATE LIBFOLDER SET LIBPARENTID=0 WHERE LIBFOLDERID="+ FOLDERID);
			upQuery.exec();
		}
	}
}
void LibFolder::RootLoad2(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QByteArray Buffer;
	QSqlQuery InsertQuery;

	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
			QString FOLDERID;
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if(Backup.at(iY) == /**/"LIBPARENTID" || Backup.at(iY) == /**/"LIBFOLDERID"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				if (Backup.at(iY) == /**/"LIBPARENTID"){
					QSqlQuery PQuery(/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBFOLDERID=" + QString::number(iData));
					if (PQuery.next() == false) // 存在していない場合
						iData=0;
				}else
					FOLDERID = QString::number(iData);
				InsertQuery.addBindValue(iData);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		QSqlQuery SelQuery(/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBFOLDERID="+ FOLDERID);
		if(SelQuery.next()==true){//既に存在している場合
			Delete(FOLDERID);//上書きの場合
		}
		InsertQuery.exec();
	}
}
void LibFolder::ALLDelete()
{
	QSqlQuery DelFolderQuery(/**/"DELETE FROM LIBFOLDER");
	DelFolderQuery.exec();
}
void LibFolder::Delete(QString &FolderID)
{
	QSqlQuery DeleteQuery(/**/"DELETE FROM LIBFOLDER WHERE LIBFOLDERID=" + FolderID );
	DeleteQuery.exec();
}
void LibFolder::ChildDelete(QString &FolderID)
{
	//LibParentIDを親に持つ子供を探す
	QString Select=/**/"SELECT LIBFOLDERID FROM LIBFOLDER WHERE LIBPARENTID="+ FolderID +/**/" ORDER BY LIBPARENTID";
	QSqlQuery FolderQuery(Select);
	while(FolderQuery.next()){
		QString LibFolderID=FolderQuery.value(0).toString();
		Lib->FolderDelete(LibFolderID);//InspeclLibを削除
		Delete(LibFolderID);//リブフォルダー削除
		ChildDelete(LibFolderID);
	}
}


InspectLib::InspectLib(QObject *parent)
	: BackupBase(parent)
{
	model = new QSqlQueryModel(this);
}
void InspectLib::Select(QSqlQueryModel *model, QString &sSelect, QString &sOrder)
{
		model->setQuery(/**/"SELECT INSPECTLIB.LIBID, INSPECTLIB.LIBNAME, INSPECTLIBTYPE.TYPENAME ,INSPECTLIB.LASTWORKER, INSPECTLIB.DATAVERSION ,INSPECTLIB.LASTUPDATED, INSPECTLIB.LIBFOLDERID FROM INSPECTLIB LEFT JOIN INSPECTLIBTYPE ON INSPECTLIB.LIBTYPE=INSPECTLIBTYPE.LIBTYPE "
			 + sSelect + sOrder);
		model->setHeaderData(0, Qt::Horizontal, tr("ID"));
		model->setHeaderData(1, Qt::Horizontal, tr("LIBNAME"));
		model->setHeaderData(2, Qt::Horizontal, tr("LIBTYPE"));
		model->setHeaderData(3, Qt::Horizontal, tr("LASTWORKER"));
		model->setHeaderData(4, Qt::Horizontal, tr("DATAVERSION"));
		model->setHeaderData(5, Qt::Horizontal, tr("LASTUPDATED"));
		model->setHeaderData(6, Qt::Horizontal, tr("LIBFOLDERID"));
}
void InspectLib::FolderDelete(QString &FolderID)
{
	QSqlQuery DeleteQuery(/**/"DELETE FROM INSPECTLIB WHERE LIBFOLDERID=" + FolderID);
	DeleteQuery.exec();
}
void InspectLib::ALLDelete()
{
	QSqlQuery DeleteQuery(/**/"DELETE FROM INSPECTLIB");
	DeleteQuery.exec();
}
void InspectLib::Delete(QString &TypeName, QString &LibID)
{
	QString LibType;
	QSqlQuery Query(/**/"SELECT LIBTYPE FROM INSPECTLIBTYPE WHERE TYPENAME LIKE \'"+ TypeName +/**/"\'");
	if(Query.next()==true){//存在している場合
		LibType= Query.value(0).toString();
		QSqlQuery DeleteQuery(/**/"DELETE FROM INSPECTLIB WHERE LIBID=" + LibID + /**/"AND LIBTYPE=" + LibType);
		DeleteQuery.exec();
	}
}
void InspectLib::Save(QIODevice &Device, QString &FolderID)
{
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);
	QString Select;
	Select=/**/"SELECT * FROM INSPECTLIB WHERE LIBFOLDERID=" + FolderID;
	if(FolderID==/**/"-1")
		Select=/**/"SELECT * FROM INSPECTLIB ORDER BY LIBFOLDERID";
	QSqlQuery Query(Select);
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//DataSelect数
	::Save(&Device, Cnt);
	for (int iX=0; Cnt>iX ; iX++){
		for (int iY=0; iField>iY; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}
void InspectLib::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QString Buffer;
	QSqlQuery InsertQuery;
	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return;
	int iField;
	if(::Load(&Device, iField)==false)
		return;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return;
	for (int iX=0; iX<Cnt; iX++){
		QString LibID=/**/"";
		QString LibTYPE=/**/"";
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if(Backup.at(iY) == /**/"LIBID" || Backup.at(iY) == /**/"LIBTYPE"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				if (Backup.at(iY) == /**/"LIBID")
					LibID   = QString::number(iData);
				else
					LibTYPE = QString::number(iData);
				if(LibID.isEmpty()==false && LibTYPE.isEmpty()==false)
				{
					QSqlQuery Query(/**/"SELECT LIBTYPE,LIBID FROM INSPECTLIB WHERE LIBID=" + LibID + /**/"AND LIBTYPE=" + LibTYPE);
					if(Query.next()==true)	//既に存在している場合
						Delete(LibID, LibTYPE);
				}
				InsertQuery.addBindValue(iData);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}

InspectLibType::InspectLibType(QObject *parent)
	: BackupBase(parent)
{
}
void InspectLibType::Save(QIODevice &Device)
{
	QByteArray Type=QByteArray(typeid(this).name());
	::Save(&Device, Type);
	QSqlQuery Query(/**/"SELECT * FROM INSPECTLIBTYPE");
	int iField = Query.record().count();//フィールド数
	::Save(&Device, iField);
	int Cnt=0;
	if(Query.next()==false){
		::Save(&Device, Cnt);
		return;
	}
	Cnt = Query.numRowsAffected();//DataSelect数
	::Save(&Device, Cnt);
	for (int iX=0; Cnt>iX ; iX++){
		for (int iY=0; iField>iY; iY++){
			save(Device,Query.value(iY));
		}
		Query.next();
	}
}
void InspectLibType::Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData)
{
	QByteArray Buffer;
	QSqlQuery InsertQuery;

	QByteArray Type;
	if(::Load(&Device, Type)==false)
		return ;
	int iField;
	if(::Load(&Device, iField)==false)
		return ;
	int Cnt;
	if(::Load(&Device, Cnt)==false)
		return ;
	for (int iX=0; iX<Cnt; iX++){
		QString LIBTYPE;
		InsertQuery.prepare(InsertData);
		for (int iY=0; iField>iY; iY++){
			if(Now.indexOf(Backup.at(iY)) == -1)
				continue;
			if (Backup.at(iY) == /**/"LIBTYPE"){
				int iData;
				if(::Load(&Device,iData)==false)
					return;
				if(::Load(&Device,iData)==false)
					return;
				LIBTYPE = QString::number(iData);
				InsertQuery.addBindValue(iData);
				continue;
			}
			if(load(Device,InsertQuery)==false)
				return;
		}
		InsertQuery.exec();
	}
}