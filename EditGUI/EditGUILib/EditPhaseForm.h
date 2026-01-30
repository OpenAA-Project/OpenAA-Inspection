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


#ifndef EDITPHASEFORM_H
#define EDITPHASEFORM_H

#include <QWidget>
#include"XParamGlobal.h"
#include "XServiceForLayers.h"
#include "WMultiGrid.h"

namespace Ui {
class EditPhaseForm;
}

class	EditPhaseForm;

class	PhaseGrid : public WMultiGrid
{
    EditPhaseForm	*EParent;

public:
    PhaseGrid(EditPhaseForm *eParent ,QWidget * parent=0):WMultiGrid(parent),EParent(eParent){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};

class EditPhaseForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    PhaseGrid	aGrid;
    int			OldPhaseIndex;
    QByteArray	CopiedBuff;
public:
    explicit EditPhaseForm(LayersBase *base ,QWidget *parent = 0);
    ~EditPhaseForm();

    void	SetGrid(void);

signals:
    void	SignalClose();
public slots:
    void	SlotClickedXYButton( int row ,int col);
private slots:
    void on_comboBoxPhase_currentIndexChanged(int index);
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonSaveFilter_clicked();

private:
    Ui::EditPhaseForm *ui;

    virtual	void closeEvent ( QCloseEvent * event )	override;
};

#endif // EDITPHASEFORM_H