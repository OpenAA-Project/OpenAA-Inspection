#ifndef INPUTMIRROR_H
#define INPUTMIRROR_H

#include <QDialog>
#include "XDisplayImage.h"
#include "XDataAlgorithm.h"

namespace Ui {
class InputMirror;
}

class	LayersBase;

class InputMirror : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputMirror(LayersBase *Base,QWidget *parent = 0);
    ~InputMirror();

    AlgorithmItemRoot::_MirrorMode	MirrorMode;
    
private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonYMirror_clicked();
    void on_pushButtonXMirror_clicked();

private:
    Ui::InputMirror *ui;
};

#endif // INPUTMIRROR_H
