#ifndef SELECTBYLIMITEDDIALOG_H
#define SELECTBYLIMITEDDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectByLimitedDialog;
}
class SelectLibrariesForAnyType;

class SelectByLimitedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectByLimitedDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectByLimitedDialog();

	SelectLibrariesForAnyType		*Libs;
	bool	RetOK;
	void	SetSelected(AlgorithmLibraryListContainer &selectedList);
	AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_ButtonSelectAll_clicked();
    void on_ButtonSelectOneAtLeast_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectByLimitedDialog *ui;
};

#endif // SELECTBYLIMITEDDIALOG_H
