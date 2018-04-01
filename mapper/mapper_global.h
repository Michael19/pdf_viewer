#ifndef MAPPER_GLOBAL_H
#define MAPPER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAPPER_LIBRARY)
#  define MAPPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAPPERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MAPPER_GLOBAL_H
