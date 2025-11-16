/********************************************************************************
** Form generated from reading UI file 'ExpandedPasteForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPANDEDPASTEFORM_H
#define UI_EXPANDEDPASTEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExpandedPasteForm
{
public:
    QPushButton *ButtonOK;
    QLabel *label_8;
    QTabWidget *tabWidget;
    QWidget *tabVH;
    QSpinBox *spinBoxXNumb;
    QLabel *label;
    QSpinBox *spinBoxYNumb;
    QLabel *label_2;
    QSpinBox *spinBoxYDot;
    QLabel *label_3;
    QSpinBox *spinBoxXDot;
    QLabel *label_4;
    QPushButton *ButtonArrange;
    QLabel *label_5;
    QPushButton *ButtonCancel;
    QLineEdit *lineEditTotalNumb;
    QPushButton *ButtonPasteSameAlgo;
    QWidget *MatrixList;
    QTableWidget *tableWidgetMatrixList;
    QPushButton *ButtonPasteSameAlgoInMatrixList;
    QPushButton *pushButtonLoadMastixList;
    QPushButton *pushButtonSaveMastixList;

    void setupUi(QWidget *ExpandedPasteForm)
    {
        if (ExpandedPasteForm->objectName().isEmpty())
            ExpandedPasteForm->setObjectName("ExpandedPasteForm");
        ExpandedPasteForm->resize(279, 385);
        ButtonOK = new QPushButton(ExpandedPasteForm);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(30, 460, 191, 31));
        label_8 = new QLabel(ExpandedPasteForm);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 10, 241, 20));
        QFont font;
        font.setPointSize(10);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidget = new QTabWidget(ExpandedPasteForm);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 40, 261, 341));
        tabVH = new QWidget();
        tabVH->setObjectName("tabVH");
        spinBoxXNumb = new QSpinBox(tabVH);
        spinBoxXNumb->setObjectName("spinBoxXNumb");
        spinBoxXNumb->setGeometry(QRect(30, 30, 91, 22));
        spinBoxXNumb->setMinimum(1);
        spinBoxXNumb->setMaximum(1000000);
        spinBoxXNumb->setValue(10);
        label = new QLabel(tabVH);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 91, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxYNumb = new QSpinBox(tabVH);
        spinBoxYNumb->setObjectName("spinBoxYNumb");
        spinBoxYNumb->setGeometry(QRect(130, 30, 91, 22));
        spinBoxYNumb->setMinimum(1);
        spinBoxYNumb->setMaximum(1000000);
        spinBoxYNumb->setValue(10);
        label_2 = new QLabel(tabVH);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 10, 91, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxYDot = new QSpinBox(tabVH);
        spinBoxYDot->setObjectName("spinBoxYDot");
        spinBoxYDot->setGeometry(QRect(130, 80, 91, 22));
        spinBoxYDot->setMinimum(-1000000);
        spinBoxYDot->setMaximum(1000000);
        spinBoxYDot->setValue(200);
        label_3 = new QLabel(tabVH);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 60, 91, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxXDot = new QSpinBox(tabVH);
        spinBoxXDot->setObjectName("spinBoxXDot");
        spinBoxXDot->setGeometry(QRect(30, 80, 91, 22));
        spinBoxXDot->setMinimum(-1000000);
        spinBoxXDot->setMaximum(1000000);
        spinBoxXDot->setValue(200);
        label_4 = new QLabel(tabVH);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 60, 91, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonArrange = new QPushButton(tabVH);
        ButtonArrange->setObjectName("ButtonArrange");
        ButtonArrange->setGeometry(QRect(20, 170, 101, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Move.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonArrange->setIcon(icon);
        label_5 = new QLabel(tabVH);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(30, 140, 91, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonCancel = new QPushButton(tabVH);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(140, 170, 101, 41));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon1);
        lineEditTotalNumb = new QLineEdit(tabVH);
        lineEditTotalNumb->setObjectName("lineEditTotalNumb");
        lineEditTotalNumb->setGeometry(QRect(120, 140, 91, 20));
        lineEditTotalNumb->setMaxLength(12);
        lineEditTotalNumb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditTotalNumb->setReadOnly(true);
        ButtonPasteSameAlgo = new QPushButton(tabVH);
        ButtonPasteSameAlgo->setObjectName("ButtonPasteSameAlgo");
        ButtonPasteSameAlgo->setGeometry(QRect(10, 250, 241, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Paste.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPasteSameAlgo->setIcon(icon2);
        tabWidget->addTab(tabVH, QString());
        MatrixList = new QWidget();
        MatrixList->setObjectName("MatrixList");
        tableWidgetMatrixList = new QTableWidget(MatrixList);
        if (tableWidgetMatrixList->columnCount() < 3)
            tableWidgetMatrixList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetMatrixList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetMatrixList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetMatrixList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetMatrixList->setObjectName("tableWidgetMatrixList");
        tableWidgetMatrixList->setGeometry(QRect(10, 10, 241, 191));
        ButtonPasteSameAlgoInMatrixList = new QPushButton(MatrixList);
        ButtonPasteSameAlgoInMatrixList->setObjectName("ButtonPasteSameAlgoInMatrixList");
        ButtonPasteSameAlgoInMatrixList->setGeometry(QRect(20, 260, 221, 41));
        ButtonPasteSameAlgoInMatrixList->setIcon(icon2);
        pushButtonLoadMastixList = new QPushButton(MatrixList);
        pushButtonLoadMastixList->setObjectName("pushButtonLoadMastixList");
        pushButtonLoadMastixList->setGeometry(QRect(20, 210, 91, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoadMastixList->setIcon(icon3);
        pushButtonSaveMastixList = new QPushButton(MatrixList);
        pushButtonSaveMastixList->setObjectName("pushButtonSaveMastixList");
        pushButtonSaveMastixList->setGeometry(QRect(150, 210, 91, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSaveMastixList->setIcon(icon4);
        tabWidget->addTab(MatrixList, QString());

        retranslateUi(ExpandedPasteForm);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ExpandedPasteForm);
    } // setupUi

    void retranslateUi(QWidget *ExpandedPasteForm)
    {
        ExpandedPasteForm->setWindowTitle(QCoreApplication::translate("ExpandedPasteForm", "Form", nullptr));
        ButtonOK->setText(QCoreApplication::translate("ExpandedPasteForm", "Fixed Paste by Shape", nullptr));
        label_8->setText(QCoreApplication::translate("ExpandedPasteForm", "\351\201\270\346\212\236\343\201\225\343\202\214\343\201\237\343\202\242\343\202\244\343\203\206\343\203\240\343\202\222\350\262\274\343\202\212\344\273\230\343\201\221", nullptr));
        label->setText(QCoreApplication::translate("ExpandedPasteForm", "\346\250\252\343\201\256\345\200\213\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("ExpandedPasteForm", "\347\270\246\343\201\256\345\200\213\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("ExpandedPasteForm", "\346\250\252\343\201\256\351\226\223\351\232\224(Dot)", nullptr));
        label_4->setText(QCoreApplication::translate("ExpandedPasteForm", "\347\270\246\343\201\256\351\226\223\351\232\224(Dot)", nullptr));
        ButtonArrange->setText(QCoreApplication::translate("ExpandedPasteForm", "\351\205\215\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("ExpandedPasteForm", "\345\200\213\346\225\260", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("ExpandedPasteForm", "Cancel", nullptr));
        ButtonPasteSameAlgo->setText(QCoreApplication::translate("ExpandedPasteForm", "\345\220\214\343\201\230\343\202\242\343\203\253\343\202\264\343\203\252\343\202\272\343\203\240\343\201\270\343\201\256\350\262\274\343\202\212\344\273\230\343\201\221", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabVH), QCoreApplication::translate("ExpandedPasteForm", "\347\270\246\346\250\252", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetMatrixList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ExpandedPasteForm", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetMatrixList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ExpandedPasteForm", "XPos", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetMatrixList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ExpandedPasteForm", "YPos", nullptr));
        ButtonPasteSameAlgoInMatrixList->setText(QCoreApplication::translate("ExpandedPasteForm", "\345\220\214\343\201\230\343\202\242\343\203\253\343\202\264\343\203\252\343\202\272\343\203\240\343\201\270\343\201\256\350\262\274\343\202\212\344\273\230\343\201\221", nullptr));
        pushButtonLoadMastixList->setText(QCoreApplication::translate("ExpandedPasteForm", "Load", nullptr));
        pushButtonSaveMastixList->setText(QCoreApplication::translate("ExpandedPasteForm", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(MatrixList), QCoreApplication::translate("ExpandedPasteForm", "\345\272\247\346\250\231\343\203\252\343\202\271\343\203\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExpandedPasteForm: public Ui_ExpandedPasteForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPANDEDPASTEFORM_H
