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



#ifndef DELETE_H
#define DELETE_H

#include <QWidget>
#include "ui_delete.h"
#include <QDir>
#include <QLibrary>
#include <QProgressBar>

class Delete : public QWidget
{
	Q_OBJECT

public:
	Delete(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
private:
	Ui::DeleteClass ui;
	
	void setFilters();
	void setFilters_Source();
	void DeleteMain(const QString &ChildDir);
	void removeFile(QDir &NowDir,const QString &NowPath);
	bool shouldDeleteFile(const QString &FileName);
	void removeSvn(const QString &NowPath);
	void removeSvnFile(const QString &SvnDir);
	void removeSvnDir(const QString &SvnDir);

	QStringList nameFilters;
private slots:
	void on_pushButtonSource_clicked();
	void on_pushButton_clicked();
};

#endif // DELETE_H