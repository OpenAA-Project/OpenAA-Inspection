#include "guilistwindow.h"
#include "ui_guilistwindow.h"

GuiListWindow::GuiListWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiListWindow)
{
    ui->setupUi(this);
}

GuiListWindow::~GuiListWindow()
{
    delete ui;
}
