/********************************************************************************
** Form generated from reading UI file 'SelectPasteForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTPASTEFORM_H
#define UI_SELECTPASTEFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectPasteForm
{
public:
    QPushButton *ButtonPasteSameAlgo;
    QPushButton *CancelButton;
    QPushButton *ButtonPasteSameAlgoPosToSelectedLayer;
    QTableWidget *GridPaste;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonLoad;
    QPushButton *pushButtonCutOnShape;
    QPushButton *ButtonFixedPasteByShape;
    QPushButton *ButtonFixedPasteForImage;
    QPushButton *ButtonPasteSameAlgoPos;
    QStackedWidget *stackedWidgetLayerType;
    QWidget *page;
    QComboBox *comboBoxPastedLayer;
    QLabel *label;
    QWidget *page_2;
    QToolButton *toolButtonAdoptLayer0;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *SelectPasteForm)
    {
        if (SelectPasteForm->objectName().isEmpty())
            SelectPasteForm->setObjectName("SelectPasteForm");
        SelectPasteForm->resize(572, 400);
        ButtonPasteSameAlgo = new QPushButton(SelectPasteForm);
        ButtonPasteSameAlgo->setObjectName("ButtonPasteSameAlgo");
        ButtonPasteSameAlgo->setGeometry(QRect(10, 490, 141, 31));
        CancelButton = new QPushButton(SelectPasteForm);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(460, 360, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        CancelButton->setIcon(icon);
        ButtonPasteSameAlgoPosToSelectedLayer = new QPushButton(SelectPasteForm);
        ButtonPasteSameAlgoPosToSelectedLayer->setObjectName("ButtonPasteSameAlgoPosToSelectedLayer");
        ButtonPasteSameAlgoPosToSelectedLayer->setGeometry(QRect(10, 240, 391, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Block.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonPasteSameAlgoPosToSelectedLayer->setIcon(icon1);
        GridPaste = new QTableWidget(SelectPasteForm);
        if (GridPaste->columnCount() < 5)
            GridPaste->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        GridPaste->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        GridPaste->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        GridPaste->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        GridPaste->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        GridPaste->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        GridPaste->setObjectName("GridPaste");
        GridPaste->setGeometry(QRect(10, 10, 551, 181));
        pushButtonSave = new QPushButton(SelectPasteForm);
        pushButtonSave->setObjectName("pushButtonSave");
        pushButtonSave->setGeometry(QRect(10, 360, 181, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonSave->setIcon(icon2);
        pushButtonLoad = new QPushButton(SelectPasteForm);
        pushButtonLoad->setObjectName("pushButtonLoad");
        pushButtonLoad->setGeometry(QRect(200, 360, 201, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Load.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonLoad->setIcon(icon3);
        pushButtonCutOnShape = new QPushButton(SelectPasteForm);
        pushButtonCutOnShape->setObjectName("pushButtonCutOnShape");
        pushButtonCutOnShape->setGeometry(QRect(10, 320, 181, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Cut.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCutOnShape->setIcon(icon4);
        ButtonFixedPasteByShape = new QPushButton(SelectPasteForm);
        ButtonFixedPasteByShape->setObjectName("ButtonFixedPasteByShape");
        ButtonFixedPasteByShape->setGeometry(QRect(200, 320, 201, 31));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Paste.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonFixedPasteByShape->setIcon(icon5);
        ButtonFixedPasteForImage = new QPushButton(SelectPasteForm);
        ButtonFixedPasteForImage->setObjectName("ButtonFixedPasteForImage");
        ButtonFixedPasteForImage->setGeometry(QRect(410, 320, 151, 31));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Image.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonFixedPasteForImage->setIcon(icon6);
        ButtonPasteSameAlgoPos = new QPushButton(SelectPasteForm);
        ButtonPasteSameAlgoPos->setObjectName("ButtonPasteSameAlgoPos");
        ButtonPasteSameAlgoPos->setGeometry(QRect(10, 280, 391, 31));
        ButtonPasteSameAlgoPos->setIcon(icon1);
        stackedWidgetLayerType = new QStackedWidget(SelectPasteForm);
        stackedWidgetLayerType->setObjectName("stackedWidgetLayerType");
        stackedWidgetLayerType->setGeometry(QRect(10, 200, 411, 31));
        page = new QWidget();
        page->setObjectName("page");
        comboBoxPastedLayer = new QComboBox(page);
        comboBoxPastedLayer->setObjectName("comboBoxPastedLayer");
        comboBoxPastedLayer->setGeometry(QRect(190, 0, 181, 22));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 181, 16));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        stackedWidgetLayerType->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        toolButtonAdoptLayer0 = new QToolButton(page_2);
        toolButtonAdoptLayer0->setObjectName("toolButtonAdoptLayer0");
        toolButtonAdoptLayer0->setGeometry(QRect(110, 0, 251, 26));
        toolButtonAdoptLayer0->setCheckable(true);
        toolButtonAdoptLayer0->setChecked(true);
        stackedWidgetLayerType->addWidget(page_2);
        pushButtonDelete = new QPushButton(SelectPasteForm);
        pushButtonDelete->setObjectName("pushButtonDelete");
        pushButtonDelete->setGeometry(QRect(430, 200, 131, 23));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonDelete->setIcon(icon7);

        retranslateUi(SelectPasteForm);

        ButtonPasteSameAlgoPosToSelectedLayer->setDefault(true);
        ButtonPasteSameAlgoPos->setDefault(true);
        stackedWidgetLayerType->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SelectPasteForm);
    } // setupUi

    void retranslateUi(QWidget *SelectPasteForm)
    {
        SelectPasteForm->setWindowTitle(QCoreApplication::translate("SelectPasteForm", "Form", nullptr));
        ButtonPasteSameAlgo->setText(QCoreApplication::translate("SelectPasteForm", "Paste in Same Algorithm", nullptr));
        CancelButton->setText(QCoreApplication::translate("SelectPasteForm", "Cancel", nullptr));
        ButtonPasteSameAlgoPosToSelectedLayer->setText(QCoreApplication::translate("SelectPasteForm", "Same Algorithm ,Position / to Selected layer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = GridPaste->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("SelectPasteForm", "Date/Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = GridPaste->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("SelectPasteForm", "Item Counts", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = GridPaste->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("SelectPasteForm", "Root", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = GridPaste->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("SelectPasteForm", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = GridPaste->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("SelectPasteForm", "Remark", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("SelectPasteForm", "Save selected lines", nullptr));
        pushButtonLoad->setText(QCoreApplication::translate("SelectPasteForm", "Load", nullptr));
        pushButtonCutOnShape->setText(QCoreApplication::translate("SelectPasteForm", "Cut items on Shape", nullptr));
        ButtonFixedPasteByShape->setText(QCoreApplication::translate("SelectPasteForm", "Fixed Paste by Shape", nullptr));
        ButtonFixedPasteForImage->setText(QCoreApplication::translate("SelectPasteForm", "Paste for Image", nullptr));
        ButtonPasteSameAlgoPos->setText(QCoreApplication::translate("SelectPasteForm", "Same Algorithm ,Same Position ,Same layer", nullptr));
        label->setText(QCoreApplication::translate("SelectPasteForm", "Layer to be Pasted", nullptr));
        toolButtonAdoptLayer0->setText(QCoreApplication::translate("SelectPasteForm", "Adopt only Layer-0", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("SelectPasteForm", "Delete line", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectPasteForm: public Ui_SelectPasteForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTPASTEFORM_H
