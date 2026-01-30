/*
 * Copyright (C) 2024
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

#ifndef SHOWKIDAMEASURERESULTFORM_H
#define SHOWKIDAMEASURERESULTFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowKidaMeasureResultForm;
}
class	EasyPropertyDentMeasureForm;

class	SwordList : public NPList<SwordList>
{
public:
	int	SlaveNo;
	int	ItemID;
	NGPoint	*Refer;
};


class ShowKidaMeasureResultForm : public GUIFormBase
{
    Q_OBJECT
    
	EasyPropertyDentMeasureForm	*EasyPropertyDentMeasurePointer[10];
	NPListPack<SwordList>	SwordListContainer;
public:
	int		SlaveNoToShow;

    explicit ShowKidaMeasureResultForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowKidaMeasureResultForm();
    
	virtual void	ReadyParam(void) override;
private slots:
	void	ResizeAction();
private:
    Ui::ShowKidaMeasureResultForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	void	ShowData(void);

};

#endif // SHOWKIDAMEASURERESULTFORM_H