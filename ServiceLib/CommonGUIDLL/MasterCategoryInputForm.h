/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MasterCategoryInputForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MASTERCATEGORYINPUTFORM_H
#define MASTERCATEGORYINPUTFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class MasterCategoryInputForm;
}

class MasterCategoryInputForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MasterCategoryInputForm(LayersBase *lbase ,const QString &folderName ,const QString &remark ,QWidget *parent = 0);
    ~MasterCategoryInputForm();

    QString	FolderName;
    QString	Remark;

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::MasterCategoryInputForm *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // MASTERCATEGORYINPUTFORM_H
