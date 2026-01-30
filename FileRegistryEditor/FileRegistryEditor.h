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



#ifndef FILEREGISTRYEDITOR_H
#define FILEREGISTRYEDITOR_H

#include <QMainWindow>
#include "ui_FileRegistryEditor.h"
#include "XFileRegistry.h"
#include "XServiceForLayers.h"

class FileRegistryEditor : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

public:
	FileRegistryEditor(LayersBase *base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~FileRegistryEditor();

private:
	Ui::FileRegistryEditorClass ui;

	FileRegistry	*FRegistry;
	QString PathName;
	void	ShowInfo();

	bool	SQLLoadMachine(void);


private slots:
	void on_pushButtonLoadDatabase_clicked();
	void on_pushButtonSelectFolder_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // FILEREGISTRYEDITOR_H