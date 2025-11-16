#ifndef EDITEXECUTEVISUALIZER_H
#define EDITEXECUTEVISUALIZER_H

#include <QMainWindow>
#include "ui_EditExecuteVisualizer.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"

class	EVDLLListForm;

class EditExecuteVisualizer : public QMainWindow
{
	Q_OBJECT

	RunnerMap	RMap;
	EVDLLListForm	*DLLListForm;

public:
	EditExecuteVisualizer(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditExecuteVisualizer();

private:
	
	virtual void closeEvent ( QCloseEvent * event )	override;


private slots:
        void on_actionLoad_EV_File_triggered();
        void on_actionSave_EV_File_triggered();
        void on_actionExfit_triggered();

	void	SlotLDoubleClick(int x ,int y);

private:
	Ui::EditExecuteVisualizerClass ui;
};

#endif // EDITEXECUTEVISUALIZER_H
