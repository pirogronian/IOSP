
add_executable(InputKeyBinderTest InputKeyBinderTest.cpp)

target_include_directories(InputKeyBinderTest PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(InputKeyBinderTest BEFORE PRIVATE "${PROJECT_SOURCE_DIR}/src/")

target_link_libraries(InputKeyBinderTest IospUtils)

add_executable(BulletTest BulletTest.cpp ../BulletDebugDrawer.h ../BulletDebugDrawer.cpp)

target_include_directories(BulletTest PRIVATE ${IRRLICHT_INCLUDE_DIR})

target_include_directories(BulletTest PRIVATE ${BULLET_INCLUDE_DIR})

target_include_directories(BulletTest BEFORE PRIVATE "${PROJECT_SOURCE_DIR}/src/")

target_link_libraries(BulletTest PRIVATE
    Bullet
    #BulletDynamics
    #BulletCollision
    #LinearMath
    Irrlicht)

add_executable(ScaleFloatDisplayTest ScaleFloatDisplayTest.cpp)

target_include_directories(ScaleFloatDisplayTest PRIVATE ${IRRLICHT_INCLUDE_DIR})
target_include_directories(ScaleFloatDisplayTest PRIVATE ${PROJECT_SOURCE_DIR}/src/)
target_include_directories(ScaleFloatDisplayTest PRIVATE ${BULLET_INCLUDE_DIR})
target_link_libraries(ScaleFloatDisplayTest PRIVATE
    #IospUtils
    IospScreenUtils
    Bullet
    Irrlicht
)
