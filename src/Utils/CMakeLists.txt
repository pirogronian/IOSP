
set(SOURCES
    Accumulator.h
    Accumulator.cpp
    AutoIndexer.h
    Conversions.h
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
    VectorHelper.h
    XMLNodeWriter.h
    XMLNodeWriter.cpp
    XMLParser.h
    XMLParser.cpp)

add_library(IospUtils STATIC ${SOURCES})

target_include_directories(IospUtils PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(IospUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
