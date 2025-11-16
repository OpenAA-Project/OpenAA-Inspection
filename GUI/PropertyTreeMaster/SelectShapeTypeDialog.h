#ifndef SELECTSHAPETYPEDIALOG_H
#define SELECTSHAPETYPEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectShapeTypeDialog;
}

class SelectShapeTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectShapeTypeDialog(LayersBase *base, QWidget *parent = 0);
    ~SelectShapeTypeDialog();
    
	double	ThreShape;
	double	ThreColor;
	int		SearchDot;

private slots:
    void on_pushButtonSetColorArea_clicked();

    void on_pushButtonSetShapeArea_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SelectShapeTypeDialog *ui;
};

#endif // SELECTSHAPETYPEDIALOG_H
