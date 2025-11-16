/****************************************************************************
** Meta object code from reading C++ file 'XCommunicatedServer.h'
**
** Created: Thu Sep 10 11:41:25 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XCommunicatedServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XCommunicatedServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CommunicatedServerComm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   47,   47,   47, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   70,   47,   47, 0x09,
      72,   47,   47,   47, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CommunicatedServerComm[] = {
    "CommunicatedServerComm\0SignalExecuteWriteOut()\0"
    "\0SlotReceived(int,int)\0,\0SlotExecuteWriteOut()\0"
};

void CommunicatedServerComm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CommunicatedServerComm *_t = static_cast<CommunicatedServerComm *>(_o);
        switch (_id) {
        case 0: _t->SignalExecuteWriteOut(); break;
        case 1: _t->SlotReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->SlotExecuteWriteOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CommunicatedServerComm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CommunicatedServerComm::staticMetaObject = {
    { &FastComm::staticMetaObject, qt_meta_stringdata_CommunicatedServerComm,
      qt_meta_data_CommunicatedServerComm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CommunicatedServerComm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CommunicatedServerComm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CommunicatedServerComm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommunicatedServerComm))
        return static_cast<void*>(const_cast< CommunicatedServerComm*>(this));
    return FastComm::qt_metacast(_clname);
}

int CommunicatedServerComm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FastComm::qt_metacall(_c, _id, _a);
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
void CommunicatedServerComm::SignalExecuteWriteOut()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
