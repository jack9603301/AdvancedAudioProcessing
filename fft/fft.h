#ifndef FFT_H
#define FFT_H

#include "fft_global.h"
#include <QByteArray>
namespace AudioCollection {

    class FFTSHARED_EXPORT Fft : public QObject
    {
    public:
        Fft(QObject *parent = Q_NULLPTR);
        QByteArray operator()(QByteArray Sample);
    };

}

#endif // FFT_H
