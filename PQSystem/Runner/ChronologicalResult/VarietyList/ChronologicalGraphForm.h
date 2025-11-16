#ifndef CHRONOLOGICALGRAPHFORM_H
#define CHRONOLOGICALGRAPHFORM_H

#include <QWidget>

namespace Ui {
class ChronologicalGraphForm;
}

class ChronologicalGraphForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChronologicalGraphForm(QWidget *parent = 0);
    ~ChronologicalGraphForm();
    
private slots:
    void on_comboBoxTimeSpan_currentIndexChanged(int index);

private:
    Ui::ChronologicalGraphForm *ui;
};

#endif // CHRONOLOGICALGRAPHFORM_H
