file(GLOB CORE_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(core
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)