TEMPLATE    =   lib
CONFIG      +=  c++11
CONFIG      +=  qt
TARGET      =   Operators
QT          +=  core widgets gui
DEFINES     +=  OPERATOR_GUI_DEFINE

unix:!mac{ QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/\'" }

include(./Operators.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../FITK_Kernal  \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/Operators/release/moc
    Release:RCC_DIR         = ../generate/Operators/release/rcc
    Release:UI_DIR          = ../generate/Operators/release/qui
    Release:OBJECTS_DIR     = ../generate/Operators/release/obj
    Release:LIBS +=  \
        -L../output/bin  \
        -lFITKAppFramework \
        -lFITKCore \
        -lOperatorsInterface \
        -lDataCenter \
        -lGUIFrame \
        -lGUIWidget \
        -lGraphics \

    Debug:CONFIG            +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/Operators/debug/moc
    Debug:RCC_DIR         = ../generate/Operators/debug/rcc
    Debug:UI_DIR          = ../generate/Operators/debug/qui
    Debug:OBJECTS_DIR     = ../generate/Operators/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d \
        -lFITKAppFramework \
        -lFITKCore \
        -lOperatorsInterface \
        -lDataCenter \
        -lGUIFrame \
        -lGUIWidget \
        -lGraphics \

    message("Windows Operators generated")
}

unix{

    INCLUDEPATH    +=   ./  \
                        ../ \
                        ../FITK_Kernal \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/Operators/release/moc
    UI_DIR          = ../generate/Operators/release/qui
    RCC_DIR         = ../generate/Operators/release/rcc
    OBJECTS_DIR     = ../generate/Operators/release/obj
    LIBS += \
        -L../output/bin \
        -lFITKAppFramework \
        -lFITKCore \
        -lOperatorsInterface \
        -lDataCenter \
        -lGUIFrame \
        -lGUIWidget \
        -lGraphics \
        
    message("Linux Operators generated")
}
