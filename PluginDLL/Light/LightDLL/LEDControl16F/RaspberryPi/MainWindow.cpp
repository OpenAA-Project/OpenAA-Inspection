#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ControlFIOForm.h"
#include "ControlLightFForm.h"
#include <wiringPi.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitialSignal();

    ControlFIOForm  *FIO=new ControlFIOForm();
    FIO->show();
    ControlLightFForm   *Light=new ControlLightFForm();
    Light->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void    MainWindow::InitialSignal(void)
{
    if (wiringPiSetupGpio() < 0) {
        printf("GPIO ERROR\n");
        return;
    }
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(16,OUTPUT);
    pinMode(17,OUTPUT);


    pinMode(22,INPUT);
    pinMode(23,INPUT);
    pinMode(24,INPUT);
    pinMode(25,INPUT);
    pinMode(27,OUTPUT);

    pullUpDnControl(22,PUD_DOWN);
    pullUpDnControl(23,PUD_DOWN);
    pullUpDnControl(24,PUD_DOWN);
    pullUpDnControl(25,PUD_DOWN);

    digitalWrite(2 , 0);
    digitalWrite(3 , 0);
    digitalWrite(4 , 0);
    digitalWrite(5 , 0);
    digitalWrite(6 , 0);
    digitalWrite(7 , 0);
    digitalWrite(8 , 0);
    digitalWrite(9 , 0);
    digitalWrite(11, 0);
    digitalWrite(12, 0);
    digitalWrite(13, 0);
    digitalWrite(14, 0);
    digitalWrite(15, 0);
    digitalWrite(16, 0);
    digitalWrite(17, 0);


    digitalWrite(27, 1);

    digitalWrite(21, 1);
    delay(1000);
    digitalWrite(21, 0);

    digitalWrite(10, 1);    //Reset
    delay(1000);
    digitalWrite(10, 0);    //Reset Off
}
