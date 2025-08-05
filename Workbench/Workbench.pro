TEMPLATE    =  app
CONFIG     +=  c++11
CONFIG     +=  qt
TARGET      =  Workbench
QT         +=  core widgets gui 

unix:!mac{ QMAKE_LFLAGS += -Wl,-rpath,\'\$$ORIGIN/\' }

include(./Workbench.pri)

win32{

    INCLUDEPATH    +=  ./   \
                       ../  \
                       ../../ \

    Release:DESTDIR         = ../output/bin
    Release:MOC_DIR         = ../generate/Workbench/release/moc
    Release:RCC_DIR         = ../generate/Workbench/release/rcc
    Release:UI_DIR          = ../generate/Workbench/release/qui
    Release:OBJECTS_DIR     = ../generate/Workbench/release/obj
    Release:LIBS +=  \
        -L../output/bin  \
        -lFITKAppFramework \
        -lFITKCore \
        -lGUIFrame \
        -lDataCenter \
        -lOperators \

    Debug:CONFIG          +=  console
    Debug:DESTDIR         = ../output/bin_d
    Debug:MOC_DIR         = ../generate/Workbench/debug/moc
    Debug:RCC_DIR         = ../generate/Workbench/debug/rcc
    Debug:UI_DIR          = ../generate/Workbench/debug/qui
    Debug:OBJECTS_DIR     = ../generate/Workbench/debug/obj
    Debug:LIBS +=  \
        -L../output/bin_d  \
        -lFITKAppFramework \
        -lFITKCore \
        -lGUIFrame \
        -lDataCenter \
        -lOperators \

    message("Windows Workbench generated")
}

unix{

    INCLUDEPATH    +=   ./  \
                        ../ \
                        ../../ \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/Workbench/release/moc
    UI_DIR          = ../generate/Workbench/release/qui
    RCC_DIR         = ../generate/Workbench/release/rcc
    OBJECTS_DIR     = ../generate/Workbench/release/obj
    LIBS += \
        -L../output/bin \
        -lFITKAppFramework \
        -lFITKCore \
        -lGUIFrame \
        -lDataCenter \
        -lOperators \

    message("Linux Workbench generated")
}

