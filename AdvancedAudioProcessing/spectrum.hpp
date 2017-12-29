#ifndef SPECTRUM_HPP
#define SPECTRUM_HPP

#include <QObject>
#include "audiocollectionsample.hpp"
#include <QQuickPaintedItem>
#include <QPainter>
#include <QColor>
#include <QTimer>

namespace AudioCollection {
	namespace Chart
	{
		class Spectrum : public QQuickPaintedItem
		{
			Q_OBJECT
			Q_ENUMS(DeviceType)
			Q_PROPERTY(DeviceType deviceType READ GetDeviceType WRITE SetDeviceType)
			Q_PROPERTY(QColor backgroundColor READ GetBackgroundColor WRITE	SetBackgroundColor)
			Q_PROPERTY(int minHz READ GetMinHz WRITE SetMinHz)
			Q_PROPERTY(int maxHz READ GetMaxHz WRITE SetMaxHz)
			Q_PROPERTY(int minDB READ GetMinDB WRITE SetMinDB)
			Q_PROPERTY(int maxDB READ GetMaxDB WRITE SetMaxDB)
			Q_PROPERTY(int updateInterval READ GetUpdateInterval WRITE SetUpdateInterval)
			Q_PROPERTY(QColor dynamicAxisColor READ GetDynamicAxisColor WRITE SetDynamicAxisColor)
			Q_PROPERTY(QColor lineColor READ GetLineColor WRITE SetLineColor)
		public:
			enum DeviceType
			{
				File,
				Device
			};
		public:
			explicit Spectrum(QQuickItem *parent = nullptr);
			Q_INVOKABLE bool Start();
			Q_INVOKABLE void Stop();
		protected:
			DeviceType GetDeviceType();
			void SetDeviceType(DeviceType DeviceType);
			QColor GetBackgroundColor();
			void SetBackgroundColor(QColor BackgroundColor);
			QColor GetDynamicAxisColor();
			void SetDynamicAxisColor(QColor Color);
			QColor GetLineColor();
			void SetLineColor(QColor Color);
			int GetMinHz();
			void SetMinHz(int Min);
			int GetMaxHz();
			void SetMaxHz(int Max);
			int GetMinDB();
			void SetMinDB(int Min);
			int GetMaxDB();
			void SetMaxDB(int Max);
			int GetUpdateInterval(void);
			void SetUpdateInterval(int Interval);
		protected:
			virtual void paint(QPainter *painter);
			virtual QString QrealToString(qreal Num,QString Tag);
			virtual void hoverMoveEvent(QHoverEvent* event);
		private slots:
			void SampleSlot(QByteArray Buffer);
			void UpdateSpectrum();
		private:
			DeviceType Type;
			AudioCollectionSample Sample;
			QColor BackgroundColor;
			QByteArray SamplesBuffer;
			int MinHz;
			int MaxHz;
			int MinDB;
			int MaxDB;
			QTimer TimeUpdate;
			QPoint MousePoint;
			QColor DynamicAxisColor;
			QColor LineColor;
		};
	}
}


#endif // SPECTRUM_HPP
