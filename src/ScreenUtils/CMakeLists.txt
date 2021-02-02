
set(SOURCES
    ScreenElement.h
    ScreenElement.cpp
    ScreenText.h
    ScreenText.cpp)

add_library(IospScreenUtils STATIC ${SOURCES})

target_include_directories(IospScreenUtils PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(IospScreenUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
