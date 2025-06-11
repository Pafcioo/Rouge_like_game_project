file(GLOB FACTORY_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(factory STATIC ${FACTORY_SOURCES})
target_include_directories(factory PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(factory
    PUBLIC
        entity
        algorithm
        SFML::Graphics
        SFML::Window
        SFML::System
)