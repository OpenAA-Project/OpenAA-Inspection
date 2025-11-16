#ifndef RWDEV3DMOUSEFORM_H
#define RWDEV3DMOUSEFORM_H

#include <QWidget>

namespace Ui {
class RWDev3DMouseForm;
}

class RWDev3DMouse;

class RWDev3DMouseForm : public QWidget
{
    Q_OBJECT

    RWDev3DMouse    *Parent;
public:
    explicit RWDev3DMouseForm(RWDev3DMouse *p,QWidget *parent = nullptr);
    ~RWDev3DMouseForm();

private:
    Ui::RWDev3DMouseForm *ui;
};

#endif // RWDEV3DMOUSEFORM_H
