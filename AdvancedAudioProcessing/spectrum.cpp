#include "spectrum.hpp"
#include <QString>

namespace AudioCollection {
	namespace Chart
	{
		Spectrum::Spectrum(QQuickItem *parent)
			: QQuickPaintedItem(parent),
			  MinHz(0),
			  MinDB(0),
			  MaxDB(0),
			  MaxHz(0)
		{
			setAcceptHoverEvents(true);
			setAcceptedMouseButtons(Qt::AllButtons);
			setFlag(ItemAcceptsInputMethod, true);
			connect(&Sample,SIGNAL(Sample(QByteArray)),this,SLOT(SampleSlot(QByteArray)));
			connect(&TimeUpdate,SIGNAL(timeout()),this,SLOT(UpdateSpectrum()));
		}

		Spectrum::DeviceType Spectrum::GetDeviceType()
		{
			return Type;
		}

		void Spectrum::SetDeviceType(DeviceType DeviceType)
		{
			this->Type = DeviceType;
		}

		bool Spectrum::Start()
		{
			if(Type == DeviceType::Device)
			{
				bool Ret = Sample.StartAudioSampleFromDevice();
				if(Ret)
				{
					TimeUpdate.start();
				}
				return Ret;
			}
			else
			{
				return false;
			}
		}

		void Spectrum::Stop()
		{
			Sample.Stop();
			TimeUpdate.stop();
		}

		QColor Spectrum::GetBackgroundColor()
		{
			return this->BackgroundColor;
		}

		void Spectrum::SetBackgroundColor(QColor BackgroundColor)
		{
			this->BackgroundColor = BackgroundColor;
		}

		QColor Spectrum::GetDynamicAxisColor()
		{
			return DynamicAxisColor;
		}

		void Spectrum::SetDynamicAxisColor(QColor Color)
		{
			this->DynamicAxisColor = Color;
		}

		QColor Spectrum::GetLineColor()
		{
			return LineColor;
		}

		void Spectrum::SetLineColor(QColor Color)
		{
			LineColor = Color;
		}

		int Spectrum::GetMinHz()
		{
			return MinHz;
		}

		void Spectrum::SetMinHz(int Min)
		{
			MinHz = Min;
		}

		int Spectrum::GetMaxHz()
		{
			return MaxHz;
		}

		void Spectrum::SetMaxHz(int Max)
		{
			MaxHz = Max;
		}

		int Spectrum::GetMinDB()
		{
			return MinDB;
		}

		void Spectrum::SetMinDB(int Min)
		{
			MinDB = Min;
		}

		int Spectrum::GetMaxDB()
		{
			return MaxDB;
		}

		void Spectrum::SetMaxDB(int Max)
		{
			this->MaxDB = Max;
		}

		int Spectrum::GetUpdateInterval()
		{
			return TimeUpdate.interval();
		}

		void Spectrum::SetUpdateInterval(int Interval)
		{
			TimeUpdate.setInterval(Interval);
		}

