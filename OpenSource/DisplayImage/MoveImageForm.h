#ifndef MOVEIMAGEFORM_H
#define MOVEIMAGEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class MoveImageForm;
}

class MoveImageForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MoveImageForm(LayersBase *Base,QWidget *parent = 0);
    ~MoveImageForm();

    bool	FlagMaster;
    bool	FlagTarget;

    int		XDir,YDir;
    bool	RetMode;

signals:
    void	SignalClose();

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MoveImageForm *ui;
};

#endif // MOVEIMAGEFORM_H
