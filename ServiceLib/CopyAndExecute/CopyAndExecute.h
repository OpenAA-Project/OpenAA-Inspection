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

#ifndef COPYANDEXECUTE_H
#define COPYANDEXECUTE_H

#include <QMainWindow>
#include "ui_CopyAndExecute.h"

class CopyAndExecute : public QMainWindow
{
	Q_OBJECT

	QString	SourcePath;
public:
	CopyAndExecute(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CopyAndExecute();

	void	Initial(QString	&SourcePath);
	void	DeleteFiles	(const QString &TargetFile);
	void	CopyFiles	(const QString &SourceFile,const QString &DestinationPath);
private:
	Ui::CopyAndExecuteClass ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // COPYANDEXECUTE_H