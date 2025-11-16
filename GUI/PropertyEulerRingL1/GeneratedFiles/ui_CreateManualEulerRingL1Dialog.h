/********************************************************************************
** Form generated from reading UI file 'CreateManualEulerRingL1Dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEMANUALEULERRINGL1DIALOG_H
#define UI_CREATEMANUALEULERRINGL1DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateManualEulerRingL1Dialog
{
public:
    QPushButton *ButtonCancel;
    QLineEdit *EditItemName;
    QLineEdit *EditLibName;
    QLineEdit *EditLibID;
    QTableWidget *tableWidgetLibList;
    QPushButton *ButtonOK;
    QLabel *label_6;
    QFrame *frameLibFolder;
    QLabel *label;
    QTabWidget *tabWidgetInspect;
    QWidget *tab_6;
    QLabel *label_23;
    QLabel *label_22;
    QLabel *label_21;
    QSpinBox *EditDarkWidth;
    QSpinBox *EditLightWidth;
    QLabel *label_37;
    QSpinBox *EditConnectLen;
    QLabel *labelUnitName_8;
    QDoubleSpinBox *doubleSpinBoxConnectLenMM;
    QLabel *labelUnitName_3;
    QCheckBox *checkModeEnableOpenRingCheck;
    QWidget *tab_5;
    QSpinBox *EditMinHoleDiameter;
    QLabel *label_17;
    QSpinBox *EditMaxShiftHole;
    QLabel *label_32;
    QDoubleSpinBox *doubleSpinBoxMinHoleDiameterMM;
    QDoubleSpinBox *doubleSpinBoxMaxShiftHoleMM;
    QLabel *labelUnitName_2;
    QDoubleSpinBox *doubleSpinBoxMaxHoleDiameterMM;
    QSpinBox *EditMaxHoleDiameter;
    QLabel *label_18;
    QLabel *label_20;
    QSpinBox *EditHoleBrightnessAsReference;
    QWidget *tab_7;
    QCheckBox *checkModeEnabled;
    QCheckBox *checkModeAbsoluteBright;
    QCheckBox *checkModeCenterBrightFromParts;
    QCheckBox *checkModeDynamicMask;
    QCheckBox *checkModeEnableHoleCheck;
    QWidget *tab_8;
    QLabel *label_26;
    QLabel *label_25;
    QSpinBox *EditAdjustWhite;
    QSpinBox *EditAdjustBlack;
    QWidget *tab;
    QSpinBox *EditExpandForDynamicMask;
    QLabel *label_19;

    void setupUi(QDialog *CreateManualEulerRingL1Dialog)
    {
        if (CreateManualEulerRingL1Dialog->objectName().isEmpty())
            CreateManualEulerRingL1Dialog->setObjectName("CreateManualEulerRingL1Dialog");
        CreateManualEulerRingL1Dialog->resize(424, 419);
        ButtonCancel = new QPushButton(CreateManualEulerRingL1Dialog);
        ButtonCancel->setObjectName("ButtonCancel");
        ButtonCancel->setGeometry(QRect(270, 380, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/Cancel.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonCancel->setIcon(icon);
        EditItemName = new QLineEdit(CreateManualEulerRingL1Dialog);
        EditItemName->setObjectName("EditItemName");
        EditItemName->setGeometry(QRect(90, 160, 321, 21));
        EditItemName->setReadOnly(false);
        EditLibName = new QLineEdit(CreateManualEulerRingL1Dialog);
        EditLibName->setObjectName("EditLibName");
        EditLibName->setGeometry(QRect(90, 190, 321, 21));
        EditLibName->setReadOnly(true);
        EditLibID = new QLineEdit(CreateManualEulerRingL1Dialog);
        EditLibID->setObjectName("EditLibID");
        EditLibID->setGeometry(QRect(40, 190, 51, 21));
        EditLibID->setReadOnly(true);
        tableWidgetLibList = new QTableWidget(CreateManualEulerRingL1Dialog);
        if (tableWidgetLibList->columnCount() < 2)
            tableWidgetLibList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetLibList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetLibList->setObjectName("tableWidgetLibList");
        tableWidgetLibList->setGeometry(QRect(210, 10, 201, 141));
        tableWidgetLibList->setSelectionBehavior(QAbstractItemView::SelectRows);
        ButtonOK = new QPushButton(CreateManualEulerRingL1Dialog);
        ButtonOK->setObjectName("ButtonOK");
        ButtonOK->setGeometry(QRect(30, 380, 101, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/OK.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ButtonOK->setIcon(icon1);
        label_6 = new QLabel(CreateManualEulerRingL1Dialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 220, 20, 151));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Raised);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(1);
        frameLibFolder = new QFrame(CreateManualEulerRingL1Dialog);
        frameLibFolder->setObjectName("frameLibFolder");
        frameLibFolder->setGeometry(QRect(10, 10, 191, 141));
        frameLibFolder->setFrameShape(QFrame::StyledPanel);
        frameLibFolder->setFrameShadow(QFrame::Sunken);
        label = new QLabel(CreateManualEulerRingL1Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 160, 81, 21));
        tabWidgetInspect = new QTabWidget(CreateManualEulerRingL1Dialog);
        tabWidgetInspect->setObjectName("tabWidgetInspect");
        tabWidgetInspect->setGeometry(QRect(60, 220, 331, 151));
        tab_6 = new QWidget();
        tab_6->setObjectName("tab_6");
        label_23 = new QLabel(tab_6);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(140, 10, 91, 21));
        label_23->setFrameShape(QFrame::Panel);
        label_23->setFrameShadow(QFrame::Sunken);
        label_23->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_22 = new QLabel(tab_6);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 30, 121, 20));
        label_22->setFrameShape(QFrame::Panel);
        label_22->setFrameShadow(QFrame::Sunken);
        label_22->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21 = new QLabel(tab_6);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(230, 10, 91, 21));
        label_21->setFrameShape(QFrame::Panel);
        label_21->setFrameShadow(QFrame::Sunken);
        label_21->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditDarkWidth = new QSpinBox(tab_6);
        EditDarkWidth->setObjectName("EditDarkWidth");
        EditDarkWidth->setGeometry(QRect(140, 30, 91, 20));
        EditDarkWidth->setMinimum(-255);
        EditDarkWidth->setMaximum(255);
        EditLightWidth = new QSpinBox(tab_6);
        EditLightWidth->setObjectName("EditLightWidth");
        EditLightWidth->setGeometry(QRect(230, 30, 91, 20));
        EditLightWidth->setMinimum(-255);
        EditLightWidth->setMaximum(255);
        label_37 = new QLabel(tab_6);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(10, 70, 121, 21));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setFrameShadow(QFrame::Sunken);
        label_37->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditConnectLen = new QSpinBox(tab_6);
        EditConnectLen->setObjectName("EditConnectLen");
        EditConnectLen->setGeometry(QRect(140, 70, 91, 22));
        EditConnectLen->setMinimum(-9999);
        EditConnectLen->setMaximum(99999999);
        labelUnitName_8 = new QLabel(tab_6);
        labelUnitName_8->setObjectName("labelUnitName_8");
        labelUnitName_8->setGeometry(QRect(320, 60, 61, 20));
        labelUnitName_8->setFrameShape(QFrame::NoFrame);
        labelUnitName_8->setFrameShadow(QFrame::Sunken);
        labelUnitName_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxConnectLenMM = new QDoubleSpinBox(tab_6);
        doubleSpinBoxConnectLenMM->setObjectName("doubleSpinBoxConnectLenMM");
        doubleSpinBoxConnectLenMM->setGeometry(QRect(230, 70, 91, 22));
        QPalette palette;
        QBrush brush(QColor(255, 170, 0, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxConnectLenMM->setPalette(palette);
        doubleSpinBoxConnectLenMM->setMaximum(9999999999.000000000000000);
        labelUnitName_3 = new QLabel(tab_6);
        labelUnitName_3->setObjectName("labelUnitName_3");
        labelUnitName_3->setGeometry(QRect(220, 50, 91, 20));
        labelUnitName_3->setFrameShape(QFrame::NoFrame);
        labelUnitName_3->setFrameShadow(QFrame::Sunken);
        labelUnitName_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkModeEnableOpenRingCheck = new QCheckBox(tab_6);
        checkModeEnableOpenRingCheck->setObjectName("checkModeEnableOpenRingCheck");
        checkModeEnableOpenRingCheck->setGeometry(QRect(10, 98, 291, 20));
        tabWidgetInspect->addTab(tab_6, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        EditMinHoleDiameter = new QSpinBox(tab_5);
        EditMinHoleDiameter->setObjectName("EditMinHoleDiameter");
        EditMinHoleDiameter->setGeometry(QRect(140, 50, 91, 20));
        EditMinHoleDiameter->setMinimum(-255);
        EditMinHoleDiameter->setMaximum(255);
        label_17 = new QLabel(tab_5);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 50, 121, 21));
        label_17->setFrameShape(QFrame::Panel);
        label_17->setFrameShadow(QFrame::Sunken);
        label_17->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditMaxShiftHole = new QSpinBox(tab_5);
        EditMaxShiftHole->setObjectName("EditMaxShiftHole");
        EditMaxShiftHole->setGeometry(QRect(140, 90, 91, 20));
        EditMaxShiftHole->setMaximum(99999999);
        label_32 = new QLabel(tab_5);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(10, 90, 121, 20));
        label_32->setFrameShape(QFrame::Panel);
        label_32->setFrameShadow(QFrame::Sunken);
        label_32->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        doubleSpinBoxMinHoleDiameterMM = new QDoubleSpinBox(tab_5);
        doubleSpinBoxMinHoleDiameterMM->setObjectName("doubleSpinBoxMinHoleDiameterMM");
        doubleSpinBoxMinHoleDiameterMM->setGeometry(QRect(230, 50, 91, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxMinHoleDiameterMM->setPalette(palette1);
        doubleSpinBoxMinHoleDiameterMM->setMaximum(9999999999.000000000000000);
        doubleSpinBoxMaxShiftHoleMM = new QDoubleSpinBox(tab_5);
        doubleSpinBoxMaxShiftHoleMM->setObjectName("doubleSpinBoxMaxShiftHoleMM");
        doubleSpinBoxMaxShiftHoleMM->setGeometry(QRect(230, 90, 91, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxMaxShiftHoleMM->setPalette(palette2);
        doubleSpinBoxMaxShiftHoleMM->setMaximum(9999999999.000000000000000);
        labelUnitName_2 = new QLabel(tab_5);
        labelUnitName_2->setObjectName("labelUnitName_2");
        labelUnitName_2->setGeometry(QRect(220, 30, 91, 20));
        labelUnitName_2->setFrameShape(QFrame::NoFrame);
        labelUnitName_2->setFrameShadow(QFrame::Sunken);
        labelUnitName_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBoxMaxHoleDiameterMM = new QDoubleSpinBox(tab_5);
        doubleSpinBoxMaxHoleDiameterMM->setObjectName("doubleSpinBoxMaxHoleDiameterMM");
        doubleSpinBoxMaxHoleDiameterMM->setGeometry(QRect(230, 70, 91, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        doubleSpinBoxMaxHoleDiameterMM->setPalette(palette3);
        doubleSpinBoxMaxHoleDiameterMM->setMaximum(9999999999.000000000000000);
        EditMaxHoleDiameter = new QSpinBox(tab_5);
        EditMaxHoleDiameter->setObjectName("EditMaxHoleDiameter");
        EditMaxHoleDiameter->setGeometry(QRect(140, 70, 91, 20));
        EditMaxHoleDiameter->setMinimum(-255);
        EditMaxHoleDiameter->setMaximum(255);
        label_18 = new QLabel(tab_5);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 70, 121, 21));
        label_18->setFrameShape(QFrame::Panel);
        label_18->setFrameShadow(QFrame::Sunken);
        label_18->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_20 = new QLabel(tab_5);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(10, 10, 121, 21));
        label_20->setFrameShape(QFrame::Panel);
        label_20->setFrameShadow(QFrame::Sunken);
        label_20->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditHoleBrightnessAsReference = new QSpinBox(tab_5);
        EditHoleBrightnessAsReference->setObjectName("EditHoleBrightnessAsReference");
        EditHoleBrightnessAsReference->setGeometry(QRect(140, 10, 91, 20));
        EditHoleBrightnessAsReference->setMinimum(-255);
        EditHoleBrightnessAsReference->setMaximum(255);
        tabWidgetInspect->addTab(tab_5, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        checkModeEnabled = new QCheckBox(tab_7);
        checkModeEnabled->setObjectName("checkModeEnabled");
        checkModeEnabled->setGeometry(QRect(10, 10, 141, 18));
        checkModeAbsoluteBright = new QCheckBox(tab_7);
        checkModeAbsoluteBright->setObjectName("checkModeAbsoluteBright");
        checkModeAbsoluteBright->setGeometry(QRect(10, 30, 141, 18));
        checkModeCenterBrightFromParts = new QCheckBox(tab_7);
        checkModeCenterBrightFromParts->setObjectName("checkModeCenterBrightFromParts");
        checkModeCenterBrightFromParts->setGeometry(QRect(10, 90, 211, 18));
        checkModeDynamicMask = new QCheckBox(tab_7);
        checkModeDynamicMask->setObjectName("checkModeDynamicMask");
        checkModeDynamicMask->setGeometry(QRect(10, 50, 141, 18));
        checkModeEnableHoleCheck = new QCheckBox(tab_7);
        checkModeEnableHoleCheck->setObjectName("checkModeEnableHoleCheck");
        checkModeEnableHoleCheck->setGeometry(QRect(10, 70, 211, 18));
        tabWidgetInspect->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_26 = new QLabel(tab_8);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(10, 70, 201, 21));
        label_26->setFrameShape(QFrame::Panel);
        label_26->setFrameShadow(QFrame::Sunken);
        label_26->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(tab_8);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(10, 40, 201, 21));
        label_25->setFrameShape(QFrame::Panel);
        label_25->setFrameShadow(QFrame::Sunken);
        label_25->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        EditAdjustWhite = new QSpinBox(tab_8);
        EditAdjustWhite->setObjectName("EditAdjustWhite");
        EditAdjustWhite->setGeometry(QRect(220, 70, 81, 22));
        EditAdjustWhite->setMaximum(255);
        EditAdjustBlack = new QSpinBox(tab_8);
        EditAdjustBlack->setObjectName("EditAdjustBlack");
        EditAdjustBlack->setGeometry(QRect(220, 40, 81, 22));
        EditAdjustBlack->setMaximum(255);
        tabWidgetInspect->addTab(tab_8, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        EditExpandForDynamicMask = new QSpinBox(tab);
        EditExpandForDynamicMask->setObjectName("EditExpandForDynamicMask");
        EditExpandForDynamicMask->setGeometry(QRect(170, 20, 91, 20));
        EditExpandForDynamicMask->setMinimum(-255);
        EditExpandForDynamicMask->setMaximum(255);
        label_19 = new QLabel(tab);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(40, 20, 121, 21));
        label_19->setFrameShape(QFrame::Panel);
        label_19->setFrameShadow(QFrame::Sunken);
        label_19->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabWidgetInspect->addTab(tab, QString());

        retranslateUi(CreateManualEulerRingL1Dialog);

        tabWidgetInspect->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CreateManualEulerRingL1Dialog);
    } // setupUi

    void retranslateUi(QDialog *CreateManualEulerRingL1Dialog)
    {
        CreateManualEulerRingL1Dialog->setWindowTitle(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Create Manual EulerRingL1", nullptr));
        ButtonCancel->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Cancel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetLibList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetLibList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Name", nullptr));
        ButtonOK->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "OK", nullptr));
        label_6->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\244\234\n"
"\346\237\273", nullptr));
        label->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Item name", nullptr));
        label_23->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\232\227\345\201\264", nullptr));
        label_22->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "OK\350\274\235\345\272\246\347\257\204\345\233\262", nullptr));
        label_21->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\230\216\345\201\264", nullptr));
        label_37->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\216\245\347\266\232\350\267\235\351\233\242", nullptr));
        labelUnitName_8->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "mm", nullptr));
        labelUnitName_3->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "mm", nullptr));
        checkModeEnableOpenRingCheck->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\345\272\247\345\210\207\343\202\214\346\244\234\346\237\273\343\202\222\345\256\237\350\241\214", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_6), QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Ring", nullptr));
        label_17->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\234\200\345\260\217\347\251\264\345\276\204", nullptr));
        label_32->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\347\251\264\347\247\273\345\213\225\347\257\204\345\233\262", nullptr));
        labelUnitName_2->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "mm", nullptr));
        label_18->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\234\200\345\244\247\347\251\264\345\276\204", nullptr));
        label_20->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\345\217\202\350\200\203\350\274\235\345\272\246", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_5), QCoreApplication::translate("CreateManualEulerRingL1Dialog", "Hole", nullptr));
        checkModeEnabled->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\244\234\346\237\273\346\234\211\345\212\271", nullptr));
        checkModeAbsoluteBright->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\347\265\266\345\257\276\350\274\235\345\272\246", nullptr));
        checkModeCenterBrightFromParts->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\351\203\250\345\223\201\343\201\213\343\202\211\350\274\235\345\272\246\343\202\222\346\212\275\345\207\272\343\201\231\343\202\213", nullptr));
        checkModeDynamicMask->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\345\256\237\350\241\214\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220", nullptr));
        checkModeEnableHoleCheck->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\347\251\264\345\210\244\345\256\232\343\202\222\350\241\214\343\201\206", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_7), QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\345\261\236\346\200\247", nullptr));
        label_26->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\230\216\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        label_25->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\346\232\227\345\201\264\343\200\200\346\234\200\345\244\247\350\243\234\346\255\243\350\274\235\345\272\246\351\207\217", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab_8), QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\350\243\234\346\255\243", nullptr));
        label_19->setText(QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\343\203\236\343\202\271\343\202\257\350\206\250\345\274\265\343\203\211\343\203\203\343\203\210", nullptr));
        tabWidgetInspect->setTabText(tabWidgetInspect->indexOf(tab), QCoreApplication::translate("CreateManualEulerRingL1Dialog", "\343\203\236\343\202\271\343\202\257\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateManualEulerRingL1Dialog: public Ui_CreateManualEulerRingL1Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEMANUALEULERRINGL1DIALOG_H
