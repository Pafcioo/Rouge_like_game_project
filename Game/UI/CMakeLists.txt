# Game/Spawner/CMakeLists.txt
file(GLOB SPAWNER_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(UI STATIC ${SPAWNER_SOURCES})
target_include_directories(UI PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(UI
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)