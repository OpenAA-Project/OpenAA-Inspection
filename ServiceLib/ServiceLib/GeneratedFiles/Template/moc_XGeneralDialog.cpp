/****************************************************************************
** Meta object code from reading C++ file 'XGeneralDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XGeneralDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XGeneralDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GeneralDialog_t {
    QByteArrayData data[3];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GeneralDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GeneralDialog_t qt_meta_stringdata_GeneralDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GeneralDialog"
QT_MOC_LITERAL(1, 14, 9), // "SlotClose"
QT_MOC_LITERAL(2, 24, 0) // ""

    },
    "GeneralDialog\0SlotClose\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeneralDialog[] = {

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

void GeneralDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GeneralDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotClose(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject GeneralDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_GeneralDialog.data,
    qt_meta_data_GeneralDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GeneralDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeneralDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralDialog.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QDialog::qt_metacast(_clname);
}

int GeneralDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_GeneralLibFolderForm_t {
    QByteArrayData data[12];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GeneralLibFolderForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GeneralLibFolderForm_t qt_meta_stringdata_GeneralLibFolderForm = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GeneralLibFolderForm"
QT_MOC_LITERAL(1, 21, 15), // "SelectLibFolder"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "LibFolderID"
QT_MOC_LITERAL(4, 50, 10), // "FolderName"
QT_MOC_LITERAL(5, 61, 10), // "SignalDrop"
QT_MOC_LITERAL(6, 72, 14), // "FolderParentID"
QT_MOC_LITERAL(7, 87, 8), // "QWidget*"
QT_MOC_LITERAL(8, 96, 1), // "w"
QT_MOC_LITERAL(9, 98, 19), // "SlotSelectLibFolder"
QT_MOC_LITERAL(10, 118, 1), // "s"
QT_MOC_LITERAL(11, 120, 8) // "SlotDrop"

    },
    "GeneralLibFolderForm\0SelectLibFolder\0"
    "\0LibFolderID\0FolderName\0SignalDrop\0"
    "FolderParentID\0QWidget*\0w\0SlotSelectLibFolder\0"
    "s\0SlotDrop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeneralLibFolderForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   46,    2, 0x08 /* Private */,
      11,    3,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    6,    3,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 7,    6,    3,    8,

       0        // eod
};

void GeneralLibFolderForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GeneralLibFolderForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SignalDrop((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        case 2: _t->SlotSelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->SlotDrop((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QWidget*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GeneralLibFolderForm::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GeneralLibFolderForm::SelectLibFolder)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GeneralLibFolderForm::*)(int , int , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GeneralLibFolderForm::SignalDrop)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GeneralLibFolderForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GeneralLibFolderForm.data,
    qt_meta_data_GeneralLibFolderForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GeneralLibFolderForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeneralLibFolderForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralLibFolderForm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GeneralLibFolderForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void GeneralLibFolderForm::SelectLibFolder(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GeneralLibFolderForm::SignalDrop(int _t1, int _t2, QWidget * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
