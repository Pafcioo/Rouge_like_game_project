# Game/States/CMakeLists.txt
file(GLOB SPAWNER_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(States STATIC ${SPAWNER_SOURCES})
target_include_directories(States PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(States
    PUBLIC
        UI
        SFML::Graphics
        SFML::Window
        SFML::System
)