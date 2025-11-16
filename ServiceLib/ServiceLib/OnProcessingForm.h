/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\OnProcessingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
