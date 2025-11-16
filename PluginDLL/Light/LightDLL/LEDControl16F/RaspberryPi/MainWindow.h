#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>
#include "LightDeviceStruct.h"
#include "NListRPi.h"
#include "DeviceStruct.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void    InitialSignal(void);

private slots:

};
#endif // MAINWINDOW_H
