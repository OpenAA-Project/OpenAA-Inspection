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


#ifndef SELECTLOTFORM_H
#define SELECTLOTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "commonguidll_global.h"

namespace Ui {
class SelectLotForm;
}
class	GUIFormBase;

class SelectLotForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    GUIFormBase	*ParentGUI;
public:
    explicit SelectLotForm(LayersBase *pbase ,QWidget *parent, QWidget *parentGUI ,int MaxLines);
    ~SelectLotForm();

    bool	RetMode;

    int			SelectedLotAutoCount;
    QString		SelectedLotID;
    QString		SelectedLotName;
    XDateTime	SelectedLastUpdated;
    QString		SelectedRemark;

    bool	RxSync(QByteArray &f);
    bool	RxSync(QIODevice &Buff);

    virtual	void	TxSync(QBuffer &f);

    void	CreateNewLot(const QString &LotID ,const QString &LotName ,bool Synchronized=true);


signals:
    void	SignalClose();

private slots:
    void on_tableWidgetLot_clicked(const QModelIndex &index);
    void on_tableWidgetLot_doubleClicked(const QModelIndex &index);
    void on_ButtonCreate_clicked();
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectLotForm *ui;
    IntList	LotAutoCounts;

    bool SelectLotAction(void);
    bool ExecuteCreateNew(void);

    virtual	void	closeEvent ( QCloseEvent * event )	override;
};

#endif // SELECTLOTFORM_H