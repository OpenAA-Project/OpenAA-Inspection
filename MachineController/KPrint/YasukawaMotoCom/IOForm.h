#ifndef IOFORM_H
#define IOFORM_H

#include <QWidget>
#include <QLocalServer>

namespace Ui {
class IOForm;
}
class YasukawaMotoCom;
class IOForm : public QWidget
{
    Q_OBJECT

    YasukawaMotoCom *Parent;
    QLocalServer    Server;
    QLocalSocket    *Socket;
public:
    explicit IOForm(YasukawaMotoCom *P,QWidget *parent = nullptr);
    ~IOForm();

private slots:
    void on_pushButtonWrite_clicked();
    void on_pushButtonRead_clicked();
    void    SlotNewConnection();
    void    SlotReadyRead();

    void on_pushButtonWriteByte_clicked();

    void on_pushButtonReadByte_clicked();

private:
    Ui::IOForm *ui;
    void WriteData(int Data[6]);
    void WriteData(unsigned char Data[32]);
};

#endif // IOFORM_H
