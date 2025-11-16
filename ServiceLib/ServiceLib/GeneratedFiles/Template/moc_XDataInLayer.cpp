/****************************************************************************
** Meta object code from reading C++ file 'XDataInLayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../Open/XDataInLayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XDataInLayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataInLayer_t {
    QByteArrayData data[5];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataInLayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataInLayer_t qt_meta_stringdata_DataInLayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DataInLayer"
QT_MOC_LITERAL(1, 12, 24), // "SignalChangedMasterImage"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 7), // "LayerNo"
QT_MOC_LITERAL(4, 46, 22) // "SlotChangedMasterImage"

    },
    "DataInLayer\0SignalChangedMasterImage\0"
    "\0LayerNo\0SlotChangedMasterImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataInLayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DataInLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataInLayer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalChangedMasterImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SlotChangedMasterImage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataInLayer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataInLayer::SignalChangedMasterImage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataInLayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataInLayer.data,
    qt_meta_data_DataInLayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataInLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataInLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataInLayer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    return QObject::qt_metacast(_clname);
}

int DataInLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataInLayer::SignalChangedMasterImage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_DataInPage_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataInPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataInPage_t qt_meta_stringdata_DataInPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DataInPage"
QT_MOC_LITERAL(1, 11, 24), // "SignalChangedMasterImage"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "PageNo"
QT_MOC_LITERAL(4, 44, 7), // "LayerNo"
QT_MOC_LITERAL(5, 52, 22) // "SlotChangedMasterImage"

    },
    "DataInPage\0SignalChangedMasterImage\0"
    "\0PageNo\0LayerNo\0SlotChangedMasterImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataInPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void DataInPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataInPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalChangedMasterImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->SlotChangedMasterImage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataInPage::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataInPage::SignalChangedMasterImage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataInPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataInPage.data,
    qt_meta_data_DataInPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataInPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataInPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataInPage.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "LearningInPage"))
        return static_cast< LearningInPage*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    return QObject::qt_metacast(_clname);
}

int DataInPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataInPage::SignalChangedMasterImage(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_PageDataInOnePhase_t {
    QByteArrayData data[9];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PageDataInOnePhase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PageDataInOnePhase_t qt_meta_stringdata_PageDataInOnePhase = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PageDataInOnePhase"
QT_MOC_LITERAL(1, 19, 24), // "SignalChangedMasterImage"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "phase"
QT_MOC_LITERAL(4, 51, 4), // "Page"
QT_MOC_LITERAL(5, 56, 5), // "Layer"
QT_MOC_LITERAL(6, 62, 22), // "SlotChangedMasterImage"
QT_MOC_LITERAL(7, 85, 6), // "PageNo"
QT_MOC_LITERAL(8, 92, 7) // "LayerNo"

    },
    "PageDataInOnePhase\0SignalChangedMasterImage\0"
    "\0phase\0Page\0Layer\0SlotChangedMasterImage\0"
    "PageNo\0LayerNo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PageDataInOnePhase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

       0        // eod
};

void PageDataInOnePhase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PageDataInOnePhase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalChangedMasterImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->SlotChangedMasterImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PageDataInOnePhase::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PageDataInOnePhase::SignalChangedMasterImage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PageDataInOnePhase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PageDataInOnePhase.data,
    qt_meta_data_PageDataInOnePhase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PageDataInOnePhase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PageDataInOnePhase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PageDataInOnePhase.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    return QObject::qt_metacast(_clname);
}

int PageDataInOnePhase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PageDataInOnePhase::SignalChangedMasterImage(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_LayersBase_t {
    QByteArrayData data[20];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LayersBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LayersBase_t qt_meta_stringdata_LayersBase = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LayersBase"
QT_MOC_LITERAL(1, 11, 21), // "SignalMainFormCommand"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 3), // "cmd"
QT_MOC_LITERAL(4, 38, 15), // "SignalChangedXY"
QT_MOC_LITERAL(5, 54, 27), // "SignalChangedPhasePageLayer"
QT_MOC_LITERAL(6, 82, 24), // "SignalChangeCurrentPhase"
QT_MOC_LITERAL(7, 107, 34), // "SignalChangeCurrentStrategicN..."
QT_MOC_LITERAL(8, 142, 37), // "SignalChangeCurrentStrategicN..."
QT_MOC_LITERAL(9, 180, 26), // "SignalChangeThresholdLevel"
QT_MOC_LITERAL(10, 207, 10), // "OldLevelID"
QT_MOC_LITERAL(11, 218, 10), // "NewLevelID"
QT_MOC_LITERAL(12, 229, 24), // "SignalChangedMasterImage"
QT_MOC_LITERAL(13, 254, 5), // "Phase"
QT_MOC_LITERAL(14, 260, 4), // "Page"
QT_MOC_LITERAL(15, 265, 5), // "Layer"
QT_MOC_LITERAL(16, 271, 22), // "SlotChangedMasterImage"
QT_MOC_LITERAL(17, 294, 7), // "PhaseNo"
QT_MOC_LITERAL(18, 302, 6), // "PageNo"
QT_MOC_LITERAL(19, 309, 7) // "LayerNo"

    },
    "LayersBase\0SignalMainFormCommand\0\0cmd\0"
    "SignalChangedXY\0SignalChangedPhasePageLayer\0"
    "SignalChangeCurrentPhase\0"
    "SignalChangeCurrentStrategicNumber\0"
    "SignalChangeCurrentStrategicNumberSeq\0"
    "SignalChangeThresholdLevel\0OldLevelID\0"
    "NewLevelID\0SignalChangedMasterImage\0"
    "Phase\0Page\0Layer\0SlotChangedMasterImage\0"
    "PhaseNo\0PageNo\0LayerNo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LayersBase[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    0,   63,    2, 0x06 /* Public */,
       6,    0,   64,    2, 0x06 /* Public */,
       7,    0,   65,    2, 0x06 /* Public */,
       8,    0,   66,    2, 0x06 /* Public */,
       9,    2,   67,    2, 0x06 /* Public */,
      12,    3,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    3,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   17,   18,   19,

       0        // eod
};

void LayersBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LayersBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalMainFormCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SignalChangedXY(); break;
        case 2: _t->SignalChangedPhasePageLayer(); break;
        case 3: _t->SignalChangeCurrentPhase(); break;
        case 4: _t->SignalChangeCurrentStrategicNumber(); break;
        case 5: _t->SignalChangeCurrentStrategicNumberSeq(); break;
        case 6: _t->SignalChangeThresholdLevel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->SignalChangedMasterImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->SlotChangedMasterImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LayersBase::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalMainFormCommand)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangedXY)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangedPhasePageLayer)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangeCurrentPhase)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangeCurrentStrategicNumber)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangeCurrentStrategicNumberSeq)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangeThresholdLevel)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LayersBase::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayersBase::SignalChangedMasterImage)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LayersBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LayersBase.data,
    qt_meta_data_LayersBase,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LayersBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayersBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LayersBase.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AuthenticationInComponent"))
        return static_cast< AuthenticationInComponent*>(this);
    if (!strcmp(_clname, "ShadowTree"))
        return static_cast< ShadowTree*>(this);
    if (!strcmp(_clname, "IdentifiedClass"))
        return static_cast< IdentifiedClass*>(this);
    return QObject::qt_metacast(_clname);
}

int LayersBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void LayersBase::SignalMainFormCommand(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayersBase::SignalChangedXY()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LayersBase::SignalChangedPhasePageLayer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LayersBase::SignalChangeCurrentPhase()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LayersBase::SignalChangeCurrentStrategicNumber()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LayersBase::SignalChangeCurrentStrategicNumberSeq()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LayersBase::SignalChangeThresholdLevel(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LayersBase::SignalChangedMasterImage(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
