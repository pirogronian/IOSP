
set(SOURCES
    ScreenElement.h
    ScreenElement.cpp
    ScreenText.h
    ScreenText.cpp)

add_library(IospHudUtils STATIC ${SOURCES})

target_include_directories(IospHudUtils PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(IospHudUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
