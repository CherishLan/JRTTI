/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Wed Dec 14 15:13:19 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      81,   11,   11,   11, 0x08,
     125,  120,   11,   11, 0x08,
     168,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0on_pushButton_add_clicked()\0"
    "on_lineEdit_beginEA_textChanged(QString)\0"
    "on_lineEdit_endEA_textChanged(QString)\0"
    "arg1\0on_lineEdit_targetDir_textChanged(QString)\0"
    "on_toolButton_showFileDialog_clicked()\0"
    "on_pushButton_generateFiles_clicked()\0"
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWidget *_t = static_cast<MainWidget *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_add_clicked(); break;
        case 1: _t->on_lineEdit_beginEA_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_lineEdit_endEA_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_lineEdit_targetDir_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_toolButton_showFileDialog_clicked(); break;
        case 5: _t->on_pushButton_generateFiles_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
