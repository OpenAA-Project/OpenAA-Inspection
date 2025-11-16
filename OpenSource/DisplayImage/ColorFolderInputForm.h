#ifndef COLORFOLDERINPUTFORM_H
#define COLORFOLDERINPUTFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ColorFolderInputForm;
}

class ColorFolderInputForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    QString	FolderName;

    explicit ColorFolderInputForm(LayersBase *base,const QString &folderName ,QWidget *parent = 0);
    ~ColorFolderInputForm();


private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ColorFolderInputForm *ui;

    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // COLORFOLDERINPUTFORM_H
