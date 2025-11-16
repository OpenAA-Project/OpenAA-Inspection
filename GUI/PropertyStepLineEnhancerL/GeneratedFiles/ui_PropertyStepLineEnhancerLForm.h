/********************************************************************************
** Form generated from reading UI file 'PropertyStepLineEnhancerLForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYSTEPLINEENHANCERLFORM_H
#define UI_PROPERTYSTEPLINEENHANCERLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <guiformbase.h>

QT_BEGIN_NAMESPACE

class Ui_PropertyStepLineEnhancerLForm
{
public:
    QLabel *label_30;
    QPushButton *ButtonPickupTest;
    QPushButton *pushButtonGetBack;
    QPushButton *ButtonGenerateLibs;
    QLabel *label_31;
    QPushButton *pushButtonSetFromAll;
    QLabel *labelLibFolderName;
    QPushButton *pushButtonEditLibFolder;
    QPushButton *pushButtonGetBackAll;
    QTableWidget *tableWidgetGeneratedLibList;
    QPushButton *ButtonPickupClearTest;
    QFrame *frame_2;
    QLabel *label_37;
    QLabel *label_35;
    QSpinBox *EditMinSize;
    QLabel *label_34;
    QLabel *label_29;
    QSpinBox *EditPriority;
    QSpinBox *EditStepDot;
    QSpinBox *EditMaxSize;
    QSpinBox *EditMaxDot;
    QSpinBox *EditMinDot;
    QSpinBox *EditSearchBlockWidth;
    QLabel *label_26;
    QLabel *label_28;
    QSpinBox *EditShrinkDot;
    QLabel *label_27;
    QLabel *label_36;
    QLabel *label_39;
    QSpinBox *EditLimitDot;
    QPushButton *ButtonLibSave;
    QLabel *label_3;
    QLineEdit *EditLibName;
    QLabel *label_4;
    QLineEdit *EditLibID;
    QTableWidget *tableWidgetLibList;
    QPushButton *pushButtonEditLibrary;
    QPushButton *pushButtonSetFrom;
    QFrame *frame;
    QRadioButton *radioButtonPickupArea;
    QLabel *label;
    QRadioButton *radioButtonCalc;
    QRadioButton *radioButtonBlock;
    QRadioButton *radioButtonMatching;

    void setupUi(GUIFormBase *PropertyStepLineEnhancerLForm)
    {
        if (PropertyStepLineEnhancerLForm->objectName().isEmpty())
            PropertyStepLineEnhancerLForm->setObjectName(QString::fromUtf8("PropertyStepLineEnhancerLForm"));
        PropertyStepLineEnhancerLForm->resize(400, 700);
        label_30 = new QLabel(PropertyStepLineEnhancerLForm);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(10, 50, 161, 20));
        label_30->setFrameShape(QFrame::Panel);
        label_30->setFrameShadow(QFrame::Sunken);
        label_30->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ButtonPickupTest = new QPushButton(PropertyStepLineEnhancerLForm);
        ButtonPickupTest->setObjectName(QString::fromUtf8("ButtonPickupTest"));
        ButtonPickupTest->setGeometry(QRect(10, 234, 191, 41));
        QFont font;
        font.setPointSize(11);
        ButtonPickupTest->setFont(font);
        pushButtonGetBack = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonGetBack->setObjectName(QString::fromUtf8("pushButtonGetBack"));
        pushButtonGetBack->setGeometry(QRect(180, 120, 39, 23));
        ButtonGenerateLibs = new QPushButton(PropertyStepLineEnhancerLForm);
        ButtonGenerateLibs->setObjectName(QString::fromUtf8("ButtonGenerateLibs"));
        ButtonGenerateLibs->setGeometry(QRect(210, 240, 181, 71));
        ButtonGenerateLibs->setFont(font);
        label_31 = new QLabel(PropertyStepLineEnhancerLForm);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(230, 50, 161, 20));
        label_31->setFrameShape(QFrame::Panel);
        label_31->setFrameShadow(QFrame::Sunken);
        label_31->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonSetFromAll = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonSetFromAll->setObjectName(QString::fromUtf8("pushButtonSetFromAll"));
        pushButtonSetFromAll->setGeometry(QRect(180, 170, 39, 23));
        labelLibFolderName = new QLabel(PropertyStepLineEnhancerLForm);
        labelLibFolderName->setObjectName(QString::fromUtf8("labelLibFolderName"));
        labelLibFolderName->setGeometry(QRect(140, 10, 241, 31));
        QFont font1;
        font1.setPointSize(16);
        labelLibFolderName->setFont(font1);
        pushButtonEditLibFolder = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonEditLibFolder->setObjectName(QString::fromUtf8("pushButtonEditLibFolder"));
        pushButtonEditLibFolder->setGeometry(QRect(20, 10, 101, 31));
        pushButtonGetBackAll = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonGetBackAll->setObjectName(QString::fromUtf8("pushButtonGetBackAll"));
        pushButtonGetBackAll->setGeometry(QRect(180, 200, 39, 23));
        tableWidgetGeneratedLibList = new QTableWidget(PropertyStepLineEnhancerLForm);
        if (tableWidgetGeneratedLibList->columnCount() < 2)
            tableWidgetGeneratedLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetGeneratedLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetGeneratedLibList->setObjectName(QString::fromUtf8("tableWidgetGeneratedLibList"));
        tableWidgetGeneratedLibList->setGeometry(QRect(230, 70, 161, 121));
        tableWidgetGeneratedLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonPickupClearTest = new QPushButton(PropertyStepLineEnhancerLForm);
        ButtonPickupClearTest->setObjectName(QString::fromUtf8("ButtonPickupClearTest"));
        ButtonPickupClearTest->setGeometry(QRect(10, 280, 191, 31));
        ButtonPickupClearTest->setFont(font);
        frame_2 = new QFrame(PropertyStepLineEnhancerLForm);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(10, 430, 381, 261));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_37 = new QLabel(frame_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(40, 120, 131, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_35 = new QLabel(frame_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(210, 50, 81, 21));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setFrameShadow(QFrame::Sunken);
        label_35->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMinSize = new QSpinBox(frame_2);
        EditMinSize->setObjectName(QString::fromUtf8("EditMinSize"));
        EditMinSize->setGeometry(QRect(290, 50, 71, 22));
        EditMinSize->setMaximum(999999);
        label_34 = new QLabel(frame_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(200, 150, 111, 21));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setFrameShadow(QFrame::Sunken);
        label_34->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_29 = new QLabel(frame_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 150, 121, 21));
        label_29->setFrameShape(QFrame::Panel);
        label_29->setFrameShadow(QFrame::Sunken);
        label_29->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditPriority = new QSpinBox(frame_2);
        EditPriority->setObjectName(QString::fromUtf8("EditPriority"));
        EditPriority->setGeometry(QRect(130, 150, 61, 22));
        EditPriority->setMaximum(255);
        EditStepDot = new QSpinBox(frame_2);
        EditStepDot->setObjectName(QString::fromUtf8("EditStepDot"));
        EditStepDot->setGeometry(QRect(310, 150, 61, 22));
        EditStepDot->setMaximum(255);
        EditMaxSize = new QSpinBox(frame_2);
        EditMaxSize->setObjectName(QString::fromUtf8("EditMaxSize"));
        EditMaxSize->setGeometry(QRect(290, 70, 71, 22));
        EditMaxSize->setMaximum(999999);
        EditMaxDot = new QSpinBox(frame_2);
        EditMaxDot->setObjectName(QString::fromUtf8("EditMaxDot"));
        EditMaxDot->setGeometry(QRect(120, 70, 71, 22));
        EditMaxDot->setMaximum(99999999);
        EditMinDot = new QSpinBox(frame_2);
        EditMinDot->setObjectName(QString::fromUtf8("EditMinDot"));
        EditMinDot->setGeometry(QRect(120, 50, 71, 22));
        EditMinDot->setMaximum(999999);
        EditSearchBlockWidth = new QSpinBox(frame_2);
        EditSearchBlockWidth->setObjectName(QString::fromUtf8("EditSearchBlockWidth"));
        EditSearchBlockWidth->setGeometry(QRect(170, 120, 61, 22));
        EditSearchBlockWidth->setMaximum(255);
        label_26 = new QLabel(frame_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(40, 100, 131, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_28 = new QLabel(frame_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(40, 70, 81, 21));
        label_28->setFrameShape(QFrame::Panel);
        label_28->setFrameShadow(QFrame::Sunken);
        label_28->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditShrinkDot = new QSpinBox(frame_2);
        EditShrinkDot->setObjectName(QString::fromUtf8("EditShrinkDot"));
        EditShrinkDot->setGeometry(QRect(170, 100, 61, 22));
        EditShrinkDot->setMaximum(255);
        label_27 = new QLabel(frame_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(40, 50, 81, 21));
        label_27->setFrameShape(QFrame::Panel);
        label_27->setFrameShadow(QFrame::Sunken);
        label_27->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(frame_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(210, 70, 81, 21));
        label_36->setFrameShape(QFrame::Panel);
        label_36->setFrameShadow(QFrame::Sunken);
        label_36->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(frame_2);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(10, 180, 121, 21));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setFrameShadow(QFrame::Sunken);
        label_39->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLimitDot = new QSpinBox(frame_2);
        EditLimitDot->setObjectName(QString::fromUtf8("EditLimitDot"));
        EditLimitDot->setGeometry(QRect(130, 180, 61, 22));
        EditLimitDot->setMaximum(99999);
        ButtonLibSave = new QPushButton(frame_2);
        ButtonLibSave->setObjectName(QString::fromUtf8("ButtonLibSave"));
        ButtonLibSave->setGeometry(QRect(10, 210, 361, 41));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 0, 381, 21));
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibName = new QLineEdit(frame_2);
        EditLibName->setObjectName(QString::fromUtf8("EditLibName"));
        EditLibName->setGeometry(QRect(140, 20, 231, 21));
        QFont font2;
        font2.setPointSize(12);
        EditLibName->setFont(font2);
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 20, 51, 21));
        label_4->setFont(font2);
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditLibID = new QLineEdit(frame_2);
        EditLibID->setObjectName(QString::fromUtf8("EditLibID"));
        EditLibID->setGeometry(QRect(60, 20, 81, 21));
        EditLibID->setFont(font2);
        EditLibID->setReadOnly(true);
        tableWidgetLibList = new QTableWidget(PropertyStepLineEnhancerLForm);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        tableWidgetLibList->setObjectName(QString::fromUtf8("tableWidgetLibList"));
        tableWidgetLibList->setGeometry(QRect(10, 70, 161, 161));
        tableWidgetLibList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        pushButtonEditLibrary = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonEditLibrary->setObjectName(QString::fromUtf8("pushButtonEditLibrary"));
        pushButtonEditLibrary->setGeometry(QRect(230, 200, 161, 31));
        pushButtonEditLibrary->setFont(font2);
        pushButtonSetFrom = new QPushButton(PropertyStepLineEnhancerLForm);
        pushButtonSetFrom->setObjectName(QString::fromUtf8("pushButtonSetFrom"));
        pushButtonSetFrom->setGeometry(QRect(180, 90, 39, 23));
        frame = new QFrame(PropertyStepLineEnhancerLForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(90, 320, 211, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        radioButtonPickupArea = new QRadioButton(frame);
        radioButtonPickupArea->setObjectName(QString::fromUtf8("radioButtonPickupArea"));
        radioButtonPickupArea->setGeometry(QRect(10, 20, 191, 18));
        radioButtonPickupArea->setChecked(true);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 211, 20));
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        radioButtonCalc = new QRadioButton(frame);
        radioButtonCalc->setObjectName(QString::fromUtf8("radioButtonCalc"));
        radioButtonCalc->setGeometry(QRect(10, 60, 191, 18));
        radioButtonBlock = new QRadioButton(frame);
        radioButtonBlock->setObjectName(QString::fromUtf8("radioButtonBlock"));
        radioButtonBlock->setGeometry(QRect(10, 40, 191, 18));
        radioButtonMatching = new QRadioButton(frame);
        radioButtonMatching->setObjectName(QString::fromUtf8("radioButtonMatching"));
        radioButtonMatching->setGeometry(QRect(10, 80, 191, 18));

        retranslateUi(PropertyStepLineEnhancerLForm);

        QMetaObject::connectSlotsByName(PropertyStepLineEnhancerLForm);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyStepLineEnhancerLForm)
    {
        PropertyStepLineEnhancerLForm->setWindowTitle(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "Property StepLineEnhancer", nullptr));
        label_30->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\347\231\273\351\214\262\343\201\225\343\202\214\343\201\246\343\201\204\343\202\213\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\252\343\202\271\343\203\210", nullptr));
        ButtonPickupTest->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\345\215\230\344\270\200\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\343\201\256\346\212\275\345\207\272", nullptr));
        pushButtonGetBack->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "<=", nullptr));
        ButtonGenerateLibs->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\344\270\212\343\201\256\345\205\250\343\201\246\343\201\256\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\201\247\347\224\237\346\210\220", nullptr));
        label_31->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\344\273\212\345\233\236\344\275\277\347\224\250\343\201\231\343\202\213\350\250\255\345\256\232", nullptr));
        pushButtonSetFromAll->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "=>>", nullptr));
        labelLibFolderName->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\357\274\270\357\274\270\357\274\270", nullptr));
        pushButtonEditLibFolder->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\345\210\206\351\241\236\351\201\270\346\212\236", nullptr));
        pushButtonGetBackAll->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "<<=", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetGeneratedLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetGeneratedLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "Name", nullptr));
        ButtonPickupClearTest->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\212\275\345\207\272\343\201\256\343\202\257\343\203\252\343\202\242", nullptr));
        label_37->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\216\242\347\264\242\351\240\230\345\237\237\345\271\205", nullptr));
        label_35->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\234\200\345\260\217\351\225\267\343\201\225", nullptr));
        label_34->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\345\210\206\345\211\262\347\265\202\347\253\257\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_29->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\347\224\237\346\210\220\346\231\202\343\201\256\345\204\252\345\205\210\345\272\246", nullptr));
        label_26->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\345\207\246\347\220\206\351\240\230\345\237\237\343\201\270\343\201\256\345\217\216\347\270\256\351\207\217", nullptr));
        label_28->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\234\200\345\244\247\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_27->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\234\200\345\260\217\343\203\211\343\203\203\343\203\210\346\225\260", nullptr));
        label_36->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\234\200\345\244\247\351\225\267\343\201\225", nullptr));
        label_39->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\351\231\220\347\225\214\343\202\265\343\202\244\343\202\272", nullptr));
        ButtonLibSave->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\343\203\207\343\203\274\343\202\277\343\203\231\343\203\274\343\202\271\343\201\270\343\201\256\346\233\264\346\226\260", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\343\203\227\343\203\255\343\203\221\343\203\206\343\202\243", nullptr));
        EditLibName->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "Library Name", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\345\220\215\347\247\260", nullptr));
        EditLibID->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "12345", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "Name", nullptr));
        pushButtonEditLibrary->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\343\203\251\343\202\244\343\203\226\343\203\251\343\203\252\347\267\250\351\233\206", nullptr));
        pushButtonSetFrom->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "=>", nullptr));
        radioButtonPickupArea->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\212\275\345\207\272\351\240\230\345\237\237", nullptr));
        label->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\350\241\250\347\244\272", nullptr));
        radioButtonCalc->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\351\201\251\347\224\250\351\240\230\345\237\237", nullptr));
        radioButtonBlock->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\346\212\275\345\207\272\343\203\226\343\203\255\343\203\203\343\202\257\351\240\230\345\237\237", nullptr));
        radioButtonMatching->setText(QCoreApplication::translate("PropertyStepLineEnhancerLForm", "\343\203\236\343\203\203\343\203\201\343\203\263\343\202\260\351\240\230\345\237\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyStepLineEnhancerLForm: public Ui_PropertyStepLineEnhancerLForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYSTEPLINEENHANCERLFORM_H
