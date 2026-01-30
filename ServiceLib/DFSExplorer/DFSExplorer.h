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

#ifndef DFSEXPLORER_H
#define DFSEXPLORER_H

#include <QMainWindow>
#include "ui_DFSExplorer.h"
#include <QTimer>
#include "XDFSClient.h"

class DFSExplorer : public QMainWindow
{
	Q_OBJECT

	QTimer		TM;
	DFSClient	Socket;
	TreeFolderContainer		Folders;
	TreeFolder				*CurrentFolder;
	FileAttrContainer		Files;
public:
	DFSExplorer(QString &IPAddress , int Address 
				,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DFSExplorer();

private slots:
    void on_pushButtonAddFolder_clicked();
	void	SlotTimeOut();
	void	SlotShowFolders();
	void	SlotShowFiles();

    void on_treeWidgetFolders_clicked(const QModelIndex &index);
    void on_pushButtonCopyTo_clicked();
    void on_pushButtonCopyFrom_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonRemoveFolder_clicked();

private:
	Ui::DFSExplorerClass ui;

	void	ShowFolder(void);
	void	SetSubFolder(QTreeWidgetItem *Parent ,TreeFolder *F);
	void	ShowFiles(void);
};

#endif // DFSEXPLORER_H