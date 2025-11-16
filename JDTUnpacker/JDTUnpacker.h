#ifndef JDTUNPACKER_H
#define JDTUNPACKER_H

#include <QDialog>
#include <QEvent>
#include "ui_jdtunpacker.h"

class JDTUnpacker : public QDialog
{
	Q_OBJECT

public:
	JDTUnpacker(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~JDTUnpacker();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);

private:
	void setEnableInput(bool b);
	QString unpack(void);	//return path

private slots:
	void slotClickUnpack();
	void fileopen(void);


private:
	Ui::JDTUnpackerClass ui;
};

#endif // JDTUNPACKER_H
