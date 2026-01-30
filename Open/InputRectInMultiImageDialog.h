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

#pragma once

#include <QDialog>
#include <QPoint>

#include "ui_InputRectInMultiImageDialog.h"

// This Dialog is view one image on itself.
// User can draw rect on image and out signal from this.
// Also, user can shift move image, zoom up, down and reset.

// (example 1.)
// 
// QList<QImage> imageList;
// 
// ...// create list
// 
// InputRectInImageDialog dialog;
// 
// dialog.setImageList(imageList);
// 
// connect(&dialog, SIGNAL(rectCreated(QPoint, qreal, QRect)), this, SLOT(OnRectCreated(QPoint, qreal, QRect)));
// 
// dialog.exec();// -> if user create rect until exec(), slot function OnrectCreated() will be executed.
//
// (example 2.)
// 
// QList<QImage> imageList;
// 
// ...// create list
// 
// InputRectInImageDialog dialog;
// 
// dialog.setImageList(imageList);
// 
// if(dialog.exec()==QDialog::Accepted)==true){// -> if user create rect until exec(), slot function OnrectCreated() will be executed.
//	// on OK button clicked
// }
//
class InputRectInMultiImageDialog : public QDialog
{
	Q_OBJECT

public:
	InputRectInMultiImageDialog(QWidget *parent=NULL);

public:
	void setImageList(const QList<QImage> &imageList, const QList<QPoint> &outlineList);
	void setFirstExpand(bool enable){ canvas()->setFirstExpand(enable); };

public slots:
	void setZoomStepLimit(quint32 limitCount);
	void setZoomStep(int step);
	void zoomStepIn();
	void zoomStepOut();
	void setResultRect(const QRect &rect, qreal zoomRate=1.0);
	void setTopPage(qint32 page);

protected:
	void keyPressEvent(QKeyEvent *);

private:
	Ui::InputRectInMultiImageDialogClass m_ui;

private:
	inline const Ui::InputRectInMultiImageDialogClass &ui() const { return m_ui; };
	inline Ui::InputRectInMultiImageDialogClass &ui() { return m_ui; };
	inline const InputRectInMultiImageWidget *canvas() const { return ui().wCanvas; };
	inline InputRectInMultiImageWidget *canvas() { return ui().wCanvas; };

private slots:
	//void on_rbDefault_toggled(bool checked);
	void on_rbCreateRect_toggled(bool checked);
	void on_rbShiftImage_toggled(bool checked);

public:
	QRect resultRect() const;
};