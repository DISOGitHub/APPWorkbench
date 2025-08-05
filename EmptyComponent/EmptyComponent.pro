TEMPLATE    =  app
CONFIG     +=  c++11
CONFIG     +=  qt
TARGET      =  EmptyComponent
QT         +=  core widgets gui 

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./EmptyComponent.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../../ \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/EmptyComponent/release/moc
    Release:RCC_DIR         = ../generate/EmptyComponent/release/rcc
    Release:UI_DIR          = ../generate/EmptyComponent/release/qui
    Release:OBJECTS_DIR     = ../generate/EmptyComponent/release/obj
    Release:LIBS +=  \
        -L../output/bin  \

    Debug:CONFIG          +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/EmptyComponent/debug/moc
    Debug:RCC_DIR         = ../generate/EmptyComponent/debug/rcc
    Debug:UI_DIR          = ../generate/EmptyComponent/debug/qui
    Debug:OBJECTS_DIR     = ../generate/EmptyComponent/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d  \

    message("Windows EmptyComponent generated")
}

unix{

    INCLUDEPATH    +=   ./  \
                        ../ \
                        ../../ \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ./output/bin
    MOC_DIR         = ./generate/EmptyComponent/release/moc
    UI_DIR          = ./generate/EmptyComponent/release/qui
    RCC_DIR         = ./generate/EmptyComponent/release/rcc
    OBJECTS_DIR     = ./generate/EmptyComponent/release/obj
    LIBS += \
        -L./output/bin \

    message("Linux EmptyComponent generated")
}

