# Game/Factory/CMakeLists.txt
file(GLOB LOGIC_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(logic STATIC ${LOGIC_SOURCES})
target_include_directories(logic PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(logic
    PUBLIC
        entity
        factory
        SFML::Graphics
        SFML::Window
        SFML::System
)