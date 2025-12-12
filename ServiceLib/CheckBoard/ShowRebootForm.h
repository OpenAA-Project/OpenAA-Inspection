#ifndef SHOWREBOOTFORM_H
#define SHOWREBOOTFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class ShowRebootForm;
}

class ShowRebootForm : public QWidget
{
    Q_OBJECT

    QTimer  TM;
public:
    explicit ShowRebootForm(int ReasonIndex ,QWidget *parent = nullptr);
    ~ShowRebootForm();

private slots:
    void OnTimerTicked();

signals:
	void    SignalTimeUp();
private:
    Ui::ShowRebootForm *ui;
};

#endif // SHOWREBOOTFORM_H
