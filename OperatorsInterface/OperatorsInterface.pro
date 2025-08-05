TEMPLATE    =   lib
CONFIG      +=  c++11
CONFIG      +=  qt
TARGET      =   OperatorsInterface
QT          +=  core widgets gui
DEFINES     +=  OPERATORS_INTERFACE_DEFINE

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./OperatorsInterface.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../FITK_Kernal  \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/OperatorsInterface/release/moc
    Release:RCC_DIR         = ../generate/OperatorsInterface/release/rcc
    Release:UI_DIR          = ../generate/OperatorsInterface/release/qui
    Release:OBJECTS_DIR     = ../generate/OperatorsInterface/release/obj
    Release:LIBS +=  \
        -L../output/bin  \
        -lFITKCore \

    Debug:CONFIG            +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/OperatorsInterface/debug/moc
    Debug:RCC_DIR         = ../generate/OperatorsInterface/debug/rcc
    Debug:UI_DIR          = ../generate/OperatorsInterface/debug/qui
    Debug:OBJECTS_DIR     = ../generate/OperatorsInterface/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d \
        -lFITKCore \

    message("Windows Operators Interface generated")
}

unix{

    INCLUDEPATH    +=   ./  \
                        ../ \
                        ../FITK_Kernal \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/OperatorsInterface/release/moc
    UI_DIR          = ../generate/OperatorsInterface/release/qui
    RCC_DIR         = ../generate/OperatorsInterface/release/rcc
    OBJECTS_DIR     = ../generate/OperatorsInterface/release/obj
    LIBS += \
        -L../output/bin \
        -lFITKCore \
        
    message("Linux Operators Interface generated")
}
