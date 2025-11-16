/********************************************************************************
** Form generated from reading UI file 'PropertyNamingForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTYNAMINGFORM_H
#define UI_PROPERTYNAMINGFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_PropertyNamingFormClass
{
public:
    QTableWidget *tableWidgetNamingList;
    QGroupBox *groupBox_AutoNaming;
    QPushButton *pushButtonExecute;
    QLineEdit *lineEditFormat;
    QLabel *label;
    QPushButton *pushButtonGenerateIndex;
    QGroupBox *groupBox;
    QWidget *verticalLayout;
    QVBoxLayout *vboxLayout;
    QLabel *label_6;
    QHBoxLayout *hboxLayout;
    QDoubleSpinBox *doubleSpinBox_Resolution;
    QLabel *label_7;
    QWidget *verticalLayout_2;
    QVBoxLayout *vboxLayout1;
    QLabel *label_8;
    QLineEdit *lineEdit_ItemsName;
    QPushButton *pushButton_CreateItemFromItsCoordinate;
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QSpinBox *spinBox_ItemsLeft;
    QHBoxLayout *hboxLayout2;
    QLabel *label_4;
    QSpinBox *spinBox_ItemsTop;
    QHBoxLayout *hboxLayout3;
    QLabel *label_3;
    QSpinBox *spinBox_ItemsWidth;
    QHBoxLayout *hboxLayout4;
    QLabel *label_5;
    QSpinBox *spinBox_ItemsHeight;
    QGroupBox *groupBox_2;
    QLabel *label_9;
    QLabel *label_10;
    QSpinBox *spinBoxAutoCountY;
    QSpinBox *spinBoxAutoCountX;
    QToolButton *toolButtonAutoCount;
    QLabel *label_12;
    QLineEdit *lineEditCountFormat;
    QLabel *label_13;
    QSpinBox *spinBoxAutoExpand;
    QGroupBox *groupBox_3;
    QToolButton *toolButtonMakeGroup;
    QListWidget *listWidgetGroup;
    QLabel *label_11;
    QPushButton *pushButtonClearSelectedGroup;

    void setupUi(GUIFormBase *PropertyNamingFormClass)
    {
        if (PropertyNamingFormClass->objectName().isEmpty())
            PropertyNamingFormClass->setObjectName("PropertyNamingFormClass");
        PropertyNamingFormClass->resize(401, 700);
        tableWidgetNamingList = new QTableWidget(PropertyNamingFormClass);
        if (tableWidgetNamingList->columnCount() < 3)
            tableWidgetNamingList->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetNamingList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetNamingList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetNamingList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetNamingList->setObjectName("tableWidgetNamingList");
        tableWidgetNamingList->setGeometry(QRect(10, 560, 371, 131));
        tableWidgetNamingList->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetNamingList->setSelectionBehavior(QAbstractItemView::SelectRows);
        groupBox_AutoNaming = new QGroupBox(PropertyNamingFormClass);
        groupBox_AutoNaming->setObjectName("groupBox_AutoNaming");
        groupBox_AutoNaming->setGeometry(QRect(10, 290, 381, 111));
        pushButtonExecute = new QPushButton(groupBox_AutoNaming);
        pushButtonExecute->setObjectName("pushButtonExecute");
        pushButtonExecute->setGeometry(QRect(210, 20, 161, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Name.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonExecute->setIcon(icon);
        lineEditFormat = new QLineEdit(groupBox_AutoNaming);
        lineEditFormat->setObjectName("lineEditFormat");
        lineEditFormat->setGeometry(QRect(10, 40, 191, 20));
        label = new QLabel(groupBox_AutoNaming);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 191, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonGenerateIndex = new QPushButton(groupBox_AutoNaming);
        pushButtonGenerateIndex->setObjectName("pushButtonGenerateIndex");
        pushButtonGenerateIndex->setGeometry(QRect(130, 70, 241, 31));
        pushButtonGenerateIndex->setIcon(icon);
        groupBox = new QGroupBox(PropertyNamingFormClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 10, 381, 141));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QWidget(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setGeometry(QRect(10, 70, 131, 55));
        vboxLayout = new QVBoxLayout(verticalLayout);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(verticalLayout);
        label_6->setObjectName("label_6");

        vboxLayout->addWidget(label_6);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName("hboxLayout");
        doubleSpinBox_Resolution = new QDoubleSpinBox(verticalLayout);
        doubleSpinBox_Resolution->setObjectName("doubleSpinBox_Resolution");
        sizePolicy.setHeightForWidth(doubleSpinBox_Resolution->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Resolution->setSizePolicy(sizePolicy);
        doubleSpinBox_Resolution->setMaximum(99999.000000000000000);
        doubleSpinBox_Resolution->setSingleStep(0.100000000000000);
        doubleSpinBox_Resolution->setValue(1.000000000000000);

        hboxLayout->addWidget(doubleSpinBox_Resolution);

        label_7 = new QLabel(verticalLayout);
        label_7->setObjectName("label_7");

        hboxLayout->addWidget(label_7);


        vboxLayout->addLayout(hboxLayout);

        verticalLayout_2 = new QWidget(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setGeometry(QRect(10, 20, 131, 53));
        vboxLayout1 = new QVBoxLayout(verticalLayout_2);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName("vboxLayout1");
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(verticalLayout_2);
        label_8->setObjectName("label_8");

        vboxLayout1->addWidget(label_8);

        lineEdit_ItemsName = new QLineEdit(verticalLayout_2);
        lineEdit_ItemsName->setObjectName("lineEdit_ItemsName");

        vboxLayout1->addWidget(lineEdit_ItemsName);

        pushButton_CreateItemFromItsCoordinate = new QPushButton(groupBox);
        pushButton_CreateItemFromItsCoordinate->setObjectName("pushButton_CreateItemFromItsCoordinate");
        pushButton_CreateItemFromItsCoordinate->setGeometry(QRect(290, 110, 81, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_CreateItemFromItsCoordinate->sizePolicy().hasHeightForWidth());
        pushButton_CreateItemFromItsCoordinate->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Make.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_CreateItemFromItsCoordinate->setIcon(icon1);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(190, 20, 203, 106));
        vboxLayout2 = new QVBoxLayout(layoutWidget);
        vboxLayout2->setSpacing(0);
        vboxLayout2->setContentsMargins(11, 11, 11, 11);
        vboxLayout2->setObjectName("vboxLayout2");
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName("hboxLayout1");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        hboxLayout1->addWidget(label_2);

        spinBox_ItemsLeft = new QSpinBox(layoutWidget);
        spinBox_ItemsLeft->setObjectName("spinBox_ItemsLeft");
        spinBox_ItemsLeft->setMaximum(99999);

        hboxLayout1->addWidget(spinBox_ItemsLeft);


        vboxLayout2->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName("hboxLayout2");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);

        hboxLayout2->addWidget(label_4);

        spinBox_ItemsTop = new QSpinBox(layoutWidget);
        spinBox_ItemsTop->setObjectName("spinBox_ItemsTop");
        spinBox_ItemsTop->setMaximum(99999);

        hboxLayout2->addWidget(spinBox_ItemsTop);


        vboxLayout2->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setObjectName("hboxLayout3");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        hboxLayout3->addWidget(label_3);

        spinBox_ItemsWidth = new QSpinBox(layoutWidget);
        spinBox_ItemsWidth->setObjectName("spinBox_ItemsWidth");
        spinBox_ItemsWidth->setMinimum(100);
        spinBox_ItemsWidth->setMaximum(99999);

        hboxLayout3->addWidget(spinBox_ItemsWidth);


        vboxLayout2->addLayout(hboxLayout3);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(6);
        hboxLayout4->setObjectName("hboxLayout4");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        hboxLayout4->addWidget(label_5);

        spinBox_ItemsHeight = new QSpinBox(layoutWidget);
        spinBox_ItemsHeight->setObjectName("spinBox_ItemsHeight");
        spinBox_ItemsHeight->setMinimum(100);
        spinBox_ItemsHeight->setMaximum(99999);

        hboxLayout4->addWidget(spinBox_ItemsHeight);


        vboxLayout2->addLayout(hboxLayout4);

        groupBox_2 = new QGroupBox(PropertyNamingFormClass);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 160, 381, 121));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 44, 131, 22));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setFrameShadow(QFrame::Sunken);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 68, 131, 22));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setFrameShadow(QFrame::Sunken);
        label_10->setAlignment(Qt::AlignCenter);
        spinBoxAutoCountY = new QSpinBox(groupBox_2);
        spinBoxAutoCountY->setObjectName("spinBoxAutoCountY");
        spinBoxAutoCountY->setGeometry(QRect(150, 68, 71, 22));
        spinBoxAutoCountY->setMaximum(9999);
        spinBoxAutoCountX = new QSpinBox(groupBox_2);
        spinBoxAutoCountX->setObjectName("spinBoxAutoCountX");
        spinBoxAutoCountX->setGeometry(QRect(150, 44, 71, 22));
        spinBoxAutoCountX->setMaximum(9999);
        toolButtonAutoCount = new QToolButton(groupBox_2);
        toolButtonAutoCount->setObjectName("toolButtonAutoCount");
        toolButtonAutoCount->setGeometry(QRect(230, 50, 141, 51));
        toolButtonAutoCount->setCheckable(true);
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 20, 131, 21));
        label_12->setFrameShape(QFrame::Panel);
        label_12->setFrameShadow(QFrame::Sunken);
        label_12->setAlignment(Qt::AlignCenter);
        lineEditCountFormat = new QLineEdit(groupBox_2);
        lineEditCountFormat->setObjectName("lineEditCountFormat");
        lineEditCountFormat->setGeometry(QRect(150, 20, 221, 20));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 92, 131, 22));
        label_13->setFrameShape(QFrame::Panel);
        label_13->setFrameShadow(QFrame::Sunken);
        label_13->setAlignment(Qt::AlignCenter);
        spinBoxAutoExpand = new QSpinBox(groupBox_2);
        spinBoxAutoExpand->setObjectName("spinBoxAutoExpand");
        spinBoxAutoExpand->setGeometry(QRect(150, 92, 71, 22));
        spinBoxAutoExpand->setMinimum(-100);
        spinBoxAutoExpand->setMaximum(100);
        groupBox_3 = new QGroupBox(PropertyNamingFormClass);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(0, 400, 381, 151));
        toolButtonMakeGroup = new QToolButton(groupBox_3);
        toolButtonMakeGroup->setObjectName("toolButtonMakeGroup");
        toolButtonMakeGroup->setGeometry(QRect(10, 16, 231, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Group.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toolButtonMakeGroup->setIcon(icon2);
        toolButtonMakeGroup->setCheckable(false);
        toolButtonMakeGroup->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        listWidgetGroup = new QListWidget(groupBox_3);
        listWidgetGroup->setObjectName("listWidgetGroup");
        listWidgetGroup->setGeometry(QRect(10, 70, 251, 71));
        listWidgetGroup->setSelectionMode(QAbstractItemView::MultiSelection);
        listWidgetGroup->setSelectionBehavior(QAbstractItemView::SelectRows);
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 50, 251, 21));
        label_11->setFrameShape(QFrame::Panel);
        label_11->setFrameShadow(QFrame::Sunken);
        label_11->setAlignment(Qt::AlignCenter);
        pushButtonClearSelectedGroup = new QPushButton(groupBox_3);
        pushButtonClearSelectedGroup->setObjectName("pushButtonClearSelectedGroup");
        pushButtonClearSelectedGroup->setGeometry(QRect(270, 90, 101, 23));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonClearSelectedGroup->setIcon(icon3);
        QWidget::setTabOrder(lineEdit_ItemsName, doubleSpinBox_Resolution);
        QWidget::setTabOrder(doubleSpinBox_Resolution, spinBox_ItemsLeft);
        QWidget::setTabOrder(spinBox_ItemsLeft, spinBox_ItemsTop);
        QWidget::setTabOrder(spinBox_ItemsTop, spinBox_ItemsWidth);
        QWidget::setTabOrder(spinBox_ItemsWidth, spinBox_ItemsHeight);
        QWidget::setTabOrder(spinBox_ItemsHeight, pushButton_CreateItemFromItsCoordinate);
        QWidget::setTabOrder(pushButton_CreateItemFromItsCoordinate, lineEditFormat);
        QWidget::setTabOrder(lineEditFormat, pushButtonExecute);
        QWidget::setTabOrder(pushButtonExecute, tableWidgetNamingList);

        retranslateUi(PropertyNamingFormClass);

        QMetaObject::connectSlotsByName(PropertyNamingFormClass);
    } // setupUi

    void retranslateUi(GUIFormBase *PropertyNamingFormClass)
    {
        PropertyNamingFormClass->setWindowTitle(QCoreApplication::translate("PropertyNamingFormClass", "PropertyNamingForm", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetNamingList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PropertyNamingFormClass", "Page", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetNamingList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PropertyNamingFormClass", "Position", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetNamingList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PropertyNamingFormClass", "Name", nullptr));
        groupBox_AutoNaming->setTitle(QCoreApplication::translate("PropertyNamingFormClass", "\350\207\252\345\213\225\343\201\247\345\221\275\345\220\215", nullptr));
        pushButtonExecute->setText(QCoreApplication::translate("PropertyNamingFormClass", "\351\201\270\346\212\236\351\240\230\345\237\237\343\202\222\350\207\252\345\213\225\343\201\247\345\221\275\345\220\215", nullptr));
#if QT_CONFIG(tooltip)
        lineEditFormat->setToolTip(QCoreApplication::translate("PropertyNamingFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Auto Naming's Format Specification</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Their number is counted from first area.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\">From left to right or from top to bottom</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[Axa] or [Aya]  -&gt; Replaced with alphabet in the direction of horizonal([Axa]) or vertical([Aya]).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[Nx1] or [Ny1]  -&gt; Replaced with number in the direction of horizonal([Nx1]) or vertical([Ny1]).</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">From right to left or from bottom to top</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[-Axa] or [-Aya]  -&gt; it means reve"
                        "rsed [Axa] or [Aya].</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[-Nx1] or [-Ny1] -&gt; it means reversed [Nx1] or [Ny1].</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Other characters are all copied</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">{A/N} {x/y} {Top Character}</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEditFormat->setText(QCoreApplication::translate("PropertyNamingFormClass", "Area-[Axa]-[Ny1]", nullptr));
        label->setText(QCoreApplication::translate("PropertyNamingFormClass", "\343\203\225\343\202\251\343\203\274\343\203\236\343\203\203\343\203\210", nullptr));
        pushButtonGenerateIndex->setText(QCoreApplication::translate("PropertyNamingFormClass", "Generate index in selected Items", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PropertyNamingFormClass", "\345\247\213\347\202\271\343\201\256\345\272\247\346\250\231\343\201\250\345\271\205\343\203\273\351\253\230\343\201\225\343\201\213\343\202\211\351\240\230\345\237\237\343\202\222\344\275\234\346\210\220", nullptr));
        label_6->setText(QCoreApplication::translate("PropertyNamingFormClass", "\350\247\243\345\203\217\345\272\246\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("PropertyNamingFormClass", "/ pixel", nullptr));
        label_8->setText(QCoreApplication::translate("PropertyNamingFormClass", "\351\240\230\345\237\237\343\201\256\345\220\215\345\211\215\357\274\232", nullptr));
        pushButton_CreateItemFromItsCoordinate->setText(QCoreApplication::translate("PropertyNamingFormClass", "\344\275\234\346\210\220", nullptr));
        label_2->setText(QCoreApplication::translate("PropertyNamingFormClass", "\345\247\213\347\202\271\343\201\256\345\267\246\343\201\256\345\272\247\346\250\231", nullptr));
        label_4->setText(QCoreApplication::translate("PropertyNamingFormClass", "\345\247\213\347\202\271\343\201\256\344\270\212\343\201\256\345\272\247\346\250\231", nullptr));
        label_3->setText(QCoreApplication::translate("PropertyNamingFormClass", "\345\271\205", nullptr));
        label_5->setText(QCoreApplication::translate("PropertyNamingFormClass", "\351\253\230\343\201\225", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PropertyNamingFormClass", "\347\237\251\345\275\242\345\206\205\343\201\253\350\207\252\345\213\225\347\232\204\343\201\253\347\224\237\346\210\220", nullptr));
        label_9->setText(QCoreApplication::translate("PropertyNamingFormClass", "\346\250\252\346\226\271\345\220\221\343\201\256\345\200\213\346\225\260", nullptr));
        label_10->setText(QCoreApplication::translate("PropertyNamingFormClass", "\347\270\246\346\226\271\345\220\221\343\201\256\345\200\213\346\225\260", nullptr));
        toolButtonAutoCount->setText(QCoreApplication::translate("PropertyNamingFormClass", "\344\275\234\346\210\220\351\226\213\345\247\213", nullptr));
        label_12->setText(QCoreApplication::translate("PropertyNamingFormClass", "\345\220\215\347\247\260\343\203\225\343\202\251\343\203\274\343\203\236\343\203\203\343\203\210", nullptr));
#if QT_CONFIG(tooltip)
        lineEditCountFormat->setToolTip(QCoreApplication::translate("PropertyNamingFormClass", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Auto Naming's Format Specification</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Their number is counted from first area.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\">From left to right or from top to bottom</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[Axa] or [Aya]  -&gt; Replaced with alphabet in the direction of horizonal([Axa]) or vertical([Aya]).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[Nx1] or [Ny1]  -&gt; Replaced with number in the direction of horizonal([Nx1]) or vertical([Ny1]).</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">From right to left or from bottom to top</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[-Axa] or [-Aya]  -&gt; it means reve"
                        "rsed [Axa] or [Aya].</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">[-Nx1] or [-Ny1] -&gt; it means reversed [Nx1] or [Ny1].</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Other characters are all copied</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">{A/N} {x/y} {Top Character}</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        lineEditCountFormat->setText(QCoreApplication::translate("PropertyNamingFormClass", "Area-[Axa]-[Ny1]", nullptr));
        label_13->setText(QCoreApplication::translate("PropertyNamingFormClass", "\345\220\204\343\202\250\343\203\252\343\202\242\343\201\256\350\206\250\345\274\265", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PropertyNamingFormClass", "Group\344\275\234\346\210\220", nullptr));
        toolButtonMakeGroup->setText(QCoreApplication::translate("PropertyNamingFormClass", "\351\201\270\346\212\236\343\201\227\343\201\237\343\202\242\343\202\244\343\203\206\343\203\240\343\202\222\343\202\260\343\203\253\343\203\274\343\203\227\345\214\226", nullptr));
        label_11->setText(QCoreApplication::translate("PropertyNamingFormClass", "\343\202\260\343\203\253\343\203\274\343\203\227\343\203\252\343\202\271\343\203\210", nullptr));
        pushButtonClearSelectedGroup->setText(QCoreApplication::translate("PropertyNamingFormClass", "\351\201\270\346\212\236\350\241\214\343\202\257\343\203\252\343\202\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertyNamingFormClass: public Ui_PropertyNamingFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTYNAMINGFORM_H
