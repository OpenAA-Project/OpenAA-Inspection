#ifndef CHECKDLLFORM_H
#define CHECKDLLFORM_H

#include <QWidget>
#include "ui_CheckDLLForm.h"
#include "XServiceForLayers.h"

class	RunnerMap;

class CheckDLLForm : public QWidget ,public ServiceForLayers
{
	Q_OBJECT

	RunnerMap	*EVMap;
public:
	CheckDLLForm(LayersBase *Base,QWidget *parent = 0);
	~CheckDLLForm();

private:
	Ui::CheckDLLFormClass ui;

signals:
	void	SignalClose();

private slots:
	void on_pushButtonOK_clicked();
	void on_listWidgetAlgorithm_clicked(const QModelIndex &);
	void on_listWidgetGUI_clicked(const QModelIndex &);
        void on_listWidgetResultDLL_clicked(const QModelIndex &index);
        void on_listWidgetFilter_clicked(const QModelIndex &index);
        void on_listWidgetCamera_clicked(const QModelIndex &index);
        void on_listWidgetPIO_clicked(const QModelIndex &index);
        void on_listWidgetSequenceDLL_clicked(const QModelIndex &index);
        void on_listWidgetLightDLL_clicked(const QModelIndex &index);
        void on_pushButtonSetting_clicked();
        void on_pushButtonTest_clicked();
        void on_listWidgetExecuteVisualizer_clicked(const QModelIndex &index);
};

#endif // CHECKDLLFORM_H