		void Spectrum::paint(QPainter *painter)
		{
			Q_ASSERT(painter);
			QPen LineColorPen(GetLineColor());
			painter->setPen(LineColorPen);
			QRectF Rect(60,20,this->width()-70,this->height() - 40);
			painter->fillRect(Rect,GetBackgroundColor());
			qreal XLineUnit = 100;
			qreal YLineUnit = 50;


			if(XLineUnit > 0 && YLineUnit > 0)
			{
				for(qreal XPos = Rect.left();XPos<=Rect.right();XPos+=XLineUnit)
				{
					QLineF XLine;
					XLine.setLine(XPos,Rect.top(),XPos,Rect.bottom());
					painter->drawLine(XLine);
				}
				for(qreal YPos = Rect.top();YPos<=Rect.bottom();YPos+=YLineUnit)
				{

					QLineF YLine;
					YLine.setLine(Rect.left(),YPos,Rect.right(),YPos);
					painter->drawLine(YLine);
				}
				painter->drawRect(Rect);
				//绘制X坐标轴
				QRectF RectText;
				for(qreal XPos = Rect.left();XPos<=Rect.right();XPos+=XLineUnit)
				{
					RectText.setRect(XPos - XLineUnit/2,Rect.bottom() + 5,XLineUnit,10);
					qreal XHz = MinHz + (((MaxHz - MinHz)/Rect.width())*(XPos - Rect.left()));
					painter->drawText(RectText,Qt::AlignCenter,QrealToString(XHz,"hz"));
				}
				//绘制Y坐标轴
				for(qreal YPos = Rect.top();YPos<=Rect.bottom();YPos+=YLineUnit)
				{
					RectText.setRect(0,YPos - 5,Rect.left(),10);
					qreal YDB = MaxDB - (((MaxDB - MinDB)/Rect.height())*(YPos - Rect.top()));
					painter->drawText(RectText,Qt::AlignRight,QrealToString(YDB,"db"));
				}
				//绘制鼠标区域
				//确定X轴区域
				qreal MouseX = MinHz + (((MaxHz - MinHz)/Rect.width())*(MousePoint.x() - Rect.left()));
				//确定Y轴区域
				qreal MouseY = MaxDB - (((MaxDB - MinDB)/Rect.height())*(MousePoint.y() - Rect.top()));
				//绘制动态轴线，确定鼠标位置映射在图表的坐标
				if((MousePoint.x() >= Rect.left()) &&
				   (MousePoint.y() >= Rect.top()) &&
				   (MousePoint.x() <= Rect.right()) &&
				   (MousePoint.y() <= Rect.bottom()))
				{
					QPen DynamicAxisPen(DynamicAxisColor);
					painter->setPen(DynamicAxisPen);
					QPointF BeginXDynamic(MousePoint.x(),Rect.bottom());
					QPointF BeginYDynamic(Rect.left(),MousePoint.y());
					QPointF EndXDynamic(MousePoint.x(),Rect.top());
					QPointF EndYDynamic(Rect.right(),MousePoint.y());
					QLineF XDynamic(BeginXDynamic,EndXDynamic);
					QLineF YDynamic(BeginYDynamic,EndYDynamic);
					painter->drawLine(XDynamic);
					painter->drawLine(YDynamic);
					QPoint Point(MousePoint.x() + 10,
								 MousePoint.y() -10);
					QString DrawPointText("(%1,%2)");
					DrawPointText = DrawPointText.arg(QrealToString(MouseX,"hz"))
												 .arg(QrealToString(MouseY,"db"));
					painter->drawText(Point,DrawPointText);
					painter->setPen(LineColorPen);
				}
			}
		}

		QString Spectrum::QrealToString(qreal Num, QString Tag)
		{
			QString String;
			if(Tag == "hz")
			{
				if(Num < 1000)
				{
					QString NumStr = QString::number(Num,'F',2);
					String = QString("%1Hz").arg(NumStr.toDouble(Q_NULLPTR));
				}
				else
				{
					QString NumStr = QString::number(Num/1000,'F',2);
					String = QString("%1kHz").arg(NumStr.toDouble(Q_NULLPTR));
				}
			}
			else
			{
				if(Num < 1000)
				{
					QString NumStr = QString::number(Num,'F',2);
					String = QString("%1db").arg(NumStr.toDouble(Q_NULLPTR));
				}
				else
				{
					QString NumStr = QString::number(Num,'F',2);
					String = QString("%1kdb").arg(NumStr.toDouble(Q_NULLPTR));
				}
			}

			return String;
		}

		void Spectrum::hoverMoveEvent(QHoverEvent *event)
		{
			MousePoint = event->pos();
			QRect Rect(0,0,this->width(),this->height());
			update(Rect);
		}

		void Spectrum::SampleSlot(QByteArray Buffer)
		{
			SamplesBuffer = Buffer;
		}

		void Spectrum::UpdateSpectrum()
		{
			QRect GlobalRect(0,0,this->width(),this->height());
			update(GlobalRect);
			return;
		}
	}
}
