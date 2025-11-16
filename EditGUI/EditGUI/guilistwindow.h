#ifndef GUILISTWINDOW_H
#define GUILISTWINDOW_H

#include <QWidget>

namespace Ui {
class GuiListWindow;
}

class GuiListWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit GuiListWindow(QWidget *parent = 0);
    ~GuiListWindow();
    
private:
    Ui::GuiListWindow *ui;
};

#endif // GUILISTWINDOW_H
