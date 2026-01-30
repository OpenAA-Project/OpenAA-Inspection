/*
 * Copyright (C) 2016
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
	void MasterTreeRowChanged(QTreeWidgetItem *CIndex);		//�}�X�^�[�c���[��RowChanged�C�x���g
	void MasterListRowChanged(const QModelIndex &CIndex);	//�}�X�^�[���X�g��RowChanged�C�x���g
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