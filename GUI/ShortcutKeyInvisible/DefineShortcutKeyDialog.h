/*
 * Copyright (C) 2018
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

#ifndef DEFINESHORTCUTKEYDIALOG_H
#define DEFINESHORTCUTKEYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include <QPushButton>

struct	ShortcutKeyInfoList;

namespace Ui {
class DefineShortcutKeyDialog;
}


class DefineShortcutKeyDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	struct	ShortcutKeyInfoList	 *ShortcutKeyDim;
	int		CountOfShortcut;
public:
    explicit DefineShortcutKeyDialog(struct	ShortcutKeyInfoList	 _ShortcutKeyDim[] , int _CountOfShortcut ,LayersBase *base,QWidget *parent = 0);
    ~DefineShortcutKeyDialog();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_pushButtonLoadFile_clicked();

private:
    Ui::DefineShortcutKeyDialog *ui;

	void StoreDataFromWindow(struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
	void ShowDataToWindow	(struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);

	bool	SaveToFile  (QIODevice *f , struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
	bool	LoadFromFile(QIODevice *f , struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
};


class	CellInComponentControl : public QPushButton
{
    Q_OBJECT
public:
	DefineShortcutKeyDialog	*Parent;
	int	Row;
	QString		DLLRoot;
	QString		DLLName;
	QString		DLLInst;
	QString		ObjPath;
	QString		ObjName;

	CellInComponentControl(DefineShortcutKeyDialog *p ,int row);
	
	void	Set( const QString &DLLRoot
				,const QString &DLLName
				,const QString &DLLInst
				,const QString &ObjPath
				,const QString &ObjName);
	
private slots:
	void	SlotClicked();
};

#endif // DEFINESHORTCUTKEYDIALOG_H