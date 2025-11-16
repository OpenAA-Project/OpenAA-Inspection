/********************************************************************************
** Form generated from reading UI file 'LibFolderForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIBFOLDERFORM_H
#define UI_LIBFOLDERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LibFolderForm
{
public:
    QLabel *SelectedFolderName;
    QPushButton *pushButtonUpdate;
    QLabel *labelFolder;

    void setupUi(QWidget *LibFolderForm)
    {
        if (LibFolderForm->objectName().isEmpty())
            LibFolderForm->setObjectName("LibFolderForm");
        LibFolderForm->resize(351, 162);
        SelectedFolderName = new QLabel(LibFolderForm);
        SelectedFolderName->setObjectName("SelectedFolderName");
        SelectedFolderName->setGeometry(QRect(0, 140, 221, 20));
        SelectedFolderName->setFrameShape(QFrame::Panel);
        SelectedFolderName->setFrameShadow(QFrame::Sunken);
        pushButtonUpdate = new QPushButton(LibFolderForm);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(254, 140, 91, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonUpdate->setIcon(icon);
        labelFolder = new QLabel(LibFolderForm);
        labelFolder->setObjectName("labelFolder");
        labelFolder->setGeometry(QRect(0, 0, 351, 20));
        labelFolder->setFrameShape(QFrame::Panel);
        labelFolder->setFrameShadow(QFrame::Sunken);

        retranslateUi(LibFolderForm);

        QMetaObject::connectSlotsByName(LibFolderForm);
    } // setupUi

    void retranslateUi(QWidget *LibFolderForm)
    {
        LibFolderForm->setWindowTitle(QCoreApplication::translate("LibFolderForm", "Form", nullptr));
        SelectedFolderName->setText(QCoreApplication::translate("LibFolderForm", "FolderName", nullptr));
        pushButtonUpdate->setText(QCoreApplication::translate("LibFolderForm", "Update", nullptr));
        labelFolder->setText(QCoreApplication::translate("LibFolderForm", "Saved folder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LibFolderForm: public Ui_LibFolderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIBFOLDERFORM_H
