/****************************************************************************
** Meta object code from reading C++ file 'LionManager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LionManager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LionManager.h' doesn't include <QObject>."
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
        "hungerChanged",
        "thirstChanged",
        "affectionChanged",
        "energyChanged",
        "connectionStatusChanged",
        "stateUpdated",
        "state",
        "decayStates",
        "feed",
        "points",
        "giveWater",
        "pet",
        "water",
        "startAsHost",
        "joinAsClient",
        "mood",
        "hunger",
        "thirst",
        "affection",
        "energy",
        "connectionStatus"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'moodChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hungerChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'thirstChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'affectionChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'energyChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectionStatusChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'stateUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'decayStates'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'feed'
        QtMocHelpers::MethodData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'giveWater'
        QtMocHelpers::MethodData<void(int)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'pet'
        QtMocHelpers::MethodData<void(int)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'water'
        QtMocHelpers::MethodData<void(int)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'startAsHost'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'joinAsClient'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'mood'
        QtMocHelpers::PropertyData<QString>(18, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 0),
        // property 'hunger'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'thirst'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'affection'
        QtMocHelpers::PropertyData<int>(21, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'energy'
        QtMocHelpers::PropertyData<int>(22, QMetaType::Int, QMC::DefaultPropertyFlags, 4),
        // property 'connectionStatus'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
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
        case 1: _t->hungerChanged(); break;
        case 2: _t->thirstChanged(); break;
        case 3: _t->affectionChanged(); break;
        case 4: _t->energyChanged(); break;
        case 5: _t->connectionStatusChanged(); break;
        case 6: _t->stateUpdated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->decayStates(); break;
        case 8: _t->feed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->giveWater((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->pet((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->water((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->startAsHost(); break;
        case 13: _t->joinAsClient(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::moodChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::hungerChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::thirstChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::affectionChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::energyChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)()>(_a, &LionManager::connectionStatusChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (LionManager::*)(const QString & )>(_a, &LionManager::stateUpdated, 6))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->mood(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->getHunger(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->getThirst(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->getAffection(); break;
        case 4: *reinterpret_cast<int*>(_v) = _t->getEnergy(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->connectionStatus(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMood(*reinterpret_cast<QString*>(_v)); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void LionManager::moodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LionManager::hungerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LionManager::thirstChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LionManager::affectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LionManager::energyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LionManager::connectionStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LionManager::stateUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}
QT_WARNING_POP
