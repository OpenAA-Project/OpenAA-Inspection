#ifndef SHOWIOFORM_H
#define SHOWIOFORM_H

#include <QDialog>
#include "DummyPIO.h"
#include <QTableWidgetItem>

namespace Ui {
    class ShowIOForm;
}

class ShowIOForm : public QDialog
{
    Q_OBJECT

public:
    explicit ShowIOForm(QWidget *parent = 0);
    ~ShowIOForm();

	bool	InBit[DummyBitCount];
	bool	OutBit[DummyBitCount];

	void	ShowOut(void);

private slots:
        void on_twIN_itemChanged(QTableWidgetItem *item);

        void on_twOUT_itemChanged(QTableWidgetItem *item);

private:
    Ui::ShowIOForm *ui;
};

#endif // SHOWIOFORM_H
