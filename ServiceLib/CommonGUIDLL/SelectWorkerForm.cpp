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

#include "CommonGUIDLLResource.h"

#include "SelectWorkerForm.h"
#include "ui_SelectWorkerForm.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XFileRegistry.h"


QSqlWorkerListModel::QSqlWorkerListModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
}
QString QSqlWorkerListModel::selectStatement () const
{
    QString	ret=QString(/**/"SELECT WORKERID,NAME,SECTION FROM WORKER WHERE ALIVE>0 ORDER BY WORKERID;");
    return ret;
}

SelectWorkerForm::SelectWorkerForm(LayersBase *pbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::SelectWorkerForm)
    
{
    ui->setupUi(this);
    LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangCGSolver.SetUI(this);

    SelectWorkerID=-1;
    QSqlWorkerListModel *MModel = new QSqlWorkerListModel(this,GetLayersBase()->GetDatabase());
    MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    MModel->select();
//	MModel->removeColumn(0); // don't show the ID
    MModel->setHeaderData(0, Qt::Horizontal, tr(/**/"ID"	));
    MModel->setHeaderData(1, Qt::Horizontal, tr(/**/"Name"	));
    MModel->setHeaderData(2, Qt::Horizontal, tr(/**/"Section"));

    ui->MListView->setModel(MModel);
    ui->MListView->setColumnWidth (0, 50);
    ui->MListView->setColumnWidth (1, 140);
    ui->MListView->setColumnWidth (2, 140);
    connect(ui->MListView ,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
    connect(ui->MListView ,SIGNAL(doubleClicked (const QModelIndex & )),this,SLOT(SlotDoubleClicked(const QModelIndex &)));

    InstallOperationLog(this);
}

SelectWorkerForm::~SelectWorkerForm()
{
    delete ui;
}

void SelectWorkerForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	SelectWorkerForm::SlotClicked(const QModelIndex &Index)
{
    QSqlWorkerListModel	*M=dynamic_cast<QSqlWorkerListModel	 *>(ui->MListView->model());
    if(M!=NULL){
        QModelIndex RIndex=Index.sibling ( Index.row(), 0);
        SelectWorkerID=M->data(RIndex).toInt();
        ui->EditWorkerID->setText(QString::number(SelectWorkerID));
        QString	S=QString(/**/"SELECT WORKERID,NAME,SECTION,REMARK FROM WORKER WHERE WORKERID=")
            +QString::number(SelectWorkerID);
        QSqlQuery query(S ,GetLayersBase()->GetDatabase());
        if(query.next ()==false){
            return;
        }

        QString	Name	=query.value(query.record().indexOf(/**/"NAME"		)).toString();
        QString	Section	=query.value(query.record().indexOf(/**/"SECTION"	)).toString();
        QString	Remark	=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
        ui->EditName		->setText(Name);
        ui->EditSection	->setText(Section);
        ui->EditRemark	->setText(Remark);
        SelectWorkerName=Name;
    }
}

void	SelectWorkerForm::SlotDoubleClicked(const QModelIndex &Index)
{
    on_ButtonSelect_clicked();
}

void SelectWorkerForm::on_ButtonSelect_clicked()
{
    emit	SignalClose();
}