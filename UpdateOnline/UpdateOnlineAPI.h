#pragma once
#include <QtCore/QtGlobal>

#ifdef UPDATE_ONLINE_DEFINE
#define UPDATE_ONLINE_API Q_DECL_EXPORT
#else
#define UPDATE_ONLINE_API Q_DECL_IMPORT
#endif
