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

#ifndef PROPERTYPARTIALIMAGINGFORM_H
#define PROPERTYPARTIALIMAGINGFORM_H

#include <QWidget>
#include "XPartialImaging.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XPropertyPartialImagingPacket.h"

namespace Ui {
class PropertyPartialImagingForm;
}

class PropertyPartialImagingForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyPartialImagingForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyPartialImagingForm();

	PartialImagingBase	*GetPartialImagingBase(void);

	void	ShowLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyPartialImagingForm *ui;

	PartialImagingInfoContainer	PInfoContainer;

};

#endif // PROPERTYPARTIALIMAGINGFORM_H