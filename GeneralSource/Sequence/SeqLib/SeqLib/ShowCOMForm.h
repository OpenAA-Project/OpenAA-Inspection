#ifndef SHOWCOMFORM_H
#define SHOWCOMFORM_H

#include <QWidget>

namespace Ui {
class ShowCOMForm;
}

class CommOperand;

class ShowCOMForm : public QWidget
{
    Q_OBJECT

    CommOperand *OpeIndex;
public:
    explicit ShowCOMForm(CommOperand *Ope ,QWidget *parent = nullptr);
    ~ShowCOMForm();

private:
    Ui::ShowCOMForm *ui;
    virtual void closeEvent(QCloseEvent *event)     override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    QString GetBinaryStr(const QByteArray &str);

private slots:
	void	SlotTx(const QByteArray &str);
	void	SlotRx(const QByteArray &str);
};

#endif // SHOWCOMFORM_H
