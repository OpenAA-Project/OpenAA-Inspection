#ifndef HASPVIEWER_H
#define HASPVIEWER_H

#include <QWidget>
#include "ui_Haspviewer.h"
//#include "hasp_hl.h"
#include "hasp_api.h"
#include <QMessageBox>

class HaspViewer : public QWidget
{
	Q_OBJECT

public:
	HaspViewer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~HaspViewer();

	
	void View(void);
	void clearUI(void);
	QString GetID(char *C);
	bool ErrorCheck(const hasp_status_t &status);

	//void Fukugou(QString &str_ID,unsigned char *Data);
	void Fukugou(int ID,QByteArray ReData,QByteArray &fukugou);

	void setDateList(unsigned char *Data,QStringList &DateList);
	void setTypeList(unsigned char *Data,QStringList &TypeList);
	void showCode(const QString &Code,const QString &Date);
	hasp_status_t Login(hasp_handle_t &handle);
private slots:
        void on_pbUpdate_clicked();

        void on_pbEND_clicked();

private:
	Ui::HaspViewerClass ui;

	hasp_handle_t   handle;
	QMessageBox Mbox;
};

#endif // HASPVIEWER_H
