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


#ifndef SELECTWORKERFORM_H
#define SELECTWORKERFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include <QSqlTableModel>
#include "XServiceForLayers.h"

namespace Ui {
class SelectWorkerForm;
}

class	QSqlWorkerListModel : public QSqlTableModel
{
public:
    QSqlWorkerListModel(QObject * parent, QSqlDatabase db);
    QString selectStatement () const;
};

class SelectWorkerForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectWorkerForm(LayersBase *pbase ,QWidget *parent = 0);
    ~SelectWorkerForm();

    int		SelectWorkerID;
    QString	SelectWorkerName;

signals:
    void	SignalClose();
private slots:
    void on_ButtonSelect_clicked();
    void	SlotClicked(const QModelIndex &Index);
    void	SlotDoubleClicked(const QModelIndex &Index);
private:
    Ui::SelectWorkerForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // SELECTWORKERFORM_H