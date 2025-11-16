#ifndef EACHTHRESHOLDSCRATCHFORM_H
#define EACHTHRESHOLDSCRATCHFORM_H

#include <QWidget>

namespace Ui {
class EachThresholdScratchForm;
}

class EachThresholdScratchForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit EachThresholdScratchForm(QWidget *parent = 0);
    ~EachThresholdScratchForm();
    
private:
    Ui::EachThresholdScratchForm *ui;
};

#endif // EACHTHRESHOLDSCRATCHFORM_H
