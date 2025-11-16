#ifndef SHOWSTATUSCOMMENT_H
#define SHOWSTATUSCOMMENT_H

#include <QMainWindow>
#include "ui_ShowStatusComment.h"
#include <QLocalSocket>
#include <QTimer>

class ShowStatusComment : public QMainWindow 
{
	Q_OBJECT

	QLocalSocket	*Sock;
	QTimer	TM;
	bool	ConnectedOnce;
public:
	ShowStatusComment(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ShowStatusComment();

private:
	Ui::ShowStatusCommentClass ui;

	virtual	void resizeEvent ( QResizeEvent * event )	override;
	virtual	void closeEvent ( QCloseEvent * event )		override;
	virtual	void showEvent ( QShowEvent * event )		override;

	QString	GetPositionFileName(void)	{	return /**/"ShowStatusComment.dat";	}
	void	OutputPosition(void);
private slots:
	void	SlotDisconnected();
	void	SlotReadyRead() ;
	void	SlotTimeOut();
};

#endif // SHOWSTATUSCOMMENT_H
