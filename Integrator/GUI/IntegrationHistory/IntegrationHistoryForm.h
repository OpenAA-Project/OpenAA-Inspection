/*
 * Copyright (C) 2023
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

#ifndef INTEGRATIONHISTORYFORM_H
#define INTEGRATIONHISTORYFORM_H

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
class IntegrationHistoryForm;
}

class	SpecialHistoryColumn : public NPList<SpecialHistoryColumn>
{
public:
	QString	ColumnName;

	SpecialHistoryColumn(void){}
	virtual	QString		JudgeFunc(InspectionList *L[][2],int MachineCount,QColor &RetColumnColor)	=0;
};



class IntegrationHistoryForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	int	CurrentOKCount;
	int	TMOutCount;
	int	*IDDim;
	int	MaxID;
public:
	int32	AllocatedCount;
	int32	ScrollerWidth;
	QFont	CharFont;
	bool	ShowOnlyNG;
	bool	ShowTotal;
	NPListPack<SpecialHistoryColumn>	SpecialHistoryColumnContainer;

    explicit IntegrationHistoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationHistoryForm();

	virtual	void	Prepare(void) override;
	void	ShowList(void);
	void	ClearList(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

private slots:
    void on_tableWidgetHistory_doubleClicked(const QModelIndex &index);
	void	ResizeAction();
private:
    Ui::IntegrationHistoryForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual void	StartLot	(void) override;
};

class	CmdAddSpecialHistoryColumnPacket : public GUIDirectMessage
{
public:
	SpecialHistoryColumn	*NewColumn;

	CmdAddSpecialHistoryColumnPacket(LayersBase *base):GUIDirectMessage(base){	NewColumn=NULL;	}
	CmdAddSpecialHistoryColumnPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	NewColumn=NULL;	}
};

#endif // INTEGRATIONHISTORYFORM_H