/****************************************************************************
** Meta object code from reading C++ file 'SelectMaskingLibraryForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SelectMaskingLibraryForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectMaskingLibraryForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SelectMaskingLibraryForm_t {
    QByteArrayData data[9];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectMaskingLibraryForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectMaskingLibraryForm_t qt_meta_stringdata_SelectMaskingLibraryForm = {
    {
QT_MOC_LITERAL(0, 0, 24), // "SelectMaskingLibraryForm"
QT_MOC_LITERAL(1, 25, 35), // "on_tableWidgetLibList_doubleC..."
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 74, 23), // "on_ButtonCancel_clicked"
QT_MOC_LITERAL(5, 98, 23), // "on_ButtonSelect_clicked"
QT_MOC_LITERAL(6, 122, 19), // "SlotSelectLibFolder"
QT_MOC_LITERAL(7, 142, 11), // "LibFolderID"
QT_MOC_LITERAL(8, 154, 10) // "FolderName"

    },
    "SelectMaskingLibraryForm\0"
    "on_tableWidgetLibList_doubleClicked\0"
    "\0QModelIndex\0on_ButtonCancel_clicked\0"
    "on_ButtonSelect_clicked\0SlotSelectLibFolder\0"
    "LibFolderID\0FolderName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectMaskingLibraryForm[] = {

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
       4,    0,   37,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    2,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,

       0        // eod
};

void SelectMaskingLibraryForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectMaskingLibraryForm *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_tableWidgetLibList_doubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_ButtonCancel_clicked(); break;
        case 2: _t->on_ButtonSelect_clicked(); break;
        case 3: _t->SlotSelectLibFolder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectMaskingLibraryForm::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_SelectMaskingLibraryForm.data,
    qt_meta_data_SelectMaskingLibraryForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectMaskingLibraryForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectMaskingLibraryForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectMaskingLibraryForm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(this);
    return QDialog::qt_metacast(_clname);
}

int SelectMaskingLibraryForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
