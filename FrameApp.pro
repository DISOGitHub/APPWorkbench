TEMPLATE = subdirs

SUBDIRS += \
    $$PWD/FITK_Kernel \
    $$PWD/DataCenter \
    $$PWD/Workbench \
    $$PWD/Graphics \
    $$PWD/GUIFrame \
    $$PWD/GUIWidget \
    $$PWD/Operators \
    $$PWD/OperatorsInterface \
    $$PWD/TypeFileChecker \
    $$PWD/UpdateOnline \
  
#CONFIG += ordered

FITK_Kernel/FITKCore.depends =
FITK_Kernel/FITKAppFramework.depends = FITK_Kernel/FITKCore
DataCenter.depends = FITK_Kernel/FITKCore
UpdateOnline.depends = FITK_Kernel/FITKCore
OperatorsInterface.depends = FITK_Kernel/FITKCore
Graphics.depends = FITK_Kernel/FITKCore FITK_Kernel/FITKAppFramework DataCenter
Operators.depends = FITK_Kernel/FITKCore FITK_Kernel/FITKAppFramework OperatorsInterface DataCenter GUIFrame Graphics
GUIFrame.depends = FITK_Kernel/FITKCore FITK_Kernel/FITKAppFramework OperatorsInterface DataCenter Graphics 
FrameAPP.depends = FITK_Kernel/FITKCore FITK_Kernel/FITKAppFramework GUIFrame DataCenter Operators
