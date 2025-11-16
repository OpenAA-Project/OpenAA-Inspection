/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\BackupBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BACKUPBASE_H
#define BACKUPBASE_H

#include <QObject>
#include <QtSql>


class InspectLib;
class InspectLibType;
class MasterImage;
class MasterPage;
class MasterCategory;

class BackupBase : public QObject
{
    Q_OBJECT
public:
    explicit BackupBase(QObject *parent = 0);
	void FieldSave(QIODevice &Device,const QString &Table);
	void FieldLoad(QIODevice &Device,  QStringList &BField);
	void FieldGet(const QString &Table,QStringList &NowField);
	void RestoreField(QStringList &Backup, QStringList &Now, QString &Table, QString &Insert);
	void save(QIODevice &Device,const QVariant &value);
	bool load(QIODevice &Device,QSqlQuery &Query);
};
class MasterData : public BackupBase
{	
public:
		MasterData(QObject *parent);
		//~MasterData();
		MasterImage *Image;
		MasterPage *Page;
		MasterCategory *Category;
		void Update(QStringList &DataList);
		QString getCurrentMachineID(QString &MasterCode);
		void Select(QSqlQueryModel *model, QString &Sel, QString &Order);
		void Save(QIODevice &Device, const QString &MASTERCODE);
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData, QString &MASTERCODE);
		void Delete(const QString &MASTERCODE);
		void ALLDelete(QString &CATEGORYID);
};
class MasterPage : public BackupBase
{	
public:
		MasterPage(QObject *parent);
		void Select(QString FolderID, QSqlQueryModel *model);
		void Save(QIODevice &Device, const QString &MasterCode);
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData, QString &MASTERCODE);
		void Delete(const QString &MASTERCODE);
		void ALLDelete();
};
class MasterCategory : public BackupBase
{	
public:
		MasterCategory(QObject *parent);
		void Select(QByteArray FolderID, QSqlQueryModel *model);
		void ParentSave(QIODevice &Device, const QString &CATEGORYID);
		void Save(QIODevice &Device, const QString &CATEGORYID);
		void ParentLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
		void Delete(const QString &CategoryID);
		void ALLDlete();
};
class ImageFile{
public:
	ImageFile(void){Device = NULL;}
	ImageFile(QIODevice *Device);
	void SetFilePath(const QString &Path,QString FileType,const QString &Mastercode,int Phase,const QString &PageID,const QString &MacID);
	void SetFileType(QString FileType);
	QString GetFilePath(){return FilePath;}
	void Save(QString blb = "");
	bool Load(bool isBLB = false);
	void Delete(){QFile::remove(FilePath);}
	void DeleteTry(QString Type,const QString &Path,const QString &MasterCode,QString PageID="");
private:
	QString FilePath;
	QIODevice *Device;
};
class MasterImage : public BackupBase
{	
public:
	MasterImage(QObject *parent);
	void Save(QIODevice &Device, const QString &MasterCode);
	void Load(QIODevice &Device, QString &MasterCode);
	void Delete(const QString &MasterCode);
	void DeleteTry(QString Type,const QString &Path,const QString &MasterCode,QString PageID="");
	void BlobField(QStringList &BOLBFIELD);
	void UpdateMachineID(const QString &MasterCode,const QString &MachineID,const QString &OldMacID);
};
class Machine : public BackupBase
{	
public:
		Machine(QObject *parent);
		~Machine();
		QSqlQueryModel *model;
		void Select(QSqlQueryModel *model);
		bool Insert(QStringList &DataList);
		bool Update(QStringList &DataList,QString &OldMachineID);
		bool Delete(QString &MachineID);
		void Save(QIODevice &Device);		 
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);		
};
class Worker : public BackupBase
{	
public:
		Worker(QObject *parent);
		~Worker();
		QSqlQueryModel *model;
		void Select(QSqlQueryModel *model);
		bool Insert(QStringList &DataList,QDateTime &UpdateTime);
		bool Update(QStringList &DataList,QDateTime &UpdateTime,QString &OldWorkerID);
		bool Delete(QString &WorkerID);
		void Save(QIODevice &Device);		 
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);		
};
class LibFolder : public BackupBase
{	
public:
		LibFolder(QObject *parent);
		//~LibFolder();
		InspectLib *Lib;
		InspectLibType *Type;
		void SubSave(QString &Target, QIODevice &Device, QString &FolderID);
		void SubLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InspectData);
		void Save(QIODevice &Device, QString &ParentID);
		void Load(QString &Target, QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InspectData);
		//MasterDataの読み込み時使用(Rootに戻す)
		void RootLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
		void RootSubLoad(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
		void RootLoad2(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
		void ALLDelete();//LibFolderの全削除
		void Delete(QString &FolderID);//LibFolderの削除
		void ChildDelete(QString &FolderID);//子供階層の削除
		void RetFolderID(QString Mid, QStringList &idList);//RELATEDMASTERCODEの追加に伴い
};
class InspectLib : public BackupBase
{	
public:
		InspectLib(QObject *parent);
		QSqlQueryModel *model;
		void Select(QSqlQueryModel *model, QString &sSelect, QString &sOrder);
		void Save(QIODevice &Device, QString &FolderID);	
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);	
		void ALLDelete();//InspectLibの全削除
		void FolderDelete(QString &FolderID);//InspectLibのFolderID削除
		void Delete(QString &TypeName, QString &LibID);//InspectLibの1件削除
};
class InspectLibType : public BackupBase
{	
public:
		InspectLibType(QObject *parent);
		void FieldSave(QIODevice &Device);
		void Select(QSqlQueryModel *model, QString &sSelect, QString &sOrder);
		void Save(QIODevice &Device);		 
		void Load(QIODevice &Device, QStringList &Backup, QStringList &Now, QString &InsertData);
};

#endif // BACKUPBASE_H
