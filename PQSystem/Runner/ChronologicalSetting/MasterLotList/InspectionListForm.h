#ifndef INSPECTIONLISTFORM_H
#define INSPECTIONLISTFORM_H

#include <QWidget>

namespace Ui {
class InspectionListForm;
}

class InspectionListForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit InspectionListForm(QWidget *parent = 0);
    ~InspectionListForm();
    
private:
    Ui::InspectionListForm *ui;
};

#endif // INSPECTIONLISTFORM_H
