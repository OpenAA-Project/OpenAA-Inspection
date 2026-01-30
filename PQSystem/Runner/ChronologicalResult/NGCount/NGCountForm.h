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

#ifndef NGCOUNTFORM_H
#define NGCOUNTFORM_H

#include <QWidget>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "SelectLotForm.h"
#include "XFlexArea.h"

namespace Ui {
class NGCountForm;
}

class ChronologicalGraphForm;


class NGResultList : public NPList<NGResultList>
{
public:
	XDateTime					InspectionTime;
	int64						InspectionID;
	LotListWithResult			*LotPointer;
	int							RelationCode;

	NGResultList()	{	LotPointer=NULL;	}
	~NGResultList(){}
};

class NGCountForm : public PQSystemRunner
{
    Q_OBJECT
    SelectLotForm					LotForm;
	NPListPack<LotListContainerWithRelationCode>	AllLotList;
	ChronologicalGraphForm	*Graph;
public:
	int							ResultRelationCode;
	NPListPack<NGResultList>	ResultList;
	FlexArea					SelectArea;

    explicit NGCountForm(LayersBase *base ,const QString &root ,const QString &name
							,QWidget *parent = 0);
    ~NGCountForm();
    
	virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemNGCount";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemNGCount.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();
    void on_pushButtonExcel_clicked();
    void on_pushButtonSelectArea_clicked();

private:
    Ui::NGCountForm *ui;

	bool	CheckByLib(NGPoint *NG);
};

#endif // NGCOUNTFORM_H