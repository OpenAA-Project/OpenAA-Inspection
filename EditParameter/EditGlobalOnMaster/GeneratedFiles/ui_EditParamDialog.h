/********************************************************************************
** Form generated from reading UI file 'EditParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPARAMDIALOG_H
#define UI_EDITPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditParamDialog
{
public:
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditMasterCode;
    QLineEdit *lineEditMasterName;
    QSpinBox *spinBoxMachineCode;
    QSpinBox *spinBoxWorkerID;
    QPushButton *pushButtonSelectMachine;
    QPushButton *pushButtonSelectWorker;
    QListWidget *listWidgetPage;
    QPushButton *pushButtonUpdate;
    QPushButton *pushButtonCancel;
    QTabWidget *tabWidget;
    QWidget *Global;
    QFrame *framePanel;
    QWidget *Strategy;
    QFrame *frameFormStrategy;
    QWidget *Communicate;
    QFrame *frameFormComm;

    void setupUi(QDialog *EditParamDialog)
    {
        if (EditParamDialog->objectName().isEmpty())
            EditParamDialog->setObjectName("EditParamDialog");
        EditParamDialog->resize(726, 661);
        frame = new QFrame(EditParamDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 10, 631, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 131, 21));
        label->setFrameShape(QFrame::Panel);
        label->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 131, 21));
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 131, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        lineEditMasterCode = new QLineEdit(frame);
        lineEditMasterCode->setObjectName("lineEditMasterCode");
        lineEditMasterCode->setGeometry(QRect(140, 10, 91, 20));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        QBrush brush1(QColor(212, 208, 200, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditMasterCode->setPalette(palette);
        lineEditMasterCode->setReadOnly(true);
        lineEditMasterName = new QLineEdit(frame);
        lineEditMasterName->setObjectName("lineEditMasterName");
        lineEditMasterName->setGeometry(QRect(230, 10, 381, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        lineEditMasterName->setPalette(palette1);
        lineEditMasterName->setReadOnly(true);
        spinBoxMachineCode = new QSpinBox(frame);
        spinBoxMachineCode->setObjectName("spinBoxMachineCode");
        spinBoxMachineCode->setGeometry(QRect(140, 30, 91, 22));
        spinBoxMachineCode->setMaximum(99999999);
        spinBoxWorkerID = new QSpinBox(frame);
        spinBoxWorkerID->setObjectName("spinBoxWorkerID");
        spinBoxWorkerID->setGeometry(QRect(140, 50, 91, 22));
        spinBoxWorkerID->setMaximum(99999999);
        pushButtonSelectMachine = new QPushButton(frame);
        pushButtonSelectMachine->setObjectName("pushButtonSelectMachine");
        pushButtonSelectMachine->setGeometry(QRect(230, 30, 31, 23));
        pushButtonSelectWorker = new QPushButton(frame);
        pushButtonSelectWorker->setObjectName("pushButtonSelectWorker");
        pushButtonSelectWorker->setGeometry(QRect(230, 50, 31, 23));
        listWidgetPage = new QListWidget(EditParamDialog);
        new QListWidgetItem(listWidgetPage);
        new QListWidgetItem(listWidgetPage);
        listWidgetPage->setObjectName("listWidgetPage");
        listWidgetPage->setGeometry(QRect(10, 90, 91, 511));
        pushButtonUpdate = new QPushButton(EditParamDialog);
        pushButtonUpdate->setObjectName("pushButtonUpdate");
        pushButtonUpdate->setGeometry(QRect(100, 620, 101, 31));
        pushButtonCancel = new QPushButton(EditParamDialog);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(530, 620, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        tabWidget = new QTabWidget(EditParamDialog);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(100, 90, 621, 511));
        Global = new QWidget();
        Global->setObjectName("Global");
        framePanel = new QFrame(Global);
        framePanel->setObjectName("framePanel");
        framePanel->setGeometry(QRect(0, 0, 611, 481));
        framePanel->setFrameShape(QFrame::StyledPanel);
        framePanel->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(Global, QString());
        Strategy = new QWidget();
        Strategy->setObjectName("Strategy");
        frameFormStrategy = new QFrame(Strategy);
        frameFormStrategy->setObjectName("frameFormStrategy");
        frameFormStrategy->setGeometry(QRect(0, 0, 484, 484));
        frameFormStrategy->setFrameShape(QFrame::Panel);
        frameFormStrategy->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(Strategy, QString());
        Communicate = new QWidget();
        Communicate->setObjectName("Communicate");
        frameFormComm = new QFrame(Communicate);
        frameFormComm->setObjectName("frameFormComm");
        frameFormComm->setGeometry(QRect(0, 0, 484, 484));
        frameFormComm->setFrameShape(QFrame::Panel);
        frameFormComm->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(Communicate, QString());

        retranslateUi(EditParamDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EditParamDialog);
    } // setupUi

    void retranslateUi(QDialog *EditParamDialog)
    {
        EditParamDialog->setWindowTitle(QCoreApplication::translate("EditParamDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("EditParamDialog", "Machine code", nullptr));
        label_2->setText(QCoreApplication::translate("EditParamDialog", "Worker ID", nullptr));
        label_3->setText(QCoreApplication::translate("EditParamDialog", "Master code / Name", nullptr));
        pushButtonSelectMachine->setText(QCoreApplication::translate("EditParamDialog", "...", nullptr));
        pushButtonSelectWorker->setText(QCoreApplication::translate("EditParamDialog", "...", nullptr));

        const bool __sortingEnabled = listWidgetPage->isSortingEnabled();
        listWidgetPage->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidgetPage->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("EditParamDialog", "MasterData", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidgetPage->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("EditParamDialog", "Page 0", nullptr));
        listWidgetPage->setSortingEnabled(__sortingEnabled);

        pushButtonUpdate->setText(QCoreApplication::translate("EditParamDialog", "UPDATE", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("EditParamDialog", "Cancel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Global), QCoreApplication::translate("EditParamDialog", "Global", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Strategy), QCoreApplication::translate("EditParamDialog", "Strategy", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Communicate), QCoreApplication::translate("EditParamDialog", "Communicate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditParamDialog: public Ui_EditParamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPARAMDIALOG_H
