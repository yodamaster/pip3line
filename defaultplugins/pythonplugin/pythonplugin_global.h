/**
Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com

https://github.com/nccgroup/pip3line

Released under AGPL see LICENSE for more information
**/

#ifndef PYTHONPLUGIN_GLOBAL_H
#define PYTHONPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PYTHONPLUGIN_LIBRARY)
#  define PYTHONPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PYTHONPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PYTHONPLUGIN_GLOBAL_H
