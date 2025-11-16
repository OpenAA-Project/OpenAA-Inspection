#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include <QMainWindow>
#include "ui_MultiOperation.h"

class MultiOperation : public QMainWindow
{
	Q_OBJECT

public:
	MultiOperation(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MultiOperation();

private slots:
    void on_pushButtonCreateNewConnect_clicked();

    void on_pushButtonUpdateConnect_clicked();

    void on_pushButtonDeleteConnect_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
	Ui::MultiOperationClass ui;
};

#endif // MULTIOPERATION_H
