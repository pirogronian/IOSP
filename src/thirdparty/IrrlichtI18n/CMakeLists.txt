
#include(FindPkgConfig)
#pkg_search_module(FREETYPE2 REQUIRED FREETYPE)

find_package(Freetype REQUIRED)

add_library(IrrlichtI18n STATIC)

set(SOURCES
    CGUITTFont.h
    CGUITTFont.cpp
    irrUString.h)

target_sources(IrrlichtI18n PRIVATE ${SOURCES})

target_include_directories(IrrlichtI18n PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(IrrlichtI18n PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(IrrlichtI18n PRIVATE
    freetype)

target_include_directories(IOSP PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_include_directories(IOSP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
