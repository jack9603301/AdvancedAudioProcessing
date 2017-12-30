contains(TEMPLATE,app) {
    DESTDIR = $$PWD/Bin
    QMAKE_RPATHDIR = $$PWD/Bin
} else: contains(TEMPLATE,lib) {
    contains(CONFIG,static) {
        DESTDIR = $$PWD/Lib
    } else: {
        win32 {
            DESTDIR = $$PWD/lib
            DLLDESTDIR = $$PWD/Bin
        } else {
            DESTDIR = $$PWD/Bin
        }
    }
}

win32 {
    CONFIG(debug,debug|release) {
        TARGET = $${TARGET}d
    }
}

OBJECTS_DIR = $$OUT_PWD/Gen/Objs
RCC_DIR = $$OUT_PWD/Gen/Rcc
UI_DIR = $$OUT_PWD/Gen/Ui
MOC_DIR = $$OUT_PWD/Gen/Moc

QMAKE_DISTCLEAN += $$OBJECTS_DIR \
    $$RCC_DIR \
    $$UI_DIR \
    $$MOC_DIR
