file(GLOB ALGORITHM_SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
    inc/*.h
)

add_library(algorithm STATIC ${ALGORITHM_SOURCES})
target_include_directories(algorithm PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(algorithm
    PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)