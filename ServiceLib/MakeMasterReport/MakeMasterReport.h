#ifndef MAKEMASTERREPORT_H
#define MAKEMASTERREPORT_H

#include <QMainWindow>
#include "ui_MakeMasterReport.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

class	MakeMasterReport;
class	QSqlLoadMasterModel;
class	ParamGlobal;

class MakeMasterReport : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT
	friend class	QSqlLoadMasterModel;

public:
	MakeMasterReport(ParamGlobal *GlobalParam ,LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MakeMasterReport();

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
	ParamGlobal *GlobalParam;

	void	ShowListHeader(void);
	void	SelectView(void);
	bool	LoadDataFromMaster(int masterCode);

private slots:
        void on_pushButtonOpenDatabase_clicked();
        void on_pushButtonStartSearchByID_clicked();
        void on_pushButtonStartSearchByName_clicked();
        void on_pushButtonClose_clicked();
	void	SlotClicked		(const QModelIndex &Index);
	void	SlotDoubleClicked(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	
	void	MListSectionClicked ( int logicalIndex );
    void on_pushButtonSelect_clicked();

private:
	Ui::MakeMasterReportClass ui;
};

#endif // MAKEMASTERREPORT_H
