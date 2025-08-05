TEMPLATE    =   lib
CONFIG      +=  c++11
CONFIG      +=  qt
TARGET      =   UpdateOnline
QT          +=  core widgets gui
DEFINES     +=  UPDATE_ONLINE_DEFINE

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./UpdateOnline.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/UpdateOnline/release/moc
    Release:RCC_DIR         = ../generate/UpdateOnline/release/rcc
    Release:UI_DIR          = ../generate/UpdateOnline/release/qui
    Release:OBJECTS_DIR     = ../generate/UpdateOnline/release/obj
    Release:LIBS +=  \
        -L../output/bin             \
                        -lFITKCore  \

    Debug:CONFIG            +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/UpdateOnline/debug/moc
    Debug:RCC_DIR         = ../generate/UpdateOnline/debug/rcc
    Debug:UI_DIR          = ../generate/UpdateOnline/debug/qui
    Debug:OBJECTS_DIR     = ../generate/UpdateOnline/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d           \
                        -lFITKCore  \

    message("Windows UpdateOnline generated")
}

unix{
    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/UpdateOnline/release/moc
    UI_DIR          = ../generate/UpdateOnline/release/qui
    RCC_DIR         = ../generate/UpdateOnline/release/rcc
    OBJECTS_DIR     = ../generate/UpdateOnline/release/obj
    INCLUDEPATH    += ./  \
                      ../ \

    LIBS += \

    message("Linux UpdateOnline generated")
}

