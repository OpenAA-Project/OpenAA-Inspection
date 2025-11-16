#ifndef SEARCHMASTERDATAFORM_H
#define SEARCHMASTERDATAFORM_H

#include <QDialog>
#include "ui_SearchMasterDataForm.h"

class RepairBase;

class SearchMasterDataForm : public QDialog
{
	Q_OBJECT

public:
	SearchMasterDataForm(RepairBase *ParentClass,const QStringList &trMFieldNames,const QStringList &twMFieldNames,QWidget *parent);
	~SearchMasterDataForm();

	QString GetMasterCode()	{	return MasterCode;	}

private slots:
	void MasterTreeRowChanged(QTreeWidgetItem *CIndex);		//マスターツリーのRowChangedイベント
	void MasterListRowChanged(const QModelIndex &CIndex);	//マスターリストのRowChangedイベント
	void pbSearchByMasterIDClicked();
	void pbSearchByMasterNameClicked();
	void pbReadMasterDataClicked();
	void pbCancelClicked();
	void MasterListsectionClicked(int logicalIndex);

private:
	Ui::SearchMasterDataFormClass ui;
	RepairBase *PClass;
	QStringList MTFieldNames,MFieldNames;
	QString MasterCode;

	int		CategoryID;
	int		StartSearchID;
	QString	StartSearchName;

	enum	_ListMode{
		_IDNormal
		,_IDReverse
		,_NameNormal
		,_NameReverse
		,_TimeNormal
		,_TimeReverse
		,_RemarkNormal
		,_RemarkReverse
	}ListMode;
	int	IDOrder;
	int	NameOrder;
	int	TimeOrder;
	int	RemarkOrder;

	int  ShowMasterTree	(bool UpdatesEnabled=true);
	void AddChildTree	(QTreeWidgetItem *ParentItem,QVariant *value);
};

#endif // SEARCHMASTERDATAFORM_H
