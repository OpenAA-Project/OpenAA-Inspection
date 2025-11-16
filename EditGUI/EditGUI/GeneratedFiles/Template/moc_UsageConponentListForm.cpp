/****************************************************************************
** Meta object code from reading C++ file 'UsageConponentListForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UsageConponentListForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UsageConponentListForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UsageConponentListForm_t {
    QByteArrayData data[10];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UsageConponentListForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UsageConponentListForm_t qt_meta_stringdata_UsageConponentListForm = {
    {
QT_MOC_LITERAL(0, 0, 22), // "UsageConponentListForm"
QT_MOC_LITERAL(1, 23, 19), // "MListSectionClicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 22), // "on_tableWidget_clicked"
QT_MOC_LITERAL(4, 67, 11), // "QModelIndex"
QT_MOC_LITERAL(5, 79, 5), // "index"
QT_MOC_LITERAL(6, 85, 32), // "on_pushButtonMakeCopyBAT_clicked"
QT_MOC_LITERAL(7, 118, 27), // "on_pushButtonDelete_clicked"
QT_MOC_LITERAL(8, 146, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(9, 173, 36) // "on_pushButtonExcludedListOut_..."

    },
    "UsageConponentListForm\0MListSectionClicked\0"
    "\0on_tableWidget_clicked\0QModelIndex\0"
    "index\0on_pushButtonMakeCopyBAT_clicked\0"
    "on_pushButtonDelete_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonExcludedListOut_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UsageConponentListForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       3,    1,   47,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UsageConponentListForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UsageConponentListForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->MListSectionClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_tableWidget_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_pushButtonMakeCopyBAT_clicked(); break;
        case 3: _t->on_pushButtonDelete_clicked(); break;
        case 4: _t->on_pushButtonClose_clicked(); break;
        case 5: _t->on_pushButtonExcludedListOut_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UsageConponentListForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_UsageConponentListForm.data,
    qt_meta_data_UsageConponentListForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UsageConponentListForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UsageConponentListForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UsageConponentListForm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int UsageConponentListForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
