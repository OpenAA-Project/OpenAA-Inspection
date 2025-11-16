#ifndef SETTINGREVERSELENSONESIDE_H
#define SETTINGREVERSELENSONESIDE_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class SettingReverseLensOneside;
}

class SettingReverseLensOneside : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingReverseLensOneside(LayersBase *base
									,double _Strength ,double _Width
									,  bool	_LeftSide   ,bool _RightSide
									,QWidget *parent = 0);
    ~SettingReverseLensOneside();

	double Strength ,Width;
	bool	LeftSide;
	bool	RightSide;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingReverseLensOneside *ui;
};

#endif // SETTINGREVERSELENSONESIDE_H
