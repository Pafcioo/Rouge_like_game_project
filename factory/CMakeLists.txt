# Game/Factory/CMakeLists.txt
file(GLOB FACTORY_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(Factory STATIC ${FACTORY_SOURCES})
target_include_directories(Factory PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(Factory
    PUBLIC
        AIController
        SFML::Graphics
        SFML::Window
        SFML::System
)