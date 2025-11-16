#ifndef SHOWRESULTLISTFORM_H
#define SHOWRESULTLISTFORM_H

#include <QWidget>

namespace Ui {
class ShowResultListForm;
}

class ShowResultListForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShowResultListForm(QWidget *parent = 0);
    ~ShowResultListForm();
    
private:
    Ui::ShowResultListForm *ui;
};

#endif // SHOWRESULTLISTFORM_H
