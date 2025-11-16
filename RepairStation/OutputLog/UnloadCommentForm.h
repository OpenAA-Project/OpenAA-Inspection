#ifndef UNLOADCOMMENTFORM_H
#define UNLOADCOMMENTFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_UnloadCommentForm.h"

class UnloadCommentForm : public QWidget
{
	Q_OBJECT

public:
	UnloadCommentForm(QWidget *parent = 0);
	~UnloadCommentForm();

	void	SetShowPickupEnable	(QString &KibanNo);
	void	SetShowMaxOverEnable(QString &KibanNo);

private slots:
	void	update();

private:
	Ui::UnloadCommentFormClass ui;
	QTimer *timer;
	QPalette palette[2];
	char	Index;
};

#endif // UNLOADCOMMENTFORM_H
