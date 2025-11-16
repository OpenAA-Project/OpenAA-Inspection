#ifndef MESSAGEFORM_H
#define MESSAGEFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_MessageForm.h"

class MessageForm : public QWidget
{
	Q_OBJECT

public:
	MessageForm(QWidget *parent = 0);
	~MessageForm();

	Ui::MessageFormClass ui;
	QPalette palette[2];

	void SetBlink();

private slots:
	void	update();

private:
	QTimer *timer;
	char	Index;
};

#endif // MESSAGEFORM_H
