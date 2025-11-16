#ifndef TESTFLUORESCENTFLAT_H
#define TESTFLUORESCENTFLAT_H

#include <QMainWindow>
#include "ui_TestFluorescentFlat.h"
#include "XFluorescentFlat.h"

class TestFluorescentFlat : public QMainWindow
{
	Q_OBJECT

	SystemLEDSheet	SystemData;

public:
	TestFluorescentFlat(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TestFluorescentFlat();

private slots:
        void on_pushButtonSetAll_clicked();
        void on_pushButtonOK_clicked();

        void on_toolButtonOnOff_clicked();

private:
	Ui::TestFluorescentFlatClass ui;

	void	FromWindow(void);
	void	ToWindow(void);

};

#endif // TESTFLUORESCENTFLAT_H
