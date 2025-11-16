/****************************************************************************
** Meta object code from reading C++ file 'XMLServerV3.h'
**
** Created: Thu Sep 10 11:41:21 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../XMLServerV3.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XMLServerV3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_XMLServerV3[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   32,   35,   35, 0x08,
      36,   79,   35,   35, 0x08,
     121,   35,   35,   35, 0x08,
     135,   35,   35,   35, 0x08,
     150,   35,   35,   35, 0x08,
     165,   35,   35,   35, 0x08,
     194,  241,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_XMLServerV3[] = {
    "XMLServerV3\0SlotShowClient(int)\0id\0\0"
    "SlotAnalize(QDateTime,int,int,QString,int)\0"
    "tm,ClientID,OpeHandleCode,Command,milisec\0"
    "slotSetting()\0SlotProgress()\0"
    "slotWriteOut()\0on_checkBoxShowAll_clicked()\0"
    "on_tableWidgetTable_doubleClicked(QModelIndex)\0"
    "index\0"
};

void XMLServerV3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        XMLServerV3 *_t = static_cast<XMLServerV3 *>(_o);
        switch (_id) {
        case 0: _t->SlotShowClient((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SlotAnalize((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->slotSetting(); break;
        case 3: _t->SlotProgress(); break;
        case 4: _t->slotWriteOut(); break;
        case 5: _t->on_checkBoxShowAll_clicked(); break;
        case 6: _t->on_tableWidgetTable_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData XMLServerV3::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject XMLServerV3::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_XMLServerV3,
      qt_meta_data_XMLServerV3, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &XMLServerV3::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *XMLServerV3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *XMLServerV3::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_XMLServerV3))
        return static_cast<void*>(const_cast< XMLServerV3*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int XMLServerV3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
