#pragma once
#include <QtCore/QtGlobal>

#ifdef GUI_WIDGET_DEFINE
#define GUI_WIDGET_API Q_DECL_EXPORT
#else
#define GUI_WIDGET_API Q_DECL_IMPORT
#endif
