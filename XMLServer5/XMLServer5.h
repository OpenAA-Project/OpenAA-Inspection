#ifndef XMLSERVER5_H
#define XMLSERVER5_H

#include <QMainWindow>
#include "ui_XMLServer5.h"

class XMLServer5 : public QMainWindow
{
	Q_OBJECT

public:
	XMLServer5(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~XMLServer5();

private:
	Ui::XMLServer5Class ui;
};

#endif // XMLSERVER5_H
