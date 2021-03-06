####
# Released as open source by NCC Group Plc - http://www.nccgroup.com/
#
# Developed by Gabriel Caudrelier, gabriel dot caudrelier at nccgroup dot com
#
# https://github.com/nccgroup/pip3line
#
# Released under AGPL see LICENSE for more information
####

message( STATUS "Configuring libtransform --" )
project( transform )
cmake_minimum_required( VERSION 2.8.11 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall -DLIBTRANSFORM_LIBRARY)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WITH_QT5)
	find_package(Qt5Widgets)
	find_package(Qt5Core)
	find_package(Qt5Svg)
	find_package(Qt5Concurrent)
else(WITH_QT5)	
	find_package ( Qt4 REQUIRED QtCore QtGui QtSvg)
	include ( ${QT_USE_FILE} )
endif(WITH_QT5)

set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin )

set ( transform_HDRS
	transformfactoryplugininterface.h
	commonstrings.h
	transformmgmt.h
	transformabstract.h
	pip3linecallback.h
	transformchain.h
	composedtransform.h
	modulesmanagement.h
	modulesmanagementwidget.h
	moduletransformwidget.h
	scripttransformabstract.h
	deleteablelistitem.h
	threadedprocessor.h
	)

set ( transform_SRCS
	transformmgmt.cpp
	transformabstract.cpp
	pip3linecallback.cpp
	transformchain.cpp
	composedtransform.cpp
	modulesmanagement.cpp
	modulesmanagementwidget.cpp
	moduletransformwidget.cpp
	scripttransformabstract.cpp
	deleteablelistitem.cpp
	threadedprocessor.cpp
	)

set ( transform_UIS
	modulesmanagementwidget.ui
	moduletransformwidget.ui
	deleteablelistitem.ui
	)

if(WITH_QT5)
	qt5_wrap_ui(UIS ${transform_UIS})
else(WITH_QT5)
	qt4_wrap_ui(UIS ${transform_UIS})
endif(WITH_QT5)


add_library ( transform SHARED ${transform_SRCS} ${RSCS} ${UIS} )

if(WITH_QT5)
	qt5_use_modules(transform Widgets Svg Concurrent)
else(WITH_QT5)
	target_link_libraries ( transform  ${QT_LIBRARIES} )
endif(WITH_QT5)

IF(UNIX)
	install (TARGETS transform DESTINATION lib)
	install (FILES ${transform_HDRS} DESTINATION include/libtransform )
	install (FILES ${transform_MOCS} DESTINATION include/libtransform )
	install (FILES LibTransform DESTINATION include )
ENDIF(UNIX)

