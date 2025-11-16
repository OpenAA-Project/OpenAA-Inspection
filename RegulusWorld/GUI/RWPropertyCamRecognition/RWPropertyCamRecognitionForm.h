#ifndef RWPROPERTYCAMRECOGNITIONFORM_H
#define RWPROPERTYCAMRECOGNITIONFORM_H

#include <QWidget>
#include "XGUIFormBase.h"

namespace Ui {
class RWPropertyCamRecognitionForm;
}

class RWPropertyCamRecognitionForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWPropertyCamRecognitionForm(LayersBase *Base,QWidget *parent = nullptr);
    ~RWPropertyCamRecognitionForm();

private:
    Ui::RWPropertyCamRecognitionForm *ui;
};

#endif // RWPROPERTYCAMRECOGNITIONFORM_H
