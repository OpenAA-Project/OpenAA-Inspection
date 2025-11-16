#pragma once

#include "ui_ResultLotLoadForm.h"

class ResultLotLoadForm : public QDialog
{
public:
	ResultLotLoadForm(QWidget *parent=NULL, Qt::WindowFlags f=0);

public:
	void setValue(quint32 FrontNGCount, quint32 FrontOKCount, quint32 BackNGCount, quint32 BackOKCount, bool isOtherErrorExist=false);

private:
	Ui::ResultLotLoadClass ui;
};
