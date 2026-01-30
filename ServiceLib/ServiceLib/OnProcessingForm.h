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


#ifndef ONPROCESSINGFORM_H
#define ONPROCESSINGFORM_H

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include "XServiceForLayers.h"
#include<QTimer>

namespace Ui {
class OnProcessingForm;
}

class OnProcessingForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    bool	ModeShowing;
    QTimer	TM;

    class	ProgressList
    {
        QProgressBar	*PBar;
        QLabel			*Label;

    public:
        explicit    ProgressList(QWidget *parent);
        ~ProgressList(void);

        void	SetPage(int page ,int YPoint);
        void	SetMaximum(int d);
        void	StepIt(void);
        void	SetValue(int d);
        int		maximum(void);
        int		value(void);
        void	show(void);
    };
    ProgressList	**ProgressListPointer;
    int				AllocatedPageNumb;

public:
    explicit OnProcessingForm(LayersBase *lbase ,QWidget *parent = 0);
    ~OnProcessingForm();

    void	SetCancelMode(bool CancelMode);
    void	SetMessage(QString message);
    void	Set(int page ,int currentValue ,int maxValue);
    void	SetMax(int maxValue);
    void	SetValue(int page ,int currentValue);
    void	AddMax(int localpage ,int maxValue);
    void	Step(int localpage);

    void	Show(void);
    void	Hide(void);
    void	DelayedHide(int sec);

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonClose_clicked();
    void	SlotCheck();
private:
    Ui::OnProcessingForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;
    virtual	void showEvent( QShowEvent * event )		override;
    int		LanguageCode;
    void	CheckPageNumb(void);
};

#endif // ONPROCESSINGFORM_H