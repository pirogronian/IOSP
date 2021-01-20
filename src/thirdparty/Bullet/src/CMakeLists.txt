
add_library(Bullet STATIC)
target_include_directories(Bullet BEFORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(BulletCollision)
add_subdirectory(BulletDynamics)
add_subdirectory(LinearMath)

target_include_directories(IOSP BEFORE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(Bullet BEFORE PRIVATE -w)
