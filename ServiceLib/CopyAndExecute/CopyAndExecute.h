#ifndef COPYANDEXECUTE_H
#define COPYANDEXECUTE_H

#include <QMainWindow>
#include "ui_CopyAndExecute.h"

class CopyAndExecute : public QMainWindow
{
	Q_OBJECT

	QString	SourcePath;
public:
	CopyAndExecute(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CopyAndExecute();

	void	Initial(QString	&SourcePath);
	void	DeleteFiles	(const QString &TargetFile);
	void	CopyFiles	(const QString &SourceFile,const QString &DestinationPath);
private:
	Ui::CopyAndExecuteClass ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // COPYANDEXECUTE_H
