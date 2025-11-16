/********************************************************************************
** Form generated from reading UI file 'DrawHookControlPanelForm.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWHOOKCONTROLPANELFORM_H
#define UI_DRAWHOOKCONTROLPANELFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_DrawHookControlPanelForm
{
public:
    QToolBox *toolBox;
    QWidget *PageLine;
    QLabel *label;
    QSpinBox *spinBoxLineWidth;
    QLabel *label_2;
    QComboBox *comboBoxLineType;
    QLabel *label_3;
    QComboBox *comboBoxLineStartType;
    QLabel *label_4;
    QComboBox *comboBoxLineEndType;
    QLabel *label_5;
    QToolButton *toolButtonLineColor;
    QWidget *PageDraw;
    QComboBox *comboBoxDrawType;
    QToolButton *toolButtonDrawLineColor;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBoxDrawInsideType;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *spinBoxDrawLineWidth;
    QToolButton *toolButtonDrawInsideColor;
    QLabel *label_10;
    QWidget *PageText;
    QLabel *label_11;
    QSpinBox *spinBoxTextSize;
    QLabel *label_12;
    QLineEdit *lineEditTextFont;
    QPushButton *pushButtonTextFont;
    QToolButton *toolButtonTextColor;
    QLabel *label_13;
    QToolButton *toolButtonNew;
    QToolButton *toolButtonSelect;
    QToolButton *toolButtonDelete;

    void setupUi(GUIFormBase *DrawHookControlPanelForm)
    {
        if (DrawHookControlPanelForm->objectName().isEmpty())
            DrawHookControlPanelForm->setObjectName("DrawHookControlPanelForm");
        DrawHookControlPanelForm->resize(175, 420);
        toolBox = new QToolBox(DrawHookControlPanelForm);
        toolBox->setObjectName("toolBox");
        toolBox->setGeometry(QRect(0, 0, 171, 361));
        PageLine = new QWidget();
        PageLine->setObjectName("PageLine");
        PageLine->setGeometry(QRect(0, 0, 171, 256));
        label = new QLabel(PageLine);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 75, 18));
        spinBoxLineWidth = new QSpinBox(PageLine);
        spinBoxLineWidth->setObjectName("spinBoxLineWidth");
        spinBoxLineWidth->setGeometry(QRect(70, 0, 81, 24));
        spinBoxLineWidth->setValue(1);
        label_2 = new QLabel(PageLine);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 40, 75, 18));
        comboBoxLineType = new QComboBox(PageLine);
        comboBoxLineType->addItem(QString());
        comboBoxLineType->addItem(QString());
        comboBoxLineType->addItem(QString());
        comboBoxLineType->setObjectName("comboBoxLineType");
        comboBoxLineType->setGeometry(QRect(60, 70, 101, 24));
        label_3 = new QLabel(PageLine);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 140, 75, 18));
        comboBoxLineStartType = new QComboBox(PageLine);
        comboBoxLineStartType->addItem(QString());
        comboBoxLineStartType->addItem(QString());
        comboBoxLineStartType->addItem(QString());
        comboBoxLineStartType->addItem(QString());
        comboBoxLineStartType->addItem(QString());
        comboBoxLineStartType->setObjectName("comboBoxLineStartType");
        comboBoxLineStartType->setGeometry(QRect(40, 160, 131, 24));
        label_4 = new QLabel(PageLine);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 200, 75, 18));
        comboBoxLineEndType = new QComboBox(PageLine);
        comboBoxLineEndType->addItem(QString());
        comboBoxLineEndType->addItem(QString());
        comboBoxLineEndType->addItem(QString());
        comboBoxLineEndType->addItem(QString());
        comboBoxLineEndType->addItem(QString());
        comboBoxLineEndType->setObjectName("comboBoxLineEndType");
        comboBoxLineEndType->setGeometry(QRect(40, 220, 131, 24));
        label_5 = new QLabel(PageLine);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 110, 75, 18));
        toolButtonLineColor = new QToolButton(PageLine);
        toolButtonLineColor->setObjectName("toolButtonLineColor");
        toolButtonLineColor->setGeometry(QRect(100, 110, 71, 31));
        QPalette palette;
        QBrush brush(QColor(85, 85, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        toolButtonLineColor->setPalette(palette);
        toolButtonLineColor->setAutoFillBackground(true);
        toolButtonLineColor->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonLineColor->setArrowType(Qt::NoArrow);
        toolBox->addItem(PageLine, QString::fromUtf8("Line"));
        PageDraw = new QWidget();
        PageDraw->setObjectName("PageDraw");
        PageDraw->setGeometry(QRect(0, 0, 171, 256));
        comboBoxDrawType = new QComboBox(PageDraw);
        comboBoxDrawType->addItem(QString());
        comboBoxDrawType->addItem(QString());
        comboBoxDrawType->addItem(QString());
        comboBoxDrawType->setObjectName("comboBoxDrawType");
        comboBoxDrawType->setGeometry(QRect(30, 20, 131, 24));
        toolButtonDrawLineColor = new QToolButton(PageDraw);
        toolButtonDrawLineColor->setObjectName("toolButtonDrawLineColor");
        toolButtonDrawLineColor->setGeometry(QRect(100, 100, 51, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        toolButtonDrawLineColor->setPalette(palette1);
        toolButtonDrawLineColor->setAutoFillBackground(true);
        toolButtonDrawLineColor->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonDrawLineColor->setArrowType(Qt::NoArrow);
        label_6 = new QLabel(PageDraw);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 100, 61, 21));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(PageDraw);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 0, 75, 18));
        comboBoxDrawInsideType = new QComboBox(PageDraw);
        comboBoxDrawInsideType->addItem(QString());
        comboBoxDrawInsideType->addItem(QString());
        comboBoxDrawInsideType->addItem(QString());
        comboBoxDrawInsideType->setObjectName("comboBoxDrawInsideType");
        comboBoxDrawInsideType->setGeometry(QRect(30, 180, 131, 24));
        label_8 = new QLabel(PageDraw);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 150, 75, 18));
        label_9 = new QLabel(PageDraw);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 70, 61, 21));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxDrawLineWidth = new QSpinBox(PageDraw);
        spinBoxDrawLineWidth->setObjectName("spinBoxDrawLineWidth");
        spinBoxDrawLineWidth->setGeometry(QRect(100, 70, 61, 24));
        spinBoxDrawLineWidth->setValue(1);
        toolButtonDrawInsideColor = new QToolButton(PageDraw);
        toolButtonDrawInsideColor->setObjectName("toolButtonDrawInsideColor");
        toolButtonDrawInsideColor->setGeometry(QRect(100, 210, 51, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        toolButtonDrawInsideColor->setPalette(palette2);
        toolButtonDrawInsideColor->setAutoFillBackground(true);
        toolButtonDrawInsideColor->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonDrawInsideColor->setArrowType(Qt::NoArrow);
        label_10 = new QLabel(PageDraw);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 217, 61, 21));
        toolBox->addItem(PageDraw, QString::fromUtf8("Draw"));
        PageText = new QWidget();
        PageText->setObjectName("PageText");
        PageText->setGeometry(QRect(0, 0, 171, 256));
        label_11 = new QLabel(PageText);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 10, 91, 21));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxTextSize = new QSpinBox(PageText);
        spinBoxTextSize->setObjectName("spinBoxTextSize");
        spinBoxTextSize->setGeometry(QRect(90, 40, 61, 31));
        spinBoxTextSize->setMaximum(9999);
        spinBoxTextSize->setValue(12);
        label_12 = new QLabel(PageText);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 90, 91, 21));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditTextFont = new QLineEdit(PageText);
        lineEditTextFont->setObjectName("lineEditTextFont");
        lineEditTextFont->setGeometry(QRect(10, 113, 131, 31));
        pushButtonTextFont = new QPushButton(PageText);
        pushButtonTextFont->setObjectName("pushButtonTextFont");
        pushButtonTextFont->setGeometry(QRect(140, 113, 28, 31));
        toolButtonTextColor = new QToolButton(PageText);
        toolButtonTextColor->setObjectName("toolButtonTextColor");
        toolButtonTextColor->setGeometry(QRect(120, 170, 51, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::NoRole, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::NoRole, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::NoRole, brush);
        toolButtonTextColor->setPalette(palette3);
        toolButtonTextColor->setAutoFillBackground(true);
        toolButtonTextColor->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButtonTextColor->setArrowType(Qt::NoArrow);
        label_13 = new QLabel(PageText);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 170, 101, 31));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        toolBox->addItem(PageText, QString::fromUtf8("Text"));
        toolButtonNew = new QToolButton(DrawHookControlPanelForm);
        toolButtonNew->setObjectName("toolButtonNew");
        toolButtonNew->setGeometry(QRect(0, 370, 51, 41));
        toolButtonNew->setCheckable(true);
        toolButtonSelect = new QToolButton(DrawHookControlPanelForm);
        toolButtonSelect->setObjectName("toolButtonSelect");
        toolButtonSelect->setGeometry(QRect(60, 370, 51, 41));
        toolButtonSelect->setCheckable(true);
        toolButtonDelete = new QToolButton(DrawHookControlPanelForm);
        toolButtonDelete->setObjectName("toolButtonDelete");
        toolButtonDelete->setGeometry(QRect(120, 370, 51, 41));
        toolButtonDelete->setCheckable(false);

        retranslateUi(DrawHookControlPanelForm);

        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(DrawHookControlPanelForm);
    } // setupUi

    void retranslateUi(GUIFormBase *DrawHookControlPanelForm)
    {
        DrawHookControlPanelForm->setWindowTitle(QCoreApplication::translate("DrawHookControlPanelForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\345\271\205", nullptr));
        label_2->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\347\250\256\351\241\236", nullptr));
        comboBoxLineType->setItemText(0, QCoreApplication::translate("DrawHookControlPanelForm", "Solid", nullptr));
        comboBoxLineType->setItemText(1, QCoreApplication::translate("DrawHookControlPanelForm", "Dot", nullptr));
        comboBoxLineType->setItemText(2, QCoreApplication::translate("DrawHookControlPanelForm", "Double", nullptr));

        label_3->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\345\247\213\347\202\271", nullptr));
        comboBoxLineStartType->setItemText(0, QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\345\210\206", nullptr));
        comboBoxLineStartType->setItemText(1, QCoreApplication::translate("DrawHookControlPanelForm", "\351\226\213\346\224\276", nullptr));
        comboBoxLineStartType->setItemText(2, QCoreApplication::translate("DrawHookControlPanelForm", "\347\237\242\345\215\260", nullptr));
        comboBoxLineStartType->setItemText(3, QCoreApplication::translate("DrawHookControlPanelForm", "\344\270\270\345\215\260", nullptr));
        comboBoxLineStartType->setItemText(4, QCoreApplication::translate("DrawHookControlPanelForm", "\343\203\220\343\203\274", nullptr));

        label_4->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\265\202\347\202\271", nullptr));
        comboBoxLineEndType->setItemText(0, QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\345\210\206", nullptr));
        comboBoxLineEndType->setItemText(1, QCoreApplication::translate("DrawHookControlPanelForm", "\351\226\213\346\224\276", nullptr));
        comboBoxLineEndType->setItemText(2, QCoreApplication::translate("DrawHookControlPanelForm", "\347\237\242\345\215\260", nullptr));
        comboBoxLineEndType->setItemText(3, QCoreApplication::translate("DrawHookControlPanelForm", "\344\270\270\345\215\260", nullptr));
        comboBoxLineEndType->setItemText(4, QCoreApplication::translate("DrawHookControlPanelForm", "\343\203\220\343\203\274", nullptr));

        label_5->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\350\211\262", nullptr));
        toolButtonLineColor->setText(QCoreApplication::translate("DrawHookControlPanelForm", "...", nullptr));
        toolBox->setItemText(toolBox->indexOf(PageLine), QCoreApplication::translate("DrawHookControlPanelForm", "Line", nullptr));
        comboBoxDrawType->setItemText(0, QCoreApplication::translate("DrawHookControlPanelForm", "\345\233\233\350\247\222\345\275\242", nullptr));
        comboBoxDrawType->setItemText(1, QCoreApplication::translate("DrawHookControlPanelForm", "\345\206\206", nullptr));
        comboBoxDrawType->setItemText(2, QCoreApplication::translate("DrawHookControlPanelForm", "\345\244\232\350\247\222\345\275\242", nullptr));

        toolButtonDrawLineColor->setText(QCoreApplication::translate("DrawHookControlPanelForm", "...", nullptr));
        label_6->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\350\211\262", nullptr));
        label_7->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\346\217\217\347\224\273\347\250\256\351\241\236", nullptr));
        comboBoxDrawInsideType->setItemText(0, QCoreApplication::translate("DrawHookControlPanelForm", "\346\217\217\347\224\273\347\204\241\343\201\227", nullptr));
        comboBoxDrawInsideType->setItemText(1, QCoreApplication::translate("DrawHookControlPanelForm", "\345\241\227\343\202\212\343\201\244\343\201\266\343\201\227", nullptr));
        comboBoxDrawInsideType->setItemText(2, QCoreApplication::translate("DrawHookControlPanelForm", "\343\203\217\343\203\203\343\203\201", nullptr));

        label_8->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\345\206\205\351\203\250\347\250\256\351\241\236", nullptr));
        label_9->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\347\267\232\345\271\205", nullptr));
        toolButtonDrawInsideColor->setText(QCoreApplication::translate("DrawHookControlPanelForm", "...", nullptr));
        label_10->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\345\206\205\351\203\250\350\211\262", nullptr));
        toolBox->setItemText(toolBox->indexOf(PageDraw), QCoreApplication::translate("DrawHookControlPanelForm", "Draw", nullptr));
        label_11->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\346\226\207\345\255\227\343\202\265\343\202\244\343\202\272", nullptr));
        label_12->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\343\203\225\343\202\251\343\203\263\343\203\210", nullptr));
        pushButtonTextFont->setText(QCoreApplication::translate("DrawHookControlPanelForm", "...", nullptr));
        toolButtonTextColor->setText(QCoreApplication::translate("DrawHookControlPanelForm", "...", nullptr));
        label_13->setText(QCoreApplication::translate("DrawHookControlPanelForm", "\346\226\207\345\255\227\343\201\256\350\211\262", nullptr));
        toolBox->setItemText(toolBox->indexOf(PageText), QCoreApplication::translate("DrawHookControlPanelForm", "Text", nullptr));
        toolButtonNew->setText(QCoreApplication::translate("DrawHookControlPanelForm", "New", nullptr));
        toolButtonSelect->setText(QCoreApplication::translate("DrawHookControlPanelForm", "Sel", nullptr));
        toolButtonDelete->setText(QCoreApplication::translate("DrawHookControlPanelForm", "Del", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawHookControlPanelForm: public Ui_DrawHookControlPanelForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWHOOKCONTROLPANELFORM_H
