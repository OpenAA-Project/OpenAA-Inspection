#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_ErrorForm.h"

class ErrorForm : public QWidget
{
	Q_OBJECT

public:
//	ErrorForm(const QString &KibanNo,QWidget *parent = 0);			//D-20091106
	ErrorForm(const QString &KibanNo,int Code,QWidget *parent = 0);	//A-20091106
	~ErrorForm();

private slots:
	void	update();

private:
	Ui::ErrorFormClass ui;
	QTimer *timer;
	QPalette palette[2];
	char	Index;
};

#endif // ERRORFORM_H
