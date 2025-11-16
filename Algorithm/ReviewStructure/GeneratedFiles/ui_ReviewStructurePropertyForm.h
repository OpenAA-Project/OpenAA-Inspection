/********************************************************************************
** Form generated from reading UI file 'ReviewStructurePropertyForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVIEWSTRUCTUREPROPERTYFORM_H
#define UI_REVIEWSTRUCTUREPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ReviewStructureClass
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *sbPreNGImageLoadLength;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_10;
    QComboBox *cbMasterImageQuality;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *cbVRSOperationEnable;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QFrame *line;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *cbHistorySortOrder;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *cbNGNailSortOrder;
    QGroupBox *gbSaveNGImageFileFormat;
    QGridLayout *gridLayout;
    QLineEdit *leSaveNGImageFileFormat;
    QLabel *label_7;
    QTableWidget *twSaveNGImageFileFormatMacroTable;
    QGroupBox *gbXMLServer;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *leXMLServerIPAddress;
    QLineEdit *leXMLServerPortNo;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *leNGImagePath;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout_5;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBoxCSVMagnificationX;
    QSpinBox *spinBoxCSVOffsetX;
    QLabel *label_11;
    QSpinBox *spinBoxCSVOffsetY;
    QCheckBox *checkBoxCSVReverseX;
    QCheckBox *checkBoxCSVReverseY;
    QLabel *label_10;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBoxCSVMagnificationY;
    QLabel *label_14;
    QLineEdit *leDirectoryToSaveCSV;
    QCheckBox *checkBoxCSVUnitMM;
    QLabel *label_9;

    void setupUi(QDialog *ReviewStructureClass)
    {
        if (ReviewStructureClass->objectName().isEmpty())
            ReviewStructureClass->setObjectName("ReviewStructureClass");
        ReviewStructureClass->resize(635, 975);
        gridLayout_4 = new QGridLayout(ReviewStructureClass);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(ReviewStructureClass);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        sbPreNGImageLoadLength = new QSpinBox(ReviewStructureClass);
        sbPreNGImageLoadLength->setObjectName("sbPreNGImageLoadLength");

        horizontalLayout_3->addWidget(sbPreNGImageLoadLength);


        gridLayout_4->addLayout(horizontalLayout_3, 2, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_8 = new QLabel(ReviewStructureClass);
        label_8->setObjectName("label_8");

        horizontalLayout_4->addWidget(label_8);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        cbMasterImageQuality = new QComboBox(ReviewStructureClass);
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->addItem(QString());
        cbMasterImageQuality->setObjectName("cbMasterImageQuality");

        horizontalLayout_4->addWidget(cbMasterImageQuality);


        gridLayout_4->addLayout(horizontalLayout_4, 3, 0, 1, 2);

        line_2 = new QFrame(ReviewStructureClass);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_4->addWidget(line_2, 4, 0, 1, 2);

        horizontalSpacer_11 = new QSpacerItem(424, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_11, 5, 0, 1, 1);

        cbVRSOperationEnable = new QCheckBox(ReviewStructureClass);
        cbVRSOperationEnable->setObjectName("cbVRSOperationEnable");

        gridLayout_4->addWidget(cbVRSOperationEnable, 5, 1, 1, 1);

        groupBox = new QGroupBox(ReviewStructureClass);
        groupBox->setObjectName("groupBox");
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        line = new QFrame(groupBox);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_3->addWidget(line, 1, 0, 1, 6);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout_3->addWidget(label_2, 3, 1, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 3, 3, 1, 1);

        cbHistorySortOrder = new QComboBox(groupBox);
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->addItem(QString());
        cbHistorySortOrder->setObjectName("cbHistorySortOrder");
        cbHistorySortOrder->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_3->addWidget(cbHistorySortOrder, 3, 4, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_3->addWidget(label, 0, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 3, 1, 1);

        cbNGNailSortOrder = new QComboBox(groupBox);
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->addItem(QString());
        cbNGNailSortOrder->setObjectName("cbNGNailSortOrder");
        cbNGNailSortOrder->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout_3->addWidget(cbNGNailSortOrder, 0, 4, 1, 2);

        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);

        gridLayout_4->addWidget(groupBox, 0, 0, 1, 2);

        gbSaveNGImageFileFormat = new QGroupBox(ReviewStructureClass);
        gbSaveNGImageFileFormat->setObjectName("gbSaveNGImageFileFormat");
        gridLayout = new QGridLayout(gbSaveNGImageFileFormat);
        gridLayout->setObjectName("gridLayout");
        leSaveNGImageFileFormat = new QLineEdit(gbSaveNGImageFileFormat);
        leSaveNGImageFileFormat->setObjectName("leSaveNGImageFileFormat");

        gridLayout->addWidget(leSaveNGImageFileFormat, 1, 1, 1, 1);

        label_7 = new QLabel(gbSaveNGImageFileFormat);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        twSaveNGImageFileFormatMacroTable = new QTableWidget(gbSaveNGImageFileFormat);
        if (twSaveNGImageFileFormatMacroTable->columnCount() < 2)
            twSaveNGImageFileFormatMacroTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (twSaveNGImageFileFormatMacroTable->rowCount() < 8)
            twSaveNGImageFileFormatMacroTable->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(0, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(0, 1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(1, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(1, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(2, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(2, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(3, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(3, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(4, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(4, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(5, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(5, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(6, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(6, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(7, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        twSaveNGImageFileFormatMacroTable->setItem(7, 1, __qtablewidgetitem17);
        twSaveNGImageFileFormatMacroTable->setObjectName("twSaveNGImageFileFormatMacroTable");
        twSaveNGImageFileFormatMacroTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twSaveNGImageFileFormatMacroTable->setTabKeyNavigation(false);
        twSaveNGImageFileFormatMacroTable->setProperty("showDropIndicator", QVariant(false));
        twSaveNGImageFileFormatMacroTable->setSortingEnabled(true);
        twSaveNGImageFileFormatMacroTable->setWordWrap(true);
        twSaveNGImageFileFormatMacroTable->setCornerButtonEnabled(true);
        twSaveNGImageFileFormatMacroTable->setRowCount(8);
        twSaveNGImageFileFormatMacroTable->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(twSaveNGImageFileFormatMacroTable, 5, 0, 1, 3);


        gridLayout_4->addWidget(gbSaveNGImageFileFormat, 1, 0, 1, 2);

        gbXMLServer = new QGroupBox(ReviewStructureClass);
        gbXMLServer->setObjectName("gbXMLServer");
        gridLayout_2 = new QGridLayout(gbXMLServer);
        gridLayout_2->setObjectName("gridLayout_2");
        label_5 = new QLabel(gbXMLServer);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        leXMLServerIPAddress = new QLineEdit(gbXMLServer);
        leXMLServerIPAddress->setObjectName("leXMLServerIPAddress");

        gridLayout_2->addWidget(leXMLServerIPAddress, 0, 3, 1, 1);

        leXMLServerPortNo = new QLineEdit(gbXMLServer);
        leXMLServerPortNo->setObjectName("leXMLServerPortNo");

        gridLayout_2->addWidget(leXMLServerPortNo, 1, 3, 1, 1);

        label_6 = new QLabel(gbXMLServer);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 1, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 2, 0, 1, 1);

        label_3 = new QLabel(gbXMLServer);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 2, 1, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 2, 2, 1, 1);

        leNGImagePath = new QLineEdit(gbXMLServer);
        leNGImagePath->setObjectName("leNGImagePath");

        gridLayout_2->addWidget(leNGImagePath, 2, 3, 1, 1);

        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 1);

        gridLayout_4->addWidget(gbXMLServer, 6, 0, 1, 2);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName("hboxLayout");
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(ReviewStructureClass);
        okButton->setObjectName("okButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/flash_swf_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        okButton->setIcon(icon);

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(ReviewStructureClass);
        cancelButton->setObjectName("cancelButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        cancelButton->setIcon(icon1);

        hboxLayout->addWidget(cancelButton);


        gridLayout_4->addLayout(hboxLayout, 8, 0, 1, 2);

        gridGroupBox = new QGroupBox(ReviewStructureClass);
        gridGroupBox->setObjectName("gridGroupBox");
        gridGroupBox->setCheckable(true);
        gridLayout_5 = new QGridLayout(gridGroupBox);
        gridLayout_5->setObjectName("gridLayout_5");
        frame = new QFrame(gridGroupBox);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setObjectName("gridLayout_6");
        label_12 = new QLabel(frame);
        label_12->setObjectName("label_12");

        gridLayout_6->addWidget(label_12, 0, 0, 1, 1);

        doubleSpinBoxCSVMagnificationX = new QDoubleSpinBox(frame);
        doubleSpinBoxCSVMagnificationX->setObjectName("doubleSpinBoxCSVMagnificationX");
        doubleSpinBoxCSVMagnificationX->setDecimals(6);
        doubleSpinBoxCSVMagnificationX->setMinimum(-99.000000000000000);

        gridLayout_6->addWidget(doubleSpinBoxCSVMagnificationX, 0, 1, 1, 1);

        spinBoxCSVOffsetX = new QSpinBox(frame);
        spinBoxCSVOffsetX->setObjectName("spinBoxCSVOffsetX");
        spinBoxCSVOffsetX->setMinimum(-999999999);
        spinBoxCSVOffsetX->setMaximum(999999999);

        gridLayout_6->addWidget(spinBoxCSVOffsetX, 2, 1, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");

        gridLayout_6->addWidget(label_11, 3, 0, 1, 1);

        spinBoxCSVOffsetY = new QSpinBox(frame);
        spinBoxCSVOffsetY->setObjectName("spinBoxCSVOffsetY");
        spinBoxCSVOffsetY->setMinimum(-999999999);
        spinBoxCSVOffsetY->setMaximum(999999999);

        gridLayout_6->addWidget(spinBoxCSVOffsetY, 3, 1, 1, 1);

        checkBoxCSVReverseX = new QCheckBox(frame);
        checkBoxCSVReverseX->setObjectName("checkBoxCSVReverseX");

        gridLayout_6->addWidget(checkBoxCSVReverseX, 2, 2, 1, 1);

        checkBoxCSVReverseY = new QCheckBox(frame);
        checkBoxCSVReverseY->setObjectName("checkBoxCSVReverseY");

        gridLayout_6->addWidget(checkBoxCSVReverseY, 3, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName("label_10");

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName("label_13");

        gridLayout_6->addWidget(label_13, 1, 0, 1, 1);

        doubleSpinBoxCSVMagnificationY = new QDoubleSpinBox(frame);
        doubleSpinBoxCSVMagnificationY->setObjectName("doubleSpinBoxCSVMagnificationY");
        doubleSpinBoxCSVMagnificationY->setDecimals(6);
        doubleSpinBoxCSVMagnificationY->setMinimum(-99.000000000000000);

        gridLayout_6->addWidget(doubleSpinBoxCSVMagnificationY, 1, 1, 1, 1);

        label_14 = new QLabel(frame);
        label_14->setObjectName("label_14");

        gridLayout_6->addWidget(label_14, 4, 0, 1, 3);


        gridLayout_5->addWidget(frame, 3, 0, 1, 1);

        leDirectoryToSaveCSV = new QLineEdit(gridGroupBox);
        leDirectoryToSaveCSV->setObjectName("leDirectoryToSaveCSV");

        gridLayout_5->addWidget(leDirectoryToSaveCSV, 1, 0, 1, 1);

        checkBoxCSVUnitMM = new QCheckBox(gridGroupBox);
        checkBoxCSVUnitMM->setObjectName("checkBoxCSVUnitMM");

        gridLayout_5->addWidget(checkBoxCSVUnitMM, 2, 0, 1, 1);

        label_9 = new QLabel(gridGroupBox);
        label_9->setObjectName("label_9");

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);


        gridLayout_4->addWidget(gridGroupBox, 7, 0, 1, 2);


        retranslateUi(ReviewStructureClass);
        QObject::connect(okButton, &QPushButton::clicked, ReviewStructureClass, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, ReviewStructureClass, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ReviewStructureClass);
    } // setupUi

    void retranslateUi(QDialog *ReviewStructureClass)
    {
        ReviewStructureClass->setWindowTitle(QCoreApplication::translate("ReviewStructureClass", "ReviewStructureProperty", nullptr));
        label_4->setText(QCoreApplication::translate("ReviewStructureClass", "Pre NG image load length", nullptr));
        label_8->setText(QCoreApplication::translate("ReviewStructureClass", "Master image quality", nullptr));
        cbMasterImageQuality->setItemText(0, QCoreApplication::translate("ReviewStructureClass", "1/1", nullptr));
        cbMasterImageQuality->setItemText(1, QCoreApplication::translate("ReviewStructureClass", "1/2", nullptr));
        cbMasterImageQuality->setItemText(2, QCoreApplication::translate("ReviewStructureClass", "1/3", nullptr));
        cbMasterImageQuality->setItemText(3, QCoreApplication::translate("ReviewStructureClass", "1/4", nullptr));
        cbMasterImageQuality->setItemText(4, QCoreApplication::translate("ReviewStructureClass", "1/5", nullptr));
        cbMasterImageQuality->setItemText(5, QCoreApplication::translate("ReviewStructureClass", "1/6", nullptr));
        cbMasterImageQuality->setItemText(6, QCoreApplication::translate("ReviewStructureClass", "1/7", nullptr));
        cbMasterImageQuality->setItemText(7, QCoreApplication::translate("ReviewStructureClass", "1/8", nullptr));
        cbMasterImageQuality->setItemText(8, QCoreApplication::translate("ReviewStructureClass", "1/9", nullptr));
        cbMasterImageQuality->setItemText(9, QCoreApplication::translate("ReviewStructureClass", "1/10", nullptr));
        cbMasterImageQuality->setItemText(10, QCoreApplication::translate("ReviewStructureClass", "1/11", nullptr));
        cbMasterImageQuality->setItemText(11, QCoreApplication::translate("ReviewStructureClass", "1/12", nullptr));
        cbMasterImageQuality->setItemText(12, QCoreApplication::translate("ReviewStructureClass", "1/13", nullptr));
        cbMasterImageQuality->setItemText(13, QCoreApplication::translate("ReviewStructureClass", "1/14", nullptr));
        cbMasterImageQuality->setItemText(14, QCoreApplication::translate("ReviewStructureClass", "1/15", nullptr));
        cbMasterImageQuality->setItemText(15, QCoreApplication::translate("ReviewStructureClass", "1/16", nullptr));

        cbVRSOperationEnable->setText(QCoreApplication::translate("ReviewStructureClass", "VRS operation enable", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ReviewStructureClass", "Sort", nullptr));
        label_2->setText(QCoreApplication::translate("ReviewStructureClass", "History list", nullptr));
        cbHistorySortOrder->setItemText(0, QCoreApplication::translate("ReviewStructureClass", "InspectID(Lesser)", nullptr));
        cbHistorySortOrder->setItemText(1, QCoreApplication::translate("ReviewStructureClass", "InspectID(Greater)", nullptr));
        cbHistorySortOrder->setItemText(2, QCoreApplication::translate("ReviewStructureClass", "InspectTime(Lesser)", nullptr));
        cbHistorySortOrder->setItemText(3, QCoreApplication::translate("ReviewStructureClass", "InspectTime(Greater)", nullptr));
        cbHistorySortOrder->setItemText(4, QCoreApplication::translate("ReviewStructureClass", "NCCount(Lesser)", nullptr));
        cbHistorySortOrder->setItemText(5, QCoreApplication::translate("ReviewStructureClass", "NCCount(Greater)", nullptr));
        cbHistorySortOrder->setItemText(6, QCoreApplication::translate("ReviewStructureClass", "NCCountOnlyFront(Lesser)", nullptr));
        cbHistorySortOrder->setItemText(7, QCoreApplication::translate("ReviewStructureClass", "NCCountOnlyFront(Greater)", nullptr));
        cbHistorySortOrder->setItemText(8, QCoreApplication::translate("ReviewStructureClass", "NCCountOnlyBack(Lesser)", nullptr));
        cbHistorySortOrder->setItemText(9, QCoreApplication::translate("ReviewStructureClass", "NCCountOnlyBack(Greater)", nullptr));

        label->setText(QCoreApplication::translate("ReviewStructureClass", "NG image list", nullptr));
        cbNGNailSortOrder->setItemText(0, QCoreApplication::translate("ReviewStructureClass", "Y(Lesser)", nullptr));
        cbNGNailSortOrder->setItemText(1, QCoreApplication::translate("ReviewStructureClass", "Y(Greater)", nullptr));
        cbNGNailSortOrder->setItemText(2, QCoreApplication::translate("ReviewStructureClass", "X(Lesser)", nullptr));
        cbNGNailSortOrder->setItemText(3, QCoreApplication::translate("ReviewStructureClass", "X(Greater)", nullptr));
        cbNGNailSortOrder->setItemText(4, QCoreApplication::translate("ReviewStructureClass", "Lib(Lesser)", nullptr));
        cbNGNailSortOrder->setItemText(5, QCoreApplication::translate("ReviewStructureClass", "Lib(Greater)", nullptr));
        cbNGNailSortOrder->setItemText(6, QCoreApplication::translate("ReviewStructureClass", "NGCause(Lesser)", nullptr));
        cbNGNailSortOrder->setItemText(7, QCoreApplication::translate("ReviewStructureClass", "NGCause(Greater)", nullptr));
        cbNGNailSortOrder->setItemText(8, QCoreApplication::translate("ReviewStructureClass", "Area", nullptr));

        gbSaveNGImageFileFormat->setTitle(QCoreApplication::translate("ReviewStructureClass", "Save NG image format", nullptr));
        label_7->setText(QCoreApplication::translate("ReviewStructureClass", "format", nullptr));
        QTableWidgetItem *___qtablewidgetitem = twSaveNGImageFileFormatMacroTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("ReviewStructureClass", "Macro", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twSaveNGImageFileFormatMacroTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("ReviewStructureClass", "Detail", nullptr));

        const bool __sortingEnabled = twSaveNGImageFileFormatMacroTable->isSortingEnabled();
        twSaveNGImageFileFormatMacroTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem2 = twSaveNGImageFileFormatMacroTable->item(0, 0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("ReviewStructureClass", "%S", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twSaveNGImageFileFormatMacroTable->item(0, 1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("ReviewStructureClass", "Side Name(Front or Back)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twSaveNGImageFileFormatMacroTable->item(1, 0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("ReviewStructureClass", "%l", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = twSaveNGImageFileFormatMacroTable->item(1, 1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("ReviewStructureClass", "Lot Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twSaveNGImageFileFormatMacroTable->item(2, 0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("ReviewStructureClass", "%n", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = twSaveNGImageFileFormatMacroTable->item(2, 1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("ReviewStructureClass", "Number of row on NG list", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = twSaveNGImageFileFormatMacroTable->item(3, 0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("ReviewStructureClass", "%M", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = twSaveNGImageFileFormatMacroTable->item(3, 1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("ReviewStructureClass", "Master Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = twSaveNGImageFileFormatMacroTable->item(4, 0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("ReviewStructureClass", "%N", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = twSaveNGImageFileFormatMacroTable->item(4, 1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("ReviewStructureClass", "Number of row on NG list at current side", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = twSaveNGImageFileFormatMacroTable->item(5, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("ReviewStructureClass", "%m", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = twSaveNGImageFileFormatMacroTable->item(5, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("ReviewStructureClass", "Master Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = twSaveNGImageFileFormatMacroTable->item(6, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("ReviewStructureClass", "%i", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = twSaveNGImageFileFormatMacroTable->item(6, 1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("ReviewStructureClass", "Inspect ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = twSaveNGImageFileFormatMacroTable->item(7, 0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("ReviewStructureClass", "/", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = twSaveNGImageFileFormatMacroTable->item(7, 1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("ReviewStructureClass", "directory separator", nullptr));
        twSaveNGImageFileFormatMacroTable->setSortingEnabled(__sortingEnabled);

        gbXMLServer->setTitle(QCoreApplication::translate("ReviewStructureClass", "XML server connect", nullptr));
        label_5->setText(QCoreApplication::translate("ReviewStructureClass", "IP Address", nullptr));
        label_6->setText(QCoreApplication::translate("ReviewStructureClass", "Port No", nullptr));
        label_3->setText(QCoreApplication::translate("ReviewStructureClass", "Main path for NG image", nullptr));
        okButton->setText(QCoreApplication::translate("ReviewStructureClass", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("ReviewStructureClass", "Cancel", nullptr));
        gridGroupBox->setTitle(QCoreApplication::translate("ReviewStructureClass", "Directory for Save CSV", nullptr));
        label_12->setText(QCoreApplication::translate("ReviewStructureClass", "X magnification", nullptr));
        label_11->setText(QCoreApplication::translate("ReviewStructureClass", "Offset Y as Pixel", nullptr));
        checkBoxCSVReverseX->setText(QCoreApplication::translate("ReviewStructureClass", "ReverseX(Left:+  , Right:-)", nullptr));
        checkBoxCSVReverseY->setText(QCoreApplication::translate("ReviewStructureClass", "ReverseY(Top:+  , Bottomt:-)", nullptr));
        label_10->setText(QCoreApplication::translate("ReviewStructureClass", "Offset X as Pixel", nullptr));
        label_13->setText(QCoreApplication::translate("ReviewStructureClass", "Y magnification", nullptr));
        label_14->setText(QCoreApplication::translate("ReviewStructureClass", "Pos (X,Y) mm = { Pixel (x,y) * Mag (Zx,Zy) + Offset (OffX,OffY) } * UnitPerPixel", nullptr));
        checkBoxCSVUnitMM->setText(QCoreApplication::translate("ReviewStructureClass", "Unit mm", nullptr));
        label_9->setText(QCoreApplication::translate("ReviewStructureClass", "Directory", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReviewStructureClass: public Ui_ReviewStructureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVIEWSTRUCTUREPROPERTYFORM_H
