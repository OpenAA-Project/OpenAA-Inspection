#pragma once

#include <QTableWidget>

/////////////////////////////////////////////////////////////////////
// ƒL[“ü—Í‚ğó‚¯•t‚¯‚È‚¢QTableWidget
/////////////////////////////////////////////////////////////////////

class TableWidgetWithoutKey : public QTableWidget
{
	Q_OBJECT

public:
	TableWidgetWithoutKey(QWidget *parent):QTableWidget(parent){};

protected:
	virtual	void keyPressEvent(QKeyEvent *event)	override{};
};