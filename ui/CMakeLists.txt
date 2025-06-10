# Game/Factory/CMakeLists.txt
file(GLOB UI_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(ui STATIC ${UI_SOURCES})
target_include_directories(ui PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(ui
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)