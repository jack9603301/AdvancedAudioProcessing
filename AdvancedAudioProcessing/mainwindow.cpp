#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "documentview.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	Q_ASSERT(ui);
	ui->setupUi(this);
	DocumentView *Welcome = new DocumentView(this);
	Q_ASSERT(Welcome);
	Welcome->setSource(QUrl("qrc:/qml/Welcome.qml"));
	if(!(Welcome->status() == QQuickWidget::Error))
	{
		Q_ASSERT(ui->Document);
		ui->Document->addTab(Welcome,tr("Welcome"));
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}
