/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Black_Jack/window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_BJ__window_t {
    uint offsetsAndSizes[30];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[23];
    char stringdata5[24];
    char stringdata6[25];
    char stringdata7[24];
    char stringdata8[25];
    char stringdata9[24];
    char stringdata10[17];
    char stringdata11[5];
    char stringdata12[18];
    char stringdata13[8];
    char stringdata14[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BJ__window_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BJ__window_t qt_meta_stringdata_BJ__window = {
    {
        QT_MOC_LITERAL(0, 10),  // "BJ::window"
        QT_MOC_LITERAL(11, 11),  // "setGameSkin"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 4),  // "text"
        QT_MOC_LITERAL(29, 22),  // "handleBetButtonClicked"
        QT_MOC_LITERAL(52, 23),  // "handleMenuButtonClicked"
        QT_MOC_LITERAL(76, 24),  // "handleSoundButtonClicked"
        QT_MOC_LITERAL(101, 23),  // "handleFaceButtonClicked"
        QT_MOC_LITERAL(125, 24),  // "handleShirtButtonClicked"
        QT_MOC_LITERAL(150, 23),  // "handleBackButtonClicked"
        QT_MOC_LITERAL(174, 16),  // "handleSkinChoice"
        QT_MOC_LITERAL(191, 4),  // "info"
        QT_MOC_LITERAL(196, 17),  // "handleMatchEnding"
        QT_MOC_LITERAL(214, 7),  // "Winner&"
        QT_MOC_LITERAL(222, 6)   // "winner"
    },
    "BJ::window",
    "setGameSkin",
    "",
    "text",
    "handleBetButtonClicked",
    "handleMenuButtonClicked",
    "handleSoundButtonClicked",
    "handleFaceButtonClicked",
    "handleShirtButtonClicked",
    "handleBackButtonClicked",
    "handleSkinChoice",
    "info",
    "handleMatchEnding",
    "Winner&",
    "winner"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BJ__window[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   71,    2, 0x0a,    3 /* Public */,
       5,    0,   72,    2, 0x0a,    4 /* Public */,
       6,    0,   73,    2, 0x0a,    5 /* Public */,
       7,    0,   74,    2, 0x0a,    6 /* Public */,
       8,    0,   75,    2, 0x0a,    7 /* Public */,
       9,    0,   76,    2, 0x0a,    8 /* Public */,
      10,    1,   77,    2, 0x0a,    9 /* Public */,
      12,    1,   80,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject BJ::window::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_BJ__window.offsetsAndSizes,
    qt_meta_data_BJ__window,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BJ__window_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<window, std::true_type>,
        // method 'setGameSkin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleBetButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleMenuButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSoundButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFaceButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleShirtButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleBackButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSkinChoice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleMatchEnding'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Winner &, std::false_type>
    >,
    nullptr
} };

void BJ::window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<window *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setGameSkin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->handleBetButtonClicked(); break;
        case 2: _t->handleMenuButtonClicked(); break;
        case 3: _t->handleSoundButtonClicked(); break;
        case 4: _t->handleFaceButtonClicked(); break;
        case 5: _t->handleShirtButtonClicked(); break;
        case 6: _t->handleBackButtonClicked(); break;
        case 7: _t->handleSkinChoice((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->handleMatchEnding((*reinterpret_cast< std::add_pointer_t<Winner&>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (window::*)(const QString & );
            if (_t _q_method = &window::setGameSkin; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *BJ::window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BJ::window::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BJ__window.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int BJ::window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void BJ::window::setGameSkin(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
