/****************************************************************************
** Meta object code from reading C++ file 'XNamedPipe.h'
**
** Created: Thu Sep 10 11:41:23 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Open/XNamedPipe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XNamedPipe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WatchdogInstance[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   33,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WatchdogInstance[] = {
    "WatchdogInstance\0SlotReadyRead()\0\0"
};

void WatchdogInstance::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WatchdogInstance *_t = static_cast<WatchdogInstance *>(_o);
        switch (_id) {
        case 0: _t->SlotReadyRead(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WatchdogInstance::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WatchdogInstance::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_WatchdogInstance,
      qt_meta_data_WatchdogInstance, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WatchdogInstance::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WatchdogInstance::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WatchdogInstance::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WatchdogInstance))
        return static_cast<void*>(const_cast< WatchdogInstance*>(this));
    return QObject::qt_metacast(_clname);
}

int WatchdogInstance::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_WatchdogInProgram[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   38,   38,   38, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WatchdogInProgram[] = {
    "WatchdogInProgram\0SlotNewConnection()\0"
    "\0"
};

void WatchdogInProgram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WatchdogInProgram *_t = static_cast<WatchdogInProgram *>(_o);
        switch (_id) {
        case 0: _t->SlotNewConnection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WatchdogInProgram::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WatchdogInProgram::staticMetaObject = {
    { &QLocalServer::staticMetaObject, qt_meta_stringdata_WatchdogInProgram,
      qt_meta_data_WatchdogInProgram, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WatchdogInProgram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WatchdogInProgram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WatchdogInProgram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WatchdogInProgram))
        return static_cast<void*>(const_cast< WatchdogInProgram*>(this));
    return QLocalServer::qt_metacast(_clname);
}

int WatchdogInProgram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLocalServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
