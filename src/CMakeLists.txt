
#set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

target_include_directories(IOSP SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(thirdparty)
add_subdirectory(Utils)
add_subdirectory(Tests)

set(IOSP_MAIN_SRCS
    AbstractControlPanelSceneNode.h
    AbstractControlPanelSceneNode.cpp
    BulletBodySceneNode.h
    BulletBodySceneNode.cpp
    BulletDebugDrawer.h
    BulletDebugDrawer.cpp
    BulletMotionState.h
    BulletMotionState.cpp
    BulletWorldSceneNode.h
    BulletWorldSceneNode.cpp
    Common.h
    Conversions.h
    EventReceiver.h
    EventReceiver.cpp
    main.cpp
    Simulation.h
    Simulation.cpp
    TestScene.h
    TestScene.cpp)

list(TRANSFORM IOSP_MAIN_SRCS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

target_sources(IOSP PRIVATE ${IOSP_MAIN_SRCS})

# Make the executable a default target to build & run in Visual Studio
#set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MospApplication)
