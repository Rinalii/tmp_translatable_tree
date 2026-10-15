QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD/ui \
    $$PWD/model \
    $$PWD/translation

SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    model/translatableitemmodel.cpp \
    model/treeloader.cpp \
    translation/jsontranslationprovider.cpp \
    translation/qttranslationprovider.cpp

HEADERS += \
    ui/mainwindow.h \
    model/itemroles.h \
    model/translatableitemmodel.h \
    model/treeloader.h \
    translation/itranslationprovider.h \
    translation/jsontranslationprovider.h \
    translation/qttranslationprovider.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
