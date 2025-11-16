#ifndef XMLSERVER_IF_H
#define XMLSERVER_IF_H

#include <QWidget>
#include "ui_xmlserver_if.h"

#include "XMLServerHandle.h"

class XMLServer_IF : public QWidget
{
    Q_OBJECT

public:
    XMLServer_IF(QWidget *parent = 0);
    ~XMLServer_IF();

public slots:
	void showMess(QString mess);

private slots:
	void exitApp();
	void connectSvr();
	void chkStats();
	void disConnectSvr();

	void selectXML();
	void firstXML();
	void nextXML();

	void addXML();
	void appendXML();

	void updXML();
	void delXML();

private:
    Ui::XMLServer_IFClass ui;

    XMLServerHandle *handle;
};

#endif // XMLSERVER_IF_H
