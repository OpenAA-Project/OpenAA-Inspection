/*
 * Copyright (C) 2020
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

#ifndef INTEGRATIONRESULTLISTFORM_H
#define INTEGRATIONRESULTLISTFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"


namespace Ui {
class IntegrationResultListForm;
}

class IntegrationResultListForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	int		ResultDimCount;
	InspectionList	*ResultDim[100];
public:
	QFont	CharFont;
	bool	ShowPos;
	bool	ShowCause;
	bool	ShowValue;
	int32	ScrollerWidth;

    explicit IntegrationResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationResultListForm();

	virtual	void	Prepare(void) override;
	void	ShowList(void);

private:
    Ui::IntegrationResultListForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual void	StartLot	(void) override;
signals:
	void	SignalShowList();
private slots:
	void	ResizeAction();
	void	SlotShowList();
    void on_tableWidget_clicked(const QModelIndex &index);
};

#endif // INTEGRATIONRESULTLISTFORM_H