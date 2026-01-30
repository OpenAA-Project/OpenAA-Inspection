/*
 * Copyright (C) 2022
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

#ifndef CHILDPANELFORM_H
#define CHILDPANELFORM_H

#include <QWidget>
#include <QTimer>
#include "mtFrameDraw.h"
#include "LiveMightexForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class ChildPanelForm;
}
class	ChildPanelForm;
class	LiveMightexForm;

class	ChildCamPanel : public mtFrameDraw
{
    Q_OBJECT

	ChildPanelForm		*LiveParent;
public:
	ChildCamPanel(QWidget *parent);

	virtual	void	SlotOnPaint(QPainter &pnt);
	virtual	void mousePressEvent ( QMouseEvent * e )	override;

signals:
	void	LSignalOnPaint(QPainter &pnt);
};

class ChildPanelForm : public QWidget , public ServiceForLayers
{
    Q_OBJECT
	ChildCamPanel	ViewerPanel;
	QImage	Pict;
public:
    LiveMightexForm	*ParentForm;

    explicit ChildPanelForm(LayersBase *base ,LiveMightexForm *p,QWidget *parent = 0);
    ~ChildPanelForm();

private slots:
    void on_pushButtonSetting_clicked();
    void on_toolButtonLive_clicked();
	void	SlotDraw();
public slots:
	void	SlotOnPaint(QPainter &pnt);
private:
    Ui::ChildPanelForm *ui;
    
    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // CHILDPANELFORM_H