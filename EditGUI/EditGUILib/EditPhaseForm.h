/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\EditPhaseForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
