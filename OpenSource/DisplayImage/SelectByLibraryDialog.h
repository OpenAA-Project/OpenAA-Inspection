#ifndef SELECTBYLIBRARYDIALOG_H
#define SELECTBYLIBRARYDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "SelectLibrariesForm.h"

namespace Ui {
class SelectByLibraryDialog;
}

class SelectByLibraryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectByLibraryDialog(int libType ,LayersBase *Base,QWidget *parent = 0);
    ~SelectByLibraryDialog();

    SelectLibrariesForm		Libs;

private slots:
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectByLibraryDialog *ui;
};

#endif // SELECTBYLIBRARYDIALOG_H
