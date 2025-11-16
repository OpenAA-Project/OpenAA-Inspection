#ifndef AUTOSTARTPARAMLIST_H
#define AUTOSTARTPARAMLIST_H

#include <QDialog>
#include "ui_AutoStartParamList.h"
#include "XAutoStart.h"

class AutoStartParamList : public QDialog
{
	Q_OBJECT

public:
	AutoStartParamList(AutoStartExeList &List ,QWidget *parent = 0);
	~AutoStartParamList();

	AutoStartExeList	TmpData;

private:
	Ui::AutoStartParamListClass ui;
	void	ShowList(void);

private slots:
	void on_pushButtonOK_clicked();
    void on_pushButtonAdd_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
};

#endif // AUTOSTARTPARAMLIST_H
