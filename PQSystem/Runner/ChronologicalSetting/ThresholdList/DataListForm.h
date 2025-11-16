#ifndef DATALISTFORM_H
#define DATALISTFORM_H

#include <QWidget>

namespace Ui {
class DataListForm;
}

class DataListForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit DataListForm(QWidget *parent = 0);
    ~DataListForm();
    
private:
    Ui::DataListForm *ui;
};

#endif // DATALISTFORM_H
