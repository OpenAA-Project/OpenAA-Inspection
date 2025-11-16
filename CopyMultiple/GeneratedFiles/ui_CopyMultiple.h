/********************************************************************************
** Form generated from reading UI file 'CopyMultiple.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPYMULTIPLE_H
#define UI_COPYMULTIPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CopyMultipleClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *label;
    QLineEdit *lineEditSourcePath;
    QPushButton *pushButtonSourcePath;
    QLabel *label_2;
    QFrame *frame_2;
    QLabel *label_3;
    QPushButton *pushButtonLoadFilter;
    QPushButton *pushButtonSaveFilter;
    QTableWidget *tableWidgetSearchFilter;
    QTableWidget *tableWidgetExcludedFilter;
    QPushButton *pushButtonAllFiles;
    QPushButton *pushButtonForRelease;
    QPushButton *pushButtonAllClear;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QFrame *frame_3;
    QCheckBox *checkBoxCopyNewer;
    QFrame *frame_4;
    QLabel *label_6;
    QFrame *frameDestination;
    QPushButton *pushButtonStartCopy;
    QPushButton *pushButtonStopCopy;

    void setupUi(QMainWindow *CopyMultipleClass)
    {
        if (CopyMultipleClass->objectName().isEmpty())
            CopyMultipleClass->setObjectName("CopyMultipleClass");
        CopyMultipleClass->resize(490, 690);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CopyMultipleClass->sizePolicy().hasHeightForWidth());
        CopyMultipleClass->setSizePolicy(sizePolicy);
        CopyMultipleClass->setMinimumSize(QSize(490, 690));
        CopyMultipleClass->setMaximumSize(QSize(490, 690));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        CopyMultipleClass->setFont(font);
        centralWidget = new QWidget(CopyMultipleClass);
        centralWidget->setObjectName("centralWidget");
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 471, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 391, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        lineEditSourcePath = new QLineEdit(frame);
        lineEditSourcePath->setObjectName("lineEditSourcePath");
        lineEditSourcePath->setGeometry(QRect(20, 50, 391, 21));
        pushButtonSourcePath = new QPushButton(frame);
        pushButtonSourcePath->setObjectName("pushButtonSourcePath");
        pushButtonSourcePath->setGeometry(QRect(420, 50, 31, 23));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 471, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_2->setAlignment(Qt::AlignCenter);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(20, 80, 431, 331));
        frame_2->setFont(font);
        frame_2->setStyleSheet(QString::fromUtf8(""));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 431, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(14);
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonLoadFilter = new QPushButton(frame_2);
        pushButtonLoadFilter->setObjectName("pushButtonLoadFilter");
        pushButtonLoadFilter->setGeometry(QRect(350, 10, 55, 28));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(11);
        pushButtonLoadFilter->setFont(font2);
        pushButtonLoadFilter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 14px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonSaveFilter = new QPushButton(frame_2);
        pushButtonSaveFilter->setObjectName("pushButtonSaveFilter");
        pushButtonSaveFilter->setGeometry(QRect(290, 10, 55, 28));
        pushButtonSaveFilter->setFont(font2);
        pushButtonSaveFilter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 14px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        tableWidgetSearchFilter = new QTableWidget(frame_2);
        if (tableWidgetSearchFilter->columnCount() < 1)
            tableWidgetSearchFilter->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetSearchFilter->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidgetSearchFilter->rowCount() < 100)
            tableWidgetSearchFilter->setRowCount(100);
        tableWidgetSearchFilter->setObjectName("tableWidgetSearchFilter");
        tableWidgetSearchFilter->setGeometry(QRect(0, 50, 211, 231));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(9);
        tableWidgetSearchFilter->setFont(font3);
        tableWidgetSearchFilter->setStyleSheet(QString::fromUtf8(""));
        tableWidgetSearchFilter->setRowCount(100);
        tableWidgetSearchFilter->horizontalHeader()->setDefaultSectionSize(160);
        tableWidgetExcludedFilter = new QTableWidget(frame_2);
        if (tableWidgetExcludedFilter->columnCount() < 1)
            tableWidgetExcludedFilter->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetExcludedFilter->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        if (tableWidgetExcludedFilter->rowCount() < 100)
            tableWidgetExcludedFilter->setRowCount(100);
        tableWidgetExcludedFilter->setObjectName("tableWidgetExcludedFilter");
        tableWidgetExcludedFilter->setGeometry(QRect(220, 50, 211, 231));
        tableWidgetExcludedFilter->setFont(font);
        tableWidgetExcludedFilter->setRowCount(100);
        tableWidgetExcludedFilter->horizontalHeader()->setDefaultSectionSize(160);
        pushButtonAllFiles = new QPushButton(frame_2);
        pushButtonAllFiles->setObjectName("pushButtonAllFiles");
        pushButtonAllFiles->setGeometry(QRect(8, 10, 75, 28));
        pushButtonAllFiles->setFont(font2);
        pushButtonAllFiles->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 14px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonForRelease = new QPushButton(frame_2);
        pushButtonForRelease->setObjectName("pushButtonForRelease");
        pushButtonForRelease->setGeometry(QRect(90, 10, 78, 28));
        pushButtonForRelease->setFont(font3);
        pushButtonForRelease->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 14px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        pushButtonAllClear = new QPushButton(frame_2);
        pushButtonAllClear->setObjectName("pushButtonAllClear");
        pushButtonAllClear->setGeometry(QRect(180, 290, 75, 27));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(13);
        font4.setBold(false);
        pushButtonAllClear->setFont(font4);
        pushButtonAllClear->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 13px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));\n"
"}\n"
"QPushButton:pressed { 	\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));\n"
"}"));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 290, 111, 30));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Arial")});
        font5.setPointSize(23);
        font5.setBold(false);
        label_4->setFont(font5);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(310, 300, 71, 22));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Arial")});
        font6.setPointSize(15);
        font6.setBold(false);
        label_5->setFont(font6);
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(330, 275, 16, 25));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Arial")});
        font7.setPointSize(15);
        label_7->setFont(font7);
        label_7->setStyleSheet(QString::fromUtf8(""));
        label_7->setAlignment(Qt::AlignCenter);
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(320, 640, 161, 41));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        checkBoxCopyNewer = new QCheckBox(frame_3);
        checkBoxCopyNewer->setObjectName("checkBoxCopyNewer");
        checkBoxCopyNewer->setGeometry(QRect(20, 10, 111, 20));
        checkBoxCopyNewer->setChecked(true);
        frame_4 = new QFrame(centralWidget);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(10, 430, 471, 201));
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(frame_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(0, 0, 471, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);
        frameDestination = new QFrame(frame_4);
        frameDestination->setObjectName("frameDestination");
        frameDestination->setGeometry(QRect(10, 30, 451, 161));
        frameDestination->setFrameShape(QFrame::NoFrame);
        frameDestination->setFrameShadow(QFrame::Raised);
        pushButtonStartCopy = new QPushButton(centralWidget);
        pushButtonStartCopy->setObjectName("pushButtonStartCopy");
        pushButtonStartCopy->setGeometry(QRect(80, 640, 160, 41));
        QPalette palette;
        QLinearGradient gradient(0.0113636, 0, 0, 1);
        gradient.setSpread(QGradient::Spread::PadSpread);
        gradient.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(203, 236, 255, 255));
        gradient.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush(gradient);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        QLinearGradient gradient1(0.0113636, 0, 0, 1);
        gradient1.setSpread(QGradient::Spread::PadSpread);
        gradient1.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient1.setColorAt(0, QColor(203, 236, 255, 255));
        gradient1.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush2(gradient1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush2);
        QLinearGradient gradient2(0.0113636, 0, 0, 1);
        gradient2.setSpread(QGradient::Spread::PadSpread);
        gradient2.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient2.setColorAt(0, QColor(203, 236, 255, 255));
        gradient2.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush3(gradient2);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush3);
        QLinearGradient gradient3(0.0113636, 0, 0, 1);
        gradient3.setSpread(QGradient::Spread::PadSpread);
        gradient3.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient3.setColorAt(0, QColor(203, 236, 255, 255));
        gradient3.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush4(gradient3);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        QLinearGradient gradient4(0.0113636, 0, 0, 1);
        gradient4.setSpread(QGradient::Spread::PadSpread);
        gradient4.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient4.setColorAt(0, QColor(203, 236, 255, 255));
        gradient4.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush5(gradient4);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush5);
        QLinearGradient gradient5(0.0113636, 0, 0, 1);
        gradient5.setSpread(QGradient::Spread::PadSpread);
        gradient5.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient5.setColorAt(0, QColor(203, 236, 255, 255));
        gradient5.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush6(gradient5);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush6);
        QLinearGradient gradient6(0.0113636, 0, 0, 1);
        gradient6.setSpread(QGradient::Spread::PadSpread);
        gradient6.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient6.setColorAt(0, QColor(203, 236, 255, 255));
        gradient6.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush7(gradient6);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush7);
        QBrush brush8(QColor(106, 104, 100, 255));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush8);
        QLinearGradient gradient7(0.0113636, 0, 0, 1);
        gradient7.setSpread(QGradient::Spread::PadSpread);
        gradient7.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient7.setColorAt(0, QColor(203, 236, 255, 255));
        gradient7.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush9(gradient7);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush9);
        QLinearGradient gradient8(0.0113636, 0, 0, 1);
        gradient8.setSpread(QGradient::Spread::PadSpread);
        gradient8.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient8.setColorAt(0, QColor(203, 236, 255, 255));
        gradient8.setColorAt(1, QColor(5, 161, 255, 255));
        QBrush brush10(gradient8);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush10);
        pushButtonStartCopy->setPalette(palette);
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Arial")});
        font8.setPointSize(22);
        font8.setBold(false);
        pushButtonStartCopy->setFont(font8);
        pushButtonStartCopy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 20px;\n"
"	border-color: rgb(70, 70, 70);\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(203, 236, 255, 255), stop:1 rgba(5, 161, 255, 255));\n"
"}\n"
"QPushButton:pressed { 		\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(150, 216, 255, 255), stop:1 rgba(5, 161, 255, 255));\n"
"}"));
        pushButtonStopCopy = new QPushButton(centralWidget);
        pushButtonStopCopy->setObjectName("pushButtonStopCopy");
        pushButtonStopCopy->setGeometry(QRect(80, 640, 160, 41));
        QPalette palette1;
        QLinearGradient gradient9(0.0113636, 0, 0, 1);
        gradient9.setSpread(QGradient::Spread::PadSpread);
        gradient9.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient9.setColorAt(0, QColor(255, 203, 203, 255));
        gradient9.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush11(gradient9);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush11);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        QLinearGradient gradient10(0.0113636, 0, 0, 1);
        gradient10.setSpread(QGradient::Spread::PadSpread);
        gradient10.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient10.setColorAt(0, QColor(255, 203, 203, 255));
        gradient10.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush12(gradient10);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush12);
        QLinearGradient gradient11(0.0113636, 0, 0, 1);
        gradient11.setSpread(QGradient::Spread::PadSpread);
        gradient11.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient11.setColorAt(0, QColor(255, 203, 203, 255));
        gradient11.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush13(gradient11);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush13);
        QLinearGradient gradient12(0.0113636, 0, 0, 1);
        gradient12.setSpread(QGradient::Spread::PadSpread);
        gradient12.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient12.setColorAt(0, QColor(255, 203, 203, 255));
        gradient12.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush14(gradient12);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush14);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        QLinearGradient gradient13(0.0113636, 0, 0, 1);
        gradient13.setSpread(QGradient::Spread::PadSpread);
        gradient13.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient13.setColorAt(0, QColor(255, 203, 203, 255));
        gradient13.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush15(gradient13);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush15);
        QLinearGradient gradient14(0.0113636, 0, 0, 1);
        gradient14.setSpread(QGradient::Spread::PadSpread);
        gradient14.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient14.setColorAt(0, QColor(255, 203, 203, 255));
        gradient14.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush16(gradient14);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush16);
        QLinearGradient gradient15(0.0113636, 0, 0, 1);
        gradient15.setSpread(QGradient::Spread::PadSpread);
        gradient15.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient15.setColorAt(0, QColor(255, 203, 203, 255));
        gradient15.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush17(gradient15);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush17);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush8);
        QLinearGradient gradient16(0.0113636, 0, 0, 1);
        gradient16.setSpread(QGradient::Spread::PadSpread);
        gradient16.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient16.setColorAt(0, QColor(255, 203, 203, 255));
        gradient16.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush18(gradient16);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush18);
        QLinearGradient gradient17(0.0113636, 0, 0, 1);
        gradient17.setSpread(QGradient::Spread::PadSpread);
        gradient17.setCoordinateMode(QGradient::CoordinateMode::ObjectBoundingMode);
        gradient17.setColorAt(0, QColor(255, 203, 203, 255));
        gradient17.setColorAt(1, QColor(255, 5, 5, 255));
        QBrush brush19(gradient17);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush19);
        pushButtonStopCopy->setPalette(palette1);
        pushButtonStopCopy->setFont(font8);
        pushButtonStopCopy->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-radius: 20px;\n"
"	border-color: rgb(70, 70, 70);			\n"
"	\n"
"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(255, 203, 203, 255), stop:1 rgba(255, 5, 5, 255));\n"
"}\n"
"QPushButton:pressed { 		\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(255, 83, 83, 255), stop:1 rgba(255, 5, 5, 255));\n"
"}"));
        CopyMultipleClass->setCentralWidget(centralWidget);
        pushButtonStopCopy->raise();
        pushButtonStartCopy->raise();
        frame->raise();
        frame_3->raise();
        frame_4->raise();

        retranslateUi(CopyMultipleClass);

        QMetaObject::connectSlotsByName(CopyMultipleClass);
    } // setupUi

    void retranslateUi(QMainWindow *CopyMultipleClass)
    {
        CopyMultipleClass->setWindowTitle(QCoreApplication::translate("CopyMultipleClass", "CopyMultiple", nullptr));
        label->setText(QCoreApplication::translate("CopyMultipleClass", "Source main path", nullptr));
        pushButtonSourcePath->setText(QCoreApplication::translate("CopyMultipleClass", "...", nullptr));
        label_2->setText(QCoreApplication::translate("CopyMultipleClass", "Source", nullptr));
        label_3->setText(QCoreApplication::translate("CopyMultipleClass", "File Filter", nullptr));
        pushButtonLoadFilter->setText(QCoreApplication::translate("CopyMultipleClass", "Load", nullptr));
        pushButtonSaveFilter->setText(QCoreApplication::translate("CopyMultipleClass", "Save", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetSearchFilter->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CopyMultipleClass", "Search file filter", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetExcludedFilter->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CopyMultipleClass", "Excluded file filter", nullptr));
        pushButtonAllFiles->setText(QCoreApplication::translate("CopyMultipleClass", "All Files", nullptr));
        pushButtonForRelease->setText(QCoreApplication::translate("CopyMultipleClass", "For Release", nullptr));
        pushButtonAllClear->setText(QCoreApplication::translate("CopyMultipleClass", "All Clear", nullptr));
        label_4->setText(QCoreApplication::translate("CopyMultipleClass", "Copy \342\206\223", nullptr));
        label_5->setText(QCoreApplication::translate("CopyMultipleClass", "NoCopy", nullptr));
        label_7->setText(QCoreApplication::translate("CopyMultipleClass", "\342\206\223", nullptr));
        checkBoxCopyNewer->setText(QCoreApplication::translate("CopyMultipleClass", "Copy newer file", nullptr));
        label_6->setText(QCoreApplication::translate("CopyMultipleClass", "Destination", nullptr));
        pushButtonStartCopy->setText(QCoreApplication::translate("CopyMultipleClass", "Start copy", nullptr));
        pushButtonStopCopy->setText(QCoreApplication::translate("CopyMultipleClass", "Stop copy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CopyMultipleClass: public Ui_CopyMultipleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYMULTIPLE_H
