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

#ifndef LISTPIECEFORM_H
#define LISTPIECEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ListPieceForm;
}

class	AreaList : public NPList<AreaList>
{
public:
	int			Front;
	QString		Row;
	QString		Column;
	QString		AreaName;

	virtual	int	Compare(AreaList &src)	override;
};

class	AreaListContainer : public NPListPack<AreaList>
{
public:
	void	MergeArea(QString &aname);
	QStringList	MakeAreaList(void);
};


class ListPieceForm : public GUIFormBase
{
    Q_OBJECT

	AreaListContainer	FrontList;
	AreaListContainer	BackList;
public:
    explicit ListPieceForm(LayersBase *base ,QWidget *parent = 0);
    ~ListPieceForm();

	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	
private slots:
    void on_tableWidgetPiece_clicked(const QModelIndex &index);
	void	ResizeAction();
private:
    Ui::ListPieceForm *ui;

	void	UpdateList(void);
};

#endif // LISTPIECEFORM_H