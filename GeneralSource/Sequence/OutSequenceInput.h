#ifndef OUTSEQUENCEINPUT_H
#define OUTSEQUENCEINPUT_H

#include <QWidget>
#include <QString>
#include <QShowEvent>
#include <QCloseEvent>

namespace Ui {
class OutSequenceInput;
}
class	SeqControl;
class	ThreadSequence;

class OutSequenceInput : public QWidget
{
    Q_OBJECT
    
public:
    explicit OutSequenceInput(SeqControl *seq ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~OutSequenceInput();

    volatile    bool    OnAwake;
    bool        OKMode;
    QString		MessageData;
    QString		DefaultString;
    QString		Ret;
    void	ShowMessage(QString &msg ,QString &defaultstring);

    virtual void showEvent ( QShowEvent * event )	override;
    virtual void closeEvent ( QCloseEvent * e )		override;
    ThreadSequence  *SeqParent;

private slots:
    void on_YesButton_clicked();
    void on_NoButton_clicked();

private:
    Ui::OutSequenceInput *ui;
};

#endif // OUTSEQUENCEINPUT_H
