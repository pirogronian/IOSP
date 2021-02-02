cmake_minimum_required(VERSION 3.4)

#set(CMAKE_VERBOSE_MAKEFILE ON)

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
#find_package(Bullet REQUIRED Collision Dynamics)

add_definitions(-DBT_USE_DOUBLE_PRECISION -DQUATERNION_DERIVATIVE)

add_executable(IOSP)

target_include_directories(IOSP PRIVATE ${IRRLICHT_INCLUDE_DIR})
#target_include_directories(IOSP PRIVATE ${BULLET_INCLUDE_DIR})

add_subdirectory(src)

target_link_libraries(IOSP PRIVATE
    IospUtils
    IospScreenUtils
    Bullet
    #BulletCollision
    LinearMath
    Irrlicht
    IrrlichtI18n)
