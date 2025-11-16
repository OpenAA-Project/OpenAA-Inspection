/********************************************************************************
** Form generated from reading UI file 'ZAxisViewerGraph.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZAXISVIEWERGRAPH_H
#define UI_ZAXISVIEWERGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include "guiformbase.h"

QT_BEGIN_NAMESPACE

class Ui_ZAxisViewerGraphClass
{
public:

    void setupUi(GUIFormBase *ZAxisViewerGraphClass)
    {
        if (ZAxisViewerGraphClass->objectName().isEmpty())
            ZAxisViewerGraphClass->setObjectName(QString::fromUtf8("ZAxisViewerGraphClass"));
        ZAxisViewerGraphClass->resize(633, 370);

        retranslateUi(ZAxisViewerGraphClass);

        QMetaObject::connectSlotsByName(ZAxisViewerGraphClass);
    } // setupUi

    void retranslateUi(GUIFormBase *ZAxisViewerGraphClass)
    {
        ZAxisViewerGraphClass->setWindowTitle(QCoreApplication::translate("ZAxisViewerGraphClass", "ZAxisViewerGraph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ZAxisViewerGraphClass: public Ui_ZAxisViewerGraphClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZAXISVIEWERGRAPH_H
