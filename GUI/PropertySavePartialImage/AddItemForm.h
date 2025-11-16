#ifndef ADDITEMFORM_H
#define ADDITEMFORM_H

#include <QWidget>

namespace Ui {
class AddItemForm;
}

class AddItemForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddItemForm(QWidget *parent = 0);
    ~AddItemForm();
    
private:
    Ui::AddItemForm *ui;
};

#endif // ADDITEMFORM_H
