/********************************************************************************
** Form generated from reading UI file 'PropertyMakeAverageImageForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYMAKEAVERAGEIMAGEFORM_H
#define UI_PROPERTYMAKEAVERAGEIMAGEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyMakeAverageImageForm
{
public:
    QToolButton *toolButtonDrawPartialArea;
    QFrame *frame;
    QToolButton *toolButtonDrawImage;
    QToolButton *toolButtonDrawDarkImage;
    QToolButton *toolButtonDrawLightImage;
    QToolButton *toolButtonDrawAverageImage;
    QToolButton *toolButtonDrawVariableImage;
    QLabel *label_2;
    QSlider *horizontalSliderVariableStrength;
    QPushButton *pushButtonSetAverageToMaster;
    QLabel *label;
    QLineEdit *lineEditAverageCount;
    QPushButton *pushButtonResetAverage;

    void setupUi(GUIFormBase *PropertyMakeAverageImageForm)
    {
        if (PropertyMakeAverageImageForm->objectName().isEmpty())
            PropertyMakeAverageImageForm->setObjectName("PropertyMakeAverageImageForm");
        PropertyMakeAverageImageForm->resize(310, 700);
        toolButtonDrawPartialArea = new QToolButton(PropertyMakeAverageImageForm);
        toolButtonDrawPartialArea->setObjectName("toolButtonDrawPartialArea");
        toolButtonDrawPartialArea->setGeometry(QRect(20, 10, 271, 41));
        toolButtonDrawPartialArea->setCheckable(true);
        frame = new QFrame(PropertyMakeAverageImageForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 60, 291, 291));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        toolButtonDrawImage = new QToolButton(frame);
        toolButtonDrawImage->setObjectName("toolButtonDrawImage");
        toolButtonDrawImage->setGeometry(QRect(10, 10, 271, 41));
        toolButtonDrawImage->setCheckable(true);
        toolButtonDrawImage->setChecked(true);
        toolButtonDrawImage->setAutoExclusive(true);
        toolButtonDrawDarkImage = new QToolButton(frame);
        toolButtonDrawDarkImage->setObjectName("toolButtonDrawDarkImage");
        toolButtonDrawDarkImage->setGeometry(QRect(10, 60, 271, 41));
        toolButtonDrawDarkImage->setCheckable(true);
        toolButtonDrawDarkImage->setAutoExclusive(true);
        toolButtonDrawLightImage = new QToolButton(frame);
        toolButtonDrawLightImage->setObjectName("toolButtonDrawLightImage");
        toolButtonDrawLightImage->setGeometry(QRect(10, 110, 271, 41));
        toolButtonDrawLightImage->setCheckable(true);
        toolButtonDrawLightImage->setAutoExclusive(true);
        toolButtonDrawAverageImage = new QToolButton(frame);
        toolButtonDrawAverageImage->setObjectName("toolButtonDrawAverageImage");
        toolButtonDrawAverageImage->setGeometry(QRect(10, 240, 271, 41));
        toolButtonDrawAverageImage->setCheckable(true);
        toolButtonDrawAverageImage->setAutoExclusive(true);
        toolButtonDrawVariableImage = new QToolButton(frame);
        toolButtonDrawVariableImage->setObjectName("toolButtonDrawVariableImage");
        toolButtonDrawVariableImage->setGeometry(QRect(10, 160, 271, 41));
        toolButtonDrawVariableImage->setCheckable(true);
        toolButtonDrawVariableImage->setAutoExclusive(true);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 200, 71, 21));
        label_2->setAlignment(Qt::AlignCenter);
        horizontalSliderVariableStrength = new QSlider(frame);
        horizontalSliderVariableStrength->setObjectName("horizontalSliderVariableStrength");
        horizontalSliderVariableStrength->setGeometry(QRect(90, 200, 191, 21));
        horizontalSliderVariableStrength->setMinimum(1);
        horizontalSliderVariableStrength->setMaximum(100);
        horizontalSliderVariableStrength->setOrientation(Qt::Horizontal);
        pushButtonSetAverageToMaster = new QPushButton(PropertyMakeAverageImageForm);
        pushButtonSetAverageToMaster->setObjectName("pushButtonSetAverageToMaster");
        pushButtonSetAverageToMaster->setGeometry(QRect(30, 370, 241, 51));
        label = new QLabel(PropertyMakeAverageImageForm);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 430, 121, 21));
        lineEditAverageCount = new QLineEdit(PropertyMakeAverageImageForm);
        lineEditAverageCount->setObjectName("lineEditAverageCount");
        lineEditAverageCount->setGeometry(QRect(160, 430, 113, 24));
        lineEditAverageCount->setReadOnly(true);
        pushButtonResetAverage = new QPushButton(PropertyMakeAverageImageForm);
        pushButtonResetAverage->setObjectName("pushButtonResetAverage");
        pushButtonResetAverage->setGeometry(QRect(30, 470, 241, 51));

        retranslateUi(PropertyMakeAverageImageForm);

        QMetaObject::connectSlotsByName(PropertyMakeAverageImageForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyMakeAverageImageForm)
    {
        PropertyMakeAverageImageForm->setWindowTitle(QCoreApplication::translate("PropertyMakeAverageImageForm", "Form", nullptr));
        toolButtonDrawPartialArea->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Draw partial area", nullptr));
        toolButtonDrawImage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Draw image", nullptr));
        toolButtonDrawDarkImage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Dark image", nullptr));
        toolButtonDrawLightImage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Light image", nullptr));
        toolButtonDrawAverageImage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Average image", nullptr));
        toolButtonDrawVariableImage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Variable image", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "\350\241\250\347\244\272\345\274\267\345\272\246", nullptr));
        pushButtonSetAverageToMaster->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Set average to Master image", nullptr));
        label->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Average count", nullptr));
        pushButtonResetAverage->setText(QCoreApplication::translate("PropertyMakeAverageImageForm", "Reset average", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyMakeAverageImageForm: public Ui_PropertyMakeAverageImageForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYMAKEAVERAGEIMAGEFORM_H
