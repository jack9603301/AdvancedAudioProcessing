#include "documentview.hpp"
#include "spectrum.hpp"
#include <QQmlEngine>
#include <QResizeEvent>
#include <QQmlContext>
#include <QQuickItem>

DocumentView::DocumentView(QWidget *parent)
	:QQuickWidget(parent)
{
	using namespace AudioCollection::Chart;
	qmlRegisterType<Spectrum>("AudioAnalysis.Charts",1,0,"Spectrum");
}

void DocumentView::resizeEvent(QResizeEvent *event)
{
	QQuickWidget::resizeEvent(event);
	Q_ASSERT(event);
	QSize Size = event->size();
	int width = Size.width();
	int height = Size.height();
	QQuickItem *Item = this->rootObject();
	if(Item)
	{
		Item->setProperty("height",height);
		Item->setProperty("width",width);
	}
}
