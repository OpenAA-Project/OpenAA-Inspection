#ifndef XMLDB_MAKEDAT_H
#define XMLDB_MAKEDAT_H

#include <QWidget>
#include "ui_xmldb_makedat.h"
#include "clsMakeDat.h"

class XMLDB_MakeDat : public QWidget
{
    Q_OBJECT

public:
    XMLDB_MakeDat(QWidget *parent = 0);
    ~XMLDB_MakeDat();

    QString dbFile;

private slots:
	void addIst();
	void exitWin();
	void showMess(QString mess);
	void updLotID(QString lid);

	void fileSel();
	void execCreate();

private:
    Ui::XMLDB_MakeDatClass ui;

    clsMakeDat *objThr;
};

#endif // XMLDB_MAKEDAT_H
