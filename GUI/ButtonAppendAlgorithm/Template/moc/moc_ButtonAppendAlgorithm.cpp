/****************************************************************************
** Meta object code from reading C++ file 'ButtonAppendAlgorithm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ButtonAppendAlgorithm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ButtonAppendAlgorithm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ButtonAppendAlgorithm_t {
    QByteArrayData data[5];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ButtonAppendAlgorithm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ButtonAppendAlgorithm_t qt_meta_stringdata_ButtonAppendAlgorithm = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ButtonAppendAlgorithm"
QT_MOC_LITERAL(1, 22, 11), // "SlotClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "checked"
QT_MOC_LITERAL(4, 43, 12) // "ResizeAction"

    },
    "ButtonAppendAlgorithm\0SlotClicked\0\0"
    "checked\0ResizeAction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ButtonAppendAlgorithm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void ButtonAppendAlgorithm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ButtonAppendAlgorithm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->ResizeAction(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ButtonAppendAlgorithm::staticMetaObject = { {
    QMetaObject::SuperData::link<GUIFormBase::staticMetaObject>(),
    qt_meta_stringdata_ButtonAppendAlgorithm.data,
    qt_meta_data_ButtonAppendAlgorithm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ButtonAppendAlgorithm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ButtonAppendAlgorithm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ButtonAppendAlgorithm.stringdata0))
        return static_cast<void*>(this);
    return GUIFormBase::qt_metacast(_clname);
}

int ButtonAppendAlgorithm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GUIFormBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
