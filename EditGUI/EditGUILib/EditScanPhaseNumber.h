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

#ifndef EDITSCANPHASENUMBER_H
#define EDITSCANPHASENUMBER_H

#include "EditGUILibResource.h"
#include <QDialog>
#include"XParamGlobal.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

namespace Ui {
    class EditScanPhaseNumber;
}

class	EditScanPhaseNumber;

class	ScanPhaseNumberGrid : public WMultiGrid
{
	EditScanPhaseNumber	*EParent;

public:
	ScanPhaseNumberGrid(EditScanPhaseNumber *eParent ,QWidget * parent=0):WMultiGrid(parent),EParent(eParent){}

protected:
	virtual	void	ChangeValue(int row ,int col,const QVariant &value)	override;
	virtual	void	GetValue(int row ,int col,QVariant &value)			override;
};

class EditScanPhaseNumber : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

	ScanPhaseNumberGrid	aGrid;
public:
    explicit EditScanPhaseNumber(LayersBase *Base,QWidget *parent = 0);
    ~EditScanPhaseNumber();

	void	SetGrid(void);
	void	Show(void);

public slots:
	void	ChangeValue();

signals:
	void	Reflect();
	void	ChangedValue();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::EditScanPhaseNumber *ui;
};

#endif // EDITSCANPHASENUMBER_H