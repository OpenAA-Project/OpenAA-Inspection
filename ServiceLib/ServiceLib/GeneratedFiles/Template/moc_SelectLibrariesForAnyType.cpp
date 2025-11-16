/****************************************************************************
** Meta object code from reading C++ file 'SelectLibrariesForAnyType.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SelectLibrariesForAnyType.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectLibrariesForAnyType.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectLibrariesForAnyType_t {
    QByteArrayData data[10];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectLibrariesForAnyType_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectLibrariesForAnyType_t qt_meta_stringdata_SelectLibrariesForAnyType = {
    {
QT_MOC_LITERAL(0, 0, 25), // "SelectLibrariesForAnyType"
QT_MOC_LITERAL(1, 26, 40), // "on_tableWidgetSelectedList_do..."
QT_MOC_LITERAL(2, 67, 0), // ""
QT_MOC_LITERAL(3, 68, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 80, 5), // "index"
QT_MOC_LITERAL(5, 86, 35), // "on_tableWidgetLibList_doubleC..."
QT_MOC_LITERAL(6, 122, 36), // "on_comboBLibType_currentIndex..."
QT_MOC_LITERAL(7, 159, 19), // "SlotSelectLibFolder"
QT_MOC_LITERAL(8, 179, 11), // "LibFolderID"
QT_MOC_LITERAL(9, 191, 10) // "FolderName"

    },
    "SelectLibrariesForAnyType\0"
    "on_tableWidgetSelectedList_doubleClicked\0"
    "\0QModelIndex\0index\0"
    "on_tableWidgetLibList_doubleClicked\0"
    "on_comboBLibType_currentIndexChanged\0"
    "SlotSelectLibFolder\0LibFolderID\0"
    "FolderName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectLibrariesForAnyType[] = {

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
       1,    1,   34,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,
       6,    1,   40,    2, 0x08 /* Private */,
       7,    2,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    9,

       0        // eod
};

void SelectLibrariesForAnyType::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectLibrariesForAnyType *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_tableWidgetSelectedList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_tableWidgetLibList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->on_comboBLibType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SlotSelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectLibrariesForAnyType::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SelectLibrariesForAnyType.data,
    qt_meta_data_SelectLibrariesForAnyType,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectLibrariesForAnyType::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectLibrariesForAnyType::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectLibrariesForAnyType.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QWidget::qt_metacast(_clname);
}

int SelectLibrariesForAnyType::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
