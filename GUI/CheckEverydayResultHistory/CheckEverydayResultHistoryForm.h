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

#ifndef CHECKEVERYDAYRESULTHISTORYFORM_H
#define CHECKEVERYDAYRESULTHISTORYFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XCheckEverydayCommon.h"

namespace Ui {
class CheckEverydayResultHistoryForm;
}

class	CheckEverydayResultHistoryForm;

class	ResultListOfCheckEveryday : public NPList<ResultListOfCheckEveryday>
{
public:
	XDateTime	ResultTime;
	double		CurrentValue;
	bool		Result;
	int64		InspectionID;

	ResultListOfCheckEveryday(void){}

	bool	SaveText(QTextStream &f);
};


class	HistoryListOfCheckEveryday : public NPList<HistoryListOfCheckEveryday>
{
	CheckEverydayResultHistoryForm	*Parent;
public:
	int32		Page;
	int32		Layer;
	int32		ID;
	NPListPack<ResultListOfCheckEveryday>	ResultContainer;

	HistoryListOfCheckEveryday(CheckEverydayResultHistoryForm *parent):Parent(parent){}

	bool	SaveText(QTextStream &f);
};


class CheckEverydayResultHistoryForm : public GUIFormBase
{
    Q_OBJECT

	CheckEverydayLightInfoContainer	InfoLight;
	CheckEverydayFocusInfoContainer	InfoFocus;

	NPListPack<HistoryListOfCheckEveryday>	HistoryList;

public:
    explicit CheckEverydayResultHistoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~CheckEverydayResultHistoryForm();

	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	HistoryListOfCheckEveryday	*SearchHistory(int page ,int layer ,int ld);
	QString						SearchItemName(int page ,int layer ,int ld);

private slots:
    void on_pushButtonSaveButton_clicked();
    void on_tableWidgetItemList_clicked(const QModelIndex &index);

private:
    Ui::CheckEverydayResultHistoryForm *ui;
};

//-----------------------------------------------------------------------------------------------------------


#endif // CHECKEVERYDAYRESULTHISTORYFORM_H