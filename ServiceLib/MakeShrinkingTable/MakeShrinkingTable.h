#ifndef MAKESHRINKINGTABLE_H
#define MAKESHRINKINGTABLE_H

#include <QMainWindow>
#include "ui_MakeShrinkingTable.h"
#include "XImageExpand.h"

class MakeShrinkingTable : public QMainWindow
{
	Q_OBJECT

public:
	MakeShrinkingTable(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MakeShrinkingTable();

	ShrinkingPackContainer	ShrinkingPackContainerInstance;
private slots:
    void on_pushButtonStart_clicked();

private:
	Ui::MakeShrinkingTableClass ui;
};

#endif // MAKESHRINKINGTABLE_H
