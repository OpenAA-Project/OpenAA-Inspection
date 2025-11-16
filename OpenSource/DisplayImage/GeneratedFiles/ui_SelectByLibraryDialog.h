/********************************************************************************
** Form generated from reading UI file 'SelectByLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTBYLIBRARYDIALOG_H
#define UI_SELECTBYLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectByLibraryDialog
{
public:
    QPushButton *ButtonSelect;
    QPushButton *ButtonCancel;
    QFrame *frameLibrary;

    void setupUi(QDialog *SelectByLibraryDialog)
    {
        if (SelectByLibraryDialog->objectName().isEmpty())
            SelectByLibraryDialog->setObjectName("SelectByLibraryDialog");
        SelectByLibraryDialog->resize(602, 521);
        ButtonSelect = new QPushButton(SelectByLibraryDialog);
        ButtonSelect->setObjectName("ButtonSelect");
        ButtonSelect->setGeometry(QRect(120, 470, 131, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonSelect->setIcon(icon);
        ButtonCancel = new QPushButton(SelectByLibraryDialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(350, 470, 131, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        frameLibrary = new QFrame(SelectByLibraryDialog);
        frameLibrary->setObjectName("frameLibrary");
        frameLibrary->setGeometry(QRect(10, 10, 581, 451));
        frameLibrary->setFrameShape(QFrame::StyledPanel);
        frameLibrary->setFrameShadow(QFrame::Sunken);

        retranslateUi(SelectByLibraryDialog);

        QMetaObject::connectSlotsByName(SelectByLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectByLibraryDialog)
    {
        SelectByLibraryDialog->setWindowTitle(QCoreApplication::translate("SelectByLibraryDialog", "Dialog", nullptr));
        ButtonSelect->setText(QCoreApplication::translate("SelectByLibraryDialog", "Select", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("SelectByLibraryDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectByLibraryDialog: public Ui_SelectByLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTBYLIBRARYDIALOG_H
