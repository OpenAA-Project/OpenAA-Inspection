#ifndef INTEGRATIONSAVEMASTERFORM_H
#define INTEGRATIONSAVEMASTERFORM_H

#include <QWidget>

namespace Ui {
class IntegrationSaveMasterForm;
}

class IntegrationSaveMasterForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit IntegrationSaveMasterForm(QWidget *parent = 0);
    ~IntegrationSaveMasterForm();
    
private:
    Ui::IntegrationSaveMasterForm *ui;
};

#endif // INTEGRATIONSAVEMASTERFORM_H
