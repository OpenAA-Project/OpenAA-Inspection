/*
 * Copyright (C) 2025
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

#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QWidget>
#include "ui_datamanagement.h"
#include "BackupBase.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "progressbar.h"
#include <QModelIndex>

class UIBase;

class Datamanagement : public QWidget
{
	Q_OBJECT

	QList<QLabel *>	LabelDim;
public:
	Datamanagement(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Datamanagement();
	
	Progressbar *Pdialog;
	//Ui::Progressbar P;

	void saveRelatedMastercode(QIODevice &file,QString &MasterCode);
	void loadRelatedMastercode(QIODevice &file);
	Ui::Datamanagement *getUI(){return &ui;}
private slots:
        void on_pbInsert_clicked();
        void on_pbUpdate_clicked();
        void on_pbDelete_clicked();
        void on_pbBackup_clicked();
        void on_pbRestore_clicked();
        void on_pbSET_clicked();
        void on_pbEND_clicked();
        void on_tabWidget_currentChanged(int index);
        void on_tableView_clicked(const QModelIndex &index);

private:
		Ui::Datamanagement ui;
		QList<UIBase*> UIList;
		UIBase *Gui;
};
//====================================================
class UIBase : public QObject{
	Q_OBJECT
public:
	UIBase(){};
	UIBase(Datamanagement *parent);
	UIBase(Ui::Datamanagement *ui);
	UIBase(const UIBase &rhs);
	UIBase &operator=(UIBase &rhs);
	virtual ~UIBase(){};

	//virtual void setData(QStringList &DataList) = 0;
	virtual void view() = 0;
	virtual void changeUI() = 0;
	virtual void Insert(){;}
	virtual void Update(){;}
	virtual void Delete()  = 0;
	virtual void Backup()  = 0;
	virtual void Restore() = 0;
			bool message(const QString &type);
	virtual void saveRelatedMastercode(QIODevice &file,QString &MasterCode){;}
	virtual void loadRelatedMastercode(QIODevice &file){;}
protected:
	Ui::Datamanagement *ui;
	Datamanagement *parent;
};

class	RelationUI;

class	QSqlRelationModel : public QSqlTableModel
{
	friend	class RelationUI;

	RelationUI	*ParentWindow;
public:
	QSqlRelationModel(QObject * parent);
	QString selectStatement () const;
private slots:
 };

class RelationUI : public UIBase
{
	Q_OBJECT

friend	class	QSqlRelationModel;

public:
	RelationUI(Datamanagement *parent);
	RelationUI(Ui::Datamanagement *ui,QObject *parent);
	void view();
	void clear();
	void changeUI();
	void Update();
	void Delete();
	void Backup();
	void Restore();
private:
	bool	AcsendantOrder;
	int		OrderMode;		//0:RELATIONCODE,1:REGTIME,2:RELATIONNUMBER,3:RELATIONNAME,4:REMARK
	MasterData *Master;
	MasterPage	*Page;
	MasterImage *Image;
public:
	int	ResultRelationCode;
public slots:
	void	MListSectionClicked ( int logicalIndex );
};

class MasterUI : public UIBase{
	Q_OBJECT
public:
	MasterUI(Datamanagement *parent);
	MasterUI(Ui::Datamanagement *ui,QObject *parent);
	void view();
	void view(QString &SELECT,QString &ORDER);
	void clear();
	void changeUI();
	void resizeHeader();
	void setData(QStringList &DataList);
	QLineEdit *getLineEdit(int i);
	bool isEmpty(QStringList &DataList);

	void showTree();
	void addChildTree(QString &QueryData, QTreeWidgetItem *ParentItem);
	QTreeWidgetItem* CheckTrMasterList(QTreeWidgetItem *item, int col, QString data);

	void select(QString &SELECT,QString &ORDER);
	void Update();
	void Delete();
	void Backup();
	void Restore();
private:
	MasterData *Master;
	MasterPage	*Page;
	MasterImage *Image;
	MasterCategory *Category;
	QSqlQueryModel *MasterModel;
	int MasterJudge;
public slots:
	void on_pbMASTERSELECT_clicked();
	void on_combMASTERSel_1_currentIndexChanged(int index);
	void Tree_rowChanged(QModelIndex INDEX);
	void rowMoved(QModelIndex INDEX, QModelIndex INDEX2);
	void on_trMasterList_itemClicked(QTreeWidgetItem *item, int column);
    void on_MASTERView_itemClicked(QTableWidgetItem *item);
};

class MachineUI : public UIBase{
	Q_OBJECT
public:
	MachineUI(Datamanagement *parent);
	MachineUI(Ui::Datamanagement *ui,QObject *parent);
	void view();
	void clear();
	void changeUI();
	void resizeHeader();
	void setData(QStringList &DataList);
	QLineEdit *getLineEdit(int i);
	bool isEmpty(QStringList &DataList);

	void Insert();
	void Update();
	void Delete();
	void Backup();
	void Restore();
private:
	Machine *Mac;
	QSqlQueryModel *MacModel;
	QString OldMachineID;
public slots:
	void rowMoved (QModelIndex INDEX, QModelIndex INDEX2);
};

class WorkerUI : public UIBase{
	Q_OBJECT
public:
	WorkerUI(Datamanagement *parent);
	WorkerUI(Ui::Datamanagement *ui,QObject *parent);
	void view();
	void clear();
	void changeUI();
	void resizeHeader();
	//void setData(QStringList &DataList);
	void setData(QStringList &DataList,QDateTime &Updatetime);
	QLineEdit *getLineEdit(int i);
	bool isEmpty(QStringList &DataList);

	void Insert();
	void Update();
	void Delete();
	void Backup();
	void Restore();
private:
	Worker *Work;
	QSqlQueryModel *WorkerModel;
	QString OldWorkerID;
public slots:
	void rowMoved (QModelIndex INDEX, QModelIndex INDEX2);
};

class LibUI : public UIBase{
	Q_OBJECT
public:
	LibUI(Datamanagement *parent);
	LibUI(Ui::Datamanagement *ui,QObject *parent);
	void view();
	void changeUI();
	void resizeHeader();
	void setData(QStringList &DataList);

	void Delete();
	void Backup();
	void Restore();
	void saveRelatedMastercode(QIODevice &file,QString &MasterCode);
	void loadRelatedMastercode(QIODevice &file);
private:
	LibFolder *Folder;
	InspectLib *Lib;
	InspectLibType *LibType;
	QSqlQueryModel *LibModel;
	QSqlQueryModel *LibFolderModel;
	int LibJudge;
public slots:
	void showTree();
	void addChildTree(QString &QueryData, QTreeWidgetItem *ParentItem);
	void rowChanged(QModelIndex INDEX);
	void on_LibTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
	void on_INSPECTLIBView_itemClicked(QTableWidgetItem *item);
};

#endif // DATAMANAGEMENT_H