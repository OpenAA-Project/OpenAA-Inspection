#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gpiod.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct gpiod_chip *GPIOChip;
    struct gpiod_line *SPICS;
    struct gpiod_line *GIO27;
    int     SPIHandle;
    uint8_t SPIBits;
    uint32_t SPISpeed;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int     Initial(void);
    bool    SetSPiCS(int d);

private slots:
    void on_toolButtonLightA_clicked();
    void on_toolButtonLightB_clicked();
    void on_pushButtonReflectLight_clicked();
    void on_pushButtonReflectIO_clicked();

private:
    Ui::MainWindow *ui;

    bool    CommToSendLightInfo(void);
    bool    CommToSendGIOInfo(void);
};
#endif // MAINWINDOW_H
