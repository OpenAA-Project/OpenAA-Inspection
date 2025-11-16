#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectLibraryDialog;
}
class ConfirmForm;

class SelectLibraryDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

	ConfirmForm *Parent;
	AlgorithmLibraryListContainer	List;
public:
    explicit SelectLibraryDialog(LayersBase *base, ConfirmForm *p, QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	void	Initial(AlgorithmLibraryListContainer &src);

	AlgorithmLibraryList	*Selected;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonCancel_clicked();
    void on_toolButtonSelect_clicked();

private:
    Ui::SelectLibraryDialog *ui;
};

#endif // SELECTLIBRARYDIALOG_H
