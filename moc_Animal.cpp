/****************************************************************************
** Meta object code from reading C++ file 'Animal.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Animal.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Animal.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6AnimalE_t {};
} // unnamed namespace

template <> constexpr inline auto Animal::qt_create_metaobjectdata<qt_meta_tag_ZN6AnimalE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Animal",
        "faimChanged",
        "",
        "soifChanged",
        "humeurChanged",
        "empoisonnementChanged",
        "estMortChanged",
        "etatChanged",
        "reactionAliment",
        "message",
        "animalMort",
        "decroissance",
        "verifierEtat",
        "donnerAliment",
        "Aliment*",
        "aliment",
        "resetAnimal",
        "faim",
        "soif",
        "humeur",
        "empoisonnement",
        "estMort",
        "etat",
        "nom",
        "type"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'faimChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'soifChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'humeurChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'empoisonnementChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'estMortChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'etatChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reactionAliment'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Signal 'animalMort'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'decroissance'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessProtected, QMetaType::Void),
        // Slot 'verifierEtat'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessProtected, QMetaType::Void),
        // Method 'donnerAliment'
        QtMocHelpers::MethodData<void(Aliment *)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Method 'resetAnimal'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'faim'
        QtMocHelpers::PropertyData<int>(17, QMetaType::Int, QMC::DefaultPropertyFlags, 0),
        // property 'soif'
        QtMocHelpers::PropertyData<int>(18, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'humeur'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
        // property 'empoisonnement'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 3),
        // property 'estMort'
        QtMocHelpers::PropertyData<bool>(21, QMetaType::Bool, QMC::DefaultPropertyFlags, 4),
        // property 'etat'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'nom'
        QtMocHelpers::PropertyData<QString>(23, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'type'
        QtMocHelpers::PropertyData<QString>(24, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Animal, qt_meta_tag_ZN6AnimalE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Animal::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6AnimalE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6AnimalE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6AnimalE_t>.metaTypes,
    nullptr
} };

void Animal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Animal *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->faimChanged(); break;
        case 1: _t->soifChanged(); break;
        case 2: _t->humeurChanged(); break;
        case 3: _t->empoisonnementChanged(); break;
        case 4: _t->estMortChanged(); break;
        case 5: _t->etatChanged(); break;
        case 6: _t->reactionAliment((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->animalMort(); break;
        case 8: _t->decroissance(); break;
        case 9: _t->verifierEtat(); break;
        case 10: _t->donnerAliment((*reinterpret_cast< std::add_pointer_t<Aliment*>>(_a[1]))); break;
        case 11: _t->resetAnimal(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Aliment* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::faimChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::soifChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::humeurChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::empoisonnementChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::estMortChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::etatChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)(const QString & )>(_a, &Animal::reactionAliment, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Animal::*)()>(_a, &Animal::animalMort, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->getFaim(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->getSoif(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->getHumeur(); break;
        case 3: *reinterpret_cast<int*>(_v) = _t->getEmpoisonnement(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->getEstMort(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->getEtatString(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->getNom(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->getType(); break;
        default: break;
        }
    }
}

const QMetaObject *Animal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Animal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6AnimalE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Animal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Animal::faimChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Animal::soifChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Animal::humeurChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Animal::empoisonnementChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Animal::estMortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Animal::etatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Animal::reactionAliment(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void Animal::animalMort()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
