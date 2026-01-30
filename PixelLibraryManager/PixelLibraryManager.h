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

#ifndef PIXELLIBRARYMANAGER_H
#define PIXELLIBRARYMANAGER_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include "ui_PixelLibraryManager.h"
#include "XServiceForLayers.h"

class PixelLibraryManager : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	PixelLibraryManager(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PixelLibraryManager();

private slots:
	void	twPixelLibraryListDoubleClicked(const QModelIndex &Index);
	void	twPixelLibraryListCurrentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn);

	void	cmbPixelLibraryNameListCurrentIndexChanged(int Index);
	void	cmbLibraryNameListCurrentIndexChanged(int Index);
	void	cmbUniqueNameListCurrentIndexChanged(int Index);

	void	pbSaveClicked();
	void	pbUpdateClicked();
	void	pbLoadClicked();
	void	pbAddRowClicked();
	void	pbDeleteRowClicked();
	void	pbCloseClicked();

private:
	Ui::PixelLibraryManagerClass ui;

	QComboBox	*cmbPixelLibraryNameList;
	QComboBox	*cmbAlgorithmNameList;
	QComboBox	*cmbLibraryNameList;
	QComboBox	*cmbUniqueNameList;
	QSpinBox	*sbPriority;

	QStringList	TableColHeader;
	QStringList	TableRowHeader;
	QStringList	PixelLibraryIDList;
	QStringList	PixelLibraryNameList;
	QStringList	AlgorithmListName;
	QStringList	LibraryIDList;
	QStringList	LibraryNameList;
	QStringList	UniqueNameList[1];

	int		NowRow;
	QString NowFileName;

	typedef	enum	_UniqueType{
		_DynamicClassify	=0
	}UniqueType;

	void	CreateTable();
	void	CreatePixelLibraryNameList();
	void	CreateAlgorithmNameList();
	bool	CreateLibraryNameList(int Row);
	bool	CreateUniqueNameList(int Row);
	void	CreatePriority();

	bool	SaveFile(const QString &FileName);
	bool	CheckLoadData(int Row,int Col,const QStringList &myStringList,QString &Msg);
	void	SetDataToTable(QTableWidget *W,int row,int col,QVariant value);
};

#endif // PIXELLIBRARYMANAGER_H