#ifndef ADDROUTEDIALOG_H
#define ADDROUTEDIALOG_H

#include <QDialog>
#include "XDFSProvider.h"

namespace Ui {
class AddRouteDialog;
}

class AddRouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRouteDialog(QWidget *parent = 0);
    ~AddRouteDialog();

	void	Initial(PathClass &d);

	QString	Path;
	int		Priority;
	QString	NetworkPath;
	QString	DFSFilterDLLFileName;
	QString	DFSFilterParameter;

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSearchDLL_clicked();

private:
    Ui::AddRouteDialog *ui;
};

#endif // ADDROUTEDIALOG_H
