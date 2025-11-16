#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PQSystemExecutor.h"
#include "XPQRunnerController.h"
#include "XServiceForLayers.h"
#include <QToolButton>

class PQSystemExecutor;

class MenuButton : public QToolButton ,public NPList<MenuButton>
{
	Q_OBJECT
	PQSystemExecutor	*Parent;
public:
	QString	TabName;
	QString	ButtonName;
	PQRunnerController	*Controller;

	MenuButton(PQSystemExecutor *p);
	~MenuButton(){}

private slots:
	void	SlotClicked();
};

class PQSystemExecutor : public QMainWindow,public ServiceForLayers
{
    Q_OBJECT

	PQRunnerControllerContainer	Runners;

	NPListPack<MenuButton>	Tabs[100];
	int						TabCount;
	PQSystemRunner			*CurrentRunner;
public:
    PQSystemExecutor(LayersBase *base,QWidget *parent = Q_NULLPTR);

	bool	LoadDLL(const QString &DLLPath);
	void	ShowController(PQRunnerController *Controller);

protected:
	virtual	void resizeEvent(QResizeEvent *event) override;

private:
    Ui::PQSystemExecutorClass ui;
};
