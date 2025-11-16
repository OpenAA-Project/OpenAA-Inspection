/********************************************************************************
** Form generated from reading UI file 'WindUpImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDUPIMAGEFORM_H
#define UI_WINDUPIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_WindUpImageForm
{
public:
    QPushButton *pushButtonExecuteWindup;
    QLabel *label;
    QSpinBox *spinBoxShiftDown;
    QSpinBox *spinBoxWindUp;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxBrightness;

    void setupUi(GUIFormBase *WindUpImageForm)
    {
        if (WindUpImageForm->objectName().isEmpty())
            WindUpImageForm->setObjectName("WindUpImageForm");
        WindUpImageForm->resize(366, 102);
        pushButtonExecuteWindup = new QPushButton(WindUpImageForm);
        pushButtonExecuteWindup->setObjectName("pushButtonExecuteWindup");
        pushButtonExecuteWindup->setGeometry(QRect(230, 30, 121, 51));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Start.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonExecuteWindup->setIcon(icon);
        label = new QLabel(WindUpImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 121, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter);
        spinBoxShiftDown = new QSpinBox(WindUpImageForm);
        spinBoxShiftDown->setObjectName("spinBoxShiftDown");
        spinBoxShiftDown->setGeometry(QRect(140, 10, 71, 21));
        spinBoxShiftDown->setMinimum(-99999999);
        spinBoxShiftDown->setMaximum(99999999);
        spinBoxWindUp = new QSpinBox(WindUpImageForm);
        spinBoxWindUp->setObjectName("spinBoxWindUp");
        spinBoxWindUp->setGeometry(QRect(140, 40, 71, 21));
        spinBoxWindUp->setMaximum(99999999);
        label_2 = new QLabel(WindUpImageForm);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 121, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(WindUpImageForm);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 121, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        spinBoxBrightness = new QSpinBox(WindUpImageForm);
        spinBoxBrightness->setObjectName("spinBoxBrightness");
        spinBoxBrightness->setGeometry(QRect(140, 70, 71, 21));
        spinBoxBrightness->setMaximum(255);

        retranslateUi(WindUpImageForm);

        QMetaObject::connectSlotsByName(WindUpImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *WindUpImageForm)
    {
        WindUpImageForm->setWindowTitle(QCoreApplication::translate("WindUpImageForm", "Wind-up Image", nullptr));
        pushButtonExecuteWindup->setText(QCoreApplication::translate("WindUpImageForm", "Execute wind up", nullptr));
        label->setText(QCoreApplication::translate("WindUpImageForm", "Shift down", nullptr));
        label_2->setText(QCoreApplication::translate("WindUpImageForm", "Wind up length", nullptr));
        label_3->setText(QCoreApplication::translate("WindUpImageForm", "Dummy brightness", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindUpImageForm: public Ui_WindUpImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDUPIMAGEFORM_H
