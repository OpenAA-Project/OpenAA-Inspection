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

#ifndef NGMAPFORM_H
#define NGMAPFORM_H

#include <QWidget>
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"
#include "SelectLotForm.h"

namespace Ui {
class NGMapForm;
}

class MapForm;

class NGPointList : public NPList<NGPointList>
{
public:
	int	XPos,YPos;

	NGPointList(){}
	~NGPointList(){}
};

class MapListByMaster : public NPList<MapListByMaster>
{
public:
	EachMaster	*Master;
	int	MachineID;
	NPListPack<NGPointList>	NGPoints;

	MapListByMaster(){}
	~MapListByMaster(){}

	void	Add(int x ,int y);
};

class NGMapForm : public PQSystemRunner
{
    Q_OBJECT
    SelectLotForm					LotForm;
	NPListPack<LotListContainerWithRelationCode>	AllLotList;
	MapForm							*MapResult;
public:
	NPListPack<MapListByMaster>		MapList;
	int	ResultRelationCode;

    explicit NGMapForm(LayersBase *base ,const QString &root ,const QString &name
						,QWidget *parent = 0);
    ~NGMapForm();
    
	virtual	bool	Initial(void)   override;
	virtual	const QString	GetPath(void)			override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemNGMap";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemNGMap.dat";  }
protected:
	virtual	void showEvent(QShowEvent *event)	override;

private slots:
    void on_pushButtonSelectMaster_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_pushButtonView_clicked();

private:
    Ui::NGMapForm *ui;

	bool	CheckByLib(NGPoint *NG);
};

#endif // NGMAPFORM_H