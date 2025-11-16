#ifndef TESTERLIGHTDLL_H
#define TESTERLIGHTDLL_H

#include <QMainWindow>
#include "ui_TesterLightDLL.h"
#include <QTimer>
#include <QMutex>
#include "XServiceForLayers.h"

class TesterLightDLL : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QTimer	IdleTimer;
	QMutex	MutexTimerFunc;
public:
	TesterLightDLL(LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TesterLightDLL();
	
	virtual	void	closeEvent(QCloseEvent *event)	override;
private slots:
    void    on_pushButtonLoadDLL_clicked();
    void    on_toolButtonOnOff_clicked();
    void    on_pushButtonSetting_clicked();
    void    on_pushButtonSaveToDefault_clicked();
    void on_pushButtonLoadFromDefault_clicked();
    void on_pushButtonSaveAs_clicked();
    void on_pushButtonLoadAs_clicked();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
protected slots:
	void	TimeOutForIdle(void);

private:
	Ui::TesterLightDLLClass ui;
};

#endif // TESTERLIGHTDLL_H
