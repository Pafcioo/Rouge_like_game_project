# Game/Spawner/CMakeLists.txt
file(GLOB FACTORY_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Factory STATIC ${FACTORY_SOURCES})
target_include_directories(Factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Game)