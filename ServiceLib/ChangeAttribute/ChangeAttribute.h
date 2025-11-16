#ifndef CHANGEATTRIBUTE_H
#define CHANGEATTRIBUTE_H

#include <QMainWindow>
#include "ui_ChangeAttribute.h"

class ChangeAttribute : public QMainWindow
{
	Q_OBJECT

public:
	ChangeAttribute(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ChangeAttribute();

private slots:
    void on_pushButtonSelectGUI_clicked();

    void on_pushButtonSelectSequence_clicked();

    void on_pushButtonSelectFilter_clicked();

    void on_pushButtonSendGUI_clicked();

    void on_pushButtonSendSequence_clicked();

    void on_pushButtonSendFilter_clicked();

private:
	Ui::ChangeAttributeClass ui;
};

#endif // CHANGEATTRIBUTE_H
