#ifndef COMMANDFORM_H
#define COMMANDFORM_H

#include <QWidget>

namespace Ui {
class CommandForm;
}

class CommandForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit CommandForm(QWidget *parent = 0);
    ~CommandForm();
    
private:
    Ui::CommandForm *ui;
};

#endif // COMMANDFORM_H
