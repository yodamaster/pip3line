/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#ifndef QUICKVIEWDIALOG_H
#define QUICKVIEWDIALOG_H

#include <QDialog>
#include <QList>
#include <QPoint>
#include "appdialog.h"

namespace Ui {
class QuickViewDialog;
}

class GuiHelper;
class QuickViewItem;

class QuickViewDialog : public AppDialog
{
        Q_OBJECT
        
    public:
        explicit QuickViewDialog(GuiHelper * guiHelper, QWidget *parent = 0);
        ~QuickViewDialog();
    public slots:
        void receivingData(const QByteArray &data);
    private slots:
        void newItem();
        void itemDeleted();
        void onReset();

    private:
        Q_DISABLE_COPY(QuickViewDialog)
        void addItem(const QString & conf);
        Ui::QuickViewDialog *ui;
        QList<QuickViewItem *> itemList;
        QByteArray currentData;
};

#endif // QUICKVIEWDIALOG_H
