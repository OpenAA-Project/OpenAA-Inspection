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

#ifndef PROPERTYALIGNMENTPROJECTIONFORM_H
#define PROPERTYALIGNMENTPROJECTIONFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentProjectionForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentProjectionPacket.h"
#include "XAlignmentProjection.h"

namespace Ui {
class PropertyAlignmentProjectionForm;
}

class PropertyAlignmentProjectionForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyAlignmentProjectionForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentProjectionForm();

	AlignmentProjectionPointListPack		PointList;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	ShowInEdit	(void)	override;

	void	CreateAlignmentPoint(FlexArea &area ,int globalPage ,int PeakCount ,double Angle, int UsageLayer);
    
private slots:
    void on_tableWidgetPoint_doubleClicked(const QModelIndex &index);
	void on_tableWidgetPoint_clicked(const QModelIndex &MIndex);

private:
    Ui::PropertyAlignmentProjectionForm *ui;

	void	ShowPointList(void);

	AlignmentProjectionBase	*GetAlignmentProjectionBase(void);
};

#endif // PROPERTYALIGNMENTPROJECTIONFORM_H