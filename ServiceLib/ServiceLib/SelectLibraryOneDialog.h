#ifndef SELECTLIBRARYONEDIALOG_H
#define SELECTLIBRARYONEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include <QModelIndex>
#include "XIntClass.h"

namespace Ui {
class SelectLibraryOneDialog;
}

class SelectLibraryOneDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	IntList	LibList;
public:
    explicit SelectLibraryOneDialog(LayersBase *Base,int LibType,const IntList &_LibList ,QWidget *parent = 0);
    ~SelectLibraryOneDialog();

	int	SelectedLibID;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLibraryOneDialog *ui;
};

#endif // SELECTLIBRARYONEDIALOG_H
