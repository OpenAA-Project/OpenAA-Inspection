/********************************************************************************
** Form generated from reading UI file 'EditOutlineOffset.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOUTLINEOFFSET_H
#define UI_EDITOUTLINEOFFSET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditOutlineOffset
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QFrame *frameGrid;

    void setupUi(QWidget *EditOutlineOffset)
    {
        if (EditOutlineOffset->objectName().isEmpty())
            EditOutlineOffset->setObjectName("EditOutlineOffset");
        EditOutlineOffset->resize(415, 274);
        frame = new QFrame(EditOutlineOffset);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 230, 411, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(280, 0, 91, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        frameGrid = new QFrame(EditOutlineOffset);
        frameGrid->setObjectName("frameGrid");
        frameGrid->setGeometry(QRect(10, 10, 401, 211));
        frameGrid->setFrameShape(QFrame::StyledPanel);
        frameGrid->setFrameShadow(QFrame::Raised);

        retranslateUi(EditOutlineOffset);

        QMetaObject::connectSlotsByName(EditOutlineOffset);
    } // setupUi

    void retranslateUi(QWidget *EditOutlineOffset)
    {
        EditOutlineOffset->setWindowTitle(QCoreApplication::translate("EditOutlineOffset", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("EditOutlineOffset", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOutlineOffset: public Ui_EditOutlineOffset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOUTLINEOFFSET_H
