/****************************************************************************
** Meta object code from reading C++ file 'SelectPhasePageLayerDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SelectPhasePageLayerDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectPhasePageLayerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectPhasePageLayerDialog_t {
    QByteArrayData data[9];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectPhasePageLayerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectPhasePageLayerDialog_t qt_meta_stringdata_SelectPhasePageLayerDialog = {
    {
QT_MOC_LITERAL(0, 0, 26), // "SelectPhasePageLayerDialog"
QT_MOC_LITERAL(1, 27, 33), // "on_listWidgetPhase1_doubleCli..."
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 74, 5), // "index"
QT_MOC_LITERAL(5, 80, 32), // "on_listWidgetPage1_doubleClicked"
QT_MOC_LITERAL(6, 113, 33), // "on_listWidgetLayer1_doubleCli..."
QT_MOC_LITERAL(7, 147, 28), // "on_pushButtonSelect1_clicked"
QT_MOC_LITERAL(8, 176, 28) // "on_pushButtonCancel1_clicked"

    },
    "SelectPhasePageLayerDialog\0"
    "on_listWidgetPhase1_doubleClicked\0\0"
    "QModelIndex\0index\0on_listWidgetPage1_doubleClicked\0"
    "on_listWidgetLayer1_doubleClicked\0"
    "on_pushButtonSelect1_clicked\0"
    "on_pushButtonCancel1_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectPhasePageLayerDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       6,    1,   45,    2, 0x08 /* Private */,
       7,    0,   48,    2, 0x08 /* Private */,
       8,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SelectPhasePageLayerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectPhasePageLayerDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_listWidgetPhase1_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_listWidgetPage1_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_listWidgetLayer1_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->on_pushButtonSelect1_clicked(); break;
        case 4: _t->on_pushButtonCancel1_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectPhasePageLayerDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SelectPhasePageLayerDialog.data,
    qt_meta_data_SelectPhasePageLayerDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectPhasePageLayerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectPhasePageLayerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectPhasePageLayerDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QDialog::qt_metacast(_clname);
}

int SelectPhasePageLayerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
