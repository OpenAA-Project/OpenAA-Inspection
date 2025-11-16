/****************************************************************************
** Meta object code from reading C++ file 'SettingCameraDialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SettingCameraDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingCameraDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SettingCameraDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   21,   20,   20, 0x08,
      74,   68,   20,   20, 0x08,
     126,  120,   20,   20, 0x08,
     174,  120,   20,   20, 0x08,
     220,  120,   20,   20, 0x08,
     263,  120,   20,   20, 0x08,
     306,  120,   20,   20, 0x08,
     354,  120,   20,   20, 0x08,
     397,  120,   20,   20, 0x08,
     447,  120,   20,   20, 0x08,
     495,  120,   20,   20, 0x08,
     537,  120,   20,   20, 0x08,
     579,  120,   20,   20, 0x08,
     622,  120,   20,   20, 0x08,
     668,  120,   20,   20, 0x08,
     710,  120,   20,   20, 0x08,
     751,  120,   20,   20, 0x08,
     793,  120,   20,   20, 0x08,
     839,   20,   20,   20, 0x08,
     870,   20,   20,   20, 0x08,
     901,   20,   20,   20, 0x08,
     933,   20,   20,   20, 0x08,
     963,   20,   20,   20, 0x08,
     990,   20,   20,   20, 0x08,
    1017,   20,   20,   20, 0x08,
    1049,   20,   20,   20, 0x08,
    1076,   20,   20,   20, 0x08,
    1110,   20,   20,   20, 0x08,
    1142,   20,   20,   20, 0x08,
    1168,   68,   20,   20, 0x08,
    1219,   20,   20,   20, 0x08,
    1245,   20,   20,   20, 0x08,
    1272,   20,   20,   20, 0x08,
    1302,   20,   20,   20, 0x08,
    1328,   20,   20,   20, 0x08,
    1353,   20,   20,   20, 0x08,
    1379,   20,   20,   20, 0x08,
    1409,   20,   20,   20, 0x08,
    1435,   20,   20,   20, 0x08,
    1465,   20,   20,   20, 0x08,
    1493,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SettingCameraDialog[] = {
    "SettingCameraDialog\0\0arg1\0"
    "on_spinBoxTotalCamCount_valueChanged(int)\0"
    "index\0on_comboBoxImageSize_currentIndexChanged(int)\0"
    "value\0on_horizontalSliderBrightness_valueChanged(int)\0"
    "on_horizontalSliderContrast_valueChanged(int)\0"
    "on_horizontalSliderColor_valueChanged(int)\0"
    "on_horizontalSliderVivid_valueChanged(int)\0"
    "on_horizontalSliderVividation_valueChanged(int)\0"
    "on_horizontalSliderGamma_valueChanged(int)\0"
    "on_horizontalSliderWhiteBalance_valueChanged(int)\0"
    "on_horizontalSliderReflection_valueChanged(int)\0"
    "on_horizontalSliderGain_valueChanged(int)\0"
    "on_horizontalSliderZoom_valueChanged(int)\0"
    "on_horizontalSliderFocus_valueChanged(int)\0"
    "on_horizontalSliderExposure_valueChanged(int)\0"
    "on_horizontalSliderIris_valueChanged(int)\0"
    "on_horizontalSliderPan_valueChanged(int)\0"
    "on_horizontalSliderTilt_valueChanged(int)\0"
    "on_horizontalSliderRotation_valueChanged(int)\0"
    "on_checkBoxAdjustLow_clicked()\0"
    "on_pushButtonDefault_clicked()\0"
    "on_checkBoxBrightness_clicked()\0"
    "on_checkBoxContrast_clicked()\0"
    "on_checkBoxColor_clicked()\0"
    "on_checkBoxVivid_clicked()\0"
    "on_checkBoxVividation_clicked()\0"
    "on_checkBoxGamma_clicked()\0"
    "on_checkBoxWhiteBalance_clicked()\0"
    "on_checkBoxReflection_clicked()\0"
    "on_checkBoxGain_clicked()\0"
    "on_comboBoxPowerFrequency_currentIndexChanged(int)\0"
    "on_checkBoxZoom_clicked()\0"
    "on_checkBoxFocus_clicked()\0"
    "on_checkBoxExposure_clicked()\0"
    "on_checkBoxIris_clicked()\0"
    "on_checkBoxPan_clicked()\0"
    "on_checkBoxTilt_clicked()\0"
    "on_checkBoxRotation_clicked()\0"
    "on_pushButtonOK_clicked()\0"
    "on_pushButtonCancel_clicked()\0"
    "on_pushButtonSave_clicked()\0"
    "on_pushButtonLoad_clicked()\0"
};

void SettingCameraDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SettingCameraDialog *_t = static_cast<SettingCameraDialog *>(_o);
        switch (_id) {
        case 0: _t->on_spinBoxTotalCamCount_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_comboBoxImageSize_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSliderBrightness_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_horizontalSliderContrast_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_horizontalSliderColor_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_horizontalSliderVivid_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_horizontalSliderVividation_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_horizontalSliderGamma_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_horizontalSliderWhiteBalance_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_horizontalSliderReflection_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_horizontalSliderGain_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_horizontalSliderZoom_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_horizontalSliderFocus_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_horizontalSliderExposure_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_horizontalSliderIris_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_horizontalSliderPan_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_horizontalSliderTilt_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_horizontalSliderRotation_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_checkBoxAdjustLow_clicked(); break;
        case 19: _t->on_pushButtonDefault_clicked(); break;
        case 20: _t->on_checkBoxBrightness_clicked(); break;
        case 21: _t->on_checkBoxContrast_clicked(); break;
        case 22: _t->on_checkBoxColor_clicked(); break;
        case 23: _t->on_checkBoxVivid_clicked(); break;
        case 24: _t->on_checkBoxVividation_clicked(); break;
        case 25: _t->on_checkBoxGamma_clicked(); break;
        case 26: _t->on_checkBoxWhiteBalance_clicked(); break;
        case 27: _t->on_checkBoxReflection_clicked(); break;
        case 28: _t->on_checkBoxGain_clicked(); break;
        case 29: _t->on_comboBoxPowerFrequency_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_checkBoxZoom_clicked(); break;
        case 31: _t->on_checkBoxFocus_clicked(); break;
        case 32: _t->on_checkBoxExposure_clicked(); break;
        case 33: _t->on_checkBoxIris_clicked(); break;
        case 34: _t->on_checkBoxPan_clicked(); break;
        case 35: _t->on_checkBoxTilt_clicked(); break;
        case 36: _t->on_checkBoxRotation_clicked(); break;
        case 37: _t->on_pushButtonOK_clicked(); break;
        case 38: _t->on_pushButtonCancel_clicked(); break;
        case 39: _t->on_pushButtonSave_clicked(); break;
        case 40: _t->on_pushButtonLoad_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SettingCameraDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SettingCameraDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SettingCameraDialog,
      qt_meta_data_SettingCameraDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SettingCameraDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SettingCameraDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SettingCameraDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SettingCameraDialog))
        return static_cast<void*>(const_cast< SettingCameraDialog*>(this));
    if (!strcmp(_clname, "ServiceForLayers"))
        return static_cast< ServiceForLayers*>(const_cast< SettingCameraDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SettingCameraDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
