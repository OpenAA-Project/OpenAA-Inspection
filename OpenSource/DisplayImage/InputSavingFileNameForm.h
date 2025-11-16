#ifndef INPUTSAVINGFILENAMEFORM_H
#define INPUTSAVINGFILENAMEFORM_H

#include <QDialog>

namespace Ui {
class InputSavingFileNameForm;
}
class	LayersBase;

class InputSavingFileNameForm : public QDialog
{
    Q_OBJECT

    QString	PathFileName;
public:
    explicit InputSavingFileNameForm(LayersBase *Base,const QString &filename,QWidget *parent = 0);
    ~InputSavingFileNameForm();

    QString	GetPathFileName(void){	return PathFileName;	}

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputSavingFileNameForm *ui;
};

#endif // INPUTSAVINGFILENAMEFORM_H
