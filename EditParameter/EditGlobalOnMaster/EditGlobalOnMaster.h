#ifndef EDITGLOBALONMASTER_H
#define EDITGLOBALONMASTER_H

#include <QMainWindow>
#include "ui_EditGlobalOnMaster.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class EditGlobalOnMaster;

class	QSqlLoadMasterModel : public QSqlTableModel
{
	EditGlobalOnMaster	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;

};

class EditGlobalOnMaster : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;

public:
	EditGlobalOnMaster(ParamGlobal *GlobalParam ,LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditGlobalOnMaster();

	void	RefreshGrid(void);
private:
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;
	int		SelectedMasterCode;

	enum	_ListMode{
		_IDNormal
		,_IDReverse
		,_TimeNormal
		,_TimeReverse
		,_NameNormal
		,_NameReverse
		,_LastEditNormal
		,_LastEditReverse
	}ListMode;
	QString	StartSearchName;
	int		StartSearchID;
	void	ShowListHeader(void);
	void	SelectView(void);

private slots:
        void on_pushButtonOpenDatabase_clicked();
        void on_pushButtonStartSearchByID_clicked();
        void on_pushButtonStartSearchByName_clicked();
        void on_pushButtonClose_clicked();

	void	SlotClicked		(const QModelIndex &Index);
	void	SlotDoubleClicked(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	
	void	MListSectionClicked ( int logicalIndex );

private:
	Ui::EditGlobalOnMasterClass ui;
};

#endif // EDITGLOBALONMASTER_H
