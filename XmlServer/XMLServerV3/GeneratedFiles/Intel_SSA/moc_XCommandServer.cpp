/****************************************************************************
** Meta object code from reading C++ file 'XCommandServer.h'
**
** Created: Thu Sep 10 11:41:24 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XCommandServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XCommandServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XMLCommandExecuter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   41,   44,   44, 0x05,
      45,   44,   44,   44, 0x05,
      56,  101,   44,   44, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_XMLCommandExecuter[] = {
    "XMLCommandExecuter\0SignalShowClient(int)\0"
    "id\0\0SignalTx()\0"
    "SignalAnalize(QDateTime,int,int,QString,int)\0"
    "tm,ClientID,OpeHandleCode,Command,milisec\0"
};

void XMLCommandExecuter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XMLCommandExecuter *_t = static_cast<XMLCommandExecuter *>(_o);
        switch (_id) {
        case 0: _t->SignalShowClient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SignalTx(); break;
        case 2: _t->SignalAnalize((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XMLCommandExecuter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XMLCommandExecuter::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_XMLCommandExecuter,
      qt_meta_data_XMLCommandExecuter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLCommandExecuter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLCommandExecuter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLCommandExecuter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLCommandExecuter))
        return static_cast<void*>(const_cast< XMLCommandExecuter*>(this));
    return QThread::qt_metacast(_clname);
}

int XMLCommandExecuter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void XMLCommandExecuter::SignalShowClient(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XMLCommandExecuter::SignalTx()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void XMLCommandExecuter::SignalAnalize(QDateTime _t1, int _t2, int _t3, QString _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_SClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,   32,   32,   32, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   32,   32,   32, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SClient[] = {
    "SClient\0SignalCheckUnsedTable()\0\0"
    "SlotTx()\0"
};

void SClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SClient *_t = static_cast<SClient *>(_o);
        switch (_id) {
        case 0: _t->SignalCheckUnsedTable(); break;
        case 1: _t->SlotTx(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SClient::staticMetaObject = {
    { &FastCommLeaf::staticMetaObject, qt_meta_stringdata_SClient,
      qt_meta_data_SClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SClient))
        return static_cast<void*>(const_cast< SClient*>(this));
    if (!strcmp(_clname, "NPListPack<ClientOperation>"))
        return static_cast< NPListPack<ClientOperation>*>(const_cast< SClient*>(this));
    return FastCommLeaf::qt_metacast(_clname);
}

int SClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FastCommLeaf::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SClient::SignalCheckUnsedTable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_XMLServerComm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   36,   39,   39, 0x05,
      40,   85,   39,   39, 0x05,
     127,   39,   39,   39, 0x05,

 // slots: signature, parameters, type, tag, flags
     144,   36,   39,   39, 0x0a,
     164,   85,   39,   39, 0x0a,
     207,   39,   39,   39, 0x0a,
     229,   39,   39,   39, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_XMLServerComm[] = {
    "XMLServerComm\0SignalShowClient(int)\0"
    "id\0\0SignalAnalize(QDateTime,int,int,QString,int)\0"
    "tm,ClientID,OpeHandleCode,Command,milisec\0"
    "SignalProgress()\0SlotShowClient(int)\0"
    "SlotAnalize(QDateTime,int,int,QString,int)\0"
    "SlotCheckUnsedTable()\0SlotTimeOut()\0"
};

void XMLServerComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XMLServerComm *_t = static_cast<XMLServerComm *>(_o);
        switch (_id) {
        case 0: _t->SignalShowClient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SignalAnalize((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->SignalProgress(); break;
        case 3: _t->SlotShowClient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SlotAnalize((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 5: _t->SlotCheckUnsedTable(); break;
        case 6: _t->SlotTimeOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XMLServerComm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XMLServerComm::staticMetaObject = {
    { &FastComm::staticMetaObject, qt_meta_stringdata_XMLServerComm,
      qt_meta_data_XMLServerComm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLServerComm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLServerComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLServerComm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLServerComm))
        return static_cast<void*>(const_cast< XMLServerComm*>(this));
    if (!strcmp(_clname, "ParamBase"))
        return static_cast< ParamBase*>(const_cast< XMLServerComm*>(this));
    if (!strcmp(_clname, "XMLStocker"))
        return static_cast< XMLStocker*>(const_cast< XMLServerComm*>(this));
    return FastComm::qt_metacast(_clname);
}

int XMLServerComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FastComm::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void XMLServerComm::SignalShowClient(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XMLServerComm::SignalAnalize(QDateTime _t1, int _t2, int _t3, QString _t4, int _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void XMLServerComm::SignalProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
