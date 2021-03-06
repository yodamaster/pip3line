/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#include "messagepanelwidget.h"
#include "ui_messagepanelwidget.h"

MessagePanelWidget::MessagePanelWidget(QWidget *parent) :
    QWidget(parent)
{
    ui = new(std::nothrow) Ui::MessagePanelWidget();
    if (ui == NULL) {
        qFatal("Cannot allocate memory for Ui::MessagePanelWidget X{");
    }
    ui->setupUi(this);
    this->setVisible(false);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(closeWidget()));
}

MessagePanelWidget::~MessagePanelWidget()
{
    delete ui;
}

void MessagePanelWidget::logWarning(const QString message, const QString )
{
    addMessage(message,Qt::blue);
}

void MessagePanelWidget::logError(const QString message, const QString )
{
    addMessage(message,Qt::red);
}

void MessagePanelWidget::logStatus(const QString message, const QString )
{
    addMessage(message,Qt::black);
}

void MessagePanelWidget::log(QString mess, QString , Pip3lineConst::LOGLEVEL level)
{
    QColor color = Qt::black;
    if (level == Pip3lineConst::LERROR)
        color = Qt::red;
    else if (level == Pip3lineConst::LWARNING)
        color = Qt::blue;

    addMessage(mess,color);
}

void MessagePanelWidget::closeWidget()
{
    ui->textEdit->clear();
    this->setVisible(false);
}

void MessagePanelWidget::clear()
{
    ui->textEdit->clear();
}

void MessagePanelWidget::addMessage(const QString &message, QColor color)
{
    ui->textEdit->setTextColor(color);
    ui->textEdit->append(message);
    this->setVisible(true);
}
