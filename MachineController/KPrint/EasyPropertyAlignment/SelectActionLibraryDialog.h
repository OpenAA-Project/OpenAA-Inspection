#ifndef SELECTACTIONLIBRARYDIALOG_H
#define SELECTACTIONLIBRARYDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectActionLibraryDialog;
}
class EasyPropertyAlignmentForm;

class SelectActionLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyAlignmentForm   *Parent;
    IntList                         LibTypeList;
    AlgorithmLibraryListContainer   CurrentLibList;
public:
    explicit SelectActionLibraryDialog(LayersBase *base
                                        ,EasyPropertyAlignmentForm *P
                                        ,bool DeleteButton
                                        ,QWidget *parent = nullptr);
    ~SelectActionLibraryDialog();

    AlgorithmLibraryListContainer    Selected;

private slots:
    void on_listWidgetLibType_clicked(const QModelIndex &index);

    void on_toolButtonAddLibrary_clicked();
    void on_toolButtonRemoveLibrary_clicked();
    void on_tableWidgetLibrary_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectActionLibraryDialog *ui;
};

#endif // SELECTACTIONLIBRARYDIALOG_H
