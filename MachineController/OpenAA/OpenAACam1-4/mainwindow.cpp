#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QThread>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int    MainWindow::Initial(void)
{
    /*
    if (wiringPiSetupGpio() < 0) {
       printf("GPIO ERROR\n");
       return;
    }

    SPIChannel  =0;
    int SPISpeed    = 2000000;
    if(wiringPiSPISetup (SPIChannel, SPISpeed)<0){
        QMessageBox::critical(NULL,"SPI error","Error : wiringPiSPISetup");
        return;
    }
    */

    const char *device = "/dev/spidev0.0";  // SPI0, CS0
    SPIHandle = open(device, O_RDWR);
    if (SPIHandle < 0) {
        perror("SPI device open failed");
        return 1;
    }

    uint8_t mode = SPI_MODE_0;
    SPIBits = 8;
    SPISpeed = 100000; // 500kHz

    if (ioctl(SPIHandle, SPI_IOC_WR_MODE, &mode) == -1) {
        perror("Can't set SPI mode");
        return 1;
    }

    if (ioctl(SPIHandle, SPI_IOC_WR_BITS_PER_WORD, &SPIBits) == -1) {
        perror("Can't set bits per word");
        return 1;
    }

    if (ioctl(SPIHandle, SPI_IOC_WR_MAX_SPEED_HZ, &SPISpeed) == -1) {
        perror("Can't set max speed");
        return 1;
    }


    const char *chipname = "gpiochip4";
    unsigned int line_num = 8;
    int value = 1;

    GPIOChip = gpiod_chip_open_by_name(chipname);
    if (!GPIOChip) {
        perror("gpiod_chip_open_by_name");
        exit(EXIT_FAILURE);
    }

    /*
    SPICS = gpiod_chip_get_line(GPIOChip, line_num);
    if (!SPICS) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(GPIOChip);
        return -1;
    }
    if (gpiod_line_request_output(SPICS, "libgpiod-output", 0) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(GPIOChip);
        return false;
    }
    */

    GIO27= gpiod_chip_get_line(GPIOChip, 27);
    if (!GIO27) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(GPIOChip);
        return -1;
    }
    if (gpiod_line_request_output(GIO27, "libgpiod-output", 1) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(GPIOChip);
        return false;
    }
    gpiod_line_set_value(GIO27, 0);
    gpiod_line_set_value(GIO27, 1);


    SetSPiCS(0);
    SetSPiCS(1);

    SetSPiCS(value);



    return 0;
}

bool    MainWindow::SetSPiCS(int d)
{
    /*
    if (gpiod_line_set_value(SPICS, d) < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(GPIOChip);
        return false;
    }
    */
    return true;
}


bool MainWindow::CommToSendLightInfo(void)
{
    SetSPiCS(0);

    int LightA=ui->spinBoxLightA->value();
    int LightB=ui->spinBoxLightB->value();

    if(ui->toolButtonLightA->isChecked()==false)
        LightA=0;
    if(ui->toolButtonLightB->isChecked()==false)
        LightB=0;

    uint8_t tx[] = { 0x1E ,5 ,1 ,0,0,0,0,0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = sizeof(tx),
        .delay_usecs = 0,
        .speed_hz = SPISpeed,
        .bits_per_word = SPIBits,
    };

    tx[3]=LightA;
    tx[4]=LightA>>8;
    tx[5]=LightB;
    tx[6]=LightB>>8;

    uint8_t CheckSum=0;
    for(int i=2;i<sizeof(tx)-1;i++){
        CheckSum+=tx[i];
    }
    tx[sizeof(tx)-1]=CheckSum;

    if (ioctl(SPIHandle, SPI_IOC_MESSAGE(1), &tr) < 1) {
        perror("SPI transfer failed");
        SetSPiCS(1);
        return false;
    }
    SetSPiCS(1);
    return true;
}

bool MainWindow::CommToSendGIOInfo(void)
{
    SetSPiCS(0);

    int GOut=    ((ui->checkBoxOut0->isChecked()==true)?0x01:0)
                +((ui->checkBoxOut1->isChecked()==true)?0x02:0)
                +((ui->checkBoxOut2->isChecked()==true)?0x04:0)
                +((ui->checkBoxOut3->isChecked()==true)?0x08:0);

    uint8_t tx[] = { 0x1E ,2 ,2 ,0,0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = sizeof(tx),
        .delay_usecs = 0,
        .speed_hz = SPISpeed,
        .bits_per_word = SPIBits,
    };

    tx[3]=GOut;

    uint8_t CheckSum=0;
    for(int i=2;i<sizeof(tx)-1;i++){
        CheckSum+=tx[i];
    }
    tx[sizeof(tx)-1]=CheckSum;

    if (ioctl(SPIHandle, SPI_IOC_MESSAGE(1), &tr) < 1) {
        perror("SPI transfer failed");
        SetSPiCS(1);
        return false;
    }
    SetSPiCS(1);

    if(rx[0]==0x1B & rx[1]==1 && rx[2]==0x80){
        int GIN=rx[3];
        if((GIN&0x01)!=0)
            ui->checkBoxIn0->setChecked(true);
        else
            ui->checkBoxIn0->setChecked(false);

        if((GIN&0x02)!=0)
            ui->checkBoxIn1->setChecked(true);
        else
            ui->checkBoxIn1->setChecked(false);

        if((GIN&0x04)!=0)
            ui->checkBoxIn2->setChecked(true);
        else
            ui->checkBoxIn2->setChecked(false);

        if((GIN&0x08)!=0)
            ui->checkBoxIn3->setChecked(true);
        else
            ui->checkBoxIn3->setChecked(false);
    }
    return true;
}

void MainWindow::on_toolButtonLightA_clicked()
{

}


void MainWindow::on_toolButtonLightB_clicked()
{

}


void MainWindow::on_pushButtonReflectLight_clicked()
{
    CommToSendLightInfo();
}


void MainWindow::on_pushButtonReflectIO_clicked()
{
    CommToSendGIOInfo();
}

