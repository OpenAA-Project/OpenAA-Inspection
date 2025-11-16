/********************************************************************************
** Form generated from reading UI file 'RegistLearningSelectLibDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTLEARNINGSELECTLIBDIALOG_H
#define UI_REGISTLEARNINGSELECTLIBDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistLearningSelectLibDialog
{
public:
    QFrame *frame_2;
    QPushButton *pushButtonNG;
    QFrame *frame;
    QPushButton *pushButtonOK;
    QFrame *frame_3;
    QPushButton *pushButtonCancel;
    QSlider *horizontalSliderPriority;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QSpinBox *spinBoxPriority;
    QTableWidget *tableWidgetSelectLibrary;

    void setupUi(QDialog *RegistLearningSelectLibDialog)
    {
        if (RegistLearningSelectLibDialog->objectName().isEmpty())
            RegistLearningSelectLibDialog->setObjectName("RegistLearningSelectLibDialog");
        RegistLearningSelectLibDialog->resize(400, 599);
        frame_2 = new QFrame(RegistLearningSelectLibDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(170, 460, 151, 41));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButtonNG = new QPushButton(frame_2);
        pushButtonNG->setObjectName("pushButtonNG");
        pushButtonNG->setGeometry(QRect(0, 0, 151, 34));
        frame = new QFrame(RegistLearningSelectLibDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 460, 151, 41));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButtonOK = new QPushButton(frame);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(0, 0, 151, 34));
        frame_3 = new QFrame(RegistLearningSelectLibDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(0, 510, 391, 91));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        pushButtonCancel = new QPushButton(frame_3);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(140, 50, 111, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        horizontalSliderPriority = new QSlider(frame_3);
        horizontalSliderPriority->setObjectName("horizontalSliderPriority");
        horizontalSliderPriority->setGeometry(QRect(120, 20, 160, 16));
        horizontalSliderPriority->setMaximum(100);
        horizontalSliderPriority->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 20, 41, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(290, 20, 31, 20));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(frame_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 20, 71, 20));
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxPriority = new QSpinBox(frame_3);
        spinBoxPriority->setObjectName("spinBoxPriority");
        spinBoxPriority->setGeometry(QRect(330, 11, 51, 31));
        spinBoxPriority->setMaximum(100);
        tableWidgetSelectLibrary = new QTableWidget(RegistLearningSelectLibDialog);
        if (tableWidgetSelectLibrary->columnCount() < 4)
            tableWidgetSelectLibrary->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSelectLibrary->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetSelectLibrary->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetSelectLibrary->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetSelectLibrary->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidgetSelectLibrary->setObjectName("tableWidgetSelectLibrary");
        tableWidgetSelectLibrary->setGeometry(QRect(10, 10, 381, 441));
        tableWidgetSelectLibrary->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetSelectLibrary->setSelectionBehavior(QAbstractItemView::SelectItems);

        retranslateUi(RegistLearningSelectLibDialog);

        QMetaObject::connectSlotsByName(RegistLearningSelectLibDialog);
    } // setupUi

    void retranslateUi(QDialog *RegistLearningSelectLibDialog)
    {
        RegistLearningSelectLibDialog->setWindowTitle(QCoreApplication::translate("RegistLearningSelectLibDialog", "Learning registration", nullptr));
        pushButtonNG->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "NG\343\200\200\347\231\273\351\214\262", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "OK\343\200\200\347\231\273\351\214\262", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "Cancel", nullptr));
        label_4->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "\351\253\230\343\201\204", nullptr));
        label_3->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "\344\275\216\343\201\204", nullptr));
        label_2->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "\351\207\215\350\246\201\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSelectLibrary->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "Check", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetSelectLibrary->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "LibID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetSelectLibrary->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "LibName", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetSelectLibrary->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RegistLearningSelectLibDialog", "Judge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistLearningSelectLibDialog: public Ui_RegistLearningSelectLibDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTLEARNINGSELECTLIBDIALOG_H
