
#set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

target_include_directories(IOSP SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(IOSP SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/IrrImgui/includes/)
target_include_directories(IOSP SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/IrrImgui/dependency/)
target_include_directories(IOSP SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/IrrImgui/dependency/IMGUI)

add_subdirectory(thirdparty)
add_subdirectory(Utils)
add_subdirectory(ScreenUtils)
add_subdirectory(Tests)

set(IOSP_MAIN_SRCS
    Application.h
    Application.cpp
    BulletBodySceneNode.h
    BulletBodySceneNode.cpp
    BulletDebugDrawer.h
    BulletDebugDrawer.cpp
    BulletMotionState.h
    BulletMotionState.cpp
    BulletWorldSceneNode.h
    BulletWorldSceneNode.cpp
    Common.h
    Component.h
    Component.cpp
    ControlPanelSceneNode.h
    ControlPanelSceneNode.cpp
    LinearThruster.h
    LinearThruster.cpp
    main.cpp
    MagicSimpleRocketControlPanel.h
    MagicSimpleRocketControlPanel.cpp
    ManualThrustControlPanel.h
    ManualThrustControlPanel.cpp
    Settings.h
    Settings.cpp
    SettingsWindow.h
    SettingsWindow.cpp
    Simulation.h
    Simulation.cpp
    TestScene.h
    TestScene.cpp
    TorqueThruster.h
    TorqueThruster.cpp
    ThirdPersonCamera.h
    ThirdPersonCamera.cpp
    Thruster.h
    Thruster.cpp)

list(TRANSFORM IOSP_MAIN_SRCS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

target_sources(IOSP PRIVATE ${IOSP_MAIN_SRCS})

# Make the executable a default target to build & run in Visual Studio
#set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MospApplication)
