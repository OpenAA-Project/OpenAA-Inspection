#ifndef SELECTHISTGRAMNAME_H
#define SELECTHISTGRAMNAME_H

#include <QDialog>
#include "XDataAlgorithm.h"

namespace Ui {
    class SelectHistgramName;
}

class SelectHistgramName : public QDialog
{
    Q_OBJECT

	AlgorithmBase *ABase;

public:
    explicit SelectHistgramName(AlgorithmBase *base ,QWidget *parent = 0);
    ~SelectHistgramName();

	int	HistgramID;

private slots:
    void on_pushButtonSelect_clicked();

    void on_listWidgetHistName_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectHistgramName *ui;
};

#endif // SELECTHISTGRAMNAME_H
