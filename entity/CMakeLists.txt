file(GLOB ENTITY_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(entity STATIC ${ENTITY_SOURCES})
target_include_directories(entity PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(entity
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)