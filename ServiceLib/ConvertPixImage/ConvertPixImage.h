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

#ifndef CONVERTPIXIMAGE_H
#define CONVERTPIXIMAGE_H

#include <QMainWindow>
#include "ui_ConvertPixImage.h"
#include "NList.h"

class	PixFileList : public NPList<PixFileList>
{
public:
	QString	Path;
	QString	FileName;
};



class ConvertPixImage : public QMainWindow
{
	Q_OBJECT

	NPListPack<PixFileList>	PixFileContainer;
	QString		LastDir;

public:
	ConvertPixImage(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ConvertPixImage();

private slots:
    void on_pushButtonAddPixFile_clicked();
    void on_pushButtonAddPixFolder_clicked();
    void on_pushButtonFindPath_clicked();
    void on_pushButtonExecuteConvert_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonDeleteList_clicked();

private:
	Ui::ConvertPixImageClass ui;

	void	ShowList(void);
	bool	ConvertToImage(PixFileList	*PixFile,const QString &OutPath,const QString &ImgFormat);

};

#endif // CONVERTPIXIMAGE_H