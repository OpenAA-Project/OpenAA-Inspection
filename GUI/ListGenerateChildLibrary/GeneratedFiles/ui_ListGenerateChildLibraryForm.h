/********************************************************************************
** Form generated from reading UI file 'ListGenerateChildLibraryForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTGENERATECHILDLIBRARYFORM_H
#define UI_LISTGENERATECHILDLIBRARYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ListGenerateChildLibraryForm
{
public:
    QLabel *label;
    QFrame *frameLibFolder;
    QFrame *frame;
    QLabel *label_2;
    QLineEdit *lineEditFolderName;
    QPushButton *pushButtonGenerate;
    QPushButton *pushButtonSelect;

    void setupUi(GUIFormBase *ListGenerateChildLibraryForm)
    {
        if (ListGenerateChildLibraryForm->objectName().isEmpty())
            ListGenerateChildLibraryForm->setObjectName("ListGenerateChildLibraryForm");
        ListGenerateChildLibraryForm->resize(263, 300);
        label = new QLabel(ListGenerateChildLibraryForm);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 261, 18));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        frameLibFolder = new QFrame(ListGenerateChildLibraryForm);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(0, 20, 261, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(ListGenerateChildLibraryForm);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 220, 261, 78));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 261, 18));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        lineEditFolderName = new QLineEdit(frame);
        lineEditFolderName->setObjectName("lineEditFolderName");
        lineEditFolderName->setGeometry(QRect(0, 20, 261, 24));
        pushButtonGenerate = new QPushButton(frame);
        pushButtonGenerate->setObjectName("pushButtonGenerate");
        pushButtonGenerate->setGeometry(QRect(0, 44, 91, 34));
        pushButtonSelect = new QPushButton(frame);
        pushButtonSelect->setObjectName("pushButtonSelect");
        pushButtonSelect->setGeometry(QRect(170, 44, 91, 34));

        retranslateUi(ListGenerateChildLibraryForm);

        QMetaObject::connectSlotsByName(ListGenerateChildLibraryForm);
    } // setupUi

    void retranslateUi(GUIFormBase *ListGenerateChildLibraryForm)
    {
        ListGenerateChildLibraryForm->setWindowTitle(QCoreApplication::translate("ListGenerateChildLibraryForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ListGenerateChildLibraryForm", "\343\202\263\343\203\224\343\203\274\345\205\203\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\225\343\202\251\343\203\253\343\203\200", nullptr));
        label_2->setText(QCoreApplication::translate("ListGenerateChildLibraryForm", "\344\273\212\345\233\236\344\275\234\346\210\220\343\201\231\343\202\213\343\203\225\343\202\251\343\203\253\343\203\200", nullptr));
        pushButtonGenerate->setText(QCoreApplication::translate("ListGenerateChildLibraryForm", "\347\224\237\346\210\220", nullptr));
        pushButtonSelect->setText(QCoreApplication::translate("ListGenerateChildLibraryForm", "\351\201\270\346\212\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListGenerateChildLibraryForm: public Ui_ListGenerateChildLibraryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTGENERATECHILDLIBRARYFORM_H
