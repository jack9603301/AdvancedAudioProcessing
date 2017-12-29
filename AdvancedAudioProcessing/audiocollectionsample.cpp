#include "audiocollectionsample.hpp"
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInput>

namespace AudioCollection {

	AudioCollectionSample::AudioCollectionSample(QObject *parent)
		: QObject(parent),
		  AudioDevice(Q_NULLPTR),
		  Format(Q_NULLPTR),
		  InputDevice(Q_NULLPTR)
	{
	}

	AudioCollectionSample::~AudioCollectionSample()
	{
		Stop();
	}

	bool AudioCollectionSample::StartAudioSampleFromDevice()
	{
		if(Format && AudioDevice)
		{

			if(InputDevice)
			{
				InputDevice->stop();
				delete InputDevice;
				InputDevice = Q_NULLPTR;
			}
			AudioDevice = Q_NULLPTR;
			delete Format;
			Format = Q_NULLPTR;
		}

		Q_ASSERT(Format == Q_NULLPTR && AudioDevice == Q_NULLPTR && InputDevice == Q_NULLPTR);

		Format = new QAudioFormat;
		Format->setByteOrder(QAudioFormat::LittleEndian);
		Format->setChannelCount(2);
		Format->setCodec("Audio/pcm");
		Format->setSampleRate(1000);
		Format->setSampleSize(200);
		Format->setSampleType(QAudioFormat::UnSignedInt);
		QAudioDeviceInfo Info = QAudioDeviceInfo::defaultInputDevice();
		if(!Info.isFormatSupported(*Format))
		{
			(*Format) = Info.nearestFormat(*Format);
		}
		InputDevice = new QAudioInput(*Format,this);
		AudioDevice = InputDevice->start();
		if(AudioDevice)
		{
			connect(AudioDevice,SIGNAL(readyRead()),this,SLOT(Ready()));
			return true;
		}
		else
		{
			return false;
		}
	}

	void AudioCollectionSample::Stop()
	{
		if(Format && AudioDevice)
		{
			disconnect(AudioDevice,SIGNAL(readyRead()),this,SLOT(Ready()));
			if(InputDevice)
			{
				InputDevice->stop();
				delete InputDevice;
				InputDevice = Q_NULLPTR;
			}
			AudioDevice = Q_NULLPTR;
			delete Format;
			Format = Q_NULLPTR;
		}
	}

	void AudioCollectionSample::Ready()
	{
		Q_ASSERT(AudioDevice);
		emit Sample(AudioDevice->readAll());
	}
}
