
set(SOURCES
    Accumulator.h
    Accumulator.cpp
    AutoIndexer.h
    BulletShapes.h
    BulletShapes.cpp
    CommonObject.h
    CommonObject.cpp
    Conversions.h
    CopyFrom.h
    CopyFrom.cpp
    Dump.h
    Dump.cpp
    FloatFormatString.h
    IndexEntry.h
    InputKeyActionManager.h
    InputKeyActionManager.cpp
    InputKeyBinder.h
    InputKeyBinder.cpp
    IntervalTimer.h
    IntervalTimer.cpp
    IrrCommonObject.h
    IrrCommonObject.cpp
    NamedClassInstance.h
    Ownership.h
    RelativeValue.h
    SimpleState.h
    SimpleState.cpp
    VectorHelper.h
    XMLNodeWriter.h
    XMLNodeWriter.cpp
    XMLParser.h
    XMLParser.cpp)

add_library(IospUtils STATIC ${SOURCES})

target_include_directories(IospUtils PRIVATE ${IRRLICHT_INCLUDE_DIR})
target_include_directories(IospUtils PRIVATE ${BULLET_INCLUDE_DIR})

target_include_directories(IospUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_include_directories(IospUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/thirdparty/IrrlichtI18n/)

find_package(Freetype REQUIRED)

target_include_directories(IospUtils PRIVATE ${FREETYPE_INCLUDE_DIRS})
