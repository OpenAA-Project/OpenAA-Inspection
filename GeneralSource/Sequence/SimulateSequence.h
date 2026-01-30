/*
 * Copyright (C) 2025
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


#ifndef SIMULATESEQUENCE_H
#define SIMULATESEQUENCE_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class SimulateSequence;
}

class	Sequence;
class	SeqControl;
class	ShowCOMForm;

class SimulateSequence : public QWidget
{
    Q_OBJECT
    SeqControl	*BaseParent;
    int         ComCount;
    ShowCOMForm **ShowCOMFormList;
public:
    explicit SimulateSequence(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~SimulateSequence();

    void  ShowSeqList(void);
    void  ShowIO(void);
    void  ShowSystemReg(void);
    void  ShowSequence(int tabindex);
    void  ShowTab(void);
    void  ShowWReg(void);
    void  ShowBReg(void);
    void  ShowCReg(void);
    void  ShowGReg(void);
    void  ShowPReg(void);
    void  ShowQReg(void);
    void  ShowRReg(void);
    void  ShowLanvar(void);
    void  ShowFIFO(void);
    void  ShowFReg(void);
    void  ViewAll(int TabIndex);
    void  ShowLWReg(int TabIndex);
    void  ShowLBReg(int TabIndex);
    void  ShowLCReg(int TabIndex);
    void  ShowLFReg(int TabIndex);
    void  ShowCOM(void);

    Sequence    * GetSeq(int TabIndex);

private slots:
    void on_SGridSystemReg_doubleClicked(const QModelIndex &index);
    void on_SGridSystemBReg_doubleClicked(const QModelIndex &index);
    void on_SGridSystemQReg_doubleClicked(const QModelIndex &index);
    void on_SGridSystemRReg_doubleClicked(const QModelIndex &index);
    void on_SGridWReg_doubleClicked(const QModelIndex &index);
    void on_IOGrid_doubleClicked(const QModelIndex &index);
    void on_SGridBReg_doubleClicked(const QModelIndex &index);
    void on_SGridFReg_doubleClicked(const QModelIndex &index);
    void on_SGridCReg_doubleClicked(const QModelIndex &index);
    void on_SGridGReg_doubleClicked(const QModelIndex &index);
    void on_LanGrid_doubleClicked(const QModelIndex &index);
    void on_SGridLBReg_doubleClicked(const QModelIndex &index);
    void on_SGridLWReg_doubleClicked(const QModelIndex &index);
    void on_SGridLFReg_doubleClicked(const QModelIndex &index);
    void on_SGridLCReg_doubleClicked(const QModelIndex &index);
    void on_SeqGrid_clicked(const QModelIndex &index);
    void on_SGridFifo_clicked(const QModelIndex &index);
    void on_ViewButton_clicked();
    void on_BreakPointButton_clicked();
    void on_GoButton_clicked();
    void on_StepButton_clicked();
    void on_StopButton_clicked();
    void on_ShowButton_clicked();
    void on_CloseButton_clicked();
    void on_tableWidgetCOMReg_doubleClicked(const QModelIndex &index);

private:
    Ui::SimulateSequence *ui;
};

#endif // SIMULATESEQUENCE_H