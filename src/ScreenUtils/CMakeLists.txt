
set(SOURCES
    ScreenElement.h
    ScreenElement.cpp
    ScreenFloatDisplay.h
    ScreenFloatDisplay.cpp
    ScreenRectangle.h
    ScreenRectangle.cpp
    ScreenText.h
    ScreenText.cpp)

add_library(IospScreenUtils STATIC ${SOURCES})

target_include_directories(IospScreenUtils PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(IospScreenUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_include_directories(IospScreenUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/thirdparty/Bullet/src/)
target_include_directories(IospScreenUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/thirdparty/IrrlichtI18n/)
find_package(Freetype REQUIRED)

target_include_directories(IospScreenUtils PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(IospScreenUtils PRIVATE IospUtils)
