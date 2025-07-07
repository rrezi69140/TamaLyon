/****************************************************************************
** Meta object code from reading C++ file 'AlimentManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AlimentManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AlimentManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14AlimentManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto AlimentManager::qt_create_metaobjectdata<qt_meta_tag_ZN14AlimentManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AlimentManager",
        "alimentsChanged",
        "",
        "getAlimentByIndex",
        "Aliment*",
        "index",
        "getAlimentByName",
        "nom",
        "getAlimentCount",
        "getAlimentInfo",
        "alimentsDisponibles",
        "QQmlListProperty<Aliment>"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'alimentsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'getAlimentByIndex'
        QtMocHelpers::MethodData<Aliment *(int) const>(3, 2, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::Int, 5 },
        }}),
        // Method 'getAlimentByName'
        QtMocHelpers::MethodData<Aliment *(const QString &) const>(6, 2, QMC::AccessPublic, 0x80000000 | 4, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'getAlimentCount'
        QtMocHelpers::MethodData<int() const>(8, 2, QMC::AccessPublic, QMetaType::Int),
        // Method 'getAlimentInfo'
        QtMocHelpers::MethodData<QString(int) const>(9, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::Int, 5 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'alimentsDisponibles'
        QtMocHelpers::PropertyData<QQmlListProperty<Aliment>>(10, 0x80000000 | 11, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AlimentManager, qt_meta_tag_ZN14AlimentManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AlimentManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14AlimentManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14AlimentManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14AlimentManagerE_t>.metaTypes,
    nullptr
} };

void AlimentManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AlimentManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->alimentsChanged(); break;
        case 1: { Aliment* _r = _t->getAlimentByIndex((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Aliment**>(_a[0]) = std::move(_r); }  break;
        case 2: { Aliment* _r = _t->getAlimentByName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Aliment**>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->getAlimentCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getAlimentInfo((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AlimentManager::*)()>(_a, &AlimentManager::alimentsChanged, 0))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QQmlListProperty<Aliment>*>(_v) = _t->alimentsDisponibles(); break;
        default: break;
        }
    }
}

const QMetaObject *AlimentManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlimentManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14AlimentManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AlimentManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void AlimentManager::alimentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
