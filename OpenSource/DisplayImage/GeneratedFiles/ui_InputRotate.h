/********************************************************************************
** Form generated from reading UI file 'InputRotate.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTROTATE_H
#define UI_INPUTROTATE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_InputRotate
{
public:
    QPushButton *pushButtonSetDegree;
    QPushButton *pushButton180Degree;
    QPushButton *pushButtonCancel;
    QPushButton *pushButton270Degree;
    QPushButton *pushButton90Degree;
    QSpinBox *spinBoxAngle;

    void setupUi(QDialog *InputRotate)
    {
        if (InputRotate->objectName().isEmpty())
            InputRotate->setObjectName("InputRotate");
        InputRotate->resize(249, 123);
        pushButtonSetDegree = new QPushButton(InputRotate);
        pushButtonSetDegree->setObjectName("pushButtonSetDegree");
        pushButtonSetDegree->setGeometry(QRect(10, 60, 121, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSetDegree->setIcon(icon);
        pushButton180Degree = new QPushButton(InputRotate);
        pushButton180Degree->setObjectName("pushButton180Degree");
        pushButton180Degree->setGeometry(QRect(140, 30, 101, 23));
        pushButtonCancel = new QPushButton(InputRotate);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 82, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon1);
        pushButton270Degree = new QPushButton(InputRotate);
        pushButton270Degree->setObjectName("pushButton270Degree");
        pushButton270Degree->setGeometry(QRect(140, 50, 101, 23));
        pushButton90Degree = new QPushButton(InputRotate);
        pushButton90Degree->setObjectName("pushButton90Degree");
        pushButton90Degree->setGeometry(QRect(140, 10, 101, 23));
        spinBoxAngle = new QSpinBox(InputRotate);
        spinBoxAngle->setObjectName("spinBoxAngle");
        spinBoxAngle->setGeometry(QRect(10, 30, 91, 22));

        retranslateUi(InputRotate);

        pushButtonCancel->setDefault(true);


        QMetaObject::connectSlotsByName(InputRotate);
    } // setupUi

    void retranslateUi(QDialog *InputRotate)
    {
        InputRotate->setWindowTitle(QCoreApplication::translate("InputRotate", "Dialog", nullptr));
        pushButtonSetDegree->setText(QCoreApplication::translate("InputRotate", "Set Degree", nullptr));
        pushButton180Degree->setText(QCoreApplication::translate("InputRotate", "180 degree", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("InputRotate", "Cancel", nullptr));
        pushButton270Degree->setText(QCoreApplication::translate("InputRotate", "270 degree", nullptr));
        pushButton90Degree->setText(QCoreApplication::translate("InputRotate", "90 degree", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputRotate: public Ui_InputRotate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTROTATE_H
