/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#include "charencoding.h"
#include "confgui/charencodingwidget.h"
#include <QTextStream>
#include <QTextCodec>
#include <QTextEncoder>
#include <QTextDecoder>
#include <QtAlgorithms>

const QString CharEncoding::id = "Char encoding";

CharEncoding::CharEncoding()
{
    QList<QByteArray> codecs =  QTextCodec::availableCodecs();
    qSort(codecs);
    codecName = codecs.at(0);
}

CharEncoding::~CharEncoding()
{
}

QString CharEncoding::name() const {
    return id;
}

QString CharEncoding::description() const {
    return tr("Convert the input into different character encoding standards.");
}

bool CharEncoding::isTwoWays() {
    return true;
}

QHash<QString, QString> CharEncoding::getConfiguration()
{
    QHash<QString, QString> properties = TransformAbstract::getConfiguration();
    properties.insert(XMLCODECNAME,QString(codecName));

    return properties;
}

bool CharEncoding::setConfiguration(QHash<QString, QString> propertiesList)
{
    bool res = TransformAbstract::setConfiguration(propertiesList);

    res = setCodecName(propertiesList.value(XMLCODECNAME).toUtf8()) && res;

    return res;
}

QWidget *CharEncoding::requestGui(QWidget *parent)
{
    QWidget * widget = new(std::nothrow) CharEncodingWidget(this, parent);
    if (widget == NULL) {
        qFatal("Cannot allocate memory for CharEncodingWidget X{");
    }
    return widget;
}

QString CharEncoding::help() const
{
    QString help;
    help.append("<p>Character encoding converter</p><p>This transformation is used to convert the input to a specific Character encoding (UTF-8, UTF-16 ...).</p><p>Note: <ul><li>Encoding: UTF-8 => [Choosen encoding]</li><li>Decoding: [Choosen encoding] => UTF-8</li></ul></p>");
    return help;
}

QByteArray CharEncoding::getCodecName()
{
    return codecName;
}

bool CharEncoding::setCodecName(QByteArray val)
{
    QTextCodec *codec = QTextCodec::codecForName(val);
    if (codec == NULL) {
        emit error(tr("No codec named: %1").arg(QString(val)),id);
        return false;
    } else {
        codecName = val;
        emit confUpdated();
    }
    return true;
}

void CharEncoding::transform(const QByteArray &input, QByteArray &output) {
    output.clear();

    QTextCodec *codec = QTextCodec::codecForName(codecName);
    if (codec == NULL) {
        emit error("Unknown codec",id);
        return;
    }

    if (wayValue == TransformAbstract::INBOUND) {
        QString init = QString::fromUtf8(input);
        QTextEncoder *encoder = codec->makeEncoder(QTextCodec::ConvertInvalidToNull);
        output = encoder->fromUnicode(init);
        if (encoder->hasFailure()) {
            emit error(tr("Errors were encountered while encoding"),id);
        }
    } else {
        QTextDecoder *decoder = codec->makeDecoder(QTextCodec::ConvertInvalidToNull);
        output = decoder->toUnicode(input).toUtf8();
        if (decoder->hasFailure()) {
            emit error(tr("Errors were encountered while decoding"),id);
        }
    }
}
