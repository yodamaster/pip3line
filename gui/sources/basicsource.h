/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#ifndef BASICSOURCE_H
#define BASICSOURCE_H

#include "bytesourceabstract.h"

class BasicSearch : public SearchAbstract {
    Q_OBJECT
    public:
        BasicSearch(QByteArray *data, QObject *parent = 0);
        ~BasicSearch();
    private:
        void internalStart();
        QByteArray *sdata;
};

class BasicSource : public ByteSourceAbstract
{
        Q_OBJECT
    public:
        BasicSource(QObject *parent = 0);
        virtual ~BasicSource();
        QString description();
        virtual void setData(QByteArray data, quintptr source = INVALID_SOURCE);
        QByteArray getRawData();
        quint64 size();
        virtual QByteArray extract(quint64 offset, int length);
        char extract(quint64 offset);
        virtual void replace(quint64 offset, int length, QByteArray repData, quintptr source = INVALID_SOURCE);
        virtual void insert(quint64 offset, QByteArray repData, quintptr source = INVALID_SOURCE);
        virtual void remove(quint64 offset, int length, quintptr source = INVALID_SOURCE);
        virtual void clear(quintptr source = INVALID_SOURCE);
        int getViewOffset(quint64 realoffset);
        int preferredTabType();
        bool isOffsetValid(quint64 offset);
        bool isReadableText();
    protected:
        QByteArray rawData;
    private:
        Q_DISABLE_COPY(BasicSource)
        static const QByteArray TEXT;
        static const QString LOGID;
        bool validateOffsetAndSize(quint64 offset, int length);
        SearchAbstract *requestSearchObject(QObject *parent = 0);
        BasicSearch *bsearchObj;

};

#endif // BASICSOURCE_H
