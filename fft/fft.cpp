#include "fft.h"
#include <QBuffer>

namespace AudioCollection {

    Fft::Fft(QObject *parent)
        :QObject(parent)
    {
    }

    QByteArray Fft::operator()(QByteArray Sample)
    {
        QByteArray Ret;
        QBuffer Buffer(&Sample);
        Buffer.open(QBuffer::ReadOnly);
        if(Buffer.isOpen()) {
            while(!Buffer.atEnd()) {
                short Data;
                Buffer.read(reinterpret_cast<char *>(&Data),sizeof(Data));
            }
        }
        return Ret;
    }

}
