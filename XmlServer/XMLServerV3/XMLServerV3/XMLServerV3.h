#ifndef XMLSERVERV3_H
#define XMLSERVERV3_H

#include <QMainWindow>
#include "ui_XMLServerV3.h"
#include "XCommandServer.h"
#include "XNamedPipe.h"
#include <QSystemTrayIcon>

class	SettingParamForm;
class QMenu;
class QAction;

class XMLServerV3 : public QMainWindow
{
	Q_OBJECT

	QString			UserPath;
	XMLServerComm	SMain;
	SettingParamForm	*SettingForm;
	WatchdogInProgram	WDog;

    QAction			*restoreAction;
    QAction			*quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu			*trayIconMenu;
public:
	XMLServerV3(const QString &UserPath,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~XMLServerV3();

	QString	GetUserPath(void)	{	return UserPath;	}
protected:
	virtual	void showEvent ( QShowEvent * event )	override;
	virtual	void closeEvent(QCloseEvent *event)		override;
private:
	Ui::XMLServerV3Class ui;

	void	SlotShowClientinside(int id);
	void	ShowTable(void);

private slots:
	void	SlotShowClient(int id);
	void	SlotAnalize(QDateTime tm , int ClientID, int OpeHandleCode, QString Command,int milisec);

	void	slotSetting();
	void	SlotProgress();
	void	slotWriteOut();
    void	on_checkBoxShowAll_clicked();
    void	on_tableWidgetTable_doubleClicked(const QModelIndex &index);
	void	iconActivated(QSystemTrayIcon::ActivationReason reason);
	void	messageClicked();
};

#endif // XMLSERVERV3_H
