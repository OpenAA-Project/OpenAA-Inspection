#ifndef INPUTROTATE_H
#define INPUTROTATE_H

#include <QDialog>

namespace Ui {
class InputRotate;
}
class	LayersBase;

class InputRotate : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputRotate(LayersBase *Base,QWidget *parent = 0);
    ~InputRotate();

    int	Angle;

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonSetDegree_clicked();
    void on_pushButton90Degree_clicked();
    void on_pushButton180Degree_clicked();
    void on_pushButton270Degree_clicked();

private:
    Ui::InputRotate *ui;
};

#endif // INPUTROTATE_H
