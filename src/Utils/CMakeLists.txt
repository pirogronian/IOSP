
set(SOURCES
    Accumulator.h
    Accumulator.cpp
    AutoIndexer.h
    IndexEntry.h
    InputKeyBinder.h
    InputKeyBinder.cpp
    NamedClassInstance.h
    VectorHelper.h)

add_library(IospUtils STATIC ${SOURCES})

target_include_directories(IospUtils PRIVATE ${PROJECT_SOURCE_DIR}/src/)
