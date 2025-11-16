#ifndef POSITIONIMAGEFORM_H
#define POSITIONIMAGEFORM_H

#include <QWidget>

namespace Ui {
class PositionImageForm;
}

class PositionImageForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PositionImageForm(QWidget *parent = 0);
    ~PositionImageForm();
    
private:
    Ui::PositionImageForm *ui;
};

#endif // POSITIONIMAGEFORM_H
