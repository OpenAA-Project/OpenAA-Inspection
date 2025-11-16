#ifndef MANAGEBYLOT_H
#define MANAGEBYLOT_H

#include <QDialog>
#include <QToolButton>
#include <QModelIndex>
#include "XResultDataManager.h"
#include "MasterCategoryForm.h"
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include "NList.h"
#include "XMLClient.h"
#include "XDatabaseLoader.h"

namespace Ui {
    class ManageByLot;
}


class ManageByLot;
class	QSqlLoadMasterModel : public QSqlTableModel
{
	ManageByLot	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;


};

class	MachineButton : public QToolButton ,public NPList<MachineButton>
{
    Q_OBJECT
public:
	int MachineID;
	ManageByLot	*ParentWindow;

	MachineButton(int _MachineID ,ManageByLot *ParentWindow ,QWidget *parent);

private slots:
	void	ToggleButton(bool mode);
};


class	MachineList : public NPList<MachineList>
{
public:
	int		MachineID;
	QString	Name;
};

class ManageByLot : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend class	QSqlLoadMasterModel;

	//QFrame					ScrollFrame;
	//QWidget					ScrollFrame;
	ResultDataManagerParam	*SParam;

	int	SelectedMachineID ,SelectedMasterCode;

	XMLServerHandle	*XMLServer;
	std::shared_ptr<DatabaseLoader>	SQLDatabase;
	RServerParam	ServerParam;

	QStringList		EnumResultList;

	QStringList hhLotHeaderList;

	QString hhLotLabelLotFileName;
	QString hhLotLabelLotName;
	QString hhLotLabelFirstInsTime;
	QString hhLotLabelLastInsTime;
	QString hhLotLabelInspectCount;

	QStringList hhInsHeaderList;

	QString hhInsLabelEID;
	QString hhInsLabelDay;
	QString hhInsLabelResult;

	class	LotInfo : public NPList<LotInfo>
	{
	public:
		QString	TableName;
		QString LotName;
		QString LotID;
		QString LotRemark;
		QString StartTimeValue;
		QString EndTimeValue;
		int		ISTCount;
		QDateTime	StartTime;
		LotInfo(void){	ISTCount=0;	}
	};
	NPListPack<LotInfo>		CurrentAllLots;
	QStringList				CurrentLotTime;
public:
    explicit ManageByLot(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent = 0);
    ~ManageByLot();

	NPListPack<MachineList>		MachineContainer;
	NPListPack<MachineButton>	MachineButtonContainer;

	void	RefreshGrid(void);
	QString	MakeMachineSQL(void);

private:
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

	void	ShowLotAll(int MachineID ,int MasterCode);
	void	ShowAllInspect(LotInfo *w);
	void	DeleteLot(int MasterCode, const QString &lotFilename);

private slots:
	void on_pushButtonStartSearchByID_clicked();
	void on_pushButtonStartSearchByName_clicked();
	void on_pushButtonDeleteLot_clicked();
	void on_pushButtonDeleteAll_clicked();
	void on_pushButtonDeleteLines_clicked();
	void on_tableWidgetLot_doubleClicked(const QModelIndex &index);
	void on_pushButtonBackup_clicked();
	void on_pushButtonRestore_clicked();
	void on_pushButtonClose_clicked();
	void on_cbShowInspectFirstEndTime_stateChanged(int state);
	void on_cbShowInspectionCount_stateChanged(int state);

	void clearInspectionTable();

	void	SlotClicked		(const QModelIndex &Index);
	void	SlotSelectCategory(int CategoryID ,QString FolderName ,QString Remark);
	void	SlotResizeHorizontalItemWidth();
	
	void	MListSectionClicked ( int logicalIndex );
    void	on_pushButtonBackupOnly_clicked();

private:
    Ui::ManageByLot *ui;
};

#endif // MANAGEBYLOT_H
