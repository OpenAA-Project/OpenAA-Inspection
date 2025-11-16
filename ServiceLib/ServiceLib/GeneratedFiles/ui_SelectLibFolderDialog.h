/********************************************************************************
** Form generated from reading UI file 'SelectLibFolderDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTLIBFOLDERDIALOG_H
#define UI_SELECTLIBFOLDERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectLibFolderDialog
{
public:
    QFrame *frameLibFolder;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSelect;

    void setupUi(QDialog *SelectLibFolderDialog)
    {
        if (SelectLibFolderDialog->objectName().isEmpty())
            SelectLibFolderDialog->setObjectName("SelectLibFolderDialog");
        SelectLibFolderDialog->resize(241, 264);
        frameLibFolder = new QFrame(SelectLibFolderDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 221, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        pushButtonCancel = new QPushButton(SelectLibFolderDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(130, 220, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        pushButtonSelect = new QPushButton(SelectLibFolderDialog);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(10, 220, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Select.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSelect->setIcon(icon1);

        retranslateUi(SelectLibFolderDialog);

        QMetaObject::connectSlotsByName(SelectLibFolderDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectLibFolderDialog)
    {
        SelectLibFolderDialog->setWindowTitle(QCoreApplication::translate("SelectLibFolderDialog", "Dialog", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("SelectLibFolderDialog", "Cancel", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("SelectLibFolderDialog", "Select", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectLibFolderDialog: public Ui_SelectLibFolderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTLIBFOLDERDIALOG_H
