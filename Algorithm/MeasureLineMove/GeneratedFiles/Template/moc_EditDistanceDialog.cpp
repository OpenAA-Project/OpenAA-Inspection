/****************************************************************************
** Meta object code from reading C++ file 'EditDistanceDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../EditDistanceDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditDistanceDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EditDistanceDialog_t {
    QByteArrayData data[17];
    char stringdata0[455];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditDistanceDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditDistanceDialog_t qt_meta_stringdata_EditDistanceDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "EditDistanceDialog"
QT_MOC_LITERAL(1, 19, 30), // "on_pushButtonChangeLib_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 33), // "on_ButtonRelrectOnlyBlock_cli..."
QT_MOC_LITERAL(4, 85, 33), // "on_ButtonReflectAllBlocks_cli..."
QT_MOC_LITERAL(5, 119, 30), // "on_ButtonSaveToLibrary_clicked"
QT_MOC_LITERAL(6, 150, 32), // "on_ButtonLoadFromLibrary_clicked"
QT_MOC_LITERAL(7, 183, 25), // "on_pushButtonTest_clicked"
QT_MOC_LITERAL(8, 209, 22), // "on_ButtonClose_clicked"
QT_MOC_LITERAL(9, 232, 35), // "on_listWidgetHistList_doubleC..."
QT_MOC_LITERAL(10, 268, 11), // "QModelIndex"
QT_MOC_LITERAL(11, 280, 5), // "index"
QT_MOC_LITERAL(12, 286, 39), // "on_doubleSpinBoxThresholdM_va..."
QT_MOC_LITERAL(13, 326, 4), // "arg1"
QT_MOC_LITERAL(14, 331, 41), // "on_doubleSpinBoxThresholdM_2_..."
QT_MOC_LITERAL(15, 373, 39), // "on_doubleSpinBoxThresholdP_va..."
QT_MOC_LITERAL(16, 413, 41) // "on_doubleSpinBoxThresholdP_2_..."

    },
    "EditDistanceDialog\0on_pushButtonChangeLib_clicked\0"
    "\0on_ButtonRelrectOnlyBlock_clicked\0"
    "on_ButtonReflectAllBlocks_clicked\0"
    "on_ButtonSaveToLibrary_clicked\0"
    "on_ButtonLoadFromLibrary_clicked\0"
    "on_pushButtonTest_clicked\0"
    "on_ButtonClose_clicked\0"
    "on_listWidgetHistList_doubleClicked\0"
    "QModelIndex\0index\0"
    "on_doubleSpinBoxThresholdM_valueChanged\0"
    "arg1\0on_doubleSpinBoxThresholdM_2_valueChanged\0"
    "on_doubleSpinBoxThresholdP_valueChanged\0"
    "on_doubleSpinBoxThresholdP_2_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditDistanceDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    1,   81,    2, 0x08 /* Private */,
      12,    1,   84,    2, 0x08 /* Private */,
      14,    1,   87,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      16,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   13,

       0        // eod
};

void EditDistanceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EditDistanceDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButtonChangeLib_clicked(); break;
        case 1: _t->on_ButtonRelrectOnlyBlock_clicked(); break;
        case 2: _t->on_ButtonReflectAllBlocks_clicked(); break;
        case 3: _t->on_ButtonSaveToLibrary_clicked(); break;
        case 4: _t->on_ButtonLoadFromLibrary_clicked(); break;
        case 5: _t->on_pushButtonTest_clicked(); break;
        case 6: _t->on_ButtonClose_clicked(); break;
        case 7: _t->on_listWidgetHistList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_doubleSpinBoxThresholdM_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_doubleSpinBoxThresholdM_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_doubleSpinBoxThresholdP_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->on_doubleSpinBoxThresholdP_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EditDistanceDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EditDistanceDialog.data,
    qt_meta_data_EditDistanceDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EditDistanceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditDistanceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EditDistanceDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int EditDistanceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
