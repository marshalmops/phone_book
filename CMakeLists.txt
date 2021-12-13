cmake_minimum_required(VERSION 3.5)

project(PhoneBook VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        include/validators/datavalidator.h
        src/validators/datavalidator.cpp
        include/validators/initialsvalidator.h
        src/validators/initialsvalidator.cpp
        include/validators/phonevalidator.h
        src/validators/phonevalidator.cpp
        include/appinitializer.h
        src/appinitializer.cpp
        src/views/phonebookview.cpp
        include/views/phonebookview.h
        include/views/administratephonestypesview.h
        src/views/administratephonestypesview.cpp
        include/editors/abonenteditor.h
        src/editors/abonenteditor.cpp
        include/editors/phoneeditor.h
        src/editors/phoneeditor.cpp
        include/editors/phonetypeeditor.h
        src/editors/phonetypeeditor.cpp
        include/models/phonebookmodel.h
        src/models/phonebookmodel.cpp
        include/models/administratephonestypesmodel.h
        src/models/administratephonestypesmodel.cpp
        include/database/databasemanager.h
        src/database/databasemanager.cpp
        include/database/databasefacades/databasefacade.h 
        src/database/databasefacades/databasefacade.cpp
        include/database/databasefacades/databasefacadeabonent.h
        src/database/databasefacades/databasefacadeabonent.cpp
        include/database/databasefacades/databasefacadephone.h
        src/database/databasefacades/databasefacadephone.cpp
        include/database/databasefacades/databasefacadephonetype.h
        src/database/databasefacades/databasefacadephonetype.cpp
        include/database/databaseconnections/databaseconnectiongenerator.h
        src/database/databaseconnections/databaseconnectiongenerator.cpp
        include/database/databaseconnections/idatabaseconnection.h
        include/database/databaseconnections/databaseconnectionsqlite.h
        src/database/databaseconnections/databaseconnectionsqlite.cpp
        include/models/abonentsmodel.h
        src/models/abonentsmodel.cpp
        include/models/phonesmodel.h
        src/models/phonesmodel.cpp
        include/models/phonestypesmodel.h
        src/models/phonestypesmodel.cpp
        include/entities/ientity.h
        include/entities/abonent.h
        src/entities/abonent.cpp
        include/entities/phone.h
        src/entities/phone.cpp
        include/entities/phonetype.h
        src/entities/phonetype.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PhoneBook
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PhoneBook APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PhoneBook SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PhoneBook
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(PhoneBook PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(PhoneBook PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PhoneBook)
endif()
