/****************************************************************************
** Meta object code from reading C++ file 'folderview.h'
**
** Created: Wed Jun 30 17:10:48 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "folderview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'folderview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FolderView[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,
      30,   12,   11,   11, 0x05,
      53,   49,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   49,   11,   11, 0x0a,
      87,   11,   11,   11, 0x0a,
     100,   12,   11,   11, 0x0a,
     131,  116,   11,   11, 0x0a,
     150,   49,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_FolderView[] = {
    "FolderView\0\0f\0isFiltred(bool)\0"
    "setFilter(QString)\0tag\0currentDir(QString)\0"
    "skip(QString)\0updateGrid()\0filter(QString)\0"
    "tag,emitSignal\0open(QString,bool)\0"
    "open(QString)\0"
};

const QMetaObject FolderView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FolderView,
      qt_meta_data_FolderView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FolderView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FolderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FolderView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FolderView))
        return static_cast<void*>(const_cast< FolderView*>(this));
    return QWidget::qt_metacast(_clname);
}

int FolderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: isFiltred((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: currentDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: skip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: updateGrid(); break;
        case 5: filter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: open((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void FolderView::isFiltred(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FolderView::setFilter(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FolderView::currentDir(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
