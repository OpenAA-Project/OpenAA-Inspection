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

#ifndef PROPERTYSWITCHPHASEFORM_H
#define PROPERTYSWITCHPHASEFORM_H

#include "XGUIFormBase.h"
#include "XSwitchPhase.h"
#include "XStandardPropertyForm.h"
#include <QPushButton>

namespace Ui {
class PropertySwitchPhaseForm;
}

class	EnableExecuteMatchButton : public QPushButton
{
	Q_OBJECT
public:
	int	Phase;

	EnableExecuteMatchButton(int phase);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int phase);
};

class PropertySwitchPhaseForm : public GUIFormBase
{
    Q_OBJECT

	PhaseItemListContainer	PhaseItemListInfo;
	PhaseItemInfoListContainer	MarkList;
	int		CurrentScanNo;
public:
    explicit PropertySwitchPhaseForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertySwitchPhaseForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1) override;

	void	ScanFrom1(int StartPhaseNo);
	void	CancelScan(void);
	void	AutoGeneration(void);
	void	DeleteAllPhases(void);
	void	DeleteAllMarks(void);
	void	ReUseMark(void);

private slots:
    void on_tableWidgetPhaseList_clicked(const QModelIndex &index);
    void on_pushButtonAddPhase_clicked();
    void on_pushButtonDelPhase_clicked();
    void on_pushButtonGoUp_clicked();
    void on_pushButtonGoDown_clicked();
    void on_tableWidgetMarkList_clicked(const QModelIndex &index);
    void on_toolButtonCapture_clicked();
    void on_pushButtonShowMatching_clicked();
    void on_tableWidgetMarkList_doubleClicked(const QModelIndex &index);
	void	SlotEnableExecuteMatchClicked(int phase);
    void on_pushButtonAutoGeneration_clicked();
    void on_pushButtonDeleteAll_clicked();

signals:
	void	SignalSwitchedImage(int CurrentScanNo);

private:
    Ui::PropertySwitchPhaseForm *ui;
    
    SwitchPhaseBase	*GetSwitchPhaseBase(void);

	void	ShowPhaseList(void);
	void	ShowMarkList(void);
};

#endif // PROPERTYSWITCHPHASEFORM_H