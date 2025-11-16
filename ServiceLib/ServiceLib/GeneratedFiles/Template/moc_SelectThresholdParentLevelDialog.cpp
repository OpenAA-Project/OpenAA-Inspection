/****************************************************************************
** Meta object code from reading C++ file 'SelectThresholdParentLevelDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SelectThresholdParentLevelDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectThresholdParentLevelDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectThresholdParentLevelDialog_t {
    QByteArrayData data[13];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectThresholdParentLevelDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectThresholdParentLevelDialog_t qt_meta_stringdata_SelectThresholdParentLevelDialog = {
    {
QT_MOC_LITERAL(0, 0, 32), // "SelectThresholdParentLevelDialog"
QT_MOC_LITERAL(1, 33, 27), // "on_pushButtonSelect_clicked"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 27), // "on_pushButtonCancel_clicked"
QT_MOC_LITERAL(4, 90, 36), // "on_treeWidgetLevel_itemDouble..."
QT_MOC_LITERAL(5, 127, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 144, 4), // "item"
QT_MOC_LITERAL(7, 149, 6), // "column"
QT_MOC_LITERAL(8, 156, 39), // "on_treeWidgetLevel_itemSelect..."
QT_MOC_LITERAL(9, 196, 26), // "on_treeWidgetLevel_clicked"
QT_MOC_LITERAL(10, 223, 11), // "QModelIndex"
QT_MOC_LITERAL(11, 235, 5), // "index"
QT_MOC_LITERAL(12, 241, 28) // "on_pushButtonTopRoot_clicked"

    },
    "SelectThresholdParentLevelDialog\0"
    "on_pushButtonSelect_clicked\0\0"
    "on_pushButtonCancel_clicked\0"
    "on_treeWidgetLevel_itemDoubleClicked\0"
    "QTreeWidgetItem*\0item\0column\0"
    "on_treeWidgetLevel_itemSelectionChanged\0"
    "on_treeWidgetLevel_clicked\0QModelIndex\0"
    "index\0on_pushButtonTopRoot_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectThresholdParentLevelDialog[] = {

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
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    2,   46,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    1,   52,    2, 0x08 /* Private */,
      12,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void SelectThresholdParentLevelDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectThresholdParentLevelDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButtonSelect_clicked(); break;
        case 1: _t->on_pushButtonCancel_clicked(); break;
        case 2: _t->on_treeWidgetLevel_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_treeWidgetLevel_itemSelectionChanged(); break;
        case 4: _t->on_treeWidgetLevel_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_pushButtonTopRoot_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectThresholdParentLevelDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SelectThresholdParentLevelDialog.data,
    qt_meta_data_SelectThresholdParentLevelDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectThresholdParentLevelDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectThresholdParentLevelDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectThresholdParentLevelDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QDialog::qt_metacast(_clname);
}

int SelectThresholdParentLevelDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
