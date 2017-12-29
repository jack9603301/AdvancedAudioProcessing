#ifndef DOCUMENTVIEW_HPP
#define DOCUMENTVIEW_HPP

#include <QQuickWidget>

class DocumentView : public QQuickWidget
{
	Q_OBJECT
public:
	DocumentView(QWidget *parent = Q_NULLPTR);
protected:
	virtual void resizeEvent(QResizeEvent *event);
};

#endif // DOCUMENTVIEW_HPP
