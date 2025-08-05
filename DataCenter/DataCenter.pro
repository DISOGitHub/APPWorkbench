TEMPLATE    =   lib
CONFIG      +=  c++11
CONFIG      +=  qt
TARGET      =   DataCenter
QT          +=  core widgets
DEFINES     +=  DATA_CENTER_DEFINE

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./DataCenter.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../FITK_Kernal  \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/DataCenter/release/moc
    Release:RCC_DIR         = ../generate/DataCenter/release/rcc
    Release:UI_DIR          = ../generate/DataCenter/release/qui
    Release:OBJECTS_DIR     = ../generate/DataCenter/release/obj
    Release:LIBS +=  \
        -L../output/bin  \
        -lFITKCore \
        -lOperatorsInterface \


    Debug:CONFIG            +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/DataCenter/debug/moc
    Debug:RCC_DIR         = ../generate/DataCenter/debug/rcc
    Debug:UI_DIR          = ../generate/DataCenter/debug/qui
    Debug:OBJECTS_DIR     = ../generate/DataCenter/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d \
        -lFITKCore \
        -lOperatorsInterface \

    message("Windows Data Center generated")
}

unix{

    INCLUDEPATH    +=   ./  \
                        ../ \
                        ../FITK_Kernal \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/DataCenter/release/moc
    UI_DIR          = ../generate/DataCenter/release/qui
    RCC_DIR         = ../generate/DataCenter/release/rcc
    OBJECTS_DIR     = ../generate/DataCenter/release/obj
    LIBS += \
        -L../output/bin \
        -lFITKCore \
        -lOperatorsInterface \
        
    message("Linux Data Center generated")
}
