#ifndef EDITSTATUSDIALOG_H
#define EDITSTATUSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditStatusDialog;
}

class EditStatusDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
    QWidget *Control;
public:
	QString	GUIRoot;
	QString	GUIName;
	QString	GUIInst;
	QStringList	ObjectPath;
	bool	HTMLMode;
    bool	HTMLModeToopTip;

	explicit EditStatusDialog(LayersBase *base ,QWidget *Ctrl,QWidget *parent = 0);
    ~EditStatusDialog();
    
private slots:
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonLoadHTML_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonLoadToolTipHTML_clicked();
    void on_pushButtonToolTipClear_clicked();
    void on_checkBoxEnableToolTip_clicked();

private:
    Ui::EditStatusDialog *ui;

	virtual	void	showEvent ( QShowEvent * event )		override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // EDITSTATUSDIALOG_H
