/****************************************************************************
** Meta object code from reading C++ file 'XIntegrationComm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Integrator/IntegrationLib/XIntegrationComm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XIntegrationComm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IntegrationCommPipe_t {
    QByteArrayData data[10];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntegrationCommPipe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntegrationCommPipe_t qt_meta_stringdata_IntegrationCommPipe = {
    {
QT_MOC_LITERAL(0, 0, 19), // "IntegrationCommPipe"
QT_MOC_LITERAL(1, 20, 14), // "SignalReceived"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "SlaveNo"
QT_MOC_LITERAL(4, 44, 3), // "Cmd"
QT_MOC_LITERAL(5, 48, 29), // "SlotOneShotTimerForConnection"
QT_MOC_LITERAL(6, 78, 22), // "SlotDisconnectedClient"
QT_MOC_LITERAL(7, 101, 24), // "SlotDisconnectedReceiver"
QT_MOC_LITERAL(8, 126, 19), // "SlotReadyReadClient"
QT_MOC_LITERAL(9, 146, 21) // "SlotReadyReadReceiver"

    },
    "IntegrationCommPipe\0SignalReceived\0\0"
    "SlaveNo\0Cmd\0SlotOneShotTimerForConnection\0"
    "SlotDisconnectedClient\0SlotDisconnectedReceiver\0"
    "SlotReadyReadClient\0SlotReadyReadReceiver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntegrationCommPipe[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   49,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IntegrationCommPipe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegrationCommPipe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SlotOneShotTimerForConnection(); break;
        case 2: _t->SlotDisconnectedClient(); break;
        case 3: _t->SlotDisconnectedReceiver(); break;
        case 4: _t->SlotReadyReadClient(); break;
        case 5: _t->SlotReadyReadReceiver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IntegrationCommPipe::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegrationCommPipe::SignalReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IntegrationCommPipe::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IntegrationCommPipe.data,
    qt_meta_data_IntegrationCommPipe,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntegrationCommPipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegrationCommPipe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntegrationCommPipe.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPList<IntegrationCommPipe>"))
        return static_cast< NPList<IntegrationCommPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int IntegrationCommPipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void IntegrationCommPipe::SignalReceived(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_IntegrationCommPack_t {
    QByteArrayData data[6];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntegrationCommPack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntegrationCommPack_t qt_meta_stringdata_IntegrationCommPack = {
    {
QT_MOC_LITERAL(0, 0, 19), // "IntegrationCommPack"
QT_MOC_LITERAL(1, 20, 17), // "SlotNewConnection"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 22), // "SlotNewSlaveConnection"
QT_MOC_LITERAL(4, 62, 12), // "SlotReceived"
QT_MOC_LITERAL(5, 75, 11) // "SlotTimeOut"

    },
    "IntegrationCommPack\0SlotNewConnection\0"
    "\0SlotNewSlaveConnection\0SlotReceived\0"
    "SlotTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntegrationCommPack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    2,   36,    2, 0x08 /* Private */,
       5,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

       0        // eod
};

