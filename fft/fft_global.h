#ifndef FFT_GLOBAL_H
#define FFT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FFT_LIBRARY)
#  define FFTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FFTSHARED_EXPORT Q_DECL_IMPORT
#endif
#include <QObject>

#endif // FFT_GLOBAL_H
