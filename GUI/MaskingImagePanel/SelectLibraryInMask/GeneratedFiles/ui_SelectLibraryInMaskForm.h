/********************************************************************************
** Form generated from reading UI file 'SelectLibraryInMaskForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBRARYINMASKFORM_H
#define UI_SELECTLIBRARYINMASKFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectLibraryInMaskFormClass
{
public:
    QFrame *frameLibrary;
    QFrame *frame;
    QPushButton *ButtonNotEffective;
    QPushButton *ButtonEffective;
    QPushButton *ButtonCancel;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *SelectLibraryInMaskFormClass)
    {
        if (SelectLibraryInMaskFormClass->objectName().isEmpty())
            SelectLibraryInMaskFormClass->setObjectName("SelectLibraryInMaskFormClass");
        SelectLibraryInMaskFormClass->resize(650, 549);
        frameLibrary = new QFrame(SelectLibraryInMaskFormClass);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(0, 0, 651, 461));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(SelectLibraryInMaskFormClass);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 460, 651, 91));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        ButtonNotEffective = new QPushButton(frame);
        ButtonNotEffective->setObjectName("ButtonNotEffective");
        ButtonNotEffective->setGeometry(QRect(360, 50, 151, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/EffectNG.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonNotEffective->setIcon(icon);
        ButtonEffective = new QPushButton(frame);
        ButtonEffective->setObjectName("ButtonEffective");
        ButtonEffective->setGeometry(QRect(360, 10, 151, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Effect.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonEffective->setIcon(icon1);
        ButtonCancel = new QPushButton(frame);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(520, 10, 121, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon2);
        pushButtonDelete = new QPushButton(frame);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(189, 10, 151, 31));

        retranslateUi(SelectLibraryInMaskFormClass);

        QMetaObject::connectSlotsByName(SelectLibraryInMaskFormClass);
    } // setupUi

    void retranslateUi(QWidget *SelectLibraryInMaskFormClass)
    {
        SelectLibraryInMaskFormClass->setWindowTitle(QCoreApplication::translate("SelectLibraryInMaskFormClass", "SelectLibraryInMaskForm", nullptr));
        ButtonNotEffective->setText(QCoreApplication::translate("SelectLibraryInMaskFormClass", "Not Effective", nullptr));
        ButtonEffective->setText(QCoreApplication::translate("SelectLibraryInMaskFormClass", "Effective Mask", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectLibraryInMaskFormClass", "Cancel", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SelectLibraryInMaskFormClass", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibraryInMaskFormClass: public Ui_SelectLibraryInMaskFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBRARYINMASKFORM_H
