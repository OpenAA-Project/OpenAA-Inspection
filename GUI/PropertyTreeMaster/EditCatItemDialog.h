#ifndef EDITCATITEMDIALOG_H
#define EDITCATITEMDIALOG_H

#include <QDialog>

namespace Ui {
    class EditCatItemDialog;
}

#include <QSqlTableModel>
#include <QTableView>
#include <QToolButton>
#include "XServiceForLayers.h"
#include "NList.h"
#include "MasterCategoryForm.h"
#include<QTableWidget>

class	MachineButton;
class	MachineList;

class EditCatItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend class	QSqlLoadMasterModel;

	QFrame					ScrollFrame;
public:
    //explicit EditCatItemDialog(int TMItemID ,LayersBase *Base,QWidget *parent = 0);
	 explicit EditCatItemDialog(int TMItemID ,LayersBase *Base,QTableWidget *TMList,QWidget *parent = 0);
    ~EditCatItemDialog();

	int	SelectedMasterCode;
	QString SelectedMasterName;
	QString	CatName;
	bool	Deleted;

	NPListPack<MachineList>		MachineContainer;
	NPListPack<MachineButton>	MachineButtonContainer;

	void	RefreshGrid(void);
	QString	MakeMachineSQL(void);
	void	Initial(QString catname, int mastercode);
	QTableWidget *getTable();
	

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	void	MListSectionClicked ( int logicalIndex );

        void on_pushButtonStartSearchByID_clicked();

        void on_pushButtonStartSearchByName_clicked();

        void on_pushButtonNew_clicked();

        void on_pushButtonAdd_clicked();

        void on_tableWidgetDst_doubleClicked(const QModelIndex &index);

private:
    Ui::EditCatItemDialog *ui;
	MasterCategoryForm	*MasterCategory;
	QTableView *MListView;

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
	void	LoadMachineList(void);

};

class	QSqlLoadMasterModel : public QSqlTableModel
{
	EditCatItemDialog	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class	MachineButton : public QToolButton ,public NPList<MachineButton>
{
    Q_OBJECT
public:
	int MachineID;
	EditCatItemDialog	*ParentWindow;

	MachineButton(int _MachineID ,EditCatItemDialog *ParentWindow ,QWidget *parent);

private slots:
	void	ToggleButton(bool mode);
};


class	MachineList : public NPList<MachineList>
{
public:
	int		MachineID;
	QString	Name;
};


#endif // EDITCATITEMDIALOG_H
