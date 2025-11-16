#ifndef SELECTBYORIGIN_H
#define SELECTBYORIGIN_H

#include <QDialog>
#include "XDisplayImage.h"

namespace Ui {
class SelectByOrigin;
}

class SelectByOrigin : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectByOrigin(LayersBase *Base,NPListPack<OriginNames> &originNameList,QWidget *parent = 0);
    ~SelectByOrigin();

    NPListPack<OriginNames>	OriginNameList;
    OriginNames				*Selected;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectByOrigin *ui;
};

#endif // SELECTBYORIGIN_H
