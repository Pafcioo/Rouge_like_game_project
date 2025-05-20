# Game/AIController/CMakeLists.txt
file(GLOB AI_SOURCES
    CONFIGURE_DEPENDS
    *.cpp
    *.h
)

add_library(AIController STATIC ${AI_SOURCES})
target_include_directories(AIController PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Game)