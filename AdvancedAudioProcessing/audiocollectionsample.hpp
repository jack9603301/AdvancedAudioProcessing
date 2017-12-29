#ifndef AUDIOCOLLECTIONSAMPLE_HPP
#define AUDIOCOLLECTIONSAMPLE_HPP

#include <QObject>
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioInput>

namespace AudioCollection {
	class AudioCollectionSample : public QObject
	{
		Q_OBJECT
	public:
		explicit AudioCollectionSample(QObject *parent = nullptr);
		~AudioCollectionSample();
		bool StartAudioSampleFromDevice();
		void Stop();
	signals:
		void Sample(QByteArray Buffer);
	private slots:
		void Ready();
	private:
		QIODevice *AudioDevice;
		QAudioFormat *Format;
		QAudioInput *InputDevice;
	};

}



#endif // AUDIOCOLLECTIONSAMPLE_HPP
