cmake_minimum_required(VERSION 3.4)
project(MOSP)

cmake_policy(SET CMP0079 NEW)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/Modules/" ${CMAKE_MODULE_PATH})

if(MSVC)
    #string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    #add_compile_options(-w)
endif()

set(CMAKE_CXX_STANDARD 17)

find_package(Irrlicht REQUIRED)

add_definitions(-DBT_USE_DOUBLE_PRECISION)

add_executable(IOSP)

target_include_directories(IOSP PRIVATE ${IRRLICHT_INCLUDE_DIR})

add_subdirectory(src)

target_link_libraries(IOSP PRIVATE
    MospUtils
    Bullet
    Irrlicht)
