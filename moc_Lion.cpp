/****************************************************************************
** Meta object code from reading C++ file 'Lion.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Lion.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Lion.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11LionManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto LionManager::qt_create_metaobjectdata<qt_meta_tag_ZN11LionManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LionManager",
        "moodChanged",
        "",
        "connectionStatusChanged",
        "sendState",
        "state",
        "processCommand",
        "cmd",
        "updateFromState",
        "updateMood",
        "sendCommand",
        "startAsHost",
        "joinAsClient",
        "feed",
        "amount",
        "water",
        "pet",
        "mood",
        "connectionStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'moodChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectionStatusChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sendState'
        QtMocHelpers::SignalData<void(const QJsonObject &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonObject, 5 },
        }}),
        // Slot 'processCommand'
        QtMocHelpers::SlotData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'updateFromState'
        QtMocHelpers::SlotData<void(const QJsonObject &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QJsonObject, 5 },
        }}),
        // Slot 'updateMood'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'sendCommand'
        QtMocHelpers::MethodData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'startAsHost'
        QtMocHelpers::MethodData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'joinAsClient'
        QtMocHelpers::MethodData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'feed'
        QtMocHelpers::MethodData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Method 'water'
        QtMocHelpers::MethodData<void(int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
        // Method 'pet'
        QtMocHelpers::MethodData<void(int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 14 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'mood'
        QtMocHelpers::PropertyData<QString>(17, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
        // property 'connectionStatus'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LionManager, qt_meta_tag_ZN11LionManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject LionManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LionManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LionManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11LionManagerE_t>.metaTypes,
    nullptr
} };

void LionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LionManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->moodChanged(); break;
        case 1: _t->connectionStatusChanged(); break;
        case 2: _t->sendState((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 3: _t->processCommand((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->updateFromState((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 5: _t->updateMood(); break;
        case 6: _t->sendCommand((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->startAsHost(); break;
        case 8: _t->joinAsClient(); break;
        case 9: _t->feed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->water((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->pet((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::moodChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::connectionStatusChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)(const QJsonObject & )>(_a, &LionManager::sendState, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->mood(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->connectionStatus(); break;
        default: break;
        }
    }
}

const QMetaObject *LionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11LionManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LionManager::moodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LionManager::connectionStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LionManager::sendState(const QJsonObject & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
