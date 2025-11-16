/****************************************************************************
** Meta object code from reading C++ file 'XFastComm.h'
**
** Created: Thu Sep 10 11:41:22 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Open/XFastComm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XFastComm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FastCommLeaf[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   37,   44,   44, 0x05,
      45,   69,   44,   44, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   44,   44,   44, 0x08,
      88,   44,   44,   44, 0x08,
     107,   44,   44,   44, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FastCommLeaf[] = {
    "FastCommLeaf\0SignalReceived(int,int)\0"
    "ID,Cmd\0\0SignalDisconnected(int)\0id\0"
    "SlotConnected()\0SlotDisconnected()\0"
    "SlotReadyRead()\0"
};

void FastCommLeaf::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FastCommLeaf *_t = static_cast<FastCommLeaf *>(_o);
        switch (_id) {
        case 0: _t->SignalReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SignalDisconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SlotConnected(); break;
        case 3: _t->SlotDisconnected(); break;
        case 4: _t->SlotReadyRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FastCommLeaf::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FastCommLeaf::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FastCommLeaf,
      qt_meta_data_FastCommLeaf, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FastCommLeaf::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FastCommLeaf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FastCommLeaf::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FastCommLeaf))
        return static_cast<void*>(const_cast< FastCommLeaf*>(this));
    return QObject::qt_metacast(_clname);
}

int FastCommLeaf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FastCommLeaf::SignalReceived(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FastCommLeaf::SignalDisconnected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_CommBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   29,   29,   29, 0x09,
      30,   52,   29,   29, 0x09,
      54,   76,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CommBase[] = {
    "CommBase\0SlotNewConnection()\0\0"
    "SlotReceived(int,int)\0,\0SlotDisconnected(int)\0"
    "id\0"
};

void CommBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CommBase *_t = static_cast<CommBase *>(_o);
        switch (_id) {
        case 0: _t->SlotNewConnection(); break;
        case 1: _t->SlotReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->SlotDisconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CommBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CommBase::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_CommBase,
      qt_meta_data_CommBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CommBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CommBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CommBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommBase))
        return static_cast<void*>(const_cast< CommBase*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int CommBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_FastComm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,   29,   29,   29, 0x08,
      30,   52,   29,   29, 0x09,
      54,   76,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_FastComm[] = {
    "FastComm\0SlotNewConnection()\0\0"
    "SlotReceived(int,int)\0,\0SlotDisconnected(int)\0"
    "id\0"
};

void FastComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FastComm *_t = static_cast<FastComm *>(_o);
        switch (_id) {
        case 0: _t->SlotNewConnection(); break;
        case 1: _t->SlotReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->SlotDisconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FastComm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FastComm::staticMetaObject = {
    { &CommBase::staticMetaObject, qt_meta_stringdata_FastComm,
      qt_meta_data_FastComm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FastComm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FastComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FastComm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FastComm))
        return static_cast<void*>(const_cast< FastComm*>(this));
    return CommBase::qt_metacast(_clname);
}

int FastComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CommBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
