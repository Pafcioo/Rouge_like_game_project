# Game/Spawner/CMakeLists.txt
file(GLOB SPAWNER_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Spawner STATIC ${SPAWNER_SOURCES})
target_include_directories(Spawner PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(Spawner
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)