void IntegrationCommPack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegrationCommPack *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotNewConnection(); break;
        case 1: _t->SlotNewSlaveConnection(); break;
        case 2: _t->SlotReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->SlotTimeOut(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IntegrationCommPack::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IntegrationCommPack.data,
    qt_meta_data_IntegrationCommPack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntegrationCommPack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegrationCommPack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntegrationCommPack.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPListPack<IntegrationCommPipe>"))
        return static_cast< NPListPack<IntegrationCommPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int IntegrationCommPack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_IntegrationPageDirectlyCommPipe_t {
    QByteArrayData data[11];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntegrationPageDirectlyCommPipe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntegrationPageDirectlyCommPipe_t qt_meta_stringdata_IntegrationPageDirectlyCommPipe = {
    {
QT_MOC_LITERAL(0, 0, 31), // "IntegrationPageDirectlyCommPipe"
QT_MOC_LITERAL(1, 32, 14), // "SignalReceived"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 7), // "SlaveNo"
QT_MOC_LITERAL(4, 56, 3), // "Cmd"
QT_MOC_LITERAL(5, 60, 10), // "globalPage"
QT_MOC_LITERAL(6, 71, 29), // "SlotOneShotTimerForConnection"
QT_MOC_LITERAL(7, 101, 22), // "SlotDisconnectedClient"
QT_MOC_LITERAL(8, 124, 24), // "SlotDisconnectedReceiver"
QT_MOC_LITERAL(9, 149, 19), // "SlotReadyReadClient"
QT_MOC_LITERAL(10, 169, 21) // "SlotReadyReadReceiver"

    },
    "IntegrationPageDirectlyCommPipe\0"
    "SignalReceived\0\0SlaveNo\0Cmd\0globalPage\0"
    "SlotOneShotTimerForConnection\0"
    "SlotDisconnectedClient\0SlotDisconnectedReceiver\0"
    "SlotReadyReadClient\0SlotReadyReadReceiver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntegrationPageDirectlyCommPipe[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   51,    2, 0x09 /* Protected */,
       7,    0,   52,    2, 0x09 /* Protected */,
       8,    0,   53,    2, 0x09 /* Protected */,
       9,    0,   54,    2, 0x09 /* Protected */,
      10,    0,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IntegrationPageDirectlyCommPipe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegrationPageDirectlyCommPipe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->SlotOneShotTimerForConnection(); break;
        case 2: _t->SlotDisconnectedClient(); break;
        case 3: _t->SlotDisconnectedReceiver(); break;
        case 4: _t->SlotReadyReadClient(); break;
        case 5: _t->SlotReadyReadReceiver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IntegrationPageDirectlyCommPipe::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegrationPageDirectlyCommPipe::SignalReceived)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IntegrationPageDirectlyCommPipe::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IntegrationPageDirectlyCommPipe.data,
    qt_meta_data_IntegrationPageDirectlyCommPipe,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntegrationPageDirectlyCommPipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegrationPageDirectlyCommPipe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntegrationPageDirectlyCommPipe.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPList<IntegrationPageDirectlyCommPipe>"))
        return static_cast< NPList<IntegrationPageDirectlyCommPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int IntegrationPageDirectlyCommPipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void IntegrationPageDirectlyCommPipe::SignalReceived(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_IntegrationPageDirectlyCommPack_t {
    QByteArrayData data[5];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntegrationPageDirectlyCommPack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntegrationPageDirectlyCommPack_t qt_meta_stringdata_IntegrationPageDirectlyCommPack = {
    {
QT_MOC_LITERAL(0, 0, 31), // "IntegrationPageDirectlyCommPack"
QT_MOC_LITERAL(1, 32, 22), // "SlotNewSlaveConnection"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 12), // "SlotReceived"
QT_MOC_LITERAL(4, 69, 11) // "SlotTimeOut"

    },
    "IntegrationPageDirectlyCommPack\0"
    "SlotNewSlaveConnection\0\0SlotReceived\0"
    "SlotTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntegrationPageDirectlyCommPack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    3,   30,    2, 0x08 /* Private */,
       4,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,

       0        // eod
};

void IntegrationPageDirectlyCommPack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegrationPageDirectlyCommPack *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotNewSlaveConnection(); break;
        case 1: _t->SlotReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->SlotTimeOut(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IntegrationPageDirectlyCommPack::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IntegrationPageDirectlyCommPack.data,
    qt_meta_data_IntegrationPageDirectlyCommPack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntegrationPageDirectlyCommPack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegrationPageDirectlyCommPack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntegrationPageDirectlyCommPack.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPListPack<IntegrationPageDirectlyCommPipe>"))
        return static_cast< NPListPack<IntegrationPageDirectlyCommPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int IntegrationPageDirectlyCommPack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
