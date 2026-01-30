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

#ifndef NGCAUSEFORM_H
#define NGCAUSEFORM_H

#include <QWidget>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "SelectLotForm.h"

namespace Ui {
class NGCauseForm;
}

class NGCauseForm : public PQSystemRunner
{
    Q_OBJECT
    AlgorithmBasePointerContainer 	AlgorithmContainer;
	AlgorithmBase					*CurrentAlgorithm;
	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmLibraryList			*CurrentLibrary;
	SelectLotForm					LotForm;
public:
	int	ResultRelationCode;

    explicit NGCauseForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent = 0);
    ~NGCauseForm();
    virtual	bool	Initial(void)   override;
    virtual	const QString	GetPath(void)		override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemNGCause";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemNGCause.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_listWidgetAlgorithm_clicked(const QModelIndex &index);
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);
    void on_pushButtonSelectMaster_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();
    void on_pushButtonSelectArea_clicked();

private:
    Ui::NGCauseForm *ui;
};

#endif // NGCAUSEFORM_H