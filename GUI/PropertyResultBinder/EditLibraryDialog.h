#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditLibraryDialog;
}

class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditLibraryDialog(LayersBase *base, QWidget *parent = 0);
    ~EditLibraryDialog();
    
private:
    Ui::EditLibraryDialog *ui;
};

#endif // EDITLIBRARYDIALOG_H
