/********************************************************************************
** Form generated from reading UI file 'EditLibraryDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITLIBRARYDIALOG_H
#define UI_EDITLIBRARYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_EditLibraryDialog
{
public:
    QPushButton *ButtonLibDelete;
    QLineEdit *EditLibID;
    QFrame *frameLibFolder;
    QPushButton *ButtonLibSaveNew;
    QLabel *label_4;
    QLineEdit *EditLibName;
    QPushButton *ButtonLibNew;
    QPushButton *ButtonLibSave;
    QTableWidget *tableWidgetLibList;
    QFrame *frame_2;
    QLabel *label_92;
    QSpinBox *EditSearchDot;
    QLabel *label_93;
    QLabel *label_94;
    QDoubleSpinBox *doubleSpinBoxThresholdM;
    QDoubleSpinBox *doubleSpinBoxThresholdP;
    QSpinBox *EditEdgeWidth;
    QLabel *label_95;
    QCheckBox *checkBoxPrevailLeft;
    QCheckBox *checkBoxPrevailRight;
    QCheckBox *checkBoxModeToSetInInitial;
    QDoubleSpinBox *doubleSpinBoxOKRangeInInitial;
    QLabel *label_96;
    QLabel *label_97;
    QComboBox *comboBoxOutputType;
    QComboBox *comboBoxSearchType;
    QLabel *label_98;
    QDoubleSpinBox *doubleSpinBoxThresholdRate;
    QLabel *label_103;
    QPushButton *pushButton;

    void setupUi(QDialog *EditLibraryDialog)
    {
        if (EditLibraryDialog->objectName().isEmpty())
            EditLibraryDialog->setObjectName("EditLibraryDialog");
        EditLibraryDialog->resize(458, 692);
        ButtonLibDelete = new QPushButton(EditLibraryDialog);
        ButtonLibDelete->setObjectName("ButtonLibDelete");
        ButtonLibDelete->setGeometry(QRect(130, 610, 91, 31));
        QFont font;
        font.setPointSize(11);
        ButtonLibDelete->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibDelete->setIcon(icon);
        EditLibID = new QLineEdit(EditLibraryDialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(80, 230, 81, 31));
        QFont font1;
        font1.setPointSize(12);
        EditLibID->setFont(font1);
        EditLibID->setReadOnly(true);
        frameLibFolder = new QFrame(EditLibraryDialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 211, 201));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        ButtonLibSaveNew = new QPushButton(EditLibraryDialog);
        ButtonLibSaveNew->setObjectName("ButtonLibSaveNew");
        ButtonLibSaveNew->setGeometry(QRect(230, 610, 121, 31));
        ButtonLibSaveNew->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSaveNew->setIcon(icon1);
        label_4 = new QLabel(EditLibraryDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 230, 71, 31));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(EditLibraryDialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(160, 230, 291, 31));
        EditLibName->setFont(font1);
        ButtonLibNew = new QPushButton(EditLibraryDialog);
        ButtonLibNew->setObjectName("ButtonLibNew");
        ButtonLibNew->setGeometry(QRect(10, 610, 111, 31));
        ButtonLibNew->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/ClearNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibNew->setIcon(icon2);
        ButtonLibSave = new QPushButton(EditLibraryDialog);
        ButtonLibSave->setObjectName("ButtonLibSave");
        ButtonLibSave->setGeometry(QRect(360, 610, 91, 31));
        ButtonLibSave->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Update.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonLibSave->setIcon(icon3);
        tableWidgetLibList = new QTableWidget(EditLibraryDialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(230, 10, 221, 201));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        frame_2 = new QFrame(EditLibraryDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 270, 441, 331));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_92 = new QLabel(frame_2);
        label_92->setObjectName("label_92");
        label_92->setGeometry(QRect(50, 10, 201, 21));
        label_92->setFrameShape(QFrame::Panel);
        label_92->setFrameShadow(QFrame::Sunken);
        label_92->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditSearchDot = new QSpinBox(frame_2);
        EditSearchDot->setObjectName("EditSearchDot");
        EditSearchDot->setGeometry(QRect(260, 10, 81, 22));
        EditSearchDot->setMaximum(255);
        label_93 = new QLabel(frame_2);
        label_93->setObjectName("label_93");
        label_93->setGeometry(QRect(50, 40, 201, 21));
        label_93->setFrameShape(QFrame::Panel);
        label_93->setFrameShadow(QFrame::Sunken);
        label_93->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_94 = new QLabel(frame_2);
        label_94->setObjectName("label_94");
        label_94->setGeometry(QRect(50, 70, 201, 21));
        label_94->setFrameShape(QFrame::Panel);
        label_94->setFrameShadow(QFrame::Sunken);
        label_94->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdM = new QDoubleSpinBox(frame_2);
        doubleSpinBoxThresholdM->setObjectName("doubleSpinBoxThresholdM");
        doubleSpinBoxThresholdM->setGeometry(QRect(260, 40, 81, 22));
        doubleSpinBoxThresholdP = new QDoubleSpinBox(frame_2);
        doubleSpinBoxThresholdP->setObjectName("doubleSpinBoxThresholdP");
        doubleSpinBoxThresholdP->setGeometry(QRect(260, 70, 81, 22));
        EditEdgeWidth = new QSpinBox(frame_2);
        EditEdgeWidth->setObjectName("EditEdgeWidth");
        EditEdgeWidth->setGeometry(QRect(260, 100, 81, 22));
        EditEdgeWidth->setMaximum(255);
        label_95 = new QLabel(frame_2);
        label_95->setObjectName("label_95");
        label_95->setGeometry(QRect(50, 100, 201, 21));
        label_95->setFrameShape(QFrame::Panel);
        label_95->setFrameShadow(QFrame::Sunken);
        label_95->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        checkBoxPrevailLeft = new QCheckBox(frame_2);
        checkBoxPrevailLeft->setObjectName("checkBoxPrevailLeft");
        checkBoxPrevailLeft->setGeometry(QRect(50, 130, 351, 21));
        checkBoxPrevailRight = new QCheckBox(frame_2);
        checkBoxPrevailRight->setObjectName("checkBoxPrevailRight");
        checkBoxPrevailRight->setGeometry(QRect(50, 150, 351, 21));
        checkBoxModeToSetInInitial = new QCheckBox(frame_2);
        checkBoxModeToSetInInitial->setObjectName("checkBoxModeToSetInInitial");
        checkBoxModeToSetInInitial->setGeometry(QRect(50, 170, 351, 21));
        doubleSpinBoxOKRangeInInitial = new QDoubleSpinBox(frame_2);
        doubleSpinBoxOKRangeInInitial->setObjectName("doubleSpinBoxOKRangeInInitial");
        doubleSpinBoxOKRangeInInitial->setGeometry(QRect(320, 200, 81, 22));
        label_96 = new QLabel(frame_2);
        label_96->setObjectName("label_96");
        label_96->setGeometry(QRect(10, 200, 301, 21));
        label_96->setFrameShape(QFrame::Panel);
        label_96->setFrameShadow(QFrame::Sunken);
        label_96->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_97 = new QLabel(frame_2);
        label_97->setObjectName("label_97");
        label_97->setGeometry(QRect(10, 230, 111, 21));
        label_97->setFrameShape(QFrame::Panel);
        label_97->setFrameShadow(QFrame::Sunken);
        label_97->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxOutputType = new QComboBox(frame_2);
        comboBoxOutputType->addItem(QString());
        comboBoxOutputType->addItem(QString());
        comboBoxOutputType->setObjectName("comboBoxOutputType");
        comboBoxOutputType->setGeometry(QRect(130, 230, 301, 24));
        comboBoxSearchType = new QComboBox(frame_2);
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->addItem(QString());
        comboBoxSearchType->setObjectName("comboBoxSearchType");
        comboBoxSearchType->setGeometry(QRect(130, 260, 301, 22));
        label_98 = new QLabel(frame_2);
        label_98->setObjectName("label_98");
        label_98->setGeometry(QRect(10, 260, 111, 21));
        label_98->setFrameShape(QFrame::Panel);
        label_98->setFrameShadow(QFrame::Sunken);
        label_98->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxThresholdRate = new QDoubleSpinBox(frame_2);
        doubleSpinBoxThresholdRate->setObjectName("doubleSpinBoxThresholdRate");
        doubleSpinBoxThresholdRate->setGeometry(QRect(310, 290, 121, 21));
        doubleSpinBoxThresholdRate->setDecimals(5);
        doubleSpinBoxThresholdRate->setMaximum(255.000000000000000);
        label_103 = new QLabel(frame_2);
        label_103->setObjectName("label_103");
        label_103->setGeometry(QRect(170, 290, 131, 21));
        label_103->setFrameShape(QFrame::Panel);
        label_103->setFrameShadow(QFrame::Sunken);
        label_103->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(EditLibraryDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 650, 101, 31));
        pushButton->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon4);

        retranslateUi(EditLibraryDialog);

        QMetaObject::connectSlotsByName(EditLibraryDialog);
    } // setupUi

    void retranslateUi(QDialog *EditLibraryDialog)
    {
        EditLibraryDialog->setWindowTitle(QCoreApplication::translate("EditLibraryDialog", "Edit Library", nullptr));
        ButtonLibDelete->setText(QCoreApplication::translate("EditLibraryDialog", "Delete", nullptr));
        EditLibID->setText(QCoreApplication::translate("EditLibraryDialog", "12345", nullptr));
        ButtonLibSaveNew->setText(QCoreApplication::translate("EditLibraryDialog", "Save New", nullptr));
        label_4->setText(QCoreApplication::translate("EditLibraryDialog", "\345\220\215\347\247\260", nullptr));
        EditLibName->setText(QCoreApplication::translate("EditLibraryDialog", "Library Name", nullptr));
        ButtonLibNew->setText(QCoreApplication::translate("EditLibraryDialog", "Clear new", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("EditLibraryDialog", "Update", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EditLibraryDialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EditLibraryDialog", "Name", nullptr));
        label_92->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\343\203\211\343\203\203\343\203\210", nullptr));
        label_93->setText(QCoreApplication::translate("EditLibraryDialog", "\344\270\213\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_94->setText(QCoreApplication::translate("EditLibraryDialog", "\344\270\212\351\231\220\343\201\227\343\201\215\343\201\204\345\200\244\357\274\210\346\234\200\345\260\217\357\274\220\357\274\211", nullptr));
        label_95->setText(QCoreApplication::translate("EditLibraryDialog", "\350\274\252\351\203\255\345\271\205", nullptr));
        checkBoxPrevailLeft->setText(QCoreApplication::translate("EditLibraryDialog", "Prevail left brightness", nullptr));
        checkBoxPrevailRight->setText(QCoreApplication::translate("EditLibraryDialog", "Prevail right brightness", nullptr));
        checkBoxModeToSetInInitial->setText(QCoreApplication::translate("EditLibraryDialog", "Update position and value in Initialization", nullptr));
        label_96->setText(QCoreApplication::translate("EditLibraryDialog", "\345\210\235\346\234\237\345\214\226\346\231\202\343\201\253OK\347\257\204\345\233\262\343\202\222\350\250\255\345\256\232\343\201\231\343\202\213\343\201\250\343\201\215\343\201\256OK\345\271\205(mm)", nullptr));
        label_97->setText(QCoreApplication::translate("EditLibraryDialog", "\345\207\272\345\212\233\343\202\277\343\202\244\343\203\227", nullptr));
        comboBoxOutputType->setItemText(0, QCoreApplication::translate("EditLibraryDialog", "\350\250\210\346\270\254\345\200\244\343\201\256\345\207\272\345\212\233", nullptr));
        comboBoxOutputType->setItemText(1, QCoreApplication::translate("EditLibraryDialog", "\343\201\227\343\201\215\343\201\204\345\200\244\344\270\255\345\244\256\345\200\244\343\201\250\343\201\256\345\267\256\345\210\206\345\207\272\345\212\233", nullptr));

        comboBoxSearchType->setItemText(0, QCoreApplication::translate("EditLibraryDialog", "Separated smart match", nullptr));
        comboBoxSearchType->setItemText(1, QCoreApplication::translate("EditLibraryDialog", "Comparable brightness difference", nullptr));
        comboBoxSearchType->setItemText(2, QCoreApplication::translate("EditLibraryDialog", "Distance-Line:Inside=HighVariance", nullptr));
        comboBoxSearchType->setItemText(3, QCoreApplication::translate("EditLibraryDialog", "Simple brightness difference", nullptr));
        comboBoxSearchType->setItemText(4, QCoreApplication::translate("EditLibraryDialog", "Simple brightness difference rate", nullptr));
        comboBoxSearchType->setItemText(5, QCoreApplication::translate("EditLibraryDialog", "Div from outside", nullptr));
        comboBoxSearchType->setItemText(6, QCoreApplication::translate("EditLibraryDialog", "Div center", nullptr));
        comboBoxSearchType->setItemText(7, QCoreApplication::translate("EditLibraryDialog", "Max difference of deviation", nullptr));

        label_98->setText(QCoreApplication::translate("EditLibraryDialog", "\346\216\242\347\264\242\343\202\277\343\202\244\343\203\227", nullptr));
        label_103->setText(QCoreApplication::translate("EditLibraryDialog", "\346\261\272\345\256\232\345\211\262\345\220\210", nullptr));
        pushButton->setText(QCoreApplication::translate("EditLibraryDialog", "\351\226\211\343\201\230\343\202\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditLibraryDialog: public Ui_EditLibraryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITLIBRARYDIALOG_H
