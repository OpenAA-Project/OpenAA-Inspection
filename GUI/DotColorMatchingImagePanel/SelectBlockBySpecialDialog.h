#ifndef SELECTBLOCKBYSPECIALDIALOG_H
#define SELECTBLOCKBYSPECIALDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "SelectLibrariesForm.h"

namespace Ui {
class SelectBlockBySpecialDialog;
}

class	DotColorMatchingImagePanel;

class SelectBlockBySpecialDialog : public QDialog
{
    Q_OBJECT

    DotColorMatchingImagePanel  *Parent;
public:
    SelectLibrariesForm		Libs;
public:
    explicit SelectBlockBySpecialDialog(DotColorMatchingImagePanel *p,int libType ,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectBlockBySpecialDialog();

    bool    OutlineMode;
private slots:
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectBlockBySpecialDialog *ui;
};

#endif // SELECTBLOCKBYSPECIALDIALOG_H
