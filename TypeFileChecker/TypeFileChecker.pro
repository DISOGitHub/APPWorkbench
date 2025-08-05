TEMPLATE    =   lib
CONFIG      +=  c++11
CONFIG      +=  qt
TARGET      =   TypeFileChecker
QT          +=  core widgets gui
DEFINES     +=  TYPE_FILE_CHECKER_DEFINE

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./TypeFileChecker.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../FITK_Kernal  \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/TypeFileChecker/release/moc
    Release:RCC_DIR         = ../generate/TypeFileChecker/release/rcc
    Release:UI_DIR          = ../generate/TypeFileChecker/release/qui
    Release:OBJECTS_DIR     = ../generate/TypeFileChecker/release/obj
    Release:LIBS +=  \
        -L../output/bin  \
        -lFITKCore \

    Debug:CONFIG            +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/TypeFileChecker/debug/moc
    Debug:RCC_DIR         = ../generate/TypeFileChecker/debug/rcc
    Debug:UI_DIR          = ../generate/TypeFileChecker/debug/qui
    Debug:OBJECTS_DIR     = ../generate/TypeFileChecker/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d \
        -lFITKCore \

    message("Windows Type File Checker generated")
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
        
    message("Linux Type File Checker generated")
}
