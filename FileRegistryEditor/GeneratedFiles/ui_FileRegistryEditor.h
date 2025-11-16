/********************************************************************************
** Form generated from reading UI file 'FileRegistryEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEREGISTRYEDITOR_H
#define UI_FILEREGISTRYEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileRegistryEditorClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEditPathName;
    QLabel *label;
    QSpinBox *spinBoxMachineID;
    QLabel *label_2;
    QPushButton *pushButtonSelectFolder;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;
    QFrame *frame;
    QLineEdit *lineEditHostName;
    QLineEdit *lineEditName;
    QLineEdit *lineEditDatabaseName;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *pushButtonLoadDatabase;
    QLabel *label_6;
    QLabel *label_8;
    QSpinBox *spinBoxDatabasePortNo;
    QLabel *label_7;
    QComboBox *comboBoxLanguage;
    QCheckBox *checkBoxEditMaltipleMachine;

    void setupUi(QMainWindow *FileRegistryEditorClass)
    {
        if (FileRegistryEditorClass->objectName().isEmpty())
            FileRegistryEditorClass->setObjectName("FileRegistryEditorClass");
        FileRegistryEditorClass->resize(600, 426);
        centralWidget = new QWidget(FileRegistryEditorClass);
        centralWidget->setObjectName("centralWidget");
        lineEditPathName = new QLineEdit(centralWidget);
        lineEditPathName->setObjectName("lineEditPathName");
        lineEditPathName->setGeometry(QRect(100, 10, 321, 20));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 50, 14));
        spinBoxMachineID = new QSpinBox(centralWidget);
        spinBoxMachineID->setObjectName("spinBoxMachineID");
        spinBoxMachineID->setGeometry(QRect(100, 60, 61, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 60, 61, 16));
        pushButtonSelectFolder = new QPushButton(centralWidget);
        pushButtonSelectFolder->setObjectName("pushButtonSelectFolder");
        pushButtonSelectFolder->setGeometry(QRect(440, 10, 75, 23));
        pushButtonOK = new QPushButton(centralWidget);
        pushButtonOK->setObjectName("pushButtonOK");
        pushButtonOK->setGeometry(QRect(110, 380, 101, 31));
        pushButtonCancel = new QPushButton(centralWidget);
        pushButtonCancel->setObjectName("pushButtonCancel");
        pushButtonCancel->setGeometry(QRect(390, 380, 101, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("J:/\346\244\234\346\237\273\347\224\273\351\235\242icon/flash_64.PNG"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButtonCancel->setIcon(icon);
        frame = new QFrame(centralWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(230, 50, 311, 281));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEditHostName = new QLineEdit(frame);
        lineEditHostName->setObjectName("lineEditHostName");
        lineEditHostName->setGeometry(QRect(10, 50, 291, 20));
        lineEditName = new QLineEdit(frame);
        lineEditName->setObjectName("lineEditName");
        lineEditName->setGeometry(QRect(10, 210, 291, 20));
        lineEditDatabaseName = new QLineEdit(frame);
        lineEditDatabaseName->setObjectName("lineEditDatabaseName");
        lineEditDatabaseName->setGeometry(QRect(10, 100, 291, 20));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 80, 291, 21));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 30, 291, 21));
        label_3->setFrameShape(QFrame::Panel);
        label_3->setFrameShadow(QFrame::Sunken);
        label_3->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 0, 311, 21));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButtonLoadDatabase = new QPushButton(frame);
        pushButtonLoadDatabase->setObjectName("pushButtonLoadDatabase");
        pushButtonLoadDatabase->setGeometry(QRect(110, 240, 91, 31));
        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 190, 291, 21));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(frame);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 130, 291, 21));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBoxDatabasePortNo = new QSpinBox(frame);
        spinBoxDatabasePortNo->setObjectName("spinBoxDatabasePortNo");
        spinBoxDatabasePortNo->setGeometry(QRect(50, 150, 91, 22));
        spinBoxDatabasePortNo->setMaximum(65535);
        spinBoxDatabasePortNo->setValue(3051);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 310, 61, 16));
        comboBoxLanguage = new QComboBox(centralWidget);
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->addItem(QString());
        comboBoxLanguage->setObjectName("comboBoxLanguage");
        comboBoxLanguage->setGeometry(QRect(100, 310, 111, 22));
        checkBoxEditMaltipleMachine = new QCheckBox(centralWidget);
        checkBoxEditMaltipleMachine->setObjectName("checkBoxEditMaltipleMachine");
        checkBoxEditMaltipleMachine->setGeometry(QRect(100, 340, 201, 18));
        FileRegistryEditorClass->setCentralWidget(centralWidget);

        retranslateUi(FileRegistryEditorClass);

        QMetaObject::connectSlotsByName(FileRegistryEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *FileRegistryEditorClass)
    {
        FileRegistryEditorClass->setWindowTitle(QCoreApplication::translate("FileRegistryEditorClass", "FileRegistryEditor", nullptr));
        label->setText(QCoreApplication::translate("FileRegistryEditorClass", "Path", nullptr));
        label_2->setText(QCoreApplication::translate("FileRegistryEditorClass", "MachineID", nullptr));
        pushButtonSelectFolder->setText(QCoreApplication::translate("FileRegistryEditorClass", "...", nullptr));
        pushButtonOK->setText(QCoreApplication::translate("FileRegistryEditorClass", "Save and Close", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("FileRegistryEditorClass", "Cancel", nullptr));
        lineEditHostName->setText(QCoreApplication::translate("FileRegistryEditorClass", "localhost", nullptr));
        lineEditDatabaseName->setText(QCoreApplication::translate("FileRegistryEditorClass", "d:/data/Regulus64.fdb", nullptr));
        label_4->setText(QCoreApplication::translate("FileRegistryEditorClass", "Database name", nullptr));
        label_3->setText(QCoreApplication::translate("FileRegistryEditorClass", "Host Name", nullptr));
        label_5->setText(QCoreApplication::translate("FileRegistryEditorClass", "Database", nullptr));
        pushButtonLoadDatabase->setText(QCoreApplication::translate("FileRegistryEditorClass", "Load database", nullptr));
        label_6->setText(QCoreApplication::translate("FileRegistryEditorClass", "Machine Name from database", nullptr));
        label_8->setText(QCoreApplication::translate("FileRegistryEditorClass", "Port number", nullptr));
        label_7->setText(QCoreApplication::translate("FileRegistryEditorClass", "Language", nullptr));
        comboBoxLanguage->setItemText(0, QCoreApplication::translate("FileRegistryEditorClass", "\346\227\245\346\234\254\350\252\236", nullptr));
        comboBoxLanguage->setItemText(1, QCoreApplication::translate("FileRegistryEditorClass", "English", nullptr));
        comboBoxLanguage->setItemText(2, QCoreApplication::translate("FileRegistryEditorClass", "\347\271\201\344\275\223\344\270\255\346\226\207", nullptr));
        comboBoxLanguage->setItemText(3, QCoreApplication::translate("FileRegistryEditorClass", "\347\260\241\344\275\223\344\270\255\346\226\207", nullptr));
        comboBoxLanguage->setItemText(4, QCoreApplication::translate("FileRegistryEditorClass", "Korean", nullptr));

        checkBoxEditMaltipleMachine->setText(QCoreApplication::translate("FileRegistryEditorClass", "Edit multiple machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileRegistryEditorClass: public Ui_FileRegistryEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEREGISTRYEDITOR_H
