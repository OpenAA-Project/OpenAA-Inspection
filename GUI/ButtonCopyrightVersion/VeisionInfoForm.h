/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\VeisionInfoForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef VEISIONINFOFORM_H
#define VEISIONINFOFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class VeisionInfoForm;
}

class VeisionInfoForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit VeisionInfoForm(LayersBase *lbase ,QWidget *parent = 0);
    ~VeisionInfoForm();
    
signals:
    void	SignalClose(void);
private slots:
    void on_pushButton_clicked();

private:
    Ui::VeisionInfoForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // VEISIONINFOFORM_H
