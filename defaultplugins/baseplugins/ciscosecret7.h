/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#ifndef CISCOSECRET7_H
#define CISCOSECRET7_H

#include <transformabstract.h>

class CiscoSecret7 : public TransformAbstract
{
        Q_OBJECT
    public:
        explicit CiscoSecret7();
        ~CiscoSecret7() {}
        QString name() const;
        QString description() const;
        void transform(const QByteArray &input, QByteArray &output);
        bool isTwoWays();
        static const QString id;
        QString help() const;
        unsigned int getSeed() const;
        bool setSeed(unsigned int seed);
    private:
        unsigned int seed;
        void cipher(unsigned int seed, const QByteArray &data, QByteArray &output);
        static const QByteArray ckey;
        static const unsigned int MAXSEED;
};

#endif // CISCOSECRET7_H
