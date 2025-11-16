/****************************************************************************
** Meta object code from reading C++ file 'XExecuteInspectBase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XExecuteInspectBase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XExecuteInspectBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExecuteInspectBase_t {
    QByteArrayData data[5];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExecuteInspectBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExecuteInspectBase_t qt_meta_stringdata_ExecuteInspectBase = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ExecuteInspectBase"
QT_MOC_LITERAL(1, 19, 14), // "SignalCaptured"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "SignalTargetImageCaptured"
QT_MOC_LITERAL(4, 61, 25) // "SignalMasterImageCaptured"

    },
    "ExecuteInspectBase\0SignalCaptured\0\0"
    "SignalTargetImageCaptured\0"
    "SignalMasterImageCaptured"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExecuteInspectBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    0,   32,    2, 0x06 /* Public */,
       4,    0,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExecuteInspectBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExecuteInspectBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalCaptured((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SignalTargetImageCaptured(); break;
        case 2: _t->SignalMasterImageCaptured(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExecuteInspectBase::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExecuteInspectBase::SignalCaptured)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExecuteInspectBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExecuteInspectBase::SignalTargetImageCaptured)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ExecuteInspectBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExecuteInspectBase::SignalMasterImageCaptured)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExecuteInspectBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_ExecuteInspectBase.data,
    qt_meta_data_ExecuteInspectBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExecuteInspectBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExecuteInspectBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExecuteInspectBase.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QThread::qt_metacast(_clname);
}

int ExecuteInspectBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ExecuteInspectBase::SignalCaptured(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExecuteInspectBase::SignalTargetImageCaptured()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExecuteInspectBase::SignalMasterImageCaptured()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
