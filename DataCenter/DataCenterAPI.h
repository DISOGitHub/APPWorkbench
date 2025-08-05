#pragma once
#include <QtCore/QtGlobal>

#ifdef DATA_CENTER_DEFINE
#define DATA_CENTER_API Q_DECL_EXPORT
#else
#define DATA_CENTER_API Q_DECL_IMPORT
#endif