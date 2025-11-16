#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditRWParameter.h"
#include "XParamRegulusWorld.h"
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTranslator>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "WEditParameterTab.h"
#include "WMultiGrid.h"
#include "EditRWDeviceParamForm.h"

class EditRWParameter : public QMainWindow,public ServiceForLayers
{
    Q_OBJECT

    WEditParameterTab	    *WTab;
    EditRWDeviceParamForm   *WDeviceTab;
public:
    EditRWParameter(LayersBase *base,QWidget *parent = nullptr);
    ~EditRWParameter();

private slots:
    void on_SaveButton_clicked();
    void on_UpdateDefaultButton_clicked();
    void on_LoadButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::EditRWParameterClass ui;

    QString		RWParamLoadedFileName;

    virtual	void resizeEvent(QResizeEvent *e)	override;
};
