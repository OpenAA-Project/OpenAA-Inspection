/********************************************************************************
** Form generated from reading UI file 'EditGui.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITGUI_H
#define UI_EDITGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditGUIClass
{
public:
    QAction *actionCreate_new;
    QAction *actionOpen_GUI_file;
    QAction *actionSave_GUI_file;
    QAction *actionExit;
    QAction *actionGlobal_Setting;
    QAction *actionCommunication_Setting;
    QAction *actionScanning_setting;
    QAction *actionTest;
    QAction *actionXXX;
    QAction *actionSave_Setting;
    QAction *actionOutlineOffset;
    QAction *actionSave_Global_Param;
    QAction *actionEdit_Filter;
    QAction *actionSave_GUI_file_As;
    QAction *actionAbc;
    QAction *action_Sync_GUI_File;
    QAction *actionEditPhase;
    QAction *actionUsage_component;
    QAction *actionImage_direction_on_each_page;
    QAction *actionSort;
    QAction *actionSearch;
    QAction *actionSnap_to_grid;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionAlign_left;
    QAction *actionAlign_top;
    QAction *actionAlign_same_width;
    QAction *actionAlign_same_height;
    QAction *actionAlign_right;
    QAction *actionAlign_bottom;
    QAction *actionAlign_horizontal_same_gap;
    QAction *actionAlign_vertical_same_gap;
    QAction *actionDelete_Selected_components;
    QAction *actionMake_BAT_file;
    QAction *actionMake_status_Def_fike;
    QAction *actionMake_GUILanguage_file;
    QAction *actionEdit_order;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSave_And_Rename;
    QMenu *menuTool;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditGUIClass)
    {
        if (EditGUIClass->objectName().isEmpty())
            EditGUIClass->setObjectName("EditGUIClass");
        EditGUIClass->resize(382, 86);
        actionCreate_new = new QAction(EditGUIClass);
        actionCreate_new->setObjectName("actionCreate_new");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Qtres/CopyOne.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCreate_new->setIcon(icon);
        actionCreate_new->setShortcutContext(Qt::ApplicationShortcut);
        actionOpen_GUI_file = new QAction(EditGUIClass);
        actionOpen_GUI_file->setObjectName("actionOpen_GUI_file");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Qtres/Folder.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpen_GUI_file->setIcon(icon1);
        actionOpen_GUI_file->setShortcutContext(Qt::ApplicationShortcut);
        actionSave_GUI_file = new QAction(EditGUIClass);
        actionSave_GUI_file->setObjectName("actionSave_GUI_file");
        actionSave_GUI_file->setEnabled(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Qtres/Save.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave_GUI_file->setIcon(icon2);
        actionSave_GUI_file->setShortcutContext(Qt::ApplicationShortcut);
        actionExit = new QAction(EditGUIClass);
        actionExit->setObjectName("actionExit");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Qtres/Close.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExit->setIcon(icon3);
        actionGlobal_Setting = new QAction(EditGUIClass);
        actionGlobal_Setting->setObjectName("actionGlobal_Setting");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Qtres/Setting.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionGlobal_Setting->setIcon(icon4);
        actionCommunication_Setting = new QAction(EditGUIClass);
        actionCommunication_Setting->setObjectName("actionCommunication_Setting");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Qtres/Commn.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCommunication_Setting->setIcon(icon5);
        actionScanning_setting = new QAction(EditGUIClass);
        actionScanning_setting->setObjectName("actionScanning_setting");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Qtres/Scan.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionScanning_setting->setIcon(icon6);
        actionTest = new QAction(EditGUIClass);
        actionTest->setObjectName("actionTest");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Qtres/Test2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionTest->setIcon(icon7);
        actionXXX = new QAction(EditGUIClass);
        actionXXX->setObjectName("actionXXX");
        actionSave_Setting = new QAction(EditGUIClass);
        actionSave_Setting->setObjectName("actionSave_Setting");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Qtres/CommnSave.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave_Setting->setIcon(icon8);
        actionOutlineOffset = new QAction(EditGUIClass);
        actionOutlineOffset->setObjectName("actionOutlineOffset");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Qtres/Outline.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOutlineOffset->setIcon(icon9);
        actionSave_Global_Param = new QAction(EditGUIClass);
        actionSave_Global_Param->setObjectName("actionSave_Global_Param");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Qtres/ParameterSave.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave_Global_Param->setIcon(icon10);
        actionEdit_Filter = new QAction(EditGUIClass);
        actionEdit_Filter->setObjectName("actionEdit_Filter");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Qtres/Filter.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionEdit_Filter->setIcon(icon11);
        actionSave_GUI_file_As = new QAction(EditGUIClass);
        actionSave_GUI_file_As->setObjectName("actionSave_GUI_file_As");
        actionSave_GUI_file_As->setEnabled(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Qtres/SaveNew.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSave_GUI_file_As->setIcon(icon12);
        actionAbc = new QAction(EditGUIClass);
        actionAbc->setObjectName("actionAbc");
        action_Sync_GUI_File = new QAction(EditGUIClass);
        action_Sync_GUI_File->setObjectName("action_Sync_GUI_File");
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Qtres/Sync.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        action_Sync_GUI_File->setIcon(icon13);
        actionEditPhase = new QAction(EditGUIClass);
        actionEditPhase->setObjectName("actionEditPhase");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Qtres/Phase.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionEditPhase->setIcon(icon14);
        actionUsage_component = new QAction(EditGUIClass);
        actionUsage_component->setObjectName("actionUsage_component");
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Qtres/Learn.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionUsage_component->setIcon(icon15);
        actionImage_direction_on_each_page = new QAction(EditGUIClass);
        actionImage_direction_on_each_page->setObjectName("actionImage_direction_on_each_page");
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Qtres/Image.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionImage_direction_on_each_page->setIcon(icon16);
        actionSort = new QAction(EditGUIClass);
        actionSort->setObjectName("actionSort");
        actionSearch = new QAction(EditGUIClass);
        actionSearch->setObjectName("actionSearch");
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Qtres/Search.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSearch->setIcon(icon17);
        actionSnap_to_grid = new QAction(EditGUIClass);
        actionSnap_to_grid->setObjectName("actionSnap_to_grid");
        actionSnap_to_grid->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/Qtres/Grid.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionSnap_to_grid->setIcon(icon18);
        actionCopy = new QAction(EditGUIClass);
        actionCopy->setObjectName("actionCopy");
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/Qtres/Copy.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCopy->setIcon(icon19);
        actionPaste = new QAction(EditGUIClass);
        actionPaste->setObjectName("actionPaste");
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/Qtres/Paste.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionPaste->setIcon(icon20);
        actionAlign_left = new QAction(EditGUIClass);
        actionAlign_left->setObjectName("actionAlign_left");
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/Qtres/AlignLeft.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_left->setIcon(icon21);
        actionAlign_top = new QAction(EditGUIClass);
        actionAlign_top->setObjectName("actionAlign_top");
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/Qtres/AlignTop.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_top->setIcon(icon22);
        actionAlign_same_width = new QAction(EditGUIClass);
        actionAlign_same_width->setObjectName("actionAlign_same_width");
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/Qtres/AlignWidth.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_same_width->setIcon(icon23);
        actionAlign_same_height = new QAction(EditGUIClass);
        actionAlign_same_height->setObjectName("actionAlign_same_height");
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/Qtres/AlignHeight.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_same_height->setIcon(icon24);
        actionAlign_right = new QAction(EditGUIClass);
        actionAlign_right->setObjectName("actionAlign_right");
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/Qtres/AlignRight.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_right->setIcon(icon25);
        actionAlign_bottom = new QAction(EditGUIClass);
        actionAlign_bottom->setObjectName("actionAlign_bottom");
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/Qtres/AlignBottom.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_bottom->setIcon(icon26);
        actionAlign_horizontal_same_gap = new QAction(EditGUIClass);
        actionAlign_horizontal_same_gap->setObjectName("actionAlign_horizontal_same_gap");
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/Qtres/AlignHorizontal.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_horizontal_same_gap->setIcon(icon27);
        actionAlign_vertical_same_gap = new QAction(EditGUIClass);
        actionAlign_vertical_same_gap->setObjectName("actionAlign_vertical_same_gap");
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/Qtres/AlignVertical.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAlign_vertical_same_gap->setIcon(icon28);
        actionDelete_Selected_components = new QAction(EditGUIClass);
        actionDelete_Selected_components->setObjectName("actionDelete_Selected_components");
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/Qtres/Delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionDelete_Selected_components->setIcon(icon29);
        actionMake_BAT_file = new QAction(EditGUIClass);
        actionMake_BAT_file->setObjectName("actionMake_BAT_file");
        actionMake_status_Def_fike = new QAction(EditGUIClass);
        actionMake_status_Def_fike->setObjectName("actionMake_status_Def_fike");
        actionMake_GUILanguage_file = new QAction(EditGUIClass);
        actionMake_GUILanguage_file->setObjectName("actionMake_GUILanguage_file");
        actionEdit_order = new QAction(EditGUIClass);
        actionEdit_order->setObjectName("actionEdit_order");
        centralWidget = new QWidget(EditGUIClass);
        centralWidget->setObjectName("centralWidget");
        EditGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditGUIClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 382, 17));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuSave_And_Rename = new QMenu(menuFile);
        menuSave_And_Rename->setObjectName("menuSave_And_Rename");
        menuSave_And_Rename->setEnabled(true);
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/Qtres/SaveRename.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        menuSave_And_Rename->setIcon(icon30);
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName("menuTool");
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName("menuEdit");
        EditGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditGUIClass);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setOrientation(Qt::Horizontal);
        EditGUIClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditGUIClass);
        statusBar->setObjectName("statusBar");
        EditGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuFile->addAction(actionCreate_new);
        menuFile->addAction(actionOpen_GUI_file);
        menuFile->addAction(actionSave_GUI_file);
        menuFile->addAction(actionSave_GUI_file_As);
        menuFile->addAction(menuSave_And_Rename->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTool->addAction(actionTest);
        menuTool->addSeparator();
        menuTool->addAction(actionGlobal_Setting);
        menuTool->addAction(actionScanning_setting);
        menuTool->addAction(actionCommunication_Setting);
        menuTool->addAction(actionSave_Setting);
        menuTool->addAction(actionOutlineOffset);
        menuTool->addAction(actionSave_Global_Param);
        menuTool->addAction(actionEdit_Filter);
        menuTool->addAction(action_Sync_GUI_File);
        menuTool->addAction(actionEditPhase);
        menuTool->addAction(actionUsage_component);
        menuTool->addAction(actionImage_direction_on_each_page);
        menuTool->addAction(actionMake_status_Def_fike);
        menuTool->addAction(actionMake_BAT_file);
        menuTool->addSeparator();
        menuTool->addAction(actionMake_GUILanguage_file);
        menuTool->addAction(actionEdit_order);
        menuEdit->addAction(actionSearch);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionDelete_Selected_components);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSnap_to_grid);
        menuEdit->addSeparator();
        menuEdit->addAction(actionAlign_left);
        menuEdit->addAction(actionAlign_right);
        menuEdit->addAction(actionAlign_top);
        menuEdit->addAction(actionAlign_bottom);
        menuEdit->addAction(actionAlign_same_width);
        menuEdit->addAction(actionAlign_same_height);
        menuEdit->addAction(actionAlign_horizontal_same_gap);
        menuEdit->addAction(actionAlign_vertical_same_gap);

        retranslateUi(EditGUIClass);

        QMetaObject::connectSlotsByName(EditGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditGUIClass)
    {
        EditGUIClass->setWindowTitle(QCoreApplication::translate("EditGUIClass", "EditGUI", nullptr));
        actionCreate_new->setText(QCoreApplication::translate("EditGUIClass", "&Create new", nullptr));
#if QT_CONFIG(shortcut)
        actionCreate_new->setShortcut(QCoreApplication::translate("EditGUIClass", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_GUI_file->setText(QCoreApplication::translate("EditGUIClass", "&Open GUI file", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen_GUI_file->setShortcut(QCoreApplication::translate("EditGUIClass", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_GUI_file->setText(QCoreApplication::translate("EditGUIClass", "&Save GUI file", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_GUI_file->setShortcut(QCoreApplication::translate("EditGUIClass", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("EditGUIClass", "&Exit", nullptr));
        actionGlobal_Setting->setText(QCoreApplication::translate("EditGUIClass", "&Global Setting", nullptr));
        actionCommunication_Setting->setText(QCoreApplication::translate("EditGUIClass", "&Communication Setting", nullptr));
        actionScanning_setting->setText(QCoreApplication::translate("EditGUIClass", "&Scanning setting", nullptr));
        actionTest->setText(QCoreApplication::translate("EditGUIClass", "&Test", nullptr));
        actionXXX->setText(QCoreApplication::translate("EditGUIClass", "XXX", nullptr));
        actionSave_Setting->setText(QCoreApplication::translate("EditGUIClass", "Save C&ommSetting", nullptr));
        actionOutlineOffset->setText(QCoreApplication::translate("EditGUIClass", "&OutlineOffset", nullptr));
        actionSave_Global_Param->setText(QCoreApplication::translate("EditGUIClass", "Save G&lobal Param", nullptr));
        actionEdit_Filter->setText(QCoreApplication::translate("EditGUIClass", "&Edit Filter", nullptr));
        actionSave_GUI_file_As->setText(QCoreApplication::translate("EditGUIClass", "Save GUI file &as...", nullptr));
        actionAbc->setText(QCoreApplication::translate("EditGUIClass", "abc", nullptr));
        action_Sync_GUI_File->setText(QCoreApplication::translate("EditGUIClass", "&Sync GUI File", nullptr));
        actionEditPhase->setText(QCoreApplication::translate("EditGUIClass", "EditPhase", nullptr));
        actionUsage_component->setText(QCoreApplication::translate("EditGUIClass", "Usage component", nullptr));
        actionImage_direction_on_each_page->setText(QCoreApplication::translate("EditGUIClass", "Image direction on each page", nullptr));
        actionSort->setText(QCoreApplication::translate("EditGUIClass", "Sort", nullptr));
        actionSearch->setText(QCoreApplication::translate("EditGUIClass", "Search", nullptr));
        actionSnap_to_grid->setText(QCoreApplication::translate("EditGUIClass", "Snap to grid", nullptr));
        actionCopy->setText(QCoreApplication::translate("EditGUIClass", "Copy", nullptr));
        actionPaste->setText(QCoreApplication::translate("EditGUIClass", "Paste", nullptr));
        actionAlign_left->setText(QCoreApplication::translate("EditGUIClass", "Align left", nullptr));
        actionAlign_top->setText(QCoreApplication::translate("EditGUIClass", "Align top", nullptr));
        actionAlign_same_width->setText(QCoreApplication::translate("EditGUIClass", "Align same width", nullptr));
        actionAlign_same_height->setText(QCoreApplication::translate("EditGUIClass", "Align same height", nullptr));
        actionAlign_right->setText(QCoreApplication::translate("EditGUIClass", "Align right", nullptr));
        actionAlign_bottom->setText(QCoreApplication::translate("EditGUIClass", "Align bottom", nullptr));
        actionAlign_horizontal_same_gap->setText(QCoreApplication::translate("EditGUIClass", "Align horizontal same gap", nullptr));
        actionAlign_vertical_same_gap->setText(QCoreApplication::translate("EditGUIClass", "Align vertical same gap", nullptr));
        actionDelete_Selected_components->setText(QCoreApplication::translate("EditGUIClass", "Delete (Selected components)", nullptr));
        actionMake_BAT_file->setText(QCoreApplication::translate("EditGUIClass", "Make BAT file", nullptr));
        actionMake_status_Def_fike->setText(QCoreApplication::translate("EditGUIClass", "Make status Def file", nullptr));
        actionMake_GUILanguage_file->setText(QCoreApplication::translate("EditGUIClass", "Make GUILanguage file", nullptr));
        actionEdit_order->setText(QCoreApplication::translate("EditGUIClass", "Edit order", nullptr));
        menuFile->setTitle(QCoreApplication::translate("EditGUIClass", "&File", nullptr));
        menuSave_And_Rename->setTitle(QCoreApplication::translate("EditGUIClass", "Save And &Rename", nullptr));
        menuTool->setTitle(QCoreApplication::translate("EditGUIClass", "&Tool", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("EditGUIClass", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditGUIClass: public Ui_EditGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITGUI_H
