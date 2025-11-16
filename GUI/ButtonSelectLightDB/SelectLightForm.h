/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLightForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SELECTLIGHTFORM_H
#define SELECTLIGHTFORM_H

#include <QWidget>
#include <QByteArray>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NList.h"

namespace Ui {
class SelectLightForm;
}

class SelectLightForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

    class	LightPacket : public NPList<LightPacket>
    {
    public:
        int		MachineID;
        int		LightID;
    };
    NPListPack<LightPacket>	LightLines;
public:
    explicit SelectLightForm(LayersBase *pbase ,bool ShowSelectButtons ,bool EditPanel, int SelectMachineCode=-1 ,QWidget *parent = 0);
    ~SelectLightForm();

    int		SelectedMachineID;
    int		SelectedLightID;
    QByteArray	SelectedLight;

signals:
    void	SignalClose();
private slots:
    void on_tableWidgetLight_clicked(const QModelIndex &index);
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectLightForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;

    void	ShowList(void);
    void	SelectOne(void);
};

#endif // SELECTLIGHTFORM_H
