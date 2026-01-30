/*
 * Copyright (C) 2012
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

#ifndef SELECTLEARNINGIMAGEFORM_H
#define SELECTLEARNINGIMAGEFORM_H

#include <QWidget>
#include "ui_SelectLearningImageForm.h"
#include "XServiceForLayers.h"
#include "XSelectLearningPacket.h"
#include "XDisplayImageHook.h"

class	ButtonSelectLearningTargetImage;

class SelectLearningImageForm : public QWidget,public FunctionServerClass ,public ServiceForLayers
{
	Q_OBJECT

	QString	DisplayImageRoot;
	QString	DisplayImageName;
	QString	DisplayImageInst;
	ButtonSelectLearningTargetImage	*ParentForm;

	NPListPack<RectClass>	RectStocker;
public:
	SelectLearningImageForm(LayersBase *Base
							,ButtonSelectLearningTargetImage *parentForm
							,const QString	&_DisplayImageRoot
							,const QString	&_DisplayImageName
							,const QString	&_DisplayImageInst
							,QWidget *parent = 0);
	~SelectLearningImageForm();

	void	Draw(QPainter &pnt,int movx ,int movy ,double ZoomRate);

private:
	Ui::SelectLearningImageFormClass ui;

	LearningImageListContainer	Stocker;
private slots:
	void on_pushButtonDelete_clicked();
	void on_pushButtonEdit_clicked();
	void on_listWidget_itemDoubleClicked(QListWidgetItem*);
	void on_pushButtonUpdate_clicked();
	void on_listWidget_clicked(const QModelIndex &);
	void on_pushButtonClose_clicked();
};

#endif // SELECTLEARNINGIMAGEFORM_H