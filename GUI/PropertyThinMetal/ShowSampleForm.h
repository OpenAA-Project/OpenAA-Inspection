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

#ifndef SHOWSAMPLEFORM_H
#define SHOWSAMPLEFORM_H

#include <QWidget>
#include <QTableWidget>
#include "XThinMetal.h"
#include "XThinMetalLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowSampleForm;
}

class ShowSampleForm;
class	SampleImagePanel : public QWidget,public ServiceForLayers
{
	ShowSampleForm	*Parent;
public:
	int		MovX,MovY;
	double	ZoomRate;

	SampleImagePanel(LayersBase *base ,ShowSampleForm *parent);

	void	SetInitial(CoeffImageList *a);
protected:
    virtual	void	paintEvent(QPaintEvent *event)	override;

protected:
	virtual void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual void	mouseMoveEvent ( QMouseEvent * e )		override;
	virtual void	mouseReleaseEvent ( QMouseEvent * e )	override;
	virtual void	wheelEvent ( QWheelEvent * event )		override;
};

class ShowSampleForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
	ThinMetalInfoList *ItemInfo;
	IntList				Judgements;
	CoeffImageList		CurrentSample;
	SampleImagePanel	SamplePanel;

    explicit ShowSampleForm(ThinMetalInfoList *L ,LayersBase *base ,QWidget *parent = 0);
    ~ShowSampleForm();

	void	ShowList(void);

private slots:

    void on_pushButtonDeleteSelection_clicked();
    void on_pushButtonClose_clicked();
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::ShowSampleForm *ui;
};

#endif // SHOWSAMPLEFORM_H