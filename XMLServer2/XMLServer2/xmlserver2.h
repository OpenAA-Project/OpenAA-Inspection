#ifndef XMLSERVER2_H
#define XMLSERVER2_H

#include <QWidget>
#include "ui_xmlserver2.h"
#include "clsTcpSvr.h"

class XMLServer2 : public QWidget
{
    Q_OBJECT

public:
    XMLServer2(QWidget *parent = 0);
    ~XMLServer2();

    clsTcpSvr *objSvr;
    void drawRowMstId(int port, const QByteArray &MstId);

private slots:
	void exitApp();
	void drawRequest(int port, QString svr, QString sts);
	void popParam();

private:
    Ui::XMLServer2Class ui;
    void addRow(int port, QString svr, QString sts);
};

#endif // XMLSERVER2_H
