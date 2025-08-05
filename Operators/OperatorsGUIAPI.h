#pragma once

#include <QtCore/QtGlobal>

#ifdef OPERATOR_GUI_DEFINE
#define OPERATOR_GUI_API Q_DECL_EXPORT
#else
#define OPERATOR_GUI_API Q_DECL_IMPORT
#endif