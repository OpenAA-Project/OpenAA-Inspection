/****************************************************************************
** Meta object code from reading C++ file 'XStatusController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XStatusController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XStatusController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StatusClient_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StatusClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StatusClient_t qt_meta_stringdata_StatusClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StatusClient"
QT_MOC_LITERAL(1, 13, 16), // "SlotDisconnected"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "StatusClient\0SlotDisconnected\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StatusClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void StatusClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StatusClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotDisconnected(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject StatusClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_StatusClient.data,
    qt_meta_data_StatusClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StatusClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatusClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StatusClient.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPList<StatusClient>"))
        return static_cast< NPList<StatusClient>*>(this);
    return QObject::qt_metacast(_clname);
}

int StatusClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_StatusController_t {
    QByteArrayData data[5];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StatusController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StatusController_t qt_meta_stringdata_StatusController = {
    {
QT_MOC_LITERAL(0, 0, 16), // "StatusController"
QT_MOC_LITERAL(1, 17, 17), // "SignalShowComment"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "HTMLMode"
QT_MOC_LITERAL(4, 45, 17) // "SlotNewConnection"

    },
    "StatusController\0SignalShowComment\0\0"
    "HTMLMode\0SlotNewConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StatusController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QStringList,    3,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void StatusController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StatusController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalShowComment((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 1: _t->SlotNewConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StatusController::*)(bool , const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StatusController::SignalShowComment)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StatusController::staticMetaObject = { {
    QMetaObject::SuperData::link<QLocalServer::staticMetaObject>(),
    qt_meta_stringdata_StatusController.data,
    qt_meta_data_StatusController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StatusController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatusController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StatusController.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    if (!strcmp(_clname, "NPListPackSaveLoad<StatusOpinionInGUI>"))
        return static_cast< NPListPackSaveLoad<StatusOpinionInGUI>*>(this);
    return QLocalServer::qt_metacast(_clname);
}

int StatusController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLocalServer::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void StatusController::SignalShowComment(bool _t1, const QStringList & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
