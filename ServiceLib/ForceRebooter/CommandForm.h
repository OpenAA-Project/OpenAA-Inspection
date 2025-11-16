#ifndef COMMANDFORM_H
#define COMMANDFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class CommandForm;
}

class CommandForm : public QWidget
{
    Q_OBJECT

    int     Cmd;
    int     OwnCmd;
    QTimer  TM;

public:
    explicit CommandForm(int cmd ,int OwnCmd,QWidget *parent = 0);
    ~CommandForm();
    
private:
    Ui::CommandForm *ui;

private slots:
    void    SlotTimeOut();
};

#endif // COMMANDFORM_H
