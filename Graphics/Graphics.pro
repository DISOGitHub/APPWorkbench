TEMPLATE    =   lib
CONFIG      +=  c++11 
CONFIG      +=  qt
TARGET      =   Graphics
QT          +=  core gui widgets svg
DEFINES     +=  GRAPHICS_DEFINE

include(./Graphics.pri)

win32{

  INCLUDEPATH   +=  ./ \
                    ../ \
                    
  Release:DESTDIR         = ../output/bin 
  Release:MOC_DIR         = ../generate/Graphics/release/moc
  Release:RCC_DIR         = ../generate/Graphics/release/rcc
  Release:UI_DIR          = ../generate/Graphics/release/qui
  Release:OBJECTS_DIR     = ../generate/Graphics/release/obj
  Release:LIBS += -L../output/bin \
                        -lFITKAppFramework \
                        -lFITKCore \
                        -lDataCenter \
                        -lOperatorsInterface \
                        
  Debug:CONFIG	        +=  console
  Debug:DESTDIR         = ../output/bin_d
  Debug:MOC_DIR         = ../generate/Graphics/debug/moc 
  Debug:RCC_DIR         = ../generate/Graphics/debug/rcc 
  Debug:UI_DIR          = ../generate/Graphics/debug/qui 
  Debug:OBJECTS_DIR     = ../generate/Graphics/debug/obj 
  Debug:LIBS += -L../output/bin_d \
                        -lFITKAppFramework \
                        -lFITKCore \
                        -lDataCenter \
                        -lOperatorsInterface \

  message("Windows  Graphics Module build!")
}


unix{

    INCLUDEPATH    +=   ./  \
                        ../ \

    CONFIG          += console
    CONFIG          += plugin
    DESTDIR         = ../output/bin
    MOC_DIR         = ../generate/Graphics/release/moc
    UI_DIR          = ../generate/Graphics/release/qui
    RCC_DIR         = ../generate/Graphics/release/rcc
    OBJECTS_DIR     = ../generate/Graphics/release/obj
    LIBS += \
            -L../output/bin \
                    -lFITKAppFramework \
                    -lFITKCore \
                    -lDataCenter \
                    -lOperatorsInterface \

    message("Linux Graphics generated")
}
