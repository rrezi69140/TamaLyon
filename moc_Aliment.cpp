/****************************************************************************
** Meta object code from reading C++ file 'Aliment.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Aliment.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Aliment.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7AlimentE_t {};
} // unnamed namespace

template <> constexpr inline auto Aliment::qt_create_metaobjectdata<qt_meta_tag_ZN7AlimentE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Aliment",
        "faimImpact",
        "soifImpact",
        "humeurImpact",
        "estToxique",
        "categorie",
        "nom",
        "emoji",
        "description"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'faimImpact'
        QtMocHelpers::PropertyData<int>(1, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'soifImpact'
        QtMocHelpers::PropertyData<int>(2, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'humeurImpact'
        QtMocHelpers::PropertyData<int>(3, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'estToxique'
        QtMocHelpers::PropertyData<bool>(4, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'categorie'
        QtMocHelpers::PropertyData<QString>(5, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'nom'
        QtMocHelpers::PropertyData<QString>(6, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'emoji'
        QtMocHelpers::PropertyData<QString>(7, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'description'
        QtMocHelpers::PropertyData<QString>(8, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Aliment, qt_meta_tag_ZN7AlimentE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Aliment::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7AlimentE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7AlimentE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7AlimentE_t>.metaTypes,
    nullptr
} };

void Aliment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Aliment *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->getFaimImpact(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->getSoifImpact(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->getHumeurImpact(); break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->getEstToxique(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->getCategorie(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->getNom(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->getEmoji(); break;
        case 7: *reinterpret_cast<QString*>(_v) = _t->getDescription(); break;
        default: break;
        }
    }
}

const QMetaObject *Aliment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Aliment::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7AlimentE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Aliment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
