#ifndef SUBTRACTLIBIDDIALOG_H
#define SUBTRACTLIBIDDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SubtractLibIDDialog;
}
class   LibFolderForm;

class SubtractLibIDDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SubtractLibIDDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~SubtractLibIDDialog();

    AlgorithmLibraryListContainer	SelectedList;
    void	SetSelected(AlgorithmLibraryListContainer &selectedList);

    void	ShowFolder(int LibType);
    void	ShowSelectedList(void);
private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSend_clicked();
    void on_pushButtonBack_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index);

private:
    Ui::SubtractLibIDDialog *ui;

    LibFolderForm					*pLibFolderForm;
    int                             LibType;
    int								LibFolderID;
    AlgorithmLibraryListContainer	LibIDList;
};

#endif // SUBTRACTLIBIDDIALOG_H
