/****************************************************************************
** Meta object code from reading C++ file 'XSyncGUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XSyncGUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XSyncGUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SyncGUIPipe_t {
    QByteArrayData data[8];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SyncGUIPipe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SyncGUIPipe_t qt_meta_stringdata_SyncGUIPipe = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SyncGUIPipe"
QT_MOC_LITERAL(1, 12, 13), // "SignalReceive"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 22), // "SlotDisconnectedClient"
QT_MOC_LITERAL(4, 50, 24), // "SlotDisconnectedReceiver"
QT_MOC_LITERAL(5, 75, 19), // "SlotReadyReadClient"
QT_MOC_LITERAL(6, 95, 21), // "SlotReadyReadReceiver"
QT_MOC_LITERAL(7, 117, 11) // "SlotReceive"

    },
    "SyncGUIPipe\0SignalReceive\0\0"
    "SlotDisconnectedClient\0SlotDisconnectedReceiver\0"
    "SlotReadyReadClient\0SlotReadyReadReceiver\0"
    "SlotReceive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyncGUIPipe[] = {

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
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SyncGUIPipe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SyncGUIPipe *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalReceive(); break;
        case 1: _t->SlotDisconnectedClient(); break;
        case 2: _t->SlotDisconnectedReceiver(); break;
        case 3: _t->SlotReadyReadClient(); break;
        case 4: _t->SlotReadyReadReceiver(); break;
        case 5: _t->SlotReceive(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SyncGUIPipe::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SyncGUIPipe::SignalReceive)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SyncGUIPipe::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SyncGUIPipe.data,
    qt_meta_data_SyncGUIPipe,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SyncGUIPipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyncGUIPipe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SyncGUIPipe.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPList<SyncGUIPipe>"))
        return static_cast< NPList<SyncGUIPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int SyncGUIPipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SyncGUIPipe::SignalReceive()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_SyncGUIPack_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SyncGUIPack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SyncGUIPack_t qt_meta_stringdata_SyncGUIPack = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SyncGUIPack"
QT_MOC_LITERAL(1, 12, 17), // "SlotNewConnection"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "SyncGUIPack\0SlotNewConnection\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SyncGUIPack[] = {

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

void SyncGUIPack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SyncGUIPack *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotNewConnection(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SyncGUIPack::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SyncGUIPack.data,
    qt_meta_data_SyncGUIPack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SyncGUIPack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SyncGUIPack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SyncGUIPack.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "NPListPack<SyncGUIPipe>"))
        return static_cast< NPListPack<SyncGUIPipe>*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QObject::qt_metacast(_clname);
}

int SyncGUIPack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
