#ifndef MANAGEMASTERCONNECTION_H
#define MANAGEMASTERCONNECTION_H

#include <QMainWindow>
#include "ui_ManageMasterConnection.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class	ManageMasterConnection;
class	MasterCategoryForm;


class	QSqlSelectMasterModel : public QSqlTableModel
{
	ManageMasterConnection	*ParentWindow;
public:
	QSqlSelectMasterModel(QObject * parent, const QSqlDatabase &db);
	QString selectStatement () const;
};

class	QSqlConnectionModel : public QSqlTableModel
{
	ManageMasterConnection	*ParentWindow;
public:
	QSqlConnectionModel(QObject * parent, const QSqlDatabase &db);
	QString selectStatement () const;
};

class	QSqlContentModel : public QSqlTableModel
{
	ManageMasterConnection	*ParentWindow;
public:
	QSqlContentModel(QObject * parent, const QSqlDatabase &db);
	QString selectStatement () const;
};

class ManageMasterConnection : public QMainWindow,ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;
public:
	ManageMasterConnection(LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ManageMasterConnection();

	enum	_ListMode{
		_IDNormal
		,_IDReverse
		,_TimeNormal
		,_TimeReverse
		,_NameNormal
		,_NameReverse
	}ListMode;
	QString	StartSearchName;
	int		StartSearchID;

	int		CurrentMasterCode;
	int		RelationCode;
	QSqlConnectionModel *CModel;

private:
	Ui::ManageMasterConnectionClass ui;
	MasterCategoryForm	*MasterCategory;

	void	ShowListHeader(void);
	void	SelectView(void);

private slots:
	void on_pushButtonAddMaster_clicked();
	void on_pushButtonDeleteConnection_clicked();
	void on_pushButtonCreateNew_clicked();
	void on_tableViewContents_doubleClicked(QModelIndex);
	void on_tableViewConnection_doubleClicked(QModelIndex);
	void on_tableViewConnection_clicked(const QModelIndex &);
	void on_tableView_clicked(const QModelIndex &);
	void on_pushButtonClose_clicked();
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
};

#endif // MANAGEMASTERCONNECTION_H
