#ifndef ALLCHECKEDFORM_H
#define ALLCHECKEDFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_AllCheckedForm.h"

class AllCheckedForm : public QWidget
{
	Q_OBJECT

public:
	AllCheckedForm(QWidget *parent = 0);
	~AllCheckedForm();

	void	SetShowPickupEnable	(QString &KibanNo);
	void	SetShowMaxOverEnable(QString &KibanNo);

private slots:
	void	update();

private:
	Ui::AllCheckedFormClass ui;
	QTimer *timer;
	QPalette palette[2];
	char	Index;
};

#endif // ALLCHECKEDFORM_H
