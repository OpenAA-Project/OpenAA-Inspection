/*
 * Copyright (C) 2026
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

#ifndef EDITOCRITEMDIALOG_H
#define EDITOCRITEMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XColorSpace.h"

namespace Ui {
class EditOCRItemDialog;
}

class EditOCRItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditOCRItemDialog(LayersBase *Base, QWidget *parent = 0);
    ~EditOCRItemDialog();

	int32		Mergin;

	QString		ItemName;
	int			RegNumber;
	bool		InspectMatching;
	bool		SaveIntoResult;
	bool		OKByFailingRecognition;
	QStringList		CorrectList;

	void	ReflectToWindow(void);
	void	FromWindow(void);

private slots:
    void on_listWidgetMatchingList_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddMatchingList_clicked();
    void on_pushButtonSubMatchingList_clicked();
    void on_ButtonSaveNewItem_clicked();
    void on_ButtonUpdateItem_clicked();
    void on_pushButtonClose_clicked();

    void on_ButtonDeleteItem_clicked();


private:
    Ui::EditOCRItemDialog *ui;
};

#endif // EDITOCRITEMDIALOG_H