#ifndef LIBFOLDERINPUTFORM_H
#define LIBFOLDERINPUTFORM_H

#include <QDialog>

namespace Ui {
class LibFolderInputForm;
}
class	LayersBase;

class LibFolderInputForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit LibFolderInputForm(LayersBase *lbase ,const QString &folderName ,QWidget *parent = 0);
    ~LibFolderInputForm();

    QString	FolderName;
private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::LibFolderInputForm *ui;
};

#endif // LIBFOLDERINPUTFORM_H
